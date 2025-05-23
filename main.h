#ifndef HEADER_M
#include <stdio.h>
#include<string.h>



#define SUCCESS 1
#define FAILURE 0

//structure for storing data from tagreader

typedef struct tag
{
    char title[50];
    char artist[50];
    char album[50];
    char year[5];
    char music[50];
    char comment[50];

}tag;

int validate(int argc,char *argv[]);

void help(void);

int mp3_view(char *argv[]);

int read_size(FILE **ptr,int count);


/*function prototype for mp3edit*/
int Mp3edit(char *argv[]);

/*function prototype for writing the data*/
void edit(FILE **ptr, char *argv[], int size);
#endif

