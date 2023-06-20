#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "benford.h"

int main(int argc, char *argv[])
{
  if (argc != 2) {
    printf("Usage : <file.csv>\n");
    return 1;
  }
  
  float expectedFreq[9];
  float observedFreq[9];

  int data[9];
  memset(data, 0, sizeof(data));

  // Theorical frequencies calculation
  for (int i = 1; i <= 9; i++) {
    expectedFreq[i - 1] = log10(1.0 + (1.0 / i)) * MAX_LENGTH;
  }

  readFile(argv[1], data);

  // Real frequencies calculation
  int total = 0;
  for (int i = 0; i < 9; i++) {
    total += data[i];
  }
  for (int i = 0; i < 9; i++) {
    observedFreq[i] = ((float)data[i] / total) * MAX_LENGTH;
  }

  for (int i = 0; i < 9; i++) {
    printf("%.1f\n", observedFreq[i]);
  }

  // Generate chart
  const char * outputFile = "chart.png";
  generateChart(expectedFreq, observedFreq, outputFile);

  return 0;
}