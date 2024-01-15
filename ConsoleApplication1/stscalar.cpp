#include<stscalar.h> //������û����ģ��������������ͷ�ļ��ͻ��������,�����������ǿ��Զ�������ģ�����main������ͷ�ļ���������������Ԥ�����ʱ��ͻ�����ض��壬��Ϊ����ǻᵥ��������ļ�Ȼ�����ӵ�main�ϣ�����main�������obj����ͻᶼ������һ������



void setscalar()
{
    // ����һ��Բ����Դ
    vtkSmartPointer<vtkCylinderSource> cylinderSource = vtkSmartPointer<vtkCylinderSource>::New();
    cylinderSource->SetHeight(2.0); // ����Բ����߶�
    cylinderSource->SetRadius(1.0); // ����Բ����뾶
    cylinderSource->SetResolution(50); // ����Բ����ֱ���
    cylinderSource->Update(); //��Ҫupdateһ�²��ܻ�ȡ������
    std::ofstream file("points.txt");


    vtkSmartPointer<vtkDoubleArray> scalars = vtkSmartPointer<vtkDoubleArray>::New();
    scalars->SetName(" s");
    vtkSmartPointer<vtkPolyData> poly = vtkSmartPointer<vtkPolyData>::New();

    poly = cylinderSource->GetOutput();

    int num = poly->GetPoints()->GetNumberOfPoints();
    //cout << num << endl; //������200����

    // ��ȡ��������
    vtkSmartPointer<vtkPoints> points = poly->GetPoints();
    for (vtkIdType i = 0; i < points->GetNumberOfPoints(); ++i)
    {
        double point[3];
        points->GetPoint(i, point);
        /*std::cout << "Point " << i << ": (" << point[0] << ", " << point[1] << ", " << point[2] << ")" << std::endl;*/
        // vtk��
        scalars->InsertNextValue(point[1]);
        file << point[0] << " " << point[1] << " " << point[2] << std::endl;
        
    }
    scalars->PrintSelf(cout, vtkIndent(0));
    cout <<"value:" << scalars->GetValue(1) << endl;
    cylinderSource->GetOutput()->GetPointData()->SetScalars(scalars);
    cylinderSource->Update();

    // ����Mapper��Actor
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    //mapper->SetInputConnection(cylinderSource->GetOutputPort());
    mapper->SetInputData(poly);


    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    // ������Ⱦ���ʹ���
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);


    // ����������
    vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(renderWindow);

  

    //vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    //interactor->SetInteractorStyle(style);


     // ���������������
    vtkSmartPointer<vtkAxesActor> axes_actor = vtkSmartPointer<vtkAxesActor>::New();
    axes_actor->SetPosition(0, 0, 0);
    axes_actor->SetTotalLength(2, 2, 2);
    axes_actor->SetShaftType(0);
    axes_actor->SetCylinderRadius(0.02);



    //// ��������ϵ��ʹ֮���ӽǹ�ͬ�仯 
    vtkSmartPointer<vtkOrientationMarkerWidget> widget = vtkSmartPointer<vtkOrientationMarkerWidget>::New();
    widget->SetOrientationMarker(actor);
    widget->SetInteractor(interactor);
    widget->SetEnabled(1);
    widget->InteractiveOn();

      // ��Actor��ӵ���Ⱦ��
    renderer->AddActor(actor);
    renderer->AddActor(axes_actor);
    //renderer->AddActor(axes);
    renderer->SetBackground(1.0, 1.0, 1.0); // ���ñ�����ɫ

    // ��Ⱦ����������
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

    // ��һ������ű�ʾ����һ��std::array����
    //�ڶ�������ű�ʾ���std::array�����а���8��Ԫ�أ�ÿ��Ԫ�ض���һ����������double���͵�ֵ��һά���飬
    //����������ű�ʾ���һά�����а�������double���͵�ֵ��
    //���Ĳ�����ű�ʾ���ֵ�ĳ�ʼ����

    std::array<std::array<vtkIdType, 4>, 6> ording =
    { {{
         {0, 1, 2, 3}}
        ,{{4, 5, 6, 7}}
        ,{{0, 1, 5, 4}}
        ,{{1, 2, 6, 5}}
        ,{{2, 3, 7, 6}}
        ,{{3, 0, 4, 7}}} };
    vtkSmartPointer<vtkPolyData> cube = vtkSmartPointer<vtkPolyData>::New();
    // ����������Ķ�������
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
    vtkSmartPointer<vtkCellArray> polys = vtkSmartPointer<vtkCellArray>::New();
    vtkSmartPointer<vtkFloatArray> scalar = vtkSmartPointer<vtkFloatArray>::New();


    for (size_t i = 0; i < pts.size(); i++)
    {
        points->InsertPoint(i, pts[i].data()); //�������һ��array��ָ��
        //points->inse
        //cout<<"data:" << pts[i].data()[0] << endl;
        scalar->InsertTuple1(i, i); //��ÿһ��������и�ֵ
    };

    for (auto&& i : ording)
    {
        polys->InsertNextCell(vtkIdType(i.size()), i.data());
    };
    cube->SetPoints(points);
    cube->SetPolys(polys);// �����poly��ʵ�����棬��һ��vtkCellArray
    cube->GetPointData()->SetScalars(scalar);// vtkDataArray �洢���Ǿ��������

    // ����ӳ��������Ա
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputData(cube);
    mapper->SetScalarRange(cube->GetScalarRange()); // ���ñ�����Χ

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    // ������Ⱦ������Ⱦ����
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(actor);

    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);

    // ������Ⱦ���ڽ�����
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    // ��ʾ���
    renderWindow->Render();
    renderWindowInteractor->Start();
}


