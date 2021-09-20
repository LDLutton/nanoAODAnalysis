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

#Extra output at end and for each file
extraOut = False

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

weightsAr = [tmpXS/tmpEvs for tmpXS,tmpEvs in zip(XSAr,totalEvents)]

cutAmnt = 50

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


ZMass = 91.1876
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


#fileAr.append(TFile.Open("FoMTreesFrompphzzjjQCD0SMHLOOP0NPE1NPcHWE1QEDE5ResMasAllVer100Ev_0p999cHW100GeVIMJetCut_InputTrimmed_FullPass.root"))
#isSignalAr.append(True)
#fileAr.append(TFile.Open("FoMTreesFrompphzzjjQCD0SMHLOOP0QEDE5NPE0ResMasAllVer100Ev_0p999cHW100GeVIMJetCut_InputTrimmed_FullPass.root"))
#isSignalAr.append(False)

#################################BUILDING NEW LOOP HERE

#MAIN LOOP
for k,fileA in enumerate(fileAr):
    print("Entering file {0}".format(k))
    CTree = fileA.cutTree
    tmpZ1InvMassCutLowCntAr = [0 for cutItr in range(cutAmnt)]
    histZ1InvMassCutLowAr.append(TH1F("Z1InvMassCutLowHist{0}".format(nameAr[k]),"Z1InvMassCutLowHist{0}".format(nameAr[k]), cutAmnt, Z1InvMassCutLowRange[0], Z1InvMassCutLowRange[1]))
    tmpZ1InvMassCutHighCntAr = [0 for cutItr in range(cutAmnt)]
    histZ1InvMassCutHighAr.append(TH1F("Z1InvMassCutHighHist{0}".format(nameAr[k]),"Z1InvMassCutHighHist{0}".format(nameAr[k]), cutAmnt, Z1InvMassCutHighRange[0], Z1InvMassCutHighRange[1]))
    tmpZ1PtCutLowCntAr = [0 for cutItr in range(cutAmnt)]
    histZ1PtCutLowAr.append(TH1F("Z1PtCutLowHist{0}".format(nameAr[k]),"Z1PtCutLowHist{0}".format(nameAr[k]), cutAmnt, Z1PtCutLowRange[0], Z1PtCutLowRange[1]))
    tmpZ1PtCutHighCntAr = [0 for cutItr in range(cutAmnt)]
    histZ1PtCutHighAr.append(TH1F("Z1PtCutHighHist{0}".format(nameAr[k]),"Z1PtCutHighHist{0}".format(nameAr[k]), cutAmnt, Z1PtCutHighRange[0], Z1PtCutHighRange[1]))
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
                    
                    Z1LeadItr,Z1TrailingItr,Z1LeadPt,Z1TrailingPt,Z1LeadVec,Z1TrailingVec,Z1LeadCharge,Z1TrailingCharge,Z1IsMuon,difFromZMassOne = doeZ1Cut(ev,elecCandIndAr,elecCandVecAr,elecCandChargeAr,elecPassesZ2CutsAr,Z1IsMuon,invMassCutLow,tmpZ1InvMassCutHigh,ptLeadCut,ptTrailingCut,Z1LeadPt,Z1TrailingPt,Z1LeadItr,Z1TrailingItr,Z1LeadVec,Z1TrailingVec,Z1LeadCharge,Z1TrailingCharge,difFromZMassOne)
                muonPassesZ2CutsAr = []
                if enoughMuonCands: #If enough muon cands, run Z1 cuts
                    
                    Z1LeadItr,Z1TrailingItr,Z1LeadPt,Z1TrailingPt,Z1LeadVec,Z1TrailingVec,Z1LeadCharge,Z1TrailingCharge,Z1IsMuon,difFromZMassOne = domZ1Cut(ev,muonCandIndAr,muonCandVecAr,muonCandChargeAr,muonPassesZ2CutsAr,Z1IsMuon,invMassCutLow,tmpZ1InvMassCutHigh,ptLeadCut,ptTrailingCut,Z1LeadPt,Z1TrailingPt,Z1LeadItr,Z1TrailingItr,Z1LeadVec,Z1TrailingVec,Z1LeadCharge,Z1TrailingCharge,difFromZMassOne)
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

