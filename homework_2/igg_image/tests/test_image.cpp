#include <gtest/gtest.h>
#include "igg_image/image.h"
#include "igg_image/io_tools.h"

namespace{
TEST(Image, DefaultConstructor)
{
    // by nature also testing the getter functions
    const igg::Image img;

    EXPECT_EQ(0, img.rows());
    EXPECT_EQ(0, img.cols());
}

TEST(Image, ConstructorWithMemberList)
{
    // by nature also testing the getter functions for rows and cols
    const igg::Image img(100,100);

    EXPECT_EQ(100, img.rows());
    EXPECT_EQ(100, img.cols());
}

TEST(Image, FileReading)
{
    // also testing getter function for pixel value
    igg::Image img, img1;
    img1.FillFromPgm("bogus_file");
    EXPECT_EQ(0, img1.rows());

    img.FillFromPgm("data/lena.ascii.pgm");

    for (int i = 0; i < img.rows(); i++)
    {
        for (int j = 0; j < img.cols(); j++)
        {
            EXPECT_GE(img.at(i, j), 0) << "ERROR: Pixel value < 0";
            EXPECT_LE(img.at(i, j), 255) << "ERROR: Pixel value > 255";
        } 
    }
}

TEST(Image, FileWriting)
{
    // also test the setter function
    igg::Image img(50,50);

    img.at(25,25) = 254;
    // img.FillFromPgm("data/lena.ascii.pgm");
    EXPECT_EQ(254, img.at(25,25));
    // EXPECT_EQ(0, img.at(24,25));
}
}   //namespace 