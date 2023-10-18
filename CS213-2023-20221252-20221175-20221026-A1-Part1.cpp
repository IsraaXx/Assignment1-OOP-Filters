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
void DetectEdges();
void Blur_Image();
void Shrink_Image(string x);
void Crop_Image(int x ,int y , int l , int w);
void Mirror_Filter(char x);
void Enlarge_Image();
void Shufffel_Image();
void Skew_Image_Right();
void Skew_Image_Up(double angle_degree);
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
    cout<< "1-Black & White Filter\n2-Invert Filter\n3-Merge Filter\n4-Flip Image\n5-Rotate Image\n6-Darken and Lighten Image\n7-Detect Image Edges\n"
           "8-Enlarge Image\n9-Shrink Image\n10-Mirror 1/2 Image\n11-Shuffle Image\n12-Blur Image\n"
           "13-Crop Image\n14-Skew Image Right\n15-Skew Image Up\n16-Save the image to a file\n0-Exit\n";
    cout << "Your Selection :";
    cin >> choice;
    if (choice == 1)
    {
        BlackWhite();
        return true;
    } 
    else if (choice == 2)
    {
        InvertImage();
        return true;
    } 
    else if (choice == 3)
    {
        MergeImage();
        return true;
    } 
    else if (choice == 4)
    {
        cout << "Flip horizontally or vertically ? Enter letter h or v:";
        cin >> flip;
        FlipImage(flip);
        return true;
    } 
    else if (choice == 5)
    {
        RotateImage();
        return true;
    } 
    else if (choice == 6)
    {
        cout << "Do you want to darken or lighten ? Enter letter d or l:";
        cin >> Dark_light;
        Darken_Lighten(Dark_light);
        return true;
    } 
    else if (choice==7)
    {
         DetectEdges();
        return true;
    }
    else if (choice==8)
    {
        Enlarge_Image();
        return true;
    }
    else if(choice==9)
    {
        string x;
        cout<<"Shrink to (1/2), (1/3) or (1/4) :";
        cin>>x;
        Shrink_Image(x);
        return true;
    }
    else if(choice==10)
    {
       cout<<"Mirror (l)eft, (r)ight, (u)pper, (d)own side? Enter the letter:\n";
       char m;
       cin>>m;
       Mirror_Filter(m);
        return true;
    }
    else if(choice==11)
    {
        Shufffel_Image();
        return true;
    }
    else if(choice==12)
    {
        Blur_Image();
        return true;
    }
    else if(choice==13)
    {
        cout<<"Please Enter x y position:\n";
        int x ,y ,l ,w;
        cin>>x>>y;
        cout<<"Please Enter length and width of the image to keep:\n";
        cin>>l>>w;
        Crop_Image(x,y,l,w);
        return true;
    }
    else if(choice==14)
    {
        //cout<<"Please enter degree to skew Right(Horizontally):";
        //Skew_Image_Right();
        //return true;
    }
    else if(choice==15)
    {
        cout<<"Please enter degree to skew Up(Vertically):";
        double angle_degree;
        cin>>angle_degree;
       Skew_Image_Up(angle_degree);
       return true;
    }
    else if (choice == 16)
    {
        saveImage();
        cout << "Do you want to choose another image? Enter y for yes, n for no:";
        char anotherImage;
        cin >> anotherImage;
        if (anotherImage != 'y' && anotherImage != 'Y') {
            return false;}
        loadImage();
        return true;
    } 

    else if (choice == 0)
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

