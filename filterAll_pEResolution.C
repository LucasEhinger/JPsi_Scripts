#include "analyzeData.h"

bool passEoverP(double p, double Efcal, double Ebcal, bool isFCAL, double sigma_minus, double sigma_plus){
  double fcal_mu=1.06319717;
  double fcal_sigma=0.085128472;
  double bcal_mu=1.028670304;
  double bcal_sigma=0.072119971;

  if (isFCAL)
  {
    return ((p/Efcal > fcal_mu + sigma_minus * fcal_sigma) && (p/Efcal < fcal_mu + sigma_plus * fcal_sigma));
  }
  else
    return ((p/Ebcal > bcal_mu + sigma_minus * bcal_sigma) && (p/Ebcal < bcal_mu + sigma_plus * bcal_sigma));
}



void makePoverEPlots_thetaCut(RNode rdf_in, string thetaMin, string thetaMax, string p_min, string p_max) {
  string theta_em_cut = "em_theta > " + thetaMin + " && em_theta < " + thetaMax;
  string theta_ep_cut = "ep_theta > " + thetaMin + " && ep_theta < " + thetaMax;
  string p_ep_cut = "ep_p > " + p_min + " && ep_p < " + p_max;
  string p_em_cut = "em_p > " + p_min + " && em_p < " + p_max;

  string em_cut = "("+ theta_em_cut + ") && (" + p_em_cut + ")";
  string ep_cut = "("+ theta_ep_cut + ") && (" + p_ep_cut + ")";

  string title = "P/E ["+thetaMin + " < #theta < " + thetaMax + "]" + "[" + p_min + " < p < " + p_max + "]";
  string name = "PoverE_"+thetaMin+"_"+thetaMax+"_"+p_min+"_"+p_max;

  string em_isFCAL = "em_isFCAL==0";
  string ep_isFCAL = "ep_isFCAL==0";
  if (stod(thetaMax) <= 11)
    em_isFCAL = "em_isFCAL>0";
    ep_isFCAL = "ep_isFCAL>0";


  TH1D h_fcal_em_PoverE = *rdf_in.Filter(em_cut.c_str()).Filter(em_isFCAL.c_str()).Histo1D(PE_Ratio_model,"em_PoverE","accidweight");
  TH1D h_fcal_ep_PoverE = *rdf_in.Filter(ep_cut.c_str()).Filter(ep_isFCAL.c_str()).Histo1D(PE_Ratio_model,"ep_PoverE","accidweight");
  TH1D h_fcal_lep_PoverE = h_fcal_em_PoverE+h_fcal_ep_PoverE;
  h_fcal_lep_PoverE.SetName(name.c_str());
  h_fcal_lep_PoverE.SetTitle(title.c_str());
  h_fcal_lep_PoverE.Write();
}
void makePoverEPlots(RNode rdf_in) {
  TH1D h_em_PoverE = *rdf_in.Histo1D(PE_Ratio_model,"em_PoverE","accidweight");
  h_em_PoverE.SetName("em_PoverE");
  h_em_PoverE.SetTitle("P/E");
  h_em_PoverE.Write();

  TH1D h_ep_PoverE = *rdf_in.Histo1D(PE_Ratio_model,"ep_PoverE","accidweight");
  h_ep_PoverE.SetName("ep_PoverE");
  h_ep_PoverE.SetTitle("P/E");
  h_ep_PoverE.Write();

  TH1D h_lep_PoverE = h_em_PoverE+h_ep_PoverE;
  h_lep_PoverE.SetName("lep_PoverE");
  h_lep_PoverE.SetTitle("P/E");
  h_lep_PoverE.Write();

  TH2D h_PoverE_2D = *rdf_in.Histo2D(EP_2DModel,"em_PoverE","ep_PoverE","accidweight");
  h_PoverE_2D.SetName("PoverE_2D");
  h_PoverE_2D.SetTitle("P/E");
  h_PoverE_2D.Write();

  vector<string> thetaCuts = {"0","3","5","8","11","15","20","25","30","35","40","45","50","55","60","65","70","75","80","85","90","95","100","105","110","115","120","125"};
  vector<string> pCuts = {"0.4", "1.6", "2.8", "4.0", "5.2", "6.4", "7.6", "8.8", "10.0"};
  for (int i=0; i<thetaCuts.size()-1; i++)
  {
    for (int j=0; j<pCuts.size()-1; j++)
    {
      makePoverEPlots_thetaCut(rdf_in,thetaCuts[i],thetaCuts[i+1],pCuts[j],pCuts[j+1]);
    }
  }
}


