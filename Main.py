import serial
from time import sleep
import pygame

#Command translator lists
LeftCommands={"Flat":"Stop", "Bump":"Forward", "Left": "Forward","Right":"Accelerate", "Beg":"Stop", "Flex":"Reverse", "Down":"BridgeDown", "Stop": "BridgeUp" }
RightCommands={"Take":"Right", "Push":"Left", "Button":"Stop" }

#Initialization
pygame.mixer.init()
Arduino=serial.Serial('/dev/ttyUSB0', 9600)
BluetoothSerial2 = serial.Serial("/dev/rfcomm0", baudrate=9600)
BluetoothSerial1 = serial.Serial("/dev/rfcomm1", baudrate=9600)

#Song tracking variables
paused = False
playing=False

#Plays a song
def playSong(song):
	stopSong()
	pygame.mixer.music.load(song)
	pygame.mixer.music.play()
	playing=True
	paused=False
#Stops a song
def stopSong():
	pygame.mixer.music.stop()
	playing=False

#Pauses or resumes a song
def PauseSong():
	if playing:
		if paused:
			pygame.mixer.music.pause()
			paused=True
		else: 
			pygame.mixer.music.unpause()
			paused=False

#Checks input and sends it to arduino
def CheckInput(input):
	print input
	input=input[:-2]
	print input
	if input[0] == 'l': 
		if input[1:] in LeftCommands:
			Arduino.write(LeftCommands[input[1:]])
	else:
		if input[1:] in RightCommands:
			Arduino.write(RightCommands[input[1:]])	
	CheckMusic(input)

#Checks imput and checks if there are songs ready to be played
def CheckMusic(input):
	if input[0] == 'r':
		if input[1:]=="Revolution":
			playSong("/home/pi/Work/IronMan.mp3")    
		elif input[1:]=="Bump":
			PauseSong()
		elif input[1:]=="Beg":
			playSong("/home/pi/Work/Valkyries.mp3")
		elif input[1:]=="Push":
			playSong("/home/pi/Work/Johnny.mp3")
		elif input[1:]=="Stop":
			playSong("/home/pi/Work/MarchOfTheWarElephants.mp3")
		elif input[1:]=="Flex":
			stopSong()

#Main loop that checks for data
while True:
	if BluetoothSerial1.inWaiting() > 0:
		CheckInput(BluetoothSerial1.readline())
	if BluetoothSerial2.inWaiting() > 0:
		CheckInput(BluetoothSerial2.readline())
	sleep(0.3)
