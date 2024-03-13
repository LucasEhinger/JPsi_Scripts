#!/usr/bin/env bash

Targets=("D" "He" "C")
#Targets=("C")

Targets_names=("deuterium" "helium" "carbon")
#Targets_names=("carbon")

TreeNames=("gd_epemprotinc__B4_F4_T1_S2" "ghe_epemprotinc__B4_F4_T1_S2" "gc12_epemprotinc__B4_F4_T1_S2")
#TreeNames=("gc12_epemprotinc__B4_F4_T1_S2")

inFOLDER=/volatile/halld/home/jrpybus/analysis/jpsi/ver08/
#inFOLDER=/lustre19/expphy/volatile/halld/home/ehingerl/jpsi/trees/v8/tmp_D_B
inFOLDER_SIM=/w/halld-scshelf2101/halld2/home/jrpybus/analysis/jpsi/analysis/trees/DSelector/sim/SRC_CT/


volatileFolder=/lustre19/expphy/volatile/halld/home/ehingerl/jpsi/trees/v8/filtered_partial/noTrackShower
mkdir -p ${volatileFolder}
#for i in ${!Targets[@]}; do
#  INPUTFILE=${inFOLDER}/e_e_p_X*.root
#  INPUTFILE=${inFOLDER}/${Targets_names[$i]}/e_e_p_X/e_e_p_X_0902*.root
#  INPUTFILE=${inFOLDER}/${Targets_names[$i]}/e_e_p_X/e_e_p_X*.root
#  TREE=${volatileFolder}/data_tree_${Targets[$i]}.root
#  root -q -b 'filterAll_min_cuts.C("'${INPUTFILE}'","'${TREE}'","'${TreeNames[$i]}'")'
#done

TargetsSIM=("2H" "4He" "12C")
TargetsSIM=("12C")
TreeNames=("gc12_epemprotinc__B4_F4_T1_S2")
mixedStrings=("_mixed")
MFSRCStrings=("MF" "SRC")
for isMixed in ${mixedStrings[@]}; do
  for MFSRC in ${MFSRCStrings[@]}; do
    for i in ${!TargetsSIM[@]}; do
      if [[ ${TargetsSIM[$i]} != "2H" || ${MFSRC} != "SRC" ]]
      then
        INPUTFILE=${inFOLDER_SIM}/tree_DSelector_${TargetsSIM[$i]}_${MFSRC}_helicity${isMixed}.root
        TREE=${volatileFolder}/tree_DSelector_${TargetsSIM[$i]}_${MFSRC}_helicity${isMixed}.root
        root -q -b 'filterAll_min_cuts.C("'${INPUTFILE}'","'${TREE}'","'${TreeNames[$i]}'")'
      fi
    done
  done
done
wait