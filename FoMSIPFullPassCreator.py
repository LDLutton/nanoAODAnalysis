import datetime
from array import array
from math import sqrt
from ROOT import TFile, TChain, gDirectory, TApplication, TMath, Math, TMinuit, TROOT, TSystem, TTree, TVector2
from ROOT import TH1F, TCanvas, TPad, TF1, TGraph, TGraphErrors, TLegend, TLine, TPaveText, TStyle
from ROOT import TH2D, TH2F,gPad
from math import sqrt,pi,log
import time as time

today = datetime.datetime.today()
startt = time.time()
"""
def doZ2Cut(ev,Z1LeadVec,Z1TrailingVec,Z1IsMuon,eZ2PairIndAr,mZ2PairIndAr,fourLepInvMassCut,optLepInvMassCut):
    tmpLeadInd = -1
    tmpTrailingInd = -1
    tmpZ1Vec = Z1LeadVec + Z1TrailingVec
    #Electrons first
    for eZ2PairInd in eZ2PairIndAr:
        tmpZ2VecOne = ev.
"""

def makeNiceHistos(histo,xTitle,yTitle,noX=True):
  if noX:
    histo.GetXaxis().SetLabelOffset(999)
    histo.GetXaxis().SetLabelSize(0)
  else:
    histo.GetXaxis().SetTitle(xTitle)
    histo.GetXaxis().SetTitleSize(0.068)
    histo.GetXaxis().SetTitleFont(42)
    histo.GetXaxis().SetLabelFont(42)
    histo.GetXaxis().SetLabelSize(0.055)
  histo.GetYaxis().SetTitle(yTitle)
  histo.GetYaxis().CenterTitle()
  histo.GetYaxis().SetTitleOffset(0.55)
  histo.GetYaxis().SetTitleSize(0.068)
  histo.GetYaxis().SetTitleFont(42)
  histo.GetYaxis().SetLabelFont(42)
  histo.GetYaxis().SetLabelSize(0.055)
  histo.SetTitle("")
  histo.SetStats(0)

def setUpLegend(legAr):
  legAr.append(TLegend(.9,.6,.99,.92))
  legAr[-1].SetTextSize(0.036)
  legAr[-1].SetTextFont(42)


def setUpPadsAr(padAr,padName):
  padAr.append([])
  padAr[-1].append(TPad(padName, padName,0.,0.40,1,1))
  padAr[-1].append(TPad(padName+" ratio", padName+" ratio",0.,0.,1,0.45))

def setUpBottomPadsAr(padAr):
  padAr[1].SetTopMargin(0)
  padAr[1].SetBottomMargin(0.15)
  padAr[1].Draw()
  padAr[1].cd()

def doeCandCut(ev,neLep,elecCandIndAr,elecCandVecAr,elecCandChargeAr,ePtCut,eEtaCut):
    for eItr in range(neLep):
        tmpPt = ev.ePt[eItr]
        if tmpPt > ePtCut:
            tmpEta = ev.eEta[eItr]
            if abs(tmpEta) < eEtaCut:
                elecCandIndAr.append(eItr)
                tmpPhi = ev.ePhi[eItr]
                tmpMass = ev.eMass[eItr]
                tmpVec = Math.PtEtaPhiMVector(tmpPt, tmpEta, tmpPhi, tmpMass)
                elecCandVecAr.append(tmpVec)
                tmpCharge = ev.eCharge[eItr]
                elecCandChargeAr.append(tmpCharge)

def domCandCut(ev,nmLep,muonCandIndAr,muonCandVecAr,muonCandChargeAr,mPtCut,mEtaCut):
    for mItr in range(nmLep):
        tmpPt = ev.mPt[mItr]
        if tmpPt > mPtCut:
            tmpEta = ev.mEta[mItr]
            if abs(tmpEta) < mEtaCut:
                muonCandIndAr.append(mItr)
                tmpPhi = ev.mPhi[mItr]
                tmpMass = ev.mMass[mItr]
                tmpVec = Math.PtEtaPhiMVector(tmpPt, tmpEta, tmpPhi, tmpMass)
                muonCandVecAr.append(tmpVec)
                tmpCharge = ev.mCharge[mItr]
                muonCandChargeAr.append(tmpCharge)     


def doeZ1Cut(ev,elecCandIndAr,elecCandVecAr,elecCandChargeAr,elecPassesZ2CutsAr,Z1IsMuon,invMassCutLow,invMassCutHigh,ptLeadCut,ptTrailingCut,tmpTopZ1LeadPt,tmpTopZ1TrailingPt,tmpTopLeadItr,tmpTopTrailingItr,tmpTopLeadVec,tmpTopTrailingVec,tmpTopLeadCharge,tmpTopTrailingCharge,difFromZMassOne):
    if debug:
        print("in doeZ1Cut fcn")
    for eItrOne,elecCandIndOne in enumerate(elecCandIndAr[:-1]): #ELECTRON LOOP ONE
        tmpChargeOne = elecCandChargeAr[eItrOne]
        if debug:
            print("eItrOne",eItrOne,"elecCandIndOne",elecCandIndOne,"tmpChargeOne",tmpChargeOne)
        for tmpeItrTwo,elecCandIndTwo in enumerate(elecCandIndAr[eItrOne+1:]): #ELECTRON LOOP TWO
            eItrTwo = eItrOne + tmpeItrTwo + 1
            tmpChargeTwo = elecCandChargeAr[eItrTwo]
            if debug:
                print("eItrTwo",eItrTwo,"elecCandIndOne",elecCandIndTwo,"tmpChargeOne",tmpChargeTwo)
            if tmpChargeOne != tmpChargeTwo: #CHECK IF OPPOSITE CHARGE
                tmpZ1VecOne = elecCandVecAr[eItrOne]
                tmpZ1VecTwo = elecCandVecAr[eItrTwo]
                tmpZ1Vec =  tmpZ1VecOne+tmpZ1VecTwo
                tmpZ1Mass = tmpZ1Vec.M()
                if debug:
                    print("not the same charge. yay")
                    print("tmpZ1VecOne",tmpZ1VecOne,"tmpZ1VecTwo",tmpZ1VecTwo,"tmpZ1Vec",tmpZ1Vec)
                if tmpZ1Mass > invMassCutLow and tmpZ1Mass < invMassCutHigh: #CHECK IF INV MASS PASSES CUTS
                    if debug:
                        print("Passed inv mass cut")
                    tmpZDif = abs(tmpZ1Mass - ZMass)
                    tmpPtOne = ev.ePt[elecCandIndOne]
                    tmpPtTwo = ev.ePt[elecCandIndTwo]
                    if debug:
                        print("tmpZDif",tmpZDif,"tmpPtOne",tmpPtOne,"tmpPtTwo",tmpPtTwo)
                    if tmpPtOne >= tmpPtTwo: #SORT PTS
                        #elecPassesZ2CutsAr.append([elecCandIndOne,elecCandIndTwo])
                        tmpPtLead = tmpPtOne
                        tmpPtTrailing = tmpPtTwo
                        tmpLeadItr = eItrOne
                        tmpTrailingItr = eItrTwo
                        tmpLeadVec = tmpZ1VecOne
                        tmpTrailingVec = tmpZ1VecTwo
                        tmpLeadCharge = tmpChargeOne
                        tmpTrailingCharge = tmpChargeTwo
                    else:
                        #elecPassesZ2CutsAr.append([elecCandIndTwo,elecCandIndOne])
                        tmpPtLead = tmpPtTwo
                        tmpPtTrailing = tmpPtOne
                        tmpLeadItr = eItrTwo
                        tmpTrailingItr = eItrOne
                        tmpLeadVec = tmpZ1VecTwo
                        tmpTrailingVec = tmpZ1VecOne
                        tmpLeadCharge = tmpChargeTwo
                        tmpTrailingCharge = tmpChargeOne


                    if tmpZDif < difFromZMassOne: #CHECK IF INV MASS DIF LESS THAN CURRENT SMALLEST DIF
                        if debug:
                            print("current smallest zdif yay")
                        

                        if tmpPtLead > ptLeadCut and tmpPtTrailing > ptTrailingCut: #CHECK IF PASSES PT CUT
                            if debug:
                                print("wow it passed the pt cut also yay")
                            tmpTopZ1LeadPt = tmpPtLead
                            tmpTopZ1TrailingPt = tmpPtTrailing
                            difFromZMassOne = tmpZDif
                            tmpTopLeadItr = tmpLeadItr
                            tmpTopTrailingItr = tmpTrailingItr
                            Z1IsMuon = False
                            tmpTopLeadVec = tmpLeadVec
                            tmpTopTrailingVec = tmpTrailingVec
                            tmpTopLeadCharge = tmpLeadCharge
                            tmpTopTrailingCharge = tmpTrailingCharge
                    elecPassesZ2CutsAr.append([tmpLeadItr,tmpTrailingItr])
    return tmpTopLeadItr,tmpTopTrailingItr,tmpTopZ1LeadPt,tmpTopZ1TrailingPt,tmpTopLeadVec,tmpTopTrailingVec,tmpTopLeadCharge,tmpTopTrailingCharge,Z1IsMuon,difFromZMassOne

