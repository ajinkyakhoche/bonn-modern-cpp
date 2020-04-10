#pragma once

#include <vector>
#include "io_tools.h"

namespace igg {

class Image {
 public:
  ///////////////////// Create the public interface here ///////////////////////
  Image() {}
  // Constructor with Member intializer list
  Image(int rows, int cols): rows_{rows}, cols_{cols} 
  {
    data_.reserve(rows*cols);
  }  
  // Getter functions for image size
  int rows() const {return rows_;}  // const correctness
  int cols() const {return cols_;}

  // // Setter functions for image size
  // int rows() {return rows_;}
  // int cols() {return cols_};


  // getter function for pixel value
  const int& at(int r, int c) const;

  // setter function for pixel value
  int& at(int r, int c);
  
  bool FillFromPgm(const std::string& file_name);
  void WriteToPgm(const std::string& file_name);

  // histogram of image
  std::vector<float> ComputeHistogram(int bins) const;

  // Downscaling an image
  void DownScale(int scale);
  void UpScale(int scale);

 private:
  int rows_ = 0;
  int cols_ = 0;
  int max_val_ = 255;
  std::vector<int> data_;
};

}  // namespace igg
