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


void DoHLTFilterBeforeAnalysis(UInt_t fileInd){
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

    if (MGC2VEtaDifCut){
        saveName = "C2VEtaDifCut";
        isBackground = false;
        int arrSize = sizeof(MGC2VEtaDifCutAr)/sizeof(MGC2VEtaDifCutAr[0]);
        std::string tmpStrWithPath = strAdd+"/dlutton/NanoAODFiles/pphzzjj_C2V_QCD0SMHLOOP0NPLE1C2VE1KappaFramework_100Ev_3p0c2V_100GeVIMJetCut_2EtaDifCut/"+MGC2VEtaDifCutAr[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = strAdd+"/dlutton/NanoAODFiles/pphzzjj_C2V_QCD0SMHLOOP0NPLE1C2VE1KappaFramework_100Ev_3p0c2V_100GeVIMJetCut_2EtaDifCut/"+MGC2VEtaDifCutAr[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
    }
    else if (SDC2V3MC){
        saveName = "SDC2V3MC";
        isBackground = false;
        int arrSize = sizeof(SDC2V3MCAr)/sizeof(SDC2V3MCAr[0]);
        std::string tmpStrWithPath = SDC2V3MCAr[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V3MCAr[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (MGOSix){
        saveName = "OSix";
        isBackground = false;
        int arrSize = sizeof(MGOSixAr)/sizeof(MGOSixAr[0]);
        std::string tmpStrWithPath = strAdd+"/dlutton/NanoAODFiles/pphzzjj_OSix_QCD0SMHLOOP0NPLE1NPcHE1_100Ev_0p4cH_100GeVIMJetCut/"+MGOSixAr[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = strAdd+"/dlutton/NanoAODFiles/pphzzjj_OSix_QCD0SMHLOOP0NPLE1NPcHE1_100Ev_0p4cH_100GeVIMJetCut/"+MGOSixAr[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
    }
    else if (MGOSixEtaDifCut){
        saveName = "OSix_EtaDifCut";
        isBackground = false;
        int arrSize = sizeof(MGOSixEtaDifCutAr)/sizeof(MGOSixEtaDifCutAr[0]);
        std::string tmpStrWithPath = strAdd+"/dlutton/NanoAODFiles/pphzzjj_OSix_QCD0SMHLOOP0NPLE1NPcHE1_100Ev_0p4cH_100GeVIMJetCut_2EtaDifCut/"+MGOSixEtaDifCutAr[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = strAdd+"/dlutton/NanoAODFiles/pphzzjj_OSix_QCD0SMHLOOP0NPLE1NPcHE1_100Ev_0p4cH_100GeVIMJetCut_2EtaDifCut/"+MGOSixEtaDifCutAr[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
    }
    else if (MGOHBox){
        saveName = "OHBox";
        isBackground = false;
        int arrSize = sizeof(MGOHBoxAr)/sizeof(MGOHBoxAr[0]);
        std::string tmpStrWithPath = strAdd+"/dlutton/NanoAODFiles/pphzzjj_OHBox_QCD0SMHLOOP0NPLE1NPcHBoxE1_100Ev_0p5cHBox_100GeVIMJetCut/"+MGOHBoxAr[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = strAdd+"/dlutton/NanoAODFiles/pphzzjj_OHBox_QCD0SMHLOOP0NPLE1NPcHBoxE1_100Ev_0p5cHBox_100GeVIMJetCut/"+MGOHBoxAr[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (MGOHBoxEtaDifCut){
        saveName = "OHBox_EtaDifCut";
        isBackground = false;
        int arrSize = sizeof(MGOHBoxEtaDifCutAr)/sizeof(MGOHBoxEtaDifCutAr[0]);
        std::string tmpStrWithPath = strAdd+"/dlutton/NanoAODFiles/pphzzjj_OHBox_QCD0SMHLOOP0NPLE1NPcHBoxE1_100Ev_0p5cHBox_100GeVIMJetCut_2EtaDifCut/"+MGOHBoxEtaDifCutAr[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = strAdd+"/dlutton/NanoAODFiles/pphzzjj_OHBox_QCD0SMHLOOP0NPLE1NPcHBoxE1_100Ev_0p5cHBox_100GeVIMJetCut_2EtaDifCut/"+MGOHBoxEtaDifCutAr[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (MGOHDD){
        saveName = "OHDD";
        isBackground = false;
        int arrSize = sizeof(MGOHDDAr)/sizeof(MGOHDDAr[0]);
        std::string tmpStrWithPath = strAdd+"/dlutton/NanoAODFiles/pphzzjj_OHDD_QCD0SMHLOOP0NPLE1NPcHDDE1_0p6cHDD_100GeVIMJetCut/"+MGOHDDAr[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = strAdd+"/dlutton/NanoAODFiles/pphzzjj_OHDD_QCD0SMHLOOP0NPLE1NPcHDDE1_0p6cHDD_100GeVIMJetCut/"+MGOHDDAr[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (MGOHDDEtaDifCut){
        saveName = "OHDD_EtaDifCut";
        isBackground = false;
        int arrSize = sizeof(MGOHDDEtaDifCutAr)/sizeof(MGOHDDEtaDifCutAr[0]);
        std::string tmpStrWithPath = strAdd+"/dlutton/NanoAODFiles/pphzzjj_OHDD_QCD0SMHLOOP0NPLE1NPcHDDE1_0p6cHDD_100GeVIMJetCut_2EtaDifCut/"+MGOHDDEtaDifCutAr[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = strAdd+"/dlutton/NanoAODFiles/pphzzjj_OHDD_QCD0SMHLOOP0NPLE1NPcHDDE1_0p6cHDD_100GeVIMJetCut_2EtaDifCut/"+MGOHDDEtaDifCutAr[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (MGOHW){
        saveName = "OHW";
        isBackground = false;
        int arrSize = sizeof(MGOHWAr)/sizeof(MGOHWAr[0]);
        std::string tmpStrWithPath = strAdd+"/dlutton/NanoAODFiles/pphzzjjQCD0SMHLOOP0NPE1NPcHWE1QEDE5/"+MGOHWAr[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = strAdd+"/dlutton/NanoAODFiles/pphzzjjQCD0SMHLOOP0NPE1NPcHWE1QEDE5/"+MGOHWAr[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (MGSM){
        saveName = "SM";
        isBackground = false;
        int arrSize = sizeof(MGSMAr)/sizeof(MGSMAr[0]);
        std::string tmpStrWithPath = strAdd+"/dlutton/NanoAODFiles/pphzzjjQCD0SMHLOOP0QEDE5NPE0/"+MGSMAr[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = strAdd+"/dlutton/NanoAODFiles/pphzzjjQCD0SMHLOOP0QEDE5NPE0/"+MGSMAr[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (ttHToBBBackground){
        //saveName = "ttHToBB";
        crossSection = 0.5071*0.582;

        saveName = "ttHToBB";
        
        isBackground = true;
        int arrSize = sizeof(ttHToBBBackgroundAr)/sizeof(ttHToBBBackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(ttHToBBBackgroundAr[i]);
        }
        */
        fileAr.push_back(ttHToBBBackgroundAr[fileInd]);
    }
    else if (ttZJetsBackground){
        //saveName = "ttZJets";
        
        crossSection = 0.5407;
        saveName = "ttZJets";
        isBackground = true;
        int arrSize = sizeof(ttZJetsBackgroundAr)/sizeof(ttZJetsBackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(ttZJetsBackgroundAr[i]);
        }
        */
        fileAr.push_back(ttZJetsBackgroundAr[fileInd]);
    }
    else if (DYBackground){
        //saveName = "DY";
        
        crossSection = 5364;
        saveName = "DY";

        isBackground = true;
        int arrSize = sizeof(DYBackgroundAr)/sizeof(DYBackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(DYBackgroundAr[i]);
        }
        */
        fileAr.push_back(DYBackgroundAr[fileInd]);
    }
    else if (QCDPT170to300Background){
        //saveName = "QCDPT170to300";
        
        crossSection = 103300.0;

        saveName = "QCDPT170to300";
        
        isBackground = true;
        int arrSize = sizeof(QCDPT170to300BackgroundAr)/sizeof(QCDPT170to300BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(QCDPT170to300BackgroundAr[i]);
        }
        */
        fileAr.push_back(QCDPT170to300BackgroundAr[fileInd]);
    }
    else if (QCDPT300to470Background){
        //saveName = "QCDPT300to470";
        
        crossSection = 6826.0;

        saveName = "QCDPT300to470";
        
        isBackground = true;
        int arrSize = sizeof(QCDPT300to470BackgroundAr)/sizeof(QCDPT300to470BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(QCDPT300to470BackgroundAr[i]);
        }
        */
        fileAr.push_back(QCDPT300to470BackgroundAr[fileInd]);
    }
    else if (QCDPT470to600Background){
        //saveName = "QCDPT470to600";
        
        crossSection = 552.6;
        
        saveName = "QCDPT470to600";

        isBackground = true;
        int arrSize = sizeof(QCDPT470to600BackgroundAr)/sizeof(QCDPT470to600BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(QCDPT470to600BackgroundAr[i]);
        }
        */
        fileAr.push_back(QCDPT470to600BackgroundAr[fileInd]);
    }
    else if (QCDPT600to800Background){
        //saveName = "QCDPT600to800";
        
        crossSection = 156.6;

        saveName = "QCDPT600to800";
        
        isBackground = true;
        int arrSize = sizeof(QCDPT600to800BackgroundAr)/sizeof(QCDPT600to800BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(QCDPT600to800BackgroundAr[i]);
        }
        */
        fileAr.push_back(QCDPT600to800BackgroundAr[fileInd]);
    }
    else if (QCDPT800to1000Background){
        //saveName = "QCDPT800to1000";
        
        crossSection = 26.32;

        saveName = "QCDPT800to1000";
        
        isBackground = true;
        int arrSize = sizeof(QCDPT800to1000BackgroundAr)/sizeof(QCDPT800to1000BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(QCDPT800to1000BackgroundAr[i]);
        }
        */
        fileAr.push_back(QCDPT800to1000BackgroundAr[fileInd]);
    }
    else if (QCDPT1000to1400Background){
        //saveName = "QCDPT1000to1400";
        
        crossSection = 7.5;

        saveName = "QCDPT1000to1400";
        
        isBackground = true;
        int arrSize = sizeof(QCDPT1000to1400BackgroundAr)/sizeof(QCDPT1000to1400BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(QCDPT1000to1400BackgroundAr[i]);
        }
        */
        fileAr.push_back(QCDPT1000to1400BackgroundAr[fileInd]);
    }
    else if (QCDPT1400to1800Background){
        //saveName = "QCDPT1400to1800";
        
        crossSection = 0.6479;

        saveName = "QCDPT1400to1800";
        
        isBackground = true;
        int arrSize = sizeof(QCDPT1400to1800BackgroundAr)/sizeof(QCDPT1400to1800BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(QCDPT1400to1800BackgroundAr[i]);
        }
        */
        fileAr.push_back(QCDPT1400to1800BackgroundAr[fileInd]);
    }
    else if (QCDPT1800to2400Background){
        //saveName = "QCDPT1800to2400";
        
        crossSection = 0.08715;

        saveName = "QCDPT1800to2400";
        
        isBackground = true;
        int arrSize = sizeof(QCDPT1800to2400BackgroundAr)/sizeof(QCDPT1800to2400BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(QCDPT1800to2400BackgroundAr[i]);
        }
        */
        fileAr.push_back(QCDPT1800to2400BackgroundAr[fileInd]);
    }
    else if (QCDPT2400to3200Background){
        //saveName = "QCDPT2400to3200";
        
        crossSection = 0.005242;

        saveName = "QCDPT2400to3200";
        
        isBackground = true;
        int arrSize = sizeof(QCDPT2400to3200BackgroundAr)/sizeof(QCDPT2400to3200BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(QCDPT2400to3200BackgroundAr[i]);
        }
        */
        fileAr.push_back(QCDPT2400to3200BackgroundAr[fileInd]);
    }
    else if (QCDPT3200toInfBackground){
        //saveName = "QCDPT3200toInf";
        
        crossSection = 0.0001349;

        saveName = "QCDPT3200toInf";
        
        isBackground = true;
        int arrSize = sizeof(QCDPT3200toInfBackgroundAr)/sizeof(QCDPT3200toInfBackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(QCDPT3200toInfBackgroundAr[i]);
        }
        */
        fileAr.push_back(QCDPT3200toInfBackgroundAr[fileInd]);
    }
    else if (TTToHadronicBackground){
        //saveName = "QCDPT3200toInf";
        
        crossSection = 377.96;

        saveName = "TTToHadronic";
        
        isBackground = true;
        int arrSize = sizeof(TTToHadronicBackgroundAr)/sizeof(TTToHadronicBackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(TTToHadronicBackgroundAr[i]);
        }
        */
        fileAr.push_back(TTToHadronicBackgroundAr[fileInd]);
    }
    else if (TTJetsBackground){
        //saveName = "";
        
        crossSection = 722.8;

        saveName = "TTJets";
        
        isBackground = true;
        int arrSize = sizeof(TTJetsBackgroundAr)/sizeof(TTJetsBackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(TTJetsBackgroundAr[i]);
        }
        */
        fileAr.push_back(TTJetsBackgroundAr[fileInd]);
    }
    else if (TTTo2L2NuBackground){
        //saveName = "";
        
        crossSection = 88.29;

        saveName = "TTTo2L2Nu";
        
        isBackground = true;
        int arrSize = sizeof(TTTo2L2NuBackgroundAr)/sizeof(TTTo2L2NuBackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(TTTo2L2NuBackgroundAr[i]);
        }
        */
        fileAr.push_back(TTTo2L2NuBackgroundAr[fileInd]);
    }
    else if (ST_s_ChannelBackground){
        //saveName = "";
        
        crossSection = 3.74;

        saveName = "ST_s_Channel";
        
        isBackground = true;
        int arrSize = sizeof(ST_s_ChannelBackgroundAr)/sizeof(ST_s_ChannelBackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(ST_s_ChannelBackgroundAr[i]);
        }
        */
        fileAr.push_back(ST_s_ChannelBackgroundAr[fileInd]);
    }
    else if (ST_t_ChannelAntiTopBackground){
        //saveName = "";
        
        crossSection = 69.09;

        saveName = "ST_t_ChannelAntiTop";
        
        isBackground = true;
        int arrSize = sizeof(ST_t_ChannelAntiTopBackgroundAr)/sizeof(ST_t_ChannelAntiTopBackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(ST_t_ChannelAntiTopBackgroundAr[i]);
        }
        */
        fileAr.push_back(ST_t_ChannelAntiTopBackgroundAr[fileInd]);
    }
    else if (ST_t_ChannelTopBackground){
        //saveName = "";
        
        crossSection = 115.3;

        saveName = "ST_t_ChannelTop";
        
        isBackground = true;
        int arrSize = sizeof(ST_t_ChannelTopBackgroundAr)/sizeof(ST_t_ChannelTopBackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(ST_t_ChannelTopBackgroundAr[i]);
        }
        */
        fileAr.push_back(ST_t_ChannelTopBackgroundAr[fileInd]);
    }
    else if (ZZTo2Q2NuBackground){
        //saveName = "";
        
        crossSection = 4.561;

        saveName = "ZZTo2Q2Nu";
        
        isBackground = true;
        int arrSize = sizeof(ZZTo2Q2NuBackgroundAr)/sizeof(ZZTo2Q2NuBackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(ZZTo2Q2NuBackgroundAr[i]);
        }
        */
        fileAr.push_back(ZZTo2Q2NuBackgroundAr[fileInd]);
    }
    else if (WWTo2L2NuBackground){
        //saveName = "";
        
        crossSection = 10.48;

        saveName = "WWTo2L2Nu";
        
        isBackground = true;
        int arrSize = sizeof(WWTo2L2NuBackgroundAr)/sizeof(WWTo2L2NuBackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(WWTo2L2NuBackgroundAr[i]);
        }
        */
        fileAr.push_back(WWTo2L2NuBackgroundAr[fileInd]);
    }
    else if (WZTo3LNuBackground){
        //saveName = "";
        
        crossSection = 5.052;

        saveName = "WZTo3LNu";
        
        isBackground = true;
        int arrSize = sizeof(WZTo3LNuBackgroundAr)/sizeof(WZTo3LNuBackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(WZTo3LNuBackgroundAr[i]);
        }
        */
        fileAr.push_back(WZTo3LNuBackgroundAr[fileInd]);
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
    std::string outFileStr = "HLTFilteredForAnalysis"+saveName+"_"+std::to_string(fileInd)+".root";
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
    Double_t passHLTWeightedCtr = 0;
    UInt_t passnFJCtr = 0;
    Double_t passnFJWeightedCtr = 0;
    UInt_t passnVBFCtr = 0;
    Double_t passnVBFWeightedCtr = 0;

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

    //
    Float_t fixedGridRhoFastjetAllL;

    //genChannel characterization
    //0=Leptonic,1=Semi-leptonic,2=Hadronic,3=Other,4=Error
    UInt_t genChannelL;

    Bool_t HTobbBoolL;


    TTree *FilteredEventsTree = new TTree("FilteredEventsTree", "FilteredEventsTree");
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

    //
    FilteredEventsTree->Branch("fixedGridRhoFastjetAllL",&fixedGridRhoFastjetAllL);

    //genChannel characterization
    //0=Leptonic,1=Semi-leptonic,2=Hadronic,3=Other,4=Error
    FilteredEventsTree->Branch("genChannelL",&genChannelL,"genChannelL/i");

    FilteredEventsTree->Branch("HTobbBoolL",&HTobbBoolL,"HTobbBoolL/O");
    

    Double_t sumOfGenWeights = 0;

    UInt_t genLepChannelCtr = 0;
    UInt_t genSemiLepChannelCtr = 0;
    UInt_t genHadronicChannelCtr = 0;
    UInt_t genOtherChannelCtr = 0;
    UInt_t genErrorChannelCtr = 0;

    Double_t genLepChannelWeightedCtr = 0;
    Double_t genSemiLepChannelWeightedCtr = 0;
    Double_t genHadronicChannelWeightedCtr = 0;
    Double_t genOtherChannelWeightedCtr = 0;
    Double_t genErrorChannelWeightedCtr = 0;


    UInt_t HTobbCtr = 0;
    Double_t HTobbWeightedCtr = 0;

    
    
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

        //genWeights
        TTreeReaderValue<Float_t> genWeight(myEventsReader, "genWeight");

        //LHE stuff
        TTreeReaderValue<UInt_t> nLHEPart(myEventsReader, "nLHEPart");
        TTreeReaderArray<Int_t> LHEPart_pdgId(myEventsReader, "LHEPart_pdgId");
        TTreeReaderArray<Float_t> LHEPart_pt(myEventsReader, "LHEPart_pt");

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

        //

        TTreeReaderValue<Float_t> fixedGridRhoFastjetAll(myEventsReader, "fixedGridRhoFastjetAll");



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


            //--------------KINEMATICS--------------

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

                bool ZIsLeptonic = false;
                bool ZIsSemiLeptonic = false;
                bool ZIsHadronic = false;

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
                }
                else{
                    if (debugGenPart) std::cout <<"H found\n";
                    if (abs(HFJ_decaypdgId_FromGenMatch[0]) == 5){
                        HTobbBoolL = true;
                        HTobbCtr += 1;
                        HTobbWeightedCtr += *genWeight;
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
                        genErrorChannelCtr += 1;
                        genErrorChannelWeightedCtr += *genWeight;

                    }
                    else{
                        
                        if (ZDecFound) {
                            
                            if (abs(finalZDecAr[0][0])==15 && abs(finalZDecAr[0][1])==15){
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
                                    
                                    std::vector<Int_t> tmpIndAr;
                                    if (!tauOneBool){
                                        for (UInt_t j=0;j<tauOneAr.size();j++){
                                            if (tmpMotherID == tauOneAr[j]){
                                                if (abs(tmpPDGId) == 15) tmpIndAr.push_back(i);
                                                else if (abs(tmpPDGId) == 13 || abs(tmpPDGId) == 11) {
                                                    tauOneBool = true;
                                                    tauOneDecPDG = abs(tmpPDGId);
                                                }
                                            }
                                        }
                                        if (tmpIndAr.size()) {
                                            for (UInt_t j=0;j<tmpIndAr.size();j++){
                                                tauOneAr.push_back(tmpIndAr[j]);
                                            }
                                        }
                                    }
                                    if (!tauTwoBool){
                                        for (UInt_t j=0;j<tauTwoAr.size();j++){
                                            if (tmpMotherID == tauTwoAr[j]){
                                                if (abs(tmpPDGId) == 15) tmpIndAr.push_back(i);
                                                else if (abs(tmpPDGId) == 13 || abs(tmpPDGId) == 11) {
                                                    tauTwoBool = true;
                                                    tauTwoDecPDG = abs(tmpPDGId);
                                                }
                                            }
                                        }
                                        if (tmpIndAr.size()) {
                                            for (UInt_t j=0;j<tmpIndAr.size();j++){
                                                tauTwoAr.push_back(tmpIndAr[j]);
                                            }
                                        }
                                    }
                                }
                                if (tauOneBool && tauTwoBool && tauOneDecPDG == tauTwoDecPDG) {
                                    ZTwoIsLeptonic = true;
                                }
                            }
                            if (abs(finalZDecAr[1][0])==15 && abs(finalZDecAr[1][1])==15){
                                std::vector<Int_t> tauOneAr;
                                std::vector<Int_t> tauTwoAr;
                                bool tauOneBool = false;
                                bool tauTwoBool = false;
                                UInt_t tauOneDecPDG = 0;
                                UInt_t tauTwoDecPDG = 0;
                                tauOneAr.push_back(finalZDecIndAr[1][0]);
                                tauTwoAr.push_back(finalZDecIndAr[1][1]);
                                for (UInt_t i=0;i<*nGenPart;i++){
                                    Int_t tmpPDGId = GenPart_pdgId[i];
                                    Int_t tmpMotherID = GenPart_genPartIdxMother[i];
                                    
                                    std::vector<Int_t> tmpIndAr;
                                    if (!tauOneBool){
                                        for (UInt_t j=0;j<tauOneAr.size();j++){
                                            if (tmpMotherID == tauOneAr[j]){
                                                if (abs(tmpPDGId) == 15) tmpIndAr.push_back(i);
                                                else if (abs(tmpPDGId) == 13 || abs(tmpPDGId) == 11) {
                                                    tauOneBool = true;
                                                    tauOneDecPDG = abs(tmpPDGId);
                                                }
                                            }
                                        }
                                        if (tmpIndAr.size()) {
                                            for (UInt_t j=0;j<tmpIndAr.size();j++){
                                                tauOneAr.push_back(tmpIndAr[j]);
                                            }
                                        }
                                    }
                                    if (!tauTwoBool){
                                        for (UInt_t j=0;j<tauTwoAr.size();j++){
                                            if (tmpMotherID == tauTwoAr[j]){
                                                if (abs(tmpPDGId) == 15) tmpIndAr.push_back(i);
                                                else if (abs(tmpPDGId) == 13 || abs(tmpPDGId) == 11) {
                                                    tauTwoBool = true;
                                                    tauTwoDecPDG = abs(tmpPDGId);
                                                }
                                            }
                                        }
                                        if (tmpIndAr.size()) {
                                            for (UInt_t j=0;j<tmpIndAr.size();j++){
                                                tauTwoAr.push_back(tmpIndAr[j]);
                                            }
                                        }
                                    }
                                }
                                if (tauOneBool && tauTwoBool && tauOneDecPDG == tauTwoDecPDG) {
                                    ZTwoIsLeptonic = true;
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


                            
                        }
                        

                        if (ZIsHadronic) {

                            genChannelL=2;
                            genHadronicChannelCtr += 1;
                            genHadronicChannelWeightedCtr += *genWeight;

                        }

                        else if (ZIsSemiLeptonic) {

                            genChannelL=1;
                            genSemiLepChannelCtr += 1;
                            genSemiLepChannelWeightedCtr += *genWeight;

                        }

                        else if (ZIsLeptonic) {
                            genChannelL=0;
                            genLepChannelCtr += 1;
                            genLepChannelWeightedCtr += *genWeight;

                            

                        }
                        else {
                            genChannelL=3;
                            genOtherChannelCtr += 1;
                            genOtherChannelWeightedCtr += *genWeight;
                        }
                        

                        
                            
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
            bool passHLTBool = (*HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02 || *HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2 || *HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4 || *HLT_PFHT1050 || *HLT_AK8PFJet500 || *HLT_AK8PFJet360_TrimMass30 || *HLT_AK8PFHT750_TrimMass50 || *HLT_AK8PFJet380_TrimMass30 ||
            *HLT_AK8PFJet400_TrimMass30 || *HLT_AK8PFJet420_TrimMass30 || *HLT_AK8PFHT800_TrimMass50 || *HLT_AK8PFHT850_TrimMass50 || *HLT_AK8PFHT900_TrimMass50 ||*HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL || *HLT_DoubleEle25_CaloIdL_MW || *HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ || *HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL ||  *HLT_DiEle27_WPTightCaloOnly_L1DoubleEG || 
            *HLT_DoubleEle33_CaloIdL_MW || *HLT_DoubleEle25_CaloIdL_MW || *HLT_DoubleEle27_CaloIdL_MW || *HLT_DoublePhoton70 || *HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8 || *HLT_TripleMu_10_5_5_DZ || *HLT_TripleMu_12_10_5 || *HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8 || *HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8 || 
            *HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass3p8 || *HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass8 || *HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL || *HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ || *HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ || *HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ || 
            *HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL || *HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL || *HLT_Ele32_WPTight_Gsf || *HLT_Ele115_CaloIdVT_GsfTrkIdT || *HLT_Ele27_WPTight_Gsf || *HLT_Ele28_WPTight_Gsf || 
            *HLT_Ele35_WPTight_Gsf || *HLT_Ele38_WPTight_Gsf || *HLT_Ele40_WPTight_Gsf || *HLT_Ele32_WPTight_Gsf_L1DoubleEG || *HLT_Photon200 || *HLT_IsoMu24 || *HLT_IsoMu27 || *HLT_IsoMu30 || *HLT_Mu50);
            //std::cout << testPassHLTBool << " " << passHLTBool << "\n";
            if (!passHLTBool) continue;
            passHLTCtr += 1;
            passHLTWeightedCtr += *genWeight;
            if (debug){
                std::cout <<"Passed HLT\n";
            }
            

            genWeightL = *genWeight;

            //Check if any fat jets in event
            UInt_t tmpnFatJets = *nFatJet;
            if (tmpnFatJets<=0) continue;
            if (debug){
                std::cout <<"Passed nFJs\n";
            }
            passnFJCtr += 1;
            passnFJWeightedCtr += *genWeight; 

            // check if two or more VBF jets in event
            UInt_t tmpnVBFJets = *nJet;
            
            if (tmpnVBFJets < 2) continue;
            if (debug){
                std::cout <<"Passed nJs\n";
            }

            passnVBFCtr += 1;
            passnVBFWeightedCtr += *genWeight; 
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
    std::cout << "passes HLT cut: " << passHLTCtr << " ------------------- " << passHLTWeightedCtr<< "\n";
    std::cout << "passes nFJ cut: " << passnFJCtr << " ------------------- " << passnFJWeightedCtr<< "\n";
    std::cout << "passes nVBF cut: " << passnVBFCtr << " ------------------- " << passnVBFWeightedCtr<< "\n";

    
    std::cout << "sumOfGenWeights: " << sumOfGenWeights << "\n";

    if (!isBackground){
        std::cout << "Gen Lep Channel: " << genLepChannelCtr << " ------------------- " << genLepChannelWeightedCtr<< "\n";
        std::cout << "Gen SemiLep Channel: " << genSemiLepChannelCtr << " ------------------- " << genSemiLepChannelWeightedCtr<< "\n";
        std::cout << "Gen Hadronic Channel: " << genHadronicChannelCtr << " ------------------- " << genHadronicChannelWeightedCtr<< "\n";
        std::cout << "Gen Other Channel: " << genOtherChannelCtr << " ------------------- " << genOtherChannelWeightedCtr<< "\n";
        std::cout << "Gen Error Channel: " << genErrorChannelCtr << " ------------------- " << genErrorChannelWeightedCtr<< "\n";
        std::cout << "HTobb Channel: " << HTobbCtr << " ------------------- " << HTobbWeightedCtr<< "\n";
        
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

    outFile->Close();
}
