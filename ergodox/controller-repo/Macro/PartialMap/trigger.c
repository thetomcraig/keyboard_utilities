/* Copyright (C) 2014-2018 by Jacob Alexander
 *
 * This file is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This file is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this file.  If not, see <http://www.gnu.org/licenses/>.
 */

// ----- Includes -----

// Compiler Includes
#include <Lib/MacroLib.h>

// Project Includes
#include <led.h>
#include <print.h>

// Local Includes
#include "trigger.h"
#include "layer.h"
#include "kll.h"



// ----- Enums -----

// Bit positions are important, passes (correct key) always trump incorrect key votes
typedef enum TriggerMacroVote {
	TriggerMacroVote_Release          = 0x10, // Correct key
	TriggerMacroVote_PassRelease      = 0x18, // Correct key (both pass and release)
	TriggerMacroVote_Pass             = 0x8,  // Correct key
	TriggerMacroVote_DoNothingRelease = 0x4,  // Incorrect key
	TriggerMacroVote_DoNothing        = 0x2,  // Incorrect key
	TriggerMacroVote_Fail             = 0x1,  // Incorrect key
	TriggerMacroVote_Invalid          = 0x0,  // Invalid state
} TriggerMacroVote;

typedef enum TriggerMacroEval {
	TriggerMacroEval_DoNothing,
	TriggerMacroEval_DoResult,
	TriggerMacroEval_DoResultAndRemove,
	TriggerMacroEval_Remove,
} TriggerMacroEval;



// ----- Generated KLL Variables -----

extern const Capability CapabilitiesList[];

extern const TriggerMacro TriggerMacroList[];
extern TriggerMacroRecord TriggerMacroRecordList[];

extern const ResultMacro ResultMacroList[];



// ----- Variables -----

// Incoming Trigger Event Buffer
extern TriggerEvent macroTriggerEventBuffer[];
extern var_uint_t macroTriggerEventBufferSize;
extern var_uint_t macroTriggerEventLayerCache[];

// Debug Variables
extern uint8_t triggerPendingDebugMode;
extern uint8_t voteDebugMode;

// Pending Trigger Macro Index List
//  * Any trigger macros that need processing from a previous macro processing loop
// TODO, figure out a good way to scale this array size without wasting too much memory, but not rejecting macros
//       Possibly could be calculated by the KLL compiler
// XXX It may be possible to calculate the worst case using the KLL compiler
#if TriggerMacroNum == 0
#undef TriggerMacroNum
#define TriggerMacroNum 1
#endif
index_uint_t macroTriggerMacroPendingList[ TriggerMacroNum ] = { 0 };
index_uint_t macroTriggerMacroPendingListSize = 0;



// ----- Protected Macro Functions -----

extern void Result_appendResultMacroToPendingList( const TriggerMacro *triggerMacro );



// ----- Functions -----

// -- Debug --

// Show TriggerMacroVote
void Trigger_showTriggerMacroVote( TriggerMacroVote vote, uint8_t long_trigger_macro )
{
	const char *result = "";

	// Long Macro
	if ( long_trigger_macro )
	{
		print("l");
	}
	// Short Macro
	else
	{
		print("s");
	}

	// Static voting
	switch ( vote )
	{
	case TriggerMacroVote_Invalid:
		result = "V:I";
		break;

	case TriggerMacroVote_Release:
		result = "V:R";
		break;

	case TriggerMacroVote_Pass:
		result = "V:P";
		break;

	case TriggerMacroVote_PassRelease:
		result = "V:PR";
		break;

	default:
		print("V:");
		if ( vote & TriggerMacroVote_Fail )
		{
			print("F");
		}
		if ( vote & TriggerMacroVote_DoNothingRelease )
		{
			print("NR");
		}
		else if ( vote & TriggerMacroVote_DoNothing )
		{
			print("N");
		}
		return;
	}

	print( result );
}


// -- General --

// Determine if long ResultMacro (more than 1 seqence element)
uint8_t Trigger_isLongResultMacro( const ResultMacro *macro )
{
	// Check the second sequence combo length
	// If non-zero return non-zero (long sequence)
	// 0 otherwise (short sequence)
	var_uint_t position = 1;
	for ( var_uint_t result = 0; result < macro->guide[0]; result++ )
		position += ResultGuideSize( (ResultGuide*)&macro->guide[ position ] );
	return macro->guide[ position ];
}


