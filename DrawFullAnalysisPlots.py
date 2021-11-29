import datetime
from ROOT import TFile, TChain, gDirectory, TApplication, TMath, Math, TMinuit, TROOT, TSystem, TTree, TVector2, THStack
# You probably also want to import TH1D and TCanvas,
# unless you're not making any histograms.
from ROOT import TH1F, TH1D, TF1, TGraph, TGraphErrors, TLegend, TLine, TPaveText, TStyle
from ROOT import TH2D, TH2F
from FunctionsForFullAnalysisPlots import *

today = datetime.datetime.today()

datasetSaveNameAr = []
fileAr = []
XSAr = []
totalEvents = []
fileAr = []
nameAr = []
isSignalAr = []
colorAr = []
useLHEAr = []


if testRun:
    fileAr.append(TFile.Open("{0}FullAnalysistestRun.root".format(forCondorStr)))
    colorAr.append(1)
    datasetSaveNameAr.append("testRun")
    isQCDAr.append(False)
    testRunXSTree = fileAr[-1].crossSectionTree
    tmpXSAvg = 0
    tmpXSCnt = 0
    isSignalAr.append(False)
    for testRunXS in testRunXSTree:
        tmpXSAvg += testRunXS.crossSectionVar
        tmpXSCnt += 1
    tmpXSAvg = tmpXSAvg / tmpXSCnt
    XSAr.append(tmpXSAvg)
    ENTree = fileAr[-1].evNumTree
    evNum = 0
    for ev in ENTree:
        evNum = ev.nEv
    totalEvents.append(evNum)
if MGSM:
    fileAr.append(TFile.Open("{0}FullAnalysisSM.root".format(forCondorStr)))
    colorAr.append(2)
    datasetSaveNameAr.append("SM")
    isQCDAr.append(False)
    isSignalAr.append(False)
    useLHEAr.append(True)

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
    signalPos = 1
else:
    signalPos = 0
if MGEFT:
    fileAr.append(TFile.Open("{0}FullAnalysisEFT.root".format(forCondorStr)))
    colorAr.append(6)
    datasetSaveNameAr.append("EFT")
    isQCDAr.append(False)
    isSignalAr.append(True)
    useLHEAr.append(True)

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
if ttHToBBBackground:
    fileAr.append(TFile.Open("{0}FullAnalysisttHToBB.root".format(forCondorStr)))
    colorAr.append(7)
    datasetSaveNameAr.append("ttHToBB")
    XSAr.append(0.5071*0.582)
    isQCDAr.append(False)
    isSignalAr.append(False)
    useLHEAr.append(False)
    ENTree = fileAr[-1].evNumTree
    evNum = 0
    for ev in ENTree:
        evNum = ev.nEv
    totalEvents.append(evNum)
if ttZJetsBackground:
    fileAr.append(TFile.Open("{0}FullAnalysisttZJets.root".format(forCondorStr)))
    colorAr.append(4)
    datasetSaveNameAr.append("ttZJets")
    XSAr.append(0.5407)
    isQCDAr.append(False)
    isSignalAr.append(False)
    useLHEAr.append(False)
    ENTree = fileAr[-1].evNumTree
    evNum = 0
    for ev in ENTree:
        evNum = ev.nEv
    totalEvents.append(evNum)
if DYBackground:
    fileAr.append(TFile.Open("{0}FullAnalysisDY.root".format(forCondorStr)))
    colorAr.append(8)
    datasetSaveNameAr.append("DY")
    XSAr.append(5364)
    isQCDAr.append(False)
    isSignalAr.append(False)
    useLHEAr.append(False)
    ENTree = fileAr[-1].evNumTree
    evNum = 0
    for ev in ENTree:
        evNum = ev.nEv
    totalEvents.append(evNum)
if QCDPT170to300Background:
    fileAr.append(TFile.Open("{0}FullAnalysisQCDPT170to300.root".format(forCondorStr)))
    nameAr.append("QCDPT170to300Background")
    datasetSaveNameAr.append("QCD0")
    isSignalAr.append(False)
    useLHEAr.append(False)
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
    fileAr.append(TFile.Open("{0}FullAnalysisQCDPT300to470.root".format(forCondorStr)))
    nameAr.append("QCDPT300to470Background")
    datasetSaveNameAr.append("QCD1")
    isSignalAr.append(False)
    useLHEAr.append(False)
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
    fileAr.append(TFile.Open("{0}FullAnalysisQCDPT470to600.root".format(forCondorStr)))
    nameAr.append("QCDPT470to600Background")
    datasetSaveNameAr.append("QCD2")
    colorAr.append(9)
    isSignalAr.append(False)
    useLHEAr.append(False)
    tmpXSAvg = 552.6
    XSAr.append(tmpXSAvg)
    ENTree = fileAr[-1].evNumTree
    evNum = 0
    for ev in ENTree:
        evNum = ev.nEv
    totalEvents.append(evNum)
    isQCDAr.append(True)
if QCDPT600to800Background:
    fileAr.append(TFile.Open("{0}FullAnalysisQCDPT600to800.root".format(forCondorStr)))
    nameAr.append("QCDPT600to800Background")
    datasetSaveNameAr.append("QCD3")
    colorAr.append(10)
    isSignalAr.append(False)
    useLHEAr.append(False)
    tmpXSAvg = 156.6
    XSAr.append(tmpXSAvg)
    ENTree = fileAr[-1].evNumTree
    evNum = 0
    for ev in ENTree:
        evNum = ev.nEv
    totalEvents.append(evNum)
    isQCDAr.append(True)
if QCDPT800to1000Background:
    fileAr.append(TFile.Open("{0}FullAnalysisQCDPT800to1000.root".format(forCondorStr)))
    nameAr.append("QCDPT800to1000Background")
    datasetSaveNameAr.append("QCD4")
    colorAr.append(11)
    isSignalAr.append(False)
    useLHEAr.append(False)
    tmpXSAvg = 26.32
    XSAr.append(tmpXSAvg)
    ENTree = fileAr[-1].evNumTree
    evNum = 0
    for ev in ENTree:
        evNum = ev.nEv
    totalEvents.append(evNum)
    isQCDAr.append(True)
if QCDPT1000to1400Background:
    fileAr.append(TFile.Open("{0}FullAnalysisQCDPT1000to1400.root".format(forCondorStr)))
    nameAr.append("QCDPT1000to1400Background")
    datasetSaveNameAr.append("QCD5")
    colorAr.append(12)
    isSignalAr.append(False)
    useLHEAr.append(False)
    tmpXSAvg = 7.5
    XSAr.append(tmpXSAvg)
    ENTree = fileAr[-1].evNumTree
    evNum = 0
    for ev in ENTree:
        evNum = ev.nEv
    totalEvents.append(evNum)
    isQCDAr.append(True)
