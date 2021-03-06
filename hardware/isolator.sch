EESchema Schematic File Version 4
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Bricklet Isolator"
Date "2017-12-11"
Rev "1.0"
Comp "Tinkerforge GmbH"
Comment1 "Licensed under CERN OHL v.1.1"
Comment2 "Copyright (©) 2017, L.Lauer <lukas@tinkerforge.com>"
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L tinkerforge:MAX14850 U2
U 1 1 589C6C92
P 7200 3050
F 0 "U2" H 6900 3500 60  0000 C CNN
F 1 "MAX14850" H 7200 2600 60  0000 C CNN
F 2 "kicad-libraries:SOIC16" H 7450 3550 60  0001 C CNN
F 3 "" H 7450 3550 60  0000 C CNN
	1    7200 3050
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:CON-SENSOR2 P1
U 1 1 589C6F82
P 1050 1550
F 0 "P1" H 900 1950 60  0000 C CNN
F 1 "CON-SENSOR2" V 1200 1550 60  0000 C CNN
F 2 "kicad-libraries:CON-SENSOR2" H 1150 1400 60  0001 C CNN
F 3 "" H 1150 1400 60  0000 C CNN
	1    1050 1550
	-1   0    0    -1  
$EndComp
$Comp
L tinkerforge:CON-SENSOR2 P2
U 1 1 589C7061
P 10400 3000
F 0 "P2" H 10250 3400 60  0000 C CNN
F 1 "CON-SENSOR2" V 10550 3000 60  0000 C CNN
F 2 "kicad-libraries:CON-SENSOR2" H 10500 2850 60  0001 C CNN
F 3 "" H 10500 2850 60  0000 C CNN
	1    10400 3000
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:LD1117 U3
U 1 1 589C71BF
P 9300 4950
F 0 "U3" H 9100 5450 60  0000 C CNN
F 1 "LD1117" H 9300 5250 60  0000 C CNN
F 2 "kicad-libraries:SOT-223" H 9300 4950 60  0001 C CNN
F 3 "" H 9300 4950 60  0000 C CNN
	1    9300 4950
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:C C9
U 1 1 589C7370
P 8350 5050
F 0 "C9" H 8400 5150 50  0000 L CNN
F 1 "4,7µF/10V" V 8200 4850 50  0000 L CNN
F 2 "kicad-libraries:C0805" H 8350 5050 60  0001 C CNN
F 3 "" H 8350 5050 60  0000 C CNN
	1    8350 5050
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:C C10
U 1 1 589C753D
P 8700 5050
F 0 "C10" H 8750 5150 50  0000 L CNN
F 1 "100n" H 8750 4950 50  0000 L CNN
F 2 "kicad-libraries:C0603F" H 8700 5050 60  0001 C CNN
F 3 "" H 8700 5050 60  0000 C CNN
	1    8700 5050
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:C C11
U 1 1 589C75EA
P 9900 5050
F 0 "C11" H 9950 5150 50  0000 L CNN
F 1 "10µF/10V" V 9750 4850 50  0000 L CNN
F 2 "kicad-libraries:C0805" H 9900 5050 60  0001 C CNN
F 3 "" H 9900 5050 60  0000 C CNN
	1    9900 5050
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:C C12
U 1 1 589C7663
P 10250 5050
F 0 "C12" H 10300 5150 50  0000 L CNN
F 1 "100n" H 10300 4950 50  0000 L CNN
F 2 "kicad-libraries:C0603F" H 10250 5050 60  0001 C CNN
F 3 "" H 10250 5050 60  0000 C CNN
	1    10250 5050
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:DCDC-CRE1 U1
U 1 1 589D7C9F
P 7200 1500
F 0 "U1" H 6950 1700 60  0000 C CNN
F 1 "DCDC-CRE1" H 7500 1700 60  0000 C CNN
F 2 "kicad-libraries:SIP4" H 7200 1500 60  0001 C CNN
F 3 "" H 7200 1500 60  0000 C CNN
	1    7200 1500
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:GND #PWR01
U 1 1 589D822B
P 6950 2000
F 0 "#PWR01" H 6950 2000 30  0001 C CNN
F 1 "GND" H 6950 1930 30  0001 C CNN
F 2 "" H 6950 2000 60  0000 C CNN
F 3 "" H 6950 2000 60  0000 C CNN
	1    6950 2000
	1    0    0    -1  
$EndComp
Text GLabel 7750 4750 0    60   Input ~ 0
5V_DCDC
Text GLabel 10800 4750 2    60   Output ~ 0
3,3VB
Text GLabel 8900 1900 2    60   Output ~ 0
5V_DCDC
Text GLabel 9950 2700 0    60   Input ~ 0
5V_DCDC
Text GLabel 9950 2900 0    60   Input ~ 0
3,3VB
$Comp
L tinkerforge:GND #PWR06
U 1 1 589D8B13
P 6650 3900
F 0 "#PWR06" H 6650 3900 30  0001 C CNN
F 1 "GND" H 6650 3830 30  0001 C CNN
F 2 "" H 6650 3900 60  0000 C CNN
F 3 "" H 6650 3900 60  0000 C CNN
	1    6650 3900
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:R R1
U 1 1 589D8C05
P 6200 1600
F 0 "R1" V 6280 1600 50  0000 C CNN
F 1 "1k" V 6200 1600 50  0000 C CNN
F 2 "kicad-libraries:R0603F" H 6200 1600 60  0001 C CNN
F 3 "" H 6200 1600 60  0000 C CNN
	1    6200 1600
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:3V3 #PWR07
U 1 1 589D8D3D
P 6200 1300
F 0 "#PWR07" H 6200 1400 40  0001 C CNN
F 1 "3V3" H 6200 1425 40  0000 C CNN
F 2 "" H 6200 1300 60  0000 C CNN
F 3 "" H 6200 1300 60  0000 C CNN
	1    6200 1300
	1    0    0    -1  
