#pragma once
#include <vtkInteractorStyleTrackballActor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkActor.h>
#include <vtkSphereSource.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include<vtkRenderWindowInteractor.h>
#include <vtkRenderWindowCollection.h>
#include<vtkPicker.h>
#include<vtkPolyDataMapper.h>
#include<vtkRendererCollection.h>
#include<vtkProperty.h>
#include<vtkCellPicker.h>

/*************************************************************************************************/
class PointPickerInteractorStyle : public vtkInteractorStyleTrackballCamera
{
public:
 static PointPickerInteractorStyle* New();
 vtkTypeMacro(PointPickerInteractorStyle, vtkInteractorStyleTrackballCamera);
 virtual void OnLeftButtonDown();
 
};

/************************************************************************************************/


void pickpointGridOnSphere();