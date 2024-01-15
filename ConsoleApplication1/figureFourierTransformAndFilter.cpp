#include<figureFourierTransformAndFilter.h>


void figureFourierTransformAndFilter()
{
    // 创建一个 JPG 图像读取器
    vtkSmartPointer<vtkPNGReader> jpegReader = vtkSmartPointer<vtkPNGReader>::New();
    jpegReader->SetFileName("C:\\gitlab\\vs\\ConsoleApplication1\\x64\\Debug\\123.png"); // 替换为你的图像文件路径
    jpegReader->Update();

    vtkSmartPointer<vtkImageFFT> filter = vtkSmartPointer<vtkImageFFT>::New();
    filter->SetInputConnection(jpegReader->GetOutputPort());
    filter->SetDimensionality(2); // 不懂这个是在干什么
    filter->Update();

    //做一个低通滤波器
    /*vtkSmartPointer<vtkImageIdealLowPass> lowpass = vtkSmartPointer<vtkImageIdealLowPass>::New();
    lowpass->SetInputConnection(filter->GetOutputPort());
    lowpass->SetXCutOff(0.2);
    lowpass->SetYCutOff(0.2);
    lowpass->Update();*/

    //做一个高通滤波器
    vtkSmartPointer<vtkImageIdealHighPass> lowpass = vtkSmartPointer<vtkImageIdealHighPass>::New();
    lowpass->SetInputConnection(filter->GetOutputPort());
    lowpass->SetXCutOff(0.1);
    lowpass->SetYCutOff(0.1);
    lowpass->Update();

    vtkSmartPointer<vtkImageExtractComponents> filter_ext = vtkSmartPointer<vtkImageExtractComponents>::New();

    filter_ext->SetInputConnection(filter->GetOutputPort());
    filter_ext->SetComponents(0);//指定提取图像的实部进行显示
    filter_ext->Update();

    double range[2];
    filter_ext->GetOutput()->GetScalarRange(range);
    cout << range[0] << ":" << range[1] << endl;

    vtkSmartPointer<vtkImageShiftScale> shiftscale = vtkSmartPointer<vtkImageShiftScale>::New();
    shiftscale->SetOutputScalarTypeToUnsignedChar();
    shiftscale->SetScale(255.0 / (range[1] - range[0]));
    shiftscale->SetShift(-range[0]);
    shiftscale->SetInputConnection(filter_ext->GetOutputPort());
    shiftscale->Update();

    vtkSmartPointer<vtkImageRFFT> rfft = vtkSmartPointer<vtkImageRFFT>::New();
    rfft->SetInputConnection(lowpass->GetOutputPort());
    rfft->SetDimensionality(2); // 不懂这个是在干什么
    rfft->Update();


    vtkSmartPointer<vtkImageExtractComponents> rfilter_ext = vtkSmartPointer<vtkImageExtractComponents>::New();
    rfilter_ext->SetInputConnection(rfft->GetOutputPort());
    rfilter_ext->SetComponents(0);
    rfilter_ext->Update();

    vtkSmartPointer<vtkImageCast> castfilter_ext = vtkSmartPointer<vtkImageCast>::New();
    castfilter_ext->SetInputConnection(rfilter_ext->GetOutputPort());
    castfilter_ext->SetOutputScalarTypeToUnsignedChar();
    castfilter_ext->Update();




    // 创建一个图像查看器
    vtkSmartPointer<vtkImageViewer2> imageViewer = vtkSmartPointer<vtkImageViewer2>::New();
    imageViewer->SetInputConnection(castfilter_ext->GetOutputPort()); //jpegReader->GetOutputPort()返回算法输出端口对象，用于连接
    // 创建一个渲染窗口交互器
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    imageViewer->SetupInteractor(renderWindowInteractor);
    // 渲染图像
    imageViewer->Render();
    // 启动交互
    renderWindowInteractor->Start(); // 这段代码是实现窗口暂停的基础，不然窗口会一闪而过

};
