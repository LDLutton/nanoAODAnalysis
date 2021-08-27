from ROOT import TFile, TChain, gDirectory, TApplication, TMath, Math, TMinuit, TROOT, TSystem, TTree, TVector2,TObject
# You probably also want to import TH1D and TCanvas,
# unless you're not making any histograms.
from ROOT import TH1F, TCanvas, TF1, TGraph, TGraphErrors, TLegend, TLine, TPaveText, TStyle
from ROOT import TH2D, TH2F
from math import sqrt,pi
from fileLists import MGEFTAr
from fileLists import MGSMAr
from array import array
import numpy as np

#Background
from fileLists import ttHToBBBackgroundAr
from fileLists import ttZJetsBackgroundAr
from fileLists import DYBackgroundAr
from fileLists import QCDPT170to300BackgroundAr
from fileLists import QCDPT300to470BackgroundAr
from fileLists import QCDPT470to600BackgroundAr
from fileLists import QCDPT600to800BackgroundAr
from fileLists import QCDPT800to1000BackgroundAr
from fileLists import QCDPT1000to1400BackgroundAr
from fileLists import QCDPT1400to1800BackgroundAr
from fileLists import QCDPT1800to2400BackgroundAr
from fileLists import QCDPT2400to3200BackgroundAr
from fileLists import QCDPT3200toInfBackgroundAr

import time as time

#To enable heavy printing for debug
debug = False
debugChannelSort = False
#To break out of loops after NToEnd events
endAfter = False
NToStart = 0
NToEnd = 2500

###########


###########

#withDipoleRecoil = True

testRun = True
MGSM = False
MGEFT = False
ttHToBBBackground = False
ttZJetsBackground = False
DYBackground = False
QCDPT170to300Background = False
QCDPT300to470Background = False
QCDPT470to600Background = False
QCDPT600to800Background = False
QCDPT800to1000Background = False
QCDPT1000to1400Background = False
QCDPT1400to1800Background = False
QCDPT1800to2400Background = False
QCDPT2400to3200Background = False
QCDPT3200toInfBackground = False


isBackground = False

#For drawing and saving histograms
#Saves a png and, optionally, a pdf version
#Saves histogram to the currently active root file

#Defining Lepton cuts
firstZLeadingCut = 20
firstZTrailingCut = 10
ZMass = 91.1876
leptonInvMassCutLow = 60
leptonInvMassCutHigh = 120
leptonInvMassCutTwo = 12
fourLeptonInvMassCut = 100
leptonZ2CutLow = 60
leptonZ2CutHigh = 120
elecCandEtaCut =  2.5
elecCandPTCut = 7
muonCandEtaCut =  2.4
muonCandPTCut = 5
lepIsoCut = 0.35

def DrawPlot(plot,name,saveName,normalizeOrNot,COLZOrNot = False):
    if normalizeOrNot and plot.GetEntries() > 0:
        c1 = TCanvas("c1","c1",3600,2400)

        plot.SetFillColorAlpha(30,0.35)
        if not COLZOrNot:
            plot.Draw("hist")
        else:
            plot.Draw("COLZ")
        c1.SaveAs((name+"{0}.png".format(saveName)))
        plot.Write(name)
        intOfPlot = plot.Integral()
        if intOfPlot != 0:
            plot.Scale(1.0 / intOfPlot)
        else:
            print("intOfPlot == 0. Just remaking histogram for the 'normalized' one")
        if not COLZOrNot:
            plot.Draw("hist")
        else:
            plot.Draw("COLZ")
        c1.SaveAs((name+"{0}Normalized.png".format(saveName)))
        #c1.SaveAs((name+"{0}.pdf".format(saveName)))
        plot.Write(name+"Normalized")
    else:
        print(name,"has no entries. Adding empty histograms")
        c1 = TCanvas()
        plot.Draw("hist")
        plot.Write(name)
        plot.Write(name+"Normalized")


def checkForElecCands(ev,nElectronInt,elecCandIndAr):
    nElecCandidatesNeg = 0
    nElecCandidatesPos = 0
    for i in range(nElectronInt):
        if debug:
            print(evCount,"ev.Electron_eta[i]",ev.Electron_eta[i],"ev.Electron_pt[i]",ev.Electron_pt[i],"ev.Electron_charge[i]",ev.Electron_charge[i],"ev.Electron_mass[i]",ev.Electron_mass[i])
        #Checking for electron candidates with the initial eta and pt cuts. Keeping track of whether there is a negative and/or a positive electron present
        if abs(ev.Electron_eta[i]) < elecCandEtaCut and ev.Electron_pt[i] > elecCandPTCut:
            elecCandIndAr.append(i)
            if ev.Electron_charge[i] == -1:
                #elecHasNeg = True
                nElecCandidatesNeg += 1
            else:
                #elecHasPos = True
                nElecCandidatesPos += 1
    nElecCandPairs = 0
    if nElecCandidatesNeg <= nElecCandidatesPos:
        nElecCandPairs = nElecCandidatesNeg
    else:
        nElecCandPairs = nElecCandidatesPos
    if debug:
        print("nElecCandidatesNeg",nElecCandidatesNeg,"nElecCandidatesPos",nElecCandidatesPos,"nElecCandPairs",nElecCandPairs)
        
    return nElecCandPairs

def checkForMuonCands(ev,nMuonInt,muonCandIndAr):
    nMuonCandidatesNeg = 0
    nMuonCandidatesPos = 0
    #Loop over muons
    for i in range(nMuonInt):
        if debug:
            print("ev.Muon_eta[i]",ev.Muon_eta[i],"ev.Muon_pt[i]",ev.Muon_pt[i],"ev.Muon_charge[i]",ev.Muon_charge[i])
        #Checking for muon candidates with the initial eta and pt cuts. Keeping track of whether there is a negative and/or a positive muon present
        if abs(ev.Muon_eta[i]) < muonCandEtaCut and ev.Muon_pt[i] > muonCandPTCut:
            muonCandIndAr.append(i)
            if ev.Muon_charge[i] == -1:
                #muonHasNeg = True
                nMuonCandidatesNeg += 1
            else:
                #muonHasPos = True
                nMuonCandidatesPos += 1
    nMuonCandPairs = 0
    if nMuonCandidatesNeg <= nMuonCandidatesPos:
        nMuonCandPairs = nMuonCandidatesNeg
    else:
        nMuonCandPairs = nMuonCandidatesPos
    if debug:
        print("nMuonCandidatesNeg",nMuonCandidatesNeg,"nMuonCandidatesPos",nMuonCandidatesPos,"nMuonCandPairs",nMuonCandPairs)
    return nMuonCandPairs

def checkForLepCands(nElecCandPairs,nMuonCandPairs):
    enoughElecCands = False
    enoughMuonCands = False
    enoughLepCands = False
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
    return (enoughElecCands,enoughMuonCands,enoughLepCands)

def checkForElecPair(ev,i,tmpnElectron,elecCandIndAr,elecPassesZ2CutsAr,elecPassesCutsAr,difFromZMassOne,lepPairOneLeadInd,lepPairOneTrailingInd,leadLepPairOneVec,trailingLepPairOneVec,leadLepPairCharge,trailingLepPairCharge):
    for tmpjElecItr,j in enumerate(elecCandIndAr[i+1:]):
        if debug:
            print("Second Electron",j)
        #Check that the electrons have the opposite charge
        tmpElecCharge = ev.Electron_charge[i]
        tmpElecChargeTwo = ev.Electron_charge[j]
        if tmpElecCharge == - tmpElecChargeTwo:
            if debug:
                print(i,j,"Electrons have the opposite charge")
            #Get variables from second electron
            tmpPtTwo = ev.Electron_pt[j]

            tmpEtaTwo = ev.Electron_eta[j]
            tmpMassTwo = ev.Electron_mass[j]
            if debug:
                print(i,j,"ev.Electron_mass",tmpMassOne,tmpMassTwo)
            
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
            
            tmpDiElectronVec = tmpLeadVec+tmpTrailingVec
            tmpDiElectronInvMass = tmpDiElectronVec.M()
            if debug:
                print(i,j,"tmpLeadInd",tmpLeadInd,"tmpSecondInd",tmpSecondInd,"tmpMaxPtLead",tmpMaxPtLead,"tmpMaxPtSecond",tmpMaxPtSecond,"tmpLeadCharge",tmpLeadCharge,"tmpTrailingCharge",tmpTrailingCharge)
            if debug:
                print("tmpDiElectronInvMass",tmpDiElectronInvMass)
            if tmpDiElectronInvMass > leptonZ2CutLow and tmpDiElectronInvMass < leptonZ2CutHigh:
                if debug:
                    print(i,j,"Electron pair passed invmass Z2 cut",leptonZ2CutLow,leptonZ2CutHigh)
                elecPassesZ2CutsAr.append([[tmpLeadInd,tmpSecondInd],[tmpLeadVec,tmpTrailingVec],[tmpLeadCharge,tmpTrailingCharge]])
            #Check that the pt of the second electron passes the lower pt cut
            if tmpPtTwo > firstZTrailingCut:
                if debug:
                    print(i,j,"Second electron pt passed Z1 trailing cut",firstZTrailingCut)
                #Sort the electrons into leading and trailing based on pt
                #Actually get these earlier

                #Check that the lead electron passes the higher pt cut
                if tmpMaxPtLead > firstZLeadingCut:
                    if debug:
                        print(i,j,"Electron lead pt passed Z1 lead cut",firstZLeadingCut)
                    
                    #Check that invmass passes the Cut
                    if tmpDiElectronInvMass > leptonInvMassCutLow and tmpDiElectronInvMass < leptonInvMassCutHigh:
                        if debug:
                            print(i,j,"Electron pair passed Z1 inv mass cut",leptonInvMassCutLow)
                        elecPassesCutsAr.append([tmpLeadInd,tmpSecondInd])
                        #Check if the mass is closer to Z than current candidate
                        tmpDifFromZMass = abs(tmpDiElectronInvMass-ZMass)
                        #Switching over variables
                        if debug:
                            print(i,j,"tmpDifFromZMass",tmpDifFromZMass)
                        if tmpDifFromZMass < difFromZMassOne:
                            if debug:
                                print(i,j,"Electron pair has lowest current dif from Zmass. Old ZMassdif:",difFromZMassOne)
                            #Switching ZMassDif
                            difFromZMassOne = tmpDifFromZMass
                            #Switching pair indices
                            lepPairOneLeadInd = tmpLeadInd
                            lepPairOneTrailingInd = tmpSecondInd
                            #Switching 4 vectors
                            leadLepPairOneVec = tmpLeadVec
                            trailingLepPairOneVec = tmpTrailingVec
                            leadLepPairCharge = tmpLeadCharge
                            trailingLepPairCharge = tmpTrailingCharge
    return (difFromZMassOne,lepPairOneLeadInd,lepPairOneTrailingInd,leadLepPairOneVec,trailingLepPairOneVec,leadLepPairCharge,trailingLepPairCharge)

