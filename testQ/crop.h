#include <iostream>
#include <math.h>
#include <stdio.h>
#include <windows.h>
#include <list>

#include "opencv2/opencv.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
// 환경에 따라 헤더파일을 변경
//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgproc/imgproc.hpp"

typedef struct POS
{
	vector<Point2f> corner_points;
	vector<Point2f> quad_pnts;
};

using namespace std;
using namespace cv;

int point_num;
int point_x1, point_x2, point_x3, point_x4;
int point_y1, point_y2, point_y3, point_y4;

Mat img_color, quad, transmtx;
int radius = 3;
int flag = 0;
int pos[8];

void sortCorners(vector<Point2f> & corner_points, Point2f centerpoint);
void mouseHandler(int event, int x, int y, int flags, void *param);
POS p;

int* crop(VideoCapture cap){
	point_num = 0;
	flag = 0;
	Point2f centerpoint(0, 0);

	point_x1 = 0, point_x2 = 0, point_x3 = 0, point_x4 = 0;
	point_y1 = 0, point_y2 = 0, point_y3 = 0, point_y4 = 0;

	if (!cap.isOpened()) {
		cerr << "에러 - 카메라를 열 수 없습니다.\n";
	}
	// DELETE AFTER DEVISE
	string myText;
	Point myPoint;

	// DELETE AFTER DEVISE
	
	while (1)
	{
		// 카메라로부터 캡쳐한 영상을 frame에 저장합니다.
		cap.read(img_color);
		namedWindow("RawDisplay", WINDOW_AUTOSIZE);

		//점을 찍어 보자 
		circle(img_color, Point2f(point_x1, point_y1), radius, CV_RGB(0, 255, 0), 2);
		circle(img_color, Point2f(point_x2, point_y2), radius, CV_RGB(0, 255, 0), 2);
		circle(img_color, Point2f(point_x3, point_y3), radius, CV_RGB(0, 255, 0), 2);
		circle(img_color, Point2f(point_x4, point_y4), radius, CV_RGB(0, 255, 0), 2);

		// DELETE AFTER DEVISE
		myText = "[" + to_string(point_x1) + ", " + to_string(point_y1) + "]";
		myText = myText + ", " + "[" + to_string(point_x2) + ", " + to_string(point_y2) + "]";
		myText = myText + ", " + "[" + to_string(point_x3) + ", " + to_string(point_y3) + "]";
		myText = myText + ", " + "[" + to_string(point_x4) + ", " + to_string(point_y4) + "]";

		if (point_x1 == 0) {
			myText = "Please take the coordinates in the order of upper left, upper right, lower left, and lower right.";
		}
		myPoint.x = 10;
		myPoint.y = 40;
		putText(img_color, myText, myPoint, 2, 0.4, Scalar::all(255));

		// DELETE AFTER DEVISE
		
		imshow("RawDisplay", img_color);

		setMouseCallback("RawDisplay", mouseHandler, 0);
		
		if (point_num % 4 == 0 && (point_num + flag) != 0) {
			pos[0] = point_x1;
			pos[1] = point_y1;
			pos[2] = point_x2;
			pos[3] = point_y2;
			pos[4] = point_x3;
			pos[5] = point_y3;
			pos[6] = point_x4;
			pos[7] = point_y4;


		/*
			Mat dstImg = img_color.clone();

			// corner point -> Point2f -> array
			Point2f pt1 = Point2f(point_x1, point_y1);
			Point2f pt2 = Point2f(point_x2, point_y2);
			Point2f pt3 = Point2f(point_x3, point_y3);
			Point2f pt4 = Point2f(point_x4, point_y4);
			//Point2f pts[] = { pt1, pt2, pt3, pt4 };
			Point2f pts[] = { pt1, pt2, pt3, pt4 };

			// array -> vector<Point2f>

			vector<Point2f> corner_points(pts, pts + sizeof(pts) / sizeof(pts[0]));


			// 중심점을 찍어보자

			for (int i = 0; i < corner_points.size(); i++) {
				centerpoint += corner_points[i];
			}

			centerpoint *= (1. / corner_points.size());
			sortCorners(corner_points, centerpoint);

			// 코너에 동그라미를 출력 

			circle(dstImg, corner_points[0], radius, CV_RGB(0, 255, 0), 2);
			circle(dstImg, corner_points[1], radius, CV_RGB(0, 255, 0), 2);
			circle(dstImg, corner_points[2], radius, CV_RGB(0, 255, 0), 2);
			circle(dstImg, corner_points[3], radius, CV_RGB(0, 255, 0), 2);

			// draing weighted center

			
			//circle(dstImg, centerpoint, 3, CV_RGB(0, 0, 255), 2);
			//printf("corner_points[0] : (%lf, %lf)\n", corner_points[0].x, corner_points[0].y);
			//printf("corner_points[1] : (%lf, %lf)\n", corner_points[1].x, corner_points[1].y);
			//printf("corner_points[2] : (%lf, %lf)\n", corner_points[2].x, corner_points[2].y);
			//printf("corner_points[3] : (%lf, %lf)\n", corner_points[3].x, corner_points[3].y);
			
			// calculate result image's corner points

			// www의 크기를 조정할 수 있음.
			double width_x = pow(abs(corner_points[1].x - corner_points[0].x), 2);
			double width_y = pow(abs(corner_points[1].y - corner_points[0].y), 2);
			double quad_width = sqrt(abs(width_x + width_y)) + 200;//0.5
			double height_x = pow(abs(corner_points[3].x - corner_points[0].x), 2);
			double height_y = pow(abs(corner_points[3].y - corner_points[0].y), 2);
			double quad_height = sqrt(abs(height_x + height_y)) + 200; //0.5

			//Mat quad = Mat::zeros((int)quad_height, (int)quad_width, CV_8UC3);
			quad = Mat::zeros((int)quad_height, (int)quad_width, CV_8UC3);

			vector<Point2f> quad_pnts;
			quad_pnts.push_back(Point2f(0, 0));
			quad_pnts.push_back(Point2f(quad.cols, 0));
			quad_pnts.push_back(Point2f(quad.cols, quad.rows));
			quad_pnts.push_back(Point2f(0, quad.rows));

			//destroyWindow("RawDisplay");
			//waitKey(1);

			//p.corner_points = corner_points;
			//p.quad_pnts = quad_pnts;

			// Perspecitive Transformaion (tooshi transform)
			
			//Mat transmtx = getPerspectiveTransform(corner_points, quad_pnts);
			
			if (flag == 0) {
				transmtx = getPerspectiveTransform(corner_points, quad_pnts);
			}
			warpPerspective(img_color, quad, transmtx, quad.size());
			
			//여기서 동영상으로 출력
			
			//namedWindow("original image", WINDOW_AUTOSIZE); 
			//namedWindow("CropDisplay", WINDOW_AUTOSIZE);
			//imshow("original image", dstImg);
			//imshow("CropDisplay", quad);
			
			//ESC키 입력시 종료
			
			//if (waitKey(25) >= 0)
			//	break;
		*/	
			flag = 1;
		}
		
		waitKey(27);

		if (flag == 1) {
			break;
		}
	}
	destroyWindow("RawDisplay");
	return pos;
}

