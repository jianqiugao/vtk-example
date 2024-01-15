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
// �ѵ���ȡ������Ȼ��ע��һ��polydata�У�ʹ��vtkSurfaceReconstructionFilterʵ�־��뺯����Ȼ����vtkContourFilter��ȡ��ֵ�������ʾ����

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


	// ��ά�ؽ�����
	vtkSmartPointer<vtkSurfaceReconstructionFilter> surf = vtkSmartPointer<vtkSurfaceReconstructionFilter>::New();
	surf->SetInputData(points);
	surf->SetNeighborhoodSize(20);
	surf->SetSampleSpacing(0.01);
	surf->Modified();
	surf->Update(); // ���surf ��Ҫ��vtkdatasetmapper����ʾ����polydatamapper��ʾ�Ļ�����ʲô��û�У���֪����ô���¡�


	vtkSmartPointer<vtkContourFilter> contour = vtkSmartPointer<vtkContourFilter>::New();
	contour->SetInputConnection(surf->GetOutputPort());
	contour->SetValue(0, 0.0);
	contour->Update(); // ѡ�����������Ϊ0�ĵ�ֵ��

	// ��ԭʼ�ĵ㴦��һ��չʾ����,��ҪĿ�����Զ��ѵ�����ΪvertexȻ��ͨ��output�ӿ�չʾ����
	vtkSmartPointer<vtkVertexGlyphFilter> vtkgaly = vtkSmartPointer<vtkVertexGlyphFilter>::New();
	vtkSmartPointer<vtkPolyData> points_2 = vtkSmartPointer<vtkPolyData>::New();
	points_2->SetPoints(points_1);
	vtkgaly->AddInputData(points_2); // ��ʵ��Ҫ���ǵ��ǲ���ֱ����ʾ�����ģ�����һ����������ݣ�ÿһ���㶼������Ϊһ��vertex���͵�vtkcellarray
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
	filtertMapper->SetInputData((vtkDataSet * )surf->GetOutput()); //�����actor��Ҫת��Ϊdataset

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
