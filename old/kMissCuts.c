//
// Created by Lucas Ehinger on 6/9/23.
//

#include "analyzeData.h"

void kMissCuts(string inFileName, string outFileNameLower, string outFileNameUpper, string kmissLimit="9", string treeName = "e_e_p_X")
{

  using namespace ROOT;
  using namespace std;

  EnableImplicitMT();
  TChain chain(treeName.c_str());
  chain.Add(inFileName.c_str());

  RDataFrame rdf_def(chain);

  auto rdf_final=rdf_def.Redefine("kmiss","mN*sqrt((mN*mN + tot_p4_kin.Perp2())/(tot_p4_kin.Minus()*(2*mN - tot_p4_kin.Minus())) - 1)");

  string cutLower="(kmiss<"+kmissLimit+")";
  string cutUpper="(kmiss>"+kmissLimit+")";
  auto rdf_lower = rdf_final.Filter(cutLower.c_str());
  auto rdf_upper = rdf_final.Filter(cutUpper.c_str());


  rdf_upper.Snapshot(treeName.c_str(),outFileNameUpper.c_str());
  rdf_lower.Snapshot(treeName.c_str(),outFileNameLower.c_str());
}
