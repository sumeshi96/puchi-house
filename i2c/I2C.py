import smbus
import time

bus = smbus.SMBus(1)
address = 0x08

def receiveBooleanData():
    try:
        byte = bus.read_byte(address)
        return byte != 0  # 0以外の値をTrueとして解釈
    except IOError:
        return False

print("start")
while True:
    booleanData = receiveBooleanData()
    print("Received:", booleanData)
    time.sleep(1)
