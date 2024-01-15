#include<figureFourierTransformAndFilter.h>


void figureFourierTransformAndFilter()
{
    // ����һ�� JPG ͼ���ȡ��
    vtkSmartPointer<vtkPNGReader> jpegReader = vtkSmartPointer<vtkPNGReader>::New();
    jpegReader->SetFileName("C:\\gitlab\\vs\\ConsoleApplication1\\x64\\Debug\\123.png"); // �滻Ϊ���ͼ���ļ�·��
    jpegReader->Update();

    vtkSmartPointer<vtkImageFFT> filter = vtkSmartPointer<vtkImageFFT>::New();
    filter->SetInputConnection(jpegReader->GetOutputPort());
    filter->SetDimensionality(2); // ����������ڸ�ʲô
    filter->Update();

    //��һ����ͨ�˲���
    /*vtkSmartPointer<vtkImageIdealLowPass> lowpass = vtkSmartPointer<vtkImageIdealLowPass>::New();
    lowpass->SetInputConnection(filter->GetOutputPort());
    lowpass->SetXCutOff(0.2);
    lowpass->SetYCutOff(0.2);
    lowpass->Update();*/

    //��һ����ͨ�˲���
    vtkSmartPointer<vtkImageIdealHighPass> lowpass = vtkSmartPointer<vtkImageIdealHighPass>::New();
    lowpass->SetInputConnection(filter->GetOutputPort());
    lowpass->SetXCutOff(0.1);
    lowpass->SetYCutOff(0.1);
    lowpass->Update();

    vtkSmartPointer<vtkImageExtractComponents> filter_ext = vtkSmartPointer<vtkImageExtractComponents>::New();

    filter_ext->SetInputConnection(filter->GetOutputPort());
    filter_ext->SetComponents(0);//ָ����ȡͼ���ʵ��������ʾ
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
    rfft->SetDimensionality(2); // ����������ڸ�ʲô
    rfft->Update();


    vtkSmartPointer<vtkImageExtractComponents> rfilter_ext = vtkSmartPointer<vtkImageExtractComponents>::New();
    rfilter_ext->SetInputConnection(rfft->GetOutputPort());
    rfilter_ext->SetComponents(0);
    rfilter_ext->Update();

    vtkSmartPointer<vtkImageCast> castfilter_ext = vtkSmartPointer<vtkImageCast>::New();
    castfilter_ext->SetInputConnection(rfilter_ext->GetOutputPort());
    castfilter_ext->SetOutputScalarTypeToUnsignedChar();
    castfilter_ext->Update();




    // ����һ��ͼ��鿴��
    vtkSmartPointer<vtkImageViewer2> imageViewer = vtkSmartPointer<vtkImageViewer2>::New();
    imageViewer->SetInputConnection(castfilter_ext->GetOutputPort()); //jpegReader->GetOutputPort()�����㷨����˿ڶ�����������
    // ����һ����Ⱦ���ڽ�����
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    imageViewer->SetupInteractor(renderWindowInteractor);
    // ��Ⱦͼ��
    imageViewer->Render();
    // ��������
    renderWindowInteractor->Start(); // ��δ�����ʵ�ִ�����ͣ�Ļ�������Ȼ���ڻ�һ������

};
