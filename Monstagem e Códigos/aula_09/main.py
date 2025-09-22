import serial
from time import sleep

if __name__ == '__main__':
  
  ser = serial.Serial('COM20', baudrate=115200, timeout=1.0)
  sleep(2)
  x = ser.read_until('\n') 
  
  try:
    while True:
      ser.write(b'Raphael\n')
      x = ser.read_until('\n') 
      print(x.decode('utf8'))
      sleep(2) 
  except KeyboardInterrupt:
    ser.close()
  