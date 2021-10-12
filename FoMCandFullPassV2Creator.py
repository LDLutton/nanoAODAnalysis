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
ttZJetsBackground = False
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
ePtRange = [0,100]
ePtStep = (ePtRange[1]-ePtRange[0])/cutAmnt
ePtSignalAr = [0 for i in range(cutAmnt)] 
ePtBackgroundAr = [0 for i in range(cutAmnt)] 

eEtaCut = 2.5
eEtaRange = [0,4]
eEtaStep = (eEtaRange[1]-eEtaRange[0])/cutAmnt
eEtaSignalAr = [0 for i in range(cutAmnt)] 
eEtaBackgroundAr = [0 for i in range(cutAmnt)] 

mPtCut = 5
mPtRange = [0,100]
mPtStep = (mPtRange[1]-mPtRange[0])/cutAmnt
mPtSignalAr = [0 for i in range(cutAmnt)] 
mPtBackgroundAr = [0 for i in range(cutAmnt)] 
mEtaCut = 2.4
mEtaRange = [0,4]
mEtaStep = (mEtaRange[1]-mEtaRange[0])/cutAmnt
mEtaSignalAr = [0 for i in range(cutAmnt)] 
mEtaBackgroundAr = [0 for i in range(cutAmnt)] 


invMassCutLow=60
invMassCutHigh=120
ptLeadCut=20
ptTrailingCut=10

fourLepInvMassCut = 100
optLepInvMassCut = 12
lepIsoCut = 0.35


SIPCut = 4



ePtEvPassGraphAr = []
eEtaEvPassGraphAr = []
mPtEvPassGraphAr = []
mEtaEvPassGraphAr = []
for nameA in nameAr:
    ePtEvPassGraphAr.append(array('d'))
    eEtaEvPassGraphAr.append(array('d'))
    mPtEvPassGraphAr.append(array('d'))
    mEtaEvPassGraphAr.append(array('d'))

