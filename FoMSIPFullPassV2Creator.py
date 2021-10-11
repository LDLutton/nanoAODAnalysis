import datetime
from array import array
from math import sqrt
from ROOT import TFile, TChain, gDirectory, TApplication, TMath, Math, TMinuit, TROOT, TSystem, TTree, TVector2
from ROOT import THStack, TH1D, TCanvas, TPad, TF1, TGraph, TGraphErrors, TLegend, TLine, TPaveText, TStyle
from ROOT import TH2D, TH2F,gPad
from math import sqrt,pi,log
from functionsForFoMPlots import *
import time as time

#today = datetime.datetime.today()
startt = time.time()
"""
def makeNiceTHStack(histo,xTitle,yTitle,noX=True):

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


def getEdgesArForRebinHist(histToRebin,variableRebinVar):
    edgesAr = array('d')
    binSum = 0
    sumError = 0
    edgesAr.append(histToRebin.GetBinLowEdge(1))
    for i in range(binAmnt):
        binSum += histToRebin.GetBinContent(i)
        binError = histToRebin.GetBinError(i)
        sumError += sqrt((sumError*sumError)+(binError*binError))
        if (binSum > 0 and binError/binSum < variableRebinVar):
            edgesAr.append(histToRebin.GetBinLowEdge(i+1))
            binSum = 0
            sumError = 0
    lenEdgesAr = len(edgesAr)
    
    if lenEdgesAr:
        edgesAr.append(histToRebin.GetBinLowEdge(binAmnt+1))
        
    
    return lenEdgesAr,edgesAr

def variableRebinHist(histToRebin,histName,variableRebinVar,cutName):
    lenEdgesAr,edgesAr = getEdgesArForRebinHist(histToRebin,variableRebinVar)
    if lenEdgesAr:
        print(lenEdgesAr)
        print(edgesAr)
        print("-----------")
        return histToRebin.Rebin(lenEdgesAr,"{0}Hist{1}Rebin".format(cutName,histName),edgesAr)


def variableRebinBackgroundHists(tmpHist,backgroundHistAr,histNameAr,variableRebinVar,cutName,extraHistsAr = [],extraHistsNameAr=[]):
    for k in range(len(backgroundHistAr)):
        if not isSignalAr[k]:
            #Assumes each histogram starts with the same binning
            backgroundHistAr[k].Sumw2()
            tmpHist.Add(backgroundHistAr[k],weightsAr[k])
    lenEdgesAr,edgesAr = getEdgesArForRebinHist(tmpHist,variableRebinVar)
    if lenEdgesAr:
        print(lenEdgesAr)
        print(edgesAr)
        print("-----------")
        for k in range(len(backgroundHistAr)):
            if not isSignalAr[k]:
                backgroundHistAr[k].Sumw2()
                backgroundHistAr[k] = backgroundHistAr[k].Rebin(lenEdgesAr,"{0}Hist{1}Rebin".format(cutName,histNameAr[k]),edgesAr)
        if extraHistsAr:
            for k in range(len(extraHistsAr)):
                extraHistsAr[k].Sumw2()
                extraHistsAr[k] = extraHistsAr[k].Rebin(lenEdgesAr,"{0}Hist{1}Rebin".format(cutName,extraHistsNameAr[k]),edgesAr)

def FoMCalc(signalAr,backgroundAr,graphAr,xAr, cutAmnt,cutRange,cutStep):
    for c in range(cutAmnt):
        tmpSignal = signalAr[c]
        tmpBackground = backgroundAr[c]
        if tmpSignal > 0:
            if tmpBackground == 0:
                tmpFoM = tmpSignal/(sqrt(tmpSignal+tmpBackground))
            else:
                tmpFoM = sqrt(2*(((tmpSignal+tmpBackground)*log(1+(tmpSignal / tmpBackground)))-tmpSignal))
        else:
            tmpFoM = 0
        graphAr.append(tmpFoM)
        tmpX = cutRange[0] + (cutStep*c)
        xAr.append(tmpX)


def makeEvPassGraphs(nameAr,evPassCanAr,evPassGraphAr,evPassGraphsAr,xAr,cutName):
    for k,nameA in enumerate(nameAr):
        evPassCanAr.append(TCanvas("c1{0}{1}".format(cutName,nameA),"c1{0}{1}".format(cutName,nameA),3600,2400))
        evPassGraphsAr.append(TGraph(len(evPassGraphAr[k]),xAr,evPassGraphAr[k]))
        setUpGraphs(evPassGraphsAr[-1],3,22,"Number of Passing Events Vs {0} Cut for {1}".format(cutName,nameA),cutName,"Events Passing Cut")
        evPassGraphsAr[-1].Draw("APL*")
        evPassCanAr[-1].Draw()
        #"FP" stands for "Full Pass"
        evPassCanAr[-1].SaveAs("evPassCutGraph_FP_{0}{1}_V2_{1}.png".format(cutName,nameA,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))

def setHistoElements(nameAr,colorAr,sumQCD,QCDSumHist,isQCDAr,histAr,isSignalAr,cutName,normalizeBackgroundsTogether,intAr):
    backgroundIntSum = 0
    QCDSumInt = 0
    for j,colorA,nameA in zip(range(len(nameAr)),colorAr,nameAr):
        if not sumQCD or not isQCDAr[j]:
            histAr[j].SetLineColor(colorA)
            histAr[j].SetLineWidth(2)
            if not isSignalAr[j]:
                histAr[j].SetFillColorAlpha(colorA,0.2)
            if j == 0:
                makeNiceHistos(histAr[j],"","Events",True)
                histAr[j].SetTitle("Events Passing All Cuts Vs {0} Cut Value".format(cutName))
            tmpHistInt = histAr[j].Integral()
            if normalizeBackgroundsTogether:
                backgroundIntSum += tmpHistInt*weightsAr[j]

            intAr.append(tmpHistInt)
        else:
            intAr.append(1)
    if sumQCD:
        QCDSumHist.SetLineColor(9)
        QCDSumHist.SetLineWidth(2)
        QCDSumHist.SetFillColorAlpha(9,0.2)
        QCDSumInt = QCDSumHist.Integral()
    return backgroundIntSum, QCDSumInt

def doVariableRebinning(histAr,isSignalAr,variableRebinVar,binAmnt,cutRange,sumQCD,nameAr,QCDSumHist,cutName):
    #first do signal
    for k in range(len(histAr)):
        if isSignalAr[k]:
            print(k)
            histAr[k] = variableRebinHist(histAr[k],nameAr[k],variableRebinVar,cutName)
            break
    #Now background
    tmpRebinHist = TH1D("rebinHist","rebinHist", binAmnt, cutRange[0], cutRange[1])
    if sumQCD:
        extraHistsAr = [QCDSumHist]
        extraHistsNameAr = ["{0}HistQCDSum".format(cutName)]
        variableRebinBackgroundHists(tmpRebinHist,histAr,nameAr,variableRebinVar,cutName,extraHistsAr,extraHistsNameAr)
        QCDSumHist = extraHistsAr[0]
    else:
        variableRebinBackgroundHists(tmpRebinHist,histAr,nameAr,variableRebinVar,cutName)

def normalizeHists(histAr,sumQCD,isQCDAr,normalizeBackgroundsTogether,backgroundIntSum,isSignalAr,weightsAr,legAr,nameAr,intAr):
    histMax = 0
    for j in range(len(histAr)):
        if not sumQCD or not isQCDAr[j]:
            histAr[j].Sumw2()
            if normalizeBackgroundsTogether and backgroundIntSum and not isSignalAr[j]:
                
                histAr[j].Scale(weightsAr[j] / backgroundIntSum)
                tmpMax = histAr[j].GetMaximum()
                if tmpMax > histMax:
                    histMax = tmpMax
                legAr[-1].AddEntry(histAr[j],nameAr[j],"l")
            elif intAr[j]:
                print(j)
                print(intAr[j])
                histAr[j].Scale(1.0 / intAr[j])
                tmpMax = histAr[j].GetMaximum()
                if not normalizeBackgroundsTogether:
                    if tmpMax > histMax:
                        histMax = tmpMax
                legAr[-1].AddEntry(histAr[j],nameAr[j],"l")
    return histMax

def scaleQCDHist(QCDSumInt,QCDSumHist,histMax):
    QCDSumHist.Sumw2()
    QCDSumHist.Scale(1.0 / QCDSumInt)
    tmpMax = QCDSumHist.GetMaximum()
    if tmpMax > histMax:
        histMax = tmpMax
    legAr[-1].AddEntry(QCDSumHist,"QCDSum","l")
    return histMax

def addHistsToStack(histAr,isSignalAr,sumQCD,isQCDAr,histStack,QCDSumHist,normalizeBackgroundsTogether,backgroundIntSum):
    maxInt = 0
    for j in range(len(histAr)):
        if not isSignalAr[j] and (not sumQCD or not isQCDAr[j]):
            tmpMaxInt = histAr[j].Integral()
            if tmpMaxInt > maxInt:
                maxInt = tmpMaxInt
            histAr[j].Sumw2()
            histStack.Add(histAr[j])
    if sumQCD:
        histStack.Add(QCDSumHist)
    if normalizeBackgroundsTogether:
        tmpMaxBackground = histStack.GetMaximum()
        tmpMaxSignal = histAr[1].GetMaximum()
        tmpMaxRatio = tmpMaxBackground/tmpMaxSignal
        #tmpSignalInt = histAr[1].Integral()
        histAr[1].Sumw2()
        histAr[1].Scale(tmpMaxRatio)
        #histAr[1].Scale(backgroundIntSum / tmpSignalInt)
    return maxInt

def setUpInvHists(histAr,isSignalAr,sumQCD,isQCDAr,invHistsAr,nameAr,intAr,drawInvAr,QCDSumInt,QCDSumHist,cutName):
    for j in range(len(histAr)):
        if not isSignalAr[j] and (not sumQCD or not isQCDAr[j]):
            invHistsAr.append(histAr[j].Clone("{0}Inv".format(nameAr[j])))
            if intAr[j]:
                drawInvAr.append(True)

                tmpNBins = histAr[j].GetNbinsX()
                tmpBinErrorAr = []
                for i in range(tmpNBins):
                    tmpBinErrorAr.append(histAr[j].GetBinError(i))
                for k in range(j):
                    if not isSignalAr[k] and (not sumQCD or not isQCDAr[k]):
                        invHistsAr[-1].Add(histAr[k])
                for i in range(tmpNBins):
                    invHistsAr[-1].SetBinError(i,tmpBinErrorAr[i])
            else:
                drawInvAr.append(False)
    if sumQCD:
        if QCDSumInt:
            drawInvAr.append(True)
            invHistsAr.append(QCDSumHist.Clone("{0}HistQCDSumInv".format(cutName)))
            tmpNBins = QCDSumHist.GetNbinsX()
            tmpBinErrorAr = []
            for i in range(tmpNBins):
                tmpBinErrorAr.append(QCDSumHist.GetBinError(i))
            for k in range(j):
                if not isSignalAr[k] and not isQCDAr[k]:
                    invHistsAr[-1].Add(histAr[k])
            for i in range(tmpNBins):
                invHistsAr[-1].SetBinError(i,tmpBinErrorAr[i])
        else:
            drawInvAr.append(False)

def setUpStackedHistAndDrawFoMPlot(histMax,histAr,histStack,invHistsAr,drawInvAr,legAr,FoMCan,padAr,FoMgraph,cutRange,cutName,signalName,backgroundName):
    #maxForRange = 1.1*histMax
    #histAr[1].GetYaxis().SetRangeUser(0,maxForRange)

    histStack.Draw("hist")
    makeNiceTHStack(histStack,"","Events",True)
    tmpMax = histStack.GetMaximum()
    if tmpMax < histMax:
        histStack.SetMaximum(histMax)
    histStack.Draw("same hist")

    for k in range(len(invHistsAr)):

        if drawInvAr[k]:
            print("passed")
            invHistsAr[k].SetStats(0)
            invHistsAr[k].Draw("same E1")

    histAr[1].Draw("same hist E1")
    legAr[-1].Draw()


    FoMCan.cd()

    setUpBottomPadsAr(padAr[-1])
    
    setUpGraphs(FoMgraph,3,22,"{0} FoM Plot".format(cutName),cutName,"SQRT(2*(((S+B)*log(1+(S/B)))-S))")
    FoMgraph.GetXaxis().SetRangeUser(cutRange[0],cutRange[1])
    FoMgraph.Draw("APL* same")
    FoMCan.Update()
    #"FP" stands for "Full Pass"
    if normalizeBackgroundsTogether:
        FoMCan.SaveAs("FoMGraph_FP_{0}_{1}_Vs_{2}_AMSFoM_WithComparisonHist_Stacked_NBT_V2_{3}.png".format(cutName,signalName,backgroundName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
    else:
        FoMCan.SaveAs("FoMGraph_FP_{0}_{1}_Vs_{2}_AMSFoM_WithComparisonHist_Stacked_V2_{3}.png".format(cutName,signalName,backgroundName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))


def setUpNonStackedHistAndFoMPlot(FoM2Can,cutName,padAr,sumQCD,QCDSumHist,histMax,normalizeBackgroundsTogether,maxInt,histAr,legAr,FoMGraph,signalName,backgroundName):
    setUpPadsAr(padAr,"{0}Pad".format("{0}2".format(cutName)))
    padAr[-1][0].Draw()
    padAr[-1][0].cd()
    #Rescale signal hist
    if sumQCD:
        tmpMax = QCDSumHist.GetMaximum()
        if tmpMax > histMax:
            histMax = tmpMax
    if normalizeBackgroundsTogether:
        #tmpMaxSignal = histAr[1].GetMaximum()
        #tmpMaxRatio = histMax/tmpMaxSignal

        tmpSignalInt = histAr[1].Integral()
        histAr[1].Sumw2()
        #histAr[1].Scale(tmpMaxRatio)
        histAr[1].Scale(maxInt/tmpSignalInt)
    tmpMax = histAr[1].GetMaximum()
    if tmpMax > histMax:
        histMax = tmpMax

    histAr[0].GetYaxis().SetRangeUser(0,histMax)
    histAr[0].Draw("hist")

    if sumQCD:
        QCDSumHist.DrawCopy("same hist")
    for j in range(1,len(histAr)):
        if not sumQCD or not isQCDAr[j]:
            histAr[j].DrawCopy("same hist")
    
  
    legAr[-1].Draw()
    FoM2Can.cd()

    setUpBottomPadsAr(padAr[-1]) 
    FoMGraph.Draw("APL same")
    FoM2Can.Update()
    #"FP" stands for "Full Pass"
    if normalizeBackgroundsTogether:
        FoM2Can.SaveAs("FoMGraph_FP_{0}_{1}_Vs_{2}_AMSFoM_WithComparisonHist_NBT_V2_{3}.png".format(cutName,signalName,backgroundName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
    else:
        FoM2Can.SaveAs("FoMGraph_FP_{0}_{1}_Vs_{2}_AMSFoM_WithComparisonHist_V2_{3}.png".format(cutName,signalName,backgroundName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
"""




