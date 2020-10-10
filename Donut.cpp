#include "assignment-2.h"

Donut::Donut() {}
Donut::~Donut() {}

void Donut::runSimulation() {
  bool validInput = false; // Initializes variables
  string outputMethod;
  while (!validInput) {
    cout << "Do you want to insert a file or randomly populate the grid? ('file' 'populate')?" << endl; // Asks user for their input
    cin >> configuration; // Finds the wanted configuration
    if (configuration == "populate") {
      populateNewGrid(); // Populates the grid,
      validInput = true;
    }
    else if (configuration == "file") {
      cout << "Enter a file: ";
      cin >> filename;
      readFile(filename); // Reads the file.
      validInput = true;
    }
  }
  cout << "How many rounds do you want to simulate?: ";
  cin >> rounds; // Initializes rounds
  cout << "What output do you want? 'break' 'enter' 'file': ";
  cin >> outputMethod;
  cout << "generation number 0" << endl;
  if (outputMethod == "break") {
    printGrid(); // Prints the grid.
    usleep(3000000); // Sleeps for a 3-5 second interval.
    for (int currentRound = 0; currentRound < rounds; ++currentRound) {
         usleep(3000000);
         cout << "generation number " << currentRound + 1 << endl;
         printGrid(); // Prints the grid again
         update(); //Updates the grid.
        if(generationFreeze() == true) {
          cout << "Press enter to exit: " << endl;
          cin.ignore();
          cin.get();
          exit(0);
      }
    }
  }
  if (outputMethod == "enter") {
    string temp;
    printGrid(); // Prints the grid.
    cout << "Press enter to continue: " << endl;
    cin.ignore();
    for (int currentRound = 0; currentRound < rounds; ++currentRound) {
         cout << "generation number " << currentRound + 1 << endl;
         printGrid(); // Prints the grid again
         cout << "Press enter to continue: " << endl;
         cin.ignore();
         update(); //Updates the grid.
        if(generationFreeze() == true) {
          cout << "Press enter to exit: " << endl;
          cin.ignore();
          cin.get();
          exit(0);
      }
    }
  }
  if (outputMethod == "file") {
    string temp;
    cout << "Enter file name: " << endl;
    cin >> temp;
    writeFile(temp, 0); // Prints the grid.
    for (int currentRound = 0; currentRound < rounds; ++currentRound) {
         writeFile(temp, currentRound);
         update(); //Updates the grid.
        if(generationFreeze() == true) {
          cout << "Press enter to exit: " << endl;
          cin.ignore();
          cin.get();
          exit(0);
      }
    }
  }
}

int Donut::donutNeighborCount(int posX, int posY) { 
  int aliveCount = 0;
  
  // First check all "normal neighbors", later check for wrap around cells.
  // Calculate high / low values to account for corner or edge cases
  int rowMin = posX - 1;
  int rowMax = posX + 1;
  int colMin = posY - 1;
  int colMax = posY + 1;

  // Iterate over
  for(int row = rowMin; row <= rowMax; row++) {
    // Calculate effective row by adding the size of the xAxis to it and moduloing it by the xAxis
    int effectiveRow = (row + xAxis) % xAxis;
    for(int col = colMin; col <= colMax; col++) {
      // Calculate effective col by adding the size of the yAxis to it and moduloing it by the yAxis
      int effectiveCol = (col + yAxis) % yAxis;
      // Make sure it doesn't count itself
      if(effectiveRow == posX && effectiveCol == posY) {
        continue;
      }
      // Add each cell that is occupied
      aliveCount += gameArray[effectiveRow][effectiveCol];
    }
  }
  
  return aliveCount;
}

