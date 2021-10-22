from ROOT import TFile, TChain, gDirectory, TApplication, TMath, Math, TMinuit, TROOT, TSystem, TVector2, TObject
# You probably also want to import TH1D and TCanvas,
# unless you're not making any histograms.
from ROOT import TH1F, TCanvas, TF1, TGraph, TGraphErrors, TLegend, TLine, TPaveText, TStyle
from ROOT import TH2D, TH2F
from math import sqrt,pi
from fileLists import MGEFTAr
from fileLists import MGSMAr
from AnalyzeNanoAODHiggsJets_Variables import *

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
    saveName = "EFT"
    
    for fileName in MGEFTAr:
        fileAr.append("/scratch365/dlutton/NanoAODFiles/pphzzjjQCD0SMHLOOP0NPE1NPcHWE1QEDE5/"+fileName)
elif MGSM:
    saveName = "SM"
    
    for fileName in MGSMAr:
        fileAr.append("/scratch365/dlutton/NanoAODFiles/pphzzjjQCD0SMHLOOP0QEDE5NPE0/"+fileName)
elif ttHToBBBackground:
    #saveName = "ttHToBB"
    crossSection = 0.5071*0.582

    saveName = "ttHToBB"
    
    isBackground = True
    for fileName in ttHToBBBackgroundAr:
        fileAr.append(fileName)
elif ttZJetsBackground:
    #saveName = "ttZJets"
    
    crossSection = 0.5407
    saveName = "ttZJets"
    isBackground = True
    for fileName in ttZJetsBackgroundAr:
        fileAr.append(fileName)
elif DYBackground:
    #saveName = "DY"
    
    crossSection = 5364
    saveName = "DY"

    isBackground = True
    for fileName in DYBackgroundAr:
        fileAr.append(fileName)
elif QCDPT170to300Background:
    #saveName = "QCDPT170to300"
    
    crossSection = 103300.0

    saveName = "QCDPT170to300"
    
    isBackground = True
    for fileName in QCDPT170to300BackgroundAr:
        fileAr.append(fileName)
elif QCDPT300to470Background:
    #saveName = "QCDPT300to470"
    
    crossSection = 6826.0

    saveName = "QCDPT300to470"
    
    isBackground = True
    for fileName in QCDPT300to470BackgroundAr:
        fileAr.append(fileName)
elif QCDPT470to600Background:
    #saveName = "QCDPT470to600"
    
    crossSection = 552.6
    
    saveName = "QCDPT470to600"

    isBackground = True
    for fileName in QCDPT470to600BackgroundAr:
        fileAr.append(fileName)
elif QCDPT600to800Background:
    #saveName = "QCDPT600to800"
    
    crossSection = 156.6

    saveName = "QCDPT600to800"
    
    isBackground = True
    for fileName in QCDPT600to800BackgroundAr:
        fileAr.append(fileName)
elif QCDPT800to1000Background:
    #saveName = "QCDPT800to1000"
    
    crossSection = 26.32

    saveName = "QCDPT800to1000"
    
    isBackground = True
    for fileName in QCDPT800to1000BackgroundAr:
        fileAr.append(fileName)
elif QCDPT1000to1400Background:
    #saveName = "QCDPT1000to1400"
    
    crossSection = 7.5

    saveName = "QCDPT1000to1400"
    
    isBackground = True
    for fileName in QCDPT1000to1400BackgroundAr:
        fileAr.append(fileName)
elif QCDPT1400to1800Background:
    #saveName = "QCDPT1400to1800"
    
    crossSection = 0.6479

    saveName = "QCDPT1400to1800"
    
    isBackground = True
    for fileName in QCDPT1400to1800BackgroundAr:
        fileAr.append(fileName)
elif QCDPT1800to2400Background:
    #saveName = "QCDPT1800to2400"
    
    crossSection = 0.08715

    saveName = "QCDPT1800to2400"
    
    isBackground = True
    for fileName in QCDPT1800to2400BackgroundAr:
        fileAr.append(fileName)
