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
    
    while(true) {
        int left_count = left.getCount();
        int right_count = right.getCount();

        cout << left_count << " | " << right_count << "\n";
        sleep_ms(100);

        //360 rotation: ~130
        //90 rotation: ~30

        if(!gpio_get(RCC_PUSHBUTTON)) {
            MotorPower(&motors, 0, 50); 
        }

        if(right_count >= 130){
            MotorPower(&motors, 0, 0);
        }
    }
}