    #include "rcc_stdlib.h"
    using namespace std;
    
    #define WHEEL_RADIUS 0.04 //meters
    #define COUNTS_PER_ROTATION 40 

    int distanceToCounts(float distance){
    float rotations = distance / (2*3.14 * WHEEL_RADIUS);
    float fcounts = rotations * COUNTS_PER_ROTATION;
    int counts = int(fcounts);
    return counts;
    }
    
    //setup instance of config struct
    PID_control_config_t config;
    
    int main(){
        stdio_init_all();
        cyw43_arch_init();
        sleep_ms(1500);
    
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
        int base_power = 75;
        int output; 
    
        //timing variables setup
        uint32_t current_time, previous_time;
        current_time = time_us_32();
        
        //pico led on when done setup
        cyw43_arch_gpio_put(0,1); 
    
        while(true){
            //update current time
            current_time = time_us_32();
            int left_count = left.getCount();
            int right_count = right.getCount();
            int dist = distanceToCounts(1);
    
            //if config's timestep has passed
            if((current_time - previous_time) >= config.ts*1e6){
    
                //get data from sensors
                imu.update_pico();
                //calculate controller output:
                    //first input is desired value
                    //second input is actual value
                output = controller.pid(0.0, imu.getAngVelZ());
    
                //set motor power based on controller output
                MotorPower(&motors, (base_power-output), (base_power+output));

                //reset previous time
                previous_time = current_time;
            }

            if((left_count >= dist) && (right_count >= dist)) {
                MotorPower(&motors, 0, 0);
            }
        }
    }