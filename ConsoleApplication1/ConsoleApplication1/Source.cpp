#include "opencv2\opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

const int alpha_slider_max = 400;
int color_rad;

 Mat original ;
int alpha_slider = 100;
int color_center[3];




void color_slicing(int alpha_slider) {


	Mat modified = original.clone();

	for (int r = 0; r < original.rows; r++) {
		for (int c = 0; c < original.cols; c++) {
			
			if (sqrt(pow((original.at<cv::Vec3b>(r, c)[0] - color_center[0]), 2) + pow((original.at<cv::Vec3b>(r, c)[1] - color_center[1]), 2) + pow((original.at<cv::Vec3b>(r, c)[2] - color_center[2]), 2)) > alpha_slider) {
				int average = (original.at<cv::Vec3b>(r, c)[0] + original.at<cv::Vec3b>(r, c)[1] + original.at<cv::Vec3b>(r, c)[2]) / 3;
				modified.at<cv::Vec3b>(r, c)[0] = average;
				modified.at<cv::Vec3b>(r, c)[1] = average;
				modified.at<cv::Vec3b>(r, c)[2] = average;
			}

		}
		//cout << r << endl;
		
	}

	imshow("Color", modified);
	
	
	
}

void onmouse(int event, int x, int y, int d, void *)
{
	if (event == EVENT_LBUTTONDOWN) // lbutton down
	{
		
		
		color_center[0] = original.at<cv::Vec3b>(y, x)[0];
		color_center[1] = original.at<cv::Vec3b>(y, x)[1];
		color_center[2] = original.at<cv::Vec3b>(y, x)[2];

		color_slicing(alpha_slider);
		
		cout << "R:" << color_center[2] << "; G:" << color_center[1] << "; B:" << color_center[0] << "; " << endl;
	}

}



void on_trackbar(int alpha_slider, void*)
{


	color_slicing(alpha_slider);
	
}





int main(int argv, char** argc)
{
	
	//image uploading
	//original = imread("parrot.jpg", CV_LOAD_IMAGE_UNCHANGED);

	//modified = Mat::zeros(original.size(), CV_8UC1);

	VideoCapture vid(0); // open the default camera
	if (!vid.isOpened())  // check if we succeeded
		return -1;


	while (vid.read(original)) {


		//creating the button
	

		//Creating the trackbar
		

		namedWindow("Color", CV_WINDOW_FREERATIO);
		char TrackbarName[50];
		sprintf_s(TrackbarName, "Alpha x %d", alpha_slider_max);
		createTrackbar(TrackbarName, "Color", &alpha_slider, alpha_slider_max, on_trackbar);
		on_trackbar(alpha_slider, 0);

		//set the callback function for any mouse event
		setMouseCallback("Color", onmouse, 0);

		
		


		if (waitKey(30) >= 0) break;



	}
	


return 1;





}
	

