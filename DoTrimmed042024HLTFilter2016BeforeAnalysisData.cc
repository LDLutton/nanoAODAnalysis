#include<TApplication.h>
#include<TFile.h>
#include<TMath.h>
#include<TMinuit.h>
#include<TROOT.h>
#include<TSystem.h>
#include<TObject.h>



#include<TCanvas.h>
#include<TF1.h>
#include<TGraph.h>
#include<TGraphErrors.h>
#include<TLegend.h>
#include<TLine.h>
#include<TH2F.h>
#include<TPaveText.h>
#include<TPaveStats.h>
#include<TStyle.h>
#include<TTreeReader.h>
#include<TTreeReaderArray.h>
#include<TTreeReaderValue.h>
#include "DoHLTFilterBeforeAnalysis.h"
#include "new032022Analysis_FileList.h"
#include<time.h>
#include "golden_json.h"

#include<algorithm>
#include<chrono>
#include<ctime>
#include<fstream>
#include<iostream>
#include<mutex>
#include<string>

#include<thread>


#include<sys/stat.h>
#include<errno.h>



////////////////////////////////START OF MAIN FUNCTION////////////////////////////////
////////////////////////////////START OF MAIN FUNCTION////////////////////////////////
////////////////////////////////START OF MAIN FUNCTION////////////////////////////////
////////////////////////////////START OF MAIN FUNCTION////////////////////////////////


