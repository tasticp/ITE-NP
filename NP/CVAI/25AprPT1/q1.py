##########################################################################START
import cv2
import numpy as np
##########################################################################TASK1
uno = cv2.imread("uno.png", cv2.IMREAD_ANYCOLOR)
green = cv2.imread("green.png", cv2.IMREAD_ANYCOLOR)
cv2.imshow("1.Original Uno", uno)
cv2.imshow("2.Green Image", green)
##########################################################################TASK2
imHSV = cv2.cvtColor(uno, cv2.COLOR_BGR2HSV)
low_thresh = np.array([ 0,  44, 46])
high_thresh = np.array([ 179,  255, 255])
green_mask = cv2.inRange(imHSV, low_thresh, high_thresh)
cv2.imshow("3.Segmented Colour", green_mask)
##########################################################################TASK3
element = cv2.getStructuringElement(cv2.MORPH_ELLIPSE,(3,3))
close = cv2.morphologyEx(green_mask, cv2.MORPH_CLOSE, element,iterations = 0)
open = cv2.morphologyEx(close, cv2.MORPH_OPEN, element,iterations = 1)
closeT = cv2.morphologyEx(open, cv2.MORPH_CLOSE, element,iterations = 0)
cv2.imshow("4.Clean Colour", closeT)
##########################################################################TASK4
imSEG = cv2.cvtColor(uno, cv2.COLOR_BGR2HSV)
low_thresh = np.array([ 28,  79, 28])
high_thresh = np.array([ 102,  255, 198])
S_mask = cv2.inRange(imSEG, low_thresh, high_thresh)
cv2.imshow("5.Segmented Green", S_mask)
##########################################################################TASK5
element = cv2.getStructuringElement(cv2.MORPH_ELLIPSE,(3,3))
closeA = cv2.morphologyEx(S_mask, cv2.MORPH_CLOSE, element,iterations = 0)
openA = cv2.morphologyEx(closeA, cv2.MORPH_OPEN, element,iterations = 1)
closeB = cv2.morphologyEx(openA, cv2.MORPH_CLOSE, element,iterations = 0)
cv2.imshow("6.Clean Green", closeB)
##########################################################################TASK6
imgXOR = cv2.bitwise_xor(closeT, closeB)
element = cv2.getStructuringElement(cv2.MORPH_ELLIPSE,(3,3))
closeC = cv2.morphologyEx(imgXOR, cv2.MORPH_CLOSE, element,iterations = 0)
openB = cv2.morphologyEx(closeC, cv2.MORPH_OPEN, element,iterations = 1)
closeD = cv2.morphologyEx(openB, cv2.MORPH_CLOSE, element,iterations = 0)
cv2.imshow("7.Not Green Mask", closeD)
##########################################################################TASK7
comb = cv2.bitwise_and(uno, uno, mask=closeD)
cv2.imshow("1", comb)
imgNOT = cv2.bitwise_not(comb)###########################################INVERT
cv2.imshow("2", imgNOT)
comb1 = cv2.bitwise_and(uno, imgNOT)
cv2.imshow("3", comb1)
imgNOT5 = cv2.bitwise_not(comb1)#########################################INVERT
cv2.imshow("4", imgNOT5)
comb4 = cv2.bitwise_and(green, green, mask=closeD)
cv2.imshow("5", comb4)
imgNOT4= cv2.bitwise_not(comb4)##########################################INVERT
cv2.imshow("6", imgNOT4)
comb5 = cv2.bitwise_and(imgNOT5, imgNOT4)
cv2.imshow("7", comb5)
imgNOT5= cv2.bitwise_not(comb5)##########################################INVERT
cv2.imshow("8.Recolour Uno", imgNOT5)
##########################################################################TASK8
dst = cv2.Canny(imgNOT5,80,250, apertureSize = 3, L2gradient = True)
cv2.imshow("9.Edge Image", dst)
##########################################################################TASK9
sText= "kel's Green Uno"
cv2.putText(dst, sText, (50, 30), cv2.FONT_HERSHEY_SIMPLEX, 0.4, color=(255, 255, 255), thickness = 1, lineType=cv2.LINE_AA)
cv2.imshow("10.Final Image", dst)
#########################################################################TASK10
cv2.imwrite("Kelvin EdgeUno.png" ,dst)
############################################################################END
cv2.waitKey(0)
cv2.destroyAllWindows()
############################################################################END