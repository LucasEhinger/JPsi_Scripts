using namespace std;
using namespace ROOT::RDF;
using namespace ROOT::Detail::RDF;

vector<TH1*> hists;

TH1DModel zVertex_model("zVertex", ";z Vertex [cm];Counts",1000,0,200);
TH2DModel xyVertex_model("xyVertex", ";x Vertex [cm];y Vertex [cm]",100,-5,5,100,-5,5);
TH1DModel mass_model("mass",";m_ee [GeV];Counts",1000,0,10);
TH1DModel t_model("t",";-t [GeV^2];Counts",1000,0,10);
TH1DModel pmiss_model("pmiss",";p_miss [GeV];Counts",1000,0,1);

double kbins[17] = {7,7.5,8,8.5,8.9,9.2,9.5,9.75,10,10.25,10.5,10.75,11,11.2,11.4,11.6,12};

//TH1DModel k_model("k",";k [GeV];Counts",10,7,12);
TH1DModel k_model("k",";k [GeV];Counts",16,kbins);

TH2DModel k_mass_model("k_mass",";k [GeV]; m_ee [GeV]",100,7,12,1000,0,10);
  
TH2DModel kin_model("kin",";p [GeV];Theta [degrees]",120,0,12,180,0,180);

TH2DModel pMinus_pPerp_model("minus_perp",";pMinus [GeV]; pPerp [GeV]",100,0,4,100,0,4);
