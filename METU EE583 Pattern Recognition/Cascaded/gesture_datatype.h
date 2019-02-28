#ifndef __GESTURE_DATATYPE__
#define __GESTURE_DATATYPE__

#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iomanip>
#include <limits>
#include <cmath>
#include <sstream>
#include <cstring>
#include <stdio.h>
#include <fstream>
#include <cmath>
#include <vector>

using namespace cv;
using namespace std;


#define DEBUG_MODE 1

typedef enum
{
	EN_HAAR_KERNEL_TYPE_A = 0,	// 2 Region white(left) and black(right) e.g {{1, -1},{ 1, -1}}
	EN_HAAR_KERNEL_TYPE_B,	// 2 Region black(top) and white(down) e.g. {{-1 , -1}, {1, 1}}
	EN_HAAR_KERNEL_TYPE_C,  // 3 Region black(left) white(middle) and black(right) e.g. {{-1, 1, -1}, {-1, 1, -1}, {-1, 1, -1}} 
	EN_HAAR_KERNEL_TYPE_COUNT,
	
}EN_HAAR_KERNEL_TYPE;

typedef struct
{
	EN_HAAR_KERNEL_TYPE kernel_type;
	int kernel_width;
	int kernel_height;
	int threshold_value;
	double error_value;
	double beta_value;
	double alfa_value;

}Gesture_Struct;


typedef struct{
	int value;
	int x;
	int y;
}PIXEL_INFORMATION;

class Threshold_Info
{
	public:
		Threshold_Info();
		~Threshold_Info();

		double error_value;
		int threshold_value;
};

Threshold_Info::Threshold_Info()
{
	error_value = 1;
	threshold_value = -1;
}

Threshold_Info::~Threshold_Info()
{
	
}


class TestImage
{
	public:
		TestImage();
		~TestImage();
		
		Mat image;
		bool bHand;
		char* imageName;
		bool bClassified;
};

TestImage::TestImage()
{
	bHand = false;
	bClassified = false;
}

TestImage::~TestImage()
{
	
}


/**************Global Variables*******************/
int TRAINING_SET_HAND_IMAGE_NUMBER = 0;
int TRAINING_SET_NONHAND_IMAGE_NUMBER = 0;
const int MAX_KERNEL_WIDTH = 7;
const int TRAINING_SET_IMAGES_SIZE = 24;
int NUMBER_OF_CLASSIFIER = MAX_KERNEL_WIDTH * EN_HAAR_KERNEL_TYPE_COUNT;



int number_of_classified = 0;

/**************Global Variables*******************/










#endif