Z1InvMassCutLowGraphAr = array('d')
Z1InvMassCutLowXAr = array('d')
Z1InvMassCutHighGraphAr = array('d')
Z1InvMassCutHighXAr = array('d')
Z1PtCutLowGraphAr = array('d')
Z1PtCutLowXAr = array('d')
Z1PtCutHighGraphAr = array('d')
Z1PtCutHighXAr = array('d')
for c in range(cutAmnt):
    #Z1InvMassCutLow
    tmpSignal = Z1InvMassCutLowSignalAr[c]
    tmpBackground = Z1InvMassCutLowBackgroundAr[c]
    if tmpSignal > 0:
        if tmpBackground == 0:
            tmpFoM = tmpSignal/(sqrt(tmpSignal+tmpBackground))
        else:
            tmpFoM = sqrt(2*(((tmpSignal+tmpBackground)*log(1+(tmpSignal / tmpBackground)))-tmpSignal))
    else:
        tmpFoM = 0
    Z1InvMassCutLowGraphAr.append(tmpFoM)
    tmpX = Z1InvMassCutLowRange[0] + (Z1InvMassCutLowStep*c)
    Z1InvMassCutLowXAr.append(tmpX)

    #Z1InvMassCutHigh
    tmpSignal = Z1InvMassCutHighSignalAr[c]
    tmpBackground = Z1InvMassCutHighBackgroundAr[c]
    if tmpSignal > 0:
        if tmpBackground == 0:
            tmpFoM = tmpSignal/(sqrt(tmpSignal+tmpBackground))
        else:
            tmpFoM = sqrt(2*(((tmpSignal+tmpBackground)*log(1+(tmpSignal / tmpBackground)))-tmpSignal))
    else:
        tmpFoM = 0
    Z1InvMassCutHighGraphAr.append(tmpFoM)
    tmpX = Z1InvMassCutHighRange[0] + (Z1InvMassCutHighStep*c)
    Z1InvMassCutHighXAr.append(tmpX)


    #Z1PtCutLow
    tmpSignal = Z1PtCutLowSignalAr[c]
    tmpBackground = Z1PtCutLowBackgroundAr[c]
    if tmpSignal > 0:
        if tmpBackground == 0:
            tmpFoM = tmpSignal/(sqrt(tmpSignal+tmpBackground))
        else:
            tmpFoM = sqrt(2*(((tmpSignal+tmpBackground)*log(1+(tmpSignal / tmpBackground)))-tmpSignal))
    else:
        tmpFoM = 0
    Z1PtCutLowGraphAr.append(tmpFoM)
    tmpX = Z1PtCutLowRange[0] + (Z1PtCutLowStep*c)
    Z1PtCutLowXAr.append(tmpX)

    #Z1PtCutHigh
    tmpSignal = Z1PtCutHighSignalAr[c]
    tmpBackground = Z1PtCutHighBackgroundAr[c]
    if tmpSignal > 0:
        if tmpBackground == 0:
            tmpFoM = tmpSignal/(sqrt(tmpSignal+tmpBackground))
        else:
            tmpFoM = sqrt(2*(((tmpSignal+tmpBackground)*log(1+(tmpSignal / tmpBackground)))-tmpSignal))
    else:
        tmpFoM = 0
    Z1PtCutHighGraphAr.append(tmpFoM)
    tmpX = Z1PtCutHighRange[0] + (Z1PtCutHighStep*c)
    Z1PtCutHighXAr.append(tmpX)


if extraOut:
    print(Z1InvMassCutLowGraphAr)
    print(Z1InvMassCutHighGraphAr)
    print(Z1PtCutLowGraphAr)
    print(Z1PtCutHighGraphAr)

