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


void new072022BDTAnalysis(string datasetString){
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
    if (datasetString == "SDC2V3MC") SDC2V3MC = true;
    if (datasetString == "SDC2Vm2p5MC") SDC2Vm2p5MC = true;
    if (datasetString == "SDC2Vm2MC") SDC2Vm2MC = true;
    if (datasetString == "SDC2Vm1MC") SDC2Vm1MC = true;
    if (datasetString == "SDC2V0MC") SDC2V0MC = true;
    if (datasetString == "SDC2V1MC") SDC2V1MC = true;
    if (datasetString == "SDC2V4MC") SDC2V4MC = true;
    if (datasetString == "SDC2V4p5MC") SDC2V4p5MC = true;
    
    if (datasetString == "SDC2V3MCV2") SDC2V3MCV2 = true;
    if (datasetString == "SDC2Vm2p5MCV2") SDC2Vm2p5MCV2 = true;
    if (datasetString == "SDC2Vm2MCV2") SDC2Vm2MCV2 = true;
    if (datasetString == "SDC2Vm1MCV2") SDC2Vm1MCV2 = true;
    if (datasetString == "SDC2V0MCV2") SDC2V0MCV2 = true;
    if (datasetString == "SDC2V1MCV2") SDC2V1MCV2 = true;
    if (datasetString == "SDC2V4MCV2") SDC2V4MCV2 = true;
    if (datasetString == "SDC2V4p5MCV2") SDC2V4p5MCV2 = true;

    if (datasetString == "SDC2V3MCWZHV2") SDC2V3MCWZHV2 = true;
    if (datasetString == "SDC2Vm2p5MCWZHV2") SDC2Vm2p5MCWZHV2 = true;
    if (datasetString == "SDC2Vm3MCWZHV2") SDC2Vm3MCWZHV2 = true;
    if (datasetString == "SDC2Vm1MCWZHV2") SDC2Vm1MCWZHV2 = true;
    if (datasetString == "SDC2V0MCWZHV2") SDC2V0MCWZHV2 = true;
    if (datasetString == "SDC2V1MCWZHV2") SDC2V1MCWZHV2 = true;
    if (datasetString == "SDC2V4MCWZHV2") SDC2V4MCWZHV2 = true;
    if (datasetString == "SDC2V5MCWZHV2") SDC2V5MCWZHV2 = true;


    if (datasetString == "C2VEtaDifCut") MGC2VEtaDifCut = true;
    if (datasetString == "OSix") MGOSix = true;
    if (datasetString == "OSixEtaDifCut") MGOSixEtaDifCut = true;
    if (datasetString == "OHBox") MGOHBox = true;
    if (datasetString == "OHBoxEtaDifCut") MGOHBoxEtaDifCut = true;
    if (datasetString == "OHDD") MGOHDD = true;
    if (datasetString == "OHDDEtaDifCut") MGOHDDEtaDifCut = true;
    if (datasetString == "OHW") MGOHW = true;
    if (datasetString == "SM") MGSM = true;

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
        XS = 0.0029534660375063228;
        datasetType = 0;
        isBackground = false;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisSDC2V3MC.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2Vm2p5MC){
        saveName = "SDC2Vm2p5MC";
        totWeight = 5438.886;
        XS = 0.00870572774942857;
        datasetType = 0;
        isBackground = false;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisSDC2Vm2p5MC.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2Vm2MC){
        saveName = "SDC2Vm2MC";
        totWeight = 3995.7870000000003;
        XS = 0.00639583800188236;
        datasetType = 0;
        isBackground = false;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisSDC2Vm2MC.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2Vm1MC){
        saveName = "SDC2Vm1MC";
        totWeight = 1807.3179999999995;
        XS = 0.0028928659463785507;
        datasetType = 0;
        isBackground = false;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisSDC2Vm1MC.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2V0MC){
        saveName = "SDC2V0MC";
        totWeight = 494.6163;
        XS = 0.0007917027611044418;
        datasetType = 0;
        isBackground = false;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisSDC2V0MC.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2V1MC){
        saveName = "SDC2V1MC";
        totWeight = 64.51377;
        XS = 0.00010119807058823528;
        datasetType = 0;
        isBackground = false;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisSDC2V1MC.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2V4MC){
        saveName = "SDC2V4MC";
        totWeight = 4076.6;
        XS = 0.006525170068027211;
        datasetType = 0;
        isBackground = false;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisSDC2V4MC.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2V4p5MC){
        saveName = "SDC2V4p5MC";
        totWeight = 5512.316000000001;
        XS = 0.008823234893957584;
        datasetType = 0;
        isBackground = false;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisSDC2V4p5MC.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2V3MCV2){
        saveName = "SDC2V3MCV2";
        totWeight = 1896.1953;
        XS = 4.24E-3;
        //XS = 0.0029535844348424762;
        datasetType = 0;
        isBackground = false;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisSDC2V3MCV2.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2Vm2p5MCV2){
        saveName = "SDC2Vm2p5MCV2";
        totWeight = 5467.7935;
        XS = 1.242E-2;
        //XS = 0.008265774802040217;
        datasetType = 0;
        isBackground = false;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisSDC2Vm2p5MCV2.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2Vm2MCV2){
        saveName = "SDC2Vm2MCV2";
        totWeight = 3869.629;
        XS = 9.16E-3;
        //XS = 0.006398746254638295;
        datasetType = 0;
        isBackground = false;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisSDC2Vm2MCV2.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2Vm1MCV2){
        saveName = "SDC2Vm1MCV2";
        totWeight = 1856.9267999999995;
        XS = 4.13E-3;
        //XS = 0.002893536112193221;
        datasetType = 0;
        isBackground = false;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisSDC2Vm1MCV2.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2V0MCV2){
        saveName = "SDC2V0MCV2";
        totWeight = 510.37219999999996;
        XS = 1.13E-3;
        //XS = 0.0007918885958107059;
        datasetType = 0;
        isBackground = false;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisSDC2V0MCV2.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2V1MCV2){
        saveName = "SDC2V1MCV2";
        totWeight = 64.988248;
        XS = 1.5E-4;
        //XS = 0.00010118839704165045;
        datasetType = 0;
        isBackground = false;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisSDC2V1MCV2.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2V4MCV2){
        saveName = "SDC2V4MCV2";
        totWeight = 3956.4910000000004;
        XS = 9.32E-3;
        //XS = 0.006526170721649485;
        datasetType = 0;
        isBackground = false;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisSDC2V4MCV2.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2V4p5MCV2){
        saveName = "SDC2V4p5MCV2";
        totWeight = 5698.066000000001;
        XS = 1.261E-2;
        //XS = 0.00882395044521874;
        datasetType = 0;
        isBackground = false;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisSDC2V4p5MCV2.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2V3MCWZHV2){
        saveName = "SDC2V3MCWZHV2";
        totWeight = 2307.0611;
        XS = 5.37E-3;
        //XS = 0.0035740683191324554;
        datasetType = 25;
        isBackground = false;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisSDC2V3MCWZHV2.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2Vm2p5MCWZHV2){
        saveName = "SDC2Vm2p5MCWZHV2";
        totWeight = 6336.808999999999;
        XS = 1.451E-2;
        //XS = 0.009874264121542655;
        datasetType = 25;
        isBackground = false;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisSDC2Vm2p5MCWZHV2.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2Vm3MCWZHV2){
        saveName = "SDC2Vm3MCWZHV2";
        totWeight = 7799.2880000000005;
        XS = 1.881E-2;
        //XS = 0.012859502061005772;
        datasetType = 25;
        isBackground = false;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisSDC2Vm3MCWZHV2.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2Vm1MCWZHV2){
        saveName = "SDC2Vm1MCWZHV2";
        totWeight = 2203.4332000000004;
        XS = 5.08E-3;
        //XS = 0.0034321549789173476;
        datasetType = 25;
        isBackground = false;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisSDC2Vm1MCWZHV2.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2V0MCWZHV2){
        saveName = "SDC2V0MCWZHV2";
        totWeight = 672.6487999999999;
        XS = 1.68E-3;
        //XS = 0.0011072408230452674;
        datasetType = 25;
        isBackground = false;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisSDC2V0MCWZHV2.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2V1MCWZHV2){
        saveName = "SDC2V1MCWZHV2";
        totWeight = 237.60372;
        XS = 6.0E-4;
        //XS = 0.0003700992523364486;
        datasetType = 25;
        isBackground = false;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisSDC2V1MCWZHV2.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2V4MCWZHV2){
        saveName = "SDC2V4MCWZHV2";
        totWeight = 4890.388999999999;
        XS = 1.123E-2;
        //XS = 0.0076115240825652365;
        datasetType = 25;
        isBackground = false;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisSDC2V4MCWZHV2.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2V5MCWZHV2){
        saveName = "SDC2V5MCWZHV2";
        totWeight = 8465.52;
        XS = 1.940E-2;
        //XS = 0.013140136810456827;
        datasetType = 25;
        isBackground = false;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisSDC2V5MCWZHV2.root";
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
        
        
    }
    else if (MGOSixEtaDifCut){
        saveName = "OSix_EtaDifCut";
        isBackground = false;
        int arrSize = sizeof(MGOSixEtaDifCutAr)/sizeof(MGOSixEtaDifCutAr[0]);
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisOSix_EtaDifCut.root";
            fileAr.push_back(tmpStrWithPath);
        }
        
        
    }
    else if (MGOHBox){
        saveName = "OHBox";
        isBackground = false;
        int arrSize = sizeof(MGOHBoxAr)/sizeof(MGOHBoxAr[0]);
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisOHBox.root";
            fileAr.push_back(tmpStrWithPath);
        }
        
        
        
    }
    else if (MGOHBoxEtaDifCut){
        saveName = "OHBox_EtaDifCut";
        isBackground = false;
        int arrSize = sizeof(MGOHBoxEtaDifCutAr)/sizeof(MGOHBoxEtaDifCutAr[0]);
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisOHBox_EtaDifCut.root";
            fileAr.push_back(tmpStrWithPath);
        }
        
        
        
    }
    else if (MGOHDD){
        saveName = "OHDD";
        isBackground = false;
        int arrSize = sizeof(MGOHDDAr)/sizeof(MGOHDDAr[0]);
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisOHDD.root";
            fileAr.push_back(tmpStrWithPath);
        }
        
        
        
    }
    else if (MGOHDDEtaDifCut){
        saveName = "OHDD_EtaDifCut";
        isBackground = false;
        int arrSize = sizeof(MGOHDDEtaDifCutAr)/sizeof(MGOHDDEtaDifCutAr[0]);
        for (int i=0; i<arrSize; i++){
            std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisOHDD_EtaDifCut.root";
            fileAr.push_back(tmpStrWithPath);
        }
        
        
        
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
        XS = 8.37711e-05*0.5772683;
        datasetType = 1;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisSM.root";
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
    
    std::string outFileStr = "new072022BDTAnalysis"+saveName+".root";
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

    Double_t startingWeightedCtr = 0;
    

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
    Double_t tryingSemiLepChannelWeightedCtr = 0;
    Double_t passFJInSemiLepChannelWeightedCtr = 0;
    Double_t passEnoughLepsInSemiLepChannelWeightedCtr = 0;
    Double_t passEnoughFJsInSemiLepChannelWeightedCtr = 0;
    Double_t passLepCutInSemiLepChannelWeightedCtr = 0;
    Double_t passSemiLepChannelWeightedCtr = 0.;
    Double_t passHadChannelWeightedCtr = 0.;
    Double_t passVBFJetBVetoWeightedCtr = 0;
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
    
    Double_t startingGenLepWeightedCtr = 0;

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
    Double_t tryingSemiLepChannelGenLepWeightedCtr = 0;
    Double_t passFJInSemiLepChannelGenLepWeightedCtr = 0;
    Double_t passEnoughLepsInSemiLepChannelGenLepWeightedCtr = 0;
    Double_t passEnoughFJsInSemiLepChannelGenLepWeightedCtr = 0;
    Double_t passLepCutInSemiLepChannelGenLepWeightedCtr = 0;
    Double_t passSemiLepChannelGenLepWeightedCtr = 0.;
    Double_t passHadChannelGenLepWeightedCtr = 0.;
    Double_t passVBFJetBVetoGenLepWeightedCtr = 0;
    Double_t passVBFJetBVetoWeightedLepGenLepCtr = 0.;
    Double_t passVBFJetBVetoWeightedSemiLepGenLepCtr = 0.;
    Double_t passVBFJetBVetoWeightedHadGenLepCtr = 0.;
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

    Double_t startingGenSemiLepWeightedCtr = 0;

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
    Double_t tryingSemiLepChannelGenSemiLepWeightedCtr = 0;
    Double_t passFJInSemiLepChannelGenSemiLepWeightedCtr = 0;
    Double_t passEnoughLepsInSemiLepChannelGenSemiLepWeightedCtr = 0;
    Double_t passEnoughFJsInSemiLepChannelGenSemiLepWeightedCtr = 0;
    Double_t passLepCutInSemiLepChannelGenSemiLepWeightedCtr = 0;
    Double_t passSemiLepChannelGenSemiLepWeightedCtr = 0.;
    Double_t passHadChannelGenSemiLepWeightedCtr = 0.;
    Double_t passVBFJetBVetoGenSemiLepWeightedCtr = 0;
    Double_t passVBFJetBVetoWeightedLepGenSemiLepCtr = 0.;
    Double_t passVBFJetBVetoWeightedSemiLepGenSemiLepCtr = 0.;
    Double_t passVBFJetBVetoWeightedHadGenSemiLepCtr = 0.;
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
    
    Double_t startingGenHadWeightedCtr = 0;

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
    Double_t tryingSemiLepChannelGenHadWeightedCtr = 0;
    Double_t passFJInSemiLepChannelGenHadWeightedCtr = 0;
    Double_t passEnoughLepsInSemiLepChannelGenHadWeightedCtr = 0;
    Double_t passEnoughFJsInSemiLepChannelGenHadWeightedCtr = 0;
    Double_t passLepCutInSemiLepChannelGenHadWeightedCtr = 0;
    Double_t passSemiLepChannelGenHadWeightedCtr = 0.;
    Double_t passHadChannelGenHadWeightedCtr = 0.;
    Double_t passVBFJetBVetoGenHadWeightedCtr = 0;
    Double_t passVBFJetBVetoWeightedLepGenHadCtr = 0.;
    Double_t passVBFJetBVetoWeightedSemiLepGenHadCtr = 0.;
    Double_t passVBFJetBVetoWeightedHadGenHadCtr = 0.;
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
    
    Double_t startingGenOtherWeightedCtr = 0;

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
    Double_t tryingSemiLepChannelGenOtherWeightedCtr = 0;
    Double_t passFJInSemiLepChannelGenOtherWeightedCtr = 0;
    Double_t passEnoughLepsInSemiLepChannelGenOtherWeightedCtr = 0;
    Double_t passEnoughFJsInSemiLepChannelGenOtherWeightedCtr = 0;
    Double_t passLepCutInSemiLepChannelGenOtherWeightedCtr = 0;
    Double_t passSemiLepChannelGenOtherWeightedCtr = 0.;
    Double_t passHadChannelGenOtherWeightedCtr = 0.;
    Double_t passVBFJetBVetoGenOtherWeightedCtr = 0;
    Double_t passVBFJetBVetoWeightedLepGenOtherCtr = 0.;
    Double_t passVBFJetBVetoWeightedSemiLepGenOtherCtr = 0.;
    Double_t passVBFJetBVetoWeightedHadGenOtherCtr = 0.;
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
    
    Double_t startingGenLepNoHTobbWeightedCtr = 0;

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
    Double_t tryingSemiLepChannelGenLepNoHTobbWeightedCtr = 0;
    Double_t passFJInSemiLepChannelGenLepNoHTobbWeightedCtr = 0;
    Double_t passEnoughLepsInSemiLepChannelGenLepNoHTobbWeightedCtr = 0;
    Double_t passEnoughFJsInSemiLepChannelGenLepNoHTobbWeightedCtr = 0;
    Double_t passLepCutInSemiLepChannelGenLepNoHTobbWeightedCtr = 0;
    Double_t passSemiLepChannelGenLepNoHTobbWeightedCtr = 0.;
    Double_t passHadChannelGenLepNoHTobbWeightedCtr = 0.;
    Double_t passVBFJetBVetoGenLepNoHTobbWeightedCtr = 0;
    Double_t passVBFJetBVetoWeightedLepGenLepNoHTobbCtr = 0.;
    Double_t passVBFJetBVetoWeightedSemiLepGenLepNoHTobbCtr = 0.;
    Double_t passVBFJetBVetoWeightedHadGenLepNoHTobbCtr = 0.;
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
    
    Double_t startingGenSemiLepNoHTobbWeightedCtr = 0;

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
    Double_t tryingSemiLepChannelGenSemiLepNoHTobbWeightedCtr = 0;
    Double_t passFJInSemiLepChannelGenSemiLepNoHTobbWeightedCtr = 0;
    Double_t passEnoughLepsInSemiLepChannelGenSemiLepNoHTobbWeightedCtr = 0;
    Double_t passEnoughFJsInSemiLepChannelGenSemiLepNoHTobbWeightedCtr = 0;
    Double_t passLepCutInSemiLepChannelGenSemiLepNoHTobbWeightedCtr = 0;
    Double_t passSemiLepChannelGenSemiLepNoHTobbWeightedCtr = 0.;
    Double_t passHadChannelGenSemiLepNoHTobbWeightedCtr = 0.;
    Double_t passVBFJetBVetoGenSemiLepNoHTobbWeightedCtr = 0;
    Double_t passVBFJetBVetoWeightedLepGenSemiLepNoHTobbCtr = 0.;
    Double_t passVBFJetBVetoWeightedSemiLepGenSemiLepNoHTobbCtr = 0.;
    Double_t passVBFJetBVetoWeightedHadGenSemiLepNoHTobbCtr = 0.;
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
    
    Double_t startingGenHadNoHTobbWeightedCtr = 0;

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
    Double_t tryingSemiLepChannelGenHadNoHTobbWeightedCtr = 0;
    Double_t passFJInSemiLepChannelGenHadNoHTobbWeightedCtr = 0;
    Double_t passEnoughLepsInSemiLepChannelGenHadNoHTobbWeightedCtr = 0;
    Double_t passEnoughFJsInSemiLepChannelGenHadNoHTobbWeightedCtr = 0;
    Double_t passLepCutInSemiLepChannelGenHadNoHTobbWeightedCtr = 0;
    Double_t passSemiLepChannelGenHadNoHTobbWeightedCtr = 0.;
    Double_t passHadChannelGenHadNoHTobbWeightedCtr = 0.;
    Double_t passVBFJetBVetoGenHadNoHTobbWeightedCtr = 0;
    Double_t passVBFJetBVetoWeightedLepGenHadNoHTobbCtr = 0.;
    Double_t passVBFJetBVetoWeightedSemiLepGenHadNoHTobbCtr = 0.;
    Double_t passVBFJetBVetoWeightedHadGenHadNoHTobbCtr = 0.;
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
    
    Double_t startingGenOtherNoHTobbWeightedCtr = 0;

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
    Double_t tryingSemiLepChannelGenOtherNoHTobbWeightedCtr = 0;
    Double_t passFJInSemiLepChannelGenOtherNoHTobbWeightedCtr = 0;
    Double_t passEnoughLepsInSemiLepChannelGenOtherNoHTobbWeightedCtr = 0;
    Double_t passEnoughFJsInSemiLepChannelGenOtherNoHTobbWeightedCtr = 0;
    Double_t passLepCutInSemiLepChannelGenOtherNoHTobbWeightedCtr = 0;
    Double_t passSemiLepChannelGenOtherNoHTobbWeightedCtr = 0.;
    Double_t passHadChannelGenOtherNoHTobbWeightedCtr = 0.;
    Double_t passVBFJetBVetoGenOtherNoHTobbWeightedCtr = 0;
    Double_t passVBFJetBVetoWeightedLepGenOtherNoHTobbCtr = 0.;
    Double_t passVBFJetBVetoWeightedSemiLepGenOtherNoHTobbCtr = 0.;
    Double_t passVBFJetBVetoWeightedHadGenOtherNoHTobbCtr = 0.;
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

    Float_t selectedHiggsFJ_pt_L_L;
    Float_t selectedHiggsFJ_eta_L_L;
    Float_t selectedHiggsFJ_ParticleNet_HbbvsQCD_L_L;

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

    passingEvLepTree->Branch("selectedHiggsFJ_pt_L_L",&selectedHiggsFJ_pt_L_L,"selectedHiggsFJ_pt_L_L/F");
    passingEvLepTree->Branch("selectedHiggsFJ_eta_L_L",&selectedHiggsFJ_eta_L_L,"selectedHiggsFJ_eta_L_L/F");
    passingEvLepTree->Branch("selectedHiggsFJ_ParticleNet_HbbvsQCD_L_L",&selectedHiggsFJ_ParticleNet_HbbvsQCD_L_L,"selectedHiggsFJ_ParticleNet_HbbvsQCD_L_L/F");

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

    Float_t selectedHiggsFJ_pt_SL_L;
    Float_t selectedHiggsFJ_eta_SL_L;
    Float_t selectedHiggsFJ_ParticleNet_HbbvsQCD_SL_L;
    Float_t selectedZFJ_pt_SL_L;
    Float_t selectedZFJ_eta_SL_L;
    Float_t selectedZFJ_ParticleNet_ZvsQCD_SL_L;

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

    passingEvSemiLepTree->Branch("selectedHiggsFJ_pt_SL_L",&selectedHiggsFJ_pt_SL_L,"selectedHiggsFJ_pt_SL_L/F");
    passingEvSemiLepTree->Branch("selectedHiggsFJ_eta_SL_L",&selectedHiggsFJ_eta_SL_L,"selectedHiggsFJ_eta_SL_L/F");
    passingEvSemiLepTree->Branch("selectedHiggsFJ_ParticleNet_HbbvsQCD_SL_L",&selectedHiggsFJ_ParticleNet_HbbvsQCD_SL_L,"selectedHiggsFJ_ParticleNet_HbbvsQCD_SL_L/F");
    passingEvSemiLepTree->Branch("selectedZFJ_pt_SL_L",&selectedZFJ_pt_SL_L,"selectedZFJ_pt_SL_L/F");
    passingEvSemiLepTree->Branch("selectedZFJ_eta_SL_L",&selectedZFJ_eta_SL_L,"selectedZFJ_eta_SL_L/F");
    passingEvSemiLepTree->Branch("selectedZFJ_ParticleNet_ZvsQCD_SL_L",&selectedZFJ_ParticleNet_ZvsQCD_SL_L,"selectedZFJ_ParticleNet_ZvsQCD_SL_L/F");

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
            
                passLepChannelCtr += 1;
                passLepChannelWeightedCtr += tmpGenWeights;
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
                
                passLepOrSemiLepChannelCtr += 1;
                passLepOrSemiLepChannelWeightedCtr += tmpGenWeights;
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
            if ((!passesCutsBool)){
                dRCheckVecAr.clear();
                std::vector<Float_t> SemiLepInvMass;
                
                if (debug) std::cout << "trying SemiLeptonic\n";
                tryingSemiLepChannelCtr += 1;
                tryingSemiLepChannelWeightedCtr += tmpGenWeights;
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
                    if (*HTobbBoolL){
                        if (*genChannelL == 0) {
                            passEnoughFJsInSemiLepChannelGenLepCtr += 1;
                            passEnoughFJsInSemiLepChannelGenLepWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 1) {
                            passEnoughFJsInSemiLepChannelGenSemiLepCtr += 1;
                            passEnoughFJsInSemiLepChannelGenSemiLepWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 2) {
                            passEnoughFJsInSemiLepChannelGenHadCtr += 1;
                            passEnoughFJsInSemiLepChannelGenHadWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 3) {
                            passEnoughFJsInSemiLepChannelGenOtherCtr += 1;
                            passEnoughFJsInSemiLepChannelGenOtherWeightedCtr += tmpGenWeights;
                        }
                    }
                    else {
                        if (*genChannelL == 0) {
                            passEnoughFJsInSemiLepChannelGenLepNoHTobbCtr += 1;
                            passEnoughFJsInSemiLepChannelGenLepNoHTobbWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 1) {
                            passEnoughFJsInSemiLepChannelGenSemiLepNoHTobbCtr += 1;
                            passEnoughFJsInSemiLepChannelGenSemiLepNoHTobbWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 2) {
                            passEnoughFJsInSemiLepChannelGenHadNoHTobbCtr += 1;
                            passEnoughFJsInSemiLepChannelGenHadNoHTobbWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 3) {
                            passEnoughFJsInSemiLepChannelGenOtherNoHTobbCtr += 1;
                            passEnoughFJsInSemiLepChannelGenOtherNoHTobbWeightedCtr += tmpGenWeights;
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
                        passEnoughLepsInSemiLepChannelWeightedCtr += tmpGenWeights;
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

                    if (passedAsSemiLepLepCutBool){
                        if (debug) std::cout << "Passed semi lep lep cut\n";
                        passSemiLepLepCutCtr += 1;
                        passSemiLepLepCutWeightedCtr += tmpGenWeights;
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
                        passFJInSemiLepChannelWeightedCtr += tmpGenWeights;
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
                        
                    FJIndAr.push_back(FJInd);
                    
                    }
                }
                
                if (passesCutsBool){
                    passChannelCtr += 1;
                    passChannelWeightedCtr += tmpGenWeights;
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
                    


                    passSemiLepChannelCtr += 1;
                    passSemiLepChannelWeightedCtr += tmpGenWeights;
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
                    

                    passLepOrSemiLepChannelCtr += 1;
                    passLepOrSemiLepChannelWeightedCtr += tmpGenWeights;
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
                    
                    passHadChannelCtr += 1;
                    passHadChannelWeightedCtr += tmpGenWeights;
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
            debug = false;

            if (*HTobbBoolL){
                if (*genChannelL == 0) {
                    passHiggsFJPreSTGenLepCtr += 1;
                    passHiggsFJPreSTGenLepWeightedCtr += tmpGenWeights;
                }
                if (*genChannelL == 1) {
                    passHiggsFJPreSTGenSemiLepCtr += 1;
                    passHiggsFJPreSTGenSemiLepWeightedCtr += tmpGenWeights;
                }
                if (*genChannelL == 2) {
                    passHiggsFJPreSTGenHadCtr += 1;
                    passHiggsFJPreSTGenHadWeightedCtr += tmpGenWeights;
                }
                if (*genChannelL == 3) {
                    passHiggsFJPreSTGenOtherCtr += 1;
                    passHiggsFJPreSTGenOtherWeightedCtr += tmpGenWeights;
                }
            }
            else {
                if (*genChannelL == 0) {
                    passHiggsFJPreSTGenLepNoHTobbCtr += 1;
                    passHiggsFJPreSTGenLepNoHTobbWeightedCtr += tmpGenWeights;
                }
                if (*genChannelL == 1) {
                    passHiggsFJPreSTGenSemiLepNoHTobbCtr += 1;
                    passHiggsFJPreSTGenSemiLepNoHTobbWeightedCtr += tmpGenWeights;
                }
                if (*genChannelL == 2) {
                    passHiggsFJPreSTGenHadNoHTobbCtr += 1;
                    passHiggsFJPreSTGenHadNoHTobbWeightedCtr += tmpGenWeights;
                }
                if (*genChannelL == 3) {
                    passHiggsFJPreSTGenOtherNoHTobbCtr += 1;
                    passHiggsFJPreSTGenOtherNoHTobbWeightedCtr += tmpGenWeights;
                }
            }
            

            if (passedAsLepBool) {
                passHiggsFJPreSTLepCtr += 1;
                passHiggsFJPreSTWeightedLepCtr += tmpGenWeights;
                if (*HTobbBoolL){
                    if (*genChannelL == 0) {
                        passHiggsFJPreSTLepGenLepCtr += 1;
                        passHiggsFJPreSTWeightedLepGenLepCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 1) {
                        passHiggsFJPreSTLepGenSemiLepCtr += 1;
                        passHiggsFJPreSTWeightedLepGenSemiLepCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 2) {
                        passHiggsFJPreSTLepGenHadCtr += 1;
                        passHiggsFJPreSTWeightedLepGenHadCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 3) {
                        passHiggsFJPreSTLepGenOtherCtr += 1;
                        passHiggsFJPreSTWeightedLepGenOtherCtr += tmpGenWeights;
                    }
                }
                else {
                    if (*genChannelL == 0) {
                        passHiggsFJPreSTLepGenLepNoHTobbCtr += 1;
                        passHiggsFJPreSTWeightedLepGenLepNoHTobbCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 1) {
                        passHiggsFJPreSTLepGenSemiLepNoHTobbCtr += 1;
                        passHiggsFJPreSTWeightedLepGenSemiLepNoHTobbCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 2) {
                        passHiggsFJPreSTLepGenHadNoHTobbCtr += 1;
                        passHiggsFJPreSTWeightedLepGenHadNoHTobbCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 3) {
                        passHiggsFJPreSTLepGenOtherNoHTobbCtr += 1;
                        passHiggsFJPreSTWeightedLepGenOtherNoHTobbCtr += tmpGenWeights;
                    }
                }
                
            }
            else if (passedAsSemiLepBool) {
                passHiggsFJPreSTSemiLepCtr += 1;
                passHiggsFJPreSTWeightedSemiLepCtr += tmpGenWeights;
                if (*HTobbBoolL){
                    if (*genChannelL == 0) {
                        passHiggsFJPreSTSemiLepGenLepCtr += 1;
                        passHiggsFJPreSTWeightedSemiLepGenLepCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 1) {
                        passHiggsFJPreSTSemiLepGenSemiLepCtr += 1;
                        passHiggsFJPreSTWeightedSemiLepGenSemiLepCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 2) {
                        passHiggsFJPreSTSemiLepGenHadCtr += 1;
                        passHiggsFJPreSTWeightedSemiLepGenHadCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 3) {
                        passHiggsFJPreSTSemiLepGenOtherCtr += 1;
                        passHiggsFJPreSTWeightedSemiLepGenOtherCtr += tmpGenWeights;
                    }
                }
                else {
                    if (*genChannelL == 0) {
                        passHiggsFJPreSTSemiLepGenLepNoHTobbCtr += 1;
                        passHiggsFJPreSTWeightedSemiLepGenLepNoHTobbCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 1) {
                        passHiggsFJPreSTSemiLepGenSemiLepNoHTobbCtr += 1;
                        passHiggsFJPreSTWeightedSemiLepGenSemiLepNoHTobbCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 2) {
                        passHiggsFJPreSTSemiLepGenHadNoHTobbCtr += 1;
                        passHiggsFJPreSTWeightedSemiLepGenHadNoHTobbCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 3) {
                        passHiggsFJPreSTSemiLepGenOtherNoHTobbCtr += 1;
                        passHiggsFJPreSTWeightedSemiLepGenOtherNoHTobbCtr += tmpGenWeights;
                    }
                }
                
            }
            else if (passedAsHadBool) {
                passHiggsFJPreSTHadCtr += 1;
                passHiggsFJPreSTWeightedHadCtr += tmpGenWeights;
                if (*HTobbBoolL){
                    if (*genChannelL == 0) {
                        passHiggsFJPreSTHadGenLepCtr += 1;
                        passHiggsFJPreSTWeightedHadGenLepCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 1) {
                        passHiggsFJPreSTHadGenSemiLepCtr += 1;
                        passHiggsFJPreSTWeightedHadGenSemiLepCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 2) {
                        passHiggsFJPreSTHadGenHadCtr += 1;
                        passHiggsFJPreSTWeightedHadGenHadCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 3) {
                        passHiggsFJPreSTHadGenOtherCtr += 1;
                        passHiggsFJPreSTWeightedHadGenOtherCtr += tmpGenWeights;
                    }
                }
                else {
                    if (*genChannelL == 0) {
                        passHiggsFJPreSTHadGenLepNoHTobbCtr += 1;
                        passHiggsFJPreSTWeightedHadGenLepNoHTobbCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 1) {
                        passHiggsFJPreSTHadGenSemiLepNoHTobbCtr += 1;
                        passHiggsFJPreSTWeightedHadGenSemiLepNoHTobbCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 2) {
                        passHiggsFJPreSTHadGenHadNoHTobbCtr += 1;
                        passHiggsFJPreSTWeightedHadGenHadNoHTobbCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 3) {
                        passHiggsFJPreSTHadGenOtherNoHTobbCtr += 1;
                        passHiggsFJPreSTWeightedHadGenOtherNoHTobbCtr += tmpGenWeights;
                    }
                }
                
            }








            bool passesSTCutBool = false;
            doHiggsFatJetCutSTWithBDTVars(dRCheckVecAr,ZPairPlusHInvMassCut,ZPairPlusHPtCut,ZPairPlusHInvMass,ZPairPlusHPt,passesSTCutBool);
            if (!passesSTCutBool) continue;
            if (debug) std::cout << " found Higgs fat jet\n";
            passHiggsFJCtr += 1;
            passHiggsFJWeightedCtr += tmpGenWeights;
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
            

            if (passedAsLepBool) {
                passHiggsFJLepCtr += 1;
                passHiggsFJWeightedLepCtr += tmpGenWeights;
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
            else if (passedAsSemiLepBool) {
                passHiggsFJSemiLepCtr += 1;
                passHiggsFJWeightedSemiLepCtr += tmpGenWeights;
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
            else if (passedAsHadBool) {
                passHiggsFJHadCtr += 1;
                passHiggsFJWeightedHadCtr += tmpGenWeights;
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
            if (*HTobbBoolL){
                if (*genChannelL == 0) {
                    passVBFJetBVetoGenLepCtr += 1;
                    passVBFJetBVetoGenLepWeightedCtr += tmpGenWeights;
                }
                if (*genChannelL == 1) {
                    passVBFJetBVetoGenSemiLepCtr += 1;
                    passVBFJetBVetoGenSemiLepWeightedCtr += tmpGenWeights;
                }
                if (*genChannelL == 2) {
                    passVBFJetBVetoGenHadCtr += 1;
                    passVBFJetBVetoGenHadWeightedCtr += tmpGenWeights;
                }
                if (*genChannelL == 3) {
                    passVBFJetBVetoGenOtherCtr += 1;
                    passVBFJetBVetoGenOtherWeightedCtr += tmpGenWeights;
                }
            }
            else {
                if (*genChannelL == 0) {
                    passVBFJetBVetoGenLepNoHTobbCtr += 1;
                    passVBFJetBVetoGenLepNoHTobbWeightedCtr += tmpGenWeights;
                }
                if (*genChannelL == 1) {
                    passVBFJetBVetoGenSemiLepNoHTobbCtr += 1;
                    passVBFJetBVetoGenSemiLepNoHTobbWeightedCtr += tmpGenWeights;
                }
                if (*genChannelL == 2) {
                    passVBFJetBVetoGenHadNoHTobbCtr += 1;
                    passVBFJetBVetoGenHadNoHTobbWeightedCtr += tmpGenWeights;
                }
                if (*genChannelL == 3) {
                    passVBFJetBVetoGenOtherNoHTobbCtr += 1;
                    passVBFJetBVetoGenOtherNoHTobbWeightedCtr += tmpGenWeights;
                }
            }
        

            if (passedAsLepBool) {
                passVBFJetBVetoLepCtr += 1;
                passVBFJetBVetoWeightedLepCtr += tmpGenWeights;
                if (*HTobbBoolL){
                    if (*genChannelL == 0) {
                        passVBFJetBVetoLepGenLepCtr += 1;
                        passVBFJetBVetoWeightedLepGenLepCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 1) {
                        passVBFJetBVetoLepGenSemiLepCtr += 1;
                        passVBFJetBVetoWeightedLepGenSemiLepCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 2) {
                        passVBFJetBVetoLepGenHadCtr += 1;
                        passVBFJetBVetoWeightedLepGenHadCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 3) {
                        passVBFJetBVetoLepGenOtherCtr += 1;
                        passVBFJetBVetoWeightedLepGenOtherCtr += tmpGenWeights;
                    }
                }
                else {
                    if (*genChannelL == 0) {
                        passVBFJetBVetoLepGenLepNoHTobbCtr += 1;
                        passVBFJetBVetoWeightedLepGenLepNoHTobbCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 1) {
                        passVBFJetBVetoLepGenSemiLepNoHTobbCtr += 1;
                        passVBFJetBVetoWeightedLepGenSemiLepNoHTobbCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 2) {
                        passVBFJetBVetoLepGenHadNoHTobbCtr += 1;
                        passVBFJetBVetoWeightedLepGenHadNoHTobbCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 3) {
                        passVBFJetBVetoLepGenOtherNoHTobbCtr += 1;
                        passVBFJetBVetoWeightedLepGenOtherNoHTobbCtr += tmpGenWeights;
                    }
                }
            
            }
            else if (passedAsSemiLepBool) {
                passVBFJetBVetoSemiLepCtr += 1;
                passVBFJetBVetoWeightedSemiLepCtr += tmpGenWeights;
                if (*HTobbBoolL){
                    if (*genChannelL == 0) {
                        passVBFJetBVetoSemiLepGenLepCtr += 1;
                        passVBFJetBVetoWeightedSemiLepGenLepCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 1) {
                        passVBFJetBVetoSemiLepGenSemiLepCtr += 1;
                        passVBFJetBVetoWeightedSemiLepGenSemiLepCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 2) {
                        passVBFJetBVetoSemiLepGenHadCtr += 1;
                        passVBFJetBVetoWeightedSemiLepGenHadCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 3) {
                        passVBFJetBVetoSemiLepGenOtherCtr += 1;
                        passVBFJetBVetoWeightedSemiLepGenOtherCtr += tmpGenWeights;
                    }
                }
                else {
                    if (*genChannelL == 0) {
                        passVBFJetBVetoSemiLepGenLepNoHTobbCtr += 1;
                        passVBFJetBVetoWeightedSemiLepGenLepNoHTobbCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 1) {
                        passVBFJetBVetoSemiLepGenSemiLepNoHTobbCtr += 1;
                        passVBFJetBVetoWeightedSemiLepGenSemiLepNoHTobbCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 2) {
                        passVBFJetBVetoSemiLepGenHadNoHTobbCtr += 1;
                        passVBFJetBVetoWeightedSemiLepGenHadNoHTobbCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 3) {
                        passVBFJetBVetoSemiLepGenOtherNoHTobbCtr += 1;
                        passVBFJetBVetoWeightedSemiLepGenOtherNoHTobbCtr += tmpGenWeights;
                    }
                }
            
            }
            else if (passedAsHadBool) {
                passVBFJetBVetoHadCtr += 1;
                passVBFJetBVetoWeightedHadCtr += tmpGenWeights;
                if (*HTobbBoolL){
                    if (*genChannelL == 0) {
                        passVBFJetBVetoHadGenLepCtr += 1;
                        passVBFJetBVetoWeightedHadGenLepCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 1) {
                        passVBFJetBVetoHadGenSemiLepCtr += 1;
                        passVBFJetBVetoWeightedHadGenSemiLepCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 2) {
                        passVBFJetBVetoHadGenHadCtr += 1;
                        passVBFJetBVetoWeightedHadGenHadCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 3) {
                        passVBFJetBVetoHadGenOtherCtr += 1;
                        passVBFJetBVetoWeightedHadGenOtherCtr += tmpGenWeights;
                    }
                }
                else {
                    if (*genChannelL == 0) {
                        passVBFJetBVetoHadGenLepNoHTobbCtr += 1;
                        passVBFJetBVetoWeightedHadGenLepNoHTobbCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 1) {
                        passVBFJetBVetoHadGenSemiLepNoHTobbCtr += 1;
                        passVBFJetBVetoWeightedHadGenSemiLepNoHTobbCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 2) {
                        passVBFJetBVetoHadGenHadNoHTobbCtr += 1;
                        passVBFJetBVetoWeightedHadGenHadNoHTobbCtr += tmpGenWeights;
                    }
                    if (*genChannelL == 3) {
                        passVBFJetBVetoHadGenOtherNoHTobbCtr += 1;
                        passVBFJetBVetoWeightedHadGenOtherNoHTobbCtr += tmpGenWeights;
                    }
                }
            
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
            

                //std::cout << passedAsLepBool << " "<< passedAsSemiLepBool << " " << passedAsHadBool << "\n";
                if (passedAsLepBool) {

                    passAsLepCtr += 1;
                    passAsLepWeightedCtr += tmpGenWeights;
                    if (!BDTSignalGenChannelMatched){
                        //Fill BDT Lep Tree
                        passingEvGenWeight_L_L = tmpGenWeights;

                        passingEvFullWeight_L_L = tmpGenWeights*XS*Run2Lumi/totWeight;

                        datasetType_L_L = datasetType;

                        selectedHiggsFJ_pt_L_L = hFatJet_pt_fromHTag;
                        selectedHiggsFJ_eta_L_L = hFatJet_eta_fromHTag;
                        selectedHiggsFJ_ParticleNet_HbbvsQCD_L_L = hFatJet_HTag_fromHTag;

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
                    }

                    if (*HTobbBoolL){
                        if (*genChannelL == 0) {
                            passAsLepGenLepCtr += 1;
                            passAsLepGenLepWeightedCtr += tmpGenWeights;

                            if (BDTSignalGenChannelMatched){


                                //Fill BDT Lep Tree
                                passingEvGenWeight_L_L = tmpGenWeights;

                                passingEvFullWeight_L_L = tmpGenWeights*XS*Run2Lumi/totWeight;

                                datasetType_L_L = datasetType;

                                selectedHiggsFJ_pt_L_L = hFatJet_pt_fromHTag;
                                selectedHiggsFJ_eta_L_L = hFatJet_eta_fromHTag;
                                selectedHiggsFJ_ParticleNet_HbbvsQCD_L_L = hFatJet_HTag_fromHTag;

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
                            }




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
                
                else if (passedAsSemiLepBool){


                    passAsSemiLepCtr += 1;
                    passAsSemiLepWeightedCtr += tmpGenWeights;


                    if (!BDTSignalGenChannelMatched){
                        passingEvGenWeight_SL_L = tmpGenWeights;

                        passingEvFullWeight_SL_L = tmpGenWeights*XS*Run2Lumi/totWeight;

                        datasetType_SL_L = datasetType;

                        selectedHiggsFJ_pt_SL_L = hFatJet_pt_fromHTag;
                        selectedZFJ_pt_SL_L = dRCheckVecAr[2].Pt();
                        selectedHiggsFJ_eta_SL_L = hFatJet_eta_fromHTag;
                        selectedZFJ_eta_SL_L = dRCheckVecAr[2].Eta();
                        selectedHiggsFJ_ParticleNet_HbbvsQCD_SL_L = hFatJet_HTag_fromHTag;
                        selectedZFJ_ParticleNet_ZvsQCD_SL_L = FatJet_particleNet_ZvsQCDL[FJIndAr[0]];

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
                    }





                    if (*HTobbBoolL){
                        if (*genChannelL == 0) {
                            passAsSemiLepGenLepCtr += 1;
                            passAsSemiLepGenLepWeightedCtr += tmpGenWeights;
                        }
                        if (*genChannelL == 1) {
                            passAsSemiLepGenSemiLepCtr += 1;
                            passAsSemiLepGenSemiLepWeightedCtr += tmpGenWeights;
                            //Fill BDT SemiLep Tree
                            if (BDTSignalGenChannelMatched){
                                passingEvGenWeight_SL_L = tmpGenWeights;

                                passingEvFullWeight_SL_L = tmpGenWeights*XS*Run2Lumi/totWeight;

                                datasetType_SL_L = datasetType;

                                selectedHiggsFJ_pt_SL_L = hFatJet_pt_fromHTag;
                                selectedZFJ_pt_SL_L = dRCheckVecAr[2].Pt();
                                selectedHiggsFJ_eta_SL_L = hFatJet_eta_fromHTag;
                                selectedZFJ_eta_SL_L = dRCheckVecAr[2].Eta();
                                selectedHiggsFJ_ParticleNet_HbbvsQCD_SL_L = hFatJet_HTag_fromHTag;
                                selectedZFJ_ParticleNet_ZvsQCD_SL_L = FatJet_particleNet_ZvsQCDL[FJIndAr[0]];

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
                            }





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
                else if (passedAsHadBool) {

                    passAsHadCtr += 1;
                    passAsHadWeightedCtr += tmpGenWeights;
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
    if (debug) std::cout << "Filling complete \n";

    clock_t endt = clock();
    double time_spent = (double)(endt - startt) / CLOCKS_PER_SEC;


    std::cout << "Finished file loop. " << "time: " << time_spent << "\n";
    crossSection = crossSectionAvg / crossSectionCnt;
        
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
    std::cout << "Double_t " << saveName << "PassVBFJetBVetoWeightedCtr = " << passVBFJetBVetoWeightedCtr << "\n";
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
    std::cout << "UInt_t " << saveName << "passEnoughFJsInSemiLepChannelGenLepCtr = " << passEnoughFJsInSemiLepChannelGenLepCtr << "\n";
    std::cout << "Double_t " << saveName << "passEnoughFJsInSemiLepChannelGenLepWeightedCtr = " << passEnoughFJsInSemiLepChannelGenLepWeightedCtr << "\n";
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
    std::cout << "UInt_t " << saveName << "PassHiggsFJPreSTGenLepCtr = " << passHiggsFJPreSTGenLepCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJPreSTGenLepWeightedCtr = " << passHiggsFJPreSTGenLepWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJPreSTLepGenLepCtr = " << passHiggsFJPreSTLepGenLepCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJPreSTWeightedLepGenLepCtr = " << passHiggsFJPreSTWeightedLepGenLepCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJPreSTSemiLepGenLepCtr = " << passHiggsFJPreSTSemiLepGenLepCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJPreSTWeightedSemiLepGenLepCtr = " << passHiggsFJPreSTWeightedSemiLepGenLepCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJPreSTHadGenLepCtr = " << passHiggsFJPreSTHadGenLepCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJPreSTWeightedHadGenLepCtr = " << passHiggsFJPreSTWeightedHadGenLepCtr << "\n";
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
    std::cout << "UInt_t " << saveName << "PassVBFJetBVetoGenLepCtr = " << passVBFJetBVetoGenLepCtr << "\n";
    std::cout << "Double_t " << saveName << "PassVBFJetBVetoGenLepWeightedCtr = " << passVBFJetBVetoGenLepWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassVBFJetBVetoLepGenLepCtr = " << passVBFJetBVetoLepGenLepCtr << "\n";
    std::cout << "Double_t " << saveName << "passVBFJetBVetoWeightedLepGenLepCtr = " << passVBFJetBVetoWeightedLepGenLepCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassVBFJetBVetoSemiLepGenLepCtr = " << passVBFJetBVetoSemiLepGenLepCtr << "\n";
    std::cout << "Double_t " << saveName << "passVBFJetBVetoWeightedSemiLepGenLepCtr = " << passVBFJetBVetoWeightedSemiLepGenLepCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassVBFJetBVetoHadGenLepCtr = " << passVBFJetBVetoHadGenLepCtr << "\n";
    std::cout << "Double_t " << saveName << "passVBFJetBVetoWeightedHadGenLepCtr = " << passVBFJetBVetoWeightedHadGenLepCtr << "\n";
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
    std::cout << "UInt_t " << saveName << "passEnoughFJsInSemiLepChannelGenSemiLepCtr = " << passEnoughFJsInSemiLepChannelGenSemiLepCtr << "\n";
    std::cout << "Double_t " << saveName << "passEnoughFJsInSemiLepChannelGenSemiLepWeightedCtr = " << passEnoughFJsInSemiLepChannelGenSemiLepWeightedCtr << "\n";
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
    std::cout << "UInt_t " << saveName << "PassHiggsFJPreSTGenSemiLepCtr = " << passHiggsFJPreSTGenSemiLepCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJPreSTGenSemiLepWeightedCtr = " << passHiggsFJPreSTGenSemiLepWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJPreSTLepGenSemiLepCtr = " << passHiggsFJPreSTLepGenSemiLepCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJPreSTWeightedLepGenSemiLepCtr = " << passHiggsFJPreSTWeightedLepGenSemiLepCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJPreSTSemiLepGenSemiLepCtr = " << passHiggsFJPreSTSemiLepGenSemiLepCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJPreSTWeightedSemiLepGenSemiLepCtr = " << passHiggsFJPreSTWeightedSemiLepGenSemiLepCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJPreSTHadGenSemiLepCtr = " << passHiggsFJPreSTHadGenSemiLepCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJPreSTWeightedHadGenSemiLepCtr = " << passHiggsFJPreSTWeightedHadGenSemiLepCtr << "\n";
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
    std::cout << "UInt_t " << saveName << "PassVBFJetBVetoGenSemiLepCtr = " << passVBFJetBVetoGenSemiLepCtr << "\n";
    std::cout << "Double_t " << saveName << "PassVBFJetBVetoGenSemiLepWeightedCtr = " << passVBFJetBVetoGenSemiLepWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassVBFJetBVetoLepGenSemiLepCtr = " << passVBFJetBVetoLepGenSemiLepCtr << "\n";
    std::cout << "Double_t " << saveName << "passVBFJetBVetoWeightedLepGenSemiLepCtr = " << passVBFJetBVetoWeightedLepGenSemiLepCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassVBFJetBVetoSemiLepGenSemiLepCtr = " << passVBFJetBVetoSemiLepGenSemiLepCtr << "\n";
    std::cout << "Double_t " << saveName << "passVBFJetBVetoWeightedSemiLepGenSemiLepCtr = " << passVBFJetBVetoWeightedSemiLepGenSemiLepCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassVBFJetBVetoHadGenSemiLepCtr = " << passVBFJetBVetoHadGenSemiLepCtr << "\n";
    std::cout << "Double_t " << saveName << "passVBFJetBVetoWeightedHadGenSemiLepCtr = " << passVBFJetBVetoWeightedHadGenSemiLepCtr << "\n";
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
    std::cout << "UInt_t " << saveName << "passEnoughFJsInSemiLepChannelGenHadCtr = " << passEnoughFJsInSemiLepChannelGenHadCtr << "\n";
    std::cout << "Double_t " << saveName << "passEnoughFJsInSemiLepChannelGenHadWeightedCtr = " << passEnoughFJsInSemiLepChannelGenHadWeightedCtr << "\n";
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
    std::cout << "UInt_t " << saveName << "PassHiggsFJPreSTGenHadCtr = " << passHiggsFJPreSTGenHadCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJPreSTGenHadWeightedCtr = " << passHiggsFJPreSTGenHadWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJPreSTLepGenHadCtr = " << passHiggsFJPreSTLepGenHadCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJPreSTWeightedLepGenHadCtr = " << passHiggsFJPreSTWeightedLepGenHadCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJPreSTSemiLepGenHadCtr = " << passHiggsFJPreSTSemiLepGenHadCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJPreSTWeightedSemiLepGenHadCtr = " << passHiggsFJPreSTWeightedSemiLepGenHadCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJPreSTHadGenHadCtr = " << passHiggsFJPreSTHadGenHadCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJPreSTWeightedHadGenHadCtr = " << passHiggsFJPreSTWeightedHadGenHadCtr << "\n";
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
    std::cout << "UInt_t " << saveName << "PassVBFJetBVetoGenHadCtr = " << passVBFJetBVetoGenHadCtr << "\n";
    std::cout << "Double_t " << saveName << "PassVBFJetBVetoGenHadWeightedCtr = " << passVBFJetBVetoGenHadWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassVBFJetBVetoLepGenHadCtr = " << passVBFJetBVetoLepGenHadCtr << "\n";
    std::cout << "Double_t " << saveName << "passVBFJetBVetoWeightedLepGenHadCtr = " << passVBFJetBVetoWeightedLepGenHadCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassVBFJetBVetoSemiLepGenHadCtr = " << passVBFJetBVetoSemiLepGenHadCtr << "\n";
    std::cout << "Double_t " << saveName << "passVBFJetBVetoWeightedSemiLepGenHadCtr = " << passVBFJetBVetoWeightedSemiLepGenHadCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassVBFJetBVetoHadGenHadCtr = " << passVBFJetBVetoHadGenHadCtr << "\n";
    std::cout << "Double_t " << saveName << "passVBFJetBVetoWeightedHadGenHadCtr = " << passVBFJetBVetoWeightedHadGenHadCtr << "\n";
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
    std::cout << "UInt_t " << saveName << "passEnoughFJsInSemiLepChannelGenOtherCtr = " << passEnoughFJsInSemiLepChannelGenOtherCtr << "\n";
    std::cout << "Double_t " << saveName << "passEnoughFJsInSemiLepChannelGenOtherWeightedCtr = " << passEnoughFJsInSemiLepChannelGenOtherWeightedCtr << "\n";
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
    std::cout << "UInt_t " << saveName << "PassHiggsFJPreSTGenOtherCtr = " << passHiggsFJPreSTGenOtherCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJPreSTGenOtherWeightedCtr = " << passHiggsFJPreSTGenOtherWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJPreSTLepGenOtherCtr = " << passHiggsFJPreSTLepGenOtherCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJPreSTWeightedLepGenOtherCtr = " << passHiggsFJPreSTWeightedLepGenOtherCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJPreSTSemiLepGenOtherCtr = " << passHiggsFJPreSTSemiLepGenOtherCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJPreSTWeightedSemiLepGenOtherCtr = " << passHiggsFJPreSTWeightedSemiLepGenOtherCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJPreSTHadGenOtherCtr = " << passHiggsFJPreSTHadGenOtherCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJPreSTWeightedHadGenOtherCtr = " << passHiggsFJPreSTWeightedHadGenOtherCtr << "\n";
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
    std::cout << "UInt_t " << saveName << "PassVBFJetBVetoGenOtherCtr = " << passVBFJetBVetoGenOtherCtr << "\n";
    std::cout << "Double_t " << saveName << "PassVBFJetBVetoGenOtherWeightedCtr = " << passVBFJetBVetoGenOtherWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassVBFJetBVetoLepGenOtherCtr = " << passVBFJetBVetoLepGenOtherCtr << "\n";
    std::cout << "Double_t " << saveName << "passVBFJetBVetoWeightedLepGenOtherCtr = " << passVBFJetBVetoWeightedLepGenOtherCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassVBFJetBVetoSemiLepGenOtherCtr = " << passVBFJetBVetoSemiLepGenOtherCtr << "\n";
    std::cout << "Double_t " << saveName << "passVBFJetBVetoWeightedSemiLepGenOtherCtr = " << passVBFJetBVetoWeightedSemiLepGenOtherCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassVBFJetBVetoHadGenOtherCtr = " << passVBFJetBVetoHadGenOtherCtr << "\n";
    std::cout << "Double_t " << saveName << "passVBFJetBVetoWeightedHadGenOtherCtr = " << passVBFJetBVetoWeightedHadGenOtherCtr << "\n";
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
    std::cout << "UInt_t " << saveName << "passEnoughFJsInSemiLepChannelGenLepNoHTobbCtr = " << passEnoughFJsInSemiLepChannelGenLepNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passEnoughFJsInSemiLepChannelGenLepNoHTobbWeightedCtr = " << passEnoughFJsInSemiLepChannelGenLepNoHTobbWeightedCtr << "\n";
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
    std::cout << "UInt_t " << saveName << "PassHiggsFJPreSTGenLepNoHTobbCtr = " << passHiggsFJPreSTGenLepNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJPreSTGenLepNoHTobbWeightedCtr = " << passHiggsFJPreSTGenLepNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJPreSTLepGenLepNoHTobbCtr = " << passHiggsFJPreSTLepGenLepNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJPreSTWeightedLepGenLepNoHTobbCtr = " << passHiggsFJPreSTWeightedLepGenLepNoHTobbCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJPreSTSemiLepGenLepNoHTobbCtr = " << passHiggsFJPreSTSemiLepGenLepNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJPreSTWeightedSemiLepGenLepNoHTobbCtr = " << passHiggsFJPreSTWeightedSemiLepGenLepNoHTobbCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJPreSTHadGenLepNoHTobbCtr = " << passHiggsFJPreSTHadGenLepNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJPreSTWeightedHadGenLepNoHTobbCtr = " << passHiggsFJPreSTWeightedHadGenLepNoHTobbCtr << "\n";
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
    std::cout << "UInt_t " << saveName << "PassVBFJetBVetoGenLepNoHTobbCtr = " << passVBFJetBVetoGenLepNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "PassVBFJetBVetoGenLepNoHTobbWeightedCtr = " << passVBFJetBVetoGenLepNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassVBFJetBVetoLepGenLepNoHTobbCtr = " << passVBFJetBVetoLepGenLepNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passVBFJetBVetoWeightedLepGenLepNoHTobbCtr = " << passVBFJetBVetoWeightedLepGenLepNoHTobbCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassVBFJetBVetoSemiLepGenLepNoHTobbCtr = " << passVBFJetBVetoSemiLepGenLepNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passVBFJetBVetoWeightedSemiLepGenLepNoHTobbCtr = " << passVBFJetBVetoWeightedSemiLepGenLepNoHTobbCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassVBFJetBVetoHadGenLepNoHTobbCtr = " << passVBFJetBVetoHadGenLepNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passVBFJetBVetoWeightedHadGenLepNoHTobbCtr = " << passVBFJetBVetoWeightedHadGenLepNoHTobbCtr << "\n";
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
    std::cout << "UInt_t " << saveName << "passEnoughFJsInSemiLepChannelGenSemiLepNoHTobbCtr = " << passEnoughFJsInSemiLepChannelGenSemiLepNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passEnoughFJsInSemiLepChannelGenSemiLepNoHTobbWeightedCtr = " << passEnoughFJsInSemiLepChannelGenSemiLepNoHTobbWeightedCtr << "\n";
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
    std::cout << "UInt_t " << saveName << "PassHiggsFJPreSTGenSemiLepNoHTobbCtr = " << passHiggsFJPreSTGenSemiLepNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJPreSTGenSemiLepNoHTobbWeightedCtr = " << passHiggsFJPreSTGenSemiLepNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJPreSTLepGenSemiLepNoHTobbCtr = " << passHiggsFJPreSTLepGenSemiLepNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJPreSTWeightedLepGenSemiLepNoHTobbCtr = " << passHiggsFJPreSTWeightedLepGenSemiLepNoHTobbCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJPreSTSemiLepGenSemiLepNoHTobbCtr = " << passHiggsFJPreSTSemiLepGenSemiLepNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJPreSTWeightedSemiLepGenSemiLepNoHTobbCtr = " << passHiggsFJPreSTWeightedSemiLepGenSemiLepNoHTobbCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJPreSTHadGenSemiLepNoHTobbCtr = " << passHiggsFJPreSTHadGenSemiLepNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJPreSTWeightedHadGenSemiLepNoHTobbCtr = " << passHiggsFJPreSTWeightedHadGenSemiLepNoHTobbCtr << "\n";
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
    std::cout << "UInt_t " << saveName << "PassVBFJetBVetoGenSemiLepNoHTobbCtr = " << passVBFJetBVetoGenSemiLepNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "PassVBFJetBVetoGenSemiLepNoHTobbWeightedCtr = " << passVBFJetBVetoGenSemiLepNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassVBFJetBVetoLepGenSemiLepNoHTobbCtr = " << passVBFJetBVetoLepGenSemiLepNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passVBFJetBVetoWeightedLepGenSemiLepNoHTobbCtr = " << passVBFJetBVetoWeightedLepGenSemiLepNoHTobbCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassVBFJetBVetoSemiLepGenSemiLepNoHTobbCtr = " << passVBFJetBVetoSemiLepGenSemiLepNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passVBFJetBVetoWeightedSemiLepGenSemiLepNoHTobbCtr = " << passVBFJetBVetoWeightedSemiLepGenSemiLepNoHTobbCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassVBFJetBVetoHadGenSemiLepNoHTobbCtr = " << passVBFJetBVetoHadGenSemiLepNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passVBFJetBVetoWeightedHadGenSemiLepNoHTobbCtr = " << passVBFJetBVetoWeightedHadGenSemiLepNoHTobbCtr << "\n";
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
    std::cout << "UInt_t " << saveName << "passEnoughFJsInSemiLepChannelGenHadNoHTobbCtr = " << passEnoughFJsInSemiLepChannelGenHadNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passEnoughFJsInSemiLepChannelGenHadNoHTobbWeightedCtr = " << passEnoughFJsInSemiLepChannelGenHadNoHTobbWeightedCtr << "\n";
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
    std::cout << "UInt_t " << saveName << "PassHiggsFJPreSTGenHadNoHTobbCtr = " << passHiggsFJPreSTGenHadNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJPreSTGenHadNoHTobbWeightedCtr = " << passHiggsFJPreSTGenHadNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJPreSTLepGenHadNoHTobbCtr = " << passHiggsFJPreSTLepGenHadNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJPreSTWeightedLepGenHadNoHTobbCtr = " << passHiggsFJPreSTWeightedLepGenHadNoHTobbCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJPreSTSemiLepGenHadNoHTobbCtr = " << passHiggsFJPreSTSemiLepGenHadNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJPreSTWeightedSemiLepGenHadNoHTobbCtr = " << passHiggsFJPreSTWeightedSemiLepGenHadNoHTobbCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJPreSTHadGenHadNoHTobbCtr = " << passHiggsFJPreSTHadGenHadNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJPreSTWeightedHadGenHadNoHTobbCtr = " << passHiggsFJPreSTWeightedHadGenHadNoHTobbCtr << "\n";
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
    std::cout << "UInt_t " << saveName << "PassVBFJetBVetoGenHadNoHTobbCtr = " << passVBFJetBVetoGenHadNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "PassVBFJetBVetoGenHadNoHTobbWeightedCtr = " << passVBFJetBVetoGenHadNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassVBFJetBVetoLepGenHadNoHTobbCtr = " << passVBFJetBVetoLepGenHadNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passVBFJetBVetoWeightedLepGenHadNoHTobbCtr = " << passVBFJetBVetoWeightedLepGenHadNoHTobbCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassVBFJetBVetoSemiLepGenHadNoHTobbCtr = " << passVBFJetBVetoSemiLepGenHadNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passVBFJetBVetoWeightedSemiLepGenHadNoHTobbCtr = " << passVBFJetBVetoWeightedSemiLepGenHadNoHTobbCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassVBFJetBVetoHadGenHadNoHTobbCtr = " << passVBFJetBVetoHadGenHadNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passVBFJetBVetoWeightedHadGenHadNoHTobbCtr = " << passVBFJetBVetoWeightedHadGenHadNoHTobbCtr << "\n";
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
    std::cout << "UInt_t " << saveName << "passEnoughFJsInSemiLepChannelGenOtherNoHTobbCtr = " << passEnoughFJsInSemiLepChannelGenOtherNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passEnoughFJsInSemiLepChannelGenOtherNoHTobbWeightedCtr = " << passEnoughFJsInSemiLepChannelGenOtherNoHTobbWeightedCtr << "\n";
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
    std::cout << "UInt_t " << saveName << "PassHiggsFJPreSTGenOtherNoHTobbCtr = " << passHiggsFJPreSTGenOtherNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJPreSTGenOtherNoHTobbWeightedCtr = " << passHiggsFJPreSTGenOtherNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJPreSTLepGenOtherNoHTobbCtr = " << passHiggsFJPreSTLepGenOtherNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJPreSTWeightedLepGenOtherNoHTobbCtr = " << passHiggsFJPreSTWeightedLepGenOtherNoHTobbCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJPreSTSemiLepGenOtherNoHTobbCtr = " << passHiggsFJPreSTSemiLepGenOtherNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJPreSTWeightedSemiLepGenOtherNoHTobbCtr = " << passHiggsFJPreSTWeightedSemiLepGenOtherNoHTobbCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassHiggsFJPreSTHadGenOtherNoHTobbCtr = " << passHiggsFJPreSTHadGenOtherNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passHiggsFJPreSTWeightedHadGenOtherNoHTobbCtr = " << passHiggsFJPreSTWeightedHadGenOtherNoHTobbCtr << "\n";
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
    std::cout << "UInt_t " << saveName << "PassVBFJetBVetoGenOtherNoHTobbCtr = " << passVBFJetBVetoGenOtherNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "PassVBFJetBVetoGenOtherNoHTobbWeightedCtr = " << passVBFJetBVetoGenOtherNoHTobbWeightedCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassVBFJetBVetoLepGenOtherNoHTobbCtr = " << passVBFJetBVetoLepGenOtherNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passVBFJetBVetoWeightedLepGenOtherNoHTobbCtr = " << passVBFJetBVetoWeightedLepGenOtherNoHTobbCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassVBFJetBVetoSemiLepGenOtherNoHTobbCtr = " << passVBFJetBVetoSemiLepGenOtherNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passVBFJetBVetoWeightedSemiLepGenOtherNoHTobbCtr = " << passVBFJetBVetoWeightedSemiLepGenOtherNoHTobbCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassVBFJetBVetoHadGenOtherNoHTobbCtr = " << passVBFJetBVetoHadGenOtherNoHTobbCtr << "\n";
    std::cout << "Double_t " << saveName << "passVBFJetBVetoWeightedHadGenOtherNoHTobbCtr = " << passVBFJetBVetoWeightedHadGenOtherNoHTobbCtr << "\n";
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
    passingEvLepTree->Write("",TObject::kOverwrite);
    passingEvSemiLepTree->Write("",TObject::kOverwrite);

    outFile->Close();

}