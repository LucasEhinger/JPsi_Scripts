//
// Created by Lucas Ehinger on 10/27/23.
//

#include "analyzeData.h"
using namespace ROOT;
using namespace std;

void make2DPlots(RNode rdf_in, TDirectory* currentDirectory,string mass_variable){

  TDirectory* dir = currentDirectory->mkdir(mass_variable.c_str());
  dir->cd();

  TH2D h_2D_t = *rdf_in.Histo2D({(mass_variable+"_vs_t").c_str(),("; -t [GeV^2];"+mass_variable+"[GeV]").c_str(),100,0,6,1000,2.6,3.4},"t_kin_minus",mass_variable.c_str(),"accidweight");
  h_2D_t.Write();

  TH2D h_2D_alpha_miss = *rdf_in.Histo2D({(mass_variable+"_vs_alpha_miss").c_str(),("; alpha_miss [GeV];"+mass_variable+"[GeV]").c_str(),100,0.8,1.8,1000,2.6,3.4},"alpha_miss",mass_variable.c_str(),"accidweight");
  h_2D_alpha_miss.Write();

  TH2D h_2D_kmiss = *rdf_in.Histo2D({(mass_variable+"_vs_kmiss").c_str(),("; kmiss [GeV/c];"+mass_variable+"[GeV]").c_str(),100,0,1,1000,2.6,3.4},"kmiss",mass_variable.c_str(),"accidweight");
  h_2D_kmiss.Write();

  TH2D h_2D_pT = *rdf_in.Histo2D({(mass_variable+"_vs_pT").c_str(),("; pT [GeV/c];"+mass_variable+"[GeV]").c_str(),100,0,0.8,1000,2.6,3.4},"tot_perp",mass_variable.c_str(),"accidweight");
  h_2D_pT.Write();
}

void make_sim_mass_hists(string inFileName, string outFileName, string treeName = "e_e_p_X")
{

  using namespace ROOT;
  using namespace std;

  EnableImplicitMT();
  TChain chain(treeName.c_str());
  chain.Add(inFileName.c_str());

  RDataFrame rdf_def(chain);

  auto rdf_final=rdf_def.Filter("(E_gamma>7)");

  //Start defining histograms

  TFile * histFile = new TFile(outFileName.c_str(),"RECREATE");

  histFile->cd();

  make2DPlots(rdf_final, histFile, "jpsi_m_pair");
  make2DPlots(rdf_final, histFile, "jpsi_m_kin");
}
