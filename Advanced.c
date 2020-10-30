#include "Advanced.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>


/* Add noise to an image */
IMAGE *AddNoise(IMAGE *image, int n) {
        int x, y, i;
        int num; /* number of noise added */
        num = ( n* ImageHeight(image) * ImageWidth(image) )/100;
        srand(time(NULL));

        for ( i = 0; i < num; i++ ) {
                x = ( (double)rand()/RAND_MAX )*(ImageWidth(image)-1);
                y = ( (double)rand()/RAND_MAX )*(ImageHeight(image)-1);
                SetPixelR(image, x, y, 255);
                SetPixelG(image, x, y, 255);
                SetPixelB(image, x, y, 255);
        }
        return image;
}


/* sharpen the image */
IMAGE *Sharpen (IMAGE *image) {
        int x, y, m, n, a, b;
        int tmpR = 0;
        int tmpG = 0;
        int tmpB = 0;
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

        for (y = 0; y < HEIGHT; y++){
                for (x = 0; x < WIDTH; x++){
                        for (n = -1; n <= 1; n++){
                                for (m = -1; m <= 1; m++) {
                                        a = x + m;
                                        b = y + n;
                                        if (a > WIDTH - 1)
                                                a = WIDTH - 1;
                                        if (a < 0)
                                                a = 0;
                                        if (b > HEIGHT - 1)
                                                b = HEIGHT - 1;
                                        if (b < 0)
                                                b = 0;

                                        if ((n==0)&&(m==0))
                                        {
                                                tmpR += 9*GetPixelR(temp, a, b) ;
                                                tmpG += 9*GetPixelG(temp, a, b) ;
                                                tmpB += 9*GetPixelB(temp, a, b) ;
                                        }
                                        else
                                        {
                                                tmpR -= GetPixelR(temp, a, b) ;
                                                tmpG -= GetPixelG(temp, a, b) ;
                                                tmpB -= GetPixelB(temp, a, b) ;
                                        }
                                }
                        }
                        SetPixelR(image, x, y, (tmpR>255)? 255: (tmpR<0)? 0: tmpR);
                        SetPixelG(image, x, y, (tmpG>255)? 255: (tmpG<0)? 0: tmpG);
                        SetPixelB(image, x, y, (tmpB>255)? 255: (tmpB<0)? 0: tmpB);
                        tmpR = tmpG = tmpB = 0;
                }
        }
        return image;
}

/* make the image posterized */
IMAGE *Posterize (IMAGE *image, unsigned int rbits, unsigned int gbits, unsigned int bbits) {
        int x, y, tempR, tempG,tempB;
        int HEIGHT = ImageHeight(image), WIDTH = ImageWidth(image);
        for(x=0; x<WIDTH; x++) {
                for(y=0; y<HEIGHT; y++) {
                        unsigned char one = 1;
                        int i;
                        for(i=0; i<rbits-1; i++) {
                                tempR = GetPixelR(image, x, y);
                                tempR |= one;
                                one <<= 1;
                        }
                        one = ~one;
                        tempR &= one;
                        SetPixelR(image, x, y, tempR);

                        one = 1;
                        for(i=0; i<gbits-1; i++) {
                                tempG = GetPixelG(image, x, y);
                                tempG |= one;
                                one <<= 1;
                        }
                        one = ~one;
                        tempG &= one;
                        SetPixelG(image, x, y, tempG);

                        one = 1;
                        for(i=0; i<bbits-1; i++) {
                                tempB = GetPixelB(image, x, y);
                                tempB |= one;
                                one <<= 1;
                        }
                        one = ~one;
                        tempB &= one;
                        SetPixelB(image, x, y, tempB);
                }
        }
        return image;
}

