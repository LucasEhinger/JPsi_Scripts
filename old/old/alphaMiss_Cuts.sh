#!/usr/bin/env bash

Targets=("D" "He" "C")
TreeNames=("gd_epemprotinc__B4_F4_T1_S2" "ghe_epemprotinc__B4_F4_T1_S2" "gc12_epemprotinc__B4_F4_T1_S2")
FOLDERS=("/lustre19/expphy/volatile/halld/home/ehingerl/jpsi/trees/v7/PoverE/m3_p2_sigma/noTracks/preB_03/Emiss_1/"\
 "/lustre19/expphy/volatile/halld/home/ehingerl/jpsi/trees/v7/PoverE/m3_p2_sigma/withTracks/preB_03/Emiss_1/")
TargetsSIM=("2H" "4He" "12C")
mixedStrings=("." "_mixed.")
MFSRCStrings=("MF" "SRC")

AlphaMissVals=("1.25")

#FOLDERS=("files/PoverE_simSigma/m3_p3_sigma/no_cut" "files/PoverE_simSigma/m3_p3_sigma/EMiss_1")
for j in ${!FOLDERS[@]}; do
  for AlphaMissVal in ${AlphaMissVals[@]}; do
    mkdir -p ${FOLDERS[$j]}/AlphaMissVals/${AlphaMissVal//[.]/p}_upper ${FOLDERS[$j]}/AlphaMissVals/${AlphaMissVal//[.]/p}_lower
    for i in ${!Targets[@]}; do
      INPUTFILE=${FOLDERS[$j]}/data_tree_${Targets[$i]}.root
      TREEUpper=${FOLDERS[$j]}/AlphaMissVals/${AlphaMissVal//[.]/p}_upper/data_tree_${Targets[$i]}.root
      TREELower=${FOLDERS[$j]}/AlphaMissVals/${AlphaMissVal//[.]/p}_lower/data_tree_${Targets[$i]}.root
      root -q -b 'alphaMiss_Cuts.C("'${INPUTFILE}'","'${TREELower}'","'${TREEUpper}'","'${AlphaMissVal}'","'${TreeNames[$i]}'")' &
    done

    for isMixed in ${mixedStrings[@]}; do
      for MFSRC in ${MFSRCStrings[@]}; do
        for i in ${!TargetsSIM[@]}; do
          INPUTFILE=${FOLDERS[$j]}/tree_DSelector_${TargetsSIM[$i]}_${MFSRC}_helicity${isMixed}root
          TREEUpper=${FOLDERS[$j]}/AlphaMissVals/${AlphaMissVal//[.]/p}_upper/tree_DSelector_${TargetsSIM[$i]}_${MFSRC}_helicity${isMixed}root
          TREELower=${FOLDERS[$j]}/AlphaMissVals/${AlphaMissVal//[.]/p}_lower/tree_DSelector_${TargetsSIM[$i]}_${MFSRC}_helicity${isMixed}root
          if [[ ${TargetsSIM[$i]} != "2H" || ${MFSRC} != "SRC" ]]
          then
            root -q -b 'alphaMiss_Cuts.C("'${INPUTFILE}'","'${TREELower}'","'${TREEUpper}'","'${AlphaMissVal}'","'${TreeNames[$i]}'")' &
          fi
        done
      done
    done
  done
done

wait