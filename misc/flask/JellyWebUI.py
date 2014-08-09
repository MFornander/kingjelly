from flask import Flask, render_template, request, jsonify
from struct import *
import socket

app = Flask(__name__)

value = [0,0,0,0,0,0,0,0]

def sendPacket():
    HOST = 'localhost'    # The remote host
    PORT = 30000              # The same port as used by the server
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    msg = pack('!????BBBB', *value) 
    s.sendto(msg,(HOST, PORT))
    s.close
    #print value


# return index page when IP address of RPi is typed in the browser
@app.route("/")
def Index():
    return render_template("index.html", uptime=GetUptime())

# ajax GET call this function to set state
# depending on the GET parameter sent
@app.route("/_left")
def _switch_left():
    state = request.args.get('state')
    value[0] = int(state)
    sendPacket()
    return ""
    
@app.route("/_right")
def _switch_right():
    state = request.args.get('state')
    value[1] = int(state)
    sendPacket()
    return ""

@app.route("/_up")
def _switch_up():
    state = request.args.get('state')
    value[2] = int(state)
    sendPacket()
    return ""

@app.route("/_down")
def _switch_down():
    state = request.args.get('state')
    value[3] = int(state)
    sendPacket()
    return ""

# find a way to do this with a variable
@app.route("/_pot0")
def _pot0():
    state = request.args.get('state')
    value[4] = int(state)
    sendPacket()
    return ""

@app.route("/_pot1")
def _pot1():
    state = request.args.get('state')
    value[5] = int(state)
    sendPacket()
    return ""

@app.route("/_pot2")
def _pot2():
    state = request.args.get('state')
    value[6] = int(state)
    sendPacket()
    return ""

@app.route("/_pot3")
def _pot3():
    state = request.args.get('state')
    value[7] = int(state)
    sendPacket()
    return ""


# ajax GET call this function periodically to read button state
# the state is sent back as json data
#@app.route("/_button")
#def _button():
#    if Pins.ReadButton():
#        state = "pressed"
#    else:
#        state = "not pressed"
#    return jsonify(buttonState=state)

def GetUptime():
    # get uptime from the linux terminal command
    from subprocess import check_output
    output = check_output(["uptime"])
    # return only uptime info
    uptime = output[output.find("up"):output.find("user")-4]
    return uptime
    
# run the webserver on standard port 80, requires sudo
if __name__ == "__main__":
    #Pins.Init()
    app.run(host='0.0.0.0', port=8080, debug=True)