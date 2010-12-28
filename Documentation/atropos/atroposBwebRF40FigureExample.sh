# input image 
IMG=T1_ICBM_1mm_3perc_40_bias/t1_icbm_normal_1mm_pn3_rf40.mhd
if [ ! -s $IMG ] ; then 
 echo no image named $IMG exists --- exiting.   you should be able to download this image from the brainweb website and use the header defined below to make it readable by Atropos. 
 exit
fi
# number of classes
NC=3
# convergence criterion 
CONV=[3,0]
# MRF-beta parameter 
MRF=0.20
# socrates parameter --- estimates mixture model
SOC=1
# kmeans with N4
NAMING=bwebRF40example
# binary image used as a weight and mask image for N4 and segmentation mask for Atropos 
# you can get this by thresholding the ground_truth labeling 
WTIM=mask.nii.gz
$EX  -d 3 -a  $IMG -i KMeans[$NC] -o [test_init.nii.gz,test_init_prob%02d.nii.gz] -m [${MRF},1x1x1] -x mask.nii.gz -p Socrates[${SOC}]  -c $CONV 
BS="N4BiasFieldCorrection -d 3  -h 0 " ; ITS=20 ; ITS2=3
$BS  -i $IMG   -o  n4.nii.gz -s 2 -b [200] -w mask.nii.gz -c [${ITS}x${ITS}x${ITS}x${ITS}x${ITS2},0.0001] -x mask.nii.gz 
Atropos -d 3 -a  n4.nii.gz -i KMeans[$NC] -o [test.nii.gz,test_prob%02d.nii.gz] -m [${MRF},1x1x1] -x mask.nii.gz -p Socrates[${SOC}]  -c $CONV 
# evaluation numbers
if [ -s ground_truth.nii.gz ] ; then 
ImageMath 3 dice_out.txt DiceAndMinDistSum test.nii.gz ground_truth.nii.gz 
fi
exit

# below this line is a header file that can be used for the brain web raw data:
ObjectType = Image
NDims = 3
BinaryData = True
BinaryDataByteOrderMSB = False
CompressedData = False
TransformMatrix = 1 0 0 0 1 0 0 0 1
Offset = 0 0 0
CenterOfRotation = 0 0 0
AnatomicalOrientation = RAI
ElementSpacing = 1 1 1
DimSize = 181 217 181
ElementType = MET_UCHAR
ElementDataFile = t1_icbm_normal_1mm_pn3_rf40.rawb
