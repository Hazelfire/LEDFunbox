// Adafruit_NeoMatrix example for single NeoPixel Shield.
// Scrolls 'Howdy' across the matrix in a portrait (vertical) orientation.

#include "Pong.h"

#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

#define PIN 6

// MATRIX DECLARATION:
// Parameter 1 = width of NeoPixel matrix
// Parameter 2 = height of matrix
// Parameter 3 = pin number (most are valid)
// Parameter 4 = matrix layout flags, add together as needed:
//   NEO_MATRIX_TOP, NEO_MATRIX_BOTTOM, NEO_MATRIX_LEFT, NEO_MATRIX_RIGHT:
//     Position of the FIRST LED in the matrix; pick two, e.g.
//     NEO_MATRIX_TOP + NEO_MATRIX_LEFT for the top-left corner.
//   NEO_MATRIX_ROWS, NEO_MATRIX_COLUMNS: LEDs are arranged in horizontal
//     rows or in vertical columns, respectively; pick one or the other.
//   NEO_MATRIX_PROGRESSIVE, NEO_MATRIX_ZIGZAG: all rows/columns proceed
//     in the same order, or alternate lines reverse direction; pick one.
//   See example below for these values in action.
// Parameter 5 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)


// Example for NeoPixel Shield.  In this application we'd like to use it
// as a 5x8 tall matrix, with the USB port positioned at the top of the
// Arduino.  When held that way, the first pixel is at the top right, and
// lines are arranged in columns, progressive order.  The shield uses
// 800 KHz (v2) pixels that expect GRB color data.
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(16, 16, PIN,
  NEO_MATRIX_BOTTOM     + NEO_MATRIX_LEFT +
  NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);


Game* activeGame;

// Player Controls
#define PLAYER1CLK 8
#define PLAYER1DT 9
#define PLAYER1BUT 4
#define PLAYER2CLK 10
#define PLAYER2DT 11
#define PLAYER2BUT 2


int player1Last;
int player2Last;

bool player1Press = false;
bool player2Press = false;



void setup() {

  pinMode(PLAYER1CLK, INPUT);
  pinMode(PLAYER1DT, INPUT);
  pinMode(PLAYER1BUT, INPUT);
  pinMode(PLAYER2CLK, INPUT);
  pinMode(PLAYER2DT, INPUT);
  pinMode(PLAYER2BUT, INPUT);

  
  player1Last = digitalRead(PLAYER1CLK);
  player2Last = digitalRead(PLAYER2CLK);
  
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(40);
  matrix.setTextColor(matrix.Color(0, 100, 0));
  matrix.setTextSize(1);

  /*for(int x = 0; x < 16; x++){
    for(int y = 0; y < 16; y++){
      if(y == 0 || y == 15)
        matrix.drawPixel(x, y, green);
    }
  }

  matrix.show();*/

  activeGame = new Pong();
  activeGame->begin(&matrix);

  Serial.begin(9600);
}


void updatePlayers(){
  int nPlayer1 = digitalRead(PLAYER1CLK);

  if (nPlayer1 != player1Last){
    if(digitalRead(PLAYER1DT) == nPlayer1){
      activeGame->player1Clock();
     }
     else{
      activeGame->player1Anticlock();
     }
  }

  player1Last = nPlayer1;
  
  int nPlayer2 = digitalRead(PLAYER2CLK);

  if (nPlayer2 != player2Last){
    if(digitalRead(PLAYER2DT) == nPlayer2){
      activeGame->player2Clock();
     }
     else{
      activeGame->player2Anticlock();
     }
  }

  
  player2Last = nPlayer2;
}

void loop() {
  
  if(!digitalRead(PLAYER1BUT)){
    if(!player1Press){
      player1Press = true;
      activeGame->player1Button();
    }
  }else{
    player1Press = false;
  }
    
   if(!digitalRead(PLAYER2BUT)){
    if(!player2Press){
      player2Press = true;
      activeGame->player2Button();
    }
  }else{
    player2Press = false;
  }


  updatePlayers();

  activeGame->update();
  delay(1);
  matrix.show();
}
