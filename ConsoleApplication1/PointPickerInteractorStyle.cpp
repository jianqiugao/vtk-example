#include<PointPickerInteractorStyle.h>

void PointPickerInteractorStyle::OnLeftButtonDown()
{
	// ��ӡ����������λ��
	std::cout << "Picking pixel: " << this->Interactor->GetEventPosition()[0] << " " << this->Interactor->GetEventPosition()[1] << std::endl;
	// ע��ʰȡ�㺯��
	this->Interactor->GetPicker()->
		Pick(
			this->Interactor->GetEventPosition()[0],
			this->Interactor->GetEventPosition()[1],
			0, //��Ҫ��ȡ���Ƕ�άƽ������ص�����  
			this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()//��ȡvtkrender����
		);

	// ��ӡʰȡ��ռ�λ��
	double picked[3];
	this->Interactor->GetPicker()->GetPickPosition(picked);
	std::cout << "Picked value: " << picked[0] << " " << picked[1] << " " << picked[2] << std::endl;

	// ��ʰȡ����б��
	vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
	sphereSource->Update();
	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(sphereSource->GetOutputPort());
	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);
	actor->SetPosition(picked);
	actor->SetScale(0.01);
	actor->GetProperty()->SetColor(1.0, 1.0, 0.0);
	this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(actor);
	vtkInteractorStyleTrackballCamera::OnLeftButtonDown(); // ����ִ������Ĳ���
}


vtkStandardNewMacro(PointPickerInteractorStyle); //ʵ��������캯��

void pickpointGridOnSphere() {

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
	actor->GetProperty()->SetColor(1.0, 0.0, 0.0); // ������ɫΪ��ɫ

	//4
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
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
	vtkSmartPointer<PointPickerInteractorStyle> style = vtkSmartPointer<PointPickerInteractorStyle>::New();
	renderWindowInteractor->SetInteractorStyle(style);
	renderWindow->SetSize(800, 600);
	renderWindow->Render();
	renderWindowInteractor->Initialize();
	renderWindowInteractor->Start();
}