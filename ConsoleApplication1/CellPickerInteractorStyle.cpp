#include <CellPickerInteractorStyle.h>



void CellPickerInteractorStyle::OnLeftButtonDown()
{
	int* pos = this->GetInteractor()->GetEventPosition();
	vtkSmartPointer<vtkCellPicker> picker = vtkSmartPointer<vtkCellPicker>::New();
	picker->SetTolerance(0.0005);
	picker->Pick(pos[0], pos[1], 0, this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer());

	if (picker->GetCellId() != -1)
	{
		vtkSmartPointer<vtkIdTypeArray> ids = vtkSmartPointer<vtkIdTypeArray>::New();
		ids->SetNumberOfComponents(1);
		ids->InsertNextValue(picker->GetCellId()); // 放了一个longlong的整数进去
		cout << picker->GetCellId() << endl;
		vtkSmartPointer<vtkSelectionNode> selectionNode = vtkSmartPointer<vtkSelectionNode>::New();
		selectionNode->SetFieldType(vtkSelectionNode::CELL);
		selectionNode->SetContentType(vtkSelectionNode::INDICES);
		selectionNode->SetSelectionList(ids);

		vtkSmartPointer<vtkSelection> selection = vtkSmartPointer<vtkSelection>::New();
		selection->AddNode(selectionNode);

		vtkSmartPointer<vtkExtractSelection> extractSelection = vtkSmartPointer<vtkExtractSelection>::New();
		polyData = data;
		cout << "polyData == nullptr:" << ((polyData == nullptr) ? "yes" : "no") << endl;
		extractSelection->SetInputData(0, polyData);
		extractSelection->SetInputData(1, selection);
		extractSelection->Update();
		// 目的就是把polydata选取出来


		selectedMapper->SetInputData((vtkDataSet*)extractSelection->GetOutput());
	

		selectedActor->SetMapper(selectedMapper);
		selectedActor->GetProperty()->EdgeVisibilityOn();
		selectedActor->GetProperty()->SetEdgeColor(0, 0, 0);
		selectedActor->GetProperty()->SetLineWidth(3);
		this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(selectedActor);


	}
	vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
}

vtkStandardNewMacro(CellPickerInteractorStyle);