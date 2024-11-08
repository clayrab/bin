#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

int main() {
    FILE *file;
    int ch;
    int key;

    // Initialize ncurses mode
    initscr();
    // Disable echoing of characters typed by the user
    noecho();
    // React to keys instantly without requiring the Enter key
    cbreak();
    // Hide cursor
    curs_set(0);

    // Open the file
    file = fopen("read_keys.c", "r");
    if (file == NULL) {
        printw("Failed to open file\n");
        getch(); // Wait for user input
        endwin(); // End ncurses mode
        return 1;
    }

    // Read and display characters until EOF or Ctrl-C is pressed
    while ((ch = fgetc(file)) != EOF) {
        // Display the character
        printw("%c", ch);
        refresh();

        // Wait for any key press
        key = getch();

        // Check for Ctrl-C (usually not necessary as ncurses handles it, but here for completeness)
        if (key == 3) {
            break;
        }
    }

    // Close the file
    fclose(file);

    // Wait for final key press before exiting
    getch();
    // End ncurses mode
    endwin();

    return 0;
}