#pragma once
#include<vtkCommand.h>
#include<vtkImageReslice.h>
#include<vtkImageMapToColors.h>
#include<vtkRenderWindowInteractor.h>
#include<vtkMatrix4x4.h>
#include<vtkInteractorStyle.h>
#include<vtkImageData.h>

class vtkImageInteractionCallback : public vtkCommand
{
public:
    static vtkImageInteractionCallback* New()
    {
        return new vtkImageInteractionCallback;
    }

    vtkImageInteractionCallback();

    void SetImageReslice(vtkImageReslice* reslice);

    void SetImageMapToColors(vtkImageMapToColors* mapToColors);

    vtkImageReslice* GetImageReslice();

    void SetInteractor(vtkRenderWindowInteractor* interactor);

    vtkRenderWindowInteractor* GetInteractor();

    virtual void Execute(vtkObject*, unsigned long event, void*);

private:
    int Slicing;
    vtkImageReslice* ImageReslice;
    vtkRenderWindowInteractor* Interactor;
    vtkImageMapToColors* mapToColors;
};