def domZ1Cut(ev,muonCandIndAr,muonCandVecAr,muonCandChargeAr,muonPassesZ2CutsAr,Z1IsMuon,invMassCutLow,invMassCutHigh,ptLeadCut,ptTrailingCut,tmpTopZ1LeadPt,tmpTopZ1TrailingPt,tmpTopLeadItr,tmpTopTrailingItr,tmpTopLeadVec,tmpTopTrailingVec,tmpTopLeadCharge,tmpTopTrailingCharge,difFromZMassOne):
    if debug:
        print("in domZ1Cut fcn")
    for mItrOne,muonCandIndOne in enumerate(muonCandIndAr[:-1]): #MUON LOOP ONE
        tmpChargeOne = muonCandChargeAr[mItrOne]
        if debug:
            print("mItrOne",mItrOne,"muonCandIndOne",muonCandIndOne,"tmpChargeOne",tmpChargeOne)
        for tmpmItrTwo,muonCandIndTwo in enumerate(muonCandIndAr[mItrOne+1:]): #MUON LOOP TWO
            mItrTwo = mItrOne + tmpmItrTwo + 1
            tmpChargeTwo = muonCandChargeAr[mItrTwo]
            if debug:
                print("mItrTwo",mItrTwo,"muonCandIndOne",muonCandIndTwo,"tmpChargeOne",tmpChargeTwo)
            if tmpChargeOne != tmpChargeTwo: #CHECK IF OPPOSITE CHARGE
                tmpZ1VecOne = muonCandVecAr[mItrOne]
                tmpZ1VecTwo = muonCandVecAr[mItrTwo]
                tmpZ1Vec =  tmpZ1VecOne+tmpZ1VecTwo
                tmpZ1Mass = tmpZ1Vec.M()
                if debug:
                    print("not the same charge. yay")
                    print("tmpZ1VecOne",tmpZ1VecOne,"tmpZ1VecTwo",tmpZ1VecTwo,"tmpZ1Vec",tmpZ1Vec)
                if tmpZ1Mass > invMassCutLow and tmpZ1Mass < invMassCutHigh: #CHECK IF INV MASS PASSES CUTS
                    if debug:
                        print("Passed inv mass cut")
                    tmpZDif = abs(tmpZ1Mass - ZMass)
                    tmpPtOne = ev.mPt[muonCandIndOne]
                    tmpPtTwo = ev.mPt[muonCandIndTwo]
                    if debug:
                        print("tmpZDif",tmpZDif,"tmpPtOne",tmpPtOne,"tmpPtTwo",tmpPtTwo)
                    if tmpPtOne >= tmpPtTwo: #SORT PTS
                        #muonPassesZ2CutsAr.append([muonCandIndOne,muonCandIndTwo])
                        tmpPtLead = tmpPtOne
                        tmpPtTrailing = tmpPtTwo
                        tmpLeadItr = mItrOne
                        tmpTrailingItr = mItrTwo
                        tmpLeadVec = tmpZ1VecOne
                        tmpTrailingVec=tmpZ1VecTwo
                        tmpLeadCharge = tmpChargeOne
                        tmpTrailingCharge = tmpChargeTwo
                    else:
                        #muonPassesZ2CutsAr.append([muonCandIndTwo,muonCandIndOne])
                        tmpPtLead = tmpPtTwo
                        tmpPtTrailing = tmpPtOne
                        tmpLeadItr = mItrTwo
                        tmpTrailingItr = mItrOne
                        tmpLeadVec = tmpZ1VecTwo
                        tmpTrailingVec=tmpZ1VecOne
                        tmpLeadCharge = tmpChargeTwo
                        tmpTrailingCharge = tmpChargeOne


                    if tmpZDif < difFromZMassOne: #CHECK IF INV MASS DIF LESS THAN CURRENT SMALLEST DIF
                        if debug:
                            print("current smallest zdif yay")
                        
                        if tmpPtLead > ptLeadCut and tmpPtTrailing > ptTrailingCut: #CHECK IF PASSES PT CUT
                            if debug:
                                print("wow it passed the pt cut also yay")
                            tmpTopZ1LeadPt = tmpPtLead
                            tmpTopZ1TrailingPt = tmpPtTrailing
                            difFromZMassOne = tmpZDif
                            tmpTopLeadItr = tmpLeadItr
                            tmpTopTrailingItr = tmpTrailingItr
                            Z1IsMuon = True
                            tmpTopLeadVec = tmpLeadVec
                            tmpTopTrailingVec = tmpTrailingVec
                            tmpTopLeadCharge = tmpLeadCharge
                            tmpTopTrailingCharge = tmpTrailingCharge
                    muonPassesZ2CutsAr.append([tmpLeadItr,tmpTrailingItr])
    return tmpTopLeadItr,tmpTopTrailingItr,tmpTopZ1LeadPt,tmpTopZ1TrailingPt,tmpTopLeadVec,tmpTopTrailingVec,tmpTopLeadCharge,tmpTopTrailingCharge,Z1IsMuon,difFromZMassOne

def doeZ2Cut(ev,Z1LeadVec,Z1TrailingVec,tmpZ1Vec,Z1LeadCharge,Z1TrailingCharge,Z1IsMuon,eZ2VecPairAr,eZ2PtPairAr,eZ2ChargePairAr,tmpZ2Ind,Z2IsMuon,tmpTopZ2LeadPt,tmpTopZ2TrailingPt,fourLepInvMassCut,optLepInvMassCut):
    #Electrons first
    for Z2Itr,eZ2VecPair in enumerate(eZ2VecPairAr): #LOOP OVER ALL Z2 CANDIDATE PAIRS
        tmpZ2LeadPt = eZ2PtPairAr[Z2Itr][0] 
        if tmpZ2LeadPt > tmpTopZ2LeadPt: #Check if passes lead Z2 pt cut
            tmpZ4Vec = tmpZ1Vec+eZ2VecPair[0]+eZ2VecPair[1]
            if tmpZ4Vec.M() > fourLepInvMassCut: #Check if passes four lepton inv mass cut
                if not Z1IsMuon: #If Z1 is electrons, then have to perform second 4e cuts
                    if Z1LeadCharge != eZ2ChargePairAr[0]:
                        tmpLepPairVecOne = Z1LeadVec + eZ2VecPair[0]
                        if tmpLepPairVecOne.M() > optLepInvMassCut:
                            tmpZ2Ind = Z2Itr
                            tmpTopZ2LeadPt = tmpZ2LeadPt
                            tmpTopZ2TrailingPt = eZ2PtPairAr[Z2Itr][1]
                            Z2IsMuon = False
                        else:
                            tmpLepPairVecTwo = Z1TrailingVec + eZ2VecPair[1]
                            if tmpLepPairVecTwo.M() > optLepInvMassCut:
                                tmpZ2Ind = Z2Itr
                                tmpTopZ2LeadPt = tmpZ2LeadPt
                                tmpTopZ2TrailingPt = eZ2PtPairAr[Z2Itr][1]
                                Z2IsMuon = False
                                
                    else:
                        tmpLepPairVecOne = Z1LeadVec + eZ2VecPair[1]
                        if tmpLepPairVecOne.M() > optLepInvMassCut:
                            tmpZ2Ind = Z2Itr
                            tmpTopZ2LeadPt = tmpZ2LeadPt
                            tmpTopZ2TrailingPt = eZ2PtPairAr[Z2Itr][1]
                            Z2IsMuon = False
                        else:
                            tmpLepPairVecTwo = Z1TrailingVec + eZ2VecPair[0]
                            if tmpLepPairVecTwo.M() > optLepInvMassCut:
                                tmpZ2Ind = Z2Itr
                                tmpTopZ2LeadPt = tmpZ2LeadPt
                                tmpTopZ2TrailingPt = eZ2PtPairAr[Z2Itr][1]
                                Z2IsMuon = False
                else:
                    tmpZ2Ind = Z2Itr
                    tmpTopZ2LeadPt = tmpZ2LeadPt
                    tmpTopZ2TrailingPt = eZ2PtPairAr[Z2Itr][1]
                    Z2IsMuon = False

        elif tmpZ2LeadPt == tmpTopZ2LeadPt:
            tmpZ2TrailingPt = eZ2PtPairAr[Z2Itr][1] 
            if tmpZ2TrailingPt > tmpTopZ2TrailingPt:
                tmpZ4Vec = tmpZ1Vec+eZ2VecPair[0]+eZ2VecPair[1]
                if tmpZ4Vec.M() > fourLepInvMassCut:
                    if not Z1IsMuon:
                        if Z1LeadCharge != eZ2ChargePairAr[0]:
                            tmpLepPairVecOne = Z1LeadVec + eZ2VecPair[0]
                            if tmpLepPairVecOne.M() > optLepInvMassCut:
                                tmpZ2Ind = Z2Itr
                                tmpTopZ2LeadPt = tmpZ2LeadPt
                                tmpTopZ2TrailingPt = tmpZ2TrailingPt
                                Z2IsMuon = False
                            else:
                                tmpLepPairVecTwo = Z1TrailingVec + eZ2VecPair[1]
                                if tmpLepPairVecTwo.M() > optLepInvMassCut:
                                    tmpZ2Ind = Z2Itr
                                    tmpTopZ2LeadPt = tmpZ2LeadPt
                                    tmpTopZ2TrailingPt = tmpZ2TrailingPt
                                    Z2IsMuon = False
                        else:
                            tmpLepPairVecOne = Z1LeadVec + eZ2VecPair[1]
                            if tmpLepPairVecOne.M() > optLepInvMassCut:
                                tmpZ2Ind = Z2Itr
                                tmpTopZ2LeadPt = tmpZ2LeadPt
                                tmpTopZ2TrailingPt = tmpZ2TrailingPt 
                                Z2IsMuon = False
                            else:
                                tmpLepPairVecTwo = Z1TrailingVec + eZ2VecPair[0]
                                if tmpLepPairVecTwo.M() > optLepInvMassCut:
                                    tmpZ2Ind = Z2Itr
                                    tmpTopZ2LeadPt = tmpZ2LeadPt
                                    tmpTopZ2TrailingPt = tmpZ2TrailingPt 
                                    Z2IsMuon = False
                    else:
                        tmpZ2Ind = Z2Itr
                        tmpTopZ2LeadPt = tmpZ2LeadPt
                        tmpTopZ2TrailingPt = tmpZ2TrailingPt
                        Z2IsMuon = False
    return tmpZ2Ind,Z2IsMuon,tmpTopZ2LeadPt,tmpTopZ2TrailingPt
    #Now Muons
