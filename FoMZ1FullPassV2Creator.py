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
debugV2GraphMaking = False
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
    tmpXSAvg = 0.6*0.584
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
    colorAr.append(5)
    isSignalAr.append(False)
    tmpXSAvg = 6077.22
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

cutAmnt = 200
binAmnt = 20

ePtCut = 7
eEtaCut = 2.5

mPtCut = 5
mEtaCut = 2.4
invMassCutLow=60
Z1InvMassCutLowRange = [0,120]
Z1InvMassCutLowStep = (Z1InvMassCutLowRange[1]-Z1InvMassCutLowRange[0])/cutAmnt
Z1InvMassCutLowSignalAr = [0 for i in range(cutAmnt)] 
Z1InvMassCutLowBackgroundAr = [0 for i in range(cutAmnt)] 


invMassCutHigh=120
Z1InvMassCutHighRange = [60,180]
Z1InvMassCutHighStep = (Z1InvMassCutHighRange[1]-Z1InvMassCutHighRange[0])/cutAmnt
Z1InvMassCutHighSignalAr = [0 for i in range(cutAmnt)] 
Z1InvMassCutHighBackgroundAr = [0 for i in range(cutAmnt)] 

ptTrailingCut=10
Z1PtCutLowRange = [0,100]
Z1PtCutLowStep = (Z1PtCutLowRange[1]-Z1PtCutLowRange[0])/cutAmnt
Z1PtCutLowSignalAr = [0 for i in range(cutAmnt)] 
Z1PtCutLowBackgroundAr = [0 for i in range(cutAmnt)] 

ptLeadCut=20
Z1PtCutHighRange = [0,200]
Z1PtCutHighStep = (Z1PtCutHighRange[1]-Z1PtCutHighRange[0])/cutAmnt
Z1PtCutHighSignalAr = [0 for i in range(cutAmnt)] 
Z1PtCutHighBackgroundAr = [0 for i in range(cutAmnt)] 


#ZMass = 91.1876
fourLepInvMassCut = 100
optLepInvMassCut = 12
lepIsoCut = 0.35

SIPCut = 4



Z1InvMassCutLowEvPassGraphAr = []
Z1InvMassCutHighEvPassGraphAr = []
Z1PtCutLowEvPassGraphAr = []
Z1PtCutHighEvPassGraphAr = []
for nameA in nameAr:
    Z1InvMassCutLowEvPassGraphAr.append(array('d'))
    Z1InvMassCutHighEvPassGraphAr.append(array('d'))
    Z1PtCutLowEvPassGraphAr.append(array('d'))
    Z1PtCutHighEvPassGraphAr.append(array('d'))

histZ1InvMassCutLowAr = []
histZ1InvMassCutHighAr = []
histZ1PtCutLowAr = []
histZ1PtCutHighAr = []

def setUpGraphs(gGraph,markerStyle,lineColor,gTitle,xTitle,yTitle):
    #gGraph.SetMarkerStyle(markerStyle)
    gGraph.SetTitle(gTitle)
    
    gGraph.GetXaxis().SetTitle(xTitle)
    gGraph.GetXaxis().CenterTitle()
    gGraph.GetYaxis().SetTitle(yTitle)
    gGraph.GetYaxis().CenterTitle()
    #gGraph.SetLineColor(lineColor)
    gGraph.GetXaxis().SetLabelFont(42)
    gGraph.GetXaxis().SetLabelSize(0.035)
    gGraph.GetXaxis().SetTitleFont(42)
    gGraph.GetYaxis().SetLabelFont(42)
    gGraph.GetYaxis().SetLabelSize(0.035)
    gGraph.GetYaxis().SetTitleFont(42)
    gGraph.GetYaxis().SetTitleOffset(1.2)
    gGraph.GetXaxis().SetTitleOffset(0.9)


