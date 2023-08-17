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

    Left_Odom left; 
    Right_Odom right; 

    int left_count = left.getCount();
    int right_count = right.getCount(); 
    
    float scale_factor = 1.18;

    while(true) {
        if(!gpio_get(RCC_PUSHBUTTON)) {
            MotorPower(&motors, static_cast<int>(scale_factor * 40), 40);
        }
        
        if ((left_count >= 200) && (right_count >= 200)) { 
            MotorPower(&motors, 0, 0);
        }
    } 
}