histePtAr = []
histeEtaAr = []
histmPtAr = []
histmEtaAr = []

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
    tmpePtCntAr = [0 for cutItr in range(cutAmnt)]
    histePtAr.append(TH1D("ePtHist{0}".format(nameAr[k]),"ePtHist{0}".format(nameAr[k]), binAmnt, ePtRange[0], ePtRange[1]))
    tmpeEtaCntAr = [0 for cutItr in range(cutAmnt)]
    histeEtaAr.append(TH1D("eEtaHist{0}".format(nameAr[k]),"eEtaHist{0}".format(nameAr[k]), binAmnt, eEtaRange[0], eEtaRange[1]))
    tmpmPtCntAr = [0 for cutItr in range(cutAmnt)]
    histmPtAr.append(TH1D("mPtHist{0}".format(nameAr[k]),"mPtHist{0}".format(nameAr[k]), binAmnt, mPtRange[0], mPtRange[1]))
    tmpmEtaCntAr = [0 for cutItr in range(cutAmnt)]
    histmEtaAr.append(TH1D("mEtaHist{0}".format(nameAr[k]),"mEtaHist{0}".format(nameAr[k]), binAmnt, mEtaRange[0], mEtaRange[1]))
    
    #LOOP OVER EVENTS IN FILE k
    for j,ev in enumerate(CTree):
        if debug:
            if j < debugMin:
                continue
            if j > debugMax:
                break
        if j % 10000 == 0:
            print("event {0} in file {1}".format(j,k))
        neLep = ev.neLep
        nmLep = ev.nmLep
        eHLT = ev.eHLT
        emHLT = ev.emHLT
        mHLT = ev.mHLT
        if neLep:
            enoughMuonCands = False
            negMuonCands = 0
            posMuonCands = 0
            totMuonCands = 0
            muonCandIndAr = []
            muonCandVecAr = []
            muonCandChargeAr = []

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
            

            #Now fill histogram with ePt and eEta based on whether or not the remaining electrons could make this event qualify if it doesn't yet
            tmpElecPos = 0
            tmpElecNeg = 0
            if eHLT or emHLT:
                for elecItr in range(neLep):
                    if ev.eCharge[elecItr] == 1:
                        tmpElecPos += 1
                    else:
                        tmpElecNeg += 1
            tmpTotElecCands = min(tmpElecNeg,tmpElecPos)
            if tmpTotElecCands + totMuonCands >= 2:
                #Fill histos if any elec pairs possible
                if tmpTotElecCands:
                    for elecItr in range(neLep):
                        histePtAr[-1].Fill(ev.ePt[elecItr])
                        histeEtaAr[-1].Fill(ev.eEta[elecItr])
                #Do the ePt cut loop
                for ePtCutItr in range(cutAmnt):
                    tmpePtCut = ePtRange[0]+(ePtCutItr*ePtStep)

                    enoughElecCands = False
                    negElecCands = 0
                    posElecCands = 0
                    totElecCands = 0
                    elecCandIndAr = []
                    elecCandVecAr = []
                    elecCandChargeAr = []
                    
                    if eHLT or emHLT:
                        doeCandCut(ev,neLep,elecCandIndAr,elecCandVecAr,elecCandChargeAr,tmpePtCut,eEtaCut)
                        for elecCandCharge in elecCandChargeAr:
                            if elecCandCharge == -1:
                                negElecCands += 1
                            else:
                                posElecCands += 1
                        totElecCands = min(negElecCands,posElecCands)
                        if totElecCands >= 1:
                            enoughElecCands = True


                
                    
                    if debug:
                        print("--------------------------------------------")
                        print("j",j,"ev.evInd",ev.evInd,"neLep",neLep)
                        for tmpItr in range(neLep):
                            print("tmpItr",tmpItr,"ev.ePt[tmpItr]",ev.ePt[tmpItr],"ev.eEta[tmpItr]",ev.eEta[tmpItr],"ev.eCharge[tmpItr]",ev.eCharge[tmpItr])
                    
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
                            Z1LeadItr,Z1TrailingItr,Z1LeadPt,Z1TrailingPt,Z1LeadVec,Z1TrailingVec,Z1LeadCharge,Z1TrailingCharge,Z1IsMuon,difFromZMassOne = doeZ1Cut(ev,elecCandIndAr,elecCandVecAr,elecCandChargeAr,elecPassesZ2CutsAr,Z1IsMuon,invMassCutLow,invMassCutHigh,ptLeadCut,ptTrailingCut,Z1LeadPt,Z1TrailingPt,Z1LeadItr,Z1TrailingItr,Z1LeadVec,Z1TrailingVec,Z1LeadCharge,Z1TrailingCharge,difFromZMassOne,debug)
                        muonPassesZ2CutsAr = []
                        if enoughMuonCands: #If enough muon cands, run Z1 cuts
                            
                            Z1LeadItr,Z1TrailingItr,Z1LeadPt,Z1TrailingPt,Z1LeadVec,Z1TrailingVec,Z1LeadCharge,Z1TrailingCharge,Z1IsMuon,difFromZMassOne = domZ1Cut(ev,muonCandIndAr,muonCandVecAr,muonCandChargeAr,muonPassesZ2CutsAr,Z1IsMuon,invMassCutLow,invMassCutHigh,ptLeadCut,ptTrailingCut,Z1LeadPt,Z1TrailingPt,Z1LeadItr,Z1TrailingItr,Z1LeadVec,Z1TrailingVec,Z1LeadCharge,Z1TrailingCharge,difFromZMassOne,debug)
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
                                            tmpePtCntAr[ePtCutItr] += 1


                
                #Do the eEta cut loop
                for eEtaCutItr in range(cutAmnt):
                    tmpeEtaCut = eEtaRange[0]+(eEtaCutItr*eEtaStep)

                    enoughElecCands = False
                    negElecCands = 0
                    posElecCands = 0
                    totElecCands = 0
                    elecCandIndAr = []
                    elecCandVecAr = []
                    elecCandChargeAr = []
                    
                    if eHLT or emHLT:
                        doeCandCut(ev,neLep,elecCandIndAr,elecCandVecAr,elecCandChargeAr,ePtCut,tmpeEtaCut)
                        for elecCandCharge in elecCandChargeAr:
                            if elecCandCharge == -1:
                                negElecCands += 1
                            else:
                                posElecCands += 1
                        totElecCands = min(negElecCands,posElecCands)
                        if totElecCands >= 1:
                            enoughElecCands = True


                
                    
                    if debug:
                        print("--------------------------------------------")
                        print("j",j,"ev.evInd",ev.evInd,"neLep",neLep)
                        for tmpItr in range(neLep):
                            print("tmpItr",tmpItr,"ev.ePt[tmpItr]",ev.ePt[tmpItr],"ev.eEta[tmpItr]",ev.eEta[tmpItr],"ev.eCharge[tmpItr]",ev.eCharge[tmpItr])
                    
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
                                            tmpeEtaCntAr[eEtaCutItr] += 1
        if nmLep:
            enoughElecCands = False
            negElecCands = 0
            posElecCands = 0
            totElecCands = 0
            elecCandIndAr = []
            elecCandVecAr = []
            elecCandChargeAr = []

            if neLep:
                eHLT = ev.mHLT
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
            #Now fill histogram with mPt and mEta based on whether or not the remaining muons could make this event qualify if it doesn't yet
            tmpMuonPos = 0
            tmpMuonNeg = 0
            if eHLT or emHLT:
                for muonItr in range(neLep):
                    if ev.eCharge[muonItr] == 1:
                        tmpMuonPos += 1
                    else:
                        tmpMuonNeg += 1
            tmpTotMuonCands = min(tmpMuonNeg,tmpMuonPos)
            if tmpTotMuonCands + totMuonCands >= 2:
                #Fill histos if any muon pairs possible
                if tmpTotMuonCands:
                    for muonItr in range(nmLep):
                        histmPtAr[-1].Fill(ev.mPt[muonItr])
                        histmEtaAr[-1].Fill(ev.mEta[muonItr])
                #Do the mPt cut loop
                for mPtCutItr in range(cutAmnt):
                    tmpmPtCut = mPtRange[0]+(mPtCutItr*mPtStep)

                    enoughMuonCands = False
                    negMuonCands = 0
                    posMuonCands = 0
                    totMuonCands = 0
                    muonCandIndAr = []
                    muonCandVecAr = []
                    muonCandChargeAr = []
                    
                    if mHLT or emHLT:
                        domCandCut(ev,nmLep,muonCandIndAr,muonCandVecAr,muonCandChargeAr,tmpmPtCut,mEtaCut)
                        for muonCandCharge in muonCandChargeAr:
                            if muonCandCharge == -1:
                                negMuonCands += 1
                            else:
                                posMuonCands += 1
                        totMuonCands = min(negMuonCands,posMuonCands)
                        if totMuonCands >= 1:
                            enoughMuonCands = True


                
                    
                    if debug:
                        print("--------------------------------------------")
                        print("j",j,"ev.evInd",ev.evInd,"neLep",neLep)
                        for tmpItr in range(neLep):
                            print("tmpItr",tmpItr,"ev.ePt[tmpItr]",ev.ePt[tmpItr],"ev.eEta[tmpItr]",ev.eEta[tmpItr],"ev.eCharge[tmpItr]",ev.eCharge[tmpItr])
                    
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
                                            tmpmPtCntAr[mPtCutItr] += 1


                
                #Do the mEta cut loop
                for mEtaCutItr in range(cutAmnt):
                    tmpmEtaCut = mEtaRange[0]+(mEtaCutItr*mEtaStep)

                    enoughMuonCands = False
                    negMuonCands = 0
                    posMuonCands = 0
                    totMuonCands = 0
                    muonCandIndAr = []
                    muonCandVecAr = []
                    muonCandChargeAr = []
                    
                    if eHLT or emHLT:
                        domCandCut(ev,nmLep,muonCandIndAr,muonCandVecAr,muonCandChargeAr,mPtCut,tmpmEtaCut)
                        for muonCandCharge in muonCandChargeAr:
                            if muonCandCharge == -1:
                                negMuonCands += 1
                            else:
                                posMuonCands += 1
                        totMuonCands = min(negMuonCands,posMuonCands)
                        if totMuonCands >= 1:
                            enoughMuonCands = True


                
                    
                    if debug:
                        print("--------------------------------------------")
                        print("j",j,"ev.evInd",ev.evInd,"neLep",neLep)
                        for tmpItr in range(neLep):
                            print("tmpItr",tmpItr,"ev.ePt[tmpItr]",ev.ePt[tmpItr],"ev.eEta[tmpItr]",ev.eEta[tmpItr],"ev.eCharge[tmpItr]",ev.eCharge[tmpItr])
                    
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
                                            tmpmEtaCntAr[mEtaCutItr] += 1
                
                                
                            
    for c in range(cutAmnt):
        ePtEvPassGraphAr[k].append(tmpePtCntAr[c])
        if isSignalAr[k]:
            ePtSignalAr[c] += tmpePtCntAr[c]*weightsAr[k]
        else:
            ePtBackgroundAr[c] += tmpePtCntAr[c]*weightsAr[k]
        eEtaEvPassGraphAr[k].append(tmpeEtaCntAr[c])
        if isSignalAr[k]:
            eEtaSignalAr[c] += tmpeEtaCntAr[c]*weightsAr[k]
        else:
            eEtaBackgroundAr[c] += tmpeEtaCntAr[c]*weightsAr[k]
        mPtEvPassGraphAr[k].append(tmpmPtCntAr[c])
        if isSignalAr[k]:
            mPtSignalAr[c] += tmpmPtCntAr[c]*weightsAr[k]
        else:
            mPtBackgroundAr[c] += tmpmPtCntAr[c]*weightsAr[k]
        mEtaEvPassGraphAr[k].append(tmpmEtaCntAr[c])
        if isSignalAr[k]:
            mEtaSignalAr[c] += tmpmEtaCntAr[c]*weightsAr[k]
        else:
            mEtaBackgroundAr[c] += tmpmEtaCntAr[c]*weightsAr[k]
    if extraOut:
        print(nameAr[k])
        print("ePtSignalAr",ePtSignalAr)
        print("ePtBackgroundAr",ePtBackgroundAr)
        print("eEtaSignalAr",eEtaSignalAr)
        print("eEtaBackgroundAr",eEtaBackgroundAr)
        print("mPtSignalAr",mPtSignalAr)
        print("mPtBackgroundAr",mPtBackgroundAr)
        print("mEtaSignalAr",mEtaSignalAr)
        print("mEtaBackgroundAr",mEtaBackgroundAr)
