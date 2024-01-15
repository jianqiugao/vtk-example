#pragma once
#include<iostream>
#include <vector>
#include <fstream>
#include <math.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp> 
#include <opencv2/highgui/highgui.hpp> 
#include <opencv2/imgproc/imgproc.hpp>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include<vtkParametricSpline.h>
#include<vtkParametricFunctionSource.h> // 这里的source和不带source的有什么区别
#include<vtkPolyDataMapper.h>
#include<vtkActor.h>
#include<vtkProperty.h>
#include<vtkTubeFilter.h>
#include<vtkRenderer.h>
#include<vtkRenderWindowInteractor.h>
#include<vtkRenderWindow.h>
using cv::Mat;

typedef struct My_Scalefactor//定义缩放因子结构体
{
	double IamgeAXfactor;//ImageA上二维点X坐标除以D1
	double ImageAYfactor;//ImageA上二维点Y坐标除以D1
	double ImageBXfactor;//ImageA上二维点X坐标除以D2
	double ImageBYfactor;//ImageA上二维点X坐标除以D2
};
typedef struct My2dPoint//定义自己的二维坐标点结构体
{
	double x;
	double y;
};
typedef struct My3dPoint//定义自己的三维坐标点结构体
{
	double x;
	double y;
	double z;
};



void InitMat(cv::Mat& m, double* num);
//用一维数组初始化OpenCV矩阵Mat对象

cv::Mat GenerateRxmat(double jiaodu);
//构造Rx矩阵OpenCV矩阵Mat对象,参数角度为角度,直接返回一个Mat对象

float ExtractMatIJValue(cv::Mat& M, int i, int j);//提取Mat对象第i行第j列的数值,M为Mat对象，ij为行列值

cv::Mat Generate3DAmat(cv::Mat& M, My_Scalefactor& myfactor);//生成最后求三维点的A矩阵，M为Mat类对象,为先求出的R矩阵，My_Scalefactor为struct

cv::Mat Genreate3Damat(cv::Mat& M, My_Scalefactor& myfactor);//生成求B矩阵的a矩阵

cv::Mat Generate3DTmat(double T);//生成求B矩阵的T矩阵

cv::Mat Generate3Dbmat(cv::Mat& M, My_Scalefactor& myfactor);//生成求B矩阵的b矩阵

cv::Mat Generate3DBmat(cv::Mat& a, cv::Mat& b, cv::Mat& t);//生成最后求三维点的B矩阵

void plotVesselbuTubeFilter();

