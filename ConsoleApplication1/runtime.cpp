#include<vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2); // VTK was built with vtkRenderingOpenGL
//VTK_MODULE_INIT(vtkRenderingVolumeOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingFreeType);
//VTK_MODULE_INIT(vtkRenderingVolumeOpenGL)



#include <CellPickerInteractorStyle.h>
#include<pickTriangelGridOnSphere.h>
#include<pickPointToChangeAbleLine.h>
#include<vtkImageTracerWidgetOn3D.h>
#include<PointPickerInteractorStyle1.h>
#include<MouseInteractorStyle.h>
#include<PointPickerInteractorStyle.h>
#include<vtkImageTracerWidgetOn2dCanvas.h>
#include<wordpresent.h>
#include<angleWidget.h>
#include<distancewidget.h>
#include<anglewidgetsimple.h>
#include<BiDimensionalWidget.h>
#include<icppointmatch.h>
#include<somemacro.h>
#include<surfacereconstruct.h>
#include <FigureTraversal.h>
#include<addObserverInWindowInteractor.h>
#include<surfaceReconstructDelaunay2d.h>
#include<dijsearch.h>
#include<figureFourierTransformAndFilter.h>
#include<basedatainvtk.h>
#include<stscalar.h>
#include<cplusrule.h>
#include<vtktest.h>
#include <tubereconstuction.h>
#include<reconstructVesselTroughTubeFilter.h>
#include<marchcubeandreconstruct.h>
#include <readMultiPictiure.h>
#include<maptest.h>
#include<factory_test.h>
#include<readimagedataandreconstruct.h>


int main()
{
	//pickPointToChangeAbleLine(); // 非常重要 在球上画几条先然后自动把线闭合，获取小插件的表示，然后在表示中插入一个点放置器
 //vtkImageTracerWidgetOn3D();
	//plotOn3d();
	//plotOnPicture();
 //pickTriangelGridOnSphere(); //重要 选取球上的三角面
	//vtktest();
	//pickTriangelGridOnSphereByMstyle(); //选取球上的点，然后高亮显示出来
	//pickpointGridOnSphere(); //把点到的坐标显示出来
	//plotlineon2dcanvas(); // 在2d的canvas上绘制线条并显示线条的位置，这个在vtk9中是可以的
	//wordpresent(); // 就是一个显示文字的widget
	//angelwidget();
	//distancewidgetexample();
	//readimageanddrawline();
    //anglewidgetexample();
	// 
	
	// 看到这里了
	//BiDimensionalWidgetexample();// 两个维度测量图片距离同时注册了一个回调函数去显示具体的值
	//icppointmatcg();// icp实现配准，有很多基础知识没有掌握
	//macrotest();
	//surfaceReconstruction(); //通过点云进行重建
	//addObserverInWindowInteractor();
	//FigureTraversal();
	//surfaceReconstructDelaunay2d();
	//tubereconstruction();

	//dijsearch();
	//figureFourierTransformAndFilter();//实现一版快速傅里叶变换
	//basedatainvtk(); //vtk中的基础数据结构
	//plotVesselbuTubeFilter();
	//setscalar(); //基础的数据结构，需要重点理解
	//scalaronfigure();
	//create2drectange();
	//createasphere();
	//plotacircle();	
	//getcurentpath();
	//getcurentpath_method1();
	//plottrianglesingleton();
	//setexture();
	//readstlfile();
	//readjpeg();
	//readFullHeadDataAndShow();//使用marchcube进行体绘制mpr
	//readtxtandplotpoint();
	readimagedataandreconstruct();
	factory_test();
	std::string s = "add";
	maptest(s);
	use_template();
	sort_values();	
	random_number_generate();
	return 0;
}





// VTK headers
#include "vtkVolume16Reader.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkMarchingCubes.h"
#include "vtkStripper.h"
#include "vtkActor.h"
#include "vtkPolyDataMapper.h"
#include "vtkProperty.h"
#include "vtkCamera.h"
//#include "vtkBoxWidget.h"

#include <iostream>

