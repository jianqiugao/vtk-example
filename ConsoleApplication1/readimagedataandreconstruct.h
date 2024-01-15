#pragma once
#include <vtkVolume16Reader.h>
#include <vtkMarchingCubes.h>
#include <vtkStripper.h>
#include<vtkPolyDataMapper.h>
#include<vtkActor.h>
#include<vtkRenderer.h>
#include<vtkRenderWindow.h>
#include<vtkRenderWindowInteractor.h>


void readimagedataandreconstruct();