def checkForMuonPair(ev,i,tmpnMuon,muonCandIndAr,muonPassesZ2CutsAr,muonPassesCutsAr,difFromZMassOne,lepPairOneLeadInd,lepPairOneTrailingInd,leadLepPairOneVec,trailingLepPairOneVec,leadLepPairCharge,trailingLepPairCharge,muonLeading):
    for tmpjMuonItr,j in enumerate(muonCandIndAr[i+1:]):
        if debug:
            print("Second Muon",j)
        #Check that muons have the opposite charge
        tmpMuonCharge = ev.Muon_charge[i]
        tmpMuonChargeTwo = ev.Muon_charge[j]
        if tmpMuonCharge == - tmpMuonChargeTwo:
            if debug:
                print(i,j,"Muons have the opposite charge")
            #Get vaariables from second electron
            tmpPtTwo = ev.Muon_pt[j]
            tmpEtaTwo = ev.Muon_eta[j]
            if debug:
                print(i,j,"ev.Muon_mass",ev.Muon_mass[i],ev.Muon_mass[j])
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
            tmpDiMuonVec = tmpLeadVec+tmpTrailingVec
            tmpDiMuonInvMass = tmpDiMuonVec.M()
            if debug:
                print(i,j,"tmpLeadInd",tmpLeadInd,"tmpSecondInd",tmpSecondInd,"tmpMaxPtLead",tmpMaxPtLead,"tmpMaxPtSecond",tmpMaxPtSecond,"tmpLeadCharge",tmpLeadCharge,"tmpTrailingCharge",tmpTrailingCharge)
            if debug:
                print("tmpDiMuonInvMass",tmpDiMuonInvMass)
            if tmpDiMuonInvMass > leptonZ2CutLow and tmpDiMuonInvMass < leptonZ2CutHigh:
                if debug:
                    print(i,j,"Muon pair passed invmass Z2 cut",leptonZ2CutLow,leptonZ2CutHigh)
                muonPassesZ2CutsAr.append([[tmpLeadInd,tmpSecondInd],[tmpLeadVec,tmpTrailingVec],[tmpLeadCharge,tmpTrailingCharge]])
            
            #Check that the pt of the second muon passes the lower pt cut
            if tmpPtTwo > firstZTrailingCut:
                if debug:
                    print(i,j,"Muon trailing pt passed Z1 trailing cut",firstZTrailingCut)
                #Sort the muons into leading and trailing based on pt
                #Check that the lead muon passes the higher pt cut
                if tmpMaxPtLead > firstZLeadingCut:
                    if debug:
                        print(i,j,"Muon lead pt passed Z1 lead cut",firstZLeadingCut)
                    #Check that invmass passes the Cut
                    if tmpDiMuonInvMass > leptonInvMassCutLow and tmpDiMuonInvMass < leptonInvMassCutHigh:
                        if debug:
                            print(i,j,"Muon pair passed Z1 inv mass cut",leptonInvMassCutLow)

                        muonPassesCutsAr.append([tmpLeadInd,tmpSecondInd])
                        #Check if the mass is closer to Z than current candidate
                        tmpDifFromZMass = abs(tmpDiMuonInvMass-ZMass)
                        #Switching over variables
                        if debug:
                            print(i,j,"tmpDifFromZMass",tmpDifFromZMass)
                        if tmpDifFromZMass < difFromZMassOne:
                            if debug:
                                print(i,j,"Muon pair has lowest current dif from Zmass. Old ZMassdif:",difFromZMassOne)
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
    return (difFromZMassOne,lepPairOneLeadInd,lepPairOneTrailingInd,leadLepPairOneVec,trailingLepPairOneVec,leadLepPairCharge,trailingLepPairCharge,muonLeading)

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
    for fileName in MGEFTAr:
        fileAr.append("/scratch365/dlutton/NanoAODFiles/pphzzjjQCD0SMHLOOP0NPE1NPcHWE1QEDE5ResMasAllVer100Ev_0p999cHW100GeVIMJetCut/"+fileName)
elif MGSM:
    saveName = "pphzzjjQCD0SMHLOOP0QEDE5NPE0ResMasAllVer100Ev_0p999cHW100GeVIMJetCut"
    for fileName in MGSMAr:
        fileAr.append("/scratch365/dlutton/NanoAODFiles/pphzzjjQCD0SMHLOOP0QEDE5NPE0ResMasAllVer100Ev_0p999cHW100GeVIMJetCut/"+fileName)
elif ttHToBBBackground:
    saveName = "ttHToBBBackground"
    
    crossSection = 0.6*0.584
    
    isBackground = True
    for fileName in ttHToBBBackgroundAr:
        fileAr.append(fileName)
elif ttZJetsBackground:
    saveName = "ttZJetsBackground"
    
    crossSection = 0.5407
    
    isBackground = True
    for fileName in ttZJetsBackgroundAr:
        fileAr.append(fileName)
elif DYBackground:
    saveName = "DYBackground"
    
    crossSection = 6077.22
    
    isBackground = True
    for fileName in DYBackgroundAr:
        fileAr.append(fileName)
elif QCDPT170to300Background:
    saveName = "QCDPT170to300Background"
    
    crossSection = 103300.0
    
    isBackground = True
    for fileName in QCDPT170to300BackgroundAr:
        fileAr.append(fileName)
elif QCDPT300to470Background:
    saveName = "QCDPT300to470Background"
    
    crossSection = 6826.0
    
    isBackground = True
    for fileName in QCDPT300to470BackgroundAr:
        fileAr.append(fileName)
elif QCDPT470to600Background:
    saveName = "QCDPT470to600Background"
    
    crossSection = 552.6
    
    isBackground = True
    for fileName in QCDPT470to600BackgroundAr:
        fileAr.append(fileName)
elif QCDPT600to800Background:
    saveName = "QCDPT600to800Background"
    
    crossSection = 156.6
    
    isBackground = True
    for fileName in QCDPT600to800BackgroundAr:
        fileAr.append(fileName)
elif QCDPT800to1000Background:
    saveName = "QCDPT800to1000Background"
    
    crossSection = 26.32
    
    isBackground = True
    for fileName in QCDPT800to1000BackgroundAr:
        fileAr.append(fileName)
elif QCDPT1000to1400Background:
    saveName = "QCDPT1000to1400Background"
    
    crossSection = 7.5
    
    isBackground = True
    for fileName in QCDPT1000to1400BackgroundAr:
        fileAr.append(fileName)
elif QCDPT1400to1800Background:
    saveName = "QCDPT1400to1800Background"
    
    crossSection = 0.6479
    
    isBackground = True
    for fileName in QCDPT1400to1800BackgroundAr:
        fileAr.append(fileName)
elif QCDPT1800to2400Background:
    saveName = "QCDPT1800to2400Background"
    
    crossSection = 0.08715
    
    isBackground = True
    for fileName in QCDPT1800to2400BackgroundAr:
        fileAr.append(fileName)
elif QCDPT2400to3200Background:
    saveName = "QCDPT2400to3200Background"
    
    crossSection = 0.005242
    
    isBackground = True
    for fileName in QCDPT2400to3200BackgroundAr:
        fileAr.append(fileName)
elif QCDPT3200toInfBackground:
    saveName = "QCDPT3200toInfBackground"
    
    crossSection = 0.0001349
    
    isBackground = True
    for fileName in QCDPT3200toInfBackgroundAr:
        fileAr.append(fileName)
elif testRun:
    saveName = "testRun"
    fileAr.append("./unweighted_eventspphzzjjQCD0SMHLOOP0NPE1NPcHWE1QEDE5ResMasAllVer100Ev10080Seed_0p999cHW100GeVIMJetCut_200.root")






#Initializing counter variables
evCount = 0

#Setting up outfile for tree
outFile = TFile("FoMTreesFrom{0}.root".format(saveName),"recreate")

#Initial with no cuts. Information needed:
#Electron/Muon eta, Pt, and the HLT triggers

neLep = array('i',[0])
eEta = array('f',[0.])
ePt = array('f',[0.])
eHLT = array('B',[0])

nmLep = array('i',[0])
mEta = array('f',[0.])
mPt = array('f',[0.])
mHLT = array('B',[0])

emHLT = array('B',[0])



cutZeroTree = TTree('cutZeroTree', 'cutZeroTree')

cutZeroTree.Branch("neLep",neLep,"neLep/I")
cutZeroTree.Branch("eEta",eEta,"eEta[neLep]/F")
cutZeroTree.Branch("ePt",ePt,"ePt[neLep]/F")
cutZeroTree.Branch("eHLT",eHLT,"eHLT/O")
cutZeroTree.Branch("nmLep",nmLep,"nmLep/I")
cutZeroTree.Branch("mEta",mEta,"mEta[nmLep]/F")
cutZeroTree.Branch("mPt",mPt,"mPt[nmLep]/F")
cutZeroTree.Branch("mHLT",mHLT,"mHLT/O")

cutZeroTree.Branch("emHLT",emHLT,"emHLT/O")

#After establishing lepton candidates. Information needed:
#Electron/Muon charge, eta, phi, pt, and mass
neC1Lep = array('i',[0])
eC1Charge = array('i',[0])
eC1Eta = array('f',[0.])
eC1Phi = array('f',[0.])
eC1Pt = array('f',[0.])
eC1Mass = array('f',[0.])
nmC1Lep = array('i',[0])
mC1Charge = array('i',[0])
mC1Eta = array('f',[0.])
mC1Phi = array('f',[0.])
mC1Pt = array('f',[0.])
mC1Mass = array('f',[0.])