/* add motion blur to the image */
IMAGE *MotionBlur(IMAGE *image, int BlurAmount){
        int x,y,m;
        unsigned int temp_r , temp_g , temp_b;

        for (x = 0; x < ImageWidth(image); x++)
                for (y = 0; y < ImageHeight(image) ; y++)
                {
                        temp_r = GetPixelR(image, x, y)/2;
                        temp_b = GetPixelB(image, x, y)/2;
                        temp_g = GetPixelG(image, x, y)/2;

                        for (m = 1; m<=BlurAmount ; m++)
                        {
                                if ((x+m) < ImageWidth(image))
                                {
                                        temp_r = temp_r + GetPixelR(image, x+m, y) * 0.5/BlurAmount;
                                        temp_b = temp_b + GetPixelB(image, x+m, y) * 0.5/BlurAmount;
                                        temp_g = temp_g + GetPixelG(image, x+m, y) * 0.5/BlurAmount;
                                }
                        }
                        SetPixelR(image, x, y, temp_r);
                        SetPixelB(image, x, y, temp_b);
                        SetPixelG(image, x, y, temp_g);
                }
        return image;
}

/*Crop the image*/
IMAGE *Crop(IMAGE *image, unsigned int x, unsigned int y, unsigned int W, unsigned int H){
        unsigned int WIDTH = ImageWidth(image), HEIGHT = ImageHeight(image);
        int i, j, lenW, lenH, tmpR, tmpB, tmpG;
        IMAGE *temp;


        if(W + x > WIDTH){
                W = WIDTH - x;
        }
        if(H + y > HEIGHT){
                H = HEIGHT - y;
        }
        lenW = W + x;
        lenH = H + y;
        temp = CreateImage(W, H);

        for ( i = x; i < lenW; i++){
                for ( j = y; j < lenH; j++) {
                        if( i > WIDTH || j > HEIGHT){break;}
                        tmpR = GetPixelR(image, i, j);
                        tmpG = GetPixelG(image, i, j);
                        tmpB = GetPixelB(image, i, j);

                        SetPixelR(temp, i-x, j-y, tmpR);
                        SetPixelG(temp, i-x, j-y, tmpG);
                        SetPixelB(temp, i-x, j-y, tmpB);
                }
        }
        DeleteImage(image);
        image = CreateImage(W, H);

        for ( i = 0; i < W; i++){
                for ( j = 0; j < H; j++) {
                        if( i > WIDTH || j > HEIGHT){break;}
                        tmpR = GetPixelR(temp, i, j);
                        tmpG = GetPixelG(temp, i, j);
                        tmpB = GetPixelB(temp, i, j);

                        SetPixelR(image, i, j, tmpR);
                        SetPixelG(image, i, j, tmpG);
                        SetPixelB(image, i, j, tmpB);
                }
        }
        return image;
}

/*Resize the image*/
IMAGE *Resize(IMAGE *image, int percentage){
        if(percentage == 100){return image;}

        int x, y, i, j;
        unsigned int WIDTH = ImageWidth(image), HEIGHT = ImageHeight(image);
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

        int newW, newH;
        double n, n1;
        double x1_old, x2_old, y1_old, y2_old, sumR, sumG, sumB, avgR, avgG, avgB, counter;
        n = percentage / 100.00;
        n1 = 100.00 / percentage;
        newW = WIDTH * n;
        newH = HEIGHT * n;
        image = CreateImage(newW, newH);

        if(percentage > 100){
                for (y = 0; y < newH; y++){
                        for (x = 0; x < newW; x++) {
                                SetPixelR(image, x, y, GetPixelR(temp, x*n1, y*n1));
                                SetPixelG(image, x, y, GetPixelG(temp, x*n1, y*n1));
                                SetPixelB(image, x, y, GetPixelB(temp, x*n1, y*n1));
                        }
                }
        }

        if(percentage < 100){
                for (y = 0; y < newH; y++){
                        for (x = 0; x < newW; x++) {
                                x1_old = x * n1;
                                y1_old = y * n1;
                                x2_old = (x+1) * n1;
                                y2_old = (y+1) * n1;
                                sumR = sumB = sumG = avgR = avgG = avgB = counter = 0;
                                for(i = x1_old; i < x2_old; i++){
                                        for(j = y1_old; j < y2_old; j++){
                                                sumR += GetPixelR(temp, i, j);
                                                sumG += GetPixelG(temp, i, j);
                                                sumB += GetPixelB(temp, i, j);
                                                counter++;
                                        }
                                }
                                avgR = sumR /( counter );
                                avgG = sumG /( counter );
                                avgB = sumB /( counter );

                                SetPixelR(image, x, y, avgR);
                                SetPixelG(image, x, y, avgG);
                                SetPixelB(image, x, y, avgB);
                        }
                }
        }
        return image;
}

