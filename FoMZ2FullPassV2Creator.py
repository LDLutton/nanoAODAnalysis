import datetime
from array import array
from math import sqrt
from ROOT import TFile, TChain, gDirectory, TApplication, TMath, Math, TMinuit, TROOT, TSystem, TTree, TVector2
from ROOT import THStack, TH1D, TCanvas, TPad, TF1, TGraph, TGraphErrors, TLegend, TLine, TPaveText, TStyle
from ROOT import TH2D, TH2F,gPad
from math import sqrt,pi,log
from functionsForFoMPlots import *
import time as time

startt = time.time()

#Extra output at end and for each file
extraOut = False

debug = False
debugMin = 1000
debugMax = 1004
forCondor = False
if forCondor:
    forCondorStr = "/scratch365/dlutton/HistosAndPNGs/"
else:
    forCondorStr = ""

skipEvPassGraphs = False
variableRebin = False
variableRebinVar = 0.3
normalizeBackgroundsTogether = True
sumQCD = True
isQCDAr = []

MGSM = True
MGEFT = True
ttHToBBBackground = True
ttZJetsBackground = True
DYBackground = False
QCDPT170to300Background = True
QCDPT300to470Background = False
QCDPT470to600Background = False
QCDPT600to800Background = False
QCDPT800to1000Background = False
QCDPT1000to1400Background = False
QCDPT1400to1800Background = False
QCDPT1800to2400Background = False
QCDPT2400to3200Background = False
QCDPT3200toInfBackground = False

#All True

"""
MGSM = True
MGEFT = True
ttHToBBBackground = True
ttZJetsBackground = True
DYBackground = True
QCDPT170to300Background = True
QCDPT300to470Background = True
QCDPT470to600Background = True
QCDPT600to800Background = True
QCDPT800to1000Background = True
QCDPT1000to1400Background = True
QCDPT1400to1800Background = True
QCDPT1800to2400Background = True
QCDPT2400to3200Background = True
QCDPT3200toInfBackground = True
"""

XSAr = []
totalEvents = []
fileAr = []
nameAr = []
isSignalAr = []
colorAr = []


saveNameAr = []

if MGSM:
    #fileAr.append(TFile.Open("{0}FoMTreesFrompphzzjjQCD0SMHLOOP0QEDE5NPE0ResMasAllVer100Ev_0p999cHW100GeVIMJetCut.root".format(forCondorStr)))
    fileAr.append(TFile.Open("{0}FoMTreesFrompphzzjjQCD0SMHLOOP0QEDE5NPE0ResMasAllVer100Ev_0p999cHW100GeVIMJetCut_InputTrimmed_FullPass.root".format(forCondorStr)))
    nameAr.append("SM")
    saveNameAr.append("SM")
    colorAr.append(2)
    isSignalAr.append(False)

    SMXSTree = fileAr[-1].crossSectionTree
    tmpXSAvg = 0
    tmpXSCnt = 0
    for SMXS in SMXSTree:
        tmpXSAvg += SMXS.crossSectionVar
        tmpXSCnt += 1
    tmpXSAvg = tmpXSAvg / tmpXSCnt
    XSAr.append(tmpXSAvg)
    #SMCZTree = fileAr[-1].cutZeroTree
    #totalEvents.append(SMCZTree.GetEntries())
    ENTree = fileAr[-1].evNumTree
    evNum = 0
    for ev in ENTree:
        evNum = ev.nEv
    totalEvents.append(evNum)
    isQCDAr.append(False)
if MGEFT:
    #fileAr.append(TFile.Open("{0}FoMTreesFrompphzzjjQCD0SMHLOOP0NPE1NPcHWE1QEDE5ResMasAllVer100Ev_0p999cHW100GeVIMJetCut.root".format(forCondorStr)))
    fileAr.append(TFile.Open("{0}FoMTreesFrompphzzjjQCD0SMHLOOP0NPE1NPcHWE1QEDE5ResMasAllVer100Ev_0p999cHW100GeVIMJetCut_InputTrimmed_FullPass.root".format(forCondorStr)))
    nameAr.append("EFT")
    saveNameAr.append("EFT")
    colorAr.append(6)
    #nameAr.append("EFTC0p1")
    isSignalAr.append(True)
    EFTXSTree = fileAr[-1].crossSectionTree
    tmpXSAvg = 0
    tmpXSCnt = 0
    for EFTXS in EFTXSTree:
        tmpXSAvg += EFTXS.crossSectionVar
        tmpXSCnt += 1
    tmpXSAvg = tmpXSAvg / tmpXSCnt
    #tmpXSAvg = tmpXSAvg*0.1 / tmpXSCnt
    XSAr.append(tmpXSAvg)
    #EFTCZTree = fileAr[-1].cutZeroTree
    #totalEvents.append(EFTCZTree.GetEntries())
    ENTree = fileAr[-1].evNumTree
    evNum = 0
    for ev in ENTree:
        evNum = ev.nEv
    totalEvents.append(evNum)
    isQCDAr.append(False)

if ttHToBBBackground:
    #fileAr.append(TFile.Open("{0}FoMTreesFromttHToBBBackground.root".format(forCondorStr)))
    fileAr.append(TFile.Open("{0}FoMTreesFromttHToBBBackground_InputTrimmed_FullPass.root".format(forCondorStr)))
    nameAr.append("ttHToBBBackground")
    saveNameAr.append("ttHToBB")
    colorAr.append(7)
    isSignalAr.append(False)
    tmpXSAvg = 0.5071*0.582
    XSAr.append(tmpXSAvg)
    #tmpCZTree = fileAr[-1].cutZeroTree
    #totalEvents.append(tmpCZTree.GetEntries())
    ENTree = fileAr[-1].evNumTree
    evNum = 0
    for ev in ENTree:
        evNum = ev.nEv
    totalEvents.append(evNum)
    isQCDAr.append(False)
if ttZJetsBackground:
    fileAr.append(TFile.Open("{0}FoMTreesFromttZJetsBackground_InputTrimmed_FullPass.root".format(forCondorStr)))
    nameAr.append("ttZJetsBackground")
    saveNameAr.append("ttZJets")
    colorAr.append(4)
    isSignalAr.append(False)
    tmpXSAvg = 0.5407
    XSAr.append(tmpXSAvg)
    #tmpCZTree = fileAr[-1].cutZeroTree
    #totalEvents.append(tmpCZTree.GetEntries())
    ENTree = fileAr[-1].evNumTree
    evNum = 0
    for ev in ENTree:
        evNum = ev.nEv
    totalEvents.append(evNum)
    isQCDAr.append(False)


