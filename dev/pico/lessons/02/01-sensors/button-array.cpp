#include "rcc_stdlib.h"
using namespace std;

int main() { 
    stdio_init_all();
    if(cyw43_arch_init()) { cout << "CYW43 init failed!" << "\n"; }
    cyw43_arch_gpio_put(0, 1);
    rcc_init_pushbutton();

    int array[100];
    for (int i = 0; i < 100; i++) { 
        array[i] = i;
    }

    int i = 0; 

    while(true) {
        if(!gpio_get(RCC_PUSHBUTTON)) {
            cout << "i = " << array[i] << "\n"; 
            i++; 
        }
    }
}