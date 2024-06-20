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
#include<time.h>

#include<algorithm>
#include<chrono>
#include<ctime>
#include<fstream>
#include<iostream>
#include<mutex>

#include<thread>
#include<string>
#include <vector>


#include<sys/stat.h>
#include<errno.h>
#include<TTree.h>


bool debug = false;
bool endEvAfter = false;
bool endAfter = false;
int NToStart = 0;
int NToEnd = 20;
int NToEndTot = 10000;

////////////////////////////////START OF MAIN FUNCTION////////////////////////////////
////////////////////////////////START OF MAIN FUNCTION////////////////////////////////
////////////////////////////////START OF MAIN FUNCTION////////////////////////////////
////////////////////////////////START OF MAIN FUNCTION////////////////////////////////


void getHEMRatio(){
    // Open the file. Note that the name of your file outside this class
    // will probably NOT be experiment.root.
    std::cout << "start Analysis\n";
    clock_t startt = clock();
    //Analyzer will run over all files put into fileAr

    //gInterpreter->GenerateDictionary("vector<vector<vector<Double_t> > >", "vector");
    //gInterpreter->GenerateDictionary("vector<vector<vector<Int_t> > >", "vector");


    std::string saveName;
    
    const uint nDataSets = 3;

    std::string datasetTypeStrAr[nDataSets] =  {
    "DoubleMuon",
    "EGamma",
    "SingleMuon"};

    std::string datasetStrAr[nDataSets];
    for (uint k = 0; k < nDataSets; k++){
        datasetStrAr[k] = "HLTTrimmedFilteredForAnalysis"+datasetTypeStrAr[k]+"Data.root";
    }

    ////////////////////////////////GETTING DATASET////////////////////////////////
    ////////////////////////////////GETTING DATASET////////////////////////////////
    ////////////////////////////////GETTING DATASET////////////////////////////////
    ////////////////////////////////GETTING DATASET////////////////////////////////


    std::string strAdd;
    std::vector<std::string> fileAr;
    strAdd ="/scratch365/dlutton/HLT042024DataForPreSel/";
    for (UInt_t i = 0; i < nDataSets; i++){
        fileAr.push_back(strAdd+datasetStrAr[i]);
    }

    //Setting up outfile

    std::string outFileStr;
    outFileStr = "HEM062024RatioData.root";
    
    std::cout << "Doing duplicate checker for outFile: " << outFileStr << "\n";
    TFile *outFile = new TFile(outFileStr.c_str(),"RECREATE");
    

    ////////////////////////////////DEFINING TREES////////////////////////////////
    ////////////////////////////////DEFINING TREES////////////////////////////////
    ////////////////////////////////DEFINING TREES////////////////////////////////
    ////////////////////////////////DEFINING TREES////////////////////////////////

    ////////////////////////////////DEFINING COUNTERS////////////////////////////////
    ////////////////////////////////NEUTRAL COUNTERS////////////////////////////////

    UInt_t allCtr = 0;
    UInt_t uniqueCtr = 0;

    //HEM Check Tree
    UInt_t runForHEM_U;
    ULong64_t eventForHEM_U;
    Bool_t isHEMRun_U;

    TTree *HEMCheckUniqueTree = new TTree("HEMCheckUniqueTree", "HEMCheckUniqueTree");

    HEMCheckUniqueTree->Branch("runForHEM_U",&runForHEM_U,"runForHEM_U/i");
    HEMCheckUniqueTree->Branch("eventForHEM_U",&eventForHEM_U,"eventForHEM_U/l");
    HEMCheckUniqueTree->Branch("isHEMRun_U",&isHEMRun_U,"isHEMRun_U/O");




    std::vector<int> runVec;
    std::vector<int> evVec;
    

    std::cout << "Going into file loop.\n";

    for (UInt_t k=0; k<fileAr.size(); k++){
        if (endAfter && allCtr > NToEndTot) break;
        if (debug) std::cout<<"File:    "<<fileAr[k]<<"\n";
        //Open the file, get the Events tree
        TFile* tmpfile = TFile::Open(fileAr[k].c_str());
        //outFile->cd();
        TTreeReader myEventsReader("HEMCheckTree", tmpfile);

        TTreeReaderValue<UInt_t> runForHEM(myEventsReader, "runForHEM");
        TTreeReaderValue<ULong64_t> eventForHEM(myEventsReader, "eventForHEM");
        TTreeReaderValue<Bool_t> isHEMRun(myEventsReader, "isHEMRun");


        if (k % 10 == 0){
            double tmpTime = (double)(clock()-startt)/CLOCKS_PER_SEC;
            std::cout << "Going into event loop for file" << k << " .\ttime:" << (double)(clock()-startt)/CLOCKS_PER_SEC << "\n";
        }
        std::cout << "File " << k << " Current nEv: " << allCtr << " Current unique: " << uniqueCtr << " time " << (double)(clock()-startt)/CLOCKS_PER_SEC << "\n";
        

        uint evCount = 0;


        //EvLoop
        while (myEventsReader.Next()) {
            
            if (endEvAfter){
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
            
            evCount += 1;
            allCtr += 1;

            bool isUnique = true;

            for (uint runEvInt = 0; runEvInt < runVec.size(); runEvInt++) {
                if (runVec[runEvInt] == *runForHEM && evVec[runEvInt] == *eventForHEM) {
                    isUnique = false;
                    break;
                }
            }

            

            if (isUnique){
                uniqueCtr += 1;
                runVec.push_back(*runForHEM);
                evVec.push_back(*eventForHEM);

            
                //Fill BDT SemiLep Tree

                runForHEM_U = *runForHEM;
                eventForHEM_U = *eventForHEM;
                isHEMRun_U = *isHEMRun;

                HEMCheckUniqueTree->Fill();
                


            }

        }
    }
    if (debug) std::cout << "Filling complete \n";

    clock_t endt = clock();
    double time_spent = (double)(endt - startt) / CLOCKS_PER_SEC;


    std::cout << "Finished file loop. time: " << time_spent << " nEv total: " << allCtr << " nEv unique: " << uniqueCtr << "\n";
    

    outFile->cd();
    HEMCheckUniqueTree->Write("",TObject::kOverwrite);

    outFile->Close();
}