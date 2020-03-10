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
String day [] = {"March 12th (Thu)", "March 13th (Fri)", "March 14th (Sat)", "March 15th (Sun)", "March 16th (Mon)", "March 17th (Tue)", "March 18th (Wed)"};
String degree_values [] = {"+12", "+5", "-7", "+10", "-10", "-12", "0"};

int current_day = 0;

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
  
  current_day = 0;
  weatherChange(WEATHER_FORECAST[current_day]);

  lcd.print("hello");
}

/* Shows weather on lcd, change weather conditions for the next or previous day */
void loop() {
   show_day_and_weather_on_lcd();
   
   if ((digitalRead(FORWARD_BUTTON)==HIGH) && (current_day < (sizeof(WEATHER_FORECAST)/sizeof(WEATHER_FORECAST[0])-1)) && (count>5) ){
    count = 0;
    current_day = current_day + 1;
    weatherChange(WEATHER_FORECAST[current_day]);
   }
    
   if ((digitalRead(BACKWARD_BUTTON)==HIGH) && current_day > 0 && (count>5)){
    count = 0;
    current_day = current_day -1;
    weatherChange(WEATHER_FORECAST[current_day]);
   }

   count =count + 1;
   delay(200);
}

/* Shows day, weather information on display */
void show_day_and_weather_on_lcd(){
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print(day[current_day]);
   lcd.setCursor(0, 1);
   lcd.print(degree_values[current_day]);
   lcd.setCursor(3, 1);
   lcd.print(char(223));
   lcd.setCursor(4, 1);
   lcd.print("C");
   lcd.setCursor(6, 1);
   lcd.print("Day: ");
   lcd.setCursor(10, 1);
   lcd.print(current_day+1);
}


/* Sends request to update song */
void send(String message){
  Serial.println(message);
  Serial.print("\n");
  Serial.flush();
  delay(50);
}


/* Changes clothing */
void changeClothing(int clothing){
  //servo_clothing.write(clothing);
}


/* Updates weather condition settings based on parameter weather */
void weatherChange(int weather){
  /* Resets settings from previous state: */
  digitalWrite(SUN_BUTTON, LOW);
  digitalWrite(WIND_BUTTON, LOW);
  send("StopBirds");
  send("StopWind");
  send("StopRain");

  /* Change weather, clothing and song:*/
  //servo_weather.write(weather);
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
