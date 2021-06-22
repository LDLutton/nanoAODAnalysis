from ROOT import TFile, TChain, gDirectory, TApplication, TMath, Math, TMinuit, TROOT, TSystem, TTree, TVector2
# You probably also want to import TH1D and TCanvas,
# unless you're not making any histograms.
from ROOT import TH1F, TCanvas, TF1, TGraph, TGraphErrors, TLegend, TLine, TPaveText, TStyle
from ROOT import TH2D, TH2F
from math import sqrt,pi
from fileLists import MGEFTAr
from fileLists import MGSMAr
from fileLists import ttHToBBBackgroundAr
import time as time

#withDipoleRecoil = True

MGSM = True
MGEFT = False
ttHToBBBackground = False

#For drawing and saving histograms
#Saves a png and, optionally, a pdf version
#Saves histogram to the currently active root file

def DrawPlot(plot,name,saveName,normalizeOrNot):
    if normalizeOrNot and plot.GetEntries() > 0:
        c1 = TCanvas("c1","c1",3600,2400)

        plot.SetFillColorAlpha(30,0.35)

        plot.Draw("hist")
        c1.SaveAs((name+"{0}.png".format(saveName)))
        plot.Write(name)
        plot.Scale(1.0 / plot.Integral())

        plot.Draw("hist")
        c1.SaveAs((name+"{0}Normalized.png".format(saveName)))
        #c1.SaveAs((name+"{0}.pdf".format(saveName)))
        plot.Write(name+"Normalized")
    else:
        print(name,"has no entries. Adding empty histograms")
        c1 = TCanvas()
        plot.Draw("hist")
        plot.Write(name)
        plot.Write(name+"Normalized")




#For calculating DeltaR for two particles from their respective etas and phis
def calcDeltaR(phi1,eta1,phi2,eta2):
    deta = eta1-eta2
    dphi = abs(phi1-phi2)
    if dphi > pi:
        dphi -= (2*pi)
    return sqrt((deta*deta)+(dphi*dphi))


# Open the file. Note that the name of your file outside this class
# will probably NOT be experiment.root.
print("start")
startt = time.time()
#Analyzer will run over all files put into fileAr
fileAr = []

if MGEFT:
    saveName = "pphzzjjQCD0SMHLOOP0NPE1NPcHWE1QEDE5ResMasAllVer100Ev_0p999cHW100GeVIMJetCut"
    h_LHEWeight      = TH1F("h_LHEWeight","h_LHEWeight",100,0.000262,0.000273)

    for fileName in MGEFTAr:
        fileAr.append("/scratch365/dlutton/NanoAODFiles/pphzzjjQCD0SMHLOOP0NPE1NPcHWE1QEDE5ResMasAllVer100Ev_0p999cHW100GeVIMJetCut/"+fileName)
elif MGSM:
    saveName = "pphzzjjQCD0SMHLOOP0QEDE5NPE0ResMasAllVer100Ev_0p999cHW100GeVIMJetCut"
    h_LHEWeight      = TH1F("h_LHEWeight","h_LHEWeight",100,8.0e-05,8.5e-05)
    for fileName in MGSMAr:
        fileAr.append("/scratch365/dlutton/NanoAODFiles/pphzzjjQCD0SMHLOOP0QEDE5NPE0ResMasAllVer100Ev_0p999cHW100GeVIMJetCut/"+fileName)
elif ttHToBBBackground:
    saveName = "ttHToBBBackground"
    h_LHEWeight      = TH1F("h_LHEWeight","h_LHEWeight",100,8.0e-05,8.5e-05) #Non-functional, just to keep the program from crashing
    crossSection = 0.6*0.584
    for fileName in ttHToBBBackgroundAr:
        fileAr.append(fileName)
    
if not ttHToBBBackground:
    crossSectionAvg = 0
    crossSectionCtr = 0

print("Making Histos/Defining variables.","time:",time.time()-startt)
h_CaloMET_phi    = TH1F("h_CaloMET_phi","h_CaloMET_phi", 100, -3.5, 3.5)
h_CaloMET_pt     = TH1F("h_CaloMET_pt","h_CaloMET_pt", 20, 0, 200)
h_CaloMET_sumEt  = TH1F("h_CaloMET_sumEt","h_CaloMET_sumEt", 500, 0, 4000)

#Leptons with no cuts
#Electrons
h_Electron_eta   = TH1F("h_Electron_eta","h_Electron_eta", 100, -5.0, 5.0)
h_Electron_hoe   = TH1F("h_Electron_hoe","h_Electron_hoe", 200, 0, 5.0)
h_Electron_mass  = TH1F("h_Electron_mass","h_Electron_mass", 200, 0, 0.15)
h_Electron_phi   = TH1F("h_Electron_phi","h_Electron_phi", 100, -3.5, 3.5)
h_Electron_pt    = TH1F("h_Electron_pt","h_Electron_pt", 20, 0, 200)
h_Electron_r9    = TH1F("h_Electron_r9","h_Electron_r9", 200, 0, 4.0)
h_Electron_sieie = TH1F("h_Electron_sieie","h_Electron_sieie", 200, 0, 0.2)

#Muons
h_Muon_eta       = TH1F("Muon_eta","Muon_eta", 100, -5.0, 5.0)
h_Muon_mass      = TH1F("h_Muon_mass","h_Muon_mass", 200, 0, 0.15)
h_Muon_phi       = TH1F("h_Muon_phi","h_Muon_phi", 100, -3.5, 3.5)
h_Muon_pt        = TH1F("h_Muon_pt","h_Muon_pt", 20, 0, 200)

#Leptons with cuts
#Electrons
h_Electron_Cuts_eta   = TH1F("h_Electron_Cuts_eta","h_Electron_Cuts_eta", 100, -5.0, 5.0)
h_Electron_Cuts_hoe   = TH1F("h_Electron_Cuts_hoe","h_Electron_Cuts_hoe", 200, 0, 5.0)
h_Electron_Cuts_mass  = TH1F("h_Electron_Cuts_mass","h_Electron_Cuts_mass", 200, 0, 0.15)
h_Electron_Cuts_phi   = TH1F("h_Electron_Cuts_phi","h_Electron_Cuts_phi", 100, -3.5, 3.5)
h_Electron_Cuts_pt    = TH1F("h_Electron_Cuts_pt","h_Electron_Cuts_pt", 20, 0, 200)
h_Electron_Cuts_r9    = TH1F("h_Electron_Cuts_r9","h_Electron_Cuts_r9", 200, 0, 4.0)
h_Electron_Cuts_sieie = TH1F("h_Electron_Cuts_sieie","h_Electron_Cuts_sieie", 200, 0, 0.2)

#Muons
h_Muon_Cuts_eta       = TH1F("Muon_Cuts_eta","Muon_Cuts_eta", 100, -5.0, 5.0)
h_Muon_Cuts_mass      = TH1F("h_Muon_Cuts_mass","h_Muon_Cuts_mass", 200, 0, 0.15)
h_Muon_Cuts_phi       = TH1F("h_Muon_Cuts_phi","h_Muon_Cuts_phi", 100, -3.5, 3.5)
h_Muon_Cuts_pt        = TH1F("h_Muon_Cuts_pt","h_Muon_Cuts_pt", 20, 0, 200)

#Jets
h_Jet_eta        = TH1F("h_Jet_eta","h_Jet_eta", 100, -5.0, 5.0)
h_Jet_mass       = TH1F("h_Jet_mass","h_Jet_mass", 200, 0, 200)
h_Jet_phi        = TH1F("h_Jet_phi","h_Jet_phi", 100, -3.5, 3.5)
h_Jet_pt         = TH1F("h_Jet_pt","h_Jet_pt", 25, 0, 500)
h_nJet          = TH1F("h_nJet","h_nJet", 19, 0, 19)

#Calculated hists

#Jets from gen particle matching
h_InitialJet_EtaSep     = TH1F("h_InitialJet_EtaSep","h_InitialJet_EtaSep", 100, 0, 10)
h_InitialJet_Eta     = TH1F("h_InitialJet_Eta","h_InitialJet_Eta", 100, -5.0, 5.0)
h_InitialJet_pt    = TH1F("h_InitialJet_pt","h_InitialJet_pt", 25, 0, 500)
#Jets with cuts using the Leading jet
h_InitialJetAlt_Eta     = TH1F("h_InitialJetAlt_Eta","h_InitialJetAlt_Eta", 100, -5.0, 5.0)
h_InitialJetAlt_EtaSep     = TH1F("h_InitialJetAlt_EtaSep","h_InitialJetAlt_EtaSep", 100, 0, 10)
h_InitialJetAlt_pt    = TH1F("h_InitialJetAlt_pt","h_InitialJetAlt_pt", 25, 0, 500)
#These for selecting jet pair with inv mass
h_InitialJetAltIM_Eta     = TH1F("h_InitialJetAltIM_Eta","h_InitialJetAltIM_Eta", 100, -5.0, 5.0)
h_InitialJetAltIM_EtaSep     = TH1F("h_InitialJetAltIM_EtaSep","h_InitialJetAltIM_EtaSep", 100, 0, 10)
h_InitialJetAltIM_pt    = TH1F("h_InitialJetAltIM_pt","h_InitialJetAltIM_pt", 25, 0, 500)
#These for selecting jet pair with top jet pt (second jet pt as tiebreaker)
h_InitialJetAltLJ_Eta     = TH1F("h_InitialJetAltLJ_Eta","h_InitialJetAltLJ_Eta", 100, -5.0, 5.0)
h_InitialJetAltLJ_EtaSep     = TH1F("h_InitialJetAltLJ_EtaSep","h_InitialJetAltLJ_EtaSep", 100, 0, 10)
h_InitialJetAltLJ_pt    = TH1F("h_InitialJetAltLJ_pt","h_InitialJetAltLJ_pt", 25, 0, 500)

#Defining Lepton cuts
firstZLeadingCut = 20
firstZTrailingCut = 10
ZMass = 91.1876
leptonInvMassCutLow = 60
leptonInvMassCutHigh = 120
leptonInvMassCutTwo = 12
fourLeptonInvMassCut = 100
leptonZ2Cut = 12
elecCandEtaCut =  2.5
elecCandPTCut = 7
muonCandEtaCut =  2.4
muonCandPTCut = 5

#Defining jet matching cuts
jetPTCut = 30
fatJetPTCut = 200
jetEtaDifCut = 2.0
jetInvMassCut = 400
#Using deeptagging
#Rates aren't actually for Z, just based on the W (MD) values here:
#https://indico.cern.ch/event/877167/contributions/3744193/attachments/1989744/3379280/DeepAK8_Top_W_SFs_V2.pdf

cutOnZTag5MTR = 0.245
cutOnZTag2p5MTR = 0.479
cutOnZTag1MTR = 0.704
cutOnZTag0p5MTR = 0.806

cutOnZTagAr = [cutOnZTag0p5MTR,cutOnZTag1MTR,cutOnZTag2p5MTR,cutOnZTag5MTR]

cutOnZTagStrAr = ["0p5","1","2p5","5"]
#Fat Jets with no cut and no tagging
h_FatJet_pt         = TH1F("h_FatJet_pt","h_FatJet_pt", 250, 0, 500)
h_nFatJet           = TH1F("h_nFatJet","h_nFatJet", 7, 0, 7)
h_FatJet_eta        = TH1F("h_FatJet_eta","h_FatJet_eta", 100, -5.0, 5.0)
h_FatJet_mass       = TH1F("h_FatJet_mass","h_FatJet_mass", 200, 0, 200)
h_FatJet_phi        = TH1F("h_FatJet_phi","h_FatJet_phi", 100, -3.5, 3.5)


#Fat Jets with tagging but no cut
h_FatJet_etaZAr = []
h_FatJet_massZAr = []
h_FatJet_ptZAr = []
h_FatJet_phiZAr = []

#Fat Jets with cut but no tagging
h_InitialFatJetAltLJ_Eta     = TH1F("h_InitialFatJetAltLJ_Eta","h_InitialFatJetAltLJ_Eta", 100, -5.0, 5.0)
h_InitialFatJetAltLJ_EtaSep     = TH1F("h_InitialFatJetAltLJ_EtaSep","h_InitialFatJetAltLJ_EtaSep", 100, 0, 10)
h_InitialFatJetAltLJ_pt    = TH1F("h_InitialFatJetAltLJ_pt","h_InitialFatJetAltLJ_pt", 25, 0, 500)


#Fat jets with cut and tagging
h_InitialFatJetAltLJ_EtaZAr = []
h_InitialFatJetAltLJ_EtaSepZAr = []
h_InitialFatJetAltLJ_ptZAr = []

