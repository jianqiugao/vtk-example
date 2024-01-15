#include <vtkImageTracerWidgetOn3D.h>
void vtkImageTracerWidgetOn3D()

{


vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
sphereSource->SetThetaResolution(30);
sphereSource->SetPhiResolution(30);
sphereSource->Update();


vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
mapper->SetInputConnection(sphereSource->GetOutputPort());
vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
actor->SetMapper(mapper);
actor->GetProperty();


vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
renderWindow->AddRenderer(renderer);
renderWindow->SetWindowName("ImageTracerWidgetNonPlanar");

renderer->AddActor(actor);
renderer->SetBackground(0, 0, 0);

vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
renderWindowInteractor->SetRenderWindow(renderWindow);

vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();

renderWindowInteractor->SetInteractorStyle(style);

// 应该是从这里开始做的
vtkSmartPointer<vtkImageTracerWidget> tracerWidget = vtkSmartPointer<vtkImageTracerWidget>::New();
tracerWidget->SetInteractor(renderWindowInteractor);
tracerWidget->SetViewProp(actor);

tracerWidget->EnabledOn();
renderWindow->Render();
renderWindowInteractor->Initialize();

renderWindowInteractor->Start();

}