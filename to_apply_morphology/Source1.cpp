/*
* This implementation use itk
* Closing
* @auther tozawa
* @history
* 20171110
*/

#define ITK_IO_FACTORY_REGISTER_MANAGER
#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>
#include "itkBinaryBallStructuringElement.h"
#include "itkBinaryMorphologicalClosingImageFilter.h"
typedef unsigned char IN_TYPE;

int main(int argc, char **argv)
{
	if (argc != 4) {
		std::cerr << "Usage : " << std::endl;
		std::cerr << argv[0] << " inputFile(.mhd) outputFileName(.mhd) radius" << std::endl;
		exit(1);
	}
	unsigned int radius = atoi(argv[3]);
	std::cout << "Radius: " << radius << std::endl;

	const unsigned char NDims = 3;
	typedef itk::Image<IN_TYPE, NDims> ImageType;
	typedef itk::ImageFileReader<ImageType> ImageReaderType;//Define image type
	ImageReaderType::Pointer Input = ImageReaderType::New();//Define image pointer
	Input->SetFileName(argv[1]);//Set read directory path
	try
	{
		Input->Update();
	}
	catch (itk::ExceptionObject & excep) {
		std::cerr << "Exception caught !" << std::endl;
		std::cerr << excep << std::endl;
		system("pause");
		exit(1);
	}

	typedef itk::BinaryBallStructuringElement<ImageType::PixelType, NDims> StructuringElementType;
	StructuringElementType structuringElement;
	structuringElement.SetRadius(radius);
	structuringElement.CreateStructuringElement();

	typedef itk::BinaryMorphologicalClosingImageFilter <ImageType, ImageType, StructuringElementType>
		BinaryMorphologicalClosingImageFilterType;
	BinaryMorphologicalClosingImageFilterType::Pointer closingFilter
		= BinaryMorphologicalClosingImageFilterType::New();
	closingFilter->SetInput(Input->GetOutput());
	closingFilter->SetKernel(structuringElement);

	//Prepare for output image
	typedef itk::ImageFileWriter<ImageType> ImageWriterType;
	ImageWriterType::Pointer writerI = ImageWriterType::New();
	writerI->SetFileName(argv[2]);
	writerI->SetInput(closingFilter->GetOutput());
	try
	{
		writerI->Update();
	}
	catch (itk::ExceptionObject & excep) {
		std::cerr << "Exception caught !" << std::endl;
		std::cerr << excep << std::endl;
		system("pause");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}