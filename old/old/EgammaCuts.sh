#!/usr/bin/env bash

Targets=("D" "He" "C")
TreeNames=("gd_epemprotinc__B4_F4_T1_S2" "ghe_epemprotinc__B4_F4_T1_S2" "gc12_epemprotinc__B4_F4_T1_S2")

FOLDERS=("/lustre19/expphy/volatile/halld/home/ehingerl/jpsi/trees/v7/PoverE/m3_p2_sigma/withTracks/preB_03/Emiss_1/"\
 "/lustre19/expphy/volatile/halld/home/ehingerl/jpsi/trees/v7/PoverE/m3_p2_sigma/noTracks/preB_03/Emiss_1/")
TargetsSIM=("2H" "4He" "12C")
mixedStrings=("." "_mixed.")
MFSRCStrings=("MF" "SRC")

#EgammaVals=("8.0" "8.05" "8.1" "8.15" "8.2" "8.25" "9.0")
EgammaVals=("8.2" "9.5")
#EgammaVals=("9.5")

#FOLDERS=("files/PoverE_simSigma/m3_p3_sigma/no_cut" "files/PoverE_simSigma/m3_p3_sigma/EMiss_1")
for j in ${!FOLDERS[@]}; do
  for EgammaVal in ${EgammaVals[@]}; do
    mkdir -p ${FOLDERS[$j]}/EgammaCuts/${EgammaVal//[.]/p}_upper ${FOLDERS[$j]}/EgammaCuts/${EgammaVal//[.]/p}_lower
    for i in ${!Targets[@]}; do
      INPUTFILE=${FOLDERS[$j]}/data_tree_${Targets[$i]}.root
      TREEUpper=${FOLDERS[$j]}/EgammaCuts/${EgammaVal//[.]/p}_upper/data_tree_${Targets[$i]}.root
      TREELower=${FOLDERS[$j]}/EgammaCuts/${EgammaVal//[.]/p}_lower/data_tree_${Targets[$i]}.root
      root -q -b 'EgammaCuts.C("'${INPUTFILE}'","'${TREELower}'","'${TREEUpper}'","'${EgammaVal}'","7","'${TreeNames[$i]}'")'
    done

    for isMixed in ${mixedStrings[@]}; do
      for MFSRC in ${MFSRCStrings[@]}; do
        for i in ${!TargetsSIM[@]}; do
          INPUTFILE=${FOLDERS[$j]}/tree_DSelector_${TargetsSIM[$i]}_${MFSRC}_helicity${isMixed}root
          TREEUpper=${FOLDERS[$j]}/EgammaCuts/${EgammaVal//[.]/p}_upper/tree_DSelector_${TargetsSIM[$i]}_${MFSRC}_helicity${isMixed}root
          TREELower=${FOLDERS[$j]}/EgammaCuts/${EgammaVal//[.]/p}_lower/tree_DSelector_${TargetsSIM[$i]}_${MFSRC}_helicity${isMixed}root
          if [[ ${TargetsSIM[$i]} != "2H" || ${MFSRC} != "SRC" ]]
          then
            root -q -b 'EgammaCuts.C("'${INPUTFILE}'","'${TREELower}'","'${TREEUpper}'","'${EgammaVal}'","7","'${TreeNames[$i]}'")'
          fi
        done
      done
    done
  done
done

wait