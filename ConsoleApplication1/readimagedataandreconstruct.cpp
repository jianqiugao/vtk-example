#include "readimagedataandreconstruct.h"

void readimagedataandreconstruct()
{
	//��ȡ��ά��Ƭ��������
	vtkVolume16Reader* reader = vtkVolume16Reader::New();
	reader->SetDataDimensions(64, 64); //��������
	reader->SetDataByteOrderToLittleEndian();
	reader->SetFilePrefix("C:\\gitlab\\vs\\ctest\\ctest\\vtk\\VTK-9.3.0\\Examples\\ImageProcessing\\Cxx\\Testing\\Data\\headsq\\quarter");//���ö�ȡ·��
	reader->SetImageRange(1, 93);
	reader->SetDataSpacing(3.2, 3.2, 1.5);

	vtkSmartPointer<vtkMarchingCubes> boneExtractor = vtkSmartPointer<vtkMarchingCubes>::New();
	boneExtractor->SetInputConnection(reader->GetOutputPort());
	boneExtractor->SetValue(0, 500); // ���õ�ֵ��

	//�޳��ɵĻ�ϳ������ݵ�Ԫ����߻����ٶ�
	vtkSmartPointer<vtkStripper> boneStripper = vtkStripper::New(); //���Ǵ�����
	boneStripper->SetInputConnection(boneExtractor->GetOutputPort());

	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(boneStripper->GetOutputPort());

	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	vtkSmartPointer<vtkRenderer> render = vtkSmartPointer<vtkRenderer>::New();
	render->AddActor(actor);

	vtkSmartPointer<vtkRenderWindow> window = vtkSmartPointer<vtkRenderWindow>::New();
	window->AddRenderer(render);

	vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	interactor->SetRenderWindow(window);
	//render->Render();
	interactor->Start();


}