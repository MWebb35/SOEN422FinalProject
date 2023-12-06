#include <WiFi.h>
#include <WebServer.h>
#include <WiFiClientSecure.h>
// #include "arduino_secret.h"

#include <HTTPClient.h>

#include <ArduinoJson.h>

#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"

//HTML Header Files
#include "page1.h"
#include "page2.h"
#include "page3.h"
#include "page4.h"
#include "meditation.h"
#include "animations.h"
#include "play.h"
#include "win.h"
#include "draw.h"
#include "loss.h"
#include "stats.h"
#include "study.h"
#include "playResults.h"
#include "whileStudying.h"

//Libraries for OLED Display
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <elapsedMillis.h>

using namespace std;

//OLED pins
#define OLED_SDA 4
#define OLED_SCL 15 
#define OLED_RST 16
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST);

WebServer server(80);

const char* host = "tamagotchi2.azurewebsites.net";  // Server URL

WiFiClientSecure client;

JsonArray userDetails;
DynamicJsonDocument doc(6100);

String json = "";

String petName = "";

String currentUsername = "";

bool sleepingNow = 0;

//LOGIN 
bool login = 0;

//Sleep
int led = 14;         // the PWM pin the LED is attached to
const byte photoResistor = 34;
int brightness = 0;  // how bright the LED is
int fadeAmount = 2;  // how many points to fade the LED by

int amountInterrupt = 0;

bool inStudy = 0;

int buzzer = 12;

//Play
long randomNumber;

// const char* ssid = "SOEN422";
// const char* password = "m2%a$S88";

const char* ssid = "iPhone (80)";
const char* password = "MadisonsIphone80";

// IPAddress staticIP(172, 30, 140, 207);
// IPAddress gateway(172, 30, 140, 129);
// IPAddress subnet(255, 255, 255, 128);

// WiFiClient client;
HTTPClient http;

//Get request for pet name 
void getPet(String enteredUsername){
  client.setInsecure();
  if (!client.connect(host,443)){
        Serial.println("Cannot connect to host");
      } else {
        client.println("GET https://tamagotchi2.azurewebsites.net/GetPetDetails?username="+enteredUsername+" HTTP/1.1");
        client.println("Host: tamagotchi2.azurewebsites.net");
        client.println("Connection: close");
        client.println();

        while (client.connected()) {
          String line = client.readStringUntil('\n');
          Serial.println(line);
          if (line == "\r") {
            Serial.println("Recieved headers");
            break;
          }
        }
  
        while (client.available()) {
          char c = client.read();
          Serial.write(c);
          json+=c;
        }

        //Prints the json string
        json = json.substring((json.indexOf("{")), json.lastIndexOf("}")+1);
        Serial.println("Start");
        Serial.println(json.c_str());
        Serial.println("End");

        client.stop();
          // Deserialize the JSON document
        DeserializationError error = deserializeJson(doc, json);

        if (error) {
          Serial.print(F("deserializeJson() failed: "));
          Serial.println(error.f_str());
        }
        
        String tempPet = doc["petName"];
        petName = tempPet; //Assign to global variable

        Serial.println("Pet name: " + petName);

        json.clear();
      }
}

//Main page - variables reset when user logs out
void handleRoot() {
  petName = "";
  currentUsername = "";  
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("Ready for action!");
  display.display();
  Serial.println("GET /");
  server.send(200, "text/html", htmlPage1);
}