#print(passesCandCutsCtr)
#print(passesZ1CutsCtr)
#print(passesZ2CutsCtr)
#print(passesIsoCutCtr)
#print(passesAllCutsCtr)
#print(allPassAr)
if extraOut:
    print(ePtSignalAr)
    print(ePtBackgroundAr)
    print(eEtaSignalAr)
    print(eEtaBackgroundAr)
    print(mPtSignalAr)
    print(mPtBackgroundAr)
    print(mEtaSignalAr)
    print(mEtaBackgroundAr)


##############ELECTRON PT CUT##############

ePtGraphAr = array('d')
ePtXAr = array('d')

FoMCalc(ePtSignalAr,ePtBackgroundAr,ePtGraphAr,ePtXAr,cutAmnt,ePtRange,ePtStep)

evPassePtCanAr = []
evPassePtGraphAr = []
print("Done.","time:",time.time()-startt)

#make evpass graphs

cutName = "ePt"

if not skipEvPassGraphs:
    makeEvPassGraphs(nameAr,evPassePtCanAr,ePtEvPassGraphAr,evPassePtGraphAr,ePtXAr,cutName)


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
    QCDSumHist = TH1D("ePtHistQCDSum","ePtHistQCDSum", binAmnt, ePtRange[0], ePtRange[1])
    for k in range(len(histePtAr)):

        if isQCDAr[k]:
            histePtAr[k].Sumw2()
            QCDSumHist.Sumw2()
            QCDSumHist.Add(histePtAr[k],weightsAr[k])
