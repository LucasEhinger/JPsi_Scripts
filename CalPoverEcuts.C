//
// Created by Lucas Ehinger on 6/9/23.
//

#include "analyzeData.h"

bool passEoverP(double p, double Efcal, double Ebcal, bool isFCAL, double fcalMin, double fcalMax, double bcalMin, double bcalMax)
{
  if (isFCAL)
    {
      return ((p/Efcal > fcalMin) && (p/Efcal < fcalMax));
    }
  else 
    return ((p/Ebcal > bcalMin) && (p/Ebcal < bcalMax));
}

void CalPoverEcuts(string inFileName, string outFileName, string treeName , string fcalMin="0.8078", string fcalMax="1.3186",
                string bcalMin="0.8123", string bcalMax="1.2450") {

  using namespace ROOT;
  using namespace std;

  EnableImplicitMT();
  TChain chain(treeName.c_str());
  chain.Add(inFileName.c_str());

  RDataFrame rdf_def(chain);

  auto rdf_final = rdf_def.Filter("(jpsi_m_kin > 2) && (jpsi_m_kin < 4)")
          .Define("em_isFCAL","em_efcal > em_ebcal")
          .Define("ep_isFCAL","ep_efcal > ep_ebcal")
          .Filter("(passEoverP(em_p4_kin.P(),em_efcal,em_ebcal,em_isFCAL," + fcalMin + "," + fcalMax + ","  + bcalMin + "," + bcalMax + "))")
          .Filter("(passEoverP(ep_p4_kin.P(),ep_efcal,ep_ebcal,ep_isFCAL," + fcalMin + "," + fcalMax + ","  + bcalMin + "," + bcalMax + "))");

  rdf_final.Snapshot(treeName.c_str(),outFileName.c_str());


}
