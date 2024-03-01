#include<TTree.h>

bool debug = false;
bool endAfter = false;
int NToStart = 0;
int NToEnd = 2500;

bool debugGenPart = false;

bool scratchDown = true;

bool testRun = true;
bool SDC2V3MCWZHV2 = false;
bool SDC2Vm2p5MCWZHV2 = false;
bool SDC2Vm3MCWZHV2 = false;
bool SDC2Vm1MCWZHV2 = false;
bool SDC2V0MCWZHV2 = false;
bool SDC2V1MCWZHV2 = false;
bool SDC2V4MCWZHV2 = false;
bool SDC2V5MCWZHV2 = false;
bool SDC2V3MC = false;
bool SDC2Vm2p5MC = false;
bool SDC2Vm2MC = false;
bool SDC2Vm1MC = false;
bool SDC2V0MC = false;
bool SDC2V1MC = false;
bool SDC2V4MC = false;
bool SDC2V4p5MC = false;
bool SDC2V3MCV2 = false;
bool SDC2Vm2p5MCV2 = false;
bool SDC2Vm2MCV2 = false;
bool SDC2Vm1MCV2 = false;
bool SDC2V0MCV2 = false;
bool SDC2V1MCV2 = false;
bool SDC2V4MCV2 = false;
bool SDC2V4p5MCV2 = false;

bool SDC2V3MCWZH2017V2 = false;
bool SDC2Vm2p5MCWZH2017V2 = false;
bool SDC2Vm3MCWZH2017V2 = false;
bool SDC2Vm1MCWZH2017V2 = false;
bool SDC2V0MCWZH2017V2 = false;
bool SDC2V1MCWZH2017V2 = false;
bool SDC2V4MCWZH2017V2 = false;
bool SDC2V5MCWZH2017V2 = false;
bool SDC2V3MC2017V2 = false;
bool SDC2Vm2p5MC2017V2 = false;
bool SDC2Vm2MC2017V2 = false;
bool SDC2Vm1MC2017V2 = false;
bool SDC2V0MC2017V2 = false;
bool SDC2V1MC2017V2 = false;
bool SDC2V4MC2017V2 = false;
bool SDC2V4p5MC2017V2 = false;

bool SDC2V3MCWZH2016V2 = false;
bool SDC2Vm2p5MCWZH2016V2 = false;
bool SDC2Vm3MCWZH2016V2 = false;
bool SDC2Vm1MCWZH2016V2 = false;
bool SDC2V0MCWZH2016V2 = false;
bool SDC2V1MCWZH2016V2 = false;
bool SDC2V4MCWZH2016V2 = false;
bool SDC2V5MCWZH2016V2 = false;
bool SDC2V3MC2016V2 = false;
bool SDC2Vm2p5MC2016V2 = false;
bool SDC2Vm2MC2016V2 = false;
bool SDC2Vm1MC2016V2 = false;
bool SDC2V0MC2016V2 = false;
bool SDC2V1MC2016V2 = false;
bool SDC2V4MC2016V2 = false;
bool SDC2V4p5MC2016V2 = false;

bool SDC2V3MCWZH2016APVV2 = false;
bool SDC2Vm2p5MCWZH2016APVV2 = false;
bool SDC2Vm3MCWZH2016APVV2 = false;
bool SDC2Vm1MCWZH2016APVV2 = false;
bool SDC2V0MCWZH2016APVV2 = false;
bool SDC2V1MCWZH2016APVV2 = false;
bool SDC2V4MCWZH2016APVV2 = false;
bool SDC2V5MCWZH2016APVV2 = false;
bool SDC2V3MC2016APVV2 = false;
bool SDC2Vm2p5MC2016APVV2 = false;
bool SDC2Vm2MC2016APVV2 = false;
bool SDC2Vm1MC2016APVV2 = false;
bool SDC2V0MC2016APVV2 = false;
bool SDC2V1MC2016APVV2 = false;
bool SDC2V4MC2016APVV2 = false;
bool SDC2V4p5MC2016APVV2 = false;

bool SDC2V2MCZZHReweight = false;
bool SDC2V2MCZZH17Reweight = false;
bool SDC2V2MCZZH16Reweight = false;
bool SDC2V2MCZZH16APVReweight = false;

bool SDC2V2MCWZHReweight = false;
bool SDC2V2MCWZH17Reweight = false;
bool SDC2V2MCWZH16Reweight = false;
bool SDC2V2MCWZH16APVReweight = false;


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

//Veto and Tight Lepton cuts
//elec veto
float elecPtVetoCut = 7;
float elecEtaVetoCut = 2.5;
float elecDxyVetoCut = 0.05;
float elecDzVetoCut = 0.1;
float elecSIP3DVetoCut = 8;
float elecMiniPFRelIsoCut = 0.4;
int elecLostHitsVetoCut = 1;
//elec tight
float elecPtTightCut = 10.;
float elecHoeTightCut = 0.1;
float elecInvMinusPInvTightCut = -0.04;
float elecLostHitsTightCut = 0;
float elecJetDeepTagMediumCut = 0.3033;
float elecPromptMVACut = 0.8;


