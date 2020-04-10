#include <vector>
#include <iostream>
#include "image.h"
// #include "io_tools.h"

using std::cout;
using std::endl;

namespace igg
{
// getter function for pixel value    
const int &Image::at(int r, int c) const{
    return data_[r * cols_ + c + 1];
}

// setter function for pixel value
int &Image::at(int r, int c){ 
    return data_[r * cols_ + c + 1];
}

bool Image::FillFromPgm(const std::string& file_name)
{  
    bool ret = true;

    io_tools::ImageData img = io_tools::ReadFromPgm(file_name);

    if (img.data.empty())
        ret = false;
    else
    {
        rows_ = img.rows;
        cols_ = img.cols;
        max_val_ = img.max_val;

        data_.insert(data_.end(), img.data.begin(), img.data.end());

        ret = true;
    }

    return ret;
}

void Image::WriteToPgm(const std::string& file_name)
{
    io_tools::ImageData img_data = {
        rows_,
        cols_,
        max_val_, 
        data_
    };
    
    if (io_tools::WriteToPgm(img_data, file_name))
        cout << "image writing successful" << endl;
    else
        cout << "image writing FAILED!"<<endl;
}

std::vector<float> Image::ComputeHistogram(int bins) const
{
    std::vector<float> hist(bins);
    int thresh = max_val_/bins;

    for (int i = 0; i < rows()*cols(); i++)
    {
        auto d = data_[i];
        
        for (int j = 1; j <= bins; j++)
        {
            if(d <= j * thresh)
            {
                hist[j-1] += 1.0;
                break;
            }
        }
    }
    
    for (int j = 0; j < bins; j++)
    {
        hist[j] /= (rows()*cols());
    }
    
    return hist;
}

void Image::DownScale(int scale)
{
    auto new_rows = (int)(rows()/scale), new_cols = (int)(cols()/scale);
    std::vector<int> new_data(new_rows * new_cols);
    float avg = 0.;
    
    for (int i = 0; i < rows()- scale; i+=scale)
    {
        for (int j = 0; j < cols() - scale; j+=scale)
        {
            for (int k = 0; k < scale; k++)
            {
                for (int l = 0; l < scale; l++)
                {
                    avg += at(i+k, j+l);
                }
            }
            new_data[new_rows * (int)(i/scale) + (int)(j/scale)] = (int)(avg / (scale*scale));
            
            avg = 0.;
        }
    }
    
    rows_ = new_rows;
    cols_ = new_cols;
    data_ = new_data;
}

void Image::UpScale(int scale)
{   
    auto new_rows = (int)(rows()*scale), new_cols = (int)(cols()*scale);
    std::vector<int> new_data(new_rows * new_cols);

    for (int i = 0; i < new_rows- scale; i+=scale)
    {
        for (int j = 0; j < new_cols - scale; j+=scale)
        {
            for (int k = 0; k < scale; k++)
            {
                for (int l = 0; l < scale; l++)
                {
                    new_data[(i+k)*new_rows + j+l] = Image::at((int)(i/scale) , (int)(j/scale));
                }
            }
        }
    }

    rows_ = new_rows;
    cols_ = new_cols;
    data_ = new_data;
}
} // namespace igg