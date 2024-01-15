#include<stscalar.h> //本来是没问题的，但是如果定义在头文件就会出现问题,我在想申明是可以多次申明的，但是main中引入头文件，这里再引入在预编译的时候就会出现重定义，因为这个是会单独编译成文件然后链接到main上，这样main和这个的obj里面就会都有这样一个函数



void setscalar()
{
    // 创建一个圆柱体源
    vtkSmartPointer<vtkCylinderSource> cylinderSource = vtkSmartPointer<vtkCylinderSource>::New();
    cylinderSource->SetHeight(2.0); // 设置圆柱体高度
    cylinderSource->SetRadius(1.0); // 设置圆柱体半径
    cylinderSource->SetResolution(50); // 设置圆柱体分辨率
    cylinderSource->Update(); //需要update一下才能获取到数据
    std::ofstream file("points.txt");


    vtkSmartPointer<vtkDoubleArray> scalars = vtkSmartPointer<vtkDoubleArray>::New();
    scalars->SetName(" s");
    vtkSmartPointer<vtkPolyData> poly = vtkSmartPointer<vtkPolyData>::New();

    poly = cylinderSource->GetOutput();

    int num = poly->GetPoints()->GetNumberOfPoints();
    //cout << num << endl; //发现有200个点

    // 获取顶点坐标
    vtkSmartPointer<vtkPoints> points = poly->GetPoints();
    for (vtkIdType i = 0; i < points->GetNumberOfPoints(); ++i)
    {
        double point[3];
        points->GetPoint(i, point);
        /*std::cout << "Point " << i << ": (" << point[0] << ", " << point[1] << ", " << point[2] << ")" << std::endl;*/
        // vtk中
        scalars->InsertNextValue(point[1]);
        file << point[0] << " " << point[1] << " " << point[2] << std::endl;
        
    }
    scalars->PrintSelf(cout, vtkIndent(0));
    cout <<"value:" << scalars->GetValue(1) << endl;
    cylinderSource->GetOutput()->GetPointData()->SetScalars(scalars);
    cylinderSource->Update();

    // 创建Mapper和Actor
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    //mapper->SetInputConnection(cylinderSource->GetOutputPort());
    mapper->SetInputData(poly);


    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    // 创建渲染器和窗口
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);


    // 创建交互器
    vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(renderWindow);

  

    //vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    //interactor->SetInteractorStyle(style);


     // 进行坐标轴的设置
    vtkSmartPointer<vtkAxesActor> axes_actor = vtkSmartPointer<vtkAxesActor>::New();
    axes_actor->SetPosition(0, 0, 0);
    axes_actor->SetTotalLength(2, 2, 2);
    axes_actor->SetShaftType(0);
    axes_actor->SetCylinderRadius(0.02);



    //// 控制坐标系，使之随视角共同变化 
    vtkSmartPointer<vtkOrientationMarkerWidget> widget = vtkSmartPointer<vtkOrientationMarkerWidget>::New();
    widget->SetOrientationMarker(actor);
    widget->SetInteractor(interactor);
    widget->SetEnabled(1);
    widget->InteractiveOn();

      // 将Actor添加到渲染器
    renderer->AddActor(actor);
    renderer->AddActor(axes_actor);
    //renderer->AddActor(axes);
    renderer->SetBackground(1.0, 1.0, 1.0); // 设置背景颜色

    // 渲染并启动交互
    renderWindow->Render();
    interactor->Start();

}


