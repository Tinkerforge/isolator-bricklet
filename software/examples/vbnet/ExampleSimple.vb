Imports System
Imports Tinkerforge

Module ExampleSimple
    Const HOST As String = "localhost"
    Const PORT As Integer = 4223
    Const UID As String = "XYZ" ' Change XYZ to the UID of your Isolator Bricklet

    Sub Main()
        Dim ipcon As New IPConnection() ' Create IP connection
        Dim i As New BrickletIsolator(UID, ipcon) ' Create device object

        ipcon.Connect(HOST, PORT) ' Connect to brickd
        ' Don't use device before ipcon is connected

        ' Get current statistics
        Dim messagesFromBrick, messagesFromBricklet As Long
        Dim connectedBrickletDeviceIdentifier As Integer
        Dim connectedBrickletUID As String

        i.GetStatistics(messagesFromBrick, messagesFromBricklet, _
                        connectedBrickletDeviceIdentifier, connectedBrickletUID)

        Console.WriteLine("Messages From Brick: " + messagesFromBrick.ToString())
        Console.WriteLine("Messages From Bricklet: " + messagesFromBricklet.ToString())
        Console.WriteLine("Connected Bricklet Device Identifier: " + connectedBrickletDeviceIdentifier.ToString())
        Console.WriteLine("Connected Bricklet UID: " + connectedBrickletUID)

        Console.WriteLine("Press key to exit")
        Console.ReadLine()
        ipcon.Disconnect()
    End Sub
End Module
