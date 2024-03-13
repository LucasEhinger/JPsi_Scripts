#!/usr/bin/env bash

#Targets=("D" "He" "C")
Targets=("D")
TreeNames=("gd_epemprotinc__B4_F4_T1_S2" "ghe_epemprotinc__B4_F4_T1_S2" "gc12_epemprotinc__B4_F4_T1_S2")
inFOLDER=/lustre19/expphy/volatile/halld/home/ehingerl/jpsi/trees/v8/fiducialCuts/noTracks/

iter=$1
fcalMax=$2
fcalMin=$3
bcalMax=$4
bcalMin=$5
#
for i in ${!Targets[@]}; do
  INPUTFILE=${inFOLDER}/data_tree_${Targets[$i]}.root
  TREE=${outFOLDER}/data_tree_${Targets[$i]}.root
  root -q -b 'CalPoverEcuts.C("'${INPUTFILE}'","'${TREE}'","'${TreeNames[$i]}'","'${fcalMin}'","'${fcalMax}'","'${bcalMin}'","'${bcalMax}'")' &
done

#TargetsSIM=("2H" "4He" "12C")
#mixedStrings=("." "_mixed.")
#MFSRCStrings=("MF" "SRC")
#
#for isMixed in ${mixedStrings[@]}; do
#  for MFSRC in ${MFSRCStrings[@]}; do
#    for i in ${!TargetsSIM[@]}; do
#      INPUTFILE=${inFOLDER}/tree_DSelector_${TargetsSIM[$i]}_${MFSRC}_helicity${isMixed}root
#      TREE=${outFOLDER}/tree_DSelector_${TargetsSIM[$i]}_${MFSRC}_helicity${isMixed}root
#      if [[ ${TargetsSIM[$i]} != "2H" || ${MFSRC} != "SRC" ]]
#      then
#        root -q -b 'CalPoverEcuts.C("'${INPUTFILE}'","'${TREE}'","'${TreeNames[$i]}'","'${fcalMin}'","'${fcalMax}'","'${bcalMin}'","'${bcalMax}'")' &
#      fi
#    done
#  done
#done

wait