if QCDPT1400to1800Background:
    fileAr.append(TFile.Open("{0}FullAnalysisQCDPT1400to1800.root".format(forCondorStr)))
    nameAr.append("QCDPT1400to1800Background")
    datasetSaveNameAr.append("QCD6")
    isSignalAr.append(False)
    useLHEAr.append(False)
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
    fileAr.append(TFile.Open("{0}FullAnalysisQCDPT1800to2400.root".format(forCondorStr)))
    nameAr.append("QCDPT1800to2400Background")
    datasetSaveNameAr.append("QCD7")
    isSignalAr.append(False)
    useLHEAr.append(False)
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
    fileAr.append(TFile.Open("{0}FullAnalysisQCDPT2400to3200.root".format(forCondorStr)))
    nameAr.append("QCDPT2400to3200Background")
    datasetSaveNameAr.append("QCD8")
    isSignalAr.append(False)
    useLHEAr.append(False)
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
    fileAr.append(TFile.Open("{0}FullAnalysisQCDPT3200toInf.root".format(forCondorStr)))
    nameAr.append("QCDPT3200toInfBackground")
    datasetSaveNameAr.append("QCD9")
    isSignalAr.append(False)
    useLHEAr.append(False)
    colorAr.append(16)
    tmpXSAvg = 0.0001349
    XSAr.append(tmpXSAvg)
    ENTree = fileAr[-1].evNumTree
    evNum = 0
    for ev in ENTree:
        evNum = ev.nEv
    totalEvents.append(evNum)
    isQCDAr.append(True)


print("totalEvents:",totalEvents)
print("XSAr:",XSAr)
weightsAr = [tmpXS/tmpEvs for tmpXS,tmpEvs in zip(XSAr,totalEvents)]
print("weightsAr:",weightsAr)


