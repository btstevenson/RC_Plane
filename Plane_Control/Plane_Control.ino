#include <Servo.h>

#define COMMANDSIZE 5

Servo servoAil; //servo for aileron control
Servo servoEle; //servo for elevator control
Servo servoMot; //servo for motor control
Servo servoRud; //servo for rudder control

//get commands checking for beginning and end of string
void GetCommands(char *commandBuffer)
{
  servoMot.write(45);
  char readByte = '0';
  char i = 0;
  
  readByte = Serial.read();
  while(readByte != 'e' && i < COMMANDSIZE )
  {
    if(Serial.available())
    {    
      commandBuffer[i] = readByte;
      i++;
      readByte = Serial.read();
    }
  }
}

//parse out the commas getting the command values
void ParseCommands(short int *commands, char *commandBuffer)
{
  char *hold = NULL;
  char i = 0;
  
  servoMot.write(135);
  
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
  servoEle.attach(6, 500,2500);
  servoMot.attach(7, 500,2500); // will have to find range of motor
  servoRud.attach(8, 500,2500);
  
  servoAil.write(90);
  servoEle.write(90);
  servoMot.write(90);
  servoRud.write(90);
  
  Serial.begin(9600); //using UART for wifly 
}

void loop() {
  short int commands[4];
  char commandBuffer[18];
  
  memset(&commands[0], 0, sizeof(commands));
  memset(&commandBuffer[0], 0, sizeof(commandBuffer));
  
  // put your main code here, to run repeatedly:
  if(Serial.peek() == 'b')
  {
    Serial.read();
    GetCommands(&commandBuffer[0]);
    ParseCommands(&commands[0], commandBuffer);
    
    servoAil.write(commands[0]);
    servoEle.write(commands[1]);
    servoMot.write(commands[2]);
    servoRud.write(commands[3]);
  }
}
