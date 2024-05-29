#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/_types/_null.h>
#include <sys/_types/_ssize_t.h>

typedef struct {
  char *block;
  size_t block_size;
  ssize_t input_size;
} InputBlock;

void error_handler(char error[]) {
  printf("%s", error);
  exit(EXIT_FAILURE);
};

InputBlock *create_input_block(void) {
  InputBlock *input_block = malloc(sizeof(InputBlock));
  input_block->block = NULL;
  input_block->block_size = 0;
  input_block->input_size = 0;
  return input_block;
};

void free_input_block(InputBlock *input_block) {
  free(input_block->block);
  free(input_block);
};

void read_prompt(InputBlock *input_block) {
  ssize_t bytes =
      getline(&(input_block->block), &(input_block->block_size), stdin);

  if (bytes <= 0) {
    error_handler("Error read input");
  };

  // Ignore trailing newline
  input_block->block_size = bytes - 1;
  input_block->block[bytes - 1] = 0;
};

void repl(void) {
  //
  printf("sqlite >> ");
}

int main() {
  InputBlock *input_block = create_input_block();

  while (true) {
    repl();
    read_prompt(input_block);

    if (strcmp(input_block->block, ".exit") == 0) {
      free_input_block(input_block);
      exit(EXIT_SUCCESS);
    } else {
      printf("Unrecognized command '%s'.\n", input_block->block);
    }
  }
};
