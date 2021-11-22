import datetime
from ROOT import TLegend, TPad,TCanvas


today = datetime.datetime.today()


forCondor = False
if forCondor:
    forCondorStr = "/scratch365/dlutton/HistosAndPNGs/"
    savePathBool = False
else:
    forCondorStr = ""
    savePathBool = True


#For drawing and saving histograms
#Saves a png and, optionally, a pdf version
#Saves histogram to the currently active root file
sumQCD = True
isQCDAr = []

testRun = False
MGSM = True
MGEFT = True
ttHToBBBackground = True
ttZJetsBackground = True
DYBackground = True
QCDPT170to300Background = True
QCDPT300to470Background = True
QCDPT470to600Background = True
QCDPT600to800Background = True
QCDPT800to1000Background = True
QCDPT1000to1400Background = True
QCDPT1400to1800Background = True
QCDPT1800to2400Background = True
QCDPT2400to3200Background = True
QCDPT3200toInfBackground = True
normalizeBackgroundsTogether = True

onlyDoSomeHists = False
histsToDo = 2

breakEvEarly = False
breakEvAt = 2500

drawXSPlots = False
drawEvPlots = False
#ignoreHist = True
#ignoreHistInd = 13

FJCandidateHistIndRangeAr = [[9,14],[14,19]]
#FJMatchedHistIndRangeAr = [[19,24],[24,29],[29,34]]
FJMatchedHistIndRangeAr = [[19,24]]
FJCandidateSaveNameAr = ["","UsingDTHForCand"]
FJMatchedSaveNameAr = ["","UsingDTHForMatch","UsingdRForMatch"]


XSxTitleAr = ["Cross Section"]
XShTitleAr = ["Cross Section"]
XSBinsAndRangeAr = [[50,-1,1]]

evNxTitleAr = ["Events","Events"]
evNhTitleAr = ["Total Events","Events Passing Higgs Jet Cuts"]
evNBinsAndRangeAr = [[4,132877,132881],[4,55628,55632]]

histAr = []
QCDSumHistAr = []
canAr = []
histLepAr = []
QCDSumHistLepAr = []
canLepAr = []

histSemiLepAr = []
QCDSumHistSemiLepAr = []
canSemiLepAr = []

histHadAr = []
QCDSumHistHadAr = []
canHadAr = []


FASaveNameAr = ["nJets","JetLeadPt","JetTrailingPt","JetLeadPhi","JetTrailingPhi","JetPairIM","JetLeadEta","JetTrailingEta",
"nFJ","FJPt","FJPhi","FJEta","FJMass","FJDeepTagH",
"FJPt_UsingDTH","FJPhi_UsingDTH","FJEta_UsingDTH","FJMass_UsingDTH","FJDeepTagH_UsingDTH",

"nGP","dR","Ind","pdg","pdgMom",
"dR_UsingDTH","Ind_UsingDTH","pdg_UsingDTH","pdgMom_UsingDTH",
"hbbTag","DEHLT","DMHLT","MEGHLT","SEHLT","SMHLT","HHLT",
"LepChannel","SemiLepChannel","HadChannel",
"passedLep","passedSemiLep","passedHad"
]


FATitleAr = ["Number of Jets","Jet Lead Pt","Jet Trailing Pt","Jet Lead Phi","Jet Trailing Phi","Jet Pair Inv Mass","Jet Lead Eta","Jet Trailing Eta",
"Number of Fat Jets","Pt of Higgs Candidate Fat Jets","Phi of Higgs Candidate Fat Jets","Eta of Higgs Candidate Fat Jets","Mass of Higgs Candidate Fat Jets","DeepTag_H of Higgs Candidate Fat Jets",
"Pt of Higgs Candidate Fat Jets Chosen Using DeepTag_H","Phi of Higgs Candidate Fat Jets Chosen Using DeepTag_H","Eta of Higgs Candidate Fat Jets Chosen Using DeepTag_H","Mass of Higgs Candidate Fat Jets Chosen Using DeepTag_H","DeepTag_H of Higgs Candidate Fat Jets Chosen Using DeepTag_H",

"Number of Gen Particles","dR of Higgs Candidate Fat Jet to Closest Gen Particle","Index of Closest Gen Particle to Higgs Candidate Fat Jet","pdg Id of Closest Gen Particle to Higgs Candidate Fat Jet","pdg Id of Initial Particle Leading to Closest Gen Particle to Higgs Candidate Fat Jet",
"dR of Higgs Candidate Fat Jet to Closest Gen Particle Chosen Using DeepTag_H","Index of Closest Gen Particle to Higgs Candidate Fat Jet Chosen Using DeepTag_H","pdg Id of Closest Gen Particle to Higgs Candidate Fat Jet Chosen Using DeepTag_H","pdg Id of Initial Particle Leading to Closest Gen Particle to Higgs Candidate Fat Jet Chosen Using DeepTag_H",
"Hbb Tag for Events that Pass (always true)","Double Elec HLT","Double Muon HLT","Muon EG HLT","Single Electron HLT","Single Muon HLT","Hadronic HLT",
"Leptonic Channel","Semi-Leptonic Channel","Hadronic Channel",
"passedLep","passedSemiLep","passedHad"]