void sortCorners(vector<Point2f> & corner_points, Point2f centerpoint)
{
	vector<Point2f> top, bot;

	for (int i = 0; i < corner_points.size(); i++) {
		if (corner_points[i].y < centerpoint.y) {
			top.push_back(corner_points[i]);
		}
		else {
			bot.push_back(corner_points[i]);
		}
	}
	Point2f tl = top[0].x > top[1].x ? top[1] : top[0];
	Point2f tr = top[0].x > top[1].x ? top[0] : top[1];
	Point2f bl = bot[0].x > bot[1].x ? bot[1] : bot[0];
	Point2f br = bot[0].x > bot[1].x ? bot[0] : bot[1];

	corner_points.clear();
	corner_points.push_back(tl);
	corner_points.push_back(tr);
	corner_points.push_back(br);
	corner_points.push_back(bl);
}

void mouseHandler(int event, int x, int y, int flags, void *param)

{
	if (event == EVENT_LBUTTONDOWN) {
		cout << "ohhhhh" << endl;
		if (point_num % 4 == 0) {
			point_x1 = x;
			point_y1 = y;
		}
		else if (point_num % 4 == 1) {
			point_x2 = x;
			point_y2 = y;
		}
		else if (point_num % 4 == 2) {
			point_x3 = x;
			point_y3 = y;
		}
		else if (point_num % 4 == 3) {
			point_x4 = x;
			point_y4 = y;
		}
		point_num++;
		cout << point_num << endl;
	}
}