#MAIN LOOP
for k,fileA in enumerate(fileAr):
    print("Entering file {0}".format(k))
    CTree = fileA.cutTree
    tmpZ1InvMassCutLowCntAr = [0 for cutItr in range(cutAmnt)]
    histZ1InvMassCutLowAr.append(TH1D("Z1InvMassCutLowHist{0}".format(nameAr[k]),"Z1InvMassCutLowHist{0}".format(nameAr[k]), binAmnt, Z1InvMassCutLowRange[0], Z1InvMassCutLowRange[1]))
    tmpZ1InvMassCutHighCntAr = [0 for cutItr in range(cutAmnt)]
    histZ1InvMassCutHighAr.append(TH1D("Z1InvMassCutHighHist{0}".format(nameAr[k]),"Z1InvMassCutHighHist{0}".format(nameAr[k]), binAmnt, Z1InvMassCutHighRange[0], Z1InvMassCutHighRange[1]))
    tmpZ1PtCutLowCntAr = [0 for cutItr in range(cutAmnt)]
    histZ1PtCutLowAr.append(TH1D("Z1PtCutLowHist{0}".format(nameAr[k]),"Z1PtCutLowHist{0}".format(nameAr[k]), binAmnt, Z1PtCutLowRange[0], Z1PtCutLowRange[1]))
    tmpZ1PtCutHighCntAr = [0 for cutItr in range(cutAmnt)]
    histZ1PtCutHighAr.append(TH1D("Z1PtCutHighHist{0}".format(nameAr[k]),"Z1PtCutHighHist{0}".format(nameAr[k]), binAmnt, Z1PtCutHighRange[0], Z1PtCutHighRange[1]))
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
        
        if enoughLepCands: #Check there are enough lep cands after candidate cuts
            #passesCandCutsCtr += 1
            if enoughElecCands:
                for eItrOne,elecCandIndOne in enumerate(elecCandIndAr[:-1]): #ELECTRON LOOP ONE
                    tmpChargeOne = elecCandChargeAr[eItrOne]
                    for tmpeItrTwo,elecCandIndTwo in enumerate(elecCandIndAr[eItrOne+1:]): #ELECTRON LOOP TWO
                        eItrTwo = eItrOne + tmpeItrTwo + 1
                        tmpChargeTwo = elecCandChargeAr[eItrTwo]
                        if tmpChargeOne != tmpChargeTwo: #CHECK IF OPPOSITE CHARGE
                            tmpZ1VecOne = elecCandVecAr[eItrOne]
                            tmpZ1VecTwo = elecCandVecAr[eItrTwo]
                            tmpZ1Vec =  tmpZ1VecOne+tmpZ1VecTwo
                            tmpZ1Mass = tmpZ1Vec.M()
                            histZ1InvMassCutLowAr[-1].Fill(tmpZ1Mass)
                            histZ1InvMassCutHighAr[-1].Fill(tmpZ1Mass)
            if enoughMuonCands:
                for mItrOne,muonCandIndOne in enumerate(muonCandIndAr[:-1]): #MUON LOOP ONE
                    tmpChargeOne = muonCandChargeAr[mItrOne]
                    for tmpmItrTwo,muonCandIndTwo in enumerate(muonCandIndAr[mItrOne+1:]): #ELECTRON LOOP TWO
                        mItrTwo = mItrOne + tmpmItrTwo + 1
                        tmpChargeTwo = muonCandChargeAr[mItrTwo]
                        if tmpChargeOne != tmpChargeTwo: #CHECK IF OPPOSITE CHARGE
                            tmpZ1VecOne = muonCandVecAr[mItrOne]
                            tmpZ1VecTwo = muonCandVecAr[mItrTwo]
                            tmpZ1Vec =  tmpZ1VecOne+tmpZ1VecTwo
                            tmpZ1Mass = tmpZ1Vec.M()
                            histZ1InvMassCutLowAr[-1].Fill(tmpZ1Mass)
                            histZ1InvMassCutHighAr[-1].Fill(tmpZ1Mass)
            #Run Loop here
            #Inv mass cut low loop
            for Z1InvMassCutLowItr in range(cutAmnt):
                tmpZ1InvMassCutLow = Z1InvMassCutLowRange[0]+(Z1InvMassCutLowItr*Z1InvMassCutLowStep)
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

                elecPassesZ2CutsAr = []

                if enoughElecCands: #If enough elec cands, run Z1 cuts
                    
                    Z1LeadItr,Z1TrailingItr,Z1LeadPt,Z1TrailingPt,Z1LeadVec,Z1TrailingVec,Z1LeadCharge,Z1TrailingCharge,Z1IsMuon,difFromZMassOne = doeZ1Cut(ev,elecCandIndAr,elecCandVecAr,elecCandChargeAr,elecPassesZ2CutsAr,Z1IsMuon,tmpZ1InvMassCutLow,invMassCutHigh,ptLeadCut,ptTrailingCut,Z1LeadPt,Z1TrailingPt,Z1LeadItr,Z1TrailingItr,Z1LeadVec,Z1TrailingVec,Z1LeadCharge,Z1TrailingCharge,difFromZMassOne)
                muonPassesZ2CutsAr = []
                if enoughMuonCands: #If enough muon cands, run Z1 cuts
                    
                    Z1LeadItr,Z1TrailingItr,Z1LeadPt,Z1TrailingPt,Z1LeadVec,Z1TrailingVec,Z1LeadCharge,Z1TrailingCharge,Z1IsMuon,difFromZMassOne = domZ1Cut(ev,muonCandIndAr,muonCandVecAr,muonCandChargeAr,muonPassesZ2CutsAr,Z1IsMuon,tmpZ1InvMassCutLow,invMassCutHigh,ptLeadCut,ptTrailingCut,Z1LeadPt,Z1TrailingPt,Z1LeadItr,Z1TrailingItr,Z1LeadVec,Z1TrailingVec,Z1LeadCharge,Z1TrailingCharge,difFromZMassOne)
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
                        tmpZ2Ind = -1
                        Z2IsMuon = False
                        tmpTopZ2LeadPt = 0
                        tmpTopZ2TrailingPt = 0
                        tmpZ1Vec = Z1LeadVec+Z1TrailingVec

                        
                        if elecPassesZ2CutsFinalAr:
                            tmpZ2Ind,Z2IsMuon,tmpTopZ2LeadPt,tmpTopZ2TrailingPt = doeZ2Cut(ev,Z1LeadVec,Z1TrailingVec,tmpZ1Vec,Z1LeadCharge,Z1TrailingCharge,Z1IsMuon,eZ2VecPairAr,eZ2PtPairAr,eZ2ChargePairAr,tmpZ2Ind,Z2IsMuon,tmpTopZ2LeadPt,tmpTopZ2TrailingPt,fourLepInvMassCut,optLepInvMassCut)

                        if muonPassesZ2CutsFinalAr:
                            tmpZ2Ind,Z2IsMuon,tmpTopZ2LeadPt,tmpTopZ2TrailingPt = domZ2Cut(ev,Z1LeadVec,Z1TrailingVec,tmpZ1Vec,Z1LeadCharge,Z1TrailingCharge,Z1IsMuon,mZ2VecPairAr,mZ2PtPairAr,mZ2ChargePairAr,tmpZ2Ind,Z2IsMuon,tmpTopZ2LeadPt,tmpTopZ2TrailingPt,fourLepInvMassCut,optLepInvMassCut)
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
                                #Fill with HIGHEST SIP
                                
                                #histIsoAr[-1].Fill(Z1LeadSIP)
                                #histIsoAr[-1].Fill(Z1TrailingSIP)
                                #histIsoAr[-1].Fill(Z2LeadSIP)
                                #histIsoAr[-1].Fill(Z2TrailingSIP)
                                #Loop here
                                
                                
                                """
                                for SIPCutItr in range(cutAmnt):
                                    tmpSIPCut = SIPRange[0]+(SIPCutItr*SIPStep)
                                    passSIPCut = doSIPCut(Z1LeadSIP,Z1TrailingSIP,Z2LeadSIP,Z2TrailingSIP,tmpSIPCut)
                                    if passSIPCut:
                                        tmpSIPCntAr[SIPCutItr] += 1
                                        #if isSignalAr[k]:
                                        #    SIPSignalAr[SIPCutItr] += 1
                                        #else:
                                        #    SIPBackgroundAr[SIPCutItr] += 1
                                """
                                passSIPCut = doSIPCut(Z1LeadSIP,Z1TrailingSIP,Z2LeadSIP,Z2TrailingSIP,SIPCut)
                                if passSIPCut:
                                    if debug:
                                        print("passed SIP cut yay")
                                    tmpZ1InvMassCutLowCntAr[Z1InvMassCutLowItr] += 1
            



            #Inv mass cut high loop
            for Z1InvMassCutHighItr in range(cutAmnt):
                tmpZ1InvMassCutHigh = Z1InvMassCutHighRange[0]+(Z1InvMassCutHighItr*Z1InvMassCutHighStep)
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

                elecPassesZ2CutsAr = []

                if enoughElecCands: #If enough elec cands, run Z1 cuts
                    
                    Z1LeadItr,Z1TrailingItr,Z1LeadPt,Z1TrailingPt,Z1LeadVec,Z1TrailingVec,Z1LeadCharge,Z1TrailingCharge,Z1IsMuon,difFromZMassOne = doeZ1Cut(ev,elecCandIndAr,elecCandVecAr,elecCandChargeAr,elecPassesZ2CutsAr,Z1IsMuon,invMassCutLow,tmpZ1InvMassCutHigh,ptLeadCut,ptTrailingCut,Z1LeadPt,Z1TrailingPt,Z1LeadItr,Z1TrailingItr,Z1LeadVec,Z1TrailingVec,Z1LeadCharge,Z1TrailingCharge,difFromZMassOne,debug)
                muonPassesZ2CutsAr = []
                if enoughMuonCands: #If enough muon cands, run Z1 cuts
                    
                    Z1LeadItr,Z1TrailingItr,Z1LeadPt,Z1TrailingPt,Z1LeadVec,Z1TrailingVec,Z1LeadCharge,Z1TrailingCharge,Z1IsMuon,difFromZMassOne = domZ1Cut(ev,muonCandIndAr,muonCandVecAr,muonCandChargeAr,muonPassesZ2CutsAr,Z1IsMuon,invMassCutLow,tmpZ1InvMassCutHigh,ptLeadCut,ptTrailingCut,Z1LeadPt,Z1TrailingPt,Z1LeadItr,Z1TrailingItr,Z1LeadVec,Z1TrailingVec,Z1LeadCharge,Z1TrailingCharge,difFromZMassOne,debug)
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
                        tmpZ2Ind = -1
                        Z2IsMuon = False
                        tmpTopZ2LeadPt = 0
                        tmpTopZ2TrailingPt = 0
                        tmpZ1Vec = Z1LeadVec+Z1TrailingVec

                        
                        if elecPassesZ2CutsFinalAr:
                            tmpZ2Ind,Z2IsMuon,tmpTopZ2LeadPt,tmpTopZ2TrailingPt = doeZ2Cut(ev,Z1LeadVec,Z1TrailingVec,tmpZ1Vec,Z1LeadCharge,Z1TrailingCharge,Z1IsMuon,eZ2VecPairAr,eZ2PtPairAr,eZ2ChargePairAr,tmpZ2Ind,Z2IsMuon,tmpTopZ2LeadPt,tmpTopZ2TrailingPt,fourLepInvMassCut,optLepInvMassCut)

                        if muonPassesZ2CutsFinalAr:
                            tmpZ2Ind,Z2IsMuon,tmpTopZ2LeadPt,tmpTopZ2TrailingPt = domZ2Cut(ev,Z1LeadVec,Z1TrailingVec,tmpZ1Vec,Z1LeadCharge,Z1TrailingCharge,Z1IsMuon,mZ2VecPairAr,mZ2PtPairAr,mZ2ChargePairAr,tmpZ2Ind,Z2IsMuon,tmpTopZ2LeadPt,tmpTopZ2TrailingPt,fourLepInvMassCut,optLepInvMassCut)
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
                                #Fill with HIGHEST SIP
                                
                                #histIsoAr[-1].Fill(Z1LeadSIP)
                                #histIsoAr[-1].Fill(Z1TrailingSIP)
                                #histIsoAr[-1].Fill(Z2LeadSIP)
                                #histIsoAr[-1].Fill(Z2TrailingSIP)
                                #Loop here
                                
                                
                                """
                                for SIPCutItr in range(cutAmnt):
                                    tmpSIPCut = SIPRange[0]+(SIPCutItr*SIPStep)
                                    passSIPCut = doSIPCut(Z1LeadSIP,Z1TrailingSIP,Z2LeadSIP,Z2TrailingSIP,tmpSIPCut)
                                    if passSIPCut:
                                        tmpSIPCntAr[SIPCutItr] += 1
                                        #if isSignalAr[k]:
                                        #    SIPSignalAr[SIPCutItr] += 1
                                        #else:
                                        #    SIPBackgroundAr[SIPCutItr] += 1
                                """
                                passSIPCut = doSIPCut(Z1LeadSIP,Z1TrailingSIP,Z2LeadSIP,Z2TrailingSIP,SIPCut)
                                if passSIPCut:
                                    if debug:
                                        print("passed SIP cut yay")
                                    tmpZ1InvMassCutHighCntAr[Z1InvMassCutHighItr] += 1

            
            
            if enoughElecCands:
                for elecCandIndOne in elecCandIndAr: #ELECTRON LOOP ONE
                    tmpPt = ev.ePt[elecCandIndOne]
                    histZ1PtCutLowAr[-1].Fill(tmpPt)
                    histZ1PtCutHighAr[-1].Fill(tmpPt)
                
            if enoughMuonCands:      
                for muonCandIndOne in muonCandIndAr: #MUON LOOP ONE
                    tmpPt = ev.mPt[muonCandIndOne]
                    histZ1PtCutLowAr[-1].Fill(tmpPt)
                    histZ1PtCutHighAr[-1].Fill(tmpPt)

            #pt cut low loop
            for Z1PtCutLowItr in range(cutAmnt):
                tmpZ1PtCutLow = Z1PtCutLowRange[0]+(Z1PtCutLowItr*Z1PtCutLowStep)
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

                elecPassesZ2CutsAr = []

                if enoughElecCands: #If enough elec cands, run Z1 cuts
                    
                    Z1LeadItr,Z1TrailingItr,Z1LeadPt,Z1TrailingPt,Z1LeadVec,Z1TrailingVec,Z1LeadCharge,Z1TrailingCharge,Z1IsMuon,difFromZMassOne = doeZ1Cut(ev,elecCandIndAr,elecCandVecAr,elecCandChargeAr,elecPassesZ2CutsAr,Z1IsMuon,invMassCutLow,invMassCutHigh,ptLeadCut,tmpZ1PtCutLow,Z1LeadPt,Z1TrailingPt,Z1LeadItr,Z1TrailingItr,Z1LeadVec,Z1TrailingVec,Z1LeadCharge,Z1TrailingCharge,difFromZMassOne)
                muonPassesZ2CutsAr = []
                if enoughMuonCands: #If enough muon cands, run Z1 cuts
                    
                    Z1LeadItr,Z1TrailingItr,Z1LeadPt,Z1TrailingPt,Z1LeadVec,Z1TrailingVec,Z1LeadCharge,Z1TrailingCharge,Z1IsMuon,difFromZMassOne = domZ1Cut(ev,muonCandIndAr,muonCandVecAr,muonCandChargeAr,muonPassesZ2CutsAr,Z1IsMuon,invMassCutLow,invMassCutHigh,ptLeadCut,tmpZ1PtCutLow,Z1LeadPt,Z1TrailingPt,Z1LeadItr,Z1TrailingItr,Z1LeadVec,Z1TrailingVec,Z1LeadCharge,Z1TrailingCharge,difFromZMassOne)
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
                        tmpZ2Ind = -1
                        Z2IsMuon = False
                        tmpTopZ2LeadPt = 0
                        tmpTopZ2TrailingPt = 0
                        tmpZ1Vec = Z1LeadVec+Z1TrailingVec

                        
                        if elecPassesZ2CutsFinalAr:
                            tmpZ2Ind,Z2IsMuon,tmpTopZ2LeadPt,tmpTopZ2TrailingPt = doeZ2Cut(ev,Z1LeadVec,Z1TrailingVec,tmpZ1Vec,Z1LeadCharge,Z1TrailingCharge,Z1IsMuon,eZ2VecPairAr,eZ2PtPairAr,eZ2ChargePairAr,tmpZ2Ind,Z2IsMuon,tmpTopZ2LeadPt,tmpTopZ2TrailingPt,fourLepInvMassCut,optLepInvMassCut)

                        if muonPassesZ2CutsFinalAr:
                            tmpZ2Ind,Z2IsMuon,tmpTopZ2LeadPt,tmpTopZ2TrailingPt = domZ2Cut(ev,Z1LeadVec,Z1TrailingVec,tmpZ1Vec,Z1LeadCharge,Z1TrailingCharge,Z1IsMuon,mZ2VecPairAr,mZ2PtPairAr,mZ2ChargePairAr,tmpZ2Ind,Z2IsMuon,tmpTopZ2LeadPt,tmpTopZ2TrailingPt,fourLepInvMassCut,optLepInvMassCut)
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
                                #Fill with HIGHEST SIP
                                
                                #histIsoAr[-1].Fill(Z1LeadSIP)
                                #histIsoAr[-1].Fill(Z1TrailingSIP)
                                #histIsoAr[-1].Fill(Z2LeadSIP)
                                #histIsoAr[-1].Fill(Z2TrailingSIP)
                                #Loop here
                                
                                
                                """
                                for SIPCutItr in range(cutAmnt):
                                    tmpSIPCut = SIPRange[0]+(SIPCutItr*SIPStep)
                                    passSIPCut = doSIPCut(Z1LeadSIP,Z1TrailingSIP,Z2LeadSIP,Z2TrailingSIP,tmpSIPCut)
                                    if passSIPCut:
                                        tmpSIPCntAr[SIPCutItr] += 1
                                        #if isSignalAr[k]:
                                        #    SIPSignalAr[SIPCutItr] += 1
                                        #else:
                                        #    SIPBackgroundAr[SIPCutItr] += 1
                                """
                                passSIPCut = doSIPCut(Z1LeadSIP,Z1TrailingSIP,Z2LeadSIP,Z2TrailingSIP,SIPCut)
                                if passSIPCut:
                                    if debug:
                                        print("passed SIP cut yay")
                                    tmpZ1PtCutLowCntAr[Z1PtCutLowItr] += 1
            



            #Inv mass cut high loop
            for Z1PtCutHighItr in range(cutAmnt):
                tmpZ1PtCutHigh = Z1PtCutHighRange[0]+(Z1PtCutHighItr*Z1PtCutHighStep)
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

                elecPassesZ2CutsAr = []

                if enoughElecCands: #If enough elec cands, run Z1 cuts
                    
                    Z1LeadItr,Z1TrailingItr,Z1LeadPt,Z1TrailingPt,Z1LeadVec,Z1TrailingVec,Z1LeadCharge,Z1TrailingCharge,Z1IsMuon,difFromZMassOne = doeZ1Cut(ev,elecCandIndAr,elecCandVecAr,elecCandChargeAr,elecPassesZ2CutsAr,Z1IsMuon,invMassCutLow,invMassCutHigh,tmpZ1PtCutHigh,ptTrailingCut,Z1LeadPt,Z1TrailingPt,Z1LeadItr,Z1TrailingItr,Z1LeadVec,Z1TrailingVec,Z1LeadCharge,Z1TrailingCharge,difFromZMassOne)
                muonPassesZ2CutsAr = []
                if enoughMuonCands: #If enough muon cands, run Z1 cuts
                    
                    Z1LeadItr,Z1TrailingItr,Z1LeadPt,Z1TrailingPt,Z1LeadVec,Z1TrailingVec,Z1LeadCharge,Z1TrailingCharge,Z1IsMuon,difFromZMassOne = domZ1Cut(ev,muonCandIndAr,muonCandVecAr,muonCandChargeAr,muonPassesZ2CutsAr,Z1IsMuon,invMassCutLow,invMassCutHigh,tmpZ1PtCutHigh,ptTrailingCut,Z1LeadPt,Z1TrailingPt,Z1LeadItr,Z1TrailingItr,Z1LeadVec,Z1TrailingVec,Z1LeadCharge,Z1TrailingCharge,difFromZMassOne)
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
                        tmpZ2Ind = -1
                        Z2IsMuon = False
                        tmpTopZ2LeadPt = 0
                        tmpTopZ2TrailingPt = 0
                        tmpZ1Vec = Z1LeadVec+Z1TrailingVec

                        
                        if elecPassesZ2CutsFinalAr:
                            tmpZ2Ind,Z2IsMuon,tmpTopZ2LeadPt,tmpTopZ2TrailingPt = doeZ2Cut(ev,Z1LeadVec,Z1TrailingVec,tmpZ1Vec,Z1LeadCharge,Z1TrailingCharge,Z1IsMuon,eZ2VecPairAr,eZ2PtPairAr,eZ2ChargePairAr,tmpZ2Ind,Z2IsMuon,tmpTopZ2LeadPt,tmpTopZ2TrailingPt,fourLepInvMassCut,optLepInvMassCut)

                        if muonPassesZ2CutsFinalAr:
                            tmpZ2Ind,Z2IsMuon,tmpTopZ2LeadPt,tmpTopZ2TrailingPt = domZ2Cut(ev,Z1LeadVec,Z1TrailingVec,tmpZ1Vec,Z1LeadCharge,Z1TrailingCharge,Z1IsMuon,mZ2VecPairAr,mZ2PtPairAr,mZ2ChargePairAr,tmpZ2Ind,Z2IsMuon,tmpTopZ2LeadPt,tmpTopZ2TrailingPt,fourLepInvMassCut,optLepInvMassCut)
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
                                #Fill with HIGHEST SIP
                                
                                #histIsoAr[-1].Fill(Z1LeadSIP)
                                #histIsoAr[-1].Fill(Z1TrailingSIP)
                                #histIsoAr[-1].Fill(Z2LeadSIP)
                                #histIsoAr[-1].Fill(Z2TrailingSIP)
                                #Loop here
                                
                                
                                """
                                for SIPCutItr in range(cutAmnt):
                                    tmpSIPCut = SIPRange[0]+(SIPCutItr*SIPStep)
                                    passSIPCut = doSIPCut(Z1LeadSIP,Z1TrailingSIP,Z2LeadSIP,Z2TrailingSIP,tmpSIPCut)
                                    if passSIPCut:
                                        tmpSIPCntAr[SIPCutItr] += 1
                                        #if isSignalAr[k]:
                                        #    SIPSignalAr[SIPCutItr] += 1
                                        #else:
                                        #    SIPBackgroundAr[SIPCutItr] += 1
                                """
                                passSIPCut = doSIPCut(Z1LeadSIP,Z1TrailingSIP,Z2LeadSIP,Z2TrailingSIP,SIPCut)
                                if passSIPCut:
                                    if debug:
                                        print("passed SIP cut yay")
                                    tmpZ1PtCutHighCntAr[Z1PtCutHighItr] += 1
                            
                            
    for c in range(cutAmnt):
        Z1InvMassCutLowEvPassGraphAr[k].append(tmpZ1InvMassCutLowCntAr[c])
        if isSignalAr[k]:
            Z1InvMassCutLowSignalAr[c] += tmpZ1InvMassCutLowCntAr[c]*weightsAr[k]
        else:
            Z1InvMassCutLowBackgroundAr[c] += tmpZ1InvMassCutLowCntAr[c]*weightsAr[k]
        Z1InvMassCutHighEvPassGraphAr[k].append(tmpZ1InvMassCutHighCntAr[c])
        if isSignalAr[k]:
            Z1InvMassCutHighSignalAr[c] += tmpZ1InvMassCutHighCntAr[c]*weightsAr[k]
        else:
            Z1InvMassCutHighBackgroundAr[c] += tmpZ1InvMassCutHighCntAr[c]*weightsAr[k]

        Z1PtCutLowEvPassGraphAr[k].append(tmpZ1PtCutLowCntAr[c])
        if isSignalAr[k]:
            Z1PtCutLowSignalAr[c] += tmpZ1PtCutLowCntAr[c]*weightsAr[k]
        else:
            Z1PtCutLowBackgroundAr[c] += tmpZ1PtCutLowCntAr[c]*weightsAr[k]
        Z1PtCutHighEvPassGraphAr[k].append(tmpZ1PtCutHighCntAr[c])
        if isSignalAr[k]:
            Z1PtCutHighSignalAr[c] += tmpZ1PtCutHighCntAr[c]*weightsAr[k]
        else:
            Z1PtCutHighBackgroundAr[c] += tmpZ1PtCutHighCntAr[c]*weightsAr[k]
    if extraOut:
        print(nameAr[k])
        print("Z1InvMassCutLowSignalAr",Z1InvMassCutLowSignalAr)
        print("Z1InvMassCutLowBackgroundAr",Z1InvMassCutLowBackgroundAr)
        print("Z1InvMassCutHighSignalAr",Z1InvMassCutHighSignalAr)
        print("Z1InvMassCutHighBackgroundAr",Z1InvMassCutHighBackgroundAr)
        print("Z1PtCutLowSignalAr",Z1PtCutLowSignalAr)
        print("Z1PtCutLowBackgroundAr",Z1PtCutLowBackgroundAr)
        print("Z1PtCutHighSignalAr",Z1PtCutHighSignalAr)
        print("Z1PtCutHighBackgroundAr",Z1PtCutHighBackgroundAr)
