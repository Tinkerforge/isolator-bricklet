<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickletIsolator.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickletIsolator;

const HOST = 'localhost';
const PORT = 4223;
const UID = 'XYZ'; // Change XYZ to the UID of your Isolator Bricklet

$ipcon = new IPConnection(); // Create IP connection
$i = new BrickletIsolator(UID, $ipcon); // Create device object

$ipcon->connect(HOST, PORT); // Connect to brickd
// Don't use device before ipcon is connected

// Get current statistics
$statistics = $i->getStatistics();

echo "Messages From Brick: " . $statistics['messages_from_brick'] . "\n";
echo "Messages From Bricklet: " . $statistics['messages_from_bricklet'] . "\n";
echo "Connected Bricklet Device Identifier: " . $statistics['connected_bricklet_device_identifier'] . "\n";
echo "Connected Bricklet UID: " . $statistics['connected_bricklet_uid'] . "\n";

echo "Press key to exit\n";
fgetc(fopen('php://stdin', 'r'));
$ipcon->disconnect();

?>
