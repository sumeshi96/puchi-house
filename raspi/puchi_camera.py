import cv2

cap = cv2.VideoCapture(0,cv2.CAP_V4L2)
cap.set(cv2.CAP_PROP_FRAME_WIDTH,1280)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT,720)

def get_img():
    ret,frame = cap.read()
    cap.release()
    cap.open(0)
    cv2.imwrite("image.jpg",frame)
