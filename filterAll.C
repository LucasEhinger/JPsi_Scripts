#include "analyzeData.h"
double returnNonZeroPoverE(double em_ebcal, double ep_ebcal, double em_p, double ep_p){
  if(em_ebcal>0){
    return em_p/em_ebcal;}
  else if(ep_ebcal>0){
    return ep_p/ep_ebcal;}
  else {
    return 0;}
}

double returnGreaterThetaVertex(double theta_em, double theta_ep, double vertex_em, double vertex_ep){
  if(theta_em>theta_ep){
    return vertex_em;}
  else {
    return vertex_ep;}
}
bool passEoverP(double p, double Efcal, double Ebcal, bool isFCAL, double fcalMin, double fcalMax, double bcalMin, double bcalMax)
{
  if (isFCAL)
  {
    return ((p/Efcal > fcalMin) && (p/Efcal < fcalMax));
  }
  else
    return ((p/Ebcal > bcalMin) && (p/Ebcal < bcalMax));
}

void filterAll(string inFileName, string outFileName, string treeName = "e_e_p_X",string fcalMin="0.8078", string fcalMax="1.3186",
               string bcalMin="0.8123", string bcalMax="1.2450", string EMissCut="1", string theta_p_cut="80", string preBCut="50")
{

  using namespace ROOT;
  using namespace std;

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
          .Define("t_kin","Delta_kin.M2()")
          .Define("minust_kin","-t_kin")
          .Define("pmiss","miss_p4_kin.P()")
          .Define("k","beam_p4_kin.P()")
          .Define("Delta_plus","1*(miss_p4_kin.Plus() - (mN*mN + miss_p4_kin.Perp2())/miss_p4_kin.Minus())")
          .Define("p_em","em_p4_kin.P()")
          .Define("theta_em","em_p4_kin.Theta()*180/3.14159265")
          .Define("p_ep","ep_p4_kin.P()")
          .Define("theta_ep","ep_p4_kin.Theta()*180/3.14159265")
          .Define("p_p","p_p4_kin.P()")
          .Define("theta_p","p_p4_kin.Theta()*180/3.14159265")
          .Define("jpsi_m_pair","sqrt(jpsi_m_kin*jpsi_m_kin + 1*Delta_plus * jpsi_p4_kin.Minus())")
          .Define("jpsi_m_stand","sqrt((mN + beam_p4_kin.Plus() - p_p4_kin.Plus()) * jpsi_p4_kin.Minus() - jpsi_p4_kin.Perp2())")
          .Define("E_gamma","beam_p4_kin.T()")
          .Define("em_ep_angle", "(ep_p4_kin.Angle(em_p4_kin.Vect())*180/3.1415)")
          .Define("em_eprebcal_sinTheta", "em_eprebcal*sin(theta_em*3.1415/180)")
          .Define("ep_eprebcal_sinTheta", "ep_eprebcal*sin(theta_ep*3.1415/180)")
          .Define("em_pMinus","em_p4_kin.Minus()")
          .Define("ep_pMinus","ep_p4_kin.Minus()")
          .Define("p_pMinus","p_p4_kin.Minus()")
          .Define("jpsi_pMinus","jpsi_p4_kin.Minus()")
          .Define("em_perp","em_p4_kin.Perp()")
          .Define("ep_perp","ep_p4_kin.Perp()")
          .Define("p_perp","p_p4_kin.Perp()")
          .Define("jpsi_perp","jpsi_p4_kin.Perp()")
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
          .Define("xVertexLepton","returnGreaterThetaVertex(theta_em, theta_ep, em_x4_meas.X(), ep_x4_meas.X())")
          .Define("yVertexLepton","returnGreaterThetaVertex(theta_em, theta_ep, em_x4_meas.Y(), ep_x4_meas.Y())")
          .Define("zVertexLepton","returnGreaterThetaVertex(theta_em, theta_ep, em_x4_meas.Z(), ep_x4_meas.Z())")
          .Define("xVertexProton","p_x4_meas.X()")
          .Define("yVertexProton","p_x4_meas.Y()")
          .Define("zVertexProton","p_x4_meas.Z()")
          .Define("deltaXYVertexLepton","sqrt(xVertexLepton*xVertexLepton+yVertexLepton*yVertexLepton)-sqrt(xVertexProton*xVertexProton+yVertexProton*yVertexProton)")
          .Define("deltaZVertex","zVertexLepton-zVertexProton")
          .Define("deltaTheta_p_ep","(p_p4_meas.Theta()-ep_p4_meas.Theta())*180/3.14159")
          .Define("deltaPhi_p_ep","(p_p4_meas.Phi()-ep_p4_meas.Phi())*180/3.14159")
          .Filter("(jpsi_m_pair > 2) && (jpsi_m_pair < 3.5)")
          .Filter("(zVertex > 51) && (zVertex < 79) && (xVertex*xVertex + yVertex*yVertex < 1*1)")
          .Filter("(theta_em > 2) && (theta_ep > 2) && (theta_p > 2)")
          .Filter("(p_em > 0.4) && (p_ep > 0.4) && (p_p > 0.4)")
          .Filter("(unusedShowers == 0) && (unusedTracks == 0)")
          .Define("em_isFCAL","em_efcal > em_ebcal")
          .Define("ep_isFCAL","ep_efcal > ep_ebcal")
          .Filter("(passEoverP(em_p4_kin.P(),em_efcal,em_ebcal,em_isFCAL," + fcalMin + "," + fcalMax + ","  + bcalMin + "," + bcalMax + "))")
          .Filter("(passEoverP(ep_p4_kin.P(),ep_efcal,ep_ebcal,ep_isFCAL," + fcalMin + "," + fcalMax + ","  + bcalMin + "," + bcalMax + "))")
          .Filter("(fabs(E_miss_stat_p) < " + EMissCut + ")")
          .Filter("(theta_p < " +theta_p_cut + ")")
          .Filter("(em_eprebcal_sinTheta > " +preBCut + ") || (em_efcal > 0 )")
          .Filter("(ep_eprebcal_sinTheta > " +preBCut + ") || (ep_efcal > 0 )");

//  .Filter("(em_eprebcal_sinTheta > " +preBCut + ") || (ep_eprebcal_sinTheta > " +preBCut + ")");


  rdf_def.Snapshot(treeName.c_str(),outFileName.c_str());

}
