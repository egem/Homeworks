#ifndef __HAAR_FEATURE_H__
#define __HAAR_FEATURE_H__

#include "gesture_datatype.h"

class Haar_Feature
{
	public:
		static Mat ComputeIntegralImage(const Mat& image);
		static Mat ComputeHaarResponse(const Mat OriginalIntegralImage, EN_HAAR_KERNEL_TYPE KernelType, int KernelSize_x, int KernelSize_y);
};



Mat Haar_Feature::ComputeIntegralImage(const Mat& image)
{
	Mat IntegralImage(image.rows, image.cols, CV_32SC1, Scalar(0));
	Mat GrayImage;
	if(image.channels() == 3)
		cvtColor(image, GrayImage, CV_BGR2GRAY);
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


Mat Haar_Feature::ComputeHaarResponse(const Mat OriginalIntegralImage, EN_HAAR_KERNEL_TYPE KernelType, int KernelSize_x, int KernelSize_y)
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


#endif
