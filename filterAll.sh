#!/usr/bin/env bash

Targets=("D" "He" "C")
#Targets=("He" "C")
Targets=("C")
Targets_names=("deuterium" "helium" "carbon")
#Targets_names=("helium" "carbon")
Targets_names=("carbon")
TreeNames=("gd_epemprotinc__B4_F4_T1_S2" "ghe_epemprotinc__B4_F4_T1_S2" "gc12_epemprotinc__B4_F4_T1_S2")
#TreeNames=("ghe_epemprotinc__B4_F4_T1_S2" "gc12_epemprotinc__B4_F4_T1_S2")
TreeNames=("gc12_epemprotinc__B4_F4_T1_S2")
inFOLDER=/volatile/halld/home/jrpybus/analysis/jpsi/ver08/
inFOLDER_SIM=/w/halld-scshelf2101/halld2/home/jrpybus/analysis/jpsi/analysis/trees/DSelector/sim/SRC_CT/
#outFOLDER=/lustre19/expphy/volatile/halld/home/ehingerl/jpsi/trees/v7/PoverE2/m3_p2_sigma/noTracks/preB_03/Emiss_1


PreBCalCut=0.03
EMissCut=1
trackShower_sel=0
sigma_minus=-3
sigma_plus=2

#Loose Cuts
#PreBCalCut=0.025
#EMissCut=1.5
#trackShower_sel=0
#sigma_minus=-3.5
#sigma_plus=2.5

outFOLDER=/lustre19/expphy/volatile/halld/home/ehingerl/jpsi/trees/v8/filtered/noTrackShower
workFolder=/w/halld-scshelf2101/halld2/home/ehingerl/analysis/jpsi/trees/v8/filtered/noTrackShower
mkdir -p ${outFOLDER}
for i in ${!Targets[@]}; do
  INPUTFILE=${inFOLDER}/${Targets_names[$i]}/e_e_p_X/e_e_p_X*.root
  TREE=${outFOLDER}/data_tree_${Targets[$i]}.root
  HISTFILE=${workFolder}/data_hist_cutflow_${Targets[$i]}.root
  root -q -b 'filterAll.C("'${INPUTFILE}'","'${TREE}'","'${HISTFILE}'","'${TreeNames[$i]}'","'${trackShower_sel}'","'${PreBCalCut}'","'${sigma_minus}'","'${sigma_plus}'","'${EMissCut}'")'
done

TargetsSIM=("2H" "4He" "12C")
mixedStrings=("_mixed.")
MFSRCStrings=("MF" "SRC")
#for isMixed in ${mixedStrings[@]}; do
#  for MFSRC in ${MFSRCStrings[@]}; do
#    for i in ${!TargetsSIM[@]}; do
#      if [[ ${TargetsSIM[$i]} != "2H" || ${MFSRC} != "SRC" ]]
#      then
#        INPUTFILE=${inFOLDER_SIM}/tree_DSelector_${TargetsSIM[$i]}_${MFSRC}_helicity${isMixed}root
#        TREE=${outFOLDER}/tree_DSelector_${TargetsSIM[$i]}_${MFSRC}_helicity${isMixed}root
#        HISTFILE=${workFolder}/hist_cutflow_DSelector_${TargetsSIM[$i]}_${MFSRC}_helicity${isMixed}root
#        root -q -b 'filterAll.C("'${INPUTFILE}'","'${TREE}'","'${TreeNames[$i]}'","'${trackShower_sel}'","'${PreBCalCut}'","'${sigma_minus}'","'${sigma_plus}'","'${EMissCut}'")'
#      fi
#    done
#  done
#done
#wait