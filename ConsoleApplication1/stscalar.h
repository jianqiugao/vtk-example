#pragma once
#include <vtkSmartPointer.h>
#include <vtkDoubleArray.h>
#include <vtkCylinder.h>
#include <vtkCylinderSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkPointData.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkAxesActor.h>
#include <vector>
#include <array>
#include <vtkFloatArray.h>
#include <vtkLookupTable.h>
#include <vtkRegularPolygonSource.h>
#include <vtkLinearExtrusionFilter.h>
#include <vtkTransformFilter.h>
#include <vtkLookupTable.h>
#include <vtkTransform.h>
#include <vtkTransformFilter.h>
#include <vtkProperty.h>
#include <vtkNamedColors.h>
#include "vtkColor.h"
#include "vtkLine.h"
#include "vtkPNGReader.h"
#include "vtkPlaneSource.h"
#include "vtkSTLReader.h"
#include "vtkImageViewer2.h"
#include <string>
#include <vector>
#include<vtkAlgorithmOutput.h>

void setscalar();
void scalaronfigure();
void scalaronfigure();
void create2drectange();
void createasphere();
void plotacircle() ;
void plottrianglesingleton();
int setexture();
int readstlfile();
int readjpeg();

int readtxtandplotpoint();
