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


void new09272023BDTReweightingAnalysis(string datasetString){
    // Open the file. Note that the name of your file outside this class
    // will probably NOT be experiment.root.
    std::cout << "start Analysis\n";
    clock_t startt = clock();
    //Analyzer will run over all files put into fileAr

    std::vector<std::string> fileAr;


    std::string saveName;
    float crossSection;
    bool isBackground = false;

    if (datasetString == "testRun") testRun = true;
    if (datasetString == "SDC2V2MCZZHReweight") SDC2V2MCZZHReweight = true;
    if (datasetString == "SDC2V2MCZZH17Reweight") SDC2V2MCZZH17Reweight = true;
    if (datasetString == "SDC2V2MCZZH16Reweight") SDC2V2MCZZH16Reweight = true;
    if (datasetString == "SDC2V2MCZZH16APVReweight") SDC2V2MCZZH16APVReweight = true;
    if (datasetString == "SDC2V2MCZZHReweightTrimmed") SDC2V2MCZZHReweightTrimmed = true;
    if (datasetString == "SDC2V2MCZZH17ReweightTrimmed") SDC2V2MCZZH17ReweightTrimmed = true;
    if (datasetString == "SDC2V2MCZZH16ReweightTrimmed") SDC2V2MCZZH16ReweightTrimmed = true;
    if (datasetString == "SDC2V2MCZZH16APVReweightTrimmed") SDC2V2MCZZH16APVReweightTrimmed = true;

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
    //precalculate this
    double XS = 1;

    UInt_t datasetType = 0;
    UInt_t yearType = 0;

    
    if (SDC2V2MCZZHReweight){
        saveName = "SDC2V2MCZZHReweight";
        //totWeight = ;
        //XS = ;
        isBackground = false;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisSDC2V2MCZZHReweight_0.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2V2MCZZH17Reweight){
        saveName = "SDC2V2MCZZH17Reweight";
        yearType = 1;
        //totWeight = ;
        //XS = ;
        isBackground = false;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisSDC2V2MCZZH17Reweight_0.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2V2MCZZH16Reweight){
        saveName = "SDC2V2MCZZH16Reweight";
        yearType = 2;
        //totWeight = ;
        //XS = ;
        isBackground = false;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisSDC2V2MCZZH16Reweight_0.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2V2MCZZH16APVReweight){
        saveName = "SDC2V2MCZZH16APVReweight";
        yearType = 3;
        //totWeight = ;
        //XS = ;
        isBackground = false;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisSDC2V2MCZZH16APVReweight_0.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2V2MCZZHReweightTrimmed){
        saveName = "SDC2V2MCZZHReweightTrimmed";
        //totWeight = ;
        //XS = ;
        isBackground = false;
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisSDC2V2MCZZHReweight_0.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2V2MCZZH17ReweightTrimmed){
        saveName = "SDC2V2MCZZH17ReweightTrimmed";
        yearType = 1;
        //totWeight = ;
        //XS = ;
        isBackground = false;
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisSDC2V2MCZZH17Reweight_0.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2V2MCZZH16ReweightTrimmed){
        saveName = "SDC2V2MCZZH16ReweightTrimmed";
        yearType = 2;
        //totWeight = ;
        //XS = ;
        isBackground = false;
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisSDC2V2MCZZH16Reweight_0.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2V2MCZZH16APVReweightTrimmed){
        saveName = "SDC2V2MCZZH16APVReweightTrimmed";
        yearType = 3;
        //totWeight = ;
        //XS = ;
        isBackground = false;
        std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisSDC2V2MCZZH16APVReweight_0.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (testRun){
        saveName = "testRun";
        fileAr.push_back("./HLTFilteredForAnalysistestRun_0.root");
        
        
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
    
    std::string outFileStr = "new122022BDTAnalysis"+saveName+".root";
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


    

    std::vector<std::string> C2VNameAr {"-2.0","-1.75","-1.5","-1.25","-1.0","-0.75","-0.5","-0.25","0.0","0.1","0.2","0.3","0.4","0.5","0.6","0.7","0.8","0.9","1.0","1.1","1.2","1.3","1.4","1.5","1.6","1.7","1.8","1.9","2.25","2.5","2.75","3.0","3.25","3.5","3.75","4.0"};
    std::vector<std::string> htobbNameAr {"HTobb","NoHTobb"};
    std::vector<std::string> typeNameAr {"","GenLep","GenSemiLep","GenHad","GenOther"};
    std::vector<std::string> typeNameAltAr {"GenLep","GenSemiLep","GenHad","GenOther"};
    std::vector<Double_t> zeroC2VVec(37,0.0);
    std::vector<std::vector<Double_t>> zeroTypeVec(5,zeroC2VVec);

    std::vector<std::vector<std::vector<Double_t>>> startingWeightedCtrAr(2,zeroTypeVec);

    std::vector<std::vector<std::vector<Double_t>>> passHiggsFJPreSTWeightedCtrAr(2,zeroTypeVec);
    std::vector<std::vector<std::vector<Double_t>>> passHiggsFJPreSTWeightedLepCtr(2,zeroTypeVec);
    std::vector<std::vector<std::vector<Double_t>>> passHiggsFJPreSTWeightedSemiLepCtr(2,zeroTypeVec);
    std::vector<std::vector<std::vector<Double_t>>> passHiggsFJPreSTWeightedHadCtr(2,zeroTypeVec);

    std::vector<std::vector<std::vector<Double_t>>> passHiggsFJWeightedCtrAr(2,zeroTypeVec);
    std::vector<std::vector<std::vector<Double_t>>> passHiggsFJWeightedLepCtr(2,zeroTypeVec);
    std::vector<std::vector<std::vector<Double_t>>> passHiggsFJWeightedSemiLepCtr(2,zeroTypeVec);
    std::vector<std::vector<std::vector<Double_t>>> passHiggsFJWeightedHadCtr(2,zeroTypeVec);

    std::vector<std::vector<std::vector<Double_t>>> passChannelWeightedCtrAr(2,zeroTypeVec);
    std::vector<std::vector<std::vector<Double_t>>> passLepOrSemiLepChannelWeightedCtrAr(2,zeroTypeVec);

    std::vector<std::vector<std::vector<Double_t>>> passLepChannelWeightedCtrAr(2,zeroTypeVec);
    std::vector<std::vector<std::vector<Double_t>>> tryingSemiLepChannelWeightedCtrAr(2,zeroTypeVec);
    std::vector<std::vector<std::vector<Double_t>>> passFJInSemiLepChannelWeightedCtrAr(2,zeroTypeVec);
    std::vector<std::vector<std::vector<Double_t>>> passEnoughLepsInSemiLepChannelWeightedCtrAr(2,zeroTypeVec);

    std::vector<std::vector<std::vector<Double_t>>> passEnoughFJsInSemiLepChannelWeightedCtrAr(2,zeroTypeVec);
    //std::vector<std::vector<std::vector<Double_t>>> passLepCutInSemiLepChannelWeightedCtrAr(2,zeroTypeVec);
    std::vector<std::vector<std::vector<Double_t>>> passSemiLepLepCutWeightedCtrAr(2,zeroTypeVec);
    std::vector<std::vector<std::vector<Double_t>>> passSemiLepChannelWeightedCtrAr(2,zeroTypeVec);
    std::vector<std::vector<std::vector<Double_t>>> passHadChannelWeightedCtrAr(2,zeroTypeVec);

    std::vector<std::vector<std::vector<Double_t>>> passVBFJetBVetoWeightedCtr(2,zeroTypeVec);
    std::vector<std::vector<std::vector<Double_t>>> passVBFJetBVetoWeightedLepCtr(2,zeroTypeVec);
    std::vector<std::vector<std::vector<Double_t>>> passVBFJetBVetoWeightedSemiLepCtr(2,zeroTypeVec);
    std::vector<std::vector<std::vector<Double_t>>> passVBFJetBVetoWeightedHadCtr(2,zeroTypeVec);

    std::vector<std::vector<std::vector<Double_t>>> passVBFJetsWeightedCtr(2,zeroTypeVec);

    std::vector<std::vector<std::vector<Double_t>>> passAsLepWeightedCtr(2,zeroTypeVec);
    std::vector<std::vector<std::vector<Double_t>>> passAsSemiLepWeightedCtr(2,zeroTypeVec);
    std::vector<std::vector<std::vector<Double_t>>> passAsHadWeightedCtr(2,zeroTypeVec);
    std::vector<std::vector<std::vector<Double_t>>> passSemiLepLepCutWeightedCtr(2,zeroTypeVec);

    
    
    UInt_t passSemiLepLepCutCtr = 0;
    //Double_t passSemiLepLepCutWeightedCtr = 0.;
    
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
    UInt_t passEnoughFJsInSemiLepChannelGenLepCtr = 0;
    UInt_t passLepCutInSemiLepChannelGenLepCtr = 0;
    UInt_t passSemiLepChannelGenLepCtr = 0;
    UInt_t passHadChannelGenLepCtr = 0;
    UInt_t passVBFJetBVetoGenLepCtr = 0;
    UInt_t passVBFJetBVetoLepGenLepCtr = 0;
    UInt_t passVBFJetBVetoSemiLepGenLepCtr = 0;
    UInt_t passVBFJetBVetoHadGenLepCtr = 0;
    UInt_t passVBFJetsGenLepCtr = 0;
    UInt_t passAsLepGenLepCtr = 0;
    UInt_t passAsSemiLepGenLepCtr = 0;
    UInt_t passAsHadGenLepCtr = 0;
    UInt_t passSemiLepLepCutGenLepCtr = 0;
    //Double_t passSemiLepLepCutGenLepWeightedCtr = 0.;

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
    UInt_t passEnoughFJsInSemiLepChannelGenSemiLepCtr = 0;
    UInt_t passLepCutInSemiLepChannelGenSemiLepCtr = 0;
    UInt_t passSemiLepChannelGenSemiLepCtr = 0;
    UInt_t passHadChannelGenSemiLepCtr = 0;
    UInt_t passVBFJetBVetoGenSemiLepCtr = 0;
    UInt_t passVBFJetBVetoLepGenSemiLepCtr = 0;
    UInt_t passVBFJetBVetoSemiLepGenSemiLepCtr = 0;
    UInt_t passVBFJetBVetoHadGenSemiLepCtr = 0;
    UInt_t passVBFJetsGenSemiLepCtr = 0;
    UInt_t passAsLepGenSemiLepCtr = 0;
    UInt_t passAsSemiLepGenSemiLepCtr = 0;
    UInt_t passAsHadGenSemiLepCtr = 0;

    UInt_t passSemiLepLepCutGenSemiLepCtr = 0;
    //Double_t passSemiLepLepCutGenSemiLepWeightedCtr = 0.;


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
    UInt_t passEnoughFJsInSemiLepChannelGenHadCtr = 0;
    UInt_t passLepCutInSemiLepChannelGenHadCtr = 0;
    UInt_t passSemiLepChannelGenHadCtr = 0;
    UInt_t passHadChannelGenHadCtr = 0;
    UInt_t passVBFJetBVetoGenHadCtr = 0;
    UInt_t passVBFJetBVetoLepGenHadCtr = 0;
    UInt_t passVBFJetBVetoSemiLepGenHadCtr = 0;
    UInt_t passVBFJetBVetoHadGenHadCtr = 0;
    UInt_t passVBFJetsGenHadCtr = 0;
    UInt_t passAsLepGenHadCtr = 0;
    UInt_t passAsSemiLepGenHadCtr = 0;
    UInt_t passAsHadGenHadCtr = 0;
    UInt_t passSemiLepLepCutGenHadCtr = 0;
    //Double_t passSemiLepLepCutGenHadWeightedCtr = 0.;

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
    UInt_t passEnoughFJsInSemiLepChannelGenOtherCtr = 0;
    UInt_t passLepCutInSemiLepChannelGenOtherCtr = 0;
    UInt_t passSemiLepChannelGenOtherCtr = 0;
    UInt_t passHadChannelGenOtherCtr = 0;
    UInt_t passVBFJetBVetoGenOtherCtr = 0;
    UInt_t passVBFJetBVetoLepGenOtherCtr = 0;
    UInt_t passVBFJetBVetoSemiLepGenOtherCtr = 0;
    UInt_t passVBFJetBVetoHadGenOtherCtr = 0;
    UInt_t passVBFJetsGenOtherCtr = 0;
    UInt_t passAsLepGenOtherCtr = 0;
    UInt_t passAsSemiLepGenOtherCtr = 0;
    UInt_t passAsHadGenOtherCtr = 0;

    UInt_t passSemiLepLepCutGenOtherCtr = 0;
    //Double_t passSemiLepLepCutGenOtherWeightedCtr = 0.;
    

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
    UInt_t passEnoughFJsInSemiLepChannelGenLepNoHTobbCtr = 0;
    UInt_t passLepCutInSemiLepChannelGenLepNoHTobbCtr = 0;
    UInt_t passSemiLepChannelGenLepNoHTobbCtr = 0;
    UInt_t passHadChannelGenLepNoHTobbCtr = 0;
    UInt_t passVBFJetBVetoGenLepNoHTobbCtr = 0;
    UInt_t passVBFJetBVetoLepGenLepNoHTobbCtr = 0;
    UInt_t passVBFJetBVetoSemiLepGenLepNoHTobbCtr = 0;
    UInt_t passVBFJetBVetoHadGenLepNoHTobbCtr = 0;
    UInt_t passVBFJetsGenLepNoHTobbCtr = 0;
    UInt_t passAsLepGenLepNoHTobbCtr = 0;
    UInt_t passAsSemiLepGenLepNoHTobbCtr = 0;
    UInt_t passAsHadGenLepNoHTobbCtr = 0;

    UInt_t passSemiLepLepCutGenLepNoHTobbCtr = 0;
    //Double_t passSemiLepLepCutGenLepNoHTobbWeightedCtr = 0.;

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
    UInt_t passEnoughFJsInSemiLepChannelGenSemiLepNoHTobbCtr = 0;
    UInt_t passLepCutInSemiLepChannelGenSemiLepNoHTobbCtr = 0;
    UInt_t passSemiLepChannelGenSemiLepNoHTobbCtr = 0;
    UInt_t passHadChannelGenSemiLepNoHTobbCtr = 0;
    UInt_t passVBFJetBVetoGenSemiLepNoHTobbCtr = 0;
    UInt_t passVBFJetBVetoLepGenSemiLepNoHTobbCtr = 0;
    UInt_t passVBFJetBVetoSemiLepGenSemiLepNoHTobbCtr = 0;
    UInt_t passVBFJetBVetoHadGenSemiLepNoHTobbCtr = 0;
    UInt_t passVBFJetsGenSemiLepNoHTobbCtr = 0;
    UInt_t passAsLepGenSemiLepNoHTobbCtr = 0;
    UInt_t passAsSemiLepGenSemiLepNoHTobbCtr = 0;
    UInt_t passAsHadGenSemiLepNoHTobbCtr = 0;
    UInt_t passSemiLepLepCutGenSemiLepNoHTobbCtr = 0;
    //Double_t passSemiLepLepCutGenSemiLepNoHTobbWeightedCtr = 0.;


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
    UInt_t passEnoughFJsInSemiLepChannelGenHadNoHTobbCtr = 0;
    UInt_t passLepCutInSemiLepChannelGenHadNoHTobbCtr = 0;
    UInt_t passSemiLepChannelGenHadNoHTobbCtr = 0;
    UInt_t passHadChannelGenHadNoHTobbCtr = 0;
    UInt_t passVBFJetBVetoGenHadNoHTobbCtr = 0;
    UInt_t passVBFJetBVetoLepGenHadNoHTobbCtr = 0;
    UInt_t passVBFJetBVetoSemiLepGenHadNoHTobbCtr = 0;
    UInt_t passVBFJetBVetoHadGenHadNoHTobbCtr = 0;
    UInt_t passVBFJetsGenHadNoHTobbCtr = 0;
    UInt_t passAsLepGenHadNoHTobbCtr = 0;
    UInt_t passAsSemiLepGenHadNoHTobbCtr = 0;
    UInt_t passAsHadGenHadNoHTobbCtr = 0;
    UInt_t passSemiLepLepCutGenHadNoHTobbCtr = 0;
    //Double_t passSemiLepLepCutGenHadNoHTobbWeightedCtr = 0.;

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
     UInt_t passEnoughFJsInSemiLepChannelGenOtherNoHTobbCtr = 0;
    UInt_t passLepCutInSemiLepChannelGenOtherNoHTobbCtr = 0;
    UInt_t passSemiLepChannelGenOtherNoHTobbCtr = 0;
    UInt_t passHadChannelGenOtherNoHTobbCtr = 0;
    UInt_t passVBFJetBVetoGenOtherNoHTobbCtr = 0;
    UInt_t passVBFJetBVetoLepGenOtherNoHTobbCtr = 0;
    UInt_t passVBFJetBVetoSemiLepGenOtherNoHTobbCtr = 0;
    UInt_t passVBFJetBVetoHadGenOtherNoHTobbCtr = 0;
    UInt_t passVBFJetsGenOtherNoHTobbCtr = 0;
    UInt_t passAsLepGenOtherNoHTobbCtr = 0;
    UInt_t passAsSemiLepGenOtherNoHTobbCtr = 0;
    UInt_t passAsHadGenOtherNoHTobbCtr = 0;
    
    UInt_t passSemiLepLepCutGenOtherNoHTobbCtr = 0;
    //Double_t passSemiLepLepCutGenOtherNoHTobbWeightedCtr = 0.;

    




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

    //EventReweighting
    UInt_t nLHEReweightingWeight_L_L;
    std::vector<Float_t> LHEReweightingWeight_L_L;

    Double_t passingEvGenWeight_L_L;

    //Double_t passingEvFullWeight_L_L;

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
    Float_t selectedZOneLeadLepton_phi_L_L;
    Float_t selectedZOneTrailingLepton_phi_L_L;
    Float_t selectedZOneLeadLepton_SIP3D_L_L;
    Float_t selectedZOneTrailingLepton_SIP3D_L_L;
    Float_t selectedLeptons_MaxRelIso_L_L;
    Float_t selectedZOneLeptons_InvMass_L_L;
    Bool_t selectedZOneLeptons_Type_L_L;

    Float_t selectedZTwoLeadLepton_pt_L_L;
    Float_t selectedZTwoTrailingLepton_pt_L_L;
    Float_t selectedZTwoLeadLepton_eta_L_L;
    Float_t selectedZTwoTrailingLepton_eta_L_L;
    Float_t selectedZTwoLeadLepton_phi_L_L;
    Float_t selectedZTwoTrailingLepton_phi_L_L;
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

    passingEvLepTree->Branch("nLHEReweightingWeight_L_L",&nLHEReweightingWeight_L_L,"nLHEReweightingWeight_L_L/i");
    passingEvLepTree->Branch("LHEReweightingWeight_L_L",&LHEReweightingWeight_L_L);
    
    passingEvLepTree->Branch("passingEvGenWeight_L_L",&passingEvGenWeight_L_L,"passingEvGenWeight_L_L/D");

    //passingEvLepTree->Branch("passingEvFullWeight_L_L",&passingEvFullWeight_L_L,"passingEvFullWeight_L_L/D");

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
    passingEvLepTree->Branch("selectedZOneLeadLepton_phi_L_L",&selectedZOneLeadLepton_phi_L_L,"selectedZOneLeadLepton_phi_L_L/F");
    passingEvLepTree->Branch("selectedZOneTrailingLepton_phi_L_L",&selectedZOneTrailingLepton_phi_L_L,"selectedZOneTrailingLepton_phi_L_L/F");
    passingEvLepTree->Branch("selectedZOneLeadLepton_SIP3D_L_L",&selectedZOneLeadLepton_SIP3D_L_L,"selectedZOneLeadLepton_SIP3D_L_L/F");
    passingEvLepTree->Branch("selectedZOneTrailingLepton_SIP3D_L_L",&selectedZOneTrailingLepton_SIP3D_L_L,"selectedZOneTrailingLepton_SIP3D_L_L/F");
    
    passingEvLepTree->Branch("selectedZOneLeptons_InvMass_L_L",&selectedZOneLeptons_InvMass_L_L,"selectedZOneLeptons_InvMass_L_L/F");
    passingEvLepTree->Branch("selectedZOneLeptons_Type_L_L",&selectedZOneLeptons_Type_L_L,"selectedZOneLeptons_Type_L_L/O");

    passingEvLepTree->Branch("selectedZTwoLeadLepton_pt_L_L",&selectedZTwoLeadLepton_pt_L_L,"selectedZTwoLeadLepton_pt_L_L/F");
    passingEvLepTree->Branch("selectedZTwoTrailingLepton_pt_L_L",&selectedZTwoTrailingLepton_pt_L_L,"selectedZTwoTrailingLepton_pt_L_L/F");
    passingEvLepTree->Branch("selectedZTwoLeadLepton_eta_L_L",&selectedZTwoLeadLepton_eta_L_L,"selectedZTwoLeadLepton_eta_L_L/F");
    passingEvLepTree->Branch("selectedZTwoTrailingLepton_eta_L_L",&selectedZTwoTrailingLepton_eta_L_L,"selectedZTwoTrailingLepton_eta_L_L/F");
    passingEvLepTree->Branch("selectedZTwoLeadLepton_phi_L_L",&selectedZTwoLeadLepton_phi_L_L,"selectedZTwoLeadLepton_phi_L_L/F");
    passingEvLepTree->Branch("selectedZTwoTrailingLepton_phi_L_L",&selectedZTwoTrailingLepton_phi_L_L,"selectedZTwoTrailingLepton_phi_L_L/F");
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
    

    

    TTree *passingEvSemiLepTree = new TTree("passingEvSemiLepTree", "passingEvSemiLepTree");

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


    //passingEvSemiLepTree->Branch("ZFJInd_SL_L",&ZFJInd_SL_L,"ZFJInd_SL_L/I");
    //passingEvSemiLepTree->Branch("HFJInd_SL_L",&HFJInd_SL_L,"HFJInd_SL_L/I");
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

        //genChannelL
        TTreeReaderValue<UInt_t> genChannelL(myEventsReader, "genChannelL");
        //HTobbBool
        TTreeReaderValue<Bool_t> HTobbBoolL(myEventsReader, "HTobbBoolL");


        TTreeReaderValue<Int_t> ZFJIndL(myEventsReader,"ZFJIndL");
        TTreeReaderValue<Int_t> HFJIndL(myEventsReader,"HFJIndL");
        TTreeReaderValue<Bool_t> goodGenZFJMatchL(myEventsReader,"goodGenZFJMatchL");
        TTreeReaderValue<Bool_t> goodGenHFJMatchL(myEventsReader,"goodGenHFJMatchL");
        TTreeReaderValue<Bool_t> goodZFJMatchToGenL(myEventsReader,"goodZFJMatchToGenL");
        TTreeReaderValue<Bool_t> goodHFJMatchToGenL(myEventsReader,"goodHFJMatchToGenL");
        TTreeReaderValue<Bool_t> eventGenSemileptonicL(myEventsReader,"eventGenSemileptonicL");
        TTreeReaderValue<Bool_t> eventGenHToBBL(myEventsReader,"eventGenHToBBL");

        TTreeReaderValue<Int_t> ZFJGenHadronFlavourL(myEventsReader,"ZFJGenHadronFlavourL");
        TTreeReaderValue<Int_t> HFJGenHadronFlavourL(myEventsReader,"HFJGenHadronFlavourL");
        TTreeReaderArray<Int_t> FatJet_hadronFlavourL(myEventsReader,"FatJet_hadronFlavourL");






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

        //BDT Vars
        float selectedLeptons_MaxRelIso;
        float selectedLeptons_InvMass;

        float selectedZOneLeptons_InvMass;
        float selectedZTwoLeptons_InvMass;

        float ZPairPlusHInvMass;
        float ZPairPlusHPt;

        //Getting the cross section
        //For background it's precalculated

    
        while (myXSReader.Next()){
            crossSectionAvg += *crossSectionVar;
            crossSectionCnt += 1;
            //dataXS = *crossSectionVar;
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
                std::cout << evCount+1 << " in ev loop\n";
            }
            //Increment event count
            evRunOver += 1;
            evCount += 1;



            
            elecCandIndAr.clear();
            muonCandIndAr.clear();

            eZ2VecPairAr.clear();
            mZ2VecPairAr.clear();

            std::vector<Bool_t> falseTypeMask(5,false);
            std::vector<std::vector<Bool_t>> falseHtobbMask(2,falseTypeMask);

            Double_t tmpGenWeights = *genWeightL;
            startingCtr += 1;
            //startingWeightedCtr += tmpGenWeights;
            
            

        
            if (*HTobbBoolL){
                falseHtobbMask[0][0] = true;
                if (*genChannelL == 0) {
                    startingGenLepCtr += 1;
                    falseHtobbMask[0][1] = true;
                    //startingGenLepWeightedCtr += tmpGenWeights;
                    
                }
                if (*genChannelL == 1) {
                    startingGenSemiLepCtr += 1;
                    falseHtobbMask[0][2] = true;
                    //startingGenSemiLepWeightedCtr += tmpGenWeights;
                }
                if (*genChannelL == 2) {
                    startingGenHadCtr += 1;
                    falseHtobbMask[0][3] = true;
                    //startingGenHadWeightedCtr += tmpGenWeights;
                }
                if (*genChannelL == 3) {
                    startingGenOtherCtr += 1;
                    falseHtobbMask[0][4] = true;
                    //startingGenOtherWeightedCtr += tmpGenWeights;
                }
            }
            else{
                falseHtobbMask[1][0] = true;
                if (*genChannelL == 0) {
                    startingGenLepNoHTobbCtr += 1;
                    falseHtobbMask[1][1] = true;
                    //startingGenLepNoHTobbWeightedCtr += tmpGenWeights;
                }
                if (*genChannelL == 1) {
                    startingGenSemiLepNoHTobbCtr += 1;
                    falseHtobbMask[1][2] = true;
                    //startingGenSemiLepNoHTobbWeightedCtr += tmpGenWeights;
                }
                if (*genChannelL == 2) {
                    startingGenHadNoHTobbCtr += 1;
                    falseHtobbMask[1][3] = true;
                    //startingGenHadNoHTobbWeightedCtr += tmpGenWeights;
                }
                if (*genChannelL == 3) {
                    startingGenOtherNoHTobbCtr += 1;
                    falseHtobbMask[1][4] = true;
                    //startingGenOtherNoHTobbWeightedCtr += tmpGenWeights;
                }
            }

            for (unsigned int maskHtobbInt = 0; maskHtobbInt < falseHtobbMask.size(); maskHtobbInt++){
                for (unsigned int maskTypeInt = 0; maskTypeInt < falseHtobbMask[maskHtobbInt].size(); maskTypeInt++){
                    if (falseHtobbMask[maskHtobbInt][maskTypeInt]){
                        startingWeightedCtrAr[maskHtobbInt][maskTypeInt][0] += *genWeightL;
                        for (unsigned int C2VCtr = 1; C2VCtr < startingWeightedCtrAr[maskHtobbInt][maskTypeInt].size(); C2VCtr++){
                            startingWeightedCtrAr[maskHtobbInt][maskTypeInt][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                        }
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
                //passChannelWeightedCtr += tmpGenWeights;
                if (*HTobbBoolL){
                    if (*genChannelL == 0) {
                        passChannelGenLepCtr += 1;
                        //passChannelGenLepWeightedCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 1) {
                        passChannelGenSemiLepCtr += 1;
                        //passChannelGenSemiLepWeightedCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 2) {
                        passChannelGenHadCtr += 1;
                        //passChannelGenHadWeightedCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 3) {
                        passChannelGenOtherCtr += 1;
                        //passChannelGenOtherWeightedCtr += tmpGenWeights;
                    }
                }
                else{
                    if (*genChannelL == 0) {
                        passChannelGenLepNoHTobbCtr += 1;
                        //passChannelGenLepNoHTobbWeightedCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 1) {
                        passChannelGenSemiLepNoHTobbCtr += 1;
                        //passChannelGenSemiLepNoHTobbWeightedCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 2) {
                        passChannelGenHadNoHTobbCtr += 1;
                        //passChannelGenHadNoHTobbWeightedCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 3) {
                        passChannelGenOtherNoHTobbCtr += 1;
                        //passChannelGenOtherNoHTobbWeightedCtr += tmpGenWeights;
                    }
                }

                for (unsigned int maskHtobbInt = 0; maskHtobbInt < falseHtobbMask.size(); maskHtobbInt++){
                    for (unsigned int maskTypeInt = 0; maskTypeInt < falseHtobbMask[maskHtobbInt].size(); maskTypeInt++){
                        if (falseHtobbMask[maskHtobbInt][maskTypeInt]){
                            passChannelWeightedCtrAr[maskHtobbInt][maskTypeInt][0] += *genWeightL;
                            for (unsigned int C2VCtr = 1; C2VCtr < passChannelWeightedCtrAr[maskHtobbInt][maskTypeInt].size(); C2VCtr++){
                                passChannelWeightedCtrAr[maskHtobbInt][maskTypeInt][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                            }
                        }
                    }
                }
                
                passLepChannelCtr += 1;
                //passLepChannelWeightedCtr += tmpGenWeights;
                if (*HTobbBoolL){
                    if (*genChannelL == 0) {
                        passLepChannelGenLepCtr += 1;
                        //passLepChannelGenLepWeightedCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 1) {
                        passLepChannelGenSemiLepCtr += 1;
                        //passLepChannelGenSemiLepWeightedCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 2) {
                        passLepChannelGenHadCtr += 1;
                        //passLepChannelGenHadWeightedCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 3) {
                        passLepChannelGenOtherCtr += 1;
                        //passLepChannelGenOtherWeightedCtr += tmpGenWeights;
                    }
                }
                else {
                    if (*genChannelL == 0) {
                        passLepChannelGenLepNoHTobbCtr += 1;
                        //passLepChannelGenLepNoHTobbWeightedCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 1) {
                        passLepChannelGenSemiLepNoHTobbCtr += 1;
                        //passLepChannelGenSemiLepNoHTobbWeightedCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 2) {
                        passLepChannelGenHadNoHTobbCtr += 1;
                        //passLepChannelGenHadNoHTobbWeightedCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 3) {
                        passLepChannelGenOtherNoHTobbCtr += 1;
                        //passLepChannelGenOtherNoHTobbWeightedCtr += tmpGenWeights;
                    }

                }

                for (unsigned int maskHtobbInt = 0; maskHtobbInt < falseHtobbMask.size(); maskHtobbInt++){
                    for (unsigned int maskTypeInt = 0; maskTypeInt < falseHtobbMask[maskHtobbInt].size(); maskTypeInt++){
                        if (falseHtobbMask[maskHtobbInt][maskTypeInt]){
                            passLepChannelWeightedCtrAr[maskHtobbInt][maskTypeInt][0] += *genWeightL;
                            for (unsigned int C2VCtr = 1; C2VCtr < passLepChannelWeightedCtrAr[maskHtobbInt][maskTypeInt].size(); C2VCtr++){
                                passLepChannelWeightedCtrAr[maskHtobbInt][maskTypeInt][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                            }
                        }
                    }
                }
                
                passLepOrSemiLepChannelCtr += 1;
                //passLepOrSemiLepChannelWeightedCtr += tmpGenWeights;
                if (*HTobbBoolL){
                    if (*genChannelL == 0) {
                        passLepOrSemiLepChannelGenLepCtr += 1;
                        //passLepOrSemiLepChannelGenLepWeightedCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 1) {
                        passLepOrSemiLepChannelGenSemiLepCtr += 1;
                        //passLepOrSemiLepChannelGenSemiLepWeightedCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 2) {
                        passLepOrSemiLepChannelGenHadCtr += 1;
                        //passLepOrSemiLepChannelGenHadWeightedCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 3) {
                        passLepOrSemiLepChannelGenOtherCtr += 1;
                        //passLepOrSemiLepChannelGenOtherWeightedCtr += tmpGenWeights;
                    }
                }
                else {
                    if (*genChannelL == 0) {
                        passLepOrSemiLepChannelGenLepNoHTobbCtr += 1;
                        //passLepOrSemiLepChannelGenLepNoHTobbWeightedCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 1) {
                        passLepOrSemiLepChannelGenSemiLepNoHTobbCtr += 1;
                        //passLepOrSemiLepChannelGenSemiLepNoHTobbWeightedCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 2) {
                        passLepOrSemiLepChannelGenHadNoHTobbCtr += 1;
                        //passLepOrSemiLepChannelGenHadNoHTobbWeightedCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 3) {
                        passLepOrSemiLepChannelGenOtherNoHTobbCtr += 1;
                        //passLepOrSemiLepChannelGenOtherNoHTobbWeightedCtr += tmpGenWeights;
                    }
                }

                for (unsigned int maskHtobbInt = 0; maskHtobbInt < falseHtobbMask.size(); maskHtobbInt++){
                    for (unsigned int maskTypeInt = 0; maskTypeInt < falseHtobbMask[maskHtobbInt].size(); maskTypeInt++){
                        if (falseHtobbMask[maskHtobbInt][maskTypeInt]){
                            passLepOrSemiLepChannelWeightedCtrAr[maskHtobbInt][maskTypeInt][0] += *genWeightL;
                            for (unsigned int C2VCtr = 1; C2VCtr < passLepOrSemiLepChannelWeightedCtrAr[maskHtobbInt][maskTypeInt].size(); C2VCtr++){
                                passLepOrSemiLepChannelWeightedCtrAr[maskHtobbInt][maskTypeInt][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                            }
                        }
                    }
                }
                
            }
            if ((!passesCutsBool)){
                dRCheckVecAr.clear();
                std::vector<Float_t> SemiLepInvMass;
                
                if (debug) std::cout << "trying SemiLeptonic\n";
                tryingSemiLepChannelCtr += 1;
                //tryingSemiLepChannelWeightedCtr += tmpGenWeights;
                if (*HTobbBoolL){
                    if (*genChannelL == 0) {
                        tryingSemiLepChannelGenLepCtr += 1;
                        //tryingSemiLepChannelGenLepWeightedCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 1) {
                        tryingSemiLepChannelGenSemiLepCtr += 1;
                        //tryingSemiLepChannelGenSemiLepWeightedCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 2) {
                        tryingSemiLepChannelGenHadCtr += 1;
                        //tryingSemiLepChannelGenHadWeightedCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 3) {
                        tryingSemiLepChannelGenOtherCtr += 1;
                        //tryingSemiLepChannelGenOtherWeightedCtr += tmpGenWeights;
                    }
                }
                else {
                    if (*genChannelL == 0) {
                        tryingSemiLepChannelGenLepNoHTobbCtr += 1;
                        //tryingSemiLepChannelGenLepNoHTobbWeightedCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 1) {
                        tryingSemiLepChannelGenSemiLepNoHTobbCtr += 1;
                        //tryingSemiLepChannelGenSemiLepNoHTobbWeightedCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 2) {
                        tryingSemiLepChannelGenHadNoHTobbCtr += 1;
                        //tryingSemiLepChannelGenHadNoHTobbWeightedCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 3) {
                        tryingSemiLepChannelGenOtherNoHTobbCtr += 1;
                        //tryingSemiLepChannelGenOtherNoHTobbWeightedCtr += tmpGenWeights;
                    }
                }

                for (unsigned int maskHtobbInt = 0; maskHtobbInt < falseHtobbMask.size(); maskHtobbInt++){
                    for (unsigned int maskTypeInt = 0; maskTypeInt < falseHtobbMask[maskHtobbInt].size(); maskTypeInt++){
                        if (falseHtobbMask[maskHtobbInt][maskTypeInt]){
                            tryingSemiLepChannelWeightedCtrAr[maskHtobbInt][maskTypeInt][0] += *genWeightL;
                            for (unsigned int C2VCtr = 1; C2VCtr < tryingSemiLepChannelWeightedCtrAr[maskHtobbInt][maskTypeInt].size(); C2VCtr++){
                                tryingSemiLepChannelWeightedCtrAr[maskHtobbInt][maskTypeInt][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                            }
                        }
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
                    //passEnoughFJsInSemiLepChannelWeightedCtr += tmpGenWeights;
                    if (*HTobbBoolL){
                        if (*genChannelL == 0) {
                            passEnoughFJsInSemiLepChannelGenLepCtr += 1;
                            //passEnoughFJsInSemiLepChannelGenLepWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 1) {
                            passEnoughFJsInSemiLepChannelGenSemiLepCtr += 1;
                            //passEnoughFJsInSemiLepChannelGenSemiLepWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 2) {
                            passEnoughFJsInSemiLepChannelGenHadCtr += 1;
                            //passEnoughFJsInSemiLepChannelGenHadWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 3) {
                            passEnoughFJsInSemiLepChannelGenOtherCtr += 1;
                            //passEnoughFJsInSemiLepChannelGenOtherWeightedCtr += tmpGenWeights;
                        }
                    }
                    else {
                        if (*genChannelL == 0) {
                            passEnoughFJsInSemiLepChannelGenLepNoHTobbCtr += 1;
                            //passEnoughFJsInSemiLepChannelGenLepNoHTobbWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 1) {
                            passEnoughFJsInSemiLepChannelGenSemiLepNoHTobbCtr += 1;
                            //passEnoughFJsInSemiLepChannelGenSemiLepNoHTobbWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 2) {
                            passEnoughFJsInSemiLepChannelGenHadNoHTobbCtr += 1;
                            //passEnoughFJsInSemiLepChannelGenHadNoHTobbWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 3) {
                            passEnoughFJsInSemiLepChannelGenOtherNoHTobbCtr += 1;
                            //passEnoughFJsInSemiLepChannelGenOtherNoHTobbWeightedCtr += tmpGenWeights;
                        }
                    }

                    for (unsigned int maskHtobbInt = 0; maskHtobbInt < falseHtobbMask.size(); maskHtobbInt++){
                        for (unsigned int maskTypeInt = 0; maskTypeInt < falseHtobbMask[maskHtobbInt].size(); maskTypeInt++){
                            if (falseHtobbMask[maskHtobbInt][maskTypeInt]){
                                passEnoughFJsInSemiLepChannelWeightedCtrAr[maskHtobbInt][maskTypeInt][0] += *genWeightL;
                                for (unsigned int C2VCtr = 1; C2VCtr < passEnoughFJsInSemiLepChannelWeightedCtrAr[maskHtobbInt][maskTypeInt].size(); C2VCtr++){
                                    passEnoughFJsInSemiLepChannelWeightedCtrAr[maskHtobbInt][maskTypeInt][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                                }
                            }
                        }
                    }
                
                    
                

                    
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
                        //passEnoughLepsInSemiLepChannelWeightedCtr += tmpGenWeights;
                        if (*HTobbBoolL){
                            if (*genChannelL == 0) {
                                passEnoughLepsInSemiLepChannelGenLepCtr += 1;
                                //passEnoughLepsInSemiLepChannelGenLepWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 1) {
                                passEnoughLepsInSemiLepChannelGenSemiLepCtr += 1;
                                //passEnoughLepsInSemiLepChannelGenSemiLepWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 2) {
                                passEnoughLepsInSemiLepChannelGenHadCtr += 1;
                                //passEnoughLepsInSemiLepChannelGenHadWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 3) {
                                passEnoughLepsInSemiLepChannelGenOtherCtr += 1;
                                //passEnoughLepsInSemiLepChannelGenOtherWeightedCtr += tmpGenWeights;
                            }
                        }
                        else {
                            if (*genChannelL == 0) {
                                passEnoughLepsInSemiLepChannelGenLepNoHTobbCtr += 1;
                                //passEnoughLepsInSemiLepChannelGenLepNoHTobbWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 1) {
                                passEnoughLepsInSemiLepChannelGenSemiLepNoHTobbCtr += 1;
                                //passEnoughLepsInSemiLepChannelGenSemiLepNoHTobbWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 2) {
                                passEnoughLepsInSemiLepChannelGenHadNoHTobbCtr += 1;
                                //passEnoughLepsInSemiLepChannelGenHadNoHTobbWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 3) {
                                passEnoughLepsInSemiLepChannelGenOtherNoHTobbCtr += 1;
                                //passEnoughLepsInSemiLepChannelGenOtherNoHTobbWeightedCtr += tmpGenWeights;
                            }
                        }

                        for (unsigned int maskHtobbInt = 0; maskHtobbInt < falseHtobbMask.size(); maskHtobbInt++){
                            for (unsigned int maskTypeInt = 0; maskTypeInt < falseHtobbMask[maskHtobbInt].size(); maskTypeInt++){
                                if (falseHtobbMask[maskHtobbInt][maskTypeInt]){
                                    passEnoughLepsInSemiLepChannelWeightedCtrAr[maskHtobbInt][maskTypeInt][0] += *genWeightL;
                                    for (unsigned int C2VCtr = 1; C2VCtr < passEnoughLepsInSemiLepChannelWeightedCtrAr[maskHtobbInt][maskTypeInt].size(); C2VCtr++){
                                        passEnoughLepsInSemiLepChannelWeightedCtrAr[maskHtobbInt][maskTypeInt][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                                    }
                                }
                            }
                        }
                    
                        
                    }

                    if (passedAsSemiLepLepCutBool){
                        if (debug) std::cout << "Passed semi lep lep cut\n";
                        passSemiLepLepCutCtr += 1;
                        //passSemiLepLepCutWeightedCtr += tmpGenWeights;
                        if (*HTobbBoolL){
                            if (*genChannelL == 0) {
                                passSemiLepLepCutGenLepCtr += 1;
                                //passSemiLepLepCutGenLepWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 1) {
                                passSemiLepLepCutGenSemiLepCtr += 1;
                                //passSemiLepLepCutGenSemiLepWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 2) {
                                passSemiLepLepCutGenHadCtr += 1;
                                //passSemiLepLepCutGenHadWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 3) {
                                passSemiLepLepCutGenOtherCtr += 1;
                                //passSemiLepLepCutGenOtherWeightedCtr += tmpGenWeights;
                            }
                        }
                        else {
                            if (*genChannelL == 0) {
                                passSemiLepLepCutGenLepNoHTobbCtr += 1;
                                //passSemiLepLepCutGenLepNoHTobbWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 1) {
                                passSemiLepLepCutGenSemiLepNoHTobbCtr += 1;
                                //passSemiLepLepCutGenSemiLepNoHTobbWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 2) {
                                passSemiLepLepCutGenHadNoHTobbCtr += 1;
                                //passSemiLepLepCutGenHadNoHTobbWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 3) {
                                passSemiLepLepCutGenOtherNoHTobbCtr += 1;
                                //passSemiLepLepCutGenOtherNoHTobbWeightedCtr += tmpGenWeights;
                            }
                        }

                        for (unsigned int maskHtobbInt = 0; maskHtobbInt < falseHtobbMask.size(); maskHtobbInt++){
                            for (unsigned int maskTypeInt = 0; maskTypeInt < falseHtobbMask[maskHtobbInt].size(); maskTypeInt++){
                                if (falseHtobbMask[maskHtobbInt][maskTypeInt]){
                                    passSemiLepLepCutWeightedCtrAr[maskHtobbInt][maskTypeInt][0] += *genWeightL;
                                    for (unsigned int C2VCtr = 1; C2VCtr < passSemiLepLepCutWeightedCtrAr[maskHtobbInt][maskTypeInt].size(); C2VCtr++){
                                        passSemiLepLepCutWeightedCtrAr[maskHtobbInt][maskTypeInt][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                                    }
                                }
                            }
                        }
                    
                        
                    }
                    Int_t FJInd;

                    FJInd = -1;
                    //UInt_t numFatJet = *nFatJetL;
                    if (debug){
                        std::cout << "Pre FJC dRCheckVecAr.size() " << dRCheckVecAr.size() << "\n";
                    }
                    doSemiLepChanFatJetCut(FJInd,numFatJet,fatJetPTCut,fatJetZParticleNetCut,FatJet_ptL,FatJet_phiL,FatJet_etaL,FatJet_massL,FatJet_particleNet_ZvsQCDL,FatJet_jetIdL,dRCheckVecAr,dRCut,passSemiLepCut,passesCutsBool,passedAsSemiLepBool);
                    if (debug){
                        std::cout << "Post FJC dRCheckVecAr.size() " << dRCheckVecAr.size() << " FJInd "<< FJInd <<"\n";
                    }
                    if (FJInd >= 0){
                        passFJInSemiLepChannelCtr += 1;
                        //passFJInSemiLepChannelWeightedCtr += tmpGenWeights;

                        if (FJInd == *ZFJIndL) {
                            ZReconstructedWithCorrectFJ_SL_L = true;
                            ZReconstructedWithHFJ_SL_L = false;
                            }
                        else if (FJInd == *HFJIndL) {
                            ZReconstructedWithCorrectFJ_SL_L = false;
                            ZReconstructedWithHFJ_SL_L = true;
                        }
                        else {
                            ZReconstructedWithCorrectFJ_SL_L = false;
                            ZReconstructedWithHFJ_SL_L = false;
                        }

                        if (*HTobbBoolL){
                            if (*genChannelL == 0) {
                                passFJInSemiLepChannelGenLepCtr += 1;
                                //passFJInSemiLepChannelGenLepWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 1) {
                                passFJInSemiLepChannelGenSemiLepCtr += 1;
                                //passFJInSemiLepChannelGenSemiLepWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 2) {
                                passFJInSemiLepChannelGenHadCtr += 1;
                                //passFJInSemiLepChannelGenHadWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 3) {
                                passFJInSemiLepChannelGenOtherCtr += 1;
                                //passFJInSemiLepChannelGenOtherWeightedCtr += tmpGenWeights;
                            }
                        }
                        else{
                            if (*genChannelL == 0) {
                                passFJInSemiLepChannelGenLepNoHTobbCtr += 1;
                                //passFJInSemiLepChannelGenLepNoHTobbWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 1) {
                                passFJInSemiLepChannelGenSemiLepNoHTobbCtr += 1;
                                //passFJInSemiLepChannelGenSemiLepNoHTobbWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 2) {
                                passFJInSemiLepChannelGenHadNoHTobbCtr += 1;
                                //passFJInSemiLepChannelGenHadNoHTobbWeightedCtr += tmpGenWeights;
                            }
                            if (*genChannelL == 3) {
                                passFJInSemiLepChannelGenOtherNoHTobbCtr += 1;
                                //passFJInSemiLepChannelGenOtherNoHTobbWeightedCtr += tmpGenWeights;
                            }
                        }

                        for (unsigned int maskHtobbInt = 0; maskHtobbInt < falseHtobbMask.size(); maskHtobbInt++){
                            for (unsigned int maskTypeInt = 0; maskTypeInt < falseHtobbMask[maskHtobbInt].size(); maskTypeInt++){
                                if (falseHtobbMask[maskHtobbInt][maskTypeInt]){
                                    passFJInSemiLepChannelWeightedCtrAr[maskHtobbInt][maskTypeInt][0] += *genWeightL;
                                    for (unsigned int C2VCtr = 1; C2VCtr < passFJInSemiLepChannelWeightedCtrAr[maskHtobbInt][maskTypeInt].size(); C2VCtr++){
                                        passFJInSemiLepChannelWeightedCtrAr[maskHtobbInt][maskTypeInt][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                                    }
                                }
                            }
                        }
                        
                    FJIndAr.push_back(FJInd);
                    
                    }
                }
                
                if (passesCutsBool){
                    passChannelCtr += 1;
                    //passChannelWeightedCtr += tmpGenWeights;
                    if (*HTobbBoolL){
                        if (*genChannelL == 0) {
                            passChannelGenLepCtr += 1;
                            //passChannelGenLepWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 1) {
                            passChannelGenSemiLepCtr += 1;
                            //passChannelGenSemiLepWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 2) {
                            passChannelGenHadCtr += 1;
                            //passChannelGenHadWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 3) {
                            passChannelGenOtherCtr += 1;
                            //passChannelGenOtherWeightedCtr += tmpGenWeights;
                        }
                    }
                    else {
                        if (*genChannelL == 0) {
                            passChannelGenLepNoHTobbCtr += 1;
                            //passChannelGenLepNoHTobbWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 1) {
                            passChannelGenSemiLepNoHTobbCtr += 1;
                            //passChannelGenSemiLepNoHTobbWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 2) {
                            passChannelGenHadNoHTobbCtr += 1;
                            //passChannelGenHadNoHTobbWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 3) {
                            passChannelGenOtherNoHTobbCtr += 1;
                            //passChannelGenOtherNoHTobbWeightedCtr += tmpGenWeights;
                        }
                    }

                    for (unsigned int maskHtobbInt = 0; maskHtobbInt < falseHtobbMask.size(); maskHtobbInt++){
                        for (unsigned int maskTypeInt = 0; maskTypeInt < falseHtobbMask[maskHtobbInt].size(); maskTypeInt++){
                            if (falseHtobbMask[maskHtobbInt][maskTypeInt]){
                                passChannelWeightedCtrAr[maskHtobbInt][maskTypeInt][0] += *genWeightL;
                                for (unsigned int C2VCtr = 1; C2VCtr < passChannelWeightedCtrAr[maskHtobbInt][maskTypeInt].size(); C2VCtr++){
                                    passChannelWeightedCtrAr[maskHtobbInt][maskTypeInt][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                                }
                            }
                        }
                    }
                    


                    passSemiLepChannelCtr += 1;
                    //passSemiLepChannelWeightedCtr += tmpGenWeights;
                    if (*HTobbBoolL){
                        if (*genChannelL == 0) {
                            passSemiLepChannelGenLepCtr += 1;
                            //passSemiLepChannelGenLepWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 1) {
                            passSemiLepChannelGenSemiLepCtr += 1;
                            //passSemiLepChannelGenSemiLepWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 2) {
                            passSemiLepChannelGenHadCtr += 1;
                            //passSemiLepChannelGenHadWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 3) {
                            passSemiLepChannelGenOtherCtr += 1;
                            //passSemiLepChannelGenOtherWeightedCtr += tmpGenWeights;
                        }
                    }
                    else {
                        if (*genChannelL == 0) {
                            passSemiLepChannelGenLepNoHTobbCtr += 1;
                            //passSemiLepChannelGenLepNoHTobbWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 1) {
                            passSemiLepChannelGenSemiLepNoHTobbCtr += 1;
                            //passSemiLepChannelGenSemiLepNoHTobbWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 2) {
                            passSemiLepChannelGenHadNoHTobbCtr += 1;
                            //passSemiLepChannelGenHadNoHTobbWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 3) {
                            passSemiLepChannelGenOtherNoHTobbCtr += 1;
                            //passSemiLepChannelGenOtherNoHTobbWeightedCtr += tmpGenWeights;
                        }
                    }

                    for (unsigned int maskHtobbInt = 0; maskHtobbInt < falseHtobbMask.size(); maskHtobbInt++){
                        for (unsigned int maskTypeInt = 0; maskTypeInt < falseHtobbMask[maskHtobbInt].size(); maskTypeInt++){
                            if (falseHtobbMask[maskHtobbInt][maskTypeInt]){
                                passSemiLepChannelWeightedCtrAr[maskHtobbInt][maskTypeInt][0] += *genWeightL;
                                for (unsigned int C2VCtr = 1; C2VCtr < passSemiLepChannelWeightedCtrAr[maskHtobbInt][maskTypeInt].size(); C2VCtr++){
                                    passSemiLepChannelWeightedCtrAr[maskHtobbInt][maskTypeInt][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                                }
                            }
                        }
                    }
                    

                    passLepOrSemiLepChannelCtr += 1;
                    //passLepOrSemiLepChannelWeightedCtr += tmpGenWeights;
                    if (*HTobbBoolL){
                        if (*genChannelL == 0) {
                            passLepOrSemiLepChannelGenLepCtr += 1;
                            //passLepOrSemiLepChannelGenLepWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 1) {
                            passLepOrSemiLepChannelGenSemiLepCtr += 1;
                            //passLepOrSemiLepChannelGenSemiLepWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 2) {
                            passLepOrSemiLepChannelGenHadCtr += 1;
                            //passLepOrSemiLepChannelGenHadWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 3) {
                            passLepOrSemiLepChannelGenOtherCtr += 1;
                            //passLepOrSemiLepChannelGenOtherWeightedCtr += tmpGenWeights;
                        }
                    }
                    else {
                        if (*genChannelL == 0) {
                            passLepOrSemiLepChannelGenLepNoHTobbCtr += 1;
                            //passLepOrSemiLepChannelGenLepNoHTobbWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 1) {
                            passLepOrSemiLepChannelGenSemiLepNoHTobbCtr += 1;
                            //passLepOrSemiLepChannelGenSemiLepNoHTobbWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 2) {
                            passLepOrSemiLepChannelGenHadNoHTobbCtr += 1;
                            //passLepOrSemiLepChannelGenHadNoHTobbWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 3) {
                            passLepOrSemiLepChannelGenOtherNoHTobbCtr += 1;
                            //passLepOrSemiLepChannelGenOtherNoHTobbWeightedCtr += tmpGenWeights;
                        }
                    }

                    for (unsigned int maskHtobbInt = 0; maskHtobbInt < falseHtobbMask.size(); maskHtobbInt++){
                        for (unsigned int maskTypeInt = 0; maskTypeInt < falseHtobbMask[maskHtobbInt].size(); maskTypeInt++){
                            if (falseHtobbMask[maskHtobbInt][maskTypeInt]){
                                passLepOrSemiLepChannelWeightedCtrAr[maskHtobbInt][maskTypeInt][0] += *genWeightL;
                                for (unsigned int C2VCtr = 1; C2VCtr < passLepOrSemiLepChannelWeightedCtrAr[maskHtobbInt][maskTypeInt].size(); C2VCtr++){
                                    passLepOrSemiLepChannelWeightedCtrAr[maskHtobbInt][maskTypeInt][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                                }
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
                    //passChannelWeightedCtr += tmpGenWeights;
                    if (*HTobbBoolL){
                        if (*genChannelL == 0) {
                            passChannelGenLepCtr += 1;
                            //passChannelGenLepWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 1) {
                            passChannelGenSemiLepCtr += 1;
                            //passChannelGenSemiLepWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 2) {
                            passChannelGenHadCtr += 1;
                            //passChannelGenHadWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 3) {
                            passChannelGenOtherCtr += 1;
                            //passChannelGenOtherWeightedCtr += tmpGenWeights;
                        }
                    }
                    else {
                        if (*genChannelL == 0) {
                            passChannelGenLepNoHTobbCtr += 1;
                            //passChannelGenLepNoHTobbWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 1) {
                            passChannelGenSemiLepNoHTobbCtr += 1;
                            //passChannelGenSemiLepNoHTobbWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 2) {
                            passChannelGenHadNoHTobbCtr += 1;
                            //passChannelGenHadNoHTobbWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 3) {
                            passChannelGenOtherNoHTobbCtr += 1;
                            //passChannelGenOtherNoHTobbWeightedCtr += tmpGenWeights;
                        }
                    }

                    for (unsigned int maskHtobbInt = 0; maskHtobbInt < falseHtobbMask.size(); maskHtobbInt++){
                        for (unsigned int maskTypeInt = 0; maskTypeInt < falseHtobbMask[maskHtobbInt].size(); maskTypeInt++){
                            if (falseHtobbMask[maskHtobbInt][maskTypeInt]){
                                passChannelWeightedCtrAr[maskHtobbInt][maskTypeInt][0] += *genWeightL;
                                for (unsigned int C2VCtr = 1; C2VCtr < passChannelWeightedCtrAr[maskHtobbInt][maskTypeInt].size(); C2VCtr++){
                                    passChannelWeightedCtrAr[maskHtobbInt][maskTypeInt][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                                }
                            }
                        }
                    }
                    
                    passHadChannelCtr += 1;
                    //passHadChannelWeightedCtr += tmpGenWeights;
                    if (*HTobbBoolL){
                        if (*genChannelL == 0) {
                            passHadChannelGenLepCtr += 1;
                            //passHadChannelGenLepWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 1) {
                            passHadChannelGenSemiLepCtr += 1;
                            //passHadChannelGenSemiLepWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 2) {
                            passHadChannelGenHadCtr += 1;
                            //passHadChannelGenHadWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 3) {
                            passHadChannelGenOtherCtr += 1;
                            //passHadChannelGenOtherWeightedCtr += tmpGenWeights;
                        }
                    }
                    else {
                        if (*genChannelL == 0) {
                            passHadChannelGenLepNoHTobbCtr += 1;
                            //passHadChannelGenLepNoHTobbWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 1) {
                            passHadChannelGenSemiLepNoHTobbCtr += 1;
                            //passHadChannelGenSemiLepNoHTobbWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 2) {
                            passHadChannelGenHadNoHTobbCtr += 1;
                            //passHadChannelGenHadNoHTobbWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 3) {
                            passHadChannelGenOtherNoHTobbCtr += 1;
                            //passHadChannelGenOtherNoHTobbWeightedCtr += tmpGenWeights;
                        }
                    }

                    for (unsigned int maskHtobbInt = 0; maskHtobbInt < falseHtobbMask.size(); maskHtobbInt++){
                        for (unsigned int maskTypeInt = 0; maskTypeInt < falseHtobbMask[maskHtobbInt].size(); maskTypeInt++){
                            if (falseHtobbMask[maskHtobbInt][maskTypeInt]){
                                passHadChannelWeightedCtrAr[maskHtobbInt][maskTypeInt][0] += *genWeightL;
                                for (unsigned int C2VCtr = 1; C2VCtr < passHadChannelWeightedCtrAr[maskHtobbInt][maskTypeInt].size(); C2VCtr++){
                                    passHadChannelWeightedCtrAr[maskHtobbInt][maskTypeInt][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                                }
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
            //doHiggsFatJetCut(nFatJetLen,hFatJet_pt_fromHTag,hFatJet_phi_fromHTag,hFatJet_eta_fromHTag,hFatJet_mass_fromHTag,hFatJet_HTag_fromHTag,hFatJet_ind_fromHTag,FatJet_particleNet_HbbvsQCDL,hFatJetParticleNetCut,FatJet_ptL,hFatJetPTCut,FatJet_jetIdL,FatJet_phiL,FatJet_etaL,FatJet_massL,dRCheckVecAr,dRCut,FJIndAr,ZPairPlusHInvMassCut,ZPairPlusHPtCut);
            doHiggsFatJetCutEarlySelection(nFatJetLen,hFatJet_pt_fromHTag,hFatJet_phi_fromHTag,hFatJet_eta_fromHTag,hFatJet_mass_fromHTag,hFatJet_HTag_fromHTag,hFatJet_ind_fromHTag,FatJet_particleNet_HbbvsQCDL,hFatJetParticleNetCut,FatJet_ptL,hFatJetPTCut,FatJet_jetIdL,FatJet_phiL,FatJet_etaL,FatJet_massL,dRCheckVecAr,dRCut,FJIndAr);
            
            if (hFatJet_pt_fromHTag == 0) continue;
            if (debug) std::cout << " found Higgs fat jet\n";

            passHiggsFJPreSTCtr += 1;
            //passHiggsFJPreSTWeightedCtr += tmpGenWeights;
            debug = false;
            if (hFatJet_ind_fromHTag == *HFJIndL) {
                HReconstructedWithCorrectFJ_SL_L = true;
                HReconstructedWithZFJ_SL_L = false;
                }
            else if (hFatJet_ind_fromHTag == *ZFJIndL) {
                HReconstructedWithCorrectFJ_SL_L = false;
                HReconstructedWithZFJ_SL_L = true;
            }
            else {
                HReconstructedWithCorrectFJ_SL_L = false;
                HReconstructedWithZFJ_SL_L = false;
            }

            if (*HTobbBoolL){
                if (*genChannelL == 0) {
                    passHiggsFJPreSTGenLepCtr += 1;
                    //passHiggsFJPreSTGenLepWeightedCtr += tmpGenWeights;
                }
                if (*genChannelL == 1) {
                    passHiggsFJPreSTGenSemiLepCtr += 1;
                    //passHiggsFJPreSTGenSemiLepWeightedCtr += tmpGenWeights;
                }
                if (*genChannelL == 2) {
                    passHiggsFJPreSTGenHadCtr += 1;
                    //passHiggsFJPreSTGenHadWeightedCtr += tmpGenWeights;
                }
                if (*genChannelL == 3) {
                    passHiggsFJPreSTGenOtherCtr += 1;
                    //passHiggsFJPreSTGenOtherWeightedCtr += tmpGenWeights;
                }
            }
            else {
                if (*genChannelL == 0) {
                    passHiggsFJPreSTGenLepNoHTobbCtr += 1;
                    //passHiggsFJPreSTGenLepNoHTobbWeightedCtr += tmpGenWeights;
                }
                if (*genChannelL == 1) {
                    passHiggsFJPreSTGenSemiLepNoHTobbCtr += 1;
                    //passHiggsFJPreSTGenSemiLepNoHTobbWeightedCtr += tmpGenWeights;
                }
                if (*genChannelL == 2) {
                    passHiggsFJPreSTGenHadNoHTobbCtr += 1;
                    //passHiggsFJPreSTGenHadNoHTobbWeightedCtr += tmpGenWeights;
                }
                if (*genChannelL == 3) {
                    passHiggsFJPreSTGenOtherNoHTobbCtr += 1;
                    //passHiggsFJPreSTGenOtherNoHTobbWeightedCtr += tmpGenWeights;
                }
            }

            for (unsigned int maskHtobbInt = 0; maskHtobbInt < falseHtobbMask.size(); maskHtobbInt++){
                for (unsigned int maskTypeInt = 0; maskTypeInt < falseHtobbMask[maskHtobbInt].size(); maskTypeInt++){
                    if (falseHtobbMask[maskHtobbInt][maskTypeInt]){
                        passHiggsFJPreSTWeightedCtrAr[maskHtobbInt][maskTypeInt][0] += *genWeightL;
                        for (unsigned int C2VCtr = 1; C2VCtr < passHiggsFJPreSTWeightedCtrAr[maskHtobbInt][maskTypeInt].size(); C2VCtr++){
                            passHiggsFJPreSTWeightedCtrAr[maskHtobbInt][maskTypeInt][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                        }
                    }
                }
            }
            

            if (passedAsLepBool) {
                passHiggsFJPreSTLepCtr += 1;
                //passHiggsFJPreSTWeightedLepCtr += tmpGenWeights;
                if (*HTobbBoolL){
                    if (*genChannelL == 0) {
                        passHiggsFJPreSTLepGenLepCtr += 1;
                    //    passHiggsFJPreSTWeightedLepGenLepCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 1) {
                        passHiggsFJPreSTLepGenSemiLepCtr += 1;
                    //    passHiggsFJPreSTWeightedLepGenSemiLepCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 2) {
                        passHiggsFJPreSTLepGenHadCtr += 1;
                    //    passHiggsFJPreSTWeightedLepGenHadCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 3) {
                        passHiggsFJPreSTLepGenOtherCtr += 1;
                    //    passHiggsFJPreSTWeightedLepGenOtherCtr += tmpGenWeights;
                    }
                }
                else {
                    if (*genChannelL == 0) {
                        passHiggsFJPreSTLepGenLepNoHTobbCtr += 1;
                    //    passHiggsFJPreSTWeightedLepGenLepNoHTobbCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 1) {
                        passHiggsFJPreSTLepGenSemiLepNoHTobbCtr += 1;
                    //    passHiggsFJPreSTWeightedLepGenSemiLepNoHTobbCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 2) {
                        passHiggsFJPreSTLepGenHadNoHTobbCtr += 1;
                    //    passHiggsFJPreSTWeightedLepGenHadNoHTobbCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 3) {
                        passHiggsFJPreSTLepGenOtherNoHTobbCtr += 1;
                    //    passHiggsFJPreSTWeightedLepGenOtherNoHTobbCtr += tmpGenWeights;
                    }
                }

                for (unsigned int maskHtobbInt = 0; maskHtobbInt < falseHtobbMask.size(); maskHtobbInt++){
                    for (unsigned int maskTypeInt = 0; maskTypeInt < falseHtobbMask[maskHtobbInt].size(); maskTypeInt++){
                        if (falseHtobbMask[maskHtobbInt][maskTypeInt]){
                            passHiggsFJPreSTWeightedLepCtr[maskHtobbInt][maskTypeInt][0] += *genWeightL;
                            for (unsigned int C2VCtr = 1; C2VCtr < passHiggsFJPreSTWeightedLepCtr[maskHtobbInt][maskTypeInt].size(); C2VCtr++){
                                passHiggsFJPreSTWeightedLepCtr[maskHtobbInt][maskTypeInt][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                            }
                        }
                    }
                }
                
            }
            else if (passedAsSemiLepBool) {
                passHiggsFJPreSTSemiLepCtr += 1;
                //passHiggsFJPreSTWeightedSemiLepCtr += tmpGenWeights;
                if (*HTobbBoolL){
                    if (*genChannelL == 0) {
                        passHiggsFJPreSTSemiLepGenLepCtr += 1;
                    //    passHiggsFJPreSTWeightedSemiLepGenLepCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 1) {
                        passHiggsFJPreSTSemiLepGenSemiLepCtr += 1;
                    //    passHiggsFJPreSTWeightedSemiLepGenSemiLepCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 2) {
                        passHiggsFJPreSTSemiLepGenHadCtr += 1;
                    //    passHiggsFJPreSTWeightedSemiLepGenHadCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 3) {
                        passHiggsFJPreSTSemiLepGenOtherCtr += 1;
                    //    passHiggsFJPreSTWeightedSemiLepGenOtherCtr += tmpGenWeights;
                    }
                }
                else {
                    if (*genChannelL == 0) {
                        passHiggsFJPreSTSemiLepGenLepNoHTobbCtr += 1;
                    //    passHiggsFJPreSTWeightedSemiLepGenLepNoHTobbCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 1) {
                        passHiggsFJPreSTSemiLepGenSemiLepNoHTobbCtr += 1;
                    //    passHiggsFJPreSTWeightedSemiLepGenSemiLepNoHTobbCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 2) {
                        passHiggsFJPreSTSemiLepGenHadNoHTobbCtr += 1;
                    //    passHiggsFJPreSTWeightedSemiLepGenHadNoHTobbCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 3) {
                        passHiggsFJPreSTSemiLepGenOtherNoHTobbCtr += 1;
                    //    passHiggsFJPreSTWeightedSemiLepGenOtherNoHTobbCtr += tmpGenWeights;
                    }
                }

                for (unsigned int maskHtobbInt = 0; maskHtobbInt < falseHtobbMask.size(); maskHtobbInt++){
                    for (unsigned int maskTypeInt = 0; maskTypeInt < falseHtobbMask[maskHtobbInt].size(); maskTypeInt++){
                        if (falseHtobbMask[maskHtobbInt][maskTypeInt]){
                            passHiggsFJPreSTWeightedSemiLepCtr[maskHtobbInt][maskTypeInt][0] += *genWeightL;
                            for (unsigned int C2VCtr = 1; C2VCtr < passHiggsFJPreSTWeightedSemiLepCtr[maskHtobbInt][maskTypeInt].size(); C2VCtr++){
                                passHiggsFJPreSTWeightedSemiLepCtr[maskHtobbInt][maskTypeInt][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                            }
                        }
                    }
                }
                
            }
            else if (passedAsHadBool) {
                passHiggsFJPreSTHadCtr += 1;
                //passHiggsFJPreSTWeightedHadCtr += tmpGenWeights;
                if (*HTobbBoolL){
                    if (*genChannelL == 0) {
                        passHiggsFJPreSTHadGenLepCtr += 1;
                    //    passHiggsFJPreSTWeightedHadGenLepCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 1) {
                        passHiggsFJPreSTHadGenSemiLepCtr += 1;
                    //    passHiggsFJPreSTWeightedHadGenSemiLepCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 2) {
                        passHiggsFJPreSTHadGenHadCtr += 1;
                    //    passHiggsFJPreSTWeightedHadGenHadCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 3) {
                        passHiggsFJPreSTHadGenOtherCtr += 1;
                    //    passHiggsFJPreSTWeightedHadGenOtherCtr += tmpGenWeights;
                    }
                }
                else {
                    if (*genChannelL == 0) {
                        passHiggsFJPreSTHadGenLepNoHTobbCtr += 1;
                    //    passHiggsFJPreSTWeightedHadGenLepNoHTobbCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 1) {
                        passHiggsFJPreSTHadGenSemiLepNoHTobbCtr += 1;
                    //    passHiggsFJPreSTWeightedHadGenSemiLepNoHTobbCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 2) {
                        passHiggsFJPreSTHadGenHadNoHTobbCtr += 1;
                    //    passHiggsFJPreSTWeightedHadGenHadNoHTobbCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 3) {
                        passHiggsFJPreSTHadGenOtherNoHTobbCtr += 1;
                    //    passHiggsFJPreSTWeightedHadGenOtherNoHTobbCtr += tmpGenWeights;
                    }
                }

                for (unsigned int maskHtobbInt = 0; maskHtobbInt < falseHtobbMask.size(); maskHtobbInt++){
                    for (unsigned int maskTypeInt = 0; maskTypeInt < falseHtobbMask[maskHtobbInt].size(); maskTypeInt++){
                        if (falseHtobbMask[maskHtobbInt][maskTypeInt]){
                            passHiggsFJPreSTWeightedHadCtr[maskHtobbInt][maskTypeInt][0] += *genWeightL;
                            for (unsigned int C2VCtr = 1; C2VCtr < passHiggsFJPreSTWeightedHadCtr[maskHtobbInt][maskTypeInt].size(); C2VCtr++){
                                passHiggsFJPreSTWeightedHadCtr[maskHtobbInt][maskTypeInt][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                            }
                        }
                    }
                }
                
            }








            bool passesSTCutBool = false;
            doHiggsFatJetCutSTWithBDTVars(dRCheckVecAr,ZPairPlusHInvMassCut,ZPairPlusHPtCut,ZPairPlusHInvMass,ZPairPlusHPt,passesSTCutBool);
            if (!passesSTCutBool) continue;
            if (debug) std::cout << " found Higgs fat jet\n";
            passHiggsFJCtr += 1;
            //passHiggsFJWeightedCtr += tmpGenWeights;
            if (*HTobbBoolL){
                if (*genChannelL == 0) {
                    passHiggsFJGenLepCtr += 1;
                    //passHiggsFJGenLepWeightedCtr += tmpGenWeights;
                }
                if (*genChannelL == 1) {
                    passHiggsFJGenSemiLepCtr += 1;
                    //passHiggsFJGenSemiLepWeightedCtr += tmpGenWeights;
                }
                if (*genChannelL == 2) {
                    passHiggsFJGenHadCtr += 1;
                    //passHiggsFJGenHadWeightedCtr += tmpGenWeights;
                }
                if (*genChannelL == 3) {
                    passHiggsFJGenOtherCtr += 1;
                    //passHiggsFJGenOtherWeightedCtr += tmpGenWeights;
                }
            }
            else {
                if (*genChannelL == 0) {
                    passHiggsFJGenLepNoHTobbCtr += 1;
                    //passHiggsFJGenLepNoHTobbWeightedCtr += tmpGenWeights;
                }
                if (*genChannelL == 1) {
                    passHiggsFJGenSemiLepNoHTobbCtr += 1;
                    //passHiggsFJGenSemiLepNoHTobbWeightedCtr += tmpGenWeights;
                }
                if (*genChannelL == 2) {
                    passHiggsFJGenHadNoHTobbCtr += 1;
                    //passHiggsFJGenHadNoHTobbWeightedCtr += tmpGenWeights;
                }
                if (*genChannelL == 3) {
                    passHiggsFJGenOtherNoHTobbCtr += 1;
                    //passHiggsFJGenOtherNoHTobbWeightedCtr += tmpGenWeights;
                }
            }

            for (unsigned int maskHtobbInt = 0; maskHtobbInt < falseHtobbMask.size(); maskHtobbInt++){
                for (unsigned int maskTypeInt = 0; maskTypeInt < falseHtobbMask[maskHtobbInt].size(); maskTypeInt++){
                    if (falseHtobbMask[maskHtobbInt][maskTypeInt]){
                        passHiggsFJWeightedCtrAr[maskHtobbInt][maskTypeInt][0] += *genWeightL;
                        for (unsigned int C2VCtr = 1; C2VCtr < passHiggsFJWeightedCtrAr[maskHtobbInt][maskTypeInt].size(); C2VCtr++){
                            passHiggsFJWeightedCtrAr[maskHtobbInt][maskTypeInt][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                        }
                    }
                }
            }
            

            if (passedAsLepBool) {
                passHiggsFJLepCtr += 1;
                //passHiggsFJWeightedLepCtr += tmpGenWeights;
                if (*HTobbBoolL){
                    if (*genChannelL == 0) {
                        passHiggsFJLepGenLepCtr += 1;
                    //    passHiggsFJWeightedLepGenLepCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 1) {
                        passHiggsFJLepGenSemiLepCtr += 1;
                    //    passHiggsFJWeightedLepGenSemiLepCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 2) {
                        passHiggsFJLepGenHadCtr += 1;
                    //    passHiggsFJWeightedLepGenHadCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 3) {
                        passHiggsFJLepGenOtherCtr += 1;
                    //    passHiggsFJWeightedLepGenOtherCtr += tmpGenWeights;
                    }
                }
                else {
                    if (*genChannelL == 0) {
                        passHiggsFJLepGenLepNoHTobbCtr += 1;
                    //    passHiggsFJWeightedLepGenLepNoHTobbCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 1) {
                        passHiggsFJLepGenSemiLepNoHTobbCtr += 1;
                    //    passHiggsFJWeightedLepGenSemiLepNoHTobbCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 2) {
                        passHiggsFJLepGenHadNoHTobbCtr += 1;
                    //    passHiggsFJWeightedLepGenHadNoHTobbCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 3) {
                        passHiggsFJLepGenOtherNoHTobbCtr += 1;
                    //    passHiggsFJWeightedLepGenOtherNoHTobbCtr += tmpGenWeights;
                    }
                }

                for (unsigned int maskHtobbInt = 0; maskHtobbInt < falseHtobbMask.size(); maskHtobbInt++){
                    for (unsigned int maskTypeInt = 0; maskTypeInt < falseHtobbMask[maskHtobbInt].size(); maskTypeInt++){
                        if (falseHtobbMask[maskHtobbInt][maskTypeInt]){
                            passHiggsFJWeightedLepCtr[maskHtobbInt][maskTypeInt][0] += *genWeightL;
                            for (unsigned int C2VCtr = 1; C2VCtr < passHiggsFJWeightedLepCtr[maskHtobbInt][maskTypeInt].size(); C2VCtr++){
                                passHiggsFJWeightedLepCtr[maskHtobbInt][maskTypeInt][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                            }
                        }
                    }
                }
            
            }
            else if (passedAsSemiLepBool) {
                passHiggsFJSemiLepCtr += 1;
                //passHiggsFJWeightedSemiLepCtr += tmpGenWeights;
                if (*HTobbBoolL){
                    if (*genChannelL == 0) {
                        passHiggsFJSemiLepGenLepCtr += 1;
                    //    passHiggsFJWeightedSemiLepGenLepCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 1) {
                        passHiggsFJSemiLepGenSemiLepCtr += 1;
                    //    passHiggsFJWeightedSemiLepGenSemiLepCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 2) {
                        passHiggsFJSemiLepGenHadCtr += 1;
                    //    passHiggsFJWeightedSemiLepGenHadCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 3) {
                        passHiggsFJSemiLepGenOtherCtr += 1;
                    //    passHiggsFJWeightedSemiLepGenOtherCtr += tmpGenWeights;
                    }
                }
                else {
                    if (*genChannelL == 0) {
                        passHiggsFJSemiLepGenLepNoHTobbCtr += 1;
                    //    passHiggsFJWeightedSemiLepGenLepNoHTobbCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 1) {
                        passHiggsFJSemiLepGenSemiLepNoHTobbCtr += 1;
                    //    passHiggsFJWeightedSemiLepGenSemiLepNoHTobbCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 2) {
                        passHiggsFJSemiLepGenHadNoHTobbCtr += 1;
                    //    passHiggsFJWeightedSemiLepGenHadNoHTobbCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 3) {
                        passHiggsFJSemiLepGenOtherNoHTobbCtr += 1;
                    //    passHiggsFJWeightedSemiLepGenOtherNoHTobbCtr += tmpGenWeights;
                    }
                }

                for (unsigned int maskHtobbInt = 0; maskHtobbInt < falseHtobbMask.size(); maskHtobbInt++){
                    for (unsigned int maskTypeInt = 0; maskTypeInt < falseHtobbMask[maskHtobbInt].size(); maskTypeInt++){
                        if (falseHtobbMask[maskHtobbInt][maskTypeInt]){
                            passHiggsFJWeightedSemiLepCtr[maskHtobbInt][maskTypeInt][0] += *genWeightL;
                            for (unsigned int C2VCtr = 1; C2VCtr < passHiggsFJWeightedSemiLepCtr[maskHtobbInt][maskTypeInt].size(); C2VCtr++){
                                passHiggsFJWeightedSemiLepCtr[maskHtobbInt][maskTypeInt][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                            }
                        }
                    }
                }
            
            }
            else if (passedAsHadBool) {
                passHiggsFJHadCtr += 1;
                //passHiggsFJWeightedHadCtr += tmpGenWeights;
                if (*HTobbBoolL){
                    if (*genChannelL == 0) {
                        passHiggsFJHadGenLepCtr += 1;
                    //    passHiggsFJWeightedHadGenLepCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 1) {
                        passHiggsFJHadGenSemiLepCtr += 1;
                    //    passHiggsFJWeightedHadGenSemiLepCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 2) {
                        passHiggsFJHadGenHadCtr += 1;
                    //    passHiggsFJWeightedHadGenHadCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 3) {
                        passHiggsFJHadGenOtherCtr += 1;
                    //    passHiggsFJWeightedHadGenOtherCtr += tmpGenWeights;
                    }
                }
                else {
                    if (*genChannelL == 0) {
                        passHiggsFJHadGenLepNoHTobbCtr += 1;
                    //    passHiggsFJWeightedHadGenLepNoHTobbCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 1) {
                        passHiggsFJHadGenSemiLepNoHTobbCtr += 1;
                    //    passHiggsFJWeightedHadGenSemiLepNoHTobbCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 2) {
                        passHiggsFJHadGenHadNoHTobbCtr += 1;
                    //    passHiggsFJWeightedHadGenHadNoHTobbCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 3) {
                        passHiggsFJHadGenOtherNoHTobbCtr += 1;
                    //    passHiggsFJWeightedHadGenOtherNoHTobbCtr += tmpGenWeights;
                    }
                }

                for (unsigned int maskHtobbInt = 0; maskHtobbInt < falseHtobbMask.size(); maskHtobbInt++){
                    for (unsigned int maskTypeInt = 0; maskTypeInt < falseHtobbMask[maskHtobbInt].size(); maskTypeInt++){
                        if (falseHtobbMask[maskHtobbInt][maskTypeInt]){
                            passHiggsFJWeightedHadCtr[maskHtobbInt][maskTypeInt][0] += *genWeightL;
                            for (unsigned int C2VCtr = 1; C2VCtr < passHiggsFJWeightedHadCtr[maskHtobbInt][maskTypeInt].size(); C2VCtr++){
                                passHiggsFJWeightedHadCtr[maskHtobbInt][maskTypeInt][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                            }
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
            float jetLeadMass    = 0;
            float jetTrailingMass    = 0;

            //B jet veto
            bool passBJetVeto = true;
            float maxPassingBTag = 0;
            doBJetVeto_WithBDTVariables(nJetLen,Jet_ptL,Jet_etaL,Jet_phiL,Jet_btagDeepFlavBL,hFatJet_phi_fromHTag,hFatJet_eta_fromHTag,dRCut,bTagCut,passBJetVeto,maxPassingBTag,debug);
            if (!passBJetVeto) continue;

            passVBFJetBVetoCtr += 1;
            //passVBFJetBVetoWeightedCtr += tmpGenWeights;
            if (*HTobbBoolL){
                if (*genChannelL == 0) {
                    passVBFJetBVetoGenLepCtr += 1;
                    //passVBFJetBVetoGenLepWeightedCtr += tmpGenWeights;
                }
                if (*genChannelL == 1) {
                    passVBFJetBVetoGenSemiLepCtr += 1;
                    //passVBFJetBVetoGenSemiLepWeightedCtr += tmpGenWeights;
                }
                if (*genChannelL == 2) {
                    passVBFJetBVetoGenHadCtr += 1;
                    //passVBFJetBVetoGenHadWeightedCtr += tmpGenWeights;
                }
                if (*genChannelL == 3) {
                    passVBFJetBVetoGenOtherCtr += 1;
                    //passVBFJetBVetoGenOtherWeightedCtr += tmpGenWeights;
                }
            }
            else {
                if (*genChannelL == 0) {
                    passVBFJetBVetoGenLepNoHTobbCtr += 1;
                    //passVBFJetBVetoGenLepNoHTobbWeightedCtr += tmpGenWeights;
                }
                if (*genChannelL == 1) {
                    passVBFJetBVetoGenSemiLepNoHTobbCtr += 1;
                    //passVBFJetBVetoGenSemiLepNoHTobbWeightedCtr += tmpGenWeights;
                }
                if (*genChannelL == 2) {
                    passVBFJetBVetoGenHadNoHTobbCtr += 1;
                    //passVBFJetBVetoGenHadNoHTobbWeightedCtr += tmpGenWeights;
                }
                if (*genChannelL == 3) {
                    passVBFJetBVetoGenOtherNoHTobbCtr += 1;
                    //passVBFJetBVetoGenOtherNoHTobbWeightedCtr += tmpGenWeights;
                }
            }

            for (unsigned int maskHtobbInt = 0; maskHtobbInt < falseHtobbMask.size(); maskHtobbInt++){
                for (unsigned int maskTypeInt = 0; maskTypeInt < falseHtobbMask[maskHtobbInt].size(); maskTypeInt++){
                    if (falseHtobbMask[maskHtobbInt][maskTypeInt]){
                        passVBFJetBVetoWeightedCtr[maskHtobbInt][maskTypeInt][0] += *genWeightL;
                        for (unsigned int C2VCtr = 1; C2VCtr < passVBFJetBVetoWeightedCtr[maskHtobbInt][maskTypeInt].size(); C2VCtr++){
                            passVBFJetBVetoWeightedCtr[maskHtobbInt][maskTypeInt][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                        }
                    }
                }
            }
        

            if (passedAsLepBool) {
                passVBFJetBVetoLepCtr += 1;
                //passVBFJetBVetoWeightedLepCtr += tmpGenWeights;
                if (*HTobbBoolL){
                    if (*genChannelL == 0) {
                        passVBFJetBVetoLepGenLepCtr += 1;
                        //passVBFJetBVetoWeightedLepGenLepCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 1) {
                        passVBFJetBVetoLepGenSemiLepCtr += 1;
                        //passVBFJetBVetoWeightedLepGenSemiLepCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 2) {
                        passVBFJetBVetoLepGenHadCtr += 1;
                        //passVBFJetBVetoWeightedLepGenHadCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 3) {
                        passVBFJetBVetoLepGenOtherCtr += 1;
                        //passVBFJetBVetoWeightedLepGenOtherCtr += tmpGenWeights;
                    }
                }
                else {
                    if (*genChannelL == 0) {
                        passVBFJetBVetoLepGenLepNoHTobbCtr += 1;
                        //passVBFJetBVetoWeightedLepGenLepNoHTobbCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 1) {
                        passVBFJetBVetoLepGenSemiLepNoHTobbCtr += 1;
                        //passVBFJetBVetoWeightedLepGenSemiLepNoHTobbCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 2) {
                        passVBFJetBVetoLepGenHadNoHTobbCtr += 1;
                        //passVBFJetBVetoWeightedLepGenHadNoHTobbCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 3) {
                        passVBFJetBVetoLepGenOtherNoHTobbCtr += 1;
                        //passVBFJetBVetoWeightedLepGenOtherNoHTobbCtr += tmpGenWeights;
                    }
                }

                for (unsigned int maskHtobbInt = 0; maskHtobbInt < falseHtobbMask.size(); maskHtobbInt++){
                    for (unsigned int maskTypeInt = 0; maskTypeInt < falseHtobbMask[maskHtobbInt].size(); maskTypeInt++){
                        if (falseHtobbMask[maskHtobbInt][maskTypeInt]){
                            passVBFJetBVetoWeightedLepCtr[maskHtobbInt][maskTypeInt][0] += *genWeightL;
                            for (unsigned int C2VCtr = 1; C2VCtr < passVBFJetBVetoWeightedLepCtr[maskHtobbInt][maskTypeInt].size(); C2VCtr++){
                                passVBFJetBVetoWeightedLepCtr[maskHtobbInt][maskTypeInt][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                            }
                        }
                    }
                }
            
            }
            else if (passedAsSemiLepBool) {
                passVBFJetBVetoSemiLepCtr += 1;
                //passVBFJetBVetoWeightedSemiLepCtr += tmpGenWeights;
                if (*HTobbBoolL){
                    if (*genChannelL == 0) {
                        passVBFJetBVetoSemiLepGenLepCtr += 1;
                        //passVBFJetBVetoWeightedSemiLepGenLepCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 1) {
                        passVBFJetBVetoSemiLepGenSemiLepCtr += 1;
                        //passVBFJetBVetoWeightedSemiLepGenSemiLepCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 2) {
                        passVBFJetBVetoSemiLepGenHadCtr += 1;
                        //passVBFJetBVetoWeightedSemiLepGenHadCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 3) {
                        passVBFJetBVetoSemiLepGenOtherCtr += 1;
                        //passVBFJetBVetoWeightedSemiLepGenOtherCtr += tmpGenWeights;
                    }
                }
                else {
                    if (*genChannelL == 0) {
                        passVBFJetBVetoSemiLepGenLepNoHTobbCtr += 1;
                        //passVBFJetBVetoWeightedSemiLepGenLepNoHTobbCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 1) {
                        passVBFJetBVetoSemiLepGenSemiLepNoHTobbCtr += 1;
                        //passVBFJetBVetoWeightedSemiLepGenSemiLepNoHTobbCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 2) {
                        passVBFJetBVetoSemiLepGenHadNoHTobbCtr += 1;
                        //passVBFJetBVetoWeightedSemiLepGenHadNoHTobbCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 3) {
                        passVBFJetBVetoSemiLepGenOtherNoHTobbCtr += 1;
                        //passVBFJetBVetoWeightedSemiLepGenOtherNoHTobbCtr += tmpGenWeights;
                    }
                }

                for (unsigned int maskHtobbInt = 0; maskHtobbInt < falseHtobbMask.size(); maskHtobbInt++){
                    for (unsigned int maskTypeInt = 0; maskTypeInt < falseHtobbMask[maskHtobbInt].size(); maskTypeInt++){
                        if (falseHtobbMask[maskHtobbInt][maskTypeInt]){
                            passVBFJetBVetoWeightedSemiLepCtr[maskHtobbInt][maskTypeInt][0] += *genWeightL;
                            for (unsigned int C2VCtr = 1; C2VCtr < passVBFJetBVetoWeightedSemiLepCtr[maskHtobbInt][maskTypeInt].size(); C2VCtr++){
                                passVBFJetBVetoWeightedSemiLepCtr[maskHtobbInt][maskTypeInt][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                            }
                        }
                    }
                }
            
            }
            else if (passedAsHadBool) {
                passVBFJetBVetoHadCtr += 1;
                //passVBFJetBVetoWeightedHadCtr += tmpGenWeights;
                if (*HTobbBoolL){
                    if (*genChannelL == 0) {
                        passVBFJetBVetoHadGenLepCtr += 1;
                        //passVBFJetBVetoWeightedHadGenLepCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 1) {
                        passVBFJetBVetoHadGenSemiLepCtr += 1;
                        //passVBFJetBVetoWeightedHadGenSemiLepCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 2) {
                        passVBFJetBVetoHadGenHadCtr += 1;
                        //passVBFJetBVetoWeightedHadGenHadCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 3) {
                        passVBFJetBVetoHadGenOtherCtr += 1;
                        //passVBFJetBVetoWeightedHadGenOtherCtr += tmpGenWeights;
                    }
                }
                else {
                    if (*genChannelL == 0) {
                        passVBFJetBVetoHadGenLepNoHTobbCtr += 1;
                        //passVBFJetBVetoWeightedHadGenLepNoHTobbCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 1) {
                        passVBFJetBVetoHadGenSemiLepNoHTobbCtr += 1;
                        //passVBFJetBVetoWeightedHadGenSemiLepNoHTobbCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 2) {
                        passVBFJetBVetoHadGenHadNoHTobbCtr += 1;
                        //passVBFJetBVetoWeightedHadGenHadNoHTobbCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 3) {
                        passVBFJetBVetoHadGenOtherNoHTobbCtr += 1;
                        //passVBFJetBVetoWeightedHadGenOtherNoHTobbCtr += tmpGenWeights;
                    }
                }

                for (unsigned int maskHtobbInt = 0; maskHtobbInt < falseHtobbMask.size(); maskHtobbInt++){
                    for (unsigned int maskTypeInt = 0; maskTypeInt < falseHtobbMask[maskHtobbInt].size(); maskTypeInt++){
                        if (falseHtobbMask[maskHtobbInt][maskTypeInt]){
                            passVBFJetBVetoWeightedHadCtr[maskHtobbInt][maskTypeInt][0] += *genWeightL;
                            for (unsigned int C2VCtr = 1; C2VCtr < passVBFJetBVetoWeightedHadCtr[maskHtobbInt][maskTypeInt].size(); C2VCtr++){
                                passVBFJetBVetoWeightedHadCtr[maskHtobbInt][maskTypeInt][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                            }
                        }
                    }
                }
            
            }



            if (debug) std::cout << "Entering jet loop. Len: " << nJetLen << "\n";
            //doVBFJetCutPtSelectionWithBDTVars(nJetLen,Jet_ptL,Jet_jetIdL,Jet_etaL,Jet_phiL,Jet_massL,jetPTCut,jetEtaDifCut,jetInvMassCut,jetPairInvMass,jetLeadPt,jetLeadEta,jetLeadPhi,jetLeadMass,jetTrailingPt,jetTrailingEta,jetTrailingPhi,jetTrailingMass,leadJet_1,leadJet_2,dRCheckVecAr,dRCut,debug);
            //doVBFJetCutdEtaSelectionWithBDTVars(nJetLen,Jet_ptL,Jet_jetIdL,Jet_etaL,Jet_phiL,Jet_massL,jetPTCut,jetEtaDifCut,jetInvMassCut,jetPairInvMass,jetLeadPt,jetLeadEta,jetLeadPhi,jetLeadMass,jetTrailingPt,jetTrailingEta,jetTrailingPhi,jetTrailingMass,leadJet_1,leadJet_2,dRCheckVecAr,dRCut,debug);
            doVBFJetCutdEtaSelectionNoInvMassWithBDTVars(nJetLen,Jet_ptL,Jet_jetIdL,Jet_etaL,Jet_phiL,Jet_massL,jetPTCut,jetEtaDifCut,jetInvMassCut,jetPairInvMass,jetLeadPt,jetLeadEta,jetLeadPhi,jetLeadMass,jetTrailingPt,jetTrailingEta,jetTrailingPhi,jetTrailingMass,leadJet_1,leadJet_2,dRCheckVecAr,dRCut,debug);
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
                //passVBFJetsWeightedCtr += tmpGenWeights;
                if (*HTobbBoolL){
                    if (*genChannelL == 0) {
                        passVBFJetsGenLepCtr += 1;
                        //passVBFJetsGenLepWeightedCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 1) {
                        passVBFJetsGenSemiLepCtr += 1;
                        //passVBFJetsGenSemiLepWeightedCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 2) {
                        passVBFJetsGenHadCtr += 1;
                        //passVBFJetsGenHadWeightedCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 3) {
                        passVBFJetsGenOtherCtr += 1;
                        //passVBFJetsGenOtherWeightedCtr += tmpGenWeights;
                    }
                }
                else {
                    if (*genChannelL == 0) {
                        passVBFJetsGenLepNoHTobbCtr += 1;
                        //passVBFJetsGenLepNoHTobbWeightedCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 1) {
                        passVBFJetsGenSemiLepNoHTobbCtr += 1;
                        //passVBFJetsGenSemiLepNoHTobbWeightedCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 2) {
                        passVBFJetsGenHadNoHTobbCtr += 1;
                        //passVBFJetsGenHadNoHTobbWeightedCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 3) {
                        passVBFJetsGenOtherNoHTobbCtr += 1;
                        //passVBFJetsGenOtherNoHTobbWeightedCtr += tmpGenWeights;
                    }
                }

                for (unsigned int maskHtobbInt = 0; maskHtobbInt < falseHtobbMask.size(); maskHtobbInt++){
                    for (unsigned int maskTypeInt = 0; maskTypeInt < falseHtobbMask[maskHtobbInt].size(); maskTypeInt++){
                        if (falseHtobbMask[maskHtobbInt][maskTypeInt]){
                            passVBFJetsWeightedCtr[maskHtobbInt][maskTypeInt][0] += *genWeightL;
                            for (unsigned int C2VCtr = 1; C2VCtr < passVBFJetsWeightedCtr[maskHtobbInt][maskTypeInt].size(); C2VCtr++){
                                passVBFJetsWeightedCtr[maskHtobbInt][maskTypeInt][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                            }
                        }
                    }
                }

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
                    //passAsLepWeightedCtr += tmpGenWeights;

                    for (unsigned int maskHtobbInt = 0; maskHtobbInt < falseHtobbMask.size(); maskHtobbInt++){
                        for (unsigned int maskTypeInt = 0; maskTypeInt < falseHtobbMask[maskHtobbInt].size(); maskTypeInt++){
                            if (falseHtobbMask[maskHtobbInt][maskTypeInt]){
                                passAsLepWeightedCtr[maskHtobbInt][maskTypeInt][0] += *genWeightL;
                                for (unsigned int C2VCtr = 1; C2VCtr < passAsLepWeightedCtr[maskHtobbInt][maskTypeInt].size(); C2VCtr++){
                                    passAsLepWeightedCtr[maskHtobbInt][maskTypeInt][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                                }
                            }
                        }
                    }

                    if (!BDTSignalGenChannelMatched){
                        //Fill BDT Lep Tree

                        nLHEReweightingWeight_L_L = *nLHEReweightingWeightL;
                        for (UInt_t nReweightItr=0; nReweightItr<nLHEReweightingWeight_L_L;nReweightItr++){
                            LHEReweightingWeight_L_L.push_back(LHEReweightingWeightL[nReweightItr]);
                        }

                        passingEvGenWeight_L_L = tmpGenWeights;

                        //passingEvFullWeight_L_L = tmpGenWeights*XS*Run2Lumi/totWeight;

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
                        selectedZOneLeadLepton_phi_L_L = dRCheckVecAr[0].Phi();
                        selectedZOneTrailingLepton_phi_L_L = dRCheckVecAr[1].Phi();
                        selectedZOneLeadLepton_SIP3D_L_L = Z1LeadSIP;
                        selectedZOneTrailingLepton_SIP3D_L_L = Z1TrailingSIP;

                        selectedZOneLeptons_InvMass_L_L = selectedZOneLeptons_InvMass; 
                        selectedZOneLeptons_Type_L_L = Z1IsMuon;

                        selectedZTwoLeadLepton_pt_L_L = tmpTopZ2LeadPt;
                        selectedZTwoTrailingLepton_pt_L_L = tmpTopZ2TrailingPt;
                        selectedZTwoLeadLepton_eta_L_L = dRCheckVecAr[2].Eta();
                        selectedZTwoTrailingLepton_eta_L_L = dRCheckVecAr[3].Eta();
                        selectedZTwoLeadLepton_phi_L_L = dRCheckVecAr[2].Phi();
                        selectedZTwoTrailingLepton_phi_L_L = dRCheckVecAr[3].Phi();
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

                        LHEReweightingWeight_L_L.clear();

                        Jet_eta_L_L.clear();
                        Jet_pt_L_L.clear();
                        Jet_phi_L_L.clear();
                        Jet_mass_L_L.clear();
                        Jet_jetId_L_L.clear();
                        Jet_btagDeepFlavB_L_L.clear();

                    }

                    if (*HTobbBoolL){
                        if (*genChannelL == 0) {
                            passAsLepGenLepCtr += 1;
                            //passAsLepGenLepWeightedCtr += tmpGenWeights;

                            

                            if (BDTSignalGenChannelMatched){


                                //Fill BDT Lep Tree

                                nLHEReweightingWeight_L_L = *nLHEReweightingWeightL;
                                for (UInt_t nReweightItr=0; nReweightItr<nLHEReweightingWeight_L_L;nReweightItr++){
                                    LHEReweightingWeight_L_L.push_back(LHEReweightingWeightL[nReweightItr]);
                                }


                                passingEvGenWeight_L_L = tmpGenWeights;

                                //passingEvFullWeight_L_L = tmpGenWeights*XS*Run2Lumi/totWeight;

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
                                selectedZOneLeadLepton_phi_L_L = dRCheckVecAr[0].Phi();
                                selectedZOneTrailingLepton_phi_L_L = dRCheckVecAr[1].Phi();
                                selectedZOneLeadLepton_SIP3D_L_L = Z1LeadSIP;
                                selectedZOneTrailingLepton_SIP3D_L_L = Z1TrailingSIP;

                                selectedZOneLeptons_InvMass_L_L = selectedZOneLeptons_InvMass; 
                                selectedZOneLeptons_Type_L_L = Z1IsMuon;

                                selectedZTwoLeadLepton_pt_L_L = tmpTopZ2LeadPt;
                                selectedZTwoTrailingLepton_pt_L_L = tmpTopZ2TrailingPt;
                                selectedZTwoLeadLepton_eta_L_L = dRCheckVecAr[2].Eta();
                                selectedZTwoTrailingLepton_eta_L_L = dRCheckVecAr[3].Eta();
                                selectedZTwoLeadLepton_phi_L_L = dRCheckVecAr[2].Phi();
                                selectedZTwoTrailingLepton_phi_L_L = dRCheckVecAr[3].Phi();
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

                                LHEReweightingWeight_L_L.clear();

                                Jet_eta_L_L.clear();
                                Jet_pt_L_L.clear();
                                Jet_phi_L_L.clear();
                                Jet_mass_L_L.clear();
                                Jet_jetId_L_L.clear();
                                Jet_btagDeepFlavB_L_L.clear();
                            }




                        }
                        if (*genChannelL == 1) {
                            passAsLepGenSemiLepCtr += 1;
                            //passAsLepGenSemiLepWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 2) {
                            passAsLepGenHadCtr += 1;
                            //passAsLepGenHadWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 3) {
                            passAsLepGenOtherCtr += 1;
                            //passAsLepGenOtherWeightedCtr += tmpGenWeights;
                        }
                    }
                    else {
                        if (*genChannelL == 0) {
                            passAsLepGenLepNoHTobbCtr += 1;
                            //passAsLepGenLepNoHTobbWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 1) {
                            passAsLepGenSemiLepNoHTobbCtr += 1;
                            //passAsLepGenSemiLepNoHTobbWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 2) {
                            passAsLepGenHadNoHTobbCtr += 1;
                            //passAsLepGenHadNoHTobbWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 3) {
                            passAsLepGenOtherNoHTobbCtr += 1;
                            //passAsLepGenOtherNoHTobbWeightedCtr += tmpGenWeights;
                        }
                    }
                    
                    
                }
                
                else if (passedAsSemiLepBool){


                    passAsSemiLepCtr += 1;
                    //passAsSemiLepWeightedCtr += tmpGenWeights;

                    for (unsigned int maskHtobbInt = 0; maskHtobbInt < falseHtobbMask.size(); maskHtobbInt++){
                        for (unsigned int maskTypeInt = 0; maskTypeInt < falseHtobbMask[maskHtobbInt].size(); maskTypeInt++){
                            if (falseHtobbMask[maskHtobbInt][maskTypeInt]){
                                passAsSemiLepWeightedCtr[maskHtobbInt][maskTypeInt][0] += *genWeightL;
                                for (unsigned int C2VCtr = 1; C2VCtr < passAsSemiLepWeightedCtr[maskHtobbInt][maskTypeInt].size(); C2VCtr++){
                                    passAsSemiLepWeightedCtr[maskHtobbInt][maskTypeInt][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                                }
                            }
                        }
                    }


                    if (!BDTSignalGenChannelMatched){
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

                        selectedZFJ_InvMassSoftDrop_SL_L = FatJet_msoftdropL[FJIndAr[0]];
                        selectedHiggsFJ_InvMassSoftDrop_SL_L = FatJet_msoftdropL[FJIndAr[1]];


                        selectedHiggsFJ_ParticleNet_HbbvsQCD_SL_L = hFatJet_HTag_fromHTag;
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


                        

                        goodGenZFJMatch_SL_L = *goodGenZFJMatchL;
                        goodGenHFJMatch_SL_L = *goodGenHFJMatchL;
                        goodZFJMatchToGen_SL_L = *goodZFJMatchToGenL;
                        goodHFJMatchToGen_SL_L = *goodHFJMatchToGenL;
                        eventGenSemileptonic_SL_L = *eventGenSemileptonicL;
                        eventGenHToBB_SL_L = *eventGenHToBBL;
                        ZFJGenHadronFlavour_SL_L = *ZFJGenHadronFlavourL;
                        HFJGenHadronFlavour_SL_L = *HFJGenHadronFlavourL;
                        FatJet_hadronFlavour_SL_L =  FatJet_hadronFlavourL[FJIndAr[0]];




                        passingEvSemiLepTree->Fill();

                        LHEReweightingWeight_SL_L.clear();

                        Jet_eta_SL_L.clear();
                        Jet_pt_SL_L.clear();
                        Jet_phi_SL_L.clear();
                        Jet_mass_SL_L.clear();
                        Jet_jetId_SL_L.clear();
                        Jet_btagDeepFlavB_SL_L.clear();

                    }





                    if (*HTobbBoolL){
                        if (*genChannelL == 0) {
                            passAsSemiLepGenLepCtr += 1;
                            //passAsSemiLepGenLepWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 1) {
                            passAsSemiLepGenSemiLepCtr += 1;
                            //passAsSemiLepGenSemiLepWeightedCtr += tmpGenWeights;
                            //Fill BDT SemiLep Tree
                            if (BDTSignalGenChannelMatched){
                                passingEvGenWeight_SL_L = tmpGenWeights;

                                //passingEvFullWeight_SL_L = tmpGenWeights*XS*Run2Lumi/totWeight;

                                nLHEReweightingWeight_SL_L = *nLHEReweightingWeightL;
                                for (UInt_t nReweightItr=0; nReweightItr<nLHEReweightingWeight_SL_L;nReweightItr++){
                                    LHEReweightingWeight_SL_L.push_back(LHEReweightingWeightL[nReweightItr]);
                                }
                                passingEvGenWeight_SL_L = tmpGenWeights;

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

                                selectedZFJ_InvMassSoftDrop_SL_L = FatJet_msoftdropL[FJIndAr[0]];
                                selectedHiggsFJ_InvMassSoftDrop_SL_L = FatJet_msoftdropL[FJIndAr[1]];
                                
                                selectedHiggsFJ_ParticleNet_HbbvsQCD_SL_L = hFatJet_HTag_fromHTag;
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


                                goodGenZFJMatch_SL_L = *goodGenZFJMatchL;
                                goodGenHFJMatch_SL_L = *goodGenHFJMatchL;
                                goodZFJMatchToGen_SL_L = *goodZFJMatchToGenL;
                                goodHFJMatchToGen_SL_L = *goodHFJMatchToGenL;
                                eventGenSemileptonic_SL_L = *eventGenSemileptonicL;
                                eventGenHToBB_SL_L = *eventGenHToBBL;
                                ZFJGenHadronFlavour_SL_L = *ZFJGenHadronFlavourL;
                                HFJGenHadronFlavour_SL_L = *HFJGenHadronFlavourL;
                                FatJet_hadronFlavour_SL_L =  FatJet_hadronFlavourL[FJIndAr[0]];

                                passingEvSemiLepTree->Fill();

                                LHEReweightingWeight_SL_L.clear();

                                Jet_eta_SL_L.clear();
                                Jet_pt_SL_L.clear();
                                Jet_phi_SL_L.clear();
                                Jet_mass_SL_L.clear();
                                Jet_jetId_SL_L.clear();
                                Jet_btagDeepFlavB_SL_L.clear();

                            }





                        }
                        if (*genChannelL == 2) {
                            passAsSemiLepGenHadCtr += 1;
                            //passAsSemiLepGenHadWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 3) {
                            passAsSemiLepGenOtherCtr += 1;
                            //passAsSemiLepGenOtherWeightedCtr += tmpGenWeights;
                        }
                    }
                    else {
                        if (*genChannelL == 0) {
                            passAsSemiLepGenLepNoHTobbCtr += 1;
                            //passAsSemiLepGenLepNoHTobbWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 1) {
                            passAsSemiLepGenSemiLepNoHTobbCtr += 1;
                            //passAsSemiLepGenSemiLepNoHTobbWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 2) {
                            passAsSemiLepGenHadNoHTobbCtr += 1;
                            //passAsSemiLepGenHadNoHTobbWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 3) {
                            passAsSemiLepGenOtherNoHTobbCtr += 1;
                            //passAsSemiLepGenOtherNoHTobbWeightedCtr += tmpGenWeights;
                        }
                    }
                
                    

                }
                else if (passedAsHadBool) {

                    passAsHadCtr += 1;
                    //passAsHadWeightedCtr += tmpGenWeights;

                    for (unsigned int maskHtobbInt = 0; maskHtobbInt < falseHtobbMask.size(); maskHtobbInt++){
                        for (unsigned int maskTypeInt = 0; maskTypeInt < falseHtobbMask[maskHtobbInt].size(); maskTypeInt++){
                            if (falseHtobbMask[maskHtobbInt][maskTypeInt]){
                                passAsHadWeightedCtr[maskHtobbInt][maskTypeInt][0] += *genWeightL;
                                for (unsigned int C2VCtr = 1; C2VCtr < passAsHadWeightedCtr[maskHtobbInt][maskTypeInt].size(); C2VCtr++){
                                    passAsHadWeightedCtr[maskHtobbInt][maskTypeInt][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
                                }
                            }
                        }
                    }


                    if (*HTobbBoolL){
                        if (*genChannelL == 0) {
                            passAsHadGenLepCtr += 1;
                            //passAsHadGenLepWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 1) {
                            passAsHadGenSemiLepCtr += 1;
                            //passAsHadGenSemiLepWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 2) {
                            passAsHadGenHadCtr += 1;
                            //passAsHadGenHadWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 3) {
                            passAsHadGenOtherCtr += 1;
                            //passAsHadGenOtherWeightedCtr += tmpGenWeights;
                        }
                    }
                    else {
                        if (*genChannelL == 0) {
                            passAsHadGenLepNoHTobbCtr += 1;
                            //passAsHadGenLepNoHTobbWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 1) {
                            passAsHadGenSemiLepNoHTobbCtr += 1;
                            //passAsHadGenSemiLepNoHTobbWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 2) {
                            passAsHadGenHadNoHTobbCtr += 1;
                            //passAsHadGenHadNoHTobbWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 3) {
                            passAsHadGenOtherNoHTobbCtr += 1;
                            //passAsHadGenOtherNoHTobbWeightedCtr += tmpGenWeights;
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
    crossSection = crossSectionAvg / crossSectionCnt;
        
    std::cout << "XS: " << crossSection << "\n";
    std::cout << "nEv total: " << datanEv << "\n";
    std::cout << "nEv post pre-selection: " << datanEvPass << "\n"; 
    

    //--------------------HTobbChannel Output--------------

    std::vector<UInt_t> startingTypeCtrAr {startingGenLepCtr,startingGenSemiLepCtr,startingGenHadCtr,startingGenOtherCtr};
    std::vector<UInt_t> startingTypeNoHTobbCtrAr {startingGenLepNoHTobbCtr,startingGenSemiLepNoHTobbCtr,startingGenHadNoHTobbCtr,startingGenOtherNoHTobbCtr};
    std::vector<std::vector<UInt_t>> startingHTobbCtrAr {startingTypeCtrAr,startingTypeNoHTobbCtrAr};

    std::vector<UInt_t> tryingSemiLepChannelTypeCtrAr {tryingSemiLepChannelGenLepCtr,tryingSemiLepChannelGenSemiLepCtr,tryingSemiLepChannelGenHadCtr,tryingSemiLepChannelGenOtherCtr};
    std::vector<UInt_t> tryingSemiLepChannelTypeNoHTobbCtrAr {tryingSemiLepChannelGenLepNoHTobbCtr,tryingSemiLepChannelGenSemiLepNoHTobbCtr,tryingSemiLepChannelGenHadNoHTobbCtr,tryingSemiLepChannelGenOtherNoHTobbCtr};
    std::vector<std::vector<UInt_t>> tryingSemiLepChannelHTobbCtrAr {tryingSemiLepChannelTypeCtrAr,tryingSemiLepChannelTypeNoHTobbCtrAr};

    

    std::vector<UInt_t> passEnoughFJsInSemiLepChannelTypeCtrAr {passEnoughFJsInSemiLepChannelGenLepCtr,passEnoughFJsInSemiLepChannelGenSemiLepCtr,passEnoughFJsInSemiLepChannelGenHadCtr,passEnoughFJsInSemiLepChannelGenOtherCtr};
    std::vector<UInt_t> passEnoughFJsInSemiLepChannelTypeNoHTobbCtrAr {passEnoughFJsInSemiLepChannelGenLepNoHTobbCtr,passEnoughFJsInSemiLepChannelGenSemiLepNoHTobbCtr,passEnoughFJsInSemiLepChannelGenHadNoHTobbCtr,passEnoughFJsInSemiLepChannelGenOtherNoHTobbCtr};
    std::vector<std::vector<UInt_t>> passEnoughFJsInSemiLepChannelHTobbCtrAr {passEnoughFJsInSemiLepChannelTypeCtrAr,passEnoughFJsInSemiLepChannelTypeNoHTobbCtrAr};

    std::vector<UInt_t> passEnoughLepsInSemiLepChannelTypeCtrAr {passEnoughLepsInSemiLepChannelGenLepCtr,passEnoughLepsInSemiLepChannelGenSemiLepCtr,passEnoughLepsInSemiLepChannelGenHadCtr,passEnoughLepsInSemiLepChannelGenOtherCtr};
    std::vector<UInt_t> passEnoughLepsInSemiLepChannelTypeNoHTobbCtrAr {passEnoughLepsInSemiLepChannelGenLepNoHTobbCtr,passEnoughLepsInSemiLepChannelGenSemiLepNoHTobbCtr,passEnoughLepsInSemiLepChannelGenHadNoHTobbCtr,passEnoughLepsInSemiLepChannelGenOtherNoHTobbCtr};
    std::vector<std::vector<UInt_t>> passEnoughLepsInSemiLepChannelHTobbCtrAr {passEnoughLepsInSemiLepChannelTypeCtrAr,passEnoughLepsInSemiLepChannelTypeNoHTobbCtrAr};

    std::vector<UInt_t> passSemiLepLepCutTypeCtrAr {passSemiLepLepCutGenLepCtr,passSemiLepLepCutGenSemiLepCtr,passSemiLepLepCutGenHadCtr,passSemiLepLepCutGenOtherCtr};
    std::vector<UInt_t> passSemiLepLepCutTypeNoHTobbCtrAr {passSemiLepLepCutGenLepNoHTobbCtr,passSemiLepLepCutGenSemiLepNoHTobbCtr,passSemiLepLepCutGenHadNoHTobbCtr,passSemiLepLepCutGenOtherNoHTobbCtr};
    std::vector<std::vector<UInt_t>> passSemiLepLepCutChannelHTobbCtrAr {passSemiLepLepCutTypeCtrAr,passSemiLepLepCutTypeNoHTobbCtrAr};

    std::vector<UInt_t> passFJInSemiLepChannelTypeCtrAr {passFJInSemiLepChannelGenLepCtr,passFJInSemiLepChannelGenSemiLepCtr,passFJInSemiLepChannelGenHadCtr,passFJInSemiLepChannelGenOtherCtr};
    std::vector<UInt_t> passFJInSemiLepChannelTypeNoHTobbCtrAr {passFJInSemiLepChannelGenLepNoHTobbCtr,passFJInSemiLepChannelGenSemiLepNoHTobbCtr,passFJInSemiLepChannelGenHadNoHTobbCtr,passFJInSemiLepChannelGenOtherNoHTobbCtr};
    std::vector<std::vector<UInt_t>> passFJInSemiLepChannelHTobbCtrAr {passFJInSemiLepChannelTypeCtrAr,passFJInSemiLepChannelTypeNoHTobbCtrAr};

    std::vector<UInt_t> passChannelTypeCtrAr {passChannelGenLepCtr,passChannelGenSemiLepCtr,passChannelGenHadCtr,passChannelGenOtherCtr};
    std::vector<UInt_t> passChannelTypeNoHTobbCtrAr {passChannelGenLepNoHTobbCtr,passChannelGenSemiLepNoHTobbCtr,passChannelGenHadNoHTobbCtr,passChannelGenOtherNoHTobbCtr};
    std::vector<std::vector<UInt_t>> passChannelHTobbCtrAr {passChannelTypeCtrAr,passChannelTypeNoHTobbCtrAr};

    std::vector<UInt_t> passLepOrSemiLepChannelTypeCtrAr {passLepOrSemiLepChannelGenLepCtr,passLepOrSemiLepChannelGenSemiLepCtr,passLepOrSemiLepChannelGenHadCtr,passLepOrSemiLepChannelGenOtherCtr};
    std::vector<UInt_t> passLepOrSemiLepChannelTypeNoHTobbCtrAr {passLepOrSemiLepChannelGenLepNoHTobbCtr,passLepOrSemiLepChannelGenSemiLepNoHTobbCtr,passLepOrSemiLepChannelGenHadNoHTobbCtr,passLepOrSemiLepChannelGenOtherNoHTobbCtr};
    std::vector<std::vector<UInt_t>> passLepOrSemiLepChannelHTobbCtrAr {passLepOrSemiLepChannelTypeCtrAr,passLepOrSemiLepChannelTypeNoHTobbCtrAr};

    std::vector<UInt_t> passLepChannelTypeCtrAr {passLepChannelGenLepCtr,passLepChannelGenSemiLepCtr,passLepChannelGenHadCtr,passLepChannelGenOtherCtr};
    std::vector<UInt_t> passLepChannelTypeNoHTobbCtrAr {passLepChannelGenLepNoHTobbCtr,passLepChannelGenSemiLepNoHTobbCtr,passLepChannelGenHadNoHTobbCtr,passLepChannelGenOtherNoHTobbCtr};
    std::vector<std::vector<UInt_t>> passLepChannelHTobbCtrAr {passLepChannelTypeCtrAr,passLepChannelTypeNoHTobbCtrAr};

    

    std::vector<UInt_t> passSemiLepChannelTypeCtrAr {passSemiLepChannelGenLepCtr,passSemiLepChannelGenSemiLepCtr,passSemiLepChannelGenHadCtr,passSemiLepChannelGenOtherCtr};
    std::vector<UInt_t> passSemiLepChannelTypeNoHTobbCtrAr {passSemiLepChannelGenLepNoHTobbCtr,passSemiLepChannelGenSemiLepNoHTobbCtr,passSemiLepChannelGenHadNoHTobbCtr,passSemiLepChannelGenOtherNoHTobbCtr};
    std::vector<std::vector<UInt_t>> passSemiLepChannelHTobbCtrAr {passSemiLepChannelTypeCtrAr,passSemiLepChannelTypeNoHTobbCtrAr};

    std::vector<UInt_t> passHadChannelTypeCtrAr {passHadChannelGenLepCtr,passHadChannelGenSemiLepCtr,passHadChannelGenHadCtr,passHadChannelGenOtherCtr};
    std::vector<UInt_t> passHadChannelTypeNoHTobbCtrAr {passHadChannelGenLepNoHTobbCtr,passHadChannelGenSemiLepNoHTobbCtr,passHadChannelGenHadNoHTobbCtr,passHadChannelGenOtherNoHTobbCtr};
    std::vector<std::vector<UInt_t>> passHadChannelHTobbCtrAr {passHadChannelTypeCtrAr,passHadChannelTypeNoHTobbCtrAr};

    std::vector<UInt_t> passHiggsFJPreSTTypeCtrAr {passHiggsFJPreSTGenLepCtr,passHiggsFJPreSTGenSemiLepCtr,passHiggsFJPreSTGenHadCtr,passHiggsFJPreSTGenOtherCtr};
    std::vector<UInt_t> passHiggsFJPreSTTypeNoHTobbCtrAr {passHiggsFJPreSTGenLepNoHTobbCtr,passHiggsFJPreSTGenSemiLepNoHTobbCtr,passHiggsFJPreSTGenHadNoHTobbCtr,passHiggsFJPreSTGenOtherNoHTobbCtr};
    std::vector<std::vector<UInt_t>> passHiggsFJPreSTHTobbCtrAr {passHiggsFJPreSTTypeCtrAr,passHiggsFJPreSTTypeNoHTobbCtrAr};

    std::vector<UInt_t> passHiggsFJPreSTLepTypeCtrAr {passHiggsFJPreSTLepGenLepCtr,passHiggsFJPreSTLepGenSemiLepCtr,passHiggsFJPreSTLepGenHadCtr,passHiggsFJPreSTLepGenOtherCtr};
    std::vector<UInt_t> passHiggsFJPreSTLepTypeNoHTobbCtrAr {passHiggsFJPreSTLepGenLepNoHTobbCtr,passHiggsFJPreSTLepGenSemiLepNoHTobbCtr,passHiggsFJPreSTLepGenHadNoHTobbCtr,passHiggsFJPreSTLepGenOtherNoHTobbCtr};
    std::vector<std::vector<UInt_t>> passHiggsFJPreSTLepHTobbCtrAr {passHiggsFJPreSTLepTypeCtrAr,passHiggsFJPreSTLepTypeNoHTobbCtrAr};

    std::vector<UInt_t> passHiggsFJPreSTSemiLepTypeCtrAr {passHiggsFJPreSTSemiLepGenLepCtr,passHiggsFJPreSTSemiLepGenSemiLepCtr,passHiggsFJPreSTSemiLepGenHadCtr,passHiggsFJPreSTSemiLepGenOtherCtr};
    std::vector<UInt_t> passHiggsFJPreSTSemiLepTypeNoHTobbCtrAr {passHiggsFJPreSTSemiLepGenLepNoHTobbCtr,passHiggsFJPreSTSemiLepGenSemiLepNoHTobbCtr,passHiggsFJPreSTSemiLepGenHadNoHTobbCtr,passHiggsFJPreSTSemiLepGenOtherNoHTobbCtr};
    std::vector<std::vector<UInt_t>> passHiggsFJPreSTSemiLepHTobbCtrAr {passHiggsFJPreSTSemiLepTypeCtrAr,passHiggsFJPreSTSemiLepTypeNoHTobbCtrAr};

    std::vector<UInt_t> passHiggsFJPreSTHadTypeCtrAr {passHiggsFJPreSTHadGenLepCtr,passHiggsFJPreSTHadGenSemiLepCtr,passHiggsFJPreSTHadGenHadCtr,passHiggsFJPreSTHadGenOtherCtr};
    std::vector<UInt_t> passHiggsFJPreSTHadTypeNoHTobbCtrAr {passHiggsFJPreSTHadGenLepNoHTobbCtr,passHiggsFJPreSTHadGenSemiLepNoHTobbCtr,passHiggsFJPreSTHadGenHadNoHTobbCtr,passHiggsFJPreSTHadGenOtherNoHTobbCtr};
    std::vector<std::vector<UInt_t>> passHiggsFJPreSTHadHTobbCtrAr {passHiggsFJPreSTHadTypeCtrAr,passHiggsFJPreSTHadTypeNoHTobbCtrAr};

    std::vector<UInt_t> passHiggsFJTypeCtrAr {passHiggsFJGenLepCtr,passHiggsFJGenSemiLepCtr,passHiggsFJGenHadCtr,passHiggsFJGenOtherCtr};
    std::vector<UInt_t> passHiggsFJTypeNoHTobbCtrAr {passHiggsFJGenLepNoHTobbCtr,passHiggsFJGenSemiLepNoHTobbCtr,passHiggsFJGenHadNoHTobbCtr,passHiggsFJGenOtherNoHTobbCtr};
    std::vector<std::vector<UInt_t>> passHiggsFJHTobbCtrAr {passHiggsFJTypeCtrAr,passHiggsFJTypeNoHTobbCtrAr};

    


    std::vector<UInt_t> passHiggsFJLepTypeCtrAr {passHiggsFJLepGenLepCtr,passHiggsFJLepGenSemiLepCtr,passHiggsFJLepGenHadCtr,passHiggsFJLepGenOtherCtr};
    std::vector<UInt_t> passHiggsFJLepTypeNoHTobbCtrAr {passHiggsFJLepGenLepNoHTobbCtr,passHiggsFJLepGenSemiLepNoHTobbCtr,passHiggsFJLepGenHadNoHTobbCtr,passHiggsFJLepGenOtherNoHTobbCtr};
    std::vector<std::vector<UInt_t>> passHiggsFJLepHTobbCtrAr {passHiggsFJLepTypeCtrAr,passHiggsFJLepTypeNoHTobbCtrAr};
    
    std::vector<UInt_t> passHiggsFJSemiLepTypeCtrAr {passHiggsFJSemiLepGenLepCtr,passHiggsFJSemiLepGenSemiLepCtr,passHiggsFJSemiLepGenHadCtr,passHiggsFJSemiLepGenOtherCtr};
    std::vector<UInt_t> passHiggsFJSemiLepTypeNoHTobbCtrAr {passHiggsFJSemiLepGenLepNoHTobbCtr,passHiggsFJSemiLepGenSemiLepNoHTobbCtr,passHiggsFJSemiLepGenHadNoHTobbCtr,passHiggsFJSemiLepGenOtherNoHTobbCtr};
    std::vector<std::vector<UInt_t>> passHiggsFJSemiLepHTobbCtrAr {passHiggsFJSemiLepTypeCtrAr,passHiggsFJSemiLepTypeNoHTobbCtrAr};

    std::vector<UInt_t> passHiggsFJHadTypeCtrAr {passHiggsFJHadGenLepCtr,passHiggsFJHadGenSemiLepCtr,passHiggsFJHadGenHadCtr,passHiggsFJHadGenOtherCtr};
    std::vector<UInt_t> passHiggsFJHadTypeNoHTobbCtrAr {passHiggsFJHadGenLepNoHTobbCtr,passHiggsFJHadGenSemiLepNoHTobbCtr,passHiggsFJHadGenHadNoHTobbCtr,passHiggsFJHadGenOtherNoHTobbCtr};
    std::vector<std::vector<UInt_t>> passHiggsFJHadHTobbCtrAr {passHiggsFJHadTypeCtrAr,passHiggsFJHadTypeNoHTobbCtrAr};

    std::vector<UInt_t> passVBFJetBVetoTypeCtrAr {passVBFJetBVetoGenLepCtr,passVBFJetBVetoGenSemiLepCtr,passVBFJetBVetoGenHadCtr,passVBFJetBVetoGenOtherCtr};
    std::vector<UInt_t> passVBFJetBVetoTypeNoHTobbCtrAr {passVBFJetBVetoGenLepNoHTobbCtr,passVBFJetBVetoGenSemiLepNoHTobbCtr,passVBFJetBVetoGenHadNoHTobbCtr,passVBFJetBVetoGenOtherNoHTobbCtr};
    std::vector<std::vector<UInt_t>> passVBFJetBVetoHTobbCtrAr {passVBFJetBVetoTypeCtrAr,passVBFJetBVetoTypeNoHTobbCtrAr};

    std::vector<UInt_t> passVBFJetBVetoLepTypeCtrAr {passVBFJetBVetoLepGenLepCtr,passVBFJetBVetoLepGenSemiLepCtr,passVBFJetBVetoLepGenHadCtr,passVBFJetBVetoLepGenOtherCtr};
    std::vector<UInt_t> passVBFJetBVetoLepTypeNoHTobbCtrAr {passVBFJetBVetoLepGenLepNoHTobbCtr,passVBFJetBVetoLepGenSemiLepNoHTobbCtr,passVBFJetBVetoLepGenHadNoHTobbCtr,passVBFJetBVetoLepGenOtherNoHTobbCtr};
    std::vector<std::vector<UInt_t>> passVBFJetBVetoLepHTobbCtrAr {passVBFJetBVetoLepTypeCtrAr,passVBFJetBVetoLepTypeNoHTobbCtrAr};


    std::vector<UInt_t> passVBFJetBVetoSemiLepTypeCtrAr {passVBFJetBVetoSemiLepGenLepCtr,passVBFJetBVetoSemiLepGenSemiLepCtr,passVBFJetBVetoSemiLepGenHadCtr,passVBFJetBVetoSemiLepGenOtherCtr};
    std::vector<UInt_t> passVBFJetBVetoSemiLepTypeNoHTobbCtrAr {passVBFJetBVetoSemiLepGenLepNoHTobbCtr,passVBFJetBVetoSemiLepGenSemiLepNoHTobbCtr,passVBFJetBVetoSemiLepGenHadNoHTobbCtr,passVBFJetBVetoSemiLepGenOtherNoHTobbCtr};
    std::vector<std::vector<UInt_t>> passVBFJetBVetoSemiLepHTobbCtrAr {passVBFJetBVetoSemiLepTypeCtrAr,passVBFJetBVetoSemiLepTypeNoHTobbCtrAr};

    

    std::vector<UInt_t> passVBFJetBVetoHadTypeCtrAr {passVBFJetBVetoHadGenLepCtr,passVBFJetBVetoHadGenSemiLepCtr,passVBFJetBVetoHadGenHadCtr,passVBFJetBVetoHadGenOtherCtr};
    std::vector<UInt_t> passVBFJetBVetoHadTypeNoHTobbCtrAr {passVBFJetBVetoHadGenLepNoHTobbCtr,passVBFJetBVetoHadGenSemiLepNoHTobbCtr,passVBFJetBVetoHadGenHadNoHTobbCtr,passVBFJetBVetoHadGenOtherNoHTobbCtr};
    std::vector<std::vector<UInt_t>> passVBFJetBVetoHadHTobbCtrAr {passVBFJetBVetoHadTypeCtrAr,passVBFJetBVetoHadTypeNoHTobbCtrAr};

    std::vector<UInt_t> passVBFJetsTypeCtrAr {passVBFJetsGenLepCtr,passVBFJetsGenSemiLepCtr,passVBFJetsGenHadCtr,passVBFJetsGenOtherCtr};
    std::vector<UInt_t> passVBFJetsTypeNoHTobbCtrAr {passVBFJetsGenLepNoHTobbCtr,passVBFJetsGenSemiLepNoHTobbCtr,passVBFJetsGenHadNoHTobbCtr,passVBFJetsGenOtherNoHTobbCtr};
    std::vector<std::vector<UInt_t>> passVBFJetsHTobbCtrAr {passVBFJetsTypeCtrAr,passVBFJetsTypeNoHTobbCtrAr};

    std::vector<UInt_t> passAsLepTypeCtrAr {passAsLepGenLepCtr,passAsLepGenSemiLepCtr,passAsLepGenHadCtr,passAsLepGenOtherCtr};
    std::vector<UInt_t> passAsLepTypeNoHTobbCtrAr {passAsLepGenLepNoHTobbCtr,passAsLepGenSemiLepNoHTobbCtr,passAsLepGenHadNoHTobbCtr,passAsLepGenOtherNoHTobbCtr};
    std::vector<std::vector<UInt_t>> passAsLepHTobbCtrAr {passAsLepTypeCtrAr,passAsLepTypeNoHTobbCtrAr};

    std::vector<UInt_t> passAsSemiLepTypeCtrAr {passAsSemiLepGenLepCtr,passAsSemiLepGenSemiLepCtr,passAsSemiLepGenHadCtr,passAsSemiLepGenOtherCtr};
    std::vector<UInt_t> passAsSemiLepTypeNoHTobbCtrAr {passAsSemiLepGenLepNoHTobbCtr,passAsSemiLepGenSemiLepNoHTobbCtr,passAsSemiLepGenHadNoHTobbCtr,passAsSemiLepGenOtherNoHTobbCtr};
    std::vector<std::vector<UInt_t>> passAsSemiLepHTobbCtrAr {passAsSemiLepTypeCtrAr,passAsSemiLepTypeNoHTobbCtrAr};

    std::vector<UInt_t> passAsHadTypeCtrAr {passAsHadGenLepCtr,passAsHadGenSemiLepCtr,passAsHadGenHadCtr,passAsHadGenOtherCtr};
    std::vector<UInt_t> passAsHadTypeNoHTobbCtrAr {passAsHadGenLepNoHTobbCtr,passAsHadGenSemiLepNoHTobbCtr,passAsHadGenHadNoHTobbCtr,passAsHadGenOtherNoHTobbCtr};
    std::vector<std::vector<UInt_t>> passAsHadHTobbCtrAr {passAsHadTypeCtrAr,passAsHadTypeNoHTobbCtrAr};
    

    std::vector<std::vector<std::vector<UInt_t>>> ctrAr {startingHTobbCtrAr,tryingSemiLepChannelHTobbCtrAr,passEnoughFJsInSemiLepChannelHTobbCtrAr,passEnoughLepsInSemiLepChannelHTobbCtrAr,passSemiLepLepCutChannelHTobbCtrAr,passFJInSemiLepChannelHTobbCtrAr,passChannelHTobbCtrAr,passLepOrSemiLepChannelHTobbCtrAr,passLepChannelHTobbCtrAr,
    passSemiLepChannelHTobbCtrAr,passHadChannelHTobbCtrAr,passHiggsFJPreSTHTobbCtrAr,passHiggsFJPreSTLepHTobbCtrAr,passHiggsFJPreSTSemiLepHTobbCtrAr,passHiggsFJPreSTHadHTobbCtrAr,passHiggsFJHTobbCtrAr,passHiggsFJLepHTobbCtrAr,passHiggsFJSemiLepHTobbCtrAr,passHiggsFJHadHTobbCtrAr,passVBFJetBVetoHTobbCtrAr,passVBFJetBVetoLepHTobbCtrAr,passVBFJetBVetoSemiLepHTobbCtrAr,passVBFJetBVetoHadHTobbCtrAr,passVBFJetsHTobbCtrAr,passAsLepHTobbCtrAr,passAsSemiLepHTobbCtrAr,passAsHadHTobbCtrAr};

    std::vector<string> ctrNameAr {"startingHTobbCtrAr","tryingSemiLepChannelHTobbCtrAr","passEnoughFJsInSemiLepChannelHTobbCtrAr","passEnoughLepsInSemiLepChannelHTobbCtrAr","passSemiLepLepCutChannelHTobbCtrAr","passFJInSemiLepChannelHTobbCtrAr","passChannelHTobbCtrAr","passLepOrSemiLepChannelHTobbCtrAr","passLepChannelHTobbCtrAr",
    "passSemiLepChannelHTobbCtrAr","passHadChannelHTobbCtrAr","passHiggsFJPreSTHTobbCtrAr","passHiggsFJPreSTLepHTobbCtrAr","passHiggsFJPreSTSemiLepHTobbCtrAr","passHiggsFJPreSTHadHTobbCtrAr","passHiggsFJHTobbCtrAr","passHiggsFJLepHTobbCtrAr","passHiggsFJSemiLepHTobbCtrAr","passHiggsFJHadHTobbCtrAr","passVBFJetBVetoHTobbCtrAr","passVBFJetBVetoLepHTobbCtrAr","passVBFJetBVetoSemiLepHTobbCtrAr","passVBFJetBVetoHadHTobbCtrAr","passVBFJetsHTobbCtrAr","passAsLepHTobbCtrAr","passAsSemiLepHTobbCtrAr","passAsHadHTobbCtrAr"};



    std::cout << "==============================TOTAL COUNTERS==============================\n";
    
    std::cout << "startingCtr: " << startingCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "tryingSemiLepChannelCtr = " << tryingSemiLepChannelCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "passEnoughFJsInSemiLepChannelCtr = " << passEnoughFJsInSemiLepChannelCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "passEnoughLepsInSemiLepChannelCtr = " << passEnoughLepsInSemiLepChannelCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "passSemiLepLepCutCtr = " << passSemiLepLepCutCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "passFJInSemiLepChannelCtr = " << passFJInSemiLepChannelCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassChannelCtr = " << passChannelCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassLepOrSemiLepChannelCtr = " << passLepOrSemiLepChannelCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassLepChannelCtr = " << passLepChannelCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassSemiLepChannelCtr = " << passSemiLepChannelCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHadChannelCtr = " << passHadChannelCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJPreSTCtr = " << passHiggsFJPreSTCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJPreSTLepCtr = " << passHiggsFJPreSTLepCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJPreSTSemiLepCtr = " << passHiggsFJPreSTSemiLepCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJPreSTHadCtr = " << passHiggsFJPreSTHadCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJCtr = " << passHiggsFJCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJLepCtr = " << passHiggsFJLepCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJSemiLepCtr = " << passHiggsFJSemiLepCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJHadCtr = " << passHiggsFJHadCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassVBFJetBVetoCtr = " << passVBFJetBVetoCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassVBFJetBVetoLepCtr = " << passVBFJetBVetoLepCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassVBFJetBVetoSemiLepCtr = " << passVBFJetBVetoSemiLepCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassVBFJetBVetoHadCtr = " << passVBFJetBVetoHadCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassVBFJetsCtr = " << passVBFJetsCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassAsLepCtr = " << passAsLepCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassAsSemiLepCtr = " << passAsSemiLepCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassAsHadCtr = " << passAsHadCtr << "\n";
    std::cout << "------------------------\n";



    for (unsigned int ctrItr = 0; ctrItr < ctrAr.size(); ctrItr++){
        std::cout << ctrNameAr[ctrItr] << " ";
        for (unsigned int htobbItr = 0; htobbItr < htobbNameAr.size(); htobbItr++){
            for (unsigned int typeItr = 0; typeItr < typeNameAltAr.size(); typeItr++){
                std::cout << htobbNameAr[htobbItr] << " " << typeNameAltAr[typeItr] << " " << ctrAr[ctrItr][htobbItr][typeItr] << " |||| ";
                
            }
        }
        std::cout << "\n";
    }
        


    std::vector<std::vector<std::vector<std::vector<Double_t>>>> allWeightedCtrAr {startingWeightedCtrAr,
    passHiggsFJPreSTWeightedCtrAr,passHiggsFJPreSTWeightedLepCtr,passHiggsFJPreSTWeightedSemiLepCtr,passHiggsFJPreSTWeightedHadCtr,
    passHiggsFJWeightedCtrAr,passHiggsFJWeightedLepCtr,passHiggsFJWeightedSemiLepCtr,passHiggsFJWeightedHadCtr,
    passChannelWeightedCtrAr,passLepOrSemiLepChannelWeightedCtrAr,
    passLepChannelWeightedCtrAr,tryingSemiLepChannelWeightedCtrAr,passFJInSemiLepChannelWeightedCtrAr,passEnoughLepsInSemiLepChannelWeightedCtrAr,
    passEnoughFJsInSemiLepChannelWeightedCtrAr,passSemiLepLepCutWeightedCtrAr,passSemiLepChannelWeightedCtrAr,passHadChannelWeightedCtrAr,
    passVBFJetBVetoWeightedCtr,passVBFJetBVetoWeightedLepCtr,passVBFJetBVetoWeightedSemiLepCtr,passVBFJetBVetoWeightedHadCtr,
    passAsLepWeightedCtr,passAsSemiLepWeightedCtr,passAsHadWeightedCtr,passSemiLepLepCutWeightedCtr};

    std::vector<string> allWeightedNameAr {"startingWeightedCtrAr",
    "passHiggsFJPreSTWeightedCtrAr","passHiggsFJPreSTWeightedLepCtr","passHiggsFJPreSTWeightedSemiLepCtr","passHiggsFJPreSTWeightedHadCtr",
    "passHiggsFJWeightedCtrAr","passHiggsFJWeightedLepCtr","passHiggsFJWeightedSemiLepCtr","passHiggsFJWeightedHadCtr",
    "passChannelWeightedCtrAr",
    "passLepOrSemiLepChannelWeightedCtrAr","passLepChannelWeightedCtrAr",
    "tryingSemiLepChannelWeightedCtrAr",
    "passFJInSemiLepChannelWeightedCtrAr","passEnoughLepsInSemiLepChannelWeightedCtrAr","passEnoughFJsInSemiLepChannelWeightedCtrAr","passSemiLepLepCutWeightedCtrAr","passSemiLepChannelWeightedCtrAr",
    "passHadChannelWeightedCtrAr",
    "passVBFJetBVetoWeightedCtr","passVBFJetBVetoWeightedLepCtr","passVBFJetBVetoWeightedSemiLepCtr","passVBFJetBVetoWeightedHadCtr",
    "passAsLepWeightedCtr","passAsSemiLepWeightedCtr","passAsHadWeightedCtr","passSemiLepLepCutWeightedCtr"};
    for (unsigned int allItr = 0; allItr < allWeightedNameAr.size(); allItr++){
        std::cout << allWeightedNameAr[allItr] << "\n";
        for (unsigned int htobbItr = 0; htobbItr < htobbNameAr.size(); htobbItr++){
            for (unsigned int typeItr = 0; typeItr < typeNameAr.size(); typeItr++){
                std::cout << htobbNameAr[htobbItr] << " " << typeNameAr[typeItr] << "\n"; //" ctr " << startingHTobbCtrAr[htobbItr][typeItr] << " ";
                for (unsigned int loopItr = 0; loopItr < C2VNameAr.size(); loopItr++){
                    if (loopItr == C2VNameAr.size() - 1) {
                        std::cout << "(" << C2VNameAr[loopItr] << "," << allWeightedCtrAr[allItr][htobbItr][typeItr][loopItr + 1] << ")\n";
                    }
                    else std::cout << "(" << C2VNameAr[loopItr] << "," << allWeightedCtrAr[allItr][htobbItr][typeItr][loopItr + 1] << "),";
                    if (loopItr == 27) {
                        std::cout << "(2.0," << allWeightedCtrAr[allItr][htobbItr][typeItr][0] << "),";
                    }
                }
            }
        }
        std::cout << "-------------------------------\n";
    }



    outFile->cd();
    passingEvLepTree->Write("",TObject::kOverwrite);
    passingEvSemiLepTree->Write("",TObject::kOverwrite);

    outFile->Close();

}