/*
 * 0-sos.cpp -- morse code SOS
 *
 * Using the built-in LED of the Pico W, blink SOS in Morse Code.
 * Short pulses should be 400ms while long pulses should be 800ms.
 */

#include "rcc_stdlib.h"
using namespace std; 

int main(void)
{
  /*Initialize stdio and cyw43!
    Remember for the PicoW the onboard LED requires initializing the wireless 
    module!
  */
  stdio_init_all();
  if(cyw43_arch_init()) { cout << "CYW43 init failed!" << "\n"; }
  cyw43_arch_gpio_put(0, 1);

  // blink SOS here (in a loop)!
}