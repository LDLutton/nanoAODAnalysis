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

//This version has the higgs being selected before the Z
void new042024BDTBackgroundAnalysis(string datasetString, int JECCorInd, bool JECCorUpOrDown,  int RochInd, int JERInd){
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

    if (datasetString == "testRun") testRun = true;
    if (datasetString == "ttHToBB") ttHToBBTrimmedBackground = true;
    if (datasetString == "ttZJets") ttZJetsTrimmedBackground = true;
    if (datasetString == "ttWJets") ttWJetsTrimmedBackground = true;
    if (datasetString == "DY") DYTrimmedBackground = true;
    if (datasetString == "TTJets") TTJetsTrimmedBackground = true;
    if (datasetString == "ST_s_Channel") ST_s_ChannelTrimmedBackground = true;
    if (datasetString == "ST_t_ChannelAntiTop") ST_t_ChannelAntiTopTrimmedBackground = true;
    if (datasetString == "ST_t_ChannelTop") ST_t_ChannelTopTrimmedBackground = true;
    if (datasetString == "ZZ") ZZTrimmedBackground = true;
    if (datasetString == "WW") WWTrimmedBackground = true;
    if (datasetString == "WZ") WZTrimmedBackground = true;
    if (datasetString == "TTbb_TTToHadronic") TTbb_TTToHadronicTrimmedBackground = true;
    if (datasetString == "TTbb_TTTo2L2Nu") TTbb_TTTo2L2NuTrimmedBackground = true;
    if (datasetString == "TTbb_TTToSemiLeptonic") TTbb_TTToSemiLeptonicTrimmedBackground = true;

    if (datasetString == "TTToHadronic") TTToHadronicTrimmedBackground = true;
    if (datasetString == "TTTo2L2Nu") TTTo2L2NuTrimmedBackground = true;
    if (datasetString == "TTToSemiLeptonic") TTToSemiLeptonicTrimmedBackground = true;

    if (datasetString == "QCDPT170to300") QCDPT170to300TrimmedBackground = true;
    if (datasetString == "QCDPT300to470") QCDPT300to470TrimmedBackground = true;
    if (datasetString == "QCDPT470to600") QCDPT470to600TrimmedBackground = true;
    if (datasetString == "QCDPT600to800") QCDPT600to800TrimmedBackground = true;
    if (datasetString == "QCDPT800to1000") QCDPT800to1000TrimmedBackground = true;
    if (datasetString == "QCDPT1000to1400") QCDPT1000to1400TrimmedBackground = true;
    if (datasetString == "QCDPT1400to1800") QCDPT1400to1800TrimmedBackground = true;
    if (datasetString == "QCDPT1800to2400") QCDPT1800to2400TrimmedBackground = true;
    if (datasetString == "QCDPT2400to3200") QCDPT2400to3200TrimmedBackground = true;
    if (datasetString == "QCDPT3200toInf") QCDPT3200toInfTrimmedBackground = true;

    if (datasetString == "QCDHT50to100") QCDHT50to100TrimmedBackground = true;
    if (datasetString == "QCDHT100to200") QCDHT100to200TrimmedBackground = true;
    if (datasetString == "QCDHT200to300") QCDHT200to300TrimmedBackground = true;
    if (datasetString == "QCDHT300to500") QCDHT300to500TrimmedBackground = true;
    if (datasetString == "QCDHT500to700") QCDHT500to700TrimmedBackground = true;
    if (datasetString == "QCDHT700to1000") QCDHT700to1000TrimmedBackground = true;
    if (datasetString == "QCDHT1000to1500") QCDHT1000to1500TrimmedBackground = true;
    if (datasetString == "QCDHT1500to2000") QCDHT1500to2000TrimmedBackground = true;
    if (datasetString == "QCDHT2000toInf") QCDHT2000toInfTrimmedBackground = true;


    if (datasetString == "DYM10To50") DYM10To50TrimmedBackground = true;
    if (datasetString == "ST_tW_antitop") ST_tW_antitopTrimmedBackground = true;
    if (datasetString == "ST_tW_top") ST_tW_topTrimmedBackground = true;
    if (datasetString == "EWKWMinus2Jets_WToLNu") EWKWMinus2Jets_WToLNuTrimmedBackground = true;
    if (datasetString == "EWKWMinus2Jets_WToQQ") EWKWMinus2Jets_WToQQTrimmedBackground = true;
    if (datasetString == "EWKWPlus2Jets_WToLNu") EWKWPlus2Jets_WToLNuTrimmedBackground = true;
    if (datasetString == "EWKWPlus2Jets_WToQQ") EWKWPlus2Jets_WToQQTrimmedBackground = true;
    if (datasetString == "VHToNonbb") VHToNonbbTrimmedBackground = true;
    if (datasetString == "WminusH_HToBB_WToLNu") WminusH_HToBB_WToLNuTrimmedBackground = true;
    if (datasetString == "WminusH_HToBB_WToQQ") WminusH_HToBB_WToQQTrimmedBackground = true;
    if (datasetString == "WplusH_HToBB_WToLNu") WplusH_HToBB_WToLNuTrimmedBackground = true;
    if (datasetString == "WplusH_HToBB_WToQQ") WplusH_HToBB_WToQQTrimmedBackground = true;
    if (datasetString == "WJetsToLNu") WJetsToLNuTrimmedBackground = true;
    if (datasetString == "WWW") WWWTrimmedBackground = true;
    if (datasetString == "WWZ") WWZTrimmedBackground = true;
    if (datasetString == "WZZ") WZZTrimmedBackground = true;
    if (datasetString == "ZH_HToBB_ZToBB") ZH_HToBB_ZToBBTrimmedBackground = true;
    if (datasetString == "ZH_HToBB_ZToNuNu") ZH_HToBB_ZToNuNuTrimmedBackground = true;
    if (datasetString == "ZH_HToBB_ZToLL") ZH_HToBB_ZToLLTrimmedBackground = true;
    if (datasetString == "ZH_HToBB_ZToQQ") ZH_HToBB_ZToQQTrimmedBackground = true;
    if (datasetString == "ggZH_HToBB_ZToBB") ggZH_HToBB_ZToBBTrimmedBackground = true;
    if (datasetString == "ggZH_HToBB_ZToNuNu") ggZH_HToBB_ZToNuNuTrimmedBackground = true;
    if (datasetString == "ggZH_HToBB_ZToLL") ggZH_HToBB_ZToLLTrimmedBackground = true;
    if (datasetString == "ggZH_HToBB_ZToQQ") ggZH_HToBB_ZToQQTrimmedBackground = true;
    if (datasetString == "EWKZ2Jets_ZToLL") EWKZ2Jets_ZToLLTrimmedBackground = true;
    if (datasetString == "EWKZ2Jets_ZToNuNu") EWKZ2Jets_ZToNuNuTrimmedBackground = true;
    if (datasetString == "EWKZ2Jets_ZToQQ") EWKZ2Jets_ZToQQTrimmedBackground = true;
    if (datasetString == "ZZZ") ZZZTrimmedBackground = true;

    if (datasetString == "LaraTest") LaraTest = true;

    ////////////////////////////////GETTING DATASET////////////////////////////////
    ////////////////////////////////GETTING DATASET////////////////////////////////
    ////////////////////////////////GETTING DATASET////////////////////////////////
    ////////////////////////////////GETTING DATASET////////////////////////////////


    float totWeight = 1;
    //precalculate this
    double XS = 1;

    UInt_t datasetType = 0;
    UInt_t yearType = 0;

    
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
    else if (QCDHT50to100TrimmedBackground){
        //saveName = "QCDHT50to100";
        
        crossSection = 187700000.; //XS for QCDHT aren't valid yet since they're only for one year but not used here anyway

        saveName = "QCDHT50to100";
        datasetType = 79;
        
        
        
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearString+".root");
        //QCDHT50to100BackgroundAr[fileInd]);
    }
    else if (QCDHT100to200TrimmedBackground){
        //saveName = "QCDHT100to200";
        
        crossSection = 23640000.0;

        saveName = "QCDHT100to200";

        datasetType = 80;
        
        
        
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearString+".root");
        //QCDHT100to200BackgroundAr[fileInd]);
    }
    else if (QCDHT200to300TrimmedBackground){
        //saveName = "QCDHT200to300";
        
        crossSection = 1546000.0;

        saveName = "QCDHT200to300";

        datasetType = 81;
        
        
        
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearString+".root");
        //QCDHT200to300BackgroundAr[fileInd]);
    }
    else if (QCDHT300to500TrimmedBackground){
        //saveName = "QCDHT300to500";
        
        crossSection = 321600.0;

        saveName = "QCDHT300to500";

        datasetType = 82;
        
        
        
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearString+".root");
        //QCDHT300to500BackgroundAr[fileInd]);
    }
    else if (QCDHT500to700TrimmedBackground){
        //saveName = "QCDHT500to700";
        
        crossSection = 30980.0;

        saveName = "QCDHT500to700";

        datasetType = 83;
        
        
        
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearString+".root");
        //QCDHT500to700BackgroundAr[fileInd]);
    }
    else if (QCDHT700to1000TrimmedBackground){
        //saveName = "QCDHT700to1000";
        
        crossSection = 6364.0;

        saveName = "QCDHT700to1000";

        datasetType = 84;
        
        
        
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearString+".root");
        //QCDHT700to1000BackgroundAr[fileInd]);
    }
    else if (QCDHT1000to1500TrimmedBackground){
        //saveName = "QCDHT1000to1500";
        
        crossSection = 1117.0;

        saveName = "QCDHT1000to1500";

        datasetType = 85;
        
        
        
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearString+".root");
        //QCDHT1000to1500BackgroundAr[fileInd]);
    }
    else if (QCDHT1500to2000TrimmedBackground){
        //saveName = "QCDHT1500to2000";
        
        crossSection = 108.4;

        saveName = "QCDHT1500to2000";

        datasetType = 86;
        
        
        
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearString+".root");
        //QCDHT1500to2000BackgroundAr[fileInd]);
    }
    else if (QCDHT2000toInfTrimmedBackground){
        //saveName = "QCDHT2000toInf";
        
        crossSection = 22.36;

        saveName = "QCDHT2000toInf";

        datasetType = 87;
        
        
        
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearString+".root");
        
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
    else if (TTToHadronicTrimmedBackground){
        
        
        crossSection = 377.96; //XS for these three TT aren't valid but also aren't used here so ignore

        saveName = "TTJetsHadronic";

        datasetType = 88;
        
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearString+".root");
        
    }
    else if (TTToSemiLeptonicTrimmedBackground){
        //saveName = "";
        
        crossSection = 365.346;

        saveName = "TTJetsSemiLeptonic";

        datasetType = 89;
        
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearString+".root");
        
    }
    else if (TTTo2L2NuTrimmedBackground){
        
        crossSection = 88.29;

        saveName = "TTJets2L2Nu";

        datasetType = 90;
        
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearString+".root");
        
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


    
    
    UInt_t passSemiLepLepCutCtr = 0;
    

    Double_t startingWeightedCtr = 0;

    Double_t passHiggsFJWeightedCtr = 0;
    Double_t passHiggsFJSemiLepWeightedCtr = 0;
    Double_t passChannelWeightedCtr = 0;
    Double_t passLepOrSemiLepChannelWeightedCtr = 0;
    Double_t tryingSemiLepChannelWeightedCtr = 0;
    Double_t passHiggsFJInSemiLepChannelWeightedCtr = 0;
    Double_t passFJInSemiLepChannelWeightedCtr = 0;
    Double_t passEnoughFJsInSemiLepChannelWeightedCtr = 0;
    Double_t passLepCutInSemiLepChannelWeightedCtr = 0;
    Double_t passSemiLepChannelWeightedCtr = 0;
    Double_t passVBFJetBVetoWeightedCtr = 0;
    Double_t passVBFJetBVetoSemiLepWeightedCtr = 0;
    Double_t passVBFJetsWeightedCtr = 0;
    Double_t passLepVetoWeightedCtr = 0;
    Double_t passAsSemiLepWeightedCtr = 0;


    
    
    Double_t passSemiLepLepCutWeightedCtr = 0;

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

    UInt_t datanEv = 0;
    UInt_t datanEvPass = 0;
    UInt_t evCount = 0;
    UInt_t evRunOver = 0;

    UInt_t passVBFJetsWeighted = 0;
    UInt_t passFatJetsWeighted = 0;
    UInt_t passFJMatchWeighted = 0;
    UInt_t passLepCutWeighted = 0;
    UInt_t passSemiLepCutWeighted = 0;

    UInt_t passHadCutWeighted = 0;

    UInt_t tryingLepWeightedCtr = 0;
    UInt_t tryingSemiLepWeightedCtr = 0;
    UInt_t tryingHadWeightedCtr = 0;

    UInt_t datanEvWeighted = 0;
    UInt_t datanEvPassWeighted = 0;
    UInt_t evCountWeighted = 0;
    UInt_t evRunOverWeighted = 0;

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

    Int_t FatJet_hadronFlavour_SL_L;

    Bool_t firstHToBBBool_SL_L; //including as alternative to eventGenHToBB. Checking if there's a difference.

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
    Float_t selectedHiggsFJ_InvMassPNRegress_JMSNomJMRNom_SL_L;

    TTree *passingEvSemiLepTree = new TTree("passingEvSemiLepTree", "passingEvSemiLepTree");

    //EventCor/UncInds
    passingEvSemiLepTree->Branch("JECCorInd_SL_L",&JECCorInd_SL_L,"JECCorInd_SL_L/i");
    passingEvSemiLepTree->Branch("JECCorUpOrDown_SL_L",&JECCorUpOrDown_SL_L,"JECCorUpOrDown_SL_L/i");
    passingEvSemiLepTree->Branch("RochInd_SL_L",&RochInd_SL_L,"RochInd_SL_L/i");
    passingEvSemiLepTree->Branch("JERInd_SL_L",&JERInd_SL_L,"JERInd_SL_L/i");

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


    passingEvSemiLepTree->Branch("FatJet_hadronFlavour_SL_L",&FatJet_hadronFlavour_SL_L,"FatJet_hadronFlavour_SL_L/I");

    passingEvSemiLepTree->Branch("firstHToBBBool_SL_L",&firstHToBBBool_SL_L,"firstHToBBBool_SL_L/O");

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
    passingEvSemiLepTree->Branch("selectedZFJ_InvMassSoftDrop_JMSNomJMRNom_SL_L",&selectedZFJ_InvMassSoftDrop_JMSNomJMRNom_SL_L,"selectedZFJ_InvMassSoftDrop_JMSNomJMRNom_SL_L/F");
    passingEvSemiLepTree->Branch("selectedHiggsFJ_InvMassSoftDrop_JMSNomJMRNom_SL_L",&selectedHiggsFJ_InvMassSoftDrop_JMSNomJMRNom_SL_L,"selectedHiggsFJ_InvMassSoftDrop_JMSNomJMRNom_SL_L/F");


    //Whole Run Tree
    UInt_t nLHEPdfSumwL;
    std::vector<Double_t> LHEPdfSumwL;
    UInt_t nLHEScaleSumwL;
    std::vector<Double_t> LHEScaleSumwL;
    Long64_t genEventCountL;
    Double_t genEventSumwL;
    Double_t genEventSumw2L;
    UInt_t runL;
    

    TTree *runTree = new TTree("runTree", "runTree");

    runTree->Branch("nLHEPdfSumwL",&nLHEPdfSumwL,"nLHEPdfSumwL/i");
    runTree->Branch("LHEPdfSumwL",&LHEPdfSumwL);
    runTree->Branch("nLHEScaleSumwL",&nLHEScaleSumwL,"nLHEScaleSumwL/i");
    runTree->Branch("LHEScaleSumwL",&LHEScaleSumwL);
    runTree->Branch("genEventCountL",&genEventCountL,"genEventCountL/L");
    runTree->Branch("genEventSumwL",&genEventSumwL,"genEventSumwL/D");
    runTree->Branch("genEventSumw2L",&genEventSumw2L,"genEventSumw2L/D");
    runTree->Branch("runL",&runL,"runL/i");

    //Weight sums tree
    Float_t Generator_weightSumL;
    UInt_t nLHEPdfWeightSumL;
    std::vector<Float_t> LHEPdfWeightSumL;
    Float_t LHEWeight_originalXWGTUPSumL;
    Float_t genWeightSumL;

    TTree *weightSumsTree = new TTree("weightSumsTree", "weightSumsTree");

    weightSumsTree->Branch("Generator_weightSumL",&Generator_weightSumL,"Generator_weightSumL/F");
    weightSumsTree->Branch("nLHEPdfWeightSumL",&nLHEPdfWeightSumL,"nLHEPdfWeightSumL/i");
    weightSumsTree->Branch("LHEPdfWeightSumL",&LHEPdfWeightSumL);
    weightSumsTree->Branch("LHEWeight_originalXWGTUPSumL",&LHEWeight_originalXWGTUPSumL,"LHEWeight_originalXWGTUPSumL/F");
    weightSumsTree->Branch("genWeightSumL",&genWeightSumL,"genWeightSumL/F");

    Float_t dataSetTotWeight = 0;

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


        TTreeReaderValue<Int_t> ZFJIndL(myEventsReader,"ZFJIndL");
        TTreeReaderValue<Int_t> HFJIndL(myEventsReader,"HFJIndL");
        
        TTreeReaderArray<Int_t> FatJet_hadronFlavourL(myEventsReader,"FatJet_hadronFlavourL");

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


        //Transferring run tree
        TTreeReader myRunsReader("runTree", tmpfile);
        TTreeReaderValue<UInt_t> run(myRunsReader, "runL");
        TTreeReaderValue<UInt_t> nLHEPdfSumw(myRunsReader, "nLHEPdfSumwL");
        TTreeReaderArray<Double_t> LHEPdfSumw(myRunsReader, "LHEPdfSumwL");
        TTreeReaderValue<UInt_t> nLHEScaleSumw(myRunsReader, "nLHEScaleSumwL");
        TTreeReaderArray<Double_t> LHEScaleSumw(myRunsReader, "LHEScaleSumwL");
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
            genEventCountL = *genEventCount;
            genEventSumwL = *genEventSumw;
            genEventSumw2L = *genEventSumw2;
            tmpRunsInt += 1;
            runTree->Fill();
            //clear run tree vectors
            LHEPdfSumwL.clear();
            LHEScaleSumwL.clear();

        }
        std::cout << "Run loop for file " << k << " done. RunsInt " << tmpRunsInt <<"\n";

        //Transferring weight sums tree
        TTreeReader myWeightSumReader("weightSumsTree", tmpfile);
        TTreeReaderValue<Float_t> Generator_weightSum(myWeightSumReader, "Generator_weightSumL");
        TTreeReaderValue<UInt_t> nLHEPdfWeightSum(myWeightSumReader, "nLHEPdfWeightSumL");
        TTreeReaderArray<Float_t> LHEPdfWeightSum(myWeightSumReader, "LHEPdfWeightSumL");
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
            LHEWeight_originalXWGTUPSumL = *LHEWeight_originalXWGTUPSum;
            genWeightSumL = *genWeightSum;
            tmpWeightSumInt += 1;
            weightSumsTree->Fill();
            //clear weight sums tree vectors
            LHEPdfWeightSumL.clear();
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

            Double_t tmpGenWeights = *genWeightL;
            startingCtr += 1;
            startingWeightedCtr += tmpGenWeights;
        


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
            tryingLepWeightedCtr += tmpGenWeights;
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



            
            std::vector<Float_t> SemiLepInvMass;
            
            if (debug) std::cout << "trying SemiLeptonic\n";
            tryingSemiLepChannelCtr += 1;
            tryingSemiLepChannelWeightedCtr += tmpGenWeights;
        
            tryingSemiLepCtr += 1;
            tryingSemiLepWeightedCtr += tmpGenWeights;
            //Checking that there are enough FJs for both the Z and the H
            UInt_t numFatJet = *nFatJetL;
            UInt_t nPassingJetIdFJs = 0;
            for (UInt_t fatJetInd=0;fatJetInd<numFatJet;fatJetInd++){
                if (FatJet_jetIdL[fatJetInd] == 6) nPassingJetIdFJs += 1;

            }

            if (nPassingJetIdFJs >=2){
                passEnoughFJsInSemiLepChannelCtr += 1;
                passEnoughFJsInSemiLepChannelWeightedCtr += tmpGenWeights;
                


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
                    passSemiLepLepCutCtr += 1;
                    passSemiLepLepCutWeightedCtr += tmpGenWeights;
                
                    
                }






                if (debug){
                    std::cout << "Pre FJC dRCheckVecAr.size() " << dRCheckVecAr.size() << "\n";
                }
                doHiggsFatJetCutBeforeZMDPNSelection(nFatJetLen,hFatJet_pt_fromHTag,hFatJet_phi_fromHTag,hFatJet_eta_fromHTag,hFatJet_mass_fromHTag,hFatJet_HTag_fromHTag,hFatJet_ind_fromHTag,FatJet_particleNetMD_QCDL,FatJet_particleNetMD_XbbL,hFatJetParticleNetCut,FatJet_pt_FinalL,hFatJetPTCut,FatJet_jetIdL,FatJet_phi_FinalL,FatJet_eta_FinalL,FatJet_mass_FinalL,dRCheckVecAr,dRCut,passedAsSemiLepLepCutBool,passedAsSemiLepHiggsCutBool);
                
                if (debug) std::cout << " found Higgs fat jet\n";


                if (passedAsSemiLepHiggsCutBool){
                    passHiggsFJInSemiLepChannelCtr += 1;
                    passHiggsFJInSemiLepChannelWeightedCtr += tmpGenWeights;

                    
                
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
                    passFJInSemiLepChannelWeightedCtr += tmpGenWeights;

                
                    FJIndAr.push_back(FJInd);
                    FJIndAr.push_back(hFatJet_ind_fromHTag);
                    
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
            if ((!passesCutsBool)) continue;
            

            //Now fat jets
            
            if (debug){
                std::cout << "Entering Fat Jets Loop\n";
            }








            bool passesSTCutBool = false;
            doHiggsFatJetCutSTWithBDTVars(dRCheckVecAr,ZPairPlusHInvMassCut,ZPairPlusHPtCut,ZPairPlusHInvMass,ZPairPlusHPt,passesSTCutBool);
            if (!passesSTCutBool) continue;
            if (debug) std::cout << " found Higgs fat jet\n";
            passHiggsFJCtr += 1;
            passHiggsFJWeightedCtr += tmpGenWeights;
            
            

            if (passedAsSemiLepBool) {
                passHiggsFJSemiLepCtr += 1;
                passHiggsFJWeightedSemiLepCtr += tmpGenWeights;
            
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
            passVBFJetBVetoWeightedCtr += tmpGenWeights;
        

            
            if (passedAsSemiLepBool) {
                passVBFJetBVetoSemiLepCtr += 1;
                passVBFJetBVetoSemiLepWeightedCtr += tmpGenWeights;
            
            }
            



            if (debug) std::cout << "Entering jet loop. Len: " << nJetLen << "\n";
            //doVBFJetCutPtSelectionWithBDTVars(nJetLen,Jet_ptL,Jet_jetIdL,Jet_etaL,Jet_phiL,Jet_massL,jetPTCut,jetEtaDifCut,jetInvMassCut,jetPairInvMass,jetLeadPt,jetLeadEta,jetLeadPhi,jetLeadMass,jetTrailingPt,jetTrailingEta,jetTrailingPhi,jetTrailingMass,leadJet_1,leadJet_2,dRCheckVecAr,dRCut,debug);
            //doVBFJetCutdEtaSelectionWithBDTVars(nJetLen,Jet_ptL,Jet_jetIdL,Jet_etaL,Jet_phiL,Jet_massL,jetPTCut,jetEtaDifCut,jetInvMassCut,jetPairInvMass,jetLeadPt,jetLeadEta,jetLeadPhi,jetLeadMass,jetTrailingPt,jetTrailingEta,jetTrailingPhi,jetTrailingMass,leadJet_1,leadJet_2,dRCheckVecAr,dRCut,debug);
            doVBFJetCutdEtaSelectionNoInvMassWithBDTVars(nJetLen,Jet_pt_FinalL,Jet_jetIdL,Jet_eta_FinalL,Jet_phi_FinalL,Jet_mass_FinalL,jetPTCut,jetEtaDifCut,jetInvMassCut,jetPairInvMass,jetLeadPt,jetLeadEta,jetLeadPhi,jetLeadMass,jetTrailingPt,jetTrailingEta,jetTrailingPhi,jetTrailingMass,leadJet_1,leadJet_2,dRCheckVecAr,dRCut,debug);
            //std::cout << jetLeadPt << endl;
            if (jetLeadPt == 0) continue;
            debugOutputForVBFJetCut(evCount,leadJet_1,leadJet_2,Jet_phi_FinalL,Jet_eta_FinalL,debug);
            passVBFJets += 1;
            passVBFJetsWeighted += tmpGenWeights;

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
                passVBFJetsWeightedCtr += tmpGenWeights;


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
                passLepVetoWeightedCtr += tmpGenWeights;


                //get number of passing VBFJets

                UInt_t tmpnAK4JetsPassing = 0;

                for (UInt_t nJetItr=0; nJetItr<nJetLen;nJetItr++){
                    UInt_t tmpJetPt = Jet_pt_FinalL[nJetItr];
                    //Jet_etaL[nJetItr]
                    Int_t tmpJetId = Jet_jetIdL[nJetItr];
                    if (tmpJetPt < 30 || !(tmpJetId == 6)) continue;
                    tmpnAK4JetsPassing += 1;

                
                }
            

                if (passedAsSemiLepBool){


                    passAsSemiLepCtr += 1;
                    passAsSemiLepWeightedCtr += tmpGenWeights;

                    //EventCor/UncInds
                    JECCorInd_SL_L = JECCorInd;
                    JECCorUpOrDown_SL_L = JECCorUpOrDown;
                    RochInd_SL_L = RochInd;
                    JERInd_SL_L = JERInd;

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
                    fixedGridRhoFastjetAll_SL_L = *fixedGridRhoFastjetAllL;


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


                    
                    FatJet_hadronFlavour_SL_L =  FatJet_hadronFlavourL[FJIndAr[0]];

                    firstHToBBBool_SL_L = *HTobbBoolL;

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
                    luminosityBlockL = *luminosityBlock;
                    eventL = *event;

                    selectedZFJ_InvMassPNRegress_JMSNomJMRNom_SL_L = FatJet_particleNet_mass_JMSNomJMRNomCorL[FJIndAr[0]];

                    selectedHiggsFJ_InvMassPNRegress_JMSNomJMRNom_SL_L = FatJet_particleNet_mass_JMSNomJMRNomCorL[FJIndAr[1]];

                    passingEvSemiLepTree->Fill();

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

                    Jet_puIdL.clear();

                    PSWeightL.clear();
                    LHEScaleWeightL.clear();
                    LHEPdfWeightL.clear();

                    Jet_LowPtPassesPUIDL.clear();

                }

            }

        }

        
    }



    clock_t endt = clock();
    double time_spent = (double)(endt - startt) / CLOCKS_PER_SEC;


    std::cout << "Finished file loop. " << "time: " << time_spent << "\n";
    //crossSection = crossSectionAvg / crossSectionCnt;
        
    std::cout << "XS: " << crossSection << "\n";
    std::cout << "nEv total: " << datanEv << "\n";
    std::cout << "nEv post pre-selection: " << datanEvPass << "\n"; 


    std::cout << "==============================TOTAL COUNTERS==============================\n";
    
    std::cout << "startingCtr: " << startingCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "tryingSemiLepChannelCtr = " << tryingSemiLepChannelCtr << "\n";
    std::cout << "Double_t " << saveName << "startingWeightedCtr = " << startingWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "passEnoughFJsInSemiLepChannelCtr = " << passEnoughFJsInSemiLepChannelCtr << "\n";
    std::cout << "Double_t " << saveName << "passEnoughFJsInSemiLepChannelWeightedCtr = " << passEnoughFJsInSemiLepChannelWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "passSemiLepLepCutCtr = " << passSemiLepLepCutCtr << "\n";
    std::cout << "Double_t " << saveName << "passSemiLepLepCutWeightedCtr = " << passSemiLepLepCutWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "passHiggsFJInSemiLepChannelCtr = " << passHiggsFJInSemiLepChannelCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJInSemiLepChannelWeightedCtr = " << passHiggsFJInSemiLepChannelWeightedCtr << "\n";
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
    std::cout << "UInt_t " << saveName << "PassSemiLepChannelCtr = " << passSemiLepChannelCtr << "\n";
    std::cout << "Double_t " << saveName << "PassSemiLepChannelWeightedCtr = " << passSemiLepChannelWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJCtr = " << passHiggsFJCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJWeightedCtr = " << passHiggsFJWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJSemiLepCtr = " << passHiggsFJSemiLepCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJWeightedSemiLepCtr = " << passHiggsFJWeightedSemiLepCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassVBFJetBVetoCtr = " << passVBFJetBVetoCtr << "\n";
    std::cout << "Double_t " << saveName << "passVBFJetBVetoWeightedCtr = " << passVBFJetBVetoWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassVBFJetBVetoSemiLepCtr = " << passVBFJetBVetoSemiLepCtr << "\n";
    std::cout << "Double_t " << saveName << "passVBFJetBVetoWeightedSemiLepCtr = " << passVBFJetBVetoWeightedSemiLepCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassVBFJetsCtr = " << passVBFJetsCtr << "\n";
    std::cout << "Double_t " << saveName << "PassVBFJetsWeightedCtr = " << passVBFJetsWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassLepVetoCtr = " << passLepVetoCtr << "\n";
    std::cout << "Double_t " << saveName << "PassLepVetoWeightedCtr = " << PassLepVetoWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassAsSemiLepCtr = " << passAsSemiLepCtr << "\n";
    std::cout << "Double_t " << saveName << "PassAsSemiLepWeightedCtr = " << passAsSemiLepWeightedCtr << "\n";
    std::cout << "------------------------\n";



    outFile->cd();
    weightSumsTree->Write("",TObject::kOverwrite);
    runTree->Write("",TObject::kOverwrite);
    passingEvSemiLepTree->Write("",TObject::kOverwrite);
    //btagEffTree->Write("",TObject::kOverwrite);

    outFile->Close();

}