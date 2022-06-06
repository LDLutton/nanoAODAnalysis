#include<TTree.h>

bool debug = false;
bool endAfter = false;
int NToStart = 0;
int NToEnd = 20;

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

bool weakCuts = true;

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

UInt_t Run2Lumi = 137600;

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

float hFatJetParticleNetCut = 0.9;
float hFatJetParticleNetRangeTop = 1.;
float hFatJetParticleNetRangeBottom = 0.;
float hFatJetParticleNetCutStep = (hFatJetParticleNetRangeTop - hFatJetParticleNetRangeBottom) / cutAmnt;





std::vector<UInt_t> cutPassAr;
std::vector<UInt_t> cutLepPassAr;
std::vector<UInt_t> cutSemiLepPassAr;
std::vector<UInt_t> cutHadPassAr;
std::vector<UInt_t> cutLepOrSemiLepPassAr;

std::vector<Double_t> cutPassWeightedAr;
std::vector<Double_t> cutLepPassWeightedAr;
std::vector<Double_t> cutSemiLepPassWeightedAr;
std::vector<Double_t> cutHadPassWeightedAr;
std::vector<Double_t> cutLepOrSemiLepPassWeightedAr;
std::vector<float> cutRangeAr;

//New 062022 Lepton ID cuts
float lDxyCut = 0.05;
float lDxyRangeTop = 0.1;
float lDxyRangeBottom = 0.;
float lDxyCutStep = (lDxyRangeTop - lDxyRangeBottom) / cutAmnt;
float lDzCut = 0.1;
float lDzRangeTop = 0.2;
float lDzRangeBottom = 0.;
float lDzCutStep = (lDzRangeTop - lDzRangeBottom) / cutAmnt;
float lMiniPFRelIsoCut = 0.4;
float lMiniPFRelIsoRangeTop = 1.;
float lMiniPFRelIsoRangeBottom = 0.;
float lMiniPFRelIsoCutStep = (lMiniPFRelIsoRangeTop - lMiniPFRelIsoRangeBottom) / cutAmnt;
float eSieieBarrelCut = 0.011;
float eSieieBarrelRangeTop = 0.5;
float eSieieBarrelRangeBottom = 0.;
float eSieieBarrelCutStep = (eSieieBarrelRangeTop - eSieieBarrelRangeBottom) / cutAmnt;

float eSieieEndcapCut = 0.030;
float eSieieEndcapRangeTop = 0.5;
float eSieieEndcapRangeBottom = 0.011;
float eSieieEndcapCutStep = (eSieieEndcapRangeTop - eSieieEndcapRangeBottom) / cutAmnt;


float eHoeCut = 0.1;
float eHoeRangeTop = 2.;
float eHoeRangeBottom = 0.;
float eHoeCutStep = (eHoeRangeTop - eHoeRangeBottom) / cutAmnt;
float eInvMinusPInvCut = -0.04;
float eInvMinusPInvRangeTop = 0.05;
float eInvMinusPInvRangeBottom = -0.15;
float eInvMinusPInvCutStep = (eInvMinusPInvRangeTop - eInvMinusPInvRangeBottom) / cutAmnt;
float ePromptMVACut = 0.8;
float ePromptMVARangeTop = 1.;
float ePromptMVARangeBottom = 0.;
float ePromptMVACutStep = (ePromptMVARangeTop - ePromptMVARangeBottom) / cutAmnt;

UInt_t eLostHitsCut = 0;

float lepJetDeepTagLooseCut = 0.0521;
float lepJetDeepTagLooseRangeTop = 0.3033;
float lepJetDeepTagLooseRangeBottom = 0.;
float lepJetDeepTagLooseCutStep = (lepJetDeepTagLooseRangeTop - lepJetDeepTagLooseRangeBottom) / cutAmnt;
float lepJetDeepTagMediumCut = 0.3033;
float lepJetDeepTagMediumRangeTop = 1.;
float lepJetDeepTagMediumRangeBottom = 0.0521;
float lepJetDeepTagMediumCutStep = (lepJetDeepTagMediumRangeTop - lepJetDeepTagMediumRangeBottom) / cutAmnt;

