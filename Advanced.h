#ifndef ADVANCED_H_INCLUDED_
#define ADVANCED_H_INCLUDED_

#include "Constants.h"
#include "Image.h"

/* add noise to an image */
IMAGE *AddNoise(IMAGE *image, int n);

/* sharpen the image */
IMAGE *Sharpen (IMAGE *image);

/* posterize the image */
IMAGE *Posterize (IMAGE *image, unsigned int rbits, unsigned int gbits, unsigned int bbits);

/* motion blur */
IMAGE *MotionBlur(IMAGE *image, int BlurAmount);

/*Crop the image*/
IMAGE *Crop(IMAGE *image, unsigned int x, unsigned int y, unsigned int W, unsigned int H);

/*Crop the image*/
IMAGE *Crop(IMAGE *image, unsigned int x, unsigned int y, unsigned int W, unsigned int H);

/*Resize the image*/
IMAGE *Resize(IMAGE *image, int percentage);

/*Brightness and Contrast*/
IMAGE *BrightnessAndContrast(IMAGE *image, int brightness, int contrast);

/*Watermark the image*/
IMAGE *Watermark(IMAGE *image, const IMAGE *watermark_image);
#endif /* ADVANCED_H_INCLUDED_ */

/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */

