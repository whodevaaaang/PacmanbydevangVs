#include <conio.h> 
#include <stdio.h> 
#include <stdlib.h> 

// elements
#define WIDTH 50 
#define HEIGHT 15 
#define PACMAN 'C' 
#define WALL '|' 
#define FOOD '.' 
#define EMPTY ' ' 
#define GHOST '@' 

// Global Variables
int result = 0; 
int game_score = 0; 
int pac_x, pac_y; 
char board[HEIGHT][WIDTH]; 
int total_food = 0; 
int eaten_food = 0; 

void setup_board() 
{ 
    for (int i = 0; i < HEIGHT; i++) { 
        for (int j = 0; j < WIDTH; j++) { 
            if (i == 0 || j == 0 || i == HEIGHT - 1 || j == WIDTH - 1) { 
                board[i][j] = WALL; 
            } 
            else
                board[i][j] = EMPTY; 
        } 
    } 

    int wall_count = 40; 
    while (wall_count > 0) { 
        int i = rand() % HEIGHT; 
        int j = rand() % WIDTH; 

        if (board[i][j] != WALL && board[i][j] != PACMAN) { 
            board[i][j] = WALL; 
            wall_count--; 
        } 
    } 

    int row_blocks = 4; 
    while (row_blocks--) { 
        int row = rand() % HEIGHT; 
        for (int j = 5; j < WIDTH - 5; j++) { 
            if (board[row][j] != WALL && board[row][j] != PACMAN) { 
                board[row][j] = WALL; 
            } 
        } 
    } 

    int ghost_count = 8; 
    while (ghost_count > 0) { 
        int i = rand() % HEIGHT; 
        int j = rand() % WIDTH; 

        if (board[i][j] != WALL && board[i][j] != PACMAN) { 
            board[i][j] = GHOST; 
            ghost_count--; 
        } 
    } 

    pac_x = WIDTH / 3; 
    pac_y = HEIGHT / 2; 
    board[pac_y][pac_x] = PACMAN; 

    for (int i = 0; i < HEIGHT; i++) { 
        for (int j = 0; j < WIDTH; j++) { 
            if ((i + j) % 3 == 0 && board[i][j] == EMPTY) { 
                board[i][j] = FOOD; 
                total_food++; 
            } 
        } 
    } 
} 

void display() 
{ 
    system("cls"); 

    for (int i = 0; i < HEIGHT; i++) { 
        for (int j = 0; j < WIDTH; j++) { 
            printf("%c", board[i][j]); 
        } 
        printf("\n"); 
    } 
    printf("Score: %d\n", game_score); 
    printf("Remaining Food: %d\n", total_food - eaten_food); 
} 

void move_pacman(int dx, int dy) 
{ 
    int new_x = pac_x + dx; 
    int new_y = pac_y + dy; 

    if (board[new_y][new_x] != WALL) { 
        if (board[new_y][new_x] == FOOD) { 
            game_score += 2; 
            eaten_food++; 
            if (eaten_food == total_food) { 
                result = 2; 
                return; 
            } 
        } 
        else if (board[new_y][new_x] == GHOST) { 
            result = 1; 
        } 

        board[pac_y][pac_x] = EMPTY; 
        pac_x = new_x; 
        pac_y = new_y; 
        board[pac_y][pac_x] = PACMAN; 
    } 
} 

int main() 
{ 
    setup_board(); 
    char command; 
    printf("Controls: w(up), a(left), d(right), s(down). Press q to quit.\n"); 
    printf("Enter Y to start the game: \n"); 

    command = getch(); 
    if (command != 'Y' && command != 'y') { 
        printf("Exiting the game.\n"); 
        return 1; 
    } 

    while (1) { 
        display(); 

        if (result == 1) { 
            system("cls"); 
            printf("Game Over! You were caught by a ghost.\nYour Score: %d\n", game_score); 
            return 1; 
        } 

        if (result == 2) { 
            system("cls"); 
            printf("You Win! Final Score: %d\n", game_score); 
            return 1; 
        } 

        command = getch(); 

        switch (command) { 
        case 'w': 
            move_pacman(0, -1); 
            break; 
        case 's': 
            move_pacman(0, 1); 
            break; 
        case 'a': 
            move_pacman(-1, 0); 
            break; 
        case 'd': 
            move_pacman(1, 0); 
            break; 
        case 'q': 
            printf("Game Over! Your Score: %d\n", game_score); 
            return 0; 
        } 
    } 

    return 0; 
}