// Determine if long TriggerMacro (more than 1 sequence element)
uint8_t Trigger_isLongTriggerMacro( const TriggerMacro *macro )
{
	// Check the second sequence combo length
	// If non-zero return non-zero (long sequence)
	// 0 otherwise (short sequence)
	return macro->guide[ macro->guide[0] * TriggerGuideSize + 1 ];
}


// Handle short trigger PHRO/AODO state transitions
TriggerMacroVote Trigger_evalShortTriggerMacroVote_PHRO( ScheduleState state )
{
	switch ( state & 0x0F )
	{
	// Correct key, pressed, possible passing
	case ScheduleType_P:
		return TriggerMacroVote_Pass;

	// Correct key, held, possible passing or release
	case ScheduleType_H:
		return TriggerMacroVote_PassRelease;

	// Correct key, released, possible release
	case ScheduleType_R:
		return TriggerMacroVote_Release;

	// Invalid state, fail
	default:
		return TriggerMacroVote_Fail;
	}
}


// Handle short trigger DRO state transitions
TriggerMacroVote Trigger_evalShortTriggerMacroVote_DRO( ScheduleState state )
{
	switch ( state )
	{
	// Correct event, possible passing
	case ScheduleType_Done:
	case ScheduleType_Repeat:
		return TriggerMacroVote_Pass;

	// Invalid state, fail
	default:
		return TriggerMacroVote_Fail;
	}
}


// Votes on the given key vs. guide, short macros
TriggerMacroVote Trigger_evalShortTriggerMacroVote( TriggerEvent *event, TriggerGuide *guide )
{
	// Lookup full index
	var_uint_t guide_index = KLL_TriggerIndex_loopkup( guide->type, guide->scanCode );
	var_uint_t event_index = KLL_TriggerIndex_loopkup( event->type, event->index );

	// Depending on key type
	switch ( guide->type )
	{
	// Normal State Type
	case TriggerType_Switch1:
	case TriggerType_Switch2:
	case TriggerType_Switch3:
	case TriggerType_Switch4:
	// LED State Type
	case TriggerType_LED1:
	// Layer State Type
	case TriggerType_Layer1:
	case TriggerType_Layer2:
	case TriggerType_Layer3:
	case TriggerType_Layer4:
	// Activity State Types
	case TriggerType_Sleep1:
	case TriggerType_Resume1:
	case TriggerType_Inactive1:
	case TriggerType_Active1:
		// For short TriggerMacros completely ignore incorrect keys
		// Only monitor 0x70 bits if set in the guide, otherwise ensure they are 0x00
		// Used for Layer state information
		if (
			guide_index == event_index &&
			guide->type == event->type &&
			(
				(guide->state & 0x70) == (event->state & 0x70) ||
				(guide->state & 0x70) == 0x00
			)
		)
		{
			return Trigger_evalShortTriggerMacroVote_PHRO( event->state );
		}

		return TriggerMacroVote_DoNothing;

	// Analog State Type
	case TriggerType_Analog1:
	case TriggerType_Analog2:
	case TriggerType_Analog3:
	case TriggerType_Analog4:
		erro_print("Analog State Type - Not implemented...");
		break;

	// Animation State Type
	case TriggerType_Animation1:
	case TriggerType_Animation2:
	case TriggerType_Animation3:
	case TriggerType_Animation4:
		// For short TriggerMacros completely ignore incorrect triggers
		if (
			guide_index == event_index &&
			guide->type == event->type &&
			guide->state == event->state
		)
		{
			return Trigger_evalShortTriggerMacroVote_DRO( event->state );
		}

		return TriggerMacroVote_DoNothing;

	// Invalid State Type
	default:
		erro_print("Invalid State Type. This is a bug.");
		break;
	}

	// XXX Shouldn't reach here
	return TriggerMacroVote_Invalid;
}


