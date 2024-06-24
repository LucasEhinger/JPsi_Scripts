//
// Created by Lucas Ehinger on 10/27/23.
//

#include "analyzeData.h"
using namespace ROOT;
using namespace std;

void makeResPlots(RNode rdf_in, TDirectory *currentDirectory, string var, double min, double max, int nHists = 5,
                  int nBins = 1000) {

  TDirectory *dir = currentDirectory->mkdir(var.c_str());
  dir->cd();

  TH1D hist = *rdf_in.Histo1D({var.c_str(), var.c_str(), nBins, -1, 1}, var.c_str(), "accidweight");
  hist.Write();

  string name               = var + "_restricted";
  TH1D hist_mass_restrected = *rdf_in.Filter("(jpsi_m_true>3)&&(jpsi_m_true<3.2)")
                                   .Histo1D({name.c_str(), var.c_str(), nBins, -1, 1}, var.c_str(), "accidweight");
  hist_mass_restrected.Write();

  map<string, string> delta_true_Map;
  delta_true_Map["delta_kmiss"]      = "kmiss_true";
  delta_true_Map["delta_alpha_miss"] = "alpha_miss_true";
  delta_true_Map["delta_t"]          = "t_kin_thrown";
  delta_true_Map["delta_t_lc"]       = "t_kin_thrown";
  delta_true_Map["delta_pT"]         = "tot_perp_true";

  double delta_range = 1;
  if (var == "delta_kmiss" || var == "delta_alpha_miss" || var == "delta_pT")
    delta_range = 0.3;

  for (int i = 0; i < nHists; i++) {
    string cut = "(" + delta_true_Map[var] + " > " + to_string(min + i * (max - min) / nHists) + ") && (" +
                 delta_true_Map[var] + " < " + to_string(min + (i + 1) * (max - min) / nHists) + ")";
    name = var + "_bin_" + to_string(i);
    TH1D hist =
        *rdf_in.Filter(cut)
             .Filter("(jpsi_m_true>3)&&(jpsi_m_true<3.2)")
             .Histo1D({name.c_str(), var.c_str(), nBins, -delta_range, delta_range}, var.c_str(), "accidweight");
    hist.Write();
  }

  TH1D hist_true = *rdf_in.Histo1D({delta_true_Map[var].c_str(), delta_true_Map[var].c_str(), nBins, min, max},
                                   delta_true_Map[var].c_str(), "accidweight");
  hist_true.Write();

  string var_meas = delta_true_Map[var].substr(0, delta_true_Map[var].size() - 5);
  if (var == "delta_t_lc" || var == "delta_t")
    var_meas = delta_true_Map[var].substr(0, delta_true_Map[var].size() - 7);

  TH1D hist_meas =
      *rdf_in.Histo1D({var_meas.c_str(), var_meas.c_str(), nBins, min, max}, var_meas.c_str(), "accidweight");
  hist_meas.Write();

  TH2D hist2D =
      *rdf_in.Histo2D({(delta_true_Map[var] + "_vs_" + var_meas).c_str(),
                       (delta_true_Map[var] + "_vs_" + var_meas + ";" + delta_true_Map[var] + ";" + var_meas).c_str(),
                       nBins, min, max, nBins, min, max},
                      delta_true_Map[var].c_str(), var_meas.c_str(), "accidweight");
  hist2D.Write();
}

void make_sim_resolution_hists(string inFileName, string outFileName, string treeName = "e_e_p_X") {

  using namespace ROOT;
  using namespace std;

  EnableImplicitMT();
  TChain chain(treeName.c_str());
  chain.Add(inFileName.c_str());

  RDataFrame rdf_def(chain);

  auto rdf_final =
      rdf_def.Filter("(E_gamma>7)")
          .Define("jpsi_p4_true", "thrownElectron + thrownPositron")
          .Define("tot_p4_true", "(jpsi_p4_true+thrownProton-thrownBeam)")
          .Define("tot_perp_true", "(tot_p4_true.Perp())")
          .Define("tot_pMinus_true", "(tot_p4_true.Minus())")
          .Define("alpha_miss_true", "(tot_pMinus_true/mN)")
          .Define("kmiss_true",
                  "mN*sqrt((mN*mN + tot_p4_true.Perp2())/(tot_p4_true.Minus()*(2*mN - tot_p4_true.Minus())) - 1)")
          .Define("delta_kmiss", "kmiss_true - kmiss")
          .Define("delta_alpha_miss", "alpha_miss_true - alpha_miss")
          .Define("delta_t", "t_kin_thrown - t_kin")
          .Define("delta_t_lc", "t_kin_thrown - t_kin_lc")
          .Define("delta_pT", "tot_perp_true - tot_perp")
          .Define("jpsi_m_true", "jpsi_p4_true.M()");

  // Start defining histograms

  TFile *histFile = new TFile(outFileName.c_str(), "RECREATE");

  histFile->cd();

  string variables[] = {"delta_kmiss", "delta_alpha_miss", "delta_t", "delta_t_lc", "delta_pT"};

  map<string, array<double, 2>> plotRangeMap;
  plotRangeMap["delta_kmiss"]      = {0.0, 1};
  plotRangeMap["delta_alpha_miss"] = {0.8, 1.5};
  plotRangeMap["delta_t"]          = {-6.0, 0.0};
  plotRangeMap["delta_t_lc"]       = {-6.0, 0.0};
  plotRangeMap["delta_pT"]         = {0, 0.6};

  for (string var : variables) {
    makeResPlots(rdf_final, histFile, var, plotRangeMap[var][0], plotRangeMap[var][1], 10);
  }
}
