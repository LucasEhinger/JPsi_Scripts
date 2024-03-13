 #!/usr/bin/env bash

fcalMax=1.2335
fcalMin=0.8078
bcalMax=1.1729
bcalMin=0.8123

export outFOLDER=/lustre19/expphy/volatile/halld/home/ehingerl/jpsi/trees/v8/PoverE/m3_p2_sigma/noTracks/preB_0/Emiss_100/
mkdir -p ${outFOLDER}
./CalPoverEcuts.sh 0 ${fcalMax} ${fcalMin} ${bcalMax} ${bcalMin}


#Targets=("D" "He" "C")
Targets=("D")
TreeNames=("gd_epemprotinc__B4_F4_T1_S2" "ghe_epemprotinc__B4_F4_T1_S2" "gc12_epemprotinc__B4_F4_T1_S2")
TargetsSIM=("2H" "4He" "12C")
mixedStrings=("." "_mixed.")
MFSRCStrings=("MF" "SRC")

inFOLDER=${outFOLDER}

# Jackson: You probably don't need all these different cuts, so I've commented them out
# and only included the relevant ones below
#PreBCalCuts=("0.0" "0.025" "0.03" "0.035" "0.04")
#EMissCuts=("0.5" "1" "1.5" "2" "3" "4" "100")
PreBCalCuts=("0.03" "0.0")
EMissCuts=("1" "100")

thetaCut=180

for preBCut in ${PreBCalCuts[@]}; do
  for EMissCut in ${EMissCuts[@]}; do
    outFOLDER=/lustre19/expphy/volatile/halld/home/ehingerl/jpsi/trees/v8/PoverE/m3_p2_sigma/noTracks/preB_${preBCut#"0."}/Emiss_${EMissCut//[.]/p}/
    if [ "${outFOLDER}" != "${inFOLDER}" ]; then
      mkdir -p ${outFOLDER}

      for i in ${!Targets[@]}; do
        INPUTFILE=${inFOLDER}/data_tree_${Targets[$i]}.root
        TREE=${outFOLDER}/data_tree_${Targets[$i]}.root
        root -q -b 'protonCuts.C("'${INPUTFILE}'","'${TREE}'","'${TreeNames[$i]}'","'${EMissCut}'","'${thetaCut}'","'${preBCut}'")' &
      done

#      for isMixed in ${mixedStrings[@]}; do
#        for MFSRC in ${MFSRCStrings[@]}; do
#          for i in ${!TargetsSIM[@]}; do
#            INPUTFILE=${inFOLDER}/tree_DSelector_${TargetsSIM[$i]}_${MFSRC}_helicity${isMixed}root
#            TREE=${outFOLDER}/tree_DSelector_${TargetsSIM[$i]}_${MFSRC}_helicity${isMixed}root
#            if [[ ${TargetsSIM[$i]} != "2H" || ${MFSRC} != "SRC" ]]
#            then
#              root -q -b 'protonCuts.C("'${INPUTFILE}'","'${TREE}'","'${TreeNames[$i]}'","'${EMissCut}'","'${thetaCut}'","'${preBCut}'")' &
#            fi
#          done
#        done
#      done
      wait
    fi
  done
done
wait