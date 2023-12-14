#include<TApplication.h>
#include<TFile.h>
#include<TMath.h>
#include<TMinuit.h>
#include<TROOT.h>
#include<TSystem.h>
#include<TObject.h>

#include "Math/LorentzVector.h"



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
#include "../new062022FoMAnalysis.h"
#include "../new062022FoMAnalysis_Functions.h"
#include "../genFileList.h"
#include<time.h>

#include<algorithm>
#include<chrono>
#include<ctime>
#include<fstream>
#include<iostream>
#include<mutex>

#include<thread>
#include<string>


#include<sys/stat.h>
#include<errno.h>
#include "../RoccoR.cc"
#include "../NanoCORE/Nano.h"
#include "../NanoCORE/SSSelections.cc"
#include "../NanoCORE/MetSelections.cc"
#include "../NanoCORE/Tools/JetCorrector.cc"
#include "../NanoCORE/Tools/jetcorr/JetResolutionUncertainty.h"
#include "../NanoCORE/Tools/jetcorr/JetCorrectionUncertainty.h"




////////////////////////////////START OF MAIN FUNCTION////////////////////////////////
////////////////////////////////START OF MAIN FUNCTION////////////////////////////////
////////////////////////////////START OF MAIN FUNCTION////////////////////////////////
////////////////////////////////START OF MAIN FUNCTION////////////////////////////////

