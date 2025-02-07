#include <cmath>
#include <bits/stdc++.h>
// predefined matrices to store images
unsigned char image[SIZE][SIZE];
unsigned char image2[SIZE][SIZE];



// load images into the matrix
void loadImage (){
    char imageFileName[100];

    // get gray scale image file name
    cout << "Please enter file name of the image to process: ";
    cin >> imageFileName;

    // add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}

void loadImage2 (){
    char imageFileName[100];

    // get gray scale image file name
    cout << "Please enter name of image file to merge with: ";
    cin >> imageFileName;

    // add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, image2);
}



//save the image from the matrix to the file
void saveImage (){
    char imageFileName[100];

    // get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
}



//set the original matrix to the value of the filtered image
void finalImage(){

    // loop on all pixels
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)

            // copy pixels to the original matrix
            image[i][j]=image2[i][j];
}



// turn image into black and white
void blacknwhite(){

    //loop on all pixels
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)

            // turn pixel to the closest between black and white
            image[i][j] = image[i][j]/128*255 ;
}



// Produce a negative image from the loaded one
void invert(){

    // loop on all pixels
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)

            // turn pixel into the opposite color
            image[i][j] = 255-image[i][j] ;
}



// Merge two images into a new one
void merge(){

    // load another image
    loadImage2();

    // loop on all pixels
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)

            // take the average between the two images and loaded into one
            image[i][j] = (image[i][j]+image2[i][j])/2;
}



// flip image with two options Vertical flip and Horizontal flip
void flip(){

    // choose between vertical and horizontal flip
    cout<<"Flip (h)orizontally or (v)ertically ?\n ";
    char c; cin>>c;

    // for vertical flip
    if (tolower(c)=='v')

        // loop on all pixels
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)

                // change the orientation of the pixels
                image2[i][j] = image[SIZE-i][j];

    // For horizontal flip
    if (tolower(c)=='h')

        // loop on all pixels
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)

                // change the orientation of pixels
                image2[i][j] = image[i][SIZE-j];

    // save the image in the original matrix
    finalImage();
}



// rotate image with the different angle option 90, 180, 270.
void rotate(){

    // different angle options
    cout<<"Rotate (90), (180) or (270) degrees?\n";
    int x; cin>>x;

    if (x==90)
        // loop on all pixels
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)

                // rearrange pixels to perform 90 degree rotate
                image2[i][j] = image[SIZE-j][i];

    if (x==180)
        // loop on all pixels
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)

                // rearrange pixels to perform 180 degree rotate
                image2[i][j] = image[SIZE-i][SIZE-j];

    if (x==270)
        //loop on all pixels
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)

                // rearrange pixels to perform 270 degree rotate
                image2[i][j] = image[j][SIZE-i];

    // save the image the original matrix
    finalImage();

}



// increase or decrease the brightness of the image with 50%
void brightness() {

    //choose between increasing or decreasing brightness
    cout<<"\n 0:Darken, 1:lighten\n";
    int x; cin>>x;

    // loop on all pixels
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)

            // change pixel color to be set in  half the range of colors
            image[i][j] = image[i][j]*0.5+127*x;

}



//Detect the edges of the image and delete the rest
void edge(){

    //turn image into black and white.
    blacknwhite();

    // loop on all pixels
    for (int i=0; i<SIZE; ++i)
        for (int j=0; j<SIZE; ++j){

            // set the pixel color to white by default
            int color=255;

            //turn the pixel color black if one of the conditions is  true
            if (image[i][j] != image[i + 1][j]) color=0;
            if (image[i][j] != image[i][j + 1]) color=0;

            // change the pixel color
            image[i][j]=color;
        }
}



// enlarge part of the image to fill the whole 256*256
void enlarge(){

    // choose the part of image to enlarge
    cout<<"1:top left   2:top right\n3:bottom left 4:bottom right\n";
    int x; cin>>x;

    // loop on all pixels
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)

            // copy the same pixel repeatedly focus on the first part
            image2[i][j] = image[(i/2)+((x/3)*127)][j/2+(((x+1)%2)*127)];

    // save the image in the original matrix
    finalImage();
}



// shrink image with three scale options 1/2, 1/3, 1/4
void shrink(){

    // different shrink scales
    cout<<"\n 2:half, 3:third  4:fourth\n";
    int x; cin>>x;

    // loop on just a part of the image
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)

            if (i<SIZE/x && j<SIZE/x)
                // skip pixels to fit the smaller size
                image2[i][j]  = image[i*x][j*x];

                // turn background white
            else image2[i][j] = 255;

    // save the image in the original matrix
    finalImage();
}



// take half of the image and repeat it on the other half reversed
void mirror (){

    // choose a half of the image to be mirrored
    cout<<"\n 1:left  2:right\n 3:upper 4:bottom\n";
    int x; cin>>x;

    if (x==1)
        // start from half of the image going right
        for (int i = 0; i < SIZE; i++)
            for (int j = SIZE/2; j < SIZE; j++)

                // copy the pixel in reversed order
                image[i][j] = image[i][SIZE-j];

    if (x==2)
        // start from the half of the image going left
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE/2; j++)

                // copy the pixels in reversed order
                image[i][j] = image[i][SIZE-j];

    if (x==3)
        // start from half of the image going down
        for (int i = SIZE/2; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)

                // copy the pixels in reversed order
                image[i][j] = image[SIZE-i][j];

    if (x==4)
        // start from half of the image going up
        for (int i = 0; i < SIZE/2; i++)
            for (int j = 0; j < SIZE; j++)

                // copy pixels in reversed order
                image[i][j] = image[SIZE-i][j];
}



