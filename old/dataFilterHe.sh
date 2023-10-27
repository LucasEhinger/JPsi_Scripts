#!/usr/bin/env bash
FOLDER=trees/v5/orig/

INPUTFILE=/volatile/halld/home/jrpybus/analysis/jpsi/ver05/helium/e_e_p_X/e_e_p_X_*.root


TREE=../${FOLDER}/data_tree_He.root

root -q -b 'filter.C("'${INPUTFILE}'","'${TREE}'","ghe_epemprotinc__B4_F4_T1_S2")'
