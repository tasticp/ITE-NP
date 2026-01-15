
from flask import Flask, render_template, jsonify
import cv2
import numpy as np
import base64

# Initialize Flask application
app = Flask(__name__, template_folder="templates", static_folder="static")

# Route for the main page
@app.route('/')
def index():
    return render_template('index.html')


# Read Original Image in AnyColor
mix = cv2.imread('./static/MixBiscuit.png',cv2.IMREAD_ANYCOLOR)
star = cv2.imread('./static/StarBiscuit.png',cv2.IMREAD_ANYCOLOR)
plain = cv2.imread('./static/PlainBiscuit.png',cv2.IMREAD_ANYCOLOR)

# Convert image to Base64 encoding
def to_base64(img):
    _, buffer = cv2.imencode('.png', img)
    img_base64 = base64.b64encode(buffer).decode('utf-8')
    return img_base64


# Type new routes below
@app.route('/extractJam', methods=['POST'])
def extractJam():
  
  
  global clean_green, clean_blue

  imHSV = cv2.cvtColor(mix, cv2.COLOR_BGR2HSV)      # Convert original image
  
  
  low_thresh = np.array([ 29,  103, 0])
  high_thresh = np.array([ 89,  255, 170])

  green_mask  = cv2.inRange(imHSV, low_thresh, high_thresh)

  imHSV1 = cv2.cvtColor(mix, cv2.COLOR_BGR2HSV)      # Convert original image
  
  low_thresh = np.array([ 61,  177, 0])
  high_thresh = np.array([ 164,  255, 178])

  blue_mask   = cv2.inRange(imHSV1, low_thresh, high_thresh)


  # ============================================================================
  # MORPHOLOGICAL OPERATIONS FOR NOISE REDUCTION
  # ============================================================================
  # Create elliptical structuring element for morphological operations
  element = cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (3, 3))
  
  # Perform closing operation (dilation followed by erosion)
  # This fills small holes and connects nearby regions
  imClose = cv2.morphologyEx(green_mask, cv2.MORPH_CLOSE, element, iterations=1)
  imClose1 = cv2.morphologyEx(blue_mask, cv2.MORPH_CLOSE, element, iterations=1)

  
  # Perform opening operation (erosion followed by dilation)
  # This removes small noise and smooths object boundaries
  clean_green = cv2.morphologyEx(imClose, cv2.MORPH_OPEN, element, iterations=1)
  clean_blue = cv2.morphologyEx(imClose1, cv2.MORPH_OPEN, element, iterations=1)

  cleanGreenDisplay  = clean_green.copy()    # Copy for mixing operations
  cleanBlueDisplay   = clean_blue.copy()    # Copy for mixing operations

  # ============================================================================
  # TEXT OVERLAY ON PROCESSED IMAGE
  # ============================================================================
  # Add text overlay to the cleaned image
  sText= "Kelvin's Clean Green Jam"
  cv2.putText(cleanGreenDisplay, sText, (20, 20), cv2.FONT_HERSHEY_SIMPLEX, 0.4, color=(255, 255, 255), thickness = 1, lineType=cv2.LINE_AA)

  sText= "Kelvin's Clean Blue Jam"
  cv2.putText(cleanBlueDisplay, sText, (20, 20), cv2.FONT_HERSHEY_SIMPLEX, 0.4, color=(255, 255, 255), thickness = 1, lineType=cv2.LINE_AA)

  
 

  # Return the original and resized frames as Base64-encoded images and update the labels
  return jsonify({
     'imLeft ': to_base64(mix), 
     'imCenter': to_base64(cleanGreenDisplay),
     'imRight': to_base64(cleanBlueDisplay),
     'txtLeft': 'Mix Biscuit',
     'txtCenter': 'Clean Green Jam',
     'txtRight': 'Clean Blue Jam'
    })  

# Type new routes below
@app.route('/replaceJam', methods=['POST'])
def replaceJam():
 
  global clean_green, clean_blue
  extractJam() 


  imWithoutGreen = cv2.bitwise_and(plain, plain, mask=cv2.bitwise_not(clean_green))  # Extract non-yellow regions from mixed image
  imWithoutBlue = cv2.bitwise_and(plain, plain, mask=cv2.bitwise_not(clean_blue))  # Extract non-yellow regions from mixed image
  
  
  
  imCombined = cv2.bitwise_or(imWithoutBlue, imWithoutGreen)                     # Combine the two sets of regions
  replaced_plain = cv2.bitwise_and(mix, mix, mask=clean_green)                   # Extract green/orange regions from cube image

  imWithoutGreen = cv2.bitwise_and(mix, mix, mask=cv2.bitwise_not(clean_green))  # Extract non-yellow regions from mixed image
  imWithoutBlue = cv2.bitwise_and(plain, plain, mask=cv2.bitwise_not(clean_blue))  # Extract non-yellow regions from mixed image
  
  imCombined = cv2.bitwise_or(imWithoutBlue, imWithoutGreen)                     # Combine the two sets of regions
  replaced_star = cv2.bitwise_and(mix, mix, mask=clean_blue) 

  # ============================================================================
  # TEXT OVERLAY ON PROCESSED IMAGE
  # ============================================================================
  # Add text overlay to the cleaned image
  sText1= "Kelvin's Plain Biscuit"
  cv2.putText(replaced_plain, sText1, (20, 20), cv2.FONT_HERSHEY_SIMPLEX, 0.4, color=(255, 255, 255), thickness = 1, lineType=cv2.LINE_AA)
  
  sText2= "Kelvin's Mix Star Biscuit"
  cv2.putText(replaced_star, sText2, (20, 20), cv2.FONT_HERSHEY_SIMPLEX, 0.4, color=(255, 255, 255), thickness = 1, lineType=cv2.LINE_AA)
  


  cv2.imwrite("Kelvin-Plain Biscuit.png" ,replaced_plain)
  cv2.imwrite("Kelvin-Mix Star Biscuit.png" ,replaced_star)
  
 

  # Return the original and resized frames as Base64-encoded images and update the labels
  return jsonify({
     'imLeft': to_base64(mix), 
     'imCenter': to_base64(replaced_plain),
     'imRight': to_base64(replaced_star),
     'txtLeft': 'Mix Biscuit',
     'txtCenter': 'Replaced Plain Biscuit',
     'txtRight': 'Replaced Star Biscuit'
    })  




# Run the Flask application
if __name__ == '__main__':
    app.run(host='0.0.0.0', port='5000')
    # app.run(debug=True)

