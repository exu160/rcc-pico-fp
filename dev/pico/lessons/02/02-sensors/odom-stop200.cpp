#include "rcc_stdlib.h"
using namespace std;

#define WHEEL_RADIUS 0.04 //meters
#define COUNTS_PER_ROTATION 40 

int distanceToCounts(float distance){
    float rotations = distance / (2*3.14 * WHEEL_RADIUS);
    float fcounts = rotations * COUNTS_PER_ROTATION;
    int counts = int(fcounts);
    return counts;
}

int main() { 
    stdio_init_all();
    if(cyw43_arch_init()) { cout << "CYW43 init failed!" << "\n"; }
    cyw43_arch_gpio_put(0, 1);
    rcc_init_pushbutton();

    Motor motors;
    MotorInit(&motors, RCC_ENA, RCC_ENB, 1000); 
    MotorsOn(&motors); 

    Left_Odom left; 
    Right_Odom right; 
    
    while(true) {
        int left_count = left.getCount();
        int right_count = right.getCount();
        int m = distanceToCounts(1);

        if(!gpio_get(RCC_PUSHBUTTON)) {
            MotorPower(&motors, 47, 50);
        } 

        if ((left_count >= m) && (right_count >= m)) { 
            MotorPower(&motors, 0, 0);
        }
    }
}