if DYBackground:
    fileAr.append(TFile.Open("{0}FoMTreesFromDYBackground_InputTrimmed_FullPass.root".format(forCondorStr)))
    nameAr.append("DYBackground")
    saveNameAr.append("DY")
    colorAr.append(8)
    isSignalAr.append(False)
    tmpXSAvg = 5364
    XSAr.append(tmpXSAvg)
    #tmpCZTree = fileAr[-1].cutZeroTree
    #totalEvents.append(tmpCZTree.GetEntries())
    ENTree = fileAr[-1].evNumTree
    evNum = 0
    for ev in ENTree:
        evNum = ev.nEv
    totalEvents.append(evNum)
    isQCDAr.append(False)


if QCDPT170to300Background:
    fileAr.append(TFile.Open("{0}FoMTreesFromQCDPT170to300Background_InputTrimmed_FullPass.root".format(forCondorStr)))
    nameAr.append("QCDPT170to300Background")
    saveNameAr.append("QCD0")
    isSignalAr.append(False)
    colorAr.append(1)
    tmpXSAvg = 103300.0
    XSAr.append(tmpXSAvg)
    #tmpCZTree = fileAr[-1].cutZeroTree
    #totalEvents.append(tmpCZTree.GetEntries())
    ENTree = fileAr[-1].evNumTree
    evNum = 0
    for ev in ENTree:
        evNum = ev.nEv
    totalEvents.append(evNum)
    isQCDAr.append(True)
if QCDPT300to470Background:
    fileAr.append(TFile.Open("{0}FoMTreesFromQCDPT300to470Background_InputTrimmed_FullPass.root".format(forCondorStr)))
    nameAr.append("QCDPT300to470Background")
    saveNameAr.append("QCD1")
    isSignalAr.append(False)
    colorAr.append(8)
    tmpXSAvg = 6826.0
    XSAr.append(tmpXSAvg)
    #tmpCZTree = fileAr[-1].cutZeroTree
    #totalEvents.append(tmpCZTree.GetEntries())
    ENTree = fileAr[-1].evNumTree
    evNum = 0
    for ev in ENTree:
        evNum = ev.nEv
    totalEvents.append(evNum)
    isQCDAr.append(True)
if QCDPT470to600Background:
    fileAr.append(TFile.Open("{0}FoMTreesFromQCDPT470to600Background_InputTrimmed_FullPass.root".format(forCondorStr)))
    nameAr.append("QCDPT470to600Background")
    saveNameAr.append("QCD2")
    colorAr.append(9)
    isSignalAr.append(False)
    tmpXSAvg = 552.6
    XSAr.append(tmpXSAvg)
    ENTree = fileAr[-1].evNumTree
    evNum = 0
    for ev in ENTree:
        evNum = ev.nEv
    totalEvents.append(evNum)
    isQCDAr.append(True)
if QCDPT600to800Background:
    fileAr.append(TFile.Open("{0}FoMTreesFromQCDPT600to800Background_InputTrimmed_FullPass.root".format(forCondorStr)))
    nameAr.append("QCDPT600to800Background")
    saveNameAr.append("QCD3")
    colorAr.append(10)
    isSignalAr.append(False)
    tmpXSAvg = 156.6
    XSAr.append(tmpXSAvg)
    ENTree = fileAr[-1].evNumTree
    evNum = 0
    for ev in ENTree:
        evNum = ev.nEv
    totalEvents.append(evNum)
    isQCDAr.append(True)
if QCDPT800to1000Background:
    fileAr.append(TFile.Open("{0}FoMTreesFromQCDPT800to1000Background_InputTrimmed_FullPass.root".format(forCondorStr)))
    nameAr.append("QCDPT800to1000Background")
    saveNameAr.append("QCD4")
    colorAr.append(11)
    isSignalAr.append(False)
    tmpXSAvg = 26.32
    XSAr.append(tmpXSAvg)
    ENTree = fileAr[-1].evNumTree
    evNum = 0
    for ev in ENTree:
        evNum = ev.nEv
    totalEvents.append(evNum)
    isQCDAr.append(True)
if QCDPT1000to1400Background:
    fileAr.append(TFile.Open("{0}FoMTreesFromQCDPT1000to1400Background_InputTrimmed_FullPass.root".format(forCondorStr)))
    nameAr.append("QCDPT1000to1400Background")
    saveNameAr.append("QCD5")
    colorAr.append(12)
    isSignalAr.append(False)
    tmpXSAvg = 7.5
    XSAr.append(tmpXSAvg)
    ENTree = fileAr[-1].evNumTree
    evNum = 0
    for ev in ENTree:
        evNum = ev.nEv
    totalEvents.append(evNum)
    isQCDAr.append(True)
if QCDPT1400to1800Background:
    fileAr.append(TFile.Open("{0}FoMTreesFromQCDPT1400to1800Background_InputTrimmed_FullPass.root".format(forCondorStr)))
    nameAr.append("QCDPT1400to1800Background")
    saveNameAr.append("QCD6")
    isSignalAr.append(False)
    colorAr.append(13)
    tmpXSAvg = 0.6479
    XSAr.append(tmpXSAvg)
    ENTree = fileAr[-1].evNumTree
    evNum = 0
    for ev in ENTree:
        evNum = ev.nEv
    totalEvents.append(evNum)
    isQCDAr.append(True)
if QCDPT1800to2400Background:
    fileAr.append(TFile.Open("{0}FoMTreesFromQCDPT1800to2400Background_InputTrimmed_FullPass.root".format(forCondorStr)))
    nameAr.append("QCDPT1800to2400Background")
    saveNameAr.append("QCD7")
    isSignalAr.append(False)
    colorAr.append(14)
    tmpXSAvg = 0.08715
    XSAr.append(tmpXSAvg)
    ENTree = fileAr[-1].evNumTree
    evNum = 0
    for ev in ENTree:
        evNum = ev.nEv
    totalEvents.append(evNum)
    isQCDAr.append(True)
if QCDPT2400to3200Background:
    fileAr.append(TFile.Open("{0}FoMTreesFromQCDPT2400to3200Background_InputTrimmed_FullPass.root".format(forCondorStr)))
    nameAr.append("QCDPT2400to3200Background")
    saveNameAr.append("QCD8")
    isSignalAr.append(False)
    colorAr.append(15)
    tmpXSAvg = 0.005242
    XSAr.append(tmpXSAvg)
    ENTree = fileAr[-1].evNumTree
    evNum = 0
    for ev in ENTree:
        evNum = ev.nEv
    totalEvents.append(evNum)
    isQCDAr.append(True)
if QCDPT3200toInfBackground:
    fileAr.append(TFile.Open("{0}FoMTreesFromQCDPT3200toInfBackground_InputTrimmed_FullPass.root".format(forCondorStr)))
    nameAr.append("QCDPT3200toInfBackground")
    saveNameAr.append("QCD9")
    isSignalAr.append(False)
    colorAr.append(16)
    tmpXSAvg = 0.0001349
    XSAr.append(tmpXSAvg)
    ENTree = fileAr[-1].evNumTree
    evNum = 0
    for ev in ENTree:
        evNum = ev.nEv
    totalEvents.append(evNum)
    isQCDAr.append(True)


