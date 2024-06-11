#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// OLED 
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// IR connections 
# define Left 36
# define Center 39
# define Right 34

// motor driver connections
# define ENA 26
# define IN1 27
# define IN2 14
# define IN3 12
# define IN4 13
# define ENB 15

// ultrasonic sensor connections
# define TRIGGER_PIN  33
# define ECHO_PIN 32
# define MAX_DISTANCE 400

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE) ;

void setup() 
{
   
   Serial.begin(9600);

   // ir sensor
   pinMode(Left, INPUT);
   pinMode(Center, INPUT);
   pinMode(Right, INPUT);

   pinMode(ENA, OUTPUT);
   pinMode(IN1, OUTPUT);
   pinMode(IN2, OUTPUT);
   pinMode(IN3, OUTPUT);
   pinMode(IN4, OUTPUT);
   pinMode(ENB, OUTPUT);
   // end ir //

   // motor driver
       // MOTOR 1
   digitalWrite(IN1, HIGH);
   digitalWrite(IN2, LOW);
      // MOTOR 2
   digitalWrite(IN3, LOW);
   digitalWrite(IN4, HIGH);
   
 //OLED Display 
    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
}

void loop() {
   for ir sensor 
    Serial.print (analogRead (left));
    Serial.print (" ");
    Serial.print (analogRead (center));
    Serial.print (" ");
    Serial.print (analogRead (right));
    Serial.println (" ");
    delay(100);  

    Forward();
    delay(1000);
    Left_turn();
    delay(1000);
    Forward();
    delay(1000);
    Right_turn();
    delay(1000); 

  line_follow();

 obstacle_avoid();
    
}

void Forward()
{
  analogWrite(ENA, 80);
  analogWrite(ENB, 80);
}
void Left_turn()
{
  analogWrite(ENA, 80);
  analogWrite(ENB, 0);
}
void Right_turn()
{ 
  analogWrite(ENA, 0);
  analogWrite(ENB, 80);
}
void Stop()
{
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

void line_follow()
{
 
   if (analogRead (Left)< 500 && analogRead (Center)< 500 && analogRead (Right)< 500 )
   { Forward();}
   if (analogRead (Left)< 500 && analogRead (Center)< 500 && analogRead (Right)> 500 )
   { Left_turn();}
   if (analogRead (Left)< 500 && analogRead (Center)> 500 && analogRead (Right)< 500 )
   {Stop();}
   if (analogRead (Left)< 500 && analogRead (Center)> 500 && analogRead (Right)> 500 )
   {Left_turn();}
   if (analogRead (Left)> 500 && analogRead (Center)< 500 && analogRead (Right)< 500 )
    {Right_turn();}    
   if (analogRead (Left)> 500 && analogRead (Center)< 500 && analogRead (Right)> 500 )
    {Forward();}
   if (analogRead (Left)> 500 && analogRead (Center)> 500 && analogRead (Right)< 500 )
    {Right_turn();}
   if (analogRead (Left)> 500 && analogRead (Center)> 500 && analogRead (Right)> 500 )
   {Stop();}
}
void obstacle_avoid(){
  Serial.print("Distance = ");
  Serial.print(sonar.ping_cm());
  Serial.println(" cm");

 if(sonar.ping_cm()<= 15)
 {   
  Stop ();
  delay(200);
 }
 
 else
 line_follow();
 display.clearDisplay();
 
  delay(500);
}