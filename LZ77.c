#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SearchSize 7
#define LookaheadSize 6
#define WindowSize SearchSize + LookaheadSize

typedef enum { false, true } bool;
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

// While LookaheadBuffer is not empty
//      go backwards in searchBuffer to find longest match of the
//      LookaheadBuffer
//
//      if match found
//          print: (offset from window boundary, length of match, next symbol in
//          LookaheadBuffer);
//          shift window by length+1;
//      else
//          print: (0. 0, first symbol in LookaheadBuffer);
//          shift window by 1;

int fileSize(FILE* fileInput) {
  fseek(fileInput, 0, SEEK_END);
  int size = ftell(fileInput);
  rewind(fileInput);
  return size;
}

bool findMatch(char* searchBuffer) {
  bool found = false;
  return found;
}

void compress(FILE* fileInput) {
  char searchBuffer[SearchSize];
  char loadBuffer[LookaheadSize];
  char lookaheadBuffer[LookaheadSize];

  printf("File Size: %d\n", fileSize(fileInput));
  fread(lookaheadBuffer, 1, LookaheadSize, fileInput);
  fread(loadBuffer, 1, LookaheadSize, fileInput);

  if (findMatch(searchBuffer)) {
  } else {
    // Return (0, 0, symbol)
    // Shift a sequence of characters by 1
    size_t i = 1, j = 1;
    searchBuffer[SearchSize - 1] = lookaheadBuffer[0];

    for (; i < SearchSize - 1; ++i) {
      searchBuffer[i - 1] = searchBuffer[i];
    }

    for (; j < LookaheadSize; ++j) {
      lookaheadBuffer[j - 1] = lookaheadBuffer[j];
    }
  }
}

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

  // Read entire file
  FILE* fileInput = validateInput(argc, argv);
  read_lines(fileInput, &lines, &num_lines);
  compress(fileInput);
  return 0;
}
