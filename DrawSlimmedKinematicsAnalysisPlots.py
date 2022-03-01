import datetime
from ROOT import TFile, TChain, gDirectory, TApplication, TMath, Math, TMinuit, TROOT, TSystem, TTree, TVector2, THStack
# You probably also want to import TH1D and TCanvas,
# unless you're not making any histograms.
from ROOT import TH1F, TH1D, TF1, TGraph, TGraphErrors, TLegend, TLine, TPaveText, TStyle
from ROOT import TH2D, TH2F
from FunctionsForSlimmedKinematicsAnalysisPlots import *

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

if MGC2VEtaDifCut:
    if useTightdRCut:
        fileAr.append(TFile.Open("{0}KinematicsAnalysisC2VEtaDifCutTighterCut.root".format(forCondorStr)))
    else:
        fileAr.append(TFile.Open("{0}KinematicsAnalysisC2VEtaDifCut.root".format(forCondorStr)))
    colorAr.append(1)
    datasetSaveNameAr.append("C2VEtaDifCut")
    
    
    useLHEAr.append(True)

    C2VEtaDifCutXSTree = fileAr[-1].crossSectionTree
    tmpXSAvg = 0
    tmpXSCnt = 0
    for C2VEtaDifCutXS in C2VEtaDifCutXSTree:
        tmpXSAvg += C2VEtaDifCutXS.crossSectionVar
        tmpXSCnt += 1
    tmpXSAvg = tmpXSAvg / tmpXSCnt
    XSAr.append(tmpXSAvg)
    ENTree = fileAr[-1].evNumTree
    evNum = 0
    for ev in ENTree:
        evNum = ev.nEv
    totalEvents.append(evNum)

if SDC2V3MC:
    if useTightdRCut:
        fileAr.append(TFile.Open("{0}KinematicsAnalysisSDC2V3MCTighterCut.root".format(forCondorStr)))
    else:
        fileAr.append(TFile.Open("{0}KinematicsAnalysisSDC2V3MC.root".format(forCondorStr)))
    colorAr.append(4)
    datasetSaveNameAr.append("SDC2V3MC")
    
    
    useLHEAr.append(True)

    SDC2V3MCXSTree = fileAr[-1].crossSectionTree
    tmpXSAvg = 0
    tmpXSCnt = 0
    for SDC2V3MCXS in SDC2V3MCXSTree:
        tmpXSAvg += SDC2V3MCXS.crossSectionVar
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
        fileAr.append(TFile.Open("{0}KinematicsAnalysisOHWTighterCut.root".format(forCondorStr)))
    else:
        fileAr.append(TFile.Open("{0}KinematicsAnalysisOHW.root".format(forCondorStr)))
    colorAr.append(6)
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

