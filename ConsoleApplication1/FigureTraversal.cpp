#include <FigureTraversal.h>


static long pressCounts = 0;


void FigureTraversal()
{
    vtkSmartPointer<vtkPNGReader> jpegReader = vtkSmartPointer<vtkPNGReader>::New();
    jpegReader->SetFileName("C:\\gitlab\\vs\\ConsoleApplication1\\x64\\Debug\\123.jpg"); // 替换为你的图像文件路径
    cout << "引用计数" << jpegReader->GetReferenceCount() << endl;
    jpegReader->Update();
    int dims[3];
    //jpegReader->GetOutputData()->GetDimensions();
    jpegReader->GetOutput()->GetDimensions(dims);
    int numOfComponet;
    numOfComponet = jpegReader->GetOutput()->GetNumberOfScalarComponents();
    // 这个计算通道数png是4个通道
    cout << "numOfComponet" << numOfComponet << endl;

    unsigned char* pixel = (unsigned char*)jpegReader->GetOutput()->GetScalarPointer(500, 500, 0);

    cout << "pixel" << "第一个通道:" << float(pixel[0]) << "第二个通道:" << float(pixel[1]) << "第三个通道:" << float(pixel[2]) << "第四个通道;" << float(pixel[3]) << endl;
    cout << dims[0] << ":" << dims[1] << ":" << dims[2] << endl;
    
    // 创建一个图像查看器 图片看着一个四维数据
    int subregion[6] = { 2,5,2,6,0,0 };
    vtkImageIterator<unsigned char > it(jpegReader->GetOutput(), subregion);
    int j = 0;
    while (!it.IsAtEnd())
    {

        unsigned char* insi = it.BeginSpan(); //获取一个条幅的
        unsigned char* issiend = it.EndSpan();
        while (insi != issiend)
        {
            double x = *insi++;
            double y = *insi++;
            double z = *insi++;
            double m = *insi++;
            std::cout << "(" << x << "," << y << "," << z << "," << m <<")";
        }
        std::cout << std::endl;
        it.NextSpan();
        //j++;
    };

    vtkSmartPointer<vtkImageViewer2> imageViewer = vtkSmartPointer<vtkImageViewer2>::New();
    imageViewer->SetInputConnection(jpegReader->GetOutputPort()); //jpegReader->GetOutputPort()返回算法输出端口对象，用于连接

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    imageViewer->SetupInteractor(renderWindowInteractor);

    // 渲染图像
    imageViewer->Render();
    cout << "引用计数" << imageViewer->GetReferenceCount() << endl;
    // 启动交互
    renderWindowInteractor->SetRenderWindow(imageViewer->GetRenderWindow());
    /*  renderWindowInteractor->AddObserver(vtkCommand::LeftButtonPressEvent,commadn);*/
    renderWindowInteractor->Initialize();
    renderWindowInteractor->Start(); // 这段代码是实现窗口暂停的基础，不然窗口会一闪而过
}