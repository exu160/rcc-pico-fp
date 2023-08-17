#include "rcc_stdlib.h"
using namespace std;

int main() {
    stdio_init_all();
    if(cyw43_arch_init()) { cout << "CYW43 failed!" << "\n"; }
    cyw43_arch_gpio_put(0, 1);

    gpio_init(0);
    gpio_set_dir(0, true);

    while(true) { 
        sleep_ms(500);
        gpio_put(0, 1);
        sleep_ms(500);
        gpio_put(0, 0);
    }
}