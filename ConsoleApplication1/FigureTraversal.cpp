#include <FigureTraversal.h>


static long pressCounts = 0;


void FigureTraversal()
{
    vtkSmartPointer<vtkPNGReader> jpegReader = vtkSmartPointer<vtkPNGReader>::New();
    jpegReader->SetFileName("C:\\gitlab\\vs\\ConsoleApplication1\\x64\\Debug\\123.jpg"); // �滻Ϊ���ͼ���ļ�·��
    cout << "���ü���" << jpegReader->GetReferenceCount() << endl;
    jpegReader->Update();
    int dims[3];
    //jpegReader->GetOutputData()->GetDimensions();
    jpegReader->GetOutput()->GetDimensions(dims);
    int numOfComponet;
    numOfComponet = jpegReader->GetOutput()->GetNumberOfScalarComponents();
    // �������ͨ����png��4��ͨ��
    cout << "numOfComponet" << numOfComponet << endl;

    unsigned char* pixel = (unsigned char*)jpegReader->GetOutput()->GetScalarPointer(500, 500, 0);

    cout << "pixel" << "��һ��ͨ��:" << float(pixel[0]) << "�ڶ���ͨ��:" << float(pixel[1]) << "������ͨ��:" << float(pixel[2]) << "���ĸ�ͨ��;" << float(pixel[3]) << endl;
    cout << dims[0] << ":" << dims[1] << ":" << dims[2] << endl;
    
    // ����һ��ͼ��鿴�� ͼƬ����һ����ά����
    int subregion[6] = { 2,5,2,6,0,0 };
    vtkImageIterator<unsigned char > it(jpegReader->GetOutput(), subregion);
    int j = 0;
    while (!it.IsAtEnd())
    {

        unsigned char* insi = it.BeginSpan(); //��ȡһ��������
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
    imageViewer->SetInputConnection(jpegReader->GetOutputPort()); //jpegReader->GetOutputPort()�����㷨����˿ڶ�����������

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    imageViewer->SetupInteractor(renderWindowInteractor);

    // ��Ⱦͼ��
    imageViewer->Render();
    cout << "���ü���" << imageViewer->GetReferenceCount() << endl;
    // ��������
    renderWindowInteractor->SetRenderWindow(imageViewer->GetRenderWindow());
    /*  renderWindowInteractor->AddObserver(vtkCommand::LeftButtonPressEvent,commadn);*/
    renderWindowInteractor->Initialize();
    renderWindowInteractor->Start(); // ��δ�����ʵ�ִ�����ͣ�Ļ�������Ȼ���ڻ�һ������
}