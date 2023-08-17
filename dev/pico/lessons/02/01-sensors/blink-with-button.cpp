#include "rcc_stdlib.h"
using namespace std;

void blink_led(int speed) { 
    cyw43_arch_gpio_put(0, !cyw43_arch_gpio_get(0));
    sleep_ms(speed);
}

int main() { 
    stdio_init_all();
    if(cyw43_arch_init()) { cout << "CYW43 init failed!" << "\n"; }
    cyw43_arch_gpio_put(0, 1);
    rcc_init_pushbutton();

    while(true) {
        if(!gpio_get(RCC_PUSHBUTTON)) {
            blink_led(400);
        }
    } 
} 
