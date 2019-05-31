#include <opencv2/opencv.hpp>
#include <iostream>


using namespace cv;
using namespace std;

// 탐지율이 너무 낮음 

int main()
{
	Mat img_color, img_gray;
	Mat gray,edges,kernel, closed;

	//비디오 캡쳐 초기화
	VideoCapture cap(1);
	if (!cap.isOpened()) {
		cerr << "에러 - 카메라를 열 수 없습니다.\n";
		return -1;
	}

	while (1)
	{
		// 카메라로부터 캡쳐한 영상을 frame에 저장합니다.
		cap.read(img_color);

		cvtColor(img_color, img_gray, COLOR_BGR2GRAY);
		GaussianBlur(img_gray, img_gray, Size(5, 5), 0, 0);
		bilateralFilter(img_gray, gray, 11, 17,17);
		Canny(gray, edges, 0, 200,3, false);
		kernel = getStructuringElement(MORPH_RECT, Size(3, 3), Point(1, 1));
		morphologyEx(edges, closed, MORPH_CLOSE, kernel);

		//이진화 이미지로 변환
		//adaptiveThreshold(img_gray, img_gray, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 201, 7); //기존의 방식
		
		//contour를 찾는다.
		vector<vector<Point> > contours;
		//findContours(img_gray, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);
		findContours(closed, contours, RETR_LIST, CHAIN_APPROX_NONE);// 파이썬에서 사용한 경우

		//contour를 근사화한다.
		Mat img_result;
		vector<Point2f> approx;
		img_result = img_color.clone();

		if (img_color.empty()) {
			cerr << "빈 영상\n";
			break;
		}
		for (size_t i = 0; i < contours.size(); i++)
		{
			approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);

			if (fabs(contourArea(Mat(approx))) > 50000 && fabs(contourArea(Mat(approx))) < 200000) 
			{
				int size = approx.size();
				// 사각형을 탐지하고 각 점을 연결 
				if (size == 4) {
					for (int k = 0; k <= size - 1; k++) {
						if(k==size-1)line(img_result, approx[k], approx[0], Scalar(0, 255, 255), 3);
						else line(img_result, approx[k], approx[k + 1], Scalar(0, 255, 255), 3);
					}
				}
			}
		}

		// 영상을 화면에 보여줍니다. 
		imshow("Color", img_color);
		imshow("Gray", closed);
		imshow("Result", img_result);


		// ESC 키를 입력하면 루프가 종료됩니다. 

		if (waitKey(25) >= 0)
			break;
	}

	return 0;
}