#Histograms for different levels of cut on the Z tagging
for cutOnZTagStr in cutOnZTagStrAr:
    h_InitialFatJetAltLJ_EtaZAr.append(TH1F("h_InitialFatJetAltLJ_Eta_ZTag{0}MTR".format(cutOnZTagStr),"h_InitialFatJetAltLJ_Eta_ZTag{0}MTR".format(cutOnZTagStr), 100, -5.0, 5.0))
    h_InitialFatJetAltLJ_EtaSepZAr.append(TH1F("h_InitialFatJetAltLJ_EtaSep_ZTag{0}MTR".format(cutOnZTagStr),"h_InitialFatJetAltLJ_EtaSep_ZTag{0}MTR".format(cutOnZTagStr), 100, 0, 10))
    h_InitialFatJetAltLJ_ptZAr.append(TH1F("h_InitialFatJetAltLJ_pt_ZTag{0}MTR".format(cutOnZTagStr),"h_InitialFatJetAltLJ_pt_ZTag{0}MTR".format(cutOnZTagStr), 25, 0, 500))
    h_FatJet_etaZAr.append(TH1F("h_FatJet_Eta_ZTag{0}MTR".format(cutOnZTagStr),"h_FatJet_Eta_ZTag{0}MTR".format(cutOnZTagStr), 100, -5.0, 5.0))
    h_FatJet_massZAr.append(TH1F("h_FatJet_Mass_ZTag{0}MTR".format(cutOnZTagStr),"h_FatJet_Mass_ZTag{0}MTR".format(cutOnZTagStr), 200, 0, 200))
    h_FatJet_ptZAr.append(TH1F("h_FatJet_pt_ZTag{0}MTR".format(cutOnZTagStr),"h_FatJet_pt_ZTag{0}MTR".format(cutOnZTagStr), 25, 0, 500))
    h_FatJet_phiZAr.append(TH1F("h_FatJet_phi_ZTag{0}MTR".format(cutOnZTagStr),"h_FatJet_phi_ZTag{0}MTR".format(cutOnZTagStr), 100, -3.5, 3.5))

#Lepton
#histograms for full ZZ cuts
LepFullCut_Z1Leadpt         = TH1F("LepFullCut_Z1Leadpt","LepFullCut_Z1Leadpt", 250, 0, 500)
LepFullCut_Z1Trailingpt         = TH1F("LepFullCut_Z1Trailingpt","LepFullCut_Z1Trailingpt", 250, 0, 500)
LepFullCut_Z2Leadpt         = TH1F("LepFullCut_Z2Leadpt","LepFullCut_Z2Leadpt", 250, 0, 500)
LepFullCut_Z2Trailingpt         = TH1F("LepFullCut_Z2Trailingpt","LepFullCut_Z2Trailingpt", 250, 0, 500)
LepFullCut_Z1Leadeta        = TH1F("LepFullCut_Z1Leadeta","LepFullCut_Z1Leadeta", 100, -5.0, 5.0)
LepFullCut_Z1Trailingeta        = TH1F("LepFullCut_Z1Trailingeta","LepFullCut_Z1Trailingeta", 100, -5.0, 5.0)
LepFullCut_Z2Leadeta        = TH1F("LepFullCut_Z2Leadeta","LepFullCut_Z2Leadeta", 100, -5.0, 5.0)
LepFullCut_Z2Trailingeta        = TH1F("LepFullCut_Z2Trailingeta","LepFullCut_Z2Trailingeta", 100, -5.0, 5.0)
LepFullCut_Z1Leadmass       = TH1F("LepFullCut_Z1Leadmass","LepFullCut_Z1Leadmass", 200, 0, 200)
LepFullCut_Z1Trailingmass       = TH1F("LepFullCut_Z1Trailingmass","LepFullCut_Z1Trailingmass", 200, 0, 200)
LepFullCut_Z2Leadmass       = TH1F("LepFullCut_Z2Leadmass","LepFullCut_Z2Leadmass", 200, 0, 200)
LepFullCut_Z2Trailingmass       = TH1F("LepFullCut_Z2Trailingmass","LepFullCut_Z2Trailingmass", 200, 0, 200)
LepFullCut_Z1Leadphi        = TH1F("LepFullCut_Z1Leadphi","LepFullCut_Z1Leadphi", 100, -3.5, 3.5)
LepFullCut_Z1Trailingphi        = TH1F("LepFullCut_Z1Trailingphi","LepFullCut_Z1Trailingphi", 100, -3.5, 3.5)
LepFullCut_Z2Leadphi        = TH1F("LepFullCut_Z2Leadphi","LepFullCut_Z2Leadphi", 100, -3.5, 3.5)
LepFullCut_Z2Trailingphi        = TH1F("LepFullCut_Z2Trailingphi","LepFullCut_Z2Trailingphi", 100, -3.5, 3.5)
LepFullCut_Z1EtaSep        = TH1F("LepFullCut_Z1EtaSep","LepFullCut_Z1EtaSep", 100, 0, 10)
LepFullCut_Z2EtaSep        = TH1F("LepFullCut_Z2EtaSep","LepFullCut_Z2EtaSep", 100, 0, 10)
LepFullCut_Z1InvMass        = TH1F("LepFullCut_Z1InvMass","LepFullCut_Z1InvMass", 100, 60, 120)
LepFullCut_Z2InvMass        = TH1F("LepFullCut_Z2InvMass","LepFullCut_Z2InvMass", 100, 60, 120)




#Initializing counter variables
evCount = 0
noMatchCount = 0
noOutCount = 0
ifOneCount = 0
ifTwoCount = 0
ifThreeCount = 0
ifFourCount = 0

ifOneFJCount = 0
ifTwoFJCount = 0
ifThreeFJCount = 0
ifFourFJCount = 0

#Counter for lepton cuts

ifEnoughElecCandCount = 0
ifEnoughMuonCandCount = 0
ifZ1ElecPairCandCount = 0
ifZ1MuonPairCandCount = 0
ifZ2ElecPairCandCount = 0
ifZ2MuonPairCandCount = 0
passesIsoCutsCount = 0
passesSIPCutCount = 0
allCutPassCount = 0


