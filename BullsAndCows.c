#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h> // Include for getch() on Windows

// Enumeration for difficulty levels
enum boolean {TRUE = 0, FALSE};
enum DifficultyLevel {EASY = 1, MEDIUM, HARD, CRAZY};

// Constants for difficulty levels
#define EASY_ROUNDS 20
#define MEDIUM_ROUNDS 15
#define HARD_ROUNDS 10
#define CRAZY_MIN_ROUNDS 5
#define CRAZY_MAX_ROUNDS 25
#define DIGITS_IN_NUMBER 4
#define MIN_DIGIT 1
#define MAX_DIGIT 6
#define REMOVE_AND_GET_LAST_DIGIT 10
#define LOOP_RESET -1
#define MAX_RANDOM_CRAZY 21
#define MIN_RANDOM_CRAZY 5
#define MIN_DIGIT_CHAR '1'
#define MAX_DIGIT_CHAR '6'
#define BASE_DIGIT_CHAR '0'

// This function prints the welcome message and the rules of the game.
void printWelcomeAndRules();

// This function gets the difficulty level from the user and returns it.
void getDifficultyLevel();

// This function generates a random number based on the difficulty level and returns it.
void getRandomNumber();

// This function plays the game based on the difficulty level.
void playDifficulty();

// This function plays the game. It takes the number of guesses allowed as a parameter.
void playGame(int amountOfGuesses);

// This function gets a guess from the user and returns it.
int getGuess(int amountOfGuesses);

// This function checks the user's guess.
void checkGuess(int guess);

// Global variables
int difficultyLevel = 0;
int randomNumber = 0;
int hits = 0;
int misses = 0;

int main()
{
    // Seed the random number generator
    srand(time(NULL));

    // playAgain - A flag to indicate if the user wants to play again
    char playAgain = ' ';

    // Print welcome message and rules
    printWelcomeAndRules();

    // Play the game as long as the user wants to play again
    do
    {
        // Get the difficulty level from the user
        getDifficultyLevel();
        // Generate a random number
        getRandomNumber();
        // Play the game according to the difficulty level
        playDifficulty();

        // Ask the user if they want to play again
        do {
            // Get the user's response
            printf("Do you want to play again? (y/n): ");
            playAgain = getch();
            printf("\n");
        } while (playAgain != 'y' && playAgain != 'n');

        // If the user doesn't want to play again, break out of the loop
        if (playAgain == 'n') {
            printf("Goodbye!\n");
            break;
        }

    } while (TRUE);

    return 0;
}

// printWelcomeAndRules - Print welcome message and rules
void printWelcomeAndRules()
{
    printf("The game is called \"Bulls and Cows\".\n");
    printf("The game is played between you and the computer.\n");
    printf("The computer will choose a secret password of 4 distinct digits.\n");
    printf("Your goal is to guess the password.\n");
    printf("The rules are as follows:\n");
    printf("1. In each round you try to guess the secret password (4 distinct digits)\n");
    printf("2. After every guess you'll receive two hints about the password\n");
    printf("   HITS:   The number of digits in your guess which were exactly right.\n");
    printf("   MISSES: The number of digits in your guess which belongs to\n");
    printf("           the password but were miss-placed.\n");
    printf("3. If you'll fail to guess the password after a certain number of rounds\n");
    printf("   You will lose!\n\n");
}

// getDifficultyLevel - Get the difficulty level from the user
void getDifficultyLevel()
{
    // Print the options for the user
    printf("Please choose the game level:\n");
    printf("1 - Easy (20 rounds)\n");
    printf("2 - Moderate (15 rounds)\n");
    printf("3 - Hard (10 rounds)\n");
    printf("4 - Crazy (random number of rounds 5-25)\n");

    // Get the difficulty level from the user as long as he doesn't enter a valid difficulty level
    do {
        // Get the difficulty level from the user and save it in the global variable
        printf("Make a choice: ");
        scanf("%d", &difficultyLevel);
    } while(difficultyLevel < EASY || difficultyLevel > CRAZY); // Check if the user entered a valid difficulty level
}

// getRandomNumber - Generate a random number
void getRandomNumber()
{
    /*
    Defining local variables
    i - A counter for the loop
    j - A counter for the loop
    randomDigit - A random digit to build the random number
    */
    int i = 0, j = 0;
    int randomDigit = 0;

    // Reset the random number
    randomNumber = 0;

    // Generate a random number without duplicate digits
    while(i < DIGITS_IN_NUMBER)
    {
        // Generate a random number between 1 and 6 (inclusive)
        randomDigit = rand() % MAX_DIGIT + MIN_DIGIT;

        // Save the random number in a temporary variable - to check if the digit is already in the random number
        int tempRandomNumber = randomNumber;

        // Check if the digit is already in the random number
        for(j = 0; j < i; j++)
        {
            // If the digit is already in the random number
            if(randomDigit == tempRandomNumber % REMOVE_AND_GET_LAST_DIGIT)
            {
                // Generate a new digit
                randomDigit = rand() % MAX_DIGIT + MIN_DIGIT;

                // Reset the loop
                j = LOOP_RESET;

                // Reset the tempRandomNumber
                tempRandomNumber = randomNumber;

                // break the loop
                continue;
            }
            // Remove the last digit from the tempRandomNumber
            tempRandomNumber /= REMOVE_AND_GET_LAST_DIGIT;
        }

        // Add the digit to the random number
        randomNumber = randomNumber * REMOVE_AND_GET_LAST_DIGIT + randomDigit;
        i++;
    }
}

