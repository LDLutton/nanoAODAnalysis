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
void new042024BDTDataAnalysis(string datasetString){
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

    if (datasetString == "DoubleEG16Data") DoubleEG16Data = true;
    if (datasetString == "DoubleMuon16Data") DoubleMuon16Data = true;
    if (datasetString == "SingleElectron16Data") SingleElectron16Data = true;
    if (datasetString == "SingleMuon16Data") SingleMuon16Data = true;
    if (datasetString == "DoubleEG17Data") DoubleEG17Data = true;
    if (datasetString == "DoubleMuon17Data") DoubleMuonData = true;
    if (datasetString == "SingleElectron17Data") SingleElectron17Data = true;
    if (datasetString == "SingleMuon17Data") SingleMuon16Data = true;
    if (datasetString == "DoubleMuonData") DoubleMuonData = true;
    if (datasetString == "EGammaData") EGammaData = true;
    if (datasetString == "SingleMuonData") SingleMuonData = true;

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

    
    if (DoubleMuonData){
        datasetType = 31;
        saveName = "DoubleMuonData";
        
        std::string tmpStrWithPath = "/scratch365/dlutton/HLT042024DataWithPreSel/HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+"_WithPreSel.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (EGammaData){
        datasetType = 33;
        saveName = "EGammaData";
        
        std::string tmpStrWithPath = "/scratch365/dlutton/HLT042024DataWithPreSel/HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+"_WithPreSel.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SingleMuonData){
        datasetType = 47;
        saveName = "SingleMuonData";
        
        std::string tmpStrWithPath = "/scratch365/dlutton/HLT042024DataWithPreSel/HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+"_WithPreSel.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (DoubleEG17Data){
        datasetType = 30;
        yearType = 1;
        saveName = "DoubleEG17Data";
        
        std::string tmpStrWithPath = "/scratch365/dlutton/HLT042024DataWithPreSel/HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+"_WithPreSel.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (DoubleMuon17Data){
        datasetType = 31;
        yearType = 1;
        saveName = "DoubleMuon17Data";
        
        std::string tmpStrWithPath = "/scratch365/dlutton/HLT042024DataWithPreSel/HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+"_WithPreSel.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SingleElectron17Data){
        datasetType = 46;
        yearType = 1;
        saveName = "SingleElectron17Data";
        
        std::string tmpStrWithPath = "/scratch365/dlutton/HLT042024DataWithPreSel/HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+"_WithPreSel.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SingleMuon17Data){
        datasetType = 47;
        yearType = 1;
        saveName = "SingleMuon17Data";
        
        std::string tmpStrWithPath = "/scratch365/dlutton/HLT042024DataWithPreSel/HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+"_WithPreSel.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (DoubleEG16Data){
        datasetType = 30;
        yearType = 2;
        saveName = "DoubleEG16Data";
        
        std::string tmpStrWithPath = "/scratch365/dlutton/HLT042024DataWithPreSel/HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+"_WithPreSel.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (DoubleMuon16Data){
        datasetType = 31;
        yearType = 2;
        saveName = "DoubleMuon16Data";
        
        std::string tmpStrWithPath = "/scratch365/dlutton/HLT042024DataWithPreSel/HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+"_WithPreSel.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SingleElectron16Data){
        datasetType = 46;
        yearType = 2;
        saveName = "SingleElectron16Data";
        
        std::string tmpStrWithPath = "/scratch365/dlutton/HLT042024DataWithPreSel/HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+"_WithPreSel.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else if (SingleMuon16Data){
        datasetType = 47;
        yearType = 2;
        saveName = "SingleMuon16Data";
        
        std::string tmpStrWithPath = "/scratch365/dlutton/HLT042024DataWithPreSel/HLTTrimmedFilteredForAnalysis"+saveName+NoSLString+"_WithPreSel.root";
        fileAr.push_back(tmpStrWithPath);
    }
    else{
        std::cout << "ERROR. NO INPUT DATASET NAME GIVEN\n";
    }

    if (!useSingleLepHLT){
        saveName = saveName+NoSLString;
    }

    std::cout << "Doing " << saveName << "\n";
    //Setting up outfile with variables for BDT
    
    std::string outFileStr = "new042024BDTAnalysis"+saveName+".root";
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
    UInt_t passLepVetoCtr = 0;
    UInt_t passAsSemiLepCtr = 0;


    UInt_t passSemiLepLepCutCtr = 0;
    
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

    //042024SFAndSuchAdditions
    //PU JetID
    std::vector<Int_t> Jet_puIdL;
    //additional 042024Branches starting with this presel script
    //PUID SF check
    std::vector<Bool_t> Jet_LowPtPassesPUIDL;

    //more 042024Branches starting with selection
    Bool_t selectedLeadVBFJet_PUIDSFEligible_SL_L;
    Bool_t selectedTrailingVBFJet_PUIDSFEligible_SL_L;

    //05052024 Additions for PN regress mass scaling and resolution corrections
    UInt_t luminosityBlock_SL_L;
    ULong64_t event_SL_L;


    TTree *passingEvSemiLepTree = new TTree("passingEvSemiLepTree", "passingEvSemiLepTree");


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
    passingEvSemiLepTree->Branch("fixedGridRhoFastjetAll_SL_L",&fixedGridRhoFastjetAll_SL_L,"fixedGridRhoFastjetAll_SL_L/F");


    

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

    //042024SFAndSuchAdditions
    //PU JetID
    passingEvSemiLepTree->Branch("Jet_puIdL",&Jet_puIdL);
    //additional 042024Branches starting with this script
    //PUID SF check
    passingEvSemiLepTree->Branch("Jet_LowPtPassesPUIDL",&Jet_LowPtPassesPUIDL);

    //more 042024Branches starting with selection
    passingEvSemiLepTree->Branch("selectedLeadVBFJet_PUIDSFEligible_SL_L",&selectedLeadVBFJet_PUIDSFEligible_SL_L,"selectedLeadVBFJet_PUIDSFEligible_SL_L/O");
    passingEvSemiLepTree->Branch("selectedTrailingVBFJet_PUIDSFEligible_SL_L",&selectedTrailingVBFJet_PUIDSFEligible_SL_L,"selectedTrailingVBFJet_PUIDSFEligible_SL_L/O");

    //05052024 Additions for PN regress mass scaling and resolution corrections
    passingEvSemiLepTree->Branch("luminosityBlock_SL_L",&luminosityBlock_SL_L,"luminosityBlock_SL_L/i");
    passingEvSemiLepTree->Branch("event_SL_L",&event_SL_L,"event_SL_L/l");

    Float_t dataSetTotWeight = 0;

    std::cout << "Going into file loop.\n";

    for (UInt_t k=0; k<fileAr.size(); k++){
        if (endAfter && evCount > NToEnd) break;
        if (debug) std::cout<<"File:    "<<fileAr[k]<<"\n";
        //Open the file, get the Events tree
        TFile* tmpfile = TFile::Open(fileAr[k].c_str());
        //outFile->cd();
        TTreeReader myEventsReader("FilteredEventsTree", tmpfile);

        //jets

        TTreeReaderValue<UInt_t> nJetL(myEventsReader, "nJetL");
        TTreeReaderArray<Float_t> Jet_etaL(myEventsReader, "Jet_etaL");
        TTreeReaderArray<Float_t> Jet_ptL(myEventsReader, "Jet_ptL");
        TTreeReaderArray<Float_t> Jet_phiL(myEventsReader, "Jet_phiL");
        TTreeReaderArray<Float_t> Jet_massL(myEventsReader, "Jet_massL");
        TTreeReaderArray<Int_t> Jet_jetIdL(myEventsReader, "Jet_jetIdL");
        TTreeReaderValue<Float_t> fixedGridRhoFastjetAllL(myEventsReader, "fixedGridRhoFastjetAllL");

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

        TTreeReaderValue<UInt_t> nVetoElecL(myEventsReader,"nVetoElecL");
        TTreeReaderValue<UInt_t> nVetoMuonL(myEventsReader,"nVetoMuonL");
        TTreeReaderArray<Int_t> vetoElecIndL(myEventsReader,"vetoElecIndL");
        TTreeReaderArray<Int_t> vetoMuonIndL(myEventsReader,"vetoMuonIndL");

        //042024SFAndSuchAdditions
        //PU JetID
        TTreeReaderArray<Int_t> Jet_puId(myEventsReader, "Jet_puIdL");

        //additional 042024Branches starting with preselection
        //PUID SF check
        TTreeReaderArray<Bool_t> Jet_LowPtPassesPUID(myEventsReader, "Jet_LowPtPassesPUIDL");

        //05052024 Additions for PN regress mass scaling and resolution corrections
        TTreeReaderValue<UInt_t> luminosityBlock(myEventsReader, "luminosityBlockL");
        TTreeReaderValue<ULong64_t> event(myEventsReader, "eventL");

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

            startingCtr += 1;
        


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
        
            tryingSemiLepCtr += 1;
            //Checking that there are enough FJs for both the Z and the H
            UInt_t numFatJet = *nFatJetL;
            UInt_t nPassingJetIdFJs = 0;
            for (UInt_t fatJetInd=0;fatJetInd<numFatJet;fatJetInd++){
                if (FatJet_jetIdL[fatJetInd] == 6) nPassingJetIdFJs += 1;

            }

            if (nPassingJetIdFJs >=2){
                passEnoughFJsInSemiLepChannelCtr += 1;
                


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
                
                    
                }






                if (debug){
                    std::cout << "Pre FJC dRCheckVecAr.size() " << dRCheckVecAr.size() << "\n";
                }
                doHiggsFatJetCutBeforeZMDPNSelection(nFatJetLen,hFatJet_pt_fromHTag,hFatJet_phi_fromHTag,hFatJet_eta_fromHTag,hFatJet_mass_fromHTag,hFatJet_HTag_fromHTag,hFatJet_ind_fromHTag,FatJet_particleNetMD_QCDL,FatJet_particleNetMD_XbbL,hFatJetParticleNetCut,FatJet_ptL,hFatJetPTCut,FatJet_jetIdL,FatJet_phiL,FatJet_etaL,FatJet_massL,dRCheckVecAr,dRCut,passedAsSemiLepLepCutBool,passedAsSemiLepHiggsCutBool);
                
                if (debug) std::cout << " found Higgs fat jet\n";


                if (passedAsSemiLepHiggsCutBool){
                    passHiggsFJInSemiLepChannelCtr += 1;

                    
                
                }



                
                Int_t FJInd;

                FJInd = -1;
                //UInt_t numFatJet = *nFatJetL;
                if (debug){
                    std::cout << "Pre FJC dRCheckVecAr.size() " << dRCheckVecAr.size() << "\n";
                }
                doSemiLepChanFatJetCutAfterHMDPNSelection(FJInd,numFatJet,fatJetPTCut,fatJetZParticleNetCut,FatJet_ptL,FatJet_phiL,FatJet_etaL,FatJet_massL,FatJet_particleNetMD_QCDL,FatJet_particleNetMD_XbbL,FatJet_particleNetMD_XccL,FatJet_particleNetMD_XqqL,FatJet_jetIdL,dRCheckVecAr,dRCut,hFatJet_ind_fromHTag,passedAsSemiLepHiggsCutBool,passSemiLepCut,passesCutsBool,passedAsSemiLepBool);
                if (debug){
                    std::cout << "Post FJC dRCheckVecAr.size() " << dRCheckVecAr.size() << " FJInd "<< FJInd <<"\n";
                }
                if (FJInd >= 0){
                    passFJInSemiLepChannelCtr += 1;

                
                    FJIndAr.push_back(FJInd);
                    FJIndAr.push_back(hFatJet_ind_fromHTag);
                    
                }
            }
            
            if (passesCutsBool){
                passChannelCtr += 1;
                
                
                passSemiLepChannelCtr += 1;
                

                passLepOrSemiLepChannelCtr += 1;
                
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
            
            

            if (passedAsSemiLepBool) {
                passHiggsFJSemiLepCtr += 1;
            
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
        

            
            if (passedAsSemiLepBool) {
                passVBFJetBVetoSemiLepCtr += 1;
            
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

            dRCheckVecAr.push_back(tmpLeadJetVec);
            dRCheckVecAr.push_back(tmpTrailingJetVec);
            

            if (passesCutsBool){
                passVBFJetsCtr += 1;


                bool passVetoLep = true;
                //if any veto leptons, check if they are close to the other objects
                //if there are any that aren't close, veto the event
                for (UInt_t elecItr=0; elecItr < *nVetoElecL; elecItr++){
                    //Loop through dRCheckVecAr
                    for (UInt_t dRCheckVecInd=0; dRCheckVecInd<dRCheckVecAr.size();dRCheckVecInd++) {
                        float tmpDeltaR = calcDeltaR(Electron_phiL[vetoElecIndL[elecItr]],Electron_etaL[vetoElecIndL[elecItr]],dRCheckVecAr[dRCheckVecInd].Phi(),dRCheckVecAr[dRCheckVecInd].Eta());

                        if (tmpDeltaR > lepVetodRCut){
                            passVetoLep = false;
                            break;
                        }
                    }
                    if (!passVetoLep) break;
                }
                if (!passVetoLep) continue;
                //now check muons
                for (UInt_t muItr=0; muItr < *nVetoMuonL; muItr++){
                    //Loop through dRCheckVecAr
                    for (UInt_t dRCheckVecInd=0; dRCheckVecInd<dRCheckVecAr.size();dRCheckVecInd++) {
                        float tmpDeltaR = calcDeltaR(Muon_phiL[vetoMuonIndL[muItr]],Muon_etaL[vetoMuonIndL[muItr]],dRCheckVecAr[dRCheckVecInd].Phi(),dRCheckVecAr[dRCheckVecInd].Eta());

                        if (tmpDeltaR > lepVetodRCut){
                            passVetoLep = false;
                            break;
                        }
                    }
                    if (!passVetoLep) break;
                }
                if (!passVetoLep) continue;

                passLepVetoCtr += 1;


                //get number of passing VBFJets

                UInt_t tmpnAK4JetsPassing = 0;

                for (UInt_t nJetItr=0; nJetItr<nJetLen;nJetItr++){
                    UInt_t tmpJetPt = Jet_ptL[nJetItr];
                    //Jet_etaL[nJetItr]
                    Int_t tmpJetId = Jet_jetIdL[nJetItr];
                    if (tmpJetPt < 30 || !(tmpJetId == 6)) continue;
                    tmpnAK4JetsPassing += 1;

                
                }
            

                if (passedAsSemiLepBool){


                    passAsSemiLepCtr += 1;

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
                    

                    //042024SFAndSuchAdditions
                    //PU JetID
                    for (UInt_t nJetItr=0; nJetItr<nJetLen;nJetItr++){
                        Jet_puIdL.push_back(Jet_puId[nJetItr]);
                    }
                    //additional 042024Branches starting with this script
                    //PUID SF check
                    for (UInt_t nJetItr=0; nJetItr<nJetLen;nJetItr++){
                        Jet_LowPtPassesPUIDL.push_back(Jet_LowPtPassesPUID[nJetItr]);
                    }

                    //more 042024Branches starting with selection
                    selectedLeadVBFJet_PUIDSFEligible_SL_L = Jet_LowPtPassesPUID[leadJet_1];
                    selectedTrailingVBFJet_PUIDSFEligible_SL_L = Jet_LowPtPassesPUID[leadJet_2];

                    //05052024 Additions for PN regress mass scaling and resolution corrections
                    luminosityBlock_SL_L = *luminosityBlock;
                    event_SL_L = *event;

                    passingEvSemiLepTree->Fill();

                    Jet_eta_SL_L.clear();
                    Jet_pt_SL_L.clear();
                    Jet_phi_SL_L.clear();
                    Jet_mass_SL_L.clear();
                    Jet_jetId_SL_L.clear();
                    Jet_btagDeepFlavB_SL_L.clear();

                    Jet_puIdL.clear();

                    Jet_LowPtPassesPUIDL.clear();

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
    std::cout << "UInt_t " << saveName << "PassLepVetoCtr = " << passLepVetoCtr << "\n";
    std::cout << "------------------------\n";
    std::cout << "UInt_t " << saveName << "PassAsSemiLepCtr = " << passAsSemiLepCtr << "\n";
    std::cout << "------------------------\n";



    outFile->cd();
    passingEvSemiLepTree->Write("",TObject::kOverwrite);
    //btagEffTree->Write("",TObject::kOverwrite);

    outFile->Close();

}