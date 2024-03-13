//
// Created by Lucas Ehinger on 10/27/23.
//

#include "analyzeData.h"
using namespace ROOT;
using namespace std;

void makeParticleKinPlots(RNode rdf_in, TDirectory* currentDirectory,string particle){

  auto rdf_ROI=rdf_in.Filter("((jpsi_m_pair>3)&&(jpsi_m_pair<3.2))");
  auto rdf_SB=rdf_in.Filter("(((jpsi_m_pair>2.9)&&(jpsi_m_pair<3))||((jpsi_m_pair>3.2)&&(jpsi_m_pair<3.3)))");

  //<editor-fold desc="ROI">
  TDirectory* ROI_plots = currentDirectory->mkdir("ROI");
  ROI_plots->cd();

  TH1D h_p_ROI = *rdf_ROI.Histo1D({(particle+"_p").c_str(),("; "+particle+"_p [GeV/c]; Counts").c_str(),1000,0,10},(particle+"_p").c_str(),"accidweight");
  h_p_ROI.Write();

  TH1D h_pPlus_ROI = *rdf_ROI.Histo1D({(particle+"_pPlus").c_str(),("; "+particle+"_pPlus [GeV/c]; Counts").c_str(),1000,0,30},(particle+"_pPlus").c_str(),"accidweight");
  h_pPlus_ROI.Write();

  TH1D h_pMinus_ROI = *rdf_ROI.Histo1D({(particle+"_pMinus").c_str(),("; "+particle+"_pMinus [GeV/c]; Counts").c_str(),1000,0,10},(particle+"_pMinus").c_str(),"accidweight");
  h_pMinus_ROI.Write();

  TH1D h_perp_ROI = *rdf_ROI.Histo1D({(particle+"_pT").c_str(),("; "+particle+"_pT [GeV/c]; Counts").c_str(),1000,0,10},(particle+"_perp").c_str(),"accidweight");
  h_perp_ROI.Write();

  TH1D h_theta_ROI = *rdf_ROI.Histo1D({(particle+"_theta").c_str(),("; "+particle+"_theta [Deg]; Counts").c_str(),1000,0,180},(particle+"_theta").c_str(),"accidweight");
  h_theta_ROI.Write();

  TH2D h_kin_ROI = *rdf_ROI.Histo2D(kin_model,(particle+"_p").c_str(),(particle+"_theta").c_str(),"accidweight");
  h_kin_ROI.SetName(("kin_"+particle).c_str());
  h_kin_ROI.Write();
  //</editor-fold>

  //<editor-fold desc="SB">
  TDirectory* SB_plots = currentDirectory->mkdir("SB");
  SB_plots->cd();

  TH1D h_p_SB = *rdf_SB.Histo1D({(particle+"_p").c_str(),("; "+particle+"_p [GeV/c]; Counts").c_str(),1000,0,10},(particle+"_p").c_str(),"accidweight");
  h_p_SB.Write();

  TH1D h_pPlus_SB = *rdf_SB.Histo1D({(particle+"_pPlus").c_str(),("; "+particle+"_pPlus [GeV/c]; Counts").c_str(),1000,0,30},(particle+"_pPlus").c_str(),"accidweight");
  h_pPlus_SB.Write();

  TH1D h_pMinus_SB = *rdf_SB.Histo1D({(particle+"_pMinus").c_str(),("; "+particle+"_pMinus [GeV/c]; Counts").c_str(),1000,0,10},(particle+"_pMinus").c_str(),"accidweight");
  h_pMinus_SB.Write();

  TH1D h_perp_SB = *rdf_SB.Histo1D({(particle+"_pT").c_str(),("; "+particle+"_pT [GeV/c]; Counts").c_str(),1000,0,10},(particle+"_perp").c_str(),"accidweight");
  h_perp_SB.Write();

  TH1D h_theta_SB = *rdf_SB.Histo1D({(particle+"_theta").c_str(),("; "+particle+"_theta [Deg]; Counts").c_str(),1000,0,180},(particle+"_theta").c_str(),"accidweight");
  h_theta_SB.Write();

  TH2D h_kin_SB = *rdf_SB.Histo2D(kin_model,(particle+"_p").c_str(),(particle+"_theta").c_str(),"accidweight");
  h_kin_SB.SetName(("kin_"+particle).c_str());
  h_kin_SB.Write();
  //</editor-fold>

  //<editor-fold desc="SBS">
  TDirectory* SBS_plots = currentDirectory->mkdir("SBS");
  SBS_plots->cd();

  TH1D h_p_SBS = h_p_ROI - h_p_SB;
  h_p_SBS.Write();

  TH1D h_pPlus_SBS = h_pPlus_ROI - h_pPlus_SB;
  h_pPlus_SBS.Write();

  TH1D h_pMinus_SBS = h_pMinus_ROI - h_pMinus_SB;
  h_pMinus_SBS.Write();

  TH1D h_perp_SBS = h_perp_ROI - h_perp_SB;
  h_perp_SBS.Write();

  TH1D h_theta_SBS = h_theta_ROI - h_theta_SB;
  h_theta_SBS.Write();
  //</editor-fold>


  if (particle=="p" || particle=="jpsi") {
    ROI_plots->cd();
    TH1D h_alpha_ROI = *rdf_ROI.Histo1D({(particle+"_alpha").c_str(),("; "+particle+"_alpha; Counts").c_str(),1000,0,2.5},(particle+"_alpha").c_str(),"accidweight");
    h_alpha_ROI.Write();

    SB_plots->cd();
    TH1D h_alpha_SB = *rdf_SB.Histo1D({(particle+"_alpha").c_str(),("; "+particle+"_alpha; Counts").c_str(),1000,0,2.5},(particle+"_alpha").c_str(),"accidweight");
    h_alpha_SB.Write();

    SBS_plots->cd();
    TH1D h_alpha_SBS = h_alpha_ROI - h_alpha_SB;
    h_alpha_SB.Write();
  }
}