//Login - checks for username and password then performs a get request from the database and compares this against received values
void handlePage2() {
  login = 0;
  client.setInsecure();
  //IF HAS USERNAME
  if (server.hasArg("USERNAME")){
    Serial.println("Username: " + server.arg("USERNAME"));
    String enteredUsername = server.arg("USERNAME");
    //IF HAS PASSWORD
    if (server.hasArg("PASSWORD")){
      String enteredPassword = server.arg("PASSWORD");
      if (!client.connect(host,443)){
              Serial.println("Cannot connect to host");
      } else {
        client.println("GET https://tamagotchi2.azurewebsites.net/GetUsername?username="+enteredUsername+" HTTP/1.1");
        client.println("Host: tamagotchi2.azurewebsites.net");
        client.println("Connection: close");
        client.println();

        while (client.connected()) {
          String line = client.readStringUntil('\n');
          Serial.println(line);
          if (line == "\r") {
            Serial.println("Recieved headers");
            break;
          }
         }
  
        while (client.available()) {
          char c = client.read();
          Serial.write(c);
          json+=c;
        }

        //Prints the json string
        json = json.substring((json.indexOf("{")), json.lastIndexOf("}")+1);
        Serial.println("Start");
        Serial.println(json.c_str());
        Serial.println("End");

        client.stop();
          // Deserialize the JSON document
        DeserializationError error = deserializeJson(doc, json);

        if (error) {
          Serial.print(F("deserializeJson() failed: "));
          Serial.println(error.f_str());
          return;
        }

        String retrievedUsername = doc["userName"];
        String retrievedPassword = doc["passwords"];
        json.clear();
        
        if (retrievedUsername == enteredUsername){
          if (retrievedPassword == enteredPassword){
            Serial.println("Log in successful");
            currentUsername = enteredUsername;
            login = 1;
            getPet(enteredUsername);
          } else {
            Serial.println("Log in not sucessful >:( - Password");
          }
        } else {
            Serial.println("Log in not sucessful >:( - Username");
          }
      } 
    } else { Serial.println("Please enter your password");}
  } else {Serial.println("Please enter your username");}
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("Have your username and password ready!");
  display.display();
  if (login == 0){
    Serial.println("GET /page2");
    server.send(200, "text/html", htmlPage2);
  } else {
    handlePage4();
  }
}

