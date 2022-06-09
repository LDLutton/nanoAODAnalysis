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


void new062022LepCutsFoMAnalysis(string inputString){
    // Open the file. Note that the name of your file outside this class
    // will probably NOT be experiment.root.
    std::cout << "start Lep Cuts FoM Analysis\n";
    clock_t startt = clock();
    //Analyzer will run over all files put into fileAr


    //interpret input string
    std::string datasetString;
    std::string cutString;
    char delim[] = ";";
    std::stringstream ss(inputString);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, *delim)) {
        //elems.push_back(item);
        elems.push_back(std::move(item)); // if C++11 (based on comment from @mchiasson)
    }
    datasetString = elems[0];
    cutString = elems[1];
    std::cout << "start Lep " << cutString <<  "Cut FoM Analysis\n";


    float cutRangeBottom;
    float cutStep;
    float *cutPtr;

    std::vector<std::string> fileAr;
    if (cutString == "ePt") {
        cutRangeBottom = ePtRangeBottom;
        cutStep = ePtCutStep;
        cutPtr = &ePtCut;
    };
    if (cutString == "eEta") {
        cutRangeBottom = eEtaRangeBottom;
        cutStep = eEtaCutStep;
        cutPtr = &eEtaCut;
    };
    if (cutString == "mPt") {
        cutRangeBottom = mPtRangeBottom;
        cutStep = mPtCutStep;
        cutPtr = &mPtCut;
    };
    if (cutString == "mEta") {
        cutRangeBottom = mEtaRangeBottom;
        cutStep = mEtaCutStep;
        cutPtr = &mEtaCut;
    };
    if (cutString == "invMassCutLow") {
        cutRangeBottom = invMassCutLowRangeBottom;
        cutStep = invMassCutLowCutStep;
        cutPtr = &invMassCutLow;
    };
    if (cutString == "invMassCutHigh") {
        cutRangeBottom = invMassCutHighRangeBottom;
        cutStep = invMassCutHighCutStep;
        cutPtr = &invMassCutHigh;
    };
    if (cutString == "ptLead") {
        cutRangeBottom = ptLeadRangeBottom;
        cutStep = ptLeadCutStep;
        cutPtr = &ptLeadCut;
    };
    if (cutString == "ptTrailing") {
        cutRangeBottom = ptTrailingRangeBottom;
        cutStep = ptTrailingCutStep;
        cutPtr = &ptTrailingCut;
    };
    if (cutString == "fourLepInvMass") {
        cutRangeBottom = fourLepInvMassRangeBottom;
        cutStep = fourLepInvMassCutStep;
        cutPtr = &fourLepInvMassCut;
    };
    if (cutString == "optLepInvMass") {
        cutRangeBottom = optLepInvMassRangeBottom;
        cutStep = optLepInvMassCutStep;
        cutPtr = &optLepInvMassCut;
    };
    if (cutString == "lepIso") {
        cutRangeBottom = lepIsoRangeBottom;
        cutStep = lepIsoCutStep;
        cutPtr = &lepIsoCut;
    };
    if (cutString == "SIP") {
        cutRangeBottom = SIPRangeBottom;
        cutStep = SIPCutStep;
        cutPtr = &SIPCut;
    };
    if (cutString == "lDxy") {
        cutRangeBottom = lDxyRangeBottom;
        cutStep = lDxyCutStep;
        cutPtr = &lDxyCut;
    };
    if (cutString == "lDz") {
        cutRangeBottom = lDzRangeBottom;
        cutStep = lDzCutStep;
        cutPtr = &lDzCut;
    };
    if (cutString == "lMiniPFRelIso") {
        cutRangeBottom = lMiniPFRelIsoRangeBottom;
        cutStep = lMiniPFRelIsoCutStep;
        cutPtr = &lMiniPFRelIsoCut;
    };
    if (cutString == "eSieieBarrel") {
        cutRangeBottom = eSieieBarrelRangeBottom;
        cutStep = eSieieBarrelCutStep;
        cutPtr = &eSieieBarrelCut;
    };
    if (cutString == "eSieieEndcap") {
        cutRangeBottom = eSieieEndcapRangeBottom;
        cutStep = eSieieEndcapCutStep;
        cutPtr = &eSieieEndcapCut;
    };
    if (cutString == "eHoe") {
        cutRangeBottom = eHoeRangeBottom;
        cutStep = eHoeCutStep;
        cutPtr = &eHoeCut;
    };
    if (cutString == "eInvMinusPInv") {
        cutRangeBottom = eInvMinusPInvRangeBottom;
        cutStep = eInvMinusPInvCutStep;
        cutPtr = &eInvMinusPInvCut;
    };
    if (cutString == "ePromptMVA") {
        cutRangeBottom = ePromptMVARangeBottom;
        cutStep = ePromptMVACutStep;
        cutPtr = &ePromptMVACut;
    };
    if (cutString == "mPromptMVA") {
        cutRangeBottom = mPromptMVARangeBottom;
        cutStep = mPromptMVACutStep;
        cutPtr = &mPromptMVACut;
    };
    if (cutString == "lepJetDeepTagLoose") {
        cutRangeBottom = lepJetDeepTagLooseRangeBottom;
        cutStep = lepJetDeepTagLooseCutStep;
        cutPtr = &lepJetDeepTagLooseCut;
    };
    if (cutString == "lepJetDeepTagMedium") {
        cutRangeBottom = lepJetDeepTagMediumRangeBottom;
        cutStep = lepJetDeepTagMediumCutStep;
        cutPtr = &lepJetDeepTagMediumCut;
    };
    


    for (UInt_t rangeItr=0; rangeItr<cutAmnt+1; rangeItr++){
        cutPassAr.push_back(0);
        cutLepPassAr.push_back(0);
        cutSemiLepPassAr.push_back(0);
        cutHadPassAr.push_back(0);
        cutLepOrSemiLepPassAr.push_back(0);

        cutPassWeightedAr.push_back(0);
        cutLepPassWeightedAr.push_back(0);
        cutSemiLepPassWeightedAr.push_back(0);
        cutHadPassWeightedAr.push_back(0);
        cutLepOrSemiLepPassWeightedAr.push_back(0);

        cutRangeAr.push_back(cutRangeBottom+(rangeItr*cutStep));
    }






    std::string saveName;
    float crossSection = 1;
    float totWeight = 1;
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

    
    UInt_t passAnyChannelCtr = 0;
    UInt_t passLepAndSemiLepChannelCtr = 0;
    UInt_t passLepAndHadChannelCtr = 0;
    UInt_t passSemiLepAndHadChannelCtr = 0;
    UInt_t passAllChannelCtr = 0;
    UInt_t passVBFJets = 0;
    UInt_t passFatJets = 0;
    UInt_t passFJMatch = 0;
    UInt_t passLepCut = 0;
    UInt_t passSemiLepCut = 0;
    UInt_t passSemiLepLepCutCtr = 0;
    Double_t passSemiLepLepCutWeightedCtr = 0.;
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
            if (evCount % 1000 == 0) std::cout << "Event: " << evCount << "\n";
            if (debug){
                std::cout << "-------------------------\n";
                std::cout << evCount+1 << " starting cut loop\n";
            }
            //Increment event count
            evRunOver += 1;
            evCount += 1;

            UInt_t neLep = *nElectronL;
            UInt_t nmLep = *nMuonL;
            Double_t tmpGenWeights = *genWeightL;


            if (debug){
                std::cout << "Entering cut loop\n";
            }

            for (UInt_t rangeItr=0; rangeItr<cutAmnt+1; rangeItr++){
                if (debug) std::cout << "rangeItr " << rangeItr << " cutRangeAr[rangeItr] "<<cutRangeAr[rangeItr] << " \n";
                
                *cutPtr = cutRangeAr[rangeItr];
                if (debug) std::cout << "cutPtr " << cutPtr << " \n";

                
                elecCandIndAr.clear();
                muonCandIndAr.clear();

                eZ2VecPairAr.clear();
                mZ2VecPairAr.clear();
                


                bool passesCutsBool = false;
                bool passedAsLepBool = false;
                bool passedAsSemiLepBool = false;
                bool passedAsSemiLepLepCutBool = false;
                bool passedAsHadBool = false;



                
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
                doHiggsFatJetCut(nFatJetLen,hFatJet_pt_fromHTag,hFatJet_phi_fromHTag,hFatJet_eta_fromHTag,hFatJet_mass_fromHTag,hFatJet_HTag_fromHTag,hFatJet_ind_fromHTag,FatJet_particleNet_HbbvsQCDL,hFatJetParticleNetCut,FatJet_ptL,hFatJetPTCut,FatJet_jetIdL,FatJet_phiL,FatJet_etaL,FatJet_massL,dRCheckVecAr,dRCut,FJIndAr,ZPairPlusHInvMassCut,ZPairPlusHPtCut);
                
                if (hFatJet_pt_fromHTag == 0) continue;
                if (debug) std::cout << " found fat jet\n";

                
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
                if (debug) std::cout << "Entering jet loop. Len: " << nJetLen << "\n";
                doVBFJetCut(nJetLen,Jet_ptL,Jet_jetIdL,Jet_etaL,Jet_phiL,Jet_massL,jetPTCut,jetEtaDifCut,jetInvMassCut,jetPairInvMass,jetLeadPt,jetLeadEta,jetLeadPhi,jetTrailingPt,jetTrailingEta,jetTrailingPhi,leadJet_1,leadJet_2,dRCheckVecAr,dRCut,debug);
                //std::cout << jetLeadPt << endl;
                if (jetLeadPt == 0) continue;
                debugOutputForVBFJetCut(evCount,leadJet_1,leadJet_2,Jet_phiL,Jet_etaL,debug);
                passVBFJets += 1;

                if (passesCutsBool){
                    cutPassAr[rangeItr] += 1;

                    cutPassWeightedAr[rangeItr] += *genWeightL;
                    //std::cout << passedAsLepBool << " "<< passedAsSemiLepBool << " " << passedAsHadBool << "\n";
                    if (passedAsLepBool) {
                        cutLepPassAr[rangeItr] += 1;
                        cutLepOrSemiLepPassAr[rangeItr] += 1;

                        cutLepPassWeightedAr[rangeItr] += *genWeightL;
                        cutLepOrSemiLepPassWeightedAr[rangeItr] += *genWeightL;;
                        
                    }
                    
                    else if (passedAsSemiLepBool){
                        cutSemiLepPassAr[rangeItr] += 1;
                        cutLepOrSemiLepPassAr[rangeItr] += 1;

                        cutSemiLepPassWeightedAr[rangeItr] += *genWeightL;
                        cutLepOrSemiLepPassWeightedAr[rangeItr] += *genWeightL;
                    }
                    else if (passedAsHadBool) {
                        cutHadPassAr[rangeItr] += 1;
                        
                        cutHadPassWeightedAr[rangeItr] += *genWeightL;
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
    
    
    for (UInt_t rangeItr=0; rangeItr<cutAmnt+1; rangeItr++){
        std::cout << "cutRangeAr[rangeItr] " << cutRangeAr[rangeItr] << " cutPassAr[rangeItr] " << cutPassAr[rangeItr] << " cutLepPassAr[rangeItr] " << cutLepPassAr[rangeItr] << " cutSemiLepPassAr[rangeItr] " << cutSemiLepPassAr[rangeItr] << " cutLepOrSemiLepPassAr[rangeItr] " << cutLepOrSemiLepPassAr[rangeItr] << " cutHadPassAr[rangeItr] " << cutHadPassAr[rangeItr] << "\n";
    }
    std::cout << "std::vector<float> cutRangeAr = [";
    for (UInt_t rangeItr=0; rangeItr<cutAmnt; rangeItr++){
        std::cout << cutRangeAr[rangeItr] << ",";
    }
    std::cout << cutRangeAr[cutAmnt] << "];\n";

    std::cout << "std::vector<UInt_t> " << saveName << "PassAr = [";
    for (UInt_t rangeItr=0; rangeItr<cutAmnt; rangeItr++){
        std::cout << cutPassAr[rangeItr] << ",";
    }
    std::cout << cutPassAr[cutAmnt] << "];\n";

    std::cout << "std::vector<UInt_t> " << saveName << "LepPassAr = [";
    for (UInt_t rangeItr=0; rangeItr<cutAmnt; rangeItr++){
        std::cout << cutLepPassAr[rangeItr] << ",";
    }
    std::cout << cutLepPassAr[cutAmnt] << "];\n";

    std::cout << "std::vector<UInt_t> " << saveName << "SemiLepPassAr = [";
    for (UInt_t rangeItr=0; rangeItr<cutAmnt; rangeItr++){
        std::cout << cutSemiLepPassAr[rangeItr] << ",";
    }
    std::cout << cutSemiLepPassAr[cutAmnt] << "];\n";

    std::cout << "std::vector<UInt_t> " << saveName << "LepOrSemiLepPassAr = [";
    for (UInt_t rangeItr=0; rangeItr<cutAmnt; rangeItr++){
        std::cout << cutLepOrSemiLepPassAr[rangeItr] << ",";
    }
    std::cout << cutLepOrSemiLepPassAr[cutAmnt] << "];\n";

    std::cout << "std::vector<UInt_t> " << saveName << "HadPassAr = [";
    for (UInt_t rangeItr=0; rangeItr<cutAmnt; rangeItr++){
        std::cout << cutHadPassAr[rangeItr] << ",";
    }
    std::cout << cutHadPassAr[cutAmnt] << "];\n";

    //
    //
    //

    for (UInt_t rangeItr=0; rangeItr<cutAmnt+1; rangeItr++){
        std::cout << "cutRangeAr[rangeItr] " << cutRangeAr[rangeItr] << " cutPassWeightedAr[rangeItr] " << cutPassWeightedAr[rangeItr] << " cutLepPassWeightedAr[rangeItr] " << cutLepPassWeightedAr[rangeItr] << " cutSemiLepPassWeightedAr[rangeItr] " << cutSemiLepPassWeightedAr[rangeItr] << " cutLepOrSemiLepPassWeightedAr[rangeItr] " << cutLepOrSemiLepPassWeightedAr[rangeItr] << " cutHadPassWeightedAr[rangeItr] " << cutHadPassWeightedAr[rangeItr] << "\n";
    }
    std::cout << "std::vector<float> cutRangeAr = [";
    for (UInt_t rangeItr=0; rangeItr<cutAmnt; rangeItr++){
        std::cout << cutRangeAr[rangeItr] << ",";
    }
    std::cout << cutRangeAr[cutAmnt] << "];\n";

    std::cout << "std::vector<Double_t> " << saveName << "PassWeightedAr = [";
    for (UInt_t rangeItr=0; rangeItr<cutAmnt; rangeItr++){
        std::cout << cutPassWeightedAr[rangeItr]*crossSection*Run2Lumi/totWeight << ",";
    }
    std::cout << cutPassWeightedAr[cutAmnt]*crossSection*Run2Lumi/totWeight << "];\n";

    std::cout << "std::vector<Double_t> " << saveName << "LepPassWeightedAr = [";
    for (UInt_t rangeItr=0; rangeItr<cutAmnt; rangeItr++){
        std::cout << cutLepPassWeightedAr[rangeItr]*crossSection*Run2Lumi/totWeight << ",";
    }
    std::cout << cutLepPassWeightedAr[cutAmnt]*crossSection*Run2Lumi/totWeight << "];\n";

    std::cout << "std::vector<Double_t> " << saveName << "SemiLepPassWeightedAr = [";
    for (UInt_t rangeItr=0; rangeItr<cutAmnt; rangeItr++){
        std::cout << cutSemiLepPassWeightedAr[rangeItr]*crossSection*Run2Lumi/totWeight << ",";
    }
    std::cout << cutSemiLepPassWeightedAr[cutAmnt]*crossSection*Run2Lumi/totWeight << "];\n";

    std::cout << "std::vector<Double_t> " << saveName << "LepOrSemiLepPassWeightedAr = [";
    for (UInt_t rangeItr=0; rangeItr<cutAmnt; rangeItr++){
        std::cout << cutLepOrSemiLepPassWeightedAr[rangeItr]*crossSection*Run2Lumi/totWeight << ",";
    }
    std::cout << cutLepOrSemiLepPassWeightedAr[cutAmnt]*crossSection*Run2Lumi/totWeight << "];\n";

    std::cout << "std::vector<Double_t> " << saveName << "HadPassWeightedAr = [";
    for (UInt_t rangeItr=0; rangeItr<cutAmnt; rangeItr++){
        std::cout << cutHadPassWeightedAr[rangeItr]*crossSection*Run2Lumi/totWeight << ",";
    }
    std::cout << cutHadPassWeightedAr[cutAmnt]*crossSection*Run2Lumi/totWeight << "];\n";

}