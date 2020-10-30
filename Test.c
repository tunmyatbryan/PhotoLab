#include <stdio.h>
#include "Test.h"
#include "Image.h"
#include "FileIO.h"
#include "DIPs.h"
#include "Advanced.h"

int AutoTest(void) {
    int result;
    const char fname[SLEN] = "HSSOE";
    const char watermarkImgName[SLEN] = "watermark_template";
    char color[SLEN] = "yellow";

    IMAGE *image = NULL;
    image = LoadImage(fname);
    if (! image) return 11;
    image = BlackNWhite(image);
    if (! image) return 12;
    result = SaveImage("bw", image);
    if (result) return result;
#ifdef DEBUG
    printf("Black and White tested!\n\n");
#endif
        DeleteImage(image);
        image = NULL;

    image = LoadImage(fname);
    if (! image) return 13;
    image = Negative(image);
    if (! image) return 14;
    result = SaveImage("negative", image);
    if (result) return result;
#ifdef DEBUG
    printf("Negative tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    if (! image) return 15;
    image = ColorFilter(image, CF_TARGET_R, CF_TARGET_G, CF_TARGET_B, CF_THRESHOLD, CF_REPLACED_R, CF_REPLACED_G, CF_REPLACED_B);
    if (! image) return 16;
    result = SaveImage("colorfilter", image);
    if (result) return result;
#ifdef DEBUG
    printf("Color Filter tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    if (! image) return 17;
    image = Edge(image);
    if (! image) return 18;
    result = SaveImage("edge", image);
    if (result) return result;
#ifdef DEBUG
    printf("Edge Detection tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    if (! image) return 19;
    image = Shuffle(image);
    if (! image) return 20;
    result = SaveImage("shuffle", image);
    if (result) return result;
#ifdef DEBUG
    printf("Shuffle tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    if (! image) return 21;
    image = VFlip(image);
    if (! image) return 22;
    result = SaveImage("vflip", image);
    if (result) return result;
#ifdef DEBUG
    printf("VFlip tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    if (! image) return 23;
    image = VMirror(image);
    if (! image) return 24;
    result = SaveImage("vmirror", image);
    if (result) return result;
#ifdef DEBUG
    printf("VMirror tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    if (! image) return 25;
    image = AddBorder(image, color, BORDER_WIDTH);
    if (! image) return 26;
    result = SaveImage("border", image);
    if (result) return result;
#ifdef DEBUG
    printf("Add Border tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    if (! image) return 27;
    image = AddNoise(image, NOISE_PERCENTAGE);
    if (! image) return 28;
    result = SaveImage("noise", image);
    if (result) return result;
#ifdef DEBUG
    printf("Add Noise tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    if (! image) return 29;
    image = Sharpen(image);
    if (! image) return 30;
    result = SaveImage("sharpen", image);
    if (result) return result;
#ifdef DEBUG
    printf("Sharpen tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    if (! image) return 31;
    image = Posterize(image, R_BITS, G_BITS, B_BITS);
    if (! image) return 32;
    result = SaveImage("posterize", image);
    if (result) return result;
#ifdef DEBUG
    printf("Posterize tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    if (! image) return 33;
    image = MotionBlur(image, BLUR_AMOUNT);
    if (! image) return 34;
    result = SaveImage("blur", image);
    if (result) return result;
#ifdef DEBUG
    printf("MotionBlur tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    if (! image) return 35;
    image = Crop(image, CROP_X, CROP_Y, CROP_WIDTH, CROP_HEIGHT);
    if (! image) return 36;
    result = SaveImage("crop", image);
    if (result) return result;
#ifdef DEBUG
    printf("Crop tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    if (! image) return 37;
    image = Resize(image, SMALL_RESIZE_PERCENTAGE);
    if (! image) return 38;
    result = SaveImage("smallresize", image);
    if (result) return result;
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    if (! image) return 39;
    image = Resize(image, BIG_RESIZE_PERCENTAGE);
    if (! image) return 40;
    result = SaveImage("bigresize", image);
    if (result) return result;
#ifdef DEBUG
    printf("Resize tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    if (! image) return 41;
    image = BrightnessAndContrast(image, BRIGHTNESS, CONTRAST);
    if (! image) return 42;
    result = SaveImage("brightnessandcontrast", image);
    if (result) return result;
#ifdef DEBUG
    printf("Brightness and Contrast tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;


    image = LoadImage(fname);
    if (! image) return 43;
    IMAGE *watermark_Image = LoadImage(watermarkImgName);
    if (! watermark_Image) return 44;
    image = Watermark(image, watermark_Image);
    DeleteImage(watermark_Image);
    watermark_Image = NULL;
    if (! image) return 45;
    result = SaveImage("watermark", image);
    if (result) return result;
#ifdef DEBUG
    printf("Watermark tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;
    return 0; /* success! */
}

