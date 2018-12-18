/*
* Make label for MicroCT
* @auther tozawa
* @history 20171108
* 
* #define ITK_IO_FACTORY_REGISTER_MANAGER
* #include "itkImageFileReader.h"
* #include "itkImageFileWriter.h"
* Add project to these files.
* itkTransformIOFactoryRegisterManager.h
* itkImageIOFactoryRegisterManager.h
* @method
* 1.median(3*3*3)
* 2.otsu method
* 3.Closing(dilation=3, erosion=3)
*/