print("Going into file loop.","time:",time.time()-startt)
for k,fileName in enumerate(fileAr):
    #if evCount > 450:
    #    break
    #Open the file, get the Events tree
    tmpfile = TFile.Open(fileName)
    mytree = tmpfile.Events
    runTree = tmpfile.Runs
    #Getting the cross section
    #For background it's precalculated
    if not ttHToBBBackground:
        for i,runEv in enumerate(runTree):
            if i > 0:
                print("uhoh it has two",i,k,fileName)
            crossSection = runEv.genEventSumw / runEv.genEventCount
        h_LHEWeight.Fill(crossSection)
        crossSectionAvg += crossSection
        crossSectionCtr += 1
    if k % 10 == 0:
        print("Going into event loop for file {0}.".format(k),"time:",time.time()-startt)

    #EvLoop
    for ev in mytree:
        #if evCount > 450:
        #    break
        if evCount % 1000 == 0:
            print("Event: "+str(evCount))
        #print(ev.CaloMET_sumEt)
        #Filling up MET Hists
        h_CaloMET_phi.Fill(ev.CaloMET_phi)
        h_CaloMET_pt.Fill(ev.CaloMET_pt)
        h_CaloMET_sumEt.Fill(ev.CaloMET_sumEt)

        #Filling up nJet hists
        h_nJet.Fill(ev.nJet)
        h_nFatJet.Fill(ev.nFatJet)
        #Initializing temporary, per event, variables for jet matching
        #Gen matching:
        #These for saving the index of the jet pair in jet matching
        jOneInd = -1
        jTwoInd = -1
        #These for saving the index of the fat jet pair in jet matching
        fJOneInd = -1
        fJTwoInd = -1
        #These for saving the two minimum deltaR between jets and the outgoing quarks from gen particles
        deltaRMinOne = 10000
        deltaRMinTwo = 10000

        #Matching with cuts based on max summed PT of the jets:
        #These for saving the maximum PT 
        ptOneInd = -1
        ptTwoInd = -1
        diJetMaxPT = 0


        #Matching with cuts based on max PT of jet in the jet pair, second jet PT as tiebreaker
        LJOneInd = -1
        LJTwoInd = -1
        leadJetMaxPT = 0
        secondJetMaxPT = 0

        #Matching Fat Jets with cuts based on max PT of jet in the jet pair, second jet PT as tiebreaker
        LFJOneInd = -1
        LFJTwoInd = -1
        leadFatJetMaxPT = 0
        secondFatJetMaxPT = 0

        #Matching Fat Jets with cuts and tagging based on max PT of jet in the jet pair, second jet PT as tiebreaker
        LFJTOneIndAr = []
        LFJTTwoIndAr = [] 
        leadFatJetTMaxPTAr = []
        secondFatJetTMaxPTAr = []
        for i in range(len(cutOnZTagAr)):
            LFJTOneIndAr.append(-1)
            LFJTTwoIndAr.append(-1)
            leadFatJetTMaxPTAr.append(0)
            secondFatJetTMaxPTAr.append(0)


        #Matching with cuts based on max InvMass of jet pair:
        invMassOneInd = -1
        invMassTwoInd = -1
        diJetMaxInvMass = 0

        #IndicesForLeptonPairs
        lepPairOneLeadInd = 0
        lepPairOneTrailingInd = 0
        #lepPairTwoLeadInd = 0
        #lepPairTwoTrailingInd = 0

        #For counters to not overcount
        ifOneBool = False
        ifTwoBool = False
        ifThreeBool = False
        ifFourBool = False
        ifOneFJBool = False
        ifTwoFJBool = False
        ifThreeFJBool = False
        ifFourFJBool = False

        ifEnoughElecCandBool = False
        ifEnoughMuonCandBool = False
        ifZ1ElecPairCandBool = False
        ifZ1MuonPairCandBool = False
        ifZ2ElecPairCandBool = False
        ifZ2MuonPairCandBool = False
        passesIsoCutsBool = False
        passesSIPCutBool = False
        allCutPassBool = False

        #Array for the Candidates for the first Z
        ZOneCandAr = []
        #number of electrons and muons and the sum
        tmpnElectron = ev.nElectron
        tmpnMuon = ev.nMuon
        leptonSum = tmpnElectron+tmpnMuon
        #Variables for tracking the lepton energy that is the closest to the Z mass
        difFromZMassOne = 1000
        difFromZMassTwo = 1000
        #Vectors for Leptons
        leadLepPairOneVec = Math.PtEtaPhiMVector(0,0,0,0)
        trailingLepPairOneVec = Math.PtEtaPhiMVector(0,0,0,0)
        #leadLepPairTwoVec = Math.PtEtaPhiMVector(0,0,0,0)
        #trailingLepPairTwoVec = Math.PtEtaPhiMVector(0,0,0,0)
        leadLepPairVec = Math.PtEtaPhiMVector(0,0,0,0)
        trailingLepPairVec = Math.PtEtaPhiMVector(0,0,0,0)
        elecPassesCutsAr = []
        elecPassesZ2CutsAr = []
        leadLepPairCharge = 0
        trailingLepPairCharge = 0
        leadZ2LepPairInd = -1
        leadZ2Pt = 0
        trailingZ2Pt = 0

        #Counting Elec Candidates Loop
        nElecCandidates = 0
        elecVetoAr = []
        #Replacing bools here with a counter
        #elecHasNeg = False
        #elecHasPos = False
        nElecCandidatesNeg = 0
        nElecCandidatesPos = 0
        #Looping over electrons
        for i in range(tmpnElectron):
            #Checking for electron candidates with the initial eta and pt cuts. Keeping track of whether there is a negative and/or a positive electron present
            if abs(ev.Electron_eta[i]) < elecCandEtaCut and ev.Electron_pt[i] > elecCandPTCut:

                nElecCandidates += 1
                if ev.Electron_charge[i] == -1:
                    #elecHasNeg = True
                    nElecCandidatesNeg += 1
                else:
                    #elecHasPos = True
                    nElecCandidatesPos += 1
            else:
                #Keeping track of electrons that didn't pass
                elecVetoAr.append(i)
        nElecCandPairs = 0
        if nElecCandidatesNeg <= nElecCandidatesPos:
            nElecCandPairs = nElecCandidatesNeg
        else:
            nElecCandPairs = nElecCandidatesPos
        
        #Counting Muon Candidates Loop
        nMuonCandidates = 0
        muonVetoAr = []
        #muonHasNeg = False
        #muonHasPos = False
        nMuonCandidatesNeg = 0
        nMuonCandidatesPos = 0
        #Loop over muons
        for i in range(tmpnMuon):
            #Checking for muon candidates with the initial eta and pt cuts. Keeping track of whether there is a negative and/or a positive muon present
            if abs(ev.Muon_eta[i]) < muonCandEtaCut and ev.Muon_pt[i] > muonCandPTCut:
                nMuonCandidates += 1
                if ev.Muon_charge[i] == -1:
                    #muonHasNeg = True
                    nMuonCandidatesNeg += 1
                else:
                    #muonHasPos = True
                    nMuonCandidatesPos += 1
            else:
                #Keeping track of muons that didn't pass
                muonVetoAr.append(i)
        nMuonCandPairs = 0
        if nMuonCandidatesNeg <= nMuonCandidatesPos:
            nMuonCandPairs = nMuonCandidatesNeg
        else:
            nMuonCandPairs = nMuonCandidatesPos
        
        enoughElecCands = False
        enoughLepCands = False
        #Checking if there is an electron positron pair
        if nElecCandPairs >= 1:
            enoughElecCands = True
            #Checking if electrons alone satisfy the lep candidates
            #if nElecCandidates >=4 and nElecCandPairs >= 2:
            if nElecCandPairs >= 2:
                enoughLepCands = True
        if nMuonCandPairs >= 1:
            enoughMuonCands = True
            #Checking if muons alone satisfy the lep candidates
            #if nMuonCandidates >=4 and nMuonCandPairs >= 2:
            if nMuonCandPairs >= 2:
                enoughLepCands = True
            #Else, checking if the sum of the two is enough and whether or not they both have a pair
            elif not enoughLepCands and enoughElecCands:
                enoughLepCands = True


        #leptonCandSum = nElecCandidates + nMuonCandidates
        #Electrons loop
        for i in range(tmpnElectron):
            
            tmpPtOne = ev.Electron_pt[i]
            tmpEtaOne = ev.Electron_eta[i]
            tmpMassOne = ev.Electron_mass[i]
            tmpPhiOne = ev.Electron_phi[i]
            #No Cuts
            h_Electron_eta.Fill(tmpEtaOne)
            h_Electron_hoe.Fill(ev.Electron_hoe[i])
            h_Electron_mass.Fill(tmpMassOne)
            h_Electron_phi.Fill(tmpPhiOne)
            h_Electron_pt.Fill(tmpPtOne)
            h_Electron_r9.Fill(ev.Electron_r9[i])
            h_Electron_sieie.Fill(ev.Electron_sieie[i])
            #Z Cuts
            
            #If enough lepton candidates and enough electron candidates, begin the loop
            #if leptonCandSum >= 4:
            if enoughLepCands and enoughElecCands:
                if not ifEnoughElecCandBool:
                    ifEnoughElecCandCount += 1
                    ifEnoughElecCandBool = True
                    
                if tmpPtOne > firstZTrailingCut:
                    #Looping over other electrons
                    for j in range(i+1,tmpnElectron):
                        #Check that the electrons have the opposite charge
                        tmpElecCharge = ev.Electron_charge[i]
                        tmpElecChargeTwo = ev.Electron_charge[j]
                        if tmpElecCharge == - tmpElecChargeTwo:
                            #Get variables from second electron
                            tmpPtTwo = ev.Electron_pt[j]

                            tmpEtaTwo = ev.Electron_eta[j]
                            tmpMassTwo = ev.Electron_mass[j]
                            tmpPhiTwo = ev.Electron_phi[j]

                            if tmpPtOne > tmpPtTwo:
                                tmpMaxPtLead = tmpPtOne
                                tmpMaxPtSecond = tmpPtTwo
                                tmpLeadInd = i
                                tmpSecondInd = j
                                tmpLeadCharge = tmpElecCharge
                                tmpTrailingCharge = tmpElecChargeTwo
                            else:
                                tmpMaxPtLead = tmpPtTwo
                                tmpMaxPtSecond = tmpPtOne
                                tmpLeadInd = j
                                tmpSecondInd = i
                                tmpLeadCharge = tmpElecChargeTwo
                                tmpTrailingCharge = tmpElecCharge
                            if tmpLeadInd == i:
                                tmpLeadVec = Math.PtEtaPhiMVector(tmpPtOne, tmpEtaOne, tmpPhiOne, tmpMassOne)
                                tmpTrailingVec = Math.PtEtaPhiMVector(tmpPtTwo, tmpEtaTwo, tmpPhiTwo, tmpMassTwo)
                            else:
                                tmpLeadVec = Math.PtEtaPhiMVector(tmpPtTwo, tmpEtaTwo, tmpPhiTwo, tmpMassTwo)
                                tmpTrailingVec = Math.PtEtaPhiMVector(tmpPtOne, tmpEtaOne, tmpPhiOne, tmpMassOne)
                            tmpDiElectronVec = tmpVecOne+tmpVecTwo
                            tmpDiElectronInvMass = tmpDiElectronVec.M()
                            if tmpDiElectronInvMass > leptonZ2Cut:
                                elecPassesZ2CutsAr.append([[tmpLeadInd,tmpSecondInd],[tmpLeadVec,tmpTrailingVec],[tmpLeadCharge,tmpTrailingCharge]])
                                
                            #Check that the pt of the second electron passes the lower pt cut
                            if tmpPtTwo > firstZTrailingCut:
                                #Sort the electrons into leading and trailing based on pt
                                #Actually get these earlier
                                """
                                if tmpPtOne > tmpPtTwo:
                                    tmpMaxPtLead = tmpPtOne
                                    tmpMaxPtSecond = tmpPtTwo
                                    tmpLeadInd = i
                                    tmpSecondInd = j
                                else:
                                    tmpMaxPtLead = tmpPtTwo
                                    tmpMaxPtSecond = tmpPtOne
                                    tmpLeadInd = j
                                    tmpSecondInd = i
                                """
                                #Check that the lead electron passes the higher pt cut
                                if tmpMaxPtLead > firstZLeadingCut:
                                    #If so, get variables from the second electron (actually now it works better to get them earlier)
                                    #Also get the vectors and inv mass earlier
                                    """
                                    #tmpEtaTwo = ev.Electron_eta[j]
                                    #tmpMassTwo = ev.Electron_mass[j]
                                    #tmpPhiTwo = ev.Electron_phi[j]
                                    #Get invMass from electron pair
                                    if tmpLeadInd = i:
                                        tmpLeadVec = Math.PtEtaPhiMVector(tmpPtOne, tmpEtaOne, tmpPhiOne, tmpMassOne)
                                        tmpTrailingVec = Math.PtEtaPhiMVector(tmpPtTwo, tmpEtaTwo, tmpPhiTwo, tmpMassTwo)
                                    else:
                                        tmpLeadVec = Math.PtEtaPhiMVector(tmpPtTwo, tmpEtaTwo, tmpPhiTwo, tmpMassTwo)
                                        tmpTrailingVec = Math.PtEtaPhiMVector(tmpPtOne, tmpEtaOne, tmpPhiOne, tmpMassOne)
                                    tmpDiElectronVec = tmpVecOne+tmpVecTwo
                                    tmpDiElectronInvMass = tmpDiElectronVec.M()
                                    """
                                    
                                    #Check that invmass passes the Cut
                                    if tmpDiElectronInvMass > leptonInvMassCutLow:
                                        if not ifZ1ElecPairCandBool:
                                            ifZ1ElecPairCandCount += 1
                                            ifZ1ElecPairCandBool = True
                                        elecPassesCutsAr.append([tmpLeadInd,tmpSecondInd])
                                        #Check if the mass is closer to Z than current candidate
                                        tmpDifFromZMass = abs(tmpDiElectronInvMass-ZMass)
                                        #Switching over variables
                                        if tmpDifFromZMass < difFromZMassOne:
                                            #Switching ZMassDif
                                            #difFromZMassTwo = difFromZMassOne
                                            difFromZMassOne = tmpDifFromZMass
                                            #Switching pair indices
                                            #lepPairTwoLeadInd = lepPairOneLeadInd
                                            #lepPairTwoTrailingInd = lepPairOneTrailingInd
                                            lepPairOneLeadInd = tmpLeadInd
                                            lepPairOneTrailingInd = tmpSecondInd
                                            #Switching 4 vectors
                                            #leadLepPairTwoVec = leadLepPairOneVec
                                            #trailingLepPairTwoVec = trailingLepPairOneVec
                                            leadLepPairOneVec = tmpLeadVec
                                            trailingLepPairOneVec = tmpTrailingVec
                                            leadLepPairCharge = tmpLeadCharge
                                            trailingLepPairCharge = tmpTrailingCharge

                                        #elif tmpDifFromZMass < difFromZMassTwo:
                                        #    difFromZMassTwo = tmpDifFromZMass
                                        #    lepPairTwoLeadInd = tmpLeadInd
                                        #    lepPairTwoTrailingInd = tmpSecondInd
                                        #    leadLepPairTwoVec = tmpLeadVec
                                        #    trailingLepPairTwoVec = tmpTrailingVec
                                            
                        
        muonLeading = False
        muonPassesCutsAr = []
        muonPassesZ2CutsAr = []

        #Muons loop
        for i in range(tmpnMuon):
            #No cuts
            tmpPtOne = ev.Muon_pt[i]
            tmpEtaOne = ev.Muon_eta[i]
            tmpMassOne = ev.Muon_mass[i]
            tmpPhiOne = ev.Muon_phi[i]
            
            h_Muon_pt.Fill(tmpPtOne)
            h_Muon_eta.Fill(tmpEtaOne)
            h_Muon_mass.Fill(tmpMassOne)
            h_Muon_phi.Fill(tmpPhiOne)
            
            #First Z Cuts
            if enoughLepCands and enoughMuonCands:
                if not ifEnoughMuonCandBool:
                    ifEnoughMuonCandCount += 1
                    ifEnoughMuonCandBool = True
                if tmpPtOne > firstZTrailingCut:
                    #Looping over other muons
                    for j in range(i+1,tmpnMuon):
                        #Check that muons have the opposite charge
                        tmpMuonCharge = ev.Muon_charge[i]
                        tmpMuonChargeTwo = ev.Muon_charge[j]
                        if tmpMuonCharge == - tmpMuonChargeTwo:
                            #Get vaariables from second electron
                            tmpPtTwo = ev.Muon_pt[j]
                            tmpEtaTwo = ev.Muon_eta[j]
                            tmpMassTwo = ev.Muon_mass[j]
                            tmpPhiTwo = ev.Muon_phi[j]

                            if tmpPtOne > tmpPtTwo:
                                tmpMaxPtLead = tmpPtOne
                                tmpMaxPtSecond = tmpPtTwo
                                tmpLeadInd = i
                                tmpSecondInd = j
                                tmpLeadCharge = tmpMuonCharge
                                tmpTrailingCharge = tmpMuonChargeTwo
                            else:
                                tmpMaxPtLead = tmpPtTwo
                                tmpMaxPtSecond = tmpPtOne
                                tmpLeadInd = j
                                tmpSecondInd = i
                                tmpLeadCharge = tmpMuonChargeTwo
                                tmpTrailingCharge = tmpMuonCharge
                            if tmpLeadInd == i:
                                tmpLeadVec = Math.PtEtaPhiMVector(tmpPtOne, tmpEtaOne, tmpPhiOne, tmpMassOne)
                                tmpTrailingVec = Math.PtEtaPhiMVector(tmpPtTwo, tmpEtaTwo, tmpPhiTwo, tmpMassTwo)
                            else:
                                tmpLeadVec = Math.PtEtaPhiMVector(tmpPtTwo, tmpEtaTwo, tmpPhiTwo, tmpMassTwo)
                                tmpTrailingVec = Math.PtEtaPhiMVector(tmpPtOne, tmpEtaOne, tmpPhiOne, tmpMassOne)
                            tmpDiMuonVec = tmpVecOne+tmpVecTwo
                            tmpDiMuonInvMass = tmpDiMuonVec.M()
                            if tmpDiMuonInvMass > leptonZ2Cut:
                                muonPassesZ2CutsAr.append([[tmpLeadInd,tmpSecondInd],[tmpLeadVec,tmpTrailingVec],[tmpLeadCharge,tmpTrailingCharge]])
                            
                            #Check that the pt of the second muon passes the lower pt cut
                            if tmpPtTwo > firstZTrailingCut:
                                #Sort the muons into leading and trailing based on pt
                                #Check that the lead muon passes the higher pt cut
                                if tmpMaxPtLead > firstZLeadingCut:
                                    
                                    #Check that invmass passes the Cut
                                    if tmpDiMuonInvMass > leptonInvMassCutLow:
                                        if not ifZ1MuonPairCandBool:
                                            ifZ1MuonPairCandCount += 1
                                            ifZ1MuonPairCandBool = True
                                        muonPassesCutsAr.append([tmpLeadInd,tmpSecondInd])
                                        #Check if the mass is closer to Z than current candidate
                                        tmpDifFromZMass = abs(tmpDiMuonInvMass-ZMass)
                                        #Switching over variables
                                        if tmpDifFromZMass < difFromZMassOne:
                                            muonLeading = True
                                            #Switching ZMassDif
                                            #difFromZMassTwo = difFromZMassOne
                                            difFromZMassOne = tmpDifFromZMass
                                            #Switching pair indices
                                            #lepPairTwoLeadInd = lepPairOneLeadInd
                                            #lepPairTwoTrailingInd = lepPairOneTrailingInd
                                            lepPairOneLeadInd = tmpLeadInd
                                            lepPairOneTrailingInd = tmpSecondInd
                                            #Switching 4 vectors
                                            #leadLepPairTwoVec = leadLepPairOneVec
                                            #trailingLepPairTwoVec = trailingLepPairOneVec
                                            leadLepPairOneVec = tmpLeadVec
                                            trailingLepPairOneVec = tmpTrailingVec
                                            leadLepPairCharge = tmpLeadCharge
                                            trailingLepPairCharge = tmpTrailingCharge

                                        #elif tmpDifFromZMass < difFromZMassTwo:
                                        #    difFromZMassTwo = tmpDifFromZMass
                                        #    lepPairTwoLeadInd = tmpLeadInd
                                        #    lepPairTwoTrailingInd = tmpSecondInd
                                        #    leadLepPairTwoVec = tmpLeadVec
                                        #    trailingLepPairTwoVec = tmpTrailingVec
                                            """
                                            switchZTwo = False
                                            #Checking if new Z2 candidate satisfies Z2 cuts
                                            
                                            if lepPairOneLeadInd != lepPairOneTrailingInd:
                                                if ev.Muon_charge[lepPairOneLeadInd] == -1:
                                                    tmpNegInd = lepPairOneLeadInd
                                                    tmpPosInd = lepPairOneTrailingInd
                                                else:
                                                    tmpNegInd = lepPairOneTrailingInd
                                                    tmpPosInd = lepPairOneLeadInd

                                                if lepPairTwoLeadInd != lepPairTwoTrailingInd:
                                                    tmpFourLepVec = leadLepPairOneVec + trailingLepPairOneVec + leadLepPairTwoVec + trailingLepPairTwoVec
                                                    tmpFourLepInvMass = tmpFourLepVec.M()
                                                    if tmpFourLepInvMass > 100:
                                                        if ev.Muon_charge[lepPairTwoLeadInd] == -1:
                                                            #tmpNegTwoInd = lepPairTwoLeadInd
                                                            #tmpPosTwoInd = lepPairTwoTrailingInd
                                                            if tmpNegInd == lepPairOneLeadInd:
                                                                tmpCrossLepPairVec = leadLepPairOneVec  + trailingLepPairTwoVec
                                                                if tmpCrossLepPairVec.M() > 12:
                                                                    switchZTwo = True
                                                                else:
                                                                    tmpCrossLepPairVec = leadLepPairTwoVec  + trailingLepPairOneVec
                                                                    if tmpCrossLepPairVec.M() > 12:
                                                                        switchZTwo = True
                                                            else:
                                                                tmpCrossLepPairVec = trailingLepPairOneVec  + trailingLepPairTwoVec
                                                                if tmpCrossLepPairVec.M() > 12:
                                                                    switchZTwo = True
                                                                else:
                                                                    tmpCrossLepPairVec = leadLepPairTwoVec  + LeadLepPairOneVec
                                                                    if tmpCrossLepPairVec.M() > 12:
                                                                        switchZTwo = True
                                                        else:
                                                            #tmpNegTwoInd = lepPairTwoTrailingInd
                                                            #tmpPosTwoInd = lepPairTwoLeadInd
                                                            if tmpPosInd == lepPairOneLeadInd:
                                                                tmpCrossLepPairVec = leadLepPairOneVec  + trailingLepPairTwoVec
                                                                if tmpCrossLepPairVec.M() > 12:
                                                                    switchZTwo = True
                                                                else:
                                                                    tmpCrossLepPairVec = leadLepPairTwoVec  + trailingLepPairOneVec
                                                                    if tmpCrossLepPairVec.M() > 12:
                                                                        switchZTwo = True
                                                            else:
                                                                tmpCrossLepPairVec = trailingLepPairOneVec  + trailingLepPairTwoVec
                                                                if tmpCrossLepPairVec.M() > 12:
                                                                    switchZTwo = True
                                                                else:
                                                                    tmpCrossLepPairVec = leadLepPairTwoVec  + LeadLepPairOneVec
                                                                    if tmpCrossLepPairVec.M() > 12:
                                                                        switchZTwo = True
                                                        
                                                    
                                                else:
                                                    switchZTwo = True
                                            
                                            #Checking if new Z2 candidate has higher pt than current one
                                            if switchZTwo:
                                                if ev.Muon_pt[lepPairOneLeadInd] + ev.Muon_pt[lepPairOneTrailingInd] > ev.Muon_pt[lepPairTwoLeadInd] + ev.Muon_pt[lepPairTwoTrailingInd]:
                                                    difFromZMassTwo = difFromZMassOne
                                                    lepPairTwoLeadInd = lepPairOneLeadInd
                                                    lepPairTwoTrailingInd = lepPairOneTrailingInd
                                                    leadLepPairTwoVec = leadLepPairOneVec
                                                    trailingLepPairTwoVec = trailingLepPairOneVec
                                            """

                                                    
                                            """
                                            #Switching ZMassDif
                                            difFromZMassOne = tmpDifFromZMass
                                            #Switching pair indices
                                            
                                            lepPairOneLeadInd = tmpLeadInd
                                            lepPairOneTrailingInd = tmpSecondInd
                                            #Switching 4 vectors
                                            
                                            leadLepPairOneVec = tmpLeadVec
                                            trailingLepPairOneVec = tmpTrailingVec
                                        """
                                        """
                                        elif tmpDifFromZMass < difFromZMassTwo:
                                            difFromZMassTwo = tmpDifFromZMass
                                            lepPairTwoLeadInd = tmpLeadInd
                                            lepPairTwoTrailingInd = tmpSecondInd
                                            leadLepPairTwoVec = tmpLeadVec
                                            trailingLepPairTwoVec = tmpTrailingVec
                                        """
        
        
            """
            if lepPairTwoLeadInd == lepPairTwoTrailingInd:
                for lepIndAr in elecPassesCutsAr:
                    if lepIndAr[0] == lepPairOneLeadInd or lepIndAr[1] == lepPairOneTrailingInd:
                        continue
                    tmpLeadLepPairTwoVec = Math.PtEtaPhiMVector(ev.Electron_pt[lepIndAr[0]],ev.Electron_eta[lepIndAr[0]],ev.Electron_phi[lepIndAr[0]],ev.Electron_mass[lepIndAr[0]])
                    tmpTrailingLepPairTwoVec = Math.PtEtaPhiMVector(ev.Electron_pt[lepIndAr[1]],ev.Electron_eta[lepIndAr[1]],ev.Electron_phi[lepIndAr[1]],ev.Electron_mass[lepIndAr[1]])

                    trailingLepPairVec = Math.PtEtaPhiMVector(0,0,0,0)
            """
        passesCandCuts = False
        muonZ2Pair = False
        if len(muonPassesCutsAr) + len(elecPassesCutsAr) > 0 and len(muonPassesZ2CutsAr) + len(elecPassesZ2CutsAr) > 0:
            for i,elecZ2Cand in enumerate(elecPassesZ2CutsAr):
                if elecZ2Cand[0][0] != lepPairOneLeadInd and elecZ2Cand[0][0] != lepPairOneTrailingInd and elecZ2Cand[0][1] != lepPairOneLeadInd and elecZ2Cand[0][1] != lepPairOneTrailingInd: 
                    fourLepVec = elecZ2Cand[1][0] + elecZ2Cand[1][1] + leadLepPairOneVec + trailingLepPairOneVec
                    fourLepInvMass = fourLepVec.M()
                    if fourLepInvMass > fourLeptonInvMassCut:
                        passesCandCuts = True
                        if not muonLeading:
                            passesCandCuts = False
                            if elecZ2Cand[2][0] != leadLepPairCharge:
                                tmpCrossCandVec = elecZ2Cand[1][0] + leadLepPairOneVec
                                if tmpCrossCandVec.M() > 12:
                                    passesCandCuts = True
                                else:
                                    tmpCrossCandVec = elecZ2Cand[1][1] + trailingLepPairOneVec
                                    if tmpCrossCandVec.M() > 12:
                                        passesCandCuts = True
                            else:
                                tmpCrossCandVec = elecZ2Cand[1][1] + leadLepPairOneVec
                                if tmpCrossCandVec.M() > 12:
                                    passesCandCuts = True
                                else:
                                    tmpCrossCandVec = elecZ2Cand[1][0] + trailingLepPairOneVec
                                    if tmpCrossCandVec.M() > 12:
                                        passesCandCuts = True
                        if passesCandCuts:
                            if not ifZ2ElecPairCandBool:
                                ifZ2ElecPairCandCount += 1
                                ifZ2ElecPairCandBool = True
                            if elecZ2Cand[1][0].Pt() > leadZ2Pt:
                                leadZ2Pt = elecZ2Cand[1][0].Pt()
                                trailingZ2Pt = elecZ2Cand[1][1].Pt()
                                leadZ2LepPairInd = i
                            elif elecZ2Cand[1][0].Pt() == leadZ2Pt:
                                if elecZ2Cand[1][1].Pt() == trailingZ2Pt:
                                    trailingZ2Pt = elecZ2Cand[1][1].Pt()
                                    leadZ2LepPairInd = i


                            


            for i,muonZ2Cand in enumerate(muonPassesZ2CutsAr):
                if muonZ2Cand[0][0] != lepPairOneLeadInd and muonZ2Cand[0][0] != lepPairOneTrailingInd and muonZ2Cand[0][1] != lepPairOneLeadInd and muonZ2Cand[0][1] != lepPairOneTrailingInd: 
                    fourLepVec = muonZ2Cand[1][0] + muonZ2Cand[1][1] + leadLepPairOneVec + trailingLepPairOneVec
                    fourLepInvMass = fourLepVec.M()
                    if fourLepInvMass > fourLeptonInvMassCut:
                        passesCandCuts = True
                        if muonLeading:
                            passesCandCuts = False
                            if muonZ2Cand[2][0] != leadLepPairCharge:
                                tmpCrossCandVec = muonZ2Cand[1][0] + leadLepPairOneVec
                                if tmpCrossCandVec.M() > 12:
                                    passesCandCuts = True
                                else:
                                    tmpCrossCandVec = muonZ2Cand[1][1] + trailingLepPairOneVec
                                    if tmpCrossCandVec.M() > 12:
                                        passesCandCuts = True
                            else:
                                tmpCrossCandVec = muonZ2Cand[1][1] + leadLepPairOneVec
                                if tmpCrossCandVec.M() > 12:
                                    passesCandCuts = True
                                else:
                                    tmpCrossCandVec = muonZ2Cand[1][0] + trailingLepPairOneVec
                                    if tmpCrossCandVec.M() > 12:
                                        passesCandCuts = True
                        if passesCandCuts:
                            if not ifZ2MuonPairCandBool:
                                ifZ2MuonPairCandCount += 1
                                ifZ2MuonPairCandBool = True
                            if muonZ2Cand[1][0].Pt() > leadZ2Pt:
                                muonZ2Pair = True
                                leadZ2Pt = muonZ2Cand[1][0].Pt()
                                trailingZ2Pt = muonZ2Cand[1][1].Pt()
                                leadZ2LepPairInd = i
                            elif muonZ2Cand[1][0].Pt() == leadZ2Pt:
                                if muonZ2Cand[1][1].Pt() == trailingZ2Pt:
                                    muonZ2Pair = True
                                    trailingZ2Pt = muonZ2Cand[1][1].Pt()
                                    leadZ2LepPairInd = i
            #At this point, if the cuts were passed, should have two pairs of leptons. The first reprsented by
            #lepPairOneLeadInd,lepPairOneTrailingInd variables (also lead/trailingLepPairOneVec and lead/trailingLepPairCharge)
            #which can be used to index ev.Electron/Muon_Branch
            #The second represented by 
            #leadZ2LepPairInd which can be used to index elec/muonPassesZ2CutsAr
            #which contains the indices for accessing the ev.Electron/Muon_branch, the four vector, and the charge)
            #So first check that the cuts were passed:
            if leadZ2LepPairInd >= 0:
                #Now we want to cut based on the relative isolation
                #For each lepton this is obtained as follows
                #Sum up the Pt for all the tracks, the energy deposits in the ECAL, and the energy deposits in the HCAL, within a DeltaR < 0.3 cone around the lepton
                #Add these three sums together and divide by the lepton's Pt
                #Unfortunately with NanoAOD, you do not have the information to do these sums.
                #There are branches that have precalculated them, but only for electrons with Pt > 35GeV
                #The muon branches don't have these, but rather have values based on particle flow
                #Particularly the Muon_pfRelIso03_all branch
                #Not sure if it's at all proper to add these together, but I think to not bias things I'll only do the cut if both leptons have E > 35GeV
                passesIsoCuts = True
                #There is absolutely a better way to do this than these awful if blocks. should be able to just put each isolation variable in an array
                #at the start, with an array that says whether or not they have pt over 35 and then loop over those arrays. Do it later
                if muonLeading:
                    if muonZ2Pair:
                        #muon Z1, muon Z2
                        if leadLepPairOneVec.Pt() > 35:
                            if trailingLepPairOneVec.Pt() > 35:
                                tmpIsoOne = ev.Muon_pfRelIso03_all[lepPairOneLeadInd]
                                tmpIsoTwo = ev.Muon_pfRelIso03_all[lepPairOneTrailingInd]
                                if tmpIsoOne + tmpIsoTwo > 0.35:
                                    passesIsoCuts = False
                                elif muonPassesZ2CutsAr[leadZ2LepPairInd][1][0].Pt() > 35:
                                    tmpIsoThree = ev.Muon_pfRelIso03_all[muonPassesZ2CutsAr[leadZ2LepPairInd][0][0]]
                                    if tmpIsoOne + tmpIsoThree > 0.35:
                                        passesIsoCuts = False
                                    elif tmpIsoTwo + tmpIsoThree > 0.35:
                                        passesIsoCuts = False
                                    elif muonPassesZ2CutsAr[leadZ2LepPairInd][1][1].Pt() > 35:
                                        tmpIsoFour = ev.Muon_pfRelIso03_all[muonPassesZ2CutsAr[leadZ2LepPairInd][0][1]]
                                        if tmpIsoOne + tmpIsoFour > 0.35:
                                            passesIsoCuts = False
                                        elif tmpIsoTwo + tmpIsoFour > 0.35:
                                            passesIsoCuts = False
                                        elif tmpIsoThree + tmpIsoFour > 0.35:
                                            passesIsoCuts = False
                            elif muonPassesZ2CutsAr[leadZ2LepPairInd][1][0].Pt() > 35:
                                tmpIsoOne = ev.Muon_pfRelIso03_all[lepPairOneLeadInd]
                                tmpIsoThree = ev.Muon_pfRelIso03_all[muonPassesZ2CutsAr[leadZ2LepPairInd][0][0]]
                                if tmpIsoOne + tmpIsoThree > 0.35:
                                    passesIsoCuts = False
                                elif muonPassesZ2CutsAr[leadZ2LepPairInd][1][1].Pt() > 35:
                                    tmpIsoFour = ev.Muon_pfRelIso03_all[muonPassesZ2CutsAr[leadZ2LepPairInd][0][1]]
                                    if tmpIsoOne + tmpIsoFour > 0.35:
                                        passesIsoCuts = False
                                    elif tmpIsoThree + tmpIsoFour > 0.35:
                                        passesIsoCuts = False
                        elif muonPassesZ2CutsAr[leadZ2LepPairInd][1][0].Pt() > 35:
                            if muonPassesZ2CutsAr[leadZ2LepPairInd][1][1].Pt() > 35:
                                tmpIsoThree = ev.Muon_pfRelIso03_all[muonPassesZ2CutsAr[leadZ2LepPairInd][0][0]]
                                tmpIsoFour = ev.Muon_pfRelIso03_all[muonPassesZ2CutsAr[leadZ2LepPairInd][0][1]]
                                if tmpIsoThree + tmpIsoFour > 0.35:
                                    passesIsoCuts = False
                    else:
                        #muon Z1, elec Z2
                        if leadLepPairOneVec.Pt() > 35:
                            if trailingLepPairOneVec.Pt() > 35:
                                tmpIsoOne = ev.Muon_pfRelIso03_all[lepPairOneLeadInd]
                                tmpIsoTwo = ev.Muon_pfRelIso03_all[lepPairOneTrailingInd]
                                if tmpIsoOne + tmpIsoTwo > 0.35:
                                    passesIsoCuts = False
                                elif elecPassesZ2CutsAr[leadZ2LepPairInd][1][0].Pt() > 35:
                                    if abs(ev.Electron_eta[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]]) < 1.4:
                                        tmpIsoThree = ( ev.Electron_dr03TkSumPt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]] + max(0., ev.Electron_dr03EcalRecHitSumEt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]] - 1.) + ev.Electron_dr03HcalDepth1TowerSumEt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]] ) / ev.Electron_pt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]]
                                    else:
                                        tmpIsoThree = ( ev.Electron_dr03TkSumPt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]] + ev.Electron_dr03EcalRecHitSumEt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]] + ev.Electron_dr03HcalDepth1TowerSumEt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]] ) / ev.Electron_pt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]]
                                        
                                    if tmpIsoOne + tmpIsoThree > 0.35:
                                        passesIsoCuts = False
                                    elif tmpIsoTwo + tmpIsoThree > 0.35:
                                        passesIsoCuts = False
                                    elif elecPassesZ2CutsAr[leadZ2LepPairInd][1][1].Pt() > 35:
                                        if abs(ev.Electron_eta[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]]) < 1.4:
                                            tmpIsoFour = ( ev.Electron_dr03TkSumPt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]] + max(0., ev.Electron_dr03EcalRecHitSumEt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]] - 1.) + ev.Electron_dr03HcalDepth1TowerSumEt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]] ) / ev.Electron_pt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]]
                                        else:
                                            tmpIsoFour = ( ev.Electron_dr03TkSumPt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]] + ev.Electron_dr03EcalRecHitSumEt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]] + ev.Electron_dr03HcalDepth1TowerSumEt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]] ) / ev.Electron_pt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]]
                                        
                                        if tmpIsoOne + tmpIsoFour > 0.35:
                                            passesIsoCuts = False
                                        elif tmpIsoTwo + tmpIsoFour > 0.35:
                                            passesIsoCuts = False
                                        elif tmpIsoThree + tmpIsoFour > 0.35:
                                            passesIsoCuts = False
                            elif elecPassesZ2CutsAr[leadZ2LepPairInd][1][0].Pt() > 35:
                                tmpIsoOne = ev.Muon_pfRelIso03_all[lepPairOneLeadInd]
                                if abs(ev.Electron_eta[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]]) < 1.4:
                                    tmpIsoThree = ( ev.Electron_dr03TkSumPt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]] + max(0., ev.Electron_dr03EcalRecHitSumEt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]] - 1.) + ev.Electron_dr03HcalDepth1TowerSumEt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]] ) / ev.Electron_pt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]]
                                else:
                                    tmpIsoThree = ( ev.Electron_dr03TkSumPt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]] + ev.Electron_dr03EcalRecHitSumEt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]] + ev.Electron_dr03HcalDepth1TowerSumEt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]] ) / ev.Electron_pt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]]
                                if tmpIsoOne + tmpIsoThree > 0.35:
                                    passesIsoCuts = False
                                elif elecPassesZ2CutsAr[leadZ2LepPairInd][1][1].Pt() > 35:
                                    if abs(ev.Electron_eta[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]]) < 1.4:
                                        tmpIsoFour = ( ev.Electron_dr03TkSumPt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]] + max(0., ev.Electron_dr03EcalRecHitSumEt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]] - 1.) + ev.Electron_dr03HcalDepth1TowerSumEt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]] ) / ev.Electron_pt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]]
                                    else:
                                        tmpIsoFour = ( ev.Electron_dr03TkSumPt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]] + ev.Electron_dr03EcalRecHitSumEt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]] + ev.Electron_dr03HcalDepth1TowerSumEt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]] ) / ev.Electron_pt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]]
                                        
                                    if tmpIsoOne + tmpIsoFour > 0.35:
                                        passesIsoCuts = False
                                    elif tmpIsoThree + tmpIsoFour > 0.35:
                                        passesIsoCuts = False
                        elif elecPassesZ2CutsAr[leadZ2LepPairInd][1][0].Pt() > 35:
                            if elecPassesZ2CutsAr[leadZ2LepPairInd][1][1].Pt() > 35:
                                if abs(ev.Electron_eta[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]]) < 1.4:
                                    tmpIsoThree = ( ev.Electron_dr03TkSumPt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]] + max(0., ev.Electron_dr03EcalRecHitSumEt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]] - 1.) + ev.Electron_dr03HcalDepth1TowerSumEt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]] ) / ev.Electron_pt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]]
                                else:
                                    tmpIsoThree = ( ev.Electron_dr03TkSumPt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]] + ev.Electron_dr03EcalRecHitSumEt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]] + ev.Electron_dr03HcalDepth1TowerSumEt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]] ) / ev.Electron_pt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]]
                                if abs(ev.Electron_eta[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]]) < 1.4:
                                    tmpIsoFour = ( ev.Electron_dr03TkSumPt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]] + max(0., ev.Electron_dr03EcalRecHitSumEt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]] - 1.) + ev.Electron_dr03HcalDepth1TowerSumEt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]] ) / ev.Electron_pt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]]
                                else:
                                    tmpIsoFour = ( ev.Electron_dr03TkSumPt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]] + ev.Electron_dr03EcalRecHitSumEt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]] + ev.Electron_dr03HcalDepth1TowerSumEt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]] ) / ev.Electron_pt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]]
                                if tmpIsoThree + tmpIsoFour > 0.35:
                                    passesIsoCuts = False
                else:
                    if muonZ2Pair:
                        #Electron Z1, muon Z2
                        if leadLepPairOneVec.Pt() > 35:
                            if trailingLepPairOneVec.Pt() > 35:
                                if abs(ev.Electron_eta[lepPairOneLeadInd]) < 1.4:
                                    tmpIsoOne = ( ev.Electron_dr03TkSumPt[lepPairOneLeadInd] + max(0., ev.Electron_dr03EcalRecHitSumEt[lepPairOneLeadInd] - 1.) + ev.Electron_dr03HcalDepth1TowerSumEt[lepPairOneLeadInd] ) / ev.Electron_pt[lepPairOneLeadInd]
                                else:
                                    tmpIsoOne = ( ev.Electron_dr03TkSumPt[lepPairOneLeadInd] + ev.Electron_dr03EcalRecHitSumEt[lepPairOneLeadInd] + ev.Electron_dr03HcalDepth1TowerSumEt[lepPairOneLeadInd] ) / ev.Electron_pt[lepPairOneLeadInd]
                                
                                if abs(ev.Electron_eta[lepPairOneTrailingInd]) < 1.4:
                                    tmpIsoTwo = ( ev.Electron_dr03TkSumPt[lepPairOneTrailingInd] + max(0., ev.Electron_dr03EcalRecHitSumEt[lepPairOneTrailingInd] - 1.) + ev.Electron_dr03HcalDepth1TowerSumEt[lepPairOneTrailingInd] ) / ev.Electron_pt[lepPairOneTrailingInd]
                                else:
                                    tmpIsoTwo = ( ev.Electron_dr03TkSumPt[lepPairOneTrailingInd] + ev.Electron_dr03EcalRecHitSumEt[lepPairOneTrailingInd] + ev.Electron_dr03HcalDepth1TowerSumEt[lepPairOneTrailingInd] ) / ev.Electron_pt[lepPairOneTrailingInd]
                                
                                if tmpIsoOne + tmpIsoTwo > 0.35:
                                    passesIsoCuts = False
                                elif muonPassesZ2CutsAr[leadZ2LepPairInd][1][0].Pt() > 35:
                                    tmpIsoThree = ev.Muon_pfRelIso03_all[muonPassesZ2CutsAr[leadZ2LepPairInd][0][0]]
                                    if tmpIsoOne + tmpIsoThree > 0.35:
                                        passesIsoCuts = False
                                    elif tmpIsoTwo + tmpIsoThree > 0.35:
                                        passesIsoCuts = False
                                    elif muonPassesZ2CutsAr[leadZ2LepPairInd][1][1].Pt() > 35:
                                        tmpIsoFour = ev.Muon_pfRelIso03_all[muonPassesZ2CutsAr[leadZ2LepPairInd][0][1]]
                                        if tmpIsoOne + tmpIsoFour > 0.35:
                                            passesIsoCuts = False
                                        elif tmpIsoTwo + tmpIsoFour > 0.35:
                                            passesIsoCuts = False
                                        elif tmpIsoThree + tmpIsoFour > 0.35:
                                            passesIsoCuts = False
                            elif muonPassesZ2CutsAr[leadZ2LepPairInd][1][0].Pt() > 35:
                                if abs(ev.Electron_eta[lepPairOneLeadInd]) < 1.4:
                                    tmpIsoOne = ( ev.Electron_dr03TkSumPt[lepPairOneLeadInd] + max(0., ev.Electron_dr03EcalRecHitSumEt[lepPairOneLeadInd] - 1.) + ev.Electron_dr03HcalDepth1TowerSumEt[lepPairOneLeadInd] ) / ev.Electron_pt[lepPairOneLeadInd]
                                else:
                                    tmpIsoOne = ( ev.Electron_dr03TkSumPt[lepPairOneLeadInd] + ev.Electron_dr03EcalRecHitSumEt[lepPairOneLeadInd] + ev.Electron_dr03HcalDepth1TowerSumEt[lepPairOneLeadInd] ) / ev.Electron_pt[lepPairOneLeadInd]
                                
                                tmpIsoThree = ev.Muon_pfRelIso03_all[muonPassesZ2CutsAr[leadZ2LepPairInd][0][0]]
                                if tmpIsoOne + tmpIsoThree > 0.35:
                                    passesIsoCuts = False
                                elif muonPassesZ2CutsAr[leadZ2LepPairInd][1][1].Pt() > 35:
                                    tmpIsoFour = ev.Muon_pfRelIso03_all[muonPassesZ2CutsAr[leadZ2LepPairInd][0][1]]
                                    if tmpIsoOne + tmpIsoFour > 0.35:
                                        passesIsoCuts = False
                                    elif tmpIsoThree + tmpIsoFour > 0.35:
                                        passesIsoCuts = False
                        elif muonPassesZ2CutsAr[leadZ2LepPairInd][1][0].Pt() > 35:
                            if muonPassesZ2CutsAr[leadZ2LepPairInd][1][1].Pt() > 35:
                                tmpIsoThree = ev.Muon_pfRelIso03_all[muonPassesZ2CutsAr[leadZ2LepPairInd][0][0]]
                                tmpIsoFour = ev.Muon_pfRelIso03_all[muonPassesZ2CutsAr[leadZ2LepPairInd][0][1]]
                                if tmpIsoThree + tmpIsoFour > 0.35:
                                    passesIsoCuts = False
                    else:
                        #Elec Z1, elec Z2
                        if leadLepPairOneVec.Pt() > 35:
                            if trailingLepPairOneVec.Pt() > 35:
                                if abs(ev.Electron_eta[lepPairOneLeadInd]) < 1.4:
                                    tmpIsoOne = ( ev.Electron_dr03TkSumPt[lepPairOneLeadInd] + max(0., ev.Electron_dr03EcalRecHitSumEt[lepPairOneLeadInd] - 1.) + ev.Electron_dr03HcalDepth1TowerSumEt[lepPairOneLeadInd] ) / ev.Electron_pt[lepPairOneLeadInd]
                                else:
                                    tmpIsoOne = ( ev.Electron_dr03TkSumPt[lepPairOneLeadInd] + ev.Electron_dr03EcalRecHitSumEt[lepPairOneLeadInd] + ev.Electron_dr03HcalDepth1TowerSumEt[lepPairOneLeadInd] ) / ev.Electron_pt[lepPairOneLeadInd]
                                
                                if abs(ev.Electron_eta[lepPairOneTrailingInd]) < 1.4:
                                    tmpIsoTwo = ( ev.Electron_dr03TkSumPt[lepPairOneTrailingInd] + max(0., ev.Electron_dr03EcalRecHitSumEt[lepPairOneTrailingInd] - 1.) + ev.Electron_dr03HcalDepth1TowerSumEt[lepPairOneTrailingInd] ) / ev.Electron_pt[lepPairOneTrailingInd]
                                else:
                                    tmpIsoTwo = ( ev.Electron_dr03TkSumPt[lepPairOneTrailingInd] + ev.Electron_dr03EcalRecHitSumEt[lepPairOneTrailingInd] + ev.Electron_dr03HcalDepth1TowerSumEt[lepPairOneTrailingInd] ) / ev.Electron_pt[lepPairOneTrailingInd]
                                
                                if tmpIsoOne + tmpIsoTwo > 0.35:
                                    passesIsoCuts = False
                                elif elecPassesZ2CutsAr[leadZ2LepPairInd][1][0].Pt() > 35:
                                    if abs(ev.Electron_eta[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]]) < 1.4:
                                        tmpIsoThree = ( ev.Electron_dr03TkSumPt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]] + max(0., ev.Electron_dr03EcalRecHitSumEt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]] - 1.) + ev.Electron_dr03HcalDepth1TowerSumEt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]] ) / ev.Electron_pt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]]
                                    else:
                                        tmpIsoThree = ( ev.Electron_dr03TkSumPt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]] + ev.Electron_dr03EcalRecHitSumEt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]] + ev.Electron_dr03HcalDepth1TowerSumEt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]] ) / ev.Electron_pt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]]
                                        
                                    if tmpIsoOne + tmpIsoThree > 0.35:
                                        passesIsoCuts = False
                                    elif tmpIsoTwo + tmpIsoThree > 0.35:
                                        passesIsoCuts = False
                                    elif elecPassesZ2CutsAr[leadZ2LepPairInd][1][1].Pt() > 35:
                                        if abs(ev.Electron_eta[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]]) < 1.4:
                                            tmpIsoFour = ( ev.Electron_dr03TkSumPt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]] + max(0., ev.Electron_dr03EcalRecHitSumEt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]] - 1.) + ev.Electron_dr03HcalDepth1TowerSumEt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]] ) / ev.Electron_pt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]]
                                        else:
                                            tmpIsoFour = ( ev.Electron_dr03TkSumPt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]] + ev.Electron_dr03EcalRecHitSumEt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]] + ev.Electron_dr03HcalDepth1TowerSumEt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]] ) / ev.Electron_pt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]]
                                        
                                        if tmpIsoOne + tmpIsoFour > 0.35:
                                            passesIsoCuts = False
                                        elif tmpIsoTwo + tmpIsoFour > 0.35:
                                            passesIsoCuts = False
                                        elif tmpIsoThree + tmpIsoFour > 0.35:
                                            passesIsoCuts = False
                            elif elecPassesZ2CutsAr[leadZ2LepPairInd][1][0].Pt() > 35:
                                if abs(ev.Electron_eta[lepPairOneLeadInd]) < 1.4:
                                    tmpIsoOne = ( ev.Electron_dr03TkSumPt[lepPairOneLeadInd] + max(0., ev.Electron_dr03EcalRecHitSumEt[lepPairOneLeadInd] - 1.) + ev.Electron_dr03HcalDepth1TowerSumEt[lepPairOneLeadInd] ) / ev.Electron_pt[lepPairOneLeadInd]
                                else:
                                    tmpIsoOne = ( ev.Electron_dr03TkSumPt[lepPairOneLeadInd] + ev.Electron_dr03EcalRecHitSumEt[lepPairOneLeadInd] + ev.Electron_dr03HcalDepth1TowerSumEt[lepPairOneLeadInd] ) / ev.Electron_pt[lepPairOneLeadInd]
                                
                                if abs(ev.Electron_eta[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]]) < 1.4:
                                    tmpIsoThree = ( ev.Electron_dr03TkSumPt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]] + max(0., ev.Electron_dr03EcalRecHitSumEt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]] - 1.) + ev.Electron_dr03HcalDepth1TowerSumEt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]] ) / ev.Electron_pt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]]
                                else:
                                    tmpIsoThree = ( ev.Electron_dr03TkSumPt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]] + ev.Electron_dr03EcalRecHitSumEt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]] + ev.Electron_dr03HcalDepth1TowerSumEt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]] ) / ev.Electron_pt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]]
                                if tmpIsoOne + tmpIsoThree > 0.35:
                                    passesIsoCuts = False
                                elif elecPassesZ2CutsAr[leadZ2LepPairInd][1][1].Pt() > 35:
                                    if abs(ev.Electron_eta[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]]) < 1.4:
                                        tmpIsoFour = ( ev.Electron_dr03TkSumPt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]] + max(0., ev.Electron_dr03EcalRecHitSumEt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]] - 1.) + ev.Electron_dr03HcalDepth1TowerSumEt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]] ) / ev.Electron_pt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]]
                                    else:
                                        tmpIsoFour = ( ev.Electron_dr03TkSumPt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]] + ev.Electron_dr03EcalRecHitSumEt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]] + ev.Electron_dr03HcalDepth1TowerSumEt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]] ) / ev.Electron_pt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]]
                                        
                                    if tmpIsoOne + tmpIsoFour > 0.35:
                                        passesIsoCuts = False
                                    elif tmpIsoThree + tmpIsoFour > 0.35:
                                        passesIsoCuts = False
                        elif elecPassesZ2CutsAr[leadZ2LepPairInd][1][0].Pt() > 35:
                            if elecPassesZ2CutsAr[leadZ2LepPairInd][1][1].Pt() > 35:
                                if abs(ev.Electron_eta[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]]) < 1.4:
                                    tmpIsoThree = ( ev.Electron_dr03TkSumPt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]] + max(0., ev.Electron_dr03EcalRecHitSumEt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]] - 1.) + ev.Electron_dr03HcalDepth1TowerSumEt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]] ) / ev.Electron_pt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]]
                                else:
                                    tmpIsoThree = ( ev.Electron_dr03TkSumPt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]] + ev.Electron_dr03EcalRecHitSumEt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]] + ev.Electron_dr03HcalDepth1TowerSumEt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]] ) / ev.Electron_pt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]]
                                if abs(ev.Electron_eta[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]]) < 1.4:
                                    tmpIsoFour = ( ev.Electron_dr03TkSumPt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]] + max(0., ev.Electron_dr03EcalRecHitSumEt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]] - 1.) + ev.Electron_dr03HcalDepth1TowerSumEt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]] ) / ev.Electron_pt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]]
                                else:
                                    tmpIsoFour = ( ev.Electron_dr03TkSumPt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]] + ev.Electron_dr03EcalRecHitSumEt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]] + ev.Electron_dr03HcalDepth1TowerSumEt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]] ) / ev.Electron_pt[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]]
                                if tmpIsoThree + tmpIsoFour > 0.35:
                                    passesIsoCuts = False
                #Now, assuming all *these* cuts pass, on to cut 6.
                #Want the SIP of the leptons
                if passesIsoCuts:
                    if not passesIsoCutsBool:
                        passesIsoCutsCount += 1
                        passesIsoCutsBool = True

                    passesSIPCut = True
                    if muonLeading:
                        if muonZ2Pair:
                            if ev.Muon_sip3d[lepPairOneLeadInd] > 4:
                                passesSIPCut = False
                            elif ev.Muon_sip3d[lepPairOneTrailingInd] > 4:
                                passesSIPCut = False
                            elif ev.Muon_sip3d[muonPassesZ2CutsAr[leadZ2LepPairInd][0][0]] > 4:
                                passesSIPCut = False
                            elif ev.Muon_sip3d[muonPassesZ2CutsAr[leadZ2LepPairInd][0][1]] > 4:
                                passesSIPCut = False
                        else:
                            if ev.Muon_sip3d[lepPairOneLeadInd] > 4:
                                passesSIPCut = False
                            elif ev.Muon_sip3d[lepPairOneTrailingInd] > 4:
                                passesSIPCut = False
                            elif ev.Electron_sip3d[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]] > 4:
                                passesSIPCut = False
                            elif ev.Electron_sip3d[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]] > 4:
                                passesSIPCut = False
                    elif muonZ2Pair:
                        if ev.Electron_sip3d[lepPairOneLeadInd] > 4:
                            passesSIPCut = False
                        elif ev.Electron_sip3d[lepPairOneTrailingInd] > 4:
                            passesSIPCut = False
                        elif ev.Muon_sip3d[muonPassesZ2CutsAr[leadZ2LepPairInd][0][0]] > 4:
                            passesSIPCut = False
                        elif ev.Muon_sip3d[muonPassesZ2CutsAr[leadZ2LepPairInd][0][1]] > 4:
                            passesSIPCut = False
                    else:
                        if ev.Electron_sip3d[lepPairOneLeadInd] > 4:
                            passesSIPCut = False
                        elif ev.Electron_sip3d[lepPairOneTrailingInd] > 4:
                            passesSIPCut = False
                        elif ev.Electron_sip3d[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]] > 4:
                            passesSIPCut = False
                        elif ev.Electron_sip3d[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]] > 4:
                            passesSIPCut = False
                #Now just check that the Z1 and Z2 inv mass falls within the Z low and Z high cuts (60 and 120GeV)
                if passesSIPCut:
                    if not passesSIPCutBool:
                        passesSIPCutCount += 1
                        passesSIPCutBool = True

                    tmpVec = leadLepPairOneVec + trailingLepPairOneVec
                    tmpZ1InvMass = tmpVec.M()
                    if tmpZ1InvMass < 120:
                        if muonZ2Pair:
                            tmpLeadZ2Vec = muonPassesZ2CutsAr[leadZ2LepPairInd][1][0]
                            tmpTrailingZ2Vec = muonPassesZ2CutsAr[leadZ2LepPairInd][1][1]
                            tmpVecTwo = tmpLeadZ2Vec + tmpTrailingZ2Vec
                        else:
                            tmpLeadZ2Vec = elecPassesZ2CutsAr[leadZ2LepPairInd][1][0]
                            tmpTrailingZ2Vec = elecPassesZ2CutsAr[leadZ2LepPairInd][1][1]
                            tmpVecTwo = tmpLeadZ2Vec + tmpTrailingZ2Vec
                        tmpZ2InvMass = tmpVecTwo.M()
                        if tmpZ2InvMass > 60 and tmpZ2InvMass < 120:
                            #at this point all lepton cuts have been passed. Filling histograms
                            if not allCutPassBool:
                                allCutPassCount += 1
                                allCutPassBool = True
                            LepFullCut_Z1Leadpt.Fill(leadLepPairOneVec.Pt())
                            LepFullCut_Z1Trailingpt.Fill(trailingLepPairOneVec.Pt())
                            tmpLeadEta = leadLepPairOneVec.Eta()
                            tmpTrailingEta = trailingLepPairOneVec.Eta()
                            LepFullCut_Z1Leadeta.Fill(tmpLeadEta)
                            LepFullCut_Z1Trailingeta.Fill(tmpTrailingEta)
                            
                            LepFullCut_Z1Leadmass.Fill(leadLepPairOneVec.M())
                            LepFullCut_Z1Trailingmass.Fill(trailingLepPairOneVec.M())
                            LepFullCut_Z1Leadphi.Fill(leadLepPairOneVec.Phi())
                            LepFullCut_Z1Trailingphi.Fill(trailingLepPairOneVec.Phi())
                            #tmpVec = leadLepPairOneVec + trailingLepPairOneVec

                            LepFullCut_Z1InvMass.Fill(tmpZ1InvMass)
                            LepFullCut_Z1EtaSep.Fill(abs(tmpLeadEta - tmpTrailingEta))
                            

                            LepFullCut_Z2Leadpt.Fill(tmpLeadZ2Vec.Pt())
                            LepFullCut_Z2Trailingpt.Fill(tmpTrailingZ2Vec.Pt())
                            LepFullCut_Z2Leadmass.Fill(tmpLeadZ2Vec.M())
                            LepFullCut_Z2Trailingmass.Fill(tmpTrailingZ2Vec.M())
                            LepFullCut_Z2Leadphi.Fill(tmpLeadZ2Vec.Phi())
                            LepFullCut_Z2Trailingphi.Fill(tmpTrailingZ2Vec.Phi())

                            tmpLeadEta = tmpLeadZ2Vec.Eta()
                            tmpTrailingEta = tmpTrailingZ2Vec.Eta()

                                
                            LepFullCut_Z2Leadeta.Fill(tmpLeadEta)
                            LepFullCut_Z2Trailingeta.Fill(tmpTrailingEta)
                            LepFullCut_Z2InvMass.Fill(tmpZ2InvMass)
                            LepFullCut_Z2EtaSep.Fill(abs(tmpLeadEta - tmpTrailingEta))
                    

        #FatJets loop
        tmpTagBoolAr = []
        for i in range(ev.nFatJet):
            tmpFatJetPT = ev.FatJet_pt[i]
            #FatJets with no tagging no cuts
            tmpFJEta = ev.FatJet_eta[i]
            tmpFJMass = ev.FatJet_mass[i]
            tmpFJPhi = ev.FatJet_phi[i]

            h_FatJet_eta.Fill(tmpFJEta)
            h_FatJet_mass.Fill(tmpFJMass)
            h_FatJet_phi.Fill(tmpFJPhi)
            h_FatJet_pt.Fill(tmpFatJetPT)

            #Fat Jets with tagging and no cuts
            tmpTagBoolAr.append([])
            tmpZVsQCD = ev.FatJet_deepTagMD_ZvsQCD[i]
            tmpWVsQCD = ev.FatJet_deepTagMD_WvsQCD[i]
            tmpHbbVsQCD = ev.FatJet_deepTagMD_HbbvsQCD[i]
            tmpH4qVsQCD = ev.FatJet_deepTagMD_H4qvsQCD[i]
            if tmpZVsQCD > tmpWVsQCD and tmpZVsQCD > tmpHbbVsQCD and tmpZVsQCD > tmpH4qVsQCD:
                for j,zCut in enumerate(cutOnZTagAr):
                    if tmpZVsQCD > zCut:
                        h_FatJet_etaZAr[j].Fill(tmpFJEta)
                        h_FatJet_ptZAr[j].Fill(tmpFatJetPT)
                        h_FatJet_massZAr[j].Fill(tmpFJMass)
                        h_FatJet_phiZAr[j].Fill(tmpFJPhi)
                        tmpTagBoolAr[-1].append(True)
                    else:
                        tmpTagBoolAr[-1].append(False)
        
        #Running a loop for cut jets with the tagging information
        for i in range(ev.nFatJet):
            #Fat Jets with cut but no tagging
            #Also Fat Jets with cuts and tagging
            if tmpFatJetPT > fatJetPTCut:
                #Counter
                if not ifOneFJBool:
                    ifOneFJCount += 1
                    ifOneFJBool = True
                #Looping through all jets past the current one
                for j in range(i+1,ev.nFatJet):
                    #Getting PT of the second jet
                    tmpFatJetPTTwo = ev.FatJet_pt[j]
                    #Checking if it passes the pt cut
                    if tmpFatJetPTTwo > fatJetPTCut:
                        #Counter
                        if not ifTwoFJBool:
                            ifTwoFJCount += 1
                            ifTwoFJBool = True
                        #Getting the eta dif between the two jets
                        tmpEtaDif = abs(ev.FatJet_eta[i]-ev.FatJet_eta[j])
                        #Checking if the eta dif passes the eta dif cut
                        if tmpEtaDif > jetEtaDifCut:
                            #Counter
                            if not ifThreeFJBool:
                                ifThreeFJCount += 1
                                ifThreeFJBool = True
                            #Getting four vectors for the two jets, using pt, eta, phi, and mass
                            tmpVecOne = Math.PtEtaPhiMVector(ev.FatJet_pt[i], ev.FatJet_eta[i], ev.FatJet_phi[i], ev.FatJet_mass[i])
                            tmpVecTwo = Math.PtEtaPhiMVector(ev.FatJet_pt[j], ev.FatJet_eta[j], ev.FatJet_phi[j], ev.FatJet_mass[j])
                            #Adding four vectors together and getting their invariant mass
                            tmpDiJetVec = tmpVecOne+tmpVecTwo
                            tmpFJInvMass = tmpDiJetVec.M()
                            #Checking if their InvMass passes the InvMass cut
                            if tmpFJInvMass > jetInvMassCut:
                                #Counter
                                if not ifFourFJBool:
                                    ifFourFJCount += 1
                                    ifFourFJBool = True
                                #Selecting on top jet pt first
                                tmpMaxPtLead = 0
                                tmpMaxPtSecond = 0
                                #Sorting which jet has the larger pt
                                if tmpFatJetPT > tmpFatJetPTTwo:
                                    tmpMaxPtLead = tmpFatJetPT
                                    tmpMaxPtSecond = tmpFatJetPTTwo
                                else:
                                    tmpMaxPtLead = tmpFatJetPTTwo
                                    tmpMaxPtSecond = tmpFatJetPT
                                #Selecting based on that jet's pt
                                if tmpMaxPtLead > leadFatJetMaxPT:
                                    leadFatJetMaxPT = tmpMaxPtLead
                                    secondFatJetMaxPT = tmpMaxPtSecond
                                    LFJOneInd = i
                                    LFJTwoInd = j
                                #If that jet is already part of the current selected pair,
                                #select based on the respective lower pt jets in the pairs
                                elif tmpMaxPtLead == leadFatJetMaxPT:
                                    if tmpMaxPtSecond > secondFatJetMaxPT:
                                        secondFatJetMaxPT = tmpMaxPtSecond
                                        LFJOneInd = i
                                        LFJTwoInd = j
                                #Selecting based on tagged jets
                                for l,cutBool in enumerate(tmpTagBoolAr[i]):
                                    if cutBool:
                                        if tmpMaxPtLead > leadFatJetTMaxPTAr[l]:
                                            for cutBoolSecond in tmpTagBoolAr[j]:
                                                if cutBoolSecond:
                                                    leadFatJetTMaxPTAr[l] = tmpMaxPtLead
                                                    secondFatJetTMaxPTAr[l] = tmpMaxPtSecond
                                                    LFJTOneIndAr[l] = i
                                                    LFJTTwoIndAr[l] = j
                                        elif tmpMaxPtLead == leadFatJetTMaxPTAr[l]:
                                            if tmpMaxPtSecond > secondFatJetTMaxPTAr[l]:
                                                for cutBoolSecond in tmpTagBoolAr[j]:
                                                    if cutBoolSecond:
                                                        secondFatJetTMaxPTAr[l] = tmpMaxPtSecond
                                                        LFJTOneIndAr[l] = i
                                                        LFJTTwoIndAr[l] = j
        #Filling histograms based on max jet pt in pair, with secondary jet pt as a tiebreaker
        #Checking that it didn't select the same jet for both parts of the pair 
        if LJOneInd != LJTwoInd:
            h_InitialFatJetAltLJ_Eta.Fill(ev.FatJet_eta[LFJOneInd])
            h_InitialFatJetAltLJ_Eta.Fill(ev.FatJet_eta[LFJTwoInd])
            h_InitialFatJetAltLJ_EtaSep.Fill(abs(ev.FatJet_eta[LFJOneInd]-ev.FatJet_eta[LFJTwoInd]))
            h_InitialFatJetAltLJ_pt.Fill(ev.FatJet_pt[LFJOneInd])
            h_InitialFatJetAltLJ_pt.Fill(ev.FatJet_pt[LFJTwoInd])
        for i,LFJTOneInd,LFJTTwoInd in zip(range(len(cutOnZTagAr)),LFJTOneIndAr,LFJTTwoIndAr):
            if LFJTOneInd != LFJTTwoInd:
                h_InitialFatJetAltLJ_EtaZAr[i].Fill(ev.FatJet_eta[LFJOneInd])
                h_InitialFatJetAltLJ_EtaZAr[i].Fill(ev.FatJet_eta[LFJTwoInd])
                h_InitialFatJetAltLJ_EtaSepZAr[i].Fill(abs(ev.FatJet_eta[LFJOneInd]-ev.FatJet_eta[LFJTwoInd]))
                h_InitialFatJetAltLJ_ptZAr[i].Fill(ev.FatJet_pt[LFJOneInd])
                h_InitialFatJetAltLJ_ptZAr[i].Fill(ev.FatJet_pt[LFJTwoInd])



        #Jets loop
        for i in range(ev.nJet):
            #Getting jet PT
            tmpJetPT = ev.Jet_pt[i]
            h_Jet_eta.Fill(ev.Jet_eta[i])
            h_Jet_mass.Fill(ev.Jet_mass[i])
            h_Jet_phi.Fill(ev.Jet_phi[i])
            h_Jet_pt.Fill(tmpJetPT)
            #Getting jet DeltaR from first outgoing quark
            tmpDeltaR = calcDeltaR(ev.Jet_phi[i],ev.Jet_eta[i],ev.GenPart_phi[5],ev.GenPart_eta[5])
            #Checking if it's less than the current lowest deltaR
            if tmpDeltaR < deltaRMinOne:
                deltaRMinOne = tmpDeltaR
                jOneInd = i
            #Checking again with the second outgoing quark
            tmpDeltaR = calcDeltaR(ev.Jet_phi[i],ev.Jet_eta[i],ev.GenPart_phi[6],ev.GenPart_eta[6])
            if tmpDeltaR < deltaRMinTwo:
                deltaRMinTwo = tmpDeltaR
                jTwoInd = i
            
            #Starting the matching based on cuts
            #Checking if the jet pt passes the pt cut
            if tmpJetPT > jetPTCut:
                #Counter
                if not ifOneBool:
                    ifOneCount += 1
                    ifOneBool = True
                #Looping through all jets past the current one
                for j in range(i+1,ev.nJet):
                    #Getting PT of the second jet
                    tmpJetPTTwo = ev.Jet_pt[j]
                    #Checking if it passes the pt cut
                    if tmpJetPTTwo > jetPTCut:
                        #Counter
                        if not ifTwoBool:
                            ifTwoCount += 1
                            ifTwoBool = True
                        #Getting the eta dif between the two jets
                        tmpEtaDif = abs(ev.Jet_eta[i]-ev.Jet_eta[j])
                        #Checking if the eta dif passes the eta dif cut
                        if tmpEtaDif > jetEtaDifCut:
                            #Counter
                            if not ifThreeBool:
                                ifThreeCount += 1
                                ifThreeBool = True
                            #Getting four vectors for the two jets, using pt, eta, phi, and mass
                            tmpVecOne = Math.PtEtaPhiMVector(ev.Jet_pt[i], ev.Jet_eta[i], ev.Jet_phi[i], ev.Jet_mass[i])
                            tmpVecTwo = Math.PtEtaPhiMVector(ev.Jet_pt[j], ev.Jet_eta[j], ev.Jet_phi[j], ev.Jet_mass[j])
                            #Adding four vectors together and getting their invariant mass
                            tmpDiJetVec = tmpVecOne+tmpVecTwo
                            tmpInvMass = tmpDiJetVec.M()
                            #Checking if their InvMass passes the InvMass cut
                            if tmpInvMass > jetInvMassCut:
                                #Counter
                                if not ifFourBool:
                                    ifFourCount += 1
                                    ifFourBool = True
                                
                                #Selecting by summed jet pt
                                tmpDiJetPT = tmpJetPT+tmpJetPTTwo
                                if tmpDiJetPT > diJetMaxPT:
                                    diJetMaxPT = tmpDiJetPT
                                    ptOneInd = i
                                    ptTwoInd = j
                                #Selecting by diJet inv mass
                                if tmpInvMass > diJetMaxInvMass:
                                    diJetMaxInvMass = tmpInvMass
                                    invMassOneInd = i
                                    invMassTwoInd = j
                                #Selecting on top jet pt first
                                tmpMaxPtLead = 0
                                tmpMaxPtSecond = 0
                                #Sorting which jet has the larger pt
                                if tmpJetPT > tmpJetPTTwo:
                                    tmpMaxPtLead = tmpJetPT
                                    tmpMaxPtSecond = tmpJetPTTwo
                                else:
                                    tmpMaxPtLead = tmpJetPTTwo
                                    tmpMaxPtSecond = tmpJetPT
                                #Selecting based on that jet's pt
                                if tmpMaxPtLead > leadJetMaxPT:
                                    leadJetMaxPT = tmpMaxPtLead
                                    secondJetMaxPT = tmpMaxPtSecond
                                    LJOneInd = i
                                    LJTwoInd = j
                                #If that jet is already part of the current selected pair,
                                #select based on the respective lower pt jets in the pairs
                                elif tmpMaxPtLead == leadJetMaxPT:
                                    if tmpMaxPtSecond > secondJetMaxPT:
                                        secondJetMaxPT = tmpMaxPtSecond
                                        LJOneInd = i
                                        LJTwoInd = j

        #Filling jet matching with cuts histos:
        #Filling histograms based on summed jet pt
        #Checking that it didn't select the same jet for both parts of the pair                    
        if ptOneInd != ptTwoInd:
            h_InitialJetAlt_Eta.Fill(ev.Jet_eta[ptOneInd])
            h_InitialJetAlt_Eta.Fill(ev.Jet_eta[ptTwoInd])
            h_InitialJetAlt_EtaSep.Fill(abs(ev.Jet_eta[ptOneInd]-ev.Jet_eta[ptTwoInd]))
            h_InitialJetAlt_pt.Fill(ev.Jet_pt[ptOneInd])
            h_InitialJetAlt_pt.Fill(ev.Jet_pt[ptTwoInd])
            #print(evCount,i,deltaRMinOne,deltaRMinTwo,jOneInd,jTwoInd)
        #Filling histograms based on diJet invMass
        #Checking that it didn't select the same jet for both parts of the pair 
        if invMassOneInd != invMassTwoInd:
            h_InitialJetAltIM_Eta.Fill(ev.Jet_eta[invMassOneInd])
            h_InitialJetAltIM_Eta.Fill(ev.Jet_eta[invMassTwoInd])
            h_InitialJetAltIM_EtaSep.Fill(abs(ev.Jet_eta[invMassOneInd]-ev.Jet_eta[invMassTwoInd]))
            h_InitialJetAltIM_pt.Fill(ev.Jet_pt[invMassOneInd])
            h_InitialJetAltIM_pt.Fill(ev.Jet_pt[invMassTwoInd])
            #print(evCount,i,deltaRMinOne,deltaRMinTwo,jOneInd,jTwoInd)
        #Filling histograms based on max jet pt in pair, with secondary jet pt as a tiebreaker
        #Checking that it didn't select the same jet for both parts of the pair 
        if LJOneInd != LJTwoInd:
            h_InitialJetAltLJ_Eta.Fill(ev.Jet_eta[LJOneInd])
            h_InitialJetAltLJ_Eta.Fill(ev.Jet_eta[LJTwoInd])
            h_InitialJetAltLJ_EtaSep.Fill(abs(ev.Jet_eta[LJOneInd]-ev.Jet_eta[LJTwoInd]))
            h_InitialJetAltLJ_pt.Fill(ev.Jet_pt[LJOneInd])
            h_InitialJetAltLJ_pt.Fill(ev.Jet_pt[LJTwoInd])
            #print(evCount,i,deltaRMinOne,deltaRMinTwo,jOneInd,jTwoInd)

        #Filling gen matching histos:
        #Checking that we were actually looking at the outgoing quarks when gen matching
        #Note: should change this to just check at the start and be more flexible with the quark position
        #(i.e. check more than just [5] and [6])
        if abs(ev.GenPart_pdgId[5])>10 or abs(ev.GenPart_pdgId[6])>10:
            #Incrementing counter if not
            noOutCount += 1
        #Checking that the DeltaRs for both jets are small enough
        elif deltaRMinOne > 0.4 or deltaRMinTwo > 0.4:
            #Incrementing counter if not
            noMatchCount +=1
        #Checking that it didn't select the same jet for both parts of the pair 
        elif jOneInd == jTwoInd:
            #If so, then print out what happened (rare)
            print("uhoh",str(jOneInd),str(jTwoInd),evCount,ev.GenPart_pdgId[5],ev.GenPart_pdgId[6],deltaRMinOne,deltaRMinTwo)
        #If it passes all the checks above, fill the gen matching histograms    
        else:
            h_InitialJet_Eta.Fill(ev.Jet_eta[jOneInd])
            h_InitialJet_Eta.Fill(ev.Jet_eta[jTwoInd])
            h_InitialJet_EtaSep.Fill(abs(ev.Jet_eta[jOneInd]-ev.Jet_eta[jTwoInd]))
            h_InitialJet_pt.Fill(ev.Jet_pt[jOneInd])
            h_InitialJet_pt.Fill(ev.Jet_pt[jTwoInd])
        #Increment event count
        evCount += 1