void makeKinPlots(RNode rdf_in, TDirectory* currentDirectory){
  auto rdf_ROI= rdf_in.Filter("((jpsi_m_pair>3)&&(jpsi_m_pair<3.2))");
  auto rdf_SB= rdf_in.Filter("(((jpsi_m_pair>2.9)&&(jpsi_m_pair<3))||((jpsi_m_pair>3.2)&&(jpsi_m_pair<3.3)))");

  //<editor-fold desc="ROI Plots">
  TDirectory* ROI_plots = currentDirectory->mkdir("ROI");
  ROI_plots->cd();

  TH1D h_t_ROI = *rdf_ROI.Histo1D({"t_kin_minus_ROI","; t [GeV]; Counts",1000,0,10},"t_kin_minus","accidweight");
  h_t_ROI.Write();

  TH1D h_t_lc_ROI = *rdf_ROI.Histo1D({"t_kin_minus_lc_ROI","; t [GeV]; Counts",1000,0,10},"t_kin_minus_lc","accidweight");
  h_t_lc_ROI.Write();

  TH1D h_alpha_miss_ROI = *rdf_ROI.Histo1D({"alpha_miss_ROI","; alpha_miss; Counts",1000,0,2.5},"alpha_miss","accidweight");
  h_alpha_miss_ROI.Write();

  TH1D h_kmiss_ROI = *rdf_ROI.Histo1D({"k_miss_ROI","; k_miss [GeV/c]; Counts",1000,0,2},"kmiss","accidweight");
  h_kmiss_ROI.Write();

  TH1D h_Egamma_ROI = *rdf_ROI.Histo1D({"Egamma_ROI","; E_gamma [GeV]; Counts",1000,6,11},"E_gamma","accidweight");
  h_Egamma_ROI.Write();

  TH1D h_pT_ROI = *rdf_ROI.Histo1D({"pT_ROI","; pT [GeV]; Counts",1000,0,2},"tot_perp","accidweight");
  h_pT_ROI.Write();

  TH1D h_mmiss_ROI = *rdf_ROI.Histo1D(mass_model,"miss_m_kin","accidweight");
  h_mmiss_ROI.SetName("mass_miss");
  h_mmiss_ROI.Write();

  TH1D h_pmiss_ROI = *rdf_ROI.Histo1D(pmiss_model,"pmiss","accidweight");
  h_pmiss_ROI.Write();

  TH1D h_k_ROI = *rdf_ROI.Histo1D(k_model,"k","accidweight");
  h_k_ROI.Write();

  TH1D h_E_miss_ROI = *rdf_ROI.Histo1D(E_miss_model,"E_miss_stat_p","accidweight");
  h_E_miss_ROI.SetName("E_miss_stat_p");
  h_E_miss_ROI.SetTitle("missing Energy: stationary proton; E_miss [GeV]");
  h_E_miss_ROI.Write();

  TH1D h_jpsi_beta_gamma_ROI = *rdf_ROI.Histo1D({"jpsi_beta_gamma","; jpsi_beta_gamma; Counts",1000,0,5},"jpsi_beta_gamma","accidweight");
  h_jpsi_beta_gamma_ROI.Write();

  TH2D h_alpha_miss_vs_Egamma_ROI = *rdf_ROI.Histo2D({"alpha_miss_vs_Egamma","; alpha_miss; Egamma [GeV]",100,0,2.5,100,6,11},"alpha_miss","E_gamma","accidweight");
  h_alpha_miss_vs_Egamma_ROI.Write();

  TH2D h_alpha_miss_v_pT_ROI = *rdf_ROI.Histo2D({"alpha_miss_vs_pT","; alpha_miss; pT [GeV/c]",100,0,2.5,100,0,2},"alpha_miss","tot_perp","accidweight");
  h_alpha_miss_v_pT_ROI.Write();

  TH2D h_theta_em_ep_ROI = *rdf_ROI.Histo2D({"theta_em_ep","; em_theta; ep_theta",100,0,180,100,0,180},"em_theta","ep_theta","accidweight");
  h_theta_em_ep_ROI.Write();
  //</editor-fold>

  //<editor-fold desc="Sideband Plots">
  TDirectory* SB_plots = currentDirectory->mkdir("SB");
  SB_plots->cd();

  TH1D h_t_SB = *rdf_ROI.Histo1D({"t_kin_minus_SB","; t [GeV]; Counts",1000,0,10},"t_kin_minus","accidweight");
  h_t_SB.Write();

  TH1D h_t_lc_SB = *rdf_ROI.Histo1D({"t_kin_minus_lc_SB","; t [GeV]; Counts",1000,0,10},"t_kin_minus_lc","accidweight");
  h_t_lc_SB.Write();

  TH1D h_alpha_miss_SB = *rdf_SB.Histo1D({"alpha_miss_SB","; alpha_miss; Counts",1000,0,2.5},"alpha_miss","accidweight");
  h_alpha_miss_SB.Write();

  TH1D h_kmiss_SB = *rdf_SB.Histo1D({"k_miss_SB","; k_miss [GeV/c]; Counts",1000,0,2},"kmiss","accidweight");
  h_kmiss_SB.Write();

  TH1D h_Egamma_SB = *rdf_SB.Histo1D({"Egamma_SB","; E_gamma [GeV]; Counts",1000,6,11},"E_gamma","accidweight");
  h_Egamma_SB.Write();

  TH1D h_pT_SB = *rdf_SB.Histo1D({"pT_SB","; pT [GeV/c]; Counts",1000,0,2},"tot_perp","accidweight");
  h_pT_SB.Write();

  TH1D h_mmiss_SB = *rdf_SB.Histo1D(mass_model,"miss_m_kin","accidweight");
  h_mmiss_SB.SetName("mass_miss");
  h_mmiss_SB.Write();

  TH1D h_pmiss_SB = *rdf_SB.Histo1D(pmiss_model,"pmiss","accidweight");
  h_pmiss_SB.Write();

  TH1D h_k_SB = *rdf_SB.Histo1D(k_model,"k","accidweight");
  h_k_SB.Write();

  TH1D h_E_miss_SB = *rdf_SB.Histo1D(E_miss_model,"E_miss_stat_p","accidweight");
  h_E_miss_SB.SetName("E_miss_stat_p");
  h_E_miss_SB.SetTitle("missing Energy: stationary proton; E_miss [GeV]");
  h_E_miss_SB.Write();

  TH2D h_alpha_miss_vs_Egamma_SB = *rdf_SB.Histo2D({"alpha_miss_vs_Egamma_SB","; alpha_miss; Egamma [GeV]",100,0,2.5,100,6,11},"alpha_miss","E_gamma","accidweight");
  h_alpha_miss_vs_Egamma_SB.Write();

  TH2D h_alpha_miss_v_pT_SB = *rdf_SB.Histo2D({"alpha_miss_vs_pT","; alpha_miss; pT [GeV/c]",100,0,2.5,100,0,2},"alpha_miss","tot_perp","accidweight");
  h_alpha_miss_v_pT_SB.Write();

  TH2D h_theta_em_ep_SB = *rdf_SB.Histo2D({"theta_em_ep","; em_theta; ep_theta",100,0,180,100,0,180},"em_theta","ep_theta","accidweight");
  h_theta_em_ep_SB.Write();
  //</editor-fold>

  //<editor-fold desc="SBS Plots">
  TDirectory* SBS_plots = currentDirectory->mkdir("SBS");
  SBS_plots->cd();

  TH1D h_t_SBS = h_t_ROI - h_t_SB;
  h_t_SBS.SetName("t_kin_minus_SBS");
  h_t_SBS.Write();

  TH1D h_t_lc_SBS = h_t_lc_ROI - h_t_lc_SB;
  h_t_lc_SBS.SetName("t_kin_minus_lc_SBS");
  h_t_lc_SBS.Write();

  TH1D h_alpha_miss_SBS = h_alpha_miss_ROI - h_alpha_miss_SB;
  h_alpha_miss_SBS.SetName("alpha_miss_SBS");
  h_alpha_miss_SBS.Write();

  TH1D h_kmiss_SBS = h_kmiss_ROI - h_kmiss_SB;
  h_kmiss_SBS.SetName("k_miss_SBS");
  h_kmiss_SBS.Write();

  TH1D h_Egamma_SBS = h_Egamma_ROI - h_Egamma_SB;
  h_Egamma_SBS.SetName("Egamma_SBS");
  h_Egamma_SBS.Write();

  TH1D h_Pt_SBS = h_pT_ROI - h_pT_SB;
  h_Pt_SBS.SetName("Pt_SBS");
  h_Pt_SBS.Write();

  TH1D h_mmiss_SBS = h_mmiss_ROI - h_mmiss_SB;
  h_mmiss_SBS.Write();

  TH1D h_pmiss_SBS = h_pmiss_ROI - h_pmiss_SB;
  h_pmiss_SBS.Write();

  TH1D h_k_SBS = h_k_ROI - h_k_SB;
  h_k_SBS.Write();

  TH1D h_E_miss_SBS = h_E_miss_ROI - h_E_miss_SB;
  h_E_miss_SBS.Write();
  //</editor-fold>

  //<editor-fold desc="Simulation Plots">
  try{
    TDirectory* Sim_plots = currentDirectory->mkdir("Sim");
    Sim_plots->cd();

    TH1D h_delta_t_thrown_ROI = *rdf_ROI.Histo1D({"delta_t_thrown_ROI","; t true - t kin [GeV]; Counts",1000,-10,10},"delta_t_thrown","accidweight");
    h_delta_t_thrown_ROI.Write();

    TH1D h_delta_t_thrown_lc_ROI = *rdf_ROI.Histo1D({"delta_t_thrown_lc_ROI","; t true - t light cone [GeV]; Counts",1000,-10,10},"delta_t_thrown_lc","accidweight");
    h_delta_t_thrown_lc_ROI.Write();
  }
  catch(...){}
  //</editor-fold>

  //<editor-fold desc="Kin2D">
  TDirectory* kin2D_plots = currentDirectory->mkdir("Kin2D");
  kin2D_plots->cd();

  TH2D h_alpha_miss_v_mee = *rdf_in.Histo2D({"alpha_miss_vs_mee","; alpha_miss; Mee [GeV]",100,0,2.5,100,1.5,3.5},"alpha_miss","jpsi_m_pair","accidweight");
  h_alpha_miss_v_mee.Write();

  TH2D h_alpha_miss_v_pT = *rdf_in.Histo2D({"alpha_miss_vs_pT","; alpha_miss; pT [GeV]",100,0,2.5,100,0,2},"alpha_miss","tot_perp","accidweight");
  h_alpha_miss_v_pT.Write();

  TH2D h_alpha_miss_vs_Egamma = *rdf_in.Histo2D({"alpha_miss_vs_Egamma","; alpha_miss; Egamma [GeV]",100,0,2.5,100,6,11},"alpha_miss","E_gamma","accidweight");
  h_alpha_miss_vs_Egamma.Write();

  TH2D h_kmiss_v_mee = *rdf_in.Histo2D({"k_miss_vs_mee","; k_miss; m_ee [GeV]",100,0,4,100,1.5,3.5},"kmiss","jpsi_m_pair","accidweight");
  h_kmiss_v_mee.Write();

  TH2D h_Egamma_v_mee = *rdf_in.Histo2D({"Egamma_v_mee","; E_gamma [GeV]; m_ee [GeV]",100,6,11,100,1.5,3.5},"E_gamma","jpsi_m_pair","accidweight");
  h_Egamma_v_mee.Write();

  TH2D h_Pt_v_mee = *rdf_in.Histo2D({"Pt_v_mee","; Pt [GeV]; m_ee [GeV]",100,0,2,100,1.5,3.5},"tot_perp","jpsi_m_pair","accidweight");
  h_Pt_v_mee.Write();

  TH2D h_alpha_p_v_alpha_n = *rdf_in.Histo2D({"alpha_p_v_alpha_n","; alpha_p; alpha_n",100,0,2,100,0,2},"p_alpha","n_alpha","accidweight");
  h_alpha_p_v_alpha_n.Write();
  //</editor-fold>

  //<editor-fold desc="JPsi Mass">
  TDirectory* jpsiMass_plots = currentDirectory->mkdir("Jpsi_mass");
  jpsiMass_plots->cd();

  TH1D h_mmeas = *rdf_in.Histo1D({"mass_meas","; m_ee [GeV]; Counts",2000,2,4},"jpsi_m_meas","accidweight");
  h_mmeas.SetName("mass_meas");
  h_mmeas.Write();

  TH1D h_mkin = *rdf_in.Histo1D({"mass_kin","; m_ee [GeV]; Counts",2000,2,4},"jpsi_m_kin","accidweight");
  h_mkin.SetName("mass_kin");
  h_mkin.Write();

  TH1D h_mstand = *rdf_in.Histo1D({"mass_stand","; m_ee [GeV]; Counts",2000,2,4},"jpsi_m_stand","accidweight");
  h_mstand.SetName("mass_stand");
  h_mstand.Write();


  TH1D h_mpair = *rdf_in.Histo1D({"mass_pair","; m_ee [GeV]; Counts",2000,2,4},"jpsi_m_pair","accidweight");
  h_mpair.Write();

  TH1D h_mpair_nn = *rdf_in.Filter("(accidweight>0)").Histo1D({"mass_pair_no_neg","; m_ee [GeV]; Counts",2000,2,4},"jpsi_m_pair","accidweight");
  h_mpair_nn.Write();

  TH1D h_mpair_accid = *rdf_in.Filter("(accidweight<0)").Histo1D({"mass_pair_neg","; m_ee [GeV]; Counts",2000,2,4},"jpsi_m_pair","accidweight");
  h_mpair_accid.Write();

  TH1D h_mpair_Egamma_9p5_lower = *rdf_in.Filter("E_gamma<9.5").Histo1D({"mpair_Egamma_9p5_lower","; m_ee [GeV]; Counts",2000,2,4},"jpsi_m_pair","accidweight");
  h_mpair_Egamma_9p5_lower.Write();

  TH1D h_mpair_Egamma_9p5_upper = *rdf_in.Filter("E_gamma>9.5").Histo1D({"mpair_Egamma_9p5_upper","; m_ee [GeV]; Counts",2000,2,4},"jpsi_m_pair","accidweight");
  h_mpair_Egamma_9p5_upper.Write();

  TH1D h_mpair_minus_t_1_lower = *rdf_in.Filter("t_kin_minus<1").Histo1D({"mpair_minus_t_1_lower","; m_ee [GeV]; Counts",2000,2,4},"jpsi_m_pair","accidweight");
  h_mpair_minus_t_1_lower.Write();

  TH1D h_mpair_minus_t_1_upper = *rdf_in.Filter("t_kin_minus>1").Histo1D({"mpair_minus_t_1_upper","; m_ee [GeV]; Counts",2000,2,4},"jpsi_m_pair","accidweight");
  h_mpair_minus_t_1_upper.Write();

  TH1D h_mpair_minus_t_lc_1_lower = *rdf_in.Filter("t_kin_minus_lc<1").Histo1D({"mpair_minus_t_lc_1_lower","; m_ee [GeV]; Counts",2000,2,4},"jpsi_m_pair","accidweight");
  h_mpair_minus_t_lc_1_lower.Write();

  TH1D h_mpair_minus_t_lc_1_upper = *rdf_in.Filter("t_kin_minus_lc>1").Histo1D({"mpair_minus_t_lc_1_upper","; m_ee [GeV]; Counts",2000,2,4},"jpsi_m_pair","accidweight");
  h_mpair_minus_t_lc_1_upper.Write();

  TH1D h_mpair_betagamma_2p75_lower = *rdf_in.Filter("jpsi_beta_gamma<2.75").Histo1D({"mpair_betagamma_2p75_lower","; m_ee [GeV]; Counts",2000,2,4},"jpsi_m_pair","accidweight");
  h_mpair_betagamma_2p75_lower.Write();

  TH1D h_mpair_betagamma_2p75_upper = *rdf_in.Filter("jpsi_beta_gamma>2.75").Histo1D({"mpair_betagamma_2p75_upper","; m_ee [GeV]; Counts",2000,2,4},"jpsi_m_pair","accidweight");
  h_mpair_betagamma_2p75_upper.Write();

  TH1D h_mpair_jpsi_alpha_0p6_lower = *rdf_in.Filter("jpsi_alpha<0.6").Histo1D({"mpair_jpsi_alpha_0p6_lower","; m_ee [GeV]; Counts",2000,2,4},"jpsi_m_pair","accidweight");
  h_mpair_jpsi_alpha_0p6_lower.Write();

  TH1D h_mpair_jpsi_alpha_0p6_upper = *rdf_in.Filter("jpsi_alpha>0.6").Histo1D({"mpair_jpsi_alpha_0p6_upper","; m_ee [GeV]; Counts",2000,2,4},"jpsi_m_pair","accidweight");
  h_mpair_jpsi_alpha_0p6_upper.Write();

  TH2D h_mpair_v_mkin = *rdf_in.Histo2D({"mpair_v_mkin","; m_ee (Pair) [GeV/c^2]; m_ee (Kin) [GeV/c^2]",500,2,3.5,500,2,3.5},"jpsi_m_pair","jpsi_m_kin","accidweight");
  h_mpair_v_mkin.Write();

  TH2D h_mpair_v_Emiss = *rdf_in.Histo2D({"mpair_v_Emiss","; m_ee (Pair) [GeV/c^2]; E_miss [GeV/]",500,2,3.5,500,-2,2},"jpsi_m_pair","E_miss_stat_p","accidweight");
  h_mpair_v_Emiss.Write();
  //</editor-fold>

}

