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
#include "new032022KinematicsAnalysisSlimmed.h"
#include "new032022KinematicsAnalysis_Functions.h"
#include "new032022KinematicsAnalysis_FileList.h"
#include<time.h>

#include<algorithm>
#include<chrono>
#include<ctime>
#include<fstream>
#include<iostream>
#include<mutex>

#include<thread>


#include<sys/stat.h>
#include<errno.h>



////////////////////////////////START OF MAIN FUNCTION////////////////////////////////
////////////////////////////////START OF MAIN FUNCTION////////////////////////////////
////////////////////////////////START OF MAIN FUNCTION////////////////////////////////
////////////////////////////////START OF MAIN FUNCTION////////////////////////////////


void new032022Analysis(){
    // Open the file. Note that the name of your file outside this class
    // will probably NOT be experiment.root.
    std::cout << "start\n";
    clock_t startt = clock();
    //Analyzer will run over all files put into fileAr

    std::vector<std::string> fileAr;

    //Gen Jet matching dR cut

    float genMatchdRCut;
    std::string cutName;

    if (useTighterCut) {
        genMatchdRCut = 0.1;
        cutName = "TighterCut";
    }
    else {
        genMatchdRCut = 0.4;
        cutName = "";
    }


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

    if (MGC2VEtaDifCut){
        saveName = "C2VEtaDifCut";
        isBackground = false;
        int arrSize = sizeof(MGC2VEtaDifCutAr)/sizeof(MGC2VEtaDifCutAr[0]);
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = strAdd+"/dlutton/NanoAODFiles/pphzzjj_C2V_QCD0SMHLOOP0NPLE1C2VE1KappaFramework_100Ev_3p0c2V_100GeVIMJetCut_2EtaDifCut/"+MGC2VEtaDifCutAr[i];
            fileAr.push_back(tmpStrWithPath);
        }
        useLHETree = true;
        useFJGenMatchTree = true;
    }
    else if (MGOSix){
        saveName = "OSix";
        isBackground = false;
        int arrSize = sizeof(MGOSixAr)/sizeof(MGOSixAr[0]);
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = strAdd+"/dlutton/NanoAODFiles/pphzzjj_OSix_QCD0SMHLOOP0NPLE1NPcHE1_100Ev_0p4cH_100GeVIMJetCut/"+MGOSixAr[i];
            fileAr.push_back(tmpStrWithPath);
        }
        useLHETree = true;
        useFJGenMatchTree = true;
    }
    else if (MGOSixEtaDifCut){
        saveName = "OSix_EtaDifCut";
        isBackground = false;
        int arrSize = sizeof(MGOSixEtaDifCutAr)/sizeof(MGOSixEtaDifCutAr[0]);
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = strAdd+"/dlutton/NanoAODFiles/pphzzjj_OSix_QCD0SMHLOOP0NPLE1NPcHE1_100Ev_0p4cH_100GeVIMJetCut_2EtaDifCut/"+MGOSixEtaDifCutAr[i];
            fileAr.push_back(tmpStrWithPath);
        }
        useLHETree = true;
        useFJGenMatchTree = true;
    }
    else if (MGOHBox){
        saveName = "OHBox";
        isBackground = false;
        int arrSize = sizeof(MGOHBoxAr)/sizeof(MGOHBoxAr[0]);
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = strAdd+"/dlutton/NanoAODFiles/pphzzjj_OHBox_QCD0SMHLOOP0NPLE1NPcHBoxE1_100Ev_0p5cHBox_100GeVIMJetCut/"+MGOHBoxAr[i];
            fileAr.push_back(tmpStrWithPath);
        }
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (MGOHBoxEtaDifCut){
        saveName = "OHBox_EtaDifCut";
        isBackground = false;
        int arrSize = sizeof(MGOHBoxEtaDifCutAr)/sizeof(MGOHBoxEtaDifCutAr[0]);
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = strAdd+"/dlutton/NanoAODFiles/pphzzjj_OHBox_QCD0SMHLOOP0NPLE1NPcHBoxE1_100Ev_0p5cHBox_100GeVIMJetCut_2EtaDifCut/"+MGOHBoxEtaDifCutAr[i];
            fileAr.push_back(tmpStrWithPath);
        }
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (MGOHDD){
        saveName = "OHDD";
        isBackground = false;
        int arrSize = sizeof(MGOHDDAr)/sizeof(MGOHDDAr[0]);
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = strAdd+"/dlutton/NanoAODFiles/pphzzjj_OHDD_QCD0SMHLOOP0NPLE1NPcHDDE1_0p6cHDD_100GeVIMJetCut/"+MGOHDDAr[i];
            fileAr.push_back(tmpStrWithPath);
        }
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (MGOHDDEtaDifCut){
        saveName = "OHDD_EtaDifCut";
        isBackground = false;
        int arrSize = sizeof(MGOHDDEtaDifCutAr)/sizeof(MGOHDDEtaDifCutAr[0]);
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = strAdd+"/dlutton/NanoAODFiles/pphzzjj_OHDD_QCD0SMHLOOP0NPLE1NPcHDDE1_0p6cHDD_100GeVIMJetCut_2EtaDifCut/"+MGOHDDEtaDifCutAr[i];
            fileAr.push_back(tmpStrWithPath);
        }
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (MGOHW){
        saveName = "OHW";
        isBackground = false;
        int arrSize = sizeof(MGOHWAr)/sizeof(MGOHWAr[0]);
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = strAdd+"/dlutton/NanoAODFiles/pphzzjjQCD0SMHLOOP0NPE1NPcHWE1QEDE5/"+MGOHWAr[i];
            fileAr.push_back(tmpStrWithPath);
        }
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (MGSM){
        saveName = "SM";
        isBackground = false;
        int arrSize = sizeof(MGSMAr)/sizeof(MGSMAr[0]);
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = strAdd+"/dlutton/NanoAODFiles/pphzzjjQCD0SMHLOOP0QEDE5NPE0/"+MGSMAr[i];
            fileAr.push_back(tmpStrWithPath);
        }
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (ttHToBBBackground){
        //saveName = "ttHToBB";
        crossSection = 0.5071*0.582;

        saveName = "ttHToBB";
        
        isBackground = true;
        int arrSize = sizeof(ttHToBBBackgroundAr)/sizeof(ttHToBBBackgroundAr[0]);
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(ttHToBBBackgroundAr[i]);
        }
    }
    else if (ttZJetsBackground){
        //saveName = "ttZJets";
        
        crossSection = 0.5407;
        saveName = "ttZJets";
        isBackground = true;
        int arrSize = sizeof(ttZJetsBackgroundAr)/sizeof(ttZJetsBackgroundAr[0]);
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(ttZJetsBackgroundAr[i]);
        }
    }
    else if (DYBackground){
        //saveName = "DY";
        
        crossSection = 5364;
        saveName = "DY";

        isBackground = true;
        int arrSize = sizeof(DYBackgroundAr)/sizeof(DYBackgroundAr[0]);
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(DYBackgroundAr[i]);
        }
    }
    else if (QCDPT170to300Background){
        //saveName = "QCDPT170to300";
        
        crossSection = 103300.0;

        saveName = "QCDPT170to300";
        
        isBackground = true;
        int arrSize = sizeof(QCDPT170to300BackgroundAr)/sizeof(QCDPT170to300BackgroundAr[0]);
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(QCDPT170to300BackgroundAr[i]);
        }
    }
    else if (QCDPT300to470Background){
        //saveName = "QCDPT300to470";
        
        crossSection = 6826.0;

        saveName = "QCDPT300to470";
        
        isBackground = true;
        int arrSize = sizeof(QCDPT300to470BackgroundAr)/sizeof(QCDPT300to470BackgroundAr[0]);
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(QCDPT300to470BackgroundAr[i]);
        }
    }
    else if (QCDPT470to600Background){
        //saveName = "QCDPT470to600";
        
        crossSection = 552.6;
        
        saveName = "QCDPT470to600";

        isBackground = true;
        int arrSize = sizeof(QCDPT470to600BackgroundAr)/sizeof(QCDPT470to600BackgroundAr[0]);
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(QCDPT470to600BackgroundAr[i]);
        }
    }
    else if (QCDPT600to800Background){
        //saveName = "QCDPT600to800";
        
        crossSection = 156.6;

        saveName = "QCDPT600to800";
        
        isBackground = true;
        int arrSize = sizeof(QCDPT600to800BackgroundAr)/sizeof(QCDPT600to800BackgroundAr[0]);
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(QCDPT600to800BackgroundAr[i]);
        }
    }
    else if (QCDPT800to1000Background){
        //saveName = "QCDPT800to1000";
        
        crossSection = 26.32;

        saveName = "QCDPT800to1000";
        
        isBackground = true;
        int arrSize = sizeof(QCDPT800to1000BackgroundAr)/sizeof(QCDPT800to1000BackgroundAr[0]);
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(QCDPT800to1000BackgroundAr[i]);
        }
    }
    else if (QCDPT1000to1400Background){
        //saveName = "QCDPT1000to1400";
        
        crossSection = 7.5;

        saveName = "QCDPT1000to1400";
        
        isBackground = true;
        int arrSize = sizeof(QCDPT1000to1400BackgroundAr)/sizeof(QCDPT1000to1400BackgroundAr[0]);
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(QCDPT1000to1400BackgroundAr[i]);
        }
    }
    else if (QCDPT1400to1800Background){
        //saveName = "QCDPT1400to1800";
        
        crossSection = 0.6479;

        saveName = "QCDPT1400to1800";
        
        isBackground = true;
        int arrSize = sizeof(QCDPT1400to1800BackgroundAr)/sizeof(QCDPT1400to1800BackgroundAr[0]);
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(QCDPT1400to1800BackgroundAr[i]);
        }
    }
    else if (QCDPT1800to2400Background){
        //saveName = "QCDPT1800to2400";
        
        crossSection = 0.08715;

        saveName = "QCDPT1800to2400";
        
        isBackground = true;
        int arrSize = sizeof(QCDPT1800to2400BackgroundAr)/sizeof(QCDPT1800to2400BackgroundAr[0]);
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(QCDPT1800to2400BackgroundAr[i]);
        }
    }
    else if (QCDPT2400to3200Background){
        //saveName = "QCDPT2400to3200";
        
        crossSection = 0.005242;

        saveName = "QCDPT2400to3200";
        
        isBackground = true;
        int arrSize = sizeof(QCDPT2400to3200BackgroundAr)/sizeof(QCDPT2400to3200BackgroundAr[0]);
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(QCDPT2400to3200BackgroundAr[i]);
        }
    }
    else if (QCDPT3200toInfBackground){
        //saveName = "QCDPT3200toInf";
        
        crossSection = 0.0001349;

        saveName = "QCDPT3200toInf";
        
        isBackground = true;
        int arrSize = sizeof(QCDPT3200toInfBackgroundAr)/sizeof(QCDPT3200toInfBackgroundAr[0]);
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(QCDPT3200toInfBackgroundAr[i]);
        }
    }
    else if (testRun){
        saveName = "testRun";
        fileAr.push_back("./unweighted_eventspphzzjjQCD0SMHLOOP0NPE1NPcHWE1QEDE5ResMasAllVer100Ev10080Seed_0p999cHW100GeVIMJetCut_200.root");
        useLHETree = true;
        useFJGenMatchTree = true;
        
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
    std::string outFileStr = "new032022FullAnalysis"+saveName+cutName+".root";
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


    UInt_t passHLTCtr = 0;
    UInt_t passAnyChannelCtr = 0;
    UInt_t passLepChannelCtr = 0;
    UInt_t passSemiLepChannelCtr = 0;
    UInt_t passHadChannelCtr = 0;
    UInt_t passLepAndSemiLepChannelCtr = 0;
    UInt_t passLepAndHadChannelCtr = 0;
    UInt_t passSemiLepAndHadChannelCtr = 0;
    UInt_t passAllChannelCtr = 0;
    UInt_t passVBFJets = 0;
    UInt_t passFatJets = 0;
    UInt_t passGenPart = 0;
    UInt_t passFJMatch = 0;
    UInt_t passLepCut = 0;
    UInt_t passSemiLepCut = 0;
    UInt_t passHadCut = 0;

    UInt_t ZFJSameJetCtr = 0;

    UInt_t tryingLepCtr = 0;
    UInt_t tryingSemiLepCtr = 0;
    UInt_t tryingHadCtr = 0;

    UInt_t passesCutsCtr = 0;


    float crossSectionAvg = 0.;
    UInt_t crossSectionCtr = 0;
    UInt_t evRunOver = 0;
    UInt_t evCount = 0;
    UInt_t evPassCount = 0;
    
    UInt_t nEv;
    UInt_t nEvPass;

    TTree *evNumTree = new TTree("evNumTree","evNumTree");

    evNumTree->Branch("nEv",&nEv,"nEv/i");
    evNumTree->Branch("nEvPass",&nEvPass,"nEvPass/i");


    //creating Full Analysis tree
    //"L" is for leaf
    //First jets
    UInt_t nJetL;
    float jetLeadPtL;
    float jetTrailingPtL;
    float jetLeadPhiL;
    float jetTrailingPhiL;
    float jetPairInvMassL;
    float jetLeadEtaL;
    float jetTrailingEtaL;
    //now fat jets
    UInt_t nFatJetL;
    /*
    float hFatJet_pt_fromPtL;
    float hFatJet_phi_fromPtL;
    float hFatJet_eta_fromPtL;
    float hFatJet_mass_fromPtL;
    float hFatJet_HTag_fromPtL;
    */
    float hFatJet_pt_fromHTagL;
    float hFatJet_phi_fromHTagL;
    float hFatJet_eta_fromHTagL;
    float hFatJet_mass_fromHTagL;
    float hFatJet_HTag_fromHTagL;

    //Now GenPart

    UInt_t nGenPartL;
    /*
    float hGenPartDR_fromPtL;
    float hGenPartInd_fromPtL;
    float hGenPartpdgId_fromPtL;
    Int_t hGenPartFirstMompdgId_fromPtL;
    */
    float hGenPartDR_fromHTagL;
    float hGenPartInd_fromHTagL;
    float hGenPartpdgId_fromHTagL;
    Int_t hGenPartFirstMompdgId_fromHTagL;

    //Now HLT stuff;
    bool hbbTagL;

    bool doubleElecHLTL;
    bool doubleMuonHLTL;
    bool muonEGHLTL;
    bool elecHLTL;
    bool muonHLTL;
    bool hadHLTL;
    bool isLeptonicL;
    bool isSemiLeptonicL;
    bool isHadronicL;

    //Branches for distinguishing between channels;
    bool passedLepL;
    bool passedSemiLepL;
    bool passedHadL;

    //Now tree and branches;

    TTree *FATree = new TTree("FATree", "FATree");

    //cutTree->Branch("evInd",evInd,"evInd/I");

    FATree->Branch("nJetL",&nJetL,"nJetL/i");
    FATree->Branch("jetLeadPtL",&jetLeadPtL,"jetLeadPtL/F");
    FATree->Branch("jetTrailingPtL",&jetTrailingPtL,"jetTrailingPtL/F");
    FATree->Branch("jetLeadPhiL",&jetLeadPhiL,"jetLeadPhiL/F");
    FATree->Branch("jetTrailingPhiL",&jetTrailingPhiL,"jetTrailingPhiL/F");
    FATree->Branch("jetPairInvMassL",&jetPairInvMassL,"jetPairInvMassL/F");
    FATree->Branch("jetLeadEtaL",&jetLeadEtaL,"jetLeadEtaL/F");
    FATree->Branch("jetTrailingEtaL",&jetTrailingEtaL,"jetTrailingEtaL/F");
    //now fat jets;
    FATree->Branch("nFatJetL",&nFatJetL,"nFatJetL/i");
    /*
    FATree->Branch("hFatJet_pt_fromPtL",&hFatJet_pt_fromPtL,"hFatJet_pt_fromPtL/F");
    FATree->Branch("hFatJet_phi_fromPtL",&hFatJet_phi_fromPtL,"hFatJet_phi_fromPtL/F");
    FATree->Branch("hFatJet_eta_fromPtL",&hFatJet_eta_fromPtL,"hFatJet_eta_fromPtL/F");
    FATree->Branch("hFatJet_mass_fromPtL",&hFatJet_mass_fromPtL,"hFatJet_mass_fromPtL/F");
    FATree->Branch("hFatJet_HTag_fromPtL",&hFatJet_HTag_fromPtL,"hFatJet_HTag_fromPtL/F");
    */
    FATree->Branch("hFatJet_pt_fromHTagL",&hFatJet_pt_fromHTagL,"hFatJet_pt_fromHTagL/F");
    FATree->Branch("hFatJet_phi_fromHTagL",&hFatJet_phi_fromHTagL,"hFatJet_phi_fromHTagL/F");
    FATree->Branch("hFatJet_eta_fromHTagL",&hFatJet_eta_fromHTagL,"hFatJet_eta_fromHTagL/F");
    FATree->Branch("hFatJet_mass_fromHTagL",&hFatJet_mass_fromHTagL,"hFatJet_mass_fromHTagL/F");
    FATree->Branch("hFatJet_HTag_fromHTagL",&hFatJet_HTag_fromHTagL,"hFatJet_HTag_fromHTagL/F");

    //now genpart
    FATree->Branch("nGenPartL",&nGenPartL,"nGenPartL/i");
    /*
    FATree->Branch("hGenPartDR_fromPtL",&hGenPartDR_fromPtL,"hGenPartDR_fromPtL/F");
    FATree->Branch("hGenPartInd_fromPtL",&hGenPartInd_fromPtL,"hGenPartInd_fromPtL/F");
    FATree->Branch("hGenPartpdgId_fromPtL",&hGenPartpdgId_fromPtL,"hGenPartpdgId_fromPtL/F");
    FATree->Branch("hGenPartFirstMompdgId_fromPtL",&hGenPartFirstMompdgId_fromPtL,"hGenPartFirstMompdgId_fromPtL/I");
    */
    FATree->Branch("hGenPartDR_fromHTagL",&hGenPartDR_fromHTagL,"hGenPartDR_fromHTagL/F");
    FATree->Branch("hGenPartInd_fromHTagL",&hGenPartInd_fromHTagL,"hGenPartInd_fromHTagL/F");
    FATree->Branch("hGenPartpdgId_fromHTagL",&hGenPartpdgId_fromHTagL,"hGenPartpdgId_fromHTagL/F");
    FATree->Branch("hGenPartFirstMompdgId_fromHTagL",&hGenPartFirstMompdgId_fromHTagL,"hGenPartFirstMompdgId_fromHTagL/I");

    //Now HLT stuff;

    FATree->Branch("hbbTagL",&hbbTagL,"hbbTagL/O");

    FATree->Branch("doubleElecHLTL",&doubleElecHLTL,"doubleElecHLTL/O");
    FATree->Branch("doubleMuonHLTL",&doubleMuonHLTL,"doubleMuonHLTL/O");
    FATree->Branch("muonEGHLTL",&muonEGHLTL,"muonEGHLTL/O");
    FATree->Branch("elecHLTL",&elecHLTL,"elecHLTL/O");
    FATree->Branch("muonHLTL",&muonHLTL,"muonHLTL/O");
    FATree->Branch("hadHLTL",&hadHLTL,"hadHLTL/O");
    FATree->Branch("isLeptonicL",&isLeptonicL,"isLeptonicL/O");
    FATree->Branch("isSemiLeptonicL",&isSemiLeptonicL,"isSemiLeptonicL/O");
    FATree->Branch("isHadronicL",&isHadronicL,"isHadronicL/O");

    //Branches for distinguishing between channels;
    FATree->Branch("passedLepL",&passedLepL,"passedLepL/O");
    FATree->Branch("passedSemiLepL",&passedSemiLepL,"passedSemiLepL/O");
    FATree->Branch("passedHadL",&passedHadL,"passedHadL/O");




    //Now trees for specific channels;

    //Leptonic variables;
    float lepZ1LeadPtL;
    float lepZ1TrailingPtL;
    float lepZ1LeadPhiL;
    float lepZ1TrailingPhiL;
    float lepZ1PairInvMassL;
    float lepZ1LeadEtaL;
    float lepZ1TrailingEtaL;
    bool lepZ1IsElectronL;
    bool lepZ1IsMuonL;
    float lepZ1LeadIsoL;
    float lepZ1TrailingIsoL;
    float lepZ1LeadSIPL;
    float lepZ1TrailingSIPL;

    float lepZ2LeadPtL;
    float lepZ2TrailingPtL;
    float lepZ2LeadPhiL;
    float lepZ2TrailingPhiL;
    float lepZ2PairInvMassL;
    float lepZ2LeadEtaL;
    float lepZ2TrailingEtaL;
    bool lepZ2IsElectronL;
    bool lepZ2IsMuonL;
    float lepZ2LeadIsoL;
    float lepZ2TrailingIsoL;
    float lepZ2LeadSIPL;
    float lepZ2TrailingSIPL;

    float lepChanHiggsFatJet_pt_fromHTagL;
    float lepChanHiggsFatJet_phi_fromHTagL;
    float lepChanHiggsFatJet_eta_fromHTagL;
    float lepChanHiggsFatJet_mass_fromHTagL;
    float lepChanHiggsFatJet_HTag_fromHTagL;

    //Leptonic tree;
    TTree *LepTree = new TTree("LepTree", "LepTree");

    LepTree->Branch("lepZ1LeadPtL",&lepZ1LeadPtL,"lepZ1LeadPtL/F");
    LepTree->Branch("lepZ1TrailingPtL",&lepZ1TrailingPtL,"lepZ1TrailingPtL/F");
    LepTree->Branch("lepZ1LeadPhiL",&lepZ1LeadPhiL,"lepZ1LeadPhiL/F");
    LepTree->Branch("lepZ1TrailingPhiL",&lepZ1TrailingPhiL,"lepZ1TrailingPhiL/F");
    LepTree->Branch("lepZ1PairInvMassL",&lepZ1PairInvMassL,"lepZ1PairInvMassL/F");
    LepTree->Branch("lepZ1LeadEtaL",&lepZ1LeadEtaL,"lepZ1LeadEtaL/F");
    LepTree->Branch("lepZ1TrailingEtaL",&lepZ1TrailingEtaL,"lepZ1TrailingEtaL/F");
    LepTree->Branch("lepZ1IsElectronL",&lepZ1IsElectronL,"lepZ1IsElectronL/O");
    LepTree->Branch("lepZ1IsMuonL",&lepZ1IsMuonL,"lepZ1IsMuonL/O");
    LepTree->Branch("lepZ1LeadIsoL",&lepZ1LeadIsoL,"lepZ1LeadIsoL/F");
    LepTree->Branch("lepZ1TrailingIsoL",&lepZ1TrailingIsoL,"lepZ1TrailingIsoL/F");
    LepTree->Branch("lepZ1LeadSIPL",&lepZ1LeadSIPL,"lepZ1LeadSIPL/F");
    LepTree->Branch("lepZ1TrailingSIPL",&lepZ1TrailingSIPL,"lepZ1TrailingSIPL/F");

    LepTree->Branch("lepZ2LeadPtL",&lepZ2LeadPtL,"lepZ2LeadPtL/F");
    LepTree->Branch("lepZ2TrailingPtL",&lepZ2TrailingPtL,"lepZ2TrailingPtL/F");
    LepTree->Branch("lepZ2LeadPhiL",&lepZ2LeadPhiL,"lepZ2LeadPhiL/F");
    LepTree->Branch("lepZ2TrailingPhiL",&lepZ2TrailingPhiL,"lepZ2TrailingPhiL/F");
    LepTree->Branch("lepZ2PairInvMassL",&lepZ2PairInvMassL,"lepZ2PairInvMassL/F");
    LepTree->Branch("lepZ2LeadEtaL",&lepZ2LeadEtaL,"lepZ2LeadEtaL/F");
    LepTree->Branch("lepZ2TrailingEtaL",&lepZ2TrailingEtaL,"lepZ2TrailingEtaL/F");
    LepTree->Branch("lepZ2IsElectronL",&lepZ2IsElectronL,"lepZ2IsElectronL/O");
    LepTree->Branch("lepZ2IsMuonL",&lepZ2IsMuonL,"lepZ2IsMuonL/O");
    LepTree->Branch("lepZ2LeadIsoL",&lepZ2LeadIsoL,"lepZ2LeadIsoL/F");
    LepTree->Branch("lepZ2TrailingIsoL",&lepZ2TrailingIsoL,"lepZ2TrailingIsoL/F");
    LepTree->Branch("lepZ2LeadSIPL",&lepZ2LeadSIPL,"lepZ2LeadSIPL/F");
    LepTree->Branch("lepZ2TrailingSIPL",&lepZ2TrailingSIPL,"lepZ2TrailingSIPL/F");

    LepTree->Branch("lepChanHiggsFatJet_pt_fromHTagL",&lepChanHiggsFatJet_pt_fromHTagL,"lepChanHiggsFatJet_pt_fromHTagL/F");
    LepTree->Branch("lepChanHiggsFatJet_phi_fromHTagL",&lepChanHiggsFatJet_phi_fromHTagL,"lepChanHiggsFatJet_phi_fromHTagL/F");
    LepTree->Branch("lepChanHiggsFatJet_eta_fromHTagL",&lepChanHiggsFatJet_eta_fromHTagL,"lepChanHiggsFatJet_eta_fromHTagL/F");
    LepTree->Branch("lepChanHiggsFatJet_mass_fromHTagL",&lepChanHiggsFatJet_mass_fromHTagL,"lepChanHiggsFatJet_mass_fromHTagL/F");
    LepTree->Branch("lepChanHiggsFatJet_HTag_fromHTagL",&lepChanHiggsFatJet_HTag_fromHTagL,"lepChanHiggsFatJet_HTag_fromHTagL/F");


    //SemiLeptonic variables;
    float lepLeadPtL;
    float lepTrailingPtL;
    float lepLeadPhiL;
    float lepTrailingPhiL;
    float lepPairInvMassL;
    float lepLeadEtaL;
    float lepTrailingEtaL;
    float lepLeadIsoL;
    float lepTrailingIsoL;
    float lepLeadSIPL;
    float lepTrailingSIPL;
    bool lepIsElectronL;
    bool lepIsMuonL;


    float FJPtL;
    float FJPhiL;
    float FJMassL;
    float FJEtaL;


    float semiLepChanHiggsFatJet_pt_fromHTagL;
    float semiLepChanHiggsFatJet_phi_fromHTagL;
    float semiLepChanHiggsFatJet_eta_fromHTagL;
    float semiLepChanHiggsFatJet_mass_fromHTagL;
    float semiLepChanHiggsFatJet_HTag_fromHTagL;

    //SemiLeptonic tree;
    TTree *SemiLepTree = new TTree("SemiLepTree", "SemiLepTree");

    SemiLepTree->Branch("lepLeadPtL",&lepLeadPtL,"lepLeadPtL/F");
    SemiLepTree->Branch("lepTrailingPtL",&lepTrailingPtL,"lepTrailingPtL/F");
    SemiLepTree->Branch("lepLeadPhiL",&lepLeadPhiL,"lepLeadPhiL/F");
    SemiLepTree->Branch("lepTrailingPhiL",&lepTrailingPhiL,"lepTrailingPhiL/F");
    SemiLepTree->Branch("lepPairInvMassL",&lepPairInvMassL,"lepPairInvMassL/F");
    SemiLepTree->Branch("lepLeadEtaL",&lepLeadEtaL,"lepLeadEtaL/F");
    SemiLepTree->Branch("lepTrailingEtaL",&lepTrailingEtaL,"lepTrailingEtaL/F");
    SemiLepTree->Branch("lepIsElectronL",&lepIsElectronL,"lepIsElectronL/O");
    SemiLepTree->Branch("lepIsMuonL",&lepIsMuonL,"lepIsMuonL/O");
    SemiLepTree->Branch("lepLeadIsoL",&lepLeadIsoL,"lepLeadIsoL/F");
    SemiLepTree->Branch("lepTrailingIsoL",&lepTrailingIsoL,"lepTrailingIsoL/F");
    SemiLepTree->Branch("lepLeadSIPL",&lepLeadSIPL,"lepLeadSIPL/F");
    SemiLepTree->Branch("lepTrailingSIPL",&lepTrailingSIPL,"lepTrailingSIPL/F");
    

    SemiLepTree->Branch("FJPtL",&FJPtL,"FJPtL/F");
    SemiLepTree->Branch("FJPhiL",&FJPhiL,"FJPhiL/F");
    SemiLepTree->Branch("FJMassL",&FJMassL,"FJMassL/F");
    SemiLepTree->Branch("FJEtaL",&FJEtaL,"FJEtaL/F");


    SemiLepTree->Branch("semiLepChanHiggsFatJet_pt_fromHTagL",&semiLepChanHiggsFatJet_pt_fromHTagL,"semiLepChanHiggsFatJet_pt_fromHTagL/F");
    SemiLepTree->Branch("semiLepChanHiggsFatJet_phi_fromHTagL",&semiLepChanHiggsFatJet_phi_fromHTagL,"semiLepChanHiggsFatJet_phi_fromHTagL/F");
    SemiLepTree->Branch("semiLepChanHiggsFatJet_eta_fromHTagL",&semiLepChanHiggsFatJet_eta_fromHTagL,"semiLepChanHiggsFatJet_eta_fromHTagL/F");
    SemiLepTree->Branch("semiLepChanHiggsFatJet_mass_fromHTagL",&semiLepChanHiggsFatJet_mass_fromHTagL,"semiLepChanHiggsFatJet_mass_fromHTagL/F");
    SemiLepTree->Branch("semiLepChanHiggsFatJet_HTag_fromHTagL",&semiLepChanHiggsFatJet_HTag_fromHTagL,"semiLepChanHiggsFatJet_HTag_fromHTagL/F");


    //Hadronic variables;
    float FJLeadPtL;
    float FJTrailingPtL;
    float FJLeadPhiL;
    float FJTrailingPhiL;
    float FJLeadMassL;
    float FJTrailingMassL;
    float FJPairInvMassL;
    float FJLeadEtaL;
    float FJTrailingEtaL;
    float FJEtaSepL;

    float hadChanHiggsFatJet_pt_fromHTagL;
    float hadChanHiggsFatJet_phi_fromHTagL;
    float hadChanHiggsFatJet_eta_fromHTagL;
    float hadChanHiggsFatJet_mass_fromHTagL;
    float hadChanHiggsFatJet_HTag_fromHTagL;

    //Hadronic tree;
    TTree *HadTree = new TTree("HadTree", "HadTree");

    HadTree->Branch("FJLeadPtL",&FJLeadPtL,"FJLeadPtL/F");
    HadTree->Branch("FJTrailingPtL",&FJTrailingPtL,"FJTrailingPtL/F");
    HadTree->Branch("FJLeadPhiL",&FJLeadPhiL,"FJLeadPhiL/F");
    HadTree->Branch("FJTrailingPhiL",&FJTrailingPhiL,"FJTrailingPhiL/F");
    HadTree->Branch("FJLeadMassL",&FJLeadMassL,"FJLeadMassL/F");
    HadTree->Branch("FJTrailingMassL",&FJTrailingMassL,"FJTrailingMassL/F");
    HadTree->Branch("FJPairInvMassL",&FJPairInvMassL,"FJPairInvMassL/F");
    HadTree->Branch("FJLeadEtaL",&FJLeadEtaL,"FJLeadEtaL/F");
    HadTree->Branch("FJTrailingEtaL",&FJTrailingEtaL,"FJTrailingEtaL/F");
    HadTree->Branch("FJEtaSepL",&FJEtaSepL,"FJEtaSepL/F");


    HadTree->Branch("hadChanHiggsFatJet_pt_fromHTagL",&hadChanHiggsFatJet_pt_fromHTagL,"hadChanHiggsFatJet_pt_fromHTagL/F");
    HadTree->Branch("hadChanHiggsFatJet_phi_fromHTagL",&hadChanHiggsFatJet_phi_fromHTagL,"hadChanHiggsFatJet_phi_fromHTagL/F");
    HadTree->Branch("hadChanHiggsFatJet_eta_fromHTagL",&hadChanHiggsFatJet_eta_fromHTagL,"hadChanHiggsFatJet_eta_fromHTagL/F");
    HadTree->Branch("hadChanHiggsFatJet_mass_fromHTagL",&hadChanHiggsFatJet_mass_fromHTagL,"hadChanHiggsFatJet_mass_fromHTagL/F");
    HadTree->Branch("hadChanHiggsFatJet_HTag_fromHTagL",&hadChanHiggsFatJet_HTag_fromHTagL,"hadChanHiggsFatJet_HTag_fromHTagL/F");


    
    std::cout << "Going into file loop.\n";

    for (UInt_t k=0; k<fileAr.size(); k++){
        if (endAfter && evCount > NToEnd) break;
        if (debug) std::cout<<"File:    "<<fileAr[k]<<"\n";
        //Open the file, get the Events tree
        TFile* tmpfile = TFile::Open(fileAr[k].c_str());
        outFile->cd();
        TTreeReader myEventsReader("Events", tmpfile);
        TTreeReaderValue<UInt_t> nLHEPart(myEventsReader, "nLHEPart");
        TTreeReaderArray<Float_t> LHEPart_pt(myEventsReader, "LHEPart_pt");
        TTreeReaderArray<Float_t> LHEPart_eta(myEventsReader, "LHEPart_eta");
        TTreeReaderArray<Int_t> LHEPart_pdgId(myEventsReader, "LHEPart_pdgId");
        TTreeReaderArray<Float_t> LHEPart_mass(myEventsReader, "LHEPart_mass");
        TTreeReaderArray<Float_t> LHEPart_phi(myEventsReader, "LHEPart_phi");
          

        TTreeReaderValue<Bool_t> HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02(myEventsReader, "HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02");
        TTreeReaderValue<Bool_t> HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2(myEventsReader, "HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2");
        TTreeReaderValue<Bool_t> HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4(myEventsReader, "HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4");
        TTreeReaderValue<Bool_t> HLT_TripleMu_10_5_5_DZ(myEventsReader, "HLT_TripleMu_10_5_5_DZ");
        TTreeReaderValue<Bool_t> HLT_TripleMu_12_10_5(myEventsReader, "HLT_TripleMu_12_10_5");

        //HLT Branches
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

        //Muons
        TTreeReaderValue<UInt_t> nMuon(myEventsReader, "nMuon");
        TTreeReaderArray<Float_t> Muon_eta(myEventsReader, "Muon_eta");
        TTreeReaderArray<Float_t> Muon_mass(myEventsReader, "Muon_mass");
        TTreeReaderArray<Int_t> Muon_charge(myEventsReader, "Muon_charge");
        TTreeReaderArray<Float_t> Muon_phi(myEventsReader, "Muon_phi");
        TTreeReaderArray<Float_t> Muon_pt(myEventsReader, "Muon_pt");
        TTreeReaderArray<Float_t> Muon_pfRelIso03_all(myEventsReader, "Muon_pfRelIso03_all");
        TTreeReaderArray<Float_t> Muon_sip3d(myEventsReader, "Muon_sip3d");



        TTreeReader myRunsReader("Runs", tmpfile);
        TTreeReaderValue<Long64_t> genEventCount(myRunsReader, "genEventCount");
        TTreeReaderValue<Double_t> genEventSumw(myRunsReader, "genEventSumw");

        Int_t tmpPDGId;

        float ZOne_pt_FromLHERaw;
        float ZOne_eta_FromLHERaw;
        float ZOne_phi_FromLHERaw;
        float ZOne_mass_FromLHERaw;
        

        float ZTwo_pt_FromLHERaw;
        float ZTwo_eta_FromLHERaw;
        float ZTwo_phi_FromLHERaw;
        float ZTwo_mass_FromLHERaw;

        float ZPair_InvMass_FromLHERaw;
        float ZPair_EtaSep_FromLHERaw;

        float H_pt_FromLHERaw;
        float H_eta_FromLHERaw;
        float H_phi_FromLHERaw;
        float H_mass_FromLHERaw;

        float ZPairPlusH_InvMass_FromLHERaw;

        float JOne_pt_FromLHERaw;
        float JOne_eta_FromLHERaw;
        float JOne_pdgId_FromLHERaw;

        float JTwo_pt_FromLHERaw;
        float JTwo_eta_FromLHERaw;
        float JTwo_pdgId_FromLHERaw;

        float JOne_invmass_FromLHERaw;
        float JTwo_invmass_FromLHERaw;

        float JOne_phi_FromLHERaw;
        float JTwo_phi_FromLHERaw;

        float JPair_invmass_FromLHERaw;
        float J_etasep_FromLHERaw;

        float tmpIso;

        Int_t tmpZ2Ind = -1;
        bool Z2IsMuon = false;
        float tmpTopZ2LeadPt = 0;
        float tmpTopZ2TrailingPt = 0;
        ROOT::Math::PtEtaPhiMVector tmpZ1Vec;
        float tmpZ1M;

        float Z1LeadIso;
        float Z1TrailingIso;
        float Z2LeadIso;
        float Z2TrailingIso;
        float Z1LeadSIP;
        float Z1TrailingSIP;
        float Z2LeadSIP;
        float Z2TrailingSIP;

        std::vector<UInt_t> muonCandIndAr;
        std::vector<UInt_t> elecCandIndAr;

        float tmpAdd;

        Int_t LFJOneInd = -1;
        Int_t LFJTwoInd = -1;
        float leadFatJetMaxPT = -1;
        float secondFatJetMaxPT = -1;
        float FJInvMass = -1;

        std::vector<std::array<ROOT::Math::PtEtaPhiMVector,2>> eZ2VecPairAr;
        std::vector<std::array<ROOT::Math::PtEtaPhiMVector,2>> mZ2VecPairAr;

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
            if (evCount % 1000 == 0) std::cout << "Event: " << evCount << "\n";
            if (debug){
                std::cout << "-------------------------\n";
                std::cout << evCount+1 << " starting jets loop\n";
            }
            //Increment event count
            evRunOver += 1;
            evCount += 1;

            //tmpZ1Vec.clear();
            
            elecCandIndAr.clear();
            muonCandIndAr.clear();

            eZ2VecPairAr.clear();
            mZ2VecPairAr.clear();

            //HFJ_decaypdgId_FromGenMatchL.clear();


            bool passesCutsBool = false;
            bool passedAsLepBool = false;
            bool passedAsSemiLepBool = false;
            bool passedAsHadBool = false;
            


            
            //First check that it passes the hbb tagging
            bool hbbTag = *HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02 || *HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2 || *HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4;

            //Hadronic
            bool hadHLT =  (*HLT_PFHT1050 || *HLT_AK8PFJet500 || *HLT_AK8PFJet360_TrimMass30 || *HLT_AK8PFHT750_TrimMass50 || *HLT_AK8PFJet380_TrimMass30 ||
            *HLT_AK8PFJet400_TrimMass30 || *HLT_AK8PFJet420_TrimMass30 ||
            *HLT_AK8PFHT800_TrimMass50 || *HLT_AK8PFHT850_TrimMass50 || *HLT_AK8PFHT900_TrimMass50);
            /*

            
            if (!hbbTag) continue;
            passhbbCtr += 1;
            */

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

            bool passHLTBool = hbbTag || hadHLT || doubleElecHLT || doubleMuonHLT || muonEGHLT || elecHLT || muonHLT;

            if (!passHLTBool) continue;
            passHLTCtr += 1;
            
            

            bool isLeptonic = doubleElecHLT || doubleMuonHLT || muonEGHLT;
            bool isSemiLeptonic = (elecHLT || muonHLT) && hadHLT;
            bool isHadronic = hadHLT;

            /*

            if (!(isLeptonic || isSemiLeptonic || isHadronic)) continue;
            */
            
            if (isLeptonic || isSemiLeptonic || isHadronic) passAnyChannelCtr += 1;
            if (isLeptonic){
                
                if (isSemiLeptonic){
                    if (isHadronic) passAllChannelCtr += 1;
                    else passLepAndSemiLepChannelCtr += 1;
                }
                else if (isHadronic) passLepAndHadChannelCtr += 1;
                else passLepChannelCtr += 1;
            }
            else if (isSemiLeptonic){
                if (isHadronic) passSemiLepAndHadChannelCtr += 1;
                else passSemiLepChannelCtr += 1;
            }
            else if (isHadronic) passHadChannelCtr += 1;
            

            //Now fat jets
            UInt_t nFatJetLen = *nFatJet;
            /*
            float hFatJet_HTag_fromPt = 0.;
            float hFatJet_pt_fromPt = 0.;
            float hFatJet_phi_fromPt = 0.;
            float hFatJet_eta_fromPt = 0.;
            float hFatJet_mass_fromPt = 0.;
            */
            float hFatJet_pt_fromHTag = 0.;
            float hFatJet_phi_fromHTag = 0.;
            float hFatJet_eta_fromHTag = 0.;
            float hFatJet_mass_fromHTag = 0.;
            float hFatJet_HTag_fromHTag = 0.;
            UInt_t hFatJet_ind_fromHTag = 0;
            if (debug){
                std::cout << "Entering Fat Jets Loop\n";
            }

            vector<float> selectedFJ_phi;
            vector<float> selectedFJ_eta;

            //doHiggsFatJetCut(nFatJetLen,hFatJet_HTag_fromPt,hFatJet_pt_fromPt,hFatJet_phi_fromPt,hFatJet_eta_fromPt,hFatJet_mass_fromPt,hFatJet_pt_fromHTag,hFatJet_phi_fromHTag,hFatJet_eta_fromHTag,hFatJet_mass_fromHTag,hFatJet_HTag_fromHTag,hFatJet_ind_fromHTag,FatJet_deepTag_H,hFatJetDeepTagCut,FatJet_pt,hFatJetPTCut,FatJet_jetId,FatJet_phi,FatJet_eta,jetLeadPhi,jetLeadEta,jetTrailingPhi,jetTrailingEta,hFatJetdRCut,FatJet_mass);
            doHiggsFatJetCut(nFatJetLen,hFatJet_pt_fromHTag,hFatJet_phi_fromHTag,hFatJet_eta_fromHTag,hFatJet_mass_fromHTag,hFatJet_HTag_fromHTag,hFatJet_ind_fromHTag,FatJet_deepTag_H,hFatJetDeepTagCut,FatJet_pt,hFatJetPTCut,FatJet_jetId,FatJet_phi,FatJet_eta,FatJet_mass,selectedFJ_phi,selectedFJ_eta);
            
            if (hFatJet_pt_fromHTag == 0) continue;
            if (debug) std::cout << " found fat jet\n";
            passFatJets += 1;



            


            


            //Now gen matching
            UInt_t nGenPartLen = *nGenPart;
            /*
            float hGenPartDR_fromPt = 999.;
            Int_t hGenPartInd_fromPt = -1;
            Int_t hGenPartpdgId_fromPt = -1;
            */
            float hGenPartDR_fromHTag = 999.;
            Int_t hGenPartInd_fromHTag = -1;
            Int_t hGenPartpdgId_fromHTag = -1;
            for (UInt_t genPartInd=0; genPartInd < nGenPartLen; genPartInd++){
                float tmpGenPart_phi = GenPart_phi[genPartInd];
                float tmpGenPart_eta = GenPart_eta[genPartInd];
                /*
                float tmpDR_fromPt = calcDeltaR(hFatJet_phi_fromPt,hFatJet_eta_fromPt,tmpGenPart_phi,tmpGenPart_eta);
                if (tmpDR_fromPt < hGenPartDR_fromPt){
                    hGenPartDR_fromPt = tmpDR_fromPt;
                    hGenPartInd_fromPt = genPartInd;
                    hGenPartpdgId_fromPt = GenPart_pdgId[genPartInd];
                }
                */
                float tmpDR_fromHTag = calcDeltaR(hFatJet_phi_fromHTag,hFatJet_eta_fromHTag,tmpGenPart_phi,tmpGenPart_eta);
                if (tmpDR_fromHTag < hGenPartDR_fromHTag){
                    hGenPartDR_fromHTag = tmpDR_fromHTag;
                    hGenPartInd_fromHTag = genPartInd;
                    hGenPartpdgId_fromHTag = GenPart_pdgId[genPartInd];
                }
            }
            //if (!(hGenPartInd_fromPt == -1) && !(hGenPartInd_fromHTag == -1)){
            if (!(hGenPartInd_fromHTag == -1)){
                if (debug) std::cout << " found gen part\n";
                passGenPart += 1;
                
                //Get genPart first mom
                if (debug) std::cout << "GenPart_genPartIdxMother[hGenPartInd_fromPt] " << GenPart_genPartIdxMother[hGenPartInd_fromPt] << "\n";
                //Int_t hGenPartFirstMompdgId_fromPt = getInitialMother(GenPart_genPartIdxMother,GenPart_pdgId,hGenPartInd_fromPt,debug);
                Int_t hGenPartFirstMompdgId_fromHTag = getInitialMother(GenPart_genPartIdxMother,GenPart_pdgId,hGenPartInd_fromHTag,debug);
                //if (debug) std::cout << "hGenPartFirstMompdgId_fromPt: " << hGenPartFirstMompdgId_fromPt << " hGenPartFirstMompdgId_fromHTag: " << hGenPartFirstMompdgId_fromHTag << "\n";
                if (debug) std::cout << "hGenPartFirstMompdgId_fromHTag: " << hGenPartFirstMompdgId_fromHTag << "\n";
            }
            if (true) {
                UInt_t neLep = *nElectron;
                UInt_t nmLep = *nMuon;
                bool enoughElecCands = false;
                UInt_t negElecCands = 0;
                UInt_t posElecCands = 0;
                UInt_t totElecCands = 0;
                
                std::vector<ROOT::Math::PtEtaPhiMVector> elecCandVecAr;
                std::vector<Int_t> elecCandChargeAr;


                bool enoughMuonCands = false;
                UInt_t negMuonCands = 0;
                UInt_t posMuonCands = 0;
                UInt_t totMuonCands = 0;
                
                std::vector<ROOT::Math::PtEtaPhiMVector> muonCandVecAr;
                std::vector<Int_t> muonCandChargeAr;
                bool enoughLepCands;
                bool Z1Cand = false;

                float difFromZMassOne = 1000.;
                Int_t Z1LeadItr = -1;
                Int_t Z1TrailingItr = -1;
                float Z1LeadPt = 0.;
                float Z1TrailingPt = 0.;
                bool Z1IsMuon = false;
                ROOT::Math::PtEtaPhiMVector Z1LeadVec;
                ROOT::Math::PtEtaPhiMVector Z1TrailingVec;
                Int_t Z1LeadCharge = 0;
                Int_t Z1TrailingCharge = 0;

                if (true){
                    if (debug) cout << "trying Leptonic\n";
                    tryingLepCtr += 1;
                    
                    
                    
                    if (neLep){
                        if (debug) std::cout << "Doing elec cand cut\n";
                        dolCandCut(Electron_eta,Electron_mass,Electron_charge,Electron_phi,Electron_pt,neLep,elecCandIndAr,elecCandVecAr,elecCandChargeAr,ePtCut,eEtaCut,debug);
                        //doeCandCut(Electron_eta,Electron_mass,Electron_charge,Electron_phi,Electron_pt,neLep,elecCandIndAr,elecCandVecAr,elecCandChargeAr,ePtCut,eEtaCut);
                        for (UInt_t elecCandChargeInd=0;elecCandChargeInd<elecCandChargeAr.size();elecCandChargeInd++){
                            if (elecCandChargeAr[elecCandChargeInd] == -1) negElecCands += 1;
                            else posElecCands += 1;
                        }
                        totElecCands = std::min(negElecCands,posElecCands);
                        if (totElecCands >= 1) enoughElecCands = true;
                    }


                    
                    
                    if (debug){
                        std::cout << "--------------------------------------------\n";
                        std::cout << "neLep " << neLep << "\n";
                        for (UInt_t tmpItr=0; tmpItr < neLep; tmpItr++){
                            std::cout <<"tmpItr " << tmpItr << " Electron_pt[tmpItr] " << Electron_pt[tmpItr] << " Electron_eta[tmpItr] " << Electron_eta[tmpItr] << " Electron_charge[tmpItr] " << Electron_charge[tmpItr] << "\n";
                        }
                    }
                    if (nmLep){
                        if (debug) std::cout << "Doing muon cand cut\n";

                        dolCandCut(Muon_eta,Muon_mass,Muon_charge,Muon_phi,Muon_pt,nmLep,muonCandIndAr,muonCandVecAr,muonCandChargeAr,mPtCut,mEtaCut,debug);

                        //domCandCut(Muon_eta,Muon_mass,Muon_charge,Muon_phi,Muon_pt,neLep,muonCandIndAr,muonCandVecAr,muonCandChargeAr,mPtCut,mEtaCut);
                        for (UInt_t muonCandChargeInd=0;muonCandChargeInd<muonCandChargeAr.size();muonCandChargeInd++){
                            if (muonCandChargeAr[muonCandChargeInd] == -1) negMuonCands += 1;
                            else posMuonCands += 1;
                        }
                        totMuonCands = std::min(negMuonCands,posMuonCands);
                        if (totMuonCands >= 1) enoughMuonCands = true;
                    }

                    enoughLepCands = false;
                    if (totElecCands+totMuonCands >= 2) enoughLepCands = true;
                    if (debug){
                        std::cout << "negElecCands " << negElecCands << " posElecCands " << posElecCands << " totElecCands " << totElecCands << "\n";
                        std::cout << "nmLep " << nmLep << " negMuonCands " << negMuonCands << " posMuonCands " << posMuonCands << " totMuonCands " << totMuonCands << "\n";
                        std::cout << "enoughLepCands " << enoughLepCands << "\n";
                    }
                    
                    

                    

                    if (enoughLepCands){ //Check there are enough lep cands after candidate cuts
                        //passesCandCutsCtr += 1
                        std::vector<std::array<UInt_t,2>> elecPassesZ2CutsAr;
                        if (enoughElecCands){ //If enough elec cands, run Z1 cuts
                            dolZ1Cut(Electron_pt,elecCandIndAr,elecCandVecAr,elecCandChargeAr,elecPassesZ2CutsAr,Z1IsMuon,false,invMassCutLow,invMassCutHigh,ptLeadCut,ptTrailingCut,Z1LeadPt,Z1TrailingPt,Z1LeadItr,Z1TrailingItr,Z1LeadVec,Z1TrailingVec,Z1LeadCharge,Z1TrailingCharge,difFromZMassOne,debug);
                        }
                        std::vector<std::array<UInt_t,2>> muonPassesZ2CutsAr;
                        if (enoughMuonCands){ //If enough muon cands, run Z1 cuts
                            dolZ1Cut(Muon_pt,muonCandIndAr,muonCandVecAr,muonCandChargeAr,muonPassesZ2CutsAr,Z1IsMuon,true,invMassCutLow,invMassCutHigh,ptLeadCut,ptTrailingCut,Z1LeadPt,Z1TrailingPt,Z1LeadItr,Z1TrailingItr,Z1LeadVec,Z1TrailingVec,Z1LeadCharge,Z1TrailingCharge,difFromZMassOne,debug);
                        }
                        if (debug) std::cout <<"Z1LeadItr " << Z1LeadItr << " Z1TrailingItr " << Z1TrailingItr << " Z1LeadPt " << Z1LeadPt << " Z1TrailingPt " << Z1TrailingPt << " Z1LeadVec " << Z1LeadVec << " Z1TrailingVec " << Z1TrailingVec << " Z1LeadCharge " << Z1LeadCharge << " Z1TrailingCharge " << Z1TrailingCharge << " Z1IsMuon " << Z1IsMuon << " difFromZMassOne " << difFromZMassOne << "\n";
                        if (Z1LeadItr >= 0) { //If Z1 found
                            //passesZ1CutsCtr += 1
                            if (debug) std::cout <<"passed Z1 cut. checking for enough Z2 now\n";

                            std::vector<std::array<UInt_t,2>> elecPassesZ2CutsFinalAr;
                                
                            
                            std::vector<std::array<double,2>> eZ2PtPairAr;
                            std::vector<std::array<Int_t,2>> eZ2ChargePairAr;
                            bool tmpIgnore;
                            if (!Z1IsMuon) tmpIgnore = true;
                            else tmpIgnore = false;
                            std::array<Int_t,2> indsToIgnore = {Z1LeadItr,Z1TrailingItr};
                            bool eZ2CandsBool = false;
                            bool mZ2CandsBool = false;
                                

                            fillZ2Ars(elecPassesZ2CutsFinalAr,eZ2VecPairAr,eZ2PtPairAr,eZ2ChargePairAr,elecPassesZ2CutsAr,elecCandChargeAr,elecCandVecAr,tmpIgnore,indsToIgnore,eZ2CandsBool);

                            std::vector<std::array<UInt_t,2>> muonPassesZ2CutsFinalAr;
                                
                            
                            std::vector<std::array<double,2>> mZ2PtPairAr;
                            std::vector<std::array<Int_t,2>> mZ2ChargePairAr;
                            fillZ2Ars(muonPassesZ2CutsFinalAr,mZ2VecPairAr,mZ2PtPairAr,mZ2ChargePairAr,muonPassesZ2CutsAr,muonCandChargeAr,muonCandVecAr,!tmpIgnore,indsToIgnore,mZ2CandsBool);


                            if (debug){
                                std::vector<float> tmpPtAr;
                                std::vector<ROOT::Math::PtEtaPhiMVector> tmpVecAr;
                                //for elecCandInd in elecCandIndAr:
                                std::cout << "elecCandIndAr loop\n";
                                for (UInt_t elecCandIndInd=0; elecCandIndInd<elecCandIndAr.size();elecCandIndInd++){
                                    cout << "elecCandIndInd " << elecCandIndInd << "elecCandIndAr[elecCandIndInd]" << elecCandIndAr[elecCandIndInd] << "\n";

                                }
                                std::cout << "elecCandChargeAr loop\n";
                                for (UInt_t elecCandChargeInd=0; elecCandChargeInd<elecCandChargeAr.size();elecCandChargeInd++){
                                    cout << "elecCandChargeInd " << elecCandChargeInd << "elecCandChargeAr[elecCandChargeInd]" << elecCandChargeAr[elecCandChargeInd] << "\n";
                                }
                                std::cout << "elecCandVecAr loop\n";
                                if (elecCandVecAr.size()){
                                    for (UInt_t elecCandVecItrOne=0; elecCandVecItrOne<elecCandVecAr.size()-1; elecCandVecItrOne++){
                                        std::cout << "elecCandVecItrOne " << elecCandVecItrOne << " elecCandVecOne " << elecCandVecAr[elecCandVecItrOne] << "\n";
                                        for (UInt_t elecCandVecItrTwo=elecCandVecItrOne+1; elecCandVecItrTwo<elecCandVecAr.size(); elecCandVecItrTwo++){
                                            std::cout << "elecCandVecItrTwo " << elecCandVecItrTwo << " elecCandVecTwo " << elecCandVecAr[elecCandVecItrTwo] << "\n";
                                            ROOT::Math::PtEtaPhiMVector tmpVecSum = elecCandVecAr[elecCandVecItrOne]+elecCandVecAr[elecCandVecItrTwo];
                                            std::cout << tmpVecSum << "\n";
                                            std::cout << tmpVecSum.M() << "\n";
                                        }
                                    }
                                }
                                
                                std::cout << "elecPassesZ2CutsAr loop\n";
                                for (UInt_t elecPassesZ2CutsInd=0; elecPassesZ2CutsInd<elecPassesZ2CutsAr.size(); elecPassesZ2CutsInd++){
                                    std::cout << "elecPassesZ2CutsInd " << elecPassesZ2CutsInd << "elecPassesZ2CutsAr[elecPassesZ2CutsInd][0] " << elecPassesZ2CutsAr[elecPassesZ2CutsInd][0] << "\n";
                                    std::cout << "elecPassesZ2CutsInd " << elecPassesZ2CutsInd << "elecPassesZ2CutsAr[elecPassesZ2CutsInd][1] " << elecPassesZ2CutsAr[elecPassesZ2CutsInd][1] << "\n";

                                }

                                std::cout << "elecPassesZ2CutsFinalAr loop\n";
                                for (UInt_t elecPassesZ2CutsFinalInd=0; elecPassesZ2CutsFinalInd<elecPassesZ2CutsFinalAr.size();elecPassesZ2CutsFinalInd++){
                                    std::cout << "elecPassesZ2CutsFinalInd " << elecPassesZ2CutsFinalInd << "elecPassesZ2CutsFinalAr[elecPassesZ2CutsFinalInd][0]" << elecPassesZ2CutsFinalAr[elecPassesZ2CutsFinalInd][0] << "\n";

                                }


                                std::cout << "muonCandIndAr loop\n";
                                for (UInt_t muonCandIndInd=0; muonCandIndInd<muonCandIndAr.size();muonCandIndInd++){
                                    std::cout << "muonCandIndInd " << muonCandIndInd << "muonCandIndAr[muonCandIndInd]" << muonCandIndAr[muonCandIndInd] << "\n";

                                }
                                std::cout << "muonCandChargeAr loop\n";
                                for (UInt_t muonCandChargeInd=0; muonCandChargeInd<muonCandChargeAr.size();muonCandChargeInd++){
                                    std::cout << "muonCandChargeInd " << muonCandChargeInd << "muonCandChargeAr[muonCandChargeInd]" << muonCandChargeAr[muonCandChargeInd] << "\n";
                                }
                                std::cout <<"muonCandVecAr loop\n";
                                if (muonCandVecAr.size()) {
                                    for (UInt_t muonCandVecItrOne=0; muonCandVecItrOne<muonCandVecAr.size()-1; muonCandVecItrOne++){
                                        std::cout <<"muonCandVecItrOne " << muonCandVecItrOne << " muonCandVecOne " << muonCandVecAr[muonCandVecItrOne] << "\n";
                                        for (UInt_t muonCandVecItrTwo=muonCandVecItrOne+1; muonCandVecItrTwo<muonCandVecAr.size(); muonCandVecItrTwo++){
                                            std::cout <<"muonCandVecItrTwo " << muonCandVecItrTwo << " muonCandVecTwo " << muonCandVecAr[muonCandVecItrTwo] << "\n";
                                            ROOT::Math::PtEtaPhiMVector tmpVecSum = muonCandVecAr[muonCandVecItrOne]+muonCandVecAr[muonCandVecItrTwo];
                                            std::cout <<tmpVecSum << "\n";
                                            std::cout <<tmpVecSum.M() << "\n";
                                        }
                                    }
                                }
                                //std::cout <<"muonPassesZ2CutsAr " << muonPassesZ2CutsAr << "\n";
                                std::cout << "muonPassesZ2CutsAr loop\n";
                                for (UInt_t muonPassesZ2CutsInd=0; muonPassesZ2CutsInd<muonPassesZ2CutsAr.size();muonPassesZ2CutsInd++){
                                    std::cout << "muonPassesZ2CutsInd " << muonPassesZ2CutsInd << "muonPassesZ2CutsAr[muonPassesZ2CutsInd][0]" << muonPassesZ2CutsAr[muonPassesZ2CutsInd][0] << "\n";

                                }

                                //std::cout <<"muonPassesZ2CutsFinalAr " << muonPassesZ2CutsFinalAr << "\n";
                                std::cout << "muonPassesZ2CutsFinalAr loop\n";
                                for (UInt_t muonPassesZ2CutsFinalInd=0; muonPassesZ2CutsFinalInd<muonPassesZ2CutsFinalAr.size();muonPassesZ2CutsFinalInd++){
                                    std::cout << "muonPassesZ2CutsFinalInd " << muonPassesZ2CutsFinalInd << "muonPassesZ2CutsFinalAr[muonPassesZ2CutsFinalInd][0]" << muonPassesZ2CutsFinalAr[muonPassesZ2CutsFinalInd][0] << "\n";

                                }

                            }


                            //if (elecPassesZ2CutsFinalAr || muonPassesZ2CutsFinalAr){
                            if (eZ2CandsBool || mZ2CandsBool) {
                                if (debug) std::cout << "passed to Z2 Cut\n";
                                tmpZ2Ind = -1;
                                Z2IsMuon = false;
                                tmpTopZ2LeadPt = 0;
                                tmpTopZ2TrailingPt = 0;
                                tmpZ1Vec = Z1LeadVec+Z1TrailingVec;
                                tmpZ1M = tmpZ1Vec.M();

                                
                                if (eZ2CandsBool) dolZ2Cut(Z1LeadVec,Z1TrailingVec,tmpZ1Vec,tmpZ1M,Z1LeadCharge,Z1TrailingCharge,Z1IsMuon,eZ2VecPairAr,eZ2PtPairAr,eZ2ChargePairAr,tmpZ2Ind,Z2IsMuon,tmpTopZ2LeadPt,tmpTopZ2TrailingPt,fourLepInvMassCut,optLepInvMassCut,true);
                                if (mZ2CandsBool) dolZ2Cut(Z1LeadVec,Z1TrailingVec,tmpZ1Vec,tmpZ1M,Z1LeadCharge,Z1TrailingCharge,Z1IsMuon,mZ2VecPairAr,mZ2PtPairAr,mZ2ChargePairAr,tmpZ2Ind,Z2IsMuon,tmpTopZ2LeadPt,tmpTopZ2TrailingPt,fourLepInvMassCut,optLepInvMassCut,false);
                                if (debug) std::cout << "tmpZ2Ind " << tmpZ2Ind << " Z2IsMuon " << Z2IsMuon << " tmpTopZ2LeadPt " << tmpTopZ2LeadPt << " tmpTopZ2TrailingPt " << tmpTopZ2TrailingPt << "\n";
                                if (tmpZ2Ind >= 0){ //Passed Z2 Cut
                                    if (debug) std::cout << "passed Z2 cut\n";
                                    //passesZ2CutsCtr += 1
                                    tmpIso = 0;
                                    
                                    float tmpPt;
                                    

                                    if (!Z1IsMuon){
                                        if (debug) std::cout << "In first if\n";
                                        tmpPt = Z1LeadPt;
                                        if (tmpPt > 35){
                                            if (debug) std::cout << "lead pt > 35\n";
                                            if (abs(Electron_eta[elecCandIndAr[Z1LeadItr]]) < 1.4) tmpAdd = max(0., Electron_dr03EcalRecHitSumEt[elecCandIndAr[Z1LeadItr]] - 1.);
                                            else tmpAdd = Electron_dr03EcalRecHitSumEt[elecCandIndAr[Z1LeadItr]];
                                            tmpIso = ( Electron_dr03TkSumPt[elecCandIndAr[Z1LeadItr]] + tmpAdd + Electron_dr03HcalDepth1TowerSumEt[elecCandIndAr[Z1LeadItr]] ) / Electron_pt[elecCandIndAr[Z1LeadItr]];
                                        }
                                        else tmpIso = Electron_pfRelIso03_all[elecCandIndAr[Z1LeadItr]];
                                        
                                        Z1LeadIso = tmpIso;
                                        if (debug) std::cout << "Got Z1 Lead Iso\n";
                                        
                                        tmpPt = Z1TrailingPt;
                                        if (tmpPt > 35){
                                            if (debug) std::cout << "trailing pt > 35\n";
                                            if (abs(Electron_eta[elecCandIndAr[Z1TrailingItr]]) < 1.4) tmpAdd = max(0., Electron_dr03EcalRecHitSumEt[elecCandIndAr[Z1TrailingItr]] - 1.);
                                            else tmpAdd = Electron_dr03EcalRecHitSumEt[elecCandIndAr[Z1TrailingItr]];
                                            tmpIso = ( Electron_dr03TkSumPt[elecCandIndAr[Z1TrailingItr]] + tmpAdd + Electron_dr03HcalDepth1TowerSumEt[elecCandIndAr[Z1LeadItr]] ) / Electron_pt[elecCandIndAr[Z1LeadItr]];
                                        }
                                        else tmpIso = Electron_pfRelIso03_all[elecCandIndAr[Z1TrailingItr]];
                                        Z1TrailingIso = tmpIso;
                                    }
                                    else{
                                        if (debug) std::cout << "getting Z1 muon Isos\n";
                                        Z1LeadIso = Muon_pfRelIso03_all[muonCandIndAr[Z1LeadItr]];
                                        Z1TrailingIso = Muon_pfRelIso03_all[muonCandIndAr[Z1TrailingItr]];
                                        //Z1LeadIso = mIso[muonCandIndAr[Z1LeadItr]]
                                        //Z1TrailingIso = mIso[muonCandIndAr[Z1TrailingItr]]
                                    }
                                    if (debug) std::cout << "Now Z2\n";
                                    if (!Z2IsMuon){
                                        if (debug) std::cout << "In first Z2 if\n";
                                        //Z2LeadIso = eIso[elecPassesZ2CutsFinalAr[tmpZ2Ind][0]]
                                        //Z2TrailingIso = eIso[elecPassesZ2CutsFinalAr[tmpZ2Ind][1]]

                                        tmpPt = tmpTopZ2LeadPt;
                                        if (tmpPt > 35){
                                            if (debug) std::cout << "Z2 lead pt > 35\n";
                                            /*
                                            if (debug) std::cout << "tmpZ2Ind " << tmpZ2Ind << "\n";
                                            if (debug) std::cout << "elecPassesZ2CutsAr[tmpZ2Ind][0] " << elecPassesZ2CutsAr[tmpZ2Ind][0] << "\n";
                                            if (debug) std::cout << "Electron_eta[elecPassesZ2CutsAr[tmpZ2Ind][0]] " << Electron_eta[elecPassesZ2CutsAr[tmpZ2Ind][0]] << "\n";
                                            if (debug) std::cout << "abs(Electron_eta[elecPassesZ2CutsAr[tmpZ2Ind][0]]) " << abs(Electron_eta[elecPassesZ2CutsAr[tmpZ2Ind][0]]) << "\n";
                                            if (debug) std::cout << "Electron_dr03EcalRecHitSumEt[elecPassesZ2CutsAr[tmpZ2Ind][0]] " << Electron_dr03EcalRecHitSumEt[elecPassesZ2CutsAr[tmpZ2Ind][0]] << "\n";
                                            if (debug) std::cout << "Electron_dr03TkSumPt[elecPassesZ2CutsAr[tmpZ2Ind][0]] " << Electron_dr03TkSumPt[elecPassesZ2CutsAr[tmpZ2Ind][0]] << "\n";
                                            if (debug) std::cout << "Electron_dr03HcalDepth1TowerSumEt[elecPassesZ2CutsAr[tmpZ2Ind][0]] " << Electron_dr03HcalDepth1TowerSumEt[elecPassesZ2CutsAr[tmpZ2Ind][0]] << "\n";
                                            if (debug) std::cout << "Electron_pt[elecPassesZ2CutsAr[tmpZ2Ind][0]] " << Electron_pt[elecPassesZ2CutsAr[tmpZ2Ind][0]] << "\n";
                                            */



                                            if (abs(Electron_eta[elecPassesZ2CutsAr[tmpZ2Ind][0]]) < 1.4) tmpAdd = max(0., Electron_dr03EcalRecHitSumEt[elecPassesZ2CutsAr[tmpZ2Ind][0]] - 1.);
                                            else tmpAdd = Electron_dr03EcalRecHitSumEt[elecPassesZ2CutsAr[tmpZ2Ind][0]];
                                            tmpIso = ( Electron_dr03TkSumPt[elecPassesZ2CutsAr[tmpZ2Ind][0]] + tmpAdd + Electron_dr03HcalDepth1TowerSumEt[elecPassesZ2CutsAr[tmpZ2Ind][0]] ) / Electron_pt[elecPassesZ2CutsAr[tmpZ2Ind][0]];
                                        }
                                        else tmpIso = Electron_pfRelIso03_all[elecPassesZ2CutsAr[tmpZ2Ind][0]];
                                        if (debug) std::cout << "Got Z2 Lead Iso\n";
                                        Z2LeadIso = tmpIso;
                                        if (debug) std::cout << "Got Z2 Lead Iso\n";

                                        
                                        tmpPt = tmpTopZ2TrailingPt;
                                        if (tmpPt > 35){
                                            if (debug) std::cout << "Z2 trailing pt > 35\n";
                                            if (abs(Electron_eta[elecPassesZ2CutsAr[tmpZ2Ind][1]]) < 1.4) tmpAdd = max(0., Electron_dr03EcalRecHitSumEt[elecPassesZ2CutsAr[tmpZ2Ind][1]] - 1.);
                                            else tmpAdd = Electron_dr03EcalRecHitSumEt[elecPassesZ2CutsAr[tmpZ2Ind][1]];
                                            tmpIso = ( Electron_dr03TkSumPt[elecPassesZ2CutsAr[tmpZ2Ind][1]] + tmpAdd + Electron_dr03HcalDepth1TowerSumEt[elecPassesZ2CutsAr[tmpZ2Ind][1]] ) / Electron_pt[elecPassesZ2CutsAr[tmpZ2Ind][1]];
                                        }
                                        else tmpIso = Electron_pfRelIso03_all[elecPassesZ2CutsAr[tmpZ2Ind][1]];
                                        Z2TrailingIso = tmpIso;
                                        if (debug) std::cout << "Got Z2 trailing Iso\n";
                                    }

                                    else{
                                        if (debug) std::cout << "getting Z2 muon Isos\n";
                                        Z2LeadIso = Muon_pfRelIso03_all[muonPassesZ2CutsFinalAr[tmpZ2Ind][0]];
                                        Z2TrailingIso = Muon_pfRelIso03_all[muonPassesZ2CutsFinalAr[tmpZ2Ind][1]];
                                        //Z2LeadIso = mIso[muonPassesZ2CutsFinalAr[tmpZ2Ind][0]]
                                        //Z2TrailingIso = mIso[muonPassesZ2CutsFinalAr[tmpZ2Ind][1]]
                                    }
                                    if (debug) std::cout << "Z1LeadIso " << Z1LeadIso << " Z1TrailingIso " << Z1TrailingIso << " Z2LeadIso " << Z2LeadIso << " Z2TrailingIso " << Z2TrailingIso << "\n";

                                    
                                    bool passIsoCut = doISOCut(Z1LeadIso,Z1TrailingIso,Z2LeadIso,Z2TrailingIso,lepIsoCut);

                                    if (passIsoCut){
                                        
                                        if (debug) std::cout << "passed iso cut yay\n";
                                        //passesIsoCutCtr += 1
                                        if (!Z1IsMuon){
                                            Z1LeadSIP = Electron_sip3d[elecCandIndAr[Z1LeadItr]];
                                            Z1TrailingSIP = Electron_sip3d[elecCandIndAr[Z1TrailingItr]];
                                        }
                                        else{
                                            Z1LeadSIP = Muon_sip3d[muonCandIndAr[Z1LeadItr]];
                                            Z1TrailingSIP = Muon_sip3d[muonCandIndAr[Z1TrailingItr]];
                                        }
                                        if (!Z2IsMuon){
                                            Z2LeadSIP = Electron_sip3d[elecPassesZ2CutsFinalAr[tmpZ2Ind][0]];
                                            Z2TrailingSIP = Electron_sip3d[elecPassesZ2CutsFinalAr[tmpZ2Ind][1]];
                                        }
                                        else{
                                            Z2LeadSIP = Muon_sip3d[muonPassesZ2CutsFinalAr[tmpZ2Ind][0]];
                                            Z2TrailingSIP = Muon_sip3d[muonPassesZ2CutsFinalAr[tmpZ2Ind][1]];
                                        }
                                        if (debug) std::cout << "Z1LeadSIP " << Z1LeadSIP << " Z1TrailingSIP " << Z1TrailingSIP << " Z2LeadSIP " << Z2LeadSIP << " Z2TrailingSIP " << Z2TrailingSIP << "\n"; 
                                        //Fill with HIGHEST SIP
                                        
                                        bool passSIPCut = doSIPCut(Z1LeadSIP,Z1TrailingSIP,Z2LeadSIP,Z2TrailingSIP,SIPCut);
                                        if (passSIPCut){
                                            if (debug) cout << "passed SIP cut yay\n";
                                            passLepCut += 1;
                                            passesCutsBool = true;
                                            passedAsLepBool = true;
                                        }
                                    }

                                }

                            }
                                
                            
                        }
                    }

                }

                Int_t FJInd;
                if (debug) std::cout << "passesCutsBool " << passesCutsBool << " isSemiLeptonic " << isSemiLeptonic << "\n";
                if ((!passesCutsBool)){
                    if (debug) std::cout << "trying SemiLeptonic\n";
                    tryingSemiLepCtr += 1;
                    FJInd = -1;
                    UInt_t numFatJet = *nFatJet;
                    doSemiLepChanFatJetCut(FJInd,numFatJet,hFatJet_ind_fromHTag,fatJetPTCut,fatJetZTagCut,FatJet_pt,FatJet_phi,FatJet_eta,FatJet_deepTag_ZvsQCD,selectedFJ_phi,selectedFJ_eta);
                    /*
                    for (UInt_t i=0; i<*nFatJet;i++){
                        tmpFatJetPT = FatJet_pt[i];
                        if (tmpFatJetPT > fatJetPTCut) FJInd = i;
                    }
                    */
                    if (FJInd != -1){
                        if (debug) cout << "passed FJ check\n";

                        enoughElecCands = false;
                        negElecCands = 0;
                        posElecCands = 0;
                        totElecCands = 0;
                        elecCandIndAr.clear();
                        elecCandVecAr.clear();
                        elecCandChargeAr.clear();

                        if (neLep){
                            if (debug) std::cout << "Doing elec cand cut\n";
                            dolCandCut(Electron_eta,Electron_mass,Electron_charge,Electron_phi,Electron_pt,neLep,elecCandIndAr,elecCandVecAr,elecCandChargeAr,ePtCut,eEtaCut,debug);
                            
                            for (UInt_t elecCandChargeInd=0;elecCandChargeInd<elecCandChargeAr.size();elecCandChargeInd++){
                                if (debug) std::cout << "elecCandChargeInd " << elecCandChargeInd << " elecCandChargeAr[elecCandChargeInd] " << elecCandChargeAr[elecCandChargeInd] << "\n";
                                if (elecCandChargeAr[elecCandChargeInd] == -1) negElecCands += 1;
                                else posElecCands += 1;
                            }
                            totElecCands = std::min(negElecCands,posElecCands);
                            if (totElecCands >= 1) enoughElecCands = true;
                        }


                        enoughMuonCands = false;
                        negMuonCands = 0;
                        posMuonCands = 0;
                        totMuonCands = 0;
                        muonCandIndAr.clear();
                        muonCandVecAr.clear();
                        muonCandChargeAr.clear();

                        if (debug){
                            std::cout << "--------------------------------------------\n";
                            std::cout << "neLep " << neLep << "\n";
                            for (UInt_t tmpItr=0; tmpItr < neLep; tmpItr++){
                                std::cout <<"tmpItr " << tmpItr << " Electron_pt[tmpItr] " << Electron_pt[tmpItr] << " Electron_eta[tmpItr] " << Electron_eta[tmpItr] << " Electron_charge[tmpItr] " << Electron_charge[tmpItr] << "\n";
                            }
                        }
                        if (nmLep){
                            if (debug) std::cout << "Doing muon cand cut\n";

                            dolCandCut(Muon_eta,Muon_mass,Muon_charge,Muon_phi,Muon_pt,nmLep,muonCandIndAr,muonCandVecAr,muonCandChargeAr,mPtCut,mEtaCut,debug);

                            //domCandCut(Muon_eta,Muon_mass,Muon_charge,Muon_phi,Muon_pt,neLep,muonCandIndAr,muonCandVecAr,muonCandChargeAr,mPtCut,mEtaCut);
                            for (UInt_t muonCandChargeInd=0;muonCandChargeInd<muonCandChargeAr.size();muonCandChargeInd++){
                                if (muonCandChargeAr[muonCandChargeInd] == -1) negMuonCands += 1;
                                else posMuonCands += 1;
                            }
                            totMuonCands = std::min(negMuonCands,posMuonCands);
                            if (totMuonCands >= 1) enoughMuonCands = true;
                        }


                        enoughLepCands = false;
                        if (totElecCands || totMuonCands) enoughLepCands = true;
                        if (debug){
                            std::cout << "negElecCands " << negElecCands << " posElecCands " << posElecCands << " totElecCands " << totElecCands << "\n";
                            std::cout << "nmLep " << nmLep << " negMuonCands " << negMuonCands << " posMuonCands " << posMuonCands << " totMuonCands " << totMuonCands << "\n";
                            std::cout << "enoughLepCands " << enoughLepCands << "\n";
                        }
                        

                        if (enoughLepCands){ //Check there are enough lep cands after candidate cuts
                            //passesCandCutsCtr += 1
                            Z1Cand = false;
                            difFromZMassOne = 1000.;
                            Z1LeadItr = -1;
                            Z1TrailingItr = -1;
                            Z1LeadPt = 0.;
                            Z1TrailingPt = 0.;
                            Z1IsMuon = false;
                            Z1LeadCharge = 0;
                            Z1TrailingCharge = 0;
                            Z1LeadIso = 0;
                            Z1TrailingIso = 0;
                            std::vector<std::array<UInt_t,2>> elecPassesZ2CutsAr;
                            if (enoughElecCands){ //If enough elec cands, run Z1 cuts
                            
                                dolZ1Cut(Electron_pt,elecCandIndAr,elecCandVecAr,elecCandChargeAr,elecPassesZ2CutsAr,Z1IsMuon,false,invMassCutLow,invMassCutHigh,ptLeadCut,ptTrailingCut,Z1LeadPt,Z1TrailingPt,Z1LeadItr,Z1TrailingItr,Z1LeadVec,Z1TrailingVec,Z1LeadCharge,Z1TrailingCharge,difFromZMassOne,debug);
                            }
                            std::vector<std::array<UInt_t,2>> muonPassesZ2CutsAr;
                            if (enoughMuonCands){ //If enough muon cands, run Z1 cuts
                                dolZ1Cut(Muon_pt,muonCandIndAr,muonCandVecAr,muonCandChargeAr,muonPassesZ2CutsAr,Z1IsMuon,true,invMassCutLow,invMassCutHigh,ptLeadCut,ptTrailingCut,Z1LeadPt,Z1TrailingPt,Z1LeadItr,Z1TrailingItr,Z1LeadVec,Z1TrailingVec,Z1LeadCharge,Z1TrailingCharge,difFromZMassOne,debug);
                            }
                            if (debug) std::cout <<"Z1LeadItr " << Z1LeadItr << " Z1TrailingItr " << Z1TrailingItr << " Z1LeadPt " << Z1LeadPt << " Z1TrailingPt " << Z1TrailingPt << " Z1LeadVec " << Z1LeadVec << " Z1TrailingVec " << Z1TrailingVec << " Z1LeadCharge " << Z1LeadCharge << " Z1TrailingCharge " << Z1TrailingCharge << " Z1IsMuon " << Z1IsMuon << " difFromZMassOne " << difFromZMassOne << "\n";
                            if (Z1LeadItr >= 0) { //If Z1 found
                                bool semiLepPassIso = false;
                                if (!Z1IsMuon){
                                    if (debug) std::cout << "D01 \n";
                                    if (Z1LeadPt > 35){
                                        if (debug) std::cout << "D02 \n";
                                        if (abs(Electron_eta[elecCandIndAr[Z1LeadItr]]) < 1.4) tmpAdd = max(0., Electron_dr03EcalRecHitSumEt[elecCandIndAr[Z1LeadItr]] - 1.);
                                        else tmpAdd = Electron_dr03EcalRecHitSumEt[elecCandIndAr[Z1LeadItr]];
                                        tmpIso = ( Electron_dr03TkSumPt[elecCandIndAr[Z1LeadItr]] + tmpAdd + Electron_dr03HcalDepth1TowerSumEt[elecCandIndAr[Z1LeadItr]] ) / Electron_pt[elecCandIndAr[Z1LeadItr]];
                                    }
                                    else tmpIso = Electron_pfRelIso03_all[elecCandIndAr[Z1LeadItr]];
                                    Z1LeadIso = tmpIso;
                                
                                    if (Z1TrailingPt > 35){
                                        if (debug) std::cout << "D03 \n";
                                        if (abs(Electron_eta[elecCandIndAr[Z1TrailingItr]]) < 1.4) tmpAdd = max(0., Electron_dr03EcalRecHitSumEt[elecCandIndAr[Z1TrailingItr]] - 1.);
                                        else tmpAdd = Electron_dr03EcalRecHitSumEt[elecCandIndAr[Z1TrailingItr]];
                                        tmpIso = ( Electron_dr03TkSumPt[elecCandIndAr[Z1TrailingItr]] + tmpAdd + Electron_dr03HcalDepth1TowerSumEt[elecCandIndAr[Z1LeadItr]] ) / Electron_pt[elecCandIndAr[Z1LeadItr]];
                                    }
                                    else tmpIso = Electron_pfRelIso03_all[elecCandIndAr[Z1TrailingItr]];
                                    Z1TrailingIso = tmpIso;
                                }
                                else{
                                    if (debug) std::cout << "D04 \n";
                                    if (debug) std::cout << "Z1LeadItr " << Z1LeadItr << "\n";
                                    if (debug) std::cout << "muonCandIndAr[Z1LeadItr]" << muonCandIndAr[Z1LeadItr] << "\n";
                                    Z1LeadIso = Muon_pfRelIso03_all[muonCandIndAr[Z1LeadItr]];
                                    Z1TrailingIso = Muon_pfRelIso03_all[muonCandIndAr[Z1TrailingItr]];
                                }
                                semiLepPassIso = doSemiLepISOCut(Z1LeadIso,Z1TrailingIso,lepIsoCut);
                                if (semiLepPassIso) {
                                    if (debug) std::cout << "Passed as SemiLep\n";
                                    passSemiLepCut += 1;
                                    passesCutsBool = true;
                                    passedAsSemiLepBool = true;
                                    if (debug) {
                                        std::cout << "Z1IsMuon " <<Z1IsMuon<< "\n";
                                        std::cout << "elecCandIndAr size " << elecCandIndAr.size() << "\n";

                                        std::cout << "muonCandIndAr loop " << muonCandIndAr.size() << "\n";
                                        
                                        for (UInt_t muonCandIndInd=0; muonCandIndInd<muonCandIndAr.size();muonCandIndInd++){
                                            std::cout << "muonCandIndInd " << muonCandIndInd << "muonCandIndAr[muonCandIndInd]" << muonCandIndAr[muonCandIndInd] << "\n";

                                        }
                                    }
                                }

                            }
                        }
                    }
                }
                if (debug) std::cout << "Test\n";
                if ((!passesCutsBool)){
                    tryingHadCtr += 1;
                    LFJOneInd = -1;
                    LFJTwoInd = -1;
                    FJInvMass = -1;
                    if (debugHadronic) std::cout << "---------------- Event " << evCount - 1 << " ----------------\n";
                    //if (debugHadronic) std::cout << "hFatJet_ind_fromHTag " << hFatJet_ind_fromHTag << "\n";
                    if (debugHadronic) std::cout << "fatJetPTCut " << fatJetPTCut << "\n";

                    if (debugHadronic) std::cout << "--------- Entering FJ loop for Hadronic Channel ---------\n";

                    UInt_t numFatJet = *nFatJet;
                    doHadChanFatJetCut(LFJOneInd,LFJTwoInd,FJInvMass,numFatJet,hFatJet_ind_fromHTag,fatJetPTCut,fatJetZPairInvMassCut,FatJet_pt,FatJet_phi,FatJet_eta,FatJet_mass,selectedFJ_phi,selectedFJ_eta,hFatJet_pt_fromHTag);

                    
                    if (LFJOneInd != LFJTwoInd){
                        passHadCut += 1;
                        passesCutsBool = true;
                        passedAsHadBool = true;
                    }
                }


                //Now match VBF jets
                UInt_t nJetLen        = *nJet;
                UInt_t leadJet_1      = 0;
                UInt_t leadJet_2      = 0;
                float jetLeadPt      = 0;
                float jetTrailingPt  = 0;
                ROOT::Math::PtEtaPhiMVector jetLeadVec;
                ROOT::Math::PtEtaPhiMVector jetTrailingVec;
                float jetPairInvMass = 0;
                float jetLeadPhi     = 0;
                float jetTrailingPhi = 0;
                float jetLeadEta     = 0;
                float jetTrailingEta = 0;
                if (debug) std::cout << "Entering jet loop. Len: " << nJetLen << "\n";
                doVBFJetCut(nJetLen,Jet_pt,Jet_jetId,Jet_eta,Jet_phi,Jet_mass,jetPTCut,jetEtaDifCut,jetInvMassCut,jetPairInvMass,jetLeadPt,jetLeadEta,jetLeadPhi,jetTrailingPt,jetTrailingEta,jetTrailingPhi,leadJet_1,leadJet_2,,selectedFJ_phi,selectedFJ_eta,debug);
                
                if (jetLeadPt == 0) continue;
                debugOutputForVBFJetCut(evCount,leadJet_1,leadJet_2,Jet_phi,Jet_eta,debug);
                /*
                if (debug){
                    std::cout << " found jet pairs\n";
                    std::cout << evCount+1 << " selected jet pair\n";
                    std::cout << "Lead jet ind    " << leadJet_1 << "\n";
                    std::cout << "Trailing jet ind    " << leadJet_2 << "\n";
                    std::cout << "Lead jet phi    " << Jet_phi[leadJet_1] << "\n";
                    std::cout << "Trailing jet phi    " << Jet_phi[leadJet_2] << "\n";
                    std::cout << "Lead jet eta    " << Jet_eta[leadJet_1] << "\n";
                    std::cout << "Trailing jet eta    " << Jet_eta[leadJet_2] << "\n";
                }
                */
                passVBFJets += 1;

                if (passesCutsBool){
                    if (debug) std::cout << "Passed cuts. Now filling trees\n";
                    passesCutsCtr += 1;
                    //Fill tree
                    if (debug) std::cout << "Filling jets\n";
                    nJetL = *nJet;
                    jetLeadPtL = jetLeadPt;
                    jetTrailingPtL = jetTrailingPt;
                    jetLeadPhiL = jetLeadPhi;
                    jetTrailingPhiL = jetTrailingPhi;
                    jetPairInvMassL = jetPairInvMass;
                    jetLeadEtaL = jetLeadEta;
                    jetTrailingEtaL = jetTrailingEta;
                    //now fat jets
                    if (debug) std::cout << "Filling fat jets\n";
                    nFatJetL = *nFatJet;
                    /*
                    
                    hFatJet_pt_fromPtL = hFatJet_pt_fromPt;
                    hFatJet_phi_fromPtL = hFatJet_phi_fromPt;
                    hFatJet_eta_fromPtL = hFatJet_eta_fromPt;
                    hFatJet_mass_fromPtL = hFatJet_mass_fromPt;
                    hFatJet_HTag_fromPtL = hFatJet_HTag_fromPt;
                    */
                    hFatJet_pt_fromHTagL = hFatJet_pt_fromHTag;
                    hFatJet_phi_fromHTagL = hFatJet_phi_fromHTag;
                    hFatJet_eta_fromHTagL = hFatJet_eta_fromHTag;
                    hFatJet_mass_fromHTagL = hFatJet_mass_fromHTag;
                    hFatJet_HTag_fromHTagL = hFatJet_HTag_fromHTag;
                    

                    //Now GenPart
                    //print(nGenPart)
                    if (debug) std::cout << "Filling gen parts\n";

                    nGenPartL = *nGenPart;
                    /*
                    hGenPartDR_fromPtL = hGenPartDR_fromPt;
                    hGenPartInd_fromPtL = hGenPartInd_fromPt;
                    hGenPartpdgId_fromPtL = hGenPartpdgId_fromPt;
                    hGenPartFirstMompdgId_fromPtL = hGenPartFirstMompdgId_fromPt;
                    */
                    hGenPartDR_fromHTagL = hGenPartDR_fromHTag;
                    hGenPartInd_fromHTagL = hGenPartInd_fromHTag;
                    hGenPartpdgId_fromHTagL = hGenPartpdgId_fromHTag;
                    hGenPartFirstMompdgId_fromHTagL = hGenPartFirstMompdgId_fromHTag;

                    //HLT stuff
                    if (debug) std::cout << "Filling HLT\n";

                    hbbTagL = hbbTag;

                    doubleElecHLTL = doubleElecHLT;
                    doubleMuonHLTL = doubleMuonHLT;
                    muonEGHLTL = muonEGHLT;
                    elecHLTL = elecHLT;
                    muonHLTL = muonHLT;
                    hadHLTL = hadHLT;
                    isLeptonicL = isLeptonic;
                    isSemiLeptonicL = isSemiLeptonic;
                    isHadronicL = isHadronic;

                    //Branches for distinguishing between channels
                    
                    passedLepL = passedAsLepBool ;
                    passedSemiLepL = passedAsSemiLepBool;
                    passedHadL = passedAsHadBool;

                    FATree->Fill();



                    if (debug) std::cout << "Filling channel branches \n";
                    evPassCount += 1;
                    ROOT::Math::PtEtaPhiMVector tmpZ2LeadVec;
                    ROOT::Math::PtEtaPhiMVector tmpZ2TrailingVec;
                    ROOT::Math::PtEtaPhiMVector tmpZ2Vec;
                    tmpIso = 0;

                }

            }

        }
    }
    if (debug) std::cout << "Filling complete \n";

    clock_t endt = clock();
    double time_spent = (double)(endt - startt) / CLOCKS_PER_SEC;


    std::cout << "Finished file loop. " << "time: " << time_spent << "\n";

    nEv = evRunOver;
    nEvPass = evPassCount;
    evNumTree->Fill();

    std::cout << "evRunOver: " << evRunOver << " -------------------\n";
    std::cout << "passes HLT cut: " << passHLTCtr << " -------------------\n";
    std::cout << "passes channel cut: " << passAnyChannelCtr << " -------------------\n";
    std::cout << "passes lep channel cut: " << passLepChannelCtr << "\n";
    std::cout << "passes semi lep channel cut: " << passSemiLepChannelCtr << "\n";
    std::cout << "passes had channel cut: " << passHadChannelCtr << "\n";
    std::cout << "passes lep and semi lep channel cut: " << passLepAndSemiLepChannelCtr << "\n";
    std::cout << "passes lep and had channel cut: " << passLepAndHadChannelCtr << "\n";
    std::cout << "passes semi lep and had channel cut: " << passSemiLepAndHadChannelCtr << "\n";
    std::cout << "passes all channel cut: " << passAllChannelCtr << "\n";
    std::cout << "passes VBF Jet cut: " << passVBFJets << " -------------------\n";
    std::cout << "passes Higgs FatJet cut: " << passFatJets << "\n";
    std::cout << "passes Higgs GenPart cut: " << passGenPart << " -------------------\n";

    std::cout << "passes all cuts: " << passesCutsCtr << " -------------------\n";
    std::cout << "evPassCount: " << evPassCount << "\n";

    std::cout << "ZFJSameJetCtr " << ZFJSameJetCtr << "\n";

    std::cout << "ZFJSameJetTaggedCtr " << ZFJSameJetTaggedCtr << "\n";

    if (!isBackground){
        std::cout << "Cross section average before division: " << crossSectionAvg << "\n";
        std::cout << "Cross section counter: " << crossSectionCtr << "\n";
        crossSectionAvg = crossSectionAvg / crossSectionCtr;
        std::cout << "Cross section average after division: " << crossSectionAvg << "\n";
        //XS Tree
        float crossSectionVar;
        TTree* crossSectionTree = new TTree("crossSectionTree","crossSectionTree");
        crossSectionTree->Branch("crossSectionVar",&crossSectionVar,"crossSectionVar/F");
        crossSectionVar = crossSectionAvg;
        crossSectionTree->Fill();
        crossSectionTree->Write("",TObject::kOverwrite);
    }

    outFile->cd();
    evNumTree->Write("",TObject::kOverwrite);
    FATree->Write("",TObject::kOverwrite);
    if (useLHETree) {
        RawTree->Write("",TObject::kOverwrite);
        if (useFJGenMatchTree) {
            ZFJGenTaggedTree->Write("",TObject::kOverwrite);
            HFJGenTree->Write("",TObject::kOverwrite);
            ZHFJGenTaggedTree->Write("",TObject::kOverwrite);
        }
        if (useJGenMatchTree || useFJGenMatchTree) {
            GenRawTree->Write("",TObject::kOverwrite);
            GenRawTaggedTree->Write("",TObject::kOverwrite);
            GenRawSemiLepTaggedTree->Write("",TObject::kOverwrite);
            GenRawLepTaggedTree->Write("",TObject::kOverwrite);
        }

    }

    outFile->Close();
}