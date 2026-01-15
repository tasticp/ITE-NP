// ============================================================================
// JAVASCRIPT FILE - AJAX REQUESTS FOR IMAGE PROCESSING
// ============================================================================
// This function sends a POST request to the Flask backend to get processed images
// and updates the HTML page with the results
function extractJam() {
    // ============================================================================
    // AJAX POST REQUEST TO FLASK BACKEND
    // ============================================================================
    // Send a POST request to the /routename endpoint
    $.ajax({
        type: "POST",                    // HTTP method
        url: "/extractJam",               // Flask route endpoint
        success: function(response) {
            // ============================================================================
            // UPDATE HTML IMAGES WITH BASE64 ENCODED IMAGES FROM PYTHON RESPONSE  // Convert base64 string to image source for its Image
            // ============================================================================
            $('#imLeft').attr('src', 'data:image/png;base64,' + response.imLeft ); 
            $('#imCenter').attr('src', 'data:image/png;base64,' + response.imCenter );
            $('#imRight').attr('src', 'data:image/png;base64,' + response.imRight );
            
            // ============================================================================
            // UPDATE LABEL TEXT WITH RESPONSE LABELS // Update the label text for its image
            // ============================================================================
            $('#txtLeft').text(response.txtLeft );
            $('#txtCenter').text(response.txtCenter );
            $('#txtRight').text(response.txtRight );
        },
        // ============================================================================
        // ERROR HANDLING
        // ============================================================================
        // Display an alert if there is an error in processing
        error: function() {
            alert('Error in Processing');
        }
    });
}


function replaceJam() {
    // ============================================================================
    // AJAX POST REQUEST TO FLASK BACKEND
    // ============================================================================
    // Send a POST request to the /routename endpoint
    $.ajax({
        type: "POST",                    // HTTP method
        url: "/replaceJam",               // Flask route endpoint
        success: function(response) {
            // ============================================================================
            // UPDATE HTML IMAGES WITH BASE64 ENCODED IMAGES FROM PYTHON RESPONSE  // Convert base64 string to image source for its Image
            // ============================================================================
            $('#imLeft').attr('src', 'data:image/png;base64,' + response.imLeft ); 
            $('#imCenter').attr('src', 'data:image/png;base64,' + response.imCenter );
            $('#imRight').attr('src', 'data:image/png;base64,' + response.imRight );
            
            // ============================================================================
            // UPDATE LABEL TEXT WITH RESPONSE LABELS // Update the label text for its image
            // ============================================================================
            $('#txtLeft').text(response.txtLeft );
            $('#txtCenter').text(response.txtCenter );
            $('#txtRight').text(response.txtRight );
        },
        // ============================================================================
        // ERROR HANDLING
        // ============================================================================
        // Display an alert if there is an error in processing
        error: function() {
            alert('Error in Processing');
        }
    });
}