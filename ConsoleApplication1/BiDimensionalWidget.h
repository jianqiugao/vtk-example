#pragma once
#include <vtkCommand.h>
#include <vtkSmartPointer.h>
#include <vtkJPEGReader.h>
#include <vtkImageActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>

#include <vtkDistanceWidget.h>
#include <vtkDistanceRepresentation.h>
#include <vtkAngleWidget.h>
#include <vtkProperty2D.h>
#include <vtkLeaderActor2D.h>
#include <vtkAngleRepresentation2D.h>
#include <vtkBiDimensionalWidget.h>
#include <vtkBiDimensionalRepresentation2D.h>
#include <vtkPNGReader.h>
#include <Windows.h>
#include<vtkEvent.h>
#include <vtkWidgetEventTranslator.h>
#include<vtkWidgetEvent.h>
#include<vtkImageTracerWidget.h>
#include<vtkTextWidget.h>
#include<vtkDistanceWidget.h>

void BiDimensionalWidgetexample();

class vtkBiDimensionalCallback : public vtkCommand
{
public:
    static	vtkBiDimensionalCallback* New()
    {
        return new vtkBiDimensionalCallback;
    }

    virtual void Execute(vtkObject* caller, unsigned long, void*);
    vtkBiDimensionalCallback() {} //���ǹ��캯����û�����ûص�����
};
