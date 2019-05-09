import serial #import the serial library
from visual import * #import everything from visual

arduinoSerialData = serial.Serial('com5',9600)#Create an object to read serial port

while(1):
    if(arduinoSerialData.inWaiting()>0):    #check for data
        myData=arduinoSerialData.readline() #if data is there then read it
          
        distance = float(myData)            #convert string myData to floating point no. and hold it in distance variable
        print distance
