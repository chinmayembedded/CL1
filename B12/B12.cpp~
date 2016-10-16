#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat src, dst[4];

int main()
{
    src = imread("m1.png", 1);
	if(!src.data)
    {
        cout<<"Error opening file.\n";
        return -1;
    }
    namedWindow("Source Image", CV_WINDOW_AUTOSIZE);
    imshow("Source Image", src);
    waitKey(0);

    for(int i = 0; i < 4; i++)
        dst[i] = Mat::zeros(src.size(), CV_8UC3);

    Vec3b means[3] = { Vec3b(0, 0, 0), Vec3b(0, 0, 0), Vec3b(0, 0, 0) };
    Vec3b newmeans[3] = { Vec3b(200, 0, 0), Vec3b(0, 200, 0), Vec3b(0, 0, 200) };
    float d[3], n[3], sum[3][3];
    int small;

    while (means[0] != newmeans[0] || means[1] != newmeans[1] || means[2] != newmeans[2])
    {
        for(int i = 0; i < 3; i++)
        {
            d[i] = 0;
            n[i] = 0;
            means[i] = newmeans[i];
            newmeans[i] = Vec3b(0, 0, 0);
            for(int j = 0; j < 3; j++)
                sum[i][j] = 0;
        }
        for(int i = 0; i < src.rows; i++)
            for(int j = 0; j < src.cols; j++)
            {
                for(int k = 0; k < 3; k++)
                    d[k] = norm(means[k]-src.at<Vec3b>(i, j));

                if(d[0] < d[1] && d[0] < d[2])
                    small = 0;
                else if(d[1] < d[2])
                    small = 1;
                else
                    small = 2;

                for(int k = 0; k < 3; k++)
                    sum[small][k] += src.at<Vec3b>(i, j)[k];

                n[small]++;
                dst[0].at<Vec3b>(i, j) = means[small];
            }

        for(int i = 0; i < 3; i++)
            for(int j = 0; j < 3; j++)
                newmeans[i][j] = sum[i][j]/n[i];
    }
    namedWindow("Segmented Image", CV_WINDOW_AUTOSIZE);
    imshow("Segmented Image", dst[0]);

    for(int i = 0; i < src.rows; i++)
        for(int j = 0; j < src.cols; j++)
            if(dst[0].at<Vec3b>(i, j) == means[0])
                dst[1].at<Vec3b>(i, j) = src.at<Vec3b>(i, j);
            else if(dst[0].at<Vec3b>(i, j) == means[1])
                dst[2].at<Vec3b>(i, j) = src.at<Vec3b>(i, j);
            else
                dst[3].at<Vec3b>(i, j) = src.at<Vec3b>(i, j);

    namedWindow("Segment 1", CV_WINDOW_AUTOSIZE);
    imshow("Segment 1", dst[1]);
    namedWindow("Segment 2", CV_WINDOW_AUTOSIZE);
    imshow("Segment 2", dst[2]);
    namedWindow("Segment 3", CV_WINDOW_AUTOSIZE);
    imshow("Segment 3", dst[3]);
    waitKey(0);
    return 0;
}