weightsAr = [tmpXS/tmpEvs for tmpXS,tmpEvs in zip(XSAr,totalEvents)]

cutAmnt = 100
binAmnt = 20

ePtCut = 7
eEtaCut = 2.5

mPtCut = 5
mEtaCut = 2.4
invMassCutLow=60
invMassCutHigh=120
ptLeadCut=20
ptTrailingCut=10

ZMass = 91.1876
fourLepInvMassCut = 100
Z2FourLepRange = [0,1400]

Z2FourLepStep = (Z2FourLepRange[1]-Z2FourLepRange[0])/cutAmnt
Z2FourLepSignalAr = [0 for i in range(cutAmnt)] 
Z2FourLepBackgroundAr = [0 for i in range(cutAmnt)] 

optLepInvMassCut = 12
Z2OptLepRange = [0,400]
Z2OptLepStep = (Z2OptLepRange[1]-Z2OptLepRange[0])/cutAmnt
Z2OptLepSignalAr = [0 for i in range(cutAmnt)] 
Z2OptLepBackgroundAr = [0 for i in range(cutAmnt)] 

lepIsoCut = 0.35


SIPCut = 4



Z2FourLepEvPassGraphAr = []
Z2OptLepEvPassGraphAr = []
for nameA in nameAr:
    Z2FourLepEvPassGraphAr.append(array('d'))
    Z2OptLepEvPassGraphAr.append(array('d'))

histZ2FourLepAr = []
histZ2OptLepAr = []

#fileAr.append(TFile.Open("FoMTreesFrompphzzjjQCD0SMHLOOP0NPE1NPcHWE1QEDE5ResMasAllVer100Ev_0p999cHW100GeVIMJetCut_InputTrimmed_FullPass.root"))
#isSignalAr.append(True)
#fileAr.append(TFile.Open("FoMTreesFrompphzzjjQCD0SMHLOOP0QEDE5NPE0ResMasAllVer100Ev_0p999cHW100GeVIMJetCut_InputTrimmed_FullPass.root"))
#isSignalAr.append(False)

#################################BUILDING NEW LOOP HERE

