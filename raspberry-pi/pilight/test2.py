import time
import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BOARD)
GPIO.setup(7, GPIO.OUT)
class test:
	def method(self):
		p = GPIO.PWM(7, 50)  # channel=12 frequency=50Hz
		p.start(0)
		try:
		    while 1:
		        for dc in range(0, 101, 5):
		            p.ChangeDutyCycle(dc)
		            time.sleep(0.1)
		        for dc in range(100, -1, -5):
		            p.ChangeDutyCycle(dc)
		            time.sleep(0.1)
		except KeyboardInterrupt:
		    pass
		p.stop()
		GPIO.cleanup()

test = test()	
test.method()