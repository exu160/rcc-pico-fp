#include "rcc_stdlib.h"
using namespace std;

int main() { 
    stdio_init_all();
    cyw43_arch_init();
    cyw43_arch_gpio_put(0, 1);
    rcc_init_pushbutton();

    Motor motors;
    MotorInit(&motors, RCC_ENA, RCC_ENB, 1000);
    MotorsOn(&motors);

    rcc_init_i2c();
    MPU6050 imu;
    imu.begin(i2c1);
    imu.calibrate();

    int base_power = 50;
    float desired = 150.0;
    int power_boost;
    float kp = 1.0;
    float error;
    int tolerance = 5;

    bool control = false;

    while(true) {
        if(!gpio_get(RCC_PUSHBUTTON)) {
            control = true;
        }

        if(control) {
            imu.update_pico();
            float angvel_z = imu.getAngVelZ();

            error = desired - angvel_z;
            power_boost = static_cast<int>(kp*error);

            MotorPower(&motors, 0, (base_power + power_boost));

            if(error > tolerance || error < (-1*tolerance)) {
                cyw43_arch_gpio_put(0, 1);
            } else {
                cyw43_arch_gpio_put(0, 0);
            }

            cout << angvel_z << "\n";
        }
    }
}