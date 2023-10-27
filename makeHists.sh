#!/usr/bin/env bash

Targets=("D" "He" "C")
#Targets=("D")
TreeNames=("gd_epemprotinc__B4_F4_T1_S2" "ghe_epemprotinc__B4_F4_T1_S2" "gc12_epemprotinc__B4_F4_T1_S2")
TargetsSIM=("2H" "4He" "12C")
mixedStrings=("." "_mixed.")
MFSRCStrings=("MF" "SRC")
workFolder="/w/halld-scshelf2101/halld2/home/ehingerl/analysis/jpsi/trees/"

IFS=$'\n'
#FOLDERS=($(find .//lustre19/expphy/volatile/halld/home/ehingerl/jpsi/trees/v7/PoverE/m3_p2_sigma/noTracks/preB_03/Emiss_1/ -name "data_tree_D.root"))
#FOLDERS=($(find ./../files/fiducialCuts/negWeights/ -name "data_tree_D.root"))
FOLDERS=($(find /lustre19/expphy/volatile/halld/home/ehingerl/jpsi/trees/v7/PoverE4/m3_p2_sigma/one_Track/preB_03/Emiss_1/ -name "data_tree_D.root"))
#FOLDERS=($(find ./../files/PoverE/m3_p2_sigma/preB_0/ -name "data_tree_D.root"))
unset IFS

#FOLDERS=(".//lustre19/expphy/volatile/halld/home/ehingerl/jpsi/trees/v7/PoverE/m3_p2_sigma/withTracks/preB_03/Emiss_1/EgammaCuts/8p2_upper" ".//lustre19/expphy/volatile/halld/home/ehingerl/jpsi/trees/v7/PoverE/m3_p2_sigma/noTracks/preB_03/Emiss_1/EgammaCuts/8p2_upper")
for j in ${!FOLDERS[@]}; do
  tmp1=${FOLDERS[$j]}
  inFolder=${tmp1%data*}
  outFolder=${workFolder}${inFolder##*trees}

  mkdir -p ${outFolder}
  for i in ${!Targets[@]}; do
    INPUTFILE=${inFolder}/data_tree_${Targets[$i]}.root
    TREE=${outFolder}/data_hist_${Targets[$i]}.root
    root -q -b 'makeHists.C("'${INPUTFILE}'","'${TREE}'","'${TreeNames[$i]}'")' &
  done

#  for isMixed in ${mixedStrings[@]}; do
#    for MFSRC in ${MFSRCStrings[@]}; do
#      for i in ${!TargetsSIM[@]}; do
#        INPUTFILE=${inFolder}/tree_DSelector_${TargetsSIM[$i]}_${MFSRC}_helicity${isMixed}root
#        TREE=${outFolder}/hist_DSelector_${TargetsSIM[$i]}_${MFSRC}_helicity${isMixed}root
#        if [[ ${TargetsSIM[$i]} != "2H" || ${MFSRC} != "SRC" ]]
#        then
#          root -q -b 'makeHists.C("'${INPUTFILE}'","'${TREE}'","'${TreeNames[$i]}'")' &
#        fi
#      done
#    done
#  done
  wait
done
wait


