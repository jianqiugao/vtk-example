# include <angleWidget.h>

void angelwidget()
{
    // 创建一个VTK渲染器和渲染窗口
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->SetBackground(100, 100, 100);
   /* renderer->GetActiveCamera()->SetPosition(0, -1, 0);
    renderer->GetActiveCamera()->SetFocalPoint(0, 0, 0);
    renderer->GetActiveCamera()->SetViewUp(0, 0, 1);
    renderer->GetActiveCamera()->Azimuth(30);
    renderer->GetActiveCamera()->Elevation(30);*/
    renderer->ResetCamera();

    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);

    // 创建一个VTK渲染窗口交互器
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    // 创建一个球体作为示例对象
    vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->SetRadius(1.0);
    sphereSource->SetPhiResolution(60);
    sphereSource->SetThetaResolution(60);
    sphereSource->Update();

    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(sphereSource->GetOutputPort());

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(1.0, 0.0, 0.0);
    // 设置颜色为红色

    // 将球体添加到渲染器中
    renderer->AddActor(actor);

    // 创建一个vtkAngleWidget并设置其属性
    vtkSmartPointer<vtkAngleWidget> angleWidget = vtkSmartPointer<vtkAngleWidget>::New();
    vtkSmartPointer<vtkAngleRepresentation2D> angleRep = vtkSmartPointer<vtkAngleRepresentation2D>::New();
    angleWidget->SetRepresentation(angleRep);

    // 将vtkAngleWidget添加到渲染器中
    angleWidget->SetInteractor(renderWindowInteractor);
    angleWidget->On();

    // 设置渲染窗口的大小并启动交互循环
    renderWindow->SetSize(800, 600);
    renderWindow->Render();
    renderWindowInteractor->Initialize();
    renderWindowInteractor->Start();

}