def domZ2Cut(ev,Z1LeadVec,Z1TrailingVec,tmpZ1Vec,Z1LeadCharge,Z1TrailingCharge,Z1IsMuon,mZ2VecPairAr,mZ2PtPairAr,mZ2ChargePairAr,tmpZ2Ind,Z2IsMuon,tmpTopZ2LeadPt,tmpTopZ2TrailingPt,fourLepInvMassCut,optLepInvMassCut):
    for Z2Itr,mZ2VecPair in enumerate(mZ2VecPairAr):
        tmpZ2LeadPt = mZ2PtPairAr[Z2Itr][0] 
        if tmpZ2LeadPt > tmpTopZ2LeadPt:
            tmpZ4Vec = tmpZ1Vec+mZ2VecPair[0]+mZ2VecPair[1]
            if tmpZ4Vec.M() > fourLepInvMassCut:
                if Z1IsMuon:
                    if Z1LeadCharge != mZ2ChargePairAr[0]:
                        tmpLepPairVecOne = Z1LeadVec + mZ2VecPair[0]
                        if tmpLepPairVecOne.M() > optLepInvMassCut:
                            tmpZ2Ind = Z2Itr
                            tmpTopZ2LeadPt = tmpZ2LeadPt
                            tmpTopZ2TrailingPt = mZ2PtPairAr[Z2Itr][1]
                            Z2IsMuon = True
                        else:
                            tmpLepPairVecTwo = Z1TrailingVec + mZ2VecPair[1]
                            if tmpLepPairVecTwo.M() > optLepInvMassCut:
                                tmpZ2Ind = Z2Itr
                                tmpTopZ2LeadPt = tmpZ2LeadPt
                                tmpTopZ2TrailingPt = mZ2PtPairAr[Z2Itr][1]
                                Z2IsMuon = True
                    else:
                        tmpLepPairVecOne = Z1LeadVec + mZ2VecPair[1]
                        if tmpLepPairVecOne.M() > optLepInvMassCut:
                            tmpZ2Ind = Z2Itr
                            tmpTopZ2LeadPt = tmpZ2LeadPt
                            tmpTopZ2TrailingPt = mZ2PtPairAr[Z2Itr][1]
                            Z2IsMuon = True
                        else:
                            tmpLepPairVecTwo = Z1TrailingVec + mZ2VecPair[0]
                            if tmpLepPairVecTwo.M() > optLepInvMassCut:
                                tmpZ2Ind = Z2Itr
                                tmpTopZ2LeadPt = tmpZ2LeadPt
                                tmpTopZ2TrailingPt = mZ2PtPairAr[Z2Itr][1]
                                Z2IsMuon = True
                else:
                    tmpZ2Ind = Z2Itr
                    tmpTopZ2LeadPt = tmpZ2LeadPt
                    tmpTopZ2TrailingPt = mZ2PtPairAr[Z2Itr][1]
                    Z2IsMuon = True

        elif tmpZ2LeadPt == tmpTopZ2LeadPt:
            tmpZ2TrailingPt = mZ2PtPairAr[Z2Itr][1] 
            if tmpZ2TrailingPt > tmpTopZ2TrailingPt:
                tmpZ4Vec = tmpZ1Vec+mZ2VecPair[0]+mZ2VecPair[1]
                if tmpZ4Vec.M() > fourLepInvMassCut:
                    if Z1IsMuon:
                        if Z1LeadCharge != mZ2ChargePairAr[0]:
                            tmpLepPairVecOne = Z1LeadVec + mZ2VecPair[0]
                            if tmpLepPairVecOne.M() > optLepInvMassCut:
                                tmpZ2Ind = Z2Itr
                                tmpTopZ2LeadPt = tmpZ2LeadPt
                                tmpTopZ2TrailingPt = tmpZ2TrailingPt
                                Z2IsMuon = True
                            else:
                                tmpLepPairVecTwo = Z1TrailingVec + mZ2VecPair[1]
                                if tmpLepPairVecTwo.M() > optLepInvMassCut:
                                    tmpZ2Ind = Z2Itr
                                    tmpTopZ2LeadPt = tmpZ2LeadPt
                                    tmpTopZ2TrailingPt = tmpZ2TrailingPt
                                    Z2IsMuon = True
                        else:
                            tmpLepPairVecOne = Z1LeadVec + mZ2VecPair[1]
                            if tmpLepPairVecOne.M() > optLepInvMassCut:
                                tmpZ2Ind = Z2Itr
                                tmpTopZ2LeadPt = tmpZ2LeadPt
                                tmpTopZ2TrailingPt = tmpZ2TrailingPt
                                Z2IsMuon = True
                            else:
                                tmpLepPairVecTwo = Z1TrailingVec + mZ2VecPair[0]
                                if tmpLepPairVecTwo.M() > optLepInvMassCut:
                                    tmpZ2Ind = Z2Itr
                                    tmpTopZ2LeadPt = tmpZ2LeadPt
                                    tmpTopZ2TrailingPt = tmpZ2TrailingPt
                                    Z2IsMuon = True
                    else:
                        tmpZ2Ind = Z2Itr
                        tmpTopZ2LeadPt = tmpZ2LeadPt
                        tmpTopZ2TrailingPt = tmpZ2TrailingPt
                        Z2IsMuon = True
    return tmpZ2Ind,Z2IsMuon,tmpTopZ2LeadPt,tmpTopZ2TrailingPt
                        