elif QCDPT2400to3200Background:
    #saveName = "QCDPT2400to3200"
    
    crossSection = 0.005242

    saveName = "QCDPT2400to3200"
    
    isBackground = True
    for fileName in QCDPT2400to3200BackgroundAr:
        fileAr.append(fileName)
elif QCDPT3200toInfBackground:
    #saveName = "QCDPT3200toInf"
    
    crossSection = 0.0001349

    saveName = "QCDPT3200toInf"
    
    isBackground = True
    for fileName in QCDPT3200toInfBackgroundAr:
        fileAr.append(fileName)
elif testRun:
    saveName = "testRun"
    fileAr.append("./unweighted_eventspphzzjjQCD0SMHLOOP0NPE1NPcHWE1QEDE5ResMasAllVer100Ev10080Seed_0p999cHW100GeVIMJetCut_200.root")
elif LaraTest:
    saveName = "LaraTest"
    fileAr.append("/scratch365/dlutton/NanoAODFiles/pp_hwpwmjj_EFT_VBF_chw_09999000_250k.root")
else:
    print("ERROR. NO INPUT DATASET NAME GIVEN")

#Setting up outfile for tree
outFile = TFile("hJetFrom{0}MatchedToGen.root".format(saveName),"recreate")

if isBackground:
    checkChannelSplits = False

passhbbCtr = 0
passChannelCtr = 0
passVBFJets = 0
passFatJets = 0
passGenPart = 0
passFJMatch = 0

#Currently doesn't take into account intermediary particles really. should update at some point
#Can look at old AnalyzeNanoAODFilesWithPyRoot.py script to see how I dealt with this previously
def getInitialMother(ev,genPartInd):
    momFound = False
    motherAr = []
    tmpMomInd = ev.GenPart_genPartIdxMother[genPartInd]
    while not momFound:
        motherAr.append(ev.GenPart_pdgId[tmpMomInd])
        tmpMomInd = ev.GenPart_genPartIdxMother[tmpMomInd]
        if tmpMomInd == -1 or tmpMomInd == 0:
            momFound = True
    return motherAr[-1]



if not isBackground:
    crossSectionAvg = 0
    crossSectionCtr = 0
