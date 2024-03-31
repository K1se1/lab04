#include<iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

//делает карту границ изображений(не самым эффективным способом)
cv::Mat* make_diff_map(const cv::Mat& img, int detal)
{
    int rows = img.rows;
    int cols = img.cols;
    cv::Vec3b energy;
    auto find_mid{[](const cv::Vec3b &v1, const cv::Vec3b &v2){return v1/2+v2/2;}};
    auto calcdeep{ [](cv::Vec3b &energy){return sqrt((energy[0]*energy[0]+energy[1]*energy[1]+energy[2]*energy[2]));} }; // страшная функция для посчета пикселся
    const cv::Vec3b *ptr;
    uint16_t *ptrmap;
    cv::Mat* map = new cv::Mat(rows, cols, CV_16UC1 , cv::Scalar(0));
    for(int r = 1; r < rows-1; ++r)
    {
        ptr = img.ptr<cv::Vec3b>(r);
        ptrmap = map->ptr<uint16_t>(r);
        for(int c = 1; c < cols-1; ++c)
        {
            energy = ptr[c]-find_mid(find_mid(find_mid(img.ptr<cv::Vec3b>(r+1)[c], img.ptr<cv::Vec3b>(r-1)[c]), 
                                find_mid(img.ptr<cv::Vec3b>(r)[c-1], img.ptr<cv::Vec3b>(r)[c+1])), 
                                find_mid(find_mid(img.ptr<cv::Vec3b>(r+1)[c-1], img.ptr<cv::Vec3b>(r+1)[c+1]),
                                find_mid(img.ptr<cv::Vec3b>(r-1)[c-1], img.ptr<cv::Vec3b>(r-1)[c+1])));

                ptrmap[c] = calcdeep(energy)*1000;
        }
    }
    return map;
}



int main()

{
    cv::Mat img = cv::imread("C:\\Labs\\Lab04\\img1.jpg");
    if (img.empty()) {
        std::cout << "Error: Could not load the image.\n";
        return 1;
    }
    cv::Mat* img1 = make_diff_map(img, 1);
    cv::imshow("Hello!", *img1);
    cv::waitKey();
    return 0;
}
