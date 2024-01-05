#include <iostream>
#include <fstream>

using namespace std;

unsigned char* readBMP(char* filename, int &width, int &height){

    //open file
    FILE* f = fopen(filename, "rb");
    unsigned char info[54];

    //Read the 54-byte header
    fread(info, sizeof(unsigned char), 54, f);

    //extract image height and width from header
    width = *(int*)&info[18];
    height = *(int*)&info[22];

    //allocate 3 bytes per pixel
    int size = 3 * width * height;
    unsigned char* data = new unsigned char[size];

    //read the rest of the data at once
    fread(data, sizeof(unsigned char), size, f);
    fclose(f);

    //flip the order of every 3 bytes
    for(int i = 0; i < size; i++){
        unsigned char tmp = data[i];
        data[i] = data[i+2];
        data[i+2] = tmp;
    }

    return data;
}

int main(int argc, char* argv[]){
    //check args
    if(argc != 2){
        cout << "Invalid usage! ./ascii.cpp <bmp file name>" << endl;
        return -1;
    }

    int height;
    int width;

    unsigned char* data = readBMP(argv[1], width, height);

    cout << "Width: " << width << "\nHeight: " << height << endl;
}