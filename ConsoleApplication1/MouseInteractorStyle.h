#pragma once

#include<vtkInteractorStyleTrackballCamera.h>
#include <vtkSmartPointer.h>
#include <vtkNamedColors.h>
#include <vtkProperty.h>
#include <vtkActor.h>
#include<vtkRenderer.h>
#include<vtkRenderWindow.h>
#include<vtkRenderWindowInteractor.h>
#include<vtkRendererCollection.h>
#include <vtkCellPicker.h>
#include <vtkSphereSource.h>
#include <vtkMapper.h>
#include <vtkPointPicker.h>
#include<vtkPolyDataMapper.h>

class MouseInteractorStyle : public vtkInteractorStyleTrackballCamera
{
public:
    static MouseInteractorStyle* New();

    vtkTypeMacro(MouseInteractorStyle, vtkInteractorStyleTrackballCamera);

    MouseInteractorStyle()
    {
        displayActor = vtkSmartPointer<vtkActor>::New();
        displayActor->GetProperty()->SetColor(1.0, 0.0, 0.0);
    }

    virtual void OnLeftButtonDown() override;
    vtkPolyData* data = nullptr;
    vtkSmartPointer<vtkActor> displayActor = nullptr;
};


void pickTriangelGridOnSphereByMstyle();