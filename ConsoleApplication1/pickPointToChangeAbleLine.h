#pragma once
#include <vtkCommand.h>
#include <vtkSmartPointer.h>
#include <vtkContourWidget.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkOrientedGlyphContourRepresentation.h>
#include <vtkPolygonalSurfacePointPlacer.h>
#include <vtkPolyDataCollection.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

class MyCallback : public vtkCommand
{
public:
	static MyCallback* New()
	{
		return new MyCallback;
	}
	MyCallback()
	{
	}

	virtual void Execute(vtkObject* caller, unsigned long, void*)
	{
		vtkContourWidget* contourWidget = reinterpret_cast<vtkContourWidget*>(caller);
		//vtkContourRepresentation* rep = static_cast<vtkContourRepresentation*>();

	}

	void SetSphereSource(vtkSmartPointer<vtkSphereSource> sphere)
	{
		this->SphereSource = sphere;
	}

private:
	vtkSmartPointer<vtkSphereSource> SphereSource;
};



void pickPointToChangeAbleLine();
