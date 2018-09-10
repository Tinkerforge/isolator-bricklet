import com.tinkerforge.IPConnection;
import com.tinkerforge.BrickletIsolator;
import com.tinkerforge.BrickletIsolator.Statistics;

public class ExampleSimple {
	private static final String HOST = "localhost";
	private static final int PORT = 4223;

	// Change XYZ to the UID of your Isolator Bricklet
	private static final String UID = "XYZ";

	// Note: To make the example code cleaner we do not handle exceptions. Exceptions
	//       you might normally want to catch are described in the documentation
	public static void main(String args[]) throws Exception {
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletIsolator i = new BrickletIsolator(UID, ipcon); // Create device object

		ipcon.connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Get current statistics
		Statistics statistics = i.getStatistics(); // Can throw com.tinkerforge.TimeoutException

		System.out.println("Messages From Brick: " + statistics.messagesFromBrick);
		System.out.println("Messages From Bricklet: " + statistics.messagesFromBricklet);
		System.out.println("Connected Bricklet Device Identifier: " + statistics.connectedBrickletDeviceIdentifier);
		System.out.println("Connected Bricklet UID: " + statistics.connectedBrickletUID);

		System.out.println("Press key to exit"); System.in.read();
		ipcon.disconnect();
	}
}
