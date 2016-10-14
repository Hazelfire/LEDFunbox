#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

class Game{
public:
  
  virtual void begin(Adafruit_NeoMatrix *nMatrix) = 0;
  virtual void update() = 0;
  virtual void player1Button() = 0;
  virtual void player1Clock() = 0;
  virtual void player1Anticlock() = 0;
  virtual void player2Button() = 0;
  virtual void player2Clock() = 0;
  virtual void player2Anticlock() = 0;

protected:
  Adafruit_NeoMatrix *matrix;
};

