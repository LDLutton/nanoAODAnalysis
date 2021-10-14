import datetime
from array import array
from math import sqrt
from ROOT import TFile, TChain, gDirectory, TApplication, TMath, Math, TMinuit, TROOT, TSystem, TTree, TVector2
from ROOT import THStack, TH1D, TCanvas, TPad, TF1, TGraph, TGraphErrors, TLegend, TLine, TPaveText, TStyle
from ROOT import TH2D, TH2F,gPad
from math import sqrt,pi,log

ZMass = 91.1876

today = datetime.datetime.today()

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


def doeZ1Cut(ev,elecCandIndAr,elecCandVecAr,elecCandChargeAr,elecPassesZ2CutsAr,Z1IsMuon,invMassCutLow,invMassCutHigh,ptLeadCut,ptTrailingCut,tmpTopZ1LeadPt,tmpTopZ1TrailingPt,tmpTopLeadItr,tmpTopTrailingItr,tmpTopLeadVec,tmpTopTrailingVec,tmpTopLeadCharge,tmpTopTrailingCharge,difFromZMassOne,debug=False):
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

def domZ1Cut(ev,muonCandIndAr,muonCandVecAr,muonCandChargeAr,muonPassesZ2CutsAr,Z1IsMuon,invMassCutLow,invMassCutHigh,ptLeadCut,ptTrailingCut,tmpTopZ1LeadPt,tmpTopZ1TrailingPt,tmpTopLeadItr,tmpTopTrailingItr,tmpTopLeadVec,tmpTopTrailingVec,tmpTopLeadCharge,tmpTopTrailingCharge,difFromZMassOne,debug=False):
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


def getEdgesArForRebinHist(histToRebin,variableRebinVar,binAmnt):
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

def variableRebinHist(histToRebin,binAmnt,histName,variableRebinVar,cutName):
    lenEdgesAr,edgesAr = getEdgesArForRebinHist(histToRebin,variableRebinVar,binAmnt)
    if lenEdgesAr:
        print(lenEdgesAr)
        print(edgesAr)
        print("-----------")
        return histToRebin.Rebin(lenEdgesAr,"{0}Hist{1}Rebin".format(cutName,histName),edgesAr)


def variableRebinBackgroundHists(tmpHist,backgroundHistAr,binAmnt,isSignalAr,histNameAr,variableRebinVar,cutName,weightsAr,extraHistsAr = [],extraHistsNameAr=[]):
    for k in range(len(backgroundHistAr)):
        if not isSignalAr[k]:
            #Assumes each histogram starts with the same binning
            backgroundHistAr[k].Sumw2()
            tmpHist.Add(backgroundHistAr[k],weightsAr[k])
    lenEdgesAr,edgesAr = getEdgesArForRebinHist(tmpHist,variableRebinVar,binAmnt)
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
        evPassCanAr[-1].SaveAs("evPassCutGraph_FP_{0}{1}_V2_{2}.png".format(cutName,nameA,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))

def setHistoElements(nameAr,colorAr,sumQCD,QCDSumHist,isQCDAr,histAr,isSignalAr,cutName,normalizeBackgroundsTogether,weightsAr,intAr):
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
                if not isSignalAr[j]:
                    backgroundIntSum += tmpHistInt*weightsAr[j]

            intAr.append(tmpHistInt)
        else:
            intAr.append(1)
    if sumQCD:
        QCDSumHist.SetLineColor(9)
        QCDSumHist.SetLineWidth(2)
        QCDSumHist.SetFillColorAlpha(28,0.2)
        QCDSumInt = QCDSumHist.Integral()
    return backgroundIntSum, QCDSumInt

def doVariableRebinning(histAr,isSignalAr,variableRebinVar,binAmnt,cutRange,sumQCD,nameAr,QCDSumHist,cutName,weightsAr):
    #first do signal
    for k in range(len(histAr)):
        if isSignalAr[k]:
            print(k)
            histAr[k] = variableRebinHist(histAr[k],binAmnt,nameAr[k],variableRebinVar,cutName)
            break
    #Now background
    tmpRebinHist = TH1D("rebinHist","rebinHist", binAmnt, cutRange[0], cutRange[1])
    if sumQCD:
        extraHistsAr = [QCDSumHist]
        extraHistsNameAr = ["{0}HistQCDSum".format(cutName)]
        variableRebinBackgroundHists(tmpRebinHist,histAr,binAmnt,nameAr,variableRebinVar,cutName,weightsAr,extraHistsAr,extraHistsNameAr)
        QCDSumHist = extraHistsAr[0]
    else:
        variableRebinBackgroundHists(tmpRebinHist,histAr,binAmnt,isSignalAr,nameAr,variableRebinVar,cutName,weightsAr)

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

def scaleQCDHist(QCDSumInt,QCDSumHist,histMax,legAr):
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
        print("------------")
        print(tmpMaxBackground,tmpMaxSignal,tmpMaxRatio)
        print(histAr[1].GetMaximum())
        #tmpSignalInt = histAr[1].Integral()
        histAr[1].Sumw2()
        histAr[1].Scale(tmpMaxRatio)
        print(histAr[1].GetMaximum())
        print("------------")
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

def setUpStackedHistAndDrawFoMPlot(histMax,histAr,histStack,invHistsAr,drawInvAr,legAr,FoMCan,padAr,FoMgraph,cutRange,normalizeBackgroundsTogether,cutName,signalName,backgroundName):
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


def setUpNonStackedHistAndFoMPlot(FoM2Can,cutName,padAr,sumQCD,QCDSumHist,histMax,isSignalAr,isQCDAr,normalizeBackgroundsTogether,maxInt,histAr,legAr,FoMGraph,signalName,backgroundName):
    setUpPadsAr(padAr,"{0}Pad".format("{0}2".format(cutName)))
    padAr[-1][0].Draw()
    padAr[-1][0].cd()
    #Rescale signal hist
    if sumQCD:
        tmpMax = QCDSumHist.GetMaximum()
        if tmpMax > histMax:
            histMax = tmpMax
    if normalizeBackgroundsTogether:
        tmpMaxSignal = histAr[1].GetMaximum()
        tmpMaxRatio = histMax/tmpMaxSignal

        #tmpSignalInt = histAr[1].Integral()
        histAr[1].Sumw2()
        histAr[1].Scale(tmpMaxRatio)
        #histAr[1].Scale(maxInt/tmpSignalInt)
    tmpMax = histAr[1].GetMaximum()
    if tmpMax > histMax:
        histMax = tmpMax

    histAr[0].GetYaxis().SetRangeUser(0,histMax*1.1)
    histAr[0].Draw("hist")

    if sumQCD:
        QCDSumHist.DrawCopy("same hist")
    for j in range(1,len(histAr)):
        if not isSignalAr[j] and (not sumQCD or not isQCDAr[j]):
            histAr[j].DrawCopy("same hist")
    histAr[1].DrawCopy("same hist")
    
  
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