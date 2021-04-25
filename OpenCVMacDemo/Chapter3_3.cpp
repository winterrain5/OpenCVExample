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

void Chapter3_3::imageWrapAffine() {
    Mat img = imread("/Users/victor03/Desktop/images/test1.jpeg");
    
    Mat rotation0, rotation1, img_wrap0, img_warp1;
    double angle = 30; // 设置图像旋转的角度
    Size dst_size(img.rows, img.cols); // 设置输出图像的尺寸
    Point2f center(img.rows / 2.0, img.cols / 2.0); // 输出图像的旋转中心
    
    rotation0 = getRotationMatrix2D(center, angle, 1); // 计算仿射变换矩阵
    warpAffine(img, img_wrap0, rotation0, dst_size);
    namedWindow("旋转仿射变换");
    imshow("旋转仿射变换", img_wrap0);
    
    // 根据定义的3个点进行仿射变换
    Point2f src_points[3];
    Point2f dst_points[3];
    // 原始图像中的3个点
    src_points[0] = Point2f(0,0);
    src_points[1] = Point2f(0, float(img.cols - 1));
    src_points[2] = Point2f(float(img.rows - 1),float(img.cols - 1));
    
    // 仿射变换后图像中的3个点
    dst_points[0] = Point2f(float(img.rows)*0.11, float(img.cols)*0.2);
    dst_points[1] = Point2f(float(img.rows)*0.15, float(img.cols)*0.7);
    dst_points[2] = Point2f(float(img.rows)*0.81, float(img.cols)*0.85);
    // 根据对应点求取仿射变换矩阵
    rotation1 = getAffineTransform(src_points, dst_points);
    warpAffine(img, img_warp1, rotation1, dst_size);
    namedWindow("三点旋转仿射变换");
    imshow("三点旋转仿射变换", img_warp1);
    
    waitKey();
}


void Chapter3_3::imageWarpPolar() {
    Mat img = imread("/Users/victor03/Desktop/images/clock.jpeg");
    
    Mat img1, img2;
    Point2f center = Point2f(img.cols / 2, img.rows / 2); // 极坐标在图像中的原点
    
    // 正极坐标变换
    warpPolar(img, img1, Size(300,600), center, center.x, INTER_LINEAR + WARP_POLAR_LINEAR);
    // 逆极坐标变换
    warpPolar(img1, img2, Size(img.rows,img.cols), center, center.x, INTER_LINEAR + WARP_POLAR_LINEAR + WARP_INVERSE_MAP);
    
//    imshow("原表盘图", img);
    imshow("表盘极坐标变换结果", img1);
    imshow("逆变换结果", img2);
    
    waitKey();
}