void scalaronfigure()
{

    /*std::array<std::array<double, 3>, 8> */
    std::vector<std::vector<double>>
        pts = {
        {{{0., 0., 0.}}
        ,{{1., 0., 0.}}
        ,{{1., 1, 0.}}
        ,{{0, 1., 0.}}
        ,{{0., 0, 1.}}
        ,{{1., 0., 1.}}
        ,{{1., 1., 1.}}
        ,{{0., 1., 1.}}} };

    // 第一层大括号表示这是一个std::array对象，
    //第二层大括号表示这个std::array对象中包含8个元素，每个元素都是一个包含三个double类型的值的一维数组，
    //第三层大括号表示这个一维数组中包含三个double类型的值，
    //第四层大括号表示这个值的初始化。

    std::array<std::array<vtkIdType, 4>, 6> ording =
    { {{
         {0, 1, 2, 3}}
        ,{{4, 5, 6, 7}}
        ,{{0, 1, 5, 4}}
        ,{{1, 2, 6, 5}}
        ,{{2, 3, 7, 6}}
        ,{{3, 0, 4, 7}}} };
    vtkSmartPointer<vtkPolyData> cube = vtkSmartPointer<vtkPolyData>::New();
    // 创建正方体的顶点坐标
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
    vtkSmartPointer<vtkCellArray> polys = vtkSmartPointer<vtkCellArray>::New();
    vtkSmartPointer<vtkFloatArray> scalar = vtkSmartPointer<vtkFloatArray>::New();


    for (size_t i = 0; i < pts.size(); i++)
    {
        points->InsertPoint(i, pts[i].data()); //插入的是一个array的指针
        //points->inse
        //cout<<"data:" << pts[i].data()[0] << endl;
        scalar->InsertTuple1(i, i); //对每一个顶点进行赋值
    };

    for (auto&& i : ording)
    {
        polys->InsertNextCell(vtkIdType(i.size()), i.data());
    };
    cube->SetPoints(points);
    cube->SetPolys(polys);// 这里的poly其实就是面，是一个vtkCellArray
    cube->GetPointData()->SetScalars(scalar);// vtkDataArray 存储的是具体的数据

    // 创建映射器和演员
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputData(cube);
    mapper->SetScalarRange(cube->GetScalarRange()); // 设置标量范围

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    // 创建渲染器和渲染窗口
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(actor);

    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);

    // 创建渲染窗口交互器
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    // 显示结果
    renderWindow->Render();
    renderWindowInteractor->Start();
}


void create2drectange()
{
    // 创建正方体的顶点坐标
    std::vector<float> first = { 0., 0., 0. };
    std::vector<float> second = { 0., 1., 0. };
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
   
    /* points->InsertPoint(0, first.data());
    points->InsertPoint(1, second.data());
    points->InsertPoint(2, 1., 0., 0.);
    points->InsertPoint(3, 1., 1., 0.);
    points->InsertPoint(4, 2., 0., 0.);
    points->InsertPoint(5, 2., 1., 0.);
    points->InsertPoint(6, 3., 0., 0.);
    points->InsertPoint(7, 3., 1., 0.);*/


    points->InsertNextPoint(first.data());
    points->InsertNextPoint( second.data());
    points->InsertNextPoint(1., 0., 0.);
    points->InsertNextPoint( 1., 1., 0.);
    points->InsertNextPoint( 2., 0., 0.);
    points->InsertNextPoint(2., 1., 0.);
    points->InsertNextPoint(3., 0., 0.);
    points->InsertNextPoint( 3., 1., 0.);


    vtkSmartPointer<vtkCellArray> strips = vtkSmartPointer<vtkCellArray>::New();
    //strips->InsertNextCell(8);
    //strips->InsertCellPoint(0);
    //strips->InsertCellPoint(1);
    //strips->InsertCellPoint(2);
    //strips->InsertCellPoint(3);
    //strips->InsertCellPoint(4);
    //strips->InsertCellPoint(5);
    //strips->InsertCellPoint(6);
    //strips->InsertCellPoint(7);

    std::vector<std::vector<vtkIdType>> spt = { {{{0},{1},{2},{3},{4},{5},{6},{7}}} };
    for (auto&& i : spt)
    {
        strips->InsertNextCell(vtkIdType(i.size()), i.data()); 
        // 也可以先设定点数，然后再逐渐把点加进去
        // 或者我这里每个点都当一个单元，至于最后出来的是面还是线取决于vtkPolyData中的设置
    };

    vtkSmartPointer<vtkPolyData> poly = vtkSmartPointer<vtkPolyData>::New();
    poly->SetPoints(points);
    //poly->SetStrips(strips);
    poly->SetLines(strips);

    //// 设置顶点颜色
    vtkSmartPointer<vtkFloatArray> colors = vtkSmartPointer<vtkFloatArray>::New();
    colors->InsertNextValue(0); // 红色
    colors->InsertNextValue(1); // 绿色
    colors->InsertNextValue(2); // 蓝色
    colors->InsertNextValue(3); // 黄色
    colors->InsertNextValue(4); // 紫色
    colors->InsertNextValue(5); // 青色
    colors->InsertNextValue(6); // 橙色
    colors->InsertNextValue(7); // 粉色

    // 创建拓扑结构
    //vtkSmartPointer<vtkCellArray> cellArray = vtkSmartPointer<vtkCellArray>::New();
    //cellArray->InsertNextCell(8);
    //for (vtkIdType i = 0; i < 8; ++i)
    //{
    //    cellArray->InsertCellPoint(i);
    //}

    //// 创建PolyData
    /*vtkSmartPointer<vtkPolyData> polyData = vtkSmartPointer<vtkPolyData>::New();
    polyData->SetPoints(points);
    polyData->SetVerts(cellArray);
    polyData->GetPointData()->SetScalars(colors);*/

    // 创建映射器和演员
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputData(poly);
    mapper->SetScalarRange(0, 7); // 设置标量范围

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    // 创建渲染器和渲染窗口
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(actor);

    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);

    // 创建渲染窗口交互器
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    // 显示结果
    renderWindow->Render();
    renderWindowInteractor->Start();
}



