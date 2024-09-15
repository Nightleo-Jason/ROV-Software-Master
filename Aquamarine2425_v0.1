import pygame
import sys

# Initialize Pygame
pygame.init()

# Set up display with a size of 1023x1023

window = pygame.display.set_mode((2240, 800))

graphSize = 512
graphSurface = pygame.Surface((graphSize, graphSize))
graphPosition = (1500,200)
pygame.display.set_caption("This took half a day's worth of life away from me")

# Colors
white = (255, 255, 255)
black = (0, 0, 0)
red = (255, 0, 0)
gray = (170, 170, 170)
Lgray = (200,200,200)

deadzoneHor = (450,574)
deadzoneVer = (400,624)

import serial
import time

ser = serial.Serial('/dev/tty.usbserial-1220', baudrate = 9600, timeout = 1)
time.sleep(3)


numPoints = 5
dataList = [0]*numPoints

def getValues():
    ser.write(b'g')
    arduinoData = ser.readline().decode().split('\r\n')

    return arduinoData[0]

# Function to draw the grid
def draw_grid():
    
    mult = graphSize/1024
    
    horMin = deadzoneHor[0]*mult
    horMax = (deadzoneHor[1]-deadzoneHor[0])*mult
    
    verMin = deadzoneVer[0]*mult
    verMax = (deadzoneVer[1]-deadzoneVer[0])*mult
    
    graphSurface.fill(white)

    gray_out_area(Lgray, graphSize, horMin, horMax, verMin, verMax)
    # Draw minor gridlines
    for i in range(0, graphSize, int(64*mult)):
        pygame.draw.line(graphSurface, gray, (i, 0), (i, graphSize))
        pygame.draw.line(graphSurface, gray, (0, i), (graphSize, i))

    # Draw axes
    pygame.draw.line(graphSurface, black, (0, graphSize // 2), (graphSize, graphSize // 2), 1)
    pygame.draw.line(graphSurface, black, (graphSize // 2, 0), (graphSize // 2, graphSize), 1)
    
def getArduino():
    for i in range(0,numPoints):
        data = getValues()
        dataList[i] = data

    return(dataList)
  
    
    

# Function to gray out specific areas
def gray_out_area(colour, size, H_dzMin, H_dzMax, V_dzMin, V_dzMax):
    pygame.draw.rect(graphSurface, colour, (0, H_dzMin, size, H_dzMax))
    pygame.draw.rect(graphSurface, colour, (V_dzMin,0 , V_dzMax, size))

# Function to draw the point
def draw_dot(x, y):
    mult = graphSize/1024
    pygame.draw.circle(graphSurface, red, (x*mult, y*mult), 5)

# Main loop
def main():
    x, y = 0, 512  # Example starting point

    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        #x = (x + 1) % size
        window.fill(white)
        draw_grid()
        draw_dot(int(dataList[0]),int(dataList[0]))
        window.blit(graphSurface, graphPosition)
        
        
        #draw_point(x, y)
        pygame.display.flip()
        #pygame.time.delay(100)
        
        getArduino()
        print(dataList[0])
            

    pygame.quit()
    sys.exit()

if __name__ == "__main__":
    main()


