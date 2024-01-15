#pragma once
#include <vtkActor.h>
#include <vtkCallbackCommand.h>
#include <vtkImageActor.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkImageMapper3D.h>
#include <vtkImageTracerWidget.h>
#include <vtkInteractorStyleImage.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <array>
#include <vtkAutoInit.h>
#include <vtkObject.h>
#include <vtkPNGReader.h>
#include <vtkBMPReader.h>
#include <vtkImageData.h>
#include <vtkImageAppendComponents.h>
#include <vtkImageAccumulate.h>
#include <vtkImageStencilToImage.h>
#include <vtkImageAppendComponents.h>
#include <vtkPolyDataToImageStencil.h> 
#include<vtkPointData.h>
#include<vtkPoints.h>
#include <vtkConeSource.h>


void CallbackFunction(vtkObject* caller, long unsigned int eventId, void* clientData, void* callData);


void plotlineon2dcanvas();