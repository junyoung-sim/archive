#include <iostream> 
#include <opencv2/core/core.hpp> 
#include <opencv2/imgproc/imgproc.hpp> 
#include <opencv2/highgui/highgui.hpp> 
#include <vector> 
#include "EdgeVision.hpp"

Vision::Vision() 
{
    kernelAreaDotProd_X = 0;
    kernelAreaDotProd_Y = 0;
}

Mat Vision::SobelConv2D(Mat convSrcImg, Mat convDstImg)
{
    int convRow = 0, convCol = 0;
    int kernelRow = 0, kernelCol = 0;
    int convDstRow = 1, convDstCol = 1;
    int gradient = 0;

    const int kernel_vertical[KERNEL_X][KERNEL_Y] = {
        { 1, 0, -1 },
        { 2, 0, -2 },
        { 1, 0, -1 }
    }; // initialize sobel vertical kernel

    cout << "Sobel Vertical Kernel Vector = [ ";
    for (int i = 0; i < KERNEL_X; i++)
        for (int j = 0; j < KERNEL_Y; j++) cout << kernel_vertical[i][j] << ", ";
    
    cout << "]";
    cout << endl;
    
    const int kernel_horizontal[KERNEL_X][KERNEL_Y] = {
        { 1, 2, 1 },
        { 0, 0, 0 },
        { -1, -2, -1 }
    }; // initialize sobel horizontal kernel
    
    cout << "Sobel Horizontal Kernel Vector = [ ";
    for (int i = 0; i < KERNEL_X; i++)
        for (int j = 0; j < KERNEL_Y; j++) cout << kernel_horizontal[i][j] << ", ";
    
    cout << "]";
    cout << endl << "Vision2D :: Kernel vectors created.." << endl << endl;
    cout << "Vision2D :: Sobel Convolution started.." << endl;

    while (convRow <= convSrcImg.rows - KERNEL_X && convCol <= convSrcImg.cols - KERNEL_Y)
    {
        for (int row = convRow; row < convRow + KERNEL_X; row++)
        {
            for (int col = convCol; col < convCol + KERNEL_Y; col++) // sobel conv (x and y; duo processing)
            {
                kernelAreaDotProd_X += (int)convSrcImg.at<uchar>(row, col) * kernel_vertical[kernelRow][kernelCol];
                kernelAreaDotProd_Y += (int)convSrcImg.at<uchar>(row, col) * kernel_horizontal[kernelRow][kernelCol];
                kernelCol++;
            }

            kernelCol = 0;
            kernelRow++;
        }

        kernelRow = 0; kernelCol = 0;

        if (convDstCol <= convDstImg.cols - 2)
        {
            gradient = kernelAreaDotProd_X * kernelAreaDotProd_X + kernelAreaDotProd_Y * kernelAreaDotProd_Y;
            
            if (gradient > 10000) convDstImg.at<uchar>(convDstRow, convDstCol) = 255; // ReLU thresholding
            else convDstImg.at<uchar>(convDstRow, convDstCol) = 0;
            
            convDstCol++;
        }
        else
        {
            convDstRow++; convDstCol = 1;
            gradient = kernelAreaDotProd_X * kernelAreaDotProd_X + kernelAreaDotProd_Y * kernelAreaDotProd_Y;
            
            if (gradient > 10000) convDstImg.at<uchar>(convDstRow, convDstCol) = 255; // ReLU thresholding
            else convDstImg.at<uchar>(convDstRow, convDstCol) = 0;
            
            convDstCol++;
        }
        
        if (convCol < convSrcImg.cols - KERNEL_X) convCol++;
        else { convRow++; startCol = 0; }
        
        kernelAreaDotProd_X = 0;
        kernelAreaDotProd_Y = 0;
    }
   
    cout << "Vision2D :: PROCESS COMPLETE ..." << endl << endl;
    
    return convDstImg;
}
