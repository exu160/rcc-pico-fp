from pynput import keyboard 
from pynput.keyboard import Key 
from comms.messages import Twist
from comms.controller import WirelessController, WirelessInterface

c = WirelessController(WirelessInterface)
c.start_inbound()
c.start_outbound()

def on_press(key):
    try:
        print('alphanumeric key {0} pressed'.format(
            key.char))
        if key.char == "x": 
            t = Twist((3, 0))
            pout = t.pack() 
            c.outbound.put(pout)
        if key.char == "y": 
            t = Twist((0, 0))
            pout = t.pack() 
            c.outbound.put(pout)
    except AttributeError:
        print('special key {0} pren?ssed'.format(
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