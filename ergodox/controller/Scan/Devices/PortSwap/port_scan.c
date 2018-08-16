/* Copyright (C) 2015-2018 by Jacob Alexander
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
#include <Lib/ScanLib.h>

// Project Includes
#include <cli.h>
#include <kll_defs.h>
#include <latency.h>
#include <led.h>
#include <print.h>

// USB Includes
#if defined(_avr_at_)
#include <avr/usb_keyboard_serial.h>
#elif defined(_kinetis_) || defined(_sam_) //AVR
#include <arm/usb_dev.h>
#endif

// Interconnect Includes
#include <connect_scan.h>

// Local Includes
#include "port_scan.h"



// ----- Defines -----

#define USB_SWAP_PIN 4
#define UART_TXRX_PIN 12
#define UART_SWAP_PIN 13


// ----- Structs -----



// ----- Function Declarations -----

// CLI Functions
void cliFunc_portCross( char* args );
void cliFunc_portUART ( char* args );
void cliFunc_portUSB  ( char* args );



// ----- Variables -----

uint32_t Port_lastcheck_ms;

// Scan Module command dictionary
CLIDict_Entry( portCross, "Cross interconnect pins." );
CLIDict_Entry( portUSB,   "Swap USB ports manually, forces usb and interconnect to re-negotiate if necessary." );
CLIDict_Entry( portUART,  "Swap interconnect ports." );

CLIDict_Def( portCLIDict, "Port Swap Module Commands" ) = {
	CLIDict_Item( portCross ),
	CLIDict_Item( portUART ),
	CLIDict_Item( portUSB ),
	{ 0, 0, 0 } // Null entry for dictionary end
};

// Latency measurement resource
static uint8_t portLatencyResource;



// ----- Functions -----

void Port_usb_swap()
{
	info_print("USB Port Swap");

	// PTA4 - USB Swap
#if defined(_kinetis_)
	GPIOA_PTOR |= (1<<USB_SWAP_PIN);
#elif defined(_sam_)
	if (PIOA->ODSR & (1<<USB_SWAP_PIN)) {
		PIOA->CODR = (1<<USB_SWAP_PIN);
	} else {
		PIOA->SODR = (1<<USB_SWAP_PIN);
	}
#endif

	// Re-initialize usb
	// Call usb_configured() to check if usb is ready
	usb_init();
}

void Port_uart_swap()
{
	info_print("Interconnect Line Swap");

	// PTA13 - UART Swap
#if defined(_kinetis_)
	GPIOA_PTOR |= (1<<UART_SWAP_PIN);
#elif defined(_sam_)
	if (PIOA->ODSR & (1<<UART_SWAP_PIN)) {
		PIOA->CODR = (1<<UART_SWAP_PIN);
	} else {
		PIOA->SODR = (1<<UART_SWAP_PIN);
	}
#endif
}

void Port_cross()
{
	info_print("Interconnect Line Cross");

	// PTA12 - UART Tx/Rx cross-over
#if defined(_kinetis_)
	GPIOA_PTOR |= (1<<UART_TXRX_PIN);
#elif defined(_sam_)
	if (PIOA->ODSR & (1<<UART_TXRX_PIN)) {
		PIOA->CODR = (1<<UART_TXRX_PIN);
	} else {
		PIOA->SODR = (1<<UART_TXRX_PIN);
	}
#endif

	// Reset interconnects
	Connect_reset();
}

// Setup
inline void Port_setup()
{
	// Register Scan CLI dictionary
	CLI_registerDictionary( portCLIDict, portCLIDictName );

	// PTA4 - USB Swap
	// Start, disabled
#if defined(_kinetis_)
	GPIOA_PDDR |= (1<<USB_SWAP_PIN);
	PORTA_PCR4 = PORT_PCR_SRE | PORT_PCR_DSE | PORT_PCR_MUX(1);
	GPIOA_PCOR |= (1<<USB_SWAP_PIN);
#elif defined(_sam_)
	PIOA->PIO_OER = (1<<USB_SWAP_PIN);
	PIOA->PIO_CODR = (1<<USB_SWAP_PIN);
#endif

	// PTA12 - UART Tx/Rx cross-over
	// Start, disabled
#if defined(_kinetis_)
	GPIOA_PDDR |= (1<<UART_TXRX_PIN);
	PORTA_PCR12 = PORT_PCR_SRE | PORT_PCR_DSE | PORT_PCR_MUX(1);
	GPIOA_PCOR |= (1<<UART_TXRX_PIN);
#elif defined(_sam_)
	PIOA->PIO_OER = (1<<UART_TXRX_PIN);
	PIOA->PIO_CODR = (1<<UART_TXRX_PIN);
#endif

	// PTA13 - UART Swap
	// Start, disabled
#if defined(_kinetis_)
	GPIOA_PDDR |= (1<<UART_SWAP_PIN);
	PORTA_PCR13 = PORT_PCR_SRE | PORT_PCR_DSE | PORT_PCR_MUX(1);
	GPIOA_PCOR |= (1<<UART_SWAP_PIN);
#elif defined(_sam_)
	PIOA->PIO_OER = (1<<UART_SWAP_PIN);
	PIOA->PIO_CODR = (1<<UART_SWAP_PIN);
#endif

	// Starting point for automatic port swapping
	Port_lastcheck_ms = systick_millis_count;

	// Allocate latency measurement resource
	portLatencyResource = Latency_add_resource("PortSwap", LatencyOption_Ticks);
}

// Port State processing loop
inline uint8_t Port_scan()
{
	// Latency measurement start
	Latency_start_time( portLatencyResource );

	// TODO Add in interconnect line cross

	#define USBPortSwapDelay_ms 1000
	// Wait 1000 ms before checking
	// Only check for swapping after delay
	uint32_t wait_ms = systick_millis_count - Port_lastcheck_ms;
	if ( wait_ms > USBPortSwapDelay_ms )
	{
		// Update timeout
		Port_lastcheck_ms = systick_millis_count;

		// USB not initialized, attempt to swap
		if ( !usb_configured() )
		{
			Port_usb_swap();
		}
	}

	// Latency measurement end
	Latency_end_time( portLatencyResource );

	return 0;
}



// ----- Capabilities -----

void Port_uart_capability( TriggerMacro *trigger, uint8_t state, uint8_t stateType, uint8_t *args )
{
	CapabilityState cstate = KLL_CapabilityState( state, stateType );

	switch ( cstate )
	{
	case CapabilityState_Last:
		// Only use capability on release
		break;
	case CapabilityState_Debug:
		// Display capability name
		print("Port_uart_capability()");
		return;
	default:
		return;
	}

	Port_uart_swap();
}

void Port_usb_capability( TriggerMacro *trigger, uint8_t state, uint8_t stateType, uint8_t *args )
{
	CapabilityState cstate = KLL_CapabilityState( state, stateType );

	switch ( cstate )
	{
	case CapabilityState_Last:
		// Only use capability on release
		break;
	case CapabilityState_Debug:
		// Display capability name
		print("Port_usb_capability()");
		return;
	default:
		return;
	}

	Port_usb_swap();
}

void Port_cross_capability( TriggerMacro *trigger, uint8_t state, uint8_t stateType, uint8_t *args )
{
	CapabilityState cstate = KLL_CapabilityState( state, stateType );

	switch ( cstate )
	{
	case CapabilityState_Last:
		// Only use capability on release
		break;
	case CapabilityState_Debug:
		// Display capability name
		print("Port_cross_capability()");
		return;
	default:
		return;
	}

	Port_cross();
}



// ----- CLI Command Functions -----

void cliFunc_portUART( char* args )
{
	print( NL );
	Port_uart_swap();
}

void cliFunc_portUSB( char* args )
{
	print( NL );
	Port_usb_swap();
}

void cliFunc_portCross( char* args )
{
	print( NL );
	Port_cross();
}

