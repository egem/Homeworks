#ifndef __BASIC_OPERATIONS_H__
#define __BASIC_OPERATIONS_H__

#include "gesture_datatype.h"

template <class T>
class BasicImageOperations
{
	public:
		static PIXEL_INFORMATION FindMaxValue(const Mat& image);
		static PIXEL_INFORMATION FindAbsoluteMaxValue(const Mat& image);
		static PIXEL_INFORMATION FindMinValue(const Mat& image);
		static Mat ThresholdGrayImage(const Mat& image, T min_value, T max_value);
};




template <class T>
PIXEL_INFORMATION BasicImageOperations<T>::FindMaxValue(const Mat& image)
{
	Mat localImage;

	localImage = image.clone();
	PIXEL_INFORMATION brightest_pixel = {0,0,0};
	T* p1;
	brightest_pixel.value = numeric_limits<int>::min();
	for(int i = 0; i < localImage.rows; i++)
	{
		p1 = localImage.ptr<T>(i);
		for(int j = 0; j < localImage.cols; j++)
		{
			if(static_cast<int>(p1[j]) > brightest_pixel.value)
			{
				brightest_pixel.value = (int)p1[j];
				brightest_pixel.x = j;
				brightest_pixel.y = i;
				
			}
		}
	}
	
	return brightest_pixel;	
}

template <class T>
PIXEL_INFORMATION BasicImageOperations<T>::FindAbsoluteMaxValue(const Mat& image)
{
	Mat localImage;

	localImage = image.clone();
	
	PIXEL_INFORMATION brightest_pixel = {0,0,0};
	T* p1;
	brightest_pixel.value = numeric_limits<int>::min();
	for(int i = 0; i < localImage.rows; i++)
	{
		p1 = localImage.ptr<T>(i);
		for(int j = 0; j < localImage.cols; j++)
		{
			if(abs(static_cast<int>(p1[j])) > brightest_pixel.value)
			{
				brightest_pixel.value = abs((int)p1[j]);
				brightest_pixel.x = j;
				brightest_pixel.y = i;
				
			}
		}
	}
	
	return brightest_pixel;	
}

template <class T>
PIXEL_INFORMATION BasicImageOperations<T>::FindMinValue(const Mat& image)
{
	Mat localImage;

	localImage = image.clone();
	
	PIXEL_INFORMATION darkest_pixel = {0,0,0};
	T* p1;
	darkest_pixel.value = numeric_limits<int>::max();
	for(int i = 0; i < localImage.rows; i++)
	{
		p1 = localImage.ptr<T>(i);
		for(int j = 0; j < localImage.cols; j++)
		{
			if(static_cast<int>(p1[j]) < darkest_pixel.value)
			{
				darkest_pixel.value = (int)p1[j];
				darkest_pixel.x = j;
				darkest_pixel.y = i;
				
			}
		}
	}
	
	return darkest_pixel;	
}

template <class T>
Mat BasicImageOperations<T>::ThresholdGrayImage(const Mat& image, T min_value, T max_value)
{
	Mat localImage;

	localImage = image.clone();
	
	Mat binaryImage(image.rows,image.cols, CV_8UC1, Scalar(0));
	T* p1;
	for(int i = 0; i < localImage.rows; i++)
	{
		p1 = localImage.ptr<T>(i);
		for(int j = 0; j < localImage.cols; j++)
		{
			if(p1[j] > min_value && p1[j] < max_value)
			{
				binaryImage.at<uchar>(i,j) = 255;
			}
		}
	}

	return binaryImage;
	
}


class BasicOperations
{
	public:
		static string TrimInputString(string input);
		static double String2Double(string input);
		static int String2Int(string input);

};
string BasicOperations::TrimInputString(string input)
{
	/*Removing labels from the beginning*/
	int i = 0;
  	for(; i < input.length(); i++)
	{
		if(input[i] == '>')
		{
			i++;
			break;
		}
			
	}

	/*Remove the blanks from the end*/
	int j = input.length()-1;
	for(; j>0; j--)
	{
		if(input[j] == '<')
			break;
	}
	
	string newstring(input,i,(j-i));	// Formed a (j-i) length string starting from ith character

	return newstring;
}

double BasicOperations::String2Double(string input)
{
	double fValue;

	stringstream s_str(input);
	s_str >> fValue;

	return fValue;
}

int BasicOperations::String2Int(string input)
{
	int dValue;

	stringstream s_str(input);
	s_str >> dValue;

	return dValue;
}



#endif
