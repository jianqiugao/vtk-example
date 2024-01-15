#include<anglewidgetsimple.h>


void anglewidgetexample()

{
vtkSmartPointer<vtkPNGReader> reader = vtkSmartPointer<vtkPNGReader>::New();
reader->SetFileName("C:\\gitlab\\vs\\ConsoleApplication1\\x64\\Debug\\123.jpg");
reader->Update();

vtkSmartPointer<vtkImageActor> imgActor = vtkSmartPointer<vtkImageActor>::New();
imgActor->SetInputData(reader->GetOutput());

vtkSmartPointer<vtkRenderer> render = vtkSmartPointer<vtkRenderer>::New();
render->AddActor(imgActor);
render->SetBackground(0, 0, 0);
render->ResetCamera();

vtkSmartPointer<vtkRenderWindow> rw = vtkSmartPointer<vtkRenderWindow>::New();
rw->AddRenderer(render);
rw->SetWindowName("MeasurementDistanceApp");
rw->SetSize(320, 320);
rw->Render();

vtkSmartPointer<vtkRenderWindowInteractor> rwi = vtkSmartPointer<vtkRenderWindowInteractor>::New();
rwi->SetRenderWindow(rw);

vtkSmartPointer<vtkInteractorStyleImage> style = vtkSmartPointer<vtkInteractorStyleImage>::New();
rwi->SetInteractorStyle(style);
/****************************************************************/

vtkSmartPointer<vtkAngleWidget> angleWiget = vtkSmartPointer<vtkAngleWidget>::New();
angleWiget->SetInteractor(rwi);
//创建个性化的实体图标
vtkSmartPointer<vtkAngleRepresentation2D> angleRep = vtkSmartPointer<vtkAngleRepresentation2D>::New();
angleRep->GetRay1()->GetProperty()->SetColor(1, 0, 0);
angleRep->GetRay1()->GetProperty()->SetLineWidth(3);
angleRep->GetRay2()->GetProperty()->SetColor(0, 1, 0);
angleRep->GetRay2()->GetProperty()->SetLineWidth(3);
angleRep->GetArc()->GetProperty()->SetColor(0, 1, 0);
angleRep->GetArc()->GetProperty()->SetLineWidth(3);
angleWiget->SetRepresentation(angleRep);
angleWiget->On();

rw->Render();
rwi->Initialize();
rwi->Start();

}