float mPromptMVACut = 0.85;
float mPromptMVARangeTop = 1.;
float mPromptMVARangeBottom = 0.;
float mPromptMVACutStep = (mPromptMVARangeTop - mPromptMVARangeBottom) / cutAmnt;



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

float fatJetZParticleNetCut = 0.8;
float fatJetZParticleNetRangeTop = 1.;
float fatJetZParticleNetRangeBottom = 0.;
float fatJetZParticleNetCutStep = (fatJetZParticleNetRangeTop - fatJetZParticleNetRangeBottom) / cutAmnt;

//Need to test if this cut is necessary. Not sure.
float fatJetZPairInvMassCut = 300;
//EtaDifCut probably not necessary
//float fatJetEtaDifCut = 5.0;
float fatJetZPlusHPTCut = 1050;
/*
float fatJetZPlusHInvMassCut = 0;
float fatJetZPlusHInvMassRangeTop = 4000.;
float fatJetZPlusHInvMassRangeBottom = 0.;
float fatJetZPlusHInvMassCutStep = (fatJetZPlusHInvMassRangeTop - fatJetZPlusHInvMassRangeBottom) / cutAmnt;

float fatJetZPairPlusHInvMassCut = 0;
float fatJetZPairPlusHInvMassRangeTop = 4000.;
float fatJetZPairPlusHInvMassRangeBottom = 0.;
float fatJetZPairPlusHInvMassCutStep = (fatJetZPlusHInvMassRangeTop - fatJetZPlusHInvMassRangeBottom) / cutAmnt;
*/
float ZPairPlusHInvMassCut = 500.;
float ZPairPlusHInvMassRangeTop = 4000.;
float ZPairPlusHInvMassRangeBottom = 0.;
float ZPairPlusHInvMassCutStep = (ZPairPlusHInvMassRangeTop - ZPairPlusHInvMassRangeBottom) / cutAmnt;

float ZPairPlusHPtCut = 500.;
float ZPairPlusHPtRangeTop = 4000.;
float ZPairPlusHPtRangeBottom = 0.;
float ZPairPlusHPtCutStep = (ZPairPlusHPtRangeTop - ZPairPlusHPtRangeBottom) / cutAmnt;



float dRCut = 0.4;
float dRCutRangeTop = 4.;
float dRCutRangeBottom = 0.;
float dRCutCutStep = (dRCutRangeTop - dRCutRangeBottom) / cutAmnt;

//Ultra Weak cuts V8 06022022 Added new lepton ID, moving back cuts, and added particle net instead of deeptag

float dRWeakCut = 0.001;

float jetPTWeakCut = 5.;

float jetEtaDifWeakCut = .5;

float jetInvMassWeakCut = 100.;

//Higgs FJ cuts

float hFatJetPTWeakCut = 100.;


float hFatJetParticleNetWeakCut = 0.005;



//Lep cuts

float ePtWeakCut = 5.;

float eEtaWeakCut = 3.;

float mPtWeakCut = 3.;

float mEtaWeakCut = 3.;

float invMassWeakCutLow=20.;

float invMassWeakCutHigh=160.;

float ptLeadWeakCut=5.;

float ptTrailingWeakCut=3.;

float fourLepInvMassWeakCut = 30.;

float optLepInvMassWeakCut = 3.;

float lepIsoWeakCut = 10.;

float SIPWeakCut = 8.;

//Semi-Lep cuts
//fatJetPTWeakCut = 200.;

float fatJetZParticleNetWeakCut = 0.05;

float ZPairPlusHInvMassWeakCut = 500;
float ZPairPlusHPtWeakCut = 500;


float lDxyWeakCut = 0.3;
float lDzWeakCut = 0.5;
float lMiniPFRelIsoWeakCut = 10.;
float eSieieBarrelWeakCut = 0.05;
float eSieieEndcapWeakCut = 0.070;

