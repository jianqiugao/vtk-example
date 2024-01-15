#include<pickTriangelGridOnSphere.h>


void pickTriangelGridOnSphere() {

	vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
	sphereSource->SetRadius(10);
	sphereSource->SetThetaResolution(60);
	sphereSource->SetPhiResolution(60);

	// 2 
	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(sphereSource->GetOutputPort());
	//3
	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);
	actor->GetProperty()->SetColor(1.0, 0.0, 0.0); // 设置颜色为红色


	//4
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	//renderer->SetBackground(100, 100, 100);
	//renderer->GetActiveCamera()->SetPosition(0, -1, 0);
	//renderer->GetActiveCamera()->SetFocalPoint(0, 0, 0);
	//renderer->GetActiveCamera()->SetViewUp(0, 0, 1);
	//renderer->GetActiveCamera()->Azimuth(30);
	//renderer->GetActiveCamera()->Elevation(30);
	renderer->ResetCamera();
	renderer->AddActor(actor);

	// 5
	vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);


	// 6
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(renderWindow);

	vtkSmartPointer<vtkCellPicker> picker = vtkSmartPointer<vtkCellPicker>::New();
	renderWindowInteractor->SetPicker(picker);

	// 7
	vtkSmartPointer<CellPickerInteractorStyle> style = vtkSmartPointer<CellPickerInteractorStyle>::New();
	style->data = sphereSource->GetOutput();
	renderWindowInteractor->SetInteractorStyle(style);


	renderWindow->SetSize(800, 600);
	renderWindow->Render();
	renderWindowInteractor->Initialize();
	renderWindowInteractor->Start();
}