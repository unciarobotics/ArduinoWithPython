import serial                                   #import the serial library
from visual import *                            #import everything from visual

arduinoSerialData = serial.Serial('com34',9600)  #Create an object to read serial port
measuringRod=cylinder(length=10,color=color.yellow, radius=.5, pos=(-3,0,0))

lengthLabel = label(text='Target Distance is: ',pos =(0,3,0),height=30, box=false)
while(1):
    rate(20)                                    #20 times a second
    if(arduinoSerialData.inWaiting()>0):        #check for data
        myData=arduinoSerialData.readline()     #if data is there then read it
          
        distance = float(myData)                #convert string myData to floating point no. and hold it in distance variable
        print distance
        myLabel= 'Target Distance is: '+ myData
        lengthLabel.text=myLabel
        measuringRod.length=distance
