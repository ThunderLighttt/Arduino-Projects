#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

/* Установите здесь свои SSID и пароль */
const char* ssid = "NodeMCU";       // SSID
const char* password = "12345678";  // пароль

/* Настройки IP адреса */
IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

ESP8266WebServer server(80);

uint8_t LED1pin = D4;
bool LED1status = LOW;

uint8_t LED2pin = D6;
bool LED2status = LOW;

void WebInit() {
  Serial.begin(115200);
  pinMode(LED1pin, OUTPUT);
  pinMode(LED2pin, OUTPUT);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  WiFi.softAP(ssid, password);

  delay(100);

  server.on("/", handle_OnConnect);
  server.on("/Red", handle_Red);
  server.on("/Orange", handle_Orange);
  server.on("/Yellow", handle_Yellow);
  server.on("/Green", handle_Green);
  server.on("/Cyan", handle_Cyan);
  server.on("/Blue", handle_Blue);
  server.on("/Violet", handle_Violet);
  server.on("/Auto", handle_Auto);
  server.on("/Static", handle_Static);
  server.on("/Breath", handle_Breath);
  server.on("/Rainbow", handle_Rainbow);

  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void WebRoutine() {
  server.handleClient();
}

void handle_OnConnect() {

  server.send(200, "text/html", SendHTML(MatrixGetMode(), MatrixGetColour()));
}


void handle_Red() {
  MatrixSetColour(0);
  MatrixSetColours(255, 0, 0);
  server.send(200, "text/html", SendHTML(MatrixGetMode(), MatrixGetColour()));
}
void handle_Orange() {
  MatrixSetColour(1);
  MatrixSetColours(255, 69, 0);
  server.send(200, "text/html", SendHTML(MatrixGetMode(), MatrixGetColour()));
}
void handle_Yellow() {
  MatrixSetColour(2);
  MatrixSetColours(255, 255, 0);
  server.send(200, "text/html", SendHTML(MatrixGetMode(), MatrixGetColour()));
}
void handle_Green() {
  MatrixSetColour(3);
  MatrixSetColours(0, 255, 0);
  server.send(200, "text/html", SendHTML(MatrixGetMode(), MatrixGetColour()));
}
void handle_Cyan() {
  MatrixSetColour(4);
   MatrixSetColours(0, 255, 255);
  server.send(200, "text/html", SendHTML(MatrixGetMode(), MatrixGetColour()));
}
void handle_Blue() {
  MatrixSetColour(5);
   MatrixSetColours(0, 0, 255);
  server.send(200, "text/html", SendHTML(MatrixGetMode(), MatrixGetColour()));
}
void handle_Violet() {
  MatrixSetColour(6);
   MatrixSetColours(255, 0, 255);
  server.send(200, "text/html", SendHTML(MatrixGetMode(), MatrixGetColour()));
}

void handle_Auto() {
  MatrixSetMode(0);

  server.send(200, "text/html", SendHTML(MatrixGetMode(), MatrixGetColour()));
}
void handle_Static() {
  MatrixSetMode(1);
  server.send(200, "text/html", SendHTML(MatrixGetMode(), MatrixGetColour()));
}

void handle_Breath() {
  MatrixSetMode(2);
  server.send(200, "text/html", SendHTML(MatrixGetMode(), MatrixGetColour()));
}
void handle_Rainbow() {
  MatrixSetMode(6);
  server.send(200, "text/html", SendHTML(MatrixGetMode(), MatrixGetColour()));
}

void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
}

String SendHTML(uint8_t mode, uint8_t colour) {

  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title>LED Control</title>\n";
  ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 10px auto; text-align: center;}\n";
  ptr += ".mySelect{display: block;width: 200px;background-color:DodgerBlue;border: none;color: white;padding: 13px 40px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 30px;}\n";
  ptr += ".button {display: inline-block; width: auto;background-color: black;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr += ".redButton {background-color: Red;}\n";
  ptr += ".orangeButton {background-color: Orange;}\n";
  ptr += ".yellowButton {background-color: yellow;color: black;}\n";
  ptr += ".greenButton {background-color:#00FF00;}\n";
  ptr += ".cyanButton {background-color: #00FFFF;}\n";
  ptr += ".blueButton {background-color: Blue;}\n";
  ptr += ".violetButton {background-color: #FF00FF;}\n";
  ptr += ".bordered {border: 4px solid black;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<h1>ESP8266 Web Server</h1>\n";
  ptr += "<h3>Choose mode</h3>\n";



  ptr += "<select class=\'mySelect\' name=\'forma\' onchange=\'location = this.value;\'>\n";
  ptr += "<option value=\'/Auto\'";
  if (mode == 0) ptr += "selected";
  ptr += ">Auto</option>\n";

  ptr += "<option value=\'/Static\'";
  if (mode == 1) ptr += "selected";
  ptr += ">Static</option>\n";

  ptr += "<option value=\'/Breath\'";
  if (mode == 2) ptr += "selected";
  ptr += ">Breath</option>\n";

  ptr += "<option value=\'/Rainbow\'";
  if (mode == 3) ptr += "selected";
  ptr += ">Rainbow</option>\n";

  ptr += "</select> \n";


  ptr += "<h3>Choose colour</h3>\n";

  ptr += "<a class = \'button redButton";
  if (colour == 0) ptr += " bordered";
  ptr += "\'href=\"/Red\">Red</a>\n";

  ptr += "<a class = \'button orangeButton";
  if (colour == 1) ptr += " bordered";
  ptr += "\'href=\"/Orange\">Orange</a>\n";

  ptr += "<a class = \'button yellowButton";
  if (colour == 2) ptr += " bordered";
  ptr += "\'href=\"/Yellow\">Yellow</a>\n";

  ptr += "<a class = \'button greenButton";
  if (colour == 3) ptr += " bordered";
  ptr += "\'href=\"/Green\">Green</a>\n";

  ptr += "<a class = \'button cyanButton";
  if (colour == 4) ptr += " bordered";
  ptr += "\'href=\"/Cyan\">Cyan</a>\n";

  ptr += "<a class = \'button blueButton";
  if (colour == 5) ptr += " bordered";
  ptr += "\'href=\"/Blue\">Blue</a>\n";

  ptr += "<a class = \'button violetButton";
  if (colour == 6) ptr += " bordered";
  ptr += "\'href=\"/Violet\">Violet</a>\n";



  ptr += "</body>\n";
  ptr += "</html>\n";

  return ptr;
}