def doISOCut(Z1LeadIso,Z1TrailingIso,Z2LeadIso,Z2TrailingIso,lepIsoCut):
    if Z1LeadIso + Z1TrailingIso >= lepIsoCut:
        return False
    elif Z1LeadIso + Z2LeadIso >= lepIsoCut:
        return False
    elif Z1LeadIso + Z2TrailingIso >= lepIsoCut:
        return False
    elif Z1TrailingIso + Z2LeadIso >= lepIsoCut:
        return False
    elif Z1TrailingIso + Z2TrailingIso >= lepIsoCut:
        return False
    elif Z2LeadIso + Z2TrailingIso >= lepIsoCut:
        return False
    else:
        return True
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
        tmpIsoAr.append(tmpIsoOne)
        lepC3Iso[i] = tmpIsoOne
                        
    cutThreeTree.SetBranchAddress("lepC3Iso",lepC3Iso)
    cutThreeTree.Fill()
                        
    for i,tmpIsoOne in enumerate(tmpIsoAr[:-1]):
        for tmpIsoTwo in tmpIsoAr[i+1:]:
            if debug:
                print(i,"tmpIsoOne",tmpIsoOne,"tmpIsoTwo",tmpIsoTwo)
            if tmpIsoOne + tmpIsoTwo > lepIsoCut:
                if debug:
                    print(i,"summed isos > 0.35. cuts not passed")
                passesIsoCuts = False
                break
        if not passesIsoCuts:
            break
    """

def doSIPCut(Z1LeadSIP,Z1TrailingSIP,Z2LeadSIP,Z2TrailingSIP,SIPCut):
    if Z1LeadSIP > SIPCut:
        return False
    elif Z1TrailingSIP > SIPCut:
        return False
    if Z2LeadSIP > SIPCut:
        return False
    elif Z2TrailingSIP > SIPCut:
        return False
    else:
        return True



debug = False
debugMin = 1000
debugMax = 1004
forCondor = True
if forCondor:
    forCondorStr = "/scratch365/dlutton/HistosAndPNGs/"
else:
    forCondorStr = ""

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



if MGSM:
    #fileAr.append(TFile.Open("{0}FoMTreesFrompphzzjjQCD0SMHLOOP0QEDE5NPE0ResMasAllVer100Ev_0p999cHW100GeVIMJetCut.root".format(forCondorStr)))
    fileAr.append(TFile.Open("{0}FoMTreesFrompphzzjjQCD0SMHLOOP0QEDE5NPE0ResMasAllVer100Ev_0p999cHW100GeVIMJetCut_InputTrimmed_FullPass.root".format(forCondorStr)))
    nameAr.append("SM")
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
if MGEFT:
    #fileAr.append(TFile.Open("{0}FoMTreesFrompphzzjjQCD0SMHLOOP0NPE1NPcHWE1QEDE5ResMasAllVer100Ev_0p999cHW100GeVIMJetCut.root".format(forCondorStr)))
    fileAr.append(TFile.Open("{0}FoMTreesFrompphzzjjQCD0SMHLOOP0NPE1NPcHWE1QEDE5ResMasAllVer100Ev_0p999cHW100GeVIMJetCut_InputTrimmed_FullPass.root".format(forCondorStr)))
    nameAr.append("EFT")
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

if ttHToBBBackground:
    #fileAr.append(TFile.Open("{0}FoMTreesFromttHToBBBackground.root".format(forCondorStr)))
    fileAr.append(TFile.Open("{0}FoMTreesFromttHToBBBackground_InputTrimmed_FullPass.root".format(forCondorStr)))
    nameAr.append("ttHToBBBackground")
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
if ttZJetsBackground:
    fileAr.append(TFile.Open("{0}FoMTreesFromttZJetsBackground_InputTrimmed_FullPass.root".format(forCondorStr)))
    nameAr.append("ttZJetsBackground")
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


if DYBackground:
    fileAr.append(TFile.Open("{0}FoMTreesFromDYBackground_InputTrimmed_FullPass.root".format(forCondorStr)))
    nameAr.append("DYBackground")
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


if QCDPT170to300Background:
    fileAr.append(TFile.Open("{0}FoMTreesFromQCDPT170to300Background_InputTrimmed_FullPass.root".format(forCondorStr)))
    nameAr.append("QCDPT170to300Background")
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
if QCDPT300to470Background:
    fileAr.append(TFile.Open("{0}FoMTreesFromQCDPT300to470Background_InputTrimmed_FullPass.root".format(forCondorStr)))
    nameAr.append("QCDPT300to470Background")
    isSignalAr.append(False)
    tmpXSAvg = 6826.0
    XSAr.append(tmpXSAvg)
    #tmpCZTree = fileAr[-1].cutZeroTree
    #totalEvents.append(tmpCZTree.GetEntries())
    ENTree = fileAr[-1].evNumTree
    evNum = 0
    for ev in ENTree:
        evNum = ev.nEv
    totalEvents.append(evNum)
if QCDPT470to600Background:
    fileAr.append(TFile.Open("{0}FoMTreesFromQCDPT470to600Background_InputTrimmed_FullPass.root".format(forCondorStr)))
    nameAr.append("QCDPT470to600Background")
    isSignalAr.append(False)
    tmpXSAvg = 552.6
    XSAr.append(tmpXSAvg)
    ENTree = fileAr[-1].evNumTree
    evNum = 0
    for ev in ENTree:
        evNum = ev.nEv
    totalEvents.append(evNum)
if QCDPT600to800Background:
    fileAr.append(TFile.Open("{0}FoMTreesFromQCDPT600to800Background_InputTrimmed_FullPass.root".format(forCondorStr)))
    nameAr.append("QCDPT600to800Background")
    isSignalAr.append(False)
    tmpXSAvg = 156.6
    XSAr.append(tmpXSAvg)
    ENTree = fileAr[-1].evNumTree
    evNum = 0
    for ev in ENTree:
        evNum = ev.nEv
    totalEvents.append(evNum)
if QCDPT800to1000Background:
    fileAr.append(TFile.Open("{0}FoMTreesFromQCDPT800to1000Background_InputTrimmed_FullPass.root".format(forCondorStr)))
    nameAr.append("QCDPT800to1000Background")
    isSignalAr.append(False)
    tmpXSAvg = 26.32
    XSAr.append(tmpXSAvg)
    ENTree = fileAr[-1].evNumTree
    evNum = 0
    for ev in ENTree:
        evNum = ev.nEv
    totalEvents.append(evNum)
if QCDPT1000to1400Background:
    fileAr.append(TFile.Open("{0}FoMTreesFromQCDPT1000to1400Background_InputTrimmed_FullPass.root".format(forCondorStr)))
    nameAr.append("QCDPT1000to1400Background")
    isSignalAr.append(False)
    tmpXSAvg = 7.5
    XSAr.append(tmpXSAvg)
    ENTree = fileAr[-1].evNumTree
    evNum = 0
    for ev in ENTree:
        evNum = ev.nEv
    totalEvents.append(evNum)
if QCDPT1400to1800Background:
    fileAr.append(TFile.Open("{0}FoMTreesFromQCDPT1400to1800Background_InputTrimmed_FullPass.root".format(forCondorStr)))
    nameAr.append("QCDPT1400to1800Background")
    isSignalAr.append(False)
    tmpXSAvg = 0.6479
    XSAr.append(tmpXSAvg)
    ENTree = fileAr[-1].evNumTree
    evNum = 0
    for ev in ENTree:
        evNum = ev.nEv
    totalEvents.append(evNum)
if QCDPT1800to2400Background:
    fileAr.append(TFile.Open("{0}FoMTreesFromQCDPT1800to2400Background_InputTrimmed_FullPass.root".format(forCondorStr)))
    nameAr.append("QCDPT1800to2400Background")
    isSignalAr.append(False)
    tmpXSAvg = 0.08715
    XSAr.append(tmpXSAvg)
    ENTree = fileAr[-1].evNumTree
    evNum = 0
    for ev in ENTree:
        evNum = ev.nEv
    totalEvents.append(evNum)
if QCDPT2400to3200Background:
    fileAr.append(TFile.Open("{0}FoMTreesFromQCDPT2400to3200Background_InputTrimmed_FullPass.root".format(forCondorStr)))
    nameAr.append("QCDPT2400to3200Background")
    isSignalAr.append(False)
    tmpXSAvg = 0.005242
    XSAr.append(tmpXSAvg)
    ENTree = fileAr[-1].evNumTree
    evNum = 0
    for ev in ENTree:
        evNum = ev.nEv
    totalEvents.append(evNum)
if QCDPT3200toInfBackground:
    fileAr.append(TFile.Open("{0}FoMTreesFromQCDPT3200toInfBackground_InputTrimmed_FullPass.root".format(forCondorStr)))
    nameAr.append("QCDPT3200toInfBackground")
    isSignalAr.append(False)
    tmpXSAvg = 0.0001349
    XSAr.append(tmpXSAvg)
    ENTree = fileAr[-1].evNumTree
    evNum = 0
    for ev in ENTree:
        evNum = ev.nEv
    totalEvents.append(evNum)



weightsAr = [tmpXS/tmpEvs for tmpXS,tmpEvs in zip(XSAr,totalEvents)]



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
optLepInvMassCut = 12
lepIsoCut = 0.35

cutAmnt = 50

SIPCut = 4
SIPRange = [0,5]

SIPStep = (SIPRange[1]-SIPRange[0])/cutAmnt
SIPSignalAr = [0 for i in range(cutAmnt)] 
SIPBackgroundAr = [0 for i in range(cutAmnt)] 


SIPEvPassGraphAr = []
for nameA in nameAr:
    SIPEvPassGraphAr.append(array('d'))

histSIPAr = []

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
    tmpSIPCntAr = [0 for cutItr in range(cutAmnt)]
    histSIPAr.append(TH1F("SIPHist{0}".format(nameAr[k]),"SIPHist{0}".format(nameAr[k]), cutAmnt, SIPRange[0], SIPRange[1]))
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
                            tmpTopSIP = max(max(Z1LeadSIP,Z1TrailingSIP),max(Z2LeadSIP,Z2TrailingSIP))
                            histSIPAr[-1].Fill(tmpTopSIP)
                            #histSIPAr[-1].Fill(Z1LeadSIP)
                            #histSIPAr[-1].Fill(Z1TrailingSIP)
                            #histSIPAr[-1].Fill(Z2LeadSIP)
                            #histSIPAr[-1].Fill(Z2TrailingSIP)
                            #Loop here
                            
                            

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
                                passesAllCutsCtr += 1
                                #allPassAr.append([j,ev.evInd])
                                allPassAr.append(ev.evInd)
                            """
                            




        """
        doeCandCut(ev,neLep,elecCandIndAr,elecCandVecAr,elecCandChargeAr,ePtCut,eEtaCut)

        domCandCut(ev,neLep,muonCandIndAr,muonCandVecAr,muonCandChargeAr,mPtCut,mEtaCut):

        doeZ1Cut(ev,elecCandIndAr,elecCandVecAr,elecCandChargeAr,elecPassesZ2CutsAr,Z1IsMuon,invMassCutLow,invMassCutHigh,ptLeadCut,ptTrailingCut,tmpTopZ1LeadPt,tmpTopZ1TrailingPt,difFromZMassOne)

        domZ1Cut(ev,muonCandIndAr,muonCandVecAr,muonCandChargeAr,muonPassesZ2CutsAr,Z1IsMuon,invMassCutLow,invMassCutHigh,ptLeadCut,ptTrailingCut,tmpTopZ1LeadPt,tmpTopZ1TrailingPt,difFromZMassOne)

        doeZ2Cut(ev,Z1LeadVec,Z1TrailingVec,tmpZ1Vec,Z1LeadCharge,Z1TrailingCharge,Z1IsMuon,eZ2VecPairAr,eZ2PtPairAr,eZ2ChargePairAr,tmpZ2Ind,Z2IsMuon,tmpTopZ2LeadPt,tmpTopZ2TrailingPt,fourLepInvMassCut,optLepInvMassCut)

        domZ2Cut(ev,Z1LeadVec,Z1TrailingVec,tmpZ1Vec,Z1LeadCharge,Z1TrailingCharge,Z1IsMuon,mZ2VecPairAr,mZ2PtPairAr,mZ2ChargePairAr,tmpZ2Ind,Z2IsMuon,tmpTopZ2LeadPt,tmpTopZ2TrailingPt,fourLepInvMassCut,optLepInvMassCut)

        doISOCut(Z1LeadIso,Z1TrailingIso,Z2LeadIso,Z2TrailingIso,lepIsoCut)

        doSIPCut(Z1LeadSIP,Z1TrailingSIP,Z2LeadSIP,Z2TrailingSIP,SIPCut)
        """
    for c in range(cutAmnt):
        SIPEvPassGraphAr[k].append(tmpSIPCntAr[c])
        if isSignalAr[k]:
            SIPSignalAr[c] += tmpSIPCntAr[c]*weightsAr[k]
        else:
            SIPBackgroundAr[c] += tmpSIPCntAr[c]*weightsAr[k]
