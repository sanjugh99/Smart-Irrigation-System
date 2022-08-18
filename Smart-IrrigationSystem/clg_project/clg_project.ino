// First two lines , copied from the blynk web dashboard
#define BLYNK_TEMPLATE_ID "TMPL_aTegc3N"
#define BLYNK_DEVICE_NAME "PLANT MONITORING SYSTEM"
#define BLYNK_AUTH_TOKEN "AlHWWcfhSss26vEGSj8ObouvbMWm-5zl"
// Need to define these libraries for compiling
#define BLYNK_PRINT Serial
#include <SPI.h>
#include <DHT.h>
#include <OneWire.h>
#include <BlynkSimpleEsp8266.h>
#include <DallasTemperature.h>
OneWire oneWire(ONEWIRE_CRC);
DallasTemperature sensors(&oneWire);

// The auth token should be copied from your mail id in the registration time on blynk.io
char auth[] ="AlHWWcfhSss26vEGSj8ObouvbMWm-5zl";
// Put your wifi name and password
char ssid[] = "POCO M2";     //your wifi name
char pass[] = "munnA@01";  //your password name

// Need to define these libraries for compiling
#define ONE_WIRE_BUS D2
#define DHTPIN 2
#define DHTTYPE DHT11
//#define motor 25
#define moistureSensor 35

// INITIALISATION
int motor = 5;
int MotorState=0;
int moistureState =0;
int lastmoisState=0;

