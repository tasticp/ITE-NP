// Global state management
let isProcessing = false;
let currentBatchIndex = 0;
let batchDetectedImages = [];
let batchOriginalImages = [];

// Enhanced loading states and user feedback
function showLoading(element, text = "Processing...") {
  const originalContent = element.html();
  element.html(`<div class="loading-spinner"></div> ${text}`);
  element.prop("disabled", true);
  return originalContent;
}

function hideLoading(element, originalContent) {
  element.html(originalContent);
  element.prop("disabled", false);
}

function showNotification(message, type = "info") {
  const notification = $(`
        <div class="notification notification-${type} fade-in" style="
            position: fixed;
            top: 20px;
            right: 20px;
            background: ${type === "success" ? "var(--accent-color)" : type === "error" ? "var(--danger-color)" : "var(--primary-color)"};
            color: white;
            padding: 1rem 1.5rem;
            border-radius: var(--radius-md);
            box-shadow: var(--shadow-lg);
            z-index: 1000;
            max-width: 300px;
            font-weight: 500;
        ">
            <i class="fas fa-${type === "success" ? "check-circle" : type === "error" ? "exclamation-circle" : "info-circle"}"></i>
            ${message}
        </div>
    `);

  $("body").append(notification);

  setTimeout(() => {
    notification.fadeOut(300, function () {
      $(this).remove();
    });
  }, 3000);
}

// Enhanced single object detection
function singleobject() {
  if (isProcessing) {
    showNotification("Please wait for current processing to complete", "error");
    return;
  }

  const fileInput = document.createElement("input");
  fileInput.type = "file";
  fileInput.accept = "image/*";

  fileInput.onchange = function (event) {
    const file = event.target.files[0];
    if (file) {
      // Validate file type
      if (!file.type.startsWith("image/")) {
        showNotification("Please select a valid image file", "error");
        return;
      }

      // Validate file size (max 10MB)
      if (file.size > 10 * 1024 * 1024) {
        showNotification("File size must be less than 10MB", "error");
        return;
      }

      isProcessing = true;
      const formData = new FormData();
      formData.append("file", file);

      // Show loading state
      const dropZone = $("#drop-area-single");
      const originalDropZoneContent = dropZone.html();
      dropZone.html(`
                <div class="loading-spinner" style="font-size: 2rem; margin-bottom: 1rem;"></div>
                <div class="drop-zone-text">Processing your image...</div>
                <div class="drop-zone-subtext">Please wait</div>
            `);

      $.ajax({
        type: "POST",
        url: "/singleobject",
        data: formData,
        processData: false,
        contentType: false,
        success: function (response) {
          if (response.error) {
            showNotification(response.error, "error");
          } else {
            // Animate image loading
            $("#left").fadeOut(200, function () {
              $(this)
                .attr("src", "data:image/png;base64," + response.left)
                .fadeIn(300);
            });

            $("#center").fadeOut(200, function () {
              $(this)
                .attr("src", "data:image/png;base64," + response.center)
                .fadeIn(300);
            });

            $("#leftlabel").text(response.leftlabel);
            $("#centerlabel").text(response.centerlabel);

            // Animate download button appearance
            const downloadBtn = $("#download-single");
            downloadBtn.attr(
              "href",
              "data:image/png;base64," + response.center,
            );
            downloadBtn.fadeIn(300);

            showNotification("Image processed successfully!", "success");
          }
        },
        error: function (xhr, status, error) {
          showNotification(
            "Error processing image. Please try again.",
            "error",
          );
          console.error("Error:", error);
        },
        complete: function () {
          isProcessing = false;
          dropZone.html(originalDropZoneContent);
        },
      });
    }
  };

  fileInput.click();
}

