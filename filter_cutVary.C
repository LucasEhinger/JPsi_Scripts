#include "analyzeData.h"
#include <time.h>

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

bool passEoverP(double p, double Efcal, double Ebcal, bool isFCAL, double sigma_minus, double sigma_plus)
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

void filter_cutVary(string inFileName, string outFileName, string treeName = "e_e_p_X", string numIters="5")
{

// Time the script:
  clock_t tStart = clock();

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
          .Define("pMinus_init","init_p4_kin.Minus()")
          .Define("pPerp_init","init_p4_kin.Perp()")
          .Define("miss_p4_meas","N2_p4 + beam_p4_meas - jpsi_p4_meas - p_p4_meas")
          .Define("miss_p4_kin","N2_p4 + beam_p4_kin - jpsi_p4_kin - p_p4_kin")
          .Define("miss_m_meas","miss_p4_meas.M()")
          .Define("miss_m_kin","miss_p4_kin.M()")
          .Define("ep_EoverP","(ep_efcal+ep_ebcal)/ep_p4_kin.P()")
          .Define("em_EoverP","(em_efcal+em_ebcal)/em_p4_kin.P()")
          .Define("xVertex","p_x4_kin.X()")
          .Define("yVertex","p_x4_kin.Y()")
          .Define("zVertex","p_x4_kin.Z()")
          .Define("Delta_kin","beam_p4_kin - jpsi_p4_kin")
          .Define("t_kin","Delta_kin.M2()")//Don't use these
          .Define("minust_kin","-t_kin")//Don't use these
          .Define("pmiss","miss_p4_kin.P()")
          .Define("k","beam_p4_kin.P()")
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
          .Define("em_ep_angle", "(ep_p4_kin.Angle(em_p4_kin.Vect())*180/3.1415)")
          .Define("em_eprebcal_sinTheta", "em_eprebcal*sin(em_theta*3.1415/180)")
          .Define("ep_eprebcal_sinTheta", "ep_eprebcal*sin(ep_theta*3.1415/180)")
          .Define("em_pMinus","em_p4_kin.Minus()")
          .Define("ep_pMinus","ep_p4_kin.Minus()")
          .Define("p_pMinus","p_p4_kin.Minus()")
          .Define("jpsi_pMinus","jpsi_p4_kin.Minus()")
          .Define("em_pPlus","em_p4_kin.Plus()")
          .Define("ep_pPlus","ep_p4_kin.Plus()")
          .Define("p_pPlus","p_p4_kin.Plus()")
          .Define("jpsi_pPlus","jpsi_p4_kin.Plus()")
          .Define("em_perp","em_p4_kin.Perp()")
          .Define("ep_perp","ep_p4_kin.Perp()")
          .Define("p_perp","p_p4_kin.Perp()")
          .Define("jpsi_perp","jpsi_p4_kin.Perp()")
          .Define("jpsi_alpha","(jpsi_pMinus/mN)")
          .Define("p_alpha","(p_pMinus/mN)")
          .Define("n_alpha","(2-jpsi_alpha-p_alpha)")
          .Define("E_miss_stat_p","(mN + beam_p4_kin.T() - jpsi_p4_kin.T() - p_p4_kin.T())")
          .Define("E_prot_init","(jpsi_p4_kin.T() + p_p4_kin.T() - beam_p4_kin.T())")
          .Define("em_PoverE","em_p4_kin.P()/(em_efcal+em_ebcal)")
          .Define("ep_PoverE","ep_p4_kin.P()/(ep_efcal+ep_ebcal)")
          .Define("tot_p4_kin","(jpsi_p4_kin+p_p4_kin-beam_p4_kin)")
          .Define("tot_perp","(tot_p4_kin.Perp())")
          .Define("tot_pMinus","(tot_p4_kin.Minus())")
          .Define("alpha_miss","(tot_pMinus/mN)")
          .Define("kmiss","mN*sqrt((mN*mN + tot_p4_kin.Perp2())/(tot_p4_kin.Minus()*(2*mN - tot_p4_kin.Minus())) - 1)")
          .Define("mJPsi","(3.096)")
          .Define("t_kin_minus","(-(mJPsi*mJPsi-2*E_gamma*(jpsi_p4_kin.Minus())))")
          .Define("xVertexLepton","returnGreaterThetaVertex(em_theta, ep_theta, em_x4_meas.X(), ep_x4_meas.X())")
          .Define("yVertexLepton","returnGreaterThetaVertex(em_theta, ep_theta, em_x4_meas.Y(), ep_x4_meas.Y())")
          .Define("zVertexLepton","returnGreaterThetaVertex(em_theta, ep_theta, em_x4_meas.Z(), ep_x4_meas.Z())")
          .Define("xVertexProton","p_x4_meas.X()")
          .Define("yVertexProton","p_x4_meas.Y()")
          .Define("zVertexProton","p_x4_meas.Z()")
          .Define("deltaXYVertexLepton","sqrt(xVertexLepton*xVertexLepton+yVertexLepton*yVertexLepton)-sqrt(xVertexProton*xVertexProton+yVertexProton*yVertexProton)")
          .Define("deltaZVertex","zVertexLepton-zVertexProton")
          .Define("deltaTheta_p_ep","(p_p4_meas.Theta()-ep_p4_meas.Theta())*180/3.14159")
          .Define("deltaPhi_p_ep","(p_p4_meas.Phi()-ep_p4_meas.Phi())*180/3.14159")
          .Define("em_isFCAL","em_efcal > em_ebcal")
          .Define("ep_isFCAL","ep_efcal > ep_ebcal");

  auto rdf_fiducial=rdf_def.Filter("(jpsi_m_pair > 2) && (jpsi_m_pair < 3.5)")
          .Filter("(zVertex > 51) && (zVertex < 79) && (xVertex*xVertex + yVertex*yVertex < 1*1)")
          .Filter("(em_theta > 2) && (ep_theta > 2) && (p_theta > 2)")
          .Filter("(em_p > 0.4) && (ep_p > 0.4) && (p_p > 0.4)");

  string track_shower_sel="1";
  string track_shower_cut="";
  switch (stoi(track_shower_sel)){
    case 0:
      track_shower_cut="(unusedShowers == 0) && (unusedTracks == 0)";
      break;
    case 1:
      track_shower_cut="(unusedShowers == 0) && (unusedTracks < 2)";
      break;
    case 2:
      track_shower_cut="(unusedShowers < 2) && (unusedTracks == 0)";
      break;
    case 3:
      track_shower_cut="(unusedShowers < 2) && (unusedTracks < 2)";
      break;
    default:
      track_shower_cut="(unusedShowers < 10) && (unusedTracks < 10)";
      break;
  }
  auto rdf_track_shower=rdf_fiducial.Filter(track_shower_cut.c_str());


  auto rand3 = new TRandom3(3096);

  double preBCut_min=0.25;
  double preBCut_max=0.35;
  double sigma_minus_min=-3.5;
  double sigma_minus_max=-2.5;
  double sigma_plus_min=1.5;
  double sigma_plus_max=2.5;
  double EMissCut_min=0.5;
  double EMissCut_max=1.5;

  TFile * histFile = new TFile(outFileName.c_str(),"RECREATE");
  histFile->cd();

  for(int i=0;i<stoi(numIters);i++){
    string preBCut = to_string(rand3->Uniform(preBCut_min,preBCut_max));
    string sigma_minus = to_string(rand3->Uniform(sigma_minus_min,sigma_minus_max));
    string sigma_plus = to_string(rand3->Uniform(sigma_plus_min,sigma_plus_max));
    string EMissCut = to_string(rand3->Uniform(EMissCut_min,EMissCut_max));

    auto rdf_preShower=rdf_track_shower.Filter("(em_eprebcal_sinTheta > " +preBCut + ") || (em_efcal > 0 )")
            .Filter("(ep_eprebcal_sinTheta > " +preBCut + ") || (ep_efcal > 0 )");

    auto rdf_PoverE=rdf_preShower.Filter("(passEoverP(em_p4_kin.P(),em_efcal,em_ebcal,em_isFCAL," + sigma_minus + "," + sigma_plus + "))")
            .Filter("(passEoverP(ep_p4_kin.P(),ep_efcal,ep_ebcal,ep_isFCAL," + sigma_minus + "," + sigma_plus + "))");

    auto rdf_final=rdf_PoverE.Filter("(fabs(E_miss_stat_p) < " + EMissCut + ")");

    TDirectory* iteration_dir = histFile->mkdir(("Iteration_"+to_string(i)).c_str());
    iteration_dir->cd();
    string paramVals=preBCut+";"+sigma_minus+";"+sigma_minus+";"+EMissCut+";";
    TNamed params("param_vals",paramVals.c_str());

    params.Write();
    makePlots(rdf_final,histFile,iteration_dir);
  }

  clock_t tEnd = clock();
  double elapsed = (double(tEnd - tStart)/CLOCKS_PER_SEC/60);

  printf("Total time: %.2f min.\n", elapsed);
}
