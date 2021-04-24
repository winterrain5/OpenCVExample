//
//  Chapter3.cpp
//  OpenCVMacDemo
//
//  Created by VICTOR03 on 2021/4/22.
//

#include "Chapter3.hpp"
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void Chapter3::colorConvert() {
    Mat img = imread("/Users/victor03/Desktop/images/test.jpeg");
    
    Mat gray, HSV, YUV, Lab, img32;
    img.convertTo(img32, CV_32F, 1.0 / 255); // 将cv_8u类型转成cv_32f
    cvtColor(img32, HSV, COLOR_BGR2HSV);
    cvtColor(img32, YUV, COLOR_BGR2YUV);
    cvtColor(img32, Lab, COLOR_BGR2Lab);
    cvtColor(img32, gray, COLOR_BGR2GRAY);
    
    imshow("原图", img32);
    imshow("HSV", HSV);
    imshow("YUV", YUV);
    imshow("Lab", Lab);
    imshow("gray", gray);
    
    waitKey(0);
}

void Chapter3::splitAndMerge() {
    Mat img = imread("/Users/victor03/Desktop/images/test.jpeg");
    
    Mat HSV;
    cvtColor(img, HSV, COLOR_BGR2HSV);
    Mat imgs0, imgs1, imgs2; // 用于存放数组类型的结果
    Mat imgv0, imgv1, imgv2; // 用于存放vector类型的结果
    Mat result0, result1, result2; // 多通道合并的结果
    
    // 输入数组参数的多通道分离与合并
    Mat imgs[3];
    split(img, imgs);
    imgs0 = imgs[0];
    imgs1 = imgs[1];
    imgs2 = imgs[2];
    imshow("RGB-B通道", imgs0);
    imshow("RGB-G通道", imgs1);
    imshow("RGB-R通道", imgs2);
//    imgs[2] = img; // 将数组中的图像通道数变成不一致
//    merge(imgs, 3, result0); // 合并图像

    Mat zero = Mat::zeros(img.rows, img.cols, CV_8UC1);
    imgs[0] = zero;
    imgs[2] = zero;
    merge(imgs, 3, result1);
    imshow("result1", result1);
    
    vector<Mat> imgv;
    split(HSV, imgv);
    imgv0 = imgv.at(0);
    imgv1 = imgv.at(1);
    imgv2 = imgv.at(2);
    
    imshow("HSV-H通道", imgv0);
    imshow("HSV-S通道", imgv1);
    imshow("HSV-V通道", imgv2);
    imgv.push_back(HSV);
//    merge(imgv, result2);
//    imshow("result2", result2);
    
    waitKey(0);
}

void Chapter3::findMinAndMax(){
    float a[12] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 0};
    Mat img = Mat(3, 4, CV_32FC1, a);
    double minVal, maxVal; // 用于存放矩阵的最大值和最小值
    Point minIdx, maxIdx; // 用于存放矩阵中的最大值和最小值在矩阵的位置
    
    minMaxLoc(img, &minVal, &maxVal, &minIdx, &maxIdx);
    cout << "img中最大值" << maxVal << "在矩阵中的位置" << maxIdx << endl;
    cout << "img中最小值" << minVal << "在矩阵中的位置" << minIdx << endl;
}

void Chapter3::twoImageCompare() {
    Mat img0 = imread("/Users/victor03/Desktop/images/test.jpeg");
    Mat img1 = imread("/Users/victor03/Desktop/images/test1.jpeg");
    
    Mat comMin, comMax;
    max(img0, img1, comMax);
    min(img0, img1, comMin);
    imshow("comMin", comMin);
    imshow("comMax", comMax);
    
    // 与掩模进行比较运算
    Mat scr1 = Mat::zeros(419, 500, CV_8UC3);
    Rect rect(0,0,300,300);
    scr1(rect) = Scalar(255,255,255);// 生成一个低通300*300的掩模
    
    Mat comsrc1;
    min(img1, scr1, comsrc1);
    imshow("comsrc1", comsrc1);
    
    
    waitKey(0);
}

void Chapter3::logicOpreration() {
    Mat img = imread("/Users/victor03/Desktop/images/test1.jpeg");
    
    // 创建两个黑白图像
    Mat img0 = Mat::zeros(200, 200, CV_8UC1);
    Rect rect0(50,50,100,100);
    img0(rect0) = Scalar(255);
    
    Mat img1 = Mat::zeros(200, 200, CV_8UC1);
    Rect rect1(100,100,100,100);
    img1(rect1) = Scalar(255);
    
    imshow("img0", img0);
    imshow("img1", img1);
    
    // 进行逻辑运算
    Mat mand, mOr, mXor, mNot, imgNot;
    bitwise_not(img0, mNot);
    bitwise_or(img0, img1, mOr);
    bitwise_and(img0, img1, mand);
    bitwise_xor(img0, img1, mXor);
    bitwise_not(img, imgNot);
    
    imshow("mNot", mNot);
    imshow("mOr", mOr);
    imshow("mXor", mXor);
    imshow("mand", mand);
    imshow("imgNot", imgNot);
    
    waitKey(0);
}

void Chapter3::imageBinarization() {
    Mat img = imread("/Users/victor03/Desktop/images/test1.jpeg");
    
    Mat gray;
    cvtColor(img, gray, COLOR_RGB2GRAY);
    Mat img_B, img_B_V, grayB, gray_B_V, gray_T, gray_T_V;
    
    // 彩色图像二值化
    threshold(img, img_B, 125, 255, THRESH_BINARY);
    threshold(img, img_B_V, 125, 255, THRESH_BINARY_INV);
    imshow("img_B", img_B);
    imshow("img_B_V", img_B_V);
    
    // 灰度图像二值化
    threshold(gray, grayB, 125, 255, THRESH_BINARY);
    threshold(gray, gray_B_V, 125, 255, THRESH_BINARY_INV);
    imshow("grayB", grayB);
    imshow("gray_B_V", gray_B_V);
    
    // 灰度图像TOZERO变换
    threshold(gray, gray_T, 125, 255, THRESH_TOZERO);
    threshold(gray, gray_T_V, 125, 255, THRESH_TOZERO_INV);
    imshow("gray_T", gray_T);
    imshow("gray_T_V", gray_T_V);
    
    waitKey();
}
