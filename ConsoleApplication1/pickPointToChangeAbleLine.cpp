
#include<pickPointToChangeAbleLine.h>


void pickPointToChangeAbleLine() {
	vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New(); // 创建一个球体
	sphereSource->SetRadius(5);
	sphereSource->SetPhiResolution(30);
	sphereSource->SetThetaResolution(30);
	sphereSource->Update();

	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();//创建mapper
	mapper->SetInputConnection(sphereSource->GetOutputPort());

	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);
	actor->GetProperty()->SetColor(1, 0, 0);

	// Create the RenderWindow, Renderer
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(actor);
	renderer->SetBackground(0, 1, 0);

	vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);
	renderWindow->SetWindowName("PolygonalSurfacePointPlacer");

	vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	interactor->SetRenderWindow(renderWindow);
	//到这里流程差不多就走通了，后面是额外添加的一个小插件

	vtkSmartPointer<vtkContourWidget> contourWidget = vtkSmartPointer<vtkContourWidget>::New();
	contourWidget->SetInteractor(interactor);

	vtkOrientedGlyphContourRepresentation* rep = dynamic_cast<vtkOrientedGlyphContourRepresentation*>(contourWidget->GetRepresentation());

	vtkSmartPointer<vtkPolygonalSurfacePointPlacer> pointPlacer = vtkSmartPointer<vtkPolygonalSurfacePointPlacer>::New();
	pointPlacer->AddProp(actor);
	pointPlacer->GetPolys()->AddItem(sphereSource->GetOutput());

	rep->GetLinesProperty()->SetColor(0, 1, 1);
	rep->GetLinesProperty()->SetLineWidth(3.0);
	rep->SetPointPlacer(pointPlacer);

	contourWidget->EnabledOn();
	renderer->ResetCamera();
	// 这里结束添加小插件，但是直接注释小插件应该没什么影响

	renderWindow->Render();

	interactor->Start(); //感觉里面是一个while True
}