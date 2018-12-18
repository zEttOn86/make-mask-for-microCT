/*
* Extract the maximum region
* This implementation use itk
* @auther tozawa
* @history
* 20171113
*/

#define ITK_IO_FACTORY_REGISTER_MANAGER
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkBinaryImageToLabelMapFilter.h"
#include "itkLabelMapToLabelImageFilter.h"
#include "itkLabelStatisticsImageFilter.h"
#include "itkThresholdImageFilter.h"

typedef unsigned char IN_TYPE;
int main(int argc, char **argv)
{
	if (argc != 3) {
		std::cerr << "Usage : " << std::endl;
		std::cerr << argv[0] << " inputFile(.mhd) outputFileName(.mhd)" << std::endl;
		exit(1);
	}
	const char * inputFileName = argv[1];
	const char * outputFileName = argv[2];
	const unsigned char NDims = 3;

	// Input Image
	typedef itk::Image<IN_TYPE, NDims> ImageType;
	typedef itk::ImageFileReader<ImageType> ImageReaderType;
	ImageReaderType::Pointer Input = ImageReaderType::New();
	Input->SetFileName(inputFileName);
	
	//binary filter
	int lowerThreshold = 100;
	int upperThreshold = 100;
	typedef itk::ThresholdImageFilter< ImageType > FilterType;
	FilterType::Pointer filter = FilterType::New();
	filter->SetInput(Input->GetOutput());
	//filter->ThresholdAbove(upperThreshold);
	filter->ThresholdOutside(lowerThreshold, upperThreshold);
	filter->SetOutsideValue(0);

	//  Create a LabelMap from binary image
	//typedef itk::BinaryImageToLabelMapFilter<ImageType> 
	//	BinaryImageToLabelMapFilterType;
	//BinaryImageToLabelMapFilterType::Pointer binaryImageToLabelMapFilter =
	//	BinaryImageToLabelMapFilterType::New();
	//binaryImageToLabelMapFilter->SetInput(filter->GetOutput());
	//binaryImageToLabelMapFilter->Update();

	//// The output of this filter is an itk::LabelMap, which contains itk::LabelObject's
	//std::cout << "There are " << binaryImageToLabelMapFilter->GetOutput()->GetNumberOfLabelObjects() << " objects." << std::endl;
	//std::vector<unsigned long> labelsToRemove;

	//std::cout << "There are originally " << binaryImageToLabelMapFilter->GetOutput()->GetNumberOfLabelObjects() << " objects." << std::endl;

	//// Note: do NOT remove the labels inside the loop! The IDs are stored such that they will change when one is deleted.
	//// Instead, mark all of the labels to be removed first and then remove them all together.
	//unsigned long maxRegion = 0;
	//unsigned int maxRegionIndex = 0;
	//for (unsigned int i = 0; i < binaryImageToLabelMapFilter->GetOutput()->GetNumberOfLabelObjects(); i++)
	//{
	//	// Get the ith region
	//	BinaryImageToLabelMapFilterType::OutputImageType::LabelObjectType* labelObject = binaryImageToLabelMapFilter->GetOutput()->GetNthLabelObject(i);
	//	//std::cout << "Region " << i << " has " << labelObject->Size() << " pixels." << std::endl;
	//	if (maxRegion < labelObject->Size())
	//	{
	//		maxRegion = labelObject->Size();
	//		maxRegionIndex = i;
	//	}
	//	// Mark every other label to be removed
	//	// Memo : labelObject->GetLabel() = i+1 dayo
	//	/*if (i  != 5)
	//	{
	//		std::cout << labelObject->GetLabel() << std::endl;
	//		labelsToRemove.push_back(labelObject->GetLabel());
	//	}*/
	//}
	//// Mark every other label to be removed
	////for (unsigned int i = 0; i < binaryImageToLabelMapFilter->GetOutput()->GetNumberOfLabelObjects(); i++)
	////{
	////	// Get the ith region
	////	BinaryImageToLabelMapFilterType::OutputImageType::LabelObjectType* labelObject = binaryImageToLabelMapFilter->GetOutput()->GetNthLabelObject(i);
	////	if (i != maxRegionIndex)
	////	{
	////		std::cout << labelObject->GetLabel() << std::endl;
	////		labelsToRemove.push_back(labelObject->GetLabel());
	////	}
	////}

	//std::cout << "Removing " << labelsToRemove.size() << " objects." << std::endl;
	//std::cout << "Max Region number" << maxRegion << std::endl;
	//// Remove all regions that were marked for removal.
	///*for (unsigned int i = 0; i < labelsToRemove.size(); ++i)
	//{
	//	binaryImageToLabelMapFilter->GetOutput()->RemoveLabel(labelsToRemove[i]);
	//}
	//std::cout << "There are " << binaryImageToLabelMapFilter->GetOutput()->GetNumberOfLabelObjects()
	//	<< " objects remaining." << std::endl;*/

	
	//// Create a label image
	//typedef itk::LabelMapToLabelImageFilter<BinaryImageToLabelMapFilterType::OutputImageType, ImageType> 
	//	LabelMapToLabelImageFilterType;
	//LabelMapToLabelImageFilterType::Pointer labelMapToLabelImageFilter 
	//	= LabelMapToLabelImageFilterType::New();
	//labelMapToLabelImageFilter->SetInput(binaryImageToLabelMapFilter->GetOutput());
	//labelMapToLabelImageFilter->Update();

	//binary filter
	/*int lowerThreshold = maxRegion;
	int upperThreshold = maxRegion+1;
	typedef itk::ThresholdImageFilter< ImageType > FilterType;
	FilterType::Pointer filter = FilterType::New();
	filter->SetInput(labelMapToLabelImageFilter->GetOutput());
	filter->ThresholdOutside(lowerThreshold, upperThreshold);
	filter->SetOutsideValue(0);*/

	// Create an output image
	typedef itk::ImageFileWriter<ImageType> WriterType;
	WriterType::Pointer writer = WriterType::New();
	writer->SetFileName(outputFileName);
	writer->SetInput(filter->GetOutput());
	try
	{
		writer->Update();
	}
	catch (itk::ExceptionObject & error)
	{
		std::cerr << "Error:" << error << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
	//typedef itk::LabelStatisticsImageFilter< ImageType, ImageType > 
	//	LabelStatisticsImageFilterType;
	//LabelStatisticsImageFilterType::Pointer labelStatisticsImageFilter 
	//	= LabelStatisticsImageFilterType::New();
	//labelStatisticsImageFilter->SetLabelInput(labelMapToLabelImageFilter->GetOutput());
	//labelStatisticsImageFilter->SetInput(Input->GetOutput());
	//labelStatisticsImageFilter->Update();

	//std::cout << "Number of labels: " << labelStatisticsImageFilter->GetNumberOfLabels() << std::endl;
	//std::cout << std::endl;

	//typedef LabelStatisticsImageFilterType::ValidLabelValuesContainerType ValidLabelValuesType;
	//typedef LabelStatisticsImageFilterType::LabelPixelType                LabelPixelType;

	//for (ValidLabelValuesType::const_iterator vIt = labelStatisticsImageFilter->GetValidLabelValues().begin();
	//	vIt != labelStatisticsImageFilter->GetValidLabelValues().end();
	//	++vIt)
	//{
	//	if (labelStatisticsImageFilter->HasLabel(*vIt))
	//	{
	//		LabelPixelType labelValue = *vIt;
	//		std::cout << "min: " << labelStatisticsImageFilter->GetMinimum(labelValue) << std::endl;
	//		std::cout << "max: " << labelStatisticsImageFilter->GetMaximum(labelValue) << std::endl;
	//		std::cout << "median: " << labelStatisticsImageFilter->GetMedian(labelValue) << std::endl;
	//		std::cout << "mean: " << labelStatisticsImageFilter->GetMean(labelValue) << std::endl;
	//		std::cout << "sigma: " << labelStatisticsImageFilter->GetSigma(labelValue) << std::endl;
	//		std::cout << "variance: " << labelStatisticsImageFilter->GetVariance(labelValue) << std::endl;
	//		std::cout << "sum: " << labelStatisticsImageFilter->GetSum(labelValue) << std::endl;
	//		std::cout << "count: " << labelStatisticsImageFilter->GetCount(labelValue) << std::endl;
	//		//std::cout << "box: " << labelStatisticsImageFilter->GetBoundingBox( labelValue ) << std::endl; // can't output a box
	//		std::cout << "region: " << labelStatisticsImageFilter->GetRegion(labelValue) << std::endl;
	//		std::cout << std::endl << std::endl;
	//	}
	//}
	//return EXIT_SUCCESS;
}