#!/usr/bin/env ruby
# -*- ruby encoding: utf-8 -*-

require 'tinkerforge/ip_connection'
require 'tinkerforge/bricklet_isolator'

include Tinkerforge

HOST = 'localhost'
PORT = 4223
UID = 'XYZ' # Change XYZ to the UID of your Isolator Bricklet

ipcon = IPConnection.new # Create IP connection
i = BrickletIsolator.new UID, ipcon # Create device object

ipcon.connect HOST, PORT # Connect to brickd
# Don't use device before ipcon is connected

# Get current statistics as [messages_from_brick, messages_from_bricklet,
#                            connected_bricklet_device_identifier, connected_bricklet_uid]
statistics = i.get_statistics

puts "Messages From Brick: #{statistics[0]}"
puts "Messages From Bricklet: #{statistics[1]}"
puts "Connected Bricklet Device Identifier: #{statistics[2]}"
puts "Connected Bricklet UID: #{statistics[3]}"

puts 'Press key to exit'
$stdin.gets
ipcon.disconnect
