#include<TTree.h>

bool debug = false;
bool debugHadronic = false;
bool debugGenPart = false;
bool endAfter = false;
int NToStart = 17;
int NToEnd = 18;

bool useTighterCut = false;

bool FoMOnHiggsCut = true;

bool testRun = false;
bool SDC2V3MC = false;
bool MGC2VEtaDifCut = false;
bool MGOSix = false;
bool MGOSixEtaDifCut = false;
bool MGOHBox = false;
bool MGOHBoxEtaDifCut = false;
bool MGOHDD = false;
bool MGOHDDEtaDifCut = false;
bool MGOHW = false;
bool MGSM = false;
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

bool TTJetsBackground = false;
bool TTToHadronicBackground = false;
bool TTTo2L2NuBackground = false;
bool TTToSemiLeptonicBackground = false;
bool ST_s_ChannelBackground = false;
bool ST_t_ChannelAntiTopBackground = false;
bool ST_t_ChannelTopBackground = false;
bool ZZTo2Q2NuBackground = false;
bool WWTo2L2NuBackground = false;
bool WZTo3LNuBackground = false;

bool LaraTest = false;

bool isBackground = false;

bool scratchDown = false;

//VBF jet pair selection;
//Defining jet matching cuts;
/*
//float hFatJetdRCut = 0.4;
float hFatJetdRRangeTop = 2.;
float hFatJetdRRangeBottom = 0.;
float hFatJetdRCutStep = (hFatJetdRRangeTop - hFatJetdRRangeBottom) / cutAmnt;
*/
UInt_t cutAmnt = 200;

UInt_t lumi = 137600;

float VBFJetdRCut = 0.4;
float VBFJetdRRangeTop = 4.;
float VBFJetdRRangeBottom = 0.;
float VBFJetdRCutStep = (VBFJetdRRangeTop - VBFJetdRRangeBottom) / cutAmnt;




float jetPTCut = 50.;
float jetPTRangeTop = 200.;
float jetPTRangeBottom = 0.;
float jetPTCutStep = (jetPTRangeTop - jetPTRangeBottom) / cutAmnt;

float jetEtaDifCut = 2.0;
float jetEtaRangeTop = 8.;
float jetEtaRangeBottom = 0.;
float jetEtaCutStep = (jetEtaRangeTop - jetEtaRangeBottom) / cutAmnt;

float jetInvMassCut = 400.;
float jetInvMassRangeTop = 4000.;
float jetInvMassRangeBottom = 0.;
float jetInvMassCutStep = (jetInvMassRangeTop - jetInvMassRangeBottom) / cutAmnt;

//Defining fat jet matching cuts;
float fatJetPTCut = 200.;
float fatJetPTRangeTop = 4000.;
float fatJetPTRangeBottom = 0.;
float fatJetPTCutStep = (fatJetPTRangeTop - fatJetPTRangeBottom) / cutAmnt;
//float hFatJetPTCut = 350.;


//Higgs cuts
float hFatJetPTCut = 300.;
float hFatJetPTCutRangeTop = 2000;
float hFatJetPTCutRangeBottom = 0.;
float hFatJetPTCutStep = (hFatJetPTCutRangeTop - hFatJetPTCutRangeBottom) / cutAmnt;


float hFatJetDeepTagCut = 0.9;
float hFatJetDeepTagRangeTop = 1.;
float hFatJetDeepTagRangeBottom = 0.;
float hFatJetDeepTagCutStep = (hFatJetDeepTagRangeTop - hFatJetDeepTagRangeBottom) / cutAmnt;




std::vector<UInt_t> cutPassAr;
std::vector<UInt_t> cutLepPassAr;
std::vector<UInt_t> cutSemiLepPassAr;
std::vector<UInt_t> cutHadPassAr;
std::vector<UInt_t> cutLepOrSemiLepPassAr;

