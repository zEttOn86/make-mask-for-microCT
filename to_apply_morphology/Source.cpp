/*
* This implementation use itk
* Dilation
* @auther tozawa
* @history 
* 20171110
* 20171108
*/

#define ITK_IO_FACTORY_REGISTER_MANAGER
#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>
#include "itkBinaryBallStructuringElement.h"
#include "itkBinaryDilateImageFilter.h"
typedef unsigned char T_TYPE;
int main(int argc, char **argv)
{
	if (argc != 4) {
		std::cerr << "Usage : " << std::endl;
		std::cerr << argv[0] << " inputFile(.mhd) outputFileName(.mhd) radius" << std::endl;
		exit(1);
	}
	unsigned int radius = atoi(argv[3]);

	const unsigned char NDims = 3;
	typedef itk::Image<T_TYPE, NDims> ImageType;
	typedef itk::ImageFileReader<ImageType> ImageReaderType;//処理の定義
	ImageReaderType::Pointer Input = ImageReaderType::New();//フィルタの定義
	Input->SetFileName(argv[1]);//読み込み先パスの設定
	
	typedef itk::BinaryBallStructuringElement<ImageType::PixelType, NDims> StructuringElementType;
	StructuringElementType structuringElement;
	structuringElement.SetRadius(radius);
	structuringElement.CreateStructuringElement();

	typedef itk::BinaryDilateImageFilter<ImageType, ImageType, StructuringElementType> BinaryDilateImageFilterType;
	BinaryDilateImageFilterType::Pointer dilateFilter
		= BinaryDilateImageFilterType::New();
	dilateFilter->SetInput(Input->GetOutput());
	dilateFilter->SetKernel(structuringElement);

	//出力画像の用意
	typedef itk::ImageFileWriter<ImageType> ImageWriterType;
	ImageWriterType::Pointer writerI = ImageWriterType::New();
	writerI->SetFileName(argv[2]);
	writerI->SetInput(dilateFilter->GetOutput());
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