#print(passesCandCutsCtr)
#print(passesZ1CutsCtr)
#print(passesZ2CutsCtr)
#print(passesZ1InvMassCutLowCutCtr)
#print(passesAllCutsCtr)
#print(allPassAr)
if extraOut:
    print(Z1InvMassCutLowSignalAr)
    print(Z1InvMassCutLowBackgroundAr)
    print(Z1InvMassCutHighSignalAr)
    print(Z1InvMassCutHighBackgroundAr)
    print(Z1PtCutLowSignalAr)
    print(Z1PtCutLowBackgroundAr)
    print(Z1PtCutHighSignalAr)
    print(Z1PtCutHighBackgroundAr)

if debugV2GraphMaking:
    print("starting Inv Mass Cut Low graphs")
##############INV MASS CUT LOW##############
Z1InvMassCutLowGraphAr = array('d')
Z1InvMassCutLowXAr = array('d')

if debugV2GraphMaking:
    print("Doing FoMCalc")
    print("Z1InvMassCutLowXAr",Z1InvMassCutLowXAr,"cutAmnt",cutAmnt,"Z1InvMassCutLowRange",Z1InvMassCutLowRange,"Z1InvMassCutLowStep",Z1InvMassCutLowStep)
FoMCalc(Z1InvMassCutLowSignalAr,Z1InvMassCutLowBackgroundAr,Z1InvMassCutLowGraphAr,Z1InvMassCutLowXAr,cutAmnt,Z1InvMassCutLowRange,Z1InvMassCutLowStep)

