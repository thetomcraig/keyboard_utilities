/* Copyright (C) 2014-2017 by Jacob Alexander
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

// ----- Includes -----

// Compiler Includes
#include <Lib/ScanLib.h>

// Project Includes
#include <cli.h>
#include <led.h>
#include <print.h>
#include <matrix_scan.h>
#include <macro.h>

// KLL Include
#include <kll.h>

// Local Includes
#include "scan_loop.h"



// ----- Function Declarations -----

// CLI Functions
void cliFunc_echo( char* args );



// ----- Variables -----

// Scan Module command dictionary
CLIDict_Entry( echo,        "Example command, echos the arguments." );

CLIDict_Def( scanCLIDict, "Scan Module Commands" ) = {
	CLIDict_Item( echo ),
	{ 0, 0, 0 } // Null entry for dictionary end
};



// ----- Functions -----

// Setup
inline void Scan_setup()
{
	// Register Scan CLI dictionary
	CLI_registerDictionary( scanCLIDict, scanCLIDictName );

	// Setup GPIO pins for matrix scanning
	Matrix_setup();

	// Start Matrix Scanner
	Matrix_start();
}


// Main Poll Loop
// This is for operations that need to be run as often as possible
// Usually reserved for LED update routines and other things that need quick update rates
void Scan_poll()
{
}


// Main Periodic Scan
// This function is called periodically at a constant rate
// Useful for matrix scanning and anything that requires consistent attention
uint8_t Scan_periodic()
{
	// Scan Matrix
	return Matrix_single_scan();
}


// Signal from Macro Module that all keys have been processed (that it knows about)
inline void Scan_finishedWithMacro( uint8_t sentKeys )
{
}


// Signal from Output Module that all keys have been processed (that it knows about)
inline void Scan_finishedWithOutput( uint8_t sentKeys )
{
}


// Signal from the Output Module that the available current has changed
// current - mA
void Scan_currentChange( unsigned int current )
{
	// Indicate to all submodules current change
	Matrix_currentChange( current );
}



// ----- CLI Command Functions -----

// XXX Just an example command showing how to parse arguments (more complex than generally needed)
void cliFunc_echo( char* args )
{
	char* curArgs;
	char* arg1Ptr;
	char* arg2Ptr = args;

	// Parse args until a \0 is found
	while ( 1 )
	{
		print( NL ); // No \r\n by default after the command is entered

		curArgs = arg2Ptr; // Use the previous 2nd arg pointer to separate the next arg from the list
		CLI_argumentIsolation( curArgs, &arg1Ptr, &arg2Ptr );

		// Stop processing args if no more are found
		if ( *arg1Ptr == '\0' )
			break;

		// Print out the arg
		dPrint( arg1Ptr );
	}
}

