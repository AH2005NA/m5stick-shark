/*
  Adapted by Milton Matuda to work with M5-NEMO.
  You cand find a list of #define for other octaves at Robson's Github.
  IG: @35mmatuda | https://github.com/Mmatuda
*/
/* 
  Super Mario Bros - Overworld theme 
  More songs available at https://github.com/robsoncouto/arduino-songs                                            
                                              
                                              Robson Couto, 2019
*/

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0

// change this to make the song slower or faster
int tempo = 200;

// notes of the melody followed by the duration.
// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
// !!negative numbers are used to represent dotted notes,
// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
int melody0[] = {
  NOTE_E6,8, NOTE_E6,8, REST,8, NOTE_E6,8, REST,8, NOTE_C6,8, NOTE_E6,8, //WRITE YOUR MELODY HERE
  NOTE_G6,4, REST,2, NOTE_G5,2,
};
int melody1[] = {
  NOTE_E5, 4,  NOTE_B4,8,  NOTE_C5,8,  NOTE_D5,4,  NOTE_C5,8,  NOTE_B4,8,
  NOTE_A4, 4,  NOTE_A4,8,  NOTE_C5,8,  NOTE_E5,4,  NOTE_D5,8,  NOTE_C5,8,
  NOTE_B4, -4,  NOTE_C5,8,  NOTE_D5,4,  NOTE_E5,4,
  NOTE_C5, 4,  NOTE_A4,4,  NOTE_A4,8,  NOTE_A4,4,
};
int melody2[] = {
  NOTE_AS4,8, NOTE_AS4,8,
  NOTE_AS4,8, NOTE_F5,2, NOTE_C6,2,
  NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F6,2, NOTE_C6,4,
  NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F6,2, NOTE_C6,4,
  NOTE_AS5,8, NOTE_A5,8, NOTE_AS5,8, NOTE_G5,2,
};
int melody3[] = {
  NOTE_E5,-8, NOTE_D5,8, NOTE_B4,-8, NOTE_A4,8, NOTE_G4,-8, NOTE_E4,-8,
  NOTE_AS4,16, NOTE_A4,-8, NOTE_AS4,16, NOTE_A4,-8, NOTE_AS4,16, NOTE_A4,-8, NOTE_AS4,16, NOTE_A4,-8,   
  NOTE_G4,-16, NOTE_E4,-16, NOTE_D4,-16, NOTE_E4,16, NOTE_E4,16, NOTE_E4,2,
};
int melody4[] = {
  //TEMPO=100!
  NOTE_B4, 16, NOTE_B5, 16, NOTE_FS5, 16, NOTE_DS5, 16, NOTE_B5, 32, NOTE_FS5, -16, NOTE_DS5, 8,
  NOTE_C5, 16, NOTE_C6, 16, NOTE_G6, 16, NOTE_E6, 16, NOTE_C6, 32, NOTE_G6, -16, NOTE_E6, 8,
};
int melody5[] = {
  NOTE_E5, 8, NOTE_D5, 8, NOTE_FS4, 4, NOTE_GS4, 4, 
  NOTE_CS5, 8, NOTE_B4, 8, NOTE_D4, 4, NOTE_E4, 4, 
  NOTE_B4, 8, NOTE_A4, 8, NOTE_CS4, 4, NOTE_E4, 4,
  NOTE_A4, 2, 
};
int melody6[] = {
  REST, 2, NOTE_D4, 4,
  NOTE_G4, -4, NOTE_AS4, 8, NOTE_A4, 4,
  NOTE_G4, 2, NOTE_D5, 4,
  NOTE_C5, -2, 
  NOTE_A4, -2,
  NOTE_G4, -4, NOTE_AS4, 8, NOTE_A4, 4,
  NOTE_F4, 2, NOTE_GS4, 4,
  NOTE_D4, -1, 
};

int melody[40] = {
  REST,0xff, REST,0xff, REST,0xff, REST,0xff, REST,0xff,
  REST,0xff, REST,0xff, REST,0xff, REST,0xff, REST,0xff,
  REST,0xff, REST,0xff, REST,0xff, REST,0xff, REST,0xff,
  REST,0xff, REST,0xff, REST,0xff, REST,0xff, REST,0xff,
};


void setupSongs(uint8_t randomsong) {
  //Start
  /*
uint8_t randomsong = EEPROM.read(6);
if(randomsong>=6)
{
EEPROM.write(6, 0);
}
else
{
EEPROM.write(6, (randomsong+1));
}*/
  if(randomsong==0){
    for(uint8_t i=0; i<20; i++)
    {
      melody[i] = melody0[i];
    }
  }
  if(randomsong==1){
    for(uint8_t i=0; i<40; i++)
    {
      melody[i] = melody1[i];
    }
  }
  if(randomsong==2){
    for(uint8_t i=0; i<38; i++)
    {
      melody[i] = melody2[i];
    }
  }
  if(randomsong==3){
    for(uint8_t i=0; i<40; i++)
    {
      melody[i] = melody3[i];
    }
  }
  if(randomsong==4){
    tempo = 100;
    for(uint8_t i=0; i<28; i++)
    {
      melody[i] = melody4[i];
    }
  }
  if(randomsong==5){
    for(uint8_t i=0; i<26; i++)
    {
      melody[i] = melody5[i];
    }
  }
  if(randomsong==6){
    for(uint8_t i=0; i<30; i++)
    {
      melody[i] = melody6[i];
    }
  }
// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
// there are two values per note (pitch and duration), so for each note there are four bytes
int notes = sizeof(melody) / sizeof(melody[0]) / 2;

// this calculates the duration of a whole note in ms
int wholenote = (60000 * 4) / tempo;

int divider = 0, noteDuration = 0;

  // iterate over the notes of the melody.
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
    if(thisNote+1==0xff)
    {
      break;
    }
    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }
#if defined(STICK_C_PLUS)
    // playing 2 octave up (2^2) due to proximity of frequencies and high noise on low freqs
    SPEAKER.tone(melody[thisNote]*4, noteDuration*0.9);
    SPEAKER.tone(0, noteDuration*0.1);
    // Wait for the specief duration before playing the next note.
    delay(noteDuration);
    SPEAKER.mute();
#elif defined(CARDPUTER)
    // we only play the note for 90% of the duration, leaving 10% as a pause
    SPEAKER.tone(melody[thisNote], noteDuration * 0.9);
    // Wait for the specief duration before playing the next note.
    delay(noteDuration);
#elif defined(STICK_C_PLUS2)
    // playing 2 octave up (2^2) due to proximity of frequencies and high noise on low freqs
    SPEAKER.tone(melody[thisNote]*4, noteDuration*0.9);
    SPEAKER.tone(0, noteDuration*0.1);
    // Wait for the specief duration before playing the next note.
    delay(noteDuration);
    SPEAKER.stop();
#endif
    
  }
}
