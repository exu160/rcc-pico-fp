#include "rcc_stdlib.h"
using namespace std;

int main() { 
    stdio_init_all();
    if(cyw43_arch_init()) { cout << "CYW43 init failed!" << "\n"; }
    cyw43_arch_gpio_put(0, 1);
    rcc_init_pushbutton();

    Motor motors;
    MotorInit(&motors, RCC_ENA, RCC_ENB, 1000); 
    MotorsOn(&motors); 

    while(true) {
        MotorPower(&motors, 47, 50); 
    }
}
