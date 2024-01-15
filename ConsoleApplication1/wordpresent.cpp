#include<wordpresent.h>
void wordpresent()
{
    // 创建一个VTK渲染器和渲染窗口
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);

    // 创建一个VTK渲染窗口交互器
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    // 创建一个vtkTextActor并设置其属性
    vtkSmartPointer<vtkTextActor> textActor = vtkSmartPointer<vtkTextActor>::New();
    textActor->SetTextScaleModeToNone(); // 禁用自动缩放
    textActor->GetTextProperty()->SetFontSize(24);
    textActor->GetTextProperty()->SetColor(1.0, 1.0, 1.0); // 设置文本颜色为白色
    textActor->SetInput("Hello, VTK Text Widget!");

    // 创建一个vtkTextRepresentation并设置其属性
    vtkSmartPointer<vtkTextRepresentation> textRep = vtkSmartPointer<vtkTextRepresentation>::New();
    textRep->GetPositionCoordinate()->SetValue(0.5, 0.5); // 通过文本的表示来设置文本的位置
    

    // 创建一个vtkTextWidget并设置其属性
    vtkSmartPointer<vtkTextWidget> textWidget = vtkSmartPointer<vtkTextWidget>::New();
    textWidget->SetRepresentation(textRep);
    textWidget->SetTextActor(textActor);
    textWidget->SetInteractor(renderWindowInteractor);
    textWidget->On();

    // 设置渲染窗口的大小并启动交互循环
    renderWindow->SetSize(800, 600);
    renderWindow->Render();
    renderWindowInteractor->Initialize();
    renderWindowInteractor->Start();

}