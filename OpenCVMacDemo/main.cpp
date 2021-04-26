//
//  main.cpp
//  OpenCVMacDemo
//
//  Created by VICTOR03 on 2021/4/22.
//
#include "Chapter2.hpp"
#include "Chapter3.hpp"
#include "Chapter4.hpp"
#include <iostream>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


int main(int argc, const char * argv[]) {
    
    Chapter4 demo;
    demo.matchTemplate();

    return 0;
}