//Sign up - checks for the existance of entered data, the compares the username against usernames in the database to see if it already exists. If it doesn't, a post request is made to add these fields to the table
void handlePage3() {
  login = 0;
  client.setInsecure();
  //IF HAS USERNAME
  if (server.hasArg("USERNAME")){
    Serial.println("Username: " + server.arg("USERNAME"));
    String enteredUsername = server.arg("USERNAME");
    //IF HAS PASSWORD
    if (server.hasArg("PASSWORD")){
      
      //IF HAS PASSWORD AGAIN
      if (server.hasArg("PASSWORDAGAIN")){
        String initialPass = server.arg("PASSWORD");
        String checkPass = server.arg("PASSWORDAGAIN");

        //IF PASSWORDS ARE EQUAL
        if(initialPass.compareTo(checkPass) == 0){

          //IF CAN'T CONNECT TO HOST
          if (!client.connect(host,443)){
              Serial.println("Cannot connect to host");
          } else {
              client.println("GET https://tamagotchi2.azurewebsites.net/GetUsername?username="+enteredUsername+" HTTP/1.1");
              client.println("Host: tamagotchi2.azurewebsites.net");
              client.println("Connection: close");
              client.println();

              while (client.connected()) {
                String line = client.readStringUntil('\n');
                Serial.println(line);
                if (line == "\r") {
                  Serial.println("Recieved headers");
                  break;
                }
              }
        
              while (client.available()) {
                char c = client.read();
                Serial.write(c);
                json+=c;
              }

              //Prints the json string
              json = json.substring((json.indexOf("{")), json.lastIndexOf("}")+1);
              Serial.println("Start");
              Serial.println(json.c_str());
              Serial.println("End");

              client.stop();
                // Deserialize the JSON document
              DeserializationError error = deserializeJson(doc, json);

              if (error) {
                Serial.print(F("deserializeJson() failed: "));
                Serial.println(error.f_str());
                return;
              }

              String retrievedUsername = doc["userName"];
              json.clear();

              //Check if username already exists in the database
              if (retrievedUsername == enteredUsername){
                Serial.println("Sorry, that username is already taken. Please choose another");
              } else {
                 if (!client.connect(host,443)){
                  Serial.println("Cannot connect to host");
                } else {
                  login = 1;
                  currentUsername = enteredUsername;
                  String myContent = "username=" + server.arg("USERNAME") +"&password=" + server.arg("PASSWORD");
                  String postRequest = "POST /PostUsername HTTP/1.1\r\n";
                  postRequest+="Host: tamagotchi2.azurewebsites.net\r\n";
                  postRequest+="Content-Type: application/x-www-form-urlencoded\r\n";
                  postRequest+= "Content-Length: " + String(myContent.length()) + "\r\n\r\n";
                  postRequest+= myContent;

                  Serial.println(postRequest);
                  client.println(postRequest);

                  while (client.connected()){
                        String data = client.readStringUntil('\n');
                        Serial.println(data);
                        if (data=="\r"){
                          Serial.println("All Headers Recieved");
                          break;
                        }
                  }
                  
                  String myContent2 = "username=" + server.arg("USERNAME") + "&petname=" + server.arg("PETNAME")+ "&wins=0" + "&games=0" + "&minutes=0" + "&interrupts=0";
                  String postRequest1 = "POST /PostPet HTTP/1.1\r\n";
                  postRequest1+="Host: tamagotchi2.azurewebsites.net\r\n";
                  postRequest1+="Content-Type: application/x-www-form-urlencoded\r\n";
                  postRequest1+= "Content-Length: " + String(myContent2.length()) + "\r\n\r\n";
                  postRequest1+= myContent2;
                  
                  Serial.println(postRequest1);
                  client.println(postRequest1);

                  while (client.connected()){
                        String data = client.readStringUntil('\n');
                        Serial.println(data);
                        if (data=="\r"){
                          Serial.println("All Headers Recieved");
                          break;
                        }
                    }
                  client.stop();
                  } 
                }
              }
        } else {Serial.println("Please make sure your passwords match");} 
      } else {Serial.println("Please enter your password again");} 
    } 
  }
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("Welcome to the team!");
  display.display();
  //If login not successful
  if (login == 0){
    Serial.println("GET /page3");
    server.send(200, "text/html", htmlPage3);
  } else {
    getPet(currentUsername);
    handlePage4();
  }
  
}

//Home page
void handlePage4(){

  inStudy = 0;
  
  display.clearDisplay();
  display.drawBitmap(0, 0, animations::corgiWave, 64, 128, WHITE);
  display.display();

  Serial.println("GET /page4");
  server.send(200, "text/html", home::runPage(petName));
}

//Get request to update minute value
void getMinute(){
  client.setInsecure();
  if (!client.connect(host,443)){
    Serial.println("Cannot connect to host");
  } else {
    client.println("GET https://tamagotchi2.azurewebsites.net/UpdateMinutes?username="+currentUsername+" HTTP/1.1");
    client.println("Host: tamagotchi2.azurewebsites.net");
    client.println("Connection: close");
    client.println();

     while (client.connected()){
        String data = client.readStringUntil('\n');
        Serial.println(data);
        if (data=="\r"){
          Serial.println("All Headers Recieved");
          break;
        }
    }
    client.stop();
  }
}

//Get request to update interrupt value
void getInterrupt(){
  client.setInsecure();
  if (!client.connect(host,443)){
    Serial.println("Cannot connect to host");
  } else {
    client.println("GET https://tamagotchi2.azurewebsites.net/UpdateInterrupts?username="+currentUsername+" HTTP/1.1");
    client.println("Host: tamagotchi2.azurewebsites.net");
    client.println("Connection: close");
    client.println();

     while (client.connected()){
        String data = client.readStringUntil('\n');
        Serial.println(data);
        if (data=="\r"){
          Serial.println("All Headers Recieved");
          break;
        }
    }
    client.stop();
  }
}