void create2drectange()
{
    // ����������Ķ�������
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
        // Ҳ�������趨������Ȼ�����𽥰ѵ�ӽ�ȥ
        // ����������ÿ���㶼��һ����Ԫ�����������������滹����ȡ����vtkPolyData�е�����
    };

    vtkSmartPointer<vtkPolyData> poly = vtkSmartPointer<vtkPolyData>::New();
    poly->SetPoints(points);
    //poly->SetStrips(strips);
    poly->SetLines(strips);

    //// ���ö�����ɫ
    vtkSmartPointer<vtkFloatArray> colors = vtkSmartPointer<vtkFloatArray>::New();
    colors->InsertNextValue(0); // ��ɫ
    colors->InsertNextValue(1); // ��ɫ
    colors->InsertNextValue(2); // ��ɫ
    colors->InsertNextValue(3); // ��ɫ
    colors->InsertNextValue(4); // ��ɫ
    colors->InsertNextValue(5); // ��ɫ
    colors->InsertNextValue(6); // ��ɫ
    colors->InsertNextValue(7); // ��ɫ

    // �������˽ṹ
    //vtkSmartPointer<vtkCellArray> cellArray = vtkSmartPointer<vtkCellArray>::New();
    //cellArray->InsertNextCell(8);
    //for (vtkIdType i = 0; i < 8; ++i)
    //{
    //    cellArray->InsertCellPoint(i);
    //}

    //// ����PolyData
    /*vtkSmartPointer<vtkPolyData> polyData = vtkSmartPointer<vtkPolyData>::New();
    polyData->SetPoints(points);
    polyData->SetVerts(cellArray);
    polyData->GetPointData()->SetScalars(colors);*/

    // ����ӳ��������Ա
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputData(poly);
    mapper->SetScalarRange(0, 7); // ���ñ�����Χ

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    // ������Ⱦ������Ⱦ����
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(actor);

    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);

    // ������Ⱦ���ڽ�����
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    // ��ʾ���
    renderWindow->Render();
    renderWindowInteractor->Start();
}



