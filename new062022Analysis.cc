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


void new062022Analysis(string datasetString){
    // Open the file. Note that the name of your file outside this class
    // will probably NOT be experiment.root.
    std::cout << "start Analysis\n";
    clock_t startt = clock();
    //Analyzer will run over all files put into fileAr

    std::vector<std::string> fileAr;

    //Gen Jet matching dR cut

    float genMatchdRCut;
    std::string cutName;

    if (useTighterCut) {
        genMatchdRCut = 0.1;
        cutName = "TighterCut";
    }
    else {
        genMatchdRCut = 0.4;
        cutName = "";
    }


    std::string saveName;
    float crossSection;
    bool isBackground;
    bool useLHETree = false;
    bool useFJGenMatchTree = false;
    bool useJGenMatchTree = false;

    if (datasetString == "testRun") testRun = true;
    if (datasetString == "SDC2V3MC") SDC2V3MC = true;
    if (datasetString == "C2VEtaDifCut") MGC2VEtaDifCut = true;
    if (datasetString == "OSix") MGOSix = true;
    if (datasetString == "OSixEtaDifCut") MGOSixEtaDifCut = true;
    if (datasetString == "OHBox") MGOHBox = true;
    if (datasetString == "OHBoxEtaDifCut") MGOHBoxEtaDifCut = true;
    if (datasetString == "OHDD") MGOHDD = true;
    if (datasetString == "OHDDEtaDifCut") MGOHDDEtaDifCut = true;
    if (datasetString == "OHW") MGOHW = true;
    if (datasetString == "SM") MGSM = true;
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

    if (datasetString == "LaraTest") LaraTest = true;

    ////////////////////////////////GETTING DATASET////////////////////////////////
    ////////////////////////////////GETTING DATASET////////////////////////////////
    ////////////////////////////////GETTING DATASET////////////////////////////////
    ////////////////////////////////GETTING DATASET////////////////////////////////

    std::string strAdd;
    if (scratchDown) strAdd ="/afs/crc.nd.edu/user/d/dlutton/Public/condorStuff/NanoAODToHistos/tmpHoldForNanoAODWithoutScratch/";
    else strAdd ="/scratch365/dlutton/HLTFilteredFiles/";
    if (localTest) strAdd = "";

    float totWeight = 1;

    if (MGC2VEtaDifCut){
        saveName = "C2VEtaDifCut";
        isBackground = false;
        totWeight = 643.339314999999;
        //std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisC2VEtaDifCut.root";
        std::string tmpStrWithPath = "HLTFilteredForAnalysisC2VEtaDifCut.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2V3MC){
        saveName = "SDC2V3MC";
        totWeight = 1845.172;
        isBackground = false;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisSDC2V3MC.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (MGOSix){
        saveName = "OSix";
        isBackground = false;
        int arrSize = sizeof(MGOSixAr)/sizeof(MGOSixAr[0]);
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisOSix.root";
            fileAr.push_back(tmpStrWithPath);
        }
        useLHETree = true;
        useFJGenMatchTree = true;
    }
    else if (MGOSixEtaDifCut){
        saveName = "OSix_EtaDifCut";
        isBackground = false;
        int arrSize = sizeof(MGOSixEtaDifCutAr)/sizeof(MGOSixEtaDifCutAr[0]);
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisOSix_EtaDifCut.root";
            fileAr.push_back(tmpStrWithPath);
        }
        useLHETree = true;
        useFJGenMatchTree = true;
    }
    else if (MGOHBox){
        saveName = "OHBox";
        isBackground = false;
        int arrSize = sizeof(MGOHBoxAr)/sizeof(MGOHBoxAr[0]);
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisOHBox.root";
            fileAr.push_back(tmpStrWithPath);
        }
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (MGOHBoxEtaDifCut){
        saveName = "OHBox_EtaDifCut";
        isBackground = false;
        int arrSize = sizeof(MGOHBoxEtaDifCutAr)/sizeof(MGOHBoxEtaDifCutAr[0]);
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisOHBox_EtaDifCut.root";
            fileAr.push_back(tmpStrWithPath);
        }
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (MGOHDD){
        saveName = "OHDD";
        isBackground = false;
        int arrSize = sizeof(MGOHDDAr)/sizeof(MGOHDDAr[0]);
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisOHDD.root";
            fileAr.push_back(tmpStrWithPath);
        }
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (MGOHDDEtaDifCut){
        saveName = "OHDD_EtaDifCut";
        isBackground = false;
        int arrSize = sizeof(MGOHDDEtaDifCutAr)/sizeof(MGOHDDEtaDifCutAr[0]);
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisOHDD_EtaDifCut.root";
            fileAr.push_back(tmpStrWithPath);
        }
        useLHETree = true;
        useFJGenMatchTree = true;
        
    }
    else if (MGOHW){
        saveName = "OHW";
        isBackground = false;
        int arrSize = sizeof(MGOHWAr)/sizeof(MGOHWAr[0]);
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisOHW.root";
        fileAr.push_back(tmpStrWithPath);
        
    }
    else if (MGSM){
        saveName = "SM";
        isBackground = false;
        totWeight = 11.713886530000012;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisSM.root";
        fileAr.push_back(tmpStrWithPath);
        
    }
    else if (ttHToBBBackground){
        //saveName = "ttHToBB";
        crossSection = 0.5071*0.582;
        totWeight = 4834432.8;
        saveName = "ttHToBB";
        
        isBackground = true;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisttHToBB.root";
        fileAr.push_back(tmpStrWithPath);
        
    }
    else if (ttZJetsBackground){
        //saveName = "ttZJets";
        
        crossSection = 0.5407;
        saveName = "ttZJets";
        isBackground = true;
        totWeight = 32793821;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisttZJets.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (DYBackground){
        //saveName = "DY";
        
        crossSection = 5364;
        totWeight = 96233326;
        saveName = "DY";

        isBackground = true;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisDY.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (QCDPT170to300Background){
        //saveName = "QCDPT170to300";
        
        crossSection = 103300.0;
        totWeight = 29478000;

        saveName = "QCDPT170to300";
        
        isBackground = true;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisQCDPT170to300.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (QCDPT300to470Background){
        //saveName = "QCDPT300to470";
        
        crossSection = 6826.0;
        totWeight = 57868000;

        saveName = "QCDPT300to470";
        
        isBackground = true;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisQCDPT300to470.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (QCDPT470to600Background){
        //saveName = "QCDPT470to600";
        
        crossSection = 552.6;
        totWeight = 51062083.800000004;
        
        saveName = "QCDPT470to600";

        isBackground = true;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisQCDPT470to600.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (QCDPT600to800Background){
        //saveName = "QCDPT600to800";
        
        crossSection = 156.6;
        totWeight = 66914000;

        saveName = "QCDPT600to800";
        
        isBackground = true;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisQCDPT600to800.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (QCDPT800to1000Background){
        //saveName = "QCDPT800to1000";
        
        crossSection = 26.32;
        totWeight = 36830000;

        saveName = "QCDPT800to1000";
        
        isBackground = true;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisQCDPT800to1000.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (QCDPT1000to1400Background){
        //saveName = "QCDPT1000to1400";
        
        crossSection = 7.5;
        totWeight = 19664000;


        saveName = "QCDPT1000to1400";
        
        isBackground = true;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisQCDPT1000to1400.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (QCDPT1400to1800Background){
        //saveName = "QCDPT1400to1800";
        
        crossSection = 0.6479;
        totWeight = 10982000;

        saveName = "QCDPT1400to1800";
        
        isBackground = true;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisQCDPT1400to1800.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (QCDPT1800to2400Background){
        //saveName = "QCDPT1800to2400";
        
        crossSection = 0.08715;
        totWeight = 5491000;

        saveName = "QCDPT1800to2400";
        
        isBackground = true;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisQCDPT1800to2400.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (QCDPT2400to3200Background){
        //saveName = "QCDPT2400to3200";
        
        crossSection = 0.005242;
        totWeight = 2931000;

        saveName = "QCDPT2400to3200";
        
        isBackground = true;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisQCDPT2400to3200.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (QCDPT3200toInfBackground){
        //saveName = "QCDPT3200toInf";
        
        crossSection = 0.0001349;
        totWeight = 1000000;

        saveName = "QCDPT3200toInf";
        
        isBackground = true;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisQCDPT3200toInf.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (TTJetsBackground){
        //saveName = "QCDPT3200toInf";
        
        crossSection = 722.8;
        totWeight = 610815599000;

        saveName = "TTJets";
        
        isBackground = true;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisTTJets.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (TTToHadronicBackground){
        //saveName = "QCDPT3200toInf";
        
        crossSection = 377.96;

        saveName = "TTToHadronic";
        
        isBackground = true;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisTTToHadronic.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (TTTo2L2NuBackground){
        //saveName = "QCDPT3200toInf";
        
        crossSection = 88.29;

        saveName = "TTTo2L2Nu";
        
        isBackground = true;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisTTTo2L2Nu.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (TTToSemiLeptonicBackground){
        //saveName = "QCDPT3200toInf";
        
        crossSection = 365.34;

        saveName = "TTToSemiLeptonic";
        
        isBackground = true;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisTTToSemiLeptonic.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (ST_s_ChannelBackground){
        //saveName = "QCDPT3200toInf";
        
        crossSection = 3.74;
        totWeight = 68767088;

        saveName = "ST_s_Channel";
        
        isBackground = true;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisST_s_Channel.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (ST_t_ChannelAntiTopBackground){
        //saveName = "QCDPT3200toInf";
        
        crossSection = 69.09;
        totWeight = 6014529940;

        saveName = "ST_t_ChannelAntiTop";
        
        isBackground = true;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisST_t_ChannelAntiTop.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (ST_t_ChannelTopBackground){
        //saveName = "QCDPT3200toInf";
        
        crossSection = 115.3;
        totWeight = 18955976000;

        saveName = "ST_t_ChannelTop";
        
        isBackground = true;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisST_t_ChannelTop.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (ZZTo2Q2NuBackground){
        //saveName = "QCDPT3200toInf";
        
        crossSection = 4.561;
        totWeight = 137620470.60000002;

        saveName = "ZZTo2Q2Nu";
        
        isBackground = true;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisZZTo2Q2Nu.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (WWTo2L2NuBackground){
        //saveName = "QCDPT3200toInf";
        
        crossSection = 10.48;
        totWeight = 110795338.10000001;

        saveName = "WWTo2L2Nu";
        
        isBackground = true;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisWWTo2L2Nu.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (WZTo3LNuBackground){
        //saveName = "QCDPT3200toInf";
        
        crossSection = 5.052;
        totWeight = 83145925.5;

        saveName = "WZTo3LNu";
        
        isBackground = true;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisWZTo3LNu.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (testRun){
        saveName = "testRun";
        fileAr.push_back("./HLTFilteredForAnalysistestRun_0.root");
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
    //Setting up outfile for tree
    /*
    std::string outFileStr = "new032022FullAnalysis"+saveName+cutName+".root";
    std::cout << "OutFile: " << outFileStr << "\n";
    TFile *outFile = new TFile(outFileStr.c_str(),"RECREATE");
    */
    bool checkChannelSplits;
    if (isBackground){
        checkChannelSplits = false;
    }

    ////////////////////////////////DEFINING TREES////////////////////////////////
    ////////////////////////////////DEFINING TREES////////////////////////////////
    ////////////////////////////////DEFINING TREES////////////////////////////////
    ////////////////////////////////DEFINING TREES////////////////////////////////

    ////////////////////////////////DEFINING COUNTERS////////////////////////////////
    ////////////////////////////////NEUTRAL COUNTERS////////////////////////////////

    UInt_t startingCtr = 0;

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
    UInt_t passLepCutInSemiLepChannelCtr = 0;
    UInt_t passSemiLepChannelCtr = 0;
    UInt_t passHadChannelCtr = 0;
    UInt_t passVBFJetsCtr = 0;
    UInt_t passAsLepCtr = 0;
    UInt_t passAsSemiLepCtr = 0;
    UInt_t passAsHadCtr = 0;

    Double_t startingWeightedCtr = 0;
    

    Double_t passHiggsFJWeightedCtr = 0.;
    Double_t passHiggsFJWeightedLepCtr = 0.;
    Double_t passHiggsFJWeightedSemiLepCtr = 0.;
    Double_t passHiggsFJWeightedHadCtr = 0.;
    Double_t passChannelWeightedCtr = 0.;
    Double_t passLepOrSemiLepChannelWeightedCtr = 0.;
    Double_t passLepChannelWeightedCtr = 0.;
    Double_t tryingSemiLepChannelWeightedCtr = 0;
    Double_t passFJInSemiLepChannelWeightedCtr = 0;
    Double_t passEnoughLepsInSemiLepChannelWeightedCtr = 0;
    Double_t passLepCutInSemiLepChannelWeightedCtr = 0;
    Double_t passSemiLepChannelWeightedCtr = 0.;
    Double_t passHadChannelWeightedCtr = 0.;
    Double_t passVBFJetsWeightedCtr = 0.;
    Double_t passAsLepWeightedCtr = 0.;
    Double_t passAsSemiLepWeightedCtr = 0.;
    Double_t passAsHadWeightedCtr = 0.;

    UInt_t passSemiLepLepCutCtr = 0;
    Double_t passSemiLepLepCutWeightedCtr = 0.;

    ////////////////////////////////GEN LEP COUNTERS////////////////////////////////

    UInt_t startingGenLepCtr = 0;

    UInt_t passHiggsFJGenLepCtr = 0;
    UInt_t passHiggsFJLepGenLepCtr = 0;
    UInt_t passHiggsFJSemiLepGenLepCtr = 0;
    UInt_t passHiggsFJHadGenLepCtr = 0;
    UInt_t passChannelGenLepCtr = 0;
    UInt_t passLepOrSemiLepChannelGenLepCtr = 0;
    UInt_t passLepChannelGenLepCtr = 0;
    UInt_t tryingSemiLepChannelGenLepCtr = 0;
    UInt_t passFJInSemiLepChannelGenLepCtr = 0;
    UInt_t passEnoughLepsInSemiLepChannelGenLepCtr = 0;
    UInt_t passLepCutInSemiLepChannelGenLepCtr = 0;
    UInt_t passSemiLepChannelGenLepCtr = 0;
    UInt_t passHadChannelGenLepCtr = 0;
    UInt_t passVBFJetsGenLepCtr = 0;
    UInt_t passAsLepGenLepCtr = 0;
    UInt_t passAsSemiLepGenLepCtr = 0;
    UInt_t passAsHadGenLepCtr = 0;
    
    Double_t startingGenLepWeightedCtr = 0;

    Double_t passHiggsFJGenLepWeightedCtr = 0.;
    Double_t passHiggsFJWeightedLepGenLepCtr = 0.;
    Double_t passHiggsFJWeightedSemiLepGenLepCtr = 0.;
    Double_t passHiggsFJWeightedHadGenLepCtr = 0.;
    Double_t passChannelGenLepWeightedCtr = 0.;
    Double_t passLepOrSemiLepChannelGenLepWeightedCtr = 0.;
    Double_t passLepChannelGenLepWeightedCtr = 0.;
    Double_t tryingSemiLepChannelGenLepWeightedCtr = 0;
    Double_t passFJInSemiLepChannelGenLepWeightedCtr = 0;
    Double_t passEnoughLepsInSemiLepChannelGenLepWeightedCtr = 0;
    Double_t passLepCutInSemiLepChannelGenLepWeightedCtr = 0;
    Double_t passSemiLepChannelGenLepWeightedCtr = 0.;
    Double_t passHadChannelGenLepWeightedCtr = 0.;
    Double_t passVBFJetsGenLepWeightedCtr = 0.;
    Double_t passAsLepGenLepWeightedCtr = 0.;
    Double_t passAsSemiLepGenLepWeightedCtr = 0.;
    Double_t passAsHadGenLepWeightedCtr = 0.;

    UInt_t passSemiLepLepCutGenLepCtr = 0;
    Double_t passSemiLepLepCutGenLepWeightedCtr = 0.;

    ////////////////////////////////GEN SEMILEP COUNTERS////////////////////////////////

    UInt_t startingGenSemiLepCtr = 0;

    UInt_t passHiggsFJGenSemiLepCtr = 0;
    UInt_t passHiggsFJLepGenSemiLepCtr = 0;
    UInt_t passHiggsFJSemiLepGenSemiLepCtr = 0;
    UInt_t passHiggsFJHadGenSemiLepCtr = 0;
    UInt_t passChannelGenSemiLepCtr = 0;
    UInt_t passLepOrSemiLepChannelGenSemiLepCtr = 0;
    UInt_t passLepChannelGenSemiLepCtr = 0;
    UInt_t tryingSemiLepChannelGenSemiLepCtr = 0;
    UInt_t passFJInSemiLepChannelGenSemiLepCtr = 0;
    UInt_t passEnoughLepsInSemiLepChannelGenSemiLepCtr = 0;
    UInt_t passLepCutInSemiLepChannelGenSemiLepCtr = 0;
    UInt_t passSemiLepChannelGenSemiLepCtr = 0;
    UInt_t passHadChannelGenSemiLepCtr = 0;
    UInt_t passVBFJetsGenSemiLepCtr = 0;
    UInt_t passAsLepGenSemiLepCtr = 0;
    UInt_t passAsSemiLepGenSemiLepCtr = 0;
    UInt_t passAsHadGenSemiLepCtr = 0;

    Double_t startingGenSemiLepWeightedCtr = 0;
    
    Double_t passHiggsFJGenSemiLepWeightedCtr = 0.;
    Double_t passHiggsFJWeightedLepGenSemiLepCtr = 0.;
    Double_t passHiggsFJWeightedSemiLepGenSemiLepCtr = 0.;
    Double_t passHiggsFJWeightedHadGenSemiLepCtr = 0.;
    Double_t passChannelGenSemiLepWeightedCtr = 0.;
    Double_t passLepOrSemiLepChannelGenSemiLepWeightedCtr = 0.;
    Double_t passLepChannelGenSemiLepWeightedCtr = 0.;
    Double_t tryingSemiLepChannelGenSemiLepWeightedCtr = 0;
    Double_t passFJInSemiLepChannelGenSemiLepWeightedCtr = 0;
    Double_t passEnoughLepsInSemiLepChannelGenSemiLepWeightedCtr = 0;
    Double_t passLepCutInSemiLepChannelGenSemiLepWeightedCtr = 0;
    Double_t passSemiLepChannelGenSemiLepWeightedCtr = 0.;
    Double_t passHadChannelGenSemiLepWeightedCtr = 0.;
    Double_t passVBFJetsGenSemiLepWeightedCtr = 0.;
    Double_t passAsLepGenSemiLepWeightedCtr = 0.;
    Double_t passAsSemiLepGenSemiLepWeightedCtr = 0.;
    Double_t passAsHadGenSemiLepWeightedCtr = 0.;

    UInt_t passSemiLepLepCutGenSemiLepCtr = 0;
    Double_t passSemiLepLepCutGenSemiLepWeightedCtr = 0.;


    ////////////////////////////////GEN HAD COUNTERS////////////////////////////////

    UInt_t startingGenHadCtr = 0;

    UInt_t passHiggsFJGenHadCtr = 0;
    UInt_t passHiggsFJLepGenHadCtr = 0;
    UInt_t passHiggsFJSemiLepGenHadCtr = 0;
    UInt_t passHiggsFJHadGenHadCtr = 0;
    UInt_t passChannelGenHadCtr = 0;
    UInt_t passLepOrSemiLepChannelGenHadCtr = 0;
    UInt_t passLepChannelGenHadCtr = 0;
    UInt_t tryingSemiLepChannelGenHadCtr = 0;
    UInt_t passFJInSemiLepChannelGenHadCtr = 0;
    UInt_t passEnoughLepsInSemiLepChannelGenHadCtr = 0;
    UInt_t passLepCutInSemiLepChannelGenHadCtr = 0;
    UInt_t passSemiLepChannelGenHadCtr = 0;
    UInt_t passHadChannelGenHadCtr = 0;
    UInt_t passVBFJetsGenHadCtr = 0;
    UInt_t passAsLepGenHadCtr = 0;
    UInt_t passAsSemiLepGenHadCtr = 0;
    UInt_t passAsHadGenHadCtr = 0;
    
    Double_t startingGenHadWeightedCtr = 0;

    Double_t passHiggsFJGenHadWeightedCtr = 0.;
    Double_t passHiggsFJWeightedLepGenHadCtr = 0.;
    Double_t passHiggsFJWeightedSemiLepGenHadCtr = 0.;
    Double_t passHiggsFJWeightedHadGenHadCtr = 0.;
    Double_t passChannelGenHadWeightedCtr = 0.;
    Double_t passLepOrSemiLepChannelGenHadWeightedCtr = 0.;
    Double_t passLepChannelGenHadWeightedCtr = 0.;
    Double_t tryingSemiLepChannelGenHadWeightedCtr = 0;
    Double_t passFJInSemiLepChannelGenHadWeightedCtr = 0;
    Double_t passEnoughLepsInSemiLepChannelGenHadWeightedCtr = 0;
    Double_t passLepCutInSemiLepChannelGenHadWeightedCtr = 0;
    Double_t passSemiLepChannelGenHadWeightedCtr = 0.;
    Double_t passHadChannelGenHadWeightedCtr = 0.;
    Double_t passVBFJetsGenHadWeightedCtr = 0.;
    Double_t passAsLepGenHadWeightedCtr = 0.;
    Double_t passAsSemiLepGenHadWeightedCtr = 0.;
    Double_t passAsHadGenHadWeightedCtr = 0.;

    UInt_t passSemiLepLepCutGenHadCtr = 0;
    Double_t passSemiLepLepCutGenHadWeightedCtr = 0.;

    ////////////////////////////////GEN OTHER COUNTERS////////////////////////////////

    UInt_t startingGenOtherCtr = 0;

    UInt_t passHiggsFJGenOtherCtr = 0;
    UInt_t passHiggsFJLepGenOtherCtr = 0;
    UInt_t passHiggsFJSemiLepGenOtherCtr = 0;
    UInt_t passHiggsFJHadGenOtherCtr = 0;
    UInt_t passChannelGenOtherCtr = 0;
    UInt_t passLepOrSemiLepChannelGenOtherCtr = 0;
    UInt_t passLepChannelGenOtherCtr = 0;
    UInt_t tryingSemiLepChannelGenOtherCtr = 0;
    UInt_t passFJInSemiLepChannelGenOtherCtr = 0;
    UInt_t passEnoughLepsInSemiLepChannelGenOtherCtr = 0;
    UInt_t passLepCutInSemiLepChannelGenOtherCtr = 0;
    UInt_t passSemiLepChannelGenOtherCtr = 0;
    UInt_t passHadChannelGenOtherCtr = 0;
    UInt_t passVBFJetsGenOtherCtr = 0;
    UInt_t passAsLepGenOtherCtr = 0;
    UInt_t passAsSemiLepGenOtherCtr = 0;
    UInt_t passAsHadGenOtherCtr = 0;
    
    Double_t startingGenOtherWeightedCtr = 0;

    Double_t passHiggsFJGenOtherWeightedCtr = 0.;
    Double_t passHiggsFJWeightedLepGenOtherCtr = 0.;
    Double_t passHiggsFJWeightedSemiLepGenOtherCtr = 0.;
    Double_t passHiggsFJWeightedHadGenOtherCtr = 0.;
    Double_t passChannelGenOtherWeightedCtr = 0.;
    Double_t passLepOrSemiLepChannelGenOtherWeightedCtr = 0.;
    Double_t passLepChannelGenOtherWeightedCtr = 0.;
    Double_t tryingSemiLepChannelGenOtherWeightedCtr = 0;
    Double_t passFJInSemiLepChannelGenOtherWeightedCtr = 0;
    Double_t passEnoughLepsInSemiLepChannelGenOtherWeightedCtr = 0;
    Double_t passLepCutInSemiLepChannelGenOtherWeightedCtr = 0;
    Double_t passSemiLepChannelGenOtherWeightedCtr = 0.;
    Double_t passHadChannelGenOtherWeightedCtr = 0.;
    Double_t passVBFJetsGenOtherWeightedCtr = 0.;
    Double_t passAsLepGenOtherWeightedCtr = 0.;
    Double_t passAsSemiLepGenOtherWeightedCtr = 0.;
    Double_t passAsHadGenOtherWeightedCtr = 0.;

    UInt_t passSemiLepLepCutGenOtherCtr = 0;
    Double_t passSemiLepLepCutGenOtherWeightedCtr = 0.;
    

    ////////////////////////////////NO HToBB COUNTERS////////////////////////////////

    ////////////////////////////////GEN LEP COUNTERS////////////////////////////////

    UInt_t startingGenLepNoHTobbCtr = 0;

    UInt_t passHiggsFJGenLepNoHTobbCtr = 0;
    UInt_t passHiggsFJLepGenLepNoHTobbCtr = 0;
    UInt_t passHiggsFJSemiLepGenLepNoHTobbCtr = 0;
    UInt_t passHiggsFJHadGenLepNoHTobbCtr = 0;
    UInt_t passChannelGenLepNoHTobbCtr = 0;
    UInt_t passLepOrSemiLepChannelGenLepNoHTobbCtr = 0;
    UInt_t passLepChannelGenLepNoHTobbCtr = 0;
    UInt_t tryingSemiLepChannelGenLepNoHTobbCtr = 0;
    UInt_t passFJInSemiLepChannelGenLepNoHTobbCtr = 0;
    UInt_t passEnoughLepsInSemiLepChannelGenLepNoHTobbCtr = 0;
    UInt_t passLepCutInSemiLepChannelGenLepNoHTobbCtr = 0;
    UInt_t passSemiLepChannelGenLepNoHTobbCtr = 0;
    UInt_t passHadChannelGenLepNoHTobbCtr = 0;
    UInt_t passVBFJetsGenLepNoHTobbCtr = 0;
    UInt_t passAsLepGenLepNoHTobbCtr = 0;
    UInt_t passAsSemiLepGenLepNoHTobbCtr = 0;
    UInt_t passAsHadGenLepNoHTobbCtr = 0;
    
    Double_t startingGenLepNoHTobbWeightedCtr = 0;

    Double_t passHiggsFJGenLepNoHTobbWeightedCtr = 0.;
    Double_t passHiggsFJWeightedLepGenLepNoHTobbCtr = 0.;
    Double_t passHiggsFJWeightedSemiLepGenLepNoHTobbCtr = 0.;
    Double_t passHiggsFJWeightedHadGenLepNoHTobbCtr = 0.;
    Double_t passChannelGenLepNoHTobbWeightedCtr = 0.;
    Double_t passLepOrSemiLepChannelGenLepNoHTobbWeightedCtr = 0.;
    Double_t passLepChannelGenLepNoHTobbWeightedCtr = 0.;
    Double_t tryingSemiLepChannelGenLepNoHTobbWeightedCtr = 0;
    Double_t passFJInSemiLepChannelGenLepNoHTobbWeightedCtr = 0;
    Double_t passEnoughLepsInSemiLepChannelGenLepNoHTobbWeightedCtr = 0;
    Double_t passLepCutInSemiLepChannelGenLepNoHTobbWeightedCtr = 0;
    Double_t passSemiLepChannelGenLepNoHTobbWeightedCtr = 0.;
    Double_t passHadChannelGenLepNoHTobbWeightedCtr = 0.;
    Double_t passVBFJetsGenLepNoHTobbWeightedCtr = 0.;
    Double_t passAsLepGenLepNoHTobbWeightedCtr = 0.;
    Double_t passAsSemiLepGenLepNoHTobbWeightedCtr = 0.;
    Double_t passAsHadGenLepNoHTobbWeightedCtr = 0.;

    UInt_t passSemiLepLepCutGenLepNoHTobbCtr = 0;
    Double_t passSemiLepLepCutGenLepNoHTobbWeightedCtr = 0.;

    ////////////////////////////////GEN SEMILEP COUNTERS////////////////////////////////

    UInt_t startingGenSemiLepNoHTobbCtr = 0;

    UInt_t passHiggsFJGenSemiLepNoHTobbCtr = 0;
    UInt_t passHiggsFJLepGenSemiLepNoHTobbCtr = 0;
    UInt_t passHiggsFJSemiLepGenSemiLepNoHTobbCtr = 0;
    UInt_t passHiggsFJHadGenSemiLepNoHTobbCtr = 0;
    UInt_t passChannelGenSemiLepNoHTobbCtr = 0;
    UInt_t passLepOrSemiLepChannelGenSemiLepNoHTobbCtr = 0;
    UInt_t passLepChannelGenSemiLepNoHTobbCtr = 0;
    UInt_t tryingSemiLepChannelGenSemiLepNoHTobbCtr = 0;
    UInt_t passFJInSemiLepChannelGenSemiLepNoHTobbCtr = 0;
    UInt_t passEnoughLepsInSemiLepChannelGenSemiLepNoHTobbCtr = 0;
    UInt_t passLepCutInSemiLepChannelGenSemiLepNoHTobbCtr = 0;
    UInt_t passSemiLepChannelGenSemiLepNoHTobbCtr = 0;
    UInt_t passHadChannelGenSemiLepNoHTobbCtr = 0;
    UInt_t passVBFJetsGenSemiLepNoHTobbCtr = 0;
    UInt_t passAsLepGenSemiLepNoHTobbCtr = 0;
    UInt_t passAsSemiLepGenSemiLepNoHTobbCtr = 0;
    UInt_t passAsHadGenSemiLepNoHTobbCtr = 0;
    
    Double_t startingGenSemiLepNoHTobbWeightedCtr = 0;

    Double_t passHiggsFJGenSemiLepNoHTobbWeightedCtr = 0.;
    Double_t passHiggsFJWeightedLepGenSemiLepNoHTobbCtr = 0.;
    Double_t passHiggsFJWeightedSemiLepGenSemiLepNoHTobbCtr = 0.;
    Double_t passHiggsFJWeightedHadGenSemiLepNoHTobbCtr = 0.;
    Double_t passChannelGenSemiLepNoHTobbWeightedCtr = 0.;
    Double_t passLepOrSemiLepChannelGenSemiLepNoHTobbWeightedCtr = 0.;
    Double_t passLepChannelGenSemiLepNoHTobbWeightedCtr = 0.;
    Double_t tryingSemiLepChannelGenSemiLepNoHTobbWeightedCtr = 0;
    Double_t passFJInSemiLepChannelGenSemiLepNoHTobbWeightedCtr = 0;
    Double_t passEnoughLepsInSemiLepChannelGenSemiLepNoHTobbWeightedCtr = 0;
    Double_t passLepCutInSemiLepChannelGenSemiLepNoHTobbWeightedCtr = 0;
    Double_t passSemiLepChannelGenSemiLepNoHTobbWeightedCtr = 0.;
    Double_t passHadChannelGenSemiLepNoHTobbWeightedCtr = 0.;
    Double_t passVBFJetsGenSemiLepNoHTobbWeightedCtr = 0.;
    Double_t passAsLepGenSemiLepNoHTobbWeightedCtr = 0.;
    Double_t passAsSemiLepGenSemiLepNoHTobbWeightedCtr = 0.;
    Double_t passAsHadGenSemiLepNoHTobbWeightedCtr = 0.;

    UInt_t passSemiLepLepCutGenSemiLepNoHTobbCtr = 0;
    Double_t passSemiLepLepCutGenSemiLepNoHTobbWeightedCtr = 0.;


    ////////////////////////////////GEN HAD COUNTERS////////////////////////////////

    UInt_t startingGenHadNoHTobbCtr = 0;

    UInt_t passHiggsFJGenHadNoHTobbCtr = 0;
    UInt_t passHiggsFJLepGenHadNoHTobbCtr = 0;
    UInt_t passHiggsFJSemiLepGenHadNoHTobbCtr = 0;
    UInt_t passHiggsFJHadGenHadNoHTobbCtr = 0;
    UInt_t passChannelGenHadNoHTobbCtr = 0;
    UInt_t passLepOrSemiLepChannelGenHadNoHTobbCtr = 0;
    UInt_t passLepChannelGenHadNoHTobbCtr = 0;
    UInt_t tryingSemiLepChannelGenHadNoHTobbCtr = 0;
    UInt_t passFJInSemiLepChannelGenHadNoHTobbCtr = 0;
    UInt_t passEnoughLepsInSemiLepChannelGenHadNoHTobbCtr = 0;
    UInt_t passLepCutInSemiLepChannelGenHadNoHTobbCtr = 0;
    UInt_t passSemiLepChannelGenHadNoHTobbCtr = 0;
    UInt_t passHadChannelGenHadNoHTobbCtr = 0;
    UInt_t passVBFJetsGenHadNoHTobbCtr = 0;
    UInt_t passAsLepGenHadNoHTobbCtr = 0;
    UInt_t passAsSemiLepGenHadNoHTobbCtr = 0;
    UInt_t passAsHadGenHadNoHTobbCtr = 0;
    
    Double_t startingGenHadNoHTobbWeightedCtr = 0;

    Double_t passHiggsFJGenHadNoHTobbWeightedCtr = 0.;
    Double_t passHiggsFJWeightedLepGenHadNoHTobbCtr = 0.;
    Double_t passHiggsFJWeightedSemiLepGenHadNoHTobbCtr = 0.;
    Double_t passHiggsFJWeightedHadGenHadNoHTobbCtr = 0.;
    Double_t passChannelGenHadNoHTobbWeightedCtr = 0.;
    Double_t passLepOrSemiLepChannelGenHadNoHTobbWeightedCtr = 0.;
    Double_t passLepChannelGenHadNoHTobbWeightedCtr = 0.;
    Double_t tryingSemiLepChannelGenHadNoHTobbWeightedCtr = 0;
    Double_t passFJInSemiLepChannelGenHadNoHTobbWeightedCtr = 0;
    Double_t passEnoughLepsInSemiLepChannelGenHadNoHTobbWeightedCtr = 0;
    Double_t passLepCutInSemiLepChannelGenHadNoHTobbWeightedCtr = 0;
    Double_t passSemiLepChannelGenHadNoHTobbWeightedCtr = 0.;
    Double_t passHadChannelGenHadNoHTobbWeightedCtr = 0.;
    Double_t passVBFJetsGenHadNoHTobbWeightedCtr = 0.;
    Double_t passAsLepGenHadNoHTobbWeightedCtr = 0.;
    Double_t passAsSemiLepGenHadNoHTobbWeightedCtr = 0.;
    Double_t passAsHadGenHadNoHTobbWeightedCtr = 0.;

    UInt_t passSemiLepLepCutGenHadNoHTobbCtr = 0;
    Double_t passSemiLepLepCutGenHadNoHTobbWeightedCtr = 0.;

    ////////////////////////////////GEN OTHER COUNTERS////////////////////////////////

    UInt_t startingGenOtherNoHTobbCtr = 0;

    UInt_t passHiggsFJGenOtherNoHTobbCtr = 0;
    UInt_t passHiggsFJLepGenOtherNoHTobbCtr = 0;
    UInt_t passHiggsFJSemiLepGenOtherNoHTobbCtr = 0;
    UInt_t passHiggsFJHadGenOtherNoHTobbCtr = 0;
    UInt_t passChannelGenOtherNoHTobbCtr = 0;
    UInt_t passLepOrSemiLepChannelGenOtherNoHTobbCtr = 0;
    UInt_t passLepChannelGenOtherNoHTobbCtr = 0;
    UInt_t tryingSemiLepChannelGenOtherNoHTobbCtr = 0;
    UInt_t passFJInSemiLepChannelGenOtherNoHTobbCtr = 0;
    UInt_t passEnoughLepsInSemiLepChannelGenOtherNoHTobbCtr = 0;
    UInt_t passLepCutInSemiLepChannelGenOtherNoHTobbCtr = 0;
    UInt_t passSemiLepChannelGenOtherNoHTobbCtr = 0;
    UInt_t passHadChannelGenOtherNoHTobbCtr = 0;
    UInt_t passVBFJetsGenOtherNoHTobbCtr = 0;
    UInt_t passAsLepGenOtherNoHTobbCtr = 0;
    UInt_t passAsSemiLepGenOtherNoHTobbCtr = 0;
    UInt_t passAsHadGenOtherNoHTobbCtr = 0;
    
    Double_t startingGenOtherNoHTobbWeightedCtr = 0;

    Double_t passHiggsFJGenOtherNoHTobbWeightedCtr = 0.;
    Double_t passHiggsFJWeightedLepGenOtherNoHTobbCtr = 0.;
    Double_t passHiggsFJWeightedSemiLepGenOtherNoHTobbCtr = 0.;
    Double_t passHiggsFJWeightedHadGenOtherNoHTobbCtr = 0.;
    Double_t passChannelGenOtherNoHTobbWeightedCtr = 0.;
    Double_t passLepOrSemiLepChannelGenOtherNoHTobbWeightedCtr = 0.;
    Double_t passLepChannelGenOtherNoHTobbWeightedCtr = 0.;
    Double_t tryingSemiLepChannelGenOtherNoHTobbWeightedCtr = 0;
    Double_t passFJInSemiLepChannelGenOtherNoHTobbWeightedCtr = 0;
    Double_t passEnoughLepsInSemiLepChannelGenOtherNoHTobbWeightedCtr = 0;
    Double_t passLepCutInSemiLepChannelGenOtherNoHTobbWeightedCtr = 0;
    Double_t passSemiLepChannelGenOtherNoHTobbWeightedCtr = 0.;
    Double_t passHadChannelGenOtherNoHTobbWeightedCtr = 0.;
    Double_t passVBFJetsGenOtherNoHTobbWeightedCtr = 0.;
    Double_t passAsLepGenOtherNoHTobbWeightedCtr = 0.;
    Double_t passAsSemiLepGenOtherNoHTobbWeightedCtr = 0.;
    Double_t passAsHadGenOtherNoHTobbWeightedCtr = 0.;

    UInt_t passSemiLepLepCutGenOtherNoHTobbCtr = 0;
    Double_t passSemiLepLepCutGenOtherNoHTobbWeightedCtr = 0.;





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


    if (weakCuts){
        std::cout << "Using weak cuts\n";
        dRCut = dRWeakCut;

        jetPTCut = jetPTWeakCut;

        jetEtaDifCut = jetEtaDifWeakCut;

        jetInvMassCut = jetInvMassWeakCut;

        //Higgs FJ cuts

        hFatJetPTCut = hFatJetPTWeakCut;

        hFatJetDeepTagCut = hFatJetDeepTagWeakCut;

        hFatJetParticleNetCut = hFatJetParticleNetWeakCut;



        //Lep cuts

        ePtCut = ePtWeakCut;

        eEtaCut = eEtaWeakCut;

        mPtCut = mPtWeakCut;

        mEtaCut = mEtaWeakCut;

        invMassCutLow=invMassWeakCutLow;

        invMassCutHigh=invMassWeakCutHigh;

        ptLeadCut=ptLeadWeakCut;

        ptTrailingCut=ptTrailingWeakCut;

        fourLepInvMassCut = fourLepInvMassWeakCut;

        optLepInvMassCut = optLepInvMassWeakCut;

        lepIsoCut = lepIsoWeakCut;

        SIPCut = SIPWeakCut;

        //Semi-Lep cuts
        //fatJetPTCut = 200.;

        fatJetZTagCut = fatJetZTagWeakCut;
        fatJetZParticleNetCut = fatJetZParticleNetWeakCut;

        ZPairPlusHInvMassCut = ZPairPlusHInvMassWeakCut;
        ZPairPlusHPtCut = ZPairPlusHPtWeakCut;
        lDxyCut = lDxyWeakCut;
        lDzCut = lDzWeakCut;
        lMiniPFRelIsoCut = lMiniPFRelIsoWeakCut;
        eSieieBarrelCut = eSieieBarrelWeakCut;
        eSieieEndcapCut = eSieieEndcapWeakCut;

        eHoeCut = eHoeWeakCut;
        eInvMinusPInvCut = eInvMinusPInvWeakCut;
        ePromptMVACut = ePromptMVAWeakCut;
        lepJetDeepTagLooseCut = lepJetDeepTagLooseWeakCut;
        lepJetDeepTagMediumCut = lepJetDeepTagMediumWeakCut;
        mPromptMVACut = mPromptMVAWeakCut;
    }
    std::string outFileStr;
    if (weakCuts){
        outFileStr = "new062022AnalysisWeakCuts"+saveName+".root";
    }
    else{
        outFileStr = "new062022Analysis"+saveName+".root";
    }
    //std::string outFileStr = "BeforeCutEvents"+saveName+".root";
    std::cout << "OutFile: " << outFileStr << "\n";
    TFile *outFile = new TFile(outFileStr.c_str(),"RECREATE");

    Double_t genLepWeightL;
    std::vector<Float_t> LepInvMassL;
    //Float_t LepInvMassL;

    TTree *BeforeCutLepInvMassTree = new TTree("BeforeCutLepInvMassTree", "BeforeCutLepInvMassTree");

    BeforeCutLepInvMassTree->Branch("genLepWeightL",&genLepWeightL,"genLepWeightL/D");
    BeforeCutLepInvMassTree->Branch("LepInvMassL",&LepInvMassL);
    //BeforeCutLepInvMassTree->Branch("LepInvMassL",&LepInvMassL,"LepInvMassL/F");
    
    Double_t genSemiLepWeightL;
    //std::vector<Float_t> SemiLepInvMassL;
    Float_t SemiLepInvMassL;
    

    TTree *BeforeCutSemiLepInvMassTree = new TTree("BeforeCutSemiLepInvMassTree", "BeforeCutSemiLepInvMassTree");
    
    BeforeCutSemiLepInvMassTree->Branch("genSemiLepWeightL",&genSemiLepWeightL,"genSemiLepWeightL/D");
    //BeforeCutSemiLepInvMassTree->Branch("SemiLepInvMassL",&SemiLepInvMassL);
    BeforeCutSemiLepInvMassTree->Branch("SemiLepInvMassL",&SemiLepInvMassL,"SemiLepInvMassL/F");


    UInt_t  nFJL;
    UInt_t  nJL;
    Double_t AfterCutGenSemiLepWeightL;
    TTree *AfterCutSemiLepInvMassTree = new TTree("AfterCutSemiLepInvMassTree", "AfterCutSemiLepInvMassTree");
    AfterCutSemiLepInvMassTree->Branch("AfterCutGenSemiLepWeightL",&AfterCutGenSemiLepWeightL,"AfterCutGenSemiLepWeightL/D");
    AfterCutSemiLepInvMassTree->Branch("nFJL",&nFJL,"nFJL/i");
    AfterCutSemiLepInvMassTree->Branch("nJL",&nJL,"nJL/i");

    

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

        //genChannelL
        TTreeReaderValue<UInt_t> genChannelL(myEventsReader, "genChannelL");
        //HTobbBool
        TTreeReaderValue<Bool_t> HTobbBoolL(myEventsReader, "HTobbBoolL");

        TTreeReader myEvNumReader("evNumTree", tmpfile);
        TTreeReaderValue<UInt_t> nEv(myEvNumReader, "nEv");
        TTreeReaderValue<UInt_t> nEvPass(myEvNumReader, "nEvPass");

        TTreeReader myXSReader("crossSectionTree", tmpfile);
        TTreeReaderValue<Float_t> crossSectionVar(myXSReader, "crossSectionVar");

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

        //Getting the cross section
        //For background it's precalculated

        if (!isBackground){
            while (myXSReader.Next()){
                crossSectionAvg += *crossSectionVar;
                crossSectionCnt += 1;
                //dataXS = *crossSectionVar;
            }
        }
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

            if (!isBackground){
                if (*HTobbBoolL){
                    if (*genChannelL == 0) {
                        startingGenLepCtr += 1;
                        startingGenLepWeightedCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 1) {
                        startingGenSemiLepCtr += 1;
                        startingGenSemiLepWeightedCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 2) {
                        startingGenHadCtr += 1;
                        startingGenHadWeightedCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 3) {
                        startingGenOtherCtr += 1;
                        startingGenOtherWeightedCtr += tmpGenWeights;
                    }
                }
                else{
                    if (*genChannelL == 0) {
                        startingGenLepNoHTobbCtr += 1;
                        startingGenLepNoHTobbWeightedCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 1) {
                        startingGenSemiLepNoHTobbCtr += 1;
                        startingGenSemiLepNoHTobbWeightedCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 2) {
                        startingGenHadNoHTobbCtr += 1;
                        startingGenHadNoHTobbWeightedCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 3) {
                        startingGenOtherNoHTobbCtr += 1;
                        startingGenOtherNoHTobbWeightedCtr += tmpGenWeights;
                    }
                }
            }


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

            

            if (LepInvMass.size() >= 2) {
                /*
                Float_t closestInvMassDifOne = 999999.;
                Float_t tmpInvMassOne = 0.;
                Float_t closestInvMassDifTwo = 999999.;
                Float_t tmpInvMassTwo = 0.;
                */
                std::vector<Float_t> tmpInvMassVec;
                tmpInvMassVec.push_back(0.);
                tmpInvMassVec.push_back(0.);
                std::vector<Float_t> closestInvMassDifVec;
                closestInvMassDifVec.push_back(999999.);
                closestInvMassDifVec.push_back(999999.);
                for (UInt_t LepInvMassInd=0;LepInvMassInd<LepInvMass.size();LepInvMassInd++){
                    Float_t tmpInvMassDif = abs(ZMass - LepInvMass[LepInvMassInd]);
                    if (tmpInvMassDif < closestInvMassDifVec[0]) {
                        tmpInvMassVec[1] = tmpInvMassVec[0];
                        closestInvMassDifVec[1] = closestInvMassDifVec[0];
                        tmpInvMassVec[0] = LepInvMass[LepInvMassInd];
                        closestInvMassDifVec[0] = tmpInvMassDif;

                    }
                    else if (tmpInvMassDif < closestInvMassDifVec[1]) {
                        closestInvMassDifVec[1] = tmpInvMassDif;
                        tmpInvMassVec[1] = LepInvMass[LepInvMassInd];
                    }
                }
                //LepInvMassL = LepInvMass;
                LepInvMassL = tmpInvMassVec;
                genLepWeightL = *genWeightL;
                BeforeCutLepInvMassTree->Fill();
                LepInvMassL.clear();
            }

            
            if (debug) std::cout << "passesCutsBool " << passesCutsBool << "\n";
            if (passesCutsBool){
                passChannelCtr += 1;
                passChannelWeightedCtr += tmpGenWeights;
                if (!isBackground){ 
                    if (*HTobbBoolL){
                        if (*genChannelL == 0) {
                            passChannelGenLepCtr += 1;
                            passChannelGenLepWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 1) {
                            passChannelGenSemiLepCtr += 1;
                            passChannelGenSemiLepWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 2) {
                            passChannelGenHadCtr += 1;
                            passChannelGenHadWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 3) {
                            passChannelGenOtherCtr += 1;
                            passChannelGenOtherWeightedCtr += tmpGenWeights;
                        }
                    }
                    else{
                        if (*genChannelL == 0) {
                            passChannelGenLepNoHTobbCtr += 1;
                            passChannelGenLepNoHTobbWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 1) {
                            passChannelGenSemiLepNoHTobbCtr += 1;
                            passChannelGenSemiLepNoHTobbWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 2) {
                            passChannelGenHadNoHTobbCtr += 1;
                            passChannelGenHadNoHTobbWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 3) {
                            passChannelGenOtherNoHTobbCtr += 1;
                            passChannelGenOtherNoHTobbWeightedCtr += tmpGenWeights;
                        }
                    }
                }
                passLepChannelCtr += 1;
                passLepChannelWeightedCtr += tmpGenWeights;
                if (!isBackground){ 
                    if (*HTobbBoolL){
                        if (*genChannelL == 0) {
                            passLepChannelGenLepCtr += 1;
                            passLepChannelGenLepWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 1) {
                            passLepChannelGenSemiLepCtr += 1;
                            passLepChannelGenSemiLepWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 2) {
                            passLepChannelGenHadCtr += 1;
                            passLepChannelGenHadWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 3) {
                            passLepChannelGenOtherCtr += 1;
                            passLepChannelGenOtherWeightedCtr += tmpGenWeights;
                        }
                    }
                    else {
                        if (*genChannelL == 0) {
                            passLepChannelGenLepNoHTobbCtr += 1;
                            passLepChannelGenLepNoHTobbWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 1) {
                            passLepChannelGenSemiLepNoHTobbCtr += 1;
                            passLepChannelGenSemiLepNoHTobbWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 2) {
                            passLepChannelGenHadNoHTobbCtr += 1;
                            passLepChannelGenHadNoHTobbWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 3) {
                            passLepChannelGenOtherNoHTobbCtr += 1;
                            passLepChannelGenOtherNoHTobbWeightedCtr += tmpGenWeights;
                        }

                    }
                }
                passLepOrSemiLepChannelCtr += 1;
                passLepOrSemiLepChannelWeightedCtr += tmpGenWeights;
                if (!isBackground){ 
                    if (*HTobbBoolL){
                        if (*genChannelL == 0) {
                            passLepOrSemiLepChannelGenLepCtr += 1;
                            passLepOrSemiLepChannelGenLepWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 1) {
                            passLepOrSemiLepChannelGenSemiLepCtr += 1;
                            passLepOrSemiLepChannelGenSemiLepWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 2) {
                            passLepOrSemiLepChannelGenHadCtr += 1;
                            passLepOrSemiLepChannelGenHadWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 3) {
                            passLepOrSemiLepChannelGenOtherCtr += 1;
                            passLepOrSemiLepChannelGenOtherWeightedCtr += tmpGenWeights;
                        }
                    }
                    else {
                        if (*genChannelL == 0) {
                            passLepOrSemiLepChannelGenLepNoHTobbCtr += 1;
                            passLepOrSemiLepChannelGenLepNoHTobbWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 1) {
                            passLepOrSemiLepChannelGenSemiLepNoHTobbCtr += 1;
                            passLepOrSemiLepChannelGenSemiLepNoHTobbWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 2) {
                            passLepOrSemiLepChannelGenHadNoHTobbCtr += 1;
                            passLepOrSemiLepChannelGenHadNoHTobbWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 3) {
                            passLepOrSemiLepChannelGenOtherNoHTobbCtr += 1;
                            passLepOrSemiLepChannelGenOtherNoHTobbWeightedCtr += tmpGenWeights;
                        }
                    }
                }
            }
            if ((!passesCutsBool)){
                dRCheckVecAr.clear();
                std::vector<Float_t> SemiLepInvMass;
                
                if (debug) std::cout << "trying SemiLeptonic\n";
                tryingSemiLepChannelCtr += 1;
                tryingSemiLepChannelWeightedCtr += tmpGenWeights;
                if (!isBackground){ 
                    if (*HTobbBoolL){
                        if (*genChannelL == 0) {
                            tryingSemiLepChannelGenLepCtr += 1;
                            tryingSemiLepChannelGenLepWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 1) {
                            tryingSemiLepChannelGenSemiLepCtr += 1;
                            tryingSemiLepChannelGenSemiLepWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 2) {
                            tryingSemiLepChannelGenHadCtr += 1;
                            tryingSemiLepChannelGenHadWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 3) {
                            tryingSemiLepChannelGenOtherCtr += 1;
                            tryingSemiLepChannelGenOtherWeightedCtr += tmpGenWeights;
                        }
                    }
                    else {
                        if (*genChannelL == 0) {
                            tryingSemiLepChannelGenLepNoHTobbCtr += 1;
                            tryingSemiLepChannelGenLepNoHTobbWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 1) {
                            tryingSemiLepChannelGenSemiLepNoHTobbCtr += 1;
                            tryingSemiLepChannelGenSemiLepNoHTobbWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 2) {
                            tryingSemiLepChannelGenHadNoHTobbCtr += 1;
                            tryingSemiLepChannelGenHadNoHTobbWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 3) {
                            tryingSemiLepChannelGenOtherNoHTobbCtr += 1;
                            tryingSemiLepChannelGenOtherNoHTobbWeightedCtr += tmpGenWeights;
                        }
                    }
                }
                tryingSemiLepCtr += 1;
                
                enoughLepCands = false;
                doSemiLepCutWithTree(enoughElecCands,negElecCands,posElecCands,totElecCands,Electron_etaL,Electron_massL,Electron_chargeL,Electron_phiL,Electron_ptL,neLep,elecCandIndAr,elecCandVecAr,elecCandChargeAr,ePtCut,eEtaCut,
                 enoughMuonCands,negMuonCands,posMuonCands,totMuonCands,Muon_etaL,Muon_massL,Muon_chargeL,Muon_phiL,Muon_ptL,nmLep,muonCandIndAr,muonCandVecAr,muonCandChargeAr,mPtCut,mEtaCut,
                 enoughLepCands,invMassCutLow,invMassCutHigh,ptLeadCut,ptTrailingCut,Z1Cand,difFromZMassOne,Z1LeadItr,Z1TrailingItr,Z1LeadPt,Z1TrailingPt,Z1IsMuon,Z1LeadVec,Z1TrailingVec,Z1LeadCharge,Z1TrailingCharge,
                 Electron_dr03EcalRecHitSumEtL,Electron_dr03TkSumPtL,Electron_dr03HcalDepth1TowerSumEtL,Electron_pfRelIso03_allL,
                 Z1LeadIso,Muon_pfRelIso03_allL,Z1TrailingIso,lepIsoCut,
                 SemiLepInvMass,
                 Electron_mvaFall17V2noIso_WPLL,Muon_mediumIdL,
                 dRCheckVecAr,
                 passedAsSemiLepLepCutBool,
                 debug);
                if (enoughLepCands){
                    passEnoughLepsInSemiLepChannelCtr += 1;
                    passEnoughLepsInSemiLepChannelWeightedCtr += tmpGenWeights;
                    if (!isBackground){ 
                        if (*HTobbBoolL){
                            if (*genChannelL == 0) {
                                passEnoughLepsInSemiLepChannelGenLepCtr += 1;
                                passEnoughLepsInSemiLepChannelGenLepWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 1) {
                                passEnoughLepsInSemiLepChannelGenSemiLepCtr += 1;
                                passEnoughLepsInSemiLepChannelGenSemiLepWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 2) {
                                passEnoughLepsInSemiLepChannelGenHadCtr += 1;
                                passEnoughLepsInSemiLepChannelGenHadWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 3) {
                                passEnoughLepsInSemiLepChannelGenOtherCtr += 1;
                                passEnoughLepsInSemiLepChannelGenOtherWeightedCtr += tmpGenWeights;
                            }
                        }
                        else {
                            if (*genChannelL == 0) {
                                passEnoughLepsInSemiLepChannelGenLepNoHTobbCtr += 1;
                                passEnoughLepsInSemiLepChannelGenLepNoHTobbWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 1) {
                                passEnoughLepsInSemiLepChannelGenSemiLepNoHTobbCtr += 1;
                                passEnoughLepsInSemiLepChannelGenSemiLepNoHTobbWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 2) {
                                passEnoughLepsInSemiLepChannelGenHadNoHTobbCtr += 1;
                                passEnoughLepsInSemiLepChannelGenHadNoHTobbWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 3) {
                                passEnoughLepsInSemiLepChannelGenOtherNoHTobbCtr += 1;
                                passEnoughLepsInSemiLepChannelGenOtherNoHTobbWeightedCtr += tmpGenWeights;
                            }
                        }
                    }
                    
                }

                if (passedAsSemiLepLepCutBool){
                    if (debug) std::cout << "Passed semi lep lep cut\n";
                    passSemiLepLepCutCtr += 1;
                    passSemiLepLepCutWeightedCtr += tmpGenWeights;
                    if (!isBackground){ 
                        if (*HTobbBoolL){
                            if (*genChannelL == 0) {
                                passSemiLepLepCutGenLepCtr += 1;
                                passSemiLepLepCutGenLepWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 1) {
                                passSemiLepLepCutGenSemiLepCtr += 1;
                                passSemiLepLepCutGenSemiLepWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 2) {
                                passSemiLepLepCutGenHadCtr += 1;
                                passSemiLepLepCutGenHadWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 3) {
                                passSemiLepLepCutGenOtherCtr += 1;
                                passSemiLepLepCutGenOtherWeightedCtr += tmpGenWeights;
                            }
                        }
                        else {
                            if (*genChannelL == 0) {
                                passSemiLepLepCutGenLepNoHTobbCtr += 1;
                                passSemiLepLepCutGenLepNoHTobbWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 1) {
                                passSemiLepLepCutGenSemiLepNoHTobbCtr += 1;
                                passSemiLepLepCutGenSemiLepNoHTobbWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 2) {
                                passSemiLepLepCutGenHadNoHTobbCtr += 1;
                                passSemiLepLepCutGenHadNoHTobbWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 3) {
                                passSemiLepLepCutGenOtherNoHTobbCtr += 1;
                                passSemiLepLepCutGenOtherNoHTobbWeightedCtr += tmpGenWeights;
                            }
                        }
                    }
                    
                }


                if (SemiLepInvMass.size()) {
                    Float_t closestInvMassDif = 999999.;
                    Float_t tmpInvMass = 0.;
                    for (UInt_t SemiLepInvMassInd=0;SemiLepInvMassInd<SemiLepInvMass.size();SemiLepInvMassInd++){
                        Float_t tmpInvMassDif = abs(ZMass - SemiLepInvMass[SemiLepInvMassInd]);
                        if (tmpInvMassDif < closestInvMassDif) {
                            closestInvMassDif = tmpInvMassDif;
                            tmpInvMass = SemiLepInvMass[SemiLepInvMassInd];
                        }
                    }
                    //SemiLepInvMassL = SemiLepInvMass;
                    SemiLepInvMassL = tmpInvMass;
                    genSemiLepWeightL = *genWeightL;
                    BeforeCutSemiLepInvMassTree->Fill();
                    //SemiLepInvMassL.clear();
                }
                /*
                if (SemiLepInvMass.size()) {
                    SemiLepInvMassL = SemiLepInvMass;
                    genSemiLepWeightL = *genWeightL;
                    BeforeCutSemiLepInvMassTree->Fill();
                    SemiLepInvMassL.clear();
                }
                */
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
                    if (!isBackground){ 
                        if (*HTobbBoolL){
                            if (*genChannelL == 0) {
                                passFJInSemiLepChannelGenLepCtr += 1;
                                passFJInSemiLepChannelGenLepWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 1) {
                                passFJInSemiLepChannelGenSemiLepCtr += 1;
                                passFJInSemiLepChannelGenSemiLepWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 2) {
                                passFJInSemiLepChannelGenHadCtr += 1;
                                passFJInSemiLepChannelGenHadWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 3) {
                                passFJInSemiLepChannelGenOtherCtr += 1;
                                passFJInSemiLepChannelGenOtherWeightedCtr += tmpGenWeights;
                            }
                        }
                        else{
                            if (*genChannelL == 0) {
                                passFJInSemiLepChannelGenLepNoHTobbCtr += 1;
                                passFJInSemiLepChannelGenLepNoHTobbWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 1) {
                                passFJInSemiLepChannelGenSemiLepNoHTobbCtr += 1;
                                passFJInSemiLepChannelGenSemiLepNoHTobbWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 2) {
                                passFJInSemiLepChannelGenHadNoHTobbCtr += 1;
                                passFJInSemiLepChannelGenHadNoHTobbWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 3) {
                                passFJInSemiLepChannelGenOtherNoHTobbCtr += 1;
                                passFJInSemiLepChannelGenOtherNoHTobbWeightedCtr += tmpGenWeights;
                            }
                        }
                    }
                   FJIndAr.push_back(FJInd);
                   
                }

                
                if (passesCutsBool){
                    passChannelCtr += 1;
                    passChannelWeightedCtr += tmpGenWeights;
                    if (!isBackground){ 
                        if (*HTobbBoolL){
                            if (*genChannelL == 0) {
                                passChannelGenLepCtr += 1;
                                passChannelGenLepWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 1) {
                                passChannelGenSemiLepCtr += 1;
                                passChannelGenSemiLepWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 2) {
                                passChannelGenHadCtr += 1;
                                passChannelGenHadWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 3) {
                                passChannelGenOtherCtr += 1;
                                passChannelGenOtherWeightedCtr += tmpGenWeights;
                            }
                        }
                        else {
                            if (*genChannelL == 0) {
                                passChannelGenLepNoHTobbCtr += 1;
                                passChannelGenLepNoHTobbWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 1) {
                                passChannelGenSemiLepNoHTobbCtr += 1;
                                passChannelGenSemiLepNoHTobbWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 2) {
                                passChannelGenHadNoHTobbCtr += 1;
                                passChannelGenHadNoHTobbWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 3) {
                                passChannelGenOtherNoHTobbCtr += 1;
                                passChannelGenOtherNoHTobbWeightedCtr += tmpGenWeights;
                            }
                        }
                    }


                    passSemiLepChannelCtr += 1;
                    passSemiLepChannelWeightedCtr += tmpGenWeights;
                    if (!isBackground){ 
                        if (*HTobbBoolL){
                            if (*genChannelL == 0) {
                                passSemiLepChannelGenLepCtr += 1;
                                passSemiLepChannelGenLepWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 1) {
                                passSemiLepChannelGenSemiLepCtr += 1;
                                passSemiLepChannelGenSemiLepWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 2) {
                                passSemiLepChannelGenHadCtr += 1;
                                passSemiLepChannelGenHadWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 3) {
                                passSemiLepChannelGenOtherCtr += 1;
                                passSemiLepChannelGenOtherWeightedCtr += tmpGenWeights;
                            }
                        }
                        else {
                            if (*genChannelL == 0) {
                                passSemiLepChannelGenLepNoHTobbCtr += 1;
                                passSemiLepChannelGenLepNoHTobbWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 1) {
                                passSemiLepChannelGenSemiLepNoHTobbCtr += 1;
                                passSemiLepChannelGenSemiLepNoHTobbWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 2) {
                                passSemiLepChannelGenHadNoHTobbCtr += 1;
                                passSemiLepChannelGenHadNoHTobbWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 3) {
                                passSemiLepChannelGenOtherNoHTobbCtr += 1;
                                passSemiLepChannelGenOtherNoHTobbWeightedCtr += tmpGenWeights;
                            }
                        }
                    }

                    passLepOrSemiLepChannelCtr += 1;
                    passLepOrSemiLepChannelWeightedCtr += tmpGenWeights;
                    if (!isBackground){ 
                        if (*HTobbBoolL){
                            if (*genChannelL == 0) {
                                passLepOrSemiLepChannelGenLepCtr += 1;
                                passLepOrSemiLepChannelGenLepWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 1) {
                                passLepOrSemiLepChannelGenSemiLepCtr += 1;
                                passLepOrSemiLepChannelGenSemiLepWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 2) {
                                passLepOrSemiLepChannelGenHadCtr += 1;
                                passLepOrSemiLepChannelGenHadWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 3) {
                                passLepOrSemiLepChannelGenOtherCtr += 1;
                                passLepOrSemiLepChannelGenOtherWeightedCtr += tmpGenWeights;
                            }
                        }
                        else {
                            if (*genChannelL == 0) {
                                passLepOrSemiLepChannelGenLepNoHTobbCtr += 1;
                                passLepOrSemiLepChannelGenLepNoHTobbWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 1) {
                                passLepOrSemiLepChannelGenSemiLepNoHTobbCtr += 1;
                                passLepOrSemiLepChannelGenSemiLepNoHTobbWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 2) {
                                passLepOrSemiLepChannelGenHadNoHTobbCtr += 1;
                                passLepOrSemiLepChannelGenHadNoHTobbWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 3) {
                                passLepOrSemiLepChannelGenOtherNoHTobbCtr += 1;
                                passLepOrSemiLepChannelGenOtherNoHTobbWeightedCtr += tmpGenWeights;
                            }
                        }
                    }
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
                    if (!isBackground){ 
                        if (*HTobbBoolL){
                            if (*genChannelL == 0) {
                                passChannelGenLepCtr += 1;
                                passChannelGenLepWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 1) {
                                passChannelGenSemiLepCtr += 1;
                                passChannelGenSemiLepWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 2) {
                                passChannelGenHadCtr += 1;
                                passChannelGenHadWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 3) {
                                passChannelGenOtherCtr += 1;
                                passChannelGenOtherWeightedCtr += tmpGenWeights;
                            }
                        }
                        else {
                            if (*genChannelL == 0) {
                                passChannelGenLepNoHTobbCtr += 1;
                                passChannelGenLepNoHTobbWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 1) {
                                passChannelGenSemiLepNoHTobbCtr += 1;
                                passChannelGenSemiLepNoHTobbWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 2) {
                                passChannelGenHadNoHTobbCtr += 1;
                                passChannelGenHadNoHTobbWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 3) {
                                passChannelGenOtherNoHTobbCtr += 1;
                                passChannelGenOtherNoHTobbWeightedCtr += tmpGenWeights;
                            }
                        }
                    }
                    passHadChannelCtr += 1;
                    passHadChannelWeightedCtr += tmpGenWeights;
                    if (!isBackground){ 
                        if (*HTobbBoolL){
                            if (*genChannelL == 0) {
                                passHadChannelGenLepCtr += 1;
                                passHadChannelGenLepWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 1) {
                                passHadChannelGenSemiLepCtr += 1;
                                passHadChannelGenSemiLepWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 2) {
                                passHadChannelGenHadCtr += 1;
                                passHadChannelGenHadWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 3) {
                                passHadChannelGenOtherCtr += 1;
                                passHadChannelGenOtherWeightedCtr += tmpGenWeights;
                            }
                        }
                        else {
                            if (*genChannelL == 0) {
                                passHadChannelGenLepNoHTobbCtr += 1;
                                passHadChannelGenLepNoHTobbWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 1) {
                                passHadChannelGenSemiLepNoHTobbCtr += 1;
                                passHadChannelGenSemiLepNoHTobbWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 2) {
                                passHadChannelGenHadNoHTobbCtr += 1;
                                passHadChannelGenHadNoHTobbWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 3) {
                                passHadChannelGenOtherNoHTobbCtr += 1;
                                passHadChannelGenOtherNoHTobbWeightedCtr += tmpGenWeights;
                            }
                        }
                    }
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
            doHiggsFatJetCut(nFatJetLen,hFatJet_pt_fromHTag,hFatJet_phi_fromHTag,hFatJet_eta_fromHTag,hFatJet_mass_fromHTag,hFatJet_HTag_fromHTag,hFatJet_ind_fromHTag,FatJet_particleNet_HbbvsQCDL,hFatJetParticleNetCut,FatJet_ptL,hFatJetPTCut,FatJet_jetIdL,FatJet_phiL,FatJet_etaL,FatJet_massL,dRCheckVecAr,dRCut,FJIndAr,ZPairPlusHInvMassCut,ZPairPlusHPtCut);
            
            if (hFatJet_pt_fromHTag == 0) continue;
            if (debug) std::cout << " found fat jet\n";

            
            passHiggsFJCtr += 1;
            passHiggsFJWeightedCtr += tmpGenWeights;
            if (!isBackground){ 
                if (*HTobbBoolL){
                    if (*genChannelL == 0) {
                        passHiggsFJGenLepCtr += 1;
                        passHiggsFJGenLepWeightedCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 1) {
                        passHiggsFJGenSemiLepCtr += 1;
                        passHiggsFJGenSemiLepWeightedCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 2) {
                        passHiggsFJGenHadCtr += 1;
                        passHiggsFJGenHadWeightedCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 3) {
                        passHiggsFJGenOtherCtr += 1;
                        passHiggsFJGenOtherWeightedCtr += tmpGenWeights;
                    }
                }
                else {
                    if (*genChannelL == 0) {
                        passHiggsFJGenLepNoHTobbCtr += 1;
                        passHiggsFJGenLepNoHTobbWeightedCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 1) {
                        passHiggsFJGenSemiLepNoHTobbCtr += 1;
                        passHiggsFJGenSemiLepNoHTobbWeightedCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 2) {
                        passHiggsFJGenHadNoHTobbCtr += 1;
                        passHiggsFJGenHadNoHTobbWeightedCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 3) {
                        passHiggsFJGenOtherNoHTobbCtr += 1;
                        passHiggsFJGenOtherNoHTobbWeightedCtr += tmpGenWeights;
                    }
                }
            }

            if (passedAsLepBool) {
                passHiggsFJLepCtr += 1;
                passHiggsFJWeightedLepCtr += tmpGenWeights;
                if (!isBackground){ 
                    if (*HTobbBoolL){
                        if (*genChannelL == 0) {
                            passHiggsFJLepGenLepCtr += 1;
                            passHiggsFJWeightedLepGenLepCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 1) {
                            passHiggsFJLepGenSemiLepCtr += 1;
                            passHiggsFJWeightedLepGenSemiLepCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 2) {
                            passHiggsFJLepGenHadCtr += 1;
                            passHiggsFJWeightedLepGenHadCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 3) {
                            passHiggsFJLepGenOtherCtr += 1;
                            passHiggsFJWeightedLepGenOtherCtr += tmpGenWeights;
                        }
                    }
                    else {
                        if (*genChannelL == 0) {
                            passHiggsFJLepGenLepNoHTobbCtr += 1;
                            passHiggsFJWeightedLepGenLepNoHTobbCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 1) {
                            passHiggsFJLepGenSemiLepNoHTobbCtr += 1;
                            passHiggsFJWeightedLepGenSemiLepNoHTobbCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 2) {
                            passHiggsFJLepGenHadNoHTobbCtr += 1;
                            passHiggsFJWeightedLepGenHadNoHTobbCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 3) {
                            passHiggsFJLepGenOtherNoHTobbCtr += 1;
                            passHiggsFJWeightedLepGenOtherNoHTobbCtr += tmpGenWeights;
                        }
                    }
                }
            }
            else if (passedAsSemiLepBool) {
                passHiggsFJSemiLepCtr += 1;
                passHiggsFJWeightedSemiLepCtr += tmpGenWeights;
                if (!isBackground){ 
                    if (*HTobbBoolL){
                        if (*genChannelL == 0) {
                            passHiggsFJSemiLepGenLepCtr += 1;
                            passHiggsFJWeightedSemiLepGenLepCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 1) {
                            passHiggsFJSemiLepGenSemiLepCtr += 1;
                            passHiggsFJWeightedSemiLepGenSemiLepCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 2) {
                            passHiggsFJSemiLepGenHadCtr += 1;
                            passHiggsFJWeightedSemiLepGenHadCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 3) {
                            passHiggsFJSemiLepGenOtherCtr += 1;
                            passHiggsFJWeightedSemiLepGenOtherCtr += tmpGenWeights;
                        }
                    }
                    else {
                        if (*genChannelL == 0) {
                            passHiggsFJSemiLepGenLepNoHTobbCtr += 1;
                            passHiggsFJWeightedSemiLepGenLepNoHTobbCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 1) {
                            passHiggsFJSemiLepGenSemiLepNoHTobbCtr += 1;
                            passHiggsFJWeightedSemiLepGenSemiLepNoHTobbCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 2) {
                            passHiggsFJSemiLepGenHadNoHTobbCtr += 1;
                            passHiggsFJWeightedSemiLepGenHadNoHTobbCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 3) {
                            passHiggsFJSemiLepGenOtherNoHTobbCtr += 1;
                            passHiggsFJWeightedSemiLepGenOtherNoHTobbCtr += tmpGenWeights;
                        }
                    }
                }
            }
            else if (passedAsHadBool) {
                passHiggsFJHadCtr += 1;
                passHiggsFJWeightedHadCtr += tmpGenWeights;
                if (!isBackground){ 
                    if (*HTobbBoolL){
                        if (*genChannelL == 0) {
                            passHiggsFJHadGenLepCtr += 1;
                            passHiggsFJWeightedHadGenLepCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 1) {
                            passHiggsFJHadGenSemiLepCtr += 1;
                            passHiggsFJWeightedHadGenSemiLepCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 2) {
                            passHiggsFJHadGenHadCtr += 1;
                            passHiggsFJWeightedHadGenHadCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 3) {
                            passHiggsFJHadGenOtherCtr += 1;
                            passHiggsFJWeightedHadGenOtherCtr += tmpGenWeights;
                        }
                    }
                    else {
                        if (*genChannelL == 0) {
                            passHiggsFJHadGenLepNoHTobbCtr += 1;
                            passHiggsFJWeightedHadGenLepNoHTobbCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 1) {
                            passHiggsFJHadGenSemiLepNoHTobbCtr += 1;
                            passHiggsFJWeightedHadGenSemiLepNoHTobbCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 2) {
                            passHiggsFJHadGenHadNoHTobbCtr += 1;
                            passHiggsFJWeightedHadGenHadNoHTobbCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 3) {
                            passHiggsFJHadGenOtherNoHTobbCtr += 1;
                            passHiggsFJWeightedHadGenOtherNoHTobbCtr += tmpGenWeights;
                        }
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
            if (debug) std::cout << "Entering jet loop. Len: " << nJetLen << "\n";
            doVBFJetCutPtSelection(nJetLen,Jet_ptL,Jet_jetIdL,Jet_etaL,Jet_phiL,Jet_massL,jetPTCut,jetEtaDifCut,jetInvMassCut,jetPairInvMass,jetLeadPt,jetLeadEta,jetLeadPhi,jetTrailingPt,jetTrailingEta,jetTrailingPhi,leadJet_1,leadJet_2,dRCheckVecAr,dRCut,debug);
            //std::cout << jetLeadPt << endl;
            if (jetLeadPt == 0) continue;
            debugOutputForVBFJetCut(evCount,leadJet_1,leadJet_2,Jet_phiL,Jet_etaL,debug);
            passVBFJets += 1;

            if (passesCutsBool){
                passVBFJetsCtr += 1;
                passVBFJetsWeightedCtr += tmpGenWeights;
                if (!isBackground){ 
                    if (*HTobbBoolL){
                        if (*genChannelL == 0) {
                            passVBFJetsGenLepCtr += 1;
                            passVBFJetsGenLepWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 1) {
                            passVBFJetsGenSemiLepCtr += 1;
                            passVBFJetsGenSemiLepWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 2) {
                            passVBFJetsGenHadCtr += 1;
                            passVBFJetsGenHadWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 3) {
                            passVBFJetsGenOtherCtr += 1;
                            passVBFJetsGenOtherWeightedCtr += tmpGenWeights;
                        }
                    }
                    else {
                        if (*genChannelL == 0) {
                            passVBFJetsGenLepNoHTobbCtr += 1;
                            passVBFJetsGenLepNoHTobbWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 1) {
                            passVBFJetsGenSemiLepNoHTobbCtr += 1;
                            passVBFJetsGenSemiLepNoHTobbWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 2) {
                            passVBFJetsGenHadNoHTobbCtr += 1;
                            passVBFJetsGenHadNoHTobbWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 3) {
                            passVBFJetsGenOtherNoHTobbCtr += 1;
                            passVBFJetsGenOtherNoHTobbWeightedCtr += tmpGenWeights;
                        }
                    }
                }

                //std::cout << passedAsLepBool << " "<< passedAsSemiLepBool << " " << passedAsHadBool << "\n";
                if (passedAsLepBool) {

                    passAsLepCtr += 1;
                    passAsLepWeightedCtr += tmpGenWeights;
                    if (!isBackground){ 
                        if (*HTobbBoolL){
                            if (*genChannelL == 0) {
                                passAsLepGenLepCtr += 1;
                                passAsLepGenLepWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 1) {
                                passAsLepGenSemiLepCtr += 1;
                                passAsLepGenSemiLepWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 2) {
                                passAsLepGenHadCtr += 1;
                                passAsLepGenHadWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 3) {
                                passAsLepGenOtherCtr += 1;
                                passAsLepGenOtherWeightedCtr += tmpGenWeights;
                            }
                        }
                        else {
                            if (*genChannelL == 0) {
                                passAsLepGenLepNoHTobbCtr += 1;
                                passAsLepGenLepNoHTobbWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 1) {
                                passAsLepGenSemiLepNoHTobbCtr += 1;
                                passAsLepGenSemiLepNoHTobbWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 2) {
                                passAsLepGenHadNoHTobbCtr += 1;
                                passAsLepGenHadNoHTobbWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 3) {
                                passAsLepGenOtherNoHTobbCtr += 1;
                                passAsLepGenOtherNoHTobbWeightedCtr += tmpGenWeights;
                            }
                        }
                    }
                    
                    
                }
                
                else if (passedAsSemiLepBool){


                    passAsSemiLepCtr += 1;
                    passAsSemiLepWeightedCtr += tmpGenWeights;
                    if (!isBackground){ 
                        if (*HTobbBoolL){
                            if (*genChannelL == 0) {
                                passAsSemiLepGenLepCtr += 1;
                                passAsSemiLepGenLepWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 1) {
                                passAsSemiLepGenSemiLepCtr += 1;
                                passAsSemiLepGenSemiLepWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 2) {
                                passAsSemiLepGenHadCtr += 1;
                                passAsSemiLepGenHadWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 3) {
                                passAsSemiLepGenOtherCtr += 1;
                                passAsSemiLepGenOtherWeightedCtr += tmpGenWeights;
                            }
                        }
                        else {
                            if (*genChannelL == 0) {
                                passAsSemiLepGenLepNoHTobbCtr += 1;
                                passAsSemiLepGenLepNoHTobbWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 1) {
                                passAsSemiLepGenSemiLepNoHTobbCtr += 1;
                                passAsSemiLepGenSemiLepNoHTobbWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 2) {
                                passAsSemiLepGenHadNoHTobbCtr += 1;
                                passAsSemiLepGenHadNoHTobbWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 3) {
                                passAsSemiLepGenOtherNoHTobbCtr += 1;
                                passAsSemiLepGenOtherNoHTobbWeightedCtr += tmpGenWeights;
                            }
                        }
                    }
                    nFJL = *nFatJetL;
                    nJL = *nJetL;
                    AfterCutGenSemiLepWeightL = *genWeightL;
                    AfterCutSemiLepInvMassTree->Fill();
                    

                }
                else if (passedAsHadBool) {

                    passAsHadCtr += 1;
                    passAsHadWeightedCtr += tmpGenWeights;
                    if (!isBackground){ 
                        if (*HTobbBoolL){
                            if (*genChannelL == 0) {
                                passAsHadGenLepCtr += 1;
                                passAsHadGenLepWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 1) {
                                passAsHadGenSemiLepCtr += 1;
                                passAsHadGenSemiLepWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 2) {
                                passAsHadGenHadCtr += 1;
                                passAsHadGenHadWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 3) {
                                passAsHadGenOtherCtr += 1;
                                passAsHadGenOtherWeightedCtr += tmpGenWeights;
                            }
                        }
                        else {
                            if (*genChannelL == 0) {
                                passAsHadGenLepNoHTobbCtr += 1;
                                passAsHadGenLepNoHTobbWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 1) {
                                passAsHadGenSemiLepNoHTobbCtr += 1;
                                passAsHadGenSemiLepNoHTobbWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 2) {
                                passAsHadGenHadNoHTobbCtr += 1;
                                passAsHadGenHadNoHTobbWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 3) {
                                passAsHadGenOtherNoHTobbCtr += 1;
                                passAsHadGenOtherNoHTobbWeightedCtr += tmpGenWeights;
                            }
                        }
                    }
                }

            }

        }
    }
    if (debug) std::cout << "Filling complete \n";

    clock_t endt = clock();
    double time_spent = (double)(endt - startt) / CLOCKS_PER_SEC;


    std::cout << "Finished file loop. " << "time: " << time_spent << "\n";
    if (!isBackground){
        crossSection = crossSectionAvg / crossSectionCnt;
        
        //std::cout << "XS: " << dataXS << "\n";
    }
    std::cout << "XS: " << crossSection << "\n";
    std::cout << "nEv total: " << datanEv << "\n";
    std::cout << "nEv post pre-selection: " << datanEvPass << "\n"; 
    

    //--------------------HTobbChannel Output--------------
    std::cout << "==============================TOTAL COUNTERS==============================\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "startingCtr = " << startingCtr << "\n";
    std::cout << "Double_t " << saveName << "startingWeightedCtr = " << startingWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "tryingSemiLepChannelCtr = " << tryingSemiLepChannelCtr << "\n";
    std::cout << "Double_t " << saveName << "tryingSemiLepChannelWeightedCtr = " << tryingSemiLepChannelWeightedCtr << "\n";
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
    std::cout << "==============================HTOBB GEN CHANNEL COUNTERS==============================\n";
    std::cout << "\n";
    std::cout << "++++++++++++++++++++++++++++++GEN LEP CHANNEL COUNTERS++++++++++++++++++++++++++++++\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "startingGenLepCtr = " << startingGenLepCtr << "\n";
    std::cout << "Double_t " << saveName << "startingGenLepWeightedCtr = " << startingGenLepWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "tryingSemiLepChannelGenLepCtr = " << tryingSemiLepChannelGenLepCtr << "\n";
    std::cout << "Double_t " << saveName << "tryingSemiLepChannelGenLepWeightedCtr = " << tryingSemiLepChannelGenLepWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "passEnoughLepsInSemiLepChannelGenLepCtr = " << passEnoughLepsInSemiLepChannelGenLepCtr << "\n";
    std::cout << "Double_t " << saveName << "passEnoughLepsInSemiLepChannelGenLepWeightedCtr = " << passEnoughLepsInSemiLepChannelGenLepWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "passSemiLepLepCutGenLepCtr = " << passSemiLepLepCutGenLepCtr << "\n";
    std::cout << "Double_t " << saveName << "passSemiLepLepCutGenLepWeightedCtr = " << passSemiLepLepCutGenLepWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "passFJInSemiLepChannelGenLepCtr = " << passFJInSemiLepChannelGenLepCtr << "\n";
    std::cout << "Double_t " << saveName << "passFJInSemiLepChannelGenLepWeightedCtr = " << passFJInSemiLepChannelGenLepWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassChannelGenLepCtr = " << passChannelGenLepCtr << "\n";
    std::cout << "Double_t " << saveName << "PassChannelGenLepWeightedCtr = " << passChannelGenLepWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassLepOrSemiLepChannelGenLepCtr = " << passLepOrSemiLepChannelGenLepCtr << "\n";
    std::cout << "Double_t " << saveName << "PassLepOrSemiLepChannelGenLepWeightedCtr = " << passLepOrSemiLepChannelGenLepWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassLepChannelGenLepCtr = " << passLepChannelGenLepCtr << "\n";
    std::cout << "Double_t " << saveName << "PassLepChannelGenLepWeightedCtr = " << passLepChannelGenLepWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassSemiLepChannelGenLepCtr = " << passSemiLepChannelGenLepCtr << "\n";
    std::cout << "Double_t " << saveName << "PassSemiLepChannelGenLepWeightedCtr = " << passSemiLepChannelGenLepWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHadChannelGenLepCtr = " << passHadChannelGenLepCtr << "\n";
    std::cout << "Double_t " << saveName << "PassHadChannelGenLepWeightedCtr = " << passHadChannelGenLepWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJGenLepCtr = " << passHiggsFJGenLepCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJGenLepWeightedCtr = " << passHiggsFJGenLepWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJLepGenLepCtr = " << passHiggsFJLepGenLepCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJWeightedLepGenLepCtr = " << passHiggsFJWeightedLepGenLepCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJSemiLepGenLepCtr = " << passHiggsFJSemiLepGenLepCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJWeightedSemiLepGenLepCtr = " << passHiggsFJWeightedSemiLepGenLepCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJHadGenLepCtr = " << passHiggsFJHadGenLepCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJWeightedHadGenLepCtr = " << passHiggsFJWeightedHadGenLepCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassVBFJetsGenLepCtr = " << passVBFJetsGenLepCtr << "\n";
    std::cout << "Double_t " << saveName << "PassVBFJetsGenLepWeightedCtr = " << passVBFJetsGenLepWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassAsLepGenLepCtr = " << passAsLepGenLepCtr << "\n";
    std::cout << "Double_t " << saveName << "PassAsLepGenLepWeightedCtr = " << passAsLepGenLepWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassAsSemiLepGenLepCtr = " << passAsSemiLepGenLepCtr << "\n";
    std::cout << "Double_t " << saveName << "PassAsSemiLepGenLepWeightedCtr = " << passAsSemiLepGenLepWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassAsHadGenLepCtr = " << passAsHadGenLepCtr << "\n";
    std::cout << "Double_t " << saveName << "PassAsHadGenLepWeightedCtr = " << passAsHadGenLepWeightedCtr << "\n";
    std::cout << "------------------------\n";

    std::cout << "\n";
    std::cout << "++++++++++++++++++++++++++++++GEN SEMI LEP CHANNEL COUNTERS++++++++++++++++++++++++++++++\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "startingGenSemiLepCtr = " << startingGenSemiLepCtr << "\n";
    std::cout << "Double_t " << saveName << "startingGenSemiLepWeightedCtr = " << startingGenSemiLepWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "tryingSemiLepChannelGenSemiLepCtr = " << tryingSemiLepChannelGenSemiLepCtr << "\n";
    std::cout << "Double_t " << saveName << "tryingSemiLepChannelGenSemiLepWeightedCtr = " << tryingSemiLepChannelGenSemiLepWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "passEnoughLepsInSemiLepChannelGenSemiLepCtr = " << passEnoughLepsInSemiLepChannelGenSemiLepCtr << "\n";
    std::cout << "Double_t " << saveName << "passEnoughLepsInSemiLepChannelGenSemiLepWeightedCtr = " << passEnoughLepsInSemiLepChannelGenSemiLepWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "passSemiLepLepCutGenSemiLepCtr = " << passSemiLepLepCutGenSemiLepCtr << "\n";
    std::cout << "Double_t " << saveName << "passSemiLepLepCutGenSemiLepWeightedCtr = " << passSemiLepLepCutGenSemiLepWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "passFJInSemiLepChannelGenSemiLepCtr = " << passFJInSemiLepChannelGenSemiLepCtr << "\n";
    std::cout << "Double_t " << saveName << "passFJInSemiLepChannelGenSemiLepWeightedCtr = " << passFJInSemiLepChannelGenSemiLepWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassChannelGenSemiLepCtr = " << passChannelGenSemiLepCtr << "\n";
    std::cout << "Double_t " << saveName << "PassChannelGenSemiLepWeightedCtr = " << passChannelGenSemiLepWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassLepOrSemiLepChannelGenSemiLepCtr = " << passLepOrSemiLepChannelGenSemiLepCtr << "\n";
    std::cout << "Double_t " << saveName << "PassLepOrSemiLepChannelGenSemiLepWeightedCtr = " << passLepOrSemiLepChannelGenSemiLepWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassLepChannelGenSemiLepCtr = " << passLepChannelGenSemiLepCtr << "\n";
    std::cout << "Double_t " << saveName << "PassLepChannelGenSemiLepWeightedCtr = " << passLepChannelGenSemiLepWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassSemiLepChannelGenSemiLepCtr = " << passSemiLepChannelGenSemiLepCtr << "\n";
    std::cout << "Double_t " << saveName << "PassSemiLepChannelGenSemiLepWeightedCtr = " << passSemiLepChannelGenSemiLepWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHadChannelGenSemiLepCtr = " << passHadChannelGenSemiLepCtr << "\n";
    std::cout << "Double_t " << saveName << "PassHadChannelGenSemiLepWeightedCtr = " << passHadChannelGenSemiLepWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJGenSemiLepCtr = " << passHiggsFJGenSemiLepCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJGenSemiLepWeightedCtr = " << passHiggsFJGenSemiLepWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJLepGenSemiLepCtr = " << passHiggsFJLepGenSemiLepCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJWeightedLepGenSemiLepCtr = " << passHiggsFJWeightedLepGenSemiLepCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJSemiLepGenSemiLepCtr = " << passHiggsFJSemiLepGenSemiLepCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJWeightedSemiLepGenSemiLepCtr = " << passHiggsFJWeightedSemiLepGenSemiLepCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJHadGenSemiLepCtr = " << passHiggsFJHadGenSemiLepCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJWeightedHadGenSemiLepCtr = " << passHiggsFJWeightedHadGenSemiLepCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassVBFJetsGenSemiLepCtr = " << passVBFJetsGenSemiLepCtr << "\n";
    std::cout << "Double_t " << saveName << "PassVBFJetsGenSemiLepWeightedCtr = " << passVBFJetsGenSemiLepWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassAsLepGenSemiLepCtr = " << passAsLepGenSemiLepCtr << "\n";
    std::cout << "Double_t " << saveName << "PassAsLepGenSemiLepWeightedCtr = " << passAsLepGenSemiLepWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassAsSemiLepGenSemiLepCtr = " << passAsSemiLepGenSemiLepCtr << "\n";
    std::cout << "Double_t " << saveName << "PassAsSemiLepGenSemiLepWeightedCtr = " << passAsSemiLepGenSemiLepWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassAsHadGenSemiLepCtr = " << passAsHadGenSemiLepCtr << "\n";
    std::cout << "Double_t " << saveName << "PassAsHadGenSemiLepWeightedCtr = " << passAsHadGenSemiLepWeightedCtr << "\n";
    std::cout << "------------------------\n";

    std::cout << "\n";
    std::cout << "++++++++++++++++++++++++++++++GEN HAD CHANNEL COUNTERS++++++++++++++++++++++++++++++\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "startingGenHadCtr = " << startingGenHadCtr << "\n";
    std::cout << "Double_t " << saveName << "startingGenHadWeightedCtr = " << startingGenHadWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "tryingSemiLepChannelGenHadCtr = " << tryingSemiLepChannelGenHadCtr << "\n";
    std::cout << "Double_t " << saveName << "tryingSemiLepChannelGenHadWeightedCtr = " << tryingSemiLepChannelGenHadWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "passEnoughLepsInSemiLepChannelGenHadCtr = " << passEnoughLepsInSemiLepChannelGenHadCtr << "\n";
    std::cout << "Double_t " << saveName << "passEnoughLepsInSemiLepChannelGenHadWeightedCtr = " << passEnoughLepsInSemiLepChannelGenHadWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "passSemiLepLepCutGenHadCtr = " << passSemiLepLepCutGenHadCtr << "\n";
    std::cout << "Double_t " << saveName << "passSemiLepLepCutGenHadWeightedCtr = " << passSemiLepLepCutGenHadWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "passFJInSemiLepChannelGenHadCtr = " << passFJInSemiLepChannelGenHadCtr << "\n";
    std::cout << "Double_t " << saveName << "passFJInSemiLepChannelGenHadWeightedCtr = " << passFJInSemiLepChannelGenHadWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassChannelGenHadCtr = " << passChannelGenHadCtr << "\n";
    std::cout << "Double_t " << saveName << "PassChannelGenHadWeightedCtr = " << passChannelGenHadWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassLepOrSemiLepChannelGenHadCtr = " << passLepOrSemiLepChannelGenHadCtr << "\n";
    std::cout << "Double_t " << saveName << "PassLepOrSemiLepChannelGenHadWeightedCtr = " << passLepOrSemiLepChannelGenHadWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassLepChannelGenHadCtr = " << passLepChannelGenHadCtr << "\n";
    std::cout << "Double_t " << saveName << "PassLepChannelGenHadWeightedCtr = " << passLepChannelGenHadWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassSemiLepChannelGenHadCtr = " << passSemiLepChannelGenHadCtr << "\n";
    std::cout << "Double_t " << saveName << "PassSemiLepChannelGenHadWeightedCtr = " << passSemiLepChannelGenHadWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHadChannelGenHadCtr = " << passHadChannelGenHadCtr << "\n";
    std::cout << "Double_t " << saveName << "PassHadChannelGenHadWeightedCtr = " << passHadChannelGenHadWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJGenHadCtr = " << passHiggsFJGenHadCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJGenHadWeightedCtr = " << passHiggsFJGenHadWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJLepGenHadCtr = " << passHiggsFJLepGenHadCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJWeightedLepGenHadCtr = " << passHiggsFJWeightedLepGenHadCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJSemiLepGenHadCtr = " << passHiggsFJSemiLepGenHadCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJWeightedSemiLepGenHadCtr = " << passHiggsFJWeightedSemiLepGenHadCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJHadGenHadCtr = " << passHiggsFJHadGenHadCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJWeightedHadGenHadCtr = " << passHiggsFJWeightedHadGenHadCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassVBFJetsGenHadCtr = " << passVBFJetsGenHadCtr << "\n";
    std::cout << "Double_t " << saveName << "PassVBFJetsGenHadWeightedCtr = " << passVBFJetsGenHadWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassAsLepGenHadCtr = " << passAsLepGenHadCtr << "\n";
    std::cout << "Double_t " << saveName << "PassAsLepGenHadWeightedCtr = " << passAsLepGenHadWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassAsSemiLepGenHadCtr = " << passAsSemiLepGenHadCtr << "\n";
    std::cout << "Double_t " << saveName << "PassAsSemiLepGenHadWeightedCtr = " << passAsSemiLepGenHadWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassAsHadGenHadCtr = " << passAsHadGenHadCtr << "\n";
    std::cout << "Double_t " << saveName << "PassAsHadGenHadWeightedCtr = " << passAsHadGenHadWeightedCtr << "\n";
    std::cout << "------------------------\n";

    std::cout << "\n";
    std::cout << "++++++++++++++++++++++++++++++GEN OTHER CHANNEL COUNTERS++++++++++++++++++++++++++++++\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "startingGenOtherCtr = " << startingGenOtherCtr << "\n";
    std::cout << "Double_t " << saveName << "startingGenOtherWeightedCtr = " << startingGenOtherWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "tryingSemiLepChannelGenOtherCtr = " << tryingSemiLepChannelGenOtherCtr << "\n";
    std::cout << "Double_t " << saveName << "tryingSemiLepChannelGenOtherWeightedCtr = " << tryingSemiLepChannelGenOtherWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "passEnoughLepsInSemiLepChannelGenOtherCtr = " << passEnoughLepsInSemiLepChannelGenOtherCtr << "\n";
    std::cout << "Double_t " << saveName << "passEnoughLepsInSemiLepChannelGenOtherWeightedCtr = " << passEnoughLepsInSemiLepChannelGenOtherWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "passSemiLepLepCutGenOtherCtr = " << passSemiLepLepCutGenOtherCtr << "\n";
    std::cout << "Double_t " << saveName << "passSemiLepLepCutGenOtherWeightedCtr = " << passSemiLepLepCutGenOtherWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "passFJInSemiLepChannelGenOtherCtr = " << passFJInSemiLepChannelGenOtherCtr << "\n";
    std::cout << "Double_t " << saveName << "passFJInSemiLepChannelGenOtherWeightedCtr = " << passFJInSemiLepChannelGenOtherWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassChannelGenOtherCtr = " << passChannelGenOtherCtr << "\n";
    std::cout << "Double_t " << saveName << "PassChannelGenOtherWeightedCtr = " << passChannelGenOtherWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassLepOrSemiLepChannelGenOtherCtr = " << passLepOrSemiLepChannelGenOtherCtr << "\n";
    std::cout << "Double_t " << saveName << "PassLepOrSemiLepChannelGenOtherWeightedCtr = " << passLepOrSemiLepChannelGenOtherWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassLepChannelGenOtherCtr = " << passLepChannelGenOtherCtr << "\n";
    std::cout << "Double_t " << saveName << "PassLepChannelGenOtherWeightedCtr = " << passLepChannelGenOtherWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassSemiLepChannelGenOtherCtr = " << passSemiLepChannelGenOtherCtr << "\n";
    std::cout << "Double_t " << saveName << "PassSemiLepChannelGenOtherWeightedCtr = " << passSemiLepChannelGenOtherWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHadChannelGenOtherCtr = " << passHadChannelGenOtherCtr << "\n";
    std::cout << "Double_t " << saveName << "PassHadChannelGenOtherWeightedCtr = " << passHadChannelGenOtherWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJGenOtherCtr = " << passHiggsFJGenOtherCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJGenOtherWeightedCtr = " << passHiggsFJGenOtherWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJLepGenOtherCtr = " << passHiggsFJLepGenOtherCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJWeightedLepGenOtherCtr = " << passHiggsFJWeightedLepGenOtherCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJSemiLepGenOtherCtr = " << passHiggsFJSemiLepGenOtherCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJWeightedSemiLepGenOtherCtr = " << passHiggsFJWeightedSemiLepGenOtherCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJHadGenOtherCtr = " << passHiggsFJHadGenOtherCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJWeightedHadGenOtherCtr = " << passHiggsFJWeightedHadGenOtherCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassVBFJetsGenOtherCtr = " << passVBFJetsGenOtherCtr << "\n";
    std::cout << "Double_t " << saveName << "PassVBFJetsGenOtherWeightedCtr = " << passVBFJetsGenOtherWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassAsLepGenOtherCtr = " << passAsLepGenOtherCtr << "\n";
    std::cout << "Double_t " << saveName << "PassAsLepGenOtherWeightedCtr = " << passAsLepGenOtherWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassAsSemiLepGenOtherCtr = " << passAsSemiLepGenOtherCtr << "\n";
    std::cout << "Double_t " << saveName << "PassAsSemiLepGenOtherWeightedCtr = " << passAsSemiLepGenOtherWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassAsHadGenOtherCtr = " << passAsHadGenOtherCtr << "\n";
    std::cout << "Double_t " << saveName << "PassAsHadGenOtherWeightedCtr = " << passAsHadGenOtherWeightedCtr << "\n";
    std::cout << "------------------------\n";


    //---------------------- No HTobbChannel Counters -----------------------

    std::cout << "\n";
    std::cout << "==============================NO HTOBB GEN CHANNEL COUNTERS==============================\n";
    std::cout << "\n";
    std::cout << "++++++++++++++++++++++++++++++GEN LEP CHANNEL COUNTERS++++++++++++++++++++++++++++++\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "startingGenLepNoHTobbCtr = " << startingGenLepNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "startingGenLepNoHTobbWeightedCtr = " << startingGenLepNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "tryingSemiLepChannelGenLepNoHTobbCtr = " << tryingSemiLepChannelGenLepNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "tryingSemiLepChannelGenLepNoHTobbWeightedCtr = " << tryingSemiLepChannelGenLepNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "passEnoughLepsInSemiLepChannelGenLepNoHTobbCtr = " << passEnoughLepsInSemiLepChannelGenLepNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passEnoughLepsInSemiLepChannelGenLepNoHTobbWeightedCtr = " << passEnoughLepsInSemiLepChannelGenLepNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "passSemiLepLepCutGenLepNoHTobbCtr = " << passSemiLepLepCutGenLepNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passSemiLepLepCutGenLepNoHTobbWeightedCtr = " << passSemiLepLepCutGenLepNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "passFJInSemiLepChannelGenLepNoHTobbCtr = " << passFJInSemiLepChannelGenLepNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passFJInSemiLepChannelGenLepNoHTobbWeightedCtr = " << passFJInSemiLepChannelGenLepNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassChannelGenLepNoHTobbCtr = " << passChannelGenLepNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "PassChannelGenLepNoHTobbWeightedCtr = " << passChannelGenLepNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassLepOrSemiLepChannelGenLepNoHTobbCtr = " << passLepOrSemiLepChannelGenLepNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "PassLepOrSemiLepChannelGenLepNoHTobbWeightedCtr = " << passLepOrSemiLepChannelGenLepNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassLepChannelGenLepNoHTobbCtr = " << passLepChannelGenLepNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "PassLepChannelGenLepNoHTobbWeightedCtr = " << passLepChannelGenLepNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassSemiLepChannelGenLepNoHTobbCtr = " << passSemiLepChannelGenLepNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "PassSemiLepChannelGenLepNoHTobbWeightedCtr = " << passSemiLepChannelGenLepNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHadChannelGenLepNoHTobbCtr = " << passHadChannelGenLepNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "PassHadChannelGenLepNoHTobbWeightedCtr = " << passHadChannelGenLepNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJGenLepNoHTobbCtr = " << passHiggsFJGenLepNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJGenLepNoHTobbWeightedCtr = " << passHiggsFJGenLepNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJLepGenLepNoHTobbCtr = " << passHiggsFJLepGenLepNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJWeightedLepGenLepNoHTobbCtr = " << passHiggsFJWeightedLepGenLepNoHTobbCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJSemiLepGenLepNoHTobbCtr = " << passHiggsFJSemiLepGenLepNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJWeightedSemiLepGenLepNoHTobbCtr = " << passHiggsFJWeightedSemiLepGenLepNoHTobbCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJHadGenLepNoHTobbCtr = " << passHiggsFJHadGenLepNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJWeightedHadGenLepNoHTobbCtr = " << passHiggsFJWeightedHadGenLepNoHTobbCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassVBFJetsGenLepNoHTobbCtr = " << passVBFJetsGenLepNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "PassVBFJetsGenLepNoHTobbWeightedCtr = " << passVBFJetsGenLepNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassAsLepGenLepNoHTobbCtr = " << passAsLepGenLepNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "PassAsLepGenLepNoHTobbWeightedCtr = " << passAsLepGenLepNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassAsSemiLepGenLepNoHTobbCtr = " << passAsSemiLepGenLepNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "PassAsSemiLepGenLepNoHTobbWeightedCtr = " << passAsSemiLepGenLepNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassAsHadGenLepNoHTobbCtr = " << passAsHadGenLepNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "PassAsHadGenLepNoHTobbWeightedCtr = " << passAsHadGenLepNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";

    std::cout << "\n";
    std::cout << "++++++++++++++++++++++++++++++GEN SEMI LEP CHANNEL COUNTERS++++++++++++++++++++++++++++++\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "startingGenSemiLepNoHTobbCtr = " << startingGenSemiLepNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "startingGenSemiLepNoHTobbWeightedCtr = " << startingGenSemiLepNoHTobbWeightedCtr << "\n";

    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "tryingSemiLepChannelGenSemiLepNoHTobbCtr = " << tryingSemiLepChannelGenSemiLepNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "tryingSemiLepChannelGenSemiLepNoHTobbWeightedCtr = " << tryingSemiLepChannelGenSemiLepNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "passEnoughLepsInSemiLepChannelGenSemiLepNoHTobbCtr = " << passEnoughLepsInSemiLepChannelGenSemiLepNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passEnoughLepsInSemiLepChannelGenSemiLepNoHTobbWeightedCtr = " << passEnoughLepsInSemiLepChannelGenSemiLepNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "passSemiLepLepCutGenSemiLepNoHTobbCtr = " << passSemiLepLepCutGenSemiLepNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passSemiLepLepCutGenSemiLepNoHTobbWeightedCtr = " << passSemiLepLepCutGenSemiLepNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "passFJInSemiLepChannelGenSemiLepNoHTobbCtr = " << passFJInSemiLepChannelGenSemiLepNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passFJInSemiLepChannelGenSemiLepNoHTobbWeightedCtr = " << passFJInSemiLepChannelGenSemiLepNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassChannelGenSemiLepNoHTobbCtr = " << passChannelGenSemiLepNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "PassChannelGenSemiLepNoHTobbWeightedCtr = " << passChannelGenSemiLepNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassLepOrSemiLepChannelGenSemiLepNoHTobbCtr = " << passLepOrSemiLepChannelGenSemiLepNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "PassLepOrSemiLepChannelGenSemiLepNoHTobbWeightedCtr = " << passLepOrSemiLepChannelGenSemiLepNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassLepChannelGenSemiLepNoHTobbCtr = " << passLepChannelGenSemiLepNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "PassLepChannelGenSemiLepNoHTobbWeightedCtr = " << passLepChannelGenSemiLepNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassSemiLepChannelGenSemiLepNoHTobbCtr = " << passSemiLepChannelGenSemiLepNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "PassSemiLepChannelGenSemiLepNoHTobbWeightedCtr = " << passSemiLepChannelGenSemiLepNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHadChannelGenSemiLepNoHTobbCtr = " << passHadChannelGenSemiLepNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "PassHadChannelGenSemiLepNoHTobbWeightedCtr = " << passHadChannelGenSemiLepNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJGenSemiLepNoHTobbCtr = " << passHiggsFJGenSemiLepNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJGenSemiLepNoHTobbWeightedCtr = " << passHiggsFJGenSemiLepNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJLepGenSemiLepNoHTobbCtr = " << passHiggsFJLepGenSemiLepNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJWeightedLepGenSemiLepNoHTobbCtr = " << passHiggsFJWeightedLepGenSemiLepNoHTobbCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJSemiLepGenSemiLepNoHTobbCtr = " << passHiggsFJSemiLepGenSemiLepNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJWeightedSemiLepGenSemiLepNoHTobbCtr = " << passHiggsFJWeightedSemiLepGenSemiLepNoHTobbCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJHadGenSemiLepNoHTobbCtr = " << passHiggsFJHadGenSemiLepNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJWeightedHadGenSemiLepNoHTobbCtr = " << passHiggsFJWeightedHadGenSemiLepNoHTobbCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassVBFJetsGenSemiLepNoHTobbCtr = " << passVBFJetsGenSemiLepNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "PassVBFJetsGenSemiLepNoHTobbWeightedCtr = " << passVBFJetsGenSemiLepNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassAsLepGenSemiLepNoHTobbCtr = " << passAsLepGenSemiLepNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "PassAsLepGenSemiLepNoHTobbWeightedCtr = " << passAsLepGenSemiLepNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassAsSemiLepGenSemiLepNoHTobbCtr = " << passAsSemiLepGenSemiLepNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "PassAsSemiLepGenSemiLepNoHTobbWeightedCtr = " << passAsSemiLepGenSemiLepNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassAsHadGenSemiLepNoHTobbCtr = " << passAsHadGenSemiLepNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "PassAsHadGenSemiLepNoHTobbWeightedCtr = " << passAsHadGenSemiLepNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";

    std::cout << "\n";
    std::cout << "++++++++++++++++++++++++++++++GEN HAD CHANNEL COUNTERS++++++++++++++++++++++++++++++\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "startingGenHadNoHTobbCtr = " << startingGenHadNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "startingGenHadNoHTobbWeightedCtr = " << startingGenHadNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "tryingSemiLepChannelGenHadNoHTobbCtr = " << tryingSemiLepChannelGenHadNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "tryingSemiLepChannelGenHadNoHTobbWeightedCtr = " << tryingSemiLepChannelGenHadNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "passEnoughLepsInSemiLepChannelGenHadNoHTobbCtr = " << passEnoughLepsInSemiLepChannelGenHadNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passEnoughLepsInSemiLepChannelGenHadNoHTobbWeightedCtr = " << passEnoughLepsInSemiLepChannelGenHadNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "passSemiLepLepCutGenHadNoHTobbCtr = " << passSemiLepLepCutGenHadNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passSemiLepLepCutGenHadNoHTobbWeightedCtr = " << passSemiLepLepCutGenHadNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "passFJInSemiLepChannelGenHadNoHTobbCtr = " << passFJInSemiLepChannelGenHadNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passFJInSemiLepChannelGenHadNoHTobbWeightedCtr = " << passFJInSemiLepChannelGenHadNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassChannelGenHadNoHTobbCtr = " << passChannelGenHadNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "PassChannelGenHadNoHTobbWeightedCtr = " << passChannelGenHadNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassLepOrSemiLepChannelGenHadNoHTobbCtr = " << passLepOrSemiLepChannelGenHadNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "PassLepOrSemiLepChannelGenHadNoHTobbWeightedCtr = " << passLepOrSemiLepChannelGenHadNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassLepChannelGenHadNoHTobbCtr = " << passLepChannelGenHadNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "PassLepChannelGenHadNoHTobbWeightedCtr = " << passLepChannelGenHadNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassSemiLepChannelGenHadNoHTobbCtr = " << passSemiLepChannelGenHadNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "PassSemiLepChannelGenHadNoHTobbWeightedCtr = " << passSemiLepChannelGenHadNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHadChannelGenHadNoHTobbCtr = " << passHadChannelGenHadNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "PassHadChannelGenHadNoHTobbWeightedCtr = " << passHadChannelGenHadNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJGenHadNoHTobbCtr = " << passHiggsFJGenHadNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJGenHadNoHTobbWeightedCtr = " << passHiggsFJGenHadNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJLepGenHadNoHTobbCtr = " << passHiggsFJLepGenHadNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJWeightedLepGenHadNoHTobbCtr = " << passHiggsFJWeightedLepGenHadNoHTobbCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJSemiLepGenHadNoHTobbCtr = " << passHiggsFJSemiLepGenHadNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJWeightedSemiLepGenHadNoHTobbCtr = " << passHiggsFJWeightedSemiLepGenHadNoHTobbCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJHadGenHadNoHTobbCtr = " << passHiggsFJHadGenHadNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJWeightedHadGenHadNoHTobbCtr = " << passHiggsFJWeightedHadGenHadNoHTobbCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassVBFJetsGenHadNoHTobbCtr = " << passVBFJetsGenHadNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "PassVBFJetsGenHadNoHTobbWeightedCtr = " << passVBFJetsGenHadNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassAsLepGenHadNoHTobbCtr = " << passAsLepGenHadNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "PassAsLepGenHadNoHTobbWeightedCtr = " << passAsLepGenHadNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassAsSemiLepGenHadNoHTobbCtr = " << passAsSemiLepGenHadNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "PassAsSemiLepGenHadNoHTobbWeightedCtr = " << passAsSemiLepGenHadNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassAsHadGenHadNoHTobbCtr = " << passAsHadGenHadNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "PassAsHadGenHadNoHTobbWeightedCtr = " << passAsHadGenHadNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";

    std::cout << "\n";
    std::cout << "++++++++++++++++++++++++++++++GEN OTHER CHANNEL COUNTERS++++++++++++++++++++++++++++++\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "startingGenOtherNoHTobbCtr = " << startingGenOtherNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "startingGenOtherNoHTobbWeightedCtr = " << startingGenOtherNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "tryingSemiLepChannelGenOtherNoHTobbCtr = " << tryingSemiLepChannelGenOtherNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "tryingSemiLepChannelGenOtherNoHTobbWeightedCtr = " << tryingSemiLepChannelGenOtherNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "passEnoughLepsInSemiLepChannelGenOtherNoHTobbCtr = " << passEnoughLepsInSemiLepChannelGenOtherNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passEnoughLepsInSemiLepChannelGenOtherNoHTobbWeightedCtr = " << passEnoughLepsInSemiLepChannelGenOtherNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "passSemiLepLepCutGenOtherNoHTobbCtr = " << passSemiLepLepCutGenOtherNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passSemiLepLepCutGenOtherNoHTobbWeightedCtr = " << passSemiLepLepCutGenOtherNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "passFJInSemiLepChannelGenOtherNoHTobbCtr = " << passFJInSemiLepChannelGenOtherNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passFJInSemiLepChannelGenOtherNoHTobbWeightedCtr = " << passFJInSemiLepChannelGenOtherNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassChannelGenOtherNoHTobbCtr = " << passChannelGenOtherNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "PassChannelGenOtherNoHTobbWeightedCtr = " << passChannelGenOtherNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassLepOrSemiLepChannelGenOtherNoHTobbCtr = " << passLepOrSemiLepChannelGenOtherNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "PassLepOrSemiLepChannelGenOtherNoHTobbWeightedCtr = " << passLepOrSemiLepChannelGenOtherNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassLepChannelGenOtherNoHTobbCtr = " << passLepChannelGenOtherNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "PassLepChannelGenOtherNoHTobbWeightedCtr = " << passLepChannelGenOtherNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassSemiLepChannelGenOtherNoHTobbCtr = " << passSemiLepChannelGenOtherNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "PassSemiLepChannelGenOtherNoHTobbWeightedCtr = " << passSemiLepChannelGenOtherNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHadChannelGenOtherNoHTobbCtr = " << passHadChannelGenOtherNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "PassHadChannelGenOtherNoHTobbWeightedCtr = " << passHadChannelGenOtherNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJGenOtherNoHTobbCtr = " << passHiggsFJGenOtherNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJGenOtherNoHTobbWeightedCtr = " << passHiggsFJGenOtherNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJLepGenOtherNoHTobbCtr = " << passHiggsFJLepGenOtherNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJWeightedLepGenOtherNoHTobbCtr = " << passHiggsFJWeightedLepGenOtherNoHTobbCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJSemiLepGenOtherNoHTobbCtr = " << passHiggsFJSemiLepGenOtherNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJWeightedSemiLepGenOtherNoHTobbCtr = " << passHiggsFJWeightedSemiLepGenOtherNoHTobbCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJHadGenOtherNoHTobbCtr = " << passHiggsFJHadGenOtherNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJWeightedHadGenOtherNoHTobbCtr = " << passHiggsFJWeightedHadGenOtherNoHTobbCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassVBFJetsGenOtherNoHTobbCtr = " << passVBFJetsGenOtherNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "PassVBFJetsGenOtherNoHTobbWeightedCtr = " << passVBFJetsGenOtherNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassAsLepGenOtherNoHTobbCtr = " << passAsLepGenOtherNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "PassAsLepGenOtherNoHTobbWeightedCtr = " << passAsLepGenOtherNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassAsSemiLepGenOtherNoHTobbCtr = " << passAsSemiLepGenOtherNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "PassAsSemiLepGenOtherNoHTobbWeightedCtr = " << passAsSemiLepGenOtherNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassAsHadGenOtherNoHTobbCtr = " << passAsHadGenOtherNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "PassAsHadGenOtherNoHTobbWeightedCtr = " << passAsHadGenOtherNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";



    outFile->cd();
    BeforeCutLepInvMassTree->Write("",TObject::kOverwrite);
    BeforeCutSemiLepInvMassTree->Write("",TObject::kOverwrite);
    AfterCutSemiLepInvMassTree->Write("",TObject::kOverwrite);

    outFile->Close();

}