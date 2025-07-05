#include <stdio.h>
#include <string.h>

void decompressor_RLE(char text[1024]){
    char c;
    int repeated = 0;
    char result[1024] = {0};
    char temp[124];
    for(int i = 0; i < strlen(text); i += 2){
        repeated = text[i] - '0';
        c = text[i+1];
        for (int j = 1; j <= repeated; j++){
            sprintf(temp, "%c", c);
            strcat(result, temp);
        }     
    }
    printf("The original message (decompressed data) was : %s", result);
}