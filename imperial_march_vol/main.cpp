// miniblip play notes with interrupts with variable volume - Not tested with led matrix
// JCristobal version, based in https://github.com/hack-miniblip/hack-miniblip.github.io/blob/master/ejemplos/imperial_march/imperial_march.cpp (Alberto Piganti)
// For documentation see http://mbed.org/users/4180_1/notebook/using-a-speaker-for-audio-output/

#include "mbed.h"
#include "SongPlayer.h"

// Potentiometer to handle the volume
#define ANALOG_POTENTIOMETER P0_22
AnalogIn   ain(ANALOG_POTENTIOMETER);

#define MUTE  0.0
#define END   1.0

//-- Notes and frequencies (Hz)
#define DO_4  261.626
#define MI_4  329.628 
#define SOL_4 391.995 
#define SI_4  493.883
#define DO_5  523.251

//-- Tempo
#define TEMPO 200

//-- Default volume
float VOL = 0.5;

//-- Notes for the imperial march. MUTE means silence.  END for marking the end
float notes[] = {MI_4, MUTE, MI_4, MUTE, MI_4, MUTE, DO_4, SOL_4, MI_4, MUTE, DO_4,  SOL_4,  MI_4, MUTE, 
                 SI_4, MUTE, SI_4, MUTE, SI_4, MUTE, DO_5, SOL_4, MI_4, MUTE, DO_4,  SOL_4,  MI_4, END};
                 
//--  Notes duration                 
float tempo[] = {2   ,    1,    2,    1,    2,   1,    2,     1,    2,    1,    2,      1,     2,    3,  
                 2   ,    1,    2,    1,    2,   1,    2,     1,    2,    1,    2,      1,     2,    0};

//-- Declare speaker object
PwmOut speaker(P0_8);

void play()
{
  int i=0;
  //-- Reproduce all the notes in the list
  while(notes[i] != END) {
    
    //-- If silence, turn of the PWM
    if (notes[i] == MUTE) {
      speaker = 0.0;
    }
    else {
      speaker.period(1.0/notes[i]);               //-- Note
      float potenciometro = ain.read() * 0.7f;    // Handle the volume with the potentiometer 
      speaker = potenciometro;                    //-- Set the volume
    }  
    
    //-- Note duration
    wait_ms(TEMPO * tempo[i]);
    
    //-- Move to the next note
    i++;
  }  
  
  //-- Turn off the speacker
  speaker = MUTE;
}


int main()
{

    while(1){
         // Play the song!!
         play();
         wait_ms(500);        
    } ;
}

