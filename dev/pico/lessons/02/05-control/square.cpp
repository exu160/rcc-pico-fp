#include "rcc_stdlib.h"
using namespace std;

#define WHEEL_RADIUS 0.04 //meters
#define COUNTS_PER_ROTATION 40 

typedef enum{
    WAIT,
    FORWARD,
    TURN
} state_t;

int distanceToCounts(float distance){
    float rotations = distance / (2*3.14 * WHEEL_RADIUS);
    float fcounts = rotations * COUNTS_PER_ROTATION;
    int counts = int(fcounts);
    return counts;
}

PID_control_config_t config;

int main() {
    stdio_init_all();
        cyw43_arch_init();
        rcc_init_pushbutton();
    
        //init i2c first
        rcc_init_i2c(); 
        MPU6050 imu;
        imu.begin(i2c1);
        imu.calibrate();
    
        Motor motors;
        MotorInit(&motors, RCC_ENA, RCC_ENB, 20000);
        MotorsOn(&motors);

        Left_Odom left; 
        Right_Odom right; 
    
        //set values for config
        config.kp = 0.8; //0.9 and 0.15
        config.ki = 0.15;
        config.kd = 0;
        config.ts = 0.01; // 10ms
        config.sigma = 0.1;
        config.lowerLimit = -50;
        config.upperLimit = 50;
        config.antiWindupEnabled = true;
    
        //create controller class based on config
        PID_control controller(config);
    
        //motor power variables setup
        int base_power = 80;
        int output; 
        float angle = 0;
        
        state_t my_state = WAIT;

        //timing variables setup
        uint32_t current_time, previous_time;
        current_time = time_us_32();
    
        //pico led on when done setup
        cyw43_arch_gpio_put(0,1); 
    
    while(true) {
        current_time = time_us_32();
        int dist = distanceToCounts(1);

        switch(my_state) {
            case WAIT: 
                if(!gpio_get(RCC_PUSHBUTTON)) {
                    my_state = FORWARD;
                    break;
                }
                break;
            case FORWARD:
                if((current_time - previous_time) >= config.ts*1e6){
                        imu.update_pico();
                        output = controller.pid(0.0, imu.getAngVelZ());
                        MotorPower(&motors, (base_power-output), (base_power+output));
                        previous_time = current_time;
                }
                
                if ((left.getCount() >= dist) && (right.getCount() >= dist)) { 
                    MotorPower(&motors, 0, 0);
                    my_state = TURN;
                }
                break;

            case TURN: 
                if((current_time - previous_time) >= config.ts*1e6){
                        imu.update_pico();
                        angle += imu.getAngVelZ()*config.ts; // deg/sec * sec
                        output = controller.pid(75.0, angle);
                        MotorPower(&motors, (base_power-output), (base_power+output));
                        previous_time = current_time;
                    }

                    if(angle >= 75.0) { 
                        MotorPower(&motors, 0, 0);
                        left.setZero();
                        right.setZero();
                        my_state = FORWARD;
                    }
                    angle = 0;
                break;
        }
    }
}