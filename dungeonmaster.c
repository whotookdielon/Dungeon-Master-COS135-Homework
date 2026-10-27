
#include <stdio.h>
#include <string.h>

// Stores the basic information for one room.
typedef struct {
    char name[100];
    char code[10];
} Room;

int main(int argc, char *argv[]) {
    FILE *file;
    char line[2048];
    Room room = {"", ""};

    // Gets the file name from the command line.
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

    // Reads each line and finds the room name and code.
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strncmp(line, "Room Name:", 10) == 0) {
            sscanf(line + 10, " %99[^\r\n]", room.name);
        } else if (strncmp(line, "Room Code:", 10) == 0) {
            if (sscanf(line + 10, " %9[^\r\n]", room.code) == 1) {
                printf("Room %s: %s\n", room.code, room.name);
            }
        }
    }

    fclose(file);
    return 0;
}