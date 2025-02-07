#include <bits/stdc++.h>
// predefined matrices to store cImages

unsigned char cImage[SIZE][SIZE][RGB];
unsigned char cImage2[SIZE][SIZE][RGB];
unsigned char cImage3[SIZE][SIZE][SIZE];



// load cImages into the matrix
void cLoadImage (){
    char cImageFileName[100];

    // get gray scale image file name
    cout << "Please enter file name of the image to process: ";
    cin >> cImageFileName;

    // add to it .bmp extension and load cImage
    strcat (cImageFileName, ".bmp");
    readRGBBMP(cImageFileName, cImage);
}

void cLoadImage2 (){
    char cImageFileName[100];

    // get gray scale cImage file name
    cout << "Please enter name of image file to merge with: ";
    cin >> cImageFileName;

    // add to it .bmp extension and load cImage
    strcat (cImageFileName, ".bmp");
    readRGBBMP(cImageFileName, cImage2);
}



//save the cImage from the matrix to the file
void cSaveImage (){
    char cImageFileName[100];

    // get gray scale cImage target file name
    cout << "Enter the target Image file name: ";
    cin >> cImageFileName;

    // add to it .bmp extension and load cImage
    strcat (cImageFileName, ".bmp");
    writeRGBBMP(cImageFileName, cImage);
}



//set the original matrix to the value of the filtered image
void cFinalImage(){

    // loop on all pixels
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            for(int k=0; k<RGB; k++)

                // copy pixels to the original matrix
                cImage[i][j][k]=cImage2[i][j][k];
}



// turn cImage into black and white
void cBlacknwhite(){

    //loop on all pixels
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++) {

            //take the equivalent grey color for the RGB
            cImage[i][j][0] = 0.299 * cImage[i][j][0] + 0.587 * cImage[i][j][1] + 0.114 * cImage[i][j][2];

            // turn pixel to the closest between black and white
            cImage[i][j][0] = cImage[i][j][0] / 128 * 255;
            cImage[i][j][1]=cImage[i][j][0]; cImage[i][j][2]=cImage[i][j][1];

        }

}



// Produce a negative cImage from the loaded one
void cInvert(){

    // loop on all pixels
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            for (int k=0; k<RGB; k++)

            // turn pixel to the opposite color
            cImage[i][j][k] = 255 - cImage[i][j][k];

}



// Merge two images into a new one
void cMerge(){

    // load another image
    cLoadImage2();

    // loop on all pixels
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            for (int k=0; k<RGB; k++)

            // take the average between the two images and loaded into one
            cImage[i][j][k] = (cImage[i][j][k]+cImage2[i][j][k])/2;

}



// flip cImage with two options Vertical flip and Horizontal flip
void cFlip(){

    // choose between vertical and horizontal flip
    cout<<"Flip (h)orizontally or (v)ertically ?\n ";
    char c; cin>>c;

    // for vertical flip
    if (tolower(c)=='v')

        // loop on all pixels
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                for(int k=0; k<RGB; k++)

                    // change the orientation of the pixels
                    cImage2[i][j][k] = cImage[SIZE-i][j][k];

    // For horizontal flip
    if (tolower(c)=='h')

        // loop on all pixels
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                for(int k=0; k<RGB; k++)

                    // change the orientation of pixels
                    cImage2[i][j][k] = cImage[i][SIZE-j][k];


    // save the image in the original matrix
    cFinalImage();
}



// rotate cImage with the different angle option 90, 180, 270.
void cRotate(){

    // different angle options
    cout<<"Rotate (90), (180) or (270) degrees?\n";
    int x; cin>>x;

    if (x==90)
        // loop on all pixels
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                for(int k=0; k<RGB; k++)

                    // rearrange pixels to perform 90 degree rotate
                    cImage2[i][j][k] = cImage[SIZE-j][i][k];

    if (x==180)
        // loop on all pixels
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                for(int k=0; k<RGB; k++)

                    // rearrange pixels to perform 180 degree rotate
                    cImage2[i][j][k] = cImage[SIZE-i][SIZE-j][k];

    if (x==270)
        //loop on all pixels
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                for(int k=0; k<RGB; k++)

                    // rearrange pixels to perform 270 degree rotate
                    cImage2[i][j][k] = cImage[j][SIZE-i][k];

    // save the image the original matrix
    cFinalImage();
}



