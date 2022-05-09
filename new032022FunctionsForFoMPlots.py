import datetime
from array import array
from math import sqrt
from ROOT import TFile, TChain, gDirectory, TApplication, TMath, Math, TMinuit, TROOT, TSystem, TTree, TVector2
from ROOT import THStack, TH1D, TCanvas, TPad, TF1, TGraph, TMultiGraph, TGraphErrors, TLegend, TLine, TPaveText, TStyle
from ROOT import TH2D, TH2F,gPad
from math import sqrt,pi,log

ZMass = 91.1876

weakCuts = False

VBFJetdRCut = 0.4

VBFJetPtCut = 50.
VBFJetEtaCut = 2.0
VBFJetInvMassCut = 400.
SemiLepFatJetPtCut = 200.

hFatJetPtCut = 300.

hFatJetDeepTagCut = 0.9
scaleSignalToBackground = True

LepePtCut = 7.
LepeEtaCut = 2.5
LepmPtCut = 5.
LepmEtaCut = 2.4
SemiLepePtCut = 7.
SemiLepeEtaCut = 2.5
SemiLepmPtCut = 5.
SemiLepmEtaCut = 2.4

useLogY = True


SemiLepInvMassCutLowCut=80.
SemiLepInvMassCutHighCut=100.
InvMassCutLowCut=80.
InvMassCutHighCut=100.
SemiLepPtLeadCut=20.
SemiLepPtTrailingCut=10.
PtLeadCut=20.
PtTrailingCut=10.
FourLepInvMassCut = 100.
OptLepInvMassCut = 12.
LepIsoCut = 0.35
SIPCut = 4.
SemiLepFatJetZTagCut = 0.8

if weakCuts:
    VBFJetdRCut = 0.1

    VBFJetPtCut = 20.

    VBFJetEtaCut = 1.0

    VBFJetInvMassCut = 200.

    hFatJetPtCut = 200.

    hFatJetDeepTagCut = 0.1

    LepePtCut = 1.

    LepeEtaCut = 3.0

    LepmPtCut = 1.

    LepmEtaCut = 3.0


    SemiLepePtCut = 1.

    SemiLepeEtaCut = 3.0

    SemiLepmPtCut = 1.

    SemiLepmEtaCut = 3.0

    SemiLepInvMassCutLowCut = 40.

    SemiLepInvMassCutHighCut = 140.

    InvMassCutLow=40.

    InvMassCutHigh=140.

    PtLeadCut=10.

    PtTrailingCut=5.

    FourLepInvMassCut = 50.

    OptLepInvMassCut = 6.

    LepIsoCut = 1.5

    SIPCut = 5.5


    SemiLepFatJetZTagCut = 0.1

defaultCutPosAr = [hFatJetPtCut,hFatJetDeepTagCut,VBFJetPtCut,VBFJetdRCut,VBFJetEtaCut,
VBFJetInvMassCut,SemiLepmPtCut,SemiLepmEtaCut,SemiLepePtCut,
SemiLepeEtaCut,SemiLepPtLeadCut,SemiLepPtTrailingCut,SemiLepInvMassCutLowCut,
SemiLepInvMassCutHighCut,SemiLepFatJetPtCut,SemiLepFatJetZTagCut,LepmPtCut,
LepmEtaCut,LepeEtaCut,LepePtCut,PtLeadCut,PtTrailingCut,InvMassCutLowCut,
InvMassCutHighCut,FourLepInvMassCut,OptLepInvMassCut,LepIsoCut,SIPCut]
#cutsToPlot = [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15] #SL
cutsToPlot = [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15] #SL
#cutsToPlot = [0,1,2,3,4,5,16,17,18,19,20,21,22,23,24,25,26,27] #Lep
#cutsToPlot = [0,1,2,3,4,5,12,13,14,15,22,23,24,26,27]
#cutsToPlot = [i for i in range(len(defaultCutPosAr))] #All
#badCutIndsForSL = [0,2,3,4,5,6,7,8,9,10,11,12,13,14,15]
badCutIndsForSL = []
today = datetime.datetime.today()

def find2ndToLast(a,b,c,d):
    abMin = min(a,b)
    cdMin = min(c,d)
    abMax = max(a,b)
    cdMax = max(c,d)
    if abMin > cdMin:
        if abMin > cdMax:
            return cdMax
        else:
            return abMin
    else:
        if cdMin > abMax:
            return abMax
        else:
            return cdMin

def makeNiceTHStack(histo,xTitle,yTitle,noX=True):
  #print("testAlt1")
  if noX:
    histo.GetXaxis().SetLabelOffset(999)
    #print("testAlt11")
    histo.GetXaxis().SetLabelSize(0)
  else:
    histo.GetXaxis().SetTitle(xTitle)
    histo.GetXaxis().SetTitleSize(0.068)
    histo.GetXaxis().SetTitleFont(42)
    histo.GetXaxis().SetLabelFont(42)
    histo.GetXaxis().SetLabelSize(0.055)
  #print("testAlt2")
  histo.GetYaxis().SetTitle(yTitle)
  histo.GetYaxis().CenterTitle()
  #print("testAlt3")
  histo.GetYaxis().SetTitleOffset(0.55)
  histo.GetYaxis().SetTitleSize(0.068)
  #print("testAlt4")
  histo.GetYaxis().SetTitleFont(42)
  histo.GetYaxis().SetLabelFont(42)
  #print("testAlt5")
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