// Handle long trigger PHRO/AODO state transitions
TriggerMacroVote Trigger_evalLongTriggerMacroVote_PHRO( ScheduleState state, uint8_t correct )
{
	// Correct scancode match
	if ( correct )
	{
		switch ( state )
		{
		// Correct key, pressed, possible passing
		case ScheduleType_P:
			return TriggerMacroVote_Pass;

		// Correct key, held, possible passing or release
		case ScheduleType_H:
			return TriggerMacroVote_PassRelease;

		// Correct key, released, possible release
		case ScheduleType_R:
			return TriggerMacroVote_Release;

		// Invalid state, fail
		default:
			return TriggerMacroVote_Fail;
		}
	}
	// Incorrect scancode match
	else
	{
		switch ( state )
		{
		// Wrong key, pressed, fail
		case ScheduleType_P:
			return TriggerMacroVote_Fail;

		// Wrong key, held, do not pass (no effect)
		case ScheduleType_H:
			return TriggerMacroVote_DoNothing;

		// Wrong key released, fail out if pos == 0
		case ScheduleType_R:
			return TriggerMacroVote_DoNothing | TriggerMacroVote_DoNothingRelease;

		// Invalid state, fail
		default:
			return TriggerMacroVote_Fail;
		}
	}
}


// Handle long trigger DRO state transitions
TriggerMacroVote Trigger_evalLongTriggerMacroVote_DRO( ScheduleState state, uint8_t correct )
{
	// Correct match
	if ( correct )
	{
		switch ( state )
		{
		// Correct event, possible passing
		case ScheduleType_Done:
		case ScheduleType_Repeat:
			return TriggerMacroVote_Pass;

		// Invalid state, fail
		default:
			return TriggerMacroVote_Fail;
		}
	}
	// Incorrect match
	else
	{
		return TriggerMacroVote_Fail;
	}
}


// Votes on the given key vs. guide, long macros
// A long macro is defined as a guide with more than 1 combo
TriggerMacroVote Trigger_evalLongTriggerMacroVote( TriggerEvent *event, TriggerGuide *guide )
{
	// Lookup full index
	var_uint_t guide_index = KLL_TriggerIndex_loopkup( guide->type, guide->scanCode );
	var_uint_t event_index = KLL_TriggerIndex_loopkup( event->type, event->index );

	// Depending on key type
	switch ( guide->type )
	{
	// Normal State Type
	case TriggerType_Switch1:
	case TriggerType_Switch2:
	case TriggerType_Switch3:
	case TriggerType_Switch4:
	// LED State Type
	case TriggerType_LED1:
	// Layer State Type
	case TriggerType_Layer1:
	case TriggerType_Layer2:
	case TriggerType_Layer3:
	case TriggerType_Layer4:
	// Activity State Types
	case TriggerType_Sleep1:
	case TriggerType_Resume1:
	case TriggerType_Inactive1:
	case TriggerType_Active1:
		// Depending on the state of the buffered key, make voting decision
		// Only monitor 0x70 bits if set in the guide, otherwise ensure they are 0x00
		// Used for Layer state information
		// Correct key
		if (
			guide_index == event_index &&
			guide->type == event->type &&
			(
				(guide->state & 0x70) == (event->state & 0x70) ||
				(guide->state & 0x70) == 0x00
			)
		)
		{
			return Trigger_evalLongTriggerMacroVote_PHRO( event->state, 1 );
		}
		// Incorrect key
		else
		{
			return Trigger_evalLongTriggerMacroVote_PHRO( event->state, 0 );
		}

		break;

	// Analog State Type
	case TriggerType_Analog1:
	case TriggerType_Analog2:
	case TriggerType_Analog3:
	case TriggerType_Analog4:
		erro_print("Analog State Type - Not implemented...");
		break;

	// Animation State Type
	case TriggerType_Animation1:
	case TriggerType_Animation2:
	case TriggerType_Animation3:
	case TriggerType_Animation4:
		// Depending on the state of the buffered key, make voting decision
		// Correct trigger
		if (
			guide_index == event_index &&
			guide->type == event->type &&
			guide->state == event->state
		)
		{
			return Trigger_evalLongTriggerMacroVote_DRO( event->state, 1 );
		}
		// Incorrect trigger
		else
		{
			return Trigger_evalLongTriggerMacroVote_DRO( event->state, 0 );
		}

		break;

	// Invalid State Type
	default:
		erro_print("Invalid State Type. This is a bug.");
		break;
	}

	// XXX Shouldn't reach here
	return TriggerMacroVote_Invalid;
}


