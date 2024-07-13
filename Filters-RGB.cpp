// FCAI – OOP Programming–2023-Assignment Bonus Part
// Program Name: CS213-2023-S1,S2-20221252-20221175-20221026-A1-Bonus.cpp
// Last Modification Date:	19 October 2023
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
unsigned char image[SIZE][SIZE][RGB];
unsigned char image1[SIZE][SIZE][RGB];
void BlackWhite();
void InvertImage();
void MergeImage();
void FlipImage(char x);
void RotateImage();
void Darken_Lighten(char y);
void DetectEdges();
void Blur_Image();
void Shrink_Image(string x);
void Crop_Image(int x ,int y , int l , int w);
void Mirror_Filter(char x);
void Enlarge_Image();
void Shuffle_Image();
void Skew_Image_Up(double angle_degree);
void Skew_Image_Right();
bool displayMenu();
void loadImage() {  // to read the image name
    char imageFileName[100];
    cout << "Please enter file name of the image to process:";
    cin >> imageFileName;
    strcat(imageFileName, ".bmp");
    readRGBBMP(imageFileName, image);
}

void loadImage1() { // load another Image to use it with merge filter
    char imageFileName[100];
    cout << "Enter the source image to merge with file name:";
    cin >> imageFileName;
    strcat(imageFileName, ".bmp");
    readRGBBMP(imageFileName, image1);
}

void saveImage() {  // to save the Edited Image by a name you write
    char imageFileName[100];
    cout << "Enter the target image file name:";
    cin >> imageFileName;
    strcat(imageFileName, ".bmp");
    writeRGBBMP(imageFileName, image);
}

int choice;

int main() {
    cout << "Welcome User\n";
    loadImage();
    while (true) {
        if (!displayMenu()) {
            break;
        }
    }
}

bool displayMenu() {
    char flip, Dark_light;
    cout << "Please select the number of filter to apply or 0 to exit: \n";
    cout<< "1-Black & White Filter\n2-Invert Filter\n3-Merge Filter\n4-Flip Image\n5-Rotate Image\n6-Darken and Lighten Image\n7-Detect Image Edges\n"
               "8-Enlarge Image\n9-Shrink Image\n10-Mirror 1/2 Image\n11-Shuffle Image\n12-Blur Image\n"
               "13-Crop Image\n14-Skew Image Right\n15-Skew Image Up\n16-Save Image to a file\n0-Exit\n";
    cout << "Your Selection :";
    cin >> choice;
    if (choice == 1) {
        BlackWhite();
        return true;
    } else if (choice == 2) {
         InvertImage();
        return true;
    } else if (choice == 3) {
        MergeImage();
        return true;
    } else if (choice == 4) {
        cout << "Flip horizontally or vertically ? Enter letter h or v:";
        cin >> flip;
        FlipImage(flip);
        return true;
    } else if (choice == 5) {
         RotateImage();
        return true;
    } else if (choice == 6) {
        cout << "Do you want to darken or lighten ? Enter letter d or l:";
        cin >> Dark_light;
        Darken_Lighten(Dark_light);
        return true;
    } else if (choice == 7) {
        DetectEdges();
        return true;
    } else if (choice == 8) {
        Enlarge_Image();
        return true;
    } else if (choice == 9) {
        string x;
        cout << "Shrink to (1/2), (1/3) or (1/4) :";
        cin >> x;
        Shrink_Image(x);
        return true;
    } else if (choice == 10) {
        cout << "Mirror (l)eft, (r)ight, (u)pper, (d)own side? Enter the letter:\n";
        char m;
        cin >> m;
        Mirror_Filter(m);
        return true;
    } else if (choice == 11) {
        Shuffle_Image();
        return true;
    } else if (choice == 12) {
        Blur_Image();
        return true;
    } else if (choice == 13) {
        cout << "Please Enter x y position:\n";
        int x, y, l, w;
        cin >> x >> y;
        cout << "Please Enter length and width of the image to keep:\n";
        cin >> l >> w;
        Crop_Image(x, y, l, w);
        return true;
    }
    else if(choice==14){
        Skew_Image_Right();
        return true;
    }
    else if(choice==15)
    {
        cout<<"Please enter degree to skew Up(Vertically):";
        double angle_degree;
        cin>>angle_degree;
        Skew_Image_Up(angle_degree);
        return true;
    }
    else if (choice == 16) {
        saveImage();
        cout << "Do you want to choose another image? Enter y for yes, n for no:";
        char anotherImage;
        cin >> anotherImage;
        if (anotherImage != 'y' && anotherImage != 'Y') {
            return false;
        }
        loadImage();
        return true;
    } else if (choice == 0) {
        return false;
    }
}
void BlackWhite() { // Author: Israa Mohamed Elsayed
    int grayscale;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {//get the average of the pixel of the 3 channels and this is our grayscale color
            grayscale = (image[i][j][0] + image[i][j][1] + image[i][j][2]) / 3;
            for (int k = 0; k < RGB; k++) {
                image[i][j][k] = grayscale; // make every pixel a grayscale
                if (grayscale >= 128) //assume that the average for grayscale is 128
                    image[i][j][k] = 255;//if the gray is >128 so convert it to white
                else
                    image[i][j][k] = 0; // if the current gray is < 128 make it blackm
            }
        }
    }
}

