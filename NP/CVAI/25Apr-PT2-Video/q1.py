import numpy as np
import cv2

# ============================================================================
# VIDEO CAPTURE SETUP
# ============================================================================
# However if wanna open existing video, use cap = cv2.VideoCapture("name of video.mp4")

# CHANGE THIS LINE TO YOUR VIDEO FILE NAME
cap = cv2.VideoCapture("birds.mp4")  # EXAM: Change to your video file ("fish.mp4" is an example)
src = cv2.imread("yellow.png", cv2.IMREAD_ANYCOLOR)
# ============================================================================
# ERROR CHECKING FOR VIDEO OPENING
# ============================================================================
# Check if camera opened successfully
if (cap.isOpened() == False):
  print("Error opening video stream or file")
  exit()

# ============================================================================
# VIDEO WRITER SETUP
# ============================================================================
# Get video frame dimensions and set up the video writer
width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
# EXAM: Change output filename and code as needed
out = cv2.VideoWriter("Kelvin-birdscount.mp4", cv2.VideoWriter_fourcc(*'mp4v'), 24, (width,height))

# ============================================================================
# MAIN VIDEO PROCESSING LOOP
# ============================================================================
# Check if camera object is opened successfully. If camera open, program will keep running in the while loop
while cap.isOpened():
  # ============================================================================
  # READ FRAME FROM VIDEO
  # ============================================================================
  # Read from the camera and save the image as frame
  ret, frame = cap.read()  
  # if frame is read correctly ret is True. If the frame cannot read exit while loop
  if not ret:  
    break
    
  # ============================================================================
  # DISPLAY ORIGINAL FRAME
  # ============================================================================
  # Display the original and processed image
  cv2.imshow('1.Original Birds', frame)
  cv2.imshow('2.Yellow Background', src)
  
  # ==============================================================================================================
  # IMAGE PROCESSING SECTION - =============PUT YOUR CODE HERE==================


  
  # ============================================================================
  # STEP 1: NOISE REDUCTION USING MEDIAN BLUR
  # ============================================================================
  # Apply median blur to reduce noise in the image
  #dstMedian = cv2.medianBlur(frame,3)    #dstMediann is needed
  #cv2.imshow('2.Clean Fish', dstMedian)
  # ============================================================================
  # STEP 2: CONVERT TO GRAYSCALE AND THRESHOLD
  # ============================================================================
  # Convert to grayscale for easier processing
  #imGRAY = cv2.cvtColor(dstMedian, cv2.COLOR_BGR2GRAY)
  # Apply binary threshold to create mask (invert colors)
  imHSV = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
  
  low_thresh = np.array([ 0,  84, 51])
  high_thresh = np.array([ 179,  255, 255])

  bird_mask = cv2.inRange(imHSV, low_thresh, high_thresh)
  cv2.imshow("3.Extracted Birds", bird_mask)

  # ============================================================================
  # STEP 3: MORPHOLOGICAL OPERATIONS FOR NOISE REMOVAL
  # ============================================================================
  # OPENING is erosion followed by dilation. It is useful in removing noise. 
  # Instead of running Erosion followed by Dilation we can just run 1 iteration of Open
  
  # Create a structuring element using cv2.getStructuringElement with a size of 3x3 and store in variable element
  element = cv2.getStructuringElement(cv2.MORPH_ELLIPSE,(3,3))
  # Apply opening operation (erosion followed by dilation)
  open1 = cv2.morphologyEx(bird_mask, cv2.MORPH_OPEN, element, iterations = 1)
  # Apply closing operation (dilation followed by erosion)
  #element = cv2.getStructuringElement(cv2.MORPH_ELLIPSE,(3,3))
  close1 = cv2.morphologyEx(open1, cv2.MORPH_CLOSE, element,iterations = 1)
  # Apply second opening operation
  #element = cv2.getStructuringElement(cv2.MORPH_ELLIPSE,(3,3))
  open2 = cv2.morphologyEx(close1, cv2.MORPH_OPEN, element, iterations = 0)

  cv2.imshow("4.Clean Birds ", open2)



  # This commented section shows a method for exchanging colors between images
  imWithoutYellow = cv2.bitwise_and(frame, frame, mask=cv2.bitwise_not(open2))  # Extract non-yellow regions from mixed image
  imyellow = cv2.bitwise_and(src, src, mask=open2)                   # Extract green/orange regions from cube image
  imCombined = cv2.bitwise_or(imWithoutYellow, imyellow)                     # Combine the two sets of regions
  cv2.imshow("5.Yellow Birds", imCombined)

  countBirds = imCombined.copy()

  # ============================================================================
  # STEP 4: CONTOUR DETECTION AND ANALYSIS
  # ============================================================================
  # Find contours in the processed image
  contours, hierarchy = cv2.findContours(open2, cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)
   
  # Loop through all detected contours
  for contour in contours:
    # it is a for loop as there may be many contours in the frame

    #==============================================
    # Calculate the area of each contour
    area = cv2.contourArea(contour)
    #==============================================
    
    #==============================================
    #cv2.drawContours(open2, [contour], contourIdx=-1, color=(0,0,255), thickness=-1)
    # Number of contours in the frame
    #noofcontours = len(contours)
    #cv2.putText(frame, f"Patch Count: {noofcontours}", (20, 280), cv2.FONT_HERSHEY_SIMPLEX, 0.5, color=(0, 0, 255), thickness = 1, lineType=cv2.LINE_AA)
    #==============================================

    #==============================================
    # EXAM: Change area threshold as needed (currently 500)
    if area > 500:                            
        # Get bounding rectangle coordinates
        x, y, w, h = cv2.boundingRect(contour)
        # Draw rectangle around detected object
        #cv2.rectangle(open2, (x, y), (x+w, y+h), color=(255, 255, 255), thickness=1)
        # Add text showing area of detected object
        
        #==============================================
        #cv2.drawContours(open2, [contour], contourIdx=-1, color=(0,0,255), thickness=-1)
        # Number of contours in the frame
        noofcontours = len(contour)
        #cv2.putText(frame, f"Patch Count: {noofcontours}", (20, 20), cv2.FONT_HERSHEY_SIMPLEX, 0.5, color=(0, 0, 255), thickness = 1, lineType=cv2.LINE_AA)
    #==============================================
        cv2.putText(countBirds, f"Birds Count: {area}", (20, 20), cv2.FONT_HERSHEY_SIMPLEX, 0.5, color=(0, 0, 255), thickness = 1, lineType=cv2.LINE_AA)
        cv2.imshow('6.Count Birds', countBirds)
    # End of for loop for drawing contours
    #==============================================
    
  # ============================================================================
  # STEP 5: CONVERT BACK TO BGR FOR VIDEO OUTPUT
  # ============================================================================
  # Convert back to BGR to be able to save output video
  #imFinal = cv2.cvtColor(countBirds, cv2.COLOR_GRAY2BGR)
  cv2.imshow('kelvin-birdscount.mp4', countBirds)
  
  # ============================================================================
  # WRITE FRAME TO OUTPUT VIDEO
  # ============================================================================
  # Write the processed frame to output video file
  out.write(countBirds)
  
  # Wait for 50ms, if "Esc" is pressed on the keyboard then exit the loop
  if cv2.waitKey(60) & 0xFF == 27:
         break
# ==============================================================================================================
# CLEANUP AND RESOURCE RELEASE
# ============================================================================
# Release the capture and close all windows
cap.release()
# EXAM: Need this to let the video close properly 
out.release()
cv2.destroyAllWindows()
