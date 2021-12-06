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
#include "fileListsInC.h"
#include "FullAnalysisInC.h"
#include "FullAnalysisInC_Functions.h"
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


void FullAnalysisInCWithLHE(){
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

    if (MGEFT){
        saveName = "EFT";
        isBackground = false;
        int arrSize = sizeof(MGEFTAr)/sizeof(MGEFTAr[0]);
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = "/scratch365/dlutton/NanoAODFiles/pphzzjjQCD0SMHLOOP0NPE1NPcHWE1QEDE5/"+MGEFTAr[i];
            fileAr.push_back(tmpStrWithPath);
        }
        useLHETree = true;
        useFJGenMatchTree = true;
        useJGenMatchTree = true;
    }
    else if (MGSM){
        saveName = "SM";
        isBackground = false;
        int arrSize = sizeof(MGSMAr)/sizeof(MGSMAr[0]);
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = "/scratch365/dlutton/NanoAODFiles/pphzzjjQCD0SMHLOOP0QEDE5NPE0/"+MGSMAr[i];
            fileAr.push_back(tmpStrWithPath);
        }
        useLHETree = true;
        useFJGenMatchTree = true;
        useJGenMatchTree = true;
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
        useJGenMatchTree = true;
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
    std::string outFileStr = "FullAnalysis"+saveName+".root";
    std::cout << "OutFile: " << outFileStr << "\n";
    TFile *outFile = new TFile(outFileStr.c_str(),"RECREATE");
    bool checkChannelSplits;
    if (isBackground){
        checkChannelSplits = false;
    }

    UInt_t HFJSameJetCtr = 0;

    float HFJ_pt_FromGenMatchL;
    float HFJ_eta_FromGenMatchL;
    float HFJ_phi_FromGenMatchL;
    float HFJ_mass_FromGenMatchL;
    float HFJ_dRFromFJ_FromGenMatchL;



    TTree *HFJGenTree = new TTree("HFJGenTree", "HFJGenTree");

    HFJGenTree->Branch("HFJ_pt_FromGenMatchL",&HFJ_pt_FromGenMatchL,"HFJ_pt_FromGenMatchL/F");
    HFJGenTree->Branch("HFJ_eta_FromGenMatchL",&HFJ_eta_FromGenMatchL,"HFJ_eta_FromGenMatchL/F");
    HFJGenTree->Branch("HFJ_phi_FromGenMatchL",&HFJ_phi_FromGenMatchL,"HFJ_phi_FromGenMatchL/F");
    HFJGenTree->Branch("HFJ_mass_FromGenMatchL",&HFJ_mass_FromGenMatchL,"HFJ_mass_FromGenMatchL/F");
    HFJGenTree->Branch("HFJ_dRFromFJ_FromGenMatchL",&HFJ_dRFromFJ_FromGenMatchL,"HFJ_dRFromFJ_FromGenMatchL/F");


    UInt_t ZFJSameJetCtr = 0;

    float ZFJLead_pt_FromGenMatchL;
    float ZFJLead_eta_FromGenMatchL;
    float ZFJLead_phi_FromGenMatchL;
    float ZFJLead_mass_FromGenMatchL;
    float ZFJLead_dRFromFJ_FromGenMatchL;
    

    float ZFJTrailing_pt_FromGenMatchL;
    float ZFJTrailing_eta_FromGenMatchL;
    float ZFJTrailing_phi_FromGenMatchL;
    float ZFJTrailing_mass_FromGenMatchL;
    float ZFJTrailing_dRFromFJ_FromGenMatchL;

    float ZFJPair_InvMass_FromGenMatchL;
    float ZFJPair_EtaSep_FromGenMatchL;

    TTree *ZFJGenTree = new TTree("ZFJGenTree", "ZFJGenTree");

    ZFJGenTree->Branch("ZFJLead_pt_FromGenMatchL",&ZFJLead_pt_FromGenMatchL,"ZFJLead_pt_FromGenMatchL/F");
    ZFJGenTree->Branch("ZFJLead_eta_FromGenMatchL",&ZFJLead_eta_FromGenMatchL,"ZFJLead_eta_FromGenMatchL/F");
    ZFJGenTree->Branch("ZFJLead_phi_FromGenMatchL",&ZFJLead_phi_FromGenMatchL,"ZFJLead_phi_FromGenMatchL/F");
    ZFJGenTree->Branch("ZFJLead_mass_FromGenMatchL",&ZFJLead_mass_FromGenMatchL,"ZFJLead_mass_FromGenMatchL/F");
    ZFJGenTree->Branch("ZFJLead_dRFromFJ_FromGenMatchL",&ZFJLead_dRFromFJ_FromGenMatchL,"ZFJLead_dRFromFJ_FromGenMatchL/F");

    ZFJGenTree->Branch("ZFJTrailing_pt_FromGenMatchL",&ZFJTrailing_pt_FromGenMatchL,"ZFJTrailing_pt_FromGenMatchL/F");
    ZFJGenTree->Branch("ZFJTrailing_eta_FromGenMatchL",&ZFJTrailing_eta_FromGenMatchL,"ZFJTrailing_eta_FromGenMatchL/F");
    ZFJGenTree->Branch("ZFJTrailing_phi_FromGenMatchL",&ZFJTrailing_phi_FromGenMatchL,"ZFJTrailing_phi_FromGenMatchL/F");
    ZFJGenTree->Branch("ZFJTrailing_mass_FromGenMatchL",&ZFJTrailing_mass_FromGenMatchL,"ZFJTrailing_mass_FromGenMatchL/F");
    ZFJGenTree->Branch("ZFJTrailing_dRFromFJ_FromGenMatchL",&ZFJTrailing_dRFromFJ_FromGenMatchL,"ZFJTrailing_dRFromFJ_FromGenMatchL/F");

    ZFJGenTree->Branch("ZFJPair_InvMass_FromGenMatchL",&ZFJPair_InvMass_FromGenMatchL,"ZFJPair_InvMass_FromGenMatchL/F");
    ZFJGenTree->Branch("ZFJPair_EtaSep_FromGenMatchL",&ZFJPair_EtaSep_FromGenMatchL,"ZFJPair_EtaSep_FromGenMatchL/F");

    float ZHFJ_ZPairPlusHInvMass_FromGenMatchL;
    TTree *ZHFJGenTree = new TTree("ZHFJGenTree", "ZHFJGenTree");
    ZHFJGenTree->Branch("ZHFJ_ZPairPlusHInvMass_FromGenMatchL",&ZHFJ_ZPairPlusHInvMass_FromGenMatchL,"ZHFJ_ZPairPlusHInvMass_FromGenMatchL/F");

    float ZHJ_ZPairPlusHInvMass_FromGenMatchL;
    TTree *ZHJGenTree = new TTree("ZHJGenTree", "ZHJGenTree");
    ZHJGenTree->Branch("ZHJ_ZPairPlusHInvMass_FromGenMatchL",&ZHJ_ZPairPlusHInvMass_FromGenMatchL,"ZHJ_ZPairPlusHInvMass_FromGenMatchL/F");





    UInt_t ZJSameJetCtr = 0;


    float ZJLead_pt_FromGenMatchL;
    float ZJLead_eta_FromGenMatchL;
    float ZJLead_phi_FromGenMatchL;
    float ZJLead_mass_FromGenMatchL;
    float ZJLead_dRFromJ_FromGenMatchL;
    

    float ZJTrailing_pt_FromGenMatchL;
    float ZJTrailing_eta_FromGenMatchL;
    float ZJTrailing_phi_FromGenMatchL;
    float ZJTrailing_mass_FromGenMatchL;
    float ZJTrailing_dRFromJ_FromGenMatchL;

    float ZJPair_InvMass_FromGenMatchL;
    float ZJPair_EtaSep_FromGenMatchL;

    TTree *ZJGenTree = new TTree("ZJGenTree", "ZJGenTree");

    ZJGenTree->Branch("ZJLead_pt_FromGenMatchL",&ZJLead_pt_FromGenMatchL,"ZJLead_pt_FromGenMatchL/F");
    ZJGenTree->Branch("ZJLead_eta_FromGenMatchL",&ZJLead_eta_FromGenMatchL,"ZJLead_eta_FromGenMatchL/F");
    ZJGenTree->Branch("ZJLead_phi_FromGenMatchL",&ZJLead_phi_FromGenMatchL,"ZJLead_phi_FromGenMatchL/F");
    ZJGenTree->Branch("ZJLead_mass_FromGenMatchL",&ZJLead_mass_FromGenMatchL,"ZJLead_mass_FromGenMatchL/F");
    ZJGenTree->Branch("ZJLead_dRFromJ_FromGenMatchL",&ZJLead_dRFromJ_FromGenMatchL,"ZJLead_dRFromJ_FromGenMatchL/F");

    ZJGenTree->Branch("ZJTrailing_pt_FromGenMatchL",&ZJTrailing_pt_FromGenMatchL,"ZJTrailing_pt_FromGenMatchL/F");
    ZJGenTree->Branch("ZJTrailing_eta_FromGenMatchL",&ZJTrailing_eta_FromGenMatchL,"ZJTrailing_eta_FromGenMatchL/F");
    ZJGenTree->Branch("ZJTrailing_phi_FromGenMatchL",&ZJTrailing_phi_FromGenMatchL,"ZJTrailing_phi_FromGenMatchL/F");
    ZJGenTree->Branch("ZJTrailing_mass_FromGenMatchL",&ZJTrailing_mass_FromGenMatchL,"ZJTrailing_mass_FromGenMatchL/F");
    ZJGenTree->Branch("ZJTrailing_dRFromJ_FromGenMatchL",&ZJTrailing_dRFromJ_FromGenMatchL,"ZJTrailing_dRFromJ_FromGenMatchL/F");

    ZJGenTree->Branch("ZJPair_InvMass_FromGenMatchL",&ZJPair_InvMass_FromGenMatchL,"ZJPair_InvMass_FromGenMatchL/F");
    ZJGenTree->Branch("ZJPair_EtaSep_FromGenMatchL",&ZJPair_EtaSep_FromGenMatchL,"ZJPair_EtaSep_FromGenMatchL/F");





    //This tree is for gen variables before the cuts
    //Can only use this on EFT and SM, not background


    float ZOne_pt_FromGenRawL;
    float ZOne_eta_FromGenRawL;
    float ZOne_phi_FromGenRawL;
    float ZOne_mass_FromGenRawL;
    float ZOne_pdgId_FromGenRawL;
    float ZOne_genPartIdxMother_FromGenRawL;

    float ZTwo_pt_FromGenRawL;
    float ZTwo_eta_FromGenRawL;
    float ZTwo_phi_FromGenRawL;
    float ZTwo_mass_FromGenRawL;
    float ZTwo_pdgId_FromGenRawL;
    float ZTwo_genPartIdxMother_FromGenRawL;

    float ZPair_InvMass_FromGenRawL;
    float ZPair_EtaSep_FromGenRawL;

    float H_pt_FromGenRawL;
    float H_eta_FromGenRawL;
    float H_phi_FromGenRawL;
    float H_mass_FromGenRawL;
    float H_pdgId_FromGenRawL;
    float H_genPartIdxMother_FromGenRawL;

    float ZPairPlusH_InvMass_FromGenRawL;

    TTree *GenRawTree = new TTree("GenRawTree", "GenRawTree");

    GenRawTree->Branch("ZOne_pt_FromGenRawL",&ZOne_pt_FromGenRawL,"ZOne_pt_FromGenRawL/F");
    GenRawTree->Branch("ZOne_eta_FromGenRawL",&ZOne_eta_FromGenRawL,"ZOne_eta_FromGenRawL/F");
    GenRawTree->Branch("ZOne_phi_FromGenRawL",&ZOne_phi_FromGenRawL,"ZOne_phi_FromGenRawL/F");
    GenRawTree->Branch("ZOne_mass_FromGenRawL",&ZOne_mass_FromGenRawL,"ZOne_mass_FromGenRawL/F");
    GenRawTree->Branch("ZOne_pdgId_FromGenRawL",&ZOne_pdgId_FromGenRawL,"ZOne_pdgId_FromGenRawL/F");
    GenRawTree->Branch("ZOne_genPartIdxMother_FromGenRawL",&ZOne_genPartIdxMother_FromGenRawL,"ZOne_genPartIdxMother_FromGenRawL/F");

    GenRawTree->Branch("ZTwo_pt_FromGenRawL",&ZTwo_pt_FromGenRawL,"ZTwo_pt_FromGenRawL/F");
    GenRawTree->Branch("ZTwo_eta_FromGenRawL",&ZTwo_eta_FromGenRawL,"ZTwo_eta_FromGenRawL/F");
    GenRawTree->Branch("ZTwo_phi_FromGenRawL",&ZTwo_phi_FromGenRawL,"ZTwo_phi_FromGenRawL/F");
    GenRawTree->Branch("ZTwo_mass_FromGenRawL",&ZTwo_mass_FromGenRawL,"ZTwo_mass_FromGenRawL/F");
    GenRawTree->Branch("ZTwo_pdgId_FromGenRawL",&ZTwo_pdgId_FromGenRawL,"ZTwo_pdgId_FromGenRawL/F");
    GenRawTree->Branch("ZTwo_genPartIdxMother_FromGenRawL",&ZTwo_genPartIdxMother_FromGenRawL,"ZTwo_genPartIdxMother_FromGenRawL/F");

    GenRawTree->Branch("ZPair_InvMass_FromGenRawL",&ZPair_InvMass_FromGenRawL,"ZPair_InvMass_FromGenRawL/F");
    GenRawTree->Branch("ZPair_EtaSep_FromGenRawL",&ZPair_EtaSep_FromGenRawL,"ZPair_EtaSep_FromGenRawL/F");

    GenRawTree->Branch("H_pt_FromGenRawL",&H_pt_FromGenRawL,"H_pt_FromGenRawL/F");
    GenRawTree->Branch("H_eta_FromGenRawL",&H_eta_FromGenRawL,"H_eta_FromGenRawL/F");
    GenRawTree->Branch("H_phi_FromGenRawL",&H_phi_FromGenRawL,"H_phi_FromGenRawL/F");
    GenRawTree->Branch("H_mass_FromGenRawL",&H_mass_FromGenRawL,"H_mass_FromGenRawL/F");
    GenRawTree->Branch("H_pdgId_FromGenRawL",&H_pdgId_FromGenRawL,"H_pdgId_FromGenRawL/F");
    GenRawTree->Branch("H_genPartIdxMother_FromGenRawL",&H_genPartIdxMother_FromGenRawL,"H_genPartIdxMother_FromGenRawL/F");

    GenRawTree->Branch("ZPairPlusH_InvMass_FromGenRawL",&ZPairPlusH_InvMass_FromGenRawL,"ZPairPlusH_InvMass_FromGenRawL/F");



    //This tree is for variables before the cuts
    //Can only use this on EFT and SM, not background


    float ZOne_pt_FromLHERawL;
    float ZOne_eta_FromLHERawL;
    float ZOne_phi_FromLHERawL;
    float ZOne_mass_FromLHERawL;
    

    float ZTwo_pt_FromLHERawL;
    float ZTwo_eta_FromLHERawL;
    float ZTwo_phi_FromLHERawL;
    float ZTwo_mass_FromLHERawL;

    float ZPair_InvMass_FromLHERawL;
    float ZPair_EtaSep_FromLHERawL;

    float H_pt_FromLHERawL;
    float H_eta_FromLHERawL;
    float H_phi_FromLHERawL;
    float H_mass_FromLHERawL;

    float ZPairPlusH_InvMass_FromLHERawL;

    float JOne_pt_FromLHERawL;
    float JOne_eta_FromLHERawL;
    float JOne_phi_FromLHERawL;
    float JOne_pdgId_FromLHERawL;

    float JTwo_pt_FromLHERawL;
    float JTwo_eta_FromLHERawL;
    float JTwo_phi_FromLHERawL;
    float JTwo_pdgId_FromLHERawL;

    float JOne_invmass_FromLHERawL;
    float JTwo_invmass_FromLHERawL;

    
    

    float JPair_invmass_FromLHERawL;
    float J_etasep_FromLHERawL;

    TTree *RawTree = new TTree("RawTree", "RawTree");

    RawTree->Branch("ZOne_pt_FromLHERawL",&ZOne_pt_FromLHERawL,"ZOne_pt_FromLHERawL/F");
    RawTree->Branch("ZOne_eta_FromLHERawL",&ZOne_eta_FromLHERawL,"ZOne_eta_FromLHERawL/F");
    RawTree->Branch("ZOne_phi_FromLHERawL",&ZOne_phi_FromLHERawL,"ZOne_phi_FromLHERawL/F");
    RawTree->Branch("ZOne_mass_FromLHERawL",&ZOne_mass_FromLHERawL,"ZOne_mass_FromLHERawL/F");

    RawTree->Branch("ZTwo_pt_FromLHERawL",&ZTwo_pt_FromLHERawL,"ZTwo_pt_FromLHERawL/F");
    RawTree->Branch("ZTwo_eta_FromLHERawL",&ZTwo_eta_FromLHERawL,"ZTwo_eta_FromLHERawL/F");
    RawTree->Branch("ZTwo_phi_FromLHERawL",&ZTwo_phi_FromLHERawL,"ZTwo_phi_FromLHERawL/F");
    RawTree->Branch("ZTwo_mass_FromLHERawL",&ZTwo_mass_FromLHERawL,"ZTwo_mass_FromLHERawL/F");

    RawTree->Branch("ZPair_InvMass_FromLHERawL",&ZPair_InvMass_FromLHERawL,"ZPair_InvMass_FromLHERawL/F");
    RawTree->Branch("ZPair_EtaSep_FromLHERawL",&ZPair_EtaSep_FromLHERawL,"ZPair_EtaSep_FromLHERawL/F");

    RawTree->Branch("H_pt_FromLHERawL",&H_pt_FromLHERawL,"H_pt_FromLHERawL/F");
    RawTree->Branch("H_eta_FromLHERawL",&H_eta_FromLHERawL,"H_eta_FromLHERawL/F");
    RawTree->Branch("H_phi_FromLHERawL",&H_phi_FromLHERawL,"H_phi_FromLHERawL/F");
    RawTree->Branch("H_mass_FromLHERawL",&H_mass_FromLHERawL,"H_mass_FromLHERawL/F");

    RawTree->Branch("ZPairPlusH_InvMass_FromLHERawL",&ZPairPlusH_InvMass_FromLHERawL,"ZPairPlusH_InvMass_FromLHERawL/F");

    RawTree->Branch("JOne_pt_FromLHERawL",&JOne_pt_FromLHERawL,"JOne_pt_FromLHERawL/F");
    RawTree->Branch("JOne_eta_FromLHERawL",&JOne_eta_FromLHERawL,"JOne_eta_FromLHERawL/F");
    RawTree->Branch("JOne_phi_FromLHERawL",&JOne_phi_FromLHERawL,"JOne_phi_FromLHERawL/F");
    RawTree->Branch("JOne_invmass_FromLHERawL",&JOne_invmass_FromLHERawL,"JOne_invmass_FromLHERawL/F");
    RawTree->Branch("JOne_pdgId_FromLHERawL",&JOne_pdgId_FromLHERawL,"JOne_pdgId_FromLHERawL/F");

    RawTree->Branch("JTwo_pt_FromLHERawL",&JTwo_pt_FromLHERawL,"JTwo_pt_FromLHERawL/F");
    RawTree->Branch("JTwo_eta_FromLHERawL",&JTwo_eta_FromLHERawL,"JTwo_eta_FromLHERawL/F");
    RawTree->Branch("JTwo_phi_FromLHERawL",&JTwo_phi_FromLHERawL,"JTwo_phi_FromLHERawL/F");
    RawTree->Branch("JTwo_invmass_FromLHERawL",&JTwo_invmass_FromLHERawL,"JTwo_invmass_FromLHERawL/F");
    RawTree->Branch("JTwo_pdgId_FromLHERawL",&JTwo_pdgId_FromLHERawL,"JTwo_pdgId_FromLHERawL/F");

    

    RawTree->Branch("JPair_invmass_FromLHERawL",&JPair_invmass_FromLHERawL,"JPair_invmass_FromLHERawL/F");
    RawTree->Branch("J_etasep_FromLHERawL",&J_etasep_FromLHERawL,"J_etasep_FromLHERawL/F");




    UInt_t passhbbCtr = 0;
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

    float hFatJet_pt_fromPtL;
    float hFatJet_phi_fromPtL;
    float hFatJet_eta_fromPtL;
    float hFatJet_mass_fromPtL;
    float hFatJet_HTag_fromPtL;
    float hFatJet_pt_fromHTagL;
    float hFatJet_phi_fromHTagL;
    float hFatJet_eta_fromHTagL;
    float hFatJet_mass_fromHTagL;
    float hFatJet_HTag_fromHTagL;

    //Now GenPart

    UInt_t nGenPartL;
    float hGenPartDR_fromPtL;
    float hGenPartInd_fromPtL;
    float hGenPartpdgId_fromPtL;
    Int_t hGenPartFirstMompdgId_fromPtL;
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

    FATree->Branch("hFatJet_pt_fromPtL",&hFatJet_pt_fromPtL,"hFatJet_pt_fromPtL/F");
    FATree->Branch("hFatJet_phi_fromPtL",&hFatJet_phi_fromPtL,"hFatJet_phi_fromPtL/F");
    FATree->Branch("hFatJet_eta_fromPtL",&hFatJet_eta_fromPtL,"hFatJet_eta_fromPtL/F");
    FATree->Branch("hFatJet_mass_fromPtL",&hFatJet_mass_fromPtL,"hFatJet_mass_fromPtL/F");
    FATree->Branch("hFatJet_HTag_fromPtL",&hFatJet_HTag_fromPtL,"hFatJet_HTag_fromPtL/F");
    FATree->Branch("hFatJet_pt_fromHTagL",&hFatJet_pt_fromHTagL,"hFatJet_pt_fromHTagL/F");
    FATree->Branch("hFatJet_phi_fromHTagL",&hFatJet_phi_fromHTagL,"hFatJet_phi_fromHTagL/F");
    FATree->Branch("hFatJet_eta_fromHTagL",&hFatJet_eta_fromHTagL,"hFatJet_eta_fromHTagL/F");
    FATree->Branch("hFatJet_mass_fromHTagL",&hFatJet_mass_fromHTagL,"hFatJet_mass_fromHTagL/F");
    FATree->Branch("hFatJet_HTag_fromHTagL",&hFatJet_HTag_fromHTagL,"hFatJet_HTag_fromHTagL/F");

    //now genpart
    FATree->Branch("nGenPartL",&nGenPartL,"nGenPartL/i");
    FATree->Branch("hGenPartDR_fromPtL",&hGenPartDR_fromPtL,"hGenPartDR_fromPtL/F");
    FATree->Branch("hGenPartInd_fromPtL",&hGenPartInd_fromPtL,"hGenPartInd_fromPtL/F");
    FATree->Branch("hGenPartpdgId_fromPtL",&hGenPartpdgId_fromPtL,"hGenPartpdgId_fromPtL/F");
    FATree->Branch("hGenPartFirstMompdgId_fromPtL",&hGenPartFirstMompdgId_fromPtL,"hGenPartFirstMompdgId_fromPtL/I");
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


    //This tree is for variables before the cuts
    //Can only use this on EFT and SM, not background


    float ZOne_pt_FromLHESelectedL;
    float ZOne_eta_FromLHESelectedL;
    float ZOne_phi_FromLHESelectedL;
    float ZOne_mass_FromLHESelectedL;
    

    float ZTwo_pt_FromLHESelectedL;
    float ZTwo_eta_FromLHESelectedL;
    float ZTwo_phi_FromLHESelectedL;
    float ZTwo_mass_FromLHESelectedL;

    float ZPair_InvMass_FromLHESelectedL;
    float ZPair_EtaSep_FromLHESelectedL;

    float H_pt_FromLHESelectedL;
    float H_eta_FromLHESelectedL;
    float H_phi_FromLHESelectedL;
    float H_mass_FromLHESelectedL;

    float ZPairPlusH_InvMass_FromLHESelectedL;

    float JOne_pt_FromLHESelectedL;
    float JOne_eta_FromLHESelectedL;
    float JOne_phi_FromLHESelectedL;
    float JOne_invmass_FromLHESelectedL;
    float JOne_pdgId_FromLHESelectedL;

    float JTwo_pt_FromLHESelectedL;
    float JTwo_eta_FromLHESelectedL;
    float JTwo_phi_FromLHESelectedL;
    float JTwo_invmass_FromLHESelectedL;
    float JTwo_pdgId_FromLHESelectedL;
    
    float JPair_invmass_FromLHESelectedL;

    float J_etasep_FromLHESelectedL;

    TTree *SelectedTree = new TTree("SelectedTree", "SelectedTree");

    SelectedTree->Branch("ZOne_pt_FromLHESelectedL",&ZOne_pt_FromLHESelectedL,"ZOne_pt_FromLHESelectedL/F");
    SelectedTree->Branch("ZOne_eta_FromLHESelectedL",&ZOne_eta_FromLHESelectedL,"ZOne_eta_FromLHESelectedL/F");
    SelectedTree->Branch("ZOne_phi_FromLHESelectedL",&ZOne_phi_FromLHESelectedL,"ZOne_phi_FromLHESelectedL/F");
    SelectedTree->Branch("ZOne_mass_FromLHESelectedL",&ZOne_mass_FromLHESelectedL,"ZOne_mass_FromLHESelectedL/F");

    SelectedTree->Branch("ZTwo_pt_FromLHESelectedL",&ZTwo_pt_FromLHESelectedL,"ZTwo_pt_FromLHESelectedL/F");
    SelectedTree->Branch("ZTwo_eta_FromLHESelectedL",&ZTwo_eta_FromLHESelectedL,"ZTwo_eta_FromLHESelectedL/F");
    SelectedTree->Branch("ZTwo_phi_FromLHESelectedL",&ZTwo_phi_FromLHESelectedL,"ZTwo_phi_FromLHESelectedL/F");
    SelectedTree->Branch("ZTwo_mass_FromLHESelectedL",&ZTwo_mass_FromLHESelectedL,"ZTwo_mass_FromLHESelectedL/F");

    SelectedTree->Branch("ZPair_InvMass_FromLHESelectedL",&ZPair_InvMass_FromLHESelectedL,"ZPair_InvMass_FromLHESelectedL/F");
    SelectedTree->Branch("ZPair_EtaSep_FromLHESelectedL",&ZPair_EtaSep_FromLHESelectedL,"ZPair_EtaSep_FromLHESelectedL/F");

    SelectedTree->Branch("H_pt_FromLHESelectedL",&H_pt_FromLHESelectedL,"H_pt_FromLHESelectedL/F");
    SelectedTree->Branch("H_eta_FromLHESelectedL",&H_eta_FromLHESelectedL,"H_eta_FromLHESelectedL/F");
    SelectedTree->Branch("H_phi_FromLHESelectedL",&H_phi_FromLHESelectedL,"H_phi_FromLHESelectedL/F");
    SelectedTree->Branch("H_mass_FromLHESelectedL",&H_mass_FromLHESelectedL,"H_mass_FromLHESelectedL/F");

    SelectedTree->Branch("ZPairPlusH_InvMass_FromLHESelectedL",&ZPairPlusH_InvMass_FromLHESelectedL,"ZPairPlusH_InvMass_FromLHESelectedL/F");

    SelectedTree->Branch("JOne_pt_FromLHESelectedL",&JOne_pt_FromLHESelectedL,"JOne_pt_FromLHESelectedL/F");
    SelectedTree->Branch("JOne_eta_FromLHESelectedL",&JOne_eta_FromLHESelectedL,"JOne_eta_FromLHESelectedL/F");
    SelectedTree->Branch("JOne_phi_FromLHESelectedL",&JOne_phi_FromLHESelectedL,"JOne_phi_FromLHESelectedL/F");
    SelectedTree->Branch("JOne_invmass_FromLHESelectedL",&JOne_invmass_FromLHESelectedL,"JOne_invmass_FromLHESelectedL/F");
    SelectedTree->Branch("JOne_pdgId_FromLHESelectedL",&JOne_pdgId_FromLHESelectedL,"JOne_pdgId_FromLHESelectedL/F");

    SelectedTree->Branch("JTwo_pt_FromLHESelectedL",&JTwo_pt_FromLHESelectedL,"JTwo_pt_FromLHESelectedL/F");
    SelectedTree->Branch("JTwo_eta_FromLHESelectedL",&JTwo_eta_FromLHESelectedL,"JTwo_eta_FromLHESelectedL/F");
    SelectedTree->Branch("JTwo_phi_FromLHESelectedL",&JTwo_phi_FromLHESelectedL,"JTwo_phi_FromLHESelectedL/F");
    SelectedTree->Branch("JTwo_invmass_FromLHESelectedL",&JTwo_invmass_FromLHESelectedL,"JTwo_invmass_FromLHESelectedL/F");
    SelectedTree->Branch("JTwo_pdgId_FromLHESelectedL",&JTwo_pdgId_FromLHESelectedL,"JTwo_pdgId_FromLHESelectedL/F");


    SelectedTree->Branch("JPair_invmass_FromLHESelectedL",&JPair_invmass_FromLHESelectedL,"JPair_invmass_FromLHESelectedL/F");
    SelectedTree->Branch("J_etasep_FromLHESelectedL",&J_etasep_FromLHESelectedL,"J_etasep_FromLHESelectedL/F");






    
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


            bool passesCutsBool = false;
            bool passedAsLepBool = false;
            bool passedAsSemiLepBool = false;
            bool passedAsHadBool = false;

            //If SM or EFT, get LHE information
            
            if (useLHETree) {
                UInt_t lenLHEPart = *nLHEPart;
                Int_t tmpZCtr = 0;
                Int_t tmpHCtr = 0;
                Int_t tmpJCtr = 0;
                std::vector<UInt_t> tmpZAr;
                Int_t tmpHInd = -1;
                std::vector<UInt_t>tmpJAr;
                tmpPDGId = 0;
                for (UInt_t LHEItr=0; LHEItr<lenLHEPart;LHEItr++){
                    tmpPDGId = LHEPart_pdgId[LHEItr];
                    if (tmpPDGId == 23){
                        tmpZCtr += 1;
                        if (tmpZCtr > 2) std::cout << "ERROR MORE THAN 2 Zs IN LHE\n";
                        else tmpZAr.push_back(LHEItr);
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
                    //LHEFound = true;
                    float tmpLHEPartPtOne = LHEPart_pt[tmpZAr[0]];
                    float tmpLHEPartPtTwo = LHEPart_pt[tmpZAr[1]];
                    
                    if (tmpLHEPartPtOne >= tmpLHEPartPtTwo){
                        ZOne_pt_FromLHERaw = tmpLHEPartPtOne;
                        ZOne_eta_FromLHERaw = LHEPart_eta[tmpZAr[0]];
                        ZOne_phi_FromLHERaw = LHEPart_phi[tmpZAr[0]];
                        ZOne_mass_FromLHERaw = LHEPart_mass[tmpZAr[0]];

                        ZTwo_pt_FromLHERaw = tmpLHEPartPtTwo;
                        ZTwo_eta_FromLHERaw = LHEPart_eta[tmpZAr[1]];
                        ZTwo_phi_FromLHERaw = LHEPart_phi[tmpZAr[1]];
                        ZTwo_mass_FromLHERaw = LHEPart_mass[tmpZAr[1]];
                        
                    }
                    else{
                        ZOne_pt_FromLHERaw = tmpLHEPartPtTwo;
                        ZOne_eta_FromLHERaw = LHEPart_eta[tmpZAr[1]];
                        ZOne_phi_FromLHERaw = LHEPart_phi[tmpZAr[1]];
                        ZOne_mass_FromLHERaw = LHEPart_mass[tmpZAr[1]];

                        ZTwo_pt_FromLHERaw = tmpLHEPartPtOne;
                        ZTwo_eta_FromLHERaw = LHEPart_eta[tmpZAr[0]];
                        ZTwo_phi_FromLHERaw = LHEPart_phi[tmpZAr[0]];
                        ZTwo_mass_FromLHERaw = LHEPart_mass[tmpZAr[0]];
                    }

                    ROOT::Math::PtEtaPhiMVector tmpZOneVec  = ROOT::Math::PtEtaPhiMVector(ZOne_pt_FromLHERaw, ZOne_eta_FromLHERaw, ZOne_phi_FromLHERaw, ZOne_mass_FromLHERaw);
                    ROOT::Math::PtEtaPhiMVector tmpZTwoVec  = ROOT::Math::PtEtaPhiMVector(ZTwo_pt_FromLHERaw, ZTwo_eta_FromLHERaw, ZTwo_phi_FromLHERaw, ZTwo_mass_FromLHERaw);
                    ROOT::Math::PtEtaPhiMVector tmpZPairVec = tmpZOneVec+tmpZTwoVec;
                    ZPair_InvMass_FromLHERaw = tmpZPairVec.M();
                    ZPair_EtaSep_FromLHERaw = abs(ZOne_eta_FromLHERaw-ZTwo_eta_FromLHERaw);
                    

                    

                    H_pt_FromLHERaw = LHEPart_pt[tmpHInd];
                    H_eta_FromLHERaw = LHEPart_eta[tmpHInd];
                    H_phi_FromLHERaw = LHEPart_phi[tmpHInd];
                    H_mass_FromLHERaw = LHEPart_mass[tmpHInd];

                    ROOT::Math::PtEtaPhiMVector tmpHVec  = ROOT::Math::PtEtaPhiMVector(H_pt_FromLHERaw,H_eta_FromLHERaw,H_phi_FromLHERaw,H_mass_FromLHERaw);

                    ROOT::Math::PtEtaPhiMVector tmpZPairPlusHVec = tmpZPairVec+tmpHVec;

                    ZPairPlusH_InvMass_FromLHERaw = tmpZPairPlusHVec.M();

                    tmpLHEPartPtOne = LHEPart_pt[tmpJAr[0]];
                    tmpLHEPartPtTwo = LHEPart_pt[tmpJAr[1]];

                    if (tmpLHEPartPtOne >= tmpLHEPartPtTwo) {
                        JOne_pt_FromLHERaw = tmpLHEPartPtOne;
                        JOne_eta_FromLHERaw = LHEPart_eta[tmpJAr[0]];
                        JOne_pdgId_FromLHERaw = LHEPart_pdgId[tmpJAr[0]];

                        JTwo_pt_FromLHERaw = tmpLHEPartPtTwo;
                        JTwo_eta_FromLHERaw = LHEPart_eta[tmpJAr[1]];
                        JTwo_pdgId_FromLHERaw = LHEPart_pdgId[tmpJAr[1]];

                        JOne_invmass_FromLHERaw = LHEPart_mass[tmpJAr[0]];
                        JTwo_invmass_FromLHERaw = LHEPart_mass[tmpJAr[1]];

                        JOne_phi_FromLHERaw = LHEPart_phi[tmpJAr[0]];
                        JTwo_phi_FromLHERaw = LHEPart_phi[tmpJAr[1]];
                    }
                    else{
                        JOne_pt_FromLHERaw = tmpLHEPartPtTwo;
                        JOne_eta_FromLHERaw = LHEPart_eta[tmpJAr[1]];
                        JOne_pdgId_FromLHERaw = LHEPart_pdgId[tmpJAr[1]];

                        JTwo_pt_FromLHERaw = tmpLHEPartPtOne;
                        JTwo_eta_FromLHERaw = LHEPart_eta[tmpJAr[0]];
                        JTwo_pdgId_FromLHERaw = LHEPart_pdgId[tmpJAr[0]];

                        JOne_invmass_FromLHERaw = LHEPart_mass[tmpJAr[1]];
                        JTwo_invmass_FromLHERaw = LHEPart_mass[tmpJAr[0]];

                        JOne_phi_FromLHERaw = LHEPart_phi[tmpJAr[1]];
                        JTwo_phi_FromLHERaw = LHEPart_phi[tmpJAr[0]];

                    }

                    ROOT::Math::PtEtaPhiMVector tmpJOneVec = ROOT::Math::PtEtaPhiMVector(JOne_pt_FromLHERaw, JOne_eta_FromLHERaw, JOne_phi_FromLHERaw, JOne_invmass_FromLHERaw);
                    ROOT::Math::PtEtaPhiMVector tmpJTwoVec = ROOT::Math::PtEtaPhiMVector(JTwo_pt_FromLHERaw, JTwo_eta_FromLHERaw, JTwo_phi_FromLHERaw, JTwo_invmass_FromLHERaw);
                    ROOT::Math::PtEtaPhiMVector tmpJPairVec = tmpJOneVec + tmpJTwoVec;
                    JPair_invmass_FromLHERaw = tmpJPairVec.M();

                    J_etasep_FromLHERaw = abs(JOne_eta_FromLHERaw-JTwo_eta_FromLHERaw);

                    ZOne_pt_FromLHERawL = ZOne_pt_FromLHERaw;
                    ZOne_eta_FromLHERawL = ZOne_eta_FromLHERaw;
                    ZOne_phi_FromLHERawL = ZOne_phi_FromLHERaw;
                    ZOne_mass_FromLHERawL = ZOne_mass_FromLHERaw;

                    ZTwo_pt_FromLHERawL = ZTwo_pt_FromLHERaw;
                    ZTwo_eta_FromLHERawL = ZTwo_eta_FromLHERaw;
                    ZTwo_phi_FromLHERawL = ZTwo_phi_FromLHERaw;
                    ZTwo_mass_FromLHERawL = ZTwo_mass_FromLHERaw;

                    ZPair_InvMass_FromLHERawL = ZPair_InvMass_FromLHERaw;
                    ZPair_EtaSep_FromLHERawL = ZPair_EtaSep_FromLHERaw;

                    H_pt_FromLHERawL = H_pt_FromLHERaw;
                    H_eta_FromLHERawL = H_eta_FromLHERaw;
                    H_phi_FromLHERawL = H_phi_FromLHERaw;
                    H_mass_FromLHERawL = H_mass_FromLHERaw;

                    ZPairPlusH_InvMass_FromLHERawL = ZPairPlusH_InvMass_FromLHERaw;

                    JOne_pt_FromLHERawL = JOne_pt_FromLHERaw;
                    JOne_eta_FromLHERawL = JOne_eta_FromLHERaw;
                    JOne_pdgId_FromLHERawL = JOne_pdgId_FromLHERaw;

                    JTwo_pt_FromLHERawL = JTwo_pt_FromLHERaw;
                    JTwo_eta_FromLHERawL = JTwo_eta_FromLHERaw;
                    JTwo_pdgId_FromLHERawL = JTwo_pdgId_FromLHERaw;

                    JOne_invmass_FromLHERawL = JOne_invmass_FromLHERaw;
                    JTwo_invmass_FromLHERawL = JTwo_invmass_FromLHERaw;

                    JOne_phi_FromLHERawL = JOne_phi_FromLHERaw;

                    JTwo_phi_FromLHERawL = JTwo_phi_FromLHERaw;
                    JPair_invmass_FromLHERawL = JPair_invmass_FromLHERaw;

                    J_etasep_FromLHERawL = J_etasep_FromLHERaw;

                    RawTree->Fill();

                }
                if (useFJGenMatchTree || useJGenMatchTree) {
                    std::vector<std::vector<Int_t>> tmpHFJAr;
                    std::vector<std::vector<Int_t>> tmpZFJAr;
                    //std::vector<Int_t> tmpZFJAr;
                    for (UInt_t i=0;i<*nGenPart;i++){
                        Int_t tmpPDGId = GenPart_pdgId[i];
                        Int_t tmpMotherID = GenPart_genPartIdxMother[i];
                        if (debugGenPart) std::cout << "i " << i << " GenPart_pdgId[i] " << tmpPDGId << "\n";

                        if (tmpHFJAr.size()){
                            for (UInt_t tmpHItr=0;tmpHItr<tmpHFJAr.size();tmpHItr++){
                                if (debugGenPart) std::cout << "tmpHItr " << tmpHItr << " tmpMotherID " << tmpMotherID << "\n";
                                if (tmpMotherID == tmpHFJAr[tmpHItr][0]){
                                    if (tmpPDGId == 25) std::cout <<"ERROR, ERROR, DAUGHTER PARTICLE IS H\n";
                                    else tmpHFJAr[tmpHItr].push_back(tmpPDGId);
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
                            if (tmpStatusBin) tmpHFJAr.push_back(tmpHFJVec);
                        }
                        
                        if (tmpZFJAr.size()){
                            for (UInt_t tmpZItr=0;tmpZItr<tmpZFJAr.size();tmpZItr++){
                                if (debugGenPart) std::cout << "tmpZItr " << tmpZItr << " tmpMotherID " << tmpMotherID << "\n";
                                if (tmpMotherID == tmpZFJAr[tmpZItr][0]){
                                    if (tmpPDGId == 23) std::cout <<"ERROR, ERROR, DAUGHTER PARTICLE IS Z\n";
                                    else tmpZFJAr[tmpZItr].push_back(tmpPDGId);
                                }
                            }
                        }
                        
                        if (GenPart_pdgId[i] == 23){
                            //std::bitset<sizeof(Int_t)> tmpStatusBitSet;
                            //bool tmpStatusBin = tmpStatusBitSet(GenPart_statusFlags[i]).test(13);
                            bool tmpStatusBin = GenPart_statusFlags[i] & (1 << 13);
                            //tmpStatusBin = bin(GenPart_statusFlags[i]);
                            if (debugGenPart) std::cout <<"GenPart_statusFlags[i] " << GenPart_statusFlags[i] << " tmpStatusBin " << tmpStatusBin << "\n";
                            
                            //tmpIsEnd = tmpStatusBin[-14];
                            std::vector<Int_t> tmpZFJVec;
                            tmpZFJVec.push_back(i);
                            if (tmpStatusBin) tmpZFJAr.push_back(tmpZFJVec);
                        }
                    }
                    if (debugGenPart) {
                        std::cout <<"Finished H,Z Finding. tmpHFJAr:\n";
                        if (tmpHFJAr.size()){
                            for (UInt_t tmpHItr=0;tmpHItr<tmpHFJAr.size();tmpHItr++){
                                for (UInt_t tmpHItrTwo=0;tmpHItrTwo<tmpHFJAr[tmpHItr].size();tmpHItrTwo++){
                                    std::cout << tmpHFJAr[tmpHItr][tmpHItrTwo] << ", ";
                                }
                                std::cout << "\n";
                            }
                        }
                        std::cout <<"tmpZFJAr:\n";
                        if (tmpZFJAr.size()){
                            for (UInt_t tmpZItr=0;tmpZItr<tmpZFJAr.size();tmpZItr++){
                                for (UInt_t tmpZItrTwo=0;tmpZItrTwo<tmpZFJAr[tmpZItr].size();tmpZItrTwo++){
                                    std::cout << tmpZFJAr[tmpZItr][tmpZItrTwo] << ", ";
                                }
                                std::cout << "\n";
                            }
                        }
                    }

                    std::vector<Int_t> tmpHFinalAr;
                    Int_t intermediaryH = -1;
                    if (tmpHFJAr.size() >= 2){
                        for (UInt_t tmpHItr=0;tmpHItr<tmpHFJAr.size();tmpHItr++){
                            if (std::count(tmpHFJAr[tmpHItr].begin(), tmpHFJAr[tmpHItr].end(), JOne_pdgId_FromLHERaw)){
                                if (std::count(tmpHFJAr[tmpHItr].begin(), tmpHFJAr[tmpHItr].end(), JTwo_pdgId_FromLHERaw)){
                                    if (tmpHFJAr[tmpHItr].size() == 3){
                                        intermediaryH = tmpHItr;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    std::vector<Int_t> finalHAr;
                    if (tmpHFJAr.size()){
                        for (UInt_t tmpHItr=0;tmpHItr<tmpHFJAr.size();tmpHItr++){
                            if (tmpHItr != intermediaryH) finalHAr.push_back(tmpHFJAr[tmpHItr][0]);
                        }
                    }

                    bool hGenFound = false;
                    float H_pt_FromGenRaw;
                    float H_eta_FromGenRaw;
                    float H_phi_FromGenRaw;
                    float H_mass_FromGenRaw;
                    float H_pdgId_FromGenRaw;
                    float H_genPartIdxMother_FromGenRaw;

                    std::vector<Int_t> tmpHDecAr;
                    UInt_t hJetInd;
                    bool hJetFound = false;
                    float HFJ_pt_FromGenMatch;
                    float HFJ_eta_FromGenMatch;
                    float HFJ_phi_FromGenMatch;
                    float HFJ_mass_FromGenMatch;
                    float HFJ_dRFromFJ_FromGenMatch;
                    
                    if (finalHAr.size() != 1) {
                        std::cout <<"ERROR ERROR, MORE OR LESS THAN ONE H,evCount,JOne_pdgId_FromLHERaw,JTwo_pdgId_FromLHERaw " << evCount<< " " <<JOne_pdgId_FromLHERaw<< " " <<JTwo_pdgId_FromLHERaw << "\n";
                    }
                    else{
                        Int_t tmpHInd = finalHAr[0];
                        hGenFound = true;
                        H_pt_FromGenRaw = GenPart_pt[tmpHInd];
                        H_eta_FromGenRaw = GenPart_eta[tmpHInd];
                        H_phi_FromGenRaw = GenPart_phi[tmpHInd];
                        H_mass_FromGenRaw = GenPart_mass[tmpHInd];
                        H_pdgId_FromGenRaw = GenPart_pdgId[tmpHInd];
                        H_genPartIdxMother_FromGenRaw = GenPart_genPartIdxMother[tmpHInd];



                        float mindROne = 1000;

                        if (useFJGenMatchTree){
                            if (debugGenPart) {
                                std::cout <<"entering FJ H gen matching loop\n";
                            }
                            /*
                            if (evCount-1 == 29){
                                std::cout << "ev29\n";
                                std::cout << "*nFatJet " << *nFatJet <<" finalHAr[0] " << finalHAr[0] << " GenPart_phi[finalHAr[0]] " << GenPart_phi[finalHAr[0]] << " GenPart_eta[finalHAr[0]] " << GenPart_eta[finalHAr[0]] << "\n";
                            }
                            */

                            for (UInt_t fatJetInd=0;fatJetInd<*nFatJet;fatJetInd++){
                                float tmpMindROne = calcDeltaR(FatJet_phi[fatJetInd],FatJet_eta[fatJetInd],GenPart_phi[tmpHInd],GenPart_eta[tmpHInd]);
                                /*
                                if (evCount-1 == 29){
                                    std::cout << "fatJetInd " << fatJetInd << " tmpMindROne " << tmpMindROne << " FatJet_phi[fatJetInd] "<<FatJet_phi[fatJetInd] << " FatJet_eta[fatJetInd] " << FatJet_eta[fatJetInd] << "\n";
                                }
                                */
                                if (tmpMindROne < mindROne){
                                    mindROne = tmpMindROne;
                                    hJetInd = fatJetInd;
                                }
                            }
                            

                            if (mindROne < genMatchdRCut){ //(mindROne != 1000){
                                hJetFound = true;
                                HFJ_pt_FromGenMatch = FatJet_pt[hJetInd];
                                HFJ_eta_FromGenMatch = FatJet_eta[hJetInd];
                                HFJ_phi_FromGenMatch = FatJet_phi[hJetInd];
                                HFJ_mass_FromGenMatch = FatJet_mass[hJetInd];
                                HFJ_dRFromFJ_FromGenMatch = mindROne;


                                HFJ_pt_FromGenMatchL = HFJ_pt_FromGenMatch;
                                HFJ_eta_FromGenMatchL = HFJ_eta_FromGenMatch;
                                HFJ_phi_FromGenMatchL = HFJ_phi_FromGenMatch;
                                HFJ_mass_FromGenMatchL = HFJ_mass_FromGenMatch;
                                HFJ_dRFromFJ_FromGenMatchL = HFJ_dRFromFJ_FromGenMatch;
                                

                                HFJGenTree->Fill();
                            }
                            else if (debugGenPart) {
                                std::cout <<"H Gen Match failed\n";
                                std::cout << "evCount " << evCount-1 << " mindROne " << mindROne << "\n";
                                std::cout << "*nFatJet " << *nFatJet << "\n";

                            }
                        }
                    }



                    std::vector<Int_t> tmpZFinalAr;
                    Int_t intermediaryZ = -1;
                    /*
                    if (evCount -1 == 407){
                        std::cout << "tmpZFJAr.size() " << tmpZFJAr.size() <<" JOne_pdgId_FromLHERaw " << JOne_pdgId_FromLHERaw << " JTwo_pdgId_FromLHERaw " << JTwo_pdgId_FromLHERaw << "\n";
                    }
                    */
                    if (tmpZFJAr.size() >= 3){
                        //if (evCount -1 == 407) std::cout << "yes\n";
                        for (UInt_t tmpZItr=0;tmpZItr<tmpZFJAr.size();tmpZItr++){
                            //if (evCount -1 == 407) std::cout << "yes\n";
                            if (std::count(tmpZFJAr[tmpZItr].begin(), tmpZFJAr[tmpZItr].end(), JOne_pdgId_FromLHERaw)){
                                //if (evCount -1 == 407) std::cout << "yes\n";
                                if (std::count(tmpZFJAr[tmpZItr].begin(), tmpZFJAr[tmpZItr].end(), JTwo_pdgId_FromLHERaw)){
                                    //if (evCount -1 == 407) std::cout << "yes\n";
                                    if (tmpZFJAr[tmpZItr].size() == 3){
                                        //if (evCount -1 == 407) std::cout << "yes\n";
                                        intermediaryZ = tmpZItr;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    std::vector<Int_t> finalZAr;
                    if (tmpZFJAr.size()){
                        for (UInt_t tmpZItr=0;tmpZItr<tmpZFJAr.size();tmpZItr++){
                            if (tmpZItr != intermediaryZ) finalZAr.push_back(tmpZFJAr[tmpZItr][0]);
                        }
                    }

                    bool zGenFound = false;
                    float ZOne_pt_FromGenRaw;
                    float ZOne_eta_FromGenRaw;
                    float ZOne_phi_FromGenRaw;
                    float ZOne_mass_FromGenRaw;
                    float ZOne_pdgId_FromGenRaw;
                    float ZOne_genPartIdxMother_FromGenRaw;
                    float ZTwo_pt_FromGenRaw;
                    float ZTwo_eta_FromGenRaw;
                    float ZTwo_phi_FromGenRaw;
                    float ZTwo_mass_FromGenRaw;
                    float ZTwo_pdgId_FromGenRaw;
                    float ZTwo_genPartIdxMother_FromGenRaw;

                    float ZPair_InvMass_FromGenRaw;
                    float ZPair_EtaSep_FromGenRaw;
                    ROOT::Math::PtEtaPhiMVector ZGenLeadVec;

                    ROOT::Math::PtEtaPhiMVector ZGenTrailingVec;

                    ROOT::Math::PtEtaPhiMVector ZGenPairVec;


                    std::vector<Int_t> tmpZDecAr;
                    if (finalZAr.size() != 2){
                        std::cout <<"ERROR ERROR, MORE OR LESS THAN TWO Zs,evCount,finalZAr.size(),intermediaryZ,JOne_pdgId_FromLHERaw,JTwo_pdgId_FromLHERaw " << evCount-1<< " " << finalZAr.size() << " " << intermediaryZ << " "<<JOne_pdgId_FromLHERaw<< " " <<JTwo_pdgId_FromLHERaw << "\n";
                        if (tmpZFJAr.size()){
                            for (UInt_t tmpZItr=0;tmpZItr<tmpZFJAr.size();tmpZItr++){
                                for (UInt_t tmpZItrTwo=0;tmpZItrTwo<tmpZFJAr[tmpZItr].size();tmpZItrTwo++){
                                    std::cout <<"tmpZItr " << tmpZItr << " tmpZItrTwo " << tmpZItrTwo << " tmpZFJAr[tmpZItr][tmpZItrTwo] " << tmpZFJAr[tmpZItr][tmpZItrTwo] << "\n";
                                }
                            }
                        }
                        if (finalZAr.size()){
                            for (UInt_t tmpZItr=0;tmpZItr<finalZAr.size();tmpZItr++){
                                std::cout << "finalZAr[tmpZItr] " << finalZAr[tmpZItr] << "\n";
                            }
                        }
                    }
                    else{


                        Int_t tmpZOneInd = finalZAr[0];
                        zGenFound = true;
                        ZOne_pt_FromGenRaw = GenPart_pt[tmpZOneInd];
                        ZOne_eta_FromGenRaw = GenPart_eta[tmpZOneInd];
                        ZOne_phi_FromGenRaw = GenPart_phi[tmpZOneInd];
                        ZOne_mass_FromGenRaw = GenPart_mass[tmpZOneInd];
                        ZOne_pdgId_FromGenRaw = GenPart_pdgId[tmpZOneInd];
                        ZOne_genPartIdxMother_FromGenRaw = GenPart_genPartIdxMother[tmpZOneInd];

                        Int_t tmpZTwoInd = finalZAr[1];
                        ZTwo_pt_FromGenRaw = GenPart_pt[tmpZTwoInd];
                        ZTwo_eta_FromGenRaw = GenPart_eta[tmpZTwoInd];
                        ZTwo_phi_FromGenRaw = GenPart_phi[tmpZTwoInd];
                        ZTwo_mass_FromGenRaw = GenPart_mass[tmpZTwoInd];
                        ZTwo_pdgId_FromGenRaw = GenPart_pdgId[tmpZTwoInd];
                        ZTwo_genPartIdxMother_FromGenRaw = GenPart_genPartIdxMother[tmpZTwoInd];

                        ZGenLeadVec  = ROOT::Math::PtEtaPhiMVector(ZOne_pt_FromGenRaw,ZOne_eta_FromGenRaw,ZOne_phi_FromGenRaw,ZOne_mass_FromGenRaw);

                        ZGenTrailingVec  = ROOT::Math::PtEtaPhiMVector(ZTwo_pt_FromGenRaw,ZTwo_eta_FromGenRaw,ZTwo_phi_FromGenRaw,ZTwo_mass_FromGenRaw);

                        ZGenPairVec = ZGenLeadVec+ZGenTrailingVec;

                        ZPair_InvMass_FromGenRaw = ZGenPairVec.M();
                        ZPair_EtaSep_FromGenRaw = abs(ZOne_eta_FromGenRaw-ZTwo_eta_FromGenRaw);

                        UInt_t zJetIndOne;
                        UInt_t zJetIndOneSecondPlace;
                        UInt_t zJetIndTwo;
                        float mindROne = 1000;
                        float mindROneSecondPlace = 1000;

                        float mindRTwo = 1000;
                        bool useSecondPlace = false;


                        if (useFJGenMatchTree){
                            if (debugGenPart) {
                                std::cout <<"entering FJ Z gen matching loop\n";
                                std::cout << "*nFatJet " << *nFatJet <<  " hJetFound " << hJetFound;
                                if (hJetFound) std::cout <<" hJetInd " << hJetInd << "\n";
                                else std::cout << "\n";
                            }

                            for (UInt_t fatJetInd=0;fatJetInd<*nFatJet;fatJetInd++){
                                if (hJetFound && fatJetInd == hJetInd) continue;
                                float tmpMindROne = calcDeltaR(FatJet_phi[fatJetInd],FatJet_eta[fatJetInd],GenPart_phi[finalZAr[0]],GenPart_eta[finalZAr[0]]);
                                /*
                                if (evCount -1 == 0){
                                    std::cout << "tmpMindROne " << tmpMindROne << "\n";
                                }
                                */
                                if (tmpMindROne < mindROne){
                                    mindROneSecondPlace = mindROne;
                                    mindROne = tmpMindROne;
                                    zJetIndOneSecondPlace = zJetIndOne;
                                    zJetIndOne = fatJetInd;
                                    /*
                                    if (evCount -1 == 0){
                                        std::cout << "mindROneSecondPlace " << mindROneSecondPlace << " mindROne " << mindROne << " zJetIndOneSecondPlace " << zJetIndOneSecondPlace << " zJetIndOne " << zJetIndOne << " useSecondPlace " << useSecondPlace << "\n";
                                    }
                                    */
                                }
                            }
                            /*
                            if (evCount -1 == 0){
                                std::cout << "secondloop\n";
                            }
                            */
                            for (UInt_t fatJetInd=0;fatJetInd<*nFatJet;fatJetInd++){
                                if (hJetFound && fatJetInd == hJetInd) continue;
                                float tmpMindRTwo = calcDeltaR(FatJet_phi[fatJetInd],FatJet_eta[fatJetInd],GenPart_phi[finalZAr[1]],GenPart_eta[finalZAr[1]]);
                                /*
                                if (evCount -1 == 0){
                                    std::cout << "tmpMindRTwo " << tmpMindRTwo << "\n";
                                }
                                */
                                if (tmpMindRTwo < mindRTwo){
                                    /*
                                    if (evCount -1 == 0){
                                        std::cout << "fatJetInd " << fatJetInd << "\n";
                                    }
                                    */
                                    if (fatJetInd == zJetIndOne) {
                                        /*
                                        if (evCount -1 == 0){
                                            std::cout << "mindROne " << mindROne << "\n";
                                        }
                                        */
                                        if (tmpMindRTwo < mindROne){
                                            useSecondPlace = true;
                                            mindRTwo = tmpMindRTwo;
                                            zJetIndTwo = fatJetInd;
                                            /*
                                            if (evCount -1 == 0){
                                                std::cout << "mindRTwo " << mindRTwo << "zJetIndTwo " << zJetIndTwo << "useSecondPlace " << useSecondPlace << "\n";
                                            }
                                            */
                                        }
                                        else useSecondPlace = false;
                                    }
                                    else {
                                        useSecondPlace = false;
                                        mindRTwo = tmpMindRTwo;
                                        zJetIndTwo = fatJetInd;
                                        /*
                                        if (evCount -1 == 0){
                                            std::cout << "mindRTwo " << mindRTwo << "zJetIndTwo " << zJetIndTwo << "useSecondPlace " << useSecondPlace << "\n";
                                        }
                                        */

                                    }
                                }
                            }

                            if (useSecondPlace) {
                                zJetIndOne = zJetIndOneSecondPlace;
                                mindROne = mindROneSecondPlace;
                                ZFJSameJetCtr += 1;
                                if (debugGenPart) std::cout << "evCount " << evCount -1 << " zJetIndOne " << zJetIndOne << " zJetIndTwo " << zJetIndTwo << " mindROne " << mindROne << " mindRTwo " << mindRTwo << "\n";
                            }


                            if (mindROne < genMatchdRCut && mindRTwo < genMatchdRCut ){
                                UInt_t tmpLeadInd;
                                UInt_t tmpTrailingInd;
                                if (FatJet_pt[zJetIndOne] > FatJet_pt[zJetIndTwo]){
                                    tmpLeadInd = zJetIndOne;
                                    tmpTrailingInd = zJetIndTwo;
                                }
                                else {
                                    tmpLeadInd = zJetIndTwo;
                                    tmpTrailingInd = zJetIndOne;
                                }
                                float ZFJLead_pt_FromGenMatch = FatJet_pt[tmpLeadInd];
                                float ZFJLead_eta_FromGenMatch = FatJet_eta[tmpLeadInd];
                                float ZFJLead_phi_FromGenMatch = FatJet_phi[tmpLeadInd];
                                float ZFJLead_mass_FromGenMatch = FatJet_mass[tmpLeadInd];
                                float ZFJLead_dRFromFJ_FromGenMatch = mindROne;

                                float ZFJTrailing_pt_FromGenMatch = FatJet_pt[tmpTrailingInd];
                                float ZFJTrailing_eta_FromGenMatch = FatJet_eta[tmpTrailingInd];
                                float ZFJTrailing_phi_FromGenMatch = FatJet_phi[tmpTrailingInd];
                                float ZFJTrailing_mass_FromGenMatch = FatJet_mass[tmpTrailingInd];
                                float ZFJTrailing_dRFromFJ_FromGenMatch = mindRTwo;

                                ZFJLead_pt_FromGenMatchL = ZFJLead_pt_FromGenMatch;
                                ZFJLead_eta_FromGenMatchL = ZFJLead_eta_FromGenMatch;
                                ZFJLead_phi_FromGenMatchL = ZFJLead_phi_FromGenMatch;
                                ZFJLead_mass_FromGenMatchL = ZFJLead_mass_FromGenMatch;
                                ZFJLead_dRFromFJ_FromGenMatchL = ZFJLead_dRFromFJ_FromGenMatch;
                                

                                ZFJTrailing_pt_FromGenMatchL = ZFJTrailing_pt_FromGenMatch;
                                ZFJTrailing_eta_FromGenMatchL = ZFJTrailing_eta_FromGenMatch;
                                ZFJTrailing_phi_FromGenMatchL = ZFJTrailing_phi_FromGenMatch;
                                ZFJTrailing_mass_FromGenMatchL = ZFJTrailing_mass_FromGenMatch;
                                ZFJTrailing_dRFromFJ_FromGenMatchL = ZFJTrailing_dRFromFJ_FromGenMatch;


                                ROOT::Math::PtEtaPhiMVector tmpZFJLeadVec  = ROOT::Math::PtEtaPhiMVector(ZFJLead_pt_FromGenMatch,ZFJLead_eta_FromGenMatch,ZFJLead_phi_FromGenMatch,ZFJLead_mass_FromGenMatch);

                                ROOT::Math::PtEtaPhiMVector tmpZFJTrailingVec  = ROOT::Math::PtEtaPhiMVector(ZFJTrailing_pt_FromGenMatch,ZFJTrailing_eta_FromGenMatch,ZFJTrailing_phi_FromGenMatch,ZFJTrailing_mass_FromGenMatch);

                                ROOT::Math::PtEtaPhiMVector tmpZFJPairVec = tmpZFJLeadVec+tmpZFJTrailingVec;

                                float ZFJPair_InvMass_FromGenMatch = tmpZFJPairVec.M();;
                                float ZFJPair_EtaSep_FromGenMatch = abs(ZFJLead_eta_FromGenMatch-ZFJTrailing_eta_FromGenMatch);

                                ZFJPair_InvMass_FromGenMatchL = ZFJPair_InvMass_FromGenMatch;
                                ZFJPair_EtaSep_FromGenMatchL = ZFJPair_EtaSep_FromGenMatch;
                                ZFJGenTree->Fill();
                                if (hJetFound){
                                    ROOT::Math::PtEtaPhiMVector tmpHFJVec  = ROOT::Math::PtEtaPhiMVector(HFJ_pt_FromGenMatch,HFJ_eta_FromGenMatch,HFJ_phi_FromGenMatch,HFJ_mass_FromGenMatch);

                                    ROOT::Math::PtEtaPhiMVector tmpHZFJVec = tmpHFJVec+tmpZFJPairVec;
                                    
                                    ZHFJ_ZPairPlusHInvMass_FromGenMatchL = tmpHZFJVec.M();
                                    ZHFJGenTree->Fill();
                                }
                            }
                        }
                        if (useJGenMatchTree){
                            if (debugGenPart) {
                                std::cout <<"entering J Z gen matching loop\n";
                            }

                            if (useFJGenMatchTree) {
                                mindROne = 1000;
                                mindRTwo = 1000;
                                mindROneSecondPlace = 1000;
                                useSecondPlace = false;
                            }

                            for (UInt_t jetInd=0;jetInd<*nJet;jetInd++){
                                float tmpMindROne = calcDeltaR(Jet_phi[jetInd],Jet_eta[jetInd],GenPart_phi[finalZAr[0]],GenPart_eta[finalZAr[0]]);
                                
                                if (tmpMindROne < mindROne){
                                    mindROneSecondPlace = mindROne;
                                    mindROne = tmpMindROne;
                                    zJetIndOneSecondPlace = zJetIndOne;
                                    zJetIndOne = jetInd;
                                }
                            }
                            for (UInt_t jetInd=0;jetInd<*nJet;jetInd++){
                                float tmpMindRTwo = calcDeltaR(Jet_phi[jetInd],Jet_eta[jetInd],GenPart_phi[finalZAr[1]],GenPart_eta[finalZAr[1]]);
                                if (tmpMindRTwo < mindRTwo){
                                    if (jetInd == zJetIndOne) {
                                        if (tmpMindRTwo < mindROne){
                                            useSecondPlace = true;
                                            mindRTwo = tmpMindRTwo;
                                            zJetIndTwo = jetInd;
                                        }
                                        else useSecondPlace = false;
                                    }
                                    else {
                                        useSecondPlace = false;
                                        mindRTwo = tmpMindRTwo;
                                        zJetIndTwo = jetInd;
                                    }
                                }
                            }

                            if (useSecondPlace) {
                                zJetIndOne = zJetIndOneSecondPlace;
                                mindROne = mindROneSecondPlace;
                                ZJSameJetCtr += 1;
                            }


                            


                            if (mindROne < genMatchdRCut && mindRTwo < genMatchdRCut ){
                                UInt_t tmpLeadInd;
                                UInt_t tmpTrailingInd;
                                if (Jet_pt[zJetIndOne] > Jet_pt[zJetIndTwo]){
                                    tmpLeadInd = zJetIndOne;
                                    tmpTrailingInd = zJetIndTwo;
                                }
                                else {
                                    tmpLeadInd = zJetIndTwo;
                                    tmpTrailingInd = zJetIndOne;
                                }
                                float ZJLead_pt_FromGenMatch = Jet_pt[tmpLeadInd];
                                float ZJLead_eta_FromGenMatch = Jet_eta[tmpLeadInd];
                                float ZJLead_phi_FromGenMatch = Jet_phi[tmpLeadInd];
                                float ZJLead_mass_FromGenMatch = Jet_mass[tmpLeadInd];
                                float ZJLead_dRFromJ_FromGenMatch = mindROne;

                                float ZJTrailing_pt_FromGenMatch = Jet_pt[tmpTrailingInd];
                                float ZJTrailing_eta_FromGenMatch = Jet_eta[tmpTrailingInd];
                                float ZJTrailing_phi_FromGenMatch = Jet_phi[tmpTrailingInd];
                                float ZJTrailing_mass_FromGenMatch = Jet_mass[tmpTrailingInd];
                                float ZJTrailing_dRFromJ_FromGenMatch = mindRTwo;

                                ZJLead_pt_FromGenMatchL = ZJLead_pt_FromGenMatch;
                                ZJLead_eta_FromGenMatchL = ZJLead_eta_FromGenMatch;
                                ZJLead_phi_FromGenMatchL = ZJLead_phi_FromGenMatch;
                                ZJLead_mass_FromGenMatchL = ZJLead_mass_FromGenMatch;
                                ZJLead_dRFromJ_FromGenMatchL = ZJLead_dRFromJ_FromGenMatch;
                                

                                ZJTrailing_pt_FromGenMatchL = ZJTrailing_pt_FromGenMatch;
                                ZJTrailing_eta_FromGenMatchL = ZJTrailing_eta_FromGenMatch;
                                ZJTrailing_phi_FromGenMatchL = ZJTrailing_phi_FromGenMatch;
                                ZJTrailing_mass_FromGenMatchL = ZJTrailing_mass_FromGenMatch;
                                ZJTrailing_dRFromJ_FromGenMatchL = ZJTrailing_dRFromJ_FromGenMatch;

                                ROOT::Math::PtEtaPhiMVector tmpZJLeadVec  = ROOT::Math::PtEtaPhiMVector(ZJLead_pt_FromGenMatch,ZJLead_eta_FromGenMatch,ZJLead_phi_FromGenMatch,ZJLead_mass_FromGenMatch);

                                ROOT::Math::PtEtaPhiMVector tmpZJTrailingVec  = ROOT::Math::PtEtaPhiMVector(ZJTrailing_pt_FromGenMatch,ZJTrailing_eta_FromGenMatch,ZJTrailing_phi_FromGenMatch,ZJTrailing_mass_FromGenMatch);

                                ROOT::Math::PtEtaPhiMVector tmpZJPairVec = tmpZJLeadVec+tmpZJTrailingVec;

                                float ZJPair_InvMass_FromGenMatch = tmpZJPairVec.M();;
                                float ZJPair_EtaSep_FromGenMatch = abs(ZJLead_eta_FromGenMatch-ZJTrailing_eta_FromGenMatch);

                                ZJPair_InvMass_FromGenMatchL = ZJPair_InvMass_FromGenMatch;
                                ZJPair_EtaSep_FromGenMatchL = ZJPair_EtaSep_FromGenMatch;
                                ZJGenTree->Fill();

                                if (hJetFound){
                                    ROOT::Math::PtEtaPhiMVector tmpHFJVec  = ROOT::Math::PtEtaPhiMVector(HFJ_pt_FromGenMatch,HFJ_eta_FromGenMatch,HFJ_phi_FromGenMatch,HFJ_mass_FromGenMatch);

                                    ROOT::Math::PtEtaPhiMVector tmpHZJVec = tmpHFJVec+tmpZJPairVec;
                                    
                                    ZHJ_ZPairPlusHInvMass_FromGenMatchL = tmpHZJVec.M();
                                    ZHJGenTree->Fill();
                                }
                            }
                        }

                        if (hGenFound && zGenFound){

                            ROOT::Math::PtEtaPhiMVector tmpHGenVec  = ROOT::Math::PtEtaPhiMVector(H_pt_FromGenRaw,H_eta_FromGenRaw,H_phi_FromGenRaw,H_mass_FromGenRaw);



                            ROOT::Math::PtEtaPhiMVector tmpZPairPlusHVec = ZGenPairVec+tmpHGenVec;

                            float ZPairPlusH_InvMass_FromGenRaw = tmpZPairPlusHVec.M();




                            H_pt_FromGenRawL = H_pt_FromGenRaw;
                            H_eta_FromGenRawL = H_eta_FromGenRaw;
                            H_phi_FromGenRawL = H_phi_FromGenRaw;
                            H_mass_FromGenRawL = H_mass_FromGenRaw;
                            H_pdgId_FromGenRawL = H_pdgId_FromGenRaw;
                            H_genPartIdxMother_FromGenRawL = H_genPartIdxMother_FromGenRaw;

                            ZOne_pt_FromGenRawL = ZOne_pt_FromGenRaw;
                            ZOne_eta_FromGenRawL = ZOne_eta_FromGenRaw;
                            ZOne_phi_FromGenRawL = ZOne_phi_FromGenRaw;
                            ZOne_mass_FromGenRawL = ZOne_mass_FromGenRaw;
                            ZOne_pdgId_FromGenRawL = ZOne_pdgId_FromGenRaw;
                            ZOne_genPartIdxMother_FromGenRawL = ZOne_genPartIdxMother_FromGenRaw;

                            ZTwo_pt_FromGenRawL = ZTwo_pt_FromGenRaw;
                            ZTwo_eta_FromGenRawL = ZTwo_eta_FromGenRaw;
                            ZTwo_phi_FromGenRawL = ZTwo_phi_FromGenRaw;
                            ZTwo_mass_FromGenRawL = ZTwo_mass_FromGenRaw;
                            ZTwo_pdgId_FromGenRawL = ZTwo_pdgId_FromGenRaw;
                            ZTwo_genPartIdxMother_FromGenRawL = ZTwo_genPartIdxMother_FromGenRaw;

                            ZPair_InvMass_FromGenRawL = ZPair_InvMass_FromGenRaw;
                            ZPair_EtaSep_FromGenRawL = ZPair_EtaSep_FromGenRaw;

                            ZPairPlusH_InvMass_FromGenRawL = ZPairPlusH_InvMass_FromGenRaw;

                            GenRawTree->Fill();
                            

                        }
                            
                            
                    }
                }
            }
            



            //First check that it passes the hbb tagging
            bool hbbTag = *HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02 || *HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2 || *HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4;
            if (!hbbTag) continue;
            passhbbCtr += 1;
            

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

            bool lepHLT = elecHLT || muonHLT;
            
            //Hadronic
            bool hadHLT =  (*HLT_PFHT1050 || *HLT_AK8PFJet500 || *HLT_AK8PFJet360_TrimMass30 || *HLT_AK8PFHT750_TrimMass50 || *HLT_AK8PFJet380_TrimMass30 ||
            *HLT_AK8PFJet400_TrimMass30 || *HLT_AK8PFJet420_TrimMass30 ||
            *HLT_AK8PFHT800_TrimMass50 || *HLT_AK8PFHT850_TrimMass50 || *HLT_AK8PFHT900_TrimMass50);

            bool isLeptonic = doubleElecHLT || doubleMuonHLT || muonEGHLT;
            bool isSemiLeptonic = (elecHLT || muonHLT) && hadHLT;
            bool isHadronic = hadHLT;

            if (!(isLeptonic || isSemiLeptonic || isHadronic)) continue;

            passAnyChannelCtr += 1;
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
            doVBFJetCut(nJetLen,Jet_pt,Jet_jetId,Jet_eta,Jet_phi,Jet_mass,jetPTCut,jetEtaDifCut,jetInvMassCut,jetPairInvMass,jetLeadPt,jetLeadEta,jetLeadPhi,jetTrailingPt,jetTrailingEta,jetTrailingPhi,leadJet_1,leadJet_2,debug);
            /*
            for (UInt_t jetIndOne=0; jetIndOne<nJetLen-1;jetIndOne++){
                float jetPtOne = Jet_pt[jetIndOne];
                float jetIdOne = Jet_jetId[jetIndOne];
                if (debug) std::cout << "jetIndOne: " << jetIndOne << " Jet_pt[jetIndOne]: " << Jet_pt[jetIndOne] << " Jet_jetId[jetIndOne]: " << Jet_jetId[jetIndOne] << "\n";
                if (jetPtOne < jetPTCut || !(jetIdOne == 6)) continue;
                for (UInt_t jetIndTwo=jetIndOne+1; jetIndTwo<nJetLen; jetIndTwo++){
                    float jetPtTwo = Jet_pt[jetIndTwo];
                    UInt_t jetIdTwo = Jet_jetId[jetIndTwo];
                    if (debug) std::cout << "jetIndTwo: " << jetIndTwo << " Jet_pt[jetIndTwo]: " << Jet_pt[jetIndTwo] << " Jet_jetId[jetIndTwo]: " << Jet_jetId[jetIndTwo] << "\n";
                    if (jetPtTwo < jetPTCut || !(jetIdTwo == 6)) continue;
                    float jetEtaOne = Jet_eta[jetIndOne];
                    float jetEtaTwo = Jet_eta[jetIndTwo];
                    if (abs(jetEtaOne - jetEtaTwo) < jetEtaDifCut) continue;
                    
                    float jetPhiOne = Jet_phi[jetIndOne];
                    float jetPhiTwo = Jet_phi[jetIndTwo];
                    float jetMassOne = Jet_mass[jetIndOne];
                    float jetMassTwo = Jet_mass[jetIndTwo];
                    ROOT::Math::PtEtaPhiMVector tmpVecOne = ROOT::Math::PtEtaPhiMVector(jetPtOne, jetEtaOne, jetPhiOne, jetMassOne);
                    ROOT::Math::PtEtaPhiMVector tmpVecTwo = ROOT::Math::PtEtaPhiMVector(jetPtTwo, jetEtaTwo, jetPhiTwo, jetMassTwo);
                    ROOT::Math::PtEtaPhiMVector tmpVecSum = tmpVecOne+tmpVecTwo;
                    float tmpJetPairInvMass = tmpVecSum.M();
                    if (tmpJetPairInvMass < jetInvMassCut) continue;
                    if (tmpJetPairInvMass > jetPairInvMass){
                        jetPairInvMass = tmpJetPairInvMass;
                        if (jetPtOne >= jetPtTwo) {
                            jetLeadPt = jetPtOne;
                            jetLeadEta = jetEtaOne;
                            jetLeadPhi = jetPhiOne;
                            jetTrailingPt = jetPtTwo;
                            jetTrailingEta = jetEtaTwo;
                            jetTrailingPhi = jetPhiTwo;
                            leadJet_1 = jetIndOne;
                            leadJet_2 = jetIndTwo;
                        }
                        else {
                            jetLeadPt = jetPtTwo;
                            jetLeadEta = jetEtaTwo;
                            jetLeadPhi = jetPhiTwo;
                            jetTrailingPt = jetPtOne;
                            jetTrailingEta = jetEtaOne;
                            jetTrailingPhi = jetPhiOne;
                            leadJet_1 = jetIndTwo;
                            leadJet_2 = jetIndOne;
                        }
                    }
                }
            }
            */
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


            //Now fat jets
            UInt_t nFatJetLen = *nFatJet;
            float hFatJet_HTag_fromPt = 0.;
            float hFatJet_pt_fromPt = 0.;
            float hFatJet_phi_fromPt = 0.;
            float hFatJet_eta_fromPt = 0.;
            float hFatJet_mass_fromPt = 0.;
            float hFatJet_pt_fromHTag = 0.;
            float hFatJet_phi_fromHTag = 0.;
            float hFatJet_eta_fromHTag = 0.;
            float hFatJet_mass_fromHTag = 0.;
            float hFatJet_HTag_fromHTag = 0.;
            UInt_t hFatJet_ind_fromHTag = 0;
            if (debug){
                std::cout << "Entering Fat Jets Loop\n";
            }

            doHiggsFatJetCut(nFatJetLen,hFatJet_HTag_fromPt,hFatJet_pt_fromPt,hFatJet_phi_fromPt,hFatJet_eta_fromPt,hFatJet_mass_fromPt,hFatJet_pt_fromHTag,hFatJet_phi_fromHTag,hFatJet_eta_fromHTag,hFatJet_mass_fromHTag,hFatJet_HTag_fromHTag,hFatJet_ind_fromHTag,FatJet_deepTag_H,hFatJetDeepTagCut,FatJet_pt,hFatJetPTCut,FatJet_jetId,FatJet_phi,FatJet_eta,jetLeadPhi,jetLeadEta,jetTrailingPhi,jetTrailingEta,hFatJetdRCut,FatJet_mass);
            /*
            for (UInt_t fatJetInd=0;fatJetInd<*nFatJet;fatJetInd++){
                float tmpFatJet_deepTag_H = FatJet_deepTag_H[fatJetInd];
                if (debug) {
                    std::cout << fatJetInd << " +++++++++++++++\n";
                    std::cout << "Fat jet DeepTag_H    " <<  tmpFatJet_deepTag_H << "\n";
                }
                
                
                
                if (tmpFatJet_deepTag_H > hFatJetDeepTagCut){
                    float tmpFatJet_pt = FatJet_pt[fatJetInd];
                    if (debug){
                        std::cout << "Fat jet pt    " <<  tmpFatJet_pt << "\n";
                    }
                    
                    if (tmpFatJet_pt > hFatJetPTCut){
                        Int_t tmpFatJet_jetId = FatJet_jetId[fatJetInd];
                        if (debug){
                            std::cout << "Fat jet jetId    " <<  tmpFatJet_jetId << "\n";
                        }
                        if (tmpFatJet_jetId == 6){
                            float tmpFatJet_phi = FatJet_phi[fatJetInd];
                            float tmpFatJet_eta = FatJet_eta[fatJetInd];
                            float tmpDROne = calcDeltaR(tmpFatJet_phi,tmpFatJet_eta,jetLeadPhi,jetLeadEta);
                            float tmpDRTwo = calcDeltaR(tmpFatJet_phi,tmpFatJet_eta,jetTrailingPhi,jetTrailingEta);
                            if (debug){
                                std::cout << "Fat jet phi    " <<  tmpFatJet_phi << "\n";
                                std::cout << "Fat jet eta    " <<  tmpFatJet_eta << "\n";
                                std::cout << "Fat jet dROne    " <<  tmpDROne << " \n";
                                std::cout << "Fat jet dRTwo    " <<  tmpDRTwo << " \n";
                            }
                            if (tmpDROne > hFatJetdRCut && tmpDRTwo > hFatJetdRCut){
                                if (debug) std::cout << "Passed fatjet cuts\n";
                                float tmpFatJet_HTag = FatJet_deepTag_H[fatJetInd];
                                if (tmpFatJet_pt > hFatJet_pt_fromPt){
                                    hFatJet_HTag_fromPt = tmpFatJet_HTag;
                                    hFatJet_pt_fromPt = tmpFatJet_pt;
                                    hFatJet_eta_fromPt = tmpFatJet_eta;
                                    hFatJet_phi_fromPt = tmpFatJet_phi;
                                    hFatJet_mass_fromPt = FatJet_mass[fatJetInd];
                                }
                                
                                if (tmpFatJet_HTag > hFatJet_HTag_fromHTag){
                                    hFatJet_HTag_fromHTag = tmpFatJet_HTag;
                                    hFatJet_pt_fromHTag = tmpFatJet_pt;
                                    hFatJet_eta_fromHTag = tmpFatJet_eta;
                                    hFatJet_phi_fromHTag = tmpFatJet_phi;
                                    hFatJet_mass_fromHTag = FatJet_mass[fatJetInd];
                                }
                            }
                        }
                    }
                }
            }
            */
            if (hFatJet_pt_fromHTag == 0) continue;
            if (debug) std::cout << " found fat jet\n";
            passFatJets += 1;


            //Now gen matching
            UInt_t nGenPartLen = *nGenPart;
            float hGenPartDR_fromPt = 999.;
            Int_t hGenPartInd_fromPt = -1;
            Int_t hGenPartpdgId_fromPt = -1;
            float hGenPartDR_fromHTag = 999.;
            Int_t hGenPartInd_fromHTag = -1;
            Int_t hGenPartpdgId_fromHTag = -1;
            for (UInt_t genPartInd=0; genPartInd < nGenPartLen; genPartInd++){
                float tmpGenPart_phi = GenPart_phi[genPartInd];
                float tmpGenPart_eta = GenPart_eta[genPartInd];
                float tmpDR_fromPt = calcDeltaR(hFatJet_phi_fromPt,hFatJet_eta_fromPt,tmpGenPart_phi,tmpGenPart_eta);
                if (tmpDR_fromPt < hGenPartDR_fromPt){
                    hGenPartDR_fromPt = tmpDR_fromPt;
                    hGenPartInd_fromPt = genPartInd;
                    hGenPartpdgId_fromPt = GenPart_pdgId[genPartInd];
                }
                float tmpDR_fromHTag = calcDeltaR(hFatJet_phi_fromHTag,hFatJet_eta_fromHTag,tmpGenPart_phi,tmpGenPart_eta);
                if (tmpDR_fromHTag < hGenPartDR_fromHTag){
                    hGenPartDR_fromHTag = tmpDR_fromHTag;
                    hGenPartInd_fromHTag = genPartInd;
                    hGenPartpdgId_fromHTag = GenPart_pdgId[genPartInd];
                }
            }
            if (!(hGenPartInd_fromPt == -1) && !(hGenPartInd_fromHTag == -1)){
                if (debug) std::cout << " found gen part\n";
                passGenPart += 1;
                
                //Get genPart first mom
                if (debug) std::cout << "GenPart_genPartIdxMother[hGenPartInd_fromPt] " << GenPart_genPartIdxMother[hGenPartInd_fromPt] << "\n";
                Int_t hGenPartFirstMompdgId_fromPt = getInitialMother(GenPart_genPartIdxMother,GenPart_pdgId,hGenPartInd_fromPt,debug);
                Int_t hGenPartFirstMompdgId_fromHTag = getInitialMother(GenPart_genPartIdxMother,GenPart_pdgId,hGenPartInd_fromHTag,debug);
                if (debug) std::cout << "hGenPartFirstMompdgId_fromPt: " << hGenPartFirstMompdgId_fromPt << " hGenPartFirstMompdgId_fromHTag: " << hGenPartFirstMompdgId_fromHTag << "\n";
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

                if (isLeptonic){
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
                if ((!passesCutsBool) && isSemiLeptonic){
                    if (debug) std::cout << "trying SemiLeptonic\n";
                    tryingSemiLepCtr += 1;
                    float semiLepFatJetPT = 0;
                    FJInd = -1;
                    UInt_t numFatJet = *nFatJet;
                    doSemiLepChanFatJetCut(semiLepFatJetPT,FJInd,numFatJet,jetLeadPhi,jetLeadEta,jetTrailingPhi,jetTrailingEta,hFatJet_ind_fromHTag,fatJetPTCut,hFatJetdRCut,FatJet_pt,FatJet_phi,FatJet_eta);
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
                if ((!passesCutsBool) && isHadronic){
                    tryingHadCtr += 1;
                    LFJOneInd = -1;
                    LFJTwoInd = -1;
                    leadFatJetMaxPT = -1;
                    secondFatJetMaxPT = -1;
                    FJInvMass = -1;
                    float tmpFatJetPT;
                    float tmpFatJetPTTwo;
                    float tmpEtaDif;
                    if (debugHadronic) std::cout << "---------------- Event " << evCount - 1 << " ----------------\n";
                    //if (debugHadronic) std::cout << "hFatJet_ind_fromHTag " << hFatJet_ind_fromHTag << "\n";
                    if (debugHadronic) std::cout << "hFatJetdRCut " << hFatJetdRCut << "\n";
                    if (debugHadronic) std::cout << "fatJetPTCut " << fatJetPTCut << "\n";
                    if (debugHadronic) std::cout << "jetEtaDifCut " << jetEtaDifCut << "\n";
                    if (debugHadronic) std::cout << "jetInvMassCut " << jetInvMassCut << "\n";

                    if (debugHadronic) std::cout << "--------- Entering FJ loop for Hadronic Channel ---------\n";

                    UInt_t numFatJet = *nFatJet;
                    doHadChanFatJetCut(LFJOneInd,LFJTwoInd,leadFatJetMaxPT,secondFatJetMaxPT,FJInvMass,tmpFatJetPT,tmpFatJetPTTwo,tmpEtaDif,numFatJet,hFatJet_ind_fromHTag,jetLeadPhi,jetLeadEta,jetTrailingPhi,jetTrailingEta,hFatJetdRCut,fatJetPTCut,jetEtaDifCut,jetInvMassCut,FatJet_pt,FatJet_phi,FatJet_eta,FatJet_mass);

                    /*

                    for (UInt_t i=0;i<*nFatJet-1;i++){
                        
                        if (debugHadronic) std::cout << "First FatJet " << i << "\n";

                        tmpFatJetPT = FatJet_pt[i];
                        if (debugHadronic) std::cout << "tmpFatJetPT " << tmpFatJetPT << "\n";
                        if (tmpFatJetPT > fatJetPTCut){
                            //Looping through all jets past the current one
                            for (UInt_t j=i+1;j<*nFatJet;j++){
                                if (debugHadronic) std::cout << "Second FatJet " << j << "\n";
                                //Getting PT of the second jet
                                tmpFatJetPTTwo = FatJet_pt[j];
                                if (debugHadronic) std::cout << "tmpFatJetPTTwo " << tmpFatJetPTTwo << "\n";
                                //Checking if it passes the pt cut
                                if (tmpFatJetPTTwo > fatJetPTCut){
                                    //Getting the eta dif between the two jets
                                    tmpEtaDif = abs(FatJet_eta[i]-FatJet_eta[j]);
                                    if (debugHadronic) std::cout << "tmpEtaDif " << tmpEtaDif << "\n";
                                    //Checking if the eta dif passes the eta dif cut
                                    if (tmpEtaDif > jetEtaDifCut){
                                        //Getting four vectors for the two jets, using pt, eta, phi, and mass
                                        ROOT::Math::PtEtaPhiMVector tmpVecOne = ROOT::Math::PtEtaPhiMVector(FatJet_pt[i], FatJet_eta[i], FatJet_phi[i], FatJet_mass[i]);
                                        ROOT::Math::PtEtaPhiMVector tmpVecTwo = ROOT::Math::PtEtaPhiMVector(FatJet_pt[j], FatJet_eta[j], FatJet_phi[j], FatJet_mass[j]);
                                        //Adding four vectors together and getting their invariant mass
                                        ROOT::Math::PtEtaPhiMVector tmpDiJetVec = tmpVecOne+tmpVecTwo;
                                        float tmpFJInvMass = tmpDiJetVec.M();
                                        if (debugHadronic) std::cout << "tmpFJInvMass " << tmpFJInvMass << "\n";
                                        //Checking if their InvMass passes the InvMass cut
                                        if (tmpFJInvMass > jetInvMassCut){
                                            if (debugHadronic) std::cout << "Passed all cuts!!!!!!!!!!!!!!\n";
                                            
                                            //Selecting on top jet pt first
                                            float tmpMaxPtLead = 0;
                                            float tmpMaxPtSecond = 0;
                                            UInt_t tmpFJLeadInd=0;
                                            UInt_t tmpFJTrailingInd=0;
                                            //Sorting which jet has the larger pt
                                            if (tmpFatJetPT > tmpFatJetPTTwo){
                                                tmpMaxPtLead = tmpFatJetPT;
                                                tmpMaxPtSecond = tmpFatJetPTTwo;
                                                tmpFJLeadInd = i;
                                                tmpFJTrailingInd = j;
                                            }
                                            else{
                                                tmpMaxPtLead = tmpFatJetPTTwo;
                                                tmpMaxPtSecond = tmpFatJetPT;
                                                tmpFJLeadInd = j;
                                                tmpFJTrailingInd = i;
                                            }

                                            //Selecting based on that jet's pt
                                            if (tmpMaxPtLead > leadFatJetMaxPT){
                                                leadFatJetMaxPT = tmpMaxPtLead;
                                                secondFatJetMaxPT = tmpMaxPtSecond;
                                                LFJOneInd = tmpFJLeadInd;
                                                LFJTwoInd = tmpFJTrailingInd;
                                                FJInvMass = tmpFJInvMass;
                                            }
                                            //If that jet is already part of the current selected pair,
                                            //select based on the respective lower pt jets in the pairs
                                            else if (tmpMaxPtLead == leadFatJetMaxPT){
                                                if (tmpMaxPtSecond > secondFatJetMaxPT){
                                                    secondFatJetMaxPT = tmpMaxPtSecond;
                                                    LFJOneInd = tmpFJLeadInd;
                                                    LFJTwoInd = tmpFJTrailingInd;
                                                    FJInvMass = tmpFJInvMass;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    */
                    //Filling histograms based on max jet pt in pair, with secondary jet pt as a tiebreaker
                    //Checking that it didn't select the same jet for both parts of the pair 
                    if (LFJOneInd != LFJTwoInd){
                        passHadCut += 1;
                        passesCutsBool = true;
                        passedAsHadBool = true;
                    }
                }

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
                    
                    hFatJet_pt_fromPtL = hFatJet_pt_fromPt;
                    hFatJet_phi_fromPtL = hFatJet_phi_fromPt;
                    hFatJet_eta_fromPtL = hFatJet_eta_fromPt;
                    hFatJet_mass_fromPtL = hFatJet_mass_fromPt;
                    hFatJet_HTag_fromPtL = hFatJet_HTag_fromPt;
                    hFatJet_pt_fromHTagL = hFatJet_pt_fromHTag;
                    hFatJet_phi_fromHTagL = hFatJet_phi_fromHTag;
                    hFatJet_eta_fromHTagL = hFatJet_eta_fromHTag;
                    hFatJet_mass_fromHTagL = hFatJet_mass_fromHTag;
                    hFatJet_HTag_fromHTagL = hFatJet_HTag_fromHTag;
                    

                    //Now GenPart
                    //print(nGenPart)
                    if (debug) std::cout << "Filling gen parts\n";

                    nGenPartL = *nGenPart;
                    hGenPartDR_fromPtL = hGenPartDR_fromPt;
                    hGenPartInd_fromPtL = hGenPartInd_fromPt;
                    hGenPartpdgId_fromPtL = hGenPartpdgId_fromPt;
                    hGenPartFirstMompdgId_fromPtL = hGenPartFirstMompdgId_fromPt;
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

                    if (useLHETree) {
                        
                        ZOne_pt_FromLHESelectedL = ZOne_pt_FromLHERaw;
                        ZOne_eta_FromLHESelectedL = ZOne_eta_FromLHERaw;
                        ZOne_phi_FromLHESelectedL = ZOne_phi_FromLHERaw;
                        ZOne_mass_FromLHESelectedL = ZOne_mass_FromLHERaw;

                        ZTwo_pt_FromLHESelectedL = ZTwo_pt_FromLHERaw;
                        ZTwo_eta_FromLHESelectedL = ZTwo_eta_FromLHERaw;
                        ZTwo_phi_FromLHESelectedL = ZTwo_phi_FromLHERaw;
                        ZTwo_mass_FromLHESelectedL = ZTwo_mass_FromLHERaw;

                        ZPair_InvMass_FromLHESelectedL = ZPair_InvMass_FromLHERaw;
                        ZPair_EtaSep_FromLHESelectedL = ZPair_EtaSep_FromLHERaw;

                        H_pt_FromLHESelectedL = H_pt_FromLHERaw;
                        H_eta_FromLHESelectedL = H_eta_FromLHERaw;
                        H_phi_FromLHESelectedL = H_phi_FromLHERaw;
                        H_mass_FromLHESelectedL = H_mass_FromLHERaw;

                        ZPairPlusH_InvMass_FromLHESelectedL = ZPairPlusH_InvMass_FromLHERaw;

                        JOne_pt_FromLHESelectedL = JOne_pt_FromLHERaw;
                        JOne_eta_FromLHESelectedL = JOne_eta_FromLHERaw;
                        JOne_pdgId_FromLHESelectedL = JOne_pdgId_FromLHERaw;
                        

                        JTwo_pt_FromLHESelectedL = JTwo_pt_FromLHERaw;
                        JTwo_eta_FromLHESelectedL = JTwo_eta_FromLHERaw;
                        JTwo_pdgId_FromLHESelectedL = JTwo_pdgId_FromLHERaw;

                        JOne_invmass_FromLHESelectedL = JOne_invmass_FromLHERaw;
                        JTwo_invmass_FromLHESelectedL = JTwo_invmass_FromLHERaw;

                        JOne_phi_FromLHESelectedL = JOne_phi_FromLHERaw;

                        JTwo_phi_FromLHESelectedL = JTwo_phi_FromLHERaw;
                        JPair_invmass_FromLHESelectedL = JPair_invmass_FromLHERaw;

                        J_etasep_FromLHESelectedL = J_etasep_FromLHERaw;

                        SelectedTree->Fill();
                        
                    }



                    if (debug) std::cout << "Filling channel branches \n";
                    evPassCount += 1;
                    ROOT::Math::PtEtaPhiMVector tmpZ2LeadVec;
                    ROOT::Math::PtEtaPhiMVector tmpZ2TrailingVec;
                    ROOT::Math::PtEtaPhiMVector tmpZ2Vec;
                    tmpIso = 0;

                    if (passedAsLepBool){
                        if (debug) std::cout << "Filling passed as lep branch \n";
                        //tmpZ1Vec = Z1LeadVec + Z1TrailingVec
                        if (!Z2IsMuon){
                            tmpZ2LeadVec = eZ2VecPairAr[tmpZ2Ind][0];
                            tmpZ2TrailingVec = eZ2VecPairAr[tmpZ2Ind][1];
                        }
                        else{
                            tmpZ2LeadVec = mZ2VecPairAr[tmpZ2Ind][0];
                            tmpZ2TrailingVec = mZ2VecPairAr[tmpZ2Ind][1];
                        }
                        tmpZ2Vec = tmpZ2LeadVec+tmpZ2TrailingVec;
                        if (debug) std::cout << "After ifs \n";



                        lepZ1LeadPtL      = Z1LeadPt;
                        lepZ1TrailingPtL  = Z1TrailingPt;
                        lepZ1LeadPhiL     = Z1LeadVec.Phi();
                        lepZ1TrailingPhiL = Z1TrailingVec.Phi();
                        lepZ1PairInvMassL = tmpZ1M;
                        lepZ1LeadEtaL     = Z1LeadVec.Eta();
                        lepZ1TrailingEtaL = Z1TrailingVec.Eta();
                        lepZ1IsElectronL  = !Z1IsMuon;
                        lepZ1IsMuonL      = Z1IsMuon;
                        lepZ1LeadIsoL     = Z1LeadIso;
                        lepZ1TrailingIsoL = Z1TrailingIso;
                        lepZ1LeadSIPL     = Z1LeadSIP;
                        lepZ1TrailingSIPL = Z1TrailingSIP;
                        if (debug) std::cout << "after Z1 \n";

                        lepZ2LeadPtL      = tmpTopZ2LeadPt;
                        lepZ2TrailingPtL  = tmpTopZ2TrailingPt;
                        lepZ2LeadPhiL     = tmpZ2LeadVec.Phi();
                        lepZ2TrailingPhiL = tmpZ2TrailingVec.Phi();
                        lepZ2PairInvMassL = tmpZ2Vec.M();
                        lepZ2LeadEtaL     = tmpZ2LeadVec.Eta();
                        lepZ2TrailingEtaL = tmpZ2TrailingVec.Eta();
                        lepZ2IsElectronL  = !Z2IsMuon;
                        lepZ2IsMuonL      = Z2IsMuon;
                        lepZ2LeadIsoL     = Z2LeadIso;
                        lepZ2TrailingIsoL = Z2TrailingIso;
                        lepZ2LeadSIPL     = Z2LeadSIP;
                        lepZ2TrailingSIPL = Z2TrailingSIP;

                        lepChanHiggsFatJet_pt_fromHTagL = hFatJet_pt_fromHTag;
                        lepChanHiggsFatJet_phi_fromHTagL = hFatJet_phi_fromHTag;
                        lepChanHiggsFatJet_eta_fromHTagL = hFatJet_eta_fromHTag;
                        lepChanHiggsFatJet_mass_fromHTagL = hFatJet_mass_fromHTag;
                        lepChanHiggsFatJet_HTag_fromHTagL = hFatJet_HTag_fromHTag;


                        if (debug) std::cout << "after Z2 \n";
                        LepTree->Fill();
                        
                    }
                    
                    else if (passedAsSemiLepBool){
                        if (debug) std::cout << "Filling passed as semilep branch \n";
                        tmpZ1Vec = Z1LeadVec+Z1TrailingVec;
                        if (debug) std::cout << "First need to get iso info \n";
                        if (debug) std::cout << "Z1IsMuon " << Z1IsMuon <<" Z1LeadPt " <<Z1LeadPt<<"\n";
                        /*
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
                        */
                        if (debug) std::cout << "Now SIP info \n";

                        if (!Z1IsMuon){
                            Z1LeadSIP = Electron_sip3d[elecCandIndAr[Z1LeadItr]];
                            Z1TrailingSIP = Electron_sip3d[elecCandIndAr[Z1TrailingItr]];
                        }
                        else{
                            Z1LeadSIP = Muon_sip3d[muonCandIndAr[Z1LeadItr]];
                            Z1TrailingSIP = Muon_sip3d[muonCandIndAr[Z1TrailingItr]];
                        }
                        if (debug) std::cout << "now lep leaves \n";

                        
                        lepLeadPtL      = Z1LeadPt;
                        lepTrailingPtL  = Z1TrailingPt;
                        lepLeadPhiL     = Z1LeadVec.Phi();
                        lepTrailingPhiL = Z1TrailingVec.Phi();
                        lepPairInvMassL = tmpZ1Vec.M();
                        lepLeadEtaL     = Z1LeadVec.Eta();
                        lepTrailingEtaL = Z1TrailingVec.Eta();
                        lepIsElectronL  = !Z1IsMuon;
                        lepIsMuonL      = Z1IsMuon;
                        lepLeadIsoL     = Z1LeadIso;
                        lepTrailingIsoL = Z1TrailingIso;
                        lepLeadSIPL     = Z1LeadSIP;
                        lepTrailingSIPL = Z1TrailingSIP;
                        if (debug) std::cout << "now FJ leaves \n";

                        FJPtL      = FatJet_pt[FJInd];
                        FJPhiL     = FatJet_phi[FJInd];
                        FJMassL    = FatJet_mass[FJInd];
                        FJEtaL     = FatJet_eta[FJInd];

                        semiLepChanHiggsFatJet_pt_fromHTagL = hFatJet_pt_fromHTag;
                        semiLepChanHiggsFatJet_phi_fromHTagL = hFatJet_phi_fromHTag;
                        semiLepChanHiggsFatJet_eta_fromHTagL = hFatJet_eta_fromHTag;
                        semiLepChanHiggsFatJet_mass_fromHTagL = hFatJet_mass_fromHTag;
                        semiLepChanHiggsFatJet_HTag_fromHTagL = hFatJet_HTag_fromHTag;




                        if (debug) std::cout << "now filling \n";

                        SemiLepTree->Fill();
                        if (debug) std::cout << "Filled \n";
                    }


                    else if (passedAsHadBool){
                        if (debug) std::cout << "Filling passed as had branch \n";
                        
                        FJLeadPtL      = leadFatJetMaxPT;
                        FJTrailingPtL  = secondFatJetMaxPT;
                        FJLeadPhiL     = FatJet_phi[LFJOneInd];
                        FJTrailingPhiL = FatJet_phi[LFJTwoInd];
                        FJLeadMassL    = FatJet_mass[LFJOneInd];
                        FJTrailingMassL = FatJet_mass[LFJTwoInd];
                        FJPairInvMassL = FJInvMass;
                        FJLeadEtaL     = FatJet_eta[LFJOneInd];
                        FJTrailingEtaL = FatJet_eta[LFJTwoInd];
                        FJEtaSepL      = abs(FatJet_eta[LFJOneInd]-FatJet_eta[LFJTwoInd]);


                        hadChanHiggsFatJet_pt_fromHTagL = hFatJet_pt_fromHTag;
                        hadChanHiggsFatJet_phi_fromHTagL = hFatJet_phi_fromHTag;
                        hadChanHiggsFatJet_eta_fromHTagL = hFatJet_eta_fromHTag;
                        hadChanHiggsFatJet_mass_fromHTagL = hFatJet_mass_fromHTag;
                        hadChanHiggsFatJet_HTag_fromHTagL = hFatJet_HTag_fromHTag;

                        HadTree->Fill();
                    }
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
    std::cout << "passes hbb cut: " << passhbbCtr << " -------------------\n";
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
    std::cout << "trying lep cut: " << tryingLepCtr << "\n";
    std::cout << "trying semi lep cut: " << tryingSemiLepCtr << "\n";
    std::cout << "trying had cut: " << tryingHadCtr << "\n";
    std::cout << "passes lep cut: " << passLepCut << " -------------------\n";
    std::cout << "passes semi lep cut: " << passSemiLepCut << " -------------------\n";
    std::cout << "passes had cut: " << passHadCut << " -------------------\n";

    std::cout << "passes all cuts: " << passesCutsCtr << " -------------------\n";
    std::cout << "evPassCount: " << evPassCount << "\n";

    std::cout << "ZFJSameJetCtr " << ZFJSameJetCtr << "\n";
    std::cout << "ZJSameJetCtr " << ZJSameJetCtr << "\n";

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
    LepTree->Write("",TObject::kOverwrite);
    SemiLepTree->Write("",TObject::kOverwrite);
    HadTree->Write("",TObject::kOverwrite);
    if (useLHETree) {
        RawTree->Write("",TObject::kOverwrite);
        SelectedTree->Write("",TObject::kOverwrite);
        if (useFJGenMatchTree) {
            ZFJGenTree->Write("",TObject::kOverwrite);
            HFJGenTree->Write("",TObject::kOverwrite);
            ZHFJGenTree->Write("",TObject::kOverwrite);
            
        }
        if (useJGenMatchTree) {
            ZJGenTree->Write("",TObject::kOverwrite);
            ZHJGenTree->Write("",TObject::kOverwrite);
        }
        if (useJGenMatchTree || useFJGenMatchTree) {
            GenRawTree->Write("",TObject::kOverwrite);
        }

    }

    outFile->Close();
}