//
//  Chapter3_3.cpp
//  OpenCVMacDemo
//
//  Created by VICTOR03 on 2021/4/24.
//

#include "Chapter3_3.hpp"
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;
void Chapter3_3::imageConcat() {
    Mat img00 = imread("/Users/victor03/Desktop/images/test00.jpeg");
    Mat img01 = imread("/Users/victor03/Desktop/images/test01.jpeg");
    Mat img02 = imread("/Users/victor03/Desktop/images/test02.jpeg");
    Mat img03 = imread("/Users/victor03/Desktop/images/test03.jpeg");
    
    imshow("img00", img00);
    imshow("img01", img01);
    imshow("img02", img02);
    imshow("img03", img03);
    
    //图像连接
    Mat img1, img2, img3;
    // 图像横向连接
    hconcat(img00, img01, img1);
    hconcat(img02, img03, img2);
    // 横向连接后在竖向连接
    vconcat(img1, img2, img3);
    
    imshow("img1", img1);
    imshow("img2", img2);
    imshow("img3", img3);
    
    waitKey();
}
