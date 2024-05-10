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

//Script for calculating the JEC and Rochester uncertainties, and BTagging Efficiencies for the HLT output files
//Output should be the same but with additional branches for the corrections and efficiencies
//Apply JER before BTagging Efficencies
//Input should be the dataset string, then an integer for each correction/efficiency to be calculated
void calc042024BackgroundJECRochJERUncertaintiesAndBTagEff(string datasetString, int JECCorInd, bool JECCorUpOrDown,  int RochInd, int JERInd,uint yearInd){
    // Open the file. Note that the name of your file outside this class
    // will probably NOT be experiment.root.
    std::cout << "start Analysis\n";
    clock_t startt = clock();


    RoccoR  rc("../RoccoR2018UL.txt"); 

    //Will run over all files put into fileAr

    //gInterpreter->GenerateDictionary("vector<vector<vector<Double_t> > >", "vector");
    //gInterpreter->GenerateDictionary("vector<vector<vector<Int_t> > >", "vector");


    std::vector<std::string> fileAr;
    string NoSLString = "";
    if (!useSingleLepHLT){
        NoSLString = "_NoSLHLT";
    }


    std::string saveName;
    bool isBackground;

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

    ////////////////////////////////GETTING DATASET////////////////////////////////
    ////////////////////////////////GETTING DATASET////////////////////////////////
    ////////////////////////////////GETTING DATASET////////////////////////////////
    ////////////////////////////////GETTING DATASET////////////////////////////////

    std::string strAdd;
    if (scratchDown) strAdd ="/afs/crc.nd.edu/user/d/dlutton/Public/condorStuff/NanoAODToHistos/tmpHoldForNanoAODWithoutScratch/";
    else strAdd ="/scratch365/dlutton/HLT042024BackgroundForPreSel/";
    if (localTest) strAdd = "";


    UInt_t datasetType = 0;
    float crossSection; //this is unused
    std::vector<string> yearStringAr = {"","Y17","Y16","Y16APV"};
    UInt_t yearType = yearInd;
    string yearNameStr = yearStringAr[yearType];

    if (ttHToBBTrimmedBackground){
        //saveName = "ttHToBB";
        crossSection = 0.5071*0.582;

        saveName = "ttHToBB";
        
        
        //int arrSize = sizeof(ttHToBBBackgroundAr)/sizeof(ttHToBBBackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //ttHToBBBackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //ttHToBBBackgroundAr[fileInd]);
    }
    else if (ttZJetsTrimmedBackground){
        //saveName = "ttZJets";
        
        crossSection = 0.5407;
        saveName = "ttZJets";
        
        //int arrSize = sizeof(ttZJetsBackgroundAr)/sizeof(ttZJetsBackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //ttZJetsBackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //ttZJetsBackgroundAr[fileInd]);
    }
    else if (ttWJetsTrimmedBackground){
        
        crossSection = 0.4611;
        saveName = "ttWJets";
        
        //int arrSize = sizeof(ttWJetsBackgroundAr)/sizeof(ttWJetsBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //ttWJetsBackgroundAr[fileInd]);
    }
    else if (DYTrimmedBackground){
        //saveName = "DY";
        
        crossSection = 5364;
        saveName = "DY";

        
        //int arrSize = sizeof(DYBackgroundAr)/sizeof(DYBackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //DYBackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //DYBackgroundAr[fileInd]);
    }
    else if (QCDPT170to300TrimmedBackground){
        //saveName = "QCDPT170to300";
        
        crossSection = 103300.0;

        saveName = "QCDPT170to300";
        
        
        //int arrSize = sizeof(QCDPT170to300BackgroundAr)/sizeof(QCDPT170to300BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //QCDPT170to300BackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //QCDPT170to300BackgroundAr[fileInd]);
    }
    else if (QCDPT300to470TrimmedBackground){
        //saveName = "QCDPT300to470";
        
        crossSection = 6826.0;

        saveName = "QCDPT300to470";
        
        
        //int arrSize = sizeof(QCDPT300to470BackgroundAr)/sizeof(QCDPT300to470BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //QCDPT300to470BackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //QCDPT300to470BackgroundAr[fileInd]);
    }
    else if (QCDPT470to600TrimmedBackground){
        //saveName = "QCDPT470to600";
        
        crossSection = 552.6;
        
        saveName = "QCDPT470to600";

        
        //int arrSize = sizeof(QCDPT470to600BackgroundAr)/sizeof(QCDPT470to600BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //QCDPT470to600BackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //QCDPT470to600BackgroundAr[fileInd]);
    }
    else if (QCDPT600to800TrimmedBackground){
        //saveName = "QCDPT600to800";
        
        crossSection = 156.6;

        saveName = "QCDPT600to800";
        
        
        //int arrSize = sizeof(QCDPT600to800BackgroundAr)/sizeof(QCDPT600to800BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //QCDPT600to800BackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //QCDPT600to800BackgroundAr[fileInd]);
    }
    else if (QCDPT800to1000TrimmedBackground){
        //saveName = "QCDPT800to1000";
        
        crossSection = 26.32;

        saveName = "QCDPT800to1000";
        
        
        //int arrSize = sizeof(QCDPT800to1000BackgroundAr)/sizeof(QCDPT800to1000BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //QCDPT800to1000BackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //QCDPT800to1000BackgroundAr[fileInd]);
    }
    else if (QCDPT1000to1400TrimmedBackground){
        //saveName = "QCDPT1000to1400";
        
        crossSection = 7.5;

        saveName = "QCDPT1000to1400";
        
        
        //int arrSize = sizeof(QCDPT1000to1400BackgroundAr)/sizeof(QCDPT1000to1400BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //QCDPT1000to1400BackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //QCDPT1000to1400BackgroundAr[fileInd]);
    }
    else if (QCDPT1400to1800TrimmedBackground){
        //saveName = "QCDPT1400to1800";
        
        crossSection = 0.6479;

        saveName = "QCDPT1400to1800";
        
        
        //int arrSize = sizeof(QCDPT1400to1800BackgroundAr)/sizeof(QCDPT1400to1800BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //QCDPT1400to1800BackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //QCDPT1400to1800BackgroundAr[fileInd]);
    }
    else if (QCDPT1800to2400TrimmedBackground){
        //saveName = "QCDPT1800to2400";
        
        crossSection = 0.08715;

        saveName = "QCDPT1800to2400";
        
        
        //int arrSize = sizeof(QCDPT1800to2400BackgroundAr)/sizeof(QCDPT1800to2400BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //QCDPT1800to2400BackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //QCDPT1800to2400BackgroundAr[fileInd]);
    }
    else if (QCDPT2400to3200TrimmedBackground){
        //saveName = "QCDPT2400to3200";
        
        crossSection = 0.005242;

        saveName = "QCDPT2400to3200";
        
        
        //int arrSize = sizeof(QCDPT2400to3200BackgroundAr)/sizeof(QCDPT2400to3200BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //QCDPT2400to3200BackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //QCDPT2400to3200BackgroundAr[fileInd]);
    }
    else if (QCDPT3200toInfTrimmedBackground){
        //saveName = "QCDPT3200toInf";
        
        crossSection = 0.0001349;

        saveName = "QCDPT3200toInf";
        
        
        //int arrSize = sizeof(QCDPT3200toInfBackgroundAr)/sizeof(QCDPT3200toInfBackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //QCDPT3200toInfBackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //QCDPT3200toInfBackgroundAr[fileInd]);
    }
    else if (QCDHT50to100TrimmedBackground){
        //saveName = "QCDHT50to100";
        
        crossSection = 187700000.;

        saveName = "QCDHT50to100";
        
        
        //int arrSize = sizeof(QCDHT50to100BackgroundAr)/sizeof(QCDHT50to100BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //QCDHT50to100BackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //QCDHT50to100BackgroundAr[fileInd]);
    }
    else if (QCDHT100to200TrimmedBackground){
        //saveName = "QCDHT100to200";
        
        crossSection = 23640000.0;

        saveName = "QCDHT100to200";
        
        
        //int arrSize = sizeof(QCDHT100to200BackgroundAr)/sizeof(QCDHT100to200BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //QCDHT100to200BackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //QCDHT100to200BackgroundAr[fileInd]);
    }
    else if (QCDHT200to300TrimmedBackground){
        //saveName = "QCDHT200to300";
        
        crossSection = 1546000.0;

        saveName = "QCDHT200to300";
        
        
        //int arrSize = sizeof(QCDHT200to300BackgroundAr)/sizeof(QCDHT200to300BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //QCDHT200to300BackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //QCDHT200to300BackgroundAr[fileInd]);
    }
    else if (QCDHT300to500TrimmedBackground){
        //saveName = "QCDHT300to500";
        
        crossSection = 321600.0;

        saveName = "QCDHT300to500";
        
        
        //int arrSize = sizeof(QCDHT300to500BackgroundAr)/sizeof(QCDHT300to500BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //QCDHT300to500BackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //QCDHT300to500BackgroundAr[fileInd]);
    }
    else if (QCDHT500to700TrimmedBackground){
        //saveName = "QCDHT500to700";
        
        crossSection = 30980.0;

        saveName = "QCDHT500to700";
        
        
        //int arrSize = sizeof(QCDHT500to700BackgroundAr)/sizeof(QCDHT500to700BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //QCDHT500to700BackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //QCDHT500to700BackgroundAr[fileInd]);
    }
    else if (QCDHT700to1000TrimmedBackground){
        //saveName = "QCDHT700to1000";
        
        crossSection = 6364.0;

        saveName = "QCDHT700to1000";
        
        
        //int arrSize = sizeof(QCDHT700to1000BackgroundAr)/sizeof(QCDHT700to1000BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //QCDHT700to1000BackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //QCDHT700to1000BackgroundAr[fileInd]);
    }
    else if (QCDHT1000to1500TrimmedBackground){
        //saveName = "QCDHT1000to1500";
        
        crossSection = 1117.0;

        saveName = "QCDHT1000to1500";
        
        
        //int arrSize = sizeof(QCDHT1000to1500BackgroundAr)/sizeof(QCDHT1000to1500BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //QCDHT1000to1500BackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //QCDHT1000to1500BackgroundAr[fileInd]);
    }
    else if (QCDHT1500to2000TrimmedBackground){
        //saveName = "QCDHT1500to2000";
        
        crossSection = 108.4;

        saveName = "QCDHT1500to2000";
        
        
        //int arrSize = sizeof(QCDHT1500to2000BackgroundAr)/sizeof(QCDHT1500to2000BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //QCDHT1500to2000BackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //QCDHT1500to2000BackgroundAr[fileInd]);
    }
    else if (QCDHT2000toInfTrimmedBackground){
        //saveName = "QCDHT2000toInf";
        
        crossSection = 22.36;

        saveName = "QCDHT2000toInf";
        
        
        //int arrSize = sizeof(QCDHT2000toInfBackgroundAr)/sizeof(QCDHT2000toInfBackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //QCDHT2000toInfBackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //QCDHT2000toInfBackgroundAr[fileInd]);
    }
    else if (TTJetsTrimmedBackground){
        //saveName = "";
        
        crossSection = 722.8;

        saveName = "TTJets";
        
        
        //int arrSize = sizeof(TTJetsBackgroundAr)/sizeof(TTJetsBackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //TTJetsBackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //TTJetsBackgroundAr[fileInd]);
    }
    else if (TTToHadronicTrimmedBackground){
        //saveName = "";
        
        crossSection = 377.96;

        saveName = "TTJetsHadronic";
        
        
        //int arrSize = sizeof(TTJetsHadronicBackgroundAr)/sizeof(TTJetsHadronicBackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //TTJetsHadronicBackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //TTJetsHadronicBackgroundAr[fileInd]);
    }
    else if (TTToSemiLeptonicTrimmedBackground){
        //saveName = "";
        
        crossSection = 365.346;

        saveName = "TTJetsSemiLeptonic";
        
        
        //int arrSize = sizeof(TTJetsSemiLeptonicBackgroundAr)/sizeof(TTJetsSemiLeptonicBackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //TTJetsSemiLeptonicBackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //TTJetsSemiLeptonicBackgroundAr[fileInd]);
    }
    else if (TTTo2L2NuTrimmedBackground){
        //saveName = "";
        
        crossSection = 88.29;

        saveName = "TTJets2L2Nu";
        
        
        //int arrSize = sizeof(TTJets2L2NuBackgroundAr)/sizeof(TTJets2L2NuBackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //TTJets2L2NuBackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //TTJets2L2NuBackgroundAr[fileInd]);
    }
    else if (ST_s_ChannelTrimmedBackground){
        //saveName = "";
        
        crossSection = 3.74;

        saveName = "ST_s_Channel";
        
        
        //int arrSize = sizeof(ST_s_ChannelBackgroundAr)/sizeof(ST_s_ChannelBackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //ST_s_ChannelBackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //ST_s_ChannelBackgroundAr[fileInd]);
    }
    else if (ST_t_ChannelAntiTopTrimmedBackground){
        //saveName = "";
        
        crossSection = 69.09;

        saveName = "ST_t_ChannelAntiTop";
        
        
        //int arrSize = sizeof(ST_t_ChannelAntiTopBackgroundAr)/sizeof(ST_t_ChannelAntiTopBackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //ST_t_ChannelAntiTopBackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //ST_t_ChannelAntiTopBackgroundAr[fileInd]);
    }
    else if (ST_t_ChannelTopTrimmedBackground){
        //saveName = "";
        
        crossSection = 115.3;

        saveName = "ST_t_ChannelTop";
        
        
        //int arrSize = sizeof(ST_t_ChannelTopBackgroundAr)/sizeof(ST_t_ChannelTopBackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //ST_t_ChannelTopBackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //ST_t_ChannelTopBackgroundAr[fileInd]);
    }
    else if (ZZTrimmedBackground){
        //saveName = "";
        
        crossSection = 12.17;

        saveName = "ZZ";
        
        
        //int arrSize = sizeof(ZZBackgroundAr)/sizeof(ZZBackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //ZZBackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //ZZBackgroundAr[fileInd]);
    }
    else if (WWTrimmedBackground){
        //saveName = "";
        
        crossSection = 75.95;

        saveName = "WW";
        
        
        //int arrSize = sizeof(WWBackgroundAr)/sizeof(WWBackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //WWBackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //WWBackgroundAr[fileInd]);
    }
    else if (WZTrimmedBackground){
        //saveName = "";
        
        crossSection = 27.59;

        saveName = "WZ";
        
        
        //int arrSize = sizeof(WZBackgroundAr)/sizeof(WZBackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //WZBackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //WZBackgroundAr[fileInd]);
    }
    else if (TTbb_TTToHadronicTrimmedBackground){
        //saveName = "QCDPT3200toInf";
        
        crossSection = 5.5;

        saveName = "TTbb_TTToHadronic";
        
        
        //int arrSize = sizeof(TTbb_TTToHadronicBackgroundAr)/sizeof(TTbb_TTToHadronicBackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //TTbb_TTToHadronicBackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //TTbb_TTToHadronicBackgroundAr[fileInd]);
    }
    else if (TTbb_TTTo2L2NuTrimmedBackground){
        //saveName = "";
        
        crossSection = 2.9;

        saveName = "TTbb_TTTo2L2Nu";
        
        
        //int arrSize = sizeof(TTbb_TTTo2L2NuBackgroundAr)/sizeof(TTbb_TTTo2L2NuBackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //TTbb_TTTo2L2NuBackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //TTbb_TTTo2L2NuBackgroundAr[fileInd]);
    }
    else if (TTbb_TTToSemiLeptonicTrimmedBackground){
        //saveName = "";
        
        crossSection = 4.7;

        saveName = "TTbb_TTToSemiLeptonic";
        
        
        //int arrSize = sizeof(TTbb_TTToSemiLeptonicBackgroundAr)/sizeof(TTbb_TTToSemiLeptonicBackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //TTbb_TTToSemiLeptonicBackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //TTbb_TTToSemiLeptonicBackgroundAr[fileInd]);
    }
    else if (DYM10To50TrimmedBackground){
        //datasetType = 50;
        saveName = "DYM10To50";
        
        //int arrSize = sizeof(DYM10To50BackgroundAr)/sizeof(DYM10To50BackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //DYM10To50BackgroundAr[fileInd]);
    }
    else if (ST_tW_antitopTrimmedBackground){
        //datasetType = 51;
        saveName = "ST_tW_antitop";
        
        //int arrSize = sizeof(ST_tW_antitopBackgroundAr)/sizeof(ST_tW_antitopBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //ST_tW_antitopBackgroundAr[fileInd]);
    }
    else if (ST_tW_topTrimmedBackground){
        //datasetType = 52;
        saveName = "ST_tW_top";
        
        //int arrSize = sizeof(ST_tW_topBackgroundAr)/sizeof(ST_tW_topBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //ST_tW_topBackgroundAr[fileInd]);
    }
    else if (EWKWMinus2Jets_WToLNuTrimmedBackground){
        //datasetType = 53;
        saveName = "EWKWMinus2Jets_WToLNu";
        
        //int arrSize = sizeof(EWKWMinus2Jets_WToLNuBackgroundAr)/sizeof(EWKWMinus2Jets_WToLNuBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //EWKWMinus2Jets_WToLNuBackgroundAr[fileInd]);
    }
    else if (EWKWMinus2Jets_WToQQTrimmedBackground){
        //datasetType = 54;
        saveName = "EWKWMinus2Jets_WToQQ";
        
        //int arrSize = sizeof(EWKWMinus2Jets_WToQQBackgroundAr)/sizeof(EWKWMinus2Jets_WToQQBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //EWKWMinus2Jets_WToQQBackgroundAr[fileInd]);
    }
    else if (EWKWPlus2Jets_WToLNuTrimmedBackground){
        //datasetType = 55;
        saveName = "EWKWPlus2Jets_WToLNu";
        
        //int arrSize = sizeof(EWKWPlus2Jets_WToLNuBackgroundAr)/sizeof(EWKWPlus2Jets_WToLNuBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //EWKWPlus2Jets_WToLNuBackgroundAr[fileInd]);
    }
    else if (EWKWPlus2Jets_WToQQTrimmedBackground){
        //datasetType = 56;
        saveName = "EWKWPlus2Jets_WToQQ";
        
        //int arrSize = sizeof(EWKWPlus2Jets_WToQQBackgroundAr)/sizeof(EWKWPlus2Jets_WToQQBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //EWKWPlus2Jets_WToQQBackgroundAr[fileInd]);
    }
    else if (VHToNonbbTrimmedBackground){
        //datasetType = 57;
        saveName = "VHToNonbb";
        
        //int arrSize = sizeof(VHToNonbbBackgroundAr)/sizeof(VHToNonbbBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //VHToNonbbBackgroundAr[fileInd]);
    }
    else if (WminusH_HToBB_WToLNuTrimmedBackground){
        //datasetType = 58;
        saveName = "WminusH_HToBB_WToLNu";
        
        //int arrSize = sizeof(WminusH_HToBB_WToLNuBackgroundAr)/sizeof(WminusH_HToBB_WToLNuBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //WminusH_HToBB_WToLNuBackgroundAr[fileInd]);
    }
    else if (WminusH_HToBB_WToQQTrimmedBackground){
        //datasetType = 59;
        saveName = "WminusH_HToBB_WToQQ";
        
        //int arrSize = sizeof(WminusH_HToBB_WToQQBackgroundAr)/sizeof(WminusH_HToBB_WToQQBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //WminusH_HToBB_WToQQBackgroundAr[fileInd]);
    }
    else if (WplusH_HToBB_WToLNuTrimmedBackground){
        //datasetType = 60;
        saveName = "WplusH_HToBB_WToLNu";
        
        //int arrSize = sizeof(WplusH_HToBB_WToLNuBackgroundAr)/sizeof(WplusH_HToBB_WToLNuBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //WplusH_HToBB_WToLNuBackgroundAr[fileInd]);
    }
    else if (WplusH_HToBB_WToQQTrimmedBackground){
        //datasetType = 61;
        saveName = "WplusH_HToBB_WToQQ";
        
        //int arrSize = sizeof(WplusH_HToBB_WToQQBackgroundAr)/sizeof(WplusH_HToBB_WToQQBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //WplusH_HToBB_WToQQBackgroundAr[fileInd]);
    }
    else if (WJetsToLNuTrimmedBackground){
        //datasetType = 62;
        saveName = "WJetsToLNu";
        
        //int arrSize = sizeof(WJetsToLNuBackgroundAr)/sizeof(WJetsToLNuBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //WJetsToLNuBackgroundAr[fileInd]);
    }
    else if (WWWTrimmedBackground){
        //datasetType = 63;
        saveName = "WWW";
        
        //int arrSize = sizeof(WWWBackgroundAr)/sizeof(WWWBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //WWWBackgroundAr[fileInd]);
    }
    else if (WWZTrimmedBackground){
        //datasetType = 64;
        saveName = "WWZ";
        
        //int arrSize = sizeof(WWZBackgroundAr)/sizeof(WWZBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //WWZBackgroundAr[fileInd]);
    }
    else if (WZZTrimmedBackground){
        //datasetType = 65;
        saveName = "WZZ";
        
        //int arrSize = sizeof(WZZBackgroundAr)/sizeof(WZZBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //WZZBackgroundAr[fileInd]);
    }
    else if (ZH_HToBB_ZToBBTrimmedBackground){
        //datasetType = 66;
        saveName = "ZH_HToBB_ZToBB";
        
        //int arrSize = sizeof(ZH_HToBB_ZToBBBackgroundAr)/sizeof(ZH_HToBB_ZToBBBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //ZH_HToBB_ZToBBBackgroundAr[fileInd]);
    }
    else if (ZH_HToBB_ZToNuNuTrimmedBackground){
        //datasetType = 66;
        saveName = "ZH_HToBB_ZToNuNu";
        
        //int arrSize = sizeof(ZH_HToBB_ZToNuNuBackgroundAr)/sizeof(ZH_HToBB_ZToNuNuBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //ZH_HToBB_ZToNuNuBackgroundAr[fileInd]);
    }
    else if (ZH_HToBB_ZToLLTrimmedBackground){
        //datasetType = 66;
        saveName = "ZH_HToBB_ZToLL";
        
        //int arrSize = sizeof(ZH_HToBB_ZToLLBackgroundAr)/sizeof(ZH_HToBB_ZToLLBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //ZH_HToBB_ZToLLBackgroundAr[fileInd]);
    }
    else if (ZH_HToBB_ZToQQTrimmedBackground){
        //datasetType = 67;
        saveName = "ZH_HToBB_ZToQQ";
        
        //int arrSize = sizeof(ZH_HToBB_ZToQQBackgroundAr)/sizeof(ZH_HToBB_ZToQQBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //ZH_HToBB_ZToQQBackgroundAr[fileInd]);
    }
    else if (ggZH_HToBB_ZToBBTrimmedBackground){
        //datasetType = 68;
        saveName = "ggZH_HToBB_ZToBB";
        
        //int arrSize = sizeof(ggZH_HToBB_ZToBBBackgroundAr)/sizeof(ggZH_HToBB_ZToBBBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //ggZH_HToBB_ZToBBBackgroundAr[fileInd]);
    }
    else if (ggZH_HToBB_ZToNuNuTrimmedBackground){
        //datasetType = 68;
        saveName = "ggZH_HToBB_ZToNuNu";
        
        //int arrSize = sizeof(ggZH_HToBB_ZToNuNuBackgroundAr)/sizeof(ggZH_HToBB_ZToNuNuBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //ggZH_HToBB_ZToNuNuBackgroundAr[fileInd]);
    }
    else if (ggZH_HToBB_ZToLLTrimmedBackground){
        //datasetType = 68;
        saveName = "ggZH_HToBB_ZToLL";
        
        //int arrSize = sizeof(ggZH_HToBB_ZToLLBackgroundAr)/sizeof(ggZH_HToBB_ZToLLBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //ggZH_HToBB_ZToLLBackgroundAr[fileInd]);
    }
    else if (ggZH_HToBB_ZToQQTrimmedBackground){
        //datasetType = 69;
        saveName = "ggZH_HToBB_ZToQQ";
        
        //int arrSize = sizeof(ggZH_HToBB_ZToQQBackgroundAr)/sizeof(ggZH_HToBB_ZToQQBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //ggZH_HToBB_ZToQQBackgroundAr[fileInd]);
    }
    else if (EWKZ2Jets_ZToLLTrimmedBackground){
        //datasetType = 70;
        saveName = "EWKZ2Jets_ZToLL";
        
        //int arrSize = sizeof(EWKZ2Jets_ZToLLBackgroundAr)/sizeof(EWKZ2Jets_ZToLLBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //EWKZ2Jets_ZToLLBackgroundAr[fileInd]);
    }
    else if (EWKZ2Jets_ZToNuNuTrimmedBackground){
        //datasetType = 71;
        saveName = "EWKZ2Jets_ZToNuNu";
        
        //int arrSize = sizeof(EWKZ2Jets_ZToNuNuBackgroundAr)/sizeof(EWKZ2Jets_ZToNuNuBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //EWKZ2Jets_ZToNuNuBackgroundAr[fileInd]);
    }
    else if (EWKZ2Jets_ZToQQTrimmedBackground){
        //datasetType = 72;
        saveName = "EWKZ2Jets_ZToQQ";
        
        //int arrSize = sizeof(EWKZ2Jets_ZToQQBackgroundAr)/sizeof(EWKZ2Jets_ZToQQBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //EWKZ2Jets_ZToQQBackgroundAr[fileInd]);
    }
    else if (ZZZTrimmedBackground){
        //datasetType = 73;
        saveName = "ZZZ";
        
        //int arrSize = sizeof(ZZZBackgroundAr)/sizeof(ZZZBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //ZZZBackgroundAr[fileInd]);
    }
    else if (testRun){
        saveName = "testRun";
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //"./unweighted_eventspphzzjjQCD0SMHLOOP0NPE1NPcHWE1QEDE5ResMasAllVer100Ev10080Seed_0p999cHW100GeVIMJetCut_200.root");
        
        isBackground = false;
        
    }
    else if (LaraTest){
        saveName = "LaraTest";
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch.root");
        //"/scratch365/dlutton/NanoAODFiles/pp_hwpwmjj_EFT_VBF_chw_09999000_250k.root");
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


    std::string outFileStr = "HLTTrimmedFilteredForAnalysis"+saveName+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root";
    std::cout << "OutFile: " << outFileStr << "\n";
    TFile *outFile = new TFile(outFileStr.c_str(),"RECREATE");

    UInt_t datanEv = 0;
    UInt_t datanEvPass = 0;
    UInt_t evCount = 0;
    UInt_t evRunOver = 0;

    //these aren't even used in this script. no point in being here
    /*
    std::string yearStr;
    if (yearType == 0) yearStr = "Summer19UL18_JRV2_MC";
    else if (yearType == 1) yearStr = "Summer19UL17_JRV2_MC";
    else if (yearType == 2) yearStr = "Summer20UL16_JRV3_MC";
    else if (yearType == 3) yearStr = "Summer20UL16APV_JRV3_MC";
    std::string filePathStr = "../NanoCORE/Tools/jetcorr/data/"+yearStr+"/"+yearStr;
    */

    //instead of having a loop for each text file, just make that many separate instances of the class
    //Array for holding different correction types
    std::string corrType2018Ar[12] = {"FlavorQCD","FlavorQCD","RelativeBal","HF","BBEC1","EC2","Absolute","Absolute_2018","HF_2018","EC2_2018","RelativeSample_2018","BBEC1_2018"};
    std::string corrType2017Ar[12] = {"FlavorQCD","FlavorQCD","RelativeBal","HF","BBEC1","EC2","Absolute","Absolute_2017","HF_2017","EC2_2017","RelativeSample_2017","BBEC1_2017"};
    std::string corrType2016Ar[12] = {"FlavorQCD","FlavorQCD","RelativeBal","HF","BBEC1","EC2","Absolute","Absolute_2016","HF_2016","EC2_2016","RelativeSample_2016","BBEC1_2016"};





    JetCorrectionUncertainty jec18("../NanoCORE/Tools/jetcorr/data/Summer19UL18_V5_MC/RegroupedV2_Summer19UL18_V5_MC_UncertaintySources_AK4PFchs_"+corrType2018Ar[JECCorInd]+".txt");
    JetCorrectionUncertainty jec17("../NanoCORE/Tools/jetcorr/data/Summer19UL17_V5_MC/RegroupedV2_Summer19UL17_V5_MC_UncertaintySources_AK4PFchs_"+corrType2017Ar[JECCorInd]+".txt");

    JetCorrectionUncertainty jec16("../NanoCORE/Tools/jetcorr/data/Summer19UL16_V7_MC/RegroupedV2_Summer19UL16_V7_MC_UncertaintySources_AK4PFchs_"+corrType2016Ar[JECCorInd]+".txt");
    JetCorrectionUncertainty jec16APV("../NanoCORE/Tools/jetcorr/data/Summer19UL16APV_V7_MC/RegroupedV2_Summer19UL16APV_V7_MC_UncertaintySources_AK4PFchs_"+corrType2016Ar[JECCorInd]+".txt");

    //make a vector of pointer to the class instances
    std::vector<JetCorrectionUncertainty*> jecUncAr;
    jecUncAr.push_back(&jec18);
    jecUncAr.push_back(&jec17);
    jecUncAr.push_back(&jec16);
    jecUncAr.push_back(&jec16APV);


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
    //JetsAllCorrections. Whatever the JECInd, JECCorUpOrDown, and JERInd are set to, the resulting jets will be stored in these vectors
    std::vector<Float_t> Jet_eta_FinalL;
    std::vector<Float_t> Jet_pt_FinalL;
    std::vector<Float_t> Jet_phi_FinalL;
    std::vector<Float_t> Jet_mass_FinalL;

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
    //JetsAllCorrections. Whatever the JECInd, JECCorUpOrDown, and JERInd are set to, the resulting jets will be stored in these vectors
    std::vector<Float_t> FatJet_eta_FinalL;
    std::vector<Float_t> FatJet_pt_FinalL;
    std::vector<Float_t> FatJet_phi_FinalL;
    std::vector<Float_t> FatJet_mass_FinalL;


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
    std::vector<Float_t> Muon_RochCorUncL;

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

    std::vector<Int_t> FatJet_hadronFlavourL;

    //HLT 
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
    //PN Regress Mass nominal JMS and JMR plus up/down
    std::vector<Float_t> FatJet_particleNet_mass_JMSNomJMRNomCorL;
    
    


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
    FilteredEventsTree->Branch("Jet_eta_FinalL",&Jet_eta_FinalL);
    FilteredEventsTree->Branch("Jet_pt_FinalL",&Jet_pt_FinalL);
    FilteredEventsTree->Branch("Jet_phi_FinalL",&Jet_phi_FinalL);
    FilteredEventsTree->Branch("Jet_mass_FinalL",&Jet_mass_FinalL);


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
    FilteredEventsTree->Branch("FatJet_eta_FinalL",&FatJet_eta_FinalL);
    FilteredEventsTree->Branch("FatJet_pt_FinalL",&FatJet_pt_FinalL);
    FilteredEventsTree->Branch("FatJet_phi_FinalL",&FatJet_phi_FinalL);
    FilteredEventsTree->Branch("FatJet_mass_FinalL",&FatJet_mass_FinalL);




    

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
    FilteredEventsTree->Branch("Muon_RochCorUncL",&Muon_RochCorUncL);
    


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

    FilteredEventsTree->Branch("FatJet_hadronFlavourL",&FatJet_hadronFlavourL);

    //HLT
    FilteredEventsTree->Branch("HLT_Ele32_WPTight_Gsf_L1DoubleEGL",&HLT_Ele32_WPTight_Gsf_L1DoubleEGL,"HLT_Ele32_WPTight_Gsf_L1DoubleEGL/O");
    FilteredEventsTree->Branch("HLT_IsoMu27L",&HLT_IsoMu27L,"HLT_IsoMu27L/O");
    FilteredEventsTree->Branch("HLT_Mu50L",&HLT_Mu50L,"HLT_Mu50L/O");
    FilteredEventsTree->Branch("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZL",&HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZL,"HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZL/O");
    FilteredEventsTree->Branch("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8L",&HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8L,"HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8L/O");

    //2016
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
    //PN Regress Mass nominal JMS and JMR plus up/down
    FilteredEventsTree->Branch("FatJet_particleNet_mass_JMSNomJMRNomCorL", &FatJet_particleNet_mass_JMSNomJMRNomCorL);

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
    //3d vectors with 1 dimension for pt, 1 for eta, 1 for jet flavor
    //pt dimensions were [0, 30, 50, 70, 100, 140, 200, 300, 600, 1000]
    //03032024 change 9 bins from 0 to 270 [0, 30, 60, 90, 120, 150, 180, 210, 240, 270]
    //here the inds were for [0,30), [30,50), ... [600,1000), [1000,inf)
    //now the inds are for [0,30), [30,60), ... [240,270), [270,300), [300,inf)
    //eta dimensions were [0,2.5]
    //Now 4 bins from 0 to 2.5 [0, 0.625, 1.25, 1.875, 2.5]
    //here the inds were for [0,2.5), [2.5,inf)
    //Now for [0,0.625), [0.625,1.25), [1.25,1.875), [1.875,2.5)]
    //no 2.5 to inf. btagging cuts those jets anyway
    //flavor dimensions are [0,4,5]
    //here the inds are for ==0, ==4, ==5
    //initialize here
    //Create branches and tree for btagging efficiencies
    std::vector<std::vector<std::vector<Int_t>>> nJetsCtrL;
    std::vector<std::vector<std::vector<Int_t>>> nJetsPassBtagCtrL;
    //3d vector of btagging efficiencies
    std::vector<std::vector<std::vector<Double_t>>> btagEffL;
    /*
    TTree *btagEffTree = new TTree("btagEffTree","btagEffTree");
    btagEffTree->Branch("nJetsCtrL",&nJetsCtrL);
    btagEffTree->Branch("nJetsPassBtagCtrL",&nJetsPassBtagCtrL);
    btagEffTree->Branch("btagEffL",&btagEffL);
    */
    //fill the 3d vectors with 0s
    int nPtBins = 10;
    int nEtaBins = 4;
    int nFlavorBins = 3;
    for (int i=0; i<nPtBins; i++){
        std::vector<std::vector<int>> nJetsCtrL2;
        std::vector<std::vector<int>> nJetsPassBtagCtrL2;
        std::vector<std::vector<double>> btagEffL2;
        for (int j=0; j<nEtaBins; j++){
            std::vector<int> nJetsCtrL3;
            std::vector<int> nJetsPassBtagCtrL3;
            std::vector<double> btagEffL3;
            for (int k=0; k<nFlavorBins; k++){
                nJetsCtrL3.push_back(0);
                nJetsPassBtagCtrL3.push_back(0);
                btagEffL3.push_back(0.);
            }
            nJetsCtrL2.push_back(nJetsCtrL3);
            nJetsPassBtagCtrL2.push_back(nJetsPassBtagCtrL3);
            btagEffL2.push_back(btagEffL3);
        }
        nJetsCtrL.push_back(nJetsCtrL2);
        nJetsPassBtagCtrL.push_back(nJetsPassBtagCtrL2);
        btagEffL.push_back(btagEffL2);
    }

    //array for pt dimensions
    //std::vector<double> ptBins = {0, 30, 50, 70, 100, 140, 200, 300, 600, 1000};
    std::vector<double> ptBins = {0, 30, 60, 90, 120, 150, 180, 210, 240, 270};
    //array for eta dimensions
    //std::vector<double> etaBins = {0,2.5};
    std::vector<double> etaBins = {0, 0.625, 1.25, 1.875};
    //array for flavor dimensions
    std::vector<int> flavorBins = {0,4,5};

    


    //Tight cuts
    
    float bTagUL18Cut = 0.7100;
    float bTagUL17Cut = 0.7476;
    float bTagUL16Cut = 0.6377;
    float bTagUL16APVCut = 0.6502;
    //medium cuts
    /*
    float bTagUL18Cut = 0.2783;
    float bTagUL17Cut = 0.3040;
    float bTagUL16Cut = 0.2489;
    float bTagUL16APVCut = 0.2598;
    */
    //Vector of btag cuts
    std::vector<float> bTagCuts = {bTagUL18Cut,bTagUL17Cut,bTagUL16Cut,bTagUL16APVCut};

    float bTagCutToUse = bTagCuts[yearType];


    

    std::cout << "Going into file loop.\n";

    for (UInt_t k=0; k<fileAr.size(); k++){
        if (endAfter && evCount > NToEnd) break;
        if (debug) std::cout<<"File:    "<<fileAr[k]<<"\n";
        //Open the file, get the Events tree
        TFile* tmpfile = TFile::Open(fileAr[k].c_str());
        //outFile->cd();
        TTreeReader myEventsReader("FilteredEventsTree", tmpfile);


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

        //Jets with JER applied
        TTreeReaderArray<Float_t> Jet_eta_JERMid(myEventsReader, "Jet_eta_JERMidL");
        TTreeReaderArray<Float_t> Jet_pt_JERMid(myEventsReader, "Jet_pt_JERMidL");
        TTreeReaderArray<Float_t> Jet_phi_JERMid(myEventsReader, "Jet_phi_JERMidL");
        TTreeReaderArray<Float_t> Jet_mass_JERMid(myEventsReader, "Jet_mass_JERMidL");
        TTreeReaderArray<Float_t> Jet_eta_JERUp(myEventsReader, "Jet_eta_JERUpL");
        TTreeReaderArray<Float_t> Jet_pt_JERUp(myEventsReader, "Jet_pt_JERUpL");
        TTreeReaderArray<Float_t> Jet_phi_JERUp(myEventsReader, "Jet_phi_JERUpL");
        TTreeReaderArray<Float_t> Jet_mass_JERUp(myEventsReader, "Jet_mass_JERUpL");
        TTreeReaderArray<Float_t> Jet_eta_JERDown(myEventsReader, "Jet_eta_JERDownL");
        TTreeReaderArray<Float_t> Jet_pt_JERDown(myEventsReader, "Jet_pt_JERDownL");
        TTreeReaderArray<Float_t> Jet_phi_JERDown(myEventsReader, "Jet_phi_JERDownL");
        TTreeReaderArray<Float_t> Jet_mass_JERDown(myEventsReader, "Jet_mass_JERDownL");

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
        //Jets with JER applied
        TTreeReaderArray<Float_t> FatJet_eta_JERMid(myEventsReader, "FatJet_eta_JERMidL");
        TTreeReaderArray<Float_t> FatJet_pt_JERMid(myEventsReader, "FatJet_pt_JERMidL");
        TTreeReaderArray<Float_t> FatJet_phi_JERMid(myEventsReader, "FatJet_phi_JERMidL");
        TTreeReaderArray<Float_t> FatJet_mass_JERMid(myEventsReader, "FatJet_mass_JERMidL");
        TTreeReaderArray<Float_t> FatJet_eta_JERUp(myEventsReader, "FatJet_eta_JERUpL");
        TTreeReaderArray<Float_t> FatJet_pt_JERUp(myEventsReader, "FatJet_pt_JERUpL");
        TTreeReaderArray<Float_t> FatJet_phi_JERUp(myEventsReader, "FatJet_phi_JERUpL");
        TTreeReaderArray<Float_t> FatJet_mass_JERUp(myEventsReader, "FatJet_mass_JERUpL");
        TTreeReaderArray<Float_t> FatJet_eta_JERDown(myEventsReader, "FatJet_eta_JERDownL");
        TTreeReaderArray<Float_t> FatJet_pt_JERDown(myEventsReader, "FatJet_pt_JERDownL");
        TTreeReaderArray<Float_t> FatJet_phi_JERDown(myEventsReader, "FatJet_phi_JERDownL");
        TTreeReaderArray<Float_t> FatJet_mass_JERDown(myEventsReader, "FatJet_mass_JERDownL");


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
        TTreeReaderArray<Float_t> Muon_RochMomCorrections(myEventsReader, "Muon_RochMomCorrectionsL");
        TTreeReaderArray<Float_t> Muon_ptCorrected(myEventsReader, "Muon_ptCorrectedL");
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

        TTreeReaderArray<Int_t> FatJet_hadronFlavour(myEventsReader, "FatJet_hadronFlavourL");

        //HLT

        TTreeReaderValue<Bool_t> HLT_Ele32_WPTight_Gsf_L1DoubleEG(myEventsReader, "HLT_Ele32_WPTight_Gsf_L1DoubleEGL");
        TTreeReaderValue<Bool_t> HLT_IsoMu27(myEventsReader, "HLT_IsoMu27L");
        TTreeReaderValue<Bool_t> HLT_Mu50(myEventsReader, "HLT_Mu50L");
        TTreeReaderValue<Bool_t> HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ(myEventsReader, "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZL");
        TTreeReaderValue<Bool_t> HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8(myEventsReader, "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8L");

        TTreeReaderValue<Bool_t> HLT_Ele27_WPTight_Gsf(myEventsReader,"HLT_Ele27_WPTight_GsfL");
        TTreeReaderValue<Bool_t> HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ(myEventsReader,"HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZL");


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
                std::cout << evCount+1 << " starting muon loop\n";
            }
            //Increment event count
            evRunOver += 1;
            evCount += 1;

            std::vector<Float_t> Muon_RochCorUnc;

            //check if doing an uncertainty of the rochester correction
            if (RochInd > 0){

                

                //Loop through muons and calculate rochester correction uncertainty
                for (int i = 0; i < *nMuon; i++){
                    int genPartIdx = Muon_genPartIdx[i];
                    double mcSFUnc;
                    double mcSFErr;
                    int charge = Muon_charge[i];
                    float pt = Muon_pt[i];
                    float eta = Muon_eta[i];
                    float phi = Muon_phi[i];
                    float u = gRandom->Rndm();
                    int nl = Muon_nTrackerLayers[i];
                    //Create vector in case that error set is Stat
                    std::vector<Float_t> rochMomCorrectionsStat;
                    if (RochInd != 1){
                        //Get gRandom for function
                        
                        //Check if muon has a genmatch
                        if (genPartIdx == -1) {
                            //no gen match, use kSmearMC with random u
                            mcSFUnc = rc.kSmearMC(charge, pt, eta, phi, nl, u, RochInd, 0);
                        }
                        else{
                            float genPt = GenPart_pt[genPartIdx];
                            //Get rochester correction with kSpreadMC
                            mcSFUnc = rc.kSpreadMC(charge, pt, eta, phi, genPt, RochInd, 0);
                        }
                        //mcSFUnc = rc.kScaleDT(charge, pt, eta, phi, RochInd, 0);
                    }
                    else{ //loop through all 100 error members and store them in a vector
                        for (int j = 0; j < 100; j++){
                            //Check if muon has a genmatch
                            if (genPartIdx == -1) {
                                //no gen match, use kSmearMC with random u
                                mcSFErr = rc.kSmearMC(charge, pt, eta, phi, nl, u, RochInd, j);
                            }
                            else{
                                float genPt = GenPart_pt[genPartIdx];
                                //Get rochester correction with kSpreadMC
                                mcSFErr = rc.kSpreadMC(charge, pt, eta, phi, genPt, RochInd, j);
                            }
                            //mcSFErr = rc.kScaleDT(charge, pt, eta, phi, RochInd, j);
                            rochMomCorrectionsStat.push_back(mcSFErr);
                        }
                        //Get the mean and standard deviation of the vector
                        float mean = TMath::Mean(rochMomCorrectionsStat.begin(), rochMomCorrectionsStat.end());
                        float stdDev = TMath::StdDev(rochMomCorrectionsStat.begin(), rochMomCorrectionsStat.end());
                        /*
                        //Get a random number from a gaussian with the mean and std dev
                        TRandom3 *r = new TRandom3();
                        mcSF = r->Gaus(mean, stdDev);
                        */
                        mcSFUnc = stdDev;
                    }
                    Muon_RochCorUnc.push_back(mcSFUnc);
                    
                    
                }
                
                
            }
            else {
                //If not, just set unc to 0
                for (int i = 0; i < *nMuon; i++){
                    Muon_RochCorUnc.push_back(0);
                }
            }

            //initialize a vector of Pt for the jets
            std::vector<Float_t> jetAllCorPtVec;
            std::vector<Float_t> AK8jetAllCorPtVec;
            //also the other kinematics
            std::vector<Float_t> jetAllCorEtaVec;
            std::vector<Float_t> jetAllCorPhiVec;
            std::vector<Float_t> jetAllCorMassVec;
            std::vector<Float_t> AK8jetAllCorEtaVec;
            std::vector<Float_t> AK8jetAllCorPhiVec;
            std::vector<Float_t> AK8jetAllCorMassVec;

            //If JECCorInd > 0, then apply JECs
            if (JECCorInd > 0){
                //Loop through jets and apply JECs
                for (int i = 0; i < *nJet; i++){
                    //Get the jet pt, eta, phi, and mass
                    float pt = Jet_pt_JERMid[i];
                    float eta = Jet_eta_JERMid[i];
                    float phi = Jet_phi_JERMid[i];
                    float mass = Jet_mass_JERMid[i];
                    //transfer the other kinematics
                    jetAllCorEtaVec.push_back(eta);
                    jetAllCorPhiVec.push_back(phi);
                    jetAllCorMassVec.push_back(mass);
                    
                    
                    //Get the JEC uncertainty
                    if (jecUncAr[yearType] == NULL){
                        std::cout << "jecUncAr[" << yearType << "] is NULL\n";
                        break;
                    }
                    jecUncAr[yearType]->setJetPt(pt);
                    jecUncAr[yearType]->setJetEta(eta);
                    //get unc
                    double unc = jecUncAr[yearType]->getUncertainty(JECCorUpOrDown);
                    double JEC;
                    if (JECCorUpOrDown){
                        JEC = 1. - unc;
                    }
                    else {
                        JEC = 1. + unc;
                    }
                    float tmpPt = pt * JEC;
                    //mass *= JEC;
                    //Do HEM15/16 correction
                    float finalPt;
                    if (yearType == 2018){
                        if(phi > -1.57 && phi < -0.87) {
                            if (eta > -3.0 && eta < -2.5){
                                if (tmpPt > 15 && Jet_jetId[i] == 6){
                                    finalPt = tmpPt * 0.65;
                                }
                                else {
                                    finalPt = tmpPt;
                                }
                            }
                            else if (eta > -2.5 && eta < -1.3){
                                if (tmpPt > 15 && Jet_jetId[i] == 6){
                                    finalPt = tmpPt * 0.8;
                                }
                                else {
                                    finalPt = tmpPt;
                                }
                            }
                            else {
                                finalPt = tmpPt;
                            }
                        }
                        else {
                            finalPt = tmpPt;
                        }
                    }
                    else {
                        finalPt = tmpPt;
                    }
                    jetAllCorPtVec.push_back(finalPt);
                    
                }
                //Now AK8 jets
                for (int i = 0; i < *nFatJet; i++){
                    //Get the jet pt, eta, phi, and mass
                    float pt = FatJet_pt_JERMid[i];
                    float eta = FatJet_eta_JERMid[i];
                    float phi = FatJet_phi_JERMid[i];
                    float mass = FatJet_mass_JERMid[i];
                    //transfer the other kinematics
                    AK8jetAllCorEtaVec.push_back(eta);
                    AK8jetAllCorPhiVec.push_back(phi);
                    AK8jetAllCorMassVec.push_back(mass);
                    
                    //Get the JEC uncertainty
                    if (jecUncAr[yearType] == NULL){
                        std::cout << "jecUncAr[" << yearType << "] is NULL\n";
                        break;
                    }
                    //Get the JEC uncertainty
                    jecUncAr[yearType]->setJetPt(pt);
                    jecUncAr[yearType]->setJetEta(eta);
                    //get unc
                    double unc = jecUncAr[yearType]->getUncertainty(JECCorUpOrDown);
                    double JEC;
                    if (JECCorUpOrDown){
                        JEC = 1. - unc;
                    }
                    else {
                        JEC = 1. + unc;
                    }
                    float tmpPt = pt * JEC;
                    AK8jetAllCorPtVec.push_back(tmpPt);
                }
            }
            else if (JERInd > 0){
                //if JERInd > 0, then use JER Up for 1 and JER Down for 2
                //Loop through jets and apply JERs
                for (int i = 0; i < *nJet; i++){
                    //transfer the kinematics
                    float tmpPt;
                    float eta;
                    float phi;
                    float mass;
                    if (JERInd == 1){
                        //jetAllCorPtVec.push_back(Jet_pt_JERUp[i]);
                        tmpPt = Jet_pt_JERUp[i];
                        eta = Jet_eta_JERUp[i];
                        phi = Jet_phi_JERUp[i];
                        mass = Jet_mass_JERUp[i];
                        jetAllCorEtaVec.push_back(Jet_eta_JERUp[i]);
                        jetAllCorPhiVec.push_back(Jet_phi_JERUp[i]);
                        jetAllCorMassVec.push_back(Jet_mass_JERUp[i]);
                    }
                    else {
                        //jetAllCorPtVec.push_back(Jet_pt_JERDown[i]);
                        tmpPt = Jet_pt_JERDown[i];
                        eta = Jet_eta_JERDown[i];
                        phi = Jet_phi_JERDown[i];
                        mass = Jet_mass_JERDown[i];
                        jetAllCorEtaVec.push_back(Jet_eta_JERDown[i]);
                        jetAllCorPhiVec.push_back(Jet_phi_JERDown[i]);
                        jetAllCorMassVec.push_back(Jet_mass_JERDown[i]);
                    }
                    float finalPt;
                    if (yearType == 2018){
                        if(phi > -1.57 && phi < -0.87) {
                            if (eta > -3.0 && eta < -2.5){
                                if (tmpPt > 15 && Jet_jetId[i] == 6){
                                    finalPt = tmpPt * 0.65;
                                }
                                else {
                                    finalPt = tmpPt;
                                }
                            }
                            else if (eta > -2.5 && eta < -1.3){
                                if (tmpPt > 15 && Jet_jetId[i] == 6){
                                    finalPt = tmpPt * 0.8;
                                }
                                else {
                                    finalPt = tmpPt;
                                }
                            }
                            else {
                                finalPt = tmpPt;
                            }
                        }
                        else {
                            finalPt = tmpPt;
                        }
                    }
                    else {
                        finalPt = tmpPt;
                    }
                    jetAllCorPtVec.push_back(finalPt);
                    
                }
                //Now AK8 jets
                for (int i = 0; i < *nFatJet; i++){
                    //transfer the kinematics
                    if (JERInd == 1){
                        AK8jetAllCorPtVec.push_back(FatJet_pt_JERUp[i]);
                        AK8jetAllCorEtaVec.push_back(FatJet_eta_JERUp[i]);
                        AK8jetAllCorPhiVec.push_back(FatJet_phi_JERUp[i]);
                        AK8jetAllCorMassVec.push_back(FatJet_mass_JERUp[i]);
                    }
                    else {
                        AK8jetAllCorPtVec.push_back(FatJet_pt_JERDown[i]);
                        AK8jetAllCorEtaVec.push_back(FatJet_eta_JERDown[i]);
                        AK8jetAllCorPhiVec.push_back(FatJet_phi_JERDown[i]);
                        AK8jetAllCorMassVec.push_back(FatJet_mass_JERDown[i]);
                    }
                }

            }
            else {
                //If not, just transfer the kinematics for JERMid unchanged
                for (int i = 0; i < *nJet; i++){
                    float tmpPt = Jet_pt_JERMid[i];
                    float eta = Jet_eta_JERMid[i];
                    float phi = Jet_phi_JERMid[i];
                    float mass = Jet_mass_JERMid[i];
                    //jetAllCorPtVec.push_back(Jet_pt_JERMid[i]);
                    float finalPt;
                    if (yearType == 2018){
                        if(phi > -1.57 && phi < -0.87) {
                            if (eta > -3.0 && eta < -2.5){
                                if (tmpPt > 15 && Jet_jetId[i] == 6){
                                    finalPt = tmpPt * 0.65;
                                }
                                else {
                                    finalPt = tmpPt;
                                }
                            }
                            else if (eta > -2.5 && eta < -1.3){
                                if (tmpPt > 15 && Jet_jetId[i] == 6){
                                    finalPt = tmpPt * 0.8;
                                }
                                else {
                                    finalPt = tmpPt;
                                }
                            }
                            else {
                                finalPt = tmpPt;
                            }
                        }
                        else {
                            finalPt = tmpPt;
                        }
                    }
                    else {
                        finalPt = tmpPt;
                    }
                    jetAllCorPtVec.push_back(finalPt);
                    jetAllCorEtaVec.push_back(Jet_eta_JERMid[i]);
                    jetAllCorPhiVec.push_back(Jet_phi_JERMid[i]);
                    jetAllCorMassVec.push_back(Jet_mass_JERMid[i]);
                }
                for (int i = 0; i < *nFatJet; i++){
                    AK8jetAllCorPtVec.push_back(FatJet_pt_JERMid[i]);
                    AK8jetAllCorEtaVec.push_back(FatJet_eta_JERMid[i]);
                    AK8jetAllCorPhiVec.push_back(FatJet_phi_JERMid[i]);
                    AK8jetAllCorMassVec.push_back(FatJet_mass_JERMid[i]);
                }
            }

            



            //Calculate the BTagging efficiency
            //Using "AllCor" vectors, loop through jets, check if btagged
            
            for (UInt_t jetInd=0; jetInd<*nJet;jetInd++){
                bool passesCut = false;
                float jetPt = jetAllCorPtVec[jetInd];
                float jetEta = jetAllCorEtaVec[jetInd];
                if (jetPt >= 30){
                    
                    if (abs(jetEta) <= 2.5){
                        passesCut = true;
                    }
                }
                float tmpJetBTag = Jet_btagDeepFlavB[jetInd];
                if (passesCut){
                    //get pt, eta, and flavor dimensions
                    int ptInd = 0;
                    int etaInd = 0;
                    int flavInd = 0;
                    //get pt ind, remember, last bin is [1000,inf)] NOTE: NOW [270,inf)]
                    //so have to do special check for that
                    if (jetPt >= ptBins[ptBins.size()-1]){
                        ptInd = ptBins.size()-1;
                    }
                    else {
                        for (UInt_t ptIndItr=0; ptIndItr<ptBins.size()-1;ptIndItr++){
                            if (jetPt >= ptBins[ptIndItr] && jetPt < ptBins[ptIndItr+1]){
                                ptInd = ptIndItr;
                                break;
                            }
                        }
                    }
                    //now eta. same thing
                    if (abs(jetEta) >= etaBins[etaBins.size()-1]){
                        etaInd = etaBins.size()-1;
                    }
                    else {
                        for (UInt_t etaIndItr=0; etaIndItr<etaBins.size()-1;etaIndItr++){
                            if (abs(jetEta) >= etaBins[etaIndItr] && abs(jetEta) < etaBins[etaIndItr+1]){
                                etaInd = etaIndItr;
                                break;
                            }
                        }
                    }
                    //now flavor, just check if equal to 0, 4, 5. if none, then debug
                    if (Jet_hadronFlavour[jetInd] == 0){
                        flavInd = 0;
                    }
                    else if (Jet_hadronFlavour[jetInd] == 4){
                        flavInd = 1;
                    }
                    else if (Jet_hadronFlavour[jetInd] == 5){
                        flavInd = 2;
                    }
                    else {
                        std::cout << "Jet_hadronFlavour[" << jetInd << "] = " << Jet_hadronFlavour[jetInd] << "!!!!!!!!!\n";
                        break;
                    }
                    //increment the total number of jets in the pt, eta, and flavor bin
                    nJetsCtrL[ptInd][etaInd][flavInd] += 1;
                    //Check if passes btagging cut
                    if (tmpJetBTag > bTagCutToUse){
                        //if so, increment the number of btags in the pt, eta, and flavor bin
                        nJetsPassBtagCtrL[ptInd][etaInd][flavInd] += 1;
                    }


                }
            }
                    
            

            //Fill in all branches of TTree

            //Event reweighting
            if (debug){
                std::cout <<"Filling Reweighting\n";
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
                Jet_eta_JERMidL.push_back(Jet_eta_JERMid[nJetItr]);
                Jet_pt_JERMidL.push_back(Jet_pt_JERMid[nJetItr]);
                Jet_phi_JERMidL.push_back(Jet_phi_JERMid[nJetItr]);
                Jet_mass_JERMidL.push_back(Jet_mass_JERMid[nJetItr]);
                Jet_eta_JERUpL.push_back(Jet_eta_JERUp[nJetItr]);
                Jet_pt_JERUpL.push_back(Jet_pt_JERUp[nJetItr]);
                Jet_phi_JERUpL.push_back(Jet_phi_JERUp[nJetItr]);
                Jet_mass_JERUpL.push_back(Jet_mass_JERUp[nJetItr]);
                Jet_eta_JERDownL.push_back(Jet_eta_JERDown[nJetItr]);
                Jet_pt_JERDownL.push_back(Jet_pt_JERDown[nJetItr]);
                Jet_phi_JERDownL.push_back(Jet_phi_JERDown[nJetItr]);
                Jet_mass_JERDownL.push_back(Jet_mass_JERDown[nJetItr]);
                Jet_eta_FinalL.push_back(jetAllCorEtaVec[nJetItr]);
                Jet_pt_FinalL.push_back(jetAllCorPtVec[nJetItr]);
                Jet_phi_FinalL.push_back(jetAllCorPhiVec[nJetItr]);
                Jet_mass_FinalL.push_back(jetAllCorMassVec[nJetItr]);



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
                FatJet_eta_JERMidL.push_back(FatJet_pt_JERMid[nFatJetItr]);
                FatJet_pt_JERMidL.push_back(FatJet_pt_JERMid[nFatJetItr]);
                FatJet_phi_JERMidL.push_back(FatJet_phi_JERMid[nFatJetItr]);
                FatJet_mass_JERMidL.push_back(FatJet_mass_JERMid[nFatJetItr]);
                FatJet_eta_JERUpL.push_back(FatJet_eta_JERUp[nFatJetItr]);
                FatJet_pt_JERUpL.push_back(FatJet_pt_JERUp[nFatJetItr]);
                FatJet_phi_JERUpL.push_back(FatJet_phi_JERUp[nFatJetItr]);
                FatJet_mass_JERUpL.push_back(FatJet_mass_JERUp[nFatJetItr]);
                FatJet_eta_JERDownL.push_back(FatJet_eta_JERDown[nFatJetItr]);
                FatJet_pt_JERDownL.push_back(FatJet_pt_JERDown[nFatJetItr]);
                FatJet_phi_JERDownL.push_back(FatJet_phi_JERDown[nFatJetItr]);
                FatJet_mass_JERDownL.push_back(FatJet_mass_JERDown[nFatJetItr]);
                FatJet_eta_FinalL.push_back(AK8jetAllCorEtaVec[nFatJetItr]);
                FatJet_pt_FinalL.push_back(AK8jetAllCorPtVec[nFatJetItr]);
                FatJet_phi_FinalL.push_back(AK8jetAllCorPhiVec[nFatJetItr]);
                FatJet_mass_FinalL.push_back(AK8jetAllCorMassVec[nFatJetItr]);

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
                Muon_RochMomCorrectionsL.push_back(Muon_RochMomCorrections[nMuonItr]);
                Muon_ptCorrectedL.push_back(Muon_ptCorrected[nMuonItr]);
                Muon_RochCorUncL.push_back(Muon_RochCorUnc[nMuonItr]);

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

            //HLT

            if (debug){
                std::cout <<"Filling HLT\n";
            }
            HLT_Ele32_WPTight_Gsf_L1DoubleEGL = *HLT_Ele32_WPTight_Gsf_L1DoubleEG;
            HLT_IsoMu27L = *HLT_IsoMu27;
            HLT_Mu50L = *HLT_Mu50;
            HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZL = *HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;
            HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8L = *HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8;

            HLT_Ele27_WPTight_GsfL = *HLT_Ele27_WPTight_Gsf;
            HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZL = *HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ;

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

            for (UInt_t nFatJetItr=0; nFatJetItr<nFatJetL;nFatJetItr++){

                FatJet_particleNet_mass_JMSNomJMRNomCorL.push_back(FatJet_particleNet_mass_JMSNomJMRNomCor[nFatJetItr]);

            }

            


            FilteredEventsTree->Fill();

            //Clear all vectors


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
            Jet_eta_FinalL.clear();
            Jet_pt_FinalL.clear();
            Jet_phi_FinalL.clear();
            Jet_mass_FinalL.clear();

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
            FatJet_eta_FinalL.clear();
            FatJet_pt_FinalL.clear();
            FatJet_phi_FinalL.clear();
            FatJet_mass_FinalL.clear();

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
            Muon_RochCorUncL.clear();

            FatJet_particleNet_HbbvsQCDL.clear();
            FatJet_particleNet_ZvsQCDL.clear();

            FatJet_particleNetMD_QCDL.clear();
            FatJet_particleNetMD_XbbL.clear();
            FatJet_particleNetMD_XccL.clear();
            FatJet_particleNetMD_XqqL.clear();

            Jet_puIdL.clear();

            PSWeightL.clear();
            LHEScaleWeightL.clear();
            LHEPdfWeightL.clear();

            //05052024 Additions for PN regress mass scaling and resolution corrections
            FatJet_particleNet_mass_JMSNomJMRNomCorL.clear();



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

    //calculate btag efficiency
    std::cout << "Calculating btag efficiency\n";
    //loop through pt, eta, and flavor bins
    for (UInt_t ptInd=0; ptInd<ptBins.size();ptInd++){
        for (UInt_t etaInd=0; etaInd<etaBins.size();etaInd++){
            for (UInt_t flavInd=0; flavInd<flavorBins.size();flavInd++){
                //get the number of jets in the bin
                float nJets = nJetsCtrL[ptInd][etaInd][flavInd];
                //get the number of btags in the bin
                float nBtags = nJetsPassBtagCtrL[ptInd][etaInd][flavInd];
                //calculate the efficiency
                float eff = 0;
                if (nJets != 0){
                    eff = nBtags/nJets;
                }
                
                //store the efficiency
                btagEffL[ptInd][etaInd][flavInd] = eff;
                //std::cout << "ptInd: " << ptInd << " etaInd: " << etaInd << " flavInd: " << flavInd << " nJets: " << nJets << " nBtags: " << nBtags << " eff: " << eff << "\n";
            }
        }
    }
    /*
    //Fill the btagEffTree
    std::cout << "Filling btagEffTree\n";
    btagEffTree->Fill();
    //clear the vectors
    btagEffL.clear();
    nJetsCtrL.clear();
    nJetsPassBtagCtrL.clear();
    */
    //Only need to do the btag efficiencies for the nominal case
    //so ignore unless JECCorInd == 0, RochInd == 0, JERInd == 0
    if (JECCorInd == 0 && RochInd == 0 && JERInd == 0){
        // Open a file for writing
        std::ofstream btagOutFile("btag_eff_"+saveName+yearNameStr+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".py");

        // Check if the file is open
        if (!btagOutFile.is_open()) {
            std::cout << "Failed to open the file for writing." << std::endl;
        }

        // Dimensions of the 3D vector
        //const int dim1 = 10, dim2 = 2, dim3 = 3;
        const int dim1 = ptBins.size(), dim2 = etaBins.size(), dim3 = flavorBins.size();
        btagOutFile << "nJetsCtrAr_" + saveName+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+" = [";
        

        // Write the 3D vector to the file
        for (int i = 0; i < dim1; ++i) {
            btagOutFile << "[";
            for (int j = 0; j < dim2; ++j) {
                btagOutFile << "[";
                for (int k = 0; k < dim3; ++k) {
                    //if (k == 0) btagOutFile << "[";
                    btagOutFile << nJetsCtrL[i][j][k];
                    if (k < dim3 - 1) btagOutFile << ",";
                }
                btagOutFile << "]";
                if (j < dim2 - 1) btagOutFile << ",";
            }
            btagOutFile << "]";
            if (i < dim1 -1) btagOutFile << ",";
        }
        btagOutFile << "]\n";

        btagOutFile << "nJetsPassBtagCtrAr_" +saveName+ std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+" = [";
        for (int i = 0; i < dim1; ++i) {
            btagOutFile << "[";
            for (int j = 0; j < dim2; ++j) {
                btagOutFile << "[";
                for (int k = 0; k < dim3; ++k) {
                    //if (k == 0) btagOutFile << "[";
                    btagOutFile << nJetsPassBtagCtrL[i][j][k];
                    if (k < dim3 - 1) btagOutFile << ",";
                }
                btagOutFile << "]";
                if (j < dim2 - 1) btagOutFile << ",";
            }
            btagOutFile << "]";
            if (i < dim1 -1) btagOutFile << ",";
        }
        btagOutFile << "]\n";


        btagOutFile << "btagEffAr_" +saveName+ std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+" = [";

        for (int i = 0; i < dim1; ++i) {
            btagOutFile << "[";
            for (int j = 0; j < dim2; ++j) {
                btagOutFile << "[";
                for (int k = 0; k < dim3; ++k) {
                    //if (k == 0) btagOutFile << "[";
                    btagOutFile << btagEffL[i][j][k];
                    if (k < dim3 - 1) btagOutFile << ",";
                }
                btagOutFile << "]";
                if (j < dim2 - 1) btagOutFile << ",";
            }
            btagOutFile << "]";
            if (i < dim1 -1) btagOutFile << ",";
        }
        btagOutFile << "]";

        // Close the file
        btagOutFile.close();
    }




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
    //btagEffTree->Write("",TObject::kOverwrite);

    outFile->Close();
    

    delete outFile;

}