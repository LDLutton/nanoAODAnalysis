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
#include "new062022FoMAnalysis.h"
#include "new062022FoMAnalysis_Functions.h"
#include "genFileList.h"
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



////////////////////////////////START OF MAIN FUNCTION////////////////////////////////
////////////////////////////////START OF MAIN FUNCTION////////////////////////////////
////////////////////////////////START OF MAIN FUNCTION////////////////////////////////
////////////////////////////////START OF MAIN FUNCTION////////////////////////////////

//Script for running over data using MD PN for selection and having the H AK8 selected before the Z AK8 jet
void new122023BDTAnalysisData(string datasetString, int JECCorInd,  int RochInd, bool UncUpDownBool){
    // Open the file. Note that the name of your file outside this class
    // will probably NOT be experiment.root.
    std::cout << "start Analysis\n";
    clock_t startt = clock();
    //Analyzer will run over all files put into fileAr

    std::vector<std::string> fileAr;
    bool handBrake = false;
    int handBrakeInd = 2000;


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



    UInt_t datasetType = 0;

    UInt_t yearType = 0;

    if (BTagMuData){
        datasetType = 27;
        saveName = "BTagMuData";
        
        std::string tmpStrWithPath = "./HLTTrimmedFilteredForAnalysisBTagMuData_"+std::to_string(JECCorInd)+"_"+std::to_string(RochInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (CharmoniumData){
        datasetType = 28;
        saveName = "CharmoniumData";
        
        std::string tmpStrWithPath = "./HLTTrimmedFilteredForAnalysisCharmoniumData_"+std::to_string(JECCorInd)+"_"+std::to_string(RochInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (DisplacedJetData){
        datasetType = 29;
        saveName = "DisplacedJetData";
        
        std::string tmpStrWithPath = "./HLTTrimmedFilteredForAnalysisDisplacedJetData_"+std::to_string(JECCorInd)+"_"+std::to_string(RochInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (DoubleMuonData){
        datasetType = 31;
        saveName = "DoubleMuonData";
        
        std::string tmpStrWithPath = "./HLTTrimmedFilteredForAnalysisDoubleMuonData_"+std::to_string(JECCorInd)+"_"+std::to_string(RochInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (DoubleMuonLowMassData){
        datasetType = 32;
        saveName = "DoubleMuonLowMassData";
        
        std::string tmpStrWithPath = "./HLTTrimmedFilteredForAnalysisDoubleMuonLowMassData_"+std::to_string(JECCorInd)+"_"+std::to_string(RochInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (EGammaData){
        datasetType = 33;
        saveName = "EGammaData";
        
        std::string tmpStrWithPath = "./HLTTrimmedFilteredForAnalysisEGammaData_"+std::to_string(JECCorInd)+"_"+std::to_string(RochInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (JetHTData){
        datasetType = 41;
        saveName = "JetHTData";
        
        std::string tmpStrWithPath = "./HLTTrimmedFilteredForAnalysisJetHTData_"+std::to_string(JECCorInd)+"_"+std::to_string(RochInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (METData){
        datasetType = 43;
        saveName = "METData";
        
        std::string tmpStrWithPath = "./HLTTrimmedFilteredForAnalysisMETData_"+std::to_string(JECCorInd)+"_"+std::to_string(RochInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (MuOniaData){
        datasetType = 44;
        saveName = "MuOniaData";
        
        std::string tmpStrWithPath = "./HLTTrimmedFilteredForAnalysisMuOniaData_"+std::to_string(JECCorInd)+"_"+std::to_string(RochInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (MuonEGData){
        datasetType = 45;
        saveName = "MuonEGData";
        
        std::string tmpStrWithPath = "./HLTTrimmedFilteredForAnalysisMuonEGData_"+std::to_string(JECCorInd)+"_"+std::to_string(RochInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SingleMuonData){
        datasetType = 47;
        saveName = "SingleMuonData";
        
        std::string tmpStrWithPath = "./HLTTrimmedFilteredForAnalysisSingleMuonData_"+std::to_string(JECCorInd)+"_"+std::to_string(RochInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (TauData){
        datasetType = 49;
        saveName = "TauData";
        
        std::string tmpStrWithPath = "./HLTTrimmedFilteredForAnalysisTauData_"+std::to_string(JECCorInd)+"_"+std::to_string(RochInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }

    else if (BTagCSV17Data){
        datasetType = 26;
        yearType = 1;
        saveName = "BTagCSV17Data";
        
        std::string tmpStrWithPath = "./HLTTrimmedFilteredForAnalysisBTagCSV17Data_"+std::to_string(JECCorInd)+"_"+std::to_string(RochInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (BTagMu17Data){
        datasetType = 27;
        yearType = 1;
        saveName = "BTagMu17Data";
        
        std::string tmpStrWithPath = "./HLTTrimmedFilteredForAnalysisBTagMu17Data_"+std::to_string(JECCorInd)+"_"+std::to_string(RochInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (Charmonium17Data){
        datasetType = 28;
        yearType = 1;
        saveName = "Charmonium17Data";
        
        std::string tmpStrWithPath = "./HLTTrimmedFilteredForAnalysisCharmonium17Data_"+std::to_string(JECCorInd)+"_"+std::to_string(RochInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (DisplacedJet17Data){
        datasetType = 29;
        yearType = 1;
        saveName = "DisplacedJet17Data";
        
        std::string tmpStrWithPath = "./HLTTrimmedFilteredForAnalysisDisplacedJet17Data_"+std::to_string(JECCorInd)+"_"+std::to_string(RochInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (DoubleEG17Data){
        datasetType = 30;
        yearType = 1;
        saveName = "DoubleEG17Data";
        
        std::string tmpStrWithPath = "./HLTTrimmedFilteredForAnalysisDoubleEG17Data_"+std::to_string(JECCorInd)+"_"+std::to_string(RochInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (DoubleMuon17Data){
        datasetType = 31;
        yearType = 1;
        saveName = "DoubleMuon17Data";
        
        std::string tmpStrWithPath = "./HLTTrimmedFilteredForAnalysisDoubleMuon17Data_"+std::to_string(JECCorInd)+"_"+std::to_string(RochInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (DoubleMuonLowMass17Data){
        datasetType = 32;
        yearType = 1;
        saveName = "DoubleMuonLowMass17Data";
        
        std::string tmpStrWithPath = "./HLTTrimmedFilteredForAnalysisDoubleMuonLowMass17Data_"+std::to_string(JECCorInd)+"_"+std::to_string(RochInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (FSQJet117Data){
        datasetType = 34;
        yearType = 1;
        saveName = "FSQJet117Data";
        
        std::string tmpStrWithPath = "./HLTTrimmedFilteredForAnalysisFSQJet117Data_"+std::to_string(JECCorInd)+"_"+std::to_string(RochInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (FSQJet217Data){
        datasetType = 35;
        yearType = 1;
        saveName = "FSQJet217Data";
        
        std::string tmpStrWithPath = "./HLTTrimmedFilteredForAnalysisFSQJet217Data_"+std::to_string(JECCorInd)+"_"+std::to_string(RochInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (HTMHT17Data){
        datasetType = 36;
        yearType = 1;
        saveName = "HTMHT17Data";
        
        std::string tmpStrWithPath = "./HLTTrimmedFilteredForAnalysisHTMHT17Data_"+std::to_string(JECCorInd)+"_"+std::to_string(RochInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (HeavyFlavor17Data){
        datasetType = 37;
        yearType = 1;
        saveName = "HeavyFlavor17Data";
        
        std::string tmpStrWithPath = "./HLTTrimmedFilteredForAnalysisHeavyFlavor17Data_"+std::to_string(JECCorInd)+"_"+std::to_string(RochInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (HighEGJet17Data){
        datasetType = 38;
        yearType = 1;
        saveName = "HighEGJet17Data";
        
        std::string tmpStrWithPath = "./HLTTrimmedFilteredForAnalysisHighEGJet17Data_"+std::to_string(JECCorInd)+"_"+std::to_string(RochInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (HighPtLowerPhotons17Data){
        datasetType = 39;
        yearType = 1;
        saveName = "HighPtLowerPhotons17Data";
        
        std::string tmpStrWithPath = "./HLTTrimmedFilteredForAnalysisHighPtLowerPhotons17Data_"+std::to_string(JECCorInd)+"_"+std::to_string(RochInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (HighPtPhoton30AndZ17Data){
        datasetType = 40;
        yearType = 1;
        saveName = "HighPtPhoton30AndZ17Data";
        
        std::string tmpStrWithPath = "./HLTTrimmedFilteredForAnalysisHighPtPhoton30AndZ17Data_"+std::to_string(JECCorInd)+"_"+std::to_string(RochInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (JetHT17Data){
        datasetType = 41;
        yearType = 1;
        saveName = "JetHT17Data";
        
        std::string tmpStrWithPath = "./HLTTrimmedFilteredForAnalysisJetHT17Data_"+std::to_string(JECCorInd)+"_"+std::to_string(RochInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (LowEGJet17Data){
        datasetType = 42;
        yearType = 1;
        saveName = "LowEGJet17Data";
        
        std::string tmpStrWithPath = "./HLTTrimmedFilteredForAnalysisLowEGJet17Data_"+std::to_string(JECCorInd)+"_"+std::to_string(RochInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (MET17Data){
        datasetType = 43;
        yearType = 1;
        saveName = "MET17Data";
        
        std::string tmpStrWithPath = "./HLTTrimmedFilteredForAnalysisMET17Data_"+std::to_string(JECCorInd)+"_"+std::to_string(RochInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (MuOnia17Data){
        datasetType = 44;
        yearType = 1;
        saveName = "MuOnia17Data";
        
        std::string tmpStrWithPath = "./HLTTrimmedFilteredForAnalysisMuOnia17Data_"+std::to_string(JECCorInd)+"_"+std::to_string(RochInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (MuonEG17Data){
        datasetType = 45;
        yearType = 1;
        saveName = "MuonEG17Data";
        
        std::string tmpStrWithPath = "./HLTTrimmedFilteredForAnalysisMuonEG17Data_"+std::to_string(JECCorInd)+"_"+std::to_string(RochInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SingleElectron17Data){
        datasetType = 46;
        yearType = 1;
        saveName = "SingleElectron17Data";
        
        std::string tmpStrWithPath = "./HLTTrimmedFilteredForAnalysisSingleElectron17Data_"+std::to_string(JECCorInd)+"_"+std::to_string(RochInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SingleMuon17Data){
        datasetType = 47;
        yearType = 1;
        saveName = "SingleMuon17Data";
        
        std::string tmpStrWithPath = "./HLTTrimmedFilteredForAnalysisSingleMuon17Data_"+std::to_string(JECCorInd)+"_"+std::to_string(RochInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SinglePhoton17Data){
        datasetType = 48;
        yearType = 1;
        saveName = "SinglePhoton17Data";
        
        std::string tmpStrWithPath = "./HLTTrimmedFilteredForAnalysisSinglePhoton17Data_"+std::to_string(JECCorInd)+"_"+std::to_string(RochInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (Tau17Data){
        datasetType = 49;
        yearType = 1;
        saveName = "Tau17Data";
        
        std::string tmpStrWithPath = "./HLTTrimmedFilteredForAnalysisTau17Data_"+std::to_string(JECCorInd)+"_"+std::to_string(RochInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (BTagCSV16Data){
        datasetType = 26;
        yearType = 2;
        saveName = "BTagCSV16Data";
        
        std::string tmpStrWithPath = "./HLTTrimmedFilteredForAnalysisBTagCSV16Data_"+std::to_string(JECCorInd)+"_"+std::to_string(RochInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (BTagMu16Data){
        datasetType = 27;
        yearType = 2;
        saveName = "BTagMu16Data";
        
        std::string tmpStrWithPath = "./HLTTrimmedFilteredForAnalysisBTagMu16Data_"+std::to_string(JECCorInd)+"_"+std::to_string(RochInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (Charmonium16Data){
        datasetType = 28;
        yearType = 2;
        saveName = "Charmonium16Data";
        
        std::string tmpStrWithPath = "./HLTTrimmedFilteredForAnalysisCharmonium16Data_"+std::to_string(JECCorInd)+"_"+std::to_string(RochInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (DisplacedJet16Data){
        datasetType = 29;
        yearType = 2;
        saveName = "DisplacedJet16Data";
        
        std::string tmpStrWithPath = "./HLTTrimmedFilteredForAnalysisDisplacedJet16Data_"+std::to_string(JECCorInd)+"_"+std::to_string(RochInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (DoubleEG16Data){
        datasetType = 30;
        yearType = 2;
        saveName = "DoubleEG16Data";
        
        std::string tmpStrWithPath = "./HLTTrimmedFilteredForAnalysisDoubleEG16Data_"+std::to_string(JECCorInd)+"_"+std::to_string(RochInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (DoubleMuon16Data){
        datasetType = 31;
        yearType = 2;
        saveName = "DoubleMuon16Data";
        
        std::string tmpStrWithPath = "./HLTTrimmedFilteredForAnalysisDoubleMuon16Data_"+std::to_string(JECCorInd)+"_"+std::to_string(RochInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (DoubleMuonLowMass16Data){
        datasetType = 32;
        yearType = 2;
        saveName = "DoubleMuonLowMass16Data";
        
        std::string tmpStrWithPath = "./HLTTrimmedFilteredForAnalysisDoubleMuonLowMass16Data_"+std::to_string(JECCorInd)+"_"+std::to_string(RochInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (HTMHT16Data){
        datasetType = 36;
        yearType = 2;
        saveName = "HTMHT16Data";
        
        std::string tmpStrWithPath = "./HLTTrimmedFilteredForAnalysisHTMHT16Data_"+std::to_string(JECCorInd)+"_"+std::to_string(RochInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (JetHT16Data){
        datasetType = 41;
        yearType = 2;
        saveName = "JetHT16Data";
        
        std::string tmpStrWithPath = "./HLTTrimmedFilteredForAnalysisJetHT16Data_"+std::to_string(JECCorInd)+"_"+std::to_string(RochInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (MET16Data){
        datasetType = 43;
        yearType = 2;
        saveName = "MET16Data";
        
        std::string tmpStrWithPath = "./HLTTrimmedFilteredForAnalysisMET16Data_"+std::to_string(JECCorInd)+"_"+std::to_string(RochInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (MuOnia16Data){
        datasetType = 44;
        yearType = 2;
        saveName = "MuOnia16Data";
        
        std::string tmpStrWithPath = "./HLTTrimmedFilteredForAnalysisMuOnia16Data_"+std::to_string(JECCorInd)+"_"+std::to_string(RochInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (MuonEG16Data){
        datasetType = 45;
        yearType = 2;
        saveName = "MuonEG16Data";
        
        std::string tmpStrWithPath = "./HLTTrimmedFilteredForAnalysisMuonEG16Data_"+std::to_string(JECCorInd)+"_"+std::to_string(RochInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SingleElectron16Data){
        datasetType = 46;
        yearType = 2;
        saveName = "SingleElectron16Data";
        
        std::string tmpStrWithPath = "./HLTTrimmedFilteredForAnalysisSingleElectron16Data_"+std::to_string(JECCorInd)+"_"+std::to_string(RochInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SingleMuon16Data){
        datasetType = 47;
        yearType = 2;
        saveName = "SingleMuon16Data";
        
        std::string tmpStrWithPath = "./HLTTrimmedFilteredForAnalysisSingleMuon16Data_"+std::to_string(JECCorInd)+"_"+std::to_string(RochInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SinglePhoton16Data){
        datasetType = 48;
        yearType = 2;
        saveName = "SinglePhoton16Data";
        
        std::string tmpStrWithPath = "./HLTTrimmedFilteredForAnalysisSinglePhoton16Data_"+std::to_string(JECCorInd)+"_"+std::to_string(RochInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (Tau16Data){
        datasetType = 49;
        yearType = 2;
        saveName = "Tau16Data";
        
        std::string tmpStrWithPath = "./HLTTrimmedFilteredForAnalysisTau16Data_"+std::to_string(JECCorInd)+"_"+std::to_string(RochInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }

    else if (testRun){
        saveName = "testRun";
        fileAr.push_back("./HLTFilteredForAnalysistestRun_0_"+std::to_string(JECCorInd)+"_"+std::to_string(RochInd)+".root");
        
    }
    else{
        std::cout << "ERROR. NO INPUT DATASET NAME GIVEN\n";
    }

    std::cout << "Doing " << saveName << "\n";
    //Setting up outfile with variables for BDT
    std::string outUpDownStr = "";
    if (JECCorInd >0){
        if (UncUpDownBool) {
            outUpDownStr = "_UncUp";
        }
        else {
            outUpDownStr = "_UncDown";
        }
    }
    
    std::string outFileStr = "new122023BDTAnalysis"+saveName+"_"+std::to_string(JECCorInd)+"_"+std::to_string(RochInd)+outUpDownStr+".root";
    std::cout << "OutFile: " << outFileStr << "\n";
    TFile *outFile = new TFile(outFileStr.c_str(),"RECREATE");

    ////////////////////////////////DEFINING TREES////////////////////////////////
    ////////////////////////////////DEFINING TREES////////////////////////////////
    ////////////////////////////////DEFINING TREES////////////////////////////////
    ////////////////////////////////DEFINING TREES////////////////////////////////

    ////////////////////////////////DEFINING COUNTERS////////////////////////////////
    ////////////////////////////////NEUTRAL COUNTERS////////////////////////////////

    UInt_t startingCtr = 0;

    UInt_t passHiggsFJPreSTCtr = 0;
    UInt_t passHiggsFJPreSTLepCtr = 0;
    UInt_t passHiggsFJPreSTSemiLepCtr = 0;
    UInt_t passHiggsFJPreSTHadCtr = 0;

    UInt_t passHiggsFJInSemiLepChannelCtr = 0;

    UInt_t passHiggsFJCtr = 0;
    UInt_t passHiggsFJLepCtr = 0;
    UInt_t passHiggsFJSemiLepCtr = 0;
    UInt_t passHiggsFJHadCtr = 0;
    UInt_t passChannelCtr = 0;
    UInt_t passLepOrSemiLepChannelCtr = 0;
    UInt_t passLepChannelCtr = 0;
    UInt_t tryingSemiLepChannelCtr = 0;
    UInt_t passFJInSemiLepChannelCtr = 0;
    UInt_t passEnoughLepsInSemiLepChannelCtr = 0;
    UInt_t passEnoughFJsInSemiLepChannelCtr = 0;
    UInt_t passLepCutInSemiLepChannelCtr = 0;
    UInt_t passSemiLepChannelCtr = 0;
    UInt_t passHadChannelCtr = 0;
    UInt_t passVBFJetBVetoCtr = 0;
    UInt_t passVBFJetBVetoLepCtr = 0;
    UInt_t passVBFJetBVetoSemiLepCtr = 0;
    UInt_t passVBFJetBVetoHadCtr = 0;
    UInt_t passVBFJetsCtr = 0;
    UInt_t passAsLepCtr = 0;
    UInt_t passAsSemiLepCtr = 0;
    UInt_t passAsHadCtr = 0;

    UInt_t passSemiLepLepCutCtr = 0;




    ////////////////////////////////OTHER COUNTERS////////////////////////////////

    UInt_t passVBFJets = 0;
    UInt_t passFatJets = 0;
    UInt_t passFJMatch = 0;
    UInt_t passLepCut = 0;
    UInt_t passSemiLepCut = 0;

    UInt_t passHadCut = 0;

    UInt_t tryingLepCtr = 0;
    UInt_t tryingSemiLepCtr = 0;
    UInt_t tryingHadCtr = 0;

    //float dataXS;
    /*
    UInt_t datanEv;
    UInt_t datanEvPass;
    */
    UInt_t datanEv = 0;
    UInt_t datanEvPass = 0;
    UInt_t evCount = 0;
    UInt_t evRunOver = 0;



    if (BDTCuts){
        std::cout << "Using BDT cuts\n";
        dRCut = dRBDTCut;

        jetPTCut = jetPTBDTCut;

        jetEtaDifCut = jetEtaDifBDTCut;

        jetInvMassCut = jetInvMassBDTCut;

        bTagCut = bTagBDTCut;

        //Higgs FJ cuts

        hFatJetPTCut = hFatJetPTBDTCut;

        hFatJetDeepTagCut = hFatJetDeepTagBDTCut;

        hFatJetParticleNetCut = hFatJetParticleNetBDTCut;



        //Lep cuts

        ePtCut = ePtBDTCut;

        eEtaCut = eEtaBDTCut;

        mPtCut = mPtBDTCut;

        mEtaCut = mEtaBDTCut;

        invMassCutLow=invMassBDTCutLow;

        invMassCutHigh=invMassBDTCutHigh;

        ptLeadCut=ptLeadBDTCut;

        ptTrailingCut=ptTrailingBDTCut;

        fourLepInvMassCut = fourLepInvMassBDTCut;

        optLepInvMassCut = optLepInvMassBDTCut;

        lepIsoCut = lepIsoBDTCut;

        SIPCut = SIPBDTCut;

        //Semi-Lep cuts
        //fatJetPTCut = 200.;

        fatJetZTagCut = fatJetZTagBDTCut;
        fatJetZParticleNetCut = fatJetZParticleNetBDTCut;

        ZPairPlusHInvMassCut = ZPairPlusHInvMassBDTCut;
        ZPairPlusHPtCut = ZPairPlusHPtBDTCut;
        lDxyCut = lDxyBDTCut;
        lDzCut = lDzBDTCut;
        lMiniPFRelIsoCut = lMiniPFRelIsoBDTCut;
        eSieieBarrelCut = eSieieBarrelBDTCut;
        eSieieEndcapCut = eSieieEndcapBDTCut;

        eHoeCut = eHoeBDTCut;
        eInvMinusPInvCut = eInvMinusPInvBDTCut;
        ePromptMVACut = ePromptMVABDTCut;
        lepJetDeepTagLooseCut = lepJetDeepTagLooseBDTCut;
        lepJetDeepTagMediumCut = lepJetDeepTagMediumBDTCut;
        mPromptMVACut = mPromptMVABDTCut;
    }

    //PASSING EV TREE FOR BDT IN LEP CHANNEL

    UInt_t run_L_L;
    UInt_t event_L_L;
    UInt_t datasetType_L_L;
    UInt_t yearType_L_L;

    UInt_t eventNAK4Jets_L_L;
    UInt_t eventNAK8Jets_L_L;
    UInt_t eventNMuons_L_L;
    UInt_t eventNElectrons_L_L;

    std::vector<Float_t> Jet_eta_L_L;
    std::vector<Float_t> Jet_pt_L_L;
    std::vector<Float_t> Jet_phi_L_L;
    std::vector<Float_t> Jet_mass_L_L;
    std::vector<Int_t> Jet_jetId_L_L;
    std::vector<Float_t> Jet_btagDeepFlavB_L_L;

    UInt_t eventNAK4JetsPassingCuts_L_L;

    UInt_t eventNLooseElectrons_L_L;
    UInt_t eventNTightElectrons_L_L;
    UInt_t eventNLooseMuons_L_L;
    UInt_t eventNTightMuons_L_L;

    Float_t selectedHiggsFJ_pt_L_L;
    Float_t selectedHiggsFJ_eta_L_L;
    Float_t selectedHiggsFJ_ParticleNet_HbbvsQCD_L_L;

    Float_t selectedHiggsFJ_ParticleNetMD_QCD_L_L;
    Float_t selectedHiggsFJ_ParticleNetMD_Xbb_L_L;
    Float_t selectedHiggsFJ_ParticleNetMD_Xcc_L_L;
    Float_t selectedHiggsFJ_ParticleNetMD_Xqq_L_L;

    Float_t selectedLeadVBFJet_pt_L_L;
    Float_t selectedTrailingVBFJet_pt_L_L;
    Float_t selectedLeadVBFJet_eta_L_L;
    Float_t selectedTrailingVBFJet_eta_L_L;
    Float_t selectedVBFJets_EtaSep_L_L;
    Float_t selectedVBFJets_InvMass_L_L;

    Float_t selectedZOneLeadLepton_pt_L_L;
    Float_t selectedZOneTrailingLepton_pt_L_L;
    Float_t selectedZOneLeadLepton_eta_L_L;
    Float_t selectedZOneTrailingLepton_eta_L_L;
    Float_t selectedZOneLeadLepton_phi_L_L;
    Float_t selectedZOneTrailingLepton_phi_L_L;
    Float_t selectedZOneLeadLepton_SIP3D_L_L;
    Float_t selectedZOneTrailingLepton_SIP3D_L_L;
    Float_t selectedLeptons_MaxRelIso_L_L;
    Float_t selectedZOneLeptons_InvMass_L_L;
    Bool_t selectedZOneLeptons_Type_L_L;

    Float_t selectedZTwoLeadLepton_pt_L_L;
    Float_t selectedZTwoTrailingLepton_pt_L_L;
    Float_t selectedZTwoLeadLepton_eta_L_L;
    Float_t selectedZTwoTrailingLepton_eta_L_L;
    Float_t selectedZTwoLeadLepton_phi_L_L;
    Float_t selectedZTwoTrailingLepton_phi_L_L;
    Float_t selectedZTwoLeadLepton_SIP3D_L_L;
    Float_t selectedZTwoTrailingLepton_SIP3D_L_L;
    Float_t selectedZTwoLeptons_InvMass_L_L;
    Bool_t selectedZTwoLeptons_Type_L_L;

    Float_t selectedLeptons_InvMass_L_L;

    Float_t selectedZPairPlusHiggsFJ_InvMass_L_L;
    Float_t selectedZPairPlusHiggsFJ_pt_L_L;

    Float_t selectedVBFJets_MaxBTag_L_L;

    Float_t selectedZPairPlusHiggsFJPlusVBFJets_PtVecSum_L_L;
    Float_t selectedZPairPlusHiggsFJPlusVBFJets_PtScalarSum_L_L;

    Float_t selectedZPairPlusHiggsFJPlusVBFJets_PtVecOverScalarSum_L_L;
    

    TTree *passingEvLepTree = new TTree("passingEvLepTree", "passingEvLepTree");

    passingEvLepTree->Branch("run_L_L",&run_L_L,"run_L_L/i");
    passingEvLepTree->Branch("event_L_L",&event_L_L,"event_L_L/i");
    passingEvLepTree->Branch("datasetType_L_L",&datasetType_L_L,"datasetType_L_L/i");
    passingEvLepTree->Branch("yearType_L_L",&yearType_L_L,"yearType_L_L/i");

    passingEvLepTree->Branch("eventNAK4Jets_L_L",&eventNAK4Jets_L_L,"eventNAK4Jets_L_L/i");
    passingEvLepTree->Branch("eventNAK8Jets_L_L",&eventNAK8Jets_L_L,"eventNAK8Jets_L_L/i");
    passingEvLepTree->Branch("eventNMuons_L_L",&eventNMuons_L_L,"eventNMuons_L_L/i");
    passingEvLepTree->Branch("eventNElectrons_L_L",&eventNElectrons_L_L,"eventNElectrons_L_L/i");

    //Jets    
    passingEvLepTree->Branch("Jet_eta_L_L",&Jet_eta_L_L);
    passingEvLepTree->Branch("Jet_pt_L_L",&Jet_pt_L_L);
    passingEvLepTree->Branch("Jet_phi_L_L",&Jet_phi_L_L);
    passingEvLepTree->Branch("Jet_mass_L_L",&Jet_mass_L_L);
    passingEvLepTree->Branch("Jet_jetId_L_L",&Jet_jetId_L_L);
    passingEvLepTree->Branch("Jet_btagDeepFlavB_L_L",&Jet_btagDeepFlavB_L_L);
    

    passingEvLepTree->Branch("eventNAK4JetsPassingCuts_L_L",&eventNAK4JetsPassingCuts_L_L,"eventNAK4JetsPassingCuts_L_L/i");

    passingEvLepTree->Branch("eventNLooseElectrons_L_L",&eventNLooseElectrons_L_L,"eventNLooseElectrons_L_L/i");
    passingEvLepTree->Branch("eventNTightElectrons_L_L",&eventNTightElectrons_L_L,"eventNTightElectrons_L_L/i");

    passingEvLepTree->Branch("eventNLooseMuons_L_L",&eventNLooseMuons_L_L,"eventNLooseMuons_L_L/i");
    passingEvLepTree->Branch("eventNTightMuons_L_L",&eventNTightMuons_L_L,"eventNTightMuons_L_L/i");


    passingEvLepTree->Branch("selectedHiggsFJ_pt_L_L",&selectedHiggsFJ_pt_L_L,"selectedHiggsFJ_pt_L_L/F");
    passingEvLepTree->Branch("selectedHiggsFJ_eta_L_L",&selectedHiggsFJ_eta_L_L,"selectedHiggsFJ_eta_L_L/F");
    passingEvLepTree->Branch("selectedHiggsFJ_ParticleNet_HbbvsQCD_L_L",&selectedHiggsFJ_ParticleNet_HbbvsQCD_L_L,"selectedHiggsFJ_ParticleNet_HbbvsQCD_L_L/F");

    passingEvLepTree->Branch("selectedHiggsFJ_ParticleNetMD_QCD_L_L", &selectedHiggsFJ_ParticleNetMD_QCD_L_L);
    passingEvLepTree->Branch("selectedHiggsFJ_ParticleNetMD_Xbb_L_L", &selectedHiggsFJ_ParticleNetMD_Xbb_L_L);
    passingEvLepTree->Branch("selectedHiggsFJ_ParticleNetMD_Xcc_L_L", &selectedHiggsFJ_ParticleNetMD_Xcc_L_L);
    passingEvLepTree->Branch("selectedHiggsFJ_ParticleNetMD_Xqq_L_L", &selectedHiggsFJ_ParticleNetMD_Xqq_L_L);

    passingEvLepTree->Branch("selectedLeadVBFJet_pt_L_L",&selectedLeadVBFJet_pt_L_L,"selectedLeadVBFJet_pt_L_L/F");
    passingEvLepTree->Branch("selectedTrailingVBFJet_pt_L_L",&selectedTrailingVBFJet_pt_L_L,"selectedTrailingVBFJet_pt_L_L/F");
    passingEvLepTree->Branch("selectedLeadVBFJet_eta_L_L",&selectedLeadVBFJet_eta_L_L,"selectedLeadVBFJet_eta_L_L/F");
    passingEvLepTree->Branch("selectedTrailingVBFJet_eta_L_L",&selectedTrailingVBFJet_eta_L_L,"selectedTrailingVBFJet_eta_L_L/F");
    passingEvLepTree->Branch("selectedVBFJets_EtaSep_L_L",&selectedVBFJets_EtaSep_L_L,"selectedVBFJets_EtaSep_L_L/F");
    passingEvLepTree->Branch("selectedVBFJets_InvMass_L_L",&selectedVBFJets_InvMass_L_L,"selectedVBFJets_InvMass_L_L/F");

    passingEvLepTree->Branch("selectedZOneLeadLepton_pt_L_L",&selectedZOneLeadLepton_pt_L_L,"selectedZOneLeadLepton_pt_L_L/F");
    passingEvLepTree->Branch("selectedZOneTrailingLepton_pt_L_L",&selectedZOneTrailingLepton_pt_L_L,"selectedZOneTrailingLepton_pt_L_L/F");
    passingEvLepTree->Branch("selectedZOneLeadLepton_eta_L_L",&selectedZOneLeadLepton_eta_L_L,"selectedZOneLeadLepton_eta_L_L/F");
    passingEvLepTree->Branch("selectedZOneTrailingLepton_eta_L_L",&selectedZOneTrailingLepton_eta_L_L,"selectedZOneTrailingLepton_eta_L_L/F");
    passingEvLepTree->Branch("selectedZOneLeadLepton_phi_L_L",&selectedZOneLeadLepton_phi_L_L,"selectedZOneLeadLepton_phi_L_L/F");
    passingEvLepTree->Branch("selectedZOneTrailingLepton_phi_L_L",&selectedZOneTrailingLepton_phi_L_L,"selectedZOneTrailingLepton_phi_L_L/F");
    passingEvLepTree->Branch("selectedZOneLeadLepton_SIP3D_L_L",&selectedZOneLeadLepton_SIP3D_L_L,"selectedZOneLeadLepton_SIP3D_L_L/F");
    passingEvLepTree->Branch("selectedZOneTrailingLepton_SIP3D_L_L",&selectedZOneTrailingLepton_SIP3D_L_L,"selectedZOneTrailingLepton_SIP3D_L_L/F");
    
    passingEvLepTree->Branch("selectedZOneLeptons_InvMass_L_L",&selectedZOneLeptons_InvMass_L_L,"selectedZOneLeptons_InvMass_L_L/F");
    passingEvLepTree->Branch("selectedZOneLeptons_Type_L_L",&selectedZOneLeptons_Type_L_L,"selectedZOneLeptons_Type_L_L/O");

    passingEvLepTree->Branch("selectedZTwoLeadLepton_pt_L_L",&selectedZTwoLeadLepton_pt_L_L,"selectedZTwoLeadLepton_pt_L_L/F");
    passingEvLepTree->Branch("selectedZTwoTrailingLepton_pt_L_L",&selectedZTwoTrailingLepton_pt_L_L,"selectedZTwoTrailingLepton_pt_L_L/F");
    passingEvLepTree->Branch("selectedZTwoLeadLepton_eta_L_L",&selectedZTwoLeadLepton_eta_L_L,"selectedZTwoLeadLepton_eta_L_L/F");
    passingEvLepTree->Branch("selectedZTwoTrailingLepton_eta_L_L",&selectedZTwoTrailingLepton_eta_L_L,"selectedZTwoTrailingLepton_eta_L_L/F");
    passingEvLepTree->Branch("selectedZTwoLeadLepton_phi_L_L",&selectedZTwoLeadLepton_phi_L_L,"selectedZTwoLeadLepton_phi_L_L/F");
    passingEvLepTree->Branch("selectedZTwoTrailingLepton_phi_L_L",&selectedZTwoTrailingLepton_phi_L_L,"selectedZTwoTrailingLepton_phi_L_L/F");
    passingEvLepTree->Branch("selectedZTwoLeadLepton_SIP3D_L_L",&selectedZTwoLeadLepton_SIP3D_L_L,"selectedZTwoLeadLepton_SIP3D_L_L/F");
    passingEvLepTree->Branch("selectedZTwoTrailingLepton_SIP3D_L_L",&selectedZTwoTrailingLepton_SIP3D_L_L,"selectedZTwoTrailingLepton_SIP3D_L_L/F");

    passingEvLepTree->Branch("selectedZTwoLeptons_InvMass_L_L",&selectedZTwoLeptons_InvMass_L_L,"selectedZTwoLeptons_InvMass_L_L/F");
    passingEvLepTree->Branch("selectedZTwoLeptons_Type_L_L",&selectedZTwoLeptons_Type_L_L,"selectedZTwoLeptons_Type_L_L/O");

    passingEvLepTree->Branch("selectedLeptons_InvMass_L_L",&selectedLeptons_InvMass_L_L,"selectedLeptons_InvMass_L_L/F");
    passingEvLepTree->Branch("selectedLeptons_MaxRelIso_L_L",&selectedLeptons_MaxRelIso_L_L,"selectedLeptons_MaxRelIso_L_L/F");

    passingEvLepTree->Branch("selectedZPairPlusHiggsFJ_InvMass_L_L",&selectedZPairPlusHiggsFJ_InvMass_L_L,"selectedZPairPlusHiggsFJ_InvMass_L_L/F");
    passingEvLepTree->Branch("selectedZPairPlusHiggsFJ_pt_L_L",&selectedZPairPlusHiggsFJ_pt_L_L,"selectedZPairPlusHiggsFJ_pt_L_L/F");

    passingEvLepTree->Branch("selectedVBFJets_MaxBTag_L_L",&selectedVBFJets_MaxBTag_L_L,"selectedVBFJets_MaxBTag_L_L/F");

    passingEvLepTree->Branch("selectedZPairPlusHiggsFJPlusVBFJets_PtVecSum_L_L",&selectedZPairPlusHiggsFJPlusVBFJets_PtVecSum_L_L,"selectedZPairPlusHiggsFJPlusVBFJets_PtVecSum_L_L/F");
    passingEvLepTree->Branch("selectedZPairPlusHiggsFJPlusVBFJets_PtScalarSum_L_L",&selectedZPairPlusHiggsFJPlusVBFJets_PtScalarSum_L_L,"selectedZPairPlusHiggsFJPlusVBFJets_PtScalarSum_L_L/F");
    passingEvLepTree->Branch("selectedZPairPlusHiggsFJPlusVBFJets_PtVecOverScalarSum_L_L",&selectedZPairPlusHiggsFJPlusVBFJets_PtVecOverScalarSum_L_L,"selectedZPairPlusHiggsFJPlusVBFJets_PtVecOverScalarSum_L_L/F");





    //PASSING EV TREE FOR BDT IN SEMILEP CHANNEL
    UInt_t run_SL_L;
    UInt_t event_SL_L;
    UInt_t datasetType_SL_L;
    UInt_t yearType_SL_L;

    UInt_t runAlphNum_SL_L;
    Bool_t APV_SL_L;
    Int_t JECCorInd_SL_L;
    Int_t RochInd_SL_L;

    UInt_t eventNAK4Jets_SL_L;
    UInt_t eventNAK8Jets_SL_L;
    UInt_t eventNMuons_SL_L;
    UInt_t eventNElectrons_SL_L;

    std::vector<Float_t> Jet_eta_SL_L;
    std::vector<Float_t> Jet_pt_SL_L;
    std::vector<Float_t> Jet_phi_SL_L;
    std::vector<Float_t> Jet_mass_SL_L;
    std::vector<Int_t> Jet_jetId_SL_L;
    std::vector<Float_t> Jet_btagDeepFlavB_SL_L;

    Float_t fixedGridRhoFastjetAll_SL_L;
    std::vector<Float_t> Jet_ptCorrectedDown_SL_L;
    std::vector<Float_t> Jet_ptCorrectedUp_SL_L;

    UInt_t eventNAK4JetsPassingCuts_SL_L;

    UInt_t eventNLooseElectrons_SL_L;
    UInt_t eventNTightElectrons_SL_L;
    UInt_t eventNLooseMuons_SL_L;
    UInt_t eventNTightMuons_SL_L;

    Float_t selectedHiggsFJ_pt_SL_L;
    Float_t selectedHiggsFJ_eta_SL_L;
    Float_t selectedHiggsFJ_ParticleNet_HbbvsQCD_SL_L;
    Float_t selectedZFJ_pt_SL_L;
    Float_t selectedZFJ_eta_SL_L;
    Float_t selectedZFJ_ParticleNet_ZvsQCD_SL_L;

    Float_t selectedZFJ_InvMass_SL_L;
    Float_t selectedHiggsFJ_InvMass_SL_L;

    Float_t selectedZFJ_InvMassSoftDrop_SL_L;
    Float_t selectedHiggsFJ_InvMassSoftDrop_SL_L;

    Float_t selectedZFJ_InvMassPNRegress_SL_L;
    Float_t selectedHiggsFJ_InvMassPNRegress_SL_L;

    Float_t selectedHiggsFJ_ParticleNetMD_QCD_SL_L;
    Float_t selectedHiggsFJ_ParticleNetMD_Xbb_SL_L;
    Float_t selectedHiggsFJ_ParticleNetMD_Xcc_SL_L;
    Float_t selectedHiggsFJ_ParticleNetMD_Xqq_SL_L;

    Float_t selectedZFJ_ParticleNetMD_QCD_SL_L;
    Float_t selectedZFJ_ParticleNetMD_Xbb_SL_L;
    Float_t selectedZFJ_ParticleNetMD_Xcc_SL_L;
    Float_t selectedZFJ_ParticleNetMD_Xqq_SL_L;

    Float_t selectedLeadVBFJet_pt_SL_L;
    Float_t selectedTrailingVBFJet_pt_SL_L;
    Float_t selectedLeadVBFJet_eta_SL_L;
    Float_t selectedTrailingVBFJet_eta_SL_L;
    Float_t selectedVBFJets_EtaSep_SL_L;
    Float_t selectedVBFJets_InvMass_SL_L;

    Float_t selectedLeadLepton_pt_SL_L;
    Float_t selectedTrailingLepton_pt_SL_L;
    Float_t selectedLeadLepton_eta_SL_L;
    Float_t selectedTrailingLepton_eta_SL_L;
    Float_t selectedLeadLepton_phi_SL_L;
    Float_t selectedTrailingLepton_phi_SL_L;
    Float_t selectedLeadLepton_SIP3D_SL_L;
    Float_t selectedTrailingLepton_SIP3D_SL_L;
    Float_t selectedLeptons_RelIso_SL_L;
    Float_t selectedLeptons_InvMass_SL_L;
    Bool_t selectedLeptons_IsMuon_SL_L;

    Float_t selectedZPairPlusHiggsFJ_InvMass_SL_L;
    Float_t selectedZPairPlusHiggsFJ_pt_SL_L;

    Float_t selectedVBFJets_MaxBTag_SL_L;

    Float_t selectedZPairPlusHiggsFJPlusVBFJets_PtVecSum_SL_L;
    Float_t selectedZPairPlusHiggsFJPlusVBFJets_PtScalarSum_SL_L;

    Float_t selectedZPairPlusHiggsFJPlusVBFJets_PtVecOverScalarSum_SL_L;
    

    TTree *passingEvSemiLepTree = new TTree("passingEvSemiLepTree", "passingEvSemiLepTree");

    passingEvSemiLepTree->Branch("run_SL_L",&run_SL_L,"run_SL_L/i");
    passingEvSemiLepTree->Branch("event_SL_L",&event_SL_L,"event_SL_L/i");

    passingEvSemiLepTree->Branch("datasetType_SL_L",&datasetType_SL_L,"datasetType_SL_L/i");
    passingEvSemiLepTree->Branch("yearType_SL_L",&yearType_SL_L,"yearType_SL_L/i");

    passingEvSemiLepTree->Branch("runAlphNum_SL_L",&runAlphNum_SL_L,"runAlphNum_SL_L/i");
    passingEvSemiLepTree->Branch("APV_SL_L",&APV_SL_L,"APV_SL_L/O");
    passingEvSemiLepTree->Branch("JECCorInd_SL_L",&JECCorInd_SL_L,"JECCorInd_SL_L/I");
    passingEvSemiLepTree->Branch("RochInd_SL_L",&RochInd_SL_L,"RochInd_SL_L/I");


    passingEvSemiLepTree->Branch("eventNAK4Jets_SL_L",&eventNAK4Jets_SL_L,"eventNAK4Jets_SL_L/i");
    passingEvSemiLepTree->Branch("eventNAK8Jets_SL_L",&eventNAK8Jets_SL_L,"eventNAK8Jets_SL_L/i");
    passingEvSemiLepTree->Branch("eventNMuons_SL_L",&eventNMuons_SL_L,"eventNMuons_SL_L/i");
    passingEvSemiLepTree->Branch("eventNElectrons_SL_L",&eventNElectrons_SL_L,"eventNElectrons_SL_L/i");

    passingEvSemiLepTree->Branch("Jet_eta_SL_L",&Jet_eta_SL_L);
    passingEvSemiLepTree->Branch("Jet_pt_SL_L",&Jet_pt_SL_L);
    passingEvSemiLepTree->Branch("Jet_phi_SL_L",&Jet_phi_SL_L);
    passingEvSemiLepTree->Branch("Jet_mass_SL_L",&Jet_mass_SL_L);
    passingEvSemiLepTree->Branch("Jet_jetId_SL_L",&Jet_jetId_SL_L);
    passingEvSemiLepTree->Branch("Jet_btagDeepFlavB_SL_L",&Jet_btagDeepFlavB_SL_L);

    passingEvSemiLepTree->Branch("fixedGridRhoFastjetAll_SL_L",&fixedGridRhoFastjetAll_SL_L,"fixedGridRhoFastjetAll_SL_L/F");
    passingEvSemiLepTree->Branch("Jet_ptCorrectedDown_SL_L",&Jet_ptCorrectedDown_SL_L);
    passingEvSemiLepTree->Branch("Jet_ptCorrectedUp_SL_L",&Jet_ptCorrectedUp_SL_L);
    

    passingEvSemiLepTree->Branch("eventNAK4JetsPassingCuts_SL_L",&eventNAK4JetsPassingCuts_SL_L,"eventNAK4JetsPassingCuts_SL_L/i");

    passingEvSemiLepTree->Branch("eventNLooseElectrons_SL_L",&eventNLooseElectrons_SL_L,"eventNLooseElectrons_SL_L/i");
    passingEvSemiLepTree->Branch("eventNTightElectrons_SL_L",&eventNTightElectrons_SL_L,"eventNTightElectrons_SL_L/i");

    passingEvSemiLepTree->Branch("eventNLooseMuons_SL_L",&eventNLooseMuons_SL_L,"eventNLooseMuons_SL_L/i");
    passingEvSemiLepTree->Branch("eventNTightMuons_SL_L",&eventNTightMuons_SL_L,"eventNTightMuons_SL_L/i");

    passingEvSemiLepTree->Branch("selectedHiggsFJ_pt_SL_L",&selectedHiggsFJ_pt_SL_L,"selectedHiggsFJ_pt_SL_L/F");
    passingEvSemiLepTree->Branch("selectedHiggsFJ_eta_SL_L",&selectedHiggsFJ_eta_SL_L,"selectedHiggsFJ_eta_SL_L/F");
    passingEvSemiLepTree->Branch("selectedHiggsFJ_ParticleNet_HbbvsQCD_SL_L",&selectedHiggsFJ_ParticleNet_HbbvsQCD_SL_L,"selectedHiggsFJ_ParticleNet_HbbvsQCD_SL_L/F");
    passingEvSemiLepTree->Branch("selectedZFJ_pt_SL_L",&selectedZFJ_pt_SL_L,"selectedZFJ_pt_SL_L/F");
    passingEvSemiLepTree->Branch("selectedZFJ_eta_SL_L",&selectedZFJ_eta_SL_L,"selectedZFJ_eta_SL_L/F");
    passingEvSemiLepTree->Branch("selectedZFJ_ParticleNet_ZvsQCD_SL_L",&selectedZFJ_ParticleNet_ZvsQCD_SL_L,"selectedZFJ_ParticleNet_ZvsQCD_SL_L/F");

    passingEvSemiLepTree->Branch("selectedZFJ_InvMass_SL_L",&selectedZFJ_InvMass_SL_L,"selectedZFJ_InvMass_SL_L/F");
    passingEvSemiLepTree->Branch("selectedHiggsFJ_InvMass_SL_L",&selectedHiggsFJ_InvMass_SL_L,"selectedHiggsFJ_InvMass_SL_L/F");

    passingEvSemiLepTree->Branch("selectedZFJ_InvMassSoftDrop_SL_L",&selectedZFJ_InvMassSoftDrop_SL_L,"selectedZFJ_InvMassSoftDrop_SL_L/F");
    passingEvSemiLepTree->Branch("selectedHiggsFJ_InvMassSoftDrop_SL_L",&selectedHiggsFJ_InvMassSoftDrop_SL_L,"selectedHiggsFJ_InvMassSoftDrop_SL_L/F");

    passingEvSemiLepTree->Branch("selectedZFJ_InvMassPNRegress_SL_L",&selectedZFJ_InvMassPNRegress_SL_L,"selectedZFJ_InvMassPNRegress_SL_L/F");
    passingEvSemiLepTree->Branch("selectedHiggsFJ_InvMassPNRegress_SL_L",&selectedHiggsFJ_InvMassPNRegress_SL_L,"selectedHiggsFJ_InvMassPNRegress_SL_L/F");

    passingEvSemiLepTree->Branch("selectedHiggsFJ_ParticleNetMD_QCD_SL_L", &selectedHiggsFJ_ParticleNetMD_QCD_SL_L);
    passingEvSemiLepTree->Branch("selectedHiggsFJ_ParticleNetMD_Xbb_SL_L", &selectedHiggsFJ_ParticleNetMD_Xbb_SL_L);
    passingEvSemiLepTree->Branch("selectedHiggsFJ_ParticleNetMD_Xcc_SL_L", &selectedHiggsFJ_ParticleNetMD_Xcc_SL_L);
    passingEvSemiLepTree->Branch("selectedHiggsFJ_ParticleNetMD_Xqq_SL_L", &selectedHiggsFJ_ParticleNetMD_Xqq_SL_L);

    passingEvSemiLepTree->Branch("selectedZFJ_ParticleNetMD_QCD_SL_L", &selectedZFJ_ParticleNetMD_QCD_SL_L);
    passingEvSemiLepTree->Branch("selectedZFJ_ParticleNetMD_Xbb_SL_L", &selectedZFJ_ParticleNetMD_Xbb_SL_L);
    passingEvSemiLepTree->Branch("selectedZFJ_ParticleNetMD_Xcc_SL_L", &selectedZFJ_ParticleNetMD_Xcc_SL_L);
    passingEvSemiLepTree->Branch("selectedZFJ_ParticleNetMD_Xqq_SL_L", &selectedZFJ_ParticleNetMD_Xqq_SL_L);

    passingEvSemiLepTree->Branch("selectedLeadVBFJet_pt_SL_L",&selectedLeadVBFJet_pt_SL_L,"selectedLeadVBFJet_pt_SL_L/F");
    passingEvSemiLepTree->Branch("selectedTrailingVBFJet_pt_SL_L",&selectedTrailingVBFJet_pt_SL_L,"selectedTrailingVBFJet_pt_SL_L/F");
    passingEvSemiLepTree->Branch("selectedLeadVBFJet_eta_SL_L",&selectedLeadVBFJet_eta_SL_L,"selectedLeadVBFJet_eta_SL_L/F");
    passingEvSemiLepTree->Branch("selectedTrailingVBFJet_eta_SL_L",&selectedTrailingVBFJet_eta_SL_L,"selectedTrailingVBFJet_eta_SL_L/F");
    passingEvSemiLepTree->Branch("selectedVBFJets_EtaSep_SL_L",&selectedVBFJets_EtaSep_SL_L,"selectedVBFJets_EtaSep_SL_L/F");
    passingEvSemiLepTree->Branch("selectedVBFJets_InvMass_SL_L",&selectedVBFJets_InvMass_SL_L,"selectedVBFJets_InvMass_SL_L/F");

    passingEvSemiLepTree->Branch("selectedLeadLepton_pt_SL_L",&selectedLeadLepton_pt_SL_L,"selectedLeadLepton_pt_SL_L/F");
    passingEvSemiLepTree->Branch("selectedTrailingLepton_pt_SL_L",&selectedTrailingLepton_pt_SL_L,"selectedTrailingLepton_pt_SL_L/F");
    passingEvSemiLepTree->Branch("selectedLeadLepton_eta_SL_L",&selectedLeadLepton_eta_SL_L,"selectedLeadLepton_eta_SL_L/F");
    passingEvSemiLepTree->Branch("selectedTrailingLepton_eta_SL_L",&selectedTrailingLepton_eta_SL_L,"selectedTrailingLepton_eta_SL_L/F");
    passingEvSemiLepTree->Branch("selectedLeadLepton_phi_SL_L",&selectedLeadLepton_phi_SL_L,"selectedLeadLepton_phi_SL_L/F");
    passingEvSemiLepTree->Branch("selectedTrailingLepton_phi_SL_L",&selectedTrailingLepton_phi_SL_L,"selectedTrailingLepton_phi_SL_L/F");
    passingEvSemiLepTree->Branch("selectedLeadLepton_SIP3D_SL_L",&selectedLeadLepton_SIP3D_SL_L,"selectedLeadLepton_SIP3D_SL_L/F");
    passingEvSemiLepTree->Branch("selectedTrailingLepton_SIP3D_SL_L",&selectedTrailingLepton_SIP3D_SL_L,"selectedTrailingLepton_SIP3D_SL_L/F");
    passingEvSemiLepTree->Branch("selectedLeptons_RelIso_SL_L",&selectedLeptons_RelIso_SL_L,"selectedLeptons_RelIso_SL_L/F");
    passingEvSemiLepTree->Branch("selectedLeptons_InvMass_SL_L",&selectedLeptons_InvMass_SL_L,"selectedLeptons_InvMass_SL_L/F");
    passingEvSemiLepTree->Branch("selectedLeptons_IsMuon_SL_L",&selectedLeptons_IsMuon_SL_L,"selectedLeptons_IsMuon_SL_L/O");

    passingEvSemiLepTree->Branch("selectedZPairPlusHiggsFJ_InvMass_SL_L",&selectedZPairPlusHiggsFJ_InvMass_SL_L,"selectedZPairPlusHiggsFJ_InvMass_SL_L/F");
    passingEvSemiLepTree->Branch("selectedZPairPlusHiggsFJ_pt_SL_L",&selectedZPairPlusHiggsFJ_pt_SL_L,"selectedZPairPlusHiggsFJ_pt_SL_L/F");

    passingEvSemiLepTree->Branch("selectedVBFJets_MaxBTag_SL_L",&selectedVBFJets_MaxBTag_SL_L,"selectedVBFJets_MaxBTag_SL_L/F");


    passingEvSemiLepTree->Branch("selectedZPairPlusHiggsFJPlusVBFJets_PtVecSum_SL_L",&selectedZPairPlusHiggsFJPlusVBFJets_PtVecSum_SL_L,"selectedZPairPlusHiggsFJPlusVBFJets_PtVecSum_SL_L/F");
    passingEvSemiLepTree->Branch("selectedZPairPlusHiggsFJPlusVBFJets_PtScalarSum_SL_L",&selectedZPairPlusHiggsFJPlusVBFJets_PtScalarSum_SL_L,"selectedZPairPlusHiggsFJPlusVBFJets_PtScalarSum_SL_L/F");
    passingEvSemiLepTree->Branch("selectedZPairPlusHiggsFJPlusVBFJets_PtVecOverScalarSum_SL_L",&selectedZPairPlusHiggsFJPlusVBFJets_PtVecOverScalarSum_SL_L,"selectedZPairPlusHiggsFJPlusVBFJets_PtVecOverScalarSum_SL_L/F");




    

    std::cout << "Going into file loop.\n";

    for (UInt_t k=0; k<fileAr.size(); k++){
        if (endAfter && evCount > NToEnd) break;
        if (debug) std::cout<<"File:    "<<fileAr[k]<<"\n";
        //Open the file, get the Events tree
        TFile* tmpfile = TFile::Open(fileAr[k].c_str());
        //outFile->cd();
        TTreeReader myEventsReader("FilteredEventsTree", tmpfile);

        TTreeReaderValue<UInt_t> runL(myEventsReader, "runL");
        TTreeReaderValue<UInt_t> eventL(myEventsReader, "eventL");

        TTreeReaderValue<UInt_t> runAlphNumL(myEventsReader, "runAlphNumL");
        TTreeReaderValue<Bool_t> APVL(myEventsReader, "APVL");
        TTreeReaderValue<Int_t> JECCorIndL(myEventsReader, "JECCorIndL");
        TTreeReaderValue<Int_t> RochIndL(myEventsReader, "RochIndL");


        //jets

        TTreeReaderValue<UInt_t> nJetL(myEventsReader, "nJetL");
        TTreeReaderArray<Float_t> Jet_etaL(myEventsReader, "Jet_etaL");
        TTreeReaderArray<Float_t> Jet_ptL(myEventsReader, "Jet_ptL");
        TTreeReaderArray<Float_t> Jet_phiL(myEventsReader, "Jet_phiL");
        TTreeReaderArray<Float_t> Jet_massL(myEventsReader, "Jet_massL");
        TTreeReaderArray<Int_t> Jet_jetIdL(myEventsReader, "Jet_jetIdL");
        TTreeReaderArray<Float_t> Jet_btagDeepFlavBL(myEventsReader,"Jet_btagDeepFlavBL");

        TTreeReaderValue<Float_t> fixedGridRhoFastjetAllL(myEventsReader, "fixedGridRhoFastjetAllL");
        TTreeReaderArray<Float_t> Jet_ptCorrectedDownL(myEventsReader, "Jet_ptCorrectedDownL");
        TTreeReaderArray<Float_t> Jet_ptCorrectedUpL(myEventsReader, "Jet_ptCorrectedUpL");


        //Fat jets

        TTreeReaderValue<UInt_t> nFatJetL(myEventsReader, "nFatJetL");
        TTreeReaderArray<Float_t> FatJet_etaL(myEventsReader, "FatJet_etaL");
        TTreeReaderArray<Float_t> FatJet_ptL(myEventsReader, "FatJet_ptL");
        TTreeReaderArray<Float_t> FatJet_phiL(myEventsReader, "FatJet_phiL");
        TTreeReaderArray<Float_t> FatJet_massL(myEventsReader, "FatJet_massL");
        TTreeReaderArray<Int_t> FatJet_jetIdL(myEventsReader, "FatJet_jetIdL");
        //TTreeReaderArray<Float_t> FatJet_deepTag_HL(myEventsReader, "FatJet_deepTag_HL");
        //TTreeReaderArray<Float_t> FatJet_deepTag_ZvsQCDL(myEventsReader, "FatJet_deepTag_ZvsQCDL");
        TTreeReaderArray<Float_t> FatJet_msoftdropL(myEventsReader, "FatJet_msoftdropL");

        TTreeReaderArray<Float_t> FatJet_particleNet_massL(myEventsReader, "FatJet_particleNet_massL");

        TTreeReaderArray<Float_t> FatJet_ptCorrectedDownL(myEventsReader, "FatJet_ptCorrectedDownL");
        TTreeReaderArray<Float_t> FatJet_ptCorrectedUpL(myEventsReader, "FatJet_ptCorrectedUpL");


        //Electrons
        TTreeReaderValue<UInt_t> nElectronL(myEventsReader, "nElectronL");
        TTreeReaderArray<Float_t> Electron_etaL(myEventsReader, "Electron_etaL");
        TTreeReaderArray<Float_t> Electron_massL(myEventsReader, "Electron_massL");
        TTreeReaderArray<Int_t> Electron_chargeL(myEventsReader, "Electron_chargeL");
        TTreeReaderArray<Float_t> Electron_phiL(myEventsReader, "Electron_phiL");
        TTreeReaderArray<Float_t> Electron_ptL(myEventsReader, "Electron_ptL");
        TTreeReaderArray<Float_t> Electron_dr03EcalRecHitSumEtL(myEventsReader, "Electron_dr03EcalRecHitSumEtL");
        TTreeReaderArray<Float_t> Electron_dr03TkSumPtL(myEventsReader, "Electron_dr03TkSumPtL");
        TTreeReaderArray<Float_t> Electron_dr03HcalDepth1TowerSumEtL(myEventsReader, "Electron_dr03HcalDepth1TowerSumEtL");
        TTreeReaderArray<Float_t> Electron_pfRelIso03_allL(myEventsReader, "Electron_pfRelIso03_allL");
        TTreeReaderArray<Float_t> Electron_sip3dL(myEventsReader, "Electron_sip3dL");
        //TTreeReaderArray<Bool_t> Electron_mvaFall17V2Iso_WP80L(myEventsReader, "Electron_mvaFall17V2Iso_WP80L");
        TTreeReaderArray<Bool_t> Electron_mvaFall17V2noIso_WPLL(myEventsReader, "Electron_mvaFall17V2noIso_WPLL");

        //Muons
        TTreeReaderValue<UInt_t> nMuonL(myEventsReader, "nMuonL");
        TTreeReaderArray<Float_t> Muon_etaL(myEventsReader, "Muon_etaL");
        TTreeReaderArray<Float_t> Muon_massL(myEventsReader, "Muon_massL");
        TTreeReaderArray<Int_t> Muon_chargeL(myEventsReader, "Muon_chargeL");
        TTreeReaderArray<Float_t> Muon_phiL(myEventsReader, "Muon_phiL");
        TTreeReaderArray<Float_t> Muon_ptL(myEventsReader, "Muon_ptL");
        TTreeReaderArray<Float_t> Muon_pfRelIso03_allL(myEventsReader, "Muon_pfRelIso03_allL");
        TTreeReaderArray<Float_t> Muon_sip3dL(myEventsReader, "Muon_sip3dL");
        //TTreeReaderArray<Bool_t> Muon_tightIdL(myEventsReader, "Muon_tightIdL");
        TTreeReaderArray<Bool_t> Muon_mediumIdL(myEventsReader, "Muon_mediumIdL");
        TTreeReaderArray<Bool_t> Muon_looseIdL(myEventsReader, "Muon_looseIdL");
        TTreeReaderArray<Float_t> Muon_RochMomCorrectionsL(myEventsReader, "Muon_RochMomCorrectionsL");;
        TTreeReaderArray<Float_t> Muon_ptCorrectedL(myEventsReader, "Muon_ptCorrectedL");;
        TTreeReaderArray<Float_t> Muon_RochCorUncL(myEventsReader, "Muon_RochCorUncL");;




        //For LepID
        TTreeReaderArray<Float_t> Electron_dxyL(myEventsReader, "Electron_dxyL");
        TTreeReaderArray<Float_t> Electron_dzL(myEventsReader, "Electron_dzL");
        TTreeReaderArray<Float_t> Electron_miniPFRelIso_allL(myEventsReader, "Electron_miniPFRelIso_allL");
        TTreeReaderArray<Float_t> Electron_sieieL(myEventsReader, "Electron_sieieL");
        TTreeReaderArray<Float_t> Electron_hoeL(myEventsReader, "Electron_hoeL");
        TTreeReaderArray<Float_t> Electron_eInvMinusPInvL(myEventsReader, "Electron_eInvMinusPInvL");
        TTreeReaderArray<Bool_t> Electron_convVetoL(myEventsReader, "Electron_convVetoL");
        TTreeReaderArray<UChar_t> Electron_lostHitsL(myEventsReader, "Electron_lostHitsL");
        TTreeReaderArray<Int_t> Electron_jetIdxL(myEventsReader, "Electron_jetIdxL");
        TTreeReaderArray<Float_t> Electron_jetRelIsoL(myEventsReader, "Electron_jetRelIsoL");
        TTreeReaderArray<Float_t> Electron_mvaTTHL(myEventsReader, "Electron_mvaTTHL");

        TTreeReaderArray<Float_t> Muon_dxyL(myEventsReader, "Muon_dxyL");
        TTreeReaderArray<Float_t> Muon_dzL(myEventsReader, "Muon_dzL");
        TTreeReaderArray<Float_t> Muon_miniPFRelIso_allL(myEventsReader, "Muon_miniPFRelIso_allL");
        TTreeReaderArray<Int_t> Muon_jetIdxL(myEventsReader, "Muon_jetIdxL");
        TTreeReaderArray<Float_t> Muon_jetRelIsoL(myEventsReader, "Muon_jetRelIsoL");
        TTreeReaderArray<Float_t> Muon_mvaTTHL(myEventsReader, "Muon_mvaTTHL");

        

        //ParticleNet
        TTreeReaderArray<Float_t> FatJet_particleNet_HbbvsQCDL(myEventsReader, "FatJet_particleNet_HbbvsQCDL");
        TTreeReaderArray<Float_t> FatJet_particleNet_ZvsQCDL(myEventsReader, "FatJet_particleNet_ZvsQCDL");

        TTreeReaderArray<Float_t> FatJet_particleNetMD_QCDL(myEventsReader, "FatJet_particleNetMD_QCDL");
        TTreeReaderArray<Float_t> FatJet_particleNetMD_XbbL(myEventsReader, "FatJet_particleNetMD_XbbL");
        TTreeReaderArray<Float_t> FatJet_particleNetMD_XccL(myEventsReader, "FatJet_particleNetMD_XccL");
        TTreeReaderArray<Float_t> FatJet_particleNetMD_XqqL(myEventsReader, "FatJet_particleNetMD_XqqL");


        TTreeReader myEvNumReader("evNumTree", tmpfile);
        TTreeReaderValue<UInt_t> nEv(myEvNumReader, "nEv");
        TTreeReaderValue<UInt_t> nEvPass(myEvNumReader, "nEvPass");

        Int_t tmpPDGId;


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

        //BDT Vars
        float selectedLeptons_MaxRelIso;
        float selectedLeptons_InvMass;

        float selectedZOneLeptons_InvMass;
        float selectedZTwoLeptons_InvMass;

        float ZPairPlusHInvMass;
        float ZPairPlusHPt;

        while (myEvNumReader.Next()){
            /*
            datanEv = *nEv;
            datanEvPass = *nEvPass;
            */
            datanEv += *nEv;
            datanEvPass += *nEvPass;
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
            if (handBrake && evCount > handBrakeInd) break;
            //Increment event count
            evRunOver += 1;
            evCount += 1;
            //Depending on if JEC Correction is applied (JECCorInd), and whether or not it's up or down (UncUpDownBool), fill jet pt vector:
            std::vector<Float_t> jetPtVec;
            std::vector<Float_t> fatJetPtVec;
            if (JECCorInd == 0){
                for (UInt_t i=0; i<*nJetL; i++){
                    jetPtVec.push_back(Jet_ptL[i]);
                }
                for (UInt_t i=0; i<*nFatJetL; i++){
                    fatJetPtVec.push_back(FatJet_ptL[i]);
                }

            }
            else if (JECCorInd > 0){
                for (UInt_t i=0; i<*nJetL; i++){
                    if (UncUpDownBool) jetPtVec.push_back(Jet_ptCorrectedUpL[i]);
                    else jetPtVec.push_back(Jet_ptCorrectedDownL[i]);
                }
                for (UInt_t i=0; i<*nFatJetL; i++){
                    if (UncUpDownBool) fatJetPtVec.push_back(FatJet_ptCorrectedUpL[i]);
                    else fatJetPtVec.push_back(FatJet_ptCorrectedDownL[i]);
                }
            }
            else{
                std::cout << "Error: JECCorInd is " << JECCorInd << ". Must be >= 0.\n";
                return 1;
            }

            //Same for the Muon Rochestor corrections to pt
            std::vector<Float_t> muonPtVec;
            if (RochInd == 0){
                for (UInt_t i=0; i<*nMuonL; i++){
                    muonPtVec.push_back(Muon_ptCorrectedL[i]);
                }
            }
            else if (RochInd > 0){
                for (UInt_t i=0; i<*nMuonL; i++){
                    if (UncUpDownBool) muonPtVec.push_back(Muon_ptCorrectedL[i]+Muon_RochCorUncL[i]);
                    else muonPtVec.push_back(Muon_ptCorrectedL[i]-Muon_RochCorUncL[i]);
                }
            }
            else{
                std::cout << "Error: RochInd is " << RochInd << ". Must be >= 0.\n";
                return 1;
            }


            
            elecCandIndAr.clear();
            muonCandIndAr.clear();

            eZ2VecPairAr.clear();
            mZ2VecPairAr.clear();
            startingCtr += 1;

            


            bool passesCutsBool = false;
            bool passedAsLepBool = false;
            bool passedAsSemiLepBool = false;
            bool passedAsSemiLepLepCutBool = false;
            bool passedAsSemiLepHiggsCutBool = false;
            bool passedAsHadBool = false;
            



            UInt_t neLep = *nElectronL;
            UInt_t nmLep = *nMuonL;
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

            if (debug) cout << "trying Leptonic\n";
            tryingLepCtr += 1;
            std::vector<Float_t> LepInvMass;
            std::vector<Int_t> FJIndAr;

            //Higgs AK8 Jet Variables
            UInt_t nFatJetLen = *nFatJetL;
            
            float hFatJet_pt_fromHTag = 0.;
            float hFatJet_phi_fromHTag = 0.;
            float hFatJet_eta_fromHTag = 0.;
            float hFatJet_mass_fromHTag = 0.;
            float hFatJet_HTag_fromHTag = 0.;
            UInt_t hFatJet_ind_fromHTag = 0;

            
            /*
            std::cout << "elecIDVec.size() " << elecIDVec.size() << "\n";

            for (UInt_t lInd=0;lInd<elecIDVec.size();lInd++){
                std::cout << "lInd " << lInd << "\n";
                std::cout << "elecIDVec[lInd] " << elecIDVec[lInd] << "\n";
            }
            */
            std::vector<ROOT::Math::PtEtaPhiMVector> dRCheckVecAr;
            if (debug) std::cout << "*nJetL " << *nJetL << "\n";

            UInt_t elecTightCount = 0;
            UInt_t elecLooseCount = 0;
            
            
            getNTightAndLooseElectrons(Electron_mvaFall17V2noIso_WPLL,Electron_etaL,Electron_ptL,Electron_dxyL,Electron_dzL,Electron_sip3dL,Electron_miniPFRelIso_allL,Electron_sieieL,Electron_hoeL,Electron_eInvMinusPInvL,Electron_convVetoL,Electron_lostHitsL,Electron_jetIdxL,Jet_btagDeepFlavBL,Electron_mvaTTHL,neLep,ePtTightCut,ePtLooseCut,eEtaCut,lDxyCut,lDzCut,lMiniPFRelIsoCut,eSieieBarrelCut,eSieieEndcapCut,eHoeCut,eInvMinusPInvCut,eLostHitsCut,lepJetDeepTagLooseCut,lepJetDeepTagMediumCut,ePromptMVACut,SIPCut,elecTightCount,elecLooseCount,debug);
            
            UInt_t muonTightCount = 0;
            UInt_t muonLooseCount = 0;
            getNTightAndLooseMuons_RochUnc(Muon_looseIdL,Muon_mediumIdL,Muon_etaL,muonPtVec,Muon_dxyL,Muon_dzL,Muon_sip3dL,Muon_miniPFRelIso_allL,Muon_jetIdxL,Jet_btagDeepFlavBL,Muon_mvaTTHL,nmLep,mPtTightCut,mPtLooseCut,mEtaCut,lDxyCut,lDzCut,lMiniPFRelIsoCut,lepJetDeepTagLooseCut,lepJetDeepTagMediumCut,mPromptMVACut,SIPCut,muonTightCount,muonLooseCount,debug);
            
            
            
            doLeptonicCutsWithTree_RochUnc(Electron_etaL,Electron_massL,Electron_chargeL,Electron_phiL,Electron_ptL, neLep, elecCandIndAr, elecCandVecAr, elecCandChargeAr,negElecCands,posElecCands,totElecCands,enoughElecCands,negMuonCands,posMuonCands,totMuonCands,enoughMuonCands,enoughLepCands,ePtCut,eEtaCut,
            Muon_etaL,Muon_massL, Muon_chargeL,Muon_phiL,muonPtVec, nmLep, muonCandIndAr, muonCandVecAr, muonCandChargeAr,
            Electron_dxyL,Electron_dzL,Electron_miniPFRelIso_allL,Electron_sieieL,Electron_hoeL,Electron_eInvMinusPInvL,Electron_convVetoL,Electron_lostHitsL,Electron_jetIdxL,Jet_btagDeepFlavBL,Electron_mvaTTHL,

            Muon_dxyL,Muon_dzL,Muon_miniPFRelIso_allL,Muon_mvaTTHL,Muon_jetIdxL,

            lDxyCut,lDzCut,lMiniPFRelIsoCut,eSieieBarrelCut,eSieieEndcapCut,eHoeCut,eInvMinusPInvCut,eLostHitsCut,lepJetDeepTagLooseCut,lepJetDeepTagMediumCut,ePromptMVACut,mPromptMVACut,
            mPtCut,mEtaCut,
            Z1IsMuon,invMassCutLow,invMassCutHigh,ptLeadCut,ptTrailingCut,
            Z1LeadPt,Z1TrailingPt,Z1LeadItr,Z1TrailingItr,Z1LeadVec,Z1TrailingVec,Z1LeadCharge,Z1TrailingCharge,difFromZMassOne,
            eZ2VecPairAr,tmpZ2Ind,Z2IsMuon,tmpTopZ2LeadPt,tmpTopZ2TrailingPt,fourLepInvMassCut,optLepInvMassCut,
            mZ2VecPairAr,
            tmpZ1Vec,tmpZ1M,
            Electron_dr03EcalRecHitSumEtL,Electron_dr03TkSumPtL,Electron_dr03HcalDepth1TowerSumEtL,Electron_pfRelIso03_allL,
            Z1LeadIso,Muon_pfRelIso03_allL,Z1TrailingIso,Z2LeadIso,Z2TrailingIso,lepIsoCut,
            Z1LeadSIP,Electron_sip3dL,Z1TrailingSIP,Z2LeadSIP,Muon_sip3dL,Z2TrailingSIP,SIPCut,passLepCut,passesCutsBool,passedAsLepBool,
            LepInvMass,
            Electron_mvaFall17V2noIso_WPLL,Muon_mediumIdL,
            dRCheckVecAr,
            debug);

            

            

            
            if (debug) std::cout << "passesCutsBool " << passesCutsBool << "\n";
            if (passesCutsBool){
                //Fill Lep BDT Vars
                ROOT::Math::PtEtaPhiMVector tmpZ1Vec = dRCheckVecAr[0] + dRCheckVecAr[1];
                ROOT::Math::PtEtaPhiMVector tmpZ2Vec = dRCheckVecAr[2] + dRCheckVecAr[3];
                ROOT::Math::PtEtaPhiMVector tmpZPairVec = tmpZ1Vec + tmpZ2Vec;
                selectedZOneLeptons_InvMass = tmpZ1Vec.M();
                selectedZTwoLeptons_InvMass = tmpZ2Vec.M();
                selectedLeptons_InvMass = tmpZPairVec.M();
                if (Z1LeadIso > Z2LeadIso) {
                    if (Z1LeadIso > Z1TrailingIso) {
                        selectedLeptons_MaxRelIso = Z1LeadIso + max(Z1TrailingIso,max(Z2LeadIso,Z2TrailingIso));
                    }
                    else {
                        selectedLeptons_MaxRelIso = Z1TrailingIso + max(Z1LeadIso,Z2TrailingIso);
                    }
                }
                else{
                    if (Z2LeadIso > Z1TrailingIso) {
                        selectedLeptons_MaxRelIso = Z2LeadIso + max(Z1TrailingIso,max(Z1LeadIso,Z2TrailingIso));
                    }
                    else {
                        selectedLeptons_MaxRelIso = Z1TrailingIso + max(Z2LeadIso,Z2TrailingIso);
                    }
                }

                passChannelCtr += 1;
                
                passLepChannelCtr += 1;
                
                passLepOrSemiLepChannelCtr += 1;
            }
            if ((!passesCutsBool)){
                dRCheckVecAr.clear();
                std::vector<Float_t> SemiLepInvMass;
                
                if (debug) std::cout << "trying SemiLeptonic\n";
                tryingSemiLepChannelCtr += 1;
                
                tryingSemiLepCtr += 1;

                //Checking that there are enough FJs for both the Z and the H
                UInt_t numFatJet = *nFatJetL;

                UInt_t nPassingJetIdFJs = 0;
                for (UInt_t fatJetInd=0;fatJetInd<numFatJet;fatJetInd++){
                    if (FatJet_jetIdL[fatJetInd] == 6) nPassingJetIdFJs += 1;

                }

                if (nPassingJetIdFJs >=2){
                    passEnoughFJsInSemiLepChannelCtr += 1;
                    
                    enoughLepCands = false;
                    doSemiLepCutWithTreeWithBDTVars_RochUnc(enoughElecCands,negElecCands,posElecCands,totElecCands,Electron_etaL,Electron_massL,Electron_chargeL,Electron_phiL,Electron_ptL,neLep,elecCandIndAr,elecCandVecAr,elecCandChargeAr,ePtCut,eEtaCut,
                    enoughMuonCands,negMuonCands,posMuonCands,totMuonCands,Muon_etaL,Muon_massL,Muon_chargeL,Muon_phiL,muonPtVec,nmLep,muonCandIndAr,muonCandVecAr,muonCandChargeAr,mPtCut,mEtaCut,
                    enoughLepCands,invMassCutLow,invMassCutHigh,ptLeadCut,ptTrailingCut,Z1Cand,difFromZMassOne,Z1LeadItr,Z1TrailingItr,Z1LeadPt,Z1TrailingPt,Z1IsMuon,Z1LeadVec,Z1TrailingVec,Z1LeadCharge,Z1TrailingCharge,
                    Electron_dr03EcalRecHitSumEtL,Electron_dr03TkSumPtL,Electron_dr03HcalDepth1TowerSumEtL,Electron_pfRelIso03_allL,
                    Z1LeadIso,Muon_pfRelIso03_allL,Z1TrailingIso,lepIsoCut,
                    SemiLepInvMass,
                    Electron_mvaFall17V2noIso_WPLL,Muon_mediumIdL,
                    Electron_sip3dL,Muon_sip3dL,Z1LeadSIP,Z1TrailingSIP,
                    dRCheckVecAr,
                    passedAsSemiLepLepCutBool,
                    selectedLeptons_InvMass,
                    debug);
                    if (enoughLepCands){
                        passEnoughLepsInSemiLepChannelCtr += 1;
                        
                        
                    }

                    if (passedAsSemiLepLepCutBool){
                        if (debug) std::cout << "Passed semi lep lep cut\n";
                        passSemiLepLepCutCtr += 1;
                        
                        
                    }


                    if (debug){
                        std::cout << "Pre FJC dRCheckVecAr.size() " << dRCheckVecAr.size() << "\n";
                    }
                    doHiggsFatJetCutBeforeZMDPNSelection_JECUnc(nFatJetLen,hFatJet_pt_fromHTag,hFatJet_phi_fromHTag,hFatJet_eta_fromHTag,hFatJet_mass_fromHTag,hFatJet_HTag_fromHTag,hFatJet_ind_fromHTag,FatJet_particleNetMD_QCDL,FatJet_particleNetMD_XbbL,hFatJetParticleNetCut,fatJetPtVec,hFatJetPTCut,FatJet_jetIdL,FatJet_phiL,FatJet_etaL,FatJet_massL,dRCheckVecAr,dRCut,passedAsSemiLepLepCutBool,passedAsSemiLepHiggsCutBool);
                    
                    if (debug) std::cout << " found Higgs fat jet\n";
                    if (passedAsSemiLepHiggsCutBool){
                        passHiggsFJInSemiLepChannelCtr += 1;
                    }


                    
                    Int_t FJInd;

                    FJInd = -1;
                    UInt_t numFatJet = *nFatJetL;
                    if (debug){
                        std::cout << "Pre FJC dRCheckVecAr.size() " << dRCheckVecAr.size() << "\n";
                    }
                    doSemiLepChanFatJetCutAfterHMDPNSelection_JECUnc(FJInd,numFatJet,fatJetPTCut,fatJetZParticleNetCut,fatJetPtVec,FatJet_phiL,FatJet_etaL,FatJet_massL,FatJet_particleNetMD_QCDL,FatJet_particleNetMD_XbbL,FatJet_particleNetMD_XccL,FatJet_particleNetMD_XqqL,FatJet_jetIdL,dRCheckVecAr,dRCut,hFatJet_ind_fromHTag,passedAsSemiLepHiggsCutBool,passSemiLepCut,passesCutsBool,passedAsSemiLepBool);
                    if (debug){
                        std::cout << "Post FJC dRCheckVecAr.size() " << dRCheckVecAr.size() << " FJInd "<< FJInd <<"\n";
                    }
                    if (FJInd >= 0){
                        passFJInSemiLepChannelCtr += 1;
                        
                    FJIndAr.push_back(FJInd);
                    FJIndAr.push_back(hFatJet_ind_fromHTag);
                    
                    }

                }
                
                if (passesCutsBool){
                    passChannelCtr += 1;
                    


                    passSemiLepChannelCtr += 1;
                    

                    passLepOrSemiLepChannelCtr += 1;
                    
                }
            }
            if (debug) std::cout << "Test\n";
            if ((!passesCutsBool)){
                dRCheckVecAr.clear();

                nFatJetLen = *nFatJetL;
            
                hFatJet_pt_fromHTag = 0.;
                hFatJet_phi_fromHTag = 0.;
                hFatJet_eta_fromHTag = 0.;
                hFatJet_mass_fromHTag = 0.;
                hFatJet_HTag_fromHTag = 0.;
                hFatJet_ind_fromHTag = 0;

                tryingHadCtr += 1;
                LFJOneInd = -1;
                LFJTwoInd = -1;
                if (debug) std::cout << "---------------- Event " << evCount - 1 << " ----------------\n";
                //if (debug) std::cout << "hFatJet_ind_fromHTag " << hFatJet_ind_fromHTag << "\n";
                if (debug) std::cout << "fatJetPTCut " << fatJetPTCut << "\n";

                if (debug) std::cout << "--------- Entering FJ loop for Hadronic Channel ---------\n";

                UInt_t numFatJet = *nFatJetL;
                //still uses non-MD PN, but the cut is set to 0 and the selection is on Pt so it doesn't matter
                doHadChanFatJetCut_JECUnc(LFJOneInd,LFJTwoInd,numFatJet,fatJetPTCut,fatJetZPairInvMassCut,fatJetPtVec,FatJet_phiL,FatJet_etaL,FatJet_massL,FatJet_particleNet_ZvsQCDL);

                
                if (LFJOneInd != LFJTwoInd){
                    passHadCut += 1;
                    passesCutsBool = true;
                    passedAsHadBool = true;
                    FJIndAr.push_back(LFJOneInd);
                    FJIndAr.push_back(LFJTwoInd);
                    dRCheckVecAr.push_back(ROOT::Math::PtEtaPhiMVector(fatJetPtVec[LFJOneInd],FatJet_etaL[LFJOneInd],FatJet_phiL[LFJOneInd],FatJet_massL[LFJOneInd]));
                    dRCheckVecAr.push_back(ROOT::Math::PtEtaPhiMVector(fatJetPtVec[LFJTwoInd],FatJet_etaL[LFJTwoInd],FatJet_phiL[LFJTwoInd],FatJet_massL[LFJTwoInd]));
                }
                if (passesCutsBool){
                    passChannelCtr += 1;
                    
                    passHadChannelCtr += 1;
                    
                }
            }
            if ((!passesCutsBool)) continue;
            

            //Now fat jets
            
            if (debug){
                std::cout << "Entering Fat Jets Loop\n";
            }

            if (!passedAsSemiLepBool){
                //doHiggsFatJetCut(nFatJetLen,hFatJet_HTag_fromPt,hFatJet_pt_fromPt,hFatJet_phi_fromPt,hFatJet_eta_fromPt,hFatJet_mass_fromPt,hFatJet_pt_fromHTag,hFatJet_phi_fromHTag,hFatJet_eta_fromHTag,hFatJet_mass_fromHTag,hFatJet_HTag_fromHTag,hFatJet_ind_fromHTag,FatJet_deepTag_HL,hFatJetDeepTagCut,FatJet_ptL,hFatJetPTCut,FatJet_jetIdL,FatJet_phiL,FatJet_etaL,jetLeadPhi,jetLeadEta,jetTrailingPhi,jetTrailingEta,hFatJetdRCut,FatJet_massL);
                //Replacing hFatJetDeepTagCut
                //doHiggsFatJetCut(nFatJetLen,hFatJet_pt_fromHTag,hFatJet_phi_fromHTag,hFatJet_eta_fromHTag,hFatJet_mass_fromHTag,hFatJet_HTag_fromHTag,hFatJet_ind_fromHTag,FatJet_particleNet_HbbvsQCDL,hFatJetParticleNetCut,FatJet_ptL,hFatJetPTCut,FatJet_jetIdL,FatJet_phiL,FatJet_etaL,FatJet_massL,dRCheckVecAr,dRCut,FJIndAr,ZPairPlusHInvMassCut,ZPairPlusHPtCut);
                doHiggsFatJetCutEarlyMDPNSelection_JECUnc(nFatJetLen,hFatJet_pt_fromHTag,hFatJet_phi_fromHTag,hFatJet_eta_fromHTag,hFatJet_mass_fromHTag,hFatJet_HTag_fromHTag,hFatJet_ind_fromHTag,FatJet_particleNetMD_QCDL,FatJet_particleNetMD_XbbL,hFatJetParticleNetCut,fatJetPtVec,hFatJetPTCut,FatJet_jetIdL,FatJet_phiL,FatJet_etaL,FatJet_massL,dRCheckVecAr,dRCut,FJIndAr);
                
                if (hFatJet_pt_fromHTag == 0) continue;
                if (debug) std::cout << " found Higgs fat jet\n";
                passHiggsFJPreSTCtr += 1;

                

                if (passedAsLepBool) {
                    passHiggsFJPreSTLepCtr += 1;
                    
                }
                else if (passedAsSemiLepBool) {
                    passHiggsFJPreSTSemiLepCtr += 1;
                    
                }
                else if (passedAsHadBool) {
                    passHiggsFJPreSTHadCtr += 1;
                    
                }
            }








            bool passesSTCutBool = false;
            doHiggsFatJetCutSTWithBDTVars(dRCheckVecAr,ZPairPlusHInvMassCut,ZPairPlusHPtCut,ZPairPlusHInvMass,ZPairPlusHPt,passesSTCutBool);
            if (!passesSTCutBool) continue;
            if (debug) std::cout << " found Higgs fat jet\n";
            passHiggsFJCtr += 1;
            

            if (passedAsLepBool) {
                passHiggsFJLepCtr += 1;
                
            }
            else if (passedAsSemiLepBool) {
                passHiggsFJSemiLepCtr += 1;
                
            }
            else if (passedAsHadBool) {
                passHiggsFJHadCtr += 1;
                
            }
            //passFatJets += 1;


            


            //Now match VBF jets
            UInt_t nJetLen        = *nJetL;
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
            float jetLeadMass    = 0;
            float jetTrailingMass    = 0;

            //B jet veto
            bool passBJetVeto = true;
            float maxPassingBTag = 0;
            doBJetVeto_WithBDTVariables_JECUnc(nJetLen,jetPtVec,Jet_etaL,Jet_phiL,Jet_btagDeepFlavBL,hFatJet_phi_fromHTag,hFatJet_eta_fromHTag,dRCut,bTagCut,passBJetVeto,maxPassingBTag,debug);
            if (!passBJetVeto) continue;

            passVBFJetBVetoCtr += 1;

            if (passedAsLepBool) {
                passVBFJetBVetoLepCtr += 1;
                
            }
            else if (passedAsSemiLepBool) {
                passVBFJetBVetoSemiLepCtr += 1;
                
            }
            else if (passedAsHadBool) {
                passVBFJetBVetoHadCtr += 1;
                
            }

            


            if (debug) std::cout << "Entering jet loop. Len: " << nJetLen << "\n";
            //doVBFJetCutPtSelectionWithBDTVars(nJetLen,Jet_ptL,Jet_jetIdL,Jet_etaL,Jet_phiL,Jet_massL,jetPTCut,jetEtaDifCut,jetInvMassCut,jetPairInvMass,jetLeadPt,jetLeadEta,jetLeadPhi,jetLeadMass,jetTrailingPt,jetTrailingEta,jetTrailingPhi,jetTrailingMass,leadJet_1,leadJet_2,dRCheckVecAr,dRCut,debug);
            //doVBFJetCutdEtaSelectionWithBDTVars(nJetLen,Jet_ptL,Jet_jetIdL,Jet_etaL,Jet_phiL,Jet_massL,jetPTCut,jetEtaDifCut,jetInvMassCut,jetPairInvMass,jetLeadPt,jetLeadEta,jetLeadPhi,jetLeadMass,jetTrailingPt,jetTrailingEta,jetTrailingPhi,jetTrailingMass,leadJet_1,leadJet_2,dRCheckVecAr,dRCut,debug);
            doVBFJetCutdEtaSelectionNoInvMassWithBDTVar_JECUnc(nJetLen,jetPtVec,Jet_jetIdL,Jet_etaL,Jet_phiL,Jet_massL,jetPTCut,jetEtaDifCut,jetInvMassCut,jetPairInvMass,jetLeadPt,jetLeadEta,jetLeadPhi,jetLeadMass,jetTrailingPt,jetTrailingEta,jetTrailingPhi,jetTrailingMass,leadJet_1,leadJet_2,dRCheckVecAr,dRCut,debug);
            //std::cout << jetLeadPt << endl;
            if (jetLeadPt == 0) continue;
            debugOutputForVBFJetCut(evCount,leadJet_1,leadJet_2,Jet_phiL,Jet_etaL,debug);
            passVBFJets += 1;

            ROOT::Math::PtEtaPhiMVector tmpLeadJetVec = ROOT::Math::PtEtaPhiMVector(jetLeadPt, jetLeadEta, jetLeadPhi, jetLeadMass);
            ROOT::Math::PtEtaPhiMVector tmpTrailingJetVec = ROOT::Math::PtEtaPhiMVector(jetTrailingPt, jetTrailingEta, jetTrailingPhi, jetTrailingMass);

            ROOT::Math::PtEtaPhiMVector tmpPtVecSumVec = tmpLeadJetVec + tmpTrailingJetVec;
            float tmpPtScalarSum = tmpLeadJetVec.Pt() + tmpTrailingJetVec.Pt();

            for (UInt_t dRCheckVecInd=0; dRCheckVecInd<dRCheckVecAr.size();dRCheckVecInd++) {
                tmpPtVecSumVec += dRCheckVecAr[dRCheckVecInd];
                tmpPtScalarSum += dRCheckVecAr[dRCheckVecInd].Pt();
            }

            if (passesCutsBool){
                passVBFJetsCtr += 1;

                //get number of passing VBFJets

                UInt_t tmpnAK4JetsPassing = 0;

                for (UInt_t nJetItr=0; nJetItr<nJetLen;nJetItr++){
                    UInt_t tmpJetPt = jetPtVec[nJetItr];
                    //Jet_etaL[nJetItr]
                    Int_t tmpJetId = Jet_jetIdL[nJetItr];
                    if (tmpJetPt < 30 || !(tmpJetId == 6)) continue;
                    tmpnAK4JetsPassing += 1;

                
                }
                

                //std::cout << passedAsLepBool << " "<< passedAsSemiLepBool << " " << passedAsHadBool << "\n";
                if (passedAsLepBool) {

                    passAsLepCtr += 1;

                    //Fill BDT Lep Tree

                    run_L_L = *runL;
                    event_L_L = *eventL;

                    datasetType_L_L = datasetType;
                    yearType_L_L = yearType;

                    eventNAK4Jets_L_L = nJetLen;
                    eventNAK8Jets_L_L = nFatJetLen;
                    eventNMuons_L_L = nmLep;
                    eventNElectrons_L_L = neLep;

                    for (UInt_t nJetItr=0; nJetItr<nJetLen;nJetItr++){
                        Jet_eta_L_L.push_back(Jet_etaL[nJetItr]);
                        Jet_pt_L_L.push_back(jetPtVec[nJetItr]);
                        Jet_phi_L_L.push_back(Jet_phiL[nJetItr]);
                        Jet_mass_L_L.push_back(Jet_massL[nJetItr]);
                        Jet_jetId_L_L.push_back(Jet_jetIdL[nJetItr]);
                        Jet_btagDeepFlavB_L_L.push_back(Jet_btagDeepFlavBL[nJetItr]);
                    }


                    eventNAK4JetsPassingCuts_L_L = tmpnAK4JetsPassing;

                    eventNLooseElectrons_L_L = elecLooseCount;
                    eventNTightElectrons_L_L = elecTightCount;

                    eventNLooseMuons_L_L = muonLooseCount;
                    eventNTightMuons_L_L = muonTightCount;

                    selectedHiggsFJ_pt_L_L = hFatJet_pt_fromHTag;
                    selectedHiggsFJ_eta_L_L = hFatJet_eta_fromHTag;
                    selectedHiggsFJ_ParticleNet_HbbvsQCD_L_L = FatJet_particleNet_HbbvsQCDL[FJIndAr[0]];

                    selectedHiggsFJ_ParticleNetMD_QCD_L_L = FatJet_particleNetMD_QCDL[FJIndAr[0]];
                    selectedHiggsFJ_ParticleNetMD_Xbb_L_L = FatJet_particleNetMD_XbbL[FJIndAr[0]];
                    selectedHiggsFJ_ParticleNetMD_Xcc_L_L = FatJet_particleNetMD_XccL[FJIndAr[0]];
                    selectedHiggsFJ_ParticleNetMD_Xqq_L_L = FatJet_particleNetMD_XqqL[FJIndAr[0]];

                    selectedLeadVBFJet_pt_L_L = jetLeadPt;
                    selectedTrailingVBFJet_pt_L_L = jetTrailingPt;
                    selectedLeadVBFJet_eta_L_L = jetLeadEta;
                    selectedTrailingVBFJet_eta_L_L = jetTrailingEta;
                    selectedVBFJets_EtaSep_L_L = abs(jetLeadEta - jetTrailingEta);
                    selectedVBFJets_InvMass_L_L = jetPairInvMass;

                    selectedZOneLeadLepton_pt_L_L = Z1LeadPt;
                    selectedZOneTrailingLepton_pt_L_L = Z1TrailingPt;
                    selectedZOneLeadLepton_eta_L_L = dRCheckVecAr[0].Eta();
                    selectedZOneTrailingLepton_eta_L_L = dRCheckVecAr[1].Eta();
                    selectedZOneLeadLepton_phi_L_L = dRCheckVecAr[0].Phi();
                    selectedZOneTrailingLepton_phi_L_L = dRCheckVecAr[1].Phi();
                    selectedZOneLeadLepton_SIP3D_L_L = Z1LeadSIP;
                    selectedZOneTrailingLepton_SIP3D_L_L = Z1TrailingSIP;

                    selectedZOneLeptons_InvMass_L_L = selectedZOneLeptons_InvMass; 
                    selectedZOneLeptons_Type_L_L = Z1IsMuon;

                    selectedZTwoLeadLepton_pt_L_L = tmpTopZ2LeadPt;
                    selectedZTwoTrailingLepton_pt_L_L = tmpTopZ2TrailingPt;
                    selectedZTwoLeadLepton_eta_L_L = dRCheckVecAr[2].Eta();
                    selectedZTwoTrailingLepton_eta_L_L = dRCheckVecAr[3].Eta();
                    selectedZTwoLeadLepton_phi_L_L = dRCheckVecAr[2].Phi();
                    selectedZTwoTrailingLepton_phi_L_L = dRCheckVecAr[3].Phi();
                    selectedZTwoLeadLepton_SIP3D_L_L = Z2LeadSIP;
                    selectedZTwoTrailingLepton_SIP3D_L_L = Z2TrailingSIP;

                    selectedZTwoLeptons_InvMass_L_L = selectedZTwoLeptons_InvMass; 
                    selectedZTwoLeptons_Type_L_L = Z2IsMuon;
                    
                    
                    selectedLeptons_MaxRelIso_L_L = selectedLeptons_MaxRelIso;
                    selectedLeptons_InvMass_L_L = selectedLeptons_InvMass;

                    selectedZPairPlusHiggsFJ_InvMass_L_L = ZPairPlusHInvMass;
                    selectedZPairPlusHiggsFJ_pt_L_L = ZPairPlusHPt;

                    selectedVBFJets_MaxBTag_L_L = maxPassingBTag;

                    selectedZPairPlusHiggsFJPlusVBFJets_PtVecSum_L_L = tmpPtVecSumVec.Pt();
                    selectedZPairPlusHiggsFJPlusVBFJets_PtScalarSum_L_L = tmpPtScalarSum;
                    selectedZPairPlusHiggsFJPlusVBFJets_PtVecOverScalarSum_L_L = tmpPtVecSumVec.Pt()/tmpPtScalarSum;


                    passingEvLepTree->Fill();

                    Jet_eta_L_L.clear();
                    Jet_pt_L_L.clear();
                    Jet_phi_L_L.clear();
                    Jet_mass_L_L.clear();
                    Jet_jetId_L_L.clear();
                    Jet_btagDeepFlavB_L_L.clear();
                    
                    
                    
                }
                
                else if (passedAsSemiLepBool){


                    passAsSemiLepCtr += 1;

                    //Fill BDT SemiLep Tree

                    run_SL_L = *runL;
                    event_SL_L = *eventL;

                    datasetType_SL_L = datasetType;
                    yearType_SL_L = yearType;

                    runAlphNum_SL_L = *runAlphNumL;
                    APV_SL_L = *APVL;
                    JECCorInd_SL_L = *JECCorIndL;
                    RochInd_SL_L = *RochIndL;

                    

                    eventNAK4Jets_SL_L = nJetLen;
                    eventNAK8Jets_SL_L = nFatJetLen;
                    eventNMuons_SL_L = nmLep;
                    eventNElectrons_SL_L = neLep;

                    for (UInt_t nJetItr=0; nJetItr<nJetLen;nJetItr++){
                        Jet_eta_SL_L.push_back(Jet_etaL[nJetItr]);
                        Jet_pt_SL_L.push_back(jetPtVec[nJetItr]);
                        Jet_phi_SL_L.push_back(Jet_phiL[nJetItr]);
                        Jet_mass_SL_L.push_back(Jet_massL[nJetItr]);
                        Jet_jetId_SL_L.push_back(Jet_jetIdL[nJetItr]);
                        Jet_btagDeepFlavB_SL_L.push_back(Jet_btagDeepFlavBL[nJetItr]);
                        Jet_ptCorrectedDown_SL_L.push_back(Jet_ptCorrectedDownL[nJetItr]);
                        Jet_ptCorrectedUp_SL_L.push_back(Jet_ptCorrectedUpL[nJetItr]);
                    }
                    fixedGridRhoFastjetAll_SL_L = *fixedGridRhoFastjetAllL;

                    eventNAK4JetsPassingCuts_SL_L = tmpnAK4JetsPassing;

                    eventNLooseElectrons_SL_L = elecLooseCount;
                    eventNTightElectrons_SL_L = elecTightCount;

                    eventNLooseMuons_SL_L = muonLooseCount;
                    eventNTightMuons_SL_L = muonTightCount;

                    selectedHiggsFJ_pt_SL_L = hFatJet_pt_fromHTag;
                    selectedZFJ_pt_SL_L = dRCheckVecAr[3].Pt();
                    selectedHiggsFJ_eta_SL_L = hFatJet_eta_fromHTag;
                    selectedZFJ_eta_SL_L = dRCheckVecAr[3].Eta();
                    selectedZFJ_InvMass_SL_L = dRCheckVecAr[3].M();
                    selectedHiggsFJ_InvMass_SL_L = dRCheckVecAr[2].M();
                    selectedHiggsFJ_ParticleNet_HbbvsQCD_SL_L = FatJet_particleNet_HbbvsQCDL[FJIndAr[1]];

                    selectedZFJ_InvMassSoftDrop_SL_L = FatJet_msoftdropL[FJIndAr[0]];
                    selectedHiggsFJ_InvMassSoftDrop_SL_L = FatJet_msoftdropL[FJIndAr[1]];

                    selectedZFJ_InvMassPNRegress_SL_L = FatJet_particleNet_massL[FJIndAr[0]];
                    selectedHiggsFJ_InvMassPNRegress_SL_L = FatJet_particleNet_massL[FJIndAr[1]];

                    selectedZFJ_ParticleNet_ZvsQCD_SL_L = FatJet_particleNet_ZvsQCDL[FJIndAr[0]];

                    selectedHiggsFJ_ParticleNetMD_QCD_SL_L = FatJet_particleNetMD_QCDL[FJIndAr[1]];
                    selectedHiggsFJ_ParticleNetMD_Xbb_SL_L = FatJet_particleNetMD_XbbL[FJIndAr[1]];
                    selectedHiggsFJ_ParticleNetMD_Xcc_SL_L = FatJet_particleNetMD_XccL[FJIndAr[1]];
                    selectedHiggsFJ_ParticleNetMD_Xqq_SL_L = FatJet_particleNetMD_XqqL[FJIndAr[1]];

                    selectedZFJ_ParticleNetMD_QCD_SL_L = FatJet_particleNetMD_QCDL[FJIndAr[0]];
                    selectedZFJ_ParticleNetMD_Xbb_SL_L = FatJet_particleNetMD_XbbL[FJIndAr[0]];
                    selectedZFJ_ParticleNetMD_Xcc_SL_L = FatJet_particleNetMD_XccL[FJIndAr[0]];
                    selectedZFJ_ParticleNetMD_Xqq_SL_L = FatJet_particleNetMD_XqqL[FJIndAr[0]];

                    selectedLeadVBFJet_pt_SL_L = jetLeadPt;
                    selectedTrailingVBFJet_pt_SL_L = jetTrailingPt;
                    selectedLeadVBFJet_eta_SL_L = jetLeadEta;
                    selectedTrailingVBFJet_eta_SL_L = jetTrailingEta;
                    selectedVBFJets_EtaSep_SL_L = abs(jetLeadEta - jetTrailingEta);
                    selectedVBFJets_InvMass_SL_L = jetPairInvMass;

                    selectedLeadLepton_pt_SL_L = Z1LeadPt;
                    selectedTrailingLepton_pt_SL_L = Z1TrailingPt;
                    selectedLeadLepton_eta_SL_L = dRCheckVecAr[0].Eta();
                    selectedTrailingLepton_eta_SL_L = dRCheckVecAr[1].Eta();
                    selectedLeadLepton_phi_SL_L = dRCheckVecAr[0].Phi();
                    selectedTrailingLepton_phi_SL_L = dRCheckVecAr[1].Phi();
                    selectedLeadLepton_SIP3D_SL_L = Z1LeadSIP;
                    selectedTrailingLepton_SIP3D_SL_L = Z1TrailingSIP;
                    selectedLeptons_RelIso_SL_L = Z1LeadIso+Z1TrailingIso;
                    selectedLeptons_InvMass_SL_L = selectedLeptons_InvMass;
                    selectedLeptons_IsMuon_SL_L = Z1IsMuon;

                    selectedZPairPlusHiggsFJ_InvMass_SL_L = ZPairPlusHInvMass;
                    selectedZPairPlusHiggsFJ_pt_SL_L = ZPairPlusHPt;

                    selectedVBFJets_MaxBTag_SL_L = maxPassingBTag;

                    selectedZPairPlusHiggsFJPlusVBFJets_PtVecSum_SL_L = tmpPtVecSumVec.Pt();
                    selectedZPairPlusHiggsFJPlusVBFJets_PtScalarSum_SL_L = tmpPtScalarSum;
                    selectedZPairPlusHiggsFJPlusVBFJets_PtVecOverScalarSum_SL_L = tmpPtVecSumVec.Pt()/tmpPtScalarSum;


                    passingEvSemiLepTree->Fill();

                    Jet_eta_SL_L.clear();
                    Jet_pt_SL_L.clear();
                    Jet_phi_SL_L.clear();
                    Jet_mass_SL_L.clear();
                    Jet_jetId_SL_L.clear();
                    Jet_btagDeepFlavB_SL_L.clear();
                    Jet_ptCorrectedDown_SL_L.clear();
                    Jet_ptCorrectedUp_SL_L.clear();
                    

                }
                else if (passedAsHadBool) {

                    passAsHadCtr += 1;
                    
                }

            }

        }
    }
    if (debug) std::cout << "Filling complete \n";

    clock_t endt = clock();
    double time_spent = (double)(endt - startt) / CLOCKS_PER_SEC;


    std::cout << "Finished file loop. " << "time: " << time_spent << "\n";
    
    std::cout << "nEv total: " << datanEv << "\n";
    std::cout << "nEv post pre-selection: " << datanEvPass << "\n"; 
    

    std::cout << "==============================TOTAL COUNTERS==============================\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "startingCtr = " << startingCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "tryingSemiLepChannelCtr = " << tryingSemiLepChannelCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "passEnoughFJsInSemiLepChannelCtr = " << passEnoughFJsInSemiLepChannelCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "passEnoughLepsInSemiLepChannelCtr = " << passEnoughLepsInSemiLepChannelCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "passSemiLepLepCutCtr = " << passSemiLepLepCutCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "passHiggsFJInSemiLepChannelCtr = " << passHiggsFJInSemiLepChannelCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "passFJInSemiLepChannelCtr = " << passFJInSemiLepChannelCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassChannelCtr = " << passChannelCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassLepOrSemiLepChannelCtr = " << passLepOrSemiLepChannelCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassLepChannelCtr = " << passLepChannelCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassSemiLepChannelCtr = " << passSemiLepChannelCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHadChannelCtr = " << passHadChannelCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJPreSTCtr = " << passHiggsFJPreSTCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJPreSTLepCtr = " << passHiggsFJPreSTLepCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJPreSTSemiLepCtr = " << passHiggsFJPreSTSemiLepCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJPreSTHadCtr = " << passHiggsFJPreSTHadCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJCtr = " << passHiggsFJCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJLepCtr = " << passHiggsFJLepCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJSemiLepCtr = " << passHiggsFJSemiLepCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJHadCtr = " << passHiggsFJHadCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassVBFJetBVetoLepCtr = " << passVBFJetBVetoLepCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassVBFJetBVetoSemiLepCtr = " << passVBFJetBVetoSemiLepCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassVBFJetBVetoHadCtr = " << passVBFJetBVetoHadCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassVBFJetsCtr = " << passVBFJetsCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassAsLepCtr = " << passAsLepCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassAsSemiLepCtr = " << passAsSemiLepCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassAsHadCtr = " << passAsHadCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "\n";



    outFile->cd();
    passingEvLepTree->Write("",TObject::kOverwrite);
    passingEvSemiLepTree->Write("",TObject::kOverwrite);

    outFile->Close();

}