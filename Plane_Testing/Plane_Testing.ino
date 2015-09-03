#include <Servo.h>
#include <SoftwareSerial.h>

#define COMMANDSIZE 17
#define rxPin 2
#define txPin 3

SoftwareSerial wifly(rxPin, txPin);

Servo servoAil; //servo for aileron control
Servo servoEle; //servo for elevator control
Servo servoMot; //servo for motor control
Servo servoRud; //servo for rudder control

//get commands checking for beginning and end of string
void GetCommands(char *commandBuffer)
{
  char readByte = '0';
  char i = 0;
  
  Serial.println("inside getcommands");
  Serial.write(wifly.read());
  Serial.println();
  readByte = wifly.read();
  while(readByte != 'e' && i < COMMANDSIZE )
  {
    if(wifly.available())
    {    
      commandBuffer[i] = readByte;
      Serial.write(readByte);
      Serial.println();
      i++;
      readByte = wifly.read();
    }
  }
}

//parse out the commas getting the command values
void ParseCommands(short int *commands, char *commandBuffer)
{
  char *hold = NULL;
  char i = 0;
  
  Serial.println("inside parse commands");
  
  hold = strtok(commandBuffer, ",");
  while(i < 4)
  {
    commands[i] = atoi(hold);
    i++;
    hold = strtok(NULL, ",");
  }
}

void setup() {
  // put your setup code here, to run once:
  servoAil.attach(5, 500,2500);
  servoEle.attach(6, 500, 2500);
  servoMot.attach(7, 500, 2500); // will have to find range of motor
  servoRud.attach(8, 500, 2500);
  
  servoAil.write(90);
  servoEle.write(90);
  servoMot.write(90);
  servoRud.write(90);
  
  Serial.begin(9600);
  wifly.begin(9600); 
}

void loop() {
  short int commands[4];
  char commandBuffer[18];
  
  memset(&commands[0], 0, sizeof(commands));
  memset(&commandBuffer[0], 0, sizeof(commandBuffer));
  
  // put your main code here, to run repeatedly:
  
  if(wifly.peek() == 'b')
  {
    Serial.println("before get commands");
    GetCommands(&commandBuffer[0]);
    ParseCommands(&commands[0], commandBuffer);
   /* 
    Serial.println("sending servo commands");
    Serial.println(commands[0], DEC);
    servoAil.write(commands[0]);
    Serial.println(commands[1], DEC);
    servoEle.write(commands[1]);
    Serial.println(commands[2], DEC);
    servoMot.write(commands[2]);
    Serial.println(commands[3], DEC);
    servoRud.write(commands[3]);
    delay(40);  
    
    */
  }
}

