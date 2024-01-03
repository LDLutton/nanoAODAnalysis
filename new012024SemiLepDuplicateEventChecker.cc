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


void new012024SemiLepDuplicateEventChecker(){
    // Open the file. Note that the name of your file outside this class
    // will probably NOT be experiment.root.
    std::cout << "start Analysis\n";
    clock_t startt = clock();
    //Analyzer will run over all files put into fileAr

    std::vector<std::string> fileAr;


    std::string saveName;
    bool isBackground;

    const uint nDataSets = 44;

    std::string datasetTypeStrAr[nDataSets] =  {"BTagCSV16",
    "BTagCSV17",
    "BTagMu16",
    "BTagMu17",
    "BTagMu",
    "Charmonium16",
    "Charmonium17",
    "Charmonium",
    "DisplacedJet16",
    "DisplacedJet17",
    "DisplacedJet",
    "DoubleEG16",
    "DoubleEG17",
    "DoubleMuon16",
    "DoubleMuon17",
    "DoubleMuon",
    "DoubleMuonLowMass16",
    "DoubleMuonLowMass17",
    "DoubleMuonLowMass",
    "EGamma",
    "HTMHT16",
    "HTMHT17",
    "JetHT16",
    "JetHT17",
    "JetHT",
    "MET16",
    "MET17",
    "MET",
    "MuOnia16",
    "MuOnia17",
    "MuOnia",
    "MuonEG16",
    "MuonEG17",
    "MuonEG",
    "SingleElectron16",
    "SingleElectron17",
    "SingleMuon16",
    "SingleMuon17",
    "SingleMuon",
    "SinglePhoton16",
    "SinglePhoton17",
    "Tau16",
    "Tau17",
    "Tau"};
    std::string uncUpDownAr[3] = {"","_UncUp","_UncDown"};
    //Loop over 27 JEC uncertainties
    for (uint i = 0; i < 27; i++){
        //Loop over 5 Muon Rochester uncertainties
        for (uint j = 0; j < 6; j++){
            //Skip instances where both i and j are nonzero
            if (i != 0 && j != 0) continue;
            //Loop over "", "UncUp", "UncDown"
            for (uint uncInd = 0; uncInd <3; uncInd++){
                //skip instances where i and j are both zero and uncInd is not zero
                if (i == 0 && j == 0 && uncInd != 0) continue;




                std::string datasetStrAr[nDataSets];
                for (uint k = 0; k < nDataSets; i++){
                    datasetStrAr[k] = "new122023BDTAnalysis"+datasetTypeStrAr[k]+"Data_"+std::to_string(i)+"_"+std::to_string(j)+uncUpDownAr[uncInd]+".root";
                }
                    

                ////////////////////////////////GETTING DATASET////////////////////////////////
                ////////////////////////////////GETTING DATASET////////////////////////////////
                ////////////////////////////////GETTING DATASET////////////////////////////////
                ////////////////////////////////GETTING DATASET////////////////////////////////

                std::string strAdd;
                strAdd ="/scratch365/dlutton/BDTWithJecRochData/";
                for (UInt_t i = 0; i < nDataSets; i++){
                    fileAr.push_back(strAdd+datasetStrAr[i]);
                }
                


                UInt_t datasetType = 0;

            

                std::cout << "Doing duplicate checker\n";
                //Setting up outfile with variables for BDT

                std::string outFileStr;
                outFileStr = "new122024BDTAnalysisUniqueData_"+std::to_string(i)+"_"+std::to_string(j)+uncUpDownAr[uncInd]+".root";
                
                std::cout << "OutFile: " << outFileStr << "\n";
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
                UInt_t event_SLU_L;
                UInt_t datasetType_SLU_L;

                UInt_t yearType_SLU_L;

                UInt_t runAlphNum_SLU_L;
                Bool_t APV_SLU_L;
                Int_t JECCorInd_SLU_L;
                Int_t RochInd_SLU_L;

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
                std::vector<Float_t> Jet_ptCorrectedDown_SLU_L;
                std::vector<Float_t> Jet_ptCorrectedUp_SLU_L;

                UInt_t eventNAK4JetsPassingCuts_SLU_L;

                UInt_t eventNLooseElectrons_SLU_L;
                UInt_t eventNTightElectrons_SLU_L;
                UInt_t eventNLooseMuons_SLU_L;
                UInt_t eventNTightMuons_SLU_L;

                Float_t selectedHiggsFJ_pt_SLU_L;
                Float_t selectedHiggsFJ_eta_SLU_L;
                Float_t selectedHiggsFJ_ParticleNet_HbbvsQCD_SLU_L;
                Float_t selectedZFJ_pt_SLU_L;
                Float_t selectedZFJ_eta_SLU_L;
                Float_t selectedZFJ_ParticleNet_ZvsQCD_SLU_L;

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
                

                TTree *passingEvSemiLepUniqueTree = new TTree("passingEvSemiLepUniqueTree", "passingEvSemiLepUniqueTree");

                passingEvSemiLepUniqueTree->Branch("run_SLU_L",&run_SLU_L,"run_SLU_L/i");
                passingEvSemiLepUniqueTree->Branch("event_SLU_L",&event_SLU_L,"event_SLU_L/i");

                passingEvSemiLepUniqueTree->Branch("datasetType_SLU_L",&datasetType_SLU_L,"datasetType_SLU_L/i");

                passingEvSemiLepUniqueTree->Branch("yearType_SLU_L",&yearType_SLU_L,"yearType_SLU_L/i");

                passingEvSemiLepUniqueTree->Branch("runAlphNum_SLU_L",&runAlphNum_SLU_L,"runAlphNum_SLU_L/i");
                passingEvSemiLepUniqueTree->Branch("APV_SLU_L",&APV_SLU_L,"APV_SLU_L/O");
                passingEvSemiLepUniqueTree->Branch("JECCorInd_SLU_L",&JECCorInd_SLU_L,"JECCorInd_SLU_L/I");
                passingEvSemiLepUniqueTree->Branch("RochInd_SLU_L",&RochInd_SLU_L,"RochInd_SLU_L/I");

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
                passingEvSemiLepUniqueTree->Branch("Jet_ptCorrectedDown_SLU_L",&Jet_ptCorrectedDown_SLU_L);
                passingEvSemiLepUniqueTree->Branch("Jet_ptCorrectedUp_SLU_L",&Jet_ptCorrectedUp_SLU_L);
                

                passingEvSemiLepUniqueTree->Branch("eventNAK4JetsPassingCuts_SLU_L",&eventNAK4JetsPassingCuts_SLU_L,"eventNAK4JetsPassingCuts_SLU_L/i");

                passingEvSemiLepUniqueTree->Branch("eventNLooseElectrons_SLU_L",&eventNLooseElectrons_SLU_L,"eventNLooseElectrons_SLU_L/i");
                passingEvSemiLepUniqueTree->Branch("eventNTightElectrons_SLU_L",&eventNTightElectrons_SLU_L,"eventNTightElectrons_SLU_L/i");

                passingEvSemiLepUniqueTree->Branch("eventNLooseMuons_SLU_L",&eventNLooseMuons_SLU_L,"eventNLooseMuons_SLU_L/i");
                passingEvSemiLepUniqueTree->Branch("eventNTightMuons_SLU_L",&eventNTightMuons_SLU_L,"eventNTightMuons_SLU_L/i");

                passingEvSemiLepUniqueTree->Branch("selectedHiggsFJ_pt_SLU_L",&selectedHiggsFJ_pt_SLU_L,"selectedHiggsFJ_pt_SLU_L/F");
                passingEvSemiLepUniqueTree->Branch("selectedHiggsFJ_eta_SLU_L",&selectedHiggsFJ_eta_SLU_L,"selectedHiggsFJ_eta_SLU_L/F");
                passingEvSemiLepUniqueTree->Branch("selectedHiggsFJ_ParticleNet_HbbvsQCD_SLU_L",&selectedHiggsFJ_ParticleNet_HbbvsQCD_SLU_L,"selectedHiggsFJ_ParticleNet_HbbvsQCD_SLU_L/F");
                passingEvSemiLepUniqueTree->Branch("selectedZFJ_pt_SLU_L",&selectedZFJ_pt_SLU_L,"selectedZFJ_pt_SLU_L/F");
                passingEvSemiLepUniqueTree->Branch("selectedZFJ_eta_SLU_L",&selectedZFJ_eta_SLU_L,"selectedZFJ_eta_SLU_L/F");
                passingEvSemiLepUniqueTree->Branch("selectedZFJ_ParticleNet_ZvsQCD_SLU_L",&selectedZFJ_ParticleNet_ZvsQCD_SLU_L,"selectedZFJ_ParticleNet_ZvsQCD_SLU_L/F");

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
                    TTreeReaderValue<UInt_t> event_SL_L(myEventsReader,  "event_SL_L");

                    TTreeReaderValue<UInt_t> datasetType_SL_L(myEventsReader,  "datasetType_SL_L");

                    TTreeReaderValue<UInt_t> yearType_SL_L(myEventsReader,  "yearType_SL_L");

                    TTreeReaderValue<UInt_t> runAlphNum_SL_L(myEventsReader, "runAlphNum_SL_L");
                    TTreeReaderValue<Bool_t> APV_SL_L(myEventsReader, "APV_SL_L");
                    TTreeReaderValue<Int_t> JECCorInd_SL_L(myEventsReader, "JECCorInd_SL_L");
                    TTreeReaderValue<Int_t> RochInd_SL_L(myEventsReader, "RochInd_SL_L");


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
                    TTreeReaderArray<Float_t> Jet_ptCorrectedDown_SL_L(myEventsReader, "Jet_ptCorrectedDown_SL_L");
                    TTreeReaderArray<Float_t> Jet_ptCorrectedUp_SL_L(myEventsReader, "Jet_ptCorrectedUp_SL_L");

                    TTreeReaderValue<UInt_t> eventNLooseElectrons_SL_L(myEventsReader, "eventNLooseElectrons_SL_L");
                    TTreeReaderValue<UInt_t> eventNTightElectrons_SL_L(myEventsReader, "eventNTightElectrons_SL_L");
                    TTreeReaderValue<UInt_t> eventNLooseMuons_SL_L(myEventsReader, "eventNLooseMuons_SL_L");
                    TTreeReaderValue<UInt_t> eventNTightMuons_SL_L(myEventsReader, "eventNTightMuons_SL_L");
                    TTreeReaderValue<UInt_t> eventNAK4JetsPassingCuts_SL_L(myEventsReader, "eventNAK4JetsPassingCuts_SL_L");

                    TTreeReaderValue<Float_t> selectedHiggsFJ_pt_SL_L(myEventsReader,  "selectedHiggsFJ_pt_SL_L");
                    TTreeReaderValue<Float_t> selectedHiggsFJ_eta_SL_L(myEventsReader,  "selectedHiggsFJ_eta_SL_L");
                    TTreeReaderValue<Float_t> selectedHiggsFJ_ParticleNet_HbbvsQCD_SL_L(myEventsReader,  "selectedHiggsFJ_ParticleNet_HbbvsQCD_SL_L");
                    TTreeReaderValue<Float_t> selectedZFJ_pt_SL_L(myEventsReader,  "selectedZFJ_pt_SL_L");
                    TTreeReaderValue<Float_t> selectedZFJ_eta_SL_L(myEventsReader,  "selectedZFJ_eta_SL_L");
                    TTreeReaderValue<Float_t> selectedZFJ_ParticleNet_ZvsQCD_SL_L(myEventsReader,  "selectedZFJ_ParticleNet_ZvsQCD_SL_L");

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


                    if (k % 10 == 0){
                        double tmpTime = (double)(clock()-startt)/CLOCKS_PER_SEC;
                        std::cout << "Going into event loop for file" << k << " .\ttime:" << (double)(clock()-startt)/CLOCKS_PER_SEC << "\n";
                    }
                    std::cout << "Current nEv: " << allCtr << "\n";
                    std::cout << "Current unique: " << uniqueCtr << "\n"; 

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
                            JECCorInd_SLU_L = *JECCorInd_SL_L;
                            RochInd_SLU_L = *RochInd_SL_L;

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
                                Jet_ptCorrectedDown_SLU_L.push_back(Jet_ptCorrectedDown_SL_L[nJetItr]);
                                Jet_ptCorrectedUp_SLU_L.push_back(Jet_ptCorrectedUp_SL_L[nJetItr]);
                            }
                            fixedGridRhoFastjetAll_SLU_L = *fixedGridRhoFastjetAll_SL_L;

                            eventNAK4JetsPassingCuts_SLU_L = *eventNAK4JetsPassingCuts_SL_L;

                            eventNLooseElectrons_SLU_L = *eventNLooseElectrons_SL_L;
                            eventNTightElectrons_SLU_L = *eventNTightElectrons_SL_L;

                            eventNLooseMuons_SLU_L = *eventNLooseMuons_SL_L;
                            eventNTightMuons_SLU_L = *eventNTightMuons_SL_L;

                            

                            selectedHiggsFJ_pt_SLU_L = *selectedHiggsFJ_pt_SL_L;
                            selectedZFJ_pt_SLU_L = *selectedZFJ_pt_SL_L;
                            selectedHiggsFJ_eta_SLU_L = *selectedHiggsFJ_eta_SL_L;
                            selectedZFJ_eta_SLU_L = *selectedZFJ_eta_SL_L;
                            selectedZFJ_InvMass_SLU_L = *selectedZFJ_InvMass_SL_L;
                            selectedHiggsFJ_InvMass_SLU_L = *selectedHiggsFJ_InvMass_SL_L;
                            selectedHiggsFJ_ParticleNet_HbbvsQCD_SLU_L = *selectedHiggsFJ_ParticleNet_HbbvsQCD_SL_L;

                            selectedZFJ_InvMassSoftDrop_SLU_L = *selectedZFJ_InvMassSoftDrop_SL_L;
                            selectedHiggsFJ_InvMassSoftDrop_SLU_L = *selectedHiggsFJ_InvMassSoftDrop_SL_L;

                            selectedZFJ_InvMassPNRegress_SLU_L = *selectedZFJ_InvMassPNRegress_SL_L;
                            selectedHiggsFJ_InvMassPNRegress_SLU_L = *selectedHiggsFJ_InvMassPNRegress_SL_L;

                            selectedZFJ_ParticleNet_ZvsQCD_SLU_L = *selectedZFJ_ParticleNet_ZvsQCD_SL_L;

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


                            passingEvSemiLepUniqueTree->Fill();

                            Jet_eta_SLU_L.clear();
                            Jet_pt_SLU_L.clear();
                            Jet_phi_SLU_L.clear();
                            Jet_mass_SLU_L.clear();
                            Jet_jetId_SLU_L.clear();
                            Jet_btagDeepFlavB_SLU_L.clear();
                            


                        }

                    }
                }
                if (debug) std::cout << "Filling complete \n";

                clock_t endt = clock();
                double time_spent = (double)(endt - startt) / CLOCKS_PER_SEC;


                std::cout << "Finished file loop. " << "time: " << time_spent << "\n";
                
                std::cout << "nEv total: " << allCtr << "\n";
                std::cout << "nEv unique: " << uniqueCtr << "\n"; 


                outFile->cd();
                passingEvSemiLepUniqueTree->Write("",TObject::kOverwrite);

                outFile->Close();
            }
        }
    }

}