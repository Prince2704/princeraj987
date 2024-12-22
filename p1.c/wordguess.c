#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_WORD_LENGTH 100
#define MAX_ATTEMPTS 10

void clearScreen() {
    printf("\033[H\033[J");
}

void displayWord(char *word, int *revealed) {
    for (int i = 0; word[i] != '\0'; i++) {
        if (revealed[i]) {
            printf("%c ", word[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");
}

int checkWin(int *revealed, int length) {
    for (int i = 0; i < length; i++) {
        if (!revealed[i]) {
            return 0;
        }
    }
    return 1;
}

void selectRandomWord(char *word) {
    const char *wordList[] = {
        "programming",
        "computer",
        "hangman",
        "science",
        "education",
        "developer",
        "keyboard",
        "monitor",
        "language",
        "algorithm"
    };
    int wordCount = sizeof(wordList) / sizeof(wordList[0]);
    srand(time(NULL));
    strcpy(word, wordList[rand() % wordCount]);
}

void playGame() {
    char word[MAX_WORD_LENGTH];
    selectRandomWord(word);

    int wordLength = strlen(word);
    int revealed[wordLength];
    memset(revealed, 0, sizeof(revealed));

    int attempts = MAX_ATTEMPTS;
    char guessedLetters[26] = {0};
    int guessedCount = 0;

    while (attempts > 0) {
        clearScreen();
        printf("Word Guess Game\n");
        printf("Attempts remaining: %d\n", attempts);
        printf("Guessed letters: ");
        for (int i = 0; i < guessedCount; i++) {
            printf("%c ", guessedLetters[i]);
        }
        printf("\n\n");

        displayWord(word, revealed);

        printf("\nEnter a letter: ");
        char guess;
        scanf(" %c", &guess);

        // Check if the letter was already guessed
        int alreadyGuessed = 0;
        for (int i = 0; i < guessedCount; i++) {
            if (guessedLetters[i] == guess) {
                alreadyGuessed = 1;
                break;
            }
        }

        if (alreadyGuessed) {
            printf("You already guessed '%c'. Try a different letter.\n", guess);
            continue;
        }

        guessedLetters[guessedCount++] = guess;

        // Check if the guessed letter is in the word
        int found = 0;
        for (int i = 0; word[i] != '\0'; i++) {
            if (word[i] == guess) {
                revealed[i] = 1;
                found = 1;
            }
        }

        if (!found) {
            attempts--;
            printf("Wrong guess! '%c' is not in the word.\n", guess);
        } else {
            printf("Good guess! '%c' is in the word.\n", guess);
        }

        if (checkWin(revealed, wordLength)) {
            printf("\nCongratulations! You've guessed the word: %s\n", word);
            return;
        }

        printf("Press Enter to continue...");
        while (getchar() != '\n'); // Wait for Enter key
    }

    printf("\nGame over! The word was: %s\n", word);
}

int main() {
    int choice;

    do {
        clearScreen();
        printf("Word Guess Game\n");
        printf("1. Play Game\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            playGame();
        } else if (choice == 2) {
            printf("Thank you for playing!\n");
        } else {
            printf("Invalid choice! Try again.\n");
        }

        printf("Press Enter to continue...");
        while (getchar() != '\n'); // Wait for Enter key
        while (getchar() != '\n');

    } while (choice != 2);

    return 0;
}
