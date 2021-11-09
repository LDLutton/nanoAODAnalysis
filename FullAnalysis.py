from ROOT import TFile, TChain, gDirectory, TApplication, TMath, Math, TMinuit, TROOT, TSystem, TVector2, TObject
# You probably also want to import TH1D and TCanvas,
# unless you're not making any histograms.
from ROOT import TH1F, TCanvas, TF1, TGraph, TGraphErrors, TLegend, TLine, TPaveText, TStyle
from ROOT import TH2D, TH2F
from math import sqrt,pi
from fileLists import MGEFTAr
from fileLists import MGSMAr
from FullAnalysis_Variables import *
from FullAnalysis_Functions import *

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

print("Doing {0}".format(saveName))
#Setting up outfile for tree
outFile = TFile("FullAnalysis{0}.root".format(saveName),"recreate")

if isBackground:
    checkChannelSplits = False

passhbbCtr = 0
passAnyChannelCtr = 0
passLepChannelCtr = 0
passSemiLepChannelCtr = 0
passHadChannelCtr = 0
passLepAndSemiLepChannelCtr = 0
passLepAndHadChannelCtr = 0
passSemiLepAndHadChannelCtr = 0
passAllChannelCtr = 0
passVBFJets = 0
passFatJets = 0
passGenPart = 0
passFJMatch = 0
passLepCut = 0
passSemiLepCut = 0
passHadCut = 0

tryingLepCtr = 0
tryingSemiLepCtr = 0
tryingHadCtr = 0