void Crop_Image(int x, int y, int l, int w) { // Author: Israa Mohamed Elsayed
    for (int i = 0; i < SIZE; ++i) { // i want to start crop from x , y position and cut a square of length l , width w
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0;
                 k < RGB; ++k) {// to keep and removing the rest so anything out of this range will be removed
                if (i < y || i > y + l || j < x || j > x + w) // removed = set to white
                    image[i][j][k] = 255;
            }
        }

    }

}

void Darken_Lighten(char y) {   // Author: Amany Mohamed Hussein
    if (y == 'd' || y == 'D') { //Darken image
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < RGB; k++) {
                    image[i][j][k] = image[i][j][k] /
                                     2;  //to make the image darken we need to divide the num of pixel /2 to minmize it to reach to 0
                }
            }
        }
    } else if (y == 'l' || y == 'L') { //Lighten image
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < RGB; k++) {
                    float Remaining_pixel = (255 - image[i][j][k]) / 2;
                    //{(255 - the num of pixel)/2} we divide /2 because we need to lighten by 50%
                    image[i][j][k] = image[i][j][k] + Remaining_pixel;
                }
            }
        }
    }
}

void Mirror_Filter(char x) { // Author: Israa Mohamed Elsayed
    if (x == 'l' || x == 'L') { // want to mirror the left half of the image , so we start from j = size/2
        for (int i = 0; i < SIZE; ++i) { // mirror from the half of columns and put the left side on the right side
            for (int j = (SIZE / 2); j < SIZE; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    image[i][j][k] = image[i][SIZE - 1 - j][k];
                }
            }
        }
    } else if (x == 'r' ||
               x == 'R') { // mirror the right half , this mean we start from 0 as usual and every pixel of the left
        for (int i = 0; i < SIZE; ++i) { // side we put instead of it the pixels of the right side
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    image[i][j][k] = image[i][SIZE - 1 - j][k];
                }
            }
        }
    } else if (x == 'u' || x == 'U') { // mirror the upper side so , it's half of the rows , so we start from i = size/2
        for (int i = (SIZE / 2); i < SIZE; ++i) {//and we replace the down pixels with thw upper ones
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    image[i][j][k] = image[SIZE - 1 - i][j][k];
                }
            }
        }
    } else if (x == 'd' ||
               x == 'D') {// mirror the down side so , we want to replace the upper pixels with the pixels of the
        for (int i = 0; i < SIZE; ++i) { // down side and SIZE-1-i means the corresponding rows on the opposite side
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    image[i][j][k] = image[SIZE - 1 - i][j][k];
                }
            }
        }

    }
}

void MergeImage() { // Author: Amany Mohamed Hussein
    loadImage1();
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; k++) {
                image[i][j][k] = (image[i][j][k] + image1[i][j][k]) / 2;
                //to merge two images we want to load two images and take the average of the pixel from two images and save it in one image.
                //the average=(the num of pixel of image 1 + the num of pixel of image 2 ) / 2.
            }
        }
    }
}

void Blur_Image()   // Author: Amany Mohamed Hussein
{
    for (int time = 0; time < 10; time++) { //Apply filter blur multible times to increase the effect of blur image.
        for (int k = 0; k < RGB; k++)
            for (int i = 1; i < SIZE - 1; i++)
                for (int j = 1; j < SIZE - 1; j++) {
                    image1[i][j][k] = (image[i][j + 1][k] + image[i][j - 1][k] + image[i - 1][j][k] + image[i + 1][j][k]
                                       + image[i - 1][j + 1][k] + image[i - 1][j - 1][k] + image[i + 1][j - 1][k] +
                                       image[i + 1][j + 1][k]) / 8;
                    //to blur image I need to get the average of each pixel around the original pixel and put average on the original pixel.
                }
        if (time != 9)
            for (int k = 0; k < RGB; k++)
                for (int i = 0; i < SIZE; i++)
                    for (int j = 0; j < SIZE; j++) {
                        image[i][j][k] = image1[i][j][k]; // copy the blur image1 in image to save it .

                    }
    }
}

