/*=========================================================================

  Program:   Advanced Normalization Tools
  Module:    $RCSfile: itkANTSImageTransformation.cxx,v $
  Language:  C++
  Date:      $Date: 2008/11/15 23:46:06 $
  Version:   $Revision: 1.18 $

  Copyright (c) ConsortiumOfANTS. All rights reserved.
  See accompanying COPYING.txt or 
 http://sourceforge.net/projects/advants/files/ANTS/ANTSCopyright.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef _itkANTSImageTransformation_txx_
#define _itkANTSImageTransformation_txx_

// disable debug warnings in MS compiler
#ifdef _MSC_VER
#pragma warning(disable: 4786)
#endif

#include "ANTS_affine_registration2.h"
#include "itkANTSImageTransformation.h"

#include "itkIdentityTransform.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkLinearInterpolateImageFunction.h"
#include "itkRecursiveGaussianImageFilter.h"
#include "itkResampleImageFilter.h"
#include "itkVectorImageFileWriter.h"

#include "vnl/vnl_math.h"

#ifdef HAVE_MINC4ITK
#include <itkMincHelpers.h>
#endif //HAVE_MINC4ITK

namespace itk
{

template<unsigned int TDimension, class TReal>
ANTSImageTransformation<TDimension, TReal>
::ANTSImageTransformation()
{
    this->m_DeformationField=NULL;
    this->m_InverseDeformationField=NULL;
    this->m_AffineTransform=NULL;
    this->m_WriteComponentImages = false;
    m_DeformationRegionOfInterestSize.Fill(0);
    m_DeformationRegionSpacing.Fill(1);
    m_DeformationRegionOfInterestCenter.Fill(0);

}

template<unsigned int TDimension, class TReal>
void
ANTSImageTransformation<TDimension, TReal>
::Compose()
{

}

template<unsigned int TDimension, class TReal>
void
ANTSImageTransformation<TDimension, TReal>
::Write()
{
    std::cout <<" begin writing " << m_NamingConvention << std::endl;

    std::string filePrefix = this->m_NamingConvention;
    std::string::size_type pos = filePrefix.rfind( "." );
    std::string extension;
    std::string gzExtension( "" );
    if ( pos != std::string::npos 
      && std::string( filePrefix, pos, pos+2 ) != std::string( "./" ) )
      {
      filePrefix = std::string( filePrefix, 0, pos );
      extension = std::string( this->m_NamingConvention, pos, 
        this->m_NamingConvention.length()-1 );
      if ( extension == std::string( ".gz" ) )
        {
        gzExtension = std::string( ".gz" );
    				pos = filePrefix.rfind( "." );
    				extension = std::string( filePrefix, pos, 
    				  filePrefix.length()-1 );
        filePrefix = std::string( filePrefix, 0, pos );
        } 
      }
    else
      {
      extension = std::string( ".nii.gz" ); 
      }  

    //Added by songgang
    if (this->m_AffineTransform) {
#ifdef HAVE_MINC4ITK
      if( extension == std::string( ".xfm" ) )
      {
        if(! this->m_DeformationField )
        {
          minc::write_linear_xfm(this->m_NamingConvention.c_str(), 
                                this->m_AffineTransform->GetMatrix(),
                                this->m_AffineTransform->GetOffset());
          // let's create an inverse to be consistent
          
          std::string inv_xfm = filePrefix + std::string( "_inverse.xfm" );
          
          AffineTransformPointer tmp=AffineTransformType::New();
          //tmp->SetCenter(this->m_AffineTransform->GetCenter());
          this->m_AffineTransform->GetInverse(tmp);
          minc::write_linear_xfm(inv_xfm.c_str(), 
                                 tmp->GetMatrix(),
                                 tmp->GetOffset());
          
          //delete tmp;
        }
      } else  
#endif //HAVE_MINC4ITK
      {        
        std::cout << " writing " << filePrefix << " affine " << std::endl;
        std::string filename = filePrefix + std::string( "Affine.txt" );
        WriteAffineTransformFile(this->m_AffineTransform, filename);
      }
    }
    
    if ( this->m_DeformationField )
    {  
        std::cout <<" writing " << filePrefix << " def " <<  std::endl;
#ifdef HAVE_MINC4ITK 
        if ( extension == std::string( ".xfm" ) )
        {
          std::string filename = filePrefix + std::string( "_grid_0.mnc" );
          typedef ImageFileWriter<DeformationFieldType> WriterType;
          typename WriterType::Pointer writer = WriterType::New();
          writer->SetFileName( filename );
          writer->SetInput( this->m_DeformationField );
          writer->Update();
          
          std::string::size_type pos = filename.rfind( "/" );
          if(pos==std::string::npos) pos=0;
          else pos++;
          std::string basename(filename,pos,filename.length());
          
          if(this->m_AffineTransform)
            minc::write_combined_xfm(this->m_NamingConvention.c_str(),
                                     basename.c_str(),
                                     this->m_AffineTransform->GetMatrix(),
                                     this->m_AffineTransform->GetOffset());
          else
            minc::write_nonlinear_xfm(this->m_NamingConvention.c_str(),basename.c_str());
          
        } else    
#endif //HAVE_MINC4ITK
        if ( extension != std::string( ".mha" ) )
        {
            std::string filename = filePrefix + std::string( "Warp" )
              + extension + gzExtension;

            typedef VectorImageFileWriter<DeformationFieldType, ImageType> WriterType;
            typename WriterType::Pointer writer = WriterType::New();
            std::cout << "filename " << filename << std::endl;
            writer->SetFileName( filename );
            writer->SetUseAvantsNamingConvention( true );
            writer->SetInput( this->m_DeformationField );
            writer->Update();
        }
        else
        {
            std::string filename = filePrefix + std::string( "Warp.mha" );
            typedef ImageFileWriter<DeformationFieldType> WriterType;
            typename WriterType::Pointer writer = WriterType::New();
            writer->SetFileName( filename );
            writer->SetInput( this->m_DeformationField );
            writer->Update();
        }
    }

    if ( this->m_InverseDeformationField )
    {  
      
#ifdef HAVE_MINC4ITK 
      if ( extension == std::string( ".xfm" ) )
      {
        std::string filename = filePrefix + std::string( "_inverse_grid_0.mnc" );
        std::cout<<"Writing:"<<filename<<std::endl;
        typedef ImageFileWriter<DeformationFieldType> WriterType;
        typename WriterType::Pointer writer = WriterType::New();
        writer->SetFileName( filename );
        writer->SetInput( this->m_InverseDeformationField );
        writer->Update();
        
        std::string inv_xfm = filePrefix + std::string( "_inverse.xfm" );
        
        std::string::size_type pos = filename.rfind( "/" );
        if(pos==std::string::npos) pos=0;
        else pos++;
        std::string basename(filename,pos,filename.length());
          
        if(this->m_AffineTransform)
        {
          AffineTransformPointer tmp=AffineTransformType::New();
          this->m_AffineTransform->GetInverse(tmp);
          
          minc::write_combined_xfm(inv_xfm.c_str(),
                                   tmp->GetMatrix(),
                                   tmp->GetOffset(),
                                    basename.c_str());
        } else {
          minc::write_nonlinear_xfm(inv_xfm.c_str(),basename.c_str());
        } 
        
      } else
#endif //HAVE_MINC4ITK 
        if ( extension != std::string( ".mha" ) )
        {
            std::string filename = filePrefix + std::string( "InverseWarp" )
              + extension + gzExtension;

            typedef VectorImageFileWriter<DeformationFieldType, ImageType> WriterType;
            typename WriterType::Pointer writer = WriterType::New();
            writer->SetFileName( filename );
            writer->SetUseAvantsNamingConvention( true );
            writer->SetInput( this->m_InverseDeformationField );
            writer->Update();
        }
        else
        {
            std::string filename = filePrefix + std::string( "InverseWarp.mha" );
            typedef ImageFileWriter<DeformationFieldType> WriterType;
            typename WriterType::Pointer writer = WriterType::New();
            writer->SetFileName( filename );
            writer->SetInput( this->m_InverseDeformationField );
            writer->Update();
        }
    }
}

/**
 * Standard "PrintSelf" method
 */
template<unsigned int TDimension, class TReal>
void
ANTSImageTransformation<TDimension, TReal>
::PrintSelf( std::ostream& os, Indent indent) const
{
    Superclass::PrintSelf( os, indent );
}


} // end namespace itk
#endif
