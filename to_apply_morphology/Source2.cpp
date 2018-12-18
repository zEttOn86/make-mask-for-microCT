/*
* This implementation use itk
* Erosion
* @auther tozawa
* @history
* 20171110
*/
#define ITK_IO_FACTORY_REGISTER_MANAGER
#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>
#include "itkBinaryBallStructuringElement.h"
#include "itkBinaryErodeImageFilter.h"

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
	typedef itk::ImageFileReader<ImageType> ImageReaderType;//�����̒�`
	ImageReaderType::Pointer Input = ImageReaderType::New();//�t�B���^�̒�`
	Input->SetFileName(argv[1]);//�ǂݍ��ݐ�p�X�̐ݒ�

	typedef itk::BinaryBallStructuringElement<ImageType::PixelType, NDims> 
		StructuringElementType;
	StructuringElementType structuringElement;
	structuringElement.SetRadius(radius);
	structuringElement.CreateStructuringElement();

	typedef itk::BinaryErodeImageFilter<ImageType, ImageType, StructuringElementType> 
		BinaryErodeImageFilterType;
	BinaryErodeImageFilterType::Pointer erodeFilter
		= BinaryErodeImageFilterType::New();
	erodeFilter->SetInput(Input->GetOutput());
	erodeFilter->SetKernel(structuringElement);

	//�o�͉摜�̗p��
	typedef itk::ImageFileWriter<ImageType> ImageWriterType;
	ImageWriterType::Pointer writerI = ImageWriterType::New();
	writerI->SetFileName(argv[2]);
	writerI->SetInput(erodeFilter->GetOutput());
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
