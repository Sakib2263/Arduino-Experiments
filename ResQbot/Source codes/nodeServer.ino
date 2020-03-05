//-- Libraries Included --------------------------------------------------------------
#include <ESP8266WiFi.h>
//------------------------------------------------------------------------------------
// Network Name and Password
char*       net_ssid = "";              // WIFI NAME
char*       net_pass = "";          // PASSWORD
//------------------------------------------------------------------------------------
#define     MAXSC     6           // MAXIMUM NUMBER OF CLIENTS

WiFiServer  daServer(1987);
WiFiClient  daClient[MAXSC];

int outputIndex[] = {16, 5, 4, 0, 2, 14, 12, 13}; // IO Number for D0 to D7
//====================================================================================
int leftl = 5;
int leftr = 4;
int rightl = 0;
int rightr = 16;
void setup()
{
  // Setting D0 to D7 as Output
  for (int i = 0; i < 7; i++)
  {
    pinMode(outputIndex[i], OUTPUT);
    digitalWrite(outputIndex[i], LOW);
  }
  // Setting Serial Port
  Serial.begin(9600);           // Computer Communication
  //off();
  // Setting Wifi Access Point
  SetWifi("ctrlESPwithJava", "");
}

//====================================================================================

void loop()
{
  // Checking For Available Clients
  AvailableClients();
  // Checking For Available Client Messages
  AvailableMessage();
}

//====================================================================================

void SetWifi(char* Name, char* Password)
{
  // Stop Any Previous WIFI
  WiFi.disconnect();

  // Setting The Wifi Mode
  WiFi.mode(WIFI_AP_STA);
  Serial.println("WIFI Mode : AccessPoint Station");

  // Setting The AccessPoint Name & Password
  net_ssid      = Name;
  net_pass  = Password;

  // Starting The Access Point
  WiFi.softAP(net_ssid, net_pass);
  Serial.println("WIFI << " + String(net_ssid) + " >> has Started");

  // Wait For Few Seconds
  delay(2000);

  // Getting Server IP
  IPAddress IP = WiFi.softAPIP();

  // Printing The Server IP Address
  Serial.print("Server IP : ");
  Serial.println(IP);

  // Starting Server
  daServer.begin();
  daServer.setNoDelay(true);
  Serial.println("Server Started, you can connect from the JAVA client");
}

//====================================================================================

void AvailableClients()
{
  if (daServer.hasClient())
  {


    for (uint8_t i = 0; i < MAXSC; i++)
    {
      //find free/disconnected spot
      if (!daClient[i] || !daClient[i].connected())
      {
        // Checks If Previously The Client Is Taken
        if (daClient[i])
        {
          daClient[i].stop();
        }

        // Checks If Clients Connected To The Server
        if (daClient[i] = daServer.available())
        {
          Serial.println("New Client: " + String(i));
        }

        // Continue Scanning
        continue;
      }
    }

    //no free/disconnected spot so reject
    WiFiClient daClient = daServer.available();
    daClient.stop();
  }
}

//====================================================================================

void AvailableMessage()
{
  //check clients for data
  for (uint8_t i = 0; i < MAXSC; i++)
  {
    if (daClient[i] && daClient[i].connected() && daClient[i].available())
    {
      while (daClient[i].available())
      {
        String Message = daClient[i].readStringUntil('!');
        Serial.println(Message);
        if (Message[0] == 'f') {
          runForward();
        }
        else if (Message[0] == 'r') {
          turnRight();
        }
        else if (Message[0] == 'l') {
          turnLeft();
        }
        else if (Message[0] == 'b') {
          runBackward();
        }
        else if (Message[0] == 's') {
          stopBot();
        }
        daClient[i].flush();
        for (int i = 0; i < 7; i++)
        {
          int cmd = 97 + i;
          if ((int)Message[0] == cmd)
          {
            digitalWrite(outputIndex[i], HIGH);
            break;
          }
          cmd = 97 + i + 7;
          if ((int)Message[0] == cmd)
          {
            digitalWrite(outputIndex[i], LOW);
            break;
          }
        }
      }
    }
  }
}
void runForward()
{
  Serial.println("forward");
  analogWrite(leftl, 800);
  analogWrite(leftr, 0);
  analogWrite(rightl, 800);
  analogWrite(rightr, 0);
}
void runBackward()
{
  Serial.println("backward");
  analogWrite(leftl, 0);
  analogWrite(leftr, 800);
  analogWrite(rightl, 0);
  analogWrite(rightr, 800);
}
void turnRight()
{
  Serial.println("right");
  analogWrite(leftl, 470);
  analogWrite(leftr, 0);
  analogWrite(rightl, 470);
  analogWrite(rightr, 0);
  delay(900);
  analogWrite(leftl, 0);
  analogWrite(leftr, 470);
  analogWrite(rightl, 0);
  analogWrite(rightr, 470);
  delay(100);
  analogWrite(leftl, 0);
  analogWrite(leftr, 0);
  analogWrite(rightl, 0);
  analogWrite(rightr, 0);
  runForward();
}
void turnLeft()
{
  Serial.println("right");
  analogWrite(leftl, 500);
  analogWrite(leftr, 0);
  analogWrite(rightl, 500);
  analogWrite(rightr, 0);
  delay(900);
  analogWrite(leftl, 0);
  analogWrite(leftr, 500);
  analogWrite(rightl, 0);
  analogWrite(rightr, 500);
  delay(100);
  analogWrite(leftl, 0);
  analogWrite(leftr, 0);
  analogWrite(rightl, 0);
  analogWrite(rightr, 0);
  runForward();
}
void stopBot() {
  analogWrite(leftl, 0);
  analogWrite(leftr, 0);
  analogWrite(rightl, 0);
  analogWrite(rightr, 0);
}