if MGSM:
    if useTightdRCut:
        fileAr.append(TFile.Open("{0}KinematicsAnalysisSMTighterCut.root".format(forCondorStr)))
    else:
        fileAr.append(TFile.Open("{0}KinematicsAnalysisSM.root".format(forCondorStr)))
    colorAr.append(7)
    datasetSaveNameAr.append("SM")
    
    
    useLHEAr.append(True)

    SMXSTree = fileAr[-1].crossSectionTree
    tmpXSAvg = 0
    tmpXSCnt = 0
    for SMXS in SMXSTree:
        tmpXSAvg += SMXS.crossSectionVar
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
    colorAr.append(4)
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
    colorAr.append(9)
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
    colorAr.append(2)
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
    colorAr.append(46)
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
    colorAr.append(3)
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
    colorAr.append(8)
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
        if makeFA:
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
            if makeHFJ:
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
            
            if makeGenRaw:
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


                

            if makeRaw:

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



        #####################
        if useTaggedTrees:
            
            

            if makeZFJ:
                evCtr = 0

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

            if makeZHFJ:


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

                
            if makeGenRawHad:
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
                    ev.ZPairPlusH_InvMass_FromTaggedGenRawL,

                    ev.ZLeadDecLead_pt_FromTaggedGenRawL,ev.ZLeadDecLead_eta_FromTaggedGenRawL,ev.ZLeadDecLead_phi_FromTaggedGenRawL,ev.ZLeadDecLead_mass_FromTaggedGenRawL,ev.ZLeadDecLead_pdgId_FromTaggedGenRawL,ev.ZLeadDecLead_genPartIdxMother_FromTaggedGenRawL,

                    ev.ZLeadDecTrailing_pt_FromTaggedGenRawL,ev.ZLeadDecTrailing_eta_FromTaggedGenRawL,ev.ZLeadDecTrailing_phi_FromTaggedGenRawL,ev.ZLeadDecTrailing_mass_FromTaggedGenRawL,ev.ZLeadDecTrailing_pdgId_FromTaggedGenRawL,ev.ZLeadDecTrailing_genPartIdxMother_FromTaggedGenRawL,

                    ev.ZTrailingDecLead_pt_FromTaggedGenRawL,ev.ZTrailingDecLead_eta_FromTaggedGenRawL,ev.ZTrailingDecLead_phi_FromTaggedGenRawL,ev.ZTrailingDecLead_mass_FromTaggedGenRawL,ev.ZTrailingDecLead_pdgId_FromTaggedGenRawL,ev.ZTrailingDecLead_genPartIdxMother_FromTaggedGenRawL,

                    ev.ZTrailingDecTrailing_pt_FromTaggedGenRawL,ev.ZTrailingDecTrailing_eta_FromTaggedGenRawL,ev.ZTrailingDecTrailing_phi_FromTaggedGenRawL,ev.ZTrailingDecTrailing_mass_FromTaggedGenRawL,ev.ZTrailingDecTrailing_pdgId_FromTaggedGenRawL,ev.ZTrailingDecTrailing_genPartIdxMother_FromTaggedGenRawL]

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


                
            evCtr = 0

                
            if makeGenRawSemiLep:
                evCtr = 0
                GenRawSemiLepTaggedTree = fileA.GenRawSemiLepTaggedTree
                histGenRawSemiLepTaggedAr.append([])
                canGenRawSemiLepTaggedAr.append([])
                
                #Initialize all GenRawSemiLepTagged hists
                print("Initializing GenRawSemiLepTagged hists")
                for GenRawSemiLepTaggedItr, GenRawSemiLepTaggedSaveName in enumerate(GenRawSemiLepTaggedSaveNameAr):
                    if onlyDoSomeHists and GenRawSemiLepTaggedItr >= histsToDo:
                        break
                    canGenRawSemiLepTaggedAr[-1].append(TCanvas("{0}CanGenRawSemiLepTagged{1}".format(GenRawSemiLepTaggedSaveName,datasetSaveNameAr[k]),"{0}CanGenRawSemiLepTagged{1}".format(GenRawSemiLepTaggedSaveName,datasetSaveNameAr[k]),3600,2400))
                    histGenRawSemiLepTaggedAr[-1].append(TH1D("{0}HistGenRawSemiLepTagged{1}".format(GenRawSemiLepTaggedSaveName,datasetSaveNameAr[k]),"{0}HistGenRawSemiLepTagged{1}".format(GenRawSemiLepTaggedSaveName,datasetSaveNameAr[k]), GenRawSemiLepTaggedBinsAndRangeAr[GenRawSemiLepTaggedItr][0], GenRawSemiLepTaggedBinsAndRangeAr[GenRawSemiLepTaggedItr][1], GenRawSemiLepTaggedBinsAndRangeAr[GenRawSemiLepTaggedItr][2]))
                print("Looping over events")
                #LOOP OVER EVENTS IN FILE k
                for j,ev in enumerate(GenRawSemiLepTaggedTree):
                    if breakEvEarly and evCtr >= breakEvAt:
                        break
                    if evCtr % 1000 == 0:
                        print("ev:",evCtr)
                    
                    valAr = [ev.ZOne_pt_FromSemiLepTaggedGenRawL,ev.ZOne_eta_FromSemiLepTaggedGenRawL,ev.ZOne_phi_FromSemiLepTaggedGenRawL,ev.ZOne_mass_FromSemiLepTaggedGenRawL,ev.ZOne_pdgId_FromSemiLepTaggedGenRawL,ev.ZOne_genPartIdxMother_FromSemiLepTaggedGenRawL,
                    ev.nZOneDecay_FromSemiLepTaggedGenRawL,ev.ZOne_decaypdgId_FromSemiLepTaggedGenRawL,
                    ev.ZTwo_pt_FromSemiLepTaggedGenRawL,ev.ZTwo_eta_FromSemiLepTaggedGenRawL,ev.ZTwo_phi_FromSemiLepTaggedGenRawL,ev.ZTwo_mass_FromSemiLepTaggedGenRawL,ev.ZTwo_pdgId_FromSemiLepTaggedGenRawL,ev.ZTwo_genPartIdxMother_FromSemiLepTaggedGenRawL,
                    ev.nZTwoDecay_FromSemiLepTaggedGenRawL,ev.ZTwo_decaypdgId_FromSemiLepTaggedGenRawL,
                    ev.ZPair_InvMass_FromSemiLepTaggedGenRawL,ev.ZPair_EtaSep_FromSemiLepTaggedGenRawL,
                    ev.H_pt_FromSemiLepTaggedGenRawL,ev.H_eta_FromSemiLepTaggedGenRawL,ev.H_phi_FromSemiLepTaggedGenRawL,ev.H_mass_FromSemiLepTaggedGenRawL,ev.H_pdgId_FromSemiLepTaggedGenRawL,ev.H_genPartIdxMother_FromSemiLepTaggedGenRawL,
                    ev.nHDecay_FromSemiLepTaggedGenRawL,ev.H_decaypdgId_FromSemiLepTaggedGenRawL,
                    ev.ZPairPlusH_InvMass_FromSemiLepTaggedGenRawL,
                    ev.ZLeadDecLead_pt_FromSemiLepTaggedGenRawL,ev.ZLeadDecLead_eta_FromSemiLepTaggedGenRawL,ev.ZLeadDecLead_phi_FromSemiLepTaggedGenRawL,ev.ZLeadDecLead_mass_FromSemiLepTaggedGenRawL,ev.ZLeadDecLead_pdgId_FromSemiLepTaggedGenRawL,ev.ZLeadDecLead_genPartIdxMother_FromSemiLepTaggedGenRawL,
                    ev.ZLeadDecTrailing_pt_FromSemiLepTaggedGenRawL,ev.ZLeadDecTrailing_eta_FromSemiLepTaggedGenRawL,ev.ZLeadDecTrailing_phi_FromSemiLepTaggedGenRawL,ev.ZLeadDecTrailing_mass_FromSemiLepTaggedGenRawL,ev.ZLeadDecTrailing_pdgId_FromSemiLepTaggedGenRawL,ev.ZLeadDecTrailing_genPartIdxMother_FromSemiLepTaggedGenRawL,
                    ev.ZTrailingDecLead_pt_FromSemiLepTaggedGenRawL,ev.ZTrailingDecLead_eta_FromSemiLepTaggedGenRawL,ev.ZTrailingDecLead_phi_FromSemiLepTaggedGenRawL,ev.ZTrailingDecLead_mass_FromSemiLepTaggedGenRawL,ev.ZTrailingDecLead_pdgId_FromSemiLepTaggedGenRawL,ev.ZTrailingDecLead_genPartIdxMother_FromSemiLepTaggedGenRawL,
                    ev.ZTrailingDecTrailing_pt_FromSemiLepTaggedGenRawL,ev.ZTrailingDecTrailing_eta_FromSemiLepTaggedGenRawL,ev.ZTrailingDecTrailing_phi_FromSemiLepTaggedGenRawL,ev.ZTrailingDecTrailing_mass_FromSemiLepTaggedGenRawL,ev.ZTrailingDecTrailing_pdgId_FromSemiLepTaggedGenRawL,ev.ZTrailingDecTrailing_genPartIdxMother_FromSemiLepTaggedGenRawL]

                    for valItr,valA in enumerate(valAr):
                        if onlyDoSomeHists and valItr >= histsToDo:
                            break
                        #if evCtr <20 and evCtr > 10 and valItr == 0:
                        #    print(valA)
                        #if str(type(valA)) == "<class 'ROOT.vector<int>'>":
                        if "vector" in str(type(valA)):
                            for valEl in valA:
                                histGenRawSemiLepTaggedAr[k][valItr].Fill(valEl)
                        else:
                            histGenRawSemiLepTaggedAr[k][valItr].Fill(valA)
                    evCtr += 1


                


            if makeGenRawLep:
                evCtr = 0
                GenRawLepTaggedTree = fileA.GenRawLepTaggedTree
                histGenRawLepTaggedAr.append([])
                canGenRawLepTaggedAr.append([])
                
                #Initialize all GenRawLepTagged hists
                print("Initializing GenRawLepTagged hists")
                for GenRawLepTaggedItr, GenRawLepTaggedSaveName in enumerate(GenRawLepTaggedSaveNameAr):
                    if onlyDoSomeHists and GenRawLepTaggedItr >= histsToDo:
                        break
                    canGenRawLepTaggedAr[-1].append(TCanvas("{0}CanGenRawLepTagged{1}".format(GenRawLepTaggedSaveName,datasetSaveNameAr[k]),"{0}CanGenRawLepTagged{1}".format(GenRawLepTaggedSaveName,datasetSaveNameAr[k]),3600,2400))
                    histGenRawLepTaggedAr[-1].append(TH1D("{0}HistGenRawLepTagged{1}".format(GenRawLepTaggedSaveName,datasetSaveNameAr[k]),"{0}HistGenRawLepTagged{1}".format(GenRawLepTaggedSaveName,datasetSaveNameAr[k]), GenRawLepTaggedBinsAndRangeAr[GenRawLepTaggedItr][0], GenRawLepTaggedBinsAndRangeAr[GenRawLepTaggedItr][1], GenRawLepTaggedBinsAndRangeAr[GenRawLepTaggedItr][2]))
                print("Looping over events")
                #LOOP OVER EVENTS IN FILE k
                for j,ev in enumerate(GenRawLepTaggedTree):
                    if breakEvEarly and evCtr >= breakEvAt:
                        break
                    if evCtr % 1000 == 0:
                        print("ev:",evCtr)
                    
                    valAr = [ev.ZOne_pt_FromLepTaggedGenRawL,ev.ZOne_eta_FromLepTaggedGenRawL,ev.ZOne_phi_FromLepTaggedGenRawL,ev.ZOne_mass_FromLepTaggedGenRawL,ev.ZOne_pdgId_FromLepTaggedGenRawL,ev.ZOne_genPartIdxMother_FromLepTaggedGenRawL,
                    ev.nZOneDecay_FromLepTaggedGenRawL,ev.ZOne_decaypdgId_FromLepTaggedGenRawL,
                    ev.ZTwo_pt_FromLepTaggedGenRawL,ev.ZTwo_eta_FromLepTaggedGenRawL,ev.ZTwo_phi_FromLepTaggedGenRawL,ev.ZTwo_mass_FromLepTaggedGenRawL,ev.ZTwo_pdgId_FromLepTaggedGenRawL,ev.ZTwo_genPartIdxMother_FromLepTaggedGenRawL,
                    ev.nZTwoDecay_FromLepTaggedGenRawL,ev.ZTwo_decaypdgId_FromLepTaggedGenRawL,
                    ev.ZPair_InvMass_FromLepTaggedGenRawL,ev.ZPair_EtaSep_FromLepTaggedGenRawL,
                    ev.H_pt_FromLepTaggedGenRawL,ev.H_eta_FromLepTaggedGenRawL,ev.H_phi_FromLepTaggedGenRawL,ev.H_mass_FromLepTaggedGenRawL,ev.H_pdgId_FromLepTaggedGenRawL,ev.H_genPartIdxMother_FromLepTaggedGenRawL,
                    ev.nHDecay_FromLepTaggedGenRawL,ev.H_decaypdgId_FromLepTaggedGenRawL,
                    ev.ZPairPlusH_InvMass_FromLepTaggedGenRawL,
                    ev.ZLeadDecLead_pt_FromLepTaggedGenRawL,ev.ZLeadDecLead_eta_FromLepTaggedGenRawL,ev.ZLeadDecLead_phi_FromLepTaggedGenRawL,ev.ZLeadDecLead_mass_FromLepTaggedGenRawL,ev.ZLeadDecLead_pdgId_FromLepTaggedGenRawL,ev.ZLeadDecLead_genPartIdxMother_FromLepTaggedGenRawL,
                    ev.ZLeadDecTrailing_pt_FromLepTaggedGenRawL,ev.ZLeadDecTrailing_eta_FromLepTaggedGenRawL,ev.ZLeadDecTrailing_phi_FromLepTaggedGenRawL,ev.ZLeadDecTrailing_mass_FromLepTaggedGenRawL,ev.ZLeadDecTrailing_pdgId_FromLepTaggedGenRawL,ev.ZLeadDecTrailing_genPartIdxMother_FromLepTaggedGenRawL,
                    ev.ZTrailingDecLead_pt_FromLepTaggedGenRawL,ev.ZTrailingDecLead_eta_FromLepTaggedGenRawL,ev.ZTrailingDecLead_phi_FromLepTaggedGenRawL,ev.ZTrailingDecLead_mass_FromLepTaggedGenRawL,ev.ZTrailingDecLead_pdgId_FromLepTaggedGenRawL,ev.ZTrailingDecLead_genPartIdxMother_FromLepTaggedGenRawL,
                    ev.ZTrailingDecTrailing_pt_FromLepTaggedGenRawL,ev.ZTrailingDecTrailing_eta_FromLepTaggedGenRawL,ev.ZTrailingDecTrailing_phi_FromLepTaggedGenRawL,ev.ZTrailingDecTrailing_mass_FromLepTaggedGenRawL,ev.ZTrailingDecTrailing_pdgId_FromLepTaggedGenRawL,ev.ZTrailingDecTrailing_genPartIdxMother_FromLepTaggedGenRawL]

                    for valItr,valA in enumerate(valAr):
                        if onlyDoSomeHists and valItr >= histsToDo:
                            break
                        #if evCtr <20 and evCtr > 10 and valItr == 0:
                        #    print(valA)
                        #if str(type(valA)) == "<class 'ROOT.vector<int>'>":
                        if "vector" in str(type(valA)):
                            for valEl in valA:
                                histGenRawLepTaggedAr[k][valItr].Fill(valEl)
                        else:
                            histGenRawLepTaggedAr[k][valItr].Fill(valA)
                    evCtr += 1

    
