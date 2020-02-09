
  
#include <iostream> 
#include <opencv2/core/core.hpp> 
#include <opencv2/imgproc/imgproc.hpp> 
#include <opencv2/highgui/highgui.hpp> 
#include "EdgeVision.hpp"

using namespace std; 
using namespace cv; 

int main() 
{
    Mat input = imread("image.jpg");
    Mat convSrcImg;
    Mat convDstImg;

    if (!input.data) // failed to read image
    {
        cout << "Failed to load or find input image..." << endl;
        cin.get();
        return -1;
    }

    namedWindow("Original Input Image", CV_WINDOW_AUTOSIZE);
    imshow("Original Input Image", input);

    cvtColor(input, convSrcImg, CV_BGR2GRAY);
    namedWindow("Grayscale Image of Input Image (ConvSrc)", CV_WINDOW_AUTOSIZE);
    imshow("Grayscale Image of Input Image (ConvSrc)", convSrcImg);

    convDstImg = convSrcImg.clone();

    Vision vision;
    vision.SobelConv2D(convSrcImg, convDstImg); // declaring convolution opr func

    namedWindow("Sobel Convolution Output Image", CV_WINDOW_AUTOSIZE);
    imshow("Sobel Convolution Output Image", convDstImg);

    waitKey(0);
    destroyAllWindows();
    return 0;
}
