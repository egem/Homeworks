#ifndef __DEBUG_H__
#define __DEBUG_H__

#include "gesture_datatype.h"

template <class T>
class Debug
{
	public:
		static void PrintImage(const Mat& image);
		static void PrintTrainedDataSet(Gesture_Struct *trained_data, int number_of_classifer);
};

template <class T>
void Debug<T>::PrintImage(const Mat& image)
{
	for(int i = 0; i< image.rows; i++)
	{
		for(int j = 0; j < image.cols; j++)
		{
			cout << setw(5) << left << (int)image.at<T>(i,j) << "  ";
		}
		cout << endl;
	}
	cout << endl << endl;
}

template <class T>
void Debug<T>::PrintTrainedDataSet(Gesture_Struct *trained_data, int number_of_classifer)
{
	for(int i = 0; i < number_of_classifer; i++)
	{
		cout << "kernel type = " << (int)trained_data[i].kernel_type << endl;
		cout << "kernel width = " << trained_data[i].kernel_width << endl;
		cout << "kernel height = " << trained_data[i].kernel_height << endl;
		cout << "threshold = " << trained_data[i].threshold_value << endl;
		cout << "=======================================" << endl;
	}
}




#endif