float eHoeWeakCut = 2.;
float eInvMinusPInvWeakCut = -0.15;
float ePromptMVAWeakCut = -0.8;
float lepJetDeepTagLooseWeakCut = 0.0221;
float lepJetDeepTagMediumWeakCut = 0.0533;
float mPromptMVAWeakCut = 0.2;

//unused
float fatJetZTagWeakCut = 0.1;
float hFatJetDeepTagWeakCut = 0.1;

/*
//Weak cuts V8 06022022 Added new lepton ID, moving back cuts, and added particle net instead of deeptag

float dRWeakCut = 0.1;

float jetPTWeakCut = 15.;

float jetEtaDifWeakCut = 1.0;

float jetInvMassWeakCut = 200.;

//Higgs FJ cuts

float hFatJetPTWeakCut = 200.;

float hFatJetDeepTagWeakCut = 0.1;

float hFatJetParticleNetWeakCut = 0.1;



//Lep cuts

float ePtWeakCut = 7.;

float eEtaWeakCut = 2.5;

float mPtWeakCut = 5.;

float mEtaWeakCut = 2.4;

float invMassWeakCutLow=40.;

float invMassWeakCutHigh=140.;

float ptLeadWeakCut=10.;

float ptTrailingWeakCut=5.;

float fourLepInvMassWeakCut = 50.;

float optLepInvMassWeakCut = 6.;

float lepIsoWeakCut = 1.35;

float SIPWeakCut = 5.;

//Semi-Lep cuts
//fatJetPTWeakCut = 200.;

float fatJetZTagWeakCut = 0.1;
float fatJetZParticleNetWeakCut = 0.1;

float ZPairPlusHInvMassWeakCut = 1000;
float ZPairPlusHPtWeakCut = 1000;


float lDxyWeakCut = 0.05;
float lDzWeakCut = 0.1;
float lMiniPFRelIsoWeakCut = 0.4;
float eSieieBarrelWeakCut = 0.011;
float eSieieEndcapWeakCut = 0.030;

float eHoeWeakCut = 0.1;
float eInvMinusPInvWeakCut = -0.04;
float ePromptMVAWeakCut = 0.8;
float lepJetDeepTagLooseWeakCut = 0.0521;
float lepJetDeepTagMediumWeakCut = 0.3033;
float mPromptMVAWeakCut = 0.85;



*/

/*
//Weak cuts V7 05252022 Moving up invmass and ZPair+H cuts

float dRWeakCut = 0.1;

float jetPTWeakCut = 15.;

float jetEtaDifWeakCut = 1.0;

float jetInvMassWeakCut = 200.;

//Higgs FJ cuts

float hFatJetPTWeakCut = 200.;

float hFatJetDeepTagWeakCut = 0.1;



//Lep cuts

float ePtWeakCut = 7.;

float eEtaWeakCut = 2.5;

float mPtWeakCut = 5.;

float mEtaWeakCut = 2.4;

float invMassWeakCutLow=80.;

float invMassWeakCutHigh=100.;

float ptLeadWeakCut=10.;

float ptTrailingWeakCut=5.;

float fourLepInvMassWeakCut = 50.;

float optLepInvMassWeakCut = 6.;

float lepIsoWeakCut = 1.35;

float SIPWeakCut = 5.;

//Semi-Lep cuts
//fatJetPTWeakCut = 200.;

float fatJetZTagWeakCut = 0.1;

float ZPairPlusHInvMassWeakCut = 1000;
float ZPairPlusHPtWeakCut = 1000;
*/
/*
//Weak cuts V6 05252022 Moving back down cuts to account for new cuts 
//Setting default ZPairPlusH cuts to 500GeV, which is very low

float dRWeakCut = 0.1;

float jetPTWeakCut = 15.;

float jetEtaDifWeakCut = 1.0;

float jetInvMassWeakCut = 200.;

//Higgs FJ cuts

float hFatJetPTWeakCut = 200.;

float hFatJetDeepTagWeakCut = 0.1;



//Lep cuts

float ePtWeakCut = 7.;

float eEtaWeakCut = 2.5;

float mPtWeakCut = 5.;

float mEtaWeakCut = 2.4;

float invMassWeakCutLow=40.;

float invMassWeakCutHigh=140.;

float ptLeadWeakCut=10.;

float ptTrailingWeakCut=5.;

float fourLepInvMassWeakCut = 50.;

float optLepInvMassWeakCut = 6.;

float lepIsoWeakCut = 1.35;

float SIPWeakCut = 5.;

//Semi-Lep cuts
//fatJetPTWeakCut = 200.;

float fatJetZTagWeakCut = 0.1;

float ZPairPlusHInvMassWeakCut = 500;
float ZPairPlusHPtWeakCut = 500;

*/

