/*********************************************************************/
/* PhotoLab.c: homework assignment #3, for EECS 22,  Fall 2017       */
/*                                                                   */
/* Author: Mina Moghadam                                                */
/* Date:   11/8/2017                                                */
/*                                                                   */
/* Comments: */
/*                                                                   */
/* Please use this template to submit your hw3.                      */
/*********************************************************************/

#include <stdio.h>
#include <string.h>

#include "DIPs.h"
#include "Advanced.h"
#include "FileIO.h"
#include "Constants.h"
#include "Image.h"
#include "Test.h"

/*** function declarations ***/

/* print a menu */
void PrintMenu();

int main()
{
        IMAGE *rc ;


#ifdef DEBUG
        AutoTest();
        rc = NULL;

#else

    int option;                 /* user input option */
    char fname[SLEN];           /* input file name */
    char colorOption[SLEN];
        rc = 0 ;
        PrintMenu();
    printf("Please make your choice: ");
    scanf("%d", &option);
    IMAGE *image;
    image = NULL;
        /* ColorFilter() parameters */
    int target_r, target_g, target_b, threshold;
    double factor_r, factor_g, factor_b;

        /* AddBorder() parameter */
    int border_width;
    unsigned char rbits, gbits, bbits;

        /* Noise() parameter */
        int n;

        /* MotionBlur() parameter */
        int motion_amount;

        /*Crop() parameter*/
        int cropx, cropy, cropw, croph;

        /*resize() parameter*/
        int resizeper;

        /*BrightnessAndContrast() parameter*/
        int bright, contra;

        /*Watermark() parameter*/
        const char watermarkImgName[SLEN] = "watermark_template";
        IMAGE *watermark_Image = LoadImage(watermarkImgName);

        while (option != EXIT) {
                if (option == 1) {
            printf("Please input the file name to load: ");
            scanf("%s", fname);
            image = LoadImage(fname);
                }

                /* menu item 2 - 14 requires image is loaded first */
        else if (option >= 2 && option <= 18) {
            if (image == NULL)   {
                printf("No image to process!\n");
            }
            /* now image is loaded */
            else {

                switch (option) {
                    case 2:
                        printf("Please input the file name to save: ");
                        scanf("%s", fname);
                        SaveImage(fname, image);
                        break;
                    case 3:
                        image = BlackNWhite(image);
                        printf("\"Black & White\" operation is done!\n");
                        break;
                    case 4:
                        image = Negative(image);
                        printf("\"Negative\" operation is done!\n");
                        break;
                    case 5:
                        printf("Enter Red   component for the target color: ");
                        scanf("%d", &target_r);
                        printf("Enter Green component for the target color: ");
                        scanf("%d", &target_g);
                        printf("Enter Blue  component for the target color: ");
                        scanf("%d", &target_b);
                        printf("Enter threshold for the color difference: ");
                        scanf("%d", &threshold);
                        printf("Enter value for Red component in the target color: ");
                        scanf("%lf", &factor_r);
                        printf("Enter value for Green component in the target color: ");
                        scanf("%lf", &factor_g);
                        printf("Enter value for Blue  component in the target color: ");
                        scanf("%lf", &factor_b);

                        ColorFilter(image, target_r, target_g, target_b, threshold, factor_r, factor_g, factor_b);
                        printf("\"Color Filter\" operation is done!\n");
                        break;
                    case 6:
                        Edge(image);
                        printf("\"Edge\" operation is done!\n");
                        break;
                    case 7:
                        Shuffle(image);
                        printf("\"Shuffle\" operation is done!\n");
                        break;
                                        case 8:
                        VFlip(image);
                        printf("\"VFlip\" operation is done!\n");
                        break;
                                        case 9:
                        VMirror(image);
                        printf("\"Vertically Mirror\" operation is done!\n");
                        break;
                    case 10:
                        printf("Enter border width:");
                        scanf("%d", &border_width);
                        printf("Available border colors : black, white, red, green, blue, yellow, cyan, pink, orange\n");
                        printf("Select border color from the options: ");
                        scanf("%s",colorOption);
                        AddBorder(image, colorOption, border_width);
                        printf("\"Border\" operation is done!\n");
                        break;
                    case 11:
                        printf("Please input noise percentage: ");
                        scanf("%d", &n);
                        AddNoise(image, n);
                        printf("\"Noise\" operation is done!\n");
                        break;
                    case 12:
                        Sharpen(image);
                        printf("\"Sharpen\" operation is done!\n");
                        break;
                    case 13:
                        printf("Enter the number of posterization bits for R chennel (1 to 8):");
                        scanf("%hhu", &rbits);
                        printf("Enter the number of posterization bits for G chennel (1 to 8):");
                        scanf("%hhu", &gbits);
                        printf("Enter the number of posterization bits for B chennel (1 to 8):");
                        scanf("%hhu", &bbits);
                        Posterize(image, rbits, gbits, bbits);
                        printf("\"Posterize\" operation is done!\n");
                        break;
                    case 14:
                        printf("Please input motion blur amount: ");
                        scanf("%d", &motion_amount);
                        MotionBlur(image, motion_amount);
                        printf("\"Motion Blur\" operation is done!\n");
                        break;

                    case 15:
                        printf("Please input the x value: ");
                        scanf("%d", &cropx);
                        printf("Please input the y value: ");
                        scanf("%d", &cropy);
                        printf("Please input the width: ");
                        scanf("%d", &cropw);
                        printf("Please input the height: ");
                        scanf("%d", &croph);
                        Crop(image, cropx, cropy, cropw, croph);
                        printf("\"Crop\" operation is done!\n");
                        break;

                    case 16:
                        printf("Please input the resizing percentage (integer between 1 - 500): ");
                        scanf("%d", &resizeper);
                        Resize(image, resizeper);
                        printf("\"Resizing the image\" operation is done!\n");
                        break;

                    case 17:
                        while(1){
                                printf("Please input the brightness level (integer between -255 to 255): ");
                                scanf("%d", &bright);
                                if(bright > -255 && bright < 255){break;}
                        }
                        while(1){
                                printf("Please input the contrast level (integer betwee -255 to 255): ");
                                scanf("%d", &contra);
                                if(contra > -255 && contra < 255){break;}
                        }
                        BrightnessAndContrast(image, bright, contra);
                        printf("\"Brightness and Contrast Adjustment\" operation is done!\n");
                        break;

                    case 18:
                        Watermark(image, watermark_Image);
                        break;

                    case 19:
                        AutoTest();
                        rc = SUCCESS;   /* set returned code SUCCESS, since image is loaded */
                        break;

                    default:
                        break;

                                }
                        }
                }

        else if (option == 19) {
            AutoTest();
            rc = SUCCESS;       /* set returned code SUCCESS, since image is loaded */
            if(rc != SUCCESS){printf("AutoTest failed, error code RC.\n");}
            else{printf("AutoTest finished successfully."); }
        }
        else {
            printf("Invalid selection!\n");
        }

                /* Process finished, waiting for another input */
        PrintMenu();
        printf("Please make your choice: ");
        scanf("%d", &option);
        }
    printf("You exit the program.\n");
#endif

        return 0;
}


/*******************************************/
/* Function implementations should go here */
/*******************************************/

/* Menu */
void PrintMenu() {
    printf("\n----------------------------\n");
    printf(" 1: Load a PPM image\n");
    printf(" 2: Save an image in PPM and JPEG format\n");
    printf(" 3: Change a color image to Black & White\n");
    printf(" 4: Make a negative of an image\n");
    printf(" 5: Color filter an image\n");
    printf(" 6: Sketch the edge of an image\n");
    printf(" 7: Shuffle an image\n");
    printf(" 8: Flip an image vertically\n");
    printf(" 9: Mirror an image vertically\n");
    printf("10: Add border to an image\n");
    printf("11: Add Noise to an image\n");
    printf("12: Sharpen an image\n");
    printf("13: Posterize an image\n");
    printf("14: Add Motion Blur to an image\n");
    printf("15: Crop\n");
    printf("16: Resize\n");
    printf("17: Brightness and Contrast\n");
    printf("18: Watermark\n");
    printf("19: Test all functions\n");
    printf("20: Exit\n");
}


/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */

