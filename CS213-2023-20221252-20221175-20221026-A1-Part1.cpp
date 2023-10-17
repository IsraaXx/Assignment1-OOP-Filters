// FCAI – OOP Programming – 2023 - Assignment
// Program Name: Filters.cpp
// Last Modification Date:	10 October 2023
// Author1 and ID and Group: Israa Mohamed Elsayed  20221252 Email : saramohamed2315@gmail.com
// Author2 and ID and Group: Nada Mohammed Soliman  20221175 Email : nda98990@gmail.com
// Author3 and ID and Group: Amany Mohamed hussein  20221026 Email : amanyhussein133@gmail.com
// Purpose: An image processing (or photo editing) Program ,
// allows you to load an image and apply some changes (Filters) to the image and save it if you want.
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"
using namespace std;
unsigned char image[SIZE][SIZE];
unsigned char image1[SIZE][SIZE];
void BlackWhite();
void InvertImage();
void MergeImage();
void FlipImage(char x);
void RotateImage();
void Darken_Lighten(char y);
bool displayMenu();
void loadImage() {  // to read the image name
    char imageFileName[100];
    cout << "Please enter file name of the image to process:";
    cin >> imageFileName;
    strcat(imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}
void loadImage1() { // load another Image to use it with merge filter
    char imageFileName[100];
    cout << "Enter the source image to merge with file name:";
    cin >> imageFileName;
    strcat(imageFileName, ".bmp");
    readGSBMP(imageFileName, image1);
}
void saveImage() {  // to save the Edited Image by a name you write
    char imageFileName[100];
    cout << "Enter the target image file name:";
    cin >> imageFileName;
    strcat(imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
}
int choice;
int main() {
    cout<<"Welcome User\n";
    loadImage();
    while (true) {
        if (!displayMenu()) {
            break;}
    }
}
bool displayMenu() {
    char flip, Dark_light;
    cout << "Please select the number of filter to apply or 0 to exit: \n";
    cout<< "1-Black & White Filter\n2-Invert Filter\n3-Merge Filter\n4-Flip Image\n5-Rotate Image\n6-Darken and Lighten Image\n7-Save the image to a file\n0-Exit\n";
    cout << "Your Selection :";
    cin >> choice;
    if (choice == 1)
    {
        BlackWhite();
        return true;
    } else if (choice == 2)
    {
        InvertImage();
        return true;
    } else if (choice == 3)
    {
        MergeImage();
        return true;
    } else if (choice == 4)
    {
        cout << "Flip horizontally or vertically ? Enter letter h or v:";
        cin >> flip;
        FlipImage(flip);
        return true;
    } else if (choice == 5)
    {
        RotateImage();
        return true;
    } else if (choice == 6)
    {
        cout << "Do you want to darken or lighten ? Enter letter d or l:";
        cin >> Dark_light;
        Darken_Lighten(Dark_light);
        return true;
    } else if (choice == 7)
    {
        saveImage();
        cout << "Do you want to choose another image? Enter y for yes, n for no:";
        char anotherImage;
        cin >> anotherImage;
        if (anotherImage != 'y' && anotherImage != 'Y') {
            return false;}
        loadImage();
        return true;
    } else if (choice == 0)
    {
        return false;
    }
}
void BlackWhite() {// Author: Israa Mohamed Elsayed
    int sum = 0, ave = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            sum += image[i][j];
        }
    }
    ave += sum / (SIZE * SIZE);
    for (int i = 0; i < SIZE; i++) { //to make the image black&white we get the average level of gray in our image
        for (int j = 0; j < SIZE; j++) { // if the current pixel has value >= the average, so it will be white
            if (image[i][j] >= ave) // and if the value < the average it will be black
                image[i][j] = 255;  // 0 means image is black ,  255 image is white
            else
                image[i][j] = 0;
        }
    }
}
void InvertImage() { // Author: Nada Mohammed Soliman
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
//I will turn every gray pixel to the opposite level of brightness and the image is 255 pixel value so I will subtract the value of every pixel from 255
            image[i][j] = 255 - image[i][j];
        }
    }
}

void FlipImage(char x) { // Author: Israa Mohamed Elsayed
    if (x == 'v' || x == 'V') { // flip vertically
        for (int i = 0; i < SIZE / 2; i++) {//loop to the half of the image vertically half of the rows
            for (int j = 0; j < SIZE; j++) {
                int temp = image[i][j];//temp holds the original value of image[i][j]
                image[i][j] = image[SIZE-1-i][j];//here the current pixel value is replaced with the corresponding pixel value from the opposite side
                image[SIZE-1-i][j] = temp;//here SIZE-1-i represents the corresponding row on the opposite side of the image
            }
        }
    } else if (x == 'h' || x == 'H') { //flip horizontally
        for (int i = 0; i <SIZE; i++) { // loop to the half of the image horizontally half of the columns to swap every side with the other
            for (int j = 0; j < SIZE / 2; j++) {
                int temp = image[i][j]; // temp is made to temporary holds the original value of image[i][j],so when i chane the original value
                image[i][j] = image[i][SIZE-1-j]; // here the current pixel value is replaced with the corresponding pixel value from the opposite side
                image[i][SIZE-1-j] = temp; //here SIZE-1-j represents the corresponding column on the opposite side of the image
                //by using temp the pixel value on the opposite side is replaced with the original value of the current pixel
            }    // at the end we have swapped both side with each-other and image flipped horizontally
        }
    }
}

void RotateImage() { // Author: Nada Mohamed Soliman
    int rotation_angle, times_to_rotate_90;
    auto n = SIZE;
    long long arr[n][n];
    cout << "Enter the rotation_angle (90) , (180) or (360) ? :"; //Get the angle that the image rotate
    cin >> rotation_angle;
    times_to_rotate_90 = rotation_angle / 90;
    while (times_to_rotate_90--) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                arr[i][j] = image[i][j];
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                //*image[i][j]=arr[j][n-1-i];*/ // to rotate the image 90 daraga left
                image[i][j] = arr[n - 1 - j][i];   //to rotate the image 90 daraga right

            }
        }
    }
}

void Darken_Lighten(char y) { // Author: Amany Mohamed Hussein
    if (y == 'd' || y == 'D') { //Darken image
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = image[i][j] /2;  //to make the image darken we need to divide the num of pixel /2 to minmize it to reach to 0
            }
        }
    } else if (y == 'l' || y == 'L') { //Lighten image
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                float Remaining_pixel = (255 - image[i][j]) / 2;
                //{(255 - the num of pixel)/2} we divide /2 because we need to lighten by 50%
                image[i][j] = image[i][j] + Remaining_pixel;
            }
        }
    }
}

void MergeImage() { // Author: Amany Mohamed Hussein
    loadImage1();
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = (image[i][j] + image1[i][j]) / 2;
            //to merge two images we want to load two images and take the average of the pixel from two images and save it in one image.
            //the average=(the num of pixel of image 1 + the num of pixel of image 2 ) / 2.
        }

    }
}