if debugV2GraphMaking:
    print("Finished FoMCalc")
    print("Z1InvMassCutLowGraphAr",Z1InvMassCutLowGraphAr,"Z1InvMassCutLowXAr",Z1InvMassCutLowXAr)

evPassZ1InvMassCutLowCanAr = []
evPassZ1InvMassCutLowGraphAr = []
print("Done.","time:",time.time()-startt)

#make evpass graphs

cutName = "Z1InvMassCutLow"

if not skipEvPassGraphs:
    if debugV2GraphMaking:
        print("Making EvPass Graphs")
        print("nameAr",nameAr,"evPassZ1InvMassCutLowCanAr",evPassZ1InvMassCutLowCanAr,"Z1InvMassCutLowEvPassGraphAr",Z1InvMassCutLowEvPassGraphAr,"evPassZ1InvMassCutLowGraphAr",evPassZ1InvMassCutLowGraphAr,"Z1InvMassCutLowXAr",Z1InvMassCutLowXAr,"cutName",cutName)
    makeEvPassGraphs(nameAr,evPassZ1InvMassCutLowCanAr,Z1InvMassCutLowEvPassGraphAr,evPassZ1InvMassCutLowGraphAr,Z1InvMassCutLowXAr,cutName)


padAr = []
legAr = []

