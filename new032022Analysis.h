#include<TTree.h>

bool debug = false;
bool debugHadronic = false;
bool debugGenPart = false;
bool endAfter = false;
int NToStart = 0;
int NToEnd = 2500;

bool useTighterCut = false;

bool testRun = true;
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

bool isBackground = false;



//VBF jet pair selection;
//Defining jet matching cuts;

float jetPTCut = 50.;
float jetEtaDifCut = 2.0;
float jetInvMassCut = 400.;

//Defining fat jet matching cuts;
float fatJetPTCut = 200.;
//float hFatJetPTCut = 350.;
float hFatJetPTCut = 300.;
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

//Hadronic cuts
//0.2 is a placeholder value
float fatJetHTagCut = 0.2;
float fatJetZTagCut = 0.2;
//Need to test if this cut is necessary. Not sure.
float fatJetZPairInvMassCut = 300;
//EtaDifCut probably not necessary
//float fatJetEtaDifCut = 5.0;
float fatJetZPlusHPTCut = 1050
