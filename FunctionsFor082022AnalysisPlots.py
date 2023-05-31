import datetime
from ROOT import TLegend, TPad,TCanvas


today = datetime.datetime.today()


forCondor = False
scratchDown = True
if forCondor:
    if scratchDown:
      forCondorStr = "/afs/crc.nd.edu/user/d/dlutton/Public/condorStuff/NanoAODToHistos/tmpHoldForNanoAODWithoutScratch/"
    else:
      forCondorStr = "/scratch365/dlutton/HistosAndPNGs/KinematicsAnalysis/Slimmed/"
    savePathBool = False
else:
    forCondorStr = ""
    savePathBool = True


#For drawing and saving histograms
#Saves a png and, optionally, a pdf version
#Saves histogram to the currently active root file

testRun = False
MGOHW = False
MGSM = True

MGC2VEtaDifCut = False

SDC2V3MC = True
SDC2Vm2p5MC = False
SDC2Vm2MC = False
SDC2Vm1MC = False
SDC2V0MC = False
SDC2V1MC = False
SDC2V4MC = False
SDC2V4p5MC = False

ttZJets = True

MGOSix = False
MGOSixEtaDifCut = False
MGOHBox = False
MGOHBoxEtaDifCut = False
MGOHDD = False
MGOHDDEtaDifCut = False

normalizeDataTogether = False
makeUnstacked = True

comparisonPlotsOnly = True

useFillColorInPlots = False

useTightdRCut = False
tightCutStr = ""
if useTightdRCut:
  tightCutStr = "WithTighterdRCut"
onlyDoSomeHists = False
histsToDo = 2

breakEvEarly = False
breakEvAt = 2500


scaleSignalToBackground = False

useLogY = True
useLogYForRatioPlot = True


drawXSPlots = False
drawEvPlots = False
#ignoreHist = True
#ignoreHistInd = 13


XSxTitleAr = ["Cross Section"]
XShTitleAr = ["Cross Section"]
XSBinsAndRangeAr = [[50,-1,1]]

evNxTitleAr = ["Events","Normalized Events"]
evNhTitleAr = ["Total Events","Events Passing Higgs Jet Cuts"]
evNBinsAndRangeAr = [[4,132877,132881],[4,55628,55632]]

histAr = []
canAr = []


histLepAr = []
canLepAr = []


LepSaveNameAr = ["ZOneLep_massLL",
"ZTwoLep_massLL",
"H_ptLL"]


LepTitleAr = ["Lead Z Invariant Mass",
"Trailing Z Invariant Mass",
"H P_{T}"]

LepXTitleAr = ["Invariant Mass (GeV)",
"Invariant Mass (GeV)",
"P_{T} (GeV)"]

LepBinsAndRangeAr = [[20,70.,110.],
[20,70.,110.],
[34,0.,2500.]]


histSemiLepAr = []
canSemiLepAr = []


SemiLepSaveNameAr = ["ZOneLep_massSLL",
"H_ptSLL"]


SemiLepTitleAr = ["Lead Z Invariant Mass",
"H P_{T}"]

SemiLepXTitleAr = ["Invariant Mass (GeV)",
"P_{T} (GeV)",]

SemiLepBinsAndRangeAr = [[20,70.,110.],
[10,0.,2500.]]

yTitle = "Normalized Events"


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

def setUpBottomPadsAr(padAr,logYForRatioPlot):
  padAr[1].SetTopMargin(0)
  padAr[1].SetBottomMargin(0.15)
  if logYForRatioPlot:
    padAr[1].SetLogy()
  padAr[1].Draw()
  padAr[1].cd()

def makeNiceHistos(histo,xTitle,yTitle,noX=True):
  if noX:
    #histo.GetXaxis().SetLabelOffset(999)
    histo.GetXaxis().SetLabelSize(0)
  else:
    histo.GetXaxis().SetTitle(xTitle)
    histo.GetXaxis().SetTitleSize(0.048)
    histo.GetXaxis().SetTitleFont(42)
    histo.GetXaxis().SetLabelFont(42)
    histo.GetXaxis().SetLabelSize(0.045)
  histo.GetYaxis().SetTitle(yTitle)
  histo.GetYaxis().CenterTitle()
  histo.GetYaxis().SetTitleOffset(0.75)
  histo.GetYaxis().SetTitleSize(0.048)
  histo.GetYaxis().SetTitleFont(42)
  histo.GetYaxis().SetLabelFont(42)
  histo.GetYaxis().SetLabelSize(0.045)
  histo.SetTitle("")
  histo.SetStats(0)

  