//Increments interrupt and keeps the pet awake until light levels are lowerred
void bright(){
    amountInterrupt += 1;
    Serial.println(amountInterrupt);
    int sensorValue = analogRead(photoResistor);
    Serial.println("It's too bright for the pet to sleep. Make it dark to continue with the meditation");
    analogWrite(led, LOW);
    while (sensorValue <= 1000){
      sensorValue = analogRead(photoResistor);
    }
}

void handlePageMeditate(){
  Serial.println("GET /meditate");
  server.send(200, "text/html", meditate::runPage());
  sleep();
}

//Sleep method - timer with a photoresistor to measure light intensity and an led to mimick breathing patterns. Call to get requests accordingly
void sleep(){  
  delay(1000);
  unsigned int interval = 60000; //one minute in ms

  elapsedMillis timeElapsed;

  int sensorValue = analogRead(photoResistor);
  Serial.println(sensorValue);

  while(timeElapsed < interval){
      sensorValue = analogRead(photoResistor);
      //Serial.println(sensorValue);
      display.clearDisplay();
      display.drawBitmap(0, 0, animations::corgiSleep, 64, 128, WHITE);
      display.display();

      if (sensorValue <= 1000){
        display.clearDisplay();
        display.drawBitmap(0, 0, animations::corgiHappy, 64, 128, WHITE);
        display.display();
        bright();
      } else {
        // set the brightness of pin 9:
        analogWrite(led, brightness);

        // change the brightness for next time through the loop:
        brightness = brightness + fadeAmount;

        //Wait three seconds - gives the user a chance to breathe out
        if (brightness <= 0){
            delay(3000);
        }

        // reverse the direction of the fading at the ends of the fade:
        if (brightness <= 0 || brightness >= 255) {
          fadeAmount = -fadeAmount;
        }

        // wait for 30 milliseconds to see the dimming effect
        delay(30);
      }
  }
  sleepingNow = 1;
  display.clearDisplay();
  display.drawBitmap(0, 0, animations::corgiExcited, 64, 128, WHITE);
  display.display();
  digitalWrite(led, LOW);
  getMinute();
  
  if (amountInterrupt > 0){
    for (int i = 0; i < amountInterrupt/2; i++){
      getInterrupt();
      delay(100);
    }
  }
  meditate::playEndingTune();

  //Reset variable
  amountInterrupt = 0;
}

//Get request to update games
void getGames(){
  client.setInsecure();
  if (!client.connect(host,443)){
    Serial.println("Cannot connect to host");
  } else {
    client.println("GET https://tamagotchi2.azurewebsites.net/UpdateGames?username="+currentUsername+" HTTP/1.1");
    client.println("Host: tamagotchi2.azurewebsites.net");
    client.println("Connection: close");
    client.println();
    
     while (client.connected()){
        String data = client.readStringUntil('\n');
        Serial.println(data);
        if (data=="\r"){
          Serial.println("All Headers Recieved");
          break;
        }
    }
    client.stop();
  }
}

//Get request to update wins
void getWins(){
  client.setInsecure();
  if (!client.connect(host,443)){
    Serial.println("Cannot connect to host");
  } else {
    client.println("GET https://tamagotchi2.azurewebsites.net/UpdateWins?username="+currentUsername+" HTTP/1.1");
    client.println("Host: tamagotchi2.azurewebsites.net");
    client.println("Connection: close");
    client.println();

     while (client.connected()){
        String data = client.readStringUntil('\n');
        Serial.println(data);
        if (data=="\r"){
          Serial.println("All Headers Recieved");
          break;
        }
    }
    client.stop();
  }
}

void handleDraw(){
  Serial.println("GET /draw");
  server.send(200, "text/html", draw);
}

void handleLoss(){
  Serial.println("GET /loss");
  server.send(200, "text/html", loss);
}

void handleWin(){
  Serial.println("GET /win");
  server.send(200, "text/html", win);
}

