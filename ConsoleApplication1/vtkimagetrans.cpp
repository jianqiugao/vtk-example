#include<vtkimagetrans.h>

void imagetrans()
{
	std::string route = "C:\\gitlab\\vs\\ctest\\ctest\\vtk\\Data\\HeadMRVolume.mhd";
	vtkSmartPointer<vtkMetaImageReader> reader = vtkSmartPointer<vtkMetaImageReader>::New(); //读*.mhd文件
	reader->SetFileName(route.c_str());
	reader->Update();
	// 第一种类型转换方案,数据读取进来之后转换为浮点数
	vtkSmartPointer<vtkImageCast> imgCast = vtkSmartPointer<vtkImageCast>::New();
	imgCast->SetInputData((vtkDataObject*)reader->GetOutput()); //由vtkImageData转换到父类的父类vtkDataObject
	imgCast->SetOutputScalarTypeToFloat();
	// 第二种类型转换方案
	vtkSmartPointer<vtkImageShiftScale> imgShiftScale = vtkSmartPointer<vtkImageShiftScale>::New();
	imgShiftScale->SetInputData((vtkDataObject*)reader->GetOutput());
	imgShiftScale->SetOutputScalarTypeToFloat();

	vtkSmartPointer<vtkImageViewer2> imgViewer = vtkSmartPointer<vtkImageViewer2>::New();
	imgViewer->SetInputConnection(imgCast->GetOutputPort());

	vtkSmartPointer<vtkRenderWindowInteractor> rwi = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	imgViewer->SetupInteractor(rwi);

	imgViewer->SetColorLevel(500);
	imgViewer->SetColorWindow(2000);
	imgViewer->SetSlice(20);
	imgViewer->SetSliceOrientationToXY();
	imgViewer->Render();

	/*imgViewer->GetRenderer()->ResetCamera();
	imgViewer->Render();*/
	imgViewer->GetRenderer()->SetBackground(1.0, 1.0, 1.0);
	imgViewer->SetSize(640, 480);
	imgViewer->GetRenderWindow()->SetWindowName("ImageTypeTrans");

	rwi->Start();
}