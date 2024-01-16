#include "analyzeData.h"
#include <chrono>


using namespace ROOT;
using namespace std;
using namespace std::chrono;

double returnNonZeroPoverE(double em_ebcal, double ep_ebcal, double em_p, double ep_p){
  if(em_ebcal>0){
    return em_p/em_ebcal;}
  else if(ep_ebcal>0){
    return ep_p/ep_ebcal;}
  else {
    return 0;}
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

template <typename RDF>
void makePlots(RDF rdf_in,TFile* histFile, TDirectory* currentDirectory){
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

void filter_cutVary_test(string inFileName, string outFileName, string treeName = "e_e_p_X")
{

  // Time the script:
  auto start = high_resolution_clock::now();

  EnableImplicitMT();
  TChain chain(treeName.c_str());
  chain.Add(inFileName.c_str());

  RDataFrame rdf_raw(chain);

  auto rdf_def = rdf_raw
          .Define("mN","0.938")
          .Define("N2_p4","TLorentzVector(0,0,0,2*mN)")
          .Define("jpsi_p4_meas","ep_p4_meas + em_p4_meas")
          .Define("jpsi_p4_kin","ep_p4_kin + em_p4_kin")
          .Define("jpsi_m_meas","jpsi_p4_meas.M()")
          .Define("jpsi_m_kin","jpsi_p4_kin.M()")
          .Define("init_p4_kin","jpsi_p4_kin + p_p4_kin - beam_p4_kin")
          .Define("miss_p4_meas","N2_p4 + beam_p4_meas - jpsi_p4_meas - p_p4_meas")
          .Define("miss_p4_kin","N2_p4 + beam_p4_kin - jpsi_p4_kin - p_p4_kin")
          .Define("Delta_kin","beam_p4_kin - jpsi_p4_kin")
          .Define("Delta_plus","1*(miss_p4_kin.Plus() - (mN*mN + miss_p4_kin.Perp2())/miss_p4_kin.Minus())")
          .Define("em_p","em_p4_kin.P()")
          .Define("em_theta","em_p4_kin.Theta()*180/3.14159265")
          .Define("ep_p","ep_p4_kin.P()")
          .Define("ep_theta","ep_p4_kin.Theta()*180/3.14159265")
          .Define("p_p","p_p4_kin.P()")
          .Define("p_theta","p_p4_kin.Theta()*180/3.14159265")
          .Define("jpsi_p","jpsi_p4_kin.P()")
          .Define("jpsi_theta","jpsi_p4_kin.Theta()*180/3.14159265")
          .Define("jpsi_m_pair","sqrt(jpsi_m_kin*jpsi_m_kin + 1*Delta_plus * jpsi_p4_kin.Minus())")
          .Define("jpsi_m_stand","sqrt((mN + beam_p4_kin.Plus() - p_p4_kin.Plus()) * jpsi_p4_kin.Minus() - jpsi_p4_kin.Perp2())")
          .Define("E_gamma","beam_p4_kin.T()")
          .Define("em_eprebcal_sinTheta", "em_eprebcal*sin(em_theta*3.1415/180)")
          .Define("ep_eprebcal_sinTheta", "ep_eprebcal*sin(ep_theta*3.1415/180)")
          .Define("em_isFCAL","em_efcal > em_ebcal")
          .Define("ep_isFCAL","ep_efcal > ep_ebcal")
          .Define("xVertex","p_x4_kin.X()")
          .Define("yVertex","p_x4_kin.Y()")
          .Define("zVertex","p_x4_kin.Z()")
          .Define("E_miss_stat_p","(mN + beam_p4_kin.T() - jpsi_p4_kin.T() - p_p4_kin.T())")
          .Filter("L1TriggerBits>0")
          .Filter("(E_gamma>7)");

  auto rdf_fiducial=rdf_def.Filter("(jpsi_m_pair > 2) && (jpsi_m_pair < 3.5)")
          .Filter("(zVertex > 51) && (zVertex < 79) && (xVertex*xVertex + yVertex*yVertex < 1*1)")
          .Filter("(em_theta > 2) && (ep_theta > 2) && (p_theta > 2)")
          .Filter("(em_p > 0.4) && (ep_p > 0.4) && (p_p > 0.4)");

  string track_shower_sel="0";
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
      track_shower_cut="((unusedShowers < 10) && (unusedTracks < 10))";
      break;
  }
  auto rdf_track_shower=rdf_fiducial.Filter(track_shower_cut.c_str());



  double preBCut_min=0.025;
  double preBCut_max=0.035;
  double sigma_minus_min=-3.5;
  double sigma_minus_max=-2.5;
  double sigma_plus_min=1.5;
  double sigma_plus_max=2.5;
  double EMissCut_min=0.5;
  double EMissCut_max=1.5;

  //Apply the loosest set of cuts possible, to make all further calculations easier.
  //All additional varied cuts will start from rdf_trimmed

  auto rdf_trimmed=rdf_track_shower.Filter("(em_eprebcal_sinTheta > " + to_string(preBCut_min) + ") || (em_efcal > 0 )")
          .Filter("(ep_eprebcal_sinTheta > " +to_string(preBCut_min) + ") || (ep_efcal > 0 )")
          .Filter("(passPoverE(em_p,em_efcal,em_ebcal,em_isFCAL," + to_string(sigma_minus_min) + "," + to_string(sigma_plus_max) + "))")
          .Filter("(passPoverE(ep_p,ep_efcal,ep_ebcal,ep_isFCAL," + to_string(sigma_minus_min) + "," + to_string(sigma_plus_max) + "))")
          .Filter("(fabs(E_miss_stat_p) < " + to_string(EMissCut_max) + ")");

  TFile * histFile = new TFile(outFileName.c_str(),"RECREATE");
  histFile->cd();

//  vector<double> preB_cuts ={preBCut_min,(preBCut_min+preBCut_max)/2,preBCut_max};
//  vector<double> PoverE_cuts_minus ={sigma_minus_min,(sigma_minus_min+sigma_minus_max)/2,sigma_minus_max};
//  vector<double> PoverE_cuts_plus ={sigma_plus_min,(sigma_plus_min+sigma_plus_max)/2,sigma_plus_max};
//  vector<double> E_miss_stat_p_cuts ={EMissCut_min,(EMissCut_min+EMissCut_max)/2,EMissCut_max};
  vector<double> preB_cuts ={(preBCut_min+preBCut_max)/2};
  vector<double> PoverE_cuts_minus ={(sigma_minus_min+sigma_minus_max)/2};
  vector<double> PoverE_cuts_plus ={(sigma_plus_min+sigma_plus_max)/2};
  vector<double> E_miss_stat_p_cuts ={(EMissCut_min+EMissCut_max)/2};

  vector<string> ranges_vec={"min","center","max"};
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

          TH1D h_mpair = *rdf_final.Histo1D({"mass_pair","; m_ee [GeV]; Counts",2000,2,4},"jpsi_m_pair","accidweight");
          h_mpair.Write();

          TH1D h_mpair_Egamma_7_8p2 = *rdf_final.Filter("(E_gamma<8.2)").Histo1D({"mass_pair_Egamma_7_8p2","; m_ee [GeV]; Counts",2000,2,4},"jpsi_m_pair","accidweight");
          h_mpair_Egamma_7_8p2.Write();

          TH1D h_mpair_Egamma_8p2_11 = *rdf_final.Filter("(E_gamma>8.2)").Histo1D({"mass_pair_Egamma_8p2_11","; m_ee [GeV]; Counts",2000,2,4},"jpsi_m_pair","accidweight");
          h_mpair_Egamma_8p2_11.Write();

          TH1D h_mpair_Egamma_8p2_9p5 = *rdf_final.Filter("((E_gamma>8.2)&&(E_gamma<9.5))").Histo1D({"mass_pair_Egamma_8p2_9p5","; m_ee [GeV]; Counts",2000,2,4},"jpsi_m_pair","accidweight");
          h_mpair_Egamma_8p2_9p5.Write();

          TH1D h_mpair_Egamma_9p5_11 = *rdf_final.Filter("(E_gamma>9.5)").Histo1D({"mass_pair_Egamma_9p5_11","; m_ee [GeV]; Counts",2000,2,4},"jpsi_m_pair","accidweight");
          h_mpair_Egamma_9p5_11.Write();
        }
      }
    }
  }
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  cout << "Time taken by function: " << duration.count() << " microseconds" << endl;
}
