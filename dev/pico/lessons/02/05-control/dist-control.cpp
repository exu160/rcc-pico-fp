#include "rcc_stdlib.h"
using namespace std;

int main() {
    stdio_init_all();
    cyw43_arch_init();
    cyw43_arch_gpio_put(0, 1);
    
    rcc_init_i2c();
    VL53L0X lidar;
    rcc_init_lidar(&lidar);

    Motor motors;
    MotorInit(&motors, RCC_ENA, RCC_ENB, 20000);
    MotorsOn(&motors);
    MotorPower(&motors, 0, 0);

    float desired = 200;
    float actual; 
    float error;
    float kp = 0.1;
    float power;
    uint16_t lidar_reading;

    while(true) {
        //Get the distance from the lidar
        lidar_reading = getFastReading(&lidar);
        //Convert the lidar distance from uint to float
        actual = static_cast<float>(lidar_reading);
        //Calculate the error
        error = desired - actual;
        //Calculate the controller output (kp*error)
        power = kp * error;
        //Saturate the controller output 
        power = max(min(power, 100.f), -100.f);
        //Convert power to an integer
        int power_int = static_cast<int>(-1 * power);
        //Apply the controller output (power) to the motors 
        MotorPower(&motors, power_int, power_int);
        cout << "desired: " << desired << " actual: " << actual << " error: " << error << " power: " << power_int << "\n";
    }
}