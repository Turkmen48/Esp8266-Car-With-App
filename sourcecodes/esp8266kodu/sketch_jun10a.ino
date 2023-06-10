#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// WiFi ağı ayarları
const char* ssid = "ESP8266_AP";
const char* password = "password";
IPAddress local_IP(192, 168, 1, 31);  // IP adresi
IPAddress gateway(192, 168, 1, 1);   // Ağ geçidi adresi
IPAddress subnet(255, 255, 255, 0);  // Alt ağ maskesi
// Motor pinleri
const int EnbSag = D7;
const int EnbSol = D8;
const int EnaIleri = D4;
const int EnaGeri = D3;
const int EnaSpeed=D6; //ileri götüren motorun hızı
const int EnbSpeed=D2; //sağa sola döndüren motorun hızı

ESP8266WebServer server(80);

void handleRoot() {
  String html = "<html><body>";
  html += "<h1>Motor Kontrolu</h1>";
  html += "<p>Ileri git: <a href='/Forward'>Ileri</a></p>";
  html += "<p>Geri git: <a href='/Backward'>Geri</a></p>";
  html += "<p>Saga don: <a href='/Right'>Sag</a></p>";
  html += "<p>Sola don: <a href='/Left'>Sol</a></p>";
  html += "<p>Ileri Saga git: <a href='/RightForward'>Saga Ileri</a></p>";
   html += "<p>Ileri Sola git: <a href='/LeftForward'>Sola Ileri</a></p>";
    html += "<p>Geri Sağa git: <a href='/RightBackward'>Saga Geri</a></p>";
       html += "<p>Geri Sola git: <a href='/LeftBackward'>Sola Geri</a></p>";
  html += "<p>Dur: <a href='/Center'>Dur</a></p>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleLeft() {
  Serial.println("Sol");
  digitalWrite(EnbSol, HIGH);
  digitalWrite(EnaGeri, LOW);
  digitalWrite(EnaIleri, LOW);
  digitalWrite(EnbSag, LOW);
  server.send(200, "text/plain", "Sol");
}

void handleRight() {
  Serial.println("Sag");
  digitalWrite(EnbSol, LOW);
  digitalWrite(EnaGeri, LOW);
  digitalWrite(EnaIleri, LOW);
  digitalWrite(EnbSag, HIGH);
  server.send(200, "text/plain", "Sag");
}

void handleForward() {
  Serial.println("Ileri");
  digitalWrite(EnbSol, LOW);
  digitalWrite(EnaGeri, LOW);
  digitalWrite(EnaIleri, HIGH);
  digitalWrite(EnbSag, LOW);
  server.send(200, "text/plain", "Ileri");
}
void handleRightForward() {
  Serial.println("Sag Ileri");
  digitalWrite(EnbSol, LOW);
  digitalWrite(EnaGeri, LOW);
  digitalWrite(EnaIleri, HIGH);
  digitalWrite(EnbSag, HIGH);
  server.send(200, "text/plain", "Sag Ileri");
}
void handleLeftForward() {
  Serial.println("Sol Ileri");
  digitalWrite(EnbSol, HIGH);
  digitalWrite(EnaGeri, LOW);
  digitalWrite(EnaIleri, HIGH);
  digitalWrite(EnbSag, LOW);
  server.send(200, "text/plain", "Sol Ileri");
}

void handleBackward() {
  Serial.println("Geri");
  digitalWrite(EnbSol, LOW);
  digitalWrite(EnaGeri, HIGH);
  digitalWrite(EnaIleri, LOW);
  digitalWrite(EnbSag, LOW);
  server.send(200, "text/plain", "Geri");
}
void handleRightBackward() {
  Serial.println("Sag Geri");
  digitalWrite(EnbSol, LOW);
  digitalWrite(EnaGeri, HIGH);
  digitalWrite(EnaIleri, LOW);
  digitalWrite(EnbSag, HIGH);
  server.send(200, "text/plain", "Sag Geri");
}
void handleLeftBackward() {
  Serial.println("Sol Geri");
  digitalWrite(EnbSol, HIGH);
  digitalWrite(EnaGeri, HIGH);
  digitalWrite(EnaIleri, LOW);
  digitalWrite(EnbSag, LOW);
  server.send(200, "text/plain", "Sol Geri");
}

void handleCenter() {
  Serial.println("Dur");
  digitalWrite(EnbSol, LOW);
  digitalWrite(EnaGeri, LOW);
  digitalWrite(EnaIleri, LOW);
  digitalWrite(EnbSag, LOW);
  server.send(200, "text/plain", "Dur");
}

void setup() {
  Serial.begin(9600);
  // Motor pinlerini çıkış olarak ayarla
  pinMode(EnbSpeed, OUTPUT);
  pinMode(EnaSpeed, OUTPUT);
  pinMode(EnbSol, OUTPUT);
  pinMode(EnaGeri, OUTPUT);
  pinMode(EnaIleri, OUTPUT);
  pinMode(EnbSag, OUTPUT);
// IP adresi, ağ geçidi ve alt ağ maskesi ayarlanıyor
  WiFi.softAPConfig(local_IP, gateway, subnet); 
  // WiFi erişim noktası oluştur
  WiFi.softAP(ssid, password);

  // Sunucuyu başlat
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", HTTP_GET, handleRoot);
  server.on("/Left", HTTP_GET, handleLeft);
  server.on("/Right", HTTP_GET, handleRight);
  server.on("/Forward", HTTP_GET, handleForward);
  server.on("/Backward", HTTP_GET, handleBackward);
  server.on("/RightBackward", HTTP_GET, handleRightBackward);
  server.on("/LeftBackward", HTTP_GET, handleLeftBackward);
  server.on("/RightForward", HTTP_GET, handleRightForward);
  server.on("/LeftForward", HTTP_GET, handleLeftForward);
  server.on("/Center", HTTP_GET, handleCenter);
  server.begin();


}

void loop() {
  server.handleClient();
}