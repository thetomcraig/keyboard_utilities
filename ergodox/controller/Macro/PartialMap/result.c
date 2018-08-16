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
#include <Lib/periodic.h>

// Project Includes
#include <led.h>
#include <print.h>

// Local Includes
#include "result.h"
#include "kll.h"



// ----- Enums -----

typedef enum ResultMacroEval {
	ResultMacroEval_DoNothing,
	ResultMacroEval_Remove,
} ResultMacroEval;



// ----- Structs -----

// Storage container for delayed result capabilities
typedef struct ResultCapabilityStackItem {
	TriggerMacro *trigger;
	uint8_t       state;
	uint8_t       stateType;
	uint8_t       capabilityIndex;
	uint8_t      *args;
} ResultCapabilityStackItem;

typedef struct ResultCapabilityStack {
	ResultCapabilityStackItem stack[ ResultCapabilityStackSize_define ];
	uint8_t                   size;
} ResultCapabilityStack;



// ----- KLL Generated Variables -----

extern const Capability CapabilitiesList[];

extern const ResultMacro ResultMacroList[];
extern ResultMacroRecord ResultMacroRecordList[];

extern var_uint_t macroTriggerEventBufferSize;
extern TriggerEvent macroTriggerEventBuffer[];



// ----- Variables -----

// Pending Result Macro Index List
//  * Any result macro that needs processing from a previous macro processing loop
ResultsPending macroResultMacroPendingList;

// Delayed capabilities stack
volatile ResultCapabilityStack macroResultDelayedCapabilities;

#if defined(_host_)
// Host-side KLL capability callback data
ResultCapabilityStackItem resultCapabilityCallbackData;
#endif

// Capability debug mode
uint8_t capDebugMode;



// ----- Functions -----

#if defined(_host_)
// Callback for host-side kll
extern int Output_callback( char* command, char* args );
#endif


void Result_evalResultMacroCombo(
	ResultPendingElem *resultElem,
	const ResultMacro *macro,
	ResultMacroRecord *record,
	var_uint_t *comboItem
)
{
	// Function Counter, used to keep track of the combo items processed
	var_uint_t funcCount = 0;

	// Length of combo being processed
	uint8_t pos = *comboItem - 1;
	uint8_t comboLength = macro->guide[ pos ];

	// Iterate through the Result Combo
	while ( funcCount < comboLength )
	{
		// Assign TriggerGuide element (key type, state and scancode)
		ResultGuide *guide = (ResultGuide*)(&macro->guide[ *comboItem ]);

		// Determine if this is a safe capability (i.e. can be execute it immediately)
		if ( CapabilitiesList[ guide->index ].features & CapabilityFeature_Safe )
		{
			// Do lookup on capability function
			void (*capability)(TriggerMacro*, uint8_t, uint8_t, uint8_t*) = \
				(void(*)(TriggerMacro*, uint8_t, uint8_t, uint8_t*))(CapabilitiesList[ guide->index ].func);

			// Capability debug
			if ( capDebugMode )
			{
				dbug_msg("Safe: ");
				capability( resultElem->trigger, ScheduleType_Debug, TriggerType_Debug, &guide->args );
				print( NL );
			}

#if defined(_host_)
			// Callback to indicate a capability has been called
			resultCapabilityCallbackData.trigger         = resultElem->trigger;
			resultCapabilityCallbackData.state           = record->state;
			resultCapabilityCallbackData.stateType       = record->stateType;
			resultCapabilityCallbackData.capabilityIndex = guide->index;
			resultCapabilityCallbackData.args            = &guide->args;

			Output_callback( "capabilityCallback", "immediate" );
#endif

			// Call capability
			capability( resultElem->trigger, record->state, record->stateType, &guide->args );
		}
		// Otherwise, queue up the capability for later
		else if ( macroResultDelayedCapabilities.size < ResultCapabilityStackSize_define )
		{
			// Make sure we haven't already added this exact capability (with same state)
			uint8_t size = macroResultDelayedCapabilities.size;
			uint8_t pos = 0;
			for ( ; pos < size; pos++ )
			{
				volatile ResultCapabilityStackItem *item = &macroResultDelayedCapabilities.stack[ pos ];
				// Check each of the conditions
				if (
					item->trigger == resultElem->trigger &&
					item->state == record->state &&
					item->stateType == record->stateType &&
					item->capabilityIndex == guide->index
				)
				{
					// Check args to make sure it's not a NULL pointer first
					if ( guide->args != 0 && item->args == &guide->args )
					{
						// Don't add
						break;
					}
					else if ( guide->args == 0 )
					{
						// Don't add
						break;
					}
				}
			}

			// Only add if we've gone through the entire list and not found a match
			if ( pos >= size )
			{
				volatile ResultCapabilityStackItem *item = &macroResultDelayedCapabilities.stack[ size ];
				item->trigger         = resultElem->trigger;
				item->state           = record->state;
				item->stateType       = record->stateType;
				item->capabilityIndex = guide->index;
				item->args            = &guide->args;
				macroResultDelayedCapabilities.size++;
			}
		}
		else
		{
			warn_print("Delayed capability stack full!");
		}

		// Increment counters
		funcCount++;
		*comboItem += ResultGuideSize( (ResultGuide*)(&macro->guide[ *comboItem ]) );
	}
}


