#include<surfacereconstruct.h>
#include<vtkPolyData.h>
#include<vtkPolyDataMapper.h>
#include<vtkActor.h>
#include<vtkProperty.h>
#include<vtkRenderer.h>
#include<vtkRenderWindow.h>
#include<vtkRenderWindowInteractor.h>
#include<vtkImageViewer2.h>
#include<vtkDataSetMapper.h>
// 把点提取出来，然后注入一个polydata中，使用vtkSurfaceReconstructionFilter实现距离函数，然后用vtkContourFilter提取等值面最后显示出来

void surfaceReconstruction()
{
	std::string route = "C:\\gitlab\\vs\\ctest\\ctest\\vtk\\VTK-9.3.0\\Testing\\Data\\fran_cut.vtk";
	vtkSmartPointer<vtkPolyDataReader> reader = vtkSmartPointer<vtkPolyDataReader>::New();
	reader->SetFileName(route.c_str());
	reader->Update();


	vtkSmartPointer<vtkPolyData> points = vtkSmartPointer<vtkPolyData>::New();
	points->SetPoints(reader->GetOutput()->GetPoints());

	vtkSmartPointer<vtkPoints> points_1 = vtkSmartPointer<vtkPoints>::New();
	points_1=reader->GetOutput()->GetPoints();


	// 三维重建部分
	vtkSmartPointer<vtkSurfaceReconstructionFilter> surf = vtkSmartPointer<vtkSurfaceReconstructionFilter>::New();
	surf->SetInputData(points);
	surf->SetNeighborhoodSize(20);
	surf->SetSampleSpacing(0.01);
	surf->Modified();
	surf->Update(); // 这个surf 需要用vtkdatasetmapper来显示，用polydatamapper显示的话出来什么都没有，不知道怎么回事。


	vtkSmartPointer<vtkContourFilter> contour = vtkSmartPointer<vtkContourFilter>::New();
	contour->SetInputConnection(surf->GetOutputPort());
	contour->SetValue(0, 0.0);
	contour->Update(); // 选择距离表面距离为0的等值面

	// 把原始的点处理一下展示出来,主要目的是自动把点设置为vertex然后通过output接口展示出来
	vtkSmartPointer<vtkVertexGlyphFilter> vtkgaly = vtkSmartPointer<vtkVertexGlyphFilter>::New();
	vtkSmartPointer<vtkPolyData> points_2 = vtkSmartPointer<vtkPolyData>::New();
	points_2->SetPoints(points_1);
	vtkgaly->AddInputData(points_2); // 其实主要还是点是不能直接显示出来的，创建一个多边形数据，每一个点都被设置为一个vertex类型的vtkcellarray
	vtkgaly->Update();

	vtkSmartPointer<vtkPolyDataMapper> pointMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	pointMapper->SetInputData(vtkgaly->GetOutput());

	vtkSmartPointer<vtkActor> pointActor = vtkSmartPointer<vtkActor>::New();
	pointActor->SetMapper(pointMapper);
	pointActor->GetProperty()->SetColor(1, 0, 0);
	pointActor->GetProperty()->SetPointSize(4);


	vtkSmartPointer<vtkPolyDataMapper> contourMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	contourMapper->SetInputData(contour->GetOutput());
	vtkSmartPointer<vtkActor> contourActor = vtkSmartPointer<vtkActor>::New();
	contourActor->SetMapper(contourMapper);


	vtkSmartPointer<vtkPolyDataMapper> rawMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	rawMapper->SetInputData(reader->GetOutput());
	vtkSmartPointer<vtkActor> rawActor = vtkSmartPointer<vtkActor>::New();
	rawActor->SetMapper(rawMapper);

	///
	double pointView[4] = { 0, 0, 0.25, 1 };
	double contourView[4] = { 0.25, 0, 0.5, 1 };
	double rawView[4] = { 0.5, 0, 0.75, 1 };
	double filterview[4] = { 0.75, 0, 1, 1 };

	vtkSmartPointer<vtkRenderer> pointRender = vtkSmartPointer<vtkRenderer>::New();
	pointRender->AddActor(pointActor);
	pointRender->SetViewport(pointView);
	pointRender->SetBackground(1, 1, 1);

	vtkSmartPointer<vtkRenderer> contourRender = vtkSmartPointer<vtkRenderer>::New();
	contourRender->AddActor(contourActor);
	contourRender->SetViewport(contourView);
	contourRender->SetBackground(0, 1, 0);

	vtkSmartPointer<vtkRenderer> rawRender = vtkSmartPointer<vtkRenderer>::New();
	rawRender->AddActor(rawActor);
	rawRender->SetViewport(rawView);
	rawRender->SetBackground(0, 0, 1);


	vtkSmartPointer<vtkDataSetMapper> filtertMapper = vtkSmartPointer<vtkDataSetMapper>::New();
	filtertMapper->SetInputData((vtkDataSet * )surf->GetOutput()); //这里的actor需要转换为dataset

	vtkSmartPointer<vtkActor> fliterActor = vtkSmartPointer<vtkActor>::New();
	fliterActor->SetMapper(filtertMapper);
	fliterActor->GetProperty()->SetColor(1, 0, 0);
	fliterActor->GetProperty()->SetPointSize(4);

	vtkSmartPointer<vtkRenderer> filterRender = vtkSmartPointer<vtkRenderer>::New();
	filterRender->AddActor(fliterActor);
	filterRender->SetViewport(filterview);
	filterRender->SetBackground(1, 1, 1);


	pointRender->GetActiveCamera()->SetPosition(0, -1, 0);
	pointRender->GetActiveCamera()->SetFocalPoint(0, 0, 0);
	pointRender->GetActiveCamera()->SetViewUp(0, 0, 1);
	pointRender->GetActiveCamera()->Azimuth(30);
	pointRender->GetActiveCamera()->Elevation(30);
	pointRender->ResetCamera();
	contourRender->SetActiveCamera(pointRender->GetActiveCamera());
	rawRender->SetActiveCamera(pointRender->GetActiveCamera());
	filterRender->SetActiveCamera(pointRender->GetActiveCamera());


	vtkSmartPointer<vtkRenderWindow> rw = vtkSmartPointer<vtkRenderWindow>::New();
	rw->AddRenderer(pointRender);
	rw->AddRenderer(contourRender);
	rw->AddRenderer(rawRender);
	rw->AddRenderer(filterRender);
	rw->SetSize(640, 320);
	rw->SetWindowName("Surface Reconstruction ");
	rw->Render();

	vtkSmartPointer<vtkRenderWindowInteractor> rwi = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	rwi->SetRenderWindow(rw);
	rwi->Initialize();
	rwi->Start();
}
