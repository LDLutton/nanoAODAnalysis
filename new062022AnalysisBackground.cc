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


void new062022AnalysisBackground(string datasetString){
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
    if (datasetString == "ZZ") ZZBackground = true;
    if (datasetString == "WW") WWBackground = true;
    if (datasetString == "WZ") WZBackground = true;
    if (datasetString == "TTbb_TTToHadronic") TTbb_TTToHadronicBackground = true;
    if (datasetString == "TTbb_TTToSemiLeptonic") TTbb_TTToSemiLeptonicBackground = true;
    if (datasetString == "TTbb_TTTo2L2Nu") TTbb_TTTo2L2NuBackground = true;

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
    else if (ZZBackground){
        //saveName = "";
        
        crossSection = 12.17;
        totWeight = 3526000.0;

        saveName = "ZZ";
        
        isBackground = true;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisZZ.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (WWBackground){
        //saveName = "";
        
        crossSection = 75.95;
        totWeight = 15679125.299999999;

        saveName = "WW";
        
        isBackground = true;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisWW.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (WZBackground){
        //saveName = "";
        
        crossSection = 27.59;
        totWeight = 7940000.0;

        saveName = "WZ";
        
        isBackground = true;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisWZ.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (TTbb_TTToHadronicBackground){
        //saveName = "QCDPT3200toInf";
        
        crossSection = 5.5;
        totWeight = 160749330.0;

        saveName = "TTbb_TTToHadronic";
        
        isBackground = true;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisTTbb_TTToHadronic.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (TTbb_TTTo2L2NuBackground){
        //saveName = "";
        
        crossSection = 2.9;
        totWeight = 21986500.0;

        saveName = "TTbb_TTTo2L2Nu";
        
        isBackground = true;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisTTbb_TTTo2L2Nu.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (TTbb_TTToSemiLeptonicBackground){
        //saveName = "";
        
        crossSection = 4.7;
        totWeight = 233964864.0;

        saveName = "TTbb_TTToSemiLeptonic";
        
        isBackground = true;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisTTbb_TTToSemiLeptonic.root";
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

    ////////////////////////////////GEN LEP COUNTERS////////////////////////////////

    UInt_t startingGenLepCtr = 0;

    UInt_t passHiggsFJPreSTGenLepCtr = 0;
    UInt_t passHiggsFJPreSTLepGenLepCtr = 0;
    UInt_t passHiggsFJPreSTSemiLepGenLepCtr = 0;
    UInt_t passHiggsFJPreSTHadGenLepCtr = 0;

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
    UInt_t passVBFJetBVetoGenLepCtr = 0;
    UInt_t passVBFJetsGenLepCtr = 0;
    UInt_t passAsLepGenLepCtr = 0;
    UInt_t passAsSemiLepGenLepCtr = 0;
    UInt_t passAsHadGenLepCtr = 0;
    
    Double_t startingGenLepWeightedCtr = 0.;

    Double_t passHiggsFJPreSTGenLepWeightedCtr = 0.;
    Double_t passHiggsFJPreSTWeightedLepGenLepCtr = 0.;
    Double_t passHiggsFJPreSTWeightedSemiLepGenLepCtr = 0.;
    Double_t passHiggsFJPreSTWeightedHadGenLepCtr = 0.;

    Double_t passHiggsFJGenLepWeightedCtr = 0.;
    Double_t passHiggsFJWeightedLepGenLepCtr = 0.;
    Double_t passHiggsFJWeightedSemiLepGenLepCtr = 0.;
    Double_t passHiggsFJWeightedHadGenLepCtr = 0.;
    Double_t passChannelGenLepWeightedCtr = 0.;
    Double_t passLepOrSemiLepChannelGenLepWeightedCtr = 0.;
    Double_t passLepChannelGenLepWeightedCtr = 0.;
    Double_t tryingSemiLepChannelGenLepWeightedCtr = 0.;
    Double_t passFJInSemiLepChannelGenLepWeightedCtr = 0.;
    Double_t passEnoughLepsInSemiLepChannelGenLepWeightedCtr = 0.;
    Double_t passLepCutInSemiLepChannelGenLepWeightedCtr = 0.;
    Double_t passSemiLepChannelGenLepWeightedCtr = 0.;
    Double_t passHadChannelGenLepWeightedCtr = 0.;
    Double_t passVBFJetBVetoGenLepWeightedCtr = 0.;
    Double_t passVBFJetsGenLepWeightedCtr = 0.;
    Double_t passAsLepGenLepWeightedCtr = 0.;
    Double_t passAsSemiLepGenLepWeightedCtr = 0.;
    Double_t passAsHadGenLepWeightedCtr = 0.;

    UInt_t passSemiLepLepCutGenLepCtr = 0;
    Double_t passSemiLepLepCutGenLepWeightedCtr = 0.;

    ////////////////////////////////GEN SEMILEP COUNTERS////////////////////////////////

    UInt_t startingGenSemiLepCtr = 0;

    UInt_t passHiggsFJPreSTGenSemiLepCtr = 0;
    UInt_t passHiggsFJPreSTLepGenSemiLepCtr = 0;
    UInt_t passHiggsFJPreSTSemiLepGenSemiLepCtr = 0;
    UInt_t passHiggsFJPreSTHadGenSemiLepCtr = 0;

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
    UInt_t passVBFJetBVetoGenSemiLepCtr = 0;
    UInt_t passVBFJetsGenSemiLepCtr = 0;
    UInt_t passAsLepGenSemiLepCtr = 0;
    UInt_t passAsSemiLepGenSemiLepCtr = 0;
    UInt_t passAsHadGenSemiLepCtr = 0;

    Double_t startingGenSemiLepWeightedCtr = 0.;

    Double_t passHiggsFJPreSTGenSemiLepWeightedCtr = 0.;
    Double_t passHiggsFJPreSTWeightedLepGenSemiLepCtr = 0.;
    Double_t passHiggsFJPreSTWeightedSemiLepGenSemiLepCtr = 0.;
    Double_t passHiggsFJPreSTWeightedHadGenSemiLepCtr = 0.;
    
    Double_t passHiggsFJGenSemiLepWeightedCtr = 0.;
    Double_t passHiggsFJWeightedLepGenSemiLepCtr = 0.;
    Double_t passHiggsFJWeightedSemiLepGenSemiLepCtr = 0.;
    Double_t passHiggsFJWeightedHadGenSemiLepCtr = 0.;
    Double_t passChannelGenSemiLepWeightedCtr = 0.;
    Double_t passLepOrSemiLepChannelGenSemiLepWeightedCtr = 0.;
    Double_t passLepChannelGenSemiLepWeightedCtr = 0.;
    Double_t tryingSemiLepChannelGenSemiLepWeightedCtr = 0.;
    Double_t passFJInSemiLepChannelGenSemiLepWeightedCtr = 0.;
    Double_t passEnoughLepsInSemiLepChannelGenSemiLepWeightedCtr = 0.;
    Double_t passLepCutInSemiLepChannelGenSemiLepWeightedCtr = 0.;
    Double_t passSemiLepChannelGenSemiLepWeightedCtr = 0.;
    Double_t passHadChannelGenSemiLepWeightedCtr = 0.;
    Double_t passVBFJetBVetoGenSemiLepWeightedCtr = 0.;
    Double_t passVBFJetsGenSemiLepWeightedCtr = 0.;
    Double_t passAsLepGenSemiLepWeightedCtr = 0.;
    Double_t passAsSemiLepGenSemiLepWeightedCtr = 0.;
    Double_t passAsHadGenSemiLepWeightedCtr = 0.;

    UInt_t passSemiLepLepCutGenSemiLepCtr = 0;
    Double_t passSemiLepLepCutGenSemiLepWeightedCtr = 0.;


    ////////////////////////////////GEN HAD COUNTERS////////////////////////////////

    UInt_t startingGenHadCtr = 0;

    UInt_t passHiggsFJPreSTGenHadCtr = 0;
    UInt_t passHiggsFJPreSTLepGenHadCtr = 0;
    UInt_t passHiggsFJPreSTSemiLepGenHadCtr = 0;
    UInt_t passHiggsFJPreSTHadGenHadCtr = 0;

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
    UInt_t passVBFJetBVetoGenHadCtr = 0;
    UInt_t passVBFJetsGenHadCtr = 0;
    UInt_t passAsLepGenHadCtr = 0;
    UInt_t passAsSemiLepGenHadCtr = 0;
    UInt_t passAsHadGenHadCtr = 0;
    
    Double_t startingGenHadWeightedCtr = 0.;

    Double_t passHiggsFJPreSTGenHadWeightedCtr = 0.;
    Double_t passHiggsFJPreSTWeightedLepGenHadCtr = 0.;
    Double_t passHiggsFJPreSTWeightedSemiLepGenHadCtr = 0.;
    Double_t passHiggsFJPreSTWeightedHadGenHadCtr = 0.;

    Double_t passHiggsFJGenHadWeightedCtr = 0.;
    Double_t passHiggsFJWeightedLepGenHadCtr = 0.;
    Double_t passHiggsFJWeightedSemiLepGenHadCtr = 0.;
    Double_t passHiggsFJWeightedHadGenHadCtr = 0.;
    Double_t passChannelGenHadWeightedCtr = 0.;
    Double_t passLepOrSemiLepChannelGenHadWeightedCtr = 0.;
    Double_t passLepChannelGenHadWeightedCtr = 0.;
    Double_t tryingSemiLepChannelGenHadWeightedCtr = 0.;
    Double_t passFJInSemiLepChannelGenHadWeightedCtr = 0.;
    Double_t passEnoughLepsInSemiLepChannelGenHadWeightedCtr = 0.;
    Double_t passLepCutInSemiLepChannelGenHadWeightedCtr = 0.;
    Double_t passSemiLepChannelGenHadWeightedCtr = 0.;
    Double_t passHadChannelGenHadWeightedCtr = 0.;
    Double_t passVBFJetBVetoGenHadWeightedCtr = 0.;
    Double_t passVBFJetsGenHadWeightedCtr = 0.;
    Double_t passAsLepGenHadWeightedCtr = 0.;
    Double_t passAsSemiLepGenHadWeightedCtr = 0.;
    Double_t passAsHadGenHadWeightedCtr = 0.;

    UInt_t passSemiLepLepCutGenHadCtr = 0;
    Double_t passSemiLepLepCutGenHadWeightedCtr = 0.;

    ////////////////////////////////GEN OTHER COUNTERS////////////////////////////////

    UInt_t startingGenOtherCtr = 0;

    UInt_t passHiggsFJPreSTGenOtherCtr = 0;
    UInt_t passHiggsFJPreSTLepGenOtherCtr = 0;
    UInt_t passHiggsFJPreSTSemiLepGenOtherCtr = 0;
    UInt_t passHiggsFJPreSTHadGenOtherCtr = 0;

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
    UInt_t passVBFJetBVetoGenOtherCtr = 0;
    UInt_t passVBFJetsGenOtherCtr = 0;
    UInt_t passAsLepGenOtherCtr = 0;
    UInt_t passAsSemiLepGenOtherCtr = 0;
    UInt_t passAsHadGenOtherCtr = 0;
    
    Double_t startingGenOtherWeightedCtr = 0.;

    Double_t passHiggsFJPreSTGenOtherWeightedCtr = 0.;
    Double_t passHiggsFJPreSTWeightedLepGenOtherCtr = 0.;
    Double_t passHiggsFJPreSTWeightedSemiLepGenOtherCtr = 0.;
    Double_t passHiggsFJPreSTWeightedHadGenOtherCtr = 0.;

    Double_t passHiggsFJGenOtherWeightedCtr = 0.;
    Double_t passHiggsFJWeightedLepGenOtherCtr = 0.;
    Double_t passHiggsFJWeightedSemiLepGenOtherCtr = 0.;
    Double_t passHiggsFJWeightedHadGenOtherCtr = 0.;
    Double_t passChannelGenOtherWeightedCtr = 0.;
    Double_t passLepOrSemiLepChannelGenOtherWeightedCtr = 0.;
    Double_t passLepChannelGenOtherWeightedCtr = 0.;
    Double_t tryingSemiLepChannelGenOtherWeightedCtr = 0.;
    Double_t passFJInSemiLepChannelGenOtherWeightedCtr = 0.;
    Double_t passEnoughLepsInSemiLepChannelGenOtherWeightedCtr = 0.;
    Double_t passLepCutInSemiLepChannelGenOtherWeightedCtr = 0.;
    Double_t passSemiLepChannelGenOtherWeightedCtr = 0.;
    Double_t passHadChannelGenOtherWeightedCtr = 0.;
    Double_t passVBFJetBVetoGenOtherWeightedCtr = 0.;
    Double_t passVBFJetsGenOtherWeightedCtr = 0.;
    Double_t passAsLepGenOtherWeightedCtr = 0.;
    Double_t passAsSemiLepGenOtherWeightedCtr = 0.;
    Double_t passAsHadGenOtherWeightedCtr = 0.;

    UInt_t passSemiLepLepCutGenOtherCtr = 0;
    Double_t passSemiLepLepCutGenOtherWeightedCtr = 0.;
    

    ////////////////////////////////NO HToBB COUNTERS////////////////////////////////

    ////////////////////////////////GEN LEP COUNTERS////////////////////////////////

    UInt_t startingGenLepNoHTobbCtr = 0;

    UInt_t passHiggsFJPreSTGenLepNoHTobbCtr = 0;
    UInt_t passHiggsFJPreSTLepGenLepNoHTobbCtr = 0;
    UInt_t passHiggsFJPreSTSemiLepGenLepNoHTobbCtr = 0;
    UInt_t passHiggsFJPreSTHadGenLepNoHTobbCtr = 0;

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
    UInt_t passVBFJetBVetoGenLepNoHTobbCtr = 0;
    UInt_t passVBFJetsGenLepNoHTobbCtr = 0;
    UInt_t passAsLepGenLepNoHTobbCtr = 0;
    UInt_t passAsSemiLepGenLepNoHTobbCtr = 0;
    UInt_t passAsHadGenLepNoHTobbCtr = 0;
    
    Double_t startingGenLepNoHTobbWeightedCtr = 0.;

    Double_t passHiggsFJPreSTGenLepNoHTobbWeightedCtr = 0.;
    Double_t passHiggsFJPreSTWeightedLepGenLepNoHTobbCtr = 0.;
    Double_t passHiggsFJPreSTWeightedSemiLepGenLepNoHTobbCtr = 0.;
    Double_t passHiggsFJPreSTWeightedHadGenLepNoHTobbCtr = 0.;

    Double_t passHiggsFJGenLepNoHTobbWeightedCtr = 0.;
    Double_t passHiggsFJWeightedLepGenLepNoHTobbCtr = 0.;
    Double_t passHiggsFJWeightedSemiLepGenLepNoHTobbCtr = 0.;
    Double_t passHiggsFJWeightedHadGenLepNoHTobbCtr = 0.;
    Double_t passChannelGenLepNoHTobbWeightedCtr = 0.;
    Double_t passLepOrSemiLepChannelGenLepNoHTobbWeightedCtr = 0.;
    Double_t passLepChannelGenLepNoHTobbWeightedCtr = 0.;
    Double_t tryingSemiLepChannelGenLepNoHTobbWeightedCtr = 0.;
    Double_t passFJInSemiLepChannelGenLepNoHTobbWeightedCtr = 0.;
    Double_t passEnoughLepsInSemiLepChannelGenLepNoHTobbWeightedCtr = 0.;
    Double_t passLepCutInSemiLepChannelGenLepNoHTobbWeightedCtr = 0.;
    Double_t passSemiLepChannelGenLepNoHTobbWeightedCtr = 0.;
    Double_t passHadChannelGenLepNoHTobbWeightedCtr = 0.;
    Double_t passVBFJetBVetoGenLepNoHTobbWeightedCtr = 0.;
    Double_t passVBFJetsGenLepNoHTobbWeightedCtr = 0.;
    Double_t passAsLepGenLepNoHTobbWeightedCtr = 0.;
    Double_t passAsSemiLepGenLepNoHTobbWeightedCtr = 0.;
    Double_t passAsHadGenLepNoHTobbWeightedCtr = 0.;

    UInt_t passSemiLepLepCutGenLepNoHTobbCtr = 0;
    Double_t passSemiLepLepCutGenLepNoHTobbWeightedCtr = 0.;

    ////////////////////////////////GEN SEMILEP COUNTERS////////////////////////////////

    UInt_t startingGenSemiLepNoHTobbCtr = 0;

    UInt_t passHiggsFJPreSTGenSemiLepNoHTobbCtr = 0;
    UInt_t passHiggsFJPreSTLepGenSemiLepNoHTobbCtr = 0;
    UInt_t passHiggsFJPreSTSemiLepGenSemiLepNoHTobbCtr = 0;
    UInt_t passHiggsFJPreSTHadGenSemiLepNoHTobbCtr = 0;

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
    UInt_t passVBFJetBVetoGenSemiLepNoHTobbCtr = 0;
    UInt_t passVBFJetsGenSemiLepNoHTobbCtr = 0;
    UInt_t passAsLepGenSemiLepNoHTobbCtr = 0;
    UInt_t passAsSemiLepGenSemiLepNoHTobbCtr = 0;
    UInt_t passAsHadGenSemiLepNoHTobbCtr = 0;
    
    Double_t startingGenSemiLepNoHTobbWeightedCtr = 0.;

    Double_t passHiggsFJPreSTGenSemiLepNoHTobbWeightedCtr = 0.;
    Double_t passHiggsFJPreSTWeightedLepGenSemiLepNoHTobbCtr = 0.;
    Double_t passHiggsFJPreSTWeightedSemiLepGenSemiLepNoHTobbCtr = 0.;
    Double_t passHiggsFJPreSTWeightedHadGenSemiLepNoHTobbCtr = 0.;

    Double_t passHiggsFJGenSemiLepNoHTobbWeightedCtr = 0.;
    Double_t passHiggsFJWeightedLepGenSemiLepNoHTobbCtr = 0.;
    Double_t passHiggsFJWeightedSemiLepGenSemiLepNoHTobbCtr = 0.;
    Double_t passHiggsFJWeightedHadGenSemiLepNoHTobbCtr = 0.;
    Double_t passChannelGenSemiLepNoHTobbWeightedCtr = 0.;
    Double_t passLepOrSemiLepChannelGenSemiLepNoHTobbWeightedCtr = 0.;
    Double_t passLepChannelGenSemiLepNoHTobbWeightedCtr = 0.;
    Double_t tryingSemiLepChannelGenSemiLepNoHTobbWeightedCtr = 0.;
    Double_t passFJInSemiLepChannelGenSemiLepNoHTobbWeightedCtr = 0.;
    Double_t passEnoughLepsInSemiLepChannelGenSemiLepNoHTobbWeightedCtr = 0.;
    Double_t passLepCutInSemiLepChannelGenSemiLepNoHTobbWeightedCtr = 0.;
    Double_t passSemiLepChannelGenSemiLepNoHTobbWeightedCtr = 0.;
    Double_t passHadChannelGenSemiLepNoHTobbWeightedCtr = 0.;
    Double_t passVBFJetBVetoGenSemiLepNoHTobbWeightedCtr = 0.;
    Double_t passVBFJetsGenSemiLepNoHTobbWeightedCtr = 0.;
    Double_t passAsLepGenSemiLepNoHTobbWeightedCtr = 0.;
    Double_t passAsSemiLepGenSemiLepNoHTobbWeightedCtr = 0.;
    Double_t passAsHadGenSemiLepNoHTobbWeightedCtr = 0.;

    UInt_t passSemiLepLepCutGenSemiLepNoHTobbCtr = 0;
    Double_t passSemiLepLepCutGenSemiLepNoHTobbWeightedCtr = 0.;


    ////////////////////////////////GEN HAD COUNTERS////////////////////////////////

    UInt_t startingGenHadNoHTobbCtr = 0;

    UInt_t passHiggsFJPreSTGenHadNoHTobbCtr = 0;
    UInt_t passHiggsFJPreSTLepGenHadNoHTobbCtr = 0;
    UInt_t passHiggsFJPreSTSemiLepGenHadNoHTobbCtr = 0;
    UInt_t passHiggsFJPreSTHadGenHadNoHTobbCtr = 0;

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
    UInt_t passVBFJetBVetoGenHadNoHTobbCtr = 0;
    UInt_t passVBFJetsGenHadNoHTobbCtr = 0;
    UInt_t passAsLepGenHadNoHTobbCtr = 0;
    UInt_t passAsSemiLepGenHadNoHTobbCtr = 0;
    UInt_t passAsHadGenHadNoHTobbCtr = 0;
    
    Double_t startingGenHadNoHTobbWeightedCtr = 0.;

    Double_t passHiggsFJPreSTGenHadNoHTobbWeightedCtr = 0.;
    Double_t passHiggsFJPreSTWeightedLepGenHadNoHTobbCtr = 0.;
    Double_t passHiggsFJPreSTWeightedSemiLepGenHadNoHTobbCtr = 0.;
    Double_t passHiggsFJPreSTWeightedHadGenHadNoHTobbCtr = 0.;

    Double_t passHiggsFJGenHadNoHTobbWeightedCtr = 0.;
    Double_t passHiggsFJWeightedLepGenHadNoHTobbCtr = 0.;
    Double_t passHiggsFJWeightedSemiLepGenHadNoHTobbCtr = 0.;
    Double_t passHiggsFJWeightedHadGenHadNoHTobbCtr = 0.;
    Double_t passChannelGenHadNoHTobbWeightedCtr = 0.;
    Double_t passLepOrSemiLepChannelGenHadNoHTobbWeightedCtr = 0.;
    Double_t passLepChannelGenHadNoHTobbWeightedCtr = 0.;
    Double_t tryingSemiLepChannelGenHadNoHTobbWeightedCtr = 0.;
    Double_t passFJInSemiLepChannelGenHadNoHTobbWeightedCtr = 0.;
    Double_t passEnoughLepsInSemiLepChannelGenHadNoHTobbWeightedCtr = 0.;
    Double_t passLepCutInSemiLepChannelGenHadNoHTobbWeightedCtr = 0.;
    Double_t passSemiLepChannelGenHadNoHTobbWeightedCtr = 0.;
    Double_t passHadChannelGenHadNoHTobbWeightedCtr = 0.;
    Double_t passVBFJetBVetoGenHadNoHTobbWeightedCtr = 0.;
    Double_t passVBFJetsGenHadNoHTobbWeightedCtr = 0.;
    Double_t passAsLepGenHadNoHTobbWeightedCtr = 0.;
    Double_t passAsSemiLepGenHadNoHTobbWeightedCtr = 0.;
    Double_t passAsHadGenHadNoHTobbWeightedCtr = 0.;

    UInt_t passSemiLepLepCutGenHadNoHTobbCtr = 0;
    Double_t passSemiLepLepCutGenHadNoHTobbWeightedCtr = 0.;

    ////////////////////////////////GEN OTHER COUNTERS////////////////////////////////

    UInt_t startingGenOtherNoHTobbCtr = 0;

    UInt_t passHiggsFJPreSTGenOtherNoHTobbCtr = 0;
    UInt_t passHiggsFJPreSTLepGenOtherNoHTobbCtr = 0;
    UInt_t passHiggsFJPreSTSemiLepGenOtherNoHTobbCtr = 0;
    UInt_t passHiggsFJPreSTHadGenOtherNoHTobbCtr = 0;

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
    UInt_t passVBFJetBVetoGenOtherNoHTobbCtr = 0;
    UInt_t passVBFJetsGenOtherNoHTobbCtr = 0;
    UInt_t passAsLepGenOtherNoHTobbCtr = 0;
    UInt_t passAsSemiLepGenOtherNoHTobbCtr = 0;
    UInt_t passAsHadGenOtherNoHTobbCtr = 0;
    
    Double_t startingGenOtherNoHTobbWeightedCtr = 0.;

    Double_t passHiggsFJPreSTGenOtherNoHTobbWeightedCtr = 0.;
    Double_t passHiggsFJPreSTWeightedLepGenOtherNoHTobbCtr = 0.;
    Double_t passHiggsFJPreSTWeightedSemiLepGenOtherNoHTobbCtr = 0.;
    Double_t passHiggsFJPreSTWeightedHadGenOtherNoHTobbCtr = 0.;

    Double_t passHiggsFJGenOtherNoHTobbWeightedCtr = 0.;
    Double_t passHiggsFJWeightedLepGenOtherNoHTobbCtr = 0.;
    Double_t passHiggsFJWeightedSemiLepGenOtherNoHTobbCtr = 0.;
    Double_t passHiggsFJWeightedHadGenOtherNoHTobbCtr = 0.;
    Double_t passChannelGenOtherNoHTobbWeightedCtr = 0.;
    Double_t passLepOrSemiLepChannelGenOtherNoHTobbWeightedCtr = 0.;
    Double_t passLepChannelGenOtherNoHTobbWeightedCtr = 0.;
    Double_t tryingSemiLepChannelGenOtherNoHTobbWeightedCtr = 0.;
    Double_t passFJInSemiLepChannelGenOtherNoHTobbWeightedCtr = 0.;
    Double_t passEnoughLepsInSemiLepChannelGenOtherNoHTobbWeightedCtr = 0.;
    Double_t passLepCutInSemiLepChannelGenOtherNoHTobbWeightedCtr = 0.;
    Double_t passSemiLepChannelGenOtherNoHTobbWeightedCtr = 0.;
    Double_t passHadChannelGenOtherNoHTobbWeightedCtr = 0.;
    Double_t passVBFJetBVetoGenOtherNoHTobbWeightedCtr = 0.;
    Double_t passVBFJetsGenOtherNoHTobbWeightedCtr = 0.;
    Double_t passAsLepGenOtherNoHTobbWeightedCtr = 0.;
    Double_t passAsSemiLepGenOtherNoHTobbWeightedCtr = 0.;
    Double_t passAsHadGenOtherNoHTobbWeightedCtr = 0.;

    UInt_t passSemiLepLepCutGenOtherNoHTobbCtr = 0;
    Double_t passSemiLepLepCutGenOtherNoHTobbWeightedCtr = 0.;





    ////////////////////////////////OTHER COUNTERS////////////////////////////////

    UInt_t passVBFJetBVeto = 0;
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



    Double_t genWeightLL;

    Float_t ZOneLep_massLL;
    Float_t ZTwoLep_massLL;
    Float_t H_ptLL;

    //ParticleNet
    Float_t FatJet_particleNet_WvsQCDLL;



    
    
    


    TTree *PassingLepEventsTree = new TTree("PassingLepEventsTree", "PassingLepEventsTree");
    //gen weights
    PassingLepEventsTree->Branch("genWeightLL",&genWeightLL,"genWeightLL/D");

    PassingLepEventsTree->Branch("H_ptLL",&H_ptLL,"H_ptLL/F");


    PassingLepEventsTree->Branch("ZOneLep_massLL",&ZOneLep_massLL,"ZOneLep_massLL/F");
    PassingLepEventsTree->Branch("ZTwoLep_massLL",&ZTwoLep_massLL,"ZTwoLep_massLL/F");
    PassingLepEventsTree->Branch("FatJet_particleNet_WvsQCDLL",&FatJet_particleNet_WvsQCDLL,"FatJet_particleNet_WvsQCDLL/F");



    Double_t genWeightSLL;

    Float_t ZOneLep_massSLL;
    Float_t H_ptSLL;

    //ParticleNet
    Float_t FatJet_particleNet_WvsQCDSLL;


    
    
    


    TTree *PassingSemiLepEventsTree = new TTree("PassingSemiLepEventsTree", "PassingSemiLepEventsTree");
    //gen weights
    PassingSemiLepEventsTree->Branch("genWeightSLL",&genWeightSLL,"genWeightSLL/D");

    PassingSemiLepEventsTree->Branch("H_ptSLL",&H_ptSLL,"H_ptSLL/F");


    PassingSemiLepEventsTree->Branch("ZOneLep_massSLL",&ZOneLep_massSLL,"ZOneLep_massSLL/F");
    PassingSemiLepEventsTree->Branch("FatJet_particleNet_WvsQCDSLL",&FatJet_particleNet_WvsQCDSLL,"FatJet_particleNet_WvsQCDSLL/F");





    

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

        //Comment these out if doing background
        /*
        //genChannelL
        TTreeReaderValue<UInt_t> genChannelL(myEventsReader, "genChannelL");
        //HTobbBool
        TTreeReaderValue<Bool_t> HTobbBoolL(myEventsReader, "HTobbBoolL");
        */

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

        //Getting the cross section
        //For background it's precalculated

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
                    
                    
                }

                if (passedAsSemiLepLepCutBool){
                    if (debug) std::cout << "Passed semi lep lep cut\n";
                    passSemiLepLepCutCtr += 1;
                    passSemiLepLepCutWeightedCtr += tmpGenWeights;
                    
                    
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
                    
                   FJIndAr.push_back(FJInd);
                   
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
            doHiggsFatJetCutST(dRCheckVecAr,ZPairPlusHInvMassCut,ZPairPlusHPtCut,passesSTCutBool);
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

            //B jet veto
            bool passBJetVeto = true;
            doBJetVeto(nJetLen,Jet_ptL,Jet_etaL,Jet_phiL,Jet_btagDeepFlavBL,hFatJet_phi_fromHTag,hFatJet_eta_fromHTag,dRCut,bTagCut,passBJetVeto,debug);
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
            doVBFJetCutPtSelection(nJetLen,Jet_ptL,Jet_jetIdL,Jet_etaL,Jet_phiL,Jet_massL,jetPTCut,jetEtaDifCut,jetInvMassCut,jetPairInvMass,jetLeadPt,jetLeadEta,jetLeadPhi,jetTrailingPt,jetTrailingEta,jetTrailingPhi,leadJet_1,leadJet_2,dRCheckVecAr,dRCut,debug);
            //std::cout << jetLeadPt << endl;
            if (jetLeadPt == 0) continue;
            debugOutputForVBFJetCut(evCount,leadJet_1,leadJet_2,Jet_phiL,Jet_etaL,debug);
            passVBFJets += 1;

            if (passesCutsBool){
                passVBFJetsCtr += 1;
                passVBFJetsWeightedCtr += tmpGenWeights;
                

                //std::cout << passedAsLepBool << " "<< passedAsSemiLepBool << " " << passedAsHadBool << "\n";
                if (passedAsLepBool) {

                    passAsLepCtr += 1;
                    passAsLepWeightedCtr += tmpGenWeights;

                    ROOT::Math::PtEtaPhiMVector tmpZLepOneVec = dRCheckVecAr[0];
                    ROOT::Math::PtEtaPhiMVector tmpZLepTwoVec = dRCheckVecAr[1];
                    ROOT::Math::PtEtaPhiMVector tmpZTwoLepOneVec = dRCheckVecAr[2];
                    ROOT::Math::PtEtaPhiMVector tmpZTwoLepTwoVec = dRCheckVecAr[3];
                    ROOT::Math::PtEtaPhiMVector tmpZOneLepVecPair = tmpZLepOneVec + tmpZLepTwoVec;
                    ROOT::Math::PtEtaPhiMVector tmpZTwoLepVecPair = tmpZTwoLepOneVec + tmpZTwoLepTwoVec;

                    genWeightLL = tmpGenWeights;

                    ZOneLep_massLL = tmpZOneLepVecPair.M();
                    ZTwoLep_massLL = tmpZTwoLepVecPair.M();
                    H_ptLL = dRCheckVecAr[4].Pt();

                    FatJet_particleNet_WvsQCDLL = 0;

                    PassingLepEventsTree->Fill();
                    
                    
                    
                }
                
                else if (passedAsSemiLepBool){


                    passAsSemiLepCtr += 1;
                    passAsSemiLepWeightedCtr += tmpGenWeights;
                    
                    nFJL = *nFatJetL;
                    nJL = *nJetL;
                    AfterCutGenSemiLepWeightL = *genWeightL;
                    AfterCutSemiLepInvMassTree->Fill();

                    ROOT::Math::PtEtaPhiMVector tmpZLepOneVec = dRCheckVecAr[0];
                    ROOT::Math::PtEtaPhiMVector tmpZLepTwoVec = dRCheckVecAr[1];
                    ROOT::Math::PtEtaPhiMVector tmpZLepVecPair = tmpZLepOneVec + tmpZLepTwoVec;

                    genWeightSLL = tmpGenWeights;

                    ZOneLep_massSLL = tmpZLepVecPair.M();
                    H_ptSLL = dRCheckVecAr[3].Pt();

                    FatJet_particleNet_WvsQCDSLL = 0;


                    PassingSemiLepEventsTree->Fill();
                    

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
    BeforeCutLepInvMassTree->Write("",TObject::kOverwrite);
    BeforeCutSemiLepInvMassTree->Write("",TObject::kOverwrite);
    AfterCutSemiLepInvMassTree->Write("",TObject::kOverwrite);
    PassingLepEventsTree->Write("",TObject::kOverwrite);
    PassingSemiLepEventsTree->Write("",TObject::kOverwrite);

    outFile->Close();

}