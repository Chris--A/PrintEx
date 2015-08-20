/********************************************************************************
    Copyright 2015 Christopher Andrews.
    https://github.com/Chris--A/PrintEx

    Released under MIT licence.
********************************************************************************/

#include <PrintEx.h>

void setup() {


  /***  NOTE: See the readme for the features supported in sprintf/printf ***/


  Serial.begin( 9600 );

  //Printing a formatted string to a RAM buffer.
  char buff[ 100 ];
  GString g( buff );
  g.printf( "%17n\nFlash string [%p]\nA decimal:%f\nDEC: %ld\nHEX: %lx\n%17n\n", '-', F("Hi from flash!"), 3.1415f, 65000, 65000, '-' );

  //Output result
  Serial.print( g );
  
  
  //You can also use sptrinf on the buffer directly (as usual, however it now supprts the extra features):
  sprintf( buff, "%17n\nsprintf using doubles\n%17n\n", '=', 123.456f, '=' );
  Serial.print( buff );

  
  //Using formatted stirngs without a buffer.
  PrintEx serial = Serial; //Wrap the Serial object in a PrintEx interface.

  serial.printf( "%17n\nFlash string [%p]\nA decimal:%f\nDEC: %ld\nHEX: %lx\n%17n", '-', F("Hi from flash!"), 3.1415f, 65000, 65000, '-' );

  /***
  For streaming communication, you can use StreamEx.
  It allows usage of standard stream functions like read(), parseInt(),...
  just with the PrintEx features included.

  StreamEx serial = Serial;

  ***/

}

void loop() {}