cutOneTree = TTree('cutOneTree', 'cutOneTree')
cutOneTree.Branch("neC1Lep",neC1Lep,"neC1Lep/I")
cutOneTree.Branch("eC1Charge",eC1Charge,"eC1Charge[neC1Lep]/I")
cutOneTree.Branch("eC1Eta",eC1Eta,"eC1Eta[neC1Lep]/F")
cutOneTree.Branch("eC1Phi",eC1Phi,"eC1Phi[neC1Lep]/F")
cutOneTree.Branch("eC1Pt",eC1Pt,"eC1Pt[neC1Lep]/F")
cutOneTree.Branch("eC1Mass",eC1Mass,"eC1Mass[neC1Lep]/F")
cutOneTree.Branch("nmC1Lep",nmC1Lep,"nmC1Lep/I")
cutOneTree.Branch("mC1Charge",mC1Charge,"mC1Charge[nmC1Lep]/I")
cutOneTree.Branch("mC1Eta",mC1Eta,"mC1Eta[nmC1Lep]/F")
cutOneTree.Branch("mC1Phi",mC1Phi,"mC1Phi[nmC1Lep]/F")
cutOneTree.Branch("mC1Pt",mC1Pt,"mC1Pt[nmC1Lep]/F")
cutOneTree.Branch("mC1Mass",mC1Mass,"mC1Mass[nmC1Lep]/F")





###############
"""
treeThree = TTree("validThree", "An Example TreeThree")
tmpLenA = 1
nThreeA = np.array([tmpLenA],dtype=np.uint32)
ptThreeA = np.zeros((tmpLenA,2),dtype=np.float32)

treeThree.Branch("nThreeA",nThreeA,"nThreeA/I")
treeThree.Branch("ptThreeA",ptThreeA,"ptThreeA[nThreeA][2]/F")


tmpLenA = 2
nThreeA[0] = tmpLenA
ptThreeA = np.zeros((tmpLenA,2),dtype=np.float32)

ptThreeA[0][0] = 1.2
ptThreeA[0][1] = 4.3
ptThreeA[1][0] = .5
ptThreeA[1][1] = -3.1

treeThree.SetBranchAddress("ptThreeA",ptThreeA)

treeThree.Fill()



cutTestTree = TTree('cutTestTree','cutTestTree')
nTest = np.array([0],dtype=np.uint32) #array('i',[0])
testF = np.zeros((0,0),dtype=np.float32) #array('f',[0.])
cutTestTree.Branch("nTest",nTest,"nTest/I")
cutTestTree.Branch("testF",testF,"testF[nTest][2]/F")
"""
###############


cutTwoTree = TTree('cutTwoTree', 'cutTwoTree')

#After getting first lepton pair. Information needed:
#Same as last cut, but don't add the leptons that form the pair
nZ1C2Lep = array('i',[0])
Z1C2Charge = array('i',[0])
Z1C2Flav = array('i',[0])
Z1C2Eta = array('f',[0.])
Z1C2Phi = array('f',[0.])
Z1C2Pt = array('f',[0.])
Z1C2Mass = array('f',[0.])


neC2Lep = np.array([0],dtype = np.uint32) #array('i',[0])
eC2Charge = np.zeros((1,1),dtype=np.int8) #array('i',[0])
eC2Eta = np.zeros((1,1),dtype=np.float32) #array('f',[0.])
eC2Phi = np.zeros((1,1),dtype=np.float32) #array('f',[0.])
eC2Pt = np.zeros((1,1),dtype=np.float32) #array('f',[0.])
eC2Mass = np.zeros((1,1),dtype=np.float32) #array('f',[0.])
nmC2Lep = np.array([0],dtype = np.uint32) #array('i',[0])
mC2Charge = np.zeros((1,1),dtype=np.int8) #array('i',[0])
mC2Eta = np.zeros((1,1),dtype=np.float32) #array('f',[0.])
mC2Phi = np.zeros((1,1),dtype=np.float32) #array('f',[0.])
mC2Pt = np.zeros((1,1),dtype=np.float32) #array('f',[0.])
mC2Mass = np.zeros((1,1),dtype=np.float32) #array('f',[0.])

cutTwoTree.Branch("nZ1C2Lep",nZ1C2Lep,"nZ1C2Lep/I")
cutTwoTree.Branch("Z1C2Charge",Z1C2Charge,"Z1C2Charge[nZ1C2Lep]/I")
cutTwoTree.Branch("Z1C2Flav",Z1C2Flav,"Z1C2Flav/I")
cutTwoTree.Branch("Z1C2Eta",Z1C2Eta,"Z1C2Eta[nZ1C2Lep]/F")
cutTwoTree.Branch("Z1C2Phi",Z1C2Phi,"Z1C2Phi[nZ1C2Lep]/F")
cutTwoTree.Branch("Z1C2Pt",Z1C2Pt,"Z1C2Pt[nZ1C2Lep]/F")
cutTwoTree.Branch("Z1C2Mass",Z1C2Mass,"Z1C2Mass[nZ1C2Lep]/F")

cutTwoTree.Branch("neC2Lep",neC2Lep,"neC2Lep/I")
cutTwoTree.Branch("eC2Charge",eC2Charge,"eC2Charge[neC2Lep][2]/I")
cutTwoTree.Branch("eC2Eta",eC2Eta,"eC2Eta[neC2Lep][2]/F")
cutTwoTree.Branch("eC2Phi",eC2Phi,"eC2Phi[neC2Lep][2]/F")
cutTwoTree.Branch("eC2Pt",eC2Pt,"eC2Pt[neC2Lep][2]/F")
cutTwoTree.Branch("eC2Mass",eC2Mass,"eC2Mass[neC2Lep][2]/F")
cutTwoTree.Branch("nmC2Lep",nmC2Lep,"nmC2Lep/I")
cutTwoTree.Branch("mC2Charge",mC2Charge,"mC2Charge[nmC2Lep][2]/I")
cutTwoTree.Branch("mC2Eta",mC2Eta,"mC2Eta[nmC2Lep][2]/F")
cutTwoTree.Branch("mC2Phi",mC2Phi,"mC2Phi[nmC2Lep][2]/F")
cutTwoTree.Branch("mC2Pt",mC2Pt,"mC2Pt[nmC2Lep][2]/F")
cutTwoTree.Branch("mC2Mass",mC2Mass,"mC2Mass[nmC2Lep][2]/F")

"""
cutTwoTree.Fill()

#After getting both lepton pairs. Information needed:
# All the above but for z1 and Z2 instead

nZ1C3Lep = array('i',[0])
Z1C3Flav = array('i',[0])
Z1C3Charge = array('i',[0])
Z1C3Eta = array('f',[0.])
Z1C3Phi = array('f',[0.])
Z1C3Pt = array('f',[0.])
Z1C3Mass = array('f',[0.])
nZ2C3Lep = array('i',[0])
Z2C3Flav = array('i',[0])
Z2C3Charge = array('i',[0])
Z2C3Eta = array('f',[0.])
Z2C3Phi = array('f',[0.])
Z2C3Pt = array('f',[0.])
Z2C3Mass = array('f',[0.])
cutThreeTree = TTree('cutThreeTree', 'cutThreeTree')
cutThreeTree.Branch("Z1C3Flav",Z1C3Flav,"Z1C3Flav[nZ1C1Lep]/I")
cutThreeTree.Branch("Z1C3Charge",Z1C3Charge,"Z1C3Charge[nZ1C1Lep]/I")
cutThreeTree.Branch("Z1C3Eta",Z1C3Eta,"Z1C3Eta[nZ1C1Lep]/F")
cutThreeTree.Branch("Z1C3Phi",Z1C3Phi,"Z1C3Phi[nZ1C1Lep]/F")
cutThreeTree.Branch("Z1C3Pt",Z1C3Pt,"Z1C3Pt[nZ1C1Lep]/F")
cutThreeTree.Branch("Z1C3Mass",Z1C3Mass,"Z1C3Mass[nZ1C1Lep]/F")
cutThreeTree.Branch("Z2C3Flav",Z2C3Flav,"Z2C3Flav[nZ2C1Lep]/I")
cutThreeTree.Branch("Z2C3Charge",Z2C3Charge,"Z2C3Charge[nZ2C1Lep]/I")
cutThreeTree.Branch("Z2C3Eta",Z2C3Eta,"Z2C3Eta[nZ2C1Lep]/F")
cutThreeTree.Branch("Z2C3Phi",Z2C3Phi,"Z2C3Phi[nZ2C1Lep]/F")
cutThreeTree.Branch("Z2C3Pt",Z2C3Pt,"Z2C3Pt[nZ2C1Lep]/F")
cutThreeTree.Branch("Z2C3Mass",Z2C3Mass,"Z2C3Mass[nZ2C1Lep]/F")
"""
#After getting both lepton pairs. Information needed:
#flavors and isolations for each lepton in Z1 and Z2

lepC3Iso = array('f',[0.]*4)
#lepC3Pt = array('f',[0.]*4)
#lepC3Eta = array('f',[0.]*4)

cutThreeTree = TTree('cutThreeTree', 'cutThreeTree')
cutThreeTree.Branch("lepC3Iso",lepC3Iso,"lepC3Iso[4]/F")
#cutThreeTree.Branch("lepC3Pt",lepC3Pt,"lepC3Pt[4]/F")
#cutThreeTree.Branch("lepC3Eta",lepC3Eta,"lepC3Eta[4]/F")

#After isolation cuts. Information needed:
#SIP for each lepton in Z1 and Z2
C4SIP = array('f',[0.]*4)
cutFourTree = TTree('cutFourTree', 'cutFourTree')
cutFourTree.Branch("C4SIP",C4SIP,"C4SIP[4]/F")





allCutPassCount = 0


crossSectionAvg = 0
crossSectionCtr = 0
print("Going into file loop.","time:",time.time()-startt)
for k,fileName in enumerate(fileAr):
    if endAfter and evCount > NToEnd:
        break
    #Open the file, get the Events tree
    tmpfile = TFile.Open(fileName)
    outFile.cd()
    mytree = tmpfile.Events
    runTree = tmpfile.Runs
    #Getting the cross section
    #For background it's precalculated
    if not isBackground:
        for i,runEv in enumerate(runTree):
            if i > 0:
                print("uhoh it has two",i,k,fileName)
            crossSection = runEv.genEventSumw / runEv.genEventCount
        crossSectionAvg += crossSection
        crossSectionCtr += 1
    if k % 10 == 0:
        print("Going into event loop for file {0}.".format(k),"time:",time.time()-startt)

    #EvLoop
    for ev in mytree:
        if endAfter:
            if evCount < NToStart:
                evCount += 1
                continue
            if evCount > NToEnd:
                break
        if evCount % 1000 == 0:
            print("Event: "+str(evCount))
        #print(ev.CaloMET_sumEt)
        #Filling up MET Hists
        
        #IndicesForLeptonPairs
        lepPairOneLeadInd = -1
        lepPairOneTrailingInd = -1
        #lepPairTwoLeadInd = 0
        #lepPairTwoTrailingInd = 0

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
        
        elecHLTPass = ev.HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL or ev.HLT_DoubleEle25_CaloIdL_MW
        muonHLTPass = ev.HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8 or ev.HLT_TripleMu_10_5_5_DZ or ev.HLT_TripleMu_12_10_5
        emHLTPass = ev.HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL or ev.HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ or ev.HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ or ev.HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ or ev.HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ or ev.HLT_Mu8_DiEle12_CaloIdL_TrackIdL_DZ
        #####FIRST SET OF LEAVES TO FILL#####
        #####ELECTRON LEAVES#####
        neLep[0] = tmpnElectron
        eHLT[0] = elecHLTPass
        print("--------------------------------------------------")
        print("evCount",evCount)
        print("neLep",neLep,"tmpnElectron",tmpnElectron,"elecHLTPass",elecHLTPass)
        if tmpnElectron:
            eEta = array('f',[0.]*tmpnElectron)
            ePt = array('f',[0.]*tmpnElectron)
            for i in range(tmpnElectron):
                print("i",i,"ev.Electron_eta[i]",ev.Electron_eta[i],"ev.Electron_pt[i]",ev.Electron_pt[i])
                eEta[i] = ev.Electron_eta[i]
                ePt[i] = ev.Electron_pt[i]
        else:
            eEta = 0
            ePt  = 0
        
        print("eEta",eEta,"ePt",ePt)
        

        #####MUON LEAVES#####
        nmLep[0] = tmpnMuon
        mHLT[0] = muonHLTPass
        if tmpnMuon:
            mEta = array('f',[0.]*tmpnMuon)
            mPt = array('f',[0.]*tmpnMuon)
            for i in range(tmpnMuon):
                mEta[i] = ev.Muon_eta[i]
                mPt[i] = ev.Muon_pt[i]
        else:
            mEta = 0
            mPt = 0

        #####ELECTRON/MUON HLT LEAF#####

        emHLT[0] = emHLTPass

        cutZeroTree.SetBranchAddress("eEta",eEta)
        cutZeroTree.SetBranchAddress("ePt",ePt)
        cutZeroTree.SetBranchAddress("mEta",mEta)
        cutZeroTree.SetBranchAddress("mPt",mPt)
        cutZeroTree.Fill()

        #####END FILLING FIRST SET OF LEAVES
        


        #####MAKING FIRST CUT FOR CANDIDATES#####
        
        #Checking double lepton HLT triggers
        elecPassHLT = False
        if elecHLTPass:
            elecPassHLT = True
        muonPassHLT = False
        if muonHLTPass:
            muonPassHLT = True
        if emHLTPass:
            elecPassHLT = True
            muonPassHLT = True


        #Counting Elec Candidates Loop
        elecCandIndAr = []
        if elecPassHLT:
            nElecCandPairs = checkForElecCands(ev,tmpnElectron,elecCandIndAr)
            tmpnElecCands = len(elecCandIndAr)
        else:
            nElecCandPairs = 0
        tmpnElecCands = len(elecCandIndAr)

        #Counting Muon Candidates Loop
        muonCandIndAr = []
        if muonPassHLT:
            nMuonCandPairs = checkForMuonCands(ev,tmpnMuon,muonCandIndAr)
        else:
            nMuonCandPairs = 0
        tmpnMuonCands = len(muonCandIndAr)
        
        #Checking if there is an electron positron pair
        enoughElecCands,enoughMuonCands,enoughLepCands = checkForLepCands(nElecCandPairs,nMuonCandPairs)
        #####CANDIDATE CUT COMPLETE#####
        if enoughLepCands:
            
            #####SECOND SET OF LEAVES TO FILL#####
            #####ELECTRON LEAVES#####
            neC1Lep[0] = tmpnElecCands
            if tmpnElecCands:
                eC1Charge = array('i',[0]*tmpnElecCands)
                eC1Eta = array('f',[0.]*tmpnElecCands)
                eC1Phi = array('f',[0.]*tmpnElecCands)
                eC1Pt = array('f',[0.]*tmpnElecCands)
                eC1Mass = array('f',[0.]*tmpnElecCands)

                for i,eCandInd in enumerate(elecCandIndAr):
                    eC1Charge[i] = ev.Electron_charge[eCandInd]
                    eC1Eta[i] = ev.Electron_eta[eCandInd]
                    eC1Phi[i] = ev.Electron_phi[eCandInd]
                    eC1Pt[i] =  ev.Electron_pt[eCandInd]
                    eC1Mass[i] = ev.Electron_mass[eCandInd]
            else:
                eC1Charge = 0
                eC1Eta = 0
                eC1Phi = 0
                eC1Pt = 0
                eC1Mass = 0



            #####MUON LEAVES#####
            nmC1Lep[0] = tmpnMuonCands
            if tmpnMuonCands:
                mC1Charge = array('i',[0]*tmpnMuonCands)
                mC1Eta = array('f',[0.]*tmpnMuonCands)
                mC1Phi = array('f',[0.]*tmpnMuonCands)
                mC1Pt = array('f',[0.]*tmpnMuonCands)
                mC1Mass = array('f',[0.]*tmpnMuonCands)

                for i,mCandInd in enumerate(muonCandIndAr):
                    mC1Charge[i] = ev.Muon_charge[mCandInd]
                    mC1Eta[i] = ev.Muon_eta[mCandInd]
                    mC1Phi[i] = ev.Muon_phi[mCandInd]
                    mC1Pt[i] =  ev.Muon_pt[mCandInd]
                    mC1Mass[i] = ev.Muon_mass[mCandInd]
            else:
                mC1Charge = 0
                mC1Eta = 0
                mC1Phi = 0
                mC1Pt = 0
                mC1Mass = 0



            cutOneTree.SetBranchAddress("eC1Charge",eC1Charge)
            cutOneTree.SetBranchAddress("eC1Eta",eC1Eta)
            cutOneTree.SetBranchAddress("eC1Phi",eC1Phi)
            cutOneTree.SetBranchAddress("eC1Pt",eC1Pt)
            cutOneTree.SetBranchAddress("eC1Mass",eC1Mass)
            cutOneTree.SetBranchAddress("mC1Charge",mC1Charge)
            cutOneTree.SetBranchAddress("mC1Eta",mC1Eta)
            cutOneTree.SetBranchAddress("mC1Phi",mC1Phi)
            cutOneTree.SetBranchAddress("mC1Pt",mC1Pt)
            cutOneTree.SetBranchAddress("mC1Mass",mC1Mass)

            cutOneTree.Fill()
                    

            #####END FILLING SECOND SET OF LEAVES

        if debug:
            print("enoughElecCands",enoughElecCands,"enoughMuonCands",enoughMuonCands,"enoughLepCands",enoughLepCands)
        #Electrons loop
        if debug:
            print("entering electrons loop")

        #####MAKING FIRST CUT FOR Z1#####
        if enoughLepCands and enoughElecCands:
            for tmpnElecItr,i in enumerate(elecCandIndAr):
                if debug:
                    print("First Electron",i)
                tmpPtOne = ev.Electron_pt[i]
                tmpEtaOne = ev.Electron_eta[i]
                tmpMassOne = ev.Electron_mass[i]
                tmpPhiOne = ev.Electron_phi[i]
                #If enough lepton candidates and enough electron candidates, begin the loop
                #if leptonCandSum >= 4:
                
                if debug:
                    print(i,"enough LepCands and ElecCands")
                if tmpPtOne > firstZTrailingCut:
                    if debug:
                        print(i,"Electron passed first trailing pt cut",firstZTrailingCut)
                    #Looping over other electrons
                    if debug:
                        print(i,"Loop over remaining electrons")
                    difFromZMassOne,lepPairOneLeadInd,lepPairOneTrailingInd,leadLepPairOneVec,trailingLepPairOneVec,leadLepPairCharge,trailingLepPairCharge = checkForElecPair(ev,i,tmpnElectron,elecCandIndAr,elecPassesZ2CutsAr,elecPassesCutsAr,difFromZMassOne,lepPairOneLeadInd,lepPairOneTrailingInd,leadLepPairOneVec,trailingLepPairOneVec,leadLepPairCharge,trailingLepPairCharge)
        if debug:
            print("ELECTRON LOOP OVER")
            print("difFromZMassOne",difFromZMassOne,"lepPairOneLeadInd",lepPairOneLeadInd,"lepPairOneTrailingInd",lepPairOneTrailingInd,"leadLepPairCharge",leadLepPairCharge,"trailingLepPairCharge",trailingLepPairCharge)

                        
        muonLeading = False
        muonPassesCutsAr = []
        muonPassesZ2CutsAr = []

        #Muons loop
        if debug:
            print("Entering muons loop")
        if enoughLepCands and enoughMuonCands:
            for tmpnMuonItr,i in enumerate(muonCandIndAr):
                if debug:
                    print("First Muon",i)
                #No cuts
                tmpPtOne = ev.Muon_pt[i]
                tmpEtaOne = ev.Muon_eta[i]
                tmpMassOne = ev.Muon_mass[i]
                tmpPhiOne = ev.Muon_phi[i]
                
            #First Z Cuts
            
                if debug:
                    print(i,"enough LepCands and MuonCands")
                if tmpPtOne > firstZTrailingCut:
                    if debug:
                        print(i,"Muon passed first trailing pt cut", firstZTrailingCut)
                    #Looping over other muons
                    if debug:
                        print(i,"Loop over remaining muons")
                    difFromZMassOne,lepPairOneLeadInd,lepPairOneTrailingInd,leadLepPairOneVec,trailingLepPairOneVec,leadLepPairCharge,trailingLepPairCharge,muonLeading = checkForMuonPair(ev,i,tmpnMuon,muonCandIndAr,muonPassesZ2CutsAr,muonPassesCutsAr,difFromZMassOne,lepPairOneLeadInd,lepPairOneTrailingInd,leadLepPairOneVec,trailingLepPairOneVec,leadLepPairCharge,trailingLepPairCharge,muonLeading)

        if debug:
            print("MUON LOOP OVER")
            print("difFromZMassOne",difFromZMassOne,"lepPairOneLeadInd",lepPairOneLeadInd,"lepPairOneTrailingInd",lepPairOneTrailingInd,"leadLepPairCharge",leadLepPairCharge,"trailingLepPairCharge",trailingLepPairCharge,"muonLeading",muonLeading)
        #####Z1 CUT COMPLETE#####
        Z1Found = lepPairOneLeadInd >= 0 and lepPairOneTrailingInd >= 0
        if Z1Found:
            #####THIRD SET OF LEAVES TO FILL#####
            #####Z1 LEAVES#####
            
            #nZ1C2Lep = array('i',[2])
            nZ1C2Lep[0] = 2
            
            if muonLeading:
                Z1C2Flav = array('i',[1]) #0 for electron, 1 for muon
                Z1C2Charge = array('i',[ev.Muon_charge[lepPairOneLeadInd],ev.Muon_charge[lepPairOneTrailingInd]])
                
                Z1C2Eta  = array('f',[ev.Muon_eta[lepPairOneLeadInd],ev.Muon_eta[lepPairOneTrailingInd]])
                Z1C2Phi  = array('f',[ev.Muon_phi[lepPairOneLeadInd],ev.Muon_phi[lepPairOneTrailingInd]])
                Z1C2Pt   = array('f',[ev.Muon_pt[lepPairOneLeadInd],ev.Muon_pt[lepPairOneTrailingInd]])
                Z1C2Mass = array('f',[ev.Muon_mass[lepPairOneLeadInd],ev.Muon_mass[lepPairOneTrailingInd]])
            else:
                Z1C2Flav   = array('i',[0]) #0 for electron, 1 for muon
                Z1C2Charge = array('i',[ev.Electron_charge[lepPairOneLeadInd],ev.Electron_charge[lepPairOneTrailingInd]])
                
                Z1C2Eta  = array('f',[ev.Electron_eta[lepPairOneLeadInd],ev.Electron_eta[lepPairOneTrailingInd]])
                Z1C2Phi  = array('f',[ev.Electron_phi[lepPairOneLeadInd],ev.Electron_phi[lepPairOneTrailingInd]])
                Z1C2Pt   = array('f',[ev.Electron_pt[lepPairOneLeadInd],ev.Electron_pt[lepPairOneTrailingInd]])
                Z1C2Mass = array('f',[ev.Electron_mass[lepPairOneLeadInd],ev.Electron_mass[lepPairOneTrailingInd]])
            


            



            #####ELECTRON LEAVES#####
            elecZ2CandIndAr = [] #This will index the candidate pairs from elecPassesZ2CutsAr,
            #                     while removing the pairs with Leptons from Z1
            for i in range(len(elecPassesZ2CutsAr)):
                tmpElecIndAr = elecPassesZ2CutsAr[i][0]
                if not muonLeading:
                    if lepPairOneLeadInd in tmpElecIndAr or lepPairOneTrailingInd in tmpElecIndAr:
                        continue
                
                elecZ2CandIndAr.append(i)

            tmpnElecZ2Cands = len(elecZ2CandIndAr)
            #neC2Lep = np.array([tmpnElecZ2Cands],dtype = np.uint32)
            neC2Lep[0] = tmpnElecZ2Cands
            if tmpnElecZ2Cands:
                eC2Charge = np.zeros((tmpnElecZ2Cands,2),dtype=np.int8)
                eC2Eta    = np.zeros((tmpnElecZ2Cands,2),dtype=np.float32)
                eC2Phi    = np.zeros((tmpnElecZ2Cands,2),dtype=np.float32)
                eC2Pt     = np.zeros((tmpnElecZ2Cands,2),dtype=np.float32)
                eC2Mass   = np.zeros((tmpnElecZ2Cands,2),dtype=np.float32)
                for i,elecPassesZ2CutsItr in enumerate(elecZ2CandIndAr):
                    eC2Charge[i][0] = elecPassesZ2CutsAr[elecPassesZ2CutsItr][2][0]
                    eC2Charge[i][1] = elecPassesZ2CutsAr[elecPassesZ2CutsItr][2][1]
                    eC2Eta[i][0]    = elecPassesZ2CutsAr[elecPassesZ2CutsItr][1][0].Eta()
                    eC2Eta[i][1]    = elecPassesZ2CutsAr[elecPassesZ2CutsItr][1][1].Eta()
                    eC2Pt[i][0]     = elecPassesZ2CutsAr[elecPassesZ2CutsItr][1][0].Pt()
                    eC2Pt[i][1]     = elecPassesZ2CutsAr[elecPassesZ2CutsItr][1][1].Pt()
                    eC2Phi[i][0]    = elecPassesZ2CutsAr[elecPassesZ2CutsItr][1][0].Phi()
                    eC2Phi[i][1]    = elecPassesZ2CutsAr[elecPassesZ2CutsItr][1][1].Phi()
                    eC2Mass[i][0]    = elecPassesZ2CutsAr[elecPassesZ2CutsItr][1][0].M()
                    eC2Mass[i][1]    = elecPassesZ2CutsAr[elecPassesZ2CutsItr][1][1].M()
            else:
                eC2Charge = 0
                eC2Eta    = 0
                eC2Phi    = 0
                eC2Pt     = 0
                eC2Mass   = 0

            #####MUON LEAVES#####
            muonZ2CandIndAr = [] #This will index the candidate pairs from muonPassesZ2CutsAr,
            #                     while removing the pairs with Leptons from Z1
            for i in range(len(muonPassesZ2CutsAr)):
                tmpMuonIndAr = muonPassesZ2CutsAr[i][0]
                if muonLeading:
                    if lepPairOneLeadInd in tmpMuonIndAr or lepPairOneTrailingInd in tmpMuonIndAr:
                        continue
                
                muonZ2CandIndAr.append(i)

            tmpnMuonZ2Cands = len(muonZ2CandIndAr)
            #nmC2Lep = np.array([tmpnMuonZ2Cands],dtype = np.uint32)
            nmC2Lep[0] = tmpnMuonZ2Cands
            if tmpnMuonZ2Cands:
                mC2Charge = np.zeros((tmpnMuonZ2Cands,2),dtype=np.int8)
                mC2Eta    = np.zeros((tmpnMuonZ2Cands,2),dtype=np.float32)
                mC2Phi    = np.zeros((tmpnMuonZ2Cands,2),dtype=np.float32)
                mC2Pt     = np.zeros((tmpnMuonZ2Cands,2),dtype=np.float32)
                mC2Mass   = np.zeros((tmpnMuonZ2Cands,2),dtype=np.float32)
                for i,muonPassesZ2CutsItr in enumerate(muonZ2CandIndAr):
                    mC2Charge[i][0] = muonPassesZ2CutsAr[muonPassesZ2CutsItr][2][0]
                    mC2Charge[i][1] = muonPassesZ2CutsAr[muonPassesZ2CutsItr][2][1]
                    mC2Eta[i][0]    = muonPassesZ2CutsAr[muonPassesZ2CutsItr][1][0].Eta()
                    mC2Eta[i][1]    = muonPassesZ2CutsAr[muonPassesZ2CutsItr][1][1].Eta()
                    mC2Pt[i][0]     = muonPassesZ2CutsAr[muonPassesZ2CutsItr][1][0].Pt()
                    mC2Pt[i][1]     = muonPassesZ2CutsAr[muonPassesZ2CutsItr][1][1].Pt()
                    mC2Phi[i][0]    = muonPassesZ2CutsAr[muonPassesZ2CutsItr][1][0].Phi()
                    mC2Phi[i][1]    = muonPassesZ2CutsAr[muonPassesZ2CutsItr][1][1].Phi()
                    mC2Mass[i][0]    = muonPassesZ2CutsAr[muonPassesZ2CutsItr][1][0].M()
                    mC2Mass[i][1]    = muonPassesZ2CutsAr[muonPassesZ2CutsItr][1][1].M()
            else:
                mC2Charge = 0
                mC2Eta    = 0
                mC2Phi    = 0
                mC2Pt     = 0
                mC2Mass   = 0
            
            #cutTwoTree.SetBranchAddress("nZ1C2Lep",nZ1C2Lep)
            cutTwoTree.SetBranchAddress("Z1C2Flav",Z1C2Flav)
            
            cutTwoTree.SetBranchAddress("Z1C2Charge",Z1C2Charge)
            cutTwoTree.SetBranchAddress("Z1C2Eta",Z1C2Eta)
            cutTwoTree.SetBranchAddress("Z1C2Phi",Z1C2Phi)
            cutTwoTree.SetBranchAddress("Z1C2Pt",Z1C2Pt)
            cutTwoTree.SetBranchAddress("Z1C2Mass",Z1C2Mass)
            
            cutTwoTree.SetBranchAddress("neC2Lep",neC2Lep)
            cutTwoTree.SetBranchAddress("eC2Charge",eC2Charge)
            cutTwoTree.SetBranchAddress("eC2Eta",eC2Eta)
            cutTwoTree.SetBranchAddress("eC2Phi",eC2Phi)
            cutTwoTree.SetBranchAddress("eC2Pt",eC2Pt)
            cutTwoTree.SetBranchAddress("eC2Mass",eC2Mass)
            cutTwoTree.SetBranchAddress("nmC2Lep",nmC2Lep)
            cutTwoTree.SetBranchAddress("mC2Charge",mC2Charge)
            cutTwoTree.SetBranchAddress("mC2Eta",mC2Eta)
            cutTwoTree.SetBranchAddress("mC2Phi",mC2Phi)
            cutTwoTree.SetBranchAddress("mC2Pt",mC2Pt)
            cutTwoTree.SetBranchAddress("mC2Mass",mC2Mass)
            #print(nZ1C2Lep,Z1C2Flav,Z1C2Charge,Z1C2Eta,Z1C2Phi,Z1C2Pt,Z1C2Mass)
            #print(neC2Lep,eC2Charge,eC2Eta,eC2Phi,eC2Pt,eC2Mass)
            #print(nmC2Lep,mC2Charge,mC2Eta,mC2Phi,mC2Pt,mC2Mass)
            

            cutTwoTree.Fill()
            #####END FILLING THIRD SET OF LEAVES
        
        

        #####MAKING SECOND CUT FOR Z2#####
        if debug:
            print("Going to find Z2 if Z1 has been found")
        if Z1Found:
            if debug:
                print("Z1 was found")
            passesCandCuts = False
            muonZ2Pair = False
            if debug:
                print("len(muonPassesCutsAr)",len(muonPassesCutsAr),"len(elecPassesCutsAr)",len(elecPassesCutsAr),"len(muonPassesZ2CutsAr)",len(muonPassesZ2CutsAr),"len(elecPassesZ2CutsAr",len(elecPassesZ2CutsAr))
            if len(muonPassesCutsAr) + len(elecPassesCutsAr) > 0 and len(muonPassesZ2CutsAr) + len(elecPassesZ2CutsAr) - 1 > 0: #-1 for the lead Z1 pair
                if debug:
                    print("Passed check for there being enough candidates for Z2")
                    print("entering loop on Electron Z2 candidates")
                for i,elecZ2Cand in enumerate(elecPassesZ2CutsAr):
                    if debug:
                        print(i,"elecZ2Cand",elecZ2Cand)
                    if muonLeading or (elecZ2Cand[0][0] != lepPairOneLeadInd and elecZ2Cand[0][0] != lepPairOneTrailingInd and elecZ2Cand[0][1] != lepPairOneLeadInd and elecZ2Cand[0][1] != lepPairOneTrailingInd):
                        if debug:
                            print("Passed the check that we aren't looking at the Z1 pair")
                        fourLepVec = elecZ2Cand[1][0] + elecZ2Cand[1][1] + leadLepPairOneVec + trailingLepPairOneVec
                        fourLepInvMass = fourLepVec.M()
                        if debug:
                            print("fourLepInvMass",fourLepInvMass)
                        if fourLepInvMass > fourLeptonInvMassCut:
                            if debug:
                                print("passed four lepton invmass cut",fourLeptonInvMassCut)
                            passesCandCuts = True
                            if not muonLeading:
                                if debug:
                                    print("not muonLeading. checking 4 e cuts")
                                passesCandCuts = False
                                if elecZ2Cand[2][0] != leadLepPairCharge:
                                    if debug:
                                        print("elecZ2Can[2][0] != leadLepPairCharge","elecZ2Can[2][0]",elecZ2Cand[2][0],"leadLepPairCharge",leadLepPairCharge)
                                    tmpCrossCandVec = elecZ2Cand[1][0] + leadLepPairOneVec
                                    if debug:
                                        print("tmpCrossCandVec = elecZ2Cand[1][0] + leadLepPairOneVec",tmpCrossCandVec)
                                        print("tmpCrossCandVec.M()",tmpCrossCandVec.M())
                                    if tmpCrossCandVec.M() > 12:
                                        if debug:
                                            print("passed check that the invmass is > 12")
                                        passesCandCuts = True
                                    else:
                                        tmpCrossCandVec = elecZ2Cand[1][1] + trailingLepPairOneVec
                                        if debug:
                                            print("Less than 12 so trying other electron electron combination")
                                            print("tmpCrossCandVec = elecZ2Cand[1][1] + trailingLepPairOneVec",tmpCrossCandVec)
                                            print("tmpCrossCandVec.M()",tmpCrossCandVec.M())
                                        if tmpCrossCandVec.M() > 12:
                                            if debug:
                                                print("passed check that the invmass is > 12")
                                            passesCandCuts = True
                                else:
                                    if debug:
                                        print("elecZ2Can[2][0] == leadLepPairCharge","elecZ2Can[2][0]",elecZ2Cand[2][0],"leadLepPairCharge",leadLepPairCharge)
                                    tmpCrossCandVec = elecZ2Cand[1][1] + leadLepPairOneVec
                                    if debug:
                                        print("tmpCrossCandVec = elecZ2Cand[1][1] + leadLepPairOneVec",tmpCrossCandVec)
                                        print("tmpCrossCandVec.M()",tmpCrossCandVec.M())
                                    if tmpCrossCandVec.M() > 12:
                                        if debug:
                                            print("passed check that the invmass is > 12")
                                        passesCandCuts = True
                                    else:
                                        tmpCrossCandVec = elecZ2Cand[1][0] + trailingLepPairOneVec
                                        if debug:
                                            print("Less than 12 so trying other electron electron combination")
                                            print("tmpCrossCandVec = elecZ2Cand[1][0] + trailingLepPairOneVec",tmpCrossCandVec)
                                            print("tmpCrossCandVec.M()",tmpCrossCandVec.M())
                                        if tmpCrossCandVec.M() > 12:
                                            if debug:
                                                print("passed check that the invmass is > 12")
                                            passesCandCuts = True
                            if debug:
                                print("checking if passed potential 4e cut","passesCandCuts",passesCandCuts)
                            if passesCandCuts:
                                if debug:
                                    print("passed cut. Checking for highest Pt in lead of Z2")
                                if debug:
                                    print("elecZ2Cand[1][0].Pt()",elecZ2Cand[1][0].Pt())
                                if elecZ2Cand[1][0].Pt() > leadZ2Pt:
                                    if debug:
                                        print("New highest pt found. Old pt:",leadZ2Pt)
                                    leadZ2Pt = elecZ2Cand[1][0].Pt()
                                    trailingZ2Pt = elecZ2Cand[1][1].Pt()
                                    leadZ2LepPairInd = i
                                elif elecZ2Cand[1][0].Pt() == leadZ2Pt:
                                    if debug:
                                        print("Highest pt equal. checking trailing Z2 pt")
                                    if elecZ2Cand[1][1].Pt() == trailingZ2Pt:
                                        if debug:
                                            print("New highest trailing pt found. Old pt:",trailingZ2Pt)
                                        trailingZ2Pt = elecZ2Cand[1][1].Pt()
                                        leadZ2LepPairInd = i
                if debug:

                    print("ELECTRON Z2 LOOP FINISHED")
                    print("leadZ2LepPairInd",leadZ2LepPairInd,"leadZ2Pt",leadZ2Pt,"trailingZ2Pt",trailingZ2Pt)


                                


                for i,muonZ2Cand in enumerate(muonPassesZ2CutsAr):
                    if debug:
                        print(i,"muonZ2Cand",muonZ2Cand)
                    if not muonLeading or (muonZ2Cand[0][0] != lepPairOneLeadInd and muonZ2Cand[0][0] != lepPairOneTrailingInd and muonZ2Cand[0][1] != lepPairOneLeadInd and muonZ2Cand[0][1] != lepPairOneTrailingInd): 
                        if debug:
                            print("Passed the check that we aren't looking at the Z1 pair")
                        fourLepVec = muonZ2Cand[1][0] + muonZ2Cand[1][1] + leadLepPairOneVec + trailingLepPairOneVec
                        fourLepInvMass = fourLepVec.M()
                        if debug:
                            print("fourLepInvMass",fourLepInvMass)
                        if fourLepInvMass > fourLeptonInvMassCut:
                            if debug:
                                print("passed four lepton invmass cut",fourLeptonInvMassCut)
                            passesCandCuts = True
                            if muonLeading:
                                if debug:
                                    print("muonLeading. checking 4 e cuts")
                                passesCandCuts = False
                                if muonZ2Cand[2][0] != leadLepPairCharge:
                                    if debug:
                                        print("muonZ2Can[2][0] != leadLepPairCharge","muonZ2Can[2][0]",muonZ2Cand[2][0],"leadLepPairCharge",leadLepPairCharge)
                                    tmpCrossCandVec = muonZ2Cand[1][0] + leadLepPairOneVec
                                    if debug:
                                        print("tmpCrossCandVec = muonZ2Cand[1][0] + leadLepPairOneVec",tmpCrossCandVec)
                                        print("tmpCrossCandVec.M()",tmpCrossCandVec.M())
                                    if tmpCrossCandVec.M() > 12:
                                        if debug:
                                            print("passed check that the invmass is > 12")
                                        passesCandCuts = True
                                    else:
                                        
                                        tmpCrossCandVec = muonZ2Cand[1][1] + trailingLepPairOneVec
                                        if debug:
                                            print("Less than 12 so trying other muon muon combination")
                                            print("tmpCrossCandVec = muonZ2Cand[1][1] + trailingLepPairOneVec",tmpCrossCandVec)
                                            print("tmpCrossCandVec.M()",tmpCrossCandVec.M())
                                        if tmpCrossCandVec.M() > 12:
                                            if debug:
                                                print("passed check that the invmass is > 12")
                                            passesCandCuts = True
                                else:
                                    if debug:
                                        print("muonZ2Can[2][0] == leadLepPairCharge","muonZ2Can[2][0]",muonZ2Cand[2][0],"leadLepPairCharge",leadLepPairCharge)
                                    tmpCrossCandVec = muonZ2Cand[1][1] + leadLepPairOneVec
                                    if debug:
                                        print("tmpCrossCandVec = muonZ2Cand[1][1] + leadLepPairOneVec",tmpCrossCandVec)
                                        print("tmpCrossCandVec.M()",tmpCrossCandVec.M())
                                    if tmpCrossCandVec.M() > 12:
                                        if debug:
                                            print("passed check that the invmass is > 12")
                                        passesCandCuts = True
                                        
                                    else:
                                        tmpCrossCandVec = muonZ2Cand[1][0] + trailingLepPairOneVec
                                        if debug:
                                            print("Less than 12 so trying other muon muon combination")
                                            print("tmpCrossCandVec = muonZ2Cand[1][0] + trailingLepPairOneVec",tmpCrossCandVec)
                                            print("tmpCrossCandVec.M()",tmpCrossCandVec.M())
                                        if tmpCrossCandVec.M() > 12:
                                            if debug:
                                                print("passed check that the invmass is > 12")
                                            passesCandCuts = True
                            if passesCandCuts:
                                if debug:
                                    print("passed cut. Checking for highest Pt in lead of Z2")
                                if debug:
                                    print("muonZ2Cand[1][0].Pt()",muonZ2Cand[1][0].Pt())
                                if muonZ2Cand[1][0].Pt() > leadZ2Pt:
                                    if debug:
                                        print("New highest pt found. Old pt:",leadZ2Pt)
                                    muonZ2Pair = True
                                    leadZ2Pt = muonZ2Cand[1][0].Pt()
                                    trailingZ2Pt = muonZ2Cand[1][1].Pt()
                                    leadZ2LepPairInd = i
                                elif muonZ2Cand[1][0].Pt() == leadZ2Pt:
                                    if debug:
                                        print("Highest pt equal. checking trailing Z2 pt")
                                    if muonZ2Cand[1][1].Pt() == trailingZ2Pt:
                                        if debug:
                                            print("New highest trailing pt found. Old pt:",trailingZ2Pt)
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
            if debug:
                print("MUON Z2 LOOP FINISHED")
                print("muonZ2Pair",muonZ2Pair,"leadZ2LepPairInd",leadZ2LepPairInd,"leadZ2Pt",leadZ2Pt,"trailingZ2Pt",trailingZ2Pt)
                print("now checking if the Z2 cuts were passed")
            if leadZ2LepPairInd >= 0:
                if debug:
                    print("The Z2 cuts were passed")

            


                #Now we want to cut based on the relative isolation
                #For each lepton this is obtained as follows
                #Sum up the Pt for all the tracks, the energy deposits in the ECAL, and the energy deposits in the HCAL, within a DeltaR < 0.3 cone around the lepton
                #Add these three sums together and divide by the lepton's Pt
                #Unfortunately with NanoAOD, you do not have the information to do these sums.
                #There are branches that have precalculated them, but only for electrons with Pt > 35GeV
                #The muon branches don't have these, but rather have values based on particle flow
                #Particularly the Muon_pfRelIso03_all branch
                #Not sure if it's at all proper to add these together, but will use the electron PF isolation also when Pt < 35GeV
                passesIsoCuts = True
                
                muonOrNotAr = [muonLeading,muonZ2Pair]
                if debug:
                    print("muonOrNotAr",muonOrNotAr)
                passesPtCutAr = [True,True,True,True]
                Z1Z2VecPtAr = []
                Z1Z2VecPtAr.append(leadLepPairOneVec.Pt())
                Z1Z2VecPtAr.append(trailingLepPairOneVec.Pt())
                Z1Z2IndAr = [lepPairOneLeadInd,lepPairOneTrailingInd,leadZ2LepPairInd,leadZ2LepPairInd]
                #Previously used passesPtCutAr to bypass the cuts if the Pt was less than 35,
                #but now just using it to switch different types of isolation used in the cuts for electrons
                for i in range(4):
                    if i < 2: 
                        if muonLeading:
                            continue
                        elif Z1Z2VecPtAr[i] < 35:
                            passesPtCutAr[i] = False
                    elif muonZ2Pair:
                        Z1Z2VecPtAr.append(muonPassesZ2CutsAr[leadZ2LepPairInd][1][i-2].Pt())
                    else:
                        Z1Z2VecPtAr.append(elecPassesZ2CutsAr[leadZ2LepPairInd][1][i-2].Pt())
                        if Z1Z2VecPtAr[i] < 35:
                            passesPtCutAr[i] = False
                if debug:
                    print("Z1Z2VecPtAr",Z1Z2VecPtAr,"Z1Z2IndAr",Z1Z2IndAr,"passesPtCutAr",passesPtCutAr)

                #####FOURTH SET OF LEAVES TO FILL#####
                #####LEPTON LEAVES WILL BE FILLED DURING CUT LOOP#####
                lepC3Iso  = array('f',[0.]*4)
                """
                lepC3Pt   = array('f',[0.]*4)
                lepC3Eta  = array('f',[0.]*4)
                for i in range(4):
                    lepC3Pt[i]  = Z1Z2VecPtAr[i]
                    lepC3Eta[i] = Z1Z2VecPtAr[i]
                    ev.Electron_eta[tmpIsoOneInd]
                    if i < 2:
                        if muonLeading:
                            lepC3Iso[i] = ev.Muon_pfRelIso03_all[Z1Z2IndAr[i]]
                        else:
                            lepC3Iso[i] = 
                """
                

                ########
                tmpIsoAr = []
                for i,Z1Z2Ind in enumerate(Z1Z2IndAr):
                    #Getting indices for accessing the different arrays for Z1
                    tmpIsMuonOne = True
                    if i < 2:
                        tmpIsoOneInd = Z1Z2Ind
                        if not muonLeading:
                            tmpIsMuonOne = False
                    elif muonZ2Pair:
                        tmpIsoOneInd = muonPassesZ2CutsAr[Z1Z2Ind][0][i-2]
                    else:
                        tmpIsoOneInd = elecPassesZ2CutsAr[Z1Z2Ind][0][i-2]
                        tmpIsMuonOne = False
                    #Getting tmpIsoOne
                    if tmpIsMuonOne:
                        tmpIsoOne = ev.Muon_pfRelIso03_all[tmpIsoOneInd]
                    elif passesPtCutAr[i]:
                        if abs(ev.Electron_eta[tmpIsoOneInd]) < 1.4:
                            if debug:
                                print("electron in barrel")
                            tmpAdd = max(0., ev.Electron_dr03EcalRecHitSumEt[tmpIsoOneInd] - 1.)
                        else:
                            if debug:
                                print("electron in endcap")
                            tmpAdd = ev.Electron_dr03EcalRecHitSumEt[tmpIsoOneInd]
                        tmpIsoOne = ( ev.Electron_dr03TkSumPt[tmpIsoOneInd] + tmpAdd + ev.Electron_dr03HcalDepth1TowerSumEt[tmpIsoOneInd] ) / ev.Electron_pt[tmpIsoOneInd]
                    else:
                        tmpIsoOne = ev.Electron_pfRelIso03_all[tmpIsoOneInd]
                    tmpIsoAr.append(tmpIsoOne)
                    lepC3Iso[i] = tmpIsoOne
                
                cutThreeTree.SetBranchAddress("lepC3Iso",lepC3Iso)
                cutThreeTree.Fill()
                
                for i,tmpIsoOne in enumerate(tmpIsoAr[:-1]):
                    for tmpIsoTwo in tmpIsoAr[i+1:]:
                        if debug:
                            print(i,j,"tmpIsoOne",tmpIsoOne,"tmpIsoTwo",tmpIsoTwo)
                        if tmpIsoOne + tmpIsoTwo > lepIsoCut:
                            if debug:
                                print(i,j,"summed isos > 0.35. cuts not passed")
                            passesIsoCuts = False
                            break
                    if not passesIsoCuts:
                        break
                        

                #########################################
                """

                for i,Z1Z2Ind in enumerate(Z1Z2IndAr):
                    #Getting indices for accessing the different arrays for Z1
                    tmpIsMuonOne = True
                    if i < 2:
                        tmpIsoOneInd = Z1Z2Ind
                        if not muonLeading:
                            tmpIsMuonOne = False
                    elif muonZ2Pair:
                        tmpIsoOneInd = muonPassesZ2CutsAr[Z1Z2Ind][0][i-2]
                    else:
                        tmpIsoOneInd = elecPassesZ2CutsAr[Z1Z2Ind][0][i-2]
                        tmpIsMuonOne = False
                    #Getting tmpIsoOne
                    if tmpIsMuonOne:
                        tmpIsoOne = ev.Muon_pfRelIso03_all[tmpIsoOneInd]
                    elif passesPtCutAr[i]:
                        if abs(ev.Electron_eta[tmpIsoOneInd]) < 1.4:
                            if debug:
                                print("electron in barrel")
                            tmpAdd = max(0., ev.Electron_dr03EcalRecHitSumEt[tmpIsoOneInd] - 1.)
                        else:
                            if debug:
                                print("electron in endcap")
                            tmpAdd = ev.Electron_dr03EcalRecHitSumEt[tmpIsoOneInd]
                        tmpIsoOne = ( ev.Electron_dr03TkSumPt[tmpIsoOneInd] + tmpAdd + ev.Electron_dr03HcalDepth1TowerSumEt[tmpIsoOneInd] ) / ev.Electron_pt[tmpIsoOneInd]
                    else:
                        tmpIsoOne = ev.Electron_pfRelIso03_all[tmpIsoOneInd]
                    for j in range(i+1,len(Z1Z2IndAr)):
                        Z1Z2IndTwo = Z1Z2IndAr[j]
                        if debug:
                            print(i,j,"muonLeading",muonLeading,"muonZ2Pair",muonZ2Pair,"Z1Z2Ind",Z1Z2Ind,"Z1Z2IndTwo",Z1Z2IndTwo)
                        
                        #Getting indices for accessing the different arrays for Z2
                        tmpIsMuonTwo = True
                        if j < 2:
                            tmpIsoTwoInd = Z1Z2IndTwo
                            if not muonLeading:
                                tmpIsMuonTwo = False
                        elif muonZ2Pair:
                            tmpIsoTwoInd = muonPassesZ2CutsAr[Z1Z2IndTwo][0][j-2]
                        else:
                            tmpIsoTwoInd = elecPassesZ2CutsAr[Z1Z2IndTwo][0][j-2]
                            tmpIsMuonTwo = False
                        if debug:
                            print(i,j,"tmpIsoOneInd",tmpIsoOneInd,"tmpIsoTwoInd",tmpIsoTwoInd)
                        
                        #Getting tmpIsoTwo
                        if tmpIsMuonTwo:
                            tmpIsoTwo = ev.Muon_pfRelIso03_all[tmpIsoTwoInd]
                        elif passesPtCutAr[i]:
                            if abs(ev.Electron_eta[tmpIsoTwoInd]) < 1.4:
                                if debug:
                                    print("electron in barrel")
                                tmpAdd = max(0., ev.Electron_dr03EcalRecHitSumEt[tmpIsoTwoInd] - 1.)
                            else:
                                if debug:
                                    print("electron in endcap")
                                tmpAdd = ev.Electron_dr03EcalRecHitSumEt[tmpIsoTwoInd]
                            tmpIsoTwo = ( ev.Electron_dr03TkSumPt[tmpIsoTwoInd] + tmpAdd + ev.Electron_dr03HcalDepth1TowerSumEt[tmpIsoTwoInd] ) / ev.Electron_pt[tmpIsoTwoInd]
                        else:
                            tmpIsoTwo = ev.Electron_pfRelIso03_all[tmpIsoTwoInd]
                        if debug:
                            print(i,j,"tmpIsoOne",tmpIsoOne,"tmpIsoTwo",tmpIsoTwo)
                        if tmpIsoOne + tmpIsoTwo > 0.35:
                            if debug:
                                print(i,j,"summed isos > 0.35. cuts not passed")
                            passesIsoCuts = False
                """

                #########################################
                        


                        
                            
                if debug:
                    print("FINISHED WITH ISO CUTS","passesIsoCuts",passesIsoCuts)



                #Now, assuming all *these* cuts pass, on to cut 6.
                #Want the SIP of the leptons
                
                if passesIsoCuts:
                    if debug:
                        print("passed iso cuts. Starting SIP cuts")
                    
                    #####FIFTH SET OF LEAVES TO FILL#####
                    #####SIP LEAF FILLED DURING LOOP#####
                    tmpSIPAr = []
                    passesSIPCut = True
                    C4SIP = array('f',[0.]*4)
                    for i,Z1Z2Ind in enumerate(Z1Z2IndAr):
                        if i < 2:
                            if muonLeading:
                                tmpSIP = ev.Muon_sip3d[Z1Z2Ind]
                            else:
                                tmpSIP = ev.Electron_sip3d[Z1Z2Ind]
                        else:
                            if muonZ2Pair:
                                tmpSIP = ev.Muon_sip3d[Z1Z2Ind]
                            else:
                                tmpSIP = ev.Electron_sip3d[Z1Z2Ind]

                        C4SIP[i] = tmpSIP
                        if tmpSIP > 4:
                            passesSIPCut = False
                    cutFourTree.SetBranchAddress("C4SIP",C4SIP)
                    cutFourTree.Fill()

                    """
                    if muonLeading:
                        if debug:
                            print("muonLeading",muonLeading)
                        if muonZ2Pair:
                            if debug:
                                print("muonZ2Pair",muonZ2Pair)
                                print("ev.Muon_sip3d[lepPairOneLeadInd]",ev.Muon_sip3d[lepPairOneLeadInd],"ev.Muon_sip3d[lepPairOneTrailingInd]",ev.Muon_sip3d[lepPairOneTrailingInd])
                                print("ev.Muon_sip3d[muonPassesZ2CutsAr[leadZ2LepPairInd][0][0]]",ev.Muon_sip3d[muonPassesZ2CutsAr[leadZ2LepPairInd][0][0]],"ev.Muon_sip3d[muonPassesZ2CutsAr[leadZ2LepPairInd][0][1]]",ev.Muon_sip3d[muonPassesZ2CutsAr[leadZ2LepPairInd][0][1]])
                            if ev.Muon_sip3d[lepPairOneLeadInd] > 4:
                                passesSIPCut = False
                            elif ev.Muon_sip3d[lepPairOneTrailingInd] > 4:
                                passesSIPCut = False
                            elif ev.Muon_sip3d[muonPassesZ2CutsAr[leadZ2LepPairInd][0][0]] > 4:
                                passesSIPCut = False
                            elif ev.Muon_sip3d[muonPassesZ2CutsAr[leadZ2LepPairInd][0][1]] > 4:
                                passesSIPCut = False
                            if debug:
                                print("passesSIPCut",passesSIPCut)
                        else:
                            if debug:
                                print("muonZ2Pair",muonZ2Pair)
                                print("ev.Muon_sip3d[lepPairOneLeadInd]",ev.Muon_sip3d[lepPairOneLeadInd],"ev.Muon_sip3d[lepPairOneTrailingInd]",ev.Muon_sip3d[lepPairOneTrailingInd])
                                print("ev.Electron_sip3d[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]]",ev.Electron_sip3d[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]],"ev.Electron_sip3d[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]]",ev.Electron_sip3d[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]])
                            if ev.Muon_sip3d[lepPairOneLeadInd] > 4:
                                passesSIPCut = False
                            elif ev.Muon_sip3d[lepPairOneTrailingInd] > 4:
                                passesSIPCut = False
                            elif ev.Electron_sip3d[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]] > 4:
                                passesSIPCut = False
                            elif ev.Electron_sip3d[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]] > 4:
                                passesSIPCut = False
                            if debug:
                                print("passesSIPCut",passesSIPCut)
                    elif muonZ2Pair:
                        if debug:
                            print("muonLeading",muonLeading)
                            print("muonZ2Pair",muonZ2Pair)
                            print("ev.Electron_sip3d[lepPairOneLeadInd]",ev.Electron_sip3d[lepPairOneLeadInd],"ev.Electron_sip3d[lepPairOneTrailingInd]",ev.Electron_sip3d[lepPairOneTrailingInd])
                            print("ev.Muon_sip3d[muonPassesZ2CutsAr[leadZ2LepPairInd][0][0]]",ev.Muon_sip3d[muonPassesZ2CutsAr[leadZ2LepPairInd][0][0]],"ev.Muon_sip3d[muonPassesZ2CutsAr[leadZ2LepPairInd][0][1]]",ev.Muon_sip3d[muonPassesZ2CutsAr[leadZ2LepPairInd][0][1]])
                        #print("lepPairOneLeadInd",lepPairOneLeadInd,"len(ev.Electron_sip3d)",len(ev.Electron_sip3d))
                        #print("len(ev.Electron_pt)",len(ev.Electron_pt))
                        #print("nElecCandidates",nElecCandidates,"nMuonCandidates",nMuonCandidates,"enoughLepCands",enoughLepCands,"enoughElecCands",enoughElecCands,"enoughMuonCands",enoughMuonCands)
                        #print("leadLepPairOneVec",leadLepPairOneVec,"trailingLepPairOneVec",trailingLepPairOneVec)
                        #print("muonLeading",muonLeading,"muonZ2Pair",muonZ2Pair)
                        #print()
                        if ev.Electron_sip3d[lepPairOneLeadInd] > 4:
                            passesSIPCut = False
                        elif ev.Electron_sip3d[lepPairOneTrailingInd] > 4:
                            passesSIPCut = False
                        elif ev.Muon_sip3d[muonPassesZ2CutsAr[leadZ2LepPairInd][0][0]] > 4:
                            passesSIPCut = False
                        elif ev.Muon_sip3d[muonPassesZ2CutsAr[leadZ2LepPairInd][0][1]] > 4:
                            passesSIPCut = False
                        if debug:
                            print("passesSIPCut",passesSIPCut)
                    else:
                        if debug:
                            print("muonLeading",muonLeading)
                            print("muonZ2Pair",muonZ2Pair)
                            print("ev.Electron_sip3d[lepPairOneLeadInd]",ev.Electron_sip3d[lepPairOneLeadInd],"ev.Electron_sip3d[lepPairOneTrailingInd]",ev.Electron_sip3d[lepPairOneTrailingInd])
                            print("ev.Electron_sip3d[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]]",ev.Electron_sip3d[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]],"ev.Electron_sip3d[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]]",ev.Electron_sip3d[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]])
                        if ev.Electron_sip3d[lepPairOneLeadInd] > 4:
                            passesSIPCut = False
                        elif ev.Electron_sip3d[lepPairOneTrailingInd] > 4:
                            passesSIPCut = False
                        elif ev.Electron_sip3d[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]] > 4:
                            passesSIPCut = False
                        elif ev.Electron_sip3d[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]] > 4:
                            passesSIPCut = False
                        if debug:
                            print("passesSIPCut",passesSIPCut)
                    """
                    #Now just check that the Z1 and Z2 inv mass falls within the Z low and Z high cuts (60 and 120GeV)
                    if passesSIPCut:
                        if debug:
                            print("passed SIP Cut")
                        allCutPassCount += 1
                                

        #Increment event count
        evCount += 1



print("Finished file loop.","time:",time.time()-startt)
print("Number of events with at least one Z1Z2 pair passing all cuts:",allCutPassCount)

if not isBackground:
    print("Cross section average before division:",crossSectionAvg)
    print("Cross section counter:",crossSectionCtr)
    crossSectionAvg = crossSectionAvg / crossSectionCtr
    print("Cross section average after division:",crossSectionAvg)
    #XS Tree
    crossSectionVar = array('f',[0.])
    crossSectionTree = TTree('crossSectionTree', 'crossSectionTree')
    crossSectionTree.Branch("crossSectionVar",crossSectionVar,"crossSectionVar/F")
    crossSectionVar[0] = crossSectionAvg
    crossSectionTree.Fill()
    crossSectionTree.Write("",TObject.kOverwrite)

outFile.cd()
cutZeroTree.Write("",TObject.kOverwrite)
cutOneTree.Write("",TObject.kOverwrite)
cutTwoTree.Write("",TObject.kOverwrite)
cutThreeTree.Write("",TObject.kOverwrite)
cutFourTree.Write("",TObject.kOverwrite)



outFile.Close()

print("Done.","time:",time.time()-startt)