void Donut::populateNewGrid() {
  populationDensity = -1;
  cout << "Enter Grid Size X Axis: "; // Gets the x Axis from the user
  cin >> xAxis;

  cout << "Enter Grid Size Y Axis: "; // Gets the y Axis from the user.
  cin >> yAxis;

  bool validInput = false;
  while (validInput == false) {
    cout << "Enter a population density between 0-1: ";
    cin >> populationDensity; // User enters a population density.

    if (populationDensity > 0 && populationDensity < 1)
      validInput = true;
  }
  //Makes a new population grid.
  for (int x = 0; x < xAxis; ++x) {
      for (int y = 0; y < yAxis; ++y) {
        gameArray[x][y] = 0;
      }
  }

  srand(time(NULL)); //Makes random based on time.
  int area = xAxis * yAxis; // Finds the area of the grid.
  int totalPopulation = area * populationDensity; // Calculates how many times the for loop needs to iterate.

  for (int i = 0; i <= totalPopulation; ++i) {
    int xRand = rand() % xAxis; // Randomizes xAxis
    int yRand = rand() % yAxis; // Randomizes yAxis
    gameArray[xRand][yRand] = 1; // Makes it equal to 1.
  }
}
void Donut::printGrid() {
  //Prints the grid, iterating through each spot.
  for (int x = 0; x < xAxis; ++x) {
      for (int y = 0; y < yAxis; ++y) {
        if (gameArray[x][y] == 0) {
          cout << "-";
        }
        else {
          cout << "X";
        }
        //cout << " ";
      }
      cout << endl;
  }
}
void Donut::shadowGridTransfer() {
  // Transfers the grid.
  for (int x = 0; x < xAxis; ++x) {
      for (int y = 0; y <= yAxis; ++y) {
        gameArray[x][y] = shadowArray[x][y];
      }
    }
}
void Donut::update() {
  //Updates the grid.
  for (int i = 0; i < xAxis; ++i) {
    for (int j = 0; j < yAxis; ++j) {
      aliveCount = 0;
      aliveCount = donutNeighborCount(i, j); // Find the alive cell count.
      determineState(i, j); // Determines the state.
    }
  }
  shadowGridTransfer(); // Transfers new grid to old grid.
}
void Donut::determineState(int posX, int posY) {
  //Uses count to determine if cell lives or dies.
  isAlive = false;
  if (aliveCount == 1) { // Dies from loneliness
    isAlive = false;
  }
  else if (aliveCount == 2) { //Keeps current state
    if (gameArray[posX][posY] == 1) {
      isAlive = true;
    }
    else {
      isAlive = false;
    }
  }
  else if (aliveCount == 3) { // New cell is born
    isAlive = true;
  }
  else if (aliveCount >= 4) { // Over crowding.
    isAlive = false;
  }
  if(isAlive == true) {
    shadowArray[posX][posY] = 1;
  }
  else {
    shadowArray[posX][posY] = 0;
  }
}

void Donut::readFile(string fn) {
  string filename = fn;
  fstream newfile;

  newfile.open(filename, ios::in); // Opens file
  if (newfile.is_open()){
    cout << filename << endl;
     string currentRow;
     int currentLineLength;
     int lineCount = 0;
     int currentPos = 0;
     while(getline(newfile, currentRow)) { // For each row in the file
       lineCount++;
       if (lineCount==1) { // Sets rows
         xAxis = stoi(currentRow);
       }
       else if (lineCount==2) { // Sets cols
         yAxis = stoi(currentRow);
         populateGrid();
       }
       else {
         currentPos = 0;
         while (currentPos <= currentRow.length() - 1) { //Interates though all rows gerater than 2
           if (currentRow.at(currentPos) == 'X') // If its an X
             gameArray[lineCount-3][currentPos] = 1; // Insert as a 1
           currentPos++; // Updates current position
         }
       }
      }
   }
   newfile.close(); // Closes the file.
}
void Donut::populateGrid() { // Populates the grid with 0s.
  //Initialize each cell to 0
  for (int x = 0; x < xAxis; ++x) {
    for (int y = 0; y < yAxis; ++y) {
      gameArray[x][y] = 0;
    }
  }
}
void Donut::writeFile(string fn, int currentRound) {
  fstream newfile;
  newfile.open(fn,ios::app);

  if(newfile.is_open()) {
    newfile << "generation number " << currentRound + 1 << endl;
    for (int x = 0; x < xAxis; ++x) {
        for (int y = 0; y < yAxis; ++y) {
          if (gameArray[x][y] == 0) {
            newfile << "-";
          }
          else {
            newfile << "X";
          }
        }
        newfile << endl;
    }
  }
  else {
    cout << "Couldn't open the file.... :(" << endl;
  }
}
bool Donut::generationFreeze() {
  bool isNotEmpty = true;
  // Check if both arrays are the same. Returns false if they are not.
  // Iterates through both the updated array (shadow array) & the current game array
  for (int x = 0; x < xAxis; ++x) {
    for (int y = 0; y < yAxis; ++y) {
      // Check if values of the indencies match to determine sameness.
      if (gameArray[x][y] != shadowArray[x][y]) {
        return false;
      }
      // Check if any single cell is not empty
      if (gameArray[x][y] != 0) {
        isNotEmpty = false;
      }
    }
  }

  return isNotEmpty;
}