// Algorithm Start
DHT dht(DHTPIN, DHTTYPE);
BLYNK_CONNECTED() 
{
  Blynk.syncVirtual(V0);
}
BLYNK_WRITE(V0)
{
  MotorState = param.asInt();  
  if (MotorState==1)
  {
    digitalWrite(motor,HIGH);
    Serial.println("Motor ON");
  }
  else
  {
    digitalWrite(motor,LOW);
    Serial.println("Motor OFF");
  }
} 
SimpleTimer timer;
void humidityTemparatureSensor()
{
  //Read the humidty temparature data from DHT11 sensor.
  float humidity = dht.readHumidity();
  float temparature = dht.readTemperature();

  //Condition, if the sensor getting error to read data.
  if (isnan(humidity) || isnan(temparature))
  {
    Serial.println("Failed to read data from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V5, humidity); //V5 is for Humidity
  Blynk.virtualWrite(V6, temparature); //V6 is for Temperature
  Serial.print("Current Humidity is: ");
  Serial.println(humidity);
  Serial.print("Current Temperature is: ");
  Serial.println(temparature);

   if(temparature > 25){
    Blynk.logEvent("temp_alert","Current temparature is crossing 25 degree");
    Serial.println("temperature  alert, notification sent ");
   }
}

void setup()
{
  Serial.begin(115200);
  //digitalWrite(8, HIGH); 
  pinMode(motor, OUTPUT);                  
  dht.begin();
  timer.setInterval(1000L, humidityTemparatureSensor);
  Blynk.begin(auth, ssid, pass);
  sensors.begin();
}
int sensor=0;
int soilMoisture=0;

void sendSoilMoistureData()
{
    sensor=analogRead(A0);
    //in place 108 there is 100(it change with the change in sensor)
    soilMoisture=(108-map(sensor,0,1023,0,100)); 
    delay(1000);
    sensors.requestTemperatures();
    float temp = sensors.getTempCByIndex(0);
    Serial.print("Current Soil Moisture is: ");
    Serial.print(soilMoisture);
    Serial.println('%');

    //Conditional statements
    if(soilMoisture > 30) 
    {
      Serial.println("NO MORE WATER NEEDED, ENOUGH WATER IN THE PLANT");
      delay(1000);
    } 
    else if (soilMoisture < 15) 
    {
      Serial.println("WARNING!! NEED WATER, notification sent ");
      Blynk.logEvent ("water_alert","Water your plants , it is becoming dry! ");
    }
    Blynk.virtualWrite(V1, temp);
    Blynk.virtualWrite(V2,soilMoisture);
    delay(1000);
}

//Looping methods
void loop()

{
  Blynk.run();
  timer.run();
  sendSoilMoistureData();
}























//#define BLYNK_TEMPLATE_ID "TMPL_aTegc3N"
//#define BLYNK_DEVICE_NAME "PLANT MONITORING SYSTEM"
//
//#define BLYNK_PRINT Serial
//#include <OneWire.h>
//#include <SPI.h>
//#include <BlynkSimpleEsp8266.h>
//#include <DHT.h>
//#include <DallasTemperature.h>
//#define ONE_WIRE_BUS D2
//OneWire oneWire(ONEWIRE_CRC);
//DallasTemperature sensors(&oneWire);
//char auth[] ="lCQ61HQ9OBbGvpiio1hrMIr4dUGOvcWb";
//char ssid[] = "samik1";
//char pass[] = "puja@1234";
//#define DHTPIN 2
//#define DHTTYPE DHT11
//#define motor 25
//#define moistureSensor 35
///////INITIALISATION///
//int MotorState=0;
//int moistureState =0;
//int lastmoisState=0;
//
//DHT dht(DHTPIN, DHTTYPE);
//BLYNK_CONNECTED() {
//  Blynk.syncVirtual(V0);
//}
//
//BLYNK_WRITE(V0)
//{
//MotorState = param.asInt();  
//if (MotorState==1)
//{
//digitalWrite(motor,HIGH);
//Serial.println("Motor ON");
//}
//else
//{
//digitalWrite(motor,LOW);
//Serial.println("Motor OFF");
//}
//} 
//
//SimpleTimer timer;
//
//void sendSensor()
//{
//  
//float h = dht.readHumidity();
//float t = dht.readTemperature();
//
//if (isnan(h) || isnan(t)) {
//Serial.println("Failed to read from DHT sensor!");
//return;
//}
//
//Blynk.virtualWrite(V5, h); //V5 is for Humidity
//Blynk.virtualWrite(V6, t); //V6 is for Temperature
//
//  Serial.print("Humidity: ");
//  Serial.println(h);
//  Serial.print("Temperature: ");
//  Serial.println(t);
//
////   moistureState  = digitalRead(moistureSensor);
//// if (moistureState == 1 && lastmoisState == 0) {
////  Serial.println("needs water, send notification");
////  Blynk.logEvent("WATER","Water your plants");
////  lastmoisState = 1;
////  delay(1000);
////} 
////  else if (moistureState == 1 && lastmoisState == 1) {
////  Serial.println("has not been watered yet");
////  delay(1000);
////  }
////  else {
////    lastmoisState = 0;
////    delay(1000);
////  }
//
//}
//void setup()
//{
//  // int relaypin = D5;
//  Serial.begin(9600);
//  digitalWrite(8, HIGH);                           // Relay Normally Hight for OFF condition
//  dht.begin();
//  timer.setInterval(1000L, sendSensor);
//  Blynk.begin(auth, ssid, pass);
//  sensors.begin();
//}
//int sensor=0;
//int moisture_output=0;
////sendTEMPS//
//void sendTemps()
//{
//     sensor=analogRead(A0);
//     moisture_output=(108-map(sensor,0,1023,0,100)); //in place 145 there is 100(it change with the change in sensor)
//     delay(1000);
//     sensors.requestTemperatures();
//    float temp = sensors.getTempCByIndex(0);
//    //Serial.println(temp);
//    Serial.print("Moisture:  ");
//    Serial.print(moisture_output);
//        Serial.println('%');
//    if(moisture_output > 30) {
//  Serial.println("ENOUGH WATER IN THE PLANT  ");
//
//  delay(2000);
//} 
//  else if (moisture_output < 15) {
//  Serial.println("WARNING!!!!! NEED WATER");
//    Blynk.logEvent("WATER","Water your plants");
//
//  }
//
//    Blynk.virtualWrite(V1, temp);
//    Blynk.virtualWrite(V2,moisture_output);
//    delay(1000);
//}
//
//void loop()
//{
//Blynk.run();
//timer.run();
//sendTemps();
//}
