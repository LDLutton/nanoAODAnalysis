from ROOT import TFile, TChain, gDirectory, TApplication, TMath, Math, TMinuit, TROOT, TSystem, TTree, TVector2
# You probably also want to import TH1D and TCanvas,
# unless you're not making any histograms.
from ROOT import TH1F, TCanvas, TPad, TF1, TGraph, TGraphErrors, TLegend, TLine, TPaveText, TStyle
from ROOT import TH2D, TH2F,gPad
from math import sqrt,pi
import time as time

#For drawing and saving histograms
#Saves a png and a pdf version
#Saves histogram to the currently active root file
def DrawPlot(plot,name):
    c1 = TCanvas("c1","c1",3600,2400)


    plot.Scale(1.0 / plot.Integral())
    plot.SetFillColorAlpha(30,0.35)

    plot.Draw("hist")
    c1.SaveAs((name+"WithDipoleRecoil.png"))
    c1.SaveAs((name+"WithDipoleRecoil.pdf"))
    plot.Write()

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

"""
def makePTHistos(histAr,histName,tmpHistWoD,tmpHistWD):
    histAr.append(TH1F("{0}WoD".format(histName),"{0}WoD".format(histName), 25, 0, 500))
    histAr.append(TH1F("{0}WD".format(histName),"{0}WD".format(histName), 25, 0, 500))
"""

# Open the file. Note that the name of your file outside this class
# will probably NOT be experiment.root.
print("start")
startt = time.time()
includeBackgroundBool = False
#Analyzer will run over all files put into fileAr
fileAr = []
#Give the names of the files as well as how you want it to appear in the legend
nameAr = []
#Give the color of the lines
colorAr = []
#Give the weights for each file
weightsAr = []
useModifiedCouplingAr = []
skipCtr = []
#First put in file to compare to other files
#This file will be used as the baseline in the ratio plots
#Compare to withoutDipole files
#fileWithoutDipole = TFile.Open("histosFromNanoAODWWithoutDipoleRecoil.root")
#With Dipole files
#fileTwo = TFile.Open("histosFromNanoAODWithDipoleRecoil.root")
couplingModifierAr = [10,0.1,0.01,0.001]
couplingModifierStrAr = ["EFTCouplingTimes10","EFTCouplingTimes0p1","EFTCouplingTimes0p01","EFTCouplingTimes0p001","EFTCouplingTimes0p0001"]
fileAr.append(TFile.Open("histosFromNanoAODpphzzjjQCD0SMHLOOP0NPE1NPcHWE1QEDE5ResMasAllVer100Ev_0p999cHW100GeVIMJetCut.root"))
nameAr.append("EFT")
colorAr.append(6)
weightsAr.append(0.00026785303750000004)
#useModifiedCouplingAr.append(True)
useModifiedCouplingAr.append(False)
skipCtr.append(0)

fileAr.append(TFile.Open("histosFromNanoAODpphzzjjQCD0SMHLOOP0QEDE5NPE0ResMasAllVer100Ev_0p999cHW100GeVIMJetCut.root"))
nameAr.append("SM")
colorAr.append(2)
weightsAr.append(8.37391538525e-05)
useModifiedCouplingAr.append(False)
skipCtr.append(0)

if includeBackgroundBool:
    #Compare to background files
    #fileOne = TFile.Open("histosFromNanoAODttHBackground.root")
    fileAr.append(TFile.Open("histosFromNanoAODttHToBBBackground.root"))
    nameAr.append("ttHToBBBackground")
    colorAr.append(4)
    weightsAr.append(0.6*0.584)
    useModifiedCouplingAr.append(False)
    skipCtr.append(0)

#Put in the key lists in the same order as in the fileAr
keysAr = []
for fileA in fileAr:
    keysAr.append(fileA.GetListOfKeys())
#listOfKeysOne = fileOne.GetListOfKeys()
#listOfKeysTwo = fileTwo.GetListOfKeys()
#StringForSavingCanvas
saveString = "Comparing{0}".format(nameAr[0])
for nameA in nameAr[1:]:
    saveString = saveString + "With{0}".format(nameA)

canAr = []
padAr = []
legAr = []
histAr = []

#Sanity check
lenKeys = len(keysAr[0])
print("lenKeys:",lenKeys)
for i,keyA in enumerate(keysAr):
    if len(keyA) != lenKeys:
        print("oh no the length is wrong",i,len(keyA),keyA)

moddedCouplingHistAr = []
moddedCouplingCanAr = []
moddedCouplingPadAr = []
moddedCouplingLegAr = []

