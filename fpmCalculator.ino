// Color sensor wiring to arduino
#define s0 4
#define s1 5
#define s2 6
#define s3 7
#define outPin 8
#define led 13
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int redFrequency,redColor,i,p2;
float bpm,bps,elapsed;
int count = 0;
unsigned long start,start1,start2,start3,start4,finish,k;

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(outPin, INPUT); // from sensor becomes input to Arduino
  pinMode(13, OUTPUT);

  //Set frequency scaling
  digitalWrite(s0,HIGH);
  digitalWrite(s1,HIGH);  //frequency scaling 100%

  //lcd setting
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print("FPM Calculator");
  delay(1000);
  
   
  Serial.begin(9600);

}

void loop() 
{
    //setting for red
    digitalWrite(s2,LOW);
    digitalWrite(s3,LOW);
    digitalWrite(led,LOW);

    redFrequency = pulseIn(outPin, LOW); //read output
    // Remaping the value of red from 0 to 255, to show in hex codes
    redColor = map(redFrequency, 3, 30, 255,0);
    //delay(1000);

    for (i = 0; i < 1; i++)
   {
    if (redColor > 200 && redColor < 255 && count < 1)
    {
      start1 = millis();
      Serial.println(start1);
      delay(1000); //need to change based on duration of flashing
      count++;
      Serial.println(count); 
    }
    else if (redColor > 200 && redColor < 255 && count < 2)
        {
          delay(1000); //need to change based on duration of flashing
          count++;
          Serial.println(count);      
         }
     else if (redColor > 200 && redColor < 255 && count < 3)
            {
              delay(1000); //need to change based on duration of flashing
              count++;
              Serial.println(count);      
             }
      else if (redColor > 200 && redColor < 255 && count < 4)
                  {
                    start4 = millis();
                    Serial.println(start4);
                    delay(1000); //need to change based on duration of flashing
                    count++;
                    Serial.println(count);
              
                    if(count == 4)
                    {
                     finish = start4;
                     elapsed = (float)(finish-start1)/1000;
                     Serial.print("Elapsed time is: ");
                     Serial.println(elapsed);
                     float p = elapsed;
                     Serial.println(p);
                     bps = 3 / p;
                     Serial.println(bps);
                     bpm = bps * 60;
                     lcd.clear();
                     lcd.setCursor(3,0);
                     lcd.print(bpm);
                     lcd.print(" FPM!");
                     
//                     count=0;
                    }
                   }
    }
}
