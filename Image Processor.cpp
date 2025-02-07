// FCAI CS-213 Fall 2023 Assignment 1
// Program: "Image Filter"
// Purpose: Apply 15 different image filter on 256 pixel grayscale and color bmp images

// Authors:
// Name: Ashraf ALaa
// ID: 20220063
// E-mail: theengashraf@gmail.com

// Name:
// ID: 20220045
// E-mail: ahmadhemdan280@gmail.com

// Name:
// ID: 20220227
// E-mail: omarmohamed012330@gmail.com



#include "bmplib.cpp"
#include "GsFunctions.cpp"
#include "RgbFunctions.cpp"

using namespace std;


int main() {

    while (true){

        // select the mood of the program
        cout<<"0: Gray\n1: Colored\n";
        bool color ; cin>>color;

        // reject invalid input
        while(color !=0 && color !=1){
            cout<<"Invalid choice, Try again\n"; cin>>color;
        }


        // load the image into the matrix
        color ? cLoadImage():loadImage();

        // keep editing the image until the user exit
        bool editing = true;
        while (editing) {

            //show the menu of available filters
            cout << """Please select a filter to apply or 0 to exit:\n"
                    "1- Black & White Filter\n"
                    "2- Invert Filter\n"
                    "3- Merge Filter \n"
                    "4- Flip Image\n"
                    "5- Rotate Image\n"
                    "6- Darken and Lighten Image\n"
                    "7- Detect Image Edges \n"
                    "8- Enlarge Image\n"
                    "9- Shrink Image\n"
                    "a- Mirror 1/2 Image\n"
                    "b- Shuffle Image\n"
                    "c- Blur Image\n"
                    "d- Crop Image\n"
                    "e- Skew Image Right \n"
                    "f- Skew Image Up\n"
                    "s- Save the image to a file\n"
                    "0- Exit\n """;

            // take the user choice
            char c;
            cin >> c;

            switch (c) {
                case '1':

                    //turn the image into black and white image
                    color ? cBlacknwhite() : blacknwhite();
                    break;

                case '2':

                    //produce a negative version of the image
                    color ? cInvert() : invert();
                    break;

                case '3':

                    // put two images together into one
                    color ? cMerge() : merge();
                    break;

                case '4':

                    // flip the image in the chosen direction
                    color ? cFlip() : flip();
                    break;


                case '5':

                    // rotate the image by the chosen angle
                    color ? cRotate() : rotate();
                    break;

                case '6':

                    // adjust brightness level 50% darker or 50%brighter
                    color ? cBrightness() : brightness();
                    break;

                case '7':

                    // show the edges of the given image
                    color? cEdge() : edge();
                    break;

                case '8':

                    // split the image into four square and fit the chosen into the whole image
                    color ? cEnlarge() : enlarge();
                    break;


                case '9':

                    //shrink the image with the chosen scale
                    color ? cShrink() : shrink();
                    break;


                case 'a':

                    // copy the chosen half of the image in reversed order to the remaining half
                    color ? cMirror() : mirror();
                    break;

                case 'b':

                    // split the image into four squares and rearrange them according to the given order
                    color ? cShuffle() : shuffle();
                    break;

                case 'c':

                    // add a blurring effect to the image
                    color ? cBlur() : blur();
                    break;

                case 'd':

                    //crop the image starting from certain point with given dimensions
                    color ? cCrop() : crop();
                    break;

                case 'e':

                    //skew image right with the given angle
                    color ? cSkewRight() : skewRight();
                    break;

                case 'f':

                    //skew image up with the given angle
                    color ? cSkewUp() : skewUp();
                    break;

                case 's':

                    //save the image to file
                    color ? cSaveImage() : saveImage();

                case '0':

                    //break out of editing loop
                    editing = false;
            }

        }

        //check if the user wishes to continue or want to quit
        cout<<"1:Edit another image\n2:Quit\n";
        int x; cin>>x; while (x!=1&&x!=2){cin>>x;}
        if ((x+1)&1) break;
    }

    return 0;
}





