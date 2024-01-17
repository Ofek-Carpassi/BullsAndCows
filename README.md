# Bulls and Cows Game

This repository contains a simple console-based implementation of the "Bulls and Cows" game in C. The game is played between the user and the computer, where the computer generates a secret password, and the user tries to guess it. The rules involve receiving hints (HITS and MISSES) after each guess.

## Instructions

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/your-username/bulls-and-cows.git
2. **Compile and Run:**
   ```bash
   gcc bullsAndCows.c -o bullsAndCows
   ./bullsAndCows
4. **Follow the Game Instructions:**
   - The computer will choose a secret password of 4 distinct digits.
   - Your goal is to guess the password within a limited number of guesses.
   - After each guess, you'll receive hints (HITS and MESSES) about the password.

## Code Overview
The main code (`bullsAndCows.c`) includes the following functions:

- `printWelcomeAndRules`: Print the welcome message and game rules.
- `getDifficultyLevel`: Gets the difficulty level from the user.
- `getRandomNumber`: Generates a random number.
- `playDifficulty`: Plays the game according to the selected difficulty level.
- `playGame`: Plays the game with the given number of attempts.
- `getGuess`: Gets a guess from the user.
- `checkGuess`: Checks the user's guess against the random number.

## Difficulty Levels
- Easy (1): 20 rounds
- Medium (2): 15 rounds
- Hard (3): 10 rounds
- Crazy (4): Random number of guesses (between 5 and 25)

## Exiting the Game
- After each round, you'll be asked if you want to play again (`y/n`).
- Enter `n` to exit the game with a farewell message.