FAXTitleAr = ["nJet","Pt (GeV)","Pt (GeV)","Phi","Phi","Inv Mass (GeV)","Eta","Eta",
"nFatJet","Pt (GeV)","Phi","Eta","Mass (GeV)","DeepTag_H",
"Pt (GeV)","Phi","Eta","Mass (GeV)","DeepTag_H",

"nGenParts","dR","Index","pdg Id","pdg Id",
"dR","Index","pdg Id","pdg Id",
"","","","","","","",
"","","",
"","",""]

FABinsAndRangeAr = [[20,0,20],[50,0,2500],[50,0,2500],[50,-3.5,3.5],[50,-3.5,3.5],[100,0,6000],[50,-4.5,4.5],[50,-4.5,4.5],
[8,0,8],[50,0,2500],[50,-3.5,3.5],[50,-4.5,4.5],[60,0,600],[100,0,1],
[50,0,2500],[50,-3.5,3.5],[50,-4.5,4.5],[60,0,600],[100,0,1],

[160,0,160],[30,0,0.3],[120,0,120],[35,-5,30],[35,-5,30],
[30,0,0.3],[120,0,120],[35,-5,30],[35,-5,30],
[3,0,3],[2,0,2],[2,0,2],[2,0,2],[2,0,2],[2,0,2],[2,0,2],
[2,0,2],[2,0,2],[2,0,2],
[2,0,2],[2,0,2],[2,0,2]]


LepSaveNameAr = ["Z1LeadPt","Z1TrailingPt","Z1LeadPhi","Z1TrailingPhi","Z1InvMass","Z1LeadEta","Z1TrailingEta",
"Z1IsElectron","Z1IsMuon",
"Z1LeadIso","Z1TrailingIso","Z1LeadSIP","Z1TrailingSIP",
"Z2LeadPt","Z2TrailingPt","Z2LeadPhi","Z2TrailingPhi","Z2InvMass","Z2LeadEta","Z2TrailingEta",
"Z2IsElectron","Z2IsMuon",
"Z2LeadIso","Z2TrailingIso","Z2LeadSIP","Z2TrailingSIP"
]

LepTitleAr = ["Z1 Lead Pt","Z1 Trailing Pt","Z1 Lead Phi","Z1 Trailing Phi","Z1 Invariant Mass","Z1 Lead Eta","Z1 Trailing Eta",
"Z1 Is Electron","Z1 Is Muon",
"Z1 Lead Iso","Z1 Trailing Iso","Z1 Lead SIP","Z1 Trailing SIP",
"Z2 Lead Pt","Z2 Trailing Pt","Z2 Lead Phi","Z2 Trailing Phi","Z2 Invariant Mass","Z2 Lead Eta","Z2 Trailing Eta",
"Z2 Is Electron","Z2 Is Muon",
"Z2 Lead Iso","Z2 Trailing Iso","Z2 Lead SIP","Z2 Trailing SIP"]

LepXTitleAr = ["Pt (GeV)","Pt (GeV)","Phi","Phi","Invariant Mass (GeV)","Eta","Eta",
"","",
"Isolation","Isolation","SIP","SIP",
"Pt (GeV)","Pt (GeV)","Phi","Phi","Invariant Mass (GeV)","Eta","Eta",
"","",
"Isolation","Isolation","SIP","SIP"]

