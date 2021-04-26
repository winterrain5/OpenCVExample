//
//  Chapter4.cpp
//  OpenCVMacDemo
//
//  Created by VICTOR03 on 2021/4/25.
//

#include "Chapter4.hpp"
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void Chapter4::calcHist() {
    Mat img = imread("/Users/victor03/Desktop/images/test1.jpeg");
    Mat gray;
    // 将图像转成单通道灰度图像
    cvtColor(img, gray, COLOR_BGR2GRAY);
    
    Mat hist; // 存储直方图计算结果
    const int channels[1] = { 0 };// 通道索引
    float inRanges[2] = { 0,255 }; //
    const float *rangs[1] = { inRanges }; // 像素灰度值范围
    const int bins[1] = { 256 }; // 直方图的维度，即像素灰度值的最大值
    cv::calcHist(&gray, 1, channels, Mat(), hist, 1, bins, rangs);
    
    // 绘制直方图
    int hist_w = 512;
    int hist_h = 400;
    int width = 2;
    Mat histImage = Mat::zeros(hist_h, hist_w, CV_8UC3);
    for (int i = 1; i <= hist.rows; i++) {
        rectangle(histImage, Point(width*(i-1),hist_h-1), Point(width*i-1,hist_h - cvRound(hist.at<float>(i-1) / 15)), Scalar(255,255,255),-1);
    }
    // 归一化直方图
    Mat histImageL1 = Mat::zeros(hist_h, hist_w, CV_8UC3);
    Mat hist_L1;
    normalize(hist, hist_L1, 1, 0,NORM_L2,-1,Mat());
    for (int i = 0; i < hist_L1.rows; i++) {
        rectangle(histImageL1, Point(width*(i - 1), hist_h - 1),
                    Point(width*i - 1, hist_h - cvRound(hist_h*hist_L1.at<float>(i - 1)) - 1),
                    Scalar(255, 255, 255), -1);
    }
    imshow("gray", gray);
    imshow("hist", histImage);
    imshow("hist_L1", histImageL1);
    waitKey(0);
}

// 归一化并绘制直方图
void drawHist(Mat &hist,int type, String name) {
    int hist_w = 512;
    int hist_h = 400;
    int width = 2;
    Mat histImage = Mat::zeros(hist_h, hist_w, CV_8UC3);
    normalize(hist, hist, 1, type); // 归一化
    for (int i = 1; i <= hist.rows; i++) {
        rectangle(histImage, Point(width*(i-1),hist_h-1), Point(width*i-1,hist_h - cvRound(hist_h*hist.at<float>(i-1)) - 1), Scalar(255,255,255),-1);
    }
    imshow(name, histImage);
}

void Chapter4::compareHist() {
    Mat img = imread("/Users/victor03/Desktop/images/test1.jpeg");
    
    Mat gray, hist, gray2, hist2, gray3, hist3;
    
    cvtColor(img, gray, COLOR_BGR2GRAY);
    
    resize(gray, gray2, Size(),0.5,0.5);
    
    gray3 = imread("/Users/victor03/Desktop/images/test2.jpeg", IMREAD_GRAYSCALE);
    
    const int channels[1] = { 0 };// 通道索引
    float inRanges[2] = { 0,255 }; //
    const float *rangs[1] = { inRanges }; // 像素灰度值范围
    const int bins[1] = { 256 }; // 直方图的维度，即像素灰度值的最大值
    
    cv::calcHist(&gray, 1, channels, Mat(), hist, 1, bins, rangs);
    drawHist(hist, NORM_INF, "hist");
    
    cv::calcHist(&gray2, 1, channels, Mat(), hist2, 1, bins, rangs);
    drawHist(hist2, NORM_INF, "hist2");
    
    cv::calcHist(&gray3, 1, channels, Mat(), hist3, 1, bins, rangs);
    drawHist(hist3, NORM_INF, "hist3");
    
    // 原图与原图直方图的相关系数
    double  hist_hist = cv::compareHist(hist, hist, HISTCMP_CORREL);
    cout << "原图与原图直方图的相关系数" << hist_hist << endl;
    
    // 原图与缩小原图直方图的相关系数
    double  hist_hist2 = cv::compareHist(hist, hist2, HISTCMP_CORREL);
    cout << "原图与缩小原图直方图的相关系数" << hist_hist2 << endl;
    
    // 两幅不同图像直方图相关系数
    double  hist_hist3 = cv::compareHist(hist, hist3, HISTCMP_CORREL);
    cout << "两幅不同图像直方图相关系数" << hist_hist3 << endl;
    
    waitKey();
}

