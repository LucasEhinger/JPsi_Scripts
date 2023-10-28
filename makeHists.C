//
// Created by Lucas Ehinger on 10/27/23.
//

#include "analyzeData.h"
using namespace ROOT;
using namespace std;

void makeParticleKinPlots(RNode rdf_in,TFile* histFile, TDirectory* currentDirectory,string particle){

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

void makeKinPlots(RNode rdf_in,TFile* histFile, TDirectory* currentDirectory){
  auto rdf_ROI= rdf_in.Filter("((jpsi_m_pair>3)&&(jpsi_m_pair<3.2))");
  auto rdf_SB= rdf_in.Filter("(((jpsi_m_pair>2.9)&&(jpsi_m_pair<3))||((jpsi_m_pair>3.2)&&(jpsi_m_pair<3.3)))");

  //<editor-fold desc="ROI Plots">
  TDirectory* ROI_plots = currentDirectory->mkdir("ROI");
  ROI_plots->cd();

  TH1D h_t_new_ROI = *rdf_ROI.Histo1D({"t_kin_minus_ROI","; t [GeV]; Counts",1000,0,10},"t_kin_minus","accidweight");
  h_t_new_ROI.Write();

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

  TH1D h_t_new_SB = *rdf_SB.Histo1D({"t_kin_minus_SB","; t [GeV]; Counts",1000,0,10},"t_kin_minus","accidweight");
  h_t_new_SB.Write();

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

  TH1D h_t_new_SBS = h_t_new_ROI - h_t_new_SB;
  h_t_new_SBS.SetName("t_kin_minus_SBS");
  h_t_new_SBS.Write();

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

  TH1D h_mmeas = *rdf_in.Histo1D(mass_model,"jpsi_m_meas","accidweight");
  h_mmeas.SetName("mass_meas");
  h_mmeas.Write();

  TH1D h_mkin = *rdf_in.Histo1D(mass_model,"jpsi_m_kin","accidweight");
  h_mkin.SetName("mass_kin");
  h_mkin.Write();

  TH1D h_mstand = *rdf_in.Histo1D(mass_model,"jpsi_m_stand","accidweight");
  h_mstand.SetName("mass_stand");
  h_mstand.Write();


  TH1D h_mpair = *rdf_in.Histo1D({"mass_pair","; m_ee [GeV]; Counts",2000,2,4},"jpsi_m_pair","accidweight");
  h_mpair.Write();

  TH1D h_mpair_nn = *rdf_in.Filter("(accidweight>0)").Histo1D(mass_model,"jpsi_m_pair","accidweight");
  h_mpair_nn.SetName("mass_pair_no_neg");
  h_mpair_nn.Write();

  TH2D h_mpair_v_mkin = *rdf_in.Histo2D({"mpair_v_mkin","; m_ee (Pair) [GeV/c^2]; m_ee (Kin) [GeV/c^2]",500,2,3.5,500,2,3.5},"jpsi_m_pair","jpsi_m_kin","accidweight");
  h_mpair_v_mkin.Write();
  //</editor-fold>

}

void makeAllPlots(RNode rdf_in,TFile* histFile, TDirectory* currentDirectory){
  TDirectory* kinematic_plots = currentDirectory->mkdir("Kin");
  kinematic_plots->cd();
  makeKinPlots(rdf_in, histFile, kinematic_plots);

  TDirectory* jpsi_plots = currentDirectory->mkdir("jpsi");
  jpsi_plots->cd();
  makeParticleKinPlots(rdf_in, histFile, jpsi_plots,"jpsi");

  TDirectory* p_plots = currentDirectory->mkdir("p");
  p_plots->cd();
  makeParticleKinPlots(rdf_in, histFile, p_plots,"p");

  TDirectory* em_plots = currentDirectory->mkdir("em");
  em_plots->cd();
  makeParticleKinPlots(rdf_in, histFile, em_plots,"em");

  TDirectory* ep_plots = currentDirectory->mkdir("ep");
  ep_plots->cd();
  makeParticleKinPlots(rdf_in, histFile, ep_plots,"ep");
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

  //Start defining histograms

  TFile * histFile = new TFile(outFileName.c_str(),"RECREATE");

  histFile->cd();


  makeAllPlots(rdf_final,histFile, histFile);


//Old Plots. Not currently using, but might want later

//  //<editor-fold desc="Pion Rejection">
//  TDirectory* PionRejectPlots = histFile->mkdir("PionRejection");
//  PionRejectPlots->cd();
//
////  TH2D h_Cal_PoverE = *rdf_final.Filter("(fcal_PoverE>0)").Filter("bcal_PoverE>0")
////          .Histo2D(EP_2DModel,"fcal_PoverE","bcal_PoverE","accidweight");
////  h_Cal_PoverE.SetName("Cal_PoverE");
////  h_Cal_PoverE.SetTitle("; fcal p/E; bcal p/E");
////  h_Cal_PoverE.Write();
////
////
////  TH1D h_fCal_PoverE = *rdf_final.Histo1D(PE_Ratio_model,"fcal_PoverE","accidweight");
////  h_fCal_PoverE.SetName("fcal_PoverE");
////  h_fCal_PoverE.SetTitle("P/E");
////  h_fCal_PoverE.Write();
////
////  TH1D h_bCal_PoverE = *rdf_final.Histo1D(PE_Ratio_model,"bcal_PoverE","accidweight");
////  h_bCal_PoverE.SetName("bcal_PoverE");
////  h_bCal_PoverE.SetTitle("P/E");
////  h_bCal_PoverE.Write();
//
//  TH1D h_em_PoverE = *rdf_final.Histo1D(PE_Ratio_model,"em_PoverE","accidweight");
//  h_em_PoverE.SetName("em_PoverE");
//  h_em_PoverE.SetTitle("P/E");
//  h_em_PoverE.Write();
//
//  TH1D h_ep_PoverE = *rdf_final.Histo1D(PE_Ratio_model,"ep_PoverE","accidweight");
//  h_ep_PoverE.SetName("ep_PoverE");
//  h_ep_PoverE.SetTitle("P/E");
//  h_ep_PoverE.Write();
//
//  TH1D h_lep_PoverE = h_em_PoverE+h_ep_PoverE;
//  h_lep_PoverE.SetName("lep_PoverE");
//  h_lep_PoverE.SetTitle("P/E");
//  h_lep_PoverE.Write();
//
//  TH1D h_em_preB_sin = *rdf_final.Filter("(em_ebcal!=0)").Histo1D(preB_sin_model,"em_eprebcal_sinTheta","accidweight");
//  h_em_preB_sin.SetName("em_eprebcal_sinTheta");
//  h_em_preB_sin.Write();
//
//  TH1D h_ep_preB_sin = *rdf_final.Filter("(ep_ebcal!=0)").Histo1D(preB_sin_model,"ep_eprebcal_sinTheta","accidweight");
//  h_ep_preB_sin.SetName("ep_eprebcal_sinTheta");
//  h_ep_preB_sin.Write();
//
//  TH2D h_PoverE_2D = *rdf_final.Histo2D(EP_2DModel,"em_PoverE","ep_PoverE","accidweight");
//  h_PoverE_2D.SetName("PoverE_2D");
//  h_PoverE_2D.SetTitle("P/E");
//  h_PoverE_2D.Write();
//  //</editor-fold>
//
//
//  //<editor-fold desc="Vertex">
//  TDirectory* vertexPlots = histFile->mkdir("Vertex");
//  vertexPlots->cd();
//
//  TH1D h_zVertex = *rdf_final.Filter("(accidweight>0)").Histo1D(Z_vertex_model,"zVertex","accidweight");
//  h_zVertex.Write();
//
//  TH2D h_xyVertex = *rdf_final.Histo2D(xyVertex_model,"xVertex","yVertex","accidweight");
//  h_xyVertex.SetName("xyVertex");
//  h_xyVertex.SetTitle("Hit Locations; x [cm]; y [cm]");
//  h_xyVertex.Write();
//
//  TDirectory* vertexROI = vertexPlots->mkdir("ROI");
//  vertexROI->cd();
//
//
//  TH2D h_xVertex2D = *rdf_ROI.Histo2D({"xVertex2D","xVertex; Lepton; Proton",100,-1,1,100,-1,1},"xVertexLepton","xVertexProton","accidweight");
//  h_xVertex2D.Write();
//
//  TH2D h_yVertex2D = *rdf_ROI.Histo2D({"yVertex2D","yVertex; Lepton; Proton",100,-1,1,100,-1,1},"yVertexLepton","yVertexProton","accidweight");
//  h_yVertex2D.Write();
//
//  TH2D h_zVertex2D = *rdf_ROI.Histo2D({"zVertex2D","zVertex; Lepton; Proton",100,50,80,100,50,80},"zVertexLepton","zVertexProton","accidweight");
//  h_zVertex2D.Write();
//
//  TH1D h_deltaXYVertex = *rdf_ROI.Histo1D({"DeltaXYVertex","DeltaXYVertex; Delta r [cm]; Counts",100,-1,1},"deltaXYVertexLepton","accidweight");
//  h_deltaXYVertex.Write();
//
//  TH1D h_deltaZVertex = *rdf_ROI.Histo1D({"DeltaZVertex","DeltaZVertex; Delta z [cm]; Counts",100,-10,10},"deltaZVertex","accidweight");
//  h_deltaZVertex.Write();
//
//  TH2D h_p_ep_theta_phi = *rdf_ROI.Histo2D({"p_ep_theta_phi","; Delta Theta [Deg]; Delta Phi [Deg]",100,-180,180,100,-180,180},"deltaTheta_p_ep","deltaPhi_p_ep","accidweight");
//  h_p_ep_theta_phi.Write();
//  //</editor-fold>

}