// Enhanced batch processing with better progress tracking
function multipleobject() {
  if (isProcessing) {
    showNotification("Please wait for current processing to complete", "error");
    return;
  }

  const fileInput = document.createElement("input");
  fileInput.type = "file";
  fileInput.webkitdirectory = true;

  fileInput.onchange = function (event) {
    const files = event.target.files;
    if (files.length > 0) {
      // Validate files
      const imageFiles = Array.from(files).filter((file) =>
        file.type.startsWith("image/"),
      );
      if (imageFiles.length === 0) {
        showNotification(
          "No valid image files found in the selected folder",
          "error",
        );
        return;
      }

      if (imageFiles.length > 100) {
        showNotification(
          "Too many files. Please select a folder with fewer than 100 images.",
          "error",
        );
        return;
      }

      isProcessing = true;
      batchDetectedImages = [];
      batchOriginalImages = [];
      currentBatchIndex = 0;

      // Show progress bar with enhanced styling
      const progressContainer = $("#batch-progress-bar-container");
      const progressBar = $("#batch-progress-bar");
      progressContainer.fadeIn(300);
      progressBar
        .css("width", "0%")
        .find(".progress-text")
        .text("Preparing...");

      const formData = new FormData();
      for (let i = 0; i < files.length; i++) {
        formData.append("files", files[i]);
      }

      $.ajax({
        type: "POST",
        url: "/multipleobject",
        data: formData,
        processData: false,
        contentType: false,
        success: function (response) {
          if (response.error) {
            showNotification(response.error, "error");
            progressContainer.fadeOut(300);
          } else {
            showNotification(`Processing ${response.length} images...`, "info");
            displayBatchImages(response);
          }
        },
        error: function (xhr, status, error) {
          showNotification(
            "Error processing batch. Please try again.",
            "error",
          );
          progressContainer.fadeOut(300);
          console.error("Error:", error);
        },
        complete: function () {
          isProcessing = false;
        },
      });
    }
  };

  fileInput.click();
}

// Enhanced batch image display with smooth transitions
function displayBatchImages(response) {
  const progressBar = $("#batch-progress-bar");
  const progressText = progressBar.find(".progress-text");

  function displayNextImage() {
    if (currentBatchIndex < response.length) {
      const responseItem = response[currentBatchIndex];

      // Animate image transitions
      $("#left-batch").fadeOut(200, function () {
        $(this)
          .attr("src", "data:image/png;base64," + responseItem.left)
          .fadeIn(300);
      });

      $("#center-batch").fadeOut(200, function () {
        $(this)
          .attr("src", "data:image/png;base64," + responseItem.center)
          .fadeIn(300);
      });

      $("#leftlabel-batch").text(responseItem.leftlabel);
      $("#centerlabel-batch").text(responseItem.centerlabel);

      // Store for zip download
      batchOriginalImages.push("data:image/png;base64," + responseItem.left);
      batchDetectedImages.push("data:image/png;base64," + responseItem.center);

      // Update progress with smooth animation
      const percent = Math.round(
        ((currentBatchIndex + 1) / response.length) * 100,
      );
      progressBar.animate({ width: percent + "%" }, 300);
      progressText.text(
        `${percent}% (${currentBatchIndex + 1}/${response.length})`,
      );

      // Enable download buttons
      enableBatchDownload(responseItem.center);

      currentBatchIndex++;
      setTimeout(displayNextImage, 800); // Slower transition for better UX
    } else {
      // Complete batch processing
      progressBar.animate({ width: "100%" }, 300);
      progressText.text("Complete!");

      setTimeout(() => {
        $("#batch-progress-bar-container").fadeOut(300);
        enableBatchZipDownload();
        showNotification(
          `Successfully processed ${response.length} images!`,
          "success",
        );
      }, 500);
    }
  }

  displayNextImage();
}

