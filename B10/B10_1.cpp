#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include<iostream>
using namespace std;
using namespace cv;

Mat image,dst1,dst2;
int g_thresh, n, c, m;
void on_global_trackbar(int, void*)
{
	for(int i=0;i<image.rows;i++)
	{
		for(int j=0; j<image.cols;j++)
		{
			if(image.at<uchar>(i,j) > g_thresh)
				dst1.at<uchar>(i,j) = 255;
			else
				dst1.at<uchar>(i,j) = 0;
		}
	}
	imshow("GLOBAL THRESH", dst1);
}
void on_adaptive_trackbar(int, void*)
{
	if(n==0)
		n++;
	n = n*10;	
	for(int i=0; i < image.rows; i++)
	{
		for(int j=0; j<image.cols;j++)
		{
			Mat tmp;
			getRectSubPix(image , Size(n,n), Point(j,i), tmp);
			m = mean(tmp)[0];
			if(m - image.at<uchar>(i,j)<c)
				dst2.at<uchar>(i,j) = 255;
			else
				dst2.at<uchar>(i,j) = 0;
		}
	}
	n = n/10;
	imshow("ADAPTIVE THRESH",dst2);
}
void global_thresh()
{
	namedWindow("GLOBAL THRESH", CV_WINDOW_AUTOSIZE);
	createTrackbar("Threshold","GLOBAL THRESH",&g_thresh, 255, on_global_trackbar);
	cout<<"Hello";
	imshow("GLOBAL THRESH", dst1);
}
void adaptive_thresh()
{
	namedWindow("ADAPTIVE THRESH", CV_WINDOW_AUTOSIZE);
	createTrackbar("N/10:", "ADAPTIVE THRESH", &n, 15 , on_adaptive_trackbar);
	createTrackbar("c:", "ADAPTIVE THRESH", &c, 10 , on_adaptive_trackbar);

	imshow("ADAPTIVE THRESH", dst2);
}
int main()
{
	image = imread("Lenna.png",CV_LOAD_IMAGE_GRAYSCALE);
	if(!image.data)
	{
		cout<<"INVALID IMAGE";
		return -1;
	}
	image.copyTo(dst1);
	image.copyTo(dst2);
	
	namedWindow("NORMAL IMAGE",CV_WINDOW_AUTOSIZE);	
	imshow("NORMAL IMAGE",image);
	global_thresh();
	adaptive_thresh();
	waitKey(0);
	return 0;
}