evPassZ1InvMassCutLowCanAr = []
evPassZ1InvMassCutLowGraphAr = []
evPassZ1InvMassCutHighCanAr = []
evPassZ1InvMassCutHighGraphAr = []
evPassZ1PtCutLowCanAr = []
evPassZ1PtCutLowGraphAr = []
evPassZ1PtCutHighCanAr = []
evPassZ1PtCutHighGraphAr = []
print("Done.","time:",time.time()-startt)
for k,nameA in enumerate(nameAr):
    #print("-------------------")
    #print(len(Z1InvMassCutLowEvPassGraphAr[k]),Z1InvMassCutLowXAr,Z1InvMassCutLowEvPassGraphAr[k])
    evPassZ1InvMassCutLowCanAr.append(TCanvas("c1Z1InvMassCutLow{0}".format(nameA),"c1Z1InvMassCutLow{0}".format(nameA),3600,2400))
    evPassZ1InvMassCutLowGraphAr.append(TGraph(len(Z1InvMassCutLowEvPassGraphAr[k]),Z1InvMassCutLowXAr,Z1InvMassCutLowEvPassGraphAr[k]))
    setUpGraphs(evPassZ1InvMassCutLowGraphAr[-1],3,22,"Number of Passing Events Vs Z1InvMassCutLow Cut for {0}".format(nameA),"Z1InvMassCutLow","Events Passing First Cut")
    evPassZ1InvMassCutLowGraphAr[-1].Draw("APL")
    evPassZ1InvMassCutLowCanAr[-1].Draw()
    #"FP" stands for "Full Pass"
    evPassZ1InvMassCutLowCanAr[-1].SaveAs("evPassCutGraph_FP_Z1InvMassCutLow{0}_{1}.png".format(nameA,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))

    #print("-------------------")
    #print(len(Z1InvMassCutHighEvPassGraphAr[k]),Z1InvMassCutHighXAr,Z1InvMassCutHighEvPassGraphAr[k])
    evPassZ1InvMassCutHighCanAr.append(TCanvas("c1Z1InvMassCutHigh{0}".format(nameA),"c1Z1InvMassCutHigh{0}".format(nameA),3600,2400))
    evPassZ1InvMassCutHighGraphAr.append(TGraph(len(Z1InvMassCutHighEvPassGraphAr[k]),Z1InvMassCutHighXAr,Z1InvMassCutHighEvPassGraphAr[k]))
    setUpGraphs(evPassZ1InvMassCutHighGraphAr[-1],3,22,"Number of Passing Events Vs Z1InvMassCutHigh Cut for {0}".format(nameA),"Z1InvMassCutHigh","Events Passing First Cut")
    evPassZ1InvMassCutHighGraphAr[-1].Draw("APL")
    evPassZ1InvMassCutHighCanAr[-1].Draw()
    #"FP" stands for "Full Pass"
    evPassZ1InvMassCutHighCanAr[-1].SaveAs("evPassCutGraph_FP_Z1InvMassCutHigh{0}_{1}.png".format(nameA,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))

    #print("-------------------")
    #print(len(Z1PtCutLowEvPassGraphAr[k]),Z1PtCutLowXAr,Z1PtCutLowEvPassGraphAr[k])
    evPassZ1PtCutLowCanAr.append(TCanvas("c1Z1PtCutLow{0}".format(nameA),"c1Z1PtCutLow{0}".format(nameA),3600,2400))
    evPassZ1PtCutLowGraphAr.append(TGraph(len(Z1PtCutLowEvPassGraphAr[k]),Z1PtCutLowXAr,Z1PtCutLowEvPassGraphAr[k]))
    setUpGraphs(evPassZ1PtCutLowGraphAr[-1],3,22,"Number of Passing Events Vs Z1PtCutLow Cut for {0}".format(nameA),"Z1PtCutLow","Events Passing First Cut")
    evPassZ1PtCutLowGraphAr[-1].Draw("APL")
    evPassZ1PtCutLowCanAr[-1].Draw()
    #"FP" stands for "Full Pass"
    evPassZ1PtCutLowCanAr[-1].SaveAs("evPassCutGraph_FP_Z1PtCutLow{0}_{1}.png".format(nameA,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))

    #print("-------------------")
    #print(len(Z1PtCutHighEvPassGraphAr[k]),Z1PtCutHighXAr,Z1PtCutHighEvPassGraphAr[k])
    evPassZ1PtCutHighCanAr.append(TCanvas("c1Z1PtCutHigh{0}".format(nameA),"c1Z1PtCutHigh{0}".format(nameA),3600,2400))
    evPassZ1PtCutHighGraphAr.append(TGraph(len(Z1PtCutHighEvPassGraphAr[k]),Z1PtCutHighXAr,Z1PtCutHighEvPassGraphAr[k]))
    setUpGraphs(evPassZ1PtCutHighGraphAr[-1],3,22,"Number of Passing Events Vs Z1PtCutHigh Cut for {0}".format(nameA),"Z1PtCutHigh","Events Passing First Cut")
    evPassZ1PtCutHighGraphAr[-1].Draw("APL")
    evPassZ1PtCutHighCanAr[-1].Draw()
    #"FP" stands for "Full Pass"
    evPassZ1PtCutHighCanAr[-1].SaveAs("evPassCutGraph_FP_Z1PtCutHigh{0}_{1}.png".format(nameA,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))





