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


void DoTrimmed09272023HLTFilterOnReweightingBeforeAnalysis(UInt_t fileInd){
    // Open the file. Note that the name of your file outside this class
    // will probably NOT be experiment.root.
    std::cout << "start\n";
    clock_t startt = clock();
    //Analyzer will run over all files put into fileAr

    std::vector<std::string> fileAr;

    std::string saveName;
    float crossSection;
    bool isBackground;
    bool useLHETree = false;
    bool useFJGenMatchTree = false;
    bool useJGenMatchTree = false;

    ////////////////////////////////GETTING DATASET////////////////////////////////
    ////////////////////////////////GETTING DATASET////////////////////////////////
    ////////////////////////////////GETTING DATASET////////////////////////////////
    ////////////////////////////////GETTING DATASET////////////////////////////////

    std::string strAdd;
    if (scratchDown) strAdd ="/afs/crc.nd.edu/user/d/dlutton/FROM_PANASAS";
    else strAdd ="/scratch365";

    if (SDC2V2MCZZHReweight){
        saveName = "SDC2V2MCZZHReweight";
        isBackground = false;
        int arrSize = sizeof(SDC2V2MCZZHReweightAr)/sizeof(SDC2V2MCZZHReweightAr[0]);
        std::string tmpStrWithPath = SDC2V2MCZZHReweightAr[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V2MCZZHReweightAr[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2V2MCZZH17Reweight){
        saveName = "SDC2V2MCZZH17Reweight";
        isBackground = false;
        int arrSize = sizeof(SDC2V2MCZZH17ReweightAr)/sizeof(SDC2V2MCZZH17ReweightAr[0]);
        std::string tmpStrWithPath = SDC2V2MCZZH17ReweightAr[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V2MCZZH17ReweightAr[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2V2MCZZH16Reweight){
        saveName = "SDC2V2MCZZH16Reweight";
        isBackground = false;
        int arrSize = sizeof(SDC2V2MCZZH16ReweightAr)/sizeof(SDC2V2MCZZH16ReweightAr[0]);
        std::string tmpStrWithPath = SDC2V2MCZZH16ReweightAr[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V2MCZZH16ReweightAr[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2V2MCZZH16APVReweight){
        saveName = "SDC2V2MCZZH16APVReweight";
        isBackground = false;
        int arrSize = sizeof(SDC2V2MCZZH16APVReweightAr)/sizeof(SDC2V2MCZZH16APVReweightAr[0]);
        std::string tmpStrWithPath = SDC2V2MCZZH16APVReweightAr[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V2MCZZH16APVReweightAr[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2V2MCWZHReweight){
        saveName = "SDC2V2MCWZHReweight";
        isBackground = false;
        int arrSize = sizeof(SDC2V2MCWZHReweightAr)/sizeof(SDC2V2MCWZHReweightAr[0]);
        std::string tmpStrWithPath = SDC2V2MCWZHReweightAr[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V2MCWZHReweightAr[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2V2MCWZH17Reweight){
        saveName = "SDC2V2MCWZH17Reweight";
        isBackground = false;
        int arrSize = sizeof(SDC2V2MCWZH17ReweightAr)/sizeof(SDC2V2MCWZH17ReweightAr[0]);
        std::string tmpStrWithPath = SDC2V2MCWZH17ReweightAr[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V2MCWZH17ReweightAr[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2V2MCWZH16Reweight){
        saveName = "SDC2V2MCWZH16Reweight";
        isBackground = false;
        int arrSize = sizeof(SDC2V2MCWZH16ReweightAr)/sizeof(SDC2V2MCWZH16ReweightAr[0]);
        std::string tmpStrWithPath = SDC2V2MCWZH16ReweightAr[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V2MCWZH16ReweightAr[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2V2MCWZH16APVReweight){
        saveName = "SDC2V2MCWZH16APVReweight";
        isBackground = false;
        int arrSize = sizeof(SDC2V2MCWZH16APVReweightAr)/sizeof(SDC2V2MCWZH16APVReweightAr[0]);
        std::string tmpStrWithPath = SDC2V2MCWZH16APVReweightAr[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V2MCWZH16APVReweightAr[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (testRun){
        saveName = "testRun";
        //fileAr.push_back("./unweighted_eventspphzzjjQCD0SMHLOOP0NPE1NPcHWE1QEDE5ResMasAllVer100Ev10080Seed_0p999cHW100GeVIMJetCut_200.root");
        fileAr.push_back("./merged18.root");
        useLHETree = true;
        useFJGenMatchTree = true;
        isBackground = false;
        
    }
    else if (LaraTest){
        saveName = "LaraTest";
        fileAr.push_back("/scratch365/dlutton/NanoAODFiles/pp_hwpwmjj_EFT_VBF_chw_09999000_250k.root");
    }
    else{
        std::cout << "ERROR. NO INPUT DATASET NAME GIVEN\n";
    }

    std::cout << "Doing " << saveName << "\n";
    //Setting up outfile for tree
    std::string outFileStr = "HLTTrimmedFilteredForAnalysis"+saveName+"_"+std::to_string(fileInd)+".root";
    std::cout << "OutFile: " << outFileStr << "\n";
    TFile *outFile = new TFile(outFileStr.c_str(),"RECREATE");
    bool checkChannelSplits;
    if (isBackground){
        checkChannelSplits = false;
    }

    ////////////////////////////////DEFINING TREES////////////////////////////////
    ////////////////////////////////DEFINING TREES////////////////////////////////
    ////////////////////////////////DEFINING TREES////////////////////////////////
    ////////////////////////////////DEFINING TREES////////////////////////////////

    std::vector<std::string> C2VNameAr {"-2.0","-1.75","-1.5","-1.25","-1.0","-0.75","-0.5","-0.25","0.0","0.1","0.2","0.3","0.4","0.5","0.6","0.7","0.8","0.9","1.0","1.1","1.2","1.3","1.4","1.5","1.6","1.7","1.8","1.9","2.25","2.5","2.75","3.0","3.25","3.5","3.75","4.0"};

    std::vector<std::string> typeNameAr {"GenLep","GenSemiLep","GenHad","GenOther","GenLep NoHTobb","GenSemiLep NoHTobb","GenHad NoHTobb","GenOther NoHTobb"};
    std::vector<Double_t> zeroVec(37,0.0);
    std::vector<std::vector<Double_t>> passFlagWeightedCtrAr(9,zeroVec);
    std::vector<std::vector<Double_t>> passHLTWeightedCtrAr(9,zeroVec);
    std::vector<std::vector<Double_t>> passnFJWeightedCtrAr(9,zeroVec);
    std::vector<std::vector<Double_t>> passnVBFWeightedCtrAr(9,zeroVec);

    

    UInt_t passFlagCtr = 0;
    //Double_t passFlagWeightedCtr = 0;
    UInt_t passHLTCtr = 0;
    //Double_t passHLTWeightedCtr = 0;
    UInt_t passnFJCtr = 0;
    //Double_t passnFJWeightedCtr = 0;
    UInt_t passnVBFCtr = 0;
    //Double_t passnVBFWeightedCtr = 0;


    UInt_t passFlagGenLepCtr = 0;
    //Double_t passFlagGenLepWeightedCtr = 0;
    UInt_t passFlagGenSemiLepCtr = 0;
    //Double_t passFlagGenSemiLepWeightedCtr = 0;
    UInt_t passFlagGenHadCtr = 0;
    //Double_t passFlagGenHadWeightedCtr = 0;
    UInt_t passFlagGenOtherCtr = 0;
    //Double_t passFlagGenOtherWeightedCtr = 0;

    UInt_t passFlagGenLepNoHTobbCtr = 0;
    //Double_t passFlagGenLepNoHTobbWeightedCtr = 0;
    UInt_t passFlagGenSemiLepNoHTobbCtr = 0;
    //Double_t passFlagGenSemiLepNoHTobbWeightedCtr = 0;
    UInt_t passFlagGenHadNoHTobbCtr = 0;
    //Double_t passFlagGenHadNoHTobbWeightedCtr = 0;
    UInt_t passFlagGenOtherNoHTobbCtr = 0;
    //Double_t passFlagGenOtherNoHTobbWeightedCtr = 0;


    UInt_t passHLTGenLepCtr = 0;
    //Double_t passHLTGenLepWeightedCtr = 0;
    UInt_t passHLTGenSemiLepCtr = 0;
    //Double_t passHLTGenSemiLepWeightedCtr = 0;
    UInt_t passHLTGenHadCtr = 0;
    //Double_t passHLTGenHadWeightedCtr = 0;
    UInt_t passHLTGenOtherCtr = 0;
    //Double_t passHLTGenOtherWeightedCtr = 0;

    UInt_t passHLTGenLepNoHTobbCtr = 0;
    //Double_t passHLTGenLepNoHTobbWeightedCtr = 0;
    UInt_t passHLTGenSemiLepNoHTobbCtr = 0;
    //Double_t passHLTGenSemiLepNoHTobbWeightedCtr = 0;
    UInt_t passHLTGenHadNoHTobbCtr = 0;
    //Double_t passHLTGenHadNoHTobbWeightedCtr = 0;
    UInt_t passHLTGenOtherNoHTobbCtr = 0;
    //Double_t passHLTGenOtherNoHTobbWeightedCtr = 0;

    UInt_t passnFJGenLepCtr = 0;
    //Double_t passnFJGenLepWeightedCtr = 0;
    UInt_t passnFJGenSemiLepCtr = 0;
    //Double_t passnFJGenSemiLepWeightedCtr = 0;
    UInt_t passnFJGenHadCtr = 0;
    //Double_t passnFJGenHadWeightedCtr = 0;
    UInt_t passnFJGenOtherCtr = 0;
    //Double_t passnFJGenOtherWeightedCtr = 0;

    UInt_t passnFJGenLepNoHTobbCtr = 0;
    //Double_t passnFJGenLepNoHTobbWeightedCtr = 0;
    UInt_t passnFJGenSemiLepNoHTobbCtr = 0;
    //Double_t passnFJGenSemiLepNoHTobbWeightedCtr = 0;
    UInt_t passnFJGenHadNoHTobbCtr = 0;
    //Double_t passnFJGenHadNoHTobbWeightedCtr = 0;
    UInt_t passnFJGenOtherNoHTobbCtr = 0;
    //Double_t passnFJGenOtherNoHTobbWeightedCtr = 0;

    UInt_t passnVBFGenLepCtr = 0;
    //Double_t passnVBFGenLepWeightedCtr = 0;
    UInt_t passnVBFGenSemiLepCtr = 0;
    //Double_t passnVBFGenSemiLepWeightedCtr = 0;
    UInt_t passnVBFGenHadCtr = 0;
    //Double_t passnVBFGenHadWeightedCtr = 0;
    UInt_t passnVBFGenOtherCtr = 0;
    //Double_t passnVBFGenOtherWeightedCtr = 0;

    UInt_t passnVBFGenLepNoHTobbCtr = 0;
    //Double_t passnVBFGenLepNoHTobbWeightedCtr = 0;
    UInt_t passnVBFGenSemiLepNoHTobbCtr = 0;
    //Double_t passnVBFGenSemiLepNoHTobbWeightedCtr = 0;
    UInt_t passnVBFGenHadNoHTobbCtr = 0;
    //Double_t passnVBFGenHadNoHTobbWeightedCtr = 0;
    UInt_t passnVBFGenOtherNoHTobbCtr = 0;
    //Double_t passnVBFGenOtherNoHTobbWeightedCtr = 0;
    





    float crossSectionAvg = 0.;
    UInt_t crossSectionCtr = 0;
    float totCrossSectionWeight = 0.;
    UInt_t totCrossSectionEvCount = 0;
    UInt_t evRunOver = 0;
    UInt_t evCount = 0;
    
    UInt_t nEv;
    UInt_t nEvPass;
    

    TTree *evNumTree = new TTree("evNumTree","evNumTree");

    evNumTree->Branch("nEv",&nEv,"nEv/i");
    evNumTree->Branch("nEvPass",&nEvPass,"nEvPass/i");

    //EventReweighting
    UInt_t nLHEReweightingWeightL;
    std::vector<Float_t> LHEReweightingWeightL;

    //EventWeights
    //Float_t genWeightL;
    Double_t genWeightL;

    //Jets
    UInt_t nJetL;
    std::vector<Float_t> Jet_etaL;
    std::vector<Float_t> Jet_ptL;
    std::vector<Float_t> Jet_phiL;
    std::vector<Float_t> Jet_massL;
    std::vector<Int_t> Jet_jetIdL;

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

    std::vector<Float_t> Jet_btagDeepFlavBL;

    //ParticleNet
    std::vector<Float_t> FatJet_particleNet_HbbvsQCDL;
    std::vector<Float_t> FatJet_particleNet_ZvsQCDL;
    std::vector<Float_t> FatJet_particleNetMD_QCDL;
    std::vector<Float_t> FatJet_particleNetMD_XbbL;
    std::vector<Float_t> FatJet_particleNetMD_XccL;
    std::vector<Float_t> FatJet_particleNetMD_XqqL;




    //
    Float_t fixedGridRhoFastjetAllL;

    //genChannel characterization
    //0=Leptonic,1=Semi-leptonic,2=Hadronic,3=Other,4=Error
    UInt_t genChannelL;

    Bool_t HTobbBoolL;

    //FJ GENMATCH

    Int_t ZFJIndL;
    Int_t HFJIndL;
    Bool_t goodGenZFJMatchL;
    Bool_t goodGenHFJMatchL;
    Bool_t eventGenSemileptonicL;
    Bool_t eventGenHToBBL;
    UChar_t ZFJGenHadronFlavourL;
    UChar_t HFJGenHadronFlavourL;
    std::vector<Int_t> FatJet_hadronFlavourL;

    

    
    

    
    
    


    TTree *FilteredEventsTree = new TTree("FilteredEventsTree", "FilteredEventsTree");


    //Event reweighting
    FilteredEventsTree->Branch("nLHEReweightingWeightL",&nLHEReweightingWeightL,"nLHEReweightingWeightL/i");
    FilteredEventsTree->Branch("LHEReweightingWeightL",&LHEReweightingWeightL);

    //gen weights
    FilteredEventsTree->Branch("genWeightL",&genWeightL,"genWeightL/D");

    //Jets    
    FilteredEventsTree->Branch("nJetL",&nJetL,"nJetL/i");
    FilteredEventsTree->Branch("Jet_etaL",&Jet_etaL);
    FilteredEventsTree->Branch("Jet_ptL",&Jet_ptL);
    FilteredEventsTree->Branch("Jet_phiL",&Jet_phiL);
    FilteredEventsTree->Branch("Jet_massL",&Jet_massL);
    FilteredEventsTree->Branch("Jet_jetIdL",&Jet_jetIdL);

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

    FilteredEventsTree->Branch("Jet_btagDeepFlavBL",&Jet_btagDeepFlavBL);

    //ParticleNet
    FilteredEventsTree->Branch("FatJet_particleNet_HbbvsQCDL",&FatJet_particleNet_HbbvsQCDL);
    FilteredEventsTree->Branch("FatJet_particleNet_ZvsQCDL",&FatJet_particleNet_ZvsQCDL);

    FilteredEventsTree->Branch("FatJet_particleNetMD_QCDL", &FatJet_particleNetMD_QCDL);
    FilteredEventsTree->Branch("FatJet_particleNetMD_XbbL", &FatJet_particleNetMD_XbbL);
    FilteredEventsTree->Branch("FatJet_particleNetMD_XccL", &FatJet_particleNetMD_XccL);
    FilteredEventsTree->Branch("FatJet_particleNetMD_XqqL", &FatJet_particleNetMD_XqqL);

    //
    FilteredEventsTree->Branch("fixedGridRhoFastjetAllL",&fixedGridRhoFastjetAllL);

    //genChannel characterization
    //0=Leptonic,1=Semi-leptonic,2=Hadronic,3=Other,4=Error
    FilteredEventsTree->Branch("genChannelL",&genChannelL,"genChannelL/i");

    FilteredEventsTree->Branch("HTobbBoolL",&HTobbBoolL,"HTobbBoolL/O");


    FilteredEventsTree->Branch("ZFJIndL",&ZFJIndL,"ZFJIndL/I");
    FilteredEventsTree->Branch("HFJIndL",&HFJIndL,"HFJIndL/I");
    FilteredEventsTree->Branch("goodGenZFJMatchL",&goodGenZFJMatchL,"goodGenZFJMatchL/O");
    FilteredEventsTree->Branch("goodGenHFJMatchL",&goodGenHFJMatchL,"goodGenHFJMatchL/O");
    FilteredEventsTree->Branch("eventGenSemileptonicL",&eventGenSemileptonicL,"eventGenSemileptonicL/O");
    FilteredEventsTree->Branch("eventGenHToBBL",&eventGenHToBBL,"eventGenHToBBL/O");

    FilteredEventsTree->Branch("ZFJGenHadronFlavourL",&ZFJGenHadronFlavourL,"ZFJGenHadronFlavourL/b");
    FilteredEventsTree->Branch("HFJGenHadronFlavourL",&HFJGenHadronFlavourL,"HFJGenHadronFlavourL/b");
    FilteredEventsTree->Branch("FatJet_hadronFlavourL",&FatJet_hadronFlavourL);



    //GenTree

    //EventReweighting
    UInt_t nLHEReweightingWeightGenL;
    std::vector<Float_t> LHEReweightingWeightGenL;

    //Gen dR of H from Z particles
    Double_t HdRFromLeadZL;
    Double_t HdRFromTrailingZL;
    Double_t LeadZdRFromTrailingZL;
    
    

    TTree *genTree = new TTree("genTree", "genTree");

    //Gen dR of H from Z particles

    genTree->Branch("nLHEReweightingWeightGenL",&nLHEReweightingWeightGenL,"nLHEReweightingWeightGenL/i");
    genTree->Branch("LHEReweightingWeightGenL",&LHEReweightingWeightGenL);
    genTree->Branch("HdRFromLeadZL",&HdRFromLeadZL,"HdRFromLeadZL/D");
    genTree->Branch("HdRFromTrailingZL",&HdRFromTrailingZL,"HdRFromTrailingZL/D");
    genTree->Branch("LeadZdRFromTrailingZL",&LeadZdRFromTrailingZL,"LeadZdRFromTrailingZL/D");
    

    /////////////
    //GenLepFJTree

    //EventReweighting
    UInt_t nLHEReweightingWeightGenLepFJL;
    std::vector<Float_t> LHEReweightingWeightGenLepFJL;

    //Gen dR of H reco'd (but gen matched) decay products from Z reco'd (but gen matched) decay products
    //With HTobb
    //gen lep channel
    Double_t HGenFJdRFromLeadZLeadLepL;
    Double_t HGenFJdRFromLeadZTrailingLepL;
    Double_t HGenFJdRFromTrailingZLeadLepL;
    Double_t HGenFJdRFromTrailingZTrailingLepL;

    TTree *genLepFJTree = new TTree("genLepFJTree", "genLepFJTree");

    //Gen dR of H reco'd (but gen matched) decay products from Z reco'd (but gen matched) decay products
    //With HTobb
    //gen lep channel
    genLepFJTree->Branch("nLHEReweightingWeightGenLepFJL",&nLHEReweightingWeightGenLepFJL,"nLHEReweightingWeightGenLepFJL/i");
    genLepFJTree->Branch("LHEReweightingWeightGenLepFJL",&LHEReweightingWeightGenLepFJL);
    genLepFJTree->Branch("HGenFJdRFromLeadZLeadLepL",&HGenFJdRFromLeadZLeadLepL,"HGenFJdRFromLeadZLeadLepL/D");
    genLepFJTree->Branch("HGenFJdRFromLeadZTrailingLepL",&HGenFJdRFromLeadZTrailingLepL,"HGenFJdRFromLeadZTrailingLepL/D");
    genLepFJTree->Branch("HGenFJdRFromTrailingZLeadLepL",&HGenFJdRFromTrailingZLeadLepL,"HGenFJdRFromTrailingZLeadLepL/D");
    genLepFJTree->Branch("HGenFJdRFromTrailingZTrailingLepL",&HGenFJdRFromTrailingZTrailingLepL,"HGenFJdRFromTrailingZTrailingLepL/D");


    //GenSemiLepFJTree


    //EventReweighting
    UInt_t nLHEReweightingWeightGenSemiLepFJL;
    std::vector<Float_t> LHEReweightingWeightGenSemiLepFJL;

    //gen Semilep channel
    Double_t HGenFJdRFromLepZLeadLepL;
    Double_t HGenFJdRFromLepZTrailingLepL;
    Double_t HGenFJdRFromHadZFJL;

    TTree *genSemiLepFJTree = new TTree("genSemiLepFJTree", "genSemiLepFJTree");

    //gen Semilep channel
    genSemiLepFJTree->Branch("nLHEReweightingWeightGenSemiLepFJL",&nLHEReweightingWeightGenSemiLepFJL,"nLHEReweightingWeightGenSemiLepFJL/i");
    genSemiLepFJTree->Branch("LHEReweightingWeightGenSemiLepFJL",&LHEReweightingWeightGenSemiLepFJL);
    genSemiLepFJTree->Branch("HGenFJdRFromLepZLeadLepL",&HGenFJdRFromLepZLeadLepL,"HGenFJdRFromLepZLeadLepL/D");
    genSemiLepFJTree->Branch("HGenFJdRFromLepZTrailingLepL",&HGenFJdRFromLepZTrailingLepL,"HGenFJdRFromLepZTrailingLepL/D");
    genSemiLepFJTree->Branch("HGenFJdRFromHadZFJL",&HGenFJdRFromHadZFJL,"HGenFJdRFromHadZFJL/D");


    //GenHadFJTree

    //EventReweighting
    UInt_t nLHEReweightingWeightGenHadFJL;
    std::vector<Float_t> LHEReweightingWeightGenHadFJL;

    //gen Had channel
    Double_t HGenFJdRFromZLeadFJL;
    Double_t HGenFJdRFromZTrailingFJL;

    TTree *genHadFJTree = new TTree("genHadFJTree", "genHadFJTree");



    
    
    //gen Had channel
    genHadFJTree->Branch("nLHEReweightingWeightGenHadFJL",&nLHEReweightingWeightGenHadFJL,"nLHEReweightingWeightGenHadFJL/i");
    genHadFJTree->Branch("LHEReweightingWeightGenHadFJL",&LHEReweightingWeightGenHadFJL);
    genHadFJTree->Branch("HGenFJdRFromZLeadFJL",&HGenFJdRFromZLeadFJL,"HGenFJdRFromZLeadFJL/D");
    genHadFJTree->Branch("HGenFJdRFromZTrailingFJL",&HGenFJdRFromZTrailingFJL,"HGenFJdRFromZTrailingFJL/D");



    //GenLepTree

    //EventReweighting
    UInt_t nLHEReweightingWeightGenLepL;
    std::vector<Float_t> LHEReweightingWeightGenLepL;


    //Gen dR of H reco'd (but gen matched) decay products from Z reco'd (but gen matched) decay products
    //With HTobb
    //gen lep channel
    Double_t HGendRFromLeadZLeadLepL;
    Double_t HGendRFromLeadZTrailingLepL;
    Double_t HGendRFromTrailingZLeadLepL;
    Double_t HGendRFromTrailingZTrailingLepL;

    TTree *genLepTree = new TTree("genLepTree", "genLepTree");

    //Gen dR of H reco'd (but gen matched) decay products from Z reco'd (but gen matched) decay products
    //With HTobb
    //gen lep channel
    genLepTree->Branch("nLHEReweightingWeightGenLepL",&nLHEReweightingWeightGenLepL,"nLHEReweightingWeightGenLepL/i");
    genLepTree->Branch("LHEReweightingWeightGenLepL",&LHEReweightingWeightGenLepL);
    genLepTree->Branch("HGendRFromLeadZLeadLepL",&HGendRFromLeadZLeadLepL,"HGendRFromLeadZLeadLepL/D");
    genLepTree->Branch("HGendRFromLeadZTrailingLepL",&HGendRFromLeadZTrailingLepL,"HGendRFromLeadZTrailingLepL/D");
    genLepTree->Branch("HGendRFromTrailingZLeadLepL",&HGendRFromTrailingZLeadLepL,"HGendRFromTrailingZLeadLepL/D");
    genLepTree->Branch("HGendRFromTrailingZTrailingLepL",&HGendRFromTrailingZTrailingLepL,"HGendRFromTrailingZTrailingLepL/D");



    //GenSemiLepTree

    //EventReweighting
    UInt_t nLHEReweightingWeightGenSemiLepL;
    std::vector<Float_t> LHEReweightingWeightGenSemiLepL;


    //gen Semilep channel
    Double_t HGendRFromLepZLeadLepL;
    Double_t HGendRFromLepZTrailingLepL;
    Double_t HGendRFromHadZL;
    Double_t LeadLepdRFromTrailingLepL;

    TTree *genSemiLepTree = new TTree("genSemiLepTree", "genSemiLepTree");

    //gen Semilep channel
    genSemiLepTree->Branch("nLHEReweightingWeightGenSemiLepL",&nLHEReweightingWeightGenSemiLepL,"nLHEReweightingWeightGenSemiLepL/i");
    genSemiLepTree->Branch("LHEReweightingWeightGenSemiLepL",&LHEReweightingWeightGenSemiLepL);
    genSemiLepTree->Branch("HGendRFromLepZLeadLepL",&HGendRFromLepZLeadLepL,"HGendRFromLepZLeadLepL/D");
    genSemiLepTree->Branch("HGendRFromLepZTrailingLepL",&HGendRFromLepZTrailingLepL,"HGendRFromLepZTrailingLepL/D");
    genSemiLepTree->Branch("HGendRFromHadZL",&HGendRFromHadZL,"HGendRFromHadZL/D");
    genSemiLepTree->Branch("LeadLepdRFromTrailingLepL",&LeadLepdRFromTrailingLepL,"LeadLepdRFromTrailingLepL/D");
    

    //GenHadTree

    //EventReweighting
    UInt_t nLHEReweightingWeightGenHadL;
    std::vector<Float_t> LHEReweightingWeightGenHadL;

    //gen Had channel
    Double_t HGendRFromZLeadL;
    Double_t HGendRFromZTrailingL;

    TTree *genHadTree = new TTree("genHadTree", "genHadTree");



    
    
    //gen Had channel
    genHadTree->Branch("nLHEReweightingWeightGenHadL",&nLHEReweightingWeightGenHadL,"nLHEReweightingWeightGenHadL/i");
    genHadTree->Branch("LHEReweightingWeightGenHadL",&LHEReweightingWeightGenHadL);
    genHadTree->Branch("HGendRFromZLeadL",&HGendRFromZLeadL,"HGendRFromZLeadL/D");
    genHadTree->Branch("HGendRFromZTrailingL",&HGendRFromZTrailingL,"HGendRFromZTrailingL/D");
    
    

    Double_t sumOfGenWeights = 0;


    std::vector<std::vector<Double_t>> genChannelWeightedCtrAr(11,zeroVec);

    
    //Ctrs for HTobb
    UInt_t genLepChannelCtr = 0;
    UInt_t genSemiLepChannelCtr = 0;
    UInt_t genHadronicChannelCtr = 0;
    UInt_t genOtherChannelCtr = 0;
    UInt_t genErrorChannelCtr = 0;
    /*
    Double_t genLepChannelWeightedCtr = 0;
    Double_t genSemiLepChannelWeightedCtr = 0;
    Double_t genHadronicChannelWeightedCtr = 0;
    Double_t genOtherChannelWeightedCtr = 0;
    Double_t genErrorChannelWeightedCtr = 0;
    */

    //Ctrs for no HTobb
    UInt_t genLepChannelNoHTobbCtr = 0;
    UInt_t genSemiLepChannelNoHTobbCtr = 0;
    UInt_t genHadronicChannelNoHTobbCtr = 0;
    UInt_t genOtherChannelNoHTobbCtr = 0;
    UInt_t genErrorChannelNoHTobbCtr = 0;
    /*
    Double_t genLepChannelNoHTobbWeightedCtr = 0;
    Double_t genSemiLepChannelNoHTobbWeightedCtr = 0;
    Double_t genHadronicChannelNoHTobbWeightedCtr = 0;
    Double_t genOtherChannelNoHTobbWeightedCtr = 0;
    Double_t genErrorChannelNoHTobbWeightedCtr = 0;
    */


    UInt_t HTobbCtr = 0;
    //Double_t HTobbWeightedCtr = 0;

    std::vector<std::string> typeNameAltAr {"GenLep","GenSemiLep","GenHad","GenOther","GenError","GenLep NoHTobb","GenSemiLep NoHTobb","GenHad NoHTobb","GenOther NoHTobb","GenError NoHTobb","Gen NoHTobb"};

    
    
    std::cout << "Going into file loop.\n";

    for (UInt_t k=0; k<fileAr.size(); k++){
        if (endAfter && evCount > NToEnd) break;
        if (debug) std::cout<<"File:    "<<fileAr[k]<<"\n";
        //Open the file, get the Events tree
        TFile* tmpfile = TFile::Open(fileAr[k].c_str());
        if (!tmpfile) {
            std::cerr << "Could not open " << fileAr[k] << "\n";
            std::cerr << "Moving to next file.\n";
            continue;
        }
        outFile->cd();
        TTreeReader myEventsReader("Events", tmpfile);

        //eventWeights
        TTreeReaderValue<UInt_t> nLHEReweightingWeight(myEventsReader, "nLHEReweightingWeight");
        TTreeReaderArray<Float_t> LHEReweightingWeight(myEventsReader, "LHEReweightingWeight");

        //genWeights
        TTreeReaderValue<Float_t> genWeight(myEventsReader, "genWeight");

        //LHE stuff
        TTreeReaderValue<UInt_t> nLHEPart(myEventsReader, "nLHEPart");
        TTreeReaderArray<Int_t> LHEPart_pdgId(myEventsReader, "LHEPart_pdgId");
        TTreeReaderArray<Float_t> LHEPart_pt(myEventsReader, "LHEPart_pt");

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
        TTreeReaderValue<Bool_t> HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02(myEventsReader, "HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02");
        TTreeReaderValue<Bool_t> HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2(myEventsReader, "HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2");
        TTreeReaderValue<Bool_t> HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4(myEventsReader, "HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4");
        TTreeReaderValue<Bool_t> HLT_TripleMu_10_5_5_DZ(myEventsReader, "HLT_TripleMu_10_5_5_DZ");
        TTreeReaderValue<Bool_t> HLT_TripleMu_12_10_5(myEventsReader, "HLT_TripleMu_12_10_5");


        TTreeReaderValue<Bool_t> HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ(myEventsReader, "HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ");
        TTreeReaderValue<Bool_t> HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL(myEventsReader, "HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL");
        TTreeReaderValue<Bool_t> HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ(myEventsReader, "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ");
        TTreeReaderValue<Bool_t> HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL(myEventsReader, "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL");
        TTreeReaderValue<Bool_t> HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ(myEventsReader, "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ");
        TTreeReaderValue<Bool_t> HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL(myEventsReader, "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL");

        TTreeReaderValue<Bool_t> HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8(myEventsReader, "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8");
        TTreeReaderValue<Bool_t> HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8(myEventsReader, "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8");
        TTreeReaderValue<Bool_t> HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass3p8(myEventsReader, "HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass3p8");
        TTreeReaderValue<Bool_t> HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass8(myEventsReader, "HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass8");

        TTreeReaderValue<Bool_t> HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ(myEventsReader, "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ");
        TTreeReaderValue<Bool_t> HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL(myEventsReader, "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL");
        TTreeReaderValue<Bool_t> HLT_DiEle27_WPTightCaloOnly_L1DoubleEG(myEventsReader, "HLT_DiEle27_WPTightCaloOnly_L1DoubleEG");
        TTreeReaderValue<Bool_t> HLT_DoubleEle33_CaloIdL_MW(myEventsReader, "HLT_DoubleEle33_CaloIdL_MW");
        TTreeReaderValue<Bool_t> HLT_DoubleEle25_CaloIdL_MW(myEventsReader, "HLT_DoubleEle25_CaloIdL_MW");
        TTreeReaderValue<Bool_t> HLT_DoubleEle27_CaloIdL_MW(myEventsReader, "HLT_DoubleEle27_CaloIdL_MW");
        TTreeReaderValue<Bool_t> HLT_DoublePhoton70(myEventsReader, "HLT_DoublePhoton70");

        TTreeReaderValue<Bool_t> HLT_IsoMu24(myEventsReader, "HLT_IsoMu24");
        TTreeReaderValue<Bool_t> HLT_IsoMu27(myEventsReader, "HLT_IsoMu27");
        TTreeReaderValue<Bool_t> HLT_IsoMu30(myEventsReader, "HLT_IsoMu30");
        TTreeReaderValue<Bool_t> HLT_Mu50(myEventsReader, "HLT_Mu50");

        TTreeReaderValue<Bool_t> HLT_Ele115_CaloIdVT_GsfTrkIdT(myEventsReader, "HLT_Ele115_CaloIdVT_GsfTrkIdT");
        TTreeReaderValue<Bool_t> HLT_Ele27_WPTight_Gsf(myEventsReader, "HLT_Ele27_WPTight_Gsf");
        TTreeReaderValue<Bool_t> HLT_Ele28_WPTight_Gsf(myEventsReader, "HLT_Ele28_WPTight_Gsf");
        TTreeReaderValue<Bool_t> HLT_Ele32_WPTight_Gsf(myEventsReader, "HLT_Ele32_WPTight_Gsf");
        TTreeReaderValue<Bool_t> HLT_Ele35_WPTight_Gsf(myEventsReader, "HLT_Ele35_WPTight_Gsf");
        TTreeReaderValue<Bool_t> HLT_Ele38_WPTight_Gsf(myEventsReader, "HLT_Ele38_WPTight_Gsf");
        TTreeReaderValue<Bool_t> HLT_Ele40_WPTight_Gsf(myEventsReader, "HLT_Ele40_WPTight_Gsf");
        TTreeReaderValue<Bool_t> HLT_Ele32_WPTight_Gsf_L1DoubleEG(myEventsReader, "HLT_Ele32_WPTight_Gsf_L1DoubleEG");
        TTreeReaderValue<Bool_t> HLT_Photon200(myEventsReader, "HLT_Photon200");

        TTreeReaderValue<Bool_t> HLT_AK8PFJet500(myEventsReader, "HLT_AK8PFJet500");
        TTreeReaderValue<Bool_t> HLT_AK8PFJet360_TrimMass30(myEventsReader, "HLT_AK8PFJet360_TrimMass30");
        TTreeReaderValue<Bool_t> HLT_AK8PFJet380_TrimMass30(myEventsReader, "HLT_AK8PFJet380_TrimMass30");
        TTreeReaderValue<Bool_t> HLT_AK8PFJet400_TrimMass30(myEventsReader, "HLT_AK8PFJet400_TrimMass30");
        TTreeReaderValue<Bool_t> HLT_AK8PFJet420_TrimMass30(myEventsReader, "HLT_AK8PFJet420_TrimMass30");
        TTreeReaderValue<Bool_t> HLT_AK8PFHT750_TrimMass50(myEventsReader, "HLT_AK8PFHT750_TrimMass50");
        TTreeReaderValue<Bool_t> HLT_AK8PFHT800_TrimMass50(myEventsReader, "HLT_AK8PFHT800_TrimMass50");
        TTreeReaderValue<Bool_t> HLT_AK8PFHT850_TrimMass50(myEventsReader, "HLT_AK8PFHT850_TrimMass50");
        TTreeReaderValue<Bool_t> HLT_AK8PFHT900_TrimMass50(myEventsReader, "HLT_AK8PFHT900_TrimMass50");
        TTreeReaderValue<Bool_t> HLT_PFHT1050(myEventsReader, "HLT_PFHT1050");

        //jets

        TTreeReaderValue<UInt_t> nJet(myEventsReader, "nJet");
        TTreeReaderArray<Float_t> Jet_eta(myEventsReader, "Jet_eta");
        TTreeReaderArray<Float_t> Jet_pt(myEventsReader, "Jet_pt");
        TTreeReaderArray<Float_t> Jet_phi(myEventsReader, "Jet_phi");
        TTreeReaderArray<Float_t> Jet_mass(myEventsReader, "Jet_mass");
        TTreeReaderArray<Int_t> Jet_jetId(myEventsReader, "Jet_jetId");

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
        TTreeReaderArray<Int_t> FatJet_genJetAK8Idx(myEventsReader, "FatJet_genJetAK8Idx");

        TTreeReaderArray<Int_t> FatJet_hadronFlavour(myEventsReader, "FatJet_hadronFlavour");


        //Gen part stuff

        TTreeReaderValue<UInt_t> nGenPart(myEventsReader, "nGenPart");
        TTreeReaderArray<Float_t> GenPart_eta(myEventsReader, "GenPart_eta");
        TTreeReaderArray<Float_t> GenPart_mass(myEventsReader, "GenPart_mass");
        TTreeReaderArray<Float_t> GenPart_phi(myEventsReader, "GenPart_phi");
        TTreeReaderArray<Float_t> GenPart_pt(myEventsReader, "GenPart_pt");
        TTreeReaderArray<Int_t> GenPart_genPartIdxMother(myEventsReader, "GenPart_genPartIdxMother");
        TTreeReaderArray<Int_t> GenPart_pdgId(myEventsReader, "GenPart_pdgId");
        TTreeReaderArray<Int_t> GenPart_status(myEventsReader, "GenPart_status");
        TTreeReaderArray<Int_t> GenPart_statusFlags(myEventsReader, "GenPart_statusFlags");
        
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

        TTreeReaderArray<Float_t> Jet_btagDeepFlavB(myEventsReader,"Jet_btagDeepFlavB");

        //ParticleNet
        TTreeReaderArray<Float_t> FatJet_particleNet_HbbvsQCD(myEventsReader, "FatJet_particleNet_HbbvsQCD");
        TTreeReaderArray<Float_t> FatJet_particleNet_ZvsQCD(myEventsReader, "FatJet_particleNet_ZvsQCD");
        TTreeReaderArray<Float_t> FatJet_particleNetMD_QCD(myEventsReader, "FatJet_particleNetMD_QCD");
        TTreeReaderArray<Float_t> FatJet_particleNetMD_Xbb(myEventsReader, "FatJet_particleNetMD_Xbb");
        TTreeReaderArray<Float_t> FatJet_particleNetMD_Xcc(myEventsReader, "FatJet_particleNetMD_Xcc");
        TTreeReaderArray<Float_t> FatJet_particleNetMD_Xqq(myEventsReader, "FatJet_particleNetMD_Xqq");

        //

        TTreeReaderValue<Float_t> fixedGridRhoFastjetAll(myEventsReader, "fixedGridRhoFastjetAll");

        //gen jets

        TTreeReaderValue<UInt_t> nGenJetAK8(myEventsReader, "nGenJetAK8");
        TTreeReaderArray<Float_t> GenJetAK8_eta(myEventsReader, "GenJetAK8_eta");
        TTreeReaderArray<Float_t> GenJetAK8_pt(myEventsReader, "GenJetAK8_pt");
        TTreeReaderArray<Float_t> GenJetAK8_phi(myEventsReader, "GenJetAK8_phi");
        TTreeReaderArray<UChar_t> GenJetAK8_hadronFlavour(myEventsReader, "GenJetAK8_hadronFlavour");

        



        TTreeReader myRunsReader("Runs", tmpfile);
        TTreeReaderValue<Long64_t> genEventCount(myRunsReader, "genEventCount");
        TTreeReaderValue<Double_t> genEventSumw(myRunsReader, "genEventSumw");


        //Getting the cross section
        //For background it's precalculated
        
        if (!isBackground){
            crossSection = 0.;
            Long64_t eventLoopMax = myRunsReader.GetEntries();
            UInt_t tmpRunsInt = 0;
            while (myRunsReader.Next()){
                if (debug){
                    std::cout << *genEventSumw << "\n";
                    std::cout << *genEventCount << "\n";
                }
                totCrossSectionWeight += *genEventSumw;
                totCrossSectionEvCount += *genEventCount;
                crossSection += *genEventSumw / *genEventCount;
                if (debug) std::cout << crossSection << "\n";
                crossSection = crossSection / eventLoopMax;
                if (debug) std::cout << crossSection << "\n";
                crossSectionAvg += crossSection;
                if (debug) std::cout << crossSectionAvg << "\n";
                crossSectionCtr += 1;
            }
        }
        
        if (k % 10 == 0){
            double tmpTime = (double)(clock()-startt)/CLOCKS_PER_SEC;
            std::cout << "Going into event loop for file" << k << " .\ttime:" << (double)(clock()-startt)/CLOCKS_PER_SEC << "\n";
        }


        //EvLoop
        while (myEventsReader.Next()) {
            
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
                std::cout << evCount+1 << " starting jets loop\n";
            }
            //Increment event count
            evRunOver += 1;
            evCount += 1;

            sumOfGenWeights += *genWeight;
            genChannelL = 4;
            HTobbBoolL = false;
            std::vector<Bool_t> evWeightedCtrMaskOne(9,false);
            evWeightedCtrMaskOne[0] = true;
            std::vector<Bool_t> evWeightedCtrMaskTwo(11,false);

            //--------------KINEMATICS--------------

            UInt_t tmpnFatJets = *nFatJet;
            
            int ZOneDecLeadInd = -1;
            int ZOneDecTrailingInd = -1;
            int ZTwoDecLeadInd = -1;
            int ZTwoDecTrailingInd = -1;
            
            bool ZIsLeptonic = false;
            bool ZIsSemiLeptonic = false;
            bool ZIsHadronic = false;

            ZFJIndL = -1;
            HFJIndL = -1;
            goodGenZFJMatchL = false;
            goodGenHFJMatchL = false;
            eventGenSemileptonicL = false;

            if (!isBackground){

                float JOne_pdgId_FromLHERaw;
                float JTwo_pdgId_FromLHERaw;

                UInt_t lenLHEPart = *nLHEPart;
                Int_t tmpZCtr = 0;
                Int_t tmpHCtr = 0;
                Int_t tmpJCtr = 0;
                Int_t tmpHInd = -1;
                std::vector<UInt_t>tmpJAr;
                Int_t tmpPDGId = 0;
                for (UInt_t LHEItr=0; LHEItr<lenLHEPart;LHEItr++){
                    tmpPDGId = LHEPart_pdgId[LHEItr];
                    if (tmpPDGId == 23){
                        tmpZCtr += 1;
                        if (tmpZCtr > 2) std::cout << "ERROR MORE THAN 2 Zs IN LHE\n";
                    }
                    else if (tmpPDGId == 25){
                        tmpHCtr += 1;
                        if (tmpHCtr > 1) std::cout << "ERROR MORE THAN 1 H IN LHE\n";
                        else tmpHInd = LHEItr;
                    }
                    else if (tmpPDGId >= -8 && tmpPDGId <= 8){
                        tmpJCtr += 1;
                        if (tmpJCtr > 4) std::cout << "ERROR MORE THAN 4 Qs IN LHE\n";
                        else if (tmpJCtr > 2) tmpJAr.push_back(LHEItr);
                    }
                    else std::cout << "ERROR UNKNOWN PARTICLE " << tmpPDGId << " IN LHE\n";
                }
                if (tmpZCtr == 2 && tmpHCtr == 1 && tmpJCtr == 4 && tmpJAr.size() == 2){
                    
                    
                    float tmpLHEPartPtOne = LHEPart_pt[tmpJAr[0]];
                    float tmpLHEPartPtTwo = LHEPart_pt[tmpJAr[1]];

                    if (tmpLHEPartPtOne >= tmpLHEPartPtTwo) {
                        JOne_pdgId_FromLHERaw = LHEPart_pdgId[tmpJAr[0]];
                        JTwo_pdgId_FromLHERaw = LHEPart_pdgId[tmpJAr[1]];
                    }
                    else{
                        JOne_pdgId_FromLHERaw = LHEPart_pdgId[tmpJAr[1]];
                        JTwo_pdgId_FromLHERaw = LHEPart_pdgId[tmpJAr[0]];

                    }
                }



                std::vector<Int_t> HFJ_decaypdgId_FromGenMatch;

                

                bool ZOneIsLeptonic = false;
                bool ZOneIsHadronic = false;

                bool ZTwoIsLeptonic = false;
                bool ZTwoIsHadronic = false;

                std::vector<std::vector<Int_t>> tmpHAr;
                std::vector<std::vector<Int_t>> tmpZAr;
                std::vector<std::vector<Int_t>> tmpZDaughterIndAr;


                //std::vector<Int_t> tmpZFJAr;
                //Usually should be straightforward 2Z 1H 2J
                //however, sometimes there are intermediary particles on the way to that in the gen that aren't in the LHE
                //Some situations:
                //Starting with 1Z 2H 0J
                //Leads to H->JJZ
                //can also have normal start but H->ZX (X can be gamma or another Z)
                //check starting particles by looking at what has the status 4481.
                //These will bounce around with status 257 until they get status 10497 (indicates "isLastCopy" bit)
                //or with H sometimes status 26881 (includes "isLastCopyBeforeFSR" bit)


                bool HFound = false;
                //std::vector<Int_t> HToZIndVec;
                std::vector<bool> HToZBoolVec;
                std::vector<Int_t> isInHDecChainVec;
                
                for (UInt_t i=0;i<*nGenPart;i++){
                    Int_t tmpPDGId = GenPart_pdgId[i];
                    Int_t tmpMotherID = GenPart_genPartIdxMother[i];
                    if (debugGenPart) std::cout << "i " << i << " GenPart_pdgId[i] " << tmpPDGId << "\n";
                    bool isHDecay = false;
                    if (isInHDecChainVec.size()){
                        if (std::count(isInHDecChainVec.begin(), isInHDecChainVec.end(), tmpMotherID)) {
                            isHDecay = true;
                            isInHDecChainVec.push_back(i);

                        }
                    }

                    if (tmpHAr.size()){
                        for (UInt_t tmpHItr=0;tmpHItr<tmpHAr.size();tmpHItr++){
                            if (debugGenPart) std::cout << "tmpHItr " << tmpHItr << " tmpMotherID " << tmpMotherID << "\n";
                            if (tmpMotherID == tmpHAr[tmpHItr][0]){
                                if (tmpPDGId == 25) std::cout <<"ERROR, ERROR, DAUGHTER PARTICLE IS H\n";
                                else {
                                    tmpHAr[tmpHItr].push_back(tmpPDGId);
                                    isHDecay = true;
                                    isInHDecChainVec.push_back(i);
                                    if (debugGenPart){
                                        std::cout << "Checking if pdg id == 23. pdgid " << tmpPDGId << " tmpZAr.size() " << tmpZAr.size() << "\n";
                                    }
                                    if (tmpPDGId == 23 && tmpZAr.size() <=1) {
                                        //HToZIndVec.push_back(i)
                                        HToZBoolVec[tmpHItr] =true;
                                    }
                                }
                            }
                        }
                    }

                    if (GenPart_pdgId[i] == 25){
                        //std::bitset<sizeof(Int_t)> tmpStatusBitSet;
                        //bool tmpStatusBin = tmpStatusBitSet(GenPart_statusFlags[i]).test(13);
                        bool tmpStatusBin = GenPart_statusFlags[i] & (1 << 13);
                        //tmpStatusBin = bin(GenPart_statusFlags[i]);
                        if (debugGenPart) std::cout <<"GenPart_statusFlags[i] " << GenPart_statusFlags[i] << " tmpStatusBin " << tmpStatusBin << "\n";
                        
                        //tmpIsEnd = tmpStatusBin[-14];
                        std::vector<Int_t> tmpHFJVec;
                        tmpHFJVec.push_back(i);                            
                        if (tmpStatusBin) {
                            tmpHAr.push_back(tmpHFJVec);
                            HToZBoolVec.push_back(false);
                        }
                    }
                    
                    if (tmpZAr.size()){
                        for (UInt_t tmpZItr=0;tmpZItr<tmpZAr.size();tmpZItr++){
                            if (debugGenPart) std::cout << "tmpZItr " << tmpZItr << " tmpMotherID " << tmpMotherID << "\n";
                            if (tmpMotherID == tmpZAr[tmpZItr][0]){
                                if (tmpPDGId == 23) std::cout <<"ERROR, ERROR, DAUGHTER PARTICLE IS Z\n";
                                else {
                                    tmpZAr[tmpZItr].push_back(tmpPDGId);
                                    tmpZDaughterIndAr[tmpZItr].push_back(i);
                                }
                            }
                        }
                    }
                    
                    if (GenPart_pdgId[i] == 23){
                        //std::bitset<sizeof(Int_t)> tmpStatusBitSet;
                        //bool tmpStatusBin = tmpStatusBitSet(GenPart_statusFlags[i]).test(13);
                        bool tmpStatusBin = GenPart_statusFlags[i] & (1 << 13);
                        //tmpStatusBin = bin(GenPart_statusFlags[i]);
                        if (debugGenPart) std::cout <<"GenPart_statusFlags[i] " << GenPart_statusFlags[i] << " tmpStatusBin " << tmpStatusBin << " tmpZAr.size() " << tmpZAr.size() << " isHDecay " << isHDecay << "\n";
                        
                        //tmpIsEnd = tmpStatusBin[-14];
                        std::vector<Int_t> tmpZFJVec;
                        tmpZFJVec.push_back(i);
                        std::vector<Int_t> tmpZOneDaughterVec;
                        
                        if (tmpZAr.size()<=1 || !isHDecay){
                            if (tmpStatusBin) {
                                tmpZAr.push_back(tmpZFJVec);
                                tmpZDaughterIndAr.push_back(tmpZOneDaughterVec);
                            }
                        }

                    }
                }
                if (debugGenPart) {
                    std::cout <<"Finished H,Z Finding. tmpHAr:\n";
                    if (tmpHAr.size()){
                        for (UInt_t tmpHItr=0;tmpHItr<tmpHAr.size();tmpHItr++){
                            for (UInt_t tmpHItrTwo=0;tmpHItrTwo<tmpHAr[tmpHItr].size();tmpHItrTwo++){
                                std::cout << tmpHAr[tmpHItr][tmpHItrTwo] << ", ";
                            }
                            std::cout << "\n";
                        }
                    }
                    std::cout <<"HToZBoolVec:\n";
                    if (HToZBoolVec.size()){
                        for (UInt_t tmpHItr=0;tmpHItr<HToZBoolVec.size();tmpHItr++){
                            std::cout << HToZBoolVec[tmpHItr] << ", ";
                        }
                        std::cout << "\n";
                    }
                    std::cout <<"tmpZAr:\n";
                    if (tmpZAr.size()){
                        for (UInt_t tmpZItr=0;tmpZItr<tmpZAr.size();tmpZItr++){
                            for (UInt_t tmpZItrTwo=0;tmpZItrTwo<tmpZAr[tmpZItr].size();tmpZItrTwo++){
                                std::cout << tmpZAr[tmpZItr][tmpZItrTwo] << ", ";
                            }
                            std::cout << "\n";
                        }
                    }
                }

                std::vector<Int_t> tmpHFinalAr;
                Int_t intermediaryH = -1;
                if (tmpHAr.size() >= 2){
                    for (UInt_t tmpHItr=0;tmpHItr<tmpHAr.size();tmpHItr++){
                        if (std::count(tmpHAr[tmpHItr].begin(), tmpHAr[tmpHItr].end(), JOne_pdgId_FromLHERaw)){
                            if (std::count(tmpHAr[tmpHItr].begin(), tmpHAr[tmpHItr].end(), JTwo_pdgId_FromLHERaw)){
                                if (tmpHAr[tmpHItr].size() == 3){
                                    intermediaryH = tmpHItr;
                                    break;
                                }
                            }
                        }
                        if (std::count(tmpHAr[tmpHItr].begin(), tmpHAr[tmpHItr].end(), 23) && HToZBoolVec[tmpHItr]){
                            intermediaryH = tmpHItr;
                            break;
                        }
                    }
                }
                std::vector<Int_t> finalHAr;

                if (tmpHAr.size()){
                    for (UInt_t tmpHItr=0;tmpHItr<tmpHAr.size();tmpHItr++){
                        if (tmpHItr != intermediaryH) {
                            finalHAr.push_back(tmpHAr[tmpHItr][0]);
                            //Looping through array for decay branches
                            for (UInt_t tmpHDecItr=1;tmpHDecItr<tmpHAr[tmpHItr].size();tmpHDecItr++){
                                HFJ_decaypdgId_FromGenMatch.push_back(tmpHAr[tmpHItr][tmpHDecItr]);
                            }
                        }
                    }
                }


                
                
                if (finalHAr.size() != 1) {
                    std::cout <<"ERROR ERROR, MORE OR LESS THAN ONE H,evCount,JOne_pdgId_FromLHERaw,JTwo_pdgId_FromLHERaw " << evCount-1<< " " <<JOne_pdgId_FromLHERaw<< " " <<JTwo_pdgId_FromLHERaw << "\n";
                    genChannelL = 4;
                    genErrorChannelCtr += 1;
                    evWeightedCtrMaskTwo[4] = true;

                }
                else{
                    if (debugGenPart) std::cout <<"H found\n";
                    if (abs(HFJ_decaypdgId_FromGenMatch[0]) == 5){
                        HTobbBoolL = true;
                        HTobbCtr += 1;
                        //HTobbWeightedCtr += *genWeight;
                    }
                    Int_t intermediaryZ = -1;
                    
                    if (tmpZAr.size() >= 3){
                        //if (evCount -1 == 407) std::cout << "yes\n";
                        for (UInt_t tmpZItr=0;tmpZItr<tmpZAr.size();tmpZItr++){
                            //if (evCount -1 == 407) std::cout << "yes\n";
                            if (std::count(tmpZAr[tmpZItr].begin(), tmpZAr[tmpZItr].end(), JOne_pdgId_FromLHERaw)){
                                //if (evCount -1 == 407) std::cout << "yes\n";
                                if (std::count(tmpZAr[tmpZItr].begin(), tmpZAr[tmpZItr].end(), JTwo_pdgId_FromLHERaw)){
                                    //if (evCount -1 == 407) std::cout << "yes\n";
                                    if (tmpZAr[tmpZItr].size() == 3){
                                        //if (evCount -1 == 407) std::cout << "yes\n";
                                        intermediaryZ = tmpZItr;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    std::vector<Int_t> finalZAr;
                    std::vector<std::vector<Int_t>> finalZDecAr;
                    std::vector<std::vector<Int_t>> finalZDecIndAr;
                    bool ZDecFound = false;


                    if (tmpZAr.size()){
                        for (UInt_t tmpZItr=0;tmpZItr<tmpZAr.size();tmpZItr++){
                            if (tmpZItr != intermediaryZ){
                                finalZAr.push_back(tmpZAr[tmpZItr][0]);
                                //Looping through array for decay branches
                                
                                
                                if (tmpZAr[tmpZItr].size() != 3) {
                                    std::cout << "ERROR ERROR tmpZAr INTERNAL VEC SIZE NOT == 3. INSTEAD SIZE == " << tmpZAr[tmpZItr].size() << "\n";
                                    for (UInt_t tmpZDecItr=0;tmpZDecItr<tmpZAr[tmpZItr].size();tmpZDecItr++){
                                        std::cout << tmpZAr[tmpZItr][tmpZDecItr] << " ";
                                    }
                                    std::cout << "\n";
                                }
                                else {
                                    ZDecFound = true;
                                    std::vector<Int_t> tmpZDecVec;
                                    tmpZDecVec.push_back(tmpZAr[tmpZItr][1]);
                                    tmpZDecVec.push_back(tmpZAr[tmpZItr][2]);
                                    finalZDecAr.push_back(tmpZDecVec);
                                    std::vector<Int_t> tmpZDecIndVec;
                                    tmpZDecIndVec.push_back(tmpZDaughterIndAr[tmpZItr][0]);
                                    tmpZDecIndVec.push_back(tmpZDaughterIndAr[tmpZItr][1]);
                                    finalZDecIndAr.push_back(tmpZDecIndVec);
                                    

                                }
                            }
                        }
                    }

                    if (finalZAr.size() != 2){
                        std::cout <<"ERROR ERROR, MORE OR LESS THAN TWO Zs,evCount,finalZAr.size(),intermediaryZ,JOne_pdgId_FromLHERaw,JTwo_pdgId_FromLHERaw " << evCount-1<< " " << finalZAr.size() << " " << intermediaryZ << " "<<JOne_pdgId_FromLHERaw<< " " <<JTwo_pdgId_FromLHERaw << "\n";
                        if (tmpZAr.size()){
                            for (UInt_t tmpZItr=0;tmpZItr<tmpZAr.size();tmpZItr++){
                                for (UInt_t tmpZItrTwo=0;tmpZItrTwo<tmpZAr[tmpZItr].size();tmpZItrTwo++){
                                    std::cout <<"tmpZItr " << tmpZItr << " tmpZItrTwo " << tmpZItrTwo << " tmpZAr[tmpZItr][tmpZItrTwo] " << tmpZAr[tmpZItr][tmpZItrTwo] << "\n";
                                }
                            }
                        }
                        if (finalZAr.size()){
                            for (UInt_t tmpZItr=0;tmpZItr<finalZAr.size();tmpZItr++){
                                std::cout << "finalZAr[tmpZItr] " << finalZAr[tmpZItr] << "\n";
                            }
                        }
                        genChannelL = 4;
                        if (HTobbBoolL){
                            genErrorChannelCtr += 1;
                            //genErrorChannelWeightedCtr += *genWeight;
                            evWeightedCtrMaskTwo[4] = true;
                        }
                        else{
                            genErrorChannelNoHTobbCtr += 1;
                            //genErrorChannelNoHTobbWeightedCtr += *genWeight;
                            evWeightedCtrMaskTwo[9] = true;
                        }

                    }
                    else{
                        
                        if (ZDecFound) {
                            if (GenPart_pt[finalZDecIndAr[0][0]] > GenPart_pt[finalZDecIndAr[0][1]]){
                                ZOneDecLeadInd = finalZDecIndAr[0][0];
                                ZOneDecTrailingInd = finalZDecIndAr[0][1];
                            }
                            else{
                                ZOneDecLeadInd = finalZDecIndAr[0][1];
                                ZOneDecTrailingInd = finalZDecIndAr[0][0];
                            }
                            if (GenPart_pt[finalZDecIndAr[1][0]] > GenPart_pt[finalZDecIndAr[1][1]]){
                                ZTwoDecLeadInd = finalZDecIndAr[1][0];
                                ZTwoDecTrailingInd = finalZDecIndAr[1][1];
                            }
                            else{
                                ZTwoDecLeadInd = finalZDecIndAr[1][1];
                                ZTwoDecTrailingInd = finalZDecIndAr[1][0];
                            }
                                
                            //std::cout << evCount << " " << finalZDecAr[0][0]<< " " << finalZDecAr[0][1] << " " << finalZDecAr[1][0] << " " << finalZDecAr[1][1] << "\n";
                            if (abs(finalZDecAr[0][0])==15 && abs(finalZDecAr[0][1])==15){
                                int tmpLepOneInd = -1;
                                int tmpLepTwoInd = -1;
                                std::vector<Int_t> tauOneAr;
                                std::vector<Int_t> tauTwoAr;
                                bool tauOneBool = false;
                                bool tauTwoBool = false;
                                UInt_t tauOneDecPDG = 0;
                                UInt_t tauTwoDecPDG = 0;
                                tauOneAr.push_back(finalZDecIndAr[0][0]);
                                tauTwoAr.push_back(finalZDecIndAr[0][1]);
                                for (UInt_t i=0;i<*nGenPart;i++){
                                    Int_t tmpPDGId = GenPart_pdgId[i];
                                    Int_t tmpMotherID = GenPart_genPartIdxMother[i];
                                    
                                    std::vector<Int_t> tmpOneIndAr;
                                    if (!tauOneBool){
                                        for (UInt_t j=0;j<tauOneAr.size();j++){
                                            if (tmpMotherID == tauOneAr[j]){
                                                if (abs(tmpPDGId) == 15) tmpOneIndAr.push_back(i);
                                                else if (abs(tmpPDGId) == 13 || abs(tmpPDGId) == 11) {
                                                    tauOneBool = true;
                                                    tauOneDecPDG = abs(tmpPDGId);
                                                    tmpLepOneInd = i;
                                                }
                                            }
                                        }
                                        if (tmpOneIndAr.size()) {
                                            for (UInt_t j=0;j<tmpOneIndAr.size();j++){
                                                tauOneAr.push_back(tmpOneIndAr[j]);
                                            }
                                        }
                                    }
                                    std::vector<Int_t> tmpTwoIndAr;
                                    if (!tauTwoBool){
                                        for (UInt_t j=0;j<tauTwoAr.size();j++){
                                            if (tmpMotherID == tauTwoAr[j]){
                                                if (abs(tmpPDGId) == 15) tmpTwoIndAr.push_back(i);
                                                else if (abs(tmpPDGId) == 13 || abs(tmpPDGId) == 11) {
                                                    tauTwoBool = true;
                                                    tauTwoDecPDG = abs(tmpPDGId);
                                                    tmpLepTwoInd = i;
                                                }
                                            }
                                        }
                                        if (tmpTwoIndAr.size()) {
                                            for (UInt_t j=0;j<tmpTwoIndAr.size();j++){
                                                tauTwoAr.push_back(tmpTwoIndAr[j]);
                                            }
                                        }
                                    }
                                }
                                if (tauOneBool && tauTwoBool && tauOneDecPDG == tauTwoDecPDG) {
                                    ZOneIsLeptonic = true;
                                    if (GenPart_pt[tmpLepOneInd] > GenPart_pt[tmpLepTwoInd]){
                                        ZOneDecLeadInd = tmpLepOneInd;
                                        ZOneDecTrailingInd = tmpLepTwoInd;
                                    }
                                    else {
                                        ZOneDecLeadInd = tmpLepTwoInd;
                                        ZOneDecTrailingInd = tmpLepOneInd;
                                    }
                                }
                            }
                            if (abs(finalZDecAr[1][0])==15 && abs(finalZDecAr[1][1])==15){
                                int tmpLepOneInd = -1;
                                int tmpLepTwoInd = -1;
                                std::vector<Int_t> tauOneAr;
                                std::vector<Int_t> tauTwoAr;
                                bool tauOneBool = false;
                                bool tauTwoBool = false;
                                UInt_t tauOneDecPDG = 0;
                                UInt_t tauTwoDecPDG = 0;
                                tauOneAr.push_back(finalZDecIndAr[1][0]);
                                tauTwoAr.push_back(finalZDecIndAr[1][1]);
                                //std::cout << "Entering GenPart loop " << tauOneAr[0]<< " " << tauTwoAr[0] << "\n";
                                for (UInt_t i=0;i<*nGenPart;i++){
                                    Int_t tmpPDGId = GenPart_pdgId[i];
                                    Int_t tmpMotherID = GenPart_genPartIdxMother[i];
                                    
                                    std::vector<Int_t> tmpOneIndAr;
                                    //std::cout << "i " << i << " " << tmpPDGId<< " " << tmpMotherID << "\n";
                                    if (!tauOneBool){
                                        for (UInt_t j=0;j<tauOneAr.size();j++){
                                            //std::cout << "t1j " << j << " " << tauOneAr[j]<<"\n";
                                            if (tmpMotherID == tauOneAr[j]){
                                                if (abs(tmpPDGId) == 15) tmpOneIndAr.push_back(i);
                                                else if (abs(tmpPDGId) == 13 || abs(tmpPDGId) == 11) {
                                                    tauOneBool = true;
                                                    tauOneDecPDG = abs(tmpPDGId);
                                                    tmpLepOneInd = i;
                                                }
                                            }
                                        }
                                        if (tmpOneIndAr.size()) {
                                            for (UInt_t j=0;j<tmpOneIndAr.size();j++){
                                                tauOneAr.push_back(tmpOneIndAr[j]);
                                            }
                                        }
                                    }
                                    std::vector<Int_t> tmpTwoIndAr;
                                    if (!tauTwoBool){
                                        for (UInt_t j=0;j<tauTwoAr.size();j++){
                                            //std::cout << "t2j " << j << " " << tauTwoAr[j]<<"\n";
                                            if (tmpMotherID == tauTwoAr[j]){
                                                
                                                if (abs(tmpPDGId) == 15) tmpTwoIndAr.push_back(i);
                                                else if (abs(tmpPDGId) == 13 || abs(tmpPDGId) == 11) {
                                                    tauTwoBool = true;
                                                    tauTwoDecPDG = abs(tmpPDGId);
                                                    tmpLepTwoInd = i;
                                                }
                                            }
                                        }
                                        if (tmpTwoIndAr.size()) {
                                            for (UInt_t j=0;j<tmpTwoIndAr.size();j++){
                                                tauTwoAr.push_back(tmpTwoIndAr[j]);
                                            }
                                        }
                                    }
                                }
                                //std::cout << "tbool " << tauOneBool << " " << tauTwoBool <<"\n";
                                if (tauOneBool && tauTwoBool && tauOneDecPDG == tauTwoDecPDG) {
                                    ZTwoIsLeptonic = true;
                                    if (GenPart_pt[tmpLepOneInd] > GenPart_pt[tmpLepTwoInd]){
                                        ZTwoDecLeadInd = tmpLepOneInd;
                                        ZTwoDecTrailingInd = tmpLepTwoInd;
                                    }
                                    else {
                                        ZTwoDecLeadInd = tmpLepTwoInd;
                                        ZTwoDecTrailingInd = tmpLepOneInd;
                                    }
                                }
                            }

                            if (debugGenPart) std::cout << "finalZDecAr[0][0] " << finalZDecAr[0][0] << " finalZDecAr[0][1] " << finalZDecAr[0][1] << " finalZDecAr[1][0] " << finalZDecAr[1][0] << " finalZDecAr[1][1] " << finalZDecAr[1][1] << "\n";
                            ZOneIsHadronic = (finalZDecAr[0][0]>-9 && finalZDecAr[0][0]<9 && finalZDecAr[0][1]>-9 && finalZDecAr[0][1]<9);
                            ZTwoIsHadronic = (finalZDecAr[1][0]>-9 && finalZDecAr[1][0]<9 && finalZDecAr[1][1]>-9 && finalZDecAr[1][1]<9);
                            if (!ZOneIsLeptonic) ZOneIsLeptonic = ((abs(finalZDecAr[0][0])==11 || abs(finalZDecAr[0][0])==13) && (abs(finalZDecAr[0][1])==11 || abs(finalZDecAr[0][1])==13));
                            if (!ZTwoIsLeptonic) ZTwoIsLeptonic = ((abs(finalZDecAr[1][0])==11 || abs(finalZDecAr[1][0])==13) && (abs(finalZDecAr[1][1])==11 || abs(finalZDecAr[1][1])==13));
                            if (ZOneIsLeptonic && ZTwoIsLeptonic) ZIsLeptonic = true;
                            else if ((ZOneIsLeptonic && ZTwoIsHadronic) || (ZOneIsHadronic && ZTwoIsLeptonic)) ZIsSemiLeptonic = true;
                            else if (ZOneIsHadronic && ZTwoIsHadronic) ZIsHadronic = true;
                            
                            if (debugGenPart) std::cout << "ZIsHadronic " << ZIsHadronic << "ZIsLeptonic" << ZIsLeptonic << "ZIsSemiLeptonic" << ZIsSemiLeptonic << "\n";
                            float tmpHEtaFordR = GenPart_eta[finalHAr[0]];
                            float tmpHPhiFordR = GenPart_phi[finalHAr[0]];
                            float tmpZLeadEtaFordR;
                            float tmpZLeadPhiFordR;
                            
                            float  tmpZTrailingEtaFordR;
                            float  tmpZTrailingPhiFordR;
                            //std::cout << finalZAr[0] << " " << finalZAr[1] << "\n";
                            //std::cout << GenPart_pt[finalZAr[0]] << " " << GenPart_pt[finalZAr[1]] << "\n";
                            if (GenPart_pt[finalZAr[0]] > GenPart_pt[finalZAr[1]]){
                                tmpZLeadEtaFordR = GenPart_eta[finalZAr[0]];
                                tmpZLeadPhiFordR = GenPart_phi[finalZAr[0]];
                                tmpZTrailingEtaFordR = GenPart_eta[finalZAr[1]];
                                tmpZTrailingPhiFordR = GenPart_phi[finalZAr[1]];

                            }
                            else {
                                tmpZLeadEtaFordR = GenPart_eta[finalZAr[1]];
                                tmpZLeadPhiFordR = GenPart_phi[finalZAr[1]];
                                tmpZTrailingEtaFordR = GenPart_eta[finalZAr[0]];
                                tmpZTrailingPhiFordR = GenPart_phi[finalZAr[0]];

                            }
                            HdRFromLeadZL = calcDeltaR(tmpHPhiFordR,tmpHEtaFordR,tmpZLeadPhiFordR,tmpZLeadEtaFordR);
                            HdRFromTrailingZL = calcDeltaR(tmpHPhiFordR,tmpHEtaFordR,tmpZTrailingPhiFordR,tmpZTrailingEtaFordR);
                            LeadZdRFromTrailingZL = calcDeltaR(tmpZLeadPhiFordR,tmpZLeadEtaFordR,tmpZTrailingPhiFordR,tmpZTrailingEtaFordR);

                            
                            nLHEReweightingWeightGenL = *nLHEReweightingWeight;
                            for (UInt_t nReweightItr=0; nReweightItr<nLHEReweightingWeightGenL;nReweightItr++){
                                LHEReweightingWeightGenL.push_back(LHEReweightingWeight[nReweightItr]);
                            }

                            genTree->Fill();

                            LHEReweightingWeightGenL.clear();



                            
                        }
                        

                        if (ZIsHadronic) {

                            genChannelL=2;
                            if (HTobbBoolL){
                                genHadronicChannelCtr += 1;
                                //genHadronicChannelWeightedCtr += *genWeight;





                                
                                //Filling genHaddR tree
                                
                                float tmpHEta = GenPart_eta[finalHAr[0]];
                                float tmpHPhi = GenPart_phi[finalHAr[0]];
                                

                                int ZLeadInd;
                                int ZTrailingInd;
                                float tmpZOnePt = GenPart_pt[finalZAr[0]];
                                float tmpZTwoPt = GenPart_pt[finalZAr[1]];
                                if (tmpZOnePt > tmpZTwoPt){
                                    ZLeadInd = finalZAr[0];
                                    ZTrailingInd = finalZAr[1];
                                }
                                else{
                                    ZLeadInd = finalZAr[1];
                                    ZTrailingInd = finalZAr[0];
                                }

                                float tmpZLeadEta = GenPart_eta[ZLeadInd];
                                float tmpZLeadPhi = GenPart_phi[ZLeadInd];
                                float tmpZTrailingEta = GenPart_eta[ZTrailingInd];
                                float tmpZTrailingPhi = GenPart_phi[ZTrailingInd];

                                float tmpHZLeaddR = calcDeltaR(tmpHPhi,tmpHEta,tmpZLeadPhi,tmpZLeadEta);
                                float tmpHZTrailingdR = calcDeltaR(tmpHPhi,tmpHEta,tmpZTrailingPhi,tmpZTrailingEta);

                                HGendRFromZLeadL = tmpHZLeaddR;
                                HGendRFromZTrailingL = tmpHZTrailingdR;

                                nLHEReweightingWeightGenHadL = *nLHEReweightingWeight;
                                for (UInt_t nReweightItr=0; nReweightItr<nLHEReweightingWeightGenHadL;nReweightItr++){
                                    LHEReweightingWeightGenHadL.push_back(LHEReweightingWeight[nReweightItr]);
                                }

                                genHadTree->Fill();

                                LHEReweightingWeightGenHadL.clear();


                                




                                //Finding H FatJet
                                float tmpHToFJMindR = 1000.;
                                int HFJInd = -1;
                                float HFJEta = 0;
                                float HFJPhi = 0;

                                //std::cout << evCount << " entering H FJ loop\n";
                                //std::cout << tmpHEta << " " << tmpHPhi << "\n";


                                for (UInt_t fatJetInd=0;fatJetInd<tmpnFatJets;fatJetInd++){
                                    float tmpHFJEta = FatJet_eta[fatJetInd];
                                    float tmpHFJPhi = FatJet_phi[fatJetInd];
                                    float tmpDeltaR = calcDeltaR(tmpHFJPhi,tmpHFJEta,tmpHPhi,tmpHEta);
                                    //std::cout << fatJetInd << " " <<  tmpHFJEta << " " << tmpHFJPhi << " " << tmpDeltaR << "\n";
                                    if (tmpDeltaR < maxdRCut && tmpDeltaR < tmpHToFJMindR) {
                                        HFJInd = fatJetInd;
                                        tmpHToFJMindR = tmpDeltaR;
                                        HFJEta = tmpHFJEta;
                                        HFJPhi = tmpHFJPhi;
                                    }
                                    
                                }

                                //Finding ZLead FatJet
                                


                                
                                float tmpZLeadToFJMindR = 1000.;
                                int ZLeadFJInd = -1;
                                float ZLeadFJEta = 0;
                                float ZLeadFJPhi = 0;
                                float ZLeadFJPt = 0;

                                //std::cout << evCount << " entering Z Lead FJ loop\n";
                                //std::cout << tmpZLeadEta << " " << tmpZLeadPhi << "\n";

                                for (UInt_t fatJetInd=0;fatJetInd<tmpnFatJets;fatJetInd++){
                                    if (fatJetInd == HFJInd) continue;
                                    float tmpZFJEta = FatJet_eta[fatJetInd];
                                    float tmpZFJPhi = FatJet_phi[fatJetInd];
                                    float tmpDeltaR = calcDeltaR(tmpZFJPhi,tmpZFJEta,tmpZLeadPhi,tmpZLeadEta);
                                    //std::cout << fatJetInd << " " <<  tmpZFJEta << " " << tmpZFJPhi << " " << tmpDeltaR << "\n";
                                    if (tmpDeltaR < maxdRCut && tmpDeltaR < tmpZLeadToFJMindR) {
                                        ZLeadFJInd = fatJetInd;
                                        tmpZLeadToFJMindR = tmpDeltaR;
                                        ZLeadFJEta = tmpZFJEta;
                                        ZLeadFJPhi = tmpZFJPhi;
                                    }
                                    
                                }



                                //Finding ZTrailing FatJet
                                
                                float tmpZTrailingToFJMindR = 1000.;
                                int ZTrailingFJInd = -1;
                                float ZTrailingFJEta = 0;
                                float ZTrailingFJPhi = 0;
                                float ZTrailingFJPt = 0;

                                //std::cout << evCount << " entering Z Trailing FJ loop\n";
                                //std::cout << tmpZTrailingEta << " " << tmpZTrailingPhi << "\n";

                                for (UInt_t fatJetInd=0;fatJetInd<tmpnFatJets;fatJetInd++){
                                    if (fatJetInd == HFJInd || fatJetInd == ZLeadFJInd) continue;
                                    float tmpZFJEta = FatJet_eta[fatJetInd];
                                    float tmpZFJPhi = FatJet_phi[fatJetInd];
                                    float tmpDeltaR = calcDeltaR(tmpZFJPhi,tmpZFJEta,tmpZTrailingPhi,tmpZTrailingEta);
                                    //std::cout << fatJetInd << " " <<  tmpZFJEta << " " << tmpZFJPhi << " " << tmpDeltaR << "\n";
                                    if (tmpDeltaR < maxdRCut && tmpDeltaR < tmpZTrailingToFJMindR) {
                                        ZTrailingFJInd = fatJetInd;
                                        tmpZTrailingToFJMindR = tmpDeltaR;
                                        ZTrailingFJEta = tmpZFJEta;
                                        ZTrailingFJPhi = tmpZFJPhi;
                                    }
                                    
                                }
                                if (HFJInd != -1 && ZLeadFJInd != -1 && ZTrailingFJInd != -1){

                                    //std::cout << "PASSES!\n";
                                    float tmpHZLeaddR = calcDeltaR(HFJPhi,HFJEta,ZLeadFJPhi,ZLeadFJEta);
                                    float tmpHZTrailingdR = calcDeltaR(HFJPhi,HFJEta,ZTrailingFJPhi,ZTrailingFJEta);

                                    HGenFJdRFromZLeadFJL = tmpHZLeaddR;
                                    HGenFJdRFromZTrailingFJL = tmpHZTrailingdR;


                                    nLHEReweightingWeightGenHadFJL = *nLHEReweightingWeight;
                                    for (UInt_t nReweightItr=0; nReweightItr<nLHEReweightingWeightGenHadFJL;nReweightItr++){
                                        LHEReweightingWeightGenHadFJL.push_back(LHEReweightingWeight[nReweightItr]);
                                    }

                                    genHadFJTree->Fill();


                                    LHEReweightingWeightGenHadFJL.clear();
                                }
                                //std::cout << "------------------------------------------------\n";





                            }
                            else{
                                genHadronicChannelNoHTobbCtr += 1;
                                //genHadronicChannelNoHTobbWeightedCtr += *genWeight;
                            }

                        }

                        else if (ZIsSemiLeptonic) {

                            eventGenSemileptonicL = true;

                            genChannelL=1;
                            if (HTobbBoolL){
                                genSemiLepChannelCtr += 1;
                                //genSemiLepChannelWeightedCtr += *genWeight;
                                //std::cout << evCount << "\n";



                                //Filling genSemiLepdR tree
                                float tmpHEta = GenPart_eta[finalHAr[0]];
                                float tmpHPhi = GenPart_phi[finalHAr[0]];

                                int ZHadInd;
                                if (ZOneIsHadronic) {
                                    ZHadInd = finalZAr[0];

                                }
                                else if (ZTwoIsHadronic) {
                                    ZHadInd = finalZAr[1];
                                }
                                else {
                                    std::cout <<"ERROR ERROR, CHANNEL TYPE MIXUP\n";
                                }

                                int ZLeadInd;
                                int ZTrailingInd;
                                float tmpZHadEta = GenPart_eta[ZHadInd];
                                float tmpZHadPhi = GenPart_phi[ZHadInd];

                                int ZLepDecLeadInd;
                                int ZLepDecTrailingInd;
                                if (ZOneIsLeptonic) {
                                    ZLepDecLeadInd = ZOneDecLeadInd;
                                    ZLepDecTrailingInd = ZOneDecTrailingInd;
                                }
                                else if (ZTwoIsLeptonic) {
                                    ZLepDecLeadInd = ZTwoDecLeadInd;
                                    ZLepDecTrailingInd = ZTwoDecTrailingInd;
                                }
                                else{
                                    std::cout <<"ERROR ERROR, CHANNEL TYPE MIXUP\n";
                                }



                                float tmpZLepDecLeadEta = GenPart_eta[ZLepDecLeadInd];
                                float tmpZLepDecLeadPhi = GenPart_phi[ZLepDecLeadInd];
                                float tmpZLepDecTrailingEta = GenPart_eta[ZLepDecTrailingInd];
                                float tmpZLepDecTrailingPhi = GenPart_phi[ZLepDecTrailingInd];
                                

                                float tmpHZdR = calcDeltaR(tmpHPhi,tmpHEta,tmpZHadPhi,tmpZHadEta);
                                float tmpHZLeadLepdR = calcDeltaR(tmpHPhi,tmpHEta,tmpZLepDecLeadPhi,tmpZLepDecLeadEta);
                                float tmpHZTrailingLepdR = calcDeltaR(tmpHPhi,tmpHEta,tmpZLepDecTrailingPhi,tmpZLepDecTrailingEta);

                                float tmpZLepDecLeadTrailingdR = calcDeltaR(tmpZLepDecLeadPhi,tmpZLepDecLeadEta,tmpZLepDecTrailingPhi,tmpZLepDecTrailingEta);

                                HGendRFromLepZLeadLepL = tmpHZLeadLepdR;
                                HGendRFromLepZTrailingLepL = tmpHZTrailingLepdR;
                                HGendRFromHadZL = tmpHZdR;
                                LeadLepdRFromTrailingLepL = tmpZLepDecLeadTrailingdR;

                                nLHEReweightingWeightGenSemiLepL = *nLHEReweightingWeight;
                                for (UInt_t nReweightItr=0; nReweightItr<nLHEReweightingWeightGenSemiLepL;nReweightItr++){
                                    LHEReweightingWeightGenSemiLepL.push_back(LHEReweightingWeight[nReweightItr]);
                                }

                                genSemiLepTree->Fill();


                                LHEReweightingWeightGenSemiLepL.clear();







                                //Finding H FatJet
                                
                                float tmpHToFJMindR = 1000.;
                                int HFJInd = -1;
                                float HFJEta = 0;
                                float HFJPhi = 0;
                                UInt_t tmpnGenJetAK8s = *nGenJetAK8;

                                //std::cout << "HFJ Loop " << tmpHEta << " "<< tmpHPhi << "\n";
                                for (UInt_t fatJetInd=0;fatJetInd<tmpnGenJetAK8s;fatJetInd++){
                                    float tmpHFJEta = GenJetAK8_eta[fatJetInd];
                                    float tmpHFJPhi = GenJetAK8_phi[fatJetInd];
                                    float tmpDeltaR = calcDeltaR(tmpHFJPhi,tmpHFJEta,tmpHPhi,tmpHEta);
                                    //std::cout << fatJetInd << " " << tmpHFJEta << " " << tmpHFJPhi << " " << tmpDeltaR << "\n";
                                    if (tmpDeltaR < maxdRCut && tmpDeltaR < tmpHToFJMindR) {
                                        HFJInd = fatJetInd;
                                        tmpHToFJMindR = tmpDeltaR;
                                        HFJEta = tmpHFJEta;
                                        HFJPhi = tmpHFJPhi;
                                    }
                                    
                                }

                                //Finding Z Had GenJetAK8
                                

                                
                                float tmpZHadToFJMindR = 1000.;
                                int ZHadFJInd = -1;
                                float ZHadFJEta = 0;
                                float ZHadFJPhi = 0;
                                //std::cout << "ZFJ Loop " << ZOneIsHadronic << " " <<  tmpZHadEta << " " << tmpZHadPhi << "\n";
                                for (UInt_t fatJetInd=0;fatJetInd<tmpnGenJetAK8s;fatJetInd++){
                                    //if (fatJetInd == HFJInd) continue;
                                    float tmpZFJEta = GenJetAK8_eta[fatJetInd];
                                    float tmpZFJPhi = GenJetAK8_phi[fatJetInd];
                                    float tmpDeltaR = calcDeltaR(tmpZFJPhi,tmpZFJEta,tmpZHadPhi,tmpZHadEta);
                                    //std::cout << fatJetInd << " " << tmpZFJEta << " " << tmpZFJPhi << " " << tmpDeltaR << "\n";
                                    if (tmpDeltaR < maxdRCut && tmpDeltaR < tmpZHadToFJMindR) {
                                        if (fatJetInd == HFJInd && tmpDeltaR >= tmpHToFJMindR){
                                            continue;
                                        } 
                                        ZHadFJInd = fatJetInd;
                                        tmpZHadToFJMindR = tmpDeltaR;
                                        ZHadFJEta = tmpZFJEta;
                                        ZHadFJPhi = tmpZFJPhi;
                                    }
                                    
                                }
                                if (ZHadFJInd == HFJInd){
                                    float tmptmpHToFJMindR = 1000.;
                                    int tmpHFJInd = -1;
                                    float tmpHFJEta = 0;
                                    float tmpHFJPhi = 0;

                                    //std::cout << "HFJ Loop " << tmpHEta << " "<< tmpHPhi << "\n";
                                    for (UInt_t fatJetInd=0;fatJetInd<tmpnGenJetAK8s;fatJetInd++){
                                        if (fatJetInd == ZHadFJInd) continue;
                                        float tmpHFJEta = GenJetAK8_eta[fatJetInd];
                                        float tmpHFJPhi = GenJetAK8_phi[fatJetInd];
                                        float tmpDeltaR = calcDeltaR(tmpHFJPhi,tmpHFJEta,tmpHPhi,tmpHEta);
                                        //std::cout << fatJetInd << " " << tmpHFJEta << " " << tmpHFJPhi << " " << tmpDeltaR << "\n";
                                        if (tmpDeltaR < maxdRCut && tmpDeltaR < tmptmpHToFJMindR) {
                                            tmpHFJInd = fatJetInd;
                                            tmptmpHToFJMindR = tmpDeltaR;
                                            tmpHFJEta = tmpHFJEta;
                                            tmpHFJPhi = tmpHFJPhi;
                                        }
                                        
                                    }
                                    HFJInd = tmpHFJInd;
                                    tmpHToFJMindR = tmptmpHToFJMindR;
                                    HFJEta = tmpHFJEta;
                                    HFJPhi = tmpHFJPhi;
                                }

                                ZFJGenHadronFlavourL = GenJetAK8_hadronFlavour[ZHadFJInd];
                                HFJGenHadronFlavourL = GenJetAK8_hadronFlavour[HFJInd];
                                

                                
                                if (ZHadFJInd >= 0) goodGenZFJMatchL = true;
                                if (HFJInd >= 0) goodGenHFJMatchL = true;

                                int HFJNonGenInd = -1;
                                int ZHadFJNonGenInd = -1;

                                for (UInt_t fatJetInd=0;fatJetInd<tmpnFatJets;fatJetInd++){
                                    Int_t tmpFJGenJetInd = FatJet_genJetAK8Idx[fatJetInd];
                                    if (tmpFJGenJetInd == HFJInd) HFJNonGenInd = fatJetInd;
                                    else if (tmpFJGenJetInd == ZHadFJInd) ZHadFJNonGenInd = fatJetInd;

                                }

                                HFJIndL = HFJNonGenInd;
                                ZFJIndL = ZHadFJNonGenInd;
                                
                                
                                
                                
                                eventGenHToBBL = true;




                                //Finding Z Lead Lep GenPart
                                
                                float tmpZLepDecLeadToFJMindR = 1000.;
                                int ZLepDecLeadLepInd = -1;
                                float ZLepDecLeadLepEta = 0;
                                float ZLepDecLeadLepPhi = 0;
                                bool ZLepIsMuon = false;
                                //std::cout << "Z Lead Lep Elec Loop " << ZOneIsLeptonic << " " <<  tmpZLepDecLeadEta << " " << tmpZLepDecLeadPhi << "\n";
                                for (UInt_t elecInd=0;elecInd<*nElectron;elecInd++){
                                    float tmpEEta = Electron_eta[elecInd];
                                    float tmpEPhi = Electron_phi[elecInd];
                                    float tmpDeltaR = calcDeltaR(tmpZLepDecLeadPhi,tmpZLepDecLeadEta,tmpEPhi,tmpEEta);
                                    //std::cout << elecInd << " " << tmpEEta << " " << tmpEPhi << " " << tmpDeltaR << "\n";
                                    if (tmpDeltaR < maxdRCut && tmpDeltaR < tmpZLepDecLeadToFJMindR) {
                                        ZLepDecLeadLepInd = elecInd;
                                        tmpZLepDecLeadToFJMindR = tmpDeltaR;
                                        ZLepDecLeadLepEta = tmpEEta;
                                        ZLepDecLeadLepPhi = tmpEPhi;
                                    }
                                    
                                }
                                //std::cout << "Z Lead Lep Muon Loop\n";
                                for (UInt_t muonInd=0;muonInd<*nMuon;muonInd++){
                                    float tmpMEta = Muon_eta[muonInd];
                                    float tmpMPhi = Muon_phi[muonInd];
                                    float tmpDeltaR = calcDeltaR(tmpZLepDecLeadPhi,tmpZLepDecLeadEta,tmpMPhi,tmpMEta);
                                    //std::cout << muonInd << " " << tmpMEta << " " << tmpMPhi << " " << tmpDeltaR << "\n";
                                    if (tmpDeltaR < maxdRCut && tmpDeltaR < tmpZLepDecLeadToFJMindR) {
                                        ZLepDecLeadLepInd = muonInd;
                                        tmpZLepDecLeadToFJMindR = tmpDeltaR;
                                        ZLepDecLeadLepEta = tmpMEta;
                                        ZLepDecLeadLepPhi = tmpMPhi;
                                        ZLepIsMuon = true;
                                    }
                                    
                                }

                                //Finding Z Trailing Lep GenPart
                                
                                
                                float tmpZLepDecTrailingToLepMindR = 1000.;
                                int ZLepDecTrailingLepInd = -1;
                                float ZLepDecTrailingLepEta = 0;
                                float ZLepDecTrailingLepPhi = 0;
                                
                                if (!ZLepIsMuon){
                                    //std::cout << "Z Trailing Lep Elec Loop " <<  tmpZLepDecTrailingEta << " " << tmpZLepDecTrailingPhi << "\n";
                                    for (UInt_t elecInd=0;elecInd<*nElectron;elecInd++){
                                        if (ZLepDecLeadLepInd == elecInd) continue;
                                        float tmpEEta = Electron_eta[elecInd];
                                        float tmpEPhi = Electron_phi[elecInd];
                                        float tmpDeltaR = calcDeltaR(tmpZLepDecTrailingPhi,tmpZLepDecTrailingEta,tmpEPhi,tmpEEta);
                                        //std::cout << elecInd << " " << tmpEEta << " " << tmpEPhi << " " << tmpDeltaR << "\n";
                                        if (tmpDeltaR < maxdRCut && tmpDeltaR < tmpZLepDecTrailingToLepMindR) {
                                            ZLepDecTrailingLepInd = elecInd;
                                            tmpZLepDecTrailingToLepMindR = tmpDeltaR;
                                            ZLepDecTrailingLepEta = tmpEEta;
                                            ZLepDecTrailingLepPhi = tmpEPhi;
                                        }
                                        
                                    }
                                }
                                else {
                                    //std::cout << "Z Trailing Lep Muon Loop\n";
                                    for (UInt_t muonInd=0;muonInd<*nMuon;muonInd++){
                                        if (ZLepDecLeadLepInd == muonInd) continue;
                                        float tmpMEta = Muon_eta[muonInd];
                                        float tmpMPhi = Muon_phi[muonInd];
                                        float tmpDeltaR = calcDeltaR(tmpZLepDecTrailingPhi,tmpZLepDecTrailingEta,tmpMPhi,tmpMEta);
                                        //std::cout << muonInd << " " << tmpMEta << " " << tmpMPhi << " " << tmpDeltaR << "\n";
                                        if (tmpDeltaR < maxdRCut && tmpDeltaR < tmpZLepDecTrailingToLepMindR) {
                                            ZLepDecTrailingLepInd = muonInd;
                                            tmpZLepDecTrailingToLepMindR = tmpDeltaR;
                                            ZLepDecTrailingLepEta = tmpMEta;
                                            ZLepDecTrailingLepPhi = tmpMPhi;
                                        }
                                        
                                    }
                                }
                                //std::cout << ZLepIsMuon << " " << HFJInd << " " << ZHadFJInd << " " << ZLepDecLeadLepInd << " " << ZLepDecTrailingLepInd << "\n";

                                if (HFJInd != -1 && ZHadFJInd != -1 && ZLepDecLeadLepInd != -1 && ZLepDecTrailingLepInd != -1){
                                    float tmpHZFJdR = calcDeltaR(HFJPhi,HFJEta,ZHadFJPhi,ZHadFJEta);
                                    float tmpHZLeadLepdR = calcDeltaR(HFJPhi,HFJEta,ZLepDecLeadLepPhi,ZLepDecLeadLepEta);
                                    float tmpHZTrailingLepdR = calcDeltaR(HFJPhi,HFJEta,ZLepDecTrailingLepPhi,ZLepDecTrailingLepEta);
                                    //std::cout << tmpHZFJdR << " " << tmpHZLeadLepdR << " " << tmpHZTrailingLepdR << "\n";

                                    HGenFJdRFromLepZLeadLepL = tmpHZLeadLepdR;
                                    HGenFJdRFromLepZTrailingLepL = tmpHZTrailingLepdR;
                                    HGenFJdRFromHadZFJL = tmpHZFJdR;


                                    nLHEReweightingWeightGenSemiLepFJL = *nLHEReweightingWeight;
                                    for (UInt_t nReweightItr=0; nReweightItr<nLHEReweightingWeightGenSemiLepFJL;nReweightItr++){
                                        LHEReweightingWeightGenSemiLepFJL.push_back(LHEReweightingWeight[nReweightItr]);
                                    }

                                    genSemiLepFJTree->Fill();

                                    LHEReweightingWeightGenSemiLepFJL.clear();
                                }
                                //std::cout << "-----------------------------------------------\n";


                            }
                            else{
                                genSemiLepChannelNoHTobbCtr += 1;
                                //genSemiLepChannelNoHTobbWeightedCtr += *genWeight;
                            }

                        }

                        else if (ZIsLeptonic) {
                            genChannelL=0;
                            if (HTobbBoolL){
                                genLepChannelCtr += 1;
                                //genLepChannelWeightedCtr += *genWeight;



                                //Filling genSemiLepdR tree

                                float tmpHEta = GenPart_eta[finalHAr[0]];
                                float tmpHPhi = GenPart_phi[finalHAr[0]];

                                int ZLeadLepDecLeadInd;
                                int ZLeadLepDecTrailingInd;
                                int ZTrailingLepDecLeadInd;
                                int ZTrailingLepDecTrailingInd;
                                float tmpZOnePt = GenPart_pt[finalZAr[0]];
                                float tmpZTwoPt = GenPart_pt[finalZAr[1]];
                                if (tmpZOnePt > tmpZTwoPt){
                                    ZLeadLepDecLeadInd = ZOneDecLeadInd;
                                    ZLeadLepDecTrailingInd = ZOneDecTrailingInd;
                                    ZTrailingLepDecLeadInd = ZTwoDecLeadInd;
                                    ZTrailingLepDecTrailingInd = ZTwoDecTrailingInd;
                                }
                                else{
                                    ZLeadLepDecLeadInd = ZTwoDecLeadInd;
                                    ZLeadLepDecTrailingInd = ZTwoDecTrailingInd;
                                    ZTrailingLepDecLeadInd = ZOneDecLeadInd;
                                    ZTrailingLepDecTrailingInd = ZOneDecTrailingInd;
                                }



                                float tmpZLeadLepDecLeadEta = GenPart_eta[ZLeadLepDecLeadInd];
                                float tmpZLeadLepDecLeadPhi = GenPart_phi[ZLeadLepDecLeadInd];

                                float tmpZLeadLepDecTrailingEta = GenPart_eta[ZLeadLepDecTrailingInd];
                                float tmpZLeadLepDecTrailingPhi = GenPart_phi[ZLeadLepDecTrailingInd];

                                float tmpZTrailingLepDecLeadEta = GenPart_eta[ZTrailingLepDecLeadInd];
                                float tmpZTrailingLepDecLeadPhi = GenPart_phi[ZTrailingLepDecLeadInd];

                                float tmpZTrailingLepDecTrailingEta = GenPart_eta[ZTrailingLepDecTrailingInd];
                                float tmpZTrailingLepDecTrailingPhi = GenPart_phi[ZTrailingLepDecTrailingInd];

                                float tmpHLeadZLeadLepdR = calcDeltaR(tmpHPhi,tmpHEta,tmpZLeadLepDecLeadPhi,tmpZLeadLepDecLeadEta);
                                float tmpHLeadZTrailingLepdR = calcDeltaR(tmpHPhi,tmpHEta,tmpZLeadLepDecTrailingPhi,tmpZLeadLepDecTrailingEta);
                                
                                float tmpHTrailingZLeadLepdR = calcDeltaR(tmpHPhi,tmpHEta,tmpZTrailingLepDecLeadPhi,tmpZTrailingLepDecLeadEta);
                                float tmpHTrailingZTrailingLepdR = calcDeltaR(tmpHPhi,tmpHEta,tmpZTrailingLepDecTrailingPhi,tmpZTrailingLepDecTrailingEta);

                                HGendRFromLeadZLeadLepL = tmpHLeadZLeadLepdR;
                                HGendRFromLeadZTrailingLepL = tmpHLeadZTrailingLepdR;
                                HGendRFromTrailingZLeadLepL = tmpHTrailingZLeadLepdR;
                                HGendRFromTrailingZTrailingLepL = tmpHTrailingZTrailingLepdR;


                                nLHEReweightingWeightGenLepL = *nLHEReweightingWeight;
                                for (UInt_t nReweightItr=0; nReweightItr<nLHEReweightingWeightGenLepL;nReweightItr++){
                                    LHEReweightingWeightGenLepL.push_back(LHEReweightingWeight[nReweightItr]);
                                }


                                genLepTree->Fill();

                                LHEReweightingWeightGenLepL.clear();
                                





                                //Finding H FatJet
                                
                                float tmpHToFJMindR = 1000.;
                                int HFJInd = -1;
                                float HFJEta = 0;
                                float HFJPhi = 0;


                                for (UInt_t fatJetInd=0;fatJetInd<tmpnFatJets;fatJetInd++){
                                    float tmpHFJEta = FatJet_eta[fatJetInd];
                                    float tmpHFJPhi = FatJet_phi[fatJetInd];
                                    float tmpDeltaR = calcDeltaR(tmpHFJPhi,tmpHFJEta,tmpHPhi,tmpHEta);
                                    if (tmpDeltaR < maxdRCut && tmpDeltaR < tmpHToFJMindR) {
                                        HFJInd = fatJetInd;
                                        tmpHToFJMindR = tmpDeltaR;
                                        HFJEta = tmpHFJEta;
                                        HFJPhi = tmpHFJPhi;
                                    }
                                    
                                }

                                //Finding Lead Z Lead Lep GenPart
                                
                                float tmpZLeadLepDecLeadToFJMindR = 1000.;
                                int ZLeadLepDecLeadLepInd = -1;
                                float ZLeadLepDecLeadLepEta = 0;
                                float ZLeadLepDecLeadLepPhi = 0;
                                bool ZLeadLepIsMuon = false;

                                for (UInt_t elecInd=0;elecInd<*nElectron;elecInd++){
                                    float tmpEEta = Electron_eta[elecInd];
                                    float tmpEPhi = Electron_phi[elecInd];
                                    float tmpDeltaR = calcDeltaR(tmpZLeadLepDecLeadPhi,tmpZLeadLepDecLeadEta,tmpEPhi,tmpEEta);
                                    if (tmpDeltaR < maxdRCut && tmpDeltaR < tmpZLeadLepDecLeadToFJMindR) {
                                        ZLeadLepDecLeadLepInd = elecInd;
                                        tmpZLeadLepDecLeadToFJMindR = tmpDeltaR;
                                        ZLeadLepDecLeadLepEta = tmpEEta;
                                        ZLeadLepDecLeadLepPhi = tmpEPhi;
                                    }
                                    
                                }
                                for (UInt_t muonInd=0;muonInd<*nMuon;muonInd++){
                                    float tmpMEta = Muon_eta[muonInd];
                                    float tmpMPhi = Muon_phi[muonInd];
                                    float tmpDeltaR = calcDeltaR(tmpZLeadLepDecLeadPhi,tmpZLeadLepDecLeadEta,tmpMPhi,tmpMEta);
                                    if (tmpDeltaR < maxdRCut && tmpDeltaR < tmpZLeadLepDecLeadToFJMindR) {
                                        ZLeadLepDecLeadLepInd = muonInd;
                                        tmpZLeadLepDecLeadToFJMindR = tmpDeltaR;
                                        ZLeadLepDecLeadLepEta = tmpMEta;
                                        ZLeadLepDecLeadLepPhi = tmpMPhi;
                                        ZLeadLepIsMuon = true;
                                    }
                                    
                                }

                                //Finding Lead Z Trailing Lep GenPart

                                
                                float tmpZLeadLepDecTrailingToLepMindR = 1000.;
                                int ZLeadLepDecTrailingLepInd = -1;
                                float ZLeadLepDecTrailingLepEta = 0;
                                float ZLeadLepDecTrailingLepPhi = 0;
                                
                                if (!ZLeadLepIsMuon){
                                    for (UInt_t elecInd=0;elecInd<*nElectron;elecInd++){
                                        if (ZLeadLepDecLeadLepInd == elecInd) continue;
                                        float tmpEEta = Electron_eta[elecInd];
                                        float tmpEPhi = Electron_phi[elecInd];
                                        float tmpDeltaR = calcDeltaR(tmpZLeadLepDecTrailingPhi,tmpZLeadLepDecTrailingEta,tmpEPhi,tmpEEta);
                                        if (tmpDeltaR < maxdRCut && tmpDeltaR < tmpZLeadLepDecTrailingToLepMindR) {
                                            ZLeadLepDecTrailingLepInd = elecInd;
                                            tmpZLeadLepDecTrailingToLepMindR = tmpDeltaR;
                                            ZLeadLepDecTrailingLepEta = tmpEEta;
                                            ZLeadLepDecTrailingLepPhi = tmpEPhi;
                                        }
                                        
                                    }
                                }
                                else {
                                    for (UInt_t muonInd=0;muonInd<*nMuon;muonInd++){
                                        if (ZLeadLepDecLeadLepInd == muonInd) continue;
                                        float tmpMEta = Muon_eta[muonInd];
                                        float tmpMPhi = Muon_phi[muonInd];
                                        float tmpDeltaR = calcDeltaR(tmpZLeadLepDecTrailingPhi,tmpZLeadLepDecTrailingEta,tmpMPhi,tmpMEta);
                                        if (tmpDeltaR < maxdRCut && tmpDeltaR < tmpZLeadLepDecTrailingToLepMindR) {
                                            ZLeadLepDecTrailingLepInd = muonInd;
                                            tmpZLeadLepDecTrailingToLepMindR = tmpDeltaR;
                                            ZLeadLepDecTrailingLepEta = tmpMEta;
                                            ZLeadLepDecTrailingLepPhi = tmpMPhi;
                                        }
                                        
                                    }
                                }


                                //Finding trailing Z Lead Lep GenPart
                                
                                float tmpZTrailingLepDecLeadToFJMindR = 1000.;
                                int ZTrailingLepDecLeadLepInd = -1;
                                float ZTrailingLepDecLeadLepEta = 0;
                                float ZTrailingLepDecLeadLepPhi = 0;
                                bool ZTrailingLepIsMuon = false;

                                for (UInt_t elecInd=0;elecInd<*nElectron;elecInd++){
                                    if (!ZLeadLepIsMuon && (ZLeadLepDecLeadLepInd == elecInd || ZLeadLepDecTrailingLepInd == elecInd)) continue;
                                    float tmpEEta = Electron_eta[elecInd];
                                    float tmpEPhi = Electron_phi[elecInd];
                                    float tmpDeltaR = calcDeltaR(tmpZTrailingLepDecLeadPhi,tmpZTrailingLepDecLeadEta,tmpEPhi,tmpEEta);
                                    if (tmpDeltaR < maxdRCut && tmpDeltaR < tmpZTrailingLepDecLeadToFJMindR) {
                                        ZTrailingLepDecLeadLepInd = elecInd;
                                        tmpZTrailingLepDecLeadToFJMindR = tmpDeltaR;
                                        ZTrailingLepDecLeadLepEta = tmpEEta;
                                        ZTrailingLepDecLeadLepPhi = tmpEPhi;
                                    }
                                    
                                }
                                for (UInt_t muonInd=0;muonInd<*nMuon;muonInd++){
                                    if (ZLeadLepIsMuon && (ZLeadLepDecLeadLepInd == muonInd || ZLeadLepDecTrailingLepInd == muonInd)) continue;
                                    float tmpMEta = Muon_eta[muonInd];
                                    float tmpMPhi = Muon_phi[muonInd];
                                    float tmpDeltaR = calcDeltaR(tmpZTrailingLepDecLeadPhi,tmpZTrailingLepDecLeadEta,tmpMPhi,tmpMEta);
                                    if (tmpDeltaR < maxdRCut && tmpDeltaR < tmpZTrailingLepDecLeadToFJMindR) {
                                        ZTrailingLepDecLeadLepInd = muonInd;
                                        tmpZTrailingLepDecLeadToFJMindR = tmpDeltaR;
                                        ZTrailingLepDecLeadLepEta = tmpMEta;
                                        ZTrailingLepDecLeadLepPhi = tmpMPhi;
                                        ZTrailingLepIsMuon = true;
                                    }
                                    
                                }

                                //Finding trailing Z Trailing Lep GenPart

                                
                                float tmpZTrailingLepDecTrailingToLepMindR = 1000.;
                                int ZTrailingLepDecTrailingLepInd = -1;
                                float ZTrailingLepDecTrailingLepEta = 0;
                                float ZTrailingLepDecTrailingLepPhi = 0;
                                
                                if (!ZTrailingLepIsMuon){
                                    for (UInt_t elecInd=0;elecInd<*nElectron;elecInd++){
                                        if (!ZLeadLepIsMuon && (ZLeadLepDecLeadLepInd == elecInd || ZLeadLepDecTrailingLepInd == elecInd)) continue;
                                        if (ZTrailingLepDecLeadLepInd == elecInd) continue;
                                        float tmpEEta = Electron_eta[elecInd];
                                        float tmpEPhi = Electron_phi[elecInd];
                                        float tmpDeltaR = calcDeltaR(tmpZTrailingLepDecTrailingPhi,tmpZTrailingLepDecTrailingEta,tmpEPhi,tmpEEta);
                                        if (tmpDeltaR < maxdRCut && tmpDeltaR < tmpZTrailingLepDecTrailingToLepMindR) {
                                            ZTrailingLepDecTrailingLepInd = elecInd;
                                            tmpZTrailingLepDecTrailingToLepMindR = tmpDeltaR;
                                            ZTrailingLepDecTrailingLepEta = tmpEEta;
                                            ZTrailingLepDecTrailingLepPhi = tmpEPhi;
                                        }
                                        
                                    }
                                }
                                else {
                                    for (UInt_t muonInd=0;muonInd<*nMuon;muonInd++){
                                        if (ZLeadLepIsMuon && (ZLeadLepDecLeadLepInd == muonInd || ZLeadLepDecTrailingLepInd == muonInd)) continue;
                                        if (ZTrailingLepDecLeadLepInd == muonInd) continue;
                                        float tmpMEta = Muon_eta[muonInd];
                                        float tmpMPhi = Muon_phi[muonInd];
                                        float tmpDeltaR = calcDeltaR(tmpZTrailingLepDecTrailingPhi,tmpZTrailingLepDecTrailingEta,tmpMPhi,tmpMEta);
                                        if (tmpDeltaR < maxdRCut && tmpDeltaR < tmpZTrailingLepDecTrailingToLepMindR) {
                                            ZTrailingLepDecTrailingLepInd = muonInd;
                                            tmpZTrailingLepDecTrailingToLepMindR = tmpDeltaR;
                                            ZTrailingLepDecTrailingLepEta = tmpMEta;
                                            ZTrailingLepDecTrailingLepPhi = tmpMPhi;
                                        }
                                        
                                    }
                                }

                                if (HFJInd != -1 && ZLeadLepDecLeadLepInd != -1 && ZLeadLepDecTrailingLepInd != -1 && ZTrailingLepDecLeadLepInd != -1 && ZTrailingLepDecTrailingLepInd != -1){
                                    float tmpHLeadZLeadLepdR = calcDeltaR(HFJPhi,HFJEta,ZLeadLepDecLeadLepPhi,ZLeadLepDecLeadLepEta);
                                    float tmpHLeadZTrailingLepdR = calcDeltaR(HFJPhi,HFJEta,ZLeadLepDecTrailingLepPhi,ZLeadLepDecTrailingLepEta);
                                    
                                    float tmpHTrailingZLeadLepdR = calcDeltaR(HFJPhi,HFJEta,ZTrailingLepDecLeadLepPhi,ZTrailingLepDecLeadLepEta);
                                    float tmpHTrailingZTrailingLepdR = calcDeltaR(HFJPhi,HFJEta,ZTrailingLepDecTrailingLepPhi,ZTrailingLepDecTrailingLepEta);

                                    HGenFJdRFromLeadZLeadLepL = tmpHLeadZLeadLepdR;
                                    HGenFJdRFromLeadZTrailingLepL = tmpHLeadZTrailingLepdR;
                                    HGenFJdRFromTrailingZLeadLepL = tmpHTrailingZLeadLepdR;
                                    HGenFJdRFromTrailingZTrailingLepL = tmpHTrailingZTrailingLepdR;


                                    nLHEReweightingWeightGenLepFJL = *nLHEReweightingWeight;
                                    for (UInt_t nReweightItr=0; nReweightItr<nLHEReweightingWeightGenLepFJL;nReweightItr++){
                                        LHEReweightingWeightGenLepFJL.push_back(LHEReweightingWeight[nReweightItr]);
                                    }


                                    genLepFJTree->Fill();

                                    LHEReweightingWeightGenLepFJL.clear();
                                }





                            }
                            else{
                                genLepChannelNoHTobbCtr += 1;
                                //genLepChannelNoHTobbWeightedCtr += *genWeight;
                            }

                            

                        }
                        else {
                            genChannelL=3;
                            if (HTobbBoolL){
                                genOtherChannelCtr += 1;
                                //genOtherChannelWeightedCtr += *genWeight;
                            }
                            else{
                                genOtherChannelNoHTobbCtr += 1;
                                //genOtherChannelNoHTobbWeightedCtr += *genWeight;
                            }
                        }
                        

                        
                            
                    }


                }

            }

            //setting array mask

            if (ZIsLeptonic) {
                if (HTobbBoolL){
                    evWeightedCtrMaskOne[1] = true;
                    evWeightedCtrMaskTwo[0] = true;
                }
                else {
                    evWeightedCtrMaskOne[5] = true;
                    evWeightedCtrMaskTwo[5] = true;
                    evWeightedCtrMaskTwo[10] = true;
                }
            }
            else if (ZIsSemiLeptonic) {
                if (HTobbBoolL){
                    evWeightedCtrMaskOne[2] = true;
                    evWeightedCtrMaskTwo[1] = true;
                }
                else {
                    evWeightedCtrMaskOne[6] = true;
                    evWeightedCtrMaskTwo[6] = true;
                    evWeightedCtrMaskTwo[10] = true;
                }
            }
            else if (ZIsHadronic) {
                if (HTobbBoolL){
                    evWeightedCtrMaskOne[3] = true;
                    evWeightedCtrMaskTwo[2] = true;
                }
                else {
                    evWeightedCtrMaskOne[7] = true;
                    evWeightedCtrMaskTwo[7] = true;
                    evWeightedCtrMaskTwo[10] = true;
                }
            }
            else {
                if (HTobbBoolL){
                    evWeightedCtrMaskOne[4] = true;
                    if (!evWeightedCtrMaskTwo[4]) evWeightedCtrMaskTwo[3] = true;
                }
                else {
                    evWeightedCtrMaskOne[8] = true;
                    if (!evWeightedCtrMaskTwo[9]) evWeightedCtrMaskTwo[8] = true;
                    evWeightedCtrMaskTwo[10] = true;
                }
            }

            for (unsigned int maskInt = 0; maskInt < evWeightedCtrMaskTwo.size(); maskInt++){
                if (evWeightedCtrMaskTwo[maskInt]){
                    genChannelWeightedCtrAr[maskInt][0] += *genWeight;
                    for (unsigned int C2VCtr = 1; C2VCtr < genChannelWeightedCtrAr[maskInt].size(); C2VCtr++){
                        genChannelWeightedCtrAr[maskInt][C2VCtr] += *genWeight*(LHEReweightingWeight[C2VCtr-1]);
                    }
                }
            }
            

            /*
            //First check that it passes the hbb tagging
            bool hbbTag = *HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02 || *HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2 || *HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4;

            //Hadronic
            bool hadHLT =  (*HLT_PFHT1050 || *HLT_AK8PFJet500 || *HLT_AK8PFJet360_TrimMass30 || *HLT_AK8PFHT750_TrimMass50 || *HLT_AK8PFJet380_TrimMass30 ||
            *HLT_AK8PFJet400_TrimMass30 || *HLT_AK8PFJet420_TrimMass30 ||
            *HLT_AK8PFHT800_TrimMass50 || *HLT_AK8PFHT850_TrimMass50 || *HLT_AK8PFHT900_TrimMass50);
            

            
            //if (!hbbTag) continue;
            //passhbbCtr += 1;
            

            //Now check that it can be sorted into either leptonic, semi-leptonic, || hadronic
            //Leptonic
            
            bool doubleElecHLT =  (*HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL || *HLT_DoubleEle25_CaloIdL_MW || *HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ || *HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL ||  *HLT_DiEle27_WPTightCaloOnly_L1DoubleEG || 
            *HLT_DoubleEle33_CaloIdL_MW || *HLT_DoubleEle25_CaloIdL_MW || *HLT_DoubleEle27_CaloIdL_MW || *HLT_DoublePhoton70);
                
            bool doubleMuonHLT =  (*HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8 || *HLT_TripleMu_10_5_5_DZ || *HLT_TripleMu_12_10_5 || *HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8 || *HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8 || 
            *HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass3p8 || *HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass8);

            bool muonEGHLT = (*HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL || *HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ || *HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ || *HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ ||  // || *HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ || *HLT_Mu8_DiEle12_CaloIdL_TrackIdL_DZ 
            *HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL || *HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL);
            
            //Semi-leptonic
            bool elecHLT = (*HLT_Ele32_WPTight_Gsf || *HLT_Ele115_CaloIdVT_GsfTrkIdT || *HLT_Ele27_WPTight_Gsf || *HLT_Ele28_WPTight_Gsf || 
            *HLT_Ele35_WPTight_Gsf || *HLT_Ele38_WPTight_Gsf || *HLT_Ele40_WPTight_Gsf || *HLT_Ele32_WPTight_Gsf_L1DoubleEG || *HLT_Photon200);

            bool muonHLT = *HLT_IsoMu24 || *HLT_IsoMu27 || *HLT_IsoMu30 || *HLT_Mu50;

            //bool passHLTBool = hbbTag || hadHLT || doubleElecHLT || doubleMuonHLT || muonEGHLT || elecHLT || muonHLT;
            */
            bool passFlagBool = *Flag_goodVertices && *Flag_globalSuperTightHalo2016Filter && *Flag_HBHENoiseFilter && *Flag_HBHENoiseIsoFilter && *Flag_EcalDeadCellTriggerPrimitiveFilter && *Flag_BadPFMuonFilter && *Flag_eeBadScFilter && *Flag_ecalBadCalibFilter;

            if (!passFlagBool) continue;
            passFlagCtr += 1;
            //passFlagWeightedCtr += *genWeight;

            if (!isBackground){
                for (unsigned int maskInt = 0; maskInt < evWeightedCtrMaskOne.size(); maskInt++){
                    if (evWeightedCtrMaskOne[maskInt]){
                        passFlagWeightedCtrAr[maskInt][0] += *genWeight;
                        for (unsigned int C2VCtr = 1; C2VCtr < passFlagWeightedCtrAr[maskInt].size(); C2VCtr++){
                            passFlagWeightedCtrAr[maskInt][C2VCtr] += *genWeight*(LHEReweightingWeight[C2VCtr-1]);
                        }
                    }
                }
                if (ZIsLeptonic) {
                    if (HTobbBoolL){
                        passFlagGenLepCtr += 1;
                        //passFlagGenLepWeightedCtr += *genWeight;
                    }
                    else {
                        passFlagGenLepNoHTobbCtr += 1;
                        //passFlagGenLepNoHTobbWeightedCtr += *genWeight;

                    }
                }
                else if (ZIsSemiLeptonic) {
                    if (HTobbBoolL){
                        passFlagGenSemiLepCtr += 1;
                        //passFlagGenSemiLepWeightedCtr += *genWeight;
                    }
                    else{
                        passFlagGenSemiLepNoHTobbCtr += 1;
                        //passFlagGenSemiLepNoHTobbWeightedCtr += *genWeight;

                    }
                }
                else if (ZIsHadronic) {
                    if (HTobbBoolL){
                        passFlagGenHadCtr += 1;
                        //passFlagGenHadWeightedCtr += *genWeight;
                    }
                    else {
                        passFlagGenHadNoHTobbCtr += 1;
                        //passFlagGenHadNoHTobbWeightedCtr += *genWeight;

                    }
                }
                else {
                    if (HTobbBoolL){
                        passFlagGenOtherCtr += 1;
                        //passFlagGenOtherWeightedCtr += *genWeight;
                    }
                    else {
                        passFlagGenOtherNoHTobbCtr += 1;
                        //passFlagGenOtherNoHTobbWeightedCtr += *genWeight;

                    }
                }
            }





            if (debug){
                std::cout <<"Passed HLT\n";
            }


            bool passHLTBool = (*HLT_Ele32_WPTight_Gsf_L1DoubleEG || *HLT_Photon200 || *HLT_Ele115_CaloIdVT_GsfTrkIdT || 
            *HLT_IsoMu27 || *HLT_Mu50 || 
            *HLT_DoubleEle33_CaloIdL_MW || *HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ || *HLT_DiEle27_WPTightCaloOnly_L1DoubleEG || *HLT_DoublePhoton70 || 
            *HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8);
            //std::cout << testPassHLTBool << " " << passHLTBool << "\n";
            if (!passHLTBool) continue;
            passHLTCtr += 1;
            //passHLTWeightedCtr += *genWeight;

            if (!isBackground){
                for (unsigned int maskInt = 0; maskInt < evWeightedCtrMaskOne.size(); maskInt++){
                    if (evWeightedCtrMaskOne[maskInt]){
                        passHLTWeightedCtrAr[maskInt][0] += *genWeight;
                        for (unsigned int C2VCtr = 1; C2VCtr < passHLTWeightedCtrAr[maskInt].size(); C2VCtr++){
                            passHLTWeightedCtrAr[maskInt][C2VCtr] += *genWeight*(LHEReweightingWeight[C2VCtr-1]);
                        }
                    }
                }

                if (ZIsLeptonic) {
                    if (HTobbBoolL){
                        passHLTGenLepCtr += 1;
                        //passHLTGenLepWeightedCtr += *genWeight;
                    }
                    else {
                        passHLTGenLepNoHTobbCtr += 1;
                        //passHLTGenLepNoHTobbWeightedCtr += *genWeight;

                    }
                }
                else if (ZIsSemiLeptonic) {
                    if (HTobbBoolL){
                        passHLTGenSemiLepCtr += 1;
                        //passHLTGenSemiLepWeightedCtr += *genWeight;
                    }
                    else{
                        passHLTGenSemiLepNoHTobbCtr += 1;
                        //passHLTGenSemiLepNoHTobbWeightedCtr += *genWeight;

                    }
                }
                else if (ZIsHadronic) {
                    if (HTobbBoolL){
                        passHLTGenHadCtr += 1;
                        //passHLTGenHadWeightedCtr += *genWeight;
                    }
                    else {
                        passHLTGenHadNoHTobbCtr += 1;
                        //passHLTGenHadNoHTobbWeightedCtr += *genWeight;

                    }
                }
                else {
                    if (HTobbBoolL){
                        passHLTGenOtherCtr += 1;
                        //passHLTGenOtherWeightedCtr += *genWeight;
                    }
                    else {
                        passHLTGenOtherNoHTobbCtr += 1;
                        //passHLTGenOtherNoHTobbWeightedCtr += *genWeight;

                    }
                }
            }





            if (debug){
                std::cout <<"Passed HLT\n";
            }
            

            genWeightL = *genWeight;

            //Check if any fat jets in event
            
            if (tmpnFatJets<=0) continue;
            if (debug){
                std::cout <<"Passed nFJs\n";
            }
            passnFJCtr += 1;
            //passnFJWeightedCtr += *genWeight; 

            if (!isBackground){
                for (unsigned int maskInt = 0; maskInt < evWeightedCtrMaskOne.size(); maskInt++){
                    if (evWeightedCtrMaskOne[maskInt]){
                        passnFJWeightedCtrAr[maskInt][0] += *genWeight;
                        for (unsigned int C2VCtr = 1; C2VCtr < passnFJWeightedCtrAr[maskInt].size(); C2VCtr++){
                            passnFJWeightedCtrAr[maskInt][C2VCtr] += *genWeight*(LHEReweightingWeight[C2VCtr-1]);
                        }
                    }
                }
                if (ZIsLeptonic) {
                    if (HTobbBoolL){
                        passnFJGenLepCtr += 1;
                        //passnFJGenLepWeightedCtr += *genWeight;
                    }
                    else {
                        passnFJGenLepNoHTobbCtr += 1;
                        //passnFJGenLepNoHTobbWeightedCtr += *genWeight;

                    }
                }
                else if (ZIsSemiLeptonic) {
                    if (HTobbBoolL){
                        passnFJGenSemiLepCtr += 1;
                        //passnFJGenSemiLepWeightedCtr += *genWeight;
                    }
                    else {
                        passnFJGenSemiLepNoHTobbCtr += 1;
                        //passnFJGenSemiLepNoHTobbWeightedCtr += *genWeight;

                    }
                }
                else if (ZIsHadronic) {
                    if (HTobbBoolL){
                        passnFJGenHadCtr += 1;
                        //passnFJGenHadWeightedCtr += *genWeight;
                    }
                    else {
                        passnFJGenHadNoHTobbCtr += 1;
                        //passnFJGenHadNoHTobbWeightedCtr += *genWeight;

                    }
                }
                else {
                    if (HTobbBoolL){
                        passnFJGenOtherCtr += 1;
                        //passnFJGenOtherWeightedCtr += *genWeight;
                    }
                    else {
                        passnFJGenOtherNoHTobbCtr += 1;
                        //passnFJGenOtherNoHTobbWeightedCtr += *genWeight;

                    }
                }
            }

            // check if two or more VBF jets in event
            UInt_t tmpnVBFJets = *nJet;
            
            if (tmpnVBFJets < 2) continue;
            if (debug){
                std::cout <<"Passed nJs\n";
            }

            passnVBFCtr += 1;
            //passnVBFWeightedCtr += *genWeight; 

            if (!isBackground){
                for (unsigned int maskInt = 0; maskInt < evWeightedCtrMaskOne.size(); maskInt++){
                    if (evWeightedCtrMaskOne[maskInt]){
                        passnVBFWeightedCtrAr[maskInt][0] += *genWeight;
                        for (unsigned int C2VCtr = 1; C2VCtr < passnVBFWeightedCtrAr[maskInt].size(); C2VCtr++){
                            passnVBFWeightedCtrAr[maskInt][C2VCtr] += *genWeight*(LHEReweightingWeight[C2VCtr-1]);
                        }
                    }
                }
                if (ZIsLeptonic) {
                    if (HTobbBoolL){
                        passnVBFGenLepCtr += 1;
                        //passnVBFGenLepWeightedCtr += *genWeight;
                    }
                    else {
                        passnVBFGenLepNoHTobbCtr += 1;
                        //passnVBFGenLepNoHTobbWeightedCtr += *genWeight;
                        
                    }
                }
                else if (ZIsSemiLeptonic) {
                    if (HTobbBoolL){
                        passnVBFGenSemiLepCtr += 1;
                        //passnVBFGenSemiLepWeightedCtr += *genWeight;
                    }
                    else {
                        passnVBFGenSemiLepNoHTobbCtr += 1;
                        //passnVBFGenSemiLepNoHTobbWeightedCtr += *genWeight;
                        
                    }
                }
                else if (ZIsHadronic) {
                    if (HTobbBoolL){
                        passnVBFGenHadCtr += 1;
                        //passnVBFGenHadWeightedCtr += *genWeight;
                    }
                    else {
                        passnVBFGenHadNoHTobbCtr += 1;
                        //passnVBFGenHadNoHTobbWeightedCtr += *genWeight;
                        
                    }
                }
                else {
                    if (HTobbBoolL){
                        passnVBFGenOtherCtr += 1;
                        //passnVBFGenOtherWeightedCtr += *genWeight;
                    }
                    else {
                        passnVBFGenOtherNoHTobbCtr += 1;
                        //passnVBFGenOtherNoHTobbWeightedCtr += *genWeight;

                    }
                }
            }


            //std::cout << evRunOver-1 << "passed\n";
            if (debug){
                std::cout <<"Filling Jets\n";
            }


            //reweighting vectors



            nLHEReweightingWeightL = *nLHEReweightingWeight;
            for (UInt_t nReweightItr=0; nReweightItr<nLHEReweightingWeightL;nReweightItr++){
                LHEReweightingWeightL.push_back(LHEReweightingWeight[nReweightItr]);
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
                FatJet_hadronFlavourL.push_back(FatJet_hadronFlavour[nFatJetItr]);

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
            }

            fixedGridRhoFastjetAllL = *fixedGridRhoFastjetAll;

            FilteredEventsTree->Fill();


            LHEReweightingWeightL.clear();

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

            FatJet_particleNet_HbbvsQCDL.clear();
            FatJet_particleNet_ZvsQCDL.clear();

            FatJet_particleNetMD_QCDL.clear();
            FatJet_particleNetMD_XbbL.clear();
            FatJet_particleNetMD_XccL.clear();
            FatJet_particleNetMD_XqqL.clear();

            FatJet_hadronFlavourL.clear();

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
    std::cout << "passes Flag cut: " << passFlagCtr << " -------------------\n";

    for (unsigned int loopItr = 0; loopItr < C2VNameAr.size(); loopItr++){
        if (loopItr == C2VNameAr.size() - 1) {
            std::cout << "(" << C2VNameAr[loopItr] << "," << passFlagWeightedCtrAr[0][loopItr + 1] << ")\n";
        }
        else std::cout << "(" << C2VNameAr[loopItr] << "," << passFlagWeightedCtrAr[0][loopItr + 1] << "),";
        if (loopItr == 27) {
            std::cout << "(2.0," << passFlagWeightedCtrAr[0][0] << "),";
        }
    }



    std::cout << "passes HLT cut: " << passHLTCtr << " -------------------\n";

    for (unsigned int loopItr = 0; loopItr < C2VNameAr.size(); loopItr++){
        if (loopItr == C2VNameAr.size() - 1) {
            std::cout << "(" << C2VNameAr[loopItr] << "," << passHLTWeightedCtrAr[0][loopItr + 1] << ")\n";
        }
        else std::cout << "(" << C2VNameAr[loopItr] << "," << passHLTWeightedCtrAr[0][loopItr + 1] << "),";
        if (loopItr == 27) {
            std::cout << "(2.0," << passHLTWeightedCtrAr[0][0] << "),";
        }
    }


    std::cout << "passes nFJ cut: " << passnFJCtr << " -------------------\n";

    for (unsigned int loopItr = 0; loopItr < C2VNameAr.size(); loopItr++){
        if (loopItr == C2VNameAr.size() - 1) {
            std::cout << "(" << C2VNameAr[loopItr] << "," << passnFJWeightedCtrAr[0][loopItr + 1] << ")\n";
        }
        else std::cout << "(" << C2VNameAr[loopItr] << "," << passnFJWeightedCtrAr[0][loopItr + 1] << "),";
        if (loopItr == 27) {
            std::cout << "(2.0," << passnFJWeightedCtrAr[0][0] << "),";
        }
    }


    std::cout << "passes nVBF cut: " << passnVBFCtr << " -------------------\n";

    for (unsigned int loopItr = 0; loopItr < C2VNameAr.size(); loopItr++){
        if (loopItr == C2VNameAr.size() - 1) {
            std::cout << "(" << C2VNameAr[loopItr] << "," << passnVBFWeightedCtrAr[0][loopItr + 1] << ")\n";
        }
        else std::cout << "(" << C2VNameAr[loopItr] << "," << passnVBFWeightedCtrAr[0][loopItr + 1] << "),";
        if (loopItr == 27) {
            std::cout << "(2.0," << passnVBFWeightedCtrAr[0][0] << "),";
        }
    }

    
    std::cout << "sumOfGenWeights: " << sumOfGenWeights << "\n";

    if (!isBackground){

        //
        std::vector<string> genHTobbStrAr {""," No HTobb"};
        
        std::vector<string> genCutStrAr {"Flag","HLT","nFJ","nVBF"};

        std::vector<string> genDecayStrAr {"gen lep","gen semilep","gen had","gen other"};

        

        std::vector<UInt_t> genFlagDecayAr {passFlagGenLepCtr,passFlagGenSemiLepCtr,passFlagGenHadCtr,passFlagGenOtherCtr};
        std::vector<UInt_t> genHLTDecayAr {passHLTGenLepCtr,passHLTGenSemiLepCtr,passHLTGenHadCtr,passHLTGenOtherCtr};
        std::vector<UInt_t> gennFJDecayAr {passnFJGenLepCtr,passnFJGenSemiLepCtr,passnFJGenHadCtr,passnFJGenOtherCtr};
        std::vector<UInt_t> gennVBFDecayAr {passnVBFGenLepCtr,passnVBFGenSemiLepCtr,passnVBFGenHadCtr,passnVBFGenOtherCtr};

        std::vector<UInt_t> genFlagDecayNoHTobbAr {passFlagGenLepNoHTobbCtr,passFlagGenSemiLepNoHTobbCtr,passFlagGenHadNoHTobbCtr,passFlagGenOtherNoHTobbCtr};
        std::vector<UInt_t> genHLTDecayNoHTobbAr {passHLTGenLepNoHTobbCtr,passHLTGenSemiLepNoHTobbCtr,passHLTGenHadNoHTobbCtr,passHLTGenOtherNoHTobbCtr};
        std::vector<UInt_t> gennFJDecayNoHTobbAr {passnFJGenLepNoHTobbCtr,passnFJGenSemiLepNoHTobbCtr,passnFJGenHadNoHTobbCtr,passnFJGenOtherNoHTobbCtr};
        std::vector<UInt_t> gennVBFDecayNoHTobbAr {passnVBFGenLepNoHTobbCtr,passnVBFGenSemiLepNoHTobbCtr,passnVBFGenHadNoHTobbCtr,passnVBFGenOtherNoHTobbCtr};

        std::vector<std::vector<UInt_t>> genCutAr {genFlagDecayAr,genHLTDecayAr,gennFJDecayAr,gennVBFDecayAr};

        std::vector<std::vector<UInt_t>> genCutNoHTobbAr {genFlagDecayNoHTobbAr,genHLTDecayNoHTobbAr,gennFJDecayNoHTobbAr,gennVBFDecayNoHTobbAr};

        std::vector<std::vector<std::vector<UInt_t>>> genHTobbAr {genCutAr,genCutNoHTobbAr};

        std::cout << "---------GEN CTRS BELOW---------\n";
        //printing out all the ctrs
        for (unsigned int HTobbItr = 0; HTobbItr < genHTobbAr.size(); HTobbItr++){
            std::cout << genHTobbStrAr[HTobbItr] << "\n";
            for (unsigned int cutItr = 0; cutItr < genHTobbAr[HTobbItr].size(); cutItr++){
                std::cout << "passes " << genCutStrAr[cutItr] << " cut\n";
                for (unsigned int typeItr = 0; typeItr < genHTobbAr[HTobbItr][cutItr].size(); typeItr++){
                    std::cout << genDecayStrAr[typeItr] << " " << genHTobbAr[HTobbItr][cutItr][typeItr] << " ";
                }
                std::cout << "\n";
            }
        }


        
        std::cout << "---------GEN WEIGHTED CTRS BY CHANNEL BELOW---------\n";


        for (unsigned int typeItr = 0; typeItr < typeNameAr.size(); typeItr++) {
            std::cout << typeNameAr[typeItr] << " passes Flag cut:\n";
            for (unsigned int loopItr = 0; loopItr < C2VNameAr.size(); loopItr++) {
                if (loopItr == C2VNameAr.size() - 1) {
                    std::cout << "(" << C2VNameAr[loopItr] << "," << passFlagWeightedCtrAr[typeItr+1][loopItr + 1] << ")\n";
                }
                else std::cout << "(" << C2VNameAr[loopItr] << "," << passFlagWeightedCtrAr[typeItr+1][loopItr + 1] << "),";
                if (loopItr == 27) {
                    std::cout << "(2.0," << passFlagWeightedCtrAr[typeItr+1][0] << "),";
                }
            }
        }

        for (unsigned int typeItr = 0; typeItr < typeNameAr.size(); typeItr++) {
            std::cout << typeNameAr[typeItr] << " passes HLT cut:\n";
            for (unsigned int loopItr = 0; loopItr < C2VNameAr.size(); loopItr++) {
                if (loopItr == C2VNameAr.size() - 1) {
                    std::cout << "(" << C2VNameAr[loopItr] << "," << passHLTWeightedCtrAr[typeItr+1][loopItr + 1] << ")\n";
                }
                else std::cout << "(" << C2VNameAr[loopItr] << "," << passHLTWeightedCtrAr[typeItr+1][loopItr + 1] << "),";
                if (loopItr == 27) {
                    std::cout << "(2.0," << passHLTWeightedCtrAr[typeItr+1][0] << "),";
                }
            }
        }

        for (unsigned int typeItr = 0; typeItr < typeNameAr.size(); typeItr++) {
            std::cout << typeNameAr[typeItr] << " passes nFJ cut:\n";
            for (unsigned int loopItr = 0; loopItr < C2VNameAr.size(); loopItr++) {
                if (loopItr == C2VNameAr.size() - 1) {
                    std::cout << "(" << C2VNameAr[loopItr] << "," << passnFJWeightedCtrAr[typeItr+1][loopItr + 1] << ")\n";
                }
                else std::cout << "(" << C2VNameAr[loopItr] << "," << passnFJWeightedCtrAr[typeItr+1][loopItr + 1] << "),";
                if (loopItr == 27) {
                    std::cout << "(2.0," << passnFJWeightedCtrAr[typeItr+1][0] << "),";
                }
            }
        }

        for (unsigned int typeItr = 0; typeItr < typeNameAr.size(); typeItr++) {
            std::cout << typeNameAr[typeItr] << " passes nVBF cut:\n";
            for (unsigned int loopItr = 0; loopItr < C2VNameAr.size(); loopItr++) {
                if (loopItr == C2VNameAr.size() - 1) {
                    std::cout << "(" << C2VNameAr[loopItr] << "," << passnVBFWeightedCtrAr[typeItr+1][loopItr + 1] << ")\n";
                }
                else std::cout << "(" << C2VNameAr[loopItr] << "," << passnVBFWeightedCtrAr[typeItr+1][loopItr + 1] << "),";
                if (loopItr == 27) {
                    std::cout << "(2.0," << passnVBFWeightedCtrAr[typeItr+1][0] << "),";
                }
            }
        }

        

        


        std::cout << "HTobb Channel: " << HTobbCtr << " ------------------- \n";
        std::cout << "Channels with HTobb\n";
        std::cout << "Gen Lep Channel: " << genLepChannelCtr << " ------------------- \n";
        std::cout << "Gen SemiLep Channel: " << genSemiLepChannelCtr << " ------------------- \n";
        std::cout << "Gen Hadronic Channel: " << genHadronicChannelCtr << " ------------------- \n";
        std::cout << "Gen Other Channel: " << genOtherChannelCtr << " ------------------- \n";
        std::cout << "Gen Error Channel: " << genErrorChannelCtr << " ------------------- \n";
        std::cout << "Channels without HTobb\n";
        std::cout << "Gen NoHTobb Lep Channel: " << genLepChannelNoHTobbCtr << " ------------------- \n";
        std::cout << "Gen NoHTobb SemiLep Channel: " << genSemiLepChannelNoHTobbCtr << " ------------------- \n";
        std::cout << "Gen NoHTobb Hadronic Channel: " << genHadronicChannelNoHTobbCtr << " ------------------- \n";
        std::cout << "Gen NoHTobb Other Channel: " << genOtherChannelNoHTobbCtr << " ------------------- \n";
        std::cout << "Gen NoHTobb Error Channel: " << genErrorChannelNoHTobbCtr << " ------------------- \n";

        std::cout << "---------Gen channel weighted ctrs below---------\n";

        for (unsigned int typeItr = 0; typeItr < typeNameAltAr.size(); typeItr++) {
            std::cout << typeNameAltAr[typeItr] << " ctr\n";
            for (unsigned int loopItr = 0; loopItr < C2VNameAr.size(); loopItr++) {
                if (loopItr == C2VNameAr.size() - 1) {
                    std::cout << "(" << C2VNameAr[loopItr] << "," << genChannelWeightedCtrAr[typeItr][loopItr + 1] << ")\n";
                }
                else std::cout << "(" << C2VNameAr[loopItr] << "," << genChannelWeightedCtrAr[typeItr][loopItr + 1] << "),";
                if (loopItr == 27) {
                    std::cout << "(2.0," << genChannelWeightedCtrAr[typeItr][0] << "),";
                }
            }
        }
        
        
        std::cout << "Cross section average before division: " << crossSectionAvg << "\n";
        std::cout << "Cross section counter: " << crossSectionCtr << "\n";
        crossSectionAvg = (crossSectionAvg*hTobbBR) / crossSectionCtr;
        std::cout << "Cross section average after division and hTobb branching ratio: " << crossSectionAvg << "\n";
        std::cout << "Tot Weight: " << totCrossSectionWeight <<"\n";
        std::cout << "Tot XS Count: " << totCrossSectionEvCount <<"\n";
        float crossSectionAvgAlt = totCrossSectionWeight/totCrossSectionEvCount;
        std::cout << "(Tot Weight*hTobbBR)/Tot XS Count: " << crossSectionAvgAlt*hTobbBR <<"\n";
        //XS Tree
        float crossSectionVar;
        TTree* crossSectionTree = new TTree("crossSectionTree","crossSectionTree");
        crossSectionTree->Branch("crossSectionVar",&crossSectionVar,"crossSectionVar/F");
        //crossSectionVar = crossSectionAvg;
        crossSectionVar = crossSectionAvgAlt*hTobbBR;
        crossSectionTree->Fill();
        crossSectionTree->Write("",TObject::kOverwrite);
    }

    outFile->cd();
    evNumTree->Write("",TObject::kOverwrite);
    FilteredEventsTree->Write("",TObject::kOverwrite);
    genTree->Write("",TObject::kOverwrite);
    genHadFJTree->Write("",TObject::kOverwrite);
    genSemiLepFJTree->Write("",TObject::kOverwrite);
    genLepFJTree->Write("",TObject::kOverwrite);
    genHadTree->Write("",TObject::kOverwrite);
    genSemiLepTree->Write("",TObject::kOverwrite);
    genLepTree->Write("",TObject::kOverwrite);

    outFile->Close();
}
