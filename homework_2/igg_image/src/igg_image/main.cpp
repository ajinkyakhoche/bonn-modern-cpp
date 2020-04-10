#include<iostream>
#include<vector>
#include "image.h"


using std::cout;
using std::endl;
using namespace igg;

int main()
{
    cout << "welcome, testing read and write functionalities:" << endl;
    std::string s = "data/lena.ascii.pgm";
    Image img = Image();

    bool ret = img.FillFromPgm(s);
    img.WriteToPgm("data/expt1.pgm");

    std::vector<float> hist = img.ComputeHistogram(10);
    cout<< "hist[1] is: "<< hist[1] <<endl;

    img.DownScale(10);
    img.WriteToPgm("data/expt2.pgm");
    cout<< "Downscaled image is written "<<endl;

    img.UpScale(20);
    img.WriteToPgm("data/expt3.pgm");
    cout<< "Upscaled image is written "<<endl;
    
    return ret;
}