import serial
import picamera
from time import sleep

serial_port = '/dev/ttyACM0'                    # シリアルポート宣言。USBで通信する。
baud_rate = 9600                                # ボートレート。通信先のデバイスと同じにする。

image_path = '/home/pi/image.jpg'               # カメラ画像の保存場所

ser = serial.Serial(serial_port, baud_rate)     # シリアル通信セットアップ

camera = picamera.PiCamera()                    # カメラセットアップ

try:
    while True:         # シリアル通信が来るのを待ち続ける
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').rstrip()
            if line == '1':
                camera.capture(image_path)
                print(f"Picture taken and saved at {image_path}")
                sleep(1)  # 一秒待つ
finally:
    ser.close()
    print("シリアル通知終了")