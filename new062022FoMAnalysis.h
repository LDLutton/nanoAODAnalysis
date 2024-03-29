#include<TTree.h>

bool debug = false;
bool endAfter = false;
int NToStart = 0;
int NToEnd = 20;

bool useSingleLepHLT = false;

bool useTighterCut = false;

bool FoMOnHiggsCut = true;

bool SDC2V2MCZZHReweight = false;
bool SDC2V2MCZZH17Reweight = false;
bool SDC2V2MCZZH16Reweight = false;
bool SDC2V2MCZZH16APVReweight = false;

bool SDC2V2MCWZHReweight = false;
bool SDC2V2MCWZH17Reweight = false;
bool SDC2V2MCWZH16Reweight = false;
bool SDC2V2MCWZH16APVReweight = false;

bool SDC2V2MCZZHReweightTrimmed = false;
bool SDC2V2MCZZH17ReweightTrimmed = false;
bool SDC2V2MCZZH16ReweightTrimmed = false;
bool SDC2V2MCZZH16APVReweightTrimmed = false;

bool SDC2V2MCWZHReweightTrimmed = false;
bool SDC2V2MCWZH17ReweightTrimmed = false;
bool SDC2V2MCWZH16ReweightTrimmed = false;
bool SDC2V2MCWZH16APVReweightTrimmed = false;

bool testRun = false;
bool SDC2V3MC = false;
bool SDC2V3MCWZH = false;
bool SDC2Vm2p5MCWZH = false;
bool SDC2Vm3MCWZH = false;
bool SDC2Vm1MCWZH = false;
bool SDC2V0MCWZH = false;
bool SDC2V1MCWZH = false;
bool SDC2V4MCWZH = false;
bool SDC2V5MCWZH = false;
bool SDC2Vm2p5MC = false;
bool SDC2Vm2MC = false;
bool SDC2Vm1MC = false;
bool SDC2V0MC = false;
bool SDC2V1MC = false;
bool SDC2V4MC = false;
bool SDC2V4p5MC = false;


bool SDC2Vm2p5MCV2 = false;
bool SDC2Vm2MCV2 = false;
bool SDC2Vm1MCV2 = false;
bool SDC2V0MCV2 = false;
bool SDC2V1MCV2 = false;
bool SDC2V3MCV2 = false;
bool SDC2V4MCV2 = false;
bool SDC2V4p5MCV2 = false;

bool SDC2Vm2p5MCWZHV2 = false;
bool SDC2Vm3MCWZHV2 = false;
bool SDC2Vm1MCWZHV2 = false;
bool SDC2V0MCWZHV2 = false;
bool SDC2V1MCWZHV2 = false;
bool SDC2V3MCWZHV2 = false;
bool SDC2V4MCWZHV2 = false;
bool SDC2V5MCWZHV2 = false;

bool ZZTo2Q2NuBackground = false;
bool WWTo2L2NuBackground = false;
bool WZTo3LNuBackground = false;

bool TTToHadronicBackground = false;
bool TTTo2L2NuBackground = false;
bool TTToSemiLeptonicBackground = false;


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

bool ST_s_ChannelBackground = false;
bool ST_t_ChannelAntiTopBackground = false;
bool ST_t_ChannelTopBackground = false;


bool ZZBackground = false;
bool WWBackground = false;
bool WZBackground = false;

bool TTbb_TTToHadronicBackground = false;
bool TTbb_TTTo2L2NuBackground = false;
bool TTbb_TTToSemiLeptonicBackground = false;


bool ttHToBBTrimmedBackground = false;
bool ttZJetsTrimmedBackground = false;
bool DYTrimmedBackground = false;
bool QCDPT170to300TrimmedBackground = false;
bool QCDPT300to470TrimmedBackground = false;
bool QCDPT470to600TrimmedBackground = false;
bool QCDPT600to800TrimmedBackground = false;
bool QCDPT800to1000TrimmedBackground = false;
bool QCDPT1000to1400TrimmedBackground = false;
bool QCDPT1400to1800TrimmedBackground = false;
bool QCDPT1800to2400TrimmedBackground = false;
bool QCDPT2400to3200TrimmedBackground = false;
bool QCDPT3200toInfTrimmedBackground = false;


