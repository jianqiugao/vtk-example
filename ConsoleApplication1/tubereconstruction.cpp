#include<tubereconstuction.h>
 
void tubereconstruction()

{
	vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
	unsigned int gridsize = 30;
	double radius = 1.2;
	for (unsigned int i = 0; i < gridsize; i++)
	{
		points->InsertNextPoint(vtkMath::Random(0, 10), vtkMath::Random(0, 10), 10 * i);
	}; //先做一条样条曲线出来

	/*-----根据三维点插值成样条曲线-----*/
	vtkSmartPointer<vtkParametricSpline>spline01 = vtkSmartPointer<vtkParametricSpline>::New();
	spline01->SetPoints(points);
	spline01->ClosedOff();


	vtkSmartPointer<vtkParametricFunctionSource>splineSource01 = vtkSmartPointer<vtkParametricFunctionSource>::New();
	splineSource01->SetParametricFunction(spline01);
	splineSource01->Update();

	/*以生成的样条曲线为中心生成圆柱体管道*/
	vtkSmartPointer<vtkTubeFilter>tube01 = vtkSmartPointer<vtkTubeFilter>::New();
	tube01->SetInputData(splineSource01->GetOutput());//输入样条曲线
	tube01->SetNumberOfSides(20);//设置圆柱体管道的侧边的数量，数量越多越圆滑
	tube01->SetRadius(radius);//设置圆柱体管道的半径
	tube01->CappingOn();
	tube01->SidesShareVerticesOn();
	tube01->Update();


	/*定义样条曲线的Mapper以及Actor*/
	vtkSmartPointer<vtkPolyDataMapper>splineMapper01 = vtkSmartPointer<vtkPolyDataMapper>::New();
	splineMapper01->SetInputConnection(splineSource01->GetOutputPort());
	splineMapper01->Update();

	vtkSmartPointer<vtkActor>splineActor01 = vtkSmartPointer<vtkActor>::New();
	splineActor01->SetMapper(splineMapper01);
	splineActor01->GetProperty()->SetColor(1, 0, 0);//设置样条曲线的颜色



	/*-----以下为vtk统一的绘制命令，向绘制窗口添加每一段样条曲线以及圆柱体管道的Actor-----*/
	vtkSmartPointer<vtkRenderer>ren1 = vtkSmartPointer<vtkRenderer>::New();
	ren1->SetBackground(0, 0, 0);//设置绘制窗口背景
	ren1->AddActor(splineActor01);
	vtkSmartPointer<vtkRenderWindow>renWin = vtkSmartPointer<vtkRenderWindow>::New();
	renWin->AddRenderer(ren1);
	vtkSmartPointer<vtkRenderWindowInteractor>iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	iren->SetRenderWindow(renWin);

	renWin->SetSize(500, 500);//设置窗口大小
	renWin->Render();//绘制
	iren->Start();//启动交互器

}
