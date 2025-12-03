#include <ESP8266WiFi.h> 
#include <ESP8266WebServer.h> 
// Wi-Fi credentials 
const char* ssid = "saf"; 
const char* password = "bamsicomel123"; 
// Web server 
ESP8266WebServer server(80); 
// Pin assignments 
const int sensorPinA = D6;       
const int sensorPinB = D7;       
const int buzzerPin = D8;        
const int yellowLedPin = D5;     
// Sensor A 
// Sensor B 
// Buzzer 
// Yellow LED 
// Variables for flow rate calculation 
volatile int pulseCountA = 0; 
volatile int pulseCountB = 0; 
float flowRateA = 0.0; 
float flowRateB = 0.0; 
unsigned long previousMillis = 0; 
const unsigned long interval = 1000; 
// Define thresholds 
const float tolerance = 5.0;           
const float minFlowThreshold = 2.0;   
const unsigned long transientDelay = 3000; 
// Variables to track transient state 
bool isTransient = false; 
unsigned long transientStartTime = 0; 
bool leakDetected = false; 
   
 
 
 
 
// Variables for LED blinking 
unsigned long ledPreviousMillis = 0; 
unsigned long ledInterval = 0; 
bool ledState = LOW; 
 
// ISR for Sensor A 
void ICACHE_RAM_ATTR countPulseA() { 
  pulseCountA++; 
} 
 
// ISR for Sensor B 
void ICACHE_RAM_ATTR countPulseB() { 
  pulseCountB++; 
} 
 
// Function to manage LED and buzzer behavior based on current state 
void updateOutputs() { 
  if (flowRateA < minFlowThreshold && flowRateB < minFlowThreshold) { 
    // No flow detected 
    digitalWrite(yellowLedPin, LOW); // LED OFF 
    digitalWrite(buzzerPin, LOW);   // Buzzer OFF 
    Serial.println("No flow detected. LED OFF."); 
    leakDetected = false; // No leak 
    isTransient = false;  // Reset transient state 
  } else if (abs(flowRateA - flowRateB) > tolerance) { 
    // Leak detected 
    if (!isTransient) { 
      isTransient = true; 
      transientStartTime = millis(); 
      Serial.println("Transient condition detected. Stabilizing..."); 
    } else if (millis() - transientStartTime >= transientDelay) { 
      digitalWrite(buzzerPin, HIGH); // Turn buzzer ON 
      if (millis() - ledPreviousMillis >= 50) { // Fast LED blinking 
        ledPreviousMillis = millis(); 
        ledState = !ledState; 
        digitalWrite(yellowLedPin, ledState); 
      } 
      Serial.println("ALERT: Leak detected! LED BLINKING."); 
      leakDetected = true; 
    } 
  } else { 
    // Normal flow, no leaks 
    digitalWrite(yellowLedPin, HIGH); // LED ON 
    digitalWrite(buzzerPin, LOW);    // Buzzer OFF 
    Serial.println("Normal flow detected. LED ON."); 
    leakDetected = false; 
    isTransient = false; // Reset transient state 
   
 
 
 
  } 
} 
 
void handleSensorData() { 
  String json = "{"; 
  json += "\"flowRateA\": " + String(flowRateA) + ","; 
  json += "\"flowRateB\": " + String(flowRateB) + ","; 
  json += "\"leakDetected\": " + String(leakDetected ? "true" : "false") + ","; 
  json += "\"noFlow\": " + String((flowRateA < minFlowThreshold && flowRateB < 
minFlowThreshold) ? "true" : "false"); 
  json += "}"; 
  server.send(200, "application/json", json); 
} 
 
void handleRoot() { 
  String html = "<!DOCTYPE html><html><head>"; 
  html += "<title>REAL-TIME PIPE FLOW AND MONITORING SYSTEM</title>"; 
  html += "<style>"; 
  html += "body { font-family: Arial, sans-serif; margin: 0; padding: 0; background
color: #f4f4f4; color: #333; }"; 
  html += "header { background-color: #007BFF; color: white; padding: 1em 0; text
align: center; }"; 
  html += "h1 { margin: 0; font-size: 32px; }"; 
  html += "main { padding: 20px; max-width: 600px; margin: auto; background: white; 
