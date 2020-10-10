#ifndef _ASSIGNMENT_2_
#define _ASSIGNMENT_2_

#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
using namespace std;
// This is the header class.
class Game { //Main class that all over classes inherit from
  public:
    Game(); //default
    Game(int x, int y); //overload
    ~Game();

    void simulateRound(string md);
    void readFile(string fn);
    int neighborCount(int x, int y);

  protected:
    int gameArray[128][128]; // Game array
    int shadowArray[128][128]; // Shadow array
    int xAxis;
    int yAxis;
  private:
    bool isAlive;
    int aliveCount;
};
class Classic : public Game {
  public:
    Classic();
    ~Classic();

    void runSimulation(); // Runs simulation
    void update(); // Updates game board
    void populateNewGrid(); // Populates a new grid full of nothing
    void printGrid(); // Prints grid
    void shadowGridTransfer(); // Transfers the shadow grid to the main grid.
    void determineState(int posX, int posY); // Determines the state of the cell
    void readFile(string fn); // Reads the file
    void populateGrid(); // Populates the grid.
    void writeFile(string fn, int currentRound);
    bool generationFreeze();
    int classicNeighborCount(int posX, int posY); // Counts the neighboring cells
  private:
    bool staticGrid; // If the game board is static
    string configuration; // Looks at the configuration of what type you want
    string filename; // File name
    string tempRows; // Rows

    int aliveCount; // Counts alive cells
    int rounds; // Counts the rounds

    double populationDensity;

    bool isAlive;
};
class Donut : public Game {
  public:
    Donut(); // Defualt constructor
    ~Donut(); // Destructor
    int donutNeighborCount(int posX, int posY); // Counts neighbors

    void runSimulation(); // Runs the simulation
    void update(); // Updates the simulation
    void populateNewGrid(int, int); // Populates the new grid full of 0s
    void printGrid(); // Prints new grid
    void shadowGridTransfer(); // Shadow transfers grid to update it to the game board.
    void determineState(int posX, int posY); // determines the state of the current cell
    void readFile(string fn); // Reads the file.
    void populateGrid(); // Populates grid randomly
    int checkCorner(int posX, int posY); // Checks the corner cells
    int checkBorder(int posX, int posY);
    void writeFile(string fn, int currentRound);
    bool generationFreeze();

  private:
    string configuration;
    string filename;
    string tempRows;
    int aliveCount;
    int rounds;
    double populationDensity;
    bool isAlive;
};
class Mirror : public Game {
  public:
    Mirror(); // Default constructor
    ~Mirror(); // Destructor
    int mirrorNeighborCount(int posX, int posY); // Mirror neighbor counts of cells
    void runSimulation(); // Runs the simulation
    void update(); // Updates the grid
    void populateNewGrid(); // Populates new grid
    void printGrid(); // Prints the grid.
    void shadowGridTransfer(); // Transfer the grid to the one before
    int innerCells(int posX, int posY); // Inner cells
    void determineState(int posX, int posY); // Determines the state of the inner cells
    void readFile(string fn); // Reads from the file
    void populateGrid(); // Populates new grid.
    int lookInwards(int posX, int posY); // Looks inwards.
    int cornerCount(int posX, int posY); // Counts the corner cells.
    bool checkCornerCell(int posX, int posY); // Check the corner cells.
    void writeFile(string fn, int currentRound);
    bool generationFreeze();
  private:
    int aliveCount;
    string configuration;
    string filename;
    string tempRows;
    int rounds;
    double populationDensity;
    bool isAlive;
};

#endif