//Uses a random number for CPU choice and compares this with what the user inputs
void handlePlay(){

  randomNumber = random(1,4);
  
  bool boolPlay = 0;
  int playResult = 0;
  //Playresult 1 = Draw
  //PlayResult 2 = Loss
  //PlayResult 3 = Win 

  //display the random number on the serial monitor
  Serial.print("The Random Number is = ");
  Serial.println(randomNumber);

  if (server.hasArg("ROCK")){
     boolPlay = 1;
     if (randomNumber == 1){
      playResult = 1;
      display.clearDisplay();
      display.drawBitmap(0, 0, animations::rock, 64, 128, WHITE);
      display.display();
      Serial.println("It's a Draw!");
    } else if (randomNumber == 2){
      playResult = 2;
      display.clearDisplay();
      display.drawBitmap(0, 0, animations::paper, 64, 128, WHITE);
      display.display();
      Serial.println(petName);
      Serial.print("WINS!");
    } else if (randomNumber == 3){
      playResult = 3;
      display.clearDisplay();
      display.drawBitmap(0, 0, animations::scissors, 64, 128, WHITE);
      display.display();
      Serial.println(currentUsername);
      Serial.print("WINS!");
    }
    
  } else if (server.hasArg("PAPER")){
    boolPlay = 1;
    if (randomNumber == 1){
      playResult = 3;
      display.clearDisplay();
      display.drawBitmap(0, 0, animations::rock, 64, 128, WHITE);
      display.display();
      Serial.println(currentUsername);
      Serial.print("WINS!");
    } else if (randomNumber == 2){
      playResult = 1;
      display.clearDisplay();
      display.drawBitmap(0, 0, animations::paper, 64, 128, WHITE);
      display.display();
      Serial.println("It's a Draw!");
    } else if (randomNumber == 3){
      playResult = 2;
      display.clearDisplay();
      display.drawBitmap(0, 0, animations::scissors, 64, 128, WHITE);
      display.display();
      Serial.println(petName);
      Serial.print("WINS!");
    }
  } else if (server.hasArg("SCISSORS")){
    boolPlay = 1;
    if (randomNumber == 1){
      playResult = 2;
      display.clearDisplay();
      display.drawBitmap(0, 0, animations::rock, 64, 128, WHITE);
      display.display();
      Serial.println(petName);
      Serial.print("WINS!");
    } else if (randomNumber == 2){
      playResult = 3;
      display.clearDisplay();
      display.drawBitmap(0, 0, animations::paper, 64, 128, WHITE);
      display.display();
      Serial.println(currentUsername);
      Serial.print("WINS!");
    } else if (randomNumber == 3){
      playResult = 1;
      display.clearDisplay();
      display.drawBitmap(0, 0, animations::scissors, 64, 128, WHITE);
      display.display();
      Serial.println("It's a Draw!");
    }
  }

  if(boolPlay == 0){
    display.clearDisplay();
    display.drawBitmap(0, 0, animations::corgiWave, 64, 128, WHITE);
    display.display();
    Serial.println("GET /play");
    server.send(200, "text/html", play);
  } else {
    if (!inStudy){
      delay(1000);
      if (playResult == 1){
        display.clearDisplay();
        display.drawBitmap(0, 0, animations::corgiLove, 64, 128, WHITE);
        display.display();
        getGames();
        handleDraw();
        Serial.println("GET /draw");
        server.send(200, "text/html", draw);
      } else if (playResult == 2){
        display.clearDisplay();
        display.drawBitmap(0, 0, animations::corgiCheeky, 64, 128, WHITE);
        display.display();
        getGames();
        handleLoss();
        Serial.println("GET /loss");
        server.send(200, "text/html", loss);
      } else if (playResult == 3){
        display.clearDisplay();
        display.drawBitmap(0, 0, animations::corgiAngry, 64, 128, WHITE);
        display.display();
        getWins();
        delay(500);
        getGames();
        handleWin();
        Serial.println("GET /win");
        server.send(200, "text/html", win);
      }
    } else {
      if (playResult == 3){
        getWins();
      } else {
        getGames();
      }

      Serial.println("GET /playResults");
      server.send(200, "text/html", playResults::runStudyPlay(playResult));
    }
  }
}

