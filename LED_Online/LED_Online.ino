#include <ESP8266WiFi.h>

const char* ssid = "3BB-WANNEE_2.4G"; //ชื่อ Wifi
const char* password = "660383552";//รหัส wifi

int ledPin1 = D0; // ขา D1
int ledPin2 = D1; // ขา D2
int ledPin3 = D2; // ขา D3
int ledPin4 = D3; // ขา D4
//กำหนดให้ไฟปิด คือ 0//
int ch1 = 0;
int ch2 = 0;
int ch3 = 0;
int ch4 = 0;

WiFiServer server(80);

void setup() {
  Serial.begin(9600);
  delay(100);

  // ประกาศขา เป็น Output
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);

  // เริ่มต้น ให้ Logic ตำแหน่งขาเป็น LOW
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin3, LOW);
  digitalWrite(ledPin4, LOW);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  // Match the request

  // รับ Link ช่อง 1

  if (request.indexOf("/LED1=ON") != -1) {
    digitalWrite(ledPin1, HIGH);
    ch1 = 1;
  }
  if (request.indexOf("/LED1=OFF") != -1) {
    digitalWrite(ledPin1, LOW);
    ch1 = 0;
  }

  // รับ Link ช่อง 2
  if (request.indexOf("/LED2=ON") != -1) {
    digitalWrite(ledPin2, HIGH);
    Serial.println("OK2");
    ch2 = 1;
  }

  if (request.indexOf("/LED2=OFF") != -1) {
    digitalWrite(ledPin2, LOW);
    Serial.println("OK2");
    ch2 = 0;
  }

  // รับ Link ช่อง 3
  if (request.indexOf("/LED3=ON") != -1) {
    digitalWrite(ledPin3, HIGH);
    Serial.println("OK3");
    ch3 = 1;
  }

  if (request.indexOf("/LED3=OFF") != -1) {
    digitalWrite(ledPin3, LOW);
    Serial.println("OK3");
    ch3 = 0;
  }

  // รับ Link ช่อง 4
  if (request.indexOf("/LED4=ON") != -1) {
    digitalWrite(ledPin4, HIGH);
    ch4 = 1;
  }

  if (request.indexOf("/LED4=OFF") != -1) {
    digitalWrite(ledPin4, LOW);
    ch4 = 0;
  }

  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("X-UA-Compatible: IE=edge");
  client.println(""); // do not forget this one
  client.println("");
  client.println("");
  client.print("<div style='color:#79031d; text-align: center; font-size:72;'>Light Pin</div>");

  client.print("PLUG(D1) : ");
  if (ch1 == 1) {
    client.print("On");
  } else {
    client.print("Off");
  }
//  client.print("Led pin D2 : ");
//  if (ch2 == 1) {
//    client.print("On<br>");
//  } else {
//    client.print("Off<br>");
//  }
//  client.print("Led pin D3 : ");
//  if (ch3 == 1) {
//    client.print("On<br>");
//  } else {
//    client.print("Off<br>");
//  }
//  client.print("Led pin D4 : ");
//  if (ch4 == 1) {
//    client.print("On<br>");
//  } else {
//    client.print("Off<br>");
//  }

  client.println("");


  client.println("PLUG <br/>  <a href=\"/LED1=ON\"\"> <button style='background-color :#4CAF50; border: none;color: white;padding: 15px 32px;text-align: center;text-decoration: none;display: inline-block; font-size: 16px;'> ON </button> </a> <a href=\"/LED1=OFF\"\"><button style='background-color :red; border: none;color: white;padding: 15px 32px;text-align: center;text-decoration: none;display: inline-block; font-size: 16px;'> OFF </button></a> <br>");

  //client.println("CH2 <a href=\"/LED2=ON\"\"><button style='color: green'> On </button></a><a href=\"/LED2=OFF\"\"><button style='color: red'> OFF </button></a><br>");

  //client.println("CH3 <a href=\"/LED3=ON\"\"><button style='color: green'> On </button></a><a href=\"/LED3=OFF\"\"><button style='color: red'> OFF </button></a><br>");

  //client.println("CH4 <a href=\"/LED4=ON\"\"><button style='color: green'> On </button></a><a href=\"/LED4=OFF\"\"><button style='color: red'> OFF </button></a><br>");

  client.println("");

  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
}
