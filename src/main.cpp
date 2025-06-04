#include <WiFi.h>
#include <WebServer.h>

// Cấu hình chân ESP32
#define PIR_PIN     14
#define DOOR_PIN    26
#define BUZZER_PIN  27
#define LED_PIN     25

// WiFi
const char* ssid = "Vân Rung";          
const char* password = "phuchamchi"; 

// Trạng thái
bool alertSent = false;
bool motionDetected = false;
bool doorOpen = false;

WebServer server(80);

// Giao diện Web nâng cấp
void handleRoot() {
  String html = R"rawliteral(
    <!DOCTYPE html>
    <html lang="vi">
    <head>
      <meta charset="UTF-8">
      <title>ESP32 Báo động thông minh</title>
      <meta http-equiv="refresh" content="2">
      <style>
        body {
          font-family: Arial, sans-serif;
          background: #f2f2f2;
          text-align: center;
          padding: 20px;
          color: #333;
        }
        h2 {
          color: #006600;
        }
        .status-box {
          background: #fff;
          border-radius: 10px;
          padding: 20px;
          max-width: 400px;
          margin: auto;
          box-shadow: 0 0 10px rgba(0,0,0,0.1);
        }
        .label {
          font-weight: bold;
          font-size: 18px;
        }
        .value {
          font-size: 20px;
          margin-bottom: 15px;
        }
        .danger {
          color: red;
          font-weight: bold;
        }
        .safe {
          color: green;
          font-weight: bold;
        }
      </style>
    </head>
    <body>
      <h2>🏠 Hệ thống báo động ESP32</h2>
      <div class="status-box">
        <div class="label">Cảm biến chuyển động:</div>
        <div class="value">%MOTION%</div>

        <div class="label">Trạng thái cửa:</div>
        <div class="value">%DOOR%</div>

        <div class="label">Báo động:</div>
        <div class="value %ALERT_CLASS%">%ALERT%</div>
      </div>
    </body>
    </html>
  )rawliteral";

  html.replace("%MOTION%", motionDetected ? "🔴 Phát hiện!" : "🟢 Không");
  html.replace("%DOOR%", doorOpen ? "🚪 Cửa mở" : "✅ Cửa đóng");
  html.replace("%ALERT%", alertSent ? "🔔 Có xâm nhập!" : "✔️ Bình thường");
  html.replace("%ALERT_CLASS%", alertSent ? "danger" : "safe");

  server.send(200, "text/html; charset=utf-8", html);
}

void setup() {
  pinMode(PIR_PIN, INPUT);
  pinMode(DOOR_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);

  // Kết nối WiFi
  WiFi.begin(ssid, password);
  Serial.print("Đang kết nối WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ Đã kết nối WiFi!");
  Serial.println("🌐 IP: " + WiFi.localIP().toString());

  // Khởi động Web server
  server.on("/", handleRoot);
  server.begin();
  Serial.println("🟢 Web server đã sẵn sàng!");
}

void loop() {
  motionDetected = digitalRead(PIR_PIN);
  doorOpen = digitalRead(DOOR_PIN) == LOW;

  if ((motionDetected || doorOpen) && !alertSent) {
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(LED_PIN, HIGH);
    Serial.println("🚨 Phát hiện xâm nhập!");
    alertSent = true;
  }

  if (!motionDetected && !doorOpen) {
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_PIN, LOW);
    alertSent = false;
  }

  server.handleClient();
  delay(100);
}
