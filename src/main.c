#include "ppm.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define HEIGHT 400
#define WIDTH  300

Pixel img[HEIGHT][WIDTH];
int status[HEIGHT][WIDTH];

void set_color(Pixel* pixel, int type) {
    if(type == 0)
        pixel->RGB[0] = pixel->RGB[1] = pixel->RGB[2] = 255;
    else
        pixel->RGB[0] = pixel->RGB[1] = pixel->RGB[2] = 0;

}

int update(int status, unsigned char rule) {
    return (rule & (1<<status)) != 0;
}

int main() {
    char file_name[20];
    srand(time(0));
    for(int i = 0 ; i < WIDTH; ++i)
        status[0][i] = rand() & 1;
    for(int k = 0; k < 256; ++k) {
        for(int i = 1 ; i < HEIGHT; ++i) {
            status[i][0] = update(4*status[i-1][WIDTH-1] + 2*status[i-1][0] + status[i-1][1], k);
            for(int j = 1; j < WIDTH-1; ++j)
                status[i][j] = update(4*status[i-1][j-1] + 2*status[i-1][j] + status[i-1][j+1], k);
            status[i][WIDTH-1] = update(4*status[i-1][WIDTH-2] + 2*status[i-1][WIDTH-1] + status[i-1][0], k);
        }
        for(int i = 0; i < HEIGHT; ++i) {
            for(int j = 0; j < WIDTH; ++j) {
                set_color(&img[i][j], status[i][j]);
            }
        }
        sprintf(file_name, "assets/rule%03d.ppm", k);
        create_ppm(file_name, &img[0][0], WIDTH, HEIGHT);
    }
    return 0;
}