passesCutsCtr = 0





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


        passesCutsBool = False
        passedAsLepBool = False
        passedAsSemiLepBool = False
        passedAsHadBool = False
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

        passAnyChannelCtr += 1
        if isLeptonic:
            
            if isSemiLeptonic:
                if isHadronic:
                    passAllChannelCtr += 1
                else:
                    passLepAndSemiLepChannelCtr += 1
            elif isHadronic:
                passLepAndHadChannelCtr += 1
            else:
                passLepChannelCtr += 1
        elif isSemiLeptonic:
            
            if isHadronic:
                passSemiLepAndHadChannelCtr += 1
            else:
                passSemiLepChannelCtr += 1
        elif isHadronic:
            passHadChannelCtr += 1





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


            if isLeptonic:
                tryingLepCtr += 1
                neLep = ev.nElectron
                enoughElecCands = False
                negElecCands = 0
                posElecCands = 0
                totElecCands = 0
                elecCandIndAr = []
                elecCandVecAr = []
                elecCandChargeAr = []
                
                if neLep:
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
                nmLep = ev.nMuon
                if debug:
                    print("--------------------------------------------")
                    print("neLep",neLep)
                    for tmpItr in range(neLep):
                        print("tmpItr",tmpItr,"ev.Electron_pt[tmpItr]",ev.Electron_pt[tmpItr],"ev.Electron_eta[tmpItr]",ev.Electron_eta[tmpItr],"ev.Electron_charge[tmpItr]",ev.Electron_charge[tmpItr])
                if nmLep:
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
                    print("negElecCands",negElecCands,"posElecCands",posElecCands,"totElecCands",totElecCands)
                    print("nmLep",nmLep,"negMuonCands",negMuonCands,"posMuonCands",posMuonCands,"totMuonCands",totMuonCands)
                    print("enoughLepCands",enoughLepCands)
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
                                    tmpPt = Z1LeadPt
                                    if tmpPt > 35:
                                        if abs(ev.Electron_eta[elecCandIndAr[Z1LeadItr]]) < 1.4:
                                            tmpAdd = max(0., ev.Electron_dr03EcalRecHitSumEt[elecCandIndAr[Z1LeadItr]] - 1.)
                                        else:
                                            tmpAdd = ev.Electron_dr03EcalRecHitSumEt[elecCandIndAr[Z1LeadItr]]
                                        tmpIso = ( ev.Electron_dr03TkSumPt[elecCandIndAr[Z1LeadItr]] + tmpAdd + ev.Electron_dr03HcalDepth1TowerSumEt[elecCandIndAr[Z1LeadItr]] ) / ev.Electron_pt[elecCandIndAr[Z1LeadItr]]
                                    else:
                                        tmpIso = ev.Electron_pfRelIso03_all[elecCandIndAr[Z1LeadItr]]
                                    Z1LeadIso = tmpIso
                                    
                                    tmpPt = Z1TrailingPt
                                    if tmpPt > 35:
                                        if abs(ev.Electron_eta[elecCandIndAr[Z1TrailingItr]]) < 1.4:
                                            tmpAdd = max(0., ev.Electron_dr03EcalRecHitSumEt[elecCandIndAr[Z1TrailingItr]] - 1.)
                                        else:
                                            tmpAdd = ev.Electron_dr03EcalRecHitSumEt[elecCandIndAr[Z1TrailingItr]]
                                        tmpIso = ( ev.Electron_dr03TkSumPt[elecCandIndAr[Z1TrailingItr]] + tmpAdd + ev.Electron_dr03HcalDepth1TowerSumEt[elecCandIndAr[Z1LeadItr]] ) / ev.Electron_pt[elecCandIndAr[Z1LeadItr]]
                                    else:
                                        tmpIso = ev.Electron_pfRelIso03_all[elecCandIndAr[Z1TrailingItr]]
                                    Z1TrailingIso = tmpIso
                                else:
                                    Z1LeadIso = ev.Muon_pfRelIso03_all[muonCandIndAr[Z1LeadItr]]
                                    Z1TrailingIso = ev.Muon_pfRelIso03_all[muonCandIndAr[Z1TrailingItr]]
                                    #Z1LeadIso = ev.mIso[muonCandIndAr[Z1LeadItr]]
                                    #Z1TrailingIso = ev.mIso[muonCandIndAr[Z1TrailingItr]]


                                if not Z2IsMuon:
                                    #Z2LeadIso = ev.eIso[elecPassesZ2CutsFinalAr[tmpZ2Ind][0]]
                                    #Z2TrailingIso = ev.eIso[elecPassesZ2CutsFinalAr[tmpZ2Ind][1]]

                                    tmpPt = tmpTopZ2LeadPt
                                    if tmpPt > 35:
                                        if abs(ev.Electron_eta[elecPassesZ2CutsAr[tmpZ2Ind][0]]) < 1.4:
                                            tmpAdd = max(0., ev.Electron_dr03EcalRecHitSumEt[elecPassesZ2CutsAr[tmpZ2Ind][0]] - 1.)
                                        else:
                                            tmpAdd = ev.Electron_dr03EcalRecHitSumEt[elecPassesZ2CutsAr[tmpZ2Ind][0]]
                                        tmpIso = ( ev.Electron_dr03TkSumPt[elecPassesZ2CutsAr[tmpZ2Ind][0]] + tmpAdd + ev.Electron_dr03HcalDepth1TowerSumEt[elecPassesZ2CutsAr[tmpZ2Ind][0]] ) / ev.Electron_pt[elecPassesZ2CutsAr[tmpZ2Ind][0]]
                                    else:
                                        tmpIso = ev.Electron_pfRelIso03_all[elecPassesZ2CutsAr[tmpZ2Ind][0]]
                                    Z2LeadIso = tmpIso
                                    tmpPt = tmpTopZ2TrailingPt
                                    if tmpPt > 35:
                                        if abs(ev.Electron_eta[elecPassesZ2CutsAr[tmpZ2Ind][1]]) < 1.4:
                                            tmpAdd = max(0., ev.Electron_dr03EcalRecHitSumEt[elecPassesZ2CutsAr[tmpZ2Ind][1]] - 1.)
                                        else:
                                            tmpAdd = ev.Electron_dr03EcalRecHitSumEt[elecPassesZ2CutsAr[tmpZ2Ind][1]]
                                        tmpIso = ( ev.Electron_dr03TkSumPt[elecPassesZ2CutsAr[tmpZ2Ind][1]] + tmpAdd + ev.Electron_dr03HcalDepth1TowerSumEt[elecPassesZ2CutsAr[tmpZ2Ind][1]] ) / ev.Electron_pt[elecPassesZ2CutsAr[tmpZ2Ind][1]]
                                    else:
                                        tmpIso = ev.Electron_pfRelIso03_all[elecPassesZ2CutsAr[tmpZ2Ind][1]]
                                    Z2TrailingIso = tmpIso

                                else:
                                    Z2LeadIso = ev.Muon_pfRelIso03_all[muonPassesZ2CutsFinalAr[tmpZ2Ind][0]]
                                    Z2TrailingIso = ev.Muon_pfRelIso03_all[muonPassesZ2CutsFinalAr[tmpZ2Ind][1]]
                                    #Z2LeadIso = ev.mIso[muonPassesZ2CutsFinalAr[tmpZ2Ind][0]]
                                    #Z2TrailingIso = ev.mIso[muonPassesZ2CutsFinalAr[tmpZ2Ind][1]]
                                if debug:
                                    print("Z1LeadIso",Z1LeadIso,"Z1TrailingIso",Z1TrailingIso,"Z2LeadIso",Z2LeadIso,"Z2TrailingIso",Z2TrailingIso)

                                
                                passIsoCut = doISOCut(Z1LeadIso,Z1TrailingIso,Z2LeadIso,Z2TrailingIso,lepIsoCut)
                                
                                if passIsoCut:
                                    if debug:
                                        print("passed iso cut yay")
                                    #passesIsoCutCtr += 1
                                    if not Z1IsMuon:
                                        Z1LeadSIP = ev.Electron_sip3d[elecCandIndAr[Z1LeadItr]]
                                        Z1TrailingSIP = ev.Electron_sip3d[elecCandIndAr[Z1TrailingItr]]
                                    else:
                                        Z1LeadSIP = ev.Muon_sip3d[muonCandIndAr[Z1LeadItr]]
                                        Z1TrailingSIP = ev.Muon_sip3d[muonCandIndAr[Z1TrailingItr]]
                                    if not Z2IsMuon:
                                        Z2LeadSIP = ev.Electron_sip3d[elecPassesZ2CutsFinalAr[tmpZ2Ind][0]]
                                        Z2TrailingSIP = ev.Electron_sip3d[elecPassesZ2CutsFinalAr[tmpZ2Ind][1]]
                                    else:
                                        Z2LeadSIP = ev.Muon_sip3d[muonPassesZ2CutsFinalAr[tmpZ2Ind][0]]
                                        Z2TrailingSIP = ev.Muon_sip3d[muonPassesZ2CutsFinalAr[tmpZ2Ind][1]]
                                    if debug:
                                        print("Z1LeadSIP",Z1LeadSIP,"Z1TrailingSIP",Z1TrailingSIP,"Z2LeadSIP",Z2LeadSIP,"Z2TrailingSIP",Z2TrailingSIP)
                                    #Fill with HIGHEST SIP
                                    
                                    passSIPCut = doSIPCut(Z1LeadSIP,Z1TrailingSIP,Z2LeadSIP,Z2TrailingSIP,SIPCut)
                                    if passSIPCut:
                                        if debug:
                                            print("passed SIP cut yay")
                                        passLepCut += 1
                                        passesCutsBool = True
                                        passedAsLepBool = True
            if (not passesCutsBool) and isSemiLeptonic:
                tryingSemiLepCtr += 1
                FJInd = -1
                for i in range(nFatJet):
                    tmpFatJetPT = ev.FatJet_pt[i]
                    if tmpFatJetPT > fatJetPTCut:
                        FJInd = i
                if FJInd != -1:
                    neLep = ev.nElectron
                    enoughElecCands = False
                    negElecCands = 0
                    posElecCands = 0
                    totElecCands = 0
                    elecCandIndAr = []
                    elecCandVecAr = []
                    elecCandChargeAr = []
                    
                    if neLep:
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
                    nmLep = ev.nMuon
                    if debug:
                        print("--------------------------------------------")
                        print("neLep",neLep)
                        for tmpItr in range(neLep):
                            print("tmpItr",tmpItr,"ev.Electron_pt[tmpItr]",ev.Electron_pt[tmpItr],"ev.Electron_eta[tmpItr]",ev.Electron_eta[tmpItr],"ev.Electron_charge[tmpItr]",ev.Electron_charge[tmpItr])
                    if nmLep:
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
                    if totElecCands or totMuonCands:
                        enoughLepCands = True
                    if debug:
                        print("negElecCands",negElecCands,"posElecCands",posElecCands,"totElecCands",totElecCands)
                        print("nmLep",nmLep,"negMuonCands",negMuonCands,"posMuonCands",posMuonCands,"totMuonCands",totMuonCands)
                        print("enoughLepCands",enoughLepCands)
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
                            passSemiLepCut += 1
                            passesCutsBool = True
                            passedAsSemiLepBool = True


            if (not passesCutsBool) and isHadronic:
                tryingHadCtr += 1
                LFJOneInd = -1
                LFJTwoInd = -1
                leadFatJetMaxPT = -1
                secondFatJetMaxPT = -1
                FJInvMass = -1
                for i in range(nFatJet):
                    #Fat Jets with cut but no tagging
                    #Also Fat Jets with cuts and tagging
                    tmpFatJetPT = ev.FatJet_pt[i]
                    if tmpFatJetPT > fatJetPTCut:
                        #Looping through all jets past the current one
                        for j in range(i+1,ev.nFatJet):
                            #Getting PT of the second jet
                            tmpFatJetPTTwo = ev.FatJet_pt[j]
                            #Checking if it passes the pt cut
                            if tmpFatJetPTTwo > fatJetPTCut:
                                #Getting the eta dif between the two jets
                                tmpEtaDif = abs(ev.FatJet_eta[i]-ev.FatJet_eta[j])
                                #Checking if the eta dif passes the eta dif cut
                                if tmpEtaDif > jetEtaDifCut:
                                    #Getting four vectors for the two jets, using pt, eta, phi, and mass
                                    tmpVecOne = Math.PtEtaPhiMVector(ev.FatJet_pt[i], ev.FatJet_eta[i], ev.FatJet_phi[i], ev.FatJet_mass[i])
                                    tmpVecTwo = Math.PtEtaPhiMVector(ev.FatJet_pt[j], ev.FatJet_eta[j], ev.FatJet_phi[j], ev.FatJet_mass[j])
                                    #Adding four vectors together and getting their invariant mass
                                    tmpDiJetVec = tmpVecOne+tmpVecTwo
                                    tmpFJInvMass = tmpDiJetVec.M()
                                    #Checking if their InvMass passes the InvMass cut
                                    if tmpFJInvMass > jetInvMassCut:
                                        
                                        #Selecting on top jet pt first
                                        tmpMaxPtLead = 0
                                        tmpMaxPtSecond = 0
                                        #Sorting which jet has the larger pt
                                        if tmpFatJetPT > tmpFatJetPTTwo:
                                            tmpMaxPtLead = tmpFatJetPT
                                            tmpMaxPtSecond = tmpFatJetPTTwo
                                            tmpFJLeadInd = i
                                            tmpFJTrailingInd = j
                                        else:
                                            tmpMaxPtLead = tmpFatJetPTTwo
                                            tmpMaxPtSecond = tmpFatJetPT
                                            tmpFJLeadInd = j
                                            tmpFJTrailingInd = i

                                        #Selecting based on that jet's pt
                                        if tmpMaxPtLead > leadFatJetMaxPT:
                                            leadFatJetMaxPT = tmpMaxPtLead
                                            secondFatJetMaxPT = tmpMaxPtSecond
                                            LFJOneInd = tmpFJLeadInd
                                            LFJTwoInd = tmpFJTrailingInd
                                            FJInvMass = tmpFJInvMass
                                        #If that jet is already part of the current selected pair,
                                        #select based on the respective lower pt jets in the pairs
                                        elif tmpMaxPtLead == leadFatJetMaxPT:
                                            if tmpMaxPtSecond > secondFatJetMaxPT:
                                                secondFatJetMaxPT = tmpMaxPtSecond
                                                LFJOneInd = tmpFJLeadInd
                                                LFJTwoInd = tmpFJTrailingInd
                                                FJInvMass = tmpFJInvMass
                #Filling histograms based on max jet pt in pair, with secondary jet pt as a tiebreaker
                #Checking that it didn't select the same jet for both parts of the pair 
                if LFJOneInd != LFJTwoInd:
                    passHadCut += 1
                    passesCutsBool = True
                    passedAsHadBool = True
                    """
                    h_InitialFatJetAltLJ_Eta.Fill(ev.FatJet_eta[LFJOneInd])
                    h_InitialFatJetAltLJ_Eta.Fill(ev.FatJet_eta[LFJTwoInd])
                    h_InitialFatJetAltLJ_EtaSep.Fill(abs(ev.FatJet_eta[LFJOneInd]-ev.FatJet_eta[LFJTwoInd]))
                    h_InitialFatJetAltLJ_pt.Fill(ev.FatJet_pt[LFJOneInd])
                    h_InitialFatJetAltLJ_pt.Fill(ev.FatJet_pt[LFJTwoInd])
                    """


            



            if passesCutsBool:
                passesCutsCtr += 1
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
                
                hFatJet_pt_fromPtL[0] = hFatJet_pt_fromPt
                hFatJet_phi_fromPtL[0] = hFatJet_phi_fromPt
                hFatJet_eta_fromPtL[0] = hFatJet_eta_fromPt
                hFatJet_mass_fromPtL[0] = hFatJet_mass_fromPt
                hFatJet_HTag_fromPtL[0] = hFatJet_HTag_fromPt
                hFatJet_pt_fromHTagL[0] = hFatJet_pt_fromHTag
                hFatJet_phi_fromHTagL[0] = hFatJet_phi_fromHTag
                hFatJet_eta_fromHTagL[0] = hFatJet_eta_fromHTag
                hFatJet_mass_fromHTagL[0] = hFatJet_mass_fromHTag
                hFatJet_HTag_fromHTagL[0] = hFatJet_HTag_fromHTag
                

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

                #Branches for distinguishing between channels
                passedLepL[0] = passedAsLepBool 
                passedSemiLepL[0] = passedAsSemiLepBool
                passedHadL[0] = passedAsHadBool

                FATree.Fill()
                evPassCount += 1

                if passedAsLepBool:
                    #tmpZ1Vec = Z1LeadVec + Z1TrailingVec
                    if not Z2IsMuon:
                        tmpZ2LeadVec = eZ2VecPairAr[tmpZ2Ind][0]
                        tmpZ2TrailingVec = eZ2VecPairAr[tmpZ2Ind][1]
                        tmpZ2Vec = tmpZ2LeadVec+tmpZ2TrailingVec
                        
                    else:
                        tmpZ2LeadVec = mZ2VecPairAr[tmpZ2Ind][0]
                        tmpZ2TrailingVec = mZ2VecPairAr[tmpZ2Ind][1]
                        tmpZ2Vec = tmpZ2LeadVec+tmpZ2TrailingVec


                    lepZ1LeadPtL[0]      = Z1LeadPt
                    lepZ1TrailingPtL[0]  = Z1TrailingPt
                    lepZ1LeadPhiL[0]     = Z1LeadVec.Phi()
                    lepZ1TrailingPhiL[0] = Z1TrailingVec.Phi()
                    lepZ1PairInvMassL[0] = tmpZ1Vec.M()
                    lepZ1LeadEtaL[0]     = Z1LeadVec.Eta()
                    lepZ1TrailingEtaL[0] = Z1TrailingVec.Eta()
                    lepZ1IsElectronL[0]  = not Z1IsMuon
                    lepZ1IsMuonL[0]      = Z1IsMuon
                    lepZ1LeadIsoL[0]     = Z1LeadIso
                    lepZ1TrailingIsoL[0] = Z1TrailingIso
                    lepZ1LeadSIPL[0]     = Z1LeadSIP
                    lepZ1TrailingSIPL[0] = Z1TrailingSIP

                    lepZ2LeadPtL[0]      = tmpTopZ2LeadPt
                    lepZ2TrailingPtL[0]  = tmpTopZ2TrailingPt
                    lepZ2LeadPhiL[0]     = tmpZ2LeadVec.Phi()
                    lepZ2TrailingPhiL[0] = tmpZ2TrailingVec.Phi()
                    lepZ2PairInvMassL[0] = tmpZ2Vec.M()
                    lepZ2LeadEtaL[0]     = tmpZ2LeadVec.Eta()
                    lepZ2TrailingEtaL[0] = tmpZ2TrailingVec.Eta()
                    lepZ2IsElectronL[0]  = not Z2IsMuon
                    lepZ2IsMuonL[0]      = Z2IsMuon
                    lepZ2LeadIsoL[0]     = Z2LeadIso
                    lepZ2TrailingIsoL[0] = Z2TrailingIso
                    lepZ2LeadSIPL[0]     = Z2LeadSIP
                    lepZ2TrailingSIPL[0] = Z2TrailingSIP
                    LepTree.Fill()
                
                elif passedAsSemiLepBool:
                    tmpZ1Vec = Z1LeadVec+Z1TrailingVec
                    if not Z1IsMuon:
                        if Z1LeadPt > 35:
                            if abs(ev.Electron_eta[elecCandIndAr[Z1LeadItr]]) < 1.4:
                                tmpAdd = max(0., ev.Electron_dr03EcalRecHitSumEt[elecCandIndAr[Z1LeadItr]] - 1.)
                            else:
                                tmpAdd = ev.Electron_dr03EcalRecHitSumEt[elecCandIndAr[Z1LeadItr]]
                            tmpIso = ( ev.Electron_dr03TkSumPt[elecCandIndAr[Z1LeadItr]] + tmpAdd + ev.Electron_dr03HcalDepth1TowerSumEt[elecCandIndAr[Z1LeadItr]] ) / ev.Electron_pt[elecCandIndAr[Z1LeadItr]]
                        else:
                            tmpIso = ev.Electron_pfRelIso03_all[elecCandIndAr[Z1LeadItr]]
                        Z1LeadIso = tmpIso
                        
                        
                        if Z1TrailingPt > 35:
                            if abs(ev.Electron_eta[elecCandIndAr[Z1TrailingItr]]) < 1.4:
                                tmpAdd = max(0., ev.Electron_dr03EcalRecHitSumEt[elecCandIndAr[Z1TrailingItr]] - 1.)
                            else:
                                tmpAdd = ev.Electron_dr03EcalRecHitSumEt[elecCandIndAr[Z1TrailingItr]]
                            tmpIso = ( ev.Electron_dr03TkSumPt[elecCandIndAr[Z1TrailingItr]] + tmpAdd + ev.Electron_dr03HcalDepth1TowerSumEt[elecCandIndAr[Z1LeadItr]] ) / ev.Electron_pt[elecCandIndAr[Z1LeadItr]]
                        else:
                            tmpIso = ev.Electron_pfRelIso03_all[elecCandIndAr[Z1TrailingItr]]
                        Z1TrailingIso = tmpIso
                    else:
                        Z1LeadIso = ev.Muon_pfRelIso03_all[muonCandIndAr[Z1LeadItr]]
                        Z1TrailingIso = ev.Muon_pfRelIso03_all[muonCandIndAr[Z1TrailingItr]]

                    if not Z1IsMuon:
                        Z1LeadSIP = ev.Electron_sip3d[elecCandIndAr[Z1LeadItr]]
                        Z1TrailingSIP = ev.Electron_sip3d[elecCandIndAr[Z1TrailingItr]]
                    else:
                        Z1LeadSIP = ev.Muon_sip3d[muonCandIndAr[Z1LeadItr]]
                        Z1TrailingSIP = ev.Muon_sip3d[muonCandIndAr[Z1TrailingItr]]

                    
                    lepLeadPtL[0]      = Z1LeadPt
                    lepTrailingPtL[0]  = Z1TrailingPt
                    lepLeadPhiL[0]     = Z1LeadVec.Phi()
                    lepTrailingPhiL[0] = Z1TrailingVec.Phi()
                    lepPairInvMassL[0] = tmpZ1Vec.M()
                    lepLeadEtaL[0]     = Z1LeadVec.Eta()
                    lepTrailingEtaL[0] = Z1TrailingVec.Eta()
                    lepIsElectronL[0]  = not Z1IsMuon
                    lepIsMuonL[0]      = Z1IsMuon
                    lepLeadIsoL[0]     = Z1LeadIso
                    lepTrailingIsoL[0] = Z1TrailingIso
                    lepLeadSIPL[0]     = Z1LeadSIP
                    lepTrailingSIPL[0] = Z1TrailingSIP

                    FJPtL[0]      = ev.FatJet_pt[FJInd]
                    FJPhiL[0]     = ev.FatJet_phi[FJInd]
                    FJMassL[0]    = ev.FatJet_mass[FJInd]
                    FJEtaL[0]     = ev.FatJet_eta[FJInd]

                    SemiLepTree.Fill()


                elif passedAsHadBool:
                    
                    FJLeadPtL[0]      = leadFatJetMaxPT
                    FJTrailingPtL[0]  = secondFatJetMaxPT
                    FJLeadPhiL[0]     = ev.FatJet_phi[LFJOneInd]
                    FJTrailingPhiL[0] = ev.FatJet_phi[LFJTwoInd]
                    FJLeadMassL[0]    = ev.FatJet_mass[LFJOneInd]
                    FJTrailingMassL[0] = ev.FatJet_mass[LFJTwoInd]
                    FJPairInvMassL[0] = FJInvMass
                    FJLeadEtaL[0]     = ev.FatJet_eta[LFJOneInd]
                    FJTrailingEtaL[0] = ev.FatJet_eta[LFJTwoInd]
                    FJEtaSepL[0]      = abs(ev.FatJet_eta[LFJOneInd]-ev.FatJet_eta[LFJTwoInd])

                    HadTree.Fill()







                    

                






