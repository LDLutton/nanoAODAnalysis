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
void calc12122023JECRoch(string datasetString, int JECCorInd, int AK8JECCorInd,  int RochInd){
    // Open the file. Note that the name of your file outside this class
    // will probably NOT be experiment.root.
    std::cout << "start Analysis\n";
    clock_t startt = clock();


    RoccoR  rc("../RoccoR2018UL.txt"); 

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


    std::string outFileStr = "new10162023BDTAnalysis"+saveName+"_"+std::to_string(JECCorInd)+"_"+std::to_string(AK8JECCorInd)+"_"+std::to_string(RochInd)+".root";
    std::cout << "OutFile: " << outFileStr << "\n";
    TFile *outFile = new TFile(outFileStr.c_str(),"RECREATE");

    UInt_t datanEv = 0;
    UInt_t datanEvPass = 0;
    UInt_t evCount = 0;
    UInt_t evRunOver = 0;

    //Array for holding different correction types
    std::string corrTypeAr[27] = {"Central","AbsoluteMPFBias","AbsoluteStat","FlavorQCD","Fragmentation","PileUpDataMC","PileUpPtBB","PileUpPtEC1","PileUpPtEC2","PileUpPtHF","PileUpPtRef","RelativeFSR","RelativeJEREC1","RelativeJEREC2",
                                "RelativeJERHF","RelativePtBB","RelativePtEC1","RelativePtEC2","RelativePtHF","RelativeBal","RelativeSample","RelativeStatEC","RelativeStatFSR","RelativeStatHF","SinglePionECAL","SinglePionHCAL","TimePtEta"};


    //Vector for holding the different text file names based on run
    std::vector<std::string> textFileAr;
    //Using the full path "NanoCORE/Tools/jetcorr/data/Summer19UL18_Run{}_V5_DATA/Summer19UL18_Run{}_V5_DATA_UncertaintySources_AK4PFchs.txt" as base string, fill vector with ["A","B","C","D"]
    if (yearType == 0) {
        textFileAr.push_back("../NanoCORE/Tools/jetcorr/data/Summer19UL18_RunA_V5_DATA/Summer19UL18_RunA_V5_DATA_UncertaintySources_AK4PFchs_");
        textFileAr.push_back("../NanoCORE/Tools/jetcorr/data/Summer19UL18_RunB_V5_DATA/Summer19UL18_RunB_V5_DATA_UncertaintySources_AK4PFchs_");
        textFileAr.push_back("../NanoCORE/Tools/jetcorr/data/Summer19UL18_RunC_V5_DATA/Summer19UL18_RunC_V5_DATA_UncertaintySources_AK4PFchs_");
        textFileAr.push_back("../NanoCORE/Tools/jetcorr/data/Summer19UL18_RunD_V5_DATA/Summer19UL18_RunD_V5_DATA_UncertaintySources_AK4PFchs_");
    }
    else if (yearType == 1) {
        //now do for UL17 with A to F
        textFileAr.push_back("../NanoCORE/Tools/jetcorr/data/Summer19UL17_RunA_V5_DATA/Summer19UL17_RunA_V5_DATA_UncertaintySources_AK4PFchs_");
        textFileAr.push_back("../NanoCORE/Tools/jetcorr/data/Summer19UL17_RunB_V5_DATA/Summer19UL17_RunB_V5_DATA_UncertaintySources_AK4PFchs_");
        textFileAr.push_back("../NanoCORE/Tools/jetcorr/data/Summer19UL17_RunC_V5_DATA/Summer19UL17_RunC_V5_DATA_UncertaintySources_AK4PFchs_");
        textFileAr.push_back("../NanoCORE/Tools/jetcorr/data/Summer19UL17_RunD_V5_DATA/Summer19UL17_RunD_V5_DATA_UncertaintySources_AK4PFchs_");
        textFileAr.push_back("../NanoCORE/Tools/jetcorr/data/Summer19UL17_RunE_V5_DATA/Summer19UL17_RunE_V5_DATA_UncertaintySources_AK4PFchs_");
        textFileAr.push_back("../NanoCORE/Tools/jetcorr/data/Summer19UL17_RunF_V5_DATA/Summer19UL17_RunF_V5_DATA_UncertaintySources_AK4PFchs_");
    }
    else if (yearType == 2) {
        //now do for UL16 with B to F
        textFileAr.push_back("../NanoCORE/Tools/jetcorr/data/Summer19UL16APV_RunBCD_V7_DATA/Summer19UL16APV_RunBCD_V7_DATA_UncertaintySources_AK4PFchs_");
        textFileAr.push_back("../NanoCORE/Tools/jetcorr/data/Summer19UL16_RunEF_V7_DATA/Summer19UL16_RunEF_V7_DATA_UncertaintySources_AK4PFchs_");
        textFileAr.push_back("../NanoCORE/Tools/jetcorr/data/Summer19UL16_RunFGH_V7_DATA/Summer19UL16_RunFGH_V7_DATA_UncertaintySources_AK4PFchs_");
    }
    //Same but for AK8 Puppi jets
    std::vector<std::string> textFileArAK8;
    if (yearType == 0) {
        textFileArAK8.push_back("../NanoCORE/Tools/jetcorr/data/Summer19UL18_RunA_V5_DATA/Summer19UL18_RunA_V5_DATA_UncertaintySources_AK8PFPuppi_");
        textFileArAK8.push_back("../NanoCORE/Tools/jetcorr/data/Summer19UL18_RunB_V5_DATA/Summer19UL18_RunB_V5_DATA_UncertaintySources_AK8PFPuppi_");
        textFileArAK8.push_back("../NanoCORE/Tools/jetcorr/data/Summer19UL18_RunC_V5_DATA/Summer19UL18_RunC_V5_DATA_UncertaintySources_AK8PFPuppi_");
        textFileArAK8.push_back("../NanoCORE/Tools/jetcorr/data/Summer19UL18_RunD_V5_DATA/Summer19UL18_RunD_V5_DATA_UncertaintySources_AK8PFPuppi_");
    }
    else if (yearType == 1) {
        //now do for UL17 with A to F
        textFileArAK8.push_back("../NanoCORE/Tools/jetcorr/data/Summer19UL17_RunA_V5_DATA/Summer19UL17_RunA_V5_DATA_UncertaintySources_AK8PFPuppi_");
        textFileArAK8.push_back("../NanoCORE/Tools/jetcorr/data/Summer19UL17_RunB_V5_DATA/Summer19UL17_RunB_V5_DATA_UncertaintySources_AK8PFPuppi_");
        textFileArAK8.push_back("../NanoCORE/Tools/jetcorr/data/Summer19UL17_RunC_V5_DATA/Summer19UL17_RunC_V5_DATA_UncertaintySources_AK8PFPuppi_");
        textFileArAK8.push_back("../NanoCORE/Tools/jetcorr/data/Summer19UL17_RunD_V5_DATA/Summer19UL17_RunD_V5_DATA_UncertaintySources_AK8PFPuppi_");
        textFileArAK8.push_back("../NanoCORE/Tools/jetcorr/data/Summer19UL17_RunE_V5_DATA/Summer19UL17_RunE_V5_DATA_UncertaintySources_AK8PFPuppi_");
        textFileArAK8.push_back("../NanoCORE/Tools/jetcorr/data/Summer19UL17_RunF_V5_DATA/Summer19UL17_RunF_V5_DATA_UncertaintySources_AK8PFPuppi_");
    }
    else if (yearType == 2) {
        //now do for UL16 with B to F
        textFileArAK8.push_back("../NanoCORE/Tools/jetcorr/data/Summer19UL16APV_RunBCD_V7_DATA/Summer19UL16APV_RunBCD_V7_DATA_UncertaintySources_AK8PFPuppi_");
        textFileArAK8.push_back("../NanoCORE/Tools/jetcorr/data/Summer19UL16_RunEF_V7_DATA/Summer19UL16_RunEF_V7_DATA_UncertaintySources_AK8PFPuppi_");
        textFileArAK8.push_back("../NanoCORE/Tools/jetcorr/data/Summer19UL16_RunFGH_V7_DATA/Summer19UL16_RunFGH_V7_DATA_UncertaintySources_AK8PFPuppi_");
    }

    std::vector<std::unique_ptr<JetCorrectionUncertainty>> jecUncAr;
    if (JECCorInd){
        for (UInt_t i = 0; i < textFileAr.size(); ++i){
            auto tmpJECUnc = std::make_unique<JetCorrectionUncertainty>(textFileAr[i]+corrTypeAr[JECCorInd]+".txt");
            jecUncAr.push_back(std::move(tmpJECUnc));
        }
    }
    //same for AK8 jets
    std::vector<std::unique_ptr<JetCorrectionUncertainty>> jecUncArAK8;
    if (AK8JECCorInd){
        for (UInt_t i = 0; i < textFileArAK8.size(); ++i){
            auto tmpJECUnc = std::make_unique<JetCorrectionUncertainty>(textFileArAK8[i]+corrTypeAr[JECCorInd]+".txt");
            jecUncArAK8.push_back(std::move(tmpJECUnc));
        }
    }


    

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

    //TREES FROM HLT FILE

    UInt_t nEv;
    UInt_t nEvPass;
    

    TTree *evNumTree = new TTree("evNumTree","evNumTree");

    evNumTree->Branch("nEv",&nEv,"nEv/i");
    evNumTree->Branch("nEvPass",&nEvPass,"nEvPass/i");

    UInt_t runL;
    UInt_t eventL;

    UInt_t datasetTypeL;

    //Run alphanumeric represented by int
    UInt_t runAlphaNumL;
    Bool_t APVL;
    Int_t JECCorIndL;
    Int_t AK8JECCorIndL;
    Int_t RochIndL;



    //Jets
    UInt_t nJetL;
    std::vector<Float_t> Jet_etaL;
    std::vector<Float_t> Jet_ptL;
    std::vector<Float_t> Jet_phiL;
    std::vector<Float_t> Jet_massL;
    std::vector<Int_t> Jet_jetIdL;
    std::vector<Float_t> Jet_btagDeepFlavBL;
    Float_t fixedGridRhoFastjetAllL;
    //Jets Corrected
    //std::vector<Float_t> Jet_etaCorrectedDownL;
    std::vector<Float_t> Jet_ptCorrectedDownL;
    //std::vector<Float_t> Jet_phiCorrectedDownL;
    //std::vector<Float_t> Jet_massCorrectedDownL;
    //Same but up
    //std::vector<Float_t> Jet_etaCorrectedUpL;
    std::vector<Float_t> Jet_ptCorrectedUpL;
    //std::vector<Float_t> Jet_phiCorrectedUpL;
    //std::vector<Float_t> Jet_massCorrectedUpL;


    //Fat jets

    UInt_t nFatJetL;
    std::vector<Float_t> FatJet_etaL;
    std::vector<Float_t> FatJet_ptL;
    std::vector<Float_t> FatJet_phiL;
    std::vector<Float_t> FatJet_massL;
    std::vector<Int_t> FatJet_jetIdL;
    std::vector<Float_t> FatJet_deepTag_HL;
    std::vector<Float_t> FatJet_deepTag_ZvsQCDL;
    std::vector<Float_t> FatJet_msoftdropL;
    std::vector<Float_t> FatJet_particleNet_massL;
    //Jets Corrected
    //std::vector<Float_t> FatJet_etaCorrectedDownL;
    std::vector<Float_t> FatJet_ptCorrectedDownL;
    //std::vector<Float_t> FatJet_phiCorrectedDownL;
    //std::vector<Float_t> FatJet_massCorrectedDownL;
    //Same but up
    //std::vector<Float_t> FatJet_etaCorrectedUpL;
    std::vector<Float_t> FatJet_ptCorrectedUpL;
    //std::vector<Float_t> FatJet_phiCorrectedUpL;
    //std::vector<Float_t> FatJet_massCorrectedUpL;

    //Electrons
    UInt_t nElectronL;
    std::vector<Float_t> Electron_etaL;
    std::vector<Float_t> Electron_massL;
    std::vector<Int_t> Electron_chargeL;
    std::vector<Float_t> Electron_phiL;
    std::vector<Float_t> Electron_ptL;
    std::vector<Float_t> Electron_dr03EcalRecHitSumEtL;
    std::vector<Float_t> Electron_dr03TkSumPtL;
    std::vector<Float_t> Electron_dr03HcalDepth1TowerSumEtL;
    std::vector<Float_t> Electron_pfRelIso03_allL;
    std::vector<Float_t> Electron_sip3dL;
    std::vector<Int_t> Electron_cutBasedL;
    std::vector<Bool_t> Electron_mvaFall17V2Iso_WP80L;
    std::vector<Bool_t> Electron_mvaFall17V2Iso_WP90L;
    std::vector<Bool_t> Electron_mvaFall17V2Iso_WPLL;
    std::vector<Bool_t> Electron_mvaFall17V2noIso_WP80L;
    std::vector<Bool_t> Electron_mvaFall17V2noIso_WP90L;
    std::vector<Bool_t> Electron_mvaFall17V2noIso_WPLL;

    std::vector<Float_t> Electron_dxyL;
    std::vector<Float_t> Electron_dzL;
    std::vector<Float_t> Electron_miniPFRelIso_allL;
    std::vector<Float_t> Electron_sieieL;
    std::vector<Float_t> Electron_hoeL;
    std::vector<Float_t> Electron_eInvMinusPInvL;
    std::vector<Bool_t> Electron_convVetoL;
    std::vector<UChar_t> Electron_lostHitsL;
    std::vector<Int_t> Electron_jetIdxL;
    std::vector<Float_t> Electron_jetRelIsoL;
    std::vector<Float_t> Electron_mvaTTHL;

    //Muons
    UInt_t nMuonL;
    std::vector<Float_t> Muon_etaL;
    std::vector<Float_t> Muon_massL;
    std::vector<Int_t> Muon_chargeL;
    std::vector<Float_t> Muon_phiL;
    std::vector<Float_t> Muon_ptL;
    std::vector<Float_t> Muon_pfRelIso03_allL;
    std::vector<Float_t> Muon_sip3dL;
    std::vector<Bool_t> Muon_tightIdL;
    std::vector<Bool_t> Muon_mediumIdL;
    std::vector<Bool_t> Muon_looseIdL;
    std::vector<Float_t> Muon_RochMomCorrectionsL;
    std::vector<Float_t> Muon_ptCorrectedL;

    std::vector<Float_t> Muon_dxyL;
    std::vector<Float_t> Muon_dzL;
    std::vector<Float_t> Muon_miniPFRelIso_allL;
    std::vector<Int_t> Muon_jetIdxL;
    std::vector<Float_t> Muon_jetRelIsoL;
    std::vector<Float_t> Muon_mvaTTHL;
    std::vector<Int_t> Muon_nTrackerLayersL;

    

    //ParticleNet
    std::vector<Float_t> FatJet_particleNet_HbbvsQCDL;
    std::vector<Float_t> FatJet_particleNet_ZvsQCDL;
    std::vector<Float_t> FatJet_particleNetMD_QCDL;
    std::vector<Float_t> FatJet_particleNetMD_XbbL;
    std::vector<Float_t> FatJet_particleNetMD_XccL;
    std::vector<Float_t> FatJet_particleNetMD_XqqL;


    
    
    


    TTree *FilteredEventsTree = new TTree("FilteredEventsTree", "FilteredEventsTree");

    FilteredEventsTree->Branch("runL",&runL,"runL/i");
    FilteredEventsTree->Branch("eventL",&eventL,"eventL/i");
    FilteredEventsTree->Branch("datasetTypeL",&datasetTypeL,"datasetTypeL/i");

    //Run alphanumeric represented by int
    FilteredEventsTree->Branch("runAlphaNumL",&runAlphaNumL,"runAlphaNumL/i");
    FilteredEventsTree->Branch("APVL",&APVL,"APVL/O");
    FilteredEventsTree->Branch("JECCorIndL",&JECCorIndL,"JECCorIndL/I");
    FilteredEventsTree->Branch("AK8JECCorIndL",&AK8JECCorIndL,"AK8JECCorIndL/I");
    FilteredEventsTree->Branch("RochIndL",&RochIndL,"RochIndL/I");

    //Jets    
    FilteredEventsTree->Branch("nJetL",&nJetL,"nJetL/i");
    FilteredEventsTree->Branch("Jet_etaL",&Jet_etaL);
    FilteredEventsTree->Branch("Jet_ptL",&Jet_ptL);
    FilteredEventsTree->Branch("Jet_phiL",&Jet_phiL);
    FilteredEventsTree->Branch("Jet_massL",&Jet_massL);
    FilteredEventsTree->Branch("Jet_jetIdL",&Jet_jetIdL);
    FilteredEventsTree->Branch("Jet_btagDeepFlavBL",&Jet_btagDeepFlavBL);
    FilteredEventsTree->Branch("fixedGridRhoFastjetAllL",&fixedGridRhoFastjetAllL,"fixedGridRhoFastjetAllL/F");
    //Jets Corrected
    //FilteredEventsTree->Branch("Jet_etaCorrectedDownL",&Jet_etaCorrectedDownL);
    FilteredEventsTree->Branch("Jet_ptCorrectedDownL",&Jet_ptCorrectedDownL);
    //FilteredEventsTree->Branch("Jet_phiCorrectedDownL",&Jet_phiCorrectedDownL);
    //FilteredEventsTree->Branch("Jet_massCorrectedDownL",&Jet_massCorrectedDownL);
    //Same but up
    //FilteredEventsTree->Branch("Jet_etaCorrectedUpL",&Jet_etaCorrectedUpL);
    FilteredEventsTree->Branch("Jet_ptCorrectedUpL",&Jet_ptCorrectedUpL);
    //FilteredEventsTree->Branch("Jet_phiCorrectedUpL",&Jet_phiCorrectedUpL);
    //FilteredEventsTree->Branch("Jet_massCorrectedUpL",&Jet_massCorrectedUpL);


    //Fat jets

    FilteredEventsTree->Branch("nFatJetL",&nFatJetL,"nFatJetL/i");
    FilteredEventsTree->Branch("FatJet_etaL",&FatJet_etaL);
    FilteredEventsTree->Branch("FatJet_ptL",&FatJet_ptL);
    FilteredEventsTree->Branch("FatJet_phiL",&FatJet_phiL);
    FilteredEventsTree->Branch("FatJet_massL",&FatJet_massL);
    FilteredEventsTree->Branch("FatJet_jetIdL",&FatJet_jetIdL);
    FilteredEventsTree->Branch("FatJet_deepTag_HL",&FatJet_deepTag_HL);
    FilteredEventsTree->Branch("FatJet_deepTag_ZvsQCDL",&FatJet_deepTag_ZvsQCDL);
    FilteredEventsTree->Branch("FatJet_msoftdropL",&FatJet_msoftdropL);
    FilteredEventsTree->Branch("FatJet_particleNet_massL", &FatJet_particleNet_massL);
    //Jets Corrected
    //FilteredEventsTree->Branch("FatJet_etaCorrectedDownL",&FatJet_etaCorrectedDownL);
    FilteredEventsTree->Branch("FatJet_ptCorrectedDownL",&FatJet_ptCorrectedDownL);
    //FilteredEventsTree->Branch("FatJet_phiCorrectedDownL",&FatJet_phiCorrectedDownL);
    //FilteredEventsTree->Branch("FatJet_massCorrectedDownL",&FatJet_massCorrectedDownL);
    //Same but up
    //FilteredEventsTree->Branch("FatJet_etaCorrectedUpL",&FatJet_etaCorrectedUpL);
    FilteredEventsTree->Branch("FatJet_ptCorrectedUpL",&FatJet_ptCorrectedUpL);
    //FilteredEventsTree->Branch("FatJet_phiCorrectedUpL",&FatJet_phiCorrectedUpL);
    //FilteredEventsTree->Branch("FatJet_massCorrectedUpL",&FatJet_massCorrectedUpL);


    //Electrons
    FilteredEventsTree->Branch("nElectronL",&nElectronL,"nElectronL/i");
    FilteredEventsTree->Branch("Electron_etaL",&Electron_etaL);
    FilteredEventsTree->Branch("Electron_massL",&Electron_massL);
    FilteredEventsTree->Branch("Electron_chargeL",&Electron_chargeL);
    FilteredEventsTree->Branch("Electron_phiL",&Electron_phiL);
    FilteredEventsTree->Branch("Electron_ptL",&Electron_ptL);
    FilteredEventsTree->Branch("Electron_dr03EcalRecHitSumEtL",&Electron_dr03EcalRecHitSumEtL);
    FilteredEventsTree->Branch("Electron_dr03TkSumPtL",&Electron_dr03TkSumPtL);
    FilteredEventsTree->Branch("Electron_dr03HcalDepth1TowerSumEtL",&Electron_dr03HcalDepth1TowerSumEtL);
    FilteredEventsTree->Branch("Electron_pfRelIso03_allL",&Electron_pfRelIso03_allL);
    FilteredEventsTree->Branch("Electron_sip3dL",&Electron_sip3dL);
    FilteredEventsTree->Branch("Electron_cutBasedL",&Electron_cutBasedL);
    FilteredEventsTree->Branch("Electron_mvaFall17V2Iso_WP80L",&Electron_mvaFall17V2Iso_WP80L);
    FilteredEventsTree->Branch("Electron_mvaFall17V2Iso_WP90L",&Electron_mvaFall17V2Iso_WP90L);
    FilteredEventsTree->Branch("Electron_mvaFall17V2Iso_WPLL",&Electron_mvaFall17V2Iso_WPLL);
    FilteredEventsTree->Branch("Electron_mvaFall17V2noIso_WP80L",&Electron_mvaFall17V2noIso_WP80L);
    FilteredEventsTree->Branch("Electron_mvaFall17V2noIso_WP90L",&Electron_mvaFall17V2noIso_WP90L);
    FilteredEventsTree->Branch("Electron_mvaFall17V2noIso_WPLL",&Electron_mvaFall17V2noIso_WPLL);


    //Muons
    FilteredEventsTree->Branch("nMuonL",&nMuonL,"nMuonL/i");
    FilteredEventsTree->Branch("Muon_etaL",&Muon_etaL);
    FilteredEventsTree->Branch("Muon_massL",&Muon_massL);
    FilteredEventsTree->Branch("Muon_chargeL",&Muon_chargeL);
    FilteredEventsTree->Branch("Muon_phiL",&Muon_phiL);
    FilteredEventsTree->Branch("Muon_ptL",&Muon_ptL);
    FilteredEventsTree->Branch("Muon_pfRelIso03_allL",&Muon_pfRelIso03_allL);
    FilteredEventsTree->Branch("Muon_sip3dL",&Muon_sip3dL);
    FilteredEventsTree->Branch("Muon_tightIdL",&Muon_tightIdL);
    FilteredEventsTree->Branch("Muon_mediumIdL",&Muon_mediumIdL);
    FilteredEventsTree->Branch("Muon_looseIdL",&Muon_looseIdL);
    FilteredEventsTree->Branch("Muon_RochMomCorrectionsL",&Muon_RochMomCorrectionsL);
    FilteredEventsTree->Branch("Muon_ptCorrectedL",&Muon_ptCorrectedL);
    


    //For LepID
    FilteredEventsTree->Branch("Electron_dxyL",&Electron_dxyL);
    FilteredEventsTree->Branch("Electron_dzL",&Electron_dzL);
    FilteredEventsTree->Branch("Electron_miniPFRelIso_allL",&Electron_miniPFRelIso_allL);
    FilteredEventsTree->Branch("Electron_sieieL",&Electron_sieieL);
    FilteredEventsTree->Branch("Electron_hoeL",&Electron_hoeL);
    FilteredEventsTree->Branch("Electron_eInvMinusPInvL",&Electron_eInvMinusPInvL);
    FilteredEventsTree->Branch("Electron_convVetoL",&Electron_convVetoL);
    FilteredEventsTree->Branch("Electron_lostHitsL",&Electron_lostHitsL);
    FilteredEventsTree->Branch("Electron_jetIdxL",&Electron_jetIdxL);
    FilteredEventsTree->Branch("Electron_jetRelIsoL",&Electron_jetRelIsoL);
    FilteredEventsTree->Branch("Electron_mvaTTHL",&Electron_mvaTTHL);

    FilteredEventsTree->Branch("Muon_dxyL",&Muon_dxyL);
    FilteredEventsTree->Branch("Muon_dzL",&Muon_dzL);
    FilteredEventsTree->Branch("Muon_miniPFRelIso_allL",&Muon_miniPFRelIso_allL);
    FilteredEventsTree->Branch("Muon_jetIdxL",&Muon_jetIdxL);
    FilteredEventsTree->Branch("Muon_jetRelIsoL",&Muon_jetRelIsoL);
    FilteredEventsTree->Branch("Muon_mvaTTHL",&Muon_mvaTTHL);
    FilteredEventsTree->Branch("Muon_nTrackerLayersL",&Muon_nTrackerLayersL);

    //ParticleNet
    FilteredEventsTree->Branch("FatJet_particleNet_HbbvsQCDL",&FatJet_particleNet_HbbvsQCDL);
    FilteredEventsTree->Branch("FatJet_particleNet_ZvsQCDL",&FatJet_particleNet_ZvsQCDL);

    FilteredEventsTree->Branch("FatJet_particleNetMD_QCDL", &FatJet_particleNetMD_QCDL);
    FilteredEventsTree->Branch("FatJet_particleNetMD_XbbL", &FatJet_particleNetMD_XbbL);
    FilteredEventsTree->Branch("FatJet_particleNetMD_XccL", &FatJet_particleNetMD_XccL);
    FilteredEventsTree->Branch("FatJet_particleNetMD_XqqL", &FatJet_particleNetMD_XqqL);


    //Rochester corrections optional tracking variables
    //add doubles for the min and max results
    double minRes = 100000;
    double maxRes = -100000;
    //add variables to hold muon pt, etc, for min and max results
    double minPt = 0;
    double maxPt = 0;
    double minEta = 0;
    double maxEta = 0;
    double minPhi = 0;
    double maxPhi = 0;
    Int_t minCharge = 0;
    Int_t maxCharge = 0;
    Int_t minEvCount = 0;
    Int_t maxEvCount = 0;
    Int_t mini = 0;
    Int_t maxi = 0;
    //add count for total muons run over
    UInt_t muCount = 0;
    //add count for how many events fall outside the hist range
    UInt_t outOfRange = 0;

    TH1D* rochesterCorrHist = new TH1D("rochesterCorrHist","rochesterCorrHist",1000,0.9,1.1);

    

    std::cout << "Going into file loop.\n";

    for (UInt_t k=0; k<fileAr.size(); k++){
        if (endAfter && evCount > NToEnd) break;
        if (debug) std::cout<<"File:    "<<fileAr[k]<<"\n";
        //Open the file, get the Events tree
        TFile* tmpfile = TFile::Open(fileAr[k].c_str());
        //outFile->cd();
        TTreeReader myEventsReader("FilteredEventsTree", tmpfile);

        TTreeReaderValue<UInt_t> run(myEventsReader, "runL");
        TTreeReaderValue<UInt_t> event(myEventsReader, "eventL");

        TTreeReaderValue<UInt_t> runAlphaNum(myEventsReader, "runAlphaNumL");
        TTreeReaderValue<Bool_t> APV(myEventsReader, "APV");

        //jets

        TTreeReaderValue<UInt_t> nJet(myEventsReader, "nJetL");
        TTreeReaderArray<Float_t> Jet_eta(myEventsReader, "Jet_etaL");
        TTreeReaderArray<Float_t> Jet_pt(myEventsReader, "Jet_ptL");
        TTreeReaderArray<Float_t> Jet_phi(myEventsReader, "Jet_phiL");
        TTreeReaderArray<Float_t> Jet_mass(myEventsReader, "Jet_massL");
        TTreeReaderArray<Int_t> Jet_jetId(myEventsReader, "Jet_jetIdL");
        TTreeReaderArray<Float_t> Jet_btagDeepFlavB(myEventsReader,"Jet_btagDeepFlavBL");
        TTreeReaderValue<Float_t> fixedGridRhoFastjetAll(myEventsReader, "fixedGridRhoFastjetAllL");

        //Fat jets

        TTreeReaderValue<UInt_t> nFatJet(myEventsReader, "nFatJetL");
        TTreeReaderArray<Float_t> FatJet_eta(myEventsReader, "FatJet_etaL");
        TTreeReaderArray<Float_t> FatJet_pt(myEventsReader, "FatJet_ptL");
        TTreeReaderArray<Float_t> FatJet_phi(myEventsReader, "FatJet_phiL");
        TTreeReaderArray<Float_t> FatJet_mass(myEventsReader, "FatJet_massL");
        TTreeReaderArray<Int_t> FatJet_jetId(myEventsReader, "FatJet_jetIdL");
        TTreeReaderArray<Float_t> FatJet_deepTag_H(myEventsReader, "FatJet_deepTag_HL");
        TTreeReaderArray<Float_t> FatJet_deepTag_ZvsQCD(myEventsReader, "FatJet_deepTag_ZvsQCDL");
        TTreeReaderArray<Float_t> FatJet_msoftdrop(myEventsReader, "FatJet_msoftdropL");

        TTreeReaderArray<Float_t> FatJet_particleNet_mass(myEventsReader, "FatJet_particleNet_massL");


        //Electrons
        TTreeReaderValue<UInt_t> nElectron(myEventsReader, "nElectronL");
        TTreeReaderArray<Float_t> Electron_eta(myEventsReader, "Electron_etaL");
        TTreeReaderArray<Float_t> Electron_mass(myEventsReader, "Electron_massL");
        TTreeReaderArray<Int_t> Electron_charge(myEventsReader, "Electron_chargeL");
        TTreeReaderArray<Float_t> Electron_phi(myEventsReader, "Electron_phiL");
        TTreeReaderArray<Float_t> Electron_pt(myEventsReader, "Electron_ptL");
        TTreeReaderArray<Float_t> Electron_dr03EcalRecHitSumEt(myEventsReader, "Electron_dr03EcalRecHitSumEtL");
        TTreeReaderArray<Float_t> Electron_dr03TkSumPt(myEventsReader, "Electron_dr03TkSumPtL");
        TTreeReaderArray<Float_t> Electron_dr03HcalDepth1TowerSumEt(myEventsReader, "Electron_dr03HcalDepth1TowerSumEtL");
        TTreeReaderArray<Float_t> Electron_pfRelIso03_all(myEventsReader, "Electron_pfRelIso03_allL");
        TTreeReaderArray<Float_t> Electron_sip3d(myEventsReader, "Electron_sip3dL");
        TTreeReaderArray<Int_t> Electron_cutBased(myEventsReader, "Electron_cutBasedL");
        TTreeReaderArray<Bool_t> Electron_mvaFall17V2Iso_WP80(myEventsReader, "Electron_mvaFall17V2Iso_WP80L");
        TTreeReaderArray<Bool_t> Electron_mvaFall17V2Iso_WP90(myEventsReader, "Electron_mvaFall17V2Iso_WP90L");
        TTreeReaderArray<Bool_t> Electron_mvaFall17V2Iso_WPL(myEventsReader, "Electron_mvaFall17V2Iso_WPLL");
        TTreeReaderArray<Bool_t> Electron_mvaFall17V2noIso_WP80(myEventsReader, "Electron_mvaFall17V2noIso_WP80L");
        TTreeReaderArray<Bool_t> Electron_mvaFall17V2noIso_WP90(myEventsReader, "Electron_mvaFall17V2noIso_WP90L");
        TTreeReaderArray<Bool_t> Electron_mvaFall17V2noIso_WPL(myEventsReader, "Electron_mvaFall17V2noIso_WPLL");

        //Muons
        TTreeReaderValue<UInt_t> nMuon(myEventsReader, "nMuonL");
        TTreeReaderArray<Float_t> Muon_eta(myEventsReader, "Muon_etaL");
        TTreeReaderArray<Float_t> Muon_mass(myEventsReader, "Muon_massL");
        TTreeReaderArray<Int_t> Muon_charge(myEventsReader, "Muon_chargeL");
        TTreeReaderArray<Float_t> Muon_phi(myEventsReader, "Muon_phiL");
        TTreeReaderArray<Float_t> Muon_pt(myEventsReader, "Muon_ptL");
        TTreeReaderArray<Float_t> Muon_pfRelIso03_all(myEventsReader, "Muon_pfRelIso03_allL");
        TTreeReaderArray<Float_t> Muon_sip3d(myEventsReader, "Muon_sip3dL");
        TTreeReaderArray<Bool_t> Muon_tightId(myEventsReader, "Muon_tightIdL");
        TTreeReaderArray<Bool_t> Muon_mediumId(myEventsReader, "Muon_mediumIdL");
        TTreeReaderArray<Bool_t> Muon_looseId(myEventsReader, "Muon_looseIdL");
        TTreeReaderArray<Int_t> Muon_nTrackerLayers(myEventsReader, "Muon_nTrackerLayersL");




        //For LepID
        TTreeReaderArray<Float_t> Electron_dxy(myEventsReader, "Electron_dxyL");
        TTreeReaderArray<Float_t> Electron_dz(myEventsReader, "Electron_dzL");
        TTreeReaderArray<Float_t> Electron_miniPFRelIso_all(myEventsReader, "Electron_miniPFRelIso_allL");
        TTreeReaderArray<Float_t> Electron_sieie(myEventsReader, "Electron_sieieL");
        TTreeReaderArray<Float_t> Electron_hoe(myEventsReader, "Electron_hoeL");
        TTreeReaderArray<Float_t> Electron_eInvMinusPInv(myEventsReader, "Electron_eInvMinusPInvL");
        TTreeReaderArray<Bool_t> Electron_convVeto(myEventsReader, "Electron_convVetoL");
        TTreeReaderArray<UChar_t> Electron_lostHits(myEventsReader, "Electron_lostHitsL");
        TTreeReaderArray<Int_t> Electron_jetIdx(myEventsReader, "Electron_jetIdxL");
        TTreeReaderArray<Float_t> Electron_jetRelIso(myEventsReader, "Electron_jetRelIsoL");
        TTreeReaderArray<Float_t> Electron_mvaTTH(myEventsReader, "Electron_mvaTTHL");

        TTreeReaderArray<Float_t> Muon_dxy(myEventsReader, "Muon_dxyL");
        TTreeReaderArray<Float_t> Muon_dz(myEventsReader, "Muon_dzL");
        TTreeReaderArray<Float_t> Muon_miniPFRelIso_all(myEventsReader, "Muon_miniPFRelIso_allL");
        TTreeReaderArray<Int_t> Muon_jetIdx(myEventsReader, "Muon_jetIdxL");
        TTreeReaderArray<Float_t> Muon_jetRelIso(myEventsReader, "Muon_jetRelIsoL");
        TTreeReaderArray<Float_t> Muon_mvaTTH(myEventsReader, "Muon_mvaTTHL");

        

        //ParticleNet
        TTreeReaderArray<Float_t> FatJet_particleNet_HbbvsQCD(myEventsReader, "FatJet_particleNet_HbbvsQCDL");
        TTreeReaderArray<Float_t> FatJet_particleNet_ZvsQCD(myEventsReader, "FatJet_particleNet_ZvsQCDL");

        TTreeReaderArray<Float_t> FatJet_particleNetMD_QCD(myEventsReader, "FatJet_particleNetMD_QCDL");
        TTreeReaderArray<Float_t> FatJet_particleNetMD_Xbb(myEventsReader, "FatJet_particleNetMD_XbbL");
        TTreeReaderArray<Float_t> FatJet_particleNetMD_Xcc(myEventsReader, "FatJet_particleNetMD_XccL");
        TTreeReaderArray<Float_t> FatJet_particleNetMD_Xqq(myEventsReader, "FatJet_particleNetMD_XqqL");


        TTreeReader myEvNumReader("evNumTree", tmpfile);
        TTreeReaderValue<UInt_t> nEvHLT(myEvNumReader, "nEv");
        TTreeReaderValue<UInt_t> nEvPassHLT(myEvNumReader, "nEvPass");

        
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


            std::vector<Float_t> rochMomCorrections;
            if (RochInd > 0){

                //Loop through muons and calculate rochester correction
                for (int i = 0; i < *nMuon; i++){
                    muCount += 1;
                    double mcSF;
                    int charge = Muon_charge[i];
                    float pt = Muon_pt[i];
                    float eta = Muon_eta[i];
                    float phi = Muon_phi[i];
                    
                    mcSF = rc.kScaleDT(charge, pt, eta, phi, RochInd-1, 0);
                    //Fill histogram
                    rochesterCorrHist->Fill(mcSF);
                    //check if outside hist range
                    if (mcSF < 0.9 || mcSF > 1.1) outOfRange += 1;
                    //check if min or max
                    if (mcSF < minRes) {
                        minRes = mcSF;
                        minPt = pt;
                        minEta = eta;
                        minPhi = phi;
                        minCharge = charge;
                        minEvCount = evCount;
                        mini = i;
                        
                    }
                    if (mcSF > maxRes) {
                        maxRes = mcSF;
                        maxPt = pt;
                        maxEta = eta;
                        maxPhi = phi;
                        maxCharge = charge;
                        maxEvCount = evCount;
                        maxi = i;
                    }
                    //Add scale to scale vector
                    rochMomCorrections.push_back(mcSF);
                }
            }
            else {
                //If not, just transfer the pt unchanged
                for (int i = 0; i < *nMuon; i++){
                    rochMomCorrections.push_back(1.);
                }
            }

            //initialize a vector of Pt for the jets
            std::vector<Float_t> jetCorPtUpVec;
            std::vector<Float_t> jetCorPtDownVec;

            //If JECCorInd > 0, then apply JECs
            if (JECCorInd > 0){
                //Loop through jets and apply JECs
                for (int i = 0; i < *nJet; i++){
                    //Get the jet pt, eta, phi, and mass
                    float pt = Jet_pt[i];
                    float eta = Jet_eta[i];
                    float phi = Jet_phi[i];
                    float mass = Jet_mass[i];
                    //Get ind for JEC from runAlphaNum and APV and year
                    int jecInd;
                    if (yearType < 2) {
                        jecInd = *runAlphaNum;
                    }
                    else if (*APV) {
                        if (*runAlphaNum < 5){
                            jecInd = 0;
                        }
                        else {
                            jecInd = 1;
                        }
                    }
                    else {
                        jecInd = 2;
                    }
                    //Get the JEC uncertainty
                    jecUncAr[jecInd]->setJetPt(pt);
                    jecUncAr[jecInd]->setJetEta(eta);
                    //down first
                    double unc = jecUncAr[jecInd]->getUncertainty(false);
                    double JEC = 1. - unc;
                    float tmpPt = pt * JEC;
                    //mass *= JEC;
                    jetCorPtDownVec.push_back(pt);
                    //Now Up
                    jecUncAr[jecInd]->setJetPt(pt);
                    jecUncAr[jecInd]->setJetEta(eta);
                    unc = jecUncAr[jecInd]->getUncertainty(true);
                    JEC = 1. + unc;
                    tmpPt = pt * JEC;
                    //mass *= JEC;
                    jetCorPtUpVec.push_back(tmpPt);
                    
                }
            }
            else {
                //If not, just transfer the pt unchanged
                for (int i = 0; i < *nJet; i++){
                    float pt = Jet_pt[i];
                    jetCorPtUpVec.push_back(pt);
                    jetCorPtDownVec.push_back(pt);
                }
            }

            //initialize a vector of Pt for the AK8 jets
            std::vector<Float_t> AK8jetCorPtUpVec;
            std::vector<Float_t> AK8jetCorPtDownVec;
            //If JECCorInd > 0, then apply JECs
            if (AK8JECCorInd > 0){
                //Loop through jets and apply JECs
                for (int i = 0; i < *nFatJet; i++){
                    //Get the jet pt, eta, phi, and mass
                    float pt = FatJet_pt[i];
                    float eta = FatJet_eta[i];
                    float phi = FatJet_phi[i];
                    float mass = FatJet_mass[i];
                    //Get ind for JEC from runAlphaNum and APV and year
                    int jecInd;
                    if (yearType < 2) {
                        jecInd = *runAlphaNum;
                    }
                    else if (*APV) {
                        if (*runAlphaNum < 5){
                            jecInd = 0;
                        }
                        else {
                            jecInd = 1;
                        }
                    }
                    else {
                        jecInd = 2;
                    }
                    //Get the JEC uncertainty
                    jecUncArAK8[jecInd]->setJetPt(pt);
                    jecUncArAK8[jecInd]->setJetEta(eta);
                    //down first
                    double unc = jecUncArAK8[jecInd]->getUncertainty(false);
                    double JEC = 1. - unc;
                    float tmpPt = pt * JEC;
                    //mass *= JEC;
                    AK8jetCorPtDownVec.push_back(pt);
                    //Now Up
                    jecUncArAK8[jecInd]->setJetPt(pt);
                    jecUncArAK8[jecInd]->setJetEta(eta);
                    unc = jecUncArAK8[jecInd]->getUncertainty(true);
                    JEC = 1. + unc;
                    tmpPt = pt * JEC;
                    //mass *= JEC;
                    AK8jetCorPtUpVec.push_back(tmpPt);
                }
            }
            else {
                //If not, just transfer the pt unchanged
                for (int i = 0; i < *nFatJet; i++){
                    float pt = FatJet_pt[i];
                    AK8jetCorPtUpVec.push_back(pt);
                    AK8jetCorPtDownVec.push_back(pt);
                }
            }


            //Fill in all branches of TTree

            runL = *run;
            eventL = *event;

            runAlphaNumL = *runAlphaNum;
            APVL = *APV;
            JECCorIndL = JECCorInd;
            AK8JECCorIndL = AK8JECCorInd;
            RochIndL = RochInd;
            datasetTypeL = datasetType;
            //std::cout << evRunOver-1 << "passed\n";
            if (debug){
                std::cout <<"Filling Jets\n";
            }
            nJetL = *nJet;
            for (UInt_t nJetItr=0; nJetItr<nJetL;nJetItr++){
                Jet_etaL.push_back(Jet_eta[nJetItr]);
                Jet_ptL.push_back(Jet_pt[nJetItr]);
                Jet_phiL.push_back(Jet_phi[nJetItr]);
                Jet_massL.push_back(Jet_mass[nJetItr]);
                Jet_jetIdL.push_back(Jet_jetId[nJetItr]);
                Jet_btagDeepFlavBL.push_back(Jet_btagDeepFlavB[nJetItr]);
                Jet_ptCorrectedDownL.push_back(jetCorPtDownVec[nJetItr]);
                Jet_ptCorrectedUpL.push_back(jetCorPtUpVec[nJetItr]);
            }
            fixedGridRhoFastjetAllL = *fixedGridRhoFastjetAll;

            //Fat jets
            if (debug){
                std::cout <<"Filling FJs\n";
            }
            nFatJetL = *nFatJet;
            for (UInt_t nFatJetItr=0; nFatJetItr<nFatJetL;nFatJetItr++){
                FatJet_etaL.push_back(FatJet_eta[nFatJetItr]);
                FatJet_ptL.push_back(FatJet_pt[nFatJetItr]);
                FatJet_phiL.push_back(FatJet_phi[nFatJetItr]);
                FatJet_massL.push_back(FatJet_mass[nFatJetItr]);
                FatJet_jetIdL.push_back(FatJet_jetId[nFatJetItr]);
                FatJet_deepTag_HL.push_back(FatJet_deepTag_H[nFatJetItr]);
                FatJet_deepTag_ZvsQCDL.push_back(FatJet_deepTag_ZvsQCD[nFatJetItr]);
                FatJet_particleNet_HbbvsQCDL.push_back(FatJet_particleNet_HbbvsQCD[nFatJetItr]);
                FatJet_particleNet_ZvsQCDL.push_back(FatJet_particleNet_ZvsQCD[nFatJetItr]);
                FatJet_particleNetMD_QCDL.push_back(FatJet_particleNetMD_QCD[nFatJetItr]);
                FatJet_particleNetMD_XbbL.push_back(FatJet_particleNetMD_Xbb[nFatJetItr]);
                FatJet_particleNetMD_XccL.push_back(FatJet_particleNetMD_Xcc[nFatJetItr]);
                FatJet_particleNetMD_XqqL.push_back(FatJet_particleNetMD_Xqq[nFatJetItr]);
                FatJet_msoftdropL.push_back(FatJet_msoftdrop[nFatJetItr]);
                FatJet_particleNet_massL.push_back(FatJet_particleNet_mass[nFatJetItr]);
                FatJet_ptCorrectedDownL.push_back(AK8jetCorPtDownVec[nFatJetItr]);
                FatJet_ptCorrectedUpL.push_back(AK8jetCorPtUpVec[nFatJetItr]);
            }

            //Electrons
            if (debug){
                std::cout <<"Filling Electrons\n";
            }
            nElectronL = *nElectron;
            for (UInt_t nElectronItr=0; nElectronItr<nElectronL;nElectronItr++){
                Electron_etaL.push_back(Electron_eta[nElectronItr]);
                Electron_massL.push_back(Electron_mass[nElectronItr]);
                Electron_chargeL.push_back(Electron_charge[nElectronItr]);
                Electron_phiL.push_back(Electron_phi[nElectronItr]);
                Electron_ptL.push_back(Electron_pt[nElectronItr]);
                Electron_dr03EcalRecHitSumEtL.push_back(Electron_dr03EcalRecHitSumEt[nElectronItr]);
                Electron_dr03TkSumPtL.push_back(Electron_dr03TkSumPt[nElectronItr]);
                Electron_dr03HcalDepth1TowerSumEtL.push_back(Electron_dr03HcalDepth1TowerSumEt[nElectronItr]);
                Electron_pfRelIso03_allL.push_back(Electron_pfRelIso03_all[nElectronItr]);
                Electron_sip3dL.push_back(Electron_sip3d[nElectronItr]);
                Electron_cutBasedL.push_back(Electron_cutBased[nElectronItr]);
                Electron_mvaFall17V2Iso_WP80L.push_back(Electron_mvaFall17V2Iso_WP80[nElectronItr]);
                Electron_mvaFall17V2Iso_WP90L.push_back(Electron_mvaFall17V2Iso_WP90[nElectronItr]);
                Electron_mvaFall17V2Iso_WPLL.push_back(Electron_mvaFall17V2Iso_WPL[nElectronItr]);
                Electron_mvaFall17V2noIso_WP80L.push_back(Electron_mvaFall17V2noIso_WP80[nElectronItr]);
                Electron_mvaFall17V2noIso_WP90L.push_back(Electron_mvaFall17V2noIso_WP90[nElectronItr]);
                Electron_mvaFall17V2noIso_WPLL.push_back(Electron_mvaFall17V2noIso_WPL[nElectronItr]);

                Electron_dxyL.push_back(Electron_dxy[nElectronItr]);
                Electron_dzL.push_back(Electron_dz[nElectronItr]);
                Electron_miniPFRelIso_allL.push_back(Electron_miniPFRelIso_all[nElectronItr]);
                Electron_sieieL.push_back(Electron_sieie[nElectronItr]);
                Electron_hoeL.push_back(Electron_hoe[nElectronItr]);
                Electron_eInvMinusPInvL.push_back(Electron_eInvMinusPInv[nElectronItr]);
                Electron_convVetoL.push_back(Electron_convVeto[nElectronItr]);
                Electron_lostHitsL.push_back(Electron_lostHits[nElectronItr]);
                Electron_jetIdxL.push_back(Electron_jetIdx[nElectronItr]);
                Electron_jetRelIsoL.push_back(Electron_jetRelIso[nElectronItr]);
                Electron_mvaTTHL.push_back(Electron_mvaTTH[nElectronItr]);
                



            }

            //Muons
            nMuonL = *nMuon;
            for (UInt_t nMuonItr=0; nMuonItr<nMuonL;nMuonItr++){
                Muon_etaL.push_back(Muon_eta[nMuonItr]);
                Muon_massL.push_back(Muon_mass[nMuonItr]);
                Muon_chargeL.push_back(Muon_charge[nMuonItr]);
                Muon_phiL.push_back(Muon_phi[nMuonItr]);
                Muon_ptL.push_back(Muon_pt[nMuonItr]);
                Muon_pfRelIso03_allL.push_back(Muon_pfRelIso03_all[nMuonItr]);
                Muon_sip3dL.push_back(Muon_sip3d[nMuonItr]);
                Muon_tightIdL.push_back(Muon_tightId[nMuonItr]);
                Muon_mediumIdL.push_back(Muon_mediumId[nMuonItr]);
                Muon_looseIdL.push_back(Muon_looseId[nMuonItr]);
                Muon_RochMomCorrectionsL.push_back(rochMomCorrections[nMuonItr]);
                Muon_ptCorrectedL.push_back(Muon_pt[nMuonItr]*rochMomCorrections[nMuonItr]);

                Muon_dxyL.push_back(Muon_dxy[nMuonItr]);
                Muon_dzL.push_back(Muon_dz[nMuonItr]);
                Muon_miniPFRelIso_allL.push_back(Muon_miniPFRelIso_all[nMuonItr]);
                Muon_jetIdxL.push_back(Muon_jetIdx[nMuonItr]);
                Muon_jetRelIsoL.push_back(Muon_jetRelIso[nMuonItr]);
                Muon_mvaTTHL.push_back(Muon_mvaTTH[nMuonItr]);
                Muon_nTrackerLayersL.push_back(Muon_nTrackerLayers[nMuonItr]);
            }

            fixedGridRhoFastjetAllL = *fixedGridRhoFastjetAll;

            FilteredEventsTree->Fill();

            Jet_etaL.clear();
            Jet_ptL.clear();
            Jet_phiL.clear();
            Jet_massL.clear();
            Jet_jetIdL.clear();
            Jet_btagDeepFlavBL.clear();
            Jet_ptCorrectedDownL.clear();
            Jet_ptCorrectedUpL.clear();

            FatJet_etaL.clear();
            FatJet_ptL.clear();
            FatJet_phiL.clear();
            FatJet_massL.clear();
            FatJet_jetIdL.clear();
            FatJet_deepTag_HL.clear();
            FatJet_deepTag_ZvsQCDL.clear();
            FatJet_msoftdropL.clear();
            FatJet_particleNet_massL.clear();
            FatJet_ptCorrectedDownL.clear();
            FatJet_ptCorrectedUpL.clear();
            

            Electron_etaL.clear();
            Electron_massL.clear();
            Electron_chargeL.clear();
            Electron_phiL.clear();
            Electron_ptL.clear();
            Electron_dr03EcalRecHitSumEtL.clear();
            Electron_dr03TkSumPtL.clear();
            Electron_dr03HcalDepth1TowerSumEtL.clear();
            Electron_pfRelIso03_allL.clear();
            Electron_sip3dL.clear();
            Electron_cutBasedL.clear();
            Electron_mvaFall17V2Iso_WP80L.clear();
            Electron_mvaFall17V2Iso_WP90L.clear();
            Electron_mvaFall17V2Iso_WPLL.clear();
            Electron_mvaFall17V2noIso_WP80L.clear();
            Electron_mvaFall17V2noIso_WP90L.clear();
            Electron_mvaFall17V2noIso_WPLL.clear();

            Electron_dxyL.clear();
            Electron_dzL.clear();
            Electron_miniPFRelIso_allL.clear();
            Electron_sieieL.clear();
            Electron_hoeL.clear();
            Electron_eInvMinusPInvL.clear();
            Electron_convVetoL.clear();
            Electron_lostHitsL.clear();
            Electron_jetIdxL.clear();
            Electron_jetRelIsoL.clear();
            Electron_mvaTTHL.clear();

            Muon_dxyL.clear();
            Muon_dzL.clear();
            Muon_miniPFRelIso_allL.clear();
            Muon_jetIdxL.clear();
            Muon_jetRelIsoL.clear();
            Muon_mvaTTHL.clear();

            
            

            Muon_etaL.clear();
            Muon_massL.clear();
            Muon_chargeL.clear();
            Muon_phiL.clear();
            Muon_ptL.clear();
            Muon_pfRelIso03_allL.clear();
            Muon_sip3dL.clear();
            Muon_tightIdL.clear();
            Muon_mediumIdL.clear();
            Muon_looseIdL.clear();
            Muon_nTrackerLayersL.clear();
            Muon_RochMomCorrectionsL.clear();
            Muon_ptCorrectedL.clear();

            FatJet_particleNet_HbbvsQCDL.clear();
            FatJet_particleNet_ZvsQCDL.clear();

            FatJet_particleNetMD_QCDL.clear();
            FatJet_particleNetMD_XbbL.clear();
            FatJet_particleNetMD_XccL.clear();
            FatJet_particleNetMD_XqqL.clear();


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
    std::cout << "UInt_t " << saveName << "evRunOver = " << evRunOver << "\n";
    std::cout << "------------------------\n";

    //print muon count
    std::cout << "MuCount: " << muCount << "\n";
    //print out of range count
    std::cout << "Out of range: " << outOfRange << "\n";
    //print min/max
    std::cout << "Min: " << minRes << "\n";
    std::cout << "Max: " << maxRes << "\n";
    //print all min variables without endline
    std::cout << "MinPt\tMinEta\tMinPhi\tMinQ\tMinEv\tMini\n";
    std::cout << std::setprecision(2) << minPt << "\t" << minEta << "\t" << minPhi << "\t" << minCharge << "\t" << minEvCount << "\t" << mini << "\n";

    //print all max variables without endline
    std::cout << "MaxPt\tMaxEta\tMaxPhi\tMaxQ\tMaxEv\tMaxi\n";
    std::cout << std::setprecision(2) << maxPt << "\t" << maxEta << "\t" << maxPhi << "\t" << maxCharge << "\t" << maxEvCount << "\t" << maxi << "\n";


    outFile->cd();
    evNumTree->Write("",TObject::kOverwrite);
    FilteredEventsTree->Write("",TObject::kOverwrite);

    outFile->Close();


}