
#include<reconstructVesselTroughTubeFilter.h>

// ��Ȼ�����������
using namespace std;//ʹ��C++�����ռ�
using namespace cv; //ʹ��OpenCV�����ռ�

#define  PI 3.14159265358979323846 //�궨��Բ����PI

void InitMat(Mat& m, double* num)//��һά�����ʼ��OpenCV����Mat����
{
	for (int i = 0; i < m.rows; i++)
	{
		for (int j = 0; j < m.cols; j++)
		{
			m.at<double>(i, j) = *(num + i * m.cols + j);
		}
	}
}


Mat GenerateRymat(double jiaodu)//����Ry����OpenCV����Mat����,�����Ƕ�Ϊ�Ƕȣ�ֱ�ӷ���һ��Mat����
{
	double m[] = { cos(jiaodu / 180 * PI),0,-sin(jiaodu / 180 * PI),
		0,1,0,
		sin(jiaodu / 180 * PI),0,cos(jiaodu / 180 * PI)
	};
	Mat Mtemp(3, 3, CV_64F);
	InitMat(Mtemp, m);
	return Mtemp;
}



Mat GenerateRxmat(double jiaodu)//����Rx����OpenCV����Mat����,�����Ƕ�Ϊ�Ƕ�,ֱ�ӷ���һ��Mat����
{
	double m[] = { 1,0,0,
		0,cos(jiaodu / 180 * PI),sin(jiaodu / 180 * PI),
		0,-sin(jiaodu / 180 * PI),cos(jiaodu / 180 * PI)
	};
	Mat Mtemp(3, 3, CV_64F);
	InitMat(Mtemp, m);
	return Mtemp;
}

float ExtractMatIJValue(Mat& M, int i, int j)//��ȡMat�����i�е�j�е���ֵ,MΪMat����ijΪ����ֵ
{
	return M.at<double>(i, j);
}


Mat Generate3DAmat(Mat& M, My_Scalefactor& myfactor)//�����������ά���A����MΪMat�����,Ϊ�������R����My_ScalefactorΪstruct
{
	Mat Mattemp(4, 3, CV_64F);
	Mattemp.at<double>(0, 0) = 1;
	Mattemp.at<double>(0, 1) = 0.0;
	Mattemp.at<double>(0, 2) = -myfactor.IamgeAXfactor;
	Mattemp.at<double>(1, 0) = 0;
	Mattemp.at<double>(1, 1) = 1;
	Mattemp.at<double>(1, 2) = -myfactor.ImageAYfactor;
	Mattemp.at<double>(2, 0) = ExtractMatIJValue(M, 0, 0) - (ExtractMatIJValue(M, 2, 0)

		* myfactor.ImageBXfactor);
	Mattemp.at<double>(2, 1) = ExtractMatIJValue(M, 0, 1) - (ExtractMatIJValue(M, 2, 1)

		* myfactor.ImageBXfactor);
	Mattemp.at<double>(2, 2) = ExtractMatIJValue(M, 0, 2) - (ExtractMatIJValue(M, 2, 2)

		* myfactor.ImageBXfactor);
	Mattemp.at<double>(3, 0) = ExtractMatIJValue(M, 1, 0) - (ExtractMatIJValue(M, 2, 0)

		* myfactor.ImageBYfactor);
	Mattemp.at<double>(3, 1) = ExtractMatIJValue(M, 1, 1) - (ExtractMatIJValue(M, 2, 1)

		* myfactor.ImageBYfactor);
	Mattemp.at<double>(3, 2) = ExtractMatIJValue(M, 1, 2) - (ExtractMatIJValue(M, 2, 2)

		* myfactor.ImageBYfactor);
	//	InitMat(Mattemp,m);
	return Mattemp;

}


Mat Genreate3Damat(Mat& M, My_Scalefactor& myfactor)//������B�����a����
{
	double m[] = { ExtractMatIJValue(M,0,0) - ExtractMatIJValue(M,2,0) * myfactor.ImageBXfactor,
		ExtractMatIJValue(M,0,1) - ExtractMatIJValue(M,2,1) * myfactor.ImageBXfactor,
		ExtractMatIJValue(M,0,2) - ExtractMatIJValue(M,2,2) * myfactor.ImageBXfactor
	};
	Mat Mattemp(1, 3, CV_64F);
	InitMat(Mattemp, m);
	return Mattemp;
}



Mat Generate3DTmat(double T)//������B�����T����
{

	Mat Mattemp(3, 1, CV_64F);
	Mattemp.at<double>(0, 0) = 0.0;
	Mattemp.at<double>(1, 0) = 0.0;
	Mattemp.at<double>(2, 0) = T;

	return Mattemp;
}


Mat Generate3Dbmat(Mat& M, My_Scalefactor& myfactor)//������B�����b����
{
	double m[] = { ExtractMatIJValue(M,1,0) - ExtractMatIJValue(M,2,0) * myfactor.ImageBYfactor,
		ExtractMatIJValue(M,1,1) - ExtractMatIJValue(M,2,1) * myfactor.ImageBYfactor,
		ExtractMatIJValue(M,1,2) - ExtractMatIJValue(M,2,2) * myfactor.ImageBYfactor
	};
	Mat Mattemp(1, 3, CV_64F);
	InitMat(Mattemp, m);
	return Mattemp;
}


