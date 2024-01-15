#include <vtkActor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkObjectFactory.h>
#include <vtkPointPicker.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkRendererCollection.h>
#include <vtkSphereSource.h>
#include <vtkRendererCollection.h>
#include <vtkObjectFactory.h>
#include <vtkCellPicker.h>
#include <vtkSelectionNode.h>
#include <vtkPolyData.h>
#include <vtkUnstructuredGrid.h>
#include <vtkSelection.h>
#include <vtkExtractSelection.h>
#include <vtkNamedColors.h>
#include <vtkDataSetMapper.h>


class MouseInteractorStyle : public vtkInteractorStyleTrackballCamera
{
public:
    static MouseInteractorStyle* New();

    vtkTypeMacro(MouseInteractorStyle, vtkInteractorStyleTrackballCamera);

    MouseInteractorStyle() {
        displayActor = vtkSmartPointer<vtkActor>::New();
        displayActor->GetProperty()->SetColor(1.0, 0.0, 0.0);
    }

    virtual void OnLeftButtonDown() override
    {
        vtkSmartPointer<vtkNamedColors> colors = vtkSmartPointer<vtkNamedColors>::New();

        // �����λ��[x, y]
        int* pos = this->Interactor->GetEventPosition();
        // ��һ�ε������λ��
        int* lastPos = this->Interactor->GetLastEventPosition();

        auto picker = this->Interactor->GetPicker();
        // ǰ��ע���picker�����picker��Ҫ��Ŀ�ľ�������һ��pick������Ȼ��ͨ�����pick�����Ϳ���ʵ��
        // Pick(x, y, z, vtkRenderer)
        picker->Pick(pos[0], pos[1], 0, this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer());

        // ��������������
        double worldPos[3];
        picker->GetPickPosition(worldPos);

        if (picker->IsA("vtkCellPicker"))
        {
            cout << "����" << "vtkCellPicker" << endl;
            auto cellPicker = vtkCellPicker::SafeDownCast(picker);
            std::cout << "Pick Position: [" << worldPos[0] << ", " << worldPos[1] << ", " << worldPos[2] << "]" << std::endl;
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
                displayPoint->SetRadius(0.02);

                auto mapper = vtkSmartPointer <vtkPolyDataMapper>::New();
                mapper->SetInputConnection(displayPoint->GetOutputPort());

                this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->RemoveActor(displayActor);
                displayActor->SetMapper(mapper);
                this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(displayActor);
            }

        }
        else if (picker->IsA("vtkPointPicker"))
        {
            cout << "����" << "vtkPointPicker" << endl;
            auto pointPicker = vtkPointPicker::SafeDownCast(picker);
            std::cout << "PointId: " << pointPicker->GetPointId() << std::endl;
            if (pointPicker->GetPointId() != -1) {
                if (nullptr == data) {
                    std::cout << "Source data not found! " << std::endl;
                    return;
                }
                auto pointPos = data->GetPoint(pointPicker->GetPointId());

                auto displayPoint = vtkSmartPointer<vtkSphereSource>::New();
                displayPoint->SetCenter(pointPos);
                displayPoint->SetRadius(0.02);

                auto mapper = vtkSmartPointer <vtkPolyDataMapper>::New();
                mapper->SetInputConnection(displayPoint->GetOutputPort());

                this->Interactor->GetRenderWindow()
                    ->GetRenderers()
                    ->GetFirstRenderer()
                    ->RemoveActor(displayActor);
                displayActor->SetMapper(mapper);
                this->Interactor->GetRenderWindow()
                    ->GetRenderers()
                    ->GetFirstRenderer()
                    ->AddActor(displayActor);
            }
        }
        else {
            std::cout << "WorldPos: [" << worldPos[0] << ", " << worldPos[1] << ", " << worldPos[2] << "]" << std::endl;
        }

        
        vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
    }

    vtkPolyData* data = nullptr;
    vtkSmartPointer<vtkActor> displayActor = nullptr;
};
vtkStandardNewMacro(MouseInteractorStyle)



int main(int, char* [])
{

    vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->SetThetaResolution(60);
    sphereSource->SetPhiResolution(60);
    sphereSource->Update();

    // Create a mapper and actor
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(sphereSource->GetOutputPort());
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(0, 1, 0);
    /*   actor->GetProperty()->SetRepresentationToWireframe();*/

       // Create a renderer, render window, and interactor
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);
    renderWindow->SetWindowName("PointPicker");

    // ʹ��vtkPointPickerʰȡ��
    //vtkNew<vtkPointPicker> picker;
    // ʹ��vtkCellPickerʰȡ��
    vtkSmartPointer<vtkCellPicker> picker = vtkSmartPointer<vtkCellPicker>::New();
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetPicker(picker);
    renderWindowInteractor->SetRenderWindow(renderWindow);

    vtkSmartPointer<MouseInteractorStyle> style = vtkSmartPointer<MouseInteractorStyle>::New();
    style->data = sphereSource->GetOutput();// ����д������д������
    renderWindowInteractor->SetInteractorStyle(style);

    // Add the actor to the scene
    renderer->AddActor(actor);
    renderer->SetBackground(1, 1, 1);

    // Render and interact
    renderWindow->Render();
    renderWindowInteractor->Start();

    return EXIT_SUCCESS;
}