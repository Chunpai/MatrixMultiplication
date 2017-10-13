#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
//prototype
double getRandDouble(double min, double max);  //generate a random double number in range [min,max]
int getRandInt(int min, int max);              //generate a random integer in range[min,max]

//first parameter is the matrix size , second is the name of file this matrix will be stored into
void generateSquareDoubleMatrix(int matrixSize, char name[]); 
void generateSquareIntMatrix(int matrixSize, char name[]);



void generateSquareDoubleMatrix(int matrixSize, char name[])
{
  FILE *fp;
  int i, j;
  double min=0.00001, max=100000;
  char comma[2];
  strcat(name,".csv");   //pass in the name, and save the matrix into name.csv
  fp = fopen(name,"w");
  //srand(time(NULL));
  fprintf(fp, "%d\n", matrixSize);
  for(i=0;i<matrixSize;i++)
  {
    sprintf(comma, "%s", "");
    for(j=0;j<matrixSize;j++)
    {
      fprintf(fp, "%s%f",comma,getRandDouble(min, max));
      sprintf(comma, "%s", ",");;
    }
      fprintf(fp, "\n");
  }
  fclose(fp);
}

void generateSquareIntMatrix(int matrixSize, char name[])
{
  FILE *fp;
  int i, j;
  int min=1;
  int max=10;
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
      fprintf(fp, "%s%d",comma,getRandInt(min,max));
      sprintf(comma, "%s", ",");;
    }
      fprintf(fp, "\n");
  }
  fclose(fp);
}


double getRandDouble(double min, double max)
{
    double d = (double)rand() / RAND_MAX;
    return min + d * (max - min);
}

int getRandInt(int min, int max)
{
    return rand()%(max) + min;
}
