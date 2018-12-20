use std::{error::Error, io};

use tinkerforge::{ip_connection::IpConnection, isolator_bricklet::*};

const HOST: &str = "localhost";
const PORT: u16 = 4223;
const UID: &str = "XYZ"; // Change XYZ to the UID of your Isolator Bricklet.

fn main() -> Result<(), Box<dyn Error>> {
    let ipcon = IpConnection::new(); // Create IP connection.
    let i = IsolatorBricklet::new(UID, &ipcon); // Create device object.

    ipcon.connect((HOST, PORT)).recv()??; // Connect to brickd.
                                          // Don't use device before ipcon is connected.

    // Get current statistics.
    let statistics = i.get_statistics().recv()?;

    println!("Messages From Brick: {}", statistics.messages_from_brick);
    println!(
        "Messages From Bricklet: {}",
        statistics.messages_from_bricklet
    );
    println!(
        "Connected Bricklet Device Identifier: {}",
        statistics.connected_bricklet_device_identifier
    );
    println!(
        "Connected Bricklet UID: {}",
        statistics.connected_bricklet_uid
    );

    println!("Press enter to exit.");
    let mut _input = String::new();
    io::stdin().read_line(&mut _input)?;
    ipcon.disconnect();
    Ok(())
}