//int main() 
//{
//
//
////抽取等值面为骨头的信息
//vtkMarchingCubes *boneExtractor = vtkMarchingCubes::New();
//boneExtractor->SetInputConnection(reader->GetOutputPort()); // 提取的是vtkimagedata
//boneExtractor->SetValue(0,500); //设置提取的等值信息
//
////剔除旧的或废除的数据单元，提高绘制速度
//vtkStripper *boneStripper = vtkStripper::New(); //三角带连接
//
//
//
////建立映射
//vtkPolyDataMapper *boneMapper = vtkPolyDataMapper::New();
////注意：vtk6.0以后的版本，管道的连接函数修改为了SetInputConnection()和GetOutputPort().
//boneMapper->SetInputConnection(boneStripper->GetOutputPort());
//
////建立角色
//vtkActor *bone = vtkActor::New();
//bone->SetMapper(boneMapper);
//
//bone->GetProperty()->SetDiffuseColor(.1,.94,.52);
//bone->GetProperty()->SetSpecular(.3);
//bone->GetProperty()->SetSpecularPower(20);
//
////标准句子
////定义绘制器
//vtkRenderer *aRenderer = vtkRenderer::New();
////定义绘制窗口
//vtkRenderWindow *renWin = vtkRenderWindow::New();
//renWin->AddRenderer(aRenderer);
////定义窗口交互器
//vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
//iren->SetRenderWindow(renWin);
//
//
//aRenderer->AddActor(bone);
//
//aRenderer->ResetCamera();
//
//aRenderer->SetBackground(0,0,0);
//aRenderer->ResetCameraClippingRange();
//
///*
//vtkBoxWidget *boxWidget = vtkBoxWidget::New();
//boxWidget->SetInteractor(iren);
//boxWidget->SetPlaceFactor(1.25);
//
//boxWidget->SetProp3D(bone);
//boxWidget->PlaceWidget();
//*/
//
//iren->Initialize();
//iren->Start();
//reader->Delete();
//iren->Delete();
//return 0;
//}
//





//int main()
//{
//
//	//标准句子
//	//定义绘制器
//	vtkRenderer* aRenderer = vtkRenderer::New();
//	//定义绘制窗口
//	vtkRenderWindow* renWin = vtkRenderWindow::New();
//	renWin->AddRenderer(aRenderer);
//	//定义窗口交互器
//	vtkRenderWindowInteractor* iren = vtkRenderWindowInteractor::New();
//	iren->SetRenderWindow(renWin);
//
//	//CT格式数据读取类
//	vtkDICOMImageReader* reader = vtkDICOMImageReader::New();
//	//这里输入Dicom数据的文件夹的路径，读者需要根据数据在本机上的位置进行修改。
//	reader->SetDirectoryName("D:\\TestData\\Brain");
//
//	//图像数据预处理。常见两种操作。一种是类型转换，通过 vtkImageShiftScale 将不同类型的数据集转换为 VTK 可以处理的数据；
//	//另一种是剔除冗余数据，通过 vtkStripper 放置无效的旧单元的存在，提高绘制速度。
//	vtkImageShiftScale* shiftScale = vtkImageShiftScale::New();
//	shiftScale->SetInputConnection(reader->GetOutputPort());
//	shiftScale->SetOutputScalarTypeToUnsignedChar();
//
//	//数据分类，找出数据与不同物质之间的对应关系，同时也为了在最终图像中以不同颜色表示单一物质的不同属性。
//	//此处省略
//	//………………
//
//	//透明度映射函数定义
//	//给数据点赋不透明值。体绘制中，需要显示三维数据场的内部结构，因而需要生成具有透明度的图像。
//	vtkPiecewiseFunction* opacityTransferFunction = vtkPiecewiseFunction::New();
//	opacityTransferFunction->AddPoint(20, 0.0);
//	opacityTransferFunction->AddPoint(255, 0.2);
//
//	//颜色映射函数定义
//	//给数据点赋颜色值，将分类后的组织信息分别予以不同的颜色，便于图像分析。
//	vtkColorTransferFunction* colorTransferFunction = vtkColorTransferFunction::New();
//	colorTransferFunction->AddRGBPoint(0.0, 0.0, 0.0, 0.0);
//	colorTransferFunction->AddRGBPoint(64.0, 1.0, 0.0, 0.0);
//	colorTransferFunction->AddRGBPoint(128.0, 0.0, 0.0, 1.0);
//	colorTransferFunction->AddRGBPoint(192.0, 0.0, 1.0, 0.0);
//	colorTransferFunction->AddRGBPoint(255.0, 0.0, 0.2, 0.0);
//
//	//体数据属性
//	vtkVolumeProperty* volumeProperty = vtkVolumeProperty::New();
//	volumeProperty->SetColor(colorTransferFunction);
//	volumeProperty->SetScalarOpacity(opacityTransferFunction);
//	volumeProperty->ShadeOn();
//	volumeProperty->SetInterpolationTypeToLinear();
//
//
//	//体绘制惯用语句：
//	//计算光照效应。采用光线类 vtkVolumeRayCastCompositeFunction 进行投射，
//	//最终用 vtkVolumeRayCastMapper类进行光效应计算。
//	vtkVolumeRayCastCompositeFunction* compositeFunction = vtkVolumeRayCastCompositeFunction::New();
//	vtkVolumeRayCastMapper* volumeMapper = vtkVolumeRayCastMapper::New();
//	volumeMapper->SetVolumeRayCastFunction(compositeFunction);
//	volumeMapper->SetInput(shiftScale->GetOutput());
//
//	vtkVolume* volume = vtkVolume::New();
//	volume->SetMapper(volumeMapper);
//	volume->SetProperty(volumeProperty);
//
//	aRenderer->AddVolume(volume);
//	aRenderer->SetBackground(1, 1, 1);
//	renWin->SetSize(600, 600);
//	renWin->Render();
//
//	iren->Initialize();
//	iren->Start();
//	return 0;
//}