LepBinsAndRangeAr = [[34,0,2500],[34,0,2500],[25,-3.5,3.5],[25,-3.5,3.5],[40,60,120],[25,-4.5,4.5],[25,-4.5,4.5],
[2,0,2],[2,0,2],
[26,0,0.4],[26,0,0.4],[26,0,4],[26,0,4],
[34,0,2500],[34,0,2500],[25,-3.5,3.5],[25,-3.5,3.5],[40,60,120],[25,-4.5,4.5],[25,-4.5,4.5],
[2,0,2],[2,0,2],
[26,0,0.4],[26,0,0.4],[26,0,4],[26,0,4]]


#Note in SemiLep tree there is an accidental branch "lepZ2IsElectron" which *should not* be in there. ignore
SemiLepSaveNameAr = ["lepPairLeadPt","lepPairTrailingPt","lepPairLeadPhi","lepPairTrailingPhi","lepPairInvMass","lepPairLeadEta","lepPairTrailingEta",
"lepPairIsElectron","lepPairIsMuon",
"lepPairLeadIso","lepPairTrailingIso","lepPairLeadSIP","lepPairTrailingSIP",
#"ignoreBranch",
"FatJetPt","FatJetPhi","FatJetInvMass","FatJetEta"
]

SemiLepTitleAr = ["Lep Pair Lead Pt","Lep Pair Trailing Pt","Lep Pair Lead Phi","Lep Pair Trailing Phi","Lep Pair Invariant Mass","Lep Pair Lead Eta","Lep Pair Trailing Eta",
"Lep Pair Is Electron","Lep Pair Is Muon",
"Lep Pair Lead Iso","Lep Pair Trailing Iso","Lep Pair Lead SIP","Lep Pair Trailing SIP",
#"ignoreBranch",
"FatJet Pt","FatJet Phi","FatJet Invariant Mass","FatJet Eta"]

SemiLepXTitleAr = ["Pt (GeV)","Pt (GeV)","Phi","Phi","Invariant Mass (GeV)","Eta","Eta",
"","",
"Isolation","Isolation","SIP","SIP",
#"ignoreBranch",
"Pt (GeV)","Phi","Invariant Mass (GeV)","Eta"]

SemiLepBinsAndRangeAr = [[50,0,2500],[50,0,2500],[50,-3.5,3.5],[50,-3.5,3.5],[120,60,120],[50,-4.5,4.5],[50,-4.5,4.5],
[2,0,2],[2,0,2],
[40,0,0.4],[40,0,0.4],[40,0,4],[40,0,4],
#[10,0,10],
[50,0,2500],[50,-3.5,3.5],[60,0,600],[50,-4.5,4.5]]

HadSaveNameAr = ["FatJetLeadPt","FatJetTrailingPt",
"FatJetLeadPhi","FatJetTrailingPhi",
"FatJetLeadInvMass","FatJetTrailingInvMass",
"FatJetPairInvMass",
"FatJetLeadEta","FatJetTrailingEta",
"FatJetEtaSep"]

HadTitleAr = ["FatJet Lead Pt","FatJet Trailing Pt",
"FatJet Lead Phi","FatJet Trailing Phi",
"FatJet Lead Invariant Mass","FatJet Trailing Invariant Mass",
"FatJet Pair Invariant Mass",
"FatJet Lead Eta","FatJet Trailing Eta",
"FatJet Eta Separation"]

HadXTitleAr = ["Pt (GeV)","Pt (GeV)",
"Phi","Phi",
"Invariant Mass (GeV)","Invariant Mass (GeV)",
"Invariant Mass (GeV)",
"Eta","Eta",
"Eta Separation"]

HadBinsAndRangeAr = [[50,0,2500],[50,0,2500],
[50,-3.5,3.5],[50,-3.5,3.5],
[60,0,600],[60,0,600],
[60,0,6000],
[50,-4.5,4.5],[50,-4.5,4.5],
[40,0,8]]


yTitle = "Events"

def makeNiceHistos(histo,xTitle,yTitle,noX=True):
  if noX:
    #histo.GetXaxis().SetLabelOffset(999)
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

