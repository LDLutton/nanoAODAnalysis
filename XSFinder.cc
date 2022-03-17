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
#include "new022022KinematicsAnalysis_FileList.h"
#include "XSFinder.h"
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


void XSFinder(){
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
        
        
    }
    else if (SDC2V3MC){
        saveName = "SDC2V3MC";
        isBackground = false;
        int arrSize = sizeof(SDC2V3MCAr)/sizeof(SDC2V3MCAr[0]);
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V3MCAr[i];
            fileAr.push_back(tmpStrWithPath);
        }
        useLHETree = true;
        
        
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
        
        
    }
    else if (testRun){
        saveName = "testRun";
        fileAr.push_back("./unweighted_eventspphzzjjQCD0SMHLOOP0NPE1NPcHWE1QEDE5ResMasAllVer100Ev10080Seed_0p999cHW100GeVIMJetCut_200.root");
        useLHETree = true;
        
        
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

    ////////////////////////////////DEFINING TREES////////////////////////////////
    ////////////////////////////////DEFINING TREES////////////////////////////////
    ////////////////////////////////DEFINING TREES////////////////////////////////
    ////////////////////////////////DEFINING TREES////////////////////////////////

    float crossSectionAvg = 0.;
    UInt_t crossSectionCtr = 0;
    float totCrossSectionWeight = 0.;
    UInt_t totCrossSectionEvCount = 0;

    UInt_t evCount = 0;
    
    std::cout << "Going into file loop.\n";

    for (UInt_t k=0; k<fileAr.size(); k++){
        if (endAfter && evCount > NToEnd) break;
        if (debug) std::cout<<"File:    "<<fileAr[k]<<"\n";
        //Open the file, get the Events tree
        TFile* tmpfile = TFile::Open(fileAr[k].c_str());
        outFile->cd();

        TTreeReader myRunsReader("Runs", tmpfile);
        TTreeReaderValue<Long64_t> genEventCount(myRunsReader, "genEventCount");
        TTreeReaderValue<Double_t> genEventSumw(myRunsReader, "genEventSumw");

        //Getting the cross section
        //For background it's precalculated
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
        
        if (k % 10 == 0){
            double tmpTime = (double)(clock()-startt)/CLOCKS_PER_SEC;
            std::cout << "Going into event loop for file" << k << " .\ttime:" << (double)(clock()-startt)/CLOCKS_PER_SEC << "\n";
        }
        evCount += 1;

    }
    if (debug) std::cout << "Filling complete \n";

    clock_t endt = clock();
    double time_spent = (double)(endt - startt) / CLOCKS_PER_SEC;


    std::cout << "Finished file loop. " << "time: " << time_spent << "\n";

    std::cout << "Cross section average before division: " << crossSectionAvg << "\n";
    std::cout << "Cross section counter: " << crossSectionCtr << "\n";
    crossSectionAvg = crossSectionAvg / crossSectionCtr;
    std::cout << "Cross section average after division: " << crossSectionAvg << "\n";
    std::cout << "Tot Weight: " << totCrossSectionWeight <<"\n";
    std::cout << "Tot XS Count: " << totCrossSectionEvCount <<"\n";
    std::cout << "Tot Weight/Tot XS Count: " << totCrossSectionWeight/totCrossSectionEvCount <<"\n";
    

    outFile->Close();
}