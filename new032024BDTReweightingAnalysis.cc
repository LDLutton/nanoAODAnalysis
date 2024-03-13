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
void new032024BDTReweightingAnalysis(string datasetString, int JECCorInd, bool JECCorUpOrDown,  int RochInd, int JERInd){
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
    if (datasetString == "SDC2V2MCZZHReweightTrimmed") SDC2V2MCZZHReweightTrimmed = true;
    if (datasetString == "SDC2V2MCZZH17ReweightTrimmed") SDC2V2MCZZH17ReweightTrimmed = true;
    if (datasetString == "SDC2V2MCZZH16ReweightTrimmed") SDC2V2MCZZH16ReweightTrimmed = true;
    if (datasetString == "SDC2V2MCZZH16APVReweightTrimmed") SDC2V2MCZZH16APVReweightTrimmed = true;

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

    
    if (SDC2V2MCZZHReweightTrimmed){
        saveName = "SDC2V2MCZZHReweightTrimmed";
        //totWeight = ;
        //XS = ;
        isBackground = false;
        //std::string tmpStrWithPath = "/afs/crc.nd.edu/user/d/dlutton/Public/condorStuff/NanoAODToHistos/nanoAODAnalysis/cpp/HLTTrimmedFilteredForAnalysisSDC2V2MCZZHReweightTrimmed"+NoSLString+"_WithPreSel_0_0_0_1.root";
        std::string tmpStrWithPath = "/scratch365/dlutton/HLT022024WithPreSel/HLTTrimmedFilteredForAnalysisSDC2V2MCZZHReweightTrimmed"+NoSLString+"_WithPreSel_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root";
        //std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisSDC2V2MCZZHReweight"+NoSLString+"_WithPreSel_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2V2MCZZH17ReweightTrimmed){
        saveName = "SDC2V2MCZZH17ReweightTrimmed";
        yearType = 1;
        //totWeight = ;
        //XS = ;
        isBackground = false;
        std::string tmpStrWithPath = "/scratch365/dlutton/HLT022024WithPreSel/HLTTrimmedFilteredForAnalysisSDC2V2MCZZH17ReweightTrimmed"+NoSLString+"_WithPreSel_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root";
        //std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisSDC2V2MCZZH17Reweight"+NoSLString+"_WithPreSel_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2V2MCZZH16ReweightTrimmed){
        saveName = "SDC2V2MCZZH16ReweightTrimmed";
        yearType = 2;
        //totWeight = ;
        //XS = ;
        isBackground = false;
        std::string tmpStrWithPath = "/scratch365/dlutton/HLT022024WithPreSel/HLTTrimmedFilteredForAnalysisSDC2V2MCZZH16ReweightTrimmed"+NoSLString+"_WithPreSel_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root";
        //std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisSDC2V2MCZZH16Reweight"+NoSLString+"_WithPreSel_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2V2MCZZH16APVReweightTrimmed){
        saveName = "SDC2V2MCZZH16APVReweightTrimmed";
        yearType = 3;
        //totWeight = ;
        //XS = ;
        isBackground = false;
        std::string tmpStrWithPath = "/scratch365/dlutton/HLT022024WithPreSel/HLTTrimmedFilteredForAnalysisSDC2V2MCZZH16APVReweightTrimmed"+NoSLString+"_WithPreSel_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root";
        //std::string tmpStrWithPath = strAdd+"HLTTrimmedFilteredForAnalysisSDC2V2MCZZH16APVReweight"+NoSLString+"_WithPreSel_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (testRun){
        saveName = "testRun";
        fileAr.push_back("/scratch365/dlutton/HLT022024WithPreSel/HLTFilteredForAnalysistestRun_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        
        
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
    
    std::string outFileStr = "new032024BDTAnalysis"+saveName+"_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root";
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
    UInt_t passAsSemiLepCtr = 0;


    

    std::vector<std::string> C2VNameAr {"-2.0","-1.75","-1.5","-1.25","-1.0","-0.75","-0.5","-0.25","0.0","0.1","0.2","0.3","0.4","0.5","0.6","0.7","0.8","0.9","1.0","1.1","1.2","1.3","1.4","1.5","1.6","1.7","1.8","1.9","2.25","2.5","2.75","3.0","3.25","3.5","3.75","4.0"};
    std::vector<std::string> htobbNameAr {"HTobb","NoHTobb"};
    std::vector<std::string> typeNameAr {"","GenLep","GenSemiLep","GenHad","GenOther"};
    std::vector<std::string> typeNameAltAr {"GenLep","GenSemiLep","GenHad","GenOther"};
    std::vector<Double_t> zeroC2VVec(37,0.0);
    std::vector<std::vector<Double_t>> zeroTypeVec(5,zeroC2VVec);

    std::vector<std::vector<std::vector<Double_t>>> startingWeightedCtrAr(2,zeroTypeVec);


    std::vector<std::vector<std::vector<Double_t>>> passHiggsFJWeightedCtrAr(2,zeroTypeVec);
    std::vector<std::vector<std::vector<Double_t>>> passHiggsFJWeightedSemiLepCtr(2,zeroTypeVec);

    std::vector<std::vector<std::vector<Double_t>>> passChannelWeightedCtrAr(2,zeroTypeVec);
    std::vector<std::vector<std::vector<Double_t>>> passLepOrSemiLepChannelWeightedCtrAr(2,zeroTypeVec);

    std::vector<std::vector<std::vector<Double_t>>> tryingSemiLepChannelWeightedCtrAr(2,zeroTypeVec);
    std::vector<std::vector<std::vector<Double_t>>> passHiggsFJInSemiLepChannelWeightedCtrAr(2,zeroTypeVec);
    std::vector<std::vector<std::vector<Double_t>>> passFJInSemiLepChannelWeightedCtrAr(2,zeroTypeVec);

    std::vector<std::vector<std::vector<Double_t>>> passEnoughFJsInSemiLepChannelWeightedCtrAr(2,zeroTypeVec);
    //std::vector<std::vector<std::vector<Double_t>>> passLepCutInSemiLepChannelWeightedCtrAr(2,zeroTypeVec);
    std::vector<std::vector<std::vector<Double_t>>> passSemiLepLepCutWeightedCtrAr(2,zeroTypeVec);
    std::vector<std::vector<std::vector<Double_t>>> passSemiLepChannelWeightedCtrAr(2,zeroTypeVec);

    std::vector<std::vector<std::vector<Double_t>>> passVBFJetBVetoWeightedCtr(2,zeroTypeVec);
    std::vector<std::vector<std::vector<Double_t>>> passVBFJetBVetoWeightedSemiLepCtr(2,zeroTypeVec);

    std::vector<std::vector<std::vector<Double_t>>> passVBFJetsWeightedCtr(2,zeroTypeVec);

    std::vector<std::vector<std::vector<Double_t>>> passAsSemiLepWeightedCtr(2,zeroTypeVec);

    
    
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
    UInt_t passHiggsFJInSemiLepChannelGenLepCtr = 0;
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
    UInt_t passHiggsFJInSemiLepChannelGenSemiLepCtr = 0;
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
    UInt_t passHiggsFJInSemiLepChannelGenHadCtr = 0;
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
    UInt_t passHiggsFJInSemiLepChannelGenOtherCtr = 0;
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
    UInt_t passHiggsFJInSemiLepChannelGenLepNoHTobbCtr = 0;
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
    UInt_t passHiggsFJInSemiLepChannelGenSemiLepNoHTobbCtr = 0;
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
    UInt_t passHiggsFJInSemiLepChannelGenHadNoHTobbCtr = 0;
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
    UInt_t passHiggsFJInSemiLepChannelGenOtherNoHTobbCtr = 0;
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

        TTreeReaderValue<UInt_t> nHDecayPIDL(myEventsReader,"nHDecayPIDL");
        TTreeReaderArray<Int_t> HDecayPIDL(myEventsReader,"HDecayPIDL");
        TTreeReaderValue<UInt_t> nZOneDecayPIDL(myEventsReader,"nZOneDecayPIDL");
        TTreeReaderArray<Int_t> ZOneDecayPIDL(myEventsReader,"ZOneDecayPIDL");
        TTreeReaderValue<UInt_t> nZTwoDecayPIDL(myEventsReader,"nZTwoDecayPIDL");
        TTreeReaderArray<Int_t> ZTwoDecayPIDL(myEventsReader,"ZTwoDecayPIDL");

        TTreeReaderValue<Int_t> ZOneTypeL(myEventsReader,"ZOneTypeL");
        TTreeReaderValue<Int_t> ZTwoTypeL(myEventsReader,"ZTwoTypeL");

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

            if (debug) cout << "trying Leptonic\n";
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






                if (debug){
                    std::cout << "Pre FJC dRCheckVecAr.size() " << dRCheckVecAr.size() << "\n";
                }
                doHiggsFatJetCutBeforeZMDPNSelection(nFatJetLen,hFatJet_pt_fromHTag,hFatJet_phi_fromHTag,hFatJet_eta_fromHTag,hFatJet_mass_fromHTag,hFatJet_HTag_fromHTag,hFatJet_ind_fromHTag,FatJet_particleNetMD_QCDL,FatJet_particleNetMD_XbbL,hFatJetParticleNetCut,FatJet_pt_FinalL,hFatJetPTCut,FatJet_jetIdL,FatJet_phi_FinalL,FatJet_eta_FinalL,FatJet_mass_FinalL,dRCheckVecAr,dRCut,passedAsSemiLepLepCutBool,passedAsSemiLepHiggsCutBool);
                
                if (debug) std::cout << " found Higgs fat jet\n";


                if (passedAsSemiLepHiggsCutBool){
                    passHiggsFJInSemiLepChannelCtr += 1;

                    if (*HTobbBoolL){
                        if (*genChannelL == 0) {
                            passHiggsFJInSemiLepChannelGenLepCtr += 1;
                            //passHiggsFJInSemiLepChannelGenLepWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 1) {
                            passHiggsFJInSemiLepChannelGenSemiLepCtr += 1;
                            //passHiggsFJInSemiLepChannelGenSemiLepWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 2) {
                            passHiggsFJInSemiLepChannelGenHadCtr += 1;
                            //passHiggsFJInSemiLepChannelGenHadWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 3) {
                            passHiggsFJInSemiLepChannelGenOtherCtr += 1;
                            //passHiggsFJInSemiLepChannelGenOtherWeightedCtr += tmpGenWeights;
                        }
                    }
                    else{
                        if (*genChannelL == 0) {
                            passHiggsFJInSemiLepChannelGenLepNoHTobbCtr += 1;
                            //passHiggsFJInSemiLepChannelGenLepNoHTobbWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 1) {
                            passHiggsFJInSemiLepChannelGenSemiLepNoHTobbCtr += 1;
                            //passHiggsFJInSemiLepChannelGenSemiLepNoHTobbWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 2) {
                            passHiggsFJInSemiLepChannelGenHadNoHTobbCtr += 1;
                            //passHiggsFJInSemiLepChannelGenHadNoHTobbWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 3) {
                            passHiggsFJInSemiLepChannelGenOtherNoHTobbCtr += 1;
                            //passHiggsFJInSemiLepChannelGenOtherNoHTobbWeightedCtr += tmpGenWeights;
                        }
                    }

                    for (unsigned int maskHtobbInt = 0; maskHtobbInt < falseHtobbMask.size(); maskHtobbInt++){
                        for (unsigned int maskTypeInt = 0; maskTypeInt < falseHtobbMask[maskHtobbInt].size(); maskTypeInt++){
                            if (falseHtobbMask[maskHtobbInt][maskTypeInt]){
                                passHiggsFJInSemiLepChannelWeightedCtrAr[maskHtobbInt][maskTypeInt][0] += *genWeightL;
                                for (unsigned int C2VCtr = 1; C2VCtr < passHiggsFJInSemiLepChannelWeightedCtrAr[maskHtobbInt][maskTypeInt].size(); C2VCtr++){
                                    passHiggsFJInSemiLepChannelWeightedCtrAr[maskHtobbInt][maskTypeInt][C2VCtr] += *genWeightL*(LHEReweightingWeightL[C2VCtr-1]);
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
                doSemiLepChanFatJetCutAfterHMDPNSelection(FJInd,numFatJet,fatJetPTCut,fatJetZParticleNetCut,FatJet_pt_FinalL,FatJet_phi_FinalL,FatJet_eta_FinalL,FatJet_mass_FinalL,FatJet_particleNetMD_QCDL,FatJet_particleNetMD_XbbL,FatJet_particleNetMD_XccL,FatJet_particleNetMD_XqqL,FatJet_jetIdL,dRCheckVecAr,dRCut,hFatJet_ind_fromHTag,passedAsSemiLepHiggsCutBool,passSemiLepCut,passesCutsBool,passedAsSemiLepBool);
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
                FJIndAr.push_back(hFatJet_ind_fromHTag);
                
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
            

            if (passedAsSemiLepBool) {
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
        

            
            if (passedAsSemiLepBool) {
                passVBFJetBVetoSemiLepCtr += 1;
                if (*HTobbBoolL){
                    if (*genChannelL == 0) {
                        passVBFJetBVetoSemiLepGenLepCtr += 1;
                    }
                    if (*genChannelL == 1) {
                        passVBFJetBVetoSemiLepGenSemiLepCtr += 1;
                    }
                    if (*genChannelL == 2) {
                        passVBFJetBVetoSemiLepGenHadCtr += 1;
                    }
                    if (*genChannelL == 3) {
                        passVBFJetBVetoSemiLepGenOtherCtr += 1;
                    }
                }
                else {
                    if (*genChannelL == 0) {
                        passVBFJetBVetoSemiLepGenLepNoHTobbCtr += 1;
                    }
                    if (*genChannelL == 1) {
                        passVBFJetBVetoSemiLepGenSemiLepNoHTobbCtr += 1;
                    }
                    if (*genChannelL == 2) {
                        passVBFJetBVetoSemiLepGenHadNoHTobbCtr += 1;
                    }
                    if (*genChannelL == 3) {
                        passVBFJetBVetoSemiLepGenOtherNoHTobbCtr += 1;
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
                    UInt_t tmpJetPt = Jet_pt_FinalL[nJetItr];
                    //Jet_etaL[nJetItr]
                    Int_t tmpJetId = Jet_jetIdL[nJetItr];
                    if (tmpJetPt < 30 || !(tmpJetId == 6)) continue;
                    tmpnAK4JetsPassing += 1;

                
                }
            

                if (passedAsSemiLepBool){


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


                        

                        goodGenZFJMatch_SL_L = *goodGenZFJMatchL;
                        goodGenHFJMatch_SL_L = *goodGenHFJMatchL;
                        goodZFJMatchToGen_SL_L = *goodZFJMatchToGenL;
                        goodHFJMatchToGen_SL_L = *goodHFJMatchToGenL;
                        eventGenSemileptonic_SL_L = *eventGenSemileptonicL;
                        eventGenHToBB_SL_L = *eventGenHToBBL;
                        ZFJGenHadronFlavour_SL_L = *ZFJGenHadronFlavourL;
                        HFJGenHadronFlavour_SL_L = *HFJGenHadronFlavourL;
                        FatJet_hadronFlavour_SL_L =  FatJet_hadronFlavourL[FJIndAr[0]];

                        firstHToBBBool_SL_L = *HTobbBoolL;

                        ZOneType_SL_L = *ZOneTypeL;
                        ZTwoType_SL_L = *ZTwoTypeL;

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
                        
                        nHDecayPID_SL_L = *nHDecayPIDL;
                        for (UInt_t HDecayItr=0; HDecayItr<*nHDecayPIDL;HDecayItr++){
                            HDecayPID_SL_L.push_back(HDecayPIDL[HDecayItr]);
                        }

                        nZOneDecayPID_SL_L = *nZOneDecayPIDL;
                        for (UInt_t ZDecayItr=0; ZDecayItr<*nZOneDecayPIDL;ZDecayItr++){
                            ZOneDecayPID_SL_L.push_back(ZOneDecayPIDL[ZDecayItr]);
                        }

                        nZTwoDecayPID_SL_L = *nZTwoDecayPIDL;
                        for (UInt_t ZDecayItr=0; ZDecayItr<*nZTwoDecayPIDL;ZDecayItr++){
                            ZTwoDecayPID_SL_L.push_back(ZTwoDecayPIDL[ZDecayItr]);
                        }





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

                    }





                    if (*HTobbBoolL){
                        if (*genChannelL == 0) {
                            passAsSemiLepGenLepCtr += 1;
                        }
                        if (*genChannelL == 1) {
                            passAsSemiLepGenSemiLepCtr += 1;
                            //Fill BDT SemiLep Tree
                            if (BDTSignalGenChannelMatched){

                                //EventCor/UncInds
                                JECCorInd_SL_L = JECCorInd;
                                JECCorUpOrDown_SL_L = JECCorUpOrDown;
                                RochInd_SL_L = RochInd;
                                JERInd_SL_L = JERInd;

                                passingEvGenWeight_SL_L = tmpGenWeights;

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


                                goodGenZFJMatch_SL_L = *goodGenZFJMatchL;
                                goodGenHFJMatch_SL_L = *goodGenHFJMatchL;
                                goodZFJMatchToGen_SL_L = *goodZFJMatchToGenL;
                                goodHFJMatchToGen_SL_L = *goodHFJMatchToGenL;
                                eventGenSemileptonic_SL_L = *eventGenSemileptonicL;
                                eventGenHToBB_SL_L = *eventGenHToBBL;
                                ZFJGenHadronFlavour_SL_L = *ZFJGenHadronFlavourL;
                                HFJGenHadronFlavour_SL_L = *HFJGenHadronFlavourL;
                                FatJet_hadronFlavour_SL_L =  FatJet_hadronFlavourL[FJIndAr[0]];

                                firstHToBBBool_SL_L = *HTobbBoolL;

                                ZOneType_SL_L = *ZOneTypeL;
                                ZTwoType_SL_L = *ZTwoTypeL;


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

                                nHDecayPID_SL_L = *nHDecayPIDL;
                                for (UInt_t HDecayItr=0; HDecayItr<*nHDecayPIDL;HDecayItr++){
                                    HDecayPID_SL_L.push_back(HDecayPIDL[HDecayItr]);
                                }

                                nZOneDecayPID_SL_L = *nZOneDecayPIDL;
                                for (UInt_t ZDecayItr=0; ZDecayItr<*nZOneDecayPIDL;ZDecayItr++){
                                    ZOneDecayPID_SL_L.push_back(ZOneDecayPIDL[ZDecayItr]);
                                }

                                nZTwoDecayPID_SL_L = *nZTwoDecayPIDL;
                                for (UInt_t ZDecayItr=0; ZDecayItr<*nZTwoDecayPIDL;ZDecayItr++){
                                    ZTwoDecayPID_SL_L.push_back(ZTwoDecayPIDL[ZDecayItr]);
                                }


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

                            }





                        }
                        if (*genChannelL == 2) {
                            passAsSemiLepGenHadCtr += 1;
                        }
                        if (*genChannelL == 3) {
                            passAsSemiLepGenOtherCtr += 1;
                        }
                    }
                    else {
                        if (*genChannelL == 0) {
                            passAsSemiLepGenLepNoHTobbCtr += 1;
                        }
                        if (*genChannelL == 1) {
                            passAsSemiLepGenSemiLepNoHTobbCtr += 1;
                        }
                        if (*genChannelL == 2) {
                            passAsSemiLepGenHadNoHTobbCtr += 1;
                        }
                        if (*genChannelL == 3) {
                            passAsSemiLepGenOtherNoHTobbCtr += 1;
                        }
                    }
                
                    

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

    std::vector<UInt_t> passHiggsFJInSemiLepChannelTypeCtrAr {passHiggsFJInSemiLepChannelGenLepCtr,passHiggsFJInSemiLepChannelGenSemiLepCtr,passHiggsFJInSemiLepChannelGenHadCtr,passHiggsFJInSemiLepChannelGenOtherCtr};
    std::vector<UInt_t> passHiggsFJInSemiLepChannelTypeNoHTobbCtrAr {passHiggsFJInSemiLepChannelGenLepNoHTobbCtr,passHiggsFJInSemiLepChannelGenSemiLepNoHTobbCtr,passHiggsFJInSemiLepChannelGenHadNoHTobbCtr,passHiggsFJInSemiLepChannelGenOtherNoHTobbCtr};
    std::vector<std::vector<UInt_t>> passHiggsFJInSemiLepChannelHTobbCtrAr {passHiggsFJInSemiLepChannelTypeCtrAr,passHiggsFJInSemiLepChannelTypeNoHTobbCtrAr};

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
    

    std::vector<std::vector<std::vector<UInt_t>>> ctrAr {startingHTobbCtrAr,tryingSemiLepChannelHTobbCtrAr,passEnoughFJsInSemiLepChannelHTobbCtrAr,passEnoughLepsInSemiLepChannelHTobbCtrAr,passSemiLepLepCutChannelHTobbCtrAr,passHiggsFJInSemiLepChannelHTobbCtrAr,passFJInSemiLepChannelHTobbCtrAr,passChannelHTobbCtrAr,passLepOrSemiLepChannelHTobbCtrAr,passLepChannelHTobbCtrAr,
    passSemiLepChannelHTobbCtrAr,passHadChannelHTobbCtrAr,passHiggsFJPreSTHTobbCtrAr,passHiggsFJPreSTLepHTobbCtrAr,passHiggsFJPreSTSemiLepHTobbCtrAr,passHiggsFJPreSTHadHTobbCtrAr,passHiggsFJHTobbCtrAr,passHiggsFJLepHTobbCtrAr,passHiggsFJSemiLepHTobbCtrAr,passHiggsFJHadHTobbCtrAr,passVBFJetBVetoHTobbCtrAr,passVBFJetBVetoLepHTobbCtrAr,passVBFJetBVetoSemiLepHTobbCtrAr,passVBFJetBVetoHadHTobbCtrAr,passVBFJetsHTobbCtrAr,passAsLepHTobbCtrAr,passAsSemiLepHTobbCtrAr,passAsHadHTobbCtrAr};

    std::vector<string> ctrNameAr {"startingHTobbCtrAr","tryingSemiLepChannelHTobbCtrAr","passEnoughFJsInSemiLepChannelHTobbCtrAr","passEnoughLepsInSemiLepChannelHTobbCtrAr","passSemiLepLepCutChannelHTobbCtrAr","passHiggsFJInSemiLepChannelHTobbCtrAr","passFJInSemiLepChannelHTobbCtrAr","passChannelHTobbCtrAr","passLepOrSemiLepChannelHTobbCtrAr","passLepChannelHTobbCtrAr",
    "passSemiLepChannelHTobbCtrAr","passHadChannelHTobbCtrAr","passHiggsFJPreSTHTobbCtrAr","passHiggsFJPreSTLepHTobbCtrAr","passHiggsFJPreSTSemiLepHTobbCtrAr","passHiggsFJPreSTHadHTobbCtrAr","passHiggsFJHTobbCtrAr","passHiggsFJLepHTobbCtrAr","passHiggsFJSemiLepHTobbCtrAr","passHiggsFJHadHTobbCtrAr","passVBFJetBVetoHTobbCtrAr","passVBFJetBVetoLepHTobbCtrAr","passVBFJetBVetoSemiLepHTobbCtrAr","passVBFJetBVetoHadHTobbCtrAr","passVBFJetsHTobbCtrAr","passAsLepHTobbCtrAr","passAsSemiLepHTobbCtrAr","passAsHadHTobbCtrAr"};



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
    std::cout << "UInt_t " << saveName << "PassAsSemiLepCtr = " << passAsSemiLepCtr << "\n";
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
    passHiggsFJWeightedCtrAr,passHiggsFJWeightedSemiLepCtr,
    passChannelWeightedCtrAr,passLepOrSemiLepChannelWeightedCtrAr,
    tryingSemiLepChannelWeightedCtrAr,passHiggsFJInSemiLepChannelWeightedCtrAr,passFJInSemiLepChannelWeightedCtrAr,
    passEnoughFJsInSemiLepChannelWeightedCtrAr,passSemiLepLepCutWeightedCtrAr,passSemiLepChannelWeightedCtrAr,
    passVBFJetBVetoWeightedCtr,passVBFJetBVetoWeightedSemiLepCtr,
    passAsSemiLepWeightedCtr};

    std::vector<string> allWeightedNameAr {"startingWeightedCtrAr",
    "passHiggsFJWeightedCtrAr","passHiggsFJWeightedSemiLepCtr",
    "passChannelWeightedCtrAr",
    "passLepOrSemiLepChannelWeightedCtrAr",
    "tryingSemiLepChannelWeightedCtrAr",
    "passHiggsFJInSemiLepChannelWeightedCtrAr","passFJInSemiLepChannelWeightedCtrAr","passEnoughFJsInSemiLepChannelWeightedCtrAr","passSemiLepLepCutWeightedCtrAr","passSemiLepChannelWeightedCtrAr",
    "passVBFJetBVetoWeightedCtr","passVBFJetBVetoWeightedSemiLepCtr",
    "passAsSemiLepWeightedCtr"};
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
    passingEvSemiLepTree->Write("",TObject::kOverwrite);
    //btagEffTree->Write("",TObject::kOverwrite);

    outFile->Close();

}