def setHistoElementsForLHETrees(colorAr,histAr,weightsAr,intAr,histTitleNameAr,onlyDoSomeHists,histsToDo,useLHEAr,useFillColorInPlots,histTypeXTitleAr):
    for k,colorA in zip(range(len(colorAr)),colorAr):
      if useLHEAr[k]:
        intAr.append([])
        for histTypeItr, histTitleName in enumerate(histTitleNameAr):
          if onlyDoSomeHists and histTypeItr >= histsToDo:
            break
          
          histAr[k][histTypeItr].SetLineColor(colorA)
          histAr[k][histTypeItr].SetLineWidth(4)
          if useFillColorInPlots:
            histAr[k][histTypeItr].SetFillColorAlpha(colorA,0.2)
          makeNiceHistos(histAr[k][histTypeItr],histTypeXTitleAr[histTypeItr],"Normalized Events",False)
          histAr[k][histTypeItr].SetTitle(histTitleName)
          tmpHistInt = histAr[k][histTypeItr].Integral()
          intAr[-1].append(tmpHistInt)

def normalizeHistsForLHETrees(histAr,weightsAr,legAr,nameAr,intAr,histTypeSaveNameAr,onlyDoSomeHists,histsToDo,useLHEAr):
    histMaxAr = []
    for histTypeItr in range(len(histTypeSaveNameAr)):
      if onlyDoSomeHists and histTypeItr >= histsToDo:
        break
      histMaxAr.append(0)
    for k in range(len(histAr)):
      if useLHEAr[k]:
        for histTypeItr in range(len(histTypeSaveNameAr)):
          if onlyDoSomeHists and histTypeItr >= histsToDo:
            break
          
          histAr[k][histTypeItr].Sumw2()
          if normalizeDataTogether:
            histAr[k][histTypeItr].Scale(weightsAr[k])
          elif intAr[k][histTypeItr]:
              histAr[k][histTypeItr].Scale(1.0 / intAr[k][histTypeItr])
              
          tmpMax = histAr[k][histTypeItr].GetMaximum()
          if tmpMax > histMaxAr[histTypeItr]:
              histMaxAr[histTypeItr] = tmpMax
          legAr[histTypeItr].AddEntry(histAr[k][histTypeItr],nameAr[k],"l")
    return histMaxAr

def setUpNonStackedHistAndFoMPlotForLHETrees(compCan,cloneHistAr,padAr,histMax,histAr,legAr,dataName,histTypeSaveNameAr,histTypeTitleAr,histTypeXTitleAr,onlyDoSomeHists,histsToDo,useLHEAr,datasetSaveNameAr):
  for k in range(len(histAr)):
      if k != 0:
        if useLHEAr[k]:
            cloneHistAr.append([])
            for histTypeItr in range(len(histTypeSaveNameAr)):
                if onlyDoSomeHists and histTypeItr >= histsToDo:
                    break
                cloneHistAr[-1].append(histAr[k][histTypeItr].Clone())


  
  for histTypeItr, histTypeSaveName in enumerate(histTypeSaveNameAr):
    if onlyDoSomeHists and histTypeItr >= histsToDo:
        break


    compCan[histTypeItr].cd()
    padAr[histTypeItr][0].Draw()
    padAr[histTypeItr][0].cd()

    histAr[0][histTypeItr].GetYaxis().SetRangeUser(0,histMax[histTypeItr]*1.1)
    histAr[0][histTypeItr].SetTitle(histTypeTitleAr[histTypeItr])
    histAr[0][histTypeItr].Draw("hist E1")

    for j in range(1,len(histAr)):
      if useLHEAr[j]:
        histAr[j][histTypeItr].DrawCopy("same hist E1")
  
    legAr[histTypeItr].Draw()
    compCan[histTypeItr].cd()

    setUpBottomPadsAr(padAr[histTypeItr],useLogYForRatioPlot) 

    histAr[0][histTypeItr].Sumw2()
    for k in range(len(cloneHistAr)):
        cloneHistAr[k][histTypeItr].Sumw2()
        cloneHistAr[k][histTypeItr].Divide(histAr[0][histTypeItr])
        makeNiceHistos(cloneHistAr[k][histTypeItr],histTypeXTitleAr[histTypeItr],"Ratio to {0}".format(datasetSaveNameAr[0]),False)
        cloneHistAr[k][histTypeItr].SetLineWidth(2)
        if k == 0 and not useLogYForRatioPlot:
          cloneHistAr[k][histTypeItr].GetYaxis().SetRangeUser(0.,2.0)
        elif useLogYForRatioPlot:
          cloneHistAr[k][histTypeItr].GetYaxis().SetRangeUser(0.01,50.0)
        cloneHistAr[k][histTypeItr].Draw("et same")


    compCan[histTypeItr].Update()
    compCan[histTypeItr].Draw()

    compCan[histTypeItr].SaveAs("ComparisonFor{0}_{1}_{2}.png".format(histTypeSaveName,dataName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))

    """
    if normalizeDataTogether:
      if savePathBool:
        compCan[histTypeItr].SaveAs("./Graphs/Comparison/ComparisonFor{0}_{1}_NBT_{2}.png".format(histTypeSaveName,dataName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
      else:
        compCan[histTypeItr].SaveAs("ComparisonFor{0}_{1}_NBT_{2}.png".format(histTypeSaveName,dataName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
    else:
      if savePathBool:
        compCan[histTypeItr].SaveAs("./Graphs/Comparison/ComparisonFor{0}_{1}_{2}.png".format(histTypeSaveName,dataName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
      else:
        compCan[histTypeItr].SaveAs("ComparisonFor{0}_{1}_{2}.png".format(histTypeSaveName,dataName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
    """

    


