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
#include "new032022FoMAnalysis.h"
#include "new032022FoMAnalysis_Functions.h"
#include "genFileList.h"
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


void new032022hFatJetPtCutFoMAnalysis(){
    // Open the file. Note that the name of your file outside this class
    // will probably NOT be experiment.root.
    std::cout << "start hFatJetPtCut FoM Analysis\n";
    clock_t startt = clock();
    //Analyzer will run over all files put into fileAr

    for (UInt_t rangeItr=0; rangeItr<cutAmnt+1; rangeItr++){
        cutPassAr.push_back(0);
        cutRangeAr.push_back(hFatJetPTCutRangeBottom+(rangeItr*hFatJetPTCutStep));
    }

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
    if (scratchDown) strAdd ="/afs/crc.nd.edu/user/d/dlutton/Public/condorStuff/NanoAODToHistos/tmpHoldForNanoAODWithoutScratch/";
    else strAdd ="/scratch365";

    if (MGC2VEtaDifCut){
        saveName = "C2VEtaDifCut";
        isBackground = false;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisC2VEtaDifCut.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2V3MC){
        saveName = "SDC2V3MC";
        isBackground = false;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisSDC2V3MCEtaDifCut.root";
        fileAr.push_back(tmpStrWithPath);
        
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
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisOHW.root";
        fileAr.push_back(tmpStrWithPath);
        
    }
    else if (MGSM){
        saveName = "SM";
        isBackground = false;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisSM.root";
        fileAr.push_back(tmpStrWithPath);
        
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
    /*
    std::string outFileStr = "new032022FullAnalysis"+saveName+cutName+".root";
    std::cout << "OutFile: " << outFileStr << "\n";
    TFile *outFile = new TFile(outFileStr.c_str(),"RECREATE");
    */
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
    UInt_t passFJMatch = 0;
    UInt_t passLepCut = 0;
    UInt_t passSemiLepCut = 0;
    UInt_t passHadCut = 0;

    UInt_t passChannelCtr = 0;

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
    //"FullPassL" is for leaf
    //First jets
    UInt_t nJetFullPassL;
    float jetLeadPtFullPassL;
    float jetTrailingPtFullPassL;
    float jetLeadPhiFullPassL;
    float jetTrailingPhiFullPassL;
    float jetPairInvMassFullPassL;
    float jetLeadEtaFullPassL;
    float jetTrailingEtaFullPassL;
    //now fat jets
    UInt_t nFatJetFullPassL;
    /*
    float hFatJet_pt_fromPtFullPassL;
    float hFatJet_phi_fromPtFullPassL;
    float hFatJet_eta_fromPtFullPassL;
    float hFatJet_mass_fromPtFullPassL;
    float hFatJet_HTag_fromPtFullPassL;
    */
    float hFatJet_pt_fromHTagFullPassL;
    float hFatJet_phi_fromHTagFullPassL;
    float hFatJet_eta_fromHTagFullPassL;
    float hFatJet_mass_fromHTagFullPassL;
    float hFatJet_HTag_fromHTagFullPassL;

    //Now GenPart

    UInt_t nGenPartFullPassL;
    /*
    float hGenPartDR_fromPtFullPassL;
    float hGenPartInd_fromPtFullPassL;
    float hGenPartpdgId_fromPtFullPassL;
    Int_t hGenPartFirstMompdgId_fromPtFullPassL;
    */
    float hGenPartDR_fromHTagFullPassL;
    float hGenPartInd_fromHTagFullPassL;
    float hGenPartpdgId_fromHTagFullPassL;
    Int_t hGenPartFirstMompdgId_fromHTagFullPassL;

    //Now HLT stuff;

    //Branches for distinguishing between channels;
    bool passedLepFullPassL;
    bool passedSemiLepFullPassL;
    bool passedHadFullPassL;

    //Now tree and branches;

    TTree *FATree = new TTree("FATree", "FATree");

    //cutTree->Branch("evInd",evInd,"evInd/I");

    FATree->Branch("nJetFullPassL",&nJetFullPassL,"nJetFullPassL/i");
    FATree->Branch("jetLeadPtFullPassL",&jetLeadPtFullPassL,"jetLeadPtFullPassL/F");
    FATree->Branch("jetTrailingPtFullPassL",&jetTrailingPtFullPassL,"jetTrailingPtFullPassL/F");
    FATree->Branch("jetLeadPhiFullPassL",&jetLeadPhiFullPassL,"jetLeadPhiFullPassL/F");
    FATree->Branch("jetTrailingPhiFullPassL",&jetTrailingPhiFullPassL,"jetTrailingPhiFullPassL/F");
    FATree->Branch("jetPairInvMassFullPassL",&jetPairInvMassFullPassL,"jetPairInvMassFullPassL/F");
    FATree->Branch("jetLeadEtaFullPassL",&jetLeadEtaFullPassL,"jetLeadEtaFullPassL/F");
    FATree->Branch("jetTrailingEtaFullPassL",&jetTrailingEtaFullPassL,"jetTrailingEtaFullPassL/F");
    //now fat jets;
    FATree->Branch("nFatJetFullPassL",&nFatJetFullPassL,"nFatJetFullPassL/i");
    /*
    FATree->Branch("hFatJet_pt_fromPtFullPassL",&hFatJet_pt_fromPtFullPassL,"hFatJet_pt_fromPtFullPassL/F");
    FATree->Branch("hFatJet_phi_fromPtFullPassL",&hFatJet_phi_fromPtFullPassL,"hFatJet_phi_fromPtFullPassL/F");
    FATree->Branch("hFatJet_eta_fromPtFullPassL",&hFatJet_eta_fromPtFullPassL,"hFatJet_eta_fromPtFullPassL/F");
    FATree->Branch("hFatJet_mass_fromPtFullPassL",&hFatJet_mass_fromPtFullPassL,"hFatJet_mass_fromPtFullPassL/F");
    FATree->Branch("hFatJet_HTag_fromPtFullPassL",&hFatJet_HTag_fromPtFullPassL,"hFatJet_HTag_fromPtFullPassL/F");
    */
    FATree->Branch("hFatJet_pt_fromHTagFullPassL",&hFatJet_pt_fromHTagFullPassL,"hFatJet_pt_fromHTagFullPassL/F");
    FATree->Branch("hFatJet_phi_fromHTagFullPassL",&hFatJet_phi_fromHTagFullPassL,"hFatJet_phi_fromHTagFullPassL/F");
    FATree->Branch("hFatJet_eta_fromHTagFullPassL",&hFatJet_eta_fromHTagFullPassL,"hFatJet_eta_fromHTagFullPassL/F");
    FATree->Branch("hFatJet_mass_fromHTagFullPassL",&hFatJet_mass_fromHTagFullPassL,"hFatJet_mass_fromHTagFullPassL/F");
    FATree->Branch("hFatJet_HTag_fromHTagFullPassL",&hFatJet_HTag_fromHTagFullPassL,"hFatJet_HTag_fromHTagFullPassL/F");

    //now genpart
    FATree->Branch("nGenPartFullPassL",&nGenPartFullPassL,"nGenPartFullPassL/i");
    /*
    FATree->Branch("hGenPartDR_fromPtFullPassL",&hGenPartDR_fromPtFullPassL,"hGenPartDR_fromPtFullPassL/F");
    FATree->Branch("hGenPartInd_fromPtFullPassL",&hGenPartInd_fromPtFullPassL,"hGenPartInd_fromPtFullPassL/F");
    FATree->Branch("hGenPartpdgId_fromPtFullPassL",&hGenPartpdgId_fromPtFullPassL,"hGenPartpdgId_fromPtFullPassL/F");
    FATree->Branch("hGenPartFirstMompdgId_fromPtFullPassL",&hGenPartFirstMompdgId_fromPtFullPassL,"hGenPartFirstMompdgId_fromPtFullPassL/I");
    */
    FATree->Branch("hGenPartDR_fromHTagFullPassL",&hGenPartDR_fromHTagFullPassL,"hGenPartDR_fromHTagFullPassL/F");
    FATree->Branch("hGenPartInd_fromHTagFullPassL",&hGenPartInd_fromHTagFullPassL,"hGenPartInd_fromHTagFullPassL/F");
    FATree->Branch("hGenPartpdgId_fromHTagFullPassL",&hGenPartpdgId_fromHTagFullPassL,"hGenPartpdgId_fromHTagFullPassL/F");
    FATree->Branch("hGenPartFirstMompdgId_fromHTagFullPassL",&hGenPartFirstMompdgId_fromHTagFullPassL,"hGenPartFirstMompdgId_fromHTagFullPassL/I");


    //Branches for distinguishing between channels;
    FATree->Branch("passedLepFullPassL",&passedLepFullPassL,"passedLepFullPassL/O");
    FATree->Branch("passedSemiLepFullPassL",&passedSemiLepFullPassL,"passedSemiLepFullPassL/O");
    FATree->Branch("passedHadFullPassL",&passedHadFullPassL,"passedHadFullPassL/O");




    //Now trees for specific channels;

    //Leptonic variables;
    float lepZ1LeadPtFullPassL;
    float lepZ1TrailingPtFullPassL;
    float lepZ1LeadPhiFullPassL;
    float lepZ1TrailingPhiFullPassL;
    float lepZ1PairInvMassFullPassL;
    float lepZ1LeadEtaFullPassL;
    float lepZ1TrailingEtaFullPassL;
    bool lepZ1IsElectronFullPassL;
    bool lepZ1IsMuonFullPassL;
    float lepZ1LeadIsoFullPassL;
    float lepZ1TrailingIsoFullPassL;
    float lepZ1LeadSIPFullPassL;
    float lepZ1TrailingSIPFullPassL;

    float lepZ2LeadPtFullPassL;
    float lepZ2TrailingPtFullPassL;
    float lepZ2LeadPhiFullPassL;
    float lepZ2TrailingPhiFullPassL;
    float lepZ2PairInvMassFullPassL;
    float lepZ2LeadEtaFullPassL;
    float lepZ2TrailingEtaFullPassL;
    bool lepZ2IsElectronFullPassL;
    bool lepZ2IsMuonFullPassL;
    float lepZ2LeadIsoFullPassL;
    float lepZ2TrailingIsoFullPassL;
    float lepZ2LeadSIPFullPassL;
    float lepZ2TrailingSIPFullPassL;

    float lepChanHiggsFatJet_pt_fromHTagFullPassL;
    float lepChanHiggsFatJet_phi_fromHTagFullPassL;
    float lepChanHiggsFatJet_eta_fromHTagFullPassL;
    float lepChanHiggsFatJet_mass_fromHTagFullPassL;
    float lepChanHiggsFatJet_HTag_fromHTagFullPassL;

    //Leptonic tree;
    TTree *LepTree = new TTree("LepTree", "LepTree");

    LepTree->Branch("lepZ1LeadPtFullPassL",&lepZ1LeadPtFullPassL,"lepZ1LeadPtFullPassL/F");
    LepTree->Branch("lepZ1TrailingPtFullPassL",&lepZ1TrailingPtFullPassL,"lepZ1TrailingPtFullPassL/F");
    LepTree->Branch("lepZ1LeadPhiFullPassL",&lepZ1LeadPhiFullPassL,"lepZ1LeadPhiFullPassL/F");
    LepTree->Branch("lepZ1TrailingPhiFullPassL",&lepZ1TrailingPhiFullPassL,"lepZ1TrailingPhiFullPassL/F");
    LepTree->Branch("lepZ1PairInvMassFullPassL",&lepZ1PairInvMassFullPassL,"lepZ1PairInvMassFullPassL/F");
    LepTree->Branch("lepZ1LeadEtaFullPassL",&lepZ1LeadEtaFullPassL,"lepZ1LeadEtaFullPassL/F");
    LepTree->Branch("lepZ1TrailingEtaFullPassL",&lepZ1TrailingEtaFullPassL,"lepZ1TrailingEtaFullPassL/F");
    LepTree->Branch("lepZ1IsElectronFullPassL",&lepZ1IsElectronFullPassL,"lepZ1IsElectronFullPassL/O");
    LepTree->Branch("lepZ1IsMuonFullPassL",&lepZ1IsMuonFullPassL,"lepZ1IsMuonFullPassL/O");
    LepTree->Branch("lepZ1LeadIsoFullPassL",&lepZ1LeadIsoFullPassL,"lepZ1LeadIsoFullPassL/F");
    LepTree->Branch("lepZ1TrailingIsoFullPassL",&lepZ1TrailingIsoFullPassL,"lepZ1TrailingIsoFullPassL/F");
    LepTree->Branch("lepZ1LeadSIPFullPassL",&lepZ1LeadSIPFullPassL,"lepZ1LeadSIPFullPassL/F");
    LepTree->Branch("lepZ1TrailingSIPFullPassL",&lepZ1TrailingSIPFullPassL,"lepZ1TrailingSIPFullPassL/F");

    LepTree->Branch("lepZ2LeadPtFullPassL",&lepZ2LeadPtFullPassL,"lepZ2LeadPtFullPassL/F");
    LepTree->Branch("lepZ2TrailingPtFullPassL",&lepZ2TrailingPtFullPassL,"lepZ2TrailingPtFullPassL/F");
    LepTree->Branch("lepZ2LeadPhiFullPassL",&lepZ2LeadPhiFullPassL,"lepZ2LeadPhiFullPassL/F");
    LepTree->Branch("lepZ2TrailingPhiFullPassL",&lepZ2TrailingPhiFullPassL,"lepZ2TrailingPhiFullPassL/F");
    LepTree->Branch("lepZ2PairInvMassFullPassL",&lepZ2PairInvMassFullPassL,"lepZ2PairInvMassFullPassL/F");
    LepTree->Branch("lepZ2LeadEtaFullPassL",&lepZ2LeadEtaFullPassL,"lepZ2LeadEtaFullPassL/F");
    LepTree->Branch("lepZ2TrailingEtaFullPassL",&lepZ2TrailingEtaFullPassL,"lepZ2TrailingEtaFullPassL/F");
    LepTree->Branch("lepZ2IsElectronFullPassL",&lepZ2IsElectronFullPassL,"lepZ2IsElectronFullPassL/O");
    LepTree->Branch("lepZ2IsMuonFullPassL",&lepZ2IsMuonFullPassL,"lepZ2IsMuonFullPassL/O");
    LepTree->Branch("lepZ2LeadIsoFullPassL",&lepZ2LeadIsoFullPassL,"lepZ2LeadIsoFullPassL/F");
    LepTree->Branch("lepZ2TrailingIsoFullPassL",&lepZ2TrailingIsoFullPassL,"lepZ2TrailingIsoFullPassL/F");
    LepTree->Branch("lepZ2LeadSIPFullPassL",&lepZ2LeadSIPFullPassL,"lepZ2LeadSIPFullPassL/F");
    LepTree->Branch("lepZ2TrailingSIPFullPassL",&lepZ2TrailingSIPFullPassL,"lepZ2TrailingSIPFullPassL/F");

    LepTree->Branch("lepChanHiggsFatJet_pt_fromHTagFullPassL",&lepChanHiggsFatJet_pt_fromHTagFullPassL,"lepChanHiggsFatJet_pt_fromHTagFullPassL/F");
    LepTree->Branch("lepChanHiggsFatJet_phi_fromHTagFullPassL",&lepChanHiggsFatJet_phi_fromHTagFullPassL,"lepChanHiggsFatJet_phi_fromHTagFullPassL/F");
    LepTree->Branch("lepChanHiggsFatJet_eta_fromHTagFullPassL",&lepChanHiggsFatJet_eta_fromHTagFullPassL,"lepChanHiggsFatJet_eta_fromHTagFullPassL/F");
    LepTree->Branch("lepChanHiggsFatJet_mass_fromHTagFullPassL",&lepChanHiggsFatJet_mass_fromHTagFullPassL,"lepChanHiggsFatJet_mass_fromHTagFullPassL/F");
    LepTree->Branch("lepChanHiggsFatJet_HTag_fromHTagFullPassL",&lepChanHiggsFatJet_HTag_fromHTagFullPassL,"lepChanHiggsFatJet_HTag_fromHTagFullPassL/F");


    //SemiLeptonic variables;
    float lepLeadPtFullPassL;
    float lepTrailingPtFullPassL;
    float lepLeadPhiFullPassL;
    float lepTrailingPhiFullPassL;
    float lepPairInvMassFullPassL;
    float lepLeadEtaFullPassL;
    float lepTrailingEtaFullPassL;
    float lepLeadIsoFullPassL;
    float lepTrailingIsoFullPassL;
    float lepLeadSIPFullPassL;
    float lepTrailingSIPFullPassL;
    bool lepIsElectronFullPassL;
    bool lepIsMuonFullPassL;


    float FJPtFullPassL;
    float FJPhiFullPassL;
    float FJMassFullPassL;
    float FJEtaFullPassL;


    float semiLepChanHiggsFatJet_pt_fromHTagFullPassL;
    float semiLepChanHiggsFatJet_phi_fromHTagFullPassL;
    float semiLepChanHiggsFatJet_eta_fromHTagFullPassL;
    float semiLepChanHiggsFatJet_mass_fromHTagFullPassL;
    float semiLepChanHiggsFatJet_HTag_fromHTagFullPassL;

    //SemiLeptonic tree;
    TTree *SemiLepTree = new TTree("SemiLepTree", "SemiLepTree");

    SemiLepTree->Branch("lepLeadPtFullPassL",&lepLeadPtFullPassL,"lepLeadPtFullPassL/F");
    SemiLepTree->Branch("lepTrailingPtFullPassL",&lepTrailingPtFullPassL,"lepTrailingPtFullPassL/F");
    SemiLepTree->Branch("lepLeadPhiFullPassL",&lepLeadPhiFullPassL,"lepLeadPhiFullPassL/F");
    SemiLepTree->Branch("lepTrailingPhiFullPassL",&lepTrailingPhiFullPassL,"lepTrailingPhiFullPassL/F");
    SemiLepTree->Branch("lepPairInvMassFullPassL",&lepPairInvMassFullPassL,"lepPairInvMassFullPassL/F");
    SemiLepTree->Branch("lepLeadEtaFullPassL",&lepLeadEtaFullPassL,"lepLeadEtaFullPassL/F");
    SemiLepTree->Branch("lepTrailingEtaFullPassL",&lepTrailingEtaFullPassL,"lepTrailingEtaFullPassL/F");
    SemiLepTree->Branch("lepIsElectronFullPassL",&lepIsElectronFullPassL,"lepIsElectronFullPassL/O");
    SemiLepTree->Branch("lepIsMuonFullPassL",&lepIsMuonFullPassL,"lepIsMuonFullPassL/O");
    SemiLepTree->Branch("lepLeadIsoFullPassL",&lepLeadIsoFullPassL,"lepLeadIsoFullPassL/F");
    SemiLepTree->Branch("lepTrailingIsoFullPassL",&lepTrailingIsoFullPassL,"lepTrailingIsoFullPassL/F");
    SemiLepTree->Branch("lepLeadSIPFullPassL",&lepLeadSIPFullPassL,"lepLeadSIPFullPassL/F");
    SemiLepTree->Branch("lepTrailingSIPFullPassL",&lepTrailingSIPFullPassL,"lepTrailingSIPFullPassL/F");
    

    SemiLepTree->Branch("FJPtFullPassL",&FJPtFullPassL,"FJPtFullPassL/F");
    SemiLepTree->Branch("FJPhiFullPassL",&FJPhiFullPassL,"FJPhiFullPassL/F");
    SemiLepTree->Branch("FJMassFullPassL",&FJMassFullPassL,"FJMassFullPassL/F");
    SemiLepTree->Branch("FJEtaFullPassL",&FJEtaFullPassL,"FJEtaFullPassL/F");


    SemiLepTree->Branch("semiLepChanHiggsFatJet_pt_fromHTagFullPassL",&semiLepChanHiggsFatJet_pt_fromHTagFullPassL,"semiLepChanHiggsFatJet_pt_fromHTagFullPassL/F");
    SemiLepTree->Branch("semiLepChanHiggsFatJet_phi_fromHTagFullPassL",&semiLepChanHiggsFatJet_phi_fromHTagFullPassL,"semiLepChanHiggsFatJet_phi_fromHTagFullPassL/F");
    SemiLepTree->Branch("semiLepChanHiggsFatJet_eta_fromHTagFullPassL",&semiLepChanHiggsFatJet_eta_fromHTagFullPassL,"semiLepChanHiggsFatJet_eta_fromHTagFullPassL/F");
    SemiLepTree->Branch("semiLepChanHiggsFatJet_mass_fromHTagFullPassL",&semiLepChanHiggsFatJet_mass_fromHTagFullPassL,"semiLepChanHiggsFatJet_mass_fromHTagFullPassL/F");
    SemiLepTree->Branch("semiLepChanHiggsFatJet_HTag_fromHTagFullPassL",&semiLepChanHiggsFatJet_HTag_fromHTagFullPassL,"semiLepChanHiggsFatJet_HTag_fromHTagFullPassL/F");


    //Hadronic variables;
    float FJLeadPtFullPassL;
    float FJTrailingPtFullPassL;
    float FJLeadPhiFullPassL;
    float FJTrailingPhiFullPassL;
    float FJLeadMassFullPassL;
    float FJTrailingMassFullPassL;
    float FJPairInvMassFullPassL;
    float FJLeadEtaFullPassL;
    float FJTrailingEtaFullPassL;
    float FJEtaSepFullPassL;

    float hadChanHiggsFatJet_pt_fromHTagFullPassL;
    float hadChanHiggsFatJet_phi_fromHTagFullPassL;
    float hadChanHiggsFatJet_eta_fromHTagFullPassL;
    float hadChanHiggsFatJet_mass_fromHTagFullPassL;
    float hadChanHiggsFatJet_HTag_fromHTagFullPassL;

    //Hadronic tree;
    TTree *HadTree = new TTree("HadTree", "HadTree");

    HadTree->Branch("FJLeadPtFullPassL",&FJLeadPtFullPassL,"FJLeadPtFullPassL/F");
    HadTree->Branch("FJTrailingPtFullPassL",&FJTrailingPtFullPassL,"FJTrailingPtFullPassL/F");
    HadTree->Branch("FJLeadPhiFullPassL",&FJLeadPhiFullPassL,"FJLeadPhiFullPassL/F");
    HadTree->Branch("FJTrailingPhiFullPassL",&FJTrailingPhiFullPassL,"FJTrailingPhiFullPassL/F");
    HadTree->Branch("FJLeadMassFullPassL",&FJLeadMassFullPassL,"FJLeadMassFullPassL/F");
    HadTree->Branch("FJTrailingMassFullPassL",&FJTrailingMassFullPassL,"FJTrailingMassFullPassL/F");
    HadTree->Branch("FJPairInvMassFullPassL",&FJPairInvMassFullPassL,"FJPairInvMassFullPassL/F");
    HadTree->Branch("FJLeadEtaFullPassL",&FJLeadEtaFullPassL,"FJLeadEtaFullPassL/F");
    HadTree->Branch("FJTrailingEtaFullPassL",&FJTrailingEtaFullPassL,"FJTrailingEtaFullPassL/F");
    HadTree->Branch("FJEtaSepFullPassL",&FJEtaSepFullPassL,"FJEtaSepFullPassL/F");


    HadTree->Branch("hadChanHiggsFatJet_pt_fromHTagFullPassL",&hadChanHiggsFatJet_pt_fromHTagFullPassL,"hadChanHiggsFatJet_pt_fromHTagFullPassL/F");
    HadTree->Branch("hadChanHiggsFatJet_phi_fromHTagFullPassL",&hadChanHiggsFatJet_phi_fromHTagFullPassL,"hadChanHiggsFatJet_phi_fromHTagFullPassL/F");
    HadTree->Branch("hadChanHiggsFatJet_eta_fromHTagFullPassL",&hadChanHiggsFatJet_eta_fromHTagFullPassL,"hadChanHiggsFatJet_eta_fromHTagFullPassL/F");
    HadTree->Branch("hadChanHiggsFatJet_mass_fromHTagFullPassL",&hadChanHiggsFatJet_mass_fromHTagFullPassL,"hadChanHiggsFatJet_mass_fromHTagFullPassL/F");
    HadTree->Branch("hadChanHiggsFatJet_HTag_fromHTagFullPassL",&hadChanHiggsFatJet_HTag_fromHTagFullPassL,"hadChanHiggsFatJet_HTag_fromHTagFullPassL/F");


    
    std::cout << "Going into file loop.\n";

    for (UInt_t k=0; k<fileAr.size(); k++){
        if (endAfter && evCount > NToEnd) break;
        if (debug) std::cout<<"File:    "<<fileAr[k]<<"\n";
        //Open the file, get the Events tree
        TFile* tmpfile = TFile::Open(fileAr[k].c_str());
        //outFile->cd();
        TTreeReader myEventsReader("FilteredEventsTree", tmpfile);
        //jets

        TTreeReaderValue<UInt_t> nJetL(myEventsReader, "nJet");
        TTreeReaderArray<Float_t> Jet_etaL(myEventsReader, "Jet_eta");
        TTreeReaderArray<Float_t> Jet_ptL(myEventsReader, "Jet_pt");
        TTreeReaderArray<Float_t> Jet_phiL(myEventsReader, "Jet_phi");
        TTreeReaderArray<Float_t> Jet_massL(myEventsReader, "Jet_mass");
        TTreeReaderArray<Int_t> Jet_jetIdL(myEventsReader, "Jet_jetId");

        //Fat jets

        TTreeReaderValue<UInt_t> nFatJetL(myEventsReader, "nFatJet");
        TTreeReaderArray<Float_t> FatJet_etaL(myEventsReader, "FatJet_eta");
        TTreeReaderArray<Float_t> FatJet_ptL(myEventsReader, "FatJet_pt");
        TTreeReaderArray<Float_t> FatJet_phiL(myEventsReader, "FatJet_phi");
        TTreeReaderArray<Float_t> FatJet_massL(myEventsReader, "FatJet_mass");
        TTreeReaderArray<Int_t> FatJet_jetIdL(myEventsReader, "FatJet_jetId");
        TTreeReaderArray<Float_t> FatJet_deepTag_HL(myEventsReader, "FatJet_deepTag_H");
        TTreeReaderArray<Float_t> FatJet_deepTag_ZvsQCDL(myEventsReader, "FatJet_deepTag_ZvsQCD");

        //Gen part stuff

        TTreeReaderValue<UInt_t> nGenPartL(myEventsReader, "nGenPart");
        TTreeReaderArray<Float_t> GenPart_etaL(myEventsReader, "GenPart_eta");
        TTreeReaderArray<Float_t> GenPart_massL(myEventsReader, "GenPart_mass");
        TTreeReaderArray<Float_t> GenPart_phiL(myEventsReader, "GenPart_phi");
        TTreeReaderArray<Float_t> GenPart_ptL(myEventsReader, "GenPart_pt");
        TTreeReaderArray<Int_t> GenPart_genPartIdxMotherL(myEventsReader, "GenPart_genPartIdxMother");
        TTreeReaderArray<Int_t> GenPart_pdgIdL(myEventsReader, "GenPart_pdgId");
        TTreeReaderArray<Int_t> GenPart_statusL(myEventsReader, "GenPart_status");
        TTreeReaderArray<Int_t> GenPart_statusFlagsL(myEventsReader, "GenPart_statusFlags");
        
        //Electrons
        TTreeReaderValue<UInt_t> nElectronL(myEventsReader, "nElectron");
        TTreeReaderArray<Float_t> Electron_etaL(myEventsReader, "Electron_eta");
        TTreeReaderArray<Float_t> Electron_massL(myEventsReader, "Electron_mass");
        TTreeReaderArray<Int_t> Electron_chargeL(myEventsReader, "Electron_charge");
        TTreeReaderArray<Float_t> Electron_phiL(myEventsReader, "Electron_phi");
        TTreeReaderArray<Float_t> Electron_ptL(myEventsReader, "Electron_pt");
        TTreeReaderArray<Float_t> Electron_dr03EcalRecHitSumEtL(myEventsReader, "Electron_dr03EcalRecHitSumEt");
        TTreeReaderArray<Float_t> Electron_dr03TkSumPtL(myEventsReader, "Electron_dr03TkSumPt");
        TTreeReaderArray<Float_t> Electron_dr03HcalDepth1TowerSumEtL(myEventsReader, "Electron_dr03HcalDepth1TowerSumEt");
        TTreeReaderArray<Float_t> Electron_pfRelIso03_allL(myEventsReader, "Electron_pfRelIso03_all");
        TTreeReaderArray<Float_t> Electron_sip3dL(myEventsReader, "Electron_sip3d");

        //Muons
        TTreeReaderValue<UInt_t> nMuonL(myEventsReader, "nMuon");
        TTreeReaderArray<Float_t> Muon_etaL(myEventsReader, "Muon_eta");
        TTreeReaderArray<Float_t> Muon_massL(myEventsReader, "Muon_mass");
        TTreeReaderArray<Int_t> Muon_chargeL(myEventsReader, "Muon_charge");
        TTreeReaderArray<Float_t> Muon_phiL(myEventsReader, "Muon_phi");
        TTreeReaderArray<Float_t> Muon_ptL(myEventsReader, "Muon_pt");
        TTreeReaderArray<Float_t> Muon_pfRelIso03_allL(myEventsReader, "Muon_pfRelIso03_all");
        TTreeReaderArray<Float_t> Muon_sip3dL(myEventsReader, "Muon_sip3d");

        Int_t tmpPDGId;


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
            for (UInt_t rangeItr=0; rangeItr<cutAmnt+1; rangeItr++){
                float tmphFatJetPTCutVal = cutRangeAr[rangeItr];
                
                
                elecCandIndAr.clear();
                muonCandIndAr.clear();

                eZ2VecPairAr.clear();
                mZ2VecPairAr.clear();


                bool passesCutsBool = false;
                bool passedAsLepBool = false;
                bool passedAsSemiLepBool = false;
                bool passedAsHadBool = false;
                

                //Now fat jets
                UInt_t nFatJetLen = *nFatJetL;
                
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

                //doHiggsFatJetCut(nFatJetLen,hFatJet_HTag_fromPt,hFatJet_pt_fromPt,hFatJet_phi_fromPt,hFatJet_eta_fromPt,hFatJet_mass_fromPt,hFatJet_pt_fromHTag,hFatJet_phi_fromHTag,hFatJet_eta_fromHTag,hFatJet_mass_fromHTag,hFatJet_HTag_fromHTag,hFatJet_ind_fromHTag,FatJet_deepTag_HL,hFatJetDeepTagCut,FatJet_ptL,hFatJetPTCut,FatJet_jetIdL,FatJet_phiL,FatJet_etaL,jetLeadPhi,jetLeadEta,jetTrailingPhi,jetTrailingEta,hFatJetdRCut,FatJet_massL);
                
                doHiggsFatJetCut(nFatJetLen,hFatJet_pt_fromHTag,hFatJet_phi_fromHTag,hFatJet_eta_fromHTag,hFatJet_mass_fromHTag,hFatJet_HTag_fromHTag,hFatJet_ind_fromHTag,FatJet_deepTag_HL,hFatJetDeepTagCut,FatJet_ptL,tmphFatJetPTCutVal,FatJet_jetIdL,FatJet_phiL,FatJet_etaL,FatJet_massL,selectedFJ_phi,selectedFJ_eta);
                
                if (hFatJet_pt_fromHTag == 0) continue;
                if (debug) std::cout << " found fat jet\n";
                passFatJets += 1;


                UInt_t neLep = *nElectronL;
                UInt_t nmLep = *nMuonL;
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

                if (debug) cout << "trying Leptonic\n";
                tryingLepCtr += 1;
                    
                    
                    
                doLeptonicCuts(Electron_etaL,Electron_massL,Electron_chargeL,Electron_phiL,Electron_ptL, neLep, elecCandIndAr, elecCandVecAr, elecCandChargeAr,negElecCands,posElecCands,totElecCands,enoughElecCands,negMuonCands,posMuonCands,totMuonCands,enoughMuonCands,enoughLepCands,ePtCut,eEtaCut,
                Muon_etaL,Muon_massL, Muon_chargeL,Muon_phiL,Muon_ptL, nmLep, muonCandIndAr, muonCandVecAr, muonCandChargeAr,mPtCut,mEtaCut,
                Z1IsMuon,invMassCutLow,invMassCutHigh,ptLeadCut,ptTrailingCut,
                Z1LeadPt,Z1TrailingPt,Z1LeadItr,Z1TrailingItr,Z1LeadVec,Z1TrailingVec,Z1LeadCharge,Z1TrailingCharge,difFromZMassOne,
                eZ2VecPairAr,tmpZ2Ind,Z2IsMuon,tmpTopZ2LeadPt,tmpTopZ2TrailingPt,fourLepInvMassCut,optLepInvMassCut,
                mZ2VecPairAr,
                tmpZ1Vec,tmpZ1M,
                Electron_dr03EcalRecHitSumEtL,Electron_dr03TkSumPtL,Electron_dr03HcalDepth1TowerSumEtL,Electron_pfRelIso03_allL,
                Z1LeadIso,Muon_pfRelIso03_allL,Z1TrailingIso,Z2LeadIso,Z2TrailingIso,lepIsoCut,
                Z1LeadSIP,Electron_sip3dL,Z1TrailingSIP,Z2LeadSIP,Muon_sip3dL,Z2TrailingSIP,passLepCut,passesCutsBool,passedAsLepBool,
                debug);

                Int_t FJInd;
                if (debug) std::cout << "passesCutsBool " << passesCutsBool << "\n";
                if ((!passesCutsBool)){
                    if (debug) std::cout << "trying SemiLeptonic\n";
                    tryingSemiLepCtr += 1;
                    FJInd = -1;
                    UInt_t numFatJet = *nFatJetL;
                    doSemiLepChanFatJetCut(FJInd,numFatJet,hFatJet_ind_fromHTag,fatJetPTCut,fatJetZTagCut,FatJet_ptL,FatJet_phiL,FatJet_etaL,FatJet_deepTag_ZvsQCDL,selectedFJ_phi,selectedFJ_eta);
                    /*
                    for (UInt_t i=0; i<*nFatJet;i++){
                        tmpFatJetPT = FatJet_ptL[i];
                        if (tmpFatJetPT > fatJetPTCut) FJInd = i;
                    }
                    */
                    doSemiLepCut(FJInd,enoughElecCands,negElecCands,posElecCands,totElecCands,Electron_etaL,Electron_massL,Electron_chargeL,Electron_phiL,Electron_ptL,neLep,elecCandIndAr,elecCandVecAr,elecCandChargeAr,ePtCut,eEtaCut,
                     enoughMuonCands,negMuonCands,posMuonCands,totMuonCands,Muon_etaL,Muon_massL,Muon_chargeL,Muon_phiL,Muon_ptL,nmLep,muonCandIndAr,muonCandVecAr,muonCandChargeAr,mPtCut,mEtaCut,
                     enoughLepCands,Z1Cand,difFromZMassOne,Z1LeadItr,Z1TrailingItr,Z1LeadPt,Z1TrailingPt,Z1IsMuon,Z1LeadVec,Z1TrailingVec,Z1LeadCharge,Z1TrailingCharge,
                     Electron_dr03EcalRecHitSumEtL,Electron_dr03TkSumPtL,Electron_dr03HcalDepth1TowerSumEtL,Electron_pfRelIso03_allL,
                     Z1LeadIso,Muon_pfRelIso03_allL,Z1TrailingIso,
                     passSemiLepCut,passesCutsBool,passedAsSemiLepBool,
                     debug);
                }
                if (debug) std::cout << "Test\n";
                if ((!passesCutsBool)){
                    tryingHadCtr += 1;
                    LFJOneInd = -1;
                    LFJTwoInd = -1;
                    if (debugHadronic) std::cout << "---------------- Event " << evCount - 1 << " ----------------\n";
                    //if (debugHadronic) std::cout << "hFatJet_ind_fromHTag " << hFatJet_ind_fromHTag << "\n";
                    if (debugHadronic) std::cout << "fatJetPTCut " << fatJetPTCut << "\n";

                    if (debugHadronic) std::cout << "--------- Entering FJ loop for Hadronic Channel ---------\n";

                    UInt_t numFatJet = *nFatJetL;
                    doHadChanFatJetCut(LFJOneInd,LFJTwoInd,numFatJet,hFatJet_ind_fromHTag,fatJetPTCut,fatJetZPairInvMassCut,FatJet_ptL,FatJet_phiL,FatJet_etaL,FatJet_massL,FatJet_deepTag_ZvsQCDL,selectedFJ_phi,selectedFJ_eta,hFatJet_pt_fromHTag);

                    
                    if (LFJOneInd != LFJTwoInd){
                        passHadCut += 1;
                        passesCutsBool = true;
                        passedAsHadBool = true;
                    }
                }
                if ((!passesCutsBool)) continue;
                else passChannelCtr += 1;


                //Now match VBF jets
                UInt_t nJetLen        = *nJetL;
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
                doVBFJetCut(nJetLen,Jet_ptL,Jet_jetIdL,Jet_etaL,Jet_phiL,Jet_massL,jetPTCut,jetEtaDifCut,jetInvMassCut,jetPairInvMass,jetLeadPt,jetLeadEta,jetLeadPhi,jetTrailingPt,jetTrailingEta,jetTrailingPhi,leadJet_1,leadJet_2,selectedFJ_phi,selectedFJ_eta,VBFJetdRCut,debug);
                //std::cout << jetLeadPt << endl;
                if (jetLeadPt == 0) continue;
                debugOutputForVBFJetCut(evCount,leadJet_1,leadJet_2,Jet_phiL,Jet_etaL,debug);
                /*
                if (debug){
                    std::cout << " found jet pairs\n";
                    std::cout << evCount+1 << " selected jet pair\n";
                    std::cout << "Lead jet ind    " << leadJet_1 << "\n";
                    std::cout << "Trailing jet ind    " << leadJet_2 << "\n";
                    std::cout << "Lead jet phi    " << Jet_phi[leadJet_1] << "\n";
                    std::cout << "Trailing jet phi    " << Jet_phi[leadJet_2] << "\n";
                    std::cout << "Lead jet eta    " << Jet_etaL[leadJet_1] << "\n";
                    std::cout << "Trailing jet eta    " << Jet_etaL[leadJet_2] << "\n";
                }
                */
                passVBFJets += 1;

                if (passesCutsBool){
                    cutPassAr[rangeItr] += 1;
                    /*
                    if (debug) std::cout << "Passed cuts. Now filling trees\n";
                    passesCutsCtr += 1;
                    //Fill tree
                    if (debug) std::cout << "Filling jets\n";
                    nJetFullPassL = *nJetL;
                    jetLeadPtFullPassL = jetLeadPt;
                    jetTrailingPtFullPassL = jetTrailingPt;
                    jetLeadPhiFullPassL = jetLeadPhi;
                    jetTrailingPhiFullPassL = jetTrailingPhi;
                    jetPairInvMassFullPassL = jetPairInvMass;
                    jetLeadEtaFullPassL = jetLeadEta;
                    jetTrailingEtaFullPassL = jetTrailingEta;
                    //now fat jets
                    if (debug) std::cout << "Filling fat jets\n";
                    nFatJetFullPassL = *nFatJetL;
                    hFatJet_pt_fromHTagFullPassL = hFatJet_pt_fromHTag;
                    hFatJet_phi_fromHTagFullPassL = hFatJet_phi_fromHTag;
                    hFatJet_eta_fromHTagFullPassL = hFatJet_eta_fromHTag;
                    hFatJet_mass_fromHTagFullPassL = hFatJet_mass_fromHTag;
                    hFatJet_HTag_fromHTagFullPassL = hFatJet_HTag_fromHTag;
                    

                    //Branches for distinguishing between channels
                    
                    passedLepFullPassL = passedAsLepBool ;
                    passedSemiLepFullPassL = passedAsSemiLepBool;
                    passedHadFullPassL = passedAsHadBool;

                    FATree->Fill();



                    if (debug) std::cout << "Filling channel branches \n";
                    evPassCount += 1;
                    ROOT::Math::PtEtaPhiMVector tmpZ2LeadVec;
                    ROOT::Math::PtEtaPhiMVector tmpZ2TrailingVec;
                    ROOT::Math::PtEtaPhiMVector tmpZ2Vec;
                    */

                }

            }

        }
    }
    if (debug) std::cout << "Filling complete \n";

    clock_t endt = clock();
    double time_spent = (double)(endt - startt) / CLOCKS_PER_SEC;


    std::cout << "Finished file loop. " << "time: " << time_spent << "\n";
    for (UInt_t rangeItr=0; rangeItr<cutAmnt+1; rangeItr++){
        std::cout << "cutRangeAr[rangeItr] " << cutRangeAr[rangeItr] << " cutPassAr[rangeItr] " << cutPassAr[rangeItr] << "\n";
    }

    /*
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
    std::cout << "passes Higgs FatJet cut: " << passFatJets << "\n";
    std::cout << "passes actual channel cut: " << passChannelCtr << "\n";
    std::cout << "passes in lep channel: " << passLepCut << "\n";
    std::cout << "passes in semi lep channel: " << passSemiLepCut << "\n";
    std::cout << "passes in had channel: " << passHadCut << "\n";
    std::cout << "passes VBF Jet cut: " << passVBFJets << " -------------------\n";
    

    std::cout << "passes all cuts: " << passesCutsCtr << " -------------------\n";
    std::cout << "evPassCount: " << evPassCount << "\n";

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

    outFile->Close();
    */
}