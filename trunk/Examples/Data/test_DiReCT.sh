#!/bin/bash 
SEGOUT=test_image_seg.nii.gz
if [ ! -s $SEGOUT ] ; then 
  echo run from the directory containing $SEGOUT
  exit
fi
GM=segger_prob_02.nii.gz 
WM=segger_prob_03.nii.gz 
GT=test_image_ground_truth.nii.gz
THICKOUT=test_image_thickness.nii.gz 
cp $SEGOUT temp.nii.gz 
ImageMath 3 temp.nii.gz CorruptImage temp.nii.gz 0.05 0.1
ThresholdImage 3 temp.nii.gz mask.nii.gz 0.1 9999 
ImageMath 3 mask.nii.gz GetLargestComponent mask.nii.gz 
Atropos -d 3 -a temp.nii.gz -i kmeans[3] -o [segger.nii.gz,segger_prob_%02d.nii.gz] -c [3,0] -m [0.0,1x1x1] -x mask.nii.gz  
# ThresholdImage 3 $SEGOUT $WM 3 3 
# SmoothImage 3  $WM 0.8  $WM 1
# ThresholdImage 3 $SEGOUT $GM 2 2  
# SmoothImage 3  $GM 0.8  $GM 1
# KellySlater 3  test_image_seg.nii.gz test_image_wm.nii.gz test_image_gm.nii.gz   test_thick.nii.gz 0.1 45 10 0 1.

rm direct_eval_log.txt 
THPROG=KellyKapowski
smoothing=1
# for r in 0.010 0.015 0.020 0.025 0.05 0.075 0.1 0.125 0.15 ; do 
rct=10
for r in 0.05 0.075 0.10 0.125 0.15 0.175 0.20 0.225 ; do
  thexe="$THPROG -d 3 -s ${SEGOUT} -w $WM -g $GM -o $THICKOUT -r $r --convergence [ 45 , 0 , 5 ] -t 10 -m $smoothing "
  echo $thexe 
  $thexe 
  ImageMath 3 diff.nii.gz - $THICKOUT $GT
  ImageMath 3 diff_${rct}_slice.nii.gz ExtractSlice diff.nii.gz 30 
  ImageMath 3 gt_slice.nii.gz ExtractSlice $GT 30 
  ThresholdImage 2 gt_slice.nii.gz gt_slice.nii.gz 2 999 
  echo " params: grad-step $r , smooth = $smoothing " >> direct_eval_log.txt
  MeasureMinMaxMean 2 diff_${rct}_slice.nii.gz direct_eval_log.txt  1 gt_slice.nii.gz 
  MeasureMinMaxMean 2 diff_${rct}_slice.nii.gz direct_eval_log.txt  0 gt_slice.nii.gz
  let rct=$rct+1
done 
rm $WM $GM temp.nii.gz mask.nii.gz segger*

