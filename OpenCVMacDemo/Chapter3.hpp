//
//  Chapter3.hpp
//  OpenCVMacDemo
//
//  Created by VICTOR03 on 2021/4/22.
//

#ifndef Chapter3_hpp
#define Chapter3_hpp

#include <stdio.h>

class Chapter3 {
public:
    void colorConvert();
    void splitAndMerge();
    void findMinAndMax();
    void twoImageCompare();
    void logicOpreration();
    // 二值化
    void imageBinarization();
    // 图片合并
    void imageConcat();
    // 灰度值映射
    void imageLUT();
    // 仿射变换
    void imageWrapAffine();
    // 极坐标变换
    void imageWarpPolar();
    // 高斯金字塔和拉普拉斯金字塔
    void imagePyramid();
};

#endif /* Chapter3_hpp */