std::vector<UInt_t> cutPassWeightedAr;
std::vector<UInt_t> cutLepPassWeightedAr;
std::vector<UInt_t> cutSemiLepPassWeightedAr;
std::vector<UInt_t> cutHadPassWeightedAr;
std::vector<UInt_t> cutLepOrSemiLepPassWeightedAr;
std::vector<float> cutRangeAr;



//Lepton cuts;
float ePtCut = 7.;
float ePtRangeTop = 100.;
float ePtRangeBottom = 0.;
float ePtCutStep = (ePtRangeTop - ePtRangeBottom) / cutAmnt;
float eEtaCut = 2.5;
float eEtaRangeTop = 3.;
float eEtaRangeBottom = 0.;
float eEtaCutStep = (eEtaRangeTop - eEtaRangeBottom) / cutAmnt;


float mPtCut = 5.;
float mPtRangeTop = 100.;
float mPtRangeBottom = 0.;
float mPtCutStep = (mPtRangeTop - mPtRangeBottom) / cutAmnt;
float mEtaCut = 2.4;
float mEtaRangeTop = 3.;
float mEtaRangeBottom = 0.;
float mEtaCutStep = (mEtaRangeTop - mEtaRangeBottom) / cutAmnt;
//float invMassCutLow=60.;
//float invMassCutHigh=120.;
float invMassCutLow=80.;
float invMassCutLowRangeTop = 120.;
float invMassCutLowRangeBottom = 0.;
float invMassCutLowCutStep = (invMassCutLowRangeTop - invMassCutLowRangeBottom) / cutAmnt;

float invMassCutHigh=100.;
float invMassCutHighRangeTop = 180.;
float invMassCutHighRangeBottom = 60.;
float invMassCutHighCutStep = (invMassCutHighRangeTop - invMassCutHighRangeBottom) / cutAmnt;

float ptLeadCut=20.;
float ptLeadRangeTop = 200.;
float ptLeadRangeBottom = 0.;
float ptLeadCutStep = (ptLeadRangeTop - ptLeadRangeBottom) / cutAmnt;

float ptTrailingCut=10.;
float ptTrailingRangeTop = 100.;
float ptTrailingRangeBottom = 0.;
float ptTrailingCutStep = (ptTrailingRangeTop - ptTrailingRangeBottom) / cutAmnt;

float fourLepInvMassCut = 100.;
float fourLepInvMassRangeTop = 1400.;
float fourLepInvMassRangeBottom = 0.;
float fourLepInvMassCutStep = (fourLepInvMassRangeTop - fourLepInvMassRangeBottom) / cutAmnt;

float optLepInvMassCut = 12.;
float optLepInvMassRangeTop = 200.;
float optLepInvMassRangeBottom = 0.;
float optLepInvMassCutStep = (optLepInvMassRangeTop - optLepInvMassRangeBottom) / cutAmnt;

float lepIsoCut = 0.35;
float lepIsoRangeTop = 4.;
float lepIsoRangeBottom = 0.;
float lepIsoCutStep = (lepIsoRangeTop - lepIsoRangeBottom) / cutAmnt;

float SIPCut = 4.;
float SIPRangeTop = 6.;
float SIPRangeBottom = 0.;
float SIPCutStep = (SIPRangeTop - SIPRangeBottom) / cutAmnt;

//Hadronic cuts
//0.2 is a placeholder value
float fatJetHTagCut = 0.2;
float fatJetZTagCut = 0.8;
float fatJetZTagRangeTop = 1.;
float fatJetZTagRangeBottom = 0.;
float fatJetZTagCutStep = (fatJetZTagRangeTop - fatJetZTagRangeBottom) / cutAmnt;
//Need to test if this cut is necessary. Not sure.
float fatJetZPairInvMassCut = 300;
//EtaDifCut probably not necessary
//float fatJetEtaDifCut = 5.0;
float fatJetZPlusHPTCut = 1050;
