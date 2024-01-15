#pragma once

#include<vtkPNGReader.h>
#include<vtkImageViewer2.h>
#include<vtkImageFFT.h>
#include<vtkImageExtractComponents.h>
#include<vtkImageData.h>
#include<vtkImageShiftScale.h>
#include<vtkImageRFFT.h>
#include<vtkImageCast.h>
#include<vtkImageIdealLowPass.h>
#include<vtkImageIdealHighPass.h>
#include<vtkPNGReader.h>
#include<vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>



void figureFourierTransformAndFilter();