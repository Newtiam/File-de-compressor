#include <stdio.h>
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

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
    printf("the width of the image is %d and its height is %d and the channels: %d \n", img->width, img->height, img->channels);
    return img;
}
void Text_compressor_RLE(char text[1024]){
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
void Image_compressor_RLE(const char* link){
    Image* img = load_image(link);
    for(int x = 1; x < img->width; x++){
        for(int y = 1; y < img->height; y++){
            unsigned char* pixel = img->data + (y * img->width + x) * img->channels;
            
            printf("the pixel in Row :%d Column: %d has Red: %d Blue: %d Green: %d \n", x, y, pixel[0], pixel[1], pixel[2]);
        }
    }
    
}