else:
    QCDSumHist = 0



FoMePtCan = TCanvas("c1ePt","c1ePt",3600,2400)
setUpLegend(legAr)
setUpPadsAr(padAr,"{0}Pad".format("ePt"))
padAr[-1][0].Draw()
padAr[-1][0].cd()

#Make top plot
#First set histogram elements (color, etc)
intePtAr = []

backgroundIntSum,QCDSumInt = setHistoElements(nameAr,colorAr,sumQCD,QCDSumHist,isQCDAr,histePtAr,isSignalAr,cutName,normalizeBackgroundsTogether,weightsAr,intePtAr)

if variableRebin:
    doVariableRebinning(histePtAr,isSignalAr,variableRebinVar,binAmnt,ePtRange,sumQCD,nameAr,QCDSumHist,cutName,weightsAr)

histMax = normalizeHists(histePtAr,sumQCD,isQCDAr,normalizeBackgroundsTogether,backgroundIntSum,isSignalAr,weightsAr,legAr,nameAr,intePtAr)


if sumQCD:
    if QCDSumInt:
        histMax = scaleQCDHist(QCDSumInt,QCDSumHist,histMax,legAr)


histePtStack = THStack("hist{0}Stack".format(cutName),"Events Passing All Cuts Vs {0} Cut Value".format(cutName))


