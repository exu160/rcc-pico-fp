#include "rcc_stdlib.h"
using namespace std;

int main() { 
    stdio_init_all();
    if(cyw43_arch_init()) { cout << "CYW43 init failed!" << "\n"; }
    cyw43_arch_gpio_put(0, 1);
    rcc_init_pushbutton();

    Servo s3; 
    ServoInit(&s3, 18, false, 50); 
    ServoOn(&s3); 

    int servo = 0;

    while(true) {
        if(!gpio_get(RCC_PUSHBUTTON)) {
            servo += 10;
            ServoPosition(&s3, servo); 
            sleep_ms(400);
        }
    }

}