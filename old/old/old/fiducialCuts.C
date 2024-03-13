//
// Created by Lucas Ehinger on 6/9/23.
//

#include "analyzeData.h"

void fiducialCuts(string inFileName, string outFileName, string treeName = "e_e_p_X")
{

  using namespace ROOT;
  using namespace std;

  EnableImplicitMT();
  TChain chain(treeName.c_str());
  chain.Add(inFileName.c_str());

  RDataFrame rdf_def(chain);

/*
  auto rdf_calhit = rdf_def.Filter("(((em_efcal!=0)||(em_ebcal!=0))&&((ep_efcal!=0)||(ep_ebcal!=0)))");
  auto rdf_PID = rdf_calhit.Filter("(fabs(ep_EoverP - 1) < 0.2) && (fabs(em_EoverP - 1) < 0.2)");
  auto rdf_vertex = rdf_PID.Filter("(zVertex > 51) && (zVertex < 79) && (xVertex*xVertex + yVertex*yVertex < 1*1)");;
  auto rdf_mass = rdf_vertex.Filter("(jpsi_m_kin > 2) && (jpsi_m_kin < 4)");
  //auto rdf_miss = rdf_mass.Filter("(jpsi_m_pair > 2.5) && (jpsi_m_pair < 3.5)").Filter("fabs(miss_m_kin - mN) < 1.");
  auto rdf_miss = rdf_mass.Filter("fabs(mN + beam_p4_kin.T() - jpsi_p4_kin.T() - p_p4_kin.T()) < 1.");
  auto rdf_final = rdf_miss.Filter("(theta_em > 2) && (theta_ep > 2) && (theta_p < 80) && (p_p > 0.4)").Filter("(unusedShowers == 0) && (unusedTracks == 0)");
*/
  auto rdf_final = rdf_def.Filter("(zVertex > 51) && (zVertex < 79) && (xVertex*xVertex + yVertex*yVertex < 1*1)")
          .Filter("(theta_em > 2) && (theta_ep > 2) && (theta_p > 2)")
          .Filter("(p_em > 0.4) && (p_ep > 0.4) && (p_p > 0.4)")
          .Filter("(unusedShowers == 0) && (unusedTracks == 0)")
          .Filter("(jpsi_m_pair > 1.5) && (jpsi_m_pair < 3.5)");

  rdf_final.Snapshot(treeName.c_str(),outFileName.c_str());
}