// split the image into four parts and rearrange them as the given order.
void shuffle(){

    // choose which part would be top left part
    cout<<"Choose top left square: ";
    int w; cin>>w;

    // make sure to get a valid input
    while (w>4 || w<1) {
        cout<<"Invalid input, Try again: "; cin>>w;
    }

    // loop on the pixels of the first square
    for (int i = 0; i < SIZE/2; i++)
        for (int j = 0; j < SIZE/2; j++)

            // change the starting point according to selected part
            image2[i][j] = image[i+w/3*127][j+(w+1)%2*127];



    //choose which part would be the top right part
    cout<<"Choose top right square: ";
    int x; cin>>x;

    // make sure to get a valid input
    while (x>4 || x<1 || w==x) {
        cout<<"Invalid input, Try again: "; cin>>x;
    }

    // loop on the pixels of the second square
    for (int i = 0; i < SIZE/2; i++)
        for (int j = SIZE/2; j < SIZE; j++)

            // change the starting point according to selected part
            image2[i][j] = image[i+x/3*127][j+x%2*-127];


    // choose which part would be bottom left part
    cout<<"Choose bottom left square: ";
    int y; cin>>y;

    // make sure to get a valid input
    while (y>4 || y<1 || w==y || x==y) {
        cout<<"Invalid input, Try again: "; cin>>y;
    }

    // loop on the pixels of the third square
    for (int i = SIZE/2; i < SIZE; i++)
        for (int j = 0; j < SIZE/2; j++)

            // change the starting point according to selected part
            image2[i][j] = image[i+(y/3-1)*127][j+(y+1)%2*127];


    // choose which part would be the bottom right part
    cout<<"Choose bottom right square: ";
    int z; cin>>z;

    // make sure to get a valid input
    while (z>4 || z<1 || w==z || x==z || y==z) {
        cout<<"Invalid input, Try again: "; cin>>z;
    }

    // loop on the pixels of the fourth square
    for (int i = SIZE/2; i < SIZE; i++)
        for (int j = SIZE/2; j < SIZE; j++)

            // change the starting point according to selected part
            image2[i][j] = image[i+(z/3-1)*127][j+z%2*-127];

    // save the image in the original matrix
    finalImage();
}



// add blurring effect to the given image
void blur() {

    // repeat the process 3 times
    for (int k=0; k<3; ++k)

        //loop on all pixels
        for (int i = 1; i < SIZE-1; i++)
            for (int j = 1; j < SIZE-1; j++){

                // set pixel color to the average of pixels in 3*3 square
                image[i][j]  = (image[i][j-1]+image[i][j]+image[i][j+1])/9;
                image[i][j] += (image[i-1][j-1]+image[i-1][j]+image[i-1][j+1])/9;
                image[i][j] += (image[i+1][j-1]+image[i+1][j]+image[i+1][j+1])/9;
            }

}



// Produce a new image with provided dimensions starting from the given point
void crop(){

    // take the center of the rectangle
    cout<<"Enter the top left point of Rectangle (x,y): ";
    int x,y; cin>>x>>y;

    // take the length and width of the rectangle
    cout<<"Enter the dimensions of the rectangle: ";
    int l, w; cin>>l>>w;

    // loop on the pixels of the target part
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)

            // check if the pixel within wanted range
            if (i<x || j<y || i>x+w || j>y+l)
                image[i][j] = 255;
}



//skew the image with the given angle vertically
void skewRight(){

    //take the skew angle form the user
    cout<<"Enter an angle: ";
    float angle; cin>>angle;
    angle=angle/180/7*22;
    angle=tan(angle);

    // shrink the image so it doesn't go out of boundries
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)

            // copy the target pixel only in a smaller size
            if (j<SIZE*(1-angle))
                image2[i][j] = image[i][int(j / (1 - angle))];

            else
                // turn background white
                image2[i][j]=255;


    // skew the image with the given angle
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            image[i][j + int((SIZE - i) * angle)] = image2[i][j];


}



//skew the image with the given angle horizontally
void skewUp(){

    //take the skew angle form the user
    cout<<"Enter an angle: ";
    float angle; cin>>angle;
    angle=angle/180/7*22;
    angle=tan(angle);

    //shrink the image ensure that it does not go out of boundries
    for (int i = 0; i < SIZE*(1-angle); i++)
        for (int j = 0; j < SIZE; j++)

                // skip pixels to fit the new size
                image2[i][j] = image[int(i / (1 - angle))][j];


    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)

            // turn the background white
            image[i][j]=255;

    //skew the image with the given angle
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)

            // copy the target pixels only
            if (i<SIZE*(1-angle))

                // push the pixel downward depending on the value of j
                image[(i + int((SIZE-j) * angle))][j] = image2[i][j];


}


