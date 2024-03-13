#!/usr/bin/env bash

Targets=("D" "He" "C")
TreeNames=("gd_epemprotinc__B4_F4_T1_S2" "ghe_epemprotinc__B4_F4_T1_S2" "gc12_epemprotinc__B4_F4_T1_S2")
FOLDERS=("files/PoverE/m3_p2_sigma/preB_03/Emiss_1")
#FOLDERS=("files/PoverE_simSigma/m3_p3_sigma/no_cut" "files/PoverE_simSigma/m3_p3_sigma/EMiss_1")
for j in ${!FOLDERS[@]}; do
  mkdir -p ../${FOLDERS[$j]}/Kmiss_cuts/Kmiss_0p3_upper ../${FOLDERS[$j]}/Kmiss_cuts/Kmiss_0p3_lower
  for i in ${!Targets[@]}; do
    INPUTFILE=../${FOLDERS[$j]}/data_tree_${Targets[$i]}.root
    TREEUpper=../${FOLDERS[$j]}/Kmiss_cuts/Kmiss_0p3_upper/data_tree_${Targets[$i]}.root
    TREELower=../${FOLDERS[$j]}/Kmiss_cuts/Kmiss_0p3_lower/data_tree_${Targets[$i]}.root
    root -q -b 'kMissCuts.C("'${INPUTFILE}'","'${TREELower}'","'${TREEUpper}'","0.3","'${TreeNames[$i]}'")'
  done
  INPUTFILE=../${FOLDERS[$j]}/sim_tree_He_MF.root
  TREEUpper=../${FOLDERS[$j]}/Kmiss_cuts/Kmiss_0p3_upper/sim_tree_He_MF.root
  TREELower=../${FOLDERS[$j]}/Kmiss_cuts/Kmiss_0p3_lower/sim_tree_He_MF.root
  root -q -b 'kMissCuts.C("'${INPUTFILE}'","'${TREELower}'","'${TREEUpper}'","0.3","e_e_p_X")'

  INPUTFILE=../${FOLDERS[$j]}/sim_tree_He_SRC.root
  TREEUpper=../${FOLDERS[$j]}/Kmiss_cuts/Kmiss_0p3_upper/sim_tree_He_SRC.root
  TREELower=../${FOLDERS[$j]}/Kmiss_cuts/Kmiss_0p3_lower/sim_tree_He_SRC.root
  root -q -b 'kMissCuts.C("'${INPUTFILE}'","'${TREELower}'","'${TREEUpper}'","0.3","e_e_p_X")'
done