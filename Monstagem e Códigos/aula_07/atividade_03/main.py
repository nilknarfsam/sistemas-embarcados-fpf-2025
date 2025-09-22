import time
import serial

if __name__ == '__main__':
  ser = serial.Serial('COM7', 9600)
  time.sleep(2)
  # a = 923
  # b_lsb = int(a % 256)
  # b_msb = int(a / 256)
  # print(b_msb)
  # print(b_lsb)
  # c = b_msb*256 + b_lsb
  # print(c)
  try:
    while True:
      value = int(input("Digite um valor: "))
      ser.write(bytearray([value]))
  except KeyboardInterrupt:
    print('\nFinalizado')
    ser.close() 
  
  
  