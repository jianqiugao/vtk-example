#include<MouseInteractorStyle.h>

void MouseInteractorStyle::OnLeftButtonDown() 
{
    vtkSmartPointer<vtkNamedColors> colors = vtkSmartPointer<vtkNamedColors>::New();


    int* pos = this->Interactor->GetEventPosition();

    //int* lastPos = this->Interactor->GetLastEventPosition();
    cout << "interactor捕获的位置:" << pos[0] << ":" << pos[1] << endl;

    auto picker = this->Interactor->GetPicker();

    // Pick(x, y, z, vtkRenderer)
    picker->Pick(pos[0], pos[1], 0, this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer());


    double worldPos[3];
    picker->GetPickPosition(worldPos);

    if (picker->IsA("vtkCellPicker"))
    {
        cout << ":" << "vtkCellPicker" << endl;
        auto cellPicker = vtkCellPicker::SafeDownCast(picker);
        std::cout << "picker到实体上的位置: [" << worldPos[0] << ", " << worldPos[1] << ", " << worldPos[2] << "]" << std::endl;
        std::cout << "CellId: " << cellPicker->GetCellId() << std::endl;
        std::cout << "PointId: " << cellPicker->GetPointId() << std::endl;

        if (cellPicker->GetCellId() != -1)
        {
            if (nullptr == data) {
                std::cout << "Source data not found! " << std::endl;
                return;
            }
            auto pointPos = data->GetPoint(cellPicker->GetPointId());

            auto displayPoint = vtkSmartPointer<vtkSphereSource>::New();
            displayPoint->SetCenter(pointPos);
            displayPoint->SetRadius(0.1);

            auto mapper = vtkSmartPointer <vtkPolyDataMapper>::New();
            mapper->SetInputConnection(displayPoint->GetOutputPort());

            this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->RemoveActor(displayActor);
            displayActor->SetMapper(mapper);
            this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(displayActor);
        }

    }
    else if (picker->IsA("vtkPointPicker"))
    {
        auto pointPicker = vtkPointPicker::SafeDownCast(picker);
        std::cout << "picker到实体上的位置: [" << worldPos[0] << ", " << worldPos[1] << ", " << worldPos[2] << "]" << std::endl;
        std::cout << "PointId: " << pointPicker->GetPointId() << std::endl;
        if (pointPicker->GetPointId() != -1) {
            if (nullptr == data) {
                std::cout << "Source data not found! " << std::endl;
                return;
            }
            auto pointPos = data->GetPoint(pointPicker->GetPointId()); //获取捕获到的点的具体坐标

            auto displayPoint = vtkSmartPointer<vtkSphereSource>::New(); //放一个球
            displayPoint->SetCenter(pointPos);//放置到这个中心上
            displayPoint->SetRadius(0.02);//设置球的直径

            auto mapper = vtkSmartPointer <vtkPolyDataMapper>::New(); //创建一个新的mapper
           
            mapper->SetInputConnection(displayPoint->GetOutputPort());

            this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->RemoveActor(displayActor);
            
            displayActor->SetMapper(mapper);
            this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(displayActor);
        }
    }
    else {
        std::cout << "WorldPos: [" << worldPos[0] << ", " << worldPos[1] << ", " << worldPos[2] << "]" << std::endl;
    }


    vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
}


vtkStandardNewMacro(MouseInteractorStyle)



void pickTriangelGridOnSphereByMstyle() 
{

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
    //renderer->SetBackground(100, 100, 100);
    //renderer->GetActiveCamera()->SetPosition(0, -1, 0);
    //renderer->GetActiveCamera()->SetFocalPoint(0, 0, 0);
    //renderer->GetActiveCamera()->SetViewUp(0, 0, 1);
    //renderer->GetActiveCamera()->Azimuth(30);
    //renderer->GetActiveCamera()->Elevation(30);
    renderer->ResetCamera();
    renderer->AddActor(actor);

    // 5
    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);


    // 6
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    vtkSmartPointer<vtkCellPicker> picker = vtkSmartPointer<vtkCellPicker>::New();
    renderWindowInteractor->SetPicker(picker);

    // 7
    vtkSmartPointer<MouseInteractorStyle> style = vtkSmartPointer<MouseInteractorStyle>::New();
    style->data = sphereSource->GetOutput();
    renderWindowInteractor->SetInteractorStyle(style);


    renderWindow->SetSize(800, 600);
    renderWindow->Render();
    renderWindowInteractor->Initialize();
    renderWindowInteractor->Start();
}