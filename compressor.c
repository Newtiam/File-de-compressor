#include <stdio.h>
#include <string.h>

void compressor_RLE(char text[1024]){
    char c = text[0];
    short length = 1;
    char result[2048] = {0};
    char temp[124];
    for(int i = 1; i <= strlen(text); i++)
    {
        if(i == strlen(text) && c == text[i]){
            length++;
            sprintf(temp, "%d", length);
            strcat(result, temp);
            sprintf(temp, "%s", c);
            strcat(result, temp);
        }
        else if(c == text[i]){
            length++;
        }
        else if(c != text[i]){
            sprintf(temp, "%d", length);
            strcat(result, temp);
            sprintf(temp, "%c", c);
            strcat(result, temp);
            length = 1;
            c = text[i];
        }
    }
    printf("the compressed data is %s ", result);
}