#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "benford.h"

void readFile(const char* fileName, int *frequencies) {
  FILE *file = fopen(fileName, "r");
  if (file == NULL) {
    printf("Erreur lors de l'ouverture du fichier.\n");
    exit(EXIT_FAILURE);
  }

  char line[MAX_LENGTH];

  while(fgets(line, sizeof(line), file) != NULL) {
    char *token = strtok(line, ";\n");

    while (token != NULL) {

      int firstDigit = atoi(token);

      while (firstDigit >= 10) {
        firstDigit /= 10;
      }

      frequencies[firstDigit - 1]++;

      token = strtok(NULL, ";\n");
    }
  }

  fclose(file);
}