#include<stdio.h>
#include<stdlib.h>
#define NO_OF_COL 44
#include <stdint.h>
int countlines(char *filename);

void main(int argc, char *argv[])
{
int  rows=countlines("Flash.HEX");
printf("LINES: %d\n",rows);
char *p = malloc( sizeof(char) * ( rows + 1 ) );
//char (*orderedIds)[NO_OF_COL+1]= malloc(rows * sizeof(*orderedIds));
FILE *fp = fopen("Flash.HEX","r");;
int i=0;
while (fgets(p,rows,fp)!=NULL)
{

printf("\n%d=%s",i,p);
i++;}
free(p);//orderedIds);
}    //int *arr = (int *)malloc(rows * NO_OF_COL * sizeof(int)); 





//Open file for reading, function.
int countlines(char *filename)
{
  // count the number of lines in the file called filename                                    
  FILE *fp = fopen(filename,"r");
  int ch=0;
  int lines=0;

  if (fp == NULL)
  return 0;

  lines++;
  while ((ch = fgetc(fp)) != EOF)
    {
      if (ch == '\n')
    lines++;
    }
  fclose(fp);
  return lines;



}
