#ifndef __ADABOOST_H_
#define __ADABOOST_H_

#include "gesture_datatype.h"


class Adaboost
{
	public:
		static void ComputeAdaboostWeight(TestImage* testImages);	
		static void ComputeAdaboostWeightCascaded(TestImage* testImages);	
	
};

void Adaboost::ComputeAdaboostWeight(TestImage* testImages)
{
	int number_of_test_image = TRAINING_SET_HAND_IMAGE_NUMBER + TRAINING_SET_NONHAND_IMAGE_NUMBER;
	double weights_sum = 0;
	int feature_number = 0;
	double error_value = 0;
	double sum_of_alfa_values = 0;
	double Hand_Images_Initial_Weight = 1 / ((double)(2 * TRAINING_SET_HAND_IMAGE_NUMBER));
	double NonHand_Images_Initial_Weight = 1 / ((double)(2 * TRAINING_SET_NONHAND_IMAGE_NUMBER));
	ofstream trainingResultFile("branch/TrainingResults.txt");
	
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
				IntegralImage = Haar_Feature::ComputeIntegralImage(ResizedImage);
				HaarResponseImage = Haar_Feature::ComputeHaarResponse(IntegralImage, kernel_type,kernel_width,kernel_width);
				PIXEL_INFORMATION max_value = BasicImageOperations<int>::FindAbsoluteMaxValue(HaarResponseImage);
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
				if( (feature_value[testImageCount] <= thresh[feature_number].threshold_value && testImages[testImageCount].bHand == false) ||
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



void Adaboost::ComputeAdaboostWeightCascaded(TestImage* testImages)
{
	int number_of_test_image = TRAINING_SET_HAND_IMAGE_NUMBER + TRAINING_SET_NONHAND_IMAGE_NUMBER;
	double weights_sum = 0;
	int feature_number = 0;
	double error_value = 0;
	double sum_of_alfa_values = 0;
	double Hand_Images_Initial_Weight = 1 / ((double)(2 * TRAINING_SET_HAND_IMAGE_NUMBER));
	double NonHand_Images_Initial_Weight = 1 / ((double)(2 * TRAINING_SET_NONHAND_IMAGE_NUMBER));
	ofstream trainingResultFile("Cascaded/TrainingResults.txt");
	
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
			//cout << feature_number << endl;
			memset(feature_value, 0, sizeof(int)*number_of_test_image);

			if(!threshold_queue.QEmpty())
				threshold_queue.ClearQueue();
				
			for(int testImageCount = 0; testImageCount < number_of_test_image; testImageCount++)
			{
				Mat ResizedImage, IntegralImage, HaarResponseImage;
				Size size(TRAINING_SET_IMAGES_SIZE,TRAINING_SET_IMAGES_SIZE);
	 
				resize(testImages[testImageCount].image,ResizedImage,size,0,0, INTER_CUBIC);
				IntegralImage = Haar_Feature::ComputeIntegralImage(ResizedImage);
				HaarResponseImage = Haar_Feature::ComputeHaarResponse(IntegralImage, kernel_type,kernel_width,kernel_width);
				PIXEL_INFORMATION max_value = BasicImageOperations<int>::FindAbsoluteMaxValue(HaarResponseImage);
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

			int threshold_value = 0;
			int previous_threshold_value = 0;
			bool stop_search = false;
			error_value = 0;
			int unclassified_feature = 0;
			/*Find the threshold which yields smallest error*/
			while(!threshold_queue.QEmpty())// nonhand region contains threshold value.
			{
				previous_threshold_value = threshold_value;
				threshold_value = threshold_queue.QDelete();

				unclassified_feature = 0;
				/*Choose the previous threshold when we face with a hand*/
				for(int testImageCount = 0; testImageCount < number_of_test_image; testImageCount++)
				{
					if(feature_value[testImageCount] <= threshold_value)
					{
						if(testImages[testImageCount].bHand == true)
						{
							unclassified_feature++;
						}
					}
					
				}

				if(unclassified_feature == 0)
				{
					if(threshold_value > thresh[feature_number].threshold_value)
					{
						thresh[feature_number].threshold_value = threshold_value;
					}
				}


				
				
			}

			error_value = 0;
			for(int testImageCount = 0; testImageCount < number_of_test_image; testImageCount++)
			{
				if(feature_value[testImageCount] <= thresh[feature_number].threshold_value && testImages[testImageCount].bHand == true)	// Error caused by hand images detected as nonhand images
				{
					cout << "Error at line : " << __LINE__ << "   at File : " << __FILE__ <<   endl;
				}
				if(feature_value[testImageCount] > thresh[feature_number].threshold_value && testImages[testImageCount].bHand == false)
					error_value += weights[testImageCount];

			}

			if(error_value < thresh[feature_number].error_value)
			{
				thresh[feature_number].error_value = error_value;
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


#endif
