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


void DoTrimmed042024WZHHLTFilterOnReweightingBeforeAnalysis(UInt_t fileInd, string datasetString){
    // Open the file. Note that the name of your file outside this class
    // will probably NOT be experiment.root.
    std::cout << "start\n";
    clock_t startt = clock();

    if (datasetString == "testRun") testRun = true;
    if (datasetString == "SDC2V2MCWZHReweight") SDC2V2MCWZHReweight = true;
    if (datasetString == "SDC2V2MCWZH17Reweight") SDC2V2MCWZH17Reweight = true;
    //Analyzer will run over all files put into fileAr

    std::vector<std::string> fileAr;

    std::string saveName;
    float crossSection;
    bool isBackground;

    ////////////////////////////////GETTING DATASET////////////////////////////////
    ////////////////////////////////GETTING DATASET////////////////////////////////
    ////////////////////////////////GETTING DATASET////////////////////////////////
    ////////////////////////////////GETTING DATASET////////////////////////////////

    std::string strAdd;
    if (scratchDown) strAdd ="/afs/crc.nd.edu/user/d/dlutton/FROM_PANASAS";
    else strAdd ="/scratch365";

    if (SDC2V2MCWZHReweight){
        saveName = "SDC2V2MCWZHReweight";
        isBackground = false;
        int arrSize = sizeof(SDC2V2MCWZHReweightAr)/sizeof(SDC2V2MCWZHReweightAr[0]);
        std::string tmpStrWithPath = SDC2V2MCWZHReweightAr[fileInd];
        fileAr.push_back(tmpStrWithPath);
        
    }
    else if (SDC2V2MCWZH17Reweight){
        saveName = "SDC2V2MCWZH17Reweight";
        isBackground = false;
        int arrSize = sizeof(SDC2V2MCWZH17ReweightAr)/sizeof(SDC2V2MCWZH17ReweightAr[0]);
        std::string tmpStrWithPath = SDC2V2MCWZH17ReweightAr[fileInd];
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

    std::vector<std::string> C2VNameAr {"-2.0","-1.75","-1.5","-1.25","-1.0","-0.75","-0.5","-0.25","0.0","0.1","0.2","0.3","0.4","0.5","0.6","0.7","0.8","0.9","1.0","1.1","1.2","1.3","1.4","1.5","1.6","1.7","1.8","1.9","2.25","2.5","2.75","3.0","3.25","3.5","3.75","4.0"};

    std::vector<std::string> typeNameAr {"WLepZLep","WLepZHadronic","WHadronicZLep","WHadronicZHadronic","GenOther","WLepZLep NoHTobb","WLepZHadronic NoHTobb","WHadronicZLep NoHTobb","WHadronicZHadronic NoHTobb","GenOther NoHTobb"};
    std::vector<Double_t> zeroVec(37,0.0);
    std::vector<std::vector<Double_t>> passFlagWeightedCtrAr(11,zeroVec);
    std::vector<std::vector<Double_t>> passHLTWeightedCtrAr(11,zeroVec);
    std::vector<std::vector<Double_t>> passnFJWeightedCtrAr(11,zeroVec);
    std::vector<std::vector<Double_t>> passnVBFWeightedCtrAr(11,zeroVec);

    

    UInt_t passFlagCtr = 0;
    UInt_t passHLTCtr = 0;
    UInt_t passnFJCtr = 0;
    UInt_t passnVBFCtr = 0;
    


    UInt_t passFlagWLepZLepCtr = 0;
    UInt_t passFlagWLepZHadronicCtr = 0;
    UInt_t passFlagWHadronicZLepCtr = 0;
    UInt_t passFlagWHadronicZHadronicCtr = 0;
    UInt_t passFlagGenOtherCtr = 0;
    

    UInt_t passFlagWLepZLepNoHTobbCtr = 0;
    UInt_t passFlagWLepZHadronicNoHTobbCtr = 0;
    UInt_t passFlagWHadronicZLepNoHTobbCtr = 0;
    UInt_t passFlagWHadronicZHadronicNoHTobbCtr = 0;
    UInt_t passFlagGenOtherNoHTobbCtr = 0;
    


    UInt_t passHLTWLepZLepCtr = 0;
    UInt_t passHLTWLepZHadronicCtr = 0;
    UInt_t passHLTWHadronicZLepCtr = 0;
    UInt_t passHLTWHadronicZHadronicCtr = 0;
    UInt_t passHLTGenOtherCtr = 0;
    

    UInt_t passHLTWLepZLepNoHTobbCtr = 0;
    UInt_t passHLTWLepZHadronicNoHTobbCtr = 0;
    UInt_t passHLTWHadronicZLepNoHTobbCtr = 0;
    UInt_t passHLTWHadronicZHadronicNoHTobbCtr = 0;
    UInt_t passHLTGenOtherNoHTobbCtr = 0;
    

    UInt_t passnFJWLepZLepCtr = 0;
    UInt_t passnFJWLepZHadronicCtr = 0;
    UInt_t passnFJWHadronicZLepCtr = 0;
    UInt_t passnFJWHadronicZHadronicCtr = 0;
    UInt_t passnFJGenOtherCtr = 0;
    

    UInt_t passnFJWLepZLepNoHTobbCtr = 0;
    UInt_t passnFJWLepZHadronicNoHTobbCtr = 0;
    UInt_t passnFJWHadronicZLepNoHTobbCtr = 0;
    UInt_t passnFJWHadronicZHadronicNoHTobbCtr = 0;
    UInt_t passnFJGenOtherNoHTobbCtr = 0;
    

    UInt_t passnVBFWLepZLepCtr = 0;
    UInt_t passnVBFWLepZHadronicCtr = 0;
    UInt_t passnVBFWHadronicZLepCtr = 0;
    UInt_t passnVBFWHadronicZHadronicCtr = 0;
    UInt_t passnVBFGenOtherCtr = 0;

    
    

    UInt_t passnVBFWLepZLepNoHTobbCtr = 0;
    UInt_t passnVBFWLepZHadronicNoHTobbCtr = 0;
    UInt_t passnVBFWHadronicZLepNoHTobbCtr = 0;
    UInt_t passnVBFWHadronicZHadronicNoHTobbCtr = 0;
    UInt_t passnVBFGenOtherNoHTobbCtr = 0;
    
    





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
    Double_t HdRFromZL;
    Double_t HdRFromWL;
    Double_t ZdRFromWL;

    TTree *genTree = new TTree("genTree", "genTree");


    genTree->Branch("nLHEReweightingWeightGenL",&nLHEReweightingWeightGenL,"nLHEReweightingWeightGenL/i");
    genTree->Branch("LHEReweightingWeightGenL",&LHEReweightingWeightGenL);
    genTree->Branch("HdRFromZL",&HdRFromZL,"HdRFromZL/D");
    genTree->Branch("HdRFromWL",&HdRFromWL,"HdRFromWL/D");
    genTree->Branch("ZdRFromWL",&ZdRFromWL,"ZdRFromWL/D");

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
    uint tmpnLHEReweightingWeightSum = 36;
    //size of 36 is hardcoded in the LHEReweightingWeight branch
    std::vector<Float_t> tmpLHEReweightingWeightSum(tmpnLHEReweightingWeightSum,0.0);
    float tmpLHEWeight_originalXWGTUPSum = 0;
    float tmpgenWeightSum = 0;

    Double_t sumOfGenWeights = 0;


    std::vector<std::vector<Double_t>> genChannelWeightedCtrAr(13,zeroVec);

    
    //Ctrs for HTobb
    UInt_t genWLepZLepChannelCtr = 0;
    UInt_t genWLepZHadronicChannelCtr = 0;
    UInt_t genWHadronicZLepChannelCtr = 0;
    UInt_t genWHadronicZHadronicChannelCtr = 0;
    UInt_t genOtherChannelCtr = 0;
    UInt_t genErrorChannelCtr = 0;

    //Ctrs for no HTobb
    UInt_t genWLepZLepChannelNoHTobbCtr = 0;
    UInt_t genWLepZHadronicChannelNoHTobbCtr = 0;
    UInt_t genWHadronicZLepChannelNoHTobbCtr = 0;
    UInt_t genWHadronicZHadronicChannelNoHTobbCtr = 0;
    UInt_t genOtherChannelNoHTobbCtr = 0;
    UInt_t genErrorChannelNoHTobbCtr = 0;


    UInt_t HTobbCtr = 0;

    std::vector<std::string> typeNameAltAr {"WLepZLep","WLepZHadronic","WHadronicZLep","WHadronicZHadronic","GenOther","GenError","WLepZLep NoHTobb","WLepZHadronic NoHTobb","WHadronicZLep NoHTobb","WHadronicZHadronic NoHTobb","GenOther NoHTobb","GenError NoHTobb","Gen NoHTobb"};

    
    
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
        TTreeReaderValue<UInt_t> luminosityBlock(myEventsReader, "luminosityBlockL");
        TTreeReaderValue<ULong64_t> event(myEventsReader, "eventL");





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
            std::vector<Bool_t> evWeightedCtrMaskOne(11,false);
            evWeightedCtrMaskOne[0] = true;
            std::vector<Bool_t> evWeightedCtrMaskTwo(13,false);

            //--------------KINEMATICS--------------

            UInt_t tmpnFatJets = *nFatJet;
            
            int ZOneDecLeadInd = -1;
            int ZOneDecTrailingInd = -1;
            int WDecLeadInd = -1;
            int WDecTrailingInd = -1;
            
            bool WLepZLep = false;
            bool WLepZHadronic = false;
            bool WHadronicZLep = false;
            bool WHadronicZHadronic = false;

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

            if (!isBackground){

                float JOne_pdgId_FromLHERaw;
                float JTwo_pdgId_FromLHERaw;

                int WPDGId = -1;

                UInt_t lenLHEPart = *nLHEPart;
                Int_t tmpZCtr = 0;
                Int_t tmpHCtr = 0;
                Int_t tmpWCtr = 0;
                Int_t tmpJCtr = 0;
                Int_t tmpZInd = -1;
                Int_t tmpHInd = -1;
                Int_t tmpWInd = -1;
                std::vector<UInt_t>tmpJAr;
                Int_t tmpPDGId = 0;

                if (debug){
                    std::cout <<"Starting LHE loop\n";
                }
                for (UInt_t LHEItr=0; LHEItr<lenLHEPart;LHEItr++){
                    tmpPDGId = LHEPart_pdgId[LHEItr];
                    if (tmpPDGId == 23){
                        tmpZCtr += 1;
                        if (tmpZCtr > 1) std::cout << "ERROR MORE THAN 1 Z IN LHE\n";
                        else tmpZInd = LHEItr;
                    }
                    else if (tmpPDGId == 25){
                        tmpHCtr += 1;
                        if (tmpHCtr > 1) std::cout << "ERROR MORE THAN 1 H IN LHE\n";
                        else tmpHInd = LHEItr;
                    }
                    else if (abs(tmpPDGId) == 24){
                        tmpWCtr += 1;
                        if (tmpWCtr > 1) std::cout << "ERROR MORE THAN 1 W IN LHE\n";
                        else {
                            tmpWInd = LHEItr;
                            WPDGId = tmpPDGId;

                        }
                    }
                    else if (tmpPDGId >= -8 && tmpPDGId <= 8){
                        tmpJCtr += 1;
                        if (tmpJCtr > 4) std::cout << "ERROR MORE THAN 4 Qs IN LHE\n";
                        else if (tmpJCtr > 2) tmpJAr.push_back(LHEItr);
                    }
                    else std::cout << "ERROR UNKNOWN PARTICLE " << tmpPDGId << " IN LHE\n";
                }
                if (tmpZCtr == 1 && tmpHCtr == 1 && tmpWCtr == 1 && tmpJCtr == 4 && tmpJAr.size() == 2){
                    
                    
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

                bool WIsLeptonic = false;
                bool WIsHadronic = false;

                std::vector<std::vector<Int_t>> tmpHAr;
                std::vector<std::vector<Int_t>> tmpZAr;
                std::vector<std::vector<Int_t>> tmpZDaughterIndAr;

                std::vector<std::vector<Int_t>> tmpWAr;
                std::vector<std::vector<Int_t>> tmpWDaughterIndAr;


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
                std::vector<bool> HToWBoolVec;
                std::vector<Int_t> isInHDecChainVec;

                if (debug){
                    std::cout <<"Starting genpart loop\n";
                }
                
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
                                    if (tmpPDGId == 23 && tmpZAr.size() ==0) {
                                        //HToZIndVec.push_back(i)
                                        HToZBoolVec[tmpHItr] =true;
                                    }
                                    if (tmpPDGId == WPDGId && tmpWAr.size() ==0) {
                                        //HToZIndVec.push_back(i)
                                        HToWBoolVec[tmpHItr] =true;
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
                            HToWBoolVec.push_back(false);
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

                    if (tmpWAr.size()){
                        for (UInt_t tmpWItr=0;tmpWItr<tmpWAr.size();tmpWItr++){
                            if (debugGenPart) std::cout << "tmpWItr " << tmpWItr << " tmpMotherID " << tmpMotherID << " tmpWAr[tmpWItr][0]) " << tmpWAr[tmpWItr][0] << "\n";
                            if (tmpMotherID == tmpWAr[tmpWItr][0]){
                                if (tmpPDGId == WPDGId) std::cout <<"ERROR, ERROR, DAUGHTER PARTICLE IS W\n";
                                else {
                                    tmpWAr[tmpWItr].push_back(tmpPDGId);
                                    tmpWDaughterIndAr[tmpWItr].push_back(i);
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
                        
                        if (tmpZAr.size()==0 || !isHDecay){
                            if (tmpStatusBin) {
                                tmpZAr.push_back(tmpZFJVec);
                                tmpZDaughterIndAr.push_back(tmpZOneDaughterVec);
                            }
                        }

                    }

                    if (GenPart_pdgId[i] == WPDGId){
                        //std::bitset<sizeof(Int_t)> tmpStatusBitSet;
                        //bool tmpStatusBin = tmpStatusBitSet(GenPart_statusFlags[i]).test(13);
                        bool tmpStatusBin = GenPart_statusFlags[i] & (1 << 13);
                        //tmpStatusBin = bin(GenPart_statusFlags[i]);
                        if (debugGenPart) std::cout <<"GenPart_statusFlags[i] " << GenPart_statusFlags[i] << " tmpStatusBin " << tmpStatusBin << " tmpWAr.size() " << tmpWAr.size() << " isHDecay " << isHDecay << "\n";
                        
                        //tmpIsEnd = tmpStatusBin[-14];
                        std::vector<Int_t> tmpWFJVec;
                        tmpWFJVec.push_back(i);
                        std::vector<Int_t> tmpWOneDaughterVec;
                        
                        if (tmpWAr.size()==0 || !isHDecay){
                            if (tmpStatusBin) {
                                tmpWAr.push_back(tmpWFJVec);
                                tmpWDaughterIndAr.push_back(tmpWOneDaughterVec);
                            }
                        }

                    }
                }
                if (debugGenPart) {
                    std::cout <<"Finished H,Z,W Finding. tmpHAr:\n";
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
                    std::cout <<"HToWBoolVec:\n";
                    if (HToWBoolVec.size()){
                        for (UInt_t tmpHItr=0;tmpHItr<HToWBoolVec.size();tmpHItr++){
                            std::cout << HToWBoolVec[tmpHItr] << ", ";
                        }
                        std::cout << "\n";
                    }
                    std::cout <<"tmpWAr:\n";
                    if (tmpWAr.size()){
                        for (UInt_t tmpWItr=0;tmpWItr<tmpWAr.size();tmpWItr++){
                            for (UInt_t tmpWItrTwo=0;tmpWItrTwo<tmpWAr[tmpWItr].size();tmpWItrTwo++){
                                std::cout << tmpWAr[tmpWItr][tmpWItrTwo] << ", ";
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
                        if (std::count(tmpHAr[tmpHItr].begin(), tmpHAr[tmpHItr].end(), WPDGId) && HToWBoolVec[tmpHItr]){
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
                    
                    genErrorChannelCtr += 1;
                    evWeightedCtrMaskTwo[5] = true;
                }
                else{
                    if (debugGenPart) std::cout <<"H found\n";
                    if (abs(HFJ_decaypdgId_FromGenMatch[0]) == 5){
                        HTobbBoolL = true;
                        HTobbCtr += 1;
                        //HTobbWeightedCtr += *genWeight;
                    }
                    Int_t intermediaryZ = -1;
                    
                    if (tmpZAr.size() >= 2){
                        //if (evCount -1 == 407) std::cout << "yes\n";
                        for (UInt_t tmpZItr=0;tmpZItr<tmpZAr.size();tmpZItr++){
                            //if (evCount -1 == 407) std::cout << "yes\n";
                            if (std::count(tmpZAr[tmpZItr].begin(), tmpZAr[tmpZItr].end(), JOne_pdgId_FromLHERaw)){
                                //if (evCount -1 == 407) std::cout << "yes\n";
                                if (std::count(tmpZAr[tmpZItr].begin(), tmpZAr[tmpZItr].end(), JTwo_pdgId_FromLHERaw)){
                                    //if (evCount -1 == 407) std::cout << "yes\n";
                                    if (tmpZAr[tmpZItr].size() == 3 || tmpZAr[tmpZItr].size() == 4){
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

                    if (finalZAr.size() != 1){
                        std::cout <<"ERROR ERROR, MORE OR LESS THAN ONE Z,evCount,finalZAr.size(),intermediaryZ,JOne_pdgId_FromLHERaw,JTwo_pdgId_FromLHERaw " << evCount-1<< " " << finalZAr.size() << " " << intermediaryZ << " "<<JOne_pdgId_FromLHERaw<< " " <<JTwo_pdgId_FromLHERaw << "\n";
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
                        if (HTobbBoolL){
                            genErrorChannelCtr += 1;
                            //genErrorChannelWeightedCtr += *genWeight;
                            evWeightedCtrMaskTwo[5] = true;
                        }
                        else{
                            genErrorChannelNoHTobbCtr += 1;
                            //genErrorChannelNoHTobbWeightedCtr += *genWeight;
                            evWeightedCtrMaskTwo[11] = true;
                        }

                    }
                    else{


                        if (debugGenPart) std::cout <<"Z found\n";
                        Int_t intermediaryW = -1;
                        
                        if (tmpWAr.size() >= 2){
                            //if (evCount -1 == 407) std::cout << "yes\n";
                            for (UInt_t tmpWItr=0;tmpWItr<tmpWAr.size();tmpWItr++){
                                //if (evCount -1 == 407) std::cout << "yes\n";
                                if (std::count(tmpWAr[tmpWItr].begin(), tmpWAr[tmpWItr].end(), JOne_pdgId_FromLHERaw)){
                                    //if (evCount -1 == 407) std::cout << "yes\n";
                                    if (std::count(tmpWAr[tmpWItr].begin(), tmpWAr[tmpWItr].end(), JTwo_pdgId_FromLHERaw)){
                                        //if (evCount -1 == 407) std::cout << "yes\n";
                                        if (tmpWAr[tmpWItr].size() == 3){
                                            //if (evCount -1 == 407) std::cout << "yes\n";
                                            intermediaryW = tmpWItr;
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                        std::vector<Int_t> finalWAr;
                        std::vector<std::vector<Int_t>> finalWDecAr;
                        std::vector<std::vector<Int_t>> finalWDecIndAr;
                        bool WDecFound = false;
                        if (debugGenPart) {
                            std::cout << "Going into tmpWAr loop\n";
                        }


                        if (tmpWAr.size()){
                            for (UInt_t tmpWItr=0;tmpWItr<tmpWAr.size();tmpWItr++){
                                if (tmpWItr != intermediaryW){
                                    finalWAr.push_back(tmpWAr[tmpWItr][0]);
                                    //Looping through array for decay branches
                                    
                                    
                                    if (tmpWAr[tmpWItr].size() != 3) {
                                        std::cout << "ERROR ERROR tmpWAr INTERNAL VEC SIZE NOT == 3. INSTEAD SIZE == " << tmpWAr[tmpWItr].size() << "\n";
                                        for (UInt_t tmpWDecItr=0;tmpWDecItr<tmpWAr[tmpWItr].size();tmpWDecItr++){
                                            std::cout << tmpWAr[tmpWItr][tmpWDecItr] << " ";
                                        }
                                        std::cout << "\n";
                                    }
                                    else {
                                        WDecFound = true;
                                        std::vector<Int_t> tmpWDecVec;
                                        tmpWDecVec.push_back(tmpWAr[tmpWItr][1]);
                                        tmpWDecVec.push_back(tmpWAr[tmpWItr][2]);
                                        finalWDecAr.push_back(tmpWDecVec);
                                        std::vector<Int_t> tmpWDecIndVec;
                                        tmpWDecIndVec.push_back(tmpWDaughterIndAr[tmpWItr][0]);
                                        tmpWDecIndVec.push_back(tmpWDaughterIndAr[tmpWItr][1]);
                                        finalWDecIndAr.push_back(tmpWDecIndVec);
                                        

                                    }
                                }
                            }
                        }

                        if (finalWAr.size() != 1){
                            std::cout <<"ERROR ERROR, MORE OR LESS THAN ONE W,evCount,finalWAr.size(),intermediaryW,JOne_pdgId_FromLHERaw,JTwo_pdgId_FromLHERaw " << evCount-1<< " " << finalWAr.size() << " " << intermediaryW << " "<<JOne_pdgId_FromLHERaw<< " " <<JTwo_pdgId_FromLHERaw << "\n";
                            if (tmpWAr.size()){
                                for (UInt_t tmpWItr=0;tmpWItr<tmpWAr.size();tmpWItr++){
                                    for (UInt_t tmpWItrTwo=0;tmpWItrTwo<tmpWAr[tmpWItr].size();tmpWItrTwo++){
                                        std::cout <<"tmpWItr " << tmpWItr << " tmpWItrTwo " << tmpWItrTwo << " tmpWAr[tmpWItr][tmpWItrTwo] " << tmpWAr[tmpWItr][tmpWItrTwo] << "\n";
                                    }
                                }
                            }
                            if (finalWAr.size()){
                                for (UInt_t tmpWItr=0;tmpWItr<finalWAr.size();tmpWItr++){
                                    std::cout << "finalWAr[tmpWItr] " << finalWAr[tmpWItr] << "\n";
                                }
                            }
                            if (HTobbBoolL){
                                genErrorChannelCtr += 1;
                                //genErrorChannelWeightedCtr += *genWeight;
                                evWeightedCtrMaskTwo[5] = true;
                            }
                            else{
                                genErrorChannelNoHTobbCtr += 1;
                                //genErrorChannelNoHTobbWeightedCtr += *genWeight;
                                evWeightedCtrMaskTwo[11] = true;
                            }

                        }
                        else{
                            if (debugGenPart) {
                                std::cout << "W Found\n";
                            }
                            if (ZDecFound and WDecFound) {
                                if (GenPart_pt[finalZDecIndAr[0][0]] > GenPart_pt[finalZDecIndAr[0][1]]){
                                    ZOneDecLeadInd = finalZDecIndAr[0][0];
                                    ZOneDecTrailingInd = finalZDecIndAr[0][1];
                                }
                                else{
                                    ZOneDecLeadInd = finalZDecIndAr[0][1];
                                    ZOneDecTrailingInd = finalZDecIndAr[0][0];
                                }
                                if (GenPart_pt[finalWDecIndAr[0][0]] > GenPart_pt[finalWDecIndAr[0][1]]){
                                    WDecLeadInd = finalWDecIndAr[0][0];
                                    WDecTrailingInd = finalWDecIndAr[0][1];
                                }
                                else{
                                    WDecLeadInd = finalWDecIndAr[0][1];
                                    WDecTrailingInd = finalWDecIndAr[0][0];
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
                                if (abs(finalWDecAr[0][0])==15 || abs(finalWDecAr[0][1])==15){
                                    int tmpLepInd = -1;
                                    std::vector<Int_t> tauAr;
                                    bool tauBool = false;
                                    UInt_t tauDecPDG = 0;
                                    if (abs(finalWDecAr[0][0]) == 15){
                                        tauAr.push_back(finalWDecIndAr[0][0]);
                                    }
                                    else{
                                        tauAr.push_back(finalWDecIndAr[0][1]);
                                    }
                                    //std::cout << "Entering GenPart loop " << tauAr[0]<< " " << tauTwoAr[0] << "\n";
                                    for (UInt_t i=0;i<*nGenPart;i++){
                                        Int_t tmpPDGId = GenPart_pdgId[i];
                                        Int_t tmpMotherID = GenPart_genPartIdxMother[i];
                                        
                                        std::vector<Int_t> tmpIndAr;
                                        //std::cout << "i " << i << " " << tmpPDGId<< " " << tmpMotherID << "\n";
                                        if (!tauBool){
                                            for (UInt_t j=0;j<tauAr.size();j++){
                                                //std::cout << "t1j " << j << " " << tauAr[j]<<"\n";
                                                if (tmpMotherID == tauAr[j]){
                                                    if (abs(tmpPDGId) == 15) tmpIndAr.push_back(i);
                                                    else if (abs(tmpPDGId) == 13 || abs(tmpPDGId) == 11) {
                                                        tauBool = true;
                                                        tauDecPDG = abs(tmpPDGId);
                                                        tmpLepInd = i;
                                                    }
                                                }
                                            }
                                            if (tmpIndAr.size()) {
                                                for (UInt_t j=0;j<tmpIndAr.size();j++){
                                                    tauAr.push_back(tmpIndAr[j]);
                                                }
                                            }
                                        }
                                        
                                    }
                                    //std::cout << "tbool " << tauOneBool << " " << tauTwoBool <<"\n";
                                    if (tauBool) {
                                        WIsLeptonic = true;
                                        WDecLeadInd = tmpLepInd;
                                    }
                                        
                                }

                                if (debugGenPart){
                                    std::cout << "finalZDecAr[0][0] " << finalZDecAr[0][0] << " finalZDecAr[0][1] " << finalZDecAr[0][1] <<"\n";
                                    std::cout << "finalWDecAr[0][0] " << finalWDecAr[0][0] << " finalWDecAr[0][1] " << finalWDecAr[0][1] << "\n";
                                }
                                ZOneIsHadronic = (finalZDecAr[0][0]>-9 && finalZDecAr[0][0]<9 && finalZDecAr[0][1]>-9 && finalZDecAr[0][1]<9);
                                WIsHadronic = (finalWDecAr[0][0]>-9 && finalWDecAr[0][0]<9 && finalWDecAr[0][1]>-9 && finalWDecAr[0][1]<9);
                                if (!ZOneIsLeptonic) ZOneIsLeptonic = ((abs(finalZDecAr[0][0])==11 || abs(finalZDecAr[0][0])==13) && (abs(finalZDecAr[0][1])==11 || abs(finalZDecAr[0][1])==13));
                                if (!WIsLeptonic) WIsLeptonic = ((abs(finalWDecAr[0][0])==11 || abs(finalWDecAr[0][0])==13) || (abs(finalWDecAr[0][1])==11 || abs(finalWDecAr[0][1])==13));

                                if (ZOneIsLeptonic && WIsLeptonic) WLepZLep = true;
                                else if (ZOneIsHadronic && WIsLeptonic) WLepZHadronic = true;
                                else if (ZOneIsLeptonic && WIsHadronic) WHadronicZLep = true;
                                else if (ZOneIsHadronic && WIsHadronic) WHadronicZHadronic = true;
                                
                                if (debugGenPart) std::cout << "WLepZLep " << WLepZLep << "WLepZHadronic" << WLepZHadronic << "WHadronicZLep" << WHadronicZLep << "WHadronicZHadronic" << WHadronicZHadronic << "\n";
                                float tmpHEtaFordR = GenPart_eta[finalHAr[0]];
                                float tmpHPhiFordR = GenPart_phi[finalHAr[0]];
                                float tmpZEtaFordR;
                                float tmpZPhiFordR;
                                
                                float  tmpWEtaFordR;
                                float  tmpWPhiFordR;

                                tmpZEtaFordR = GenPart_eta[finalZAr[0]];
                                tmpZPhiFordR = GenPart_phi[finalZAr[0]];
                                tmpWEtaFordR = GenPart_eta[finalWAr[0]];
                                tmpWPhiFordR = GenPart_phi[finalWAr[0]];

                                
                                HdRFromZL = calcDeltaR(tmpHPhiFordR,tmpHEtaFordR,tmpZPhiFordR,tmpZEtaFordR);
                                HdRFromWL = calcDeltaR(tmpHPhiFordR,tmpHEtaFordR,tmpWPhiFordR,tmpWEtaFordR);
                                ZdRFromWL = calcDeltaR(tmpZPhiFordR,tmpZEtaFordR,tmpWPhiFordR,tmpWEtaFordR);

                                
                                nLHEReweightingWeightGenL = *nLHEReweightingWeight;
                                for (UInt_t nReweightItr=0; nReweightItr<nLHEReweightingWeightGenL;nReweightItr++){
                                    LHEReweightingWeightGenL.push_back(LHEReweightingWeight[nReweightItr]);
                                }

                                genTree->Fill();

                                LHEReweightingWeightGenL.clear();
                                }



                            
                        }

                        if (WLepZLep) {

                            
                            if (HTobbBoolL){
                                genWLepZLepChannelCtr += 1;
                                //genWLepZLepChannelWeightedCtr += *genWeight;

                            }
                            else{
                                genWLepZLepChannelNoHTobbCtr += 1;
                                //genWLepZLepChannelNoHTobbWeightedCtr += *genWeight;
                            }

                        }

                        else if (WLepZHadronic) {

                            
                            if (HTobbBoolL){
                                genWLepZHadronicChannelCtr += 1;
                                //genWLepZHadronicChannelWeightedCtr += *genWeight;

                            }
                            else{
                                genWLepZHadronicChannelNoHTobbCtr += 1;
                                //genWLepZHadronicChannelNoHTobbWeightedCtr += *genWeight;
                            }

                        }
                        else if (WHadronicZLep) {

                            
                            if (HTobbBoolL){
                                genWHadronicZLepChannelCtr += 1;
                                //genWHadronicZLepChannelWeightedCtr += *genWeight;

                            }
                            else{
                                genWHadronicZLepChannelNoHTobbCtr += 1;
                                //genWHadronicZLepChannelNoHTobbWeightedCtr += *genWeight;
                            }

                        }

                        if (WHadronicZHadronic) {

                            
                            if (HTobbBoolL){
                                genWHadronicZHadronicChannelCtr += 1;
                                //genWHadronicZHadronicChannelWeightedCtr += *genWeight;

                            }
                            else{
                                genWHadronicZHadronicChannelNoHTobbCtr += 1;
                                //genWHadronicZHadronicChannelNoHTobbWeightedCtr += *genWeight;
                            }

                        }
                        else {
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

            if (WLepZLep) {
                if (HTobbBoolL){
                    evWeightedCtrMaskOne[1] = true;
                    evWeightedCtrMaskTwo[0] = true;
                }
                else {
                    evWeightedCtrMaskOne[6] = true;
                    evWeightedCtrMaskTwo[6] = true;
                    evWeightedCtrMaskTwo[12] = true;
                }
            }
            else if (WLepZHadronic) {
                if (HTobbBoolL){
                    evWeightedCtrMaskOne[2] = true;
                    evWeightedCtrMaskTwo[1] = true;
                }
                else {
                    evWeightedCtrMaskOne[7] = true;
                    evWeightedCtrMaskTwo[7] = true;
                    evWeightedCtrMaskTwo[12] = true;
                }
            }
            else if (WHadronicZLep) {
                if (HTobbBoolL){
                    evWeightedCtrMaskOne[3] = true;
                    evWeightedCtrMaskTwo[2] = true;
                }
                else {
                    evWeightedCtrMaskOne[8] = true;
                    evWeightedCtrMaskTwo[8] = true;
                    evWeightedCtrMaskTwo[12] = true;
                }
            }
            else if (WHadronicZHadronic) {
                if (HTobbBoolL){
                    evWeightedCtrMaskOne[4] = true;
                    evWeightedCtrMaskTwo[3] = true;
                }
                else {
                    evWeightedCtrMaskOne[9] = true;
                    evWeightedCtrMaskTwo[9] = true;
                    evWeightedCtrMaskTwo[12] = true;
                }
            }
            else {
                if (HTobbBoolL){
                    evWeightedCtrMaskOne[5] = true;
                    if (!evWeightedCtrMaskTwo[5]) evWeightedCtrMaskTwo[4] = true;
                }
                else {
                    evWeightedCtrMaskOne[10] = true;
                    if (!evWeightedCtrMaskTwo[11]) evWeightedCtrMaskTwo[10] = true;
                    evWeightedCtrMaskTwo[12] = true;
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
                if (WLepZLep) {
                    if (HTobbBoolL){
                        passFlagWLepZLepCtr += 1;
                        //passFlagWLepZLepWeightedCtr += *genWeight;
                    }
                    else {
                        passFlagWLepZLepNoHTobbCtr += 1;
                        //passFlagWLepZLepNoHTobbWeightedCtr += *genWeight;

                    }
                }
                else if (WLepZHadronic) {
                    if (HTobbBoolL){
                        passFlagWLepZHadronicCtr += 1;
                        //passFlagWLepZHadronicWeightedCtr += *genWeight;
                    }
                    else{
                        passFlagWLepZHadronicNoHTobbCtr += 1;
                        //passFlagWLepZHadronicNoHTobbWeightedCtr += *genWeight;

                    }
                }
                else if (WHadronicZLep) {
                    if (HTobbBoolL){
                        passFlagWHadronicZLepCtr += 1;
                        //passFlagWHadronicZLepWeightedCtr += *genWeight;
                    }
                    else {
                        passFlagWHadronicZLepNoHTobbCtr += 1;
                        //passFlagWHadronicZLepNoHTobbWeightedCtr += *genWeight;

                    }
                }
                else if (WHadronicZHadronic) {
                    if (HTobbBoolL){
                        passFlagWHadronicZHadronicCtr += 1;
                        //passFlagWHadronicZHadronicWeightedCtr += *genWeight;
                    }
                    else {
                        passFlagWHadronicZHadronicNoHTobbCtr += 1;
                        //passFlagWHadronicZHadronicNoHTobbWeightedCtr += *genWeight;

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
            bool passHLTBool = (*HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ || *HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8);
            if (useSingleLepHLT) {
                passHLTBool = (passHLTBool || *HLT_IsoMu27 || *HLT_Mu50 || *HLT_Ele32_WPTight_Gsf_L1DoubleEG);
            }
            /*
            bool passHLTBool = (*HLT_Ele32_WPTight_Gsf_L1DoubleEG || 
            *HLT_IsoMu27 || *HLT_Mu50 || 
            *HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ || 
            *HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8);
            */
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

                if (WLepZLep) {
                    if (HTobbBoolL){
                        passHLTWLepZLepCtr += 1;
                        //passHLTWLepZLepWeightedCtr += *genWeight;
                    }
                    else {
                        passHLTWLepZLepNoHTobbCtr += 1;
                        //passHLTWLepZLepNoHTobbWeightedCtr += *genWeight;

                    }
                }
                else if (WLepZHadronic) {
                    if (HTobbBoolL){
                        passHLTWLepZHadronicCtr += 1;
                        //passHLTWLepZHadronicWeightedCtr += *genWeight;
                    }
                    else{
                        passHLTWLepZHadronicNoHTobbCtr += 1;
                        //passHLTWLepZHadronicNoHTobbWeightedCtr += *genWeight;

                    }
                }
                else if (WHadronicZLep) {
                    if (HTobbBoolL){
                        passHLTWHadronicZLepCtr += 1;
                        //passHLTWHadronicZLepWeightedCtr += *genWeight;
                    }
                    else {
                        passHLTWHadronicZLepNoHTobbCtr += 1;
                        //passHLTWHadronicZLepNoHTobbWeightedCtr += *genWeight;

                    }
                }
                else if (WHadronicZHadronic) {
                    if (HTobbBoolL){
                        passHLTWHadronicZHadronicCtr += 1;
                        //passHLTWHadronicZHadronicWeightedCtr += *genWeight;
                    }
                    else {
                        passHLTWHadronicZHadronicNoHTobbCtr += 1;
                        //passHLTWHadronicZHadronicNoHTobbWeightedCtr += *genWeight;

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
                if (WLepZLep) {
                    if (HTobbBoolL){
                        passnFJWLepZLepCtr += 1;
                        //passnFJWLepZLepWeightedCtr += *genWeight;
                    }
                    else {
                        passnFJWLepZLepNoHTobbCtr += 1;
                        //passnFJWLepZLepNoHTobbWeightedCtr += *genWeight;

                    }
                }
                else if (WLepZHadronic) {
                    if (HTobbBoolL){
                        passnFJWLepZHadronicCtr += 1;
                        //passnFJWLepZHadronicWeightedCtr += *genWeight;
                    }
                    else {
                        passnFJWLepZHadronicNoHTobbCtr += 1;
                        //passnFJWLepZHadronicNoHTobbWeightedCtr += *genWeight;

                    }
                }
                else if (WHadronicZLep) {
                    if (HTobbBoolL){
                        passnFJWHadronicZLepCtr += 1;
                        //passnFJWHadronicZLepWeightedCtr += *genWeight;
                    }
                    else {
                        passnFJWHadronicZLepNoHTobbCtr += 1;
                        //passnFJWHadronicZLepNoHTobbWeightedCtr += *genWeight;

                    }
                }
                else if (WHadronicZHadronic) {
                    if (HTobbBoolL){
                        passnFJWHadronicZHadronicCtr += 1;
                        //passnFJWHadronicZHadronicWeightedCtr += *genWeight;
                    }
                    else {
                        passnFJWHadronicZHadronicNoHTobbCtr += 1;
                        //passnFJWHadronicZHadronicNoHTobbWeightedCtr += *genWeight;

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
                if (WLepZLep) {
                    if (HTobbBoolL){
                        passnVBFWLepZLepCtr += 1;
                        //passnVBFWLepZLepWeightedCtr += *genWeight;
                    }
                    else {
                        passnVBFWLepZLepNoHTobbCtr += 1;
                        //passnVBFWLepZLepNoHTobbWeightedCtr += *genWeight;
                        
                    }
                }
                else if (WLepZHadronic) {
                    if (HTobbBoolL){
                        passnVBFWLepZHadronicCtr += 1;
                        //passnVBFWLepZHadronicWeightedCtr += *genWeight;
                    }
                    else {
                        passnVBFWLepZHadronicNoHTobbCtr += 1;
                        //passnVBFWLepZHadronicNoHTobbWeightedCtr += *genWeight;
                        
                    }
                }
                else if (WHadronicZLep) {
                    if (HTobbBoolL){
                        passnVBFWHadronicZLepCtr += 1;
                        //passnVBFWHadronicZLepWeightedCtr += *genWeight;
                    }
                    else {
                        passnVBFWHadronicZLepNoHTobbCtr += 1;
                        //passnVBFWHadronicZLepNoHTobbWeightedCtr += *genWeight;
                        
                    }
                }
                else if (WHadronicZHadronic) {
                    if (HTobbBoolL){
                        passnVBFWHadronicZHadronicCtr += 1;
                        //passnVBFWHadronicZHadronicWeightedCtr += *genWeight;
                    }
                    else {
                        passnVBFWHadronicZHadronicNoHTobbCtr += 1;
                        //passnVBFWHadronicZHadronicNoHTobbWeightedCtr += *genWeight;
                        
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
            HLT_Ele32_WPTight_Gsf_L1DoubleEGL = *HLT_Ele32_WPTight_Gsf_L1DoubleEG;
            HLT_IsoMu27L = *HLT_IsoMu27;
            HLT_Mu50L = *HLT_Mu50;
            HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZL = *HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;
            HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8L = *HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8;

            //2016
            HLT_Ele27_WPTight_GsfL = false;
            HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZL = false;

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

        std::vector<string> genDecayStrAr {"W lep Z lep","W lep Z hadronic","W hadronic Z lep","W hadronic Z hadronic","gen other"};

        

        std::vector<UInt_t> genFlagDecayAr {passFlagWLepZLepCtr,passFlagWLepZHadronicCtr,passFlagWHadronicZLepCtr,passFlagWHadronicZHadronicCtr,passFlagGenOtherCtr};
        std::vector<UInt_t> genHLTDecayAr {passHLTWLepZLepCtr,passHLTWLepZHadronicCtr,passHLTWHadronicZLepCtr,passHLTWHadronicZHadronicCtr,passHLTGenOtherCtr};
        std::vector<UInt_t> gennFJDecayAr {passnFJWLepZLepCtr,passnFJWLepZHadronicCtr,passnFJWHadronicZLepCtr,passnFJWHadronicZHadronicCtr,passnFJGenOtherCtr};
        std::vector<UInt_t> gennVBFDecayAr {passnVBFWLepZLepCtr,passnVBFWLepZHadronicCtr,passnVBFWHadronicZLepCtr,passnVBFWHadronicZHadronicCtr,passnVBFGenOtherCtr};

        std::vector<UInt_t> genFlagDecayNoHTobbAr {passFlagWLepZLepNoHTobbCtr,passFlagWLepZHadronicNoHTobbCtr,passFlagWHadronicZLepNoHTobbCtr,passFlagWHadronicZHadronicNoHTobbCtr,passFlagGenOtherNoHTobbCtr};
        std::vector<UInt_t> genHLTDecayNoHTobbAr {passHLTWLepZLepNoHTobbCtr,passHLTWLepZHadronicNoHTobbCtr,passHLTWHadronicZLepNoHTobbCtr,passHLTWHadronicZHadronicNoHTobbCtr,passHLTGenOtherNoHTobbCtr};
        std::vector<UInt_t> gennFJDecayNoHTobbAr {passnFJWLepZLepNoHTobbCtr,passnFJWLepZHadronicNoHTobbCtr,passnFJWHadronicZLepNoHTobbCtr,passnFJWHadronicZHadronicNoHTobbCtr,passnFJGenOtherNoHTobbCtr};
        std::vector<UInt_t> gennVBFDecayNoHTobbAr {passnVBFWLepZLepNoHTobbCtr,passnVBFWLepZHadronicNoHTobbCtr,passnVBFWHadronicZLepNoHTobbCtr,passnVBFWHadronicZHadronicNoHTobbCtr,passnVBFGenOtherNoHTobbCtr};

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
        std::cout << "Gen WLepZLep Channel: " << genWLepZLepChannelCtr << " ------------------- \n";
        std::cout << "Gen WLepZHadronic Channel: " << genWLepZHadronicChannelCtr << " ------------------- \n";
        std::cout << "Gen WHadronicZLep Channel: " << genWHadronicZLepChannelCtr << " ------------------- \n";
        std::cout << "Gen WHadronicZHadronic Channel: " << genWHadronicZHadronicChannelCtr << " ------------------- \n";
        std::cout << "Gen Other Channel: " << genOtherChannelCtr << " ------------------- \n";
        std::cout << "Gen Error Channel: " << genErrorChannelCtr << " ------------------- \n";
        std::cout << "Channels without HTobb\n";
        std::cout << "Gen NoHTobb WLepZLep Channel: " << genWLepZLepChannelNoHTobbCtr << " ------------------- \n";
        std::cout << "Gen NoHTobb WLepZHadronic Channel: " << genWLepZHadronicChannelNoHTobbCtr << " ------------------- \n";
        std::cout << "Gen NoHTobb WHadronicZLep Channel: " << genWHadronicZLepChannelNoHTobbCtr << " ------------------- \n";
        std::cout << "Gen NoHTobb WHadronicZHadronic Channel: " << genWHadronicZHadronicChannelNoHTobbCtr << " ------------------- \n";
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
