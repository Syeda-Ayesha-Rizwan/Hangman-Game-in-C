#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
    #define CLEAR_COMMAND "cls"
#else
    #define CLEAR_COMMAND "clear"
#endif

#define MAX_TRIES_EASY 10
#define MAX_TRIES_MODERATE 8
#define MAX_TRIES_HARD 6
#define WORD_LIST_SIZE 5
#define LEADERBOARD_SIZE 5

// Structure for storing player details
typedef struct {
    char name[50];
    int score;
    int level;
} Player;

// Word bank
const char *easyWords[WORD_LIST_SIZE] = {"apple", "ball", "cat", "dog", "fish"};
const char *easyHints[WORD_LIST_SIZE] = {"A fruit", "It bounces", "A pet", "Barks", "Lives in water"};

const char *moderateWords[WORD_LIST_SIZE] = {"planet", "butter", "school", "garden", "rocket"};
const char *moderateHints[WORD_LIST_SIZE] = {"Orbits the sun", "Used on toast", "Place to study", "Has flowers", "Goes to space"};

const char *hardWords[WORD_LIST_SIZE] = {"computer", "hangman", "electric", "triangle", "magnet"};
const char *hardHints[WORD_LIST_SIZE] = {"Electronic device", "This game", "Power type", "3-sided shape", "Attracts metal"};

void clearScreen() {
    system(CLEAR_COMMAND);
}

void printHeader(char *name, int score, int level) {
    printf("=============================================\n");
    printf("  Player: %s\tScore: %d\tLevel: %s\n", name, score,
           (level == 1 ? "Easy" : level == 2 ? "Moderate" : "Hard"));
    printf("=============================================\n\n");
}

void printHangman(int tries) {
    switch (tries) {
        case 1: printf("\n O\n"); break;
        case 2: printf("\n O\n |\n"); break;
        case 3: printf("\n O\n |/\n"); break;
        case 4: printf("\n O\n/|\\\n"); break;
        case 5: printf("\n O\n/|\\\n/\n"); break;
        case 6: printf("\n O\n/|\\\n/ \\\n"); break;
        case 7: printf("\n O\n/|\\\n/ \\\n\nGame Over!\n"); break;
        default: break;
    }
}

void printWord(char *word, int *guessed) {
    for (int i = 0; i < strlen(word); i++) {
        if (guessed[i]) {
            printf("%c ", word[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");
}

int checkWin(int *guessed, int wordLength) {
    for (int i = 0; i < wordLength; i++) {
        if (!guessed[i]) return 0;
    }
    return 1;
}

void chooseWord(int level, char *word, char *hint) {
    int index = rand() % WORD_LIST_SIZE;
    if (level == 1) {
        strcpy(word, easyWords[index]);
        strcpy(hint, easyHints[index]);
    } else if (level == 2) {
        strcpy(word, moderateWords[index]);
        strcpy(hint, moderateHints[index]);
    } else {
        strcpy(word, hardWords[index]);
        strcpy(hint, hardHints[index]);
    }
}

void chooseLevel(int *level, int *maxTries) {
    printf("Select Level:\n1. Easy\n2. Moderate\n3. Hard\nEnter choice: ");
    scanf("%d", level);
    switch (*level) {
        case 1: *maxTries = MAX_TRIES_EASY; break;
        case 2: *maxTries = MAX_TRIES_MODERATE; break;
        case 3: *maxTries = MAX_TRIES_HARD; break;
        default: *level = 1; *maxTries = MAX_TRIES_EASY;
    }
}

void startNewGame(Player *player) {
    char word[20], hint[50];
    int maxTries, wrongGuesses = 0;
    chooseLevel(&player->level, &maxTries);

    chooseWord(player->level, word, hint);
    int wordLength = strlen(word);
    int guessed[wordLength];
    memset(guessed, 0, sizeof(guessed));

    char guess;
    while (wrongGuesses < maxTries) {
        clearScreen();
        printHeader(player->name, player->score, player->level);
        printf("Hint: %s\n", hint);
        printWord(word, guessed);
        printHangman(wrongGuesses);
        printf("Guess a letter: ");
        scanf(" %c", &guess);

        int found = 0;
        for (int i = 0; i < wordLength; i++) {
            if (word[i] == guess && !guessed[i]) {
                guessed[i] = 1;
                found = 1;
            }
        }

        if (!found) wrongGuesses++;

        if (checkWin(guessed, wordLength)) {
            clearScreen();
            printHeader(player->name, player->score, player->level);
            printf("Hint: %s\n", hint);
            printWord(word, guessed);
            printf("\n?? Congratulations! You guessed the word!\n");
            player->score += 10;
            break;
        }
    }

    if (!checkWin(guessed, wordLength)) {
        clearScreen();
        printHeader(player->name, player->score, player->level);
        printHangman(wrongGuesses);
        printf("\n?? You lost! The word was: %s\n", word);
    }

    printf("\nPress Enter to return to menu...");
    getchar();
    getchar();
}

void showMainMenu() {
    printf("\n========== HANGMAN GAME ==========\n");
    printf("1. Start New Game\n");
    printf("2. View Leaderboard\n");
    printf("3. Exit Game\n");
    printf("==================================\n");
}
void saveLeaderboard(Player leaderboard[]) {
    FILE *file = fopen("leaderboard.txt", "w");
    if (file) {
        for (int i = 0; i < LEADERBOARD_SIZE; i++) {
            fprintf(file, "%s %d %d\n", leaderboard[i].name, leaderboard[i].score, leaderboard[i].level);
        }
        fclose(file);
    }
}

void loadLeaderboard(Player leaderboard[]) {
    FILE *file = fopen("leaderboard.txt", "r");
    if (file) {
        for (int i = 0; i < LEADERBOARD_SIZE; i++) {
            fscanf(file, "%49s %d %d", leaderboard[i].name, &leaderboard[i].score, &leaderboard[i].level);
        }
        fclose(file);
    } else {
        // Initialize empty leaderboard if file doesn't exist
        for (int i = 0; i < LEADERBOARD_SIZE; i++) {
            strcpy(leaderboard[i].name, "---");
            leaderboard[i].score = 0;
            leaderboard[i].level = 0;
        }
    }
}


void displayLeaderboard(Player leaderboard[]) {
    clearScreen();
    printf("========== TOP PLAYERS ==========\n");
    for (int i = 0; i < LEADERBOARD_SIZE; i++) {
        if (leaderboard[i].score > 0) {
            printf("%2d. %-20s %-6d (Level: %d)\n", 
                  i+1, leaderboard[i].name, leaderboard[i].score, leaderboard[i].level);
        }
    }
    printf("=================================\n");
    printf("\nPress Enter to continue...");
    getchar(); getchar();
}


































