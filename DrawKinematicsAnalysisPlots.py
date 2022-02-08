import datetime
from ROOT import TFile, TChain, gDirectory, TApplication, TMath, Math, TMinuit, TROOT, TSystem, TTree, TVector2, THStack
# You probably also want to import TH1D and TCanvas,
# unless you're not making any histograms.
from ROOT import TH1F, TH1D, TF1, TGraph, TGraphErrors, TLegend, TLine, TPaveText, TStyle
from ROOT import TH2D, TH2F
from FunctionsForKinematicsAnalysisPlots import *

today = datetime.datetime.today()

datasetSaveNameAr = []
fileAr = []
XSAr = []
totalEvents = []
fileAr = []
nameAr = []
colorAr = []
useLHEAr = []


if testRun:
    if useTightdRCut:
        fileAr.append(TFile.Open("{0}FullAnalysistestRunTighterCut.root".format(forCondorStr)))
    else:
        fileAr.append(TFile.Open("{0}FullAnalysistestRun.root".format(forCondorStr)))
    colorAr.append(1)
    datasetSaveNameAr.append("testRun")
    
    testRunXSTree = fileAr[-1].crossSectionTree
    tmpXSAvg = 0
    tmpXSCnt = 0
    
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

if MGOHW:
    if useTightdRCut:
        fileAr.append(TFile.Open("{0}FullAnalysisEFTTighterCut.root".format(forCondorStr)))
    else:
        fileAr.append(TFile.Open("{0}FullAnalysisEFT.root".format(forCondorStr)))
    colorAr.append(2)
    datasetSaveNameAr.append("OHW")
    
    
    useLHEAr.append(True)

    OHWXSTree = fileAr[-1].crossSectionTree
    tmpXSAvg = 0
    tmpXSCnt = 0
    for OHWXS in OHWXSTree:
        tmpXSAvg += OHWXS.crossSectionVar
        tmpXSCnt += 1
    tmpXSAvg = tmpXSAvg / tmpXSCnt
    XSAr.append(tmpXSAvg)
    ENTree = fileAr[-1].evNumTree
    evNum = 0
    for ev in ENTree:
        evNum = ev.nEv
    totalEvents.append(evNum)

if MGOSix:
    if useTightdRCut:
        fileAr.append(TFile.Open("{0}KinematicsAnalysisOSixTighterCut.root".format(forCondorStr)))
    else:
        fileAr.append(TFile.Open("{0}KinematicsAnalysisOSix.root".format(forCondorStr)))
    colorAr.append(6)
    datasetSaveNameAr.append("OSix")
    
    
    useLHEAr.append(True)

    OSixXSTree = fileAr[-1].crossSectionTree
    tmpXSAvg = 0
    tmpXSCnt = 0
    for OSixXS in OSixXSTree:
        tmpXSAvg += OSixXS.crossSectionVar
        tmpXSCnt += 1
    tmpXSAvg = tmpXSAvg / tmpXSCnt
    XSAr.append(tmpXSAvg)
    ENTree = fileAr[-1].evNumTree
    evNum = 0
    for ev in ENTree:
        evNum = ev.nEv
    totalEvents.append(evNum)
if MGOSixEtaDifCut:
    if useTightdRCut:
        fileAr.append(TFile.Open("{0}KinematicsAnalysisOSix_EtaDifCutTighterCut.root".format(forCondorStr)))
    else:
        fileAr.append(TFile.Open("{0}KinematicsAnalysisOSix_EtaDifCut.root".format(forCondorStr)))
    colorAr.append(7)
    datasetSaveNameAr.append("OSixEtaDifCut")
    
    
    useLHEAr.append(True)

    OSixEtaDifCutXSTree = fileAr[-1].crossSectionTree
    tmpXSAvg = 0
    tmpXSCnt = 0
    for OSixEtaDifCutXS in OSixEtaDifCutXSTree:
        tmpXSAvg += OSixEtaDifCutXS.crossSectionVar
        tmpXSCnt += 1
    tmpXSAvg = tmpXSAvg / tmpXSCnt
    XSAr.append(tmpXSAvg)
    ENTree = fileAr[-1].evNumTree
    evNum = 0
    for ev in ENTree:
        evNum = ev.nEv
    totalEvents.append(evNum)
if MGOHBox:
    if useTightdRCut:
        fileAr.append(TFile.Open("{0}KinematicsAnalysisOHBoxTighterCut.root".format(forCondorStr)))
    else:
        fileAr.append(TFile.Open("{0}KinematicsAnalysisOHBox.root".format(forCondorStr)))
    colorAr.append(4)
    datasetSaveNameAr.append("OHBox")
    
    
    useLHEAr.append(True)

    OHBoxXSTree = fileAr[-1].crossSectionTree
    tmpXSAvg = 0
    tmpXSCnt = 0
    for OHBoxXS in OHBoxXSTree:
        tmpXSAvg += OHBoxXS.crossSectionVar
        tmpXSCnt += 1
    tmpXSAvg = tmpXSAvg / tmpXSCnt
    XSAr.append(tmpXSAvg)
    ENTree = fileAr[-1].evNumTree
    evNum = 0
    for ev in ENTree:
        evNum = ev.nEv
    totalEvents.append(evNum)
if MGOHBoxEtaDifCut:
    if useTightdRCut:
        fileAr.append(TFile.Open("{0}KinematicsAnalysisOHBox_EtaDifCutTighterCut.root".format(forCondorStr)))
    else:
        fileAr.append(TFile.Open("{0}KinematicsAnalysisOHBox_EtaDifCut.root".format(forCondorStr)))
    colorAr.append(8)
    datasetSaveNameAr.append("OHBoxEtaDifCut")
    
    
    useLHEAr.append(True)

    OHBoxEtaDifCutXSTree = fileAr[-1].crossSectionTree
    tmpXSAvg = 0
    tmpXSCnt = 0
    for OHBoxEtaDifCutXS in OHBoxEtaDifCutXSTree:
        tmpXSAvg += OHBoxEtaDifCutXS.crossSectionVar
        tmpXSCnt += 1
    tmpXSAvg = tmpXSAvg / tmpXSCnt
    XSAr.append(tmpXSAvg)
    ENTree = fileAr[-1].evNumTree
    evNum = 0
    for ev in ENTree:
        evNum = ev.nEv
    totalEvents.append(evNum)
if MGOHDD:
    if useTightdRCut:
        fileAr.append(TFile.Open("{0}KinematicsAnalysisOHDDTighterCut.root".format(forCondorStr)))
    else:
        fileAr.append(TFile.Open("{0}KinematicsAnalysisOHDD.root".format(forCondorStr)))
    colorAr.append(1)
    datasetSaveNameAr.append("OHDD")
    
    
    useLHEAr.append(True)

    OHDDXSTree = fileAr[-1].crossSectionTree
    tmpXSAvg = 0
    tmpXSCnt = 0
    for OHDDXS in OHDDXSTree:
        tmpXSAvg += OHDDXS.crossSectionVar
        tmpXSCnt += 1
    tmpXSAvg = tmpXSAvg / tmpXSCnt
    XSAr.append(tmpXSAvg)
    ENTree = fileAr[-1].evNumTree
    evNum = 0
    for ev in ENTree:
        evNum = ev.nEv
    totalEvents.append(evNum)
