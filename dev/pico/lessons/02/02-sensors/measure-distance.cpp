#include "rcc_stdlib.h"
using namespace std;

#define WHEEL_RADIUS 0.04 //meters
#define COUNTS_PER_ROTATION 40 

float countsToDistance(int counts) {
    int rotations = counts / COUNTS_PER_ROTATION;
    float distance = (float)rotations * (2*3.14 * WHEEL_RADIUS);
    return distance;
}

int main() { 
    stdio_init_all();
    if(cyw43_arch_init()) { cout << "CYW43 failed!" << "\n"; }
    cyw43_arch_gpio_put(0, 1);
    rcc_init_pushbutton();

    Motor motors;
    MotorInit(&motors, RCC_ENA, RCC_ENB, 1000);
    MotorsOn(&motors);

    Left_Odom left; 
    Right_Odom right; 

    Servo s3;
    ServoInit(&s3, 18, false, 50);
    ServoOn(&s3);
    
    rcc_init_i2c();
    VL53L0X lidar;
    rcc_init_lidar(&lidar);

    while(true) {
        int left_count = left.getCount();
        int right_count = right.getCount();

        uint16_t dist = getFastReading(&lidar);
        cout << dist << "\n";
        
        if(!gpio_get(RCC_PUSHBUTTON)) {
            ServoPosition(&s3, 50);
            MotorPower(&motors, 47, 50);
        }

        if (dist <= 200) {
            MotorPower(&motors, 0, 0);
        }

        float distance = countsToDistance(left_count);
        cout << "Distance: " << distance;
    }
}