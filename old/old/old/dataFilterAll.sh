#!/usr/bin/env bash
FOLDER=/lustre19/expphy/volatile/halld/home/ehingerl/jpsi/trees/v7/defined/

INPUTFILE=/volatile/halld/home/jrpybus/analysis/jpsi/ver07/deuterium/e_e_p_X/e_e_p_X_*.root
TREE=${FOLDER}/data_tree_D.root
root -q -b 'filter.C("'${INPUTFILE}'","'${TREE}'","gd_epemprotinc__B4_F4_T1_S2")'

INPUTFILE=/volatile/halld/home/jrpybus/analysis/jpsi/ver07/carbon/e_e_p_X/e_e_p_X_*.root
TREE=${FOLDER}/data_tree_C.root
root -q -b 'filter.C("'${INPUTFILE}'","'${TREE}'","gc12_epemprotinc__B4_F4_T1_S2")'


INPUTFILE=/volatile/halld/home/jrpybus/analysis/jpsi/ver07/helium/e_e_p_X/e_e_p_X_*.root
TREE=${FOLDER}/data_tree_He.root
root -q -b 'filter.C("'${INPUTFILE}'","'${TREE}'","ghe_epemprotinc__B4_F4_T1_S2")'

wait
