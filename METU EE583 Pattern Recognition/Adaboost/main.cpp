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
#include "enode.h"
#include "sorteddynamicqueue.h"
#include <fstream>
#include <cmath>

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



template <class T>
void PrintImage(const Mat& image)
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
PIXEL_INFORMATION FindMaxValue(const Mat& image)
{
	Mat localImage(image);
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
PIXEL_INFORMATION FindAbsoluteMaxValue(const Mat& image)
{
	Mat localImage(image);
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
PIXEL_INFORMATION FindMinValue(const Mat& image)
{
	Mat localImage(image);
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
Mat ThresholdGrayImage(const Mat& image, T min_value, T max_value)
{
	Mat localImage(image);
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

Mat ComputeIntegralImage(const Mat& image)
{
	Mat IntegralImage(image.rows, image.cols, CV_32SC1, Scalar(0));
	Mat GrayImage;
	if(image.channels() == 3)
		cvtColor(image, GrayImage, CV_RGB2GRAY);
	else if(image.channels() == 1)
		image.copyTo(GrayImage);

	
    int nRows = GrayImage.rows;
    int nCols = GrayImage.cols;
    unsigned char* p1;
    int *p2;
	int sum = 0;
    for(int i = 0; i < nRows; ++i)
    {
        p2 = IntegralImage.ptr<int>(i);
        for (int j = 0; j < nCols; ++j)
        {
        	for(int shift_i = 0; shift_i <= i ; shift_i++)
        	{
				p1 = GrayImage.ptr<unsigned char>(shift_i);
				for(int shift_j = 0; shift_j <= j ; shift_j++)
				{
					sum += p1[shift_j];
				}
        	}
            p2[j] = sum;
            sum = 0;
        }
    }

    return IntegralImage;
	
}


Mat ComputeHaarResponse(const Mat OriginalIntegralImage, EN_HAAR_KERNEL_TYPE KernelType, int KernelSize_x, int KernelSize_y)
{
	Mat IntegralImage(OriginalIntegralImage);
	Mat HaarResponseImage(IntegralImage.rows, IntegralImage.cols, CV_32SC1, Scalar(0));
	Mat BoundaryProtectedIntegralImage(IntegralImage.rows+1, IntegralImage.cols+1, CV_32SC1, Scalar(0));

	int nRows = HaarResponseImage.rows;
    int nCols = HaarResponseImage.cols;

	int *p1;
	int *p2;
	for(int i = 0; i < IntegralImage.rows; ++i)
    {
        p1 = BoundaryProtectedIntegralImage.ptr<int>(i+1);
        p2 = IntegralImage.ptr<int>(i);
        for(int j = 0; j < IntegralImage.cols; j++)
        {
			p1[j+1] = p2[j];
        }

    }

	switch(KernelType)
	{
		case EN_HAAR_KERNEL_TYPE_A:
		{
			int KernelWidth = 2 * KernelSize_x;
			int KernelHeight = KernelSize_y;

			int *IntegralImageTopRow, *IntegralImageBottomRow;
    		int *HaarResponseImageRow;
    
		    for(int i = 0; i <= nRows - KernelHeight; ++i)
		    {
		    	HaarResponseImageRow = HaarResponseImage.ptr<int>(i);
		        IntegralImageTopRow = BoundaryProtectedIntegralImage.ptr<int>(i);
		        IntegralImageBottomRow = BoundaryProtectedIntegralImage.ptr<int>(i + KernelHeight);
		        for (int j = 0; j <= nCols - KernelWidth; ++j)
		        {
		        	HaarResponseImageRow[j] = 		(	 (IntegralImageBottomRow[j+KernelSize_x] + IntegralImageTopRow[j] )
		        										-(IntegralImageBottomRow[j] + IntegralImageTopRow[j + KernelSize_x]) )					// Sum of the White Area	
		        								- 	(	 (IntegralImageBottomRow[j + KernelWidth] + IntegralImageTopRow[j + KernelSize_x])
		        										-(IntegralImageBottomRow[j + KernelSize_x] + IntegralImageTopRow[j + KernelWidth]) ); 	// Sum of the Black Area
		        								
		        }
		    }		
		}
		break;
		case EN_HAAR_KERNEL_TYPE_B:
		{
			int KernelWidth = KernelSize_x;
			int KernelHeight = 2* KernelSize_y;

			int *IntegralImageTopRow, *IntegralImageBottomRow, *IntegralImageMiddleRow;
    		int *HaarResponseImageRow;
    
		    for(int i = 0; i <= nRows - KernelHeight; ++i)
		    {
		    	HaarResponseImageRow = HaarResponseImage.ptr<int>(i);
		        IntegralImageTopRow = BoundaryProtectedIntegralImage.ptr<int>(i);
		        IntegralImageMiddleRow = BoundaryProtectedIntegralImage.ptr<int>(i + KernelSize_y); 
		        IntegralImageBottomRow = BoundaryProtectedIntegralImage.ptr<int>(i + KernelHeight);
		        for (int j = 0; j <= nCols - KernelWidth; ++j)
		        {
		        	HaarResponseImageRow[j] = 		(	 (IntegralImageBottomRow[j + KernelWidth] + IntegralImageMiddleRow[j] )
		        										-(IntegralImageBottomRow[j] + IntegralImageMiddleRow[j + KernelWidth]) )	// Sum of the White Area	
		        								- 	(	 (IntegralImageMiddleRow[j + KernelWidth] + IntegralImageTopRow[j])
		        										-(IntegralImageMiddleRow[j] + IntegralImageTopRow[j + KernelWidth]) ); 		// Sum of the Black Area
		        								
		        }
		    }		
		}
		break;
		case EN_HAAR_KERNEL_TYPE_C:
		{
			int KernelWidth = KernelSize_x * 3;
			int KernelHeight = KernelSize_y;

			int *IntegralImageTopRow, *IntegralImageBottomRow;
    		int *HaarResponseImageRow;
    
		    for(int i = 0; i <= nRows - KernelHeight; ++i)
		    {
		    	HaarResponseImageRow = HaarResponseImage.ptr<int>(i);
		        IntegralImageTopRow = BoundaryProtectedIntegralImage.ptr<int>(i);
		        IntegralImageBottomRow = BoundaryProtectedIntegralImage.ptr<int>(i + KernelHeight);
		        for (int j = 0; j <= nCols - KernelWidth; ++j)
		        {
		        	HaarResponseImageRow[j] = 		(	 (IntegralImageBottomRow[j + 2 * KernelSize_x] + IntegralImageTopRow[j + KernelSize_x] )
		        										-(IntegralImageBottomRow[j + KernelSize_x] + IntegralImageTopRow[j + 2 * KernelSize_x]) )	// Sum of the White Area	
		        								- 	(	 (IntegralImageBottomRow[j + KernelSize_x] + IntegralImageTopRow[j])
		        										-(IntegralImageBottomRow[j] + IntegralImageTopRow[j + KernelSize_x]) )
		        								-	(	 (IntegralImageBottomRow[j + KernelWidth] + IntegralImageTopRow[j + 2 * KernelSize_x])
		        										-(IntegralImageBottomRow[j + 2 * KernelSize_x] + IntegralImageTopRow[j + KernelWidth]) );	// Sum of the Black Areas
		        										
		        								
		        }
		    }		
		}
		break;
		default:
		break;
	}

	return HaarResponseImage;

}


void SaveTrainingDataSet(int argc, char *argv[], bool bHand)
{
	unsigned int baseValue = 2276;
	string fileName1;
	if(bHand)
		fileName1 = "usedDataSet/h";
	else
		fileName1 = "usedDataSet/n";
		
	for(int i = 1; i < argc; i++)
	{
		Mat image = imread(argv[i]);
		ostringstream s_str;
		s_str << (baseValue+i);
		string fileName = fileName1 + s_str.str() + ".bmp";
		imwrite(fileName, image);
	}
}

void LoadTrainingDataSet(TestImage* testImages, int argc, char* argv[])
{
	for(int testImageCount = 0; testImageCount < argc-1; testImageCount++)
	{
		testImages[testImageCount].image = imread(argv[testImageCount+1]);
		testImages[testImageCount].imageName = argv[testImageCount+1];
		if(testImages[testImageCount].imageName[12] == 'h')
		{
			TRAINING_SET_HAND_IMAGE_NUMBER++;
			testImages[testImageCount].bHand = true;
		}
		else if(testImages[testImageCount].imageName[12] == 'n')
		{
			TRAINING_SET_NONHAND_IMAGE_NUMBER++;
			testImages[testImageCount].bHand = false;
		}
		else
		{
			cout << "Invalid file name @ Line : " << __LINE__ << endl;
		}
	}


}

void ComputeAdaboostWeight(TestImage* testImages)
{
	int number_of_test_image = TRAINING_SET_HAND_IMAGE_NUMBER + TRAINING_SET_NONHAND_IMAGE_NUMBER;
	double weights_sum = 0;
	int feature_number = 0;
	double error_value = 0;
	double sum_of_alfa_values = 0;
	double Hand_Images_Initial_Weight = 1 / ((double)(2 * TRAINING_SET_HAND_IMAGE_NUMBER));
	double NonHand_Images_Initial_Weight = 1 / ((double)(2 * TRAINING_SET_NONHAND_IMAGE_NUMBER));
	ofstream trainingResultFile("Adaboost/TrainingResults.txt");
	
	SortedDynamicQueue threshold_queue;
	
	/*Dynamically allocated objects*/
	double *weights = new double[number_of_test_image];
	int *feature_value = new int[number_of_test_image];
	Threshold_Info *thresh = new Threshold_Info[NUMBER_OF_CLASSIFIER];
	double *beta_value = new double[NUMBER_OF_CLASSIFIER];
	double *alfa_value = new double[NUMBER_OF_CLASSIFIER];
	/*Dynamically allocated objects*/

	/*Assign the initial weights*/	
	for(int testImageCount = 0; testImageCount < number_of_test_image; testImageCount++)
	{
		if(testImages[testImageCount].bHand == true)
			weights[testImageCount] = Hand_Images_Initial_Weight;
		else
			weights[testImageCount] = NonHand_Images_Initial_Weight;

	}


	for(int kernel_width = 1; kernel_width <= MAX_KERNEL_WIDTH ; kernel_width++)
	{
		for(EN_HAAR_KERNEL_TYPE kernel_type = EN_HAAR_KERNEL_TYPE_A; kernel_type < EN_HAAR_KERNEL_TYPE_COUNT;kernel_type = static_cast<EN_HAAR_KERNEL_TYPE>((int)kernel_type +1))
		{
			//feature_number = static_cast<int>(kernel_type) * MAX_KERNEL_WIDTH + (kernel_width - 1);
			feature_number = (kernel_width - 1) * (int)EN_HAAR_KERNEL_TYPE_COUNT + (int)kernel_type;
			memset(feature_value, 0, sizeof(int)*number_of_test_image);
			for(int testImageCount = 0; testImageCount < number_of_test_image; testImageCount++)
			{
				Mat ResizedImage, IntegralImage, HaarResponseImage;
				Size size(TRAINING_SET_IMAGES_SIZE,TRAINING_SET_IMAGES_SIZE);
	 
				resize(testImages[testImageCount].image,ResizedImage,size,0,0, INTER_CUBIC);
				IntegralImage = ComputeIntegralImage(ResizedImage);
				HaarResponseImage = ComputeHaarResponse(IntegralImage, kernel_type,kernel_width,kernel_width);
				PIXEL_INFORMATION max_value = FindAbsoluteMaxValue<int>(HaarResponseImage);
				feature_value[testImageCount] = max_value.value;
				threshold_queue.QInsert(max_value.value);
			}

			weights_sum = 0;
			// Sum the weight for normalization
			for(int testImageCount = 0; testImageCount < number_of_test_image; testImageCount++)
			{
				weights_sum += weights[testImageCount];
			}

			// Normalization
			for(int testImageCount = 0; testImageCount < number_of_test_image; testImageCount++)
			{
				weights[testImageCount] = weights[testImageCount] / weights_sum;
			}

			/*Find the threshold which yields smallest error*/
			while(!threshold_queue.QEmpty())// nonhand region contains threshold value.
			{
				int threshold_value = threshold_queue.QDelete();

				error_value = 0;
				for(int testImageCount = 0; testImageCount < number_of_test_image; testImageCount++)
				{
					if(feature_value[testImageCount] <= threshold_value && testImages[testImageCount].bHand == true)	// Error caused by hand images detected as nonhand images
						error_value += weights[testImageCount];
					if(feature_value[testImageCount] > threshold_value && testImages[testImageCount].bHand == false)
						error_value += weights[testImageCount];
				}

				if(error_value < thresh[feature_number].error_value)
				{
					thresh[feature_number].error_value = error_value;
					thresh[feature_number].threshold_value = threshold_value;
				}
				
			}

			/*Calculate the alfa and beta values for that feature*/
			beta_value[feature_number] = thresh[feature_number].error_value / (1 - thresh[feature_number].error_value);
			alfa_value[feature_number] = log10(1/beta_value[feature_number]);

			sum_of_alfa_values += alfa_value[feature_number];
			
			/*Update the weights*/
			for(int testImageCount = 0; testImageCount < number_of_test_image; testImageCount++)
			{
				if(	(feature_value[testImageCount] <= thresh[feature_number].threshold_value && testImages[testImageCount].bHand == false) ||
					(feature_value[testImageCount] > thresh[feature_number].threshold_value && testImages[testImageCount].bHand == true))
				{
					weights[testImageCount] = weights[testImageCount] * beta_value[feature_number];
					testImages[testImageCount].bClassified = true;
				}
					
			}


		}
		
	}
	
	trainingResultFile << "==================================================" << endl;	
	trainingResultFile << "<Alfa_Sum>" << sum_of_alfa_values << "<Alfa_Sum>" << endl;
	trainingResultFile << "<Number_of_Classifier>" << NUMBER_OF_CLASSIFIER << "<Number_of_Classifier>" << endl;
	trainingResultFile << "==================================================" << endl;	
	for(int kernel_width = 1; kernel_width <= MAX_KERNEL_WIDTH ; kernel_width++)
	{
		for(EN_HAAR_KERNEL_TYPE kernel_type = EN_HAAR_KERNEL_TYPE_A; kernel_type < EN_HAAR_KERNEL_TYPE_COUNT;kernel_type = static_cast<EN_HAAR_KERNEL_TYPE>((int)kernel_type +1))
		{
			feature_number = (kernel_width - 1) * (int)EN_HAAR_KERNEL_TYPE_COUNT + (int)kernel_type;

			/*Write training result to a file "TrainingResults.txt*/
			trainingResultFile << "<Kernel_Type>" << (int)kernel_type << "<Kernel_Type>" << endl;
			trainingResultFile << "<Kernel_Width>" << kernel_width << "<Kernel_Width>" << endl;
			trainingResultFile << "<Kernel_Height>" << kernel_width << "<Kernel_Height>" << endl;
			trainingResultFile << "<Threshold>" << thresh[feature_number].threshold_value << "<Threshold>" << endl;
			trainingResultFile << "<Error>" << thresh[feature_number].error_value<< "<Error>" << endl;
			trainingResultFile << "<Beta_Value>" << beta_value[feature_number]<< "<Beta_Value>" << endl;
			trainingResultFile << "<Alfa_Value>" << log10(1/beta_value[feature_number])<< "<Alfa_Value>" << endl;
			trainingResultFile << "==================================================" << endl;	
				
		}
	}
	
	

	delete []weights;
	delete []feature_value;
	delete []beta_value;
	delete []alfa_value;
	delete []thresh;

}

#if 0
void ImportProductsFromTXT(vector<ElectronicProduct*> &product)
{
	#define EXPECTED 0
#if(EXPECTED == 0)
	cout << "Enter the file name. Press 0 to return the main menu" << endl;
	cout << setw(USER_CHOICE_WIDTH) << right << "Output file name :" << "\t";

	string inputFilePath;
	cin >> inputFilePath;

	if(inputFilePath == "0")
		return;
		
	ifstream inf(inputFilePath);
#else
	ifstream inf(INPUT_FILE_NAME);
#endif
	bool newTxt = true;
 	string input;
 	
    if (!inf)
    {
#if(EXPECTED == 0)
        cout << inputFilePath << " couldn't be opened" << endl;
#else
		cout << INPUT_FILE_NAME << " couldn't be opened" << endl;
#endif
        
    }
    else
    { 
		while (inf)
	    {
	        // read stuff from the file into a string and print it
	        getline(inf, input);
	        StateMachine(input, product,newTxt);
	        newTxt = false;
	    }
		cout << "Data is imported from text successfully" << endl;
    }
 
}
#endif

string TrimInputString(string input)
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

double String2Double(string input)
{
	double fValue;

	stringstream s_str(input);
	s_str >> fValue;

	return fValue;
}

int String2Int(string input)
{
	int dValue;

	stringstream s_str(input);
	s_str >> dValue;

	return dValue;
}

void PrintTrainedDataSet(Gesture_Struct *trained_data, int number_of_classifer)
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

void ImportTrainingDataSet(Gesture_Struct* &trained_data, double &sum_of_alfa, int &number_of_classifier)
{
	ifstream trainingResultFile("Adaboost/TrainingResults.txt");
	trainingResultFile.seekg(std::ios::beg);

	string input;
	int feature_number = 0;
	
	if(!trainingResultFile)
	{
		cout << "There is no TrainingResults.txt file" << endl;
		exit(1);
	}
	else
	{
		getline(trainingResultFile, input);
		getline(trainingResultFile, input);


		input = TrimInputString(input);
		sum_of_alfa = String2Double(input);

		getline(trainingResultFile, input);
		input = TrimInputString(input);
		number_of_classifier = String2Int(input);

		trained_data = new Gesture_Struct[number_of_classifier];
		cout << "sum_of_alfa = " << sum_of_alfa << "    number_of_classifier = " << number_of_classifier << endl;
		cout << "average = " << sum_of_alfa/number_of_classifier << endl;

		getline(trainingResultFile, input);			
					
		while(feature_number < number_of_classifier || trainingResultFile.eof())
		{
			getline(trainingResultFile, input);
			input = TrimInputString(input);
			trained_data[feature_number].kernel_type = static_cast<EN_HAAR_KERNEL_TYPE>(String2Int(input));
			
			getline(trainingResultFile, input);
			input = TrimInputString(input);
			trained_data[feature_number].kernel_width = String2Int(input);
			
			getline(trainingResultFile, input);
			input = TrimInputString(input);
			trained_data[feature_number].kernel_height = String2Int(input);

			getline(trainingResultFile, input);
			input = TrimInputString(input);
			trained_data[feature_number].threshold_value = String2Int(input);

			getline(trainingResultFile, input);
			input = TrimInputString(input);
			trained_data[feature_number].error_value = String2Double(input);

			getline(trainingResultFile, input);
			input = TrimInputString(input);
			trained_data[feature_number].beta_value = String2Double(input);

			getline(trainingResultFile, input);
			input = TrimInputString(input);
			trained_data[feature_number].alfa_value = String2Double(input);

			getline(trainingResultFile, input);
			feature_number++;
			//PrintTrainedDataSet(trained_data, number_of_classifier);
		}
	}
}

void MainTrainFunction(int argc, char * argv[])
{
	TestImage* testImages = new TestImage[argc-1];
	LoadTrainingDataSet(testImages, argc, argv);
	ComputeAdaboostWeight(testImages);

	
	delete []testImages;
}



int main(int argc, char * argv[])
{
	cout << argv[1] << endl;
	cout << "Please choose an option : " << endl;
	cout << " 1. Training" << endl;
	cout << " 2. Detection" << endl;
	int firstChoice;
	cin >> firstChoice;

	if(firstChoice == 1)
	{
		MainTrainFunction(argc,argv);
		return 0;
	}
	else if(firstChoice !=2)
	{
		cout << "Invalid Input" << endl;
		return 0;
	}

	/*Debug purpose*/
	int classified = 0;
	int nonclassified = 0;
	
	int number_of_classifer = 0;
	double sum_of_alfa = 0;
	Mat image;
	Mat imageResized;
	Mat IntegralImage;
	Mat HaarResponseImage;
	Size size(24,24);
	PIXEL_INFORMATION max_value;
	
	Gesture_Struct *trained_data = NULL;
	ImportTrainingDataSet(trained_data,sum_of_alfa,number_of_classifer);
	double average_alfa_value = sum_of_alfa / number_of_classifer;
	for(int imageCount = 1; imageCount < argc ; imageCount++)
	{
		char* imageName = argv[imageCount];
		
		image = imread(argv[imageCount]);
		resize(image,imageResized,size,0,0, INTER_CUBIC);
		IntegralImage = ComputeIntegralImage(imageResized);
		double sum_of_valid_feature_alfa = 0;
		double sum_of_detected_feature_alfa = 0;
		
		//PrintTrainedDataSet(trained_data, number_of_classifer);
		
		for(int i = 0; i < number_of_classifer; i++)
		{
			if(trained_data[i].alfa_value < average_alfa_value)
				continue;
			HaarResponseImage = ComputeHaarResponse(IntegralImage, trained_data[i].kernel_type,trained_data[i].kernel_width,trained_data[i].kernel_height);
			max_value = FindAbsoluteMaxValue<int>(HaarResponseImage);
			//cout << "max_value.value = " << max_value.value << endl;
			//cout << "threshold = " << trained_data[i].threshold_value << endl;
			if(max_value.value > trained_data[i].threshold_value)
			{
				sum_of_detected_feature_alfa += trained_data[i].alfa_value;
			}

			sum_of_valid_feature_alfa = trained_data[i].alfa_value;
		}

		if(sum_of_detected_feature_alfa > (sum_of_valid_feature_alfa/2))
		{
			cout << "There is hand" << endl;
			if(imageName[12] == 'h')
				classified++;
			else
				nonclassified++;
		}
		else
		{
			cout << "There is no hand" << endl;
			if(imageName[12] == 'n')
				classified++;
			else
				nonclassified++;
		}

	}

	cout << "success rate: " << ((double)classified /(nonclassified + classified)) << endl;
	delete []trained_data;
#if 0
	Mat image;
	Mat imageResized;
	Mat IntegralImage;
	Mat HaarResponseImage;
	Size size(24,24);
	PIXEL_INFORMATION max_value;
	for(int i = 1; i< argc; i++)
	{
		cout << argv[i] << " : " << endl;
		image = imread(argv[i]);
		resize(image,imageResized,size,0,0, INTER_CUBIC);
		IntegralImage = ComputeIntegralImage(imageResized);
		HaarResponseImage = ComputeHaarResponse(IntegralImage, EN_HAAR_KERNEL_TYPE_C,7,7);
		max_value = FindAbsoluteMaxValue<int>(HaarResponseImage);
		cout << " Absolute Max Value : " << max_value.value << endl;
		cout << " \t\t\t x = " << max_value.x << endl;
		cout << " \t\t\t y = " << max_value.y << endl;
		if(max_value.value> 7344)
			cout << "it is hand" << endl;
		else
			cout << "it is not hand" << endl;
		imshow("image", imageResized);
		imshow("Haar Response", HaarResponseImage);
		int c = waitKey(0);
		if(c== 27)
			return 0;
	}
#endif
#if 0
	cout << "argc = " << argc << endl;
	TestImage* testImages = new TestImage[argc-1];
	LoadTrainingDataSet(testImages, argc, argv);
	thresh = new Threshold_Info[NUMBER_OF_CLASSIFIER];

	ComputeAdaboostWeight(testImages);

	delete []thresh;
	delete []testImages;
#endif
	
}