void makeAllPlots(RNode rdf_in, TDirectory* currentDirectory){
  TDirectory* kinematic_plots = currentDirectory->mkdir("Kin");
  kinematic_plots->cd();
  makeKinPlots(rdf_in, kinematic_plots);

  TDirectory* jpsi_plots = currentDirectory->mkdir("jpsi");
  jpsi_plots->cd();
  makeParticleKinPlots(rdf_in, jpsi_plots,"jpsi");

  TDirectory* p_plots = currentDirectory->mkdir("p");
  p_plots->cd();
  makeParticleKinPlots(rdf_in, p_plots,"p");

  TDirectory* em_plots = currentDirectory->mkdir("em");
  em_plots->cd();
  makeParticleKinPlots(rdf_in, em_plots,"em");

  TDirectory* ep_plots = currentDirectory->mkdir("ep");
  ep_plots->cd();
  makeParticleKinPlots(rdf_in, ep_plots,"ep");
}

void makeHists(string inFileName, string outFileName, string treeName = "e_e_p_X")
{

  using namespace ROOT;
  using namespace std;

  EnableImplicitMT();
  TChain chain(treeName.c_str());
  chain.Add(inFileName.c_str());

  RDataFrame rdf_def(chain);

  auto rdf_final=rdf_def.Filter("(E_gamma>7)");

//  auto rdf_ROI=rdf_final.Filter("((jpsi_m_pair>3)&&(jpsi_m_pair<3.2))");
//  auto rdf_SB=rdf_final.Filter("(((jpsi_m_pair>2.9)&&(jpsi_m_pair<3))||((jpsi_m_pair>3.2)&&(jpsi_m_pair<3.3)))");


  auto rdf_subThresh=rdf_final.Filter("((E_gamma>7) && (E_gamma<8.2))");
  auto rdf_aboveThresh=rdf_final.Filter("(E_gamma>8.2)");
  auto rdf_aboveThresh_lower=rdf_aboveThresh.Filter("(E_gamma<9.5)");
  auto rdf_aboveThresh_upper=rdf_aboveThresh.Filter("(E_gamma>9.5)");

  auto rdf_all_pt03_lower=rdf_final.Filter("tot_perp<0.3");
  auto rdf_all_pt03_upper=rdf_final.Filter("tot_perp>0.3");
  auto rdf_subThresh_pt03_lower=rdf_subThresh.Filter("tot_perp<0.3");
  auto rdf_subThresh_pt03_upper=rdf_subThresh.Filter("tot_perp>0.3");
  auto rdf_aboveThresh_pt03_lower=rdf_aboveThresh.Filter("tot_perp<0.3");
  auto rdf_aboveThresh_pt03_upper=rdf_aboveThresh.Filter("tot_perp>0.3");
  auto rdf_all_alpha1p2_lower=rdf_final.Filter("alpha_miss<1.2");
  auto rdf_all_alpha1p2_upper=rdf_final.Filter("alpha_miss>1.2");

  auto rdf_pT_alphaCut=rdf_final.Filter("(tot_perp < 0.8-0.8/1.4*alpha_miss)");

  auto rdf_ROI_2p85_3p05=rdf_final.Filter("((jpsi_m_pair>2.85)&&(jpsi_m_pair<3.05))");
  auto rdf_ROI_3p05_3p25=rdf_final.Filter("((jpsi_m_pair>3.05)&&(jpsi_m_pair<3.25))");



  vector<string> name_vec = {"All", "SubThresh", "AboveThresh", "AboveThresh_lower", "AboveThresh_upper",
                             "All_pt03_lower","All_pt03_upper","SubThresh_pt03_lower","SubThresh_pt03_upper",
                             "AboveThresh_pt03_lower","AboveThresh_pt03_upper",
                             "All_alpha1p2_lower","All_alpha1p2_upper","All_pt_alpha",
                             "All_ROI_2p85_3p05","All_ROI_3p05_3p25"};

  vector<RNode> rdf_vec = {rdf_final, rdf_subThresh, rdf_aboveThresh, rdf_aboveThresh_lower, rdf_aboveThresh_upper,
                           rdf_all_pt03_lower,rdf_all_pt03_upper,rdf_subThresh_pt03_lower,rdf_subThresh_pt03_upper,
                           rdf_aboveThresh_pt03_lower,rdf_aboveThresh_pt03_upper,
                           rdf_all_alpha1p2_lower,rdf_all_alpha1p2_upper,rdf_pT_alphaCut,
                           rdf_ROI_2p85_3p05,rdf_ROI_3p05_3p25};

  //Start defining histograms

  TFile * histFile = new TFile(outFileName.c_str(),"RECREATE");

  histFile->cd();

  for(int i=0; i<rdf_vec.size();i++){
    TDirectory* sub_dir = histFile->mkdir(name_vec[i].c_str());
    sub_dir->cd();
    makeAllPlots(rdf_vec[i], sub_dir);
  }

}
