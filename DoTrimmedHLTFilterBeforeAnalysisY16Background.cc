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


void DoTrimmedHLTFilterBeforeAnalysisY16Background(string datasetString,UInt_t fileInd){
    // Open the file. Note that the name of your file outside this class
    // will probably NOT be experiment.root.
    std::cout << "start\n";
    clock_t startt = clock();
    //Analyzer will run over all files put into fileAr

    std::vector<std::string> fileAr;

    std::string saveName;
    float crossSection;
    bool isBackground;
    bool useLHETree = false;
    bool useFJGenMatchTree = false;
    bool useJGenMatchTree = false;

    if (datasetString == "ttHToBB") ttHToBBBackground = true;
    if (datasetString == "ttZJets") ttZJetsBackground = true;
    if (datasetString == "ttWJets") ttWJetsBackground = true;
    if (datasetString == "DY") DYBackground = true;
    if (datasetString == "TTJets") TTJetsBackground = true;
    if (datasetString == "ST_s_Channel") ST_s_ChannelBackground = true;
    if (datasetString == "ST_t_ChannelAntiTop") ST_t_ChannelAntiTopBackground = true;
    if (datasetString == "ST_t_ChannelTop") ST_t_ChannelTopBackground = true;
    if (datasetString == "ZZ") ZZBackground = true;
    if (datasetString == "WW") WWBackground = true;
    if (datasetString == "WZ") WZBackground = true;
    if (datasetString == "TTbb_TTToHadronic") TTbb_TTToHadronicBackground = true;
    if (datasetString == "TTbb_TTTo2L2Nu") TTbb_TTTo2L2NuBackground = true;
    if (datasetString == "TTbb_TTToSemiLeptonic") TTbb_TTToSemiLeptonicBackground = true;

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


    if (datasetString == "DYM10To50") DYM10To50Background = true;
    if (datasetString == "ST_tW_antitop") ST_tW_antitopBackground = true;
    if (datasetString == "ST_tW_top") ST_tW_topBackground = true;
    if (datasetString == "EWKWMinus2Jets_WToLNu") EWKWMinus2Jets_WToLNuBackground = true;
    if (datasetString == "EWKWMinus2Jets_WToQQ") EWKWMinus2Jets_WToQQBackground = true;
    if (datasetString == "EWKWPlus2Jets_WToLNu") EWKWPlus2Jets_WToLNuBackground = true;
    if (datasetString == "EWKWPlus2Jets_WToQQ") EWKWPlus2Jets_WToQQBackground = true;
    if (datasetString == "VHToNonbb") VHToNonbbBackground = true;
    if (datasetString == "WminusH_HToBB_WToLNu") WminusH_HToBB_WToLNuBackground = true;
    if (datasetString == "WminusH_HToBB_WToQQ") WminusH_HToBB_WToQQBackground = true;
    if (datasetString == "WplusH_HToBB_WToLNu") WplusH_HToBB_WToLNuBackground = true;
    if (datasetString == "WplusH_HToBB_WToQQ") WplusH_HToBB_WToQQBackground = true;
    if (datasetString == "WJetsToLNu") WJetsToLNuBackground = true;
    if (datasetString == "WWW") WWWBackground = true;
    if (datasetString == "WWZ") WWZBackground = true;
    if (datasetString == "WZZ") WZZBackground = true;
    if (datasetString == "ZH_HToBB_ZToLL") ZH_HToBB_ZToLLBackground = true;
    if (datasetString == "ZH_HToBB_ZToQQ") ZH_HToBB_ZToQQBackground = true;
    if (datasetString == "ggZH_HToBB_ZToLL") ggZH_HToBB_ZToLLBackground = true;
    if (datasetString == "ggZH_HToBB_ZToQQ") ggZH_HToBB_ZToQQBackground = true;
    if (datasetString == "EWKZ2Jets_ZToLL") EWKZ2Jets_ZToLLBackground = true;
    if (datasetString == "EWKZ2Jets_ZToNuNu") EWKZ2Jets_ZToNuNuBackground = true;
    if (datasetString == "EWKZ2Jets_ZToQQ") EWKZ2Jets_ZToQQBackground = true;
    if (datasetString == "ZZZ") ZZZBackground = true;

    ////////////////////////////////GETTING DATASET////////////////////////////////
    ////////////////////////////////GETTING DATASET////////////////////////////////
    ////////////////////////////////GETTING DATASET////////////////////////////////
    ////////////////////////////////GETTING DATASET////////////////////////////////

    std::string strAdd;
    if (scratchDown) strAdd ="/afs/crc.nd.edu/user/d/dlutton/FROM_PANASAS";
    else strAdd ="/scratch365";

    
    if (ttHToBBBackground){
        //saveName = "ttHToBBY16";
        crossSection = 0.5071*0.582;

        saveName = "ttHToBBY16";
        
        isBackground = true;
        int arrSize = sizeof(ttHToBBY16BackgroundAr)/sizeof(ttHToBBY16BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(ttHToBBY16BackgroundAr[i]);
        }
        */
        fileAr.push_back(ttHToBBY16BackgroundAr[fileInd]);
    }
    else if (ttZJetsBackground){
        //saveName = "ttZJetsY16";
        
        crossSection = 0.5407;
        saveName = "ttZJetsY16";
        isBackground = true;
        int arrSize = sizeof(ttZJetsY16BackgroundAr)/sizeof(ttZJetsY16BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(ttZJetsY16BackgroundAr[i]);
        }
        */
        fileAr.push_back(ttZJetsY16BackgroundAr[fileInd]);
    }
    else if (ttWJetsBackground){
        
        crossSection = 0.4611;
        saveName = "ttWJetsY16";
        isBackground = true;
        int arrSize = sizeof(ttWJetsY16BackgroundAr)/sizeof(ttWJetsY16BackgroundAr[0]);
        fileAr.push_back(ttWJetsY16BackgroundAr[fileInd]);
    }
    else if (DYBackground){
        //saveName = "DYY16";
        
        crossSection = 5364;
        saveName = "DYY16";

        isBackground = true;
        int arrSize = sizeof(DYY16BackgroundAr)/sizeof(DYY16BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(DYY16BackgroundAr[i]);
        }
        */
        fileAr.push_back(DYY16BackgroundAr[fileInd]);
    }
    else if (QCDPT170to300Background){
        //saveName = "QCDPT170to300Y16";
        
        crossSection = 103300.0;

        saveName = "QCDPT170to300Y16";
        
        isBackground = true;
        int arrSize = sizeof(QCDPT170to300Y16BackgroundAr)/sizeof(QCDPT170to300Y16BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(QCDPT170to300Y16BackgroundAr[i]);
        }
        */
        fileAr.push_back(QCDPT170to300Y16BackgroundAr[fileInd]);
    }
    else if (QCDPT300to470Background){
        //saveName = "QCDPT300to470Y16";
        
        crossSection = 6826.0;

        saveName = "QCDPT300to470Y16";
        
        isBackground = true;
        int arrSize = sizeof(QCDPT300to470Y16BackgroundAr)/sizeof(QCDPT300to470Y16BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(QCDPT300to470Y16BackgroundAr[i]);
        }
        */
        fileAr.push_back(QCDPT300to470Y16BackgroundAr[fileInd]);
    }
    else if (QCDPT470to600Background){
        //saveName = "QCDPT470to600Y16";
        
        crossSection = 552.6;
        
        saveName = "QCDPT470to600Y16";

        isBackground = true;
        int arrSize = sizeof(QCDPT470to600Y16BackgroundAr)/sizeof(QCDPT470to600Y16BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(QCDPT470to600Y16BackgroundAr[i]);
        }
        */
        fileAr.push_back(QCDPT470to600Y16BackgroundAr[fileInd]);
    }
    else if (QCDPT600to800Background){
        //saveName = "QCDPT600to800Y16";
        
        crossSection = 156.6;

        saveName = "QCDPT600to800Y16";
        
        isBackground = true;
        int arrSize = sizeof(QCDPT600to800Y16BackgroundAr)/sizeof(QCDPT600to800Y16BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(QCDPT600to800Y16BackgroundAr[i]);
        }
        */
        fileAr.push_back(QCDPT600to800Y16BackgroundAr[fileInd]);
    }
    else if (QCDPT800to1000Background){
        //saveName = "QCDPT800to1000Y16";
        
        crossSection = 26.32;

        saveName = "QCDPT800to1000Y16";
        
        isBackground = true;
        int arrSize = sizeof(QCDPT800to1000Y16BackgroundAr)/sizeof(QCDPT800to1000Y16BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(QCDPT800to1000Y16BackgroundAr[i]);
        }
        */
        fileAr.push_back(QCDPT800to1000Y16BackgroundAr[fileInd]);
    }
    else if (QCDPT1000to1400Background){
        //saveName = "QCDPT1000to1400Y16";
        
        crossSection = 7.5;

        saveName = "QCDPT1000to1400Y16";
        
        isBackground = true;
        int arrSize = sizeof(QCDPT1000to1400Y16BackgroundAr)/sizeof(QCDPT1000to1400Y16BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(QCDPT1000to1400Y16BackgroundAr[i]);
        }
        */
        fileAr.push_back(QCDPT1000to1400Y16BackgroundAr[fileInd]);
    }
    else if (QCDPT1400to1800Background){
        //saveName = "QCDPT1400to1800Y16";
        
        crossSection = 0.6479;

        saveName = "QCDPT1400to1800Y16";
        
        isBackground = true;
        int arrSize = sizeof(QCDPT1400to1800Y16BackgroundAr)/sizeof(QCDPT1400to1800Y16BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(QCDPT1400to1800Y16BackgroundAr[i]);
        }
        */
        fileAr.push_back(QCDPT1400to1800Y16BackgroundAr[fileInd]);
    }
    else if (QCDPT1800to2400Background){
        //saveName = "QCDPT1800to2400Y16";
        
        crossSection = 0.08715;

        saveName = "QCDPT1800to2400Y16";
        
        isBackground = true;
        int arrSize = sizeof(QCDPT1800to2400Y16BackgroundAr)/sizeof(QCDPT1800to2400Y16BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(QCDPT1800to2400Y16BackgroundAr[i]);
        }
        */
        fileAr.push_back(QCDPT1800to2400Y16BackgroundAr[fileInd]);
    }
    else if (QCDPT2400to3200Background){
        //saveName = "QCDPT2400to3200Y16";
        
        crossSection = 0.005242;

        saveName = "QCDPT2400to3200Y16";
        
        isBackground = true;
        int arrSize = sizeof(QCDPT2400to3200Y16BackgroundAr)/sizeof(QCDPT2400to3200Y16BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(QCDPT2400to3200Y16BackgroundAr[i]);
        }
        */
        fileAr.push_back(QCDPT2400to3200Y16BackgroundAr[fileInd]);
    }
    else if (QCDPT3200toInfBackground){
        //saveName = "QCDPT3200toInfY16";
        
        crossSection = 0.0001349;

        saveName = "QCDPT3200toInfY16";
        
        isBackground = true;
        int arrSize = sizeof(QCDPT3200toInfY16BackgroundAr)/sizeof(QCDPT3200toInfY16BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(QCDPT3200toInfY16BackgroundAr[i]);
        }
        */
        fileAr.push_back(QCDPT3200toInfY16BackgroundAr[fileInd]);
    }
    else if (TTJetsBackground){
        //saveName = "Y16";
        
        crossSection = 722.8;

        saveName = "TTJetsY16";
        
        isBackground = true;
        int arrSize = sizeof(TTJetsY16BackgroundAr)/sizeof(TTJetsY16BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(TTJetsY16BackgroundAr[i]);
        }
        */
        fileAr.push_back(TTJetsY16BackgroundAr[fileInd]);
    }
    else if (ST_s_ChannelBackground){
        //saveName = "Y16";
        
        crossSection = 3.74;

        saveName = "ST_s_ChannelY16";
        
        isBackground = true;
        int arrSize = sizeof(ST_s_ChannelY16BackgroundAr)/sizeof(ST_s_ChannelY16BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(ST_s_ChannelY16BackgroundAr[i]);
        }
        */
        fileAr.push_back(ST_s_ChannelY16BackgroundAr[fileInd]);
    }
    else if (ST_t_ChannelAntiTopBackground){
        //saveName = "Y16";
        
        crossSection = 69.09;

        saveName = "ST_t_ChannelAntiTopY16";
        
        isBackground = true;
        int arrSize = sizeof(ST_t_ChannelAntiTopY16BackgroundAr)/sizeof(ST_t_ChannelAntiTopY16BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(ST_t_ChannelAntiTopY16BackgroundAr[i]);
        }
        */
        fileAr.push_back(ST_t_ChannelAntiTopY16BackgroundAr[fileInd]);
    }
    else if (ST_t_ChannelTopBackground){
        //saveName = "Y16";
        
        crossSection = 115.3;

        saveName = "ST_t_ChannelTopY16";
        
        isBackground = true;
        int arrSize = sizeof(ST_t_ChannelTopY16BackgroundAr)/sizeof(ST_t_ChannelTopY16BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(ST_t_ChannelTopY16BackgroundAr[i]);
        }
        */
        fileAr.push_back(ST_t_ChannelTopY16BackgroundAr[fileInd]);
    }
    else if (ZZBackground){
        //saveName = "Y16";
        
        crossSection = 12.17;

        saveName = "ZZY16";
        
        isBackground = true;
        int arrSize = sizeof(ZZY16BackgroundAr)/sizeof(ZZY16BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(ZZY16BackgroundAr[i]);
        }
        */
        fileAr.push_back(ZZY16BackgroundAr[fileInd]);
    }
    else if (WWBackground){
        //saveName = "Y16";
        
        crossSection = 75.95;

        saveName = "WWY16";
        
        isBackground = true;
        int arrSize = sizeof(WWY16BackgroundAr)/sizeof(WWY16BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(WWY16BackgroundAr[i]);
        }
        */
        fileAr.push_back(WWY16BackgroundAr[fileInd]);
    }
    else if (WZBackground){
        //saveName = "Y16";
        
        crossSection = 27.59;

        saveName = "WZY16";
        
        isBackground = true;
        int arrSize = sizeof(WZY16BackgroundAr)/sizeof(WZY16BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(WZY16BackgroundAr[i]);
        }
        */
        fileAr.push_back(WZY16BackgroundAr[fileInd]);
    }
    else if (TTbb_TTToHadronicBackground){
        //saveName = "QCDPT3200toInfY16";
        
        crossSection = 5.5;

        saveName = "TTbb_TTToHadronicY16";
        
        isBackground = true;
        int arrSize = sizeof(TTbb_TTToHadronicY16BackgroundAr)/sizeof(TTbb_TTToHadronicY16BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(TTbb_TTToHadronicY16BackgroundAr[i]);
        }
        */
        fileAr.push_back(TTbb_TTToHadronicY16BackgroundAr[fileInd]);
    }
    else if (TTbb_TTTo2L2NuBackground){
        //saveName = "Y16";
        
        crossSection = 2.9;

        saveName = "TTbb_TTTo2L2NuY16";
        
        isBackground = true;
        int arrSize = sizeof(TTbb_TTTo2L2NuY16BackgroundAr)/sizeof(TTbb_TTTo2L2NuY16BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(TTbb_TTTo2L2NuY16BackgroundAr[i]);
        }
        */
        fileAr.push_back(TTbb_TTTo2L2NuY16BackgroundAr[fileInd]);
    }
    else if (TTbb_TTToSemiLeptonicBackground){
        //saveName = "Y16";
        
        crossSection = 4.7;

        saveName = "TTbb_TTToSemiLeptonicY16";
        
        isBackground = true;
        int arrSize = sizeof(TTbb_TTToSemiLeptonicY16BackgroundAr)/sizeof(TTbb_TTToSemiLeptonicY16BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back(TTbb_TTToSemiLeptonicY16BackgroundAr[i]);
        }
        */
        fileAr.push_back(TTbb_TTToSemiLeptonicY16BackgroundAr[fileInd]);
    }
    else if (DYM10To50Background){
        //datasetType = 50;
        saveName = "DYM10To50Y16";
        
        int arrSize = sizeof(DYM10To50Y16BackgroundAr)/sizeof(DYM10To50Y16BackgroundAr[0]);
        fileAr.push_back(DYM10To50Y16BackgroundAr[fileInd]);
    }
    else if (ST_tW_antitopBackground){
        //datasetType = 51;
        saveName = "ST_tW_antitopY16";
        
        int arrSize = sizeof(ST_tW_antitopY16BackgroundAr)/sizeof(ST_tW_antitopY16BackgroundAr[0]);
        fileAr.push_back(ST_tW_antitopY16BackgroundAr[fileInd]);
    }
    else if (ST_tW_topBackground){
        //datasetType = 52;
        saveName = "ST_tW_topY16";
        
        int arrSize = sizeof(ST_tW_topY16BackgroundAr)/sizeof(ST_tW_topY16BackgroundAr[0]);
        fileAr.push_back(ST_tW_topY16BackgroundAr[fileInd]);
    }
    else if (EWKWMinus2Jets_WToLNuBackground){
        //datasetType = 53;
        saveName = "EWKWMinus2Jets_WToLNuY16";
        
        int arrSize = sizeof(EWKWMinus2Jets_WToLNuY16BackgroundAr)/sizeof(EWKWMinus2Jets_WToLNuY16BackgroundAr[0]);
        fileAr.push_back(EWKWMinus2Jets_WToLNuY16BackgroundAr[fileInd]);
    }
    else if (EWKWMinus2Jets_WToQQBackground){
        //datasetType = 54;
        saveName = "EWKWMinus2Jets_WToQQY16";
        
        int arrSize = sizeof(EWKWMinus2Jets_WToQQY16BackgroundAr)/sizeof(EWKWMinus2Jets_WToQQY16BackgroundAr[0]);
        fileAr.push_back(EWKWMinus2Jets_WToQQY16BackgroundAr[fileInd]);
    }
    else if (EWKWPlus2Jets_WToLNuBackground){
        //datasetType = 55;
        saveName = "EWKWPlus2Jets_WToLNuY16";
        
        int arrSize = sizeof(EWKWPlus2Jets_WToLNuY16BackgroundAr)/sizeof(EWKWPlus2Jets_WToLNuY16BackgroundAr[0]);
        fileAr.push_back(EWKWPlus2Jets_WToLNuY16BackgroundAr[fileInd]);
    }
    else if (EWKWPlus2Jets_WToQQBackground){
        //datasetType = 56;
        saveName = "EWKWPlus2Jets_WToQQY16";
        
        int arrSize = sizeof(EWKWPlus2Jets_WToQQY16BackgroundAr)/sizeof(EWKWPlus2Jets_WToQQY16BackgroundAr[0]);
        fileAr.push_back(EWKWPlus2Jets_WToQQY16BackgroundAr[fileInd]);
    }
    else if (VHToNonbbBackground){
        //datasetType = 57;
        saveName = "VHToNonbbY16";
        
        int arrSize = sizeof(VHToNonbbY16BackgroundAr)/sizeof(VHToNonbbY16BackgroundAr[0]);
        fileAr.push_back(VHToNonbbY16BackgroundAr[fileInd]);
    }
    else if (WminusH_HToBB_WToLNuBackground){
        //datasetType = 58;
        saveName = "WminusH_HToBB_WToLNuY16";
        
        int arrSize = sizeof(WminusH_HToBB_WToLNuY16BackgroundAr)/sizeof(WminusH_HToBB_WToLNuY16BackgroundAr[0]);
        fileAr.push_back(WminusH_HToBB_WToLNuY16BackgroundAr[fileInd]);
    }
    else if (WminusH_HToBB_WToQQBackground){
        //datasetType = 59;
        saveName = "WminusH_HToBB_WToQQY16";
        
        int arrSize = sizeof(WminusH_HToBB_WToQQY16BackgroundAr)/sizeof(WminusH_HToBB_WToQQY16BackgroundAr[0]);
        fileAr.push_back(WminusH_HToBB_WToQQY16BackgroundAr[fileInd]);
    }
    else if (WplusH_HToBB_WToLNuBackground){
        //datasetType = 60;
        saveName = "WplusH_HToBB_WToLNuY16";
        
        int arrSize = sizeof(WplusH_HToBB_WToLNuY16BackgroundAr)/sizeof(WplusH_HToBB_WToLNuY16BackgroundAr[0]);
        fileAr.push_back(WplusH_HToBB_WToLNuY16BackgroundAr[fileInd]);
    }
    else if (WplusH_HToBB_WToQQBackground){
        //datasetType = 61;
        saveName = "WplusH_HToBB_WToQQY16";
        
        int arrSize = sizeof(WplusH_HToBB_WToQQY16BackgroundAr)/sizeof(WplusH_HToBB_WToQQY16BackgroundAr[0]);
        fileAr.push_back(WplusH_HToBB_WToQQY16BackgroundAr[fileInd]);
    }
    else if (WJetsToLNuBackground){
        //datasetType = 62;
        saveName = "WJetsToLNuY16";
        
        int arrSize = sizeof(WJetsToLNuY16BackgroundAr)/sizeof(WJetsToLNuY16BackgroundAr[0]);
        fileAr.push_back(WJetsToLNuY16BackgroundAr[fileInd]);
    }
    else if (WWWBackground){
        //datasetType = 63;
        saveName = "WWWY16";
        
        int arrSize = sizeof(WWWY16BackgroundAr)/sizeof(WWWY16BackgroundAr[0]);
        fileAr.push_back(WWWY16BackgroundAr[fileInd]);
    }
    else if (WWZBackground){
        //datasetType = 64;
        saveName = "WWZY16";
        
        int arrSize = sizeof(WWZY16BackgroundAr)/sizeof(WWZY16BackgroundAr[0]);
        fileAr.push_back(WWZY16BackgroundAr[fileInd]);
    }
    else if (WZZBackground){
        //datasetType = 65;
        saveName = "WZZY16";
        
        int arrSize = sizeof(WZZY16BackgroundAr)/sizeof(WZZY16BackgroundAr[0]);
        fileAr.push_back(WZZY16BackgroundAr[fileInd]);
    }
    else if (ZH_HToBB_ZToLLBackground){
        //datasetType = 66;
        saveName = "ZH_HToBB_ZToLLY16";
        
        int arrSize = sizeof(ZH_HToBB_ZToLLY16BackgroundAr)/sizeof(ZH_HToBB_ZToLLY16BackgroundAr[0]);
        fileAr.push_back(ZH_HToBB_ZToLLY16BackgroundAr[fileInd]);
    }
    else if (ZH_HToBB_ZToQQBackground){
        //datasetType = 67;
        saveName = "ZH_HToBB_ZToQQY16";
        
        int arrSize = sizeof(ZH_HToBB_ZToQQY16BackgroundAr)/sizeof(ZH_HToBB_ZToQQY16BackgroundAr[0]);
        fileAr.push_back(ZH_HToBB_ZToQQY16BackgroundAr[fileInd]);
    }
    else if (ggZH_HToBB_ZToLLBackground){
        //datasetType = 68;
        saveName = "ggZH_HToBB_ZToLLY16";
        
        int arrSize = sizeof(ggZH_HToBB_ZToLLY16BackgroundAr)/sizeof(ggZH_HToBB_ZToLLY16BackgroundAr[0]);
        fileAr.push_back(ggZH_HToBB_ZToLLY16BackgroundAr[fileInd]);
    }
    else if (ggZH_HToBB_ZToQQBackground){
        //datasetType = 69;
        saveName = "ggZH_HToBB_ZToQQY16";
        
        int arrSize = sizeof(ggZH_HToBB_ZToQQY16BackgroundAr)/sizeof(ggZH_HToBB_ZToQQY16BackgroundAr[0]);
        fileAr.push_back(ggZH_HToBB_ZToQQY16BackgroundAr[fileInd]);
    }
    else if (EWKZ2Jets_ZToLLBackground){
        //datasetType = 70;
        saveName = "EWKZ2Jets_ZToLLY16";
        
        int arrSize = sizeof(EWKZ2Jets_ZToLLY16BackgroundAr)/sizeof(EWKZ2Jets_ZToLLY16BackgroundAr[0]);
        fileAr.push_back(EWKZ2Jets_ZToLLY16BackgroundAr[fileInd]);
    }
    else if (EWKZ2Jets_ZToNuNuBackground){
        //datasetType = 71;
        saveName = "EWKZ2Jets_ZToNuNuY16";
        
        int arrSize = sizeof(EWKZ2Jets_ZToNuNuY16BackgroundAr)/sizeof(EWKZ2Jets_ZToNuNuY16BackgroundAr[0]);
        fileAr.push_back(EWKZ2Jets_ZToNuNuY16BackgroundAr[fileInd]);
    }
    else if (EWKZ2Jets_ZToQQBackground){
        //datasetType = 72;
        saveName = "EWKZ2Jets_ZToQQY16";
        
        int arrSize = sizeof(EWKZ2Jets_ZToQQY16BackgroundAr)/sizeof(EWKZ2Jets_ZToQQY16BackgroundAr[0]);
        fileAr.push_back(EWKZ2Jets_ZToQQY16BackgroundAr[fileInd]);
    }
    else if (ZZZBackground){
        //datasetType = 73;
        saveName = "ZZZY16";
        
        int arrSize = sizeof(ZZZY16BackgroundAr)/sizeof(ZZZY16BackgroundAr[0]);
        fileAr.push_back(ZZZY16BackgroundAr[fileInd]);
    }
    else if (testRun){
        saveName = "testRun";
        fileAr.push_back("./unweighted_eventspphzzjjQCD0SMHLOOP0NPE1NPcHWE1QEDE5ResMasAllVer100Ev10080Seed_0p999cHW100GeVIMJetCut_200.root");
        useLHETree = true;
        useFJGenMatchTree = true;
        isBackground = false;
        
    }
    else if (LaraTest){
        saveName = "LaraTest";
        fileAr.push_back("/scratch365/dlutton/NanoAODFiles/pp_hwpwmjj_EFT_VBF_chw_09999000_250k.root");
    }
    else{
        std::cout << "ERROR. NO INPUT DATASET NAME GIVEN\n";
    }

    std::cout << "Doing " << saveName << "\n";
    //Setting up outfile for tree
    std::string outFileStr = "HLTTrimmedFilteredForAnalysis"+saveName+"_"+std::to_string(fileInd)+".root";
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

    UInt_t passFlagCtr = 0;
    Double_t passFlagWeightedCtr = 0;
    UInt_t passHLTCtr = 0;
    Double_t passHLTWeightedCtr = 0;
    UInt_t passnFJCtr = 0;
    Double_t passnFJWeightedCtr = 0;
    UInt_t passnVBFCtr = 0;
    Double_t passnVBFWeightedCtr = 0;


    float crossSectionAvg = 0.;
    UInt_t crossSectionCtr = 0;
    float totCrossSectionWeight = 0.;
    UInt_t totCrossSectionEvCount = 0;
    UInt_t evRunOver = 0;
    UInt_t evCount = 0;
    
    UInt_t nEv;
    UInt_t nEvPass;
    

    TTree *evNumTree = new TTree("evNumTree","evNumTree");

    evNumTree->Branch("nEv",&nEv,"nEv/i");
    evNumTree->Branch("nEvPass",&nEvPass,"nEvPass/i");

    //EventWeights
    //Float_t genWeightL;
    Double_t genWeightL;

    //Jets
    UInt_t nJetL;
    std::vector<Float_t> Jet_etaL;
    std::vector<Float_t> Jet_ptL;
    std::vector<Float_t> Jet_phiL;
    std::vector<Float_t> Jet_massL;
    std::vector<Int_t> Jet_jetIdL;

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

    std::vector<Float_t> Muon_dxyL;
    std::vector<Float_t> Muon_dzL;
    std::vector<Float_t> Muon_miniPFRelIso_allL;
    std::vector<Int_t> Muon_jetIdxL;
    std::vector<Float_t> Muon_jetRelIsoL;
    std::vector<Float_t> Muon_mvaTTHL;

    std::vector<Float_t> Jet_btagDeepFlavBL;

    //ParticleNet
    std::vector<Float_t> FatJet_particleNet_HbbvsQCDL;
    std::vector<Float_t> FatJet_particleNet_ZvsQCDL;
    std::vector<Float_t> FatJet_particleNetMD_QCDL;
    std::vector<Float_t> FatJet_particleNetMD_XbbL;
    std::vector<Float_t> FatJet_particleNetMD_XccL;
    std::vector<Float_t> FatJet_particleNetMD_XqqL;

    //
    Float_t fixedGridRhoFastjetAllL;

    //genChannel characterization
    //0=Leptonic,1=Semi-leptonic,2=Hadronic,3=Other,4=Error
    UInt_t genChannelL = 4;

    Bool_t HTobbBoolL = false;

    
    
    


    TTree *FilteredEventsTree = new TTree("FilteredEventsTree", "FilteredEventsTree");
    //gen weights
    FilteredEventsTree->Branch("genWeightL",&genWeightL,"genWeightL/D");

    //Jets    
    FilteredEventsTree->Branch("nJetL",&nJetL,"nJetL/i");
    FilteredEventsTree->Branch("Jet_etaL",&Jet_etaL);
    FilteredEventsTree->Branch("Jet_ptL",&Jet_ptL);
    FilteredEventsTree->Branch("Jet_phiL",&Jet_phiL);
    FilteredEventsTree->Branch("Jet_massL",&Jet_massL);
    FilteredEventsTree->Branch("Jet_jetIdL",&Jet_jetIdL);

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

    FilteredEventsTree->Branch("Jet_btagDeepFlavBL",&Jet_btagDeepFlavBL);

    //ParticleNet
    FilteredEventsTree->Branch("FatJet_particleNet_HbbvsQCDL",&FatJet_particleNet_HbbvsQCDL);
    FilteredEventsTree->Branch("FatJet_particleNet_ZvsQCDL",&FatJet_particleNet_ZvsQCDL);

    FilteredEventsTree->Branch("FatJet_particleNetMD_QCDL", &FatJet_particleNetMD_QCDL);
    FilteredEventsTree->Branch("FatJet_particleNetMD_XbbL", &FatJet_particleNetMD_XbbL);
    FilteredEventsTree->Branch("FatJet_particleNetMD_XccL", &FatJet_particleNetMD_XccL);
    FilteredEventsTree->Branch("FatJet_particleNetMD_XqqL", &FatJet_particleNetMD_XqqL);

    //
    FilteredEventsTree->Branch("fixedGridRhoFastjetAllL",&fixedGridRhoFastjetAllL);

    //genChannel characterization
    //0=Leptonic,1=Semi-leptonic,2=Hadronic,3=Other,4=Error
    FilteredEventsTree->Branch("genChannelL",&genChannelL,"genChannelL/i");

    FilteredEventsTree->Branch("HTobbBoolL",&HTobbBoolL,"HTobbBoolL/O");



    Double_t sumOfGenWeights = 0;
    
    
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

        //genWeights
        TTreeReaderValue<Float_t> genWeight(myEventsReader, "genWeight");

        //Flag branches

        TTreeReaderValue<Bool_t> Flag_goodVertices(myEventsReader, "Flag_goodVertices");
        TTreeReaderValue<Bool_t> Flag_globalSuperTightHalo2016Filter(myEventsReader, "Flag_globalSuperTightHalo2016Filter");
        TTreeReaderValue<Bool_t> Flag_HBHENoiseFilter(myEventsReader, "Flag_HBHENoiseFilter");
        TTreeReaderValue<Bool_t> Flag_HBHENoiseIsoFilter(myEventsReader, "Flag_HBHENoiseIsoFilter");
        TTreeReaderValue<Bool_t> Flag_EcalDeadCellTriggerPrimitiveFilter(myEventsReader, "Flag_EcalDeadCellTriggerPrimitiveFilter");
        TTreeReaderValue<Bool_t> Flag_BadPFMuonFilter(myEventsReader, "Flag_BadPFMuonFilter");
        TTreeReaderValue<Bool_t> Flag_eeBadScFilter(myEventsReader, "Flag_eeBadScFilter");


        //HLT Branches
        TTreeReaderValue<Bool_t> HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ(myEventsReader, "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ");

        TTreeReaderValue<Bool_t> HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ(myEventsReader, "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ");

        TTreeReaderValue<Bool_t> HLT_IsoMu27(myEventsReader, "HLT_IsoMu27");
        TTreeReaderValue<Bool_t> HLT_Mu50(myEventsReader, "HLT_Mu50");

        TTreeReaderValue<Bool_t> HLT_Ele115_CaloIdVT_GsfTrkIdT(myEventsReader, "HLT_Ele115_CaloIdVT_GsfTrkIdT");
        TTreeReaderValue<Bool_t> HLT_Ele27_WPTight_Gsf(myEventsReader, "HLT_Ele27_WPTight_Gsf");

        //jets

        TTreeReaderValue<UInt_t> nJet(myEventsReader, "nJet");
        TTreeReaderArray<Float_t> Jet_eta(myEventsReader, "Jet_eta");
        TTreeReaderArray<Float_t> Jet_pt(myEventsReader, "Jet_pt");
        TTreeReaderArray<Float_t> Jet_phi(myEventsReader, "Jet_phi");
        TTreeReaderArray<Float_t> Jet_mass(myEventsReader, "Jet_mass");
        TTreeReaderArray<Int_t> Jet_jetId(myEventsReader, "Jet_jetId");

        //Fat jets

        TTreeReaderValue<UInt_t> nFatJet(myEventsReader, "nFatJet");
        TTreeReaderArray<Float_t> FatJet_eta(myEventsReader, "FatJet_eta");
        TTreeReaderArray<Float_t> FatJet_pt(myEventsReader, "FatJet_pt");
        TTreeReaderArray<Float_t> FatJet_phi(myEventsReader, "FatJet_phi");
        TTreeReaderArray<Float_t> FatJet_mass(myEventsReader, "FatJet_mass");
        TTreeReaderArray<Int_t> FatJet_jetId(myEventsReader, "FatJet_jetId");
        TTreeReaderArray<Float_t> FatJet_deepTag_H(myEventsReader, "FatJet_deepTag_H");
        TTreeReaderArray<Float_t> FatJet_deepTag_ZvsQCD(myEventsReader, "FatJet_deepTag_ZvsQCD");
        TTreeReaderArray<Float_t> FatJet_msoftdrop(myEventsReader, "FatJet_msoftdrop");

        //Electrons
        TTreeReaderValue<UInt_t> nElectron(myEventsReader, "nElectron");
        TTreeReaderArray<Float_t> Electron_eta(myEventsReader, "Electron_eta");
        TTreeReaderArray<Float_t> Electron_mass(myEventsReader, "Electron_mass");
        TTreeReaderArray<Int_t> Electron_charge(myEventsReader, "Electron_charge");
        TTreeReaderArray<Float_t> Electron_phi(myEventsReader, "Electron_phi");
        TTreeReaderArray<Float_t> Electron_pt(myEventsReader, "Electron_pt");
        TTreeReaderArray<Float_t> Electron_dr03EcalRecHitSumEt(myEventsReader, "Electron_dr03EcalRecHitSumEt");
        TTreeReaderArray<Float_t> Electron_dr03TkSumPt(myEventsReader, "Electron_dr03TkSumPt");
        TTreeReaderArray<Float_t> Electron_dr03HcalDepth1TowerSumEt(myEventsReader, "Electron_dr03HcalDepth1TowerSumEt");
        TTreeReaderArray<Float_t> Electron_pfRelIso03_all(myEventsReader, "Electron_pfRelIso03_all");
        
        TTreeReaderArray<Float_t> Electron_sip3d(myEventsReader, "Electron_sip3d");
        TTreeReaderArray<Int_t> Electron_cutBased(myEventsReader, "Electron_cutBased");
        TTreeReaderArray<Bool_t> Electron_mvaFall17V2Iso_WP80(myEventsReader, "Electron_mvaFall17V2Iso_WP80");
        TTreeReaderArray<Bool_t> Electron_mvaFall17V2Iso_WP90(myEventsReader, "Electron_mvaFall17V2Iso_WP90");
        TTreeReaderArray<Bool_t> Electron_mvaFall17V2Iso_WPL(myEventsReader, "Electron_mvaFall17V2Iso_WPL");
        TTreeReaderArray<Bool_t> Electron_mvaFall17V2noIso_WP80(myEventsReader, "Electron_mvaFall17V2noIso_WP80");
        TTreeReaderArray<Bool_t> Electron_mvaFall17V2noIso_WP90(myEventsReader, "Electron_mvaFall17V2noIso_WP90");
        TTreeReaderArray<Bool_t> Electron_mvaFall17V2noIso_WPL(myEventsReader, "Electron_mvaFall17V2noIso_WPL");

        //Muons
        TTreeReaderValue<UInt_t> nMuon(myEventsReader, "nMuon");
        TTreeReaderArray<Float_t> Muon_eta(myEventsReader, "Muon_eta");
        TTreeReaderArray<Float_t> Muon_mass(myEventsReader, "Muon_mass");
        TTreeReaderArray<Int_t> Muon_charge(myEventsReader, "Muon_charge");
        TTreeReaderArray<Float_t> Muon_phi(myEventsReader, "Muon_phi");
        TTreeReaderArray<Float_t> Muon_pt(myEventsReader, "Muon_pt");
        TTreeReaderArray<Float_t> Muon_pfRelIso03_all(myEventsReader, "Muon_pfRelIso03_all");
        
        TTreeReaderArray<Float_t> Muon_sip3d(myEventsReader, "Muon_sip3d");
        TTreeReaderArray<Bool_t> Muon_tightId(myEventsReader, "Muon_tightId");
        TTreeReaderArray<Bool_t> Muon_mediumId(myEventsReader, "Muon_mediumId");
        TTreeReaderArray<Bool_t> Muon_looseId(myEventsReader, "Muon_looseId");

        //For LepID
        TTreeReaderArray<Float_t> Electron_dxy(myEventsReader, "Electron_dxy");
        TTreeReaderArray<Float_t> Electron_dz(myEventsReader, "Electron_dz");
        TTreeReaderArray<Float_t> Electron_miniPFRelIso_all(myEventsReader, "Electron_miniPFRelIso_all");
        TTreeReaderArray<Float_t> Electron_sieie(myEventsReader, "Electron_sieie");
        TTreeReaderArray<Float_t> Electron_hoe(myEventsReader, "Electron_hoe");
        TTreeReaderArray<Float_t> Electron_eInvMinusPInv(myEventsReader, "Electron_eInvMinusPInv");
        TTreeReaderArray<Bool_t> Electron_convVeto(myEventsReader, "Electron_convVeto");
        TTreeReaderArray<UChar_t> Electron_lostHits(myEventsReader, "Electron_lostHits");
        TTreeReaderArray<Int_t> Electron_jetIdx(myEventsReader, "Electron_jetIdx");
        TTreeReaderArray<Float_t> Electron_jetRelIso(myEventsReader, "Electron_jetRelIso");
        TTreeReaderArray<Float_t> Electron_mvaTTH(myEventsReader, "Electron_mvaTTH");

        TTreeReaderArray<Float_t> Muon_dxy(myEventsReader, "Muon_dxy");
        TTreeReaderArray<Float_t> Muon_dz(myEventsReader, "Muon_dz");
        TTreeReaderArray<Float_t> Muon_miniPFRelIso_all(myEventsReader, "Muon_miniPFRelIso_all");
        TTreeReaderArray<Int_t> Muon_jetIdx(myEventsReader, "Muon_jetIdx");
        TTreeReaderArray<Float_t> Muon_jetRelIso(myEventsReader, "Muon_jetRelIso");
        TTreeReaderArray<Float_t> Muon_mvaTTH(myEventsReader, "Muon_mvaTTH");

        TTreeReaderArray<Float_t> Jet_btagDeepFlavB(myEventsReader,"Jet_btagDeepFlavB");

        //ParticleNet
        TTreeReaderArray<Float_t> FatJet_particleNet_HbbvsQCD(myEventsReader, "FatJet_particleNet_HbbvsQCD");
        TTreeReaderArray<Float_t> FatJet_particleNet_ZvsQCD(myEventsReader, "FatJet_particleNet_ZvsQCD");
        TTreeReaderArray<Float_t> FatJet_particleNetMD_QCD(myEventsReader, "FatJet_particleNetMD_QCD");
        TTreeReaderArray<Float_t> FatJet_particleNetMD_Xbb(myEventsReader, "FatJet_particleNetMD_Xbb");
        TTreeReaderArray<Float_t> FatJet_particleNetMD_Xcc(myEventsReader, "FatJet_particleNetMD_Xcc");
        TTreeReaderArray<Float_t> FatJet_particleNetMD_Xqq(myEventsReader, "FatJet_particleNetMD_Xqq");

        //

        TTreeReaderValue<Float_t> fixedGridRhoFastjetAll(myEventsReader, "fixedGridRhoFastjetAll");



        TTreeReader myRunsReader("Runs", tmpfile);
        TTreeReaderValue<Long64_t> genEventCount(myRunsReader, "genEventCount");
        TTreeReaderValue<Double_t> genEventSumw(myRunsReader, "genEventSumw");

        
        
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

            sumOfGenWeights += *genWeight;
            genChannelL = 4;
            HTobbBoolL = false;


            //--------------KINEMATICS--------------

            UInt_t tmpnFatJets = *nFatJet;
            



            /*
            //First check that it passes the hbb tagging
            bool hbbTag = *HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02 || *HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2 || *HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4;

            //Hadronic
            bool hadHLT =  (*HLT_PFHT1050 || *HLT_AK8PFJet500 || *HLT_AK8PFJet360_TrimMass30 || *HLT_AK8PFHT750_TrimMass50 || *HLT_AK8PFJet380_TrimMass30 ||
            *HLT_AK8PFJet400_TrimMass30 || *HLT_AK8PFJet420_TrimMass30 ||
            *HLT_AK8PFHT800_TrimMass50 || *HLT_AK8PFHT850_TrimMass50 || *HLT_AK8PFHT900_TrimMass50);
            

            
            //if (!hbbTag) continue;
            //passhbbCtr += 1;
            

            //Now check that it can be sorted into either leptonic, semi-leptonic, || hadronic
            //Leptonic
            
            bool doubleElecHLT =  (*HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL || *HLT_DoubleEle25_CaloIdL_MW || *HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ || *HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL ||  *HLT_DiEle27_WPTightCaloOnly_L1DoubleEG || 
            *HLT_DoubleEle33_CaloIdL_MW || *HLT_DoubleEle25_CaloIdL_MW || *HLT_DoubleEle27_CaloIdL_MW || *HLT_DoublePhoton70);
                
            bool doubleMuonHLT =  (*HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8 || *HLT_TripleMu_10_5_5_DZ || *HLT_TripleMu_12_10_5 || *HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8 || *HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8 || 
            *HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass3p8 || *HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass8);

            bool muonEGHLT = (*HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL || *HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ || *HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ || *HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ ||  // || *HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ || *HLT_Mu8_DiEle12_CaloIdL_TrackIdL_DZ 
            *HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL || *HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL);
            
            //Semi-leptonic
            bool elecHLT = (*HLT_Ele32_WPTight_Gsf || *HLT_Ele115_CaloIdVT_GsfTrkIdT || *HLT_Ele27_WPTight_Gsf || *HLT_Ele28_WPTight_Gsf || 
            *HLT_Ele35_WPTight_Gsf || *HLT_Ele38_WPTight_Gsf || *HLT_Ele40_WPTight_Gsf || *HLT_Ele32_WPTight_Gsf_L1DoubleEG || *HLT_Photon200);

            bool muonHLT = *HLT_IsoMu24 || *HLT_IsoMu27 || *HLT_IsoMu30 || *HLT_Mu50;

            //bool passHLTBool = hbbTag || hadHLT || doubleElecHLT || doubleMuonHLT || muonEGHLT || elecHLT || muonHLT;
            */

            bool passFlagBool = *Flag_goodVertices && *Flag_globalSuperTightHalo2016Filter && *Flag_HBHENoiseFilter && *Flag_HBHENoiseIsoFilter && *Flag_EcalDeadCellTriggerPrimitiveFilter && *Flag_BadPFMuonFilter && *Flag_eeBadScFilter;

            if (!passFlagBool) continue;
            passFlagCtr += 1;
            passFlagWeightedCtr += *genWeight;


            bool passHLTBool = (*HLT_Ele27_WPTight_Gsf || *HLT_Ele115_CaloIdVT_GsfTrkIdT || 
            *HLT_IsoMu27 || *HLT_Mu50 || 
            *HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ || 
            *HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ);
            //std::cout << testPassHLTBool << " " << passHLTBool << "\n";
            if (!passHLTBool) continue;
            passHLTCtr += 1;
            passHLTWeightedCtr += *genWeight;

            





            if (debug){
                std::cout <<"Passed HLT\n";
            }
            

            genWeightL = *genWeight;

            //Check if any fat jets in event
            
            if (tmpnFatJets<=0) continue;
            if (debug){
                std::cout <<"Passed nFJs\n";
            }
            passnFJCtr += 1;
            passnFJWeightedCtr += *genWeight; 

            

            // check if two or more VBF jets in event
            UInt_t tmpnVBFJets = *nJet;
            
            if (tmpnVBFJets < 2) continue;
            if (debug){
                std::cout <<"Passed nJs\n";
            }

            passnVBFCtr += 1;
            passnVBFWeightedCtr += *genWeight; 

            


            //std::cout << evRunOver-1 << "passed\n";
            if (debug){
                std::cout <<"Filling Jets\n";
            }
            nJetL = tmpnVBFJets;
            for (UInt_t nJetItr=0; nJetItr<nJetL;nJetItr++){
                Jet_etaL.push_back(Jet_eta[nJetItr]);
                Jet_ptL.push_back(Jet_pt[nJetItr]);
                Jet_phiL.push_back(Jet_phi[nJetItr]);
                Jet_massL.push_back(Jet_mass[nJetItr]);
                Jet_jetIdL.push_back(Jet_jetId[nJetItr]);
                Jet_btagDeepFlavBL.push_back(Jet_btagDeepFlavB[nJetItr]);
            }

            //Fat jets
            if (debug){
                std::cout <<"Filling FJs\n";
            }
            nFatJetL = tmpnFatJets;
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

                Muon_dxyL.push_back(Muon_dxy[nMuonItr]);
                Muon_dzL.push_back(Muon_dz[nMuonItr]);
                Muon_miniPFRelIso_allL.push_back(Muon_miniPFRelIso_all[nMuonItr]);
                Muon_jetIdxL.push_back(Muon_jetIdx[nMuonItr]);
                Muon_jetRelIsoL.push_back(Muon_jetRelIso[nMuonItr]);
                Muon_mvaTTHL.push_back(Muon_mvaTTH[nMuonItr]);
            }

            fixedGridRhoFastjetAllL = *fixedGridRhoFastjetAll;

            FilteredEventsTree->Fill();

            Jet_etaL.clear();
            Jet_ptL.clear();
            Jet_phiL.clear();
            Jet_massL.clear();
            Jet_jetIdL.clear();
            Jet_btagDeepFlavBL.clear();
            

            FatJet_etaL.clear();
            FatJet_ptL.clear();
            FatJet_phiL.clear();
            FatJet_massL.clear();
            FatJet_jetIdL.clear();
            FatJet_deepTag_HL.clear();
            FatJet_deepTag_ZvsQCDL.clear();
            FatJet_msoftdropL.clear();
            

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

    nEv = evRunOver;
    nEvPass = passHLTCtr;
    evNumTree->Fill();

    std::cout << "evRunOver: " << evRunOver << " -------------------\n";
    std::cout << "passes Flag cut: " << passFlagCtr << " ------------------- " << passFlagWeightedCtr<< "\n";
    std::cout << "passes HLT cut: " << passHLTCtr << " ------------------- " << passHLTWeightedCtr<< "\n";
    std::cout << "passes nFJ cut: " << passnFJCtr << " ------------------- " << passnFJWeightedCtr<< "\n";
    std::cout << "passes nVBF cut: " << passnVBFCtr << " ------------------- " << passnVBFWeightedCtr<< "\n";

    
    std::cout << "sumOfGenWeights: " << sumOfGenWeights << "\n";

    

    outFile->cd();
    evNumTree->Write("",TObject::kOverwrite);
    FilteredEventsTree->Write("",TObject::kOverwrite);

    outFile->Close();
}
