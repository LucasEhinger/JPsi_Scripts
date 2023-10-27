#!/usr/bin/env bash
FOLDER=/lustre19/expphy/volatile/halld/home/ehingerl/jpsi/trees/v8/defined/

INPUTFILE=/volatile/halld/home/jrpybus/analysis/jpsi/ver08/deuterium/e_e_p_X/e_e_p_X_*.root
TREE=${FOLDER}/data_tree_D.root

root -q -b 'filter.C("'${INPUTFILE}'","'${TREE}'","gd_epemprotinc__B4_F4_T1_S2")'