#Main loop over each histogram
for i in range(lenKeys):
    #print(i,moddedCouplingHistAr)
    moddedCouplingHistAr.append([])
    moddedCouplingCanAr.append([])
    moddedCouplingLegAr.append([])
    moddedCouplingPadAr.append([])
    tmpObjAr = []
    altNormalizationAr = []
    altNormalizationIntAr = []
    histName = keysAr[0][i].GetName()
    if "Normalized" not in histName:
        continue
    elif "LHEWeight" in histName and includeBackgroundBool:
        skipCtr[2] += 2
        continue
    
    canAr.append(TCanvas("{0}Can".format(histName),"{0}Can".format(histName),1920,1440))
    setUpLegend(legAr)
    setUpPadsAr(padAr,"{0}Pad".format(histName))
    canAr[-1].cd()
    padAr[-1][0].Draw()
    padAr[-1][0].cd()
    #Loop over all files
    
    combinedHistInt = 0
    combinedModdedHistIntAr = [0 for couplingModifier in couplingModifierAr]
    #Loop over different signal/background types
    for j,keyA,colorA,nameA,weightsA,skipC,useModifiedCoupling in zip(range(len(keysAr)),keysAr,colorAr,nameAr,weightsAr,skipCtr,useModifiedCouplingAr):
        tmpObjAr.append(keyA[i-skipC].ReadObj())
        tmpObjAr[-1].Scale(weightsA)
        #Sanity check
        tmpName = keyA[i-skipC].GetName()
        #tmpName = tmpObjAr[-1].GetName()
        if tmpName != histName:
            print("weeooweooo error alert:",histName,tmpName)
        tmpObjAr[-1].SetLineColor(colorA)
        tmpObjAr[-1].SetLineWidth(3)
        if j == 0:
            makeNiceHistos(tmpObjAr[-1],"","Events",True)
        tmpObjAr[-1].SetTitle(histName)
        legAr[-1].AddEntry(tmpObjAr[-1],nameA,"l")
        combinedHistInt += tmpObjAr[-1].Integral()
        altNormalizationAr.append(tmpObjAr[-1].Clone())
        altNormalizationIntAr.append(altNormalizationAr[-1].Integral())
        #Loop over different couplings
        if True in useModifiedCouplingAr:
            moddedCouplingHistAr[-1].append([])
            for k,modifiedCoupling,modifiedCouplingStr in zip(range(len(couplingModifierAr)),couplingModifierAr,couplingModifierStrAr):
                """
                print(i,j,k)
                print("moddedCouplingHistAr:",moddedCouplingHistAr)
                print("moddedCouplingHistAr[-1]:",moddedCouplingHistAr[-1])
                print("tmpObjAr:",tmpObjAr)
                print("tmpObjAr[-1]:",tmpObjAr[-1])
                """
                moddedCouplingHistAr[-1][-1].append(tmpObjAr[-1].Clone())
                if j == 0:
                    makeNiceHistos(moddedCouplingHistAr[-1][-1][-1],"","Events",True)
                    moddedCouplingLegAr[-1].append([])
                moddedCouplingHistAr[-1][-1][-1].SetTitle(histName+"EFTcHWE{0}".format(modifiedCouplingStr))
                #Will need to change this if I ever do more than one with modified coupling
                if useModifiedCoupling:
                    moddedCouplingCanAr[-1].append(TCanvas("{0}EFTcHWE{1}Can".format(histName,modifiedCouplingStr),"{0}EFTcHWE{1}Can".format(histName,modifiedCouplingStr),1920,1440))
                    setUpLegend(moddedCouplingLegAr[-1][k])
                    setUpPadsAr(moddedCouplingPadAr[-1],"{0}EFTcHWE{1}Pad".format(histName,modifiedCouplingStr))
                    moddedCouplingHistAr[-1][-1][-1].Scale(modifiedCoupling)
                    moddedCouplingLegAr[-1][k][-1].AddEntry(moddedCouplingHistAr[-1][-1][-1],nameA,"l")
                    combinedModdedHistIntAr[k] += moddedCouplingHistAr[-1][-1][-1].Integral()
    canAr[-1].cd()
    padAr[-1][0].cd()

    histMax = 0
    if combinedHistInt == 0:
        continue


    for j in range(len(tmpObjAr)):
        tmpObjAr[j].Scale(1.0 / combinedHistInt)
        tmpMax = tmpObjAr[j].GetMaximum()
        if tmpMax > histMax:
            histMax = tmpMax
    tmpObjAr[0].GetYaxis().SetRangeUser(0,histMax)
    
    tmpObjAr[0].Draw("hist")
    for j in range(1,len(tmpObjAr)):
        tmpObjAr[j].DrawCopy("same hist")
    legAr[-1].Draw()

    canAr[-1].cd()
    setUpBottomPadsAr(padAr[-1])
    ratioMax = 0
    for j in range(1,len(tmpObjAr)):
        tmpObjAr[j].Sumw2()
        tmpObjAr[j].Divide(tmpObjAr[0])
        makeNiceHistos(tmpObjAr[j],"","Ratio to EFT",False)
        tmpRatioMax = tmpObjAr[j].GetMaximum()
        if tmpRatioMax > ratioMax:
            ratioMax = tmpRatioMax
    if ratioMax > 4:
        tmpObjAr[1].GetYaxis().SetRangeUser(0,4)
    tmpObjAr[1].SetLineWidth(2)
    tmpObjAr[1].Draw("et same")
    for j in range(2,len(tmpObjAr)):
        makeNiceHistos(tmpObjAr[j],"","Ratio to EFT",False)
        tmpObjAr[j].SetLineWidth(2)
        tmpObjAr[j].Draw("et same")
    canAr[-1].Update()
    #Saving canvas

    canAr[-1].SaveAs("{0}{1}.png".format(histName,saveString))

    #Normalizing each distribution to itself
    canAr.append(TCanvas("{0}Can".format(histName),"{0}Can".format(histName),1920,1440))
    setUpLegend(legAr)
    setUpPadsAr(padAr,"{0}Pad".format(histName))
    canAr[-1].cd()
    padAr[-1][0].Draw()
    padAr[-1][0].cd()
    for j,nameA in zip(range(len(altNormalizationAr)),nameAr):
        altNormalizationAr[j].Scale(1.0 / altNormalizationIntAr[j])
        tmpMax = altNormalizationAr[j].GetMaximum()
        if tmpMax > histMax:
            histMax = tmpMax
        legAr[-1].AddEntry(altNormalizationAr[j],nameA,"l")
    altNormalizationAr[0].GetYaxis().SetRangeUser(0,histMax)
    
    altNormalizationAr[0].Draw("hist")
    for j in range(1,len(altNormalizationAr)):
        altNormalizationAr[j].DrawCopy("same hist")
    legAr[-1].Draw()

    canAr[-1].cd()
    setUpBottomPadsAr(padAr[-1])
    ratioMax = 0
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

    #Loop over the different couplings
    if True in useModifiedCouplingAr:
        for k,couplingModifier,couplingModifierStr,combinedModdedHistInt in zip(range(len(couplingModifierAr)),couplingModifierAr,couplingModifierStrAr,combinedModdedHistIntAr):
            #moddedCouplingHistAr[-1][0][k]
            moddedCouplingCanAr[-1][k].cd()
            moddedCouplingPadAr[-1][k][0].Draw()
            moddedCouplingPadAr[-1][k][0].cd()
            histMax = 0
            #loop over the different signal/background types
            #Each are scaled to the total integral sum of all, and we check the maximum for each to find the biggest
            for j in range(len(moddedCouplingHistAr[-1])):
                moddedCouplingHistAr[-1][j][k].Scale(1.0 / combinedModdedHistInt)
                tmpMax = moddedCouplingHistAr[-1][j][k].GetMaximum()
                if tmpMax > histMax:
                    histMax = tmpMax
            moddedCouplingHistAr[-1][0][k].GetYaxis().SetRangeUser(0,histMax)
            
            moddedCouplingHistAr[-1][0][k].Draw("hist") #MAIN OBJ
            for j in range(1,len(moddedCouplingHistAr[-1])):
                moddedCouplingHistAr[-1][j][k].DrawCopy("same hist")
            #Will need to change this if I ever do more than one with modified coupling
            moddedCouplingLegAr[-1][k][0].Draw()

            moddedCouplingCanAr[-1][k].cd()
            setUpBottomPadsAr(moddedCouplingPadAr[-1][k])
            ratioMax = 0
            for j in range(1,len(moddedCouplingHistAr[-1])):
                moddedCouplingHistAr[-1][j][k].Sumw2()
                moddedCouplingHistAr[-1][j][k].Divide(moddedCouplingHistAr[-1][0][k])
                makeNiceHistos(moddedCouplingHistAr[-1][j][k],"","Ratio to EFT",False)
                tmpRatioMax = moddedCouplingHistAr[-1][j][k].GetMaximum()
                if tmpRatioMax > ratioMax:
                    ratioMax = tmpRatioMax
            print(i,k,ratioMax)
            if ratioMax > 4:
                moddedCouplingHistAr[-1][1][k].GetYaxis().SetRangeUser(0,4)
            moddedCouplingHistAr[-1][1][k].SetLineWidth(2)
            moddedCouplingHistAr[-1][1][k].Draw("et same")
            #Loop over the remaining signal/background types
            for j in range(2,len(moddedCouplingHistAr[-1])):
                makeNiceHistos(moddedCouplingHistAr[-1][j][k],"","Ratio to EFT",False)
                moddedCouplingHistAr[-1][j][k].SetLineWidth(2)
                moddedCouplingHistAr[-1][j][k].Draw("et same")
            moddedCouplingCanAr[-1][k].Update()
            #Saving canvas

            moddedCouplingCanAr[-1][k].SaveAs("{0}_{1}_{2}.png".format(histName,saveString,couplingModifierStr))
            
print("Done.","time:",time.time()-startt)