print("Finished file loop.","time:",time.time()-startt)

nEv[0] = evRunOver
nEvPass[0] = evPassCount
evNumTree.Fill()

print("evRunOver:",evRunOver,"-------------------")
print("passes hbb cut:",passhbbCtr,"-------------------")
print("passes channel cut:",passAnyChannelCtr,"-------------------")
print("passes lep channel cut:",passLepChannelCtr)
print("passes semi lep channel cut:",passSemiLepChannelCtr)
print("passes had channel cut:",passHadChannelCtr)
print("passes lep and semi lep channel cut:",passLepAndSemiLepChannelCtr)
print("passes lep and had channel cut:",passLepAndHadChannelCtr)
print("passes semi lep and had channel cut:",passSemiLepAndHadChannelCtr)
print("passes all channel cut:",passAllChannelCtr)
print("passes VBF Jet cut:",passVBFJets,"-------------------")
print("passes Higgs FatJet cut:",passFatJets)
print("passes Higgs GenPart cut:",passGenPart,"-------------------")
print("trying lep cut:",tryingLepCtr)
print("trying semi lep cut:",tryingSemiLepCtr)
print("trying had cut:",tryingHadCtr)
print("passes lep cut:",passLepCut,"-------------------")
print("passes semi lep cut:",passSemiLepCut,"-------------------")
print("passes had cut:",passHadCut,"-------------------")

print("passes all cuts:",passesCutsCtr,"-------------------")
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
FATree.Write("",TObject.kOverwrite)
LepTree.Write("",TObject.kOverwrite)
SemiLepTree.Write("",TObject.kOverwrite)
HadTree.Write("",TObject.kOverwrite)



outFile.Close()

        
        
                


                




