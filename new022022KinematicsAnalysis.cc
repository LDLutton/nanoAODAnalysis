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
#include "new022022KinematicsAnalysis.h"
#include "new022022KinematicsAnalysis_Functions.h"
#include "new022022KinematicsAnalysis_FileList.h"
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


void new022022KinematicsAnalysis(){
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

    if (MGOSix){
        saveName = "OSix";
        isBackground = false;
        int arrSize = sizeof(MGOSixAr)/sizeof(MGOSixAr[0]);
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = "/scratch365/dlutton/NanoAODFiles/pphzzjj_OSix_QCD0SMHLOOP0NPLE1NPcHE1_100Ev_0p4cH_100GeVIMJetCut/"+MGOSixAr[i];
            fileAr.push_back(tmpStrWithPath);
        }
        useLHETree = true;
        useFJGenMatchTree = true;
        useJGenMatchTree = true;
    }
    else if (MGOSixEtaDifCut){
        saveName = "OSix_EtaDifCut";
        isBackground = false;
        int arrSize = sizeof(MGOSixEtaDifCutAr)/sizeof(MGOSixEtaDifCutAr[0]);
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = "/scratch365/dlutton/NanoAODFiles/pphzzjj_OSix_QCD0SMHLOOP0NPLE1NPcHE1_100Ev_0p4cH_100GeVIMJetCut_2EtaDifCut/"+MGOSixEtaDifCutAr[i];
            fileAr.push_back(tmpStrWithPath);
        }
        useLHETree = true;
        useFJGenMatchTree = true;
        useJGenMatchTree = true;
    }
    else if (MGOHBox){
        saveName = "OHBox";
        isBackground = false;
        int arrSize = sizeof(MGOHBoxAr)/sizeof(MGOHBoxAr[0]);
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = "/scratch365/dlutton/NanoAODFiles/pphzzjj_OHBox_QCD0SMHLOOP0NPLE1NPcHBoxE1_100Ev_0p5cHBox_100GeVIMJetCut/"+MGOHBoxAr[i];
            fileAr.push_back(tmpStrWithPath);
        }
        useLHETree = true;
        useFJGenMatchTree = true;
        useJGenMatchTree = true;
    }
    else if (MGOHBoxEtaDifCut){
        saveName = "OHBox_EtaDifCut";
        isBackground = false;
        int arrSize = sizeof(MGOHBoxEtaDifCutAr)/sizeof(MGOHBoxEtaDifCutAr[0]);
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = "/scratch365/dlutton/NanoAODFiles/pphzzjj_OHBox_QCD0SMHLOOP0NPLE1NPcHBoxE1_100Ev_0p5cHBox_100GeVIMJetCut_2EtaDifCut/"+MGOHBoxEtaDifCutAr[i];
            fileAr.push_back(tmpStrWithPath);
        }
        useLHETree = true;
        useFJGenMatchTree = true;
        useJGenMatchTree = true;
    }
    else if (MGOHDD){
        saveName = "OHDD";
        isBackground = false;
        int arrSize = sizeof(MGOHDDAr)/sizeof(MGOHDDAr[0]);
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = "/scratch365/dlutton/NanoAODFiles/pphzzjj_OHDD_QCD0SMHLOOP0NPLE1NPcHDDE1_0p6cHDD_100GeVIMJetCut/"+MGOHDDAr[i];
            fileAr.push_back(tmpStrWithPath);
        }
        useLHETree = true;
        useFJGenMatchTree = true;
        useJGenMatchTree = true;
    }
    else if (MGOHDDEtaDifCut){
        saveName = "OHDD_EtaDifCut";
        isBackground = false;
        int arrSize = sizeof(MGOHDDEtaDifCutAr)/sizeof(MGOHDDEtaDifCutAr[0]);
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = "/scratch365/dlutton/NanoAODFiles/pphzzjj_OHDD_QCD0SMHLOOP0NPLE1NPcHDDE1_0p6cHDD_100GeVIMJetCut_2EtaDifCut/"+MGOHDDEtaDifCutAr[i];
            fileAr.push_back(tmpStrWithPath);
        }
        useLHETree = true;
        useFJGenMatchTree = true;
        useJGenMatchTree = true;
    }
    else if (testRun){
        saveName = "testRun";
        fileAr.push_back("./unweighted_eventspphzzjjQCD0SMHLOOP0NPE1NPcHWE1QEDE5ResMasAllVer100Ev10080Seed_0p999cHW100GeVIMJetCut_200.root");
        useLHETree = true;
        useFJGenMatchTree = true;
        useJGenMatchTree = true;
    }
    else{
        std::cout << "ERROR. NO INPUT DATASET NAME GIVEN\n";
    }

    std::cout << "Doing " << saveName << "\n";
    //Setting up outfile for tree
    std::string outFileStr = "KinematicsAnalysis"+saveName+cutName+".root";
    std::cout << "OutFile: " << outFileStr << "\n";
    TFile *outFile = new TFile(outFileStr.c_str(),"RECREATE");
    bool checkChannelSplits;
    if (isBackground){
        checkChannelSplits = false;
    }


    float HFJ_pt_FromGenMatchL;
    float HFJ_eta_FromGenMatchL;
    float HFJ_phi_FromGenMatchL;
    float HFJ_mass_FromGenMatchL;
    float HFJ_dRFromFJ_FromGenMatchL;

    UInt_t nHFJDecay_FromGenMatchL;
    std::vector<Int_t> HFJ_decaypdgId_FromGenMatchL;



    TTree *HFJGenTree = new TTree("HFJGenTree", "HFJGenTree");

    HFJGenTree->Branch("HFJ_pt_FromGenMatchL",&HFJ_pt_FromGenMatchL,"HFJ_pt_FromGenMatchL/F");
    HFJGenTree->Branch("HFJ_eta_FromGenMatchL",&HFJ_eta_FromGenMatchL,"HFJ_eta_FromGenMatchL/F");
    HFJGenTree->Branch("HFJ_phi_FromGenMatchL",&HFJ_phi_FromGenMatchL,"HFJ_phi_FromGenMatchL/F");
    HFJGenTree->Branch("HFJ_mass_FromGenMatchL",&HFJ_mass_FromGenMatchL,"HFJ_mass_FromGenMatchL/F");
    HFJGenTree->Branch("HFJ_dRFromFJ_FromGenMatchL",&HFJ_dRFromFJ_FromGenMatchL,"HFJ_dRFromFJ_FromGenMatchL/F");
    
    HFJGenTree->Branch("nHFJDecay_FromGenMatchL",&nHFJDecay_FromGenMatchL,"nHFJDecay_FromGenMatchL/i");
    HFJGenTree->Branch("HFJ_decaypdgId_FromGenMatchL",&HFJ_decaypdgId_FromGenMatchL);


    UInt_t ZFJSameJetCtr = 0;

    float ZFJLead_pt_FromGenMatchL;
    float ZFJLead_eta_FromGenMatchL;
    float ZFJLead_phi_FromGenMatchL;
    float ZFJLead_mass_FromGenMatchL;
    float ZFJLead_dRFromFJ_FromGenMatchL;

    UInt_t nZFJLeadDecay_FromGenMatchL;
    std::vector<Int_t> ZFJLead_decaypdgId_FromGenMatchL;
    

    float ZFJTrailing_pt_FromGenMatchL;
    float ZFJTrailing_eta_FromGenMatchL;
    float ZFJTrailing_phi_FromGenMatchL;
    float ZFJTrailing_mass_FromGenMatchL;
    float ZFJTrailing_dRFromFJ_FromGenMatchL;

    UInt_t nZFJTrailingDecay_FromGenMatchL;
    std::vector<Int_t> ZFJTrailing_decaypdgId_FromGenMatchL;

    float ZFJPair_InvMass_FromGenMatchL;
    float ZFJPair_EtaSep_FromGenMatchL;

    TTree *ZFJGenTree = new TTree("ZFJGenTree", "ZFJGenTree");

    ZFJGenTree->Branch("ZFJLead_pt_FromGenMatchL",&ZFJLead_pt_FromGenMatchL,"ZFJLead_pt_FromGenMatchL/F");
    ZFJGenTree->Branch("ZFJLead_eta_FromGenMatchL",&ZFJLead_eta_FromGenMatchL,"ZFJLead_eta_FromGenMatchL/F");
    ZFJGenTree->Branch("ZFJLead_phi_FromGenMatchL",&ZFJLead_phi_FromGenMatchL,"ZFJLead_phi_FromGenMatchL/F");
    ZFJGenTree->Branch("ZFJLead_mass_FromGenMatchL",&ZFJLead_mass_FromGenMatchL,"ZFJLead_mass_FromGenMatchL/F");
    ZFJGenTree->Branch("ZFJLead_dRFromFJ_FromGenMatchL",&ZFJLead_dRFromFJ_FromGenMatchL,"ZFJLead_dRFromFJ_FromGenMatchL/F");

    ZFJGenTree->Branch("nZFJLeadDecay_FromGenMatchL",&nZFJLeadDecay_FromGenMatchL,"nZFJLeadDecay_FromGenMatchL/i");
    //ZFJGenTree->Branch("ZFJLead_decaypdgId_FromGenMatchL",&ZFJLead_decaypdgId_FromGenMatchL,"ZFJLead_decaypdgId_FromGenMatchL[nZFJLeadDecay_FromGenMatchL]/I");
    ZFJGenTree->Branch("ZFJLead_decaypdgId_FromGenMatchL",&ZFJLead_decaypdgId_FromGenMatchL);


    ZFJGenTree->Branch("ZFJTrailing_pt_FromGenMatchL",&ZFJTrailing_pt_FromGenMatchL,"ZFJTrailing_pt_FromGenMatchL/F");
    ZFJGenTree->Branch("ZFJTrailing_eta_FromGenMatchL",&ZFJTrailing_eta_FromGenMatchL,"ZFJTrailing_eta_FromGenMatchL/F");
    ZFJGenTree->Branch("ZFJTrailing_phi_FromGenMatchL",&ZFJTrailing_phi_FromGenMatchL,"ZFJTrailing_phi_FromGenMatchL/F");
    ZFJGenTree->Branch("ZFJTrailing_mass_FromGenMatchL",&ZFJTrailing_mass_FromGenMatchL,"ZFJTrailing_mass_FromGenMatchL/F");
    ZFJGenTree->Branch("ZFJTrailing_dRFromFJ_FromGenMatchL",&ZFJTrailing_dRFromFJ_FromGenMatchL,"ZFJTrailing_dRFromFJ_FromGenMatchL/F");

    ZFJGenTree->Branch("nZFJTrailingDecay_FromGenMatchL",&nZFJTrailingDecay_FromGenMatchL,"nZFJTrailingDecay_FromGenMatchL/i");
    //ZFJGenTree->Branch("ZFJTrailing_decaypdgId_FromGenMatchL",&ZFJTrailing_decaypdgId_FromGenMatchL,"ZFJTrailing_decaypdgId_FromGenMatchL[nZFJTrailingDecay_FromGenMatchL]/I");
    ZFJGenTree->Branch("ZFJTrailing_decaypdgId_FromGenMatchL",&ZFJTrailing_decaypdgId_FromGenMatchL);


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

    UInt_t nZJLeadDecay_FromGenMatchL;
    std::vector<Int_t> ZJLead_decaypdgId_FromGenMatchL;
    

    float ZJTrailing_pt_FromGenMatchL;
    float ZJTrailing_eta_FromGenMatchL;
    float ZJTrailing_phi_FromGenMatchL;
    float ZJTrailing_mass_FromGenMatchL;
    float ZJTrailing_dRFromJ_FromGenMatchL;

    UInt_t nZJTrailingDecay_FromGenMatchL;
    std::vector<Int_t> ZJTrailing_decaypdgId_FromGenMatchL;

    float ZJPair_InvMass_FromGenMatchL;
    float ZJPair_EtaSep_FromGenMatchL;

    TTree *ZJGenTree = new TTree("ZJGenTree", "ZJGenTree");

    ZJGenTree->Branch("ZJLead_pt_FromGenMatchL",&ZJLead_pt_FromGenMatchL,"ZJLead_pt_FromGenMatchL/F");
    ZJGenTree->Branch("ZJLead_eta_FromGenMatchL",&ZJLead_eta_FromGenMatchL,"ZJLead_eta_FromGenMatchL/F");
    ZJGenTree->Branch("ZJLead_phi_FromGenMatchL",&ZJLead_phi_FromGenMatchL,"ZJLead_phi_FromGenMatchL/F");
    ZJGenTree->Branch("ZJLead_mass_FromGenMatchL",&ZJLead_mass_FromGenMatchL,"ZJLead_mass_FromGenMatchL/F");
    ZJGenTree->Branch("ZJLead_dRFromJ_FromGenMatchL",&ZJLead_dRFromJ_FromGenMatchL,"ZJLead_dRFromJ_FromGenMatchL/F");

    ZJGenTree->Branch("nZJLeadDecay_FromGenMatchL",&nZJLeadDecay_FromGenMatchL,"nZJLeadDecay_FromGenMatchL/i");
    //ZJGenTree->Branch("ZJLead_decaypdgId_FromGenMatchL",&ZJLead_decaypdgId_FromGenMatchL,"ZJLead_decaypdgId_FromGenMatchL[nZJLeadDecay_FromGenMatchL]/I");
    ZJGenTree->Branch("ZJLead_decaypdgId_FromGenMatchL",&ZJLead_decaypdgId_FromGenMatchL);

    ZJGenTree->Branch("ZJTrailing_pt_FromGenMatchL",&ZJTrailing_pt_FromGenMatchL,"ZJTrailing_pt_FromGenMatchL/F");
    ZJGenTree->Branch("ZJTrailing_eta_FromGenMatchL",&ZJTrailing_eta_FromGenMatchL,"ZJTrailing_eta_FromGenMatchL/F");
    ZJGenTree->Branch("ZJTrailing_phi_FromGenMatchL",&ZJTrailing_phi_FromGenMatchL,"ZJTrailing_phi_FromGenMatchL/F");
    ZJGenTree->Branch("ZJTrailing_mass_FromGenMatchL",&ZJTrailing_mass_FromGenMatchL,"ZJTrailing_mass_FromGenMatchL/F");
    ZJGenTree->Branch("ZJTrailing_dRFromJ_FromGenMatchL",&ZJTrailing_dRFromJ_FromGenMatchL,"ZJTrailing_dRFromJ_FromGenMatchL/F");

    ZJGenTree->Branch("nZJTrailingDecay_FromGenMatchL",&nZJTrailingDecay_FromGenMatchL,"nZJTrailingDecay_FromGenMatchL/i");
    ZJGenTree->Branch("ZJTrailing_decaypdgId_FromGenMatchL",&ZJTrailing_decaypdgId_FromGenMatchL);


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

    UInt_t nZOneDecay_FromGenRawL;
    std::vector<Int_t> ZOne_decaypdgId_FromGenRawL;

    float ZTwo_pt_FromGenRawL;
    float ZTwo_eta_FromGenRawL;
    float ZTwo_phi_FromGenRawL;
    float ZTwo_mass_FromGenRawL;
    float ZTwo_pdgId_FromGenRawL;
    float ZTwo_genPartIdxMother_FromGenRawL;

    UInt_t nZTwoDecay_FromGenRawL;
    std::vector<Int_t> ZTwo_decaypdgId_FromGenRawL;

    float ZPair_InvMass_FromGenRawL;
    float ZPair_EtaSep_FromGenRawL;

    float H_pt_FromGenRawL;
    float H_eta_FromGenRawL;
    float H_phi_FromGenRawL;
    float H_mass_FromGenRawL;
    float H_pdgId_FromGenRawL;
    float H_genPartIdxMother_FromGenRawL;

    UInt_t nHDecay_FromGenRawL;
    std::vector<Int_t> H_decaypdgId_FromGenRawL;

    float ZPairPlusH_InvMass_FromGenRawL;

    TTree *GenRawTree = new TTree("GenRawTree", "GenRawTree");

    GenRawTree->Branch("ZOne_pt_FromGenRawL",&ZOne_pt_FromGenRawL,"ZOne_pt_FromGenRawL/F");
    GenRawTree->Branch("ZOne_eta_FromGenRawL",&ZOne_eta_FromGenRawL,"ZOne_eta_FromGenRawL/F");
    GenRawTree->Branch("ZOne_phi_FromGenRawL",&ZOne_phi_FromGenRawL,"ZOne_phi_FromGenRawL/F");
    GenRawTree->Branch("ZOne_mass_FromGenRawL",&ZOne_mass_FromGenRawL,"ZOne_mass_FromGenRawL/F");
    GenRawTree->Branch("ZOne_pdgId_FromGenRawL",&ZOne_pdgId_FromGenRawL,"ZOne_pdgId_FromGenRawL/F");
    GenRawTree->Branch("ZOne_genPartIdxMother_FromGenRawL",&ZOne_genPartIdxMother_FromGenRawL,"ZOne_genPartIdxMother_FromGenRawL/F");

    GenRawTree->Branch("nZOneDecay_FromGenRawL",&nZOneDecay_FromGenRawL,"nZOneDecay_FromGenRawL/i");
    GenRawTree->Branch("ZOne_decaypdgId_FromGenRawL",&ZOne_decaypdgId_FromGenRawL);

    GenRawTree->Branch("ZTwo_pt_FromGenRawL",&ZTwo_pt_FromGenRawL,"ZTwo_pt_FromGenRawL/F");
    GenRawTree->Branch("ZTwo_eta_FromGenRawL",&ZTwo_eta_FromGenRawL,"ZTwo_eta_FromGenRawL/F");
    GenRawTree->Branch("ZTwo_phi_FromGenRawL",&ZTwo_phi_FromGenRawL,"ZTwo_phi_FromGenRawL/F");
    GenRawTree->Branch("ZTwo_mass_FromGenRawL",&ZTwo_mass_FromGenRawL,"ZTwo_mass_FromGenRawL/F");
    GenRawTree->Branch("ZTwo_pdgId_FromGenRawL",&ZTwo_pdgId_FromGenRawL,"ZTwo_pdgId_FromGenRawL/F");
    GenRawTree->Branch("ZTwo_genPartIdxMother_FromGenRawL",&ZTwo_genPartIdxMother_FromGenRawL,"ZTwo_genPartIdxMother_FromGenRawL/F");

    GenRawTree->Branch("nZTwoDecay_FromGenRawL",&nZTwoDecay_FromGenRawL,"nZTwoDecay_FromGenRawL/i");
    GenRawTree->Branch("ZTwo_decaypdgId_FromGenRawL",&ZTwo_decaypdgId_FromGenRawL);

    GenRawTree->Branch("ZPair_InvMass_FromGenRawL",&ZPair_InvMass_FromGenRawL,"ZPair_InvMass_FromGenRawL/F");
    GenRawTree->Branch("ZPair_EtaSep_FromGenRawL",&ZPair_EtaSep_FromGenRawL,"ZPair_EtaSep_FromGenRawL/F");

    GenRawTree->Branch("H_pt_FromGenRawL",&H_pt_FromGenRawL,"H_pt_FromGenRawL/F");
    GenRawTree->Branch("H_eta_FromGenRawL",&H_eta_FromGenRawL,"H_eta_FromGenRawL/F");
    GenRawTree->Branch("H_phi_FromGenRawL",&H_phi_FromGenRawL,"H_phi_FromGenRawL/F");
    GenRawTree->Branch("H_mass_FromGenRawL",&H_mass_FromGenRawL,"H_mass_FromGenRawL/F");
    GenRawTree->Branch("H_pdgId_FromGenRawL",&H_pdgId_FromGenRawL,"H_pdgId_FromGenRawL/F");
    GenRawTree->Branch("H_genPartIdxMother_FromGenRawL",&H_genPartIdxMother_FromGenRawL,"H_genPartIdxMother_FromGenRawL/F");

    GenRawTree->Branch("nHDecay_FromGenRawL",&nHDecay_FromGenRawL,"nHDecay_FromGenRawL/i");
    GenRawTree->Branch("H_decaypdgId_FromGenRawL",&H_decaypdgId_FromGenRawL);

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





    float HFJ_pt_FromTaggedGenMatchL;
    float HFJ_eta_FromTaggedGenMatchL;
    float HFJ_phi_FromTaggedGenMatchL;
    float HFJ_mass_FromTaggedGenMatchL;
    float HFJ_dRFromFJ_FromTaggedGenMatchL;

    UInt_t nHFJDecay_FromTaggedGenMatchL;
    std::vector<Int_t> HFJ_decaypdgId_FromTaggedGenMatchL;



    TTree *HFJGenTaggedTree = new TTree("HFJGenTaggedTree", "HFJGenTaggedTree");

    HFJGenTaggedTree->Branch("HFJ_pt_FromTaggedGenMatchL",&HFJ_pt_FromTaggedGenMatchL,"HFJ_pt_FromTaggedGenMatchL/F");
    HFJGenTaggedTree->Branch("HFJ_eta_FromTaggedGenMatchL",&HFJ_eta_FromTaggedGenMatchL,"HFJ_eta_FromTaggedGenMatchL/F");
    HFJGenTaggedTree->Branch("HFJ_phi_FromTaggedGenMatchL",&HFJ_phi_FromTaggedGenMatchL,"HFJ_phi_FromTaggedGenMatchL/F");
    HFJGenTaggedTree->Branch("HFJ_mass_FromTaggedGenMatchL",&HFJ_mass_FromTaggedGenMatchL,"HFJ_mass_FromTaggedGenMatchL/F");
    HFJGenTaggedTree->Branch("HFJ_dRFromFJ_FromTaggedGenMatchL",&HFJ_dRFromFJ_FromTaggedGenMatchL,"HFJ_dRFromFJ_FromTaggedGenMatchL/F");

    HFJGenTaggedTree->Branch("nHFJDecay_FromTaggedGenMatchL",&nHFJDecay_FromTaggedGenMatchL,"nHFJDecay_FromTaggedGenMatchL/i");
    HFJGenTaggedTree->Branch("HFJ_decaypdgId_FromTaggedGenMatchL",&HFJ_decaypdgId_FromTaggedGenMatchL);


    UInt_t ZFJSameJetTaggedCtr = 0;

    float ZFJLead_pt_FromTaggedGenMatchL;
    float ZFJLead_eta_FromTaggedGenMatchL;
    float ZFJLead_phi_FromTaggedGenMatchL;
    float ZFJLead_mass_FromTaggedGenMatchL;
    float ZFJLead_dRFromFJ_FromTaggedGenMatchL;

    UInt_t nZFJLeadDecay_FromTaggedGenMatchL;
    std::vector<Int_t> ZFJLead_decaypdgId_FromTaggedGenMatchL;
    

    float ZFJTrailing_pt_FromTaggedGenMatchL;
    float ZFJTrailing_eta_FromTaggedGenMatchL;
    float ZFJTrailing_phi_FromTaggedGenMatchL;
    float ZFJTrailing_mass_FromTaggedGenMatchL;
    float ZFJTrailing_dRFromFJ_FromTaggedGenMatchL;

    UInt_t nZFJTrailingDecay_FromTaggedGenMatchL;
    std::vector<Int_t> ZFJTrailing_decaypdgId_FromTaggedGenMatchL;

    float ZFJPair_InvMass_FromTaggedGenMatchL;
    float ZFJPair_EtaSep_FromTaggedGenMatchL;

    TTree *ZFJGenTaggedTree = new TTree("ZFJGenTaggedTree", "ZFJGenTaggedTree");

    ZFJGenTaggedTree->Branch("ZFJLead_pt_FromTaggedGenMatchL",&ZFJLead_pt_FromTaggedGenMatchL,"ZFJLead_pt_FromTaggedGenMatchL/F");
    ZFJGenTaggedTree->Branch("ZFJLead_eta_FromTaggedGenMatchL",&ZFJLead_eta_FromTaggedGenMatchL,"ZFJLead_eta_FromTaggedGenMatchL/F");
    ZFJGenTaggedTree->Branch("ZFJLead_phi_FromTaggedGenMatchL",&ZFJLead_phi_FromTaggedGenMatchL,"ZFJLead_phi_FromTaggedGenMatchL/F");
    ZFJGenTaggedTree->Branch("ZFJLead_mass_FromTaggedGenMatchL",&ZFJLead_mass_FromTaggedGenMatchL,"ZFJLead_mass_FromTaggedGenMatchL/F");
    ZFJGenTaggedTree->Branch("ZFJLead_dRFromFJ_FromTaggedGenMatchL",&ZFJLead_dRFromFJ_FromTaggedGenMatchL,"ZFJLead_dRFromFJ_FromTaggedGenMatchL/F");

    ZFJGenTaggedTree->Branch("nZFJLeadDecay_FromTaggedGenMatchL",&nZFJLeadDecay_FromTaggedGenMatchL,"nZFJLeadDecay_FromTaggedGenMatchL/i");
    ZFJGenTaggedTree->Branch("ZFJLead_decaypdgId_FromTaggedGenMatchL",&ZFJLead_decaypdgId_FromTaggedGenMatchL);

    ZFJGenTaggedTree->Branch("ZFJTrailing_pt_FromTaggedGenMatchL",&ZFJTrailing_pt_FromTaggedGenMatchL,"ZFJTrailing_pt_FromTaggedGenMatchL/F");
    ZFJGenTaggedTree->Branch("ZFJTrailing_eta_FromTaggedGenMatchL",&ZFJTrailing_eta_FromTaggedGenMatchL,"ZFJTrailing_eta_FromTaggedGenMatchL/F");
    ZFJGenTaggedTree->Branch("ZFJTrailing_phi_FromTaggedGenMatchL",&ZFJTrailing_phi_FromTaggedGenMatchL,"ZFJTrailing_phi_FromTaggedGenMatchL/F");
    ZFJGenTaggedTree->Branch("ZFJTrailing_mass_FromTaggedGenMatchL",&ZFJTrailing_mass_FromTaggedGenMatchL,"ZFJTrailing_mass_FromTaggedGenMatchL/F");
    ZFJGenTaggedTree->Branch("ZFJTrailing_dRFromFJ_FromTaggedGenMatchL",&ZFJTrailing_dRFromFJ_FromTaggedGenMatchL,"ZFJTrailing_dRFromFJ_FromTaggedGenMatchL/F");

    ZFJGenTaggedTree->Branch("nZFJTrailingDecay_FromTaggedGenMatchL",&nZFJTrailingDecay_FromTaggedGenMatchL,"nZFJTrailingDecay_FromTaggedGenMatchL/i");
    ZFJGenTaggedTree->Branch("ZFJTrailing_decaypdgId_FromTaggedGenMatchL",&ZFJTrailing_decaypdgId_FromTaggedGenMatchL);

    ZFJGenTaggedTree->Branch("ZFJPair_InvMass_FromTaggedGenMatchL",&ZFJPair_InvMass_FromTaggedGenMatchL,"ZFJPair_InvMass_FromTaggedGenMatchL/F");
    ZFJGenTaggedTree->Branch("ZFJPair_EtaSep_FromTaggedGenMatchL",&ZFJPair_EtaSep_FromTaggedGenMatchL,"ZFJPair_EtaSep_FromTaggedGenMatchL/F");

    float ZHFJ_ZPairPlusHInvMass_FromTaggedGenMatchL;
    TTree *ZHFJGenTaggedTree = new TTree("ZHFJGenTaggedTree", "ZHFJGenTaggedTree");
    ZHFJGenTaggedTree->Branch("ZHFJ_ZPairPlusHInvMass_FromTaggedGenMatchL",&ZHFJ_ZPairPlusHInvMass_FromTaggedGenMatchL,"ZHFJ_ZPairPlusHInvMass_FromTaggedGenMatchL/F");

    float ZHJ_ZPairPlusHInvMass_FromTaggedGenMatchL;
    TTree *ZHJGenTaggedTree = new TTree("ZHJGenTaggedTree", "ZHJGenTaggedTree");
    ZHJGenTaggedTree->Branch("ZHJ_ZPairPlusHInvMass_FromTaggedGenMatchL",&ZHJ_ZPairPlusHInvMass_FromTaggedGenMatchL,"ZHJ_ZPairPlusHInvMass_FromTaggedGenMatchL/F");





    UInt_t ZJSameJetTaggedCtr = 0;


    float ZJLead_pt_FromTaggedGenMatchL;
    float ZJLead_eta_FromTaggedGenMatchL;
    float ZJLead_phi_FromTaggedGenMatchL;
    float ZJLead_mass_FromTaggedGenMatchL;
    float ZJLead_dRFromJ_FromTaggedGenMatchL;

    UInt_t nZJLeadDecay_FromTaggedGenMatchL;
    std::vector<Int_t> ZJLead_decaypdgId_FromTaggedGenMatchL;
    

    float ZJTrailing_pt_FromTaggedGenMatchL;
    float ZJTrailing_eta_FromTaggedGenMatchL;
    float ZJTrailing_phi_FromTaggedGenMatchL;
    float ZJTrailing_mass_FromTaggedGenMatchL;
    float ZJTrailing_dRFromJ_FromTaggedGenMatchL;

    UInt_t nZJTrailingDecay_FromTaggedGenMatchL;
    std::vector<Int_t> ZJTrailing_decaypdgId_FromTaggedGenMatchL;

    float ZJPair_InvMass_FromTaggedGenMatchL;
    float ZJPair_EtaSep_FromTaggedGenMatchL;

    TTree *ZJGenTaggedTree = new TTree("ZJGenTaggedTree", "ZJGenTaggedTree");

    ZJGenTaggedTree->Branch("ZJLead_pt_FromTaggedGenMatchL",&ZJLead_pt_FromTaggedGenMatchL,"ZJLead_pt_FromTaggedGenMatchL/F");
    ZJGenTaggedTree->Branch("ZJLead_eta_FromTaggedGenMatchL",&ZJLead_eta_FromTaggedGenMatchL,"ZJLead_eta_FromTaggedGenMatchL/F");
    ZJGenTaggedTree->Branch("ZJLead_phi_FromTaggedGenMatchL",&ZJLead_phi_FromTaggedGenMatchL,"ZJLead_phi_FromTaggedGenMatchL/F");
    ZJGenTaggedTree->Branch("ZJLead_mass_FromTaggedGenMatchL",&ZJLead_mass_FromTaggedGenMatchL,"ZJLead_mass_FromTaggedGenMatchL/F");
    ZJGenTaggedTree->Branch("ZJLead_dRFromJ_FromTaggedGenMatchL",&ZJLead_dRFromJ_FromTaggedGenMatchL,"ZJLead_dRFromJ_FromTaggedGenMatchL/F");

    ZJGenTaggedTree->Branch("nZJLeadDecay_FromTaggedGenMatchL",&nZJLeadDecay_FromTaggedGenMatchL,"nZJLeadDecay_FromTaggedGenMatchL/i");
    ZJGenTaggedTree->Branch("ZJLead_decaypdgId_FromTaggedGenMatchL",&ZJLead_decaypdgId_FromTaggedGenMatchL);

    ZJGenTaggedTree->Branch("ZJTrailing_pt_FromTaggedGenMatchL",&ZJTrailing_pt_FromTaggedGenMatchL,"ZJTrailing_pt_FromTaggedGenMatchL/F");
    ZJGenTaggedTree->Branch("ZJTrailing_eta_FromTaggedGenMatchL",&ZJTrailing_eta_FromTaggedGenMatchL,"ZJTrailing_eta_FromTaggedGenMatchL/F");
    ZJGenTaggedTree->Branch("ZJTrailing_phi_FromTaggedGenMatchL",&ZJTrailing_phi_FromTaggedGenMatchL,"ZJTrailing_phi_FromTaggedGenMatchL/F");
    ZJGenTaggedTree->Branch("ZJTrailing_mass_FromTaggedGenMatchL",&ZJTrailing_mass_FromTaggedGenMatchL,"ZJTrailing_mass_FromTaggedGenMatchL/F");
    ZJGenTaggedTree->Branch("ZJTrailing_dRFromJ_FromTaggedGenMatchL",&ZJTrailing_dRFromJ_FromTaggedGenMatchL,"ZJTrailing_dRFromJ_FromTaggedGenMatchL/F");

    ZJGenTaggedTree->Branch("nZJTrailingDecay_FromTaggedGenMatchL",&nZJTrailingDecay_FromTaggedGenMatchL,"nZJTrailingDecay_FromTaggedGenMatchL/i");
    ZJGenTaggedTree->Branch("ZJTrailing_decaypdgId_FromTaggedGenMatchL",&ZJTrailing_decaypdgId_FromTaggedGenMatchL);

    ZJGenTaggedTree->Branch("ZJPair_InvMass_FromTaggedGenMatchL",&ZJPair_InvMass_FromTaggedGenMatchL,"ZJPair_InvMass_FromTaggedGenMatchL/F");
    ZJGenTaggedTree->Branch("ZJPair_EtaSep_FromTaggedGenMatchL",&ZJPair_EtaSep_FromTaggedGenMatchL,"ZJPair_EtaSep_FromTaggedGenMatchL/F");





    //This tree is for gen variables before the cuts
    //Can only use this on EFT and SM, not background


    float ZOne_pt_FromTaggedGenRawL;
    float ZOne_eta_FromTaggedGenRawL;
    float ZOne_phi_FromTaggedGenRawL;
    float ZOne_mass_FromTaggedGenRawL;
    float ZOne_pdgId_FromTaggedGenRawL;
    float ZOne_genPartIdxMother_FromTaggedGenRawL;

    UInt_t nZOneDecay_FromTaggedGenRawL;
    std::vector<Int_t> ZOne_decaypdgId_FromTaggedGenRawL;

    float ZTwo_pt_FromTaggedGenRawL;
    float ZTwo_eta_FromTaggedGenRawL;
    float ZTwo_phi_FromTaggedGenRawL;
    float ZTwo_mass_FromTaggedGenRawL;
    float ZTwo_pdgId_FromTaggedGenRawL;
    float ZTwo_genPartIdxMother_FromTaggedGenRawL;

    UInt_t nZTwoDecay_FromTaggedGenRawL;
    std::vector<Int_t> ZTwo_decaypdgId_FromTaggedGenRawL;

    float ZPair_InvMass_FromTaggedGenRawL;
    float ZPair_EtaSep_FromTaggedGenRawL;

    float H_pt_FromTaggedGenRawL;
    float H_eta_FromTaggedGenRawL;
    float H_phi_FromTaggedGenRawL;
    float H_mass_FromTaggedGenRawL;
    float H_pdgId_FromTaggedGenRawL;
    float H_genPartIdxMother_FromTaggedGenRawL;

    UInt_t nHDecay_FromTaggedGenRawL;
    std::vector<Int_t> H_decaypdgId_FromTaggedGenRawL;

    float ZPairPlusH_InvMass_FromTaggedGenRawL;

    TTree *GenRawTaggedTree = new TTree("GenRawTaggedTree", "GenRawTaggedTree");

    GenRawTaggedTree->Branch("ZOne_pt_FromTaggedGenRawL",&ZOne_pt_FromTaggedGenRawL,"ZOne_pt_FromTaggedGenRawL/F");
    GenRawTaggedTree->Branch("ZOne_eta_FromTaggedGenRawL",&ZOne_eta_FromTaggedGenRawL,"ZOne_eta_FromTaggedGenRawL/F");
    GenRawTaggedTree->Branch("ZOne_phi_FromTaggedGenRawL",&ZOne_phi_FromTaggedGenRawL,"ZOne_phi_FromTaggedGenRawL/F");
    GenRawTaggedTree->Branch("ZOne_mass_FromTaggedGenRawL",&ZOne_mass_FromTaggedGenRawL,"ZOne_mass_FromTaggedGenRawL/F");
    GenRawTaggedTree->Branch("ZOne_pdgId_FromTaggedGenRawL",&ZOne_pdgId_FromTaggedGenRawL,"ZOne_pdgId_FromTaggedGenRawL/F");
    GenRawTaggedTree->Branch("ZOne_genPartIdxMother_FromTaggedGenRawL",&ZOne_genPartIdxMother_FromTaggedGenRawL,"ZOne_genPartIdxMother_FromTaggedGenRawL/F");

    GenRawTaggedTree->Branch("nZOneDecay_FromTaggedGenRawL",&nZOneDecay_FromTaggedGenRawL,"nZOneDecay_FromTaggedGenRawL/i");
    GenRawTaggedTree->Branch("ZOne_decaypdgId_FromTaggedGenRawL",&ZOne_decaypdgId_FromTaggedGenRawL);

    GenRawTaggedTree->Branch("ZTwo_pt_FromTaggedGenRawL",&ZTwo_pt_FromTaggedGenRawL,"ZTwo_pt_FromTaggedGenRawL/F");
    GenRawTaggedTree->Branch("ZTwo_eta_FromTaggedGenRawL",&ZTwo_eta_FromTaggedGenRawL,"ZTwo_eta_FromTaggedGenRawL/F");
    GenRawTaggedTree->Branch("ZTwo_phi_FromTaggedGenRawL",&ZTwo_phi_FromTaggedGenRawL,"ZTwo_phi_FromTaggedGenRawL/F");
    GenRawTaggedTree->Branch("ZTwo_mass_FromTaggedGenRawL",&ZTwo_mass_FromTaggedGenRawL,"ZTwo_mass_FromTaggedGenRawL/F");
    GenRawTaggedTree->Branch("ZTwo_pdgId_FromTaggedGenRawL",&ZTwo_pdgId_FromTaggedGenRawL,"ZTwo_pdgId_FromTaggedGenRawL/F");
    GenRawTaggedTree->Branch("ZTwo_genPartIdxMother_FromTaggedGenRawL",&ZTwo_genPartIdxMother_FromTaggedGenRawL,"ZTwo_genPartIdxMother_FromTaggedGenRawL/F");

    GenRawTaggedTree->Branch("nZTwoDecay_FromTaggedGenRawL",&nZTwoDecay_FromTaggedGenRawL,"nZTwoDecay_FromTaggedGenRawL/i");
    GenRawTaggedTree->Branch("ZTwo_decaypdgId_FromTaggedGenRawL",&ZTwo_decaypdgId_FromTaggedGenRawL);

    GenRawTaggedTree->Branch("ZPair_InvMass_FromTaggedGenRawL",&ZPair_InvMass_FromTaggedGenRawL,"ZPair_InvMass_FromTaggedGenRawL/F");
    GenRawTaggedTree->Branch("ZPair_EtaSep_FromTaggedGenRawL",&ZPair_EtaSep_FromTaggedGenRawL,"ZPair_EtaSep_FromTaggedGenRawL/F");

    GenRawTaggedTree->Branch("H_pt_FromTaggedGenRawL",&H_pt_FromTaggedGenRawL,"H_pt_FromTaggedGenRawL/F");
    GenRawTaggedTree->Branch("H_eta_FromTaggedGenRawL",&H_eta_FromTaggedGenRawL,"H_eta_FromTaggedGenRawL/F");
    GenRawTaggedTree->Branch("H_phi_FromTaggedGenRawL",&H_phi_FromTaggedGenRawL,"H_phi_FromTaggedGenRawL/F");
    GenRawTaggedTree->Branch("H_mass_FromTaggedGenRawL",&H_mass_FromTaggedGenRawL,"H_mass_FromTaggedGenRawL/F");
    GenRawTaggedTree->Branch("H_pdgId_FromTaggedGenRawL",&H_pdgId_FromTaggedGenRawL,"H_pdgId_FromTaggedGenRawL/F");
    GenRawTaggedTree->Branch("H_genPartIdxMother_FromTaggedGenRawL",&H_genPartIdxMother_FromTaggedGenRawL,"H_genPartIdxMother_FromTaggedGenRawL/F");

    GenRawTaggedTree->Branch("nHDecay_FromTaggedGenRawL",&nHDecay_FromTaggedGenRawL,"nHDecay_FromTaggedGenRawL/i");
    GenRawTaggedTree->Branch("H_decaypdgId_FromTaggedGenRawL",&H_decaypdgId_FromTaggedGenRawL);

    GenRawTaggedTree->Branch("ZPairPlusH_InvMass_FromTaggedGenRawL",&ZPairPlusH_InvMass_FromTaggedGenRawL,"ZPairPlusH_InvMass_FromTaggedGenRawL/F");



    //This tree is for variables before the cuts
    //Can only use this on EFT and SM, not background


    float ZOne_pt_FromTaggedLHERawL;
    float ZOne_eta_FromTaggedLHERawL;
    float ZOne_phi_FromTaggedLHERawL;
    float ZOne_mass_FromTaggedLHERawL;

    float ZTwo_pt_FromTaggedLHERawL;
    float ZTwo_eta_FromTaggedLHERawL;
    float ZTwo_phi_FromTaggedLHERawL;
    float ZTwo_mass_FromTaggedLHERawL;

    float ZPair_InvMass_FromTaggedLHERawL;
    float ZPair_EtaSep_FromTaggedLHERawL;

    float H_pt_FromTaggedLHERawL;
    float H_eta_FromTaggedLHERawL;
    float H_phi_FromTaggedLHERawL;
    float H_mass_FromTaggedLHERawL;

    float ZPairPlusH_InvMass_FromTaggedLHERawL;

    float JOne_pt_FromTaggedLHERawL;
    float JOne_eta_FromTaggedLHERawL;
    float JOne_phi_FromTaggedLHERawL;
    float JOne_pdgId_FromTaggedLHERawL;

    float JTwo_pt_FromTaggedLHERawL;
    float JTwo_eta_FromTaggedLHERawL;
    float JTwo_phi_FromTaggedLHERawL;
    float JTwo_pdgId_FromTaggedLHERawL;

    float JOne_invmass_FromTaggedLHERawL;
    float JTwo_invmass_FromTaggedLHERawL;

    
    

    float JPair_invmass_FromTaggedLHERawL;
    float J_etasep_FromTaggedLHERawL;

    TTree *RawTaggedTree = new TTree("RawTaggedTree", "RawTaggedTree");

    RawTaggedTree->Branch("ZOne_pt_FromTaggedLHERawL",&ZOne_pt_FromTaggedLHERawL,"ZOne_pt_FromTaggedLHERawL/F");
    RawTaggedTree->Branch("ZOne_eta_FromTaggedLHERawL",&ZOne_eta_FromTaggedLHERawL,"ZOne_eta_FromTaggedLHERawL/F");
    RawTaggedTree->Branch("ZOne_phi_FromTaggedLHERawL",&ZOne_phi_FromTaggedLHERawL,"ZOne_phi_FromTaggedLHERawL/F");
    RawTaggedTree->Branch("ZOne_mass_FromTaggedLHERawL",&ZOne_mass_FromTaggedLHERawL,"ZOne_mass_FromTaggedLHERawL/F");

    RawTaggedTree->Branch("ZTwo_pt_FromTaggedLHERawL",&ZTwo_pt_FromTaggedLHERawL,"ZTwo_pt_FromTaggedLHERawL/F");
    RawTaggedTree->Branch("ZTwo_eta_FromTaggedLHERawL",&ZTwo_eta_FromTaggedLHERawL,"ZTwo_eta_FromTaggedLHERawL/F");
    RawTaggedTree->Branch("ZTwo_phi_FromTaggedLHERawL",&ZTwo_phi_FromTaggedLHERawL,"ZTwo_phi_FromTaggedLHERawL/F");
    RawTaggedTree->Branch("ZTwo_mass_FromTaggedLHERawL",&ZTwo_mass_FromTaggedLHERawL,"ZTwo_mass_FromTaggedLHERawL/F");

    RawTaggedTree->Branch("ZPair_InvMass_FromTaggedLHERawL",&ZPair_InvMass_FromTaggedLHERawL,"ZPair_InvMass_FromTaggedLHERawL/F");
    RawTaggedTree->Branch("ZPair_EtaSep_FromTaggedLHERawL",&ZPair_EtaSep_FromTaggedLHERawL,"ZPair_EtaSep_FromTaggedLHERawL/F");

    RawTaggedTree->Branch("H_pt_FromTaggedLHERawL",&H_pt_FromTaggedLHERawL,"H_pt_FromTaggedLHERawL/F");
    RawTaggedTree->Branch("H_eta_FromTaggedLHERawL",&H_eta_FromTaggedLHERawL,"H_eta_FromTaggedLHERawL/F");
    RawTaggedTree->Branch("H_phi_FromTaggedLHERawL",&H_phi_FromTaggedLHERawL,"H_phi_FromTaggedLHERawL/F");
    RawTaggedTree->Branch("H_mass_FromTaggedLHERawL",&H_mass_FromTaggedLHERawL,"H_mass_FromTaggedLHERawL/F");


    RawTaggedTree->Branch("ZPairPlusH_InvMass_FromTaggedLHERawL",&ZPairPlusH_InvMass_FromTaggedLHERawL,"ZPairPlusH_InvMass_FromTaggedLHERawL/F");

    RawTaggedTree->Branch("JOne_pt_FromTaggedLHERawL",&JOne_pt_FromTaggedLHERawL,"JOne_pt_FromTaggedLHERawL/F");
    RawTaggedTree->Branch("JOne_eta_FromTaggedLHERawL",&JOne_eta_FromTaggedLHERawL,"JOne_eta_FromTaggedLHERawL/F");
    RawTaggedTree->Branch("JOne_phi_FromTaggedLHERawL",&JOne_phi_FromTaggedLHERawL,"JOne_phi_FromTaggedLHERawL/F");
    RawTaggedTree->Branch("JOne_invmass_FromTaggedLHERawL",&JOne_invmass_FromTaggedLHERawL,"JOne_invmass_FromTaggedLHERawL/F");
    RawTaggedTree->Branch("JOne_pdgId_FromTaggedLHERawL",&JOne_pdgId_FromTaggedLHERawL,"JOne_pdgId_FromTaggedLHERawL/F");

    RawTaggedTree->Branch("JTwo_pt_FromTaggedLHERawL",&JTwo_pt_FromTaggedLHERawL,"JTwo_pt_FromTaggedLHERawL/F");
    RawTaggedTree->Branch("JTwo_eta_FromTaggedLHERawL",&JTwo_eta_FromTaggedLHERawL,"JTwo_eta_FromTaggedLHERawL/F");
    RawTaggedTree->Branch("JTwo_phi_FromTaggedLHERawL",&JTwo_phi_FromTaggedLHERawL,"JTwo_phi_FromTaggedLHERawL/F");
    RawTaggedTree->Branch("JTwo_invmass_FromTaggedLHERawL",&JTwo_invmass_FromTaggedLHERawL,"JTwo_invmass_FromTaggedLHERawL/F");
    RawTaggedTree->Branch("JTwo_pdgId_FromTaggedLHERawL",&JTwo_pdgId_FromTaggedLHERawL,"JTwo_pdgId_FromTaggedLHERawL/F");

    

    RawTaggedTree->Branch("JPair_invmass_FromTaggedLHERawL",&JPair_invmass_FromTaggedLHERawL,"JPair_invmass_FromTaggedLHERawL/F");
    RawTaggedTree->Branch("J_etasep_FromTaggedLHERawL",&J_etasep_FromTaggedLHERawL,"J_etasep_FromTaggedLHERawL/F");


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

            //HFJ_decaypdgId_FromGenMatchL.clear();


            bool passesCutsBool = false;
            bool passedAsLepBool = false;
            bool passedAsSemiLepBool = false;
            bool passedAsHadBool = false;

            //Some tagging done early for the hadronic genmatching trees
            
            //First check that it passes the hbb tagging
            bool hbbTag = *HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02 || *HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2 || *HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4;

            //Hadronic
            bool hadHLT =  (*HLT_PFHT1050 || *HLT_AK8PFJet500 || *HLT_AK8PFJet360_TrimMass30 || *HLT_AK8PFHT750_TrimMass50 || *HLT_AK8PFJet380_TrimMass30 ||
            *HLT_AK8PFJet400_TrimMass30 || *HLT_AK8PFJet420_TrimMass30 ||
            *HLT_AK8PFHT800_TrimMass50 || *HLT_AK8PFHT850_TrimMass50 || *HLT_AK8PFHT900_TrimMass50);

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

                    /*

                    if (hbbTag && hadHLT) {

                        ZOne_pt_FromTaggedLHERawL = ZOne_pt_FromLHERaw;
                        ZOne_eta_FromTaggedLHERawL = ZOne_eta_FromLHERaw;
                        ZOne_phi_FromTaggedLHERawL = ZOne_phi_FromLHERaw;
                        ZOne_mass_FromTaggedLHERawL = ZOne_mass_FromLHERaw;

                        ZTwo_pt_FromTaggedLHERawL = ZTwo_pt_FromLHERaw;
                        ZTwo_eta_FromTaggedLHERawL = ZTwo_eta_FromLHERaw;
                        ZTwo_phi_FromTaggedLHERawL = ZTwo_phi_FromLHERaw;
                        ZTwo_mass_FromTaggedLHERawL = ZTwo_mass_FromLHERaw;

                        ZPair_InvMass_FromTaggedLHERawL = ZPair_InvMass_FromLHERaw;
                        ZPair_EtaSep_FromTaggedLHERawL = ZPair_EtaSep_FromLHERaw;

                        H_pt_FromTaggedLHERawL = H_pt_FromLHERaw;
                        H_eta_FromTaggedLHERawL = H_eta_FromLHERaw;
                        H_phi_FromTaggedLHERawL = H_phi_FromLHERaw;
                        H_mass_FromTaggedLHERawL = H_mass_FromLHERaw;

                        ZPairPlusH_InvMass_FromTaggedLHERawL = ZPairPlusH_InvMass_FromLHERaw;

                        JOne_pt_FromTaggedLHERawL = JOne_pt_FromLHERaw;
                        JOne_eta_FromTaggedLHERawL = JOne_eta_FromLHERaw;
                        JOne_pdgId_FromTaggedLHERawL = JOne_pdgId_FromLHERaw;

                        JTwo_pt_FromTaggedLHERawL = JTwo_pt_FromLHERaw;
                        JTwo_eta_FromTaggedLHERawL = JTwo_eta_FromLHERaw;
                        JTwo_pdgId_FromTaggedLHERawL = JTwo_pdgId_FromLHERaw;

                        JOne_invmass_FromTaggedLHERawL = JOne_invmass_FromLHERaw;
                        JTwo_invmass_FromTaggedLHERawL = JTwo_invmass_FromLHERaw;

                        JOne_phi_FromTaggedLHERawL = JOne_phi_FromLHERaw;

                        JTwo_phi_FromTaggedLHERawL = JTwo_phi_FromLHERaw;
                        JPair_invmass_FromTaggedLHERawL = JPair_invmass_FromLHERaw;

                        J_etasep_FromTaggedLHERawL = J_etasep_FromLHERaw;

                        RawTaggedTree->Fill();

                    }
                    */

                }
                if (useFJGenMatchTree || useJGenMatchTree) {
                    bool ZIsHadronic = false;
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
                    //bool HDecFound = false;

                    UInt_t nHFJDecay_FromGenMatch;
                    std::vector<Int_t> HFJ_decaypdgId_FromGenMatch;

                    if (tmpHFJAr.size()){
                        for (UInt_t tmpHItr=0;tmpHItr<tmpHFJAr.size();tmpHItr++){
                            if (tmpHItr != intermediaryH) {
                                finalHAr.push_back(tmpHFJAr[tmpHItr][0]);
                                //Looping through array for decay branches
                                for (UInt_t tmpHDecItr=1;tmpHDecItr<tmpHFJAr[tmpHItr].size();tmpHDecItr++){
                                    HFJ_decaypdgId_FromGenMatch.push_back(tmpHFJAr[tmpHItr][tmpHDecItr]);
                                }
                            }
                        }
                    }

                    if (debugGenPart) std::cout << "HFJ_decaypdgId_FromGenMatch.size() " << HFJ_decaypdgId_FromGenMatch.size() << "\n";

                    nHFJDecay_FromGenMatch = HFJ_decaypdgId_FromGenMatch.size();


                    bool hGenFound = false;
                    float H_pt_FromGenRaw;
                    float H_eta_FromGenRaw;
                    float H_phi_FromGenRaw;
                    float H_mass_FromGenRaw;
                    float H_pdgId_FromGenRaw;
                    float H_genPartIdxMother_FromGenRaw;

                    UInt_t hJetInd;
                    bool hJetFound = false;
                    //bool hJetFoundTighterCut = false;
                    float HFJ_pt_FromGenMatch;
                    float HFJ_eta_FromGenMatch;
                    float HFJ_phi_FromGenMatch;
                    float HFJ_mass_FromGenMatch;
                    float HFJ_dRFromFJ_FromGenMatch;

                    Int_t hInd = -1;

                    
                    
                    if (finalHAr.size() != 1) {
                        std::cout <<"ERROR ERROR, MORE OR LESS THAN ONE H,evCount,JOne_pdgId_FromLHERaw,JTwo_pdgId_FromLHERaw " << evCount<< " " <<JOne_pdgId_FromLHERaw<< " " <<JTwo_pdgId_FromLHERaw << "\n";
                    }
                    else{
                        hInd = finalHAr[0];
                        hGenFound = true;
                        H_pt_FromGenRaw = GenPart_pt[hInd];
                        H_eta_FromGenRaw = GenPart_eta[hInd];
                        H_phi_FromGenRaw = GenPart_phi[hInd];
                        H_mass_FromGenRaw = GenPart_mass[hInd];
                        H_pdgId_FromGenRaw = GenPart_pdgId[hInd];
                        H_genPartIdxMother_FromGenRaw = GenPart_genPartIdxMother[hInd];



                        float mindROne = 1000;

                        if (useFJGenMatchTree){
                            if (debugGenPart) {
                                std::cout <<"entering FJ H gen matching loop\n";
                            }
                            /*
                            if (evCount-1 == 29){
                                std::cout << "ev29\n";
                                std::co1ut << "*nFatJet " << *nFatJet <<" finalHAr[0] " << finalHAr[0] << " GenPart_phi[finalHAr[0]] " << GenPart_phi[finalHAr[0]] << " GenPart_eta[finalHAr[0]] " << GenPart_eta[finalHAr[0]] << "\n";
                            }
                            */

                            for (UInt_t fatJetInd=0;fatJetInd<*nFatJet;fatJetInd++){
                                float tmpMindROne = calcDeltaR(FatJet_phi[fatJetInd],FatJet_eta[fatJetInd],GenPart_phi[hInd],GenPart_eta[hInd]);
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

                                
                                nHFJDecay_FromGenMatchL = nHFJDecay_FromGenMatch;
                                
                                for (UInt_t tmpHDecItr=0;tmpHDecItr<HFJ_decaypdgId_FromGenMatch.size();tmpHDecItr++){
                                    HFJ_decaypdgId_FromGenMatchL.push_back(HFJ_decaypdgId_FromGenMatch[tmpHDecItr]);
                                }
                                //HFJ_decaypdgId_FromGenMatchL = HFJ_decaypdgId_FromGenMatch;


                                HFJ_pt_FromGenMatchL = HFJ_pt_FromGenMatch;
                                HFJ_eta_FromGenMatchL = HFJ_eta_FromGenMatch;
                                HFJ_phi_FromGenMatchL = HFJ_phi_FromGenMatch;
                                HFJ_mass_FromGenMatchL = HFJ_mass_FromGenMatch;
                                HFJ_dRFromFJ_FromGenMatchL = HFJ_dRFromFJ_FromGenMatch;
                                //for (UInt_t tmptmpItr=0;tmptmpItr<HFJ_decaypdgId_FromGenMatchL.size();tmptmpItr++){
                                //    std::cout << HFJ_decaypdgId_FromGenMatchL[tmptmpItr] << " ";
                                //}
                                //std::cout << "\n";
                                //HFJGenTree->SetBranchAddress("HFJ_decaypdgId_FromGenMatchL",&HFJ_decaypdgId_FromGenMatchL);
                                HFJGenTree->Fill();
                                HFJ_decaypdgId_FromGenMatchL.clear();
                                /*

                                if (hbbTag && hadHLT) {

                                    HFJ_pt_FromTaggedGenMatchL = HFJ_pt_FromGenMatch;
                                    HFJ_eta_FromTaggedGenMatchL = HFJ_eta_FromGenMatch;
                                    HFJ_phi_FromTaggedGenMatchL = HFJ_phi_FromGenMatch;
                                    HFJ_mass_FromTaggedGenMatchL = HFJ_mass_FromGenMatch;
                                    HFJ_dRFromFJ_FromTaggedGenMatchL = HFJ_dRFromFJ_FromGenMatch;
                                

                                    HFJGenTaggedTree->Fill();

                                }
                                */
                               /*
                                if (mindROne < genMatchdRTighterCut){
                                    hJetFoundTighterCut = true;
                                    
                                    nHFJDecay_FromGenMatchTighterCutL = nHFJDecay_FromGenMatch;
                                    
                                    for (UInt_t tmpHDecItr=0;tmpHDecItr<HFJ_decaypdgId_FromGenMatch.size();tmpHDecItr++){
                                        HFJ_decaypdgId_FromGenMatchTighterCutL.push_back(HFJ_decaypdgId_FromGenMatch[tmpHDecItr]);
                                    }


                                    HFJ_pt_FromGenMatchTighterCutL = HFJ_pt_FromGenMatch;
                                    HFJ_eta_FromGenMatchTighterCutL = HFJ_eta_FromGenMatch;
                                    HFJ_phi_FromGenMatchTighterCutL = HFJ_phi_FromGenMatch;
                                    HFJ_mass_FromGenMatchTighterCutL = HFJ_mass_FromGenMatch;
                                    HFJ_dRFromFJ_FromGenMatchTighterCutL = HFJ_dRFromFJ_FromGenMatch;
                                    HFJGenTighterCutTree->Fill();
                                    HFJ_decaypdgId_FromGenMatchTighterCutL.clear();

                                }
                                */


                            }
                            else if (debugGenPart) {
                                std::cout <<"H Gen Match failed\n";
                                std::cout << "evCount " << evCount-1 << " mindROne " << mindROne << "\n";
                                std::cout << "*nFatJet " << *nFatJet << "\n";

                            }
                        }
                    }



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
                    std::vector<std::vector<Int_t>> finalZDecAr;
                    bool ZDecFound = false;

                    UInt_t nZFJLeadDecay_FromGenMatch;
                    std::vector<Int_t> ZFJLead_decaypdgId_FromGenMatch;
                    UInt_t nZFJTrailingDecay_FromGenMatch;
                    std::vector<Int_t> ZFJTrailing_decaypdgId_FromGenMatch;
                    bool tmpGotFirst = false;

                    if (tmpZFJAr.size()){
                        for (UInt_t tmpZItr=0;tmpZItr<tmpZFJAr.size();tmpZItr++){
                            if (tmpZItr != intermediaryZ){
                                finalZAr.push_back(tmpZFJAr[tmpZItr][0]);
                                //Looping through array for decay branches
                                if (tmpGotFirst) {
                                    for (UInt_t tmpZDecItr=1;tmpZDecItr<tmpZFJAr[tmpZItr].size();tmpZDecItr++){
                                        ZFJTrailing_decaypdgId_FromGenMatch.push_back(tmpZFJAr[tmpZItr][tmpZDecItr]);
                                    }
                                        

                                }
                                else{
                                    tmpGotFirst = true;
                                    for (UInt_t tmpZDecItr=1;tmpZDecItr<tmpZFJAr[tmpZItr].size();tmpZDecItr++){
                                        ZFJLead_decaypdgId_FromGenMatch.push_back(tmpZFJAr[tmpZItr][tmpZDecItr]);
                                    }

                                }
                                
                                if (tmpZFJAr[tmpZItr].size() != 3) {
                                    std::cout << "ERROR ERROR tmpZFJAr INTERNAL VEC SIZE NOT == 3. INSTEAD SIZE == " << tmpZFJAr[tmpZItr].size() << "\n";
                                    for (UInt_t tmpZDecItr=0;tmpZDecItr<tmpZFJAr[tmpZItr].size();tmpZDecItr++){
                                        std::cout << tmpZFJAr[tmpZItr][tmpZDecItr] << " ";
                                    }
                                    std::cout << "\n";
                                }
                                else {
                                    ZDecFound = true;
                                    std::vector<Int_t> tmpZDecVec;
                                    tmpZDecVec.push_back(tmpZFJAr[tmpZItr][1]);
                                    tmpZDecVec.push_back(tmpZFJAr[tmpZItr][2]);
                                    finalZDecAr.push_back(tmpZDecVec);
                                }
                            }
                        }
                    }

                    nZFJLeadDecay_FromGenMatch = ZFJLead_decaypdgId_FromGenMatch.size();
                    nZFJTrailingDecay_FromGenMatch = ZFJTrailing_decaypdgId_FromGenMatch.size();

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
                        
                        //std::cout << evCount-1 << " " << finalZAr[0] << " " << finalZAr[1] << "\n";
                        if (ZDecFound) {
                            if (debugGenPart) std::cout << "finalZDecAr[0][0] " << finalZDecAr[0][0] << " finalZDecAr[0][1] " << finalZDecAr[0][1] << " finalZDecAr[1][0] " << finalZDecAr[1][0] << " finalZDecAr[1][1] " << finalZDecAr[1][1] << "\n";
                            ZIsHadronic = (finalZDecAr[0][0]>-9 && finalZDecAr[0][0]<9 && finalZDecAr[0][1]>-9 && finalZDecAr[0][1]<9 && finalZDecAr[1][0]>-9 && finalZDecAr[1][0]<9 && finalZDecAr[1][1]>-9 && finalZDecAr[1][1]<9);
                            if (debugGenPart) std::cout << "ZIsHadronic " << ZIsHadronic << "\n";
                        }


                        zGenFound = true;
                        Int_t tmpZOneInd = finalZAr[0];
                        Int_t tmpZTwoInd = finalZAr[1];
                        float tmpZptOne = GenPart_pt[tmpZOneInd];
                        float tmpZptTwo = GenPart_pt[tmpZTwoInd];
                        
                        
                        if (tmpZptOne > tmpZptTwo) {
                            ZOne_pt_FromGenRaw = tmpZptOne;
                            ZOne_eta_FromGenRaw = GenPart_eta[tmpZOneInd];
                            ZOne_phi_FromGenRaw = GenPart_phi[tmpZOneInd];
                            ZOne_mass_FromGenRaw = GenPart_mass[tmpZOneInd];
                            ZOne_pdgId_FromGenRaw = GenPart_pdgId[tmpZOneInd];
                            ZOne_genPartIdxMother_FromGenRaw = GenPart_genPartIdxMother[tmpZOneInd];

                            ZTwo_pt_FromGenRaw = tmpZptTwo;
                            ZTwo_eta_FromGenRaw = GenPart_eta[tmpZTwoInd];
                            ZTwo_phi_FromGenRaw = GenPart_phi[tmpZTwoInd];
                            ZTwo_mass_FromGenRaw = GenPart_mass[tmpZTwoInd];
                            ZTwo_pdgId_FromGenRaw = GenPart_pdgId[tmpZTwoInd];
                            ZTwo_genPartIdxMother_FromGenRaw = GenPart_genPartIdxMother[tmpZTwoInd];
                        }
                        else{
                            ZOne_pt_FromGenRaw = tmpZptTwo;
                            ZOne_eta_FromGenRaw = GenPart_eta[tmpZTwoInd];
                            ZOne_phi_FromGenRaw = GenPart_phi[tmpZTwoInd];
                            ZOne_mass_FromGenRaw = GenPart_mass[tmpZTwoInd];
                            ZOne_pdgId_FromGenRaw = GenPart_pdgId[tmpZTwoInd];
                            ZOne_genPartIdxMother_FromGenRaw = GenPart_genPartIdxMother[tmpZTwoInd];

                            ZTwo_pt_FromGenRaw = tmpZptOne;
                            ZTwo_eta_FromGenRaw = GenPart_eta[tmpZOneInd];
                            ZTwo_phi_FromGenRaw = GenPart_phi[tmpZOneInd];
                            ZTwo_mass_FromGenRaw = GenPart_mass[tmpZOneInd];
                            ZTwo_pdgId_FromGenRaw = GenPart_pdgId[tmpZOneInd];
                            ZTwo_genPartIdxMother_FromGenRaw = GenPart_genPartIdxMother[tmpZOneInd];

                        }

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

                        /*

                        UInt_t zJetIndOneTighterCut;
                        UInt_t zJetIndOneSecondPlaceTighterCut;
                        UInt_t zJetIndTwoTighterCut;
                        float mindROneTighterCut = 1000;
                        float mindROneSecondPlaceTighterCut = 1000;

                        float mindRTwoTighterCut = 1000;
                        bool useSecondPlaceTighterCut = false;

                        */


                        if (useFJGenMatchTree){
                            if (debugGenPart) {
                                std::cout <<"entering FJ Z gen matching loop\n";
                                std::cout << "*nFatJet " << *nFatJet <<  " hJetFound " << hJetFound;
                                if (hJetFound) std::cout <<" hJetInd " << hJetInd << "\n";
                                else std::cout << "\n";
                            }

                            for (UInt_t fatJetInd=0;fatJetInd<*nFatJet;fatJetInd++){
                                if (!(hJetFound && fatJetInd == hJetInd)) {
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
                                if (!(hJetFoundTighterCut && fatJetInd == hJetInd)) {
                                    float tmpMindROneTighterCut = calcDeltaR(FatJet_phi[fatJetInd],FatJet_eta[fatJetInd],GenPart_phi[finalZAr[0]],GenPart_eta[finalZAr[0]]);
                                    
                                    if (tmpMindROneTighterCut < mindROneTighterCut){
                                        mindROneSecondPlaceTighterCut = mindROneTighterCut;
                                        mindROneTighterCut = tmpMindROneTighterCut;
                                        zJetIndOneSecondPlaceTighterCut = zJetIndOneTighterCut;
                                        zJetIndOneTighterCut = fatJetInd;
                                    }
                                }
                                */
                            }
                            /*
                            if (evCount -1 == 0){
                                std::cout << "secondloop\n";
                            }
                            */
                            for (UInt_t fatJetInd=0;fatJetInd<*nFatJet;fatJetInd++){
                                if (!(hJetFound && fatJetInd == hJetInd)) {
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
                                /*
                                if (!(hJetFoundTighterCut && fatJetInd == hJetInd)) {
                                    float tmpMindRTwoTighterCut = calcDeltaR(FatJet_phi[fatJetInd],FatJet_eta[fatJetInd],GenPart_phi[finalZAr[1]],GenPart_eta[finalZAr[1]]);
                                    if (tmpMindRTwoTighterCut < mindRTwoTighterCut){
                                        if (fatJetInd == zJetIndOneTighterCut) {
                                            if (tmpMindRTwoTighterCut < mindROneTighterCut){
                                                useSecondPlaceTighterCut = true;
                                                mindRTwoTighterCut = tmpMindRTwoTighterCut;
                                                zJetIndTwoTighterCut = fatJetInd;
                                            }
                                            else useSecondPlaceTighterCut = false;
                                        }
                                        else {
                                            useSecondPlaceTighterCut = false;
                                            mindRTwoTighterCut = tmpMindRTwoTighterCut;
                                            zJetIndTwoTighterCut = fatJetInd;

                                        }
                                    }
                                }
                                */
                            }

                            if (useSecondPlace) {
                                zJetIndOne = zJetIndOneSecondPlace;
                                mindROne = mindROneSecondPlace;
                                ZFJSameJetCtr += 1;
                                if (ZIsHadronic) ZFJSameJetTaggedCtr += 1;
                                if (debugGenPart) std::cout << "evCount " << evCount -1 << " zJetIndOne " << zJetIndOne << " zJetIndTwo " << zJetIndTwo << " mindROne " << mindROne << " mindRTwo " << mindRTwo << "\n";
                            }

                            /*

                            if (useSecondPlaceTighterCut) {
                                zJetIndOneTighterCut = zJetIndOneSecondPlaceTighterCut;
                                mindROneTighterCut = mindROneSecondPlaceTighterCut;
                                ZFJSameJetTighterCutCtr += 1;
                                if (ZIsHadronic) ZFJSameJetTaggedTighterCutCtr += 1;
                                if (debugGenPart) std::cout << "evCount " << evCount -1 << " zJetIndOneTighterCut " << zJetIndOneTighterCut << " zJetIndTwoTighterCut " << zJetIndTwoTighterCut << " mindROneTighterCut " << mindROneTighterCut << " mindRTwoTighterCut " << mindRTwoTighterCut << "\n";
                            }
                            */


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

                                nZFJLeadDecay_FromGenMatchL = nZFJLeadDecay_FromGenMatch;
                                //ZFJLead_decaypdgId_FromGenMatchL = ZFJLead_decaypdgId_FromGenMatch;
                                for (UInt_t tmpZDecItr=0;tmpZDecItr<ZFJLead_decaypdgId_FromGenMatch.size();tmpZDecItr++){
                                    ZFJLead_decaypdgId_FromGenMatchL.push_back(ZFJLead_decaypdgId_FromGenMatch[tmpZDecItr]);
                                }
                                

                                ZFJTrailing_pt_FromGenMatchL = ZFJTrailing_pt_FromGenMatch;
                                ZFJTrailing_eta_FromGenMatchL = ZFJTrailing_eta_FromGenMatch;
                                ZFJTrailing_phi_FromGenMatchL = ZFJTrailing_phi_FromGenMatch;
                                ZFJTrailing_mass_FromGenMatchL = ZFJTrailing_mass_FromGenMatch;
                                ZFJTrailing_dRFromFJ_FromGenMatchL = ZFJTrailing_dRFromFJ_FromGenMatch;

                                nZFJTrailingDecay_FromGenMatchL = nZFJTrailingDecay_FromGenMatch;
                                //ZFJTrailing_decaypdgId_FromGenMatchL = ZFJTrailing_decaypdgId_FromGenMatch;

                                for (UInt_t tmpZDecItr=0;tmpZDecItr<ZFJTrailing_decaypdgId_FromGenMatch.size();tmpZDecItr++){
                                    ZFJTrailing_decaypdgId_FromGenMatchL.push_back(ZFJTrailing_decaypdgId_FromGenMatch[tmpZDecItr]);
                                }

                                


                                ROOT::Math::PtEtaPhiMVector tmpZFJLeadVec  = ROOT::Math::PtEtaPhiMVector(ZFJLead_pt_FromGenMatch,ZFJLead_eta_FromGenMatch,ZFJLead_phi_FromGenMatch,ZFJLead_mass_FromGenMatch);

                                ROOT::Math::PtEtaPhiMVector tmpZFJTrailingVec  = ROOT::Math::PtEtaPhiMVector(ZFJTrailing_pt_FromGenMatch,ZFJTrailing_eta_FromGenMatch,ZFJTrailing_phi_FromGenMatch,ZFJTrailing_mass_FromGenMatch);

                                ROOT::Math::PtEtaPhiMVector tmpZFJPairVec = tmpZFJLeadVec+tmpZFJTrailingVec;

                                float ZFJPair_InvMass_FromGenMatch = tmpZFJPairVec.M();
                                float ZFJPair_EtaSep_FromGenMatch = abs(ZFJLead_eta_FromGenMatch-ZFJTrailing_eta_FromGenMatch);

                                ZFJPair_InvMass_FromGenMatchL = ZFJPair_InvMass_FromGenMatch;
                                ZFJPair_EtaSep_FromGenMatchL = ZFJPair_EtaSep_FromGenMatch;
                                ZFJGenTree->Fill();

                                ZFJLead_decaypdgId_FromGenMatchL.clear();
                                ZFJTrailing_decaypdgId_FromGenMatchL.clear();

                                if (ZIsHadronic) {

                                    ZFJLead_pt_FromTaggedGenMatchL = ZFJLead_pt_FromGenMatch;
                                    ZFJLead_eta_FromTaggedGenMatchL = ZFJLead_eta_FromGenMatch;
                                    ZFJLead_phi_FromTaggedGenMatchL = ZFJLead_phi_FromGenMatch;
                                    ZFJLead_mass_FromTaggedGenMatchL = ZFJLead_mass_FromGenMatch;
                                    ZFJLead_dRFromFJ_FromTaggedGenMatchL = ZFJLead_dRFromFJ_FromGenMatch;

                                    nZFJLeadDecay_FromTaggedGenMatchL = nZFJLeadDecay_FromGenMatch;
                                    //ZFJLead_decaypdgId_FromTaggedGenMatchL = ZFJLead_decaypdgId_FromGenMatch;

                                    for (UInt_t tmpZDecItr=0;tmpZDecItr<ZFJLead_decaypdgId_FromGenMatch.size();tmpZDecItr++){
                                        ZFJLead_decaypdgId_FromTaggedGenMatchL.push_back(ZFJLead_decaypdgId_FromGenMatch[tmpZDecItr]);
                                    }
                                    

                                    ZFJTrailing_pt_FromTaggedGenMatchL = ZFJTrailing_pt_FromGenMatch;
                                    ZFJTrailing_eta_FromTaggedGenMatchL = ZFJTrailing_eta_FromGenMatch;
                                    ZFJTrailing_phi_FromTaggedGenMatchL = ZFJTrailing_phi_FromGenMatch;
                                    ZFJTrailing_mass_FromTaggedGenMatchL = ZFJTrailing_mass_FromGenMatch;
                                    ZFJTrailing_dRFromFJ_FromTaggedGenMatchL = ZFJTrailing_dRFromFJ_FromGenMatch;


                                    nZFJTrailingDecay_FromTaggedGenMatchL = nZFJTrailingDecay_FromGenMatch;
                                    //ZFJTrailing_decaypdgId_FromTaggedGenMatchL = ZFJTrailing_decaypdgId_FromGenMatch;

                                    for (UInt_t tmpZDecItr=0;tmpZDecItr<ZFJTrailing_decaypdgId_FromGenMatch.size();tmpZDecItr++){
                                        ZFJTrailing_decaypdgId_FromTaggedGenMatchL.push_back(ZFJTrailing_decaypdgId_FromGenMatch[tmpZDecItr]);
                                    }

                                    ZFJPair_InvMass_FromTaggedGenMatchL = ZFJPair_InvMass_FromGenMatch;
                                    ZFJPair_EtaSep_FromTaggedGenMatchL = ZFJPair_EtaSep_FromGenMatch;
                                    ZFJGenTaggedTree->Fill();

                                    ZFJLead_decaypdgId_FromTaggedGenMatchL.clear();
                                    ZFJTrailing_decaypdgId_FromTaggedGenMatchL.clear();
                                }



                                if (hJetFound){
                                    ROOT::Math::PtEtaPhiMVector tmpHFJVec  = ROOT::Math::PtEtaPhiMVector(HFJ_pt_FromGenMatch,HFJ_eta_FromGenMatch,HFJ_phi_FromGenMatch,HFJ_mass_FromGenMatch);

                                    ROOT::Math::PtEtaPhiMVector tmpHZFJVec = tmpHFJVec+tmpZFJPairVec;
                                    
                                    ZHFJ_ZPairPlusHInvMass_FromGenMatchL = tmpHZFJVec.M();
                                    ZHFJGenTree->Fill();

                                    if (ZIsHadronic) {

                                        ZHFJ_ZPairPlusHInvMass_FromTaggedGenMatchL = tmpHZFJVec.M();
                                        ZHFJGenTaggedTree->Fill();

                                    }



                                }
                            }

                            
                        }

                        /*
                        

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

                                nZFJLeadDecay_FromGenMatchL = nZFJLeadDecay_FromGenMatch;
                                //ZFJLead_decaypdgId_FromGenMatchL = ZFJLead_decaypdgId_FromGenMatch;
                                for (UInt_t tmpZDecItr=0;tmpZDecItr<ZFJLead_decaypdgId_FromGenMatch.size();tmpZDecItr++){
                                    ZFJLead_decaypdgId_FromGenMatchL.push_back(ZFJLead_decaypdgId_FromGenMatch[tmpZDecItr]);
                                }
                                

                                ZFJTrailing_pt_FromGenMatchL = ZFJTrailing_pt_FromGenMatch;
                                ZFJTrailing_eta_FromGenMatchL = ZFJTrailing_eta_FromGenMatch;
                                ZFJTrailing_phi_FromGenMatchL = ZFJTrailing_phi_FromGenMatch;
                                ZFJTrailing_mass_FromGenMatchL = ZFJTrailing_mass_FromGenMatch;
                                ZFJTrailing_dRFromFJ_FromGenMatchL = ZFJTrailing_dRFromFJ_FromGenMatch;

                                nZFJTrailingDecay_FromGenMatchL = nZFJTrailingDecay_FromGenMatch;
                                //ZFJTrailing_decaypdgId_FromGenMatchL = ZFJTrailing_decaypdgId_FromGenMatch;

                                for (UInt_t tmpZDecItr=0;tmpZDecItr<ZFJTrailing_decaypdgId_FromGenMatch.size();tmpZDecItr++){
                                    ZFJTrailing_decaypdgId_FromGenMatchL.push_back(ZFJTrailing_decaypdgId_FromGenMatch[tmpZDecItr]);
                                }

                                


                                ROOT::Math::PtEtaPhiMVector tmpZFJLeadVec  = ROOT::Math::PtEtaPhiMVector(ZFJLead_pt_FromGenMatch,ZFJLead_eta_FromGenMatch,ZFJLead_phi_FromGenMatch,ZFJLead_mass_FromGenMatch);

                                ROOT::Math::PtEtaPhiMVector tmpZFJTrailingVec  = ROOT::Math::PtEtaPhiMVector(ZFJTrailing_pt_FromGenMatch,ZFJTrailing_eta_FromGenMatch,ZFJTrailing_phi_FromGenMatch,ZFJTrailing_mass_FromGenMatch);

                                ROOT::Math::PtEtaPhiMVector tmpZFJPairVec = tmpZFJLeadVec+tmpZFJTrailingVec;

                                float ZFJPair_InvMass_FromGenMatch = tmpZFJPairVec.M();
                                float ZFJPair_EtaSep_FromGenMatch = abs(ZFJLead_eta_FromGenMatch-ZFJTrailing_eta_FromGenMatch);

                                ZFJPair_InvMass_FromGenMatchL = ZFJPair_InvMass_FromGenMatch;
                                ZFJPair_EtaSep_FromGenMatchL = ZFJPair_EtaSep_FromGenMatch;
                                ZFJGenTree->Fill();

                                ZFJLead_decaypdgId_FromGenMatchL.clear();
                                ZFJTrailing_decaypdgId_FromGenMatchL.clear();

                                if (ZIsHadronic) {

                                    ZFJLead_pt_FromTaggedGenMatchL = ZFJLead_pt_FromGenMatch;
                                    ZFJLead_eta_FromTaggedGenMatchL = ZFJLead_eta_FromGenMatch;
                                    ZFJLead_phi_FromTaggedGenMatchL = ZFJLead_phi_FromGenMatch;
                                    ZFJLead_mass_FromTaggedGenMatchL = ZFJLead_mass_FromGenMatch;
                                    ZFJLead_dRFromFJ_FromTaggedGenMatchL = ZFJLead_dRFromFJ_FromGenMatch;

                                    nZFJLeadDecay_FromTaggedGenMatchL = nZFJLeadDecay_FromGenMatch;
                                    //ZFJLead_decaypdgId_FromTaggedGenMatchL = ZFJLead_decaypdgId_FromGenMatch;

                                    for (UInt_t tmpZDecItr=0;tmpZDecItr<ZFJLead_decaypdgId_FromGenMatch.size();tmpZDecItr++){
                                        ZFJLead_decaypdgId_FromTaggedGenMatchL.push_back(ZFJLead_decaypdgId_FromGenMatch[tmpZDecItr]);
                                    }
                                    

                                    ZFJTrailing_pt_FromTaggedGenMatchL = ZFJTrailing_pt_FromGenMatch;
                                    ZFJTrailing_eta_FromTaggedGenMatchL = ZFJTrailing_eta_FromGenMatch;
                                    ZFJTrailing_phi_FromTaggedGenMatchL = ZFJTrailing_phi_FromGenMatch;
                                    ZFJTrailing_mass_FromTaggedGenMatchL = ZFJTrailing_mass_FromGenMatch;
                                    ZFJTrailing_dRFromFJ_FromTaggedGenMatchL = ZFJTrailing_dRFromFJ_FromGenMatch;


                                    nZFJTrailingDecay_FromTaggedGenMatchL = nZFJTrailingDecay_FromGenMatch;
                                    //ZFJTrailing_decaypdgId_FromTaggedGenMatchL = ZFJTrailing_decaypdgId_FromGenMatch;

                                    for (UInt_t tmpZDecItr=0;tmpZDecItr<ZFJTrailing_decaypdgId_FromGenMatch.size();tmpZDecItr++){
                                        ZFJTrailing_decaypdgId_FromTaggedGenMatchL.push_back(ZFJTrailing_decaypdgId_FromGenMatch[tmpZDecItr]);
                                    }

                                    ZFJPair_InvMass_FromTaggedGenMatchL = ZFJPair_InvMass_FromGenMatch;
                                    ZFJPair_EtaSep_FromTaggedGenMatchL = ZFJPair_EtaSep_FromGenMatch;
                                    ZFJGenTaggedTree->Fill();

                                    ZFJLead_decaypdgId_FromTaggedGenMatchL.clear();
                                    ZFJTrailing_decaypdgId_FromTaggedGenMatchL.clear();
                                }



                                if (hJetFound){
                                    ROOT::Math::PtEtaPhiMVector tmpHFJVec  = ROOT::Math::PtEtaPhiMVector(HFJ_pt_FromGenMatch,HFJ_eta_FromGenMatch,HFJ_phi_FromGenMatch,HFJ_mass_FromGenMatch);

                                    ROOT::Math::PtEtaPhiMVector tmpHZFJVec = tmpHFJVec+tmpZFJPairVec;
                                    
                                    ZHFJ_ZPairPlusHInvMass_FromGenMatchL = tmpHZFJVec.M();
                                    ZHFJGenTree->Fill();

                                    if (ZIsHadronic) {

                                        ZHFJ_ZPairPlusHInvMass_FromTaggedGenMatchL = tmpHZFJVec.M();
                                        ZHFJGenTaggedTree->Fill();

                                    }



                                }
                            

                            
                        }
                        */
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

                            float tmpHEta;
                            float tmpHPhi;

                            if (hJetFound) {
                                tmpHEta = FatJet_eta[hJetInd];
                                tmpHPhi = FatJet_phi[hJetInd];
                            }



                            for (UInt_t jetInd=0;jetInd<*nJet;jetInd++){
                                if (hJetFound) {
                                    float tmpHdR = calcDeltaR(Jet_phi[jetInd],Jet_eta[jetInd],tmpHPhi,tmpHEta);
                                    if (tmpHdR < genMatchdRCut) {
                                        continue;
                                    }

                                }
                                float tmpMindROne = calcDeltaR(Jet_phi[jetInd],Jet_eta[jetInd],GenPart_phi[finalZAr[0]],GenPart_eta[finalZAr[0]]);
                                
                                if (tmpMindROne < mindROne){
                                    mindROneSecondPlace = mindROne;
                                    mindROne = tmpMindROne;
                                    zJetIndOneSecondPlace = zJetIndOne;
                                    zJetIndOne = jetInd;
                                }
                            }
                            for (UInt_t jetInd=0;jetInd<*nJet;jetInd++){
                                if (hJetFound) {
                                    float tmpHdR = calcDeltaR(Jet_phi[jetInd],Jet_eta[jetInd],tmpHPhi,tmpHEta);
                                    if (tmpHdR < genMatchdRCut) {
                                        continue;
                                    }

                                }
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
                                if (ZIsHadronic) ZJSameJetTaggedCtr += 1;
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

                                nZJLeadDecay_FromGenMatchL = nZFJLeadDecay_FromGenMatch;
                                //ZJLead_decaypdgId_FromGenMatchL = ZFJLead_decaypdgId_FromGenMatch;

                                for (UInt_t tmpZDecItr=0;tmpZDecItr<ZFJLead_decaypdgId_FromGenMatch.size();tmpZDecItr++){
                                    ZJLead_decaypdgId_FromGenMatchL.push_back(ZFJLead_decaypdgId_FromGenMatch[tmpZDecItr]);
                                }
                                
                                

                                ZJTrailing_pt_FromGenMatchL = ZJTrailing_pt_FromGenMatch;
                                ZJTrailing_eta_FromGenMatchL = ZJTrailing_eta_FromGenMatch;
                                ZJTrailing_phi_FromGenMatchL = ZJTrailing_phi_FromGenMatch;
                                ZJTrailing_mass_FromGenMatchL = ZJTrailing_mass_FromGenMatch;
                                ZJTrailing_dRFromJ_FromGenMatchL = ZJTrailing_dRFromJ_FromGenMatch;

                                nZJTrailingDecay_FromGenMatchL = nZFJTrailingDecay_FromGenMatch;
                                //ZJTrailing_decaypdgId_FromGenMatchL = ZFJTrailing_decaypdgId_FromGenMatch;

                                for (UInt_t tmpZDecItr=0;tmpZDecItr<ZFJLead_decaypdgId_FromGenMatch.size();tmpZDecItr++){
                                    ZJTrailing_decaypdgId_FromGenMatchL.push_back(ZFJLead_decaypdgId_FromGenMatch[tmpZDecItr]);
                                }

                                ROOT::Math::PtEtaPhiMVector tmpZJLeadVec  = ROOT::Math::PtEtaPhiMVector(ZJLead_pt_FromGenMatch,ZJLead_eta_FromGenMatch,ZJLead_phi_FromGenMatch,ZJLead_mass_FromGenMatch);

                                ROOT::Math::PtEtaPhiMVector tmpZJTrailingVec  = ROOT::Math::PtEtaPhiMVector(ZJTrailing_pt_FromGenMatch,ZJTrailing_eta_FromGenMatch,ZJTrailing_phi_FromGenMatch,ZJTrailing_mass_FromGenMatch);

                                ROOT::Math::PtEtaPhiMVector tmpZJPairVec = tmpZJLeadVec+tmpZJTrailingVec;

                                float ZJPair_InvMass_FromGenMatch = tmpZJPairVec.M();;
                                float ZJPair_EtaSep_FromGenMatch = abs(ZJLead_eta_FromGenMatch-ZJTrailing_eta_FromGenMatch);

                                ZJPair_InvMass_FromGenMatchL = ZJPair_InvMass_FromGenMatch;
                                ZJPair_EtaSep_FromGenMatchL = ZJPair_EtaSep_FromGenMatch;
                                ZJGenTree->Fill();

                                ZJLead_decaypdgId_FromGenMatchL.clear();
                                ZJTrailing_decaypdgId_FromGenMatchL.clear();

                                if (ZIsHadronic) {

                                    ZJLead_pt_FromTaggedGenMatchL = ZJLead_pt_FromGenMatch;
                                    ZJLead_eta_FromTaggedGenMatchL = ZJLead_eta_FromGenMatch;
                                    ZJLead_phi_FromTaggedGenMatchL = ZJLead_phi_FromGenMatch;
                                    ZJLead_mass_FromTaggedGenMatchL = ZJLead_mass_FromGenMatch;
                                    ZJLead_dRFromJ_FromTaggedGenMatchL = ZJLead_dRFromJ_FromGenMatch;

                                    nZJLeadDecay_FromTaggedGenMatchL = nZFJLeadDecay_FromGenMatch;
                                    //ZJLead_decaypdgId_FromTaggedGenMatchL = ZFJLead_decaypdgId_FromGenMatch;

                                    for (UInt_t tmpZDecItr=0;tmpZDecItr<ZFJLead_decaypdgId_FromGenMatch.size();tmpZDecItr++){
                                        ZJLead_decaypdgId_FromTaggedGenMatchL.push_back(ZFJLead_decaypdgId_FromGenMatch[tmpZDecItr]);
                                    }
                                    

                                    ZJTrailing_pt_FromTaggedGenMatchL = ZJTrailing_pt_FromGenMatch;
                                    ZJTrailing_eta_FromTaggedGenMatchL = ZJTrailing_eta_FromGenMatch;
                                    ZJTrailing_phi_FromTaggedGenMatchL = ZJTrailing_phi_FromGenMatch;
                                    ZJTrailing_mass_FromTaggedGenMatchL = ZJTrailing_mass_FromGenMatch;
                                    ZJTrailing_dRFromJ_FromTaggedGenMatchL = ZJTrailing_dRFromJ_FromGenMatch;

                                    nZJTrailingDecay_FromTaggedGenMatchL = nZFJTrailingDecay_FromGenMatch;
                                    //ZJTrailing_decaypdgId_FromTaggedGenMatchL = ZFJTrailing_decaypdgId_FromGenMatch;

                                    for (UInt_t tmpZDecItr=0;tmpZDecItr<ZFJTrailing_decaypdgId_FromGenMatch.size();tmpZDecItr++){
                                        ZJTrailing_decaypdgId_FromTaggedGenMatchL.push_back(ZFJTrailing_decaypdgId_FromGenMatch[tmpZDecItr]);
                                    }

                                    ZJPair_InvMass_FromTaggedGenMatchL = ZJPair_InvMass_FromGenMatch;
                                    ZJPair_EtaSep_FromTaggedGenMatchL = ZJPair_EtaSep_FromGenMatch;
                                    ZJGenTaggedTree->Fill();

                                    ZJLead_decaypdgId_FromTaggedGenMatchL.clear();
                                    ZJTrailing_decaypdgId_FromTaggedGenMatchL.clear();


                                }

                                

                                if (hJetFound){
                                    ROOT::Math::PtEtaPhiMVector tmpHFJVec  = ROOT::Math::PtEtaPhiMVector(HFJ_pt_FromGenMatch,HFJ_eta_FromGenMatch,HFJ_phi_FromGenMatch,HFJ_mass_FromGenMatch);

                                    ROOT::Math::PtEtaPhiMVector tmpHZJVec = tmpHFJVec+tmpZJPairVec;
                                    
                                    ZHJ_ZPairPlusHInvMass_FromGenMatchL = tmpHZJVec.M();
                                    ZHJGenTree->Fill();

                                    if (ZIsHadronic) {

                                        ZHJ_ZPairPlusHInvMass_FromTaggedGenMatchL = tmpHZJVec.M();
                                        ZHJGenTaggedTree->Fill();

                                    }
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

                            nHDecay_FromGenRawL = nHFJDecay_FromGenMatch;
                            //H_decaypdgId_FromGenRawL = HFJ_decaypdgId_FromGenMatch;

                            for (UInt_t tmpHDecItr=0;tmpHDecItr<HFJ_decaypdgId_FromGenMatch.size();tmpHDecItr++){
                                H_decaypdgId_FromGenRawL.push_back(HFJ_decaypdgId_FromGenMatch[tmpHDecItr]);
                            }

                            ZOne_pt_FromGenRawL = ZOne_pt_FromGenRaw;
                            ZOne_eta_FromGenRawL = ZOne_eta_FromGenRaw;
                            ZOne_phi_FromGenRawL = ZOne_phi_FromGenRaw;
                            ZOne_mass_FromGenRawL = ZOne_mass_FromGenRaw;
                            ZOne_pdgId_FromGenRawL = ZOne_pdgId_FromGenRaw;
                            ZOne_genPartIdxMother_FromGenRawL = ZOne_genPartIdxMother_FromGenRaw;

                            nZOneDecay_FromGenRawL = nZFJLeadDecay_FromGenMatch;
                            //ZOne_decaypdgId_FromGenRawL = ZFJLead_decaypdgId_FromGenMatch;

                            for (UInt_t tmpZDecItr=0;tmpZDecItr<ZFJLead_decaypdgId_FromGenMatch.size();tmpZDecItr++){
                                ZOne_decaypdgId_FromGenRawL.push_back(ZFJLead_decaypdgId_FromGenMatch[tmpZDecItr]);
                            }

                            ZTwo_pt_FromGenRawL = ZTwo_pt_FromGenRaw;
                            ZTwo_eta_FromGenRawL = ZTwo_eta_FromGenRaw;
                            ZTwo_phi_FromGenRawL = ZTwo_phi_FromGenRaw;
                            ZTwo_mass_FromGenRawL = ZTwo_mass_FromGenRaw;
                            ZTwo_pdgId_FromGenRawL = ZTwo_pdgId_FromGenRaw;
                            ZTwo_genPartIdxMother_FromGenRawL = ZTwo_genPartIdxMother_FromGenRaw;

                            nZTwoDecay_FromGenRawL = nZFJTrailingDecay_FromGenMatch;
                            //ZTwo_decaypdgId_FromGenRawL = ZFJTrailing_decaypdgId_FromGenMatch;

                            for (UInt_t tmpZDecItr=0;tmpZDecItr<ZFJTrailing_decaypdgId_FromGenMatch.size();tmpZDecItr++){
                                ZTwo_decaypdgId_FromGenRawL.push_back(ZFJTrailing_decaypdgId_FromGenMatch[tmpZDecItr]);
                            }

                            ZPair_InvMass_FromGenRawL = ZPair_InvMass_FromGenRaw;
                            ZPair_EtaSep_FromGenRawL = ZPair_EtaSep_FromGenRaw;

                            ZPairPlusH_InvMass_FromGenRawL = ZPairPlusH_InvMass_FromGenRaw;

                            GenRawTree->Fill();

                            H_decaypdgId_FromGenRawL.clear();
                            ZOne_decaypdgId_FromGenRawL.clear();
                            ZTwo_decaypdgId_FromGenRawL.clear();


                            if (ZIsHadronic) {

                                H_pt_FromTaggedGenRawL = H_pt_FromGenRaw;
                                H_eta_FromTaggedGenRawL = H_eta_FromGenRaw;
                                H_phi_FromTaggedGenRawL = H_phi_FromGenRaw;
                                H_mass_FromTaggedGenRawL = H_mass_FromGenRaw;
                                H_pdgId_FromTaggedGenRawL = H_pdgId_FromGenRaw;
                                H_genPartIdxMother_FromTaggedGenRawL = H_genPartIdxMother_FromGenRaw;

                                nHDecay_FromTaggedGenRawL = nHFJDecay_FromGenMatch;
                                H_decaypdgId_FromTaggedGenRawL = HFJ_decaypdgId_FromGenMatch;


                                ZOne_pt_FromTaggedGenRawL = ZOne_pt_FromGenRaw;
                                ZOne_eta_FromTaggedGenRawL = ZOne_eta_FromGenRaw;
                                ZOne_phi_FromTaggedGenRawL = ZOne_phi_FromGenRaw;
                                ZOne_mass_FromTaggedGenRawL = ZOne_mass_FromGenRaw;
                                ZOne_pdgId_FromTaggedGenRawL = ZOne_pdgId_FromGenRaw;
                                ZOne_genPartIdxMother_FromTaggedGenRawL = ZOne_genPartIdxMother_FromGenRaw;

                                nZOneDecay_FromTaggedGenRawL = nZFJLeadDecay_FromGenMatch;
                                ZOne_decaypdgId_FromTaggedGenRawL = ZFJLead_decaypdgId_FromGenMatch;

                                ZTwo_pt_FromTaggedGenRawL = ZTwo_pt_FromGenRaw;
                                ZTwo_eta_FromTaggedGenRawL = ZTwo_eta_FromGenRaw;
                                ZTwo_phi_FromTaggedGenRawL = ZTwo_phi_FromGenRaw;
                                ZTwo_mass_FromTaggedGenRawL = ZTwo_mass_FromGenRaw;
                                ZTwo_pdgId_FromTaggedGenRawL = ZTwo_pdgId_FromGenRaw;
                                ZTwo_genPartIdxMother_FromTaggedGenRawL = ZTwo_genPartIdxMother_FromGenRaw;

                                nZTwoDecay_FromTaggedGenRawL = nZFJTrailingDecay_FromGenMatch;
                                ZTwo_decaypdgId_FromTaggedGenRawL = ZFJTrailing_decaypdgId_FromGenMatch;

                                ZPair_InvMass_FromTaggedGenRawL = ZPair_InvMass_FromGenRaw;
                                ZPair_EtaSep_FromTaggedGenRawL = ZPair_EtaSep_FromGenRaw;

                                ZPairPlusH_InvMass_FromTaggedGenRawL = ZPairPlusH_InvMass_FromGenRaw;

                                GenRawTaggedTree->Fill();

                            }
                            

                        }
                        //std::cout << evCount-1 << " " << ZIsHadronic << "\n";
                        if (ZIsHadronic) {

                            ZOne_pt_FromTaggedLHERawL = ZOne_pt_FromLHERaw;
                            ZOne_eta_FromTaggedLHERawL = ZOne_eta_FromLHERaw;
                            ZOne_phi_FromTaggedLHERawL = ZOne_phi_FromLHERaw;
                            ZOne_mass_FromTaggedLHERawL = ZOne_mass_FromLHERaw;

                            ZTwo_pt_FromTaggedLHERawL = ZTwo_pt_FromLHERaw;
                            ZTwo_eta_FromTaggedLHERawL = ZTwo_eta_FromLHERaw;
                            ZTwo_phi_FromTaggedLHERawL = ZTwo_phi_FromLHERaw;
                            ZTwo_mass_FromTaggedLHERawL = ZTwo_mass_FromLHERaw;

                            ZPair_InvMass_FromTaggedLHERawL = ZPair_InvMass_FromLHERaw;
                            ZPair_EtaSep_FromTaggedLHERawL = ZPair_EtaSep_FromLHERaw;

                            H_pt_FromTaggedLHERawL = H_pt_FromLHERaw;
                            H_eta_FromTaggedLHERawL = H_eta_FromLHERaw;
                            H_phi_FromTaggedLHERawL = H_phi_FromLHERaw;
                            H_mass_FromTaggedLHERawL = H_mass_FromLHERaw;

                            ZPairPlusH_InvMass_FromTaggedLHERawL = ZPairPlusH_InvMass_FromLHERaw;

                            JOne_pt_FromTaggedLHERawL = JOne_pt_FromLHERaw;
                            JOne_eta_FromTaggedLHERawL = JOne_eta_FromLHERaw;
                            JOne_pdgId_FromTaggedLHERawL = JOne_pdgId_FromLHERaw;

                            JTwo_pt_FromTaggedLHERawL = JTwo_pt_FromLHERaw;
                            JTwo_eta_FromTaggedLHERawL = JTwo_eta_FromLHERaw;
                            JTwo_pdgId_FromTaggedLHERawL = JTwo_pdgId_FromLHERaw;

                            JOne_invmass_FromTaggedLHERawL = JOne_invmass_FromLHERaw;
                            JTwo_invmass_FromTaggedLHERawL = JTwo_invmass_FromLHERaw;

                            JOne_phi_FromTaggedLHERawL = JOne_phi_FromLHERaw;

                            JTwo_phi_FromTaggedLHERawL = JTwo_phi_FromLHERaw;
                            JPair_invmass_FromTaggedLHERawL = JPair_invmass_FromLHERaw;

                            J_etasep_FromTaggedLHERawL = J_etasep_FromLHERaw;

                            RawTaggedTree->Fill();

                            if (hGenFound && hJetFound) {

                                HFJ_pt_FromTaggedGenMatchL = HFJ_pt_FromGenMatch;
                                HFJ_eta_FromTaggedGenMatchL = HFJ_eta_FromGenMatch;
                                HFJ_phi_FromTaggedGenMatchL = HFJ_phi_FromGenMatch;
                                HFJ_mass_FromTaggedGenMatchL = HFJ_mass_FromGenMatch;
                                HFJ_dRFromFJ_FromTaggedGenMatchL = HFJ_dRFromFJ_FromGenMatch;

                                nHFJDecay_FromTaggedGenMatchL = nHFJDecay_FromGenMatch;
                                HFJ_decaypdgId_FromTaggedGenMatchL = HFJ_decaypdgId_FromGenMatch;
                                    
                                HFJGenTaggedTree->Fill();
                            }




                        }
                            
                    }
                }
            }
            



            
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
                passesCutsBool = true;

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

    std::cout << "passes all cuts: " << passesCutsCtr << " -------------------\n";
    std::cout << "evPassCount: " << evPassCount << "\n";

    std::cout << "ZFJSameJetCtr " << ZFJSameJetCtr << "\n";
    std::cout << "ZJSameJetCtr " << ZJSameJetCtr << "\n";

    std::cout << "ZFJSameJetTaggedCtr " << ZFJSameJetTaggedCtr << "\n";
    std::cout << "ZJSameJetTaggedCtr " << ZJSameJetTaggedCtr << "\n";

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
        SelectedTree->Write("",TObject::kOverwrite);

        RawTaggedTree->Write("",TObject::kOverwrite);
        if (useFJGenMatchTree) {
            ZFJGenTree->Write("",TObject::kOverwrite);
            HFJGenTree->Write("",TObject::kOverwrite);
            ZHFJGenTree->Write("",TObject::kOverwrite);

            ZFJGenTaggedTree->Write("",TObject::kOverwrite);
            HFJGenTaggedTree->Write("",TObject::kOverwrite);
            ZHFJGenTaggedTree->Write("",TObject::kOverwrite);
            
            
        }
        if (useJGenMatchTree) {
            ZJGenTree->Write("",TObject::kOverwrite);
            ZHJGenTree->Write("",TObject::kOverwrite);

            ZJGenTaggedTree->Write("",TObject::kOverwrite);
            ZHJGenTaggedTree->Write("",TObject::kOverwrite);
        }
        if (useJGenMatchTree || useFJGenMatchTree) {
            GenRawTree->Write("",TObject::kOverwrite);
            GenRawTaggedTree->Write("",TObject::kOverwrite);
        }

    }

    outFile->Close();
}