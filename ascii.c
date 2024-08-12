#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

const char *ASCII_CHARS = " .:-=+*#%@";

void getTerminalSize(int *width, int *height) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    *width = w.ws_col;
    *height = w.ws_row;
}

void imageToAscii(const char *filename) {
    int img_width, img_height, channels;
    unsigned char *img = stbi_load(filename, &img_width, &img_height, &channels, 0);
    
    if(img == NULL) {
        printf("Error in loading the image\n");
        exit(1);
    }

    int term_width, term_height;
    getTerminalSize(&term_width, &term_height);
    
    float scale_w = (float)img_width / term_width;
    float scale_h = (float)img_height / (term_height * 2);
    float scale = scale_w > scale_h ? scale_w : scale_h;

    int scaled_width = (int)(img_width / scale);
    int scaled_height = (int)(img_height / scale / 2);

    int offset_x = (term_width - scaled_width) / 2;
    int offset_y = (term_height - scaled_height) / 2;

    printf("\033[2J");

    for(int y = 0; y < term_height; y++) {
        for(int x = 0; x < term_width; x++) {
            if(y >= offset_y && y < offset_y + scaled_height && x >= offset_x && x < offset_x + scaled_width) {
                int img_x = (int)((x - offset_x) * scale);
                int img_y = (int)((y - offset_y) * scale * 2);
                unsigned char *p = img + (img_y * img_width + img_x) * channels;
                int brightness = (p[0] + p[1] + p[2]) / 3;
                int index = brightness * (sizeof(ASCII_CHARS) - 2) / 255;
                putchar(ASCII_CHARS[index]);
            } else {
                putchar(' ');
            }
        }
        if(y < term_height - 1) {
            printf("\n");
        }
    }

    stbi_image_free(img);
}

int main(int argc, char **argv) {
    if(argc != 2) {
        printf("Usage: %s <image_file>\n", argv[0]);
        return 1;
    }
    
    imageToAscii(argv[1]);
    return 0;
}