maxInt = addHistsToStack(histePtAr,isSignalAr,sumQCD,isQCDAr,histePtStack,QCDSumHist,normalizeBackgroundsTogether,backgroundIntSum)

invHistsAr = []
drawInvAr = []

setUpInvHists(histePtAr,isSignalAr,sumQCD,isQCDAr,invHistsAr,nameAr,intePtAr,drawInvAr,QCDSumInt,QCDSumHist,cutName)

FoMePtGraph = TGraph(len(ePtGraphAr),ePtXAr,ePtGraphAr)



setUpStackedHistAndDrawFoMPlot(histMax,histePtAr,histePtStack,invHistsAr,drawInvAr,legAr,FoMePtCan,padAr,FoMePtGraph,ePtRange,normalizeBackgroundsTogether,cutName,signalName,backgroundName)

FoMePt2Can = TCanvas("c2ePt","c2ePt",3600,2400)

setUpNonStackedHistAndFoMPlot(FoMePt2Can,cutName,padAr,sumQCD,QCDSumHist,histMax,isSignalAr,isQCDAr,normalizeBackgroundsTogether,maxInt,histePtAr,legAr,FoMePtGraph,signalName,backgroundName)


eEtaGraphAr = array('d')
eEtaXAr = array('d')


FoMCalc(eEtaSignalAr,eEtaBackgroundAr,eEtaGraphAr,eEtaXAr,cutAmnt,eEtaRange,eEtaStep)

evPasseEtaCanAr = []
evPasseEtaGraphAr = []
print("Done.","time:",time.time()-startt)

#make evpass graphs

cutName = "eEta"

if not skipEvPassGraphs:
    makeEvPassGraphs(nameAr,evPasseEtaCanAr,eEtaEvPassGraphAr,evPasseEtaGraphAr,eEtaXAr,cutName)


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
    QCDSumHist = TH1D("eEtaHistQCDSum","eEtaHistQCDSum", binAmnt, eEtaRange[0], eEtaRange[1])
    for k in range(len(histeEtaAr)):

        if isQCDAr[k]:
            histeEtaAr[k].Sumw2()
            QCDSumHist.Sumw2()
            QCDSumHist.Add(histeEtaAr[k],weightsAr[k])
else:
    QCDSumHist = 0



FoMeEtaCan = TCanvas("c1eEta","c1eEta",3600,2400)
setUpLegend(legAr)
setUpPadsAr(padAr,"{0}Pad".format("eEta"))
padAr[-1][0].Draw()
padAr[-1][0].cd()

#Make top plot
#First set histogram elements (color, etc)
inteEtaAr = []

backgroundIntSum,QCDSumInt = setHistoElements(nameAr,colorAr,sumQCD,QCDSumHist,isQCDAr,histeEtaAr,isSignalAr,cutName,normalizeBackgroundsTogether,weightsAr,inteEtaAr)

if variableRebin:
    doVariableRebinning(histeEtaAr,isSignalAr,variableRebinVar,binAmnt,eEtaRange,sumQCD,nameAr,QCDSumHist,cutName,weightsAr)

histMax = normalizeHists(histeEtaAr,sumQCD,isQCDAr,normalizeBackgroundsTogether,backgroundIntSum,isSignalAr,weightsAr,legAr,nameAr,inteEtaAr)


if sumQCD:
    if QCDSumInt:
        histMax = scaleQCDHist(QCDSumInt,QCDSumHist,histMax,legAr)


histeEtaStack = THStack("hist{0}Stack".format(cutName),"Events Passing All Cuts Vs {0} Cut Value".format(cutName))