// Append result macro to pending list, duplicates are ok
void Result_appendResultMacroToPendingList( const TriggerMacro *triggerMacro )
{
	// Lookup result macro index
	var_uint_t resultMacroIndex = triggerMacro->result;

	// Add, even if there's a duplicate
	// There may be multiple triggers that specify the capability
	// Different triggers may result in different final results
	ResultPendingElem *elem = &macroResultMacroPendingList.data[ macroResultMacroPendingList.size++ ];
	elem->trigger = (TriggerMacro*)triggerMacro;
	elem->index = resultMacroIndex;

	// Lookup index and type of the last key in the last combo
	var_uint_t pos = 0;
	for ( uint8_t comboLength = triggerMacro->guide[0]; comboLength > 0; )
	{
		pos += TriggerGuideSize * comboLength + 1;
		comboLength = triggerMacro->guide[ pos ];
	}

	TriggerGuide *guide = (TriggerGuide*)&triggerMacro->guide[ pos - TriggerGuideSize ];
	uint8_t index = guide->scanCode;
	uint8_t type = guide->type;

	// Lookup index in buffer list for the current state and stateType
	for ( var_uint_t keyIndex = 0; keyIndex < macroTriggerEventBufferSize; keyIndex++ )
	{
		if (
			macroTriggerEventBuffer[ keyIndex ].index == index &&
			macroTriggerEventBuffer[ keyIndex ].type == type
		)
		{
			elem->record.state     = macroTriggerEventBuffer[ keyIndex ].state;
			elem->record.stateType = macroTriggerEventBuffer[ keyIndex ].type;

			// If this is a Layer stateType, mask the Shift/Latch/Lock information
			switch ( elem->record.stateType )
			{
			case TriggerType_Layer1:
			case TriggerType_Layer2:
			case TriggerType_Layer3:
			case TriggerType_Layer4:
				// We don't want to mask 0xFF, which is a debug state
				if ( elem->record.state & 0xF0 && ( elem->record.state & 0x80 ) == 0x00 )
				{
					// Need to mask over 0x70, allow through all the rest of the bits
					elem->record.state &= 0x8F;
				}
				break;
			}
			break;
		}
	}

	// Reset the macro position
	elem->record.prevPos = 0;
	elem->record.pos = 0;
}