void createasphere()
{
    vtkSmartPointer<vtkLookupTable> lut = vtkSmartPointer<vtkLookupTable>::New();
    lut->SetHueRange(0.0, 1.0); // ������ɫ��Χ

    // ����һ��Բ��
    vtkSmartPointer<vtkRegularPolygonSource> circleSource = vtkSmartPointer<vtkRegularPolygonSource>::New();
    circleSource->GeneratePolygonOn(); // ����һ��Բ�����Ƕ���Σ����������һ���滹��һ���򵥵Ķ����
    circleSource->SetNumberOfSides(100);
    circleSource->SetRadius(5.0);
    circleSource->Update();

    // ����һ�����������˲���
    vtkSmartPointer<vtkLinearExtrusionFilter> extrusionFilter = vtkSmartPointer<vtkLinearExtrusionFilter>::New();
    extrusionFilter->SetInputConnection(circleSource->GetOutputPort());
    //extrusionFilter->SetExtrusionTypeToNormalExtrusion();
    extrusionFilter->SetScaleFactor(10); // ���������������
    extrusionFilter->SetVector(0, 1, 1); // ������������
    extrusionFilter->Update();

    vtkSmartPointer<vtkFloatArray> color1 = vtkSmartPointer<vtkFloatArray>::New();
    for (int i = 0; i < extrusionFilter->GetOutput()->GetNumberOfPoints(); i++)
    {
        color1->InsertNextValue(i * 0.001);
    }

    extrusionFilter->GetOutput()->GetPointData()->SetScalars(color1);
    extrusionFilter->Update();

    //// �¹���һ��������Ȼ����б任

    //����ƽ�Ʊ任
    vtkSmartPointer<vtkRegularPolygonSource> copycircleSource = vtkSmartPointer<vtkRegularPolygonSource>::New();
    //circleSource->GeneratePolygonOff(); // ����һ��Բ�����Ƕ���Σ����������һ���滹��һ���򵥵Ķ����
    copycircleSource->SetNumberOfSides(100);
    copycircleSource->SetRadius(5.0);

    // ���˲�������
    vtkSmartPointer<vtkLinearExtrusionFilter> copyextrusionFilter = vtkSmartPointer<vtkLinearExtrusionFilter>::New();
    copyextrusionFilter->SetInputConnection(copycircleSource->GetOutputPort());
    //extrusionFilter->SetExtrusionTypeToNormalExtrusion();
    copyextrusionFilter->SetScaleFactor(5); // ���������������
    copyextrusionFilter->SetVector(0, 0, -1); // ������������

    // ���ñ任
    vtkSmartPointer<vtkTransform> trans = vtkSmartPointer<vtkTransform>::New();
    trans->Translate(0, 0, -1); // ƽ������ (2, 0, 0)
    // ���ñ任�˲������ѱ任�ӽ�ȥ

    vtkSmartPointer<vtkTransformFilter> transformFilter = vtkSmartPointer<vtkTransformFilter>::New();
    transformFilter->SetInputConnection(copyextrusionFilter->GetOutputPort());
    transformFilter->SetTransform(trans);
    transformFilter->Update();
    // ���˲�����mapper
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

    // ������Ⱦ������Ա
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(extrusionFilter->GetOutputPort());

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);


    // ������Ⱦ����
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(actor);
    renderer->AddActor(copiedActor);

    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    // ��ʾ���
    renderWindow->Render();
    renderWindowInteractor->Start();

}



void plotacircle()
{
   

    // ����һ��Բ
    vtkSmartPointer<vtkRegularPolygonSource> polygonSource = vtkSmartPointer<vtkRegularPolygonSource>::New();
    polygonSource->GeneratePolygonOff(); // ����һ��Բ�����Ƕ����
    polygonSource->SetNumberOfSides(50); // ���ñߵ�����
    polygonSource->SetRadius(5); // ���ð뾶
    polygonSource->SetCenter(0, 0, 0); // ����Բ��

    // ����ӳ����
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(polygonSource->GetOutputPort());

    // ������Ա
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();

    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(1, 0, 0);

    // ������Ⱦ��
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(actor);
    renderer->SetBackground(0, 0, 1);

    // ������Ⱦ����
    vtkSmartPointer <vtkRenderWindow> renderWindow = vtkSmartPointer <vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);

    // ����������
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);
    renderWindow->SetWindowName("Circle");

    // ��Ⱦ������������
    renderWindow->Render();
    renderWindowInteractor->Start();
}