$EndComp
NoConn ~ 6700 3200
NoConn ~ 6700 3100
$Comp
L tinkerforge:R R2
U 1 1 589D8F66
P 8550 1650
F 0 "R2" V 8630 1650 50  0000 C CNN
F 1 "1k" V 8550 1650 50  0000 C CNN
F 2 "kicad-libraries:R0603F" H 8550 1650 60  0001 C CNN
F 3 "" H 8550 1650 60  0000 C CNN
	1    8550 1650
	1    0    0    -1  
$EndComp
Text GLabel 8550 1400 1    60   Input ~ 0
3,3VB
Text GLabel 8000 2700 2    60   Input ~ 0
3,3VB
$Comp
L tinkerforge:GND #PWR08
U 1 1 589D9484
P 2300 1400
F 0 "#PWR08" H 2300 1400 30  0001 C CNN
F 1 "GND" H 2300 1330 30  0001 C CNN
F 2 "" H 2300 1400 60  0000 C CNN
F 3 "" H 2300 1400 60  0000 C CNN
	1    2300 1400
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:C C7
U 1 1 589D98CC
P 7950 3600
F 0 "C7" H 8000 3700 50  0000 L CNN
F 1 "100n" H 8000 3500 50  0000 L CNN
F 2 "kicad-libraries:C0603F" H 7950 3600 60  0001 C CNN
F 3 "" H 7950 3600 60  0000 C CNN
	1    7950 3600
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:C C4
U 1 1 589D99C5
P 6500 3650
F 0 "C4" V 6450 3700 50  0000 L CNN
F 1 "100n" V 6450 3400 50  0000 L CNN
F 2 "kicad-libraries:C0603F" H 6500 3650 60  0001 C CNN
F 3 "" H 6500 3650 60  0000 C CNN
	1    6500 3650
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:GND #PWR014
U 1 1 589D9C3F
P 6500 3900
F 0 "#PWR014" H 6500 3900 30  0001 C CNN
F 1 "GND" H 6500 3830 30  0001 C CNN
F 2 "" H 6500 3900 60  0000 C CNN
F 3 "" H 6500 3900 60  0000 C CNN
	1    6500 3900
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:AGND #PWR015
U 1 1 589D9CA2
P 7950 3850
F 0 "#PWR015" H 7950 3600 50  0001 C CNN
F 1 "AGND" H 7950 3700 50  0000 C CNN
F 2 "" H 7950 3850 50  0000 C CNN
F 3 "" H 7950 3850 50  0000 C CNN
	1    7950 3850
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:CP1 C1
U 1 1 589D9E18
P 6000 2100
F 0 "C1" V 5950 1900 50  0000 L CNN
F 1 "470µF/16V" V 5850 1850 50  0000 L CNN
F 2 "kicad-libraries:ELKO_83" H 6000 2100 60  0001 C CNN
F 3 "" H 6000 2100 60  0000 C CNN
	1    6000 2100
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:C C5
U 1 1 589DA842
P 6700 2100
F 0 "C5" H 6550 2200 50  0000 L CNN
F 1 "100n" H 6500 2000 50  0000 L CNN
F 2 "kicad-libraries:C0603F" H 6700 2100 60  0001 C CNN
F 3 "" H 6700 2100 60  0000 C CNN
	1    6700 2100
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:C C3
U 1 1 589DA98A
P 6400 2100
F 0 "C3" H 6250 2200 50  0000 L CNN
F 1 "10µ" H 6200 2000 50  0000 L CNN
F 2 "kicad-libraries:C0805" H 6400 2100 60  0001 C CNN
F 3 "" H 6400 2100 60  0000 C CNN
	1    6400 2100
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:GND #PWR016
U 1 1 589DACB4
P 6000 2350
F 0 "#PWR016" H 6000 2350 30  0001 C CNN
F 1 "GND" H 6000 2280 30  0001 C CNN
F 2 "" H 6000 2350 60  0000 C CNN
F 3 "" H 6000 2350 60  0000 C CNN
	1    6000 2350
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:GND #PWR017
U 1 1 589DACEF
P 6400 2350
F 0 "#PWR017" H 6400 2350 30  0001 C CNN
F 1 "GND" H 6400 2280 30  0001 C CNN
F 2 "" H 6400 2350 60  0000 C CNN
F 3 "" H 6400 2350 60  0000 C CNN
	1    6400 2350
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:GND #PWR018
U 1 1 589DAD2A
P 6700 2350
F 0 "#PWR018" H 6700 2350 30  0001 C CNN
F 1 "GND" H 6700 2280 30  0001 C CNN
F 2 "" H 6700 2350 60  0000 C CNN
F 3 "" H 6700 2350 60  0000 C CNN
	1    6700 2350
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:C C6
U 1 1 589DB6F3
P 7700 2150
F 0 "C6" H 7550 2250 50  0000 L CNN
F 1 "4,7µ" H 7500 2050 50  0000 L CNN
F 2 "kicad-libraries:C0805" H 7700 2150 60  0001 C CNN
F 3 "" H 7700 2150 60  0000 C CNN
	1    7700 2150
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:C C8
U 1 1 589DB760
P 8050 2150
F 0 "C8" H 7900 2250 50  0000 L CNN
F 1 "100n" H 7850 2050 50  0000 L CNN
F 2 "kicad-libraries:C0603F" H 8050 2150 60  0001 C CNN
F 3 "" H 8050 2150 60  0000 C CNN
	1    8050 2150
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:C C2
U 1 1 589DBACD
P 6250 3650
F 0 "C2" V 6200 3700 50  0000 L CNN
F 1 "10µ" V 6200 3450 50  0000 L CNN
F 2 "kicad-libraries:C0805" H 6250 3650 60  0001 C CNN
F 3 "" H 6250 3650 60  0000 C CNN
	1    6250 3650
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:GND #PWR021
U 1 1 589DBCC7
P 6250 3900
F 0 "#PWR021" H 6250 3900 30  0001 C CNN
F 1 "GND" H 6250 3830 30  0001 C CNN
F 2 "" H 6250 3900 60  0000 C CNN
F 3 "" H 6250 3900 60  0000 C CNN
	1    6250 3900
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:DRILL U7
U 1 1 589DDA30
P 11000 6350
F 0 "U7" H 11050 6400 60  0001 C CNN
F 1 "DRILL" H 11000 6350 60  0000 C CNN
F 2 "kicad-libraries:DRILL_NP" H 11000 6350 60  0001 C CNN
F 3 "" H 11000 6350 60  0000 C CNN
	1    11000 6350
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:DRILL U5
U 1 1 589DDB2A
P 10650 6350
F 0 "U5" H 10700 6400 60  0001 C CNN
F 1 "DRILL" H 10650 6350 60  0000 C CNN
F 2 "kicad-libraries:DRILL_NP" H 10650 6350 60  0001 C CNN
F 3 "" H 10650 6350 60  0000 C CNN
	1    10650 6350
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:DRILL U4
U 1 1 589DDBB7
P 10650 6150
F 0 "U4" H 10700 6200 60  0001 C CNN
F 1 "DRILL" H 10650 6150 60  0000 C CNN
F 2 "kicad-libraries:DRILL_NP" H 10650 6150 60  0001 C CNN
F 3 "" H 10650 6150 60  0000 C CNN
	1    10650 6150
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:DRILL U6
U 1 1 589DDBFE
P 11000 6150
F 0 "U6" H 11050 6200 60  0001 C CNN
F 1 "DRILL" H 11000 6150 60  0000 C CNN
F 2 "kicad-libraries:DRILL_NP" H 11000 6150 60  0001 C CNN
F 3 "" H 11000 6150 60  0000 C CNN
	1    11000 6150
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:3V3 #PWR023
U 1 1 589DE2C2
P 5350 1300
F 0 "#PWR023" H 5350 1400 40  0001 C CNN
F 1 "3V3" H 5350 1425 40  0000 C CNN
F 2 "" H 5350 1300 60  0000 C CNN
F 3 "" H 5350 1300 60  0000 C CNN
	1    5350 1300
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:TVS D1
U 1 1 589DC2B0
P 10650 5100
F 0 "D1" H 10650 5200 50  0000 C CNN
F 1 "Z3.3V" H 10650 5000 50  0000 C CNN
F 2 "kicad-libraries:SOD-323" H 10650 5100 50  0001 C CNN
F 3 "" H 10650 5100 50  0000 C CNN
	1    10650 5100
	0    1    1    0   
