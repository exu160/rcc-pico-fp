    #include "rcc_stdlib.h"
    using namespace std;
    
    typedef enum{
        WAIT,
        FWD50, 
        TURN90,
        FWD100
    } state_t;

    //setup instance of config struct
    PID_control_config_t config;
    
    int main(){
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
        config.kp = 0.7; 
        config.ki = 0.07;
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
    
        while(true){
            current_time = time_us_32();
            int left_count = left.getCount();
            int right_count = right.getCount();

            switch(my_state) { 
                case WAIT: 
                    MotorPower(&motors, 0, 0);
                    if(!gpio_get(RCC_PUSHBUTTON)) {
                        my_state = FWD50;
                        break;
                    }
                    break;
                case FWD50: 
                    if((current_time - previous_time) >= config.ts*1e6){
                        imu.update_pico();
                        output = controller.pid(0.0, imu.getAngVelZ());
                        MotorPower(&motors, (base_power-output), (base_power+output));
                        previous_time = current_time;
                    }

                    if((left_count >= 50) && (right_count >= 50)) {
                        my_state = TURN90;
                        break;
                    }
                    break;
                case TURN90:    
                    if((current_time - previous_time) >= config.ts*1e6){
                        imu.update_pico();
                        angle += imu.getAngVelZ()*config.ts; // deg/sec * sec
                        output = controller.pid(-77.0, angle);
                        MotorPower(&motors, (base_power-output), (base_power+output));
                        previous_time = current_time;
                    }

                    if(angle <= -77.0) { 
                        my_state = FWD100;
                        left.setZero();
                        right.setZero();
                        break;
                    }
                    break;
                case FWD100: 
                    if((current_time - previous_time) >= config.ts*1e6){
                        imu.update_pico();
                        output = controller.pid(0.0, imu.getAngVelZ());
                        MotorPower(&motors, (base_power-output), (base_power+output));
                        previous_time = current_time;
                    }

                    if((left_count >= 100) && (right_count >= 100)) {
                        my_state = WAIT;
                        break;
                    }
                    break;
            }
        }
    }