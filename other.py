import serial, time

ser = serial.Serial('COM5', baudrate=9600, timeout=1)
print('Established serial connection to Arduino')

while True:
    # ser.write(b"5")
    arduino_data = ser.readline()

    decoded_values = str(arduino_data[0:len(arduino_data)].decode("utf-8"))
    list_values = decoded_values.split('x')
    print('data: ', list_values)

    time.sleep(1)

print('stop')