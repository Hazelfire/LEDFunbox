#include "GameInterface.h"

class Pong : public Game{
public:
  void begin(Adafruit_NeoMatrix *nMatrix) override;
  void update() override;
  void player1Button() override;
  void player1Clock() override;
  void player1Anticlock() override;
  void player2Button() override;
  void player2Clock() override;
  void player2Anticlock() override;  
private:  

  // Colors
  uint16_t green;

  void loss();
  void drawPlayers();
  void updatePlayers();
  void clearCourt();
  void ballTick();
  
  // Game variables
  int player1Size = 3;
  int player2Size = 3;

  bool showRally = true;

  bool buttonRallyInc = false;

  int ballx = 8;
  int bally = 8;
  int balldy = 1;
  int balldx = 1;

  int player1Pos = 6;
  int player2Pos = 6;

  int loopCount = 0;

  int rallyCount = 0;
};