bool QCDHT50to100TrimmedBackground = false;
bool QCDHT100to200TrimmedBackground = false;
bool QCDHT200to300TrimmedBackground = false;
bool QCDHT300to500TrimmedBackground = false;
bool QCDHT500to700TrimmedBackground = false;
bool QCDHT700to1000TrimmedBackground = false;
bool QCDHT1000to1500TrimmedBackground = false;
bool QCDHT1500to2000TrimmedBackground = false;
bool QCDHT2000toInfTrimmedBackground = false;

bool TTToHadronicTrimmedBackground = false;
bool TTTo2L2NuTrimmedBackground = false;
bool TTToSemiLeptonicTrimmedBackground = false;

bool TTJetsTrimmedBackground = false;

bool ST_s_ChannelTrimmedBackground = false;
bool ST_t_ChannelAntiTopTrimmedBackground = false;
bool ST_t_ChannelTopTrimmedBackground = false;


bool ZZTrimmedBackground = false;
bool WWTrimmedBackground = false;
bool WZTrimmedBackground = false;

bool TTbb_TTToHadronicTrimmedBackground = false;
bool TTbb_TTTo2L2NuTrimmedBackground = false;
bool TTbb_TTToSemiLeptonicTrimmedBackground = false;

bool ttWJetsTrimmedBackground = false;
bool DYM10To50TrimmedBackground = false;
bool ST_tW_antitopTrimmedBackground = false;
bool ST_tW_topTrimmedBackground = false;
bool EWKWMinus2Jets_WToLNuTrimmedBackground = false;
bool EWKWMinus2Jets_WToQQTrimmedBackground = false;
bool EWKWPlus2Jets_WToLNuTrimmedBackground = false;
bool EWKWPlus2Jets_WToQQTrimmedBackground = false;
bool VHToNonbbTrimmedBackground = false;
bool WminusH_HToBB_WToLNuTrimmedBackground = false;
bool WminusH_HToBB_WToQQTrimmedBackground = false;
bool WplusH_HToBB_WToLNuTrimmedBackground = false;
bool WplusH_HToBB_WToQQTrimmedBackground = false;
bool WJetsToLNuTrimmedBackground = false;
bool WWWTrimmedBackground = false;
bool WWZTrimmedBackground = false;
bool WZZTrimmedBackground = false;
bool ZH_HToBB_ZToBBTrimmedBackground = false;
bool ZH_HToBB_ZToNuNuTrimmedBackground = false;
bool ZH_HToBB_ZToLLTrimmedBackground = false;
bool ZH_HToBB_ZToQQTrimmedBackground = false;
bool ggZH_HToBB_ZToBBTrimmedBackground = false;
bool ggZH_HToBB_ZToNuNuTrimmedBackground = false;
bool ggZH_HToBB_ZToLLTrimmedBackground = false;
bool ggZH_HToBB_ZToQQTrimmedBackground = false;
bool EWKZ2Jets_ZToLLTrimmedBackground = false;
bool EWKZ2Jets_ZToNuNuTrimmedBackground = false;
bool EWKZ2Jets_ZToQQTrimmedBackground = false;
bool ZZZTrimmedBackground = false;



bool BDTSignalGenChannelMatched = false;

bool weakCuts = true;

bool BDTCuts = true;


///////DATA BELOW HERE///////
bool BTagMuData = false;
bool CharmoniumData = false;
bool DisplacedJetData = false;
bool DoubleMuonData = false;
bool DoubleMuonLowMassData = false;
bool EGammaData = false;
bool JetHTData = false;
bool METData = false;
bool MuOniaData = false;
bool MuonEGData = false;
bool SingleMuonData = false;
bool TauData = false;

//2017

bool BTagCSV17Data = false;
bool BTagMu17Data = false;
bool Charmonium17Data = false;
bool DisplacedJet17Data = false;
bool DoubleEG17Data = false;
bool DoubleMuon17Data = false;
bool DoubleMuonLowMass17Data = false;
bool FSQJet117Data = false;
bool FSQJet217Data = false;
bool HTMHT17Data = false;
bool HeavyFlavor17Data = false;
bool HighEGJet17Data = false;
bool HighPtLowerPhotons17Data = false;
bool HighPtPhoton30AndZ17Data = false;
bool JetHT17Data = false;
bool LowEGJet17Data = false;
bool MET17Data = false;
bool MuOnia17Data = false;
bool MuonEG17Data = false;
bool SingleElectron17Data = false;
bool SingleMuon17Data = false;
bool SinglePhoton17Data = false;
bool Tau17Data = false;

