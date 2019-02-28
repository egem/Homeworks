#ifndef __SKIN_SEGMENTATION_H__
#define __SKIN_SEGMENTATION_H__

#include "gesture_datatype.h"

class Skin_Segmentation
{
	public:
		static Mat SegmentationYCBCR(const Mat image);
		static void PrintSingleGaussionSegmentationParam();
		static Mat SingleGaussianSegmentation(const Mat image);
};

Mat Skin_Segmentation::SegmentationYCBCR(Mat image)
{
	Mat tempImage(image.rows, image.cols, CV_8UC3,Scalar(0,0,0));
	Mat binaryImage(image.rows, image.cols, CV_8UC1,Scalar(0));
	

	for(int i = 0; i < image.rows; i++)
	{
		for(int j = 0; j < image.cols; j++)
		{
			tempImage.at<Vec3b>(i,j)[0] = (0.299 * image.at<Vec3b>(i,j)[2] + 
											0.587 * image.at<Vec3b>(i,j)[1]
											+ 0.114 * image.at<Vec3b>(i,j)[0]);
			tempImage.at<Vec3b>(i,j)[1] = (image.at<Vec3b>(i,j)[0] - tempImage.at<Vec3b>(i,j)[0]) * 0.564 + 128; 	// CB
			tempImage.at<Vec3b>(i,j)[2] = (image.at<Vec3b>(i,j)[2] - tempImage.at<Vec3b>(i,j)[0]) * 0.713 + 128;	//CR
			if((tempImage.at<Vec3b>(i,j)[2] < 210) && (tempImage.at<Vec3b>(i,j)[2] > 140) &&
				(tempImage.at<Vec3b>(i,j)[1] < 130) && (tempImage.at<Vec3b>(i,j)[1] > 90))
			{
				binaryImage.at<uchar>(i,j) = 255;
			}
		}

	}

	return binaryImage;
	
}

Mat Skin_Segmentation::SingleGaussianSegmentation(const Mat image)
{
	
	return image;
}

void Skin_Segmentation::PrintSingleGaussionSegmentationParam()
{
	ifstream skinFile("skin_color_dataset.txt");

	vector<double> vector_h,vector_s,vector_bSkin;

	double r = 0,g = 0,b = 0, classified = 0;
	double h = 0,s = 0, v = 0, c = 0;
	string input;
	double sum_h1 = 0;	
	double sum_h2 = 0;
	
	double sum_s1 = 0;
	double sum_s2 = 0;
	
	double mean_h1 = 0;
	double mean_h2 = 0;
	
	double mean_s1 = 0;	
	double mean_s2 = 0;

	double variance_h1 = 0;
	double variance_h2 = 0;

	double variance_s1 = 0;
	double variance_s2 = 0;
	
	int counter1 = 0;
	int counter2 = 0;
	while(!skinFile.eof())
	{
		skinFile >> b;
		skinFile >> g;
		skinFile >> r;
		skinFile >> classified;

		r = r/255;
		g = g/255;
		b = b/255;

		c = max(r,max(g,b)) - min(r,min(g,b));
		v = max(r,max(g,b));

		if(v == 0)
			s = 0;
		else
			s = c/v;

		if(c != 0)
		{
			if(v == r)
			{
				double x1 = (g-b)/c;
				while(!(x1 > 0 && x1 < 6))
				{
					if(x1<0)
						x1 = x1+6;
					else
						x1 = x1-6;
				}
				h = x1 * 60;
			}
			else if(v == g)
			{
				double x1 = (b-r)/c;
				h = (x1 + 2) * 60;
			}
			else if(v == b)
			{
				double x1 = (r-g)/c;
				h = (x1 + 4) * 60;
			}
		}
		else
			h = 0;

		cout << h << "\t" << s << "\t" << v << endl;
		if(classified == 1)
		{
			sum_h1 += h;
			sum_s1 += s;
			counter1++;
		}
		else if(classified == 2)
		{
			sum_h2 += h;
			sum_s2 += s;
			counter2++;
		}
		else
		{
			cout << "Error at FILE : " << __FILE__ << "   LINE: " << __LINE__ << endl;
		}
		
		vector_h.push_back(h);
		vector_s.push_back(s);
		vector_bSkin.push_back(classified);
	}
	cout << "counter = " << counter1 << endl;
	mean_h1 = sum_h1/counter1;
	mean_h2 = sum_h2/counter2;

	mean_s1 = sum_s1/counter1;
	mean_s2 = sum_s2/counter2;
	cout << "**************" << endl;
	int total = counter1+counter2;
	while(total != 0)
	{
		classified = vector_bSkin.back();
		h = vector_h.back();
		s = vector_s.back();

		vector_bSkin.pop_back();
		vector_h.pop_back();
		vector_s.pop_back();

		if(classified == 1)
		{
			variance_h1 += (h - mean_h1) * (h - mean_h1);
			variance_s1 += (s - mean_s1) * (s - mean_s1);
		}
		else if(classified == 2)
		{
			variance_h2 += (h - mean_h2) * (h - mean_h2);
			variance_s2 += (s - mean_s2) * (s - mean_s2);
		}
		total--;

	}

	variance_h1 = variance_h1 / (counter1 -1);
	variance_s1 = variance_s1 / (counter1 -1);

	variance_h2 = variance_h2 / (counter2 -1);
	variance_s2 = variance_s2 / (counter2 -1);


	cout << " mean_h1:   " << mean_h1 << endl;  
	cout << " variance_h1 : " << variance_h1 << endl;
	
	cout << " mean_s1:   " << mean_s1 << endl;  
	cout << " variance_s1 : " << variance_s1 << endl;

	cout << " mean_h2:   " << mean_h2 << endl;  
	cout << " variance_h2 : " << variance_h2 << endl;

	cout << " mean_s2:   " << mean_s2 << endl;  
	cout << " variance_s2 : " << variance_s2 << endl;
	
}



#endif 