void FlipImage(char x) { // Author: Israa Mohamed Elsayed
    if (x == 'v' || x == 'V') { // flip vertically
        for (int i = 0; i < SIZE / 2; i++) {//loop to the half of the image vertically half of the rows
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < RGB; ++k) {
                    int temp = image[i][j][k];//temp holds the original value of image[i][j]
                    image[i][j][k] = image[SIZE - 1 -
                                           i][j][k];//here the current pixel value is replaced with the corresponding pixel value from the opposite side
                    image[SIZE - 1 - i][j][k] = temp;
                } //here SIZE-1-i represents the corresponding row on the opposite side of the image
            }
        }
    } else if (x == 'h' || x == 'H') { //flip horizontally
        for (int i = 0; i <
                        SIZE; i++) { // loop to the half of the image horizontally half of the columns to swap every side with the other
            for (int j = 0; j < SIZE / 2; j++) {
                for (int k = 0; k < RGB; ++k) {
                    int temp = image[i][j][k]; // temp is made to temporary holds the original value of image[i][j],so when i chane the original value
                    image[i][j][k] = image[i][SIZE - 1 -
                                              j][k]; // here the current pixel value is replaced with the corresponding pixel value from the opposite side
                    image[i][SIZE - 1 - j][k] = temp;
                } //here SIZE-1-j represents the corresponding column on the opposite side of the image
                //by using temp the pixel value on the opposite side is replaced with the original value of the current pixel
            }    // at the end we have swapped both side with each-other and image flipped horizontally
        }
    }
}

void Shrink_Image(string x) // Author: Amany Mohamed Hussein
{
    if (x == "1/2")  //Shrink image to half.
    {
        for (int k = 0; k < RGB; k++) {
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    image1[i][j][k] = 255;  // I need an white image to be a background to the shrinked image
                }
            }
        }
        for (int k = 0; k < RGB; k++) {
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    if ((i * 2) <= 255 && (j * 2) <= 255) {
                        // it loops through the image array and checks if the indices i * 2 and j * 2 are within the bounds of the original image array.
                        image1[i][j][k] = image[i * 2][j *
                                                       2][k];// this reduces the size of the image by a factor of 2 in both dimensions.
                    }
                }
            }
        }
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    image[i][j][k] = 255;
                    image[i][j][k] = image1[i][j][k];
                }
            }
        }
    } else if (x == "1/3") //Shrink image to third.
    {
        for (int k = 0; k < RGB; k++) {
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    image1[i][j][k] = 255;  // I need an white image to be a background to the shrinked image
                }
            }
        }
        for (int k = 0; k < RGB; k++) {
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    if ((i * 3) <= 255 && (j * 3) <= 255) {
                        image1[i][j][k] = image[i * 3][j *
                                                       3][k]; // this reduces the size of the image by a factor of 3 in both dimensions.
                    }
                }
            }
        }
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    image[i][j][k] = 255;
                    image[i][j][k] = image1[i][j][k];
                }
            }
        }
    } else if (x == "1/4") //Shrink image to quarter.
    {
        for (int k = 0; k < RGB; k++) {
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    image1[i][j][k] = 255;  // I need an white image to be a background to the shrinked image
                }
            }
        }
        for (int k = 0; k < RGB; k++) {
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    if ((i * 4) <= 255 && (j * 4) <= 255) {
                        image1[i][j][k] = image[i * 4][j *
                                                       4][k]; // this reduces the size of the image by a factor of 4 in both dimensions.
                    }
                }
            }
        }
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    image[i][j][k] = 255;
                    image[i][j][k] = image1[i][j][k];
                }
            }
        }
    }
}

