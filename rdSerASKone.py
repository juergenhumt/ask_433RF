import serial
import time
import csv
import os
from timeit import default_timer as timer


# ser = serial.Serial('/dev/ttyACM0')
ser = serial.Serial('/dev/ttyACM1')
ser.flushInput()

k=-1;
m=0;
tStop=False


outF = open("test_data.csv","w")
tStrt = timer()

while True:
    if k < 1:
      print('Program Started!  ACM1')
    
    ser_bytes = ser.readline()
    # lst3= ser_bytes.decode().split(',')    
    lb = len(ser_bytes)
    outS = str(lb) + '  ' + str(ser_bytes)
    print(outS)
    print('\n')
    # print(lst3)

    outF.write(outS)

    if (k > 30) and tStop:
      tEnd = timer()        
      cmd = "aplay ~/Data/MorseCode/txt2morse-master/test/r.wav"
      returned_value = os.system(cmd)  # returns the exit code in unix
      print('returned value:', returned_value)
      print('dltT ' + str(tEnd-tStrt) + '  jSt ' + str(jSt))
      break

    k= k+1



    if k > 3760:
      tEnd = timer()
      cmd = "aplay ~/Data/MorseCode/txt2morse-master/test/r.wav"
      returned_value = os.system(cmd)  # returns the exit code in unix
      print('Max Count Reached!')
      print('Time dltT ',tEnd-tStrt)
      break
