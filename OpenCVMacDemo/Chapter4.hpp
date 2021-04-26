//
//  Chapter4.hpp
//  OpenCVMacDemo
//
//  Created by VICTOR03 on 2021/4/25.
//

#ifndef Chapter4_hpp
#define Chapter4_hpp

#include <stdio.h>

class Chapter4 {
        
    
public:
    // 绘制图像直方图
    void calcHist();
    // 直方图比较
    void compareHist();
    // 直方图均衡化 对比度增强
    void equalizeHist();
    // 直方图匹配
    void histMatch();
    // 模板匹配
    void matchTemplate();
};

#endif /* Chapter4_hpp */
