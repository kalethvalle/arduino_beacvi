import serial, time
from pathlib import Path
from pygame import mixer  # Load the popular external library

# variables globales
path = './audio/'
uid_compare = ''

# se establece conexion con el monitor serial de arduino
ser = serial.Serial('COM5', baudrate=9600, timeout=1)
print('Established serial connection to Arduino')

while True:
    # ser.write(b"5")
    arduino_data = ser.readline()

    decoded_values = str(arduino_data[0:len(arduino_data)].decode("utf-8"))
    list_values = decoded_values.split(' ')

    uid = ''
    for concat in list_values:
        uid += concat

    if uid:
       print(uid)
    #    se valida si existe el mp3 para poder ser reproducido
       file_true = Path(path + str(uid) + '.mp3').is_file()

       mixer.init()

       if file_true:
          mixer.music.load(path + str(uid) + '.mp3')

          if uid_compare != uid:
             uid_compare = uid
             mixer.music.play()
          else:
             uid_compare = ''
             mixer.music.stop()
       else:
           uid_compare = ''
           mixer.music.stop()

    time.sleep(0.01)

print('stop')