#ifndef H_BENFORD
#define H_BENFORD

#define MAX_LENGTH 100
#define MAX_DIGITS 10000

void readFile(const char *fileName, int *frequencies);
void generateChart(const float *expectedFreq, const float *observedFreq, const char *outputFile);

#endif