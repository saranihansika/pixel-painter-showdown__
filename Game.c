#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CANVAS_SIZE 10   // Size of the canvas grid (e.g., 10x10)
#define MAX_PIXELS 2  // Maximum number of pixels each player can use
#define MAX_COLORS 4   // Maximum number of available colors
#define MAX_PLAYERS 2
#define MAX_ROUNDS 3
#define PLAYER_TURN 2


// Function to initialize the canvas with blank spaces
void initializeCanvas(char canvas[][CANVAS_SIZE]) {
    for (int i = 0; i < CANVAS_SIZE; i++) {
        for (int j = 0; j < CANVAS_SIZE; j++) {
            canvas[i][j] = ' ';
        }
    }
}

// Function to display the canvas with the current artwork
void displayCanvas(char canvas[][CANVAS_SIZE]) {
    for (int i = 0; i < CANVAS_SIZE; i++) {
        for (int j = 0; j < CANVAS_SIZE; j++) {
            printf("%c ", canvas[i][j]);
        }
        printf("\n");
    }
}

// Function to handle player's turn to draw
void playerTurn(char canvas[][CANVAS_SIZE], char colors[], int playerPixels) {
    int x, y;
    char playerColor;
    int chosenColor;

    printf("Choose your color:\n");
    for (int i = 0; i < MAX_COLORS; i++) {
        printf("%d - %c\n", i + 1, colors[i]);
    }
    scanf("%d", &chosenColor);

    // Assign the chosen color to the player
    playerColor = colors[chosenColor - 1];

    while (playerPixels > 0) {
        printf("Remaining pixels: %d\n", playerPixels);
        displayCanvas(canvas);

        // Get player input for the position to place a pixel
        printf("Enter x and y coordinates to place a pixel: ");
        scanf("%d %d", &x, &y);

        // Check if the position is valid and place the pixel
        if (x >= 0 && x < CANVAS_SIZE && y >= 0 && y < CANVAS_SIZE) {
            if (canvas[x][y] == ' ') {
                canvas[x][y] = playerColor;
                playerPixels--;
            } else {
                printf("Pixel already placed there!\n");
            }
        } else {
            printf("Invalid coordinates! Try again.\n");
        }
    }
}

// Function to simulate the voting process and determine the winner
int determineWinner(int votes[], int numPlayers) {
    int maxVotes = 0;
    int winnerIndex = -1;

    for (int i = 0; i < numPlayers; i++) {
        if (votes[i] > maxVotes) {
            maxVotes = votes[i];
            winnerIndex = i;
        }
    }

    return winnerIndex;
}

int main() {
    char canvas[CANVAS_SIZE][CANVAS_SIZE];  // 2D array to store the canvas
    char colors[MAX_COLORS] = {'R', 'G', 'B', 'Y', 'W'};  // Available colors

    int numPlayers;  // Number of players (set based on lobby/room setup)
    int roundTime = 5 * 60;  // Time limit for each round in seconds (e.g., 5 minutes)

    int playerPixels[MAX_PLAYERS];  // Remaining pixels for each player
    int votes[MAX_PLAYERS] = {0};   // Array to store the votes for each player

    srand(time(0));  // Seed the random number generator with the current time

    // Game setup and lobby code goes here (e.g., room creation/joining)

    // Round starts
    for (int round = 1; round <= MAX_ROUNDS; round++) {
        // Initialize the canvas with blank spaces
        initializeCanvas(canvas);

        // Players choose colors one by one
        for (int i = 0; i < numPlayers; i++) {
            printf("Round %d, Player %d's turn:\n", round, i + 1);
            playerTurn(canvas, colors, MAX_PIXELS);

            // Save the remaining pixels for the current player for future rounds
            playerPixels[i] = MAX_PIXELS;
        }

        // End of the round, display artworks and handle voting

        // Simulate voting process (for demonstration purposes)
        for (int i = 0; i < numPlayers; i++) {
            int vote;
            printf("Player %d, vote for the best artwork (enter player number): ", i + 1);
            scanf("%d", &vote);

            // Ensure the vote is valid
            while (vote < 1 || vote > numPlayers || vote == i + 1) {
                printf("Invalid vote! Try again: ");
                scanf("%d", &vote);
            }

            votes[vote - 1]++;
        }

        // Determine the winner of the round
        int roundWinner = determineWinner(votes, numPlayers);
        printf("Round %d winner: Player %d\n", round, roundWinner + 1);
        // Reward the winning player with extra pixels (optional)

        // Clear votes for the next round
        for (int i = 0; i < numPlayers; i++) {
            votes[i] = 0;
        }
    }

    // End of the game, display final leaderboard and game-over message

    return 0;
}