//2016

bool BTagCSV16Data = false;
bool BTagMu16Data = false;
bool Charmonium16Data = false;
bool DisplacedJet16Data = false;
bool DoubleEG16Data = false;
bool DoubleMuon16Data = false;
bool DoubleMuonLowMass16Data = false;
bool HTMHT16Data = false;
bool JetHT16Data = false;
bool MET16Data = false;
bool MuOnia16Data = false;
bool MuonEG16Data = false;
bool SingleElectron16Data = false;
bool SingleMuon16Data = false;
bool SinglePhoton16Data = false;
bool Tau16Data = false;


bool LaraTest = false;

bool isBackground = false;

bool scratchDown = false;
bool localTest = true;

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

float bTagCut = 0.7100;
float bTagRangeTop = 1.;
float bTagRangeBottom = 0.;
float bTagCutStep = (bTagRangeTop - bTagRangeBottom) / cutAmnt;

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

//btag tight WPs by year
float bTagUL18Cut = 0.7100;
float bTagUL17Cut = 0.7476;
float bTagUL16Cut = 0.6377;
float bTagUL16APVCut = 0.6502;

//03132024 added veto dr
float lepVetodRCut = 0.4;

//032024 UpdatedCuts

float ptLeadElecCut = 25.;
float ptLeadMuonCut = 19.;
float ptTrailingElecCut = 18.;
float ptTrailingMuonCut = 12.;

float hFatJetPTBDTCut = 250.;


//072023 Lepton Tight ttH ID cuts
float ePtTightCut = 10.;
float ePtLooseCut = 7.;

float eEtaTightCut = 2.5;

float lDxyTightCut = 0.05;
float lDzTightCut = 0.1;
float lMiniPFRelIsoTightCut = 0.4;
float eSieieBarrelTightCut = 0.011;

float eSieieEndcapTightCut = 0.030;

float eHoeTightCut = 0.1;
float eInvMinusPInvTightCut = -0.04;
float ePromptMVATightCut = 0.8;

UInt_t eLostHitsTightCut = 0;

float lepJetDeepTagLooseBDTCut = 0.0521;
float lepJetDeepTagMediumBDTCut = 0.3033;


float mPtTightCut = 10.;
float mPtLooseCut = 5.;



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
float eSieieBarrelRangeTop = 0.1;
float eSieieBarrelRangeBottom = 0.;
float eSieieBarrelCutStep = (eSieieBarrelRangeTop - eSieieBarrelRangeBottom) / cutAmnt;

float eSieieEndcapCut = 0.030;
float eSieieEndcapRangeTop = 0.1;
float eSieieEndcapRangeBottom = 0.011;
float eSieieEndcapCutStep = (eSieieEndcapRangeTop - eSieieEndcapRangeBottom) / cutAmnt;


float eHoeCut = 0.1;
float eHoeRangeTop = .2;
float eHoeRangeBottom = 0.;
float eHoeCutStep = (eHoeRangeTop - eHoeRangeBottom) / cutAmnt;
float eInvMinusPInvCut = -0.04;
float eInvMinusPInvRangeTop = 0.05;
float eInvMinusPInvRangeBottom = -0.05;
float eInvMinusPInvCutStep = (eInvMinusPInvRangeTop - eInvMinusPInvRangeBottom) / cutAmnt;
float ePromptMVACut = 0.8;
float ePromptMVARangeTop = 1.;
float ePromptMVARangeBottom = -1.;
float ePromptMVACutStep = (ePromptMVARangeTop - ePromptMVARangeBottom) / cutAmnt;

UInt_t eLostHitsCut = 0;

float lepJetDeepTagLooseCut = 0.0521;
float lepJetDeepTagLooseRangeTop = 0.49;
float lepJetDeepTagLooseRangeBottom = 0.;
float lepJetDeepTagLooseCutStep = (lepJetDeepTagLooseRangeTop - lepJetDeepTagLooseRangeBottom) / cutAmnt;
float lepJetDeepTagMediumCut = 0.3033;
float lepJetDeepTagMediumRangeTop = 1.;
float lepJetDeepTagMediumRangeBottom = 0.2;
float lepJetDeepTagMediumCutStep = (lepJetDeepTagMediumRangeTop - lepJetDeepTagMediumRangeBottom) / cutAmnt;

