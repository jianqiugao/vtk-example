#include<marchcubeandreconstruct.h>

int readFullHeadDataAndShow()
{

	// Create the renderer, the render window, and the interactor. The renderer draws into the render window, the interactor enables 
	// mouse- and keyboard-based interaction with the data within the render window.

	//// Set a background color for the renderer and set the size of the
	//// render window (expressed in pixels).

	renderPipeLine();

	// The following reader is used to read a series of 2D slices (images)
	// that compose the volume. The slice dimensions are set, and the
	// pixel spacing. The data Endianness must also be specified. The
	// reader uses the FilePrefix in combination with the slice number to
	// construct filenames using the format FilePrefix.%d. (In this case
	// the FilePrefix is the root name of the file: quarter.)
	vtkSmartPointer<vtkMetaImageReader> reader = vtkSmartPointer<vtkMetaImageReader>::New();
	reader->SetFileName("C:\\gitlab\\vs\\ctest\\ctest\\vtk\\7.1data\\FullHead.mhd");
	reader->Update();

	vtkSmartPointer<vtkMetaImageReader> newreader = vtkSmartPointer<vtkMetaImageReader>::New();
	newreader->SetFileName("C:\\gitlab\\vs\\ctest\\ctest\\vtk\\7.2data\\FullHead.mhd");
	newreader->UpdateWholeExtent();
	newreader->Modified();
	newreader->Update();

	vtkSmartPointer<vtkDataSetMapper> imgaemapper = vtkSmartPointer<vtkDataSetMapper>::New();
	vtkSmartPointer<vtkImageData> data = vtkSmartPointer<vtkImageData>::New();
	data = newreader->GetOutput();
	int extent[6];
	//data->GetExtent(extent);
	double* res = newreader->GetOutput()->GetBounds();
	cout << res[0] << ":" << res[1] << endl; // 也就是0-239.06啊
	res = NULL;
	//cout << extent[0] << ":" << extent[1] << extent[2] << ":" << extent[3]<<":" << extent[4] << ":" << extent[5] << endl;
	imgaemapper->SetInputData(data);
	vtkSmartPointer<vtkActor> imageactor = vtkSmartPointer<vtkActor>::New();
	imageactor->SetMapper(imgaemapper);

	// An isosurface, or contour value of 500 is known to correspond to the skin of the patient.
	// The triangle stripper is used to create triangle
	// strips from the isosurface; these render much faster on may systems.

#ifdef USE_FLYING_EDGES
	vtkSmartPointer<vtkFlyingEdges3D> skinExtractor = vtkSmartPointer<vtkFlyingEdges3D>::New();
#else
	vtkSmartPointer<vtkMarchingCubes> skinExtractor = vtkSmartPointer<vtkMarchingCubes>::New();
#endif
	skinExtractor->SetInputConnection(reader->GetOutputPort()); //vtkAlgorithmOutput,连接的是vtkimagedata
	cout << "NumberOfContours" << skinExtractor->GetNumberOfContours() << endl;

	skinExtractor->SetValue(0, 500);
	skinExtractor->Update();

	vtkSmartPointer<vtkStripper> skinStripper = vtkSmartPointer<vtkStripper>::New(); // vtkStripper:用于优化网格数据,提高渲染速度
	skinStripper->SetInputConnection(skinExtractor->GetOutputPort());
	skinStripper->Update();

	vtkSmartPointer<vtkPolyDataMapper> skinMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	skinMapper->SetInputConnection(skinStripper->GetOutputPort());
	skinMapper->ScalarVisibilityOff();

	vtkSmartPointer<vtkActor> skin = vtkSmartPointer<vtkActor>::New();
	skin->SetMapper(skinMapper);
	skin->GetProperty()->SetDiffuseColor(0, 0, 1);
	skin->GetProperty()->SetSpecular(0.3);
	skin->GetProperty()->SetSpecularPower(20);

	// An isosurface, or contour value of 1150 is known to correspond to the bone of the patient.
	// The triangle stripper is used to create triangle trips from the isosurface; these render much faster on may systems.
#ifdef USE_FLYING_EDGES
	vtkSmartPointer<vtkFlyingEdges3D> boneExtractor = vtkSmartPointer<vtkFlyingEdges3D>::New();
#else
	vtkSmartPointer<vtkMarchingCubes> boneExtractor = vtkSmartPointer<vtkMarchingCubes>::New();
#endif
	boneExtractor->SetInputConnection(reader->GetOutputPort());//这个是基类中的方法并没有什么影响
	boneExtractor->ComputeNormalsOn();
	cout << "图片点" << reader->GetOutput()->GetDataDimension() << endl;
	double* ptr = (double*)(reader->GetOutput()->GetScalarPointer(0, 0, 0));

	cout << *ptr << ":" << *(ptr + 1) << ":" << *(ptr + 2) << endl;

	boneExtractor->SetValue(0, 1300); // 和前面唯一的不同就是这个值的大小
	boneExtractor->SetValue(1, 500); // 和前面唯一的不同就是这个值的大小

	boneExtractor->Update();

	vtkSmartPointer<vtkStripper> boneStripper = vtkSmartPointer<vtkStripper>::New();
	boneStripper->SetInputConnection(boneExtractor->GetOutputPort());
	//boneStripper->SetInputData(boneExtractor->GetOutput());
	boneStripper->Update();


	vtkSmartPointer<vtkPolyData> points = vtkSmartPointer<vtkPolyData>::New();

	points->SetPoints(boneExtractor->GetOutput()->GetPoints());

	cout << "num_points" << boneStripper->GetOutput()->GetNumberOfPoints() << endl;


	vtkSmartPointer<vtkVertexGlyphFilter> pointsfilter = vtkSmartPointer<vtkVertexGlyphFilter>::New();
	pointsfilter->SetInputData(points);

	pointsfilter->Update();

	vtkSmartPointer<vtkPolyDataMapper> polymapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	polymapper->SetInputData(pointsfilter->GetOutput());

	vtkSmartPointer<vtkActor> polyactor = vtkSmartPointer<vtkActor>::New();
	polyactor->SetMapper(polymapper);




	vtkSmartPointer<vtkPolyDataMapper> boneMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	boneMapper->SetInputConnection(boneStripper->GetOutputPort());
	boneMapper->ScalarVisibilityOff();

	vtkSmartPointer<vtkActor> bone = vtkSmartPointer<vtkActor>::New();
	bone->SetMapper(boneMapper);
	bone->GetProperty()->SetDiffuseColor(1, 0, 0);

	// An outline provides context around the data.
	//
	vtkSmartPointer<vtkOutlineFilter> outlineData = vtkSmartPointer<vtkOutlineFilter>::New();
	outlineData->SetInputConnection(reader->GetOutputPort());
	outlineData->Update();

	vtkSmartPointer<vtkPolyDataMapper> mapOutline = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapOutline->SetInputConnection(outlineData->GetOutputPort());

	vtkSmartPointer<vtkActor> outline = vtkSmartPointer<vtkActor>::New();
	outline->SetMapper(mapOutline);
	outline->GetProperty()->SetColor(0, 1, 0);

	// Now we are creating three orthogonal planes passing through the
	// volume. Each plane uses a different texture map and therefore has
	// different coloration.

	// Start by creating a black/white lookup table.
	vtkSmartPointer<vtkLookupTable> bwLut = vtkSmartPointer<vtkLookupTable>::New();
	bwLut->SetTableRange(0, 2000);
	bwLut->SetSaturationRange(0, 0);
	bwLut->SetHueRange(0, 0);
	bwLut->SetValueRange(0, 1);
	bwLut->Build(); // effective built

	// Now create a lookup table that consists of the full hue circle
	// (from HSV).
	vtkSmartPointer<vtkLookupTable> hueLut = vtkSmartPointer<vtkLookupTable>::New();
	hueLut->SetTableRange(0, 2000);
	hueLut->SetHueRange(0, 1);
	hueLut->SetSaturationRange(1, 1);
	hueLut->SetValueRange(1, 1);
	hueLut->Build(); // effective built

	// Finally, create a lookup table with a single hue but having a range
	// in the saturation of the hue.
	vtkSmartPointer<vtkLookupTable> satLut = vtkSmartPointer<vtkLookupTable>::New();
	satLut->SetTableRange(0, 2000);
	satLut->SetHueRange(0.6, 0.6);
	satLut->SetSaturationRange(0, 1);
	satLut->SetValueRange(1, 1);
	satLut->Build(); // effective built

	// Create the first of the three planes. The filter vtkImageMapToColors maps the data through the corresponding lookup table created above. The 
	// vtkImageActor is a type of vtkProp and conveniently displays an image on
	// a single quadrilateral plane. It does this using texture mapping and as
	// a result is quite fast. (Note: the input image has to be unsigned char
	// values, which the vtkImageMapToColors produces.) Note also that by
	// specifying the DisplayExtent, the pipeline requests data of this extent
	// and the vtkImageMapToColors only processes a slice of data.
	vtkSmartPointer<vtkImageMapToColors> sagittalColors = vtkSmartPointer<vtkImageMapToColors>::New();
	sagittalColors->SetInputConnection(reader->GetOutputPort());
	sagittalColors->SetLookupTable(bwLut);
	sagittalColors->Update();

	vtkSmartPointer<vtkImageActor> sagittal = vtkSmartPointer<vtkImageActor>::New();
	sagittal->GetMapper()->SetInputConnection(sagittalColors->GetOutputPort());
	sagittal->SetDisplayExtent(128, 128, 0, 255, 0, 92);
	sagittal->ForceOpaqueOn();

	// Create the second (axial) plane of the three planes. We use the
	// same approach as before except that the extent differs.
	vtkSmartPointer<vtkImageMapToColors> axialColors = vtkSmartPointer<vtkImageMapToColors>::New();
	axialColors->SetInputConnection(reader->GetOutputPort());
	axialColors->SetLookupTable(hueLut);
	axialColors->Update();

	vtkSmartPointer<vtkImageActor> axial = vtkSmartPointer<vtkImageActor>::New();
	axial->GetMapper()->SetInputConnection(axialColors->GetOutputPort());
	axial->SetDisplayExtent(0, 255, 0, 255, 46, 46);
	axial->ForceOpaqueOn();

	// Create the third (coronal) plane of the three planes. We use
	// the same approach as before except that the extent differs.
	vtkSmartPointer<vtkImageMapToColors> coronalColors = vtkSmartPointer<vtkImageMapToColors>::New();
	coronalColors->SetInputConnection(reader->GetOutputPort());
	coronalColors->SetLookupTable(satLut);
	coronalColors->Update();

	vtkSmartPointer<vtkImageActor> coronal = vtkSmartPointer<vtkImageActor>::New();
	coronal->GetMapper()->SetInputConnection(coronalColors->GetOutputPort());
	coronal->SetDisplayExtent(0, 255, 128, 128, 0, 92);
	coronal->ForceOpaqueOn();

	// It is convenient to create an initial view of the data. The
	// FocalPoint and Position form a vector direction. Later on
	// (ResetCamera() method) this vector is used to position the camera
	// to look at the data in this direction.
	vtkSmartPointer<vtkCamera> aCamera = vtkSmartPointer<vtkCamera>::New();
	aCamera->SetViewUp(0, 0, -1);
	aCamera->SetPosition(0, -1, 0);
	aCamera->SetFocalPoint(0, 0, 0);
	aCamera->ComputeViewPlaneNormal();
	aCamera->Azimuth(30.0);
	aCamera->Elevation(30.0);

	//// Actors are added to the renderer.
	//aRenderer->AddActor(outline);
	//aRenderer->AddActor(sagittal);
	//aRenderer->AddActor(axial);
	//aRenderer->AddActor(coronal);
	//aRenderer->AddActor(skin);
	//aRenderer->AddActor(imageactor);
	aRenderer->AddActor(bone);
	aRenderer->AddActor(polyactor);


	// Turn off bone for this example.
	bone->VisibilityOn();

	// Set skin to semi-transparent.
	skin->GetProperty()->SetOpacity(0.5);

	// An initial camera view is created. The Dolly() method moves
	// the camera towards the FocalPoint, thereby enlarging the image.
	aRenderer->SetActiveCamera(aCamera);

	// Calling Render() directly on a vtkRenderer is strictly forbidden.
	// Only calling Render() on the vtkRenderWindow is a valid call.
	renWin->Render();

	aRenderer->ResetCamera();
	aCamera->Dolly(1.5);

	// Note that when camera movement occurs (as it does in the Dolly()
	// method), the clipping planes often need adjusting. Clipping planes
	// consist of two planes: near and far along the view direction. The
	// near plane clips out objects in front of the plane; the far plane
	// clips out objects behind the plane. This way only what is drawn
	// between the planes is actually rendered.
	aRenderer->ResetCameraClippingRange();

	// interact with data
	iren->Initialize();
	iren->Start();

	return EXIT_SUCCESS;
}