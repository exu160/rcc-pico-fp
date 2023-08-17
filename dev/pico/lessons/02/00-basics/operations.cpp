#include "rcc_stdlib.h"
using namespace std;

int subtraction(int x, int y) {
    int sub = x-y;
    return sub; 
}

int multiply(int x, int y) {
    int product = x*y;
    return product;
}

int division(int x, int y) {
    int quotient = x/y;
    return quotient;
}

int main(void)
{
    stdio_init_all();

    if(cyw43_arch_init())
    {
        cout << "CYW43 init failed!" << "\n";
    }

    cyw43_arch_gpio_put(0, 1);
    
    int x = 10;
    int y = 5;
    int sub = subtraction(x, y);

    int a = 2;
    int b = 4;
    int product = multiply(a, b);

    int c = 12;
    int d = 2;
    int quotient = division(c, d);

    while(true) {
        printf("%d\n", sub);
        printf("%d\n", product);
        printf("%d\n", quotient);
        sleep_ms(100);
    }
}



