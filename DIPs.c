#include "DIPs.h"

#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

/* Example of DIP */
/* make the picture color black & white */
IMAGE *BlackNWhite (IMAGE *image){
    int x, y, tmp;

    for (y = 0; y < ImageHeight(image); y++) {
        for (x = 0; x < ImageWidth(image); x++) {
            tmp = ( GetPixelR(image, x, y) + GetPixelG(image, x, y) + GetPixelB(image, x, y) ) / 3;
            SetPixelR(image, x, y, tmp);
            SetPixelG(image, x, y, tmp);
            SetPixelB(image, x, y, tmp);
        }
    }
        return image;
}

/* reverse image color */
IMAGE *Negative (IMAGE *image) {
    int x, y, tmpR, tmpG, tmpB;
    for (y = 0; y < ImageHeight(image); y++) {
        for (x = 0; x < ImageWidth(image); x++) {
                tmpR = MAX_PIXEL - GetPixelR(image, x, y);
                tmpG = MAX_PIXEL - GetPixelG(image, x, y);
                tmpB = MAX_PIXEL - GetPixelB(image, x, y);

                SetPixelR(image, x, y, tmpR);
                SetPixelG(image, x, y, tmpG);
                SetPixelB(image, x, y, tmpB);
        }
    }
        return image;
}

/*colorfiler */
IMAGE *ColorFilter (IMAGE *image, int target_r, int target_g, int target_b, int threshold, int replace_r, int replace_g, int replace_b) {
        int x, y , r, g, b;
        for (y = 0; y < ImageHeight(image); y++){
                for(x = 0; x < ImageWidth(image); x++){

                        r = GetPixelR(image, x, y);
                        g = GetPixelG(image, x, y);
                        b = GetPixelB(image, x, y);

                        if( (r > (target_r - threshold)) && (r < (target_r + threshold))
                        &&  (g > (target_g - threshold)) && (g < (target_g + threshold))
                        &&  (b > (target_b - threshold)) && (b < (target_b + threshold)) ) {
                                SetPixelR(image, x, y, replace_r);
                                SetPixelG(image, x, y, replace_g);
                                SetPixelB(image, x, y, replace_b);
                        }
                }
        }
        return image;
}

/* Add edge to the image*/
IMAGE *Edge (IMAGE *image){
    int x, y, m, n, a, b;
    int tempR, tempG, tempB;
    int HEIGHT = ImageHeight(image), WIDTH = ImageWidth(image);
    IMAGE *temp;
    temp = CreateImage(WIDTH, HEIGHT);
    for (y = 0; y < HEIGHT; y++){
        for (x = 0; x < WIDTH; x++) {
            SetPixelR(temp, x, y, GetPixelR(image, x, y));
            SetPixelG(temp, x, y, GetPixelG(image, x, y));
            SetPixelB(temp, x, y, GetPixelB(image, x, y));
        }
    }

    DeleteImage(image);
    image = CreateImage(WIDTH, HEIGHT);

    int sumR = 0;   /* sum of the intensity differences with neighbors */
    int sumG = 0;
    int sumB = 0;
    for (y = 1; y < HEIGHT - 1; y++){
        for (x = 1; x < WIDTH - 1; x++){
            for (n = -1; n <= 1; n++){
                for (m = -1; m <= 1; m++) {
                    a = (x + m >= WIDTH) ? WIDTH - 1 : (x + m < 0) ? 0 : x + m;
                    b = (y + n >= HEIGHT) ? HEIGHT - 1 : (y + n < 0) ? 0 : y + n;

                    sumR += (GetPixelR(temp, x, y) - GetPixelR(temp, a, b));
                    sumG += (GetPixelG(temp, x, y) - GetPixelG(temp, a, b));
                    sumB += (GetPixelB(temp, x, y) - GetPixelB(temp, a, b));
                }
            }
            tempR = (sumR > MAX_PIXEL) ? MAX_PIXEL: (sumR < 0) ? 0: sumR;
            SetPixelR(image, x, y, tempR);
            tempG = (sumG > MAX_PIXEL) ? MAX_PIXEL: (sumG < 0) ? 0: sumG;
            SetPixelG(image, x, y, tempG);
            tempB = (sumB > MAX_PIXEL) ? MAX_PIXEL: (sumB < 0) ? 0: sumB;
            SetPixelB(image, x, y, tempG);
            sumR = sumG = sumB = 0;
        }
    }
            /* set all four borders to 0 */
    for (y = 0; y < HEIGHT; y++) {
        SetPixelR(image, 0, y, 0);
        SetPixelG(image, 0, y, 0);
        SetPixelB(image, 0, y, 0);

        SetPixelR(image, WIDTH-1, y, 0);
        SetPixelG(image, WIDTH-1, y, 0);
        SetPixelB(image, WIDTH-1, y, 0);
   }

    for (x = 0; x < WIDTH; x++) {
        SetPixelR(image, x, 0, 0);
        SetPixelG(image, x, 0, 0);
        SetPixelB(image, x, 0, 0);

        SetPixelR(image, x, HEIGHT-1, 0);
        SetPixelG(image, x, HEIGHT-1, 0);
        SetPixelB(image, x, HEIGHT-1, 0);
    }
        DeleteImage(temp);
        return image;
}

