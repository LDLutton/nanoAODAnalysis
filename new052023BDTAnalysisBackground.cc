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


void new052023BDTAnalysisBackground(string datasetString,string yearString){
    // Open the file. Note that the name of your file outside this class
    // will probably NOT be experiment.root.
    std::cout << "start Analysis\n";
    clock_t startt = clock();
    //Analyzer will run over all files put into fileAr

    std::vector<std::string> fileAr;


    std::string saveName;
    float crossSection;
    bool isBackground;
    bool useLHETree = false;
    bool useFJGenMatchTree = false;
    bool useJGenMatchTree = false;

    if (datasetString == "testRun") testRun = true;
    if (datasetString == "ttHToBB") ttHToBBBackground = true;
    if (datasetString == "ttZJets") ttZJetsBackground = true;
    if (datasetString == "DY") DYBackground = true;
    if (datasetString == "QCDPT170to300") QCDPT170to300Background = true;
    if (datasetString == "QCDPT300to470") QCDPT300to470Background = true;
    if (datasetString == "QCDPT470to600") QCDPT470to600Background = true;
    if (datasetString == "QCDPT600to800") QCDPT600to800Background = true;
    if (datasetString == "QCDPT800to1000") QCDPT800to1000Background = true;
    if (datasetString == "QCDPT1000to1400") QCDPT1000to1400Background = true;
    if (datasetString == "QCDPT1400to1800") QCDPT1400to1800Background = true;
    if (datasetString == "QCDPT1800to2400") QCDPT1800to2400Background = true;
    if (datasetString == "QCDPT2400to3200") QCDPT2400to3200Background = true;
    if (datasetString == "QCDPT3200toInf") QCDPT3200toInfBackground = true;

    if (datasetString == "TTJets") TTJetsBackground = true;
    if (datasetString == "TTToHadronic") TTToHadronicBackground = true;
    if (datasetString == "TTTo2L2Nu") TTTo2L2NuBackground = true;
    if (datasetString == "TTToSemiLeptonic") TTToSemiLeptonicBackground = true;
    if (datasetString == "ST_s_Channel") ST_s_ChannelBackground = true;
    if (datasetString == "ST_t_ChannelAntiTop") ST_t_ChannelAntiTopBackground = true;
    if (datasetString == "ST_t_ChannelTop") ST_t_ChannelTopBackground = true;
    if (datasetString == "ZZTo2Q2Nu") ZZTo2Q2NuBackground = true;
    if (datasetString == "WWTo2L2Nu") WWTo2L2NuBackground = true;
    if (datasetString == "WZTo3LNu") WZTo3LNuBackground = true;
    if (datasetString == "ZZ") ZZBackground = true;
    if (datasetString == "WW") WWBackground = true;
    if (datasetString == "WZ") WZBackground = true;
    if (datasetString == "TTbb_TTToHadronic") TTbb_TTToHadronicBackground = true;
    if (datasetString == "TTbb_TTToSemiLeptonic") TTbb_TTToSemiLeptonicBackground = true;
    if (datasetString == "TTbb_TTTo2L2Nu") TTbb_TTTo2L2NuBackground = true;

    if (datasetString == "ttHToBBTrimmed") ttHToBBTrimmedBackground = true;
    if (datasetString == "ttZJetsTrimmed") ttZJetsTrimmedBackground = true;
    if (datasetString == "ttWJetsTrimmed") ttWJetsTrimmedBackground = true;
    if (datasetString == "DYTrimmed") DYTrimmedBackground = true;
    if (datasetString == "QCDPT170to300Trimmed") QCDPT170to300TrimmedBackground = true;
    if (datasetString == "QCDPT300to470Trimmed") QCDPT300to470TrimmedBackground = true;
    if (datasetString == "QCDPT470to600Trimmed") QCDPT470to600TrimmedBackground = true;
    if (datasetString == "QCDPT600to800Trimmed") QCDPT600to800TrimmedBackground = true;
    if (datasetString == "QCDPT800to1000Trimmed") QCDPT800to1000TrimmedBackground = true;
    if (datasetString == "QCDPT1000to1400Trimmed") QCDPT1000to1400TrimmedBackground = true;
    if (datasetString == "QCDPT1400to1800Trimmed") QCDPT1400to1800TrimmedBackground = true;
    if (datasetString == "QCDPT1800to2400Trimmed") QCDPT1800to2400TrimmedBackground = true;
    if (datasetString == "QCDPT2400to3200Trimmed") QCDPT2400to3200TrimmedBackground = true;
    if (datasetString == "QCDPT3200toInfTrimmed") QCDPT3200toInfTrimmedBackground = true;

    if (datasetString == "TTJetsTrimmed") TTJetsTrimmedBackground = true;
    if (datasetString == "ST_s_ChannelTrimmed") ST_s_ChannelTrimmedBackground = true;
    if (datasetString == "ST_t_ChannelAntiTopTrimmed") ST_t_ChannelAntiTopTrimmedBackground = true;
    if (datasetString == "ST_t_ChannelTopTrimmed") ST_t_ChannelTopTrimmedBackground = true;
    if (datasetString == "ZZTrimmed") ZZTrimmedBackground = true;
    if (datasetString == "WWTrimmed") WWTrimmedBackground = true;
    if (datasetString == "WZTrimmed") WZTrimmedBackground = true;
    if (datasetString == "TTbb_TTToHadronicTrimmed") TTbb_TTToHadronicTrimmedBackground = true;
    if (datasetString == "TTbb_TTToSemiLeptonicTrimmed") TTbb_TTToSemiLeptonicTrimmedBackground = true;
    if (datasetString == "TTbb_TTTo2L2NuTrimmed") TTbb_TTTo2L2NuTrimmedBackground = true;

    if (datasetString == "ttWJetsTrimmed") ttWJetsTrimmedBackground = true;
    if (datasetString == "DYM10To50Trimmed") DYM10To50TrimmedBackground = true;
    if (datasetString == "ST_tW_antitopTrimmed") ST_tW_antitopTrimmedBackground = true;
    if (datasetString == "ST_tW_topTrimmed") ST_tW_topTrimmedBackground = true;
    if (datasetString == "EWKWMinus2Jets_WToLNuTrimmed") EWKWMinus2Jets_WToLNuTrimmedBackground = true;
    if (datasetString == "EWKWMinus2Jets_WToQQTrimmed") EWKWMinus2Jets_WToQQTrimmedBackground = true;
    if (datasetString == "EWKWPlus2Jets_WToLNuTrimmed") EWKWPlus2Jets_WToLNuTrimmedBackground = true;
    if (datasetString == "EWKWPlus2Jets_WToQQTrimmed") EWKWPlus2Jets_WToQQTrimmedBackground = true;
    if (datasetString == "VHToNonbbTrimmed") VHToNonbbTrimmedBackground = true;
    if (datasetString == "WminusH_HToBB_WToLNuTrimmed") WminusH_HToBB_WToLNuTrimmedBackground = true;
    if (datasetString == "WminusH_HToBB_WToQQTrimmed") WminusH_HToBB_WToQQTrimmedBackground = true;
    if (datasetString == "WplusH_HToBB_WToLNuTrimmed") WplusH_HToBB_WToLNuTrimmedBackground = true;
    if (datasetString == "WplusH_HToBB_WToQQTrimmed") WplusH_HToBB_WToQQTrimmedBackground = true;
    if (datasetString == "WJetsToLNuTrimmed") WJetsToLNuTrimmedBackground = true;
    if (datasetString == "WWWTrimmed") WWWTrimmedBackground = true;
    if (datasetString == "WWZTrimmed") WWZTrimmedBackground = true;
    if (datasetString == "WZZTrimmed") WZZTrimmedBackground = true;
    if (datasetString == "ZH_HToBB_ZToBBTrimmed") ZH_HToBB_ZToBBTrimmedBackground = true;
    if (datasetString == "ZH_HToBB_ZToNuNuTrimmed") ZH_HToBB_ZToNuNuTrimmedBackground = true;
    if (datasetString == "ZH_HToBB_ZToLLTrimmed") ZH_HToBB_ZToLLTrimmedBackground = true;
    if (datasetString == "ZH_HToBB_ZToQQTrimmed") ZH_HToBB_ZToQQTrimmedBackground = true;
    if (datasetString == "ggZH_HToBB_ZToBBTrimmed") ggZH_HToBB_ZToBBTrimmedBackground = true;
    if (datasetString == "ggZH_HToBB_ZToNuNuTrimmed") ggZH_HToBB_ZToNuNuTrimmedBackground = true;
    if (datasetString == "ggZH_HToBB_ZToLLTrimmed") ggZH_HToBB_ZToLLTrimmedBackground = true;
    if (datasetString == "ggZH_HToBB_ZToQQTrimmed") ggZH_HToBB_ZToQQTrimmedBackground = true;
    if (datasetString == "EWKZ2Jets_ZToLLTrimmed") EWKZ2Jets_ZToLLTrimmedBackground = true;
    if (datasetString == "EWKZ2Jets_ZToNuNuTrimmed") EWKZ2Jets_ZToNuNuTrimmedBackground = true;
    if (datasetString == "EWKZ2Jets_ZToQQTrimmed") EWKZ2Jets_ZToQQTrimmedBackground = true;
    if (datasetString == "ZZZTrimmed") ZZZTrimmedBackground = true;

    if (datasetString == "LaraTest") LaraTest = true;
    Run2Lumi = 59830;
    UInt_t yearType = 0;
    if (yearString == "Y17") {
        yearType = 1;
        Run2Lumi = 41480;
    }
    if (yearString == "Y16") {
        yearType = 2;
        Run2Lumi = 16810;
    }
    if (yearString == "Y16APV") {
        yearType = 3;
        Run2Lumi = 19520;
    }

    ////////////////////////////////GETTING DATASET////////////////////////////////
    ////////////////////////////////GETTING DATASET////////////////////////////////
    ////////////////////////////////GETTING DATASET////////////////////////////////
    ////////////////////////////////GETTING DATASET////////////////////////////////

    std::string strAdd;
    if (scratchDown) strAdd ="/afs/crc.nd.edu/user/d/dlutton/Public/condorStuff/NanoAODToHistos/tmpHoldForNanoAODWithoutScratch/";
    else strAdd ="/scratch365/dlutton/HLTFilteredFiles/";
    if (localTest) strAdd = "";

    float totWeight = 1;

    UInt_t datasetType = 0;
    

    if (ttHToBBBackground){
        //saveName = "ttHToBB";
        crossSection = 0.5071*0.582;
        totWeight = 4834432.8;
        saveName = "ttHToBB";
        
        isBackground = true;
        datasetType = 2;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisttHToBB.root";
        fileAr.push_back(tmpStrWithPath);
        
    }
    else if (ttZJetsBackground){
        //saveName = "ttZJets";
        
        crossSection = 0.5407;
        saveName = "ttZJets";
        isBackground = true;
        totWeight = 32793821;
        datasetType = 3;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisttZJets.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (DYBackground){
        //saveName = "DY";
        
        //crossSection = 5364;
        crossSection = 6424;
        //totWeight = 96233326;
        totWeight = 3323478039000;
        saveName = "DY";

        isBackground = true;
        datasetType = 4;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisDY.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (QCDPT170to300Background){
        //saveName = "QCDPT170to300";
        
        crossSection = 103300.0;
        totWeight = 29478000;

        saveName = "QCDPT170to300";
        
        isBackground = true;
        datasetType = 15;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisQCDPT170to300.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (QCDPT300to470Background){
        //saveName = "QCDPT300to470";
        
        crossSection = 6826.0;
        totWeight = 57868000;

        saveName = "QCDPT300to470";
        
        isBackground = true;
        datasetType = 16;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisQCDPT300to470.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (QCDPT470to600Background){
        //saveName = "QCDPT470to600";
        
        crossSection = 552.6;
        totWeight = 51062083.800000004;
        
        saveName = "QCDPT470to600";

        isBackground = true;
        datasetType = 17;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisQCDPT470to600.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (QCDPT600to800Background){
        //saveName = "QCDPT600to800";
        
        crossSection = 156.6;
        totWeight = 66914000;

        saveName = "QCDPT600to800";
        
        isBackground = true;
        datasetType = 18;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisQCDPT600to800.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (QCDPT800to1000Background){
        //saveName = "QCDPT800to1000";
        
        crossSection = 26.32;
        totWeight = 36830000;

        saveName = "QCDPT800to1000";
        
        isBackground = true;
        datasetType = 19;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisQCDPT800to1000.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (QCDPT1000to1400Background){
        //saveName = "QCDPT1000to1400";
        
        crossSection = 7.5;
        totWeight = 19664000;


        saveName = "QCDPT1000to1400";
        
        isBackground = true;
        datasetType = 20;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisQCDPT1000to1400.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (QCDPT1400to1800Background){
        //saveName = "QCDPT1400to1800";
        
        crossSection = 0.6479;
        totWeight = 10982000;

        saveName = "QCDPT1400to1800";
        
        isBackground = true;
        datasetType = 21;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisQCDPT1400to1800.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (QCDPT1800to2400Background){
        //saveName = "QCDPT1800to2400";
        
        crossSection = 0.08715;
        totWeight = 5491000;

        saveName = "QCDPT1800to2400";
        
        isBackground = true;
        datasetType = 22;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisQCDPT1800to2400.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (QCDPT2400to3200Background){
        //saveName = "QCDPT2400to3200";
        
        crossSection = 0.005242;
        //totWeight = 2931000;
        totWeight = 2847000.0;

        saveName = "QCDPT2400to3200";
        
        isBackground = true;
        datasetType = 23;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisQCDPT2400to3200.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (QCDPT3200toInfBackground){
        //saveName = "QCDPT3200toInf";
        
        crossSection = 0.0001349;
        totWeight = 1000000;

        saveName = "QCDPT3200toInf";
        
        isBackground = true;
        datasetType = 24;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisQCDPT3200toInf.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (TTJetsBackground){
        //saveName = "QCDPT3200toInf";
        
        crossSection = 722.8;
        totWeight = 610815599000;

        saveName = "TTJets";
        
        isBackground = true;
        datasetType = 5;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisTTJets.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (ST_s_ChannelBackground){
        //saveName = "QCDPT3200toInf";
        
        crossSection = 3.74;
        totWeight = 68767088;

        saveName = "ST_s_Channel";
        
        isBackground = true;
        datasetType = 9;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisST_s_Channel.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (ST_t_ChannelAntiTopBackground){
        //saveName = "QCDPT3200toInf";
        
        crossSection = 69.09;
        //totWeight = 6014529940;
        totWeight = 6114949140.0;
        saveName = "ST_t_ChannelAntiTop";
        
        isBackground = true;
        datasetType = 10;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisST_t_ChannelAntiTop.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (ST_t_ChannelTopBackground){
        //saveName = "QCDPT3200toInf";
        
        crossSection = 115.3;
        totWeight = 18955976000;

        saveName = "ST_t_ChannelTop";
        
        isBackground = true;
        datasetType = 11;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisST_t_ChannelTop.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (ZZBackground){
        //saveName = "";
        
        crossSection = 12.17;
        totWeight = 3526000.0;

        saveName = "ZZ";
        
        isBackground = true;
        datasetType = 12;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisZZ.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (WWBackground){
        //saveName = "";
        
        crossSection = 75.95;
        totWeight = 15679125.299999999;

        saveName = "WW";
        
        isBackground = true;
        datasetType = 13;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisWW.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (WZBackground){
        //saveName = "";
        
        crossSection = 27.59;
        totWeight = 7940000.0;

        saveName = "WZ";
        
        isBackground = true;
        datasetType = 14;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisWZ.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (TTbb_TTToHadronicBackground){
        //saveName = "QCDPT3200toInf";
        
        crossSection = 5.5;
        totWeight = 160749330.0;

        saveName = "TTbb_TTToHadronic";
        
        isBackground = true;
        datasetType = 6;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisTTbb_TTToHadronic.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (TTbb_TTTo2L2NuBackground){
        //saveName = "";
        
        crossSection = 2.9;
        totWeight = 21986500.0;

        saveName = "TTbb_TTTo2L2Nu";
        
        isBackground = true;
        datasetType = 8;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisTTbb_TTTo2L2Nu.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (TTbb_TTToSemiLeptonicBackground){
        //saveName = "";
        
        crossSection = 4.7;
        totWeight = 233964864.0;

        saveName = "TTbb_TTToSemiLeptonic";
        
        isBackground = true;
        datasetType = 7;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisTTbb_TTToSemiLeptonic.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (ttHToBBTrimmedBackground){

        crossSection = 0.29513219999999996;
        if (yearType == 0){
            totWeight = 4843451.890000001;
        }
        else if (yearType == 1){
            totWeight = 3919780.398000001;
        }
        else if (yearType == 2){
            totWeight = 2470819.7700000005;
        }
        else if (yearType == 3){
            totWeight = 2315362.9999999995;
        }
        
        saveName = "TrimmedttHToBB"+yearString;

        isBackground = true;
        datasetType = 2;
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisttHToBB"+yearString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (ttZJetsTrimmedBackground){

        crossSection = 0.5407;
        if (yearType == 0){
            totWeight = 32793821.0;
        }
        else if (yearType == 1){
            totWeight = 31791133.0;
        }
        else if (yearType == 2){
            totWeight = 14329445.0;
        }
        else if (yearType == 3){
            totWeight = 17127762.0;
        }
        
        saveName = "TrimmedttZJets"+yearString;

        isBackground = true;
        datasetType = 3;
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisttZJets"+yearString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (DYTrimmedBackground){

        crossSection = 6424;
        if (yearType == 0){
            totWeight = 3323478039000.0;
        }
        else if (yearType == 1){
            totWeight = 3322971118000.0;
        }
        else if (yearType == 2){
            totWeight = 1220934300000.0;
        }
        else if (yearType == 3){
            totWeight = 1545708040000.0;
        }
        
        saveName = "TrimmedDY"+yearString;

        isBackground = true;
        datasetType = 4;
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisDY"+yearString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (QCDPT170to300TrimmedBackground){

        crossSection = 103300;
        if (yearType == 0){
            totWeight = 29478000.0;
        }
        else if (yearType == 1){
            totWeight = 29491000.0;
        }
        else if (yearType == 2){
            totWeight = 29758000.0;
        }
        else if (yearType == 3){
            totWeight = 27885000.0;
        }
        
        saveName = "TrimmedQCDPT170to300"+yearString;

        isBackground = true;
        datasetType = 15;
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisQCDPT170to300"+yearString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (QCDPT300to470TrimmedBackground){

        crossSection = 6826;
        if (yearType == 0){
            totWeight = 57868000.0;
        }
        else if (yearType == 1){
            totWeight = 55358000.0;
        }
        else if (yearType == 2){
            totWeight = 55264000.0;
        }
        else if (yearType == 3){
            totWeight = 54028000.0;
        }
        
        saveName = "TrimmedQCDPT300to470"+yearString;

        isBackground = true;
        datasetType = 16;
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisQCDPT300to470"+yearString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (QCDPT470to600TrimmedBackground){

        crossSection = 552.6;
        if (yearType == 0){
            totWeight = 52448083.800000004;
        }
        else if (yearType == 1){
            totWeight = 50475112.150000006;
        }
        else if (yearType == 2){
            totWeight = 52408079.3;
        }
        else if (yearType == 3){
            totWeight = 50782081.0;
        }
        
        saveName = "TrimmedQCDPT470to600"+yearString;

        isBackground = true;
        datasetType = 17;
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisQCDPT470to600"+yearString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (QCDPT600to800TrimmedBackground){

        crossSection = 156.6;
        if (yearType == 0){
            totWeight = 66914000.0;
        }
        else if (yearType == 1){
            totWeight = 66419000.0;
        }
        else if (yearType == 2){
            totWeight = 64584000.0;
        }
        else if (yearType == 3){
            totWeight = 61904000.0;
        }
        
        saveName = "TrimmedQCDPT600to800"+yearString;

        isBackground = true;
        datasetType = 18;
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisQCDPT600to800"+yearString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (QCDPT800to1000TrimmedBackground){

        crossSection = 26.32;
        if (yearType == 0){
            totWeight = 36830000.0;
        }
        else if (yearType == 1){
            totWeight = 36890000.0;
        }
        else if (yearType == 2){
            totWeight = 37698000.0;
        }
        else if (yearType == 3){
            totWeight = 35459000.0;
        }
        
        saveName = "TrimmedQCDPT800to1000"+yearString;

        isBackground = true;
        datasetType = 19;
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisQCDPT800to1000"+yearString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (QCDPT1000to1400TrimmedBackground){

        crossSection = 7.5;
        if (yearType == 0){
            totWeight = 19664000.0;
        }
        else if (yearType == 1){
            totWeight = 19461000.0;
        }
        else if (yearType == 2){
            totWeight = 19892000.0;
        }
        else if (yearType == 3){
            totWeight = 19077000.0;
        }
        
        saveName = "TrimmedQCDPT1000to1400"+yearString;

        isBackground = true;
        datasetType = 20;
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisQCDPT1000to1400"+yearString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (QCDPT1400to1800TrimmedBackground){

        crossSection = 0.6479;
        if (yearType == 0){
            totWeight = 10982000.0;
        }
        else if (yearType == 1){
            totWeight = 10994000.0;
        }
        else if (yearType == 2){
            totWeight = 10722000.0;
        }
        else if (yearType == 3){
            totWeight = 11000000.0;
        }
        
        saveName = "TrimmedQCDPT1400to1800"+yearString;

        isBackground = true;
        datasetType = 21;
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisQCDPT1400to1800"+yearString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (QCDPT1800to2400TrimmedBackground){

        crossSection = 0.08715;
        if (yearType == 0){
            totWeight = 5491000.0;
        }
        else if (yearType == 1){
            totWeight = 5168000.0;
        }
        else if (yearType == 2){
            totWeight = 5236000.0;
        }
        else if (yearType == 3){
            totWeight = 5262000.0;
        }
        
        saveName = "TrimmedQCDPT1800to2400"+yearString;

        isBackground = true;
        datasetType = 22;
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisQCDPT1800to2400"+yearString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (QCDPT2400to3200TrimmedBackground){

        crossSection = 0.005242;
        if (yearType == 0){
            totWeight = 2931000.0;
        }
        else if (yearType == 1){
            totWeight = 2997000.0;
        }
        else if (yearType == 2){
            totWeight = 2848000.0;
        }
        else if (yearType == 3){
            totWeight = 2999000.0;
        }
        
        saveName = "TrimmedQCDPT2400to3200"+yearString;

        isBackground = true;
        datasetType = 23;
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisQCDPT2400to3200"+yearString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (QCDPT3200toInfTrimmedBackground){

        crossSection = 0.0001349;
        if (yearType == 0){
            totWeight = 1000000.0;
        }
        else if (yearType == 1){
            totWeight = 1000000.0;
        }
        else if (yearType == 2){
            totWeight = 996000.0;
        }
        else if (yearType == 3){
            totWeight = 1000000.0;
        }
        
        saveName = "TrimmedQCDPT3200toInf"+yearString;

        isBackground = true;
        datasetType = 24;
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisQCDPT3200toInf"+yearString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (ST_s_ChannelTrimmedBackground){

        crossSection = 3.74;
        if (yearType == 0){
            totWeight = 68767088.0;
        }
        else if (yearType == 1){
            totWeight = 48361399.0;
        }
        else if (yearType == 2){
            totWeight = 19433136.53;
        }
        else if (yearType == 3){
            totWeight = 19596255.0;
        }
        
        saveName = "TrimmedST_s_Channel"+yearString;

        isBackground = true;
        datasetType = 9;
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisST_s_Channel"+yearString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (ST_t_ChannelAntiTopTrimmedBackground){

        crossSection = 69.09;
        if (yearType == 0){
            totWeight = 6114949140.0;
        }
        else if (yearType == 1){
            totWeight = 4462869700.0;
        }
        else if (yearType == 2){
            totWeight = 1957283170.0;
        }
        else if (yearType == 3){
            totWeight = 1983864428.0;
        }
        
        saveName = "TrimmedST_t_ChannelAntiTop"+yearString;

        isBackground = true;
        datasetType = 10;
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisST_t_ChannelAntiTop"+yearString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (ST_t_ChannelTopTrimmedBackground){

        crossSection = 115.3;
        if (yearType == 0){
            totWeight = 18955976000.0;
        }
        else if (yearType == 1){
            totWeight = 13808002655.0;
        }
        else if (yearType == 2){
            totWeight = 6703801811.0;
        }
        else if (yearType == 3){
            totWeight = 5948133240.0;
        }
        
        saveName = "TrimmedST_t_ChannelTop"+yearString;

        isBackground = true;
        datasetType = 11;
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisST_t_ChannelTop"+yearString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (TTJetsTrimmedBackground){

        crossSection = 722.8;
        if (yearType == 0){
            totWeight = 610815599000.0;
        }
        else if (yearType == 1){
            totWeight = 497148414000.0;
        }
        else if (yearType == 2){
            totWeight = 178352266900.0;
        }
        else if (yearType == 3){
            totWeight = 188323895600.0;
        }
        
        saveName = "TrimmedTTJets"+yearString;

        isBackground = true;
        datasetType = 5;
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisTTJets"+yearString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (WWTrimmedBackground){

        crossSection = 75.95;
        if (yearType == 0){
            totWeight = 15679125.299999999;
        }
        else if (yearType == 1){
            totWeight = 15634113.2;
        }
        else if (yearType == 2){
            totWeight = 15821146.729999997;
        }
        else if (yearType == 3){
            totWeight = 15859132.4;
        }
        
        saveName = "TrimmedWW"+yearString;

        isBackground = true;
        datasetType = 13;
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisWW"+yearString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (WZTrimmedBackground){

        crossSection = 27.59;
        if (yearType == 0){
            totWeight = 7940000.0;
        }
        else if (yearType == 1){
            totWeight = 7889000.0;
        }
        else if (yearType == 2){
            totWeight = 7584000.0;
        }
        else if (yearType == 3){
            totWeight = 7934000.0;
        }
        
        saveName = "TrimmedWZ"+yearString;

        isBackground = true;
        datasetType = 14;
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisWZ"+yearString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (ZZTrimmedBackground){

        crossSection = 12.17;
        if (yearType == 0){
            totWeight = 3526000.0;
        }
        else if (yearType == 1){
            totWeight = 2704470.0;
        }
        else if (yearType == 2){
            totWeight = 1151000.0;
        }
        else if (yearType == 3){
            totWeight = 1282000.0;
        }
        
        saveName = "TrimmedZZ"+yearString;

        isBackground = true;
        datasetType = 12;
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisZZ"+yearString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (TTbb_TTTo2L2NuTrimmedBackground){

        crossSection = 2.9;
        if (yearType == 0){
            totWeight = 21986500.0;
        }
        else if (yearType == 1){
            totWeight = 15930875.0;
        }
        else if (yearType == 2){
            totWeight = 7209373.0;
        }
        else if (yearType == 3){
            totWeight = 6367619.0;
        }
        
        saveName = "TrimmedTTbb_TTTo2L2Nu"+yearString;

        isBackground = true;
        datasetType = 8;
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisTTbb_TTTo2L2Nu"+yearString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (TTbb_TTToHadronicTrimmedBackground){

        crossSection = 5.5;
        if (yearType == 0){
            totWeight = 160749330.0;
        }
        else if (yearType == 1){
            totWeight = 113736153.5;
        }
        else if (yearType == 2){
            totWeight = 51913700.0;
        }
        else if (yearType == 3){
            totWeight = 46015100.0;
        }
        
        saveName = "TrimmedTTbb_TTToHadronic"+yearString;

        isBackground = true;
        datasetType = 6;
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisTTbb_TTToHadronic"+yearString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (TTbb_TTToSemiLeptonicTrimmedBackground){

        crossSection = 4.7;
        if (yearType == 0){
            totWeight = 233964864.0;
        }
        else if (yearType == 1){
            totWeight = 153797770.0;
        }
        else if (yearType == 2){
            totWeight = 61707077.0;
        }
        else if (yearType == 3){
            totWeight = 57255440.0;
        }
        
        saveName = "TrimmedTTbb_TTToSemiLeptonic"+yearString;

        isBackground = true;
        datasetType = 7;
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisTTbb_TTToSemiLeptonic"+yearString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (ttWJetsTrimmedBackground){

        crossSection = 0.4611;
        if (yearType == 0){
            totWeight = 27686858.0;
        }
        else if (yearType == 1){
            totWeight = 27662128.0;
        }
        else if (yearType == 2){
            totWeight = 14396001.0;
        }
        else if (yearType == 3){
            totWeight = 14186419.0;
        }
        
        saveName = "TrimmedttWJets"+yearString;

        isBackground = true;
        datasetType = 50;
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisttWJets"+yearString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (DYM10To50TrimmedBackground){

        crossSection = 20490;
        if (yearType == 0){
            totWeight = 3351537100000.0;
        }
        else if (yearType == 1){
            totWeight = 3240932300000.0;
        }
        else if (yearType == 2){
            totWeight = 1664772700000.0;
        }
        else if (yearType == 3){
            totWeight = 1677278070000.0;
        }
        
        saveName = "TrimmedDYM10To50"+yearString;

        isBackground = true;
        datasetType = 51;
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisDYM10To50"+yearString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (ST_tW_antitopTrimmedBackground){

        crossSection = 32.51;
        if (yearType == 0){
            totWeight = 251902108.0;
        }
        else if (yearType == 1){
            totWeight = 184446275.0;
        }
        else if (yearType == 2){
            totWeight = 83024122.0;
        }
        else if (yearType == 3){
            totWeight = 74766330.0;
        }
        
        saveName = "TrimmedST_tW_antitop"+yearString;

        isBackground = true;
        datasetType = 52;
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisST_tW_antitop"+yearString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (ST_tW_topTrimmedBackground){

        crossSection = 32.45;
        if (yearType == 0){
            totWeight = 258137399.49999997;
        }
        else if (yearType == 1){
            totWeight = 183284979.29999998;
        }
        else if (yearType == 2){
            totWeight = 80821413.6;
        }
        else if (yearType == 3){
            totWeight = 74624684.0;
        }
        
        saveName = "TrimmedST_tW_top"+yearString;

        isBackground = true;
        datasetType = 53;
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisST_tW_top"+yearString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (EWKWMinus2Jets_WToLNuTrimmedBackground){

        crossSection = 32.05;
        if (yearType == 0){
            totWeight = 4479000.0;
        }
        else if (yearType == 1){
            totWeight = 4077000.0;
        }
        else if (yearType == 2){
            totWeight = 2202000.0;
        }
        else if (yearType == 3){
            totWeight = 2248000.0;
        }
        
        saveName = "TrimmedEWKWMinus2Jets_WToLNu"+yearString;

        isBackground = true;
        datasetType = 54;
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisEWKWMinus2Jets_WToLNu"+yearString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (EWKWPlus2Jets_WToLNuTrimmedBackground){

        crossSection = 39.13;
        if (yearType == 0){
            totWeight = 4488000.0;
        }
        else if (yearType == 1){
            totWeight = 3595000.0;
        }
        else if (yearType == 2){
            totWeight = 2033000.0;
        }
        else if (yearType == 3){
            totWeight = 2185000.0;
        }
        
        saveName = "TrimmedEWKWPlus2Jets_WToLNu"+yearString;

        isBackground = true;
        datasetType = 56;
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisEWKWPlus2Jets_WToLNu"+yearString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (EWKWMinus2Jets_WToQQTrimmedBackground){

        crossSection = 19.19;
        if (yearType == 0){
            totWeight = 9655000.0;
        }
        else if (yearType == 1){
            totWeight = 7874000.0;
        }
        else if (yearType == 2){
            totWeight = 4998130.0;
        }
        else if (yearType == 3){
            totWeight = 4999000.0;
        }
        
        saveName = "TrimmedEWKWMinus2Jets_WToQQ"+yearString;

        isBackground = true;
        datasetType = 55;
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisEWKWMinus2Jets_WToQQ"+yearString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (EWKWPlus2Jets_WToQQTrimmedBackground){

        crossSection = 28.71;
        if (yearType == 0){
            totWeight = 9991000.0;
        }
        else if (yearType == 1){
            totWeight = 7994000.0;
        }
        else if (yearType == 2){
            totWeight = 4998118.0;
        }
        else if (yearType == 3){
            totWeight = 4943000.0;
        }
        
        saveName = "TrimmedEWKWPlus2Jets_WToQQ"+yearString;

        isBackground = true;
        datasetType = 57;
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisEWKWPlus2Jets_WToQQ"+yearString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (VHToNonbbTrimmedBackground){

        crossSection = 2.605;
        if (yearType == 0){
            totWeight = 7023767.399999999;
        }
        else if (yearType == 1){
            totWeight = 5066307.699999999;
        }
        else if (yearType == 2){
            totWeight = 1917609.33;
        }
        else if (yearType == 3){
            totWeight = 2561274.6000000006;
        }
        
        saveName = "TrimmedVHToNonbb"+yearString;

        isBackground = true;
        datasetType = 58;
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisVHToNonbb"+yearString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (WminusH_HToBB_WToLNuTrimmedBackground){

        crossSection = 0.177;
        if (yearType == 0){
            totWeight = 862915.6845000001;
        }
        else if (yearType == 1){
            totWeight = 838429.8309999999;
        }
        else if (yearType == 2){
            totWeight = 396666.2394000001;
        }
        else if (yearType == 3){
            totWeight = 456329.16;
        }
        
        saveName = "TrimmedWminusH_HToBB_WToLNu"+yearString;

        isBackground = true;
        datasetType = 59;
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisWminusH_HToBB_WToLNu"+yearString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (WminusH_HToBB_WToQQTrimmedBackground){

        crossSection = 0.3675;
        if (yearType == 0){
            totWeight = 3676316.52;
        }
        else if (yearType == 1){
            totWeight = 2924795.0339999995;
        }
        else if (yearType == 2){
            totWeight = 1836585.5289999996;
        }
        else if (yearType == 3){
            totWeight = 1794191.0599999998;
        }
        
        saveName = "TrimmedWminusH_HToBB_WToQQ"+yearString;

        isBackground = true;
        datasetType = 60;
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisWminusH_HToBB_WToQQ"+yearString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (WplusH_HToBB_WToLNuTrimmedBackground){

        crossSection = 0.2832;
        if (yearType == 0){
            totWeight = 1377078.4579999996;
        }
        else if (yearType == 1){
            totWeight = 1379070.2299999997;
        }
        else if (yearType == 2){
            totWeight = 630588.626;
        }
        else if (yearType == 3){
            totWeight = 745714.035;
        }
        
        saveName = "TrimmedWplusH_HToBB_WToLNu"+yearString;

        isBackground = true;
        datasetType = 61;
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisWplusH_HToBB_WToLNu"+yearString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (WplusH_HToBB_WToQQTrimmedBackground){

        crossSection = 0.589;
        if (yearType == 0){
            totWeight = 5600077.85;
        }
        else if (yearType == 1){
            totWeight = 4609323.54;
        }
        else if (yearType == 2){
            totWeight = 2910762.9379999996;
        }
        else if (yearType == 3){
            totWeight = 2934336.9399999995;
        }
        
        saveName = "TrimmedWplusH_HToBB_WToQQ"+yearString;

        isBackground = true;
        datasetType = 62;
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisWplusH_HToBB_WToQQ"+yearString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (WJetsToLNuTrimmedBackground){

        crossSection = 66680.0;
        if (yearType == 0){
            totWeight = 5018114340000.0;
        }
        else if (yearType == 1){
            totWeight = 4559894064000.0;
        }
        else if (yearType == 2){
            totWeight = 4872963500000.0;
        }
        else if (yearType == 3){
            totWeight = 4989518390000.0;
        }
        
        saveName = "TrimmedWJetsToLNu"+yearString;

        isBackground = true;
        datasetType = 63;
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisWJetsToLNu"+yearString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (WWWTrimmedBackground){

        crossSection = 0.2158;
        if (yearType == 0){
            totWeight = 2135751.129;
        }
        else if (yearType == 1){
            totWeight = 2127101.264;
        }
        else if (yearType == 2){
            totWeight = 897983.3620000002;
        }
        else if (yearType == 3){
            totWeight = 1120296.68;
        }
        
        saveName = "TrimmedWWW"+yearString;

        isBackground = true;
        datasetType = 64;
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisWWW"+yearString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (WWZTrimmedBackground){

        crossSection = 0.1707;
        if (yearType == 0){
            totWeight = 1572221.397;
        }
        else if (yearType == 1){
            totWeight = 1697048.0349999997;
        }
        else if (yearType == 2){
            totWeight = 784714.14;
        }
        else if (yearType == 3){
            totWeight = 866227.1599999999;
        }
        
        saveName = "TrimmedWWZ"+yearString;

        isBackground = true;
        datasetType = 65;
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisWWZ"+yearString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (WZZTrimmedBackground){

        crossSection = 0.05709;
        if (yearType == 0){
            totWeight = 571468.7320000001;
        }
        else if (yearType == 1){
            totWeight = 565804.579;
        }
        else if (yearType == 2){
            totWeight = 260326.46;
        }
        else if (yearType == 3){
            totWeight = 308416.94;
        }
        
        saveName = "TrimmedWZZ"+yearString;

        isBackground = true;
        datasetType = 66;
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisWZZ"+yearString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (ZH_HToBB_ZToBBTrimmedBackground){

        crossSection = 0.5612;
        if (yearType == 0){
            totWeight = 2686414.836;
        }
        else if (yearType == 1){
            totWeight = 2663478.1038999995;
        }
        else if (yearType == 2){
            totWeight = 1240904.3085000003;
        }
        else if (yearType == 3){
            totWeight = 1448833.7057000003;
        }
        
        saveName = "TrimmedZH_HToBB_ZToBB"+yearString;

        isBackground = true;
        datasetType = 75;
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisZH_HToBB_ZToBB"+yearString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (ZH_HToBB_ZToLLTrimmedBackground){

        crossSection = 0.07977;
        if (yearType == 0){
            totWeight = 389609.65400000004;
        }
        else if (yearType == 1){
            totWeight = 367961.3039;
        }
        else if (yearType == 2){
            totWeight = 176165.53599999993;
        }
        else if (yearType == 3){
            totWeight = 212477.136;
        }
        
        saveName = "TrimmedZH_HToBB_ZToLL"+yearString;

        isBackground = true;
        datasetType = 67;
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisZH_HToBB_ZToLL"+yearString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (ZH_HToBB_ZToNuNuTrimmedBackground){

        crossSection = 0.1573;
        if (yearType == 0){
            totWeight = 361453.3201;
        }
        else if (yearType == 1){
            totWeight = 742376.6619999999;
        }
        else if (yearType == 2){
            totWeight = 346164.48300000007;
        }
        else if (yearType == 3){
            totWeight = 401141.5949;
        }
        
        saveName = "TrimmedZH_HToBB_ZToNuNu"+yearString;

        isBackground = true;
        datasetType = 76;
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisZH_HToBB_ZToNuNu"+yearString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (ZH_HToBB_ZToQQTrimmedBackground){

        crossSection = 0.5612;
        if (yearType == 0){
            totWeight = 5611321.760000001;
        }
        else if (yearType == 1){
            totWeight = 5523315.285000001;
        }
        else if (yearType == 2){
            totWeight = 2574971.707000001;
        }
        else if (yearType == 3){
            totWeight = 3031836.7879999997;
        }
        
        saveName = "TrimmedZH_HToBB_ZToQQ"+yearString;

        isBackground = true;
        datasetType = 68;
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisZH_HToBB_ZToQQ"+yearString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (ggZH_HToBB_ZToBBTrimmedBackground){

        crossSection = 0.04319;
        if (yearType == 0){
            totWeight = 200515.39800000004;
        }
        else if (yearType == 1){
            totWeight = 203165.06699999998;
        }
        else if (yearType == 2){
            totWeight = 92902.46724999997;
        }
        else if (yearType == 3){
            totWeight = 104596.24113999997;
        }
        
        saveName = "TrimmedggZH_HToBB_ZToBB"+yearString;

        isBackground = true;
        datasetType = 77;
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisggZH_HToBB_ZToBB"+yearString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (ggZH_HToBB_ZToLLTrimmedBackground){

        crossSection = 0.006185;
        if (yearType == 0){
            totWeight = 30249.127000000008;
        }
        else if (yearType == 1){
            totWeight = 28900.881299999994;
        }
        else if (yearType == 2){
            totWeight = 13538.205100000001;
        }
        else if (yearType == 3){
            totWeight = 14942.124299999996;
        }
        
        saveName = "TrimmedggZH_HToBB_ZToLL"+yearString;

        isBackground = true;
        datasetType = 69;
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisggZH_HToBB_ZToLL"+yearString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (ggZH_HToBB_ZToNuNuTrimmedBackground){

        crossSection = 0.01222;
        if (yearType == 0){
            totWeight = 59566.16379999999;
        }
        else if (yearType == 1){
            totWeight = 59040.78879999999;
        }
        else if (yearType == 2){
            totWeight = 26758.943700000007;
        }
        else if (yearType == 3){
            totWeight = 31340.952200000007;
        }
        
        saveName = "TrimmedggZH_HToBB_ZToNuNu"+yearString;

        isBackground = true;
        datasetType = 78;
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisggZH_HToBB_ZToNuNu"+yearString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (ggZH_HToBB_ZToQQTrimmedBackground){

        crossSection = 0.04319;
        if (yearType == 0){
            totWeight = 212862.332;
        }
        else if (yearType == 1){
            totWeight = 215713.47199999998;
        }
        else if (yearType == 2){
            totWeight = 99347.31699999997;
        }
        else if (yearType == 3){
            totWeight = 116625.05099999998;
        }
        
        saveName = "TrimmedggZH_HToBB_ZToQQ"+yearString;

        isBackground = true;
        datasetType = 70;
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisggZH_HToBB_ZToQQ"+yearString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (EWKZ2Jets_ZToLLTrimmedBackground){

        crossSection = 6.214;
        if (yearType == 0){
            totWeight = 1000000.0;
        }
        else if (yearType == 1){
            totWeight = 579000.0;
        }
        else if (yearType == 2){
            totWeight = 453000.0;
        }
        else if (yearType == 3){
            totWeight = 500000.0;
        }
        
        saveName = "TrimmedEWKZ2Jets_ZToLL"+yearString;

        isBackground = true;
        datasetType = 71;
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisEWKZ2Jets_ZToLL"+yearString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (EWKZ2Jets_ZToNuNuTrimmedBackground){

        crossSection = 10.68;
        if (yearType == 0){
            totWeight = 2969000.0;
        }
        else if (yearType == 1){
            totWeight = 2976000.0;
        }
        else if (yearType == 2){
            totWeight = 1500000.0;
        }
        else if (yearType == 3){
            totWeight = 1450000.0;
        }
        
        saveName = "TrimmedEWKZ2Jets_ZToNuNu"+yearString;

        isBackground = true;
        datasetType = 72;
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisEWKZ2Jets_ZToNuNu"+yearString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (EWKZ2Jets_ZToQQTrimmedBackground){

        crossSection = 9.778;
        if (yearType == 0){
            totWeight = 9985000.0;
        }
        else if (yearType == 1){
            totWeight = 8000000.0;
        }
        else if (yearType == 2){
            totWeight = 4928082.0;
        }
        else if (yearType == 3){
            totWeight = 4979000.0;
        }
        
        saveName = "TrimmedEWKZ2Jets_ZToQQ"+yearString;

        isBackground = true;
        datasetType = 73;
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisEWKZ2Jets_ZToQQ"+yearString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (ZZZTrimmedBackground){

        crossSection = 0.01476;
        if (yearType == 0){
            totWeight = 146027.43779999999;
        }
        else if (yearType == 1){
            totWeight = 140629.42869999996;
        }
        else if (yearType == 2){
            totWeight = 66938.7465;
        }
        else if (yearType == 3){
            totWeight = 78317.072;
        }
        
        saveName = "TrimmedZZZ"+yearString;

        isBackground = true;
        datasetType = 74;
        
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisZZZ"+yearString+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (testRun){
        saveName = "testRun";
        fileAr.push_back("./HLTTrimmedFilteredForAnalysistestRun_0.root");
        useLHETree = true;
        useFJGenMatchTree = true;
        isBackground = false;
        totWeight = 1;
        
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
    
    std::string outFileStr = "new052023BDTAnalysis"+saveName+".root";
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

    Double_t startingWeightedCtr = 0.;
    

    Double_t passHiggsFJPreSTWeightedCtr = 0.;
    Double_t passHiggsFJPreSTWeightedLepCtr = 0.;
    Double_t passHiggsFJPreSTWeightedSemiLepCtr = 0.;
    Double_t passHiggsFJPreSTWeightedHadCtr = 0.;

    Double_t passHiggsFJWeightedCtr = 0.;
    Double_t passHiggsFJWeightedLepCtr = 0.;
    Double_t passHiggsFJWeightedSemiLepCtr = 0.;
    Double_t passHiggsFJWeightedHadCtr = 0.;
    Double_t passChannelWeightedCtr = 0.;
    Double_t passLepOrSemiLepChannelWeightedCtr = 0.;
    Double_t passLepChannelWeightedCtr = 0.;
    Double_t tryingSemiLepChannelWeightedCtr = 0.;
    Double_t passFJInSemiLepChannelWeightedCtr = 0.;
    Double_t passEnoughLepsInSemiLepChannelWeightedCtr = 0.;
    Double_t passEnoughFJsInSemiLepChannelWeightedCtr = 0.;
    Double_t passLepCutInSemiLepChannelWeightedCtr = 0.;
    Double_t passSemiLepChannelWeightedCtr = 0.;
    Double_t passHadChannelWeightedCtr = 0.;
    Double_t passVBFJetBVetoWeightedCtr = 0.;
    Double_t passVBFJetBVetoWeightedLepCtr = 0.;
    Double_t passVBFJetBVetoWeightedSemiLepCtr = 0.;
    Double_t passVBFJetBVetoWeightedHadCtr = 0.;
    Double_t passVBFJetsWeightedCtr = 0.;
    Double_t passAsLepWeightedCtr = 0.;
    Double_t passAsSemiLepWeightedCtr = 0.;
    Double_t passAsHadWeightedCtr = 0.;

    UInt_t passSemiLepLepCutCtr = 0;
    Double_t passSemiLepLepCutWeightedCtr = 0.;




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

    //PASSING EV TREE FOR BDT IN LEP CHANNEL
    Double_t passingEvGenWeight_L_L;

    Double_t passingEvFullWeight_L_L;

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
    Float_t selectedZOneLeadLepton_SIP3D_L_L;
    Float_t selectedZOneTrailingLepton_SIP3D_L_L;
    Float_t selectedLeptons_MaxRelIso_L_L;
    Float_t selectedZOneLeptons_InvMass_L_L;
    Bool_t selectedZOneLeptons_Type_L_L;

    Float_t selectedZTwoLeadLepton_pt_L_L;
    Float_t selectedZTwoTrailingLepton_pt_L_L;
    Float_t selectedZTwoLeadLepton_eta_L_L;
    Float_t selectedZTwoTrailingLepton_eta_L_L;
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
    
    passingEvLepTree->Branch("passingEvGenWeight_L_L",&passingEvGenWeight_L_L,"passingEvGenWeight_L_L/D");

    passingEvLepTree->Branch("passingEvFullWeight_L_L",&passingEvFullWeight_L_L,"passingEvFullWeight_L_L/D");

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
    passingEvLepTree->Branch("selectedZOneLeadLepton_SIP3D_L_L",&selectedZOneLeadLepton_SIP3D_L_L,"selectedZOneLeadLepton_SIP3D_L_L/F");
    passingEvLepTree->Branch("selectedZOneTrailingLepton_SIP3D_L_L",&selectedZOneTrailingLepton_SIP3D_L_L,"selectedZOneTrailingLepton_SIP3D_L_L/F");
    
    passingEvLepTree->Branch("selectedZOneLeptons_InvMass_L_L",&selectedZOneLeptons_InvMass_L_L,"selectedZOneLeptons_InvMass_L_L/F");
    passingEvLepTree->Branch("selectedZOneLeptons_Type_L_L",&selectedZOneLeptons_Type_L_L,"selectedZOneLeptons_Type_L_L/O");

    passingEvLepTree->Branch("selectedZTwoLeadLepton_pt_L_L",&selectedZTwoLeadLepton_pt_L_L,"selectedZTwoLeadLepton_pt_L_L/F");
    passingEvLepTree->Branch("selectedZTwoTrailingLepton_pt_L_L",&selectedZTwoTrailingLepton_pt_L_L,"selectedZTwoTrailingLepton_pt_L_L/F");
    passingEvLepTree->Branch("selectedZTwoLeadLepton_eta_L_L",&selectedZTwoLeadLepton_eta_L_L,"selectedZTwoLeadLepton_eta_L_L/F");
    passingEvLepTree->Branch("selectedZTwoTrailingLepton_eta_L_L",&selectedZTwoTrailingLepton_eta_L_L,"selectedZTwoTrailingLepton_eta_L_L/F");
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
    Double_t passingEvGenWeight_SL_L;

    Double_t passingEvFullWeight_SL_L;

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
    
    passingEvSemiLepTree->Branch("passingEvGenWeight_SL_L",&passingEvGenWeight_SL_L,"passingEvGenWeight_SL_L/D");

    passingEvSemiLepTree->Branch("passingEvFullWeight_SL_L",&passingEvFullWeight_SL_L,"passingEvFullWeight_SL_L/D");

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
    passingEvSemiLepTree->Branch("Jet_btagDeepFlavB_SL_L",&Jet_btagDeepFlavB_SL_L);
    

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

        //genWeights
        TTreeReaderValue<Double_t> genWeightL(myEventsReader, "genWeightL");
        //jets

        TTreeReaderValue<UInt_t> nJetL(myEventsReader, "nJetL");
        TTreeReaderArray<Float_t> Jet_etaL(myEventsReader, "Jet_etaL");
        TTreeReaderArray<Float_t> Jet_ptL(myEventsReader, "Jet_ptL");
        TTreeReaderArray<Float_t> Jet_phiL(myEventsReader, "Jet_phiL");
        TTreeReaderArray<Float_t> Jet_massL(myEventsReader, "Jet_massL");
        TTreeReaderArray<Int_t> Jet_jetIdL(myEventsReader, "Jet_jetIdL");

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
            //Increment event count
            evRunOver += 1;
            evCount += 1;

            
            elecCandIndAr.clear();
            muonCandIndAr.clear();

            eZ2VecPairAr.clear();
            mZ2VecPairAr.clear();
            Double_t tmpGenWeights = *genWeightL;
            startingCtr += 1;
            startingWeightedCtr += tmpGenWeights;

            


            bool passesCutsBool = false;
            bool passedAsLepBool = false;
            bool passedAsSemiLepBool = false;
            bool passedAsSemiLepLepCutBool = false;
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
            getNTightAndLooseMuons(Muon_looseIdL,Muon_mediumIdL,Muon_etaL,Muon_ptL,Muon_dxyL,Muon_dzL,Muon_sip3dL,Muon_miniPFRelIso_allL,Muon_jetIdxL,Jet_btagDeepFlavBL,Muon_mvaTTHL,nmLep,mPtTightCut,mPtLooseCut,mEtaCut,lDxyCut,lDzCut,lMiniPFRelIsoCut,lepJetDeepTagLooseCut,lepJetDeepTagMediumCut,mPromptMVACut,SIPCut,muonTightCount,muonLooseCount,debug);
            
            
            doLeptonicCutsWithTree(Electron_etaL,Electron_massL,Electron_chargeL,Electron_phiL,Electron_ptL, neLep, elecCandIndAr, elecCandVecAr, elecCandChargeAr,negElecCands,posElecCands,totElecCands,enoughElecCands,negMuonCands,posMuonCands,totMuonCands,enoughMuonCands,enoughLepCands,ePtCut,eEtaCut,
            Muon_etaL,Muon_massL, Muon_chargeL,Muon_phiL,Muon_ptL, nmLep, muonCandIndAr, muonCandVecAr, muonCandChargeAr,
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
                passChannelWeightedCtr += tmpGenWeights;
                
                passLepChannelCtr += 1;
                passLepChannelWeightedCtr += tmpGenWeights;
                
                passLepOrSemiLepChannelCtr += 1;
                passLepOrSemiLepChannelWeightedCtr += tmpGenWeights;
            }
            if ((!passesCutsBool)){
                dRCheckVecAr.clear();
                std::vector<Float_t> SemiLepInvMass;
                
                if (debug) std::cout << "trying SemiLeptonic\n";
                tryingSemiLepChannelCtr += 1;
                tryingSemiLepChannelWeightedCtr += tmpGenWeights;
                
                tryingSemiLepCtr += 1;

                //Checking that there are enough FJs for both the Z and the H
                UInt_t numFatJet = *nFatJetL;

                UInt_t nPassingJetIdFJs = 0;
                for (UInt_t fatJetInd=0;fatJetInd<numFatJet;fatJetInd++){
                    if (FatJet_jetIdL[fatJetInd] == 6) nPassingJetIdFJs += 1;

                }

                if (nPassingJetIdFJs >=2){
                    passEnoughFJsInSemiLepChannelCtr += 1;
                    passEnoughFJsInSemiLepChannelWeightedCtr += tmpGenWeights;
                    
                    enoughLepCands = false;
                    doSemiLepCutWithTreeWithBDTVars(enoughElecCands,negElecCands,posElecCands,totElecCands,Electron_etaL,Electron_massL,Electron_chargeL,Electron_phiL,Electron_ptL,neLep,elecCandIndAr,elecCandVecAr,elecCandChargeAr,ePtCut,eEtaCut,
                    enoughMuonCands,negMuonCands,posMuonCands,totMuonCands,Muon_etaL,Muon_massL,Muon_chargeL,Muon_phiL,Muon_ptL,nmLep,muonCandIndAr,muonCandVecAr,muonCandChargeAr,mPtCut,mEtaCut,
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
                        passEnoughLepsInSemiLepChannelWeightedCtr += tmpGenWeights;
                        
                        
                    }

                    if (passedAsSemiLepLepCutBool){
                        if (debug) std::cout << "Passed semi lep lep cut\n";
                        passSemiLepLepCutCtr += 1;
                        passSemiLepLepCutWeightedCtr += tmpGenWeights;
                        
                        
                    }


                    
                    Int_t FJInd;

                    FJInd = -1;
                    UInt_t numFatJet = *nFatJetL;
                    if (debug){
                        std::cout << "Pre FJC dRCheckVecAr.size() " << dRCheckVecAr.size() << "\n";
                    }
                    doSemiLepChanFatJetCut(FJInd,numFatJet,fatJetPTCut,fatJetZParticleNetCut,FatJet_ptL,FatJet_phiL,FatJet_etaL,FatJet_massL,FatJet_particleNet_ZvsQCDL,FatJet_jetIdL,dRCheckVecAr,dRCut,passSemiLepCut,passesCutsBool,passedAsSemiLepBool);
                    if (debug){
                        std::cout << "Post FJC dRCheckVecAr.size() " << dRCheckVecAr.size() << " FJInd "<< FJInd <<"\n";
                    }
                    if (FJInd >= 0){
                        passFJInSemiLepChannelCtr += 1;
                        passFJInSemiLepChannelWeightedCtr += tmpGenWeights;
                        
                    FJIndAr.push_back(FJInd);
                    
                    }

                }
                
                if (passesCutsBool){
                    passChannelCtr += 1;
                    passChannelWeightedCtr += tmpGenWeights;
                    


                    passSemiLepChannelCtr += 1;
                    passSemiLepChannelWeightedCtr += tmpGenWeights;
                    

                    passLepOrSemiLepChannelCtr += 1;
                    passLepOrSemiLepChannelWeightedCtr += tmpGenWeights;
                    
                }
            }
            if (debug) std::cout << "Test\n";
            if ((!passesCutsBool)){
                dRCheckVecAr.clear();
                tryingHadCtr += 1;
                LFJOneInd = -1;
                LFJTwoInd = -1;
                if (debug) std::cout << "---------------- Event " << evCount - 1 << " ----------------\n";
                //if (debug) std::cout << "hFatJet_ind_fromHTag " << hFatJet_ind_fromHTag << "\n";
                if (debug) std::cout << "fatJetPTCut " << fatJetPTCut << "\n";

                if (debug) std::cout << "--------- Entering FJ loop for Hadronic Channel ---------\n";

                UInt_t numFatJet = *nFatJetL;
                doHadChanFatJetCut(LFJOneInd,LFJTwoInd,numFatJet,fatJetPTCut,fatJetZPairInvMassCut,FatJet_ptL,FatJet_phiL,FatJet_etaL,FatJet_massL,FatJet_particleNet_ZvsQCDL);

                
                if (LFJOneInd != LFJTwoInd){
                    passHadCut += 1;
                    passesCutsBool = true;
                    passedAsHadBool = true;
                    FJIndAr.push_back(LFJOneInd);
                    FJIndAr.push_back(LFJTwoInd);
                    dRCheckVecAr.push_back(ROOT::Math::PtEtaPhiMVector(FatJet_ptL[LFJOneInd],FatJet_etaL[LFJOneInd],FatJet_phiL[LFJOneInd],FatJet_massL[LFJOneInd]));
                    dRCheckVecAr.push_back(ROOT::Math::PtEtaPhiMVector(FatJet_ptL[LFJTwoInd],FatJet_etaL[LFJTwoInd],FatJet_phiL[LFJTwoInd],FatJet_massL[LFJTwoInd]));
                }
                if (passesCutsBool){
                    passChannelCtr += 1;
                    passChannelWeightedCtr += tmpGenWeights;
                    
                    passHadChannelCtr += 1;
                    passHadChannelWeightedCtr += tmpGenWeights;
                    
                }
            }
            if ((!passesCutsBool)) continue;
            

            //Now fat jets
            UInt_t nFatJetLen = *nFatJetL;
            
            float hFatJet_pt_fromHTag = 0.;
            float hFatJet_phi_fromHTag = 0.;
            float hFatJet_eta_fromHTag = 0.;
            float hFatJet_mass_fromHTag = 0.;
            float hFatJet_HTag_fromHTag = 0.;
            UInt_t hFatJet_ind_fromHTag = 0;
            if (debug){
                std::cout << "Entering Fat Jets Loop\n";
            }


            //doHiggsFatJetCut(nFatJetLen,hFatJet_HTag_fromPt,hFatJet_pt_fromPt,hFatJet_phi_fromPt,hFatJet_eta_fromPt,hFatJet_mass_fromPt,hFatJet_pt_fromHTag,hFatJet_phi_fromHTag,hFatJet_eta_fromHTag,hFatJet_mass_fromHTag,hFatJet_HTag_fromHTag,hFatJet_ind_fromHTag,FatJet_deepTag_HL,hFatJetDeepTagCut,FatJet_ptL,hFatJetPTCut,FatJet_jetIdL,FatJet_phiL,FatJet_etaL,jetLeadPhi,jetLeadEta,jetTrailingPhi,jetTrailingEta,hFatJetdRCut,FatJet_massL);
            //Replacing hFatJetDeepTagCut
            //doHiggsFatJetCut(nFatJetLen,hFatJet_pt_fromHTag,hFatJet_phi_fromHTag,hFatJet_eta_fromHTag,hFatJet_mass_fromHTag,hFatJet_HTag_fromHTag,hFatJet_ind_fromHTag,FatJet_particleNet_HbbvsQCDL,hFatJetParticleNetCut,FatJet_ptL,hFatJetPTCut,FatJet_jetIdL,FatJet_phiL,FatJet_etaL,FatJet_massL,dRCheckVecAr,dRCut,FJIndAr,ZPairPlusHInvMassCut,ZPairPlusHPtCut);
            doHiggsFatJetCutEarlySelection(nFatJetLen,hFatJet_pt_fromHTag,hFatJet_phi_fromHTag,hFatJet_eta_fromHTag,hFatJet_mass_fromHTag,hFatJet_HTag_fromHTag,hFatJet_ind_fromHTag,FatJet_particleNet_HbbvsQCDL,hFatJetParticleNetCut,FatJet_ptL,hFatJetPTCut,FatJet_jetIdL,FatJet_phiL,FatJet_etaL,FatJet_massL,dRCheckVecAr,dRCut,FJIndAr);
            
            if (hFatJet_pt_fromHTag == 0) continue;
            if (debug) std::cout << " found Higgs fat jet\n";
            passHiggsFJPreSTCtr += 1;
            passHiggsFJPreSTWeightedCtr += tmpGenWeights;

            

            if (passedAsLepBool) {
                passHiggsFJPreSTLepCtr += 1;
                passHiggsFJPreSTWeightedLepCtr += tmpGenWeights;
                
            }
            else if (passedAsSemiLepBool) {
                passHiggsFJPreSTSemiLepCtr += 1;
                passHiggsFJPreSTWeightedSemiLepCtr += tmpGenWeights;
                
            }
            else if (passedAsHadBool) {
                passHiggsFJPreSTHadCtr += 1;
                passHiggsFJPreSTWeightedHadCtr += tmpGenWeights;
                
            }








            bool passesSTCutBool = false;
            doHiggsFatJetCutSTWithBDTVars(dRCheckVecAr,ZPairPlusHInvMassCut,ZPairPlusHPtCut,ZPairPlusHInvMass,ZPairPlusHPt,passesSTCutBool);
            if (!passesSTCutBool) continue;
            if (debug) std::cout << " found Higgs fat jet\n";
            passHiggsFJCtr += 1;
            passHiggsFJWeightedCtr += tmpGenWeights;
            

            if (passedAsLepBool) {
                passHiggsFJLepCtr += 1;
                passHiggsFJWeightedLepCtr += tmpGenWeights;
                
            }
            else if (passedAsSemiLepBool) {
                passHiggsFJSemiLepCtr += 1;
                passHiggsFJWeightedSemiLepCtr += tmpGenWeights;
                
            }
            else if (passedAsHadBool) {
                passHiggsFJHadCtr += 1;
                passHiggsFJWeightedHadCtr += tmpGenWeights;
                
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
            doBJetVeto_WithBDTVariables(nJetLen,Jet_ptL,Jet_etaL,Jet_phiL,Jet_btagDeepFlavBL,hFatJet_phi_fromHTag,hFatJet_eta_fromHTag,dRCut,bTagCut,passBJetVeto,maxPassingBTag,debug);
            if (!passBJetVeto) continue;

            passVBFJetBVetoCtr += 1;
            passVBFJetBVetoWeightedCtr += tmpGenWeights;

            if (passedAsLepBool) {
                passVBFJetBVetoLepCtr += 1;
                passVBFJetBVetoWeightedLepCtr += tmpGenWeights;
                
            }
            else if (passedAsSemiLepBool) {
                passVBFJetBVetoSemiLepCtr += 1;
                passVBFJetBVetoWeightedSemiLepCtr += tmpGenWeights;
                
            }
            else if (passedAsHadBool) {
                passVBFJetBVetoHadCtr += 1;
                passVBFJetBVetoWeightedHadCtr += tmpGenWeights;
                
            }

            


            if (debug) std::cout << "Entering jet loop. Len: " << nJetLen << "\n";
            doVBFJetCutPtSelectionWithBDTVars(nJetLen,Jet_ptL,Jet_jetIdL,Jet_etaL,Jet_phiL,Jet_massL,jetPTCut,jetEtaDifCut,jetInvMassCut,jetPairInvMass,jetLeadPt,jetLeadEta,jetLeadPhi,jetLeadMass,jetTrailingPt,jetTrailingEta,jetTrailingPhi,jetTrailingMass,leadJet_1,leadJet_2,dRCheckVecAr,dRCut,debug);
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
                passVBFJetsWeightedCtr += tmpGenWeights;

                //get number of passing VBFJets

                UInt_t tmpnAK4JetsPassing = 0;

                for (UInt_t nJetItr=0; nJetItr<nJetLen;nJetItr++){
                    UInt_t tmpJetPt = Jet_ptL[nJetItr];
                    //Jet_etaL[nJetItr]
                    Int_t tmpJetId = Jet_jetIdL[nJetItr];
                    if (tmpJetPt < 30 || !(tmpJetId == 6)) continue;
                    tmpnAK4JetsPassing += 1;

                
                }
                

                //std::cout << passedAsLepBool << " "<< passedAsSemiLepBool << " " << passedAsHadBool << "\n";
                if (passedAsLepBool) {

                    passAsLepCtr += 1;
                    passAsLepWeightedCtr += tmpGenWeights;

                    //Fill BDT Lep Tree
                    passingEvGenWeight_L_L = tmpGenWeights;

                    passingEvFullWeight_L_L = tmpGenWeights*crossSection*Run2Lumi/totWeight;

                    datasetType_L_L = datasetType;
                    yearType_L_L = yearType;

                    eventNAK4Jets_L_L = nJetLen;
                    eventNAK8Jets_L_L = nFatJetLen;
                    eventNMuons_L_L = nmLep;
                    eventNElectrons_L_L = neLep;


                    for (UInt_t nJetItr=0; nJetItr<nJetLen;nJetItr++){
                        Jet_eta_L_L.push_back(Jet_etaL[nJetItr]);
                        Jet_pt_L_L.push_back(Jet_ptL[nJetItr]);
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
                    selectedHiggsFJ_ParticleNet_HbbvsQCD_L_L = hFatJet_HTag_fromHTag;

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
                    selectedZOneLeadLepton_SIP3D_L_L = Z1LeadSIP;
                    selectedZOneTrailingLepton_SIP3D_L_L = Z1TrailingSIP;

                    selectedZOneLeptons_InvMass_L_L = selectedZOneLeptons_InvMass; 
                    selectedZOneLeptons_Type_L_L = Z1IsMuon;

                    selectedZTwoLeadLepton_pt_L_L = tmpTopZ2LeadPt;
                    selectedZTwoTrailingLepton_pt_L_L = tmpTopZ2TrailingPt;
                    selectedZTwoLeadLepton_eta_L_L = dRCheckVecAr[2].Eta();
                    selectedZTwoTrailingLepton_eta_L_L = dRCheckVecAr[3].Eta();
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
                    //std::cout << "PASSED ON " << evCount << "\n";


                    passAsSemiLepCtr += 1;
                    passAsSemiLepWeightedCtr += tmpGenWeights;

                    //Fill BDT SemiLep Tree

                    passingEvGenWeight_SL_L = tmpGenWeights;

                    passingEvFullWeight_SL_L = tmpGenWeights*crossSection*Run2Lumi/totWeight;

                    yearType_SL_L = yearType;
                    datasetType_SL_L = datasetType;

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
                    }

                    eventNAK4JetsPassingCuts_SL_L = tmpnAK4JetsPassing;

                    eventNLooseElectrons_SL_L = elecLooseCount;
                    eventNTightElectrons_SL_L = elecTightCount;

                    eventNLooseMuons_SL_L = muonLooseCount;
                    eventNTightMuons_SL_L = muonTightCount;

                    selectedHiggsFJ_pt_SL_L = hFatJet_pt_fromHTag;
                    selectedZFJ_pt_SL_L = dRCheckVecAr[2].Pt();
                    selectedHiggsFJ_eta_SL_L = hFatJet_eta_fromHTag;
                    selectedZFJ_eta_SL_L = dRCheckVecAr[2].Eta();
                    selectedZFJ_InvMass_SL_L = dRCheckVecAr[2].M();
                    selectedHiggsFJ_InvMass_SL_L = dRCheckVecAr[3].M();
                    selectedHiggsFJ_ParticleNet_HbbvsQCD_SL_L = hFatJet_HTag_fromHTag;

                    selectedZFJ_InvMassSoftDrop_SL_L = FatJet_msoftdropL[FJIndAr[0]];
                    selectedHiggsFJ_InvMassSoftDrop_SL_L = FatJet_msoftdropL[FJIndAr[1]];

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
                    

                }
                else if (passedAsHadBool) {

                    passAsHadCtr += 1;
                    passAsHadWeightedCtr += tmpGenWeights;
                    
                }

            }

        }
    }
    if (debug) std::cout << "Filling complete \n";

    clock_t endt = clock();
    double time_spent = (double)(endt - startt) / CLOCKS_PER_SEC;


    std::cout << "Finished file loop. " << "time: " << time_spent << "\n";
    
    std::cout << "XS: " << crossSection << "\n";
    std::cout << "nEv total: " << datanEv << "\n";
    std::cout << "nEv post pre-selection: " << datanEvPass << "\n"; 
    

    std::cout << "==============================TOTAL COUNTERS==============================\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "startingCtr = " << startingCtr << "\n";
    std::cout << "Double_t " << saveName << "startingWeightedCtr = " << startingWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "tryingSemiLepChannelCtr = " << tryingSemiLepChannelCtr << "\n";
    std::cout << "Double_t " << saveName << "tryingSemiLepChannelWeightedCtr = " << tryingSemiLepChannelWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "passEnoughFJsInSemiLepChannelCtr = " << passEnoughFJsInSemiLepChannelCtr << "\n";
    std::cout << "Double_t " << saveName << "passEnoughFJsInSemiLepChannelWeightedCtr = " << passEnoughFJsInSemiLepChannelWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "passEnoughLepsInSemiLepChannelCtr = " << passEnoughLepsInSemiLepChannelCtr << "\n";
    std::cout << "Double_t " << saveName << "passEnoughLepsInSemiLepChannelWeightedCtr = " << passEnoughLepsInSemiLepChannelWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "passSemiLepLepCutCtr = " << passSemiLepLepCutCtr << "\n";
    std::cout << "Double_t " << saveName << "passSemiLepLepCutWeightedCtr = " << passSemiLepLepCutWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "passFJInSemiLepChannelCtr = " << passFJInSemiLepChannelCtr << "\n";
    std::cout << "Double_t " << saveName << "passFJInSemiLepChannelWeightedCtr = " << passFJInSemiLepChannelWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassChannelCtr = " << passChannelCtr << "\n";
    std::cout << "Double_t " << saveName << "PassChannelWeightedCtr = " << passChannelWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassLepOrSemiLepChannelCtr = " << passLepOrSemiLepChannelCtr << "\n";
    std::cout << "Double_t " << saveName << "PassLepOrSemiLepChannelWeightedCtr = " << passLepOrSemiLepChannelWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassLepChannelCtr = " << passLepChannelCtr << "\n";
    std::cout << "Double_t " << saveName << "PassLepChannelWeightedCtr = " << passLepChannelWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassSemiLepChannelCtr = " << passSemiLepChannelCtr << "\n";
    std::cout << "Double_t " << saveName << "PassSemiLepChannelWeightedCtr = " << passSemiLepChannelWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHadChannelCtr = " << passHadChannelCtr << "\n";
    std::cout << "Double_t " << saveName << "PassHadChannelWeightedCtr = " << passHadChannelWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJPreSTCtr = " << passHiggsFJPreSTCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJPreSTWeightedCtr = " << passHiggsFJPreSTWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJPreSTLepCtr = " << passHiggsFJPreSTLepCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJPreSTWeightedLepCtr = " << passHiggsFJPreSTWeightedLepCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJPreSTSemiLepCtr = " << passHiggsFJPreSTSemiLepCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJPreSTWeightedSemiLepCtr = " << passHiggsFJPreSTWeightedSemiLepCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJPreSTHadCtr = " << passHiggsFJPreSTHadCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJPreSTWeightedHadCtr = " << passHiggsFJPreSTWeightedHadCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJCtr = " << passHiggsFJCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJWeightedCtr = " << passHiggsFJWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJLepCtr = " << passHiggsFJLepCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJWeightedLepCtr = " << passHiggsFJWeightedLepCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJSemiLepCtr = " << passHiggsFJSemiLepCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJWeightedSemiLepCtr = " << passHiggsFJWeightedSemiLepCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJHadCtr = " << passHiggsFJHadCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJWeightedHadCtr = " << passHiggsFJWeightedHadCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassVBFJetBVetoCtr = " << passVBFJetBVetoCtr << "\n";
    std::cout << "Double_t " << saveName << "passVBFJetBVetoWeightedCtr = " << passVBFJetBVetoWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassVBFJetBVetoLepCtr = " << passVBFJetBVetoLepCtr << "\n";
    std::cout << "Double_t " << saveName << "passVBFJetBVetoWeightedLepCtr = " << passVBFJetBVetoWeightedLepCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassVBFJetBVetoSemiLepCtr = " << passVBFJetBVetoSemiLepCtr << "\n";
    std::cout << "Double_t " << saveName << "passVBFJetBVetoWeightedSemiLepCtr = " << passVBFJetBVetoWeightedSemiLepCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassVBFJetBVetoHadCtr = " << passVBFJetBVetoHadCtr << "\n";
    std::cout << "Double_t " << saveName << "passVBFJetBVetoWeightedHadCtr = " << passVBFJetBVetoWeightedHadCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassVBFJetsCtr = " << passVBFJetsCtr << "\n";
    std::cout << "Double_t " << saveName << "PassVBFJetsWeightedCtr = " << passVBFJetsWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassAsLepCtr = " << passAsLepCtr << "\n";
    std::cout << "Double_t " << saveName << "PassAsLepWeightedCtr = " << passAsLepWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassAsSemiLepCtr = " << passAsSemiLepCtr << "\n";
    std::cout << "Double_t " << saveName << "PassAsSemiLepWeightedCtr = " << passAsSemiLepWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassAsHadCtr = " << passAsHadCtr << "\n";
    std::cout << "Double_t " << saveName << "PassAsHadWeightedCtr = " << passAsHadWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "\n";



    outFile->cd();
    passingEvLepTree->Write("",TObject::kOverwrite);
    passingEvSemiLepTree->Write("",TObject::kOverwrite);

    outFile->Close();

}