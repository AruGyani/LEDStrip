from flask import Flask, render_template, request

import serial, serial.tools.list_ports
import sys
import time
import socket

app = Flask(__name__)

arduino = None

currLevel = 0.4
currColor = ""
currAnim = ""
currPal = ""


@app.route("/")
def home():
    templateData = {}
    return render_template('main.html', **templateData);

@app.route("/animation/", methods=['POST'])
def animation():
    button_name = get_btn_name(request)
    string_to_send = "{A=" + button_name + "}"

    arduino_send_cmd(string_to_send)

    return render_template('main.html')

@app.route("/brightness/", methods=['POST'])
def brightness():
    button_name = get_btn_name(request)
    string_to_send = "{B=" + button_name + "}"

    arduino_send_cmd(string_to_send)

    return render_template('main.html')

def get_btn_name(request):
    button_name = ""
    for key in request.form.keys():
        button_name = key

    return button_name


def arduino_get_resp(s):
    timeout = time.time() + 1.0
    data = b""
    while arduino.inWaiting() or time.time() - timeout < 0.0:
        if arduino.inWaiting() > 0:
            data += arduino.read(arduino.inWaiting())
            timeout = time.time() + 1.0
    return data

def arduino_send_cmd(s):
    arduino_get_resp(arduino)
    if arduino.in_waiting == 0:
        for i in s:
            arduino.write(i.encode())
            time.sleep(0.05)
    print(arduino_get_resp(arduino).decode('utf-8'))

# try to detect the USB port where Arduino is connected
def arduino_get_port():
    print("Listing ports")
    port = None
    ports = serial.tools.list_ports.comports()
    for p in ports:
        print(p)
        if "Arduino" in p[1]:
            port = p[0]
            print("Arduino detected on port", port)

    return port


def get_ip():
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    try:
        # doesn't even have to be reachable
        s.connect(('10.255.255.255', 1))
        ip = s.getsockname()[0]
    except:
        ip = '127.0.0.1'
    finally:
        s.close()
    return ip



if __name__ == "__main__":

    port = None
    
    # use the USB port name if passed
    if len(sys.argv)>1:
        port = sys.argv[1]
        print("Arduino port: " + port)

    # otherwise tries to detect the port
    # this seems to work only on Windows if Arduino USB driver is installed
    while(port==None):
        port = arduino_get_port()
        if port==None:
            print("Arduino not found. Retrying...")
            time.sleep(5);
    
    # open the serial interface
    arduino = serial.Serial(port, 9600, timeout=1)
    time.sleep(.5);
    
    print("Port", arduino)
    print("Current IP is", get_ip())
    print("Point your browser to http://", get_ip(), sep="")
    print()

    #app.run(host='0.0.0.0', port=80, debug=True)
    app.run(host='0.0.0.0', port=80)

