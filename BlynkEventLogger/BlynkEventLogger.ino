/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on ESP32 chip.

  Note: This requires ESP32 support package:
    https://github.com/espressif/arduino-esp32

  Please be sure to select the right ESP32 module
  in the Tools -> Board menu!

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <M5Stack.h>
#include <M5StackUpdater.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <time.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "XXXXXXXXXXXXXXXXXXXX";
char pass[] = "XXXXXXXXXXXXXXXXXXXX";

WidgetLCD lcd1(V1);
WidgetLCD lcd2(V2);
// Time
char ntpServer[] = "ntp.jst.mfeed.ad.jp";
const long gmtOffset_sec = 9 * 3600;
const int  daylightOffset_sec = 0;
struct tm timeinfo;
String dateStr;
String timeStr;

// Logger Settings
File file;
const char* fname = "/event_log.csv";
const String title = "Event";

// { V3 pin, V4 pin, V5 pin }'s eventName
char *eventName[] = { "event1", "event2", "event3" };
String lastStr;

void getTimeFromNTP(){
  
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  getLocalTime(&timeinfo);

}

void getTime(){
  getLocalTime(&timeinfo);
  dateStr = (String)(timeinfo.tm_year + 1900)
          + "/" + (String)(timeinfo.tm_mon + 1)
          + "/" + (String)timeinfo.tm_mday;
  timeStr = (String)timeinfo.tm_hour + ":" + (String)timeinfo.tm_min + ":" + (String)timeinfo.tm_sec;

  M5.Lcd.setTextColor(WHITE,BLACK);
  M5.Lcd.setCursor(0, 50, 1);
  M5.Lcd.println(dateStr + "   ");
  M5.Lcd.println(timeStr + "   ");
  
  lcd1.print(0, 0, dateStr + "   ");
  lcd1.print(0, 1, timeStr + "   ");
}

BLYNK_WRITE(V3) {
  int btnV3 = param.asInt();
  M5.Lcd.setCursor(0, 100, 1);
  M5.Lcd.print("V3:");
  displayBtn(btnV3, 0);
}

BLYNK_WRITE(V4) {
  int btnV4 = param.asInt();
  M5.Lcd.setCursor(0, 140, 1);
  M5.Lcd.print("V4:");
  displayBtn(btnV4, 1);
}

BLYNK_WRITE(V5) {
  int btnV5 = param.asInt();
  M5.Lcd.setCursor(0, 180, 1);
  M5.Lcd.print("V5:");
  displayBtn(btnV5, 2);
}

void displayBtn(int btnStatus, int eventNum) {
  if (btnStatus) {
    M5.Lcd.println("Pressed");
    M5.Lcd.print("   " + timeStr + "   ");
    writeData( eventName[eventNum] );
  }
}

void writeData(char *paramStr) {
  file = SD.open(fname, FILE_APPEND);
  getTime();
  file.println(dateStr + "," + timeStr + "," + paramStr);
  file.close();
  String lcdStr = timeStr + ":" + paramStr;
  lcd2.print(0, 0, lastStr + "     ");
  lcd2.print(0, 1, lcdStr  + "     ");  
  lastStr = lcdStr;
}

void setup()
{
  M5.begin();
  Wire.begin();
  if(digitalRead(BUTTON_A_PIN) == 0) {
    Serial.println("Will Load menu binary");
    updateFromFS(SD);
    ESP.restart();
  }
  // Debug console
  Blynk.begin(auth, ssid, pass);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(WHITE,BLACK);
  M5.Lcd.println(title + " Recording System");

  // blynk lcd
  lcd1.clear();
  lcd2.clear();

  // timeSet
  getTimeFromNTP();

}

void loop()
{
  Blynk.run();
  getTime();
}