void plottrianglesingleton()
{
    //�������������
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
    points->InsertNextPoint(1.0, 0.0, 0.0); //���ص�һ�����ID��0
    points->InsertNextPoint(0.0, 0.0, 4.0); //���صڶ������ID��1
    points->InsertNextPoint(0.0, 0.0, 0.0); //���ص��������ID��2
    points->InsertNextPoint(0.0, 2.0, 0.0); //���ص��������ID��3
    ////ÿ���������֮��ֱ𴴽�һ����
    ////SetId()�ĵ�һ���������߶εĶ˵�ID���ڶ������������ӵĵ��ID
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
    ////����Cell���飬���ڴ洢���ϴ������߶�
    vtkSmartPointer<vtkCellArray> lines = vtkSmartPointer<vtkCellArray>::New();

    lines->InsertNextCell(line0);
    lines->InsertNextCell(line1);
    lines->InsertNextCell(line2);
    lines->InsertNextCell(line3);
    lines->InsertNextCell(line4);
    lines->InsertNextCell(line5);
    vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();

    //������߼��뵽���ݼ��У�ǰ��ָ�����ݼ��ļ��Σ�����ָ��������
    polydata->SetPoints(points);
    polydata->SetLines(lines);

    //��ʾһ��������״
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
    // ����ͼ������
    vtkSmartPointer<vtkPNGReader> imageReader = vtkSmartPointer<vtkPNGReader>::New();
    imageReader->SetFileName("C:\\gitlab\\vs\\ConsoleApplication1\\x64\\Debug\\123.png");
    imageReader->Update();

    // ����ƽ�漸��
    vtkSmartPointer<vtkPlaneSource> planeSource = vtkSmartPointer<vtkPlaneSource>::New();


    // ��ͼ������ӳ�䵽ƽ��
    vtkSmartPointer<vtkTexture> texture = vtkSmartPointer<vtkTexture>::New();
    texture->SetInputConnection(imageReader->GetOutputPort());
   

    // ������Ⱦ����
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

    // ��Ⱦ�ͽ���
    renderWindow->Render();
    interactor->Start();

    return 0;
}


int readstlfile()
{
    // ����һ�� STL �ļ���ȡ��
    vtkSmartPointer<vtkSTLReader> stlReader = vtkSmartPointer<vtkSTLReader>::New();
    stlReader->SetFileName("C:\\gitlab\\vs\\ConsoleApplication1\\x64\\Release\\part.STL"); // �滻Ϊ��� STL �ļ�·��

    // ����һ��ӳ����
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(stlReader->GetOutputPort());

    // ����һ����Ա
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    // ������Ⱦ���ʹ���
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    // ����Ա��ӵ���Ⱦ��
    renderer->AddActor(actor);
    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);

    // ����������
    vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(renderWindow);


    renderer->SetBackground(0.1, 0.1, 0.1); // ���ñ�����ɫ

    // ��Ⱦ����������
    renderWindow->Render();
    interactor->Start();

    return 0;
}



int readjpeg()
{
    // ����һ�� JPG ͼ���ȡ��
    vtkSmartPointer<vtkPNGReader> jpegReader = vtkSmartPointer<vtkPNGReader>::New();
    jpegReader->SetFileName("C:\\gitlab\\vs\\ConsoleApplication1\\x64\\Debug\\123.jpg"); // �滻Ϊ���ͼ���ļ�·��
    // ����һ��ͼ��鿴�� 
    vtkSmartPointer<vtkImageViewer2> imageViewer = vtkSmartPointer<vtkImageViewer2>::New();
    imageViewer->SetInputConnection(jpegReader->GetOutputPort()); //jpegReader->GetOutputPort()�����㷨����˿ڶ�����������
    // ����һ����Ⱦ���ڽ�����
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    imageViewer->SetupInteractor(renderWindowInteractor);
    // ��Ⱦͼ��
    imageViewer->Render();
    // ��������
    renderWindowInteractor->Start(); // ��δ�����ʵ�ִ�����ͣ�Ļ�������Ȼ���ڻ�һ������
    return 0;
}



int readtxtandplotpoint()
{
    //std::string filename = "C:\\gitlab\\vs\\ConsoleApplication1\\x64\\Release\\input_file.txt";
    std::string filename = "C:\\gitlab\\vs\\ConsoleApplication1\\ConsoleApplication1\\points.txt";

    // ���Ĵ���ʵ�ֵĹ�����Ҫ��ͨ�������д������

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
    while (inputFile >> x >> y >> z) //�����ո�Ͷ�ȡ���ǿո񲻶�ȡ
    {
        cout << x << ":" << y << ":" << z << endl;
        i++;
        points->InsertNextPoint(x, y, z);
    };
    vertices->InsertNextCell(i); // 2 ��ʾ������
    while (i > 0)
    {
        cout << "����" << i << endl;
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
    pointActor->GetProperty()->SetColor(1, 0.0, 0.0); // ���õ����ɫ
    pointActor->GetProperty()->SetPointSize(5);


    // ������Ⱦ���ʹ���
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);

    // ����������
    vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(renderWindow);

    // ����Ա��ӵ���Ⱦ��
    renderer->AddActor(pointActor);
    renderer->SetBackground(0., 0., 0.); // ���ñ�����ɫ

    // ��Ⱦ����������
    renderWindow->Render();
    interactor->Start();

    return 0;
}