#!flask/bin/python
from flask import Flask, jsonify, make_response, request

import RPi.GPIO as GPIO

app = Flask(__name__)

class test:
    # Pins for the GPIO
    RED_PIN = 7
    GREEN_PIN = 11
    BLUE_PIN = 12
    GPIO.cleanup()
    GPIO.setmode(GPIO.BOARD)
    GPIO.setup(RED_PIN, GPIO.OUT)
    GPIO.setup(BLUE_PIN, GPIO.OUT)
    GPIO.setup(GREEN_PIN, GPIO.OUT)
    
   
    
    p = GPIO.PWM(BLUE_PIN, 100)  # channel=12 frequency=50Hz
    p.start(0)
    
    p = GPIO.PWM(GREEN_PIN, 100)  # channel=12 frequency=50Hz
    p.start(0)
    
    p = GPIO.PWM(RED_PIN, 200)  # channel=12 frequency=50Hz
    p.start(0)
    
    def update_colors(self):
        print "Updating!"
        color = filter(lambda t: t['id'] == self.RED_PIN, colors)
        #p = GPIO.PWM(7, 100)  # channel=12 frequency=50Hz
        self.p.ChangeDutyCycle(color[0]['intensity'])

test = test()

colors = [
    {
        'id' : 7,
        'name': 'RED',
        'intensity': 0.0
    },
    {
        'id' : 11,
        'name' : 'GREEN',
        'intensity': 0.0
   	},
    {
        'id' : 12,
        'name' : 'BLUE',
        'intensity': 0.0
    }
]

@app.route('/pilight/api/color', methods = ['GET'])
def get_colors():
    return jsonify( { 'colors': colors } )

@app.route('/pilight/api/color', methods = ['PUT'])
def set_color():
    if not request.json or not 'name' in request.json or not 'intensity' in request.json:
        abort(400)
	
    color = filter(lambda t: t['name'] == request.json['name'], colors)	
	
    if len(color) == 0:
        abort(404)

    color[0]['intensity'] = request.json.get('intensity', color[0]['intensity'])
    
    test.update_colors()
    
    return jsonify( { 'colors': color } ), 200

if __name__ == '__main__':
    app.run(debug = True, host='0.0.0.0')
    
   
    