#passesCandCutsCtr = 0
#passesZ1CutsCtr = 0
#passesZ2CutsCtr = 0
#passesIsoCutCtr = 0
#passesAllCutsCtr = 0
#allPassAr = []
#MAIN LOOP
for k,fileA in enumerate(fileAr):
    print("Entering file {0}".format(k))
    CTree = fileA.cutTree
    tmpZ2FourLepCntAr = [0 for cutItr in range(cutAmnt)]
    histZ2FourLepAr.append(TH1D("Z2FourLepHist{0}".format(nameAr[k]),"Z2FourLepHist{0}".format(nameAr[k]), binAmnt, Z2FourLepRange[0], Z2FourLepRange[1]))
    tmpZ2OptLepCntAr = [0 for cutItr in range(cutAmnt)]
    histZ2OptLepAr.append(TH1D("Z2OptLepHist{0}".format(nameAr[k]),"Z2OptLepHist{0}".format(nameAr[k]), binAmnt, Z2OptLepRange[0], Z2OptLepRange[1]))
    #LOOP OVER EVENTS IN FILE k
    for j,ev in enumerate(CTree):
        if debug:
            if j < debugMin:
                continue
            if j > debugMax:
                break
        if j % 10000 == 0:
            print("event {0} in file {1}".format(j,k))
        #First SIP cut
        neLep = ev.neLep
        enoughElecCands = False
        negElecCands = 0
        posElecCands = 0
        totElecCands = 0
        elecCandIndAr = []
        elecCandVecAr = []
        elecCandChargeAr = []
        eHLT = 0
        mHLT = 0
        emHLT = 0
        
        if neLep:
            eHLT = ev.eHLT
            emHLT = ev.emHLT
            if eHLT or emHLT:
                doeCandCut(ev,neLep,elecCandIndAr,elecCandVecAr,elecCandChargeAr,ePtCut,eEtaCut)
                for elecCandCharge in elecCandChargeAr:
                    if elecCandCharge == -1:
                        negElecCands += 1
                    else:
                        posElecCands += 1
                totElecCands = min(negElecCands,posElecCands)
                if totElecCands >= 1:
                    enoughElecCands = True


        enoughMuonCands = False
        negMuonCands = 0
        posMuonCands = 0
        totMuonCands = 0
        muonCandIndAr = []
        muonCandVecAr = []
        muonCandChargeAr = []
        nmLep = ev.nmLep
        if debug:
            print("--------------------------------------------")
            print("j",j,"ev.evInd",ev.evInd,"neLep",neLep)
            for tmpItr in range(neLep):
                print("tmpItr",tmpItr,"ev.ePt[tmpItr]",ev.ePt[tmpItr],"ev.eEta[tmpItr]",ev.eEta[tmpItr],"ev.eCharge[tmpItr]",ev.eCharge[tmpItr])
        if nmLep:
            mHLT = ev.mHLT
            emHLT = ev.emHLT
            if mHLT or emHLT:
                domCandCut(ev,nmLep,muonCandIndAr,muonCandVecAr,muonCandChargeAr,mPtCut,mEtaCut)
                for muonCandCharge in muonCandChargeAr:
                    if muonCandCharge == -1:
                        negMuonCands += 1
                    else:
                        posMuonCands += 1
                totMuonCands = min(negMuonCands,posMuonCands)
                if totMuonCands >= 1:
                    enoughMuonCands = True
        enoughLepCands = False
        if totElecCands+totMuonCands >= 2:
            enoughLepCands = True
        if debug:
            print("eHLT",eHLT,"negElecCands",negElecCands,"posElecCands",posElecCands,"totElecCands",totElecCands)
            print("nmLep",nmLep,"mHLT",mHLT,"negMuonCands",negMuonCands,"posMuonCands",posMuonCands,"totMuonCands",totMuonCands)
            print("emHLT",emHLT,"enoughLepCands",enoughLepCands)
        Z1Cand = False
        difFromZMassOne = 1000
        Z1LeadItr = -1
        Z1TrailingItr = -1
        Z1LeadPt = 0
        Z1TrailingPt = 0
        Z1IsMuon = False
        Z1LeadVec = 0
        Z1TrailingVec = 0
        Z1LeadCharge = 0
        Z1TrailingCharge = 0
        if enoughLepCands: #Check there are enough lep cands after candidate cuts
            #passesCandCutsCtr += 1
            elecPassesZ2CutsAr = []
            if enoughElecCands: #If enough elec cands, run Z1 cuts
                Z1LeadItr,Z1TrailingItr,Z1LeadPt,Z1TrailingPt,Z1LeadVec,Z1TrailingVec,Z1LeadCharge,Z1TrailingCharge,Z1IsMuon,difFromZMassOne = doeZ1Cut(ev,elecCandIndAr,elecCandVecAr,elecCandChargeAr,elecPassesZ2CutsAr,Z1IsMuon,invMassCutLow,invMassCutHigh,ptLeadCut,ptTrailingCut,Z1LeadPt,Z1TrailingPt,Z1LeadItr,Z1TrailingItr,Z1LeadVec,Z1TrailingVec,Z1LeadCharge,Z1TrailingCharge,difFromZMassOne)
            muonPassesZ2CutsAr = []
            if enoughMuonCands: #If enough muon cands, run Z1 cuts
                
                Z1LeadItr,Z1TrailingItr,Z1LeadPt,Z1TrailingPt,Z1LeadVec,Z1TrailingVec,Z1LeadCharge,Z1TrailingCharge,Z1IsMuon,difFromZMassOne = domZ1Cut(ev,muonCandIndAr,muonCandVecAr,muonCandChargeAr,muonPassesZ2CutsAr,Z1IsMuon,invMassCutLow,invMassCutHigh,ptLeadCut,ptTrailingCut,Z1LeadPt,Z1TrailingPt,Z1LeadItr,Z1TrailingItr,Z1LeadVec,Z1TrailingVec,Z1LeadCharge,Z1TrailingCharge,difFromZMassOne)
            if debug:
                print("Z1LeadItr",Z1LeadItr,"Z1TrailingItr",Z1TrailingItr,"Z1LeadPt",Z1LeadPt,"Z1TrailingPt",Z1TrailingPt,"Z1LeadVec",Z1LeadVec,"Z1TrailingVec",Z1TrailingVec,"Z1LeadCharge",Z1LeadCharge,"Z1TrailingCharge",Z1TrailingCharge,"Z1IsMuon",Z1IsMuon,"difFromZMassOne",difFromZMassOne)
            if Z1LeadItr >= 0: #If Z1 found
                #passesZ1CutsCtr += 1
                if debug:
                    print("passed Z1 cut. checking for enough Z2 now")
                if not Z1IsMuon: #If Z1 is electron, then remove any instances of Z1 particles from electron Z2 candidate pairs
                    elecPassesZ2CutsFinalAr = []
                    eZ2VecPairAr = []
                    eZ2PtPairAr = []
                    eZ2ChargePairAr = []
                    for elecPassesZ2CutsPair in elecPassesZ2CutsAr: #Loop through elec Z2 cand pairs to fill all arrays
                        if not Z1LeadItr in elecPassesZ2CutsPair and not Z1TrailingItr in elecPassesZ2CutsPair:
                            elecPassesZ2CutsFinalAr.append(elecPassesZ2CutsPair)
                            eZ2ChargePairAr.append([elecCandChargeAr[elecPassesZ2CutsPair[0]],elecCandChargeAr[elecPassesZ2CutsPair[1]]])
                            tmpVecOne = elecCandVecAr[elecPassesZ2CutsPair[0]]
                            tmpVecTwo = elecCandVecAr[elecPassesZ2CutsPair[1]]
                            eZ2PtPairAr.append([tmpVecOne.Pt(),tmpVecTwo.Pt()])
                            eZ2VecPairAr.append([tmpVecOne,tmpVecTwo])
                            eZ2ChargePairAr.append([elecCandChargeAr[elecPassesZ2CutsPair[0]],elecCandChargeAr[elecPassesZ2CutsPair[1]]])

                    muonPassesZ2CutsFinalAr = muonPassesZ2CutsAr
                    mZ2VecPairAr = []
                    mZ2PtPairAr = []
                    mZ2ChargePairAr = []
                    for muonPassesZ2CutsPair in muonPassesZ2CutsAr: #Loop through muon Z2 cand pairs to fill vector, pt, and charge arrays
                        mZ2ChargePairAr.append([muonCandChargeAr[muonPassesZ2CutsPair[0]],muonCandChargeAr[muonPassesZ2CutsPair[1]]])
                        tmpVecOne = muonCandVecAr[muonPassesZ2CutsPair[0]]
                        tmpVecTwo = muonCandVecAr[muonPassesZ2CutsPair[1]]
                        mZ2PtPairAr.append([tmpVecOne.Pt(),tmpVecTwo.Pt()])
                        mZ2VecPairAr.append([tmpVecOne,tmpVecTwo])
                        mZ2ChargePairAr.append([muonCandChargeAr[muonPassesZ2CutsPair[0]],muonCandChargeAr[muonPassesZ2CutsPair[1]]])

                else: #If Z1 is muon, then remove any instances of Z1 particles from muon Z2 candidate pairs
                    muonPassesZ2CutsFinalAr = []
                    mZ2VecPairAr = []
                    mZ2PtPairAr = []
                    mZ2ChargePairAr = []
                    for muonPassesZ2CutsPair in muonPassesZ2CutsAr: #Loop through muon Z2 cand pairs to fill all arrays
                        if not Z1LeadItr in muonPassesZ2CutsPair and not Z1TrailingItr in muonPassesZ2CutsPair:
                            muonPassesZ2CutsFinalAr.append(muonPassesZ2CutsPair)
                            mZ2ChargePairAr.append([muonCandChargeAr[muonPassesZ2CutsPair[0]],muonCandChargeAr[muonPassesZ2CutsPair[1]]])
                            tmpVecOne = muonCandVecAr[muonPassesZ2CutsPair[0]]
                            tmpVecTwo = muonCandVecAr[muonPassesZ2CutsPair[1]]
                            mZ2PtPairAr.append([tmpVecOne.Pt(),tmpVecTwo.Pt()])
                            mZ2VecPairAr.append([tmpVecOne,tmpVecTwo])
                            mZ2ChargePairAr.append([muonCandChargeAr[muonPassesZ2CutsPair[0]],muonCandChargeAr[muonPassesZ2CutsPair[1]]])

                    elecPassesZ2CutsFinalAr = elecPassesZ2CutsAr
                    eZ2VecPairAr = []
                    eZ2PtPairAr = []
                    eZ2ChargePairAr = []
                    for elecPassesZ2CutsPair in elecPassesZ2CutsAr: #Loop through elec Z2 cand pairs to fill vector, pt, and charge arrays
                        eZ2ChargePairAr.append([elecCandChargeAr[elecPassesZ2CutsPair[0]],elecCandChargeAr[elecPassesZ2CutsPair[1]]])
                        tmpVecOne = elecCandVecAr[elecPassesZ2CutsPair[0]]
                        tmpVecTwo = elecCandVecAr[elecPassesZ2CutsPair[1]]
                        eZ2PtPairAr.append([tmpVecOne.Pt(),tmpVecTwo.Pt()])
                        eZ2VecPairAr.append([tmpVecOne,tmpVecTwo])
                        eZ2ChargePairAr.append([elecCandChargeAr[elecPassesZ2CutsPair[0]],elecCandChargeAr[elecPassesZ2CutsPair[1]]])

                if debug:
                    tmpPtAr = []
                    tmpVecAr = []
                    #for elecCandInd in elecCandIndAr:
                    print("elecCandIndAr",elecCandIndAr)
                    print("elecCandChargeAr",elecCandChargeAr)
                    print("elecCandVecAr",elecCandVecAr)
                    for elecCandVecItrOne,elecCandVecOne in enumerate(elecCandVecAr[:-1]):
                        print("elecCandVecItrOne",elecCandVecItrOne,"elecCandVecOne",elecCandVecOne)
                        for elecCandVecItrTwo,elecCandVecTwo in enumerate(elecCandVecAr[elecCandVecItrOne+1:]):
                            print("elecCandVecItrTwo",elecCandVecItrOne+ 1+ elecCandVecItrTwo,"elecCandVecTwo",elecCandVecTwo)
                            tmpVecSum = elecCandVecOne +elecCandVecTwo
                            print(tmpVecSum)
                            print(tmpVecSum.M())
                    print("elecPassesZ2CutsAr",elecPassesZ2CutsAr)
                    print("elecPassesZ2CutsFinalAr",elecPassesZ2CutsFinalAr)
                    print("muonCandIndAr",muonCandIndAr)
                    print("muonCandChargeAr",muonCandChargeAr)
                    print("muonCandVecAr",muonCandVecAr)
                    for muonCandVecItrOne,muonCandVecOne in enumerate(muonCandVecAr[:-1]):
                        print("muonCandVecItrOne",muonCandVecItrOne,"muonCandVecOne",muonCandVecOne)
                        for muonCandVecItrTwo,muonCandVecTwo in enumerate(muonCandVecAr[muonCandVecItrOne+1:]):
                            print("muonCandVecItrTwo",muonCandVecItrOne+ 1+ muonCandVecItrTwo,"muonCandVecTwo",muonCandVecTwo)
                            tmpVecSum = muonCandVecOne +muonCandVecTwo
                            print(tmpVecSum)
                            print(tmpVecSum.M())
                    print("muonPassesZ2CutsAr",muonPassesZ2CutsAr)
                    print("muonPassesZ2CutsFinalAr",muonPassesZ2CutsFinalAr)
                if elecPassesZ2CutsFinalAr or muonPassesZ2CutsFinalAr:
                    if debug:
                        print("passed to Z2 Cut")
                    #First fill histo with max of the possible four lep inv mass 
                    tmpMax = 0
                    tmpZ1Vec = Z1LeadVec+Z1TrailingVec
                    for eZ2VecPair in eZ2VecPairAr:
                        tmpFourLepVec = eZ2VecPair[0]+eZ2VecPair[1]+tmpZ1Vec
                        tmpFourLepM = tmpFourLepVec.M()
                        if tmpFourLepM > tmpMax:
                            tmpMax = tmpFourLepM

                    for mZ2VecPair in mZ2VecPairAr:
                        tmpFourLepVec = mZ2VecPair[0]+mZ2VecPair[1]+tmpZ1Vec
                        tmpFourLepM = tmpFourLepVec.M()
                        if tmpFourLepM > tmpMax:
                            tmpMax = tmpFourLepM
                    histZ2FourLepAr[-1].Fill(tmpMax)
                    #Run loop here
                    for Z2FourLepCutItr in range(cutAmnt):
                        tmpZ2FourLepCut = Z2FourLepRange[0]+(Z2FourLepCutItr*Z2FourLepStep)
                        tmpZ2Ind = -1
                        Z2IsMuon = False
                        tmpTopZ2LeadPt = 0
                        tmpTopZ2TrailingPt = 0
                        
                        

                        if elecPassesZ2CutsFinalAr:
                            tmpZ2Ind,Z2IsMuon,tmpTopZ2LeadPt,tmpTopZ2TrailingPt = doeZ2Cut(ev,Z1LeadVec,Z1TrailingVec,tmpZ1Vec,Z1LeadCharge,Z1TrailingCharge,Z1IsMuon,eZ2VecPairAr,eZ2PtPairAr,eZ2ChargePairAr,tmpZ2Ind,Z2IsMuon,tmpTopZ2LeadPt,tmpTopZ2TrailingPt,tmpZ2FourLepCut,optLepInvMassCut)
                        if muonPassesZ2CutsFinalAr:
                            tmpZ2Ind,Z2IsMuon,tmpTopZ2LeadPt,tmpTopZ2TrailingPt = domZ2Cut(ev,Z1LeadVec,Z1TrailingVec,tmpZ1Vec,Z1LeadCharge,Z1TrailingCharge,Z1IsMuon,mZ2VecPairAr,mZ2PtPairAr,mZ2ChargePairAr,tmpZ2Ind,Z2IsMuon,tmpTopZ2LeadPt,tmpTopZ2TrailingPt,tmpZ2FourLepCut,optLepInvMassCut)
                        if debug:
                            print("tmpZ2Ind",tmpZ2Ind,"Z2IsMuon",Z2IsMuon,"tmpTopZ2LeadPt",tmpTopZ2LeadPt,"tmpTopZ2TrailingPt",tmpTopZ2TrailingPt) 
                        if tmpZ2Ind >= 0: #Passed Z2 Cut
                            if debug:
                                print("passed Z2 cut")
                                
                            #passesZ2CutsCtr += 1
                            if not Z1IsMuon:
                                Z1LeadIso = ev.eIso[elecCandIndAr[Z1LeadItr]]
                                Z1TrailingIso = ev.eIso[elecCandIndAr[Z1TrailingItr]]
                            else:
                                Z1LeadIso = ev.mIso[muonCandIndAr[Z1LeadItr]]
                                Z1TrailingIso = ev.mIso[muonCandIndAr[Z1TrailingItr]]
                            if not Z2IsMuon:
                                Z2LeadIso = ev.eIso[elecPassesZ2CutsFinalAr[tmpZ2Ind][0]]
                                Z2TrailingIso = ev.eIso[elecPassesZ2CutsFinalAr[tmpZ2Ind][1]]
                            else:
                                Z2LeadIso = ev.mIso[muonPassesZ2CutsFinalAr[tmpZ2Ind][0]]
                                Z2TrailingIso = ev.mIso[muonPassesZ2CutsFinalAr[tmpZ2Ind][1]]
                            if debug:
                                print("Z1LeadIso",Z1LeadIso,"Z1TrailingIso",Z1TrailingIso,"Z2LeadIso",Z2LeadIso,"Z2TrailingIso",Z2TrailingIso)
                            
                            passIsoCut = doISOCut(Z1LeadIso,Z1TrailingIso,Z2LeadIso,Z2TrailingIso,lepIsoCut)
                            
                            if passIsoCut:
                                if debug:
                                    print("passed iso cut yay")
                                #passesIsoCutCtr += 1
                                if not Z1IsMuon:
                                    Z1LeadSIP = ev.eSIP[elecCandIndAr[Z1LeadItr]]
                                    Z1TrailingSIP = ev.eSIP[elecCandIndAr[Z1TrailingItr]]
                                else:
                                    Z1LeadSIP = ev.mSIP[muonCandIndAr[Z1LeadItr]]
                                    Z1TrailingSIP = ev.mSIP[muonCandIndAr[Z1TrailingItr]]
                                if not Z2IsMuon:
                                    Z2LeadSIP = ev.eSIP[elecPassesZ2CutsFinalAr[tmpZ2Ind][0]]
                                    Z2TrailingSIP = ev.eSIP[elecPassesZ2CutsFinalAr[tmpZ2Ind][1]]
                                else:
                                    Z2LeadSIP = ev.mSIP[muonPassesZ2CutsFinalAr[tmpZ2Ind][0]]
                                    Z2TrailingSIP = ev.mSIP[muonPassesZ2CutsFinalAr[tmpZ2Ind][1]]
                                if debug:
                                    print("Z1LeadSIP",Z1LeadSIP,"Z1TrailingSIP",Z1TrailingSIP,"Z2LeadSIP",Z2LeadSIP,"Z2TrailingSIP",Z2TrailingSIP)

                                
                                passSIPCut = doSIPCut(Z1LeadSIP,Z1TrailingSIP,Z2LeadSIP,Z2TrailingSIP,SIPCut)
                                if passSIPCut:
                                    if debug:
                                        print("passed SIP cut yay")
                                    tmpZ2FourLepCntAr[Z2FourLepCutItr] += 1
                    

                    #Opt loop
                    #First fill histo with the max of the 3rd lowest inv mass combination of each Z1 Z2 pair

                    tmpMax = 0
                    tmpZ1Vec = Z1LeadVec+Z1TrailingVec
                    tmpZ1M = tmpZ1Vec.M()
                    if not Z1IsMuon:
                        for eZ2VecPair,eZ2ChargePair in zip(eZ2VecPairAr,eZ2ChargePairAr):
                            if eZ2ChargePair[0] == Z1LeadCharge:
                                tmpOptLepVecOne = eZ2VecPair[0] + Z1TrailingVec
                                tmpOptLepVecTwo = eZ2VecPair[1] + Z1LeadVec
                            else:
                                tmpOptLepVecOne = eZ2VecPair[1] + Z1TrailingVec
                                tmpOptLepVecTwo = eZ2VecPair[0] + Z1LeadVec
                            tmpZ2Vec = eZ2VecPair[0] + eZ2VecPair[1]
                            tmpZ2M = tmpZ2Vec.M()
                            tmpOptLepMOne = tmpOptLepVecOne.M()
                            tmpOptLepMTwo = tmpOptLepVecTwo.M()
                            tmpOptLepM = find2ndToLast(tmpZ1M,tmpZ2M,tmpOptLepMOne,tmpOptLepMTwo)

                            if tmpOptLepM > tmpMax:
                                tmpMax = tmpOptLepM
                        if eZ2VecPairAr:
                            histZ2OptLepAr[-1].Fill(tmpMax)
                    else:
                        for mZ2VecPair,mZ2ChargePair in zip(mZ2VecPairAr,mZ2ChargePairAr):
                            if mZ2ChargePair[0] == Z1LeadCharge:
                                tmpOptLepVecOne = mZ2VecPair[0] + Z1TrailingVec
                                tmpOptLepVecTwo = mZ2VecPair[1] + Z1LeadVec
                            else:
                                tmpOptLepVecOne = mZ2VecPair[1] + Z1TrailingVec
                                tmpOptLepVecTwo = mZ2VecPair[0] + Z1LeadVec
                            tmpZ2Vec = mZ2VecPair[0] + mZ2VecPair[1]
                            tmpZ2M = tmpZ2Vec.M()
                            tmpOptLepMOne = tmpOptLepVecOne.M()
                            tmpOptLepMTwo = tmpOptLepVecTwo.M()
                            tmpOptLepM = find2ndToLast(tmpZ1M,tmpZ2M,tmpOptLepMOne,tmpOptLepMTwo)
                            if tmpOptLepM > tmpMax:
                                tmpMax = tmpOptLepM
                            
                        if mZ2VecPairAr:
                            histZ2OptLepAr[-1].Fill(tmpMax)


                    for Z2OptLepCutItr in range(cutAmnt):
                        tmpZ2OptLepCut = Z2OptLepRange[0]+(Z2OptLepCutItr*Z2OptLepStep)
                        tmpZ2Ind = -1
                        Z2IsMuon = False
                        tmpTopZ2LeadPt = 0
                        tmpTopZ2TrailingPt = 0
                        if elecPassesZ2CutsFinalAr:
                            tmpZ2Ind,Z2IsMuon,tmpTopZ2LeadPt,tmpTopZ2TrailingPt = doeZ2Cut(ev,Z1LeadVec,Z1TrailingVec,tmpZ1Vec,Z1LeadCharge,Z1TrailingCharge,Z1IsMuon,eZ2VecPairAr,eZ2PtPairAr,eZ2ChargePairAr,tmpZ2Ind,Z2IsMuon,tmpTopZ2LeadPt,tmpTopZ2TrailingPt,fourLepInvMassCut,tmpZ2OptLepCut)

                        if muonPassesZ2CutsFinalAr:
                            tmpZ2Ind,Z2IsMuon,tmpTopZ2LeadPt,tmpTopZ2TrailingPt = domZ2Cut(ev,Z1LeadVec,Z1TrailingVec,tmpZ1Vec,Z1LeadCharge,Z1TrailingCharge,Z1IsMuon,mZ2VecPairAr,mZ2PtPairAr,mZ2ChargePairAr,tmpZ2Ind,Z2IsMuon,tmpTopZ2LeadPt,tmpTopZ2TrailingPt,fourLepInvMassCut,tmpZ2OptLepCut)
                        if debug:
                            print("tmpZ2Ind",tmpZ2Ind,"Z2IsMuon",Z2IsMuon,"tmpTopZ2LeadPt",tmpTopZ2LeadPt,"tmpTopZ2TrailingPt",tmpTopZ2TrailingPt) 
                        if tmpZ2Ind >= 0: #Passed Z2 Cut
                            if debug:
                                print("passed Z2 cut")
                                
                            #passesZ2CutsCtr += 1
                            if not Z1IsMuon:
                                Z1LeadIso = ev.eIso[elecCandIndAr[Z1LeadItr]]
                                Z1TrailingIso = ev.eIso[elecCandIndAr[Z1TrailingItr]]
                            else:
                                Z1LeadIso = ev.mIso[muonCandIndAr[Z1LeadItr]]
                                Z1TrailingIso = ev.mIso[muonCandIndAr[Z1TrailingItr]]
                            if not Z2IsMuon:
                                Z2LeadIso = ev.eIso[elecPassesZ2CutsFinalAr[tmpZ2Ind][0]]
                                Z2TrailingIso = ev.eIso[elecPassesZ2CutsFinalAr[tmpZ2Ind][1]]
                            else:
                                Z2LeadIso = ev.mIso[muonPassesZ2CutsFinalAr[tmpZ2Ind][0]]
                                Z2TrailingIso = ev.mIso[muonPassesZ2CutsFinalAr[tmpZ2Ind][1]]
                            if debug:
                                print("Z1LeadIso",Z1LeadIso,"Z1TrailingIso",Z1TrailingIso,"Z2LeadIso",Z2LeadIso,"Z2TrailingIso",Z2TrailingIso)


                            
                            passIsoCut = doISOCut(Z1LeadIso,Z1TrailingIso,Z2LeadIso,Z2TrailingIso,lepIsoCut)
                            
                            if passIsoCut:
                                if debug:
                                    print("passed iso cut yay")
                                #passesIsoCutCtr += 1
                                if not Z1IsMuon:
                                    Z1LeadSIP = ev.eSIP[elecCandIndAr[Z1LeadItr]]
                                    Z1TrailingSIP = ev.eSIP[elecCandIndAr[Z1TrailingItr]]
                                else:
                                    Z1LeadSIP = ev.mSIP[muonCandIndAr[Z1LeadItr]]
                                    Z1TrailingSIP = ev.mSIP[muonCandIndAr[Z1TrailingItr]]
                                if not Z2IsMuon:
                                    Z2LeadSIP = ev.eSIP[elecPassesZ2CutsFinalAr[tmpZ2Ind][0]]
                                    Z2TrailingSIP = ev.eSIP[elecPassesZ2CutsFinalAr[tmpZ2Ind][1]]
                                else:
                                    Z2LeadSIP = ev.mSIP[muonPassesZ2CutsFinalAr[tmpZ2Ind][0]]
                                    Z2TrailingSIP = ev.mSIP[muonPassesZ2CutsFinalAr[tmpZ2Ind][1]]
                                if debug:
                                    print("Z1LeadSIP",Z1LeadSIP,"Z1TrailingSIP",Z1TrailingSIP,"Z2LeadSIP",Z2LeadSIP,"Z2TrailingSIP",Z2TrailingSIP)

                                
                                passSIPCut = doSIPCut(Z1LeadSIP,Z1TrailingSIP,Z2LeadSIP,Z2TrailingSIP,SIPCut)
                                if passSIPCut:
                                    if debug:
                                        print("passed SIP cut yay")
                                    tmpZ2OptLepCntAr[Z2OptLepCutItr] += 1
                            
                            
    for c in range(cutAmnt):
        Z2FourLepEvPassGraphAr[k].append(tmpZ2FourLepCntAr[c])
        if isSignalAr[k]:
            Z2FourLepSignalAr[c] += tmpZ2FourLepCntAr[c]*weightsAr[k]
        else:
            Z2FourLepBackgroundAr[c] += tmpZ2FourLepCntAr[c]*weightsAr[k]
        Z2OptLepEvPassGraphAr[k].append(tmpZ2OptLepCntAr[c])
        if isSignalAr[k]:
            Z2OptLepSignalAr[c] += tmpZ2OptLepCntAr[c]*weightsAr[k]
        else:
            Z2OptLepBackgroundAr[c] += tmpZ2OptLepCntAr[c]*weightsAr[k]
    if extraOut:
        print(nameAr[k])
        print("Z2FourLepSignalAr",Z2FourLepSignalAr)
        print("Z2FourLepBackgroundAr",Z2FourLepBackgroundAr)
        print("Z2OptLepSignalAr",Z2OptLepSignalAr)
        print("Z2OptLepBackgroundAr",Z2OptLepBackgroundAr)
