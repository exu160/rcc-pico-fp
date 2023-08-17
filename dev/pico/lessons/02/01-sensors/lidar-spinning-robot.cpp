#include "rcc_stdlib.h"
using namespace std; 

void blink_led(int time) { 
    cyw43_arch_gpio_put(0, !cyw43_arch_gpio_get(0));
    sleep_ms(time);
}

int main() {
    stdio_init_all();
    if(cyw43_arch_init()) { cout << "CYW43 failed!" << "\n"; }
    cyw43_arch_gpio_put(0, 1);
    rcc_init_pushbutton();
    rcc_init_i2c();
    
    Motor motors;
    MotorInit(&motors, RCC_ENA, RCC_ENB, 1000);
    MotorsOn(&motors);

    VL53L0X lidar;
    rcc_init_lidar(&lidar);

    bool blink = false;

    while(true) {
        uint16_t dist = getFastReading(&lidar); 
    
        if(!gpio_get(RCC_PUSHBUTTON)) {
            MotorPower(&motors, 50, 0);  
        }
        
        if (dist <= 200) {
            MotorPower(&motors, 0, 0); 
            blink = true;
        }

        if (blink) {
            blink_led(400);
        }
    }
    
}