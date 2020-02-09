#ifndef __EDGEVISION_H_ 
#define __EDGEVISION_H_

#include <opencv2/core/core.hpp> 
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp> 
#include <vector>

using namespace std; 
using namespace cv;

#define KERNEL_X 3
#define KERNEL_Y 3

class Vision 
{ 
private:
    int kernelAreaDotProd_X;
    int kernelAreaDotProd_Y; 
    
public:
    Vision();
    Mat SobelConv2D(Mat src, Mat dst);
};
#endif
