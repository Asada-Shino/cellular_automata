#include <stdio.h>

#define CANT_OPEN_FILE -1

typedef struct {
    unsigned char RGB[3];
}Pixel;

int create_ppm(const char* file_name, Pixel* pixels, int width, int height) {
    FILE* fp = fopen(file_name, "wb");
    if(fp == NULL)
        return CANT_OPEN_FILE;
    fprintf(fp, "P6\n%d %d 255\n", width, height);
    fwrite(pixels, sizeof(char)*3, width*height, fp);
    fclose(fp);
    return 0;
}