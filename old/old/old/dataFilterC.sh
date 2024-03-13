#!/usr/bin/env bash
FOLDER=trees/v5/orig/

INPUTFILE=/volatile/halld/home/jrpybus/analysis/jpsi/ver05/carbon/e_e_p_X/e_e_p_X_*.root

TREE=../${FOLDER}/data_tree_C.root

root -q -b 'filter.C("'${INPUTFILE}'","'${TREE}'","gc12_epemprotinc__B4_F4_T1_S2")'
