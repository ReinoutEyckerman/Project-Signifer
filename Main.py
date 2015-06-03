#Imports
import serial
from time import sleep
import pygame

#Command Dictionary
LeftCommands={"Flat":"Stop", "Bump":"Forward", "Take": "Forward","Right":"Accelerate", "Beg":"Stop", "Flex":"Back", "Down":"BridgeDown", "Stop": "BridgeUp" }
RightCommands={"Take":"Right", "Push":"Left", "Button":"Switchmode" }

#Info
print "Initiating"

#Initiation code
pygame.mixer.init()
Arduino=serial.Serial('/dev/ttyUSB0', 9600)
BluetoothSerial2 = serial.Serial("/dev/rfcomm0", baudrate=9600)
BluetoothSerial1 = serial.Serial("/dev/rfcomm1", baudrate=9600)

#State Variables
paused = False
playing=False

#Plays music
def playSong(song):
	stopSong()
	pygame.mixer.music.load(song)
	pygame.mixer.music.play()
	playing=True
	paused=False

#Stops music
def stopSong():
	pygame.mixer.music.stop()
	playing=False

#Pauses or resumes a paused song
def PauseSong():
	if playing:
		if paused:
			pygame.mixer.music.pause()
			paused=True
		else: 
			pygame.mixer.music.unpause()
			paused=False

#Compares the input to the commands and sends this to the Arduino
def CheckInput(input):
	print "Input: "+input
	input=input[:-2]
	print "Filtered Input: "+ input
	if input!=None:
		if input[0] == 'l': 
			if input[1:] in LeftCommands:
				Arduino.write(LeftCommands[input[1:]])
		else:
			if input[1:] in RightCommands:
				Arduino.write(RightCommands[input[1:]])	
	CheckMusic(input)

#Compares the input to the playable songs
def CheckMusic(input):
	if input[0] == 'r':
		if input[1:]=="Revolution":
			playSong("/home/pi/Work/IronMan.mp3")    
		elif input[1:]=="Bump":
			PauseSong()
		elif input[1:]=="Beg":
			playSong("/home/pi/Work/Valkyries.mp3")
		elif input[1:]=="Down":
			playSong("/home/pi/Work/Hobbits.mp3")
		elif input[1:]=="Stop":
			playSong("/home/pi/Work/MarchOfTheWarElephants.mp3")
		elif input[1:]=="Flex":
			stopSong()


print "Commencing Code..."

#Loop doing the work
while True:
	if BluetoothSerial1.inWaiting() > 0:
		x = BluetoothSerial1.readline()
		CheckInput(x)
	if BluetoothSerial2.inWaiting() > 0:
		x = BluetoothSerial2.readline()
		CheckInput(x)
	sleep(0.2)
