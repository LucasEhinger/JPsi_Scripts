#include "analyzeData.h"
#include <vector>

using namespace ROOT;
using namespace std;

double returnNonZeroPoverE(double em_ebcal, double ep_ebcal, double em_p, double ep_p){
  if(em_ebcal>0){
    return em_p/em_ebcal;}
  else if(ep_ebcal>0){
    return ep_p/ep_ebcal;}
  else {
    return 0;}
}

double returnGreaterThetaVertex(double em_theta, double ep_theta, double vertex_em, double vertex_ep){
  if(em_theta>ep_theta){
    return vertex_em;}
  else {
    return vertex_ep;}
}

bool passPoverE(double p, double Efcal, double Ebcal, bool isFCAL, double sigma_minus, double sigma_plus)
{
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

void makePlots(RNode rdf_in,TFile* histFile, TDirectory* currentDirectory){
  TDirectory* jpsiMass_plots = currentDirectory->mkdir("Jpsi_mass");
  jpsiMass_plots->cd();

  TH1D h_mpair = *rdf_in.Histo1D({"mass_pair","; m_ee [GeV]; Counts",2000,2,4},"jpsi_m_pair","accidweight");
  h_mpair.Write();

  TH1D h_mpair_Egamma_7_8p2 = *rdf_in.Filter("(E_gamma<8.2)").Histo1D({"mass_pair_Egamma_7_8p2","; m_ee [GeV]; Counts",2000,2,4},"jpsi_m_pair","accidweight");
  h_mpair_Egamma_7_8p2.Write();

  TH1D h_mpair_Egamma_8p2_11 = *rdf_in.Filter("(E_gamma>8.2)").Histo1D({"mass_pair_Egamma_8p2_11","; m_ee [GeV]; Counts",2000,2,4},"jpsi_m_pair","accidweight");
  h_mpair_Egamma_8p2_11.Write();

  TH1D h_mpair_Egamma_8p2_9p5 = *rdf_in.Filter("((E_gamma>8.2)&&(E_gamma<9.5))").Histo1D({"mass_pair_Egamma_8p2_9p5","; m_ee [GeV]; Counts",2000,2,4},"jpsi_m_pair","accidweight");
  h_mpair_Egamma_8p2_9p5.Write();

  TH1D h_mpair_Egamma_9p5_11 = *rdf_in.Filter("(E_gamma>9.5)").Histo1D({"mass_pair_Egamma_9p5_11","; m_ee [GeV]; Counts",2000,2,4},"jpsi_m_pair","accidweight");
  h_mpair_Egamma_9p5_11.Write();

}

void filter_cutVary(string inFileName, string outFileName, string treeName = "e_e_p_X", string n_samples_per_cut="3")
{

// Time the script:

//  EnableImplicitMT();
  TChain chain(treeName.c_str());
  chain.Add(inFileName.c_str());

  RDataFrame rdf_trimmed(chain);

  double preBCut_min=0.025;
  double preBCut_max=0.035;
  double sigma_minus_min=-3.5;
  double sigma_minus_max=-2.5;
  double sigma_plus_min=1.5;
  double sigma_plus_max=2.5;
  double EMissCut_min=0.5;
  double EMissCut_max=1.5;

  TFile * histFile = new TFile(outFileName.c_str(),"RECREATE");
  histFile->cd();
  vector<double> preB_cuts;
  vector<double> PoverE_cuts_minus;
  vector<double> PoverE_cuts_plus;
  vector<double> E_miss_stat_p_cuts;
  vector<string> ranges_vec;

  for(int i=0; i<stoi(n_samples_per_cut);i++){
    preB_cuts.push_back(preBCut_min+(preBCut_max-preBCut_min)/(stoi(n_samples_per_cut)-1)*i);
    PoverE_cuts_minus.push_back(sigma_minus_min+(sigma_minus_max-sigma_minus_min)/(stoi(n_samples_per_cut)-1)*i);
    PoverE_cuts_plus.push_back(sigma_plus_min+(sigma_plus_max-sigma_plus_min)/(stoi(n_samples_per_cut)-1)*i);
    E_miss_stat_p_cuts.push_back(EMissCut_min+(EMissCut_max-EMissCut_min)/(stoi(n_samples_per_cut)-1)*i);
    ranges_vec.push_back("loc"+to_string(i));
  }
//  vector<double> preB_cuts ={preBCut_min,(preBCut_min+preBCut_max)/2,preBCut_max};
//  vector<double> PoverE_cuts_minus ={sigma_minus_min,(sigma_minus_min+sigma_minus_max)/2,sigma_minus_max};
//  vector<double> PoverE_cuts_plus ={sigma_plus_min,(sigma_plus_min+sigma_plus_max)/2,sigma_plus_max};
//  vector<double> E_miss_stat_p_cuts ={EMissCut_min,(EMissCut_min+EMissCut_max)/2,EMissCut_max};

  for(int i=0; i<preB_cuts.size();i++){
    for(int j=0; j<PoverE_cuts_minus.size();j++){
      for(int k=0; k<PoverE_cuts_plus.size();k++){
          for(int l=0; l<E_miss_stat_p_cuts.size();l++){
            string preBCut = to_string(preB_cuts[i]);
            string sigma_minus = to_string(PoverE_cuts_minus[j]);
            string sigma_plus = to_string(PoverE_cuts_plus[k]);
            string EMissCut = to_string(E_miss_stat_p_cuts[l]);

            auto rdf_final=rdf_trimmed.Filter("(em_eprebcal_sinTheta > " +preBCut + ") || (em_efcal > 0 )")
                    .Filter("(ep_eprebcal_sinTheta > " +preBCut + ") || (ep_efcal > 0 )")
                    .Filter("(passPoverE(em_p4_kin.P(),em_efcal,em_ebcal,em_isFCAL," + sigma_minus + "," + sigma_plus + "))")
                    .Filter("(passPoverE(ep_p4_kin.P(),ep_efcal,ep_ebcal,ep_isFCAL," + sigma_minus + "," + sigma_plus + "))")
                    .Filter("(fabs(E_miss_stat_p) < " + EMissCut + ")");

            string dir_name="preB_"+ranges_vec[i]+"_"+"sigma_"+ranges_vec[j]+"_"+ranges_vec[k]+"_"+"Emiss_"+ranges_vec[l];
            TDirectory* dir = histFile->mkdir(dir_name.c_str());
            dir->cd();
//            string paramVals=preBCut+";"+sigma_minus+";"+sigma_minus+";"+EMissCut+";";
//            TNamed params("param_vals",paramVals.c_str());
//
//            params.Write();
            makePlots(rdf_final,histFile,dir);
          }
        }
    }
  }

  histFile->Close();
}
