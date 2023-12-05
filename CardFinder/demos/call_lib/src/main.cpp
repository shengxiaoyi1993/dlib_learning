#include <iostream>
#include <opencv_basic/opencv_basic.h>
#include <opencv2/opencv.hpp>



/// 经过多次手动标记,可以将所有图案添加到标准库

/// 目前要做的是将分割出的图形与已有图片比较,若无匹配,则

double getHVRate(const cv::Mat &mat)
{
  if (mat.empty()) {
    return -1;
  }

  if (mat.type()!= CV_8U) {

  }

  double sum_h=0;
  for(int r=0;r<mat.rows;r++)
  {
    for(int c=0;c<mat.cols;c++)
    {
      sum_h+=(int)mat.at<uchar>(r,c);
    }

  }


}


int main(int argc, char *argv[])
{

  return 0;
}


//double getHVRate(const cv::Mat &mat)
//{

//}