print("Finished file loop.","time:",time.time()-startt)
#Printing out different counters:
#Counters for problems during jet matching:
print("Number of events with no matching jet:",noMatchCount)
print("Number of events with wrong out:",noOutCount)
#Counters for how many events passed each cut:
print("Number of events with one Jet pt > ",jetPTCut,"-",ifOneCount)
print("Number of events with Two Jet pt > ",jetPTCut,"-",ifTwoCount)
print("Number of events with jet pair etaDif >",jetEtaDifCut,"-",ifThreeCount)
print("Number of events with jet pair inv mass >",jetInvMassCut,"-",ifFourCount)
print("----------------------------------------------------------")
print("Number of events with at least one electron candidate pair:",ifEnoughElecCandCount)
print("Number of events with at least one muon candidate pair:",ifEnoughMuonCandCount)
print("Number of events with at least one Z1 electron pair:",ifZ1ElecPairCandCount)
print("Number of events with at least one Z1 muon pair:",ifZ1MuonPairCandCount)
print("Number of events with at least one Z2 Electron pair:",ifZ2ElecPairCandCount)
print("Number of events with at least one Z2 Muon pair:",ifZ2MuonPairCandCount)
print("Number of events with at least one Z1Z2 pair passing iso cuts:",passesIsoCutsCount)
print("Number of events with at least one Z1Z2 pair passing SIP cuts:",passesSIPCutCount)
print("Number of events with at least one Z1Z2 pair passing all cuts:",allCutPassCount)
print("----------------------------------------------------------")
print("Cross section average before division:",crossSectionAvg)
print("Cross section counter:",crossSectionCtr)
crossSectionAvg = crossSectionAvg / crossSectionCtr
print("Cross section average after division:",crossSectionAvg)

