//
// Created by Lucas Ehinger on 6/9/23.
//

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

void addDefinitions(string inFileName, string outFileName, string treeName = "e_e_p_X")
{

  using namespace ROOT;
  using namespace std;

  EnableImplicitMT();
  TChain chain(treeName.c_str());
  chain.Add(inFileName.c_str());

  RDataFrame rdf_def(chain);

  auto rdf_final = rdf_def
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
          .Define("p_miss_stat_p","(mN + beam_p4_kin.T() - jpsi_p4_kin.T() - p_p4_kin.T())")
          .Define("E_prot_init","(jpsi_p4_kin.T() + p_p4_kin.T() - beam_p4_kin.T())")
          .Define("em_PoverE","em_p4_kin.P()/(em_efcal+em_ebcal)")
          .Define("ep_PoverE","ep_p4_kin.P()/(ep_efcal+ep_ebcal)")
          .Define("tot_p4_kin","(jpsi_p4_kin+p_p4_kin-beam_p4_kin)")
          .Define("tot_perp","(tot_p4_kin.Perp())")
          .Define("tot_pMinus","(tot_p4_kin.Minus())")
          .Define("alpha_miss","(tot_pMinus/mN)")
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
          .Define("deltaPhi_p_ep","(p_p4_meas.Phi()-ep_p4_meas.Phi())*180/3.14159");





//  auto rdf_final = rdf_def.Redefine("em_eprebcal_sinTheta", "em_eprebcal*sin(theta_em*3.1415/180)")
//          .Redefine("ep_eprebcal_sinTheta", "ep_eprebcal*sin(theta_ep*3.1415/180)")
//          .Define("E_prot_init","(jpsi_p4_kin.T() + p_p4_kin.T() - beam_p4_kin.T())");

  rdf_final.Snapshot(treeName.c_str(),outFileName.c_str());
}
