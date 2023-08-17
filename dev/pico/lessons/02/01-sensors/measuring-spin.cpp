#include "rcc_stdlib.h"
using namespace std;

int main() {
    stdio_init_all();
    if(cyw43_arch_init) { cout << "CYW43 failed!" << "\n"; }
    cyw43_arch_gpio_put(0, 1);
    rcc_init_pushbutton();

    Motor motors; 
    MotorInit(&motors, RCC_ENA, RCC_ENB, 1000);  
    MotorsOn(&motors); 
    rcc_init_i2c();

    MPU6050 imu; 
    imu.begin(i2c1);
    imu.calibrate();

    while(true) {
        if(!gpio_get(RCC_PUSHBUTTON)) {
            MotorPower(&motors, 0, 100);
        }
        imu.update_pico();
        float angvel_z = imu.getAngVelZ();
        cout << "Angular Velocity: " << angvel_z << "\n";
        sleep_ms(200);
    }
}