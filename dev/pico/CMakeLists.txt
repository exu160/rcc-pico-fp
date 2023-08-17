cmake_minimum_required(VERSION 3.13)
set(CMAKE_C_STANDARD 11) 
set(CMAKE_CXX_STANDARD 17)


set(PICO_BOARD pico_w) # Force pico_w so onboard led and wireless sdk stuff is built
include(pico_sdk_import.cmake)
project(rcc_pico_dev C CXX ASM)
pico_sdk_init()

add_subdirectory(include)
add_subdirectory(../../lib lib)
add_subdirectory(sensors)
add_subdirectory(util)

macro(make_exec exec_name exec_dir)
    add_executable(${exec_name} ${exec_dir})
    
    pico_add_extra_outputs(${exec_name})

    pico_enable_stdio_usb(${exec_name} 1)
    pico_enable_stdio_uart(${exec_name} 0)
    
# For debugging with openocd (comment out above)
    # pico_enable_stdio_usb(${exec_name} 0)
    # pico_enable_stdio_uart(${exec_name} 1)

# Allow hash-library-sha1 to find endian.h which is in include directory
    target_include_directories(serial-packets PUBLIC hash-library-sha1)
    target_include_directories(hash-library-sha1 PUBLIC include)

    target_compile_definitions(${exec_name} PUBLIC
                        # Set WIFI parameters with cmake cmd
                            WIFI_SSID="Quasar"
                            WIFI_PASSWORD="wifi21122113"
                            CYW43_HOST_NAME="EX_PICO_RCC"
                            PICO_IP="192.168.0.106"
                            COMP_IP="192.168.0.209"

                        # Forced values for WIFI params
                            # WIFI_SSID=<"MY_WIFI_ROUTER"
                            # WIFI_PASSWORD="MY_WIFI_ROUTER_PASS"
                            # CYW43_HOST_NAME="NAME_I_WANT MY PICO TO HAVE ON NETWORK"

                        # Pico Sdk
                            PICO_MAX_SHARED_IRQ_HANDLERS=8 #IMPORTANT!! It seems default shared irq is 2, we need more.
                            
                        # Related to wireless capabilities
                            # PICO_CYW43_ARCH_BACKGROUND
    )

    target_include_directories(${exec_name} PUBLIC
                            ${CMAKE_CURRENT_LIST_DIR}
                            ${PICO_SDK_PATH}
                            # wireless/include #TODO: Turn into CMake compatible directory (lib)
                            include
                            
    )

    target_link_libraries(${exec_name}
                            pico_cyw43_arch_lwip_threadsafe_background # For wireless
                            # pico_cyw43_arch_none
                            pico_stdlib
                            hardware_adc
                            hardware_pwm
                            pico_multicore
                            serial-packets
                            hardware_i2c
                            sensors
                            util
    )



endmacro()

# macro template
# make_exec(arg1 arg2)
# arg1 = desired uf2 name
# arg2 = location of cpp file relative to the current /pico directory 

# Test files
# make_exec(wireless tests/wireless_interface_test.cpp)
# make_exec(wireless_background tests/wireless_background_test.cpp)
make_exec(wheadless tests/wireless_headless_test.cpp)
# make_exec(mpu6050_test tests/mpu_6050_test.cpp)
# make_exec(lidar_test tests/lidar_test.cpp)
# make_exec(multi_i2c_test tests/multi_i2c_test.cpp)
# make_exec(multi_i2c_test tests/multi_i2c_test.cpp)
# make_exec(hcsr04_test tests/hcsr04_test.cpp)
# make_exec(odom_test tests/odom_test.cpp)
# make_exec(servo_pot_test tests/servo_pot_test.cpp)
# make_exec(motor_test tests/motor_test.cpp)
# make_exec(frequency_test tests/frequency_test.cpp)
# make_exec(control_test tests/control_test.cpp)
# make_exec(all_sensor_test tests/all_sensor_test.cpp)
# make_exec(vel_control_test tests/vel_control_test.cpp)
# make_exec(conversions challenges/02-functions/1-conversions-sol/1-conversions-sol.cpp)
# make_exec(blink_test tests/blink_test.cpp)

# Lessons

#01
# make_exec(helloworld lessons/01/helloworld.cpp)
# make_exec(debug lessons/01/debug.cpp)
# make_exec(fix_helloworld lessons/01/fix_helloworld.cpp)

#02
# make_exec(operations lessons/02/operations.cpp)
# make_exec(syntax lessons/02/syntax.cpp)
# make_exec(blink-led lessons/02/blink-led.cpp)
# make_exec(blink-with-button lessons/02/blink-with-button.cpp)
# make_exec(button-moves-servo lessons/02/button-moves-servo.cpp)
# make_exec(button-array lessons/02/button-array.cpp)
# make_exec(motor lessons/02/motor.cpp)
# make_exec(odom-stop200 lessons/02/odom-stop200.cpp)
# make_exec(odom-straight-for-200 lessons/02/odom-straight-for-200.cpp)
# make_exec(counts-per-rotation lessons/02/counts-per-rotation.cpp)
# make_exec(rotate-robot lessons/02/rotate-robot.cpp)
# make_exec(lidar-spinning-robot lessons/02/lidar-spinning-robot.cpp)
# make_exec(hit-the-brakes lessons/02/hit-the-brakes.cpp)
# make_exec(blink-led-sm lessons/02/blink-led-sm.cpp)
# make_exec(follow lessons/02/follow.cpp)
# make_exec(printfunction lessons/02/printfunction.cpp)
# make_exec(arc-distance lessons/02/arc-distance.cpp)
# make_exec(target-acquired-sm lessons/02/target-acquired-sm.cpp)
# make_exec(dist-control lessons/02/dist-control.cpp)
# make_exec(control-theory lessons/02/control-theory.cpp)
# make_exec(rgb-led lessons/02/rgb-led.cpp)
# make_exec(travel-200 lessons/02/travel-200.cpp)
# make_exec(travel-1m lessons/02/travel-1m.cpp)
# make_exec(drive-straight lessons/02/05-control/drive-straight.cpp)
# make_exec(path-following lessons/02/05-control/path-following.cpp)
# make_exec(angle-controller lessons/02/05-control/angle-controller.cpp)
# make_exec(square lessons/02/05-control/square.cpp)