debug = False
debugMin = 1000
debugMax = 1004
forCondor = False
if forCondor:
    forCondorStr = "/scratch365/dlutton/HistosAndPNGs/"
else:
    forCondorStr = ""
skipEvPassGraphs = True
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

cutAmnt = 50
binAmnt = 50

ePtCut = 7
eEtaCut = 2.5

mPtCut = 5
mEtaCut = 2.4
invMassCutLow=60
invMassCutHigh=120
ptLeadCut=20
ptTrailingCut=10

#ZMass = 91.1876
fourLepInvMassCut = 100
optLepInvMassCut = 12

lepIsoCut = 0.35

SIPCut = 4
SIPRange = [0,5]

SIPStep = (SIPRange[1]-SIPRange[0])/cutAmnt
SIPSignalAr = [0 for i in range(cutAmnt)] 
SIPBackgroundAr = [0 for i in range(cutAmnt)] 

SIPEvPassGraphAr = []
for nameA in nameAr:
    SIPEvPassGraphAr.append(array('d'))

histSIPAr = []
"""
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
"""


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
    histSIPAr.append(TH1D("SIPHist{0}".format(nameAr[k]),"SIPHist{0}".format(nameAr[k]), binAmnt, SIPRange[0], SIPRange[1]))
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
                            tmpTopSIP = max(max(Z1LeadSIP,Z1TrailingSIP),max(Z2LeadSIP,Z2TrailingSIP))
                            histSIPAr[-1].Fill(tmpTopSIP)
                            
                            #Loop here
                            
                            

                            for SIPCutItr in range(cutAmnt):
                                tmpSIPCut = SIPRange[0]+(SIPCutItr*SIPStep)
                                passSIPCut = doSIPCut(Z1LeadSIP,Z1TrailingSIP,Z2LeadSIP,Z2TrailingSIP,tmpSIPCut)
                                if passSIPCut:
                                    tmpSIPCntAr[SIPCutItr] += 1
                                    


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

