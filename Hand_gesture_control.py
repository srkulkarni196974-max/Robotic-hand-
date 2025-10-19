from cvzone.HandTrackingModule import HandDetector
from cvzone.SerialModule import SerialObject
import cv2
import time
import serial


cap = cv2.VideoCapture(0)
detector = HandDetector(detectionCon=0.8, maxHands=2)
#arduino = SerialObject(portNo="COM6", baudRate=9600)

# Initialize serial connection
arduino = serial.Serial(port='COM6', baudrate=9600, timeout=2)  # Update COM port as per your setup
time.sleep(2)  # Allow time for Arduino to reset
while True:
    success, img = cap.read()
    hands, img = detector.findHands(img)
    if hands:
        hand1 = hands[0]
        lmList1 = hand1["lmList"]
        bbox1 = hand1["bbox"]
        centerPoint1 = hand1['center']
        handType1 = hand1["type"]
        fingers1 = detector.fingersUp(hand1)
        data_string = ','.join(map(str, fingers1)) + '\n'  # '\n' indicates end of data
        print(fingers1)
        arduino.write(data_string.encode())
    cv2.imshow("Image", img)
    if cv2.waitKey(1) == ord('q'):
        break
cap.release()