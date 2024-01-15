#include<addObserverInWindowInteractor.h>

long pressCounts = 0;

void myCallBackFunc(vtkObject*, unsigned long eid, void* clientdata, void* calldata)
{
    cout << "���Ѿ������" << ++pressCounts << "��" << endl;
}


void addObserverInWindowInteractor()
{
    vtkSmartPointer<vtkPNGReader> jpegReader = vtkSmartPointer<vtkPNGReader>::New();
    jpegReader->SetFileName("C:\\gitlab\\vs\\ConsoleApplication1\\x64\\Debug\\123.jpg"); // �滻Ϊ���ͼ���ļ�·��
    cout << "���ü���" << jpegReader->GetReferenceCount() << endl;

    //    // ����һ��ͼ��鿴��
    vtkSmartPointer<vtkImageViewer2> imageViewer = vtkSmartPointer<vtkImageViewer2>::New();
    imageViewer->SetInputConnection(jpegReader->GetOutputPort()); //jpegReader->GetOutputPort()�����㷨����˿ڶ�����������


    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    imageViewer->SetupInteractor(renderWindowInteractor);
    // ��Ⱦͼ��
    imageViewer->Render();
    cout << "���ü���" << imageViewer->GetReferenceCount() << endl;

    vtkSmartPointer<vtkCallbackCommand> commadn = vtkSmartPointer< vtkCallbackCommand>::New();
    commadn->SetCallback(myCallBackFunc);

    // ��������
    renderWindowInteractor->SetRenderWindow(imageViewer->GetRenderWindow());
    renderWindowInteractor->AddObserver(vtkCommand::LeftButtonPressEvent, commadn);
    renderWindowInteractor->Initialize();
    renderWindowInteractor->Start(); // ��δ�����ʵ�ִ�����ͣ�Ļ�������Ȼ���ڻ�һ������

}