Mat Generate3DBmat(Mat& a, Mat& b, Mat& t)//�����������ά���B����
{
	Mat at, bt;
	at = a * t;
	bt = b * t;
	Mat Mattemp(4, 1, CV_64F);
	Mattemp.at<double>(0, 0) = 0.0;
	Mattemp.at<double>(1, 0) = 0.0;
	Mattemp.at<double>(2, 0) = at.at<double>(0, 0);
	Mattemp.at<double>(3, 0) = bt.at<double>(0, 0);
	return Mattemp;
}

void plotVesselbuTubeFilter()
{
	Mat R;//������ת�������
	Mat t;//����ƽ�ƾ������
	//	Mat Rxp2,Rya2,Rya1,Rxp1;//��������ת����R��ԭʼ����
	// ImageA�ǶȲ���Ϊ RAO 0��CAUD 35 ����a1=0,p1=35
	// ImageB�ǶȲ���Ϊ LAO 80��CRAN 15 ����a2=80,p2=15
	// ��Ϊa1ΪRAO�Ƕȣ�����a1=-a1=0,p1=35��a2ΪLAO�Ƕȣ�a2=-a2=-80,
	// ��Ϊp2ΪCRAN�Ƕȣ�����p2=-p2=-15
	double a1, a2, p1, p2;//�����Ƕ�
	/*a1=0;
	a2=-80;
	p1=35;
	p2=-15;*/

	//�ԽǶȽ��и�ֵ
	a1 = 0;
	a2 = 80;
	p1 = 35;
	p2 = 15;
	int radius = 3;

	R = GenerateRxmat(p2) * GenerateRymat(a2) * GenerateRymat(a1) * GenerateRxmat(-p1);//����ת����R

	double T1 = 755, T2 = 865;//������������T1��ʾO�㵽s1�ľ��룬T2��ʾO�㵽s2�ľ���
	t = Generate3DTmat(T1) - (R.inv() * Generate3DTmat(T2));//��ƽ�ƾ���t


	vector<My2dPoint>ImageApoint;//�����洢ImageA�����ߵ����������
	ImageApoint.clear();//�տ�ʼ����������е�����
	vector<My2dPoint>ImageBpoint;//�����洢ImageB�����ߵ����������
	ImageBpoint.clear();//�տ�ʼ����������е�����


	/*-----��txt�ж�ȡ����ͼƬ�ֹ�ƥ��Ķ�ά�����ݣ���������䵽����֮��ȥ-----*/
	FILE* ImageA = NULL;//�����ȡͼƬA�϶�ά��������ļ�ָ��
	FILE* ImageB = NULL;//�����ȡͼƬB�϶�ά��������ļ�ָ��

	fopen_s(&ImageA, "ImageA2.txt", "rb");//�򿪴洢ͼƬA��ά�������txt�ļ�

	if (!ImageA)
	{
		cout << "���ļ�ʧ��" << endl;
	}
	double ImageAx, ImageAy;//������ʱ��ά���������
	My2dPoint ImageAtemp;//������ʱ�Ķ�ά��ṹ��

	while (!feof(ImageA))//���ж�ȡ����
	{
		fscanf_s(ImageA, "%lf %lf", &ImageAx, &ImageAy);//����ʽ��ȡ����
		//����ʱ������ֵ������ά�ṹ�����Ӧ����
		ImageAtemp.x = ImageAx;
		ImageAtemp.y = ImageAy;
		ImageApoint.push_back(ImageAtemp);//��������ѹ������ṹ��
	}

	fopen_s(&ImageB, "ImageB2.txt", "rb");//�򿪴洢ͼƬB��ά�������txt�ļ�
	//std::ifstream ImageB("E:/ImageB2.txt");

	if (!ImageB)
	{
		cout << "���ļ�ʧ��" << endl;
	}
	double ImageBx, ImageBy;//������ʱ��ά���������
	My2dPoint ImageBtemp;//������ʱ�Ķ�ά��ṹ��
	while (!feof(ImageB))//���ж�ȡ����
	{
		fscanf_s(ImageB, "%lf %lf", &ImageBx, &ImageBy);//����ʽ��ȡ����
		//����ʱ������ֵ������ά�ṹ�����Ӧ����
		ImageBtemp.x = ImageBx;
		ImageBtemp.y = ImageBy;
		ImageBpoint.push_back(ImageBtemp);//��������ѹ������ṹ��
	}


	//����X����ԴS1��S2������ͶӰƽ��Ĵ�ֱ����D1��D2
	int D1 = 987, D2 = 987;

	vector<My3dPoint> Result3Dpoint;//�����洢�����ImageA��ImageB��ά���������ά�����������

	Result3Dpoint.clear();
	for (int i = 0; i < ImageApoint.size() - 1; i++)
	{
		/*-----�����������-----*/
		My_Scalefactor temp;
		temp.IamgeAXfactor = ImageApoint[i].x / D1;
		temp.ImageAYfactor = ImageApoint[i].y / D1;
		temp.ImageBXfactor = ImageBpoint[i].x / D2;
		temp.ImageBYfactor = ImageBpoint[i].y / D2;

		/*-----ʵ�ִӶ�ά������ά��ת��-----*/
		Mat A, a, b, B;//�������������ά�����ľ����Լ����
		A = Generate3DAmat(R, temp);
		a = Genreate3Damat(R, temp);
		b = Generate3Dbmat(R, temp);
		B = Generate3DBmat(a, b, t);

		Mat C;//������ά������Ľ������
		C = (A.t() * A).inv() * A.t() * B;
		My3dPoint Result;
		Result.x = C.at<double>(0);
		Result.y = C.at<double>(1);
		Result.z = C.at<double>(2);
		ofstream f;
		f.open("��ά����2.txt", ios::out | ios::app);
		f << Result.x << "	" << Result.y << "	" << Result.z << endl;
		Result3Dpoint.push_back(Result);
	}

	/*-----�ܾ������������Ĺ�����ά���ؽ��Ľ������˳�����������ֵ������������-----*/
	/*-----���Բ�ֵ�����ɵ���������Ϊ��������Բ����ܵ���ͨ�����ò�ͬ��Բ����뾶�ﵽģ�������Ŀ��-----*/
	/*-----����vtk��ͼ����,��ʼ����-----*/

	/*-----���Ƶ�һ��������ֵ�����Լ�Բ����ܵ�����0�㵽1��-----*/
	/*-----��һ��Բ����ܵ��Ļ�������ϸע�ͣ����¼�������-----*/
	vtkSmartPointer<vtkPoints>point01 = vtkSmartPointer<vtkPoints>::New(); //������һ�������������������ĵ��VTK����ָ��
	//����������õ���ά��Ľ�������һ���ߵĵ������ָ���в�����ά��
	point01->InsertPoint(0, Result3Dpoint[0].x, Result3Dpoint[0].y, Result3Dpoint[0].z);
	point01->InsertPoint(1, Result3Dpoint[1].x, Result3Dpoint[1].y, Result3Dpoint[1].z);
	point01->InsertPoint(2, Result3Dpoint[2].x, Result3Dpoint[2].y, Result3Dpoint[2].z);
	point01->InsertPoint(3, Result3Dpoint[3].x, Result3Dpoint[3].y, Result3Dpoint[3].z);
	point01->InsertPoint(4, Result3Dpoint[4].x, Result3Dpoint[4].y, Result3Dpoint[4].z);

	/*-----������ά���ֵ����������-----*/
	vtkSmartPointer<vtkParametricSpline>spline01 = vtkSmartPointer<vtkParametricSpline>::New();
	spline01->SetPoints(point01);
	spline01->ClosedOff();

	vtkSmartPointer<vtkParametricFunctionSource>splineSource01 = vtkSmartPointer<vtkParametricFunctionSource>::New();
	splineSource01->SetParametricFunction(spline01);
	splineSource01->Update();

	/*�����������ߵ�Mapper�Լ�Actor*/
	vtkSmartPointer<vtkPolyDataMapper>splineMapper01 = vtkSmartPointer<vtkPolyDataMapper>::New();
	splineMapper01->SetInputConnection(splineSource01->GetOutputPort());

	vtkSmartPointer<vtkActor>splineActor01 = vtkSmartPointer<vtkActor>::New();
	splineActor01->SetMapper(splineMapper01);
	splineActor01->GetProperty()->SetColor(1, 0, 0);//�����������ߵ���ɫ

	/*�����ɵ���������Ϊ��������Բ����ܵ�*/
	vtkSmartPointer<vtkTubeFilter>tube01 = vtkSmartPointer<vtkTubeFilter>::New();
	tube01->SetInputData(splineSource01->GetOutput());//������������
	tube01->SetNumberOfSides(20);//����Բ����ܵ��Ĳ�ߵ�����������Խ��ԽԲ��
	tube01->SetRadius(radius);//����Բ����ܵ��İ뾶
	tube01->Update();

	/*�������ɵ�Բ����ܵ���Mapper��Actor���Ա���VTK�н��л���*/
	vtkSmartPointer<vtkPolyDataMapper>tubeMapper01 = vtkSmartPointer<vtkPolyDataMapper>::New();
	tubeMapper01->SetInputData(tube01->GetOutput());

	vtkSmartPointer<vtkActor>tubeActor01 = vtkSmartPointer<vtkActor>::New();
	tubeActor01->SetMapper(tubeMapper01);
	tubeActor01->GetProperty()->SetColor(1, 0, 0);//����Բ�������ɫ

	/*-----���Ƶڶ���������ֵ�����Լ�Բ����ܵ�����1�㵽2��-----*/
	vtkSmartPointer<vtkPoints>point12 = vtkSmartPointer<vtkPoints>::New();
	point12->InsertPoint(0, Result3Dpoint[4].x, Result3Dpoint[4].y, Result3Dpoint[4].z);
	point12->InsertPoint(1, Result3Dpoint[5].x, Result3Dpoint[5].y, Result3Dpoint[5].z);
	point12->InsertPoint(2, Result3Dpoint[6].x, Result3Dpoint[6].y, Result3Dpoint[6].z);
	point12->InsertPoint(3, Result3Dpoint[7].x, Result3Dpoint[7].y, Result3Dpoint[7].z);
	point12->InsertPoint(4, Result3Dpoint[8].x, Result3Dpoint[8].y, Result3Dpoint[8].z);
	point12->InsertPoint(5, Result3Dpoint[9].x, Result3Dpoint[9].y, Result3Dpoint[9].z);
	point12->InsertPoint(6, Result3Dpoint[10].x, Result3Dpoint[10].y, Result3Dpoint[10].z);

	vtkSmartPointer<vtkParametricSpline>spline12 = vtkSmartPointer<vtkParametricSpline>::New();
	spline12->SetPoints(point12);
	spline12->ClosedOff();


	vtkSmartPointer<vtkParametricFunctionSource>splineSource12 = vtkSmartPointer<vtkParametricFunctionSource>::New();
	splineSource12->SetParametricFunction(spline12);
	splineSource12->Update();

	vtkSmartPointer<vtkPolyDataMapper>splineMapper12 = vtkSmartPointer<vtkPolyDataMapper>::New();
	splineMapper12->SetInputConnection(splineSource12->GetOutputPort());

	vtkSmartPointer<vtkActor>splineActor12 = vtkSmartPointer<vtkActor>::New();
	splineActor12->SetMapper(splineMapper12);
	splineActor12->GetProperty()->SetColor(0.38, 0.7, 0.16);

	vtkSmartPointer<vtkTubeFilter>tube12 = vtkSmartPointer<vtkTubeFilter>::New();
	tube12->SetInputData(splineSource12->GetOutput());
	tube12->SetNumberOfSides(20);
	tube12->SetRadius(radius);
	tube12->Update();

	vtkSmartPointer<vtkPolyDataMapper>tubeMapper12 = vtkSmartPointer<vtkPolyDataMapper>::New();
	tubeMapper12->SetInputData(tube12->GetOutput());

	vtkSmartPointer<vtkActor>tubeActor12 = vtkSmartPointer<vtkActor>::New();
	tubeActor12->SetMapper(tubeMapper12);
	tubeActor12->GetProperty()->SetColor(1, 0, 0);


	/*-----���Ƶ�����������ֵ�����Լ�Բ����ܵ�����2�㵽3��-----*/
	vtkSmartPointer<vtkPoints>point23 = vtkSmartPointer<vtkPoints>::New();
	point23->InsertPoint(0, Result3Dpoint[10].x, Result3Dpoint[10].y, Result3Dpoint[10].z);
	point23->InsertPoint(1, Result3Dpoint[11].x, Result3Dpoint[11].y, Result3Dpoint[11].z);
	point23->InsertPoint(2, Result3Dpoint[12].x, Result3Dpoint[12].y, Result3Dpoint[12].z);
	point23->InsertPoint(3, Result3Dpoint[13].x, Result3Dpoint[13].y, Result3Dpoint[13].z);
	point23->InsertPoint(4, Result3Dpoint[14].x, Result3Dpoint[14].y, Result3Dpoint[14].z);
	point23->InsertPoint(5, Result3Dpoint[15].x, Result3Dpoint[15].y, Result3Dpoint[15].z);


	vtkSmartPointer<vtkParametricSpline>spline23 = vtkSmartPointer<vtkParametricSpline>::New();
	spline23->SetPoints(point23);
	spline23->ClosedOff();

	vtkSmartPointer<vtkParametricFunctionSource>splineSource23 = vtkSmartPointer<vtkParametricFunctionSource>::New();
	splineSource23->SetParametricFunction(spline23);
	splineSource23->Update();

	vtkSmartPointer<vtkPolyDataMapper>splineMapper23 = vtkSmartPointer<vtkPolyDataMapper>::New();
	splineMapper23->SetInputConnection(splineSource23->GetOutputPort());

	vtkSmartPointer<vtkActor>splineActor23 = vtkSmartPointer<vtkActor>::New();
	splineActor23->SetMapper(splineMapper23);
	splineActor23->GetProperty()->SetColor(0.38, 0.7, 0.16);

	vtkSmartPointer<vtkTubeFilter>tube23 = vtkSmartPointer<vtkTubeFilter>::New();
	tube23->SetInputData(splineSource23->GetOutput());
	tube23->SetNumberOfSides(23);
	tube23->SetRadius(radius);
	tube23->Update();

	vtkSmartPointer<vtkPolyDataMapper>tubeMapper23 = vtkSmartPointer<vtkPolyDataMapper>::New();
	tubeMapper23->SetInputData(tube23->GetOutput());

	vtkSmartPointer<vtkActor>tubeActor23 = vtkSmartPointer<vtkActor>::New();
	tubeActor23->SetMapper(tubeMapper23);
	tubeActor23->GetProperty()->SetColor(1, 0, 0);

	/*-----���Ƶ��Ķ�������ֵ�����Լ�Բ����ܵ�����2�㵽4��-----*/
	vtkSmartPointer<vtkPoints>point24 = vtkSmartPointer<vtkPoints>::New();
	point24->InsertPoint(0, Result3Dpoint[10].x, Result3Dpoint[10].y, Result3Dpoint[10].z);
	point24->InsertPoint(1, Result3Dpoint[16].x, Result3Dpoint[16].y, Result3Dpoint[16].z);
	point24->InsertPoint(2, Result3Dpoint[17].x, Result3Dpoint[17].y, Result3Dpoint[17].z);
	point24->InsertPoint(3, Result3Dpoint[18].x, Result3Dpoint[18].y, Result3Dpoint[18].z);
	point24->InsertPoint(4, Result3Dpoint[19].x, Result3Dpoint[19].y, Result3Dpoint[19].z);
	point24->InsertPoint(5, Result3Dpoint[20].x, Result3Dpoint[20].y, Result3Dpoint[20].z);


	vtkSmartPointer<vtkParametricSpline>spline24 = vtkSmartPointer<vtkParametricSpline>::New();
	spline24->SetPoints(point24);
	spline24->ClosedOff();

	vtkSmartPointer<vtkParametricFunctionSource>splineSource24 = vtkSmartPointer<vtkParametricFunctionSource>::New();
	splineSource24->SetParametricFunction(spline24);
	splineSource24->Update();

	vtkSmartPointer<vtkPolyDataMapper>splineMapper24 = vtkSmartPointer<vtkPolyDataMapper>::New();
	splineMapper24->SetInputConnection(splineSource24->GetOutputPort());

	vtkSmartPointer<vtkActor>splineActor24 = vtkSmartPointer<vtkActor>::New();
	splineActor24->SetMapper(splineMapper24);
	splineActor24->GetProperty()->SetColor(0.38, 0.7, 0.16);

	vtkSmartPointer<vtkTubeFilter>tube24 = vtkSmartPointer<vtkTubeFilter>::New();
	tube24->SetInputData(splineSource24->GetOutput());
	tube24->SetNumberOfSides(24);
	tube24->SetRadius(radius);
	tube24->Update();

	vtkSmartPointer<vtkPolyDataMapper>tubeMapper24 = vtkSmartPointer<vtkPolyDataMapper>::New();
	tubeMapper24->SetInputData(tube24->GetOutput());

	vtkSmartPointer<vtkActor>tubeActor24 = vtkSmartPointer<vtkActor>::New();
	tubeActor24->SetMapper(tubeMapper24);
	tubeActor24->GetProperty()->SetColor(1, 0, 0);

	/*-----���Ƶ����������ֵ�����Լ�Բ����ܵ�����4�㵽5��-----*/
	vtkSmartPointer<vtkPoints>point45 = vtkSmartPointer<vtkPoints>::New();
	point45->InsertPoint(0, Result3Dpoint[20].x, Result3Dpoint[20].y, Result3Dpoint[20].z);
	point45->InsertPoint(1, Result3Dpoint[21].x, Result3Dpoint[21].y, Result3Dpoint[21].z);
	point45->InsertPoint(2, Result3Dpoint[22].x, Result3Dpoint[22].y, Result3Dpoint[22].z);
	point45->InsertPoint(3, Result3Dpoint[23].x, Result3Dpoint[23].y, Result3Dpoint[23].z);
	point45->InsertPoint(4, Result3Dpoint[24].x, Result3Dpoint[24].y, Result3Dpoint[24].z);
	point45->InsertPoint(5, Result3Dpoint[25].x, Result3Dpoint[25].y, Result3Dpoint[25].z);


	vtkSmartPointer<vtkParametricSpline>spline45 = vtkSmartPointer<vtkParametricSpline>::New();
	spline45->SetPoints(point45);
	spline45->ClosedOff();


	vtkSmartPointer<vtkParametricFunctionSource>splineSource45 = vtkSmartPointer<vtkParametricFunctionSource>::New();
	splineSource45->SetParametricFunction(spline45);
	splineSource45->Update();

	vtkSmartPointer<vtkPolyDataMapper>splineMapper45 = vtkSmartPointer<vtkPolyDataMapper>::New();
	splineMapper45->SetInputConnection(splineSource45->GetOutputPort());

	vtkSmartPointer<vtkActor>splineActor45 = vtkSmartPointer<vtkActor>::New();
	splineActor45->SetMapper(splineMapper45);
	splineActor45->GetProperty()->SetColor(0.38, 0.7, 0.16);

	vtkSmartPointer<vtkTubeFilter>tube45 = vtkSmartPointer<vtkTubeFilter>::New();
	tube45->SetInputData(splineSource45->GetOutput());
	tube45->SetNumberOfSides(24);
	tube45->SetRadius(radius);
	tube45->Update();

	vtkSmartPointer<vtkPolyDataMapper>tubeMapper45 = vtkSmartPointer<vtkPolyDataMapper>::New();
	tubeMapper45->SetInputData(tube45->GetOutput());

	vtkSmartPointer<vtkActor>tubeActor45 = vtkSmartPointer<vtkActor>::New();
	tubeActor45->SetMapper(tubeMapper45);
	tubeActor45->GetProperty()->SetColor(1, 0, 0);

	/*-----���Ƶ�����������ֵ�����Լ�Բ����ܵ�����4�㵽6��-----*/
	vtkSmartPointer<vtkPoints>point46 = vtkSmartPointer<vtkPoints>::New();
	point46->InsertPoint(0, Result3Dpoint[20].x, Result3Dpoint[20].y, Result3Dpoint[20].z);
	point46->InsertPoint(1, Result3Dpoint[26].x, Result3Dpoint[26].y, Result3Dpoint[26].z);
	point46->InsertPoint(2, Result3Dpoint[27].x, Result3Dpoint[27].y, Result3Dpoint[27].z);
	point46->InsertPoint(3, Result3Dpoint[28].x, Result3Dpoint[28].y, Result3Dpoint[28].z);
	point46->InsertPoint(4, Result3Dpoint[29].x, Result3Dpoint[29].y, Result3Dpoint[29].z);


	vtkSmartPointer<vtkParametricSpline>spline46 = vtkSmartPointer<vtkParametricSpline>::New();
	spline46->SetPoints(point46);
	spline46->ClosedOff();

	vtkSmartPointer<vtkParametricFunctionSource>splineSource46 = vtkSmartPointer<vtkParametricFunctionSource>::New();
	splineSource46->SetParametricFunction(spline46);

	vtkSmartPointer<vtkPolyDataMapper>splineMapper46 = vtkSmartPointer<vtkPolyDataMapper>::New();
	splineMapper46->SetInputConnection(splineSource46->GetOutputPort());

	vtkSmartPointer<vtkActor>splineActor46 = vtkSmartPointer<vtkActor>::New();
	splineActor46->SetMapper(splineMapper46);
	splineActor46->GetProperty()->SetColor(0.38, 0.7, 0.16);

	vtkSmartPointer<vtkTubeFilter>tube46 = vtkSmartPointer<vtkTubeFilter>::New();
	tube46->SetInputData(splineSource46->GetOutput());
	tube46->SetNumberOfSides(24);
	tube46->SetRadius(radius);
	tube46->Update();

	vtkSmartPointer<vtkPolyDataMapper>tubeMapper46 = vtkSmartPointer<vtkPolyDataMapper>::New();
	tubeMapper46->SetInputData(tube46->GetOutput());

	vtkSmartPointer<vtkActor>tubeActor46 = vtkSmartPointer<vtkActor>::New();
	tubeActor46->SetMapper(tubeMapper46);
	tubeActor46->GetProperty()->SetColor(1, 0, 0);

	/*-----���Ƶ��߶�������ֵ�����Լ�Բ����ܵ�����1�㵽7��-----*/
	vtkSmartPointer<vtkPoints>point17 = vtkSmartPointer<vtkPoints>::New();
	point17->InsertPoint(0, Result3Dpoint[4].x, Result3Dpoint[4].y, Result3Dpoint[4].z);
	point17->InsertPoint(1, Result3Dpoint[31].x, Result3Dpoint[31].y, Result3Dpoint[31].z);
	point17->InsertPoint(2, Result3Dpoint[32].x, Result3Dpoint[32].y, Result3Dpoint[32].z);
	point17->InsertPoint(3, Result3Dpoint[33].x, Result3Dpoint[33].y, Result3Dpoint[33].z);
	point17->InsertPoint(4, Result3Dpoint[34].x, Result3Dpoint[34].y, Result3Dpoint[34].z);
	point17->InsertPoint(4, Result3Dpoint[35].x, Result3Dpoint[35].y, Result3Dpoint[35].z);
	point17->InsertPoint(4, Result3Dpoint[36].x, Result3Dpoint[36].y, Result3Dpoint[36].z);
	point17->InsertPoint(4, Result3Dpoint[37].x, Result3Dpoint[37].y, Result3Dpoint[37].z);
	point17->InsertPoint(4, Result3Dpoint[38].x, Result3Dpoint[38].y, Result3Dpoint[38].z);



	vtkSmartPointer<vtkParametricSpline>spline17 = vtkSmartPointer<vtkParametricSpline>::New();
	spline17->SetPoints(point17);
	spline17->ClosedOff();

	vtkSmartPointer<vtkParametricFunctionSource>splineSource17 = vtkSmartPointer<vtkParametricFunctionSource>::New();
	splineSource17->SetParametricFunction(spline17);
	splineSource17->Update();

	vtkSmartPointer<vtkPolyDataMapper>splineMapper17 = vtkSmartPointer<vtkPolyDataMapper>::New();
	splineMapper17->SetInputConnection(splineSource17->GetOutputPort());

	vtkSmartPointer<vtkActor>splineActor17 = vtkSmartPointer<vtkActor>::New();
	splineActor17->SetMapper(splineMapper17);
	splineActor17->GetProperty()->SetColor(0.38, 0.7, 0.16);

	vtkSmartPointer<vtkTubeFilter>tube17 = vtkSmartPointer<vtkTubeFilter>::New();
	tube17->SetInputData(splineSource17->GetOutput());
	tube17->SetNumberOfSides(17);
	tube17->SetRadius(radius);
	tube17->Update();

	vtkSmartPointer<vtkPolyDataMapper>tubeMapper17 = vtkSmartPointer<vtkPolyDataMapper>::New();
	tubeMapper17->SetInputData(tube17->GetOutput());

	vtkSmartPointer<vtkActor>tubeActor17 = vtkSmartPointer<vtkActor>::New();
	tubeActor17->SetMapper(tubeMapper17);
	tubeActor17->GetProperty()->SetColor(1, 0, 0);

	/*-----���Ƶڰ˶�������ֵ�����Լ�Բ����ܵ�����7�㵽8��-----*/
	vtkSmartPointer<vtkPoints>point78 = vtkSmartPointer<vtkPoints>::New();
	point78->InsertPoint(0, Result3Dpoint[38].x, Result3Dpoint[38].y, Result3Dpoint[38].z);
	point78->InsertPoint(1, Result3Dpoint[39].x, Result3Dpoint[39].y, Result3Dpoint[39].z);
	point78->InsertPoint(2, Result3Dpoint[40].x, Result3Dpoint[40].y, Result3Dpoint[40].z);
	point78->InsertPoint(3, Result3Dpoint[41].x, Result3Dpoint[41].y, Result3Dpoint[41].z);
	point78->InsertPoint(4, Result3Dpoint[42].x, Result3Dpoint[42].y, Result3Dpoint[42].z);
	point78->InsertPoint(4, Result3Dpoint[43].x, Result3Dpoint[43].y, Result3Dpoint[43].z);


	vtkSmartPointer<vtkParametricSpline>spline78 = vtkSmartPointer<vtkParametricSpline>::New();
	spline78->SetPoints(point78);
	spline78->ClosedOff();


	vtkSmartPointer<vtkParametricFunctionSource>splineSource78 = vtkSmartPointer<vtkParametricFunctionSource>::New();
	splineSource78->SetParametricFunction(spline78);
	splineSource78->Update();

	vtkSmartPointer<vtkPolyDataMapper>splineMapper78 = vtkSmartPointer<vtkPolyDataMapper>::New();
	splineMapper78->SetInputConnection(splineSource78->GetOutputPort());

	vtkSmartPointer<vtkActor>splineActor78 = vtkSmartPointer<vtkActor>::New();
	splineActor78->SetMapper(splineMapper78);
	splineActor78->GetProperty()->SetColor(0.38, 0.7, 0.16);

	vtkSmartPointer<vtkTubeFilter>tube78 = vtkSmartPointer<vtkTubeFilter>::New();
	tube78->SetInputData(splineSource78->GetOutput());
	tube78->SetNumberOfSides(24);
	tube78->SetRadius(radius);
	tube78->Update();

	vtkSmartPointer<vtkPolyDataMapper>tubeMapper78 = vtkSmartPointer<vtkPolyDataMapper>::New();
	tubeMapper78->SetInputData(tube78->GetOutput());

	vtkSmartPointer<vtkActor>tubeActor78 = vtkSmartPointer<vtkActor>::New();
	tubeActor78->SetMapper(tubeMapper78);
	tubeActor78->GetProperty()->SetColor(1, 0, 0);

	/*-----���ƵھŶ�������ֵ�����Լ�Բ����ܵ�����7�㵽9��-----*/
	vtkSmartPointer<vtkPoints>point79 = vtkSmartPointer<vtkPoints>::New();
	point79->InsertPoint(0, Result3Dpoint[38].x, Result3Dpoint[38].y, Result3Dpoint[38].z);
	point79->InsertPoint(1, Result3Dpoint[44].x, Result3Dpoint[44].y, Result3Dpoint[44].z);
	point79->InsertPoint(2, Result3Dpoint[45].x, Result3Dpoint[45].y, Result3Dpoint[45].z);
	point79->InsertPoint(3, Result3Dpoint[46].x, Result3Dpoint[46].y, Result3Dpoint[46].z);
	point79->InsertPoint(4, Result3Dpoint[47].x, Result3Dpoint[47].y, Result3Dpoint[47].z);
	point79->InsertPoint(4, Result3Dpoint[48].x, Result3Dpoint[48].y, Result3Dpoint[48].z);


	vtkSmartPointer<vtkParametricSpline>spline79 = vtkSmartPointer<vtkParametricSpline>::New();
	spline79->SetPoints(point79);
	spline79->ClosedOff();

	vtkSmartPointer<vtkParametricFunctionSource>splineSource79 = vtkSmartPointer<vtkParametricFunctionSource>::New();
	splineSource79->SetParametricFunction(spline79);

	vtkSmartPointer<vtkPolyDataMapper>splineMapper79 = vtkSmartPointer<vtkPolyDataMapper>::New();
	splineMapper79->SetInputConnection(splineSource79->GetOutputPort());

	vtkSmartPointer<vtkActor>splineActor79 = vtkSmartPointer<vtkActor>::New();
	splineActor79->SetMapper(splineMapper79);
	splineActor79->GetProperty()->SetColor(0.38, 0.7, 0.16);

	vtkSmartPointer<vtkTubeFilter>tube79 = vtkSmartPointer<vtkTubeFilter>::New();
	tube79->SetInputData(splineSource79->GetOutput());
	tube79->SetNumberOfSides(24);
	tube79->SetRadius(radius);

	vtkSmartPointer<vtkPolyDataMapper>tubeMapper79 = vtkSmartPointer<vtkPolyDataMapper>::New();
	tubeMapper79->SetInputData(tube79->GetOutput());

	vtkSmartPointer<vtkActor>tubeActor79 = vtkSmartPointer<vtkActor>::New();
	tubeActor79->SetMapper(tubeMapper79);
	tubeActor79->GetProperty()->SetColor(1, 0, 0);


	/*-----���Ƶ�ʮ��������ֵ�����Լ�Բ����ܵ�����9�㵽10��-----*/
	vtkSmartPointer<vtkPoints>point910 = vtkSmartPointer<vtkPoints>::New();
	point910->InsertPoint(0, Result3Dpoint[48].x, Result3Dpoint[48].y, Result3Dpoint[48].z);
	point910->InsertPoint(1, Result3Dpoint[49].x, Result3Dpoint[49].y, Result3Dpoint[49].z);
	point910->InsertPoint(2, Result3Dpoint[50].x, Result3Dpoint[50].y, Result3Dpoint[50].z);
	point910->InsertPoint(3, Result3Dpoint[51].x, Result3Dpoint[51].y, Result3Dpoint[51].z);


	vtkSmartPointer<vtkParametricSpline>spline910 = vtkSmartPointer<vtkParametricSpline>::New();
	spline910->SetPoints(point910);
	spline910->ClosedOff();

	vtkSmartPointer<vtkParametricFunctionSource>splineSource910 = vtkSmartPointer<vtkParametricFunctionSource>::New();
	splineSource910->SetParametricFunction(spline910);

	vtkSmartPointer<vtkPolyDataMapper>splineMapper910 = vtkSmartPointer<vtkPolyDataMapper>::New();
	splineMapper910->SetInputConnection(splineSource910->GetOutputPort());

	vtkSmartPointer<vtkActor>splineActor910 = vtkSmartPointer<vtkActor>::New();
	splineActor910->SetMapper(splineMapper910);
	splineActor910->GetProperty()->SetColor(0.38, 0.7, 0.16);

	vtkSmartPointer<vtkTubeFilter>tube910 = vtkSmartPointer<vtkTubeFilter>::New();
	tube910->SetInputData(splineSource910->GetOutput());
	tube910->SetNumberOfSides(24);
	tube910->SetRadius(radius);

	vtkSmartPointer<vtkPolyDataMapper>tubeMapper910 = vtkSmartPointer<vtkPolyDataMapper>::New();
	tubeMapper910->SetInputData(tube910->GetOutput());

	vtkSmartPointer<vtkActor>tubeActor910 = vtkSmartPointer<vtkActor>::New();
	tubeActor910->SetMapper(tubeMapper910);
	tubeActor910->GetProperty()->SetColor(1, 0, 0);



	/*-----���Ƶ�ʮһ��������ֵ�����Լ�Բ����ܵ�����10�㵽11��-----*/
	vtkSmartPointer<vtkPoints>point1011 = vtkSmartPointer<vtkPoints>::New();
	point1011->InsertPoint(0, Result3Dpoint[48].x, Result3Dpoint[48].y, Result3Dpoint[48].z);
	point1011->InsertPoint(1, Result3Dpoint[52].x, Result3Dpoint[52].y, Result3Dpoint[52].z);
	point1011->InsertPoint(2, Result3Dpoint[53].x, Result3Dpoint[53].y, Result3Dpoint[53].z);
	point1011->InsertPoint(3, Result3Dpoint[54].x, Result3Dpoint[54].y, Result3Dpoint[54].z);
	point1011->InsertPoint(3, Result3Dpoint[55].x, Result3Dpoint[55].y, Result3Dpoint[55].z);

	vtkSmartPointer<vtkParametricSpline>spline1011 = vtkSmartPointer<vtkParametricSpline>::New();
	spline1011->SetPoints(point1011);
	spline1011->ClosedOff();

	vtkSmartPointer<vtkParametricFunctionSource>splineSource1011 = vtkSmartPointer<vtkParametricFunctionSource>::New();
	splineSource1011->SetParametricFunction(spline1011);

	vtkSmartPointer<vtkPolyDataMapper>splineMapper1011 = vtkSmartPointer<vtkPolyDataMapper>::New();
	splineMapper1011->SetInputConnection(splineSource1011->GetOutputPort());

	vtkSmartPointer<vtkActor>splineActor1011 = vtkSmartPointer<vtkActor>::New();
	splineActor1011->SetMapper(splineMapper1011);
	splineActor1011->GetProperty()->SetColor(0.38, 0.7, 0.16);

	vtkSmartPointer<vtkTubeFilter>tube1011 = vtkSmartPointer<vtkTubeFilter>::New();
	tube1011->SetInputData(splineSource1011->GetOutput());
	tube1011->SetNumberOfSides(24);
	tube1011->SetRadius(radius);

	vtkSmartPointer<vtkPolyDataMapper>tubeMapper1011 = vtkSmartPointer<vtkPolyDataMapper>::New();
	tubeMapper1011->SetInputData(tube1011->GetOutput());

	vtkSmartPointer<vtkActor>tubeActor1011 = vtkSmartPointer<vtkActor>::New();
	tubeActor1011->SetMapper(tubeMapper1011);
	tubeActor1011->GetProperty()->SetColor(1, 0, 0);


	/*-----����Ϊvtkͳһ�Ļ����������ƴ������ÿһ�����������Լ�Բ����ܵ���Actor-----*/
	vtkSmartPointer<vtkRenderer>ren1 = vtkSmartPointer<vtkRenderer>::New();
	vtkSmartPointer<vtkRenderWindow>renWin = vtkSmartPointer<vtkRenderWindow>::New();
	renWin->AddRenderer(ren1);
	vtkSmartPointer<vtkRenderWindowInteractor>iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	iren->SetRenderWindow(renWin);
	ren1->SetBackground(1, 1, 1);//���û��ƴ��ڱ���

	//��ӵ�1�����������Լ�Բ����ܵ���Actor
	ren1->AddActor(splineActor01);
	ren1->AddActor(tubeActor01);
	//��ӵ�2�����������Լ�Բ����ܵ���Actor
	ren1->AddActor(splineActor12);
	ren1->AddActor(tubeActor12);
	//��ӵ�3�����������Լ�Բ����ܵ���Actor
	ren1->AddActor(splineActor23);
	ren1->AddActor(tubeActor23);
	//��ӵ�4�����������Լ�Բ����ܵ���Actor
	ren1->AddActor(splineActor24);
	ren1->AddActor(tubeActor24);
	//��ӵ�5�����������Լ�Բ����ܵ���Actor
	ren1->AddActor(splineActor45);
	ren1->AddActor(tubeActor45);
	//��ӵ�6�����������Լ�Բ����ܵ���Actor
	ren1->AddActor(splineActor46);
	ren1->AddActor(tubeActor46);
	//��ӵ�7�����������Լ�Բ����ܵ���Actor
	ren1->AddActor(splineActor17);
	ren1->AddActor(tubeActor17);
	//��ӵ�8�����������Լ�Բ����ܵ���Actor
	ren1->AddActor(splineActor78);
	ren1->AddActor(tubeActor78);
	//��ӵ�9�����������Լ�Բ����ܵ���Actor
	ren1->AddActor(splineActor79);
	ren1->AddActor(tubeActor79);
	//��ӵ�10�����������Լ�Բ����ܵ���Actor
	ren1->AddActor(splineActor910);
	ren1->AddActor(tubeActor910);
	//��ӵ�11�����������Լ�Բ����ܵ���Actor
	ren1->AddActor(splineActor1011);
	ren1->AddActor(tubeActor1011);

	renWin->SetSize(500, 500);//���ô��ڴ�С

	renWin->Render();//����
	iren->Start();//����������

}