#pragma once
#include <vtkInteractorStyleTrackballCamera.h>
#include<vtkActor.h>
#include<vtkRenderWindowInteractor.h>
#include<vtkPicker.h>
#include<vtkRenderWindow.h>
#include<vtkPolyDataMapper.h>
#include<vtkRendererCollection.h>
#include<vtkPoints.h>
#include<vtkPolyData.h>
#include<vtkPolyLine.h>
#include<vtkProperty.h>
#include<Windows.h>
#include <vtkPNGReader.h>
#include<vtkImageViewer2.h>
#include<vtkImageViewer.h>
#include<vtkProp.h>
#include<vtkImageActor.h>
#include<vtkSphereSource.h>
#include<vtkCellPicker.h>


// ÔÚÈýÎ¬³¡¾°»æ»­

class PointPickerInteractorStyle1 : public vtkInteractorStyleTrackballCamera
{

public:
    static PointPickerInteractorStyle1* New();
    vtkTypeMacro(PointPickerInteractorStyle1, vtkInteractorStyleTrackballCamera);
    virtual void OnLeftButtonDown();
    virtual void OnMouseMove();
    
private:
    vtkSmartPointer<vtkPoints> m_points = vtkSmartPointer<vtkPoints>::New();
    vtkSmartPointer<vtkCellArray> cells = vtkSmartPointer<vtkCellArray>::New();
    vtkSmartPointer<vtkPolyLine> polyLine = vtkSmartPointer<vtkPolyLine>::New();
    vtkSmartPointer<vtkPolyData>  outputVector = vtkSmartPointer<vtkPolyData>::New();
};

void plotOnPicture();

void plotOn3d();