#Calculate FoM for each point

FoMCalc(SIPSignalAr,SIPBackgroundAr,SIPGraphAr,SIPXAr,cutAmnt,SIPRange,SIPStep)
"""
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
"""

evPassSIPCanAr = []
evPassSIPGraphAr = []
print("Done.","time:",time.time()-startt)

#make evpass graphs

cutName = "SIP"

if not skipEvPassGraphs:
    makeEvPassGraphs(nameAr,evPassSIPCanAr,SIPEvPassGraphAr,evPassSIPGraphAr,SIPXAr,cutName)
    """
    for k,nameA in enumerate(nameAr):
        #print("-------------------")
        #print(len(SIPEvPassGraphAr[k]),SIPXAr,SIPEvPassGraphAr[k])
        evPassSIPCanAr.append(TCanvas("c1SIP{0}".format(nameA),"c1SIP{0}".format(nameA),3600,2400))
        evPassSIPGraphAr.append(TGraph(len(SIPEvPassGraphAr[k]),SIPXAr,SIPEvPassGraphAr[k]))
        setUpGraphs(evPassSIPGraphAr[-1],3,22,"Number of Passing Events Vs SIP Cut for {0}".format(nameA),"SIP","Events Passing First Cut")
        evPassSIPGraphAr[-1].Draw("APL*")
        evPassSIPCanAr[-1].Draw()
        #"FP" stands for "Full Pass"
        evPassSIPCanAr[-1].SaveAs("evPassCutGraph_FP_SIP{0}_V2_{1}.png".format(nameA,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
    """




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
    QCDSumHist = TH1D("SIPHistQCDSum","SIPHistQCDSum", binAmnt, SIPRange[0], SIPRange[1])
    for k in range(len(histSIPAr)):

        if isQCDAr[k]:
            histSIPAr[k].Sumw2()
            QCDSumHist.Sumw2()
            QCDSumHist.Add(histSIPAr[k],weightsAr[k])
            """
            #loop over bins and add
            numBins = histSIPAr[k].GetNbinsX()
            for i in range(numBins):
                tmpBinContentWeighted = histSIPAr[k].GetBinContent(i)*weightsAr[k]
            """
