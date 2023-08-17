from pynput import keyboard
from pynput.keyboard import Key 
from comms.controller import WirelessController, WirelessInterface
from comms.messages import Motor_Power, Increase_Power, Turn_90, Lidar_Sweep
# from comms.messages import Increase_Power
# from comms.messages import Turn_90
# from comms.messages import Lidar_Sweep

c = WirelessController(WirelessInterface)
c.start_inbound()
c.start_outbound()

def on_press(key):
    try:
        # print('alphanumeric key {0} pressed'.format(
        #     key.char))
        if key == Key.space: 
            tout = Motor_Power((0, 0))
            pout = tout.pack() 
            c.outbound.put(pout)
        elif key == Key.up:
            tout = Motor_Power((75, 75))
            pout = tout.pack()  
            c.outbound.put(pout)
        elif key == Key.down :
            tout = Motor_Power((10, 0))
            pout = tout.pack()   
            c.outbound.put(pout)
        elif key == Key.left:
            tout = Motor_Power((85, 0))
            pout = tout.pack() 
            c.outbound.put(pout)
        elif key == Key.right: 
            tout = Motor_Power((0, 85))
            pout = tout.pack() 
            c.outbound.put(pout)
        elif key == Key.shift:
            tout = Lidar_Sweep((1,))
            pout = tout.pack() 
            c.outbound.put(pout)
        # elif key == Key.shift_r: 
        #     tout = Lidar_Sweep((0,))
        #     pout = tout.pack() 
        #     c.outbound.put(pout)
        elif key.char == "l":
            tout = Increase_Power((5, 0))
            pout = tout.pack() 
            c.outbound.put(pout)
        elif key.char == "r":
            tout = Increase_Power((0, 5))
            pout = tout.pack() 
            c.outbound.put(pout)
        elif key.char == '9':
            tout = Turn_90((85, 0, 90.0))
            pout = tout.pack() 
            c.outbound.put(pout)
        elif key.char == "0":
            tout = Turn_90((0, 85, 80.0))
            pout = tout.pack() 
            c.outbound.put(pout)
        elif key.char == "8":
            tout = Turn_90((0, 85, 180.0))
            pout = tout.pack() 
            c.outbound.put(pout)
        elif key.char == "3":
            tout = Turn_90((0, 90, 360.0))
            pout = tout.pack() 
            c.outbound.put(pout)
    except AttributeError:
        print('special key {0} pressed'.format(
            key))

def on_release(key):
    print('{0} released'.format(
        key))
    if key == keyboard.Key.esc:
        # Stop listener
        return False

listener = keyboard.Listener(on_press=on_press, on_release=on_release)
listener.start()

while True:
    pass