#print(passesCandCutsCtr)
#print(passesZ1CutsCtr)
#print(passesZ2CutsCtr)
#print(passesIsoCutCtr)
#print(passesAllCutsCtr)
#print(allPassAr)

#print(SIPSignalAr)
#print(SIPBackgroundAr)

SIPGraphAr = array('d')
SIPXAr = array('d')
for c in range(cutAmnt):
    #SIP
    tmpSignal = SIPSignalAr[c]
    tmpBackground = SIPBackgroundAr[c]
    if tmpSignal > 0:
        if tmpBackground == 0:
            tmpFoM = tmpSignal/(sqrt(tmpSignal+tmpBackground))
        else:
            tmpFoM = sqrt(2*(((tmpSignal+tmpBackground)*log(1+(tmpSignal / tmpBackground)))-tmpSignal))
    else:
        tmpFoM = 0
    SIPGraphAr.append(tmpFoM)
    tmpX = SIPRange[0] + (SIPStep*c)
    SIPXAr.append(tmpX)

evPassSIPCanAr = []
evPassSIPGraphAr = []
print("Done.","time:",time.time()-startt)
for k,nameA in enumerate(nameAr):
    #print("-------------------")
    #print(len(SIPEvPassGraphAr[k]),SIPXAr,SIPEvPassGraphAr[k])
    evPassSIPCanAr.append(TCanvas("c1SIP{0}".format(nameA),"c1SIP{0}".format(nameA),3600,2400))
    evPassSIPGraphAr.append(TGraph(len(SIPEvPassGraphAr[k]),SIPXAr,SIPEvPassGraphAr[k]))
    setUpGraphs(evPassSIPGraphAr[-1],3,22,"Number of Passing Events Vs SIP Cut for {0}".format(nameA),"SIP","Events Passing First Cut")
    evPassSIPGraphAr[-1].Draw("APL")
    evPassSIPCanAr[-1].Draw()
    #"FP" stands for "Full Pass"
    evPassSIPCanAr[-1].SaveAs("evPassCutGraph_FP_SIP{0}_{1}.png".format(nameA,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))




padAr = []
legAr = []


signalName = ""
backgroundName = ""
for k,fileA in enumerate(fileAr):
    if isSignalAr[k]:
        signalName += "_"+nameAr[k]
    else:
        backgroundName += "_"+nameAr[k]
FOMSIPCan = TCanvas("c1SIP","c1SIP",3600,2400)
setUpLegend(legAr)
setUpPadsAr(padAr,"{0}Pad".format("SIP"))
padAr[-1][0].Draw()
padAr[-1][0].cd()
#Make top plot
intSIPAr = []
for j,colorA,nameA in zip(range(len(nameAr)),colorAr,nameAr):
    histSIPAr[j].SetLineColor(colorA)
    histSIPAr[j].SetLineWidth(3)
    if j == 0:
        makeNiceHistos(histSIPAr[j],"","Events",True)
        histSIPAr[j].SetTitle("SIP FoM Plot")
    intSIPAr.append(histSIPAr[j].Integral())

histMax = 0


for j in range(len(histSIPAr)):
    if intSIPAr[j]:
        histSIPAr[j].Scale(1.0 / intSIPAr[j])
        tmpMax = histSIPAr[j].GetMaximum()
        if tmpMax > histMax:
            histMax = tmpMax
        legAr[-1].AddEntry(histSIPAr[j],nameAr[j],"l")
histSIPAr[0].GetYaxis().SetRangeUser(0,histMax)
histSIPAr[0].Draw("hist")
for j in range(1,len(histSIPAr)):
    histSIPAr[j].DrawCopy("same hist")
legAr[-1].Draw()


FOMSIPCan.cd()

setUpBottomPadsAr(padAr[-1])
FOMSIPGraph = TGraph(len(SIPGraphAr),SIPXAr,SIPGraphAr)
setUpGraphs(FOMSIPGraph,3,22,"SIP FoM Plot","SIP","S/SQRT(S+B)")
FOMSIPGraph.GetXaxis().SetRangeUser(SIPRange[0],SIPRange[1])
FOMSIPGraph.Draw("APL same")
FOMSIPCan.Update()
#"FP" stands for "Full Pass"
FOMSIPCan.SaveAs("lepCutZeroFOMGraph_FP_SIP_{0}_Vs_{1}_AMSFoM_WithComparisonHist_{2}.png".format(signalName,backgroundName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))


"""
for j in range(1,len(altNormalizationAr)):
    altNormalizationAr[j].Sumw2()
    altNormalizationAr[j].Divide(altNormalizationAr[0])
    makeNiceHistos(altNormalizationAr[j],"","Ratio to EFT",False)
    tmpRatioMax = altNormalizationAr[j].GetMaximum()
    if tmpRatioMax > ratioMax:
        ratioMax = tmpRatioMax
if ratioMax > 4:
    altNormalizationAr[1].GetYaxis().SetRangeUser(0,4)
altNormalizationAr[1].SetLineWidth(2)
altNormalizationAr[1].Draw("et same")
for j in range(2,len(altNormalizationAr)):
    makeNiceHistos(altNormalizationAr[j],"","Ratio to EFT",False)
    altNormalizationAr[j].SetLineWidth(2)
    altNormalizationAr[j].Draw("et same")
canAr[-1].Update()
#Saving canvas

canAr[-1].SaveAs("{0}{1}_altNormalization.png".format(histName,saveString))
"""
"""
auto h2 = new TH2F("h2","My histogram",100,1,0,100,1,0);
ntuple->Draw("px:py >> h2");
gPad->SetLogz(true);
h2->Draw("COLZ");
for j,keyA,colorA,nameA,weightsA,skipC,useModifiedCoupling in zip(range(len(keysAr)),keysAr,colorAr,nameAr,weightsAr,skipCtr,useModifiedCouplingAr):
    tmpObjAr.append(keyA[i-skipC].ReadObj())
    tmpObjAr[-1].Scale(weightsA)
    tmpObjAr[-1].SetLineColor(colorA)
    tmpObjAr[-1].SetLineWidth(3)
    if j == 0:
        makeNiceHistos(tmpObjAr[-1],"","Events",True)
    tmpObjAr[-1].SetTitle(histName)
    legAr[-1].AddEntry(tmpObjAr[-1],nameA,"l")
    combinedHistInt += tmpObjAr[-1].Integral()
    altNormalizationAr.append(tmpObjAr[-1].Clone())
    altNormalizationIntAr.append(altNormalizationAr[-1].Integral())

histAr = []
for k,fileA in enumerate(fileAr):
    CTree = fileA.cutTree
    histAr.append(TH1F("SIPHist","SIPHist",400,0,10))
    
    CTree.Draw("SIP")
    histAr[-1].
"""




#################################

