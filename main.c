#include<stdio.h>
#include<stdlib.h>
#define NO_OF_COL 44
#include <stdint.h>
char DataTypeBuffer[2];
int getNum(char ch)
{
    int num=0;
    if(ch>='0' && ch<='9')
    {
        num=ch-0x30;
    }
    else
    {
        switch(ch)
        {
            case 'A': case 'a': num=10; break;
            case 'B': case 'b': num=11; break;
            case 'C': case 'c': num=12; break;
            case 'D': case 'd': num=13; break;
            case 'E': case 'e': num=14; break;
            case 'F': case 'f': num=15; break;
            default: num=0;
        }
    }
    return num;
}
 
//function : hex2int
//this function will return integer value against
//hexValue - which is in string format
 
unsigned int hex2int(unsigned char hex[])
{
    unsigned int x=0;
    x=(getNum(hex[0]))*16+(getNum(hex[1]));
}
unsigned char AddressBuffer[4];
int countlines(char *filename);

/*

: 11 2222 33 44444444444444444444444444444444 55 \n

    ':' = Start Code.
    11 = Byte Count
    2222 = Address
    33 = Data Type
    44 = Data
    55 = Check Sum
    '\n' = End Code
*/
int ExtSegAdrF=0; 
int RecordTypes=0;
char Datas[16];

char recordTypes[3][6]={"Dat","Eof","EsA","SsA","ElA","SlA" };
char * readline(FILE *fp, char *buffer)
{
int ByteCount=0;
int Address=0;
int DataType=0;
int CheckSum=0;
int base=0;
int counter=0;
int k=0;    int ch;
int countthevalue=0;
    int i = 0;
    size_t buff_len = 0;

    buffer = malloc(buff_len + 1);
    if (!buffer) return NULL;  // Out of memory

    while ((ch = fgetc(fp)) != '\n' && ch != EOF)
    {
        buff_len++;
        void *tmp = realloc(buffer, buff_len + 1);
        if (tmp == NULL)
        {
            free(buffer);
            return NULL; // Out of memory
        }
        buffer = tmp;

        buffer[i] = (char) ch;
        i++;
    }
    buffer[i] = '\0';
counter=0;
countthevalue=0;
while(buffer[counter]!='\0')
{
switch(buffer[counter])
	{
	case ':' :
	base=counter;
	counter=0;
	countthevalue=1;
	}
if(countthevalue)

counter++;
}
ByteCount=((int)buffer[base+1])*16+(int)buffer[base+2];
AddressBuffer[0]=buffer[base+3];
AddressBuffer[1]=buffer[base+4];
AddressBuffer[2]=buffer[base+5];
AddressBuffer[4]=buffer[base+6];//,buffer[base+5],buffer[base+6]};
Address=hex2int(AddressBuffer);
DataTypeBuffer[0]=buffer[base+7];
DataTypeBuffer[1]=buffer[base+8];
DataType=hex2int(DataTypeBuffer);//((int)buffer[base+7])*16+(int)buffer[base+8];
printf("\nDatatype=%d\n\n",DataType);
//printf("\n\nRecord type=%s",recordTypes+DataType);
for(k=0;k<ByteCount*2;k++)
putchar(buffer[base+9+k]);
printf("\nCounts=%d",counter);

exit(0);
    // Detect end
    if (ch == EOF && (i == 0 || ferror(fp)))
    {
        free(buffer);
        return NULL;
    }
    return buffer;
}

void lineByline(FILE * file){
char *s;
while ((s = readline(file, 0)) != NULL)
{
    puts(s);
    free(s);
    printf("\n");
}
}
void main()//int argc, char *argv[])
{
int  rows=countlines("Flash.HEX");



printf("LINES: %d\n",rows);

printf("\n\nhi=%s",recordTypes[2]);
///char *p = malloc( sizeof(char) * (NO_OF_COL* rows + 1 ) );
//char (*orderedIds)[NO_OF_COL+1]= malloc(rows * sizeof(*orderedIds));
FILE *fp = fopen("Flash.HEX","r");;
int i=0;

lineByline(fp);
/*
while (fgets(p,rows,fp)!=NULL)
{


//printf("\n%d=%s",i,p);
i++;}
printf("\n....\n");
printf("\n%s",p);

free(p);//orderedIds);
*/
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
