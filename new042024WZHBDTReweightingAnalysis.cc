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

//This version has the higgs being selected before the Z and the MDPN being used for selection
void new042024WZHBDTReweightingAnalysis(string datasetString, int JECCorInd, bool JECCorUpOrDown,  int RochInd, int JERInd){
    // Open the file. Note that the name of your file outside this class
    // will probably NOT be experiment.root.
    std::cout << "start Analysis\n";
    clock_t startt = clock();
    //Analyzer will run over all files put into fileAr

    std::vector<std::string> fileAr;

    string NoSLString = "";
    if (!useSingleLepHLT){
        NoSLString = "_NoSLHLT";
    }


    std::string saveName;
    float crossSection;
    bool isBackground = false;
    bool isMariaSignal = false;

    if (datasetString == "testRun") testRun = true;
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

    if (datasetString == "LaraTest") LaraTest = true;

    ////////////////////////////////GETTING DATASET////////////////////////////////
    ////////////////////////////////GETTING DATASET////////////////////////////////
    ////////////////////////////////GETTING DATASET////////////////////////////////
    ////////////////////////////////GETTING DATASET////////////////////////////////

    float totWeight = 1;
    //precalculate this
    double XS = 1;

    UInt_t datasetType = 25;
    UInt_t yearType = 0;


    
    if (SDC2V2MCWZHReweightTrimmed){
        saveName = "SDC2V2MCWZHReweightTrimmed";
        //totWeight = ;
        //XS = ;
        isBackground = false;
        std::string tmpStrWithPath = "/scratch365/dlutton/HLT042024WithPreSel/HLTTrimmedFilteredForAnalysisSDC2V2MCWZHReweightTrimmed"+NoSLString+"_WithPreSel_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2V2MCWZH17ReweightTrimmed){
        saveName = "SDC2V2MCWZH17ReweightTrimmed";
        yearType = 1;
        //totWeight = ;
        //XS = ;
        isBackground = false;
        std::string tmpStrWithPath = "/scratch365/dlutton/HLT042024WithPreSel/HLTTrimmedFilteredForAnalysisSDC2V2MCWZH17ReweightTrimmed"+NoSLString+"_WithPreSel_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2V2MCWZH16ReweightTrimmed){
        saveName = "SDC2V2MCWZH16ReweightTrimmed";
        yearType = 2;
        //totWeight = ;
        //XS = ;
        isBackground = false;
        std::string tmpStrWithPath = "/scratch365/dlutton/HLT042024WithPreSel/HLTTrimmedFilteredForAnalysisSDC2V2MCWZH16ReweightTrimmed"+NoSLString+"_WithPreSel_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2V2MCWZH16APVReweightTrimmed){
        saveName = "SDC2V2MCWZH16APVReweightTrimmed";
        yearType = 3;
        //totWeight = ;
        //XS = ;
        isBackground = false;
        std::string tmpStrWithPath = "/scratch365/dlutton/HLT042024WithPreSel/HLTTrimmedFilteredForAnalysisSDC2V2MCWZH16APVReweightTrimmed"+NoSLString+"_WithPreSel_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2V2MCWWHSSReweightTrimmed){
        saveName = "SDC2V2MCWWHSSReweightTrimmed";
        //totWeight = ;
        //XS = ;
        UInt_t datasetType = 91;
        isBackground = false;
        std::string tmpStrWithPath = "/scratch365/dlutton/HLT042024WithPreSel/HLTTrimmedFilteredForAnalysisSDC2V2MCWWHSSReweightTrimmed"+NoSLString+"_WithPreSel_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2V2MCWWHSS17ReweightTrimmed){
        saveName = "SDC2V2MCWWHSS17ReweightTrimmed";
        yearType = 1;
        //totWeight = ;
        //XS = ;
        UInt_t datasetType = 91;
        isBackground = false;
        std::string tmpStrWithPath = "/scratch365/dlutton/HLT042024WithPreSel/HLTTrimmedFilteredForAnalysisSDC2V2MCWWHSS17ReweightTrimmed"+NoSLString+"_WithPreSel_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2V2MCWWHSS16ReweightTrimmed){
        saveName = "SDC2V2MCWWHSS16ReweightTrimmed";
        yearType = 2;
        //totWeight = ;
        //XS = ;
        UInt_t datasetType = 91;
        isBackground = false;
        std::string tmpStrWithPath = "/scratch365/dlutton/HLT042024WithPreSel/HLTTrimmedFilteredForAnalysisSDC2V2MCWWHSS16ReweightTrimmed"+NoSLString+"_WithPreSel_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2V2MCWWHSS16APVReweightTrimmed){
        saveName = "SDC2V2MCWWHSS16APVReweightTrimmed";
        yearType = 3;
        //totWeight = ;
        //XS = ;
        UInt_t datasetType = 91;
        isBackground = false;
        std::string tmpStrWithPath = "/scratch365/dlutton/HLT042024WithPreSel/HLTTrimmedFilteredForAnalysisSDC2V2MCWWHSS16APVReweightTrimmed"+NoSLString+"_WithPreSel_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2V2MCWWHOSReweightTrimmed){
        saveName = "SDC2V2MCWWHOSReweightTrimmed";
        //totWeight = ;
        //XS = ;
        UInt_t datasetType = 92;
        isBackground = false;
        std::string tmpStrWithPath = "/scratch365/dlutton/HLT042024WithPreSel/HLTTrimmedFilteredForAnalysisSDC2V2MCWWHOSReweightTrimmed"+NoSLString+"_WithPreSel_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2V2MCWWHOS17ReweightTrimmed){
        saveName = "SDC2V2MCWWHOS17ReweightTrimmed";
        yearType = 1;
        //totWeight = ;
        //XS = ;
        UInt_t datasetType = 92;
        isBackground = false;
        std::string tmpStrWithPath = "/scratch365/dlutton/HLT042024WithPreSel/HLTTrimmedFilteredForAnalysisSDC2V2MCWWHOS17ReweightTrimmed"+NoSLString+"_WithPreSel_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2V2MCWWHOS16ReweightTrimmed){
        saveName = "SDC2V2MCWWHOS16ReweightTrimmed";
        yearType = 2;
        //totWeight = ;
        //XS = ;
        UInt_t datasetType = 92;
        isBackground = false;
        std::string tmpStrWithPath = "/scratch365/dlutton/HLT042024WithPreSel/HLTTrimmedFilteredForAnalysisSDC2V2MCWWHOS16ReweightTrimmed"+NoSLString+"_WithPreSel_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2V2MCWWHOS16APVReweightTrimmed){
        saveName = "SDC2V2MCWWHOS16APVReweightTrimmed";
        yearType = 3;
        //totWeight = ;
        //XS = ;
        UInt_t datasetType = 92;
        isBackground = false;
        std::string tmpStrWithPath = "/scratch365/dlutton/HLT042024WithPreSel/HLTTrimmedFilteredForAnalysisSDC2V2MCWWHOS16APVReweightTrimmed"+NoSLString+"_WithPreSel_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (MaC2V2MCWZHReweightTrimmed){
        isMariaSignal = true;
        saveName = "MaC2V2MCWZHReweightTrimmed";
        //totWeight = ;
        //XS = ;
        isBackground = false;
        std::string tmpStrWithPath = "/scratch365/dlutton/HLT042024WithPreSel/HLTTrimmedFilteredForAnalysisMaC2V2MCWZHReweightTrimmed"+NoSLString+"_WithPreSel_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (MaC2V2MCWZH17ReweightTrimmed){
        isMariaSignal = true;
        saveName = "MaC2V2MCWZH17ReweightTrimmed";
        yearType = 1;
        //totWeight = ;
        //XS = ;
        isBackground = false;
        std::string tmpStrWithPath = "/scratch365/dlutton/HLT042024WithPreSel/HLTTrimmedFilteredForAnalysisMaC2V2MCWZH17ReweightTrimmed"+NoSLString+"_WithPreSel_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (MaC2V2MCWZH16ReweightTrimmed){
        isMariaSignal = true;
        saveName = "MaC2V2MCWZH16ReweightTrimmed";
        yearType = 2;
        //totWeight = ;
        //XS = ;
        isBackground = false;
        std::string tmpStrWithPath = "/scratch365/dlutton/HLT042024WithPreSel/HLTTrimmedFilteredForAnalysisMaC2V2MCWZH16ReweightTrimmed"+NoSLString+"_WithPreSel_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (MaC2V2MCWZH16APVReweightTrimmed){
        isMariaSignal = true;
        saveName = "MaC2V2MCWZH16APVReweightTrimmed";
        yearType = 3;
        //totWeight = ;
        //XS = ;
        isBackground = false;
        std::string tmpStrWithPath = "/scratch365/dlutton/HLT042024WithPreSel/HLTTrimmedFilteredForAnalysisMaC2V2MCWZH16APVReweightTrimmed"+NoSLString+"_WithPreSel_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (MaC2V2MCWWHSSReweightTrimmed){
        isMariaSignal = true;
        saveName = "MaC2V2MCWWHSSReweightTrimmed";
        //totWeight = ;
        //XS = ;
        UInt_t datasetType = 91;
        isBackground = false;
        std::string tmpStrWithPath = "/scratch365/dlutton/HLT042024WithPreSel/HLTTrimmedFilteredForAnalysisMaC2V2MCWWHSSReweightTrimmed"+NoSLString+"_WithPreSel_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (MaC2V2MCWWHSS17ReweightTrimmed){
        isMariaSignal = true;
        saveName = "MaC2V2MCWWHSS17ReweightTrimmed";
        yearType = 1;
        //totWeight = ;
        //XS = ;
        UInt_t datasetType = 91;
        isBackground = false;
        std::string tmpStrWithPath = "/scratch365/dlutton/HLT042024WithPreSel/HLTTrimmedFilteredForAnalysisMaC2V2MCWWHSS17ReweightTrimmed"+NoSLString+"_WithPreSel_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (MaC2V2MCWWHSS16ReweightTrimmed){
        isMariaSignal = true;
        saveName = "MaC2V2MCWWHSS16ReweightTrimmed";
        yearType = 2;
        //totWeight = ;
        //XS = ;
        UInt_t datasetType = 91;
        isBackground = false;
        std::string tmpStrWithPath = "/scratch365/dlutton/HLT042024WithPreSel/HLTTrimmedFilteredForAnalysisMaC2V2MCWWHSS16ReweightTrimmed"+NoSLString+"_WithPreSel_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (MaC2V2MCWWHSS16APVReweightTrimmed){
        isMariaSignal = true;
        saveName = "MaC2V2MCWWHSS16APVReweightTrimmed";
        yearType = 3;
        //totWeight = ;
        //XS = ;
        UInt_t datasetType = 91;
        isBackground = false;
        std::string tmpStrWithPath = "/scratch365/dlutton/HLT042024WithPreSel/HLTTrimmedFilteredForAnalysisMaC2V2MCWWHSS16APVReweightTrimmed"+NoSLString+"_WithPreSel_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (MaC2V2MCWWHOSReweightTrimmed){
        isMariaSignal = true;
        saveName = "MaC2V2MCWWHOSReweightTrimmed";
        //totWeight = ;
        //XS = ;
        UInt_t datasetType = 92;
        isBackground = false;
        std::string tmpStrWithPath = "/scratch365/dlutton/HLT042024WithPreSel/HLTTrimmedFilteredForAnalysisMaC2V2MCWWHOSReweightTrimmed"+NoSLString+"_WithPreSel_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (MaC2V2MCWWHOS17ReweightTrimmed){
        isMariaSignal = true;
        saveName = "MaC2V2MCWWHOS17ReweightTrimmed";
        yearType = 1;
        //totWeight = ;
        //XS = ;
        UInt_t datasetType = 92;
        isBackground = false;
        std::string tmpStrWithPath = "/scratch365/dlutton/HLT042024WithPreSel/HLTTrimmedFilteredForAnalysisMaC2V2MCWWHOS17ReweightTrimmed"+NoSLString+"_WithPreSel_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (MaC2V2MCWWHOS16ReweightTrimmed){
        isMariaSignal = true;
        saveName = "MaC2V2MCWWHOS16ReweightTrimmed";
        yearType = 2;
        //totWeight = ;
        //XS = ;
        UInt_t datasetType = 92;
        isBackground = false;
        std::string tmpStrWithPath = "/scratch365/dlutton/HLT042024WithPreSel/HLTTrimmedFilteredForAnalysisMaC2V2MCWWHOS16ReweightTrimmed"+NoSLString+"_WithPreSel_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (MaC2V2MCWWHOS16APVReweightTrimmed){
        isMariaSignal = true;
        saveName = "MaC2V2MCWWHOS16APVReweightTrimmed";
        yearType = 3;
        //totWeight = ;
        //XS = ;
        UInt_t datasetType = 92;
        isBackground = false;
        std::string tmpStrWithPath = "/scratch365/dlutton/HLT042024WithPreSel/HLTTrimmedFilteredForAnalysisMaC2V2MCWWHOS16APVReweightTrimmed"+NoSLString+"_WithPreSel_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (CenC2V2MCWZHReweightTrimmed){
        saveName = "CenC2V2MCWZHReweightTrimmed";
        //totWeight = ;
        //XS = ;
        isBackground = false;
        std::string tmpStrWithPath = "/scratch365/dlutton/HLT042024WithPreSel/HLTTrimmedFilteredForAnalysisCenC2V2MCWZHReweightTrimmed"+NoSLString+"_WithPreSel_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (CenC2V2MCWZH17ReweightTrimmed){
        saveName = "CenC2V2MCWZH17ReweightTrimmed";
        yearType = 1;
        //totWeight = ;
        //XS = ;
        isBackground = false;
        std::string tmpStrWithPath = "/scratch365/dlutton/HLT042024WithPreSel/HLTTrimmedFilteredForAnalysisCenC2V2MCWZH17ReweightTrimmed"+NoSLString+"_WithPreSel_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (CenC2V2MCWZH16ReweightTrimmed){
        saveName = "CenC2V2MCWZH16ReweightTrimmed";
        yearType = 2;
        //totWeight = ;
        //XS = ;
        isBackground = false;
        std::string tmpStrWithPath = "/scratch365/dlutton/HLT042024WithPreSel/HLTTrimmedFilteredForAnalysisCenC2V2MCWZH16ReweightTrimmed"+NoSLString+"_WithPreSel_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (CenC2V2MCWZH16APVReweightTrimmed){
        saveName = "CenC2V2MCWZH16APVReweightTrimmed";
        yearType = 3;
        //totWeight = ;
        //XS = ;
        isBackground = false;
        std::string tmpStrWithPath = "/scratch365/dlutton/HLT042024WithPreSel/HLTTrimmedFilteredForAnalysisCenC2V2MCWZH16APVReweightTrimmed"+NoSLString+"_WithPreSel_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (CenC2V2MCWWHSSReweightTrimmed){
        saveName = "CenC2V2MCWWHSSReweightTrimmed";
        //totWeight = ;
        //XS = ;
        UInt_t datasetType = 91;
        isBackground = false;
        std::string tmpStrWithPath = "/scratch365/dlutton/HLT042024WithPreSel/HLTTrimmedFilteredForAnalysisCenC2V2MCWWHSSReweightTrimmed"+NoSLString+"_WithPreSel_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (CenC2V2MCWWHSS17ReweightTrimmed){
        saveName = "CenC2V2MCWWHSS17ReweightTrimmed";
        yearType = 1;
        //totWeight = ;
        //XS = ;
        UInt_t datasetType = 91;
        isBackground = false;
        std::string tmpStrWithPath = "/scratch365/dlutton/HLT042024WithPreSel/HLTTrimmedFilteredForAnalysisCenC2V2MCWWHSS17ReweightTrimmed"+NoSLString+"_WithPreSel_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (CenC2V2MCWWHSS16ReweightTrimmed){
        saveName = "CenC2V2MCWWHSS16ReweightTrimmed";
        yearType = 2;
        //totWeight = ;
        //XS = ;
        UInt_t datasetType = 91;
        isBackground = false;
        std::string tmpStrWithPath = "/scratch365/dlutton/HLT042024WithPreSel/HLTTrimmedFilteredForAnalysisCenC2V2MCWWHSS16ReweightTrimmed"+NoSLString+"_WithPreSel_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (CenC2V2MCWWHSS16APVReweightTrimmed){
        saveName = "CenC2V2MCWWHSS16APVReweightTrimmed";
        yearType = 3;
        //totWeight = ;
        //XS = ;
        UInt_t datasetType = 91;
        isBackground = false;
        std::string tmpStrWithPath = "/scratch365/dlutton/HLT042024WithPreSel/HLTTrimmedFilteredForAnalysisCenC2V2MCWWHSS16APVReweightTrimmed"+NoSLString+"_WithPreSel_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (CenC2V2MCWWHOSReweightTrimmed){
        saveName = "CenC2V2MCWWHOSReweightTrimmed";
        //totWeight = ;
        //XS = ;
        UInt_t datasetType = 92;
        isBackground = false;
        std::string tmpStrWithPath = "/scratch365/dlutton/HLT042024WithPreSel/HLTTrimmedFilteredForAnalysisCenC2V2MCWWHOSReweightTrimmed"+NoSLString+"_WithPreSel_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (CenC2V2MCWWHOS17ReweightTrimmed){
        saveName = "CenC2V2MCWWHOS17ReweightTrimmed";
        yearType = 1;
        //totWeight = ;
        //XS = ;
        UInt_t datasetType = 92;
        isBackground = false;
        std::string tmpStrWithPath = "/scratch365/dlutton/HLT042024WithPreSel/HLTTrimmedFilteredForAnalysisCenC2V2MCWWHOS17ReweightTrimmed"+NoSLString+"_WithPreSel_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (CenC2V2MCWWHOS16ReweightTrimmed){
        saveName = "CenC2V2MCWWHOS16ReweightTrimmed";
        yearType = 2;
        //totWeight = ;
        //XS = ;
        UInt_t datasetType = 92;
        isBackground = false;
        std::string tmpStrWithPath = "/scratch365/dlutton/HLT042024WithPreSel/HLTTrimmedFilteredForAnalysisCenC2V2MCWWHOS16ReweightTrimmed"+NoSLString+"_WithPreSel_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (CenC2V2MCWWHOS16APVReweightTrimmed){
        saveName = "CenC2V2MCWWHOS16APVReweightTrimmed";
        yearType = 3;
        //totWeight = ;
        //XS = ;
        UInt_t datasetType = 92;
        isBackground = false;
        std::string tmpStrWithPath = "/scratch365/dlutton/HLT042024WithPreSel/HLTTrimmedFilteredForAnalysisCenC2V2MCWWHOS16APVReweightTrimmed"+NoSLString+"_WithPreSel_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (testRun){
        saveName = "testRun";
        fileAr.push_back("/scratch365/dlutton/HLT042024WithPreSel/HLTFilteredForAnalysistestRun_0.root");
        
        
        isBackground = false;
        totWeight = 1;
        
    }
    else{
        std::cout << "ERROR. NO INPUT DATASET NAME GIVEN\n";
    }

    if (!useSingleLepHLT){
        saveName = saveName+NoSLString;
    }

    std::cout << "Doing " << saveName << "\n";
    //Setting up outfile with variables for BDT
    
    std::string outFileStr = "new042024BDTAnalysis"+saveName+"_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root";
    std::cout << "OutFile: " << outFileStr << "\n";
    TFile *outFile = new TFile(outFileStr.c_str(),"RECREATE");
    

    ////////////////////////////////DEFINING TREES////////////////////////////////
    ////////////////////////////////DEFINING TREES////////////////////////////////
    ////////////////////////////////DEFINING TREES////////////////////////////////
    ////////////////////////////////DEFINING TREES////////////////////////////////

    ////////////////////////////////DEFINING COUNTERS////////////////////////////////
    ////////////////////////////////NEUTRAL COUNTERS////////////////////////////////

    UInt_t startingCtr = 0;

    UInt_t passHiggsFJCtr = 0;
    UInt_t passHiggsFJSemiLepCtr = 0;
    UInt_t passChannelCtr = 0;
    UInt_t passLepOrSemiLepChannelCtr = 0;
    UInt_t tryingSemiLepChannelCtr = 0;

    UInt_t passHiggsFJInSemiLepChannelCtr = 0;

    UInt_t passFJInSemiLepChannelCtr = 0;
    UInt_t passEnoughFJsInSemiLepChannelCtr = 0;
    UInt_t passLepCutInSemiLepChannelCtr = 0;
    UInt_t passSemiLepChannelCtr = 0;
    UInt_t passVBFJetBVetoCtr = 0;
    UInt_t passVBFJetBVetoSemiLepCtr = 0;
    UInt_t passVBFJetsCtr = 0;
    UInt_t passLepVetoCtr = 0;
    UInt_t passAsSemiLepCtr = 0;


    
    std::vector<std::string> C2VNameMaAr {"C2W_m2p0_C2Z_m2p0","C2W_m2p0_C2Z_m1p0","C2W_m2p0_C2Z_m0p5","C2W_m2p0_C2Z_0p0","C2W_m2p0_C2Z_0p5","C2W_m2p0_C2Z_1p0","C2W_m2p0_C2Z_1p5","C2W_m2p0_C2Z_2p0","C2W_m2p0_C2Z_2p5","C2W_m2p0_C2Z_3p0","C2W_m2p0_C2Z_4p0","C2W_m1p0_C2Z_m2p0","C2W_m1p0_C2Z_m1p0","C2W_m1p0_C2Z_m0p5","C2W_m1p0_C2Z_0p0","C2W_m1p0_C2Z_0p5","C2W_m1p0_C2Z_1p0","C2W_m1p0_C2Z_1p5","C2W_m1p0_C2Z_2p0","C2W_m1p0_C2Z_2p5","C2W_m1p0_C2Z_3p0","C2W_m1p0_C2Z_4p0","C2W_m0p5_C2Z_m2p0","C2W_m0p5_C2Z_m1p0","C2W_m0p5_C2Z_m0p5","C2W_m0p5_C2Z_0p0","C2W_m0p5_C2Z_0p5","C2W_m0p5_C2Z_1p0","C2W_m0p5_C2Z_1p5","C2W_m0p5_C2Z_2p0","C2W_m0p5_C2Z_2p5","C2W_m0p5_C2Z_3p0","C2W_m0p5_C2Z_4p0","C2W_0p0_C2Z_m2p0","C2W_0p0_C2Z_m1p0","C2W_0p0_C2Z_m0p5","C2W_0p0_C2Z_0p0","C2W_0p0_C2Z_0p5","C2W_0p0_C2Z_1p0","C2W_0p0_C2Z_1p5","C2W_0p0_C2Z_2p0","C2W_0p0_C2Z_2p5","C2W_0p0_C2Z_3p0","C2W_0p0_C2Z_4p0","C2W_0p5_C2Z_m2p0","C2W_0p5_C2Z_m1p0","C2W_0p5_C2Z_m0p5","C2W_0p5_C2Z_0p0","C2W_0p5_C2Z_0p5","C2W_0p5_C2Z_1p0","C2W_0p5_C2Z_1p5","C2W_0p5_C2Z_2p0","C2W_0p5_C2Z_2p5","C2W_0p5_C2Z_3p0","C2W_0p5_C2Z_4p0","C2W_1p0_C2Z_m2p0","C2W_1p0_C2Z_m1p0","C2W_1p0_C2Z_m0p5","C2W_1p0_C2Z_0p0","C2W_1p0_C2Z_0p5","C2W_1p0_C2Z_1p0","C2W_1p0_C2Z_1p5","C2W_1p0_C2Z_2p0","C2W_1p0_C2Z_2p5","C2W_1p0_C2Z_3p0","C2W_1p0_C2Z_4p0","C2W_1p5_C2Z_m2p0","C2W_1p5_C2Z_m1p0","C2W_1p5_C2Z_m0p5","C2W_1p5_C2Z_0p0","C2W_1p5_C2Z_0p5","C2W_1p5_C2Z_1p0","C2W_1p5_C2Z_1p5","C2W_1p5_C2Z_2p0","C2W_1p5_C2Z_2p5","C2W_1p5_C2Z_3p0","C2W_1p5_C2Z_4p0","C2W_2p0_C2Z_m2p0","C2W_2p0_C2Z_m1p0","C2W_2p0_C2Z_m0p5","C2W_2p0_C2Z_0p0","C2W_2p0_C2Z_0p5","C2W_2p0_C2Z_1p0","C2W_2p0_C2Z_1p5","C2W_2p0_C2Z_2p5","C2W_2p0_C2Z_3p0","C2W_2p0_C2Z_4p0","C2W_2p5_C2Z_m2p0","C2W_2p5_C2Z_m1p0","C2W_2p5_C2Z_m0p5","C2W_2p5_C2Z_0p0","C2W_2p5_C2Z_0p5","C2W_2p5_C2Z_1p0","C2W_2p5_C2Z_1p5","C2W_2p5_C2Z_2p0","C2W_2p5_C2Z_2p5","C2W_2p5_C2Z_3p0","C2W_2p5_C2Z_4p0","C2W_3p0_C2Z_m2p0","C2W_3p0_C2Z_m1p0","C2W_3p0_C2Z_m0p5","C2W_3p0_C2Z_0p0","C2W_3p0_C2Z_0p5","C2W_3p0_C2Z_1p0","C2W_3p0_C2Z_1p5","C2W_3p0_C2Z_2p0","C2W_3p0_C2Z_2p5","C2W_3p0_C2Z_3p0","C2W_3p0_C2Z_4p0","C2W_4p0_C2Z_m2p0","C2W_4p0_C2Z_m1p0","C2W_4p0_C2Z_m0p5","C2W_4p0_C2Z_0p0","C2W_4p0_C2Z_0p5","C2W_4p0_C2Z_1p0","C2W_4p0_C2Z_1p5","C2W_4p0_C2Z_2p0","C2W_4p0_C2Z_2p5","C2W_4p0_C2Z_3p0","C2W_4p0_C2Z_4p0"};
    std::vector<std::string> C2VNameAr {"-2.0","-1.75","-1.5","-1.25","-1.0","-0.75","-0.5","-0.25","0.0","0.1","0.2","0.3","0.4","0.5","0.6","0.7","0.8","0.9","1.0","1.1","1.2","1.3","1.4","1.5","1.6","1.7","1.8","1.9","2.25","2.5","2.75","3.0","3.25","3.5","3.75","4.0"};
    std::vector<std::string> htobbNameAr {"HTobb","NoHTobb"};
    //std::vector<std::string> typeNameAr {"","GenLep","GenSemiLep","GenHad","GenOther"};
    //std::vector<std::string> typeNameAltAr {"GenLep","GenSemiLep","GenHad","GenOther"};
    uint C2VLen = 37;
    uint C2VMaLen = 121;
    if (isMariaSignal) C2VLen = C2VMaLen;
    std::vector<Double_t> zeroC2VVec(C2VLen,0.0);

    if (isMariaSignal) {
        C2VNameAr = C2VNameMaAr;
    }
    //std::vector<std::vector<Double_t>> zeroTypeVec(5,zeroC2VVec);

    std::vector<std::vector<Double_t>> startingWeightedCtrAr(2,zeroC2VVec);

    std::vector<std::vector<Double_t>> passHiggsFJWeightedCtrAr(2,zeroC2VVec);
    std::vector<std::vector<Double_t>> passHiggsFJWeightedSemiLepCtr(2,zeroC2VVec);
    
    std::vector<std::vector<Double_t>> passChannelWeightedCtrAr(2,zeroC2VVec);
    std::vector<std::vector<Double_t>> passLepOrSemiLepChannelWeightedCtrAr(2,zeroC2VVec);

    std::vector<std::vector<Double_t>> tryingSemiLepChannelWeightedCtrAr(2,zeroC2VVec);
    
    std::vector<std::vector<Double_t>> passHiggsFJInSemiLepChannelWeightedCtrAr(2,zeroC2VVec);
    
    std::vector<std::vector<Double_t>> passFJInSemiLepChannelWeightedCtrAr(2,zeroC2VVec);

    std::vector<std::vector<Double_t>> passEnoughFJsInSemiLepChannelWeightedCtrAr(2,zeroC2VVec);
    std::vector<std::vector<Double_t>> passSemiLepLepCutWeightedCtrAr(2,zeroC2VVec);
    std::vector<std::vector<Double_t>> passSemiLepChannelWeightedCtrAr(2,zeroC2VVec);

    std::vector<std::vector<Double_t>> passVBFJetBVetoWeightedCtr(2,zeroC2VVec);
    std::vector<std::vector<Double_t>> passVBFJetBVetoWeightedSemiLepCtr(2,zeroC2VVec);
    
    std::vector<std::vector<Double_t>> passVBFJetsWeightedCtr(2,zeroC2VVec);

    std::vector<std::vector<Double_t>> passLepVetoWeightedCtr(2,zeroC2VVec);

    std::vector<std::vector<Double_t>> passAsSemiLepWeightedCtr(2,zeroC2VVec);
    std::vector<std::vector<Double_t>> passSemiLepLepCutWeightedCtr(2,zeroC2VVec);

    
    
    UInt_t passSemiLepLepCutCtr = 0;
    //Double_t passSemiLepLepCutWeightedCtr = 0.;
    


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

    float crossSectionAvg = 0;
    float crossSectionCnt = 0;


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
    

    //PASSING EV TREE FOR BDT IN SEMILEP CHANNEL

    //EventCor/UncInds
    UInt_t JECCorInd_SL_L;
    UInt_t JECCorUpOrDown_SL_L;
    UInt_t RochInd_SL_L;
    UInt_t JERInd_SL_L;

    //EventReweighting
    UInt_t nLHEReweightingWeight_SL_L;
    std::vector<Float_t> LHEReweightingWeight_SL_L;

    Double_t passingEvGenWeight_SL_L;

    //Double_t passingEvFullWeight_SL_L;

    UInt_t datasetType_SL_L;
    UInt_t yearType_SL_L;

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
    std::vector<Int_t> Jet_hadronFlavour_SL_L;
    Float_t fixedGridRhoFastjetAll_SL_L;
    std::vector<Float_t> Jet_eta_Final_SL_L;
    std::vector<Float_t> Jet_pt_Final_SL_L;
    std::vector<Float_t> Jet_phi_Final_SL_L;
    std::vector<Float_t> Jet_mass_Final_SL_L;

    UInt_t eventNAK4JetsPassingCuts_SL_L;


    Float_t selectedHiggsFJ_pt_SL_L;
    Float_t selectedHiggsFJ_eta_SL_L;
    Float_t selectedHiggsFJ_phi_SL_L;

    Float_t selectedZFJ_ParticleNet_HbbvsQCD_SL_L;
    
    Float_t selectedHiggsFJ_ParticleNet_HbbvsQCD_SL_L;
    Float_t selectedZFJ_pt_SL_L;
    Float_t selectedZFJ_eta_SL_L;
    Float_t selectedZFJ_phi_SL_L;
    Float_t selectedZFJ_ParticleNet_ZvsQCD_SL_L;

    Float_t selectedHiggsFJ_ParticleNet_ZvsQCD_SL_L;

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

    Bool_t ZReconstructedWithCorrectFJ_SL_L;
    Bool_t HReconstructedWithCorrectFJ_SL_L;

    Bool_t ZReconstructedWithHFJ_SL_L;
    Bool_t HReconstructedWithZFJ_SL_L;

    Bool_t goodGenZFJMatch_SL_L;
    Bool_t goodGenHFJMatch_SL_L;
    Bool_t goodZFJMatchToGen_SL_L;
    Bool_t goodHFJMatchToGen_SL_L;
    Bool_t eventGenSemileptonic_SL_L;
    Bool_t eventGenHToBB_SL_L;
    Int_t ZFJGenHadronFlavour_SL_L;
    Int_t HFJGenHadronFlavour_SL_L;
    Int_t FatJet_hadronFlavour_SL_L;

    Bool_t firstHToBBBool_SL_L; //including as alternative to eventGenHToBB. Checking if there's a difference.

    UInt_t nHDecayPID_SL_L;
    std::vector<Int_t> HDecayPID_SL_L;
    UInt_t nZOneDecayPID_SL_L;
    std::vector<Int_t> ZOneDecayPID_SL_L;
    UInt_t nZTwoDecayPID_SL_L;
    std::vector<Int_t> ZTwoDecayPID_SL_L;
    Int_t ZOneType_SL_L; //0=Leptonic,1=Hadronic,2=Other
    Int_t ZTwoType_SL_L;

    //HLT 
    Bool_t HLT_Ele32_WPTight_Gsf_L1DoubleEG_SL_L;
    Bool_t HLT_IsoMu27_SL_L;
    Bool_t HLT_Mu50_SL_L;
    Bool_t HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_SL_L;
    Bool_t HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_SL_L;
    //2016 in other years just set these to false
    Bool_t HLT_Ele27_WPTight_Gsf_SL_L;
    Bool_t HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_SL_L;
    //Tight/Veto lep variables
    Bool_t tightLepLeadIsElec_SL_L;
    Bool_t tightLepTrailingIsElec_SL_L;
    Bool_t tightLepLeadIsMuon_SL_L;
    Bool_t tightLepTrailingIsMuon_SL_L;
    Int_t tightLepLeadInd_SL_L;
    Int_t tightLepTrailingInd_SL_L;
    Float_t tightLepLeadPt_SL_L;
    Float_t tightLepTrailingPt_SL_L;
    Float_t tightLepLeadEta_SL_L;
    Float_t tightLepTrailingEta_SL_L;
    Float_t tightLepLeadPhi_SL_L;
    Float_t tightLepTrailingPhi_SL_L;
    Float_t tightLepLeadMass_SL_L;
    Float_t tightLepTrailingMass_SL_L;

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
    
    //additional 042024Branches starting with this presel script
    //PUID SF check
    std::vector<Bool_t> Jet_LowPtPassesPUIDL;

    //more 042024Branches starting with selection
    Bool_t selectedLeadVBFJet_PUIDSFEligible_SL_L;
    Bool_t selectedTrailingVBFJet_PUIDSFEligible_SL_L;

    //05052024 Additions for PN regress mass scaling and resolution corrections
    UInt_t luminosityBlock_SL_L;
    ULong64_t event_SL_L;

    //PN Regress Mass nominal JMS and JMR plus up/down
    Float_t selectedZFJ_InvMassPNRegress_JMSNomJMRNom_SL_L;
    Float_t selectedZFJ_InvMassPNRegress_JMSUpJMRNom_SL_L;
    Float_t selectedZFJ_InvMassPNRegress_JMSDownJMRNom_SL_L;
    Float_t selectedZFJ_InvMassPNRegress_JMSNomJMRUp_SL_L;
    Float_t selectedZFJ_InvMassPNRegress_JMSNomJMRDown_SL_L;
    Float_t selectedHiggsFJ_InvMassPNRegress_JMSNomJMRNom_SL_L;
    Float_t selectedHiggsFJ_InvMassPNRegress_JMSUpJMRNom_SL_L;
    Float_t selectedHiggsFJ_InvMassPNRegress_JMSDownJMRNom_SL_L;
    Float_t selectedHiggsFJ_InvMassPNRegress_JMSNomJMRUp_SL_L;
    Float_t selectedHiggsFJ_InvMassPNRegress_JMSNomJMRDown_SL_L;
    
    TTree *passingEvSemiLepTree = new TTree("passingEvSemiLepTree", "passingEvSemiLepTree");

    //EventCor/UncInds
    passingEvSemiLepTree->Branch("JECCorInd_SL_L",&JECCorInd_SL_L,"JECCorInd_SL_L/i");
    passingEvSemiLepTree->Branch("JECCorUpOrDown_SL_L",&JECCorUpOrDown_SL_L,"JECCorUpOrDown_SL_L/i");
    passingEvSemiLepTree->Branch("RochInd_SL_L",&RochInd_SL_L,"RochInd_SL_L/i");
    passingEvSemiLepTree->Branch("JERInd_SL_L",&JERInd_SL_L,"JERInd_SL_L/i");

    passingEvSemiLepTree->Branch("nLHEReweightingWeight_SL_L",&nLHEReweightingWeight_SL_L,"nLHEReweightingWeight_SL_L/i");
    passingEvSemiLepTree->Branch("LHEReweightingWeight_SL_L",&LHEReweightingWeight_SL_L);
    
    passingEvSemiLepTree->Branch("passingEvGenWeight_SL_L",&passingEvGenWeight_SL_L,"passingEvGenWeight_SL_L/D");

    //passingEvSemiLepTree->Branch("passingEvFullWeight_SL_L",&passingEvFullWeight_SL_L,"passingEvFullWeight_SL_L/D");

    passingEvSemiLepTree->Branch("datasetType_SL_L",&datasetType_SL_L,"datasetType_SL_L/i");
    passingEvSemiLepTree->Branch("yearType_SL_L",&yearType_SL_L,"yearType_SL_L/i");

    passingEvSemiLepTree->Branch("eventNAK4Jets_SL_L",&eventNAK4Jets_SL_L,"eventNAK4Jets_SL_L/i");
    passingEvSemiLepTree->Branch("eventNAK8Jets_SL_L",&eventNAK8Jets_SL_L,"eventNAK8Jets_SL_L/i");
    passingEvSemiLepTree->Branch("eventNMuons_SL_L",&eventNMuons_SL_L,"eventNMuons_SL_L/i");
    passingEvSemiLepTree->Branch("eventNElectrons_SL_L",&eventNElectrons_SL_L,"eventNElectrons_SL_L/i");

    passingEvSemiLepTree->Branch("Jet_eta_SL_L",&Jet_eta_SL_L);
    passingEvSemiLepTree->Branch("Jet_pt_SL_L",&Jet_pt_SL_L);
    passingEvSemiLepTree->Branch("Jet_phi_SL_L",&Jet_phi_SL_L);
    passingEvSemiLepTree->Branch("Jet_mass_SL_L",&Jet_mass_SL_L);
    passingEvSemiLepTree->Branch("Jet_jetId_SL_L",&Jet_jetId_SL_L);
    passingEvSemiLepTree->Branch("Jet_hadronFlavour_SL_L",&Jet_hadronFlavour_SL_L);
    passingEvSemiLepTree->Branch("Jet_btagDeepFlavB_SL_L",&Jet_btagDeepFlavB_SL_L);
    passingEvSemiLepTree->Branch("fixedGridRhoFastjetAll_SL_L",&fixedGridRhoFastjetAll_SL_L,"fixedGridRhoFastjetAll_SL_L/F");
    passingEvSemiLepTree->Branch("Jet_eta_Final_SL_L",&Jet_eta_Final_SL_L);
    passingEvSemiLepTree->Branch("Jet_pt_Final_SL_L",&Jet_pt_Final_SL_L);
    passingEvSemiLepTree->Branch("Jet_phi_Final_SL_L",&Jet_phi_Final_SL_L);
    passingEvSemiLepTree->Branch("Jet_mass_Final_SL_L",&Jet_mass_Final_SL_L);
    

    passingEvSemiLepTree->Branch("eventNAK4JetsPassingCuts_SL_L",&eventNAK4JetsPassingCuts_SL_L,"eventNAK4JetsPassingCuts_SL_L/i");

    passingEvSemiLepTree->Branch("selectedHiggsFJ_pt_SL_L",&selectedHiggsFJ_pt_SL_L,"selectedHiggsFJ_pt_SL_L/F");
    passingEvSemiLepTree->Branch("selectedHiggsFJ_eta_SL_L",&selectedHiggsFJ_eta_SL_L,"selectedHiggsFJ_eta_SL_L/F");
    passingEvSemiLepTree->Branch("selectedHiggsFJ_phi_SL_L",&selectedHiggsFJ_phi_SL_L,"selectedHiggsFJ_phi_SL_L/F");

    passingEvSemiLepTree->Branch("selectedZFJ_ParticleNet_HbbvsQCD_SL_L",&selectedZFJ_ParticleNet_HbbvsQCD_SL_L,"selectedZFJ_ParticleNet_HbbvsQCD_SL_L/F");

    passingEvSemiLepTree->Branch("selectedHiggsFJ_ParticleNet_HbbvsQCD_SL_L",&selectedHiggsFJ_ParticleNet_HbbvsQCD_SL_L,"selectedHiggsFJ_ParticleNet_HbbvsQCD_SL_L/F");
    passingEvSemiLepTree->Branch("selectedZFJ_pt_SL_L",&selectedZFJ_pt_SL_L,"selectedZFJ_pt_SL_L/F");
    passingEvSemiLepTree->Branch("selectedZFJ_eta_SL_L",&selectedZFJ_eta_SL_L,"selectedZFJ_eta_SL_L/F");
    passingEvSemiLepTree->Branch("selectedZFJ_phi_SL_L",&selectedZFJ_phi_SL_L,"selectedZFJ_phi_SL_L/F");
    passingEvSemiLepTree->Branch("selectedZFJ_ParticleNet_ZvsQCD_SL_L",&selectedZFJ_ParticleNet_ZvsQCD_SL_L,"selectedZFJ_ParticleNet_ZvsQCD_SL_L/F");

    passingEvSemiLepTree->Branch("selectedHiggsFJ_ParticleNet_ZvsQCD_SL_L",&selectedHiggsFJ_ParticleNet_ZvsQCD_SL_L,"selectedHiggsFJ_ParticleNet_ZvsQCD_SL_L/F");

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
    
    passingEvSemiLepTree->Branch("ZReconstructedWithCorrectFJ_SL_L",&ZReconstructedWithCorrectFJ_SL_L,"ZReconstructedWithCorrectFJ_SL_L/O");
    passingEvSemiLepTree->Branch("HReconstructedWithCorrectFJ_SL_L",&HReconstructedWithCorrectFJ_SL_L,"HReconstructedWithCorrectFJ_SL_L/O");
    passingEvSemiLepTree->Branch("ZReconstructedWithHFJ_SL_L",&ZReconstructedWithHFJ_SL_L,"ZReconstructedWithHFJ_SL_L/O");
    passingEvSemiLepTree->Branch("HReconstructedWithZFJ_SL_L",&HReconstructedWithZFJ_SL_L,"HReconstructedWithZFJ_SL_L/O");

    passingEvSemiLepTree->Branch("goodGenZFJMatch_SL_L",&goodGenZFJMatch_SL_L,"goodGenZFJMatch_SL_L/O");
    passingEvSemiLepTree->Branch("goodGenHFJMatch_SL_L",&goodGenHFJMatch_SL_L,"goodGenHFJMatch_SL_L/O");
    passingEvSemiLepTree->Branch("goodZFJMatchToGen_SL_L",&goodZFJMatchToGen_SL_L,"goodZFJMatchToGen_SL_L/O");
    passingEvSemiLepTree->Branch("goodHFJMatchToGen_SL_L",&goodHFJMatchToGen_SL_L,"goodHFJMatchToGen_SL_L/O");
    passingEvSemiLepTree->Branch("eventGenSemileptonic_SL_L",&eventGenSemileptonic_SL_L,"eventGenSemileptonic_SL_L/O");
    passingEvSemiLepTree->Branch("eventGenHToBB_SL_L",&eventGenHToBB_SL_L,"eventGenHToBB_SL_L/O");

    passingEvSemiLepTree->Branch("ZFJGenHadronFlavour_SL_L",&ZFJGenHadronFlavour_SL_L,"ZFJGenHadronFlavour_SL_L/I");
    passingEvSemiLepTree->Branch("HFJGenHadronFlavour_SL_L",&HFJGenHadronFlavour_SL_L,"HFJGenHadronFlavour_SL_L/I");
    passingEvSemiLepTree->Branch("FatJet_hadronFlavour_SL_L",&FatJet_hadronFlavour_SL_L,"FatJet_hadronFlavour_SL_L/I");

    passingEvSemiLepTree->Branch("firstHToBBBool_SL_L",&firstHToBBBool_SL_L,"firstHToBBBool_SL_L/O");

    passingEvSemiLepTree->Branch("nHDecayPID_SL_L",&nHDecayPID_SL_L,"nHDecayPID_SL_L/i");
    passingEvSemiLepTree->Branch("HDecayPID_SL_L",&HDecayPID_SL_L);

    passingEvSemiLepTree->Branch("nZOneDecayPID_SL_L",&nZOneDecayPID_SL_L,"nZOneDecayPID_SL_L/i");
    passingEvSemiLepTree->Branch("ZOneDecayPID_SL_L",&ZOneDecayPID_SL_L);
    passingEvSemiLepTree->Branch("nZTwoDecayPID_SL_L",&nZTwoDecayPID_SL_L,"nZTwoDecayPID_SL_L/i");
    passingEvSemiLepTree->Branch("ZTwoDecayPID_SL_L",&ZTwoDecayPID_SL_L);

    passingEvSemiLepTree->Branch("ZOneType_SL_L",&ZOneType_SL_L,"ZOneType_SL_L/I");
    passingEvSemiLepTree->Branch("ZTwoType_SL_L",&ZTwoType_SL_L,"ZTwoType_SL_L/I");

    passingEvSemiLepTree->Branch("HLT_Ele32_WPTight_Gsf_L1DoubleEG_SL_L",&HLT_Ele32_WPTight_Gsf_L1DoubleEG_SL_L,"HLT_Ele32_WPTight_Gsf_L1DoubleEG_SL_L/O");
    passingEvSemiLepTree->Branch("HLT_IsoMu27_SL_L",&HLT_IsoMu27_SL_L,"HLT_IsoMu27_SL_L/O");
    passingEvSemiLepTree->Branch("HLT_Mu50_SL_L",&HLT_Mu50_SL_L,"HLT_Mu50_SL_L/O");
    passingEvSemiLepTree->Branch("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_SL_L",&HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_SL_L,"HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_SL_L/O");
    passingEvSemiLepTree->Branch("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_SL_L",&HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_SL_L,"HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_SL_L/O");

    //2016
    passingEvSemiLepTree->Branch("HLT_Ele27_WPTight_Gsf_SL_L",&HLT_Ele27_WPTight_Gsf_SL_L,"HLT_Ele27_WPTight_Gsf_SL_L/O");
    passingEvSemiLepTree->Branch("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_SL_L",&HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_SL_L,"HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_SL_L/O");

    passingEvSemiLepTree->Branch("tightLepLeadIsElec_SL_L",&tightLepLeadIsElec_SL_L,"tightLepLeadIsElec_SL_L/O");
    passingEvSemiLepTree->Branch("tightLepTrailingIsElec_SL_L",&tightLepTrailingIsElec_SL_L,"tightLepTrailingIsElec_SL_L/O");
    passingEvSemiLepTree->Branch("tightLepLeadIsMuon_SL_L",&tightLepLeadIsMuon_SL_L,"tightLepLeadIsMuon_SL_L/O");
    passingEvSemiLepTree->Branch("tightLepTrailingIsMuon_SL_L",&tightLepTrailingIsMuon_SL_L,"tightLepTrailingIsMuon_SL_L/O");
    passingEvSemiLepTree->Branch("tightLepLeadInd_SL_L",&tightLepLeadInd_SL_L,"tightLepLeadInd_SL_L/I");
    passingEvSemiLepTree->Branch("tightLepTrailingInd_SL_L",&tightLepTrailingInd_SL_L,"tightLepTrailingInd_SL_L/I");
    passingEvSemiLepTree->Branch("tightLepLeadPt_SL_L",&tightLepLeadPt_SL_L,"tightLepLeadPt_SL_L/F");
    passingEvSemiLepTree->Branch("tightLepTrailingPt_SL_L",&tightLepTrailingPt_SL_L,"tightLepTrailingPt_SL_L/F");
    passingEvSemiLepTree->Branch("tightLepLeadEta_SL_L",&tightLepLeadEta_SL_L,"tightLepLeadEta_SL_L/F");
    passingEvSemiLepTree->Branch("tightLepTrailingEta_SL_L",&tightLepTrailingEta_SL_L,"tightLepTrailingEta_SL_L/F");
    passingEvSemiLepTree->Branch("tightLepLeadPhi_SL_L",&tightLepLeadPhi_SL_L,"tightLepLeadPhi_SL_L/F");
    passingEvSemiLepTree->Branch("tightLepTrailingPhi_SL_L",&tightLepTrailingPhi_SL_L,"tightLepTrailingPhi_SL_L/F");
    passingEvSemiLepTree->Branch("tightLepLeadMass_SL_L",&tightLepLeadMass_SL_L,"tightLepLeadMass_SL_L/F");
    passingEvSemiLepTree->Branch("tightLepTrailingMass_SL_L",&tightLepTrailingMass_SL_L,"tightLepTrailingMass_SL_L/F");

    //042024SFAndSuchAdditions
    //PU JetID
    passingEvSemiLepTree->Branch("Jet_puIdL",&Jet_puIdL);
    //L1 Prefiring Weights
    passingEvSemiLepTree->Branch("L1PreFiringWeight_NomL",&L1PreFiringWeight_NomL,"L1PreFiringWeight_NomL/F");
    passingEvSemiLepTree->Branch("L1PreFiringWeight_DnL",&L1PreFiringWeight_DnL,"L1PreFiringWeight_DnL/F");
    passingEvSemiLepTree->Branch("L1PreFiringWeight_UpL",&L1PreFiringWeight_UpL,"L1PreFiringWeight_UpL/F");
    //PileUp number of interactions
    passingEvSemiLepTree->Branch("Pileup_nTrueIntL",&Pileup_nTrueIntL,"Pileup_nTrueIntL/F");
    passingEvSemiLepTree->Branch("Pileup_nPUL",&Pileup_nPUL,"Pileup_nPUL/I");
    //PSWeight
    passingEvSemiLepTree->Branch("nPSWeightL",&nPSWeightL,"nPSWeightL/i");
    passingEvSemiLepTree->Branch("PSWeightL",&PSWeightL);
    //LHE Scale Weight
    passingEvSemiLepTree->Branch("nLHEScaleWeightL",&nLHEScaleWeightL,"nLHEScaleWeightL/i");
    passingEvSemiLepTree->Branch("LHEScaleWeightL",&LHEScaleWeightL);
    //LHE PDF Weight
    passingEvSemiLepTree->Branch("nLHEPdfWeightL",&nLHEPdfWeightL,"nLHEPdfWeightL/i");
    passingEvSemiLepTree->Branch("LHEPdfWeightL",&LHEPdfWeightL);
    passingEvSemiLepTree->Branch("LHEWeight_originalXWGTUPL",&LHEWeight_originalXWGTUPL,"LHEWeight_originalXWGTUPL/F");
    //generator weight
    passingEvSemiLepTree->Branch("Generator_weightL",&Generator_weightL,"Generator_weightL/F");
    //additional 042024Branches starting with this script
    //PUID SF check
    passingEvSemiLepTree->Branch("Jet_LowPtPassesPUIDL",&Jet_LowPtPassesPUIDL);

    //more 042024Branches starting with selection
    passingEvSemiLepTree->Branch("selectedLeadVBFJet_PUIDSFEligible_SL_L",&selectedLeadVBFJet_PUIDSFEligible_SL_L,"selectedLeadVBFJet_PUIDSFEligible_SL_L/O");
    passingEvSemiLepTree->Branch("selectedTrailingVBFJet_PUIDSFEligible_SL_L",&selectedTrailingVBFJet_PUIDSFEligible_SL_L,"selectedTrailingVBFJet_PUIDSFEligible_SL_L/O");

    //05052024 Additions for PN regress mass scaling and resolution corrections
    passingEvSemiLepTree->Branch("luminosityBlock_SL_L",&luminosityBlock_SL_L,"luminosityBlock_SL_L/i");
    passingEvSemiLepTree->Branch("event_SL_L",&event_SL_L,"event_SL_L/l");
    //PN Regress Mass nominal JMS and JMR plus up/down
    passingEvSemiLepTree->Branch("selectedZFJ_InvMassPNRegress_JMSNomJMRNom_SL_L",&selectedZFJ_InvMassPNRegress_JMSNomJMRNom_SL_L,"selectedZFJ_InvMassPNRegress_JMSNomJMRNom_SL_L/F");
    passingEvSemiLepTree->Branch("selectedZFJ_InvMassPNRegress_JMSUpJMRNom_SL_L",&selectedZFJ_InvMassPNRegress_JMSUpJMRNom_SL_L,"selectedZFJ_InvMassPNRegress_JMSUpJMRNom_SL_L/F");
    passingEvSemiLepTree->Branch("selectedZFJ_InvMassPNRegress_JMSDownJMRNom_SL_L",&selectedZFJ_InvMassPNRegress_JMSDownJMRNom_SL_L,"selectedZFJ_InvMassPNRegress_JMSDownJMRNom_SL_L/F");
    passingEvSemiLepTree->Branch("selectedZFJ_InvMassPNRegress_JMSNomJMRUp_SL_L",&selectedZFJ_InvMassPNRegress_JMSNomJMRUp_SL_L,"selectedZFJ_InvMassPNRegress_JMSNomJMRUp_SL_L/F");
    passingEvSemiLepTree->Branch("selectedZFJ_InvMassPNRegress_JMSNomJMRDown_SL_L",&selectedZFJ_InvMassPNRegress_JMSNomJMRDown_SL_L,"selectedZFJ_InvMassPNRegress_JMSNomJMRDown_SL_L/F");
    passingEvSemiLepTree->Branch("selectedHiggsFJ_InvMassPNRegress_JMSNomJMRNom_SL_L",&selectedHiggsFJ_InvMassPNRegress_JMSNomJMRNom_SL_L,"selectedHiggsFJ_InvMassPNRegress_JMSNomJMRNom_SL_L/F");
    passingEvSemiLepTree->Branch("selectedHiggsFJ_InvMassPNRegress_JMSUpJMRNom_SL_L",&selectedHiggsFJ_InvMassPNRegress_JMSUpJMRNom_SL_L,"selectedHiggsFJ_InvMassPNRegress_JMSUpJMRNom_SL_L/F");
    passingEvSemiLepTree->Branch("selectedHiggsFJ_InvMassPNRegress_JMSDownJMRNom_SL_L",&selectedHiggsFJ_InvMassPNRegress_JMSDownJMRNom_SL_L,"selectedHiggsFJ_InvMassPNRegress_JMSDownJMRNom_SL_L/F");
    passingEvSemiLepTree->Branch("selectedHiggsFJ_InvMassPNRegress_JMSNomJMRUp_SL_L",&selectedHiggsFJ_InvMassPNRegress_JMSNomJMRUp_SL_L,"selectedHiggsFJ_InvMassPNRegress_JMSNomJMRUp_SL_L/F");
    passingEvSemiLepTree->Branch("selectedHiggsFJ_InvMassPNRegress_JMSNomJMRDown_SL_L",&selectedHiggsFJ_InvMassPNRegress_JMSNomJMRDown_SL_L,"selectedHiggsFJ_InvMassPNRegress_JMSNomJMRDown_SL_L/F");

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



    std::cout << "Going into file loop.\n";

    for (UInt_t k=0; k<fileAr.size(); k++){
        if (endAfter && evCount > NToEnd) break;
        if (debug) std::cout<<"File:    "<<fileAr[k]<<"\n";
        //Open the file, get the Events tree
        TFile* tmpfile = TFile::Open(fileAr[k].c_str());
        //outFile->cd();
        TTreeReader myEventsReader("FilteredEventsTree", tmpfile);

        //eventWeights
        TTreeReaderValue<UInt_t> nLHEReweightingWeightL(myEventsReader, "nLHEReweightingWeightL");
        TTreeReaderArray<Float_t> LHEReweightingWeightL(myEventsReader, "LHEReweightingWeightL");

        //genWeights
        TTreeReaderValue<Double_t> genWeightL(myEventsReader, "genWeightL");
        //jets

        TTreeReaderValue<UInt_t> nJetL(myEventsReader, "nJetL");
        TTreeReaderArray<Float_t> Jet_etaL(myEventsReader, "Jet_etaL");
        TTreeReaderArray<Float_t> Jet_ptL(myEventsReader, "Jet_ptL");
        TTreeReaderArray<Float_t> Jet_phiL(myEventsReader, "Jet_phiL");
        TTreeReaderArray<Float_t> Jet_massL(myEventsReader, "Jet_massL");
        TTreeReaderArray<Int_t> Jet_jetIdL(myEventsReader, "Jet_jetIdL");
        TTreeReaderArray<Int_t> Jet_hadronFlavourL(myEventsReader, "Jet_hadronFlavourL");
        TTreeReaderArray<Int_t> Jet_genJetIdxL(myEventsReader, "Jet_genJetIdxL");
        TTreeReaderValue<Float_t> fixedGridRhoFastjetAllL(myEventsReader, "fixedGridRhoFastjetAllL");
        TTreeReaderArray<Float_t> Jet_eta_FinalL(myEventsReader, "Jet_eta_FinalL");
        TTreeReaderArray<Float_t> Jet_pt_FinalL(myEventsReader, "Jet_pt_FinalL");
        TTreeReaderArray<Float_t> Jet_phi_FinalL(myEventsReader, "Jet_phi_FinalL");
        TTreeReaderArray<Float_t> Jet_mass_FinalL(myEventsReader, "Jet_mass_FinalL");

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
        TTreeReaderArray<Float_t> FatJet_eta_FinalL(myEventsReader, "FatJet_eta_FinalL");
        TTreeReaderArray<Float_t> FatJet_pt_FinalL(myEventsReader, "FatJet_pt_FinalL");
        TTreeReaderArray<Float_t> FatJet_phi_FinalL(myEventsReader, "FatJet_phi_FinalL");
        TTreeReaderArray<Float_t> FatJet_mass_FinalL(myEventsReader, "FatJet_mass_FinalL");

        TTreeReaderArray<Float_t> FatJet_particleNet_massL(myEventsReader, "FatJet_particleNet_massL");

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
        TTreeReaderArray<Float_t> Muon_RochMomCorrectionsL(myEventsReader, "Muon_RochMomCorrectionsL");
        TTreeReaderArray<Float_t> Muon_ptCorrectedL(myEventsReader, "Muon_ptCorrectedL");
        TTreeReaderArray<Float_t> Muon_RochCorUncL(myEventsReader, "Muon_RochCorUncL");


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

        TTreeReaderArray<Float_t> Jet_btagDeepFlavBL(myEventsReader,"Jet_btagDeepFlavBL");

        //ParticleNet
        TTreeReaderArray<Float_t> FatJet_particleNet_HbbvsQCDL(myEventsReader, "FatJet_particleNet_HbbvsQCDL");
        TTreeReaderArray<Float_t> FatJet_particleNet_ZvsQCDL(myEventsReader, "FatJet_particleNet_ZvsQCDL");

        TTreeReaderArray<Float_t> FatJet_particleNetMD_QCDL(myEventsReader, "FatJet_particleNetMD_QCDL");
        TTreeReaderArray<Float_t> FatJet_particleNetMD_XbbL(myEventsReader, "FatJet_particleNetMD_XbbL");
        TTreeReaderArray<Float_t> FatJet_particleNetMD_XccL(myEventsReader, "FatJet_particleNetMD_XccL");
        TTreeReaderArray<Float_t> FatJet_particleNetMD_XqqL(myEventsReader, "FatJet_particleNetMD_XqqL");


        


        //genChannelL
        TTreeReaderValue<UInt_t> genChannelL(myEventsReader, "genChannelL");
        //HTobbBool
        TTreeReaderValue<Bool_t> HTobbBoolL(myEventsReader, "HTobbBoolL");

        //HLT
        TTreeReaderValue<Bool_t> HLT_Ele32_WPTight_Gsf_L1DoubleEGL(myEventsReader,"HLT_Ele32_WPTight_Gsf_L1DoubleEGL");
        TTreeReaderValue<Bool_t> HLT_IsoMu27L(myEventsReader,"HLT_IsoMu27L");
        TTreeReaderValue<Bool_t> HLT_Mu50L(myEventsReader,"HLT_Mu50L");
        TTreeReaderValue<Bool_t> HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZL(myEventsReader,"HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZL");
        TTreeReaderValue<Bool_t> HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8L(myEventsReader,"HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8L");

        TTreeReaderValue<Bool_t> HLT_Ele27_WPTight_GsfL(myEventsReader,"HLT_Ele27_WPTight_GsfL");
        TTreeReaderValue<Bool_t> HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZL(myEventsReader,"HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZL");

        //Tight Leps from Preselection
        TTreeReaderValue<Int_t> tightLepLeadIndL(myEventsReader,"tightLepLeadIndL");
        TTreeReaderValue<Int_t> tightLepTrailingIndL(myEventsReader,"tightLepTrailingIndL");
        TTreeReaderValue<Bool_t> tightLepLeadIsElecL(myEventsReader,"tightLepLeadIsElecL");
        TTreeReaderValue<Bool_t> tightLepTrailingIsElecL(myEventsReader,"tightLepTrailingIsElecL");
        TTreeReaderValue<Bool_t> tightLepLeadIsMuonL(myEventsReader,"tightLepLeadIsMuonL");
        TTreeReaderValue<Bool_t> tightLepTrailingIsMuonL(myEventsReader,"tightLepTrailingIsMuonL");
        TTreeReaderValue<Float_t> tightLepLeadPtL(myEventsReader,"tightLepLeadPtL");
        TTreeReaderValue<Float_t> tightLepTrailingPtL(myEventsReader,"tightLepTrailingPtL");
        TTreeReaderValue<Float_t> tightLepLeadEtaL(myEventsReader,"tightLepLeadEtaL");
        TTreeReaderValue<Float_t> tightLepTrailingEtaL(myEventsReader,"tightLepTrailingEtaL");
        TTreeReaderValue<Float_t> tightLepLeadPhiL(myEventsReader,"tightLepLeadPhiL");
        TTreeReaderValue<Float_t> tightLepTrailingPhiL(myEventsReader,"tightLepTrailingPhiL");
        TTreeReaderValue<Float_t> tightLepLeadMassL(myEventsReader,"tightLepLeadMassL");
        TTreeReaderValue<Float_t> tightLepTrailingMassL(myEventsReader,"tightLepTrailingMassL");

        TTreeReaderValue<UInt_t> nVetoElecL(myEventsReader,"nVetoElecL");
        TTreeReaderValue<UInt_t> nVetoMuonL(myEventsReader,"nVetoMuonL");
        TTreeReaderArray<Int_t> vetoElecIndL(myEventsReader,"vetoElecIndL");
        TTreeReaderArray<Int_t> vetoMuonIndL(myEventsReader,"vetoMuonIndL");

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

        //additional 042024Branches starting with preselection
        //PUID SF check
        TTreeReaderArray<Bool_t> Jet_LowPtPassesPUID(myEventsReader, "Jet_LowPtPassesPUIDL");

        //05052024 Additions for PN regress mass scaling and resolution corrections
        TTreeReaderValue<UInt_t> luminosityBlock(myEventsReader, "luminosityBlockL");
        TTreeReaderValue<ULong64_t> event(myEventsReader, "eventL");
        TTreeReaderArray<Float_t> FatJet_particleNet_mass_JMSNomJMRNomCor(myEventsReader, "FatJet_particleNet_mass_JMSNomJMRNomCorL");
        TTreeReaderArray<Float_t> FatJet_particleNet_mass_JMSNomJMRUpCor(myEventsReader, "FatJet_particleNet_mass_JMSNomJMRUpCorL");
        TTreeReaderArray<Float_t> FatJet_particleNet_mass_JMSNomJMRDownCor(myEventsReader, "FatJet_particleNet_mass_JMSNomJMRDownCorL");
        TTreeReaderArray<Float_t> FatJet_particleNet_mass_JMSUpJMRNomCor(myEventsReader, "FatJet_particleNet_mass_JMSUpJMRNomCorL");
        TTreeReaderArray<Float_t> FatJet_particleNet_mass_JMSDownJMRNomCor(myEventsReader, "FatJet_particleNet_mass_JMSDownJMRNomCorL");


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



        TTreeReader myEvNumReader("evNumTree", tmpfile);
        TTreeReaderValue<UInt_t> nEv(myEvNumReader, "nEv");
        TTreeReaderValue<UInt_t> nEvPass(myEvNumReader, "nEvPass");

        //TTreeReader myXSReader("crossSectionTree", tmpfile);
        //TTreeReaderValue<Float_t> crossSectionVar(myXSReader, "crossSectionVar");

        Int_t tmpPDGId;


        Int_t tmpZ2Ind = -1;
        bool Z2IsMuon = false;
        float tmpTopZ2LeadPt = 0;
        float tmpTopZ2TrailingPt = 0;
        ROOT::Math::PtEtaPhiMVector tmpZ1Vec;
        float tmpZ1M;

        float Z1LeadIso;
        float Z1TrailingIso;
        float Z1LeadSIP;
        float Z1TrailingSIP;

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

        //Getting the cross section
        //For background it's precalculated

        /*
        while (myXSReader.Next()){
            crossSectionAvg += *crossSectionVar;
            crossSectionCnt += 1;
            //dataXS = *crossSectionVar;
        }
        */

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
                std::cout << evCount+1 << " in ev loop\n";
            }
            //Increment event count
            evRunOver += 1;
            evCount += 1;

            elecCandIndAr.clear();
            muonCandIndAr.clear();

            eZ2VecPairAr.clear();
            mZ2VecPairAr.clear();

            if (*nLHEReweightingWeightL == 0) {
                std::cout << "Event " << evCount << " nLHEReweightingWeightL == 0\n";
                continue;
            }

            Bool_t falseHtobbMask = false;

            //std::vector<Bool_t> falseTypeMask(5,false);
            //std::vector<std::vector<Bool_t>> falseHtobbMask(2,falseTypeMask);

            Double_t tmpGenWeights = *genWeightL;
            startingCtr += 1;
            //startingWeightedCtr += tmpGenWeights;
            
            

        
            if (*HTobbBoolL){
                falseHtobbMask = true;
                
            }
            else{
                falseHtobbMask = false;
                
            }
            
            if (falseHtobbMask) {
                startingWeightedCtrAr[0][0] = *genWeightL;
                for (unsigned int C2VCtr = 1; C2VCtr < startingWeightedCtrAr[0].size(); C2VCtr++){
                    startingWeightedCtrAr[0][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                }
            }
            else {
                startingWeightedCtrAr[1][0] = *genWeightL;
                for (unsigned int C2VCtr = 1; C2VCtr < startingWeightedCtrAr[1].size(); C2VCtr++){
                    startingWeightedCtrAr[1][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                }
            }
            
        
        


            bool passesCutsBool = false;
            bool passedAsSemiLepBool = false;
            bool passedAsSemiLepLepCutBool = false;
            bool passedAsSemiLepHiggsCutBool = false;



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
            
            std::vector<ROOT::Math::PtEtaPhiMVector> dRCheckVecAr;
            if (debug) std::cout << "*nJetL " << *nJetL << "\n";
            
            dRCheckVecAr.clear();
            std::vector<Float_t> SemiLepInvMass;
            
            if (debug) std::cout << "trying SemiLeptonic\n";
            tryingSemiLepChannelCtr += 1;
            

            if (falseHtobbMask) {
                tryingSemiLepChannelWeightedCtrAr[0][0] = *genWeightL;
                for (unsigned int C2VCtr = 1; C2VCtr < startingWeightedCtrAr[0].size(); C2VCtr++){
                    tryingSemiLepChannelWeightedCtrAr[0][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                }
            }
            else {
                tryingSemiLepChannelWeightedCtrAr[1][0] = *genWeightL;
                for (unsigned int C2VCtr = 1; C2VCtr < startingWeightedCtrAr[1].size(); C2VCtr++){
                    tryingSemiLepChannelWeightedCtrAr[1][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                }
            }

            
        
            tryingSemiLepCtr += 1;
            //Checking that there are enough FJs for both the Z and the H
            UInt_t numFatJet = *nFatJetL;
            UInt_t nPassingJetIdFJs = 0;
            for (UInt_t fatJetInd=0;fatJetInd<numFatJet;fatJetInd++){
                if (FatJet_jetIdL[fatJetInd] == 6) nPassingJetIdFJs += 1;

            }

            if (nPassingJetIdFJs >=2){
                passEnoughFJsInSemiLepChannelCtr += 1;


                if (falseHtobbMask) {
                    passEnoughFJsInSemiLepChannelWeightedCtrAr[0][0] = *genWeightL;
                    for (unsigned int C2VCtr = 1; C2VCtr < startingWeightedCtrAr[0].size(); C2VCtr++){
                        passEnoughFJsInSemiLepChannelWeightedCtrAr[0][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                    }
                }
                else {
                    passEnoughFJsInSemiLepChannelWeightedCtrAr[1][0] = *genWeightL;
                    for (unsigned int C2VCtr = 1; C2VCtr < startingWeightedCtrAr[1].size(); C2VCtr++){
                        passEnoughFJsInSemiLepChannelWeightedCtrAr[1][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                    }
                }


                float tmpPtLeadCut = 0;
                float tmpPtTrailingCut = 0;
                
                //checking the flavor and charge of the leptons
                bool chargeFlavorMatch = false;
                if (*tightLepLeadIsElecL){
                    if (*tightLepTrailingIsElecL){
                        if (Electron_chargeL[*tightLepLeadIndL] != Electron_chargeL[*tightLepTrailingIndL]){
                            chargeFlavorMatch = true;
                            tmpPtLeadCut = ptLeadElecCut;
                            tmpPtTrailingCut = ptTrailingElecCut;
                            Z1LeadSIP = Electron_sip3dL[*tightLepLeadIndL];
                            Z1TrailingSIP = Electron_sip3dL[*tightLepTrailingIndL];
                            float tmpIso;
                            float tmpIsoAdd = 0.;

                            if (*tightLepLeadPtL > 35){
                                if (abs(Electron_etaL[*tightLepLeadIndL]) < 1.4) tmpIsoAdd = max(0., Electron_dr03EcalRecHitSumEtL[*tightLepLeadIndL] - 1.);
                                else tmpIsoAdd = Electron_dr03EcalRecHitSumEtL[*tightLepLeadIndL];
                                tmpIso = ( Electron_dr03TkSumPtL[*tightLepLeadIndL] + tmpIsoAdd + Electron_dr03HcalDepth1TowerSumEtL[*tightLepLeadIndL] ) / Electron_ptL[*tightLepLeadIndL];
                            }
                            else tmpIso = Electron_pfRelIso03_allL[*tightLepLeadIndL];
                            Z1LeadIso = tmpIso;
                        
                            if (*tightLepTrailingPtL > 35){
                                if (abs(Electron_etaL[*tightLepTrailingIndL]) < 1.4) tmpIsoAdd = max(0., Electron_dr03EcalRecHitSumEtL[*tightLepTrailingIndL] - 1.);
                                else tmpIsoAdd = Electron_dr03EcalRecHitSumEtL[*tightLepTrailingIndL];
                                tmpIso = ( Electron_dr03TkSumPtL[*tightLepTrailingIndL] + tmpIsoAdd + Electron_dr03HcalDepth1TowerSumEtL[*tightLepTrailingIndL] ) / Electron_ptL[*tightLepTrailingIndL];
                            }
                            else tmpIso = Electron_pfRelIso03_allL[*tightLepTrailingIndL];
                            Z1TrailingIso = tmpIso;
                            
                        }
                    }
                }
                else if (*tightLepLeadIsMuonL){
                    if (*tightLepTrailingIsMuonL){
                        if (Muon_chargeL[*tightLepLeadIndL] != Muon_chargeL[*tightLepTrailingIndL]){
                            chargeFlavorMatch = true;
                            tmpPtLeadCut = mPtCut;
                            tmpPtTrailingCut = mPtCut;
                            Z1LeadSIP = Muon_sip3dL[*tightLepLeadIndL];
                            Z1TrailingSIP = Muon_sip3dL[*tightLepTrailingIndL];
                            Z1LeadIso = Muon_pfRelIso03_allL[*tightLepLeadIndL];
                            Z1TrailingIso = Muon_pfRelIso03_allL[*tightLepTrailingIndL];
                        }
                    }
                }
                else {
                    //if neither, then something is wrong. debug output with event number
                    std::cout << "neither tightLepLeadIsElecL nor tightLepLeadIsMuonL is true. Event: " << evCount << "\n";
                }
                if (!chargeFlavorMatch) continue;
                Z1IsMuon = *tightLepLeadIsMuonL;
                
                //Doing the semilep cuts

                ROOT::Math::PtEtaPhiMVector tmpLeadLepVec = ROOT::Math::PtEtaPhiMVector(*tightLepLeadPtL, *tightLepLeadEtaL, *tightLepLeadPhiL, *tightLepLeadMassL);
                ROOT::Math::PtEtaPhiMVector tmpTrailingLepVec = ROOT::Math::PtEtaPhiMVector(*tightLepTrailingPtL, *tightLepTrailingEtaL, *tightLepTrailingPhiL, *tightLepTrailingMassL);
                ROOT::Math::PtEtaPhiMVector tmpZ1Vec = tmpLeadLepVec + tmpTrailingLepVec;
                float tmpZ1M = tmpZ1Vec.M();



                if (*tightLepLeadPtL > tmpPtLeadCut && *tightLepTrailingPtL > tmpPtTrailingCut && tmpZ1M > invMassCutLow && tmpZ1M < invMassCutHigh){
                    passedAsSemiLepLepCutBool = true;
                    dRCheckVecAr.push_back(tmpLeadLepVec);
                    dRCheckVecAr.push_back(tmpTrailingLepVec);
                    Z1LeadPt = *tightLepLeadPtL;
                    Z1TrailingPt = *tightLepTrailingPtL;
                    selectedLeptons_InvMass = tmpZ1M;
                    

                
                }

                if (!passedAsSemiLepLepCutBool) continue;

                if (passedAsSemiLepLepCutBool){
                    if (debug) std::cout << "Passed semi lep lep cut\n";
                    passHiggsFJInSemiLepChannelCtr += 1;
                    //passSemiLepLepCutWeightedCtr += tmpGenWeights;
                    


                    if (falseHtobbMask) {
                        passSemiLepLepCutWeightedCtrAr[0][0] = *genWeightL;
                        for (unsigned int C2VCtr = 1; C2VCtr < startingWeightedCtrAr[0].size(); C2VCtr++){
                            passSemiLepLepCutWeightedCtrAr[0][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                        }
                    }
                    else {
                        passSemiLepLepCutWeightedCtrAr[1][0] = *genWeightL;
                        for (unsigned int C2VCtr = 1; C2VCtr < startingWeightedCtrAr[1].size(); C2VCtr++){
                            passSemiLepLepCutWeightedCtrAr[1][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                        }
                    }
                
                    
                }




                if (debug){
                    std::cout << "Pre FJC dRCheckVecAr.size() " << dRCheckVecAr.size() << "\n";
                }
                doHiggsFatJetCutBeforeZMDPNSelection(nFatJetLen,hFatJet_pt_fromHTag,hFatJet_phi_fromHTag,hFatJet_eta_fromHTag,hFatJet_mass_fromHTag,hFatJet_HTag_fromHTag,hFatJet_ind_fromHTag,FatJet_particleNetMD_QCDL,FatJet_particleNetMD_XbbL,hFatJetParticleNetCut,FatJet_pt_FinalL,hFatJetPTCut,FatJet_jetIdL,FatJet_phi_FinalL,FatJet_eta_FinalL,FatJet_mass_FinalL,dRCheckVecAr,dRCut,passedAsSemiLepLepCutBool,passedAsSemiLepHiggsCutBool);
                
                if (debug) std::cout << " found Higgs fat jet\n";


                if (passedAsSemiLepHiggsCutBool){
                    passSemiLepLepCutCtr += 1;
                    //passSemiLepLepCutWeightedCtr += tmpGenWeights;
                    


                    if (falseHtobbMask) {
                        passHiggsFJInSemiLepChannelWeightedCtrAr[0][0] = *genWeightL;
                        for (unsigned int C2VCtr = 1; C2VCtr < startingWeightedCtrAr[0].size(); C2VCtr++){
                            passHiggsFJInSemiLepChannelWeightedCtrAr[0][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                        }
                    }
                    else {
                        passHiggsFJInSemiLepChannelWeightedCtrAr[1][0] = *genWeightL;
                        for (unsigned int C2VCtr = 1; C2VCtr < startingWeightedCtrAr[1].size(); C2VCtr++){
                            passHiggsFJInSemiLepChannelWeightedCtrAr[1][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                        }
                    }
                
                    
                }





                Int_t FJInd;

                FJInd = -1;
                //UInt_t numFatJet = *nFatJetL;
                if (debug){
                    std::cout << "Pre FJC dRCheckVecAr.size() " << dRCheckVecAr.size() << "\n";
                }
                doSemiLepChanFatJetCutAfterHMDPNSelection(FJInd,numFatJet,fatJetPTCut,fatJetZParticleNetCut,FatJet_pt_FinalL,FatJet_phi_FinalL,FatJet_eta_FinalL,FatJet_mass_FinalL,FatJet_particleNetMD_QCDL,FatJet_particleNetMD_XbbL,FatJet_particleNetMD_XccL,FatJet_particleNetMD_XqqL,FatJet_jetIdL,dRCheckVecAr,dRCut,hFatJet_ind_fromHTag,passedAsSemiLepHiggsCutBool,passSemiLepCut,passesCutsBool,passedAsSemiLepBool);
                if (debug){
                    std::cout << "Post FJC dRCheckVecAr.size() " << dRCheckVecAr.size() << " FJInd "<< FJInd <<"\n";
                }
                if (FJInd >= 0){
                    passFJInSemiLepChannelCtr += 1;
                    //passFJInSemiLepChannelWeightedCtr += tmpGenWeights;
                    

                    if (falseHtobbMask) {
                        passFJInSemiLepChannelWeightedCtrAr[0][0] = *genWeightL;
                        for (unsigned int C2VCtr = 1; C2VCtr < startingWeightedCtrAr[0].size(); C2VCtr++){
                            passFJInSemiLepChannelWeightedCtrAr[0][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                        }
                    }
                    else {
                        passFJInSemiLepChannelWeightedCtrAr[1][0] = *genWeightL;
                        for (unsigned int C2VCtr = 1; C2VCtr < startingWeightedCtrAr[1].size(); C2VCtr++){
                            passFJInSemiLepChannelWeightedCtrAr[1][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                        }
                    }
                    
                FJIndAr.push_back(FJInd);
                FJIndAr.push_back(hFatJet_ind_fromHTag);
                
                }
            }
            
            if (passesCutsBool){
                passChannelCtr += 1;
                //passChannelWeightedCtr += tmpGenWeights;
                

                if (falseHtobbMask) {
                    passChannelWeightedCtrAr[0][0] = *genWeightL;
                    for (unsigned int C2VCtr = 1; C2VCtr < startingWeightedCtrAr[0].size(); C2VCtr++){
                        passChannelWeightedCtrAr[0][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                    }
                }
                else {
                    passChannelWeightedCtrAr[1][0] = *genWeightL;
                    for (unsigned int C2VCtr = 1; C2VCtr < startingWeightedCtrAr[1].size(); C2VCtr++){
                        passChannelWeightedCtrAr[1][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                    }
                }
                


                passSemiLepChannelCtr += 1;
                //passSemiLepChannelWeightedCtr += tmpGenWeights;
                


                if (falseHtobbMask) {
                    passSemiLepChannelWeightedCtrAr[0][0] = *genWeightL;
                    for (unsigned int C2VCtr = 1; C2VCtr < startingWeightedCtrAr[0].size(); C2VCtr++){
                        passSemiLepChannelWeightedCtrAr[0][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                    }
                }
                else {
                    passSemiLepChannelWeightedCtrAr[1][0] = *genWeightL;
                    for (unsigned int C2VCtr = 1; C2VCtr < startingWeightedCtrAr[1].size(); C2VCtr++){
                        passSemiLepChannelWeightedCtrAr[1][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                    }
                }
                

                passLepOrSemiLepChannelCtr += 1;
                //passLepOrSemiLepChannelWeightedCtr += tmpGenWeights;
                

                if (falseHtobbMask) {
                    passLepOrSemiLepChannelWeightedCtrAr[0][0] = *genWeightL;
                    for (unsigned int C2VCtr = 1; C2VCtr < startingWeightedCtrAr[0].size(); C2VCtr++){
                        passLepOrSemiLepChannelWeightedCtrAr[0][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                    }
                }
                else {
                    passLepOrSemiLepChannelWeightedCtrAr[1][0] = *genWeightL;
                    for (unsigned int C2VCtr = 1; C2VCtr < startingWeightedCtrAr[1].size(); C2VCtr++){
                        passLepOrSemiLepChannelWeightedCtrAr[1][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                    }
                }
                
            }
        
            if (debug) std::cout << "Test\n";
            
            if ((!passesCutsBool)) continue;
            

            bool passesSTCutBool = false;
            doHiggsFatJetCutSTWithBDTVars(dRCheckVecAr,ZPairPlusHInvMassCut,ZPairPlusHPtCut,ZPairPlusHInvMass,ZPairPlusHPt,passesSTCutBool);
            if (!passesSTCutBool) continue;
            if (debug) std::cout << " found Higgs fat jet\n";
            passHiggsFJCtr += 1;
            //passHiggsFJWeightedCtr += tmpGenWeights;
            


            if (falseHtobbMask) {
                passHiggsFJWeightedCtrAr[0][0] = *genWeightL;
                for (unsigned int C2VCtr = 1; C2VCtr < startingWeightedCtrAr[0].size(); C2VCtr++){
                    passHiggsFJWeightedCtrAr[0][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                }
            }
            else {
                passHiggsFJWeightedCtrAr[1][0] = *genWeightL;
                for (unsigned int C2VCtr = 1; C2VCtr < startingWeightedCtrAr[1].size(); C2VCtr++){
                    passHiggsFJWeightedCtrAr[1][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                }
            }
            

            if (passedAsSemiLepBool) {
                passHiggsFJSemiLepCtr += 1;
                


                if (falseHtobbMask) {
                    passHiggsFJWeightedSemiLepCtr[0][0] = *genWeightL;
                    for (unsigned int C2VCtr = 1; C2VCtr < startingWeightedCtrAr[0].size(); C2VCtr++){
                        passHiggsFJWeightedSemiLepCtr[0][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                    }
                }
                else {
                    passHiggsFJWeightedSemiLepCtr[1][0] = *genWeightL;
                    for (unsigned int C2VCtr = 1; C2VCtr < startingWeightedCtrAr[1].size(); C2VCtr++){
                        passHiggsFJWeightedSemiLepCtr[1][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                    }
                }
            
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
            doBJetVeto_WithBDTVariables(nJetLen,Jet_pt_FinalL,Jet_eta_FinalL,Jet_phi_FinalL,Jet_btagDeepFlavBL,hFatJet_phi_fromHTag,hFatJet_eta_fromHTag,dRCut,bTagCut,passBJetVeto,maxPassingBTag,debug);
            if (!passBJetVeto) continue;

            passVBFJetBVetoCtr += 1;
            //passVBFJetBVetoWeightedCtr += tmpGenWeights;
            


            if (falseHtobbMask) {
                passVBFJetBVetoWeightedCtr[0][0] = *genWeightL;
                for (unsigned int C2VCtr = 1; C2VCtr < startingWeightedCtrAr[0].size(); C2VCtr++){
                    passVBFJetBVetoWeightedCtr[0][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                }
            }
            else {
                passVBFJetBVetoWeightedCtr[1][0] = *genWeightL;
                for (unsigned int C2VCtr = 1; C2VCtr < startingWeightedCtrAr[1].size(); C2VCtr++){
                    passVBFJetBVetoWeightedCtr[1][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                }
            }
    

            if (passedAsSemiLepBool) {
                passVBFJetBVetoSemiLepCtr += 1;
                //passVBFJetBVetoWeightedSemiLepCtr += tmpGenWeights;
                


                if (falseHtobbMask) {
                    passVBFJetBVetoWeightedSemiLepCtr[0][0] = *genWeightL;
                    for (unsigned int C2VCtr = 1; C2VCtr < startingWeightedCtrAr[0].size(); C2VCtr++){
                        passVBFJetBVetoWeightedSemiLepCtr[0][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                    }
                }
                else {
                    passVBFJetBVetoWeightedSemiLepCtr[1][0] = *genWeightL;
                    for (unsigned int C2VCtr = 1; C2VCtr < startingWeightedCtrAr[1].size(); C2VCtr++){
                        passVBFJetBVetoWeightedSemiLepCtr[1][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                    }
                }
            
            }
            



            if (debug) std::cout << "Entering jet loop. Len: " << nJetLen << "\n";
            //doVBFJetCutPtSelectionWithBDTVars(nJetLen,Jet_ptL,Jet_jetIdL,Jet_etaL,Jet_phiL,Jet_massL,jetPTCut,jetEtaDifCut,jetInvMassCut,jetPairInvMass,jetLeadPt,jetLeadEta,jetLeadPhi,jetLeadMass,jetTrailingPt,jetTrailingEta,jetTrailingPhi,jetTrailingMass,leadJet_1,leadJet_2,dRCheckVecAr,dRCut,debug);
            //doVBFJetCutdEtaSelectionWithBDTVars(nJetLen,Jet_ptL,Jet_jetIdL,Jet_etaL,Jet_phiL,Jet_massL,jetPTCut,jetEtaDifCut,jetInvMassCut,jetPairInvMass,jetLeadPt,jetLeadEta,jetLeadPhi,jetLeadMass,jetTrailingPt,jetTrailingEta,jetTrailingPhi,jetTrailingMass,leadJet_1,leadJet_2,dRCheckVecAr,dRCut,debug);
            doVBFJetCutdEtaSelectionNoInvMassWithBDTVars(nJetLen,Jet_pt_FinalL,Jet_jetIdL,Jet_eta_FinalL,Jet_phi_FinalL,Jet_mass_FinalL,jetPTCut,jetEtaDifCut,jetInvMassCut,jetPairInvMass,jetLeadPt,jetLeadEta,jetLeadPhi,jetLeadMass,jetTrailingPt,jetTrailingEta,jetTrailingPhi,jetTrailingMass,leadJet_1,leadJet_2,dRCheckVecAr,dRCut,debug);
            //std::cout << jetLeadPt << endl;
            if (jetLeadPt == 0) continue;
            debugOutputForVBFJetCut(evCount,leadJet_1,leadJet_2,Jet_phi_FinalL,Jet_eta_FinalL,debug);
            passVBFJets += 1;

            ROOT::Math::PtEtaPhiMVector tmpLeadJetVec = ROOT::Math::PtEtaPhiMVector(jetLeadPt, jetLeadEta, jetLeadPhi, jetLeadMass);
            ROOT::Math::PtEtaPhiMVector tmpTrailingJetVec = ROOT::Math::PtEtaPhiMVector(jetTrailingPt, jetTrailingEta, jetTrailingPhi, jetTrailingMass);

            ROOT::Math::PtEtaPhiMVector tmpPtVecSumVec = tmpLeadJetVec + tmpTrailingJetVec;
            float tmpPtScalarSum = tmpLeadJetVec.Pt() + tmpTrailingJetVec.Pt();

            for (UInt_t dRCheckVecInd=0; dRCheckVecInd<dRCheckVecAr.size();dRCheckVecInd++) {
                tmpPtVecSumVec += dRCheckVecAr[dRCheckVecInd];
                tmpPtScalarSum += dRCheckVecAr[dRCheckVecInd].Pt();
            }

            dRCheckVecAr.push_back(tmpLeadJetVec);
            dRCheckVecAr.push_back(tmpTrailingJetVec);

            if (passesCutsBool){
                passVBFJetsCtr += 1;
                //passVBFJetsWeightedCtr += tmpGenWeights;
                


                if (falseHtobbMask) {
                    passVBFJetsWeightedCtr[0][0] = *genWeightL;
                    for (unsigned int C2VCtr = 1; C2VCtr < startingWeightedCtrAr[0].size(); C2VCtr++){
                        passVBFJetsWeightedCtr[0][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                    }
                }
                else {
                    passVBFJetsWeightedCtr[1][0] = *genWeightL;
                    for (unsigned int C2VCtr = 1; C2VCtr < startingWeightedCtrAr[1].size(); C2VCtr++){
                        passVBFJetsWeightedCtr[1][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                    }
                }

                bool passVetoLep = true;
                //if any veto leptons, check if they are close to the other objects
                //if there are any that aren't close, veto the event
                for (UInt_t elecItr=0; elecItr < *nVetoElecL; elecItr++){
                    //Loop through dRCheckVecAr
                    for (UInt_t dRCheckVecInd=0; dRCheckVecInd<dRCheckVecAr.size();dRCheckVecInd++) {
                        float tmpDeltaR = calcDeltaR(Electron_phiL[vetoElecIndL[elecItr]],Electron_etaL[vetoElecIndL[elecItr]],dRCheckVecAr[dRCheckVecInd].Phi(),dRCheckVecAr[dRCheckVecInd].Eta());

                        if (tmpDeltaR > lepVetodRCut){
                            passVetoLep = false;
                            break;
                        }
                    }
                    if (!passVetoLep) break;
                }
                if (!passVetoLep) continue;
                //now check muons
                for (UInt_t muItr=0; muItr < *nVetoMuonL; muItr++){
                    //Loop through dRCheckVecAr
                    for (UInt_t dRCheckVecInd=0; dRCheckVecInd<dRCheckVecAr.size();dRCheckVecInd++) {
                        float tmpDeltaR = calcDeltaR(Muon_phiL[vetoMuonIndL[muItr]],Muon_etaL[vetoMuonIndL[muItr]],dRCheckVecAr[dRCheckVecInd].Phi(),dRCheckVecAr[dRCheckVecInd].Eta());

                        if (tmpDeltaR > lepVetodRCut){
                            passVetoLep = false;
                            break;
                        }
                    }
                    if (!passVetoLep) break;
                }
                if (!passVetoLep) continue;

                passLepVetoCtr += 1;

                if (falseHtobbMask) {
                    passLepVetoWeightedCtr[0][0] = *genWeightL;
                    for (unsigned int C2VCtr = 1; C2VCtr < startingWeightedCtrAr[0].size(); C2VCtr++){
                        passLepVetoWeightedCtr[0][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                    }
                }
                else {
                    passLepVetoWeightedCtr[1][0] = *genWeightL;
                    for (unsigned int C2VCtr = 1; C2VCtr < startingWeightedCtrAr[1].size(); C2VCtr++){
                        passLepVetoWeightedCtr[1][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                    }
                }

                //get number of passing VBFJets

                UInt_t tmpnAK4JetsPassing = 0;

                for (UInt_t nJetItr=0; nJetItr<nJetLen;nJetItr++){
                    UInt_t tmpJetPt = Jet_pt_FinalL[nJetItr];
                    //Jet_etaL[nJetItr]
                    Int_t tmpJetId = Jet_jetIdL[nJetItr];
                    if (tmpJetPt < 30 || !(tmpJetId == 6)) continue;
                    tmpnAK4JetsPassing += 1;

                
                }
            

                //std::cout << passedAsLepBool << " "<< passedAsSemiLepBool << " " << passedAsHadBool << "\n";
                if (passedAsSemiLepBool){


                    passAsSemiLepCtr += 1;

                    if (falseHtobbMask) {
                        passAsSemiLepWeightedCtr[0][0] = *genWeightL;
                        for (unsigned int C2VCtr = 1; C2VCtr < startingWeightedCtrAr[0].size(); C2VCtr++){
                            passAsSemiLepWeightedCtr[0][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                        }
                    }
                    else {
                        passAsSemiLepWeightedCtr[1][0] = *genWeightL;
                        for (unsigned int C2VCtr = 1; C2VCtr < startingWeightedCtrAr[1].size(); C2VCtr++){
                            passAsSemiLepWeightedCtr[1][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                        }
                    }


                    //EventCor/UncInds
                        JECCorInd_SL_L = JECCorInd;
                        JECCorUpOrDown_SL_L = JECCorUpOrDown;
                        RochInd_SL_L = RochInd;
                        JERInd_SL_L = JERInd;
                
                    nLHEReweightingWeight_SL_L = *nLHEReweightingWeightL;
                    for (UInt_t nReweightItr=0; nReweightItr<nLHEReweightingWeight_SL_L;nReweightItr++){
                        LHEReweightingWeight_SL_L.push_back(LHEReweightingWeightL[nReweightItr]);
                    }
                    passingEvGenWeight_SL_L = tmpGenWeights;

                    //passingEvFullWeight_SL_L = tmpGenWeights*XS*Run2Lumi/totWeight;

                    datasetType_SL_L = datasetType;
                    yearType_SL_L = yearType;

                    eventNAK4Jets_SL_L = nJetLen;
                    eventNAK8Jets_SL_L = nFatJetLen;
                    eventNMuons_SL_L = nmLep;
                    eventNElectrons_SL_L = neLep;

                    for (UInt_t nJetItr=0; nJetItr<nJetLen;nJetItr++){
                        Jet_eta_SL_L.push_back(Jet_etaL[nJetItr]);
                        Jet_pt_SL_L.push_back(Jet_ptL[nJetItr]);
                        Jet_phi_SL_L.push_back(Jet_phiL[nJetItr]);
                        Jet_mass_SL_L.push_back(Jet_massL[nJetItr]);
                        Jet_jetId_SL_L.push_back(Jet_jetIdL[nJetItr]);
                        Jet_btagDeepFlavB_SL_L.push_back(Jet_btagDeepFlavBL[nJetItr]);
                        Jet_hadronFlavour_SL_L.push_back(Jet_hadronFlavourL[nJetItr]);
                        Jet_eta_Final_SL_L.push_back(Jet_eta_FinalL[nJetItr]);
                        Jet_pt_Final_SL_L.push_back(Jet_pt_FinalL[nJetItr]);
                        Jet_phi_Final_SL_L.push_back(Jet_phi_FinalL[nJetItr]);
                        Jet_mass_Final_SL_L.push_back(Jet_mass_FinalL[nJetItr]);
                    }

                    eventNAK4JetsPassingCuts_SL_L = tmpnAK4JetsPassing;

                    selectedHiggsFJ_pt_SL_L = hFatJet_pt_fromHTag;
                    selectedZFJ_pt_SL_L = dRCheckVecAr[3].Pt();
                    selectedHiggsFJ_eta_SL_L = hFatJet_eta_fromHTag;
                    selectedZFJ_eta_SL_L = dRCheckVecAr[3].Eta();
                    selectedHiggsFJ_phi_SL_L = hFatJet_phi_fromHTag;
                    selectedZFJ_phi_SL_L = dRCheckVecAr[3].Phi();

                    selectedZFJ_InvMass_SL_L = dRCheckVecAr[3].M();
                    selectedHiggsFJ_InvMass_SL_L = dRCheckVecAr[2].M();

                    selectedZFJ_InvMassSoftDrop_SL_L = FatJet_msoftdropL[FJIndAr[0]];
                    selectedHiggsFJ_InvMassSoftDrop_SL_L = FatJet_msoftdropL[FJIndAr[1]];

                    selectedZFJ_InvMassPNRegress_SL_L = FatJet_particleNet_massL[FJIndAr[0]];
                    selectedHiggsFJ_InvMassPNRegress_SL_L = FatJet_particleNet_massL[FJIndAr[1]];
                    
                    selectedZFJ_ParticleNet_HbbvsQCD_SL_L = FatJet_particleNet_HbbvsQCDL[FJIndAr[0]];
                    selectedHiggsFJ_ParticleNet_HbbvsQCD_SL_L = FatJet_particleNet_HbbvsQCDL[FJIndAr[1]];
                    selectedZFJ_ParticleNet_ZvsQCD_SL_L = FatJet_particleNet_ZvsQCDL[FJIndAr[0]];
                    selectedHiggsFJ_ParticleNet_ZvsQCD_SL_L = FatJet_particleNet_ZvsQCDL[FJIndAr[1]];

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


                    goodGenZFJMatch_SL_L = false;
                    goodGenHFJMatch_SL_L = false;
                    goodZFJMatchToGen_SL_L = false;
                    goodHFJMatchToGen_SL_L = false;
                    eventGenSemileptonic_SL_L = false;
                    eventGenHToBB_SL_L = false;
                    ZFJGenHadronFlavour_SL_L = -1;
                    HFJGenHadronFlavour_SL_L = -1;
                    FatJet_hadronFlavour_SL_L =  -1;
                    ZReconstructedWithCorrectFJ_SL_L = false;
                    HReconstructedWithCorrectFJ_SL_L = false;

                    ZReconstructedWithHFJ_SL_L = false;
                    HReconstructedWithZFJ_SL_L = false;

                    firstHToBBBool_SL_L = *HTobbBoolL;

                    ZOneType_SL_L = -1;
                    ZTwoType_SL_L = -1;

                    //HLT 
                    HLT_Ele32_WPTight_Gsf_L1DoubleEG_SL_L = *HLT_Ele32_WPTight_Gsf_L1DoubleEGL;
                    HLT_IsoMu27_SL_L = *HLT_IsoMu27L;
                    HLT_Mu50_SL_L = *HLT_Mu50L;
                    HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_SL_L = *HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZL;
                    HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_SL_L = *HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8L;

                    HLT_Ele27_WPTight_Gsf_SL_L = *HLT_Ele27_WPTight_GsfL;
                    HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_SL_L = *HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZL;

                    tightLepLeadIsElec_SL_L = *tightLepLeadIsElecL;
                    tightLepTrailingIsElec_SL_L = *tightLepTrailingIsElecL;
                    tightLepLeadIsMuon_SL_L = *tightLepLeadIsMuonL;
                    tightLepTrailingIsMuon_SL_L = *tightLepTrailingIsMuonL;
                    tightLepLeadInd_SL_L = *tightLepLeadIndL;
                    tightLepTrailingInd_SL_L = *tightLepTrailingIndL;
                
                    tightLepLeadPt_SL_L = *tightLepLeadPtL;
                    tightLepTrailingPt_SL_L = *tightLepTrailingPtL;
                    tightLepLeadEta_SL_L = *tightLepLeadEtaL;
                    tightLepTrailingEta_SL_L = *tightLepTrailingEtaL;
                    tightLepLeadPhi_SL_L = *tightLepLeadPhiL;
                    tightLepTrailingPhi_SL_L = *tightLepTrailingPhiL;
                    tightLepLeadMass_SL_L = *tightLepLeadMassL;
                    tightLepTrailingMass_SL_L = *tightLepTrailingMassL;
                    
                    nHDecayPID_SL_L = 0;

                    nZOneDecayPID_SL_L = 0;
                    nZTwoDecayPID_SL_L = 0;

                    //042024SFAndSuchAdditions
                    //PU JetID
                    for (UInt_t nJetItr=0; nJetItr<nJetLen;nJetItr++){
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
                    //additional 042024Branches starting with this script
                    //PUID SF check
                    for (UInt_t nJetItr=0; nJetItr<nJetLen;nJetItr++){
                        Jet_LowPtPassesPUIDL.push_back(Jet_LowPtPassesPUID[nJetItr]);
                    }

                    //more 042024Branches starting with selection
                    selectedLeadVBFJet_PUIDSFEligible_SL_L = Jet_LowPtPassesPUID[leadJet_1];
                    selectedTrailingVBFJet_PUIDSFEligible_SL_L = Jet_LowPtPassesPUID[leadJet_2];

                    //05052024 Additions for PN regress mass scaling and resolution corrections
                    luminosityBlock_SL_L = *luminosityBlock;
                    event_SL_L = *event;

                    selectedZFJ_InvMassPNRegress_JMSNomJMRNom_SL_L = FatJet_particleNet_mass_JMSNomJMRNomCor[FJIndAr[0]];
                    selectedZFJ_InvMassPNRegress_JMSUpJMRNom_SL_L = FatJet_particleNet_mass_JMSUpJMRNomCor[FJIndAr[0]];
                    selectedZFJ_InvMassPNRegress_JMSDownJMRNom_SL_L = FatJet_particleNet_mass_JMSDownJMRNomCor[FJIndAr[0]];
                    selectedZFJ_InvMassPNRegress_JMSNomJMRUp_SL_L = FatJet_particleNet_mass_JMSNomJMRUpCor[FJIndAr[0]];
                    selectedZFJ_InvMassPNRegress_JMSNomJMRDown_SL_L = FatJet_particleNet_mass_JMSNomJMRDownCor[FJIndAr[0]];

                    selectedHiggsFJ_InvMassPNRegress_JMSNomJMRNom_SL_L = FatJet_particleNet_mass_JMSNomJMRNomCor[FJIndAr[1]];
                    selectedHiggsFJ_InvMassPNRegress_JMSUpJMRNom_SL_L = FatJet_particleNet_mass_JMSUpJMRNomCor[FJIndAr[1]];
                    selectedHiggsFJ_InvMassPNRegress_JMSDownJMRNom_SL_L = FatJet_particleNet_mass_JMSDownJMRNomCor[FJIndAr[1]];
                    selectedHiggsFJ_InvMassPNRegress_JMSNomJMRUp_SL_L = FatJet_particleNet_mass_JMSNomJMRUpCor[FJIndAr[1]];
                    selectedHiggsFJ_InvMassPNRegress_JMSNomJMRDown_SL_L = FatJet_particleNet_mass_JMSNomJMRDownCor[FJIndAr[1]];

                    passingEvSemiLepTree->Fill();

                    LHEReweightingWeight_SL_L.clear();

                    Jet_eta_SL_L.clear();
                    Jet_pt_SL_L.clear();
                    Jet_phi_SL_L.clear();
                    Jet_mass_SL_L.clear();
                    Jet_jetId_SL_L.clear();
                    Jet_btagDeepFlavB_SL_L.clear();
                    Jet_hadronFlavour_SL_L.clear();
                    Jet_eta_Final_SL_L.clear();
                    Jet_pt_Final_SL_L.clear();
                    Jet_phi_Final_SL_L.clear();
                    Jet_mass_Final_SL_L.clear();

                    HDecayPID_SL_L.clear();
                    ZOneDecayPID_SL_L.clear();
                    ZTwoDecayPID_SL_L.clear();

                    Jet_puIdL.clear();

                    PSWeightL.clear();
                    LHEScaleWeightL.clear();
                    LHEPdfWeightL.clear();

                    Jet_LowPtPassesPUIDL.clear();

                
                    

                }

            }

        }
    }
    if (debug) std::cout << "Filling complete \n";

    clock_t endt = clock();
    double time_spent = (double)(endt - startt) / CLOCKS_PER_SEC;


    std::cout << "Finished file loop. " << "time: " << time_spent << "\n";
    //crossSection = crossSectionAvg / crossSectionCnt;
        
    std::cout << "XS: " << crossSection << "\n";
    std::cout << "nEv total: " << datanEv << "\n";
    std::cout << "nEv post pre-selection: " << datanEvPass << "\n"; 
    

    //--------------------HTobbChannel Output--------------


    std::cout << "==============================TOTAL COUNTERS==============================\n";
    
    std::cout << "startingCtr: " << startingCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "tryingSemiLepChannelCtr = " << tryingSemiLepChannelCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "passEnoughFJsInSemiLepChannelCtr = " << passEnoughFJsInSemiLepChannelCtr << "\n";
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
    std::cout << "UInt_t " << saveName << "PassSemiLepChannelCtr = " << passSemiLepChannelCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJCtr = " << passHiggsFJCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJSemiLepCtr = " << passHiggsFJSemiLepCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassVBFJetBVetoCtr = " << passVBFJetBVetoCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassVBFJetBVetoSemiLepCtr = " << passVBFJetBVetoSemiLepCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassVBFJetsCtr = " << passVBFJetsCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassLepVetoCtr = " << passLepVetoCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassAsSemiLepCtr = " << passAsSemiLepCtr << "\n";
    std::cout << "------------------------\n";


    std::string C2V2Str = "2p0";
    std::string C2V2MaStr = "C2W_2p0_C2Z_2p0";

    uint C2V2Point = 27;
    uint C2V2MaPoint = 83;

    if (isMariaSignal) {
        C2V2Str = C2V2MaStr;
        C2V2Point = C2V2MaPoint;

    }



    std::vector<std::vector<std::vector<Double_t>>> allWeightedCtrAr {startingWeightedCtrAr,
    passHiggsFJWeightedCtrAr,passHiggsFJWeightedSemiLepCtr,
    passChannelWeightedCtrAr,passLepOrSemiLepChannelWeightedCtrAr,
    tryingSemiLepChannelWeightedCtrAr,passHiggsFJInSemiLepChannelWeightedCtrAr,passFJInSemiLepChannelWeightedCtrAr,
    passEnoughFJsInSemiLepChannelWeightedCtrAr,passSemiLepLepCutWeightedCtrAr,passSemiLepChannelWeightedCtrAr,
    passVBFJetBVetoWeightedCtr,passVBFJetBVetoWeightedSemiLepCtr,
    passVBFJetsWeightedCtr,passLepVetoWeightedCtr,
    passAsSemiLepWeightedCtr,passSemiLepLepCutWeightedCtr};

    std::vector<string> allWeightedNameAr {"startingWeightedCtrAr",
    "passHiggsFJWeightedCtrAr","passHiggsFJWeightedSemiLepCtr",
    "passChannelWeightedCtrAr","passLepOrSemiLepChannelWeightedCtrAr",
    "tryingSemiLepChannelWeightedCtrAr","passHiggsFJInSemiLepChannelWeightedCtrAr","passFJInSemiLepChannelWeightedCtrAr",
    "passEnoughFJsInSemiLepChannelWeightedCtrAr","passSemiLepLepCutWeightedCtrAr","passSemiLepChannelWeightedCtrAr",
    "passVBFJetBVetoWeightedCtr","passVBFJetBVetoWeightedSemiLepCtr",
    "passVBFJetsWeightedCtr","passLepVetoWeightedCtr",
    "passAsSemiLepWeightedCtr","passSemiLepLepCutWeightedCtr"};
    for (unsigned int allItr = 0; allItr < allWeightedNameAr.size(); allItr++){
        std::cout << allWeightedNameAr[allItr] << "\n";
        for (unsigned int htobbItr = 0; htobbItr < htobbNameAr.size(); htobbItr++){
            std::cout << htobbNameAr[htobbItr] << "\n";
            
            for (unsigned int loopItr = 0; loopItr < C2VNameAr.size(); loopItr++){
                if (loopItr == C2VNameAr.size() - 1) {
                    std::cout << "(" << C2VNameAr[loopItr] << "," << allWeightedCtrAr[allItr][htobbItr][loopItr + 1] << ")\n";
                }
                else std::cout << "(" << C2VNameAr[loopItr] << "," << allWeightedCtrAr[allItr][htobbItr][loopItr + 1] << "),";
                if (loopItr == C2V2Point) {
                    std::cout << "(" << C2V2Str << "," << allWeightedCtrAr[allItr][htobbItr][0] << "),";
                }
            }
        
        }
        std::cout << "-------------------------------\n";
    }



    outFile->cd();
    weightSumsTree->Write("",TObject::kOverwrite);
    runTree->Write("",TObject::kOverwrite);
    passingEvSemiLepTree->Write("",TObject::kOverwrite);

    outFile->Close();

}