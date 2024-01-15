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
#include<vtkParametricFunctionSource.h> // �����source�Ͳ���source����ʲô����
#include<vtkPolyDataMapper.h>
#include<vtkActor.h>
#include<vtkProperty.h>
#include<vtkTubeFilter.h>
#include<vtkRenderer.h>
#include<vtkRenderWindowInteractor.h>
#include<vtkRenderWindow.h>
using cv::Mat;

typedef struct My_Scalefactor//�����������ӽṹ��
{
	double IamgeAXfactor;//ImageA�϶�ά��X�������D1
	double ImageAYfactor;//ImageA�϶�ά��Y�������D1
	double ImageBXfactor;//ImageA�϶�ά��X�������D2
	double ImageBYfactor;//ImageA�϶�ά��X�������D2
};
typedef struct My2dPoint//�����Լ��Ķ�ά�����ṹ��
{
	double x;
	double y;
};
typedef struct My3dPoint//�����Լ�����ά�����ṹ��
{
	double x;
	double y;
	double z;
};



void InitMat(cv::Mat& m, double* num);
//��һά�����ʼ��OpenCV����Mat����

cv::Mat GenerateRxmat(double jiaodu);
//����Rx����OpenCV����Mat����,�����Ƕ�Ϊ�Ƕ�,ֱ�ӷ���һ��Mat����

float ExtractMatIJValue(cv::Mat& M, int i, int j);//��ȡMat�����i�е�j�е���ֵ,MΪMat����ijΪ����ֵ

cv::Mat Generate3DAmat(cv::Mat& M, My_Scalefactor& myfactor);//�����������ά���A����MΪMat�����,Ϊ�������R����My_ScalefactorΪstruct

cv::Mat Genreate3Damat(cv::Mat& M, My_Scalefactor& myfactor);//������B�����a����

cv::Mat Generate3DTmat(double T);//������B�����T����

cv::Mat Generate3Dbmat(cv::Mat& M, My_Scalefactor& myfactor);//������B�����b����

cv::Mat Generate3DBmat(cv::Mat& a, cv::Mat& b, cv::Mat& t);//�����������ά���B����

void plotVesselbuTubeFilter();

