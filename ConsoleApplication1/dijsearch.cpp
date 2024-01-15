#include<dijsearch.h>


void dijsearch()
{
    // ����һ��Բ����Դ
    vtkSmartPointer<vtkSphereSource> cylinderSource = vtkSmartPointer<vtkSphereSource>::New();
    cylinderSource->SetRadius(5.);
    cylinderSource->SetThetaResolution(60);
    cylinderSource->SetPhiResolution(60);
    cylinderSource->Update(); //��Ҫupdateһ�²��ܻ�ȡ������

    vtkSmartPointer<vtkMassProperties> cylindermass = vtkSmartPointer<vtkMassProperties>::New();
    cylindermass->SetInputConnection(cylinderSource->GetOutputPort());
    cout << "���" << cylindermass->GetVolume() << endl;
    cout << "�����" << cylindermass->GetSurfaceArea() << endl;

    // �������ϵľ���
    vtkSmartPointer<vtkDijkstraGraphGeodesicPath> dijkstra = vtkSmartPointer<vtkDijkstraGraphGeodesicPath>::New();
    dijkstra->SetInputData(cylinderSource->GetOutput());
    dijkstra->SetStartVertex(0);
    dijkstra->SetEndVertex(30);
    dijkstra->Update();

    // ��ȡһ���߶εĳ���
    vtkSmartPointer<vtkPolyData> dijpoly = vtkSmartPointer<vtkPolyData>::New();
    dijpoly = dijkstra->GetOutput();
    cout << "�����·������" << dijpoly->GetLength() << endl;


    //// ������ķ�����,���ֻ�ǻ��Ƽ�ͷ������������Ǳ�Ҫ��
    //vtkSmartPointer<vtkPolyDataNormals> spherenormal = vtkSmartPointer<vtkPolyDataNormals>::New();
    //spherenormal->SetInputConnection(cylinderSource->GetOutputPort());
    ////spherenormal->ComputePointNormalsOn();
    ///*spherenormal->ComputeCellNormalsOn();*/
    //spherenormal->SetComputeCellNormals(0);
    //spherenormal->Update();

    // ͨ��mask��ѡȡһЩ�㹹��polydata
    vtkSmartPointer<vtkMaskPoints> mask = vtkSmartPointer<vtkMaskPoints>::New();
    mask->SetInputData(cylinderSource->GetOutput());
    mask->SetMaximumNumberOfPoints(300);
    mask->RandomModeOn();
    mask->Update();

    vtkSmartPointer<vtkArrowSource> arrowSource = vtkSmartPointer<vtkArrowSource>::New();
    arrowSource->SetTipLength(1);
    arrowSource->SetTipRadius(0.5);

    vtkSmartPointer<vtkGlyph3D> glyph = vtkSmartPointer<vtkGlyph3D>::New();

    // glyph���õ�һ���ǵ�Դһ������״
    glyph->SetInputData(mask->GetOutput());
    //glyph->SetSourceData(arrowSource->GetOutput());
    glyph->SetSourceConnection(arrowSource->GetOutputPort());
    glyph->SetVectorModeToUseNormal();
    glyph->SetScaleFactor(0.5); // ������ͷ��С
    glyph->Update();

     
    //����һ��mapper�����㷨����
    vtkSmartPointer<vtkPolyDataMapper> normalmapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    normalmapper->SetInputConnection(glyph->GetOutputPort());
    normalmapper->Update();

    vtkSmartPointer<vtkActor> normalactor = vtkSmartPointer<vtkActor>::New();
    normalactor->SetMapper(normalmapper);


    // ���ҵ���·��ɸ����
    vtkSmartPointer<vtkPolyDataMapper> djimapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    djimapper->SetInputData(dijkstra->GetOutput());
    djimapper->Update();



    vtkSmartPointer<vtkDoubleArray> scalars = vtkSmartPointer<vtkDoubleArray>::New();
    scalars->SetName("ZCoordinates");
    vtkSmartPointer<vtkPolyData> poly = vtkSmartPointer<vtkPolyData>::New();

    poly = cylinderSource->GetOutput();

    int num = poly->GetPoints()->GetNumberOfPoints();
    cout << num << endl; //������200����

    // ��ȡ��������
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

    // ����Mapper��Actor
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    //mapper->SetInputConnection(cylinderSource->GetOutputPort());
    mapper->SetInputData(poly);
    mapper->SetScalarRange(cylinderSource->GetOutput()->GetScalarRange());


    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);


    vtkSmartPointer<vtkActor> actor_dij = vtkSmartPointer<vtkActor>::New();
    actor_dij->SetMapper(djimapper);
    actor_dij->GetProperty()->SetColor(0, 0, 1);

    // ������Ⱦ���ʹ���
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);


    // ����������
    vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(renderWindow);

    // ��Actor��ӵ���Ⱦ��
    renderer->AddActor(normalactor);
    renderer->AddActor(actor);
    renderer->AddActor(actor_dij);

    renderer->SetBackground(1, 1.0, 1); // ���ñ�����ɫ

    // ��Ⱦ����������
    renderWindow->Render();
    interactor->Start();
}