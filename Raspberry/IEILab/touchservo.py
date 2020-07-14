from time import sleep
import RPi.GPIO as GPIO
from IEILab.GroveStarterKit import Servo
from IEILab.GroveStarterKit import Touchsensor

GPIO.setmode(GPIO.BCM)

# touch in 18
# servo in 16

#2 4 6 8 10 12 14 16 18
#1 3 5 7 9    11 13 15 17

touchpin=18
servo = Servo()
servo.attach(16)
touch = TouchSensor()
touch.attach(touchpin)
loc=rand()%181
servo.write(loc)
state=0


while True:
	if touch.isTouched()
		if state ==0
			loc+=20
			servo.write(loc)
			sleep(0.2)
			if loc>=180
				state=1	
		else
			loc-=10
			servo.write(loc)
			sleep(0.2)
			if loc<=0
				state=0
	else

				

GPIO.cleanup()

