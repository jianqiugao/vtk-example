#include<icppointmatch.h>

void icppointmatcg()
{
	std::string route = "C:\\gitlab\\vs\\ctest\\ctest\\vtk\\Data\\fran_cut.vtk";
	vtkSmartPointer<vtkPolyDataReader> reader = vtkSmartPointer<vtkPolyDataReader>::New();
	reader->SetFileName(route.c_str());
	reader->Update();
	vtkSmartPointer<vtkPolyData> original = reader->GetOutput();

	vtkSmartPointer<vtkTransform> translation = vtkSmartPointer<vtkTransform>::New();
	translation->Translate(0.3, 0.0, 0.0);
	translation->RotateX(15);

	vtkSmartPointer<vtkTransformPolyDataFilter> transformFilter1 = vtkSmartPointer<vtkTransformPolyDataFilter>::New();
	transformFilter1->SetInputData(reader->GetOutput());
	transformFilter1->SetTransform(translation);
	transformFilter1->Update();


	vtkSmartPointer<vtkPolyData> source = vtkSmartPointer<vtkPolyData>::New();
	source->SetPoints(original->GetPoints());


	vtkSmartPointer<vtkPolyData> target = vtkSmartPointer<vtkPolyData>::New();
	target->SetPoints(transformFilter1->GetOutput()->GetPoints());


	// 把点显示出来
	vtkSmartPointer<vtkVertexGlyphFilter> sourceGlyphFilter = vtkSmartPointer<vtkVertexGlyphFilter>::New();
	sourceGlyphFilter->SetInputData(source);
	sourceGlyphFilter->Update();

	vtkSmartPointer<vtkVertexGlyphFilter> targetGlyphFilter = vtkSmartPointer<vtkVertexGlyphFilter>::New();
	targetGlyphFilter->SetInputData(target);
	targetGlyphFilter->Update();

	// 获取的是变换矩阵
	vtkSmartPointer<vtkIterativeClosestPointTransform> icpTransform = vtkSmartPointer<vtkIterativeClosestPointTransform>::New();
	icpTransform->SetSource(source);
	icpTransform->SetTarget(targetGlyphFilter->GetOutput()); // 这个都是vtkdataset 
	icpTransform->GetLandmarkTransform()->SetModeToRigidBody();
	
	//icpTransform
	icpTransform->SetMaximumNumberOfIterations(30);
	icpTransform->StartByMatchingCentroidsOn();
	icpTransform->Modified();
	icpTransform->Update();

	//把变换矩阵进行注入
	vtkSmartPointer<vtkTransformPolyDataFilter> transformFilter2 = vtkSmartPointer<vtkTransformPolyDataFilter>::New();
	transformFilter2->SetInputData(sourceGlyphFilter->GetOutput());
	transformFilter2->SetTransform(icpTransform);
	transformFilter2->Update();

	// 对源点云进行展示
	vtkSmartPointer<vtkPolyDataMapper> sourceMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	sourceMapper->SetInputConnection(sourceGlyphFilter->GetOutputPort());
	 
	vtkSmartPointer<vtkActor> sourceActor = vtkSmartPointer<vtkActor>::New();
	sourceActor->SetMapper(sourceMapper);
	sourceActor->GetProperty()->SetColor(0, 1, 0);
	sourceActor->GetProperty()->SetPointSize(3);

	//目标矩阵进行展示
	vtkSmartPointer<vtkPolyDataMapper> targetMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	targetMapper->SetInputConnection(targetGlyphFilter->GetOutputPort());

	vtkSmartPointer<vtkActor> targetActor = vtkSmartPointer<vtkActor>::New();
	targetActor->SetMapper(targetMapper);
	targetActor->GetProperty()->SetColor(1, 0, 0);
	targetActor->GetProperty()->SetPointSize(3);

	// 选择后的源进行展示
	vtkSmartPointer<vtkPolyDataMapper> solutionMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	solutionMapper->SetInputConnection(transformFilter2->GetOutputPort());


	vtkSmartPointer<vtkActor> solutionActor = vtkSmartPointer<vtkActor>::New();
	solutionActor->SetMapper(solutionMapper);
	solutionActor->GetProperty()->SetColor(0, 0, 1);  
	solutionActor->GetProperty()->SetPointSize(3);


	// 
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->SetBackground(1.0, 1.0, 1.0);

	vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);
	renderer->AddActor(sourceActor);
	renderer->AddActor(targetActor);
	renderer->AddActor(solutionActor);

	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(renderWindow);

	renderWindow->SetSize(640, 480);
	renderWindow->Render();
	renderWindow->SetWindowName("PolyDataICP");
	renderWindow->Render();
	renderWindow->Render();
	renderWindowInteractor->Start();

}