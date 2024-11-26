# IOT-irrigation-system

**ERRORS OCCURED:**
  1.  A fatal error occurred: Failed to connect to ESP32: Wrong boot mode detected (0x13)! The chip needs to be in download mode.
      For troubleshooting steps visit: https://docs.espressif.com/projects/esptool/en/latest/troubleshooting.html
      Failed uploading: uploading error: exit status 2

SOLUTION:
    Check BOOT Mode:
    ESP32 needs to be in flash mode to upload the code. Typically, this involves:
    Press and hold the BOOT button (if your ESP32 board has one).
    Click the Upload button in the Arduino IDE.
    Release the BOOT button once the upload starts.

**OUTPUT:**

Attempting to connect
Connected.
The soil moisture is WET => deactivate the pump (66%)
Channel update successful.
The soil moisture is WET => deactivate the pump (65%)
Channel update successful.
The soil moisture is DRY => activate pump (0%)
Channel update successful.
The soil moisture is WET => deactivate the pump (62%)
