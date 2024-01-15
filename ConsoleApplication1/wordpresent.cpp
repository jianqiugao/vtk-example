#include<wordpresent.h>
void wordpresent()
{
    // ����һ��VTK��Ⱦ������Ⱦ����
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);

    // ����һ��VTK��Ⱦ���ڽ�����
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    // ����һ��vtkTextActor������������
    vtkSmartPointer<vtkTextActor> textActor = vtkSmartPointer<vtkTextActor>::New();
    textActor->SetTextScaleModeToNone(); // �����Զ�����
    textActor->GetTextProperty()->SetFontSize(24);
    textActor->GetTextProperty()->SetColor(1.0, 1.0, 1.0); // �����ı���ɫΪ��ɫ
    textActor->SetInput("Hello, VTK Text Widget!");

    // ����һ��vtkTextRepresentation������������
    vtkSmartPointer<vtkTextRepresentation> textRep = vtkSmartPointer<vtkTextRepresentation>::New();
    textRep->GetPositionCoordinate()->SetValue(0.5, 0.5); // ͨ���ı��ı�ʾ�������ı���λ��
    

    // ����һ��vtkTextWidget������������
    vtkSmartPointer<vtkTextWidget> textWidget = vtkSmartPointer<vtkTextWidget>::New();
    textWidget->SetRepresentation(textRep);
    textWidget->SetTextActor(textActor);
    textWidget->SetInteractor(renderWindowInteractor);
    textWidget->On();

    // ������Ⱦ���ڵĴ�С����������ѭ��
    renderWindow->SetSize(800, 600);
    renderWindow->Render();
    renderWindowInteractor->Initialize();
    renderWindowInteractor->Start();

}