#include <opencv2/opencv.hpp>
#include <iostream>


using namespace cv;
using namespace std;

// Ž������ �ʹ� ���� 

int main()
{
	Mat img_color, img_gray;
	Mat gray,edges,kernel, closed;

	//���� ĸ�� �ʱ�ȭ
	VideoCapture cap(1);
	if (!cap.isOpened()) {
		cerr << "���� - ī�޶� �� �� �����ϴ�.\n";
		return -1;
	}

	while (1)
	{
		// ī�޶�κ��� ĸ���� ������ frame�� �����մϴ�.
		cap.read(img_color);

		cvtColor(img_color, img_gray, COLOR_BGR2GRAY);
		GaussianBlur(img_gray, img_gray, Size(5, 5), 0, 0);
		bilateralFilter(img_gray, gray, 11, 17,17);
		Canny(gray, edges, 0, 200,3, false);
		kernel = getStructuringElement(MORPH_RECT, Size(3, 3), Point(1, 1));
		morphologyEx(edges, closed, MORPH_CLOSE, kernel);

		//����ȭ �̹����� ��ȯ
		//adaptiveThreshold(img_gray, img_gray, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 201, 7); //������ ���
		
		//contour�� ã�´�.
		vector<vector<Point> > contours;
		//findContours(img_gray, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);
		findContours(closed, contours, RETR_LIST, CHAIN_APPROX_NONE);// ���̽㿡�� ����� ���

		//contour�� �ٻ�ȭ�Ѵ�.
		Mat img_result;
		vector<Point2f> approx;
		img_result = img_color.clone();

		if (img_color.empty()) {
			cerr << "�� ����\n";
			break;
		}
		for (size_t i = 0; i < contours.size(); i++)
		{
			approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);

			if (fabs(contourArea(Mat(approx))) > 50000 && fabs(contourArea(Mat(approx))) < 200000) 
			{
				int size = approx.size();
				// �簢���� Ž���ϰ� �� ���� ���� 
				if (size == 4) {
					for (int k = 0; k <= size - 1; k++) {
						if(k==size-1)line(img_result, approx[k], approx[0], Scalar(0, 255, 255), 3);
						else line(img_result, approx[k], approx[k + 1], Scalar(0, 255, 255), 3);
					}
				}
			}
		}

		// ������ ȭ�鿡 �����ݴϴ�. 
		imshow("Color", img_color);
		imshow("Gray", closed);
		imshow("Result", img_result);


		// ESC Ű�� �Է��ϸ� ������ ����˴ϴ�. 

		if (waitKey(25) >= 0)
			break;
	}

	return 0;
}