"""


CEHLTSignal = 0
CEHLTBackground = 0
CEHLTBaseVal = True
CMHLTSignal = 0
CMHLTBackground = 0
CMHLTBaseVal = True
CEMHLTSignal = 0
CEMHLTBackground = 0
CEMHLTBaseVal = True

cutAmnt = 400

CEPtRange = [0,100]
CEPtStep = (CEPtRange[1]-CEPtRange[0])/400
CEPtBaseVal = 7
CEPtSignalAr = [0 for i in range(cutAmnt)] 
CEPtBackgroundAr = [0 for i in range(cutAmnt)] 
CEEtaRange = [0,3]
CEEtaStep = (CEEtaRange[1]-CEEtaRange[0])/400
CEEtaBaseVal = 2.5
CEEtaSignalAr = [0 for i in range(cutAmnt)] 
CEEtaBackgroundAr = [0 for i in range(cutAmnt)]

CMPtRange = [0,100]
CMPtStep = (CMPtRange[1]-CMPtRange[0])/400
CMPtBaseVal = 5
CMPtSignalAr = [0 for i in range(cutAmnt)] 
CMPtBackgroundAr = [0 for i in range(cutAmnt)] 
CMEtaRange = [0,3]
CMEtaStep = (CMEtaRange[1]-CMEtaRange[0])/400
CMEtaBaseVal = 2.4
CMEtaSignalAr = [0 for i in range(cutAmnt)] 
CMEtaBackgroundAr = [0 for i in range(cutAmnt)] 


EEtaEvPassGraphAr = []
EPtEvPassGraphAr = []
MEtaEvPassGraphAr = []
MPtEvPassGraphAr = []
for nameA in nameAr:
    EEtaEvPassGraphAr.append(array('d'))
    EPtEvPassGraphAr.append(array('d'))
    MEtaEvPassGraphAr.append(array('d'))
    MPtEvPassGraphAr.append(array('d'))
#MAIN LOOP
for k,fileA in enumerate(fileAr):
    print("Entering file {0}".format(k))
    CZTree = fileA.cutTree
    tmpEEtaCntAr = [0 for i in range(cutAmnt)] 
    tmpEPtCntAr = [0 for i in range(cutAmnt)] 
    tmpMEtaCntAr = [0 for i in range(cutAmnt)] 
    tmpMPtCntAr = [0 for i in range(cutAmnt)] 
    #LOOP OVER EVENTS IN FILE k
    for j,ev in enumerate(CZTree):
        if j % 10000 == 0:
            print("event {0} in file {1}".format(j,k))
        
        tmpneLep = ev.neLep
        tmpnmLep = ev.nmLep
        #First cut: e pt


        nElecCandPairs = 0
        if tmpneLep >=2:
            nElecCandPairs = checkForElecCands(ev,tmpneLep)
        tmpnmLep = ev.nmLep
        nMuonCandPairs = 0
        if tmpnmLep >= 2:
            nMuonCandPairs = checkForMuonCands(ev,tmpnmLep)
        if debug and j >= debugMin and j < debugMax:
            print("j",j,"tmpneLep",tmpneLep,"tmpnmLep",tmpnmLep,"nElecCandPairs",nElecCandPairs,"nMuonCandPairs",nMuonCandPairs)

        if nElecCandPairs + nMuonCandPairs >= 2:
            if debug and j >= debugMin and j < debugMax:
                print("Event {0} qualified".format(j))
            #Event qualifies - going through default cuts
            defaultECandCnt = 0
            eEtaCutCandCntAr = [0 for i in range(cutAmnt)]
            ePtCutCandCntAr  = [0 for i in range(cutAmnt)]
            if nElecCandPairs >=1:
                #eEtaCutCandChargeCntAr = [[ePosCnt,eNegCnt] for i in range(cutAmnt)]
                #ePtCutCandChargeCntAr = [[ePosCnt,eNegCnt] for i in range(cutAmnt)]
                eEtaCutCandChargeCntAr = [[0,0] for i in range(cutAmnt)]
                
                ePtCutCandChargeCntAr  = [[0,0] for i in range(cutAmnt)]
                

                if ev.eHLT or ev.emHLT:
                    tmpPosCnt = 0
                    tmpNegCnt = 0
                    if debug and j >= debugMin and j < debugMax:
                        print("j",j,"passed eHLT")
                    for i in range(tmpneLep):
                        tmpeCharge = ev.eCharge[i]
                        if debug and j >= debugMin and j < debugMax:
                            print("j",j,"i",i,"tmpeCharge",tmpeCharge,"ev.ePt[i]",ev.ePt[i])
                        if ev.ePt[i] > CEPtBaseVal:
                            if abs(ev.eEta[i]) < CEEtaBaseVal:
                                if debug and j >= debugMin and j < debugMax:
                                    print("j",j,"i",i,"passed Eta and Pt Cuts","ev.eEta[i]",ev.eEta[i])
                                if tmpeCharge == 1:
                                    tmpPosCnt += 1
                                else:
                                    tmpNegCnt += 1
                            #Now looping over Eta cut
                            for c in range(cutAmnt):
                                tmpEtaCut = CEEtaRange[0] + (CEEtaStep*c)
                                if abs(ev.eEta[i]) < tmpEtaCut:
                                    if tmpeCharge == 1:
                                        eEtaCutCandChargeCntAr[c][0] += 1
                                    else:
                                        eEtaCutCandChargeCntAr[c][1] += 1
                        #Now looping over Pt cut
                        if abs(ev.eEta[i]) < CEEtaBaseVal:
                            for c in range(cutAmnt):
                                tmpPtCut = CEPtRange[0] + (CEPtStep*c)
                                if ev.ePt[i] > tmpPtCut:
                                    if tmpeCharge == 1:
                                        ePtCutCandChargeCntAr[c][0] += 1
                                    else:
                                        ePtCutCandChargeCntAr[c][1] += 1
                    if debug and j >= debugMin and j < debugMax:
                        print("j",j,"small Electron loop finished.","tmpPosCnt",tmpPosCnt,"tmpNegCnt",tmpNegCnt)
                    #Getting electron count for default cuts
                    if tmpNegCnt <= tmpPosCnt:
                        defaultECandCnt = tmpNegCnt
                    else:
                        defaultECandCnt = tmpPosCnt
                    #Getting electron count for each cut
                    for c in range(cutAmnt):
                        if eEtaCutCandChargeCntAr[c][0] <= eEtaCutCandChargeCntAr[c][1]:
                            eEtaCutCandCntAr[c] = eEtaCutCandChargeCntAr[c][0]
                        else:
                            eEtaCutCandCntAr[c] = eEtaCutCandChargeCntAr[c][1]
                        if ePtCutCandChargeCntAr[c][0] <= ePtCutCandChargeCntAr[c][1]:
                            ePtCutCandCntAr[c] = ePtCutCandChargeCntAr[c][0]
                        else:
                            ePtCutCandCntAr[c] = ePtCutCandChargeCntAr[c][1]
            if debug and j >= debugMin and j < debugMax:
                print("j",j,"Electron loop finished.","defaultECandCnt",defaultECandCnt)


            
            defaultMCandCnt = 0
            mEtaCutCandCntAr = [0 for i in range(cutAmnt)]
            mPtCutCandCntAr  = [0 for i in range(cutAmnt)]
            if nMuonCandPairs >=1:
                #mEtaCutCandChargeCntAr = [[ePosCnt,eNegCnt] for i in range(cutAmnt)]
                #mPtCutCandChargeCntAr = [[ePosCnt,eNegCnt] for i in range(cutAmnt)]
                mEtaCutCandChargeCntAr = [[0,0] for i in range(cutAmnt)]
                mPtCutCandChargeCntAr  = [[0,0] for i in range(cutAmnt)]
                

                if ev.mHLT or ev.emHLT:
                    tmpPosCnt = 0
                    tmpNegCnt = 0
                    for i in range(tmpnmLep):
                        tmpmCharge = ev.mCharge[i]
                        if ev.mPt[i] > CMPtBaseVal:
                            if abs(ev.mEta[i]) < CMEtaBaseVal:
                                if tmpmCharge == 1:
                                    tmpPosCnt += 1
                                else:
                                    tmpNegCnt += 1
                            #Now looping over Eta cut
                            for c in range(cutAmnt):
                                tmpEtaCut = CMEtaRange[0] + (CMEtaStep*c)
                                if abs(ev.mEta[i]) < tmpEtaCut:
                                    if tmpmCharge == 1:
                                        mEtaCutCandChargeCntAr[c][0] += 1
                                    else:
                                        mEtaCutCandChargeCntAr[c][1] += 1
                        #Now looping over Pt cut
                        if abs(ev.mEta[i]) < CMEtaBaseVal:
                            for c in range(cutAmnt):
                                tmpPtCut = CMPtRange[0] + (CMPtStep*c)
                                if ev.mPt[i] > tmpPtCut:
                                    if tmpmCharge == 1:
                                        mPtCutCandChargeCntAr[c][0] += 1
                                    else:
                                        mPtCutCandChargeCntAr[c][1] += 1
                    if debug and j >= debugMin and j < debugMax:
                        print("j",j,"small Muon loop finished.","tmpPosCnt",tmpPosCnt,"tmpNegCnt",tmpNegCnt)
                    #Getting muon count for default cuts
                    if tmpNegCnt <= tmpPosCnt:
                        defaultMCandCnt = tmpNegCnt
                    else:
                        defaultMCandCnt = tmpPosCnt
                    #Getting muon count for each cut
                    for c in range(cutAmnt):
                        if mEtaCutCandChargeCntAr[c][0] <= mEtaCutCandChargeCntAr[c][1]:
                            mEtaCutCandCntAr[c] = mEtaCutCandChargeCntAr[c][0]
                        else:
                            mEtaCutCandCntAr[c] = mEtaCutCandChargeCntAr[c][1]
                        if mPtCutCandChargeCntAr[c][0] <= mPtCutCandChargeCntAr[c][1]:
                            mPtCutCandCntAr[c] = mPtCutCandChargeCntAr[c][0]
                        else:
                            mPtCutCandCntAr[c] = mPtCutCandChargeCntAr[c][1]
            if debug and j >= debugMin and j < debugMax:
                print("j",j,"Muon loop finished.","defaultMCandCnt",defaultMCandCnt)
            
            #Filling temporary event count arrays
            for c in range(cutAmnt):
                #eEta
                if eEtaCutCandCntAr[c] + defaultMCandCnt >= 2:
                    tmpEEtaCntAr[c] += 1
                #ePt
                if ePtCutCandCntAr[c] + defaultMCandCnt >= 2:
                    tmpEPtCntAr[c] += 1
                #mEta
                if mEtaCutCandCntAr[c] + defaultECandCnt >= 2:
                    tmpMEtaCntAr[c] += 1
                #mPt
                if mPtCutCandCntAr[c] + defaultECandCnt >= 2:
                    tmpMPtCntAr[c] += 1
    #Weighting event counter and adding to main arrays
    #print("FOR DATASET:",nameAr[k])
    #print("tmpEEtaCntAr",tmpEEtaCntAr)
    for c in range(cutAmnt):
        EEtaEvPassGraphAr[k].append(tmpEEtaCntAr[c])
        EPtEvPassGraphAr[k].append(tmpEPtCntAr[c])
        MEtaEvPassGraphAr[k].append(tmpMEtaCntAr[c])
        MPtEvPassGraphAr[k].append(tmpMPtCntAr[c])
        if isSignalAr[k]:
            CEEtaSignalAr[c] = tmpEEtaCntAr[c]*weightsAr[k]
            CEPtSignalAr[c] = tmpEPtCntAr[c]*weightsAr[k]
            CMEtaSignalAr[c] = tmpMEtaCntAr[c]*weightsAr[k]
            CMPtSignalAr[c] = tmpMPtCntAr[c]*weightsAr[k]
        else:
            CEEtaBackgroundAr[c] = tmpEEtaCntAr[c]*weightsAr[k]
            CEPtBackgroundAr[c] = tmpEPtCntAr[c]*weightsAr[k]
            CMEtaBackgroundAr[c] = tmpMEtaCntAr[c]*weightsAr[k]
            CMPtBackgroundAr[c] = tmpMPtCntAr[c]*weightsAr[k]
    #print("EEtaEvPassGraphAr[k]",EEtaEvPassGraphAr[k])
"""
#    """
"""
    if isSignalAr[k]:
        for c in range(cutAmnt):
            CEEtaSignalAr[c] = tmpEEtaCntAr[c]*weightsAr[k]
            CEPtSignalAr[c] = tmpEPtCntAr[c]*weightsAr[k]
            CMEtaSignalAr[c] = tmpMEtaCntAr[c]*weightsAr[k]
            CMPtSignalAr[c] = tmpMPtCntAr[c]*weightsAr[k]
    else:
        for c in range(cutAmnt):
            CEEtaBackgroundAr[c] = tmpEEtaCntAr[c]*weightsAr[k]
            CEPtBackgroundAr[c] = tmpEPtCntAr[c]*weightsAr[k]
            CMEtaBackgroundAr[c] = tmpMEtaCntAr[c]*weightsAr[k]
            CMPtBackgroundAr[c] = tmpMPtCntAr[c]*weightsAr[k]
"""
#    """
"""
print("EETA:")
for c,signalCnt,backgroundCnt in zip(range(len(CEEtaSignalAr)),CEEtaSignalAr,CEEtaBackgroundAr):
    tmpEtaCut = CEEtaRange[0] + (CEEtaStep*c)
    if signalCnt > 0:
        tmpFoM = signalCnt/(sqrt(signalCnt+backgroundCnt))
        tmpFoMAlt = sqrt(2*(((signalCnt+backgroundCnt)*log(1+(signalCnt / backgroundCnt)))-signalCnt))
    else:
        tmpFoM = 0
        tmpFoMAlt = 0
    print(c,"{:0.4f}".format(tmpEtaCut),"{:0.4e}".format(signalCnt),"{:0.4e}".format(backgroundCnt),"{:0.4e}".format(tmpFoM),"{:0.4e}".format(tmpFoMAlt))

print("-----------------------------------------")
print("EPT:")

for c,signalCnt,backgroundCnt in zip(range(len(CEPtSignalAr)),CEPtSignalAr,CEPtBackgroundAr):
    tmpPtCut = CEPtRange[0] + (CEPtStep*c)
    if signalCnt > 0:
        tmpFoM = signalCnt/(sqrt(signalCnt+backgroundCnt))
    else:
        tmpFoM = 0
    print(c,"{:0.4f}".format(tmpPtCut),"{:0.4e}".format(signalCnt),"{:0.4e}".format(backgroundCnt),"{:0.4e}".format(tmpFoM))

print("-----------------------------------------")
print("META")

for c,signalCnt,backgroundCnt in zip(range(len(CMEtaSignalAr)),CMEtaSignalAr,CMEtaBackgroundAr):
    tmpEtaCut = CMEtaRange[0] + (CMEtaStep*c)
    if signalCnt > 0:
        tmpFoM = signalCnt/(sqrt(signalCnt+backgroundCnt))
    else:
        tmpFoM = 0
    print(c,"{:0.4f}".format(tmpEtaCut),"{:0.4e}".format(signalCnt),"{:0.4e}".format(backgroundCnt),"{:0.4e}".format(tmpFoM))

print("-----------------------------------------")
print("MPT")

for c,signalCnt,backgroundCnt in zip(range(len(CMPtSignalAr)),CMPtSignalAr,CMPtBackgroundAr):
    tmpPtCut = CMPtRange[0] + (CMPtStep*c)
    if signalCnt > 0:
        tmpFoM = signalCnt/(sqrt(signalCnt+backgroundCnt))
    else:
        tmpFoM = 0
    print(c,"{:0.4f}".format(tmpPtCut),"{:0.4e}".format(signalCnt),"{:0.4e}".format(backgroundCnt),"{:0.4e}".format(tmpFoM))
print("Done.","time:",time.time()-startt)

EEtaGraphAr = array('d')
EEtaXAr = array('d')
EPtGraphAr = array('d')
EPtXAr = array('d')
MEtaGraphAr = array('d')
MEtaXAr = array('d')
MPtGraphAr = array('d')
MPtXAr = array('d')
for c in range(cutAmnt):
    #EEta
    tmpSignal = CEEtaSignalAr[c]
    tmpBackground = CEEtaBackgroundAr[c]
    if tmpSignal > 0:
        #tmpFoM = tmpSignal/(sqrt(tmpSignal+tmpBackground))
        tmpFoM = sqrt(2*(((tmpSignal+tmpBackground)*log(1+(tmpSignal / tmpBackground)))-tmpSignal))
    else:
        tmpFoM = 0
    EEtaGraphAr.append(tmpFoM)
    tmpX = CEEtaRange[0] + (CEEtaStep*c)
    EEtaXAr.append(tmpX)
    #EPt
    tmpSignal = CEPtSignalAr[c]
    tmpBackground = CEPtBackgroundAr[c]
    if tmpSignal > 0:
        #tmpFoM = tmpSignal/(sqrt(tmpSignal+tmpBackground))
        tmpFoM = sqrt(2*(((tmpSignal+tmpBackground)*log(1+(tmpSignal / tmpBackground)))-tmpSignal))
    else:
        tmpFoM = 0
    EPtGraphAr.append(tmpFoM)
    tmpX = CEPtRange[0] + (CEPtStep*c)
    EPtXAr.append(tmpX)
    #MEta
    tmpSignal = CMEtaSignalAr[c]
    tmpBackground = CMEtaBackgroundAr[c]
    if tmpSignal > 0:
        #tmpFoM = tmpSignal/(sqrt(tmpSignal+tmpBackground))
        tmpFoM = sqrt(2*(((tmpSignal+tmpBackground)*log(1+(tmpSignal / tmpBackground)))-tmpSignal))
    else:
        tmpFoM = 0
    MEtaGraphAr.append(tmpFoM)
    tmpX = CMEtaRange[0] + (CMEtaStep*c)
    MEtaXAr.append(tmpX)
    #MPt
    tmpSignal = CMPtSignalAr[c]
    tmpBackground = CMPtBackgroundAr[c]
    if tmpSignal > 0:
        #tmpFoM = tmpSignal/(sqrt(tmpSignal+tmpBackground))
        tmpFoM = sqrt(2*(((tmpSignal+tmpBackground)*log(1+(tmpSignal / tmpBackground)))-tmpSignal))
    else:
        tmpFoM = 0
    MPtGraphAr.append(tmpFoM)
    tmpX = CMPtRange[0] + (CMPtStep*c)
    MPtXAr.append(tmpX)


signalName = ""
backgroundName = ""
for k,fileA in enumerate(fileAr):
    if isSignalAr[k]:
        signalName += "_"+nameAr[k]
    else:
        backgroundName += "_"+nameAr[k]
evPassEEtaCanAr = []
evPassEPtCanAr = []
evPassMEtaCanAr = []
evPassMPtCanAr = []
evPassEEtaGraphAr = []
evPassEPtGraphAr = []
evPassMEtaGraphAr = []
evPassMPtGraphAr = []
for k,nameA in enumerate(nameAr):
    #print("nameA",nameA,"EEtaEvPassGraphAr[k]",EEtaEvPassGraphAr[k])
    evPassEEtaCanAr.append(TCanvas("c1EEta{0}".format(nameA),"c1EEta{0}".format(nameA),3600,2400))
    evPassEEtaGraphAr.append(TGraph(len(EEtaEvPassGraphAr[k]),EEtaXAr,EEtaEvPassGraphAr[k]))
    #evPassEEtaGraphAr[-1].SetTitle("Number of Passing Events Vs Electron Eta Cut for {0}".format(nameA))
    #evPassEEtaGraphAr[-1].GetXaxis().SetTitle("Eta")
    #evPassEEtaGraphAr[-1].GetYaxis().SetTitle("Events Passing First Cut")
    setUpGraphs(evPassEEtaGraphAr[-1],3,22,"Number of Passing Events Vs Electron Eta Cut for {0}".format(nameA),"Eta","Events Passing First Cut")
    evPassEEtaGraphAr[-1].Draw("APL")
    evPassEEtaCanAr[-1].Draw()
    evPassEEtaCanAr[-1].SaveAs("evPassCutZeroGraphEEta{0}_{1}.png".format(nameA,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
    
    evPassEPtCanAr.append(TCanvas("c1EPt{0}".format(nameA),"c1EPt{0}".format(nameA),3600,2400))
    evPassEPtGraphAr.append(TGraph(len(EPtEvPassGraphAr[k]),EPtXAr,EPtEvPassGraphAr[k]))
    #evPassEPtGraphAr[-1].SetTitle("Number of Passing Events Vs Electron Pt Cut for {0}".format(nameA))
    #evPassEPtGraphAr[-1].GetXaxis().SetTitle("Pt")
    #evPassEPtGraphAr[-1].GetYaxis().SetTitle("Events Passing First Cut")
    setUpGraphs(evPassEPtGraphAr[-1],3,22,"Number of Passing Events Vs Electron Pt Cut for {0}".format(nameA),"Pt (GeV)","Events Passing First Cut")
    evPassEPtGraphAr[-1].Draw("APL")
    evPassEPtCanAr[-1].Draw()
    evPassEPtCanAr[-1].SaveAs("evPassCutZeroGraphEPt{0}_{1}.png".format(nameA,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))


    evPassMEtaCanAr.append(TCanvas("c1MEta{0}".format(nameA),"c1MEta{0}".format(nameA),3600,2400))
    evPassMEtaGraphAr.append(TGraph(len(MEtaEvPassGraphAr[k]),MEtaXAr,MEtaEvPassGraphAr[k]))
    #evPassMEtaGraphAr[-1].SetTitle("Number of Passing Events Vs Muon Eta Cut for {0}".format(nameA))
    #evPassMEtaGraphAr[-1].GetXaxis().SetTitle("Eta")
    #evPassMEtaGraphAr[-1].GetYaxis().SetTitle("Events Passing First Cut")
    setUpGraphs(evPassMEtaGraphAr[-1],3,22,"Number of Passing Events Vs Muon Eta Cut for {0}".format(nameA),"Eta","Events Passing First Cut")
    evPassMEtaGraphAr[-1].Draw("APL")
    evPassMEtaCanAr[-1].Draw()
    evPassMEtaCanAr[-1].SaveAs("evPassCutZeroGraphMEta{0}_{1}.png".format(nameA,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))


    evPassMPtCanAr.append(TCanvas("c1MPt{0}".format(nameA),"c1MPt{0}".format(nameA),3600,2400))
    evPassMPtGraphAr.append(TGraph(len(MPtEvPassGraphAr[k]),MPtXAr,MPtEvPassGraphAr[k]))
    #evPassMPtGraphAr[-1].SetTitle("Number of Passing Events Vs Muon Pt Cut for {0}".format(nameA))
    #evPassMPtGraphAr[-1].GetXaxis().SetTitle("Pt")
    #evPassMPtGraphAr[-1].GetYaxis().SetTitle("Events Passing First Cut")
    setUpGraphs(evPassMPtGraphAr[-1],3,22,"Number of Passing Events Vs Muon Pt Cut for {0}".format(nameA),"Pt (GeV)","Events Passing First Cut")
    evPassMPtGraphAr[-1].Draw("APL")
    evPassMPtCanAr[-1].Draw()
    evPassMPtCanAr[-1].SaveAs("evPassCutZeroGraphMPt{0}_{1}.png".format(nameA,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
    



FOMEEtaCan = TCanvas("c1EEta","c1EEta",3600,2400)
FOMEEtaGraph = TGraph(len(EEtaGraphAr),EEtaXAr,EEtaGraphAr)
#FOMEEtaGraph.SetTitle("Electron Eta FoM Plot")
#FOMEEtaGraph.GetXaxis().SetTitle("Eta")
#FOMEEtaGraph.GetYaxis().SetTitle("S/SQRT(S+B)")
setUpGraphs(FOMEEtaGraph,3,22,"Electron Eta FoM Plot","Eta","S/SQRT(S+B)")
FOMEEtaGraph.Draw("APL")
FOMEEtaCan.Draw()
FOMEEtaCan.SaveAs("lepCutZeroFOMGraphEEta{0}_Vs_{1}_AMSFoM_{2}.png".format(signalName,backgroundName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))


FOMEPtCan = TCanvas("c1EPt","c1EPt",3600,2400)
FOMEPtGraph = TGraph(len(EPtGraphAr),EPtXAr,EPtGraphAr)
#FOMEPtGraph.SetTitle("Electron Pt FoM Plot")
#FOMEPtGraph.GetXaxis().SetTitle("Pt (GeV)")
#FOMEPtGraph.GetYaxis().SetTitle("S/SQRT(S+B)")
setUpGraphs(FOMEPtGraph,3,22,"Electron Pt FoM Plot","Pt (GeV)","S/SQRT(S+B)")
FOMEPtGraph.Draw("APL")
FOMEPtCan.Draw()
FOMEPtCan.SaveAs("lepCutZeroFOMGraphEPt{0}_Vs_{1}_AMSFoM_{2}.png".format(signalName,backgroundName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))


FOMMEtaCan = TCanvas("c1MEta","c1MEta",3600,2400)
FOMMEtaGraph = TGraph(len(MEtaGraphAr),MEtaXAr,MEtaGraphAr)
#FOMMEtaGraph.SetTitle("Muon Eta FoM Plot")
#FOMMEtaGraph.GetXaxis().SetTitle("Eta")
#FOMMEtaGraph.GetYaxis().SetTitle("S/SQRT(S+B)")
setUpGraphs(FOMMEtaGraph,3,22,"Muon Eta FoM Plot","Eta","S/SQRT(S+B)")
FOMMEtaGraph.Draw("APL")
FOMMEtaCan.Draw()
FOMMEtaCan.SaveAs("lepCutZeroFOMGraphMEta{0}_Vs_{1}_AMSFoM_{2}.png".format(signalName,backgroundName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))


FOMMPtCan = TCanvas("c1MPt","c1MPt",3600,2400)
FOMMPtGraph = TGraph(len(MPtGraphAr),MPtXAr,MPtGraphAr)
#FOMMPtGraph.SetTitle("Muon Pt FoM Plot")
#FOMMPtGraph.GetXaxis().SetTitle("Pt (GeV)")
#FOMMPtGraph.GetYaxis().SetTitle("S/SQRT(S+B)")
setUpGraphs(FOMMPtGraph,3,22,"Muon Pt FoM Plot","Pt (GeV)","S/SQRT(S+B)")
FOMMPtGraph.Draw("APL")
FOMMPtCan.Draw()
FOMMPtCan.SaveAs("lepCutZeroFOMGraphMPt{0}_Vs_{1}_AMSFoM_{2}.png".format(signalName,backgroundName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))

"""