padAr = []
legAr = []


signalName = ""
backgroundName = ""
for k,fileA in enumerate(fileAr):
    if isSignalAr[k]:
        #signalName += "_"+nameAr[k]
        signalName += "_"+saveNameAr[k]
    else:
        #backgroundName += "_"+nameAr[k]
        backgroundName += "_"+saveNameAr[k]
FOMZ1InvMassCutLowCan = TCanvas("c1Z1InvMassCutLow","c1Z1InvMassCutLow",3600,2400)
setUpLegend(legAr)
setUpPadsAr(padAr,"{0}Pad".format("Z1InvMassCutLow"))
padAr[-1][0].Draw()
padAr[-1][0].cd()
#Make top plot
intZ1InvMassCutLowAr = []
for j,colorA,nameA in zip(range(len(nameAr)),colorAr,nameAr):
    histZ1InvMassCutLowAr[j].SetLineColor(colorA)
    histZ1InvMassCutLowAr[j].SetLineWidth(3)
    if j == 0:
        makeNiceHistos(histZ1InvMassCutLowAr[j],"","Events",True)
        histZ1InvMassCutLowAr[j].SetTitle("Z1InvMassCutLow FoM Plot")
    intZ1InvMassCutLowAr.append(histZ1InvMassCutLowAr[j].Integral())

histMax = 0


for j in range(len(histZ1InvMassCutLowAr)):
    if intZ1InvMassCutLowAr[j]:
        histZ1InvMassCutLowAr[j].Scale(1.0 / intZ1InvMassCutLowAr[j])
        tmpMax = histZ1InvMassCutLowAr[j].GetMaximum()
        if tmpMax > histMax:
            histMax = tmpMax
        legAr[-1].AddEntry(histZ1InvMassCutLowAr[j],nameAr[j],"l")
histZ1InvMassCutLowAr[0].GetYaxis().SetRangeUser(0,histMax)
histZ1InvMassCutLowAr[0].Draw("hist")
for j in range(1,len(histZ1InvMassCutLowAr)):
    histZ1InvMassCutLowAr[j].DrawCopy("same hist")
legAr[-1].Draw()


FOMZ1InvMassCutLowCan.cd()

setUpBottomPadsAr(padAr[-1])
FOMZ1InvMassCutLowGraph = TGraph(len(Z1InvMassCutLowGraphAr),Z1InvMassCutLowXAr,Z1InvMassCutLowGraphAr)
setUpGraphs(FOMZ1InvMassCutLowGraph,3,22,"Z1InvMassCutLow FoM Plot","Z1InvMassCutLow","S/SQRT(S+B)")
FOMZ1InvMassCutLowGraph.GetXaxis().SetRangeUser(Z1InvMassCutLowRange[0],Z1InvMassCutLowRange[1])
FOMZ1InvMassCutLowGraph.Draw("APL same")
FOMZ1InvMassCutLowCan.Update()
#"FP" stands for "Full Pass"
FOMZ1InvMassCutLowCan.SaveAs("lepCutZeroFOMGraph_FP_Z1InvMassCutLow_{0}_Vs_{1}_AMSFoM_WithComparZ1InvMassCutLownHist_{2}.png".format(signalName,backgroundName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))




