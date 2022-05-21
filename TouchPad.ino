
#include <Wire.h>
#include "mtch6102.h"


MTCH6102 mtch;

void setup() {

  uint8_t data;

  Serial.begin(115200);
  delay(500);
//
  mtch = MTCH6102();
  mtch.begin( (uint8_t)0x25, 6);

  mtch.setMode( MTCH6102_MODE_FULL);
//  mtch.setMode( MTCH6102_MODE_TOUCH);
  
//  mtch.writeRegister(MTCH6102_NUMBEROFXCHANNELS, 0x09);
//  mtch.writeRegister(MTCH6102_NUMBEROFYCHANNELS, 0x06);
//  mtch.writeRegister(MTCH6102_MODE, MTCH6102_MODE_FULL);
//  mtch.writeRegister(HORIZONTALSWIPEDISTANCE, 0x04);
//  mtch.writeRegister(MINSWIPEVELOCITY, 0x02);
//  mtch.writeRegister(TAPDISTANCE, 0x02);
//  mtch.writeRegister(BASEPOSFILTER, 0x00);
//  mtch.writeRegister(BASENEGFILTER, 0x00);
//  mtch.writeRegister(MTCH6102_CMD, 0x20);

  mtch.showCoreRamMemoryMap();
}

void loop() {
  
  byte data;

  data = mtch.readReg(GESTURESTATE);
  
  if (data != 0) {
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

  delay(50);
}
