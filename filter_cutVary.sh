#!/usr/bin/env bash

Targets=("D" "He" "C")
TreeNames=("gd_epemprotinc__B4_F4_T1_S2" "ghe_epemprotinc__B4_F4_T1_S2" "gc12_epemprotinc__B4_F4_T1_S2")
TargetsSIM=("2H" "4He" "12C")
mixedStrings=("_mixed.")
MFSRCStrings=("MF" "SRC")
workFolder="/w/halld-scshelf2101/halld2/home/ehingerl/analysis/jpsi/trees/"


inFOLDER=/lustre19/expphy/volatile/halld/home/ehingerl/jpsi/trees/v8/filtered/noTrackShower/loose/
#outFOLDER=/lustre19/expphy/volatile/halld/home/ehingerl/jpsi/trees/v7/PoverE2/m3_p2_sigma/noTracks/preB_03/Emiss_1

n_samples_per_cut=5

IFS=$'\n'
FOLDERS=($(find ${inFOLDER} -name "data_tree_D.root"))
unset IFS

for j in ${!FOLDERS[@]}; do
  tmp1=${FOLDERS[$j]}
  inFolder=${tmp1%data*}
  outFolder=${workFolder}${inFolder##*trees}

  mkdir -p ${outFolder}
#  for i in ${!Targets[@]}; do
#    INPUTFILE=${inFolder}/data_tree_${Targets[$i]}.root
#    TREE=${outFolder}/data_hist_cutVary2_${Targets[$i]}.root
#    root -q -b 'filter_cutVary.C("'${INPUTFILE}'","'${TREE}'","'${TreeNames[$i]}'","'${n_samples_per_cut}'")'
#  done

  for isMixed in ${mixedStrings[@]}; do
    for MFSRC in ${MFSRCStrings[@]}; do
      for i in ${!TargetsSIM[@]}; do
        INPUTFILE=${inFolder}/tree_DSelector_${TargetsSIM[$i]}_${MFSRC}_helicity${isMixed}root
        TREE=${outFolder}/hist_cutVary2_DSelector_${TargetsSIM[$i]}_${MFSRC}_helicity${isMixed}root
        if [[ ${TargetsSIM[$i]} != "2H" || ${MFSRC} != "SRC" ]]
        then
          root -q -b 'filter_cutVary.C("'${INPUTFILE}'","'${TREE}'","'${TreeNames[$i]}'","'${n_samples_per_cut}'")'
        fi
      done
    done
  done
done
wait
