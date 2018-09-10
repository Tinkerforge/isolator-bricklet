using System;
using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "XYZ"; // Change XYZ to the UID of your Isolator Bricklet

	static void Main()
	{
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletIsolator i = new BrickletIsolator(UID, ipcon); // Create device object

		ipcon.Connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Get current statistics
		long messagesFromBrick, messagesFromBricklet;
		     int connectedBrickletDeviceIdentifier; string connectedBrickletUID;
		i.GetStatistics(out messagesFromBrick, out messagesFromBricklet,
		                out connectedBrickletDeviceIdentifier, out connectedBrickletUID);

		Console.WriteLine("Messages From Brick: " + messagesFromBrick);
		Console.WriteLine("Messages From Bricklet: " + messagesFromBricklet);
		Console.WriteLine("Connected Bricklet Device Identifier: " + connectedBrickletDeviceIdentifier);
		Console.WriteLine("Connected Bricklet UID: " + connectedBrickletUID);

		Console.WriteLine("Press enter to exit");
		Console.ReadLine();
		ipcon.Disconnect();
	}
}
