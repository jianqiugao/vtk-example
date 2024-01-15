#pragma once


// vtkFlyingEdges3D was introduced in VTK >= 8.2
#if VTK_MAJOR_VERSION >= 9 || (VTK_MAJOR_VERSION >= 8 && VTK_MINOR_VERSION >= 2)
#define USE_FLYING_EDGES
#else
#undef USE_FLYING_EDGES
#endif
#define USE_FLYING_ "hello"

#ifdef USE_FLYING_EDGES
#include <vtkFlyingEdges3D.h>
#else
#include <vtkMarchingCubes.h>
#endif

#include <array>


# define renderPipeLine(name) \
vtkSmartPointer<vtkRenderer> name##aRenderer = vtkSmartPointer<vtkRenderer>::New();\
vtkSmartPointer<vtkRenderWindow> name##renWin = vtkSmartPointer<vtkRenderWindow>::New();\
name##renWin->AddRenderer(name##aRenderer);\
name##renWin->SetWindowName("MedicalDemo3");\
vtkSmartPointer<vtkRenderWindowInteractor> name##iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();\
name##iren->SetRenderWindow(renWin);\
name##renWin->SetSize(640, 480);

#include<vtkRenderer.h>
#include<vtkRenderWindow.h>
#include<vtkRenderWindowInteractor.h>
#include<vtkMetaImageReader.h>
#include<vtkDataSetMapper.h>
#include<vtkImageData.h>
#include<vtkActor.h>
#include<vtkStripper.h>
#include<vtkPolyDataMapper.h>
#include<vtkProperty.h>
#include<vtkVertexGlyphFilter.h>
#include<vtkVertexGlyphFilter.h>
#include<vtkMarchingCubes.h>
#include<vtkOutlineFilter.h>
#include<vtkLookupTable.h>
#include<vtkImageMapToColors.h>
#include<vtkImageActor.h>
#include<vtkImageMapper3D.h>
#include<vtkCamera.h>

int readFullHeadDataAndShow();

