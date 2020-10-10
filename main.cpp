#include "assignment-2.h"

int main(int argc, char** argv) {
  int rounds;
  bool gameModeValid = false;
  string mode;
  string configuration;
  string filename;
  string r;
  string f;
  Game *game = new Game();

  while (!gameModeValid) { // While the game mode is valid.
    cout << "Enter a game mode: (classic, donut, mirror)? ";
    cin >> mode; // Enters game mode.

    if (mode == "classic") { // If game mode is classic
      Classic *classic = new Classic();
      classic->runSimulation(); // Runs simulation.
      gameModeValid = true;
      delete classic; // Deletes from stack
    }
    if (mode == "donut") { // If game mode is donut
      Donut *donut = new Donut(); // Runs simulatiom
      donut->runSimulation();
      gameModeValid = true;
      delete donut; // Deletes from stack
    }
    if (mode == "mirror") {
      Mirror *mirror = new Mirror();
      mirror->runSimulation(); // Runs simulation
      gameModeValid = true;
      delete mirror; // deletes from stack
    }
  }

  delete game; // deletes game from stack.
  return 0;
}