else:
    QCDSumHist = 0

"""
testCan = TCanvas()
histSIPAr[1].Draw("hist E1")
testCan.SaveAs("TestOfErrorsEFT.png")
testCanTwo = TCanvas()
histSIPAr[3].Draw("hist E1")
testCanTwo.SaveAs("TestOfErrorsttZ.png")
testCanThree = TCanvas()
histSIPAr[0].Draw("hist E1")
testCanThree.SaveAs("TestOfErrorsSM.png")
"""

FoMSIPCan = TCanvas("c1SIP","c1SIP",3600,2400)
setUpLegend(legAr)
setUpPadsAr(padAr,"{0}Pad".format("SIP"))
padAr[-1][0].Draw()
padAr[-1][0].cd()
#Make top plot


#First set histogram elements (color, etc)
intSIPAr = []



backgroundIntSum,QCDSumInt = setHistoElements(nameAr,colorAr,sumQCD,QCDSumHist,isQCDAr,histSIPAr,isSignalAr,cutName,normalizeBackgroundsTogether,weightsAr,intSIPAr)

"""
backgroundIntSum = 0
for j,colorA,nameA in zip(range(len(nameAr)),colorAr,nameAr):
    if not sumQCD or not isQCDAr[j]:
        histSIPAr[j].SetLineColor(colorA)
        histSIPAr[j].SetLineWidth(2)
        if not isSignalAr[j]:
            #histSIPAr[j].SetFillColor(colorA)
            histSIPAr[j].SetFillColorAlpha(colorA,0.2)
        if j == 0:
            makeNiceHistos(histSIPAr[j],"","Events",True)
            histSIPAr[j].SetTitle("SIP FoM Plot")
        tmpHistInt = histSIPAr[j].Integral()
        if normalizeBackgroundsTogether:
            backgroundIntSum += tmpHistInt*weightsAr[j]

        intSIPAr.append(tmpHistInt)
    else:
        intSIPAr.append(1)
if sumQCD:
    QCDSumHist.SetLineColor(9)
    QCDSumHist.SetLineWidth(2)
    #QCDSumHist.SetFillColor(9)
    QCDSumHist.SetFillColorAlpha(9,0.2)
    QCDSumInt = QCDSumHist.Integral()
    #intSIPAr.append(QCDSumHist.Integral())
"""
"""
testCanAes = TCanvas()
histSIPAr[1].Draw("hist E1")
testCanAes.SaveAs("TestOfErrorsAesEFT.png")
testCanAesTwo = TCanvas()
histSIPAr[3].Draw("hist E1")
testCanAesTwo.SaveAs("TestOfErrorsAesttZ.png")
testCanAesThree = TCanvas()
histSIPAr[0].Draw("hist E1")
testCanAesThree.SaveAs("TestOfErrorsAesSM.png")

FoMSIPCan.cd()
padAr[-1][0].cd()
"""