float mPromptMVACut = 0.85;
float mPromptMVARangeTop = 1.;
float mPromptMVARangeBottom = -1.;
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
float lepIsoRangeTop = 5.;
float lepIsoRangeBottom = 0.;
float lepIsoCutStep = (lepIsoRangeTop - lepIsoRangeBottom) / cutAmnt;

float SIPCut = 4.;
float SIPRangeTop = 10.;
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

// V2 BDT Cuts 07282022 #moving the particle net cuts to 0 and the BTag to 1

float dRBDTCut = 0.8;

//float jetPTBDTCut = 20.;
//08102023 Changing Pt cut to 30
float jetPTBDTCut = 30.;

float jetEtaDifBDTCut = 2.0;

float jetInvMassBDTCut = 200.;

float bTagBDTCut = 1.0;

//Higgs FJ cuts

//float hFatJetPTBDTCut = 200.;


float hFatJetParticleNetBDTCut = 0.0;

//updating lep bdt for the tight lepton id 07262023
float ePtBDTCut = 10.;

float mPtBDTCut = 10.;

float SIPBDTCut = 8.;
float ePromptMVABDTCut = 0.8;
float mPromptMVABDTCut = 0.85;

//Lep cuts

//float ePtBDTCut = 7.;

float eEtaBDTCut = 2.5;

//float mPtBDTCut = 5.;

float mEtaBDTCut = 2.4;

float invMassBDTCutLow=60.;

float invMassBDTCutHigh=120.;

float ptLeadBDTCut=20.;

float ptTrailingBDTCut=10.;

float fourLepInvMassBDTCut = 100.;

float optLepInvMassBDTCut = 12.;

float lepIsoBDTCut = 4.;

//float SIPBDTCut = 4.;

//Semi-Lep cuts
//fatJetPTBDTCut = 200.;

float fatJetZParticleNetBDTCut = 0.0;

float ZPairPlusHInvMassBDTCut = 500;
float ZPairPlusHPtBDTCut = 500;


float lDxyBDTCut = 0.05;
float lDzBDTCut = 0.1;
float lMiniPFRelIsoBDTCut = 0.4;
float eSieieBarrelBDTCut = 0.03;
float eSieieEndcapBDTCut = 0.011;

float eHoeBDTCut = 0.1;
float eInvMinusPInvBDTCut = -0.04;
//float ePromptMVABDTCut = -0.8;
//float lepJetDeepTagLooseBDTCut = 0.3;
//float lepJetDeepTagMediumBDTCut = 0.5;
//float mPromptMVABDTCut = 0.2;



/*
// V1 BDT Cuts 07212022 #Lowering everything

float dRBDTCut = 0.8;

float jetPTBDTCut = 20.;

float jetEtaDifBDTCut = 2.0;

float jetInvMassBDTCut = 200.;

float bTagBDTCut = 0.9;

//Higgs FJ cuts

float hFatJetPTBDTCut = 200.;


float hFatJetParticleNetBDTCut = 0.1;



//Lep cuts

float ePtBDTCut = 7.;

float eEtaBDTCut = 2.5;

float mPtBDTCut = 5.;

float mEtaBDTCut = 2.4;

float invMassBDTCutLow=60.;

float invMassBDTCutHigh=120.;

float ptLeadBDTCut=20.;

float ptTrailingBDTCut=10.;

float fourLepInvMassBDTCut = 100.;

float optLepInvMassBDTCut = 12.;

float lepIsoBDTCut = 4.;

float SIPBDTCut = 4.;

//Semi-Lep cuts
//fatJetPTBDTCut = 200.;

float fatJetZParticleNetBDTCut = 0.2;

float ZPairPlusHInvMassBDTCut = 500;
float ZPairPlusHPtBDTCut = 500;


float lDxyBDTCut = 0.05;
float lDzBDTCut = 0.1;
float lMiniPFRelIsoBDTCut = 0.4;
float eSieieBarrelBDTCut = 0.03;
float eSieieEndcapBDTCut = 0.011;

float eHoeBDTCut = 0.1;
float eInvMinusPInvBDTCut = -0.04;
float ePromptMVABDTCut = -0.8;
float lepJetDeepTagLooseBDTCut = 0.3;
float lepJetDeepTagMediumBDTCut = 0.5;
float mPromptMVABDTCut = 0.2;

*/
///////////////////////////////////////////////////

