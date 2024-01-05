#include <iostream>
#include <fstream>

using namespace std;

struct BMPSig{
    unsigned char data[2];
    BMPSig() {data[0] = data[1] = 0;}
};

struct BMPHeader{
    unsigned int fileSize;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int dataOffset;
    BMPHeader() : fileSize(0), reserved1(0), reserved2(0), dataOffset(0) {}
};

struct pixel{
    unsigned int red;
    unsigned int green;
    unsigned int blue;
    pixel() : red(0), green(0), blue(0) {}
};

void readHeader(ifstream &fin, BMPSig &sig, BMPHeader &header){
    if(!fin)
        return;

    //Go to start of file
    fin.seekg(0, ios::beg);

    //Read the signature + header
    fin.read((char*) &sig, sizeof(sig));
    fin.read((char*) &header, sizeof(header));
}

void printHeader(BMPSig sig, BMPHeader header){
    cout << "========BMP HEADER========" << endl;
    cout << "+ Signature : " << sig.data[0] << sig.data[1] << endl;
    cout << "+ File size : " << header.fileSize << " bytes" << endl;
    cout << "+ Reserved1 : " << header.reserved1 << endl;
    cout << "+ Reserved2 : " << header.reserved2 << endl;
    cout << "+ Data Offset : " << header.dataOffset << " bytes" << endl;
}

int main(int argc, char* argv[]){
    //Get command line arg
    if(argc != 2){
        cout << "Improper usage! ./ascii.out <bmp file name>" << endl;
        return -1;
    }

    //Read in file
    ifstream fin(argv[1], ios::binary);

    //Define a sig and header
    BMPSig sig;
    BMPHeader header;

    //print empty header
    printHeader(sig, header);
    //read bmp header
    readHeader(fin, sig, header);
    //print populated header
    printHeader(sig, header);

    return 0;
}