if variableRebin:
    doVariableRebinning(histSIPAr,isSignalAr,variableRebinVar,binAmnt,SIPRange,sumQCD,nameAr,QCDSumHist,cutName,weightsAr)

    """
    #first do signal
    #testCanPre = TCanvas()
    #histSIPAr[1].Draw("hist *")
    #testCanPre.SaveAs("testVariableBinningPre.png")
    for k in range(len(histSIPAr)):
        if isSignalAr[k]:
            print(k)
            histSIPAr[k] = variableRebinHist(histSIPAr[k],nameAr[k],variableRebinVar)
            break
    #testCanPost = TCanvas()
    #histSIPAr[1].Draw("hist *")
    #testCanPost.SaveAs("testVariableBinningPost.png")
    #Now background
    tmpRebinHist = TH1D("rebinHist","rebinHist", binAmnt, SIPRange[0], SIPRange[1])
    if sumQCD:
        extraHistsAr = [QCDSumHist]
        extraHistsNameAr = ["SIPHistQCDSum"]
        variableRebinBackgroundHists(tmpRebinHist,histSIPAr,nameAr,variableRebinVar,extraHistsAr,extraHistsNameAr)
        QCDSumHist = extraHistsAr[0]
    else:
        variableRebinBackgroundHists(tmpRebinHist,histSIPAr,nameAr,variableRebinVar)
    """




