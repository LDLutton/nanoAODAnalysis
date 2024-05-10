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
void finish042024DataPreselection(string datasetString,uint yearInd){
    // Open the file. Note that the name of your file outside this class
    // will probably NOT be experiment.root.
    std::cout << "start Analysis\n";
    clock_t startt = clock();
    //Analyzer will run over all files put into fileAr

    //gInterpreter->GenerateDictionary("vector<vector<vector<Double_t> > >", "vector");
    //gInterpreter->GenerateDictionary("vector<vector<vector<Int_t> > >", "vector");

    std::vector<std::string> fileAr;
    string NoSLString = "";
    if (!useSingleLepHLT){
        NoSLString = "_NoSLHLT";
    }


    std::string saveName;
    bool isBackground = false;
    bool SDC2V2MCZZHReweightTrimmed = false;
    bool SDC2V2MCZZH17ReweightTrimmed = false;
    bool SDC2V2MCZZH16ReweightTrimmed = false;
    bool SDC2V2MCZZH16APVReweightTrimmed = false;
    bool SDC2V2MCWZHReweightTrimmed = false;
    bool SDC2V2MCWZH17ReweightTrimmed = false;
    bool SDC2V2MCWZH16ReweightTrimmed = false;
    bool SDC2V2MCWZH16APVReweightTrimmed = false;

    if (datasetString == "testRun") testRun = true;
    if (datasetString == "SDC2V2MCZZHReweightTrimmed") SDC2V2MCZZHReweightTrimmed = true;
    if (datasetString == "SDC2V2MCZZH17ReweightTrimmed") SDC2V2MCZZH17ReweightTrimmed = true;
    if (datasetString == "SDC2V2MCZZH16ReweightTrimmed") SDC2V2MCZZH16ReweightTrimmed = true;
    if (datasetString == "SDC2V2MCZZH16APVReweightTrimmed") SDC2V2MCZZH16APVReweightTrimmed = true;
    if (datasetString == "SDC2V2MCWZHReweightTrimmed") SDC2V2MCWZHReweightTrimmed = true;
    if (datasetString == "SDC2V2MCWZH17ReweightTrimmed") SDC2V2MCWZH17ReweightTrimmed = true;
    if (datasetString == "SDC2V2MCWZH16ReweightTrimmed") SDC2V2MCWZH16ReweightTrimmed = true;
    if (datasetString == "SDC2V2MCWZH16APVReweightTrimmed") SDC2V2MCWZH16APVReweightTrimmed = true;

    if (datasetString == "LaraTest") LaraTest = true;

    ////////////////////////////////GETTING DATASET////////////////////////////////
    ////////////////////////////////GETTING DATASET////////////////////////////////
    ////////////////////////////////GETTING DATASET////////////////////////////////
    ////////////////////////////////GETTING DATASET////////////////////////////////

    std::string strAdd;
    if (scratchDown) strAdd ="/afs/crc.nd.edu/user/d/dlutton/Public/condorStuff/NanoAODToHistos/tmpHoldForNanoAODWithoutScratch/";
    else strAdd ="/scratch365/dlutton/HLTFilteredFiles/";

    float totWeight = 1;
    //precalculate this
    double XS = 1;

    UInt_t datasetType = 0;
    UInt_t yearType = 0;

    
    if (ttHToBBTrimmedBackground){
        //saveName = "ttHToBB";
        crossSection = 0.5071*0.582;

        saveName = "ttHToBB";
        
        
        //int arrSize = sizeof(ttHToBBBackgroundAr)/sizeof(ttHToBBBackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //ttHToBBBackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //ttHToBBBackgroundAr[fileInd]);
    }
    else if (ttZJetsTrimmedBackground){
        //saveName = "ttZJets";
        
        crossSection = 0.5407;
        saveName = "ttZJets";
        
        //int arrSize = sizeof(ttZJetsBackgroundAr)/sizeof(ttZJetsBackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //ttZJetsBackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //ttZJetsBackgroundAr[fileInd]);
    }
    else if (ttWJetsTrimmedBackground){
        
        crossSection = 0.4611;
        saveName = "ttWJets";
        
        //int arrSize = sizeof(ttWJetsBackgroundAr)/sizeof(ttWJetsBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //ttWJetsBackgroundAr[fileInd]);
    }
    else if (DYTrimmedBackground){
        //saveName = "DY";
        
        crossSection = 5364;
        saveName = "DY";

        
        //int arrSize = sizeof(DYBackgroundAr)/sizeof(DYBackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //DYBackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //DYBackgroundAr[fileInd]);
    }
    else if (QCDPT170to300TrimmedBackground){
        //saveName = "QCDPT170to300";
        
        crossSection = 103300.0;

        saveName = "QCDPT170to300";
        
        
        //int arrSize = sizeof(QCDPT170to300BackgroundAr)/sizeof(QCDPT170to300BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //QCDPT170to300BackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //QCDPT170to300BackgroundAr[fileInd]);
    }
    else if (QCDPT300to470TrimmedBackground){
        //saveName = "QCDPT300to470";
        
        crossSection = 6826.0;

        saveName = "QCDPT300to470";
        
        
        //int arrSize = sizeof(QCDPT300to470BackgroundAr)/sizeof(QCDPT300to470BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //QCDPT300to470BackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //QCDPT300to470BackgroundAr[fileInd]);
    }
    else if (QCDPT470to600TrimmedBackground){
        //saveName = "QCDPT470to600";
        
        crossSection = 552.6;
        
        saveName = "QCDPT470to600";

        
        //int arrSize = sizeof(QCDPT470to600BackgroundAr)/sizeof(QCDPT470to600BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //QCDPT470to600BackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //QCDPT470to600BackgroundAr[fileInd]);
    }
    else if (QCDPT600to800TrimmedBackground){
        //saveName = "QCDPT600to800";
        
        crossSection = 156.6;

        saveName = "QCDPT600to800";
        
        
        //int arrSize = sizeof(QCDPT600to800BackgroundAr)/sizeof(QCDPT600to800BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //QCDPT600to800BackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //QCDPT600to800BackgroundAr[fileInd]);
    }
    else if (QCDPT800to1000TrimmedBackground){
        //saveName = "QCDPT800to1000";
        
        crossSection = 26.32;

        saveName = "QCDPT800to1000";
        
        
        //int arrSize = sizeof(QCDPT800to1000BackgroundAr)/sizeof(QCDPT800to1000BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //QCDPT800to1000BackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //QCDPT800to1000BackgroundAr[fileInd]);
    }
    else if (QCDPT1000to1400TrimmedBackground){
        //saveName = "QCDPT1000to1400";
        
        crossSection = 7.5;

        saveName = "QCDPT1000to1400";
        
        
        //int arrSize = sizeof(QCDPT1000to1400BackgroundAr)/sizeof(QCDPT1000to1400BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //QCDPT1000to1400BackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //QCDPT1000to1400BackgroundAr[fileInd]);
    }
    else if (QCDPT1400to1800TrimmedBackground){
        //saveName = "QCDPT1400to1800";
        
        crossSection = 0.6479;

        saveName = "QCDPT1400to1800";
        
        
        //int arrSize = sizeof(QCDPT1400to1800BackgroundAr)/sizeof(QCDPT1400to1800BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //QCDPT1400to1800BackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //QCDPT1400to1800BackgroundAr[fileInd]);
    }
    else if (QCDPT1800to2400TrimmedBackground){
        //saveName = "QCDPT1800to2400";
        
        crossSection = 0.08715;

        saveName = "QCDPT1800to2400";
        
        
        //int arrSize = sizeof(QCDPT1800to2400BackgroundAr)/sizeof(QCDPT1800to2400BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //QCDPT1800to2400BackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //QCDPT1800to2400BackgroundAr[fileInd]);
    }
    else if (QCDPT2400to3200TrimmedBackground){
        //saveName = "QCDPT2400to3200";
        
        crossSection = 0.005242;

        saveName = "QCDPT2400to3200";
        
        
        //int arrSize = sizeof(QCDPT2400to3200BackgroundAr)/sizeof(QCDPT2400to3200BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //QCDPT2400to3200BackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //QCDPT2400to3200BackgroundAr[fileInd]);
    }
    else if (QCDPT3200toInfTrimmedBackground){
        //saveName = "QCDPT3200toInf";
        
        crossSection = 0.0001349;

        saveName = "QCDPT3200toInf";
        
        
        //int arrSize = sizeof(QCDPT3200toInfBackgroundAr)/sizeof(QCDPT3200toInfBackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //QCDPT3200toInfBackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //QCDPT3200toInfBackgroundAr[fileInd]);
    }
    else if (QCDHT50to100TrimmedBackground){
        //saveName = "QCDHT50to100";
        
        crossSection = 187700000.;

        saveName = "QCDHT50to100";
        
        
        //int arrSize = sizeof(QCDHT50to100BackgroundAr)/sizeof(QCDHT50to100BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //QCDHT50to100BackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //QCDHT50to100BackgroundAr[fileInd]);
    }
    else if (QCDHT100to200TrimmedBackground){
        //saveName = "QCDHT100to200";
        
        crossSection = 23640000.0;

        saveName = "QCDHT100to200";
        
        
        //int arrSize = sizeof(QCDHT100to200BackgroundAr)/sizeof(QCDHT100to200BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //QCDHT100to200BackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //QCDHT100to200BackgroundAr[fileInd]);
    }
    else if (QCDHT200to300TrimmedBackground){
        //saveName = "QCDHT200to300";
        
        crossSection = 1546000.0;

        saveName = "QCDHT200to300";
        
        
        //int arrSize = sizeof(QCDHT200to300BackgroundAr)/sizeof(QCDHT200to300BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //QCDHT200to300BackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //QCDHT200to300BackgroundAr[fileInd]);
    }
    else if (QCDHT300to500TrimmedBackground){
        //saveName = "QCDHT300to500";
        
        crossSection = 321600.0;

        saveName = "QCDHT300to500";
        
        
        //int arrSize = sizeof(QCDHT300to500BackgroundAr)/sizeof(QCDHT300to500BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //QCDHT300to500BackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //QCDHT300to500BackgroundAr[fileInd]);
    }
    else if (QCDHT500to700TrimmedBackground){
        //saveName = "QCDHT500to700";
        
        crossSection = 30980.0;

        saveName = "QCDHT500to700";
        
        
        //int arrSize = sizeof(QCDHT500to700BackgroundAr)/sizeof(QCDHT500to700BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //QCDHT500to700BackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //QCDHT500to700BackgroundAr[fileInd]);
    }
    else if (QCDHT700to1000TrimmedBackground){
        //saveName = "QCDHT700to1000";
        
        crossSection = 6364.0;

        saveName = "QCDHT700to1000";
        
        
        //int arrSize = sizeof(QCDHT700to1000BackgroundAr)/sizeof(QCDHT700to1000BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //QCDHT700to1000BackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //QCDHT700to1000BackgroundAr[fileInd]);
    }
    else if (QCDHT1000to1500TrimmedBackground){
        //saveName = "QCDHT1000to1500";
        
        crossSection = 1117.0;

        saveName = "QCDHT1000to1500";
        
        
        //int arrSize = sizeof(QCDHT1000to1500BackgroundAr)/sizeof(QCDHT1000to1500BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //QCDHT1000to1500BackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //QCDHT1000to1500BackgroundAr[fileInd]);
    }
    else if (QCDHT1500to2000TrimmedBackground){
        //saveName = "QCDHT1500to2000";
        
        crossSection = 108.4;

        saveName = "QCDHT1500to2000";
        
        
        //int arrSize = sizeof(QCDHT1500to2000BackgroundAr)/sizeof(QCDHT1500to2000BackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //QCDHT1500to2000BackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //QCDHT1500to2000BackgroundAr[fileInd]);
    }
    else if (QCDHT2000toInfTrimmedBackground){
        //saveName = "QCDHT2000toInf";
        
        crossSection = 22.36;

        saveName = "QCDHT2000toInf";
        
        
        //int arrSize = sizeof(QCDHT2000toInfBackgroundAr)/sizeof(QCDHT2000toInfBackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //QCDHT2000toInfBackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //QCDHT2000toInfBackgroundAr[fileInd]);
    }
    else if (TTJetsTrimmedBackground){
        //saveName = "";
        
        crossSection = 722.8;

        saveName = "TTJets";
        
        
        //int arrSize = sizeof(TTJetsBackgroundAr)/sizeof(TTJetsBackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //TTJetsBackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //TTJetsBackgroundAr[fileInd]);
    }
    else if (TTToHadronicTrimmedBackground){
        //saveName = "";
        
        crossSection = 377.96;

        saveName = "TTJetsHadronic";
        
        
        //int arrSize = sizeof(TTJetsHadronicBackgroundAr)/sizeof(TTJetsHadronicBackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //TTJetsHadronicBackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //TTJetsHadronicBackgroundAr[fileInd]);
    }
    else if (TTToSemiLeptonicTrimmedBackground){
        //saveName = "";
        
        crossSection = 365.346;

        saveName = "TTJetsSemiLeptonic";
        
        
        //int arrSize = sizeof(TTJetsSemiLeptonicBackgroundAr)/sizeof(TTJetsSemiLeptonicBackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //TTJetsSemiLeptonicBackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //TTJetsSemiLeptonicBackgroundAr[fileInd]);
    }
    else if (TTTo2L2NuTrimmedBackground){
        //saveName = "";
        
        crossSection = 88.29;

        saveName = "TTJets2L2Nu";
        
        
        //int arrSize = sizeof(TTJets2L2NuBackgroundAr)/sizeof(TTJets2L2NuBackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //TTJets2L2NuBackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //TTJets2L2NuBackgroundAr[fileInd]);
    }
    else if (ST_s_ChannelTrimmedBackground){
        //saveName = "";
        
        crossSection = 3.74;

        saveName = "ST_s_Channel";
        
        
        //int arrSize = sizeof(ST_s_ChannelBackgroundAr)/sizeof(ST_s_ChannelBackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //ST_s_ChannelBackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //ST_s_ChannelBackgroundAr[fileInd]);
    }
    else if (ST_t_ChannelAntiTopTrimmedBackground){
        //saveName = "";
        
        crossSection = 69.09;

        saveName = "ST_t_ChannelAntiTop";
        
        
        //int arrSize = sizeof(ST_t_ChannelAntiTopBackgroundAr)/sizeof(ST_t_ChannelAntiTopBackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //ST_t_ChannelAntiTopBackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //ST_t_ChannelAntiTopBackgroundAr[fileInd]);
    }
    else if (ST_t_ChannelTopTrimmedBackground){
        //saveName = "";
        
        crossSection = 115.3;

        saveName = "ST_t_ChannelTop";
        
        
        //int arrSize = sizeof(ST_t_ChannelTopBackgroundAr)/sizeof(ST_t_ChannelTopBackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //ST_t_ChannelTopBackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //ST_t_ChannelTopBackgroundAr[fileInd]);
    }
    else if (ZZTrimmedBackground){
        //saveName = "";
        
        crossSection = 12.17;

        saveName = "ZZ";
        
        
        //int arrSize = sizeof(ZZBackgroundAr)/sizeof(ZZBackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //ZZBackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //ZZBackgroundAr[fileInd]);
    }
    else if (WWTrimmedBackground){
        //saveName = "";
        
        crossSection = 75.95;

        saveName = "WW";
        
        
        //int arrSize = sizeof(WWBackgroundAr)/sizeof(WWBackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //WWBackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //WWBackgroundAr[fileInd]);
    }
    else if (WZTrimmedBackground){
        //saveName = "";
        
        crossSection = 27.59;

        saveName = "WZ";
        
        
        //int arrSize = sizeof(WZBackgroundAr)/sizeof(WZBackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //WZBackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //WZBackgroundAr[fileInd]);
    }
    else if (TTbb_TTToHadronicTrimmedBackground){
        //saveName = "QCDPT3200toInf";
        
        crossSection = 5.5;

        saveName = "TTbb_TTToHadronic";
        
        
        //int arrSize = sizeof(TTbb_TTToHadronicBackgroundAr)/sizeof(TTbb_TTToHadronicBackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //TTbb_TTToHadronicBackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //TTbb_TTToHadronicBackgroundAr[fileInd]);
    }
    else if (TTbb_TTTo2L2NuTrimmedBackground){
        //saveName = "";
        
        crossSection = 2.9;

        saveName = "TTbb_TTTo2L2Nu";
        
        
        //int arrSize = sizeof(TTbb_TTTo2L2NuBackgroundAr)/sizeof(TTbb_TTTo2L2NuBackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //TTbb_TTTo2L2NuBackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //TTbb_TTTo2L2NuBackgroundAr[fileInd]);
    }
    else if (TTbb_TTToSemiLeptonicTrimmedBackground){
        //saveName = "";
        
        crossSection = 4.7;

        saveName = "TTbb_TTToSemiLeptonic";
        
        
        //int arrSize = sizeof(TTbb_TTToSemiLeptonicBackgroundAr)/sizeof(TTbb_TTToSemiLeptonicBackgroundAr[0]);
        /*
        for (int i=0; i<arrSize; i++){
            fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //TTbb_TTToSemiLeptonicBackgroundAr[i]);
        }
        */
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //TTbb_TTToSemiLeptonicBackgroundAr[fileInd]);
    }
    else if (DYM10To50TrimmedBackground){
        //datasetType = 50;
        saveName = "DYM10To50";
        
        //int arrSize = sizeof(DYM10To50BackgroundAr)/sizeof(DYM10To50BackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //DYM10To50BackgroundAr[fileInd]);
    }
    else if (ST_tW_antitopTrimmedBackground){
        //datasetType = 51;
        saveName = "ST_tW_antitop";
        
        //int arrSize = sizeof(ST_tW_antitopBackgroundAr)/sizeof(ST_tW_antitopBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //ST_tW_antitopBackgroundAr[fileInd]);
    }
    else if (ST_tW_topTrimmedBackground){
        //datasetType = 52;
        saveName = "ST_tW_top";
        
        //int arrSize = sizeof(ST_tW_topBackgroundAr)/sizeof(ST_tW_topBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //ST_tW_topBackgroundAr[fileInd]);
    }
    else if (EWKWMinus2Jets_WToLNuTrimmedBackground){
        //datasetType = 53;
        saveName = "EWKWMinus2Jets_WToLNu";
        
        //int arrSize = sizeof(EWKWMinus2Jets_WToLNuBackgroundAr)/sizeof(EWKWMinus2Jets_WToLNuBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //EWKWMinus2Jets_WToLNuBackgroundAr[fileInd]);
    }
    else if (EWKWMinus2Jets_WToQQTrimmedBackground){
        //datasetType = 54;
        saveName = "EWKWMinus2Jets_WToQQ";
        
        //int arrSize = sizeof(EWKWMinus2Jets_WToQQBackgroundAr)/sizeof(EWKWMinus2Jets_WToQQBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //EWKWMinus2Jets_WToQQBackgroundAr[fileInd]);
    }
    else if (EWKWPlus2Jets_WToLNuTrimmedBackground){
        //datasetType = 55;
        saveName = "EWKWPlus2Jets_WToLNu";
        
        //int arrSize = sizeof(EWKWPlus2Jets_WToLNuBackgroundAr)/sizeof(EWKWPlus2Jets_WToLNuBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //EWKWPlus2Jets_WToLNuBackgroundAr[fileInd]);
    }
    else if (EWKWPlus2Jets_WToQQTrimmedBackground){
        //datasetType = 56;
        saveName = "EWKWPlus2Jets_WToQQ";
        
        //int arrSize = sizeof(EWKWPlus2Jets_WToQQBackgroundAr)/sizeof(EWKWPlus2Jets_WToQQBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //EWKWPlus2Jets_WToQQBackgroundAr[fileInd]);
    }
    else if (VHToNonbbTrimmedBackground){
        //datasetType = 57;
        saveName = "VHToNonbb";
        
        //int arrSize = sizeof(VHToNonbbBackgroundAr)/sizeof(VHToNonbbBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //VHToNonbbBackgroundAr[fileInd]);
    }
    else if (WminusH_HToBB_WToLNuTrimmedBackground){
        //datasetType = 58;
        saveName = "WminusH_HToBB_WToLNu";
        
        //int arrSize = sizeof(WminusH_HToBB_WToLNuBackgroundAr)/sizeof(WminusH_HToBB_WToLNuBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //WminusH_HToBB_WToLNuBackgroundAr[fileInd]);
    }
    else if (WminusH_HToBB_WToQQTrimmedBackground){
        //datasetType = 59;
        saveName = "WminusH_HToBB_WToQQ";
        
        //int arrSize = sizeof(WminusH_HToBB_WToQQBackgroundAr)/sizeof(WminusH_HToBB_WToQQBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //WminusH_HToBB_WToQQBackgroundAr[fileInd]);
    }
    else if (WplusH_HToBB_WToLNuTrimmedBackground){
        //datasetType = 60;
        saveName = "WplusH_HToBB_WToLNu";
        
        //int arrSize = sizeof(WplusH_HToBB_WToLNuBackgroundAr)/sizeof(WplusH_HToBB_WToLNuBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //WplusH_HToBB_WToLNuBackgroundAr[fileInd]);
    }
    else if (WplusH_HToBB_WToQQTrimmedBackground){
        //datasetType = 61;
        saveName = "WplusH_HToBB_WToQQ";
        
        //int arrSize = sizeof(WplusH_HToBB_WToQQBackgroundAr)/sizeof(WplusH_HToBB_WToQQBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //WplusH_HToBB_WToQQBackgroundAr[fileInd]);
    }
    else if (WJetsToLNuTrimmedBackground){
        //datasetType = 62;
        saveName = "WJetsToLNu";
        
        //int arrSize = sizeof(WJetsToLNuBackgroundAr)/sizeof(WJetsToLNuBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //WJetsToLNuBackgroundAr[fileInd]);
    }
    else if (WWWTrimmedBackground){
        //datasetType = 63;
        saveName = "WWW";
        
        //int arrSize = sizeof(WWWBackgroundAr)/sizeof(WWWBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //WWWBackgroundAr[fileInd]);
    }
    else if (WWZTrimmedBackground){
        //datasetType = 64;
        saveName = "WWZ";
        
        //int arrSize = sizeof(WWZBackgroundAr)/sizeof(WWZBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //WWZBackgroundAr[fileInd]);
    }
    else if (WZZTrimmedBackground){
        //datasetType = 65;
        saveName = "WZZ";
        
        //int arrSize = sizeof(WZZBackgroundAr)/sizeof(WZZBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //WZZBackgroundAr[fileInd]);
    }
    else if (ZH_HToBB_ZToBBTrimmedBackground){
        //datasetType = 66;
        saveName = "ZH_HToBB_ZToBB";
        
        //int arrSize = sizeof(ZH_HToBB_ZToBBBackgroundAr)/sizeof(ZH_HToBB_ZToBBBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //ZH_HToBB_ZToBBBackgroundAr[fileInd]);
    }
    else if (ZH_HToBB_ZToNuNuTrimmedBackground){
        //datasetType = 66;
        saveName = "ZH_HToBB_ZToNuNu";
        
        //int arrSize = sizeof(ZH_HToBB_ZToNuNuBackgroundAr)/sizeof(ZH_HToBB_ZToNuNuBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //ZH_HToBB_ZToNuNuBackgroundAr[fileInd]);
    }
    else if (ZH_HToBB_ZToLLTrimmedBackground){
        //datasetType = 66;
        saveName = "ZH_HToBB_ZToLL";
        
        //int arrSize = sizeof(ZH_HToBB_ZToLLBackgroundAr)/sizeof(ZH_HToBB_ZToLLBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //ZH_HToBB_ZToLLBackgroundAr[fileInd]);
    }
    else if (ZH_HToBB_ZToQQTrimmedBackground){
        //datasetType = 67;
        saveName = "ZH_HToBB_ZToQQ";
        
        //int arrSize = sizeof(ZH_HToBB_ZToQQBackgroundAr)/sizeof(ZH_HToBB_ZToQQBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //ZH_HToBB_ZToQQBackgroundAr[fileInd]);
    }
    else if (ggZH_HToBB_ZToBBTrimmedBackground){
        //datasetType = 68;
        saveName = "ggZH_HToBB_ZToBB";
        
        //int arrSize = sizeof(ggZH_HToBB_ZToBBBackgroundAr)/sizeof(ggZH_HToBB_ZToBBBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //ggZH_HToBB_ZToBBBackgroundAr[fileInd]);
    }
    else if (ggZH_HToBB_ZToNuNuTrimmedBackground){
        //datasetType = 68;
        saveName = "ggZH_HToBB_ZToNuNu";
        
        //int arrSize = sizeof(ggZH_HToBB_ZToNuNuBackgroundAr)/sizeof(ggZH_HToBB_ZToNuNuBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //ggZH_HToBB_ZToNuNuBackgroundAr[fileInd]);
    }
    else if (ggZH_HToBB_ZToLLTrimmedBackground){
        //datasetType = 68;
        saveName = "ggZH_HToBB_ZToLL";
        
        //int arrSize = sizeof(ggZH_HToBB_ZToLLBackgroundAr)/sizeof(ggZH_HToBB_ZToLLBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //ggZH_HToBB_ZToLLBackgroundAr[fileInd]);
    }
    else if (ggZH_HToBB_ZToQQTrimmedBackground){
        //datasetType = 69;
        saveName = "ggZH_HToBB_ZToQQ";
        
        //int arrSize = sizeof(ggZH_HToBB_ZToQQBackgroundAr)/sizeof(ggZH_HToBB_ZToQQBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //ggZH_HToBB_ZToQQBackgroundAr[fileInd]);
    }
    else if (EWKZ2Jets_ZToLLTrimmedBackground){
        //datasetType = 70;
        saveName = "EWKZ2Jets_ZToLL";
        
        //int arrSize = sizeof(EWKZ2Jets_ZToLLBackgroundAr)/sizeof(EWKZ2Jets_ZToLLBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //EWKZ2Jets_ZToLLBackgroundAr[fileInd]);
    }
    else if (EWKZ2Jets_ZToNuNuTrimmedBackground){
        //datasetType = 71;
        saveName = "EWKZ2Jets_ZToNuNu";
        
        //int arrSize = sizeof(EWKZ2Jets_ZToNuNuBackgroundAr)/sizeof(EWKZ2Jets_ZToNuNuBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //EWKZ2Jets_ZToNuNuBackgroundAr[fileInd]);
    }
    else if (EWKZ2Jets_ZToQQTrimmedBackground){
        //datasetType = 72;
        saveName = "EWKZ2Jets_ZToQQ";
        
        //int arrSize = sizeof(EWKZ2Jets_ZToQQBackgroundAr)/sizeof(EWKZ2Jets_ZToQQBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //EWKZ2Jets_ZToQQBackgroundAr[fileInd]);
    }
    else if (ZZZTrimmedBackground){
        //datasetType = 73;
        saveName = "ZZZ";
        
        //int arrSize = sizeof(ZZZBackgroundAr)/sizeof(ZZZBackgroundAr[0]);
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //ZZZBackgroundAr[fileInd]);
    }
    else if (testRun){
        saveName = "testRun";
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
        //"./unweighted_eventspphzzjjQCD0SMHLOOP0NPE1NPcHWE1QEDE5ResMasAllVer100Ev10080Seed_0p999cHW100GeVIMJetCut_200.root");
        
        isBackground = false;
        
    }
    else if (LaraTest){
        saveName = "LaraTest";
        fileAr.push_back("./HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+yearNameStr+"_WithJERRoch_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root");
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
    
    std::string outFileStr = "HLTTrimmedFilteredForAnalysis"+saveName+"_WithPreSel_"+std::to_string(JECCorInd)+"_"+std::to_string(JECCorUpOrDown)+"_"+std::to_string(RochInd)+"_"+std::to_string(JERInd)+".root";
    std::cout << "OutFile: " << outFileStr << "\n";
    TFile *outFile = new TFile(outFileStr.c_str(),"RECREATE");
    

    ////////////////////////////////DEFINING TREES////////////////////////////////
    ////////////////////////////////DEFINING TREES////////////////////////////////
    ////////////////////////////////DEFINING TREES////////////////////////////////
    ////////////////////////////////DEFINING TREES////////////////////////////////

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
    //Tight/Veto lep variables
    Bool_t tightLepLeadIsElecL;
    Bool_t tightLepTrailingIsElecL;
    Bool_t tightLepLeadIsMuonL;
    Bool_t tightLepTrailingIsMuonL;
    Int_t tightLepLeadIndL;
    Int_t tightLepTrailingIndL;
    Float_t tightLepLeadPtL;
    Float_t tightLepTrailingPtL;
    Float_t tightLepLeadEtaL;
    Float_t tightLepTrailingEtaL;
    Float_t tightLepLeadPhiL;
    Float_t tightLepTrailingPhiL;
    Float_t tightLepLeadMassL;
    Float_t tightLepTrailingMassL;
    //AK8 Jet variables
    Int_t AK8TopPNIndL;
    Float_t AK8TopPNPtL;
    Float_t AK8TopPNEtaL;
    Float_t AK8TopPNPhiL;
    Float_t AK8TopPNMassL;
    //AK4 Jet variables
    Int_t AK4TopDEtaLeadIndL;
    Int_t AK4TopDEtaTrailingIndL;
    Float_t AK4TopDEtaLeadPtL;
    Float_t AK4TopDEtaTrailingPtL;
    Float_t AK4TopDEtaLeadEtaL;
    Float_t AK4TopDEtaTrailingEtaL;
    Float_t AK4TopDEtaLeadPhiL;
    Float_t AK4TopDEtaTrailingPhiL;
    Float_t AK4TopDEtaLeadMassL;
    Float_t AK4TopDEtaTrailingMassL;
    //Vector array for Veto lepton indices
    UInt_t nVetoElecL;
    std::vector<Int_t> vetoElecIndL;
    UInt_t nVetoMuonL;
    std::vector<Int_t> vetoMuonIndL;

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
    
    //additional 042024Branches starting with this script
    //PUID SF check
    std::vector<Bool_t> Jet_LowPtPassesPUIDL; 


    
    


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

    FilteredEventsTree->Branch("HLT_Ele32_WPTight_Gsf_L1DoubleEGL",&HLT_Ele32_WPTight_Gsf_L1DoubleEGL,"HLT_Ele32_WPTight_Gsf_L1DoubleEGL/O");
    FilteredEventsTree->Branch("HLT_IsoMu27L",&HLT_IsoMu27L,"HLT_IsoMu27L/O");
    FilteredEventsTree->Branch("HLT_Mu50L",&HLT_Mu50L,"HLT_Mu50L/O");
    FilteredEventsTree->Branch("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZL",&HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZL,"HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZL/O");
    FilteredEventsTree->Branch("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8L",&HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8L,"HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8L/O");

    //2016
    FilteredEventsTree->Branch("HLT_Ele27_WPTight_GsfL",&HLT_Ele27_WPTight_GsfL,"HLT_Ele27_WPTight_GsfL/O");
    FilteredEventsTree->Branch("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZL",&HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZL,"HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZL/O");

    FilteredEventsTree->Branch("tightLepLeadIsElecL",&tightLepLeadIsElecL,"tightLepLeadIsElecL/O");
    FilteredEventsTree->Branch("tightLepTrailingIsElecL",&tightLepTrailingIsElecL,"tightLepTrailingIsElecL/O");
    FilteredEventsTree->Branch("tightLepLeadIsMuonL",&tightLepLeadIsMuonL,"tightLepLeadIsMuonL/O");
    FilteredEventsTree->Branch("tightLepTrailingIsMuonL",&tightLepTrailingIsMuonL,"tightLepTrailingIsMuonL/O");
    FilteredEventsTree->Branch("tightLepLeadIndL",&tightLepLeadIndL,"tightLepLeadIndL/I");
    FilteredEventsTree->Branch("tightLepTrailingIndL",&tightLepTrailingIndL,"tightLepTrailingIndL/I");
    FilteredEventsTree->Branch("tightLepLeadPtL",&tightLepLeadPtL,"tightLepLeadPtL/F");
    FilteredEventsTree->Branch("tightLepTrailingPtL",&tightLepTrailingPtL,"tightLepTrailingPtL/F");
    FilteredEventsTree->Branch("tightLepLeadEtaL",&tightLepLeadEtaL,"tightLepLeadEtaL/F");
    FilteredEventsTree->Branch("tightLepTrailingEtaL",&tightLepTrailingEtaL,"tightLepTrailingEtaL/F");
    FilteredEventsTree->Branch("tightLepLeadPhiL",&tightLepLeadPhiL,"tightLepLeadPhiL/F");
    FilteredEventsTree->Branch("tightLepTrailingPhiL",&tightLepTrailingPhiL,"tightLepTrailingPhiL/F");
    FilteredEventsTree->Branch("tightLepLeadMassL",&tightLepLeadMassL,"tightLepLeadMassL/F");
    FilteredEventsTree->Branch("tightLepTrailingMassL",&tightLepTrailingMassL,"tightLepTrailingMassL/F");
    
    //AK8 Jet variables
    FilteredEventsTree->Branch("AK8TopPNIndL",&AK8TopPNIndL,"AK8TopPNIndL/I");
    FilteredEventsTree->Branch("AK8TopPNPtL",&AK8TopPNPtL,"AK8TopPNPtL/F");
    FilteredEventsTree->Branch("AK8TopPNEtaL",&AK8TopPNEtaL,"AK8TopPNEtaL/F");
    FilteredEventsTree->Branch("AK8TopPNPhiL",&AK8TopPNPhiL,"AK8TopPNPhiL/F");
    FilteredEventsTree->Branch("AK8TopPNMassL",&AK8TopPNMassL,"AK8TopPNMassL/F");
    //AK4 Jet variables
    FilteredEventsTree->Branch("AK4TopDEtaLeadIndL",&AK4TopDEtaLeadIndL,"AK4TopDEtaLeadIndL/I");
    FilteredEventsTree->Branch("AK4TopDEtaTrailingIndL",&AK4TopDEtaTrailingIndL,"AK4TopDEtaTrailingIndL/I");
    FilteredEventsTree->Branch("AK4TopDEtaLeadPtL",&AK4TopDEtaLeadPtL,"AK4TopDEtaLeadPtL/F");
    FilteredEventsTree->Branch("AK4TopDEtaTrailingPtL",&AK4TopDEtaTrailingPtL,"AK4TopDEtaTrailingPtL/F");
    FilteredEventsTree->Branch("AK4TopDEtaLeadEtaL",&AK4TopDEtaLeadEtaL,"AK4TopDEtaLeadEtaL/F");
    FilteredEventsTree->Branch("AK4TopDEtaTrailingEtaL",&AK4TopDEtaTrailingEtaL,"AK4TopDEtaTrailingEtaL/F");
    FilteredEventsTree->Branch("AK4TopDEtaLeadPhiL",&AK4TopDEtaLeadPhiL,"AK4TopDEtaLeadPhiL/F");
    FilteredEventsTree->Branch("AK4TopDEtaTrailingPhiL",&AK4TopDEtaTrailingPhiL,"AK4TopDEtaTrailingPhiL/F");
    FilteredEventsTree->Branch("AK4TopDEtaLeadMassL",&AK4TopDEtaLeadMassL,"AK4TopDEtaLeadMassL/F");
    FilteredEventsTree->Branch("AK4TopDEtaTrailingMassL",&AK4TopDEtaTrailingMassL,"AK4TopDEtaTrailingMassL/F");
    //Vector array for Veto lepton indices
    FilteredEventsTree->Branch("nVetoElecL",&nVetoElecL,"nVetoElecL/i");
    FilteredEventsTree->Branch("nVetoMuonL",&nVetoMuonL,"nVetoMuonL/i");
    FilteredEventsTree->Branch("vetoElecIndL",&vetoElecIndL);
    FilteredEventsTree->Branch("vetoMuonIndL",&vetoMuonIndL);

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
    //additional 042024Branches starting with preselection
    //PUID SF check
    FilteredEventsTree->Branch("Jet_LowPtPassesPUIDL",&Jet_LowPtPassesPUIDL);

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

    

    UInt_t datanEv = 0;
    UInt_t datanEvPass = 0;
    UInt_t evCount = 0;
    UInt_t evRunOver = 0;

    UInt_t evPassesLep = 0;
    UInt_t evPassesAK8Jet = 0;
    UInt_t evPassesAK4Jet = 0;
    UInt_t evTooFewTightLeps = 0;
    UInt_t evTooManyTightLeps = 0;
    UInt_t evTooManyVetoLeps = 0;

    std::cout << "Going into file loop.\n";

    for (UInt_t k=0; k<fileAr.size(); k++){
        if (endAfter && evCount > NToEnd) break;
        if (debug) std::cout<<"File:    "<<fileAr[k]<<"\n";
        //Open the file, get the Events tree
        TFile* tmpfile = TFile::Open(fileAr[k].c_str());
        //outFile->cd();
        TTreeReader myEventsReader("FilteredEventsTree", tmpfile);

        //genWeights
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
        TTreeReaderValue<Float_t> fixedGridRhoFastjetAll(myEventsReader, "fixedGridRhoFastjetAllL");
        TTreeReaderArray<Float_t> Jet_eta_Final(myEventsReader, "Jet_eta_FinalL");
        TTreeReaderArray<Float_t> Jet_pt_Final(myEventsReader, "Jet_pt_FinalL");
        TTreeReaderArray<Float_t> Jet_phi_Final(myEventsReader, "Jet_phi_FinalL");
        TTreeReaderArray<Float_t> Jet_mass_Final(myEventsReader, "Jet_mass_FinalL");


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
        TTreeReaderArray<Float_t> FatJet_msoftdrop(myEventsReader, "FatJet_msoftdropL");
        TTreeReaderArray<Float_t> FatJet_eta_Final(myEventsReader, "FatJet_eta_FinalL");
        TTreeReaderArray<Float_t> FatJet_pt_Final(myEventsReader, "FatJet_pt_FinalL");
        TTreeReaderArray<Float_t> FatJet_phi_Final(myEventsReader, "FatJet_phi_FinalL");
        TTreeReaderArray<Float_t> FatJet_mass_Final(myEventsReader, "FatJet_mass_FinalL");
        TTreeReaderArray<Float_t> FatJet_deepTag_H(myEventsReader, "FatJet_deepTag_HL");
        TTreeReaderArray<Float_t> FatJet_deepTag_ZvsQCD(myEventsReader, "FatJet_deepTag_ZvsQCDL");

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
        TTreeReaderArray<Float_t> Muon_RochCorUnc(myEventsReader, "Muon_RochCorUncL");
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

        TTreeReaderArray<Float_t> Jet_btagDeepFlavB(myEventsReader,"Jet_btagDeepFlavBL");

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

        //genChannelL
        TTreeReaderValue<UInt_t> genChannel(myEventsReader, "genChannelL");
        //HTobbBool
        TTreeReaderValue<Bool_t> HTobbBool(myEventsReader, "HTobbBoolL");


        TTreeReaderArray<Int_t> FatJet_hadronFlavour(myEventsReader,"FatJet_hadronFlavourL");


        TTreeReaderValue<Bool_t> HLT_Ele32_WPTight_Gsf_L1DoubleEG(myEventsReader,"HLT_Ele32_WPTight_Gsf_L1DoubleEGL");
        TTreeReaderValue<Bool_t> HLT_IsoMu27(myEventsReader,"HLT_IsoMu27L");
        TTreeReaderValue<Bool_t> HLT_Mu50(myEventsReader,"HLT_Mu50L");
        TTreeReaderValue<Bool_t> HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ(myEventsReader,"HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZL");
        TTreeReaderValue<Bool_t> HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8(myEventsReader,"HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8L");

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

            //Check tight and veto electron and muon
            int nTightElec = 0;
            int nVetoElec = 0;
            int nTightMuon = 0;
            int nVetoMuon = 0;
            int tightLepOneInd = -1;
            int tightLepTwoInd = -1;
            bool tightLepOneIsElec = false;
            bool tightLepTwoIsElec = false;
            bool tightLepOneIsMuon = false;
            bool tightLepTwoIsMuon = false;
            bool oneTightLepFound = false;
            std::vector<Int_t> vetoElecInd;
            std::vector<Int_t> vetoMuonInd;
            


            getVetoAndTightElectronsWithVetoArray(nElectron,Electron_mvaFall17V2noIso_WPL,Electron_pt,Electron_eta,
            Electron_dxy,Electron_dz,Electron_sip3d,Electron_miniPFRelIso_all,
            Electron_hoe,Electron_eInvMinusPInv,Electron_convVeto,Electron_lostHits,
            Electron_jetIdx,Jet_btagDeepFlavB,Electron_mvaTTH,nVetoElec,nTightElec,tightLepOneInd,tightLepTwoInd,oneTightLepFound,
            elecPtVetoCut,elecEtaVetoCut,elecDxyVetoCut,elecDzVetoCut,elecSIP3DVetoCut,elecMiniPFRelIsoCut,elecLostHitsVetoCut,elecPtTightCut,
            elecHoeTightCut,elecInvMinusPInvTightCut,elecLostHitsTightCut,elecJetDeepTagMediumCut,elecPromptMVACut,vetoElecInd,debug);
            if (nTightElec > 0){
                tightLepOneIsElec = true;
                if (nTightElec > 1){
                    tightLepTwoIsElec = true;
                }
            }

            getVetoAndTightMuonsWithVetoArray(nMuon,Muon_looseId,Muon_mediumId,Muon_ptCorrected,Muon_eta,Muon_dxy,Muon_dz,
            Muon_sip3d,Muon_miniPFRelIso_all,Muon_jetIdx,Jet_btagDeepFlavB,
            Muon_mvaTTH,nVetoMuon,nTightMuon,tightLepOneInd,tightLepTwoInd,
            oneTightLepFound,muonPtVetoCut,muonEtaVetoCut,muonDxyVetoCut,muonDzVetoCut,muonSIP3DVetoCut,
            muonPtTightCut,muonJetDeepTagMediumCut,muonPromptMVACut,vetoMuonInd,debug);
            if (nTightMuon > 0){
                if (tightLepOneIsElec) tightLepTwoIsMuon = true;
                else tightLepOneIsMuon = true;
                if (nTightMuon > 1){
                    tightLepTwoIsMuon = true;
                }
            }
            if (nTightElec + nTightMuon < 2) evTooFewTightLeps += 1;
            if (nTightElec + nTightMuon > 2) evTooManyTightLeps += 1;
            if ((nVetoElec + nVetoMuon > 2) && (nTightElec + nTightMuon == 2)) evTooManyVetoLeps += 1;
            if (nTightElec + nTightMuon != 2) continue;
            //if (nVetoElec + nVetoMuon != 2) continue;
            evPassesLep += 1;
            //get eta, phi, pt, and mass of tight leptons
            float tightLepOneEta;
            float tightLepOnePhi;
            float tightLepTwoEta;
            float tightLepTwoPhi;
            float tightLepOnePt;
            float tightLepTwoPt;
            float tightLepOneMass;
            float tightLepTwoMass;
            if (tightLepOneIsElec){
                tightLepOneEta = Electron_eta[tightLepOneInd];
                tightLepOnePhi = Electron_phi[tightLepOneInd];
                tightLepOnePt = Electron_pt[tightLepOneInd];
                tightLepOneMass = Electron_mass[tightLepOneInd];
            }
            else {
                tightLepOneEta = Muon_eta[tightLepOneInd];
                tightLepOnePhi = Muon_phi[tightLepOneInd];
                tightLepOnePt = Muon_ptCorrected[tightLepOneInd];
                tightLepOneMass = Muon_mass[tightLepOneInd];
            }
            if (tightLepTwoIsElec){
                tightLepTwoEta = Electron_eta[tightLepTwoInd];
                tightLepTwoPhi = Electron_phi[tightLepTwoInd];
                tightLepTwoPt = Electron_pt[tightLepTwoInd];
                tightLepTwoMass = Electron_mass[tightLepTwoInd];
            }
            else {
                tightLepTwoEta = Muon_eta[tightLepTwoInd];
                tightLepTwoPhi = Muon_phi[tightLepTwoInd];
                tightLepTwoPt = Muon_ptCorrected[tightLepTwoInd];
                tightLepTwoMass = Muon_mass[tightLepTwoInd];
            }

            //Do AK8 Preselection
            
            bool passingJetExists = false;
            float topPNScore = -1;
            int topPNScoreInd = -1;
            //Loop over fatjets and do preselection cuts
            for (UInt_t fatJetInd=0;fatJetInd<*nFatJet;fatJetInd++){
                float tmpFJPt = FatJet_pt_Final[fatJetInd];
                float tmpFJEta = FatJet_eta_Final[fatJetInd];
                float tmpFJPhi = FatJet_phi_Final[fatJetInd];
                float tmpFJM = FatJet_mass_Final[fatJetInd];
                float tmpFJSDM = FatJet_msoftdrop[fatJetInd];
                //Check to avoid dividing by zero
                float tmpFJPNScore = 0;
                if (FatJet_particleNetMD_Xbb[fatJetInd]+FatJet_particleNetMD_QCD[fatJetInd] == 0) {
                    tmpFJPNScore = 0;
                }
                else{
                    tmpFJPNScore = FatJet_particleNetMD_Xbb[fatJetInd]/(FatJet_particleNetMD_Xbb[fatJetInd]+FatJet_particleNetMD_QCD[fatJetInd]);
                }
                if (tmpFJPt < AK8PtCut) continue;
                if (tmpFJM < AK8MassCut) continue;
                if (tmpFJSDM < AK8SDMassCut) continue;
                if (calcDeltaR(tightLepOnePhi,tightLepOneEta,tmpFJPhi,tmpFJEta) < maxdRCut) continue;
                if (calcDeltaR(tightLepTwoPhi,tightLepTwoEta,tmpFJPhi,tmpFJEta) < maxdRCut) continue;
                passingJetExists = true;
                if (tmpFJPNScore >= topPNScore){
                    topPNScore = tmpFJPNScore;
                    topPNScoreInd = fatJetInd;
                }
            }
            if (!passingJetExists) continue;
            if (debug){
                std::cout <<"Passed nFJs\n";
            }
            evPassesAK8Jet += 1;
            // check if two or more VBF jets in event
            UInt_t tmpnVBFJets = *nJet;
            
            bool passnVBFJets = false;
            float VBFJetAbsDEta = 0;
            int VBFJetOneInd = -1;
            int VBFJetTwoInd = -1;
            float tmpVBFJetPtOne;
            float tmpVBFJetPtTwo;
            float tmpVBFJetEtaOne;
            float tmpVBFJetEtaTwo;
            float tmpVBFJetPhiOne;
            float tmpVBFJetPhiTwo;
            float tmpVBFJetMassOne;
            float tmpVBFJetMassTwo;
            std::vector<Bool_t> tmpJet_LowPtPassesPUID;
            //Quick jet loop before the actual loop to fill the Jet_LowPtPassesPUID vector
            for (UInt_t jetInd=0;jetInd<tmpnVBFJets;jetInd++){
                if (Jet_pt_Final[jetInd] < 50) {
                    if (Jet_puId[jetInd] == 7) tmpJet_LowPtPassesPUID.push_back(true);
                    else tmpJet_LowPtPassesPUID.push_back(false);
                }
                else tmpJet_LowPtPassesPUID.push_back(false);
            }

            //Now loop through jets again to find VBF jets
            for (UInt_t jetInd=0;jetInd<tmpnVBFJets-1;jetInd++){
                tmpVBFJetPtOne = Jet_pt_Final[jetInd];
                if (tmpVBFJetPtOne < AK4PtCut) continue;
                if (tmpVBFJetPtOne < 50) {
                    if (!tmpJet_LowPtPassesPUID[jetInd]) continue;
                }
                
                tmpVBFJetPhiOne = Jet_phi_Final[jetInd];
                tmpVBFJetEtaOne = Jet_eta_Final[jetInd];
                if (calcDeltaR(tightLepOnePhi,tightLepOneEta,tmpVBFJetPhiOne,tmpVBFJetEtaOne) < maxdRCut) continue;
                if (calcDeltaR(tightLepTwoPhi,tightLepTwoEta,tmpVBFJetPhiOne,tmpVBFJetEtaOne) < maxdRCut) continue;
                for (UInt_t jetIndTwo=jetInd+1;jetIndTwo<tmpnVBFJets;jetIndTwo++){
                    tmpVBFJetPtTwo = Jet_pt_Final[jetIndTwo];
                    if (tmpVBFJetPtTwo < AK4PtCut) continue;
                    if (tmpVBFJetPtTwo < 50) {
                        if (!tmpJet_LowPtPassesPUID[jetIndTwo]) continue;
                }
                    
                    tmpVBFJetEtaTwo = Jet_eta_Final[jetIndTwo];
                    float tmpAbsDEta = abs(tmpVBFJetEtaOne - tmpVBFJetEtaTwo);
                    if (tmpAbsDEta < AK4AbsDEtaCut) continue;
                    
                    tmpVBFJetPhiTwo = Jet_phi_Final[jetIndTwo];
                    if (calcDeltaR(tightLepOnePhi,tightLepOneEta,tmpVBFJetPhiTwo,tmpVBFJetEtaTwo) < maxdRCut) continue;
                    if (calcDeltaR(tightLepTwoPhi,tightLepTwoEta,tmpVBFJetPhiTwo,tmpVBFJetEtaTwo) < maxdRCut) continue;
                    passnVBFJets = true;
                    if (tmpAbsDEta > VBFJetAbsDEta){
                        VBFJetAbsDEta = tmpAbsDEta;
                        VBFJetOneInd = jetInd;
                        VBFJetTwoInd = jetIndTwo;
                        
                    }
                    
                }
            
            }
            if (debug){
                std::cout <<"Passed VBFJets\n";
            }
            if (!passnVBFJets) continue;
            evPassesAK4Jet += 1;
            tmpVBFJetPtOne = Jet_pt_Final[VBFJetOneInd];
            tmpVBFJetPtTwo = Jet_pt_Final[VBFJetTwoInd];
            tmpVBFJetEtaOne = Jet_eta_Final[VBFJetOneInd];
            tmpVBFJetEtaTwo = Jet_eta_Final[VBFJetTwoInd];
            tmpVBFJetPhiOne = Jet_phi_Final[VBFJetOneInd];
            tmpVBFJetPhiTwo = Jet_phi_Final[VBFJetTwoInd];
            tmpVBFJetMassOne = Jet_mass_Final[VBFJetOneInd];
            tmpVBFJetMassTwo = Jet_mass_Final[VBFJetTwoInd];
            
            //Fill in all branches of TTree

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
                Jet_eta_FinalL.push_back(Jet_eta_Final[nJetItr]);
                Jet_pt_FinalL.push_back(Jet_pt_Final[nJetItr]);
                Jet_phi_FinalL.push_back(Jet_phi_Final[nJetItr]);
                Jet_mass_FinalL.push_back(Jet_mass_Final[nJetItr]);



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
                FatJet_eta_FinalL.push_back(FatJet_eta_Final[nFatJetItr]);
                FatJet_pt_FinalL.push_back(FatJet_pt_Final[nFatJetItr]);
                FatJet_phi_FinalL.push_back(FatJet_phi_Final[nFatJetItr]);
                FatJet_mass_FinalL.push_back(FatJet_mass_Final[nFatJetItr]);

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
            HLT_Ele32_WPTight_Gsf_L1DoubleEGL = *HLT_Ele32_WPTight_Gsf_L1DoubleEG;
            HLT_IsoMu27L = *HLT_IsoMu27;
            HLT_Mu50L = *HLT_Mu50;
            HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZL = *HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;
            HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8L = *HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8;

            HLT_Ele27_WPTight_GsfL = *HLT_Ele27_WPTight_Gsf;
            HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZL = *HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ;
            //Tight/Veto lep variables
            if (tightLepOnePt > tightLepTwoPt){
                tightLepLeadIsElecL = tightLepOneIsElec;
                tightLepTrailingIsElecL = tightLepTwoIsElec;
                tightLepLeadIsMuonL = tightLepOneIsMuon;
                tightLepTrailingIsMuonL = tightLepTwoIsMuon;
                tightLepLeadIndL = tightLepOneInd;
                tightLepTrailingIndL = tightLepTwoInd;
            
                tightLepLeadPtL = tightLepOnePt;
                tightLepTrailingPtL = tightLepTwoPt;
                tightLepLeadEtaL = tightLepOneEta;
                tightLepTrailingEtaL = tightLepTwoEta;
                tightLepLeadPhiL = tightLepOnePhi;
                tightLepTrailingPhiL = tightLepTwoPhi;
                tightLepLeadMassL = tightLepOneMass;
                tightLepTrailingMassL = tightLepTwoMass;
            }
            else {
                tightLepLeadIsElecL = tightLepTwoIsElec;
                tightLepTrailingIsElecL = tightLepOneIsElec;
                tightLepLeadIsMuonL = tightLepTwoIsMuon;
                tightLepTrailingIsMuonL = tightLepOneIsMuon;
                tightLepLeadIndL = tightLepTwoInd;
                tightLepTrailingIndL = tightLepOneInd;

                tightLepLeadPtL = tightLepTwoPt;
                tightLepTrailingPtL = tightLepOnePt;
                tightLepLeadEtaL = tightLepTwoEta;
                tightLepTrailingEtaL = tightLepOneEta;
                tightLepLeadPhiL = tightLepTwoPhi;
                tightLepTrailingPhiL = tightLepOnePhi;
                tightLepLeadMassL = tightLepTwoMass;
                tightLepTrailingMassL = tightLepOneMass;
            }
            //AK8 Jet variables
            AK8TopPNIndL = topPNScoreInd;
            AK8TopPNPtL = FatJet_pt_Final[topPNScoreInd];
            AK8TopPNEtaL = FatJet_eta_Final[topPNScoreInd];
            AK8TopPNPhiL = FatJet_phi_Final[topPNScoreInd];
            AK8TopPNMassL = FatJet_mass_Final[topPNScoreInd];
            //AK4 Jet variables
            if (tmpVBFJetPtOne > tmpVBFJetPtTwo){
                AK4TopDEtaLeadIndL = VBFJetOneInd;
                AK4TopDEtaTrailingIndL = VBFJetTwoInd;
                AK4TopDEtaLeadPtL = tmpVBFJetPtOne;
                AK4TopDEtaTrailingPtL = tmpVBFJetPtTwo;
                AK4TopDEtaLeadEtaL = tmpVBFJetEtaOne;
                AK4TopDEtaTrailingEtaL = tmpVBFJetEtaTwo;
                AK4TopDEtaLeadPhiL = tmpVBFJetPhiOne;
                AK4TopDEtaTrailingPhiL = tmpVBFJetPhiTwo;
                AK4TopDEtaLeadMassL = tmpVBFJetMassOne;
                AK4TopDEtaTrailingMassL = tmpVBFJetMassTwo;
                
            }
            else {
                AK4TopDEtaLeadIndL = VBFJetTwoInd;
                AK4TopDEtaTrailingIndL = VBFJetOneInd;
                AK4TopDEtaLeadPtL = tmpVBFJetPtTwo;
                AK4TopDEtaTrailingPtL = tmpVBFJetPtOne;
                AK4TopDEtaLeadEtaL = tmpVBFJetEtaTwo;
                AK4TopDEtaTrailingEtaL = tmpVBFJetEtaOne;
                AK4TopDEtaLeadPhiL = tmpVBFJetPhiTwo;
                AK4TopDEtaTrailingPhiL = tmpVBFJetPhiOne;
                AK4TopDEtaLeadMassL = tmpVBFJetMassTwo;
                AK4TopDEtaTrailingMassL = tmpVBFJetMassOne;
            }
            //Veto leptons
            nVetoElecL = vetoElecInd.size();
            nVetoMuonL = vetoMuonInd.size();
            for (UInt_t nVEItr =0; nVEItr < vetoElecInd.size();nVEItr++){
                vetoElecIndL.push_back(vetoElecInd[nVEItr]);
            }
            for (UInt_t nVMItr =0; nVMItr < vetoMuonInd.size();nVMItr++){
                vetoMuonIndL.push_back(vetoMuonInd[nVMItr]);
            }


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
            //additional 042024Branches starting with this script
            //PUID SF check
            for (UInt_t nJetItr=0; nJetItr<nJetL;nJetItr++){
                Jet_LowPtPassesPUIDL.push_back(tmpJet_LowPtPassesPUID[nJetItr]);
            }

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

            vetoElecIndL.clear();
            vetoMuonIndL.clear();

            Jet_puIdL.clear();

            PSWeightL.clear();
            LHEScaleWeightL.clear();
            LHEPdfWeightL.clear();

            Jet_LowPtPassesPUIDL.clear();

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



    clock_t endt = clock();
    double time_spent = (double)(endt - startt) / CLOCKS_PER_SEC;



    std::cout << "Finished file loop. " << "time: " << time_spent << "\n";
    //crossSection = crossSectionAvg / crossSectionCnt;
    
    std::cout << "nEv total: " << datanEv << "\n";
    std::cout << "nEv post HLT: " << datanEvPass << "\n"; 
    std::cout << "nEv run over: " << evRunOver << "\n";
    std::cout << "nEv pass lep: " << evPassesLep << "\n";
    std::cout << "Too few tight leptons: " << evTooFewTightLeps << "\n";
    std::cout << "Too many tight leptons: " << evTooManyTightLeps << "\n";
    std::cout << "Events with potential veto leptons: " << evTooManyVetoLeps << "\n";
    std::cout << "nEv pass AK8: " << evPassesAK8Jet << "\n";
    std::cout << "nEv pass VBF: " << evPassesAK4Jet << "\n";

    
    

    outFile->cd();
    evNumTree->Write("",TObject::kOverwrite);
    weightSumsTree->Write("",TObject::kOverwrite);
    runTree->Write("",TObject::kOverwrite);
    FilteredEventsTree->Write("",TObject::kOverwrite);
    //btagEffTree->Write("",TObject::kOverwrite);

    outFile->Close();

}