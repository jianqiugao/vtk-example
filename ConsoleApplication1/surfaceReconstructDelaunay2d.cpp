#include<surfaceReconstructDelaunay2d.h>

void surfaceReconstructDelaunay2d()
{
	vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
	unsigned int gridsize = 60;

	for (unsigned int i = 0; i < gridsize; i++)
	{
		for (unsigned int j = 0; j < 100; j++)
		{
			points->InsertNextPoint(2* cos(3.14 * j / gridsize), 2 * sin(3.14 * j / gridsize), 0.01*i);
		}
	};

	vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
	polydata->SetPoints(points);
	cout << "hello" << endl;

	// 三维重建部分
	vtkSmartPointer<vtkSurfaceReconstructionFilter> surf = vtkSmartPointer<vtkSurfaceReconstructionFilter>::New();
	surf->SetInputData(polydata);
	surf->SetNeighborhoodSize(5);
	surf->SetSampleSpacing(0.01);
	surf->Modified();
	surf->Update(); // 这个surf显示出来什么都没有，不知道怎么回事。

	cout <<__LINE__ << endl;
	vtkSmartPointer<vtkContourFilter> contour = vtkSmartPointer<vtkContourFilter>::New();
	contour->SetInputConnection(surf->GetOutputPort());
	contour->SetValue(0, 0.0);
	contour->Update(); // 选择距离表面距离为0的等值面
	cout << __LINE__ << endl;

	/*vtkSmartPointer<vtkDelaunay2D> delauy = vtkSmartPointer<vtkDelaunay2D>::New();
	delauy->SetInputData(polydata);
	delauy->Update();*/

	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(contour->GetOutputPort());
	mapper->Update();
	cout << __LINE__ << endl;
	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);
	cout << __LINE__ << endl;
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(actor);
	cout << __LINE__ << endl;
	// 二维的网格面重建
	vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);
	cout << __LINE__ << endl;
	vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	interactor->SetRenderWindow(renderWindow);
	cout << __LINE__ << endl;
	renderWindow->Render();
	interactor->Start();
}