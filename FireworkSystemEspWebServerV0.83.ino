#include <WiFi.h>
#include <WebServer.h>

// Wi-Fi credentials
const char* ssid = "FireworkSystem";
const char* password = "password123";

// Create a web server object on port 80
WebServer server(80);

// GPIO pins for channels
#define FIRE_CHANNEL_1_PIN 4
#define FIRE_CHANNEL_2_PIN 5
#define FIRE_CHANNEL_3_PIN 18
#define FIRE_CHANNEL_4_PIN 19
#define ONBOARD_LED_PIN 2 // Onboard LED

bool testMode = false; // Test mode flag

// Full HTML Page
const char htmlPage[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Firework Control</title>
    <style>
        body { font-family: Arial, sans-serif; text-align: center; margin: 0; padding: 0; background-color: #2C2C2C; color: #EAEAEA; }
        .container { max-width: 600px; margin: 20px auto; padding: 20px; background: #1E1E1E; box-shadow: 0 4px 10px rgba(0, 0, 0, 0.4); border-radius: 12px; }
        .status-bar { display: flex; justify-content: space-between; align-items: center; padding: 10px 20px; background-color: #121212; border-radius: 10px; margin-bottom: 20px; }
        .status-bar span { font-size: 18px; font-weight: bold; }
        .connected { color: #4CAF50; }
        .disconnected { color: #FF5252; }
        h1 { font-size: 28px; margin-bottom: 20px; color: #FFA726; }
        .checkbox { display: flex; align-items: center; justify-content: center; margin: 20px 0; }
        .checkbox input { display: none; }
        .checkbox label { position: relative; cursor: pointer; font-size: 18px; padding-left: 35px; color: #EAEAEA; }
        .checkbox label::before { content: ""; position: absolute; top: 0; left: 0; width: 20px; height: 20px; border: 2px solid #FFA726; border-radius: 3px; background: #1E1E1E; transition: 0.2s; }
        .checkbox input:checked + label::before { background: #FFA726; }
        .checkbox input:checked + label::after { content: ""; position: absolute; left: 7px; top: 3px; width: 6px; height: 12px; border: solid #2C2C2C; border-width: 0 2px 2px 0; transform: rotate(45deg); }
        .button-grid { display: grid; grid-template-columns: 1fr 1fr; gap: 15px; }
        button { padding: 15px 20px; font-size: 16px; border: none; border-radius: 8px; cursor: pointer; }
        button.fire { background-color: #FFA726; color: #1E1E1E; }
        button.fire:hover { background-color: #FF8C00; }
        button.fired { background-color: #4CAF50; color: white; }
        .status { font-size: 16px; margin: 15px 0; color: #FFA726; }
    </style>
</head>
<body>
    <div class="container">
        <div class="status-bar">
            <span>ESP32 Status:</span>
            <span id="connectionStatus" class="disconnected">Disconnected</span>
        </div>
        <div class="status-bar">
            <span>Signal Strength:</span>
            <span id="signalStrength">N/A</span>
        </div>
        <div class="status-bar">
            <span>Delay (ms):</span>
            <span id="delayTime">N/A</span>
        </div>
        <h1>Firework Control</h1>
        <div class="checkbox">
            <input type="checkbox" id="testModeCheckbox" onchange="toggleTestMode()">
            <label for="testModeCheckbox">Enable Test Mode</label>
        </div>
        <p class="status" id="testModeStatus">Test Mode: Disabled</p>
        <div class="button-grid">
            <button class="fire" id="fire1" onclick="fireChannel(1)">Fire Channel 1</button>
            <button class="fire" id="fire2" onclick="fireChannel(2)">Fire Channel 2</button>
            <button class="fire" id="fire3" onclick="fireChannel(3)">Fire Channel 3</button>
            <button class="fire" id="fire4" onclick="fireChannel(4)">Fire Channel 4</button>
        </div>
        <p class="status" id="actionStatus">Ready to Fire</p>
    </div>
    <script>
        function fireChannel(channel) {
            const actionStatus = document.getElementById("actionStatus");
            actionStatus.textContent = `Firing Channel ${channel}...`;
            fetch(`/fire${channel}`)
                .then(response => response.text())
                .then(data => {
                    actionStatus.textContent = `Response: ${data}`;
                    const button = document.getElementById(`fire${channel}`);
                    button.disabled = true;
                    button.classList.add("fired");
                })
                .catch(() => {
                    actionStatus.textContent = "Error: Could not connect to ESP32.";
                });
        }

        function toggleTestMode() {
            const checkbox = document.getElementById("testModeCheckbox");
            fetch("/toggleTestMode")
                .then(response => response.text())
                .then(data => {
                    document.getElementById("testModeStatus").textContent = `Test Mode: ${data.includes("enabled") ? "Enabled" : "Disabled"}`;
                })
                .catch(() => {
                    document.getElementById("testModeStatus").textContent = "Error: Unable to toggle Test Mode.";
                });
        }

        function checkConnection() {
            fetch("/ping")
                .then(() => {
                    document.getElementById("connectionStatus").textContent = "Connected";
                    document.getElementById("connectionStatus").classList.remove("disconnected");
                    document.getElementById("connectionStatus").classList.add("connected");
                })
                .catch(() => {
                    document.getElementById("connectionStatus").textContent = "Disconnected";
                    document.getElementById("connectionStatus").classList.remove("connected");
                    document.getElementById("connectionStatus").classList.add("disconnected");
                });
        }

        function updateSignalStrength() {
            fetch("/signalStrength")
                .then(response => response.json())
                .then(data => {
                    document.getElementById("signalStrength").textContent = `${data.strength} dBm`;
                })
                .catch(() => {
                    document.getElementById("signalStrength").textContent = "N/A";
                });
        }

        function measureDelay() {
            const startTime = Date.now();
            fetch("/ping")
                .then(() => {
                    const delay = Date.now() - startTime;
                    document.getElementById("delayTime").textContent = `${delay} ms`;
                })
                .catch(() => {
                    document.getElementById("delayTime").textContent = "N/A";
                });
        }

        setInterval(checkConnection, 2000);
        setInterval(updateSignalStrength, 3000);
        setInterval(measureDelay, 1500);
    </script>
</body>
</html>
)rawliteral";

// Serve the HTML page
void servePage() {
    server.send_P(200, "text/html", htmlPage);
}

// Blink LED for test mode
void blinkLED(int times) {
    for (int i = 0; i < times; i++) {
        digitalWrite(ONBOARD_LED_PIN, HIGH);
        delay(300);
        digitalWrite(ONBOARD_LED_PIN, LOW);
        delay(300);
    }
}

// Fire a specific channel
void fireChannel(int channel) {
    if (testMode) {
        blinkLED(channel);
    } else {
        int pin = 0;
        switch (channel) {
            case 1: pin = FIRE_CHANNEL_1_PIN; break;
            case 2: pin = FIRE_CHANNEL_2_PIN; break;
            case 3: pin = FIRE_CHANNEL_3_PIN; break;
            case 4: pin = FIRE_CHANNEL_4_PIN; break;
        }
        if (pin != 0) {
            digitalWrite(pin, HIGH);
            delay(1000);
            digitalWrite(pin, LOW);
        }
    }
    server.send(200, "text/plain", String("Channel ") + channel + (testMode ? " Tested!" : " Fired!"));
}

// ESP32 setup
void setup() {
    Serial.begin(115200);

    // Initialize GPIO pins
    pinMode(FIRE_CHANNEL_1_PIN, OUTPUT);
    pinMode(FIRE_CHANNEL_2_PIN, OUTPUT);
    pinMode(FIRE_CHANNEL_3_PIN, OUTPUT);
    pinMode(FIRE_CHANNEL_4_PIN, OUTPUT);
    pinMode(ONBOARD_LED_PIN, OUTPUT);
    digitalWrite(FIRE_CHANNEL_1_PIN, LOW);
    digitalWrite(FIRE_CHANNEL_2_PIN, LOW);
    digitalWrite(FIRE_CHANNEL_3_PIN, LOW);
    digitalWrite(FIRE_CHANNEL_4_PIN, LOW);
    digitalWrite(ONBOARD_LED_PIN, LOW);

    // Start Wi-Fi Access Point
    WiFi.softAP(ssid, password);
    Serial.println("Wi-Fi started");
    Serial.print("Access Point IP: ");
    Serial.println(WiFi.softAPIP());

    // Define server routes
    server.on("/", servePage);
    server.on("/fire1", []() { fireChannel(1); });
    server.on("/fire2", []() { fireChannel(2); });
    server.on("/fire3", []() { fireChannel(3); });
    server.on("/fire4", []() { fireChannel(4); });
    server.on("/toggleTestMode", []() {
        testMode = !testMode;
        server.send(200, "text/plain", testMode ? "Test mode enabled" : "Test mode disabled");
    });
    server.on("/signalStrength", []() {
        int32_t rssi = WiFi.RSSI();
        server.send(200, "application/json", "{\"strength\": " + String(rssi) + "}");
    });
    server.on("/ping", []() {
        server.send(200, "text/plain", "pong");
    });

    // Start the server
    server.begin();
    Serial.println("HTTP server started");
}

// Main loop
void loop() {
    server.handleClient();
}