if debugV2GraphMaking:
    print("Making signal and background names")
    print("sumQCD",sumQCD,"isQCDAr",isQCDAr,"isSignalAr",isSignalAr)

signalName = ""
backgroundName = ""
for k,fileA in enumerate(fileAr):
    if not sumQCD or not isQCDAr[k]:
        if isSignalAr[k]:
            signalName += "_"+saveNameAr[k]

        else:
            backgroundName += "_"+saveNameAr[k]

if debugV2GraphMaking:
    print("Finished signal and background names")
    print("signalName",signalName,"backgroundName",backgroundName,"isSignalAr",isSignalAr)


if sumQCD:
    if debugV2GraphMaking:
        print("Summing up QCD")
        print("histZ1InvMassCutLowAr",histZ1InvMassCutLowAr,"weightsAr",weightsAr)
    backgroundName += "_QCDSum"
    QCDSumHist = TH1D("Z1InvMassCutLowHistQCDSum","Z1InvMassCutLowHistQCDSum", binAmnt, Z1InvMassCutLowRange[0], Z1InvMassCutLowRange[1])
    for k in range(len(histZ1InvMassCutLowAr)):

        if isQCDAr[k]:
            histZ1InvMassCutLowAr[k].Sumw2()
            QCDSumHist.Sumw2()
            QCDSumHist.Add(histZ1InvMassCutLowAr[k],weightsAr[k])
    if debugV2GraphMaking:
        print("Finished summing up QCD")
        print("QCDSumHist",QCDSumHist,"backgroundName",backgroundName)