void DetectEdges() { // Author: Israa Mohamed Elsayed
    int sum =0 ;
    for (int i = 0; i < SIZE; ++i){
        for (int j = 0; j < SIZE; ++j) {
            sum+=image[i][j];
        }
    } // We get the average of the pixels, so we can check if the current pixel is greater than the next one in next row or
    // the opposite so this will be an edge = 0(black) and if the current pixel is greater than the next in next column or the opposite then
    // it also an edge , comparing the current with the nearby pixels with the average
    int ave = sum/(SIZE*SIZE);
    for (int i = 0; i < SIZE-1 ; ++i) {
        for (int j = 0; j < SIZE-1; ++j) {
            if(image[i][j]>ave && image[i+1][j]<=ave || image[i][j]<=ave&& image[i+1][j]>ave)
                image[i][j]=0;
            else if(image[i][j]>ave && image[i][j+1]<=ave || image[i][j]<=ave&& image[i][j+1]>ave)
                image[i][j]=0;
            else if(image[i][j]>ave && image[i+1][j+1]<=ave || image[i][j]<=ave&& image[i+1][j+1]>ave)
                image[i][j]=0;
            else
                image[i][j]=255;
        }

    }
}
void Blur_Image(){ // Author: Amany Mohamed Hussein
    for(int time = 0 ;time < 10 ;time++){ //Apply filter blur multible times to increase the effect of blur image.
        for (int i = 1 ; i < SIZE-1; i++)
            for (int j = 1; j < SIZE-1; j++)
            {
                image1[i][j]=(image[i][j+1] + image[i][j-1]+ image[i-1][j] + image[i+1][j]
                              + image[i-1][j+1]+ image[i-1][j-1]+ image[i+1][j-1]+ image[i+1][j+1] )/8 ;
                //to blur image I need to get the average of each pixel around the original pixel and put average on the original pixel.
            }
        if(time != 9)
            for (int i = 0 ; i < SIZE; i++)
                for (int j= 0 ; j < SIZE; j++)
                    image[i][j]=image1[i][j]; // copy the blur image1 in image to save it .

    }
}
void Shrink_Image(string x){ // Author: Amany Mohamed Hussein
    if(x=="1/2")  //Shrink image to half.
    {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                image1[i][j] = 255;  // I need a white image to be a background to the shrinked image
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if ((i * 2) <= 255 && (j * 2) <= 255) {
                    // it loops through the image array and checks if the indices i * 2 and j * 2 are within the bounds of the original image array.
                    image1[i][j] = image[i * 2][j * 2];// this reduces the size of the image by a factor of 2 in both dimensions.

                }
            }
        }
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image[i][j]=255;
                image[i][j]=image1[i][j];
            }

        }
    }
    else if(x=="1/3") //Shrink image to third.
        {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                image1[i][j] = 255;  // I need a white image to be a background to the shrinked image
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if ((i * 3) <= 255 && (j * 3) <= 255) {
                    image1[i][j] = image[i * 3][j * 3]; // this reduces the size of the image by a factor of 3 in both dimensions.
                }
            }
        }
            for (int i = 0; i < SIZE; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    image[i][j]=255;
                    image[i][j]=image1[i][j];
                }

            }
    }
    else if(x=="1/4") //Shrink image to quarter.
        {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                image1[i][j] = 255;  // I need a white image to be a background to the shrinked image
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if ((i * 4) <= 255 && (j * 4) <= 255) {
                    image1[i][j] = image[i * 4][j * 4]; // this reduces the size of the image by a factor of 4 in both dimensions.
                }
            }
        }
            for (int i = 0; i < SIZE; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    image[i][j]=255;
                    image[i][j]=image1[i][j];
                }
            }
        }
}
void Crop_Image(int x,int y,int l,int w){ // Author: Israa Mohamed Elsayed
    for (int i = 0; i < SIZE; ++i) { // i want to start crop from x , y position and cut a square of length l , width w
        for (int j = 0; j < SIZE; ++j) { // to keep and removing the rest so anything out of this range will be removed
           if(i<y||i>y+l || j<x ||j>x+w) // removed = set to white
               image[i][j]=255;
        }

    }

}
void Mirror_Filter(char x){ // Author: Israa Mohamed Elsayed
    if(x=='l'||x=='L'){ // want to mirror the left half of the image , so we start from j = size/2
        for (int i = 0; i < SIZE; ++i) { // mirror from the half of columns and put the left side on the right side
            for (int j = (SIZE/2); j < SIZE; ++j) {
                image[i][j]=image[i][SIZE-1-j];
            }
        }
    }
    else if (x=='r'||x=='R'){ // mirror the right half , this mean we start from 0 as usual and every pixel of the left
        for (int i = 0; i < SIZE; ++i) { // side we put instead of it the pixels of the right side
            for (int j = 0; j < SIZE; ++j) {
                image[i][j]=image[i][SIZE-1-j];
            }
        }
    }
    else if(x=='u'||x=='U'){ // mirror the upper side so , it's half of the rows , so we start from i = size/2
        for (int i = (SIZE/2); i < SIZE; ++i) {//and we replace the down pixels with thw upper ones
            for (int j = 0; j < SIZE; ++j) {
                image[i][j]=image[SIZE-1-i][j];
            }
        }
    }
    else if(x =='d'|| x=='D'){// mirror the down side so , we want to replace the upper pixels with the pixels of the
        for (int i = 0 ; i < SIZE; ++i) { // down side and SIZE-1-i means the corresponding rows on the opposite side
            for (int j = 0; j < SIZE; ++j) {
                image[i][j]=image[SIZE-1-i][j];
            }
        }

    }
}
void Enlarge_Image() { //Author: Nada Mohamed Soliman
    auto n=SIZE;
    int arr1[n/2][n/2],arr2[n/2][n/2],arr3[n/2][n/2],arr4[n/2][n/2],number_of_quarter;
    cout<<"Enter the number of quarter of the image: ";
    cin>>number_of_quarter;
    /*Here I will divide the image into four quarters
    and copy the pixel values from the image*/
    for (int i = 0; i <n/2; i++) {
        for (int j = 0; j<n/2; j++) {
            arr1[i][j]=image[i][j];
            arr2[i][j]=image[i][j+(n/2)];
            arr3[i][j]=image[i+(n/2)][j];
            arr4[i][j]=image[i+(n/2)][j+(n/2)]; /*n/2=quarter_width=quarter_height*/
        }
    }
    /*choose the quarter the user want and enlarge it in the original image*/
    if(number_of_quarter==1)
    {
        for (int i = 0; i <n; i++) {
            for (int j =0; j<n; j++) {
                /*to each pixel I will load four of it in the original image
                 to enlarge any of four quarters */
                image[i][j]=arr1[i/2][j/2];
            }
        }
    }
    else if(number_of_quarter==2)
    {
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                image[i][j]=arr2[i/2][j/2];
            }
        }

    }
    else if(number_of_quarter==3)
    {
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                image[i][j]=arr3[i/2][j/2];
            }
        }

    }
    else if(number_of_quarter==4)
    {
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                image[i][j]=arr4[i/2][j/2];
            }
        }

    }
}
void Shufffel_Image() { // Author: Nada Mohamed Soliman
    auto n=SIZE;
    int arr1[n/2][n/2],arr2[n/2][n/2],arr3[n/2][n/2],arr4[n/2][n/2],number_of_quarter;
    /*Here I will divide the image into four quarters
    and copy the pixel values from the image*/
    for (int i = 0; i <n/2; i++) {
        for (int j = 0; j<n/2; j++) {
            arr1[i][j]=image[i][j];
            arr2[i][j]=image[i][j+(n/2)];
            arr3[i][j]=image[i+(n/2)][j];
            arr4[i][j]=image[i+(n/2)][j+(n/2)]; /*n/2=quarter_width=quarter_height*/
        }
    }
    cout<<"Enter the order of the quarters that you want: ";
    int quarter1,quarter2,quarter3,quarter4;
    cin>>quarter1>>quarter2>>quarter3>>quarter4;
/*Make the quarter1 of image as user want by copying the pixel in this
quarter to the first quarter */
    for (int i = 0; i <n/2; i++) {
        for (int j = 0; j<n/2; j++) {
            if(quarter1==1)
                image[i][j]=arr1[i][j];
            else if(quarter1==2)
                image[i][j]=arr2[i][j];
            else if(quarter1==3)
                image[i][j]=arr3[i][j];
            else if(quarter1==4)
            {
                image[i][j]=arr4[i][j];
            }
        }
    }
    /*Make the quarter2 of image as user want by copying the pixel in this
  quarter to the second quarter which its column start from j+quarter_width
   and n/2=quarter_width */
    for (int i = 0; i <n/2; i++) {
        for (int j = 0; j<n/2; j++) {
            if(quarter2==1)
                image[i][j+(n/2)]=arr1[i][j];
            else if(quarter2==2)
                image[i][j+(n/2)]=arr2[i][j];
            else if(quarter2==3)
                image[i][j+(n/2)]=arr3[i][j];
            else if(quarter2==4)
            {
                image[i][j+(n/2)]=arr4[i][j];
            }
        }
    }
    /*Make the quarter3 of image as user want by copying the pixel in this
 quarter to the third quarter which its row start from quarter_height+i and
 I strat from zero to the size of quarter the user want to copy  */
    for (int i = 0; i <n/2; i++) {
        for (int j = 0; j<n/2; j++) {
            if(quarter3==1)
                image[i+(n/2)][j]=arr1[i][j];
            else if(quarter3==2)
                image[i+(n/2)][j]=arr2[i][j];
            else if(quarter3==3)
                image[i+(n/2)][j]=arr3[i][j];
            else if(quarter3==4)
            {
                image[i+(n/2)][j]=arr4[i][j];
            }
        }
    }
    for (int i = 0; i <n/2; i++) {
        for (int j = 0; j<n/2; j++) {
            if(quarter4==1)
                image[i+(n/2)][j+(n/2)]=arr1[i][j];
            else if(quarter4==2)
                image[i+(n/2)][j+(n/2)]=arr2[i][j];
            else if(quarter4==3)
                image[i+(n/2)][j+(n/2)]=arr3[i][j];
            else if(quarter4==4)
            {
                image[i+(n/2)][j+(n/2)]=arr4[i][j];
            }
        }
    }
}
void Skew_Image_Up(double angle_degree) {    // Author: Amany Mohamed Hussein
angle_degree = 90 - angle_degree;  //Substract the angle from 90 to get the inner angle
double angle_radian = (angle_degree* 22) /( 180 * 7 );  //convert the angle to radian to get tan(angle)
double x=256/(1+tan(angle_radian));  //move is to get the percentage that image will skew from my base = 256
double step=SIZE-x;
double move=step/SIZE;
unsigned char temp[SIZE][SIZE] ;
unsigned char image2[SIZE][SIZE];
for(int i=0;i<SIZE;i++){
         for(int j=0;j<SIZE;j++){
            //Here I will copy each pixel in the original image to temp
            temp[i][j]=image[i][j];
         }
     }
     for(int i=0;i<SIZE;i++){
         for(int j=0;j<SIZE;j++){
           image[i][j]=255;  //to make the original image white and the image2 white to make the ground of my image white as user want
           image2[i][j]=255;
         }
    }
    for(int i=0;i<SIZE;i++) {
         for(int j=0;j<SIZE;j++){
        //Here I will shrink the original image firstly and use the temp that has original pixels
            image[(j*((int)x)/SIZE)][i]=temp[j][i];//I swaped between i,j to be able to skew image right (vertical)
                                                   //because it here consider j as rows and i as columns 
         }
     }
     for(int i=0;i<SIZE;i++){
         for(int j=0;j<SIZE;j++){
             //copy pixel from shrink image to the image2 starting from j+step which step is the base of shrinked image and reduce it according to move
            image2[j+(int)step][i]=image[j][i];
         }
         step-=move;
     }
     for(int i=0;i<SIZE;i++)
     {
         for(int j=0;j<SIZE;j++)
         {
            // copy each pixel in the skewed image2 in image to save it .
             image[i][j]=image2[i][j];
         }
     }
}
