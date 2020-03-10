import serial
import pygame

# Start listen for arduino
arduinoData = serial.Serial('/dev/ttyACM0')
pygame.mixer.init()

# Load music
birds = pygame.mixer.Sound("birds.ogg")
wind = pygame.mixer.Sound("winter.ogg")
rain = pygame.mixer.Sound("rain.ogg")

# State of songs
started1 = False
started2 = False
started3 = False

# Read messages from Arduino, turn on/off songs depending on the state
while True:
    cc=str(arduinoData.readline())
    print(cc)
    print("Stop1" in cc[2:][:-5])
    print(cc)

    if("StartBirds" in cc[2:][:-5] and not started1):
        started2 = False
        started3 = False
        wind.stop()
        rain.stop()

        birds.play()
        started1= True

    if("StopBirds" in cc[2:][:-5] and started1):
        started1= False
        birds.stop()

    if("StartWinter" in cc[2:][:-5] and not started2):
        started1 = False
        started3 = False
        birds.stop()
        rain.stop()

        wind.play()
        started2= True

    if("StopWinter" in cc[2:][:-5] and started2):
        started2= False
        wind.stop()

    if("StartRain" in cc[2:][:-5] and not started3):
        started1 = False
        started2 = False
        birds.stop()
        wind.stop()

        rain.play()
        started3= True

    if("StopRain" in cc[2:][:-5] and started3):
        started3= False
        rain.stop()

# REFERENCES:
# 1) Code from first trial with Python Script for Assignment 2:
# https://github.com/Olga-Chitsvarina/Arduino-Musical-Instrument/commit/9d6f0b9ff605cd5f3fa7680977aacec84ca2638b
# 2) Pygame library:
# https://github.com/pygame/pygame/blob/bd131148444cd6e946aec986c93f9afc44728f85/test/sndarray_test.py
# 3) Python Serial Library:
# https://pyserial.readthedocs.io/en/latest/shortintro.html
# 4) Sound effects were downloaded from this website:
# https://bigsoundbank.com/detail-0595-wind.html
#