// Iterate over combo, voting on the key state
TriggerMacroVote Trigger_overallVote(
	const TriggerMacro *macro,
	TriggerMacroRecord *record,
	uint8_t long_trigger_macro,
	var_uint_t pos
)
{
	// Length of the combo being processed
	uint8_t comboLength = macro->guide[ pos ] * TriggerGuideSize;

	// The macro is waiting for input when in the TriggerMacro_Waiting state
	// Once all keys have been pressed/held (only those keys), entered TriggerMacro_Press state (passing)
	// Transition to the next combo (if it exists) when a single key is released (TriggerMacro_Release state)
	// On scan after position increment, change to TriggerMacro_Waiting state
	// TODO Add support for 0x00 Key state (not pressing a key, not all that useful in general)
	TriggerMacroVote overallVote = TriggerMacroVote_Invalid;
	for ( uint8_t comboItem = pos + 1; comboItem < pos + comboLength + 1; comboItem += TriggerGuideSize )
	{
		// Assign TriggerGuide element (key type, state and scancode)
		TriggerGuide *guide = (TriggerGuide*)(&macro->guide[ comboItem ]);

		TriggerMacroVote vote = TriggerMacroVote_Invalid;
		// Iterate through the key buffer, comparing to each key in the combo
		for ( var_uint_t key = 0; key < macroTriggerEventBufferSize; key++ )
		{
			// Lookup key information
			TriggerEvent *triggerInfo = &macroTriggerEventBuffer[ key ];

			// Vote on triggers
			vote |= long_trigger_macro
				? Trigger_evalLongTriggerMacroVote( triggerInfo, guide )
				: Trigger_evalShortTriggerMacroVote( triggerInfo, guide );
		}

		// Mask out incorrect votes, if anything indicates a pass
		if ( vote >= TriggerMacroVote_Pass )
		{
			vote &= TriggerMacroVote_Release | TriggerMacroVote_PassRelease | TriggerMacroVote_Pass;
		}

		// If no pass vote was found after scanning all of the keys
		// Fail the combo, if this is a short macro (long macros already will have a fail vote)
		if ( !long_trigger_macro && vote < TriggerMacroVote_Pass )
		{
			vote |= TriggerMacroVote_Fail;
		}

		// After voting, append to overall vote
		overallVote |= vote;
	}

	return overallVote;
}


