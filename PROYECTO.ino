#include <SoftwareSerial.h>
SoftwareSerial BT( 10 ,11 );

#define config 7
#define buzzer 6
#define R 5
#define A 4
#define V 3
#define SensorTEMP A1

String dato;

void setup()
{
  Serial.begin( 9600 );
  
  Pins();
}

void loop()
{ 
  configurarBT();
  if( !configurarBT() )
  {
     if( dato == "on" )
       {
          LedsON();
       }
     else if( dato == "off" )
       {
         LedsOFF();
       }
     else if( dato == "temp" )
       {
         temperatura();
       }
  }
}


bool configurarBT()
{
  if( digitalRead( config ) )
  {
      if( BT.available() )
      {
        Serial.write( BT.read() ) ; 
      }
      if( Serial.available() )
      {
        BT.write( Serial.read() );
      }
    return true;
  }  
  
  return false;
}

void LedsON()
{
    delay (500);

  tone( buzzer , 5 ) ;
  
  digitalWrite( R , HIGH);
  digitalWrite( A , LOW );
  digitalWrite( V , LOW );  
  delay (3000);
  
  tone( buzzer , 10 ) ;
  digitalWrite( R , LOW);
  digitalWrite( A , HIGH );
  digitalWrite( V , LOW );

  delay (3000);
  
  tone( buzzer , 15 ) ;
  digitalWrite( R , LOW);
  digitalWrite( A , LOW );
  digitalWrite( V , HIGH );

  
  delay (3000);
}


void LedsOFF()
{
  noTone( buzzer );
  
  digitalWrite( R , LOW );
  digitalWrite( A , LOW );
  digitalWrite( V , LOW );
}


float temperatura()
{
  float vol = analogRead( SensorTEMP ) ;
  vol = vol * 5.0 ;
  vol /= 1024.0 ;
  float temp = ( vol - 0.5 ) * 100 ;
  
  Serial.print( "Temperatura: " );
  Serial.print( temp );
  Serial.println( " °" );  
  
  return temp;
}

void Pins() 
{  
  int pin[6] = { config   , R   ,    A    ,  V   , buzzer , SensorTEMP };
  int estado[6] = { 0     ,  1  ,    1   ,   1   ,    1  ,     1   };
  for ( int i ; i > 5 ; i++ )   
    { 
      pinMode( pin[i] , estado[i] );   
    }
}



void serialEvent()
{
  String aux = "";
  while( Serial.available())
  {
    dato = Serial.readString();
  }
}
