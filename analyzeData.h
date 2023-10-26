using namespace std;
using namespace ROOT::RDF;
using namespace ROOT::Detail::RDF;

vector<TH1*> hists;

TH1DModel zVertex_model("zVertex", ";z Vertex [cm];Counts",1000,0,200);
TH2DModel xyVertex_model("xyVertex", ";x Vertex [cm];y Vertex [cm]",1000,-5,5,1000,-5,5);
TH1DModel mass_model("mass",";m_ee [GeV];Counts",1000,0,10);
TH1DModel E_miss_model("mass",";m_ee [GeV];Counts",1000,-10,10);
TH1DModel t_model("t",";-t [GeV^2];Counts",1000,0,10);
TH1DModel pmiss_model("pmiss",";p_miss [GeV];Counts",1000,0,1);
TH1DModel PE_Ratio_model("PE ratio",";p/E;Counts",1000,0.5,1.5);
TH1DModel Theta_model("Theta",";Theta",1000,0,180);
TH1DModel preB_sin_model("preB sin(Theta)",";preB sin(Theta)",1000,0,0.3);
TH1DModel pPerp_model("pPerp",";pPerp [GeV];Counts",1000,0,10);
TH1DModel pMinus_model("pMinus",";pMinus [GeV];Counts",1000,0,10);
TH1DModel E_gamma_model("E_gamma",";E_gamma [GeV];Counts",1000,6,11);
TH1DModel Z_vertex_model("Z-location",";Z-location;Counts",10000,30,150);
TH1DModel p_init_model("Z-location","Proton initial energy; E_proton_init [GeV];Counts",10000,-10,10);

double kbins[17] = {7,7.5,8,8.5,8.9,9.2,9.5,9.75,10,10.25,10.5,10.75,11,11.2,11.4,11.6,12};

//TH1DModel k_model("k",";k [GeV];Counts",10,7,12);
TH1DModel k_model("k",";k [GeV];Counts",16,kbins);

TH2DModel k_mass_model("k_mass",";k [GeV]; m_ee [GeV]",100,7,12,1000,0,10);

TH2DModel kin_model("kin",";p [GeV];Theta [degrees]",120,0,12,180,0,180);

TH2DModel pMinus_pPerp_model("minus_perp",";pMinus [GeV]; pPerp [GeV]",100,0,4,100,0,4);

TH2DModel EP_2DModel("EP Ratio",";em;ep",100,0.5,1.5,100,0.5,1.5);

TH2DModel P_2DModel("",";em;ep",100,0,2,100,0,2);

TH2DModel fom_model("FOM",";em;ep",100,0,0.01,100,0,0.01);
TH2DModel preBCal_2D_model("E preBcal Sin(Theta)",";em;ep",1000,0,2,1000,0,2);


