/***
  PrintAdapter example.

  Explains how to convert a Print object to a Stream.
  PrintAdapter implements an empty Stream object around
  an existing Print object.

  This is useful for passing a Print object to a function
  which only prints data, but accepts a Stream object.
***/


#include <PrintEx.h>

void setup() {

  Serial.begin(9600);

  char buffer[50];               //Create buffer to store output.
  GString str = buffer;          //Wrap the buffer in a GString, making it printable.
  PrintAdapter streamer = str;   //Convert a Print object to a Stream object.

  func( streamer );              //Can now call a function expecting a stream.
  
  Serial.print(str);             //Print the GString data.

}

//A function expecting a Stream object.
void func( Stream &stream ){
  stream.print( "foobar" );
}

void loop() { /* No loop code */ }