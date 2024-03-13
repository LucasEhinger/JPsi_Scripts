//
// Created by Lucas Ehinger on 6/9/23.
//

#include "analyzeData.h"
double returnGreaterThetaVertex(double theta_em, double theta_ep, double vertex_em, double vertex_ep){
  if(theta_em>theta_ep){
    return vertex_em;}
  else {
    return vertex_ep;}
}

void makeFigs2(string inFileName, string outFileName, string treeName = "e_e_p_X")
{

  using namespace ROOT;
  using namespace std;


  TChain chain(treeName.c_str());
  chain.Add(inFileName.c_str());

  RDataFrame rdf_def(chain);

  auto rdf_final=rdf_def.Filter("(E_gamma>7)")
          .Define("jpsi_p","jpsi_p4_kin.P()")
          .Define("theta_jpsi","jpsi_p4_kin.Theta()*180/3.14159265");

  auto rdf_ROI=rdf_final.Filter("((jpsi_m_pair>3)&&(jpsi_m_pair<3.2))");
  auto rdf_SB=rdf_final.Filter("(((jpsi_m_pair>2.9)&&(jpsi_m_pair<3))||((jpsi_m_pair>3.2)&&(jpsi_m_pair<3.3)))");


  //Start defining histograms

  TFile * histFile = new TFile(outFileName.c_str(),"RECREATE");

  histFile->cd();

  //<editor-fold desc="ROI Plots">
  TDirectory* ROIplots = histFile->mkdir("ROI");
  ROIplots->cd();
  TH1D h_t_new_ROI = *rdf_ROI.Histo1D({"t_kin_minus_ROI","; t [GeV]; Counts",1000,0,10},"t_kin_minus","accidweight");
  h_t_new_ROI.Write();

  TH1D h_alpha_miss_ROI = *rdf_ROI.Histo1D({"alpha_miss_ROI","; alpha_miss; Counts",1000,0,2.5},"alpha_miss","accidweight");
  h_alpha_miss_ROI.Write();

  TH1D h_kmiss_ROI = *rdf_ROI.Histo1D({"k_miss_ROI","; k_miss; Counts",1000,0,2},"kmiss","accidweight");
  h_kmiss_ROI.Write();

  TH1D h_Egamma_ROI = *rdf_ROI.Histo1D({"Egamma_ROI","; E_gamma [GeV]; Counts",1000,6,11},"E_gamma","accidweight");
  h_Egamma_ROI.Write();

  TH1D h_Pt_ROI = *rdf_ROI.Histo1D({"Pt_ROI","; Pt [GeV]; Counts",1000,0,2},"tot_perp","accidweight");
  h_Pt_ROI.Write();

  TH2D h_alpha_miss_vs_Egamma_ROI = *rdf_ROI.Histo2D({"alpha_miss_vs_Egamma_ROI","; alpha_miss; Egamma [GeV]",100,0,2.5,100,6,11},"alpha_miss","E_gamma","accidweight");
  h_alpha_miss_vs_Egamma_ROI.Write();

  TH2D h_alpha_miss_v_pT_ROI = *rdf_ROI.Histo2D({"alpha_miss_vs_pT_ROI","; alpha_miss; pT [GeV]",100,0,2.5,100,0,2},"alpha_miss","tot_perp","accidweight");
  h_alpha_miss_v_pT_ROI.Write();

  TH1D h_E_gamma_ROI = *rdf_ROI.Histo1D(E_gamma_model,"E_gamma","accidweight");
  h_E_gamma_ROI.SetName("E_gamma_ROI");
  h_E_gamma_ROI.SetTitle("E_gamma_ROI");
  h_E_gamma_ROI.Write();

  TH2D h_theta_em_ep = *rdf_ROI.Histo2D({"theta_em_ep","; theta_em; theta_ep",100,0,180,100,0,180},"theta_em","theta_ep","accidweight");
  h_theta_em_ep.Write();
  //</editor-fold>

  //<editor-fold desc="Sideband Plots">
  TDirectory* SBplots = histFile->mkdir("SB");
  SBplots->cd();

  TH1D h_t_new_SB = *rdf_SB.Histo1D({"t_kin_minus_SB","; t [GeV]; Counts",1000,0,10},"t_kin_minus","accidweight");
  h_t_new_SB.Write();

  TH1D h_alpha_miss_SB = *rdf_SB.Histo1D({"alpha_miss_SB","; alpha_miss; Counts",1000,0,2.5},"alpha_miss","accidweight");
  h_alpha_miss_SB.Write();

  TH1D h_kmiss_SB = *rdf_SB.Histo1D({"k_miss_SB","; k_miss; Counts",1000,0,2},"kmiss","accidweight");
  h_kmiss_SB.Write();

  TH1D h_Egamma_SB = *rdf_SB.Histo1D({"Egamma_SB","; E_gamma [GeV]; Counts",1000,6,11},"E_gamma","accidweight");
  h_Egamma_SB.Write();

  TH1D h_Pt_SB = *rdf_SB.Histo1D({"Pt_SB","; Pt [GeV]; Counts",1000,0,2},"tot_perp","accidweight");
  h_Pt_SB.Write();

  TH2D h_alpha_miss_vs_Egamma_SB = *rdf_SB.Histo2D({"alpha_miss_vs_Egamma_SB","; alpha_miss; Egamma [GeV]",100,0,2.5,100,6,11},"alpha_miss","E_gamma","accidweight");
  h_alpha_miss_vs_Egamma_SB.Write();
  //</editor-fold>


  //<editor-fold desc="SBS Plots">
  TDirectory* SBSplots = histFile->mkdir("SBS");
  SBSplots->cd();

  TH1D h_t_new_SBS = h_t_new_ROI-h_t_new_SB;
  h_t_new_SBS.SetName("t_kin_minus_SBS");
  h_t_new_SBS.Write();

  TH1D h_alpha_miss_SBS = h_alpha_miss_ROI-h_alpha_miss_SB;
  h_alpha_miss_SBS.SetName("alpha_miss_SBS");
  h_alpha_miss_SBS.Write();

  TH1D h_kmiss_SBS = h_kmiss_ROI-h_kmiss_SB;
  h_kmiss_SBS.SetName("k_miss_SBS");
  h_kmiss_SBS.Write();

  TH1D h_Egamma_SBS = h_Egamma_ROI-h_Egamma_SB;
  h_Egamma_SBS.SetName("Egamma_SBS");
  h_Egamma_SBS.Write();

  TH1D h_Pt_SBS = h_Pt_ROI-h_Pt_SB;
  h_Pt_SBS.SetName("Pt_SBS");
  h_Pt_SBS.Write();

  TH2D h_alpha_miss_vs_Egamma_SBS = h_alpha_miss_vs_Egamma_ROI-h_alpha_miss_vs_Egamma_SB;
  h_alpha_miss_vs_Egamma_SBS.SetName("alpha_miss_vs_Egamma_SBS");
  h_alpha_miss_vs_Egamma_SBS.Write();
  //</editor-fold>

  //<editor-fold desc="2D plots">
  TDirectory* SubThresh2Dplots = histFile->mkdir("SubThresh2D");
  SubThresh2Dplots->cd();

  TH2D h_alpha_miss_v_mee = *rdf_final.Histo2D({"alpha_miss_vs_mee","; alpha_miss; Mee [GeV]",100,0,2.5,100,1.5,3.5},"alpha_miss","jpsi_m_pair","accidweight");
  h_alpha_miss_v_mee.Write();

  TH2D h_alpha_miss_v_pT = *rdf_final.Histo2D({"alpha_miss_vs_pT","; alpha_miss; pT [GeV]",100,0,2.5,100,0,2},"alpha_miss","tot_perp","accidweight");
  h_alpha_miss_v_pT.Write();

  TH2D h_alpha_miss_vs_Egamma = *rdf_final.Histo2D({"alpha_miss_vs_Egamma","; alpha_miss; Egamma [GeV]",100,0,2.5,100,6,11},"alpha_miss","E_gamma","accidweight");
  h_alpha_miss_vs_Egamma.Write();

  TH2D h_kmiss_v_mee = *rdf_final.Histo2D({"k_miss_vs_mee","; k_miss; m_ee [GeV]",100,0,4,100,1.5,3.5},"kmiss","jpsi_m_pair","accidweight");
  h_kmiss_v_mee.Write();

  TH2D h_Egamma_v_mee = *rdf_final.Histo2D({"Egamma_v_mee","; E_gamma [GeV]; m_ee [GeV]",100,6,11,100,1.5,3.5},"E_gamma","jpsi_m_pair","accidweight");
  h_Egamma_v_mee.Write();

  TH2D h_Pt_v_mee = *rdf_final.Histo2D({"Pt_v_mee","; Pt [GeV]; m_ee [GeV]",100,0,2,100,1.5,3.5},"tot_perp","jpsi_m_pair","accidweight");
  h_Pt_v_mee.Write();
  //</editor-fold>

  //<editor-fold desc="Pion Rejection">
  TDirectory* PionRejectPlots = histFile->mkdir("PionRejection");
  PionRejectPlots->cd();

//  TH2D h_Cal_PoverE = *rdf_final.Filter("(fcal_PoverE>0)").Filter("bcal_PoverE>0")
//          .Histo2D(EP_2DModel,"fcal_PoverE","bcal_PoverE","accidweight");
//  h_Cal_PoverE.SetName("Cal_PoverE");
//  h_Cal_PoverE.SetTitle("; fcal p/E; bcal p/E");
//  h_Cal_PoverE.Write();
//
//
//  TH1D h_fCal_PoverE = *rdf_final.Histo1D(PE_Ratio_model,"fcal_PoverE","accidweight");
//  h_fCal_PoverE.SetName("fcal_PoverE");
//  h_fCal_PoverE.SetTitle("P/E");
//  h_fCal_PoverE.Write();
//
//  TH1D h_bCal_PoverE = *rdf_final.Histo1D(PE_Ratio_model,"bcal_PoverE","accidweight");
//  h_bCal_PoverE.SetName("bcal_PoverE");
//  h_bCal_PoverE.SetTitle("P/E");
//  h_bCal_PoverE.Write();

  TH1D h_em_PoverE = *rdf_final.Histo1D(PE_Ratio_model,"em_PoverE","accidweight");
  h_em_PoverE.SetName("em_PoverE");
  h_em_PoverE.SetTitle("P/E");
  h_em_PoverE.Write();

  TH1D h_ep_PoverE = *rdf_final.Histo1D(PE_Ratio_model,"ep_PoverE","accidweight");
  h_ep_PoverE.SetName("ep_PoverE");
  h_ep_PoverE.SetTitle("P/E");
  h_ep_PoverE.Write();

  TH1D h_lep_PoverE = h_em_PoverE+h_ep_PoverE;
  h_lep_PoverE.SetName("lep_PoverE");
  h_lep_PoverE.SetTitle("P/E");
  h_lep_PoverE.Write();

  TH1D h_em_preB_sin = *rdf_final.Filter("(em_ebcal!=0)").Histo1D(preB_sin_model,"em_eprebcal_sinTheta","accidweight");
  h_em_preB_sin.SetName("em_eprebcal_sinTheta");
  h_em_preB_sin.Write();

  TH1D h_ep_preB_sin = *rdf_final.Filter("(ep_ebcal!=0)").Histo1D(preB_sin_model,"ep_eprebcal_sinTheta","accidweight");
  h_ep_preB_sin.SetName("ep_eprebcal_sinTheta");
  h_ep_preB_sin.Write();

  TH2D h_PoverE_2D = *rdf_final.Histo2D(EP_2DModel,"em_PoverE","ep_PoverE","accidweight");
  h_PoverE_2D.SetName("PoverE_2D");
  h_PoverE_2D.SetTitle("P/E");
  h_PoverE_2D.Write();
  //</editor-fold>

  //<editor-fold desc="J Psi">
  TDirectory* JPsiplots = histFile->mkdir("JPsi");
  JPsiplots->cd();

  TH1D h_mmeas = *rdf_final.Histo1D(mass_model,"jpsi_m_meas","accidweight");
  h_mmeas.SetName("mass_meas");
  h_mmeas.Write();

  TH1D h_mkin = *rdf_final.Histo1D(mass_model,"jpsi_m_kin","accidweight");
  h_mkin.SetName("mass_kin");
  h_mkin.Write();

  TH1D h_mstand = *rdf_final.Histo1D(mass_model,"jpsi_m_stand","accidweight");
  h_mstand.SetName("mass_stand");
  h_mstand.Write();

  TH1D h_mpair = *rdf_final.Histo1D(mass_model,"jpsi_m_pair","accidweight");
  h_mpair.SetName("mass_pair");
  h_mpair.Write();

  TH1D h_mpair_fine = *rdf_final.Histo1D({"mass_pair_fine","; m_ee [GeV]; Counts",2000,2,4},"jpsi_m_pair","accidweight");
  h_mpair_fine.Write();

  TH1D h_mpair_fine_pt03 = *rdf_final.Filter("(tot_perp<0.3)").Histo1D({"mass_pair_fine_pt0p3","; m_ee [GeV]; Counts",2000,2,4},"jpsi_m_pair","accidweight");
  h_mpair_fine_pt03.Write();

  TH1D h_mpair_fine_alpha1p2 = *rdf_final.Filter("(alpha_miss<1.2)").Histo1D({"mass_pair_fine_alpha1p2","; m_ee [GeV]; Counts",2000,2,4},"jpsi_m_pair","accidweight");
  h_mpair_fine_alpha1p2.Write();

  TH1D h_mpair_fine_alpha1p2_pt0p3 = *rdf_final.Filter("(tot_perp<0.8-0.8/1.4*alpha_miss)").Histo1D({"mass_pair_fine_alpha1p2_pt0p3","; m_ee [GeV]; Counts",2000,2,4},"jpsi_m_pair","accidweight");
  h_mpair_fine_alpha1p2_pt0p3.Write();

  TH1D h_mpair_nn = *rdf_final.Filter("(accidweight>0)").Histo1D(mass_model,"jpsi_m_pair","accidweight");
  h_mpair_nn.SetName("mass_pair_no_neg");
  h_mpair_nn.Write();

  TH1D h_jpsi_pMinus = *rdf_final.Histo1D(pMinus_model,"jpsi_pMinus","accidweight");
  h_jpsi_pMinus.SetName("jpsi_pMinus");
  h_jpsi_pMinus.SetTitle("jpsi_pMinus");
  h_jpsi_pMinus.Write();

  TH1D h_jpsi_perp = *rdf_final.Histo1D(pPerp_model,"jpsi_perp","accidweight");
  h_jpsi_perp.SetName("jpsi_perp");
  h_jpsi_perp.SetTitle("jpsi_perp");
  h_jpsi_perp.Write();

  //<editor-fold desc="JPsi ROI">
  TDirectory* JPsi_ROI = JPsiplots->mkdir("JPsi_ROI");
  JPsi_ROI->cd();

  TH1D h_jpsi_alpha_ROI = *rdf_ROI.Define("alpha_jpsi","(jpsi_pMinus/mN)").Histo1D({"alpha_jpsi","; alpha; Counts",1000,0,2.5},"alpha_jpsi","accidweight");
  h_jpsi_alpha_ROI.Write();


  TH1D h_jpsi_p_ROI = *rdf_ROI.Histo1D({"jpsi_p","; jpsi_p [GeV]; Counts",1000,0,10},"jpsi_p","accidweight");
  h_jpsi_p_ROI.Write();


  TH1D h_jpsi_pPlus_ROI = *rdf_ROI.Define("jpsi_pPlus","(jpsi_p4_kin.Plus())").Histo1D({"jpsi_pPlus","; jpsi_pPlus; Counts",1000,0,10},"jpsi_pPlus","accidweight");
  h_jpsi_pPlus_ROI.Write();

  TH1D h_jpsi_pMinus_ROI = *rdf_ROI.Histo1D({"jpsi_pMinus","; jpsi_pMinus; Counts",1000,0,10},"jpsi_pMinus","accidweight");
  h_jpsi_pMinus_ROI.Write();

  TH1D h_jpsi_perp_ROI = *rdf_ROI.Histo1D(pPerp_model,"jpsi_perp","accidweight");
  h_jpsi_perp_ROI.SetName("jpsi_perp_ROI");
  h_jpsi_perp_ROI.SetTitle("jpsi_perp_ROI");
  h_jpsi_perp_ROI.Write();

  TH2D h_kin_jpsi_ROI = *rdf_ROI.Histo2D(kin_model,"jpsi_p","theta_jpsi","accidweight");
  h_kin_jpsi_ROI.SetName("kin_jpsi");
  h_kin_jpsi_ROI.Write();

  TH1D h_theta_jpsi_ROI = *rdf_ROI.Histo1D(Theta_model,"theta_jpsi","accidweight");
  h_theta_jpsi_ROI.SetName("theta_jpsi");
  h_theta_jpsi_ROI.Write();
  //</editor-fold>

  //<editor-fold desc="JPsi SB">
  TDirectory* JPsi_SB = JPsiplots->mkdir("JPsi_SB");
  JPsi_SB->cd();

  TH1D h_jpsi_alpha_SB = *rdf_SB.Define("alpha_jpsi","(jpsi_pMinus/mN)").Histo1D({"alpha_jpsi","; alpha; Counts",1000,0,2.5},"alpha_jpsi","accidweight");
  h_jpsi_alpha_SB.Write();


  TH1D h_jpsi_p_SB = *rdf_SB.Histo1D({"jpsi_p","; jpsi_p [GeV]; Counts",1000,0,10},"jpsi_p","accidweight");
  h_jpsi_p_SB.Write();


  TH1D h_jpsi_pPlus_SB = *rdf_SB.Define("jpsi_pPlus","(jpsi_p4_kin.Plus())").Histo1D({"jpsi_pPlus","; jpsi_pPlus; Counts",1000,0,10},"jpsi_pPlus","accidweight");
  h_jpsi_pPlus_SB.Write();

  TH1D h_jpsi_pMinus_SB = *rdf_SB.Histo1D({"jpsi_pMinus","; jpsi_pMinus; Counts",1000,0,10},"jpsi_pMinus","accidweight");
  h_jpsi_pMinus_SB.Write();

  TH1D h_jpsi_perp_SB = *rdf_SB.Histo1D(pPerp_model,"jpsi_perp","accidweight");
  h_jpsi_perp_SB.SetName("jpsi_perp_SB");
  h_jpsi_perp_SB.SetTitle("jpsi_perp_SB");
  h_jpsi_perp_SB.Write();

  TH2D h_kin_jpsi_SB = *rdf_SB.Histo2D(kin_model,"jpsi_p","theta_jpsi","accidweight");
  h_kin_jpsi_SB.SetName("kin_jpsi");
  h_kin_jpsi_SB.Write();

  TH1D h_theta_jpsi_SB = *rdf_SB.Histo1D(Theta_model,"theta_jpsi","accidweight");
  h_theta_jpsi_SB.SetName("theta_jpsi");
  h_theta_jpsi_SB.Write();
  //</editor-fold>

  //<editor-fold desc="JPsi SBS">
  TDirectory* JPsi_SBS = JPsiplots->mkdir("JPsi_SBS");
  JPsi_SBS->cd();

  TH1D h_jpsi_alpha_SBS = h_jpsi_alpha_ROI-h_jpsi_alpha_SB;
  h_jpsi_alpha_SBS.Write();


  TH1D h_jpsi_p_SBS = h_jpsi_p_ROI-h_jpsi_p_SB;
  h_jpsi_p_SBS.Write();


  TH1D h_jpsi_pPlus_SBS = h_jpsi_pPlus_ROI-h_jpsi_pPlus_SB;
  h_jpsi_pPlus_SBS.Write();

  TH1D h_jpsi_pMinus_SBS = h_jpsi_pMinus_ROI - h_jpsi_pMinus_SB;
  h_jpsi_pMinus_SBS.Write();

  TH1D h_jpsi_perp_SBS = h_jpsi_perp_ROI-h_jpsi_perp_SB;
  h_jpsi_perp_SBS.SetName("jpsi_perp_SBS");
  h_jpsi_perp_SBS.SetTitle("jpsi_perp_SBS");
  h_jpsi_perp_SBS.Write();

  TH2D h_kin_jpsi_SBS = h_kin_jpsi_ROI-h_kin_jpsi_SB;
  h_kin_jpsi_SBS.SetName("kin_jpsi");
  h_kin_jpsi_SBS.Write();

  TH1D h_theta_jpsi_SBS = h_theta_jpsi_ROI-h_theta_jpsi_SB;
  h_theta_jpsi_SBS.SetName("theta_jpsi");
  h_theta_jpsi_SBS.Write();
  //</editor-fold>
  //</editor-fold>

  //<editor-fold desc="Kinematic Plots">
  TDirectory* Kinplots = histFile->mkdir("Kin");
  Kinplots->cd();

  TH1D h_t_new = *rdf_final.Histo1D({"t_kin_minus","; t [GeV]; Counts",1000,0,10},"t_kin_minus","accidweight");
  h_t_new.Write();

  TH2D h_km = *rdf_final.Histo2D(k_mass_model,"k","jpsi_m_pair","accidweight");
  h_km.Write();

  TH1D h_mmiss = *rdf_final.Histo1D(mass_model,"miss_m_kin","accidweight");
  h_mmiss.SetName("mass_miss");
  h_mmiss.Write();

  TH1D h_pmiss = *rdf_final.Histo1D(pmiss_model,"pmiss","accidweight");
  h_pmiss.Write();

  TH1D h_t = *rdf_final.Histo1D(t_model,"minust_kin","accidweight");
  h_t.Write();

  TH1D h_t_low = *rdf_final.Filter("kmiss < 0.3").Histo1D(t_model,"minust_kin","accidweight");
  h_t_low.SetName("t_low");
  h_t_low.Write();

  TH1D h_t_high = *rdf_final.Filter("kmiss > 0.3").Histo1D(t_model,"minust_kin","accidweight");
  h_t_high.SetName("t_high");
  h_t_high.Write();

  TH1D h_k = *rdf_final.Histo1D(k_model,"k","accidweight");
  h_k.Write();

  TH2D h_pMinus_perp = *rdf_final.Histo2D(pMinus_pPerp_model,"pMinus_init","pPerp_init","accidweight");
  h_pMinus_perp.Write();

  TH1D h_missingMomentum_proton = *rdf_final.Histo1D(E_miss_model,"E_miss_stat_p","accidweight");
  h_missingMomentum_proton.SetName("missing Energy: stationary proton");
  h_missingMomentum_proton.SetTitle("missing Energy: stationary proton; E_miss [GeV]");
  h_missingMomentum_proton.Write();

  TH1D h_E_prot_init = *rdf_final.Histo1D(p_init_model,"E_prot_init","accidweight");
  h_E_prot_init.SetName("Proton initial energy");
  h_E_prot_init.SetTitle("Proton initial energy; E_proton_init [GeV]");
  h_E_prot_init.Write();

  TH1D h_tot_pMinus = *rdf_final.Histo1D(pMinus_model,"tot_pMinus","accidweight");
  h_tot_pMinus.SetName("tot_pMinus");
  h_tot_pMinus.SetTitle("tot_pMinus");
  h_tot_pMinus.Write();

  TH1D h_tot_perp = *rdf_final.Histo1D(pPerp_model,"tot_perp","accidweight");
  h_tot_perp.SetName("tot_perp");
  h_tot_perp.SetTitle("tot_perp");
  h_tot_perp.Write();

  TH1D h_E_gamma = *rdf_final.Histo1D(E_gamma_model,"E_gamma","accidweight");
  h_E_gamma.SetName("E_gamma");
  h_E_gamma.SetTitle("E_gamma");
  h_E_gamma.Write();

  //</editor-fold>

  //<editor-fold desc="Proton">
  TDirectory* protonPlots = histFile->mkdir("Proton");
  protonPlots->cd();

  TH1D h_p_p = *rdf_final.Histo1D(mass_model,"p_p","accidweight");
  h_p_p.SetName("p_p");
  h_p_p.Write();

  TH2D h_kin_p = *rdf_final.Histo2D(kin_model,"p_p","theta_p","accidweight");
  h_kin_p.SetName("kin_p");
  h_kin_p.Write();

  TH1D h_theta_p = *rdf_final.Histo1D(Theta_model,"theta_p","accidweight");
  h_theta_p.SetName("theta_p");
  h_theta_p.Write();

  TH1D h_p_pMinus = *rdf_final.Histo1D(pMinus_model,"p_pMinus","accidweight");
  h_p_pMinus.SetName("p_pMinus");
  h_p_pMinus.SetTitle("p_pMinus");
  h_p_pMinus.Write();

  TH1D h_p_perp = *rdf_final.Histo1D(pPerp_model,"p_perp","accidweight");
  h_p_perp.SetName("p_perp");
  h_p_perp.SetTitle("p_perp");
  h_p_perp.Write();

  //<editor-fold desc="Proton ROI">
  TDirectory* proton_ROI = protonPlots->mkdir("Proton_ROI");
  proton_ROI->cd();

  TH1D h_p_p_ROI = *rdf_ROI.Histo1D({"p_p","; p_p [GeV]; Counts",1000,0,10},"p_p","accidweight");
  h_p_p_ROI.Write();

  TH1D h_p_alpha_ROI = *rdf_ROI.Define("alpha_p","(p_pMinus/mN)").Histo1D({"alpha_p","; alpha; Counts",1000,0,2.5},"alpha_p","accidweight");
  h_p_alpha_ROI.Write();

  TH1D h_p_pPlus_ROI = *rdf_ROI.Define("p_pPlus","(p_p4_kin.Plus())").Histo1D({"p_pPlus","; p_pPlus; Counts",1000,0,10},"p_pPlus","accidweight");
  h_p_pPlus_ROI.Write();

  TH1D h_p_pMinus_ROI = *rdf_ROI.Histo1D({"p_pMinus","; p_pMinus; Counts",1000,0,10},"p_pMinus","accidweight");
  h_p_pMinus_ROI.Write();

  TH1D h_p_perp_ROI = *rdf_ROI.Histo1D(pPerp_model,"p_perp","accidweight");
  h_p_perp_ROI.SetName("p_perp_ROI");
  h_p_perp_ROI.SetTitle("p_perp_ROI");
  h_p_perp_ROI.Write();

  TH2D h_kin_p_ROI = *rdf_ROI.Histo2D(kin_model,"p_p","theta_p","accidweight");
  h_kin_p_ROI.SetName("kin_p");
  h_kin_p_ROI.Write();

  TH1D h_theta_p_ROI = *rdf_ROI.Histo1D(Theta_model,"theta_p","accidweight");
  h_theta_p_ROI.SetName("theta_p");
  h_theta_p_ROI.Write();
  //</editor-fold>

  //<editor-fold desc="Proton SB">
  TDirectory* proton_SB = protonPlots->mkdir("Proton_SB");
  proton_SB->cd();

  TH1D h_p_p_SB = *rdf_SB.Histo1D({"p_p","; p_p [GeV]; Counts",1000,0,10},"p_p","accidweight");
  h_p_p_SB.Write();

  TH1D h_p_alpha_SB = *rdf_SB.Define("alpha_p","(p_pMinus/mN)").Histo1D({"alpha_p","; alpha; Counts",1000,0,2.5},"alpha_p","accidweight");
  h_p_alpha_SB.Write();

  TH1D h_p_pPlus_SB = *rdf_SB.Define("p_pPlus","(p_p4_kin.Plus())").Histo1D({"p_pPlus","; p_pPlus; Counts",1000,0,10},"p_pPlus","accidweight");
  h_p_pPlus_SB.Write();

  TH1D h_p_pMinus_SB = *rdf_SB.Histo1D({"p_pMinus","; p_pMinus; Counts",1000,0,10},"p_pMinus","accidweight");
  h_p_pMinus_SB.Write();

  TH1D h_p_perp_SB = *rdf_SB.Histo1D(pPerp_model,"p_perp","accidweight");
  h_p_perp_SB.SetName("p_perp_SB");
  h_p_perp_SB.SetTitle("p_perp_SB");
  h_p_perp_SB.Write();

  TH2D h_kin_p_SB = *rdf_SB.Histo2D(kin_model,"p_p","theta_p","accidweight");
  h_kin_p_SB.SetName("kin_p");
  h_kin_p_SB.Write();

  TH1D h_theta_p_SB = *rdf_SB.Histo1D(Theta_model,"theta_p","accidweight");
  h_theta_p_SB.SetName("theta_p");
  h_theta_p_SB.Write();
  //</editor-fold>

  //<editor-fold desc="Proton SBS">
  TDirectory* proton_SBS = protonPlots->mkdir("Proton_SBS");
  proton_SBS->cd();

  TH1D h_p_p_SBS = h_p_p_ROI - h_p_p_SB;
  h_p_p_SBS.Write();

  TH1D h_p_alpha_SBS = h_p_alpha_ROI - h_p_alpha_SB;
  h_p_alpha_SBS.Write();

  TH1D h_p_pPlus_SBS = h_p_pPlus_ROI - h_p_pPlus_SB;
  h_p_pPlus_SBS.Write();

  TH1D h_p_pMinus_SBS = h_p_pMinus_ROI-h_p_pMinus_SB;
  h_p_pMinus_SBS.Write();

  TH1D h_p_perp_SBS = h_p_perp_ROI - h_p_perp_SB;
  h_p_perp_SBS.SetName("p_perp_SBS");
  h_p_perp_SBS.SetTitle("p_perp_SBS");
  h_p_perp_SBS.Write();

  TH2D h_kin_p_SBS = h_kin_p_ROI - h_kin_p_SB;
  h_kin_p_SBS.SetName("kin_p");
  h_kin_p_SBS.Write();

  TH1D h_theta_p_SBS = h_theta_p_ROI - h_theta_p_SB;
  h_theta_p_SBS.SetName("theta_p");
  h_theta_p_SBS.Write();
  //</editor-fold>
  //</editor-fold>

  //<editor-fold desc="Lepton">
  TDirectory* leptonPlots = histFile->mkdir("leptonPlots");
  leptonPlots->cd();

  TH2D h_emep_perp = *rdf_final.Histo2D(P_2DModel,"em_perp","ep_perp","accidweight");
  h_emep_perp.SetName("emep_perp");
  h_emep_perp.SetTitle("em_ep_perp");
  h_emep_perp.Write();

  TH2D h_emep_pMinus = *rdf_final.Histo2D(P_2DModel,"em_pMinus","ep_pMinus","accidweight");
  h_emep_pMinus.SetName("emep_pMinus");
  h_emep_pMinus.SetTitle("em_ep_pMinus");
  h_emep_pMinus.Write();

  TH1D h_em_ep_angle = *rdf_final.Histo1D(Theta_model,"em_ep_angle","accidweight");
  h_em_ep_angle.SetName("em_ep_angle");
  h_em_ep_angle.Write();

  //<editor-fold desc="Electron">
  TDirectory* emPlots = histFile->mkdir("leptonPlots/em");
  emPlots->cd();

  TH2D h_kin_em = *rdf_final.Histo2D(kin_model,"p_em","theta_em","accidweight");
  h_kin_em.SetName("kin_em");
  h_kin_em.Write();

  TH1D h_p_em = *rdf_final.Histo1D(mass_model,"p_em","accidweight");
  h_p_em.SetName("p_em");
  h_p_em.Write();

  TH1D h_theta_em = *rdf_final.Histo1D(Theta_model,"theta_em","accidweight");
  h_theta_em.SetName("theta_em");
  h_theta_em.Write();

  TH1D h_em_pMinus = *rdf_final.Histo1D(pMinus_model,"em_pMinus","accidweight");
  h_em_pMinus.SetName("em_pMinus");
  h_em_pMinus.SetTitle("em_pMinus");
  h_em_pMinus.Write();

  TH1D h_em_perp = *rdf_final.Histo1D(pPerp_model,"em_perp","accidweight");
  h_em_perp.SetName("em_perp");
  h_em_perp.SetTitle("em_perp");
  h_em_perp.Write();
  //</editor-fold>

  //<editor-fold desc="Positron">
  TDirectory* epPlots = histFile->mkdir("leptonPlots/ep");
  epPlots->cd();

  TH2D h_kin_ep = *rdf_final.Histo2D(kin_model,"p_ep","theta_ep","accidweight");
  h_kin_ep.SetName("kin_ep");
  h_kin_ep.Write();

  TH1D h_p_ep = *rdf_final.Histo1D(mass_model,"p_ep","accidweight");
  h_p_ep.SetName("p_ep");
  h_p_ep.Write();

  TH1D h_theta_ep = *rdf_final.Histo1D(Theta_model,"theta_ep","accidweight");
  h_theta_ep.SetName("theta_ep");
  h_theta_ep.Write();

  TH1D h_ep_pMinus = *rdf_final.Histo1D(pMinus_model,"ep_pMinus","accidweight");
  h_ep_pMinus.SetName("ep_pMinus");
  h_ep_pMinus.SetTitle("ep_pMinus");
  h_ep_pMinus.Write();

  TH1D h_ep_perp = *rdf_final.Histo1D(pPerp_model,"ep_perp","accidweight");
  h_ep_perp.SetName("ep_perp");
  h_ep_perp.SetTitle("ep_perp");
  h_ep_perp.Write();
  //</editor-fold>

  //</editor-fold>


  //<editor-fold desc="Vertex">
  TDirectory* vertexPlots = histFile->mkdir("Vertex");
  vertexPlots->cd();

  TH1D h_zVertex = *rdf_final.Filter("(accidweight>0)").Histo1D(Z_vertex_model,"zVertex","accidweight");
  h_zVertex.Write();

  TH2D h_xyVertex = *rdf_final.Histo2D(xyVertex_model,"xVertex","yVertex","accidweight");
  h_xyVertex.SetName("xyVertex");
  h_xyVertex.SetTitle("Hit Locations; x [cm]; y [cm]");
  h_xyVertex.Write();

  TDirectory* vertexROI = vertexPlots->mkdir("ROI");
  vertexROI->cd();


  TH2D h_xVertex2D = *rdf_ROI.Histo2D({"xVertex2D","xVertex; Lepton; Proton",100,-1,1,100,-1,1},"xVertexLepton","xVertexProton","accidweight");
  h_xVertex2D.Write();

  TH2D h_yVertex2D = *rdf_ROI.Histo2D({"yVertex2D","yVertex; Lepton; Proton",100,-1,1,100,-1,1},"yVertexLepton","yVertexProton","accidweight");
  h_yVertex2D.Write();

  TH2D h_zVertex2D = *rdf_ROI.Histo2D({"zVertex2D","zVertex; Lepton; Proton",100,50,80,100,50,80},"zVertexLepton","zVertexProton","accidweight");
  h_zVertex2D.Write();

  TH1D h_deltaXYVertex = *rdf_ROI.Histo1D({"DeltaXYVertex","DeltaXYVertex; Delta r [cm]; Counts",100,-1,1},"deltaXYVertexLepton","accidweight");
  h_deltaXYVertex.Write();

  TH1D h_deltaZVertex = *rdf_ROI.Histo1D({"DeltaZVertex","DeltaZVertex; Delta z [cm]; Counts",100,-10,10},"deltaZVertex","accidweight");
  h_deltaZVertex.Write();

  TH2D h_p_ep_theta_phi = *rdf_ROI.Histo2D({"p_ep_theta_phi","; Delta Theta [Deg]; Delta Phi [Deg]",100,-180,180,100,-180,180},"deltaTheta_p_ep","deltaPhi_p_ep","accidweight");
  h_p_ep_theta_phi.Write();
  //</editor-fold>

}
