#include "rcc_stdlib.h"
using namespace std;

typedef enum{
    ON,
    OFF
} state_t;

int main() {
    stdio_init_all();
    if(cyw43_arch_init()) { cout << "CYW43 failed!" << "\n"; }
    cyw43_arch_gpio_put(0, 1);

    int64_t current_time = time_us_64(); 
    int64_t previous_time = time_us_64(); 

    state_t my_state = OFF;

    while(true) { 
        current_time = time_us_64();
        switch(my_state) {
            case ON:
                cyw43_arch_gpio_put(0, 1);
                if (current_time - previous_time >= 400000) { 
                    my_state == OFF;
                    previous_time = current_time;
                }
                break;
            case OFF:
                cyw43_arch_gpio_put(0, 0);
                if (current_time - previous_time >= 400000) { 
                    my_state == ON;
                    previous_time = current_time;
                }
                break;
        }
    }
}