#Setting up outfile for histograms
outFile = TFile("histosFromNanoAOD{0}.root".format(saveName),"recreate")

print("Drawing plots.","time:",time.time()-startt)
#General stuff:
DrawPlot(h_CaloMET_phi, "h_CaloMET_phi_",saveName,True)
DrawPlot(h_CaloMET_pt, "h_CaloMET_pt_",saveName,True)
DrawPlot(h_CaloMET_sumEt, "h_CaloMET_sumEt_",saveName,True)

DrawPlot(h_Electron_eta,"h_Electron_eta_",saveName,True)
DrawPlot(h_Electron_hoe,"h_Electron_hoe_",saveName,True)
DrawPlot(h_Electron_mass,"h_Electron_mass_",saveName,True)
DrawPlot(h_Electron_phi,"h_Electron_phi_",saveName,True)
DrawPlot(h_Electron_pt,"h_Electron_pt_",saveName,True)
DrawPlot(h_Electron_r9,"h_Electron_r9_",saveName,True)
DrawPlot(h_Electron_sieie,"h_Electron_sieie_",saveName,True)

DrawPlot(h_Muon_eta,"h_Muon_eta_",saveName,True)
DrawPlot(h_Muon_mass,"h_Muon_mass_",saveName,True)
DrawPlot(h_Muon_phi,"h_Muon_phi_",saveName,True)
DrawPlot(h_Muon_pt,"h_Muon_pt_",saveName,True)

