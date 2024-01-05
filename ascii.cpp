#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct pixel{
    int r;
    int g;
    int b;
};

void readBMP(char* filename, vector<vector<pixel>> &pixels, int &height, int &width){

    //open file
    FILE* f = fopen(filename, "rb");
    unsigned char info[54];

    //Read the 54-byte header
    fread(info, sizeof(unsigned char), 54, f);

    //extract image height and width from header
    width = *(int*)&info[18];
    height = *(int*)&info[22];

    //ChatGPT magic idk how this works
    int rowSize = (3 * width) + (4 - (3 * width) % 4);

    //change vector size
    pixels.resize(height, vector<pixel>(width));

    //read data into 2d vector
    for(int i = height -1; i >= 0; i--){
        //write
        for(int j = 0; j < width; j++){
            fread(&(pixels[i][j].b), sizeof(unsigned char), 1, f);
            fread(&(pixels[i][j].g), sizeof(unsigned char), 1, f);
            fread(&(pixels[i][j].r), sizeof(unsigned char), 1, f);
        }
        //move pointer to start of row
        fseek(f, 54 + i * rowSize, SEEK_SET);
    }

    //close the file
    fclose(f);

}

int main(int argc, char* argv[]){
    //check args
    if(argc != 2){
        cout << "Invalid usage! ./ascii.cpp <bmp file name>" << endl;
        return -1;
    }

    int height;
    int width;

    vector<vector<pixel>> pixels;

    //get data
    readBMP(argv[1], pixels, height, width);

    printf("Height: %i\nWidth: %i\n", height, width);

    //print out pixel values
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            printf("%i, %i, %i\n", pixels[i][j].r, pixels[i][j].g, pixels[i][j].b);
        }
    }

}