histMax = normalizeHists(histSIPAr,sumQCD,isQCDAr,normalizeBackgroundsTogether,backgroundIntSum,isSignalAr,weightsAr,legAr,nameAr,intSIPAr)
"""
for j in range(len(histSIPAr)):
    if not sumQCD or not isQCDAr[j]:
        histSIPAr[j].Sumw2()
        if normalizeBackgroundsTogether and backgroundIntSum and not isSignalAr[j]:
            
            histSIPAr[j].Scale(weightsAr[j] / backgroundIntSum)
            tmpMax = histSIPAr[j].GetMaximum()
            if tmpMax > histMax:
                histMax = tmpMax
            legAr[-1].AddEntry(histSIPAr[j],nameAr[j],"l")
        elif intSIPAr[j]:
            print(j)
            print(intSIPAr[j])
            histSIPAr[j].Scale(1.0 / intSIPAr[j])
            tmpMax = histSIPAr[j].GetMaximum()
            if not normalizeBackgroundsTogether:
                if tmpMax > histMax:
                    histMax = tmpMax
            legAr[-1].AddEntry(histSIPAr[j],nameAr[j],"l")
"""

"""
testCanScale = TCanvas()
histSIPAr[1].Draw("hist E1")
testCanScale.SaveAs("TestOfErrorsScaleEFT.png")
testCanScaleTwo = TCanvas()
histSIPAr[3].Draw("hist E1")
testCanScaleTwo.SaveAs("TestOfErrorsScalettZ.png")
testCanScaleThree = TCanvas()
histSIPAr[0].Draw("hist E1")
testCanScaleThree.SaveAs("TestOfErrorsScaleSM.png")


FoMSIPCan.cd()
padAr[-1][0].cd()
"""



