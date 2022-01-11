
// Tiny Cluster - Master-Slave test rig
// Henk Mulder
// eDesign Extended
// d1x1.com
//
// This is code for the slave. it receives operands and an opcode 
// (type of operation required= from the master and returns the 
// response when requested.
// Note that although the masters in this example sends new operands 
// and requests the answers immediately, the reception of operands and
// the request for the answers are asynchronous.
#include <Wire.h>

const int SLAVE = 7;              // address of slave node
int a;
int b;
int opcode;

void setup() {
  Wire.begin(SLAVE);              // join i2c bus with address #8
  Wire.onReceive(receiveEvent);   // set up the receive event
  Wire.onRequest(requestEvent);   // set up the request event
  Serial.begin(115200);           // start serial for output

}

void loop() {
  delay(100);                     // listen for data and requests
}

// The slave has received data from the master
// The data bytes received are: opcode, operand a and operand b

void receiveEvent(int howMany) {
  opcode = Wire.read();           // receive opcode
  Serial.print("opcode: ");       // print opcode
  Serial.println(opcode);         

  while (1 <= Wire.available()) { // loop through all but the last
    a = Wire.read();              // receive byte as a int
    b = Wire.read();              // receive byte as a int
    Serial.print("a = ");          // print opertand a
    Serial.println(a);            
    Serial.print("b = ");          // print opertand b
    Serial.println(b);            // print the int
  }
}


// the master requests data dfrom the slave
// i.e. the answer of the last calculation request

void requestEvent() {
  switch( opcode )
  {
    case 1:                      // addition
        Wire.write(a+b);
        break;
    case 2:                      // subtraction
        Wire.write(a-b);
        break;
    case 3:                      // multiplication
        Wire.write(a*b);
        break;
    case 4:                      // division
        Wire.write(a/b);
        break;
  }
}
