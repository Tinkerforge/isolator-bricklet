function octave_example_simple()
    more off;

    HOST = "localhost";
    PORT = 4223;
    UID = "XYZ"; % Change XYZ to the UID of your Isolator Bricklet

    ipcon = javaObject("com.tinkerforge.IPConnection"); % Create IP connection
    i = javaObject("com.tinkerforge.BrickletIsolator", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Get current statistics
    statistics = i.getStatistics();

    fprintf("Messages From Brick: %d\n", java2int(statistics.messagesFromBrick));
    fprintf("Messages From Bricklet: %d\n", java2int(statistics.messagesFromBricklet));
    fprintf("Connected Bricklet Device Identifier: %d\n", statistics.connectedBrickletDeviceIdentifier);
    fprintf("Connected Bricklet UID: %s\n", statistics.connectedBrickletUID);

    input("Press key to exit\n", "s");
    ipcon.disconnect();
end

function int = java2int(value)
    if compare_versions(version(), "3.8", "<=")
        int = value.intValue();
    else
        int = value;
    end
end
