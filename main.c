//
//  main.c
//  "rgb2"
//
// A command line program to convert RGBA888 image files into RGBA222 files
// Usage: rgb2 [filename]
//
// Output: filename.RGB2
//
// If no filename is given then the entire current working directory of files will be converted.
// It is assumed that source files have a length divible by 4,
// which any valid RGBA8888 file whould have.
//
// Created by Richard Turnnidge on 15/03/2024.
// Intended for use on Mac, but may work on other platforms.
//
// Copy program to /usr/local/bin
// with:
// sudo cp rgb2 /usr/local/bin
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>

void doit(void);
void exportfile(char *thefilename);

#define FILENAMEMAXLENGTH            64
#define VERSION                       0
#define REVISION                      1
#define FEXT                    ".RGB2"
#define AFILE                         8

char m[64];
int ftype;
char outputName[64];
int byte1;
int byte2;
int byte3;
int byte4;
int bytecount;
int mydata;

struct dirent **namelist;
int n;

int myfilter(const struct dirent *name)
{
  return 1;
}

int main(int argc, const char * argv[]) {
    bytecount = 0;
    
    if ( argc != 2 ) /* argc is 2 if file name is given, else do whole folder */
        {
            printf( "usage: %s filename", argv[0] );

            DIR *dp;
             struct dirent *ep;
             dp = opendir ("./");
             if (dp != NULL)
             {
                 while ((ep = readdir (dp)) != NULL){
                     strcpy(m, ep->d_name);
                     ftype = ep->d_type;
                     if(ftype == AFILE)
                     {
                         exportfile(m);
                     }
                 }
                closedir (dp);
                return 0;
             }
             else
             {
                 perror ("Couldn't open the directory");
                 return -1;
             }
        }
        else
        {
            if (access((char*)argv[1], F_OK) == 0) {
                exportfile((char*)argv[1]);
            } else {
                printf( "Oops, %s does not seem to exist!\n",(char*)argv[1] );
            }
        }
            
    return 0;
}

void doit()
    {
        printf("Done - RGB2 version %d.%d, (C)2024 - Richard Turnnidge\r\n",VERSION,REVISION);
    }

void exportfile(char *thefilename){
    printf("We got %s", thefilename);
    // We assume argv[1] is a filename to open
    strcpy(outputName , thefilename);
    
    for(int i=0;i<strlen(outputName);i++) {
       if(outputName[i] == '.') {
           outputName[i]='\0';
           break;
       }
    }
    strcat(outputName , FEXT);
    
    FILE *file = fopen( thefilename, "rb" );
    FILE *outfile = fopen( outputName, "wb" );

    int x;
    while  ( ( x = fgetc( file ) ) != EOF )
        {
            bytecount++;

            byte1 = x;
            byte1 = byte1 & 0b11000000;
            byte1 = byte1 >> 6;
            
            byte2 = fgetc( file );
            byte2 = byte2 & 0b11000000;
            byte2 = byte2 >>4;
            
            byte3 = fgetc( file );
            byte3 = byte3 & 0b11000000;
            byte3 = byte3 >>2;

            byte4 = fgetc( file );
            byte4 = byte4 & 0b11000000;

            mydata = byte1 | byte2 | byte3 | byte4;
            fwrite(&mydata, 1,1, outfile);

        }
        
    fclose( file );
    fclose( outfile );
    
    printf(", so we made %s\n", outputName);
}