def FoMCalc(signalAr,backgroundAr,graphAr,xAr, cutAmnt,cutRangeAr):
    for c,cutRangeVal in enumerate(cutRangeAr):
        tmpSignal = signalAr[c]
        #print(tmpSignal)
        tmpBackground = backgroundAr[c]
        if tmpSignal > 0:
            if tmpBackground == 0:
                tmpFoM = tmpSignal/(sqrt(tmpSignal+tmpBackground))
            else:
                #print("tmpSignal",tmpSignal,"tmpBackground",tmpBackground)
                tmpFoM = sqrt(2*(((tmpSignal+abs(tmpBackground))*log(1+(tmpSignal / abs(tmpBackground))))-tmpSignal))
        else:
            tmpFoM = 0
        graphAr.append(tmpFoM)
        xAr.append(cutRangeVal)


def makeEvPassGraphs(nameAr,evPassCanAr,evPassGraphAr,evPassGraphsAr,xAr,cutName):
    for k,nameA in enumerate(nameAr):
        evPassCanAr.append(TCanvas("c1{0}{1}".format(cutName,nameA),"c1{0}{1}".format(cutName,nameA),3600,2400))
        #print(len(evPassGraphAr[k]))
        #print(xAr)
        #print(evPassGraphAr[k])
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
            histAr[j].SetLineWidth(4)
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
        QCDSumHist.SetLineColor(28)
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