def setUpNonStackedHistForLHETrees(compCan,cloneHistAr,histMax,histAr,legAr,dataName,histTypeSaveNameAr,histTypeTitleAr,histTypeXTitleAr,onlyDoSomeHists,histsToDo,useLHEAr,datasetSaveNameAr):
  for k in range(len(histAr)):
      if k != 0:
        if useLHEAr[k]:
            cloneHistAr.append([])
            for histTypeItr in range(len(histTypeSaveNameAr)):
                if onlyDoSomeHists and histTypeItr >= histsToDo:
                    break
                cloneHistAr[-1].append(histAr[k][histTypeItr].Clone())


  
  for histTypeItr, histTypeSaveName in enumerate(histTypeSaveNameAr):
    if onlyDoSomeHists and histTypeItr >= histsToDo:
        break


    compCan[histTypeItr].cd()

    histAr[0][histTypeItr].GetYaxis().SetRangeUser(0,histMax[histTypeItr]*1.1)
    histAr[0][histTypeItr].SetTitle(histTypeTitleAr[histTypeItr])
    histAr[0][histTypeItr].Draw("hist E1")

    for j in range(1,len(histAr)):
      if useLHEAr[j]:
        histAr[j][histTypeItr].DrawCopy("same hist E1")
  
    legAr[histTypeItr].Draw()
    

    compCan[histTypeItr].SaveAs("ComparisonFor{0}{1}_{2}.png".format(histTypeSaveName,dataName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))

    """
    if normalizeDataTogether:
      if savePathBool:
        compCan[histTypeItr].SaveAs("./Graphs/Comparison/ComparisonFor{0}_{1}_NBT_{2}.png".format(histTypeSaveName,dataName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
      else:
        compCan[histTypeItr].SaveAs("ComparisonFor{0}_{1}_NBT_{2}.png".format(histTypeSaveName,dataName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
    else:
      if savePathBool:
        compCan[histTypeItr].SaveAs("./Graphs/Comparison/ComparisonFor{0}_{1}_{2}.png".format(histTypeSaveName,dataName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
      else:
        compCan[histTypeItr].SaveAs("ComparisonFor{0}_{1}_{2}.png".format(histTypeSaveName,dataName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
    """

    


def setHistoElements(colorAr,histAr,normalizeDataTogether,weightsAr,intAr,histTitleNameAr,onlyDoSomeHists,histsToDo,useFillColorInPlots):
    dataIntSumAr = []
    for histTypeItr, histTitleName in enumerate(histTitleNameAr):
      if onlyDoSomeHists and histTypeItr >= histsToDo:
        break
      dataIntSumAr.append(0)
    for k,colorA in zip(range(len(colorAr)),colorAr):
      intAr.append([])
      for histTypeItr, histTitleName in enumerate(histTitleNameAr):
        if onlyDoSomeHists and histTypeItr >= histsToDo:
          break
        histAr[k][histTypeItr].SetLineColor(colorA)
        histAr[k][histTypeItr].SetLineWidth(4)
        if useFillColorInPlots:
            histAr[k][histTypeItr].SetFillColorAlpha(colorA,0.2)
        makeNiceHistos(histAr[k][histTypeItr],"","Weighted Events/Bin (pb)",True)
        histAr[k][histTypeItr].SetTitle(histTitleName)
        tmpHistInt = histAr[k][histTypeItr].Integral()
        if normalizeDataTogether:
                dataIntSumAr[histTypeItr] += tmpHistInt*weightsAr[k]
        intAr[-1].append(tmpHistInt)
    return dataIntSumAr