//Weak cuts V16 07052022

float dRWeakCut = 0.8;

float jetPTWeakCut = 20.;

float jetEtaDifWeakCut = 2.0;

float jetInvMassWeakCut = 400.;

//Higgs FJ cuts

float hFatJetPTWeakCut = 250.;


float hFatJetParticleNetWeakCut = 0.8;



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

float lepIsoWeakCut = 4.;

float SIPWeakCut = 4.;

//Semi-Lep cuts
//fatJetPTWeakCut = 200.;

float fatJetZParticleNetWeakCut = 0.8;

float ZPairPlusHInvMassWeakCut = 1500;
float ZPairPlusHPtWeakCut = 1000;


float lDxyWeakCut = 0.05;
float lDzWeakCut = 0.1;
float lMiniPFRelIsoWeakCut = 0.4;
float eSieieBarrelWeakCut = 0.03;
float eSieieEndcapWeakCut = 0.011;

float eHoeWeakCut = 0.1;
float eInvMinusPInvWeakCut = -0.04;
float ePromptMVAWeakCut = -0.8;
float lepJetDeepTagLooseWeakCut = 0.3;
float lepJetDeepTagMediumWeakCut = 0.5;
float mPromptMVAWeakCut = 0.2;


//Weak cuts V12 06082022 


/*
float dRWeakCut = 0.8;

float jetPTWeakCut = 5.;

float jetEtaDifWeakCut = 2.0;

float jetInvMassWeakCut = 400.;

//Higgs FJ cuts

float hFatJetPTWeakCut = 100.;


float hFatJetParticleNetWeakCut = 0.8;



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

float lepIsoWeakCut = 4.;

float SIPWeakCut = 4.;

//Semi-Lep cuts
//fatJetPTWeakCut = 200.;

float fatJetZParticleNetWeakCut = 0.8;

float ZPairPlusHInvMassWeakCut = 1500;
float ZPairPlusHPtWeakCut = 1000;


float lDxyWeakCut = 0.05;
float lDzWeakCut = 0.1;
float lMiniPFRelIsoWeakCut = 0.4;
float eSieieBarrelWeakCut = 0.03;
float eSieieEndcapWeakCut = 0.011;

float eHoeWeakCut = 0.1;
float eInvMinusPInvWeakCut = -0.04;
float ePromptMVAWeakCut = -0.8;
float lepJetDeepTagLooseWeakCut = 0.3;
float lepJetDeepTagMediumWeakCut = 0.5;
float mPromptMVAWeakCut = 0.2;
*/

//Messing around with local cuts 06082022 

/*


float dRWeakCut = 0.001;

float jetPTWeakCut = 5.;

float jetEtaDifWeakCut = .5;

float jetInvMassWeakCut = 100.;

//Higgs FJ cuts

float hFatJetPTWeakCut = 100.;


float hFatJetParticleNetWeakCut = 0.005;



//Lep cuts

float ePtWeakCut = 7.;

float eEtaWeakCut = 2.5;

float mPtWeakCut = 5.;

float mEtaWeakCut = 2.4;

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

float eHoeWeakCut = 1.5;
float eInvMinusPInvWeakCut = -0.15;
float ePromptMVAWeakCut = -0.8;
float lepJetDeepTagLooseWeakCut = 0.3;
float lepJetDeepTagMediumWeakCut = 0.5;
float mPromptMVAWeakCut = 0.2;
*/

