#include <PointPickerInteractorStyle1.h>





void PointPickerInteractorStyle1:: OnLeftButtonDown()
{
    // 打印鼠标左键像素位置
    std::cout << "Picking pixel: " << this->Interactor->GetEventPosition()[0] << " " << this->Interactor->GetEventPosition()[1] << std::endl;
    // 注册拾取点函数
    this->Interactor->GetPicker()->
        Pick(
            this->Interactor->GetEventPosition()[0],
            this->Interactor->GetEventPosition()[1],
            0, //主要获取的是二维平面的像素点坐标  
            this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()//获取vtkrender对象
        );

    // 打印拾取点空间位置
    double picked[3];
    this->Interactor->GetPicker()->GetPickPosition(picked);
    std::cout << "Picked value: " << picked[0] << " " << picked[1] << " " << picked[2] << std::endl;
    m_points->InsertNextPoint(picked[0], picked[1], picked[2] + 10);
    polyLine->GetPointIds()->SetNumberOfIds(m_points->GetNumberOfPoints());
    for (int i = 0; i < m_points->GetNumberOfPoints(); i++)
    {
        polyLine->GetPointIds()->SetId(i, i);
    };
    cells->InsertNextCell(polyLine);
    outputVector->SetPoints(m_points);
    outputVector->SetLines(cells);
    vtkSmartPointer<vtkPolyDataMapper> freeLineMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    freeLineMapper->SetInputData(outputVector);
    vtkSmartPointer<vtkActor> freeLineActor = vtkSmartPointer<vtkActor>::New();
    freeLineActor->SetMapper(freeLineMapper);
    freeLineActor->GetProperty()->SetColor(1, 0, 0);
    freeLineActor->GetProperty()->SetLineWidth(2);
    this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(freeLineActor);
}

void PointPickerInteractorStyle1:: OnMouseMove()
{
    if (GetAsyncKeyState(VK_LBUTTON) < 0)
    {
        cout << "鼠标左键" << GetAsyncKeyState(VK_LBUTTON) << endl;

        this->Interactor->GetPicker()->
            Pick(
                this->Interactor->GetEventPosition()[0],
                this->Interactor->GetEventPosition()[1],
                0, //主要获取的是二维平面的像素点坐标  
                this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()//获取vtkrender对象
            );
        double picked[3];
        this->Interactor->GetPicker()->GetPickPosition(picked);
        m_points->InsertNextPoint(picked[0], picked[1], picked[2] + 10);
        int numOfPoints = m_points->GetNumberOfPoints();
        polyLine->GetPointIds()->InsertNextId(numOfPoints);
        polyLine->GetPointIds()->SetId(numOfPoints - 1, numOfPoints - 1);
        m_points->Modified();
        cells->Initialize(); // reset the cells to remove the old spiral
        cells->InsertNextCell(polyLine); // re-insert the updated spiral
        cells->Modified(); // required to update
        this->Interactor->GetRenderWindow()->Render();
    }
};

vtkStandardNewMacro(PointPickerInteractorStyle1)


void plotOnPicture()
{
    vtkSmartPointer<vtkPNGReader> jpegReader = vtkSmartPointer<vtkPNGReader>::New();
    jpegReader->SetFileName("C:\\gitlab\\vs\\ConsoleApplication1\\x64\\Debug\\123.png"); // 替换为你的图像文件路径

    vtkSmartPointer<vtkImageViewer2> imageViewer = vtkSmartPointer<vtkImageViewer2>::New();
    imageViewer->SetInputConnection(jpegReader->GetOutputPort());
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);
    renderWindow->SetWindowName("Planar");
    renderer->AddActor(imageViewer->GetImageActor());
    renderer->SetBackground(0, 0, 0);
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);
    vtkSmartPointer<PointPickerInteractorStyle1> style = vtkSmartPointer<PointPickerInteractorStyle1>::New();
    renderWindowInteractor->SetInteractorStyle(style);//放入interactor中后也能够在style中来反向获取，甚至可以在内部再设置一个picker
    renderWindow->Render();
    renderWindowInteractor->Initialize();
    renderWindowInteractor->Start();
}


void plotOn3d()
{
    // 1
    vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->SetRadius(10);
    sphereSource->SetThetaResolution(60);
    sphereSource->SetPhiResolution(60);

    // 2 
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(sphereSource->GetOutputPort());
    //3
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(1.0, 0.0, 0.0); // 设置颜色为红色


    //4
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->ResetCamera();
    renderer->AddActor(actor);

    // 5
    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer); 
   


    // 6
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    vtkSmartPointer<vtkCellPicker> picker = vtkSmartPointer<vtkCellPicker>::New();

    //renderWindowInteractor->SetPicker(picker);
    renderWindow->GetInteractor()->SetPicker(picker); // 这些东西设计的时候互相嵌套，正向和逆向都可以获取

    // 7
    vtkSmartPointer<PointPickerInteractorStyle1> style = vtkSmartPointer<PointPickerInteractorStyle1>::New();
    renderWindowInteractor->SetInteractorStyle(style);


    renderWindow->SetSize(800, 600);
    renderWindow->Render();
    renderWindowInteractor->Initialize();
    renderWindowInteractor->Start();
}