void makeAllPlots(RNode rdf_in, TDirectory* currentDirectory,string track_shower_cut="",
                  string preBCut="0.030", string sigma_minus="-3", string sigma_plus="2", string EMissCut="1") {

  auto rdf_final=rdf_in.Filter("(jpsi_m_pair > 2) && (jpsi_m_pair < 3.5)")
          .Filter("(zVertex > 51) && (zVertex < 79) && (xVertex*xVertex + yVertex*yVertex < 1*1)")
          .Filter("(em_theta > 2) && (ep_theta > 2) && (p_theta > 2)")
          .Filter("(em_p > 0.4) && (ep_p > 0.4) && (p_p > 0.4)")
          .Filter(track_shower_cut.c_str())
          .Filter("(em_eprebcal_sinTheta > " +preBCut + ") || (em_efcal > 0 )")
          .Filter("(ep_eprebcal_sinTheta > " +preBCut + ") || (ep_efcal > 0 )")
          .Filter("(passEoverP(em_p4_kin.P(),em_efcal,em_ebcal,em_isFCAL," + sigma_minus + "," + sigma_plus + "))")
          .Filter("(passEoverP(ep_p4_kin.P(),ep_efcal,ep_ebcal,ep_isFCAL," + sigma_minus + "," + sigma_plus + "))")
          .Filter("(fabs(E_miss_stat_p) < " + EMissCut + ")");


  #pragma region PoverEPlots

  auto rdf_noPoverE=rdf_in.Filter("(jpsi_m_pair > 2) && (jpsi_m_pair < 3.5)")
          .Filter("(zVertex > 51) && (zVertex < 79) && (xVertex*xVertex + yVertex*yVertex < 1*1)")
          .Filter("(em_theta > 2) && (ep_theta > 2) && (p_theta > 2)")
          .Filter("(em_p > 0.4) && (ep_p > 0.4) && (p_p > 0.4)")
          .Filter(track_shower_cut.c_str())
          .Filter("(em_eprebcal_sinTheta > " +preBCut + ") || (em_efcal > 0 )")
          .Filter("(ep_eprebcal_sinTheta > " +preBCut + ") || (ep_efcal > 0 )")
          .Filter("(fabs(E_miss_stat_p) < " + EMissCut + ")");

  TDirectory* PoverEPlots = currentDirectory->mkdir("PoverEPlots");
  PoverEPlots->cd();

  makePoverEPlots(rdf_noPoverE);

  #pragma endregion PoverEPlots

}

void filterAll_pEResolution(string inFileName, string outHistName, string treeName = "e_e_p_X", string track_shower_sel="1",
               string preBCut="0.030", string sigma_minus="-3", string sigma_plus="2", string EMissCut="1"){

  using namespace ROOT;
  using namespace std;

  TChain chain(treeName.c_str());
  chain.Add(inFileName.c_str());

  RDataFrame rdf_def(chain);

  string track_shower_cut="";
  switch (stoi(track_shower_sel)){
    case 0:
      track_shower_cut="((unusedShowers == 0) && (unusedTracks == 0))";
      break;
    case 1:
      track_shower_cut="((unusedShowers == 0) && (unusedTracks < 2))";
      break;
    case 2:
      track_shower_cut="((unusedShowers < 2) && (unusedTracks == 0))";
      break;
    case 3:
      track_shower_cut="((unusedShowers < 2) && (unusedTracks < 2))";
      break;
    default:
      track_shower_cut="((unusedShowers == 0) && (unusedTracks == 0))";
      break;
  }

  TFile * histFile = new TFile(outHistName.c_str(),"RECREATE");
  histFile->cd();

  makeAllPlots(rdf_def, histFile, track_shower_cut, preBCut, sigma_minus, sigma_plus, EMissCut);
  histFile->Close();
  //  rdf_final.Snapshot(treeName.c_str(),outFileName.c_str(),{"em_eprebcal_sinTheta","em_efcal","em_ebcal","em_isFCAL","em_p4_kin","ep_eprebcal_sinTheta","ep_efcal","ep_ebcal","ep_isFCAL","ep_p4_kin","E_miss_stat_p","E_gamma","jpsi_m_pair","accidweight"});
}
