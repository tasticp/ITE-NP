import cv2
import numpy as np


img = cv2.imread("lenna.jpg", cv2.IMREAD_ANYCOLOR)
cv2.imshow("Original", img)


print(img.dtype)
print(img.shape)
print(img.shape[2])
print(img.size)


cv2.waitKey(0)
cv2.destroyAllWindows()