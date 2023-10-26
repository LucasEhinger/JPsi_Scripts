//
// Created by Lucas Ehinger on 6/9/23.
//

#include "analyzeData.h"

void EgammaCuts(string inFileName, string outFileNameLower, string outFileNameUpper, string EGammaLimit="9", string EgammaLowCut="7", string treeName = "e_e_p_X")
{

  using namespace ROOT;
  using namespace std;

  EnableImplicitMT();
  TChain chain(treeName.c_str());
  chain.Add(inFileName.c_str());

  RDataFrame rdf_def(chain);

  string cutLower="((E_gamma<"+EGammaLimit+")&&(E_gamma>"+EgammaLowCut+"))";
  string cutUpper="(E_gamma>"+EGammaLimit+")";
  auto rdf_lower = rdf_def.Filter(cutLower.c_str());//"(E_gamma<8.5)"
  auto rdf_upper = rdf_def.Filter(cutUpper.c_str());

  rdf_lower.Snapshot(treeName.c_str(),outFileNameLower.c_str());
  rdf_upper.Snapshot(treeName.c_str(),outFileNameUpper.c_str());
}