def setUpStackedHistAndDrawFoMPlot(histMax,histAr,histStack,invHistsAr,drawInvAr,legAr,FoMCan,padAr,FoMGraph,cutRange,normalizeBackgroundsTogether,cutName,signalName,backgroundName,defaultCutPos):
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
    
    setUpGraphs(FoMGraph,3,22,"{0} FoM Plot".format(cutName),cutName,"SQRT(2*(((S+B)*log(1+(S/B)))-S))")
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
    FoMCan.Update()
    #"FP" stands for "Full Pass"
    if normalizeBackgroundsTogether:
        FoMCan.SaveAs("FoMGraph_FP_{0}_{1}_Vs_{2}_AMSFoM_WithComparisonHist_Stacked_NBT_V2_{3}.png".format(cutName,signalName,backgroundName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
    else:
        FoMCan.SaveAs("FoMGraph_FP_{0}_{1}_Vs_{2}_AMSFoM_WithComparisonHist_Stacked_V2_{3}.png".format(cutName,signalName,backgroundName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))


def setUpNonStackedHistAndFoMPlot(FoM2Can,cutName,padAr,sumQCD,QCDSumHist,histMax,isSignalAr,isQCDAr,normalizeBackgroundsTogether,maxInt,histAr,legAr,FoMGraph,signalName,backgroundName,defaultCutPos):
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
    #FoM2Can.Update()
    #tmpFoMMin = FoMGraph.GetMinimum()
    tmpFoMMin = 0
    tmpFoMMax = FoMGraph.GetMaximum()
    defaultCutLine = TLine(defaultCutPos,tmpFoMMin,defaultCutPos,histMax)
    defaultCutLine.SetLineColor(2)
    defaultCutLine.SetLineWidth(4)
    defaultCutLine.SetLineStyle(9)
    defaultCutLine.Draw()
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
    #gGraph.GetYaxis().CenterTitle()
    #gGraph.SetLineColor(lineColor)
    gGraph.GetXaxis().SetLabelFont(42)
    gGraph.GetXaxis().SetLabelSize(0.035)
    gGraph.GetXaxis().SetTitleFont(42)
    gGraph.GetYaxis().SetLabelFont(42)
    gGraph.GetYaxis().SetLabelSize(0.035)
    gGraph.GetYaxis().SetTitleFont(42)
    gGraph.GetYaxis().SetTitleOffset(1.2)
    gGraph.GetXaxis().SetTitleOffset(0.9)


def makeFoMPlots(evPassVarCutAr,varCutSignalPassAr,varCutBackgroundPassAr,weightsSignalAr,weightsBackgroundAr,varCutRangeAr,cutAmnt,cutNameAr,nameAr,skipEvPassGraphs,saveName,isSignalAr,isQCDAr,anyQCD,chanName):
    #print(evPassVarCutAr)
    for cutInd,cutName in enumerate(cutNameAr):
        if cutInd > 1:
            break
        varCutEvPassGraphAr = []
        for evPassVarCutA in evPassVarCutAr[cutInd]:
            varCutEvPassGraphAr.append(array('d'))
            for evPassVarCut in evPassVarCutA:
                #print(evPassVarCut)
                varCutEvPassGraphAr[-1].append(evPassVarCut)



        varCutSignalSumAr = [0 for i in range(cutAmnt+1)]
        varCutBackgroundSumAr = [0 for i in range(cutAmnt+1)]
        #for varCutSignalPass in varCutSignalPassAr:
        #    #print(len(varCutSignalPass))
        for varCutSignalPass,weightsSignal in zip(varCutSignalPassAr[cutInd],weightsSignalAr):
            for c in range(cutAmnt+1):
                #print(c)
                varCutSignalSumAr[c] += varCutSignalPass[c]*weightsSignal
        for varCutBackgroundPass,weightsBackground in zip(varCutBackgroundPassAr[cutInd],weightsBackgroundAr):
            for c in range(cutAmnt+1):
                varCutBackgroundSumAr[c] += varCutBackgroundPass[c]*weightsBackground
        #print(passesCandCutsCtr)
        #print(passesZ1CutsCtr)
        #print(passesZ2CutsCtr)
        #print(passesIsoCutCtr)
        #print(passesAllCutsCtr)
        #print(allPassAr)

        #print(varCutSignalAr)
        #print(varCutBackgroundAr)

        varCutGraphAr = array('d')
        varCutXAr = array('d')

        #Calculate FoM for each point
        #print(len(varCutSignalSumAr),len(varCutBackgroundSumAr),len(varCutRangeAr),cutAmnt)
        FoMCalc(varCutSignalSumAr,varCutBackgroundSumAr,varCutGraphAr,varCutXAr,cutAmnt,varCutRangeAr[cutInd])

        FoMVarCutGraph = TGraph(len(varCutGraphAr),varCutXAr,varCutGraphAr)
        tmpCan = TCanvas("c1{0}".format(cutName),"c1{0}".format(cutName),3600,2400)
        
        setUpGraphs(FoMVarCutGraph,3,22,"FoM Plot for {0}".format(cutName),cutName,"FoM Value")
        FoMVarCutGraph.Draw("APL*")
        tmpCan.Draw()
        #"FP" stands for "Full Pass"
        tmpCan.SaveAs("FoMPlot_{0}_{1}_{2}.png".format(saveName,cutName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))



        #make evpass graphs

        evPassVarCutGraphAr = []
        evPassVarCutCanAr = []

        if not skipEvPassGraphs:
            makeEvPassGraphs(nameAr,evPassVarCutCanAr,varCutEvPassGraphAr,evPassVarCutGraphAr,varCutXAr,cutName)
        evPassMGAr = []
        legAr = []
        makeEvPassMultiGraphs(nameAr,evPassVarCutCanAr,evPassMGAr,varCutEvPassGraphAr,evPassVarCutGraphAr,varCutXAr,cutName,isSignalAr,weightsSignalAr,weightsBackgroundAr,legAr,isQCDAr,anyQCD,varCutRangeAr[cutInd],chanName)


def makeEvPassMultiGraphs(nameAr,evPassCanAr,evPassMGAr,evPassGraphAr,evPassGraphsAr,xAr,cutName,isSignalAr,weightsSignalAr,weightsBackgroundAr,legAr,isQCDAr,anyQCD,varCutRange,chanName):
    tmpSigAdd = 0
    tmpBackAdd = 0
    evPassCanAr.append(TCanvas("c1MG{0}".format(cutName),"c1MG{0}".format(cutName),3600,2400))
    evPassMGAr.append(TMultiGraph())
    setUpLegend(legAr)
    QCDGraphAr = array('d')
    subQCDInd = 0
    yellowSkip = 0
    if anyQCD:
        for varCutPoint in range(len(varCutRange)):
            QCDGraphAr.append(0)
    for k,nameA in enumerate(nameAr):
        tmpMult = 1
        if isSignalAr[k]:
            tmpMult = weightsSignalAr[tmpSigAdd]
            tmpSigAdd += 1
        else:
            tmpMult = weightsBackgroundAr[tmpBackAdd]
            tmpBackAdd += 1
        #weighting the data sets
        for evPassGraphInd in range(len(evPassGraphAr[k])):
            evPassGraphAr[k][evPassGraphInd] *= tmpMult
        
        if isQCDAr[k]:
            subQCDInd += 1
            for evPassGraphInd in range(len(evPassGraphAr[k])):
                QCDGraphAr[evPassGraphInd] += evPassGraphAr[k][evPassGraphInd]
        else:
            evPassGraphsAr.append(TGraph(len(evPassGraphAr[k]),xAr,evPassGraphAr[k]))
            setUpGraphs(evPassGraphsAr[-1],3,22,"{0}".format(nameA),cutName,"Events Passing Cut")
            if k == 4:
                yellowSkip += 1
            evPassGraphsAr[-1].SetLineColor(k+1-subQCDInd+yellowSkip)
            evPassMGAr[-1].Add(evPassGraphsAr[-1],"lp")
    if anyQCD:
        evPassGraphsAr.append(TGraph(len(QCDGraphAr),xAr,QCDGraphAr))
        setUpGraphs(evPassGraphsAr[-1],3,22,"QCD Sum",cutName,"Events Passing Cut")
        evPassGraphsAr[-1].SetLineColor(k+2-subQCDInd+yellowSkip)
        evPassMGAr[-1].Add(evPassGraphsAr[-1],"lp")
    evPassCanAr[-1].SetLogy()
    setUpGraphs(evPassMGAr[-1],3,22,"Weighted Passing Events in {0} Channel Vs {1} Cut".format(chanName,cutName[:-3]),cutName,"Weighted Events Passing Cut")
    evPassMGAr[-1].Draw("A*")
    evPassCanAr[-1].BuildLegend()
    evPassCanAr[-1].Draw()
    evPassCanAr[-1].SaveAs("evPassCutMultiGraph_FP_{0}_V2_{1}.png".format(cutName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))


def makeFoMWithEvPassPlots(evPassVarCutAr,varCutSignalPassAr,varCutBackgroundPassAr,weightsSignalAr,weightsBackgroundAr,varCutRangeAr,cutAmnt,cutNameAr,nameAr,skipEvPassGraphs,saveName,isSignalAr,isQCDAr,anyQCD,chanName,defaultCutPosAr,logOrNot,cutsToPlot,badCutIndsForSL):
    #print(evPassVarCutAr)
    padAr = []
    legAr = []
    evPassMGAr = []
    evPassVarCutGraphAr = []
    evPassVarCutCanAr = []
    tmpGraphHold = []

    for cutInd,cutName in enumerate(cutNameAr):
        if not cutInd in cutsToPlot:
            continue
        #if cutInd > 1:
        #    break
        varCutEvPassGraphAr = []
        for evPassVarCutA in evPassVarCutAr[cutInd]:
            varCutEvPassGraphAr.append(array('d'))
            for evPassVarCut in evPassVarCutA:
                #print(evPassVarCut)
                varCutEvPassGraphAr[-1].append(evPassVarCut)



        varCutSignalSumAr = [0 for i in range(cutAmnt+1)]
        varCutBackgroundSumAr = [0 for i in range(cutAmnt+1)]
        #for varCutSignalPass in varCutSignalPassAr:
        #    #print(len(varCutSignalPass))
        for varCutSignalPass,weightsSignal in zip(varCutSignalPassAr[cutInd],weightsSignalAr):
            print(varCutSignalPass,weightsSignal)
            for c in range(cutAmnt+1):
                #print(c)
                varCutSignalSumAr[c] += varCutSignalPass[c]*weightsSignal
        for varCutBackgroundPass,weightsBackground in zip(varCutBackgroundPassAr[cutInd],weightsBackgroundAr):
            print(varCutBackgroundPass,weightsBackground)
            for c in range(cutAmnt+1):
                varCutBackgroundSumAr[c] += varCutBackgroundPass[c]*weightsBackground

        varCutGraphAr = array('d')
        varCutXAr = array('d')

        #Calculate FoM for each point
        FoMCalc(varCutSignalSumAr,varCutBackgroundSumAr,varCutGraphAr,varCutXAr,cutAmnt,varCutRangeAr[cutInd])
        #Evpass top plot
        evPassVarCutCanAr.append(TCanvas("c1MG{0}".format(cutName),"c1MG{0}".format(cutName),3600,2400))
        setUpPadsAr(padAr,"{0}Pad".format(cutName))
        tmpSigAdd = 0
        tmpBackAdd = 0
        
        evPassMGAr.append(TMultiGraph())
        setUpLegend(legAr)
        QCDGraphAr = array('d')
        subQCDInd = 0
        yellowSkip = 0
        graySkip = 0
        if anyQCD:
            for varCutPoint in range(len(varCutRangeAr[cutInd])):
                QCDGraphAr.append(0)
        for k,nameA in enumerate(nameAr):
            tmpMult = 1
            if isSignalAr[k]:
                tmpMult = weightsSignalAr[tmpSigAdd]
                tmpSigAdd += 1
            else:
                tmpMult = weightsBackgroundAr[tmpBackAdd]
                tmpBackAdd += 1
            #weighting the data sets
            for evPassGraphInd in range(len(varCutEvPassGraphAr[k])):
                varCutEvPassGraphAr[k][evPassGraphInd] *= tmpMult
            
            if isQCDAr[k]:
                subQCDInd += 1
                for evPassGraphInd in range(len(varCutEvPassGraphAr[k])):
                    QCDGraphAr[evPassGraphInd] += varCutEvPassGraphAr[k][evPassGraphInd]
            else:
                evPassVarCutGraphAr.append(TGraph(len(varCutEvPassGraphAr[k]),varCutXAr,varCutEvPassGraphAr[k]))
                setUpGraphs(evPassVarCutGraphAr[-1],3,22,"{0}".format(nameA),cutName,"Events Passing Cut")
                if k == 4:
                    yellowSkip += 1
                #if k == 8:
                #    graySkip += 1
                if k-subQCDInd == 8:
                    yellowSkip += 18
                if k-subQCDInd == 9:
                    yellowSkip += 1
                if k-subQCDInd == 10:
                    yellowSkip += 7
                if k-subQCDInd == 11:
                    yellowSkip += 7
                print(k,k-subQCDInd,yellowSkip,k+1-subQCDInd+yellowSkip)
                
                evPassVarCutGraphAr[-1].SetLineColor(k+1-subQCDInd+yellowSkip)
                evPassMGAr[-1].Add(evPassVarCutGraphAr[-1],"lp")
        if anyQCD:
            evPassVarCutGraphAr.append(TGraph(len(QCDGraphAr),varCutXAr,QCDGraphAr))
            setUpGraphs(evPassVarCutGraphAr[-1],3,46,"QCD Sum",cutName,"Events Passing Cut")
            evPassVarCutGraphAr[-1].SetLineColor(k+2-subQCDInd+yellowSkip)
            evPassMGAr[-1].Add(evPassVarCutGraphAr[-1],"lp")
        if not logOrNot or cutInd in badCutIndsForSL:
            evPassMGAr[-1].GetHistogram().SetMinimum(10**(-9))

        evPassVarCutCanAr[-1].SetLogy()
        setUpGraphs(evPassMGAr[-1],3,22,"Weighted Passing Events in {0} Channel Vs {1} Cut".format(chanName,cutName[:-3]),cutName,"Weighted Events Passing Cut")
        evPassMGAr[-1].Draw("A*")
        #if cutInd == 
        #   evPassMGAr[-1].GetHistogram().SetMinimum(10**(-9))
        evPassMGAr[-1].GetXaxis().SetLimits(varCutRangeAr[cutInd][0],varCutRangeAr[cutInd][-1])
        #if logOrNot:
        #    evPassVarCutCanAr[-1].SetLogy()
        evPassMGAr[-1].Draw("A*")
        evPassVarCutCanAr[-1].BuildLegend()
        setUpBottomPadsAr(padAr[-1])
        
        #tmpGraphHold = []
        #FoMVarCutGraph = TGraph(len(varCutGraphAr),varCutXAr,varCutGraphAr)
        tmpGraphHold.append(TGraph(len(varCutGraphAr),varCutXAr,varCutGraphAr))
        #No idea why it won't let me change the size
        """
        tmpGraphHold[-1].GetXaxis().SetLabelFont(42)
        tmpGraphHold[-1].GetXaxis().SetLabelSize(0.035)
        tmpGraphHold[-1].GetXaxis().SetTitleFont(42)
        tmpGraphHold[-1].GetYaxis().SetLabelFont(42)
        tmpGraphHold[-1].GetYaxis().SetLabelSize(0.035)
        tmpGraphHold[-1].GetYaxis().SetTitleFont(42)
        tmpGraphHold[-1].GetYaxis().SetTitleOffset(1.2)
        tmpGraphHold[-1].GetXaxis().SetTitleOffset(0.9)
        """
        setUpGraphs(tmpGraphHold[-1],3,22,"FoM Plot",cutName,"FoM Value")
        tmpGraphHold[-1].GetYaxis().CenterTitle()
        tmpGraphHold[-1].Draw("APL* same")
        print(varCutRangeAr[cutInd][0],varCutRangeAr[cutInd][1])
        tmpGraphHold[-1].GetXaxis().SetLimits(varCutRangeAr[cutInd][0],varCutRangeAr[cutInd][-1])
        
        tmpGraphHold[-1].Draw("APL* same")
        evPassVarCutCanAr[-1].Update()
        tmpFoMMin = 0
        tmpFoMMax = tmpGraphHold[-1].GetMaximum()
        
        defaultCutLine = TLine(defaultCutPosAr[cutInd],gPad.GetUymin(),defaultCutPosAr[cutInd],gPad.GetUymax())
        defaultCutLine.SetLineColor(2)
        defaultCutLine.SetLineWidth(3)
        defaultCutLine.SetLineStyle(9)
        defaultCutLine.Draw()
        evPassVarCutCanAr[-1].Update()
        evPassVarCutCanAr[-1].Draw()
        #"FP" stands for "Full Pass"
        print(cutInd)
        evPassVarCutCanAr[-1].SaveAs("FoMPlotWithEvPassMG_{0}_{1}_{2}.png".format(saveName,cutName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))


def MakeFoMCalcGraphs(FoMGraphAr,evPassVarCutAr,varCutSignalPassAr,varCutBackgroundPassAr,weightsSignalAr,weightsBackgroundAr,varCutRangeAr,cutAmnt,cutNameAr,nameAr,skipEvPassGraphs,saveName,isSignalAr,isQCDAr,anyQCD,chanName,defaultCutPosAr,logOrNot,cutsToPlot,badCutIndsForSL):
    #print(evPassVarCutAr)
    padAr = []
    legAr = []
    evPassMGAr = []
    evPassVarCutGraphAr = []
    evPassVarCutCanAr = []
    tmpGraphHold = []

    for cutInd,cutName in enumerate(cutNameAr):
        if not cutInd in cutsToPlot:
            continue
        #if cutInd > 1:
        #    break
        varCutEvPassGraphAr = []
        for evPassVarCutA in evPassVarCutAr[cutInd]:
            varCutEvPassGraphAr.append(array('d'))
            for evPassVarCut in evPassVarCutA:
                #print(evPassVarCut)
                varCutEvPassGraphAr[-1].append(evPassVarCut)



        varCutSignalSumAr = [0 for i in range(cutAmnt+1)]
        varCutBackgroundSumAr = [0 for i in range(cutAmnt+1)]
        #for varCutSignalPass in varCutSignalPassAr:
        #    #print(len(varCutSignalPass))
        for varCutSignalPass,weightsSignal in zip(varCutSignalPassAr[cutInd],weightsSignalAr):
            print(varCutSignalPass,weightsSignal)
            for c in range(cutAmnt+1):
                #print(c)
                varCutSignalSumAr[c] += varCutSignalPass[c]*weightsSignal
        for varCutBackgroundPass,weightsBackground in zip(varCutBackgroundPassAr[cutInd],weightsBackgroundAr):
            print(varCutBackgroundPass,weightsBackground)
            for c in range(cutAmnt+1):
                varCutBackgroundSumAr[c] += varCutBackgroundPass[c]*weightsBackground

        varCutGraphAr = array('d')
        varCutXAr = array('d')

        #Calculate FoM for each point
        FoMCalc(varCutSignalSumAr,varCutBackgroundSumAr,varCutGraphAr,varCutXAr,cutAmnt,varCutRangeAr[cutInd])
        

def setHistoElementsForFoM(colorAr,sumQCD,QCDSumHist,isQCDAr,histAr,isSignalAr,normalizeBackgroundsTogether,weightsAr,intAr,histTitleNameAr,onlyDoSomeHists,histsToDo,signalPos):
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
                  makeNiceHistos(histAr[k][histTypeItr],"","Weighted Events/Bin (pb)",True)
                  histAr[k][histTypeItr].SetTitle(histTitleName)
            else:
              if k == 1:
                  makeNiceHistos(histAr[k][histTypeItr],"","Weighted Events/Bin (pb)",True)
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





def addHistsToStackForFoM(fileAr,histAr,isSignalAr,sumQCD,isQCDAr,histStackAr,QCDSumHist,normalizeBackgroundsTogether,backgroundIntSum,histTypeSaveNameAr,signalPos,onlyDoSomeHists,histsToDo,weightsAr):
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
          if scaleSignalToBackground:
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
          #else:
          #  histAr[signalPos][histTypeItr].Sumw2()
          #  histAr[signalPos][histTypeItr].Scale(weightsAr[signalPos])

      maxIntAr.append(maxInt)
    return maxIntAr

def normalizeHistsForFoM(histAr,sumQCD,isQCDAr,normalizeBackgroundsTogether,backgroundIntSum,isSignalAr,weightsAr,legAr,nameAr,intAr,histTypeSaveNameAr,onlyDoSomeHists,histsToDo,signalPos):
    histMaxAr = []
    histMinAr = []
    for histTypeItr in range(len(histTypeSaveNameAr)):
      if onlyDoSomeHists and histTypeItr >= histsToDo:
        break
      histMaxAr.append(0)
      histMinAr.append(9999)
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
                
                #histAr[k][histTypeItr].Scale(weightsAr[k] / backgroundIntSum[histTypeItr])
                histAr[k][histTypeItr].Scale(weightsAr[k])
                tmpMax = histAr[k][histTypeItr].GetMaximum()
                if tmpMax > histMaxAr[histTypeItr]:
                    histMaxAr[histTypeItr] = tmpMax
                if tmpMax > 0 and tmpMax < histMinAr[histTypeItr]:
                    histMinAr[histTypeItr] = tmpMax

                legAr[histTypeItr].AddEntry(histAr[k][histTypeItr],nameAr[k],"l")
            elif intAr[k][histTypeItr]:
                #print(k,histTypeItr)
                #print(intAr[k][histTypeItr])
                print(k,isSignalAr[k])
                if scaleSignalToBackground or not isSignalAr[k]:
                  histAr[k][histTypeItr].Scale(1.0 / intAr[k][histTypeItr])
                elif normalizeBackgroundsTogether and not scaleSignalToBackground:
                  histAr[signalPos][histTypeItr].Sumw2()
                  histAr[signalPos][histTypeItr].Scale(weightsAr[signalPos])
                  tmpMax = histAr[k][histTypeItr].GetMaximum()
                  print(tmpMax)
                  if tmpMax > histMaxAr[histTypeItr]:
                    histMaxAr[histTypeItr] = tmpMax
                  if tmpMax > 0 and tmpMax < histMinAr[histTypeItr]:
                    histMinAr[histTypeItr] = tmpMax
                print("-----------------")

                tmpMax = histAr[k][histTypeItr].GetMaximum()
                if not normalizeBackgroundsTogether:
                  if tmpMax > histMaxAr[histTypeItr]:
                    histMaxAr[histTypeItr] = tmpMax
                  if tmpMax > 0 and tmpMax < histMinAr[histTypeItr]:
                    histMinAr[histTypeItr] = tmpMax
                legAr[histTypeItr].AddEntry(histAr[k][histTypeItr],nameAr[k],"l")
    return histMaxAr,histMinAr

def scaleQCDHistForFoM(QCDSumInt,QCDSumHist,histMaxAr,histMinAr,legAr,onlyDoSomeHists,histsToDo,normalizeBackgroundsTogether,backgroundIntSum):
  for histTypeItr in range(len(histMaxAr)):
    if onlyDoSomeHists and histTypeItr >= histsToDo:
      break
    if QCDSumInt[histTypeItr]:
      #print("QCDSumInt[histTypeItr]",QCDSumInt[histTypeItr])
      QCDSumHist[histTypeItr].Sumw2()
      """
      if normalizeBackgroundsTogether:
        QCDSumHist[histTypeItr].Scale(1.0 / backgroundIntSum[histTypeItr])
      else:
        QCDSumHist[histTypeItr].Scale(1.0 / QCDSumInt[histTypeItr])
      """
      if not normalizeBackgroundsTogether:
        QCDSumHist[histTypeItr].Scale(1.0 / QCDSumInt[histTypeItr])
      tmpMax = QCDSumHist[histTypeItr].GetMaximum()
      if tmpMax > histMaxAr[histTypeItr]:
        histMaxAr[histTypeItr] = tmpMax
      if tmpMax > 0 and tmpMax < histMinAr[histTypeItr]:
        histMinAr[histTypeItr] = tmpMax
      legAr[histTypeItr].AddEntry(QCDSumHist[histTypeItr],"QCDSum","l")
  return histMaxAr,histMinAr





def setUpInvHistsForFoM(histAr,cloneHistAr,isSignalAr,sumQCD,isQCDAr,invHistsAr,nameAr,intAr,drawInvAr,QCDSumInt,QCDSumHist,histTypeSaveNameAr,onlyDoSomeHists,histsToDo):
    for k in range(len(histAr)):
      
      if not isSignalAr[k] and (not sumQCD or not isQCDAr[k]):
        cloneHistAr.append([])
        invHistsAr.append([])
        drawInvAr.append([])
        for histTypeItr in range(len(histTypeSaveNameAr)):
            if onlyDoSomeHists and histTypeItr >= histsToDo:
              break
            cloneHistAr[-1].append(histAr[k][histTypeItr].Clone())
            print(k,histTypeItr)
            print(len(invHistsAr))
            print(len(histAr))
            print(len(histAr[k]))
            print(len(nameAr))
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



def setUpStackedHistAndDrawFoMPlotForFoM(histMax,histMin,histAr,cloneHistAr,histStack,invHistsAr,drawInvAr,legAr,compCan,padAr,normalizeBackgroundsTogether,signalName,backgroundName,histTypeSaveNameAr,histTypeXTitleAr,signalPos,onlyDoSomeHists,histsToDo,defaultCutPos,cutRange,FoMGraphAr,varCutGraphAr,varCutXAr,chanName):
    #maxForRange = 1.1*histMax
    #histAr[1].GetYaxis().SetRangeUser(0,maxForRange)

    for histTypeItr, histTypeSaveName in enumerate(histTypeSaveNameAr):
      if onlyDoSomeHists and histTypeItr >= histsToDo:
        break
      #if histTypeItr == 0:
      #    continue
      #print("test1")
      compCan[histTypeItr].cd()
      #print("test11")
      if useLogY:
        padAr[histTypeItr][0].SetLogy()
      padAr[histTypeItr][0].Draw()
      padAr[histTypeItr][0].cd()
      #print("test12")
      histStack[histTypeItr].Draw("hist")
      #print("test121")
      makeNiceTHStack(histStack[histTypeItr],"","Weighted Events/Bin (pb)",True)

      #print("test122")
      tmpMax = histStack[histTypeItr].GetMaximum()
      #print("test13")
      if tmpMax < histMax[histTypeItr]:
          histStack[histTypeItr].SetMaximum(histMax[histTypeItr])
      if tmpMax > 0 and tmpMax > histMin[histTypeItr]:
          histStack[histTypeItr].SetMinimum(histMin[histTypeItr])
      histStack[histTypeItr].Draw("same hist")
      #print("test2")
      for k in range(len(invHistsAr)):
          #print(k,histTypeItr)
          #print(cloneHistAr)
          #print(histAr)
          #print(cloneHistAr[k])
          #print(histAr[k])
          #print(histAr[k][histTypeItr])
          #cloneHistAr[k].append(histAr[k][histTypeItr].Clone())

          if drawInvAr[k][histTypeItr]:
              #print("passed")
              invHistsAr[k][histTypeItr].SetStats(0)
              invHistsAr[k][histTypeItr].Draw("same E1")
      #print("test3")

      histAr[signalPos][histTypeItr].Draw("same hist E1")
      legAr[histTypeItr].Draw()

      #print("test4")
      compCan[histTypeItr].cd()

      setUpBottomPadsAr(padAr[histTypeItr])
      #print("test5")
      histAr[signalPos][histTypeItr].Sumw2()
      #REPLACE WITH RATIO PAD
      FoMGraphAr.append(TGraph(len(varCutGraphAr[histTypeItr]),varCutXAr[histTypeItr],varCutGraphAr[histTypeItr]))
      #print("test6")
      setUpGraphs(FoMGraphAr[-1],3,22,"{0} Comparison Plot".format(histTypeSaveName),histTypeSaveName,"SQRT(2*(((S+B)*log(1+(S/B)))-S))")
      FoMGraphAr[-1].GetXaxis().SetRangeUser(cutRange[histTypeItr][0],cutRange[histTypeItr][1])
      FoMGraphAr[-1].Draw("APL* same")
      #FoMCan.Update()
      #tmpFoMMin = FoMGraph.GetMinimum()
      tmpFoMMin = 0
      tmpFoMMax = FoMGraphAr[-1].GetMaximum()
      defaultCutLine = TLine(defaultCutPos[histTypeItr],tmpFoMMin,defaultCutPos[histTypeItr],histMax[histTypeItr])
      defaultCutLine.SetLineColor(2)
      defaultCutLine.SetLineWidth(4)
      defaultCutLine.SetLineStyle(9)
      defaultCutLine.Draw()
      compCan[histTypeItr].Update()
      #print("test7")
      #"FP" stands for "Full Pass"
      if normalizeBackgroundsTogether:
        compCan[histTypeItr].SaveAs("ComparisonFor{0}_{1}_Vs_{2}_{3}Chan_Stacked_new042022_NBT_{4}.png".format(histTypeSaveName,signalName,backgroundName,chanName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
      else:
        compCan[histTypeItr].SaveAs("ComparisonFor{0}_{1}_Vs_{2}_{3}Chan_Stacked_new042022_{4}.png".format(histTypeSaveName,signalName,backgroundName,chanName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))



def setUpNonStackedHistAndFoMPlotForFoM(compCan,cloneHistAr,padAr,sumQCD,QCDSumHist,histMax,histMin,isSignalAr,isQCDAr,normalizeBackgroundsTogether,maxInt,histAr,legAr,signalName,backgroundName,histTypeSaveNameAr,histTypeTitleAr,histTypeXTitleAr,signalPos,onlyDoSomeHists,histsToDo):
  for histTypeItr, histTypeSaveName in enumerate(histTypeSaveNameAr):
    if onlyDoSomeHists and histTypeItr >= histsToDo:
        break


    compCan[histTypeItr].cd()
    if useLogY:
      padAr[histTypeItr][0].SetLogy()
    padAr[histTypeItr][0].Draw()
    padAr[histTypeItr][0].cd()

    
    ##############
    #Rescale signal hist
    if sumQCD:
        tmpMax = QCDSumHist[histTypeItr].GetMaximum()
        if tmpMax > histMax[histTypeItr]:
            histMax[histTypeItr] = tmpMax
        if tmpMax > 0 and tmpMax < histMin[histTypeItr]:
            histMin[histTypeItr] = tmpMax
    if normalizeBackgroundsTogether:
        tmpMaxSignal = histAr[signalPos][histTypeItr].GetMaximum()
        if tmpMaxSignal:
          tmpMaxRatio = histMax[histTypeItr]/tmpMaxSignal
        else:
          tmpMaxRatio = 1

        #tmpSignalInt = histAr[1].Integral()
        if scaleSignalToBackground:
          histAr[signalPos][histTypeItr].Sumw2()
          histAr[signalPos][histTypeItr].Scale(tmpMaxRatio)
          #histAr[1].Scale(maxInt/tmpSignalInt)
    tmpMax = histAr[signalPos][histTypeItr].GetMaximum()
    if tmpMax > histMax[histTypeItr]:
        histMax[histTypeItr] = tmpMax
    if tmpMax > 0 and tmpMax < histMin[histTypeItr]:
        histMin[histTypeItr] = tmpMax
    if signalPos == 1:
      if not useLogY:
        histAr[0][histTypeItr].GetYaxis().SetRangeUser(0,histMax[histTypeItr]*1.1)
      else:
        histAr[0][histTypeItr].GetYaxis().SetRangeUser(histMin[histTypeItr]*0.01,histMax[histTypeItr]*1.1)
      histAr[0][histTypeItr].SetTitle(histTypeTitleAr[histTypeItr])
      histAr[0][histTypeItr].Draw("hist E1")
    else:
      if not useLogY:
        histAr[1][histTypeItr].GetYaxis().SetRangeUser(0,histMax[histTypeItr]*1.1)
      else:
        histAr[1][histTypeItr].GetYaxis().SetRangeUser(histMin[histTypeItr]*0.01,histMax[histTypeItr]*1.1)
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

    setUpBottomPadsAr(padAr[histTypeItr],useLogYForRatioPlot) 

    histAr[signalPos][histTypeItr].Sumw2()
    for k in range(len(cloneHistAr)):
        #cloneHistAr[k][histTypeItr].Sumw2()
        #cloneHistAr[k][histTypeItr].Divide(histAr[signalPos][histTypeItr])
        #makeNiceHistos(cloneHistAr[k][histTypeItr],histTypeXTitleAr[histTypeItr],"Ratio to Signal",False)
        #cloneHistAr[k][histTypeItr].SetLineWidth(2)
        cloneHistAr[k][histTypeItr].Draw("et same")

    if useLogY:
      compCan[histTypeItr].SetLogy()

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

    
