import serial
import time

ser = serial.Serial('/dev/tty.usbmodem1301', baudrate = 9600, timeout = 1)


numPoints = 5
dataList = [0]*numPoints

def getValues():
    ser.write(b'g')
    arduinoData = ser.readline().decode().split('\r\n')

    return arduinoData[0]

while (1):

    userInput = input("Get data points?")

    if userInput == 'y':
        for i in range(0,numPoints):
            data = getValues()
            dataList[i] = data

        print(dataList)
