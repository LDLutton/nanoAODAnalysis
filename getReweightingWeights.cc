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


void getReweightingWeights(UInt_t fileInd){
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

    else if (SDC2V3MC2017V2){
        saveName = "SDC2V3MC2017V2";
        isBackground = false;
        int arrSize = sizeof(SDC2V3MC2017V2Ar)/sizeof(SDC2V3MC2017V2Ar[0]);
        std::string tmpStrWithPath = SDC2V3MC2017V2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V3MC2017V2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2Vm2p5MC2017V2){
        saveName = "SDC2Vm2p5MC2017V2";
        isBackground = false;
        int arrSize = sizeof(SDC2Vm2p5MC2017V2Ar)/sizeof(SDC2Vm2p5MC2017V2Ar[0]);
        std::string tmpStrWithPath = SDC2Vm2p5MC2017V2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2Vm2p5MC2017V2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2Vm2MC2017V2){
        saveName = "SDC2Vm2MC2017V2";
        isBackground = false;
        int arrSize = sizeof(SDC2Vm2MC2017V2Ar)/sizeof(SDC2Vm2MC2017V2Ar[0]);
        std::string tmpStrWithPath = SDC2Vm2MC2017V2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2Vm2MC2017V2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2Vm1MC2017V2){
        saveName = "SDC2Vm1MC2017V2";
        isBackground = false;
        int arrSize = sizeof(SDC2Vm1MC2017V2Ar)/sizeof(SDC2Vm1MC2017V2Ar[0]);
        std::string tmpStrWithPath = SDC2Vm1MC2017V2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2Vm1MC2017V2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2V0MC2017V2){
        saveName = "SDC2V0MC2017V2";
        isBackground = false;
        int arrSize = sizeof(SDC2V0MC2017V2Ar)/sizeof(SDC2V0MC2017V2Ar[0]);
        std::string tmpStrWithPath = SDC2V0MC2017V2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V0MC2017V2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2V1MC2017V2){
        saveName = "SDC2V1MC2017V2";
        isBackground = false;
        int arrSize = sizeof(SDC2V1MC2017V2Ar)/sizeof(SDC2V1MC2017V2Ar[0]);
        std::string tmpStrWithPath = SDC2V1MC2017V2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V1MC2017V2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2V4MC2017V2){
        saveName = "SDC2V4MC2017V2";
        isBackground = false;
        int arrSize = sizeof(SDC2V4MC2017V2Ar)/sizeof(SDC2V4MC2017V2Ar[0]);
        std::string tmpStrWithPath = SDC2V4MC2017V2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V4MC2017V2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2V4p5MC2017V2){
        saveName = "SDC2V4p5MC2017V2";
        isBackground = false;
        int arrSize = sizeof(SDC2V4p5MC2017V2Ar)/sizeof(SDC2V4p5MC2017V2Ar[0]);
        std::string tmpStrWithPath = SDC2V4p5MC2017V2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V4p5MC2017V2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }

    else if (SDC2V3MCWZH2017V2){
        saveName = "SDC2V3MCWZH2017V2";
        isBackground = false;
        int arrSize = sizeof(SDC2V3MCWZH2017V2Ar)/sizeof(SDC2V3MCWZH2017V2Ar[0]);
        std::string tmpStrWithPath = SDC2V3MCWZH2017V2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V3MCWZH2017V2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2Vm2p5MCWZH2017V2){
        saveName = "SDC2Vm2p5MCWZH2017V2";
        isBackground = false;
        int arrSize = sizeof(SDC2Vm2p5MCWZH2017V2Ar)/sizeof(SDC2Vm2p5MCWZH2017V2Ar[0]);
        std::string tmpStrWithPath = SDC2Vm2p5MCWZH2017V2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2Vm2p5MCWZH2017V2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2Vm3MCWZH2017V2){
        saveName = "SDC2Vm3MCWZH2017V2";
        isBackground = false;
        int arrSize = sizeof(SDC2Vm3MCWZH2017V2Ar)/sizeof(SDC2Vm3MCWZH2017V2Ar[0]);
        std::string tmpStrWithPath = SDC2Vm3MCWZH2017V2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2Vm3MCWZH2017V2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2Vm1MCWZH2017V2){
        saveName = "SDC2Vm1MCWZH2017V2";
        isBackground = false;
        int arrSize = sizeof(SDC2Vm1MCWZH2017V2Ar)/sizeof(SDC2Vm1MCWZH2017V2Ar[0]);
        std::string tmpStrWithPath = SDC2Vm1MCWZH2017V2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2Vm1MCWZH2017V2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2V0MCWZH2017V2){
        saveName = "SDC2V0MCWZH2017V2";
        isBackground = false;
        int arrSize = sizeof(SDC2V0MCWZH2017V2Ar)/sizeof(SDC2V0MCWZH2017V2Ar[0]);
        std::string tmpStrWithPath = SDC2V0MCWZH2017V2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V0MCWZH2017V2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2V1MCWZH2017V2){
        saveName = "SDC2V1MCWZH2017V2";
        isBackground = false;
        int arrSize = sizeof(SDC2V1MCWZH2017V2Ar)/sizeof(SDC2V1MCWZH2017V2Ar[0]);
        std::string tmpStrWithPath = SDC2V1MCWZH2017V2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V1MCWZH2017V2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2V4MCWZH2017V2){
        saveName = "SDC2V4MCWZH2017V2";
        isBackground = false;
        int arrSize = sizeof(SDC2V4MCWZH2017V2Ar)/sizeof(SDC2V4MCWZH2017V2Ar[0]);
        std::string tmpStrWithPath = SDC2V4MCWZH2017V2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V4MCWZH2017V2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2V5MCWZH2017V2){
        saveName = "SDC2V5MCWZH2017V2";
        isBackground = false;
        int arrSize = sizeof(SDC2V5MCWZH2017V2Ar)/sizeof(SDC2V5MCWZH2017V2Ar[0]);
        std::string tmpStrWithPath = SDC2V5MCWZH2017V2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V5MCWZH2017V2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }


    else if (SDC2V3MC2016V2){
        saveName = "SDC2V3MC2016V2";
        isBackground = false;
        int arrSize = sizeof(SDC2V3MC2016V2Ar)/sizeof(SDC2V3MC2016V2Ar[0]);
        std::string tmpStrWithPath = SDC2V3MC2016V2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V3MC2016V2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2Vm2p5MC2016V2){
        saveName = "SDC2Vm2p5MC2016V2";
        isBackground = false;
        int arrSize = sizeof(SDC2Vm2p5MC2016V2Ar)/sizeof(SDC2Vm2p5MC2016V2Ar[0]);
        std::string tmpStrWithPath = SDC2Vm2p5MC2016V2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2Vm2p5MC2016V2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2Vm2MC2016V2){
        saveName = "SDC2Vm2MC2016V2";
        isBackground = false;
        int arrSize = sizeof(SDC2Vm2MC2016V2Ar)/sizeof(SDC2Vm2MC2016V2Ar[0]);
        std::string tmpStrWithPath = SDC2Vm2MC2016V2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2Vm2MC2016V2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2Vm1MC2016V2){
        saveName = "SDC2Vm1MC2016V2";
        isBackground = false;
        int arrSize = sizeof(SDC2Vm1MC2016V2Ar)/sizeof(SDC2Vm1MC2016V2Ar[0]);
        std::string tmpStrWithPath = SDC2Vm1MC2016V2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2Vm1MC2016V2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2V0MC2016V2){
        saveName = "SDC2V0MC2016V2";
        isBackground = false;
        int arrSize = sizeof(SDC2V0MC2016V2Ar)/sizeof(SDC2V0MC2016V2Ar[0]);
        std::string tmpStrWithPath = SDC2V0MC2016V2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V0MC2016V2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2V1MC2016V2){
        saveName = "SDC2V1MC2016V2";
        isBackground = false;
        int arrSize = sizeof(SDC2V1MC2016V2Ar)/sizeof(SDC2V1MC2016V2Ar[0]);
        std::string tmpStrWithPath = SDC2V1MC2016V2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V1MC2016V2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2V4MC2016V2){
        saveName = "SDC2V4MC2016V2";
        isBackground = false;
        int arrSize = sizeof(SDC2V4MC2016V2Ar)/sizeof(SDC2V4MC2016V2Ar[0]);
        std::string tmpStrWithPath = SDC2V4MC2016V2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V4MC2016V2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2V4p5MC2016V2){
        saveName = "SDC2V4p5MC2016V2";
        isBackground = false;
        int arrSize = sizeof(SDC2V4p5MC2016V2Ar)/sizeof(SDC2V4p5MC2016V2Ar[0]);
        std::string tmpStrWithPath = SDC2V4p5MC2016V2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V4p5MC2016V2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }

    else if (SDC2V3MCWZH2016V2){
        saveName = "SDC2V3MCWZH2016V2";
        isBackground = false;
        int arrSize = sizeof(SDC2V3MCWZH2016V2Ar)/sizeof(SDC2V3MCWZH2016V2Ar[0]);
        std::string tmpStrWithPath = SDC2V3MCWZH2016V2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V3MCWZH2016V2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2Vm2p5MCWZH2016V2){
        saveName = "SDC2Vm2p5MCWZH2016V2";
        isBackground = false;
        int arrSize = sizeof(SDC2Vm2p5MCWZH2016V2Ar)/sizeof(SDC2Vm2p5MCWZH2016V2Ar[0]);
        std::string tmpStrWithPath = SDC2Vm2p5MCWZH2016V2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2Vm2p5MCWZH2016V2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2Vm3MCWZH2016V2){
        saveName = "SDC2Vm3MCWZH2016V2";
        isBackground = false;
        int arrSize = sizeof(SDC2Vm3MCWZH2016V2Ar)/sizeof(SDC2Vm3MCWZH2016V2Ar[0]);
        std::string tmpStrWithPath = SDC2Vm3MCWZH2016V2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2Vm3MCWZH2016V2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2Vm1MCWZH2016V2){
        saveName = "SDC2Vm1MCWZH2016V2";
        isBackground = false;
        int arrSize = sizeof(SDC2Vm1MCWZH2016V2Ar)/sizeof(SDC2Vm1MCWZH2016V2Ar[0]);
        std::string tmpStrWithPath = SDC2Vm1MCWZH2016V2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2Vm1MCWZH2016V2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2V0MCWZH2016V2){
        saveName = "SDC2V0MCWZH2016V2";
        isBackground = false;
        int arrSize = sizeof(SDC2V0MCWZH2016V2Ar)/sizeof(SDC2V0MCWZH2016V2Ar[0]);
        std::string tmpStrWithPath = SDC2V0MCWZH2016V2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V0MCWZH2016V2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2V1MCWZH2016V2){
        saveName = "SDC2V1MCWZH2016V2";
        isBackground = false;
        int arrSize = sizeof(SDC2V1MCWZH2016V2Ar)/sizeof(SDC2V1MCWZH2016V2Ar[0]);
        std::string tmpStrWithPath = SDC2V1MCWZH2016V2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V1MCWZH2016V2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2V4MCWZH2016V2){
        saveName = "SDC2V4MCWZH2016V2";
        isBackground = false;
        int arrSize = sizeof(SDC2V4MCWZH2016V2Ar)/sizeof(SDC2V4MCWZH2016V2Ar[0]);
        std::string tmpStrWithPath = SDC2V4MCWZH2016V2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V4MCWZH2016V2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2V5MCWZH2016V2){
        saveName = "SDC2V5MCWZH2016V2";
        isBackground = false;
        int arrSize = sizeof(SDC2V5MCWZH2016V2Ar)/sizeof(SDC2V5MCWZH2016V2Ar[0]);
        std::string tmpStrWithPath = SDC2V5MCWZH2016V2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V5MCWZH2016V2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }


    else if (SDC2V3MC2016APVV2){
        saveName = "SDC2V3MC2016APVV2";
        isBackground = false;
        int arrSize = sizeof(SDC2V3MC2016APVV2Ar)/sizeof(SDC2V3MC2016APVV2Ar[0]);
        std::string tmpStrWithPath = SDC2V3MC2016APVV2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V3MC2016APVV2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2Vm2p5MC2016APVV2){
        saveName = "SDC2Vm2p5MC2016APVV2";
        isBackground = false;
        int arrSize = sizeof(SDC2Vm2p5MC2016APVV2Ar)/sizeof(SDC2Vm2p5MC2016APVV2Ar[0]);
        std::string tmpStrWithPath = SDC2Vm2p5MC2016APVV2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2Vm2p5MC2016APVV2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2Vm2MC2016APVV2){
        saveName = "SDC2Vm2MC2016APVV2";
        isBackground = false;
        int arrSize = sizeof(SDC2Vm2MC2016APVV2Ar)/sizeof(SDC2Vm2MC2016APVV2Ar[0]);
        std::string tmpStrWithPath = SDC2Vm2MC2016APVV2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2Vm2MC2016APVV2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2Vm1MC2016APVV2){
        saveName = "SDC2Vm1MC2016APVV2";
        isBackground = false;
        int arrSize = sizeof(SDC2Vm1MC2016APVV2Ar)/sizeof(SDC2Vm1MC2016APVV2Ar[0]);
        std::string tmpStrWithPath = SDC2Vm1MC2016APVV2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2Vm1MC2016APVV2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2V0MC2016APVV2){
        saveName = "SDC2V0MC2016APVV2";
        isBackground = false;
        int arrSize = sizeof(SDC2V0MC2016APVV2Ar)/sizeof(SDC2V0MC2016APVV2Ar[0]);
        std::string tmpStrWithPath = SDC2V0MC2016APVV2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V0MC2016APVV2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2V1MC2016APVV2){
        saveName = "SDC2V1MC2016APVV2";
        isBackground = false;
        int arrSize = sizeof(SDC2V1MC2016APVV2Ar)/sizeof(SDC2V1MC2016APVV2Ar[0]);
        std::string tmpStrWithPath = SDC2V1MC2016APVV2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V1MC2016APVV2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2V4MC2016APVV2){
        saveName = "SDC2V4MC2016APVV2";
        isBackground = false;
        int arrSize = sizeof(SDC2V4MC2016APVV2Ar)/sizeof(SDC2V4MC2016APVV2Ar[0]);
        std::string tmpStrWithPath = SDC2V4MC2016APVV2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V4MC2016APVV2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2V4p5MC2016APVV2){
        saveName = "SDC2V4p5MC2016APVV2";
        isBackground = false;
        int arrSize = sizeof(SDC2V4p5MC2016APVV2Ar)/sizeof(SDC2V4p5MC2016APVV2Ar[0]);
        std::string tmpStrWithPath = SDC2V4p5MC2016APVV2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V4p5MC2016APVV2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }

    else if (SDC2V3MCWZH2016APVV2){
        saveName = "SDC2V3MCWZH2016APVV2";
        isBackground = false;
        int arrSize = sizeof(SDC2V3MCWZH2016APVV2Ar)/sizeof(SDC2V3MCWZH2016APVV2Ar[0]);
        std::string tmpStrWithPath = SDC2V3MCWZH2016APVV2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V3MCWZH2016APVV2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2Vm2p5MCWZH2016APVV2){
        saveName = "SDC2Vm2p5MCWZH2016APVV2";
        isBackground = false;
        int arrSize = sizeof(SDC2Vm2p5MCWZH2016APVV2Ar)/sizeof(SDC2Vm2p5MCWZH2016APVV2Ar[0]);
        std::string tmpStrWithPath = SDC2Vm2p5MCWZH2016APVV2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2Vm2p5MCWZH2016APVV2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2Vm3MCWZH2016APVV2){
        saveName = "SDC2Vm3MCWZH2016APVV2";
        isBackground = false;
        int arrSize = sizeof(SDC2Vm3MCWZH2016APVV2Ar)/sizeof(SDC2Vm3MCWZH2016APVV2Ar[0]);
        std::string tmpStrWithPath = SDC2Vm3MCWZH2016APVV2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2Vm3MCWZH2016APVV2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2Vm1MCWZH2016APVV2){
        saveName = "SDC2Vm1MCWZH2016APVV2";
        isBackground = false;
        int arrSize = sizeof(SDC2Vm1MCWZH2016APVV2Ar)/sizeof(SDC2Vm1MCWZH2016APVV2Ar[0]);
        std::string tmpStrWithPath = SDC2Vm1MCWZH2016APVV2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2Vm1MCWZH2016APVV2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2V0MCWZH2016APVV2){
        saveName = "SDC2V0MCWZH2016APVV2";
        isBackground = false;
        int arrSize = sizeof(SDC2V0MCWZH2016APVV2Ar)/sizeof(SDC2V0MCWZH2016APVV2Ar[0]);
        std::string tmpStrWithPath = SDC2V0MCWZH2016APVV2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V0MCWZH2016APVV2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2V1MCWZH2016APVV2){
        saveName = "SDC2V1MCWZH2016APVV2";
        isBackground = false;
        int arrSize = sizeof(SDC2V1MCWZH2016APVV2Ar)/sizeof(SDC2V1MCWZH2016APVV2Ar[0]);
        std::string tmpStrWithPath = SDC2V1MCWZH2016APVV2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V1MCWZH2016APVV2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2V4MCWZH2016APVV2){
        saveName = "SDC2V4MCWZH2016APVV2";
        isBackground = false;
        int arrSize = sizeof(SDC2V4MCWZH2016APVV2Ar)/sizeof(SDC2V4MCWZH2016APVV2Ar[0]);
        std::string tmpStrWithPath = SDC2V4MCWZH2016APVV2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V4MCWZH2016APVV2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (SDC2V5MCWZH2016APVV2){
        saveName = "SDC2V5MCWZH2016APVV2";
        isBackground = false;
        int arrSize = sizeof(SDC2V5MCWZH2016APVV2Ar)/sizeof(SDC2V5MCWZH2016APVV2Ar[0]);
        std::string tmpStrWithPath = SDC2V5MCWZH2016APVV2Ar[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V5MCWZH2016APVV2Ar[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }

    else if (SDC2V2MCZZHReweight){
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
    else if (ZZBackground){
        //saveName = "";
        
        crossSection = 12.17;

        saveName = "ZZ";
        
        isBackground = true;
        int arrSize = sizeof(ZZBackgroundAr)/sizeof(ZZBackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(ZZBackgroundAr[i]);
        }
        */
        fileAr.push_back(ZZBackgroundAr[fileInd]);
    }
    else if (WWBackground){
        //saveName = "";
        
        crossSection = 75.95;

        saveName = "WW";
        
        isBackground = true;
        int arrSize = sizeof(WWBackgroundAr)/sizeof(WWBackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(WWBackgroundAr[i]);
        }
        */
        fileAr.push_back(WWBackgroundAr[fileInd]);
    }
    else if (WZBackground){
        //saveName = "";
        
        crossSection = 27.59;

        saveName = "WZ";
        
        isBackground = true;
        int arrSize = sizeof(WZBackgroundAr)/sizeof(WZBackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(WZBackgroundAr[i]);
        }
        */
        fileAr.push_back(WZBackgroundAr[fileInd]);
    }
    else if (TTbb_TTToHadronicBackground){
        //saveName = "QCDPT3200toInf";
        
        crossSection = 5.5;

        saveName = "TTbb_TTToHadronic";
        
        isBackground = true;
        int arrSize = sizeof(TTbb_TTToHadronicBackgroundAr)/sizeof(TTbb_TTToHadronicBackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(TTbb_TTToHadronicBackgroundAr[i]);
        }
        */
        fileAr.push_back(TTbb_TTToHadronicBackgroundAr[fileInd]);
    }
    else if (TTbb_TTTo2L2NuBackground){
        //saveName = "";
        
        crossSection = 2.9;

        saveName = "TTbb_TTTo2L2Nu";
        
        isBackground = true;
        int arrSize = sizeof(TTbb_TTTo2L2NuBackgroundAr)/sizeof(TTbb_TTTo2L2NuBackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(TTbb_TTTo2L2NuBackgroundAr[i]);
        }
        */
        fileAr.push_back(TTbb_TTTo2L2NuBackgroundAr[fileInd]);
    }
    else if (TTbb_TTToSemiLeptonicBackground){
        //saveName = "";
        
        crossSection = 4.7;

        saveName = "TTbb_TTToSemiLeptonic";
        
        isBackground = true;
        int arrSize = sizeof(TTbb_TTToSemiLeptonicBackgroundAr)/sizeof(TTbb_TTToSemiLeptonicBackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(TTbb_TTToSemiLeptonicBackgroundAr[i]);
        }
        */
        fileAr.push_back(TTbb_TTToSemiLeptonicBackgroundAr[fileInd]);
    }
    else if (testRun){
        saveName = "testRun";
        fileAr.push_back("./unweighted_eventspphzzjjQCD0SMHLOOP0NPE1NPcHWE1QEDE5ResMasAllVer100Ev10080Seed_0p999cHW100GeVIMJetCut_200.root");
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
    std::string outFileStr = "reweightingWeights"+saveName+"_"+std::to_string(fileInd)+".root";
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

    UInt_t evRunOver = 0;
    UInt_t evCount = 0;
    
    


    UInt_t nLHEReweightingWeightL;
    std::vector<Float_t> LHEReweightingWeightL;
    


    TTree *reweightTree = new TTree("reweightTree", "reweightTree");
    
    reweightTree->Branch("nLHEReweightingWeightL",&nLHEReweightingWeightL,"nLHEReweightingWeightL/i");
    reweightTree->Branch("LHEReweightingWeightL",&LHEReweightingWeightL);
    
    
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

        TTreeReaderValue<UInt_t> nLHEReweightingWeight(myEventsReader, "nLHEReweightingWeight");
        TTreeReaderArray<Float_t> LHEReweightingWeight(myEventsReader, "LHEReweightingWeight");

        
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
            //Increment event count
            evRunOver += 1;
            evCount += 1;
            bool overOneHundred = false;

            nLHEReweightingWeightL = *nLHEReweightingWeight;
            for (UInt_t reweightItr=0; reweightItr<*nLHEReweightingWeight;reweightItr++){
                LHEReweightingWeightL.push_back(LHEReweightingWeight[reweightItr]);
                if (LHEReweightingWeight[reweightItr] >=100) overOneHundred = true;
            }

            if (overOneHundred) {
                std::cout <<"High weight at ev " << evCount-1 << "\n";
                for (UInt_t reweightItr=0; reweightItr<*nLHEReweightingWeight;reweightItr++){
                    std::cout << reweightItr << " " << LHEReweightingWeight[reweightItr] << " ";
                }
                std::cout << "\n";
            }

            reweightTree->Fill();

            LHEReweightingWeightL.clear();
            

        }
    }
    if (debug) std::cout << "Filling complete \n";

    clock_t endt = clock();
    double time_spent = (double)(endt - startt) / CLOCKS_PER_SEC;


    std::cout << "Finished file loop. " << "time: " << time_spent << "\n";


    outFile->cd();
    reweightTree->Write("",TObject::kOverwrite);
    

    outFile->Close();
}
