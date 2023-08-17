#include "rcc_stdlib.h"
using namespace std;

typedef enum{
    WAIT,
    DETECT,
    RIGHT,
    LEFT, 
    FOUND
} state_t;

void blink_led(int time) { 
    cyw43_arch_gpio_put(0, !cyw43_arch_gpio_get(0));
    sleep_ms(time);
}

int main() {
    stdio_init_all();
    if(cyw43_arch_init()) { cout << "CYW43 failed!" << "\n"; }
    cyw43_arch_gpio_put(0, 1);
    rcc_init_pushbutton();

    Motor motors;
    MotorInit(&motors, RCC_ENA, RCC_ENB, 1000);
    MotorsOn(&motors);

    rcc_init_i2c();
    VL53L0X lidar;
    rcc_init_lidar(&lidar);

    Servo s3;
    ServoInit(&s3, 18, false, 50);
    ServoOn(&s3);

    uint32_t prev_time;
    uint32_t cur_time;
    int wait = 10000;
    
    state_t my_state = WAIT; 

    while(true) {
        uint16_t dist = getFastReading(&lidar);
        cout << dist << "\n";

        switch(my_state) {
            case WAIT: 
                MotorPower(&motors, 0, 0);
                ServoPosition(&s3, 50);
                blink_led(300);
                if(!gpio_get(RCC_PUSHBUTTON)) {
                    my_state = DETECT;
                }
                break;
            case DETECT:
                for(int i = 0; i <= 100; i++) {
                    while(cur_time - prev_time < wait) {
                        cur_time = time_us_32();
                    }
                    prev_time = cur_time;
                    ServoPosition(&s3, i);
                    dist = getFastReading(&lidar);
                    if(dist <= 200) {
                        ServoPosition(&s3, 50);
                        sleep_ms(200);
                        if(i <= 50) {
                            my_state = RIGHT;
                        } else {
                            my_state = LEFT;
                        }
                        break;
                    }
                }
                break;
            case RIGHT: 
                MotorPower(&motors, 75, 0);
                if(dist <= 200) {
                    my_state = FOUND;
                }
                break;
            case LEFT: 
                MotorPower(&motors, 0, 75);
                if(dist <= 200) {
                    my_state = FOUND;
                }
                break;
            case FOUND: 
                MotorPower(&motors, 47, 50);
                if(dist <= 100) {
                    my_state = WAIT;
                }
                break;
        }
    }
}
 