void createasphere()
{
    vtkSmartPointer<vtkLookupTable> lut = vtkSmartPointer<vtkLookupTable>::New();
    lut->SetHueRange(0.0, 1.0); // 设置颜色范围

    // 创建一个圆面
    vtkSmartPointer<vtkRegularPolygonSource> circleSource = vtkSmartPointer<vtkRegularPolygonSource>::New();
    circleSource->GeneratePolygonOn(); // 生成一个圆而不是多边形，这个控制是一个面还是一个简单的多边形
    circleSource->SetNumberOfSides(100);
    circleSource->SetRadius(5.0);
    circleSource->Update();

    // 创建一个法线拉伸滤波器
    vtkSmartPointer<vtkLinearExtrusionFilter> extrusionFilter = vtkSmartPointer<vtkLinearExtrusionFilter>::New();
    extrusionFilter->SetInputConnection(circleSource->GetOutputPort());
    //extrusionFilter->SetExtrusionTypeToNormalExtrusion();
    extrusionFilter->SetScaleFactor(10); // 设置拉伸比例因子
    extrusionFilter->SetVector(0, 1, 1); // 设置拉伸向量
    extrusionFilter->Update();

    vtkSmartPointer<vtkFloatArray> color1 = vtkSmartPointer<vtkFloatArray>::New();
    for (int i = 0; i < extrusionFilter->GetOutput()->GetNumberOfPoints(); i++)
    {
        color1->InsertNextValue(i * 0.001);
    }

    extrusionFilter->GetOutput()->GetPointData()->SetScalars(color1);
    extrusionFilter->Update();

    //// 新构建一个几何体然后进行变换

    //进行平移变换
    vtkSmartPointer<vtkRegularPolygonSource> copycircleSource = vtkSmartPointer<vtkRegularPolygonSource>::New();
    //circleSource->GeneratePolygonOff(); // 生成一个圆而不是多边形，这个控制是一个面还是一个简单的多边形
    copycircleSource->SetNumberOfSides(100);
    copycircleSource->SetRadius(5.0);

    // 用滤波器拉伸
    vtkSmartPointer<vtkLinearExtrusionFilter> copyextrusionFilter = vtkSmartPointer<vtkLinearExtrusionFilter>::New();
    copyextrusionFilter->SetInputConnection(copycircleSource->GetOutputPort());
    //extrusionFilter->SetExtrusionTypeToNormalExtrusion();
    copyextrusionFilter->SetScaleFactor(5); // 设置拉伸比例因子
    copyextrusionFilter->SetVector(0, 0, -1); // 设置拉伸向量

    // 设置变换
    vtkSmartPointer<vtkTransform> trans = vtkSmartPointer<vtkTransform>::New();
    trans->Translate(0, 0, -1); // 平移向量 (2, 0, 0)
    // 设置变换滤波器并把变换加进去

    vtkSmartPointer<vtkTransformFilter> transformFilter = vtkSmartPointer<vtkTransformFilter>::New();
    transformFilter->SetInputConnection(copyextrusionFilter->GetOutputPort());
    transformFilter->SetTransform(trans);
    transformFilter->Update();
    // 把滤波器放mapper
    vtkSmartPointer<vtkFloatArray> color = vtkSmartPointer<vtkFloatArray>::New();

    for(int i=0;i< transformFilter->GetOutput()->GetNumberOfPoints();i++)
    {
        color->InsertNextValue(i*0.001);
        cout << i << endl;
    }
        
    transformFilter->GetOutput()->GetPointData()->SetScalars(color);

    
    


    vtkSmartPointer<vtkPolyDataMapper> copiedMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    copiedMapper->SetInputConnection(transformFilter->GetOutputPort());
    copiedMapper->SetLookupTable(lut);
    copiedMapper->Update();

    vtkSmartPointer<vtkActor> copiedActor = vtkSmartPointer<vtkActor>::New();
    copiedActor->SetMapper(copiedMapper);

    // 创建渲染器和演员
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(extrusionFilter->GetOutputPort());

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);


    // 创建渲染窗口
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(actor);
    renderer->AddActor(copiedActor);

    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    // 显示结果
    renderWindow->Render();
    renderWindowInteractor->Start();

}



