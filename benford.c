#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "benford.h"

void readFile(const char* fileName, int *frequencies) 
{
  FILE *file = fopen(fileName, "r");
  if (file == NULL) {
    printf("Error while loading file.\n");
    exit(EXIT_FAILURE);
  }

  char line[MAX_LENGTH];

  while(fgets(line, sizeof(line), file) != NULL) {
    char *token = strtok(line, ",;\n ");

    while (token != NULL) {

      char number[MAX_DIGITS];
      strncpy(number, token, MAX_DIGITS - 1);
      number[MAX_DIGITS] = '\0';

      int firstDigit = number[0] - '0';

      frequencies[firstDigit - 1]++;

      token = strtok(NULL, ",;\n ");
    }
  }

  fclose(file);
}

void generateChart(const float *expectedFreq, const float *observedFreq, const char *outputFile)
{
  FILE *gnuplotPipe = popen("gnuplot -persistent", "w");
  if (gnuplotPipe == NULL) {
    printf("Error while executing GNUplot.\n");
    exit(EXIT_FAILURE);
  }

  fprintf(gnuplotPipe, "set term png\n");
  fprintf(gnuplotPipe, "set output '%s'\n", outputFile);

  fprintf(gnuplotPipe, "set title 'Benford'\n");
  fprintf(gnuplotPipe, "set xlabel 'Digits'\n");
  fprintf(gnuplotPipe, "set ylabel 'Frequency (in percent)'\n");
  fprintf(gnuplotPipe, "set style fill solid\n");
  fprintf(gnuplotPipe, "set boxwidth 0.4\n");
  fprintf(gnuplotPipe, "set xtics 1\n");
  fprintf(gnuplotPipe, "set grid\n");

  fprintf(gnuplotPipe, "set style line 1 linewidth 10\n"); 
  fprintf(gnuplotPipe, "plot '-' using 1:2 with linespoints lc rgb '#cf0000' lw 2 title 'Theorical frequencies', \
                        '-' using 1:2 with boxes lc rgb '#413bb8' title 'Real frequencies'\n");

  for (int i = 0; i < 9; i++) {
      fprintf(gnuplotPipe, "%d %f\n", i + 1, expectedFreq[i]);
  }
  fprintf(gnuplotPipe, "e\n");

  for (int i = 0; i < 9; i++) {
      fprintf(gnuplotPipe, "%d %f\n", i + 1, observedFreq[i]);
  }
  fprintf(gnuplotPipe, "e\n");

  // Fermeture du pipe GNUplot
  pclose(gnuplotPipe);
}
