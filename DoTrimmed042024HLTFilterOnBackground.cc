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


void DoTrimmed042024HLTFilterOnBackground(int fileInd, string datasetString,uint yearInd){
    // Open the file. Note that the name of your file outside this class
    // will probably NOT be experiment.root.
    std::cout << "start\n";
    clock_t startt = clock();
    
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

    if (datasetString == "TTToHadronic") TTToHadronicBackground = true;
    if (datasetString == "TTTo2L2Nu") TTTo2L2NuBackground = true;
    if (datasetString == "TTToSemiLeptonic") TTToSemiLeptonicBackground = true;

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

    if (datasetString == "QCDHT50to100") QCDHT50to100Background = true;
    if (datasetString == "QCDHT100to200") QCDHT100to200Background = true;
    if (datasetString == "QCDHT200to300") QCDHT200to300Background = true;
    if (datasetString == "QCDHT300to500") QCDHT300to500Background = true;
    if (datasetString == "QCDHT500to700") QCDHT500to700Background = true;
    if (datasetString == "QCDHT700to1000") QCDHT700to1000Background = true;
    if (datasetString == "QCDHT1000to1500") QCDHT1000to1500Background = true;
    if (datasetString == "QCDHT1500to2000") QCDHT1500to2000Background = true;
    if (datasetString == "QCDHT2000toInf") QCDHT2000toInfBackground = true;


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
    if (datasetString == "ZH_HToBB_ZToBB") ZH_HToBB_ZToBBBackground = true;
    if (datasetString == "ZH_HToBB_ZToNuNu") ZH_HToBB_ZToNuNuBackground = true;
    if (datasetString == "ZH_HToBB_ZToLL") ZH_HToBB_ZToLLBackground = true;
    if (datasetString == "ZH_HToBB_ZToQQ") ZH_HToBB_ZToQQBackground = true;
    if (datasetString == "ggZH_HToBB_ZToBB") ggZH_HToBB_ZToBBBackground = true;
    if (datasetString == "ggZH_HToBB_ZToNuNu") ggZH_HToBB_ZToNuNuBackground = true;
    if (datasetString == "ggZH_HToBB_ZToLL") ggZH_HToBB_ZToLLBackground = true;
    if (datasetString == "ggZH_HToBB_ZToQQ") ggZH_HToBB_ZToQQBackground = true;
    if (datasetString == "EWKZ2Jets_ZToLL") EWKZ2Jets_ZToLLBackground = true;
    if (datasetString == "EWKZ2Jets_ZToNuNu") EWKZ2Jets_ZToNuNuBackground = true;
    if (datasetString == "EWKZ2Jets_ZToQQ") EWKZ2Jets_ZToQQBackground = true;
    if (datasetString == "ZZZ") ZZZBackground = true;

    //Analyzer will run over all files put into fileAr

    std::vector<std::string> fileAr;

    std::string saveName;
    float crossSection;
    bool isBackground;

    ////////////////////////////////GETTING DATASET////////////////////////////////
    ////////////////////////////////GETTING DATASET////////////////////////////////
    ////////////////////////////////GETTING DATASET////////////////////////////////
    ////////////////////////////////GETTING DATASET////////////////////////////////

    std::string strAdd;
    if (scratchDown) strAdd ="/afs/crc.nd.edu/user/d/dlutton/FROM_PANASAS";
    else strAdd ="/scratch365";
    if (yearInd == 0) {
        if (ttHToBBBackground){
            //saveName = "ttHToBB";
            crossSection = 0.5071*0.582;

            saveName = "ttHToBB";
            
            isBackground = true;
            int arrSize = sizeof(ttHToBBBackgroundAr)/sizeof(ttHToBBBackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(ttHToBBBackgroundAr[i]);
            }
            */
            fileAr.push_back(ttHToBBBackgroundAr[fileInd]);
        }
        else if (ttZJetsBackground){
            //saveName = "ttZJets";
            
            crossSection = 0.5407;
            saveName = "ttZJets";
            isBackground = true;
            int arrSize = sizeof(ttZJetsBackgroundAr)/sizeof(ttZJetsBackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(ttZJetsBackgroundAr[i]);
            }
            */
            fileAr.push_back(ttZJetsBackgroundAr[fileInd]);
        }
        else if (ttWJetsBackground){
            
            crossSection = 0.4611;
            saveName = "ttWJets";
            isBackground = true;
            int arrSize = sizeof(ttWJetsBackgroundAr)/sizeof(ttWJetsBackgroundAr[0]);
            fileAr.push_back(ttWJetsBackgroundAr[fileInd]);
        }
        else if (DYBackground){
            //saveName = "DY";
            
            crossSection = 5364;
            saveName = "DY";

            isBackground = true;
            int arrSize = sizeof(DYBackgroundAr)/sizeof(DYBackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(DYBackgroundAr[i]);
            }
            */
            fileAr.push_back(DYBackgroundAr[fileInd]);
        }
        else if (QCDPT170to300Background){
            //saveName = "QCDPT170to300";
            
            crossSection = 103300.0;

            saveName = "QCDPT170to300";
            
            isBackground = true;
            int arrSize = sizeof(QCDPT170to300BackgroundAr)/sizeof(QCDPT170to300BackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(QCDPT170to300BackgroundAr[i]);
            }
            */
            fileAr.push_back(QCDPT170to300BackgroundAr[fileInd]);
        }
        else if (QCDPT300to470Background){
            //saveName = "QCDPT300to470";
            
            crossSection = 6826.0;

            saveName = "QCDPT300to470";
            
            isBackground = true;
            int arrSize = sizeof(QCDPT300to470BackgroundAr)/sizeof(QCDPT300to470BackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(QCDPT300to470BackgroundAr[i]);
            }
            */
            fileAr.push_back(QCDPT300to470BackgroundAr[fileInd]);
        }
        else if (QCDPT470to600Background){
            //saveName = "QCDPT470to600";
            
            crossSection = 552.6;
            
            saveName = "QCDPT470to600";

            isBackground = true;
            int arrSize = sizeof(QCDPT470to600BackgroundAr)/sizeof(QCDPT470to600BackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(QCDPT470to600BackgroundAr[i]);
            }
            */
            fileAr.push_back(QCDPT470to600BackgroundAr[fileInd]);
        }
        else if (QCDPT600to800Background){
            //saveName = "QCDPT600to800";
            
            crossSection = 156.6;

            saveName = "QCDPT600to800";
            
            isBackground = true;
            int arrSize = sizeof(QCDPT600to800BackgroundAr)/sizeof(QCDPT600to800BackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(QCDPT600to800BackgroundAr[i]);
            }
            */
            fileAr.push_back(QCDPT600to800BackgroundAr[fileInd]);
        }
        else if (QCDPT800to1000Background){
            //saveName = "QCDPT800to1000";
            
            crossSection = 26.32;

            saveName = "QCDPT800to1000";
            
            isBackground = true;
            int arrSize = sizeof(QCDPT800to1000BackgroundAr)/sizeof(QCDPT800to1000BackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(QCDPT800to1000BackgroundAr[i]);
            }
            */
            fileAr.push_back(QCDPT800to1000BackgroundAr[fileInd]);
        }
        else if (QCDPT1000to1400Background){
            //saveName = "QCDPT1000to1400";
            
            crossSection = 7.5;

            saveName = "QCDPT1000to1400";
            
            isBackground = true;
            int arrSize = sizeof(QCDPT1000to1400BackgroundAr)/sizeof(QCDPT1000to1400BackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(QCDPT1000to1400BackgroundAr[i]);
            }
            */
            fileAr.push_back(QCDPT1000to1400BackgroundAr[fileInd]);
        }
        else if (QCDPT1400to1800Background){
            //saveName = "QCDPT1400to1800";
            
            crossSection = 0.6479;

            saveName = "QCDPT1400to1800";
            
            isBackground = true;
            int arrSize = sizeof(QCDPT1400to1800BackgroundAr)/sizeof(QCDPT1400to1800BackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(QCDPT1400to1800BackgroundAr[i]);
            }
            */
            fileAr.push_back(QCDPT1400to1800BackgroundAr[fileInd]);
        }
        else if (QCDPT1800to2400Background){
            //saveName = "QCDPT1800to2400";
            
            crossSection = 0.08715;

            saveName = "QCDPT1800to2400";
            
            isBackground = true;
            int arrSize = sizeof(QCDPT1800to2400BackgroundAr)/sizeof(QCDPT1800to2400BackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(QCDPT1800to2400BackgroundAr[i]);
            }
            */
            fileAr.push_back(QCDPT1800to2400BackgroundAr[fileInd]);
        }
        else if (QCDPT2400to3200Background){
            //saveName = "QCDPT2400to3200";
            
            crossSection = 0.005242;

            saveName = "QCDPT2400to3200";
            
            isBackground = true;
            int arrSize = sizeof(QCDPT2400to3200BackgroundAr)/sizeof(QCDPT2400to3200BackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(QCDPT2400to3200BackgroundAr[i]);
            }
            */
            fileAr.push_back(QCDPT2400to3200BackgroundAr[fileInd]);
        }
        else if (QCDPT3200toInfBackground){
            //saveName = "QCDPT3200toInf";
            
            crossSection = 0.0001349;

            saveName = "QCDPT3200toInf";
            
            isBackground = true;
            int arrSize = sizeof(QCDPT3200toInfBackgroundAr)/sizeof(QCDPT3200toInfBackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(QCDPT3200toInfBackgroundAr[i]);
            }
            */
            fileAr.push_back(QCDPT3200toInfBackgroundAr[fileInd]);
        }
        else if (QCDHT50to100Background){
            //saveName = "QCDHT50to100";
            
            crossSection = 187700000.;

            saveName = "QCDHT50to100";
            
            isBackground = true;
            int arrSize = sizeof(QCDHT50to100BackgroundAr)/sizeof(QCDHT50to100BackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(QCDHT50to100BackgroundAr[i]);
            }
            */
            fileAr.push_back(QCDHT50to100BackgroundAr[fileInd]);
        }
        else if (QCDHT100to200Background){
            //saveName = "QCDHT100to200";
            
            crossSection = 23640000.0;

            saveName = "QCDHT100to200";
            
            isBackground = true;
            int arrSize = sizeof(QCDHT100to200BackgroundAr)/sizeof(QCDHT100to200BackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(QCDHT100to200BackgroundAr[i]);
            }
            */
            fileAr.push_back(QCDHT100to200BackgroundAr[fileInd]);
        }
        else if (QCDHT200to300Background){
            //saveName = "QCDHT200to300";
            
            crossSection = 1546000.0;

            saveName = "QCDHT200to300";
            
            isBackground = true;
            int arrSize = sizeof(QCDHT200to300BackgroundAr)/sizeof(QCDHT200to300BackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(QCDHT200to300BackgroundAr[i]);
            }
            */
            fileAr.push_back(QCDHT200to300BackgroundAr[fileInd]);
        }
        else if (QCDHT300to500Background){
            //saveName = "QCDHT300to500";
            
            crossSection = 321600.0;

            saveName = "QCDHT300to500";
            
            isBackground = true;
            int arrSize = sizeof(QCDHT300to500BackgroundAr)/sizeof(QCDHT300to500BackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(QCDHT300to500BackgroundAr[i]);
            }
            */
            fileAr.push_back(QCDHT300to500BackgroundAr[fileInd]);
        }
        else if (QCDHT500to700Background){
            //saveName = "QCDHT500to700";
            
            crossSection = 30980.0;

            saveName = "QCDHT500to700";
            
            isBackground = true;
            int arrSize = sizeof(QCDHT500to700BackgroundAr)/sizeof(QCDHT500to700BackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(QCDHT500to700BackgroundAr[i]);
            }
            */
            fileAr.push_back(QCDHT500to700BackgroundAr[fileInd]);
        }
        else if (QCDHT700to1000Background){
            //saveName = "QCDHT700to1000";
            
            crossSection = 6364.0;

            saveName = "QCDHT700to1000";
            
            isBackground = true;
            int arrSize = sizeof(QCDHT700to1000BackgroundAr)/sizeof(QCDHT700to1000BackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(QCDHT700to1000BackgroundAr[i]);
            }
            */
            fileAr.push_back(QCDHT700to1000BackgroundAr[fileInd]);
        }
        else if (QCDHT1000to1500Background){
            //saveName = "QCDHT1000to1500";
            
            crossSection = 1117.0;

            saveName = "QCDHT1000to1500";
            
            isBackground = true;
            int arrSize = sizeof(QCDHT1000to1500BackgroundAr)/sizeof(QCDHT1000to1500BackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(QCDHT1000to1500BackgroundAr[i]);
            }
            */
            fileAr.push_back(QCDHT1000to1500BackgroundAr[fileInd]);
        }
        else if (QCDHT1500to2000Background){
            //saveName = "QCDHT1500to2000";
            
            crossSection = 108.4;

            saveName = "QCDHT1500to2000";
            
            isBackground = true;
            int arrSize = sizeof(QCDHT1500to2000BackgroundAr)/sizeof(QCDHT1500to2000BackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(QCDHT1500to2000BackgroundAr[i]);
            }
            */
            fileAr.push_back(QCDHT1500to2000BackgroundAr[fileInd]);
        }
        else if (QCDHT2000toInfBackground){
            //saveName = "QCDHT2000toInf";
            
            crossSection = 22.36;

            saveName = "QCDHT2000toInf";
            
            isBackground = true;
            int arrSize = sizeof(QCDHT2000toInfBackgroundAr)/sizeof(QCDHT2000toInfBackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(QCDHT2000toInfBackgroundAr[i]);
            }
            */
            fileAr.push_back(QCDHT2000toInfBackgroundAr[fileInd]);
        }
        else if (TTJetsBackground){
            //saveName = "";
            
            crossSection = 722.8;

            saveName = "TTJets";
            
            isBackground = true;
            int arrSize = sizeof(TTJetsBackgroundAr)/sizeof(TTJetsBackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(TTJetsBackgroundAr[i]);
            }
            */
            fileAr.push_back(TTJetsBackgroundAr[fileInd]);
        }
        else if (TTToHadronicBackground){
            //saveName = "";
            
            crossSection = 377.96;

            saveName = "TTJetsHadronic";
            
            isBackground = true;
            int arrSize = sizeof(TTJetsHadronicBackgroundAr)/sizeof(TTJetsHadronicBackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(TTJetsHadronicBackgroundAr[i]);
            }
            */
            fileAr.push_back(TTJetsHadronicBackgroundAr[fileInd]);
        }
        else if (TTToSemiLeptonicBackground){
            //saveName = "";
            
            crossSection = 365.346;

            saveName = "TTJetsSemiLeptonic";
            
            isBackground = true;
            int arrSize = sizeof(TTJetsSemiLeptonicBackgroundAr)/sizeof(TTJetsSemiLeptonicBackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(TTJetsSemiLeptonicBackgroundAr[i]);
            }
            */
            fileAr.push_back(TTJetsSemiLeptonicBackgroundAr[fileInd]);
        }
        else if (TTTo2L2NuBackground){
            //saveName = "";
            
            crossSection = 88.29;

            saveName = "TTJets2L2Nu";
            
            isBackground = true;
            int arrSize = sizeof(TTJets2L2NuBackgroundAr)/sizeof(TTJets2L2NuBackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(TTJets2L2NuBackgroundAr[i]);
            }
            */
            fileAr.push_back(TTJets2L2NuBackgroundAr[fileInd]);
        }
        else if (ST_s_ChannelBackground){
            //saveName = "";
            
            crossSection = 3.74;

            saveName = "ST_s_Channel";
            
            isBackground = true;
            int arrSize = sizeof(ST_s_ChannelBackgroundAr)/sizeof(ST_s_ChannelBackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(ST_s_ChannelBackgroundAr[i]);
            }
            */
            fileAr.push_back(ST_s_ChannelBackgroundAr[fileInd]);
        }
        else if (ST_t_ChannelAntiTopBackground){
            //saveName = "";
            
            crossSection = 69.09;

            saveName = "ST_t_ChannelAntiTop";
            
            isBackground = true;
            int arrSize = sizeof(ST_t_ChannelAntiTopBackgroundAr)/sizeof(ST_t_ChannelAntiTopBackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(ST_t_ChannelAntiTopBackgroundAr[i]);
            }
            */
            fileAr.push_back(ST_t_ChannelAntiTopBackgroundAr[fileInd]);
        }
        else if (ST_t_ChannelTopBackground){
            //saveName = "";
            
            crossSection = 115.3;

            saveName = "ST_t_ChannelTop";
            
            isBackground = true;
            int arrSize = sizeof(ST_t_ChannelTopBackgroundAr)/sizeof(ST_t_ChannelTopBackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(ST_t_ChannelTopBackgroundAr[i]);
            }
            */
            fileAr.push_back(ST_t_ChannelTopBackgroundAr[fileInd]);
        }
        else if (ZZBackground){
            //saveName = "";
            
            crossSection = 12.17;

            saveName = "ZZ";
            
            isBackground = true;
            int arrSize = sizeof(ZZBackgroundAr)/sizeof(ZZBackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(ZZBackgroundAr[i]);
            }
            */
            fileAr.push_back(ZZBackgroundAr[fileInd]);
        }
        else if (WWBackground){
            //saveName = "";
            
            crossSection = 75.95;

            saveName = "WW";
            
            isBackground = true;
            int arrSize = sizeof(WWBackgroundAr)/sizeof(WWBackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(WWBackgroundAr[i]);
            }
            */
            fileAr.push_back(WWBackgroundAr[fileInd]);
        }
        else if (WZBackground){
            //saveName = "";
            
            crossSection = 27.59;

            saveName = "WZ";
            
            isBackground = true;
            int arrSize = sizeof(WZBackgroundAr)/sizeof(WZBackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(WZBackgroundAr[i]);
            }
            */
            fileAr.push_back(WZBackgroundAr[fileInd]);
        }
        else if (TTbb_TTToHadronicBackground){
            //saveName = "QCDPT3200toInf";
            
            crossSection = 5.5;

            saveName = "TTbb_TTToHadronic";
            
            isBackground = true;
            int arrSize = sizeof(TTbb_TTToHadronicBackgroundAr)/sizeof(TTbb_TTToHadronicBackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(TTbb_TTToHadronicBackgroundAr[i]);
            }
            */
            fileAr.push_back(TTbb_TTToHadronicBackgroundAr[fileInd]);
        }
        else if (TTbb_TTTo2L2NuBackground){
            //saveName = "";
            
            crossSection = 2.9;

            saveName = "TTbb_TTTo2L2Nu";
            
            isBackground = true;
            int arrSize = sizeof(TTbb_TTTo2L2NuBackgroundAr)/sizeof(TTbb_TTTo2L2NuBackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(TTbb_TTTo2L2NuBackgroundAr[i]);
            }
            */
            fileAr.push_back(TTbb_TTTo2L2NuBackgroundAr[fileInd]);
        }
        else if (TTbb_TTToSemiLeptonicBackground){
            //saveName = "";
            
            crossSection = 4.7;

            saveName = "TTbb_TTToSemiLeptonic";
            
            isBackground = true;
            int arrSize = sizeof(TTbb_TTToSemiLeptonicBackgroundAr)/sizeof(TTbb_TTToSemiLeptonicBackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(TTbb_TTToSemiLeptonicBackgroundAr[i]);
            }
            */
            fileAr.push_back(TTbb_TTToSemiLeptonicBackgroundAr[fileInd]);
        }
        else if (DYM10To50Background){
            //datasetType = 50;
            saveName = "DYM10To50";
            
            int arrSize = sizeof(DYM10To50BackgroundAr)/sizeof(DYM10To50BackgroundAr[0]);
            fileAr.push_back(DYM10To50BackgroundAr[fileInd]);
        }
        else if (ST_tW_antitopBackground){
            //datasetType = 51;
            saveName = "ST_tW_antitop";
            
            int arrSize = sizeof(ST_tW_antitopBackgroundAr)/sizeof(ST_tW_antitopBackgroundAr[0]);
            fileAr.push_back(ST_tW_antitopBackgroundAr[fileInd]);
        }
        else if (ST_tW_topBackground){
            //datasetType = 52;
            saveName = "ST_tW_top";
            
            int arrSize = sizeof(ST_tW_topBackgroundAr)/sizeof(ST_tW_topBackgroundAr[0]);
            fileAr.push_back(ST_tW_topBackgroundAr[fileInd]);
        }
        else if (EWKWMinus2Jets_WToLNuBackground){
            //datasetType = 53;
            saveName = "EWKWMinus2Jets_WToLNu";
            
            int arrSize = sizeof(EWKWMinus2Jets_WToLNuBackgroundAr)/sizeof(EWKWMinus2Jets_WToLNuBackgroundAr[0]);
            fileAr.push_back(EWKWMinus2Jets_WToLNuBackgroundAr[fileInd]);
        }
        else if (EWKWMinus2Jets_WToQQBackground){
            //datasetType = 54;
            saveName = "EWKWMinus2Jets_WToQQ";
            
            int arrSize = sizeof(EWKWMinus2Jets_WToQQBackgroundAr)/sizeof(EWKWMinus2Jets_WToQQBackgroundAr[0]);
            fileAr.push_back(EWKWMinus2Jets_WToQQBackgroundAr[fileInd]);
        }
        else if (EWKWPlus2Jets_WToLNuBackground){
            //datasetType = 55;
            saveName = "EWKWPlus2Jets_WToLNu";
            
            int arrSize = sizeof(EWKWPlus2Jets_WToLNuBackgroundAr)/sizeof(EWKWPlus2Jets_WToLNuBackgroundAr[0]);
            fileAr.push_back(EWKWPlus2Jets_WToLNuBackgroundAr[fileInd]);
        }
        else if (EWKWPlus2Jets_WToQQBackground){
            //datasetType = 56;
            saveName = "EWKWPlus2Jets_WToQQ";
            
            int arrSize = sizeof(EWKWPlus2Jets_WToQQBackgroundAr)/sizeof(EWKWPlus2Jets_WToQQBackgroundAr[0]);
            fileAr.push_back(EWKWPlus2Jets_WToQQBackgroundAr[fileInd]);
        }
        else if (VHToNonbbBackground){
            //datasetType = 57;
            saveName = "VHToNonbb";
            
            int arrSize = sizeof(VHToNonbbBackgroundAr)/sizeof(VHToNonbbBackgroundAr[0]);
            fileAr.push_back(VHToNonbbBackgroundAr[fileInd]);
        }
        else if (WminusH_HToBB_WToLNuBackground){
            //datasetType = 58;
            saveName = "WminusH_HToBB_WToLNu";
            
            int arrSize = sizeof(WminusH_HToBB_WToLNuBackgroundAr)/sizeof(WminusH_HToBB_WToLNuBackgroundAr[0]);
            fileAr.push_back(WminusH_HToBB_WToLNuBackgroundAr[fileInd]);
        }
        else if (WminusH_HToBB_WToQQBackground){
            //datasetType = 59;
            saveName = "WminusH_HToBB_WToQQ";
            
            int arrSize = sizeof(WminusH_HToBB_WToQQBackgroundAr)/sizeof(WminusH_HToBB_WToQQBackgroundAr[0]);
            fileAr.push_back(WminusH_HToBB_WToQQBackgroundAr[fileInd]);
        }
        else if (WplusH_HToBB_WToLNuBackground){
            //datasetType = 60;
            saveName = "WplusH_HToBB_WToLNu";
            
            int arrSize = sizeof(WplusH_HToBB_WToLNuBackgroundAr)/sizeof(WplusH_HToBB_WToLNuBackgroundAr[0]);
            fileAr.push_back(WplusH_HToBB_WToLNuBackgroundAr[fileInd]);
        }
        else if (WplusH_HToBB_WToQQBackground){
            //datasetType = 61;
            saveName = "WplusH_HToBB_WToQQ";
            
            int arrSize = sizeof(WplusH_HToBB_WToQQBackgroundAr)/sizeof(WplusH_HToBB_WToQQBackgroundAr[0]);
            fileAr.push_back(WplusH_HToBB_WToQQBackgroundAr[fileInd]);
        }
        else if (WJetsToLNuBackground){
            //datasetType = 62;
            saveName = "WJetsToLNu";
            
            int arrSize = sizeof(WJetsToLNuBackgroundAr)/sizeof(WJetsToLNuBackgroundAr[0]);
            fileAr.push_back(WJetsToLNuBackgroundAr[fileInd]);
        }
        else if (WWWBackground){
            //datasetType = 63;
            saveName = "WWW";
            
            int arrSize = sizeof(WWWBackgroundAr)/sizeof(WWWBackgroundAr[0]);
            fileAr.push_back(WWWBackgroundAr[fileInd]);
        }
        else if (WWZBackground){
            //datasetType = 64;
            saveName = "WWZ";
            
            int arrSize = sizeof(WWZBackgroundAr)/sizeof(WWZBackgroundAr[0]);
            fileAr.push_back(WWZBackgroundAr[fileInd]);
        }
        else if (WZZBackground){
            //datasetType = 65;
            saveName = "WZZ";
            
            int arrSize = sizeof(WZZBackgroundAr)/sizeof(WZZBackgroundAr[0]);
            fileAr.push_back(WZZBackgroundAr[fileInd]);
        }
        else if (ZH_HToBB_ZToBBBackground){
            //datasetType = 66;
            saveName = "ZH_HToBB_ZToBB";
            
            int arrSize = sizeof(ZH_HToBB_ZToBBBackgroundAr)/sizeof(ZH_HToBB_ZToBBBackgroundAr[0]);
            fileAr.push_back(ZH_HToBB_ZToBBBackgroundAr[fileInd]);
        }
        else if (ZH_HToBB_ZToNuNuBackground){
            //datasetType = 66;
            saveName = "ZH_HToBB_ZToNuNu";
            
            int arrSize = sizeof(ZH_HToBB_ZToNuNuBackgroundAr)/sizeof(ZH_HToBB_ZToNuNuBackgroundAr[0]);
            fileAr.push_back(ZH_HToBB_ZToNuNuBackgroundAr[fileInd]);
        }
        else if (ZH_HToBB_ZToLLBackground){
            //datasetType = 66;
            saveName = "ZH_HToBB_ZToLL";
            
            int arrSize = sizeof(ZH_HToBB_ZToLLBackgroundAr)/sizeof(ZH_HToBB_ZToLLBackgroundAr[0]);
            fileAr.push_back(ZH_HToBB_ZToLLBackgroundAr[fileInd]);
        }
        else if (ZH_HToBB_ZToQQBackground){
            //datasetType = 67;
            saveName = "ZH_HToBB_ZToQQ";
            
            int arrSize = sizeof(ZH_HToBB_ZToQQBackgroundAr)/sizeof(ZH_HToBB_ZToQQBackgroundAr[0]);
            fileAr.push_back(ZH_HToBB_ZToQQBackgroundAr[fileInd]);
        }
        else if (ggZH_HToBB_ZToBBBackground){
            //datasetType = 68;
            saveName = "ggZH_HToBB_ZToBB";
            
            int arrSize = sizeof(ggZH_HToBB_ZToBBBackgroundAr)/sizeof(ggZH_HToBB_ZToBBBackgroundAr[0]);
            fileAr.push_back(ggZH_HToBB_ZToBBBackgroundAr[fileInd]);
        }
        else if (ggZH_HToBB_ZToNuNuBackground){
            //datasetType = 68;
            saveName = "ggZH_HToBB_ZToNuNu";
            
            int arrSize = sizeof(ggZH_HToBB_ZToNuNuBackgroundAr)/sizeof(ggZH_HToBB_ZToNuNuBackgroundAr[0]);
            fileAr.push_back(ggZH_HToBB_ZToNuNuBackgroundAr[fileInd]);
        }
        else if (ggZH_HToBB_ZToLLBackground){
            //datasetType = 68;
            saveName = "ggZH_HToBB_ZToLL";
            
            int arrSize = sizeof(ggZH_HToBB_ZToLLBackgroundAr)/sizeof(ggZH_HToBB_ZToLLBackgroundAr[0]);
            fileAr.push_back(ggZH_HToBB_ZToLLBackgroundAr[fileInd]);
        }
        else if (ggZH_HToBB_ZToQQBackground){
            //datasetType = 69;
            saveName = "ggZH_HToBB_ZToQQ";
            
            int arrSize = sizeof(ggZH_HToBB_ZToQQBackgroundAr)/sizeof(ggZH_HToBB_ZToQQBackgroundAr[0]);
            fileAr.push_back(ggZH_HToBB_ZToQQBackgroundAr[fileInd]);
        }
        else if (EWKZ2Jets_ZToLLBackground){
            //datasetType = 70;
            saveName = "EWKZ2Jets_ZToLL";
            
            int arrSize = sizeof(EWKZ2Jets_ZToLLBackgroundAr)/sizeof(EWKZ2Jets_ZToLLBackgroundAr[0]);
            fileAr.push_back(EWKZ2Jets_ZToLLBackgroundAr[fileInd]);
        }
        else if (EWKZ2Jets_ZToNuNuBackground){
            //datasetType = 71;
            saveName = "EWKZ2Jets_ZToNuNu";
            
            int arrSize = sizeof(EWKZ2Jets_ZToNuNuBackgroundAr)/sizeof(EWKZ2Jets_ZToNuNuBackgroundAr[0]);
            fileAr.push_back(EWKZ2Jets_ZToNuNuBackgroundAr[fileInd]);
        }
        else if (EWKZ2Jets_ZToQQBackground){
            //datasetType = 72;
            saveName = "EWKZ2Jets_ZToQQ";
            
            int arrSize = sizeof(EWKZ2Jets_ZToQQBackgroundAr)/sizeof(EWKZ2Jets_ZToQQBackgroundAr[0]);
            fileAr.push_back(EWKZ2Jets_ZToQQBackgroundAr[fileInd]);
        }
        else if (ZZZBackground){
            //datasetType = 73;
            saveName = "ZZZ";
            
            int arrSize = sizeof(ZZZBackgroundAr)/sizeof(ZZZBackgroundAr[0]);
            fileAr.push_back(ZZZBackgroundAr[fileInd]);
        }
        else if (testRun){
            saveName = "testRun";
            fileAr.push_back("./unweighted_eventspphzzjjQCD0SMHLOOP0NPE1NPcHWE1QEDE5ResMasAllVer100Ev10080Seed_0p999cHW100GeVIMJetCut_200.root");
            
            isBackground = false;
            
        }
        else if (LaraTest){
            saveName = "LaraTest";
            fileAr.push_back("/scratch365/dlutton/NanoAODFiles/pp_hwpwmjj_EFT_VBF_chw_09999000_250k.root");
        }
        else{
            std::cout << "ERROR. NO INPUT DATASET NAME GIVEN\n";
        }
    }
    else if (yearInd == 1){
        if (ttHToBBBackground){
            //saveName = "ttHToBB";
            crossSection = 0.5071*0.582;

            saveName = "ttHToBB";
            
            isBackground = true;
            int arrSize = sizeof(ttHToBBY17BackgroundAr)/sizeof(ttHToBBY17BackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(ttHToBBY17BackgroundAr[i]);
            }
            */
            fileAr.push_back(ttHToBBY17BackgroundAr[fileInd]);
        }
        else if (ttZJetsBackground){
            //saveName = "ttZJets";
            
            crossSection = 0.5407;
            saveName = "ttZJets";
            isBackground = true;
            int arrSize = sizeof(ttZJetsY17BackgroundAr)/sizeof(ttZJetsY17BackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(ttZJetsY17BackgroundAr[i]);
            }
            */
            fileAr.push_back(ttZJetsY17BackgroundAr[fileInd]);
        }
        else if (ttWJetsBackground){
            
            crossSection = 0.4611;
            saveName = "ttWJets";
            isBackground = true;
            int arrSize = sizeof(ttWJetsY17BackgroundAr)/sizeof(ttWJetsY17BackgroundAr[0]);
            fileAr.push_back(ttWJetsY17BackgroundAr[fileInd]);
        }
        else if (DYBackground){
            //saveName = "DY";
            
            crossSection = 5364;
            saveName = "DY";

            isBackground = true;
            int arrSize = sizeof(DYY17BackgroundAr)/sizeof(DYY17BackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(DYY17BackgroundAr[i]);
            }
            */
            fileAr.push_back(DYY17BackgroundAr[fileInd]);
        }
        else if (QCDPT170to300Background){
            //saveName = "QCDPT170to300";
            
            crossSection = 103300.0;

            saveName = "QCDPT170to300";
            
            isBackground = true;
            int arrSize = sizeof(QCDPT170to300Y17BackgroundAr)/sizeof(QCDPT170to300Y17BackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(QCDPT170to300Y17BackgroundAr[i]);
            }
            */
            fileAr.push_back(QCDPT170to300Y17BackgroundAr[fileInd]);
        }
        else if (QCDPT300to470Background){
            //saveName = "QCDPT300to470";
            
            crossSection = 6826.0;

            saveName = "QCDPT300to470";
            
            isBackground = true;
            int arrSize = sizeof(QCDPT300to470Y17BackgroundAr)/sizeof(QCDPT300to470Y17BackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(QCDPT300to470Y17BackgroundAr[i]);
            }
            */
            fileAr.push_back(QCDPT300to470Y17BackgroundAr[fileInd]);
        }
        else if (QCDPT470to600Background){
            //saveName = "QCDPT470to600";
            
            crossSection = 552.6;
            
            saveName = "QCDPT470to600";

            isBackground = true;
            int arrSize = sizeof(QCDPT470to600Y17BackgroundAr)/sizeof(QCDPT470to600Y17BackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(QCDPT470to600Y17BackgroundAr[i]);
            }
            */
            fileAr.push_back(QCDPT470to600Y17BackgroundAr[fileInd]);
        }
        else if (QCDPT600to800Background){
            //saveName = "QCDPT600to800";
            
            crossSection = 156.6;

            saveName = "QCDPT600to800";
            
            isBackground = true;
            int arrSize = sizeof(QCDPT600to800Y17BackgroundAr)/sizeof(QCDPT600to800Y17BackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(QCDPT600to800Y17BackgroundAr[i]);
            }
            */
            fileAr.push_back(QCDPT600to800Y17BackgroundAr[fileInd]);
        }
        else if (QCDPT800to1000Background){
            //saveName = "QCDPT800to1000";
            
            crossSection = 26.32;

            saveName = "QCDPT800to1000";
            
            isBackground = true;
            int arrSize = sizeof(QCDPT800to1000Y17BackgroundAr)/sizeof(QCDPT800to1000Y17BackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(QCDPT800to1000Y17BackgroundAr[i]);
            }
            */
            fileAr.push_back(QCDPT800to1000Y17BackgroundAr[fileInd]);
        }
        else if (QCDPT1000to1400Background){
            //saveName = "QCDPT1000to1400";
            
            crossSection = 7.5;

            saveName = "QCDPT1000to1400";
            
            isBackground = true;
            int arrSize = sizeof(QCDPT1000to1400Y17BackgroundAr)/sizeof(QCDPT1000to1400Y17BackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(QCDPT1000to1400Y17BackgroundAr[i]);
            }
            */
            fileAr.push_back(QCDPT1000to1400Y17BackgroundAr[fileInd]);
        }
        else if (QCDPT1400to1800Background){
            //saveName = "QCDPT1400to1800";
            
            crossSection = 0.6479;

            saveName = "QCDPT1400to1800";
            
            isBackground = true;
            int arrSize = sizeof(QCDPT1400to1800Y17BackgroundAr)/sizeof(QCDPT1400to1800Y17BackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(QCDPT1400to1800Y17BackgroundAr[i]);
            }
            */
            fileAr.push_back(QCDPT1400to1800Y17BackgroundAr[fileInd]);
        }
        else if (QCDPT1800to2400Background){
            //saveName = "QCDPT1800to2400";
            
            crossSection = 0.08715;

            saveName = "QCDPT1800to2400";
            
            isBackground = true;
            int arrSize = sizeof(QCDPT1800to2400Y17BackgroundAr)/sizeof(QCDPT1800to2400Y17BackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(QCDPT1800to2400Y17BackgroundAr[i]);
            }
            */
            fileAr.push_back(QCDPT1800to2400Y17BackgroundAr[fileInd]);
        }
        else if (QCDPT2400to3200Background){
            //saveName = "QCDPT2400to3200";
            
            crossSection = 0.005242;

            saveName = "QCDPT2400to3200";
            
            isBackground = true;
            int arrSize = sizeof(QCDPT2400to3200Y17BackgroundAr)/sizeof(QCDPT2400to3200Y17BackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(QCDPT2400to3200Y17BackgroundAr[i]);
            }
            */
            fileAr.push_back(QCDPT2400to3200Y17BackgroundAr[fileInd]);
        }
        else if (QCDPT3200toInfBackground){
            //saveName = "QCDPT3200toInf";
            
            crossSection = 0.0001349;

            saveName = "QCDPT3200toInf";
            
            isBackground = true;
            int arrSize = sizeof(QCDPT3200toInfY17BackgroundAr)/sizeof(QCDPT3200toInfY17BackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(QCDPT3200toInfY17BackgroundAr[i]);
            }
            */
            fileAr.push_back(QCDPT3200toInfY17BackgroundAr[fileInd]);
        }
        else if (QCDHT50to100Background){
            //saveName = "QCDHT50to100";
            
            crossSection = 187700000.;

            saveName = "QCDHT50to100";
            
            isBackground = true;
            int arrSize = sizeof(QCDHT50to100Y17BackgroundAr)/sizeof(QCDHT50to100Y17BackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(QCDHT50to100Y17BackgroundAr[i]);
            }
            */
            fileAr.push_back(QCDHT50to100Y17BackgroundAr[fileInd]);
        }
        else if (QCDHT100to200Background){
            //saveName = "QCDHT100to200";
            
            crossSection = 23640000.0;

            saveName = "QCDHT100to200";
            
            isBackground = true;
            int arrSize = sizeof(QCDHT100to200Y17BackgroundAr)/sizeof(QCDHT100to200Y17BackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(QCDHT100to200Y17BackgroundAr[i]);
            }
            */
            fileAr.push_back(QCDHT100to200Y17BackgroundAr[fileInd]);
        }
        else if (QCDHT200to300Background){
            //saveName = "QCDHT200to300";
            
            crossSection = 1546000.0;

            saveName = "QCDHT200to300";
            
            isBackground = true;
            int arrSize = sizeof(QCDHT200to300Y17BackgroundAr)/sizeof(QCDHT200to300Y17BackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(QCDHT200to300Y17BackgroundAr[i]);
            }
            */
            fileAr.push_back(QCDHT200to300Y17BackgroundAr[fileInd]);
        }
        else if (QCDHT300to500Background){
            //saveName = "QCDHT300to500";
            
            crossSection = 321600.0;

            saveName = "QCDHT300to500";
            
            isBackground = true;
            int arrSize = sizeof(QCDHT300to500Y17BackgroundAr)/sizeof(QCDHT300to500Y17BackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(QCDHT300to500Y17BackgroundAr[i]);
            }
            */
            fileAr.push_back(QCDHT300to500Y17BackgroundAr[fileInd]);
        }
        else if (QCDHT500to700Background){
            //saveName = "QCDHT500to700";
            
            crossSection = 30980.0;

            saveName = "QCDHT500to700";
            
            isBackground = true;
            int arrSize = sizeof(QCDHT500to700Y17BackgroundAr)/sizeof(QCDHT500to700Y17BackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(QCDHT500to700Y17BackgroundAr[i]);
            }
            */
            fileAr.push_back(QCDHT500to700Y17BackgroundAr[fileInd]);
        }
        else if (QCDHT700to1000Background){
            //saveName = "QCDHT700to1000";
            
            crossSection = 6364.0;

            saveName = "QCDHT700to1000";
            
            isBackground = true;
            int arrSize = sizeof(QCDHT700to1000Y17BackgroundAr)/sizeof(QCDHT700to1000Y17BackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(QCDHT700to1000Y17BackgroundAr[i]);
            }
            */
            fileAr.push_back(QCDHT700to1000Y17BackgroundAr[fileInd]);
        }
        else if (QCDHT1000to1500Background){
            //saveName = "QCDHT1000to1500";
            
            crossSection = 1117.0;

            saveName = "QCDHT1000to1500";
            
            isBackground = true;
            int arrSize = sizeof(QCDHT1000to1500Y17BackgroundAr)/sizeof(QCDHT1000to1500Y17BackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(QCDHT1000to1500Y17BackgroundAr[i]);
            }
            */
            fileAr.push_back(QCDHT1000to1500Y17BackgroundAr[fileInd]);
        }
        else if (QCDHT1500to2000Background){
            //saveName = "QCDHT1500to2000";
            
            crossSection = 108.4;

            saveName = "QCDHT1500to2000";
            
            isBackground = true;
            int arrSize = sizeof(QCDHT1500to2000Y17BackgroundAr)/sizeof(QCDHT1500to2000Y17BackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(QCDHT1500to2000Y17BackgroundAr[i]);
            }
            */
            fileAr.push_back(QCDHT1500to2000Y17BackgroundAr[fileInd]);
        }
        else if (QCDHT2000toInfBackground){
            //saveName = "QCDHT2000toInf";
            
            crossSection = 22.36;

            saveName = "QCDHT2000toInf";
            
            isBackground = true;
            int arrSize = sizeof(QCDHT2000toInfY17BackgroundAr)/sizeof(QCDHT2000toInfY17BackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(QCDHT2000toInfY17BackgroundAr[i]);
            }
            */
            fileAr.push_back(QCDHT2000toInfY17BackgroundAr[fileInd]);
        }
        else if (TTJetsBackground){
            //saveName = "";
            
            crossSection = 722.8;

            saveName = "TTJets";
            
            isBackground = true;
            int arrSize = sizeof(TTJetsY17BackgroundAr)/sizeof(TTJetsY17BackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(TTJetsY17BackgroundAr[i]);
            }
            */
            fileAr.push_back(TTJetsY17BackgroundAr[fileInd]);
        }
        else if (TTToHadronicBackground){
            //saveName = "";
            
            crossSection = 377.96;

            saveName = "TTJetsHadronic";
            
            isBackground = true;
            int arrSize = sizeof(TTJetsHadronicY17BackgroundAr)/sizeof(TTJetsHadronicY17BackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(TTJetsHadronicY17BackgroundAr[i]);
            }
            */
            fileAr.push_back(TTJetsHadronicY17BackgroundAr[fileInd]);
        }
        else if (TTToSemiLeptonicBackground){
            //saveName = "";
            
            crossSection = 365.346;

            saveName = "TTJetsSemiLeptonic";
            
            isBackground = true;
            int arrSize = sizeof(TTJetsSemiLeptonicY17BackgroundAr)/sizeof(TTJetsSemiLeptonicY17BackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(TTJetsSemiLeptonicY17BackgroundAr[i]);
            }
            */
            fileAr.push_back(TTJetsSemiLeptonicY17BackgroundAr[fileInd]);
        }
        else if (TTTo2L2NuBackground){
            //saveName = "";
            
            crossSection = 88.29;

            saveName = "TTJets2L2Nu";
            
            isBackground = true;
            int arrSize = sizeof(TTJets2L2NuY17BackgroundAr)/sizeof(TTJets2L2NuY17BackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(TTJets2L2NuY17BackgroundAr[i]);
            }
            */
            fileAr.push_back(TTJets2L2NuY17BackgroundAr[fileInd]);
        }
        else if (ST_s_ChannelBackground){
            //saveName = "";
            
            crossSection = 3.74;

            saveName = "ST_s_Channel";
            
            isBackground = true;
            int arrSize = sizeof(ST_s_ChannelY17BackgroundAr)/sizeof(ST_s_ChannelY17BackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(ST_s_ChannelY17BackgroundAr[i]);
            }
            */
            fileAr.push_back(ST_s_ChannelY17BackgroundAr[fileInd]);
        }
        else if (ST_t_ChannelAntiTopBackground){
            //saveName = "";
            
            crossSection = 69.09;

            saveName = "ST_t_ChannelAntiTop";
            
            isBackground = true;
            int arrSize = sizeof(ST_t_ChannelAntiTopY17BackgroundAr)/sizeof(ST_t_ChannelAntiTopY17BackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(ST_t_ChannelAntiTopY17BackgroundAr[i]);
            }
            */
            fileAr.push_back(ST_t_ChannelAntiTopY17BackgroundAr[fileInd]);
        }
        else if (ST_t_ChannelTopBackground){
            //saveName = "";
            
            crossSection = 115.3;

            saveName = "ST_t_ChannelTop";
            
            isBackground = true;
            int arrSize = sizeof(ST_t_ChannelTopY17BackgroundAr)/sizeof(ST_t_ChannelTopY17BackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(ST_t_ChannelTopY17BackgroundAr[i]);
            }
            */
            fileAr.push_back(ST_t_ChannelTopY17BackgroundAr[fileInd]);
        }
        else if (ZZBackground){
            //saveName = "";
            
            crossSection = 12.17;

            saveName = "ZZ";
            
            isBackground = true;
            int arrSize = sizeof(ZZY17BackgroundAr)/sizeof(ZZY17BackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(ZZY17BackgroundAr[i]);
            }
            */
            fileAr.push_back(ZZY17BackgroundAr[fileInd]);
        }
        else if (WWBackground){
            //saveName = "";
            
            crossSection = 75.95;

            saveName = "WW";
            
            isBackground = true;
            int arrSize = sizeof(WWY17BackgroundAr)/sizeof(WWY17BackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(WWY17BackgroundAr[i]);
            }
            */
            fileAr.push_back(WWY17BackgroundAr[fileInd]);
        }
        else if (WZBackground){
            //saveName = "";
            
            crossSection = 27.59;

            saveName = "WZ";
            
            isBackground = true;
            int arrSize = sizeof(WZY17BackgroundAr)/sizeof(WZY17BackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(WZY17BackgroundAr[i]);
            }
            */
            fileAr.push_back(WZY17BackgroundAr[fileInd]);
        }
        else if (TTbb_TTToHadronicBackground){
            //saveName = "QCDPT3200toInf";
            
            crossSection = 5.5;

            saveName = "TTbb_TTToHadronic";
            
            isBackground = true;
            int arrSize = sizeof(TTbb_TTToHadronicY17BackgroundAr)/sizeof(TTbb_TTToHadronicY17BackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(TTbb_TTToHadronicY17BackgroundAr[i]);
            }
            */
            fileAr.push_back(TTbb_TTToHadronicY17BackgroundAr[fileInd]);
        }
        else if (TTbb_TTTo2L2NuBackground){
            //saveName = "";
            
            crossSection = 2.9;

            saveName = "TTbb_TTTo2L2Nu";
            
            isBackground = true;
            int arrSize = sizeof(TTbb_TTTo2L2NuY17BackgroundAr)/sizeof(TTbb_TTTo2L2NuY17BackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(TTbb_TTTo2L2NuY17BackgroundAr[i]);
            }
            */
            fileAr.push_back(TTbb_TTTo2L2NuY17BackgroundAr[fileInd]);
        }
        else if (TTbb_TTToSemiLeptonicBackground){
            //saveName = "";
            
            crossSection = 4.7;

            saveName = "TTbb_TTToSemiLeptonic";
            
            isBackground = true;
            int arrSize = sizeof(TTbb_TTToSemiLeptonicY17BackgroundAr)/sizeof(TTbb_TTToSemiLeptonicY17BackgroundAr[0]);
            /*
            for (int i=0; i<arrSize; i++){
                fileAr.push_back(TTbb_TTToSemiLeptonicY17BackgroundAr[i]);
            }
            */
            fileAr.push_back(TTbb_TTToSemiLeptonicY17BackgroundAr[fileInd]);
        }
        else if (DYM10To50Background){
            //datasetType = 50;
            saveName = "DYM10To50";
            
            int arrSize = sizeof(DYM10To50Y17BackgroundAr)/sizeof(DYM10To50Y17BackgroundAr[0]);
            fileAr.push_back(DYM10To50Y17BackgroundAr[fileInd]);
        }
        else if (ST_tW_antitopBackground){
            //datasetType = 51;
            saveName = "ST_tW_antitop";
            
            int arrSize = sizeof(ST_tW_antitopY17BackgroundAr)/sizeof(ST_tW_antitopY17BackgroundAr[0]);
            fileAr.push_back(ST_tW_antitopY17BackgroundAr[fileInd]);
        }
        else if (ST_tW_topBackground){
            //datasetType = 52;
            saveName = "ST_tW_top";
            
            int arrSize = sizeof(ST_tW_topY17BackgroundAr)/sizeof(ST_tW_topY17BackgroundAr[0]);
            fileAr.push_back(ST_tW_topY17BackgroundAr[fileInd]);
        }
        else if (EWKWMinus2Jets_WToLNuBackground){
            //datasetType = 53;
            saveName = "EWKWMinus2Jets_WToLNu";
            
            int arrSize = sizeof(EWKWMinus2Jets_WToLNuY17BackgroundAr)/sizeof(EWKWMinus2Jets_WToLNuY17BackgroundAr[0]);
            fileAr.push_back(EWKWMinus2Jets_WToLNuY17BackgroundAr[fileInd]);
        }
        else if (EWKWMinus2Jets_WToQQBackground){
            //datasetType = 54;
            saveName = "EWKWMinus2Jets_WToQQ";
            
            int arrSize = sizeof(EWKWMinus2Jets_WToQQY17BackgroundAr)/sizeof(EWKWMinus2Jets_WToQQY17BackgroundAr[0]);
            fileAr.push_back(EWKWMinus2Jets_WToQQY17BackgroundAr[fileInd]);
        }
        else if (EWKWPlus2Jets_WToLNuBackground){
            //datasetType = 55;
            saveName = "EWKWPlus2Jets_WToLNu";
            
            int arrSize = sizeof(EWKWPlus2Jets_WToLNuY17BackgroundAr)/sizeof(EWKWPlus2Jets_WToLNuY17BackgroundAr[0]);
            fileAr.push_back(EWKWPlus2Jets_WToLNuY17BackgroundAr[fileInd]);
        }
        else if (EWKWPlus2Jets_WToQQBackground){
            //datasetType = 56;
            saveName = "EWKWPlus2Jets_WToQQ";
            
            int arrSize = sizeof(EWKWPlus2Jets_WToQQY17BackgroundAr)/sizeof(EWKWPlus2Jets_WToQQY17BackgroundAr[0]);
            fileAr.push_back(EWKWPlus2Jets_WToQQY17BackgroundAr[fileInd]);
        }
        else if (VHToNonbbBackground){
            //datasetType = 57;
            saveName = "VHToNonbb";
            
            int arrSize = sizeof(VHToNonbbY17BackgroundAr)/sizeof(VHToNonbbY17BackgroundAr[0]);
            fileAr.push_back(VHToNonbbY17BackgroundAr[fileInd]);
        }
        else if (WminusH_HToBB_WToLNuBackground){
            //datasetType = 58;
            saveName = "WminusH_HToBB_WToLNu";
            
            int arrSize = sizeof(WminusH_HToBB_WToLNuY17BackgroundAr)/sizeof(WminusH_HToBB_WToLNuY17BackgroundAr[0]);
            fileAr.push_back(WminusH_HToBB_WToLNuY17BackgroundAr[fileInd]);
        }
        else if (WminusH_HToBB_WToQQBackground){
            //datasetType = 59;
            saveName = "WminusH_HToBB_WToQQ";
            
            int arrSize = sizeof(WminusH_HToBB_WToQQY17BackgroundAr)/sizeof(WminusH_HToBB_WToQQY17BackgroundAr[0]);
            fileAr.push_back(WminusH_HToBB_WToQQY17BackgroundAr[fileInd]);
        }
        else if (WplusH_HToBB_WToLNuBackground){
            //datasetType = 60;
            saveName = "WplusH_HToBB_WToLNu";
            
            int arrSize = sizeof(WplusH_HToBB_WToLNuY17BackgroundAr)/sizeof(WplusH_HToBB_WToLNuY17BackgroundAr[0]);
            fileAr.push_back(WplusH_HToBB_WToLNuY17BackgroundAr[fileInd]);
        }
        else if (WplusH_HToBB_WToQQBackground){
            //datasetType = 61;
            saveName = "WplusH_HToBB_WToQQ";
            
            int arrSize = sizeof(WplusH_HToBB_WToQQY17BackgroundAr)/sizeof(WplusH_HToBB_WToQQY17BackgroundAr[0]);
            fileAr.push_back(WplusH_HToBB_WToQQY17BackgroundAr[fileInd]);
        }
        else if (WJetsToLNuBackground){
            //datasetType = 62;
            saveName = "WJetsToLNu";
            
            int arrSize = sizeof(WJetsToLNuY17BackgroundAr)/sizeof(WJetsToLNuY17BackgroundAr[0]);
            fileAr.push_back(WJetsToLNuY17BackgroundAr[fileInd]);
        }
        else if (WWWBackground){
            //datasetType = 63;
            saveName = "WWW";
            
            int arrSize = sizeof(WWWY17BackgroundAr)/sizeof(WWWY17BackgroundAr[0]);
            fileAr.push_back(WWWY17BackgroundAr[fileInd]);
        }
        else if (WWZBackground){
            //datasetType = 64;
            saveName = "WWZ";
            
            int arrSize = sizeof(WWZY17BackgroundAr)/sizeof(WWZY17BackgroundAr[0]);
            fileAr.push_back(WWZY17BackgroundAr[fileInd]);
        }
        else if (WZZBackground){
            //datasetType = 65;
            saveName = "WZZ";
            
            int arrSize = sizeof(WZZY17BackgroundAr)/sizeof(WZZY17BackgroundAr[0]);
            fileAr.push_back(WZZY17BackgroundAr[fileInd]);
        }
        else if (ZH_HToBB_ZToBBBackground){
            //datasetType = 66;
            saveName = "ZH_HToBB_ZToBB";
            
            int arrSize = sizeof(ZH_HToBB_ZToBBY17BackgroundAr)/sizeof(ZH_HToBB_ZToBBY17BackgroundAr[0]);
            fileAr.push_back(ZH_HToBB_ZToBBY17BackgroundAr[fileInd]);
        }
        else if (ZH_HToBB_ZToNuNuBackground){
            //datasetType = 66;
            saveName = "ZH_HToBB_ZToNuNu";
            
            int arrSize = sizeof(ZH_HToBB_ZToNuNuY17BackgroundAr)/sizeof(ZH_HToBB_ZToNuNuY17BackgroundAr[0]);
            fileAr.push_back(ZH_HToBB_ZToNuNuY17BackgroundAr[fileInd]);
        }
        else if (ZH_HToBB_ZToLLBackground){
            //datasetType = 66;
            saveName = "ZH_HToBB_ZToLL";
            
            int arrSize = sizeof(ZH_HToBB_ZToLLY17BackgroundAr)/sizeof(ZH_HToBB_ZToLLY17BackgroundAr[0]);
            fileAr.push_back(ZH_HToBB_ZToLLY17BackgroundAr[fileInd]);
        }
        else if (ZH_HToBB_ZToQQBackground){
            //datasetType = 67;
            saveName = "ZH_HToBB_ZToQQ";
            
            int arrSize = sizeof(ZH_HToBB_ZToQQY17BackgroundAr)/sizeof(ZH_HToBB_ZToQQY17BackgroundAr[0]);
            fileAr.push_back(ZH_HToBB_ZToQQY17BackgroundAr[fileInd]);
        }
        else if (ggZH_HToBB_ZToBBBackground){
            //datasetType = 68;
            saveName = "ggZH_HToBB_ZToBB";
            
            int arrSize = sizeof(ggZH_HToBB_ZToBBY17BackgroundAr)/sizeof(ggZH_HToBB_ZToBBY17BackgroundAr[0]);
            fileAr.push_back(ggZH_HToBB_ZToBBY17BackgroundAr[fileInd]);
        }
        else if (ggZH_HToBB_ZToNuNuBackground){
            //datasetType = 68;
            saveName = "ggZH_HToBB_ZToNuNu";
            
            int arrSize = sizeof(ggZH_HToBB_ZToNuNuY17BackgroundAr)/sizeof(ggZH_HToBB_ZToNuNuY17BackgroundAr[0]);
            fileAr.push_back(ggZH_HToBB_ZToNuNuY17BackgroundAr[fileInd]);
        }
        else if (ggZH_HToBB_ZToLLBackground){
            //datasetType = 68;
            saveName = "ggZH_HToBB_ZToLL";
            
            int arrSize = sizeof(ggZH_HToBB_ZToLLY17BackgroundAr)/sizeof(ggZH_HToBB_ZToLLY17BackgroundAr[0]);
            fileAr.push_back(ggZH_HToBB_ZToLLY17BackgroundAr[fileInd]);
        }
        else if (ggZH_HToBB_ZToQQBackground){
            //datasetType = 69;
            saveName = "ggZH_HToBB_ZToQQ";
            
            int arrSize = sizeof(ggZH_HToBB_ZToQQY17BackgroundAr)/sizeof(ggZH_HToBB_ZToQQY17BackgroundAr[0]);
            fileAr.push_back(ggZH_HToBB_ZToQQY17BackgroundAr[fileInd]);
        }
        else if (EWKZ2Jets_ZToLLBackground){
            //datasetType = 70;
            saveName = "EWKZ2Jets_ZToLL";
            
            int arrSize = sizeof(EWKZ2Jets_ZToLLY17BackgroundAr)/sizeof(EWKZ2Jets_ZToLLY17BackgroundAr[0]);
            fileAr.push_back(EWKZ2Jets_ZToLLY17BackgroundAr[fileInd]);
        }
        else if (EWKZ2Jets_ZToNuNuBackground){
            //datasetType = 71;
            saveName = "EWKZ2Jets_ZToNuNu";
            
            int arrSize = sizeof(EWKZ2Jets_ZToNuNuY17BackgroundAr)/sizeof(EWKZ2Jets_ZToNuNuY17BackgroundAr[0]);
            fileAr.push_back(EWKZ2Jets_ZToNuNuY17BackgroundAr[fileInd]);
        }
        else if (EWKZ2Jets_ZToQQBackground){
            //datasetType = 72;
            saveName = "EWKZ2Jets_ZToQQ";
            
            int arrSize = sizeof(EWKZ2Jets_ZToQQY17BackgroundAr)/sizeof(EWKZ2Jets_ZToQQY17BackgroundAr[0]);
            fileAr.push_back(EWKZ2Jets_ZToQQY17BackgroundAr[fileInd]);
        }
        else if (ZZZBackground){
            //datasetType = 73;
            saveName = "ZZZ";
            
            int arrSize = sizeof(ZZZY17BackgroundAr)/sizeof(ZZZY17BackgroundAr[0]);
            fileAr.push_back(ZZZY17BackgroundAr[fileInd]);
        }
        else if (testRun){
            saveName = "testRun";
            fileAr.push_back("./unweighted_eventspphzzjjQCD0SMHLOOP0NPE1NPcHWE1QEDE5ResMasAllVer100Ev10080Seed_0p999cHW100GeVIMJetCut_200.root");
            
            isBackground = false;
            
        }
        else if (LaraTest){
            saveName = "LaraTest";
            fileAr.push_back("/scratch365/dlutton/NanoAODFiles/pp_hwpwmjj_EFT_VBF_chw_09999000_250k.root");
        }
        else{
            std::cout << "ERROR. NO INPUT DATASET NAME GIVEN\n";
        }
    }

    if (!useSingleLepHLT){
        saveName = saveName+"_NoSLHLT";
    }
    if (yearInd == 1){
        saveName = saveName+"Y17";
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
    std::vector<Int_t> Jet_hadronFlavourL;
    std::vector<Int_t> Jet_genJetIdxL;
    std::vector<Float_t> Jet_btagDeepFlavBL;
    Float_t fixedGridRhoFastjetAllL;
    

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

    std::vector<Int_t> FatJet_hadronFlavourL;

    

    //genChannel characterization
    //0=Leptonic,1=Semi-leptonic,2=Hadronic,3=Other,4=Error
    UInt_t genChannelL = 4;

    Bool_t HTobbBoolL = false;

    //HLT
    //2018
    Bool_t HLT_Ele32_WPTight_Gsf_L1DoubleEGL;
    Bool_t HLT_IsoMu27L;
    Bool_t HLT_Mu50L;
    Bool_t HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZL;
    Bool_t HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8L;

    //2016 in other years just set these to false
    Bool_t HLT_Ele27_WPTight_GsfL;
    Bool_t HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZL;

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
    FilteredEventsTree->Branch("Jet_hadronFlavourL",&Jet_hadronFlavourL);
    FilteredEventsTree->Branch("Jet_genJetIdxL",&Jet_genJetIdxL);
    FilteredEventsTree->Branch("Jet_btagDeepFlavBL",&Jet_btagDeepFlavBL);
    FilteredEventsTree->Branch("fixedGridRhoFastjetAllL",&fixedGridRhoFastjetAllL,"fixedGridRhoFastjetAllL/F");

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

    FilteredEventsTree->Branch("FatJet_hadronFlavourL",&FatJet_hadronFlavourL);

    

    //genChannel characterization
    //0=Leptonic,1=Semi-leptonic,2=Hadronic,3=Other,4=Error
    FilteredEventsTree->Branch("genChannelL",&genChannelL,"genChannelL/i");

    FilteredEventsTree->Branch("HTobbBoolL",&HTobbBoolL,"HTobbBoolL/O");

    //HLT
    FilteredEventsTree->Branch("HLT_Ele32_WPTight_Gsf_L1DoubleEGL",&HLT_Ele32_WPTight_Gsf_L1DoubleEGL,"HLT_Ele32_WPTight_Gsf_L1DoubleEGL/O");
    FilteredEventsTree->Branch("HLT_IsoMu27L",&HLT_IsoMu27L,"HLT_IsoMu27L/O");
    FilteredEventsTree->Branch("HLT_Mu50L",&HLT_Mu50L,"HLT_Mu50L/O");
    FilteredEventsTree->Branch("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZL",&HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZL,"HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZL/O");
    FilteredEventsTree->Branch("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8L",&HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8L,"HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8L/O");

    FilteredEventsTree->Branch("HLT_Ele27_WPTight_GsfL",&HLT_Ele27_WPTight_GsfL,"HLT_Ele27_WPTight_GsfL/O");
    FilteredEventsTree->Branch("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZL",&HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZL,"HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZL/O");

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

    float tmpGenerator_weightSum = 0;
    uint tmpnLHEPdfWeightSum = 101;
    //size of 101 is hardcoded in the LHEPdfWeight branch
    std::vector<Float_t> tmpLHEPdfWeightSum(tmpnLHEPdfWeightSum,0.0);
    float tmpLHEWeight_originalXWGTUPSum = 0;
    float tmpgenWeightSum = 0;

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
        TTreeReaderValue<Bool_t> Flag_ecalBadCalibFilter(myEventsReader, "Flag_ecalBadCalibFilter");


        //HLT Branches
        TTreeReaderValue<Bool_t> HLT_TripleMu_10_5_5_DZ(myEventsReader, "HLT_TripleMu_10_5_5_DZ");
        TTreeReaderValue<Bool_t> HLT_TripleMu_12_10_5(myEventsReader, "HLT_TripleMu_12_10_5");


        TTreeReaderValue<Bool_t> HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ(myEventsReader, "HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ");
        TTreeReaderValue<Bool_t> HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL(myEventsReader, "HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL");
        TTreeReaderValue<Bool_t> HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ(myEventsReader, "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ");
        TTreeReaderValue<Bool_t> HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL(myEventsReader, "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL");
        TTreeReaderValue<Bool_t> HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ(myEventsReader, "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ");
        TTreeReaderValue<Bool_t> HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL(myEventsReader, "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL");

        TTreeReaderValue<Bool_t> HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8(myEventsReader, "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8");
        TTreeReaderValue<Bool_t> HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8(myEventsReader, "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8");
        TTreeReaderValue<Bool_t> HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass3p8(myEventsReader, "HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass3p8");
        TTreeReaderValue<Bool_t> HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass8(myEventsReader, "HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass8");

        TTreeReaderValue<Bool_t> HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ(myEventsReader, "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ");
        TTreeReaderValue<Bool_t> HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL(myEventsReader, "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL");
        TTreeReaderValue<Bool_t> HLT_DiEle27_WPTightCaloOnly_L1DoubleEG(myEventsReader, "HLT_DiEle27_WPTightCaloOnly_L1DoubleEG");
        TTreeReaderValue<Bool_t> HLT_DoubleEle33_CaloIdL_MW(myEventsReader, "HLT_DoubleEle33_CaloIdL_MW");
        TTreeReaderValue<Bool_t> HLT_DoubleEle25_CaloIdL_MW(myEventsReader, "HLT_DoubleEle25_CaloIdL_MW");
        TTreeReaderValue<Bool_t> HLT_DoubleEle27_CaloIdL_MW(myEventsReader, "HLT_DoubleEle27_CaloIdL_MW");
        TTreeReaderValue<Bool_t> HLT_DoublePhoton70(myEventsReader, "HLT_DoublePhoton70");

        TTreeReaderValue<Bool_t> HLT_IsoMu24(myEventsReader, "HLT_IsoMu24");
        TTreeReaderValue<Bool_t> HLT_IsoMu27(myEventsReader, "HLT_IsoMu27");
        TTreeReaderValue<Bool_t> HLT_IsoMu30(myEventsReader, "HLT_IsoMu30");
        TTreeReaderValue<Bool_t> HLT_Mu50(myEventsReader, "HLT_Mu50");

        TTreeReaderValue<Bool_t> HLT_Ele115_CaloIdVT_GsfTrkIdT(myEventsReader, "HLT_Ele115_CaloIdVT_GsfTrkIdT");
        TTreeReaderValue<Bool_t> HLT_Ele27_WPTight_Gsf(myEventsReader, "HLT_Ele27_WPTight_Gsf");
        TTreeReaderValue<Bool_t> HLT_Ele32_WPTight_Gsf(myEventsReader, "HLT_Ele32_WPTight_Gsf");
        TTreeReaderValue<Bool_t> HLT_Ele35_WPTight_Gsf(myEventsReader, "HLT_Ele35_WPTight_Gsf");
        TTreeReaderValue<Bool_t> HLT_Ele38_WPTight_Gsf(myEventsReader, "HLT_Ele38_WPTight_Gsf");
        TTreeReaderValue<Bool_t> HLT_Ele40_WPTight_Gsf(myEventsReader, "HLT_Ele40_WPTight_Gsf");
        TTreeReaderValue<Bool_t> HLT_Ele32_WPTight_Gsf_L1DoubleEG(myEventsReader, "HLT_Ele32_WPTight_Gsf_L1DoubleEG");
        TTreeReaderValue<Bool_t> HLT_Photon200(myEventsReader, "HLT_Photon200");

        TTreeReaderValue<Bool_t> HLT_AK8PFJet500(myEventsReader, "HLT_AK8PFJet500");
        TTreeReaderValue<Bool_t> HLT_AK8PFJet360_TrimMass30(myEventsReader, "HLT_AK8PFJet360_TrimMass30");
        TTreeReaderValue<Bool_t> HLT_AK8PFJet380_TrimMass30(myEventsReader, "HLT_AK8PFJet380_TrimMass30");
        TTreeReaderValue<Bool_t> HLT_AK8PFJet400_TrimMass30(myEventsReader, "HLT_AK8PFJet400_TrimMass30");
        TTreeReaderValue<Bool_t> HLT_AK8PFJet420_TrimMass30(myEventsReader, "HLT_AK8PFJet420_TrimMass30");
        TTreeReaderValue<Bool_t> HLT_AK8PFHT750_TrimMass50(myEventsReader, "HLT_AK8PFHT750_TrimMass50");
        TTreeReaderValue<Bool_t> HLT_AK8PFHT800_TrimMass50(myEventsReader, "HLT_AK8PFHT800_TrimMass50");
        TTreeReaderValue<Bool_t> HLT_AK8PFHT850_TrimMass50(myEventsReader, "HLT_AK8PFHT850_TrimMass50");
        TTreeReaderValue<Bool_t> HLT_AK8PFHT900_TrimMass50(myEventsReader, "HLT_AK8PFHT900_TrimMass50");
        TTreeReaderValue<Bool_t> HLT_PFHT1050(myEventsReader, "HLT_PFHT1050");

        //jets

        TTreeReaderValue<UInt_t> nJet(myEventsReader, "nJet");
        TTreeReaderArray<Float_t> Jet_eta(myEventsReader, "Jet_eta");
        TTreeReaderArray<Float_t> Jet_pt(myEventsReader, "Jet_pt");
        TTreeReaderArray<Float_t> Jet_phi(myEventsReader, "Jet_phi");
        TTreeReaderArray<Float_t> Jet_mass(myEventsReader, "Jet_mass");
        TTreeReaderArray<Int_t> Jet_jetId(myEventsReader, "Jet_jetId");
        TTreeReaderArray<Int_t> Jet_hadronFlavour(myEventsReader, "Jet_hadronFlavour");
        TTreeReaderArray<Int_t> Jet_genJetIdx(myEventsReader, "Jet_genJetIdx");
        TTreeReaderArray<Float_t> Jet_btagDeepFlavB(myEventsReader, "Jet_btagDeepFlavB");
        TTreeReaderValue<Float_t> fixedGridRhoFastjetAll(myEventsReader, "fixedGridRhoFastjetAll");

        //GenJet

        TTreeReaderValue<UInt_t> nGenJet(myEventsReader, "nGenJet");
        TTreeReaderArray<Float_t> GenJet_eta(myEventsReader, "GenJet_eta");
        TTreeReaderArray<Float_t> GenJet_pt(myEventsReader, "GenJet_pt");
        TTreeReaderArray<Float_t> GenJet_phi(myEventsReader, "GenJet_phi");
        TTreeReaderArray<Float_t> GenJet_mass(myEventsReader, "GenJet_mass");
        TTreeReaderArray<UChar_t> GenJet_hadronFlavour(myEventsReader, "GenJet_hadronFlavour");

        //GenJetAK8
        TTreeReaderValue<UInt_t> nGenJetAK8(myEventsReader, "nGenJetAK8");
        TTreeReaderArray<Float_t> GenJetAK8_eta(myEventsReader, "GenJetAK8_eta");
        TTreeReaderArray<Float_t> GenJetAK8_pt(myEventsReader, "GenJetAK8_pt");
        TTreeReaderArray<Float_t> GenJetAK8_phi(myEventsReader, "GenJetAK8_phi");
        TTreeReaderArray<Float_t> GenJetAK8_mass(myEventsReader, "GenJetAK8_mass");
        TTreeReaderArray<UChar_t> GenJetAK8_hadronFlavour(myEventsReader, "GenJetAK8_hadronFlavour");

        

        

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
        TTreeReaderArray<Int_t> FatJet_genJetAK8Idx(myEventsReader, "FatJet_genJetAK8Idx");

        TTreeReaderArray<Int_t> FatJet_hadronFlavour(myEventsReader, "FatJet_hadronFlavour");

        TTreeReaderArray<Float_t> FatJet_particleNet_mass(myEventsReader, "FatJet_particleNet_mass");


        //Gen part stuff

        TTreeReaderValue<UInt_t> nGenPart(myEventsReader, "nGenPart");
        TTreeReaderArray<Float_t> GenPart_eta(myEventsReader, "GenPart_eta");
        TTreeReaderArray<Float_t> GenPart_mass(myEventsReader, "GenPart_mass");
        TTreeReaderArray<Float_t> GenPart_phi(myEventsReader, "GenPart_phi");
        TTreeReaderArray<Float_t> GenPart_pt(myEventsReader, "GenPart_pt");
        TTreeReaderArray<Int_t> GenPart_genPartIdxMother(myEventsReader, "GenPart_genPartIdxMother");
        TTreeReaderArray<Int_t> GenPart_pdgId(myEventsReader, "GenPart_pdgId");
        TTreeReaderArray<Int_t> GenPart_status(myEventsReader, "GenPart_status");
        TTreeReaderArray<Int_t> GenPart_statusFlags(myEventsReader, "GenPart_statusFlags");
        
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
        TTreeReaderArray<Int_t> Muon_nTrackerLayers(myEventsReader, "Muon_nTrackerLayers");
        TTreeReaderArray<Int_t> Muon_genPartIdx(myEventsReader, "Muon_genPartIdx");


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

        

        //ParticleNet
        TTreeReaderArray<Float_t> FatJet_particleNet_HbbvsQCD(myEventsReader, "FatJet_particleNet_HbbvsQCD");
        TTreeReaderArray<Float_t> FatJet_particleNet_ZvsQCD(myEventsReader, "FatJet_particleNet_ZvsQCD");
        TTreeReaderArray<Float_t> FatJet_particleNetMD_QCD(myEventsReader, "FatJet_particleNetMD_QCD");
        TTreeReaderArray<Float_t> FatJet_particleNetMD_Xbb(myEventsReader, "FatJet_particleNetMD_Xbb");
        TTreeReaderArray<Float_t> FatJet_particleNetMD_Xcc(myEventsReader, "FatJet_particleNetMD_Xcc");
        TTreeReaderArray<Float_t> FatJet_particleNetMD_Xqq(myEventsReader, "FatJet_particleNetMD_Xqq");

        //042024SFAndSuchAdditions
        //PU JetID
        TTreeReaderArray<Int_t> Jet_puId(myEventsReader, "Jet_puId");
        //L1 Prefiring Weights
        TTreeReaderValue<Float_t> L1PreFiringWeight_Nom(myEventsReader, "L1PreFiringWeight_Nom");
        TTreeReaderValue<Float_t> L1PreFiringWeight_Dn(myEventsReader, "L1PreFiringWeight_Dn");
        TTreeReaderValue<Float_t> L1PreFiringWeight_Up(myEventsReader, "L1PreFiringWeight_Up");
        //PileUp number of interactions
        TTreeReaderValue<Float_t> Pileup_nTrueInt(myEventsReader, "Pileup_nTrueInt");
        TTreeReaderValue<Int_t> Pileup_nPU(myEventsReader, "Pileup_nPU");
        //PSWeight
        TTreeReaderValue<UInt_t> nPSWeight(myEventsReader, "nPSWeight");
        TTreeReaderArray<Float_t> PSWeight(myEventsReader, "PSWeight");
        //LHE Scale Weight
        TTreeReaderValue<UInt_t> nLHEScaleWeight(myEventsReader, "nLHEScaleWeight");
        TTreeReaderArray<Float_t> LHEScaleWeight(myEventsReader, "LHEScaleWeight");
        //LHE PDF Weight
        TTreeReaderValue<UInt_t> nLHEPdfWeight(myEventsReader, "nLHEPdfWeight");
        TTreeReaderArray<Float_t> LHEPdfWeight(myEventsReader, "LHEPdfWeight");
        TTreeReaderValue<Float_t> LHEWeight_originalXWGTUP(myEventsReader, "LHEWeight_originalXWGTUP");
        //gen weights and weight sums
        TTreeReaderValue<Float_t> Generator_weight(myEventsReader, "Generator_weight");

        //05052024 Additions for PN regress mass scaling and resolution corrections
        TTreeReaderValue<UInt_t> luminosityBlock(myEventsReader, "luminosityBlock");
        TTreeReaderValue<ULong64_t> event(myEventsReader, "event");




        TTreeReader myRunsReader("Runs", tmpfile);
        TTreeReaderValue<UInt_t> run(myRunsReader, "run");
        TTreeReaderValue<UInt_t> nLHEPdfSumw(myRunsReader, "nLHEPdfSumw");
        TTreeReaderArray<Double_t> LHEPdfSumw(myRunsReader, "LHEPdfSumw");
        TTreeReaderValue<UInt_t> nLHEScaleSumw(myRunsReader, "nLHEScaleSumw");
        TTreeReaderArray<Double_t> LHEScaleSumw(myRunsReader, "LHEScaleSumw");
        TTreeReaderValue<Long64_t> genEventCount(myRunsReader, "genEventCount");
        TTreeReaderValue<Double_t> genEventSumw(myRunsReader, "genEventSumw");
        TTreeReaderValue<Double_t> genEventSumw2(myRunsReader, "genEventSumw2");
        
        crossSection = 0.;
        Long64_t eventLoopMax = myRunsReader.GetEntries();
        UInt_t tmpRunsInt = 0;
        while (myRunsReader.Next()){
            if (debug){
                std::cout << *genEventSumw << "\n";
                std::cout << *genEventCount << "\n";
            }
            totCrossSectionWeight += *genEventSumw;
            totCrossSectionEvCount += *genEventCount;
            crossSection += *genEventSumw / *genEventCount;
            if (debug) std::cout << crossSection << "\n";
            crossSection = crossSection / eventLoopMax;
            if (debug) std::cout << crossSection << "\n";
            crossSectionAvg += crossSection;
            if (debug) std::cout << crossSectionAvg << "\n";
            crossSectionCtr += 1;
            if (debug) std::cout << crossSectionCtr << "\n";
            
            //Fill the run tree
            nLHEPdfSumwL = *nLHEPdfSumw;
            for (UInt_t i=0; i<nLHEPdfSumwL; i++){
                LHEPdfSumwL.push_back(LHEPdfSumw[i]);
            }
            nLHEScaleSumwL = *nLHEScaleSumw;
            for (UInt_t i=0; i<nLHEScaleSumwL; i++){
                LHEScaleSumwL.push_back(LHEScaleSumw[i]);
            }
            genEventCountL = *genEventCount;
            genEventSumwL = *genEventSumw;
            genEventSumw2L = *genEventSumw2;
            runL = *run;
            runTree->Fill();
            //clear run tree vectors
            LHEPdfSumwL.clear();
            LHEScaleSumwL.clear();
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

            tmpGenerator_weightSum += *Generator_weight;
            for (UInt_t i=0; i<*nLHEPdfWeight; i++){
                tmpLHEPdfWeightSum[i] += LHEPdfWeight[i];
            }
            tmpLHEWeight_originalXWGTUPSum += *LHEWeight_originalXWGTUP;
            tmpgenWeightSum += *genWeight;

            sumOfGenWeights += *genWeight;
            genChannelL = 4;
            HTobbBoolL = false;

            //--------------KINEMATICS--------------

            UInt_t tmpnFatJets = *nFatJet;
            
            

            bool passFlagBool = *Flag_goodVertices && *Flag_globalSuperTightHalo2016Filter && *Flag_HBHENoiseFilter && *Flag_HBHENoiseIsoFilter && *Flag_EcalDeadCellTriggerPrimitiveFilter && *Flag_BadPFMuonFilter && *Flag_eeBadScFilter && *Flag_ecalBadCalibFilter;

            if (!passFlagBool) continue;
            passFlagCtr += 1;
            passFlagWeightedCtr += *genWeight;



            if (debug){
                std::cout <<"Passed flag\n";
            }


            bool passHLTBool = (*HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ || *HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8);
            if (useSingleLepHLT) {
                passHLTBool = (passHLTBool || *HLT_IsoMu27 || *HLT_Mu50 || *HLT_Ele32_WPTight_Gsf_L1DoubleEG);
            }
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
                Jet_hadronFlavourL.push_back(Jet_hadronFlavour[nJetItr]);
                Jet_genJetIdxL.push_back(Jet_genJetIdx[nJetItr]);
                Jet_btagDeepFlavBL.push_back(Jet_btagDeepFlavB[nJetItr]);
            }
            fixedGridRhoFastjetAllL = *fixedGridRhoFastjetAll;

            //GenJets
            nGenJetL = *nGenJet;
            for (UInt_t nGenJetItr=0; nGenJetItr<nGenJetL;nGenJetItr++){
                GenJet_etaL.push_back(GenJet_eta[nGenJetItr]);
                GenJet_ptL.push_back(GenJet_pt[nGenJetItr]);
                GenJet_phiL.push_back(GenJet_phi[nGenJetItr]);
                GenJet_massL.push_back(GenJet_mass[nGenJetItr]);
                GenJet_hadronFlavourL.push_back(GenJet_hadronFlavour[nGenJetItr]);
            }

            //GenJetAK8
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
                FatJet_hadronFlavourL.push_back(FatJet_hadronFlavour[nFatJetItr]);
                FatJet_particleNet_massL.push_back(FatJet_particleNet_mass[nFatJetItr]);

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
                Muon_nTrackerLayersL.push_back(Muon_nTrackerLayers[nMuonItr]);
                Muon_genPartIdxL.push_back(Muon_genPartIdx[nMuonItr]);

            }

            //GenPart
            nGenPartL = *nGenPart;
            for (UInt_t nGenPartItr=0; nGenPartItr<nGenPartL;nGenPartItr++){
                GenPart_etaL.push_back(GenPart_eta[nGenPartItr]);
                GenPart_massL.push_back(GenPart_mass[nGenPartItr]);
                GenPart_pdgIdL.push_back(GenPart_pdgId[nGenPartItr]);
                GenPart_phiL.push_back(GenPart_phi[nGenPartItr]);
                GenPart_ptL.push_back(GenPart_pt[nGenPartItr]);
                GenPart_statusL.push_back(GenPart_status[nGenPartItr]);
                GenPart_genPartIdxMotherL.push_back(GenPart_genPartIdxMother[nGenPartItr]);
                GenPart_statusFlagsL.push_back(GenPart_statusFlags[nGenPartItr]);
            }

            //HLT 
            HLT_Ele32_WPTight_Gsf_L1DoubleEGL = *HLT_Ele32_WPTight_Gsf_L1DoubleEG;
            HLT_IsoMu27L = *HLT_IsoMu27;
            HLT_Mu50L = *HLT_Mu50;
            HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZL = *HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;
            HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8L = *HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8;

            //2016
            HLT_Ele27_WPTight_GsfL = false;
            HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZL = false;

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

            Jet_etaL.clear();
            Jet_ptL.clear();
            Jet_phiL.clear();
            Jet_massL.clear();
            Jet_jetIdL.clear();
            Jet_hadronFlavourL.clear();
            Jet_genJetIdxL.clear();
            Jet_btagDeepFlavBL.clear();

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

            GenPart_etaL.clear();
            GenPart_massL.clear();
            GenPart_pdgIdL.clear();
            GenPart_phiL.clear();
            GenPart_ptL.clear();
            GenPart_statusL.clear();
            GenPart_genPartIdxMotherL.clear();
            GenPart_statusFlagsL.clear();
            

            FatJet_particleNet_HbbvsQCDL.clear();
            FatJet_particleNet_ZvsQCDL.clear();

            FatJet_particleNetMD_QCDL.clear();
            FatJet_particleNetMD_XbbL.clear();
            FatJet_particleNetMD_XccL.clear();
            FatJet_particleNetMD_XqqL.clear();

            FatJet_hadronFlavourL.clear();

            Jet_puIdL.clear();

            PSWeightL.clear();
            LHEScaleWeightL.clear();
            LHEPdfWeightL.clear();
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

    //Fill Weight sum tree
    Generator_weightSumL = tmpGenerator_weightSum;
    nLHEPdfWeightSumL = tmpnLHEPdfWeightSum;
    for (UInt_t nLHEPdfWeightSumItr=0; nLHEPdfWeightSumItr<nLHEPdfWeightSumL;nLHEPdfWeightSumItr++){
        LHEPdfWeightSumL.push_back(tmpLHEPdfWeightSum[nLHEPdfWeightSumItr]);
    }
    LHEWeight_originalXWGTUPSumL = tmpLHEWeight_originalXWGTUPSum;
    genWeightSumL = tmpgenWeightSum;
    std::cout << "Generator_weightSumL: " << Generator_weightSumL << "\n";
    std::cout << "nLHEPdfWeightSumL: " << nLHEPdfWeightSumL << "\n";
    std::cout << "LHEPdfWeightSumL: ";
    for (UInt_t nLHEPdfWeightSumItr=0; nLHEPdfWeightSumItr<nLHEPdfWeightSumL;nLHEPdfWeightSumItr++){
        std::cout << LHEPdfWeightSumL[nLHEPdfWeightSumItr] << " ";
    }
    std::cout << "\n";
    std::cout << "LHEWeight_originalXWGTUPSumL: " << LHEWeight_originalXWGTUPSumL << "\n";
    std::cout << "genWeightSumL: " << genWeightSumL << "\n";
    weightSumsTree->Fill();
    LHEPdfWeightSumL.clear();

    outFile->cd();
    weightSumsTree->Write("",TObject::kOverwrite);
    runTree->Write("",TObject::kOverwrite);
    evNumTree->Write("",TObject::kOverwrite);
    FilteredEventsTree->Write("",TObject::kOverwrite);

    outFile->Close();
}