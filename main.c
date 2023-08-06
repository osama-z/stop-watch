#include <LPC11xx.h>
#include "lcd_lib.h"
#include <stdio.h>

#define START_BUTTON_PIN 5
#define STOP_BUTTON_PIN 4
#define LED_PIN 3

int pf_seconds = 0;
int seconds = 0;
int minutes = 0;
int isRunning = 0;

void TIMER16_0_IRQHandler(void) {
	if (LPC_TMR16B0->IR & 0x1) { // Check if the event is on MR0
	LPC_GPIO0->DATA |= (1 << LED_PIN); // Turn on the LED
		if (isRunning) {
		pf_seconds++; // Increment partial seconds
			if (pf_seconds == 100) {
				seconds++; // Increment seconds
				pf_seconds = 0; // Reset partial seconds
				if (seconds == 60) {
				minutes++; // Increment minutes
				seconds = 0; // Reset seconds
					if (minutes == 60) {
					minutes = 0; // Reset minutes
					}
				}
			}
		}
	LPC_TMR16B0->IR = 0x1; // Reset interrupt flag on MR0
	}
}

int main(void) {
    LPC_GPIO0->DIR |= 0b001110;
    
    LPC_GPIO0->DATA &= ~(1 << LED_PIN);   // Turn off the LED initially

    // Enable output for display data
    LPC_GPIO2->DIR |= 0xFF;

    setup_lcd(); // Initialize the LCD display
    clear_screen();

    // Enable clock for TIMER16B0
    LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 7);

    // Configure TIMER16B0
    LPC_TMR16B0->PR = 12000 - 1;  	// Set Prescaler as 12000-1
    LPC_TMR16B0->MCR = 0x3;       	// Enable Interrupt and Reset on MR0
    LPC_TMR16B0->MR0 = 10;        	// Set MR0 to 10 (10 milliseconds)
    NVIC_EnableIRQ(TIMER_16_0_IRQn); 	// Enable TIMER16B0 interrupt
    LPC_TMR16B0->TCR = 0x3; 		// Enable and Reset the timer
    LPC_TMR16B0->TCR = 0x1; 		// Unreset timer

    while (1) {
        // Check if the start button is pressed
        if ((LPC_GPIO0->DATA & (1 << START_BUTTON_PIN))) {
	
            isRunning = 1;
            pf_seconds = 0;
            seconds = 0;
            minutes = 0;
	    
            clear_screen();
            send_string("Running..");
        }

        // Check if the stop button is pressed
        if ((LPC_GPIO0->DATA & (1 << STOP_BUTTON_PIN))) {
	
            isRunning = 0;
            LPC_GPIO0->DATA &= ~(1 << LED_PIN); // Turn off the LED
            clear_screen();
            char buffer[17];
            sprintf(buffer, "%02d:%02d:%02d S", minutes, seconds, pf_seconds);
            send_string(buffer);
        }
    }
    return 0;
}
