#include <WiFi.h>
#include <esp_now.h>

// I AM THE SENDER!!!
// ==========================================================================
// REPLACE WITH YOUR ESP RECEIVER'S MAC ADDRESS
// you the program find_mac_address in this repo to find your ESP32's MAC
// address
//
uint8_t broadcastAddress1[] = {0x ? ?, 0x ? ?, 0x ? ?, 0x ? ?, 0x ? ?, 0x ? ? };
// if you have other receivers you can define in the following
// uint8_t broadcastAddress2[] = {0xFF, , , , , };
// uint8_t broadcastAddress3[] = {0xFF, , , , , };

// ==========================================================================
// your data structure (the data block you send to receiver)
// your reciever should use the same data structure
typedef struct data_structure {
    int x;
    int y;
    bool isButtonPressed;
} data_structure;

data_structure sending_data;
const int JOY_STICK_VRX = 34;
const int JOY_STICK_VRY = 35;
const int PUSH_BUTTON = 18;

//=============================================================================
//
#include "Arduino.h"

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    char macStr[18];
    Serial.print("Packet to: ");
    // Copies the sender mac address to a string
    snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
             mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4],
             mac_addr[5]);
    Serial.print(macStr);
    Serial.print(" send status:\t");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success"
                                                  : "Delivery Fail");
}

void setup() {
    pinMode(JOY_STICK_VRX, INPUT);
    pinMode(JOY_STICK_VRY, INPUT);
    pinMode(PUSH_BUTTON, INPUT_PULLUP);
    Serial.begin(115200);

    WiFi.mode(WIFI_STA);

    if(esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    esp_now_register_send_cb(OnDataSent);

    // register peer
    esp_now_peer_info_t peerInfo;
    peerInfo.channel = 0;
    peerInfo.encrypt = false;
    // register first peer
    memcpy(peerInfo.peer_addr, broadcastAddress1, 6);
    if(esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Failed to add peer");
        return;
    }
}

//  MAIN LOOP
void loop() {
    float x_axis = analogRead(JOY_STICK_VRX);
    float y_axis = analogRead(JOY_STICK_VRY);
    int sw = digitalRead(PUSH_BUTTON);
    int axis_max = 4095;
    // Convert joy stick value from -45 to 45
    x_axis = (x_axis - axis_max / 2) / 22.76;
    y_axis = (y_axis - axis_max / 2) / 22.76;

    Serial.print("X_axis: ");
    Serial.print(x_axis, 0); // round off to the first dicimal place
    Serial.print("\n");
    Serial.print("Y-axis: "); // round off to the first dicimal place
    Serial.print(y_axis, 0);
    Serial.print("\n");
    Serial.print("SW: ");
    Serial.print(sw);
    Serial.print("\n\n");
    sending_data.isButtonPressed = sw;
    sending_data.x = x_axis;
    sending_data.y = y_axis;
    //
    esp_err_t result =
        esp_now_send(0, (uint8_t *)&sending_data, sizeof(data_structure));

    if(result == ESP_OK) {
        Serial.println("Sent with success");
    } else {
        Serial.println("Error sending the data");
    }
    delay(100);
}
//=============================================================================
// END
