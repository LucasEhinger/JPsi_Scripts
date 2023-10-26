#!/usr/bin/env bash

Targets=("D" "He" "C")
Targets_names=("deuterium" "helium" "carbon")
TreeNames=("gd_epemprotinc__B4_F4_T1_S2" "ghe_epemprotinc__B4_F4_T1_S2" "gc12_epemprotinc__B4_F4_T1_S2")

inFOLDER=/volatile/halld/home/jrpybus/analysis/jpsi/ver07/
inFOLDER_SIM=/w/halld-scshelf2101/halld2/home/jrpybus/analysis/jpsi/analysis/trees/DSelector/sim/SRC_CT/
#outFOLDER=/lustre19/expphy/volatile/halld/home/ehingerl/jpsi/trees/v7/PoverE2/m3_p2_sigma/noTracks/preB_03/Emiss_1

fcalMax=1.2335
fcalMin=0.8078
bcalMax=1.1729
bcalMin=0.8123

PreBCalCuts=("0.03")
EMissCuts=("1")
thetaCut=180

for preBCut in ${PreBCalCuts[@]}; do
  for EMissCut in ${EMissCuts[@]}; do
    outFOLDER=/lustre19/expphy/volatile/halld/home/ehingerl/jpsi/trees/v7/PoverE3/m3_p2_sigma/noTracks/preB_${preBCut#"0."}/Emiss_${EMissCut//[.]/p}/
    mkdir -p ${outFOLDER}
    for i in ${!Targets[@]}; do
      INPUTFILE=${inFOLDER}/${Targets_names[$i]}//e_e_p_X/e_e_p_X_*.root
      TREE=${outFOLDER}/data_tree_${Targets[$i]}.root
      root -q -b 'filterAll.C("'${INPUTFILE}'","'${TREE}'","'${TreeNames[$i]}'","'${fcalMin}'","'${fcalMax}'","'${bcalMin}'","'${bcalMax}'","'${EMissCut}'","'${thetaCut}'","'${preBCut}'")'
    done

    TargetsSIM=("2H" "4He" "12C")
    mixedStrings=("." "_mixed.")
    MFSRCStrings=("MF" "SRC")

    for isMixed in ${mixedStrings[@]}; do
      for MFSRC in ${MFSRCStrings[@]}; do
        for i in ${!TargetsSIM[@]}; do
          if [[ ${TargetsSIM[$i]} != "2H" || ${MFSRC} != "SRC" ]]
          then
            INPUTFILE=${inFOLDER_SIM}/tree_DSelector_${TargetsSIM[$i]}_${MFSRC}_helicity${isMixed}root
            TREE=${outFOLDER}/tree_DSelector_${TargetsSIM[$i]}_${MFSRC}_helicity${isMixed}root
            root -q -b 'filterAll.C("'${INPUTFILE}'","'${TREE}'","'${TreeNames[$i]}'","'${fcalMin}'","'${fcalMax}'","'${bcalMin}'","'${bcalMax}'","'${EMissCut}'","'${thetaCut}'","'${preBCut}'")'
          fi
        done
      done
    done
  done
done
wait