/*

float dRWeakCut = 0.8;

float jetPTWeakCut = 0.;

float jetEtaDifWeakCut = 4.0;

float jetInvMassWeakCut = 00.;

//Higgs FJ cuts

float hFatJetPTWeakCut = 00.;


float hFatJetParticleNetWeakCut = 0.8;



//Lep cuts

float ePtWeakCut = 7.;

float eEtaWeakCut = 2.5;

float mPtWeakCut = 5.;

float mEtaWeakCut = 2.4;

float invMassWeakCutLow=60.;

float invMassWeakCutHigh=120.;

float ptLeadWeakCut=20.;

float ptTrailingWeakCut=10.;

float fourLepInvMassWeakCut = 100.;

float optLepInvMassWeakCut = 12.;

float lepIsoWeakCut = 20.;

float SIPWeakCut = 20.;

//Semi-Lep cuts
//fatJetPTWeakCut = 200.;

float fatJetZParticleNetWeakCut = 0.8;

float ZPairPlusHInvMassWeakCut = 1000;
float ZPairPlusHPtWeakCut = 1000;

float lDxyWeakCut = 1.3;
float lDzWeakCut = 1.5;
float lMiniPFRelIsoWeakCut = 110.;
float eSieieBarrelWeakCut = 10.05;
float eSieieEndcapWeakCut = 10.070;

float eHoeWeakCut = 11.5;
float eInvMinusPInvWeakCut = -10.15;
float ePromptMVAWeakCut = -1.9;
float lepJetDeepTagLooseWeakCut = 10.3;
float lepJetDeepTagMediumWeakCut = 10.5;
float mPromptMVAWeakCut = -10.2;
*/

/*
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
//unused
float fatJetZTagWeakCut = 0.1;
float hFatJetDeepTagWeakCut = 0.1;
float fatJetZTagBDTCut = 0.1;
float hFatJetDeepTagBDTCut = 0.1;


/*
float dRWeakCut = 0.001;

float jetPTWeakCut = 5.;

float jetEtaDifWeakCut = 2.;

float jetInvMassWeakCut = 100.;

//Higgs FJ cuts

float hFatJetPTWeakCut = 100.;


float hFatJetParticleNetWeakCut = 0.5;



//Lep cuts

float ePtWeakCut = 7.;

float eEtaWeakCut = 2.5;

float mPtWeakCut = 5.;

float mEtaWeakCut = 2.4;

float invMassWeakCutLow=80.;

float invMassWeakCutHigh=100.;

float ptLeadWeakCut=5.;

float ptTrailingWeakCut=3.;

float fourLepInvMassWeakCut = 30.;

float optLepInvMassWeakCut = 3.;

float lepIsoWeakCut = 10.;

float SIPWeakCut = 8.;

//Semi-Lep cuts
//fatJetPTWeakCut = 200.;

float fatJetZParticleNetWeakCut = 0.5;

float ZPairPlusHInvMassWeakCut = 1500;
float ZPairPlusHPtWeakCut = 1500;


float lDxyWeakCut = 0.3;
float lDzWeakCut = 0.5;
float lMiniPFRelIsoWeakCut = 10.;
float eSieieBarrelWeakCut = 0.05;
float eSieieEndcapWeakCut = 0.070;

float eHoeWeakCut = 1.5;
float eInvMinusPInvWeakCut = -0.15;
float ePromptMVAWeakCut = -0.8;
float lepJetDeepTagLooseWeakCut = 0.3;
float lepJetDeepTagMediumWeakCut = 0.5;
float mPromptMVAWeakCut = 0.2;

//unused
float fatJetZTagWeakCut = 0.1;
float hFatJetDeepTagWeakCut = 0.1;
*/

