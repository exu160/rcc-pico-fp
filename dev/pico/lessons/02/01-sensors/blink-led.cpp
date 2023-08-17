#include "rcc_stdlib.h"
using namespace std;

void blink_led(int time) { 
    cyw43_arch_gpio_put(0, !cyw43_arch_gpio_get(0));
    sleep_ms(time);
}

int main() { 
    stdio_init_all();
    if(cyw43_arch_init()) { cout << "CYW43 init failed!" << "\n"; }
    cyw43_arch_gpio_put(0, 1);

    while(true) {
        blink_led(400);
    }
}