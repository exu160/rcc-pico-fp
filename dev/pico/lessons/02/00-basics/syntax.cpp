// include any libs we need for this program 
#include "rcc_stdlib.h"
using namespace std;

// function declaration 
void compare(int a, int b) { 
    if (a < b) { 
        cout << "a < b\n"; 
    } else if (a > b) { 
        cout << "a > b\n";
    } else if (a == b) { 
        cout << "a = b\n";
    }
}

void compare_led(int a, int b) { 
    if (a < b) { 
        cout << "a < b\n"; 
        cyw43_arch_gpio_put(0,0);
    } else if (a > b) { 
        cout << "a > b\n";
        cyw43_arch_gpio_put(0,1);
    } else if (a == b) { 
        cout << "a = b\n";
    }
}

void print_val_n_times(int val, int n) { 
    int i = 0;
    while(i < n) {
        cout << "val: " << val << "\n"; 
        i = i + 1;
    }
}

// make our main function, entry point into our program 
int main(void) { 
// standard initializations for pico w 
    stdio_init_all();
    if (cyw43_arch_init()) { cout << "CYW43 init failed!" << "\n"; } 
    cyw43_arch_gpio_put(0,1); //turn the LED on
    
    int x_loc = 0;
    int y_loc = 20;

    while(true) {
        cout << "x_loc: " << x_loc << " | ";
        print_val_n_times(x_loc, x_loc);
        x_loc = x_loc + 1;
        sleep_ms(500);
    }
}
