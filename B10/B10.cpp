#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat src, dst1, dst2;
int g_thresh, n, c, m;

void on_global_trackbar(int, void*)
{
    for(int i = 0; i < src.rows; i++)
        for(int j = 0; j < src.cols; j++)
            if(src.at<uchar>(i, j) > g_thresh)
                dst1.at<uchar>(i, j) = 255;
            else
                dst1.at<uchar>(i, j) = 0;
    imshow("Global Thresholding", dst1);
}

void global_thresh()
{
    namedWindow("Global Thresholding", CV_WINDOW_AUTOSIZE);
    createTrackbar("Threshold", "Global Thresholding", &g_thresh, 255, on_global_trackbar);
    imshow("Global Thresholding", dst1);
}

void on_adaptive_trackbar(int, void*)
{
    if(n == 0)
        n++;
    n *= 10;
    for(int i = 0; i < src.rows; i++)
        for(int j = 0; j < src.cols; j++)
        {
            Mat tmp;
            getRectSubPix(src, Size(n, n), Point(j, i), tmp);
            m = mean(tmp)[0];
            if(m - src.at<uchar>(i, j) < c)
                dst2.at<uchar>(i, j) = 255;
            else
                dst2.at<uchar>(i, j) = 0;
        }
    n /= 10;
    imshow("Adaptive Thresholding", dst2);
}

void adaptive_thresh()
{
    namedWindow("Adaptive Thresholding", CV_WINDOW_AUTOSIZE);
    createTrackbar("N/10: ", "Adaptive Thresholding", &n, 15, on_adaptive_trackbar);
    createTrackbar("C: ", "Adaptive Thresholding", &c, 10, on_adaptive_trackbar);
    imshow("Adaptive Thresholding", dst2);
}

int main()
{
	src = imread("Lenna.png", CV_LOAD_IMAGE_GRAYSCALE);
	if(!src.data)
    {
        cout<<"Error opening file.\n";
        return -1;
    }
    src.copyTo(dst1);
    src.copyTo(dst2);
	namedWindow("Source Image", CV_WINDOW_AUTOSIZE);
	imshow("Source Image", src);
	global_thresh();
	adaptive_thresh();
	waitKey(0);
	return 0;
}
