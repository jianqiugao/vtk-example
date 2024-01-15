#include<basedatainvtk.h>

using namespace std;


void basedatainvtk()
{

    vtkSmartPointer<vtkPolyData> leftPolydata = vtkSmartPointer<vtkPolyData>::New();
    vtkSmartPointer<vtkPolyData> rightPolydata = vtkSmartPointer<vtkPolyData>::New();
    vtkSmartPointer<vtkConeSource> con = vtkSmartPointer<vtkConeSource>::New();
    con->SetHeight(2);
    con->SetAngle(15);
    con->SetResolution(20);
    con->SetRadius(2);
    con->Update();
    int i;
    float x[8][3] = { {0,0,0}, {1,0,0}, {1,1,0}, {0,1,0},
                        {0,0,1}, {1,0,1}, {1,1,1}, {0,1,1} }; //构造正方形的八个顶点

    vtkIdType pts[6][4] = { {0,1,2,3}, {4,5,6,7}, {0,1,5,4},
                        {1,2,6,5}, {2,3,7,6}, {3,0,4,7} }; // 应该是对整数重新命名了

    vtkSmartPointer<vtkPoints> points = vtkSmartPointer <vtkPoints>::New(); //点的输入是数组
    vtkSmartPointer<vtkCellArray> polys = vtkSmartPointer<vtkCellArray>::New(); // 拓扑关系是用vtkCellArray进行存储，而输入的是vtkidtype
    vtkSmartPointer<vtkFloatArray> scalars = vtkSmartPointer <vtkFloatArray>::New();

    /*Load the point, cell, and data attributes.*/
    for (i = 0; i < 8; i++) points->InsertPoint(i, x[i]);  // 插入顶点
    for (i = 0; i < 6; i++) polys->InsertNextCell(4, pts[i]);// 插入6个面的拓扑结构
    //for (i = 0; i < 8; i++) scalars->InsertTuple1(i, i * i); // 插入颜色
    for (i = 0; i < 8; i++) scalars->InsertNextValue(i); // 插入颜色

    leftPolydata->SetPoints(points);
    leftPolydata->SetPolys(polys);
    leftPolydata->GetPointData()->SetScalars(scalars);



    rightPolydata->DeepCopy(leftPolydata); //这里是深拷贝

    //rightPolydata = con->GetOutput();
    int num = rightPolydata->GetPoints()->GetNumberOfPoints();
    cout << "num" << num << endl;
    vtkSmartPointer<vtkDoubleArray> scalars1 = vtkSmartPointer<vtkDoubleArray>::New();

    //获取顶点坐标
    vtkSmartPointer<vtkPoints> points1 = rightPolydata->GetPoints();
    for (vtkIdType i = 0; i < points->GetNumberOfPoints(); ++i)
    {
        double point[3];
        points1->GetPoint(i, point);// 初始化后把id和点的指针传递进去
        /*std::cout << "Point " << i << ": (" << point[0] << ", " << point[1] << ", " << point[2] << ")" << std::endl;*/
        scalars1->InsertNextValue(point[2]);
    }

    rightPolydata->GetPointData()->SetScalars(scalars1);


    vtkSmartPointer<vtkPolyDataMapper> leftMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    leftMapper->SetInputData(leftPolydata);

    vtkSmartPointer<vtkActor> leftActor = vtkSmartPointer<vtkActor>::New();
    leftActor->SetMapper(leftMapper);

    /*Define viewport ranges
    (xmin, ymin, xmax, ymax) left-top and right-bottom point*/
    double leftViewport[4] = { 0.0, 0.0, 0.5, 1.0 };
    double rightViewport[4] = { 0.5, 0.0, 1.0, 1.0 };

    /* Setup renderers*/
    vtkSmartPointer<vtkRenderer> leftRenderer = vtkSmartPointer<vtkRenderer>::New();
    leftRenderer->SetViewport(leftViewport);
    leftRenderer->SetBackground(0, 0, 0);

    vtkSmartPointer<vtkRenderer> rightRenderer = vtkSmartPointer<vtkRenderer>::New();
    rightRenderer->SetViewport(rightViewport);
    rightRenderer->SetBackground(0, 0, 0);

    leftRenderer->AddActor(leftActor);

    vtkSmartPointer<vtkPolyDataMapper> rightMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    rightMapper->SetInputData(rightPolydata);
    vtkSmartPointer<vtkActor> rightActor = vtkSmartPointer<vtkActor>::New();
    rightActor->SetMapper(rightMapper);

    rightRenderer->AddActor(rightActor);

    /*控制一起移动*/
    vtkSmartPointer<vtkCamera> camera = vtkSmartPointer<vtkCamera>::New();
    leftRenderer->SetActiveCamera(camera);
    rightRenderer->SetActiveCamera(camera);

    leftRenderer->ResetCamera();
    rightRenderer->ResetCamera();

    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->SetSize(600, 300);
    renderWindow->AddRenderer(leftRenderer);
    renderWindow->AddRenderer(rightRenderer);



    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    /*控制坐标系，使之随视角共同变化

    进行坐标轴的设置*/
    vtkSmartPointer<vtkAxesActor> axes_actor = vtkSmartPointer<vtkAxesActor>::New();
    axes_actor->SetPosition(0, 0, 0);
    axes_actor->SetTotalLength(2, 2, 2);
    axes_actor->SetShaftType(0);
    axes_actor->SetCylinderRadius(0.02);

    vtkSmartPointer<vtkOrientationMarkerWidget> widget = vtkSmartPointer<vtkOrientationMarkerWidget>::New();
    widget->SetOrientationMarker(axes_actor);
    widget->SetInteractor(renderWindowInteractor);
    widget->SetEnabled(1);
    widget->InteractiveOn();

    vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    renderWindowInteractor->SetInteractorStyle(style);


    renderWindow->Render();
    renderWindowInteractor->Start();
}
