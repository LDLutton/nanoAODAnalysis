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
#include "../NanoCORE/Tools/jetcorr/JetResolutionUncertainty.h"
#include "../NanoCORE/Tools/jetcorr/JetCorrectionUncertainty.h"




////////////////////////////////START OF MAIN FUNCTION////////////////////////////////
////////////////////////////////START OF MAIN FUNCTION////////////////////////////////
////////////////////////////////START OF MAIN FUNCTION////////////////////////////////
////////////////////////////////START OF MAIN FUNCTION////////////////////////////////
double massScale(double mass, double scaleVal=1.05) { return scaleVal*mass; }
double massSmear(double mass, unsigned long lumi, unsigned long event, double sigma=0.1) 
{
    TRandom3 rnd((lumi << 10) + event);
    return rnd.Gaus(1, sigma)*mass; 
}
//Script for calculating the JER, and Rochester corrections for the HLT output files
//Output should be the same but with additional branches for the corrections and efficiencies
//Apply JER before BTagging Efficencies
//Input should be the dataset string, then an integer for each correction/efficiency to be calculated
void calc042024JERRoch(string datasetString){
    // Open the file. Note that the name of your file outside this class
    // will probably NOT be experiment.root.
    std::cout << "start Analysis\n";
    clock_t startt = clock();


    RoccoR  rc("../RoccoR2018UL.txt"); 

    //Will run over all files put into fileAr



    std::vector<std::string> fileAr;
    string NoSLString = "";
    if (!useSingleLepHLT){
        NoSLString = "_NoSLHLT";
    }


    std::string saveName;
    bool isBackground;

    if (datasetString == "testRun") testRun = true;
    if (datasetString == "SDC2V2MCZZHReweightTrimmed") SDC2V2MCZZHReweightTrimmed = true;
    if (datasetString == "SDC2V2MCZZH17ReweightTrimmed") SDC2V2MCZZH17ReweightTrimmed = true;
    if (datasetString == "SDC2V2MCZZH16ReweightTrimmed") SDC2V2MCZZH16ReweightTrimmed = true;
    if (datasetString == "SDC2V2MCZZH16APVReweightTrimmed") SDC2V2MCZZH16APVReweightTrimmed = true;
    if (datasetString == "SDC2V2MCWZHReweightTrimmed") SDC2V2MCWZHReweightTrimmed = true;
    if (datasetString == "SDC2V2MCWZH17ReweightTrimmed") SDC2V2MCWZH17ReweightTrimmed = true;
    if (datasetString == "SDC2V2MCWZH16ReweightTrimmed") SDC2V2MCWZH16ReweightTrimmed = true;
    if (datasetString == "SDC2V2MCWZH16APVReweightTrimmed") SDC2V2MCWZH16APVReweightTrimmed = true;

    if (datasetString == "SDC2V2MCWWHSSReweightTrimmed") SDC2V2MCWWHSSReweightTrimmed = true;
    if (datasetString == "SDC2V2MCWWHSS17ReweightTrimmed") SDC2V2MCWWHSS17ReweightTrimmed = true;
    if (datasetString == "SDC2V2MCWWHSS16ReweightTrimmed") SDC2V2MCWWHSS16ReweightTrimmed = true;
    if (datasetString == "SDC2V2MCWWHSS16APVReweightTrimmed") SDC2V2MCWWHSS16APVReweightTrimmed = true;

    if (datasetString == "SDC2V2MCWWHOSReweightTrimmed") SDC2V2MCWWHOSReweightTrimmed = true;
    if (datasetString == "SDC2V2MCWWHOS17ReweightTrimmed") SDC2V2MCWWHOS17ReweightTrimmed = true;
    if (datasetString == "SDC2V2MCWWHOS16ReweightTrimmed") SDC2V2MCWWHOS16ReweightTrimmed = true;
    if (datasetString == "SDC2V2MCWWHOS16APVReweightTrimmed") SDC2V2MCWWHOS16APVReweightTrimmed = true;

    if (datasetString == "MaC2V2MCZZHReweightTrimmed") MaC2V2MCZZHReweightTrimmed = true;
    if (datasetString == "MaC2V2MCZZH17ReweightTrimmed") MaC2V2MCZZH17ReweightTrimmed = true;
    if (datasetString == "MaC2V2MCZZH16ReweightTrimmed") MaC2V2MCZZH16ReweightTrimmed = true;
    if (datasetString == "MaC2V2MCZZH16APVReweightTrimmed") MaC2V2MCZZH16APVReweightTrimmed = true;
    if (datasetString == "MaC2V2MCWZHReweightTrimmed") MaC2V2MCWZHReweightTrimmed = true;
    if (datasetString == "MaC2V2MCWZH17ReweightTrimmed") MaC2V2MCWZH17ReweightTrimmed = true;
    if (datasetString == "MaC2V2MCWZH16ReweightTrimmed") MaC2V2MCWZH16ReweightTrimmed = true;
    if (datasetString == "MaC2V2MCWZH16APVReweightTrimmed") MaC2V2MCWZH16APVReweightTrimmed = true;

    if (datasetString == "MaC2V2MCWWHSSReweightTrimmed") MaC2V2MCWWHSSReweightTrimmed = true;
    if (datasetString == "MaC2V2MCWWHSS17ReweightTrimmed") MaC2V2MCWWHSS17ReweightTrimmed = true;
    if (datasetString == "MaC2V2MCWWHSS16ReweightTrimmed") MaC2V2MCWWHSS16ReweightTrimmed = true;
    if (datasetString == "MaC2V2MCWWHSS16APVReweightTrimmed") MaC2V2MCWWHSS16APVReweightTrimmed = true;

    if (datasetString == "MaC2V2MCWWHOSReweightTrimmed") MaC2V2MCWWHOSReweightTrimmed = true;
    if (datasetString == "MaC2V2MCWWHOS17ReweightTrimmed") MaC2V2MCWWHOS17ReweightTrimmed = true;
    if (datasetString == "MaC2V2MCWWHOS16ReweightTrimmed") MaC2V2MCWWHOS16ReweightTrimmed = true;
    if (datasetString == "MaC2V2MCWWHOS16APVReweightTrimmed") MaC2V2MCWWHOS16APVReweightTrimmed = true;

    if (datasetString == "CenC2V2MCZZHReweightTrimmed") CenC2V2MCZZHReweightTrimmed = true;
    if (datasetString == "CenC2V2MCZZH17ReweightTrimmed") CenC2V2MCZZH17ReweightTrimmed = true;
    if (datasetString == "CenC2V2MCZZH16ReweightTrimmed") CenC2V2MCZZH16ReweightTrimmed = true;
    if (datasetString == "CenC2V2MCZZH16APVReweightTrimmed") CenC2V2MCZZH16APVReweightTrimmed = true;
    if (datasetString == "CenC2V2MCWZHReweightTrimmed") CenC2V2MCWZHReweightTrimmed = true;
    if (datasetString == "CenC2V2MCWZH17ReweightTrimmed") CenC2V2MCWZH17ReweightTrimmed = true;
    if (datasetString == "CenC2V2MCWZH16ReweightTrimmed") CenC2V2MCWZH16ReweightTrimmed = true;
    if (datasetString == "CenC2V2MCWZH16APVReweightTrimmed") CenC2V2MCWZH16APVReweightTrimmed = true;

    if (datasetString == "CenC2V2MCWWHSSReweightTrimmed") CenC2V2MCWWHSSReweightTrimmed = true;
    if (datasetString == "CenC2V2MCWWHSS17ReweightTrimmed") CenC2V2MCWWHSS17ReweightTrimmed = true;
    if (datasetString == "CenC2V2MCWWHSS16ReweightTrimmed") CenC2V2MCWWHSS16ReweightTrimmed = true;
    if (datasetString == "CenC2V2MCWWHSS16APVReweightTrimmed") CenC2V2MCWWHSS16APVReweightTrimmed = true;

    if (datasetString == "CenC2V2MCWWHOSReweightTrimmed") CenC2V2MCWWHOSReweightTrimmed = true;
    if (datasetString == "CenC2V2MCWWHOS17ReweightTrimmed") CenC2V2MCWWHOS17ReweightTrimmed = true;
    if (datasetString == "CenC2V2MCWWHOS16ReweightTrimmed") CenC2V2MCWWHOS16ReweightTrimmed = true;
    if (datasetString == "CenC2V2MCWWHOS16APVReweightTrimmed") CenC2V2MCWWHOS16APVReweightTrimmed = true;

    ////////////////////////////////GETTING DATASET////////////////////////////////
    ////////////////////////////////GETTING DATASET////////////////////////////////
    ////////////////////////////////GETTING DATASET////////////////////////////////
    ////////////////////////////////GETTING DATASET////////////////////////////////

    std::string strAdd;
    if (scratchDown) strAdd ="/afs/crc.nd.edu/user/d/dlutton/Public/condorStuff/NanoAODToHistos/tmpHoldForNanoAODWithoutScratch/";
    else strAdd ="/scratch365/dlutton/HLT042024ForPreSel/";
    if (localTest) strAdd = "";


    UInt_t datasetType = 0;

    UInt_t yearType = 0;



    if (SDC2V2MCZZHReweightTrimmed){
        saveName = "SDC2V2MCZZHReweightTrimmed";
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisSDC2V2MCZZHReweight"+NoSLString+"_0.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2V2MCZZH17ReweightTrimmed){
        saveName = "SDC2V2MCZZH17ReweightTrimmed";
        yearType = 1;
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisSDC2V2MCZZH17Reweight"+NoSLString+"_0.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2V2MCZZH16ReweightTrimmed){
        saveName = "SDC2V2MCZZH16ReweightTrimmed";
        yearType = 2;
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisSDC2V2MCZZH16Reweight"+NoSLString+"_0.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2V2MCZZH16APVReweightTrimmed){
        saveName = "SDC2V2MCZZH16APVReweightTrimmed";
        yearType = 3;
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisSDC2V2MCZZH16APVReweight"+NoSLString+"_0.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2V2MCWZHReweightTrimmed){
        saveName = "SDC2V2MCWZHReweightTrimmed";
        datasetType = 25;
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisSDC2V2MCWZHReweight"+NoSLString+"_0.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2V2MCWZH17ReweightTrimmed){
        saveName = "SDC2V2MCWZH17ReweightTrimmed";
        datasetType = 25;
        yearType = 1;
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisSDC2V2MCWZH17Reweight"+NoSLString+"_0.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2V2MCWZH16ReweightTrimmed){
        saveName = "SDC2V2MCWZH16ReweightTrimmed";
        datasetType = 25;
        yearType = 2;
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisSDC2V2MCWZH16Reweight"+NoSLString+"_0.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2V2MCWZH16APVReweightTrimmed){
        saveName = "SDC2V2MCWZH16APVReweightTrimmed";
        datasetType = 25;
        yearType = 3;
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisSDC2V2MCWZH16APVReweight"+NoSLString+"_0.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2V2MCWWHSSReweightTrimmed){
        saveName = "SDC2V2MCWWHSSReweightTrimmed";
        datasetType = 25;
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisSDC2V2MCWWHSSReweight"+NoSLString+"_0.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2V2MCWWHSS17ReweightTrimmed){
        saveName = "SDC2V2MCWWHSS17ReweightTrimmed";
        datasetType = 25;
        yearType = 1;
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisSDC2V2MCWWHSS17Reweight"+NoSLString+"_0.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2V2MCWWHSS16ReweightTrimmed){
        saveName = "SDC2V2MCWWHSS16ReweightTrimmed";
        datasetType = 25;
        yearType = 2;
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisSDC2V2MCWWHSS16Reweight"+NoSLString+"_0.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2V2MCWWHSS16APVReweightTrimmed){
        saveName = "SDC2V2MCWWHSS16APVReweightTrimmed";
        datasetType = 25;
        yearType = 3;
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisSDC2V2MCWWHSS16APVReweight"+NoSLString+"_0.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2V2MCWWHOSReweightTrimmed){
        saveName = "SDC2V2MCWWHOSReweightTrimmed";
        datasetType = 25;
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisSDC2V2MCWWHOSReweight"+NoSLString+"_0.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2V2MCWWHOS17ReweightTrimmed){
        saveName = "SDC2V2MCWWHOS17ReweightTrimmed";
        datasetType = 25;
        yearType = 1;
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisSDC2V2MCWWHOS17Reweight"+NoSLString+"_0.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2V2MCWWHOS16ReweightTrimmed){
        saveName = "SDC2V2MCWWHOS16ReweightTrimmed";
        datasetType = 25;
        yearType = 2;
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisSDC2V2MCWWHOS16Reweight"+NoSLString+"_0.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2V2MCWWHOS16APVReweightTrimmed){
        saveName = "SDC2V2MCWWHOS16APVReweightTrimmed";
        datasetType = 25;
        yearType = 3;
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisSDC2V2MCWWHOS16APVReweight"+NoSLString+"_0.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (MaC2V2MCZZHReweightTrimmed){
        saveName = "MaC2V2MCZZHReweightTrimmed";
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisMaC2V2MCZZHReweight"+NoSLString+"_0.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (MaC2V2MCZZH17ReweightTrimmed){
        saveName = "MaC2V2MCZZH17ReweightTrimmed";
        yearType = 1;
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisMaC2V2MCZZH17Reweight"+NoSLString+"_0.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (MaC2V2MCZZH16ReweightTrimmed){
        saveName = "MaC2V2MCZZH16ReweightTrimmed";
        yearType = 2;
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisMaC2V2MCZZH16Reweight"+NoSLString+"_0.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (MaC2V2MCZZH16APVReweightTrimmed){
        saveName = "MaC2V2MCZZH16APVReweightTrimmed";
        yearType = 3;
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisMaC2V2MCZZH16APVReweight"+NoSLString+"_0.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (MaC2V2MCWZHReweightTrimmed){
        saveName = "MaC2V2MCWZHReweightTrimmed";
        datasetType = 25;
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisMaC2V2MCWZHReweight"+NoSLString+"_0.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (MaC2V2MCWZH17ReweightTrimmed){
        saveName = "MaC2V2MCWZH17ReweightTrimmed";
        datasetType = 25;
        yearType = 1;
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisMaC2V2MCWZH17Reweight"+NoSLString+"_0.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (MaC2V2MCWZH16ReweightTrimmed){
        saveName = "MaC2V2MCWZH16ReweightTrimmed";
        datasetType = 25;
        yearType = 2;
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisMaC2V2MCWZH16Reweight"+NoSLString+"_0.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (MaC2V2MCWZH16APVReweightTrimmed){
        saveName = "MaC2V2MCWZH16APVReweightTrimmed";
        datasetType = 25;
        yearType = 3;
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisMaC2V2MCWZH16APVReweight"+NoSLString+"_0.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (MaC2V2MCWWHSSReweightTrimmed){
        saveName = "MaC2V2MCWWHSSReweightTrimmed";
        datasetType = 25;
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisMaC2V2MCWWHSSReweight"+NoSLString+"_0.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (MaC2V2MCWWHSS17ReweightTrimmed){
        saveName = "MaC2V2MCWWHSS17ReweightTrimmed";
        datasetType = 25;
        yearType = 1;
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisMaC2V2MCWWHSS17Reweight"+NoSLString+"_0.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (MaC2V2MCWWHSS16ReweightTrimmed){
        saveName = "MaC2V2MCWWHSS16ReweightTrimmed";
        datasetType = 25;
        yearType = 2;
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisMaC2V2MCWWHSS16Reweight"+NoSLString+"_0.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (MaC2V2MCWWHSS16APVReweightTrimmed){
        saveName = "MaC2V2MCWWHSS16APVReweightTrimmed";
        datasetType = 25;
        yearType = 3;
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisMaC2V2MCWWHSS16APVReweight"+NoSLString+"_0.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (MaC2V2MCWWHOSReweightTrimmed){
        saveName = "MaC2V2MCWWHOSReweightTrimmed";
        datasetType = 25;
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisMaC2V2MCWWHOSReweight"+NoSLString+"_0.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (MaC2V2MCWWHOS17ReweightTrimmed){
        saveName = "MaC2V2MCWWHOS17ReweightTrimmed";
        datasetType = 25;
        yearType = 1;
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisMaC2V2MCWWHOS17Reweight"+NoSLString+"_0.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (MaC2V2MCWWHOS16ReweightTrimmed){
        saveName = "MaC2V2MCWWHOS16ReweightTrimmed";
        datasetType = 25;
        yearType = 2;
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisMaC2V2MCWWHOS16Reweight"+NoSLString+"_0.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (MaC2V2MCWWHOS16APVReweightTrimmed){
        saveName = "MaC2V2MCWWHOS16APVReweightTrimmed";
        datasetType = 25;
        yearType = 3;
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisMaC2V2MCWWHOS16APVReweight"+NoSLString+"_0.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (CenC2V2MCZZHReweightTrimmed){
        saveName = "CenC2V2MCZZHReweightTrimmed";
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisCenC2V2MCZZHReweight"+NoSLString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (CenC2V2MCZZH17ReweightTrimmed){
        saveName = "CenC2V2MCZZH17ReweightTrimmed";
        yearType = 1;
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisCenC2V2MCZZH17Reweight"+NoSLString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (CenC2V2MCZZH16ReweightTrimmed){
        saveName = "CenC2V2MCZZH16ReweightTrimmed";
        yearType = 2;
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisCenC2V2MCZZH16Reweight"+NoSLString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (CenC2V2MCZZH16APVReweightTrimmed){
        saveName = "CenC2V2MCZZH16APVReweightTrimmed";
        yearType = 3;
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisCenC2V2MCZZH16APVReweight"+NoSLString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (CenC2V2MCWZHReweightTrimmed){
        saveName = "CenC2V2MCWZHReweightTrimmed";
        datasetType = 25;
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisCenC2V2MCWZHReweight"+NoSLString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (CenC2V2MCWZH17ReweightTrimmed){
        saveName = "CenC2V2MCWZH17ReweightTrimmed";
        datasetType = 25;
        yearType = 1;
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisCenC2V2MCWZH17Reweight"+NoSLString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (CenC2V2MCWZH16ReweightTrimmed){
        saveName = "CenC2V2MCWZH16ReweightTrimmed";
        datasetType = 25;
        yearType = 2;
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisCenC2V2MCWZH16Reweight"+NoSLString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (CenC2V2MCWZH16APVReweightTrimmed){
        saveName = "CenC2V2MCWZH16APVReweightTrimmed";
        datasetType = 25;
        yearType = 3;
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisCenC2V2MCWZH16APVReweight"+NoSLString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (CenC2V2MCWWHSSReweightTrimmed){
        saveName = "CenC2V2MCWWHSSReweightTrimmed";
        datasetType = 25;
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisCenC2V2MCWWHSSReweight"+NoSLString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (CenC2V2MCWWHSS17ReweightTrimmed){
        saveName = "CenC2V2MCWWHSS17ReweightTrimmed";
        datasetType = 25;
        yearType = 1;
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisCenC2V2MCWWHSS17Reweight"+NoSLString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (CenC2V2MCWWHSS16ReweightTrimmed){
        saveName = "CenC2V2MCWWHSS16ReweightTrimmed";
        datasetType = 25;
        yearType = 2;
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisCenC2V2MCWWHSS16Reweight"+NoSLString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (CenC2V2MCWWHSS16APVReweightTrimmed){
        saveName = "CenC2V2MCWWHSS16APVReweightTrimmed";
        datasetType = 25;
        yearType = 3;
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisCenC2V2MCWWHSS16APVReweight"+NoSLString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (CenC2V2MCWWHOSReweightTrimmed){
        saveName = "CenC2V2MCWWHOSReweightTrimmed";
        datasetType = 25;
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisCenC2V2MCWWHOSReweight"+NoSLString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (CenC2V2MCWWHOS17ReweightTrimmed){
        saveName = "CenC2V2MCWWHOS17ReweightTrimmed";
        datasetType = 25;
        yearType = 1;
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisCenC2V2MCWWHOS17Reweight"+NoSLString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (CenC2V2MCWWHOS16ReweightTrimmed){
        saveName = "CenC2V2MCWWHOS16ReweightTrimmed";
        datasetType = 25;
        yearType = 2;
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisCenC2V2MCWWHOS16Reweight"+NoSLString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (CenC2V2MCWWHOS16APVReweightTrimmed){
        saveName = "CenC2V2MCWWHOS16APVReweightTrimmed";
        datasetType = 25;
        yearType = 3;
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisCenC2V2MCWWHOS16APVReweight"+NoSLString+".root";
        fileAr.push_back(tmpStrWithPath);
    }

    else if (testRun){
        saveName = "testRun";
        fileAr.push_back("./HLTFilteredForAnalysistestRun_0.root");
        
    }
    else{
        std::cout << "ERROR. NO INPUT DATASET NAME GIVEN\n";
    }

    if (!useSingleLepHLT){
        saveName = saveName+NoSLString;
    }

    std::cout << "Doing " << saveName << "\n";
    //Setting up outfile with variables for BDT
    //convert int to str


    std::string outFileStr = "HLTTrimmedFilteredForAnalysis"+saveName+"_WithJERRoch.root";
    std::cout << "OutFile: " << outFileStr << "\n";
    TFile *outFile = new TFile(outFileStr.c_str(),"RECREATE");

    UInt_t datanEv = 0;
    UInt_t datanEvPass = 0;
    UInt_t evCount = 0;
    UInt_t evRunOver = 0;

    std::string yearStr;
    if (yearType == 0) yearStr = "Summer19UL18_JRV2_MC";
    else if (yearType == 1) yearStr = "Summer19UL17_JRV3_MC";
    else if (yearType == 2) yearStr = "Summer20UL16_JRV3_MC";
    else if (yearType == 3) yearStr = "Summer20UL16APV_JRV3_MC";
    std::string filePathStr = "../NanoCORE/Tools/jetcorr/data/"+yearStr+"/"+yearStr;
    std::string jetres_SF_chsStr = filePathStr+"_SF_AK4PFchs.txt";
    std::string jetres_PtResolution_chsStr = filePathStr+"_PtResolution_AK4PFchs.txt";
    std::string jetres_SF_PuppiStr = filePathStr+"_SF_AK8PFPuppi.txt";
    std::string jetres_PtResolution_PuppiStr = filePathStr+"_PtResolution_AK8PFPuppi.txt";
    JetResolutionUncertainty jetResUncPuppi(jetres_PtResolution_PuppiStr, jetres_SF_PuppiStr);
    JetResolutionUncertainty jetResUncCHS(jetres_PtResolution_chsStr, jetres_SF_chsStr);
    
    //05052024 Adding PN regress mass scaling and resolution correction functions

    

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

    UInt_t nLHEReweightingWeightL;
    std::vector<Float_t> LHEReweightingWeightL;

    Double_t genWeightL;



    //Jets
    UInt_t nJetL;
    std::vector<Float_t> Jet_etaL;
    std::vector<Float_t> Jet_ptL;
    std::vector<Float_t> Jet_phiL;
    std::vector<Float_t> Jet_massL;
    std::vector<Int_t> Jet_jetIdL;
    std::vector<Int_t> Jet_hadronFlavourL;
    std::vector<Int_t> Jet_genJetIdxL;
    std::vector<Float_t> Jet_btagDeepFlavBL;
    Float_t fixedGridRhoFastjetAllL;
    //Jets with JER applied
    std::vector<Float_t> Jet_eta_JERMidL;
    std::vector<Float_t> Jet_pt_JERMidL;
    std::vector<Float_t> Jet_phi_JERMidL;
    std::vector<Float_t> Jet_mass_JERMidL;
    std::vector<Float_t> Jet_eta_JERUpL;
    std::vector<Float_t> Jet_pt_JERUpL;
    std::vector<Float_t> Jet_phi_JERUpL;
    std::vector<Float_t> Jet_mass_JERUpL;
    std::vector<Float_t> Jet_eta_JERDownL;
    std::vector<Float_t> Jet_pt_JERDownL;
    std::vector<Float_t> Jet_phi_JERDownL;
    std::vector<Float_t> Jet_mass_JERDownL;

    //GenJets
    UInt_t nGenJetL;
    std::vector<Float_t> GenJet_etaL;
    std::vector<Float_t> GenJet_ptL;
    std::vector<Float_t> GenJet_phiL;
    std::vector<Float_t> GenJet_massL;
    std::vector<UChar_t> GenJet_hadronFlavourL;
    
    //GenJetAK8
    UInt_t nGenJetAK8L;
    std::vector<Float_t> GenJetAK8_etaL;
    std::vector<Float_t> GenJetAK8_ptL;
    std::vector<Float_t> GenJetAK8_phiL;
    std::vector<Float_t> GenJetAK8_massL;
    std::vector<UChar_t> GenJetAK8_hadronFlavourL;



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
    //Jets with JER applied
    std::vector<Float_t> FatJet_eta_JERMidL;
    std::vector<Float_t> FatJet_pt_JERMidL;
    std::vector<Float_t> FatJet_phi_JERMidL;
    std::vector<Float_t> FatJet_mass_JERMidL;
    std::vector<Float_t> FatJet_eta_JERUpL;
    std::vector<Float_t> FatJet_pt_JERUpL;
    std::vector<Float_t> FatJet_phi_JERUpL;
    std::vector<Float_t> FatJet_mass_JERUpL;
    std::vector<Float_t> FatJet_eta_JERDownL;
    std::vector<Float_t> FatJet_pt_JERDownL;
    std::vector<Float_t> FatJet_phi_JERDownL;
    std::vector<Float_t> FatJet_mass_JERDownL;

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
    std::vector<Int_t> Muon_genPartIdxL;
    

    

    //ParticleNet
    std::vector<Float_t> FatJet_particleNet_HbbvsQCDL;
    std::vector<Float_t> FatJet_particleNet_ZvsQCDL;
    std::vector<Float_t> FatJet_particleNetMD_QCDL;
    std::vector<Float_t> FatJet_particleNetMD_XbbL;
    std::vector<Float_t> FatJet_particleNetMD_XccL;
    std::vector<Float_t> FatJet_particleNetMD_XqqL;


    //Gen Particles

    UInt_t nGenPartL;
    std::vector<Float_t> GenPart_etaL;
    std::vector<Float_t> GenPart_massL;
    std::vector<Float_t> GenPart_phiL;
    std::vector<Float_t> GenPart_ptL;
    std::vector<Int_t> GenPart_genPartIdxMotherL;
    std::vector<Int_t> GenPart_pdgIdL;
    std::vector<Int_t> GenPart_statusL;
    std::vector<Int_t> GenPart_statusFlagsL;

    //genChannel characterization
    //0=Leptonic,1=Semi-leptonic,2=Hadronic,3=Other,4=Error
    UInt_t genChannelL;

    Bool_t HTobbBoolL;

    //FJ GENMATCH
    //THESE BRANCHES CURRENTLY SET TO DEFAULT VALUES
    //ONLY INCLUDED TO MAKE COMPATIBLE WITH ZZH ANALYSIS CODE

    Int_t ZFJIndL;
    Int_t HFJIndL;
    Bool_t goodGenZFJMatchL;
    Bool_t goodGenHFJMatchL;
    Bool_t goodZFJMatchToGenL;
    Bool_t goodHFJMatchToGenL;
    Bool_t eventGenSemileptonicL;
    Bool_t eventGenHToBBL;
    Int_t ZFJGenHadronFlavourL;
    Int_t HFJGenHadronFlavourL;
    std::vector<Int_t> FatJet_hadronFlavourL;

    UInt_t nHDecayPIDL;
    std::vector<Int_t> HDecayPIDL;
    UInt_t nZOneDecayPIDL;
    std::vector<Int_t> ZOneDecayPIDL;
    UInt_t nZTwoDecayPIDL;
    std::vector<Int_t> ZTwoDecayPIDL;
    Int_t ZOneTypeL; //0=Leptonic,1=Hadronic,2=Other
    Int_t ZTwoTypeL;
    //HLT 
    Bool_t HLT_Ele32_WPTight_Gsf_L1DoubleEGL;
    Bool_t HLT_IsoMu27L;
    Bool_t HLT_Mu50L;
    Bool_t HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZL;
    Bool_t HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8L;

    //2016 in other years just set these to false
    Bool_t HLT_Ele27_WPTight_GsfL;
    Bool_t HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZL;

    //change 2018 to IsoMu24 and remove DZ from diele trigger for 2018 and 2017
    Bool_t HLT_IsoMu24L;
    Bool_t HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVLL;

    //2016 in other years just set these to false
    Bool_t HLT_IsoTkMu24L;

    //042024SFAndSuchAdditions
    //PU JetID
    std::vector<Int_t> Jet_puIdL;
    //L1 Prefiring Weights
    Float_t L1PreFiringWeight_NomL;
    Float_t L1PreFiringWeight_DnL;
    Float_t L1PreFiringWeight_UpL;
    //PileUp number of interactions
    Float_t Pileup_nTrueIntL;
    Int_t Pileup_nPUL;
    //PSWeight
    UInt_t nPSWeightL;
    std::vector<Float_t> PSWeightL;
    //LHE Scale Weight
    UInt_t nLHEScaleWeightL;
    std::vector<Float_t> LHEScaleWeightL;
    //LHE PDF Weight
    UInt_t nLHEPdfWeightL;
    std::vector<Float_t> LHEPdfWeightL;
    Float_t LHEWeight_originalXWGTUPL;
    //generator weight
    Float_t Generator_weightL;

    //05052024 Additions for PN regress mass scaling and resolution corrections
    UInt_t luminosityBlockL;
    ULong64_t eventL;
    //PN Regress Mass nominal JMS and JMR plus up/down
    std::vector<Float_t> FatJet_particleNet_mass_JMSNomJMRNomCorL;
    std::vector<Float_t> FatJet_particleNet_mass_JMSNomJMRUpCorL;
    std::vector<Float_t> FatJet_particleNet_mass_JMSNomJMRDownCorL;
    std::vector<Float_t> FatJet_particleNet_mass_JMSUpJMRNomCorL;
    std::vector<Float_t> FatJet_particleNet_mass_JMSDownJMRNomCorL;
    
    


    TTree *FilteredEventsTree = new TTree("FilteredEventsTree", "FilteredEventsTree");

    //Event reweighting
    FilteredEventsTree->Branch("nLHEReweightingWeightL",&nLHEReweightingWeightL,"nLHEReweightingWeightL/i");
    FilteredEventsTree->Branch("LHEReweightingWeightL",&LHEReweightingWeightL);

    //gen weights
    FilteredEventsTree->Branch("genWeightL",&genWeightL,"genWeightL/D");

    //Jets    
    FilteredEventsTree->Branch("nJetL",&nJetL,"nJetL/i");
    FilteredEventsTree->Branch("Jet_etaL",&Jet_etaL);
    FilteredEventsTree->Branch("Jet_ptL",&Jet_ptL);
    FilteredEventsTree->Branch("Jet_phiL",&Jet_phiL);
    FilteredEventsTree->Branch("Jet_massL",&Jet_massL);
    FilteredEventsTree->Branch("Jet_jetIdL",&Jet_jetIdL);
    FilteredEventsTree->Branch("Jet_hadronFlavourL",&Jet_hadronFlavourL);
    FilteredEventsTree->Branch("Jet_genJetIdxL",&Jet_genJetIdxL);
    FilteredEventsTree->Branch("Jet_btagDeepFlavBL",&Jet_btagDeepFlavBL);
    FilteredEventsTree->Branch("fixedGridRhoFastjetAllL",&fixedGridRhoFastjetAllL,"fixedGridRhoFastjetAllL/F");
    //Jets with JER applied
    FilteredEventsTree->Branch("Jet_eta_JERMidL",&Jet_eta_JERMidL);
    FilteredEventsTree->Branch("Jet_pt_JERMidL",&Jet_pt_JERMidL);
    FilteredEventsTree->Branch("Jet_phi_JERMidL",&Jet_phi_JERMidL);
    FilteredEventsTree->Branch("Jet_mass_JERMidL",&Jet_mass_JERMidL);
    FilteredEventsTree->Branch("Jet_eta_JERUpL",&Jet_eta_JERUpL);
    FilteredEventsTree->Branch("Jet_pt_JERUpL",&Jet_pt_JERUpL);
    FilteredEventsTree->Branch("Jet_phi_JERUpL",&Jet_phi_JERUpL);
    FilteredEventsTree->Branch("Jet_mass_JERUpL",&Jet_mass_JERUpL);
    FilteredEventsTree->Branch("Jet_eta_JERDownL",&Jet_eta_JERDownL);
    FilteredEventsTree->Branch("Jet_pt_JERDownL",&Jet_pt_JERDownL);
    FilteredEventsTree->Branch("Jet_phi_JERDownL",&Jet_phi_JERDownL);
    FilteredEventsTree->Branch("Jet_mass_JERDownL",&Jet_mass_JERDownL);

    //GenJets
    FilteredEventsTree->Branch("nGenJetL",&nGenJetL,"nGenJetL/i");
    FilteredEventsTree->Branch("GenJet_etaL",&GenJet_etaL);
    FilteredEventsTree->Branch("GenJet_ptL",&GenJet_ptL);
    FilteredEventsTree->Branch("GenJet_phiL",&GenJet_phiL);
    FilteredEventsTree->Branch("GenJet_massL",&GenJet_massL);
    FilteredEventsTree->Branch("GenJet_hadronFlavourL",&GenJet_hadronFlavourL);

    //GenJetAK8
    FilteredEventsTree->Branch("nGenJetAK8L",&nGenJetAK8L,"nGenJetAK8L/i");
    FilteredEventsTree->Branch("GenJetAK8_etaL",&GenJetAK8_etaL);
    FilteredEventsTree->Branch("GenJetAK8_ptL",&GenJetAK8_ptL);
    FilteredEventsTree->Branch("GenJetAK8_phiL",&GenJetAK8_phiL);
    FilteredEventsTree->Branch("GenJetAK8_massL",&GenJetAK8_massL);
    FilteredEventsTree->Branch("GenJetAK8_hadronFlavourL",&GenJetAK8_hadronFlavourL);

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
    //Jets with JER applied
    FilteredEventsTree->Branch("FatJet_eta_JERMidL",&FatJet_eta_JERMidL);
    FilteredEventsTree->Branch("FatJet_pt_JERMidL",&FatJet_pt_JERMidL);
    FilteredEventsTree->Branch("FatJet_phi_JERMidL",&FatJet_phi_JERMidL);
    FilteredEventsTree->Branch("FatJet_mass_JERMidL",&FatJet_mass_JERMidL);
    FilteredEventsTree->Branch("FatJet_eta_JERUpL",&FatJet_eta_JERUpL);
    FilteredEventsTree->Branch("FatJet_pt_JERUpL",&FatJet_pt_JERUpL);
    FilteredEventsTree->Branch("FatJet_phi_JERUpL",&FatJet_phi_JERUpL);
    FilteredEventsTree->Branch("FatJet_mass_JERUpL",&FatJet_mass_JERUpL);
    FilteredEventsTree->Branch("FatJet_eta_JERDownL",&FatJet_eta_JERDownL);
    FilteredEventsTree->Branch("FatJet_pt_JERDownL",&FatJet_pt_JERDownL);
    FilteredEventsTree->Branch("FatJet_phi_JERDownL",&FatJet_phi_JERDownL);
    FilteredEventsTree->Branch("FatJet_mass_JERDownL",&FatJet_mass_JERDownL);




    

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
    FilteredEventsTree->Branch("Muon_genPartIdxL",&Muon_genPartIdxL);

    //ParticleNet
    FilteredEventsTree->Branch("FatJet_particleNet_HbbvsQCDL",&FatJet_particleNet_HbbvsQCDL);
    FilteredEventsTree->Branch("FatJet_particleNet_ZvsQCDL",&FatJet_particleNet_ZvsQCDL);

    FilteredEventsTree->Branch("FatJet_particleNetMD_QCDL", &FatJet_particleNetMD_QCDL);
    FilteredEventsTree->Branch("FatJet_particleNetMD_XbbL", &FatJet_particleNetMD_XbbL);
    FilteredEventsTree->Branch("FatJet_particleNetMD_XccL", &FatJet_particleNetMD_XccL);
    FilteredEventsTree->Branch("FatJet_particleNetMD_XqqL", &FatJet_particleNetMD_XqqL);

    //Gen Particles
    FilteredEventsTree->Branch("nGenPartL",&nGenPartL,"nGenPartL/i");
    FilteredEventsTree->Branch("GenPart_etaL",&GenPart_etaL);
    FilteredEventsTree->Branch("GenPart_massL",&GenPart_massL);
    FilteredEventsTree->Branch("GenPart_phiL",&GenPart_phiL);
    FilteredEventsTree->Branch("GenPart_ptL",&GenPart_ptL);
    FilteredEventsTree->Branch("GenPart_genPartIdxMotherL",&GenPart_genPartIdxMotherL);
    FilteredEventsTree->Branch("GenPart_pdgIdL",&GenPart_pdgIdL);
    FilteredEventsTree->Branch("GenPart_statusL",&GenPart_statusL);
    FilteredEventsTree->Branch("GenPart_statusFlagsL",&GenPart_statusFlagsL);

    //genChannel characterization
    //0=Leptonic,1=Semi-leptonic,2=Hadronic,3=Other,4=Error
    FilteredEventsTree->Branch("genChannelL",&genChannelL,"genChannelL/i");

    FilteredEventsTree->Branch("HTobbBoolL",&HTobbBoolL,"HTobbBoolL/O");

    FilteredEventsTree->Branch("ZFJIndL",&ZFJIndL,"ZFJIndL/I");
    FilteredEventsTree->Branch("HFJIndL",&HFJIndL,"HFJIndL/I");
    FilteredEventsTree->Branch("goodGenZFJMatchL",&goodGenZFJMatchL,"goodGenZFJMatchL/O");
    FilteredEventsTree->Branch("goodGenHFJMatchL",&goodGenHFJMatchL,"goodGenHFJMatchL/O");
    FilteredEventsTree->Branch("goodZFJMatchToGenL",&goodZFJMatchToGenL,"goodZFJMatchToGenL/O");
    FilteredEventsTree->Branch("goodHFJMatchToGenL",&goodHFJMatchToGenL,"goodHFJMatchToGenL/O");
    FilteredEventsTree->Branch("eventGenSemileptonicL",&eventGenSemileptonicL,"eventGenSemileptonicL/O");
    FilteredEventsTree->Branch("eventGenHToBBL",&eventGenHToBBL,"eventGenHToBBL/O");

    FilteredEventsTree->Branch("ZFJGenHadronFlavourL",&ZFJGenHadronFlavourL,"ZFJGenHadronFlavourL/I");
    FilteredEventsTree->Branch("HFJGenHadronFlavourL",&HFJGenHadronFlavourL,"HFJGenHadronFlavourL/I");
    FilteredEventsTree->Branch("FatJet_hadronFlavourL",&FatJet_hadronFlavourL);

    FilteredEventsTree->Branch("nHDecayPIDL",&nHDecayPIDL,"nHDecayPIDL/i");
    FilteredEventsTree->Branch("HDecayPIDL",&HDecayPIDL);

    FilteredEventsTree->Branch("nZOneDecayPIDL",&nZOneDecayPIDL,"nZOneDecayPIDL/i");
    FilteredEventsTree->Branch("ZOneDecayPIDL",&ZOneDecayPIDL);
    FilteredEventsTree->Branch("nZTwoDecayPIDL",&nZTwoDecayPIDL,"nZTwoDecayPIDL/i");
    FilteredEventsTree->Branch("ZTwoDecayPIDL",&ZTwoDecayPIDL);

    FilteredEventsTree->Branch("ZOneTypeL",&ZOneTypeL,"ZOneTypeL/I");
    FilteredEventsTree->Branch("ZTwoTypeL",&ZTwoTypeL,"ZTwoTypeL/I");

    FilteredEventsTree->Branch("HLT_Ele32_WPTight_Gsf_L1DoubleEGL",&HLT_Ele32_WPTight_Gsf_L1DoubleEGL,"HLT_Ele32_WPTight_Gsf_L1DoubleEGL/O");
    FilteredEventsTree->Branch("HLT_IsoMu27L",&HLT_IsoMu27L,"HLT_IsoMu27L/O");
    FilteredEventsTree->Branch("HLT_Mu50L",&HLT_Mu50L,"HLT_Mu50L/O");
    FilteredEventsTree->Branch("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZL",&HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZL,"HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZL/O");
    FilteredEventsTree->Branch("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8L",&HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8L,"HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8L/O");

    FilteredEventsTree->Branch("HLT_Ele27_WPTight_GsfL",&HLT_Ele27_WPTight_GsfL,"HLT_Ele27_WPTight_GsfL/O");
    FilteredEventsTree->Branch("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZL",&HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZL,"HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZL/O");

    FilteredEventsTree->Branch("HLT_IsoMu24L",&HLT_IsoMu24L,"HLT_IsoMu24L/O");
    FilteredEventsTree->Branch("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVLL",&HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVLL,"HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVLL/O");
    FilteredEventsTree->Branch("HLT_IsoTkMu24L",&HLT_IsoTkMu24L,"HLT_IsoTkMu24L/O");

    //042024SFAndSuchAdditions
    //PU JetID
    FilteredEventsTree->Branch("Jet_puIdL",&Jet_puIdL);
    //L1 Prefiring Weights
    FilteredEventsTree->Branch("L1PreFiringWeight_NomL",&L1PreFiringWeight_NomL,"L1PreFiringWeight_NomL/F");
    FilteredEventsTree->Branch("L1PreFiringWeight_DnL",&L1PreFiringWeight_DnL,"L1PreFiringWeight_DnL/F");
    FilteredEventsTree->Branch("L1PreFiringWeight_UpL",&L1PreFiringWeight_UpL,"L1PreFiringWeight_UpL/F");
    //PileUp number of interactions
    FilteredEventsTree->Branch("Pileup_nTrueIntL",&Pileup_nTrueIntL,"Pileup_nTrueIntL/F");
    FilteredEventsTree->Branch("Pileup_nPUL",&Pileup_nPUL,"Pileup_nPUL/I");
    //PSWeight
    FilteredEventsTree->Branch("nPSWeightL",&nPSWeightL,"nPSWeightL/i");
    FilteredEventsTree->Branch("PSWeightL",&PSWeightL);
    //LHE Scale Weight
    FilteredEventsTree->Branch("nLHEScaleWeightL",&nLHEScaleWeightL,"nLHEScaleWeightL/i");
    FilteredEventsTree->Branch("LHEScaleWeightL",&LHEScaleWeightL);
    //LHE PDF Weight
    FilteredEventsTree->Branch("nLHEPdfWeightL",&nLHEPdfWeightL,"nLHEPdfWeightL/i");
    FilteredEventsTree->Branch("LHEPdfWeightL",&LHEPdfWeightL);
    FilteredEventsTree->Branch("LHEWeight_originalXWGTUPL",&LHEWeight_originalXWGTUPL,"LHEWeight_originalXWGTUPL/F");
    //generator weight
    FilteredEventsTree->Branch("Generator_weightL",&Generator_weightL,"Generator_weightL/F");

    //05052024 Additions for PN regress mass scaling and resolution corrections
    FilteredEventsTree->Branch("luminosityBlockL",&luminosityBlockL,"luminosityBlockL/i");
    FilteredEventsTree->Branch("eventL",&eventL,"eventL/l");
    //PN Regress Mass nominal JMS and JMR plus up/down
    FilteredEventsTree->Branch("FatJet_particleNet_mass_JMSNomJMRNomCorL", &FatJet_particleNet_mass_JMSNomJMRNomCorL);
    FilteredEventsTree->Branch("FatJet_particleNet_mass_JMSNomJMRUpCorL", &FatJet_particleNet_mass_JMSNomJMRUpCorL);
    FilteredEventsTree->Branch("FatJet_particleNet_mass_JMSNomJMRDownCorL", &FatJet_particleNet_mass_JMSNomJMRDownCorL);
    FilteredEventsTree->Branch("FatJet_particleNet_mass_JMSUpJMRNomCorL", &FatJet_particleNet_mass_JMSUpJMRNomCorL);
    FilteredEventsTree->Branch("FatJet_particleNet_mass_JMSDownJMRNomCorL", &FatJet_particleNet_mass_JMSDownJMRNomCorL);


    //Whole Run Tree
    UInt_t nLHEPdfSumwL;
    std::vector<Double_t> LHEPdfSumwL;
    UInt_t nLHEScaleSumwL;
    std::vector<Double_t> LHEScaleSumwL;
    UInt_t nLHEReweightingSumwL;
    std::vector<Double_t> LHEReweightingSumwL;
    Long64_t genEventCountL;
    Double_t genEventSumwL;
    Double_t genEventSumw2L;
    UInt_t runL;
    

    TTree *runTree = new TTree("runTree", "runTree");

    runTree->Branch("nLHEPdfSumwL",&nLHEPdfSumwL,"nLHEPdfSumwL/i");
    runTree->Branch("LHEPdfSumwL",&LHEPdfSumwL);
    runTree->Branch("nLHEScaleSumwL",&nLHEScaleSumwL,"nLHEScaleSumwL/i");
    runTree->Branch("LHEScaleSumwL",&LHEScaleSumwL);
    runTree->Branch("nLHEReweightingSumwL",&nLHEReweightingSumwL,"nLHEReweightingSumwL/i");
    runTree->Branch("LHEReweightingSumwL",&LHEReweightingSumwL);
    runTree->Branch("genEventCountL",&genEventCountL,"genEventCountL/L");
    runTree->Branch("genEventSumwL",&genEventSumwL,"genEventSumwL/D");
    runTree->Branch("genEventSumw2L",&genEventSumw2L,"genEventSumw2L/D");
    runTree->Branch("runL",&runL,"runL/i");

    //Weight sums tree
    Float_t Generator_weightSumL;
    UInt_t nLHEPdfWeightSumL;
    std::vector<Float_t> LHEPdfWeightSumL;
    UInt_t nLHEReweightingWeightSumL;
    std::vector<Float_t> LHEReweightingWeightSumL;
    Float_t LHEWeight_originalXWGTUPSumL;
    Float_t genWeightSumL;

    TTree *weightSumsTree = new TTree("weightSumsTree", "weightSumsTree");

    weightSumsTree->Branch("Generator_weightSumL",&Generator_weightSumL,"Generator_weightSumL/F");
    weightSumsTree->Branch("nLHEPdfWeightSumL",&nLHEPdfWeightSumL,"nLHEPdfWeightSumL/i");
    weightSumsTree->Branch("LHEPdfWeightSumL",&LHEPdfWeightSumL);
    weightSumsTree->Branch("nLHEReweightingWeightSumL",&nLHEReweightingWeightSumL,"nLHEReweightingWeightSumL/i");
    weightSumsTree->Branch("LHEReweightingWeightSumL",&LHEReweightingWeightSumL);
    weightSumsTree->Branch("LHEWeight_originalXWGTUPSumL",&LHEWeight_originalXWGTUPSumL,"LHEWeight_originalXWGTUPSumL/F");
    weightSumsTree->Branch("genWeightSumL",&genWeightSumL,"genWeightSumL/F");


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

        //Event reweighting
        TTreeReaderValue<UInt_t> nLHEReweightingWeight(myEventsReader, "nLHEReweightingWeightL");
        TTreeReaderArray<Float_t> LHEReweightingWeight(myEventsReader, "LHEReweightingWeightL");

        //gen weights
        TTreeReaderValue<Double_t> genWeight(myEventsReader, "genWeightL");

        //jets

        TTreeReaderValue<UInt_t> nJet(myEventsReader, "nJetL");
        TTreeReaderArray<Float_t> Jet_eta(myEventsReader, "Jet_etaL");
        TTreeReaderArray<Float_t> Jet_pt(myEventsReader, "Jet_ptL");
        TTreeReaderArray<Float_t> Jet_phi(myEventsReader, "Jet_phiL");
        TTreeReaderArray<Float_t> Jet_mass(myEventsReader, "Jet_massL");
        TTreeReaderArray<Int_t> Jet_jetId(myEventsReader, "Jet_jetIdL");
        TTreeReaderArray<Int_t> Jet_hadronFlavour(myEventsReader, "Jet_hadronFlavourL");
        TTreeReaderArray<Int_t> Jet_genJetIdx(myEventsReader, "Jet_genJetIdxL");
        TTreeReaderArray<Float_t> Jet_btagDeepFlavB(myEventsReader,"Jet_btagDeepFlavBL");
        TTreeReaderValue<Float_t> fixedGridRhoFastjetAll(myEventsReader, "fixedGridRhoFastjetAllL");

        //GenJets

        TTreeReaderValue<UInt_t> nGenJet(myEventsReader, "nGenJetL");
        TTreeReaderArray<Float_t> GenJet_eta(myEventsReader, "GenJet_etaL");
        TTreeReaderArray<Float_t> GenJet_pt(myEventsReader, "GenJet_ptL");
        TTreeReaderArray<Float_t> GenJet_phi(myEventsReader, "GenJet_phiL");
        TTreeReaderArray<Float_t> GenJet_mass(myEventsReader, "GenJet_massL");
        TTreeReaderArray<UChar_t> GenJet_hadronFlavour(myEventsReader, "GenJet_hadronFlavourL");

        //GenJetAK8
        TTreeReaderValue<UInt_t> nGenJetAK8(myEventsReader, "nGenJetAK8L");
        TTreeReaderArray<Float_t> GenJetAK8_eta(myEventsReader, "GenJetAK8_etaL");
        TTreeReaderArray<Float_t> GenJetAK8_pt(myEventsReader, "GenJetAK8_ptL");
        TTreeReaderArray<Float_t> GenJetAK8_phi(myEventsReader, "GenJetAK8_phiL");
        TTreeReaderArray<Float_t> GenJetAK8_mass(myEventsReader, "GenJetAK8_massL");
        TTreeReaderArray<UChar_t> GenJetAK8_hadronFlavour(myEventsReader, "GenJetAK8_hadronFlavourL");

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
        TTreeReaderArray<Int_t> Muon_genPartIdx(myEventsReader, "Muon_genPartIdxL");




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

        //Gen Particles
        TTreeReaderValue<UInt_t> nGenPart(myEventsReader, "nGenPartL");
        TTreeReaderArray<Float_t> GenPart_eta(myEventsReader, "GenPart_etaL");
        TTreeReaderArray<Float_t> GenPart_mass(myEventsReader, "GenPart_massL");
        TTreeReaderArray<Float_t> GenPart_phi(myEventsReader, "GenPart_phiL");
        TTreeReaderArray<Float_t> GenPart_pt(myEventsReader, "GenPart_ptL");
        TTreeReaderArray<Int_t> GenPart_genPartIdxMother(myEventsReader, "GenPart_genPartIdxMotherL");
        TTreeReaderArray<Int_t> GenPart_pdgId(myEventsReader, "GenPart_pdgIdL");
        TTreeReaderArray<Int_t> GenPart_status(myEventsReader, "GenPart_statusL");
        TTreeReaderArray<Int_t> GenPart_statusFlags(myEventsReader, "GenPart_statusFlagsL");

        //genChannel characterization
        //0=Leptonic,1=Semi-leptonic,2=Hadronic,3=Other,4=Error
        TTreeReaderValue<UInt_t> genChannel(myEventsReader, "genChannelL");

        TTreeReaderValue<Bool_t> HTobbBool(myEventsReader, "HTobbBoolL");

        //FJ GENMATCH

        TTreeReaderValue<Int_t> ZFJInd(myEventsReader, "ZFJIndL");
        TTreeReaderValue<Int_t> HFJInd(myEventsReader, "HFJIndL");
        TTreeReaderValue<Bool_t> goodGenZFJMatch(myEventsReader, "goodGenZFJMatchL");
        TTreeReaderValue<Bool_t> goodGenHFJMatch(myEventsReader, "goodGenHFJMatchL");
        TTreeReaderValue<Bool_t> goodZFJMatchToGen(myEventsReader, "goodZFJMatchToGenL");
        TTreeReaderValue<Bool_t> goodHFJMatchToGen(myEventsReader, "goodHFJMatchToGenL");
        TTreeReaderValue<Bool_t> eventGenSemileptonic(myEventsReader, "eventGenSemileptonicL");
        TTreeReaderValue<Bool_t> eventGenHToBB(myEventsReader, "eventGenHToBBL");
        TTreeReaderValue<Int_t> ZFJGenHadronFlavour(myEventsReader, "ZFJGenHadronFlavourL");
        TTreeReaderValue<Int_t> HFJGenHadronFlavour(myEventsReader, "HFJGenHadronFlavourL");
        TTreeReaderArray<Int_t> FatJet_hadronFlavour(myEventsReader, "FatJet_hadronFlavourL");

        TTreeReaderValue<UInt_t> nHDecayPID(myEventsReader, "nHDecayPIDL");
        TTreeReaderArray<Int_t> HDecayPID(myEventsReader, "HDecayPIDL");

        TTreeReaderValue<UInt_t> nZOneDecayPID(myEventsReader, "nZOneDecayPIDL");
        TTreeReaderArray<Int_t> ZOneDecayPID(myEventsReader, "ZOneDecayPIDL");
        TTreeReaderValue<UInt_t> nZTwoDecayPID(myEventsReader, "nZTwoDecayPIDL");
        TTreeReaderArray<Int_t> ZTwoDecayPID(myEventsReader, "ZTwoDecayPIDL");

        TTreeReaderValue<Int_t> ZOneType(myEventsReader, "ZOneTypeL");
        TTreeReaderValue<Int_t> ZTwoType(myEventsReader, "ZTwoTypeL");

        TTreeReaderValue<Bool_t> HLT_Ele32_WPTight_Gsf_L1DoubleEG(myEventsReader,"HLT_Ele32_WPTight_Gsf_L1DoubleEGL");
        TTreeReaderValue<Bool_t> HLT_IsoMu27(myEventsReader,"HLT_IsoMu27L");
        TTreeReaderValue<Bool_t> HLT_Mu50(myEventsReader,"HLT_Mu50L");
        TTreeReaderValue<Bool_t> HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ(myEventsReader,"HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZL");
        TTreeReaderValue<Bool_t> HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8(myEventsReader,"HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8L");

        TTreeReaderValue<Bool_t> HLT_Ele27_WPTight_Gsf(myEventsReader,"HLT_Ele27_WPTight_GsfL");
        TTreeReaderValue<Bool_t> HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ(myEventsReader,"HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZL");

        TTreeReaderValue<Bool_t> HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL(myEventsReader, "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVLL");
        TTreeReaderValue<Bool_t> HLT_IsoMu24(myEventsReader,"HLT_IsoMu24L");
        TTreeReaderValue<Bool_t> HLT_IsoTkMu24(myEventsReader, "HLT_IsoTkMu24L");

        //042024SFAndSuchAdditions
        //PU JetID
        TTreeReaderArray<Int_t> Jet_puId(myEventsReader, "Jet_puIdL");
        //L1 Prefiring Weights
        TTreeReaderValue<Float_t> L1PreFiringWeight_Nom(myEventsReader, "L1PreFiringWeight_NomL");
        TTreeReaderValue<Float_t> L1PreFiringWeight_Dn(myEventsReader, "L1PreFiringWeight_DnL");
        TTreeReaderValue<Float_t> L1PreFiringWeight_Up(myEventsReader, "L1PreFiringWeight_UpL");
        //PileUp number of interactions
        TTreeReaderValue<Float_t> Pileup_nTrueInt(myEventsReader, "Pileup_nTrueIntL");
        TTreeReaderValue<Int_t> Pileup_nPU(myEventsReader, "Pileup_nPUL");
        //PSWeight
        TTreeReaderValue<UInt_t> nPSWeight(myEventsReader, "nPSWeightL");
        TTreeReaderArray<Float_t> PSWeight(myEventsReader, "PSWeightL");
        //LHE Scale Weight
        TTreeReaderValue<UInt_t> nLHEScaleWeight(myEventsReader, "nLHEScaleWeightL");
        TTreeReaderArray<Float_t> LHEScaleWeight(myEventsReader, "LHEScaleWeightL");
        //LHE PDF Weight
        TTreeReaderValue<UInt_t> nLHEPdfWeight(myEventsReader, "nLHEPdfWeightL");
        TTreeReaderArray<Float_t> LHEPdfWeight(myEventsReader, "LHEPdfWeightL");
        TTreeReaderValue<Float_t> LHEWeight_originalXWGTUP(myEventsReader, "LHEWeight_originalXWGTUPL");
        //gen weights and weight sums
        TTreeReaderValue<Float_t> Generator_weight(myEventsReader, "Generator_weightL");

        //05052024 Additions for PN regress mass scaling and resolution corrections
        TTreeReaderValue<UInt_t> luminosityBlock(myEventsReader, "luminosityBlockL");
        TTreeReaderValue<ULong64_t> event(myEventsReader, "eventL");


        TTreeReader myEvNumReader("evNumTree", tmpfile);
        TTreeReaderValue<UInt_t> nEvHLT(myEvNumReader, "nEv");
        TTreeReaderValue<UInt_t> nEvPassHLT(myEvNumReader, "nEvPass");

        //Transferring run tree
        TTreeReader myRunsReader("runTree", tmpfile);
        TTreeReaderValue<UInt_t> run(myRunsReader, "runL");
        TTreeReaderValue<UInt_t> nLHEPdfSumw(myRunsReader, "nLHEPdfSumwL");
        TTreeReaderArray<Double_t> LHEPdfSumw(myRunsReader, "LHEPdfSumwL");
        TTreeReaderValue<UInt_t> nLHEScaleSumw(myRunsReader, "nLHEScaleSumwL");
        TTreeReaderArray<Double_t> LHEScaleSumw(myRunsReader, "LHEScaleSumwL");
        TTreeReaderValue<UInt_t> nLHEReweightingSumw(myRunsReader, "nLHEReweightingSumwL");
        TTreeReaderArray<Double_t> LHEReweightingSumw(myRunsReader, "LHEReweightingSumwL");
        TTreeReaderValue<Long64_t> genEventCount(myRunsReader, "genEventCountL");
        TTreeReaderValue<Double_t> genEventSumw(myRunsReader, "genEventSumwL");
        TTreeReaderValue<Double_t> genEventSumw2(myRunsReader, "genEventSumw2L");

        Long64_t eventLoopMax = myRunsReader.GetEntries();
        UInt_t tmpRunsInt = 0;
        while (myRunsReader.Next()){
            runL = *run;
            nLHEPdfSumwL = *nLHEPdfSumw;
            for (UInt_t i = 0; i < nLHEPdfSumwL; i++){
                LHEPdfSumwL.push_back(LHEPdfSumw[i]);
            }
            nLHEScaleSumwL = *nLHEScaleSumw;
            for (UInt_t i = 0; i < nLHEScaleSumwL; i++){
                LHEScaleSumwL.push_back(LHEScaleSumw[i]);
            }
            nLHEReweightingSumwL = *nLHEReweightingSumw;
            for (UInt_t i = 0; i < nLHEReweightingSumwL; i++){
                LHEReweightingSumwL.push_back(LHEReweightingSumw[i]);
            }
            genEventCountL = *genEventCount;
            genEventSumwL = *genEventSumw;
            genEventSumw2L = *genEventSumw2;
            tmpRunsInt += 1;
            runTree->Fill();
            //clear run tree vectors
            LHEPdfSumwL.clear();
            LHEScaleSumwL.clear();
            LHEReweightingSumwL.clear();

        }
        std::cout << "Run loop for file " << k << " done. RunsInt " << tmpRunsInt <<"\n";

        //Transferring weight sums tree
        TTreeReader myWeightSumReader("weightSumsTree", tmpfile);
        TTreeReaderValue<Float_t> Generator_weightSum(myWeightSumReader, "Generator_weightSumL");
        TTreeReaderValue<UInt_t> nLHEPdfWeightSum(myWeightSumReader, "nLHEPdfWeightSumL");
        TTreeReaderArray<Float_t> LHEPdfWeightSum(myWeightSumReader, "LHEPdfWeightSumL");
        TTreeReaderValue<UInt_t> nLHEReweightingWeightSum(myWeightSumReader, "nLHEReweightingWeightSumL");
        TTreeReaderArray<Float_t> LHEReweightingWeightSum(myWeightSumReader, "LHEReweightingWeightSumL");
        TTreeReaderValue<Float_t> LHEWeight_originalXWGTUPSum(myWeightSumReader, "LHEWeight_originalXWGTUPSumL");
        TTreeReaderValue<Float_t> genWeightSum(myWeightSumReader, "genWeightSumL");

        Long64_t eventWeightSumLoopMax = myWeightSumReader.GetEntries();
        UInt_t tmpWeightSumInt = 0;
        while (myWeightSumReader.Next()){
            Generator_weightSumL = *Generator_weightSum;
            nLHEPdfWeightSumL = *nLHEPdfWeightSum;
            for (UInt_t i = 0; i < nLHEPdfWeightSumL; i++){
                LHEPdfWeightSumL.push_back(LHEPdfWeightSum[i]);
            }
            nLHEReweightingWeightSumL = *nLHEReweightingWeightSum;
            for (UInt_t i = 0; i < nLHEReweightingWeightSumL; i++){
                LHEReweightingWeightSumL.push_back(LHEReweightingWeightSum[i]);
            }
            LHEWeight_originalXWGTUPSumL = *LHEWeight_originalXWGTUPSum;
            genWeightSumL = *genWeightSum;
            tmpWeightSumInt += 1;
            weightSumsTree->Fill();
            //clear weight sums tree vectors
            LHEPdfWeightSumL.clear();
            LHEReweightingWeightSumL.clear();
        }

        std::cout << "Weight sum loop for file " << k << " done. WeightSumInt " << tmpWeightSumInt <<"\n";





        
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
                std::cout << evCount+1 << " starting muon loop\n";
            }
            //Increment event count
            evRunOver += 1;
            evCount += 1;


            std::vector<Float_t> rochMomCorrections;
            //Loop through muons and calculate default rochester correction
            for (int i = 0; i < *nMuon; i++){
                muCount += 1;
                int genPartIdx = Muon_genPartIdx[i];
                double mcSF;
                int charge = Muon_charge[i];
                float pt = Muon_pt[i];
                float eta = Muon_eta[i];
                float phi = Muon_phi[i];
                int nl = Muon_nTrackerLayers[i];

                //Get gRandom for function
                float u = gRandom->Rndm();
                //Check if muon has a genmatch
                if (genPartIdx == -1) {
                    //no gen match, use kSmearMC with random u
                    mcSF = rc.kSmearMC(charge, pt, eta, phi, nl, u, 0, 0);
                }
                else{
                    float genPt = GenPart_pt[genPartIdx];
                    //Get rochester correction with kSpreadMC
                    mcSF = rc.kSpreadMC(charge, pt, eta, phi, genPt, 0, 0);
                }
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

            //Loop through gen jets and add each p4 to a vector
            std::vector<LorentzVector> genJetP4s;
            for (UInt_t nGenJetItr=0; nGenJetItr<*nGenJet;nGenJetItr++){
                LorentzVector p4(GenJet_pt[nGenJetItr],GenJet_eta[nGenJetItr],GenJet_phi[nGenJetItr],GenJet_mass[nGenJetItr]);
                genJetP4s.push_back(p4);
            }
            //Loop through gen AK8 jets and add each p4 to a vector
            std::vector<LorentzVector> genAK8JetP4s;
            for (UInt_t nGenJetAK8Itr=0; nGenJetAK8Itr<*nGenJetAK8;nGenJetAK8Itr++){
                LorentzVector p4(GenJetAK8_pt[nGenJetAK8Itr],GenJetAK8_eta[nGenJetAK8Itr],GenJetAK8_phi[nGenJetAK8Itr],GenJetAK8_mass[nGenJetAK8Itr]);
                genAK8JetP4s.push_back(p4);
            }


            //Initialize TRandom3 for JER smearing
            TRandom3* rand = new TRandom3(0);


            //Do JER corrections for jets
            //Loop through jets, make lorentz vector, use "getJetEta", etc, methods to give jetResUncCHS jet variables
            //give p4 to jetResUncCHS's applyJER method, fill branch vectors with resulting altered p4
            //Do mid, up, and down
            for (UInt_t nJetItr=0; nJetItr<*nJet;nJetItr++){
                LorentzVector p4Mid(Jet_pt[nJetItr],Jet_eta[nJetItr],Jet_phi[nJetItr],Jet_mass[nJetItr]);
                jetResUncCHS.setJetEta(Jet_eta[nJetItr]);
                jetResUncCHS.setJetPt(Jet_pt[nJetItr]);
                jetResUncCHS.setRho(*fixedGridRhoFastjetAll);
                jetResUncCHS.applyJER(p4Mid,1,genJetP4s,*rand); //Alters jetp4, so store in branch. need to do this for up/down also (2 and -2)
                LorentzVector p4Up(Jet_pt[nJetItr],Jet_eta[nJetItr],Jet_phi[nJetItr],Jet_mass[nJetItr]);
                jetResUncCHS.setJetEta(Jet_eta[nJetItr]);
                jetResUncCHS.setJetPt(Jet_pt[nJetItr]);
                jetResUncCHS.setRho(*fixedGridRhoFastjetAll);
                jetResUncCHS.applyJER(p4Up,2,genJetP4s,*rand);
                LorentzVector p4Down(Jet_pt[nJetItr],Jet_eta[nJetItr],Jet_phi[nJetItr],Jet_mass[nJetItr]);
                jetResUncCHS.setJetEta(Jet_eta[nJetItr]);
                jetResUncCHS.setJetPt(Jet_pt[nJetItr]);
                jetResUncCHS.setRho(*fixedGridRhoFastjetAll);
                jetResUncCHS.applyJER(p4Down,-2,genJetP4s,*rand);
                //Store p4s in branch vectors
                Jet_eta_JERMidL.push_back(p4Mid.Eta());
                Jet_pt_JERMidL.push_back(p4Mid.Pt());
                Jet_phi_JERMidL.push_back(p4Mid.Phi());
                Jet_mass_JERMidL.push_back(p4Mid.M());
                Jet_eta_JERUpL.push_back(p4Up.Eta());
                Jet_pt_JERUpL.push_back(p4Up.Pt());
                Jet_phi_JERUpL.push_back(p4Up.Phi());
                Jet_mass_JERUpL.push_back(p4Up.M());
                Jet_eta_JERDownL.push_back(p4Down.Eta());
                Jet_pt_JERDownL.push_back(p4Down.Pt());
                Jet_phi_JERDownL.push_back(p4Down.Phi());
                Jet_mass_JERDownL.push_back(p4Down.M());
            }

            //Do JER corrections for fat jets
            for (UInt_t nFatJetItr=0; nFatJetItr<*nFatJet;nFatJetItr++){
                LorentzVector p4Mid(FatJet_pt[nFatJetItr],FatJet_eta[nFatJetItr],FatJet_phi[nFatJetItr],FatJet_mass[nFatJetItr]);
                jetResUncCHS.setJetEta(FatJet_eta[nFatJetItr]);
                jetResUncCHS.setJetPt(FatJet_pt[nFatJetItr]);
                jetResUncCHS.setRho(*fixedGridRhoFastjetAll);
                jetResUncCHS.applyJER(p4Mid,1,genAK8JetP4s,*rand); //Alters jetp4, so store in branch. need to do this for up/down also (2 and -2)
                LorentzVector p4Up(FatJet_pt[nFatJetItr],FatJet_eta[nFatJetItr],FatJet_phi[nFatJetItr],FatJet_mass[nFatJetItr]);
                jetResUncCHS.setJetEta(FatJet_eta[nFatJetItr]);
                jetResUncCHS.setJetPt(FatJet_pt[nFatJetItr]);
                jetResUncCHS.setRho(*fixedGridRhoFastjetAll);
                jetResUncCHS.applyJER(p4Up,2,genAK8JetP4s,*rand);
                LorentzVector p4Down(FatJet_pt[nFatJetItr],FatJet_eta[nFatJetItr],FatJet_phi[nFatJetItr],FatJet_mass[nFatJetItr]);
                jetResUncCHS.setJetEta(FatJet_eta[nFatJetItr]);
                jetResUncCHS.setJetPt(FatJet_pt[nFatJetItr]);
                jetResUncCHS.setRho(*fixedGridRhoFastjetAll);
                jetResUncCHS.applyJER(p4Down,-2,genAK8JetP4s,*rand);
                //Store p4s in branch vectors
                FatJet_eta_JERMidL.push_back(p4Mid.Eta());
                FatJet_pt_JERMidL.push_back(p4Mid.Pt());
                FatJet_phi_JERMidL.push_back(p4Mid.Phi());
                FatJet_mass_JERMidL.push_back(p4Mid.M());
                FatJet_eta_JERUpL.push_back(p4Up.Eta());
                FatJet_pt_JERUpL.push_back(p4Up.Pt());
                FatJet_phi_JERUpL.push_back(p4Up.Phi());
                FatJet_mass_JERUpL.push_back(p4Up.M());
                FatJet_eta_JERDownL.push_back(p4Down.Eta());
                FatJet_pt_JERDownL.push_back(p4Down.Pt());
                FatJet_phi_JERDownL.push_back(p4Down.Phi());
                FatJet_mass_JERDownL.push_back(p4Down.M());

                //05052024 adding JMS and JMR corrections
                //050502024 Adding the PN regress mass scaling, resolution, and uncertainty
                //Using double the scale/resolution values for the Up variation
                //using 0% (no change) for the Down variation
                float scaleValNom = 1.0 + PNRegMassJMSAr[yearType];
                float scaleValUp = 1.0 + (2*PNRegMassJMSAr[yearType]);

                float PNRegMasJMSCorNom = massScale(FatJet_particleNet_mass[nFatJetItr],scaleValNom);
                float PNRegMasJMSCorUp = massScale(FatJet_particleNet_mass[nFatJetItr],scaleValUp);
                float PNRegMasJMSCorDown = FatJet_particleNet_mass[nFatJetItr];

                float resSmearNom = PNRegMassJMRAr[yearType];
                float resSmearUp = (2*PNRegMassJMRAr[yearType]);

                float PNRegMasJMSNomJMRNomCor = massSmear(PNRegMasJMSCorNom,*luminosityBlock,*event,resSmearNom);

                float PNRegMasJMSUpJMRNomCor = massSmear(PNRegMasJMSCorUp,*luminosityBlock,*event,resSmearNom);
                float PNRegMasJMSDownJMRNomCor = massSmear(PNRegMasJMSCorDown,*luminosityBlock,*event,resSmearNom);

                float PNRegMasJMSNomJMRUpCor = massSmear(PNRegMasJMSCorNom,*luminosityBlock,*event,resSmearUp);
                float PNRegMasJMSNomJMRDownCor = PNRegMasJMSCorNom;


                FatJet_particleNet_mass_JMSNomJMRNomCorL.push_back(PNRegMasJMSNomJMRNomCor);
                FatJet_particleNet_mass_JMSUpJMRNomCorL.push_back(PNRegMasJMSUpJMRNomCor);
                FatJet_particleNet_mass_JMSDownJMRNomCorL.push_back(PNRegMasJMSDownJMRNomCor);
                FatJet_particleNet_mass_JMSNomJMRUpCorL.push_back(PNRegMasJMSNomJMRUpCor);
                FatJet_particleNet_mass_JMSNomJMRDownCorL.push_back(PNRegMasJMSNomJMRDownCor);
                






                
            }

            
            //Fill in all branches of TTree

            //Event reweighting
            if (debug){
                std::cout <<"Filling Reweighting\n";
            }
            nLHEReweightingWeightL = *nLHEReweightingWeight;
            for (UInt_t nLHEReweightingWeightItr=0; nLHEReweightingWeightItr<nLHEReweightingWeightL;nLHEReweightingWeightItr++){
                LHEReweightingWeightL.push_back(LHEReweightingWeight[nLHEReweightingWeightItr]);
            }

            genWeightL = *genWeight;

            
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
                Jet_hadronFlavourL.push_back(Jet_hadronFlavour[nJetItr]);
                Jet_genJetIdxL.push_back(Jet_genJetIdx[nJetItr]);


            }
            fixedGridRhoFastjetAllL = *fixedGridRhoFastjetAll;

            //GenJets

            if (debug){
                std::cout <<"Filling GenJets\n";
            }
            nGenJetL = *nGenJet;
            for (UInt_t nGenJetItr=0; nGenJetItr<nGenJetL;nGenJetItr++){
                GenJet_etaL.push_back(GenJet_eta[nGenJetItr]);
                GenJet_ptL.push_back(GenJet_pt[nGenJetItr]);
                GenJet_phiL.push_back(GenJet_phi[nGenJetItr]);
                GenJet_massL.push_back(GenJet_mass[nGenJetItr]);
                GenJet_hadronFlavourL.push_back(GenJet_hadronFlavour[nGenJetItr]);
            }

            //GenJetAK8

            if (debug){
                std::cout <<"Filling GenJetAK8\n";
            }
            nGenJetAK8L = *nGenJetAK8;
            for (UInt_t nGenJetAK8Itr=0; nGenJetAK8Itr<nGenJetAK8L;nGenJetAK8Itr++){
                GenJetAK8_etaL.push_back(GenJetAK8_eta[nGenJetAK8Itr]);
                GenJetAK8_ptL.push_back(GenJetAK8_pt[nGenJetAK8Itr]);
                GenJetAK8_phiL.push_back(GenJetAK8_phi[nGenJetAK8Itr]);
                GenJetAK8_massL.push_back(GenJetAK8_mass[nGenJetAK8Itr]);
                GenJetAK8_hadronFlavourL.push_back(GenJetAK8_hadronFlavour[nGenJetAK8Itr]);
            }

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
                FatJet_hadronFlavourL.push_back(FatJet_hadronFlavour[nFatJetItr]);
                



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
                Muon_genPartIdxL.push_back(Muon_genPartIdx[nMuonItr]);
                
            }

            fixedGridRhoFastjetAllL = *fixedGridRhoFastjetAll;

            //GenParticles
            if (debug){
                std::cout <<"Filling GenParticles\n";
            }
            nGenPartL = *nGenPart;
            for (UInt_t nGenPartItr=0; nGenPartItr<nGenPartL;nGenPartItr++){
                GenPart_etaL.push_back(GenPart_eta[nGenPartItr]);
                GenPart_massL.push_back(GenPart_mass[nGenPartItr]);
                GenPart_phiL.push_back(GenPart_phi[nGenPartItr]);
                GenPart_ptL.push_back(GenPart_pt[nGenPartItr]);
                GenPart_genPartIdxMotherL.push_back(GenPart_genPartIdxMother[nGenPartItr]);
                GenPart_pdgIdL.push_back(GenPart_pdgId[nGenPartItr]);
                GenPart_statusL.push_back(GenPart_status[nGenPartItr]);
                GenPart_statusFlagsL.push_back(GenPart_statusFlags[nGenPartItr]);
            }

            //GenChannel
            if (debug){
                std::cout <<"Filling GenChannel\n";
            }
            genChannelL = *genChannel;


            //HTobbBool
            HTobbBoolL = *HTobbBool;

            //FJ GENMATCH

            if (debug){
                std::cout <<"Filling FJGenMatch\n";
            }
            ZFJIndL = *ZFJInd;
            HFJIndL = *HFJInd;
            goodGenZFJMatchL = *goodGenZFJMatch;
            goodGenHFJMatchL = *goodGenHFJMatch;
            goodZFJMatchToGenL = *goodZFJMatchToGen;
            goodHFJMatchToGenL = *goodHFJMatchToGen;
            eventGenSemileptonicL = *eventGenSemileptonic;
            eventGenHToBBL = *eventGenHToBB;
            ZFJGenHadronFlavourL = *ZFJGenHadronFlavour;
            HFJGenHadronFlavourL = *HFJGenHadronFlavour;

            nHDecayPIDL = *nHDecayPID;
            for (UInt_t nHDecayPIDItr=0; nHDecayPIDItr<nHDecayPIDL;nHDecayPIDItr++){
                HDecayPIDL.push_back(HDecayPID[nHDecayPIDItr]);
            }

            nZOneDecayPIDL = *nZOneDecayPID;
            for (UInt_t nZOneDecayPIDItr=0; nZOneDecayPIDItr<nZOneDecayPIDL;nZOneDecayPIDItr++){
                ZOneDecayPIDL.push_back(ZOneDecayPID[nZOneDecayPIDItr]);
            }

            nZTwoDecayPIDL = *nZTwoDecayPID;
            for (UInt_t nZTwoDecayPIDItr=0; nZTwoDecayPIDItr<nZTwoDecayPIDL;nZTwoDecayPIDItr++){
                ZTwoDecayPIDL.push_back(ZTwoDecayPID[nZTwoDecayPIDItr]);
            }

            ZOneTypeL = *ZOneType;
            ZTwoTypeL = *ZTwoType;

            //HLT 
            HLT_Ele32_WPTight_Gsf_L1DoubleEGL = *HLT_Ele32_WPTight_Gsf_L1DoubleEG;
            HLT_IsoMu27L = *HLT_IsoMu27;
            HLT_Mu50L = *HLT_Mu50;
            HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZL = *HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;
            HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8L = *HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8;

            HLT_Ele27_WPTight_GsfL = *HLT_Ele27_WPTight_Gsf;
            HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZL = *HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ;

            HLT_IsoMu24L = *HLT_IsoMu24;
            HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVLL = *HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL;
            HLT_IsoTkMu24L = *HLT_IsoTkMu24;

            //042024SFAndSuchAdditions
            //PU JetID
            for (UInt_t nJetItr=0; nJetItr<nJetL;nJetItr++){
                Jet_puIdL.push_back(Jet_puId[nJetItr]);
            }
            //L1 Prefiring Weights
            L1PreFiringWeight_NomL = *L1PreFiringWeight_Nom;
            L1PreFiringWeight_DnL = *L1PreFiringWeight_Dn;
            L1PreFiringWeight_UpL = *L1PreFiringWeight_Up;
            //PileUp number of interactions
            Pileup_nTrueIntL = *Pileup_nTrueInt;
            Pileup_nPUL = *Pileup_nPU;
            //PSWeight
            nPSWeightL = *nPSWeight;
            for (UInt_t nPSWeightItr=0; nPSWeightItr<nPSWeightL;nPSWeightItr++){
                PSWeightL.push_back(PSWeight[nPSWeightItr]);
            }
            //LHE Scale Weight
            nLHEScaleWeightL = *nLHEScaleWeight;
            for (UInt_t nLHEScaleWeightItr=0; nLHEScaleWeightItr<nLHEScaleWeightL;nLHEScaleWeightItr++){
                LHEScaleWeightL.push_back(LHEScaleWeight[nLHEScaleWeightItr]);
            }
            //LHE PDF Weight
            nLHEPdfWeightL = *nLHEPdfWeight;
            for (UInt_t nLHEPdfWeightItr=0; nLHEPdfWeightItr<nLHEPdfWeightL;nLHEPdfWeightItr++){
                LHEPdfWeightL.push_back(LHEPdfWeight[nLHEPdfWeightItr]);
            }
            LHEWeight_originalXWGTUPL = *LHEWeight_originalXWGTUP;
            //generator weight
            Generator_weightL = *Generator_weight;

            //05052024 Additions for PN regress mass scaling and resolution corrections
            luminosityBlockL = *luminosityBlock;
            eventL = *event;




            FilteredEventsTree->Fill();

            //Clear all vectors
            LHEReweightingWeightL.clear();


            Jet_etaL.clear();
            Jet_ptL.clear();
            Jet_phiL.clear();
            Jet_massL.clear();
            Jet_jetIdL.clear();
            Jet_btagDeepFlavBL.clear();
            Jet_hadronFlavourL.clear();
            Jet_genJetIdxL.clear();
            Jet_eta_JERMidL.clear();
            Jet_pt_JERMidL.clear();
            Jet_phi_JERMidL.clear();
            Jet_mass_JERMidL.clear();
             Jet_eta_JERUpL.clear();
            Jet_pt_JERUpL.clear();
            Jet_phi_JERUpL.clear();
            Jet_mass_JERUpL.clear();
            Jet_eta_JERDownL.clear();
            Jet_pt_JERDownL.clear();
            Jet_phi_JERDownL.clear();
            Jet_mass_JERDownL.clear();

            GenJet_etaL.clear();
            GenJet_ptL.clear();
            GenJet_phiL.clear();
            GenJet_massL.clear();
            GenJet_hadronFlavourL.clear();

            GenJetAK8_etaL.clear();
            GenJetAK8_ptL.clear();
            GenJetAK8_phiL.clear();
            GenJetAK8_massL.clear();
            GenJetAK8_hadronFlavourL.clear();


            FatJet_etaL.clear();
            FatJet_ptL.clear();
            FatJet_phiL.clear();
            FatJet_massL.clear();
            FatJet_jetIdL.clear();
            FatJet_deepTag_HL.clear();
            FatJet_deepTag_ZvsQCDL.clear();
            FatJet_msoftdropL.clear();
            FatJet_particleNet_massL.clear();
            FatJet_eta_JERMidL.clear();
            FatJet_pt_JERMidL.clear();
            FatJet_phi_JERMidL.clear();
            FatJet_mass_JERMidL.clear();
             FatJet_eta_JERUpL.clear();
            FatJet_pt_JERUpL.clear();
            FatJet_phi_JERUpL.clear();
            FatJet_mass_JERUpL.clear();
            FatJet_eta_JERDownL.clear();
            FatJet_pt_JERDownL.clear();
            FatJet_phi_JERDownL.clear();
            FatJet_mass_JERDownL.clear();

            FatJet_hadronFlavourL.clear();

            GenPart_etaL.clear();
            GenPart_massL.clear();
            GenPart_phiL.clear();
            GenPart_ptL.clear();
            GenPart_genPartIdxMotherL.clear();
            GenPart_pdgIdL.clear();
            GenPart_statusL.clear();
            GenPart_statusFlagsL.clear();


            

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
            Muon_genPartIdxL.clear();
            Muon_RochMomCorrectionsL.clear();
            Muon_ptCorrectedL.clear();

            FatJet_particleNet_HbbvsQCDL.clear();
            FatJet_particleNet_ZvsQCDL.clear();

            FatJet_particleNetMD_QCDL.clear();
            FatJet_particleNetMD_XbbL.clear();
            FatJet_particleNetMD_XccL.clear();
            FatJet_particleNetMD_XqqL.clear();

            HDecayPIDL.clear();
            ZOneDecayPIDL.clear();
            ZTwoDecayPIDL.clear();

            Jet_puIdL.clear();

            PSWeightL.clear();
            LHEScaleWeightL.clear();
            LHEPdfWeightL.clear();

            //05052024 Additions for PN regress mass scaling and resolution corrections
            FatJet_particleNet_mass_JMSNomJMRNomCorL.clear();
            FatJet_particleNet_mass_JMSUpJMRNomCorL.clear();
            FatJet_particleNet_mass_JMSDownJMRNomCorL.clear();
            FatJet_particleNet_mass_JMSNomJMRUpCorL.clear();
            FatJet_particleNet_mass_JMSNomJMRDownCorL.clear();



        }
        //Loop over and fill evNumTree variables
        while (myEvNumReader.Next()){
            nEv = *nEvHLT;
            nEvPass = *nEvPassHLT;
            evNumTree->Fill();
            datanEv += *nEvHLT;
            datanEvPass += *nEvPassHLT;
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
    weightSumsTree->Write("",TObject::kOverwrite);
    runTree->Write("",TObject::kOverwrite);
    FilteredEventsTree->Write("",TObject::kOverwrite);
    rochesterCorrHist->Write("",TObject::kOverwrite);

    outFile->Close();
    

    delete outFile;

}