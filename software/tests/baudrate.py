# -*- coding: utf-8 -*-

HOST = "localhost"
PORT = 4223
UID = "iso1"

from tinkerforge.ip_connection import IPConnection
from tinkerforge.bricklet_isolator import BrickletIsolator
import time

if __name__ == "__main__":
    ipcon = IPConnection() # Create IP connection
    isolator = BrickletIsolator(UID, ipcon) # Create device object

    ipcon.connect(HOST, PORT) # Connect to brickd
    # Don't use device before ipcon is connected

    isolator.set_spitfp_baudrate_config(False, 400000)
    isolator.set_spitfp_baudrate(2000000)
    print(isolator.get_isolator_spitfp_error_count())

    raw_input("Press key to exit\n") # Use input() in Python 3
    ipcon.disconnect()
