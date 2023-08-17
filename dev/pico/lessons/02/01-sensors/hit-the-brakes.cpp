#include "rcc_stdlib.h"
using namespace std;

int main() { 
    stdio_init_all();
    if(cyw43_arch_init()) { cout << "CYW43 failed!" << "\n"; }
    cyw43_arch_gpio_put(0, 1);
    rcc_init_pushbutton();

    Motor motors;
    MotorInit(&motors, RCC_ENA, RCC_ENB, 1000);
    MotorsOn(&motors);

    Servo s3;
    ServoInit(&s3, 18, false, 50);
    ServoOn(&s3);
    
    rcc_init_i2c();
    VL53L0X lidar;
    rcc_init_lidar(&lidar);

    while(true) {
        uint16_t dist = getFastReading(&lidar);
        cout << dist << "\n";
        
        if(!gpio_get(RCC_PUSHBUTTON)) {
            ServoPosition(&s3, 50);
            MotorPower(&motors, 47, 50);
        }

        if (dist <= 200) {
            MotorPower(&motors, 0, 0);
        }
    }

}