void plotacircle()
{
   

    // 创建一个圆
    vtkSmartPointer<vtkRegularPolygonSource> polygonSource = vtkSmartPointer<vtkRegularPolygonSource>::New();
    polygonSource->GeneratePolygonOff(); // 生成一个圆而不是多边形
    polygonSource->SetNumberOfSides(50); // 设置边的数量
    polygonSource->SetRadius(5); // 设置半径
    polygonSource->SetCenter(0, 0, 0); // 设置圆心

    // 创建映射器
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(polygonSource->GetOutputPort());

    // 创建演员
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();

    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(1, 0, 0);

    // 创建渲染器
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(actor);
    renderer->SetBackground(0, 0, 1);

    // 创建渲染窗口
    vtkSmartPointer <vtkRenderWindow> renderWindow = vtkSmartPointer <vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);

    // 创建交互器
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);
    renderWindow->SetWindowName("Circle");

    // 渲染并启动交互器
    renderWindow->Render();
    renderWindowInteractor->Start();
}


void plottrianglesingleton()
{
    //创建三个坐标点
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
    points->InsertNextPoint(1.0, 0.0, 0.0); //返回第一个点的ID：0
    points->InsertNextPoint(0.0, 0.0, 4.0); //返回第二个点的ID：1
    points->InsertNextPoint(0.0, 0.0, 0.0); //返回第三个点的ID：2
    points->InsertNextPoint(0.0, 2.0, 0.0); //返回第三个点的ID：3
    ////每两个坐标点之间分别创建一条线
    ////SetId()的第一个参数是线段的端点ID，第二个参数是连接的点的ID
    vtkSmartPointer<vtkLine> line0 = vtkSmartPointer<vtkLine>::New();

    line0->GetPointIds()->SetId(0, 0);
    line0->GetPointIds()->SetId(1, 1);

    vtkSmartPointer<vtkLine> line1 = vtkSmartPointer<vtkLine>::New();
    line1->GetPointIds()->SetId(0, 1);
    line1->GetPointIds()->SetId(1, 2);

    vtkSmartPointer<vtkLine> line2 = vtkSmartPointer<vtkLine>::New();
    line2->GetPointIds()->SetId(0, 2);
    line2->GetPointIds()->SetId(1, 0);

    vtkSmartPointer<vtkLine> line3 = vtkSmartPointer<vtkLine>::New();
    line3->GetPointIds()->SetId(0, 0);
    line3->GetPointIds()->SetId(1, 3);
    vtkSmartPointer<vtkLine> line4 = vtkSmartPointer<vtkLine>::New();
    line4->GetPointIds()->SetId(0, 3);
    line4->GetPointIds()->SetId(1, 1);
    vtkSmartPointer<vtkLine> line5 = vtkSmartPointer<vtkLine>::New();
    line5->GetPointIds()->SetId(0, 3);
    line5->GetPointIds()->SetId(1, 2);
    ////创建Cell数组，用于存储以上创建的线段
    vtkSmartPointer<vtkCellArray> lines = vtkSmartPointer<vtkCellArray>::New();

    lines->InsertNextCell(line0);
    lines->InsertNextCell(line1);
    lines->InsertNextCell(line2);
    lines->InsertNextCell(line3);
    lines->InsertNextCell(line4);
    lines->InsertNextCell(line5);
    vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();

    //将点和线加入到数据集中，前者指定数据集的几何，后者指定其拓扑
    polydata->SetPoints(points);
    polydata->SetLines(lines);

    //显示一个立体形状
   /* vtkSmartPointer<vtkConeSource>coneSource = vtkSmartPointer<vtkConeSource>::New();
    coneSource->Update();
    polydata = coneSource->GetOutput();*/

    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputData(polydata);

    vtkSmartPointer<vtkActor>actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    vtkSmartPointer<vtkRenderer>renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(actor);
    renderer->SetBackground(0.5, 0, 0);
    renderer->ResetCamera();

    vtkSmartPointer<vtkRenderWindow>rwin = vtkSmartPointer<vtkRenderWindow>::New();
    rwin->AddRenderer(renderer);
    rwin->SetSize(600, 600);
    vtkSmartPointer<vtkRenderWindowInteractor>rwinInter =
        vtkSmartPointer<vtkRenderWindowInteractor>::New();
    rwinInter->SetRenderWindow(rwin);
    rwinInter->Initialize();
    rwinInter->Start();

}



