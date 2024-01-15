# include <angleWidget.h>

void angelwidget()
{
    // ����һ��VTK��Ⱦ������Ⱦ����
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

    // ����һ��VTK��Ⱦ���ڽ�����
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    // ����һ��������Ϊʾ������
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
    // ������ɫΪ��ɫ

    // ��������ӵ���Ⱦ����
    renderer->AddActor(actor);

    // ����һ��vtkAngleWidget������������
    vtkSmartPointer<vtkAngleWidget> angleWidget = vtkSmartPointer<vtkAngleWidget>::New();
    vtkSmartPointer<vtkAngleRepresentation2D> angleRep = vtkSmartPointer<vtkAngleRepresentation2D>::New();
    angleWidget->SetRepresentation(angleRep);

    // ��vtkAngleWidget��ӵ���Ⱦ����
    angleWidget->SetInteractor(renderWindowInteractor);
    angleWidget->On();

    // ������Ⱦ���ڵĴ�С����������ѭ��
    renderWindow->SetSize(800, 600);
    renderWindow->Render();
    renderWindowInteractor->Initialize();
    renderWindowInteractor->Start();

}