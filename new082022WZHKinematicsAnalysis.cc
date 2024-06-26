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


void new082022WZHKinematicsAnalysis(UInt_t fileInd){
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
    bool WZHBool = false;

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
    else if (SDC2Vm2p5MC){
        saveName = "SDC2Vm2p5MC";
        isBackground = false;
        int arrSize = sizeof(SDC2Vm2p5MCAr)/sizeof(SDC2Vm2p5MCAr[0]);
        std::string tmpStrWithPath = SDC2Vm2p5MCAr[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2Vm2p5MCAr[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2Vm2MC){
        saveName = "SDC2Vm2MC";
        isBackground = false;
        int arrSize = sizeof(SDC2Vm2MCAr)/sizeof(SDC2Vm2MCAr[0]);
        std::string tmpStrWithPath = SDC2Vm2MCAr[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2Vm2MCAr[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2Vm1MC){
        saveName = "SDC2Vm1MC";
        isBackground = false;
        int arrSize = sizeof(SDC2Vm1MCAr)/sizeof(SDC2Vm1MCAr[0]);
        std::string tmpStrWithPath = SDC2Vm1MCAr[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2Vm1MCAr[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2V0MC){
        saveName = "SDC2V0MC";
        isBackground = false;
        int arrSize = sizeof(SDC2V0MCAr)/sizeof(SDC2V0MCAr[0]);
        std::string tmpStrWithPath = SDC2V0MCAr[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V0MCAr[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2V1MC){
        saveName = "SDC2V1MC";
        isBackground = false;
        int arrSize = sizeof(SDC2V1MCAr)/sizeof(SDC2V1MCAr[0]);
        std::string tmpStrWithPath = SDC2V1MCAr[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V1MCAr[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2V4MC){
        saveName = "SDC2V4MC";
        isBackground = false;
        int arrSize = sizeof(SDC2V4MCAr)/sizeof(SDC2V4MCAr[0]);
        std::string tmpStrWithPath = SDC2V4MCAr[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V4MCAr[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2V4p5MC){
        saveName = "SDC2V4p5MC";
        isBackground = false;
        int arrSize = sizeof(SDC2V4p5MCAr)/sizeof(SDC2V4p5MCAr[0]);
        std::string tmpStrWithPath = SDC2V4p5MCAr[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V4p5MCAr[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2V3MCV2){
        saveName = "SDC2V3MCV2";
        isBackground = false;
        int arrSize = sizeof(SDC2V3MCV2Ar)/sizeof(SDC2V3MCV2Ar[0]);
        std::string tmpStrWithPath = SDC2V3MCV2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V3MCV2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2Vm2p5MCV2){
        saveName = "SDC2Vm2p5MCV2";
        isBackground = false;
        int arrSize = sizeof(SDC2Vm2p5MCV2Ar)/sizeof(SDC2Vm2p5MCV2Ar[0]);
        std::string tmpStrWithPath = SDC2Vm2p5MCV2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2Vm2p5MCV2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2Vm2MCV2){
        saveName = "SDC2Vm2MCV2";
        isBackground = false;
        int arrSize = sizeof(SDC2Vm2MCV2Ar)/sizeof(SDC2Vm2MCV2Ar[0]);
        std::string tmpStrWithPath = SDC2Vm2MCV2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2Vm2MCV2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2Vm1MCV2){
        saveName = "SDC2Vm1MCV2";
        isBackground = false;
        int arrSize = sizeof(SDC2Vm1MCV2Ar)/sizeof(SDC2Vm1MCV2Ar[0]);
        std::string tmpStrWithPath = SDC2Vm1MCV2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2Vm1MCV2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2V0MCV2){
        saveName = "SDC2V0MCV2";
        isBackground = false;
        int arrSize = sizeof(SDC2V0MCV2Ar)/sizeof(SDC2V0MCV2Ar[0]);
        std::string tmpStrWithPath = SDC2V0MCV2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V0MCV2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2V1MCV2){
        saveName = "SDC2V1MCV2";
        isBackground = false;
        int arrSize = sizeof(SDC2V1MCV2Ar)/sizeof(SDC2V1MCV2Ar[0]);
        std::string tmpStrWithPath = SDC2V1MCV2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V1MCV2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2V4MCV2){
        saveName = "SDC2V4MCV2";
        isBackground = false;
        int arrSize = sizeof(SDC2V4MCV2Ar)/sizeof(SDC2V4MCV2Ar[0]);
        std::string tmpStrWithPath = SDC2V4MCV2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V4MCV2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2V4p5MCV2){
        saveName = "SDC2V4p5MCV2";
        isBackground = false;
        int arrSize = sizeof(SDC2V4p5MCV2Ar)/sizeof(SDC2V4p5MCV2Ar[0]);
        std::string tmpStrWithPath = SDC2V4p5MCV2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V4p5MCV2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }

    else if (SDC2V3MCWZHV2){
        WZHBool = true;
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
        WZHBool = true;
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
        WZHBool = true;
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
        WZHBool = true;
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
        WZHBool = true;
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
        WZHBool = true;
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
        WZHBool = true;
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
        WZHBool = true;
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
    std::string outFileStr = "new082022KinematicsAnalysis"+saveName+"_"+std::to_string(fileInd)+".root";
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
    

    TTree *evNumTree = new TTree("evNumTree","evNumTree");

    evNumTree->Branch("nEv",&nEv,"nEv/i");
    
    Double_t genWeightL;

    Double_t HPtL;
    Double_t ZPtL;
    Double_t WPtL;
    Double_t HPlusBosonsPtL;
    Double_t HPlusBosonsPlusVBFPtL;
    Double_t HPlusBosonsPlusVBFVecPtL;
    Double_t HPlusBosonsPlusVBFVecOverScalarPtL;
    Double_t HPlusBosonsVecSumPtL;
    Double_t HPlusBosonsInvMassL;
    Double_t JetLeadPtL;
    Double_t JetTrailingPtL;
    Double_t JetLeadEtaL;
    Double_t JetTrailingEtaL;
    Double_t JetPairDEtaL;
    Int_t JetLeadPDGIdL;
    Int_t JetTrailingPDGIdL;


    TTree *LHEEventsTree = new TTree("LHEEventsTree", "LHEEventsTree");
    //gen weights
    LHEEventsTree->Branch("genWeightL",&genWeightL,"genWeightL/D");

    //Jets    
    LHEEventsTree->Branch("HPtL",&HPtL,"HPtL/D");
    LHEEventsTree->Branch("ZPtL",&ZPtL,"ZPtL/D");
    LHEEventsTree->Branch("WPtL",&WPtL,"WPtL/D");
    LHEEventsTree->Branch("HPlusBosonsPtL",&HPlusBosonsPtL,"HPlusBosonsPtL/D");
    LHEEventsTree->Branch("HPlusBosonsInvMassL",&HPlusBosonsInvMassL,"HPlusBosonsInvMassL/D");
    LHEEventsTree->Branch("HPlusBosonsPlusVBFPtL",&HPlusBosonsPlusVBFPtL,"HPlusBosonsPlusVBFPtL/D");
    LHEEventsTree->Branch("HPlusBosonsPlusVBFVecPtL",&HPlusBosonsPlusVBFVecPtL,"HPlusBosonsPlusVBFVecPtL/D");
    LHEEventsTree->Branch("HPlusBosonsPlusVBFVecOverScalarPtL",&HPlusBosonsPlusVBFVecOverScalarPtL,"HPlusBosonsPlusVBFVecOverScalarPtL/D");
    LHEEventsTree->Branch("JetLeadPtL",&JetLeadPtL,"JetLeadPtL/D");
    LHEEventsTree->Branch("JetTrailingPtL",&JetTrailingPtL,"JetTrailingPtL/D");
    LHEEventsTree->Branch("JetLeadEtaL",&JetLeadEtaL,"JetLeadEtaL/D");
    LHEEventsTree->Branch("JetTrailingEtaL",&JetTrailingEtaL,"JetTrailingEtaL/D");
    LHEEventsTree->Branch("JetPairDEtaL",&JetPairDEtaL,"JetPairDEtaL/D");
    LHEEventsTree->Branch("JetLeadPDGIdL",&JetLeadPDGIdL,"JetLeadPDGIdL/I");
    LHEEventsTree->Branch("JetTrailingPDGIdL",&JetTrailingPDGIdL,"JetTrailingPDGIdL/I");

    Double_t sumOfGenWeights = 0;
    
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
        TTreeReaderArray<Float_t> LHEPart_eta(myEventsReader, "LHEPart_eta");
        TTreeReaderArray<Float_t> LHEPart_phi(myEventsReader, "LHEPart_phi");
        TTreeReaderArray<Float_t> LHEPart_mass(myEventsReader, "LHEPart_mass");


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


            //--------------KINEMATICS--------------

            genWeightL = *genWeight;

            float JOne_pdgId_FromLHERaw;
            float JTwo_pdgId_FromLHERaw;

            UInt_t lenLHEPart = *nLHEPart;
            Int_t tmpZCtr = 0;
            Int_t tmpHCtr = 0;
            Int_t tmpWCtr = 0;
            Int_t tmpJCtr = 0;
            Int_t tmpHInd = -1;
            std::vector<UInt_t>tmpJAr;
            std::vector<UInt_t>tmpZAr;
            std::vector<UInt_t>tmpWAr;
            Int_t tmpPDGId = 0;

            for (UInt_t LHEItr=0; LHEItr<lenLHEPart;LHEItr++){
                tmpPDGId = LHEPart_pdgId[LHEItr];
                if (tmpPDGId == 23){
                    tmpZAr.push_back(LHEItr);
                    tmpZCtr += 1;
                    if (tmpZCtr > 2) std::cout << "ERROR MORE THAN 1 Z IN WZH LHE\n";
                    
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
                else if (abs(tmpPDGId) == 24){
                    tmpWAr.push_back(LHEItr);
                    tmpWCtr += 1;
                    if (tmpWCtr > 2) std::cout << "ERROR MORE THAN 1 W IN WZH LHE\n";
                    
                }
                else std::cout << "ERROR UNKNOWN PARTICLE " << tmpPDGId << " IN LHE\n";
            }
            if (tmpZCtr == 1 && tmpWCtr == 1 && tmpHCtr == 1 && tmpJCtr == 4 && tmpJAr.size() == 2){

                HPtL = LHEPart_pt[tmpHInd];


                ZPtL = LHEPart_pt[tmpZAr[0]];
                WPtL = LHEPart_pt[tmpWAr[0]];
                HPlusBosonsPtL = HPtL+ZPtL+WPtL;
                ROOT::Math::PtEtaPhiMVector HVec = ROOT::Math::PtEtaPhiMVector(HPtL, LHEPart_eta[tmpHInd], LHEPart_phi[tmpHInd], LHEPart_mass[tmpHInd]);
                ROOT::Math::PtEtaPhiMVector ZVec = ROOT::Math::PtEtaPhiMVector(ZPtL, LHEPart_eta[tmpZAr[0]], LHEPart_phi[tmpZAr[0]], LHEPart_mass[tmpZAr[0]]);
                ROOT::Math::PtEtaPhiMVector WVec = ROOT::Math::PtEtaPhiMVector(WPtL, LHEPart_eta[tmpWAr[0]], LHEPart_phi[tmpWAr[0]], LHEPart_mass[tmpWAr[0]]);
                ROOT::Math::PtEtaPhiMVector sumVec =HVec+ZVec+WVec;
                HPlusBosonsInvMassL = sumVec.M();
                ROOT::Math::PtEtaPhiMVector jetOneVec = ROOT::Math::PtEtaPhiMVector(LHEPart_pt[tmpJAr[0]], LHEPart_eta[tmpJAr[0]], LHEPart_phi[tmpJAr[0]], LHEPart_mass[tmpJAr[0]]);
                ROOT::Math::PtEtaPhiMVector jetTwoVec = ROOT::Math::PtEtaPhiMVector(LHEPart_pt[tmpJAr[1]], LHEPart_eta[tmpJAr[1]], LHEPart_phi[tmpJAr[1]], LHEPart_mass[tmpJAr[1]]);

                ROOT::Math::PtEtaPhiMVector sumPlusVBFJetsVec = HVec+ZVec+WVec+jetOneVec+jetTwoVec;

                HPlusBosonsPlusVBFPtL = HPtL+ZPtL+WPtL+LHEPart_pt[tmpJAr[0]]+LHEPart_pt[tmpJAr[1]];
                HPlusBosonsPlusVBFVecPtL = sumPlusVBFJetsVec.Pt();
                if (HPlusBosonsPlusVBFPtL != 0){
                    HPlusBosonsPlusVBFVecOverScalarPtL = HPlusBosonsPlusVBFVecPtL / HPlusBosonsPlusVBFPtL;
                }
                else {
                    HPlusBosonsPlusVBFVecOverScalarPtL = 0;
                }

                float tmpZLHEPartEta = LHEPart_eta[tmpZAr[0]];
                float tmpWLHEPartEta = LHEPart_eta[tmpWAr[0]];

                float tmpLHEPartPtOne = LHEPart_pt[tmpJAr[0]];
                float tmpLHEPartPtTwo = LHEPart_pt[tmpJAr[1]];

                float tmpLHEPartEtaOne = LHEPart_eta[tmpJAr[0]];
                float tmpLHEPartEtaTwo = LHEPart_eta[tmpJAr[1]];

                JetPairDEtaL = abs(tmpLHEPartEtaOne - tmpLHEPartEtaTwo);

                if (tmpLHEPartPtOne >= tmpLHEPartPtTwo) {
                    JetLeadPtL = tmpLHEPartPtOne;
                    JetTrailingPtL = tmpLHEPartPtTwo;
                    JetLeadEtaL = tmpLHEPartEtaOne;
                    JetTrailingEtaL = tmpLHEPartEtaTwo;
                    JetLeadPDGIdL = LHEPart_pdgId[tmpJAr[0]];
                    JetTrailingPDGIdL = LHEPart_pdgId[tmpJAr[1]];

                }
                else{
                    JetLeadPtL = tmpLHEPartPtTwo;
                    JetTrailingPtL = tmpLHEPartPtOne;
                    JetLeadEtaL = tmpLHEPartEtaTwo;
                    JetTrailingEtaL = tmpLHEPartEtaOne;
                    JetLeadPDGIdL = LHEPart_pdgId[tmpJAr[1]];
                    JetTrailingPDGIdL = LHEPart_pdgId[tmpJAr[0]];

                }
            }

            LHEEventsTree->Fill();






        }
    }
    if (debug) std::cout << "Filling complete \n";

    clock_t endt = clock();
    double time_spent = (double)(endt - startt) / CLOCKS_PER_SEC;


    std::cout << "Finished file loop. " << "time: " << time_spent << "\n";

    nEv = evRunOver;
    evNumTree->Fill();

    std::cout << "evRunOver: " << evRunOver << " -------------------\n";
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

    outFile->cd();
    evNumTree->Write("",TObject::kOverwrite);
    LHEEventsTree->Write("",TObject::kOverwrite);

    outFile->Close();
}
