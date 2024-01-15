#pragma once
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkSmartPointer.h>
#include <vtkDataSetMapper.h>
#include <vtkPolyData.h>
#include <vtkCellPicker.h>
#include <vtkSelectionNode.h>
#include <vtkSelection.h>
#include <vtkExtractSelection.h>
#include <vtkPolyData.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include<vtkRendererCollection.h>
#include <vtkActor.h>
#include<vtkProperty.h>
#include<vtkPolyData.h>
#include<vtkPolyDataMapper.h>

class CellPickerInteractorStyle :public vtkInteractorStyleTrackballCamera
{
public:
	static CellPickerInteractorStyle* New();

	CellPickerInteractorStyle()
	{
		selectedMapper = vtkSmartPointer<vtkDataSetMapper>::New();
		selectedActor = vtkSmartPointer<vtkActor>::New();
		
	}
	virtual void OnLeftButtonDown() ;
	

	//virtual void 
	vtkSmartPointer<vtkPolyData> data = nullptr;
	
private:
	vtkSmartPointer<vtkPolyData>      polyData;
	vtkSmartPointer<vtkDataSetMapper> selectedMapper;
	vtkSmartPointer<vtkActor>         selectedActor;
};
