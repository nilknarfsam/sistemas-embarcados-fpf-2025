import serial
from time import sleep


if __name__ == '__main__':
  try:
    ser = serial.Serial('COM5', 4800)
    sleep(2)
    while True:
      byte_list = []
      bytes_quantity = int(input("Digite a quantidade de bytes: "))
      for i in range(bytes_quantity):
        byte = int(input("Digite o byte {}: ".format(i + 1)))
        byte_list.append(byte)  
      value = bytearray(byte_list)
      ser.write(value)
      print("Mensagem enviada: {}".format(byte_list))
  except KeyboardInterrupt:
    print("\nFinalizando...")
    ser.close()