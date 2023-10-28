#!/usr/bin/env bash

#Targets=("D" "He" "C")
Targets=("D")
Targets_names=("deuterium" "helium" "carbon")
TreeNames=("gd_epemprotinc__B4_F4_T1_S2" "ghe_epemprotinc__B4_F4_T1_S2" "gc12_epemprotinc__B4_F4_T1_S2")

inFOLDER=/volatile/halld/home/jrpybus/analysis/jpsi/ver07/
inFOLDER_SIM=/w/halld-scshelf2101/halld2/home/jrpybus/analysis/jpsi/analysis/trees/DSelector/sim/SRC_CT/
#outFOLDER=/lustre19/expphy/volatile/halld/home/ehingerl/jpsi/trees/v7/PoverE2/m3_p2_sigma/noTracks/preB_03/Emiss_1


numIters=3


outFOLDER=/lustre19/expphy/volatile/halld/home/ehingerl/jpsi/trees/v7/varyCuts

mkdir -p ${outFOLDER}
for i in ${!Targets[@]}; do
  INPUTFILE=${inFOLDER}/${Targets_names[$i]}//e_e_p_X/e_e_p_X_*.root
  TREE=${outFOLDER}/data_tree_${Targets[$i]}.root
  root -q -b 'filter_cutVary.C("'${INPUTFILE}'","'${TREE}'","'${TreeNames[$i]}'","'${numIters}'")'
done

TargetsSIM=("2H" "4He" "12C")
mixedStrings=("." "_mixed.")
MFSRCStrings=("MF" "SRC")

#    for isMixed in ${mixedStrings[@]}; do
#      for MFSRC in ${MFSRCStrings[@]}; do
#        for i in ${!TargetsSIM[@]}; do
#          if [[ ${TargetsSIM[$i]} != "2H" || ${MFSRC} != "SRC" ]]
#          then
#            INPUTFILE=${inFOLDER_SIM}/tree_DSelector_${TargetsSIM[$i]}_${MFSRC}_helicity${isMixed}root
#            TREE=${outFOLDER}/tree_DSelector_${TargetsSIM[$i]}_${MFSRC}_helicity${isMixed}root
#            root -q -b 'filterAll.C("'${INPUTFILE}'","'${TREE}'","'${TreeNames[$i]}'","'${trackShower_sel}'","'${preBCut}'","'${sigma_minus}'","'${sigma_plus}'","'${EMissCut}'")'
#          fi
#        done
#      done
#    done
wait