/* flip image vertically */
IMAGE *VFlip (IMAGE *image){
    int             x, y;
    unsigned char   r, r1, g, g1,  b, b1;

    for (y = 0; y < ImageHeight(image)/2; y ++)
    {
        for (x = 0; x < ImageWidth(image); x ++)
        {
                r = GetPixelR(image, x, ImageHeight(image) - 1 - y);
                g = GetPixelG(image, x, ImageHeight(image) - 1 - y);
                b = GetPixelB(image, x, ImageHeight(image) - 1 - y);

                r1 = GetPixelR(image, x, y);
                g1 = GetPixelG(image, x, y);
                b1 = GetPixelB(image, x, y);

                SetPixelR(image, x, y, r);
                SetPixelG(image, x, y, g);
                SetPixelB(image, x, y, b);

                SetPixelR(image, x, ImageHeight(image) - 1 - y, r1);
                SetPixelG(image, x, ImageHeight(image) - 1 - y, g1);
                SetPixelB(image, x, ImageHeight(image) - 1 - y, b1);
        }
    }
        return image;
}

/* mirror image vertically */
IMAGE *VMirror (IMAGE *image) {
    int x, y, r, g, b;
    for (y = 0; y < ImageHeight(image) / 2; y ++) {
        for (x = 0; x < ImageWidth(image); x ++) {

                r = GetPixelR(image, x, y);
                g = GetPixelG(image, x, y);
                b = GetPixelB(image, x, y);

                SetPixelR(image, x, ImageHeight(image) - 1 - y, r);
                SetPixelG(image, x, ImageHeight(image) - 1 - y, g);
                SetPixelB(image, x, ImageHeight(image) - 1 - y, b);
        }
    }
        return image;
}