// Enhanced zip download with better user feedback
function enableBatchZipDownload() {
  if (batchDetectedImages.length === 0) return;

  const zip = new JSZip();
  const zipBtn = $("#download-batch-zip");

  // Show loading state on zip button
  const originalZipContent = zipBtn.html();
  zipBtn.html('<div class="loading-spinner"></div> Creating ZIP...');
  zipBtn.prop("disabled", true);

  // Add detected images
  batchDetectedImages.forEach((img, i) => {
    zip.file(`detected_${i + 1}.png`, img.split(",")[1], { base64: true });
  });

  // Add original images
  batchOriginalImages.forEach((img, i) => {
    zip.file(`original_${i + 1}.png`, img.split(",")[1], { base64: true });
  });

  zip
    .generateAsync({ type: "blob" })
    .then(function (content) {
      const url = URL.createObjectURL(content);
      zipBtn.attr("href", url);
      zipBtn.html(originalZipContent);
      zipBtn.prop("disabled", false);
      zipBtn.fadeIn(300);

      showNotification("ZIP file ready for download!", "success");
    })
    .catch(function (error) {
      showNotification("Error creating ZIP file", "error");
      zipBtn.html(originalZipContent);
      zipBtn.prop("disabled", false);
    });
}

// Enhanced single download
function enableSingleDownload(base64) {
  const link = $("#download-single");
  link.attr("href", "data:image/png;base64," + base64);
  link.fadeIn(300);
}

// Enhanced batch download
function enableBatchDownload(base64) {
  const link = $("#download-batch");
  link.attr("href", "data:image/png;base64," + base64);
  link.fadeIn(300);
}

