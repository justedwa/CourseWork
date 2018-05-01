#include <ESP8266WiFi.h>
#include "parse.h"
#include "HTTPSRedirect.h"
#include "info.h"
#include <SoftwareSerial.h>
#include <string.h>
const char* ssid = "MBED";
const char* password = "guni381!";
int flag;
String s;
char rx[75];
int htmlflg;
//sheets ID
const char *GScriptId = "AKfycbzohl4KFGdu-DMWN1Mgog67MmofIpIlM3mxI6WKw9AYtDzF9PQ";
WiFiServer server(80);
String header;
// Push data on this interval
const int dataPostDelay = 1;  // 15 minutes = 15 * 60 * 1000

const char* host = "script.google.com";
const char* googleRedirHost = "script.googleusercontent.com";
IPAddress ip;
const int httpsPort =  443;
HTTPSRedirect client(httpsPort);

// Prepare the url (without the varying data)
String url = String("/macros/s/") + GScriptId + "/exec?";

const char* fingerprint = "F0 5C 74 77 3F 6B 25 D7 3B 66 4D 43 2F 7E BC 5B E9 28 86 AD";

info* currInfo;
void setup() {
  htmlflg = 2;
  server.begin();
  flag = 0;
  currInfo = (info*) malloc(sizeof(struct info));
  populate(currInfo);
  Serial.begin(115200);
  Serial.println("Connecting to wifi: ");
  Serial.println(ssid);
  Serial.flush();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  //Serial.println(" IP address: ");
  ip = WiFi.localIP();

  
  Serial.print(String("Connecting to "));
  Serial.println(host);

  bool flag = false;
  for (int i=0; i<5; i++){
    int retval = client.connect(host, httpsPort);
    if (retval == 1) {
       flag = true;
       break;
    }
    else
      Serial.println("Connection failed. Retrying...");
  }

  // Connection Status, 1 = Connected, 0 is not.
  Serial.println("Connection Status: " + String(client.connected()));
  Serial.flush();
  
  if (!flag){
    Serial.print("Could not connect to server: ");
    Serial.println(host);
    Serial.println("Exiting...");
    Serial.flush();
    return;
  }

  // Data will still be pushed even certification don't match.
  if (client.verify(fingerprint, host)) {
    Serial.println("Certificate match.");
  } else {
    Serial.println("Certificate mis-match");
  }
}


void postData(info* currInfo){
  if (!client.connected()){
    //Serial.println("Connecting to client..."); 
    client.connect(host, httpsPort);
  }
  String urlFinal = url + "crash=" + currInfo->crash +"&ip=" + ip[0] + "." + ip[1] + "." + ip[2] + "." + ip[3] + "&gear=" + currInfo->gear + "&speed=" + currInfo->speed + "&temp=" + currInfo->temp + "&hr=" + currInfo->hr + "&coord=" + currInfo->x + "," + currInfo->y + "&lean=" + currInfo->lean + "&humidity=" + currInfo->humidity + "&accel=" + currInfo->accel;
  client.printRedir(urlFinal, host, googleRedirHost);
}
void loop() {
  WiFiClient client = server.available();
  // wait for a client (web browser) to connect
  if (client)
  {
    //Serial.println("\n[Client connected]");
    while (client.connected())
    {
      // read line by line what the client (web browser) is requesting
      if (client.available())
      {
        String line = client.readStringUntil('\r');
        //Serial.print(line);
        // wait for end of client's request, that is marked with an empty line
        if (line.length() == 1 && line[0] == '\n')
        {
          client.println(prepareHtmlPage());
          break;
        }
      }
    }
    // close the connection:
    client.stop();
  }
  if(Serial.available()){
    s = Serial.readString();
    s.toCharArray(rx,75);
    s = "";
    flag = 1;
  }
  if(flag == 1){
    if(!parse(rx,currInfo)){
      rx[0] = '\0';
      postData(currInfo);
      currInfo->crash = 0;
    }
    flag = 0;
  }
}
String prepareHtmlPage()
{
  String htmlPage =
     String("HTTP/1.1 200 OK\r\n") +
            "Content-Type: text/html\r\n" +
            "Connection: close\r\n" +  // the connection will be closed after completion of the response
            "Refresh: 60\r\n" +  // refresh the page automatically every 5 sec
            "\r\n" +
            "<!DOCTYPE HTML>" +
            "<html>" +
            "<iframe src=\"https://www.geosheets.com/map/s:QAlyNEJx/Test/embed\" style=\"border:none;width:640px;height:480px\"></iframe>"
            "</html>" +
            "\r\n";
  return htmlPage;
}