//Script for calculating the JEC,JER,Rochester corrections, and BTagging Efficiencies for the HLT output files
//Output should be the same but with additional branches for the corrections and efficiencies
//Apply JEC and JER before BTagging Efficencies
//Input should be the dataset string, then an integer for each correction/efficiency to be calculated
void minimalCalcTest(string datasetString, int JECCorInd, int AK8JECCorInd,  int RochInd){
    // Open the file. Note that the name of your file outside this class
    // will probably NOT be experiment.root.
    std::cout << "start Analysis\n";
    clock_t startt = clock();


    //Will run over all files put into fileAr



    std::vector<std::string> fileAr;


    std::string saveName;
    bool isBackground;

    if (datasetString == "testRun") testRun = true;
    if (datasetString == "BTagMuData") BTagMuData = true;
    if (datasetString == "CharmoniumData") CharmoniumData = true;
    if (datasetString == "DisplacedJetData") DisplacedJetData = true;
    if (datasetString == "DoubleMuonData") DoubleMuonData = true;
    if (datasetString == "DoubleMuonLowMassData") DoubleMuonLowMassData = true;
    if (datasetString == "EGammaData") EGammaData = true;
    if (datasetString == "JetHTData") JetHTData = true;
    if (datasetString == "METData") METData = true;
    if (datasetString == "MuOniaData") MuOniaData = true;
    if (datasetString == "MuonEGData") MuonEGData = true;
    if (datasetString == "SingleMuonData") SingleMuonData = true;
    if (datasetString == "TauData") TauData = true;

    if (datasetString == "BTagCSV17Data") BTagCSV17Data = true;
    if (datasetString == "BTagMu17Data") BTagMu17Data = true;
    if (datasetString == "Charmonium17Data") Charmonium17Data = true;
    if (datasetString == "DisplacedJet17Data") DisplacedJet17Data = true;
    if (datasetString == "DoubleEG17Data") DoubleEG17Data = true;
    if (datasetString == "DoubleMuon17Data") DoubleMuon17Data = true;
    if (datasetString == "DoubleMuonLowMass17Data") DoubleMuonLowMass17Data = true;
    if (datasetString == "FSQJet117Data") FSQJet117Data = true;
    if (datasetString == "FSQJet217Data") FSQJet217Data = true;
    if (datasetString == "HTMHT17Data") HTMHT17Data = true;
    if (datasetString == "HeavyFlavor17Data") HeavyFlavor17Data = true;
    if (datasetString == "HighEGJet17Data") HighEGJet17Data = true;
    if (datasetString == "HighPtLowerPhotons17Data") HighPtLowerPhotons17Data = true;
    if (datasetString == "HighPtPhoton30AndZ17Data") HighPtPhoton30AndZ17Data = true;
    if (datasetString == "JetHT17Data") JetHT17Data = true;
    if (datasetString == "LowEGJet17Data") LowEGJet17Data = true;
    if (datasetString == "MET17Data") MET17Data = true;
    if (datasetString == "MuOnia17Data") MuOnia17Data = true;
    if (datasetString == "MuonEG17Data") MuonEG17Data = true;
    if (datasetString == "SingleElectron17Data") SingleElectron17Data = true;
    if (datasetString == "SingleMuon17Data") SingleMuon17Data = true;
    if (datasetString == "SinglePhoton17Data") SinglePhoton17Data = true;
    if (datasetString == "Tau17Data") Tau17Data = true;

    if (datasetString == "BTagCSV16Data") BTagCSV16Data = true;
    if (datasetString == "BTagMu16Data") BTagMu16Data = true;
    if (datasetString == "Charmonium16Data") Charmonium16Data = true;
    if (datasetString == "DisplacedJet16Data") DisplacedJet16Data = true;
    if (datasetString == "DoubleEG16Data") DoubleEG16Data = true;
    if (datasetString == "DoubleMuon16Data") DoubleMuon16Data = true;
    if (datasetString == "DoubleMuonLowMass16Data") DoubleMuonLowMass16Data = true;
    if (datasetString == "HTMHT16Data") HTMHT16Data = true;
    if (datasetString == "JetHT16Data") JetHT16Data = true;
    if (datasetString == "MET16Data") MET16Data = true;
    if (datasetString == "MuOnia16Data") MuOnia16Data = true;
    if (datasetString == "MuonEG16Data") MuonEG16Data = true;
    if (datasetString == "SingleElectron16Data") SingleElectron16Data = true;
    if (datasetString == "SingleMuon16Data") SingleMuon16Data = true;
    if (datasetString == "SinglePhoton16Data") SinglePhoton16Data = true;
    if (datasetString == "Tau16Data") Tau16Data = true;

    if (datasetString == "LaraTest") LaraTest = true;

    ////////////////////////////////GETTING DATASET////////////////////////////////
    ////////////////////////////////GETTING DATASET////////////////////////////////
    ////////////////////////////////GETTING DATASET////////////////////////////////
    ////////////////////////////////GETTING DATASET////////////////////////////////

    std::string strAdd;
    if (scratchDown) strAdd ="/afs/crc.nd.edu/user/d/dlutton/Public/condorStuff/NanoAODToHistos/tmpHoldForNanoAODWithoutScratch/";
    else strAdd ="/scratch365/dlutton/HLTFilteredFiles/dataFiles/";
    if (localTest) strAdd = "";


    UInt_t datasetType = 0;

    UInt_t yearType = 0;

    if (BTagMuData){
        datasetType = 27;
        saveName = "BTagMuData";
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisBTagMuData.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (CharmoniumData){
        datasetType = 28;
        saveName = "CharmoniumData";
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisCharmoniumData.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (DisplacedJetData){
        datasetType = 29;
        saveName = "DisplacedJetData";
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisDisplacedJetData.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (DoubleMuonData){
        datasetType = 31;
        saveName = "DoubleMuonData";
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisDoubleMuonData.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (DoubleMuonLowMassData){
        datasetType = 32;
        saveName = "DoubleMuonLowMassData";
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisDoubleMuonLowMassData.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (EGammaData){
        datasetType = 33;
        saveName = "EGammaData";
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisEGammaData.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (JetHTData){
        datasetType = 41;
        saveName = "JetHTData";
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisJetHTData.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (METData){
        datasetType = 43;
        saveName = "METData";
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisMETData.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (MuOniaData){
        datasetType = 44;
        saveName = "MuOniaData";
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisMuOniaData.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (MuonEGData){
        datasetType = 45;
        saveName = "MuonEGData";
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisMuonEGData.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SingleMuonData){
        datasetType = 47;
        saveName = "SingleMuonData";
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisSingleMuonData.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (TauData){
        datasetType = 49;
        saveName = "TauData";
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisTauData.root";
        fileAr.push_back(tmpStrWithPath);
    }

    else if (BTagCSV17Data){
        datasetType = 26;
        yearType = 1;
        saveName = "BTagCSV17Data";
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisBTagCSV17Data.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (BTagMu17Data){
        datasetType = 27;
        yearType = 1;
        saveName = "BTagMu17Data";
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisBTagMu17Data.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (Charmonium17Data){
        datasetType = 28;
        yearType = 1;
        saveName = "Charmonium17Data";
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisCharmonium17Data.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (DisplacedJet17Data){
        datasetType = 29;
        yearType = 1;
        saveName = "DisplacedJet17Data";
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisDisplacedJet17Data.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (DoubleEG17Data){
        datasetType = 30;
        yearType = 1;
        saveName = "DoubleEG17Data";
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisDoubleEG17Data.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (DoubleMuon17Data){
        datasetType = 31;
        yearType = 1;
        saveName = "DoubleMuon17Data";
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisDoubleMuon17Data.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (DoubleMuonLowMass17Data){
        datasetType = 32;
        yearType = 1;
        saveName = "DoubleMuonLowMass17Data";
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisDoubleMuonLowMass17Data.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (FSQJet117Data){
        datasetType = 34;
        yearType = 1;
        saveName = "FSQJet117Data";
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisFSQJet117Data.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (FSQJet217Data){
        datasetType = 35;
        yearType = 1;
        saveName = "FSQJet217Data";
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisFSQJet217Data.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (HTMHT17Data){
        datasetType = 36;
        yearType = 1;
        saveName = "HTMHT17Data";
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisHTMHT17Data.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (HeavyFlavor17Data){
        datasetType = 37;
        yearType = 1;
        saveName = "HeavyFlavor17Data";
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisHeavyFlavor17Data.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (HighEGJet17Data){
        datasetType = 38;
        yearType = 1;
        saveName = "HighEGJet17Data";
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisHighEGJet17Data.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (HighPtLowerPhotons17Data){
        datasetType = 39;
        yearType = 1;
        saveName = "HighPtLowerPhotons17Data";
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisHighPtLowerPhotons17Data.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (HighPtPhoton30AndZ17Data){
        datasetType = 40;
        yearType = 1;
        saveName = "HighPtPhoton30AndZ17Data";
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisHighPtPhoton30AndZ17Data.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (JetHT17Data){
        datasetType = 41;
        yearType = 1;
        saveName = "JetHT17Data";
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisJetHT17Data.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (LowEGJet17Data){
        datasetType = 42;
        yearType = 1;
        saveName = "LowEGJet17Data";
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisLowEGJet17Data.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (MET17Data){
        datasetType = 43;
        yearType = 1;
        saveName = "MET17Data";
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisMET17Data.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (MuOnia17Data){
        datasetType = 44;
        yearType = 1;
        saveName = "MuOnia17Data";
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisMuOnia17Data.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (MuonEG17Data){
        datasetType = 45;
        yearType = 1;
        saveName = "MuonEG17Data";
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisMuonEG17Data.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SingleElectron17Data){
        datasetType = 46;
        yearType = 1;
        saveName = "SingleElectron17Data";
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisSingleElectron17Data.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SingleMuon17Data){
        datasetType = 47;
        yearType = 1;
        saveName = "SingleMuon17Data";
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisSingleMuon17Data.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SinglePhoton17Data){
        datasetType = 48;
        yearType = 1;
        saveName = "SinglePhoton17Data";
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisSinglePhoton17Data.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (Tau17Data){
        datasetType = 49;
        yearType = 1;
        saveName = "Tau17Data";
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisTau17Data.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (BTagCSV16Data){
        datasetType = 26;
        yearType = 2;
        saveName = "BTagCSV16Data";
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisBTagCSV16Data.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (BTagMu16Data){
        datasetType = 27;
        yearType = 2;
        saveName = "BTagMu16Data";
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisBTagMu16Data.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (Charmonium16Data){
        datasetType = 28;
        yearType = 2;
        saveName = "Charmonium16Data";
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisCharmonium16Data.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (DisplacedJet16Data){
        datasetType = 29;
        yearType = 2;
        saveName = "DisplacedJet16Data";
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisDisplacedJet16Data.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (DoubleEG16Data){
        datasetType = 30;
        yearType = 2;
        saveName = "DoubleEG16Data";
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisDoubleEG16Data.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (DoubleMuon16Data){
        datasetType = 31;
        yearType = 2;
        saveName = "DoubleMuon16Data";
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisDoubleMuon16Data.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (DoubleMuonLowMass16Data){
        datasetType = 32;
        yearType = 2;
        saveName = "DoubleMuonLowMass16Data";
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisDoubleMuonLowMass16Data.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (HTMHT16Data){
        datasetType = 36;
        yearType = 2;
        saveName = "HTMHT16Data";
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisHTMHT16Data.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (JetHT16Data){
        datasetType = 41;
        yearType = 2;
        saveName = "JetHT16Data";
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisJetHT16Data.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (MET16Data){
        datasetType = 43;
        yearType = 2;
        saveName = "MET16Data";
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisMET16Data.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (MuOnia16Data){
        datasetType = 44;
        yearType = 2;
        saveName = "MuOnia16Data";
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisMuOnia16Data.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (MuonEG16Data){
        datasetType = 45;
        yearType = 2;
        saveName = "MuonEG16Data";
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisMuonEG16Data.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SingleElectron16Data){
        datasetType = 46;
        yearType = 2;
        saveName = "SingleElectron16Data";
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisSingleElectron16Data.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SingleMuon16Data){
        datasetType = 47;
        yearType = 2;
        saveName = "SingleMuon16Data";
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisSingleMuon16Data.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SinglePhoton16Data){
        datasetType = 48;
        yearType = 2;
        saveName = "SinglePhoton16Data";
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisSinglePhoton16Data.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (Tau16Data){
        datasetType = 49;
        yearType = 2;
        saveName = "Tau16Data";
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisTau16Data.root";
        fileAr.push_back(tmpStrWithPath);
    }

    else if (testRun){
        saveName = "testRun";
        fileAr.push_back("./HLTFilteredForAnalysistestRun_0.root");
        
    }
    else if (LaraTest){
        saveName = "LaraTest";
        fileAr.push_back("/scratch365/dlutton/NanoAODFiles/pp_hwpwmjj_EFT_VBF_chw_09999000_250k.root");
    }
    else{
        std::cout << "ERROR. NO INPUT DATASET NAME GIVEN\n";
    }

    std::cout << "Doing " << saveName << "\n";
    //Setting up outfile with variables for BDT
    //convert int to str


    std::string outFileStr = "new10162023MinimalTest"+saveName+"_"+std::to_string(JECCorInd)+"_"+std::to_string(AK8JECCorInd)+"_"+std::to_string(RochInd)+".root";
    std::cout << "OutFile: " << outFileStr << "\n";
    TFile *outFile = new TFile(outFileStr.c_str(),"RECREATE");

    UInt_t datanEv = 0;
    UInt_t datanEvPass = 0;
    UInt_t evCount = 0;
    UInt_t evRunOver = 0;


    //Jets
    UInt_t nJetL;
    
    TTree *FilteredEventsTree = new TTree("FilteredEventsTree", "FilteredEventsTree");
  
    FilteredEventsTree->Branch("nJetL",&nJetL,"nJetL/i");


    std::cout << "Going into file loop.\n";

    for (UInt_t k=0; k<fileAr.size(); k++){
        if (endAfter && evCount > NToEnd) break;
        if (debug) std::cout<<"File:    "<<fileAr[k]<<"\n";
        //Open the file, get the Events tree
        TFile* tmpfile = TFile::Open(fileAr[k].c_str());
        //outFile->cd();
        TTreeReader myEventsReader("FilteredEventsTree", tmpfile);

        //jets

        TTreeReaderValue<UInt_t> nJet(myEventsReader, "nJetL");
        
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


            nJetL = *nJet;
    }
    if (debug) std::cout << "Filling complete \n";

    clock_t endt = clock();
    double time_spent = (double)(endt - startt) / CLOCKS_PER_SEC;


    std::cout << "Finished file loop. " << "time: " << time_spent << "\n";
    
    std::cout << "nEv total: " << datanEv << "\n";
    std::cout << "nEv post pre-selection: " << datanEvPass << "\n"; 
    

    std::cout << "==============================TOTAL COUNTERS==============================\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "evRunOver = " << evRunOver << "\n";
    std::cout << "------------------------\n";


    outFile->cd();
    FilteredEventsTree->Write("",TObject::kOverwrite);

    outFile->Close();
    

}