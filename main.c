#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdbool.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include "compressor.c"
#include "decomprssor.c"

#define FAIL_COLOR "\033[91m"
#define DEFAULT "\033[0m"

__declspec(dllimport) void __stdcall Sleep(unsigned long ms);

typedef struct
{
    int width, height, channels;
    unsigned char *data;
} Image;

Image *load_image(const char *filename){
    Image *img = malloc(sizeof(Image));
    if (!img) return NULL;
    img->data = stbi_load(filename, &img->width, &img->height, &img->channels, 0);
    if (!img->data){
        free(img);
        return NULL;
    }
    printf("the width of the image is %d and its height is %d ", img->width, img->height);
    return img;
}
bool search_file(const char* url){
    WIN32_FIND_DATA fd;
    HANDLE hfind = FindFirstFile(url, &fd);
    if (hfind != INVALID_HANDLE_VALUE){
        printf("file found :) \n");
        return 1;
    }
    else{
        printf("an error found, try checking the right path of the file! \n");
        return 0;
    }
    FindClose(hfind);
}
int main(){
    printf("welcome to RLE de/compressor, choose the following commands \n[1] Compressing \n[2] Decompressing \n> ");
    char input[24];
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0'; 
    if (strcmp(input, "1") == 0 || strcmp(input, "Compressing") == 0) {
        printf("Choose the file type you want to compress: \n[1] Text\n[2] Image\n > ");
        char text[6];
        fgets(text, sizeof(text), stdin);
        text[strcspn(text, "\n")] = '\0';
        if (strcmp(text, "1") == 0 || strcmp(text, "Text") == 0) {
            printf("Enter the text that you want to compress: ");
            char Text_compressor[1024];
            fgets(Text_compressor, sizeof(Text_compressor), stdin);
            Text_compressor[strcspn(Text_compressor, "\n")] = '\0'; 
            compressor_RLE(Text_compressor);
        }
        else if (strcmp(text, "2") == 0 || strcmp(text, "Image") == 0){
            printf("now, please Enter the name of the file: ");
            char link[512];
            fgets(link, sizeof(link), stdin);
            link[strcspn(link, "\n")] = '\0';
            printf("%s", link);
            if (search_file(link)){
                load_image(link);
            }
            else{
                return 0;
            }
        }
        else {
            printf("%sError: Invalid command, please reset%s\n", FAIL_COLOR, DEFAULT);
        }
    }
    else if (strcmp(input, "2") == 0 || strcmp(input, "Decompressing") == 0)
    {
        printf("Please type the text that you want to decompress \n> ");
        char Text_decompressor[1024];
        fgets(Text_decompressor, sizeof(Text_decompressor), stdin);
        Text_decompressor[strcspn(Text_decompressor, "\n")] = '\0';
        decompressor_RLE(Text_decompressor);
    }
    else {
        printf("%sError: Invalid command, please reset%s\n", FAIL_COLOR, DEFAULT);
    }
    return 0;
}