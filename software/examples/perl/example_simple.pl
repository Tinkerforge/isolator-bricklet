#!/usr/bin/perl

use strict;
use Tinkerforge::IPConnection;
use Tinkerforge::BrickletIsolator;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'XYZ'; # Change XYZ to the UID of your Isolator Bricklet

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
my $i = Tinkerforge::BrickletIsolator->new(&UID, $ipcon); # Create device object

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Get current statistics
my ($messages_from_brick, $messages_from_bricklet, $connected_bricklet_device_identifier,
    $connected_bricklet_uid) = $i->get_statistics();

print "Messages From Brick: $messages_from_brick\n";
print "Messages From Bricklet: $messages_from_bricklet\n";
print "Connected Bricklet Device Identifier: $connected_bricklet_device_identifier\n";
print "Connected Bricklet UID: $connected_bricklet_uid\n";

print "Press key to exit\n";
<STDIN>;
$ipcon->disconnect();