else:
    QCDSumHist = 0



FoMZ1InvMassCutLowCan = TCanvas("c1Z1InvMassCutLow","c1Z1InvMassCutLow",3600,2400)
setUpLegend(legAr)
setUpPadsAr(padAr,"{0}Pad".format("Z1InvMassCutLow"))
padAr[-1][0].Draw()
padAr[-1][0].cd()

#Make top plot
#First set histogram elements (color, etc)
intZ1InvMassCutLowAr = []

if debugV2GraphMaking:
    print("Setting up aesthetics of histos and getting int sums")
    print("nameAr",nameAr,"colorAr",colorAr,"sumQCD",sumQCD,"QCDSumHist",QCDSumHist,"isQCDAr",isQCDAr,"histZ1InvMassCutLowAr",histZ1InvMassCutLowAr,"isSignalAr",isSignalAr,"cutName",cutName,"normalizeBackgroundsTogether",normalizeBackgroundsTogether,"intZ1InvMassCutLowAr",intZ1InvMassCutLowAr)
backgroundIntSum,QCDSumInt = setHistoElements(nameAr,colorAr,sumQCD,QCDSumHist,isQCDAr,histZ1InvMassCutLowAr,isSignalAr,cutName,normalizeBackgroundsTogether,weightsAr,intZ1InvMassCutLowAr)

if debugV2GraphMaking:
    print("Finished aesthetics and int sum")
    print("backgroundIntSum",backgroundIntSum,"QCDSumInt",QCDSumInt,"intZ1InvMassCutLowAr",intZ1InvMassCutLowAr)


if variableRebin:
    doVariableRebinning(histZ1InvMassCutLowAr,isSignalAr,variableRebinVar,binAmnt,Z1InvMassCutLowRange,sumQCD,nameAr,QCDSumHist,cutName,weightsAr)

if debugV2GraphMaking:
    print("Normalizing hists")
    print("histZ1InvMassCutLowAr",histZ1InvMassCutLowAr,"sumQCD",sumQCD,"isQCDAr",isQCDAr,"normalizeBackgroundsTogether",normalizeBackgroundsTogether,"backgroundIntSum",backgroundIntSum,"isSignalAr",isSignalAr,"weightsAr",weightsAr,"legAr",legAr,"nameAr",nameAr,"intZ1InvMassCutLowAr",intZ1InvMassCutLowAr)

histMax = normalizeHists(histZ1InvMassCutLowAr,sumQCD,isQCDAr,normalizeBackgroundsTogether,backgroundIntSum,isSignalAr,weightsAr,legAr,nameAr,intZ1InvMassCutLowAr)

if debugV2GraphMaking:
    print("Finished normalizing hists")
    print("histMax",histMax)


if sumQCD:
    if debugV2GraphMaking:
        print("Scaling QCD sum hist")
        print("histMax",histMax,"QCDSumInt",QCDSumInt,"QCDSumHist",QCDSumHist)
    if QCDSumInt:
        histMax = scaleQCDHist(QCDSumInt,QCDSumHist,histMax,legAr)
    if debugV2GraphMaking:
        print("Scaled QCD sum hist")
        print("histMax",histMax)

histZ1InvMassCutLowStack = THStack("hist{0}Stack".format(cutName),"Events Passing All Cuts Vs {0} Cut Value".format(cutName))


maxInt = addHistsToStack(histZ1InvMassCutLowAr,isSignalAr,sumQCD,isQCDAr,histZ1InvMassCutLowStack,QCDSumHist,normalizeBackgroundsTogether,backgroundIntSum)

invHistsAr = []
drawInvAr = []

setUpInvHists(histZ1InvMassCutLowAr,isSignalAr,sumQCD,isQCDAr,invHistsAr,nameAr,intZ1InvMassCutLowAr,drawInvAr,QCDSumInt,QCDSumHist,cutName)

FoMZ1InvMassCutLowGraph = TGraph(len(Z1InvMassCutLowGraphAr),Z1InvMassCutLowXAr,Z1InvMassCutLowGraphAr)



setUpStackedHistAndDrawFoMPlot(histMax,histZ1InvMassCutLowAr,histZ1InvMassCutLowStack,invHistsAr,drawInvAr,legAr,FoMZ1InvMassCutLowCan,padAr,FoMZ1InvMassCutLowGraph,Z1InvMassCutLowRange,normalizeBackgroundsTogether,cutName,signalName,backgroundName)

FoMZ1InvMassCutLow2Can = TCanvas("c2Z1InvMassCutLow","c2Z1InvMassCutLow",3600,2400)
if debugV2GraphMaking:
    print("Making non-stacked hist and fom plot")
    print("FoMZ1InvMassCutLow2Can",FoMZ1InvMassCutLow2Can,"cutName",cutName,"padAr",padAr,"histMax",histMax,"QCDSumInt",QCDSumInt,"QCDSumHist",QCDSumHist)

setUpNonStackedHistAndFoMPlot(FoMZ1InvMassCutLow2Can,cutName,padAr,sumQCD,QCDSumHist,histMax,isSignalAr,isQCDAr,normalizeBackgroundsTogether,maxInt,histZ1InvMassCutLowAr,legAr,FoMZ1InvMassCutLowGraph,signalName,backgroundName)





##############INV MASS CUT HIGH##############

