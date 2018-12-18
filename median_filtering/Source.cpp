/*
* This implementation use ITK
* @auther tozawa
* @history 20171108
*/

#define ITK_IO_FACTORY_REGISTER_MANAGER
#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>
#include "itkMedianImageFilter.h"

typedef unsigned char T_TYPE;
void main(int argc, char **argv)
{
	if (argc != 4) {
		std::cerr << "Usage : " << std::endl;
		std::cerr << argv[0] << " inputFile(.mhd) outputFileName(.mhd) radius" << std::endl;
		exit(1);
	}
	const unsigned int NDims = 3;//�摜�̎�����
	typedef itk::Image<T_TYPE, NDims> ImageType;//���͉摜�̌^
	typedef itk::MedianImageFilter<ImageType, ImageType> MedianFilterType;
	//���͉摜�̓ǂݍ��ݏ���
	typedef itk::ImageFileReader<ImageType> ImageReaderType;//�����̒�`
	ImageReaderType::Pointer Input = ImageReaderType::New();//�t�B���^�̒�`
	Input->SetFileName(argv[1]);//�ǂݍ��ݐ�p�X�̐ݒ�
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
	MedianFilterType::Pointer medianFilter = MedianFilterType::New();
	MedianFilterType::InputSizeType radius;
	radius.Fill(atoi(argv[3]));

	medianFilter->SetRadius(radius);
	medianFilter->SetInput(Input->GetOutput());

	typedef itk::ImageFileWriter<ImageType> ImageWriterType;
	ImageWriterType::Pointer writerI = ImageWriterType::New();
	writerI->SetFileName(argv[2]);
	writerI->SetInput(medianFilter->GetOutput());
	try
	{
		writerI->Update();
	}
	catch (itk::ExceptionObject & excep) {
		std::cerr << "Exception caught !" << std::endl;
		std::cerr << excep << std::endl;
		system("pause");
		exit(1);;
	}
}