maxInt = addHistsToStack(histeEtaAr,isSignalAr,sumQCD,isQCDAr,histeEtaStack,QCDSumHist,normalizeBackgroundsTogether,backgroundIntSum)

invHistsAr = []
drawInvAr = []

setUpInvHists(histeEtaAr,isSignalAr,sumQCD,isQCDAr,invHistsAr,nameAr,inteEtaAr,drawInvAr,QCDSumInt,QCDSumHist,cutName)

FoMeEtaGraph = TGraph(len(eEtaGraphAr),eEtaXAr,eEtaGraphAr)



setUpStackedHistAndDrawFoMPlot(histMax,histeEtaAr,histeEtaStack,invHistsAr,drawInvAr,legAr,FoMeEtaCan,padAr,FoMeEtaGraph,eEtaRange,normalizeBackgroundsTogether,cutName,signalName,backgroundName)

FoMeEta2Can = TCanvas("c2eEta","c2eEta",3600,2400)

setUpNonStackedHistAndFoMPlot(FoMeEta2Can,cutName,padAr,sumQCD,QCDSumHist,histMax,isSignalAr,isQCDAr,normalizeBackgroundsTogether,maxInt,histeEtaAr,legAr,FoMeEtaGraph,signalName,backgroundName)


mPtGraphAr = array('d')
mPtXAr = array('d')


FoMCalc(mPtSignalAr,mPtBackgroundAr,mPtGraphAr,mPtXAr,cutAmnt,mPtRange,mPtStep)

evPassmPtCanAr = []
evPassmPtGraphAr = []
print("Done.","time:",time.time()-startt)

#make evpass graphs

cutName = "mPt"

if not skipEvPassGraphs:
    makeEvPassGraphs(nameAr,evPassmPtCanAr,mPtEvPassGraphAr,evPassmPtGraphAr,mPtXAr,cutName)


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
    QCDSumHist = TH1D("mPtHistQCDSum","mPtHistQCDSum", binAmnt, mPtRange[0], mPtRange[1])
    for k in range(len(histmPtAr)):

        if isQCDAr[k]:
            histmPtAr[k].Sumw2()
            QCDSumHist.Sumw2()
            QCDSumHist.Add(histmPtAr[k],weightsAr[k])
else:
    QCDSumHist = 0



FoMmPtCan = TCanvas("c1mPt","c1mPt",3600,2400)
setUpLegend(legAr)
setUpPadsAr(padAr,"{0}Pad".format("mPt"))
padAr[-1][0].Draw()
padAr[-1][0].cd()

#Make top plot
#First set histogram elements (color, etc)
intmPtAr = []

backgroundIntSum,QCDSumInt = setHistoElements(nameAr,colorAr,sumQCD,QCDSumHist,isQCDAr,histmPtAr,isSignalAr,cutName,normalizeBackgroundsTogether,weightsAr,intmPtAr)

if variableRebin:
    doVariableRebinning(histmPtAr,isSignalAr,variableRebinVar,binAmnt,mPtRange,sumQCD,nameAr,QCDSumHist,cutName,weightsAr)

histMax = normalizeHists(histmPtAr,sumQCD,isQCDAr,normalizeBackgroundsTogether,backgroundIntSum,isSignalAr,weightsAr,legAr,nameAr,intmPtAr)


if sumQCD:
    if QCDSumInt:
        histMax = scaleQCDHist(QCDSumInt,QCDSumHist,histMax,legAr)


histmPtStack = THStack("hist{0}Stack".format(cutName),"Events Passing All Cuts Vs {0} Cut Value".format(cutName))


maxInt = addHistsToStack(histmPtAr,isSignalAr,sumQCD,isQCDAr,histmPtStack,QCDSumHist,normalizeBackgroundsTogether,backgroundIntSum)

invHistsAr = []
drawInvAr = []

setUpInvHists(histmPtAr,isSignalAr,sumQCD,isQCDAr,invHistsAr,nameAr,intmPtAr,drawInvAr,QCDSumInt,QCDSumHist,cutName)

FoMmPtGraph = TGraph(len(mPtGraphAr),mPtXAr,mPtGraphAr)