Z1InvMassCutHighGraphAr = array('d')
Z1InvMassCutHighXAr = array('d')

FoMCalc(Z1InvMassCutHighSignalAr,Z1InvMassCutHighBackgroundAr,Z1InvMassCutHighGraphAr,Z1InvMassCutHighXAr,cutAmnt,Z1InvMassCutHighRange,Z1InvMassCutHighStep)

evPassZ1InvMassCutHighCanAr = []
evPassZ1InvMassCutHighGraphAr = []
print("Done.","time:",time.time()-startt)

#make evpass graphs

cutName = "Z1InvMassCutHigh"

if not skipEvPassGraphs:
    makeEvPassGraphs(nameAr,evPassZ1InvMassCutHighCanAr,Z1InvMassCutHighEvPassGraphAr,evPassZ1InvMassCutHighGraphAr,Z1InvMassCutHighXAr,cutName)

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
    QCDSumHist = TH1D("Z1InvMassCutHighHistQCDSum","Z1InvMassCutHighHistQCDSum", binAmnt, Z1InvMassCutHighRange[0], Z1InvMassCutHighRange[1])
    for k in range(len(histZ1InvMassCutHighAr)):

        if isQCDAr[k]:
            histZ1InvMassCutHighAr[k].Sumw2()
            QCDSumHist.Sumw2()
            QCDSumHist.Add(histZ1InvMassCutHighAr[k],weightsAr[k])


FoMZ1InvMassCutHighCan = TCanvas("c1Z1InvMassCutHigh","c1Z1InvMassCutHigh",3600,2400)
setUpLegend(legAr)
setUpPadsAr(padAr,"{0}Pad".format("Z1InvMassCutHigh"))
padAr[-1][0].Draw()
padAr[-1][0].cd()
#Make top plot
#First set histogram elements (color, etc)
intZ1InvMassCutHighAr = []

backgroundIntSum,QCDSumInt = setHistoElements(nameAr,colorAr,sumQCD,QCDSumHist,isQCDAr,histZ1InvMassCutHighAr,isSignalAr,cutName,normalizeBackgroundsTogether,weightsAr,intZ1InvMassCutHighAr)

if variableRebin:
    doVariableRebinning(histZ1InvMassCutHighAr,isSignalAr,variableRebinVar,binAmnt,Z1InvMassCutHighRange,sumQCD,nameAr,QCDSumHist,cutName,weightsAr)

histMax = normalizeHists(histZ1InvMassCutHighAr,sumQCD,isQCDAr,normalizeBackgroundsTogether,backgroundIntSum,isSignalAr,weightsAr,legAr,nameAr,intZ1InvMassCutHighAr)

if sumQCD:
    if QCDSumInt:
        histMax = scaleQCDHist(QCDSumInt,QCDSumHist,histMax,legAr)

histZ1InvMassCutHighStack = THStack("hist{0}Stack".format(cutName),"Events Passing All Cuts Vs {0} Cut Value".format(cutName))

maxInt = addHistsToStack(histZ1InvMassCutHighAr,isSignalAr,sumQCD,isQCDAr,histZ1InvMassCutHighStack,QCDSumHist,normalizeBackgroundsTogether,backgroundIntSum)

invHistsAr = []
drawInvAr = []

setUpInvHists(histZ1InvMassCutHighAr,isSignalAr,sumQCD,isQCDAr,invHistsAr,nameAr,intZ1InvMassCutHighAr,drawInvAr,QCDSumInt,QCDSumHist,cutName)

FoMZ1InvMassCutHighGraph = TGraph(len(Z1InvMassCutHighGraphAr),Z1InvMassCutHighXAr,Z1InvMassCutHighGraphAr)

setUpStackedHistAndDrawFoMPlot(histMax,histZ1InvMassCutHighAr,histZ1InvMassCutHighStack,invHistsAr,drawInvAr,legAr,FoMZ1InvMassCutHighCan,padAr,FoMZ1InvMassCutHighGraph,Z1InvMassCutHighRange,normalizeBackgroundsTogether,cutName,signalName,backgroundName)

FoMZ1InvMassCutHigh2Can = TCanvas("c2Z1InvMassCutHigh","c2Z1InvMassCutHigh",3600,2400)
setUpNonStackedHistAndFoMPlot(FoMZ1InvMassCutHigh2Can,cutName,padAr,sumQCD,QCDSumHist,histMax,isSignalAr,isQCDAr,normalizeBackgroundsTogether,maxInt,histZ1InvMassCutHighAr,legAr,FoMZ1InvMassCutHighGraph,signalName,backgroundName)

##############PT CUT LOW##############

Z1PtCutLowGraphAr = array('d')
Z1PtCutLowXAr = array('d')

FoMCalc(Z1PtCutLowSignalAr,Z1PtCutLowBackgroundAr,Z1PtCutLowGraphAr,Z1PtCutLowXAr,cutAmnt,Z1PtCutLowRange,Z1PtCutLowStep)

evPassZ1PtCutLowCanAr = []
evPassZ1PtCutLowGraphAr = []
print("Done.","time:",time.time()-startt)

#make evpass graphs

cutName = "Z1PtCutLow"

if not skipEvPassGraphs:
    makeEvPassGraphs(nameAr,evPassZ1PtCutLowCanAr,Z1PtCutLowEvPassGraphAr,evPassZ1PtCutLowGraphAr,Z1PtCutLowXAr,cutName)

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
    QCDSumHist = TH1D("Z1PtCutLowHistQCDSum","Z1PtCutLowHistQCDSum", binAmnt, Z1PtCutLowRange[0], Z1PtCutLowRange[1])
    for k in range(len(histZ1PtCutLowAr)):

        if isQCDAr[k]:
            histZ1PtCutLowAr[k].Sumw2()
            QCDSumHist.Sumw2()
            QCDSumHist.Add(histZ1PtCutLowAr[k],weightsAr[k])


FoMZ1PtCutLowCan = TCanvas("c1Z1PtCutLow","c1Z1PtCutLow",3600,2400)
setUpLegend(legAr)
setUpPadsAr(padAr,"{0}Pad".format("Z1PtCutLow"))
padAr[-1][0].Draw()
padAr[-1][0].cd()
#Make top plot
#First set histogram elements (color, etc)
intZ1PtCutLowAr = []

backgroundIntSum,QCDSumInt = setHistoElements(nameAr,colorAr,sumQCD,QCDSumHist,isQCDAr,histZ1PtCutLowAr,isSignalAr,cutName,normalizeBackgroundsTogether,weightsAr,intZ1PtCutLowAr)

