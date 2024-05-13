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
#include<time.h>

#include<algorithm>
#include<chrono>
#include<ctime>
#include<fstream>
#include<iostream>
#include<mutex>

#include<thread>
#include<string>
#include <vector>



#include<sys/stat.h>
#include<errno.h>
#include<TTree.h>

bool debug = false;
bool endEvAfter = false;
bool endAfter = false;
int NToStart = 0;
int NToEnd = 20;
int NToEndTot = 10000;
bool localTest = false;

bool use10162023DataResults = true;



////////////////////////////////START OF MAIN FUNCTION////////////////////////////////
////////////////////////////////START OF MAIN FUNCTION////////////////////////////////
////////////////////////////////START OF MAIN FUNCTION////////////////////////////////
////////////////////////////////START OF MAIN FUNCTION////////////////////////////////


void new042024SemiLepDuplicateEventChecker(){
    // Open the file. Note that the name of your file outside this class
    // will probably NOT be experiment.root.
    std::cout << "start Analysis\n";
    clock_t startt = clock();
    //Analyzer will run over all files put into fileAr

    


    std::string saveName;
    bool isBackground;

    const uint nDataSets = 44;

    std::string datasetTypeStrAr[nDataSets] =  {
    "DoubleEG16",
    "DoubleEG17",
    "DoubleMuon16",
    "DoubleMuon17",
    "DoubleMuon",
    "EGamma",
    "SingleElectron16",
    "SingleElectron17",
    "SingleMuon16",
    "SingleMuon17",
    "SingleMuon"};



    std::string datasetStrAr[nDataSets];
    for (uint k = 0; k < nDataSets; k++){
        datasetStrAr[k] = "new042024BDTAnalysis"+datasetTypeStrAr[k]+".root";
    }
        

    ////////////////////////////////GETTING DATASET////////////////////////////////
    ////////////////////////////////GETTING DATASET////////////////////////////////
    ////////////////////////////////GETTING DATASET////////////////////////////////
    ////////////////////////////////GETTING DATASET////////////////////////////////

    std::string strAdd;
    std::vector<std::string> fileAr;
    strAdd ="/scratch365/dlutton/new042024BDTData/";
    for (UInt_t i = 0; i < nDataSets; i++){
        fileAr.push_back(strAdd+datasetStrAr[i]);
    }
    


    UInt_t datasetType = 0;



    //Setting up outfile with variables for BDT

    std::string outFileStr;
    outFileStr = "new042024BDTAnalysisUniqueData.root";
    
    std::cout << "Doing duplicate checker for outFile: " << outFileStr << "\n";
    TFile *outFile = new TFile(outFileStr.c_str(),"RECREATE");

    ////////////////////////////////DEFINING TREES////////////////////////////////
    ////////////////////////////////DEFINING TREES////////////////////////////////
    ////////////////////////////////DEFINING TREES////////////////////////////////
    ////////////////////////////////DEFINING TREES////////////////////////////////

    ////////////////////////////////DEFINING COUNTERS////////////////////////////////
    ////////////////////////////////NEUTRAL COUNTERS////////////////////////////////

    UInt_t allCtr = 0;
    UInt_t uniqueCtr = 0;




    //PASSING EV TREE FOR BDT IN SEMILEP CHANNEL
    UInt_t run_SLU_L;
    UInt_t datasetType_SLU_L;

    UInt_t yearType_SLU_L;

    UInt_t runAlphNum_SLU_L;
    Bool_t APV_SLU_L;

    UInt_t eventNAK4Jets_SLU_L;
    UInt_t eventNAK8Jets_SLU_L;
    UInt_t eventNMuons_SLU_L;
    UInt_t eventNElectrons_SLU_L;



    std::vector<Float_t> Jet_eta_SLU_L;
    std::vector<Float_t> Jet_pt_SLU_L;
    std::vector<Float_t> Jet_phi_SLU_L;
    std::vector<Float_t> Jet_mass_SLU_L;
    std::vector<Int_t> Jet_jetId_SLU_L;
    std::vector<Float_t> Jet_btagDeepFlavB_SLU_L;

    Float_t fixedGridRhoFastjetAll_SLU_L;

    UInt_t eventNAK4JetsPassingCuts_SLU_L;

    Float_t selectedHiggsFJ_pt_SLU_L;
    Float_t selectedHiggsFJ_eta_SLU_L;
    Float_t selectedHiggsFJ_phi_SLU_L;
    Float_t selectedZFJ_ParticleNet_HbbvsQCD_SLU_L;
    Float_t selectedHiggsFJ_ParticleNet_HbbvsQCD_SLU_L;
    Float_t selectedZFJ_pt_SLU_L;
    Float_t selectedZFJ_eta_SLU_L;
    Float_t selectedZFJ_phi_SLU_L;
    Float_t selectedZFJ_ParticleNet_ZvsQCD_SLU_L;
    Float_t selectedHiggsFJ_ParticleNet_ZvsQCD_SLU_L;

    Float_t selectedZFJ_InvMass_SLU_L;
    Float_t selectedHiggsFJ_InvMass_SLU_L;

    Float_t selectedZFJ_InvMassSoftDrop_SLU_L;
    Float_t selectedHiggsFJ_InvMassSoftDrop_SLU_L;

    Float_t selectedZFJ_InvMassPNRegress_SLU_L;
    Float_t selectedHiggsFJ_InvMassPNRegress_SLU_L;

    Float_t selectedHiggsFJ_ParticleNetMD_QCD_SLU_L;
    Float_t selectedHiggsFJ_ParticleNetMD_Xbb_SLU_L;
    Float_t selectedHiggsFJ_ParticleNetMD_Xcc_SLU_L;
    Float_t selectedHiggsFJ_ParticleNetMD_Xqq_SLU_L;

    Float_t selectedZFJ_ParticleNetMD_QCD_SLU_L;
    Float_t selectedZFJ_ParticleNetMD_Xbb_SLU_L;
    Float_t selectedZFJ_ParticleNetMD_Xcc_SLU_L;
    Float_t selectedZFJ_ParticleNetMD_Xqq_SLU_L;

    Float_t selectedLeadVBFJet_pt_SLU_L;
    Float_t selectedTrailingVBFJet_pt_SLU_L;
    Float_t selectedLeadVBFJet_eta_SLU_L;
    Float_t selectedTrailingVBFJet_eta_SLU_L;
    Float_t selectedVBFJets_EtaSep_SLU_L;
    Float_t selectedVBFJets_InvMass_SLU_L;

    Float_t selectedLeadLepton_pt_SLU_L;
    Float_t selectedTrailingLepton_pt_SLU_L;
    Float_t selectedLeadLepton_eta_SLU_L;
    Float_t selectedTrailingLepton_eta_SLU_L;
    Float_t selectedLeadLepton_phi_SLU_L;
    Float_t selectedTrailingLepton_phi_SLU_L;
    Float_t selectedLeadLepton_SIP3D_SLU_L;
    Float_t selectedTrailingLepton_SIP3D_SLU_L;
    Float_t selectedLeptons_RelIso_SLU_L;
    Float_t selectedLeptons_InvMass_SLU_L;
    Bool_t selectedLeptons_IsMuon_SLU_L;

    Float_t selectedZPairPlusHiggsFJ_InvMass_SLU_L;
    Float_t selectedZPairPlusHiggsFJ_pt_SLU_L;

    Float_t selectedVBFJets_MaxBTag_SLU_L;

    Float_t selectedZPairPlusHiggsFJPlusVBFJets_PtVecSum_SLU_L;
    Float_t selectedZPairPlusHiggsFJPlusVBFJets_PtScalarSum_SLU_L;

    Float_t selectedZPairPlusHiggsFJPlusVBFJets_PtVecOverScalarSum_SLU_L;

    //HLT 
    Bool_t HLT_Ele32_WPTight_Gsf_L1DoubleEG_SLU_L;
    Bool_t HLT_IsoMu27_SLU_L;
    Bool_t HLT_Mu50_SLU_L;
    Bool_t HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_SLU_L;
    Bool_t HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_SLU_L;
    //2016 in other years just set these to false
    Bool_t HLT_Ele27_WPTight_Gsf_SLU_L;
    Bool_t HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_SLU_L;
    //Tight/Veto lep variables
    Bool_t tightLepLeadIsElec_SLU_L;
    Bool_t tightLepTrailingIsElec_SLU_L;
    Bool_t tightLepLeadIsMuon_SLU_L;
    Bool_t tightLepTrailingIsMuon_SLU_L;
    Int_t tightLepLeadInd_SLU_L;
    Int_t tightLepTrailingInd_SLU_L;
    Float_t tightLepLeadPt_SLU_L;
    Float_t tightLepTrailingPt_SLU_L;
    Float_t tightLepLeadEta_SLU_L;
    Float_t tightLepTrailingEta_SLU_L;
    Float_t tightLepLeadPhi_SLU_L;
    Float_t tightLepTrailingPhi_SLU_L;
    Float_t tightLepLeadMass_SLU_L;
    Float_t tightLepTrailingMass_SLU_L;
    //042024SFAndSuchAdditions
    //PU JetID
    std::vector<Int_t> Jet_puId_SLU_L;
    //additional 042024Branches starting with this presel script
    //PUID SF check
    std::vector<Bool_t> Jet_LowPtPassesPUID_SLU_L;

    //more 042024Branches starting with selection
    Bool_t selectedLeadVBFJet_PUIDSFEligible_SLU_L;
    Bool_t selectedTrailingVBFJet_PUIDSFEligible_SLU_L;

    //05052024 Additions for PN regress mass scaling and resolution corrections
    UInt_t luminosityBlock_SLU_L;
    ULong64_t event_SLU_L;
    

    TTree *passingEvSemiLepUniqueTree = new TTree("passingEvSemiLepUniqueTree", "passingEvSemiLepUniqueTree");

    passingEvSemiLepUniqueTree->Branch("run_SLU_L",&run_SLU_L,"run_SLU_L/i");
    passingEvSemiLepUniqueTree->Branch("event_SLU_L",&event_SLU_L,"event_SLU_L/l");

    passingEvSemiLepUniqueTree->Branch("datasetType_SLU_L",&datasetType_SLU_L,"datasetType_SLU_L/i");

    passingEvSemiLepUniqueTree->Branch("yearType_SLU_L",&yearType_SLU_L,"yearType_SLU_L/i");

    passingEvSemiLepUniqueTree->Branch("runAlphNum_SLU_L",&runAlphNum_SLU_L,"runAlphNum_SLU_L/i");
    passingEvSemiLepUniqueTree->Branch("APV_SLU_L",&APV_SLU_L,"APV_SLU_L/O");

    passingEvSemiLepUniqueTree->Branch("eventNAK4Jets_SLU_L",&eventNAK4Jets_SLU_L,"eventNAK4Jets_SLU_L/i");
    passingEvSemiLepUniqueTree->Branch("eventNAK8Jets_SLU_L",&eventNAK8Jets_SLU_L,"eventNAK8Jets_SLU_L/i");
    passingEvSemiLepUniqueTree->Branch("eventNMuons_SLU_L",&eventNMuons_SLU_L,"eventNMuons_SLU_L/i");
    passingEvSemiLepUniqueTree->Branch("eventNElectrons_SLU_L",&eventNElectrons_SLU_L,"eventNElectrons_SLU_L/i");

    passingEvSemiLepUniqueTree->Branch("Jet_eta_SLU_L",&Jet_eta_SLU_L);
    passingEvSemiLepUniqueTree->Branch("Jet_pt_SLU_L",&Jet_pt_SLU_L);
    passingEvSemiLepUniqueTree->Branch("Jet_phi_SLU_L",&Jet_phi_SLU_L);
    passingEvSemiLepUniqueTree->Branch("Jet_mass_SLU_L",&Jet_mass_SLU_L);
    passingEvSemiLepUniqueTree->Branch("Jet_jetId_SLU_L",&Jet_jetId_SLU_L);
    passingEvSemiLepUniqueTree->Branch("Jet_btagDeepFlavB_SLU_L",&Jet_btagDeepFlavB_SLU_L);

    passingEvSemiLepUniqueTree->Branch("fixedGridRhoFastjetAll_SLU_L",&fixedGridRhoFastjetAll_SLU_L,"fixedGridRhoFastjetAll_SLU_L/F");
    

    passingEvSemiLepUniqueTree->Branch("eventNAK4JetsPassingCuts_SLU_L",&eventNAK4JetsPassingCuts_SLU_L,"eventNAK4JetsPassingCuts_SLU_L/i");

    passingEvSemiLepUniqueTree->Branch("selectedHiggsFJ_pt_SLU_L",&selectedHiggsFJ_pt_SLU_L,"selectedHiggsFJ_pt_SLU_L/F");
    passingEvSemiLepUniqueTree->Branch("selectedHiggsFJ_eta_SLU_L",&selectedHiggsFJ_eta_SLU_L,"selectedHiggsFJ_eta_SLU_L/F");
    passingEvSemiLepUniqueTree->Branch("selectedHiggsFJ_phi_SLU_L",&selectedHiggsFJ_phi_SLU_L,"selectedHiggsFJ_phi_SLU_L/F");
    passingEvSemiLepUniqueTree->Branch("selectedZFJ_ParticleNet_HbbvsQCD_SLU_L",&selectedZFJ_ParticleNet_HbbvsQCD_SLU_L,"selectedZFJ_ParticleNet_HbbvsQCD_SLU_L/F");
    passingEvSemiLepUniqueTree->Branch("selectedHiggsFJ_ParticleNet_HbbvsQCD_SLU_L",&selectedHiggsFJ_ParticleNet_HbbvsQCD_SLU_L,"selectedHiggsFJ_ParticleNet_HbbvsQCD_SLU_L/F");
    passingEvSemiLepUniqueTree->Branch("selectedZFJ_pt_SLU_L",&selectedZFJ_pt_SLU_L,"selectedZFJ_pt_SLU_L/F");
    passingEvSemiLepUniqueTree->Branch("selectedZFJ_eta_SLU_L",&selectedZFJ_eta_SLU_L,"selectedZFJ_eta_SLU_L/F");
    passingEvSemiLepUniqueTree->Branch("selectedZFJ_phi_SLU_L",&selectedZFJ_phi_SLU_L,"selectedZFJ_phi_SLU_L/F");
    passingEvSemiLepUniqueTree->Branch("selectedZFJ_ParticleNet_ZvsQCD_SLU_L",&selectedZFJ_ParticleNet_ZvsQCD_SLU_L,"selectedZFJ_ParticleNet_ZvsQCD_SLU_L/F");
    passingEvSemiLepUniqueTree->Branch("selectedHiggsFJ_ParticleNet_ZvsQCD_SLU_L",&selectedHiggsFJ_ParticleNet_ZvsQCD_SLU_L,"selectedHiggsFJ_ParticleNet_ZvsQCD_SLU_L/F");

    passingEvSemiLepUniqueTree->Branch("selectedZFJ_InvMass_SLU_L",&selectedZFJ_InvMass_SLU_L,"selectedZFJ_InvMass_SLU_L/F");
    passingEvSemiLepUniqueTree->Branch("selectedHiggsFJ_InvMass_SLU_L",&selectedHiggsFJ_InvMass_SLU_L,"selectedHiggsFJ_InvMass_SLU_L/F");

    passingEvSemiLepUniqueTree->Branch("selectedZFJ_InvMassSoftDrop_SLU_L",&selectedZFJ_InvMassSoftDrop_SLU_L,"selectedZFJ_InvMassSoftDrop_SLU_L/F");
    passingEvSemiLepUniqueTree->Branch("selectedHiggsFJ_InvMassSoftDrop_SLU_L",&selectedHiggsFJ_InvMassSoftDrop_SLU_L,"selectedHiggsFJ_InvMassSoftDrop_SLU_L/F");

    passingEvSemiLepUniqueTree->Branch("selectedZFJ_InvMassPNRegress_SLU_L",&selectedZFJ_InvMassPNRegress_SLU_L,"selectedZFJ_InvMassPNRegress_SLU_L/F");
    passingEvSemiLepUniqueTree->Branch("selectedHiggsFJ_InvMassPNRegress_SLU_L",&selectedHiggsFJ_InvMassPNRegress_SLU_L,"selectedHiggsFJ_InvMassPNRegress_SLU_L/F");

    passingEvSemiLepUniqueTree->Branch("selectedHiggsFJ_ParticleNetMD_QCD_SLU_L", &selectedHiggsFJ_ParticleNetMD_QCD_SLU_L);
    passingEvSemiLepUniqueTree->Branch("selectedHiggsFJ_ParticleNetMD_Xbb_SLU_L", &selectedHiggsFJ_ParticleNetMD_Xbb_SLU_L);
    passingEvSemiLepUniqueTree->Branch("selectedHiggsFJ_ParticleNetMD_Xcc_SLU_L", &selectedHiggsFJ_ParticleNetMD_Xcc_SLU_L);
    passingEvSemiLepUniqueTree->Branch("selectedHiggsFJ_ParticleNetMD_Xqq_SLU_L", &selectedHiggsFJ_ParticleNetMD_Xqq_SLU_L);

    passingEvSemiLepUniqueTree->Branch("selectedZFJ_ParticleNetMD_QCD_SLU_L", &selectedZFJ_ParticleNetMD_QCD_SLU_L);
    passingEvSemiLepUniqueTree->Branch("selectedZFJ_ParticleNetMD_Xbb_SLU_L", &selectedZFJ_ParticleNetMD_Xbb_SLU_L);
    passingEvSemiLepUniqueTree->Branch("selectedZFJ_ParticleNetMD_Xcc_SLU_L", &selectedZFJ_ParticleNetMD_Xcc_SLU_L);
    passingEvSemiLepUniqueTree->Branch("selectedZFJ_ParticleNetMD_Xqq_SLU_L", &selectedZFJ_ParticleNetMD_Xqq_SLU_L);

    passingEvSemiLepUniqueTree->Branch("selectedLeadVBFJet_pt_SLU_L",&selectedLeadVBFJet_pt_SLU_L,"selectedLeadVBFJet_pt_SLU_L/F");
    passingEvSemiLepUniqueTree->Branch("selectedTrailingVBFJet_pt_SLU_L",&selectedTrailingVBFJet_pt_SLU_L,"selectedTrailingVBFJet_pt_SLU_L/F");
    passingEvSemiLepUniqueTree->Branch("selectedLeadVBFJet_eta_SLU_L",&selectedLeadVBFJet_eta_SLU_L,"selectedLeadVBFJet_eta_SLU_L/F");
    passingEvSemiLepUniqueTree->Branch("selectedTrailingVBFJet_eta_SLU_L",&selectedTrailingVBFJet_eta_SLU_L,"selectedTrailingVBFJet_eta_SLU_L/F");
    passingEvSemiLepUniqueTree->Branch("selectedVBFJets_EtaSep_SLU_L",&selectedVBFJets_EtaSep_SLU_L,"selectedVBFJets_EtaSep_SLU_L/F");
    passingEvSemiLepUniqueTree->Branch("selectedVBFJets_InvMass_SLU_L",&selectedVBFJets_InvMass_SLU_L,"selectedVBFJets_InvMass_SLU_L/F");

    passingEvSemiLepUniqueTree->Branch("selectedLeadLepton_pt_SLU_L",&selectedLeadLepton_pt_SLU_L,"selectedLeadLepton_pt_SLU_L/F");
    passingEvSemiLepUniqueTree->Branch("selectedTrailingLepton_pt_SLU_L",&selectedTrailingLepton_pt_SLU_L,"selectedTrailingLepton_pt_SLU_L/F");
    passingEvSemiLepUniqueTree->Branch("selectedLeadLepton_eta_SLU_L",&selectedLeadLepton_eta_SLU_L,"selectedLeadLepton_eta_SLU_L/F");
    passingEvSemiLepUniqueTree->Branch("selectedTrailingLepton_eta_SLU_L",&selectedTrailingLepton_eta_SLU_L,"selectedTrailingLepton_eta_SLU_L/F");
    passingEvSemiLepUniqueTree->Branch("selectedLeadLepton_phi_SLU_L",&selectedLeadLepton_phi_SLU_L,"selectedLeadLepton_phi_SLU_L/F");
    passingEvSemiLepUniqueTree->Branch("selectedTrailingLepton_phi_SLU_L",&selectedTrailingLepton_phi_SLU_L,"selectedTrailingLepton_phi_SLU_L/F");
    passingEvSemiLepUniqueTree->Branch("selectedLeadLepton_SIP3D_SLU_L",&selectedLeadLepton_SIP3D_SLU_L,"selectedLeadLepton_SIP3D_SLU_L/F");
    passingEvSemiLepUniqueTree->Branch("selectedTrailingLepton_SIP3D_SLU_L",&selectedTrailingLepton_SIP3D_SLU_L,"selectedTrailingLepton_SIP3D_SLU_L/F");
    passingEvSemiLepUniqueTree->Branch("selectedLeptons_RelIso_SLU_L",&selectedLeptons_RelIso_SLU_L,"selectedLeptons_RelIso_SLU_L/F");
    passingEvSemiLepUniqueTree->Branch("selectedLeptons_InvMass_SLU_L",&selectedLeptons_InvMass_SLU_L,"selectedLeptons_InvMass_SLU_L/F");
    passingEvSemiLepUniqueTree->Branch("selectedLeptons_IsMuon_SLU_L",&selectedLeptons_IsMuon_SLU_L,"selectedLeptons_IsMuon_SLU_L/O");

    passingEvSemiLepUniqueTree->Branch("selectedZPairPlusHiggsFJ_InvMass_SLU_L",&selectedZPairPlusHiggsFJ_InvMass_SLU_L,"selectedZPairPlusHiggsFJ_InvMass_SLU_L/F");
    passingEvSemiLepUniqueTree->Branch("selectedZPairPlusHiggsFJ_pt_SLU_L",&selectedZPairPlusHiggsFJ_pt_SLU_L,"selectedZPairPlusHiggsFJ_pt_SLU_L/F");

    passingEvSemiLepUniqueTree->Branch("selectedVBFJets_MaxBTag_SLU_L",&selectedVBFJets_MaxBTag_SLU_L,"selectedVBFJets_MaxBTag_SLU_L/F");


    passingEvSemiLepUniqueTree->Branch("selectedZPairPlusHiggsFJPlusVBFJets_PtVecSum_SLU_L",&selectedZPairPlusHiggsFJPlusVBFJets_PtVecSum_SLU_L,"selectedZPairPlusHiggsFJPlusVBFJets_PtVecSum_SLU_L/F");
    passingEvSemiLepUniqueTree->Branch("selectedZPairPlusHiggsFJPlusVBFJets_PtScalarSum_SLU_L",&selectedZPairPlusHiggsFJPlusVBFJets_PtScalarSum_SLU_L,"selectedZPairPlusHiggsFJPlusVBFJets_PtScalarSum_SLU_L/F");
    passingEvSemiLepUniqueTree->Branch("selectedZPairPlusHiggsFJPlusVBFJets_PtVecOverScalarSum_SLU_L",&selectedZPairPlusHiggsFJPlusVBFJets_PtVecOverScalarSum_SLU_L,"selectedZPairPlusHiggsFJPlusVBFJets_PtVecOverScalarSum_SLU_L/F");

    passingEvSemiLepUniqueTree->Branch("HLT_Ele32_WPTight_Gsf_L1DoubleEG_SLU_L",&HLT_Ele32_WPTight_Gsf_L1DoubleEG_SLU_L,"HLT_Ele32_WPTight_Gsf_L1DoubleEG_SLU_L/O");
    passingEvSemiLepUniqueTree->Branch("HLT_IsoMu27_SLU_L",&HLT_IsoMu27_SLU_L,"HLT_IsoMu27_SLU_L/O");
    passingEvSemiLepUniqueTree->Branch("HLT_Mu50_SLU_L",&HLT_Mu50_SLU_L,"HLT_Mu50_SLU_L/O");
    passingEvSemiLepUniqueTree->Branch("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_SLU_L",&HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_SLU_L,"HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_SLU_L/O");
    passingEvSemiLepUniqueTree->Branch("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_SLU_L",&HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_SLU_L,"HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_SLU_L/O");

    //2016
    passingEvSemiLepUniqueTree->Branch("HLT_Ele27_WPTight_Gsf_SLU_L",&HLT_Ele27_WPTight_Gsf_SLU_L,"HLT_Ele27_WPTight_Gsf_SLU_L/O");
    passingEvSemiLepUniqueTree->Branch("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_SLU_L",&HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_SLU_L,"HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_SLU_L/O");

    passingEvSemiLepUniqueTree->Branch("tightLepLeadIsElec_SLU_L",&tightLepLeadIsElec_SLU_L,"tightLepLeadIsElec_SLU_L/O");
    passingEvSemiLepUniqueTree->Branch("tightLepTrailingIsElec_SLU_L",&tightLepTrailingIsElec_SLU_L,"tightLepTrailingIsElec_SLU_L/O");
    passingEvSemiLepUniqueTree->Branch("tightLepLeadIsMuon_SLU_L",&tightLepLeadIsMuon_SLU_L,"tightLepLeadIsMuon_SLU_L/O");
    passingEvSemiLepUniqueTree->Branch("tightLepTrailingIsMuon_SLU_L",&tightLepTrailingIsMuon_SLU_L,"tightLepTrailingIsMuon_SLU_L/O");
    passingEvSemiLepUniqueTree->Branch("tightLepLeadInd_SLU_L",&tightLepLeadInd_SLU_L,"tightLepLeadInd_SLU_L/I");
    passingEvSemiLepUniqueTree->Branch("tightLepTrailingInd_SLU_L",&tightLepTrailingInd_SLU_L,"tightLepTrailingInd_SLU_L/I");
    passingEvSemiLepUniqueTree->Branch("tightLepLeadPt_SLU_L",&tightLepLeadPt_SLU_L,"tightLepLeadPt_SLU_L/F");
    passingEvSemiLepUniqueTree->Branch("tightLepTrailingPt_SLU_L",&tightLepTrailingPt_SLU_L,"tightLepTrailingPt_SLU_L/F");
    passingEvSemiLepUniqueTree->Branch("tightLepLeadEta_SLU_L",&tightLepLeadEta_SLU_L,"tightLepLeadEta_SLU_L/F");
    passingEvSemiLepUniqueTree->Branch("tightLepTrailingEta_SLU_L",&tightLepTrailingEta_SLU_L,"tightLepTrailingEta_SLU_L/F");
    passingEvSemiLepUniqueTree->Branch("tightLepLeadPhi_SLU_L",&tightLepLeadPhi_SLU_L,"tightLepLeadPhi_SLU_L/F");
    passingEvSemiLepUniqueTree->Branch("tightLepTrailingPhi_SLU_L",&tightLepTrailingPhi_SLU_L,"tightLepTrailingPhi_SLU_L/F");
    passingEvSemiLepUniqueTree->Branch("tightLepLeadMass_SLU_L",&tightLepLeadMass_SLU_L,"tightLepLeadMass_SLU_L/F");
    passingEvSemiLepUniqueTree->Branch("tightLepTrailingMass_SLU_L",&tightLepTrailingMass_SLU_L,"tightLepTrailingMass_SLU_L/F");

    //042024SFAndSuchAdditions
    //PU JetID
    passingEvSemiLepUniqueTree->Branch("Jet_puId_SLU_L",&Jet_puId_SLU_L);
    //additional 042024Branches starting with this script
    //PUID SF check
    passingEvSemiLepUniqueTree->Branch("Jet_LowPtPassesPUID_SLU_L",&Jet_LowPtPassesPUID_SLU_L);

    //more 042024Branches starting with selection
    passingEvSemiLepUniqueTree->Branch("selectedLeadVBFJet_PUIDSFEligible_SLU_L",&selectedLeadVBFJet_PUIDSFEligible_SLU_L,"selectedLeadVBFJet_PUIDSFEligible_SLU_L/O");
    passingEvSemiLepUniqueTree->Branch("selectedTrailingVBFJet_PUIDSFEligible_SLU_L",&selectedTrailingVBFJet_PUIDSFEligible_SLU_L,"selectedTrailingVBFJet_PUIDSFEligible_SLU_L/O");

    //05052024 Additions for PN regress mass scaling and resolution corrections
    passingEvSemiLepUniqueTree->Branch("luminosityBlock_SLU_L",&luminosityBlock_SLU_L,"luminosityBlock_SLU_L/i");


    
    std::vector<int> runVec;
    std::vector<int> evVec;
    

    std::cout << "Going into file loop.\n";

    for (UInt_t k=0; k<fileAr.size(); k++){
        if (endAfter && allCtr > NToEndTot) break;
        if (debug) std::cout<<"File:    "<<fileAr[k]<<"\n";
        //Open the file, get the Events tree
        TFile* tmpfile = TFile::Open(fileAr[k].c_str());
        //outFile->cd();
        TTreeReader myEventsReader("passingEvSemiLepTree", tmpfile);



        TTreeReaderValue<UInt_t> run_SL_L(myEventsReader, "run_SL_L");
        TTreeReaderValue<ULong64_t> event_SL_L(myEventsReader,  "event_SL_L");

        TTreeReaderValue<UInt_t> datasetType_SL_L(myEventsReader,  "datasetType_SL_L");

        TTreeReaderValue<UInt_t> yearType_SL_L(myEventsReader,  "yearType_SL_L");

        TTreeReaderValue<UInt_t> runAlphNum_SL_L(myEventsReader, "runAlphNum_SL_L");
        TTreeReaderValue<Bool_t> APV_SL_L(myEventsReader, "APV_SL_L");


        TTreeReaderValue<UInt_t> eventNAK4Jets_SL_L(myEventsReader, "eventNAK4Jets_SL_L");
        TTreeReaderValue<UInt_t> eventNAK8Jets_SL_L(myEventsReader,  "eventNAK8Jets_SL_L");
        TTreeReaderValue<UInt_t> eventNMuons_SL_L(myEventsReader, "eventNMuons_SL_L");
        TTreeReaderValue<UInt_t> eventNElectrons_SL_L(myEventsReader,  "eventNElectrons_SL_L");

        TTreeReaderArray<Float_t> Jet_eta_SL_L(myEventsReader, "Jet_eta_SL_L");
        TTreeReaderArray<Float_t> Jet_pt_SL_L(myEventsReader, "Jet_pt_SL_L");
        TTreeReaderArray<Float_t> Jet_phi_SL_L(myEventsReader, "Jet_phi_SL_L");
        TTreeReaderArray<Float_t> Jet_mass_SL_L(myEventsReader, "Jet_mass_SL_L");
        TTreeReaderArray<Int_t> Jet_jetId_SL_L(myEventsReader, "Jet_jetId_SL_L");
        TTreeReaderArray<Float_t> Jet_btagDeepFlavB_SL_L(myEventsReader, "Jet_btagDeepFlavB_SL_L");

        TTreeReaderValue<Float_t> fixedGridRhoFastjetAll_SL_L(myEventsReader, "fixedGridRhoFastjetAll_SL_L");

        TTreeReaderValue<UInt_t> eventNAK4JetsPassingCuts_SL_L(myEventsReader, "eventNAK4JetsPassingCuts_SL_L");

        TTreeReaderValue<Float_t> selectedHiggsFJ_pt_SL_L(myEventsReader,  "selectedHiggsFJ_pt_SL_L");
        TTreeReaderValue<Float_t> selectedHiggsFJ_eta_SL_L(myEventsReader,  "selectedHiggsFJ_eta_SL_L");
        TTreeReaderValue<Float_t> selectedHiggsFJ_phi_SL_L(myEventsReader,  "selectedHiggsFJ_phi_SL_L");
        TTreeReaderValue<Float_t> selectedZFJ_ParticleNet_HbbvsQCD_SL_L(myEventsReader,  "selectedZFJ_ParticleNet_HbbvsQCD_SL_L");
        TTreeReaderValue<Float_t> selectedHiggsFJ_ParticleNet_HbbvsQCD_SL_L(myEventsReader,  "selectedHiggsFJ_ParticleNet_HbbvsQCD_SL_L");
        TTreeReaderValue<Float_t> selectedZFJ_pt_SL_L(myEventsReader,  "selectedZFJ_pt_SL_L");
        TTreeReaderValue<Float_t> selectedZFJ_eta_SL_L(myEventsReader,  "selectedZFJ_eta_SL_L");
        TTreeReaderValue<Float_t> selectedZFJ_phi_SL_L(myEventsReader,  "selectedZFJ_phi_SL_L");
        TTreeReaderValue<Float_t> selectedZFJ_ParticleNet_ZvsQCD_SL_L(myEventsReader,  "selectedZFJ_ParticleNet_ZvsQCD_SL_L");
        TTreeReaderValue<Float_t> selectedHiggsFJ_ParticleNet_ZvsQCD_SL_L(myEventsReader,  "selectedHiggsFJ_ParticleNet_ZvsQCD_SL_L");

        TTreeReaderValue<Float_t> selectedZFJ_InvMass_SL_L(myEventsReader,  "selectedZFJ_InvMass_SL_L");
        TTreeReaderValue<Float_t> selectedHiggsFJ_InvMass_SL_L(myEventsReader,  "selectedHiggsFJ_InvMass_SL_L");

        TTreeReaderValue<Float_t> selectedZFJ_InvMassSoftDrop_SL_L(myEventsReader,  "selectedZFJ_InvMassSoftDrop_SL_L");
        TTreeReaderValue<Float_t> selectedHiggsFJ_InvMassSoftDrop_SL_L(myEventsReader,  "selectedHiggsFJ_InvMassSoftDrop_SL_L");

        TTreeReaderValue<Float_t> selectedZFJ_InvMassPNRegress_SL_L(myEventsReader,  "selectedZFJ_InvMassPNRegress_SL_L");
        TTreeReaderValue<Float_t> selectedHiggsFJ_InvMassPNRegress_SL_L(myEventsReader,  "selectedHiggsFJ_InvMassPNRegress_SL_L");

        TTreeReaderValue<Float_t> selectedHiggsFJ_ParticleNetMD_QCD_SL_L(myEventsReader, "selectedHiggsFJ_ParticleNetMD_QCD_SL_L");
        TTreeReaderValue<Float_t> selectedHiggsFJ_ParticleNetMD_Xbb_SL_L(myEventsReader, "selectedHiggsFJ_ParticleNetMD_Xbb_SL_L");
        TTreeReaderValue<Float_t> selectedHiggsFJ_ParticleNetMD_Xcc_SL_L(myEventsReader, "selectedHiggsFJ_ParticleNetMD_Xcc_SL_L");
        TTreeReaderValue<Float_t> selectedHiggsFJ_ParticleNetMD_Xqq_SL_L(myEventsReader, "selectedHiggsFJ_ParticleNetMD_Xqq_SL_L");

        TTreeReaderValue<Float_t> selectedZFJ_ParticleNetMD_QCD_SL_L(myEventsReader, "selectedZFJ_ParticleNetMD_QCD_SL_L");
        TTreeReaderValue<Float_t> selectedZFJ_ParticleNetMD_Xbb_SL_L(myEventsReader, "selectedZFJ_ParticleNetMD_Xbb_SL_L");
        TTreeReaderValue<Float_t> selectedZFJ_ParticleNetMD_Xcc_SL_L(myEventsReader, "selectedZFJ_ParticleNetMD_Xcc_SL_L");
        TTreeReaderValue<Float_t> selectedZFJ_ParticleNetMD_Xqq_SL_L(myEventsReader, "selectedZFJ_ParticleNetMD_Xqq_SL_L");

        TTreeReaderValue<Float_t> selectedLeadVBFJet_pt_SL_L(myEventsReader,  "selectedLeadVBFJet_pt_SL_L");
        TTreeReaderValue<Float_t> selectedTrailingVBFJet_pt_SL_L(myEventsReader,  "selectedTrailingVBFJet_pt_SL_L");
        TTreeReaderValue<Float_t> selectedLeadVBFJet_eta_SL_L(myEventsReader,  "selectedLeadVBFJet_eta_SL_L");
        TTreeReaderValue<Float_t> selectedTrailingVBFJet_eta_SL_L(myEventsReader,  "selectedTrailingVBFJet_eta_SL_L");
        TTreeReaderValue<Float_t> selectedVBFJets_EtaSep_SL_L(myEventsReader,  "selectedVBFJets_EtaSep_SL_L");
        TTreeReaderValue<Float_t> selectedVBFJets_InvMass_SL_L(myEventsReader,  "selectedVBFJets_InvMass_SL_L");

        TTreeReaderValue<Float_t> selectedLeadLepton_pt_SL_L(myEventsReader,  "selectedLeadLepton_pt_SL_L");
        TTreeReaderValue<Float_t> selectedTrailingLepton_pt_SL_L(myEventsReader,  "selectedTrailingLepton_pt_SL_L");
        TTreeReaderValue<Float_t> selectedLeadLepton_eta_SL_L(myEventsReader,  "selectedLeadLepton_eta_SL_L");
        TTreeReaderValue<Float_t> selectedTrailingLepton_eta_SL_L(myEventsReader,  "selectedTrailingLepton_eta_SL_L");
        TTreeReaderValue<Float_t> selectedLeadLepton_phi_SL_L(myEventsReader,  "selectedLeadLepton_phi_SL_L");
        TTreeReaderValue<Float_t> selectedTrailingLepton_phi_SL_L(myEventsReader,  "selectedTrailingLepton_phi_SL_L");
        TTreeReaderValue<Float_t> selectedLeadLepton_SIP3D_SL_L(myEventsReader,  "selectedLeadLepton_SIP3D_SL_L");
        TTreeReaderValue<Float_t> selectedTrailingLepton_SIP3D_SL_L(myEventsReader,  "selectedTrailingLepton_SIP3D_SL_L");
        TTreeReaderValue<Float_t> selectedLeptons_RelIso_SL_L(myEventsReader,  "selectedLeptons_RelIso_SL_L");
        TTreeReaderValue<Float_t> selectedLeptons_InvMass_SL_L(myEventsReader,  "selectedLeptons_InvMass_SL_L");
        TTreeReaderValue<Bool_t> selectedLeptons_IsMuon_SL_L(myEventsReader,  "selectedLeptons_IsMuon_SL_L");

        TTreeReaderValue<Float_t> selectedZPairPlusHiggsFJ_InvMass_SL_L(myEventsReader,  "selectedZPairPlusHiggsFJ_InvMass_SL_L");
        TTreeReaderValue<Float_t> selectedZPairPlusHiggsFJ_pt_SL_L(myEventsReader,  "selectedZPairPlusHiggsFJ_pt_SL_L");

        TTreeReaderValue<Float_t> selectedVBFJets_MaxBTag_SL_L(myEventsReader,  "selectedVBFJets_MaxBTag_SL_L");


        TTreeReaderValue<Float_t> selectedZPairPlusHiggsFJPlusVBFJets_PtVecSum_SL_L(myEventsReader,  "selectedZPairPlusHiggsFJPlusVBFJets_PtVecSum_SL_L");
        TTreeReaderValue<Float_t> selectedZPairPlusHiggsFJPlusVBFJets_PtScalarSum_SL_L(myEventsReader,  "selectedZPairPlusHiggsFJPlusVBFJets_PtScalarSum_SL_L");
        TTreeReaderValue<Float_t> selectedZPairPlusHiggsFJPlusVBFJets_PtVecOverScalarSum_SL_L(myEventsReader,  "selectedZPairPlusHiggsFJPlusVBFJets_PtVecOverScalarSum_SL_L");

        //HLT
        TTreeReaderValue<Bool_t> HLT_Ele32_WPTight_Gsf_L1DoubleEG_SL_L(myEventsReader,"HLT_Ele32_WPTight_Gsf_L1DoubleEG_SL_L");
        TTreeReaderValue<Bool_t> HLT_IsoMu27_SL_L(myEventsReader,"HLT_IsoMu27_SL_L");
        TTreeReaderValue<Bool_t> HLT_Mu50_SL_L(myEventsReader,"HLT_Mu50_SL_L");
        TTreeReaderValue<Bool_t> HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_SL_L(myEventsReader,"HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_SL_L");
        TTreeReaderValue<Bool_t> HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_SL_L(myEventsReader,"HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_SL_L");

        TTreeReaderValue<Bool_t> HLT_Ele27_WPTight_Gsf_SL_L(myEventsReader,"HLT_Ele27_WPTight_Gsf_SL_L");
        TTreeReaderValue<Bool_t> HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_SL_L(myEventsReader,"HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_SL_L");

        //Tight Leps from Preselection
        TTreeReaderValue<Int_t> tightLepLeadInd_SL_L(myEventsReader,"tightLepLeadInd_SL_L");
        TTreeReaderValue<Int_t> tightLepTrailingInd_SL_L(myEventsReader,"tightLepTrailingInd_SL_L");
        TTreeReaderValue<Bool_t> tightLepLeadIsElec_SL_L(myEventsReader,"tightLepLeadIsElec_SL_L");
        TTreeReaderValue<Bool_t> tightLepTrailingIsElec_SL_L(myEventsReader,"tightLepTrailingIsElec_SL_L");
        TTreeReaderValue<Bool_t> tightLepLeadIsMuon_SL_L(myEventsReader,"tightLepLeadIsMuon_SL_L");
        TTreeReaderValue<Bool_t> tightLepTrailingIsMuon_SL_L(myEventsReader,"tightLepTrailingIsMuon_SL_L");
        TTreeReaderValue<Float_t> tightLepLeadPt_SL_L(myEventsReader,"tightLepLeadPt_SL_L");
        TTreeReaderValue<Float_t> tightLepTrailingPt_SL_L(myEventsReader,"tightLepTrailingPt_SL_L");
        TTreeReaderValue<Float_t> tightLepLeadEta_SL_L(myEventsReader,"tightLepLeadEta_SL_L");
        TTreeReaderValue<Float_t> tightLepTrailingEta_SL_L(myEventsReader,"tightLepTrailingEta_SL_L");
        TTreeReaderValue<Float_t> tightLepLeadPhi_SL_L(myEventsReader,"tightLepLeadPhi_SL_L");
        TTreeReaderValue<Float_t> tightLepTrailingPhi_SL_L(myEventsReader,"tightLepTrailingPhi_SL_L");
        TTreeReaderValue<Float_t> tightLepLeadMass_SL_L(myEventsReader,"tightLepLeadMass_SL_L");
        TTreeReaderValue<Float_t> tightLepTrailingMass_SL_L(myEventsReader,"tightLepTrailingMass_SL_L");

        TTreeReaderValue<UInt_t> nVetoElec_SL_L(myEventsReader,"nVetoElec_SL_L");
        TTreeReaderValue<UInt_t> nVetoMuon_SL_L(myEventsReader,"nVetoMuon_SL_L");
        TTreeReaderArray<Int_t> vetoElecInd_SL_L(myEventsReader,"vetoElecInd_SL_L");
        TTreeReaderArray<Int_t> vetoMuonInd_SL_L(myEventsReader,"vetoMuonInd_SL_L");

        //042024SFAndSuchAdditions
        //PU JetID
        TTreeReaderArray<Int_t> Jet_puId_SL_L(myEventsReader, "Jet_puId_SL_L");

        //additional 042024Branches starting with preselection
        //PUID SF check
        TTreeReaderArray<Bool_t> Jet_LowPtPassesPUID_SL_L(myEventsReader, "Jet_LowPtPassesPUID_SL_L");

        //more 042024Branches starting with selection
        TTreeReaderValue<Bool_t> selectedLeadVBFJet_PUIDSFEligible_SL_L(myEventsReader, "selectedLeadVBFJet_PUIDSFEligible_SL_L");
        TTreeReaderValue<Bool_t> selectedTrailingVBFJet_PUIDSFEligible_SL_L(myEventsReader, "selectedTrailingVBFJet_PUIDSFEligible_SL_L");

        //05052024 Additions for PN regress mass scaling and resolution corrections
        TTreeReaderValue<UInt_t> luminosityBlock_SL_L(myEventsReader, "luminosityBlock_SL_L");


        if (k % 10 == 0){
            double tmpTime = (double)(clock()-startt)/CLOCKS_PER_SEC;
            std::cout << "Going into event loop for file" << k << " .\ttime:" << (double)(clock()-startt)/CLOCKS_PER_SEC << "\n";
        }
        std::cout << "File " << k << " Current nEv: " << allCtr << " Current unique: " << uniqueCtr << " time " << (double)(clock()-startt)/CLOCKS_PER_SEC << "\n";
        

        uint evCount = 0;
        //EvLoop
        while (myEventsReader.Next()) {
            
            if (endEvAfter){
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
            
            evCount += 1;
            allCtr += 1;

            bool isUnique = true;

            for (uint runEvInt = 0; runEvInt < runVec.size(); runEvInt++) {
                if (runVec[runEvInt] == *run_SL_L && evVec[runEvInt] == *event_SL_L) {
                    isUnique = false;
                    break;
                }
            }

            

            if (isUnique){
                uniqueCtr += 1;
                runVec.push_back(*run_SL_L);
                evVec.push_back(*event_SL_L);

            
                //Fill BDT SemiLep Tree

                run_SLU_L = *run_SL_L;
                event_SLU_L = *event_SL_L;

                datasetType_SLU_L = *datasetType_SL_L;
                
                yearType_SLU_L = *yearType_SL_L;

                runAlphNum_SLU_L = *runAlphNum_SL_L;
                APV_SLU_L = *APV_SL_L;

                eventNAK4Jets_SLU_L = *eventNAK4Jets_SL_L;
                eventNAK8Jets_SLU_L = *eventNAK8Jets_SL_L;
                eventNMuons_SLU_L = *eventNMuons_SL_L;
                eventNElectrons_SLU_L = *eventNElectrons_SL_L;

                for (UInt_t nJetItr=0; nJetItr<*eventNAK4Jets_SL_L;nJetItr++){
                    Jet_eta_SLU_L.push_back(Jet_eta_SL_L[nJetItr]);
                    Jet_pt_SLU_L.push_back(Jet_pt_SL_L[nJetItr]);
                    Jet_phi_SLU_L.push_back(Jet_phi_SL_L[nJetItr]);
                    Jet_mass_SLU_L.push_back(Jet_mass_SL_L[nJetItr]);
                    Jet_jetId_SLU_L.push_back(Jet_jetId_SL_L[nJetItr]);
                    Jet_btagDeepFlavB_SLU_L.push_back(Jet_btagDeepFlavB_SL_L[nJetItr]);
                }
                fixedGridRhoFastjetAll_SLU_L = *fixedGridRhoFastjetAll_SL_L;

                eventNAK4JetsPassingCuts_SLU_L = *eventNAK4JetsPassingCuts_SL_L;

                

                selectedHiggsFJ_pt_SLU_L = *selectedHiggsFJ_pt_SL_L;
                selectedZFJ_pt_SLU_L = *selectedZFJ_pt_SL_L;
                selectedHiggsFJ_eta_SLU_L = *selectedHiggsFJ_eta_SL_L;
                selectedZFJ_eta_SLU_L = *selectedZFJ_eta_SL_L;
                selectedZFJ_InvMass_SLU_L = *selectedZFJ_InvMass_SL_L;
                selectedHiggsFJ_phi_SLU_L = *selectedHiggsFJ_phi_SL_L;
                selectedZFJ_phi_SLU_L = *selectedZFJ_phi_SL_L;
                selectedHiggsFJ_InvMass_SLU_L = *selectedHiggsFJ_InvMass_SL_L;

                selectedZFJ_InvMassSoftDrop_SLU_L = *selectedZFJ_InvMassSoftDrop_SL_L;
                selectedHiggsFJ_InvMassSoftDrop_SLU_L = *selectedHiggsFJ_InvMassSoftDrop_SL_L;

                selectedZFJ_InvMassPNRegress_SLU_L = *selectedZFJ_InvMassPNRegress_SL_L;
                selectedHiggsFJ_InvMassPNRegress_SLU_L = *selectedHiggsFJ_InvMassPNRegress_SL_L;

                selectedZFJ_ParticleNet_HbbvsQCD_SLU_L = *selectedZFJ_ParticleNet_HbbvsQCD_SL_L;
                selectedHiggsFJ_ParticleNet_HbbvsQCD_SLU_L = *selectedHiggsFJ_ParticleNet_HbbvsQCD_SL_L;

                selectedZFJ_ParticleNet_ZvsQCD_SLU_L = *selectedZFJ_ParticleNet_ZvsQCD_SL_L;
                selectedHiggsFJ_ParticleNet_ZvsQCD_SLU_L = *selectedHiggsFJ_ParticleNet_ZvsQCD_SL_L;
                

                selectedHiggsFJ_ParticleNetMD_QCD_SLU_L = *selectedHiggsFJ_ParticleNetMD_QCD_SL_L;
                selectedHiggsFJ_ParticleNetMD_Xbb_SLU_L = *selectedHiggsFJ_ParticleNetMD_Xbb_SL_L;
                selectedHiggsFJ_ParticleNetMD_Xcc_SLU_L = *selectedHiggsFJ_ParticleNetMD_Xcc_SL_L;
                selectedHiggsFJ_ParticleNetMD_Xqq_SLU_L = *selectedHiggsFJ_ParticleNetMD_Xqq_SL_L;

                selectedZFJ_ParticleNetMD_QCD_SLU_L = *selectedZFJ_ParticleNetMD_QCD_SL_L;
                selectedZFJ_ParticleNetMD_Xbb_SLU_L = *selectedZFJ_ParticleNetMD_Xbb_SL_L;
                selectedZFJ_ParticleNetMD_Xcc_SLU_L = *selectedZFJ_ParticleNetMD_Xcc_SL_L;
                selectedZFJ_ParticleNetMD_Xqq_SLU_L = *selectedZFJ_ParticleNetMD_Xqq_SL_L;

                selectedLeadVBFJet_pt_SLU_L = *selectedLeadVBFJet_pt_SL_L;
                selectedTrailingVBFJet_pt_SLU_L = *selectedTrailingVBFJet_pt_SL_L;
                selectedLeadVBFJet_eta_SLU_L = *selectedLeadVBFJet_eta_SL_L;
                selectedTrailingVBFJet_eta_SLU_L = *selectedTrailingVBFJet_eta_SL_L;
                selectedVBFJets_EtaSep_SLU_L = *selectedVBFJets_EtaSep_SL_L;
                selectedVBFJets_InvMass_SLU_L = *selectedVBFJets_InvMass_SL_L;

                selectedLeadLepton_pt_SLU_L = *selectedLeadLepton_pt_SL_L;
                selectedTrailingLepton_pt_SLU_L = *selectedTrailingLepton_pt_SL_L;
                selectedLeadLepton_eta_SLU_L = *selectedLeadLepton_eta_SL_L;
                selectedTrailingLepton_eta_SLU_L = *selectedTrailingLepton_eta_SL_L;
                selectedLeadLepton_phi_SLU_L = *selectedLeadLepton_phi_SL_L;
                selectedTrailingLepton_phi_SLU_L = *selectedTrailingLepton_phi_SL_L;
                selectedLeadLepton_SIP3D_SLU_L = *selectedLeadLepton_SIP3D_SL_L;
                selectedTrailingLepton_SIP3D_SLU_L = *selectedTrailingLepton_SIP3D_SL_L;
                selectedLeptons_RelIso_SLU_L = *selectedLeptons_RelIso_SL_L;
                selectedLeptons_InvMass_SLU_L = *selectedLeptons_InvMass_SL_L;
                selectedLeptons_IsMuon_SLU_L = *selectedLeptons_IsMuon_SL_L;

                selectedZPairPlusHiggsFJ_InvMass_SLU_L = *selectedZPairPlusHiggsFJ_InvMass_SL_L;
                selectedZPairPlusHiggsFJ_pt_SLU_L = *selectedZPairPlusHiggsFJ_pt_SL_L;

                selectedVBFJets_MaxBTag_SLU_L = *selectedVBFJets_MaxBTag_SL_L;

                selectedZPairPlusHiggsFJPlusVBFJets_PtVecSum_SLU_L = *selectedZPairPlusHiggsFJPlusVBFJets_PtVecSum_SL_L;
                selectedZPairPlusHiggsFJPlusVBFJets_PtScalarSum_SLU_L = *selectedZPairPlusHiggsFJPlusVBFJets_PtScalarSum_SL_L;
                selectedZPairPlusHiggsFJPlusVBFJets_PtVecOverScalarSum_SLU_L = *selectedZPairPlusHiggsFJPlusVBFJets_PtVecOverScalarSum_SL_L;

                //HLT 
                HLT_Ele32_WPTight_Gsf_L1DoubleEG_SLU_L = *HLT_Ele32_WPTight_Gsf_L1DoubleEG_SL_L;
                HLT_IsoMu27_SLU_L = *HLT_IsoMu27_SL_L;
                HLT_Mu50_SLU_L = *HLT_Mu50_SL_L;
                HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_SLU_L = *HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_SL_L;
                HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_SLU_L = *HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_SL_L;

                HLT_Ele27_WPTight_Gsf_SLU_L = *HLT_Ele27_WPTight_Gsf_SL_L;
                HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_SLU_L = *HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_SL_L;

                tightLepLeadIsElec_SLU_L = *tightLepLeadIsElec_SL_L;
                tightLepTrailingIsElec_SLU_L = *tightLepTrailingIsElec_SL_L;
                tightLepLeadIsMuon_SLU_L = *tightLepLeadIsMuon_SL_L;
                tightLepTrailingIsMuon_SLU_L = *tightLepTrailingIsMuon_SL_L;
                tightLepLeadInd_SLU_L = *tightLepLeadInd_SL_L;
                tightLepTrailingInd_SLU_L = *tightLepTrailingInd_SL_L;
            
                tightLepLeadPt_SLU_L = *tightLepLeadPt_SL_L;
                tightLepTrailingPt_SLU_L = *tightLepTrailingPt_SL_L;
                tightLepLeadEta_SLU_L = *tightLepLeadEta_SL_L;
                tightLepTrailingEta_SLU_L = *tightLepTrailingEta_SL_L;
                tightLepLeadPhi_SLU_L = *tightLepLeadPhi_SL_L;
                tightLepTrailingPhi_SLU_L = *tightLepTrailingPhi_SL_L;
                tightLepLeadMass_SLU_L = *tightLepLeadMass_SL_L;
                tightLepTrailingMass_SLU_L = *tightLepTrailingMass_SL_L;
                

                //042024SFAndSuchAdditions
                //PU JetID
                for (UInt_t nJetItr=0; nJetItr<*eventNAK4Jets_SL_L;nJetItr++){
                    Jet_puId_SLU_L.push_back(Jet_puId_SL_L[nJetItr]);
                }
                //additional 042024Branches starting with this script
                //PUID SF check
                for (UInt_t nJetItr=0; nJetItr<*eventNAK4Jets_SL_L;nJetItr++){
                    Jet_LowPtPassesPUID_SLU_L.push_back(Jet_LowPtPassesPUID_SL_L[nJetItr]);
                }

                //more 042024Branches starting with selection
                selectedLeadVBFJet_PUIDSFEligible_SLU_L = *selectedLeadVBFJet_PUIDSFEligible_SL_L;
                selectedTrailingVBFJet_PUIDSFEligible_SLU_L = *selectedTrailingVBFJet_PUIDSFEligible_SL_L;

                //05052024 Additions for PN regress mass scaling and resolution corrections
                luminosityBlock_SLU_L = *luminosityBlock_SL_L;


                passingEvSemiLepUniqueTree->Fill();

                Jet_eta_SLU_L.clear();
                Jet_pt_SLU_L.clear();
                Jet_phi_SLU_L.clear();
                Jet_mass_SLU_L.clear();
                Jet_jetId_SLU_L.clear();
                Jet_btagDeepFlavB_SLU_L.clear();

                Jet_puId_SLU_L.clear();

                Jet_LowPtPassesPUID_SLU_L.clear();
                


            }

        }
    }
    if (debug) std::cout << "Filling complete \n";

    clock_t endt = clock();
    double time_spent = (double)(endt - startt) / CLOCKS_PER_SEC;


    std::cout << "Finished file loop. time: " << time_spent << " nEv total: " << allCtr << " nEv unique: " << uniqueCtr << "\n";
    

    outFile->cd();
    passingEvSemiLepUniqueTree->Write("",TObject::kOverwrite);

    outFile->Close();
}
        