import serial
import pygame

arduinoData = serial.Serial('/dev/ttyACM2')
# pygame.mixer.pre_init(220500, 16, 2, 4096)
pygame.mixer.init()
birds = pygame.mixer.Sound("birds.ogg")
wind = pygame.mixer.Sound("winter.ogg")
rain = pygame.mixer.Sound("rain.ogg")

started1 = False
started2 = False
started3 = False

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
