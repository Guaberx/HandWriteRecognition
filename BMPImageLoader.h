//
// Created by Guaberx on 10/17/2016.
//

#ifndef HANDWRITERECOGNITION_BMPIMAGELOADER_H
#define HANDWRITERECOGNITION_BMPIMAGELOADER_H
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include <vector>
#include <algorithm>
#include "BMPstructure.h"

using std::string;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::ios;
using std::vector;
using std::for_each;

template <typename T>
class BMPImage{
    ReadBMP bmpData;
    vector<T> bmpNormalizedData;
public:
    void read(string imagePath);
    void normalize();
    void print();
    void printNormalized();

    vector<T>& getNormalizedData();
};

template <typename T>
void BMPImage<T>::read(string imagePath){
    /*
     * Lee BMP  pixeles en formato RGB
     */
    ifstream file(imagePath,ios::in|ifstream::binary);
    if(!file.is_open()){
        cout << "DIDNT OPEN" <<endl;
        exit(1);
    }

    file.read((char*)&bmpData.bfh,sizeof(BITMAPFILEHEADER));
    file.read((char*)&bmpData.bih,sizeof(BITMAPINFOHEADER));

    ///TODO LO SIGUIENTE DA EL PADDING  Y SE MULTIPLICA POR 3 Y ESO ES CADA CUANTOS BYTES HAY WIDTH CEROS (THE SAME AMOUNT AS THE WIDTH)
    //Now we have to find out the number of bytes every scanline is padded with
    int padding = 0;
    while ( ( bmpData.bih.biWidth * 3 + padding ) % 4 != 0 )
        padding++;
    /*
     * At the end of the while loop padding will hold the number of padding bytes.
       Now we can get the length in bytes of a padded scanline:
       and eadh padding*3 bytes, the size of the width is going to be empty because of padding
	 */

    //Construct the buffer
    //Read the image into the imageReaded.image
    //We read an RGBTRIPLET EACH 3 BYTES OF THE FILE
    //IT's to be read byte by byte so the padding works as expected
    unsigned char buffer[bmpData.bih.biWidth * bmpData.bih.biHeight * 3];
    cout << "PADDING:\t" << padding << endl;
    for (int j = 0; j < bmpData.bih.biWidth * bmpData.bih.biHeight * 3; ++j) {
        if(padding != 0){
            if(j%(3*bmpData.bih.biWidth) == 0 && j != 0){//Checks for the padding
                file.seekg(padding,file.cur);//We move in the file padding times the pointer
            }
        }
        file.read((char*)&buffer[j],sizeof(char));
    }
    file.close();

    //Translate the buffer into the imageReaded
    //First we clean the vector
    bmpData.image.clear();
    uint32_t controller = 0;
    for (uint32_t k = 0; k < bmpData.bih.biWidth * bmpData.bih.biHeight * 3; k+=3, ++controller) {
        bmpData.image.push_back(RGBTRIPLE());
        bmpData.image[controller].rgbtBlue = buffer[k];
        bmpData.image[controller].rgbtGreen = buffer[k+1];
        bmpData.image[controller].rgbtRed = buffer[k+2];
    }
}

template <typename T>
void BMPImage<T>::normalize() {
    if(bmpData.image.empty()){
        return;
    }
    //First we clear the vector
    bmpNormalizedData.clear();
    //Now we add a pixel for each pixel of the data into the normalized data
    for_each(bmpData.image.begin(),bmpData.image.end(),
             [this](RGBTRIPLE i){
                 if((i.rgbtBlue + i.rgbtGreen + i.rgbtRed)/3 > 127){
                     bmpNormalizedData.push_back(0);//Negro
                 }else{
                     bmpNormalizedData.push_back(1);//Blanco
                 }
             });
}

template <typename T>
void BMPImage<T>::print(){
    uint32_t counter = 0;
    for_each(bmpData.image.begin(),bmpData.image.end(),
             [this,&counter](RGBTRIPLE i){
                 if(counter!=0 and counter%(bmpData.bih.biWidth)==0)printf("\n");
                 printf("%02x,%02x,%02x ",i.rgbtRed,i.rgbtGreen,i.rgbtBlue);
                 counter++;
             });
    cout << endl;
}

template <typename T>
void BMPImage<T>::printNormalized(){
    uint32_t counter = 0;
    for_each(bmpNormalizedData.begin(),bmpNormalizedData.end(),
             [this,&counter](T i){
                 if(counter!=0 and counter%(bmpData.bih.biWidth)==0)printf("\n");
                 if(i == 1)
                     printf("*");
                     //printf("%d",i);
                 else
                     printf(" ");
                 counter++;
             });
    cout << endl;
}

template <typename T>
vector<T>& BMPImage<T>::getNormalizedData(){
    return bmpNormalizedData;
}

#endif //HANDWRITERECOGNITION_BMPIMAGELOADER_H