if sumQCD:
    if QCDSumInt:
        histMax = scaleQCDHist(QCDSumInt,QCDSumHist,histMax,legAr)

"""
if sumQCD:
    if QCDSumInt:
        QCDSumHist.Sumw2()
        QCDSumHist.Scale(1.0 / QCDSumInt)
        tmpMax = QCDSumHist.GetMaximum()
        if tmpMax > histMax:
            histMax = tmpMax
        legAr[-1].AddEntry(QCDSumHist,"QCDSum","l")
"""



histSIPStack = THStack("hist{0}Stack".format(cutName),"Events Passing All Cuts Vs {0} Cut Value".format(cutName))

maxInt = addHistsToStack(histSIPAr,isSignalAr,sumQCD,isQCDAr,histSIPStack,QCDSumHist,normalizeBackgroundsTogether,backgroundIntSum)

"""
for j in range(len(histSIPAr)):
    if not isSignalAr[j] and (not sumQCD or not isQCDAr[j]):
        #histSIPStack.GetHistogram.Sumw2()
        histSIPAr[j].Sumw2()
        histSIPStack.Add(histSIPAr[j])
if sumQCD:
    histSIPStack.Add(QCDSumHist)
if normalizeBackgroundsTogether:
    tmpMaxBackground = histSIPStack.GetMaximum()
    tmpMaxSignal = histSIPAr[1].GetMaximum()
    tmpMaxRatio = tmpMaxBackground/tmpMaxSignal
    histSIPAr[1].Sumw2()
    histSIPAr[1].Scale(tmpMaxRatio)
"""

"""
testCanStack = TCanvas()
histSIPAr[1].Draw("hist E1")
testCanStack.SaveAs("TestOfErrorsStackEFT.png")
testCanStackTwo = TCanvas()
histSIPAr[3].Draw("hist E1")
testCanStackTwo.SaveAs("TestOfErrorsStackttZ.png")
testCanStackThree = TCanvas()
histSIPAr[0].Draw("hist E1")
testCanStackThree.SaveAs("TestOfErrorsStackSM.png")

testCanStackFour = TCanvas()
histSIPStack.Draw("hist E1")
testCanStackFour.SaveAs("TestOfErrorsStacked.png")


FoMSIPCan.cd()
padAr[-1][0].cd()
"""


#Loop over all hists that went into the THStack to get center and length of error bars for invisible hist

invHistsAr = []
drawInvAr = []

setUpInvHists(histSIPAr,isSignalAr,sumQCD,isQCDAr,invHistsAr,nameAr,intSIPAr,drawInvAr,QCDSumInt,QCDSumHist,cutName)

"""

for j in range(len(histSIPAr)):
    if not isSignalAr[j] and (not sumQCD or not isQCDAr[j]):
        invHistsAr.append(histSIPAr[j].Clone("{0}Inv".format(nameAr[j])))
        if intSIPAr[j]:
            drawInvAr.append(True)

            tmpNBins = histSIPAr[j].GetNbinsX()
            #tmpBinAr = []
            tmpBinErrorAr = []
            for i in range(tmpNBins):
                tmpBinErrorAr.append(histSIPAr[j].GetBinError(i))
            for k in range(j):
                if not isSignalAr[k] and (not sumQCD or not isQCDAr[k]):
                    invHistsAr[-1].Add(histSIPAr[k])
            for i in range(tmpNBins):
                invHistsAr[-1].SetBinError(i,tmpBinErrorAr[i])
        else:
            drawInvAr.append(False)

if sumQCD:
    if QCDSumInt:
        drawInvAr.append(True)
        invHistsAr.append(QCDSumHist.Clone("SIPHistQCDSumInv"))
        tmpNBins = QCDSumHist.GetNbinsX()
        tmpBinErrorAr = []
        for i in range(tmpNBins):
            tmpBinErrorAr.append(QCDSumHist.GetBinError(i))
        for k in range(j):
            if not isSignalAr[k] and not isQCDAr[k]:
                invHistsAr[-1].Add(histSIPAr[k])
        for i in range(tmpNBins):
            invHistsAr[-1].SetBinError(i,tmpBinErrorAr[i])
    else:
        drawInvAr.append(False)

"""

FoMSIPGraph = TGraph(len(SIPGraphAr),SIPXAr,SIPGraphAr)

