//
// Created by Lucas Ehinger on 6/9/23.
//

#include "analyzeData.h"

void protonCuts(string inFileName, string outFileName, string treeName = "e_e_p_X", string pMissCut="1", string thetaCut="80", string preBCut="50")
{

  using namespace ROOT;
  using namespace std;

  EnableImplicitMT();
  TChain chain(treeName.c_str());
  chain.Add(inFileName.c_str());

  RDataFrame rdf_def(chain);

//  auto rdf_final = rdf_def.Filter("fabs(mN + beam_p4_kin.T() - jpsi_p4_kin.T() - p_p4_kin.T()) < 1.")
//          .Filter("(theta_p < 80)");

  string pMissFilter="(fabs(p_miss_stat_p) < " +pMissCut + ")";
  string thetaFilter="(theta_p < " +thetaCut + ")";
//  preBCut = to_string(stof(preBCut)/1000);
  string preBFilter="((em_eprebcal_sinTheta > " +preBCut + ") || (ep_eprebcal_sinTheta > " +preBCut + "))";
//  auto rdf_final = rdf_def.Filter("(theta_p < 40)");
  auto rdf_final = rdf_def.Filter(pMissFilter.c_str()).Filter(thetaFilter.c_str()).Filter(preBFilter.c_str());

  rdf_final.Snapshot(treeName.c_str(),outFileName.c_str());

}