// playDifficulty - Play the game according to the difficulty level
void playDifficulty()
{
    // Play the game according to the difficulty level chosen by the user
    switch(difficultyLevel)
    {
        // Play the game according to the difficulty level
        case EASY:
            playGame(EASY_ROUNDS);
            break;
        case MEDIUM:
            playGame(MEDIUM_ROUNDS);
            break;
        case HARD:
            playGame(HARD_ROUNDS);
            break;
        case CRAZY:
            // send a random number between 5 - 25
            playGame(rand() % MAX_RANDOM_CRAZY + MIN_RANDOM_CRAZY);
            break;
    }
}

// playGame - Play the game with the given number of attempts
void playGame(int amountOfGuesses)
{
    // guess - The amount of guesses the user used
    int guess = 0;
    
    // Play the game as long as the user didn't guess the number and he still has attempts left
    while(guess != randomNumber && amountOfGuesses > 0)
    {
        // Get a guess from the user - using the getGuess function
        guess = getGuess(amountOfGuesses);

        // Check if the user entered an invalid guess
        while (guess == 0)
        {
            // Print an error message and get a new guess from the user
            printf("Only 1-6 are allowed, try again!\n");
            guess = getGuess(amountOfGuesses);
        }

        // Decrease the amount of guesses left
        amountOfGuesses--;

        // Check if the user guessed the number - using the checkGuess function
        checkGuess(guess);

        // Print the number of hits and misses
        printf("You got %d HITS %d MISSES.\n", hits, misses);
    }

    // Check if the user won or lost
    if(guess == randomNumber)
    {
        // Print a winning message
        printf("\t4 HITS YOU WON!!!\n\n");
        printf("It took you only %d guesses!\n", hits + misses);
        return;
    }
    else
    {
        // Print a losing message
        printf("The secret password was %d\n", randomNumber);
        printf("You lost, try again!\n\n");
        return;
    }
}

// getGuess - Get a guess from the user
int getGuess(int amountOfGuesses)
{
    // Print a message to the user
    printf("Write your guess (only 1-6, no ENTER is needed)\n");

    if(difficultyLevel != CRAZY)
    {
        printf("%d guesses left\n", amountOfGuesses);
    }

    int i = 0, guess = 0;

    // Get the four digits number from the user without the user hitting enter
    while (i < DIGITS_IN_NUMBER)
    {
        // Get a digit from the user using getch()
        int digit = getch();

        // If the user entered a digit between '1' and '6'
        if (digit >= MIN_DIGIT_CHAR && digit <= MAX_DIGIT_CHAR)
        {
            // Print the digit to the screen
            printf("%c", digit);

            // Add the digit to the guess
            guess = guess * REMOVE_AND_GET_LAST_DIGIT + (digit - BASE_DIGIT_CHAR);
            i++;
        }
    }

    printf("\n");  // Print a newline to separate input from the next output
    return guess;
}

// checkGuess - Check the user's guess against the random number
void checkGuess(int guess)
{
    /*
    Defining local variables
    i - A counter for the loop
    digit - A digit from the guess
    tempGuess - A temporary variable to save the guess
    tempRandomNumber - A temporary variable to save the random number
    */
    int i = 0, digit = 0, tempGuess = guess, tempRandomNumber = randomNumber;

    // Reset the hits and misses
    hits = 0;
    misses = 0;

    // Check the guess against the random number
    for(i = 0; i < DIGITS_IN_NUMBER; i++)
    {
        // Get the last digit from the guess
        digit = tempGuess % REMOVE_AND_GET_LAST_DIGIT;

        // Remove the last digit from the guess
        tempGuess /= REMOVE_AND_GET_LAST_DIGIT;

        // Check if the digit is in the random number and in the same place
        if(digit == tempRandomNumber % REMOVE_AND_GET_LAST_DIGIT)
        {
            // Increase the hits
            hits++;
        }
        // If the digit is not in the same place - check if the digit is in the random number
        else
        {
            /*
            Defining local variables
            j - A counter for the loop
            secondTempRandomNumber - A temporary variable to save the random number
            */
            int j = 0, secondTempRandomNumber = randomNumber;

            // Check if the digit is in the random number
            for(j = 0; j < DIGITS_IN_NUMBER; j++)
            {
                // If the digit is in the random number
                if(digit == secondTempRandomNumber % REMOVE_AND_GET_LAST_DIGIT)
                {
                    // Increase the misses
                    misses++;
                }

                // Remove the last digit from the random number
                secondTempRandomNumber /= REMOVE_AND_GET_LAST_DIGIT;
            }
        }

        // Remove the last digit from the random number
        tempRandomNumber /= REMOVE_AND_GET_LAST_DIGIT;
    }
}