$EndComp
Text Notes 600  7700 0    40   ~ 0
Copyright Tinkerforge GmbH 2017.\nThis documentation describes Open Hardware and is licensed under the\nCERN OHL v. 1.1.\nYou may redistribute and modify this documentation under the terms of the\nCERN OHL v.1.1. (http://ohwr.org/cernohl). This documentation is distributed\nWITHOUT ANY EXPRESS OR IMPLIED WARRANTY, INCLUDING OF\nMERCHANTABILITY, SATISFACTORY QUALITY AND FITNESS FOR A\nPARTICULAR PURPOSE. Please see the CERN OHL v.1.1 for applicable\nconditions\n
$Comp
L tinkerforge:R_PACK4 RP1
U 1 1 590C696A
P 1850 1900
F 0 "RP1" H 1850 2350 50  0000 C CNN
F 1 "82" H 1850 1850 50  0000 C CNN
F 2 "kicad-libraries:4X0402" H 1850 1900 50  0001 C CNN
F 3 "" H 1850 1900 50  0000 C CNN
	1    1850 1900
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:C C13
U 1 1 590C727D
P 1500 2100
F 0 "C13" H 1550 2200 50  0000 L CNN
F 1 "220pF" H 1550 2000 50  0000 L CNN
F 2 "kicad-libraries:C0402F" H 1500 2100 60  0001 C CNN
F 3 "" H 1500 2100 60  0000 C CNN
	1    1500 2100
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:R_PACK4 RP2
U 1 1 590C801C
P 8850 2950
F 0 "RP2" H 8800 3450 50  0000 C CNN
F 1 "82" H 8850 2900 50  0000 C CNN
F 2 "kicad-libraries:4X0402" H 8850 2950 50  0001 C CNN
F 3 "" H 8850 2950 50  0000 C CNN
	1    8850 2950
	1    0    0    1   
$EndComp
$Comp
L tinkerforge:C C14
U 1 1 590C8FA8
P 9100 3600
F 0 "C14" H 9150 3700 50  0000 L CNN
F 1 "220pf" H 9150 3500 50  0000 L CNN
F 2 "kicad-libraries:C0402F" H 9100 3600 60  0001 C CNN
F 3 "" H 9100 3600 60  0000 C CNN
	1    9100 3600
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:C C15
U 1 1 590C919A
P 9450 3600
F 0 "C15" H 9500 3700 50  0000 L CNN
F 1 "220pf" H 9500 3500 50  0000 L CNN
F 2 "kicad-libraries:C0402F" H 9450 3600 60  0001 C CNN
F 3 "" H 9450 3600 60  0000 C CNN
	1    9450 3600
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:C C16
U 1 1 590C9205
P 9800 3600
F 0 "C16" H 9850 3700 50  0000 L CNN
F 1 "220pF" H 9850 3500 50  0000 L CNN
F 2 "kicad-libraries:C0402F" H 9800 3600 60  0001 C CNN
F 3 "" H 9800 3600 60  0000 C CNN
	1    9800 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	8900 4750 8700 4750
Wire Wire Line
	8700 4850 8700 4750
Connection ~ 8700 4750
Wire Wire Line
	8350 4850 8350 4750
Connection ~ 8350 4750
Wire Wire Line
	9700 4750 9900 4750
Wire Wire Line
	10250 4850 10250 4750
Connection ~ 10250 4750
Wire Wire Line
	9900 4850 9900 4750
Connection ~ 9900 4750
Wire Wire Line
	5350 2700 6250 2700
Wire Wire Line
	6950 1800 6950 2000
Wire Wire Line
	7350 1800 7350 1950
Wire Wire Line
	7450 1800 7450 1900
Wire Wire Line
	6700 3400 6650 3400
Wire Wire Line
	6650 3400 6650 3900
Wire Wire Line
	7700 3400 7750 3400
Wire Wire Line
	7750 3100 7750 3200
Wire Wire Line
	5850 2800 6700 2800
Wire Wire Line
	6200 1850 6200 3300
Wire Wire Line
	6200 1350 6200 1300
Wire Wire Line
	5850 2900 6700 2900
Wire Wire Line
	5850 3000 6700 3000
Wire Wire Line
	8550 3300 7700 3300
Wire Wire Line
	7700 2800 8450 2800
Wire Wire Line
	8450 2800 8450 3100
Wire Wire Line
	7700 2900 8350 2900
Wire Wire Line
	8350 2900 8350 3200
Wire Wire Line
	7700 3000 8250 3000
Wire Wire Line
	8250 3000 8250 3400
Wire Wire Line
	7700 3100 7750 3100
Connection ~ 7750 3400
Wire Wire Line
	7700 3200 7750 3200
Connection ~ 7750 3200
Wire Wire Line
	7700 2700 7950 2700
Wire Wire Line
	9300 5150 9300 5400
Wire Wire Line
	7950 2700 7950 3400
Connection ~ 7950 2700
Wire Wire Line
	6500 2700 6500 3450
Connection ~ 6500 2700
Wire Wire Line
	7950 3800 7950 3850
Wire Wire Line
	7050 1850 7050 1800
Wire Wire Line
	5600 1850 6000 1850
Wire Wire Line
	6000 1900 6000 1850
Connection ~ 6000 1850
Wire Wire Line
	6400 1900 6400 1850
Connection ~ 6400 1850
Wire Wire Line
	6700 1900 6700 1850
Connection ~ 6700 1850
Wire Wire Line
	6000 2300 6000 2350
Wire Wire Line
	6400 2300 6400 2350
Wire Wire Line
	6700 2300 6700 2350
Wire Wire Line
	7450 1900 7700 1900
Wire Wire Line
	7700 1950 7700 1900
Connection ~ 7700 1900
Wire Wire Line
	8050 1950 8050 1900
Connection ~ 8050 1900
Wire Wire Line
	8050 2400 8050 2350
Wire Wire Line
	7700 2400 7700 2350
Wire Wire Line
	6500 3850 6500 3900
Wire Wire Line
	6250 3900 6250 3850
Wire Wire Line
	6250 3450 6250 2700
Connection ~ 6250 2700
Wire Wire Line
	10650 4850 10650 4750
Connection ~ 10650 4750
Wire Wire Line
	10650 5400 10650 5350
Wire Wire Line
	10250 5250 10250 5400
Wire Wire Line
	9900 5400 9900 5250
Wire Wire Line
	8700 5400 8700 5250
Wire Wire Line
	8350 5250 8350 5400
Wire Wire Line
	8550 1900 8550 3000
Wire Wire Line
	8550 3000 8650 3000
Connection ~ 8550 3000
Wire Wire Line
	8450 3100 8650 3100
Wire Wire Line
	8350 3200 8650 3200
Wire Wire Line
	8600 3300 8600 3400
Wire Wire Line
	8600 3400 8250 3400
Wire Wire Line
	9950 2700 10050 2700
Wire Wire Line
	9950 2900 10050 2900
Wire Wire Line
	10050 2800 10000 2800
Wire Wire Line
	10000 2800 10000 3850
Wire Wire Line
	8600 3300 8650 3300
Wire Wire Line
	9050 3000 9800 3000
Wire Wire Line
	10050 3100 9450 3100
Wire Wire Line
	9050 3200 9100 3200
Wire Wire Line
	10050 3300 9050 3300
Wire Wire Line
	9100 3400 9100 3200
Connection ~ 9100 3200
Wire Wire Line
	9450 3400 9450 3100
Connection ~ 9450 3100
Wire Wire Line
	9800 3400 9800 3000
Connection ~ 9800 3000
Wire Wire Line
	9800 3800 9800 3850
Wire Wire Line
	9450 3800 9450 3850
Wire Wire Line
	9100 3800 9100 3850
Text Notes 850  1050 0    60   ~ 0
Input\nto Brick
Text Notes 10200 2450 0    60   ~ 0
Output\nto Bricklet
$Comp
L tinkerforge:XMC1XXX24 U8
U 4 1 5A2E880D
P 3750 5000
F 0 "U8" H 3750 5450 60  0000 C CNN
F 1 "XMC1100" H 3750 4550 60  0000 C CNN
F 2 "kicad-libraries:QFN24-4x4mm-0.5mm" H 3900 5750 60  0001 C CNN
F 3 "" H 3900 5750 60  0000 C CNN
	4    3750 5000
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:XMC1XXX24 U8
U 2 1 5A2E88C3
P 3750 3700
F 0 "U8" H 3750 4250 60  0000 C CNN
F 1 "XMC1100" H 3750 3150 60  0000 C CNN
F 2 "kicad-libraries:QFN24-4x4mm-0.5mm" H 3900 4450 60  0001 C CNN
F 3 "" H 3900 4450 60  0000 C CNN
	2    3750 3700
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:XMC1XXX24 U8
U 3 1 5A2E89A5
P 3750 2700
F 0 "U8" H 3750 2950 60  0000 C CNN
F 1 "XMC1100" H 3750 2450 60  0000 C CNN
F 2 "kicad-libraries:QFN24-4x4mm-0.5mm" H 3900 3450 60  0001 C CNN
F 3 "" H 3900 3450 60  0000 C CNN
	3    3750 2700
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:XMC1XXX24 U8
U 1 1 5A2E8A10
P 3750 6000
F 0 "U8" H 3750 6400 60  0000 C CNN
F 1 "XMC1100" H 3750 5600 60  0000 C CNN
F 2 "kicad-libraries:QFN24-4x4mm-0.5mm" H 3900 6750 60  0001 C CNN
F 3 "" H 3900 6750 60  0000 C CNN
	1    3750 6000
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:C C17
U 1 1 5A2F4C11
P 3250 5950
F 0 "C17" H 3300 6050 50  0000 L CNN
F 1 "100n" H 3300 5850 50  0000 L CNN
F 2 "kicad-libraries:C0603F" H 3250 5950 60  0001 C CNN
F 3 "" H 3250 5950 60  0000 C CNN
	1    3250 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 5700 3250 5700
Wire Wire Line
	3250 5650 3250 5700
Wire Wire Line
	3250 6150 3250 6200
Wire Wire Line
	3250 6200 3400 6200
Wire Wire Line
	3250 6300 3400 6300
Connection ~ 3250 6200
Connection ~ 3250 6300
Connection ~ 3250 5700
$Comp
L tinkerforge:3V3 #PWR027
U 1 1 5A2F55CA
P 3250 5650
F 0 "#PWR027" H 3250 5750 40  0001 C CNN
F 1 "3V3" H 3250 5775 40  0000 C CNN
F 2 "" H 3250 5650 60  0000 C CNN
F 3 "" H 3250 5650 60  0000 C CNN
	1    3250 5650
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:GND #PWR028
U 1 1 5A2F81AB
P 3250 6450
F 0 "#PWR028" H 3250 6450 30  0001 C CNN
F 1 "GND" H 3250 6380 30  0001 C CNN
F 2 "" H 3250 6450 60  0000 C CNN
F 3 "" H 3250 6450 60  0000 C CNN
	1    3250 6450
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:CONN_01X02 P3
U 1 1 5A2FA3FD
P 2900 5000
F 0 "P3" H 2900 5150 50  0000 C CNN
F 1 "BOOT" V 3000 5000 50  0000 C CNN
F 2 "kicad-libraries:SolderJumper" H 2900 5000 50  0001 C CNN
F 3 "" H 2900 5000 50  0000 C CNN
	1    2900 5000
	-1   0    0    1   
$EndComp
Wire Wire Line
	3400 4950 3100 4950
Wire Wire Line
	3100 5050 3150 5050
Wire Wire Line
	3150 5050 3150 5100
$Comp
L tinkerforge:GND #PWR029
U 1 1 5A2FA8CF
P 3150 5100
F 0 "#PWR029" H 3150 5100 30  0001 C CNN
F 1 "GND" H 3150 5030 30  0001 C CNN
F 2 "" H 3150 5100 60  0000 C CNN
F 3 "" H 3150 5100 60  0000 C CNN
	1    3150 5100
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:R R3
U 1 1 5A2FAAFC
P 3050 2650
F 0 "R3" V 3130 2650 50  0000 C CNN
F 1 "1k" V 3050 2650 50  0000 C CNN
F 2 "kicad-libraries:R0603F" H 3050 2650 60  0001 C CNN
F 3 "" H 3050 2650 60  0000 C CNN
	1    3050 2650
	0    1    1    0   
$EndComp
$Comp
L tinkerforge:LED D2
U 1 1 5A2FAC85
P 2550 2650
F 0 "D2" H 2550 2750 50  0000 C CNN
F 1 "blue" H 2550 2550 50  0000 C CNN
F 2 "kicad-libraries:D0603E" H 2550 2650 50  0001 C CNN
F 3 "" H 2550 2650 50  0000 C CNN
	1    2550 2650
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:3V3 #PWR030
U 1 1 5A2FBA6A
P 2300 2650
F 0 "#PWR030" H 2300 2750 40  0001 C CNN
F 1 "3V3" H 2300 2775 40  0000 C CNN
F 2 "" H 2300 2650 60  0000 C CNN
F 3 "" H 2300 2650 60  0000 C CNN
	1    2300 2650
	1    0    0    -1  
$EndComp
NoConn ~ 3400 5350
NoConn ~ 3400 5150
NoConn ~ 3400 5050
NoConn ~ 3400 4850
NoConn ~ 3400 3850
$Comp
L tinkerforge:CONN_01X01 P4
U 1 1 5A2FC709
P 2900 4750
F 0 "P4" H 2900 4850 50  0000 C CNN
F 1 "Debug" V 3000 4750 50  0000 C CNN
F 2 "kicad-libraries:DEBUG_PAD" H 2900 4750 50  0001 C CNN
F 3 "" H 2900 4750 50  0000 C CNN
	1    2900 4750
	-1   0    0    1   
$EndComp
Wire Notes Line
	7200 550  7200 6400
NoConn ~ 3400 2550
NoConn ~ 3400 2750
NoConn ~ 3400 2850
$Comp
L tinkerforge:+5V #PWR031
U 1 1 5A308861
P 5600 1300
F 0 "#PWR031" H 5600 1150 50  0001 C CNN
F 1 "+5V" H 5600 1440 40  0000 C CNN
F 2 "" H 5600 1300 50  0000 C CNN
F 3 "" H 5600 1300 50  0000 C CNN
	1    5600 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 1850 5600 1300
$Comp
L tinkerforge:+5V #PWR032
U 1 1 5A30A084
P 1500 850
F 0 "#PWR032" H 1500 700 50  0001 C CNN
F 1 "+5V" H 1500 990 40  0000 C CNN
F 2 "" H 1500 850 50  0000 C CNN
F 3 "" H 1500 850 50  0000 C CNN
	1    1500 850 
	1    0    0    -1  
$EndComp
Wire Wire Line
	1400 1250 1500 1250
Wire Wire Line
	1500 1250 1500 850 
$Comp
L tinkerforge:3V3 #PWR033
U 1 1 5A30B176
P 1700 850
F 0 "#PWR033" H 1700 950 40  0001 C CNN
F 1 "3V3" H 1700 975 40  0000 C CNN
F 2 "" H 1700 850 60  0000 C CNN
F 3 "" H 1700 850 60  0000 C CNN
	1    1700 850 
	1    0    0    -1  
$EndComp
Wire Wire Line
	1700 850  1700 1450
Wire Wire Line
	1700 1450 1400 1450
Wire Wire Line
	1400 1350 2300 1350
Wire Wire Line
	2300 1350 2300 1400
$Comp
L tinkerforge:GND #PWR034
U 1 1 5A30C5B0
P 1050 2350
F 0 "#PWR034" H 1050 2350 30  0001 C CNN
F 1 "GND" H 1050 2280 30  0001 C CNN
F 2 "" H 1050 2350 60  0000 C CNN
F 3 "" H 1050 2350 60  0000 C CNN
	1    1050 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	1050 2000 1050 2350
$Comp
L tinkerforge:GND #PWR035
U 1 1 5A30E213
P 1500 2350
F 0 "#PWR035" H 1500 2350 30  0001 C CNN
F 1 "GND" H 1500 2280 30  0001 C CNN
F 2 "" H 1500 2350 60  0000 C CNN
F 3 "" H 1500 2350 60  0000 C CNN
	1    1500 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 2350 1500 2300
Wire Wire Line
	1400 1850 1500 1850
Wire Wire Line
	1500 1850 1500 1900
Wire Wire Line
	1400 1550 1650 1550
Wire Wire Line
	1650 1650 1400 1650
Wire Wire Line
	1400 1750 1650 1750
Connection ~ 1500 1850
Wire Wire Line
	5350 2700 5350 1300
Text GLabel 2200 1550 2    39   Output ~ 0
S-CS
Text GLabel 2200 1650 2    39   Output ~ 0
S-CLK
Text GLabel 2200 1750 2    39   Output ~ 0
S-MOSI
Text GLabel 2200 1850 2    39   Input ~ 0
S-MISO
Wire Wire Line
	2050 1550 2200 1550
Wire Wire Line
	2200 1650 2050 1650
Wire Wire Line
	2050 1750 2200 1750
Wire Wire Line
	2200 1850 2050 1850
Text GLabel 3300 3950 0    39   Input ~ 0
S-CS
Text GLabel 3300 4050 0    39   Input ~ 0
S-CLK
Text GLabel 3300 4150 0    39   Input ~ 0
S-MOSI
Text GLabel 3300 4650 0    39   Output ~ 0
S-MISO
Wire Wire Line
	3300 3450 3400 3450
Wire Wire Line
	3400 3550 3300 3550
Wire Wire Line
	3300 3650 3400 3650
Wire Wire Line
	3400 3750 3300 3750
NoConn ~ 3400 3350
NoConn ~ 3400 5250
Text GLabel 3300 3750 0    39   Output ~ 0
M-CS
Text GLabel 3300 3650 0    39   Output ~ 0
M-CLK
Text GLabel 3300 3550 0    39   Output ~ 0
M-MOSI
Text GLabel 3300 3450 0    39   Input ~ 0
M-MISO
Text GLabel 5850 3300 0    39   Input ~ 0
M-CS
Text GLabel 5850 2800 0    39   Input ~ 0
M-CLK
Text GLabel 5850 2900 0    39   Input ~ 0
M-MOSI
Text GLabel 5850 3000 0    39   Output ~ 0
M-MISO
Wire Wire Line
	5850 3300 6200 3300
Connection ~ 6200 3300
Wire Wire Line
	3300 3950 3400 3950
Wire Wire Line
	3400 4050 3300 4050
Wire Wire Line
	3300 4150 3400 4150
Wire Wire Line
	3400 4650 3300 4650
Wire Wire Line
	2800 2650 2750 2650
Wire Wire Line
	2350 2650 2300 2650
Text Notes 4200 3850 0    60   ~ 0
SPI Master\nP0.6 : CH1-DX0 : MISO\nP0.7 : CH1-DOUT : MOSI\nP0.8 : CH1-SCLKOUT : CLK\nP0.9 : CH1-SELO0 : SEL
Text Notes 4200 4450 0    60   ~ 0
SPI Slave/CH0\nP0.13 : USIC0_CH0-DX2F : SEL\nP0.14 : USIC0_CH0-DX1A : CLK\nP0.15 : USIC0_CH0-DX0B : MOSI\nP2.0 : USIC0_CH0-DOUT0 : MISO
Wire Wire Line
	3300 2650 3400 2650
NoConn ~ 3400 3250
Wire Wire Line
	3100 4750 3400 4750
Wire Wire Line
	8700 4750 8350 4750
Wire Wire Line
	8350 4750 7750 4750
Wire Wire Line
	10250 4750 10650 4750
Wire Wire Line
	9900 4750 10250 4750
Wire Wire Line
	7750 3400 7750 3850
Wire Wire Line
	7750 3200 7750 3400
Wire Wire Line
	7950 2700 8000 2700
Wire Wire Line
	6500 2700 6700 2700
Wire Wire Line
	6000 1850 6400 1850
Wire Wire Line
	6400 1850 6700 1850
Wire Wire Line
	6700 1850 7050 1850
Wire Wire Line
	7700 1900 8050 1900
Wire Wire Line
	8050 1900 8900 1900
Wire Wire Line
	6250 2700 6500 2700
Wire Wire Line
	10650 4750 10800 4750
Wire Wire Line
	8550 3000 8550 3300
Wire Wire Line
	9100 3200 10050 3200
Wire Wire Line
	9450 3100 9050 3100
Wire Wire Line
	9800 3000 10050 3000
Wire Wire Line
	3250 6200 3250 6300
Wire Wire Line
	3250 6300 3250 6450
Wire Wire Line
	3250 5700 3250 5750
Wire Wire Line
	1500 1850 1650 1850
Wire Wire Line
	6200 3300 6700 3300
$Comp
L tinkerforge:AGND #PWR?
U 1 1 5D02A350
P 7750 3850
F 0 "#PWR?" H 7750 3600 50  0001 C CNN
F 1 "AGND" H 7750 3700 50  0000 C CNN
F 2 "" H 7750 3850 50  0000 C CNN
F 3 "" H 7750 3850 50  0000 C CNN
	1    7750 3850
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:AGND #PWR?
U 1 1 5D02A5FE
P 9100 3850
F 0 "#PWR?" H 9100 3600 50  0001 C CNN
F 1 "AGND" H 9100 3700 50  0000 C CNN
F 2 "" H 9100 3850 50  0000 C CNN
F 3 "" H 9100 3850 50  0000 C CNN
	1    9100 3850
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:AGND #PWR?
U 1 1 5D02FFF8
P 9450 3850
F 0 "#PWR?" H 9450 3600 50  0001 C CNN
F 1 "AGND" H 9450 3700 50  0000 C CNN
F 2 "" H 9450 3850 50  0000 C CNN
F 3 "" H 9450 3850 50  0000 C CNN
	1    9450 3850
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:AGND #PWR?
U 1 1 5D030049
P 9800 3850
F 0 "#PWR?" H 9800 3600 50  0001 C CNN
F 1 "AGND" H 9800 3700 50  0000 C CNN
F 2 "" H 9800 3850 50  0000 C CNN
F 3 "" H 9800 3850 50  0000 C CNN
	1    9800 3850
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:AGND #PWR?
U 1 1 5D03009A
P 10000 3850
F 0 "#PWR?" H 10000 3600 50  0001 C CNN
F 1 "AGND" H 10000 3700 50  0000 C CNN
F 2 "" H 10000 3850 50  0000 C CNN
F 3 "" H 10000 3850 50  0000 C CNN
	1    10000 3850
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:AGND #PWR?
U 1 1 5D0300EB
P 10250 5400
F 0 "#PWR?" H 10250 5150 50  0001 C CNN
F 1 "AGND" H 10250 5250 50  0000 C CNN
F 2 "" H 10250 5400 50  0000 C CNN
F 3 "" H 10250 5400 50  0000 C CNN
	1    10250 5400
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:AGND #PWR?
U 1 1 5D03013C
P 10650 5400
F 0 "#PWR?" H 10650 5150 50  0001 C CNN
F 1 "AGND" H 10650 5250 50  0000 C CNN
F 2 "" H 10650 5400 50  0000 C CNN
F 3 "" H 10650 5400 50  0000 C CNN
	1    10650 5400
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:AGND #PWR?
U 1 1 5D03018D
P 9900 5400
F 0 "#PWR?" H 9900 5150 50  0001 C CNN
F 1 "AGND" H 9900 5250 50  0000 C CNN
F 2 "" H 9900 5400 50  0000 C CNN
F 3 "" H 9900 5400 50  0000 C CNN
	1    9900 5400
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:AGND #PWR?
U 1 1 5D0301DE
P 9300 5400
F 0 "#PWR?" H 9300 5150 50  0001 C CNN
F 1 "AGND" H 9300 5250 50  0000 C CNN
F 2 "" H 9300 5400 50  0000 C CNN
F 3 "" H 9300 5400 50  0000 C CNN
	1    9300 5400
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:AGND #PWR?
U 1 1 5D03022F
P 8700 5400
F 0 "#PWR?" H 8700 5150 50  0001 C CNN
F 1 "AGND" H 8700 5250 50  0000 C CNN
F 2 "" H 8700 5400 50  0000 C CNN
F 3 "" H 8700 5400 50  0000 C CNN
	1    8700 5400
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:AGND #PWR?
U 1 1 5D030280
P 8350 5400
F 0 "#PWR?" H 8350 5150 50  0001 C CNN
F 1 "AGND" H 8350 5250 50  0000 C CNN
F 2 "" H 8350 5400 50  0000 C CNN
F 3 "" H 8350 5400 50  0000 C CNN
	1    8350 5400
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:AGND #PWR?
U 1 1 5D03061C
P 8050 2400
F 0 "#PWR?" H 8050 2150 50  0001 C CNN
F 1 "AGND" H 8050 2250 50  0000 C CNN
F 2 "" H 8050 2400 50  0000 C CNN
F 3 "" H 8050 2400 50  0000 C CNN
	1    8050 2400
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:AGND #PWR?
U 1 1 5D0307EE
P 7700 2400
F 0 "#PWR?" H 7700 2150 50  0001 C CNN
F 1 "AGND" H 7700 2250 50  0000 C CNN
F 2 "" H 7700 2400 50  0000 C CNN
F 3 "" H 7700 2400 50  0000 C CNN
	1    7700 2400
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:AGND #PWR?
U 1 1 5D03083F
P 7350 1950
F 0 "#PWR?" H 7350 1700 50  0001 C CNN
F 1 "AGND" H 7350 1800 50  0000 C CNN
F 2 "" H 7350 1950 50  0000 C CNN
F 3 "" H 7350 1950 50  0000 C CNN
	1    7350 1950
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:AGND #PWR?
U 1 1 5D030C97
P 10400 3850
F 0 "#PWR?" H 10400 3600 50  0001 C CNN
F 1 "AGND" H 10400 3700 50  0000 C CNN
F 2 "" H 10400 3850 50  0000 C CNN
F 3 "" H 10400 3850 50  0000 C CNN
	1    10400 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	10400 3850 10400 3450
$EndSCHEMATC
