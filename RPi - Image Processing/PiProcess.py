# import the necessary packages
from picamera import PiCamera
from picamera.array import PiRGBArray
from PiVideoStream import PiVideoStream
import numpy as np
import time
import cv2

def nothing(x):
    pass

def auto_canny(image, Canny_sigma, GaussBlur_Kernel, GaussBlur_Stdev):
    # compute the median of the single channel pixel intensities
    v = np.median(image)

    # apply automatic Canny edge detection using the computed median
    lower = int(max(0, (1.0 - Canny_sigma) * v))
    upper = int(min(255, (1.0 + Canny_sigma) * v))
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    blurred = cv2.GaussianBlur(gray, (GaussBlur_Kernel, GaussBlur_Kernel), GaussBlur_Stdev)
    edged = cv2.Canny(blurred, lower, upper, True)

    # return the edged image
    return edged

cv2.namedWindow("Image", cv2.WINDOW_AUTOSIZE)

#Create trackbar
cv2.createTrackbar("Auto Canny Sigma", "Image", 33, 100, nothing)
cv2.createTrackbar("Gauss Blur Kernel", "Image", 3, 100, nothing)
cv2.createTrackbar("Gauss Blur X Stdev", "Image", 0, 100, nothing)

#Initialize PiCamera
cam = PiVideoStream().start()

#Warm up camera
time.sleep(1)

pause = False
while(1):
    #Grab frame
    if(not pause):
        image = cam.read()

    #Update our parameters
    trackBarCanny_sigma = cv2.getTrackbarPos("Auto Canny Sigma", "Image")
    trackBarGaussBlur_Kernel = cv2.getTrackbarPos("Gauss Blur Kernel", "Image")
    trackBarGaussBlur_Stdev = cv2.getTrackbarPos("Gauss Blur X Stdev", "Image")

    k = cv2.waitKey(1) & 0XFF

    if(k == 27):
        break

    elif(k == 32 and (not pause)):
        pause = True

    elif(k == 32 and pause):
        pause = False

    if (trackBarGaussBlur_Kernel != 0):
        #Process our image
        cv2.imshow("Image", auto_canny(image, trackBarCanny_sigma / 100, trackBarGaussBlur_Kernel * 2 - 1,
                                       trackBarGaussBlur_Stdev / 100))

cam.stop()
cv2.destroyAllWindows()