##################MAIN LOOP##################
for k,fileA in enumerate(fileAr):
    if not onlyLHETree:
        evCtr = 0
        
        print("Entering file {0}".format(k))
        FATree = fileA.FATree
        histAr.append([])
        canAr.append([])
        
        #Initialize all FA hists
        print("Initializing FA hists")
        for FAItr, FASaveName in enumerate(FASaveNameAr):
            if onlyDoSomeHists and FAItr >= histsToDo:
                break
            canAr[-1].append(TCanvas("{0}Can{1}".format(FASaveName,datasetSaveNameAr[k]),"{0}Can{1}".format(FASaveName,datasetSaveNameAr[k]),3600,2400))
            histAr[-1].append(TH1D("{0}Hist{1}".format(FASaveName,datasetSaveNameAr[k]),"{0}Hist{1}".format(FASaveName,datasetSaveNameAr[k]), FABinsAndRangeAr[FAItr][0], FABinsAndRangeAr[FAItr][1], FABinsAndRangeAr[FAItr][2]))
        print("Looping over events")
        #LOOP OVER EVENTS IN FILE k
        for j,ev in enumerate(FATree):
            if breakEvEarly and evCtr >= breakEvAt:
                break
            if evCtr % 1000 == 0:
                print("ev:",evCtr)
            
            valAr = [ev.nJetL,ev.jetLeadPtL,ev.jetTrailingPtL,ev.jetLeadPhiL,ev.jetTrailingPhiL,ev.jetPairInvMassL,ev.jetLeadEtaL,ev.jetTrailingEtaL,
            ev.nFatJetL,ev.hFatJet_pt_fromPtL,ev.hFatJet_phi_fromPtL,ev.hFatJet_eta_fromPtL,ev.hFatJet_mass_fromPtL,ev.hFatJet_HTag_fromPtL,
            ev.hFatJet_pt_fromHTagL,ev.hFatJet_phi_fromHTagL,ev.hFatJet_eta_fromHTagL,ev.hFatJet_mass_fromHTagL,ev.hFatJet_HTag_fromHTagL,
            ev.nGenPartL,ev.hGenPartDR_fromPtL,ev.hGenPartInd_fromPtL,ev.hGenPartpdgId_fromPtL,ev.hGenPartFirstMompdgId_fromPtL,
            ev.hGenPartDR_fromHTagL,ev.hGenPartInd_fromHTagL,ev.hGenPartpdgId_fromHTagL,ev.hGenPartFirstMompdgId_fromHTagL,
            
            ev.hbbTagL,ev.doubleElecHLTL,ev.doubleMuonHLTL,ev.muonEGHLTL,ev.elecHLTL,ev.muonHLTL,ev.hadHLTL,
            ev.isLeptonicL,ev.isSemiLeptonicL,ev.isHadronicL,
            ev.passedLepL,ev.passedSemiLepL,ev.passedHadL]

            for valItr,valA in enumerate(valAr):
                if onlyDoSomeHists and valItr >= histsToDo:
                    break
                #if evCtr <20 and evCtr > 10 and valItr == 0:
                #    print(valA)
                histAr[k][valItr].Fill(valA)
            evCtr += 1
        evCtr = 0

        LepTree = fileA.LepTree
        histLepAr.append([])
        canLepAr.append([])
        
        #Initialize all Lep hists
        print("Initializing Lep hists")
        for LepItr, LepSaveName in enumerate(LepSaveNameAr):
            if onlyDoSomeHists and LepItr >= histsToDo:
                break
            canLepAr[-1].append(TCanvas("{0}CanLep{1}".format(LepSaveName,datasetSaveNameAr[k]),"{0}CanLep{1}".format(LepSaveName,datasetSaveNameAr[k]),3600,2400))
            histLepAr[-1].append(TH1D("{0}HistLep{1}".format(LepSaveName,datasetSaveNameAr[k]),"{0}HistLep{1}".format(LepSaveName,datasetSaveNameAr[k]), LepBinsAndRangeAr[LepItr][0], LepBinsAndRangeAr[LepItr][1], LepBinsAndRangeAr[LepItr][2]))
        print("Looping over events")
        #LOOP OVER EVENTS IN FILE k
        for j,ev in enumerate(LepTree):
            if breakEvEarly and evCtr >= breakEvAt:
                break
            if evCtr % 1000 == 0:
                print("ev:",evCtr)
            
            valAr = [ev.lepZ1LeadPtL,ev.lepZ1TrailingPtL,ev.lepZ1LeadPhiL,ev.lepZ1TrailingPhiL,ev.lepZ1PairInvMassL,ev.lepZ1LeadEtaL,ev.lepZ1TrailingEtaL,
            ev.lepZ1IsElectronL,ev.lepZ1IsMuonL,
            ev.lepZ1LeadIsoL,ev.lepZ1TrailingIsoL,ev.lepZ1LeadSIPL,ev.lepZ1TrailingSIPL,
            ev.lepZ2LeadPtL,ev.lepZ2TrailingPtL,ev.lepZ2LeadPhiL,ev.lepZ2TrailingPhiL,ev.lepZ2PairInvMassL,ev.lepZ2LeadEtaL,ev.lepZ2TrailingEtaL,
            ev.lepZ2IsElectronL,ev.lepZ2IsMuonL,
            ev.lepZ2LeadIsoL,ev.lepZ2TrailingIsoL,ev.lepZ2LeadSIPL,ev.lepZ2TrailingSIPL]

            for valItr,valA in enumerate(valAr):
                if onlyDoSomeHists and valItr >= histsToDo:
                    break
                #if evCtr <20 and evCtr > 10 and valItr == 0:
                #    print(valA)
                histLepAr[k][valItr].Fill(valA)
            evCtr += 1
        
        evCtr = 0

        SemiLepTree = fileA.SemiLepTree
        histSemiLepAr.append([])
        canSemiLepAr.append([])
        
        #Initialize all SemiLep hists
        print("Initializing SemiLep hists")
        for SemiLepItr, SemiLepSaveName in enumerate(SemiLepSaveNameAr):
            if onlyDoSomeHists and SemiLepItr >= histsToDo:
                break
            canSemiLepAr[-1].append(TCanvas("{0}CanSemiLep{1}".format(SemiLepSaveName,datasetSaveNameAr[k]),"{0}CanSemiLep{1}".format(SemiLepSaveName,datasetSaveNameAr[k]),3600,2400))
            histSemiLepAr[-1].append(TH1D("{0}HistSemiLep{1}".format(SemiLepSaveName,datasetSaveNameAr[k]),"{0}HistSemiLep{1}".format(SemiLepSaveName,datasetSaveNameAr[k]), SemiLepBinsAndRangeAr[SemiLepItr][0], SemiLepBinsAndRangeAr[SemiLepItr][1], SemiLepBinsAndRangeAr[SemiLepItr][2]))
        print("Looping over events")
        #LOOP OVER EVENTS IN FILE k
        for j,ev in enumerate(SemiLepTree):
            if breakEvEarly and evCtr >= breakEvAt:
                break
            if evCtr % 1000 == 0:
                print("ev:",evCtr)
            
            valAr = [ev.lepLeadPtL,ev.lepTrailingPtL,ev.lepLeadPhiL,ev.lepTrailingPhiL,ev.lepPairInvMassL,ev.lepLeadEtaL,ev.lepTrailingEtaL,
            ev.lepIsElectronL,ev.lepIsMuonL,
            ev.lepLeadIsoL,ev.lepTrailingIsoL,ev.lepLeadSIPL,ev.lepTrailingSIPL,
            ev.FJPtL,ev.FJPhiL,ev.FJMassL,ev.FJEtaL]

            for valItr,valA in enumerate(valAr):
                if onlyDoSomeHists and valItr >= histsToDo:
                    break
                #if evCtr <20 and evCtr > 10 and valItr == 0:
                #    print(valA)
                histSemiLepAr[k][valItr].Fill(valA)
            evCtr += 1

        
        evCtr = 0

        HadTree = fileA.HadTree
        histHadAr.append([])
        canHadAr.append([])
        
        #Initialize all Had hists
        print("Initializing Had hists")
        for HadItr, HadSaveName in enumerate(HadSaveNameAr):
            if onlyDoSomeHists and HadItr >= histsToDo:
                break
            canHadAr[-1].append(TCanvas("{0}CanHad{1}".format(HadSaveName,datasetSaveNameAr[k]),"{0}CanHad{1}".format(HadSaveName,datasetSaveNameAr[k]),3600,2400))
            histHadAr[-1].append(TH1D("{0}HistHad{1}".format(HadSaveName,datasetSaveNameAr[k]),"{0}HistHad{1}".format(HadSaveName,datasetSaveNameAr[k]), HadBinsAndRangeAr[HadItr][0], HadBinsAndRangeAr[HadItr][1], HadBinsAndRangeAr[HadItr][2]))
        print("Looping over events")
        #LOOP OVER EVENTS IN FILE k
        for j,ev in enumerate(HadTree):
            if breakEvEarly and evCtr >= breakEvAt:
                break
            if evCtr % 1000 == 0:
                print("ev:",evCtr)
            
            valAr = [ev.FJLeadPtL,ev.FJTrailingPtL,
            ev.FJLeadPhiL,ev.FJTrailingPhiL,
            ev.FJLeadMassL,ev.FJTrailingMassL,
            ev.FJPairInvMassL,
            ev.FJLeadEtaL,ev.FJTrailingEtaL,
            ev.FJEtaSepL]

            for valItr,valA in enumerate(valAr):
                if onlyDoSomeHists and valItr >= histsToDo:
                    break
                #if evCtr <20 and evCtr > 10 and valItr == 0:
                #    print(valA)
                histHadAr[k][valItr].Fill(valA)
            evCtr += 1

    if useLHEAr[k]:
        evCtr = 0

        RawTree = fileA.RawTree
        histRawAr.append([])
        canRawAr.append([])
        
        #Initialize all Raw hists
        print("Initializing Raw hists")
        for RawItr, RawSaveName in enumerate(RawSaveNameAr):
            if onlyDoSomeHists and RawItr >= histsToDo:
                break
            canRawAr[-1].append(TCanvas("{0}CanRaw{1}".format(RawSaveName,datasetSaveNameAr[k]),"{0}CanRaw{1}".format(RawSaveName,datasetSaveNameAr[k]),3600,2400))
            histRawAr[-1].append(TH1D("{0}HistRaw{1}".format(RawSaveName,datasetSaveNameAr[k]),"{0}HistRaw{1}".format(RawSaveName,datasetSaveNameAr[k]), RawBinsAndRangeAr[RawItr][0], RawBinsAndRangeAr[RawItr][1], RawBinsAndRangeAr[RawItr][2]))
        print("Looping over events")
        #LOOP OVER EVENTS IN FILE k
        for j,ev in enumerate(RawTree):
            if breakEvEarly and evCtr >= breakEvAt:
                break
            if evCtr % 1000 == 0:
                print("ev:",evCtr)
            
            valAr = [ev.ZOne_pt_FromLHERawL,ev.ZOne_eta_FromLHERawL,ev.ZTwo_pt_FromLHERawL,ev.ZTwo_eta_FromLHERawL,
            ev.H_pt_FromLHERawL,ev.H_eta_FromLHERawL,
            ev.JOne_pt_FromLHERawL,ev.JOne_eta_FromLHERawL,ev.tmpJOnePhi_FromLHERawL,ev.JOne_invmass_FromLHERawL,
            ev.JTwo_pt_FromLHERawL,ev.JTwo_eta_FromLHERawL,ev.tmpJTwoPhi_FromLHERawL,ev.JTwo_invmass_FromLHERawL,
            ev.JPair_invmass_FromLHERawL,ev.J_etasep_FromLHERawL]

            for valItr,valA in enumerate(valAr):
                if onlyDoSomeHists and valItr >= histsToDo:
                    break
                #if evCtr <20 and evCtr > 10 and valItr == 0:
                #    print(valA)
                histRawAr[k][valItr].Fill(valA)
            evCtr += 1


        
        evCtr = 0

        SelectedTree = fileA.SelectedTree
        histSelectedAr.append([])
        canSelectedAr.append([])
        
        #Initialize all Selected hists
        print("Initializing Selected hists")
        for SelectedItr, SelectedSaveName in enumerate(SelectedSaveNameAr):
            if onlyDoSomeHists and SelectedItr >= histsToDo:
                break
            canSelectedAr[-1].append(TCanvas("{0}CanSelected{1}".format(SelectedSaveName,datasetSaveNameAr[k]),"{0}CanSelected{1}".format(SelectedSaveName,datasetSaveNameAr[k]),3600,2400))
            histSelectedAr[-1].append(TH1D("{0}HistSelected{1}".format(SelectedSaveName,datasetSaveNameAr[k]),"{0}HistSelected{1}".format(SelectedSaveName,datasetSaveNameAr[k]), SelectedBinsAndRangeAr[SelectedItr][0], SelectedBinsAndRangeAr[SelectedItr][1], SelectedBinsAndRangeAr[SelectedItr][2]))
        print("Looping over events")
        #LOOP OVER EVENTS IN FILE k
        for j,ev in enumerate(SelectedTree):
            if breakEvEarly and evCtr >= breakEvAt:
                break
            if evCtr % 1000 == 0:
                print("ev:",evCtr)
            
            valAr = [ev.ZOne_pt_FromLHESelectedL,ev.ZOne_eta_FromLHESelectedL,ev.ZTwo_pt_FromLHESelectedL,ev.ZTwo_eta_FromLHESelectedL,
            ev.H_pt_FromLHESelectedL,ev.H_eta_FromLHESelectedL,
            ev.JOne_pt_FromLHESelectedL,ev.JOne_eta_FromLHESelectedL,ev.tmpJOnePhi_FromLHESelectedL,ev.JOne_invmass_FromLHESelectedL,
            ev.JTwo_pt_FromLHESelectedL,ev.JTwo_eta_FromLHESelectedL,ev.tmpJTwoPhi_FromLHESelectedL,ev.JTwo_invmass_FromLHESelectedL,
            ev.JPair_invmass_FromLHESelectedL,ev.J_etasep_FromLHESelectedL]

            for valItr,valA in enumerate(valAr):
                if onlyDoSomeHists and valItr >= histsToDo:
                    break
                #if evCtr <20 and evCtr > 10 and valItr == 0:
                #    print(valA)
                histSelectedAr[k][valItr].Fill(valA)
            evCtr += 1

    

    
