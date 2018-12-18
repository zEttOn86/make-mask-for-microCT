/*
* This implementaion use itk
* Build on VS2012
* Remove hole
* @auther tozawa
* @history
* 20171110
*/


#define ITK_IO_FACTORY_REGISTER_MANAGER
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkBinaryFillholeImageFilter.h"
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

	typedef itk::Image<IN_TYPE, NDims> ImageType;
	typedef itk::ImageFileReader<ImageType> ImageReaderType;
	ImageReaderType::Pointer Input = ImageReaderType::New();
	Input->SetFileName(inputFileName);

	typedef itk::BinaryFillholeImageFilter<ImageType> FilterType;
	FilterType::Pointer filter = FilterType::New();
	filter->SetInput(Input->GetOutput());
	filter->SetForegroundValue(itk::NumericTraits<IN_TYPE>::max());

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
}