// Evaluate/Update TriggerMacro
TriggerMacroEval Trigger_evalTriggerMacro( var_uint_t triggerMacroIndex )
{
	// Lookup TriggerMacro
	const TriggerMacro *macro = &TriggerMacroList[ triggerMacroIndex ];
	TriggerMacroRecord *record = &TriggerMacroRecordList[ triggerMacroIndex ];

	// Check if this is a long Trigger Macro
	uint8_t long_trigger_macro = Trigger_isLongTriggerMacro( macro );

	// Long Macro
	if ( long_trigger_macro )
	{
		// Check if macro has finished and should be incremented sequence elements
		if ( record->state != TriggerMacro_Waiting )
		{
			record->prevPos = record->pos;
			record->pos = record->pos + macro->guide[ record->pos ] * TriggerGuideSize + 1;
		}

		// Current Macro position
		var_uint_t pos = record->pos;

		// Length of the combo being processed
		uint8_t comboLength = macro->guide[ pos ] * TriggerGuideSize;

		TriggerMacroVote overallVote = TriggerMacroVote_Invalid;
		// Iterate through the items in the combo, voting the on the key state
		// If any of the pressed keys do not match, fail the macro
		if ( comboLength != 0 )
		{
			overallVote |= Trigger_overallVote( macro, record, long_trigger_macro, pos );
		}

		// If this is a sequence, and have processed at least one vote already
		// then we need to keep track of releases
		if ( pos != 0 )
		{
			overallVote |= Trigger_overallVote( macro, record, long_trigger_macro, record->prevPos );
		}

		// If no pass vote was found after scanning the entire combo
		// And this is the first position in the combo, just remove it (nothing important happened)
		if ( overallVote & TriggerMacroVote_DoNothingRelease && pos == 0 )
		{
			overallVote |= TriggerMacroVote_Fail;
		}

		// Vote Debug
		switch ( voteDebugMode )
		{
		case 1:
			Trigger_showTriggerMacroVote( overallVote, long_trigger_macro );
			print( NL );
			break;
		}

		// Decide new state of macro after voting
		// Fail macro, remove from pending list
		if ( overallVote & TriggerMacroVote_Fail )
		{
			return TriggerMacroEval_Remove;
		}
		// Do nothing, incorrect key is being held or released
		else if ( overallVote & TriggerMacroVote_DoNothing )
		{
			record->state = TriggerMacro_Waiting;

			// Just doing nothing :)
		}
		// If ready for release state but we get both release and the next press at the same time
		// This is unlikely, but possible
		else if ( ( overallVote & TriggerMacroVote_PassRelease ) == TriggerMacroVote_PassRelease )
		{
			record->state = TriggerMacro_PressRelease;

			// If this is the last combo in the sequence, trigger result
			if ( macro->guide[ pos + comboLength + 1 ] == 0 )
			{
				return TriggerMacroEval_DoResult;
			}
		}
		// If ready for transition and in Press state, increment combo position
		else if ( overallVote & TriggerMacroVote_Release && record->state & TriggerMacro_Press )
		{
			record->state = TriggerMacro_Release;

			// If this is the last combo in the sequence, trigger result
			// Or, the final release of a sequence
			if ( macro->guide[ pos + comboLength + 1 ] == 0 || comboLength == 0 )
			{
				return TriggerMacroEval_DoResult;
			}
		}
		// If passing and in Waiting state, set macro state to Press
		else if ( overallVote & TriggerMacroVote_Pass
			&& ( record->state == TriggerMacro_Waiting || record->state & TriggerMacro_Press ) )
		{
			record->state = TriggerMacro_Press;

			// If this is the last combo in the sequence, trigger result
			if ( macro->guide[ pos + comboLength + 1 ] == 0 )
			{
				return TriggerMacroEval_DoResult;
			}
		}
	}
	// Short Macro
	else
	{
		// Current Macro position
		var_uint_t pos = record->pos;

		// Iterate through the items in the combo, voting the on the key state
		// If any of the pressed keys do not match, fail the macro
		TriggerMacroVote overallVote = Trigger_overallVote( macro, record, long_trigger_macro, pos );

		// Vote Debug
		switch ( voteDebugMode )
		{
		case 1:
			Trigger_showTriggerMacroVote( overallVote, long_trigger_macro );
			print( NL );
			break;
		}

		// Decide new state of macro after voting
		// Fail macro, remove from pending list
		if ( overallVote & TriggerMacroVote_Fail )
		{
			return TriggerMacroEval_Remove;
		}
		// If passing and in Waiting state, set macro state to Press
		// And trigger result
		else if ( overallVote & TriggerMacroVote_Pass
			&& ( record->state == TriggerMacro_Waiting || record->state == TriggerMacro_Press )
		)
		{
			record->state = TriggerMacro_Press;

			// Long result macro (more than 1 combo)
			if ( Trigger_isLongResultMacro( &ResultMacroList[ macro->result ] ) )
			{
				// Only ever trigger result once, on press
				if ( overallVote == TriggerMacroVote_Pass )
				{
					return TriggerMacroEval_DoResultAndRemove;
				}
			}
			// Short result macro
			else
			{
				// Trigger result continuously
				return TriggerMacroEval_DoResult;
			}
		}
		// Otherwise, just remove the macro on key release
		else if ( overallVote & TriggerMacroVote_Release )
		{
			// Long result macro (more than 1 combo) are ignored (only on press)
			if ( !Trigger_isLongResultMacro( &ResultMacroList[ macro->result ] ) )
			{
				record->state = TriggerMacro_Release;

				return TriggerMacroEval_DoResultAndRemove;
			}
		}

		// This is a short macro, just remove it
		// The state can be rebuilt on the next iteration
		return TriggerMacroEval_Remove;
	}

	return TriggerMacroEval_DoNothing;
}


