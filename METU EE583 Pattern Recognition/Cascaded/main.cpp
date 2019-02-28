/*Implemented libraries*/
#include "enode.h"
#include "sorteddynamicqueue.h"
#include "gesture_datatype.h"
#include "debug.h"
#include "basic_operations.h"
#include "training_operations.h"
#include "haar_feature.h"
#include "adaboost.h"
#include "skin_segmentation.h"

/*Implemented libraries*/


void MainTrainFunction(int argc, char * argv[])
{
	TestImage* testImages = new TestImage[argc-1];
	Training_Operations::LoadTrainingDataSet(testImages, argc, argv);
	Adaboost::ComputeAdaboostWeight(testImages);

	
	delete []testImages;
}

void MainDetectionFunction(int argc, char *argv[])
{
#if 0
	/*Debug purpose*/
	int classified = 0;
	int nonclassified = 0;
	
	int number_of_classifer = 0;
	double sum_of_alfa = 0;
	Mat image;
	Mat imageResized;
	Mat IntegralImage;
	Mat HaarResponseImage;
	Size size(TRAINING_SET_IMAGES_SIZE,TRAINING_SET_IMAGES_SIZE);
	PIXEL_INFORMATION max_value;
	
	Gesture_Struct *trained_data = NULL;
	Training_Operations::ImportTrainingDataSet(trained_data,sum_of_alfa,number_of_classifer);
	double average_alfa_value = sum_of_alfa / number_of_classifer;
	for(int imageCount = 1; imageCount < argc ; imageCount++)
	{
		char* imageName = argv[imageCount];
		
		image = imread(argv[imageCount]);
		resize(image,imageResized,size,0,0, INTER_CUBIC);
		IntegralImage = Haar_Feature::ComputeIntegralImage(imageResized);
		double sum_of_valid_feature_alfa = 0;
		double sum_of_detected_feature_alfa = 0;
		
		//PrintTrainedDataSet(trained_data, number_of_classifer);
		
		for(int i = 0; i < number_of_classifer; i++)
		{
			if(trained_data[i].alfa_value < average_alfa_value)
				continue;
			HaarResponseImage = Haar_Feature::ComputeHaarResponse(IntegralImage, trained_data[i].kernel_type,trained_data[i].kernel_width,trained_data[i].kernel_height);
			max_value = BasicImageOperations<int>::FindAbsoluteMaxValue(HaarResponseImage);
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
#endif 

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
	Training_Operations::ImportTrainingDataSet(trained_data,sum_of_alfa,number_of_classifer);
	double average_alfa_value = sum_of_alfa / number_of_classifer;
	for(int imageCount = 1; imageCount < argc ; imageCount++)
	{
		char* imageName = argv[imageCount];
		
		image = imread(argv[imageCount]);
		resize(image,imageResized,size,0,0, INTER_CUBIC);
		IntegralImage = Haar_Feature::ComputeIntegralImage(imageResized);
		double sum_of_valid_feature_alfa = 0;
		double sum_of_detected_feature_alfa = 0;
		
		//PrintTrainedDataSet(trained_data, number_of_classifer);
		
		for(int i = 0; i < number_of_classifer; i++)
		{
			if(trained_data[i].alfa_value < average_alfa_value)
				continue;
			HaarResponseImage = Haar_Feature::ComputeHaarResponse(IntegralImage, trained_data[i].kernel_type,trained_data[i].kernel_width,trained_data[i].kernel_height);
			max_value = BasicImageOperations<int>::FindAbsoluteMaxValue(HaarResponseImage);
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
}
/////////////////////////////////////////////////////////////////////////////////////////////////////


void MainTrainFunctionCascaded(int argc, char * argv[])
{
	TestImage* testImages = new TestImage[argc-1];
	Training_Operations::LoadTrainingDataSet(testImages, argc, argv);
	Adaboost::ComputeAdaboostWeightCascaded(testImages);
	cout << "Training operation is done successfully" << endl;
	
	delete []testImages;
}

void MainDetectionFunctionCascaded(int argc, char *argv[])
{
	/*Debug purpose*/
	int classified = 0;
	int nonclassified = 0;
	
	int number_of_classifer = 0;
	double sum_of_alfa = 0;
	Mat image;
	Mat imageResized;
	Mat IntegralImage;
	Mat HaarResponseImage;
	Size size(TRAINING_SET_IMAGES_SIZE,TRAINING_SET_IMAGES_SIZE);
	PIXEL_INFORMATION max_value;
	
	Gesture_Struct *trained_data = NULL;
	Training_Operations::ImportTrainingDataSet(trained_data,sum_of_alfa,number_of_classifer);
	double average_alfa_value = sum_of_alfa / number_of_classifer;
	for(int imageCount = 1; imageCount < argc ; imageCount++)
	{
		char* imageName = argv[imageCount];
		//cout << argv[imageCount] << endl;
		image = imread(argv[imageCount]);
		resize(image,imageResized,size,0,0, INTER_CUBIC);
		
		IntegralImage = Haar_Feature::ComputeIntegralImage(imageResized);
		double sum_of_valid_feature_alfa = 0;
		double sum_of_detected_feature_alfa = 0;
		
		//PrintTrainedDataSet(trained_data, number_of_classifer);
		bool bHandDetected = true;
		for(int i = 0; i < number_of_classifer; i++)
		{
			//if(trained_data[i].alfa_value < average_alfa_value)
				//continue;
			HaarResponseImage = Haar_Feature::ComputeHaarResponse(IntegralImage, trained_data[i].kernel_type,trained_data[i].kernel_width,trained_data[i].kernel_height);
			max_value = BasicImageOperations<int>::FindAbsoluteMaxValue(HaarResponseImage);
			//cout << "max_value.value = " << max_value.value << endl;
			//cout << "threshold = " << trained_data[i].threshold_value << endl;
			//cout << "alfa = " << trained_data[i].alfa_value << endl;
			//int a;
			//cin >> a;
			if(max_value.value > trained_data[i].threshold_value)
			{
				sum_of_detected_feature_alfa += trained_data[i].alfa_value;
			}
			else
			{
				bHandDetected = false;
				break;
			}

			sum_of_valid_feature_alfa = trained_data[i].alfa_value;
		}

		if(bHandDetected == false)
		{
			//cout << "There is no hand" << endl;
			if(imageName[12] == 'n')
				classified++;
			else
				nonclassified++;
		}
		else
		{
			if(sum_of_detected_feature_alfa > (sum_of_valid_feature_alfa/2))
			{
				//cout << "There is hand" << endl;
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

		//imshow("image", image);
		//imshow("imageResized",imageResized);
		//int a = waitKey(0);
		//if(a==27)
			//return;
		//cout << endl << endl;
	}

	cout << "success rate: " << ((double)classified /(nonclassified + classified)) << endl;
	delete []trained_data;
}






int main(int argc, char * argv[])
{
	cout << "Please choose an option : " << endl;
	cout << " 1. Training" << endl;
	cout << " 2. Detection" << endl;
	int firstChoice;
	cin >> firstChoice;

	if(firstChoice == 1)
	{
		MainTrainFunctionCascaded(argc,argv);
		return 0;
	}
	else if(firstChoice !=2)
	{
		cout << "Invalid Input" << endl;
		return 0;
	}

	MainDetectionFunctionCascaded(argc,argv);
	
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