FOMZ1InvMassCutHighCan = TCanvas("c1Z1InvMassCutHigh","c1Z1InvMassCutHigh",3600,2400)
setUpLegend(legAr)
setUpPadsAr(padAr,"{0}Pad".format("Z1InvMassCutHigh"))
padAr[-1][0].Draw()
padAr[-1][0].cd()
#Make top plot
intZ1InvMassCutHighAr = []
for j,colorA,nameA in zip(range(len(nameAr)),colorAr,nameAr):
    histZ1InvMassCutHighAr[j].SetLineColor(colorA)
    histZ1InvMassCutHighAr[j].SetLineWidth(3)
    if j == 0:
        makeNiceHistos(histZ1InvMassCutHighAr[j],"","Events",True)
        histZ1InvMassCutHighAr[j].SetTitle("Z1InvMassCutHigh FoM Plot")
    intZ1InvMassCutHighAr.append(histZ1InvMassCutHighAr[j].Integral())

histMax = 0


for j in range(len(histZ1InvMassCutHighAr)):
    if intZ1InvMassCutHighAr[j]:
        histZ1InvMassCutHighAr[j].Scale(1.0 / intZ1InvMassCutHighAr[j])
        tmpMax = histZ1InvMassCutHighAr[j].GetMaximum()
        if tmpMax > histMax:
            histMax = tmpMax
        legAr[-1].AddEntry(histZ1InvMassCutHighAr[j],nameAr[j],"l")
histZ1InvMassCutHighAr[0].GetYaxis().SetRangeUser(0,histMax)
histZ1InvMassCutHighAr[0].Draw("hist")
for j in range(1,len(histZ1InvMassCutHighAr)):
    histZ1InvMassCutHighAr[j].DrawCopy("same hist")
legAr[-1].Draw()


FOMZ1InvMassCutHighCan.cd()

setUpBottomPadsAr(padAr[-1])
FOMZ1InvMassCutHighGraph = TGraph(len(Z1InvMassCutHighGraphAr),Z1InvMassCutHighXAr,Z1InvMassCutHighGraphAr)
setUpGraphs(FOMZ1InvMassCutHighGraph,3,22,"Z1InvMassCutHigh FoM Plot","Z1InvMassCutHigh","S/SQRT(S+B)")
FOMZ1InvMassCutHighGraph.GetXaxis().SetRangeUser(Z1InvMassCutHighRange[0],Z1InvMassCutHighRange[1])
FOMZ1InvMassCutHighGraph.Draw("APL same")
FOMZ1InvMassCutHighCan.Update()
#"FP" stands for "Full Pass"
FOMZ1InvMassCutHighCan.SaveAs("lepCutZeroFOMGraph_FP_Z1InvMassCutHigh_{0}_Vs_{1}_AMSFoM_WithComparZ1InvMassCutHighnHist_{2}.png".format(signalName,backgroundName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))

FOMZ1PtCutLowCan = TCanvas("c1Z1PtCutLow","c1Z1PtCutLow",3600,2400)
setUpLegend(legAr)
setUpPadsAr(padAr,"{0}Pad".format("Z1PtCutLow"))
padAr[-1][0].Draw()
padAr[-1][0].cd()
#Make top plot
intZ1PtCutLowAr = []
for j,colorA,nameA in zip(range(len(nameAr)),colorAr,nameAr):
    histZ1PtCutLowAr[j].SetLineColor(colorA)
    histZ1PtCutLowAr[j].SetLineWidth(3)
    if j == 0:
        makeNiceHistos(histZ1PtCutLowAr[j],"","Events",True)
        histZ1PtCutLowAr[j].SetTitle("Z1PtCutLow FoM Plot")
    intZ1PtCutLowAr.append(histZ1PtCutLowAr[j].Integral())

histMax = 0


for j in range(len(histZ1PtCutLowAr)):
    if intZ1PtCutLowAr[j]:
        histZ1PtCutLowAr[j].Scale(1.0 / intZ1PtCutLowAr[j])
        tmpMax = histZ1PtCutLowAr[j].GetMaximum()
        if tmpMax > histMax:
            histMax = tmpMax
        legAr[-1].AddEntry(histZ1PtCutLowAr[j],nameAr[j],"l")
