#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "life.h"

/* Be sure to read life.h and the other given source files to understand
 * what they provide and how they fit together.  You don't have to
 * understand all of the code, but you should understand how to call
 * parse_life() and clearterm().
 */

/* This is where your program will start.  You should make sure that it
 * is capable of accepting either one or two arguments; the first
 * argument (which is required) is a starting state in one of the Life
 * formats supported by parse_life(), and the second (which is optional)
 * is a number of generations to run before printing output and stopping.
 *
 * The autograder will always call your program with two arguments.  The
 * one-argument format (as described in the handout) is for your own
 * benefit!
 */
int countAlive(char **grid, int y, int x){
    int count = 0;
    for(int i = -1; i<2; i++){
        for(int j = -1; j<2; j++){
            if(i==0 && j==0)
                continue;
            int pos_y = y+i;
            int pos_x = x+j;
            if(pos_y>-1 && pos_y < GRIDY && pos_x>-1 && pos_x < GRIDX){
                if(grid[pos_y][pos_x]==LIVE){
                    count++;
                }
            }
        }
    }
    return count;
}

void simulateGen(char **a, char **b){
    for (int i = 0; i < GRIDY; i++) {
        for (int j = 0; j < GRIDX; j++) {
            int neighbour_live_cell
                = countAlive(a, i, j);
            if (a[i][j] == 1
                && (neighbour_live_cell == 2
                    || neighbour_live_cell == 3)) {
                b[i][j] = 1;
            }

            else if (a[i][j] == 0
                     && neighbour_live_cell == 3) {
                b[i][j] = 1;
            }

            else {
                b[i][j] = 0;
            }
        }
    }
}

void print_grid(char **grid) {
    for (int i = 0; i < GRIDY; ++i) {
        for (int j = 0; j < GRIDX; ++j) {
            putchar(grid[i][j]);
        }
        putchar('\n');
    }
}


int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <inputfile> <generation>\n", argv[0]);
        return 1;
    }
    const char *filename = argv[1];
    int target_generation = atoi(argv[2]);

    if (target_generation < 0) {
        fprintf(stderr, "Invalid generation number. Must be a non-negative integer.\n");
        return 1;
    }

    char **grid = parse_life(filename);
    if (grid == NULL) {
        fprintf(stderr, "Error reading file: %s\n", filename);
        return 1;
    }
    char **next_grid = malloc(GRIDY * sizeof(char *));
    for (int i = 0; i < GRIDY; i++) {
        next_grid[i] = malloc(GRIDX * sizeof(char));
    }

    for (int gen = 0; gen <= target_generation; ++gen) {
        clearterm();
        print_grid(grid);
        usleep(300000);
        if (gen < target_generation) {
            simulateGen(grid, next_grid);
            char **temp = grid;
            grid = next_grid;
            next_grid = temp;
        }
    }
    free_grid(grid);
    free_grid(next_grid);
    return 0;
}
