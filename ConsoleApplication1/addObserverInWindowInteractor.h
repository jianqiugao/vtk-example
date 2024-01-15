#pragma once

#include <vtkObject.h>
#include <vtkPNGReader.h>
#include "vtkImageViewer2.h"
#include <vtkCallbackCommand.h>
#include <vtkObjectBase.h>
#include <vtkPNGReader.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>




void myCallBackFunc(vtkObject*, unsigned long eid, void* clientdata, void* calldata);

void addObserverInWindowInteractor();
