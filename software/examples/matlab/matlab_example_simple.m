function matlab_example_simple()
    import com.tinkerforge.IPConnection;
    import com.tinkerforge.BrickletIsolator;

    HOST = 'localhost';
    PORT = 4223;
    UID = 'XYZ'; % Change XYZ to the UID of your Isolator Bricklet

    ipcon = IPConnection(); % Create IP connection
    i = handle(BrickletIsolator(UID, ipcon), 'CallbackProperties'); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Get current statistics
    statistics = i.getStatistics();

    fprintf('Messages From Brick: %i\n', statistics.messagesFromBrick);
    fprintf('Messages From Bricklet: %i\n', statistics.messagesFromBricklet);
    fprintf('Connected Bricklet Device Identifier: %i\n', statistics.connectedBrickletDeviceIdentifier);
    fprintf('Connected Bricklet UID: %s\n', char(statistics.connectedBrickletUID));

    input('Press key to exit\n', 's');
    ipcon.disconnect();
end