setUpStackedHistAndDrawFoMPlot(histMax,histmPtAr,histmPtStack,invHistsAr,drawInvAr,legAr,FoMmPtCan,padAr,FoMmPtGraph,mPtRange,normalizeBackgroundsTogether,cutName,signalName,backgroundName)

FoMmPt2Can = TCanvas("c2mPt","c2mPt",3600,2400)

setUpNonStackedHistAndFoMPlot(FoMmPt2Can,cutName,padAr,sumQCD,QCDSumHist,histMax,isSignalAr,isQCDAr,normalizeBackgroundsTogether,maxInt,histmPtAr,legAr,FoMmPtGraph,signalName,backgroundName)


mEtaGraphAr = array('d')
mEtaXAr = array('d')


FoMCalc(mEtaSignalAr,mEtaBackgroundAr,mEtaGraphAr,mEtaXAr,cutAmnt,mEtaRange,mEtaStep)

evPassmEtaCanAr = []
evPassmEtaGraphAr = []
print("Done.","time:",time.time()-startt)

#make evpass graphs

cutName = "mEta"

if not skipEvPassGraphs:
    makeEvPassGraphs(nameAr,evPassmEtaCanAr,mEtaEvPassGraphAr,evPassmEtaGraphAr,mEtaXAr,cutName)


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
    QCDSumHist = TH1D("mEtaHistQCDSum","mEtaHistQCDSum", binAmnt, mEtaRange[0], mEtaRange[1])
    for k in range(len(histmEtaAr)):

        if isQCDAr[k]:
            histmEtaAr[k].Sumw2()
            QCDSumHist.Sumw2()
            QCDSumHist.Add(histmEtaAr[k],weightsAr[k])
else:
    QCDSumHist = 0



FoMmEtaCan = TCanvas("c1mEta","c1mEta",3600,2400)
setUpLegend(legAr)
setUpPadsAr(padAr,"{0}Pad".format("mEta"))
padAr[-1][0].Draw()
padAr[-1][0].cd()

#Make top plot
#First set histogram elements (color, etc)
intmEtaAr = []

backgroundIntSum,QCDSumInt = setHistoElements(nameAr,colorAr,sumQCD,QCDSumHist,isQCDAr,histmEtaAr,isSignalAr,cutName,normalizeBackgroundsTogether,weightsAr,intmEtaAr)

if variableRebin:
    doVariableRebinning(histmEtaAr,isSignalAr,variableRebinVar,binAmnt,mEtaRange,sumQCD,nameAr,QCDSumHist,cutName,weightsAr)

histMax = normalizeHists(histmEtaAr,sumQCD,isQCDAr,normalizeBackgroundsTogether,backgroundIntSum,isSignalAr,weightsAr,legAr,nameAr,intmEtaAr)


if sumQCD:
    if QCDSumInt:
        histMax = scaleQCDHist(QCDSumInt,QCDSumHist,histMax,legAr)


histmEtaStack = THStack("hist{0}Stack".format(cutName),"Events Passing All Cuts Vs {0} Cut Value".format(cutName))


maxInt = addHistsToStack(histmEtaAr,isSignalAr,sumQCD,isQCDAr,histmEtaStack,QCDSumHist,normalizeBackgroundsTogether,backgroundIntSum)

invHistsAr = []
drawInvAr = []

setUpInvHists(histmEtaAr,isSignalAr,sumQCD,isQCDAr,invHistsAr,nameAr,intmEtaAr,drawInvAr,QCDSumInt,QCDSumHist,cutName)

FoMmEtaGraph = TGraph(len(mEtaGraphAr),mEtaXAr,mEtaGraphAr)



setUpStackedHistAndDrawFoMPlot(histMax,histmEtaAr,histmEtaStack,invHistsAr,drawInvAr,legAr,FoMmEtaCan,padAr,FoMmEtaGraph,mEtaRange,normalizeBackgroundsTogether,cutName,signalName,backgroundName)

FoMmEta2Can = TCanvas("c2mEta","c2mEta",3600,2400)

setUpNonStackedHistAndFoMPlot(FoMmEta2Can,cutName,padAr,sumQCD,QCDSumHist,histMax,isSignalAr,isQCDAr,normalizeBackgroundsTogether,maxInt,histmEtaAr,legAr,FoMmEtaGraph,signalName,backgroundName)