evRunOver = 0
evCount = 0
evPassCount = 0
print("Going into file loop.","time:",time.time()-startt)
for k,fileName in enumerate(fileAr):
    if endAfter and evCount > NToEnd:
        break
    if debug:
        print("File:    ",fileName)
    #Open the file, get the Events tree
    tmpfile = TFile.Open(fileName)
    outFile.cd()
    mytree = tmpfile.Events
    runTree = tmpfile.Runs
    #Getting the cross section
    #For background it's precalculated
    if not isBackground:
        crossSection = 0
        for i,runEv in enumerate(runTree):
            #if i > 0:
            #    print("uhoh it has two",i,k,fileName)
            crossSection +=runEv.genEventSumw / runEv.genEventCount
        crossSection = crossSection / (i+1)
        crossSectionAvg += crossSection
        crossSectionCtr += 1
    if k % 10 == 0:
        print("Going into event loop for file {0}.".format(k),"time:",time.time()-startt)

    #EvLoop
    for ev in mytree:
        if debug:
            print("-------------------------")
            print(evCount+1," starting jets loop")
        if endAfter:
            if evCount < NToStart:
                evCount += 1
                continue
            if evCount > NToEnd:
                break
        if evCount % 1000 == 0:
            print("Event: "+str(evCount))
        #Increment event count
        evRunOver += 1
        evCount += 1
        #First check that it passes the hbb tagging
        hbbTag = ev.HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02 or ev.HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2 or ev.HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4
        if not hbbTag:
            continue
        passhbbCtr += 1

        #Now check that it can be sorted into either leptonic, semi-leptonic, or hadronic
        #Leptonic
        doubleElecHLT =  (ev.HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL or ev.HLT_DoubleEle25_CaloIdL_MW or ev.HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ or ev.HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL or  ev.HLT_DiEle27_WPTightCaloOnly_L1DoubleEG or 
           ev.HLT_DoubleEle33_CaloIdL_MW or ev.HLT_DoubleEle25_CaloIdL_MW or ev.HLT_DoubleEle27_CaloIdL_MW or ev.HLT_DoublePhoton70)
            
        doubleMuonHLT =  (ev.HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8 or ev.HLT_TripleMu_10_5_5_DZ or ev.HLT_TripleMu_12_10_5 or ev.HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8 or ev.HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8 or 
           ev.HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass3p8 or ev.HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass8)

        muonEGHLT = (ev.HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL or ev.HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ or ev.HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ or ev.HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ or  # or ev.HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ or ev.HLT_Mu8_DiEle12_CaloIdL_TrackIdL_DZ 
           ev.HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL or ev.HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL)
        
        #Semi-leptonic
        elecHLT = (ev.HLT_Ele32_WPTight_Gsf or ev.HLT_Ele115_CaloIdVT_GsfTrkIdT or ev.HLT_Ele27_WPTight_Gsf or ev.HLT_Ele28_WPTight_Gsf or 
           ev.HLT_Ele35_WPTight_Gsf or ev.HLT_Ele38_WPTight_Gsf or ev.HLT_Ele40_WPTight_Gsf or ev.HLT_Ele32_WPTight_Gsf_L1DoubleEG or ev.HLT_Photon200)

        muonHLT = ev.HLT_IsoMu24 or ev.HLT_IsoMu27 or ev.HLT_IsoMu30 or ev.HLT_Mu50

        lepHLT = elecHLT or muonHLT
        
        #Hadronic
        hadHLT =  (ev.HLT_PFHT1050 or ev.HLT_AK8PFJet500 or ev.HLT_AK8PFJet360_TrimMass30 or ev.HLT_AK8PFHT750_TrimMass50 or ev.HLT_AK8PFJet380_TrimMass30 or
           ev.HLT_AK8PFJet400_TrimMass30 or ev.HLT_AK8PFJet420_TrimMass30 or
           ev.HLT_AK8PFHT800_TrimMass50 or ev.HLT_AK8PFHT850_TrimMass50 or ev.HLT_AK8PFHT900_TrimMass50)

        isLeptonic = doubleElecHLT or doubleMuonHLT or muonEGHLT
        isSemiLeptonic = (elecHLT or muonHLT) and hadHLT
        isHadronic = hadHLT

        if not (isLeptonic or isSemiLeptonic or isHadronic):
            continue

        passChannelCtr += 1

        #First match jets
        nJet           = ev.nJet
        leadJet_1 = 0
        leadJet_2 = 0
        jetLeadPt      = 0
        jetTrailingPt  = 0
        jetLeadVec     = 0
        jetTrailingVec = 0
        jetPairInvMass = 0
        jetLeadPhi     = 0
        jetTrailingPhi = 0
        for jetIndOne in range(nJet-1):
            jetPtOne = ev.Jet_pt[jetIndOne]
            jetIdOne = ev.Jet_jetId[jetIndOne]
            if jetPtOne < jetPTCut or not jetIdOne == 6:
                continue
            for jetIndTwo in range(jetIndOne+1,nJet):
                jetPtTwo = ev.Jet_pt[jetIndTwo]
                jetIdTwo = ev.Jet_jetId[jetIndTwo]
                if jetPtTwo < jetPTCut or not jetIdTwo == 6:
                    continue
                jetEtaOne = ev.Jet_eta[jetIndOne]
                jetEtaTwo = ev.Jet_eta[jetIndTwo]
                if abs(jetEtaOne - jetEtaTwo) < jetEtaDifCut:
                    continue
                
                jetPhiOne = ev.Jet_phi[jetIndOne]
                jetPhiTwo = ev.Jet_phi[jetIndTwo]
                jetMassOne = ev.Jet_mass[jetIndOne]
                jetMassTwo = ev.Jet_mass[jetIndTwo]
                tmpVecOne = Math.PtEtaPhiMVector(jetPtOne, jetEtaOne, jetPhiOne, jetMassOne)
                tmpVecTwo = Math.PtEtaPhiMVector(jetPtTwo, jetEtaTwo, jetPhiTwo, jetMassTwo)
                tmpVecSum = tmpVecOne+tmpVecTwo
                tmpJetPairInvMass = tmpVecSum.M()
                if tmpJetPairInvMass < jetInvMassCut:
                    continue
                if tmpJetPairInvMass > jetPairInvMass:
                    jetPairInvMass = tmpJetPairInvMass
                    if jetPtOne >= jetPtTwo:
                        jetLeadPt = jetPtOne
                        jetLeadEta = jetEtaOne
                        jetLeadPhi = jetPhiOne
                        jetTrailingPt = jetPtTwo
                        jetTrailingEta = jetEtaTwo
                        jetTrailingPhi = jetPhiTwo
                        leadJet_1 = jetIndOne
                        leadJet_2 = jetIndTwo
                    else:
                        jetLeadPt = jetPtTwo
                        jetLeadEta = jetEtaTwo
                        jetLeadPhi = jetPhiTwo
                        jetTrailingPt = jetPtOne
                        jetTrailingEta = jetEtaOne
                        jetTrailingPhi = jetPhiOne
                        leadJet_1 = jetIndTwo
                        leadJet_2 = jetIndOne
        if jetLeadPt == 0:
            continue
        if debug:
            print(" found jet pairs")
            print(evCount+1," selected jet pair")
            print("Lead jet ind    ",leadJet_1)
            print("Trailing jet ind    ",leadJet_2)
            print("Lead jet phi    ",ev.Jet_phi[leadJet_1])
            print("Trailing jet phi    ",ev.Jet_phi[leadJet_2])
            print("Lead jet eta    ",ev.Jet_eta[leadJet_1])
            print("Trailing jet eta    ",ev.Jet_eta[leadJet_2])
        passVBFJets += 1


        #Now fat jets
        nFatJet = ev.nFatJet
        hFatJet_HTag_fromPt = 0
        hFatJet_pt_fromPt = 0
        hFatJet_phi_fromPt = 0
        hFatJet_eta_fromPt = 0
        hFatJet_mass_fromPt = 0
        hFatJet_pt_fromHTag = 0
        hFatJet_phi_fromHTag = 0
        hFatJet_eta_fromHTag = 0
        hFatJet_mass_fromHTag = 0
        hFatJet_HTag_fromHTag = 0
        if debug:
            print("Entering Fat Jets Loop")
        for fatJetInd in range(nFatJet):
            #if ev.FatJet_deepTag_H[fatJetInd] < hFatJetDeepTagCut:
            #    continue
            if debug:
                print(fatJetInd," +++++++++++++++")
                print("Fat jet phi    ", ev.FatJet_phi[fatJetInd])
                print("Fat jet eta    ", ev.FatJet_eta[fatJetInd])
                    
                print("Fat jet pt    ", ev.FatJet_pt[fatJetInd])
                print("Fat jet jetId    ", ev.FatJet_jetId[fatJetInd])
            tmpFatJet_pt = ev.FatJet_pt[fatJetInd]
            if tmpFatJet_pt > hFatJetPTCut:
                tmpFatJet_jetId = ev.FatJet_jetId[fatJetInd]
                if tmpFatJet_jetId == 6:
                    tmpFatJet_eta = ev.FatJet_eta[fatJetInd]
                    tmpFatJet_phi = ev.FatJet_phi[fatJetInd]
                    tmpDROne = calcDeltaR(tmpFatJet_phi,tmpFatJet_eta,jetLeadPhi,jetLeadEta)
                    tmpDRTwo = calcDeltaR(tmpFatJet_phi,tmpFatJet_eta,jetTrailingPhi,jetTrailingEta)
                    if debug:
                        print("Fat jet dROne    ", tmpDROne)
                        print("Fat jet dRTwo    ", tmpDRTwo)
                    if tmpDROne > hFatJetdRCut and tmpDRTwo > hFatJetdRCut:
                        if debug:
                            print("Passed fatjet cuts")
                        tmpFatJet_HTag = ev.FatJet_deepTag_H[fatJetInd]
                        if tmpFatJet_pt > hFatJet_pt_fromPt:
                            hFatJet_HTag_fromPt = tmpFatJet_HTag
                            hFatJet_pt_fromPt = tmpFatJet_pt
                            hFatJet_eta_fromPt = tmpFatJet_eta
                            hFatJet_phi_fromPt = tmpFatJet_phi
                            hFatJet_mass_fromPt = ev.FatJet_mass[fatJetInd]
                        
                        if tmpFatJet_HTag > hFatJet_HTag_fromHTag:
                            hFatJet_HTag_fromHTag = tmpFatJet_HTag
                            hFatJet_pt_fromHTag = tmpFatJet_pt
                            hFatJet_eta_fromHTag = tmpFatJet_eta
                            hFatJet_phi_fromHTag = tmpFatJet_phi
                            hFatJet_mass_fromHTag = ev.FatJet_mass[fatJetInd]
        if hFatJet_pt_fromHTag == 0:
            continue
        if debug:
            print(" found fat jet")
        passFatJets += 1


        #Now gen matching
        nGenPart = ev.nGenPart
        hGenPartDR_fromPt = 999
        hGenPartInd_fromPt = -1
        hGenPartpdgId_fromPt = -1
        hGenPartDR_fromHTag = 999
        hGenPartInd_fromHTag = -1
        hGenPartpdgId_fromHTag = -1
        for genPartInd in range(nGenPart):
            tmpGenPart_phi = ev.GenPart_phi[genPartInd]
            tmpGenPart_eta = ev.GenPart_eta[genPartInd]
            tmpDR_fromPt = calcDeltaR(hFatJet_phi_fromPt,hFatJet_eta_fromPt,tmpGenPart_phi,tmpGenPart_eta)
            if tmpDR_fromPt < hGenPartDR_fromPt:
                hGenPartDR_fromPt = tmpDR_fromPt
                hGenPartInd_fromPt = genPartInd
                hGenPartpdgId_fromPt = ev.GenPart_pdgId[genPartInd]
            tmpDR_fromHTag = calcDeltaR(hFatJet_phi_fromHTag,hFatJet_eta_fromHTag,tmpGenPart_phi,tmpGenPart_eta)
            if tmpDR_fromHTag < hGenPartDR_fromHTag:
                hGenPartDR_fromHTag = tmpDR_fromHTag
                hGenPartInd_fromHTag = genPartInd
                hGenPartpdgId_fromHTag = ev.GenPart_pdgId[genPartInd]
        if (not hGenPartInd_fromPt == -1) and (not hGenPartInd_fromHTag == -1):
            if debug:
                print(" found gen part")
            passGenPart += 1
            
            #Get genPart first mom
            hGenPartFirstMompdgId_fromPt = getInitialMother(ev,hGenPartInd_fromPt)
            hGenPartFirstMompdgId_fromHTag = getInitialMother(ev,hGenPartInd_fromHTag)


            #Now do higgs gen matching with fatjets
            #First get h index
            for LHEInd in range(ev.nLHEPart):
                if ev.LHEPart_pdgId[LHEInd] == 25:
                    hInd = LHEInd
            #Now get FatJets close in dR
            hLHE_phi = ev.LHEPart_phi[hInd]
            hLHE_eta = ev.LHEPart_eta[hInd]
            FJTopPt = 0
            FJTopHTag = 0
            FJTopdR = 999
            FJLHEMatchedInd_fromPt = -1
            FJLHEMatchedInd_fromHTag = -1
            FJLHEMatchedInd_fromdR = -1
            
            for fatJetInd in range(nFatJet):
                tmpFatJet_phi = ev.FatJet_phi[fatJetInd]
                tmpFatJet_eta = ev.FatJet_eta[fatJetInd]
                tmpdR = calcDeltaR(tmpFatJet_phi,tmpFatJet_eta,hLHE_phi,hLHE_eta)
                if tmpdR < 0.4:
                    tmpFJ_pt = ev.FatJet_pt[fatJetInd]
                    tmpFJ_DTH = ev.FatJet_deepTag_H[fatJetInd] 
                    if tmpFJ_pt > FJTopPt:
                        FJTopPt = tmpFJ_pt
                        FJLHEMatchedInd_fromPt = fatJetInd
                    if tmpFJ_DTH > FJTopHTag:
                        FJTopHTag = tmpFJ_DTH
                        FJLHEMatchedInd_fromHTag = fatJetInd
                    
                    if tmpdR < FJTopdR:
                        FJTopdR = tmpdR
                        FJLHEMatchedInd_fromdR = fatJetInd
                    
            if FJLHEMatchedInd_fromPt == -1:
                continue
            passFJMatch += 1
                    


            




            #Fill tree
            nJetL[0] = nJet
            jetLeadPtL[0] = jetLeadPt
            jetTrailingPtL[0] = jetTrailingPt
            jetLeadPhiL[0] = jetLeadPhi
            jetTrailingPhiL[0] = jetTrailingPhi
            jetPairInvMassL[0] = jetPairInvMass
            jetLeadEtaL[0] = jetLeadEta
            jetTrailingEtaL[0] = jetTrailingEta
            #now fat jets
            nFatJetL[0] = nFatJet
            hFatJet_HTag_fromPtL[0] = hFatJet_HTag_fromPt
            hFatJet_pt_fromPtL[0] = hFatJet_pt_fromPt
            hFatJet_phi_fromPtL[0] = hFatJet_phi_fromPt
            hFatJet_eta_fromPtL[0] = hFatJet_eta_fromPt
            hFatJet_mass_fromPtL[0] = hFatJet_mass_fromPt
            hFatJet_pt_fromHTagL[0] = hFatJet_pt_fromHTag
            hFatJet_phi_fromHTagL[0] = hFatJet_phi_fromHTag
            hFatJet_eta_fromHTagL[0] = hFatJet_eta_fromHTag
            hFatJet_mass_fromHTagL[0] = hFatJet_mass_fromHTag
            hFatJet_HTag_fromHTagL[0] = hFatJet_HTag_fromHTag

            #Now matched fat jets
            hFatJet_Matched_HTag_fromPt = ev.FatJet_deepTag_H[FJLHEMatchedInd_fromPt]
            hFatJet_Matched_pt_fromPt = ev.FatJet_pt[FJLHEMatchedInd_fromPt]
            hFatJet_Matched_phi_fromPt = ev.FatJet_phi[FJLHEMatchedInd_fromPt]
            hFatJet_Matched_eta_fromPt = ev.FatJet_eta[FJLHEMatchedInd_fromPt]
            hFatJet_Matched_mass_fromPt = ev.FatJet_mass[FJLHEMatchedInd_fromPt]
            hFatJet_Matched_HTag_fromHTag = ev.FatJet_deepTag_H[FJLHEMatchedInd_fromHTag]
            hFatJet_Matched_pt_fromHTag = ev.FatJet_pt[FJLHEMatchedInd_fromHTag]
            hFatJet_Matched_phi_fromHTag = ev.FatJet_phi[FJLHEMatchedInd_fromHTag]
            hFatJet_Matched_eta_fromHTag = ev.FatJet_eta[FJLHEMatchedInd_fromHTag]
            hFatJet_Matched_mass_fromHTag = ev.FatJet_mass[FJLHEMatchedInd_fromHTag]
            hFatJet_Matched_HTag_fromdR = ev.FatJet_deepTag_H[FJLHEMatchedInd_fromdR]
            hFatJet_Matched_pt_fromdR = ev.FatJet_pt[FJLHEMatchedInd_fromdR]
            hFatJet_Matched_phi_fromdR = ev.FatJet_phi[FJLHEMatchedInd_fromdR]
            hFatJet_Matched_eta_fromdR = ev.FatJet_eta[FJLHEMatchedInd_fromdR]
            hFatJet_Matched_mass_fromdR = ev.FatJet_mass[FJLHEMatchedInd_fromdR]

            hFatJet_Matched_HTag_fromPtL[0] = hFatJet_Matched_HTag_fromPt
            hFatJet_Matched_pt_fromPtL[0] = hFatJet_Matched_pt_fromPt
            hFatJet_Matched_phi_fromPtL[0] = hFatJet_Matched_phi_fromPt
            hFatJet_Matched_eta_fromPtL[0] = hFatJet_Matched_eta_fromPt
            hFatJet_Matched_mass_fromPtL[0] = hFatJet_Matched_mass_fromPt
            hFatJet_Matched_pt_fromHTagL[0] = hFatJet_Matched_pt_fromHTag
            hFatJet_Matched_phi_fromHTagL[0] = hFatJet_Matched_phi_fromHTag
            hFatJet_Matched_eta_fromHTagL[0] = hFatJet_Matched_eta_fromHTag
            hFatJet_Matched_mass_fromHTagL[0] = hFatJet_Matched_mass_fromHTag
            hFatJet_Matched_HTag_fromHTagL[0] = hFatJet_Matched_HTag_fromHTag
            hFatJet_Matched_pt_fromdRL[0] = hFatJet_Matched_pt_fromdR
            hFatJet_Matched_phi_fromdRL[0] = hFatJet_Matched_phi_fromdR
            hFatJet_Matched_eta_fromdRL[0] = hFatJet_Matched_eta_fromdR
            hFatJet_Matched_mass_fromdRL[0] = hFatJet_Matched_mass_fromdR
            hFatJet_Matched_HTag_fromdRL[0] = hFatJet_Matched_HTag_fromdR

            

            #Now GenPart
            #print(nGenPart)

            nGenPartL[0] = nGenPart
            hGenPartDR_fromPtL[0] = hGenPartDR_fromPt
            hGenPartInd_fromPtL[0] = hGenPartInd_fromPt
            hGenPartpdgId_fromPtL[0] = hGenPartpdgId_fromPt
            hGenPartFirstMompdgId_fromPtL[0] = hGenPartFirstMompdgId_fromPt
            hGenPartDR_fromHTagL[0] = hGenPartDR_fromHTag
            hGenPartInd_fromHTagL[0] = hGenPartInd_fromHTag
            hGenPartpdgId_fromHTagL[0] = hGenPartpdgId_fromHTag
            hGenPartFirstMompdgId_fromHTagL[0] = hGenPartFirstMompdgId_fromHTag

            #HLT stuff

            hbbTagL[0] = hbbTag

            doubleElecHLTL[0] = doubleElecHLT
            doubleMuonHLTL[0] = doubleMuonHLT
            muonEGHLTL[0] = muonEGHLT
            elecHLTL[0] = elecHLT
            muonHLTL[0] = muonHLT
            hadHLTL[0] = hadHLT
            isLeptonicL[0] = isLeptonic
            isSemiLeptonicL[0] = isSemiLeptonic
            isHadronicL[0] = isHadronic

            hJetTree.Fill()
            evPassCount += 1






print("Finished file loop.","time:",time.time()-startt)

nEv[0] = evRunOver
nEvPass[0] = evPassCount
evNumTree.Fill()

print("evRunOver:",evRunOver)
print("passes hbb cut:",passhbbCtr)
print("passes channel cut:",passChannelCtr)
print("passes VBF Jet cut:",passVBFJets)
print("passes FatJet cut:",passFatJets)
print("passes GenPart cut:",passGenPart)
print("passes Higgs Fat Jet Gen Matching:",passFJMatch)
print("evPassCount:",evPassCount)

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
hJetTree.Write("",TObject.kOverwrite)




outFile.Close()

        
        
                


                




