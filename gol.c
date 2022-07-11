// Implementation of Conway's Game Of Life
#include <stdio.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <stdlib.h>

#include <time.h>

#define SCALE 2
#define ROWS 10 * SCALE
#define COLS 10 * SCALE
int ARR[ROWS][COLS];

void display_2d_arr(int arr[ROWS][COLS]);
int count_live_neighbors(int arr[ROWS][COLS], int x, int y);
void start_simulation();
double r2();

int main(int argc, char * argv[]) {
    int simulations = -1;
    char * endPtr;
    if (argc > 2) {
        printf("\nToo Many args....");
        printf("\n Usage: <executable> 'number of simulations(integer)'");
        exit(1);
    }
    if (argc == 2) {
        simulations = strtol(argv[1], & endPtr, 10);
        if ( * endPtr) {
            printf("Unable to convert '%s' to base %d.", argv[1], 10);
            exit(1);
        }
    }
    if (argc < 2) {
        printf("\nToo Few args....");
        printf("\n Usage: <executable> 'number of simulations(integer)'");
        exit(1);
    }
    srand(time(0));
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if ((i % 2) == 0 || (j % 2) == 0) {
                ARR[i][j] = r2() < 0.5 ? 0 : 1;
            } else {
                ARR[i][j] = 0;
            }
        }
    }

    printf("\e[1;1H\e[2J");
    display_2d_arr(ARR);

    printf("\n\nStarting Simulation...\n\n");

    for (int c = 0; c < simulations; c++) {
        printf("\nSimulation Number : %d\n", (c + 1));
        start_simulation();
        printf("\e[1;1H\e[2J");
        display_2d_arr(ARR);
    }

    return 0;
}

void display_2d_arr(int arr[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (arr[i][j] == 1) printf(" # ");
            if (arr[i][j] == 0) printf("   ");
            //printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

int count_live_neighbors(int arr[ROWS][COLS], int x, int y) {
    int count = 0;
    if (x + 1 < ROWS && y < COLS) {
        count += arr[x + 1][y];
    }
    if (x - 1 > 0 && y < COLS) {
        count += arr[x - 1][y];
    }
    if (x - 1 > 0 && y - 1 > 0) {
        count += arr[x - 1][y - 1];
    }
    if (x < ROWS && y - 1 > 0) {
        count += arr[x][y - 1];
    }
    if (x + 1 < ROWS && y - 1 > 0) {
        count += arr[x + 1][y - 1];
    }
    if (x - 1 > 0 && y + 1 < COLS) {
        count += arr[x - 1][y + 1];
    }
    if (x < ROWS && y + 1 < COLS) {
        count += arr[x][y + 1];
    }
    if (x + 1 < ROWS && y + 1 < COLS) {
        count += arr[x + 1][y + 1];
    }

    return count;
}

void start_simulation() {
    usleep(200 * 1000);
    //sleep(1);
    printf("\n\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int L_Ngh = count_live_neighbors(ARR, i, j);

            // Underpopulation
            if (ARR[i][j] == 1 && L_Ngh < 2) {
                ARR[i][j] = 0;
            }

            // Overpopulation
            if (ARR[i][j] == 1 && L_Ngh > 3) {
                ARR[i][j] = 0;
            }

            //Reproduction
            if (ARR[i][j] == 0 && L_Ngh == 3) {
                ARR[i][j] = 1;
            }
        }
    }
}

double r2() {
    return (double) rand() / (double) RAND_MAX;
}