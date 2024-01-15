#include <distancewidget.h>

void distancewidgetexample()
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

    //实例化Widget
    vtkSmartPointer<vtkDistanceWidget> distanceWidget = vtkSmartPointer<vtkDistanceWidget>::New();
    //指定渲染窗口交互器,来监听用户事件
    distanceWidget->SetInteractor(rwi);
    //必要时使用观察者/命令模式创建回调函数(此处没用)
    //创建几何表达实体。用SetRepresentation()把事件与Widget关联起来
    //或者使用Widget默认的几何表达实体
    distanceWidget->CreateDefaultRepresentation();
    static_cast<vtkDistanceRepresentation*> (distanceWidget->GetRepresentation())->SetLabelFormat("%-#6.3g px"); //把父类vtkWidgetRepresentation强制转换成子类对象vtkDistanceRepresentation
    //激活Widget
    distanceWidget->On();

    rw->Render();
    //rwi->Initialize();
    rwi->Start();
}