void Chapter4::equalizeHist() {
    Mat img = imread("/Users/victor03/Desktop/images/test4.jpeg");
    
    Mat gray, hist, hist2;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    
    Mat equalImage;
    cv::equalizeHist(gray, equalImage);// 将直方图均衡化
    
    const int channels[1] = {0};
    float inRanges[2] = { 0,255 }; //
    const float *rangs[1] = { inRanges }; // 像素灰度值范围
    const int bins[1] = { 256 }; // 直方图的维度，即像素灰度值的最大值
    
    cv::calcHist(&gray, 1, channels, Mat(), hist, 1, bins, rangs);
    drawHist(hist, NORM_INF, "hist");
    imshow("origin image", gray);
    
    cv::calcHist(&equalImage, 1, channels, Mat(), hist2, 1, bins, rangs);
    drawHist(hist2, NORM_INF, "hist2");
    imshow("equalize image", equalImage);
    
    waitKey();
}

void Chapter4::histMatch() {
    Mat img1 = imread("/Users/victor03/Desktop/images/test1.jpeg");
    Mat img2 = imread("/Users/victor03/Desktop/images/test2.jpeg");
    
    Mat hist1, hist2;
    // 计算两幅图像直方图
    const int channels[1] = {0};
    float inRanges[2] = { 0,255 }; //
    const float *rangs[1] = { inRanges }; // 像素灰度值范围
    const int bins[1] = { 256 }; // 直方图的维度，即像素灰度值的最大值
    cv::calcHist(&img1, 1, channels, Mat(), hist1, 1, bins, rangs);
    drawHist(hist1, NORM_INF, "hist");
    imshow("img1", img1);
    
    cv::calcHist(&img2, 1, channels, Mat(), hist2, 1, bins, rangs);
    drawHist(hist2, NORM_INF, "hist2");
    imshow("img2", img2);
    
    // 计算两幅图像直方图的累计概率
    float hist1_cdf[256] = { hist1.at<float>(0) };
    float hist2_cdf[256] = { hist2.at<float>(0) };
    for (int i = 0; i < 256; i++) {
        hist1_cdf[i] = hist1_cdf[i-1] + hist1.at<float>(i);
        hist2_cdf[i] = hist2_cdf[i-1] + hist2.at<float>(i);
    }
    // 构建累积概率误差矩阵
    float diff_cdf[256][256];
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            diff_cdf[i][j] = fabs(hist1_cdf[i] - hist1_cdf[j]);
        }
    }
    // 生成LUT
    Mat lut(1,256,CV_8U);
    for (int i = 0; i < 256; i++) {
        // 查找源灰度级为i的映射灰度
        // 与i的累计概率值最小的规定化灰度
        float min = diff_cdf[i][0];
        int index = 0;
        // 寻找累计概率误差矩阵中每一行中的最小值
        for (int j = 0; j < 256; j++) {
            if (min > diff_cdf[i][j]) {
                min = diff_cdf[i][j];
                index = j;
            }
        }
        lut.at<uchar>(i) = (uchar)index;
    }
    
    Mat result, hist3;
    LUT(img1, lut, result);
    cv::calcHist(&result, 1, channels, Mat(), hist3, 1, bins, rangs);
    drawHist(hist3, NORM_INF, "hist3");
    imshow("result", result);
    
    waitKey();
}

void Chapter4::matchTemplate() {
    Mat img = imread("/Users/victor03/Desktop/images/test5.jpeg");
    Mat temp = imread("/Users/victor03/Desktop/images/test5_sub.png");
    
    Mat result;
    cv::matchTemplate(img, temp, result, TM_CCOEFF_NORMED); // 模板匹配
    
    double maxVal, minVal;
    Point minLoc, maxLoc;
    // 寻找匹配结果中的最大值最小值以及坐标位置
    minMaxLoc(result, &minVal,&maxVal,&minLoc,&maxLoc);
    // 绘制最佳匹配区域
    rectangle(img, Rect(maxLoc.x,maxLoc.y,80,80), Scalar(0,0,255),2);
    
    imshow("origin", img);
    imshow("temp", temp);
    imshow("result", result);
    
    waitKey();
}