/*
//Weak cuts V5 05252022 Changing things for new052022Analysis and adding in new cuts
float VBFJetdRWeakCut = 0.4;

float jetPTWeakCut = 30.;

float jetEtaDifWeakCut = 2.0;

float jetInvMassWeakCut = 400.;

//Higgs FJ cuts

float hFatJetPTWeakCut = 300.;

float hFatJetDeepTagWeakCut = 0.1;



//Lep cuts

float ePtWeakCut = 7.;

float eEtaWeakCut = 2.5;

float mPtWeakCut = 5.;

float mEtaWeakCut = 2.4;

float invMassWeakCutLow=80.;

float invMassWeakCutHigh=100.;

float ptLeadWeakCut=20.;

float ptTrailingWeakCut=10.;

float fourLepInvMassWeakCut = 100.;

float optLepInvMassWeakCut = 12.;

float lepIsoWeakCut = 0.35;

float SIPWeakCut = 4.;

//Semi-Lep cuts
//fatJetPTWeakCut = 200.;

float fatJetZTagWeakCut = 0.5;

float fatJetZPairPlusHInvMassWeakCut = 0;
*/

/*
//Weak cuts V4 05172022 Moving up certain cuts
float VBFJetdRWeakCut = 0.4;

float jetPTWeakCut = 30.;

float jetEtaDifWeakCut = 2.0;

float jetInvMassWeakCut = 400.;

//Higgs FJ cuts

float hFatJetPTWeakCut = 300.;

float hFatJetDeepTagWeakCut = 0.1;



//Lep cuts

float ePtWeakCut = 7.;

float eEtaWeakCut = 2.5;

float mPtWeakCut = 5.;

float mEtaWeakCut = 2.4;

float invMassWeakCutLow=80.;

float invMassWeakCutHigh=100.;

float ptLeadWeakCut=20.;

float ptTrailingWeakCut=10.;

float fourLepInvMassWeakCut = 100.;

float optLepInvMassWeakCut = 12.;

float lepIsoWeakCut = 0.35;

float SIPWeakCut = 4.;

//Semi-Lep cuts
//fatJetPTWeakCut = 200.;

float fatJetZTagWeakCut = 0.5;

*/


/*

//Weak cuts V3 05132022 Moving up certain cuts
float VBFJetdRWeakCut = 0.4;

float jetPTWeakCut = 20.;

float jetEtaDifWeakCut = 2.0;

float jetInvMassWeakCut = 400.;

//Higgs FJ cuts

float hFatJetPTWeakCut = 200.;

float hFatJetDeepTagWeakCut = 0.1;



//Lep cuts

float ePtWeakCut = 7.;

float eEtaWeakCut = 2.5;

float mPtWeakCut = 5.;

float mEtaWeakCut = 2.4;

float invMassWeakCutLow=80.;

float invMassWeakCutHigh=100.;

float ptLeadWeakCut=20.;

float ptTrailingWeakCut=10.;

float fourLepInvMassWeakCut = 100.;

float optLepInvMassWeakCut = 12.;

float lepIsoWeakCut = 0.35;

float SIPWeakCut = 4.;

//Semi-Lep cuts
//fatJetPTWeakCut = 200.;

float fatJetZTagWeakCut = 0.1;

*/

