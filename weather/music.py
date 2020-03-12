import serial
import pygame

# This code allows to turn off and on music based on messages coming from Arduino
# Start listen for Arduino
# Specify Port where Arduino is connected in parameter to Serial.
arduinoData = serial.Serial('/dev/ttyACM0')
pygame.mixer.init()

# Load music by specifying the path to music
birds = pygame.mixer.Sound("birds.ogg")
wind = pygame.mixer.Sound("winter.ogg")
rain = pygame.mixer.Sound("rain.ogg")

# State of songs. This helps to keep track of songs that are playing
started1 = False
started2 = False
started3 = False

# Read messages from Arduino, turn on/off songs depending on the state
while True:
    # Read message from Arduino. Print message to console
    # (useful for debugging)
    cc=str(arduinoData.readline())
    print(cc)

    # If message is Start Bird music:
    # Turn other songs off, update states for these songs to False
    # Start Bird Music, update state to started True
    if("StartBirds" in cc[2:][:-5] and not started1):
        started2 = False
        started3 = False
        wind.stop()
        rain.stop()

        birds.play()
        started1= True

    # If message is Stop Bird music, stop it, update state to False
    if("StopBirds" in cc[2:][:-5] and started1):
        started1= False
        birds.stop()

    # If message is Start Winter music:
    # Turn other songs off, update states for these songs to False
    # Start Winter music, update state to started True
    if("StartWinter" in cc[2:][:-5] and not started2):
        started1 = False
        started3 = False
        birds.stop()
        rain.stop()

        wind.play()
        started2= True

    # If message is Stop Winter music, stop it, update state to False
    if("StopWinter" in cc[2:][:-5] and started2):
        started2= False
        wind.stop()

    # If message is Start Rain music:
    # Turn other songs off, update states for these songs to False
    # Start Rain music, update state to started True
    if("StartRain" in cc[2:][:-5] and not started3):
        started1 = False
        started2 = False
        birds.stop()
        wind.stop()

        rain.play()
        started3= True

    # If message is Stop Rain music, stop it, update state to False
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