#print(passesCandCutsCtr)
#print(passesZ1CutsCtr)
#print(passesZ2CutsCtr)
#print(passesZ2CutCtr)
#print(passesAllCutsCtr)
#print(allPassAr)
if extraOut:
    print(Z2FourLepSignalAr)
    print(Z2FourLepBackgroundAr)
    print(Z2OptLepSignalAr)
    print(Z2OptLepBackgroundAr)

##############FOUR LEP INV MASS CUT LOW##############

Z2FourLepGraphAr = array('d')
Z2FourLepXAr = array('d')

FoMCalc(Z2FourLepSignalAr,Z2FourLepBackgroundAr,Z2FourLepGraphAr,Z2FourLepXAr,cutAmnt,Z2FourLepRange,Z2FourLepStep)

evPassZ2FourLepCanAr = []
evPassZ2FourLepGraphAr = []
print("Done.","time:",time.time()-startt)

#make evpass graphs

cutName = "Z2FourLep"

if not skipEvPassGraphs:
    makeEvPassGraphs(nameAr,evPassZ2FourLepCanAr,Z2FourLepEvPassGraphAr,evPassZ2FourLepGraphAr,Z2FourLepXAr,cutName)


padAr = []
legAr = []


signalName = ""
backgroundName = ""
for k,fileA in enumerate(fileAr):
    if not sumQCD or not isQCDAr[k]:
        if isSignalAr[k]:
            signalName += "_"+saveNameAr[k]

        else:
            backgroundName += "_"+saveNameAr[k]


