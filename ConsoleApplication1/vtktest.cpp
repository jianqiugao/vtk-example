#include"vtktest.h"

void vtktest()
{
	vtkSmartPointer<vtkConeSource> cone = vtkSmartPointer<vtkConeSource>::New();

	cone->SetAngle(15);
	cone->SetRadius(1);
	cone->SetResolution(60);
	cone->Update();

	vtkSmartPointer<vtkSphereSource> sphere = vtkSmartPointer<vtkSphereSource>::New();
	sphere->SetCenter(2, 0, 0);
	sphere->SetRadius(1);
	sphere->SetThetaResolution(60);
	sphere->SetPhiResolution(60);
	sphere->Update();
	
	vtkSmartPointer<vtkPolyDataMapper> smapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	smapper->SetInputData(sphere->GetOutput());
	
	vtkSmartPointer<vtkActor> sactor = vtkSmartPointer<vtkActor>::New();
	sactor->SetMapper(smapper);
	sactor->GetProperty()->SetColor(1, 0, 0);


	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputData(cone->GetOutput());

	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	vtkSmartPointer<vtkRenderer>render = vtkSmartPointer<vtkRenderer>::New();
	render->AddActor(actor);
	render->AddActor(sactor);

	vtkSmartPointer<vtkRenderWindow> renderwindow = vtkSmartPointer<vtkRenderWindow>::New();
	renderwindow->AddRenderer(render);

	vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	interactor->SetRenderWindow(renderwindow);

	interactor->Initialize();
	interactor->Start();
}

void readimageanddrawline()
{
vtkSmartPointer<vtkPNGReader> reader = vtkSmartPointer<vtkPNGReader>::New();
reader->SetFileName("C:\\gitlab\\vs\\ConsoleApplication1\\x64\\Debug\\123.png");
reader->Update();
vtkSmartPointer<vtkImageViewer2> viewer = vtkSmartPointer<vtkImageViewer2>::New();
viewer->SetInputConnection(reader->GetOutputPort());

vtkSmartPointer<vtkRenderer>render = vtkSmartPointer<vtkRenderer>::New();
vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
interactor->Initialize();
interactor->SetRenderWindow(viewer->GetRenderWindow());
viewer->SetupInteractor(interactor);

vtkSmartPointer<vtkContourWidget> contourWidget = vtkSmartPointer<vtkContourWidget>::New();
contourWidget->SetInteractor(interactor);

vtkOrientedGlyphContourRepresentation* rep = dynamic_cast<vtkOrientedGlyphContourRepresentation*>(contourWidget->GetRepresentation());
vtkSmartPointer<vtkPointPlacer> pointPlacer = vtkSmartPointer<vtkPointPlacer>::New();


rep->GetLinesProperty()->SetColor(1, 0, 0);
rep->GetLinesProperty()->SetLineWidth(3.0);
rep->SetPointPlacer(pointPlacer);
contourWidget->EnabledOn();




viewer->Render();
interactor->Start();
}