// Evaluate/Update ResultMacro
ResultMacroEval Result_evalResultMacro( ResultPendingElem *resultElem )
{
	// Lookup ResultMacro
	const ResultMacro *macro = &ResultMacroList[ resultElem->index ];

	// Lookup ResultMacroRecord
	ResultMacroRecord *record = &resultElem->record;

	// Current Macro position
	var_uint_t pos = record->pos;

	// Combo Item Position within the guide
	var_uint_t comboItem = pos + 1;

	// Process opposing event for previous item in sequence (if necessary)
	if ( record->prevPos != pos )
	{
		// Previous comboItem position
		var_uint_t oComboItem = record->prevPos + 1;

		// TODO (HaaTa) Calculate opposing state and stateType
		ResultMacroRecord oRecord = {
			record->pos,
			record->prevPos,
			ScheduleType_R,
			record->stateType,
		};
		Result_evalResultMacroCombo( resultElem, macro, &oRecord, &oComboItem );
	}

	// Evaluate Combo
	Result_evalResultMacroCombo( resultElem, macro, record, &comboItem );

	// Move to next item in the sequence
	record->prevPos = record->pos;
	record->pos = comboItem;

	// If the ResultMacro is finished, remove
	if ( macro->guide[ comboItem ] == 0 )
	{
		record->prevPos = 0;
		record->pos = 0;
		return ResultMacroEval_Remove;
	}

	// Otherwise leave the macro in the list
	return ResultMacroEval_DoNothing;
}


void Result_setup()
{
	// Initialize macroResultMacroPendingList
	macroResultMacroPendingList.size = 0;

	// Reset delayed capabilities stack
	macroResultDelayedCapabilities.size = 0;

	// Capability debug mode
	capDebugMode = 0;
}


// Process delayed capabilities
// Capabilities that are not called immediately (i.e. ones that are not deemed as thread safe)
// are processed with this function
void Result_process_delayed()
{
	// Disable periodic interrupts if we have delayed capabilities
	Periodic_disable();

	// Process stack until empty
	// For each empty, make sure interrupts are disabled
	while ( macroResultDelayedCapabilities.size > 0 )
	{
		// Lookup stack
		volatile ResultCapabilityStackItem *item = &macroResultDelayedCapabilities.stack[macroResultDelayedCapabilities.size - 1];

		// Do lookup on capability function
		void (*capability)(TriggerMacro*, uint8_t, uint8_t, uint8_t*) = \
			(void(*)(TriggerMacro*, uint8_t, uint8_t, uint8_t*))(CapabilitiesList[ item->capabilityIndex ].func);

		// Capability debug
		if ( capDebugMode )
		{
			dbug_msg("Un-safe: ");
			capability( item->trigger, ScheduleType_Debug, TriggerType_Debug, item->args );
			print( NL );
		}

#if defined(_host_)
		// Callback to indicate a capability has been called
		resultCapabilityCallbackData.trigger         = item->trigger;
		resultCapabilityCallbackData.state           = item->state;
		resultCapabilityCallbackData.stateType       = item->stateType;
		resultCapabilityCallbackData.capabilityIndex = item->capabilityIndex;
		resultCapabilityCallbackData.args            = item->args;

		Output_callback( "capabilityCallback", "delayed" );
#endif

		// Call capability
		capability( item->trigger, item->state, item->stateType, item->args );

		// Decrease stack size
		macroResultDelayedCapabilities.size--;
	}

	// Re-enable periodic interrupts
	Periodic_enable();
}


void Result_process()
{
	// Tail pointer for macroResultMacroPendingList
	// Macros must be explicitly re-added
	index_uint_t macroResultMacroPendingListTail = 0;

	// Iterate through the pending ResultMacros, processing each of them
	for ( index_uint_t macro = 0; macro < macroResultMacroPendingList.size; macro++ )
	{
		switch ( Result_evalResultMacro( &macroResultMacroPendingList.data[ macro ] ) )
		{
		// Re-add macros to pending list
		case ResultMacroEval_DoNothing:
		default:
			memcpy( &macroResultMacroPendingList.data[ macroResultMacroPendingListTail++ ],
				&macroResultMacroPendingList.data[ macro ],
				sizeof( ResultPendingElem )
			);
			break;

		// Remove Macro from Pending List, nothing to do, removing by default
		case ResultMacroEval_Remove:
			break;
		}
	}

	// Update the macroResultMacroPendingListSize with the tail pointer
	macroResultMacroPendingList.size = macroResultMacroPendingListTail;
}

