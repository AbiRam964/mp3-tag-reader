#include <stdio.h>
#include"main.h"
/*
Name : ABIRAM VALIYAVALAPPIL
Date :
Dec  :
Sample input :
Sample output:
 */

int Mp3edit(char *argv[])
{
    char *label[6] = {"TIT2", "TPE1", "TALB", "TYER", "TCON", "COMM"};
    char temp[5] = {'\0'};
    char version[3];
    int size;
    FILE *fptr = fopen(argv[4],"r+");
    if(fptr == NULL)
    {
	fprintf(stderr, "ERROR: File Failed to open\n");
    }

    fread(temp,3,1,fptr);
    if(!strcmp(temp,"ID3"))                                     //Check for ID3 tag
    {
	fread(version,2,1,fptr);
	if(version[0] == 0x03 && version[1] == 0x00)           //Checking version
	{
	    fseek(fptr,10,SEEK_SET);                                                             //skip header
	    int i,j;
	    for(i = 0; i<6; i++)
	    {
		fread(temp,4,1,fptr);
		size = read_size(&fptr,4) - 1;
		fseek(fptr,3,SEEK_CUR);                                                       //skip flags
		for(j = 0; j <6; j++)
		{
		    if(strcmp(temp,label[j])==0)                                            //compare for tags
		    {
			break;
		    }

		}
		switch(j)                                                                                      
		{
		    case 0: 
			if(!strcmp(argv[2], "-t"))                                                        //options are checked
			{
			    printf("-------------------  CHANGE THE TITLE  --------------------------\n");
			    printf("TITLE    : %.*s\n",size,argv[3]);                                  //to prompt the user
			    edit(&fptr, argv, size);                                                     //function to write the input to 
			    printf("--------------- THE TITLE CHANGED SUCCESSFULLY ----------------\n");
			    return SUCCESS;
			}
			else
			{
			    fseek(fptr, size, SEEK_CUR);                                                 //move the pointer for next tag
			}
			break;

		    case 1:
			if(!strcmp(argv[2], "-a"))                                                      //check if option is artist
			{
			    printf("-------------------  CHANGE THE ARTIST --------------------------\n");
			    printf("ARTIST   : %.*s\n", size, argv[3]);
			    edit(&fptr, argv, size);
			    printf("--------------- THE ARTIST CHANGED SUCCESSFULLY ----------------\n");
			    return SUCCESS;
			}
			else
			{
			    fseek(fptr, size, SEEK_CUR);
			}
			break;

		    case 2:
			if(!strcmp(argv[2], "-A"))                                                       //for album
			{
			    printf("-------------------  CHANGE THE ALBUM  --------------------------\n");
			    printf("ALBUM    : %.*s\n", size, argv[3]);
			    edit(&fptr, argv, size);
			    printf("--------------- THE ALBUM CHANGED SUCCESSFULLY ----------------\n");
			    return SUCCESS;
			}
			else
			{
			    fseek(fptr, size, SEEK_CUR);                                      
			}
			break;

		    case 3:
			if(!strcmp(argv[2], "-y"))                                              //for year
			{
			    printf("-------------------  CHANGE THE YEAR   --------------------------\n");
			    printf("YEAR     : %.*s\n", size, argv[3]);
			    edit(&fptr, argv, size);
			    printf("--------------- THE YEAR CHANGED SUCCESSFULLY ----------------\n");
			    return SUCCESS;
			}
			else
			{
			    fseek(fptr, size, SEEK_CUR);
			}
			break;

		    case 4:
			if(!strcmp(argv[2], "-m"))                      //for music
			{
			    printf("-------------------  CHANGE THE MUSIC  --------------------------\n");
			    printf("MUSIC    : %.*s\n", size, argv[3]);
			    edit(&fptr, argv, size);
			    printf("--------------- THE MUSIC CHANGED SUCCESSFULLY ----------------\n");
			    return 0;
			}
			else
			{
			    fseek(fptr, size, SEEK_CUR);
			}
			break;

		    case 5:
			if(!strcmp(argv[2], "-c"))                  //for comment
			{
			    printf("-------------------  CHANGE THE COMMENT -------------------------\n");
			    printf("COMMENT  : %.*s\n", size, argv[3]);
			    edit(&fptr, argv, size);
			    printf("--------------- THE COMMENT CHANGED SUCCESSFULLY ----------------\n");
			    return SUCCESS;
			}
			else
			{
			    fseek(fptr, size, SEEK_CUR);
			}
			break;
		    default:
			fseek(fptr, size, SEEK_CUR);



		}
	    }
	}
	return FAILURE;
    }
    return FAILURE;
}
void edit(FILE **ptr, char *argv[], int size)
{
    int len = strlen(argv[3]);
    if(len < size)                                             //check if entered text is less than the size
    {
	fwrite(argv[3], len+1 , 1, *ptr);                       //write the string to mp3file
    }
    else
    {
	fwrite(argv[3], size, 1, *ptr);                        //if string size is greater than size write only the size number of characters
    }

}



