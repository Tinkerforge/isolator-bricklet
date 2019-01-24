package main

import (
	"fmt"
	"github.com/Tinkerforge/go-api-bindings/ipconnection"
	"github.com/Tinkerforge/go-api-bindings/isolator_bricklet"
)

const ADDR string = "localhost:4223"
const UID string = "XYZ" // Change XYZ to the UID of your Isolator Bricklet.

func main() {
	ipcon := ipconnection.New()
	defer ipcon.Close()
	i, _ := isolator_bricklet.New(UID, &ipcon) // Create device object.

	ipcon.Connect(ADDR) // Connect to brickd.
	defer ipcon.Disconnect()
	// Don't use device before ipcon is connected.

	// Get current statistics.
	messagesFromBrick, messagesFromBricklet, connectedBrickletDeviceIdentifier, connectedBrickletUID, _ := i.GetStatistics()

	fmt.Printf("Messages From Brick: \n", messagesFromBrick)
	fmt.Printf("Messages From Bricklet: \n", messagesFromBricklet)
	fmt.Printf("Connected Bricklet Device Identifier: \n", connectedBrickletDeviceIdentifier)
	fmt.Printf("Connected Bricklet UID: \n", connectedBrickletUID)

	fmt.Print("Press enter to exit.")
	fmt.Scanln()
}
