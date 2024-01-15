#include <vtkImageTracerWidgetOn2dCanvas.h>

void CallbackFunction(vtkObject* caller, long unsigned int eventId, void* clientData, void* callData)
{
	vtkImageTracerWidget* tracerWidget = static_cast<vtkImageTracerWidget*>(caller);

	vtkSmartPointer<vtkPolyData> path = vtkSmartPointer<vtkPolyData>::New();
	tracerWidget->InitializeHandles(path->GetPoints());
	tracerWidget->GetPath(path);
	cout << "点数" << path->GetNumberOfPoints() << endl;
	cout << "线数" << path->GetNumberOfLines() << endl;
	std::cout << "There are " << path->GetNumberOfPoints() << " points in the path." << std::endl;
	tracerWidget->PlaceWidget();
	tracerWidget->SnapToImageOff();
}


void plotlineon2dcanvas()
{
	vtkSmartPointer<vtkImageCanvasSource2D> red = vtkSmartPointer<vtkImageCanvasSource2D>::New();
	red->SetScalarTypeToUnsignedChar();
	red->SetNumberOfScalarComponents(1);
	red->SetExtent(0, 100, 0, 100, 0, 0);
	red->SetDrawColor(0, 0, 0, 0);
	red->FillBox(0, 100, 0, 100);
	red->SetDrawColor(255, 0, 0, 0);
	red->FillBox(20, 40, 20, 40);
	red->Update();

	vtkSmartPointer<vtkImageCanvasSource2D> green = vtkSmartPointer<vtkImageCanvasSource2D>::New();
	green->SetScalarTypeToUnsignedChar();
	green->SetNumberOfScalarComponents(1);
	green->SetExtent(0, 100, 0, 100, 0, 0);
	green->SetDrawColor(0, 0, 0, 0);
	green->FillBox(0, 100, 0, 100);
	green->SetDrawColor(255, 0, 0, 0);
	green->FillBox(30, 50, 30, 50);
	green->Update();

	vtkSmartPointer<vtkImageCanvasSource2D> blue = vtkSmartPointer<vtkImageCanvasSource2D>::New();
	blue->SetExtent(0, 100, 0, 100, 0, 0);
	blue->SetDrawColor(0, 0, 0, 0);
	blue->FillBox(0, 100, 0, 100);
	blue->SetDrawColor(255, 0, 0, 0);
	blue->FillBox(40, 60, 40, 60);
	blue->Update();

	// 创建一个图像查看器
	vtkSmartPointer<vtkImageAppendComponents> appendFilter = vtkSmartPointer<vtkImageAppendComponents>::New();
	appendFilter->SetInputConnection(0, red->GetOutputPort());
	appendFilter->AddInputConnection(0, green->GetOutputPort());
	appendFilter->AddInputConnection(0, blue->GetOutputPort());
	appendFilter->Update();

	vtkSmartPointer<vtkImageActor> actor = vtkSmartPointer<vtkImageActor>::New();
	actor->GetMapper()->SetInputConnection(appendFilter->GetOutputPort());
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(actor);

	renderer->ResetCamera();
	vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);
	renderWindow->SetWindowName("vtkImageTracerWidget");

	vtkSmartPointer<vtkRenderWindowInteractor>interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	interactor->SetRenderWindow(renderWindow);
	vtkSmartPointer<vtkInteractorStyleImage> style = vtkSmartPointer<vtkInteractorStyleImage>::New();
	interactor->SetInteractorStyle(style);

	vtkSmartPointer<vtkImageTracerWidget> tracer = vtkSmartPointer<vtkImageTracerWidget>::New();
	tracer->GetLineProperty()->SetLineWidth(10);
	tracer->GetLineProperty()->SetColor(1, 0, 0);
	tracer->SetCaptureRadius(1.5);

	tracer->SetInputConnection(appendFilter->GetOutputPort());
	tracer->SetInteractor(interactor);
	tracer->SetViewProp(actor);
	tracer->ProjectToPlaneOff();
	tracer->Modified();

	vtkSmartPointer<vtkCallbackCommand> callback = vtkSmartPointer<vtkCallbackCommand>::New();
	callback->SetCallback(CallbackFunction);
	tracer->AddObserver(vtkCommand::EndInteractionEvent, callback);
	tracer->On();
	tracer->EnabledOn();
	renderWindow->Render();

	interactor->Initialize();
	interactor->Start();
}