if variableRebin:
    doVariableRebinning(histZ1PtCutLowAr,isSignalAr,variableRebinVar,binAmnt,Z1PtCutLowRange,sumQCD,nameAr,QCDSumHist,cutName,weightsAr)

histMax = normalizeHists(histZ1PtCutLowAr,sumQCD,isQCDAr,normalizeBackgroundsTogether,backgroundIntSum,isSignalAr,weightsAr,legAr,nameAr,intZ1PtCutLowAr)

if sumQCD:
    if QCDSumInt:
        histMax = scaleQCDHist(QCDSumInt,QCDSumHist,histMax,legAr)

histZ1PtCutLowStack = THStack("hist{0}Stack".format(cutName),"Events Passing All Cuts Vs {0} Cut Value".format(cutName))

maxInt = addHistsToStack(histZ1PtCutLowAr,isSignalAr,sumQCD,isQCDAr,histZ1PtCutLowStack,QCDSumHist,normalizeBackgroundsTogether,backgroundIntSum)

invHistsAr = []
drawInvAr = []

setUpInvHists(histZ1PtCutLowAr,isSignalAr,sumQCD,isQCDAr,invHistsAr,nameAr,intZ1PtCutLowAr,drawInvAr,QCDSumInt,QCDSumHist,cutName)

FoMZ1PtCutLowGraph = TGraph(len(Z1PtCutLowGraphAr),Z1PtCutLowXAr,Z1PtCutLowGraphAr)

setUpStackedHistAndDrawFoMPlot(histMax,histZ1PtCutLowAr,histZ1PtCutLowStack,invHistsAr,drawInvAr,legAr,FoMZ1PtCutLowCan,padAr,FoMZ1PtCutLowGraph,Z1PtCutLowRange,normalizeBackgroundsTogether,cutName,signalName,backgroundName)

FoMZ1PtCutLow2Can = TCanvas("c2Z1PtCutLow","c2Z1PtCutLow",3600,2400)
setUpNonStackedHistAndFoMPlot(FoMZ1PtCutLow2Can,cutName,padAr,sumQCD,QCDSumHist,histMax,isSignalAr,isQCDAr,normalizeBackgroundsTogether,maxInt,histZ1PtCutLowAr,legAr,FoMZ1PtCutLowGraph,signalName,backgroundName)

##############PT CUT HIGH##############

Z1PtCutHighGraphAr = array('d')
Z1PtCutHighXAr = array('d')


FoMCalc(Z1PtCutHighSignalAr,Z1PtCutHighBackgroundAr,Z1PtCutHighGraphAr,Z1PtCutHighXAr,cutAmnt,Z1PtCutHighRange,Z1PtCutHighStep)

evPassZ1PtCutHighCanAr = []
evPassZ1PtCutHighGraphAr = []
print("Done.","time:",time.time()-startt)

#make evpass graphs

cutName = "Z1PtCutHigh"

if not skipEvPassGraphs:
    makeEvPassGraphs(nameAr,evPassZ1PtCutHighCanAr,Z1PtCutHighEvPassGraphAr,evPassZ1PtCutHighGraphAr,Z1PtCutHighXAr,cutName)

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
    QCDSumHist = TH1D("Z1PtCutHighHistQCDSum","Z1PtCutHighHistQCDSum", binAmnt, Z1PtCutHighRange[0], Z1PtCutHighRange[1])
    for k in range(len(histZ1PtCutHighAr)):

        if isQCDAr[k]:
            histZ1PtCutHighAr[k].Sumw2()
            QCDSumHist.Sumw2()
            QCDSumHist.Add(histZ1PtCutHighAr[k],weightsAr[k])


FoMZ1PtCutHighCan = TCanvas("c1Z1PtCutHigh","c1Z1PtCutHigh",3600,2400)
setUpLegend(legAr)
setUpPadsAr(padAr,"{0}Pad".format("Z1PtCutHigh"))
padAr[-1][0].Draw()
padAr[-1][0].cd()
#Make top plot
#First set histogram elements (color, etc)
intZ1PtCutHighAr = []



backgroundIntSum,QCDSumInt = setHistoElements(nameAr,colorAr,sumQCD,QCDSumHist,isQCDAr,histZ1PtCutHighAr,isSignalAr,cutName,normalizeBackgroundsTogether,weightsAr,intZ1PtCutHighAr)

if variableRebin:
    doVariableRebinning(histZ1PtCutHighAr,isSignalAr,variableRebinVar,binAmnt,Z1PtCutHighRange,sumQCD,nameAr,QCDSumHist,cutName,weightsAr)

histMax = normalizeHists(histZ1PtCutHighAr,sumQCD,isQCDAr,normalizeBackgroundsTogether,backgroundIntSum,isSignalAr,weightsAr,legAr,nameAr,intZ1PtCutHighAr)

if sumQCD:
    if QCDSumInt:
        histMax = scaleQCDHist(QCDSumInt,QCDSumHist,histMax,legAr)

histZ1PtCutHighStack = THStack("hist{0}Stack".format(cutName),"Events Passing All Cuts Vs {0} Cut Value".format(cutName))

maxInt = addHistsToStack(histZ1PtCutHighAr,isSignalAr,sumQCD,isQCDAr,histZ1PtCutHighStack,QCDSumHist,normalizeBackgroundsTogether,backgroundIntSum)

invHistsAr = []
drawInvAr = []

setUpInvHists(histZ1PtCutHighAr,isSignalAr,sumQCD,isQCDAr,invHistsAr,nameAr,intZ1PtCutHighAr,drawInvAr,QCDSumInt,QCDSumHist,cutName)

FoMZ1PtCutHighGraph = TGraph(len(Z1PtCutHighGraphAr),Z1PtCutHighXAr,Z1PtCutHighGraphAr)

setUpStackedHistAndDrawFoMPlot(histMax,histZ1PtCutHighAr,histZ1PtCutHighStack,invHistsAr,drawInvAr,legAr,FoMZ1PtCutHighCan,padAr,FoMZ1PtCutHighGraph,Z1PtCutHighRange,normalizeBackgroundsTogether,cutName,signalName,backgroundName)

FoMZ1PtCutHigh2Can = TCanvas("c2Z1PtCutHigh","c2Z1PtCutHigh",3600,2400)
setUpNonStackedHistAndFoMPlot(FoMZ1PtCutHigh2Can,cutName,padAr,sumQCD,QCDSumHist,histMax,isSignalAr,isQCDAr,normalizeBackgroundsTogether,maxInt,histZ1PtCutHighAr,legAr,FoMZ1PtCutHighGraph,signalName,backgroundName)