##################END MAIN LOOP##################
print("Finished main loop")


if not onlyLHETree:

    ###############STARTING FA GRAPHS###############
    padAr = []
    legAr = []

    signalName = ""
    backgroundName = ""
    for k,fileA in enumerate(fileAr):
        if not sumQCD or not isQCDAr[k]:
            if isSignalAr[k]:
                signalName += "_"+datasetSaveNameAr[k]
            else:
                backgroundName += "_"+datasetSaveNameAr[k]

    sumQCDCanAr = []
    #print(len(weightsAr),len(histAr),len(histAr[0]),len(FASaveNameAr),len(QCDSumHistAr))
    if sumQCD:
        backgroundName += "_QCDSum"
        for FAItr, FASaveName in enumerate(FASaveNameAr):
            if onlyDoSomeHists and FAItr >= histsToDo:
                break
            sumQCDCanAr.append(TCanvas("{0}CanQCDSum".format(FASaveName),"{0}CanQCDSum".format(FASaveName),3600,2400))
            QCDSumHistAr.append(TH1D("{0}HistQCDSum".format(FASaveName),"{0}HistQCDSum".format(FASaveName), FABinsAndRangeAr[FAItr][0], FABinsAndRangeAr[FAItr][1], FABinsAndRangeAr[FAItr][2]))
        for k in range(len(histAr)):
            if isQCDAr[k]:
                for FAItr, FASaveName in enumerate(FASaveNameAr):
                    if onlyDoSomeHists and FAItr >= histsToDo:
                        break
                    #print(k,FAItr)
                    histAr[k][FAItr].Sumw2()
                    QCDSumHistAr[FAItr].Sumw2()
                    QCDSumHistAr[FAItr].Add(histAr[k][FAItr],weightsAr[k])
                    

    for k,fileA in enumerate(fileAr):
        if not sumQCD or not isQCDAr[k]:
            for FAItr, FASaveName in enumerate(FASaveNameAr):
                if onlyDoSomeHists and FAItr >= histsToDo:
                    break
                canAr[k][FAItr].cd()
                histAr[k][FAItr].Draw("hist")
                if savePathBool:
                    canAr[k][FAItr].SaveAs("./Graphs/General/{0}/{1}{2}.png".format(datasetSaveNameAr[k],FASaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
                else:
                    canAr[k][FAItr].SaveAs("{0}{1}{2}.png".format(datasetSaveNameAr[k],FASaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))


    if sumQCD:
        for FAItr, FASaveName in enumerate(FASaveNameAr):
            if onlyDoSomeHists and FAItr >= histsToDo:
                break
            sumQCDCanAr[FAItr].cd()
            QCDSumHistAr[FAItr].Draw("hist")
            if savePathBool:
                sumQCDCanAr[FAItr].SaveAs("./Graphs/General/QCDSum/{0}{1}.png".format(FASaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
            else:
                sumQCDCanAr[FAItr].SaveAs("QCDSum{0}{1}.png".format(FASaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))

    for FAItr, FASaveName in enumerate(FASaveNameAr):
        if onlyDoSomeHists and FAItr >= histsToDo:
            break
        setUpLegend(legAr)
        setUpPadsAr(padAr,"{0}Pad".format("FASaveName"))
        #padAr[-1][0].Draw()
        #padAr[-1][0].cd()

    intComparisonAr = []



    backgroundIntSumAr,QCDSumIntAr = setHistoElements(colorAr,sumQCD,QCDSumHistAr,isQCDAr,histAr,isSignalAr,normalizeBackgroundsTogether,weightsAr,intComparisonAr,FASaveNameAr,onlyDoSomeHists,histsToDo,signalPos)


    histMaxAr = normalizeHists(histAr,sumQCD,isQCDAr,normalizeBackgroundsTogether,backgroundIntSumAr,isSignalAr,weightsAr,legAr,datasetSaveNameAr,intComparisonAr,FASaveNameAr,onlyDoSomeHists,histsToDo)



    if sumQCD:
        histMaxAr = scaleQCDHist(QCDSumIntAr,QCDSumHistAr,histMaxAr,legAr,onlyDoSomeHists,histsToDo,normalizeBackgroundsTogether,backgroundIntSumAr)



    comparisonCanAr = []
    comparisonHistStackAr = []
    for FAItr, FASaveName in enumerate(FASaveNameAr):
        if onlyDoSomeHists and FAItr >= histsToDo:
            break
        comparisonCanAr.append(TCanvas("comparisonCan{0}".format(FASaveName),"comparisonCan{0}".format(FASaveName),3600,2400))
        comparisonHistStackAr.append(THStack("hist{0}Stack".format(FASaveName),FATitleAr[FAItr]))


    maxIntAr = addHistsToStack(fileAr,histAr,isSignalAr,sumQCD,isQCDAr,comparisonHistStackAr,QCDSumHistAr,normalizeBackgroundsTogether,backgroundIntSumAr,FASaveNameAr,signalPos,onlyDoSomeHists,histsToDo)

    #Loop over all hists that went into the THStack to get center and length of error bars for invisible hist

    invHistsAr = []
    drawInvAr = []
    cloneHistAr = []

    setUpInvHists(histAr,cloneHistAr,isSignalAr,sumQCD,isQCDAr,invHistsAr,FASaveNameAr,intComparisonAr,drawInvAr,QCDSumIntAr,QCDSumHistAr,FASaveNameAr,onlyDoSomeHists,histsToDo)


    setUpStackedHistAndDrawFoMPlot(histMaxAr,histAr,cloneHistAr,comparisonHistStackAr,invHistsAr,drawInvAr,legAr,comparisonCanAr,padAr,normalizeBackgroundsTogether,signalName,backgroundName,FASaveNameAr,FAXTitleAr,signalPos,onlyDoSomeHists,histsToDo)

    comparisonUnstackedCanAr = []
    legUnstackedAr = []
    padUnstackedAr = []
    for FAItr, FASaveName in enumerate(FASaveNameAr):
        if onlyDoSomeHists and FAItr >= histsToDo:
            break
        comparisonUnstackedCanAr.append(TCanvas("comparisonUnstackedCan{0}".format(FASaveName),"comparisonUnstackedCan{0}".format(FASaveName),3600,2400))
        setUpLegend(legUnstackedAr)
        setUpPadsAr(padUnstackedAr,"{0}Pad".format("FAUnstackedSaveName"))

    setUpNonStackedHistAndFoMPlot(comparisonUnstackedCanAr,cloneHistAr,padAr,sumQCD,QCDSumHistAr,histMaxAr,isSignalAr,isQCDAr,normalizeBackgroundsTogether,maxIntAr,histAr,legAr,signalName,backgroundName,FASaveNameAr,FATitleAr,FAXTitleAr,signalPos,onlyDoSomeHists,histsToDo)



    ###############STARTING LEP GRAPHS###############
    padAr = []
    legAr = []

    """
    signalName = ""
    backgroundName = ""
    for k,fileA in enumerate(fileAr):
        if not sumQCD or not isQCDAr[k]:
            if isSignalAr[k]:
                signalName += "_"+datasetSaveNameAr[k]
            else:
                backgroundName += "_"+datasetSaveNameAr[k]

    """

    sumQCDCanAr = []
    #print(len(weightsAr),len(histLepAr),len(histLepAr[0]),len(LepSaveNameAr),len(QCDSumHistLepAr))
    if sumQCD:
        backgroundName += "_QCDSum"
        for LepItr, LepSaveName in enumerate(LepSaveNameAr):
            if onlyDoSomeHists and LepItr >= histsToDo:
                break
            sumQCDCanAr.append(TCanvas("{0}CanLepQCDSum".format(LepSaveName),"{0}CanLepQCDSum".format(LepSaveName),3600,2400))
            QCDSumHistLepAr.append(TH1D("{0}HistLepQCDSum".format(LepSaveName),"{0}HistLepQCDSum".format(LepSaveName), LepBinsAndRangeAr[LepItr][0], LepBinsAndRangeAr[LepItr][1], LepBinsAndRangeAr[LepItr][2]))
        for k in range(len(histLepAr)):
            if isQCDAr[k]:
                for LepItr, LepSaveName in enumerate(LepSaveNameAr):
                    if onlyDoSomeHists and LepItr >= histsToDo:
                        break
                    #print(k,LepItr)
                    histLepAr[k][LepItr].Sumw2()
                    QCDSumHistLepAr[LepItr].Sumw2()
                    QCDSumHistLepAr[LepItr].Add(histLepAr[k][LepItr],weightsAr[k])


    for k,fileA in enumerate(fileAr):
        if not sumQCD or not isQCDAr[k]:
            for LepItr, LepSaveName in enumerate(LepSaveNameAr):
                if onlyDoSomeHists and LepItr >= histsToDo:
                    break
                canLepAr[k][LepItr].cd()
                histLepAr[k][LepItr].Draw("hist")
                if savePathBool:
                    canLepAr[k][LepItr].SaveAs("./Graphs/General/{0}/{1}{2}.png".format(datasetSaveNameAr[k],LepSaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
                else:
                    canLepAr[k][LepItr].SaveAs("{0}{1}{2}.png".format(datasetSaveNameAr[k],LepSaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))


    if sumQCD:
        for LepItr, LepSaveName in enumerate(LepSaveNameAr):
            if onlyDoSomeHists and LepItr >= histsToDo:
                break
            sumQCDCanAr[LepItr].cd()
            QCDSumHistLepAr[LepItr].Draw("hist")
            if savePathBool:
                sumQCDCanAr[LepItr].SaveAs("./Graphs/General/QCDSum/{0}{1}.png".format(LepSaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
            else:
                sumQCDCanAr[LepItr].SaveAs("QCDSum{0}{1}.png".format(LepSaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))

    for LepItr, LepSaveName in enumerate(LepSaveNameAr):
        if onlyDoSomeHists and LepItr >= histsToDo:
            break
        setUpLegend(legAr)
        setUpPadsAr(padAr,"{0}Pad".format("LepSaveName"))
        #padAr[-1][0].Draw()
        #padAr[-1][0].cd()

    intComparisonAr = []



    backgroundIntSumAr,QCDSumIntAr = setHistoElements(colorAr,sumQCD,QCDSumHistLepAr,isQCDAr,histLepAr,isSignalAr,normalizeBackgroundsTogether,weightsAr,intComparisonAr,LepSaveNameAr,onlyDoSomeHists,histsToDo,signalPos)


    histMaxAr = normalizeHists(histLepAr,sumQCD,isQCDAr,normalizeBackgroundsTogether,backgroundIntSumAr,isSignalAr,weightsAr,legAr,datasetSaveNameAr,intComparisonAr,LepSaveNameAr,onlyDoSomeHists,histsToDo)



    if sumQCD:
        histMaxAr = scaleQCDHist(QCDSumIntAr,QCDSumHistLepAr,histMaxAr,legAr,onlyDoSomeHists,histsToDo,normalizeBackgroundsTogether,backgroundIntSumAr)



    comparisonCanAr = []
    comparisonHistStackAr = []
    for LepItr, LepSaveName in enumerate(LepSaveNameAr):
        if onlyDoSomeHists and LepItr >= histsToDo:
            break
        comparisonCanAr.append(TCanvas("comparisonCan{0}".format(LepSaveName),"comparisonCan{0}".format(LepSaveName),3600,2400))
        comparisonHistStackAr.append(THStack("hist{0}Stack".format(LepSaveName),LepTitleAr[LepItr]))


    maxIntAr = addHistsToStack(fileAr,histLepAr,isSignalAr,sumQCD,isQCDAr,comparisonHistStackAr,QCDSumHistLepAr,normalizeBackgroundsTogether,backgroundIntSumAr,LepSaveNameAr,signalPos,onlyDoSomeHists,histsToDo)

    #Loop over all hists that went into the THStack to get center and length of error bars for invisible hist

    invHistsAr = []
    drawInvAr = []
    cloneHistAr = []

    setUpInvHists(histLepAr,cloneHistAr,isSignalAr,sumQCD,isQCDAr,invHistsAr,LepSaveNameAr,intComparisonAr,drawInvAr,QCDSumIntAr,QCDSumHistLepAr,LepSaveNameAr,onlyDoSomeHists,histsToDo)


    setUpStackedHistAndDrawFoMPlot(histMaxAr,histLepAr,cloneHistAr,comparisonHistStackAr,invHistsAr,drawInvAr,legAr,comparisonCanAr,padAr,normalizeBackgroundsTogether,signalName,backgroundName,LepSaveNameAr,LepXTitleAr,signalPos,onlyDoSomeHists,histsToDo)

    comparisonUnstackedCanAr = []
    legUnstackedAr = []
    padUnstackedAr = []
    for LepItr, LepSaveName in enumerate(LepSaveNameAr):
        if onlyDoSomeHists and LepItr >= histsToDo:
            break
        comparisonUnstackedCanAr.append(TCanvas("comparisonUnstackedCan{0}".format(LepSaveName),"comparisonUnstackedCan{0}".format(LepSaveName),3600,2400))
        setUpLegend(legUnstackedAr)
        setUpPadsAr(padUnstackedAr,"{0}Pad".format("LepUnstackedSaveName"))

    setUpNonStackedHistAndFoMPlot(comparisonUnstackedCanAr,cloneHistAr,padAr,sumQCD,QCDSumHistLepAr,histMaxAr,isSignalAr,isQCDAr,normalizeBackgroundsTogether,maxIntAr,histLepAr,legAr,signalName,backgroundName,LepSaveNameAr,LepTitleAr,LepXTitleAr,signalPos,onlyDoSomeHists,histsToDo)




    ###############STARTING SEMI LEP GRAPHS###############
    padAr = []
    legAr = []

    """
    signalName = ""
    backgroundName = ""
    for k,fileA in enumerate(fileAr):
        if not sumQCD or not isQCDAr[k]:
            if isSignalAr[k]:
                signalName += "_"+datasetSaveNameAr[k]
            else:
                backgroundName += "_"+datasetSaveNameAr[k]

    """

    sumQCDCanAr = []
    #print(len(weightsAr),len(histSemiLepAr),len(histSemiLepAr[0]),len(SemiLepSaveNameAr),len(QCDSumHistSemiLepAr))
    if sumQCD:
        backgroundName += "_QCDSum"
        for SemiLepItr, SemiLepSaveName in enumerate(SemiLepSaveNameAr):
            if onlyDoSomeHists and SemiLepItr >= histsToDo:
                break
            sumQCDCanAr.append(TCanvas("{0}CanSemiLepQCDSum".format(SemiLepSaveName),"{0}CanSemiLepQCDSum".format(SemiLepSaveName),3600,2400))
            QCDSumHistSemiLepAr.append(TH1D("{0}HistSemiLepQCDSum".format(SemiLepSaveName),"{0}HistSemiLepQCDSum".format(SemiLepSaveName), SemiLepBinsAndRangeAr[SemiLepItr][0], SemiLepBinsAndRangeAr[SemiLepItr][1], SemiLepBinsAndRangeAr[SemiLepItr][2]))
        for k in range(len(histSemiLepAr)):
            if isQCDAr[k]:
                for SemiLepItr, SemiLepSaveName in enumerate(SemiLepSaveNameAr):
                    if onlyDoSomeHists and SemiLepItr >= histsToDo:
                        break
                    #print(k,SemiLepItr)
                    histSemiLepAr[k][SemiLepItr].Sumw2()
                    QCDSumHistSemiLepAr[SemiLepItr].Sumw2()
                    QCDSumHistSemiLepAr[SemiLepItr].Add(histSemiLepAr[k][SemiLepItr],weightsAr[k])


    for k,fileA in enumerate(fileAr):
        if not sumQCD or not isQCDAr[k]:
            for SemiLepItr, SemiLepSaveName in enumerate(SemiLepSaveNameAr):
                if onlyDoSomeHists and SemiLepItr >= histsToDo:
                    break
                canSemiLepAr[k][SemiLepItr].cd()
                histSemiLepAr[k][SemiLepItr].Draw("hist")
                if savePathBool:
                    canSemiLepAr[k][SemiLepItr].SaveAs("./Graphs/General/{0}/{1}{2}.png".format(datasetSaveNameAr[k],SemiLepSaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
                else:
                    canSemiLepAr[k][SemiLepItr].SaveAs("{0}{1}{2}.png".format(datasetSaveNameAr[k],SemiLepSaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))


    if sumQCD:
        for SemiLepItr, SemiLepSaveName in enumerate(SemiLepSaveNameAr):
            if onlyDoSomeHists and SemiLepItr >= histsToDo:
                break
            sumQCDCanAr[SemiLepItr].cd()
            QCDSumHistSemiLepAr[SemiLepItr].Draw("hist")
            if savePathBool:
                sumQCDCanAr[SemiLepItr].SaveAs("./Graphs/General/QCDSum/{0}{1}.png".format(SemiLepSaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
            else:
                sumQCDCanAr[SemiLepItr].SaveAs("QCDSum{0}{1}.png".format(SemiLepSaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))

    for SemiLepItr, SemiLepSaveName in enumerate(SemiLepSaveNameAr):
        if onlyDoSomeHists and SemiLepItr >= histsToDo:
            break
        setUpLegend(legAr)
        setUpPadsAr(padAr,"{0}Pad".format("SemiLepSaveName"))
        #padAr[-1][0].Draw()
        #padAr[-1][0].cd()

    intComparisonAr = []



    backgroundIntSumAr,QCDSumIntAr = setHistoElements(colorAr,sumQCD,QCDSumHistSemiLepAr,isQCDAr,histSemiLepAr,isSignalAr,normalizeBackgroundsTogether,weightsAr,intComparisonAr,SemiLepSaveNameAr,onlyDoSomeHists,histsToDo,signalPos)


    histMaxAr = normalizeHists(histSemiLepAr,sumQCD,isQCDAr,normalizeBackgroundsTogether,backgroundIntSumAr,isSignalAr,weightsAr,legAr,datasetSaveNameAr,intComparisonAr,SemiLepSaveNameAr,onlyDoSomeHists,histsToDo)



    if sumQCD:
        histMaxAr = scaleQCDHist(QCDSumIntAr,QCDSumHistSemiLepAr,histMaxAr,legAr,onlyDoSomeHists,histsToDo,normalizeBackgroundsTogether,backgroundIntSumAr)



    comparisonCanAr = []
    comparisonHistStackAr = []
    for SemiLepItr, SemiLepSaveName in enumerate(SemiLepSaveNameAr):
        if onlyDoSomeHists and SemiLepItr >= histsToDo:
            break
        comparisonCanAr.append(TCanvas("comparisonCan{0}".format(SemiLepSaveName),"comparisonCan{0}".format(SemiLepSaveName),3600,2400))
        comparisonHistStackAr.append(THStack("hist{0}Stack".format(SemiLepSaveName),SemiLepTitleAr[SemiLepItr]))


    maxIntAr = addHistsToStack(fileAr,histSemiLepAr,isSignalAr,sumQCD,isQCDAr,comparisonHistStackAr,QCDSumHistSemiLepAr,normalizeBackgroundsTogether,backgroundIntSumAr,SemiLepSaveNameAr,signalPos,onlyDoSomeHists,histsToDo)

    #Loop over all hists that went into the THStack to get center and length of error bars for invisible hist

    invHistsAr = []
    drawInvAr = []
    cloneHistAr = []

    setUpInvHists(histSemiLepAr,cloneHistAr,isSignalAr,sumQCD,isQCDAr,invHistsAr,SemiLepSaveNameAr,intComparisonAr,drawInvAr,QCDSumIntAr,QCDSumHistSemiLepAr,SemiLepSaveNameAr,onlyDoSomeHists,histsToDo)


    setUpStackedHistAndDrawFoMPlot(histMaxAr,histSemiLepAr,cloneHistAr,comparisonHistStackAr,invHistsAr,drawInvAr,legAr,comparisonCanAr,padAr,normalizeBackgroundsTogether,signalName,backgroundName,SemiLepSaveNameAr,SemiLepXTitleAr,signalPos,onlyDoSomeHists,histsToDo)

    comparisonUnstackedCanAr = []
    legUnstackedAr = []
    padUnstackedAr = []
    for SemiLepItr, SemiLepSaveName in enumerate(SemiLepSaveNameAr):
        if onlyDoSomeHists and SemiLepItr >= histsToDo:
            break
        comparisonUnstackedCanAr.append(TCanvas("comparisonUnstackedCan{0}".format(SemiLepSaveName),"comparisonUnstackedCan{0}".format(SemiLepSaveName),3600,2400))
        setUpLegend(legUnstackedAr)
        setUpPadsAr(padUnstackedAr,"{0}Pad".format("SemiLepUnstackedSaveName"))

    setUpNonStackedHistAndFoMPlot(comparisonUnstackedCanAr,cloneHistAr,padAr,sumQCD,QCDSumHistSemiLepAr,histMaxAr,isSignalAr,isQCDAr,normalizeBackgroundsTogether,maxIntAr,histSemiLepAr,legAr,signalName,backgroundName,SemiLepSaveNameAr,SemiLepTitleAr,SemiLepXTitleAr,signalPos,onlyDoSomeHists,histsToDo)


    ###############STARTING HAD GRAPHS###############
    padAr = []
    legAr = []

    """
    signalName = ""
    backgroundName = ""
    for k,fileA in enumerate(fileAr):
        if not sumQCD or not isQCDAr[k]:
            if isSignalAr[k]:
                signalName += "_"+datasetSaveNameAr[k]
            else:
                backgroundName += "_"+datasetSaveNameAr[k]

    """

    sumQCDCanAr = []
    #print(len(weightsAr),len(histHadAr),len(histHadAr[0]),len(HadSaveNameAr),len(QCDSumHistHadAr))
    if sumQCD:
        backgroundName += "_QCDSum"
        for HadItr, HadSaveName in enumerate(HadSaveNameAr):
            if onlyDoSomeHists and HadItr >= histsToDo:
                break
            sumQCDCanAr.append(TCanvas("{0}CanHadQCDSum".format(HadSaveName),"{0}CanHadQCDSum".format(HadSaveName),3600,2400))
            QCDSumHistHadAr.append(TH1D("{0}HistHadQCDSum".format(HadSaveName),"{0}HistHadQCDSum".format(HadSaveName), HadBinsAndRangeAr[HadItr][0], HadBinsAndRangeAr[HadItr][1], HadBinsAndRangeAr[HadItr][2]))
        for k in range(len(histHadAr)):
            if isQCDAr[k]:
                for HadItr, HadSaveName in enumerate(HadSaveNameAr):
                    if onlyDoSomeHists and HadItr >= histsToDo:
                        break
                    #print(k,HadItr)
                    histHadAr[k][HadItr].Sumw2()
                    QCDSumHistHadAr[HadItr].Sumw2()
                    QCDSumHistHadAr[HadItr].Add(histHadAr[k][HadItr],weightsAr[k])


    for k,fileA in enumerate(fileAr):
        if not sumQCD or not isQCDAr[k]:
            for HadItr, HadSaveName in enumerate(HadSaveNameAr):
                if onlyDoSomeHists and HadItr >= histsToDo:
                    break
                canHadAr[k][HadItr].cd()
                histHadAr[k][HadItr].Draw("hist")
                if savePathBool:
                    canHadAr[k][HadItr].SaveAs("./Graphs/General/{0}/{1}{2}.png".format(datasetSaveNameAr[k],HadSaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
                else:
                    canHadAr[k][HadItr].SaveAs("{0}{1}{2}.png".format(datasetSaveNameAr[k],HadSaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))


    if sumQCD:
        for HadItr, HadSaveName in enumerate(HadSaveNameAr):
            if onlyDoSomeHists and HadItr >= histsToDo:
                break
            sumQCDCanAr[HadItr].cd()
            QCDSumHistHadAr[HadItr].Draw("hist")
            if savePathBool:
                sumQCDCanAr[HadItr].SaveAs("./Graphs/General/QCDSum/{0}{1}.png".format(HadSaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
            else:
                sumQCDCanAr[HadItr].SaveAs("QCDSum{0}{1}.png".format(HadSaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))

    for HadItr, HadSaveName in enumerate(HadSaveNameAr):
        if onlyDoSomeHists and HadItr >= histsToDo:
            break
        setUpLegend(legAr)
        setUpPadsAr(padAr,"{0}Pad".format("HadSaveName"))
        #padAr[-1][0].Draw()
        #padAr[-1][0].cd()

    intComparisonAr = []



    backgroundIntSumAr,QCDSumIntAr = setHistoElements(colorAr,sumQCD,QCDSumHistHadAr,isQCDAr,histHadAr,isSignalAr,normalizeBackgroundsTogether,weightsAr,intComparisonAr,HadSaveNameAr,onlyDoSomeHists,histsToDo,signalPos)


    histMaxAr = normalizeHists(histHadAr,sumQCD,isQCDAr,normalizeBackgroundsTogether,backgroundIntSumAr,isSignalAr,weightsAr,legAr,datasetSaveNameAr,intComparisonAr,HadSaveNameAr,onlyDoSomeHists,histsToDo)



    if sumQCD:
        histMaxAr = scaleQCDHist(QCDSumIntAr,QCDSumHistHadAr,histMaxAr,legAr,onlyDoSomeHists,histsToDo,normalizeBackgroundsTogether,backgroundIntSumAr)



    comparisonCanAr = []
    comparisonHistStackAr = []
    for HadItr, HadSaveName in enumerate(HadSaveNameAr):
        if onlyDoSomeHists and HadItr >= histsToDo:
            break
        comparisonCanAr.append(TCanvas("comparisonCan{0}".format(HadSaveName),"comparisonCan{0}".format(HadSaveName),3600,2400))
        comparisonHistStackAr.append(THStack("hist{0}Stack".format(HadSaveName),HadTitleAr[HadItr]))


    maxIntAr = addHistsToStack(fileAr,histHadAr,isSignalAr,sumQCD,isQCDAr,comparisonHistStackAr,QCDSumHistHadAr,normalizeBackgroundsTogether,backgroundIntSumAr,HadSaveNameAr,signalPos,onlyDoSomeHists,histsToDo)

    #Loop over all hists that went into the THStack to get center and length of error bars for invisible hist

    invHistsAr = []
    drawInvAr = []
    cloneHistAr = []

    setUpInvHists(histHadAr,cloneHistAr,isSignalAr,sumQCD,isQCDAr,invHistsAr,HadSaveNameAr,intComparisonAr,drawInvAr,QCDSumIntAr,QCDSumHistHadAr,HadSaveNameAr,onlyDoSomeHists,histsToDo)


    setUpStackedHistAndDrawFoMPlot(histMaxAr,histHadAr,cloneHistAr,comparisonHistStackAr,invHistsAr,drawInvAr,legAr,comparisonCanAr,padAr,normalizeBackgroundsTogether,signalName,backgroundName,HadSaveNameAr,HadXTitleAr,signalPos,onlyDoSomeHists,histsToDo)

    comparisonUnstackedCanAr = []
    legUnstackedAr = []
    padUnstackedAr = []
    for HadItr, HadSaveName in enumerate(HadSaveNameAr):
        if onlyDoSomeHists and HadItr >= histsToDo:
            break
        comparisonUnstackedCanAr.append(TCanvas("comparisonUnstackedCan{0}".format(HadSaveName),"comparisonUnstackedCan{0}".format(HadSaveName),3600,2400))
        setUpLegend(legUnstackedAr)
        setUpPadsAr(padUnstackedAr,"{0}Pad".format("HadUnstackedSaveName"))

    setUpNonStackedHistAndFoMPlot(comparisonUnstackedCanAr,cloneHistAr,padAr,sumQCD,QCDSumHistHadAr,histMaxAr,isSignalAr,isQCDAr,normalizeBackgroundsTogether,maxIntAr,histHadAr,legAr,signalName,backgroundName,HadSaveNameAr,HadTitleAr,HadXTitleAr,signalPos,onlyDoSomeHists,histsToDo)

###############STARTING RAW LHE GRAPHS###############

sumQCD = False
normalizeBackgroundsTogether = False


signalName = ""
backgroundName = ""
for k,fileA in enumerate(fileAr):
    if useLHEAr[k]:
        if isSignalAr[k]:
            signalName += "_"+datasetSaveNameAr[k]
        else:
            backgroundName += "_"+datasetSaveNameAr[k]

for k,fileA in enumerate(fileAr):
    if useLHEAr[k]:
        for RawItr, RawSaveName in enumerate(RawSaveNameAr):
            if onlyDoSomeHists and RawItr >= histsToDo:
                break
            canRawAr[k][RawItr].cd()
            histRawAr[k][RawItr].Draw("hist")
            if savePathBool:
                canRawAr[k][RawItr].SaveAs("./Graphs/General/{0}/{1}{2}.png".format(datasetSaveNameAr[k],RawSaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
            else:
                canRawAr[k][RawItr].SaveAs("{0}{1}{2}.png".format(datasetSaveNameAr[k],RawSaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
legUnstackedAr = []
padUnstackedAr = []
for RawItr, RawSaveName in enumerate(RawSaveNameAr):
    if onlyDoSomeHists and RawItr >= histsToDo:
        break
    setUpLegend(legUnstackedAr)
    setUpPadsAr(padUnstackedAr,"{0}Pad".format("RawSaveName"))

intComparisonAr = []



setHistoElementsForLHETrees(colorAr,histRawAr,isSignalAr,weightsAr,intComparisonAr,RawSaveNameAr,onlyDoSomeHists,histsToDo,signalPos,useLHEAr)

histMaxAr = normalizeHistsForLHETrees(histRawAr,isSignalAr,weightsAr,legUnstackedAr,datasetSaveNameAr,intComparisonAr,RawSaveNameAr,onlyDoSomeHists,histsToDo,useLHEAr)

cloneHistAr = []

comparisonCanAr = []
#comparisonHistStackAr = []
for RawItr, RawSaveName in enumerate(RawSaveNameAr):
    if onlyDoSomeHists and RawItr >= histsToDo:
        break
    comparisonCanAr.append(TCanvas("comparisonCan{0}".format(RawSaveName),"comparisonCan{0}".format(RawSaveName),3600,2400))
    #comparisonHistStackAr.append(THStack("hist{0}Stack".format(RawSaveName),RawTitleAr[RawItr]))
comparisonUnstackedCanAr = []

for RawItr, RawSaveName in enumerate(RawSaveNameAr):
    if onlyDoSomeHists and RawItr >= histsToDo:
        break
    comparisonUnstackedCanAr.append(TCanvas("comparisonUnstackedCan{0}".format(RawSaveName),"comparisonUnstackedCan{0}".format(RawSaveName),3600,2400))

setUpNonStackedHistAndFoMPlotForLHETrees(comparisonUnstackedCanAr,cloneHistAr,padUnstackedAr,histMaxAr,isSignalAr,histRawAr,legUnstackedAr,signalName,backgroundName,RawSaveNameAr,RawTitleAr,RawXTitleAr,signalPos,onlyDoSomeHists,histsToDo,useLHEAr)



###############STARTING RAW LHE GRAPHS###############

sumQCD = False
normalizeBackgroundsTogether = False


signalName = ""
backgroundName = ""
for k,fileA in enumerate(fileAr):
    if useLHEAr[k]:
        if isSignalAr[k]:
            signalName += "_"+datasetSaveNameAr[k]
        else:
            backgroundName += "_"+datasetSaveNameAr[k]

for k,fileA in enumerate(fileAr):
    if useLHEAr[k]:
        for SelectedItr, SelectedSaveName in enumerate(SelectedSaveNameAr):
            if onlyDoSomeHists and SelectedItr >= histsToDo:
                break
            canSelectedAr[k][SelectedItr].cd()
            histSelectedAr[k][SelectedItr].Draw("hist")
            if savePathBool:
                canSelectedAr[k][SelectedItr].SaveAs("./Graphs/General/{0}/{1}{2}.png".format(datasetSaveNameAr[k],SelectedSaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
            else:
                canSelectedAr[k][SelectedItr].SaveAs("{0}{1}{2}.png".format(datasetSaveNameAr[k],SelectedSaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
legUnstackedAr = []
padUnstackedAr = []
for SelectedItr, SelectedSaveName in enumerate(SelectedSaveNameAr):
    if onlyDoSomeHists and SelectedItr >= histsToDo:
        break
    setUpLegend(legUnstackedAr)
    setUpPadsAr(padUnstackedAr,"{0}Pad".format("SelectedSaveName"))

intComparisonAr = []



setHistoElementsForLHETrees(colorAr,histSelectedAr,isSignalAr,weightsAr,intComparisonAr,SelectedSaveNameAr,onlyDoSomeHists,histsToDo,signalPos,useLHEAr)

histMaxAr = normalizeHistsForLHETrees(histSelectedAr,isSignalAr,weightsAr,legUnstackedAr,datasetSaveNameAr,intComparisonAr,SelectedSaveNameAr,onlyDoSomeHists,histsToDo,useLHEAr)

cloneHistAr = []

comparisonCanAr = []
#comparisonHistStackAr = []
for SelectedItr, SelectedSaveName in enumerate(SelectedSaveNameAr):
    if onlyDoSomeHists and SelectedItr >= histsToDo:
        break
    comparisonCanAr.append(TCanvas("comparisonCan{0}".format(SelectedSaveName),"comparisonCan{0}".format(SelectedSaveName),3600,2400))
    #comparisonHistStackAr.append(THStack("hist{0}Stack".format(SelectedSaveName),SelectedTitleAr[SelectedItr]))
comparisonUnstackedCanAr = []

for SelectedItr, SelectedSaveName in enumerate(SelectedSaveNameAr):
    if onlyDoSomeHists and SelectedItr >= histsToDo:
        break
    comparisonUnstackedCanAr.append(TCanvas("comparisonUnstackedCan{0}".format(SelectedSaveName),"comparisonUnstackedCan{0}".format(SelectedSaveName),3600,2400))

setUpNonStackedHistAndFoMPlotForLHETrees(comparisonUnstackedCanAr,cloneHistAr,padUnstackedAr,histMaxAr,isSignalAr,histSelectedAr,legUnstackedAr,signalName,backgroundName,SelectedSaveNameAr,SelectedTitleAr,SelectedXTitleAr,signalPos,onlyDoSomeHists,histsToDo,useLHEAr)