/*

//Weak cuts V11 06082022 

float dRWeakCut = 0.8;

float jetPTWeakCut = 5.;

float jetEtaDifWeakCut = 2.0;

float jetInvMassWeakCut = 400.;

//Higgs FJ cuts

float hFatJetPTWeakCut = 100.;


float hFatJetParticleNetWeakCut = 0.8;



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

float lepIsoWeakCut = 4.;

float SIPWeakCut = 4.;

//Semi-Lep cuts
//fatJetPTWeakCut = 200.;

float fatJetZParticleNetWeakCut = 0.8;

float ZPairPlusHInvMassWeakCut = 1000;
float ZPairPlusHPtWeakCut = 1000;


float lDxyWeakCut = 0.05;
float lDzWeakCut = 0.1;
float lMiniPFRelIsoWeakCut = 0.4;
float eSieieBarrelWeakCut = 0.03;
float eSieieEndcapWeakCut = 0.011;

float eHoeWeakCut = 0.1;
float eInvMinusPInvWeakCut = -0.04;
float ePromptMVAWeakCut = -0.8;
float lepJetDeepTagLooseWeakCut = 0.3;
float lepJetDeepTagMediumWeakCut = 0.5;
float mPromptMVAWeakCut = 0.2;
*/
/*
//unused
float fatJetZTagWeakCut = 0.1;
float hFatJetDeepTagWeakCut = 0.1;





//Weak cuts V10 06082022 

float dRWeakCut = 0.8;

float jetPTWeakCut = 5.;

float jetEtaDifWeakCut = 2.0;

float jetInvMassWeakCut = 400.;

//Higgs FJ cuts

float hFatJetPTWeakCut = 100.;


float hFatJetParticleNetWeakCut = 0.2;



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

float lepIsoWeakCut = 4.;

float SIPWeakCut = 4.;

//Semi-Lep cuts
//fatJetPTWeakCut = 200.;

float fatJetZParticleNetWeakCut = 0.2;

float ZPairPlusHInvMassWeakCut = 1000;
float ZPairPlusHPtWeakCut = 1000;


float lDxyWeakCut = 0.05;
float lDzWeakCut = 0.1;
float lMiniPFRelIsoWeakCut = 0.4;
float eSieieBarrelWeakCut = 0.03;
float eSieieEndcapWeakCut = 0.011;

float eHoeWeakCut = 0.1;
float eInvMinusPInvWeakCut = -0.04;
float ePromptMVAWeakCut = -0.8;
float lepJetDeepTagLooseWeakCut = 0.3;
float lepJetDeepTagMediumWeakCut = 0.5;
float mPromptMVAWeakCut = 0.2;

//unused
float fatJetZTagWeakCut = 0.1;
float hFatJetDeepTagWeakCut = 0.1;
*/
/*
//Weak cuts V9 06072022 

float dRWeakCut = 0.001;

float jetPTWeakCut = 5.;

float jetEtaDifWeakCut = 2.0;

float jetInvMassWeakCut = 400.;

//Higgs FJ cuts

float hFatJetPTWeakCut = 100.;


float hFatJetParticleNetWeakCut = 0.005;



//Lep cuts

float ePtWeakCut = 7.;

float eEtaWeakCut = 2.5;

float mPtWeakCut = 5.;

float mEtaWeakCut = 2.4;

float invMassWeakCutLow=80.;

float invMassWeakCutHigh=100.;

float ptLeadWeakCut=5.;

float ptTrailingWeakCut=3.;

float fourLepInvMassWeakCut = 100.;

float optLepInvMassWeakCut = 12.;

float lepIsoWeakCut = 4.;

float SIPWeakCut = 8.;

//Semi-Lep cuts
//fatJetPTWeakCut = 200.;

float fatJetZParticleNetWeakCut = 0.05;

float ZPairPlusHInvMassWeakCut = 1000;
float ZPairPlusHPtWeakCut = 1000;


float lDxyWeakCut = 0.05;
float lDzWeakCut = 0.1;
float lMiniPFRelIsoWeakCut = 0.4;
float eSieieBarrelWeakCut = 0.05;
float eSieieEndcapWeakCut = 0.070;

float eHoeWeakCut = 0.1;
float eInvMinusPInvWeakCut = -0.04;
float ePromptMVAWeakCut = -0.8;
float lepJetDeepTagLooseWeakCut = 0.3;
float lepJetDeepTagMediumWeakCut = 0.5;
float mPromptMVAWeakCut = 0.2;

//unused
float fatJetZTagWeakCut = 0.1;
float hFatJetDeepTagWeakCut = 0.1;
*/
/*
//Ultra Weak cuts V8 06022022 Added new lepton ID, moving back cuts, and added particle net instead of deeptag

float dRWeakCut = 0.001;

float jetPTWeakCut = 5.;

float jetEtaDifWeakCut = .5;

float jetInvMassWeakCut = 100.;

//Higgs FJ cuts

float hFatJetPTWeakCut = 100.;


float hFatJetParticleNetWeakCut = 0.005;



//Lep cuts

float ePtWeakCut = 7.;

float eEtaWeakCut = 2.5;

float mPtWeakCut = 5.;

float mEtaWeakCut = 2.4;

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

float eHoeWeakCut = 1.5;
float eInvMinusPInvWeakCut = -0.15;
float ePromptMVAWeakCut = -0.8;
float lepJetDeepTagLooseWeakCut = 0.3;
float lepJetDeepTagMediumWeakCut = 0.5;
float mPromptMVAWeakCut = 0.2;

//unused
float fatJetZTagWeakCut = 0.1;
float hFatJetDeepTagWeakCut = 0.1;
*/
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