// increase or decrease the brightness of the cImage with 50%
void cBrightness() {

    //choose between increasing or decreasing brightness
    cout<<"\n 0:Darken, 1:lighten\n";
    int x; cin>>x;

    // loop on all pixels
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            for(int k=0; k<RGB; k++)

                // change pixel color to be set in  half the range of colors
                cImage[i][j][k] = cImage[i][j][k]*0.5+127*x;

}



//Detect the edges of the image and delete the rest
void cEdge(){

    //turn image into black and white.
    cBlacknwhite();

    // loop on all pixels
    for (int i=0; i<SIZE; ++i)
        for (int j=0; j<SIZE; ++j)
            for(int k=0; k<RGB; k++){

            // set the pixel color to white by default
            int color=255;

            //turn the pixel color black if one of the conditions is  true
            if (cImage[i][j][k] != cImage[i + 1][j][k]) color=0;
            if (cImage[i][j][k] != cImage[i][j + 1][k]) color=0;

            // change the pixel color
            cImage[i][j][k]=color;
        }
}



// enlarge part of the cImage to fill the whole 256*256
void cEnlarge(){

    // choose the part of image to enlarge
    cout<<"1:top left   2:top right\n3:bottom left 4:bottom right\n";
    int x; cin>>x;

    // loop on all pixels
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            for(int k=0; k<RGB; k++)

                // copy the same pixel repeatedly focus on the first part
                cImage2[i][j][k] = cImage[(i/2)+((x/3)*127)][j/2+(((x+1)%2)*127)][k];

    // save the image in the original matrix
    cFinalImage();
}



// shrink image with three scale options 1/2, 1/3, 1/4
void cShrink(){

    // different shrink scales
    cout<<"\n 2:half, 3:third  4:fourth\n";
    int x; cin>>x;

    // loop on just a part of the image
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            for(int k=0; k<RGB; k++)
                if (i<SIZE/x && j<SIZE/x)

                    // skip pixels to fit the smaller size
                    cImage2[i][j][k]  = cImage[i*x][j*x][k];

                    // turn background white
                else cImage2[i][j][k] = 255;

    // save the image in the original matrix
    cFinalImage();
}



// take half of the cImage and repeat it on the other half reversed
void cMirror (){

    // choose a half of the image to be mirrored
    cout<<"\n 1:left  2:right\n 3:upper 4:bottom\n";
    int x; cin>>x;

    if (x==1)
        // start from half of the image going right
        for (int i = 0; i < SIZE; i++)
            for (int j = SIZE/2; j < SIZE; j++)
                for (int k=0; k<RGB; k++)

                // copy the pixel in reversed order
                cImage[i][j][k] = cImage[i][SIZE-j][k];

    if (x==2)
        // start from half of the image going left
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE/2; j++)
                for (int k=0; k<RGB; k++)

                    // copy the pixel in reversed order
                    cImage[i][j][k] = cImage[i][SIZE-j][k];

    if (x==3)
        // start from half of the image going down
        for (int i = SIZE/2; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                for (int k=0; k<RGB; k++)

                    // copy the pixel in reversed order
                    cImage[i][j][k] = cImage[SIZE-i][j][k];

    if (x==4)
        // start from half of the image going up
        for (int i = 0; i < SIZE/2; i++)
            for (int j = 0; j < SIZE; j++)
                for (int k=0; k<RGB; k++)

                    // copy the pixel in reversed order
                    cImage[i][j][k] = cImage[SIZE-i][j][k];

}



