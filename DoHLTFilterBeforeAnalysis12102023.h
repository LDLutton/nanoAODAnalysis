#include<TTree.h>

bool debug = false;
bool endAfter = false;
int NToStart = 0;
int NToEnd = 2500;

bool debugGenPart = false;

bool testRun = false;
bool SDC2V2MCZZHReweight = false;
bool SDC2V2MCZZH17Reweight = false;
bool SDC2V2MCZZH16Reweight = false;
bool SDC2V2MCZZH16APVReweight = false;

bool SDC2V2MCWZHReweight = false;
bool SDC2V2MCWZH17Reweight = false;
bool SDC2V2MCWZH16Reweight = false;
bool SDC2V2MCWZH16APVReweight = false;


bool ttHToBBBackground = false;
bool ttZJetsBackground = false;
bool ttWJetsBackground = false;
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

bool ZZBackground = false;
bool WWBackground = false;
bool WZBackground = false;

bool TTbb_TTToHadronicBackground = false;
bool TTbb_TTTo2L2NuBackground = false;
bool TTbb_TTToSemiLeptonicBackground = false;

/////////NEW MC///////

bool DYM10To50Background = false;
bool ST_tW_antitopBackground = false;
bool ST_tW_topBackground = false;
bool EWKWMinus2Jets_WToLNuBackground = false;
bool EWKWMinus2Jets_WToQQBackground = false;
bool EWKWPlus2Jets_WToLNuBackground = false;
bool EWKWPlus2Jets_WToQQBackground = false;
bool VHToNonbbBackground = false;
bool WminusH_HToBB_WToLNuBackground = false;
bool WminusH_HToBB_WToQQBackground = false;
bool WplusH_HToBB_WToLNuBackground = false;
bool WplusH_HToBB_WToQQBackground = false;
bool WJetsToLNuBackground = false;
bool WWWBackground = false;
bool WWZBackground = false;
bool WZZBackground = false;
bool ZH_HToBB_ZToBBBackground = false;
bool ZH_HToBB_ZToNuNuBackground = false;
bool ZH_HToBB_ZToLLBackground = false;
bool ZH_HToBB_ZToQQBackground = false;
bool ggZH_HToBB_ZToBBBackground = false;
bool ggZH_HToBB_ZToNuNuBackground = false;
bool ggZH_HToBB_ZToLLBackground = false;
bool ggZH_HToBB_ZToQQBackground = false;
bool EWKZ2Jets_ZToLLBackground = false;
bool EWKZ2Jets_ZToNuNuBackground = false;
bool EWKZ2Jets_ZToQQBackground = false;
bool ZZZBackground = false;




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

float hTobbBR = 0.5772683;
float maxdRCut = 0.8;

//For calculating DeltaR for two particles from their respective etas and phis
float calcDeltaR(float phi1,float eta1,float phi2,float eta2){
    float deta = eta1-eta2;
    float dphi = abs(phi1-phi2);
    if (dphi > M_PI) dphi -= (2*M_PI);
    return sqrt((deta*deta)+(dphi*dphi));
}
