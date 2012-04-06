cmake_minimum_required(VERSION 2.8)

project(ANTS_SuperBuild)
include( ExternalProject )

# set debug build flags
set( CMAKE_CXX_FLAGS_DEBUG "-g -Wall" )
set( CMAKE_C_FLAGS_DEBUG "-g -Wall" )

# ITK library
if( NOT ITK_DIR )
  ExternalProject_Add( ITK
    TMP_DIR ${ANTS_SuperBuild_BINARY_DIR}/ITK/tmp 
    STAMP_DIR ${ANTS_SuperBuild_BINARY_DIR}/ITK/stamp
    DOWNLOAD_DIR ${ANTS_SuperBuild_BINARY_DIR}/ITK/ITK-src
    GIT_REPOSITORY git://itk.org/ITK.git 
    GIT_TAG d55f6fac703d34e43ff9d0f5be8c5f44a6d4a578
    SOURCE_DIR ${ANTS_SuperBuild_BINARY_DIR}/ITK/ITK-src
    CMAKE_ARGS -D ITK_BUILD_ALL_MODULES=ON -D CMAKE_BUILD_TYPE=Release -D BUILD_SHARED_LIBS=ON -D BUILD_TESTING=OFF -D BUILD_EXAMPLES=OFF
    BINARY_DIR ${ANTS_SuperBuild_BINARY_DIR}/ITK/ITK-build
    INSTALL_COMMAND "" ) # have to include a blank install command or it will try to install into standard dirs
  set( ITK_DIR ${ANTS_SuperBuild_BINARY_DIR}/ITK/ITK-build )
  set( ANTS_DEPENDSON_ITK ITK ) # set to ITK when we need dependency; not set otherwise
endif( NOT ITK_DIR )

# VTK library
if( NOT VTK_DIR )
  ExternalProject_Add( VTK
    TMP_DIR ${ANTS_SuperBuild_BINARY_DIR}/VTK/tmp 
    STAMP_DIR ${ANTS_SuperBuild_BINARY_DIR}/VTK/stamp
    DOWNLOAD_DIR ${ANTS_SuperBuild_BINARY_DIR}/VTK/VTK-src
    GIT_REPOSITORY git://vtk.org/VTK.git 
    GIT_TAG 2380face149471e2d8872f52c5a5f6b68fa87885
    SOURCE_DIR ${ANTS_SuperBuild_BINARY_DIR}/VTK/VTK-src
    CMAKE_ARGS -D CMAKE_BUILD_TYPE=Release -D BUILD_SHARED_LIBS=ON -D BUILD_TESTING=OFF -D BUILD_EXAMPLES=OFF
    BINARY_DIR ${ANTS_SuperBuild_BINARY_DIR}/VTK/VTK-build
    INSTALL_COMMAND "" ) # have to include a blank install command or it will try to install into standard dirs
  set( VTK_DIR ${ANTS_SuperBuild_BINARY_DIR}/VTK/VTK-build )
  set( ANTS_DEPENDSON_VTK VTK ) # set to VTK when we need dependency; not set otherwise
endif( NOT VTK_DIR )

ExternalProject_Add( ANTS
  DEPENDS ${ANTS_DEPENDSON_ITK} ${ANTS_DEPENDSON_VTK}
  TMP_DIR ${ANTS_SuperBuild_BINARY_DIR}/ANTS/tmp
  STAMP_DIR ${ANTS_SuperBuild_BINARY_DIR}/ANTS/stamp
  SOURCE_DIR ${ANTS_SuperBuild_SOURCE_DIR}/Examples
  CMAKE_ARGS -D ITK_DIR=${ITK_DIR} -D VTK_DIR=${VTK_DIR} -D CMAKE_INSTALL_PREFIX=${ANTS_SuperBuild_BINARY_DIR}
  BINARY_DIR ${ANTS_SuperBuild_BINARY_DIR}/ANTS/ANTS-build 
  INSTALL_DIR "" ) # have to include a blank install command or it will try to install into standard dirs