/* Shuffle the image */
IMAGE *Shuffle (IMAGE *image) {
    int HEIGHT = ImageHeight(image), WIDTH = ImageWidth(image);
    int block_cnt = SHUFF_HEIGHT_DIV * SHUFF_WIDTH_DIV;
    int block_width = WIDTH/SHUFF_WIDTH_DIV;
    int block_height = HEIGHT/SHUFF_HEIGHT_DIV;
    int block[SHUFF_WIDTH_DIV][SHUFF_HEIGHT_DIV];
    int i, j;

    srand(time(NULL));
    /* Initialize block markers to not done (-1) */
    for (i = 0; i < SHUFF_WIDTH_DIV; i++) {
        for (j = 0; j< SHUFF_HEIGHT_DIV; j++) {
            block[i][j] = -1;
        }
    }

    while (block_cnt > 0) {
        /* Generate a random pair of blocks */
        int dest_height = rand() % SHUFF_HEIGHT_DIV;
        int dest_width = rand() % SHUFF_WIDTH_DIV;
        int src_height = rand() % SHUFF_HEIGHT_DIV;
        int src_width = rand() % SHUFF_WIDTH_DIV;

        /* Check if these blocks are already swaped, if not swap blocks */
        if (( block[dest_width][dest_height] == -1) && (block[src_width][src_height] == -1)) {
            /* Swap blocks */
            for (i = 0; i < block_height; i++) {
                /* Init src and dest height offset */
                int h_dest = ((dest_height * block_height) + i) % HEIGHT;
                int h_src  = ((src_height * block_height) + i) % HEIGHT;
                for (j = 0; j < block_width; j++) {
                    int temp;
                    /* Init src and dest width offset */
                    int w_src  = ((src_width * block_width) + j) % WIDTH;
                    int w_dest = ((dest_width * block_width) + j) % WIDTH;

                    temp = GetPixelR(image, w_dest, h_dest);
                    SetPixelR(image, w_dest, h_dest, GetPixelR(image, w_src, h_src));
                    SetPixelR(image, w_src, h_src, temp);

                    temp = GetPixelG(image, w_dest, h_dest);
                    SetPixelG(image, w_dest, h_dest, GetPixelG(image, w_src, h_src));
                    SetPixelG(image, w_src, h_src, temp);

                    temp = GetPixelB(image, w_dest, h_dest);
                    SetPixelB(image, w_dest, h_dest, GetPixelB(image, w_src, h_src));
                    SetPixelB(image, w_src, h_src, temp);
                }
            }
            /* Set marker as done */
            block[dest_width][dest_height] = 1;
            block[src_width][src_height] = 1;
            /* Decrease block count */
            block_cnt -= 2; /* Two blocks are swapped */
        }

    }
        return image;
}

/* add border to the image */
IMAGE *AddBorder (IMAGE *image, char color[SLEN], int border_width) {
    int x, y;
    int HEIGHT = ImageHeight(image), WIDTH = ImageWidth(image);
    int border_r = 255;
    int border_g = 255;
    int border_b = 255;
    if (!strcmp(color, "black")) {
        border_r = 0;
        border_g = 0;
        border_b = 0;
    } else if (!strcmp(color, "white")) {
        border_r = 255;
        border_g = 255;
        border_b = 255;
    } else if (!strcmp(color, "red")) {
        border_r = 255;
        border_g = 0;
        border_b = 0;
    } else if (!strcmp(color, "green")) {
        border_r = 0;
        border_g = 255;
        border_b = 0;
    } else if (!strcmp(color, "blue")) {
        border_r = 0;
        border_g = 0;
        border_b = 255;
    } else if (!strcmp(color, "yellow")) {
        border_r = 255;
        border_g = 255;
        border_b = 0;
    } else if (!strcmp(color, "cyan")) {
        border_r = 0;
        border_g = 255;
        border_b = 255;
    } else if (!strcmp(color, "pink")) {
        border_r = 255;
        border_g = 192;
        border_b = 203;
    } else if (!strcmp(color, "orange")) {
        border_r = 255;
        border_g = 165;
        border_b = 0;
    } else {
        printf("Unsurported color.\n");
        return image;
    }
    const int X_BORDER_WIDTH = border_width * 9 / 16;
    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            if ((y < border_width) || (y > HEIGHT - 1 - border_width) ||
                    (x < X_BORDER_WIDTH) || (x > WIDTH - 1 - X_BORDER_WIDTH)) {
                        SetPixelR(image, x, y, border_r);
                        SetPixelG(image, x, y, border_g);
                        SetPixelB(image, x, y, border_b);

           }
        }
    }
        return image;
}


/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */

