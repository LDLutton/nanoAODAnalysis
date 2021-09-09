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
import sys

print("arglist:",sys.argv)
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

testRun = False
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
if len(sys.argv) > 1:
    tmpArgStr = sys.argv[1]
    if tmpArgStr == "testRun":
        testRun = True
    elif tmpArgStr == "MGSM":
        MGSM = True
    elif tmpArgStr == "MGEFT":
        MGEFT = True
    elif tmpArgStr == "ttHToBBBackground":
        ttHToBBBackground = True
    elif tmpArgStr == "ttZJetsBackground":
        ttZJetsBackground = True
    elif tmpArgStr == "DYBackground":
        DYBackground = True
    elif tmpArgStr == "QCDPT170to300Background":
        QCDPT170to300Background = True
    elif tmpArgStr == "QCDPT300to470Background":
        QCDPT300to470Background = True
    elif tmpArgStr == "QCDPT470to600Background":
        QCDPT470to600Background = True
    elif tmpArgStr == "QCDPT600to800Background":
        QCDPT600to800Background = True
    elif tmpArgStr == "QCDPT800to1000Background":
        QCDPT800to1000Background = True
    elif tmpArgStr == "QCDPT1000to1400Background":
        QCDPT1000to1400Background = True
    elif tmpArgStr == "QCDPT1400to1800Background":
        QCDPT1400to1800Background = True
    elif tmpArgStr == "QCDPT1800to2400Background":
        QCDPT1800to2400Background = True
    elif tmpArgStr == "QCDPT2400to3200Background":
        QCDPT2400to3200Background = True
    elif tmpArgStr == "QCDPT3200toInfBackground":
        QCDPT3200toInfBackground = True



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


def countPotentialElecPairs(ev,nElectronInt):
    nElecCandidatesNeg = 0
    nElecCandidatesPos = 0
    for i in range(nElectronInt):
        if ev.Electron_charge[i] == -1:
            nElecCandidatesNeg += 1
        else:
            nElecCandidatesPos += 1
            
    nElecCandPairs = 0
    if nElecCandidatesNeg <= nElecCandidatesPos:
        nElecCandPairs = nElecCandidatesNeg
    else:
        nElecCandPairs = nElecCandidatesPos
    return nElecCandPairs

def countPotentialMuonPairs(ev,nMuonInt):
    nMuonCandidatesNeg = 0
    nMuonCandidatesPos = 0
    for i in range(nMuonInt):
        if ev.Muon_charge[i] == -1:
            nMuonCandidatesNeg += 1
        else:
            nMuonCandidatesPos += 1
            
    nMuonCandPairs = 0
    if nMuonCandidatesNeg <= nMuonCandidatesPos:
        nMuonCandPairs = nMuonCandidatesNeg
    else:
        nMuonCandPairs = nMuonCandidatesPos
    return nMuonCandPairs

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
else:
    print("ERROR. NO INPUT DATASET NAME GIVEN")





#Initializing counter variables
evCount = 0

#Setting up outfile for tree
outFile = TFile("FoMTreesFrom{0}_InputTrimmed.root".format(saveName),"recreate")

#Tree for holding the number of events run over
#and the number of events that passed the cut
evNumTree = TTree('evNumTree','evNumTree')
nEv = array('i',[0])
nEvPass = array('i',[0])
evNumTree.Branch("nEv",nEv,"nEv/I")
evNumTree.Branch("nEvPass",nEvPass,"nEvPass/I")




#Initial with no cuts but for checking that there are enough potential candidates. Information needed:
#Electron/Muon eta, Pt, and the HLT triggers

########### FULL PASS TREE ############
neLep = array('i',[0])
eCharge = array('i',[0])
eEta = array('f',[0.])
ePt = array('f',[0.])
eMass = array('f',[0.])
eHLT = array('B',[0])

nmLep = array('i',[0])
mCharge = array('i',[0])
mEta = array('f',[0.])
mPt = array('f',[0.])
mMass = array('f',[0.])
mHLT = array('B',[0])

emHLT = array('B',[0])



cutTree = TTree('cutTree', 'cutTree')

cutTree.Branch("neLep",neLep,"neLep/I")
cutTree.Branch("eCharge",eCharge,"eCharge[neLep]/I")
cutTree.Branch("eEta",eEta,"eEta[neLep]/F")
cutTree.Branch("ePt",ePt,"ePt[neLep]/F")
cutTree.Branch("eMass",eMass,"eMass[neLep]/F")
cutTree.Branch("eHLT",eHLT,"eHLT/O")
cutTree.Branch("nmLep",nmLep,"nmLep/I")
cutTree.Branch("mCharge",mCharge,"mCharge[nmLep]/I")
cutTree.Branch("mEta",mEta,"mEta[nmLep]/F")
cutTree.Branch("mPt",mPt,"mPt[nmLep]/F")
cutTree.Branch("mMass",mMass,"mMass[nmLep]/F")
cutTree.Branch("mHLT",mHLT,"mHLT/O")

cutTree.Branch("emHLT",emHLT,"emHLT/O")

#isolations for each lepton

eIso = array('f',[0.])
mIso = array('f',[0.])

cutTree.Branch("eIso",eIso,"eIso[neLep]/F")
cutTree.Branch("mIso",mIso,"mIso[nmLep]/F")

#SIP for each lepton
eSIP = array('f',[0.])
mSIP = array('f',[0.])

cutTree.Branch("eSIP",eSIP,"eSIP[neLep]/F")
cutTree.Branch("mSIP",mSIP,"mSIP[nmLep]/F")

########### FULL PASS TREE ############


#####UNDER CONSTRUCTION#####







crossSectionAvg = 0
crossSectionCtr = 0
evRunOver = 0
evPassCount = 0
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
        

        #number of electrons and muons and the sum
        tmpnElectron = ev.nElectron
        tmpnMuon = ev.nMuon
        leptonSum = tmpnElectron+tmpnMuon


        #####CHECKING THAT EVENT PASSES MOST BASIC LEPTON CHECKS#####
        if leptonSum >= 4:
            nElecCandPairs = 0
            if tmpnElectron >=2:
                nElecCandPairs = countPotentialElecPairs(ev,tmpnElectron)
            
            nMuonCandPairs = 0
            if tmpnMuon >= 2:
                nMuonCandPairs = countPotentialMuonPairs(ev,tmpnMuon)
            if nElecCandPairs + nMuonCandPairs >= 2:
                evPassCount += 1

                
                #First fill electrons if any pairs

                if nElecCandPairs > 0:
                    elecHLTPass = ev.HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL or ev.HLT_DoubleEle25_CaloIdL_MW
                    
                    eHLT[0] = elecHLTPass
                    neLep[0] = tmpnElectron
                    eEta = array('f',[0.]*tmpnElectron)
                    ePt = array('f',[0.]*tmpnElectron)
                    eMass = array('f',[0.]*tmpnElectron)
                    eCharge = array('i',[0]*tmpnElectron)
                    eIso = array('f',[0.]*tmpnElectron)
                    eSIP = array('f',[0.]*tmpnElectron)
                    for i in range(tmpnElectron):
                        tmpPt = ev.Electron_pt[i]
                        tmpEta = ev.Electron_eta[i]
                        eEta[i] = tmpEta
                        eMass[i] = ev.Electron_mass[i]
                        ePt[i] = tmpPt
                        eCharge[i] = ev.Electron_charge[i]
                        if tmpPt > 35:
                            if abs(ev.Electron_eta[i]) < 1.4:
                                tmpAdd = max(0., ev.Electron_dr03EcalRecHitSumEt[i] - 1.)
                            else:
                                tmpAdd = ev.Electron_dr03EcalRecHitSumEt[i]
                            tmpIso = ( ev.Electron_dr03TkSumPt[i] + tmpAdd + ev.Electron_dr03HcalDepth1TowerSumEt[i] ) / ev.Electron_pt[i]
                        else:
                            tmpIso = ev.Electron_pfRelIso03_all[i]
                        eIso[i] = tmpIso
                        eSIP[i] = ev.Electron_sip3d[i]
                else:
                    neLep[0] = 0
                    eHLT[0] = False
                    eEta = 0
                    ePt  = 0
                    eMass = 0
                    eCharge = 0
                    eIso = 0
                    eSIP = 0
                
                #Now muons
                if nMuonCandPairs > 0:
                    muonHLTPass = ev.HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8 or ev.HLT_TripleMu_10_5_5_DZ or ev.HLT_TripleMu_12_10_5

                    
                    mHLT[0] = muonHLTPass
                    nmLep[0] = tmpnMuon
                    mEta = array('f',[0.]*tmpnMuon)
                    mPt = array('f',[0.]*tmpnMuon)
                    mMass = array('f',[0.]*tmpnMuon)
                    mCharge = array('i',[0]*tmpnMuon)
                    mIso = array('f',[0.]*tmpnMuon)
                    mSIP = array('f',[0.]*tmpnMuon)
                    for i in range(tmpnMuon):
                        tmpPt = ev.Muon_pt[i]
                        tmpEta = ev.Muon_eta[i]
                        mEta[i] = tmpEta
                        mMass[i] = ev.Muon_mass[i]
                        mPt[i] = tmpPt
                        mCharge[i] = ev.Muon_charge[i]
                        mIso[i] = ev.Muon_pfRelIso03_all[i]
                        mSIP[i] = ev.Muon_sip3d[i]
                else:
                    nmLep[0] = 0
                    mHLT[0] = False
                    mEta = 0
                    mPt  = 0
                    mMass = 0
                    mCharge = 0
                    mIso = 0
                    mSIP = 0
                
                emHLTPass = ev.HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL or ev.HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ or ev.HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ or ev.HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ or ev.HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ or ev.HLT_Mu8_DiEle12_CaloIdL_TrackIdL_DZ
                cutTree.Fill()
                                

        #Increment event count
        evRunOver += 1
        evCount += 1

nEv[0] = evRunOver
nEvPass[0] = evPassCount
evNumTree.Fill()




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
evNumTree.Write("",TObject.kOverwrite)
cutTree.Write("",TObject.kOverwrite)



outFile.Close()

print("Done.","time:",time.time()-startt)