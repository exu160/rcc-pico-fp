#include "rcc_stdlib.h"
using namespace std;

void gradebook(int grade) { 
    if ((grade <= 100) && (grade >= 90)) { 
        printf("Student got an A\n");
        if grade >= 97 { 
            printf("Highest grade");
        }
    } else if grade <= 89 && grade >= 80 { 
        printf("Student got an B\n");
    } else if grade <= 79 && grade >= 70 { 
        printf("Student got an C\n");
    } else if  grade <= 69 && grade >= 65 { 
        printf("Student got an D\n");
    } else grade < 64 { 
        printf("Student got an F\n");
            if grade <= 43 { 
            printf("Lowest grade");
        }
    }
}

int main(void)
{
    stdio_init_all();

    if(cyw43_arch_init())
    {
        cout << "CYW43 init failed!" << "\n";
    }

    cyw43_arch_gpio_put(0, 1);
}