#Cut Leptons
DrawPlot(LepFullCut_Z1Leadpt,"LepFullCut_Z1Leadpt",saveName,True)
DrawPlot(LepFullCut_Z1Trailingpt,"LepFullCut_Z1Trailingpt",saveName,True)
DrawPlot(LepFullCut_Z1Leadeta,"LepFullCut_Z1Leadeta",saveName,True)
DrawPlot(LepFullCut_Z1Trailingeta,"LepFullCut_Z1Trailingeta",saveName,True)

DrawPlot(LepFullCut_Z1Leadmass,"LepFullCut_Z1Leadmass",saveName,True)
DrawPlot(LepFullCut_Z1Trailingmass,"LepFullCut_Z1Trailingmass",saveName,True)
DrawPlot(LepFullCut_Z1Leadphi,"LepFullCut_Z1Leadphi",saveName,True)
DrawPlot(LepFullCut_Z1Trailingphi,"LepFullCut_Z1Trailingphi",saveName,True)

DrawPlot(LepFullCut_Z1InvMass,"LepFullCut_Z1InvMass",saveName,True)
DrawPlot(LepFullCut_Z1EtaSep,"LepFullCut_Z1EtaSep",saveName,True)


DrawPlot(LepFullCut_Z2Leadpt,"LepFullCut_Z2Leadpt",saveName,True)
DrawPlot(LepFullCut_Z2Trailingpt,"LepFullCut_Z2Trailingpt",saveName,True)
DrawPlot(LepFullCut_Z2Leadmass,"LepFullCut_Z2Leadmass",saveName,True)
DrawPlot(LepFullCut_Z2Trailingmass,"LepFullCut_Z2Trailingmass",saveName,True)
DrawPlot(LepFullCut_Z2Leadphi,"LepFullCut_Z2Leadphi",saveName,True)
DrawPlot(LepFullCut_Z2Trailingphi,"LepFullCut_Z2Trailingphi",saveName,True)

    
DrawPlot(LepFullCut_Z2Leadeta,"LepFullCut_Z2Leadeta",saveName,True)
DrawPlot(LepFullCut_Z2Trailingeta,"LepFullCut_Z2Trailingeta",saveName,True)
DrawPlot(LepFullCut_Z2InvMass,"LepFullCut_Z2InvMass",saveName,True)
DrawPlot(LepFullCut_Z2EtaSep,"LepFullCut_Z2EtaSep",saveName,True)