setUpStackedHistAndDrawFoMPlot(histMax,histSIPAr,histSIPStack,invHistsAr,drawInvAr,legAr,FoMSIPCan,padAr,FoMSIPGraph,SIPRange,normalizeBackgroundsTogether,cutName,signalName,backgroundName)



"""

maxForRange = 1.1*histMax
#print(histMax,maxForRange)
histSIPAr[1].GetYaxis().SetRangeUser(0,maxForRange)

histSIPStack.Draw("hist")
makeNiceTHStack(histSIPStack,"","Events",True)
tmpMax = histSIPStack.GetMaximum()
if tmpMax < histMax:
    histSIPStack.SetMaximum(histMax)
#histSIPStack.SetMaximum(maxForRange)
histSIPStack.Draw("same hist")

for k in range(len(invHistsAr)):
    #if k > 1:
    #    break
    #invHistsAr[k].SetFillColorAlpha(0,0)
    #invHistsAr[k].SetLineColor(0)
    #print(k,intSIPAr[k])

    if drawInvAr[k]:
        print("passed")
        invHistsAr[k].SetStats(0)
        invHistsAr[k].Draw("same E1")

histSIPAr[1].Draw("same hist E1")
legAr[-1].Draw()


FoMSIPCan.cd()

setUpBottomPadsAr(padAr[-1])
FoMSIPGraph = TGraph(len(SIPGraphAr),SIPXAr,SIPGraphAr)
setUpGraphs(FoMSIPGraph,3,22,"SIP FoM Plot","SIP","S/SQRT(S+B)")
FoMSIPGraph.GetXaxis().SetRangeUser(SIPRange[0],SIPRange[1])
FoMSIPGraph.Draw("APL* same")
FoMSIPCan.Update()
#"FP" stands for "Full Pass"
if normalizeBackgroundsTogether:
    FoMSIPCan.SaveAs("FoMGraph_FP_SIP_{0}_Vs_{1}_AMSFoM_WithComparisonHist_Stacked_NBT_V2_{2}.png".format(signalName,backgroundName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
else:
    FoMSIPCan.SaveAs("FoMGraph_FP_SIP_{0}_Vs_{1}_AMSFoM_WithComparisonHist_Stacked_V2_{2}.png".format(signalName,backgroundName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
"""


FoMSIP2Can = TCanvas("c2SIP","c2SIP",3600,2400)
setUpNonStackedHistAndFoMPlot(FoMSIP2Can,cutName,padAr,sumQCD,QCDSumHist,histMax,isSignalAr,isQCDAr,normalizeBackgroundsTogether,maxInt,histSIPAr,legAr,FoMSIPGraph,signalName,backgroundName)


"""


##Now making non-stacked graph
FoMSIP2Can = TCanvas("c2SIP","c2SIP",3600,2400)
#setUpLegend(legAr)
setUpPadsAr(padAr,"{0}Pad".format("SIP2"))
padAr[-1][0].Draw()
padAr[-1][0].cd()

histSIPAr[0].GetYaxis().SetRangeUser(0,histMax)
histSIPAr[0].Draw("hist")

for j in range(1,len(histSIPAr)):
    histSIPAr[j].DrawCopy("same hist")
legAr[-1].Draw()


FoMSIP2Can.cd()

setUpBottomPadsAr(padAr[-1])
#FoMSIPGraph = TGraph(len(SIPGraphAr),SIPXAr,SIPGraphAr)
#setUpGraphs(FoMSIPGraph,3,22,"SIP FoM Plot","SIP","S/SQRT(S+B)")
#FoMSIPGraph.GetXaxis().SetRangeUser(SIPRange[0],SIPRange[1])
FoMSIPGraph.Draw("APL same")
FoMSIP2Can.Update()
#"FP" stands for "Full Pass"
if normalizeBackgroundsTogether:
    FoMSIP2Can.SaveAs("FoMGraph_FP_SIP_{0}_Vs_{1}_AMSFoM_WithComparisonHist_NBT_V2_{2}.png".format(signalName,backgroundName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
else:
    FoMSIP2Can.SaveAs("FoMGraph_FP_SIP_{0}_Vs_{1}_AMSFoM_WithComparisonHist_V2_{2}.png".format(signalName,backgroundName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))

"""