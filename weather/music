import serial
import pygame

arduinoData = serial.Serial('/dev/ttyACM0')
# pygame.mixer.pre_init(220500, 16, 2, 4096)
pygame.mixer.init()
snd1 = pygame.mixer.Sound("rush.ogg")
snd2 = pygame.mixer.Sound("quest.ogg")


started1 = False
started2 = False

while True:
    cc=str(arduinoData.readline())
    print(cc[2:][:-5])
    print("Stop1" in cc[2:][:-5])
    print(cc)

    if("Start1" in cc[2:][:-5] and not started1):
        # snd1 = pygame.mixer.Sound("rush.ogg")
        snd1.play()
        started1= True

    if("Stop1" in cc[2:][:-5] and started1):
        started1= False
        snd1.stop()

    if("Start2" in cc[2:][:-5] and not started2):
        # snd2 = pygame.mixer.Sound("eventually.ogg")
        snd2.play()
        started2= True

    if("Stop2" in cc[2:][:-5] and started2):
        started2= False
        snd2.stop()
