#!/usr/bin/env bash

Targets=("D" "He" "C")
#Targets=("D_B")
TreeNames=("gd_epemprotinc__B4_F4_T1_S2" "ghe_epemprotinc__B4_F4_T1_S2" "gc12_epemprotinc__B4_F4_T1_S2")
#TreeNames=("gc12_epemprotinc__B4_F4_T1_S2")
TargetsSIM=("2H" "4He" "12C")
#mixedStrings=("." "_mixed.")
mixedStrings=("_mixed")
MFSRCStrings=("MF" "SRC")
workFolder="/w/halld-scshelf2101/halld2/home/ehingerl/analysis/jpsi/trees/"

IFS=$'\n'
#FOLDERS=($(find .//lustre19/expphy/volatile/halld/home/ehingerl/jpsi/trees/v7/PoverE/m3_p2_sigma/noTracks/preB_03/Emiss_1/ -name "data_tree_D.root"))
#FOLDERS=($(find ./../files/fiducialCuts/negWeights/ -name "data_tree_D.root"))
FOLDERS=($(find /lustre19/expphy/volatile/halld/home/ehingerl/jpsi/trees/v8/filtered/noTrackShower/ -name "data_tree_D.root"))
#FOLDERS=($(find ./../files/PoverE/m3_p2_sigma/preB_0/ -name "data_tree_D.root"))
unset IFS

FOLDERS=("/lustre19/expphy/volatile/halld/home/ehingerl/jpsi/trees/v8/filtered/noTrackShower/")
for j in ${!FOLDERS[@]}; do
  tmp1=${FOLDERS[$j]}
  inFolder=${tmp1%data*}
  outFolder=${workFolder}${inFolder##*trees}/simHists/

  mkdir -p ${outFolder}

  for isMixed in ${mixedStrings[@]}; do
    for MFSRC in ${MFSRCStrings[@]}; do
      for i in ${!TargetsSIM[@]}; do
        INPUTFILE=${inFolder}/tree_DSelector_${TargetsSIM[$i]}_${MFSRC}_helicity${isMixed}_2.root
        TREE=${outFolder}/hist_mass_DSelector_${TargetsSIM[$i]}_${MFSRC}_helicity${isMixed}_2.root
        if [[ ${TargetsSIM[$i]} != "2H" || ${MFSRC} != "SRC" ]]
        then
          root -q -b 'make_sim_mass_hists.C("'${INPUTFILE}'","'${TREE}'","'${TreeNames[$i]}'")'
        fi
      done
    done
  done
done
wait