if sumQCD:
    backgroundName += "_QCDSum"
    QCDSumHist = TH1D("Z2FourLepHistQCDSum","Z2FourLepHistQCDSum", binAmnt, Z2FourLepRange[0], Z2FourLepRange[1])
    for k in range(len(histZ2FourLepAr)):

        if isQCDAr[k]:
            histZ2FourLepAr[k].Sumw2()
            QCDSumHist.Sumw2()
            QCDSumHist.Add(histZ2FourLepAr[k],weightsAr[k])
else:
    QCDSumHist = 0



FoMZ2FourLepCan = TCanvas("c1Z2FourLep","c1Z2FourLep",3600,2400)
setUpLegend(legAr)
setUpPadsAr(padAr,"{0}Pad".format("Z2FourLep"))
padAr[-1][0].Draw()
padAr[-1][0].cd()

#Make top plot
#First set histogram elements (color, etc)
intZ2FourLepAr = []

backgroundIntSum,QCDSumInt = setHistoElements(nameAr,colorAr,sumQCD,QCDSumHist,isQCDAr,histZ2FourLepAr,isSignalAr,cutName,normalizeBackgroundsTogether,weightsAr,intZ2FourLepAr)

if variableRebin:
    doVariableRebinning(histZ2FourLepAr,isSignalAr,variableRebinVar,binAmnt,Z2FourLepRange,sumQCD,nameAr,QCDSumHist,cutName,weightsAr)

