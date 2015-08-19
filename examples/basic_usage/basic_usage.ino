#include <PrintEx.h>

void setup() {
  char buff[ 100 ];
  
  Serial.begin( 9600 );
  
  //GString g( buff );
  //g.printf( "%17n\nFlash string [%p]\nA decimal:%f\nDEC: %ld\nHEX: %lx\n%17n", '-', F("Hi from flash!"), 3.1415f, 65000, 65000, '-' );
  //Serial.print( g );
  
  AnyPrinter serial( Serial );
  serial.printf( "%17n\nFlash string [%p]\nA decimal:%f\nDEC: %ld\nHEX: %lx\n%17n", '-', F("Hi from flash!"), 3.1415f, 65000, 65000, '-' );
  
}

void loop() {}
