#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

int dgg(struct fb_var_screeninfo *vinfo, struct fb_fix_screeninfo *finfo, char *fbp)
{
    int x = 100;
    int y = 100;
    
    long int location = 0;
    for (y = 100; y < 300; y++){
        for (x = 100; x < 300; x++){
            location = (x+vinfo->xoffset) * (vinfo->bits_per_pixel/8) + (y+vinfo->yoffset) * finfo->line_length;

            if (vinfo->bits_per_pixel == 32) {
                *(fbp + location) = 100;        // Some blue
                *(fbp + location + 1) = 15+(x-100)/2;     // A little green
                *(fbp + location + 2) = 200-(y-100)/5;    // A lot of red
                *(fbp + location + 3) = 0;      // No transparency
            } else  { //assume 16bpp
                int b = 10;
                int g = (x-100)/6;     // A little green
                int r = 31-(y-100)/16;    // A lot of red
                unsigned short int t = r<<11 | g << 5 | b;
                *((unsigned short int*)(fbp + location)) = t;
            }
        }
    }
    return 0;
}