histMax = normalizeHists(histZ2FourLepAr,sumQCD,isQCDAr,normalizeBackgroundsTogether,backgroundIntSum,isSignalAr,weightsAr,legAr,nameAr,intZ2FourLepAr)


if sumQCD:
    if QCDSumInt:
        histMax = scaleQCDHist(QCDSumInt,QCDSumHist,histMax,legAr)


histZ2FourLepStack = THStack("hist{0}Stack".format(cutName),"Events Passing All Cuts Vs {0} Cut Value".format(cutName))


maxInt = addHistsToStack(histZ2FourLepAr,isSignalAr,sumQCD,isQCDAr,histZ2FourLepStack,QCDSumHist,normalizeBackgroundsTogether,backgroundIntSum)

invHistsAr = []
drawInvAr = []

setUpInvHists(histZ2FourLepAr,isSignalAr,sumQCD,isQCDAr,invHistsAr,nameAr,intZ2FourLepAr,drawInvAr,QCDSumInt,QCDSumHist,cutName)

FoMZ2FourLepGraph = TGraph(len(Z2FourLepGraphAr),Z2FourLepXAr,Z2FourLepGraphAr)



setUpStackedHistAndDrawFoMPlot(histMax,histZ2FourLepAr,histZ2FourLepStack,invHistsAr,drawInvAr,legAr,FoMZ2FourLepCan,padAr,FoMZ2FourLepGraph,Z2FourLepRange,normalizeBackgroundsTogether,cutName,signalName,backgroundName,fourLepInvMassCut)

