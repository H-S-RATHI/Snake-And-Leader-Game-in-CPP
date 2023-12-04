#include <cstdlib>
#include <ctime>
#include <iostream>

#ifdef _WIN32
#include <conio.h>
#define CLEAR_SCREEN "cls"
#else
#include <stdio_ext.h> // For __fpurge on some non-Windows systems
#define CLEAR_SCREEN "clear"
#endif

using namespace std;

int random(int min, int max) {
  static bool isFirst = true;
  if (isFirst) {
    srand(static_cast<unsigned int>(time(0)));
    isFirst = false;
  }
  return min + rand() % (max - min + 1);
}

int dice() { return random(1, 6); }

int main() {
  int ladder[] = {5, 20, 35, 50, 65, 80, 90};
  int snake[] = {15, 25, 37, 52, 68, 85, 98};
  const int board = 100;
  const int maxPlayer = 2;
  bool gameOver = false;
  int current[maxPlayer] = {0};
  int player = 0;

  cout << "\n\n\t\t\t\tWelcome to the Snake and Ladder Game!" << endl;
  cout << "\t\t\t\tPress Enter to start the game...";
  cin.get(); // Wait for a key press

  while (!gameOver) {
    system(CLEAR_SCREEN);
    cout << "\n\n\t\t\t\tSnake and Ladder Game!!" << endl;
    cout << "\t\t\t\tCurrent Player " << player + 1 << endl;
    cout << "\t\t\t\t=====================" << endl;

    for (int i = 0; i < maxPlayer; i++) {
      cout << "\t\t\t\tPlayer " << i + 1 << " is at Position " << current[i]
           << endl;
    }

    cout << "\t\t\t\t=========================" << endl;

    int roll = dice();
    cout << "\t\t\t\tPlayer " << player + 1 << " rolled a " << roll << endl;

    current[player] += roll;

    if (current[player] >= board) {
      cout << "\t\t\t\tPlayer " << player + 1 << " wins!" << endl << endl;
      gameOver = true;
      break;
    }

    for (size_t i = 0; i < sizeof(ladder) / sizeof(ladder[0]); i++) {
      if (current[player] == ladder[i]) {
        cout << "\t\t\t\tPlayer " << player + 1
             << " climbed a ladder to position " << ladder[i] + dice() << endl;
        current[player] = ladder[i] + dice();
      }
    }

    for (size_t i = 0; i < sizeof(snake) / sizeof(snake[0]); i++) {
      if (current[player] == snake[i]) {
        cout << "\t\t\t\tPlayer " << player + 1
             << " is bitten by a snake to position " << snake[i] - dice()
             << endl;
        current[player] = snake[i] - dice();
      }
    }

    // Make sure the player's position is not less than 1
    if (current[player] < 1) {
      current[player] = 1;
    }

    player = (player + 1) % maxPlayer;

    cout << "\n\n\t\t\t\tPlayer " << player + 1
         << " Press Enter to continue...";
    cin.get(); // Wait for a key press
  }

  return 0;
}