//Get request for all contents of the petDetails table
void handleStats(){
  client.setInsecure();
  if (!client.connect(host,443)){
    Serial.println("Cannot connect to host");
  } else {
    client.println("GET https://tamagotchi2.azurewebsites.net/GetEverythingPet?username="+currentUsername+" HTTP/1.1");
    client.println("Host: tamagotchi2.azurewebsites.net");
    client.println("Connection: close");
    client.println();
    
     while (client.connected()){
        String data = client.readStringUntil('\n');
        Serial.println(data);
        if (data=="\r"){
          Serial.println("All Headers Recieved");
          break;
        }
    }

    while (client.available()) {
      char c = client.read();
      Serial.write(c);
      json+=c;
    }

    //Prints the json string
    json = json.substring((json.indexOf("{")), json.lastIndexOf("}")+1);
    Serial.println("Start");
    Serial.println(json.c_str());
    Serial.println("End");

    client.stop();
      // Deserialize the JSON document
    DeserializationError error = deserializeJson(doc, json);

    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      return;
    }
     
     String retrievedWins = doc["wins"];
     String retrievedGames = doc["games"];
     String retrievedMinutes = doc["minutes"];  
     String retrievedInterrupts = doc["interrupts"];
     json.clear();

     Serial.println("GET /stats");
     server.send(200, "text/html", stats::runPage(retrievedWins, retrievedGames, retrievedMinutes, retrievedInterrupts, petName));
  }
}

void handleWhileStudy(){
  display.clearDisplay();
  display.drawBitmap(0, 0, animations::corgiWave, 64, 128, WHITE);
  display.display();
  
  timer();
  
  Serial.println("GET /whileStudying");
  server.send(200, "text/html", whileStudying);
}

void timer(){
  Serial.println("We got to timer");
  elapsedMillis time;
  unsigned int interval = 30000; //one minute in ms
  while (time < interval){
    server.send(200, "text/html", whileStudying);
    if (time == (interval)){
      Serial.println("The buzzer plays a tune");
      digitalWrite(buzzer,HIGH);
      delay(1000);//wait for 1ms
      digitalWrite(buzzer,LOW);
    }
  }
}

void handleStudy(){
  if (server.hasArg("TEST")){
    inStudy = 1;
    handleWhileStudy();
  }

  if (inStudy == 0){
    Serial.println("GET /study");
    server.send(200, "text/html", study);
  }
}

void setup(void){
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); //disable brownout detector
  Serial.begin(921600);

  pinMode(led, OUTPUT);
  pinMode(buzzer,OUTPUT);//initialize the buzzer pin as an output

  //reset OLED display via software
  pinMode(OLED_RST, OUTPUT);
  digitalWrite(OLED_RST, LOW);
  delay(20);
  digitalWrite(OLED_RST, HIGH);

  //initialize OLED
  Wire.begin(OLED_SDA, OLED_SCL);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3c, false, false)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  
  display.setRotation(1);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0,0);
  display.println("Please connect your device to start.");
  display.display();

  WiFi.begin(ssid, password);
  //WiFi.begin(ssid);
  Serial.println("");

  //Connects to WiFi
  //   if (WiFi.config(staticIP, gateway, subnet) == false) {
  //    Serial.println("Configuration failed.");
  //  }

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(analogRead(A0)); 

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  //Handle pages
  server.on("/", handleRoot);
  server.on("/page2", handlePage2);
  server.on("/page3", handlePage3);
  server.on("/page4", handlePage4);
  server.on("/meditate", handlePageMeditate);
  server.on("/play", handlePlay);
  server.on("/draw", handleDraw);
  server.on("/loss", handleLoss);
  server.on("/win", handleWin);
  server.on("/stats", handleStats);
  server.on("/study", handleStudy);
  server.on("/whileStudying", handleWhileStudy);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
}
