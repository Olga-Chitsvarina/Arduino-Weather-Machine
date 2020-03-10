#include <Servo.h>

const int WEATHER_SUN = 90;
const int WEATHER_SNOW = 180;
const int WEATHER_RAIN = 0;

const int CLOTHING_SUN = 90;
const int CLOTHING_SNOW = 180;
const int CLOTHING_RAIN = 0;

int weather_forecast [] = {WEATHER_SUN, WEATHER_RAIN, WEATHER_SNOW, WEATHER_SUN, WEATHER_SUN, WEATHER_SNOW, WEATHER_RAIN, WEATHER_SNOW};
int current_day = 0;

Servo servo_clothing; 
Servo servo_planner;

const int FORWARD_BUTTON = 7;
const int BACKWARD_BUTTON = 5;
const int SUN_BUTTON = 6;
const int WIND_BUTTON = 12;

int count = 200;

void setup() {
  servo_clothing.attach(9);  
  servo_planner.attach(8);
  pinMode (BACKWARD_BUTTON, INPUT);
  pinMode (FORWARD_BUTTON,INPUT);
  pinMode (SUN_BUTTON, OUTPUT);
  pinMode(WIND_BUTTON, OUTPUT);
  Serial.begin(9600);
  current_day = 0;
  weatherChange(weather_forecast[current_day]);
}

void loop() {
   if ((digitalRead(FORWARD_BUTTON)==HIGH) && (current_day < (sizeof(weather_forecast)/sizeof(weather_forecast[0])-1)) && (count>5) ){
    count = 0;
    current_day = current_day + 1;
    weatherChange(weather_forecast[current_day]);
   }
    
   if ((digitalRead(BACKWARD_BUTTON)==HIGH) && current_day > 0 && (count>5)){
    count = 0;
    current_day = current_day -1;
    weatherChange(weather_forecast[current_day]);
   }

   count =count + 1;
   delay(200);
}

void send(String message){
  Serial.println(message);
  Serial.print("\n");
  Serial.flush();
  delay(50);
}

void changeClothing(int clothing){
  servo_clothing.write(clothing);
}

void weatherChange(int weather){
  digitalWrite(SUN_BUTTON, LOW);
  digitalWrite(WIND_BUTTON, LOW);
  send("StopBirds");
  send("StopWind");
  send("StopRain");
  
  servo_planner.write(weather);
  
  switch (weather) {
  case WEATHER_SUN:
    changeClothing(CLOTHING_SUN);
    digitalWrite(SUN_BUTTON, HIGH);
    send("StartBirds");
    break;
  case WEATHER_RAIN:
    changeClothing(CLOTHING_RAIN);
    send("StartRain");
    break;
  case WEATHER_SNOW:
    digitalWrite(WIND_BUTTON, HIGH);
    changeClothing(CLOTHING_SNOW);
    send("StartWinter");
    break;
  default:
    break;
  }
  
}