void DetectEdges() { // Author: Israa Mohamed Elsayed
    BlackWhite(); // call black and white function so make it easy to detect the edges with only black and white edges
    int sumr = 0, sumg = 0, sumb = 0;
    for (int i = 0; i < SIZE - 1; i++) {
        for (int j = 0;
             j < SIZE - 1; j++) {//get the average of the pixel of the 3 channels and this is our grayscale color
            sumr += image[i][j][0]; // red channel
            sumg += image[i][j][1]; // green channel
            sumb += image[i][j][2]; // blue channel
        }
    }
    int aver = sumr / (SIZE * SIZE); // get the average of red channel
    int aveg = sumg / (SIZE * SIZE);// get the average of green channel
    int aveb = sumb / (SIZE * SIZE); // get the average of blue channel
    for (int i = 0; i < SIZE - 1; ++i) {
        for (int j = 0; j < SIZE - 1; ++j) { // compare the average of each channel to the neighbouring pixles
            if ((image[i][j][0] > aver && image[i + 1][j][0] <= aver) ||(image[i][j][0] <= aver && image[i + 1][j][0] > aver) ||
                (image[i][j][1] > aveg && image[i + 1][j][1] <= aveg) ||(image[i][j][1] <= aveg && image[i + 1][j][1] > aveg) ||
                (image[i][j][2] > aveb && image[i + 1][j][2] <= aveb )||(image[i][j][2] <= aveb && image[i + 1][j][2] > aveb))
            {
                image[i][j][0]=0;  // make it =0 then it is an edge
                image[i][j][1]=0;
                image[i][j][2]=0;

            }
                // We get the average of the pixels, so we can check if the current pixel is greater than the next one in next row or
               // the opposite so this will be an edge = 0(black) and if the current pixel is greater than the next in next column or the opposite then
                  // it also an edge , comparing the current with the nearby pixels with the average
            else if((image[i][j][0] > aver && image[i][j+1][0] <= aver ||image[i][j][0] <= aver && image[i][j+1][0] > aver) ||
                    (image[i][j][1] > aveg && image[i][j+1][1] <= aveg ||image[i][j][1] <= aveg && image[i][j+1][1] > aveg) ||
                    (image[i][j][2] > aveb && image[i][j+1][2] <= aveb ||image[i][j][2] <= aveb && image[i][j+1][2] > aveb))
            {
                image[i][j][0]=0;
                image[i][j][1]=0;
                image[i][j][2]=0;

            }
            else if((image[i][j][0] > aver && image[i+1][j+1][0] <= aver ||image[i][j][0] <= aver && image[i+1][j+1][0] > aver) ||
                    (image[i][j][1] > aveg && image[i+1][j+1][1] <= aveg ||image[i][j][1] <= aveg && image[i+1][j+1][1] > aveg) ||
                    (image[i][j][2] > aveb && image[i+1][j+1][2] <= aveb ||image[i][j][2] <= aveb && image[i+1][j+1][2] > aveb))
            {
                image[i][j][0]=0;
                image[i][j][1]=0;
                image[i][j][2]=0;

            }
            else{  // then make it white = no edge
                image[i][j][0]=255;
                image[i][j][1]=255;
                image[i][j][2]=255;
            }
        }
    }
}
void InvertImage() {//Author: Nada Mohammed Soliman Sayed
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            for(int k=0;k<3;k++)
            { // Every pixel will turned to the opposite level value of it by substrat from 255 as the image has 256 pixels
                image[i][j][k]=255-image[i][j][k];
            }


        }
    }
}
void RotateImage() {//Author: Nada Mohammed Soliman Sayed
    int rotation_angle , times_to_rotate_90;
    auto n=SIZE;
    long long arr[n][n][3];
    cout<<"Enter the rotation_angle: ";
    cin>>rotation_angle;
    times_to_rotate_90=rotation_angle/90;
    while(times_to_rotate_90--)
    {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                for(int k=0;k<RGB;k++){
                    arr[i][j][k]=image[i][j][k];
                }
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                for(int k=0;k<RGB;k++){
                    //image[i][j][k]=arr[j][n-1-i][k]; to rotate left
                    image[i][j][k]=arr[n-1-j][i][k]; //to rotate right

                }
            }
        }
    }
}
void Enlarge_Image() {//Author: Nada Mohammed Soliman Sayed
    auto n=SIZE;
    int arr1[n/2][n/2][RGB],arr2[n/2][n/2][RGB],arr3[n/2][n/2][RGB],arr4[n/2][n/2][RGB],number_of_quarter;
    cout<<"Enter the number of quarter of the image: ";
    cin>>number_of_quarter;
    /*Here I will divide the image into four quarters
    and copy the pixel values from the image*/
    for (int i = 0; i <n/2; i++) {
        for (int j = 0; j<n/2; j++) {
            for(int k=0;k<3;k++){
                arr1[i][j][k]=image[i][j][k];
                arr2[i][j][k]=image[i][j+(n/2)][k];
                arr3[i][j][k]=image[i+(n/2)][j][k];
                arr4[i][j][k]=image[i+(n/2)][j+(n/2)][k]; /*n/2=quarter_width=quarter_height*/
            }
        }
    }
    if(number_of_quarter==1)
    {
        for (int i = 0; i <n; i++) {
            for (int j =0; j<n; j++) {
                for(int k=0;k<3;k++){
                    image[i][j][k]=arr1[i/2][j/2][k];
                }
            }
        }
    }
    else if(number_of_quarter==2)
    {
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                for(int k=0;k<3;k++){
                    image[i][j][k]=arr2[i/2][j/2][k];
                }
            }
        }

    }
    else if(number_of_quarter==3)
    {
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                for(int k=0;k<3;k++){
                    image[i][j][k]=arr3[i/2][j/2][k];
                }
            }
        }

    }
    else if(number_of_quarter==4)
    {
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                for(int k=0;k<3;k++){
                    image[i][j][k]=arr4[i/2][j/2][k];
                }
            }
        }

    }
}
void Shuffle_Image() {//Author: Nada Mohammed Soliman Sayed
    auto n=SIZE;
    int arr1[n/2][n/2][RGB],arr2[n/2][n/2][3],arr3[n/2][n/2][3],arr4[n/2][n/2][3],number_of_quarter;
    /*Here I will divide the image into four quarters
    and copy the pixel values from the image*/
    for (int i = 0; i <n/2; i++) {
        for (int j = 0; j<n/2; j++) {
            for(int k=0;k<3;k++){
                arr1[i][j][k]=image[i][j][k];
                arr2[i][j][k]=image[i][j+(n/2)][k];
                arr3[i][j][k]=image[i+(n/2)][j][k];
                arr4[i][j][k]=image[i+(n/2)][j+(n/2)][k]; /*n/2=quarter_width=quarter_height*/
            }
        }
    }
    cout<<"Enter the order of the quarters that you want: ";
    int quarter1,quarter2,quarter3,quarter4;
    cin>>quarter1>>quarter2>>quarter3>>quarter4;
/*Make the quarter1 of image as user want by copying the pixel in this
quarter to the first quarter */
    for (int i = 0; i <n/2; i++) {
        for (int j = 0; j<n/2; j++) {
            for(int k=0;k<3;k++){
                if(quarter1==1)
                    image[i][j][k]=arr1[i][j][k];
                else if(quarter1==2)
                    image[i][j][k]=arr2[i][j][k];
                else if(quarter1==3)
                    image[i][j][k]=arr3[i][j][k];
                else if(quarter1==4)
                {
                    image[i][j][k]=arr4[i][j][k];
                }
            }
        }
    }
    /*Make the quarter2 of image as user want by copying the pixel in this
  quarter to the second quarter which its column start from j+quarter_width
   and n/2=quarter_width */
    for (int i = 0; i <n/2; i++) {
        for (int j = 0; j<n/2; j++) {
            for(int k=0;k<3;k++){
                if(quarter2==1)
                    image[i][j+(n/2)][k]=arr1[i][j][k];
                else if(quarter2==2)
                    image[i][j+(n/2)][k]=arr2[i][j][k];
                else if(quarter2==3)
                    image[i][j+(n/2)][k]=arr3[i][j][k];
                else if(quarter2==4)
                {
                    image[i][j+(n/2)][k]=arr4[i][j][k];
                }
            }
        }
    }
    /*Make the quarter3 of image as user want by copying the pixel in this
 quarter to the third quarter which its row start from quarter_height+i and
 i strat from zero to the size of quarter the user want to copy  */
    for (int i = 0; i <n/2; i++) {
        for (int j = 0; j<n/2; j++) {
            for(int k=0;k<3;k++){
                if(quarter3==1)
                    image[i+(n/2)][j][k]=arr1[i][j][k];
                else if(quarter3==2)
                    image[i+(n/2)][j][k]=arr2[i][j][k];
                else if(quarter3==3)
                    image[i+(n/2)][j][k]=arr3[i][j][k];
                else if(quarter3==4)
                {
                    image[i+(n/2)][j][k]=arr4[i][j][k];
                }
            }
        }
    }
    for (int i = 0; i <n/2; i++) {
        for (int j = 0; j<n/2; j++) {
            for(int k=0;k<3;k++){
                if(quarter4==1)
                    image[i+(n/2)][j+(n/2)][k]=arr1[i][j][k];
                else if(quarter4==2)
                    image[i+(n/2)][j+(n/2)][k]=arr2[i][j][k];
                else if(quarter4==3)
                    image[i+(n/2)][j+(n/2)][k]=arr3[i][j][k];
                else if(quarter4==4)
                {
                    image[i+(n/2)][j+(n/2)][k]=arr4[i][j][k];
                }
            }
        }
    }
}
void Skew_Image_Right() {//Author: Nada Mohammed Soliman Sayed
    double skew_angle_degree;
    cout<<"Enter skew angle degree: ";
    cin>>skew_angle_degree;
    /*Substract the angle from 90 to get the inner angle*/
    skew_angle_degree=90-skew_angle_degree;
    /*This law to convert the angle to radian as I will get tan(angle)*/
    double skew_angle_radian=skew_angle_degree*3.14159265359 /180.0;
    double x=256/(1+(1/tan(skew_angle_radian)));
    /*move is to get the percentage that image will skew from my base and the base =SIZE=256*/
    double step=SIZE-x;
    double move=step/SIZE;
    int temp [SIZE][SIZE][3] ;
    int img2[SIZE][SIZE][3];
    for(int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
        {
            for(int k=0;k<3;k++){
                /*Here I will copy each pixel in the original image to temp*/
                temp[i][j][k]=image[i][j][k];
            }
        }
    }
    for(int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
        {
            for(int k=0;k<3;k++){
                /*Here I will make the original image white and the img2 white to make the ground of my image white as user want*/
                image[i][j][k]=255;
                img2[i][j][k]=255;
            }
        }
    }
    for(int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
        {
            for(int k=0;k<3;k++){
                /*Here I will shrink the original image firstly and use the temp that has original pixels*/
                image[i][(j*((int)x)/SIZE)][k]=temp[i][j][k];
            }
        }
    }
    for(int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
        {
            for(int k=0;k<3;k++){
                /*copy pixel from shrink image to the img2 starting from j+step which step is the base of shrinked image and reduce it recording to my move */
                img2[i][j+(int)step][k]=image[i][j][k];
            }
        }
        step-=move;
    }
    for(int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
        {
            for(int k=0;k<3;k++){
                /* copy each pixel in the img2 to in image as it is what will appear to the user*/
                image[i][j][k]=img2[i][j][k];
            }
        }
    }

}
void Skew_Image_Up(double angle_degree) {    // Author: Amany Mohamed Hussein
    angle_degree = 90 - angle_degree;//Substract the angle from 90 to get the inner angle
    double angle_radian = (angle_degree* 22) /( 180 * 7 );//convert the angle to radian to get tan(angle)
    double x=256/(1+tan(angle_radian));//move is to get the percentage that image will skew from my base = 256
    double step=SIZE-x;
    double move=step/SIZE;
    unsigned char temp[SIZE][SIZE][RGB] ;
    unsigned char image2[SIZE][SIZE][RGB];
    for(int i=0;i<SIZE;i++){
        for(int j=0 ; j<SIZE ; j++){
            for(int k=0 ; k<RGB ; k++){
                //Here I will copy each pixel in the original image to temp
                temp[i][j][k]=image[i][j][k];
            }
        }
    }
    for(int i=0 ; i<SIZE ; i++){
        for(int  j=0 ;j<SIZE; j++){
            for(int k=0 ; k<RGB ; k++){
                image[i][j][k]=255;  //to make the original image white and the image2 white to make the ground of my image white as user want
                image2[i][j][k]=255;
            }
        }
    }
    for(int i=0 ; i<SIZE ; i++) {
        for(int j=0 ; j<SIZE ; j++){
            for(int k=0 ; k<RGB ; k++){
                //Here I will shrink the original image firstly and use the temp that has original pixels
                image[(j*((int)x)/SIZE)][i][k]=temp[j][i][k];//I swaped between i,j to be able to skew image up (vertical)
                //because it here consider j as rows and i as columns
            }
        }
    }
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            for(int k=0;k<3;k++){
                //copy pixel from shrink image to the image2 starting from j+step which step is the base of shrinked image and reduce it according to move
                image2[j+(int)step][i][k]=image[j][i][k];
            }
        }
        step-=move;
    }
    for(int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
        {
            for(int k=0;k<3;k++){
                // copy each pixel in the skewed image2 in image to save it .
                image[i][j][k]=image2[i][j][k];
            }
        }
    }

}
