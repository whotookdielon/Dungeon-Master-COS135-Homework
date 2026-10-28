/*
Name: Dylan Fish
Course: COS 135
Date: 10/30/2026
Description: This program opens a list of room codes and names and will display them in a readable format in our terminal.
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Stores a room's name, code, and description.
typedef struct {
    char name[100];
    char code[10];
    char description[1024];
} Room;

// Removes extra spaces from the beginning and end of a string.
void trim(char text[]) {
    int start = 0;
    int i = 0;
    int end;

    // Skips spaces at the beginning.
    while (isspace((unsigned char)text[start])) {
        start++;
    }

    // Moves the text forward to remove beginning spaces.
    while (text[start] != '\0') {
        text[i] = text[start];
        i++;
        start++;
    }
    text[i] = '\0';

    end = (int)strlen(text) - 1;

    // Removes spaces and newlines from the end.
    while (end >= 0 && isspace((unsigned char)text[end])) {
        text[end] = '\0';
        end--;
    }
}

// Copies text into a room field and trims it.
void copyText(char destination[], int size, char source[]) {
    snprintf(destination, size, "%s", source);
    trim(destination);
}

int main(int argc, char *argv[]) {
    FILE *file;
    char line[2048];
    Room room = {"", "", ""};

    // Checks if a filename was provided.
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Opens the room file.
    file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Could not open the file.\n");
        return 1;
    }

    // Reads the file one line at a time.
    while (fgets(line, sizeof(line), file) != NULL) {

        // Checks what information the line contains.
        if (strncmp(line, "Room Name:", 10) == 0) {
            copyText(room.name, sizeof(room.name), line + 10);

        } else if (strncmp(line, "Room Code:", 10) == 0) {
            copyText(room.code, sizeof(room.code), line + 10);

        } else if (strncmp(line, "Room Description:", 17) == 0) {
            copyText(room.description, sizeof(room.description), line + 17);

            // Prints the room after reading its information.
            printf("Room %s: %s\n", room.code, room.name);
        }
    }

    // Closes the file.
    fclose(file);

    return 0;
}