/*
//Weak cuts round two 05122022 Moving up certain cuts
float VBFJetdRWeakCut = 0.4;

float jetPTWeakCut = 20.;

float jetEtaDifWeakCut = 2.0;

float jetInvMassWeakCut = 200.;

//Higgs FJ cuts

float hFatJetPTWeakCut = 200.;

float hFatJetDeepTagWeakCut = 0.1;



//Lep cuts

float ePtWeakCut = 7.;

float eEtaWeakCut = 2.5;

float mPtWeakCut = 5.;

float mEtaWeakCut = 2.4;

float invMassWeakCutLow=80.;

float invMassWeakCutHigh=100.;

float ptLeadWeakCut=20.;

float ptTrailingWeakCut=10.;

float fourLepInvMassWeakCut = 100.;

float optLepInvMassWeakCut = 12.;

float lepIsoWeakCut = 1.5;

float SIPWeakCut = 4.;

//Semi-Lep cuts
//fatJetPTWeakCut = 200.;

float fatJetZTagWeakCut = 0.1;
*/




/*
//Weak cuts
float VBFJetdRWeakCut = 0.1;

float jetPTWeakCut = 20.;

float jetEtaDifWeakCut = 1.0;

float jetInvMassWeakCut = 200.;

//Higgs FJ cuts

float hFatJetPTWeakCut = 200.;

float hFatJetDeepTagWeakCut = 0.1;



//Lep cuts

float ePtWeakCut = 1.;

float eEtaWeakCut = 3.0;

float mPtWeakCut = 1.;

float mEtaWeakCut = 3.0;

float invMassWeakCutLow=40.;

float invMassWeakCutHigh=140.;

float ptLeadWeakCut=10.;

float ptTrailingWeakCut=5.;

float fourLepInvMassWeakCut = 50.;

float optLepInvMassWeakCut = 6.;

float lepIsoWeakCut = 1.5;

float SIPWeakCut = 5.5;

//Semi-Lep cuts
//fatJetPTWeakCut = 200.;

float fatJetZTagWeakCut = 0.1;
*/



/*
//Weakest cuts
float VBFJetdRWeakCut = 0.1;

float jetPTWeakCut = 20.;

float jetEtaDifWeakCut = 1.0;

float jetInvMassWeakCut = 200.;

//Higgs FJ cuts

float hFatJetPTWeakCut = 200.;

float hFatJetDeepTagWeakCut = 0.1;



//Lep cuts

float ePtWeakCut = 1.;

float eEtaWeakCut = 3.1;

float mPtWeakCut = 1.;

float mEtaWeakCut = 3.1;

float invMassWeakCutLow=0.;

float invMassWeakCutHigh=999.;

float ptLeadWeakCut=0.;

float ptTrailingWeakCut=0.;

float fourLepInvMassWeakCut = 0.;

float optLepInvMassWeakCut = 0.;

float lepIsoWeakCut = 999999.;

float SIPWeakCut = 0.;

//Semi-Lep cuts
//fatJetPTWeakCut = 200.;

float fatJetZTagWeakCut = 0.1;

//Not implemented

//fatJetZPairInvMassWeakCut = 300;

//fatJetZPlusHPTWeakCut = 1050;

*/


/*
if (weakCuts){
    //VBF Cuts
    VBFJetdRCut = 0.1;

    jetPTCut = 20.;

    jetEtaDifCut = 1.0;

    jetInvMassCut = 200.;

    //Higgs FJ cuts

    hFatJetPTCut = 200.;

    hFatJetDeepTagCut = 0.1;

    

    //Lep cuts

    //ePtCut = 7.;

    //eEtaCut = 2.5;

    //mPtCut = 5.;

    //mEtaCut = 2.4;

    invMassCutLow=60.;

    invMassCutHigh=120.;

    //ptLeadCut=20.;

    //ptTrailingCut=10.;

    fourLepInvMassCut = 100.;

    optLepInvMassCut = 12.;

    lepIsoCut = 1.0;

    SIPCut = 5.;

    //Semi-Lep cuts
    //fatJetPTCut = 200.;

    fatJetZTagCut = 0.1;

    //Not implemented

    //fatJetZPairInvMassCut = 300;

    //fatJetZPlusHPTCut = 1050;
}
*/
