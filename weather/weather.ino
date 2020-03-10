#include <Servo.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(14, 15, 16, 17, 18, 19);

const int WEATHER_SUN = 90;
const int WEATHER_SNOW = 180;
const int WEATHER_RAIN = 0;

const int CLOTHING_SUN = 90;
const int CLOTHING_SNOW = 180;
const int CLOTHING_RAIN = 0;

int WEATHER_FORECAST [] = {WEATHER_SUN, WEATHER_RAIN, WEATHER_SNOW, WEATHER_SUN, WEATHER_SUN, WEATHER_SNOW, WEATHER_RAIN};
String DAY [] = {"March 12th (Thu)", "March 13th (Fri)", "March 14th (Sat)", "March 15th (Sun)", "March 16th (Mon)", "March 17th (Tue)", "March 18th (Wed)"};
String DEGREE_VALUES [] = {"+12", "+5", "-7", "+10", "-10", "-12", "0"};

int CURRENT_DAY = 0;

Servo servo_clothing; 
Servo servo_weather;

const int FORWARD_BUTTON = 7;
const int BACKWARD_BUTTON = 5;
const int SUN_BUTTON = 6;
const int WIND_BUTTON = 12;

int count = 200;

void setup() {
  servo_clothing.attach(9);  
  servo_weather.attach(8);
  pinMode (BACKWARD_BUTTON, INPUT);
  pinMode (FORWARD_BUTTON,INPUT);
  pinMode (SUN_BUTTON, OUTPUT);
  pinMode(WIND_BUTTON, OUTPUT);
  Serial.begin(9600);

  lcd.begin(16, 2);
  delay (1000);
  
  CURRENT_DAY = 0;
  weatherChange(WEATHER_FORECAST[CURRENT_DAY]);

  lcd.print("hello");
}

/* Shows weather on lcd, change weather conditions for the next or previous day */
void loop() {
   show_day_and_weather_on_lcd();
   
   /* Change to the next DAY on click forward */
   if ((digitalRead(FORWARD_BUTTON)==HIGH) && (CURRENT_DAY < (sizeof(WEATHER_FORECAST)/sizeof(WEATHER_FORECAST[0])-1)) && (count>5) ){
    count = 0;
    CURRENT_DAY = CURRENT_DAY + 1;
    weatherChange(WEATHER_FORECAST[CURRENT_DAY]);
   }

   /* Change to the previous DAY on click backward */
   if ((digitalRead(BACKWARD_BUTTON)==HIGH) && CURRENT_DAY > 0 && (count>5)){
    count = 0;
    CURRENT_DAY = CURRENT_DAY -1;
    weatherChange(WEATHER_FORECAST[CURRENT_DAY]);
   }

   count =count + 1;
   delay(200);
}

/* Shows day, weather information on display (Reference 1)*/
void show_day_and_weather_on_lcd(){
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print(DAY[CURRENT_DAY]);
   lcd.setCursor(0, 1);
   lcd.print(DEGREE_VALUES[CURRENT_DAY]);
   lcd.setCursor(3, 1);
   lcd.print(char(223));
   lcd.setCursor(4, 1);
   lcd.print("C");
   lcd.setCursor(6, 1);
   lcd.print("DAY: ");
   lcd.setCursor(10, 1);
   lcd.print(CURRENT_DAY+1);
}


/* Sends request to update song (Reference 2)*/
void send(String message){
  Serial.println(message);
  Serial.print("\n");
  Serial.flush();
  delay(50);
}


/* Changes clothing (Refernce 3)*/
void changeClothing(int clothing){
  servo_clothing.write(clothing);
}


/* Updates weather condition settings based on parameter weather (References 3, 4) */
void weatherChange(int weather){
  /* Resets settings from previous state: */
  digitalWrite(SUN_BUTTON, LOW);
  digitalWrite(WIND_BUTTON, LOW);
  send("StopBirds");
  send("StopWind");
  send("StopRain");
  
  /* Change weather, clothing and song:*/
  servo_weather.write(weather);
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

/* REFERENCES: 
* 1) Code for Assignment 1: 
* https://github.com/Olga-Chitsvarina/Arduino/blob/master/lcd_display/lcd_display.ino
* 2) Code from first trial with Python Script for Assignment 2: 
* https://github.com/Olga-Chitsvarina/Arduino-Musical-Instrument/commit/9d6f0b9ff605cd5f3fa7680977aacec84ca2638b
* 3) Build in Arduino IDE examples for 
* Servo (Knob, Sweep), Basics (Blink)
* 4) This video that explains basics of working with transistors: 
* https://www.youtube.com/watch?v=gEMBXxWKUS0
*/