"""

def makeNiceHistos(histo,xTitle,yTitle,histTitle,noX=True):
  if noX:
    histo.GetXaxis().SetTitle("")
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
  histo.SetTitle(histTitle)
  histo.SetStats(0)
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

  



def setHistoElements(colorAr,sumQCD,QCDSumHist,isQCDAr,histAr,isSignalAr,normalizeBackgroundsTogether,weightsAr,intAr,histTitleNameAr,onlyDoSomeHists,histsToDo,signalPos):
    backgroundIntSumAr = []
    QCDSumIntAr = []
    for histTypeItr, histTitleName in enumerate(histTitleNameAr):
      if onlyDoSomeHists and histTypeItr >= histsToDo:
        break
      backgroundIntSumAr.append(0)
      QCDSumIntAr.append(0)
    for k,colorA in zip(range(len(colorAr)),colorAr):
      intAr.append([])
      for histTypeItr, histTitleName in enumerate(histTitleNameAr):
        if onlyDoSomeHists and histTypeItr >= histsToDo:
          break
        if not sumQCD or not isQCDAr[k]:
            histAr[k][histTypeItr].SetLineColor(colorA)
            histAr[k][histTypeItr].SetLineWidth(4)
            if not isSignalAr[k]:
                histAr[k][histTypeItr].SetFillColorAlpha(colorA,0.2)
            if signalPos == 1:
              if k == 0:
                  makeNiceHistos(histAr[k][histTypeItr],"","Events",True)
                  histAr[k][histTypeItr].SetTitle(histTitleName)
            else:
              if k == 1:
                  makeNiceHistos(histAr[k][histTypeItr],"","Events",True)
                  histAr[k][histTypeItr].SetTitle(histTitleName)
            tmpHistInt = histAr[k][histTypeItr].Integral()
            if normalizeBackgroundsTogether:
                if not isSignalAr[k]:
                    #print(k,histTypeItr)
                    #print(backgroundIntSumAr)
                    #print(tmpHistInt)
                    #print(weightsAr)
                    backgroundIntSumAr[histTypeItr] += tmpHistInt*weightsAr[k]
            intAr[-1].append(tmpHistInt)
        else:
            intAr[-1].append(1)
    if sumQCD:
        for histTypeItr, histTitleName in enumerate(histTitleNameAr):
          if onlyDoSomeHists and histTypeItr >= histsToDo:
            break
          QCDSumHist[histTypeItr].SetLineColor(28)
          QCDSumHist[histTypeItr].SetLineWidth(2)
          QCDSumHist[histTypeItr].SetFillColorAlpha(28,0.2)
          QCDSumIntAr[histTypeItr] = QCDSumHist[histTypeItr].Integral()
          if normalizeBackgroundsTogether:
            backgroundIntSumAr[histTypeItr] += QCDSumIntAr[histTypeItr]
    return backgroundIntSumAr, QCDSumIntAr

def addHistsToStack(fileAr,histAr,isSignalAr,sumQCD,isQCDAr,histStackAr,QCDSumHist,normalizeBackgroundsTogether,backgroundIntSum,histTypeSaveNameAr,signalPos,onlyDoSomeHists,histsToDo):
    maxIntAr = []
    for histTypeItr in range(len(histTypeSaveNameAr)):
      if onlyDoSomeHists and histTypeItr >= histsToDo:
        break
      maxInt = 0
      for k in range(len(fileAr)):
          #print(k)
          #print(isQCDAr)
          #print(isSignalAr)
          if not isSignalAr[k] and (not sumQCD or not isQCDAr[k]):
              tmpMaxInt = histAr[k][histTypeItr].Integral()
              if tmpMaxInt > maxInt:
                  maxInt = tmpMaxInt
              histAr[k][histTypeItr].Sumw2()
              histStackAr[histTypeItr].Add(histAr[k][histTypeItr])
      if sumQCD:
          histStackAr[histTypeItr].Add(QCDSumHist[histTypeItr])
      if normalizeBackgroundsTogether:
          tmpMaxBackground = histStackAr[histTypeItr].GetMaximum()
          tmpMaxSignal = histAr[signalPos][histTypeItr].GetMaximum()
          if tmpMaxSignal:
            tmpMaxRatio = tmpMaxBackground/tmpMaxSignal
          else:
            tmpMaxRatio = 1
          #print("------------")
          #print(tmpMaxBackground,tmpMaxSignal,tmpMaxRatio)
          #print(histAr[signalPos][histTypeItr].GetMaximum())
          #tmpSignalInt = histAr[1].Integral()
          histAr[signalPos][histTypeItr].Sumw2()
          histAr[signalPos][histTypeItr].Scale(tmpMaxRatio)
          #print(histAr[signalPos][histTypeItr].GetMaximum())
          #print("------------")
          #histAr[1].Scale(backgroundIntSum / tmpSignalInt)
      maxIntAr.append(maxInt)
    return maxIntAr

def normalizeHists(histAr,sumQCD,isQCDAr,normalizeBackgroundsTogether,backgroundIntSum,isSignalAr,weightsAr,legAr,nameAr,intAr,histTypeSaveNameAr,onlyDoSomeHists,histsToDo):
    histMaxAr = []
    for histTypeItr in range(len(histTypeSaveNameAr)):
      if onlyDoSomeHists and histTypeItr >= histsToDo:
        break
      histMaxAr.append(0)
    for k in range(len(histAr)):
      for histTypeItr in range(len(histTypeSaveNameAr)):
        if onlyDoSomeHists and histTypeItr >= histsToDo:
          break
        if not sumQCD or not isQCDAr[k]:
            histAr[k][histTypeItr].Sumw2()
            #print(k,histTypeItr)
            #print(backgroundIntSum)
            #print(isSignalAr)
            if normalizeBackgroundsTogether and backgroundIntSum[histTypeItr] and not isSignalAr[k]:
                
                histAr[k][histTypeItr].Scale(weightsAr[k] / backgroundIntSum[histTypeItr])
                tmpMax = histAr[k][histTypeItr].GetMaximum()
                if tmpMax > histMaxAr[histTypeItr]:
                    histMaxAr[histTypeItr] = tmpMax
                legAr[histTypeItr].AddEntry(histAr[k][histTypeItr],nameAr[k],"l")
            elif intAr[k][histTypeItr]:
                #print(k,histTypeItr)
                #print(intAr[k][histTypeItr])
                histAr[k][histTypeItr].Scale(1.0 / intAr[k][histTypeItr])
                tmpMax = histAr[k][histTypeItr].GetMaximum()
                if not normalizeBackgroundsTogether:
                    if tmpMax > histMaxAr[histTypeItr]:
                        histMaxAr[histTypeItr] = tmpMax
                legAr[histTypeItr].AddEntry(histAr[k][histTypeItr],nameAr[k],"l")
    return histMaxAr

def scaleQCDHist(QCDSumInt,QCDSumHist,histMaxAr,legAr,onlyDoSomeHists,histsToDo,normalizeBackgroundsTogether,backgroundIntSum):
  for histTypeItr in range(len(histMaxAr)):
    if onlyDoSomeHists and histTypeItr >= histsToDo:
      break
    if QCDSumInt[histTypeItr]:
      #print("QCDSumInt[histTypeItr]",QCDSumInt[histTypeItr])
      QCDSumHist[histTypeItr].Sumw2()
      if normalizeBackgroundsTogether:
        QCDSumHist[histTypeItr].Scale(1.0 / backgroundIntSum[histTypeItr])
      else:
        QCDSumHist[histTypeItr].Scale(1.0 / QCDSumInt[histTypeItr])
      tmpMax = QCDSumHist[histTypeItr].GetMaximum()
      if tmpMax > histMaxAr[histTypeItr]:
          histMaxAr[histTypeItr] = tmpMax
      legAr[histTypeItr].AddEntry(QCDSumHist[histTypeItr],"QCDSum","l")
  return histMaxAr



def setUpLegend(legAr):
  legAr.append(TLegend(.9,.6,.99,.92))
  legAr[-1].SetTextSize(0.036)
  legAr[-1].SetTextFont(42)


def setUpPadsAr(padAr,padName):
  padAr.append([])
  padAr[-1].append(TPad(padName, padName,0.,0.40,1,1))
  padAr[-1].append(TPad(padName+" ratio", padName+" ratio",0.,0.,1,0.45))
  #padAr[-1].append(TPad(padName, padName,0.,0.70,1,1))
  #padAr[-1].append(TPad(padName+" ratio", padName+" ratio",0.,0.,1,0.60))

def setUpBottomPadsAr(padAr):
  padAr[1].SetTopMargin(0)
  padAr[1].SetBottomMargin(0.15)
  padAr[1].Draw()
  padAr[1].cd()

def setUpInvHists(histAr,cloneHistAr,isSignalAr,sumQCD,isQCDAr,invHistsAr,nameAr,intAr,drawInvAr,QCDSumInt,QCDSumHist,histTypeSaveNameAr,onlyDoSomeHists,histsToDo):
    for k in range(len(histAr)):
      
      if not isSignalAr[k] and (not sumQCD or not isQCDAr[k]):
        cloneHistAr.append([])
        invHistsAr.append([])
        drawInvAr.append([])
        for histTypeItr in range(len(histTypeSaveNameAr)):
            if onlyDoSomeHists and histTypeItr >= histsToDo:
              break
            cloneHistAr[-1].append(histAr[k][histTypeItr].Clone())
            invHistsAr[-1].append(histAr[k][histTypeItr].Clone("{0}Inv".format(nameAr[k])))
            if intAr[k][histTypeItr]:
                drawInvAr[-1].append(True)

                tmpNBins = histAr[k][histTypeItr].GetNbinsX()
                tmpBinErrorAr = []
                for i in range(tmpNBins):
                    tmpBinErrorAr.append(histAr[k][histTypeItr].GetBinError(i))
                for j in range(k):
                    if not isSignalAr[j] and (not sumQCD or not isQCDAr[j]):
                        invHistsAr[-1][histTypeItr].Add(histAr[j][histTypeItr])
                for i in range(tmpNBins):
                    invHistsAr[-1][histTypeItr].SetBinError(i,tmpBinErrorAr[i])
            else:
                drawInvAr[-1].append(False)
    if sumQCD:
      drawInvAr.append([])
      invHistsAr.append([])
      cloneHistAr.append([])
      for histTypeItr in range(len(histTypeSaveNameAr)):
        if onlyDoSomeHists and histTypeItr >= histsToDo:
          break
        cloneHistAr[-1].append(QCDSumHist[histTypeItr].Clone())
        if QCDSumInt[histTypeItr]:
            #cloneHistAr[-1].append(QCDSumHist[histTypeItr].Clone())
            drawInvAr[-1].append(True)
            invHistsAr[-1].append(QCDSumHist[histTypeItr].Clone("{0}HistQCDSumInv".format(histTypeSaveNameAr[histTypeItr])))
            tmpNBins = QCDSumHist[histTypeItr].GetNbinsX()
            tmpBinErrorAr = []
            for i in range(tmpNBins):
              tmpBinErrorAr.append(QCDSumHist[histTypeItr].GetBinError(i))
            for j in range(k):
              if not isSignalAr[j] and not isQCDAr[j]:
                #print(j,histTypeItr)
                #print(len(invHistsAr))
                #print(len(invHistsAr[-1]))
                #print(len(histAr))
                #print(len(histAr[j]))
                invHistsAr[-1][histTypeItr].Add(histAr[j][histTypeItr])
            for i in range(tmpNBins):
              invHistsAr[-1][histTypeItr].SetBinError(i,tmpBinErrorAr[i])
        else:
            drawInvAr[-1].append(False)


def setUpStackedHistAndDrawFoMPlot(histMax,histAr,cloneHistAr,histStack,invHistsAr,drawInvAr,legAr,compCan,padAr,normalizeBackgroundsTogether,signalName,backgroundName,histTypeSaveNameAr,histTypeXTitleAr,signalPos,onlyDoSomeHists,histsToDo):
    #maxForRange = 1.1*histMax
    #histAr[1].GetYaxis().SetRangeUser(0,maxForRange)
    for histTypeItr, histTypeSaveName in enumerate(histTypeSaveNameAr):
      if onlyDoSomeHists and histTypeItr >= histsToDo:
        break
      
      
      compCan[histTypeItr].cd()
      padAr[histTypeItr][0].Draw()
      padAr[histTypeItr][0].cd()
      histStack[histTypeItr].Draw("hist")
      makeNiceTHStack(histStack[histTypeItr],"","Events",True)
      tmpMax = histStack[histTypeItr].GetMaximum()
      if tmpMax < histMax[histTypeItr]:
          histStack[histTypeItr].SetMaximum(histMax[histTypeItr])
      histStack[histTypeItr].Draw("same hist")

      for k in range(len(invHistsAr)):
          #print(k,histTypeItr)
          #print(cloneHistAr)
          #print(histAr)
          #print(cloneHistAr[k])
          #print(histAr[k])
          #print(histAr[k][histTypeItr])
          #cloneHistAr[k].append(histAr[k][histTypeItr].Clone())

          if drawInvAr[k][histTypeItr]:
              print("passed")
              invHistsAr[k][histTypeItr].SetStats(0)
              invHistsAr[k][histTypeItr].Draw("same E1")

      histAr[signalPos][histTypeItr].Draw("same hist E1")
      legAr[histTypeItr].Draw()


      compCan[histTypeItr].cd()

      setUpBottomPadsAr(padAr[histTypeItr])

      histAr[signalPos][histTypeItr].Sumw2()
      #print(len(cloneHistAr))
      ############ remove
      #testCan = TCanvas()
      #histAr[signalPos][histTypeItr].Draw("hist")
      #testCan.SaveAs("test0_{0}.png".format(histTypeItr))
      ############ remove
      for k in range(len(cloneHistAr)):
        #print(cloneHistAr[k][histTypeItr])
        #print(histAr[signalPos][histTypeItr])
        ############ remove
        #testCan = TCanvas()
        #cloneHistAr[k][histTypeItr].Draw("hist")
        #testCan.SaveAs("test{0}_{1}.png".format(k+1,histTypeItr))
        ############ remove
        #print(k,histTypeItr)
        #print(cloneHistAr)
        cloneHistAr[k][histTypeItr].Sumw2()
        cloneHistAr[k][histTypeItr].Divide(histAr[signalPos][histTypeItr])
        makeNiceHistos(cloneHistAr[k][histTypeItr],histTypeXTitleAr[histTypeItr],"Ratio to Signal",False)
        cloneHistAr[k][histTypeItr].SetLineWidth(2)
        if k == 0:
          cloneHistAr[k][histTypeItr].GetYaxis().SetRangeUser(0.,2.0)
        cloneHistAr[k][histTypeItr].Draw("et same")


      compCan[histTypeItr].Update()
      compCan[histTypeItr].Draw()

      #REPLACE WITH RATIO PAD
      """
      setUpGraphs(FoMGraph,3,22,"{0} Comparison Plot".format(histTypeSaveName),cutName,"SQRT(2*(((S+B)*log(1+(S/B)))-S))")
      FoMGraph.GetXaxis().SetRangeUser(cutRange[0],cutRange[1])
      FoMGraph.Draw("APL* same")
      #FoMCan.Update()
      #tmpFoMMin = FoMGraph.GetMinimum()
      tmpFoMMin = 0
      tmpFoMMax = FoMGraph.GetMaximum()
      defaultCutLine = TLine(defaultCutPos,tmpFoMMin,defaultCutPos,histMax)
      defaultCutLine.SetLineColor(2)
      defaultCutLine.SetLineWidth(4)
      defaultCutLine.SetLineStyle(9)
      defaultCutLine.Draw()
      compCan.Update()
      """
      #"FP" stands for "Full Pass"
      if normalizeBackgroundsTogether:
          if savePathBool:
            compCan[histTypeItr].SaveAs("./Graphs/Comparison/ComparisonFor{0}_{1}_Vs_{2}_Stacked_NBT_{3}.png".format(histTypeSaveName,signalName,backgroundName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
          else:
            compCan[histTypeItr].SaveAs("ComparisonFor{0}_{1}_Vs_{2}_Stacked_NBT_{3}.png".format(histTypeSaveName,signalName,backgroundName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
      else:
          if savePathBool:
            compCan[histTypeItr].SaveAs("./Graphs/Comparison/ComparisonFor{0}_{1}_Vs_{2}_Stacked_{3}.png".format(histTypeSaveName,signalName,backgroundName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
          else:
            compCan[histTypeItr].SaveAs("ComparisonFor{0}_{1}_Vs_{2}_Stacked_{3}.png".format(histTypeSaveName,signalName,backgroundName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))



def setUpNonStackedHistAndFoMPlot(compCan,cloneHistAr,padAr,sumQCD,QCDSumHist,histMax,isSignalAr,isQCDAr,normalizeBackgroundsTogether,maxInt,histAr,legAr,signalName,backgroundName,histTypeSaveNameAr,histTypeTitleAr,histTypeXTitleAr,signalPos,onlyDoSomeHists,histsToDo):
  for histTypeItr, histTypeSaveName in enumerate(histTypeSaveNameAr):
    if onlyDoSomeHists and histTypeItr >= histsToDo:
        break


    compCan[histTypeItr].cd()
    padAr[histTypeItr][0].Draw()
    padAr[histTypeItr][0].cd()

    
    ##############
    #Rescale signal hist
    if sumQCD:
        tmpMax = QCDSumHist[histTypeItr].GetMaximum()
        if tmpMax > histMax[histTypeItr]:
            histMax[histTypeItr] = tmpMax
    if normalizeBackgroundsTogether:
        tmpMaxSignal = histAr[signalPos][histTypeItr].GetMaximum()
        if tmpMaxSignal:
          tmpMaxRatio = histMax[histTypeItr]/tmpMaxSignal
        else:
          tmpMaxRatio = 1

        #tmpSignalInt = histAr[1].Integral()
        histAr[signalPos][histTypeItr].Sumw2()
        histAr[signalPos][histTypeItr].Scale(tmpMaxRatio)
        #histAr[1].Scale(maxInt/tmpSignalInt)
    tmpMax = histAr[signalPos][histTypeItr].GetMaximum()
    if tmpMax > histMax[histTypeItr]:
        histMax[histTypeItr] = tmpMax
    if signalPos == 1:
      histAr[0][histTypeItr].GetYaxis().SetRangeUser(0,histMax[histTypeItr]*1.1)
      histAr[0][histTypeItr].SetTitle(histTypeTitleAr[histTypeItr])
      histAr[0][histTypeItr].Draw("hist E1")
    else:
      histAr[1][histTypeItr].GetYaxis().SetRangeUser(0,histMax[histTypeItr]*1.1)
      histAr[1][histTypeItr].SetTitle(histTypeTitleAr[histTypeItr])
      histAr[1][histTypeItr].Draw("hist E1")

    if sumQCD:
        QCDSumHist[histTypeItr].DrawCopy("same hist E1")
    for j in range(2,len(histAr)):
        if not isSignalAr[j] and (not sumQCD or not isQCDAr[j]):
            histAr[j][histTypeItr].DrawCopy("same hist E1")
    histAr[signalPos][histTypeItr].DrawCopy("same hist E1")
    
  
    legAr[histTypeItr].Draw()
    compCan[histTypeItr].cd()

    setUpBottomPadsAr(padAr[histTypeItr]) 

    histAr[signalPos][histTypeItr].Sumw2()
    for k in range(len(cloneHistAr)):
        #cloneHistAr[k][histTypeItr].Sumw2()
        #cloneHistAr[k][histTypeItr].Divide(histAr[signalPos][histTypeItr])
        #makeNiceHistos(cloneHistAr[k][histTypeItr],histTypeXTitleAr[histTypeItr],"Ratio to Signal",False)
        #cloneHistAr[k][histTypeItr].SetLineWidth(2)
        cloneHistAr[k][histTypeItr].Draw("et same")


    compCan[histTypeItr].Update()
    compCan[histTypeItr].Draw()


    #REPLACE WITH RATIO PAD
    """
    FoMGraph.Draw("APL same")
    #compCan.Update()
    #tmpFoMMin = FoMGraph.GetMinimum()
    tmpFoMMin = 0
    tmpFoMMax = FoMGraph.GetMaximum()
    defaultCutLine = TLine(defaultCutPos,tmpFoMMin,defaultCutPos,histMax)
    defaultCutLine.SetLineColor(2)
    defaultCutLine.SetLineWidth(4)
    defaultCutLine.SetLineStyle(9)
    defaultCutLine.Draw()
    compCan.Update()
    #"FP" stands for "Full Pass"
    """
    if normalizeBackgroundsTogether:
      if savePathBool:
        compCan[histTypeItr].SaveAs("./Graphs/Comparison/ComparisonFor{0}_{1}_Vs_{2}_NBT_{3}.png".format(histTypeSaveName,signalName,backgroundName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
      else:
        compCan[histTypeItr].SaveAs("ComparisonFor{0}_{1}_Vs_{2}_NBT_{3}.png".format(histTypeSaveName,signalName,backgroundName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
    else:
      if savePathBool:
        compCan[histTypeItr].SaveAs("./Graphs/Comparison/ComparisonFor{0}_{1}_Vs_{2}_{3}.png".format(histTypeSaveName,signalName,backgroundName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
      else:
        compCan[histTypeItr].SaveAs("ComparisonFor{0}_{1}_Vs_{2}_{3}.png".format(histTypeSaveName,signalName,backgroundName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))

    
