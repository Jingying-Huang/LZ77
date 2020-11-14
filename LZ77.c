#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// LZ77 Logic:
// Search Buffer starts off empty
// Lookahead Buffer loads chars with corresponding size

struct LZ77 {
  int offset, length;
  char* symbol;
};

char* read_line(FILE* fileInput) {
  char* buffer = NULL;
  size_t len = 0;
  getline(&buffer, &len, fileInput);
  return buffer;
}

void push_back(char*** lines, char* buffer, int* num_lines) {
  *lines = realloc(*lines, (*num_lines + 1) * sizeof(*lines));
  ++(*num_lines);
  (*lines)[*num_lines - 1] = buffer;
}

void read_lines(FILE* fileInput, char*** lines, int* num_lines) {
  char* buffer = read_line(fileInput);
  if (!buffer) {
    exit(0);
  } else {
    while (!feof(fileInput)) {
      push_back(lines, buffer, num_lines);
      buffer = read_line(fileInput);
    }
  }
}

void compress(FILE* fileInput, char*** lines, int* num_lines) {}

FILE* validateInput(int argc, char* argv[]) {
  FILE* fileInput = NULL;
  if (argc < 2) {
    printf("Not enough arguments entered.\nEnding program.\n");
    exit(0);
  } else if (argc > 3) {
    printf("Too many arguments entered.\nEnding program.\n");
    exit(0);
  } else {
    fileInput = fopen(argv[2], "r");

    if (fileInput == NULL) {
      printf("Unable to open file: %s\nEnding program.\n", argv[2]);
      exit(0);
    }

    if (strcmp(argv[1], "-c") != 0 && strcmp(argv[1], "-d") != 0) {
      printf("Needs 2 arguments: [-c|-d] [file_path]\nEnding program.\n");
      exit(0);
    }
  }
  return fileInput;
}

int main(int argc, char* argv[]) {
  char** lines = NULL;
  int num_lines = 0;

  FILE* fileInput = validateInput(argc, argv);

  read_lines(fileInput, &lines, &num_lines);

  int i;
  for (i = 0; i < num_lines; ++i) {
    printf("%d, %s", i + 1, lines[i]);
  }

  return 0;
}
