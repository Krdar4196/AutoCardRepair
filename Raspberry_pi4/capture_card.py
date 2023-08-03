import serial
import picamera
from time import sleep

serial_port = '/dev/ttyACM0'                    # シリアルポート宣言。USBで通信する。
baud_rate = 9600                                # ボートレート。通信先のデバイスと同じにする。

image_path = '/home/pi/image.jpg'               # カメラ画像の保存場所

ser = serial.Serial(serial_port, baud_rate)     # シリアル通信セットアップ

camera = picamera.PiCamera()                    # カメラセットアップ


def get_next_filename(directory):
    if not os.path.exists(directory):
        os.makedirs(directory)
    files = os.listdir(directory)
    if files:
        last_file = max(files, key=lambda x : int(x.rstrip('.jpg')))
        next_num = int(last_file.rstrip('.jpg')) + 1
    else:
        next_num = 0
    return os.path.join(directory, f"{next_num}.jpg")


try:
    while True:         # シリアル通信が来るのを待ち続ける
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').rstrip()
            if line == '1':
                camera.capture(get_next_filename)
                print(f"Picture taken and saved at {image_path}")
                sleep(1)  # 一秒待つ
finally:
    ser.close()
    print("シリアル通知終了")