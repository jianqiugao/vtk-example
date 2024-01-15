#include<addObserverInWindowInteractor.h>

long pressCounts = 0;

void myCallBackFunc(vtkObject*, unsigned long eid, void* clientdata, void* calldata)
{
    cout << "你已经点击了" << ++pressCounts << "次" << endl;
}


void addObserverInWindowInteractor()
{
    vtkSmartPointer<vtkPNGReader> jpegReader = vtkSmartPointer<vtkPNGReader>::New();
    jpegReader->SetFileName("C:\\gitlab\\vs\\ConsoleApplication1\\x64\\Debug\\123.jpg"); // 替换为你的图像文件路径
    cout << "引用计数" << jpegReader->GetReferenceCount() << endl;

    //    // 创建一个图像查看器
    vtkSmartPointer<vtkImageViewer2> imageViewer = vtkSmartPointer<vtkImageViewer2>::New();
    imageViewer->SetInputConnection(jpegReader->GetOutputPort()); //jpegReader->GetOutputPort()返回算法输出端口对象，用于连接


    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    imageViewer->SetupInteractor(renderWindowInteractor);
    // 渲染图像
    imageViewer->Render();
    cout << "引用计数" << imageViewer->GetReferenceCount() << endl;

    vtkSmartPointer<vtkCallbackCommand> commadn = vtkSmartPointer< vtkCallbackCommand>::New();
    commadn->SetCallback(myCallBackFunc);

    // 启动交互
    renderWindowInteractor->SetRenderWindow(imageViewer->GetRenderWindow());
    renderWindowInteractor->AddObserver(vtkCommand::LeftButtonPressEvent, commadn);
    renderWindowInteractor->Initialize();
    renderWindowInteractor->Start(); // 这段代码是实现窗口暂停的基础，不然窗口会一闪而过

}