#Jets:
DrawPlot(h_Jet_eta,"h_Jet_eta_",saveName,True)
DrawPlot(h_Jet_mass,"h_Jet_mass_",saveName,True)
DrawPlot(h_Jet_phi,"h_Jet_phi_",saveName,True)
DrawPlot(h_Jet_pt,"h_Jet_pt_",saveName,True)
DrawPlot(h_nJet,"h_nJet_",saveName,True)
DrawPlot(h_nFatJet,"h_nFatJet_",saveName,True)

#Gen matched jets:
DrawPlot(h_InitialJet_Eta,"h_InitialJet_Eta_",saveName,True)
DrawPlot(h_InitialJet_EtaSep,"h_InitialJet_EtaSep_",saveName,True)
DrawPlot(h_InitialJet_pt,"h_InitialJet_pt_",saveName,True)

#Jet matching with Cuts:
#summed pt cut
DrawPlot(h_InitialJetAlt_Eta,"h_InitialJetAlt_Eta_",saveName,True)
DrawPlot(h_InitialJetAlt_EtaSep,"h_InitialJetAlt_EtaSep_",saveName,True)
DrawPlot(h_InitialJetAlt_pt,"h_InitialJetAlt_pt_",saveName,True)
#InvMass cut
DrawPlot(h_InitialJetAltIM_Eta,"h_InitialJetAltIM_Eta_",saveName,True)
DrawPlot(h_InitialJetAltIM_EtaSep,"h_InitialJetAltIM_EtaSep_",saveName,True)
DrawPlot(h_InitialJetAltIM_pt,"h_InitialJetAltIM_pt_",saveName,True)
#Max jet pt cut
DrawPlot(h_InitialJetAltLJ_Eta,"h_InitialJetAltLJ_Eta_",saveName,True)
DrawPlot(h_InitialJetAltLJ_EtaSep,"h_InitialJetAltLJ_EtaSep_",saveName,True)
DrawPlot(h_InitialJetAltLJ_pt,"h_InitialJetAltLJ_pt_",saveName,True)

DrawPlot(h_LHEWeight,"h_LHEWeight_",saveName,False)



print("Done.","time:",time.time()-startt)


