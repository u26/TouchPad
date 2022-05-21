
#include <Wire.h>
#include "mtch6102.h"

#define ADDR (byte)0x25


//uint8_t readRegister(uint8_t addr_reg) {
//  
//    uint8_t dt=0;
//    Wire.beginTransmission(ADDR);
//    Wire.write((byte)addr_reg); // register to read
//    Wire.endTransmission(false); 
//
//    Wire.requestFrom(ADDR, 1, false); // read a uint8_t
//    if (Wire.available()) {
//        dt = Wire.read();
//    }
//    Wire.endTransmission(true); 
//
//    return dt;
//    
//
//}
//
//void writeRegister(uint8_t addr_reg, uint8_t dta) {
//  
//    Wire.beginTransmission(ADDR);
//    Wire.write(addr_reg); // register to read
//    Wire.write(dta);
//    Wire.endTransmission();
//}
//bool onoff = false;

MTCH6102 mtch;

void setup() {

  uint8_t data;

  Serial.begin(115200);
  delay(500);
//
  mtch = MTCH6102();
  mtch.begin(ADDR, 6);

  mtch.setMode( MTCH6102_MODE_FULL);
//  mtch.setMode( MTCH6102_MODE_TOUCH);
  

////  mtch.writeRegister(MTCH6102_NUMBEROFXCHANNELS, 0x07);
////  mtch.writeRegister(MTCH6102_NUMBEROFYCHANNELS, 0x03);//最低3点必要なため
////  mtch.writeRegister(MTCH6102_MODE, MTCH6102_MODE_FULL);
////  mtch.writeRegister(HORIZONTALSWIPEDISTANCE, 0x04);
////  mtch.writeRegister(MINSWIPEVELOCITY, 0x02);
////  mtch.writeRegister(TAPDISTANCE, 0x02);
////  mtch.writeRegister(BASEPOSFILTER, 0x00);
////  mtch.writeRegister(BASENEGFILTER, 0x00);
////
////  mtch.writeRegister(MTCH6102_CMD, 0x20);
//  mtch.writeRegister(MTCH6102_MODE, MTCH6102_MODE_TOUCH);

  mtch.showCoreRamMemoryMap();
}

void loop() {
  
  byte data;

//  data = readRegister(0x05);
//  Serial.print("MODE: ");
//  Serial.println(data,HEX);
//
//  
//  data = readRegister( (byte)0x10 );
//  Serial.print("0x10: ");  Serial.println(data,HEX);
//
//  data = readRegister( (byte)0x00 );
//  Serial.print("0x00: ");  Serial.println(data,HEX);
//  data = readRegister( (byte)0x01 );
//  Serial.print("0x01: ");  Serial.println(data,HEX);
//  data = readRegister( (byte)0x02 );
//  Serial.print("0x02: ");  Serial.println(data,HEX);
//  data = readRegister( (byte)0x03 );
//  Serial.print("0x03: ");  Serial.println(data,HEX);
//  data = readRegister( (byte)0x04 );
//  Serial.print("0x04: ");  Serial.println(data,HEX);
//  data = readRegister( (byte)0x05 );
//  Serial.print("0x05: ");  Serial.println(data,HEX);
//  data = readRegister( (byte)0x06 );
//  Serial.print("0x06: ");  Serial.println(data,HEX);
//
//  data = readRegister(0x20);
//  Serial.print("NUMBEROFXCHANNELS: "); Serial.println(data);
//
//  data = readRegister(0x21);
//  Serial.print("NUMBEROFYCHANNELS: "); Serial.println(data);


  data = mtch.readReg(GESTURESTATE);
  if (data != 0) {
    //Serial.println(data, HEX);
    switch(data){
      case LEFT:      
        Serial.println("LEFT");  
        break;
      case RIGHT:      
        Serial.println("RIGHT");  
        break;
      case UP:      
        Serial.println("UP");  
        break;
      case DOWN:      
        Serial.println("DOWN");  
        break;
      case CLICK:      
        Serial.println("CLICK");  
        break;
      case DOUBLE_CLICK:      
        Serial.println("DOUBLE_CLICK");  
        break;
      default:
        break;
    }
  }

// TOUCHSTATE
  data = mtch.readReg(0x10);
//  Serial.print("TOUCHSTATE: ");
//  Serial.println(data,HEX);

  if(data & 0x01){

  uint16_t x,y = 0;
  x = mtch.readReg(0x11);
//  Serial.print("TOUCHX: ");
//  Serial.println(x,HEX);

  y = mtch.readReg(0x12);
//  Serial.print("TOUCHY: ");
//  Serial.println(y,HEX);

// TOUCHLSB
  uint8_t lsb = mtch.readReg(0x13);
//  Serial.print("TOUCHLSB: ");
//  Serial.println(data,HEX);

  x |= (uint16_t)(0xf0 & lsb) >> 8;
  y |= (uint16_t)(0x0f & lsb);

  Serial.print("x: "); Serial.print(x);
  Serial.print("  y: "); Serial.println(y);
  }


//  Serial.print("SENSORVALUE_RX <i>: ");
//  for (uint8_t i = 0x80; i < 0x8E; i++) {
//     data = readRegister(i);
//     
//     //Serial.print(i, HEX);
//    //Serial.print(" = ");
//    Serial.print(data,BIN);
//    Serial.print(", ");
//  }
//  Serial.println();
  
  /*
    data = readRegister(0x80);
    Serial.print("SENSORVALUE<RX0>: ");
    Serial.println(data,BIN);
    data = readRegister(0x8D);
    Serial.print("SENSORVALUE<RX13>: ");
    Serial.println(data,BIN);
    data = readRegister(0x86);
    Serial.print("SENSORVALUE<RX6>: ");
    Serial.println(data,BIN);
*/
    delay(50);
}
