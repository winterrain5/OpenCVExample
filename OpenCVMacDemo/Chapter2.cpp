//
//  Demo1.cpp
//  OpenCVMacDemo
//
//  Created by VICTOR03 on 2021/4/22.
//


#include <iostream>
#include <opencv2/opencv.hpp>
#include "Chapter2.hpp"

using namespace cv;
using namespace std;

void Chapter2::openVideo() {
    VideoCapture video("/Users/victor03/Desktop/OpenCVCourse/01 OpenCV图像处理视频课程/12-形态学操作.ts");
    
    if (video.isOpened()) {
        cout << "视频中图像的宽度=" << video.get(CAP_PROP_FRAME_WIDTH) << endl;
        cout << "视频中图像的高度=" << video.get(CAP_PROP_FRAME_HEIGHT) << endl;
        cout << "视频帧率=" << video.get(CAP_PROP_FPS) << endl;
        cout << "视频中图像的总帧数" << video.get(CAP_PROP_FRAME_COUNT) << endl;
    }else {
        cout << "视频名称错误" << endl;
    }
    while (1) {
        Mat frame;
        video >> frame;
        if (frame.empty()) {
            break;
        }
        imshow("video", frame);
        waitKey(1000 / video.get(CAP_PROP_FPS));
    }
}


void Chapter2::openCamera(){
    VideoCapture video = VideoCapture(0);
    
    cout << "视频中图像的宽度=" << video.get(CAP_PROP_FRAME_WIDTH) << endl;
    cout << "视频中图像的高度=" << video.get(CAP_PROP_FRAME_HEIGHT) << endl;
    cout << "视频帧率=" << video.get(CAP_PROP_FPS) << endl;
    
    while (1) {
        Mat frame;
        video >> frame;
        if (frame.empty()) {
            break;
        }
        imshow("video", frame);
        waitKey(1000 / video.get(CAP_PROP_FPS));
    }
}

void Chapter2::createAlphaMat() {
    Mat mat = Mat(480,640,CV_8UC4);
    for (int i = 0; i < mat.rows; ++i) {
        for (int j = 0; j < mat.cols; ++j) {
            Vec4b& bgra = mat.at<Vec4b>(i,j);
            bgra[0] = UCHAR_MAX; // 蓝色通道
            bgra[1] = saturate_cast<uchar>((float(mat.cols - j)) / ((float)mat.cols) * UCHAR_MAX); // 绿色通道
            bgra[2] = saturate_cast<uchar>((float(mat.rows - i)) / ((float)mat.rows) * UCHAR_MAX); // 红色通道
            bgra[3] = saturate_cast<uchar>(0.5 * (bgra[1] + bgra[2])); // alpha通道
        }
    }
    
    vector<int> compression_prarams;
    compression_prarams.push_back(IMWRITE_PNG_COMPRESSION); // png格式图像压缩标志
    compression_prarams.push_back(9); // 设置最高压缩质量
    bool result = imwrite("/Users/victor03/Desktop/alpha.png", mat, compression_prarams);
    if (!result) {
        cout << "保存png格式图片失败" << endl;
    }else {
        cout << "保存成功" << endl;
    }
}

void Chapter2::videoWrite() {
    Mat img;
    VideoCapture video(0);
    
    if (!video.isOpened()) {
        cout << "摄像头打开失败" << endl;
        return;
    }
    
    video >> img; // video 写入 img
    if (img.empty()) {
        cout << "没有获取到图像" << endl;
        return;
    }
    bool isColor = (img.type() == CV_8UC3); // 判断相机类型是否为彩色
    
    VideoWriter writer;
    int codec = VideoWriter::fourcc('M', 'J', 'P', 'G'); // 编码格式
    
    double fps = 20.0;// 设置帧率
    String fileName = "/Users/victor03/Desktop/live.avi";
    writer.open(fileName, codec, fps, img.size(),isColor); // 创建保存视频文件的视频流
    
    if (!writer.isOpened()) {
        cout << "打开视频文件失败，确认是否是合法输入" << endl;
        return;
    }
    
    while (1) {
        if (!video.read(img)) { // 判读能否继续从摄像头或者视频文件中读出一帧图像
            cout << "摄像头断开或者视频读取完成" << endl;
            return;
        }
        
        writer.write(img); // 图像写入视频流
        
        imshow("Live", img);
        char c = waitKey(50);
        if (c == 27){ // esc 退出
            break;
        }
    }
    
}
