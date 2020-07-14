import RPi.GPIO as GPIO
from IEILab.GroveStarterKit import LEDBar
from time import sleep

clk = 23
dta = 18
# up 9
i=1
d=0

GPIO.setmode(GPIO.BCM)
ledBar=LEDBar(clk,dta)

while True:
	ledBar.singleLed(i,1)
	ledBar.singleLed(d,0)
	i++
	d++
	if i==10
		i=0
	if d==10
		d=0
	time.sleep(0.5)

GPIO.cleanup()	
		