int setexture()
{
    // 加载图像数据
    vtkSmartPointer<vtkPNGReader> imageReader = vtkSmartPointer<vtkPNGReader>::New();
    imageReader->SetFileName("C:\\gitlab\\vs\\ConsoleApplication1\\x64\\Debug\\123.png");
    imageReader->Update();

    // 创建平面几何
    vtkSmartPointer<vtkPlaneSource> planeSource = vtkSmartPointer<vtkPlaneSource>::New();


    // 将图像纹理映射到平面
    vtkSmartPointer<vtkTexture> texture = vtkSmartPointer<vtkTexture>::New();
    texture->SetInputConnection(imageReader->GetOutputPort());
   

    // 创建渲染管线
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(planeSource->GetOutputPort());

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    actor->SetTexture(texture);

    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(actor);

    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);

    vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(renderWindow);

    // 渲染和交互
    renderWindow->Render();
    interactor->Start();

    return 0;
}


int readstlfile()
{
    // 创建一个 STL 文件读取器
    vtkSmartPointer<vtkSTLReader> stlReader = vtkSmartPointer<vtkSTLReader>::New();
    stlReader->SetFileName("C:\\gitlab\\vs\\ConsoleApplication1\\x64\\Release\\part.STL"); // 替换为你的 STL 文件路径

    // 创建一个映射器
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(stlReader->GetOutputPort());

    // 创建一个演员
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    // 创建渲染器和窗口
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    // 将演员添加到渲染器
    renderer->AddActor(actor);
    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);

    // 创建交互器
    vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(renderWindow);


    renderer->SetBackground(0.1, 0.1, 0.1); // 设置背景颜色

    // 渲染并启动交互
    renderWindow->Render();
    interactor->Start();

    return 0;
}



int readjpeg()
{
    // 创建一个 JPG 图像读取器
    vtkSmartPointer<vtkPNGReader> jpegReader = vtkSmartPointer<vtkPNGReader>::New();
    jpegReader->SetFileName("C:\\gitlab\\vs\\ConsoleApplication1\\x64\\Debug\\123.jpg"); // 替换为你的图像文件路径
    // 创建一个图像查看器 
    vtkSmartPointer<vtkImageViewer2> imageViewer = vtkSmartPointer<vtkImageViewer2>::New();
    imageViewer->SetInputConnection(jpegReader->GetOutputPort()); //jpegReader->GetOutputPort()返回算法输出端口对象，用于连接
    // 创建一个渲染窗口交互器
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    imageViewer->SetupInteractor(renderWindowInteractor);
    // 渲染图像
    imageViewer->Render();
    // 启动交互
    renderWindowInteractor->Start(); // 这段代码是实现窗口暂停的基础，不然窗口会一闪而过
    return 0;
}



int readtxtandplotpoint()
{
    //std::string filename = "C:\\gitlab\\vs\\ConsoleApplication1\\x64\\Release\\input_file.txt";
    std::string filename = "C:\\gitlab\\vs\\ConsoleApplication1\\ConsoleApplication1\\points.txt";

    // 这块的代码实现的功能主要是通过命令行传入参数

    /*if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <input_file.txt>" << std::endl;
        return 1;
    }*/

    // Read point cloud data from a text file
    std::ifstream inputFile(filename.c_str());
    if (!inputFile.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 1;
    }

    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

    vtkSmartPointer<vtkCellArray> vertices = vtkSmartPointer<vtkCellArray>::New();

    double x, y, z;
    int i = 0;
    while (inputFile >> x >> y >> z) //遇到空格就读取，非空格不读取
    {
        cout << x << ":" << y << ":" << z << endl;
        i++;
        points->InsertNextPoint(x, y, z);
    };
    vertices->InsertNextCell(i); // 2 表示两个点
    while (i > 0)
    {
        cout << "插入" << i << endl;
        i--;
        vertices->InsertCellPoint(i);
    }

    inputFile.close();



    // Create a polydata object
    vtkSmartPointer<vtkPolyData> polyData = vtkSmartPointer<vtkPolyData>::New();
    polyData->SetPoints(points);
    polyData->SetVerts(vertices);

    // Create a mapper
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputData(polyData);
    vtkSmartPointer<vtkActor> pointActor = vtkSmartPointer<vtkActor>::New();
    pointActor->SetMapper(mapper);
    pointActor->GetProperty()->SetColor(1, 0.0, 0.0); // 设置点的颜色
    pointActor->GetProperty()->SetPointSize(5);


    // 创建渲染器和窗口
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);

    // 创建交互器
    vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(renderWindow);

    // 将演员添加到渲染器
    renderer->AddActor(pointActor);
    renderer->SetBackground(0., 0., 0.); // 设置背景颜色

    // 渲染并启动交互
    renderWindow->Render();
    interactor->Start();

    return 0;
}