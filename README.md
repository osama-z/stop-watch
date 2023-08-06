# stop-watch
stop watch in Proteus 8 
# Conclusion
The provided code demonstrates the implementation of a timer-based application 
using an ARM Cortex-M microcontroller. It utilizes interrupts and GPIO to 
monitor button presses and updates the LCD display with the


# Header Files and Definitions:
• The necessary header files are included, such as "LPC11xx.h" for 
   microcontroller register definitions, "lcd_lib.h" for the LCD library, and 
  "stdio.h" for standard input/output operations , “ _sbrk” function is a 
   minimal implementation of dynamic memory allocation.
   Pin numbers for the start button, stop button, and LED are defined using 
   define directives.
# Variable Declarations:
   The code declares various variables used in the program:
   pf_seconds: Represents the partial seconds, incremented every 
   millisecond.
   seconds: Represents the seconds count.
   minutes: Represents the minutes count.
   isRunning: Tracks the state of the timer (running or stopped).
# Interrupt Handler:
  The code defines an interrupt handler function TIMER16_0_IRQHandler to 
  handle the Timer16B0 interrupt. Inside the interrupt handler, the code checks if the interrupt event 
  occurred on Match Register 0 (MR0). If the timer is running, it increments the partial seconds (pf_seconds), 
  checks for rollover to seconds and minutes, and resets the appropriate counters.

# Main Function:
  The main function initializes the necessary configurations and enters an infinite loop for the main program execution.
  The direction of the GPIO pins is configured, with LED pin set as an output.
  The LCD display is initialized using the setup_lcd() function, and the screen  is cleared.
  The clock and configuration for Timer16B0 are set up. Timer prescaler (PR), match control register (MCR), match register (MR0), and interrupts are  configured.
  The Timer16B0 interrupt is enabled using NVIC_EnableIRQ.
  The timer is enabled and reset.Inside the infinite loop:
  The program checks if the start button is pressed. If true, it starts the timer, resets the time counters, turns on the LED, and displays "Running.." on the LCD.
  The program checks if the stop button is pressed. If true, it stops the timer, turns off the LED, and displays the elapsed time on the LCD in the format "mm:ss:pp S" (minutes:seconds:partial seconds S).Note: sprintf is used to format the elapsed time string into a character buffer.
