#include "rcc_stdlib.h"
using namespace std;

typedef enum{
    WAIT, 
    FORWARD,
    BACKWARD
} state_t;

void print_state(state_t state) {
    cout << state << "\n";
}

int main() {
    stdio_init_all();
    if(cyw43_arch_init()) { cout << "CYW43 failed!" << "\n"; }
    cyw43_arch_gpio_put(0, 1);

    Motor motors;
    MotorInit(&motors, RCC_ENA, RCC_ENB, 1000);
    MotorsOn(&motors);

    rcc_init_i2c();
    VL53L0X lidar;
    rcc_init_lidar(&lidar);

    int goal_dist = 20;
    int tolerance = 5;

    state_t my_state = WAIT;

    while(true) {
        uint16_t dist = getFastReading(&lidar);
        switch(my_state) {
            case WAIT: 
                print_state(my_state);
                MotorPower(&motors, 0, 0);
                if(dist >= (goal_dist + tolerance)) {
                    my_state = FORWARD;
                }
                if(dist <= (goal_dist - tolerance)) {
                    my_state = BACKWARD;
                }
                break;
            case FORWARD:
                print_state(my_state);
                MotorPower(&motors, 47, 50);
                if(dist <= (goal_dist + tolerance)){ 
                    my_state = WAIT;
                }
                break;
            case BACKWARD:
                print_state(my_state);
                MotorPower(&motors, -47, -50);
                if(dist >= (goal_dist - tolerance)){ 
                    my_state = WAIT;
                }
                break;
        }
    }
}