// split the image into four parts and rearrange them as the given order.
void cShuffle(){

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
            for(int k=0; k<RGB; k++)

                // change the starting point according to selected part
                cImage2[i][j][k] = cImage[i+w/3*127][j+(w+1)%2*127][k];



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
            for(int k=0; k<RGB; k++)

                // change the starting point according to selected part
                cImage2[i][j][k] = cImage[i+x/3*127][j+x%2*-127][k];



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
            for(int k=0; k<RGB; k++)

                // change the starting point according to selected part
                cImage2[i][j][k] = cImage[i+(y/3-1)*127][j+(y+1)%2*127][k];



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
            for(int k=0; k<RGB; k++)
                // change the starting point according to selected part
                cImage2[i][j][k] = cImage[i+(z/3-1)*127][j+z%2*-127][k];


    // save the image in the original matrix
    cFinalImage();
}



// add blurring effect to the given image
void cBlur() {
    // repeat the process 5 times
    for (int c=0; c<5; c++)

        //loop on all pixels
        for (int i = 1; i < SIZE-1; i++)
            for (int j = 1; j < SIZE-1; j++)
                for(int k=0; k<RGB; k++){

                // set pixel color to the average of pixels in 3*3 square
                cImage[i][j][k]  = (cImage[i][j-1][k]+cImage[i][j][k]+cImage[i][j+1][k])/9;
                cImage[i][j][k] += (cImage[i-1][j-1][k]+cImage[i-1][j][k]+cImage[i-1][j+1][k])/9;
                cImage[i][j][k] += (cImage[i+1][j-1][k]+cImage[i+1][j][k]+cImage[i+1][j+1][k])/9;
            }

}



// Produce a new cImage with provided dimensions starting from the given point
void cCrop(){

    // take the stating point of the rectangle
    cout<<"Enter the top left point of Rectangle (x,y): ";
    int x,y; cin>>x>>y;

    // take the length and width of the rectangle
    cout<<"Enter the two dimensions l, w: ";
    int l, w; cin>>l>>w;

    // loop on the pixels of the target part
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            for(int k=0; k<RGB; k++)

                // check if the pixel within wanted range
                if (i<x || j<y ||  i>x+w || j>y+l)
                    cImage2[i][j][k] = 255;

                    // turn the background white
                else cImage2[i][j][k] = cImage[i][j][k];

    // save the image in the original matrix
    cFinalImage();
}



//skew the image with the given angle vertically
void cSkewRight(){

    //take the skew angle form the user
    cout<<"Enter an angle: ";
    float angle; cin>>angle;
    angle=angle/180/7*22;
    angle=tan(angle);

    // shrink the image to ensure that it doesn't go out of boundries
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            for(int k=0; k<RGB; k++)

                // copy the target pixel only in a smaller size
                if (j<SIZE*(1-angle))
                    cImage3[i][j][k] = cImage[i][int(j / (1 - angle))][k];
                else
                    // turn background white
                    cImage3[i][j][k]=255;

    // skew the image with the given angle
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            for(int k=0; k<RGB; k++)

                //move the pixels horizontally depending on the value of i
                cImage2[i][j + int((SIZE - i) * angle)][k] = cImage3[i][j][k];

    //save the image to the original matrix
    cFinalImage();
}



//skew the image with the given angle horizontally
void cSkewUp(){

    //take the skew angle form the user
    cout<<"Enter an angle: ";
    float angle; cin>>angle;
    angle=angle/180/7*22;
    angle=tan(angle);

    //shrink the image ensure that  it does not go out of boundries
    for (int i = 0; i < SIZE*(1-angle); i++)
        for (int j = 0; j < SIZE; j++)
            for(int k=0; k<RGB; k++)

                // copy the target pixel only in a smaller size
                cImage3[i][j][k] = cImage[int(i / (1 - angle))][j][k];

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            for(int k=0; k<RGB; k++)

                //turn background white
                cImage2[i][j][k]=255;

    //skew the image with the given angle
    for (int i = 0; i < SIZE*(1-angle); i++)
        for (int j = 0; j < SIZE; j++)
            for(int k=0; k<RGB; k++)

                // push the pixels downward depending on the value of j
               cImage2[i + int((SIZE-j) * angle)][j][k] = cImage3[i][j][k];

    //save the image in the original matrix
    cFinalImage();
}
