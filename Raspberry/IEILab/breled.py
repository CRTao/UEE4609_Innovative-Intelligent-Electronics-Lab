import time
import RPi.GPIO as GPIO
led_pin = 12
#up 6

GPIO.setmode(GPIO.BCM)
GPIO.setup(led_pin, GPIO.OUT)

pwm_led = GPIO.PWM(led_pin, 200)
pwm_led.start(10)

while True:
	for duty in range(10):
   		pwm_led.ChangeDutyCycle(duty)
		time.sleep(0.2)
	for deey in range(10):
		pwm_led.ChangeDutyCycle(10-deey)
		time.sleep(0.2)

GPIO.cleanup()