histZ1PtCutLowAr[0].GetYaxis().SetRangeUser(0,histMax)
histZ1PtCutLowAr[0].Draw("hist")
for j in range(1,len(histZ1PtCutLowAr)):
    histZ1PtCutLowAr[j].DrawCopy("same hist")
legAr[-1].Draw()


FOMZ1PtCutLowCan.cd()

setUpBottomPadsAr(padAr[-1])
FOMZ1PtCutLowGraph = TGraph(len(Z1PtCutLowGraphAr),Z1PtCutLowXAr,Z1PtCutLowGraphAr)
setUpGraphs(FOMZ1PtCutLowGraph,3,22,"Z1PtCutLow FoM Plot","Z1PtCutLow","S/SQRT(S+B)")
FOMZ1PtCutLowGraph.GetXaxis().SetRangeUser(Z1PtCutLowRange[0],Z1PtCutLowRange[1])
FOMZ1PtCutLowGraph.Draw("APL same")
FOMZ1PtCutLowCan.Update()
#"FP" stands for "Full Pass"
FOMZ1PtCutLowCan.SaveAs("lepCutZeroFOMGraph_FP_Z1PtCutLow_{0}_Vs_{1}_AMSFoM_WithComparZ1PtCutLownHist_{2}.png".format(signalName,backgroundName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))




FOMZ1PtCutHighCan = TCanvas("c1Z1PtCutHigh","c1Z1PtCutHigh",3600,2400)
setUpLegend(legAr)
setUpPadsAr(padAr,"{0}Pad".format("Z1PtCutHigh"))
padAr[-1][0].Draw()
padAr[-1][0].cd()
#Make top plot
intZ1PtCutHighAr = []
for j,colorA,nameA in zip(range(len(nameAr)),colorAr,nameAr):
    histZ1PtCutHighAr[j].SetLineColor(colorA)
    histZ1PtCutHighAr[j].SetLineWidth(3)
    if j == 0:
        makeNiceHistos(histZ1PtCutHighAr[j],"","Events",True)
        histZ1PtCutHighAr[j].SetTitle("Z1PtCutHigh FoM Plot")
    intZ1PtCutHighAr.append(histZ1PtCutHighAr[j].Integral())

histMax = 0


for j in range(len(histZ1PtCutHighAr)):
    if intZ1PtCutHighAr[j]:
        histZ1PtCutHighAr[j].Scale(1.0 / intZ1PtCutHighAr[j])
        tmpMax = histZ1PtCutHighAr[j].GetMaximum()
        if tmpMax > histMax:
            histMax = tmpMax
        legAr[-1].AddEntry(histZ1PtCutHighAr[j],nameAr[j],"l")
histZ1PtCutHighAr[0].GetYaxis().SetRangeUser(0,histMax)
histZ1PtCutHighAr[0].Draw("hist")
for j in range(1,len(histZ1PtCutHighAr)):
    histZ1PtCutHighAr[j].DrawCopy("same hist")
legAr[-1].Draw()


FOMZ1PtCutHighCan.cd()

setUpBottomPadsAr(padAr[-1])
FOMZ1PtCutHighGraph = TGraph(len(Z1PtCutHighGraphAr),Z1PtCutHighXAr,Z1PtCutHighGraphAr)
setUpGraphs(FOMZ1PtCutHighGraph,3,22,"Z1PtCutHigh FoM Plot","Z1PtCutHigh","S/SQRT(S+B)")
FOMZ1PtCutHighGraph.GetXaxis().SetRangeUser(Z1PtCutHighRange[0],Z1PtCutHighRange[1])
FOMZ1PtCutHighGraph.Draw("APL same")
FOMZ1PtCutHighCan.Update()
#"FP" stands for "Full Pass"
FOMZ1PtCutHighCan.SaveAs("FOMGraph_FP_Z1PtCutHigh_{0}_Vs_{1}_AMSFoM_WithComparZ1PtCutHighnHist_{2}.png".format(signalName,backgroundName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))