border-radius: 10px; box-shadow: 0 2px 5px rgba(0, 0, 0, 0.2); }"; 
  html += "p { font-size: 20px; margin: 15px 0; }"; 
  html += "#leakAlert { font-size: 24px; font-weight: bold; }"; 
  html += "#flowAlert { font-size: 20px; font-style: italic; }"; 
  html += "footer { text-align: center; padding: 1em 0; margin-top: 20px; font-size: 
14px; color: #777; }"; 
  html += "</style>"; 
  html += "</head><body>"; 
  html += "<header><h1>REAL-TIME PIPE FLOW AND MONITORING 
SYSTEM</h1></header>"; 
  html += "<main>"; 
  html += "<p><b>Flow Rate A:</b> <span id='flowRateA'>0</span> mL/sec</p>"; 
  html += "<p><b>Flow Rate B:</b> <span id='flowRateB'>0</span> mL/sec</p>"; 
  html += "<p id='leakAlert' style='color:green;'>No leaks detected.</p>"; 
  html += "<p id='flowAlert' style='color:blue;'>Flow is being monitored.</p>"; 
  html += "</main>"; 
  html += "<footer>&copy; 2025 REAL-TIME PIPE FLOW AND MONITORING 
SYSTEM</footer>"; 
  html += "<script>"; 
  html += "setInterval(() => {"; 
  html += "  fetch('/data')"; 
  html += "    .then(response => response.json())"; 
  html += "    .then(data => {"; 
  html += "      document.getElementById('flowRateA').textContent = data.flowRateA;"; 
   
 
 
 
  html += "      document.getElementById('flowRateB').textContent = data.flowRateB;"; 
  html += "      document.getElementById('leakAlert').textContent = data.leakDetected ? 
'ALERT: Leak detected!' : 'No leaks detected.';"; 
  html += "      document.getElementById('leakAlert').style.color = data.leakDetected ? 
'red' : 'green';"; 
  html += "      document.getElementById('flowAlert').textContent = data.noFlow ? 'No 
flow detected.' : 'Flow is being monitored.';"; 
  html += "      document.getElementById('flowAlert').style.color = data.noFlow ? 
'orange' : 'blue';"; 
  html += "    });"; 
  html += "}, 1000);"; 
  html += "</script>"; 
  html += "</body></html>"; 
  server.send(200, "text/html", html); 
} 
 
void setup() { 
  Serial.begin(115200); 
 
  pinMode(sensorPinA, INPUT_PULLUP); 
  pinMode(sensorPinB, INPUT_PULLUP); 
  pinMode(buzzerPin, OUTPUT); 
  pinMode(yellowLedPin, OUTPUT); 
 
  digitalWrite(buzzerPin, LOW); 
  digitalWrite(yellowLedPin, LOW); 
 
  attachInterrupt(digitalPinToInterrupt(sensorPinA), countPulseA, RISING); 
  attachInterrupt(digitalPinToInterrupt(sensorPinB), countPulseB, RISING); 
 
  // Connect to Wi-Fi 
  Serial.println("Connecting to Wi-Fi..."); 
  WiFi.begin(ssid, password); 
  while (WiFi.status() != WL_CONNECTED) { 
    delay(500); 
    Serial.print("."); 
  } 
  Serial.println("\nWi-Fi connected!"); 
  Serial.print("IP Address: "); 
  Serial.println(WiFi.localIP()); 
 
  server.on("/", handleRoot); 
  server.on("/data", handleSensorData); 
  server.begin(); 
  Serial.println("HTTP server started"); 
} 
 
void loop() { 
   
 
 
 
  unsigned long currentMillis = millis(); 
 
  if (currentMillis - previousMillis >= interval) { 
    previousMillis = currentMillis; 
 
    flowRateA = (pulseCountA / 7.5) * 16.67; 
    flowRateB = (pulseCountB / 7.5) * 16.67; 
 
    pulseCountA = 0; 
    pulseCountB = 0; 
 
    Serial.print("Flow Rate A: "); 
    Serial.print(flowRateA); 
    Serial.print(" mL/sec | Flow Rate B: "); 
    Serial.println(flowRateB); 
 
    updateOutputs(); // Call to update outputs based on current state 
  } 
 
  server.handleClient(); 
} 