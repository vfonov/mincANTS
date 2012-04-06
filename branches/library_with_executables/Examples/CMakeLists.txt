cmake_minimum_required(VERSION 2.8)

project(ANTS)

# flags for debug build
set( CMAKE_CXX_FLAGS_DEBUG "-g -Wall" )
set( CMAKE_C_FLAGS_DEBUG "-g -Wall" )

# ITK
find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

# VTK
find_package( VTK REQUIRED )
include( ${VTK_USE_FILE} )

# ANTS includes
include_directories( ../Utilities )
include_directories( ../Tensor )
include_directories( ../Temporary )
include_directories( ../ImageSegmentation )
include_directories( ../ImageRegistration )
include_directories( ../Temporary )

# global properties for RPATH
set( CMAKE_SKIP_BUILD_RPATH FALSE )
set( CMAKE_BUILD_WITH_INSTALL_RPATH FALSE )
set( CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib" )
set( CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE )

# all the other libraries link to CommandLineParser
add_library( antsCommandLineOption SHARED
  ../Utilities/antsCommandLineOption.cxx
  )
target_link_libraries( antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )

add_library( antsCommandLineParser SHARED
  ../Utilities/antsCommandLineParser.cxx
  )
target_link_libraries( antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( antsApplyTransforms SHARED
  antsApplyTransforms.cxx
  )
target_link_libraries( antsApplyTransforms antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( ANTS SHARED
  ANTS.cxx
  )
target_link_libraries( ANTS antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( ANTSIntegrateVectorField SHARED
  ANTSIntegrateVectorField.cxx
  )
target_link_libraries( ANTSIntegrateVectorField antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( ANTSIntegrateVelocityField SHARED
  ANTSIntegrateVelocityField.cxx
  )
target_link_libraries( ANTSIntegrateVelocityField antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( ANTSJacobian SHARED
  ANTSJacobian.cxx
  )
target_link_libraries( ANTSJacobian antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( antsMotionCorr SHARED
  antsMotionCorr.cxx
  )
target_link_libraries( antsMotionCorr antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( antsRegistration SHARED
  antsRegistration.cxx
  )
target_link_libraries( antsRegistration antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( ANTSUseDeformationFieldToGetAffineTransform SHARED
  ANTSUseDeformationFieldToGetAffineTransform.cxx
  )
target_link_libraries( ANTSUseDeformationFieldToGetAffineTransform antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( ANTSUseLandmarkImagesToGetAffineTransform SHARED
  ANTSUseLandmarkImagesToGetAffineTransform.cxx
  )
target_link_libraries( ANTSUseLandmarkImagesToGetAffineTransform antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( Atropos SHARED
  Atropos.cxx
  )
target_link_libraries( Atropos antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( AtroposMin SHARED
  AtroposMin.cxx
  )
target_link_libraries( AtroposMin antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( AverageAffineTransform SHARED
  AverageAffineTransform.cxx
  )
target_link_libraries( AverageAffineTransform antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( AverageImages SHARED
  AverageImages.cxx
  )
target_link_libraries( AverageImages antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( AverageTensorImages SHARED
  AverageTensorImages.cxx
  )
target_link_libraries( AverageTensorImages antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( CheckTopology SHARED
  CheckTopology.cxx
  )
target_link_libraries( CheckTopology antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( ClusterImageStatistics SHARED
  ClusterImageStatistics.cxx
  )
target_link_libraries( ClusterImageStatistics antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( ComposeMultiTransform SHARED
  ComposeMultiTransform.cxx
  )
target_link_libraries( ComposeMultiTransform antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( ComputeSimilarityMetric SHARED
  ComputeSimilarityMetric.cxx
  )
target_link_libraries( ComputeSimilarityMetric antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( ConvertImagePixelType SHARED
  ConvertImagePixelType.cxx
  )
target_link_libraries( ConvertImagePixelType antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( ConvertScalarImageToRGB SHARED
  ConvertScalarImageToRGB.cxx
  )
target_link_libraries( ConvertScalarImageToRGB antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( ConvertToJpg SHARED
  ConvertToJpg.cxx
  )
target_link_libraries( ConvertToJpg antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( ConvertVectorFieldToVTK SHARED
  ConvertVectorFieldToVTK.cxx
  )
target_link_libraries( ConvertVectorFieldToVTK antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( CopyImageHeaderInformation SHARED
  CopyImageHeaderInformation.cxx
  )
target_link_libraries( CopyImageHeaderInformation antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( CreateDisplacementField SHARED
  CreateDisplacementField.cxx
  )
target_link_libraries( CreateDisplacementField antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( CreateDTICohort SHARED
  CreateDTICohort.cxx
  )
target_link_libraries( CreateDTICohort antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( CreateImage SHARED
  CreateImage.cxx
  )
target_link_libraries( CreateImage antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( CreateWarpedGridImage SHARED
  CreateWarpedGridImage.cxx
  )
target_link_libraries( CreateWarpedGridImage antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( ExtractRegionFromImageByMask SHARED
  ExtractRegionFromImageByMask.cxx
  )
target_link_libraries( ExtractRegionFromImageByMask antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( ExtractRegionFromImage SHARED
  ExtractRegionFromImage.cxx
  )
target_link_libraries( ExtractRegionFromImage antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( ExtractSliceFromImage SHARED
  ExtractSliceFromImage.cxx
  )
target_link_libraries( ExtractSliceFromImage antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( GetMeshAndTopology SHARED
  GetMeshAndTopology.cxx
  )
target_link_libraries( GetMeshAndTopology antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( ImageCompare SHARED
  ImageCompare.cxx
  )
target_link_libraries( ImageCompare antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( ImageMath SHARED
  ImageMath.cxx
  )
target_link_libraries( ImageMath antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( ImageSetStatistics SHARED
  ImageSetStatistics.cxx
  )
target_link_libraries( ImageSetStatistics antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( KellyKapowski SHARED
  KellyKapowski.cxx
  )
target_link_libraries( KellyKapowski antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( KellySlater SHARED
  KellySlater.cxx
  )
target_link_libraries( KellySlater antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( LabelClustersUniquely SHARED
  LabelClustersUniquely.cxx
  )
target_link_libraries( LabelClustersUniquely antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( LabelGeometryMeasures SHARED
  LabelGeometryMeasures.cxx
  )
target_link_libraries( LabelGeometryMeasures antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( LabelOverlapMeasures SHARED
  LabelOverlapMeasures.cxx
  )
target_link_libraries( LabelOverlapMeasures antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( LaplacianThickness SHARED
  LaplacianThickness.cxx
  )
target_link_libraries( LaplacianThickness antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( MeasureImageSimilarity SHARED
  MeasureImageSimilarity.cxx
  )
target_link_libraries( MeasureImageSimilarity antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( MeasureMinMaxMean SHARED
  MeasureMinMaxMean.cxx
  )
target_link_libraries( MeasureMinMaxMean antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( MemoryTest SHARED
  MemoryTest.cxx
  )
target_link_libraries( MemoryTest antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( MultiplyImages SHARED
  MultiplyImages.cxx
  )
target_link_libraries( MultiplyImages antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( N3BiasFieldCorrection SHARED
  N3BiasFieldCorrection.cxx
  )
target_link_libraries( N3BiasFieldCorrection antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( N4BiasFieldCorrection SHARED
  N4BiasFieldCorrection.cxx
  )
target_link_libraries( N4BiasFieldCorrection antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( PasteImageIntoImage SHARED
  PasteImageIntoImage.cxx
  )
target_link_libraries( PasteImageIntoImage antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( PermuteFlipImageOrientationAxes SHARED
  PermuteFlipImageOrientationAxes.cxx
  )
target_link_libraries( PermuteFlipImageOrientationAxes antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( PrintHeader SHARED
  PrintHeader.cxx
  )
target_link_libraries( PrintHeader antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( ReorientTensorImage SHARED
  ReorientTensorImage.cxx
  )
target_link_libraries( ReorientTensorImage antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( ResampleImageBySpacing SHARED
  ResampleImageBySpacing.cxx
  )
target_link_libraries( ResampleImageBySpacing antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( ResampleImage SHARED
  ResampleImage.cxx
  )
target_link_libraries( ResampleImage antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( ResetDirection SHARED
  ResetDirection.cxx
  )
target_link_libraries( ResetDirection antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( sccan SHARED
  sccan.cxx
  )
target_link_libraries( sccan antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( SetDirectionByMatrix SHARED
  SetDirectionByMatrix.cxx
  )
target_link_libraries( SetDirectionByMatrix antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( SetOrigin SHARED
  SetOrigin.cxx
  )
target_link_libraries( SetOrigin antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( SetSpacing SHARED
  SetSpacing.cxx
  )
target_link_libraries( SetSpacing antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( SmoothImage SHARED
  SmoothImage.cxx
  )
target_link_libraries( SmoothImage antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( StackSlices SHARED
  StackSlices.cxx
  )
target_link_libraries( StackSlices antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( StudentsTestOnImages SHARED
  StudentsTestOnImages.cxx
  )
target_link_libraries( StudentsTestOnImages antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( SurfaceBasedSmoothing SHARED
  SurfaceBasedSmoothing.cxx
  )
target_link_libraries( SurfaceBasedSmoothing antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( SurfaceCurvature SHARED
  SurfaceCurvature.cxx
  )
target_link_libraries( SurfaceCurvature antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( TensorDerivedImage SHARED
  TensorDerivedImage.cxx
  )
target_link_libraries( TensorDerivedImage antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( ThresholdImage SHARED
  ThresholdImage.cxx
  )
target_link_libraries( ThresholdImage antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( TileImages SHARED
  TileImages.cxx
  )
target_link_libraries( TileImages antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( WarpImageMultiTransform SHARED
  WarpImageMultiTransform.cxx
  )
target_link_libraries( WarpImageMultiTransform antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( WarpTensorImageMultiTransform SHARED
  WarpTensorImageMultiTransform.cxx
  )
target_link_libraries( WarpTensorImageMultiTransform antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( WarpTimeSeriesImageMultiTransform SHARED
  WarpTimeSeriesImageMultiTransform.cxx
  )
target_link_libraries( WarpTimeSeriesImageMultiTransform antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




add_library( WarpVTKPolyDataMultiTransform SHARED
  WarpVTKPolyDataMultiTransform.cxx
  )
target_link_libraries( WarpVTKPolyDataMultiTransform antsCommandLineParser antsCommandLineOption ${ITK_LIBRARIES} ${VTK_LIBRARIES} )




install( TARGETS 
  antsCommandLineOption
  antsCommandLineParser
  ANTS
  antsApplyTransforms
  ANTSIntegrateVectorField
  ANTSIntegrateVelocityField
  ANTSJacobian
  antsMotionCorr
  antsRegistration
  ANTSUseDeformationFieldToGetAffineTransform
  ANTSUseLandmarkImagesToGetAffineTransform
  Atropos
  AtroposMin
  AverageAffineTransform
  AverageImages
  AverageTensorImages
  CheckTopology
  ClusterImageStatistics
  ComposeMultiTransform
  ComputeSimilarityMetric
  ConvertImagePixelType
  ConvertScalarImageToRGB
  ConvertToJpg
  ConvertVectorFieldToVTK
  CopyImageHeaderInformation
  CreateDisplacementField
  CreateDTICohort
  CreateImage
  CreateWarpedGridImage
  ExtractRegionFromImage
  ExtractRegionFromImageByMask
  ExtractSliceFromImage
  GetMeshAndTopology
  ImageCompare
  ImageMath
  ImageSetStatistics
  KellyKapowski
  KellySlater
  LabelClustersUniquely
  LabelGeometryMeasures
  LabelOverlapMeasures
  LaplacianThickness
  MeasureImageSimilarity
  MeasureMinMaxMean
  MemoryTest
  MultiplyImages
  N3BiasFieldCorrection
  N4BiasFieldCorrection
  PasteImageIntoImage
  PermuteFlipImageOrientationAxes
  PrintHeader
  ReorientTensorImage
  ResampleImage
  ResampleImageBySpacing
  ResetDirection
  sccan
  SetDirectionByMatrix
  SetOrigin
  SetSpacing
  SmoothImage
  StackSlices
  StudentsTestOnImages
  SurfaceBasedSmoothing
  SurfaceCurvature
  TensorDerivedImage
  ThresholdImage
  TileImages
  WarpImageMultiTransform
  WarpTensorImageMultiTransform
  WarpTimeSeriesImageMultiTransform
  WarpVTKPolyDataMultiTransform
  DESTINATION lib
  )

install( DIRECTORY
  include
  DESTINATION .
  )