void DoTrimmed042024HLTFilter2016BeforeAnalysisData(string datasetString,UInt_t fileInd,uint yearInd){
    // Open the file. Note that the name of your file outside this class
    // will probably NOT be experiment.root.
    std::cout << "start\n";
    clock_t startt = clock();
    //Analyzer will run over all files put into fileAr

    std::vector<std::string> fileAr;

    std::string saveName;

    //if (datasetString == "BTagCSV16Data") BTagCSV16Data = true;
    //if (datasetString == "BTagMu16Data") BTagMu16Data = true;
    //if (datasetString == "Charmonium16Data") Charmonium16Data = true;
    //if (datasetString == "DisplacedJet16Data") DisplacedJet16Data = true;
    if (datasetString == "DoubleEG16Data") DoubleEG16Data = true;
    if (datasetString == "DoubleMuon16Data") DoubleMuon16Data = true;
    //if (datasetString == "DoubleMuonLowMass16Data") DoubleMuonLowMass16Data = true;
    //if (datasetString == "HTMHT16Data") HTMHT16Data = true;
    //if (datasetString == "JetHT16Data") JetHT16Data = true;
    //if (datasetString == "MET16Data") MET16Data = true;
    //if (datasetString == "MuOnia16Data") MuOnia16Data = true;
    //if (datasetString == "MuonEG16Data") MuonEG16Data = true;
    if (datasetString == "SingleElectron16Data") SingleElectron16Data = true;
    if (datasetString == "SingleMuon16Data") SingleMuon16Data = true;
    //if (datasetString == "SinglePhoton16Data") SinglePhoton16Data = true;
    //if (datasetString == "Tau16Data") Tau16Data = true;

    ////////////////////////////////GETTING DATASET////////////////////////////////
    ////////////////////////////////GETTING DATASET////////////////////////////////
    ////////////////////////////////GETTING DATASET////////////////////////////////
    ////////////////////////////////GETTING DATASET////////////////////////////////

    std::string strAdd;
    if (scratchDown) strAdd ="/afs/crc.nd.edu/user/d/dlutton/FROM_PANASAS";
    else strAdd ="/scratch365";

    uint datasetType;
    if (BTagCSV16Data){
        datasetType = 26;
        saveName = "BTagCSV16Data";
        
        int arrSize = sizeof(BTagCSV16DataAr)/sizeof(BTagCSV16DataAr[0]);
        fileAr.push_back(BTagCSV16DataAr[fileInd]);
    }
    else if (BTagMu16Data){
        datasetType = 27;
        saveName = "BTagMu16Data";
        
        int arrSize = sizeof(BTagMu16DataAr)/sizeof(BTagMu16DataAr[0]);
        fileAr.push_back(BTagMu16DataAr[fileInd]);
    }
    else if (Charmonium16Data){
        datasetType = 28;
        saveName = "Charmonium16Data";
        
        int arrSize = sizeof(Charmonium16DataAr)/sizeof(Charmonium16DataAr[0]);
        fileAr.push_back(Charmonium16DataAr[fileInd]);
    }
    else if (DisplacedJet16Data){
        datasetType = 29;
        saveName = "DisplacedJet16Data";
        
        int arrSize = sizeof(DisplacedJet16DataAr)/sizeof(DisplacedJet16DataAr[0]);
        fileAr.push_back(DisplacedJet16DataAr[fileInd]);
    }
    else if (DoubleEG16Data){
        datasetType = 30;
        saveName = "DoubleEG16Data";
        
        int arrSize = sizeof(DoubleEG16DataAr)/sizeof(DoubleEG16DataAr[0]);
        fileAr.push_back(DoubleEG16DataAr[fileInd]);
    }
    else if (DoubleMuon16Data){
        datasetType = 31;
        saveName = "DoubleMuon16Data";
        
        int arrSize = sizeof(DoubleMuon16DataAr)/sizeof(DoubleMuon16DataAr[0]);
        fileAr.push_back(DoubleMuon16DataAr[fileInd]);
    }
    else if (DoubleMuonLowMass16Data){
        datasetType = 32;
        saveName = "DoubleMuonLowMass16Data";
        
        int arrSize = sizeof(DoubleMuonLowMass16DataAr)/sizeof(DoubleMuonLowMass16DataAr[0]);
        fileAr.push_back(DoubleMuonLowMass16DataAr[fileInd]);
    }
    else if (HTMHT16Data){
        datasetType = 36;
        saveName = "HTMHT16Data";
        
        int arrSize = sizeof(HTMHT16DataAr)/sizeof(HTMHT16DataAr[0]);
        fileAr.push_back(HTMHT16DataAr[fileInd]);
    }
    else if (JetHT16Data){
        datasetType = 41;
        saveName = "JetHT16Data";
        
        int arrSize = sizeof(JetHT16DataAr)/sizeof(JetHT16DataAr[0]);
        fileAr.push_back(JetHT16DataAr[fileInd]);
    }
    else if (MET16Data){
        datasetType = 43;
        saveName = "MET16Data";
        
        int arrSize = sizeof(MET16DataAr)/sizeof(MET16DataAr[0]);
        fileAr.push_back(MET16DataAr[fileInd]);
    }
    else if (MuOnia16Data){
        datasetType = 44;
        saveName = "MuOnia16Data";
        
        int arrSize = sizeof(MuOnia16DataAr)/sizeof(MuOnia16DataAr[0]);
        fileAr.push_back(MuOnia16DataAr[fileInd]);
    }
    else if (MuonEG16Data){
        datasetType = 45;
        saveName = "MuonEG16Data";
        
        int arrSize = sizeof(MuonEG16DataAr)/sizeof(MuonEG16DataAr[0]);
        fileAr.push_back(MuonEG16DataAr[fileInd]);
    }
    else if (SingleElectron16Data){
        datasetType = 46;
        saveName = "SingleElectron16Data";
        
        int arrSize = sizeof(SingleElectron16DataAr)/sizeof(SingleElectron16DataAr[0]);
        fileAr.push_back(SingleElectron16DataAr[fileInd]);
    }
    else if (SingleMuon16Data){
        datasetType = 47;
        saveName = "SingleMuon16Data";
        
        int arrSize = sizeof(SingleMuon16DataAr)/sizeof(SingleMuon16DataAr[0]);
        fileAr.push_back(SingleMuon16DataAr[fileInd]);
    }
    else if (SinglePhoton16Data){
        datasetType = 48;
        saveName = "SinglePhoton16Data";
        
        int arrSize = sizeof(SinglePhoton16DataAr)/sizeof(SinglePhoton16DataAr[0]);
        fileAr.push_back(SinglePhoton16DataAr[fileInd]);
    }
    else if (Tau16Data){
        datasetType = 49;
        saveName = "Tau16Data";
        
        int arrSize = sizeof(Tau16DataAr)/sizeof(Tau16DataAr[0]);
        fileAr.push_back(Tau16DataAr[fileInd]);
    }
    
    else if (testRun){
        saveName = "testRun";
        fileAr.push_back("./002609B3-3A29-1142-B867-A10BAA3268ED.root");
        
    }
    else if (LaraTest){
        saveName = "LaraTest";
        fileAr.push_back("/scratch365/dlutton/NanoAODFiles/pp_hwpwmjj_EFT_VBF_chw_09999000_250k.root");
    }
    else{
        std::cout << "ERROR. NO INPUT DATASET NAME GIVEN\n";
    }

    if (!useSingleLepHLT){
        saveName = saveName+"_NoSLHLT";
    }

    std::cout << "Doing " << saveName << "\n";
    //Setting up outfile for tree
    std::string outFileStr = "HLTTrimmedFilteredForAnalysis"+saveName+"_"+std::to_string(fileInd)+".root";
    std::cout << "OutFile: " << outFileStr << "\n";
    TFile *outFile = new TFile(outFileStr.c_str(),"RECREATE");
    
    //const array of the alphabet in capital letters
    std::string alphabet[26] = {"A","B","C","D","E","F","G","H","I","J","K","L","M",
                                "N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};
    ////////////////////////////////DEFINING TREES////////////////////////////////
    ////////////////////////////////DEFINING TREES////////////////////////////////
    ////////////////////////////////DEFINING TREES////////////////////////////////
    ////////////////////////////////DEFINING TREES////////////////////////////////

    UInt_t passGoldenJSONCtr = 0;
    UInt_t passFlagCtr = 0;
    UInt_t passHLTCtr = 0;
    UInt_t passnFJCtr = 0;
    UInt_t passnVBFCtr = 0;


    UInt_t evRunOver = 0;
    UInt_t evCount = 0;
    
    UInt_t nEv;
    UInt_t nEvPass;
    

    TTree *evNumTree = new TTree("evNumTree","evNumTree");

    evNumTree->Branch("nEv",&nEv,"nEv/i");
    evNumTree->Branch("nEvPass",&nEvPass,"nEvPass/i");

    UInt_t runL;

    UInt_t datasetTypeL;

    //Run alphanumeric represented by int
    UInt_t runAlphNumL;
    Bool_t APV;

    //Jets
    UInt_t nJetL;
    std::vector<Float_t> Jet_etaL;
    std::vector<Float_t> Jet_ptL;
    std::vector<Float_t> Jet_phiL;
    std::vector<Float_t> Jet_massL;
    std::vector<Int_t> Jet_jetIdL;
    std::vector<Float_t> Jet_btagDeepFlavBL;
    Float_t fixedGridRhoFastjetAllL;

    //Fat jets

    UInt_t nFatJetL;
    std::vector<Float_t> FatJet_etaL;
    std::vector<Float_t> FatJet_ptL;
    std::vector<Float_t> FatJet_phiL;
    std::vector<Float_t> FatJet_massL;
    std::vector<Int_t> FatJet_jetIdL;
    std::vector<Float_t> FatJet_deepTag_HL;
    std::vector<Float_t> FatJet_deepTag_ZvsQCDL;
    std::vector<Float_t> FatJet_msoftdropL;
    std::vector<Float_t> FatJet_particleNet_massL;

    //Electrons
    UInt_t nElectronL;
    std::vector<Float_t> Electron_etaL;
    std::vector<Float_t> Electron_massL;
    std::vector<Int_t> Electron_chargeL;
    std::vector<Float_t> Electron_phiL;
    std::vector<Float_t> Electron_ptL;
    std::vector<Float_t> Electron_dr03EcalRecHitSumEtL;
    std::vector<Float_t> Electron_dr03TkSumPtL;
    std::vector<Float_t> Electron_dr03HcalDepth1TowerSumEtL;
    std::vector<Float_t> Electron_pfRelIso03_allL;
    std::vector<Float_t> Electron_sip3dL;
    std::vector<Int_t> Electron_cutBasedL;
    std::vector<Bool_t> Electron_mvaFall17V2Iso_WP80L;
    std::vector<Bool_t> Electron_mvaFall17V2Iso_WP90L;
    std::vector<Bool_t> Electron_mvaFall17V2Iso_WPLL;
    std::vector<Bool_t> Electron_mvaFall17V2noIso_WP80L;
    std::vector<Bool_t> Electron_mvaFall17V2noIso_WP90L;
    std::vector<Bool_t> Electron_mvaFall17V2noIso_WPLL;

    std::vector<Float_t> Electron_dxyL;
    std::vector<Float_t> Electron_dzL;
    std::vector<Float_t> Electron_miniPFRelIso_allL;
    std::vector<Float_t> Electron_sieieL;
    std::vector<Float_t> Electron_hoeL;
    std::vector<Float_t> Electron_eInvMinusPInvL;
    std::vector<Bool_t> Electron_convVetoL;
    std::vector<UChar_t> Electron_lostHitsL;
    std::vector<Int_t> Electron_jetIdxL;
    std::vector<Float_t> Electron_jetRelIsoL;
    std::vector<Float_t> Electron_mvaTTHL;

    //Muons
    UInt_t nMuonL;
    std::vector<Float_t> Muon_etaL;
    std::vector<Float_t> Muon_massL;
    std::vector<Int_t> Muon_chargeL;
    std::vector<Float_t> Muon_phiL;
    std::vector<Float_t> Muon_ptL;
    std::vector<Float_t> Muon_pfRelIso03_allL;
    std::vector<Float_t> Muon_sip3dL;
    std::vector<Bool_t> Muon_tightIdL;
    std::vector<Bool_t> Muon_mediumIdL;
    std::vector<Bool_t> Muon_looseIdL;

    std::vector<Float_t> Muon_dxyL;
    std::vector<Float_t> Muon_dzL;
    std::vector<Float_t> Muon_miniPFRelIso_allL;
    std::vector<Int_t> Muon_jetIdxL;
    std::vector<Float_t> Muon_jetRelIsoL;
    std::vector<Float_t> Muon_mvaTTHL;
    std::vector<Int_t> Muon_nTrackerLayersL;

    

    //ParticleNet
    std::vector<Float_t> FatJet_particleNet_HbbvsQCDL;
    std::vector<Float_t> FatJet_particleNet_ZvsQCDL;
    std::vector<Float_t> FatJet_particleNetMD_QCDL;
    std::vector<Float_t> FatJet_particleNetMD_XbbL;
    std::vector<Float_t> FatJet_particleNetMD_XccL;
    std::vector<Float_t> FatJet_particleNetMD_XqqL;

    //HLT
    //2018
    Bool_t HLT_Ele32_WPTight_Gsf_L1DoubleEGL;
    Bool_t HLT_IsoMu27L;
    Bool_t HLT_Mu50L;
    Bool_t HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZL;
    Bool_t HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8L;

    //2016 in other years just set these to false
    Bool_t HLT_Ele27_WPTight_GsfL;
    Bool_t HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZL;

    //change 2018 to IsoMu24 and remove DZ from diele trigger for 2018 and 2017
    Bool_t HLT_IsoMu24L;
    Bool_t HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVLL;

    //2016 in other years just set these to false
    Bool_t HLT_IsoTkMu24L;

    //042024SFAndSuchAdditions
    //PU JetID
    std::vector<Int_t> Jet_puIdL;

    //05052024 Additions for PN regress mass scaling and resolution corrections
    //not necessary for data but have on hand just in case
    UInt_t luminosityBlockL;
    ULong64_t eventL;


    TTree *FilteredEventsTree = new TTree("FilteredEventsTree", "FilteredEventsTree");

    FilteredEventsTree->Branch("runL",&runL,"runL/i");
    FilteredEventsTree->Branch("datasetTypeL",&datasetTypeL,"datasetTypeL/i");

    //Run alphanumeric represented by int
    FilteredEventsTree->Branch("runAlphNumL",&runAlphNumL,"runAlphNumL/i");
    FilteredEventsTree->Branch("APV",&APV,"APV/O");

    //Jets    
    FilteredEventsTree->Branch("nJetL",&nJetL,"nJetL/i");
    FilteredEventsTree->Branch("Jet_etaL",&Jet_etaL);
    FilteredEventsTree->Branch("Jet_ptL",&Jet_ptL);
    FilteredEventsTree->Branch("Jet_phiL",&Jet_phiL);
    FilteredEventsTree->Branch("Jet_massL",&Jet_massL);
    FilteredEventsTree->Branch("Jet_jetIdL",&Jet_jetIdL);
    FilteredEventsTree->Branch("Jet_btagDeepFlavBL",&Jet_btagDeepFlavBL);
    FilteredEventsTree->Branch("fixedGridRhoFastjetAllL",&fixedGridRhoFastjetAllL,"fixedGridRhoFastjetAllL/F");

    //Fat jets

    FilteredEventsTree->Branch("nFatJetL",&nFatJetL,"nFatJetL/i");
    FilteredEventsTree->Branch("FatJet_etaL",&FatJet_etaL);
    FilteredEventsTree->Branch("FatJet_ptL",&FatJet_ptL);
    FilteredEventsTree->Branch("FatJet_phiL",&FatJet_phiL);
    FilteredEventsTree->Branch("FatJet_massL",&FatJet_massL);
    FilteredEventsTree->Branch("FatJet_jetIdL",&FatJet_jetIdL);
    FilteredEventsTree->Branch("FatJet_deepTag_HL",&FatJet_deepTag_HL);
    FilteredEventsTree->Branch("FatJet_deepTag_ZvsQCDL",&FatJet_deepTag_ZvsQCDL);
    FilteredEventsTree->Branch("FatJet_msoftdropL",&FatJet_msoftdropL);
    FilteredEventsTree->Branch("FatJet_particleNet_massL", &FatJet_particleNet_massL);

    //Electrons
    FilteredEventsTree->Branch("nElectronL",&nElectronL,"nElectronL/i");
    FilteredEventsTree->Branch("Electron_etaL",&Electron_etaL);
    FilteredEventsTree->Branch("Electron_massL",&Electron_massL);
    FilteredEventsTree->Branch("Electron_chargeL",&Electron_chargeL);
    FilteredEventsTree->Branch("Electron_phiL",&Electron_phiL);
    FilteredEventsTree->Branch("Electron_ptL",&Electron_ptL);
    FilteredEventsTree->Branch("Electron_dr03EcalRecHitSumEtL",&Electron_dr03EcalRecHitSumEtL);
    FilteredEventsTree->Branch("Electron_dr03TkSumPtL",&Electron_dr03TkSumPtL);
    FilteredEventsTree->Branch("Electron_dr03HcalDepth1TowerSumEtL",&Electron_dr03HcalDepth1TowerSumEtL);
    FilteredEventsTree->Branch("Electron_pfRelIso03_allL",&Electron_pfRelIso03_allL);
    FilteredEventsTree->Branch("Electron_sip3dL",&Electron_sip3dL);
    FilteredEventsTree->Branch("Electron_cutBasedL",&Electron_cutBasedL);
    FilteredEventsTree->Branch("Electron_mvaFall17V2Iso_WP80L",&Electron_mvaFall17V2Iso_WP80L);
    FilteredEventsTree->Branch("Electron_mvaFall17V2Iso_WP90L",&Electron_mvaFall17V2Iso_WP90L);
    FilteredEventsTree->Branch("Electron_mvaFall17V2Iso_WPLL",&Electron_mvaFall17V2Iso_WPLL);
    FilteredEventsTree->Branch("Electron_mvaFall17V2noIso_WP80L",&Electron_mvaFall17V2noIso_WP80L);
    FilteredEventsTree->Branch("Electron_mvaFall17V2noIso_WP90L",&Electron_mvaFall17V2noIso_WP90L);
    FilteredEventsTree->Branch("Electron_mvaFall17V2noIso_WPLL",&Electron_mvaFall17V2noIso_WPLL);


    //Muons
    FilteredEventsTree->Branch("nMuonL",&nMuonL,"nMuonL/i");
    FilteredEventsTree->Branch("Muon_etaL",&Muon_etaL);
    FilteredEventsTree->Branch("Muon_massL",&Muon_massL);
    FilteredEventsTree->Branch("Muon_chargeL",&Muon_chargeL);
    FilteredEventsTree->Branch("Muon_phiL",&Muon_phiL);
    FilteredEventsTree->Branch("Muon_ptL",&Muon_ptL);
    FilteredEventsTree->Branch("Muon_pfRelIso03_allL",&Muon_pfRelIso03_allL);
    FilteredEventsTree->Branch("Muon_sip3dL",&Muon_sip3dL);
    FilteredEventsTree->Branch("Muon_tightIdL",&Muon_tightIdL);
    FilteredEventsTree->Branch("Muon_mediumIdL",&Muon_mediumIdL);
    FilteredEventsTree->Branch("Muon_looseIdL",&Muon_looseIdL);


    //For LepID
    FilteredEventsTree->Branch("Electron_dxyL",&Electron_dxyL);
    FilteredEventsTree->Branch("Electron_dzL",&Electron_dzL);
    FilteredEventsTree->Branch("Electron_miniPFRelIso_allL",&Electron_miniPFRelIso_allL);
    FilteredEventsTree->Branch("Electron_sieieL",&Electron_sieieL);
    FilteredEventsTree->Branch("Electron_hoeL",&Electron_hoeL);
    FilteredEventsTree->Branch("Electron_eInvMinusPInvL",&Electron_eInvMinusPInvL);
    FilteredEventsTree->Branch("Electron_convVetoL",&Electron_convVetoL);
    FilteredEventsTree->Branch("Electron_lostHitsL",&Electron_lostHitsL);
    FilteredEventsTree->Branch("Electron_jetIdxL",&Electron_jetIdxL);
    FilteredEventsTree->Branch("Electron_jetRelIsoL",&Electron_jetRelIsoL);
    FilteredEventsTree->Branch("Electron_mvaTTHL",&Electron_mvaTTHL);

    FilteredEventsTree->Branch("Muon_dxyL",&Muon_dxyL);
    FilteredEventsTree->Branch("Muon_dzL",&Muon_dzL);
    FilteredEventsTree->Branch("Muon_miniPFRelIso_allL",&Muon_miniPFRelIso_allL);
    FilteredEventsTree->Branch("Muon_jetIdxL",&Muon_jetIdxL);
    FilteredEventsTree->Branch("Muon_jetRelIsoL",&Muon_jetRelIsoL);
    FilteredEventsTree->Branch("Muon_mvaTTHL",&Muon_mvaTTHL);
    FilteredEventsTree->Branch("Muon_nTrackerLayersL",&Muon_nTrackerLayersL);

    //ParticleNet
    FilteredEventsTree->Branch("FatJet_particleNet_HbbvsQCDL",&FatJet_particleNet_HbbvsQCDL);
    FilteredEventsTree->Branch("FatJet_particleNet_ZvsQCDL",&FatJet_particleNet_ZvsQCDL);

    FilteredEventsTree->Branch("FatJet_particleNetMD_QCDL", &FatJet_particleNetMD_QCDL);
    FilteredEventsTree->Branch("FatJet_particleNetMD_XbbL", &FatJet_particleNetMD_XbbL);
    FilteredEventsTree->Branch("FatJet_particleNetMD_XccL", &FatJet_particleNetMD_XccL);
    FilteredEventsTree->Branch("FatJet_particleNetMD_XqqL", &FatJet_particleNetMD_XqqL);

    //HLT
    FilteredEventsTree->Branch("HLT_Ele32_WPTight_Gsf_L1DoubleEGL",&HLT_Ele32_WPTight_Gsf_L1DoubleEGL,"HLT_Ele32_WPTight_Gsf_L1DoubleEGL/O");
    FilteredEventsTree->Branch("HLT_IsoMu27L",&HLT_IsoMu27L,"HLT_IsoMu27L/O");
    FilteredEventsTree->Branch("HLT_Mu50L",&HLT_Mu50L,"HLT_Mu50L/O");
    FilteredEventsTree->Branch("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZL",&HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZL,"HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZL/O");
    FilteredEventsTree->Branch("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8L",&HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8L,"HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8L/O");

    FilteredEventsTree->Branch("HLT_Ele27_WPTight_GsfL",&HLT_Ele27_WPTight_GsfL,"HLT_Ele27_WPTight_GsfL/O");
    FilteredEventsTree->Branch("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZL",&HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZL,"HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZL/O");

    FilteredEventsTree->Branch("HLT_IsoMu24L",&HLT_IsoMu24L,"HLT_IsoMu24L/O");
    FilteredEventsTree->Branch("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVLL",&HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVLL,"HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVLL/O");
    FilteredEventsTree->Branch("HLT_IsoTkMu24L",&HLT_IsoTkMu24L,"HLT_IsoTkMu24L/O");

    //042024SFAndSuchAdditions
    //PU JetID
    FilteredEventsTree->Branch("Jet_puIdL",&Jet_puIdL);

    //05052024 Additions for PN regress mass scaling and resolution corrections
    FilteredEventsTree->Branch("luminosityBlockL",&luminosityBlockL,"luminosityBlockL/i");
    FilteredEventsTree->Branch("eventL",&eventL,"eventL/l");





    //Getting ready the golden JSON arrays
    std::vector<int> runAr;
    std::vector<std::vector<std::pair<int, int>>> lumiAr;

    if (yearInd == 0){
        runAr = run_numbers2018;
        lumiAr = luminosity_blocks2018;
    }
    else if (yearInd == 1){
        runAr = run_numbers2017;
        lumiAr = luminosity_blocks2017;
    }
    else if (yearInd == 2 || yearInd == 3){
        runAr = run_numbers2016;
        lumiAr = luminosity_blocks2016;
    }
    
    
    std::cout << "Going into file loop.\n";

    for (UInt_t k=0; k<fileAr.size(); k++){
        if (endAfter && evCount > NToEnd) break;
        if (debug) std::cout<<"File:    "<<fileAr[k]<<"\n";
        //loop through the alphabet array above checking if the file name contains "Run2018"+alphabet[i]. If so, then set runAlphNum to i
        runAlphNumL = 27;
        for (UInt_t i=0; i<26; i++){
            if (fileAr[k].find("Run2018"+alphabet[i]) != std::string::npos){
                runAlphNumL = i;
                break;
            }
        } 
        //Open the file, get the Events tree
        //APV false for non-2016
        APV = false;
        TFile* tmpfile = TFile::Open(fileAr[k].c_str());
        if (!tmpfile) {
            std::cerr << "Could not open " << fileAr[k] << "\n";
            std::cerr << "Moving to next file.\n";
            continue;
        }
        outFile->cd();
        TTreeReader myEventsReader("Events", tmpfile);

        TTreeReaderValue<UInt_t> run(myEventsReader, "run");

        //Flag branches

        TTreeReaderValue<Bool_t> Flag_goodVertices(myEventsReader, "Flag_goodVertices");
        TTreeReaderValue<Bool_t> Flag_globalSuperTightHalo2016Filter(myEventsReader, "Flag_globalSuperTightHalo2016Filter");
        TTreeReaderValue<Bool_t> Flag_HBHENoiseFilter(myEventsReader, "Flag_HBHENoiseFilter");
        TTreeReaderValue<Bool_t> Flag_HBHENoiseIsoFilter(myEventsReader, "Flag_HBHENoiseIsoFilter");
        TTreeReaderValue<Bool_t> Flag_EcalDeadCellTriggerPrimitiveFilter(myEventsReader, "Flag_EcalDeadCellTriggerPrimitiveFilter");
        TTreeReaderValue<Bool_t> Flag_BadPFMuonFilter(myEventsReader, "Flag_BadPFMuonFilter");
        TTreeReaderValue<Bool_t> Flag_eeBadScFilter(myEventsReader, "Flag_eeBadScFilter");
        TTreeReaderValue<Bool_t> Flag_ecalBadCalibFilter(myEventsReader, "Flag_ecalBadCalibFilter");

        //HLT Branches

        TTreeReaderValue<Bool_t> HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ(myEventsReader, "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ");

        TTreeReaderValue<Bool_t> HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ(myEventsReader, "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ");
        TTreeReaderValue<Bool_t> HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL(myEventsReader, "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL");
        TTreeReaderValue<Bool_t> HLT_DoubleEle33_CaloIdL_MW(myEventsReader, "HLT_DoubleEle33_CaloIdL_MW");

        TTreeReaderValue<Bool_t> HLT_IsoMu24(myEventsReader, "HLT_IsoMu24");
        TTreeReaderValue<Bool_t> HLT_IsoTkMu24(myEventsReader, "HLT_IsoTkMu24");
        TTreeReaderValue<Bool_t> HLT_IsoMu27(myEventsReader, "HLT_IsoMu27");
        TTreeReaderValue<Bool_t> HLT_Mu50(myEventsReader, "HLT_Mu50");

        TTreeReaderValue<Bool_t> HLT_Ele27_WPTight_Gsf(myEventsReader, "HLT_Ele27_WPTight_Gsf");

        //jets

        TTreeReaderValue<UInt_t> nJet(myEventsReader, "nJet");
        TTreeReaderArray<Float_t> Jet_eta(myEventsReader, "Jet_eta");
        TTreeReaderArray<Float_t> Jet_pt(myEventsReader, "Jet_pt");
        TTreeReaderArray<Float_t> Jet_phi(myEventsReader, "Jet_phi");
        TTreeReaderArray<Float_t> Jet_mass(myEventsReader, "Jet_mass");
        TTreeReaderArray<Int_t> Jet_jetId(myEventsReader, "Jet_jetId");
        TTreeReaderArray<Float_t> Jet_btagDeepFlavB(myEventsReader, "Jet_btagDeepFlavB");
        TTreeReaderValue<Float_t> fixedGridRhoFastjetAll(myEventsReader, "fixedGridRhoFastjetAll");

        //Fat jets

        TTreeReaderValue<UInt_t> nFatJet(myEventsReader, "nFatJet");
        TTreeReaderArray<Float_t> FatJet_eta(myEventsReader, "FatJet_eta");
        TTreeReaderArray<Float_t> FatJet_pt(myEventsReader, "FatJet_pt");
        TTreeReaderArray<Float_t> FatJet_phi(myEventsReader, "FatJet_phi");
        TTreeReaderArray<Float_t> FatJet_mass(myEventsReader, "FatJet_mass");
        TTreeReaderArray<Int_t> FatJet_jetId(myEventsReader, "FatJet_jetId");
        TTreeReaderArray<Float_t> FatJet_deepTag_H(myEventsReader, "FatJet_deepTag_H");
        TTreeReaderArray<Float_t> FatJet_deepTag_ZvsQCD(myEventsReader, "FatJet_deepTag_ZvsQCD");
        TTreeReaderArray<Float_t> FatJet_msoftdrop(myEventsReader, "FatJet_msoftdrop");

        TTreeReaderArray<Float_t> FatJet_particleNet_mass(myEventsReader, "FatJet_particleNet_mass");

        
        //Electrons
        TTreeReaderValue<UInt_t> nElectron(myEventsReader, "nElectron");
        TTreeReaderArray<Float_t> Electron_eta(myEventsReader, "Electron_eta");
        TTreeReaderArray<Float_t> Electron_mass(myEventsReader, "Electron_mass");
        TTreeReaderArray<Int_t> Electron_charge(myEventsReader, "Electron_charge");
        TTreeReaderArray<Float_t> Electron_phi(myEventsReader, "Electron_phi");
        TTreeReaderArray<Float_t> Electron_pt(myEventsReader, "Electron_pt");
        TTreeReaderArray<Float_t> Electron_dr03EcalRecHitSumEt(myEventsReader, "Electron_dr03EcalRecHitSumEt");
        TTreeReaderArray<Float_t> Electron_dr03TkSumPt(myEventsReader, "Electron_dr03TkSumPt");
        TTreeReaderArray<Float_t> Electron_dr03HcalDepth1TowerSumEt(myEventsReader, "Electron_dr03HcalDepth1TowerSumEt");
        TTreeReaderArray<Float_t> Electron_pfRelIso03_all(myEventsReader, "Electron_pfRelIso03_all");
        
        TTreeReaderArray<Float_t> Electron_sip3d(myEventsReader, "Electron_sip3d");
        TTreeReaderArray<Int_t> Electron_cutBased(myEventsReader, "Electron_cutBased");
        TTreeReaderArray<Bool_t> Electron_mvaFall17V2Iso_WP80(myEventsReader, "Electron_mvaFall17V2Iso_WP80");
        TTreeReaderArray<Bool_t> Electron_mvaFall17V2Iso_WP90(myEventsReader, "Electron_mvaFall17V2Iso_WP90");
        TTreeReaderArray<Bool_t> Electron_mvaFall17V2Iso_WPL(myEventsReader, "Electron_mvaFall17V2Iso_WPL");
        TTreeReaderArray<Bool_t> Electron_mvaFall17V2noIso_WP80(myEventsReader, "Electron_mvaFall17V2noIso_WP80");
        TTreeReaderArray<Bool_t> Electron_mvaFall17V2noIso_WP90(myEventsReader, "Electron_mvaFall17V2noIso_WP90");
        TTreeReaderArray<Bool_t> Electron_mvaFall17V2noIso_WPL(myEventsReader, "Electron_mvaFall17V2noIso_WPL");

        //Muons
        TTreeReaderValue<UInt_t> nMuon(myEventsReader, "nMuon");
        TTreeReaderArray<Float_t> Muon_eta(myEventsReader, "Muon_eta");
        TTreeReaderArray<Float_t> Muon_mass(myEventsReader, "Muon_mass");
        TTreeReaderArray<Int_t> Muon_charge(myEventsReader, "Muon_charge");
        TTreeReaderArray<Float_t> Muon_phi(myEventsReader, "Muon_phi");
        TTreeReaderArray<Float_t> Muon_pt(myEventsReader, "Muon_pt");
        TTreeReaderArray<Float_t> Muon_pfRelIso03_all(myEventsReader, "Muon_pfRelIso03_all");
        
        TTreeReaderArray<Float_t> Muon_sip3d(myEventsReader, "Muon_sip3d");
        TTreeReaderArray<Bool_t> Muon_tightId(myEventsReader, "Muon_tightId");
        TTreeReaderArray<Bool_t> Muon_mediumId(myEventsReader, "Muon_mediumId");
        TTreeReaderArray<Bool_t> Muon_looseId(myEventsReader, "Muon_looseId");

        TTreeReaderArray<Int_t> Muon_nTrackerLayers(myEventsReader, "Muon_nTrackerLayers");
        
        //For LepID
        TTreeReaderArray<Float_t> Electron_dxy(myEventsReader, "Electron_dxy");
        TTreeReaderArray<Float_t> Electron_dz(myEventsReader, "Electron_dz");
        TTreeReaderArray<Float_t> Electron_miniPFRelIso_all(myEventsReader, "Electron_miniPFRelIso_all");
        TTreeReaderArray<Float_t> Electron_sieie(myEventsReader, "Electron_sieie");
        TTreeReaderArray<Float_t> Electron_hoe(myEventsReader, "Electron_hoe");
        TTreeReaderArray<Float_t> Electron_eInvMinusPInv(myEventsReader, "Electron_eInvMinusPInv");
        TTreeReaderArray<Bool_t> Electron_convVeto(myEventsReader, "Electron_convVeto");
        TTreeReaderArray<UChar_t> Electron_lostHits(myEventsReader, "Electron_lostHits");
        TTreeReaderArray<Int_t> Electron_jetIdx(myEventsReader, "Electron_jetIdx");
        TTreeReaderArray<Float_t> Electron_jetRelIso(myEventsReader, "Electron_jetRelIso");
        TTreeReaderArray<Float_t> Electron_mvaTTH(myEventsReader, "Electron_mvaTTH");

        TTreeReaderArray<Float_t> Muon_dxy(myEventsReader, "Muon_dxy");
        TTreeReaderArray<Float_t> Muon_dz(myEventsReader, "Muon_dz");
        TTreeReaderArray<Float_t> Muon_miniPFRelIso_all(myEventsReader, "Muon_miniPFRelIso_all");
        TTreeReaderArray<Int_t> Muon_jetIdx(myEventsReader, "Muon_jetIdx");
        TTreeReaderArray<Float_t> Muon_jetRelIso(myEventsReader, "Muon_jetRelIso");
        TTreeReaderArray<Float_t> Muon_mvaTTH(myEventsReader, "Muon_mvaTTH");


        //ParticleNet
        TTreeReaderArray<Float_t> FatJet_particleNet_HbbvsQCD(myEventsReader, "FatJet_particleNet_HbbvsQCD");
        TTreeReaderArray<Float_t> FatJet_particleNet_ZvsQCD(myEventsReader, "FatJet_particleNet_ZvsQCD");
        TTreeReaderArray<Float_t> FatJet_particleNetMD_QCD(myEventsReader, "FatJet_particleNetMD_QCD");
        TTreeReaderArray<Float_t> FatJet_particleNetMD_Xbb(myEventsReader, "FatJet_particleNetMD_Xbb");
        TTreeReaderArray<Float_t> FatJet_particleNetMD_Xcc(myEventsReader, "FatJet_particleNetMD_Xcc");
        TTreeReaderArray<Float_t> FatJet_particleNetMD_Xqq(myEventsReader, "FatJet_particleNetMD_Xqq");

        //042024SFAndSuchAdditions
        //PU JetID
        TTreeReaderArray<Int_t> Jet_puId(myEventsReader, "Jet_puId");
        //05052024 Additions for PN regress mass scaling and resolution corrections
        TTreeReaderValue<UInt_t> luminosityBlock(myEventsReader, "luminosityBlock");
        TTreeReaderValue<ULong64_t> event(myEventsReader, "event");


        
        
        if (k % 10 == 0){
            double tmpTime = (double)(clock()-startt)/CLOCKS_PER_SEC;
            std::cout << "Going into event loop for file" << k << " .\ttime:" << (double)(clock()-startt)/CLOCKS_PER_SEC << "\n";
        }


        //EvLoop
        while (myEventsReader.Next()) {
            //std::cout << "test\n";
            if (endAfter){
                if (evCount < NToStart){
                    evCount += 1;
                    continue;
                }
                if (evCount > NToEnd) break;
            }
            if (evCount % 100000 == 0) std::cout << "Event: " << evCount << "\n";
            if (debug){
                std::cout << "-------------------------\n";
                std::cout << "ev: " << evCount+1 << "\n";
            }
            //Increment event count
            evRunOver += 1;
            evCount += 1;


            //-------------Golden JSON-------------
            bool passGoldenJSON = false;
            //check if run number is in the golden JSON and get the index
            UInt_t runNum = *run;
            UInt_t runIndex = 0;
            bool runIndexFound = false;
            for (UInt_t i=0; i<runAr.size(); i++){
                if (runNum == runAr[i]){
                    runIndex = i;
                    runIndexFound = true;
                    break;
                }
            }
            //if run number is in the golden JSON, check if the lumi block is in the golden JSON
            if (runIndex < runAr.size() && runIndexFound){
                for (UInt_t i=0; i<lumiAr[runIndex].size(); i++){
                    if (lumiAr[runIndex][i].first <= *luminosityBlock && lumiAr[runIndex][i].second >= *luminosityBlock){
                        passGoldenJSON = true;
                        break;
                    }
                }
            }

            if (!passGoldenJSON) continue;
            passGoldenJSONCtr += 1;



            //--------------KINEMATICS--------------

            UInt_t tmpnFatJets = *nFatJet;

            bool passFlagBool = *Flag_goodVertices && *Flag_globalSuperTightHalo2016Filter && *Flag_HBHENoiseFilter && *Flag_HBHENoiseIsoFilter && *Flag_EcalDeadCellTriggerPrimitiveFilter && *Flag_BadPFMuonFilter && *Flag_eeBadScFilter;

            if (!passFlagBool) continue;
            passFlagCtr += 1;
            


           bool passHLTBool = (*HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ || *HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ);
            if (useSingleLepHLT) {
                passHLTBool = (passHLTBool || *HLT_IsoMu24 || *HLT_IsoTkMu24 || *HLT_Ele27_WPTight_Gsf);
            }
            
            if (!passHLTBool) continue;
            passHLTCtr += 1;

            





            if (debug){
                std::cout <<"Passed HLT\n";
            }
            
            //Check if any fat jets in event
            
            if (tmpnFatJets<=0) continue;
            if (debug){
                std::cout <<"Passed nFJs\n";
            }
            passnFJCtr += 1;

            

            // check if two or more VBF jets in event
            UInt_t tmpnVBFJets = *nJet;
            
            if (tmpnVBFJets < 2) continue;
            if (debug){
                std::cout <<"Passed nJs\n";
            }

            passnVBFCtr += 1;

            
            runL = *run;
            eventL = *event;
            datasetTypeL = datasetType;
            //std::cout << evRunOver-1 << "passed\n";
            if (debug){
                std::cout <<"Filling Jets\n";
            }
            nJetL = tmpnVBFJets;
            for (UInt_t nJetItr=0; nJetItr<nJetL;nJetItr++){
                Jet_etaL.push_back(Jet_eta[nJetItr]);
                Jet_ptL.push_back(Jet_pt[nJetItr]);
                Jet_phiL.push_back(Jet_phi[nJetItr]);
                Jet_massL.push_back(Jet_mass[nJetItr]);
                Jet_jetIdL.push_back(Jet_jetId[nJetItr]);
                Jet_btagDeepFlavBL.push_back(Jet_btagDeepFlavB[nJetItr]);
            }
            fixedGridRhoFastjetAllL = *fixedGridRhoFastjetAll;

            //Fat jets
            if (debug){
                std::cout <<"Filling FJs\n";
            }
            nFatJetL = tmpnFatJets;
            for (UInt_t nFatJetItr=0; nFatJetItr<nFatJetL;nFatJetItr++){
                FatJet_etaL.push_back(FatJet_eta[nFatJetItr]);
                FatJet_ptL.push_back(FatJet_pt[nFatJetItr]);
                FatJet_phiL.push_back(FatJet_phi[nFatJetItr]);
                FatJet_massL.push_back(FatJet_mass[nFatJetItr]);
                FatJet_jetIdL.push_back(FatJet_jetId[nFatJetItr]);
                FatJet_deepTag_HL.push_back(FatJet_deepTag_H[nFatJetItr]);
                FatJet_deepTag_ZvsQCDL.push_back(FatJet_deepTag_ZvsQCD[nFatJetItr]);
                FatJet_particleNet_HbbvsQCDL.push_back(FatJet_particleNet_HbbvsQCD[nFatJetItr]);
                FatJet_particleNet_ZvsQCDL.push_back(FatJet_particleNet_ZvsQCD[nFatJetItr]);
                FatJet_particleNetMD_QCDL.push_back(FatJet_particleNetMD_QCD[nFatJetItr]);
                FatJet_particleNetMD_XbbL.push_back(FatJet_particleNetMD_Xbb[nFatJetItr]);
                FatJet_particleNetMD_XccL.push_back(FatJet_particleNetMD_Xcc[nFatJetItr]);
                FatJet_particleNetMD_XqqL.push_back(FatJet_particleNetMD_Xqq[nFatJetItr]);
                FatJet_msoftdropL.push_back(FatJet_msoftdrop[nFatJetItr]);
                FatJet_particleNet_massL.push_back(FatJet_particleNet_mass[nFatJetItr]);
            }

            //Electrons
            if (debug){
                std::cout <<"Filling Electrons\n";
            }
            nElectronL = *nElectron;
            for (UInt_t nElectronItr=0; nElectronItr<nElectronL;nElectronItr++){
                Electron_etaL.push_back(Electron_eta[nElectronItr]);
                Electron_massL.push_back(Electron_mass[nElectronItr]);
                Electron_chargeL.push_back(Electron_charge[nElectronItr]);
                Electron_phiL.push_back(Electron_phi[nElectronItr]);
                Electron_ptL.push_back(Electron_pt[nElectronItr]);
                Electron_dr03EcalRecHitSumEtL.push_back(Electron_dr03EcalRecHitSumEt[nElectronItr]);
                Electron_dr03TkSumPtL.push_back(Electron_dr03TkSumPt[nElectronItr]);
                Electron_dr03HcalDepth1TowerSumEtL.push_back(Electron_dr03HcalDepth1TowerSumEt[nElectronItr]);
                Electron_pfRelIso03_allL.push_back(Electron_pfRelIso03_all[nElectronItr]);
                Electron_sip3dL.push_back(Electron_sip3d[nElectronItr]);
                Electron_cutBasedL.push_back(Electron_cutBased[nElectronItr]);
                Electron_mvaFall17V2Iso_WP80L.push_back(Electron_mvaFall17V2Iso_WP80[nElectronItr]);
                Electron_mvaFall17V2Iso_WP90L.push_back(Electron_mvaFall17V2Iso_WP90[nElectronItr]);
                Electron_mvaFall17V2Iso_WPLL.push_back(Electron_mvaFall17V2Iso_WPL[nElectronItr]);
                Electron_mvaFall17V2noIso_WP80L.push_back(Electron_mvaFall17V2noIso_WP80[nElectronItr]);
                Electron_mvaFall17V2noIso_WP90L.push_back(Electron_mvaFall17V2noIso_WP90[nElectronItr]);
                Electron_mvaFall17V2noIso_WPLL.push_back(Electron_mvaFall17V2noIso_WPL[nElectronItr]);

                Electron_dxyL.push_back(Electron_dxy[nElectronItr]);
                Electron_dzL.push_back(Electron_dz[nElectronItr]);
                Electron_miniPFRelIso_allL.push_back(Electron_miniPFRelIso_all[nElectronItr]);
                Electron_sieieL.push_back(Electron_sieie[nElectronItr]);
                Electron_hoeL.push_back(Electron_hoe[nElectronItr]);
                Electron_eInvMinusPInvL.push_back(Electron_eInvMinusPInv[nElectronItr]);
                Electron_convVetoL.push_back(Electron_convVeto[nElectronItr]);
                Electron_lostHitsL.push_back(Electron_lostHits[nElectronItr]);
                Electron_jetIdxL.push_back(Electron_jetIdx[nElectronItr]);
                Electron_jetRelIsoL.push_back(Electron_jetRelIso[nElectronItr]);
                Electron_mvaTTHL.push_back(Electron_mvaTTH[nElectronItr]);
                



            }

            //Muons
            nMuonL = *nMuon;
            for (UInt_t nMuonItr=0; nMuonItr<nMuonL;nMuonItr++){
                Muon_etaL.push_back(Muon_eta[nMuonItr]);
                Muon_massL.push_back(Muon_mass[nMuonItr]);
                Muon_chargeL.push_back(Muon_charge[nMuonItr]);
                Muon_phiL.push_back(Muon_phi[nMuonItr]);
                Muon_ptL.push_back(Muon_pt[nMuonItr]);
                Muon_pfRelIso03_allL.push_back(Muon_pfRelIso03_all[nMuonItr]);
                Muon_sip3dL.push_back(Muon_sip3d[nMuonItr]);
                Muon_tightIdL.push_back(Muon_tightId[nMuonItr]);
                Muon_mediumIdL.push_back(Muon_mediumId[nMuonItr]);
                Muon_looseIdL.push_back(Muon_looseId[nMuonItr]);

                Muon_dxyL.push_back(Muon_dxy[nMuonItr]);
                Muon_dzL.push_back(Muon_dz[nMuonItr]);
                Muon_miniPFRelIso_allL.push_back(Muon_miniPFRelIso_all[nMuonItr]);
                Muon_jetIdxL.push_back(Muon_jetIdx[nMuonItr]);
                Muon_jetRelIsoL.push_back(Muon_jetRelIso[nMuonItr]);
                Muon_mvaTTHL.push_back(Muon_mvaTTH[nMuonItr]);
                Muon_nTrackerLayersL.push_back(Muon_nTrackerLayers[nMuonItr]);
            }

            //HLT 
            HLT_Ele32_WPTight_Gsf_L1DoubleEGL = false;
            HLT_IsoMu27L = *HLT_IsoMu27;
            HLT_Mu50L = *HLT_Mu50;
            HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZL = *HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;
            HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8L = false;

            //2016
            HLT_Ele27_WPTight_GsfL = *HLT_Ele27_WPTight_Gsf;
            HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZL = *HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ;

            //change 2018 to IsoMu24 and remove DZ from diele trigger
            HLT_IsoMu24L = *HLT_IsoMu24;
            HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVLL = *HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL;

            //2016 in other years just set these to false
            HLT_IsoTkMu24L = *HLT_IsoTkMu24;

            //042024SFAndSuchAdditions
            //PU JetID
            for (UInt_t nJetItr=0; nJetItr<nJetL;nJetItr++){
                Jet_puIdL.push_back(Jet_puId[nJetItr]);
            }

            //05052024 Additions for PN regress mass scaling and resolution corrections
            luminosityBlockL = *luminosityBlock;
            eventL = *event;

            FilteredEventsTree->Fill();

            Jet_etaL.clear();
            Jet_ptL.clear();
            Jet_phiL.clear();
            Jet_massL.clear();
            Jet_jetIdL.clear();
            Jet_btagDeepFlavBL.clear();

            FatJet_etaL.clear();
            FatJet_ptL.clear();
            FatJet_phiL.clear();
            FatJet_massL.clear();
            FatJet_jetIdL.clear();
            FatJet_deepTag_HL.clear();
            FatJet_deepTag_ZvsQCDL.clear();
            FatJet_msoftdropL.clear();
            FatJet_particleNet_massL.clear();
            

            Electron_etaL.clear();
            Electron_massL.clear();
            Electron_chargeL.clear();
            Electron_phiL.clear();
            Electron_ptL.clear();
            Electron_dr03EcalRecHitSumEtL.clear();
            Electron_dr03TkSumPtL.clear();
            Electron_dr03HcalDepth1TowerSumEtL.clear();
            Electron_pfRelIso03_allL.clear();
            Electron_sip3dL.clear();
            Electron_cutBasedL.clear();
            Electron_mvaFall17V2Iso_WP80L.clear();
            Electron_mvaFall17V2Iso_WP90L.clear();
            Electron_mvaFall17V2Iso_WPLL.clear();
            Electron_mvaFall17V2noIso_WP80L.clear();
            Electron_mvaFall17V2noIso_WP90L.clear();
            Electron_mvaFall17V2noIso_WPLL.clear();

            Electron_dxyL.clear();
            Electron_dzL.clear();
            Electron_miniPFRelIso_allL.clear();
            Electron_sieieL.clear();
            Electron_hoeL.clear();
            Electron_eInvMinusPInvL.clear();
            Electron_convVetoL.clear();
            Electron_lostHitsL.clear();
            Electron_jetIdxL.clear();
            Electron_jetRelIsoL.clear();
            Electron_mvaTTHL.clear();

            Muon_dxyL.clear();
            Muon_dzL.clear();
            Muon_miniPFRelIso_allL.clear();
            Muon_jetIdxL.clear();
            Muon_jetRelIsoL.clear();
            Muon_mvaTTHL.clear();

            
            

            Muon_etaL.clear();
            Muon_massL.clear();
            Muon_chargeL.clear();
            Muon_phiL.clear();
            Muon_ptL.clear();
            Muon_pfRelIso03_allL.clear();
            Muon_sip3dL.clear();
            Muon_tightIdL.clear();
            Muon_mediumIdL.clear();
            Muon_looseIdL.clear();
            Muon_nTrackerLayersL.clear();

            FatJet_particleNet_HbbvsQCDL.clear();
            FatJet_particleNet_ZvsQCDL.clear();

            FatJet_particleNetMD_QCDL.clear();
            FatJet_particleNetMD_XbbL.clear();
            FatJet_particleNetMD_XccL.clear();
            FatJet_particleNetMD_XqqL.clear();

            Jet_puIdL.clear();

        }
    }
    if (debug) std::cout << "Filling complete \n";

    clock_t endt = clock();
    double time_spent = (double)(endt - startt) / CLOCKS_PER_SEC;


    std::cout << "Finished file loop. " << "time: " << time_spent << "\n";

    nEv = evRunOver;
    nEvPass = passHLTCtr;
    evNumTree->Fill();

    std::cout << "evRunOver: " << evRunOver << " -------------------\n";
    std::cout << "passes Golden JSON: " << passGoldenJSONCtr << " ------------------- "<< "\n";
    std::cout << "passes Flag cut: " << passFlagCtr << " ------------------- "<< "\n";
    std::cout << "passes HLT cut: " << passHLTCtr << " ------------------- "<< "\n";
    std::cout << "passes nFJ cut: " << passnFJCtr << " ------------------- " << "\n";
    std::cout << "passes nVBF cut: " << passnVBFCtr << " ------------------- " << "\n";

    

    

    outFile->cd();
    evNumTree->Write("",TObject::kOverwrite);
    FilteredEventsTree->Write("",TObject::kOverwrite);

    outFile->Close();
}
