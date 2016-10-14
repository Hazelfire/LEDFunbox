#include "Pong.h"

void Pong::begin(Adafruit_NeoMatrix *nMatrix){
  matrix = nMatrix;

  green = matrix->Color(0, 255, 0);
}

void Pong::loss(){
  ballx = 8;
  bally = 8;

  rallyCount = 0;
}


void Pong::drawPlayers(){

  for(int p = player1Pos - (player1Size - 1); p < player1Pos + player1Size; p++)
    matrix->drawPixel(0, p, green);

  for(int p = player2Pos - (player2Size - 1); p < player2Pos + player2Size; p++)
    matrix->drawPixel(15, p, green);
}


void Pong::updatePlayers(){
  
  for(int y = 0; y < 16; y++){
    if(ballx != 0 || bally != y)
      matrix->drawPixel(0, y, 0);

    if(ballx != 15 || bally != y)
      matrix->drawPixel(15, y, 0);
  }  
  
  drawPlayers();
}

void Pong::clearCourt(){
  for(int x = 1; x < 15; x++){
    for(int y = 0; y < 16; y++){
      matrix->drawPixel(x, y, 0);
    }
  }
}

void Pong::ballTick(){

  clearCourt();
      
  if(bally + balldy == 16 || bally + balldy == -1)
    balldy = -balldy;
    
  if(ballx + balldx == 0){
    for(int p = player1Pos - (player1Size - 1); p < player1Pos + player1Size; p++){
      if(bally  ==  p){
        balldx = -balldx;
        rallyCount++;
        break;
      }
    }
  }

  if(ballx + balldx == 15){
    for(int p = player2Pos - (player2Size - 1); p < player2Pos + player2Size; p++){
      if(bally  == p){
        balldx = -balldx;
        rallyCount++;
        break;
      }
    }
  }

  // rally Count Display
  if(showRally){
    if(rallyCount < 10)
      matrix->setCursor(6, 8);
    else
      matrix->setCursor(2, 8);
    char str[3];
    snprintf(str, 3, "%d", rallyCount);
    matrix->print(str);
  }
  
  ballx += balldx;
  bally += balldy;
  
  if(ballx < 0 || ballx > 15)
    loss();
  else
    matrix->drawPixel(ballx, bally, matrix->Color(min(255, (rallyCount / 20.0 ) * 255), 0 , max(0, ((20 - rallyCount) / 20.0 ) * 255)));
}


// Controls
void Pong::player1Button(){
  if(buttonRallyInc){
    rallyCount++;
  }
}

void Pong::player2Button(){
  if(buttonRallyInc){
    rallyCount++;
  }
}

void Pong::player1Clock(){
  if (player1Pos != 16 - player1Size){
    player1Pos++;
  }
}

void Pong::player1Anticlock(){
  if (player1Pos != player1Size - 1){
    player1Pos--;
  }
}

void Pong::player2Clock(){
  if (player2Pos != player2Size - 1){
    player2Pos--;
  }
}

void Pong::player2Anticlock(){
  if (player2Pos != 16 - player2Size){
    player2Pos++;
  }
}

void Pong::update(){
  updatePlayers();
  
  if(loopCount >  1.0 / (0.05 + min(25, rallyCount * 0.01))){
    ballTick();
    loopCount = 0;
  }
  
  loopCount++;
}