// Update pending trigger list
void Trigger_updateTriggerMacroPendingList()
{
	// Iterate over the macroTriggerEventBuffer to add any new Trigger Macros to the pending list
	for ( var_uint_t key = 0; key < macroTriggerEventBufferSize; key++ )
	{
		TriggerEvent *event = &macroTriggerEventBuffer[ key ];

		// If this is a release case, indicate to layer lookup for possible latch expiry
		uint8_t latch_expire = event->state == ScheduleType_R;

		// Lookup Trigger List
		nat_ptr_t *triggerList = Layer_layerLookup( event, latch_expire );

		// If there was an error during lookup, skip
		if ( triggerList == 0 )
			continue;

		// Number of Triggers in list
		nat_ptr_t triggerListSize = triggerList[0];

		// Iterate over triggerList to see if any TriggerMacros need to be added
		// First item is the number of items in the TriggerList
		for ( var_uint_t macro = 1; macro < triggerListSize + 1; macro++ )
		{
			// Lookup trigger macro index
			var_uint_t triggerMacroIndex = triggerList[ macro ];

			// Iterate over macroTriggerMacroPendingList to see if any macro in the scancode's
			//  triggerList needs to be added
			var_uint_t pending = 0;
			for ( ; pending < macroTriggerMacroPendingListSize; pending++ )
			{
				// Stop scanning if the trigger macro index is found in the pending list
				if ( macroTriggerMacroPendingList[ pending ] == triggerMacroIndex )
					break;
			}

			// If the triggerMacroIndex (macro) was not found in the macroTriggerMacroPendingList
			// Add it to the list
			if ( pending == macroTriggerMacroPendingListSize )
			{
				macroTriggerMacroPendingList[ macroTriggerMacroPendingListSize++ ] = triggerMacroIndex;

				// Reset macro position
				TriggerMacroRecordList[ triggerMacroIndex ].pos     = 0;
				TriggerMacroRecordList[ triggerMacroIndex ].prevPos = 0;
				TriggerMacroRecordList[ triggerMacroIndex ].state   = TriggerMacro_Waiting;
			}
		}
	}
}


void Trigger_setup()
{
	// Initialize TriggerMacro states
	for ( var_uint_t macro = 0; macro < TriggerMacroNum; macro++ )
	{
		TriggerMacroRecordList[ macro ].pos     = 0;
		TriggerMacroRecordList[ macro ].prevPos = 0;
		TriggerMacroRecordList[ macro ].state   = TriggerMacro_Waiting;
	}
}


void Trigger_process()
{
	// Update pending trigger list, before processing TriggerMacros
	Trigger_updateTriggerMacroPendingList();

	// Tail pointer for macroTriggerMacroPendingList
	// Macros must be explicitly re-added
	var_uint_t macroTriggerMacroPendingListTail = 0;

	// Display trigger information before processing
	if ( triggerPendingDebugMode )
	{
		print("\033[1;30mTPe\033[0m");
		for ( var_uint_t macro = 0; macro < macroTriggerMacroPendingListSize; macro++ )
		{
			print(" ");
			printInt8( macroTriggerMacroPendingList[ macro ] );
		}
		print(NL);
	}

	// Iterate through the pending TriggerMacros, processing each of them
	for ( var_uint_t macro = 0; macro < macroTriggerMacroPendingListSize; macro++ )
	{
		index_uint_t cur_macro = macroTriggerMacroPendingList[ macro ];
		switch ( Trigger_evalTriggerMacro( cur_macro ) )
		{
		// Trigger Result Macro (purposely falling through)
		case TriggerMacroEval_DoResult:
			// Append ResultMacro to PendingList
			Result_appendResultMacroToPendingList(
				&TriggerMacroList[ cur_macro ]
			);

		default:
			macroTriggerMacroPendingList[ macroTriggerMacroPendingListTail++ ] = cur_macro;
			break;

		// Trigger Result Macro and Remove (purposely falling through)
		case TriggerMacroEval_DoResultAndRemove:
			// Append ResultMacro to PendingList
			Result_appendResultMacroToPendingList(
				&TriggerMacroList[ cur_macro ]
			);

		// Remove Macro from Pending List, nothing to do, removing by default
		case TriggerMacroEval_Remove:
			break;
		}
	}

	// Update the macroTriggerMacroPendingListSize with the tail pointer
	macroTriggerMacroPendingListSize = macroTriggerMacroPendingListTail;
}