//AK8 presel cuts
float AK8PtCut = 200;
float AK8MassCut = 50;
float AK8SDMassCut = 40;

//AK4 presel cuts
float AK4PtCut = 20;
float AK4AbsDEtaCut = 2.5;


//muon veto
float muonPtVetoCut = 5;
float muonEtaVetoCut = 2.4;
float muonDxyVetoCut = 0.05;
float muonDzVetoCut = 0.1;
float muonSIP3DVetoCut = 8;
//muon tight
float muonPtTightCut = 10;
float muonJetDeepTagMediumCut = 0.3033;
float muonPromptMVACut = 0.85;



void getVetoAndTightElectrons(TTreeReaderArray<Int_t> &nLep,TTreeReaderArray<Bool_t> &Lep_IdL,TTreeReaderArray<Float_t> &Lep_pt,TTreeReaderArray<Float_t> &Lep_eta,TTreeReaderArray<Float_t> &Lep_Dxy,TTreeReaderArray<Float_t> &Lep_Dz,TTreeReaderArray<Float_t> &Lep_sip3d,TTreeReaderArray<Float_t> &Lep_MiniPFRelIso,TTreeReaderArray<Float_t> &Electron_hoe,TTreeReaderArray<Float_t> &Electron_eInvMinusPInv,TTreeReaderArray<Bool_t> &Electron_convVeto,TTreeReaderArray<UChar_t> &Electron_lostHits,TTreeReaderArray<Int_t> &Lep_jetIdx,TTreeReaderArray<Float_t> &Jet_btagDeepFlavB,TTreeReaderArray<Float_t> &Lep_mvaTTH, int &nVetoLep, int &nTightLep, int &tightLepOneInd, int &tightLepTwoInd,bool &oneTightLepFound, float lPtVetoCut,float lEtaVetoCut,float lDxyVetoCut,float lDzVetoCut,float lSIP3DVetoCut,float lMiniPFRelIsoCut,int eLostHitsVetoCut,float lPtTightCut,float eHoeTightCut,float eInvMinusPInvTightCut,int eLostHitsTightCut,float lepJetDeepTagMediumCut,float lPromptMVACut, bool debug){
    for (UInt_t lItr=0; lItr < *nLep; lItr++){
        if (debug) std::cout << "lItr " << lItr<< "Lep_IdL[lItr]" << Lep_IdL[lItr] << "\n";
        if (!Lep_IdL[lItr]){ //EGamma POG MVA LOOSE ID
            continue;
        }
        float tmpPt = Lep_pt[lItr];
        if (debug) std::cout << "lItr " << lItr << " tmpPt " << tmpPt << "\n";
        if (tmpPt > lPtVetoCut){
            if (debug) std::cout << "passed pt cut\n";
            float tmpEta = Lep_eta[lItr];
            if (debug) std::cout << "tmpEta " <<tmpEta << "\n";
            if (abs(tmpEta) < lEtaVetoCut){
                if (debug) std::cout << "passed eta cut\n";
                float tmpDxy = Lep_Dxy[lItr];
                if (abs(tmpDxy) < lDxyVetoCut) {
                    if (debug) std::cout << "passed Dxy cut\n";
                    float tmpDz = Lep_Dz[lItr];
                    if (abs(tmpDz) < lDzVetoCut) {
                        if (debug) std::cout << "passed Dz cut\n";
                        float tmpLepSIP3D = Lep_sip3d[lItr];
                        if (tmpLepSIP3D < lSIP3DVetoCut) {
                            if (debug) std::cout << "passed LepSIP3D cut\n";
                            float tmpLep_MiniPFRelIso = Lep_MiniPFRelIso[lItr];
                            if (tmpLep_MiniPFRelIso < lMiniPFRelIsoCut*tmpPt) {
                                UChar_t tmpLostHits =  Electron_lostHits[lItr];
                                if (tmpLostHits <= eLostHitsVetoCut) {
                                    //Passed Veto cut
                                    nVetoLep += 1;
                                    if (tmpPt > lPtTightCut){
                                        float tmpHoe = Electron_hoe[lItr];
                                        if (tmpHoe < eHoeTightCut) {
                                            if (debug) std::cout << "passed Lep Hoe cut\n";
                                            float tmpInvEInvP = Electron_eInvMinusPInv[lItr];
                                            if (tmpInvEInvP > eInvMinusPInvTightCut) {
                                                if (debug) std::cout << "passed Lep eInvMinusPInv cut\n";
                                                if (Electron_convVeto[lItr]) {
                                                    if (debug) std::cout << "passed Elec Conv cut\n";
                                                    UChar_t tmpLostHits =  Electron_lostHits[lItr];
                                                    if (tmpLostHits <= eLostHitsTightCut) {
                                                        if (debug) std::cout << "passed elec tight misshits cut\n";
                                                        Int_t tmpJetId = Lep_jetIdx[lItr];
                                                        if (debug) std::cout << "tmpJetId " << tmpJetId << "\n";
                                                        float tmpJetbTag;
                                                        if (tmpJetId <0) {
                                                            tmpJetbTag = 0;
                                                        }
                                                        else {
                                                            tmpJetbTag = Jet_btagDeepFlavB[tmpJetId];
                                                        }
                                                        if (tmpJetbTag < lepJetDeepTagMediumCut){
                                                            float tmpLepMVA = Lep_mvaTTH[lItr];
                                                            if (tmpLepMVA > lPromptMVACut) {
                                                                if (debug) std::cout << "passed Lep ttH MVA cut\n";
                                                                nTightLep += 1;
                                                                if (!oneTightLepFound){
                                                                    tightLepOneInd = lItr;
                                                                    oneTightLepFound = true;
                                                                }
                                                                else{
                                                                    tightLepTwoInd = lItr;
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}


void getVetoAndTightMuons(TTreeReaderArray<Int_t> &nLep,TTreeReaderArray<Bool_t> &Lep_LooseIdL,TTreeReaderArray<Bool_t> &Lep_MediumIdL,TTreeReaderArray<Float_t> &Lep_pt,TTreeReaderArray<Float_t> &Lep_eta,TTreeReaderArray<Float_t> &Lep_Dxy,TTreeReaderArray<Float_t> &Lep_Dz,TTreeReaderArray<Float_t> &Lep_sip3d,TTreeReaderArray<Float_t> &Lep_MiniPFRelIso,TTreeReaderArray<Int_t> &Lep_jetIdx,TTreeReaderArray<Float_t> &Jet_btagDeepFlavB,TTreeReaderArray<Float_t> &Lep_mvaTTH, int &nVetoLep, int &nTightLep, int &tightLepOneInd, int &tightLepTwoInd, bool &oneTightLepFound, float lPtVetoCut,float lEtaVetoCut,float lDxyVetoCut,float lDzVetoCut,float lSIP3DVetoCut,float lPtTightCut,float lepJetDeepTagMediumCut,float lPromptMVACut,bool debug){
    
    for (UInt_t lItr=0; lItr < *nLep; lItr++){
        float tmpPt = Lep_pt[lItr];
        if (debug) std::cout << "lItr " << lItr << " tmpPt " << tmpPt << "\n";
        if (tmpPt > lPtVetoCut){
            if (debug) std::cout << "passed pt cut\n";
            float tmpEta = Lep_eta[lItr];
            if (debug) std::cout << "tmpEta " <<tmpEta << "\n";
            if (abs(tmpEta) < lEtaVetoCut){
                if (debug) std::cout << "passed eta cut\n";
                float tmpDxy = Lep_Dxy[lItr];
                if (abs(tmpDxy) < lDxyVetoCut) {
                    if (debug) std::cout << "passed Dxy cut\n";
                    float tmpDz = Lep_Dz[lItr];
                    if (abs(tmpDz) < lDzVetoCut) {
                        if (debug) std::cout << "passed Dz cut\n";
                        float tmpLepSIP3D = Lep_sip3d[lItr];
                        if (tmpLepSIP3D < lSIP3DVetoCut) {
                            if (debug) std::cout << "passed LepSIP3D cut\n";
                            if (Lep_LooseIdL[lItr]){
                                if (debug) std::cout << "passed PFmuon loose WP cut\n";
                                //Passed Veto cut
                                nVetoLep += 1;
                                if (tmpPt > lPtTightCut){
                                    if (debug) std::cout << "passed tight pt cut\n";
                                    if (Lep_MediumIdL[lItr]){
                                        if (debug) std::cout << "passed PFmuon medium WP cut\n";

                                    
                                        Int_t tmpJetId = Lep_jetIdx[lItr];
                                        if (debug) std::cout << "tmpJetId " << tmpJetId << "\n";
                                        float tmpJetbTag;
                                        if (tmpJetId <0) {
                                            tmpJetbTag = 0;
                                        }
                                        else {
                                            tmpJetbTag = Jet_btagDeepFlavB[tmpJetId];
                                        }
                                        if (tmpJetbTag < lepJetDeepTagMediumCut){
                                            if (debug) std::cout << "passed jet btag cut\n";
                                            float tmpLepMVA = Lep_mvaTTH[lItr];
                                            if (tmpLepMVA > lPromptMVACut) {
                                                if (debug) std::cout << "passed Lep ttH MVA cut\n";
                                                nTightLep += 1;
                                                if (!oneTightLepFound){
                                                    tightLepOneInd = lItr;
                                                    oneTightLepFound = true;
                                                }
                                                else{
                                                    tightLepTwoInd = lItr;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}




