//
// Created by Lucas Ehinger on 6/9/23.
//

#include "analyzeData.h"

void alphaMiss_Cuts(string inFileName, string outFileNameLower, string outFileNameUpper, string alphaMiss_Limit="1.3", string treeName = "e_e_p_X")
{

  using namespace ROOT;
  using namespace std;

  EnableImplicitMT();
  TChain chain(treeName.c_str());
  chain.Add(inFileName.c_str());

  RDataFrame rdf_final(chain);

  string cutLower="(alpha_miss<"+alphaMiss_Limit+")";
  string cutUpper="(alpha_miss>"+alphaMiss_Limit+")";
  auto rdf_lower = rdf_final.Filter(cutLower.c_str());
  auto rdf_upper = rdf_final.Filter(cutUpper.c_str());

  rdf_lower.Snapshot(treeName.c_str(),outFileNameLower.c_str());
  rdf_upper.Snapshot(treeName.c_str(),outFileNameUpper.c_str());
}
