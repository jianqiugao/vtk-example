#include<BiDimensionalWidget.h>



void vtkBiDimensionalCallback::Execute(vtkObject* caller, unsigned long, void*)
{

    vtkBiDimensionalWidget* biDimensionalWidget = reinterpret_cast<vtkBiDimensionalWidget*> (caller);
    vtkBiDimensionalRepresentation2D* representation = static_cast<vtkBiDimensionalRepresentation2D*> (biDimensionalWidget->GetRepresentation());
    cout << "hello,getpoint" << endl;


    double p1[3];
    representation->GetPoint1DisplayPosition(p1);  // ͨ����ʾ���õ�һ����
    //��ʾ����һ�������Ļ����(px)
    std::cout << "P1: " << p1[0] << " " << p1[1] << " " << p1[2] << std::endl;
}


void BiDimensionalWidgetexample() 
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

    vtkSmartPointer<vtkBiDimensionalWidget> bidimensionalWidget = vtkSmartPointer<vtkBiDimensionalWidget>::New();
    bidimensionalWidget->SetInteractor(rwi);
    // ����Ĭ�ϵ�ͼ��
    //bidimensionalWidget->CreateDefaultRepresentation();
    bidimensionalWidget->On();

    // ��� �۲���-����ģʽ �������෽��
    vtkSmartPointer<vtkBiDimensionalCallback> bidiCallback = vtkSmartPointer<vtkBiDimensionalCallback>::New();
    
    bidimensionalWidget->AddObserver(vtkCommand::InteractionEvent, bidiCallback); //��д��excute����


    //vtkSmartPointer<vtkTextWidget> tracewidge = vtkSmartPointer<vtkTextWidget>::New();
    ////tracewidge->SetInputData(reader->GetOutput());
    ///*tracewidge->SetViewProp(imgActor);*/
    //tracewidge->SetInteractor(rwi);
    //tracewidge->On();


    // ��δ�����ôʹ���������кܴ������
   /* vtkWidgetEventTranslator* eventranslator = bidimensionalWidget->GetEventTranslator();
    eventranslator->SetTranslation(vtkCommand::RightButtonPressEvent, vtkWidgetEvent::Select);
    eventranslator->SetTranslation(vtkCommand::RightButtonPressEvent, vtkWidgetEvent::EndSelect);
    cout << "hello" << endl;*/

    rw->Render();
    rwi->Initialize();
    rwi->Start();

};