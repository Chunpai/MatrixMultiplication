#include<stdio.h>
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
//prototype
double getRand(double min, double max);

void generateSquareMatrix(int matrixSize, char name[])
{
  FILE *fp;
  int i, j;
  double min=0.00001, max=100000;
  char comma[2];
  strcat(name,".csv");
  fp = fopen(name,"w");
  srand(time(NULL));
  fprintf(fp, "%d\n", matrixSize);
  for(i=0;i<matrixSize;i++)
  {
    sprintf(comma, "%s", "");
    for(j=0;j<matrixSize;j++)
    {
      fprintf(fp, "%s%f",comma,getRand(min, max));
      sprintf(comma, "%s", ",");;
    }
      fprintf(fp, "\n");
  }
  fclose(fp);
}


double getRand(double min, double max)
{
    double d = (double)rand() / RAND_MAX;
    return min + d * (max - min);
}
