/*
Name: Dylan Fish
Course: COS 135
Date: 10/30/2026
Description: This program opens a list of room codes and names and will display them in a readable format in our terminal.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Stores a room's name, code, and description.
typedef struct {
    char name[100];
    char code[10];
    char description[1024];
} Room;

// Removes extra whitespace from the beginning and end.
void trim(char text[]) {
    int start = 0;
    int i = 0;
    int end;

    // Skips spaces at the beginning of the string.
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
    Room current = {"", "", ""};
    Room *rooms;
    int count = 0;
    int capacity = 2;
    int i;

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

    // Creates an array with space for two rooms.
    rooms = malloc(capacity * sizeof(Room));
    if (rooms == NULL) {
        printf("Could not allocate memory.\n");
        fclose(file);
        return 1;
    }

    // Reads the file one line at a time until the end.
    while (fgets(line, sizeof(line), file) != NULL) {

        // Checks what information the line contains.
        if (strncmp(line, "Room Name:", 10) == 0) {
            copyText(current.name, sizeof(current.name), line + 10);

        } else if (strncmp(line, "Room Code:", 10) == 0) {
            copyText(current.code, sizeof(current.code), line + 10);

        } else if (strncmp(line, "Room Description:", 17) == 0) {
            copyText(current.description, sizeof(current.description), line + 17);

            // Doubles the array size if there is no more room.
            if (count == capacity) {
                capacity = capacity * 2;
                Room *bigger = realloc(rooms, capacity * sizeof(Room));

                if (bigger == NULL) {
                    printf("Could not expand memory.\n");
                    free(rooms);
                    fclose(file);
                    return 1;
                }

                rooms = bigger;
            }

            // Saves the completed room into the array.
            rooms[count] = current;
            count++;
        }
    }

    // Closes the file.
    fclose(file);

    // Goes through the array and prints every room.
    for (i = 0; i < count; i++) {
        printf("Room %s: %s\n", rooms[i].code, rooms[i].name);
    }

    // Frees the memory used by the array.
    free(rooms);

    return 0;
}