""" 

        #CUT ZERO
        #First getting which events pass for each cut
        #First cut obviously has all events before it
        #EOrEMHLT cut
        if ev.eHLT or ev.emHLT:
            EvPassEOrEMHLTCutIndAr.append(j)
            #Now the PT cut




    #First HLT or not comparison



    #Loop for Electron Pt



#signalEventsPassAr =[64,59,54,20,2] #SM
signalEventsPassUnweightedAr =[96,85,79,39,4] #EFT
signalEventsPassWeightedAr = [signalEventsPass*weightsAr[0] for signalEventsPass in signalEventsPassUnweightedAr]
backgroundEventsPassUnweightedAr = [20,8,2,0,0]
backgroundEventsPassWeightedAr = [backgroundEventsPass*weightsAr[1] for backgroundEventsPass in backgroundEventsPassUnweightedAr]
graphArray = array('d')
cutLvlAr = array('d')
cutLvlCtr = 1

if weightedBool:
    signalEventsPassAr = signalEventsPassWeightedAr
    backgroundEventsPassAr = backgroundEventsPassWeightedAr
else:
    signalEventsPassAr = signalEventsPassUnweightedAr
    backgroundEventsPassAr = backgroundEventsPassUnweightedAr
for signalEventsPass,backgroundEventsPass in zip(signalEventsPassAr,backgroundEventsPassAr):
    
    if sqrtSBool:
        graphArray.append(sqrt(signalEventsPass)/sqrt(signalEventsPass+backgroundEventsPass))
    else:
        graphArray.append(signalEventsPass/sqrt(signalEventsPass+backgroundEventsPass))
    
    cutLvlAr.append(cutLvlCtr)
    cutLvlCtr += 1

FOMGraph = r.TGraph(len(graphArray),cutLvlAr,graphArray)

if sqrtSBool:
    setUpGraphs(FOMGraph,3,22,"Sqrt of Signal Over the Sqrt of Signal Plus Background for Five Different Levels of Cut","Cut Level","sqrt(s/(s+b))")
else:
    setUpGraphs(FOMGraph,3,22,"Signal Over the Sqrt of Signal Plus Background for Five Different Levels of Cut","Cut Level","s/sqrt(s+b)")

FOMCan = r.TCanvas()

FOMGraph.Draw("APL")
FOMCan.Draw()
if sqrtSBool:
    if weightedBool:
        FOMCan.SaveAs("lepCutFOMGraphSqrtSWeightedEFTVsttHToBBBackground{0}.png".format("{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
    else:
        FOMCan.SaveAs("lepCutFOMGraphSqrtSEFTVsttHToBBBackground{0}.png".format("{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
else:
    if weightedBool:
        FOMCan.SaveAs("lepCutFOMGraphWeightedEFTVsttHToBBBackground{0}.png".format("{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
    else:
        FOMCan.SaveAs("lepCutFOMGraphEFTVsttHToBBBackground{0}.png".format("{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))

"""