// Enhanced drag and drop with better visual feedback
$(function () {
  // Single image drag and drop
  const dropAreaSingle = $("#drop-area-single");

  dropAreaSingle.on("dragover", function (e) {
    e.preventDefault();
    e.stopPropagation();
    $(this).addClass("dragover");
  });

  dropAreaSingle.on("dragleave drop", function (e) {
    e.preventDefault();
    e.stopPropagation();
    $(this).removeClass("dragover");
  });

  dropAreaSingle.on("drop", function (e) {
    const files = e.originalEvent.dataTransfer.files;
    if (files.length > 0) {
      const file = files[0];

      // Validate file
      if (!file.type.startsWith("image/")) {
        showNotification("Please drop a valid image file", "error");
        return;
      }

      if (file.size > 10 * 1024 * 1024) {
        showNotification("File size must be less than 10MB", "error");
        return;
      }

      // Show preview with animation
      const reader = new FileReader();
      reader.onload = function (ev) {
        $("#left").fadeOut(200, function () {
          $(this).attr("src", ev.target.result).fadeIn(300);
        });
        $("#leftlabel").text("Original Image");
      };
      reader.readAsDataURL(file);

      // Process the file
      const formData = new FormData();
      formData.append("file", file);

      // Show loading state
      const originalContent = dropAreaSingle.html();
      dropAreaSingle.html(`
                <div class="loading-spinner" style="font-size: 2rem; margin-bottom: 1rem;"></div>
                <div class="drop-zone-text">Processing your image...</div>
                <div class="drop-zone-subtext">Please wait</div>
            `);

      $.ajax({
        type: "POST",
        url: "/singleobject",
        data: formData,
        processData: false,
        contentType: false,
        success: function (response) {
          if (response.error) {
            showNotification(response.error, "error");
          } else {
            $("#center").fadeOut(200, function () {
              $(this)
                .attr("src", "data:image/png;base64," + response.center)
                .fadeIn(300);
            });
            $("#centerlabel").text(response.centerlabel);
            enableSingleDownload(response.center);
            showNotification("Image processed successfully!", "success");
          }
        },
        error: function () {
          showNotification("Error processing image", "error");
        },
        complete: function () {
          dropAreaSingle.html(originalContent);
        },
      });
    }
  });

  dropAreaSingle.on("click", function () {
    singleobject();
  });

  // Batch drag and drop
  const dropAreaBatch = $("#drop-area-batch");

  dropAreaBatch.on("dragover", function (e) {
    e.preventDefault();
    e.stopPropagation();
    $(this).addClass("dragover");
  });

  dropAreaBatch.on("dragleave drop", function (e) {
    e.preventDefault();
    e.stopPropagation();
    $(this).removeClass("dragover");
  });

  dropAreaBatch.on("drop", function (e) {
    const files = e.originalEvent.dataTransfer.files;
    if (files.length > 0) {
      const imageFiles = Array.from(files).filter((f) =>
        f.type.startsWith("image/"),
      );

      if (imageFiles.length === 0) {
        showNotification("No valid image files found", "error");
        return;
      }

      if (imageFiles.length > 100) {
        showNotification(
          "Too many files. Please select fewer than 100 images.",
          "error",
        );
        return;
      }

      // Show preview of first image
      const firstImage = imageFiles[0];
      const reader = new FileReader();
      reader.onload = function (ev) {
        $("#left-batch").fadeOut(200, function () {
          $(this).attr("src", ev.target.result).fadeIn(300);
        });
        $("#leftlabel-batch").text("Original Image");
      };
      reader.readAsDataURL(firstImage);

      // Process batch
      const formData = new FormData();
      for (let i = 0; i < files.length; i++) {
        formData.append("files", files[i]);
      }

      // Show progress
      $("#batch-progress-bar-container").fadeIn(300);
      $("#batch-progress-bar")
        .css("width", "0%")
        .find(".progress-text")
        .text("Preparing...");

      $.ajax({
        type: "POST",
        url: "/multipleobject",
        data: formData,
        processData: false,
        contentType: false,
        success: function (response) {
          if (response.error) {
            showNotification(response.error, "error");
            $("#batch-progress-bar-container").fadeOut(300);
          } else {
            showNotification(`Processing ${response.length} images...`, "info");
            displayBatchImages(response);
          }
        },
        error: function () {
          showNotification("Error processing batch", "error");
          $("#batch-progress-bar-container").fadeOut(300);
        },
      });
    }
  });

  dropAreaBatch.on("click", function () {
    multipleobject();
  });

  // Enhanced tab switching with reset functionality
  $('a[data-toggle="tab"]').on("shown.bs.tab", function (e) {
    const target = $(e.target).attr("href");

    // Reset images when switching tabs
    if (target === "#single") {
      $("#left").fadeOut(200, function () {
        $(this).attr("src", "../static/empty.svg").fadeIn(300);
      });
      $("#center").fadeOut(200, function () {
        $(this).attr("src", "../static/empty.svg").fadeIn(300);
      });
      $("#leftlabel").text("Original Image");
      $("#centerlabel").text("Detected Image");
      $("#download-single").fadeOut(200);
    } else if (target === "#batch") {
      $("#left-batch").fadeOut(200, function () {
        $(this).attr("src", "../static/empty.svg").fadeIn(300);
      });
      $("#center-batch").fadeOut(200, function () {
        $(this).attr("src", "../static/empty.svg").fadeIn(300);
      });
      $("#leftlabel-batch").text("Original Image");
      $("#centerlabel-batch").text("Detected Image");
      $("#download-batch, #download-batch-zip").fadeOut(200);
      $("#batch-progress-bar-container").fadeOut(200);
    }

    // Add slide animation
    $(target).addClass("slide-in");
    setTimeout(() => $(target).removeClass("slide-in"), 300);
  });

  // Add keyboard shortcuts
  $(document).keydown(function (e) {
    // Ctrl/Cmd + S for single detection
    if ((e.ctrlKey || e.metaKey) && e.key === "s") {
      e.preventDefault();
      singleobject();
    }
    // Ctrl/Cmd + B for batch detection
    if ((e.ctrlKey || e.metaKey) && e.key === "b") {
      e.preventDefault();
      multipleobject();
    }
  });

  // Add tooltips for better UX
  $('[data-toggle="tooltip"]').tooltip();

  // Initialize with welcome message
  setTimeout(() => {
    showNotification(
      "Welcome to Knife Detection AI! Drag and drop images to get started.",
      "info",
    );
  }, 1000);
});
