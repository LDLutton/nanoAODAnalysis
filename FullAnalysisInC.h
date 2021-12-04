#include<TTree.h>

bool debug = false;
bool debugHadronic = false;
bool debugGenPart = false;
bool endAfter = false;
int NToStart = 0;
int NToEnd = 2500;

bool testRun = true;
bool LaraTest = false;
bool MGSM = false;
bool MGEFT = false;
bool ttHToBBBackground = false;
bool ttZJetsBackground = false;
bool DYBackground = false;
bool QCDPT170to300Background = false;
bool QCDPT300to470Background = false;
bool QCDPT470to600Background = false;
bool QCDPT600to800Background = false;
bool QCDPT800to1000Background = false;
bool QCDPT1000to1400Background = false;
bool QCDPT1400to1800Background = false;
bool QCDPT1800to2400Background = false;
bool QCDPT2400to3200Background = false;
bool QCDPT3200toInfBackground = false;
bool QCDSum = false;

bool isBackground = false;
/*
//Tree for holding the number of events run over;
//and the number of events that passed the cut;
UInt_t nEv;
UInt_t nEvPass;

TTree *evNumTree = new TTree("evNumTree","evNumTree");

evNumTree->Branch("nEv",&nEv,"nEv/i");
evNumTree->Branch("nEvPass",&nEvPass,"nEvPass/i")

//creating Full Analysis tree
//"L" is for leaf
//First jets
UInt_t nJetL;
float jetLeadPtL;
float jetTrailingPtL;
float jetLeadPhiL;
float jetTrailingPhiL;
float jetPairInvMassL;
float jetLeadEtaL;
float jetTrailingEtaL;
//now fat jets
UInt_t nFatJetL;

float hFatJet_pt_fromPtL;
float hFatJet_phi_fromPtL;
float hFatJet_eta_fromPtL;
float hFatJet_mass_fromPtL;
float hFatJet_HTag_fromPtL;
float hFatJet_pt_fromHTagL;
float hFatJet_phi_fromHTagL;
float hFatJet_eta_fromHTagL;
float hFatJet_mass_fromHTagL;
float hFatJet_HTag_fromHTagL;

//Now GenPart

UInt_t nGenPartL;
float hGenPartDR_fromPtL;
float hGenPartInd_fromPtL;
float hGenPartpdgId_fromPtL;
Int_t hGenPartFirstMompdgId_fromPtL;
float hGenPartDR_fromHTagL;
float hGenPartInd_fromHTagL;
float hGenPartpdgId_fromHTagL;
Int_t hGenPartFirstMompdgId_fromHTagL;

//Now HLT stuff;
bool hbbTagL;

bool doubleElecHLTL;
bool doubleMuonHLTL;
bool muonEGHLTL;
bool elecHLTL;
bool muonHLTL;
bool hadHLTL;
bool isLeptonicL;
bool isSemiLeptonicL;
bool isHadronicL;

//Branches for distinguishing between channels;
bool passedLepL;
bool passedSemiLepL;
bool passedHadL;

//Now tree and branches;

TTree *FATree = new TTree("FATree", "FATree");

//cutTree->Branch("evInd",evInd,"evInd/I");

FATree->Branch("nJetL",&nJetL,"nJetL/i");
FATree->Branch("jetLeadPtL",&jetLeadPtL,"jetLeadPtL/F");
FATree->Branch("jetTrailingPtL",&jetTrailingPtL,"jetTrailingPtL/F");
FATree->Branch("jetLeadPhiL",&jetLeadPhiL,"jetLeadPhiL/F");
FATree->Branch("jetTrailingPhiL",&jetTrailingPhiL,"jetTrailingPhiL/F");
FATree->Branch("jetPairInvMassL",&jetPairInvMassL,"jetPairInvMassL/F");
FATree->Branch("jetLeadEtaL",&jetLeadEtaL,"jetLeadEtaL/F");
FATree->Branch("jetTrailingEtaL",&jetTrailingEtaL,"jetTrailingEtaL/F");
//now fat jets;
FATree->Branch("nFatJetL",&nFatJetL,"nFatJetL/i");

FATree->Branch("hFatJet_pt_fromPtL",&hFatJet_pt_fromPtL,"hFatJet_pt_fromPtL/F");
FATree->Branch("hFatJet_phi_fromPtL",&hFatJet_phi_fromPtL,"hFatJet_phi_fromPtL/F");
FATree->Branch("hFatJet_eta_fromPtL",&hFatJet_eta_fromPtL,"hFatJet_eta_fromPtL/F");
FATree->Branch("hFatJet_mass_fromPtL",&hFatJet_mass_fromPtL,"hFatJet_mass_fromPtL/F");
FATree->Branch("hFatJet_HTag_fromPtL",&hFatJet_HTag_fromPtL,"hFatJet_HTag_fromPtL/F");
FATree->Branch("hFatJet_pt_fromHTagL",&hFatJet_pt_fromHTagL,"hFatJet_pt_fromHTagL/F");
FATree->Branch("hFatJet_phi_fromHTagL",&hFatJet_phi_fromHTagL,"hFatJet_phi_fromHTagL/F");
FATree->Branch("hFatJet_eta_fromHTagL",&hFatJet_eta_fromHTagL,"hFatJet_eta_fromHTagL/F");
FATree->Branch("hFatJet_mass_fromHTagL",&hFatJet_mass_fromHTagL,"hFatJet_mass_fromHTagL/F");
FATree->Branch("hFatJet_HTag_fromHTagL",&hFatJet_HTag_fromHTagL,"hFatJet_HTag_fromHTagL/F");

//now genpart
FATree->Branch("nGenPartL",&nGenPartL,"nGenPartL/i");
FATree->Branch("hGenPartDR_fromPtL",&hGenPartDR_fromPtL,"hGenPartDR_fromPtL/F");
FATree->Branch("hGenPartInd_fromPtL",&hGenPartInd_fromPtL,"hGenPartInd_fromPtL/F");
FATree->Branch("hGenPartpdgId_fromPtL",&hGenPartpdgId_fromPtL,"hGenPartpdgId_fromPtL/F");
FATree->Branch("hGenPartFirstMompdgId_fromPtL",&hGenPartFirstMompdgId_fromPtL,"hGenPartFirstMompdgId_fromPtL/I");
FATree->Branch("hGenPartDR_fromHTagL",&hGenPartDR_fromHTagL,"hGenPartDR_fromHTagL/F");
FATree->Branch("hGenPartInd_fromHTagL",&hGenPartInd_fromHTagL,"hGenPartInd_fromHTagL/F");
FATree->Branch("hGenPartpdgId_fromHTagL",&hGenPartpdgId_fromHTagL,"hGenPartpdgId_fromHTagL/F");
FATree->Branch("hGenPartFirstMompdgId_fromHTagL",&hGenPartFirstMompdgId_fromHTagL,"hGenPartFirstMompdgId_fromHTagL/I");

//Now HLT stuff;

FATree->Branch("hbbTagL",&hbbTagL,"hbbTagL/O");

FATree->Branch("doubleElecHLTL",&doubleElecHLTL,"doubleElecHLTL/O");
FATree->Branch("doubleMuonHLTL",&doubleMuonHLTL,"doubleMuonHLTL/O");
FATree->Branch("muonEGHLTL",&muonEGHLTL,"muonEGHLTL/O");
FATree->Branch("elecHLTL",&elecHLTL,"elecHLTL/O");
FATree->Branch("muonHLTL",&muonHLTL,"muonHLTL/O");
FATree->Branch("hadHLTL",&hadHLTL,"hadHLTL/O");
FATree->Branch("isLeptonicL",&isLeptonicL,"isLeptonicL/O");
FATree->Branch("isSemiLeptonicL",&isSemiLeptonicL,"isSemiLeptonicL/O");
FATree->Branch("isHadronicL",&isHadronicL,"isHadronicL/O");

//Branches for distinguishing between channels;
FATree->Branch("passedLepL",&passedLepL,"passedLepL/O");
FATree->Branch("passedSemiLepL",&passedSemiLepL,"passedSemiLepL/O");
FATree->Branch("passedHadL",&passedHadL,"passedHadL/O");



//Now trees for specific channels;

//Leptonic variables;
float lepZ1LeadPtL;
float lepZ1TrailingPtL;
float lepZ1LeadPhiL;
float lepZ1TrailingPhiL;
float lepZ1PairInvMassL;
float lepZ1LeadEtaL;
float lepZ1TrailingEtaL;
bool lepZ1IsElectronL;
bool lepZ1IsMuonL;
float lepZ1LeadIsoL;
float lepZ1TrailingIsoL;
float lepZ1LeadSIPL;
float lepZ1TrailingSIPL;

float lepZ2LeadPtL;
float lepZ2TrailingPtL;
float lepZ2LeadPhiL;
float lepZ2TrailingPhiL;
float lepZ2PairInvMassL;
float lepZ2LeadEtaL;
float lepZ2TrailingEtaL;
bool lepZ2IsElectronL;
bool lepZ2IsMuonL;
float lepZ2LeadIsoL;
float lepZ2TrailingIsoL;
float lepZ2LeadSIPL;
float lepZ2TrailingSIPL;

//Leptonic tree;
TTree *LepTree = new TTree("LepTree", "LepTree");

LepTree->Branch("lepZ1LeadPtL",&lepZ1LeadPtL,"lepZ1LeadPtL/F");
LepTree->Branch("lepZ1TrailingPtL",&lepZ1TrailingPtL,"lepZ1TrailingPtL/F");
LepTree->Branch("lepZ1LeadPhiL",&lepZ1LeadPhiL,"lepZ1LeadPhiL/F");
LepTree->Branch("lepZ1TrailingPhiL",&lepZ1TrailingPhiL,"lepZ1TrailingPhiL/F");
LepTree->Branch("lepZ1PairInvMassL",&lepZ1PairInvMassL,"lepZ1PairInvMassL/F");
LepTree->Branch("lepZ1LeadEtaL",&lepZ1LeadEtaL,"lepZ1LeadEtaL/F");
LepTree->Branch("lepZ1TrailingEtaL",&lepZ1TrailingEtaL,"lepZ1TrailingEtaL/F");
LepTree->Branch("lepZ1IsElectronL",&lepZ1IsElectronL,"lepZ1IsElectronL/O");
LepTree->Branch("lepZ1IsMuonL",&lepZ1IsMuonL,"lepZ1IsMuonL/O");
LepTree->Branch("lepZ1LeadIsoL",&lepZ1LeadIsoL,"lepZ1LeadIsoL/F");
LepTree->Branch("lepZ1TrailingIsoL",&lepZ1TrailingIsoL,"lepZ1TrailingIsoL/F");
LepTree->Branch("lepZ1LeadSIPL",&lepZ1LeadSIPL,"lepZ1LeadSIPL/F");
LepTree->Branch("lepZ1TrailingSIPL",&lepZ1TrailingSIPL,"lepZ1TrailingSIPL/F");

LepTree->Branch("lepZ2LeadPtL",&lepZ2LeadPtL,"lepZ2LeadPtL/F");
LepTree->Branch("lepZ2TrailingPtL",&lepZ2TrailingPtL,"lepZ2TrailingPtL/F");
LepTree->Branch("lepZ2LeadPhiL",&lepZ2LeadPhiL,"lepZ2LeadPhiL/F");
LepTree->Branch("lepZ2TrailingPhiL",&lepZ2TrailingPhiL,"lepZ2TrailingPhiL/F");
LepTree->Branch("lepZ2PairInvMassL",&lepZ2PairInvMassL,"lepZ2PairInvMassL/F");
LepTree->Branch("lepZ2LeadEtaL",&lepZ2LeadEtaL,"lepZ2LeadEtaL/F");
LepTree->Branch("lepZ2TrailingEtaL",&lepZ2TrailingEtaL,"lepZ2TrailingEtaL/F");
LepTree->Branch("lepZ2IsElectronL",&lepZ2IsElectronL,"lepZ2IsElectronL/O");
LepTree->Branch("lepZ2IsMuonL",&lepZ2IsMuonL,"lepZ2IsMuonL/O");
LepTree->Branch("lepZ2LeadIsoL",&lepZ2LeadIsoL,"lepZ2LeadIsoL/F");
LepTree->Branch("lepZ2TrailingIsoL",&lepZ2TrailingIsoL,"lepZ2TrailingIsoL/F");
LepTree->Branch("lepZ2LeadSIPL",&lepZ2LeadSIPL,"lepZ2LeadSIPL/F");
LepTree->Branch("lepZ2TrailingSIPL",&lepZ2TrailingSIPL,"lepZ2TrailingSIPL/F");


//SemiLeptonic variables;
float lepLeadPtL;
float lepTrailingPtL;
float lepLeadPhiL;
float lepTrailingPhiL;
float lepPairInvMassL;
float lepLeadEtaL;
float lepTrailingEtaL;
float lepLeadIsoL;
float lepTrailingIsoL;
float lepLeadSIPL;
float lepTrailingSIPL;
bool lepIsElectronL;
bool lepIsMuonL;


float FJPtL;
float FJPhiL;
float FJMassL;
float FJEtaL;

//SemiLeptonic tree;
TTree *SemiLepTree = new TTree("SemiLepTree", "SemiLepTree");

SemiLepTree->Branch("lepLeadPtL",&lepLeadPtL,"lepLeadPtL/F");
SemiLepTree->Branch("lepTrailingPtL",&lepTrailingPtL,"lepTrailingPtL/F");
SemiLepTree->Branch("lepLeadPhiL",&lepLeadPhiL,"lepLeadPhiL/F");
SemiLepTree->Branch("lepTrailingPhiL",&lepTrailingPhiL,"lepTrailingPhiL/F");
SemiLepTree->Branch("lepPairInvMassL",&lepPairInvMassL,"lepPairInvMassL/F");
SemiLepTree->Branch("lepLeadEtaL",&lepLeadEtaL,"lepLeadEtaL/F");
SemiLepTree->Branch("lepTrailingEtaL",&lepTrailingEtaL,"lepTrailingEtaL/F");
SemiLepTree->Branch("lepIsElectronL",&lepIsElectronL,"lepIsElectronL/O");
SemiLepTree->Branch("lepIsMuonL",&lepIsMuonL,"lepIsMuonL/O");
SemiLepTree->Branch("lepLeadIsoL",&lepLeadIsoL,"lepLeadIsoL/F");
SemiLepTree->Branch("lepTrailingIsoL",&lepTrailingIsoL,"lepTrailingIsoL/F");
SemiLepTree->Branch("lepLeadSIPL",&lepLeadSIPL,"lepLeadSIPL/F");
SemiLepTree->Branch("lepTrailingSIPL",&lepTrailingSIPL,"lepTrailingSIPL/F");
SemiLepTree->Branch("lepZ2IsElectronL",&lepZ2IsElectronL,"lepZ2IsElectronL/O");
SemiLepTree->Branch("lepIsMuonL",&lepIsMuonL,"lepIsMuonL/O");

SemiLepTree->Branch("FJPtL",&FJPtL,"FJPtL/F");
SemiLepTree->Branch("FJPhiL",&FJPhiL,"FJPhiL/F");
SemiLepTree->Branch("FJMassL",&FJMassL,"FJMassL/F");
SemiLepTree->Branch("FJEtaL",&FJEtaL,"FJEtaL/F");


//Hadronic variables;
float FJLeadPtL;
float FJTrailingPtL;
float FJLeadPhiL;
float FJTrailingPhiL;
float FJLeadMassL;
float FJTrailingMassL;
float FJPairInvMassL;
float FJLeadEtaL;
float FJTrailingEtaL;
float FJEtaSepL;

//Hadronic tree;
TTree *HadTree = new TTree("HadTree", "HadTree");

HadTree->Branch("FJLeadPtL",&FJLeadPtL,"FJLeadPtL/F");
HadTree->Branch("FJTrailingPtL",&FJTrailingPtL,"FJTrailingPtL/F");
HadTree->Branch("FJLeadPhiL",&FJLeadPhiL,"FJLeadPhiL/F");
HadTree->Branch("FJTrailingPhiL",&FJTrailingPhiL,"FJTrailingPhiL/F");
HadTree->Branch("FJLeadMassL",&FJLeadMassL,"FJLeadMassL/F");
HadTree->Branch("FJTrailingMassL",&FJTrailingMassL,"FJTrailingMassL/F");
HadTree->Branch("FJPairInvMassL",&FJPairInvMassL,"FJPairInvMassL/F");
HadTree->Branch("FJLeadEtaL",&FJLeadEtaL,"FJLeadEtaL/F");
HadTree->Branch("FJTrailingEtaL",&FJTrailingEtaL,"FJTrailingEtaL/F");
HadTree->Branch("FJEtaSepL",&FJEtaSepL,"FJEtaSepL/F");

*/

//VBF jet pair selection;
//Defining jet matching cuts;

float jetPTCut = 50.;
float jetEtaDifCut = 2.0;
float jetInvMassCut = 400.;

//Defining fat jet matching cuts;
float fatJetPTCut = 200.;
float hFatJetPTCut = 350.;
float hFatJetDeepTagCut = 0.2;
float hFatJetdRCut = 0.4;

//Lepton cuts;
float ePtCut = 7.;
float eEtaCut = 2.5;

float mPtCut = 5.;
float mEtaCut = 2.4;
//float invMassCutLow=60.;
//float invMassCutHigh=120.;
float invMassCutLow=80.;
float invMassCutHigh=100.;
float ptLeadCut=20.;
float ptTrailingCut=10.;

float fourLepInvMassCut = 100.;
float optLepInvMassCut = 12.;

float lepIsoCut = 0.35;

float SIPCut = 4.;