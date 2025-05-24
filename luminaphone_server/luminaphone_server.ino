#include <SPI.h>
#include <WiFiNINA.h>

#include "arduino_secrets.h" 
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
int keyIndex = 0;

int first_delay = 0;
int second_delay = 0;
String note_vals = "";

int status = WL_IDLE_STATUS;
WiFiServer server(80);

void setup() {
  Serial.begin(9600);      // initialize serial communication
  pinMode(12, OUTPUT);      // set the LED pin mode

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // Attempt to connect to WiFi network.
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);

    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
    delay(10000);
  }
  server.begin();                           // start the web server on port 80
  printWifiStatus();                        // you're connected now, so print out the status
}


void loop() {
  String lastLine = "";
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out to the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("Click <a href=\"/H\">here</a> turn the LED on pin 9 on<br>");
            client.print("Click <a href=\"/L\">here</a> turn the LED on pin 9 off<br>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            lastLine = currentLine;
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }


        if (currentLine.endsWith("SETFIRST")) {
          int start = currentLine.indexOf("GET /") + 5;
          int end = currentLine.indexOf("SETFIRST HTTP/1.1");
          String val = currentLine.substring(start, end);
          first_delay = val.toInt();
          note_vals = "";
        }
        if (currentLine.endsWith("SETSECOND")) {
          int start = currentLine.indexOf("GET /") + 5;
          int end = currentLine.indexOf("SETSECOND HTTP/1.1");
          String val = currentLine.substring(start, end);
          second_delay = val.toInt();
          note_vals = "";
        }
        if (currentLine.endsWith("NOTEVALS")) {
          int start = currentLine.indexOf("GET /") + 5;
          int end = currentLine.indexOf("NOTEVALS");
          note_vals = currentLine.substring(start, end);
        }

      }
    }
    

    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }


  if (note_vals.length() > 0) {
    int c = note_vals.length();

    for (int i=0; i<500; i++) {
      for (int x=0; x<c; x++) {
        if (note_vals[x] == '1') {
          digitalWrite(12, HIGH);
        } else if (note_vals[x] == '0') {
          digitalWrite(12, LOW);
        }
      }
    }
    
    note_vals = "";

  } else if (first_delay == 0 && second_delay == 0) {
    digitalWrite(12, LOW);

  } else {
    for(int i=0; i<400; i++) {
      digitalWrite(12, HIGH);
      delayMicroseconds(first_delay);

      digitalWrite(12, LOW);
      delayMicroseconds(second_delay);
    }
  }


}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  // print where to go in a browser:
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}
