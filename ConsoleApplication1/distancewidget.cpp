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

    //ʵ����Widget
    vtkSmartPointer<vtkDistanceWidget> distanceWidget = vtkSmartPointer<vtkDistanceWidget>::New();
    //ָ����Ⱦ���ڽ�����,�������û��¼�
    distanceWidget->SetInteractor(rwi);
    //��Ҫʱʹ�ù۲���/����ģʽ�����ص�����(�˴�û��)
    //�������α��ʵ�塣��SetRepresentation()���¼���Widget��������
    //����ʹ��WidgetĬ�ϵļ��α��ʵ��
    distanceWidget->CreateDefaultRepresentation();
    static_cast<vtkDistanceRepresentation*> (distanceWidget->GetRepresentation())->SetLabelFormat("%-#6.3g px"); //�Ѹ���vtkWidgetRepresentationǿ��ת�����������vtkDistanceRepresentation
    //����Widget
    distanceWidget->On();

    rw->Render();
    //rwi->Initialize();
    rwi->Start();
}