def normalizeHists(histAr,normalizeDataTogether,dataIntSum,weightsAr,legAr,nameAr,intAr,histTypeSaveNameAr,onlyDoSomeHists,histsToDo):
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
        histAr[k][histTypeItr].Sumw2()
        #print(k,histTypeItr)
        #print(dataIntSum)
        #print(isSignalAr)
        if normalizeDataTogether and dataIntSum[histTypeItr]:
            
            #histAr[k][histTypeItr].Scale(weightsAr[k] / dataIntSum[histTypeItr])
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
            histAr[k][histTypeItr].Scale(1.0 / intAr[k][histTypeItr])
            print("-----------------")

            tmpMax = histAr[k][histTypeItr].GetMaximum()
            if not normalizeDataTogether:
              if tmpMax > histMaxAr[histTypeItr]:
                histMaxAr[histTypeItr] = tmpMax
              if tmpMax > 0 and tmpMax < histMinAr[histTypeItr]:
                histMinAr[histTypeItr] = tmpMax
            legAr[histTypeItr].AddEntry(histAr[k][histTypeItr],nameAr[k],"l")
    return histMaxAr,histMinAr


def setUpInvHists(histAr,cloneHistAr,invHistsAr,nameAr,intAr,drawInvAr,histTypeSaveNameAr,onlyDoSomeHists,histsToDo):
    for k in range(len(histAr)):
      if k != 0:
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
                    invHistsAr[-1][histTypeItr].Add(histAr[j][histTypeItr])
                for i in range(tmpNBins):
                    invHistsAr[-1][histTypeItr].SetBinError(i,tmpBinErrorAr[i])
            else:
                drawInvAr[-1].append(False)


def setUpNonStackedHistAndFoMPlot(compCan,cloneHistAr,padAr,histMax,histMin,normalizeDataTogether,histAr,legAr,dataName,histTypeSaveNameAr,histTypeTitleAr,histTypeXTitleAr,onlyDoSomeHists,histsToDo,datasetSaveNameAr):
  for histTypeItr, histTypeSaveName in enumerate(histTypeSaveNameAr):
    if onlyDoSomeHists and histTypeItr >= histsToDo:
        break


    compCan[histTypeItr].cd()
    if useLogY:
      padAr[histTypeItr][0].SetLogy()
    padAr[histTypeItr][0].Draw()
    padAr[histTypeItr][0].cd()

    tmpMax = histAr[0][histTypeItr].GetMaximum()
    if tmpMax > histMax[histTypeItr]:
        histMax[histTypeItr] = tmpMax
    if tmpMax > 0 and tmpMax < histMin[histTypeItr]:
        histMin[histTypeItr] = tmpMax
    if not useLogY:
        histAr[0][histTypeItr].GetYaxis().SetRangeUser(0,histMax[histTypeItr]*1.1)
    else:
        histAr[0][histTypeItr].GetYaxis().SetRangeUser(histMin[histTypeItr]*0.01,histMax[histTypeItr]*1.1)
    histAr[0][histTypeItr].SetTitle(histTypeTitleAr[histTypeItr])
    histAr[0][histTypeItr].Draw("hist E1")

    for j in range(1,len(histAr)):
        histAr[j][histTypeItr].DrawCopy("same hist E1")
    
  
    legAr[histTypeItr].Draw()
    compCan[histTypeItr].cd()

    setUpBottomPadsAr(padAr[histTypeItr],useLogYForRatioPlot) 

    histAr[0][histTypeItr].Sumw2()
    for k in range(len(cloneHistAr)):
        cloneHistAr[k][histTypeItr].Sumw2()
        cloneHistAr[k][histTypeItr].Divide(histAr[0][histTypeItr])
        makeNiceHistos(cloneHistAr[k][histTypeItr],histTypeXTitleAr[histTypeItr],"Ratio to {0}".format(datasetSaveNameAr[0]),False)
        cloneHistAr[k][histTypeItr].SetLineWidth(2)
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
    if normalizeDataTogether:
      if savePathBool:
        compCan[histTypeItr].SaveAs("./Graphs/Comparison/ComparisonFor{0}_{1}_NBT_{2}.png".format(histTypeSaveName,dataName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
      else:
        compCan[histTypeItr].SaveAs("ComparisonFor{0}_{1}_NBT_{2}.png".format(histTypeSaveName,dataName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
    else:
      if savePathBool:
        compCan[histTypeItr].SaveAs("./Graphs/Comparison/ComparisonFor{0}_{1}_{2}.png".format(histTypeSaveName,dataName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
      else:
        compCan[histTypeItr].SaveAs("ComparisonFor{0}_{1}_{2}.png".format(histTypeSaveName,dataName,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))

    
