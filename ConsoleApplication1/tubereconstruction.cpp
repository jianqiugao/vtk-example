#include<tubereconstuction.h>
 
void tubereconstruction()

{
	vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
	unsigned int gridsize = 30;
	double radius = 1.2;
	for (unsigned int i = 0; i < gridsize; i++)
	{
		points->InsertNextPoint(vtkMath::Random(0, 10), vtkMath::Random(0, 10), 10 * i);
	}; //����һ���������߳���

	/*-----������ά���ֵ����������-----*/
	vtkSmartPointer<vtkParametricSpline>spline01 = vtkSmartPointer<vtkParametricSpline>::New();
	spline01->SetPoints(points);
	spline01->ClosedOff();


	vtkSmartPointer<vtkParametricFunctionSource>splineSource01 = vtkSmartPointer<vtkParametricFunctionSource>::New();
	splineSource01->SetParametricFunction(spline01);
	splineSource01->Update();

	/*�����ɵ���������Ϊ��������Բ����ܵ�*/
	vtkSmartPointer<vtkTubeFilter>tube01 = vtkSmartPointer<vtkTubeFilter>::New();
	tube01->SetInputData(splineSource01->GetOutput());//������������
	tube01->SetNumberOfSides(20);//����Բ����ܵ��Ĳ�ߵ�����������Խ��ԽԲ��
	tube01->SetRadius(radius);//����Բ����ܵ��İ뾶
	tube01->CappingOn();
	tube01->SidesShareVerticesOn();
	tube01->Update();


	/*�����������ߵ�Mapper�Լ�Actor*/
	vtkSmartPointer<vtkPolyDataMapper>splineMapper01 = vtkSmartPointer<vtkPolyDataMapper>::New();
	splineMapper01->SetInputConnection(splineSource01->GetOutputPort());
	splineMapper01->Update();

	vtkSmartPointer<vtkActor>splineActor01 = vtkSmartPointer<vtkActor>::New();
	splineActor01->SetMapper(splineMapper01);
	splineActor01->GetProperty()->SetColor(1, 0, 0);//�����������ߵ���ɫ



	/*-----����Ϊvtkͳһ�Ļ����������ƴ������ÿһ�����������Լ�Բ����ܵ���Actor-----*/
	vtkSmartPointer<vtkRenderer>ren1 = vtkSmartPointer<vtkRenderer>::New();
	ren1->SetBackground(0, 0, 0);//���û��ƴ��ڱ���
	ren1->AddActor(splineActor01);
	vtkSmartPointer<vtkRenderWindow>renWin = vtkSmartPointer<vtkRenderWindow>::New();
	renWin->AddRenderer(ren1);
	vtkSmartPointer<vtkRenderWindowInteractor>iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	iren->SetRenderWindow(renWin);

	renWin->SetSize(500, 500);//���ô��ڴ�С
	renWin->Render();//����
	iren->Start();//����������

}
