# W.S.S
Weather Station System is an I.o.T project designed for the weather station in Harare, Zimbabwe. The system is a duo of the NodeMCU ESP8266 LoLion ESP-12E microcontroller. The W.S.S uses a motion sensor to collect data from the environment.

#1 Web-Server NodeMCU
Connect PIR to ESP8266:
PIR (VCC) - ESP-12E (3V)
PIR (GND) - ESP-12E (GND)
PIR (I/O) - ESP-12E (D7)

#2 Client NodeMCU
Connect OLED to ESP8266:
OLED (VCC) - ESP-12E (3V)
OLED (GND) - ESP-12E (GND)
OLED (SCL) - ESP-12E (D1)
OLED (SDA) - ESP-12E (D2)
