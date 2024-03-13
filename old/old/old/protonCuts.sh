#!/usr/bin/env bash

Targets=("D" "He" "C")
TreeNames=("gd_epemprotinc__B4_F4_T1_S2" "ghe_epemprotinc__B4_F4_T1_S2" "gc12_epemprotinc__B4_F4_T1_S2")
inFOLDER=files/fiducialCuts/negWeights
outFOLDER=files/PoverE_Fitting/preB_03/noCalCuts
pMissCut=5000
thetaCut=180
preBCut=0.03
#preBCut=0.04

for i in ${!Targets[@]}; do
  INPUTFILE=../${inFOLDER}/data_tree_${Targets[$i]}.root
  TREE=../${outFOLDER}/data_tree_${Targets[$i]}.root
  root -q -b 'protonCuts.C("'${INPUTFILE}'","'${TREE}'","'${TreeNames[$i]}'","'${pMissCut}'","'${thetaCut}'","'${preBCut}'")' &
done

INPUTFILE=../${inFOLDER}/sim_tree_He_MF.root
TREE=../${outFOLDER}/sim_tree_He_MF.root
root -q -b 'protonCuts.C("'${INPUTFILE}'","'${TREE}'","e_e_p_X","'${pMissCut}'","'${thetaCut}'","'${preBCut}'")' &

INPUTFILE=../${inFOLDER}/sim_tree_He_SRC.root
TREE=../${outFOLDER}/sim_tree_He_SRC.root
root -q -b 'protonCuts.C("'${INPUTFILE}'","'${TREE}'","e_e_p_X","'${pMissCut}'","'${thetaCut}'","'${preBCut}'")' &
wait