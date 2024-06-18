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


void DoTrimmed042024WWHHLTFilterOnReweighting2016BeforeAnalysis(UInt_t fileInd, string datasetString){
    // Open the file. Note that the name of your file outside this class
    // will probably NOT be experiment.root.
    std::cout << "start\n";
    clock_t startt = clock();

    if (datasetString == "testRun") testRun = true;
    if (datasetString == "SDC2V2MCWWHSS16Reweight") SDC2V2MCWWHSS16Reweight = true;
    if (datasetString == "SDC2V2MCWWHSS16APVReweight") SDC2V2MCWWHSS16APVReweight = true;
    if (datasetString == "SDC2V2MCWWHOS16Reweight") SDC2V2MCWWHOS16Reweight = true;
    if (datasetString == "SDC2V2MCWWHOS16APVReweight") SDC2V2MCWWHOS16APVReweight = true;
    if (datasetString == "MaC2V2MCWWHSS16Reweight") MaC2V2MCWWHSS16Reweight = true;
    if (datasetString == "MaC2V2MCWWHSS16APVReweight") MaC2V2MCWWHSS16APVReweight = true;
    if (datasetString == "MaC2V2MCWWHOS16Reweight") MaC2V2MCWWHOS16Reweight = true;
    if (datasetString == "MaC2V2MCWWHOS16APVReweight") MaC2V2MCWWHOS16APVReweight = true;
    if (datasetString == "CenC2V2MCWWHSS16Reweight") CenC2V2MCWWHSS16Reweight = true;
    if (datasetString == "CenC2V2MCWWHSS16APVReweight") CenC2V2MCWWHSS16APVReweight = true;
    if (datasetString == "CenC2V2MCWWHOS16Reweight") CenC2V2MCWWHOS16Reweight = true;
    if (datasetString == "CenC2V2MCWWHOS16APVReweight") CenC2V2MCWWHOS16APVReweight = true;
    //Analyzer will run over all files put into fileAr

    std::vector<std::string> fileAr;

    std::string saveName;
    float crossSection;
    bool isBackground;
    bool isMariaSignal = false;

    ////////////////////////////////GETTING DATASET////////////////////////////////
    ////////////////////////////////GETTING DATASET////////////////////////////////
    ////////////////////////////////GETTING DATASET////////////////////////////////
    ////////////////////////////////GETTING DATASET////////////////////////////////

    std::string strAdd;
    if (scratchDown) strAdd ="/afs/crc.nd.edu/user/d/dlutton/FROM_PANASAS";
    else strAdd ="/scratch365";

    if (SDC2V2MCWWHSS16Reweight){
        saveName = "SDC2V2MCWWHSS16Reweight";
        isBackground = false;
        int arrSize = sizeof(SDC2V2MCWWHSS16ReweightAr)/sizeof(SDC2V2MCWWHSS16ReweightAr[0]);
        std::string tmpStrWithPath = SDC2V2MCWWHSS16ReweightAr[fileInd];
        fileAr.push_back(tmpStrWithPath);
        
    }
    else if (SDC2V2MCWWHSS16APVReweight){
        saveName = "SDC2V2MCWWHSS16APVReweight";
        isBackground = false;
        int arrSize = sizeof(SDC2V2MCWWHSS16APVReweightAr)/sizeof(SDC2V2MCWWHSS16APVReweightAr[0]);
        std::string tmpStrWithPath = SDC2V2MCWWHSS16APVReweightAr[fileInd];
        fileAr.push_back(tmpStrWithPath);
        
    }
    else if (SDC2V2MCWWHOS16Reweight){
        saveName = "SDC2V2MCWWHOS16Reweight";
        isBackground = false;
        int arrSize = sizeof(SDC2V2MCWWHOS16ReweightAr)/sizeof(SDC2V2MCWWHOS16ReweightAr[0]);
        std::string tmpStrWithPath = SDC2V2MCWWHOS16ReweightAr[fileInd];
        fileAr.push_back(tmpStrWithPath);
        
    }
    else if (SDC2V2MCWWHOS16APVReweight){
        saveName = "SDC2V2MCWWHOS16APVReweight";
        isBackground = false;
        int arrSize = sizeof(SDC2V2MCWWHOS16APVReweightAr)/sizeof(SDC2V2MCWWHOS16APVReweightAr[0]);
        std::string tmpStrWithPath = SDC2V2MCWWHOS16APVReweightAr[fileInd];
        fileAr.push_back(tmpStrWithPath);
        
    }
    else if (MaC2V2MCWWHSS16Reweight){
        isMariaSignal = true;
        saveName = "MaC2V2MCWWHSS16Reweight";
        isBackground = false;
        int arrSize = sizeof(MaC2V2MCWWHSS16ReweightAr)/sizeof(MaC2V2MCWWHSS16ReweightAr[0]);
        std::string tmpStrWithPath = MaC2V2MCWWHSS16ReweightAr[fileInd];
        fileAr.push_back(tmpStrWithPath);
        
    }
    else if (MaC2V2MCWWHSS16APVReweight){
        isMariaSignal = true;
        saveName = "MaC2V2MCWWHSS16APVReweight";
        isBackground = false;
        int arrSize = sizeof(MaC2V2MCWWHSS16APVReweightAr)/sizeof(MaC2V2MCWWHSS16APVReweightAr[0]);
        std::string tmpStrWithPath = MaC2V2MCWWHSS16APVReweightAr[fileInd];
        fileAr.push_back(tmpStrWithPath);
        
    }
    else if (MaC2V2MCWWHOS16Reweight){
        isMariaSignal = true;
        saveName = "MaC2V2MCWWHOS16Reweight";
        isBackground = false;
        int arrSize = sizeof(MaC2V2MCWWHOS16ReweightAr)/sizeof(MaC2V2MCWWHOS16ReweightAr[0]);
        std::string tmpStrWithPath = MaC2V2MCWWHOS16ReweightAr[fileInd];
        fileAr.push_back(tmpStrWithPath);
        
    }
    else if (MaC2V2MCWWHOS16APVReweight){
        isMariaSignal = true;
        saveName = "MaC2V2MCWWHOS16APVReweight";
        isBackground = false;
        int arrSize = sizeof(MaC2V2MCWWHOS16APVReweightAr)/sizeof(MaC2V2MCWWHOS16APVReweightAr[0]);
        std::string tmpStrWithPath = MaC2V2MCWWHOS16APVReweightAr[fileInd];
        fileAr.push_back(tmpStrWithPath);
        
    }
    else if (CenC2V2MCWWHSS16Reweight){
        saveName = "CenC2V2MCWWHSS16Reweight";
        isBackground = false;
        int arrSize = sizeof(CenC2V2MCWWHSS16ReweightAr)/sizeof(CenC2V2MCWWHSS16ReweightAr[0]);
        std::string tmpStrWithPath = CenC2V2MCWWHSS16ReweightAr[fileInd];
        fileAr.push_back(tmpStrWithPath);
        
    }
    else if (CenC2V2MCWWHSS16APVReweight){
        saveName = "CenC2V2MCWWHSS16APVReweight";
        isBackground = false;
        int arrSize = sizeof(CenC2V2MCWWHSS16APVReweightAr)/sizeof(CenC2V2MCWWHSS16APVReweightAr[0]);
        std::string tmpStrWithPath = CenC2V2MCWWHSS16APVReweightAr[fileInd];
        fileAr.push_back(tmpStrWithPath);
        
    }
    else if (CenC2V2MCWWHOS16Reweight){
        saveName = "CenC2V2MCWWHOS16Reweight";
        isBackground = false;
        int arrSize = sizeof(CenC2V2MCWWHOS16ReweightAr)/sizeof(CenC2V2MCWWHOS16ReweightAr[0]);
        std::string tmpStrWithPath = CenC2V2MCWWHOS16ReweightAr[fileInd];
        fileAr.push_back(tmpStrWithPath);
        
    }
    else if (CenC2V2MCWWHOS16APVReweight){
        saveName = "CenC2V2MCWWHOS16APVReweight";
        isBackground = false;
        int arrSize = sizeof(CenC2V2MCWWHOS16APVReweightAr)/sizeof(CenC2V2MCWWHOS16APVReweightAr[0]);
        std::string tmpStrWithPath = CenC2V2MCWWHOS16APVReweightAr[fileInd];
        fileAr.push_back(tmpStrWithPath);
        
    }
    else if (testRun){
        saveName = "testRun";
        //fileAr.push_back("./unweighted_eventspphzzjjQCD0SMHLOOP0NPE1NPcHWE1QEDE5ResMasAllVer100Ev10080Seed_0p999cHW100GeVIMJetCut_200.root");
        fileAr.push_back("./merged18.root");
        isBackground = false;
        
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
    bool checkChannelSplits;
    if (isBackground){
        checkChannelSplits = false;
    }

    ////////////////////////////////DEFINING TREES////////////////////////////////
    ////////////////////////////////DEFINING TREES////////////////////////////////
    ////////////////////////////////DEFINING TREES////////////////////////////////
    ////////////////////////////////DEFINING TREES////////////////////////////////

    std::vector<std::string> C2VNameMaAr {"C2W_m2p0_C2Z_m2p0","C2W_m2p0_C2Z_m1p0","C2W_m2p0_C2Z_m0p5","C2W_m2p0_C2Z_0p0","C2W_m2p0_C2Z_0p5","C2W_m2p0_C2Z_1p0","C2W_m2p0_C2Z_1p5","C2W_m2p0_C2Z_2p0","C2W_m2p0_C2Z_2p5","C2W_m2p0_C2Z_3p0","C2W_m2p0_C2Z_4p0","C2W_m1p0_C2Z_m2p0","C2W_m1p0_C2Z_m1p0","C2W_m1p0_C2Z_m0p5","C2W_m1p0_C2Z_0p0","C2W_m1p0_C2Z_0p5","C2W_m1p0_C2Z_1p0","C2W_m1p0_C2Z_1p5","C2W_m1p0_C2Z_2p0","C2W_m1p0_C2Z_2p5","C2W_m1p0_C2Z_3p0","C2W_m1p0_C2Z_4p0","C2W_m0p5_C2Z_m2p0","C2W_m0p5_C2Z_m1p0","C2W_m0p5_C2Z_m0p5","C2W_m0p5_C2Z_0p0","C2W_m0p5_C2Z_0p5","C2W_m0p5_C2Z_1p0","C2W_m0p5_C2Z_1p5","C2W_m0p5_C2Z_2p0","C2W_m0p5_C2Z_2p5","C2W_m0p5_C2Z_3p0","C2W_m0p5_C2Z_4p0","C2W_0p0_C2Z_m2p0","C2W_0p0_C2Z_m1p0","C2W_0p0_C2Z_m0p5","C2W_0p0_C2Z_0p0","C2W_0p0_C2Z_0p5","C2W_0p0_C2Z_1p0","C2W_0p0_C2Z_1p5","C2W_0p0_C2Z_2p0","C2W_0p0_C2Z_2p5","C2W_0p0_C2Z_3p0","C2W_0p0_C2Z_4p0","C2W_0p5_C2Z_m2p0","C2W_0p5_C2Z_m1p0","C2W_0p5_C2Z_m0p5","C2W_0p5_C2Z_0p0","C2W_0p5_C2Z_0p5","C2W_0p5_C2Z_1p0","C2W_0p5_C2Z_1p5","C2W_0p5_C2Z_2p0","C2W_0p5_C2Z_2p5","C2W_0p5_C2Z_3p0","C2W_0p5_C2Z_4p0","C2W_1p0_C2Z_m2p0","C2W_1p0_C2Z_m1p0","C2W_1p0_C2Z_m0p5","C2W_1p0_C2Z_0p0","C2W_1p0_C2Z_0p5","C2W_1p0_C2Z_1p0","C2W_1p0_C2Z_1p5","C2W_1p0_C2Z_2p0","C2W_1p0_C2Z_2p5","C2W_1p0_C2Z_3p0","C2W_1p0_C2Z_4p0","C2W_1p5_C2Z_m2p0","C2W_1p5_C2Z_m1p0","C2W_1p5_C2Z_m0p5","C2W_1p5_C2Z_0p0","C2W_1p5_C2Z_0p5","C2W_1p5_C2Z_1p0","C2W_1p5_C2Z_1p5","C2W_1p5_C2Z_2p0","C2W_1p5_C2Z_2p5","C2W_1p5_C2Z_3p0","C2W_1p5_C2Z_4p0","C2W_2p0_C2Z_m2p0","C2W_2p0_C2Z_m1p0","C2W_2p0_C2Z_m0p5","C2W_2p0_C2Z_0p0","C2W_2p0_C2Z_0p5","C2W_2p0_C2Z_1p0","C2W_2p0_C2Z_1p5","C2W_2p0_C2Z_2p5","C2W_2p0_C2Z_3p0","C2W_2p0_C2Z_4p0","C2W_2p5_C2Z_m2p0","C2W_2p5_C2Z_m1p0","C2W_2p5_C2Z_m0p5","C2W_2p5_C2Z_0p0","C2W_2p5_C2Z_0p5","C2W_2p5_C2Z_1p0","C2W_2p5_C2Z_1p5","C2W_2p5_C2Z_2p0","C2W_2p5_C2Z_2p5","C2W_2p5_C2Z_3p0","C2W_2p5_C2Z_4p0","C2W_3p0_C2Z_m2p0","C2W_3p0_C2Z_m1p0","C2W_3p0_C2Z_m0p5","C2W_3p0_C2Z_0p0","C2W_3p0_C2Z_0p5","C2W_3p0_C2Z_1p0","C2W_3p0_C2Z_1p5","C2W_3p0_C2Z_2p0","C2W_3p0_C2Z_2p5","C2W_3p0_C2Z_3p0","C2W_3p0_C2Z_4p0","C2W_4p0_C2Z_m2p0","C2W_4p0_C2Z_m1p0","C2W_4p0_C2Z_m0p5","C2W_4p0_C2Z_0p0","C2W_4p0_C2Z_0p5","C2W_4p0_C2Z_1p0","C2W_4p0_C2Z_1p5","C2W_4p0_C2Z_2p0","C2W_4p0_C2Z_2p5","C2W_4p0_C2Z_3p0","C2W_4p0_C2Z_4p0"};
    std::vector<std::string> C2VNameAr {"-2.0","-1.75","-1.5","-1.25","-1.0","-0.75","-0.5","-0.25","0.0","0.1","0.2","0.3","0.4","0.5","0.6","0.7","0.8","0.9","1.0","1.1","1.2","1.3","1.4","1.5","1.6","1.7","1.8","1.9","2.25","2.5","2.75","3.0","3.25","3.5","3.75","4.0"};
    std::vector<std::string> typeNameMaAr {"LWLepTWLep","LWLepTWHadronic","LWHadronicTWLep","LWHadronicTWHadronic","GenOther","LWLepTWLep NoHTobb","LWLepTWHadronic NoHTobb","LWHadronicTWLep NoHTobb","LWHadronicTWHadronic NoHTobb","GenOther NoHTobb"};
    uint C2VLen = 37;
    uint C2VMaLen = 121;
    if (isMariaSignal) C2VLen = C2VMaLen;
    std::vector<Double_t> zeroVec(C2VLen,0.0);

    if (isMariaSignal) {
        C2VNameAr = C2VNameMaAr;
    }
    std::vector<Double_t> passFlagWeightedCtrAr(zeroVec);
    std::vector<Double_t> passHLTWeightedCtrAr(zeroVec);
    std::vector<Double_t> passnFJWeightedCtrAr(zeroVec);
    std::vector<Double_t> passnVBFWeightedCtrAr(zeroVec);

    

    UInt_t passFlagCtr = 0;
    UInt_t passHLTCtr = 0;
    UInt_t passnFJCtr = 0;
    UInt_t passnVBFCtr = 0;



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
    std::vector<Int_t> Jet_hadronFlavourL;
    std::vector<Int_t> Jet_genJetIdxL;
    std::vector<Float_t> Jet_btagDeepFlavBL;
    Float_t fixedGridRhoFastjetAllL;

    //GenJets
    UInt_t nGenJetL;
    std::vector<Float_t> GenJet_etaL;
    std::vector<Float_t> GenJet_ptL;
    std::vector<Float_t> GenJet_phiL;
    std::vector<Float_t> GenJet_massL;
    std::vector<UChar_t> GenJet_hadronFlavourL;
    
    //GenJetAK8
    UInt_t nGenJetAK8L;
    std::vector<Float_t> GenJetAK8_etaL;
    std::vector<Float_t> GenJetAK8_ptL;
    std::vector<Float_t> GenJetAK8_phiL;
    std::vector<Float_t> GenJetAK8_massL;
    std::vector<UChar_t> GenJetAK8_hadronFlavourL;

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
    std::vector<Int_t> Muon_genPartIdxL;

    //ParticleNet
    std::vector<Float_t> FatJet_particleNet_HbbvsQCDL;
    std::vector<Float_t> FatJet_particleNet_ZvsQCDL;
    std::vector<Float_t> FatJet_particleNetMD_QCDL;
    std::vector<Float_t> FatJet_particleNetMD_XbbL;
    std::vector<Float_t> FatJet_particleNetMD_XccL;
    std::vector<Float_t> FatJet_particleNetMD_XqqL;

    //Gen Particles

    UInt_t nGenPartL;
    std::vector<Float_t> GenPart_etaL;
    std::vector<Float_t> GenPart_massL;
    std::vector<Float_t> GenPart_phiL;
    std::vector<Float_t> GenPart_ptL;
    std::vector<Int_t> GenPart_genPartIdxMotherL;
    std::vector<Int_t> GenPart_pdgIdL;
    std::vector<Int_t> GenPart_statusL;
    std::vector<Int_t> GenPart_statusFlagsL;

    //genChannel characterization
    //0=Leptonic,1=Semi-leptonic,2=Hadronic,3=Other,4=Error
    UInt_t genChannelL;

    Bool_t HTobbBoolL;

    //FJ GENMATCH
    //THESE BRANCHES CURRENTLY SET TO DEFAULT VALUES
    //ONLY INCLUDED TO MAKE COMPATIBLE WITH ZZH ANALYSIS CODE

    Int_t ZFJIndL;
    Int_t HFJIndL;
    Bool_t goodGenZFJMatchL;
    Bool_t goodGenHFJMatchL;
    Bool_t goodZFJMatchToGenL;
    Bool_t goodHFJMatchToGenL;
    Bool_t eventGenSemileptonicL;
    Bool_t eventGenHToBBL;
    Int_t ZFJGenHadronFlavourL;
    Int_t HFJGenHadronFlavourL;
    std::vector<Int_t> FatJet_hadronFlavourL;

    UInt_t nHDecayPIDL;
    std::vector<Int_t> HDecayPIDL;
    UInt_t nZOneDecayPIDL;
    std::vector<Int_t> ZOneDecayPIDL;
    UInt_t nZTwoDecayPIDL;
    std::vector<Int_t> ZTwoDecayPIDL;
    Int_t ZOneTypeL; //0=Leptonic,1=Hadronic,2=Other
    Int_t ZTwoTypeL;


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

    //change 2018 to IsoMu24 and remove DZ from diele trigger
    Bool_t HLT_IsoMu24L;
    Bool_t HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVLL;

    //2016 in other years just set these to false
    Bool_t HLT_IsoTkMu24L;

    //042024SFAndSuchAdditions
    //PU JetID
    std::vector<Int_t> Jet_puIdL;
    //L1 Prefiring Weights
    Float_t L1PreFiringWeight_NomL;
    Float_t L1PreFiringWeight_DnL;
    Float_t L1PreFiringWeight_UpL;
    //PileUp number of interactions
    Float_t Pileup_nTrueIntL;
    Int_t Pileup_nPUL;
    //PSWeight
    UInt_t nPSWeightL;
    std::vector<Float_t> PSWeightL;
    //LHE Scale Weight
    UInt_t nLHEScaleWeightL;
    std::vector<Float_t> LHEScaleWeightL;
    //LHE PDF Weight
    UInt_t nLHEPdfWeightL;
    std::vector<Float_t> LHEPdfWeightL;
    Float_t LHEWeight_originalXWGTUPL;
    //generator weight
    Float_t Generator_weightL;

    //05052024 Additions for PN regress mass scaling and resolution corrections
    UInt_t luminosityBlockL;
    ULong64_t eventL;

    

    
    
    


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
    FilteredEventsTree->Branch("Jet_hadronFlavourL",&Jet_hadronFlavourL);
    FilteredEventsTree->Branch("Jet_genJetIdxL",&Jet_genJetIdxL);
    FilteredEventsTree->Branch("Jet_btagDeepFlavBL",&Jet_btagDeepFlavBL);
    FilteredEventsTree->Branch("fixedGridRhoFastjetAllL",&fixedGridRhoFastjetAllL,"fixedGridRhoFastjetAllL/F");

    //GenJets
    FilteredEventsTree->Branch("nGenJetL",&nGenJetL,"nGenJetL/i");
    FilteredEventsTree->Branch("GenJet_etaL",&GenJet_etaL);
    FilteredEventsTree->Branch("GenJet_ptL",&GenJet_ptL);
    FilteredEventsTree->Branch("GenJet_phiL",&GenJet_phiL);
    FilteredEventsTree->Branch("GenJet_massL",&GenJet_massL);
    FilteredEventsTree->Branch("GenJet_hadronFlavourL",&GenJet_hadronFlavourL);

    //GenJetAK8
    FilteredEventsTree->Branch("nGenJetAK8L",&nGenJetAK8L,"nGenJetAK8L/i");
    FilteredEventsTree->Branch("GenJetAK8_etaL",&GenJetAK8_etaL);
    FilteredEventsTree->Branch("GenJetAK8_ptL",&GenJetAK8_ptL);
    FilteredEventsTree->Branch("GenJetAK8_phiL",&GenJetAK8_phiL);
    FilteredEventsTree->Branch("GenJetAK8_massL",&GenJetAK8_massL);
    FilteredEventsTree->Branch("GenJetAK8_hadronFlavourL",&GenJetAK8_hadronFlavourL);

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
    FilteredEventsTree->Branch("Muon_genPartIdxL",&Muon_genPartIdxL);

    //ParticleNet
    FilteredEventsTree->Branch("FatJet_particleNet_HbbvsQCDL",&FatJet_particleNet_HbbvsQCDL);
    FilteredEventsTree->Branch("FatJet_particleNet_ZvsQCDL",&FatJet_particleNet_ZvsQCDL);
    FilteredEventsTree->Branch("FatJet_particleNetMD_QCDL", &FatJet_particleNetMD_QCDL);
    FilteredEventsTree->Branch("FatJet_particleNetMD_XbbL", &FatJet_particleNetMD_XbbL);
    FilteredEventsTree->Branch("FatJet_particleNetMD_XccL", &FatJet_particleNetMD_XccL);
    FilteredEventsTree->Branch("FatJet_particleNetMD_XqqL", &FatJet_particleNetMD_XqqL);

    //Gen Particles
    FilteredEventsTree->Branch("nGenPartL",&nGenPartL,"nGenPartL/i");
    FilteredEventsTree->Branch("GenPart_etaL",&GenPart_etaL);
    FilteredEventsTree->Branch("GenPart_massL",&GenPart_massL);
    FilteredEventsTree->Branch("GenPart_phiL",&GenPart_phiL);
    FilteredEventsTree->Branch("GenPart_ptL",&GenPart_ptL);
    FilteredEventsTree->Branch("GenPart_genPartIdxMotherL",&GenPart_genPartIdxMotherL);
    FilteredEventsTree->Branch("GenPart_pdgIdL",&GenPart_pdgIdL);
    FilteredEventsTree->Branch("GenPart_statusL",&GenPart_statusL);
    FilteredEventsTree->Branch("GenPart_statusFlagsL",&GenPart_statusFlagsL);

    //genChannel characterization
    //0=Leptonic,1=Semi-leptonic,2=Hadronic,3=Other,4=Error
    FilteredEventsTree->Branch("genChannelL",&genChannelL,"genChannelL/i");

    FilteredEventsTree->Branch("HTobbBoolL",&HTobbBoolL,"HTobbBoolL/O");

    FilteredEventsTree->Branch("ZFJIndL",&ZFJIndL,"ZFJIndL/I");
    FilteredEventsTree->Branch("HFJIndL",&HFJIndL,"HFJIndL/I");
    FilteredEventsTree->Branch("goodGenZFJMatchL",&goodGenZFJMatchL,"goodGenZFJMatchL/O");
    FilteredEventsTree->Branch("goodGenHFJMatchL",&goodGenHFJMatchL,"goodGenHFJMatchL/O");
    FilteredEventsTree->Branch("goodZFJMatchToGenL",&goodZFJMatchToGenL,"goodZFJMatchToGenL/O");
    FilteredEventsTree->Branch("goodHFJMatchToGenL",&goodHFJMatchToGenL,"goodHFJMatchToGenL/O");
    FilteredEventsTree->Branch("eventGenSemileptonicL",&eventGenSemileptonicL,"eventGenSemileptonicL/O");
    FilteredEventsTree->Branch("eventGenHToBBL",&eventGenHToBBL,"eventGenHToBBL/O");

    FilteredEventsTree->Branch("ZFJGenHadronFlavourL",&ZFJGenHadronFlavourL,"ZFJGenHadronFlavourL/I");
    FilteredEventsTree->Branch("HFJGenHadronFlavourL",&HFJGenHadronFlavourL,"HFJGenHadronFlavourL/I");
    FilteredEventsTree->Branch("FatJet_hadronFlavourL",&FatJet_hadronFlavourL);

    FilteredEventsTree->Branch("nHDecayPIDL",&nHDecayPIDL,"nHDecayPIDL/i");
    FilteredEventsTree->Branch("HDecayPIDL",&HDecayPIDL);

    FilteredEventsTree->Branch("nZOneDecayPIDL",&nZOneDecayPIDL,"nZOneDecayPIDL/i");
    FilteredEventsTree->Branch("ZOneDecayPIDL",&ZOneDecayPIDL);
    FilteredEventsTree->Branch("nZTwoDecayPIDL",&nZTwoDecayPIDL,"nZTwoDecayPIDL/i");
    FilteredEventsTree->Branch("ZTwoDecayPIDL",&ZTwoDecayPIDL);

    FilteredEventsTree->Branch("ZOneTypeL",&ZOneTypeL,"ZOneTypeL/I");
    FilteredEventsTree->Branch("ZTwoTypeL",&ZTwoTypeL,"ZTwoTypeL/I");


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
    //L1 Prefiring Weights
    FilteredEventsTree->Branch("L1PreFiringWeight_NomL",&L1PreFiringWeight_NomL,"L1PreFiringWeight_NomL/F");
    FilteredEventsTree->Branch("L1PreFiringWeight_DnL",&L1PreFiringWeight_DnL,"L1PreFiringWeight_DnL/F");
    FilteredEventsTree->Branch("L1PreFiringWeight_UpL",&L1PreFiringWeight_UpL,"L1PreFiringWeight_UpL/F");
    //PileUp number of interactions
    FilteredEventsTree->Branch("Pileup_nTrueIntL",&Pileup_nTrueIntL,"Pileup_nTrueIntL/F");
    FilteredEventsTree->Branch("Pileup_nPUL",&Pileup_nPUL,"Pileup_nPUL/I");
    //PSWeight
    FilteredEventsTree->Branch("nPSWeightL",&nPSWeightL,"nPSWeightL/i");
    FilteredEventsTree->Branch("PSWeightL",&PSWeightL);
    //LHE Scale Weight
    FilteredEventsTree->Branch("nLHEScaleWeightL",&nLHEScaleWeightL,"nLHEScaleWeightL/i");
    FilteredEventsTree->Branch("LHEScaleWeightL",&LHEScaleWeightL);
    //LHE PDF Weight
    FilteredEventsTree->Branch("nLHEPdfWeightL",&nLHEPdfWeightL,"nLHEPdfWeightL/i");
    FilteredEventsTree->Branch("LHEPdfWeightL",&LHEPdfWeightL);
    FilteredEventsTree->Branch("LHEWeight_originalXWGTUPL",&LHEWeight_originalXWGTUPL,"LHEWeight_originalXWGTUPL/F");
    //generator weight
    FilteredEventsTree->Branch("Generator_weightL",&Generator_weightL,"Generator_weightL/F");

    //05052024 Additions for PN regress mass scaling and resolution corrections
    FilteredEventsTree->Branch("luminosityBlockL",&luminosityBlockL,"luminosityBlockL/i");
    FilteredEventsTree->Branch("eventL",&eventL,"eventL/l");


    //GenTree

    //EventReweighting
    UInt_t nLHEReweightingWeightGenL;
    std::vector<Float_t> LHEReweightingWeightGenL;

    //Gen dR of H from Z particles
    Double_t HdRFromLeadWL;
    Double_t HdRFromTrailingWL;
    Double_t leadWdRFromTrailingWL;

    TTree *genTree = new TTree("genTree", "genTree");


    genTree->Branch("nLHEReweightingWeightGenL",&nLHEReweightingWeightGenL,"nLHEReweightingWeightGenL/i");
    genTree->Branch("LHEReweightingWeightGenL",&LHEReweightingWeightGenL);
    genTree->Branch("HdRFromLeadWL",&HdRFromLeadWL,"HdRFromLeadWL/D");
    genTree->Branch("HdRFromTrailingWL",&HdRFromTrailingWL,"HdRFromTrailingWL/D");
    genTree->Branch("leadWdRFromTrailingWL",&leadWdRFromTrailingWL,"leadWdRFromTrailingWL/D");

    //Whole Run Tree
    UInt_t nLHEPdfSumwL;
    std::vector<Double_t> LHEPdfSumwL;
    UInt_t nLHEScaleSumwL;
    std::vector<Double_t> LHEScaleSumwL;
    UInt_t nLHEReweightingSumwL;
    std::vector<Double_t> LHEReweightingSumwL;
    Long64_t genEventCountL;
    Double_t genEventSumwL;
    Double_t genEventSumw2L;
    UInt_t runL;
    

    TTree *runTree = new TTree("runTree", "runTree");

    runTree->Branch("nLHEPdfSumwL",&nLHEPdfSumwL,"nLHEPdfSumwL/i");
    runTree->Branch("LHEPdfSumwL",&LHEPdfSumwL);
    runTree->Branch("nLHEScaleSumwL",&nLHEScaleSumwL,"nLHEScaleSumwL/i");
    runTree->Branch("LHEScaleSumwL",&LHEScaleSumwL);
    runTree->Branch("nLHEReweightingSumwL",&nLHEReweightingSumwL,"nLHEReweightingSumwL/i");
    runTree->Branch("LHEReweightingSumwL",&LHEReweightingSumwL);
    runTree->Branch("genEventCountL",&genEventCountL,"genEventCountL/L");
    runTree->Branch("genEventSumwL",&genEventSumwL,"genEventSumwL/D");
    runTree->Branch("genEventSumw2L",&genEventSumw2L,"genEventSumw2L/D");
    runTree->Branch("runL",&runL,"runL/i");

    //Weight sums tree
    Float_t Generator_weightSumL;
    UInt_t nLHEPdfWeightSumL;
    std::vector<Float_t> LHEPdfWeightSumL;
    UInt_t nLHEReweightingWeightSumL;
    std::vector<Float_t> LHEReweightingWeightSumL;
    Float_t LHEWeight_originalXWGTUPSumL;
    Float_t genWeightSumL;

    TTree *weightSumsTree = new TTree("weightSumsTree", "weightSumsTree");

    weightSumsTree->Branch("Generator_weightSumL",&Generator_weightSumL,"Generator_weightSumL/F");
    weightSumsTree->Branch("nLHEPdfWeightSumL",&nLHEPdfWeightSumL,"nLHEPdfWeightSumL/i");
    weightSumsTree->Branch("LHEPdfWeightSumL",&LHEPdfWeightSumL);
    weightSumsTree->Branch("nLHEReweightingWeightSumL",&nLHEReweightingWeightSumL,"nLHEReweightingWeightSumL/i");
    weightSumsTree->Branch("LHEReweightingWeightSumL",&LHEReweightingWeightSumL);
    weightSumsTree->Branch("LHEWeight_originalXWGTUPSumL",&LHEWeight_originalXWGTUPSumL,"LHEWeight_originalXWGTUPSumL/F");
    weightSumsTree->Branch("genWeightSumL",&genWeightSumL,"genWeightSumL/F");

    float tmpGenerator_weightSum = 0;
    uint tmpnLHEPdfWeightSum = 101;
    //size of 101 is hardcoded in the LHEPdfWeight branch
    std::vector<Float_t> tmpLHEPdfWeightSum(tmpnLHEPdfWeightSum,0.0);
    uint tmpnLHEReweightingWeightMaSum = 120;
    uint tmpnLHEReweightingWeightSum = 36;
    if (isMariaSignal) tmpnLHEReweightingWeightSum = tmpnLHEReweightingWeightMaSum;
    //size of 36 is hardcoded in the LHEReweightingWeight branch
    std::vector<Float_t> tmpLHEReweightingWeightSum(tmpnLHEReweightingWeightSum,0.0);
    float tmpLHEWeight_originalXWGTUPSum = 0;
    float tmpgenWeightSum = 0;

    Double_t sumOfGenWeights = 0;


    std::vector<Double_t> genChannelWeightedCtrAr(zeroVec);

    
    //Ctrs for HTobb
    UInt_t genLWLepTWLepChannelCtr = 0;
    UInt_t genLWLepTWHadronicChannelCtr = 0;
    UInt_t genLWHadronicTWLepChannelCtr = 0;
    UInt_t genLWHadronicTWHadronicChannelCtr = 0;
    UInt_t genOtherChannelCtr = 0;
    UInt_t genErrorChannelCtr = 0;

    //Ctrs for no HTobb
    UInt_t genLWLepTWLepChannelNoHTobbCtr = 0;
    UInt_t genLWLepTWHadronicChannelNoHTobbCtr = 0;
    UInt_t genLWHadronicTWLepChannelNoHTobbCtr = 0;
    UInt_t genLWHadronicTWHadronicChannelNoHTobbCtr = 0;
    UInt_t genOtherChannelNoHTobbCtr = 0;
    UInt_t genErrorChannelNoHTobbCtr = 0;


    UInt_t HTobbCtr = 0;

    std::vector<std::string> typeNameAltAr {"LWLepTWLep","LWLepTWHadronic","LWHadronicTWLep","LWHadronicTWHadronic","GenOther","GenError","LWLepTWLep NoHTobb","LWLepTWHadronic NoHTobb","LWHadronicTWLep NoHTobb","LWHadronicTWHadronic NoHTobb","GenOther NoHTobb","GenError NoHTobb","Gen NoHTobb"};

    
    
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
        TTreeReaderValue<Bool_t> HLT_TripleMu_12_10_5(myEventsReader, "HLT_TripleMu_12_10_5");


        TTreeReaderValue<Bool_t> HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ(myEventsReader, "HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ");
        TTreeReaderValue<Bool_t> HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL(myEventsReader, "HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL");
        TTreeReaderValue<Bool_t> HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ(myEventsReader, "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ");
        TTreeReaderValue<Bool_t> HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL(myEventsReader, "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL");
        TTreeReaderValue<Bool_t> HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ(myEventsReader, "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ");
        TTreeReaderValue<Bool_t> HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL(myEventsReader, "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL");

        TTreeReaderValue<Bool_t> HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ(myEventsReader, "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ");

        TTreeReaderValue<Bool_t> HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ(myEventsReader, "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ");
        TTreeReaderValue<Bool_t> HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL(myEventsReader, "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL");
        TTreeReaderValue<Bool_t> HLT_DoubleEle33_CaloIdL_MW(myEventsReader, "HLT_DoubleEle33_CaloIdL_MW");

        TTreeReaderValue<Bool_t> HLT_IsoMu24(myEventsReader, "HLT_IsoMu24");
        TTreeReaderValue<Bool_t> HLT_IsoTkMu24(myEventsReader, "HLT_IsoTkMu24");
        TTreeReaderValue<Bool_t> HLT_IsoMu27(myEventsReader, "HLT_IsoMu27");
        TTreeReaderValue<Bool_t> HLT_Mu50(myEventsReader, "HLT_Mu50");

        TTreeReaderValue<Bool_t> HLT_Ele115_CaloIdVT_GsfTrkIdT(myEventsReader, "HLT_Ele115_CaloIdVT_GsfTrkIdT");
        TTreeReaderValue<Bool_t> HLT_Ele27_WPTight_Gsf(myEventsReader, "HLT_Ele27_WPTight_Gsf");
        TTreeReaderValue<Bool_t> HLT_Ele32_WPTight_Gsf(myEventsReader, "HLT_Ele32_WPTight_Gsf");

        TTreeReaderValue<Bool_t> HLT_AK8PFJet500(myEventsReader, "HLT_AK8PFJet500");
        TTreeReaderValue<Bool_t> HLT_AK8PFJet360_TrimMass30(myEventsReader, "HLT_AK8PFJet360_TrimMass30");
        TTreeReaderValue<Bool_t> HLT_AK8PFJet400_TrimMass30(myEventsReader, "HLT_AK8PFJet400_TrimMass30");
        TTreeReaderValue<Bool_t> HLT_AK8PFHT750_TrimMass50(myEventsReader, "HLT_AK8PFHT750_TrimMass50");
        TTreeReaderValue<Bool_t> HLT_AK8PFHT800_TrimMass50(myEventsReader, "HLT_AK8PFHT800_TrimMass50");

        //jets

        TTreeReaderValue<UInt_t> nJet(myEventsReader, "nJet");
        TTreeReaderArray<Float_t> Jet_eta(myEventsReader, "Jet_eta");
        TTreeReaderArray<Float_t> Jet_pt(myEventsReader, "Jet_pt");
        TTreeReaderArray<Float_t> Jet_phi(myEventsReader, "Jet_phi");
        TTreeReaderArray<Float_t> Jet_mass(myEventsReader, "Jet_mass");
        TTreeReaderArray<Int_t> Jet_jetId(myEventsReader, "Jet_jetId");
        TTreeReaderArray<Int_t> Jet_hadronFlavour(myEventsReader, "Jet_hadronFlavour");
        TTreeReaderArray<Int_t> Jet_genJetIdx(myEventsReader, "Jet_genJetIdx");
        TTreeReaderArray<Float_t> Jet_btagDeepFlavB(myEventsReader, "Jet_btagDeepFlavB");
        TTreeReaderValue<Float_t> fixedGridRhoFastjetAll(myEventsReader, "fixedGridRhoFastjetAll");

        //GenJet

        TTreeReaderValue<UInt_t> nGenJet(myEventsReader, "nGenJet");
        TTreeReaderArray<Float_t> GenJet_eta(myEventsReader, "GenJet_eta");
        TTreeReaderArray<Float_t> GenJet_pt(myEventsReader, "GenJet_pt");
        TTreeReaderArray<Float_t> GenJet_phi(myEventsReader, "GenJet_phi");
        TTreeReaderArray<Float_t> GenJet_mass(myEventsReader, "GenJet_mass");
        TTreeReaderArray<UChar_t> GenJet_hadronFlavour(myEventsReader, "GenJet_hadronFlavour");

        //GenJetAK8
        TTreeReaderValue<UInt_t> nGenJetAK8(myEventsReader, "nGenJetAK8");
        TTreeReaderArray<Float_t> GenJetAK8_eta(myEventsReader, "GenJetAK8_eta");
        TTreeReaderArray<Float_t> GenJetAK8_pt(myEventsReader, "GenJetAK8_pt");
        TTreeReaderArray<Float_t> GenJetAK8_phi(myEventsReader, "GenJetAK8_phi");
        TTreeReaderArray<Float_t> GenJetAK8_mass(myEventsReader, "GenJetAK8_mass");
        TTreeReaderArray<UChar_t> GenJetAK8_hadronFlavour(myEventsReader, "GenJetAK8_hadronFlavour");

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

        TTreeReaderArray<Float_t> FatJet_particleNet_mass(myEventsReader, "FatJet_particleNet_mass");

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
        TTreeReaderArray<Int_t> Muon_nTrackerLayers(myEventsReader, "Muon_nTrackerLayers");
        TTreeReaderArray<Int_t> Muon_genPartIdx(myEventsReader, "Muon_genPartIdx");

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
        //L1 Prefiring Weights
        TTreeReaderValue<Float_t> L1PreFiringWeight_Nom(myEventsReader, "L1PreFiringWeight_Nom");
        TTreeReaderValue<Float_t> L1PreFiringWeight_Dn(myEventsReader, "L1PreFiringWeight_Dn");
        TTreeReaderValue<Float_t> L1PreFiringWeight_Up(myEventsReader, "L1PreFiringWeight_Up");
        //PileUp number of interactions
        TTreeReaderValue<Float_t> Pileup_nTrueInt(myEventsReader, "Pileup_nTrueInt");
        TTreeReaderValue<Int_t> Pileup_nPU(myEventsReader, "Pileup_nPU");
        //PSWeight
        TTreeReaderValue<UInt_t> nPSWeight(myEventsReader, "nPSWeight");
        TTreeReaderArray<Float_t> PSWeight(myEventsReader, "PSWeight");
        //LHE Scale Weight
        TTreeReaderValue<UInt_t> nLHEScaleWeight(myEventsReader, "nLHEScaleWeight");
        TTreeReaderArray<Float_t> LHEScaleWeight(myEventsReader, "LHEScaleWeight");
        //LHE PDF Weight
        TTreeReaderValue<UInt_t> nLHEPdfWeight(myEventsReader, "nLHEPdfWeight");
        TTreeReaderArray<Float_t> LHEPdfWeight(myEventsReader, "LHEPdfWeight");
        TTreeReaderValue<Float_t> LHEWeight_originalXWGTUP(myEventsReader, "LHEWeight_originalXWGTUP");
        //gen weights and weight sums
        TTreeReaderValue<Float_t> Generator_weight(myEventsReader, "Generator_weight");

        //05052024 Additions for PN regress mass scaling and resolution corrections
        TTreeReaderValue<UInt_t> luminosityBlock(myEventsReader, "luminosityBlock");
        TTreeReaderValue<ULong64_t> event(myEventsReader, "event");





        TTreeReader myRunsReader("Runs", tmpfile);
        TTreeReaderValue<UInt_t> run(myRunsReader, "run");
        TTreeReaderValue<UInt_t> nLHEPdfSumw(myRunsReader, "nLHEPdfSumw");
        TTreeReaderArray<Double_t> LHEPdfSumw(myRunsReader, "LHEPdfSumw");
        TTreeReaderValue<UInt_t> nLHEScaleSumw(myRunsReader, "nLHEScaleSumw");
        TTreeReaderArray<Double_t> LHEScaleSumw(myRunsReader, "LHEScaleSumw");
        TTreeReaderValue<UInt_t> nLHEReweightingSumw(myRunsReader, "nLHEReweightingSumw");
        TTreeReaderArray<Double_t> LHEReweightingSumw(myRunsReader, "LHEReweightingSumw");
        TTreeReaderValue<Long64_t> genEventCount(myRunsReader, "genEventCount");
        TTreeReaderValue<Double_t> genEventSumw(myRunsReader, "genEventSumw");
        TTreeReaderValue<Double_t> genEventSumw2(myRunsReader, "genEventSumw2");


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
                if (debug) std::cout << crossSectionCtr << "\n";
                
                //Fill the run tree
                nLHEPdfSumwL = *nLHEPdfSumw;
                for (UInt_t i=0; i<nLHEPdfSumwL; i++){
                    LHEPdfSumwL.push_back(LHEPdfSumw[i]);
                }
                nLHEScaleSumwL = *nLHEScaleSumw;
                for (UInt_t i=0; i<nLHEScaleSumwL; i++){
                    LHEScaleSumwL.push_back(LHEScaleSumw[i]);
                }
                nLHEReweightingSumwL = *nLHEReweightingSumw;
                for (UInt_t i=0; i<nLHEReweightingSumwL; i++){
                    LHEReweightingSumwL.push_back(LHEReweightingSumw[i]);
                }
                genEventCountL = *genEventCount;
                genEventSumwL = *genEventSumw;
                genEventSumw2L = *genEventSumw2;
                runL = *run;
                runTree->Fill();
                //clear run tree vectors
                LHEPdfSumwL.clear();
                LHEScaleSumwL.clear();
                LHEReweightingSumwL.clear();
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

            tmpGenerator_weightSum += *Generator_weight;
            for (UInt_t i=0; i<*nLHEPdfWeight; i++){
                tmpLHEPdfWeightSum[i] += LHEPdfWeight[i];
            }
            for (UInt_t i=0; i<*nLHEReweightingWeight; i++){
                tmpLHEReweightingWeightSum[i] += LHEReweightingWeight[i];
            }
            tmpLHEWeight_originalXWGTUPSum += *LHEWeight_originalXWGTUP;
            tmpgenWeightSum += *genWeight;

            sumOfGenWeights += *genWeight;
            genChannelL = 4;
            HTobbBoolL = false;

            //--------------KINEMATICS--------------

            UInt_t tmpnFatJets = *nFatJet;

            /*
            
            int ZOneDecLeadInd = -1;
            int ZOneDecTrailingInd = -1;
            int WDecLeadInd = -1;
            int WDecTrailingInd = -1;
            
            bool WLepZLep = false;
            bool WLepZHadronic = false;
            bool WHadronicZLep = false;
            bool WHadronicZHadronic = false;
            */

            ZFJIndL = -1;
            HFJIndL = -1;
            goodGenZFJMatchL = false;
            goodGenHFJMatchL = false;
            goodZFJMatchToGenL = false;
            goodHFJMatchToGenL = false;
            eventGenSemileptonicL = false;
            ZFJGenHadronFlavourL = -1;
            HFJGenHadronFlavourL = -1;
            eventGenHToBBL = false;
            ZOneTypeL = -1;
            ZTwoTypeL = -1;
            nHDecayPIDL = 0;
            nZOneDecayPIDL = 0;
            nZTwoDecayPIDL = 0;
            HDecayPIDL.clear();
            ZOneDecayPIDL.clear();
            ZTwoDecayPIDL.clear();


            
            genChannelWeightedCtrAr[0] += *genWeight;
            for (unsigned int C2VCtr = 1; C2VCtr < genChannelWeightedCtrAr.size(); C2VCtr++){
                genChannelWeightedCtrAr[C2VCtr] += *genWeight*(LHEReweightingWeight[C2VCtr-1]);
            }

            
            bool passFlagBool = *Flag_goodVertices && *Flag_globalSuperTightHalo2016Filter && *Flag_HBHENoiseFilter && *Flag_HBHENoiseIsoFilter && *Flag_EcalDeadCellTriggerPrimitiveFilter && *Flag_BadPFMuonFilter && *Flag_eeBadScFilter;

            if (!passFlagBool) continue;
            passFlagCtr += 1;
            //passFlagWeightedCtr += *genWeight;

            if (!isBackground){
                passFlagWeightedCtrAr[0] += *genWeight;
                for (unsigned int C2VCtr = 1; C2VCtr < passFlagWeightedCtrAr.size(); C2VCtr++){
                    passFlagWeightedCtrAr[C2VCtr] += *genWeight*(LHEReweightingWeight[C2VCtr-1]);
                }
                
            }





            if (debug){
                std::cout <<"Passed HLT\n";
            }
            bool passHLTBool = (*HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ || *HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ);
            if (useSingleLepHLT) {
                passHLTBool = (passHLTBool || *HLT_IsoMu24 || *HLT_IsoTkMu24 || *HLT_Ele27_WPTight_Gsf);
            }
            //std::cout << testPassHLTBool << " " << passHLTBool << "\n";
            if (!passHLTBool) continue;
            passHLTCtr += 1;
            //passHLTWeightedCtr += *genWeight;

            if (!isBackground){
                passHLTWeightedCtrAr[0] += *genWeight;
                for (unsigned int C2VCtr = 1; C2VCtr < passHLTWeightedCtrAr.size(); C2VCtr++){
                    passHLTWeightedCtrAr[C2VCtr] += *genWeight*(LHEReweightingWeight[C2VCtr-1]);
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
                passnFJWeightedCtrAr[0] += *genWeight;
                for (unsigned int C2VCtr = 1; C2VCtr < passnFJWeightedCtrAr.size(); C2VCtr++){
                    passnFJWeightedCtrAr[C2VCtr] += *genWeight*(LHEReweightingWeight[C2VCtr-1]);
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

                passnVBFWeightedCtrAr[0] += *genWeight;
                for (unsigned int C2VCtr = 1; C2VCtr < passnVBFWeightedCtrAr.size(); C2VCtr++){
                    passnVBFWeightedCtrAr[C2VCtr] += *genWeight*(LHEReweightingWeight[C2VCtr-1]);
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
                Jet_hadronFlavourL.push_back(Jet_hadronFlavour[nJetItr]);
                Jet_genJetIdxL.push_back(Jet_genJetIdx[nJetItr]);
                Jet_btagDeepFlavBL.push_back(Jet_btagDeepFlavB[nJetItr]);
            }
            fixedGridRhoFastjetAllL = *fixedGridRhoFastjetAll;

            //GenJets
            nGenJetL = *nGenJet;
            for (UInt_t nGenJetItr=0; nGenJetItr<nGenJetL;nGenJetItr++){
                GenJet_etaL.push_back(GenJet_eta[nGenJetItr]);
                GenJet_ptL.push_back(GenJet_pt[nGenJetItr]);
                GenJet_phiL.push_back(GenJet_phi[nGenJetItr]);
                GenJet_massL.push_back(GenJet_mass[nGenJetItr]);
                GenJet_hadronFlavourL.push_back(GenJet_hadronFlavour[nGenJetItr]);
            }

            //GenJetAK8
            nGenJetAK8L = *nGenJetAK8;
            for (UInt_t nGenJetAK8Itr=0; nGenJetAK8Itr<nGenJetAK8L;nGenJetAK8Itr++){
                GenJetAK8_etaL.push_back(GenJetAK8_eta[nGenJetAK8Itr]);
                GenJetAK8_ptL.push_back(GenJetAK8_pt[nGenJetAK8Itr]);
                GenJetAK8_phiL.push_back(GenJetAK8_phi[nGenJetAK8Itr]);
                GenJetAK8_massL.push_back(GenJetAK8_mass[nGenJetAK8Itr]);
                GenJetAK8_hadronFlavourL.push_back(GenJetAK8_hadronFlavour[nGenJetAK8Itr]);
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
                Muon_genPartIdxL.push_back(Muon_genPartIdx[nMuonItr]);
            }

            //GenPart
            nGenPartL = *nGenPart;
            for (UInt_t nGenPartItr=0; nGenPartItr<nGenPartL;nGenPartItr++){
                GenPart_etaL.push_back(GenPart_eta[nGenPartItr]);
                GenPart_massL.push_back(GenPart_mass[nGenPartItr]);
                GenPart_pdgIdL.push_back(GenPart_pdgId[nGenPartItr]);
                GenPart_phiL.push_back(GenPart_phi[nGenPartItr]);
                GenPart_ptL.push_back(GenPart_pt[nGenPartItr]);
                GenPart_statusL.push_back(GenPart_status[nGenPartItr]);
                GenPart_genPartIdxMotherL.push_back(GenPart_genPartIdxMother[nGenPartItr]);
                GenPart_statusFlagsL.push_back(GenPart_statusFlags[nGenPartItr]);
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
            //L1 Prefiring Weights
            L1PreFiringWeight_NomL = *L1PreFiringWeight_Nom;
            L1PreFiringWeight_DnL = *L1PreFiringWeight_Dn;
            L1PreFiringWeight_UpL = *L1PreFiringWeight_Up;
            //PileUp number of interactions
            Pileup_nTrueIntL = *Pileup_nTrueInt;
            Pileup_nPUL = *Pileup_nPU;
            //PSWeight
            nPSWeightL = *nPSWeight;
            for (UInt_t nPSWeightItr=0; nPSWeightItr<nPSWeightL;nPSWeightItr++){
                PSWeightL.push_back(PSWeight[nPSWeightItr]);
            }
            //LHE Scale Weight
            nLHEScaleWeightL = *nLHEScaleWeight;
            for (UInt_t nLHEScaleWeightItr=0; nLHEScaleWeightItr<nLHEScaleWeightL;nLHEScaleWeightItr++){
                LHEScaleWeightL.push_back(LHEScaleWeight[nLHEScaleWeightItr]);
            }
            //LHE PDF Weight
            nLHEPdfWeightL = *nLHEPdfWeight;
            for (UInt_t nLHEPdfWeightItr=0; nLHEPdfWeightItr<nLHEPdfWeightL;nLHEPdfWeightItr++){
                LHEPdfWeightL.push_back(LHEPdfWeight[nLHEPdfWeightItr]);
            }
            LHEWeight_originalXWGTUPL = *LHEWeight_originalXWGTUP;
            //generator weight
            Generator_weightL = *Generator_weight;

            //05052024 Additions for PN regress mass scaling and resolution corrections
            luminosityBlockL = *luminosityBlock;
            eventL = *event;


            FilteredEventsTree->Fill();


            LHEReweightingWeightL.clear();

            Jet_etaL.clear();
            Jet_ptL.clear();
            Jet_phiL.clear();
            Jet_massL.clear();
            Jet_jetIdL.clear();
            Jet_hadronFlavourL.clear();
            Jet_genJetIdxL.clear();
            Jet_btagDeepFlavBL.clear();

            GenJet_etaL.clear();
            GenJet_ptL.clear();
            GenJet_phiL.clear();
            GenJet_massL.clear();
            GenJet_hadronFlavourL.clear();

            GenJetAK8_etaL.clear();
            GenJetAK8_ptL.clear();
            GenJetAK8_phiL.clear();
            GenJetAK8_massL.clear();
            GenJetAK8_hadronFlavourL.clear();
            

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
            Muon_genPartIdxL.clear();

            GenPart_etaL.clear();
            GenPart_massL.clear();
            GenPart_pdgIdL.clear();
            GenPart_phiL.clear();
            GenPart_ptL.clear();
            GenPart_statusL.clear();
            GenPart_genPartIdxMotherL.clear();
            GenPart_statusFlagsL.clear();

            FatJet_particleNet_HbbvsQCDL.clear();
            FatJet_particleNet_ZvsQCDL.clear();

            FatJet_particleNetMD_QCDL.clear();
            FatJet_particleNetMD_XbbL.clear();
            FatJet_particleNetMD_XccL.clear();
            FatJet_particleNetMD_XqqL.clear();

            FatJet_hadronFlavourL.clear();

            HDecayPIDL.clear();

            ZOneDecayPIDL.clear();
            ZTwoDecayPIDL.clear();

            Jet_puIdL.clear();

            PSWeightL.clear();
            LHEScaleWeightL.clear();
            LHEPdfWeightL.clear();

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

    std::string C2V2Str = "2p0";
    std::string C2V2MaStr = "C2W_2p0_C2Z_2p0";

    uint C2V2Point = 27;
    uint C2V2MaPoint = 83;

    if (isMariaSignal) {
        C2V2Str = C2V2MaStr;
        C2V2Point = C2V2MaPoint;

    }

    for (unsigned int loopItr = 0; loopItr < C2VNameAr.size(); loopItr++){
        if (loopItr == C2VNameAr.size() - 1) {
            std::cout << "(" << C2VNameAr[loopItr] << "," << passFlagWeightedCtrAr[loopItr + 1] << ")\n";
        }
        else std::cout << "(" << C2VNameAr[loopItr] << "," << passFlagWeightedCtrAr[loopItr + 1] << "),";
        if (loopItr == C2V2Point) {
            std::cout << "(C2W_2p0_C2Z_2p0," << passFlagWeightedCtrAr[0] << "),";
        }
    }



    std::cout << "passes HLT cut: " << passHLTCtr << " -------------------\n";

    for (unsigned int loopItr = 0; loopItr < C2VNameAr.size(); loopItr++){
        if (loopItr == C2VNameAr.size() - 1) {
            std::cout << "(" << C2VNameAr[loopItr] << "," << passHLTWeightedCtrAr[loopItr + 1] << ")\n";
        }
        else std::cout << "(" << C2VNameAr[loopItr] << "," << passHLTWeightedCtrAr[loopItr + 1] << "),";
        if (loopItr == C2V2Point) {
            std::cout << "(C2W_2p0_C2Z_2p0," << passHLTWeightedCtrAr[0] << "),";
        }
    }


    std::cout << "passes nFJ cut: " << passnFJCtr << " -------------------\n";

    for (unsigned int loopItr = 0; loopItr < C2VNameAr.size(); loopItr++){
        if (loopItr == C2VNameAr.size() - 1) {
            std::cout << "(" << C2VNameAr[loopItr] << "," << passnFJWeightedCtrAr[loopItr + 1] << ")\n";
        }
        else std::cout << "(" << C2VNameAr[loopItr] << "," << passnFJWeightedCtrAr[loopItr + 1] << "),";
        if (loopItr == C2V2Point) {
            std::cout << "(C2W_2p0_C2Z_2p0," << passnFJWeightedCtrAr[0] << "),";
        }
    }


    std::cout << "passes nVBF cut: " << passnVBFCtr << " -------------------\n";

    for (unsigned int loopItr = 0; loopItr < C2VNameAr.size(); loopItr++){
        if (loopItr == C2VNameAr.size() - 1) {
            std::cout << "(" << C2VNameAr[loopItr] << "," << passnVBFWeightedCtrAr[loopItr + 1] << ")\n";
        }
        else std::cout << "(" << C2VNameAr[loopItr] << "," << passnVBFWeightedCtrAr[loopItr + 1] << "),";
        if (loopItr == C2V2Point) {
            std::cout << "(C2W_2p0_C2Z_2p0," << passnVBFWeightedCtrAr[0] << "),";
        }
    }

    
    std::cout << "sumOfGenWeights: " << sumOfGenWeights << "\n";
    
    if (!isBackground){
        
        
        
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
    //Fill Weight sum tree
    Generator_weightSumL = tmpGenerator_weightSum;
    nLHEPdfWeightSumL = tmpnLHEPdfWeightSum;
    for (UInt_t nLHEPdfWeightSumItr=0; nLHEPdfWeightSumItr<nLHEPdfWeightSumL;nLHEPdfWeightSumItr++){
        LHEPdfWeightSumL.push_back(tmpLHEPdfWeightSum[nLHEPdfWeightSumItr]);
    }
    nLHEReweightingWeightSumL = tmpnLHEReweightingWeightSum;
    for (UInt_t nLHEReweightingWeightSumItr=0; nLHEReweightingWeightSumItr<nLHEReweightingWeightSumL;nLHEReweightingWeightSumItr++){
        LHEReweightingWeightSumL.push_back(tmpLHEReweightingWeightSum[nLHEReweightingWeightSumItr]);
    }
    LHEWeight_originalXWGTUPSumL = tmpLHEWeight_originalXWGTUPSum;
    genWeightSumL = tmpgenWeightSum;
    std::cout << "Generator_weightSumL: " << Generator_weightSumL << "\n";
    std::cout << "nLHEPdfWeightSumL: " << nLHEPdfWeightSumL << "\n";
    std::cout << "LHEPdfWeightSumL: ";
    for (UInt_t nLHEPdfWeightSumItr=0; nLHEPdfWeightSumItr<nLHEPdfWeightSumL;nLHEPdfWeightSumItr++){
        std::cout << LHEPdfWeightSumL[nLHEPdfWeightSumItr] << " ";
    }
    std::cout << "\n";
    std::cout << "nLHEReweightingWeightSumL: " << nLHEReweightingWeightSumL << "\n";
    std::cout << "LHEReweightingWeightSumL: ";
    for (UInt_t nLHEReweightingWeightSumItr=0; nLHEReweightingWeightSumItr<nLHEReweightingWeightSumL;nLHEReweightingWeightSumItr++){
        std::cout << LHEReweightingWeightSumL[nLHEReweightingWeightSumItr] << " ";
    }
    std::cout << "\n";
    std::cout << "LHEWeight_originalXWGTUPSumL: " << LHEWeight_originalXWGTUPSumL << "\n";
    std::cout << "genWeightSumL: " << genWeightSumL << "\n";
    weightSumsTree->Fill();
    LHEPdfWeightSumL.clear();
    LHEReweightingWeightSumL.clear();

    outFile->cd();
    weightSumsTree->Write("",TObject::kOverwrite);
    runTree->Write("",TObject::kOverwrite);
    evNumTree->Write("",TObject::kOverwrite);
    FilteredEventsTree->Write("",TObject::kOverwrite);
    genTree->Write("",TObject::kOverwrite);
    
    outFile->Close();
}