##################END MAIN LOOP##################
print("Finished main loop")


if not onlyLHETree:
    if makeFA:

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



        dataIntSumAr = setHistoElements(colorAr,histAr,normalizeDataTogether,weightsAr,intComparisonAr,FASaveNameAr,onlyDoSomeHists,histsToDo,useFillColorInPlots)


        histMaxAr,histMinAr = normalizeHists(histAr,normalizeDataTogether,dataIntSumAr,weightsAr,legAr,datasetSaveNameAr,intComparisonAr,FASaveNameAr,onlyDoSomeHists,histsToDo)



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
    if makeGenRaw:

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



        setHistoElementsForLHETrees(colorAr,histGenRawAr,weightsAr,intComparisonAr,GenRawSaveNameAr,onlyDoSomeHists,histsToDo,useLHEAr,useFillColorInPlots)

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


    if makeRaw:
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



        setHistoElementsForLHETrees(colorAr,histRawAr,weightsAr,intComparisonAr,RawSaveNameAr,onlyDoSomeHists,histsToDo,useLHEAr,useFillColorInPlots)

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



###########################
if useTaggedTrees:
    if makeGenRawHad:
        ###############STARTING TAGGED GEN RAW  GRAPHS###############

        
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



        setHistoElementsForLHETrees(colorAr,histGenRawTaggedAr,weightsAr,intComparisonAr,GenRawTaggedSaveNameAr,onlyDoSomeHists,histsToDo,useLHEAr,useFillColorInPlots)

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


    if makeZFJ:
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



        setHistoElementsForLHETrees(colorAr,histZFJGenTaggedAr,weightsAr,intComparisonAr,ZFJGenTaggedSaveNameAr,onlyDoSomeHists,histsToDo,useLHEAr,useFillColorInPlots)

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

    if makeZHFJ:
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



        setHistoElementsForLHETrees(colorAr,histZHFJGenTaggedAr,weightsAr,intComparisonAr,ZHFJGenTaggedSaveNameAr,onlyDoSomeHists,histsToDo,useLHEAr,useFillColorInPlots)

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

    if makeGenRawSemiLep:
        ###############STARTING GEN RAW  GRAPHS###############

        
        normalizeDataTogether = False


        
        dataName = ""
        for k,fileA in enumerate(fileAr):
            if useLHEAr[k]:
                dataName += "_"+datasetSaveNameAr[k]

        if not comparisonPlotsOnly:
            for k,fileA in enumerate(fileAr):
                if useLHEAr[k]:
                    for GenRawSemiLepTaggedItr, GenRawSemiLepTaggedSaveName in enumerate(GenRawSemiLepTaggedSaveNameAr):
                        if onlyDoSomeHists and GenRawSemiLepTaggedItr >= histsToDo:
                            break
                        canGenRawSemiLepTaggedAr[k][GenRawSemiLepTaggedItr].cd()
                        histGenRawSemiLepTaggedAr[k][GenRawSemiLepTaggedItr].Draw("hist")
            
                        if savePathBool:
                            canGenRawSemiLepTaggedAr[k][GenRawSemiLepTaggedItr].SaveAs("./Graphs/General/{0}/{1}{2}.png".format(datasetSaveNameAr[k],GenRawSemiLepTaggedSaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
                        else:
                            canGenRawSemiLepTaggedAr[k][GenRawSemiLepTaggedItr].SaveAs("{0}{1}{2}.png".format(datasetSaveNameAr[k],GenRawSemiLepTaggedSaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
        legUnstackedAr = []
        padUnstackedAr = []
        for GenRawSemiLepTaggedItr, GenRawSemiLepTaggedSaveName in enumerate(GenRawSemiLepTaggedSaveNameAr):
            if onlyDoSomeHists and GenRawSemiLepTaggedItr >= histsToDo:
                break
            setUpLegend(legUnstackedAr)
            setUpPadsAr(padUnstackedAr,"{0}Pad".format("GenRawSemiLepTaggedSaveName"))

        intComparisonAr = []



        setHistoElementsForLHETrees(colorAr,histGenRawSemiLepTaggedAr,weightsAr,intComparisonAr,GenRawSemiLepTaggedSaveNameAr,onlyDoSomeHists,histsToDo,useLHEAr,useFillColorInPlots)

        histMaxAr = normalizeHistsForLHETrees(histGenRawSemiLepTaggedAr,weightsAr,legUnstackedAr,datasetSaveNameAr,intComparisonAr,GenRawSemiLepTaggedSaveNameAr,onlyDoSomeHists,histsToDo,useLHEAr)

        cloneHistAr = []

        comparisonCanAr = []
        #comparisonHistStackAr = []
        for GenRawSemiLepTaggedItr, GenRawSemiLepTaggedSaveName in enumerate(GenRawSemiLepTaggedSaveNameAr):
            if onlyDoSomeHists and GenRawSemiLepTaggedItr >= histsToDo:
                break
            comparisonCanAr.append(TCanvas("comparisonCan{0}".format(GenRawSemiLepTaggedSaveName),"comparisonCan{0}".format(GenRawSemiLepTaggedSaveName),3600,2400))
            #comparisonHistStackAr.append(THStack("hist{0}Stack".format(GenRawSemiLepTaggedSaveName),GenRawSemiLepTaggedTitleAr[GenRawSemiLepTaggedItr]))
        comparisonUnstackedCanAr = []

        for GenRawSemiLepTaggedItr, GenRawSemiLepTaggedSaveName in enumerate(GenRawSemiLepTaggedSaveNameAr):
            if onlyDoSomeHists and GenRawSemiLepTaggedItr >= histsToDo:
                break
            comparisonUnstackedCanAr.append(TCanvas("comparisonUnstackedCan{0}".format(GenRawSemiLepTaggedSaveName),"comparisonUnstackedCan{0}".format(GenRawSemiLepTaggedSaveName),3600,2400))

        setUpNonStackedHistAndFoMPlotForLHETrees(comparisonUnstackedCanAr,cloneHistAr,padUnstackedAr,histMaxAr,histGenRawSemiLepTaggedAr,legUnstackedAr,dataName,GenRawSemiLepTaggedSaveNameAr,GenRawSemiLepTaggedTitleAr,GenRawSemiLepTaggedXTitleAr,onlyDoSomeHists,histsToDo,useLHEAr,datasetSaveNameAr)

    if makeGenRawLep:
        ###############STARTING GEN RAW  GRAPHS###############

        
        normalizeDataTogether = False


        
        dataName = ""
        for k,fileA in enumerate(fileAr):
            if useLHEAr[k]:
                dataName += "_"+datasetSaveNameAr[k]

        if not comparisonPlotsOnly:
            for k,fileA in enumerate(fileAr):
                if useLHEAr[k]:
                    for GenRawLepTaggedItr, GenRawLepTaggedSaveName in enumerate(GenRawLepTaggedSaveNameAr):
                        if onlyDoSomeHists and GenRawLepTaggedItr >= histsToDo:
                            break
                        canGenRawLepTaggedAr[k][GenRawLepTaggedItr].cd()
                        histGenRawLepTaggedAr[k][GenRawLepTaggedItr].Draw("hist")
            
                        if savePathBool:
                            canGenRawLepTaggedAr[k][GenRawLepTaggedItr].SaveAs("./Graphs/General/{0}/{1}{2}.png".format(datasetSaveNameAr[k],GenRawLepTaggedSaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
                        else:
                            canGenRawLepTaggedAr[k][GenRawLepTaggedItr].SaveAs("{0}{1}{2}.png".format(datasetSaveNameAr[k],GenRawLepTaggedSaveName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
        legUnstackedAr = []
        padUnstackedAr = []
        for GenRawLepTaggedItr, GenRawLepTaggedSaveName in enumerate(GenRawLepTaggedSaveNameAr):
            if onlyDoSomeHists and GenRawLepTaggedItr >= histsToDo:
                break
            setUpLegend(legUnstackedAr)
            setUpPadsAr(padUnstackedAr,"{0}Pad".format("GenRawLepTaggedSaveName"))

        intComparisonAr = []



        setHistoElementsForLHETrees(colorAr,histGenRawLepTaggedAr,weightsAr,intComparisonAr,GenRawLepTaggedSaveNameAr,onlyDoSomeHists,histsToDo,useLHEAr,useFillColorInPlots)

        histMaxAr = normalizeHistsForLHETrees(histGenRawLepTaggedAr,weightsAr,legUnstackedAr,datasetSaveNameAr,intComparisonAr,GenRawLepTaggedSaveNameAr,onlyDoSomeHists,histsToDo,useLHEAr)

        cloneHistAr = []

        comparisonCanAr = []
        #comparisonHistStackAr = []
        for GenRawLepTaggedItr, GenRawLepTaggedSaveName in enumerate(GenRawLepTaggedSaveNameAr):
            if onlyDoSomeHists and GenRawLepTaggedItr >= histsToDo:
                break
            comparisonCanAr.append(TCanvas("comparisonCan{0}".format(GenRawLepTaggedSaveName),"comparisonCan{0}".format(GenRawLepTaggedSaveName),3600,2400))
            #comparisonHistStackAr.append(THStack("hist{0}Stack".format(GenRawLepTaggedSaveName),GenRawLepTaggedTitleAr[GenRawLepTaggedItr]))
        comparisonUnstackedCanAr = []

        for GenRawLepTaggedItr, GenRawLepTaggedSaveName in enumerate(GenRawLepTaggedSaveNameAr):
            if onlyDoSomeHists and GenRawLepTaggedItr >= histsToDo:
                break
            comparisonUnstackedCanAr.append(TCanvas("comparisonUnstackedCan{0}".format(GenRawLepTaggedSaveName),"comparisonUnstackedCan{0}".format(GenRawLepTaggedSaveName),3600,2400))

        setUpNonStackedHistAndFoMPlotForLHETrees(comparisonUnstackedCanAr,cloneHistAr,padUnstackedAr,histMaxAr,histGenRawLepTaggedAr,legUnstackedAr,dataName,GenRawLepTaggedSaveNameAr,GenRawLepTaggedTitleAr,GenRawLepTaggedXTitleAr,onlyDoSomeHists,histsToDo,useLHEAr,datasetSaveNameAr)
