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


//Copied from new082022GenChannelAnalysis.cc in 092022, which was my old 082022 attempt at remaking the
//DoHLTFilterBeforeAnalysis.cc code for WZH instead of ZZH

////////////////////////////////START OF MAIN FUNCTION////////////////////////////////
////////////////////////////////START OF MAIN FUNCTION////////////////////////////////
////////////////////////////////START OF MAIN FUNCTION////////////////////////////////
////////////////////////////////START OF MAIN FUNCTION////////////////////////////////


void DoWZHHLTFilterBeforeAnalysis(UInt_t fileInd){
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
    else if (SDC2V3MCWZHV2){
        
        saveName = "SDC2V3MCWZHV2";
        isBackground = false;
        int arrSize = sizeof(SDC2V3MCWZHV2Ar)/sizeof(SDC2V3MCWZHV2Ar[0]);
        std::string tmpStrWithPath = SDC2V3MCWZHV2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V3MCWZHV2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2Vm2p5MCWZHV2){
        
        saveName = "SDC2Vm2p5MCWZHV2";
        isBackground = false;
        int arrSize = sizeof(SDC2Vm2p5MCWZHV2Ar)/sizeof(SDC2Vm2p5MCWZHV2Ar[0]);
        std::string tmpStrWithPath = SDC2Vm2p5MCWZHV2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2Vm2p5MCWZHV2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2Vm3MCWZHV2){
        
        saveName = "SDC2Vm3MCWZHV2";
        isBackground = false;
        int arrSize = sizeof(SDC2Vm3MCWZHV2Ar)/sizeof(SDC2Vm3MCWZHV2Ar[0]);
        std::string tmpStrWithPath = SDC2Vm3MCWZHV2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2Vm3MCWZHV2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2Vm1MCWZHV2){
        
        saveName = "SDC2Vm1MCWZHV2";
        isBackground = false;
        int arrSize = sizeof(SDC2Vm1MCWZHV2Ar)/sizeof(SDC2Vm1MCWZHV2Ar[0]);
        std::string tmpStrWithPath = SDC2Vm1MCWZHV2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2Vm1MCWZHV2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2V0MCWZHV2){
        
        saveName = "SDC2V0MCWZHV2";
        isBackground = false;
        int arrSize = sizeof(SDC2V0MCWZHV2Ar)/sizeof(SDC2V0MCWZHV2Ar[0]);
        std::string tmpStrWithPath = SDC2V0MCWZHV2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V0MCWZHV2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2V1MCWZHV2){
        
        saveName = "SDC2V1MCWZHV2";
        isBackground = false;
        int arrSize = sizeof(SDC2V1MCWZHV2Ar)/sizeof(SDC2V1MCWZHV2Ar[0]);
        std::string tmpStrWithPath = SDC2V1MCWZHV2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V1MCWZHV2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2V4MCWZHV2){
        
        saveName = "SDC2V4MCWZHV2";
        isBackground = false;
        int arrSize = sizeof(SDC2V4MCWZHV2Ar)/sizeof(SDC2V4MCWZHV2Ar[0]);
        std::string tmpStrWithPath = SDC2V4MCWZHV2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V4MCWZHV2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2V5MCWZHV2){
        
        saveName = "SDC2V5MCWZHV2";
        isBackground = false;
        int arrSize = sizeof(SDC2V5MCWZHV2Ar)/sizeof(SDC2V5MCWZHV2Ar[0]);
        std::string tmpStrWithPath = SDC2V5MCWZHV2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V5MCWZHV2Ar[i];
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
    else if (testRun){
        saveName = "testRun";
        fileAr.push_back("./merged_0.root");
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






    float crossSectionAvg = 0.;
    UInt_t crossSectionCtr = 0;
    float totCrossSectionWeight = 0.;
    UInt_t totCrossSectionEvCount = 0;
    UInt_t evRunOver = 0;
    UInt_t evCount = 0;
    
    UInt_t nEv;

    Double_t sumOfGenWeights = 0;


    //Ctrs for HTobb
    UInt_t genWLepZLepChannelCtr = 0;
    UInt_t genWLepZHadronicChannelCtr = 0;
    UInt_t genWHadronicZLepChannelCtr = 0;
    UInt_t genWHadronicZHadronicChannelCtr = 0;
    UInt_t genOtherChannelCtr = 0;
    UInt_t genErrorChannelCtr = 0;


    Double_t genWLepZLepChannelWeightedCtr = 0;
    Double_t genWLepZHadronicChannelWeightedCtr = 0;
    Double_t genWHadronicZLepChannelWeightedCtr = 0;
    Double_t genWHadronicZHadronicChannelWeightedCtr = 0;
    Double_t genOtherChannelWeightedCtr = 0;
    Double_t genErrorChannelWeightedCtr = 0;

    //Ctrs for no HTobb
    UInt_t genWLepZLepChannelNoHTobbCtr = 0;
    UInt_t genWLepZHadronicChannelNoHTobbCtr = 0;
    UInt_t genWHadronicZLepChannelNoHTobbCtr = 0;
    UInt_t genWHadronicZHadronicChannelNoHTobbCtr = 0;
    UInt_t genOtherChannelNoHTobbCtr = 0;
    UInt_t genErrorChannelNoHTobbCtr = 0;

    Double_t genWLepZLepChannelNoHTobbWeightedCtr = 0;
    Double_t genWLepZHadronicChannelNoHTobbWeightedCtr = 0;
    Double_t genWHadronicZLepChannelNoHTobbWeightedCtr = 0;
    Double_t genWHadronicZHadronicChannelNoHTobbWeightedCtr = 0;
    Double_t genOtherChannelNoHTobbWeightedCtr = 0;
    Double_t genErrorChannelNoHTobbWeightedCtr = 0;


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
            }
            //Increment event count
            evRunOver += 1;
            evCount += 1;

            sumOfGenWeights += *genWeight;
            bool HTobbBool = false;


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
                }
                else{
                    if (debugGenPart) std::cout <<"H found\n";
                    if (abs(HFJ_decaypdgId_FromGenMatch[0]) == 5){
                        HTobbBool = true;
                        HTobbCtr += 1;
                        HTobbWeightedCtr += *genWeight;
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

                    if (finalZAr.size() != 1){
                        std::cout <<"ERROR ERROR, MORE OR LESS THAN ONE Z,evCount,finalZAr.size(),intermediaryZ,JOne_pdgId_FromLHERaw,JTwo_pdgId_FromLHERaw " << evCount-1<< " " << finalZAr.size() << " " << intermediaryZ << " "<<JOne_pdgId_FromLHERaw<< " " <<JTwo_pdgId_FromLHERaw << "\n";
                        if (tmpZAr.size()){
                            for (UInt_t tmpZItr=0;tmpZItr<tmpZAr.size();tmpZItr++){
                                for (UInt_t tmpZItrTwo=0;tmpZItrTwo<tmpZAr[tmpZItr].size();tmpZItrTwo++){
                                    std::cout <<"tmpZItr " << tmpZItr << " tmpZItrTwo " << tmpZItrTwo << " tmpZAr[tmpZItr][tmpZItrTwo] " << tmpZAr[tmpZItr][tmpZItrTwo] <<"\n";
                                }
                            }
                        }
                        if (finalZAr.size()){
                            for (UInt_t tmpZItr=0;tmpZItr<finalZAr.size();tmpZItr++){
                                std::cout << "finalZAr[tmpZItr] " << finalZAr[tmpZItr] << "\n";
                            }
                        }
                        if (HTobbBool){
                            genErrorChannelCtr += 1;
                            genErrorChannelWeightedCtr += *genWeight;
                        }
                        else{
                            genErrorChannelNoHTobbCtr += 1;
                            genErrorChannelNoHTobbWeightedCtr += *genWeight;
                        }

                    }
                    else{


                        if (debugGenPart) std::cout <<"Z found\n";
                        if (abs(HFJ_decaypdgId_FromGenMatch[0]) == 5){
                            HTobbBool = true;
                            HTobbCtr += 1;
                            HTobbWeightedCtr += *genWeight;
                        }
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
                            if (HTobbBool){
                                genErrorChannelCtr += 1;
                                genErrorChannelWeightedCtr += *genWeight;
                            }
                            else{
                                genErrorChannelNoHTobbCtr += 1;
                                genErrorChannelNoHTobbWeightedCtr += *genWeight;
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
                               
                            }



                            
                        }

                        if (WLepZLep) {

                            
                            if (HTobbBool){
                                genWLepZLepChannelCtr += 1;
                                genWLepZLepChannelWeightedCtr += *genWeight;

                            }
                            else{
                                genWLepZLepChannelNoHTobbCtr += 1;
                                genWLepZLepChannelNoHTobbWeightedCtr += *genWeight;
                            }

                        }

                        if (WLepZHadronic) {

                            
                            if (HTobbBool){
                                genWLepZHadronicChannelCtr += 1;
                                genWLepZHadronicChannelWeightedCtr += *genWeight;

                            }
                            else{
                                genWLepZHadronicChannelNoHTobbCtr += 1;
                                genWLepZHadronicChannelNoHTobbWeightedCtr += *genWeight;
                            }

                        }
                        if (WHadronicZLep) {

                            
                            if (HTobbBool){
                                genWHadronicZLepChannelCtr += 1;
                                genWHadronicZLepChannelWeightedCtr += *genWeight;

                            }
                            else{
                                genWHadronicZLepChannelNoHTobbCtr += 1;
                                genWHadronicZLepChannelNoHTobbWeightedCtr += *genWeight;
                            }

                        }

                        if (WHadronicZHadronic) {

                            
                            if (HTobbBool){
                                genWHadronicZHadronicChannelCtr += 1;
                                genWHadronicZHadronicChannelWeightedCtr += *genWeight;

                            }
                            else{
                                genWHadronicZHadronicChannelNoHTobbCtr += 1;
                                genWHadronicZHadronicChannelNoHTobbWeightedCtr += *genWeight;
                            }

                        }
                        else {
                            if (HTobbBool){
                                genOtherChannelCtr += 1;
                                genOtherChannelWeightedCtr += *genWeight;
                            }
                            else{
                                genOtherChannelNoHTobbCtr += 1;
                                genOtherChannelNoHTobbWeightedCtr += *genWeight;
                            }
                        }
                        

                        
                            
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

    std::cout << "evRunOver: " << evRunOver << " -------------------\n";
    std::cout << "sumOfGenWeights: " << sumOfGenWeights << "\n";

    std::cout << "HTobb Channel: " << HTobbCtr << " ------------------- " << HTobbWeightedCtr<< "\n";
    std::cout << "Channels with HTobb\n";



    std::cout << "Gen WLepZLep Channel: " << genWLepZLepChannelCtr << " ------------------- " << genWLepZLepChannelWeightedCtr<< "\n";
    std::cout << "Gen WLepZHadronic Channel: " << genWLepZHadronicChannelCtr << " ------------------- " << genWLepZHadronicChannelWeightedCtr<< "\n";

    std::cout << "Gen WHadronicZLep Channel: " << genWHadronicZLepChannelCtr << " ------------------- " << genWHadronicZLepChannelWeightedCtr<< "\n";

    std::cout << "Gen WHadronicZHadronic Channel: " << genWHadronicZHadronicChannelCtr << " ------------------- " << genWHadronicZHadronicChannelWeightedCtr<< "\n";
    
    std::cout << "Gen Other Channel: " << genOtherChannelCtr << " ------------------- " << genOtherChannelWeightedCtr<< "\n";
    std::cout << "Gen Error Channel: " << genErrorChannelCtr << " ------------------- " << genErrorChannelWeightedCtr<< "\n";

    std::cout << "Channels without HTobb\n";
    std::cout << "Gen NoHTobb WLepZLep Channel: " << genWLepZLepChannelNoHTobbCtr << " ------------------- " << genWLepZLepChannelNoHTobbWeightedCtr<< "\n";
    std::cout << "Gen NoHTobb WLepZHadronic Channel: " << genWLepZHadronicChannelNoHTobbCtr << " ------------------- " << genWLepZHadronicChannelNoHTobbWeightedCtr<< "\n";

    std::cout << "Gen NoHTobb WHadronicZLep Channel: " << genWHadronicZLepChannelNoHTobbCtr << " ------------------- " << genWHadronicZLepChannelNoHTobbWeightedCtr<< "\n";

    std::cout << "Gen NoHTobb WHadronicZHadronic Channel: " << genWHadronicZHadronicChannelNoHTobbCtr << " ------------------- " << genWHadronicZHadronicChannelNoHTobbWeightedCtr<< "\n";
    
    std::cout << "Gen NoHTobb Other Channel: " << genOtherChannelNoHTobbCtr << " ------------------- " << genOtherChannelNoHTobbWeightedCtr<< "\n";
    std::cout << "Gen NoHTobb Error Channel: " << genErrorChannelNoHTobbCtr << " ------------------- " << genErrorChannelNoHTobbWeightedCtr<< "\n";
    
    
    std::cout << "Cross section average before division: " << crossSectionAvg << "\n";
    std::cout << "Cross section counter: " << crossSectionCtr << "\n";
    crossSectionAvg = (crossSectionAvg*hTobbBR) / crossSectionCtr;
    std::cout << "Cross section average after division and hTobb branching ratio: " << crossSectionAvg << "\n";
    std::cout << "Tot Weight: " << totCrossSectionWeight <<"\n";
    std::cout << "Tot XS Count: " << totCrossSectionEvCount <<"\n";
    float crossSectionAvgAlt = totCrossSectionWeight/totCrossSectionEvCount;
    std::cout << "(Tot Weight*hTobbBR)/Tot XS Count: " << crossSectionAvgAlt*hTobbBR <<"\n";

}