//int main(int argc, char* argv[])
//{
//    vtkSmartPointer<vtkNamedColors> colors = vtkSmartPointer<vtkNamedColors>::New();
//
//    vtkSmartPointer<vtkImageData> volume = vtkSmartPointer<vtkImageData>::New();
//    double isoValue;
//    if (argc < 3)
//    {
//        vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
//        sphereSource->SetPhiResolution(20);
//        sphereSource->SetThetaResolution(20);
//        sphereSource->Update();
//
//        double bounds[6];
//        sphereSource->GetOutput()->GetBounds(bounds);
//        for (unsigned int i = 0; i < 6; i += 2)
//        {
//            double range = bounds[i + 1] - bounds[i];
//            bounds[i] = bounds[i] - 0.1 * range;
//            bounds[i + 1] = bounds[i + 1] + 0.1 * range;
//        }
//        vtkSmartPointer<vtkVoxelModeller> voxelModeller = vtkSmartPointer<vtkVoxelModeller>::New();
//        voxelModeller->SetSampleDimensions(50, 50, 50);
//        voxelModeller->SetModelBounds(bounds);
//        voxelModeller->SetScalarTypeToFloat();
//        voxelModeller->SetMaximumDistance(0.1);
//
//        voxelModeller->SetInputConnection(sphereSource->GetOutputPort());
//        voxelModeller->Update();
//        isoValue = 0.5;
//        volume->DeepCopy(voxelModeller->GetOutput());
//    }
//    else
//    {
//        vtkSmartPointer<vtkDICOMImageReader> reader = vtkSmartPointer<vtkDICOMImageReader>::New();
//        reader->SetDirectoryName(argv[1]);
//        reader->Update();
//        volume->DeepCopy(reader->GetOutput());
//        isoValue = atof(argv[2]);
//    }
//
//#ifdef USE_FLYING_EDGES
//    vtkSmartPointer<vtkFlyingEdges3D> surface;
//#else
//    vtkSmartPointer<vtkMarchingCubes> surface = vtkSmartPointer<vtkMarchingCubes>::New();
//#endif
//    surface->SetInputData(volume);
//    surface->ComputeNormalsOn();
//    surface->SetValue(0, isoValue);
//
//    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
// /*   renderer->SetBackground(colors->GetColor3d("DarkSlateGray").GetData());*/
//
//    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
//    renderWindow->AddRenderer(renderer);
//    renderWindow->SetWindowName("MarchingCubes");
//
//    vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
//    interactor->SetRenderWindow(renderWindow);
//
//    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
//    mapper->SetInputConnection(surface->GetOutputPort());
//    mapper->ScalarVisibilityOff();
//
//    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
//    actor->SetMapper(mapper);
//    //actor->GetProperty()->SetColor(colors->GetColor3d("MistyRose").GetData());
//
//    renderer->AddActor(actor);
//
//    renderWindow->Render();
//    interactor->Start();
//
//    return EXIT_SUCCESS;
//}