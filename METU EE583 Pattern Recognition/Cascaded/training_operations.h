#ifndef __TRAINING_OPERATIONS_H__
#define __TRAINING_OPERATIONS_H__


#include "gesture_datatype.h"

class Training_Operations
{
	public:
		static void SaveTrainingDataSet(int argc, char *argv[], bool bHand);
		static void LoadTrainingDataSet(TestImage* testImages, int argc, char* argv[]);
		static void ImportTrainingDataSet(Gesture_Struct* &trained_data, double &sum_of_alfa, int &number_of_classifier);
};



void Training_Operations::SaveTrainingDataSet(int argc, char *argv[], bool bHand)
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

void Training_Operations::LoadTrainingDataSet(TestImage* testImages, int argc, char* argv[])
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

void Training_Operations::ImportTrainingDataSet(Gesture_Struct* &trained_data, double &sum_of_alfa, int &number_of_classifier)
{
	ifstream trainingResultFile("Cascaded/TrainingResults.txt");
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


		input = BasicOperations::TrimInputString(input);
		sum_of_alfa = BasicOperations::String2Double(input);

		getline(trainingResultFile, input);
		input = BasicOperations::TrimInputString(input);
		number_of_classifier = BasicOperations::String2Int(input);

		trained_data = new Gesture_Struct[number_of_classifier];
		cout << "sum_of_alfa = " << sum_of_alfa << "    number_of_classifier = " << number_of_classifier << endl;
		cout << "average = " << sum_of_alfa/number_of_classifier << endl;

		getline(trainingResultFile, input);			
					
		while(feature_number < number_of_classifier || trainingResultFile.eof())
		{
			getline(trainingResultFile, input);
			input = BasicOperations::TrimInputString(input);
			trained_data[feature_number].kernel_type = static_cast<EN_HAAR_KERNEL_TYPE>(BasicOperations::String2Int(input));
			
			getline(trainingResultFile, input);
			input = BasicOperations::TrimInputString(input);
			trained_data[feature_number].kernel_width = BasicOperations::String2Int(input);
			
			getline(trainingResultFile, input);
			input = BasicOperations::TrimInputString(input);
			trained_data[feature_number].kernel_height = BasicOperations::String2Int(input);

			getline(trainingResultFile, input);
			input = BasicOperations::TrimInputString(input);
			trained_data[feature_number].threshold_value = BasicOperations::String2Int(input);

			getline(trainingResultFile, input);
			input = BasicOperations::TrimInputString(input);
			trained_data[feature_number].error_value = BasicOperations::String2Double(input);

			getline(trainingResultFile, input);
			input = BasicOperations::TrimInputString(input);
			trained_data[feature_number].beta_value = BasicOperations::String2Double(input);

			getline(trainingResultFile, input);
			input = BasicOperations::TrimInputString(input);
			trained_data[feature_number].alfa_value = BasicOperations::String2Double(input);

			getline(trainingResultFile, input);
			feature_number++;
			//PrintTrainedDataSet(trained_data, number_of_classifier);
		}
	}
}



#endif 
