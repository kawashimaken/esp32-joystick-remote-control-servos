# esp32-joystick-remote-control-servos


# what is this?

Take a look at description YouTube video click the picture below or click the link here [https://www.youtube.com/watch?v=qa2ixbKXAfQ]

[![](https://img.youtube.com/vi/qa2ixbKXAfQ/0.jpg)](https://www.youtube.com/watch?v=qa2ixbKXAfQ)

# folder description

* esp_now_joystick_tx : sender platformio project
* esp_now_joystick_rx : receiver platformio project


# you need to do

## This is using VSCode + platformio, you need to be familiar with platformio

## libraries you need

find them in eache platformio.ini file

## run the program find_mac_address first to find your ESP32(receiver)'s MAC address.

* and update your sender program at this line: https://github.com/kawashimaken/esp32_rotary_encoder_remote_control_esp_now/blob/a5bf81c22f3a6ad942069baa669a640d292a9f80/esp_now_sender/src/main.cpp#L7

## IMPORTANT:you need to make sure the serial port configuration is updated to yours!
change accordingly in your platformio.ini file

