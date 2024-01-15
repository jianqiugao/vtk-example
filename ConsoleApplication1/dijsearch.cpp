#include<dijsearch.h>


void dijsearch()
{
    // 创建一个圆柱体源
    vtkSmartPointer<vtkSphereSource> cylinderSource = vtkSmartPointer<vtkSphereSource>::New();
    cylinderSource->SetRadius(5.);
    cylinderSource->SetThetaResolution(60);
    cylinderSource->SetPhiResolution(60);
    cylinderSource->Update(); //需要update一下才能获取到数据

    vtkSmartPointer<vtkMassProperties> cylindermass = vtkSmartPointer<vtkMassProperties>::New();
    cylindermass->SetInputConnection(cylinderSource->GetOutputPort());
    cout << "体积" << cylindermass->GetVolume() << endl;
    cout << "表面积" << cylindermass->GetSurfaceArea() << endl;

    // 计算球径上的距离
    vtkSmartPointer<vtkDijkstraGraphGeodesicPath> dijkstra = vtkSmartPointer<vtkDijkstraGraphGeodesicPath>::New();
    dijkstra->SetInputData(cylinderSource->GetOutput());
    dijkstra->SetStartVertex(0);
    dijkstra->SetEndVertex(30);
    dijkstra->Update();

    // 获取一下线段的长度
    vtkSmartPointer<vtkPolyData> dijpoly = vtkSmartPointer<vtkPolyData>::New();
    dijpoly = dijkstra->GetOutput();
    cout << "计算的路径长度" << dijpoly->GetLength() << endl;


    //// 来算球的法向量,如果只是绘制箭头这个法向量不是必要的
    //vtkSmartPointer<vtkPolyDataNormals> spherenormal = vtkSmartPointer<vtkPolyDataNormals>::New();
    //spherenormal->SetInputConnection(cylinderSource->GetOutputPort());
    ////spherenormal->ComputePointNormalsOn();
    ///*spherenormal->ComputeCellNormalsOn();*/
    //spherenormal->SetComputeCellNormals(0);
    //spherenormal->Update();

    // 通过mask来选取一些点构成polydata
    vtkSmartPointer<vtkMaskPoints> mask = vtkSmartPointer<vtkMaskPoints>::New();
    mask->SetInputData(cylinderSource->GetOutput());
    mask->SetMaximumNumberOfPoints(300);
    mask->RandomModeOn();
    mask->Update();

    vtkSmartPointer<vtkArrowSource> arrowSource = vtkSmartPointer<vtkArrowSource>::New();
    arrowSource->SetTipLength(1);
    arrowSource->SetTipRadius(0.5);

    vtkSmartPointer<vtkGlyph3D> glyph = vtkSmartPointer<vtkGlyph3D>::New();

    // glyph设置的一个是点源一个是形状
    glyph->SetInputData(mask->GetOutput());
    //glyph->SetSourceData(arrowSource->GetOutput());
    glyph->SetSourceConnection(arrowSource->GetOutputPort());
    glyph->SetVectorModeToUseNormal();
    glyph->SetScaleFactor(0.5); // 调整箭头大小
    glyph->Update();

     
    //定义一个mapper来计算法向量
    vtkSmartPointer<vtkPolyDataMapper> normalmapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    normalmapper->SetInputConnection(glyph->GetOutputPort());
    normalmapper->Update();

    vtkSmartPointer<vtkActor> normalactor = vtkSmartPointer<vtkActor>::New();
    normalactor->SetMapper(normalmapper);


    // 把找到的路径筛出来
    vtkSmartPointer<vtkPolyDataMapper> djimapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    djimapper->SetInputData(dijkstra->GetOutput());
    djimapper->Update();



    vtkSmartPointer<vtkDoubleArray> scalars = vtkSmartPointer<vtkDoubleArray>::New();
    scalars->SetName("ZCoordinates");
    vtkSmartPointer<vtkPolyData> poly = vtkSmartPointer<vtkPolyData>::New();

    poly = cylinderSource->GetOutput();

    int num = poly->GetPoints()->GetNumberOfPoints();
    cout << num << endl; //发现有200个点

    // 获取顶点坐标
    vtkSmartPointer<vtkPoints> points = poly->GetPoints();
    for (vtkIdType i = 0; i < points->GetNumberOfPoints(); ++i)
    {
        double point[3];
        points->GetPoint(i, point);
        /*std::cout << "Point " << i << ": (" << point[0] << ", " << point[1] << ", " << point[2] << ")" << std::endl;*/
        scalars->InsertNextValue(point[1]);
    }

    cylinderSource->GetOutput()->GetPointData()->SetScalars(scalars);
    cylinderSource->Update();

    // 创建Mapper和Actor
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    //mapper->SetInputConnection(cylinderSource->GetOutputPort());
    mapper->SetInputData(poly);
    mapper->SetScalarRange(cylinderSource->GetOutput()->GetScalarRange());


    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);


    vtkSmartPointer<vtkActor> actor_dij = vtkSmartPointer<vtkActor>::New();
    actor_dij->SetMapper(djimapper);
    actor_dij->GetProperty()->SetColor(0, 0, 1);

    // 创建渲染器和窗口
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);


    // 创建交互器
    vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(renderWindow);

    // 将Actor添加到渲染器
    renderer->AddActor(normalactor);
    renderer->AddActor(actor);
    renderer->AddActor(actor_dij);

    renderer->SetBackground(1, 1.0, 1); // 设置背景颜色

    // 渲染并启动交互
    renderWindow->Render();
    interactor->Start();
}