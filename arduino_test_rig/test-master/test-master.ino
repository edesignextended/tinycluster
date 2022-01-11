// Tiny Cluster - Master-Slave test rig
// Henk Mulder
// eDesign Extended
// d1x1.com
//
// This is code for the master. It requests a series of calculations from the slave, 
// which is a i2c calculator module.

#include <Wire.h>

const int SLAVE = 7;            // address of slave node
const int OP_ADD = 1;           // opcode for addition
const int OP_SUB = 2;           // opcode for subtraction
const int OP_MUL = 3;           // opcode for multiplication
const int OP_DIV = 4;           // opcode for division

void setup() {
  Wire.begin(); // connect to i2c
  Serial.begin(115200); 
}


void loop() {
  Serial.print("8 + 101 = ");
  Serial.println(requestCalculation(OP_ADD, 8,101));
  Serial.print("72 - 8 = ");
  Serial.println(requestCalculation(OP_SUB, 72 ,8));
  Serial.print("7 * 11 = ");
  Serial.println(requestCalculation(OP_MUL, 7,110));
  Serial.print("12 / 2 = ");
  Serial.println(requestCalculation(OP_DIV, 12,2));
  Serial.println();
  
  delay(500);
}


byte requestCalculation(byte opcode, byte a,byte b){
  // send request for addition of two bytes
  Wire.beginTransmission(SLAVE);   // transmit to slave
  Wire.write(opcode);              // opcode for multiplication
  Wire.write(a);                   // first value
  Wire.write(b);                   // second value
  Wire.endTransmission();          // end transmission with slave

  Wire.requestFrom(SLAVE, 1);      // request 1 byte response from the slave

  byte answer;      
  while (Wire.available()) {  
    answer = Wire.read();          // receive a response     
  }
  return answer;
}
