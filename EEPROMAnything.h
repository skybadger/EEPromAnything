#if !defined _EEPROMANYTHING_H_
#define _EEPROMANYTHING_H_
#include <EEPROM.h>
#include <Arduino.h>  // for type definitions

template <class T> int EEPROMWriteAnything(int ee, const T& value)
{
    const byte* p = (const byte*)(const void*)&value;
    unsigned int i;
    for (i = 0; i < sizeof(value); i++)
          EEPROM.put(ee++, *p++);
    return i;
}

template <class T> int EEPROMReadAnything(int ee, T& value)
{
    byte* p = (byte*)(void*)&value;
    unsigned int i;
    for (i = 0; i < sizeof(value); i++)
          *p++ = EEPROM.read(ee++);
    return i;
}

//The functions above can't handle pointers. SO had to roll our own for Strings
int EEPROMReadString( int ee, char* inString, int length )
{
   char indata = 'a';
   int i = 0;
   
   do
   {
      indata = EEPROM.read( ee + i );
      inString[i] = indata;
      i++;
   }while ( i < (length) && indata != '\0');
   return i;
}

/*
length is the length of the string as provided by strlen - which ignores the trailing terminator
So we explicitly add it after the length here. Otherwise we can;t work kout the length of the string when we read it back.
*/
int EEPROMWriteString( int ee, char* outString, int length )
{
   int i;
   
   for ( i = 0; i < length; i++ )
   {
      EEPROM.put( ee, outString[i] );
      ee++;
   }
   return i;   
}

#endif 