/*Brightness and Contrast*/
IMAGE *BrightnessAndContrast(IMAGE *image, int brightness, int contrast){
        int x, y;
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

        double factor;
        int voldR, voldG, voldB, vnewR, vnewG, vnewB;

        factor =(double) ( 259 * (contrast + 255))/(double)( 255 * (259 - contrast));
        for (y = 0; y < HEIGHT; y++){
                for (x = 0; x < WIDTH; x++) {
                        voldR = GetPixelR(temp, x, y);
                        voldG = GetPixelG(temp, x, y);
                        voldB = GetPixelB(temp, x, y);

                        vnewR = (factor * (voldR - 128) + 128)+brightness;
                        if(vnewR > 255){vnewR = 255;}
                        if(vnewR < 0 ) {vnewR = 0;}
                        vnewG = (factor * (voldG - 128) + 128)+brightness;
                        if(vnewG > 255){vnewG = 255;}
                        if(vnewG < 0 ) {vnewG = 0;}
                        vnewB = (factor * (voldB - 128) + 128)+brightness;
                        if(vnewB > 255){vnewB = 255;}
                        if(vnewB < 0 ) {vnewB = 0;}

                        SetPixelR(image, x, y, vnewR);
                        SetPixelG(image, x, y, vnewG);
                        SetPixelB(image, x, y, vnewB);
                }
        }
        return image;
}

/*Watermark the image*/
IMAGE *Watermark(IMAGE *image, const IMAGE *watermark_image){
        unsigned int WIDTH = ImageWidth(image), HEIGHT = ImageHeight(image);
        unsigned int WWIDTH = ImageWidth(watermark_image), WHEIGHT = ImageHeight(watermark_image);
        double tmpR, tmpG, tmpB;
        double R, G, B;
        int x, y;

        for (y = 0; y < HEIGHT; y++){
                for (x = 0; x < WIDTH; x++) {
                        tmpR = tmpG = tmpB = 0;
                        tmpR = GetPixelR(watermark_image, x%WWIDTH, y%WHEIGHT);
                        tmpG = GetPixelG(watermark_image, x%WWIDTH, y%WHEIGHT);
                        tmpB = GetPixelB(watermark_image, x%WWIDTH, y%WHEIGHT);

                        if(tmpR == 0 && tmpG == 0 && tmpB ==0){
                        R = GetPixelR(image, x, y);
                        G = GetPixelG(image, x, y);
                        B = GetPixelB(image, x, y);

                        tmpR = R * 1.45;
                        tmpG = G * 1.45;
                        tmpB = B * 1.45;

                        if(tmpR > 255) {tmpR = 255;}
                        if(tmpR < 0) {tmpR = 0;}
                        if(tmpG > 255) {tmpG = 255;}
                        if(tmpG < 0) {tmpG = 0;}
                        if(tmpB > 255) {tmpB = 255;}
                        if(tmpB < 0) {tmpB = 0;}

                        SetPixelR(image, x, y, tmpR);
                        SetPixelG(image, x, y, tmpG);
                        SetPixelB(image, x, y, tmpB);
                        }
                }
        }
        return image;
}
/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */

