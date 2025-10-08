#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* ---------- Structures ---------- */
typedef struct {
    char name[50];
    int score;
    double time_taken; // in seconds
} Leaderboard;

/* ---------- Utility Functions ---------- */
void show_rules(int choice) {
    if (choice == 1)
        printf("\n--- Sudoku Rules ---\nFill the 9x9 grid so that each row, column, and 3x3 box contains numbers 1–9.\n");
    else
        printf("\n--- Snake & Ladder Rules ---\nRoll dice, move forward. Snakes pull you down, ladders push you up. First to 100 wins.\n");
}

void save_game(const char *filename, int progress) {
    FILE *fp = fopen(filename, "w");
    if (!fp) return;
    fprintf(fp, "%d\n", progress);
    fclose(fp);
}

int load_game(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) return -1; // no saved file
    int progress;
    fscanf(fp, "%d", &progress);
    fclose(fp);
    return progress;
}

void save_leaderboard(const char *filename, Leaderboard lb) {
    FILE *fp = fopen(filename, "a");
    if (!fp) return;
    fprintf(fp, "%s %d %.2f\n", lb.name, lb.score, lb.time_taken);
    fclose(fp);
}

void show_leaderboard(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("No leaderboard yet!\n");
        return;
    }
    printf("\n--- Leaderboard ---\n");
    Leaderboard lb;
    while (fscanf(fp, "%s %d %lf", lb.name, &lb.score, &lb.time_taken) == 3) {
        printf("Player: %s | Score: %d | Time: %.2fs\n", lb.name, lb.score, lb.time_taken);
    }
    fclose(fp);
}

/* ---------- Dummy Games ---------- */
void sudoku_game() {
    int choice, progress = 0;
    time_t start, end;
    char name[50];

    while (1) {
        printf("\n--- Sudoku Menu ---\n1. New Game\n2. Load Game\n3. Back\nEnter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Starting new Sudoku...\n");
            start = time(NULL);

            // Simulate playing
            for (int i = 0; i < 3; i++) {
                printf("Playing Sudoku... progress %d%%\n", (i+1)*33);
                progress = (i+1) * 33;
            }

            end = time(NULL);
            double time_taken = difftime(end, start);

            printf("Game Over! Enter your name: ");
            scanf("%s", name);

            Leaderboard lb;
            strcpy(lb.name, name);
            lb.score = 100; // Dummy score
            lb.time_taken = time_taken;
            save_leaderboard("sudoku_leaderboard.txt", lb);

        } else if (choice == 2) {
            progress = load_game("sudoku_save.txt");
            if (progress == -1) {
                printf("No saved Sudoku found!\n");
            } else {
                printf("Loaded Sudoku progress: %d%%\n", progress);
            }
        } else if (choice == 3) {
            return; // back to main menu
        } else {
            printf("Invalid choice!\n");
        }
    }
}

void snake_game() {
    int choice, progress = 0;
    time_t start, end;
    char name[50];

    while (1) {
        printf("\n--- Snake & Ladder Menu ---\n1. New Game\n2. Load Game\n3. Back\nEnter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Starting new Snake & Ladder...\n");
            start = time(NULL);

            // Simulate playing
            for (int i = 0; i < 3; i++) {
                printf("Rolling dice... progress %d%%\n", (i+1)*33);
                progress = (i+1) * 33;
            }

            end = time(NULL);
            double time_taken = difftime(end, start);

            printf("Game Over! Enter your name: ");
            scanf("%s", name);

            Leaderboard lb;
            strcpy(lb.name, name);
            lb.score = 150; // Dummy score
            lb.time_taken = time_taken;
            save_leaderboard("snake_leaderboard.txt", lb);

        } else if (choice == 2) {
            progress = load_game("snake_save.txt");
            if (progress == -1) {
                printf("No saved Snake game found!\n");
            } else {
                printf("Loaded Snake game progress: %d%%\n", progress);
            }
        } else if (choice == 3) {
            return; // back to main menu
        } else {
            printf("Invalid choice!\n");
        }
    }
}

/* ---------- Main Menu ---------- */
int main() {
    int choice;

    while (1) {
        printf(" Main Menu ");
        printf("1. Play Sudoku\n");
        printf("2. Play Snake & Ladder\n");
        printf("3. Show Rules\n");
        printf("4. Show Leaderboard\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) sudoku_game();
        else if (choice == 2) snake_game();
        else if (choice == 3) {
            int g;
            printf("Choose game (1=Sudoku, 2=Snake & Ladder): ");
            scanf("%d", &g);
            show_rules(g);
        }
        else if (choice == 4) {
            int g;
            printf("Leaderboard for (1=Sudoku, 2=Snake & Ladder): ");
            scanf("%d", &g);
            if (g == 1) show_leaderboard("sudoku_leaderboard.txt");
            else show_leaderboard("snake_leaderboard.txt");
        }
        else if (choice == 5) {
            printf("Exiting... Goodbye!\n");
            break;
        }
        else printf("Invalid choice!\n");
    }

    return 0;
}