#include <PrintEx.h>

void setup() {


  /***  NOTE: See the readme for the features supported in sprintf/printf ***/
  
  
  Serial.begin( 9600 );
  
  //Printing a formatted string to a RAM buffer.
  char buff[ 100 ];
  GString g( buff );
  g.printf( "%17n\nFlash string [%p]\nA decimal:%f\nDEC: %ld\nHEX: %lx\n%17n", '-', F("Hi from flash!"), 3.1415f, 65000, 65000, '-' );
  
  //Output result
  Serial.print( g );
  
  
  //Using formatted stirngs without a buffer.
  PrintEx serial = Serial ; //Wrap the Serial object in a PrintEx interface.
  
  serial.printf( "%17n\nFlash string [%p]\nA decimal:%f\nDEC: %ld\nHEX: %lx\n%17n", '-', F("Hi from flash!"), 3.1415f, 65000, 65000, '-' );
  
  /***
  For streaming communication, you can use StreamEx.
  It allows usage of standard stream functions like read(), parseInt(),...
  just with the PrintEx features included.
  
  StreamEx serial = Serial;
  
  ***/
  
}

void loop() {}
