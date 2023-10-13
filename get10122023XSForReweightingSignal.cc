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

//Getting XS for each reweighting value
void get10122023XSForReweightingSignal(UInt_t fileInd){
    // Open the file. Note that the name of your file outside this class
    // will probably NOT be experiment.root.
    std::cout << "start\n";
    clock_t startt = clock();
    //Analyzer will run over all files put into fileAr

    double ZZHAt2XS = 0.001132;

    std::vector<std::string> fileAr;

    std::string saveName;

    ////////////////////////////////GETTING DATASET////////////////////////////////
    ////////////////////////////////GETTING DATASET////////////////////////////////
    ////////////////////////////////GETTING DATASET////////////////////////////////
    ////////////////////////////////GETTING DATASET////////////////////////////////

    std::string strAdd;
    if (scratchDown) strAdd ="/afs/crc.nd.edu/user/d/dlutton/FROM_PANASAS";
    else strAdd ="/scratch365";

    if (SDC2V2MCZZHReweight){
        saveName = "SDC2V2MCZZHReweight";
        
        int arrSize = sizeof(SDC2V2MCZZHReweightAr)/sizeof(SDC2V2MCZZHReweightAr[0]);
        std::string tmpStrWithPath = SDC2V2MCZZHReweightAr[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V2MCZZHReweightAr[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        
        
        
    }
    else if (SDC2V2MCZZH17Reweight){
        saveName = "SDC2V2MCZZH17Reweight";
        
        int arrSize = sizeof(SDC2V2MCZZH17ReweightAr)/sizeof(SDC2V2MCZZH17ReweightAr[0]);
        std::string tmpStrWithPath = SDC2V2MCZZH17ReweightAr[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V2MCZZH17ReweightAr[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        
        
        
    }
    else if (SDC2V2MCZZH16Reweight){
        saveName = "SDC2V2MCZZH16Reweight";
        
        int arrSize = sizeof(SDC2V2MCZZH16ReweightAr)/sizeof(SDC2V2MCZZH16ReweightAr[0]);
        std::string tmpStrWithPath = SDC2V2MCZZH16ReweightAr[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V2MCZZH16ReweightAr[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        
        
        
    }
    else if (SDC2V2MCZZH16APVReweight){
        saveName = "SDC2V2MCZZH16APVReweight";
        
        int arrSize = sizeof(SDC2V2MCZZH16APVReweightAr)/sizeof(SDC2V2MCZZH16APVReweightAr[0]);
        std::string tmpStrWithPath = SDC2V2MCZZH16APVReweightAr[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V2MCZZH16APVReweightAr[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        
        
        
    }
    else if (SDC2V2MCWZHReweight){
        saveName = "SDC2V2MCWZHReweight";
        
        int arrSize = sizeof(SDC2V2MCWZHReweightAr)/sizeof(SDC2V2MCWZHReweightAr[0]);
        std::string tmpStrWithPath = SDC2V2MCWZHReweightAr[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V2MCWZHReweightAr[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        
        
        
    }
    else if (SDC2V2MCWZH17Reweight){
        saveName = "SDC2V2MCWZH17Reweight";
        
        int arrSize = sizeof(SDC2V2MCWZH17ReweightAr)/sizeof(SDC2V2MCWZH17ReweightAr[0]);
        std::string tmpStrWithPath = SDC2V2MCWZH17ReweightAr[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V2MCWZH17ReweightAr[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        
        
        
    }
    else if (SDC2V2MCWZH16Reweight){
        saveName = "SDC2V2MCWZH16Reweight";
        
        int arrSize = sizeof(SDC2V2MCWZH16ReweightAr)/sizeof(SDC2V2MCWZH16ReweightAr[0]);
        std::string tmpStrWithPath = SDC2V2MCWZH16ReweightAr[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V2MCWZH16ReweightAr[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        
        
        
    }
    else if (SDC2V2MCWZH16APVReweight){
        saveName = "SDC2V2MCWZH16APVReweight";
        
        int arrSize = sizeof(SDC2V2MCWZH16APVReweightAr)/sizeof(SDC2V2MCWZH16APVReweightAr[0]);
        std::string tmpStrWithPath = SDC2V2MCWZH16APVReweightAr[fileInd];
        /*
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = SDC2V2MCWZH16APVReweightAr[i];
            fileAr.push_back(tmpStrWithPath);
        }
        */
        fileAr.push_back(tmpStrWithPath);
        
        
        
    }
    else if (testRun){
        saveName = "testRun";
        //fileAr.push_back("./unweighted_eventspphzzjjQCD0SMHLOOP0NPE1NPcHWE1QEDE5ResMasAllVer100Ev10080Seed_0p999cHW100GeVIMJetCut_200.root");
        fileAr.push_back("./merged18.root");
        
        
        
        
    }
    else if (LaraTest){
        saveName = "LaraTest";
        fileAr.push_back("/scratch365/dlutton/NanoAODFiles/pp_hwpwmjj_EFT_VBF_chw_09999000_250k.root");
    }
    else{
        std::cout << "ERROR. NO INPUT DATASET NAME GIVEN\n";
    }

    std::cout << "Doing " << saveName << "\n";
    ////////////////////////////////DEFINING TREES////////////////////////////////
    ////////////////////////////////DEFINING TREES////////////////////////////////
    ////////////////////////////////DEFINING TREES////////////////////////////////
    ////////////////////////////////DEFINING TREES////////////////////////////////

    std::vector<std::string> C2VNameAr {"-2.0","-1.75","-1.5","-1.25","-1.0","-0.75","-0.5","-0.25","0.0","0.1","0.2","0.3","0.4","0.5","0.6","0.7","0.8","0.9","1.0","1.1","1.2","1.3","1.4","1.5","1.6","1.7","1.8","1.9","2.25","2.5","2.75","3.0","3.25","3.5","3.75","4.0"};
    std::vector<Double_t> totWeightAr(37,0.0);
    
    
    
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

        //eventWeights
        TTreeReaderValue<UInt_t> nLHEReweightingWeight(myEventsReader, "nLHEReweightingWeight");
        TTreeReaderArray<Float_t> LHEReweightingWeight(myEventsReader, "LHEReweightingWeight");

        //genWeights
        TTreeReaderValue<Float_t> genWeight(myEventsReader, "genWeight");




        
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

            totWeightAr[0] += *genWeight;
            for (unsigned int C2VCtr = 1; C2VCtr < totWeightAr.size(); C2VCtr++){
                totWeightAr[C2VCtr] += *genWeight*(LHEReweightingWeight[C2VCtr-1]);
            }
            


        }
    }
    if (debug) std::cout << "Filling complete \n";

    clock_t endt = clock();
    double time_spent = (double)(endt - startt) / CLOCKS_PER_SEC;


    std::cout << "Finished file loop. " << "time: " << time_spent << "\n";

    std::cout << "evRunOver: " << evRunOver << " -------------------\n";

    std::vector<Double_t> XSAr(37,0.0);
    XSAr[0] = ZZHAt2XS;
    for (unsigned int C2VCtr = 1; C2VCtr < totWeightAr.size(); C2VCtr++){
        XSAr[C2VCtr] = ZZHAt2XS*(totWeightAr[C2VCtr]/totWeightAr[0]);
    }


    for (unsigned int loopItr = 0; loopItr < C2VNameAr.size(); loopItr++){
        if (loopItr == C2VNameAr.size() - 1) {
            std::cout << "(" << C2VNameAr[loopItr] << "," << totWeightAr[loopItr + 1] << ")\n";
        }
        else std::cout << "(" << C2VNameAr[loopItr] << "," << totWeightAr[loopItr + 1] << "),";
        if (loopItr == 27) {
            std::cout << "(2.0," << totWeightAr[0] << "),";
        }
    }

    for (unsigned int loopItr = 0; loopItr < C2VNameAr.size(); loopItr++){
        if (loopItr == C2VNameAr.size() - 1) {
            std::cout << "(" << C2VNameAr[loopItr] << "," << XSAr[loopItr + 1] << ")\n";
        }
        else std::cout << "(" << C2VNameAr[loopItr] << "," << XSAr[loopItr + 1] << "),";
        if (loopItr == 27) {
            std::cout << "(2.0," << XSAr[0] << "),";
        }
    }



}
