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


void new082022GetXSAndWeights(UInt_t fileInd){
    // Open the file. Note that the name of your file outside this class
    // will probably NOT be experiment.root.
    std::cout << "start\n";
    clock_t startt = clock();
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

    
    if (SDC2V3MCV2){
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
        
        
        
    }
    else if (SDC2V3MCWZHV2){
        saveName = "SDC2V3MCWZHV2";
        isBackground = false;
        int arrSize = sizeof(SDC2V3MCWZHV2Ar)/sizeof(SDC2V3MCWZHV2Ar[0]);
        std::string tmpStrWithPath = SDC2V3MCWZHV2Ar[fileInd];
        fileAr.push_back(tmpStrWithPath);
        
        
    }
    else if (SDC2Vm2p5MCWZHV2){
        saveName = "SDC2Vm2p5MCWZHV2";
        isBackground = false;
        int arrSize = sizeof(SDC2Vm2p5MCWZHV2Ar)/sizeof(SDC2Vm2p5MCWZHV2Ar[0]);
        std::string tmpStrWithPath = SDC2Vm2p5MCWZHV2Ar[fileInd];
        fileAr.push_back(tmpStrWithPath);
        
        
    }
    else if (SDC2Vm3MCWZHV2){
        saveName = "SDC2Vm3MCWZHV2";
        isBackground = false;
        int arrSize = sizeof(SDC2Vm3MCWZHV2Ar)/sizeof(SDC2Vm3MCWZHV2Ar[0]);
        std::string tmpStrWithPath = SDC2Vm3MCWZHV2Ar[fileInd];
        fileAr.push_back(tmpStrWithPath);
        
        
    }
    else if (SDC2Vm1MCWZHV2){
        saveName = "SDC2Vm1MCWZHV2";
        isBackground = false;
        int arrSize = sizeof(SDC2Vm1MCWZHV2Ar)/sizeof(SDC2Vm1MCWZHV2Ar[0]);
        std::string tmpStrWithPath = SDC2Vm1MCWZHV2Ar[fileInd];
        fileAr.push_back(tmpStrWithPath);
        
        
    }
    else if (SDC2V0MCWZHV2){
        saveName = "SDC2V0MCWZHV2";
        isBackground = false;
        int arrSize = sizeof(SDC2V0MCWZHV2Ar)/sizeof(SDC2V0MCWZHV2Ar[0]);
        std::string tmpStrWithPath = SDC2V0MCWZHV2Ar[fileInd];
        fileAr.push_back(tmpStrWithPath);
        
        
    }
    else if (SDC2V1MCWZHV2){
        saveName = "SDC2V1MCWZHV2";
        isBackground = false;
        int arrSize = sizeof(SDC2V1MCWZHV2Ar)/sizeof(SDC2V1MCWZHV2Ar[0]);
        std::string tmpStrWithPath = SDC2V1MCWZHV2Ar[fileInd];
        fileAr.push_back(tmpStrWithPath);
        
        
    }
    else if (SDC2V4MCWZHV2){
        saveName = "SDC2V4MCWZHV2";
        isBackground = false;
        int arrSize = sizeof(SDC2V4MCWZHV2Ar)/sizeof(SDC2V4MCWZHV2Ar[0]);
        std::string tmpStrWithPath = SDC2V4MCWZHV2Ar[fileInd];
        fileAr.push_back(tmpStrWithPath);
        
        
    }
    else if (SDC2V5MCWZHV2){
        saveName = "SDC2V5MCWZHV2";
        isBackground = false;
        int arrSize = sizeof(SDC2V5MCWZHV2Ar)/sizeof(SDC2V5MCWZHV2Ar[0]);
        std::string tmpStrWithPath = SDC2V5MCWZHV2Ar[fileInd];
        fileAr.push_back(tmpStrWithPath);
        
        
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
        
        
        
    }
    else if (testRun){
        saveName = "testRun";
        fileAr.push_back("./merged_0.root");
        
        
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





        }
    }
    if (debug) std::cout << "Filling complete \n";

    clock_t endt = clock();
    double time_spent = (double)(endt - startt) / CLOCKS_PER_SEC;


    std::cout << "Finished file loop. " << "time: " << time_spent << "\n";

    nEv = evRunOver;

    std::cout << "evRunOver: " << evRunOver << " -------------------\n";
    std::cout << "sumOfGenWeights: " << sumOfGenWeights << "\n";

    std::cout << "Cross section average before division: " << crossSectionAvg << "\n";
    std::cout << "Cross section counter: " << crossSectionCtr << "\n";
    crossSectionAvg = (crossSectionAvg) / crossSectionCtr;
    std::cout << "Cross section average after division: " << crossSectionAvg << "\n";
    std::cout << "Tot Weight: " << totCrossSectionWeight <<"\n";
    std::cout << "Tot XS Count: " << totCrossSectionEvCount <<"\n";
    float crossSectionAvgAlt = totCrossSectionWeight/totCrossSectionEvCount;
    std::cout << "(Tot Weight)/Tot XS Count: " << crossSectionAvgAlt <<"\n";

}
