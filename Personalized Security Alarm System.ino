#include <Keypad.h>
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include<EEPROM.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);

char password[4];

char initial_password[4], new_password[4];

int i = 0;

int relay_pin = 10;

int servoPin = 11;
int servoPinn = 12;
Servo Servo1;
Servo Servo2;


int buzzer = A0;
int sensorPin1 = A1;
int sensorPin2 = A2;
int sensorPin3 = A3;
int sensorValue1 = 0;
int sensorValue2 = 0;
int sensorValue3 = 0;

char key_pressed = 0;
const byte rows = 4;
const byte cols = 4;
char hexaKeys[rows][cols] = {

  {'1', '2', '3', 'A'},

  {'4', '5', '6', 'B'},

  {'7', '8', '9', 'C'},

  {'*', '0', '#', 'D'}

};

byte rowPins[rows] = {9, 8, 7, 6};
byte colPins[cols] = {5, 4, 3, 2};

Keypad keypad_key = Keypad( makeKeymap(hexaKeys), rowPins, colPins, rows, cols);

char w = 5;


void setup()

{

  lcd.init();
  lcd.init();

  Servo1.attach(servoPin);
  Servo2.attach(servoPinn);
  Servo1.write(30);
  Servo2.write(115);

  pinMode(A2, OUTPUT);
  

  pinMode(relay_pin, OUTPUT);

  lcd.backlight();
  lcd.setCursor(1, 0);

  lcd.print("WELCOME TO THE");

  lcd.setCursor(4, 1);

  lcd.print("PROJECT");

  delay(5000);

  lcd.clear ();

  lcd.print("team C.U.R.I");

  lcd.setCursor(0, 1);

  lcd.print("WIND STAR");

  delay(5000);

  lcd.clear();

  lcd.print("Enter Password");

  lcd.setCursor(0, 1);

  initialpassword();


}




void loop()

{



  digitalWrite(relay_pin, HIGH);

  key_pressed = keypad_key.getKey();

  if (key_pressed == '#')

    change();

  if (key_pressed)

  {

    password[i++] = key_pressed;

    lcd.print(key_pressed);

  }

  if (i == 4)

  {


    delay(200);

    for (int j = 0; j < 4; j++)

      initial_password[j] = EEPROM.read(j);

    if (!(strncmp(password, initial_password, 4)))

    {

      lcd.clear();

      lcd.print("Pass Accepted");

      Servo2.write(30);
      delay(800);
      Servo1.write(150);
      delay(5000);
      Servo1.write(90);
      delay(2000);
      Servo1.write(30);
      delay(700);
      Servo2.write(115);
      delay(500);


      digitalWrite(relay_pin, LOW);

      delay(2000);

      lcd.setCursor(0, 1);

      lcd.print("Pres # to change");

      delay(2000);

      lcd.clear();

      lcd.print("Enter Password:");

      lcd.setCursor(0, 1);

      i = 0;




    }

    else

    {

      if (w == 5)
      {

        digitalWrite(relay_pin, HIGH);




        lcd.clear();

        lcd.print("Wrong Password");

        lcd.setCursor(0, 1);

        lcd.print("4 tries left");

        delay(2000);

        lcd.clear();

        lcd.print("Enter Password");

        lcd.setCursor(0, 1);

        i = 0;

        if (!(strncmp(password, initial_password, 4)))

        {
          return;
        }
        else
        {
          w = w - 1 ;
        }




      }

      else if (w == 4)
      {

        digitalWrite(relay_pin, HIGH);




        lcd.clear();

        lcd.print("Wrong Password");

        lcd.setCursor(0, 1);

        lcd.print("3 tries left");

        delay(2000);

        lcd.clear();

        lcd.print("Enter Password");

        lcd.setCursor(0, 1);

        i = 0;

        w = w - 1 ;

      }

      else if (w == 3)
      {

        digitalWrite(relay_pin, HIGH);




        lcd.clear();

        lcd.print("Wrong Password");

        lcd.setCursor(0, 1);

        lcd.print("2 tries left");

        delay(2000);

        lcd.clear();

        lcd.print("Enter Password");

        lcd.setCursor(0, 1);

        i = 0;

        w = w - 1 ;

      }

      else if (w == 2)
      {

        digitalWrite(relay_pin, HIGH);




        lcd.clear();

        lcd.print("Wrong Password");

        lcd.setCursor(0, 1);

        lcd.print("1 tries left");

        delay(2000);

        lcd.clear();

        lcd.print("Enter Password");

        lcd.setCursor(0, 1);

        i = 0;

        w = w - 1 ;

      }

      else if (w == 1)
      {

        digitalWrite(relay_pin, HIGH);




        lcd.clear();

        lcd.print("Wrong Password");

        lcd.setCursor(0, 1);

        lcd.print("Final try");

        delay(2000);

        lcd.clear();

        lcd.print("Enter Password");

        lcd.setCursor(0, 1);

        i = 0;

        w = w - 1 ;

      }

      else if (w == 0)
      {

        digitalWrite(relay_pin, HIGH);

        lcd.clear();

        lcd.print("Wrong Password");

        delay(1000);

        lcd.clear();

        digitalWrite(buzzer, HIGH);

        lcd.setCursor(0, 0);

        lcd.print("You are not");

        lcd.setCursor(0, 1);

        lcd.print("AUTHORIZED!!");

        delay(5000);

        lcd.clear();

        lcd.print("Enter Password");

        lcd.setCursor(0, 1);

        i = 0;
      }

    }

  }

  sensorValue1 = analogRead(sensorPin1);
  sensorValue2 = analogRead(sensorPin2);
  sensorValue3 = analogRead(sensorPin3);

  if (sensorValue1 < 900)
  {
    digitalWrite (buzzer, HIGH);
  }

  else if (sensorValue2 < 900)
  {
    digitalWrite (buzzer, HIGH);
  }
  else
  {
    digitalWrite(buzzer, LOW);
  }

  if (sensorValue3 < 100)
  {
    Servo2.write(30);
    delay(800);
    Servo1.write(150);
    delay(5000);
    Servo1.write(90);
    delay(2000);
    Servo1.write(30);
    delay(700);
    Servo2.write(115);
    delay(500);
  }



}

void change()

{

  int j = 0;

  lcd.clear();

  lcd.print("Current Password");

  lcd.setCursor(0, 1);

  while (j < 4)

  {

    char key = keypad_key.getKey();

    if (key)

    {

      new_password[j++] = key;

      lcd.print(key);



    }

    key = 0;

  }

  delay(500);




  if ((strncmp(new_password, initial_password, 4)))

  {

    lcd.clear();

    lcd.print("Wrong Password");

    lcd.setCursor(0, 1);

    lcd.print("Try Again");

    delay(1000);

  }

  else

  {

    j = 0;

    lcd.clear();

    lcd.print("New Password:");

    lcd.setCursor(0, 1);

    while (j < 4)

    {

      char key = keypad_key.getKey();

      if (key)

      {

        initial_password[j] = key;

        lcd.print(key);

        EEPROM.write(j, key);

        j++;



      }

    }

    lcd.print("Pass Changed");

    delay(1000);

  }

  lcd.clear();

  lcd.print("Enter Password");

  lcd.setCursor(0, 1);

  key_pressed = 0;

}




void initialpassword() {

  for (int j = 0; j < 4; j++)

    EEPROM.write(j, j + 49);

  for (int j = 0; j < 4; j++)

    initial_password[j] = EEPROM.read(j);

}

