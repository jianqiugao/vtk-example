#pragma once

#include<vtkSmartPointer.h>
#include<vtkMetaImageReader.h>
#include<vtkImageData.h>
#include<vtkMatrix4x4.h>
#include<vtkImageReslice.h> // ����ͼƬʵ����ת�Ȳ����Ĺ���
#include<vtkLookupTable.h>
#include<vtkImageMapToColors.h>
#include <vtkImageActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkInteractorStyleImage.h>
#include<vtkRenderWindowInteractor.h>


#define cosin_caculate(x)  (cos((float(x) / 180 * 3.1415926)))
#define sine_caculate(x) (sin((float(x) / 180 * 3.1415926)))

//int main()
//{
//    vtkSmartPointer<vtkMetaImageReader> reader = vtkSmartPointer<vtkMetaImageReader>::New();
//    reader->SetFileName("C:\\gitlab\\vs\\ctest\\ctest\\vtk\\7.1data\\FullHead.mhd");
//    reader->Update();
//
//    int extent[6];
//    double spacing[3];
//    double origin[3];
//
//    reader->GetOutput()->GetExtent(extent);
//    reader->GetOutput()->GetSpacing(spacing);
//    reader->GetOutput()->GetOrigin(origin);
//
//    cout << "extent" << extent[0] << ":" << extent[1] << ":" << extent[2] << ":" << extent[3] << ":" << extent[4] << ":" << extent[5] << ":" << endl;
//    // extent0:255:0:255:0:93:
//    cout << "spacing" << spacing[0] << ":" << spacing[1] << ":" << spacing[2] << ":" << endl;
//    // spacing0.9375:0.9375:1.5:
//    cout << "origin" << origin[0] << ":" << origin[1] << ":" << origin[2] << ":" << endl;
//    // origin0:0:0:
//
//    double center[3];
//    for (size_t i = 0; i < 3; i++)  // ���forѭ��ʹ����ָ��ϲ���
//    {
//        center[i] = origin[i] + spacing[i] * 0.5 * (extent[i] + extent[2 * i + 1]);
//    }
//
//
//    cout << "center" << center[0] << ":" << center[1] << ":" << center[2] << ":" << endl;
//    cout << "cos=\n" << cosin_caculate(30) << endl;
//
//    double theta = 0;
//    static double axialElements[16] =
//    {
//        cosin_caculate(theta),-sine_caculate(theta), 0, 2,
//        sine_caculate(theta), cosin_caculate(theta), 0, 2,
//        0, 0, 1, 2,
//        0, 0, 0, 1
//    };
//
//
//    // �⼸��1�ֱ��ʾx,y,z��������Ĳ�������
//    // 2 �ĵط�����ֵ�������޸� ǰ���б�ʾ�����������������Լ�ƽ��ķ��������������б�ʾ��һ������λ��
//    // ��α任��������������ά�ռ��и����λ�ú���̬��������ת�����ƽ������д��ͬһ�������У��γ�4x4�ľ�����������������������Ա任�͸��ϱ任
//
//
//    vtkSmartPointer<vtkMatrix4x4> resliceAxes = vtkSmartPointer<vtkMatrix4x4>::New();
//    resliceAxes->DeepCopy(axialElements);
//    resliceAxes->SetElement(0, 3, center[0]);
//    resliceAxes->SetElement(1, 3, center[1]);
//    resliceAxes->SetElement(2, 3, center[2]);
//
//    cout << resliceAxes->GetElement(3, 2) << endl; // �����ķ�ʽ��numpy����һ��
//
//                                                  // ʵ��ͼƬ��ת�ȵĹ��ߺ���
//    vtkSmartPointer<vtkImageReslice> reslice = vtkSmartPointer<vtkImageReslice>::New();
//    reslice->SetInputConnection(reader->GetOutputPort());
//    reslice->SetOutputDimensionality(2);
//    reslice->SetResliceAxes(resliceAxes);
//    reslice->SetInterpolationModeToLinear();
//
//
//    vtkSmartPointer<vtkLookupTable> colorTable = vtkSmartPointer<vtkLookupTable>::New();
//    colorTable->SetRange(0, 1000);
//    colorTable->SetValueRange(0.0, 1.0);
//    colorTable->SetSaturationRange(0.0, 0.0);
//    colorTable->SetRampToLinear();
//    colorTable->Build();
//
//    vtkSmartPointer<vtkImageMapToColors> colorMap = vtkSmartPointer<vtkImageMapToColors>::New();
//    colorMap->SetLookupTable(colorTable);
//    colorMap->SetInputConnection(reslice->GetOutputPort());
//    colorMap->Update();
//
//    vtkSmartPointer<vtkImageActor> imgActor = vtkSmartPointer<vtkImageActor>::New();
//    imgActor->SetInputData(colorMap->GetOutput());
//
//    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
//    renderer->AddActor(imgActor);
//    renderer->SetBackground(1, 1, 1);
//
//    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
//    renderWindow->SetSize(500, 500);
//    renderWindow->AddRenderer(renderer);
//
//    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
//    vtkSmartPointer<vtkInteractorStyleImage> imagestyle = vtkSmartPointer<vtkInteractorStyleImage>::New();
//
//    renderWindowInteractor->SetInteractorStyle(imagestyle);
//    renderWindowInteractor->SetRenderWindow(renderWindow);
//    renderWindowInteractor->Initialize();
//
//    vtkSmartPointer<vtkImageInteractionCallback> callback = vtkSmartPointer<vtkImageInteractionCallback>::New();
//    callback->SetImageReslice(reslice);
//    callback->SetInteractor(renderWindowInteractor);
//    callback->SetImageMapToColors(colorMap);
//
//    imagestyle->AddObserver(vtkCommand::MouseMoveEvent, callback);
//    imagestyle->AddObserver(vtkCommand::LeftButtonPressEvent, callback);
//    imagestyle->AddObserver(vtkCommand::LeftButtonReleaseEvent, callback);
//
//    renderWindowInteractor->Start();
//    return EXIT_SUCCESS;
//}