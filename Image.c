#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Image.h"
#include "Constants.h"

/* Get the R intensity of pixel (x, y) in image */
unsigned char GetPixelR(const IMAGE *image, unsigned int x,  unsigned int y){
        assert(image);
        unsigned int WIDTH = ImageWidth(image);
        return image -> R[x + y * WIDTH];
}

/* Get the G intensity of pixel (x, y) in image */
unsigned char GetPixelG(const IMAGE *image, unsigned int x,  unsigned int y){
        assert(image);
        unsigned int WIDTH = ImageWidth(image);
        return image -> G[x + y * WIDTH];
}

/* Get the B intensity of pixel (x, y) in image */
unsigned char GetPixelB(const IMAGE *image, unsigned int x,  unsigned int y){
        assert(image);
        unsigned int WIDTH = ImageWidth(image);
        return image -> B[x + y * WIDTH];
}

/* Set the R intensity of pixel (x, y) in image to r */
void SetPixelR(IMAGE *image, unsigned int x,  unsigned int y, unsigned char r){
        assert(image);
        unsigned int WIDTH = ImageWidth(image);
        image -> R[x + y * WIDTH] = r;
}

/* Set the G intensity of pixel (x, y) in image to g */
void SetPixelG(IMAGE *image, unsigned int x,  unsigned int y, unsigned char g){
        assert(image);
        unsigned int WIDTH = ImageWidth(image);
        image -> G[x + y * WIDTH] = g;
}
/* Set the B intensity of pixel (x, y) in image to b */
void SetPixelB(IMAGE *image, unsigned int x,  unsigned int y, unsigned char b){
        assert(image);
        unsigned int WIDTH = ImageWidth(image);
        image -> B[x + y * WIDTH] = b;
}

/* Allocate dynamic memory for the image structure and its R/G/B values */
/* Return the pointer to the image, or NULL in case of error */
IMAGE *CreateImage(unsigned int Width, unsigned int Height){
        IMAGE *i;
        i = malloc(sizeof(IMAGE));
        if( !i){
                perror("Out of memory! Exit the program!!\n");
                exit(1);
        }
        i -> W = Width;
        i -> H = Height;
        i -> R = malloc(sizeof(IMAGE) * Width * Height);
        i -> G = malloc(sizeof(IMAGE) * Width * Height);
        i -> B = malloc(sizeof(IMAGE) * Width * Height);

        return i;
}

/* Free the memory for the R/G/B values and IMAGE structure */
void DeleteImage(IMAGE *image){
        assert(image);
        free(image -> R);
        free(image -> G);
        free(image -> B);
        free(image);
}

/* Return the image's width in pixels */
unsigned int ImageWidth(const IMAGE *image){
        assert(image);
        return image -> W;
}

/* Return the image's height in pixels */
unsigned int ImageHeight(const IMAGE *image){
        assert(image);
        return image -> H;
}