if MGOHDDEtaDifCut:
    if useTightdRCut:
        fileAr.append(TFile.Open("{0}KinematicsAnalysisOHDD_EtaDifCutTighterCut.root".format(forCondorStr)))
    else:
        fileAr.append(TFile.Open("{0}KinematicsAnalysisOHDD_EtaDifCut.root".format(forCondorStr)))
    colorAr.append(9)
    datasetSaveNameAr.append("OHDDEtaDifCut")
    
    
    useLHEAr.append(True)

    OHDDEtaDifCutXSTree = fileAr[-1].crossSectionTree
    tmpXSAvg = 0
    tmpXSCnt = 0
    for OHDDEtaDifCutXS in OHDDEtaDifCutXSTree:
        tmpXSAvg += OHDDEtaDifCutXS.crossSectionVar
        tmpXSCnt += 1
    tmpXSAvg = tmpXSAvg / tmpXSCnt
    XSAr.append(tmpXSAvg)
    ENTree = fileAr[-1].evNumTree
    evNum = 0
    for ev in ENTree:
        evNum = ev.nEv
    totalEvents.append(evNum)

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
    
    if useLHETree and useLHEAr[k]:
        if not onlyTaggedTrees:

            evCtr = 0

            HFJGenTree = fileA.HFJGenTree
            histHFJGenAr.append([])
            canHFJGenAr.append([])
            
            #Initialize all HFJGen hists
            print("Initializing HFJGen hists")
            for HFJGenItr, HFJGenSaveName in enumerate(HFJGenSaveNameAr):
                if onlyDoSomeHists and HFJGenItr >= histsToDo:
                    break
                canHFJGenAr[-1].append(TCanvas("{0}CanHFJGen{1}".format(HFJGenSaveName,datasetSaveNameAr[k]),"{0}CanHFJGen{1}".format(HFJGenSaveName,datasetSaveNameAr[k]),3600,2400))
                histHFJGenAr[-1].append(TH1D("{0}HistHFJGen{1}".format(HFJGenSaveName,datasetSaveNameAr[k]),"{0}HistHFJGen{1}".format(HFJGenSaveName,datasetSaveNameAr[k]), HFJGenBinsAndRangeAr[HFJGenItr][0], HFJGenBinsAndRangeAr[HFJGenItr][1], HFJGenBinsAndRangeAr[HFJGenItr][2]))
            print("Looping over events")
            #LOOP OVER EVENTS IN FILE k
            for j,ev in enumerate(HFJGenTree):
                if breakEvEarly and evCtr >= breakEvAt:
                    break
                if evCtr % 1000 == 0:
                    print("ev:",evCtr)
                
                valAr = [ev.HFJ_pt_FromGenMatchL,ev.HFJ_eta_FromGenMatchL,ev.HFJ_phi_FromGenMatchL,ev.HFJ_mass_FromGenMatchL,ev.HFJ_dRFromFJ_FromGenMatchL,
                ev.nHFJDecay_FromGenMatchL,ev.HFJ_decaypdgId_FromGenMatchL]

                for valItr,valA in enumerate(valAr):
                    if onlyDoSomeHists and valItr >= histsToDo:
                        break
                    #if evCtr <20 and evCtr > 10 and valItr == 0:
                    #    print(valA)
                    #print(valItr,valA)
                    #print(dir(valA))
                    #print(type(valA))
                    #print(len(histHFJGenAr),len(histHFJGenAr[k]))
                    #print("-----")
                    #if str(type(valA)) == "<class 'ROOT.vector<int>'>":
                    if "vector" in str(type(valA)):
                        for valEl in valA:
                            #print(valEl)
                            histHFJGenAr[k][valItr].Fill(valEl)
                    else:
                        histHFJGenAr[k][valItr].Fill(valA)
                    #histHFJGenAr[k][valItr].Fill(valA)
                evCtr += 1

            evCtr = 0

            ZFJGenTree = fileA.ZFJGenTree
            histZFJGenAr.append([])
            canZFJGenAr.append([])
            
            #Initialize all ZFJGen hists
            print("Initializing ZFJGen hists")
            for ZFJGenItr, ZFJGenSaveName in enumerate(ZFJGenSaveNameAr):
                if onlyDoSomeHists and ZFJGenItr >= histsToDo:
                    break
                canZFJGenAr[-1].append(TCanvas("{0}CanZFJGen{1}".format(ZFJGenSaveName,datasetSaveNameAr[k]),"{0}CanZFJGen{1}".format(ZFJGenSaveName,datasetSaveNameAr[k]),3600,2400))
                histZFJGenAr[-1].append(TH1D("{0}HistZFJGen{1}".format(ZFJGenSaveName,datasetSaveNameAr[k]),"{0}HistZFJGen{1}".format(ZFJGenSaveName,datasetSaveNameAr[k]), ZFJGenBinsAndRangeAr[ZFJGenItr][0], ZFJGenBinsAndRangeAr[ZFJGenItr][1], ZFJGenBinsAndRangeAr[ZFJGenItr][2]))
            print("Looping over events")
            #LOOP OVER EVENTS IN FILE k
            for j,ev in enumerate(ZFJGenTree):
                if breakEvEarly and evCtr >= breakEvAt:
                    break
                if evCtr % 1000 == 0:
                    print("ev:",evCtr)
                
                valAr = [ev.ZFJLead_pt_FromGenMatchL,ev.ZFJLead_eta_FromGenMatchL,ev.ZFJLead_phi_FromGenMatchL,ev.ZFJLead_mass_FromGenMatchL,ev.ZFJLead_dRFromFJ_FromGenMatchL,
                ev.nZFJLeadDecay_FromGenMatchL,ev.ZFJLead_decaypdgId_FromGenMatchL,
                ev.ZFJTrailing_pt_FromGenMatchL,ev.ZFJTrailing_eta_FromGenMatchL,ev.ZFJTrailing_phi_FromGenMatchL,ev.ZFJTrailing_mass_FromGenMatchL,ev.ZFJTrailing_dRFromFJ_FromGenMatchL,
                ev.nZFJTrailingDecay_FromGenMatchL,ev.ZFJTrailing_decaypdgId_FromGenMatchL,
                ev.ZFJPair_InvMass_FromGenMatchL,ev.ZFJPair_EtaSep_FromGenMatchL]

                for valItr,valA in enumerate(valAr):
                    if onlyDoSomeHists and valItr >= histsToDo:
                        break
                    #if evCtr <20 and evCtr > 10 and valItr == 0:
                    #    print(valA)
                    #if str(type(valA)) == "<class 'ROOT.vector<int>'>":
                    if "vector" in str(type(valA)):
                        for valEl in valA:
                            histZFJGenAr[k][valItr].Fill(valEl)
                    else:
                        histZFJGenAr[k][valItr].Fill(valA)
                evCtr += 1


            evCtr = 0

            ZHFJGenTree = fileA.ZHFJGenTree
            histZHFJGenAr.append([])
            canZHFJGenAr.append([])
            
            #Initialize all ZHFJGen hists
            print("Initializing ZHFJGen hists")
            for ZHFJGenItr, ZHFJGenSaveName in enumerate(ZHFJGenSaveNameAr):
                if onlyDoSomeHists and ZHFJGenItr >= histsToDo:
                    break
                canZHFJGenAr[-1].append(TCanvas("{0}CanZHFJGen{1}".format(ZHFJGenSaveName,datasetSaveNameAr[k]),"{0}CanZHFJGen{1}".format(ZHFJGenSaveName,datasetSaveNameAr[k]),3600,2400))
                histZHFJGenAr[-1].append(TH1D("{0}HistZHFJGen{1}".format(ZHFJGenSaveName,datasetSaveNameAr[k]),"{0}HistZHFJGen{1}".format(ZHFJGenSaveName,datasetSaveNameAr[k]), ZHFJGenBinsAndRangeAr[ZHFJGenItr][0], ZHFJGenBinsAndRangeAr[ZHFJGenItr][1], ZHFJGenBinsAndRangeAr[ZHFJGenItr][2]))
            print("Looping over events")
            #LOOP OVER EVENTS IN FILE k
            for j,ev in enumerate(ZHFJGenTree):
                if breakEvEarly and evCtr >= breakEvAt:
                    break
                if evCtr % 1000 == 0:
                    print("ev:",evCtr)
                
                valAr = [ev.ZHFJ_ZPairPlusHInvMass_FromGenMatchL]

                for valItr,valA in enumerate(valAr):
                    if onlyDoSomeHists and valItr >= histsToDo:
                        break
                    #if evCtr <20 and evCtr > 10 and valItr == 0:
                    #    print(valA)
                    histZHFJGenAr[k][valItr].Fill(valA)
                evCtr += 1


            evCtr = 0

            ZHJGenTree = fileA.ZHJGenTree
            histZHJGenAr.append([])
            canZHJGenAr.append([])
            
            #Initialize all ZHJGen hists
            print("Initializing ZHJGen hists")
            for ZHJGenItr, ZHJGenSaveName in enumerate(ZHJGenSaveNameAr):
                if onlyDoSomeHists and ZHJGenItr >= histsToDo:
                    break
                canZHJGenAr[-1].append(TCanvas("{0}CanZHJGen{1}".format(ZHJGenSaveName,datasetSaveNameAr[k]),"{0}CanZHJGen{1}".format(ZHJGenSaveName,datasetSaveNameAr[k]),3600,2400))
                histZHJGenAr[-1].append(TH1D("{0}HistZHJGen{1}".format(ZHJGenSaveName,datasetSaveNameAr[k]),"{0}HistZHJGen{1}".format(ZHJGenSaveName,datasetSaveNameAr[k]), ZHJGenBinsAndRangeAr[ZHJGenItr][0], ZHJGenBinsAndRangeAr[ZHJGenItr][1], ZHJGenBinsAndRangeAr[ZHJGenItr][2]))
            print("Looping over events")
            #LOOP OVER EVENTS IN FILE k
            for j,ev in enumerate(ZHJGenTree):
                if breakEvEarly and evCtr >= breakEvAt:
                    break
                if evCtr % 1000 == 0:
                    print("ev:",evCtr)
                
                valAr = [ev.ZHJ_ZPairPlusHInvMass_FromGenMatchL]

                for valItr,valA in enumerate(valAr):
                    if onlyDoSomeHists and valItr >= histsToDo:
                        break
                    #if evCtr <20 and evCtr > 10 and valItr == 0:
                    #    print(valA)
                    histZHJGenAr[k][valItr].Fill(valA)
                evCtr += 1



            evCtr = 0

            ZJGenTree = fileA.ZJGenTree
            histZJGenAr.append([])
            canZJGenAr.append([])
            
            #Initialize all ZJGen hists
            print("Initializing ZJGen hists")
            for ZJGenItr, ZJGenSaveName in enumerate(ZJGenSaveNameAr):
                if onlyDoSomeHists and ZJGenItr >= histsToDo:
                    break
                canZJGenAr[-1].append(TCanvas("{0}CanZJGen{1}".format(ZJGenSaveName,datasetSaveNameAr[k]),"{0}CanZJGen{1}".format(ZJGenSaveName,datasetSaveNameAr[k]),3600,2400))
                histZJGenAr[-1].append(TH1D("{0}HistZJGen{1}".format(ZJGenSaveName,datasetSaveNameAr[k]),"{0}HistZJGen{1}".format(ZJGenSaveName,datasetSaveNameAr[k]), ZJGenBinsAndRangeAr[ZJGenItr][0], ZJGenBinsAndRangeAr[ZJGenItr][1], ZJGenBinsAndRangeAr[ZJGenItr][2]))
            print("Looping over events")
            #LOOP OVER EVENTS IN FILE k
            for j,ev in enumerate(ZJGenTree):
                if breakEvEarly and evCtr >= breakEvAt:
                    break
                if evCtr % 1000 == 0:
                    print("ev:",evCtr)
                
                valAr = [ev.ZJLead_pt_FromGenMatchL,ev.ZJLead_eta_FromGenMatchL,ev.ZJLead_phi_FromGenMatchL,ev.ZJLead_mass_FromGenMatchL,ev.ZJLead_dRFromJ_FromGenMatchL,
                ev.nZJLeadDecay_FromGenMatchL,ev.ZJLead_decaypdgId_FromGenMatchL,
                ev.ZJTrailing_pt_FromGenMatchL,ev.ZJTrailing_eta_FromGenMatchL,ev.ZJTrailing_phi_FromGenMatchL,ev.ZJTrailing_mass_FromGenMatchL,ev.ZJTrailing_dRFromJ_FromGenMatchL,
                ev.nZJTrailingDecay_FromGenMatchL,ev.ZJTrailing_decaypdgId_FromGenMatchL,
                ev.ZJPair_InvMass_FromGenMatchL,ev.ZJPair_EtaSep_FromGenMatchL]

                for valItr,valA in enumerate(valAr):
                    if onlyDoSomeHists and valItr >= histsToDo:
                        break
                    #if evCtr <20 and evCtr > 10 and valItr == 0:
                    #    print(valA)
                    #if str(type(valA)) == "<class 'ROOT.vector<int>'>":
                    if "vector" in str(type(valA)):
                        for valEl in valA:
                            histZJGenAr[k][valItr].Fill(valEl)
                    else:
                        histZJGenAr[k][valItr].Fill(valA)
                evCtr += 1


            evCtr = 0

            GenRawTree = fileA.GenRawTree
            histGenRawAr.append([])
            canGenRawAr.append([])
            
            #Initialize all GenRaw hists
            print("Initializing GenRaw hists")
            for GenRawItr, GenRawSaveName in enumerate(GenRawSaveNameAr):
                if onlyDoSomeHists and GenRawItr >= histsToDo:
                    break
                canGenRawAr[-1].append(TCanvas("{0}CanGenRaw{1}".format(GenRawSaveName,datasetSaveNameAr[k]),"{0}CanGenRaw{1}".format(GenRawSaveName,datasetSaveNameAr[k]),3600,2400))
                histGenRawAr[-1].append(TH1D("{0}HistGenRaw{1}".format(GenRawSaveName,datasetSaveNameAr[k]),"{0}HistGenRaw{1}".format(GenRawSaveName,datasetSaveNameAr[k]), GenRawBinsAndRangeAr[GenRawItr][0], GenRawBinsAndRangeAr[GenRawItr][1], GenRawBinsAndRangeAr[GenRawItr][2]))
            print("Looping over events")
            #LOOP OVER EVENTS IN FILE k
            for j,ev in enumerate(GenRawTree):
                if breakEvEarly and evCtr >= breakEvAt:
                    break
                if evCtr % 1000 == 0:
                    print("ev:",evCtr)
                
                valAr = [ev.ZOne_pt_FromGenRawL,ev.ZOne_eta_FromGenRawL,ev.ZOne_phi_FromGenRawL,ev.ZOne_mass_FromGenRawL,ev.ZOne_pdgId_FromGenRawL,ev.ZOne_genPartIdxMother_FromGenRawL,
                ev.nZOneDecay_FromGenRawL,ev.ZOne_decaypdgId_FromGenRawL,
                ev.ZTwo_pt_FromGenRawL,ev.ZTwo_eta_FromGenRawL,ev.ZTwo_phi_FromGenRawL,ev.ZTwo_mass_FromGenRawL,ev.ZTwo_pdgId_FromGenRawL,ev.ZTwo_genPartIdxMother_FromGenRawL,
                ev.nZTwoDecay_FromGenRawL,ev.ZTwo_decaypdgId_FromGenRawL,
                ev.ZPair_InvMass_FromGenRawL,ev.ZPair_EtaSep_FromGenRawL,
                ev.H_pt_FromGenRawL,ev.H_eta_FromGenRawL,ev.H_phi_FromGenRawL,ev.H_mass_FromGenRawL,ev.H_pdgId_FromGenRawL,ev.H_genPartIdxMother_FromGenRawL,
                ev.nHDecay_FromGenRawL,ev.H_decaypdgId_FromGenRawL,
                ev.ZPairPlusH_InvMass_FromGenRawL]

                for valItr,valA in enumerate(valAr):
                    if onlyDoSomeHists and valItr >= histsToDo:
                        break
                    #if evCtr <20 and evCtr > 10 and valItr == 0:
                    #    print(valA)
                    #if str(type(valA)) == "<class 'ROOT.vector<int>'>":
                    if "vector" in str(type(valA)):
                        for valEl in valA:
                            histGenRawAr[k][valItr].Fill(valEl)
                    else:
                        histGenRawAr[k][valItr].Fill(valA)
                evCtr += 1


            


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
                
                valAr = [ev.ZOne_pt_FromLHERawL,ev.ZOne_eta_FromLHERawL,ev.ZOne_phi_FromLHERawL,ev.ZOne_mass_FromLHERawL,
                ev.ZTwo_pt_FromLHERawL,ev.ZTwo_eta_FromLHERawL,ev.ZTwo_phi_FromLHERawL,ev.ZTwo_mass_FromLHERawL,
                ev.ZPair_InvMass_FromLHERawL,ev.ZPair_EtaSep_FromLHERawL,
                ev.H_pt_FromLHERawL,ev.H_eta_FromLHERawL,ev.H_phi_FromLHERawL,ev.H_mass_FromLHERawL,ev.ZPairPlusH_InvMass_FromLHERawL,
                ev.JOne_pt_FromLHERawL,ev.JOne_eta_FromLHERawL,ev.JOne_phi_FromLHERawL,ev.JOne_invmass_FromLHERawL,ev.JOne_pdgId_FromLHERawL,
                ev.JTwo_pt_FromLHERawL,ev.JTwo_eta_FromLHERawL,ev.JTwo_phi_FromLHERawL,ev.JTwo_invmass_FromLHERawL,ev.JTwo_pdgId_FromLHERawL,
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
                
                valAr = [ev.ZOne_pt_FromLHESelectedL,ev.ZOne_eta_FromLHESelectedL,ev.ZOne_phi_FromLHESelectedL,ev.ZOne_mass_FromLHESelectedL,
                ev.ZTwo_pt_FromLHESelectedL,ev.ZTwo_eta_FromLHESelectedL,ev.ZTwo_phi_FromLHESelectedL,ev.ZTwo_mass_FromLHESelectedL,
                ev.ZPair_InvMass_FromLHESelectedL,ev.ZPair_EtaSep_FromLHESelectedL,
                ev.H_pt_FromLHESelectedL,ev.H_eta_FromLHESelectedL,ev.H_phi_FromLHESelectedL,ev.H_mass_FromLHESelectedL,ev.ZPairPlusH_InvMass_FromLHESelectedL,
                ev.JOne_pt_FromLHESelectedL,ev.JOne_eta_FromLHESelectedL,ev.JOne_phi_FromLHESelectedL,ev.JOne_invmass_FromLHESelectedL,ev.JOne_pdgId_FromLHESelectedL,
                ev.JTwo_pt_FromLHESelectedL,ev.JTwo_eta_FromLHESelectedL,ev.JTwo_phi_FromLHESelectedL,ev.JTwo_invmass_FromLHESelectedL,ev.JTwo_pdgId_FromLHESelectedL,
                ev.JPair_invmass_FromLHESelectedL,ev.J_etasep_FromLHESelectedL]

                for valItr,valA in enumerate(valAr):
                    if onlyDoSomeHists and valItr >= histsToDo:
                        break
                    #if evCtr <20 and evCtr > 10 and valItr == 0:
                    #    print(valA)
                    histSelectedAr[k][valItr].Fill(valA)
                evCtr += 1



        #####################
        if useTaggedTrees and makeHFJ:
            
            evCtr = 0

            HFJGenTaggedTree = fileA.HFJGenTaggedTree
            histHFJGenTaggedAr.append([])
            canHFJGenTaggedAr.append([])
            
            #Initialize all HFJGenTagged hists
            print("Initializing HFJGenTagged hists")
            for HFJGenTaggedItr, HFJGenTaggedSaveName in enumerate(HFJGenTaggedSaveNameAr):
                if onlyDoSomeHists and HFJGenTaggedItr >= histsToDo:
                    break
                canHFJGenTaggedAr[-1].append(TCanvas("{0}CanHFJGenTagged{1}".format(HFJGenTaggedSaveName,datasetSaveNameAr[k]),"{0}CanHFJGenTagged{1}".format(HFJGenTaggedSaveName,datasetSaveNameAr[k]),3600,2400))
                histHFJGenTaggedAr[-1].append(TH1D("{0}HistHFJGenTagged{1}".format(HFJGenTaggedSaveName,datasetSaveNameAr[k]),"{0}HistHFJGenTagged{1}".format(HFJGenTaggedSaveName,datasetSaveNameAr[k]), HFJGenTaggedBinsAndRangeAr[HFJGenTaggedItr][0], HFJGenTaggedBinsAndRangeAr[HFJGenTaggedItr][1], HFJGenTaggedBinsAndRangeAr[HFJGenTaggedItr][2]))
            print("Looping over events")
            #LOOP OVER EVENTS IN FILE k
            for j,ev in enumerate(HFJGenTaggedTree):
                if breakEvEarly and evCtr >= breakEvAt:
                    break
                if evCtr % 1000 == 0:
                    print("ev:",evCtr)
                
                valAr = [ev.HFJ_pt_FromTaggedGenMatchL,ev.HFJ_eta_FromTaggedGenMatchL,ev.HFJ_phi_FromTaggedGenMatchL,ev.HFJ_mass_FromTaggedGenMatchL,ev.HFJ_dRFromFJ_FromTaggedGenMatchL,
                ev.nHFJDecay_FromTaggedGenMatchL,ev.HFJ_decaypdgId_FromTaggedGenMatchL]

                for valItr,valA in enumerate(valAr):
                    if onlyDoSomeHists and valItr >= histsToDo:
                        break
                    #if evCtr <20 and evCtr > 10 and valItr == 0:
                    #    print(valA)
                    #if str(type(valA)) == "<class 'ROOT.vector<int>'>":
                    if "vector" in str(type(valA)):
                        for valEl in valA:
                            #print(valEl)
                            histHFJGenTaggedAr[k][valItr].Fill(valEl)
                    else:
                        histHFJGenTaggedAr[k][valItr].Fill(valA)
                evCtr += 1

            evCtr = 0

        if makeZFJ:

            ZFJGenTaggedTree = fileA.ZFJGenTaggedTree
            histZFJGenTaggedAr.append([])
            canZFJGenTaggedAr.append([])
            
            #Initialize all ZFJGenTagged hists
            print("Initializing ZFJGenTagged hists")
            for ZFJGenTaggedItr, ZFJGenTaggedSaveName in enumerate(ZFJGenTaggedSaveNameAr):
                if onlyDoSomeHists and ZFJGenTaggedItr >= histsToDo:
                    break
                canZFJGenTaggedAr[-1].append(TCanvas("{0}CanZFJGenTagged{1}".format(ZFJGenTaggedSaveName,datasetSaveNameAr[k]),"{0}CanZFJGenTagged{1}".format(ZFJGenTaggedSaveName,datasetSaveNameAr[k]),3600,2400))
                histZFJGenTaggedAr[-1].append(TH1D("{0}HistZFJGenTagged{1}".format(ZFJGenTaggedSaveName,datasetSaveNameAr[k]),"{0}HistZFJGenTagged{1}".format(ZFJGenTaggedSaveName,datasetSaveNameAr[k]), ZFJGenTaggedBinsAndRangeAr[ZFJGenTaggedItr][0], ZFJGenTaggedBinsAndRangeAr[ZFJGenTaggedItr][1], ZFJGenTaggedBinsAndRangeAr[ZFJGenTaggedItr][2]))
            print("Looping over events")
            #LOOP OVER EVENTS IN FILE k
            for j,ev in enumerate(ZFJGenTaggedTree):
                if breakEvEarly and evCtr >= breakEvAt:
                    break
                if evCtr % 1000 == 0:
                    print("ev:",evCtr)
                
                valAr = [ev.ZFJLead_pt_FromTaggedGenMatchL,ev.ZFJLead_eta_FromTaggedGenMatchL,ev.ZFJLead_phi_FromTaggedGenMatchL,ev.ZFJLead_mass_FromTaggedGenMatchL,ev.ZFJLead_dRFromFJ_FromTaggedGenMatchL,
                ev.nZFJLeadDecay_FromTaggedGenMatchL,ev.ZFJLead_decaypdgId_FromTaggedGenMatchL,
                ev.ZFJTrailing_pt_FromTaggedGenMatchL,ev.ZFJTrailing_eta_FromTaggedGenMatchL,ev.ZFJTrailing_phi_FromTaggedGenMatchL,ev.ZFJTrailing_mass_FromTaggedGenMatchL,ev.ZFJTrailing_dRFromFJ_FromTaggedGenMatchL,
                ev.nZFJTrailingDecay_FromTaggedGenMatchL,ev.ZFJTrailing_decaypdgId_FromTaggedGenMatchL,
                ev.ZFJPair_InvMass_FromTaggedGenMatchL,ev.ZFJPair_EtaSep_FromTaggedGenMatchL]

                for valItr,valA in enumerate(valAr):
                    if onlyDoSomeHists and valItr >= histsToDo:
                        break
                    #if evCtr <20 and evCtr > 10 and valItr == 0:
                    #    print(valA)
                    #if str(type(valA)) == "<class 'ROOT.vector<int>'>":
                    if "vector" in str(type(valA)):
                        for valEl in valA:
                            histZFJGenTaggedAr[k][valItr].Fill(valEl)
                    else:
                        histZFJGenTaggedAr[k][valItr].Fill(valA)
                evCtr += 1

        if useTaggedTrees and makeZHFJ:


            evCtr = 0

            ZHFJGenTaggedTree = fileA.ZHFJGenTaggedTree
            histZHFJGenTaggedAr.append([])
            canZHFJGenTaggedAr.append([])
            
            #Initialize all ZHFJGenTagged hists
            print("Initializing ZHFJGenTagged hists")
            for ZHFJGenTaggedItr, ZHFJGenTaggedSaveName in enumerate(ZHFJGenTaggedSaveNameAr):
                if onlyDoSomeHists and ZHFJGenTaggedItr >= histsToDo:
                    break
                canZHFJGenTaggedAr[-1].append(TCanvas("{0}CanZHFJGenTagged{1}".format(ZHFJGenTaggedSaveName,datasetSaveNameAr[k]),"{0}CanZHFJGenTagged{1}".format(ZHFJGenTaggedSaveName,datasetSaveNameAr[k]),3600,2400))
                histZHFJGenTaggedAr[-1].append(TH1D("{0}HistZHFJGenTagged{1}".format(ZHFJGenTaggedSaveName,datasetSaveNameAr[k]),"{0}HistZHFJGenTagged{1}".format(ZHFJGenTaggedSaveName,datasetSaveNameAr[k]), ZHFJGenTaggedBinsAndRangeAr[ZHFJGenTaggedItr][0], ZHFJGenTaggedBinsAndRangeAr[ZHFJGenTaggedItr][1], ZHFJGenTaggedBinsAndRangeAr[ZHFJGenTaggedItr][2]))
            print("Looping over events")
            #LOOP OVER EVENTS IN FILE k
            for j,ev in enumerate(ZHFJGenTaggedTree):
                if breakEvEarly and evCtr >= breakEvAt:
                    break
                if evCtr % 1000 == 0:
                    print("ev:",evCtr)
                
                valAr = [ev.ZHFJ_ZPairPlusHInvMass_FromTaggedGenMatchL]

                for valItr,valA in enumerate(valAr):
                    if onlyDoSomeHists and valItr >= histsToDo:
                        break
                    #if evCtr <20 and evCtr > 10 and valItr == 0:
                    #    print(valA)
                    histZHFJGenTaggedAr[k][valItr].Fill(valA)
                evCtr += 1

        if useTaggedTrees and makeZHJ:
            evCtr = 0

            ZHJGenTaggedTree = fileA.ZHJGenTaggedTree
            histZHJGenTaggedAr.append([])
            canZHJGenTaggedAr.append([])
            
            #Initialize all ZHJGenTagged hists
            print("Initializing ZHJGenTagged hists")
            for ZHJGenTaggedItr, ZHJGenTaggedSaveName in enumerate(ZHJGenTaggedSaveNameAr):
                if onlyDoSomeHists and ZHJGenTaggedItr >= histsToDo:
                    break
                canZHJGenTaggedAr[-1].append(TCanvas("{0}CanZHJGenTagged{1}".format(ZHJGenTaggedSaveName,datasetSaveNameAr[k]),"{0}CanZHJGenTagged{1}".format(ZHJGenTaggedSaveName,datasetSaveNameAr[k]),3600,2400))
                histZHJGenTaggedAr[-1].append(TH1D("{0}HistZHJGenTagged{1}".format(ZHJGenTaggedSaveName,datasetSaveNameAr[k]),"{0}HistZHJGenTagged{1}".format(ZHJGenTaggedSaveName,datasetSaveNameAr[k]), ZHJGenTaggedBinsAndRangeAr[ZHJGenTaggedItr][0], ZHJGenTaggedBinsAndRangeAr[ZHJGenTaggedItr][1], ZHJGenTaggedBinsAndRangeAr[ZHJGenTaggedItr][2]))
            print("Looping over events")
            #LOOP OVER EVENTS IN FILE k
            for j,ev in enumerate(ZHJGenTaggedTree):
                if breakEvEarly and evCtr >= breakEvAt:
                    break
                if evCtr % 1000 == 0:
                    print("ev:",evCtr)
                
                valAr = [ev.ZHJ_ZPairPlusHInvMass_FromTaggedGenMatchL]

                for valItr,valA in enumerate(valAr):
                    if onlyDoSomeHists and valItr >= histsToDo:
                        break
                    #if evCtr <20 and evCtr > 10 and valItr == 0:
                    #    print(valA)
                    histZHJGenTaggedAr[k][valItr].Fill(valA)
                evCtr += 1


        if useTaggedTrees and makeZJ:
            evCtr = 0

            ZJGenTaggedTree = fileA.ZJGenTaggedTree
            histZJGenTaggedAr.append([])
            canZJGenTaggedAr.append([])
            
            #Initialize all ZJGenTagged hists
            print("Initializing ZJGenTagged hists")
            for ZJGenTaggedItr, ZJGenTaggedSaveName in enumerate(ZJGenTaggedSaveNameAr):
                if onlyDoSomeHists and ZJGenTaggedItr >= histsToDo:
                    break
                canZJGenTaggedAr[-1].append(TCanvas("{0}CanZJGenTagged{1}".format(ZJGenTaggedSaveName,datasetSaveNameAr[k]),"{0}CanZJGenTagged{1}".format(ZJGenTaggedSaveName,datasetSaveNameAr[k]),3600,2400))
                histZJGenTaggedAr[-1].append(TH1D("{0}HistZJGenTagged{1}".format(ZJGenTaggedSaveName,datasetSaveNameAr[k]),"{0}HistZJGenTagged{1}".format(ZJGenTaggedSaveName,datasetSaveNameAr[k]), ZJGenTaggedBinsAndRangeAr[ZJGenTaggedItr][0], ZJGenTaggedBinsAndRangeAr[ZJGenTaggedItr][1], ZJGenTaggedBinsAndRangeAr[ZJGenTaggedItr][2]))
            print("Looping over events")
            #LOOP OVER EVENTS IN FILE k
            for j,ev in enumerate(ZJGenTaggedTree):
                if breakEvEarly and evCtr >= breakEvAt:
                    break
                if evCtr % 1000 == 0:
                    print("ev:",evCtr)
                
                valAr = [ev.ZJLead_pt_FromTaggedGenMatchL,ev.ZJLead_eta_FromTaggedGenMatchL,ev.ZJLead_phi_FromTaggedGenMatchL,ev.ZJLead_mass_FromTaggedGenMatchL,ev.ZJLead_dRFromJ_FromTaggedGenMatchL,
                ev.nZJLeadDecay_FromTaggedGenMatchL,ev.ZJLead_decaypdgId_FromTaggedGenMatchL,
                ev.ZJTrailing_pt_FromTaggedGenMatchL,ev.ZJTrailing_eta_FromTaggedGenMatchL,ev.ZJTrailing_phi_FromTaggedGenMatchL,ev.ZJTrailing_mass_FromTaggedGenMatchL,ev.ZJTrailing_dRFromJ_FromTaggedGenMatchL,
                ev.nZJTrailingDecay_FromTaggedGenMatchL,ev.ZJTrailing_decaypdgId_FromTaggedGenMatchL,
                ev.ZJPair_InvMass_FromTaggedGenMatchL,ev.ZJPair_EtaSep_FromTaggedGenMatchL]

                for valItr,valA in enumerate(valAr):
                    if onlyDoSomeHists and valItr >= histsToDo:
                        break
                    #if evCtr <20 and evCtr > 10 and valItr == 0:
                    #    print(valA)
                    #if str(type(valA)) == "<class 'ROOT.vector<int>'>":
                    if "vector" in str(type(valA)):
                        for valEl in valA:
                            histZJGenTaggedAr[k][valItr].Fill(valEl)
                    else:
                        histZJGenTaggedAr[k][valItr].Fill(valA)
                evCtr += 1


            
        if useTaggedTrees and makeGenRaw:
            evCtr = 0
            GenRawTaggedTree = fileA.GenRawTaggedTree
            histGenRawTaggedAr.append([])
            canGenRawTaggedAr.append([])
            
            #Initialize all GenRawTagged hists
            print("Initializing GenRawTagged hists")
            for GenRawTaggedItr, GenRawTaggedSaveName in enumerate(GenRawTaggedSaveNameAr):
                if onlyDoSomeHists and GenRawTaggedItr >= histsToDo:
                    break
                canGenRawTaggedAr[-1].append(TCanvas("{0}CanGenRawTagged{1}".format(GenRawTaggedSaveName,datasetSaveNameAr[k]),"{0}CanGenRawTagged{1}".format(GenRawTaggedSaveName,datasetSaveNameAr[k]),3600,2400))
                histGenRawTaggedAr[-1].append(TH1D("{0}HistGenRawTagged{1}".format(GenRawTaggedSaveName,datasetSaveNameAr[k]),"{0}HistGenRawTagged{1}".format(GenRawTaggedSaveName,datasetSaveNameAr[k]), GenRawTaggedBinsAndRangeAr[GenRawTaggedItr][0], GenRawTaggedBinsAndRangeAr[GenRawTaggedItr][1], GenRawTaggedBinsAndRangeAr[GenRawTaggedItr][2]))
            print("Looping over events")
            #LOOP OVER EVENTS IN FILE k
            for j,ev in enumerate(GenRawTaggedTree):
                if breakEvEarly and evCtr >= breakEvAt:
                    break
                if evCtr % 1000 == 0:
                    print("ev:",evCtr)
                
                valAr = [ev.ZOne_pt_FromTaggedGenRawL,ev.ZOne_eta_FromTaggedGenRawL,ev.ZOne_phi_FromTaggedGenRawL,ev.ZOne_mass_FromTaggedGenRawL,ev.ZOne_pdgId_FromTaggedGenRawL,ev.ZOne_genPartIdxMother_FromTaggedGenRawL,
                ev.nZOneDecay_FromTaggedGenRawL,ev.ZOne_decaypdgId_FromTaggedGenRawL,
                ev.ZTwo_pt_FromTaggedGenRawL,ev.ZTwo_eta_FromTaggedGenRawL,ev.ZTwo_phi_FromTaggedGenRawL,ev.ZTwo_mass_FromTaggedGenRawL,ev.ZTwo_pdgId_FromTaggedGenRawL,ev.ZTwo_genPartIdxMother_FromTaggedGenRawL,
                ev.nZTwoDecay_FromTaggedGenRawL,ev.ZTwo_decaypdgId_FromTaggedGenRawL,
                ev.ZPair_InvMass_FromTaggedGenRawL,ev.ZPair_EtaSep_FromTaggedGenRawL,
                ev.H_pt_FromTaggedGenRawL,ev.H_eta_FromTaggedGenRawL,ev.H_phi_FromTaggedGenRawL,ev.H_mass_FromTaggedGenRawL,ev.H_pdgId_FromTaggedGenRawL,ev.H_genPartIdxMother_FromTaggedGenRawL,
                ev.nHDecay_FromTaggedGenRawL,ev.H_decaypdgId_FromTaggedGenRawL,
                ev.ZPairPlusH_InvMass_FromTaggedGenRawL]

                for valItr,valA in enumerate(valAr):
                    if onlyDoSomeHists and valItr >= histsToDo:
                        break
                    #if evCtr <20 and evCtr > 10 and valItr == 0:
                    #    print(valA)
                    #if str(type(valA)) == "<class 'ROOT.vector<int>'>":
                    if "vector" in str(type(valA)):
                        for valEl in valA:
                            histGenRawTaggedAr[k][valItr].Fill(valEl)
                    else:
                        histGenRawTaggedAr[k][valItr].Fill(valA)
                evCtr += 1


            

        if useTaggedTrees and makeRaw:
            evCtr = 0

            RawTaggedTree = fileA.RawTaggedTree
            histRawTaggedAr.append([])
            canRawTaggedAr.append([])
            
            #Initialize all RawTagged hists
            print("Initializing RawTagged hists")
            for RawTaggedItr, RawTaggedSaveName in enumerate(RawTaggedSaveNameAr):
                if onlyDoSomeHists and RawTaggedItr >= histsToDo:
                    break
                canRawTaggedAr[-1].append(TCanvas("{0}CanRawTagged{1}".format(RawTaggedSaveName,datasetSaveNameAr[k]),"{0}CanRawTagged{1}".format(RawTaggedSaveName,datasetSaveNameAr[k]),3600,2400))
                histRawTaggedAr[-1].append(TH1D("{0}HistRawTagged{1}".format(RawTaggedSaveName,datasetSaveNameAr[k]),"{0}HistRawTagged{1}".format(RawTaggedSaveName,datasetSaveNameAr[k]), RawTaggedBinsAndRangeAr[RawTaggedItr][0], RawTaggedBinsAndRangeAr[RawTaggedItr][1], RawTaggedBinsAndRangeAr[RawTaggedItr][2]))
            print("Looping over events")
            #LOOP OVER EVENTS IN FILE k
            for j,ev in enumerate(RawTaggedTree):
                if breakEvEarly and evCtr >= breakEvAt:
                    break
                if evCtr % 1000 == 0:
                    print("ev:",evCtr)
                
                valAr = [ev.ZOne_pt_FromTaggedLHERawL,ev.ZOne_eta_FromTaggedLHERawL,ev.ZOne_phi_FromTaggedLHERawL,ev.ZOne_mass_FromTaggedLHERawL,
                ev.ZTwo_pt_FromTaggedLHERawL,ev.ZTwo_eta_FromTaggedLHERawL,ev.ZTwo_phi_FromTaggedLHERawL,ev.ZTwo_mass_FromTaggedLHERawL,
                ev.ZPair_InvMass_FromTaggedLHERawL,ev.ZPair_EtaSep_FromTaggedLHERawL,
                ev.H_pt_FromTaggedLHERawL,ev.H_eta_FromTaggedLHERawL,ev.H_phi_FromTaggedLHERawL,ev.H_mass_FromTaggedLHERawL,ev.ZPairPlusH_InvMass_FromTaggedLHERawL,
                ev.JOne_pt_FromTaggedLHERawL,ev.JOne_eta_FromTaggedLHERawL,ev.JOne_phi_FromTaggedLHERawL,ev.JOne_invmass_FromTaggedLHERawL,ev.JOne_pdgId_FromTaggedLHERawL,
                ev.JTwo_pt_FromTaggedLHERawL,ev.JTwo_eta_FromTaggedLHERawL,ev.JTwo_phi_FromTaggedLHERawL,ev.JTwo_invmass_FromTaggedLHERawL,ev.JTwo_pdgId_FromTaggedLHERawL,
                ev.JPair_invmass_FromTaggedLHERawL,ev.J_etasep_FromTaggedLHERawL]

                for valItr,valA in enumerate(valAr):
                    if onlyDoSomeHists and valItr >= histsToDo:
                        break
                    #if evCtr <20 and evCtr > 10 and valItr == 0:
                    #    print(valA)
                    histRawTaggedAr[k][valItr].Fill(valA)
                evCtr += 1
    

    
##################END MAIN LOOP##################
print("Finished main loop")


if not onlyLHETree:

    ###############STARTING FA GRAPHS###############
    padAr = []
    legAr = []

    dataName = ""
    for k,fileA in enumerate(fileAr):
            dataName += "_"+datasetSaveNameAr[k]

    if not comparisonPlotsOnly:
        for k,fileA in enumerate(fileAr):
            for FAItr, FASaveName in enumerate(FASaveNameAr):
                if onlyDoSomeHists and FAItr >= histsToDo:
                    break
                canAr[k][FAItr].cd()
                histAr[k][FAItr].Draw("hist")
                if savePathBool:
                    canAr[k][FAItr].SaveAs("./Graphs/General/{0}/{1}{2}.png".format(datasetSaveNameAr[k],FASaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
                else:
                    canAr[k][FAItr].SaveAs("{0}{1}{2}.png".format(datasetSaveNameAr[k],FASaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))

    for FAItr, FASaveName in enumerate(FASaveNameAr):
        if onlyDoSomeHists and FAItr >= histsToDo:
            break
        setUpLegend(legAr)
        setUpPadsAr(padAr,"{0}Pad".format("FASaveName"))
        #padAr[-1][0].Draw()
        #padAr[-1][0].cd()

    intComparisonAr = []



    backgroundIntSumAr = setHistoElements(colorAr,histAr,normalizeDataTogether,weightsAr,intComparisonAr,FASaveNameAr,onlyDoSomeHists,histsToDo)


    histMaxAr,histMinAr = normalizeHists(histAr,normalizeDataTogether,backgroundIntSumAr,weightsAr,legAr,datasetSaveNameAr,intComparisonAr,FASaveNameAr,onlyDoSomeHists,histsToDo)



    comparisonCanAr = []
    comparisonHistStackAr = []
    for FAItr, FASaveName in enumerate(FASaveNameAr):
        if onlyDoSomeHists and FAItr >= histsToDo:
            break
        comparisonCanAr.append(TCanvas("comparisonCan{0}".format(FASaveName),"comparisonCan{0}".format(FASaveName),3600,2400))
        comparisonHistStackAr.append(THStack("hist{0}Stack".format(FASaveName),FATitleAr[FAItr]))


    #Loop over all hists that went into the THStack to get center and length of error bars for invisible hist

    invHistsAr = []
    drawInvAr = []
    cloneHistAr = []

    setUpInvHists(histAr,cloneHistAr,invHistsAr,FASaveNameAr,intComparisonAr,drawInvAr,FASaveNameAr,onlyDoSomeHists,histsToDo)


    if makeUnstacked:
        comparisonUnstackedCanAr = []
        legUnstackedAr = []
        padUnstackedAr = []
        for FAItr, FASaveName in enumerate(FASaveNameAr):
            if onlyDoSomeHists and FAItr >= histsToDo:
                break
            comparisonUnstackedCanAr.append(TCanvas("comparisonUnstackedCan{0}".format(FASaveName),"comparisonUnstackedCan{0}".format(FASaveName),3600,2400))
            setUpLegend(legUnstackedAr)
            setUpPadsAr(padUnstackedAr,"{0}Pad".format("FAUnstackedSaveName"))

        setUpNonStackedHistAndFoMPlot(comparisonUnstackedCanAr,cloneHistAr,padAr,histMaxAr,histMinAr,normalizeDataTogether,histAr,legAr,dataName,FASaveNameAr,FATitleAr,FAXTitleAr,onlyDoSomeHists,histsToDo,datasetSaveNameAr)



if useLHETree and not onlyTaggedTrees:

    ###############STARTING RAW  GRAPHS###############

    
    normalizeDataTogether = False


    
    dataName = ""
    for k,fileA in enumerate(fileAr):
        if useLHEAr[k]:
            dataName += "_"+datasetSaveNameAr[k]

    if not comparisonPlotsOnly:
        for k,fileA in enumerate(fileAr):
            if useLHEAr[k]:
                for GenRawItr, GenRawSaveName in enumerate(GenRawSaveNameAr):
                    if onlyDoSomeHists and GenRawItr >= histsToDo:
                        break
                    canGenRawAr[k][GenRawItr].cd()
                    histGenRawAr[k][GenRawItr].Draw("hist")
        
                    if savePathBool:
                        canGenRawAr[k][GenRawItr].SaveAs("./Graphs/General/{0}/{1}{2}.png".format(datasetSaveNameAr[k],GenRawSaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
                    else:
                        canGenRawAr[k][GenRawItr].SaveAs("{0}{1}{2}.png".format(datasetSaveNameAr[k],GenRawSaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
    legUnstackedAr = []
    padUnstackedAr = []
    for GenRawItr, GenRawSaveName in enumerate(GenRawSaveNameAr):
        if onlyDoSomeHists and GenRawItr >= histsToDo:
            break
        setUpLegend(legUnstackedAr)
        setUpPadsAr(padUnstackedAr,"{0}Pad".format("GenRawSaveName"))

    intComparisonAr = []



    setHistoElementsForLHETrees(colorAr,histGenRawAr,weightsAr,intComparisonAr,GenRawSaveNameAr,onlyDoSomeHists,histsToDo,useLHEAr)

    histMaxAr = normalizeHistsForLHETrees(histGenRawAr,weightsAr,legUnstackedAr,datasetSaveNameAr,intComparisonAr,GenRawSaveNameAr,onlyDoSomeHists,histsToDo,useLHEAr)

    cloneHistAr = []

    comparisonCanAr = []
    #comparisonHistStackAr = []
    for GenRawItr, GenRawSaveName in enumerate(GenRawSaveNameAr):
        if onlyDoSomeHists and GenRawItr >= histsToDo:
            break
        comparisonCanAr.append(TCanvas("comparisonCan{0}".format(GenRawSaveName),"comparisonCan{0}".format(GenRawSaveName),3600,2400))
        #comparisonHistStackAr.append(THStack("hist{0}Stack".format(GenRawSaveName),GenRawTitleAr[GenRawItr]))
    comparisonUnstackedCanAr = []

    for GenRawItr, GenRawSaveName in enumerate(GenRawSaveNameAr):
        if onlyDoSomeHists and GenRawItr >= histsToDo:
            break
        comparisonUnstackedCanAr.append(TCanvas("comparisonUnstackedCan{0}".format(GenRawSaveName),"comparisonUnstackedCan{0}".format(GenRawSaveName),3600,2400))

    setUpNonStackedHistAndFoMPlotForLHETrees(comparisonUnstackedCanAr,cloneHistAr,padUnstackedAr,histMaxAr,histGenRawAr,legUnstackedAr,dataName,GenRawSaveNameAr,GenRawTitleAr,GenRawXTitleAr,onlyDoSomeHists,histsToDo,useLHEAr,datasetSaveNameAr)



    ###############STARTING RAW LHE GRAPHS###############

    normalizeDataTogether = False


    dataName = ""
    for k,fileA in enumerate(fileAr):
        if useLHEAr[k]:
            dataName += "_"+datasetSaveNameAr[k]

    if not comparisonPlotsOnly:
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



    setHistoElementsForLHETrees(colorAr,histRawAr,weightsAr,intComparisonAr,RawSaveNameAr,onlyDoSomeHists,histsToDo,useLHEAr)

    histMaxAr = normalizeHistsForLHETrees(histRawAr,weightsAr,legUnstackedAr,datasetSaveNameAr,intComparisonAr,RawSaveNameAr,onlyDoSomeHists,histsToDo,useLHEAr)

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

    setUpNonStackedHistAndFoMPlotForLHETrees(comparisonUnstackedCanAr,cloneHistAr,padUnstackedAr,histMaxAr,histRawAr,legUnstackedAr,dataName,RawSaveNameAr,RawTitleAr,RawXTitleAr,onlyDoSomeHists,histsToDo,useLHEAr,datasetSaveNameAr)



    ###############STARTING SELECTED LHE GRAPHS###############

    
    normalizeDataTogether = False


    
    dataName = ""
    for k,fileA in enumerate(fileAr):
        if useLHEAr[k]:
            dataName += "_"+datasetSaveNameAr[k]

    if not comparisonPlotsOnly:
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



    setHistoElementsForLHETrees(colorAr,histSelectedAr,weightsAr,intComparisonAr,SelectedSaveNameAr,onlyDoSomeHists,histsToDo,useLHEAr)

    histMaxAr = normalizeHistsForLHETrees(histSelectedAr,weightsAr,legUnstackedAr,datasetSaveNameAr,intComparisonAr,SelectedSaveNameAr,onlyDoSomeHists,histsToDo,useLHEAr)

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

    setUpNonStackedHistAndFoMPlotForLHETrees(comparisonUnstackedCanAr,cloneHistAr,padUnstackedAr,histMaxAr,histSelectedAr,legUnstackedAr,dataName,SelectedSaveNameAr,SelectedTitleAr,SelectedXTitleAr,onlyDoSomeHists,histsToDo,useLHEAr,datasetSaveNameAr)




    ###############STARTING HFJGen GEN MATCHING GRAPHS###############

    
    normalizeDataTogether = False


    
    dataName = ""
    for k,fileA in enumerate(fileAr):
        if useLHEAr[k]:
            dataName += "_"+datasetSaveNameAr[k]

    if not comparisonPlotsOnly:
        for k,fileA in enumerate(fileAr):
            if useLHEAr[k]:
                for HFJGenItr, HFJGenSaveName in enumerate(HFJGenSaveNameAr):
                    if onlyDoSomeHists and HFJGenItr >= histsToDo:
                        break
                    canHFJGenAr[k][HFJGenItr].cd()
                    histHFJGenAr[k][HFJGenItr].Draw("hist")
        
                    if savePathBool:
                        canHFJGenAr[k][HFJGenItr].SaveAs("./Graphs/General/{0}/{1}{2}.png".format(datasetSaveNameAr[k],HFJGenSaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
                    else:
                        canHFJGenAr[k][HFJGenItr].SaveAs("{0}{1}{2}.png".format(datasetSaveNameAr[k],HFJGenSaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
    legUnstackedAr = []
    padUnstackedAr = []
    for HFJGenItr, HFJGenSaveName in enumerate(HFJGenSaveNameAr):
        if onlyDoSomeHists and HFJGenItr >= histsToDo:
            break
        setUpLegend(legUnstackedAr)
        setUpPadsAr(padUnstackedAr,"{0}Pad".format("HFJGenSaveName"))

    intComparisonAr = []



    setHistoElementsForLHETrees(colorAr,histHFJGenAr,weightsAr,intComparisonAr,HFJGenSaveNameAr,onlyDoSomeHists,histsToDo,useLHEAr)

    histMaxAr = normalizeHistsForLHETrees(histHFJGenAr,weightsAr,legUnstackedAr,datasetSaveNameAr,intComparisonAr,HFJGenSaveNameAr,onlyDoSomeHists,histsToDo,useLHEAr)

    cloneHistAr = []

    comparisonCanAr = []
    #comparisonHistStackAr = []
    for HFJGenItr, HFJGenSaveName in enumerate(HFJGenSaveNameAr):
        if onlyDoSomeHists and HFJGenItr >= histsToDo:
            break
        comparisonCanAr.append(TCanvas("comparisonCan{0}".format(HFJGenSaveName),"comparisonCan{0}".format(HFJGenSaveName),3600,2400))
        #comparisonHistStackAr.append(THStack("hist{0}Stack".format(HFJGenSaveName),HFJGenTitleAr[HFJGenItr]))
    comparisonUnstackedCanAr = []

    for HFJGenItr, HFJGenSaveName in enumerate(HFJGenSaveNameAr):
        if onlyDoSomeHists and HFJGenItr >= histsToDo:
            break
        comparisonUnstackedCanAr.append(TCanvas("comparisonUnstackedCan{0}".format(HFJGenSaveName),"comparisonUnstackedCan{0}".format(HFJGenSaveName),3600,2400))

    setUpNonStackedHistAndFoMPlotForLHETrees(comparisonUnstackedCanAr,cloneHistAr,padUnstackedAr,histMaxAr,histHFJGenAr,legUnstackedAr,dataName,HFJGenSaveNameAr,HFJGenTitleAr,HFJGenXTitleAr,onlyDoSomeHists,histsToDo,useLHEAr,datasetSaveNameAr)


    ###############STARTING ZFJGen GEN MATCHING GRAPHS###############

    
    normalizeDataTogether = False


    
    dataName = ""
    for k,fileA in enumerate(fileAr):
        if useLHEAr[k]:
            dataName += "_"+datasetSaveNameAr[k]

    if not comparisonPlotsOnly:
        for k,fileA in enumerate(fileAr):
            if useLHEAr[k]:
                for ZFJGenItr, ZFJGenSaveName in enumerate(ZFJGenSaveNameAr):
                    if onlyDoSomeHists and ZFJGenItr >= histsToDo:
                        break
                    canZFJGenAr[k][ZFJGenItr].cd()
                    histZFJGenAr[k][ZFJGenItr].Draw("hist")
                
                    if savePathBool:
                        canZFJGenAr[k][ZFJGenItr].SaveAs("./Graphs/General/{0}/{1}{2}.png".format(datasetSaveNameAr[k],ZFJGenSaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
                    else:
                        canZFJGenAr[k][ZFJGenItr].SaveAs("{0}{1}{2}.png".format(datasetSaveNameAr[k],ZFJGenSaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
    legUnstackedAr = []
    padUnstackedAr = []
    for ZFJGenItr, ZFJGenSaveName in enumerate(ZFJGenSaveNameAr):
        if onlyDoSomeHists and ZFJGenItr >= histsToDo:
            break
        setUpLegend(legUnstackedAr)
        setUpPadsAr(padUnstackedAr,"{0}Pad".format("ZFJGenSaveName"))

    intComparisonAr = []



    setHistoElementsForLHETrees(colorAr,histZFJGenAr,weightsAr,intComparisonAr,ZFJGenSaveNameAr,onlyDoSomeHists,histsToDo,useLHEAr)

    histMaxAr = normalizeHistsForLHETrees(histZFJGenAr,weightsAr,legUnstackedAr,datasetSaveNameAr,intComparisonAr,ZFJGenSaveNameAr,onlyDoSomeHists,histsToDo,useLHEAr)

    cloneHistAr = []

    comparisonCanAr = []
    #comparisonHistStackAr = []
    for ZFJGenItr, ZFJGenSaveName in enumerate(ZFJGenSaveNameAr):
        if onlyDoSomeHists and ZFJGenItr >= histsToDo:
            break
        comparisonCanAr.append(TCanvas("comparisonCan{0}".format(ZFJGenSaveName),"comparisonCan{0}".format(ZFJGenSaveName),3600,2400))
        #comparisonHistStackAr.append(THStack("hist{0}Stack".format(ZFJGenSaveName),ZFJGenTitleAr[ZFJGenItr]))
    comparisonUnstackedCanAr = []

    for ZFJGenItr, ZFJGenSaveName in enumerate(ZFJGenSaveNameAr):
        if onlyDoSomeHists and ZFJGenItr >= histsToDo:
            break
        comparisonUnstackedCanAr.append(TCanvas("comparisonUnstackedCan{0}".format(ZFJGenSaveName),"comparisonUnstackedCan{0}".format(ZFJGenSaveName),3600,2400))

    setUpNonStackedHistAndFoMPlotForLHETrees(comparisonUnstackedCanAr,cloneHistAr,padUnstackedAr,histMaxAr,histZFJGenAr,legUnstackedAr,dataName,ZFJGenSaveNameAr,ZFJGenTitleAr,ZFJGenXTitleAr,onlyDoSomeHists,histsToDo,useLHEAr,datasetSaveNameAr)

    ###############STARTING ZHFJGen GEN MATCHING GRAPHS###############

    
    normalizeDataTogether = False


    
    dataName = ""
    for k,fileA in enumerate(fileAr):
        if useLHEAr[k]:
            dataName += "_"+datasetSaveNameAr[k]

    if not comparisonPlotsOnly:
        for k,fileA in enumerate(fileAr):
            if useLHEAr[k]:
                for ZHFJGenItr, ZHFJGenSaveName in enumerate(ZHFJGenSaveNameAr):
                    if onlyDoSomeHists and ZHFJGenItr >= histsToDo:
                        break
                    canZHFJGenAr[k][ZHFJGenItr].cd()
                    histZHFJGenAr[k][ZHFJGenItr].Draw("hist")
        
                    if savePathBool:
                        canZHFJGenAr[k][ZHFJGenItr].SaveAs("./Graphs/General/{0}/{1}{2}.png".format(datasetSaveNameAr[k],ZHFJGenSaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
                    else:
                        canZHFJGenAr[k][ZHFJGenItr].SaveAs("{0}{1}{2}.png".format(datasetSaveNameAr[k],ZHFJGenSaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
    legUnstackedAr = []
    padUnstackedAr = []
    for ZHFJGenItr, ZHFJGenSaveName in enumerate(ZHFJGenSaveNameAr):
        if onlyDoSomeHists and ZHFJGenItr >= histsToDo:
            break
        setUpLegend(legUnstackedAr)
        setUpPadsAr(padUnstackedAr,"{0}Pad".format("ZHFJGenSaveName"))

    intComparisonAr = []



    setHistoElementsForLHETrees(colorAr,histZHFJGenAr,weightsAr,intComparisonAr,ZHFJGenSaveNameAr,onlyDoSomeHists,histsToDo,useLHEAr)

    histMaxAr = normalizeHistsForLHETrees(histZHFJGenAr,weightsAr,legUnstackedAr,datasetSaveNameAr,intComparisonAr,ZHFJGenSaveNameAr,onlyDoSomeHists,histsToDo,useLHEAr)

    cloneHistAr = []

    comparisonCanAr = []
    #comparisonHistStackAr = []
    for ZHFJGenItr, ZHFJGenSaveName in enumerate(ZHFJGenSaveNameAr):
        if onlyDoSomeHists and ZHFJGenItr >= histsToDo:
            break
        comparisonCanAr.append(TCanvas("comparisonCan{0}".format(ZHFJGenSaveName),"comparisonCan{0}".format(ZHFJGenSaveName),3600,2400))
        #comparisonHistStackAr.append(THStack("hist{0}Stack".format(ZHFJGenSaveName),ZHFJGenTitleAr[ZHFJGenItr]))
    comparisonUnstackedCanAr = []

    for ZHFJGenItr, ZHFJGenSaveName in enumerate(ZHFJGenSaveNameAr):
        if onlyDoSomeHists and ZHFJGenItr >= histsToDo:
            break
        comparisonUnstackedCanAr.append(TCanvas("comparisonUnstackedCan{0}".format(ZHFJGenSaveName),"comparisonUnstackedCan{0}".format(ZHFJGenSaveName),3600,2400))

    setUpNonStackedHistAndFoMPlotForLHETrees(comparisonUnstackedCanAr,cloneHistAr,padUnstackedAr,histMaxAr,histZHFJGenAr,legUnstackedAr,dataName,ZHFJGenSaveNameAr,ZHFJGenTitleAr,ZHFJGenXTitleAr,onlyDoSomeHists,histsToDo,useLHEAr,datasetSaveNameAr)


    ###############STARTING ZHJGen GEN MATCHING GRAPHS###############

    
    normalizeDataTogether = False


    
    dataName = ""
    for k,fileA in enumerate(fileAr):
        if useLHEAr[k]:
            dataName += "_"+datasetSaveNameAr[k]

    if not comparisonPlotsOnly:
        for k,fileA in enumerate(fileAr):
            if useLHEAr[k]:
                for ZHJGenItr, ZHJGenSaveName in enumerate(ZHJGenSaveNameAr):
                    if onlyDoSomeHists and ZHJGenItr >= histsToDo:
                        break
                    canZHJGenAr[k][ZHJGenItr].cd()
                    histZHJGenAr[k][ZHJGenItr].Draw("hist")

                    if savePathBool:
                        canZHJGenAr[k][ZHJGenItr].SaveAs("./Graphs/General/{0}/{1}{2}.png".format(datasetSaveNameAr[k],ZHJGenSaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
                    else:
                        canZHJGenAr[k][ZHJGenItr].SaveAs("{0}{1}{2}.png".format(datasetSaveNameAr[k],ZHJGenSaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
    legUnstackedAr = []
    padUnstackedAr = []
    for ZHJGenItr, ZHJGenSaveName in enumerate(ZHJGenSaveNameAr):
        if onlyDoSomeHists and ZHJGenItr >= histsToDo:
            break
        setUpLegend(legUnstackedAr)
        setUpPadsAr(padUnstackedAr,"{0}Pad".format("ZHJGenSaveName"))

    intComparisonAr = []



    setHistoElementsForLHETrees(colorAr,histZHJGenAr,weightsAr,intComparisonAr,ZHJGenSaveNameAr,onlyDoSomeHists,histsToDo,useLHEAr)

    histMaxAr = normalizeHistsForLHETrees(histZHJGenAr,weightsAr,legUnstackedAr,datasetSaveNameAr,intComparisonAr,ZHJGenSaveNameAr,onlyDoSomeHists,histsToDo,useLHEAr)

    cloneHistAr = []

    comparisonCanAr = []
    #comparisonHistStackAr = []
    for ZHJGenItr, ZHJGenSaveName in enumerate(ZHJGenSaveNameAr):
        if onlyDoSomeHists and ZHJGenItr >= histsToDo:
            break
        comparisonCanAr.append(TCanvas("comparisonCan{0}".format(ZHJGenSaveName),"comparisonCan{0}".format(ZHJGenSaveName),3600,2400))
        #comparisonHistStackAr.append(THStack("hist{0}Stack".format(ZHJGenSaveName),ZHJGenTitleAr[ZHJGenItr]))
    comparisonUnstackedCanAr = []

    for ZHJGenItr, ZHJGenSaveName in enumerate(ZHJGenSaveNameAr):
        if onlyDoSomeHists and ZHJGenItr >= histsToDo:
            break
        comparisonUnstackedCanAr.append(TCanvas("comparisonUnstackedCan{0}".format(ZHJGenSaveName),"comparisonUnstackedCan{0}".format(ZHJGenSaveName),3600,2400))

    setUpNonStackedHistAndFoMPlotForLHETrees(comparisonUnstackedCanAr,cloneHistAr,padUnstackedAr,histMaxAr,histZHJGenAr,legUnstackedAr,dataName,ZHJGenSaveNameAr,ZHJGenTitleAr,ZHJGenXTitleAr,onlyDoSomeHists,histsToDo,useLHEAr,datasetSaveNameAr)


    ###############STARTING ZJGen GEN MATCHING GRAPHS###############

    
    normalizeDataTogether = False


    
    dataName = ""
    for k,fileA in enumerate(fileAr):
        if useLHEAr[k]:
            dataName += "_"+datasetSaveNameAr[k]

    if not comparisonPlotsOnly:
        for k,fileA in enumerate(fileAr):
            if useLHEAr[k]:
                for ZJGenItr, ZJGenSaveName in enumerate(ZJGenSaveNameAr):
                    if onlyDoSomeHists and ZJGenItr >= histsToDo:
                        break
                    canZJGenAr[k][ZJGenItr].cd()
                    histZJGenAr[k][ZJGenItr].Draw("hist")
        
                    if savePathBool:
                        canZJGenAr[k][ZJGenItr].SaveAs("./Graphs/General/{0}/{1}{2}.png".format(datasetSaveNameAr[k],ZJGenSaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
                    else:
                        canZJGenAr[k][ZJGenItr].SaveAs("{0}{1}{2}.png".format(datasetSaveNameAr[k],ZJGenSaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
    legUnstackedAr = []
    padUnstackedAr = []
    for ZJGenItr, ZJGenSaveName in enumerate(ZJGenSaveNameAr):
        if onlyDoSomeHists and ZJGenItr >= histsToDo:
            break
        setUpLegend(legUnstackedAr)
        setUpPadsAr(padUnstackedAr,"{0}Pad".format("ZJGenSaveName"))

    intComparisonAr = []



    setHistoElementsForLHETrees(colorAr,histZJGenAr,weightsAr,intComparisonAr,ZJGenSaveNameAr,onlyDoSomeHists,histsToDo,useLHEAr)

    histMaxAr = normalizeHistsForLHETrees(histZJGenAr,weightsAr,legUnstackedAr,datasetSaveNameAr,intComparisonAr,ZJGenSaveNameAr,onlyDoSomeHists,histsToDo,useLHEAr)

    cloneHistAr = []

    comparisonCanAr = []
    #comparisonHistStackAr = []
    for ZJGenItr, ZJGenSaveName in enumerate(ZJGenSaveNameAr):
        if onlyDoSomeHists and ZJGenItr >= histsToDo:
            break
        comparisonCanAr.append(TCanvas("comparisonCan{0}".format(ZJGenSaveName),"comparisonCan{0}".format(ZJGenSaveName),3600,2400))
        #comparisonHistStackAr.append(THStack("hist{0}Stack".format(ZJGenSaveName),ZJGenTitleAr[ZJGenItr]))
    comparisonUnstackedCanAr = []

    for ZJGenItr, ZJGenSaveName in enumerate(ZJGenSaveNameAr):
        if onlyDoSomeHists and ZJGenItr >= histsToDo:
            break
        comparisonUnstackedCanAr.append(TCanvas("comparisonUnstackedCan{0}".format(ZJGenSaveName),"comparisonUnstackedCan{0}".format(ZJGenSaveName),3600,2400))

    setUpNonStackedHistAndFoMPlotForLHETrees(comparisonUnstackedCanAr,cloneHistAr,padUnstackedAr,histMaxAr,histZJGenAr,legUnstackedAr,dataName,ZJGenSaveNameAr,ZJGenTitleAr,ZJGenXTitleAr,onlyDoSomeHists,histsToDo,useLHEAr,datasetSaveNameAr)





###########################
if useTaggedTrees and makeGenRaw:
    ###############STARTING GEN RAW  GRAPHS###############

    
    normalizeDataTogether = False


    
    dataName = ""
    for k,fileA in enumerate(fileAr):
        if useLHEAr[k]:
            dataName += "_"+datasetSaveNameAr[k]

    if not comparisonPlotsOnly:
        for k,fileA in enumerate(fileAr):
            if useLHEAr[k]:
                for GenRawTaggedItr, GenRawTaggedSaveName in enumerate(GenRawTaggedSaveNameAr):
                    if onlyDoSomeHists and GenRawTaggedItr >= histsToDo:
                        break
                    canGenRawTaggedAr[k][GenRawTaggedItr].cd()
                    histGenRawTaggedAr[k][GenRawTaggedItr].Draw("hist")
        
                    if savePathBool:
                        canGenRawTaggedAr[k][GenRawTaggedItr].SaveAs("./Graphs/General/{0}/{1}{2}.png".format(datasetSaveNameAr[k],GenRawTaggedSaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
                    else:
                        canGenRawTaggedAr[k][GenRawTaggedItr].SaveAs("{0}{1}{2}.png".format(datasetSaveNameAr[k],GenRawTaggedSaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
    legUnstackedAr = []
    padUnstackedAr = []
    for GenRawTaggedItr, GenRawTaggedSaveName in enumerate(GenRawTaggedSaveNameAr):
        if onlyDoSomeHists and GenRawTaggedItr >= histsToDo:
            break
        setUpLegend(legUnstackedAr)
        setUpPadsAr(padUnstackedAr,"{0}Pad".format("GenRawTaggedSaveName"))

    intComparisonAr = []



    setHistoElementsForLHETrees(colorAr,histGenRawTaggedAr,weightsAr,intComparisonAr,GenRawTaggedSaveNameAr,onlyDoSomeHists,histsToDo,useLHEAr)

    histMaxAr = normalizeHistsForLHETrees(histGenRawTaggedAr,weightsAr,legUnstackedAr,datasetSaveNameAr,intComparisonAr,GenRawTaggedSaveNameAr,onlyDoSomeHists,histsToDo,useLHEAr)

    cloneHistAr = []

    comparisonCanAr = []
    #comparisonHistStackAr = []
    for GenRawTaggedItr, GenRawTaggedSaveName in enumerate(GenRawTaggedSaveNameAr):
        if onlyDoSomeHists and GenRawTaggedItr >= histsToDo:
            break
        comparisonCanAr.append(TCanvas("comparisonCan{0}".format(GenRawTaggedSaveName),"comparisonCan{0}".format(GenRawTaggedSaveName),3600,2400))
        #comparisonHistStackAr.append(THStack("hist{0}Stack".format(GenRawTaggedSaveName),GenRawTaggedTitleAr[GenRawTaggedItr]))
    comparisonUnstackedCanAr = []

    for GenRawTaggedItr, GenRawTaggedSaveName in enumerate(GenRawTaggedSaveNameAr):
        if onlyDoSomeHists and GenRawTaggedItr >= histsToDo:
            break
        comparisonUnstackedCanAr.append(TCanvas("comparisonUnstackedCan{0}".format(GenRawTaggedSaveName),"comparisonUnstackedCan{0}".format(GenRawTaggedSaveName),3600,2400))

    setUpNonStackedHistAndFoMPlotForLHETrees(comparisonUnstackedCanAr,cloneHistAr,padUnstackedAr,histMaxAr,histGenRawTaggedAr,legUnstackedAr,dataName,GenRawTaggedSaveNameAr,GenRawTaggedTitleAr,GenRawTaggedXTitleAr,onlyDoSomeHists,histsToDo,useLHEAr,datasetSaveNameAr)


if useTaggedTrees and makeRaw:
    ###############STARTING RAW LHE GRAPHS###############

    
    normalizeDataTogether = False


    
    dataName = ""
    for k,fileA in enumerate(fileAr):
        if useLHEAr[k]:
            dataName += "_"+datasetSaveNameAr[k]

    if not comparisonPlotsOnly:
        for k,fileA in enumerate(fileAr):
            if useLHEAr[k]:
                for RawTaggedItr, RawTaggedSaveName in enumerate(RawTaggedSaveNameAr):
                    if onlyDoSomeHists and RawTaggedItr >= histsToDo:
                        break
                    canRawTaggedAr[k][RawTaggedItr].cd()
                    histRawTaggedAr[k][RawTaggedItr].Draw("hist")
        
                    if savePathBool:
                        canRawTaggedAr[k][RawTaggedItr].SaveAs("./Graphs/General/{0}/{1}{2}.png".format(datasetSaveNameAr[k],RawTaggedSaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
                    else:
                        canRawTaggedAr[k][RawTaggedItr].SaveAs("{0}{1}{2}.png".format(datasetSaveNameAr[k],RawTaggedSaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
    legUnstackedAr = []
    padUnstackedAr = []
    for RawTaggedItr, RawTaggedSaveName in enumerate(RawTaggedSaveNameAr):
        if onlyDoSomeHists and RawTaggedItr >= histsToDo:
            break
        setUpLegend(legUnstackedAr)
        setUpPadsAr(padUnstackedAr,"{0}Pad".format("RawTaggedSaveName"))

    intComparisonAr = []



    setHistoElementsForLHETrees(colorAr,histRawTaggedAr,weightsAr,intComparisonAr,RawTaggedSaveNameAr,onlyDoSomeHists,histsToDo,useLHEAr)

    histMaxAr = normalizeHistsForLHETrees(histRawTaggedAr,weightsAr,legUnstackedAr,datasetSaveNameAr,intComparisonAr,RawTaggedSaveNameAr,onlyDoSomeHists,histsToDo,useLHEAr)

    cloneHistAr = []

    comparisonCanAr = []
    #comparisonHistStackAr = []
    for RawTaggedItr, RawTaggedSaveName in enumerate(RawTaggedSaveNameAr):
        if onlyDoSomeHists and RawTaggedItr >= histsToDo:
            break
        comparisonCanAr.append(TCanvas("comparisonCan{0}".format(RawTaggedSaveName),"comparisonCan{0}".format(RawTaggedSaveName),3600,2400))
        #comparisonHistStackAr.append(THStack("hist{0}Stack".format(RawTaggedSaveName),RawTaggedTitleAr[RawTaggedItr]))
    comparisonUnstackedCanAr = []

    for RawTaggedItr, RawTaggedSaveName in enumerate(RawTaggedSaveNameAr):
        if onlyDoSomeHists and RawTaggedItr >= histsToDo:
            break
        comparisonUnstackedCanAr.append(TCanvas("comparisonUnstackedCan{0}".format(RawTaggedSaveName),"comparisonUnstackedCan{0}".format(RawTaggedSaveName),3600,2400))

    setUpNonStackedHistAndFoMPlotForLHETrees(comparisonUnstackedCanAr,cloneHistAr,padUnstackedAr,histMaxAr,histRawTaggedAr,legUnstackedAr,dataName,RawTaggedSaveNameAr,RawTaggedTitleAr,RawTaggedXTitleAr,onlyDoSomeHists,histsToDo,useLHEAr,datasetSaveNameAr)


if useTaggedTrees and makeHFJ:
    ###############STARTING HFJGenTagged GEN MATCHING GRAPHS###############

    
    normalizeDataTogether = False


    
    dataName = ""
    for k,fileA in enumerate(fileAr):
        if useLHEAr[k]:
            dataName += "_"+datasetSaveNameAr[k]

    if not comparisonPlotsOnly:
        for k,fileA in enumerate(fileAr):
            if useLHEAr[k]:
                for HFJGenTaggedItr, HFJGenTaggedSaveName in enumerate(HFJGenTaggedSaveNameAr):
                    if onlyDoSomeHists and HFJGenTaggedItr >= histsToDo:
                        break
                    canHFJGenTaggedAr[k][HFJGenTaggedItr].cd()
                    histHFJGenTaggedAr[k][HFJGenTaggedItr].Draw("hist")
        
                    if savePathBool:
                        canHFJGenTaggedAr[k][HFJGenTaggedItr].SaveAs("./Graphs/General/{0}/{1}{2}.png".format(datasetSaveNameAr[k],HFJGenTaggedSaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
                    else:
                        canHFJGenTaggedAr[k][HFJGenTaggedItr].SaveAs("{0}{1}{2}.png".format(datasetSaveNameAr[k],HFJGenTaggedSaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
    legUnstackedAr = []
    padUnstackedAr = []
    for HFJGenTaggedItr, HFJGenTaggedSaveName in enumerate(HFJGenTaggedSaveNameAr):
        if onlyDoSomeHists and HFJGenTaggedItr >= histsToDo:
            break
        setUpLegend(legUnstackedAr)
        setUpPadsAr(padUnstackedAr,"{0}Pad".format("HFJGenTaggedSaveName"))

    intComparisonAr = []



    setHistoElementsForLHETrees(colorAr,histHFJGenTaggedAr,weightsAr,intComparisonAr,HFJGenTaggedSaveNameAr,onlyDoSomeHists,histsToDo,useLHEAr)

    histMaxAr = normalizeHistsForLHETrees(histHFJGenTaggedAr,weightsAr,legUnstackedAr,datasetSaveNameAr,intComparisonAr,HFJGenTaggedSaveNameAr,onlyDoSomeHists,histsToDo,useLHEAr)

    cloneHistAr = []

    comparisonCanAr = []
    #comparisonHistStackAr = []
    for HFJGenTaggedItr, HFJGenTaggedSaveName in enumerate(HFJGenTaggedSaveNameAr):
        if onlyDoSomeHists and HFJGenTaggedItr >= histsToDo:
            break
        comparisonCanAr.append(TCanvas("comparisonCan{0}".format(HFJGenTaggedSaveName),"comparisonCan{0}".format(HFJGenTaggedSaveName),3600,2400))
        #comparisonHistStackAr.append(THStack("hist{0}Stack".format(HFJGenTaggedSaveName),HFJGenTaggedTitleAr[HFJGenTaggedItr]))
    comparisonUnstackedCanAr = []

    for HFJGenTaggedItr, HFJGenTaggedSaveName in enumerate(HFJGenTaggedSaveNameAr):
        if onlyDoSomeHists and HFJGenTaggedItr >= histsToDo:
            break
        comparisonUnstackedCanAr.append(TCanvas("comparisonUnstackedCan{0}".format(HFJGenTaggedSaveName),"comparisonUnstackedCan{0}".format(HFJGenTaggedSaveName),3600,2400))

    setUpNonStackedHistAndFoMPlotForLHETrees(comparisonUnstackedCanAr,cloneHistAr,padUnstackedAr,histMaxAr,histHFJGenTaggedAr,legUnstackedAr,dataName,HFJGenTaggedSaveNameAr,HFJGenTaggedTitleAr,HFJGenTaggedXTitleAr,onlyDoSomeHists,histsToDo,useLHEAr,datasetSaveNameAr)

if useTaggedTrees and makeZFJ:
    ###############STARTING ZFJGenTagged GEN MATCHING GRAPHS###############

    
    normalizeDataTogether = False


    
    dataName = ""
    for k,fileA in enumerate(fileAr):
        if useLHEAr[k]:
            dataName += "_"+datasetSaveNameAr[k]

    if not comparisonPlotsOnly:
        for k,fileA in enumerate(fileAr):
            if useLHEAr[k]:
                for ZFJGenTaggedItr, ZFJGenTaggedSaveName in enumerate(ZFJGenTaggedSaveNameAr):
                    if onlyDoSomeHists and ZFJGenTaggedItr >= histsToDo:
                        break
                    canZFJGenTaggedAr[k][ZFJGenTaggedItr].cd()
                    histZFJGenTaggedAr[k][ZFJGenTaggedItr].Draw("hist")
                
                    if savePathBool:
                        canZFJGenTaggedAr[k][ZFJGenTaggedItr].SaveAs("./Graphs/General/{0}/{1}{2}.png".format(datasetSaveNameAr[k],ZFJGenTaggedSaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
                    else:
                        canZFJGenTaggedAr[k][ZFJGenTaggedItr].SaveAs("{0}{1}{2}.png".format(datasetSaveNameAr[k],ZFJGenTaggedSaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
    legUnstackedAr = []
    padUnstackedAr = []
    for ZFJGenTaggedItr, ZFJGenTaggedSaveName in enumerate(ZFJGenTaggedSaveNameAr):
        if onlyDoSomeHists and ZFJGenTaggedItr >= histsToDo:
            break
        setUpLegend(legUnstackedAr)
        setUpPadsAr(padUnstackedAr,"{0}Pad".format("ZFJGenTaggedSaveName"))

    intComparisonAr = []



    setHistoElementsForLHETrees(colorAr,histZFJGenTaggedAr,weightsAr,intComparisonAr,ZFJGenTaggedSaveNameAr,onlyDoSomeHists,histsToDo,useLHEAr)

    histMaxAr = normalizeHistsForLHETrees(histZFJGenTaggedAr,weightsAr,legUnstackedAr,datasetSaveNameAr,intComparisonAr,ZFJGenTaggedSaveNameAr,onlyDoSomeHists,histsToDo,useLHEAr)

    cloneHistAr = []

    comparisonCanAr = []
    #comparisonHistStackAr = []
    for ZFJGenTaggedItr, ZFJGenTaggedSaveName in enumerate(ZFJGenTaggedSaveNameAr):
        if onlyDoSomeHists and ZFJGenTaggedItr >= histsToDo:
            break
        comparisonCanAr.append(TCanvas("comparisonCan{0}".format(ZFJGenTaggedSaveName),"comparisonCan{0}".format(ZFJGenTaggedSaveName),3600,2400))
        #comparisonHistStackAr.append(THStack("hist{0}Stack".format(ZFJGenTaggedSaveName),ZFJGenTaggedTitleAr[ZFJGenTaggedItr]))
    comparisonUnstackedCanAr = []

    for ZFJGenTaggedItr, ZFJGenTaggedSaveName in enumerate(ZFJGenTaggedSaveNameAr):
        if onlyDoSomeHists and ZFJGenTaggedItr >= histsToDo:
            break
        comparisonUnstackedCanAr.append(TCanvas("comparisonUnstackedCan{0}".format(ZFJGenTaggedSaveName),"comparisonUnstackedCan{0}".format(ZFJGenTaggedSaveName),3600,2400))

    setUpNonStackedHistAndFoMPlotForLHETrees(comparisonUnstackedCanAr,cloneHistAr,padUnstackedAr,histMaxAr,histZFJGenTaggedAr,legUnstackedAr,dataName,ZFJGenTaggedSaveNameAr,ZFJGenTaggedTitleAr,ZFJGenTaggedXTitleAr,onlyDoSomeHists,histsToDo,useLHEAr,datasetSaveNameAr)

if useTaggedTrees and makeZHFJ:
    ###############STARTING ZHFJGenTagged GEN MATCHING GRAPHS###############

    
    normalizeDataTogether = False


    
    dataName = ""
    for k,fileA in enumerate(fileAr):
        if useLHEAr[k]:
            dataName += "_"+datasetSaveNameAr[k]

    if not comparisonPlotsOnly:
        for k,fileA in enumerate(fileAr):
            if useLHEAr[k]:
                for ZHFJGenTaggedItr, ZHFJGenTaggedSaveName in enumerate(ZHFJGenTaggedSaveNameAr):
                    if onlyDoSomeHists and ZHFJGenTaggedItr >= histsToDo:
                        break
                    canZHFJGenTaggedAr[k][ZHFJGenTaggedItr].cd()
                    histZHFJGenTaggedAr[k][ZHFJGenTaggedItr].Draw("hist")
        
                    if savePathBool:
                        canZHFJGenTaggedAr[k][ZHFJGenTaggedItr].SaveAs("./Graphs/General/{0}/{1}{2}.png".format(datasetSaveNameAr[k],ZHFJGenTaggedSaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
                    else:
                        canZHFJGenTaggedAr[k][ZHFJGenTaggedItr].SaveAs("{0}{1}{2}.png".format(datasetSaveNameAr[k],ZHFJGenTaggedSaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
    legUnstackedAr = []
    padUnstackedAr = []
    for ZHFJGenTaggedItr, ZHFJGenTaggedSaveName in enumerate(ZHFJGenTaggedSaveNameAr):
        if onlyDoSomeHists and ZHFJGenTaggedItr >= histsToDo:
            break
        setUpLegend(legUnstackedAr)
        setUpPadsAr(padUnstackedAr,"{0}Pad".format("ZHFJGenTaggedSaveName"))

    intComparisonAr = []



    setHistoElementsForLHETrees(colorAr,histZHFJGenTaggedAr,weightsAr,intComparisonAr,ZHFJGenTaggedSaveNameAr,onlyDoSomeHists,histsToDo,useLHEAr)

    histMaxAr = normalizeHistsForLHETrees(histZHFJGenTaggedAr,weightsAr,legUnstackedAr,datasetSaveNameAr,intComparisonAr,ZHFJGenTaggedSaveNameAr,onlyDoSomeHists,histsToDo,useLHEAr)

    cloneHistAr = []

    comparisonCanAr = []
    #comparisonHistStackAr = []
    for ZHFJGenTaggedItr, ZHFJGenTaggedSaveName in enumerate(ZHFJGenTaggedSaveNameAr):
        if onlyDoSomeHists and ZHFJGenTaggedItr >= histsToDo:
            break
        comparisonCanAr.append(TCanvas("comparisonCan{0}".format(ZHFJGenTaggedSaveName),"comparisonCan{0}".format(ZHFJGenTaggedSaveName),3600,2400))
        #comparisonHistStackAr.append(THStack("hist{0}Stack".format(ZHFJGenTaggedSaveName),ZHFJGenTaggedTitleAr[ZHFJGenTaggedItr]))
    comparisonUnstackedCanAr = []

    for ZHFJGenTaggedItr, ZHFJGenTaggedSaveName in enumerate(ZHFJGenTaggedSaveNameAr):
        if onlyDoSomeHists and ZHFJGenTaggedItr >= histsToDo:
            break
        comparisonUnstackedCanAr.append(TCanvas("comparisonUnstackedCan{0}".format(ZHFJGenTaggedSaveName),"comparisonUnstackedCan{0}".format(ZHFJGenTaggedSaveName),3600,2400))

    setUpNonStackedHistAndFoMPlotForLHETrees(comparisonUnstackedCanAr,cloneHistAr,padUnstackedAr,histMaxAr,histZHFJGenTaggedAr,legUnstackedAr,dataName,ZHFJGenTaggedSaveNameAr,ZHFJGenTaggedTitleAr,ZHFJGenTaggedXTitleAr,onlyDoSomeHists,histsToDo,useLHEAr,datasetSaveNameAr)

if useTaggedTrees and makeZHJ:
    ###############STARTING ZHJGenTagged GEN MATCHING GRAPHS###############

    
    normalizeDataTogether = False


    
    dataName = ""
    for k,fileA in enumerate(fileAr):
        if useLHEAr[k]:
            dataName += "_"+datasetSaveNameAr[k]

    if not comparisonPlotsOnly:
        for k,fileA in enumerate(fileAr):
            if useLHEAr[k]:
                for ZHJGenTaggedItr, ZHJGenTaggedSaveName in enumerate(ZHJGenTaggedSaveNameAr):
                    if onlyDoSomeHists and ZHJGenTaggedItr >= histsToDo:
                        break
                    canZHJGenTaggedAr[k][ZHJGenTaggedItr].cd()
                    histZHJGenTaggedAr[k][ZHJGenTaggedItr].Draw("hist")

                    if savePathBool:
                        canZHJGenTaggedAr[k][ZHJGenTaggedItr].SaveAs("./Graphs/General/{0}/{1}{2}.png".format(datasetSaveNameAr[k],ZHJGenTaggedSaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
                    else:
                        canZHJGenTaggedAr[k][ZHJGenTaggedItr].SaveAs("{0}{1}{2}.png".format(datasetSaveNameAr[k],ZHJGenTaggedSaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
    legUnstackedAr = []
    padUnstackedAr = []
    for ZHJGenTaggedItr, ZHJGenTaggedSaveName in enumerate(ZHJGenTaggedSaveNameAr):
        if onlyDoSomeHists and ZHJGenTaggedItr >= histsToDo:
            break
        setUpLegend(legUnstackedAr)
        setUpPadsAr(padUnstackedAr,"{0}Pad".format("ZHJGenTaggedSaveName"))

    intComparisonAr = []



    setHistoElementsForLHETrees(colorAr,histZHJGenTaggedAr,weightsAr,intComparisonAr,ZHJGenTaggedSaveNameAr,onlyDoSomeHists,histsToDo,useLHEAr)

    histMaxAr = normalizeHistsForLHETrees(histZHJGenTaggedAr,weightsAr,legUnstackedAr,datasetSaveNameAr,intComparisonAr,ZHJGenTaggedSaveNameAr,onlyDoSomeHists,histsToDo,useLHEAr)

    cloneHistAr = []

    comparisonCanAr = []
    #comparisonHistStackAr = []
    for ZHJGenTaggedItr, ZHJGenTaggedSaveName in enumerate(ZHJGenTaggedSaveNameAr):
        if onlyDoSomeHists and ZHJGenTaggedItr >= histsToDo:
            break
        comparisonCanAr.append(TCanvas("comparisonCan{0}".format(ZHJGenTaggedSaveName),"comparisonCan{0}".format(ZHJGenTaggedSaveName),3600,2400))
        #comparisonHistStackAr.append(THStack("hist{0}Stack".format(ZHJGenTaggedSaveName),ZHJGenTaggedTitleAr[ZHJGenTaggedItr]))
    comparisonUnstackedCanAr = []

    for ZHJGenTaggedItr, ZHJGenTaggedSaveName in enumerate(ZHJGenTaggedSaveNameAr):
        if onlyDoSomeHists and ZHJGenTaggedItr >= histsToDo:
            break
        comparisonUnstackedCanAr.append(TCanvas("comparisonUnstackedCan{0}".format(ZHJGenTaggedSaveName),"comparisonUnstackedCan{0}".format(ZHJGenTaggedSaveName),3600,2400))

    setUpNonStackedHistAndFoMPlotForLHETrees(comparisonUnstackedCanAr,cloneHistAr,padUnstackedAr,histMaxAr,histZHJGenTaggedAr,legUnstackedAr,dataName,ZHJGenTaggedSaveNameAr,ZHJGenTaggedTitleAr,ZHJGenTaggedXTitleAr,onlyDoSomeHists,histsToDo,useLHEAr,datasetSaveNameAr)


if useTaggedTrees and makeZJ:
    ###############STARTING ZJGenTagged GEN MATCHING GRAPHS###############

    
    normalizeDataTogether = False


    
    dataName = ""
    for k,fileA in enumerate(fileAr):
        if useLHEAr[k]:
            dataName += "_"+datasetSaveNameAr[k]

    if not comparisonPlotsOnly:
        for k,fileA in enumerate(fileAr):
            if useLHEAr[k]:
                for ZJGenTaggedItr, ZJGenTaggedSaveName in enumerate(ZJGenTaggedSaveNameAr):
                    if onlyDoSomeHists and ZJGenTaggedItr >= histsToDo:
                        break
                    canZJGenTaggedAr[k][ZJGenTaggedItr].cd()
                    histZJGenTaggedAr[k][ZJGenTaggedItr].Draw("hist")
        
                    if savePathBool:
                        canZJGenTaggedAr[k][ZJGenTaggedItr].SaveAs("./Graphs/General/{0}/{1}{2}.png".format(datasetSaveNameAr[k],ZJGenTaggedSaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
                    else:
                        canZJGenTaggedAr[k][ZJGenTaggedItr].SaveAs("{0}{1}{2}.png".format(datasetSaveNameAr[k],ZJGenTaggedSaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
    legUnstackedAr = []
    padUnstackedAr = []
    for ZJGenTaggedItr, ZJGenTaggedSaveName in enumerate(ZJGenTaggedSaveNameAr):
        if onlyDoSomeHists and ZJGenTaggedItr >= histsToDo:
            break
        setUpLegend(legUnstackedAr)
        setUpPadsAr(padUnstackedAr,"{0}Pad".format("ZJGenTaggedSaveName"))

    intComparisonAr = []



    setHistoElementsForLHETrees(colorAr,histZJGenTaggedAr,weightsAr,intComparisonAr,ZJGenTaggedSaveNameAr,onlyDoSomeHists,histsToDo,useLHEAr)

    histMaxAr = normalizeHistsForLHETrees(histZJGenTaggedAr,weightsAr,legUnstackedAr,datasetSaveNameAr,intComparisonAr,ZJGenTaggedSaveNameAr,onlyDoSomeHists,histsToDo,useLHEAr)

    cloneHistAr = []

    comparisonCanAr = []
    #comparisonHistStackAr = []
    for ZJGenTaggedItr, ZJGenTaggedSaveName in enumerate(ZJGenTaggedSaveNameAr):
        if onlyDoSomeHists and ZJGenTaggedItr >= histsToDo:
            break
        comparisonCanAr.append(TCanvas("comparisonCan{0}".format(ZJGenTaggedSaveName),"comparisonCan{0}".format(ZJGenTaggedSaveName),3600,2400))
        #comparisonHistStackAr.append(THStack("hist{0}Stack".format(ZJGenTaggedSaveName),ZJGenTaggedTitleAr[ZJGenTaggedItr]))
    comparisonUnstackedCanAr = []

    for ZJGenTaggedItr, ZJGenTaggedSaveName in enumerate(ZJGenTaggedSaveNameAr):
        if onlyDoSomeHists and ZJGenTaggedItr >= histsToDo:
            break
        comparisonUnstackedCanAr.append(TCanvas("comparisonUnstackedCan{0}".format(ZJGenTaggedSaveName),"comparisonUnstackedCan{0}".format(ZJGenTaggedSaveName),3600,2400))

    setUpNonStackedHistAndFoMPlotForLHETrees(comparisonUnstackedCanAr,cloneHistAr,padUnstackedAr,histMaxAr,histZJGenTaggedAr,legUnstackedAr,dataName,ZJGenTaggedSaveNameAr,ZJGenTaggedTitleAr,ZJGenTaggedXTitleAr,onlyDoSomeHists,histsToDo,useLHEAr,datasetSaveNameAr)