FoMZ2FourLep2Can = TCanvas("c2Z2FourLep","c2Z2FourLep",3600,2400)

setUpNonStackedHistAndFoMPlot(FoMZ2FourLep2Can,cutName,padAr,sumQCD,QCDSumHist,histMax,isSignalAr,isQCDAr,normalizeBackgroundsTogether,maxInt,histZ2FourLepAr,legAr,FoMZ2FourLepGraph,signalName,backgroundName,fourLepInvMassCut)


##############Z2 OPT LEP CUT LOW##############

Z2OptLepGraphAr = array('d')
Z2OptLepXAr = array('d')



FoMCalc(Z2OptLepSignalAr,Z2OptLepBackgroundAr,Z2OptLepGraphAr,Z2OptLepXAr,cutAmnt,Z2OptLepRange,Z2OptLepStep)

evPassZ2OptLepCanAr = []
evPassZ2OptLepGraphAr = []
print("Done.","time:",time.time()-startt)

#make evpass graphs

cutName = "Z2OptLep"

if not skipEvPassGraphs:
    makeEvPassGraphs(nameAr,evPassZ2OptLepCanAr,Z2OptLepEvPassGraphAr,evPassZ2OptLepGraphAr,Z2OptLepXAr,cutName)


padAr = []
legAr = []


signalName = ""
backgroundName = ""
for k,fileA in enumerate(fileAr):
    if not sumQCD or not isQCDAr[k]:
        if isSignalAr[k]:
            signalName += "_"+saveNameAr[k]

        else:
            backgroundName += "_"+saveNameAr[k]


if sumQCD:
    backgroundName += "_QCDSum"
    QCDSumHist = TH1D("Z2OptLepHistQCDSum","Z2OptLepHistQCDSum", binAmnt, Z2OptLepRange[0], Z2OptLepRange[1])
    for k in range(len(histZ2OptLepAr)):

        if isQCDAr[k]:
            histZ2OptLepAr[k].Sumw2()
            QCDSumHist.Sumw2()
            QCDSumHist.Add(histZ2OptLepAr[k],weightsAr[k])
else:
    QCDSumHist = 0



FoMZ2OptLepCan = TCanvas("c1Z2OptLep","c1Z2OptLep",3600,2400)
setUpLegend(legAr)
setUpPadsAr(padAr,"{0}Pad".format("Z2OptLep"))
padAr[-1][0].Draw()
padAr[-1][0].cd()

#Make top plot
#First set histogram elements (color, etc)
intZ2OptLepAr = []

backgroundIntSum,QCDSumInt = setHistoElements(nameAr,colorAr,sumQCD,QCDSumHist,isQCDAr,histZ2OptLepAr,isSignalAr,cutName,normalizeBackgroundsTogether,weightsAr,intZ2OptLepAr)

if variableRebin:
    doVariableRebinning(histZ2OptLepAr,isSignalAr,variableRebinVar,binAmnt,Z2OptLepRange,sumQCD,nameAr,QCDSumHist,cutName,weightsAr)

histMax = normalizeHists(histZ2OptLepAr,sumQCD,isQCDAr,normalizeBackgroundsTogether,backgroundIntSum,isSignalAr,weightsAr,legAr,nameAr,intZ2OptLepAr)


if sumQCD:
    if QCDSumInt:
        histMax = scaleQCDHist(QCDSumInt,QCDSumHist,histMax,legAr)


histZ2OptLepStack = THStack("hist{0}Stack".format(cutName),"Events Passing All Cuts Vs {0} Cut Value".format(cutName))


maxInt = addHistsToStack(histZ2OptLepAr,isSignalAr,sumQCD,isQCDAr,histZ2OptLepStack,QCDSumHist,normalizeBackgroundsTogether,backgroundIntSum)

invHistsAr = []
drawInvAr = []

setUpInvHists(histZ2OptLepAr,isSignalAr,sumQCD,isQCDAr,invHistsAr,nameAr,intZ2OptLepAr,drawInvAr,QCDSumInt,QCDSumHist,cutName)

FoMZ2OptLepGraph = TGraph(len(Z2OptLepGraphAr),Z2OptLepXAr,Z2OptLepGraphAr)



setUpStackedHistAndDrawFoMPlot(histMax,histZ2OptLepAr,histZ2OptLepStack,invHistsAr,drawInvAr,legAr,FoMZ2OptLepCan,padAr,FoMZ2OptLepGraph,Z2OptLepRange,normalizeBackgroundsTogether,cutName,signalName,backgroundName,optLepInvMassCut)

FoMZ2OptLep2Can = TCanvas("c2Z2OptLep","c2Z2OptLep",3600,2400)

setUpNonStackedHistAndFoMPlot(FoMZ2OptLep2Can,cutName,padAr,sumQCD,QCDSumHist,histMax,isSignalAr,isQCDAr,normalizeBackgroundsTogether,maxInt,histZ2OptLepAr,legAr,FoMZ2OptLepGraph,signalName,backgroundName,optLepInvMassCut)
