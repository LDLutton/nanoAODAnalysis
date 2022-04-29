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
#include "new032022FoMAnalysis.h"
#include "new032022FoMAnalysis_Functions.h"
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


void new032022SemiLepPtLeadCutFoMAnalysis(string datasetString){
    // Open the file. Note that the name of your file outside this class
    // will probably NOT be experiment.root.
    std::cout << "start SemiLepPtLeadCut FoM Analysis\n";
    clock_t startt = clock();
    //Analyzer will run over all files put into fileAr

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

        cutRangeAr.push_back(ptLeadRangeBottom+(rangeItr*ptLeadCutStep));
    }

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
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisC2VEtaDifCut.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SDC2V3MC){
        saveName = "SDC2V3MC";
        isBackground = false;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisSDC2V3MCEtaDifCut.root";
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

        saveName = "ttHToBB";
        
        isBackground = true;
        totWeight = 4834432.8;
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
        saveName = "DY";

        isBackground = true;
        totWeight = 96233326;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisDY.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (QCDPT170to300Background){
        //saveName = "QCDPT170to300";
        
        crossSection = 103300.0;

        saveName = "QCDPT170to300";
        
        isBackground = true;
        totWeight = 29478000;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisQCDPT170to300.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (QCDPT300to470Background){
        //saveName = "QCDPT300to470";
        
        crossSection = 6826.0;

        saveName = "QCDPT300to470";
        
        isBackground = true;
        totWeight = 57868000;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisQCDPT300to470.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (QCDPT470to600Background){
        //saveName = "QCDPT470to600";
        
        crossSection = 552.6;
        
        saveName = "QCDPT470to600";

        isBackground = true;
        totWeight = 51062083.800000004;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisQCDPT470to600.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (QCDPT600to800Background){
        //saveName = "QCDPT600to800";
        
        crossSection = 156.6;

        saveName = "QCDPT600to800";
        
        isBackground = true;
        totWeight = 66914000;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisQCDPT600to800.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (QCDPT800to1000Background){
        //saveName = "QCDPT800to1000";
        
        crossSection = 26.32;

        saveName = "QCDPT800to1000";
        
        isBackground = true;
        totWeight = 36830000;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisQCDPT800to1000.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (QCDPT1000to1400Background){
        //saveName = "QCDPT1000to1400";
        
        crossSection = 7.5;

        saveName = "QCDPT1000to1400";
        
        isBackground = true;
        totWeight = 19664000;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisQCDPT1000to1400.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (QCDPT1400to1800Background){
        //saveName = "QCDPT1400to1800";
        
        crossSection = 0.6479;

        saveName = "QCDPT1400to1800";
        
        isBackground = true;
        totWeight = 10982000;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisQCDPT1400to1800.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (QCDPT1800to2400Background){
        //saveName = "QCDPT1800to2400";
        
        crossSection = 0.08715;

        saveName = "QCDPT1800to2400";
        
        isBackground = true;
        totWeight = 5491000;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisQCDPT1800to2400.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (QCDPT2400to3200Background){
        //saveName = "QCDPT2400to3200";
        
        crossSection = 0.005242;

        saveName = "QCDPT2400to3200";
        
        isBackground = true;
        totWeight = 2931000;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisQCDPT2400to3200.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (QCDPT3200toInfBackground){
        //saveName = "QCDPT3200toInf";
        
        crossSection = 0.0001349;

        saveName = "QCDPT3200toInf";
        
        isBackground = true;
        totWeight = 1000000;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisQCDPT3200toInf.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (TTJetsBackground){
        //saveName = "QCDPT3200toInf";
        
        crossSection = 722.8;

        saveName = "TTJets";
        
        isBackground = true;
        totWeight = 610815599000;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisTTJets.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (TTToHadronicBackground){
        //saveName = "QCDPT3200toInf";
        
        crossSection = 377.96;

        saveName = "TTToHadronic";
        
        isBackground = true;
        totWeight = 643;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisTTToHadronic.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (TTTo2L2NuBackground){
        //saveName = "QCDPT3200toInf";
        
        crossSection = 88.29;

        saveName = "TTTo2L2Nu";
        
        isBackground = true;
        totWeight = 643;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisTTTo2L2Nu.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (TTToSemiLeptonicBackground){
        //saveName = "QCDPT3200toInf";
        
        crossSection = 365.34;

        saveName = "TTToSemiLeptonic";
        
        isBackground = true;
        totWeight = 643;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisTTToSemiLeptonic.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (ST_s_ChannelBackground){
        //saveName = "QCDPT3200toInf";
        
        crossSection = 3.74;

        saveName = "ST_s_Channel";
        
        isBackground = true;
        totWeight = 68767088;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisST_s_Channel.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (ST_t_ChannelAntiTopBackground){
        //saveName = "QCDPT3200toInf";
        
        crossSection = 69.09;

        saveName = "ST_t_ChannelAntiTop";
        
        isBackground = true;
        totWeight = 6014529940;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisST_t_ChannelAntiTop.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (ST_t_ChannelTopBackground){
        //saveName = "QCDPT3200toInf";
        
        crossSection = 115.3;

        saveName = "ST_t_ChannelTop";
        
        isBackground = true;
        totWeight = 18955976000;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisST_t_ChannelTop.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (ZZTo2Q2NuBackground){
        //saveName = "QCDPT3200toInf";
        
        crossSection = 4.561;

        saveName = "ZZTo2Q2Nu";
        
        isBackground = true;
        totWeight = 137620470.60000002;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisZZTo2Q2Nu.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (WWTo2L2NuBackground){
        //saveName = "QCDPT3200toInf";
        
        crossSection = 10.48;

        saveName = "WWTo2L2Nu";
        
        isBackground = true;
        totWeight = 110795338.10000001;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisWWTo2L2Nu.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (WZTo3LNuBackground){
        //saveName = "QCDPT3200toInf";
        
        crossSection = 5.052;

        saveName = "WZTo3LNu";
        
        isBackground = true;
        totWeight = 83145925.5;
        std::string tmpStrWithPath = strAdd+"HLTFilteredForAnalysisWZTo3LNu.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (testRun){
        saveName = "testRun";
        fileAr.push_back("./HLTFilteredForAnalysistestRun.root");
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


    UInt_t passHLTCtr = 0;
    UInt_t passAnyChannelCtr = 0;
    UInt_t passLepChannelCtr = 0;
    UInt_t passSemiLepChannelCtr = 0;
    UInt_t passHadChannelCtr = 0;
    UInt_t passLepAndSemiLepChannelCtr = 0;
    UInt_t passLepAndHadChannelCtr = 0;
    UInt_t passSemiLepAndHadChannelCtr = 0;
    UInt_t passAllChannelCtr = 0;
    UInt_t passVBFJets = 0;
    UInt_t passFatJets = 0;
    UInt_t passFJMatch = 0;
    UInt_t passLepCut = 0;
    UInt_t passSemiLepCut = 0;
    UInt_t passHadCut = 0;

    UInt_t passChannelCtr = 0;

    UInt_t ZFJSameJetCtr = 0;

    UInt_t tryingLepCtr = 0;
    UInt_t tryingSemiLepCtr = 0;
    UInt_t tryingHadCtr = 0;

    UInt_t passesCutsCtr = 0;

    
    UInt_t datanEv;
    UInt_t datanEvPass;

    UInt_t evCount = 0;
    UInt_t evRunOver = 0;


    
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
        TTreeReaderArray<Float_t> FatJet_deepTag_HL(myEventsReader, "FatJet_deepTag_HL");
        TTreeReaderArray<Float_t> FatJet_deepTag_ZvsQCDL(myEventsReader, "FatJet_deepTag_ZvsQCDL");

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

        //Muons
        TTreeReaderValue<UInt_t> nMuonL(myEventsReader, "nMuonL");
        TTreeReaderArray<Float_t> Muon_etaL(myEventsReader, "Muon_etaL");
        TTreeReaderArray<Float_t> Muon_massL(myEventsReader, "Muon_massL");
        TTreeReaderArray<Int_t> Muon_chargeL(myEventsReader, "Muon_chargeL");
        TTreeReaderArray<Float_t> Muon_phiL(myEventsReader, "Muon_phiL");
        TTreeReaderArray<Float_t> Muon_ptL(myEventsReader, "Muon_ptL");
        TTreeReaderArray<Float_t> Muon_pfRelIso03_allL(myEventsReader, "Muon_pfRelIso03_allL");
        TTreeReaderArray<Float_t> Muon_sip3dL(myEventsReader, "Muon_sip3dL");

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
                crossSection = *crossSectionVar;
            }
        }
        while (myEvNumReader.Next()){
            datanEv = *nEv;
            datanEvPass = *nEvPass;
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
                std::cout << evCount+1 << " starting jets loop\n";
            }
            //Increment event count
            evRunOver += 1;
            evCount += 1;

            //tmpZ1Vec.clear();
            
            elecCandIndAr.clear();
            muonCandIndAr.clear();

            eZ2VecPairAr.clear();
            mZ2VecPairAr.clear();


            bool passesCutsBool = false;
            bool passedAsLepBool = false;
            bool passedAsSemiLepBool = false;
            bool passedAsHadBool = false;
            

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

            vector<float> selectedFJ_phi;
            vector<float> selectedFJ_eta;

            //doHiggsFatJetCut(nFatJetLen,hFatJet_HTag_fromPt,hFatJet_pt_fromPt,hFatJet_phi_fromPt,hFatJet_eta_fromPt,hFatJet_mass_fromPt,hFatJet_pt_fromHTag,hFatJet_phi_fromHTag,hFatJet_eta_fromHTag,hFatJet_mass_fromHTag,hFatJet_HTag_fromHTag,hFatJet_ind_fromHTag,FatJet_deepTag_HL,hFatJetDeepTagCut,FatJet_ptL,hFatJetPTCut,FatJet_jetIdL,FatJet_phiL,FatJet_etaL,jetLeadPhi,jetLeadEta,jetTrailingPhi,jetTrailingEta,hFatJetdRCut,FatJet_massL);
            
            doHiggsFatJetCut(nFatJetLen,hFatJet_pt_fromHTag,hFatJet_phi_fromHTag,hFatJet_eta_fromHTag,hFatJet_mass_fromHTag,hFatJet_HTag_fromHTag,hFatJet_ind_fromHTag,FatJet_deepTag_HL,hFatJetDeepTagCut,FatJet_ptL,hFatJetPTCut,FatJet_jetIdL,FatJet_phiL,FatJet_etaL,FatJet_massL,selectedFJ_phi,selectedFJ_eta);
            
            if (hFatJet_pt_fromHTag == 0) continue;
            if (debug) std::cout << " found fat jet\n";
            passFatJets += 1;


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
                
                
                
            doLeptonicCuts(Electron_etaL,Electron_massL,Electron_chargeL,Electron_phiL,Electron_ptL, neLep, elecCandIndAr, elecCandVecAr, elecCandChargeAr,negElecCands,posElecCands,totElecCands,enoughElecCands,negMuonCands,posMuonCands,totMuonCands,enoughMuonCands,enoughLepCands,ePtCut,eEtaCut,
            Muon_etaL,Muon_massL, Muon_chargeL,Muon_phiL,Muon_ptL, nmLep, muonCandIndAr, muonCandVecAr, muonCandChargeAr,mPtCut,mEtaCut,
            Z1IsMuon,invMassCutLow,invMassCutHigh,ptLeadCut,ptTrailingCut,
            Z1LeadPt,Z1TrailingPt,Z1LeadItr,Z1TrailingItr,Z1LeadVec,Z1TrailingVec,Z1LeadCharge,Z1TrailingCharge,difFromZMassOne,
            eZ2VecPairAr,tmpZ2Ind,Z2IsMuon,tmpTopZ2LeadPt,tmpTopZ2TrailingPt,fourLepInvMassCut,optLepInvMassCut,
            mZ2VecPairAr,
            tmpZ1Vec,tmpZ1M,
            Electron_dr03EcalRecHitSumEtL,Electron_dr03TkSumPtL,Electron_dr03HcalDepth1TowerSumEtL,Electron_pfRelIso03_allL,
            Z1LeadIso,Muon_pfRelIso03_allL,Z1TrailingIso,Z2LeadIso,Z2TrailingIso,lepIsoCut,
            Z1LeadSIP,Electron_sip3dL,Z1TrailingSIP,Z2LeadSIP,Muon_sip3dL,Z2TrailingSIP,SIPCut,passLepCut,passesCutsBool,passedAsLepBool,
            debug);

            
            if (debug) std::cout << "passesCutsBool " << passesCutsBool << "\n";
            bool oldPassesCutsBool = passesCutsBool;
            bool oldPassedAsSemiLepBool = passedAsSemiLepBool;
            bool oldPassedAsHadBool = passedAsHadBool; 
            for (UInt_t rangeItr=0; rangeItr<cutAmnt+1; rangeItr++){
                float tmpPtLeadCutVal = cutRangeAr[rangeItr];
                Int_t FJInd;
                passesCutsBool = oldPassesCutsBool;
                passedAsSemiLepBool = oldPassedAsSemiLepBool;
                passedAsHadBool = oldPassedAsHadBool;

                if ((!passesCutsBool)){
                    if (debug) std::cout << "trying SemiLeptonic\n";
                    tryingSemiLepCtr += 1;
                    FJInd = -1;
                    UInt_t numFatJet = *nFatJetL;
                    
                    //std::cout << rangeItr << " " << tmpFatJetPTCutVal << "\n";
                    doSemiLepChanFatJetCut(FJInd,numFatJet,hFatJet_ind_fromHTag,fatJetPTCut,fatJetZTagCut,FatJet_ptL,FatJet_phiL,FatJet_etaL,FatJet_deepTag_ZvsQCDL,selectedFJ_phi,selectedFJ_eta);
                    /*
                    for (UInt_t i=0; i<*nFatJet;i++){
                        tmpFatJetPT = FatJet_ptL[i];
                        if (tmpFatJetPT > fatJetPTCut) FJInd = i;
                    }
                    */
                   //Replacing ptLeadCut
                    doSemiLepCut(FJInd,enoughElecCands,negElecCands,posElecCands,totElecCands,Electron_etaL,Electron_massL,Electron_chargeL,Electron_phiL,Electron_ptL,neLep,elecCandIndAr,elecCandVecAr,elecCandChargeAr,ePtCut,eEtaCut,
                    enoughMuonCands,negMuonCands,posMuonCands,totMuonCands,Muon_etaL,Muon_massL,Muon_chargeL,Muon_phiL,Muon_ptL,nmLep,muonCandIndAr,muonCandVecAr,muonCandChargeAr,mPtCut,mEtaCut,
                    enoughLepCands,invMassCutLow,invMassCutHigh,tmpPtLeadCutVal,ptTrailingCut,Z1Cand,difFromZMassOne,Z1LeadItr,Z1TrailingItr,Z1LeadPt,Z1TrailingPt,Z1IsMuon,Z1LeadVec,Z1TrailingVec,Z1LeadCharge,Z1TrailingCharge,
                    Electron_dr03EcalRecHitSumEtL,Electron_dr03TkSumPtL,Electron_dr03HcalDepth1TowerSumEtL,Electron_pfRelIso03_allL,
                    Z1LeadIso,Muon_pfRelIso03_allL,Z1TrailingIso,
                    passSemiLepCut,passesCutsBool,passedAsSemiLepBool,
                    debug);
                }
                if (debug) std::cout << "Test\n";
                if ((!passesCutsBool)){
                    tryingHadCtr += 1;
                    LFJOneInd = -1;
                    LFJTwoInd = -1;
                    if (debugHadronic) std::cout << "---------------- Event " << evCount - 1 << " ----------------\n";
                    //if (debugHadronic) std::cout << "hFatJet_ind_fromHTag " << hFatJet_ind_fromHTag << "\n";
                    if (debugHadronic) std::cout << "fatJetPTCut " << fatJetPTCut << "\n";

                    if (debugHadronic) std::cout << "--------- Entering FJ loop for Hadronic Channel ---------\n";

                    UInt_t numFatJet = *nFatJetL;
                    doHadChanFatJetCut(LFJOneInd,LFJTwoInd,numFatJet,hFatJet_ind_fromHTag,fatJetPTCut,fatJetZPairInvMassCut,FatJet_ptL,FatJet_phiL,FatJet_etaL,FatJet_massL,FatJet_deepTag_ZvsQCDL,selectedFJ_phi,selectedFJ_eta,hFatJet_pt_fromHTag);

                    
                    if (LFJOneInd != LFJTwoInd){
                        passHadCut += 1;
                        passesCutsBool = true;
                        passedAsHadBool = true;
                    }
                }
                if ((!passesCutsBool)) continue;
                else passChannelCtr += 1;

            
                
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
            
                //std::cout << tmpVBFJetdRCutVal << "\n";
                
                doVBFJetCut(nJetLen,Jet_ptL,Jet_jetIdL,Jet_etaL,Jet_phiL,Jet_massL,jetPTCut,jetEtaDifCut,jetInvMassCut,jetPairInvMass,jetLeadPt,jetLeadEta,jetLeadPhi,jetTrailingPt,jetTrailingEta,jetTrailingPhi,leadJet_1,leadJet_2,selectedFJ_phi,selectedFJ_eta,VBFJetdRCut,debug);
                //std::cout << jetLeadPt << endl;
                if (jetLeadPt == 0) continue;
                debugOutputForVBFJetCut(evCount,leadJet_1,leadJet_2,Jet_phiL,Jet_etaL,debug);
                /*
                if (debug){
                    std::cout << " found jet pairs\n";
                    std::cout << evCount+1 << " selected jet pair\n";
                    std::cout << "Lead jet ind    " << leadJet_1 << "\n";
                    std::cout << "Trailing jet ind    " << leadJet_2 << "\n";
                    std::cout << "Lead jet phi    " << Jet_phi[leadJet_1] << "\n";
                    std::cout << "Trailing jet phi    " << Jet_phi[leadJet_2] << "\n";
                    std::cout << "Lead jet eta    " << Jet_etaL[leadJet_1] << "\n";
                    std::cout << "Trailing jet eta    " << Jet_etaL[leadJet_2] << "\n";
                }
                */
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
                    /*
                    if (debug) std::cout << "Passed cuts. Now filling trees\n";
                    passesCutsCtr += 1;
                    //Fill tree
                    if (debug) std::cout << "Filling jets\n";
                    nJetFullPassL = *nJetL;
                    jetLeadPtFullPassL = jetLeadPt;
                    jetTrailingPtFullPassL = jetTrailingPt;
                    jetLeadPhiFullPassL = jetLeadPhi;
                    jetTrailingPhiFullPassL = jetTrailingPhi;
                    jetPairInvMassFullPassL = jetPairInvMass;
                    jetLeadEtaFullPassL = jetLeadEta;
                    jetTrailingEtaFullPassL = jetTrailingEta;
                    //now fat jets
                    if (debug) std::cout << "Filling fat jets\n";
                    nFatJetFullPassL = *nFatJetL;
                    hFatJet_pt_fromHTagFullPassL = hFatJet_pt_fromHTag;
                    hFatJet_phi_fromHTagFullPassL = hFatJet_phi_fromHTag;
                    hFatJet_eta_fromHTagFullPassL = hFatJet_eta_fromHTag;
                    hFatJet_mass_fromHTagFullPassL = hFatJet_mass_fromHTag;
                    hFatJet_HTag_fromHTagFullPassL = hFatJet_HTag_fromHTag;
                    

                    //Branches for distinguishing between channels
                    
                    passedLepFullPassL = passedAsLepBool ;
                    passedSemiLepFullPassL = passedAsSemiLepBool;
                    passedHadFullPassL = passedAsHadBool;

                    FATree->Fill();



                    if (debug) std::cout << "Filling channel branches \n";
                    evPassCount += 1;
                    ROOT::Math::PtEtaPhiMVector tmpZ2LeadVec;
                    ROOT::Math::PtEtaPhiMVector tmpZ2TrailingVec;
                    ROOT::Math::PtEtaPhiMVector tmpZ2Vec;
                    */

                }

            }

        }
    }
    if (debug) std::cout << "Filling complete \n";

    clock_t endt = clock();
    double time_spent = (double)(endt - startt) / CLOCKS_PER_SEC;


    std::cout << "Finished file loop. " << "time: " << time_spent << "\n";
    if (!isBackground){
        std::cout << "XS: " << crossSection << "\n";
    }
    std::cout << "nEv total: " << datanEv << "\n";
    std::cout << "nEv post HLT: " << datanEvPass << "\n"; 
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

    std::cout << "std::vector<Double_t> " << saveName << "PassAr = [";
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

    /*
    nEv = evRunOver;
    nEvPass = evPassCount;
    evNumTree->Fill();

    std::cout << "evRunOver: " << evRunOver << " -------------------\n";
    std::cout << "passes HLT cut: " << passHLTCtr << " -------------------\n";
    std::cout << "passes channel cut: " << passAnyChannelCtr << " -------------------\n";
    std::cout << "passes lep channel cut: " << passLepChannelCtr << "\n";
    std::cout << "passes semi lep channel cut: " << passSemiLepChannelCtr << "\n";
    std::cout << "passes had channel cut: " << passHadChannelCtr << "\n";
    std::cout << "passes lep and semi lep channel cut: " << passLepAndSemiLepChannelCtr << "\n";
    std::cout << "passes lep and had channel cut: " << passLepAndHadChannelCtr << "\n";
    std::cout << "passes semi lep and had channel cut: " << passSemiLepAndHadChannelCtr << "\n";
    std::cout << "passes all channel cut: " << passAllChannelCtr << "\n";
    std::cout << "passes Higgs FatJet cut: " << passFatJets << "\n";
    std::cout << "passes actual channel cut: " << passChannelCtr << "\n";
    std::cout << "passes in lep channel: " << passLepCut << "\n";
    std::cout << "passes in semi lep channel: " << passSemiLepCut << "\n";
    std::cout << "passes in had channel: " << passHadCut << "\n";
    std::cout << "passes VBF Jet cut: " << passVBFJets << " -------------------\n";
    

    std::cout << "passes all cuts: " << passesCutsCtr << " -------------------\n";
    std::cout << "evPassCount: " << evPassCount << "\n";

    if (!isBackground){
        std::cout << "Cross section average before division: " << crossSectionAvg << "\n";
        std::cout << "Cross section counter: " << crossSectionCtr << "\n";
        crossSectionAvg = crossSectionAvg / crossSectionCtr;
        std::cout << "Cross section average after division: " << crossSectionAvg << "\n";
        //XS Tree
        float crossSectionVar;
        TTree* crossSectionTree = new TTree("crossSectionTree","crossSectionTree");
        crossSectionTree->Branch("crossSectionVar",&crossSectionVar,"crossSectionVar/F");
        crossSectionVar = crossSectionAvg;
        crossSectionTree->Fill();
        crossSectionTree->Write("",TObject::kOverwrite);
    }

    outFile->cd();
    evNumTree->Write("",TObject::kOverwrite);
    FATree->Write("",TObject::kOverwrite);

    outFile->Close();
    */
}