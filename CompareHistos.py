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

#Analyzer will run over all files put into fileAr
fileAr = []
#Give the names of the files as well as how you want it to appear in the legend
nameAr = []
#Give the color of the lines
colorAr = []
#Give the weights for each file
weightsAr = []

#First put in file to compare to other files
#This file will be used as the baseline in the ratio plots
#Compare to withoutDipole files
#fileWithoutDipole = TFile.Open("histosFromNanoAODWWithoutDipoleRecoil.root")
#With Dipole files
#fileTwo = TFile.Open("histosFromNanoAODWithDipoleRecoil.root")
fileAr.append(TFile.Open("histosFromNanoAODWithDipoleRecoil.root"))
nameAr.append("SMAndEFT")
colorAr.append(6)
weightsAr.append(1.0)

#Compare to background files
#fileOne = TFile.Open("histosFromNanoAODttHBackground.root")
fileAr.append(TFile.Open("histosFromNanoAODttHBackground.root"))
nameAr.append("ttHToBBBackground")
colorAr.append(4)
weightsAr.append(1.0)

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
skipCounter = 0

#Main loop over each histogram
for i in range(lenKeys):
    tmpObjAr = []
    tmpObj = keysAr[0][i].ReadObj()
    histName = tmpObj.GetName()
    canAr.append(TCanvas("{0}Can".format(histName),"{0}Can".format(histName),1920,1440))
    setUpLegend(legAr)
    setUpPadsAr(padAr,"{0}Pad".format(histName))
    canAr[-1].cd()
    padAr[-1][0].Draw()
    padAr[-1][0].cd()
    #Loop over all files
    histMax = 0
    for j,keyA,colorA,nameA,weightsA in zip(range(lenKeys),keysAr,colorAr,nameAr,weightsAr):
        tmpObjAr.append(keyA[i].ReadObj())
        tmpObjAr[-1].Scale(weightsA)
        #Sanity check
        tmpName = tmpObjAr[-1].GetName()
        if tmpName != histName:
            print("weeooweooo error alert:",histName,tmpName)
        tmpObjAr[-1].SetLineColor(colorA)
        tmpObjAr[-1].SetLineWidth(3)
        if j == 0:
            makeNiceHistos(tmpObjAr[-1],"","Events",True)
        tmpObjAr[-1].SetTitle(histName)
        legAr[-1].AddEntry(tmpObjAr[-1],nameA,"l")
        tmpMax = tmpObjAr[-1].GetMaximum()
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
        makeNiceHistos(tmpObjAr[j],"","Ratio to ttH",False)
        tmpRatioMax = tmpObjAr[j].GetMaximum()
        if tmpRatioMax > ratioMax:
            ratioMax = tmpRatioMax
    if ratioMax > 4:
        tmpObjAr[1].GetYaxis().SetRangeUser(0,4)
    tmpObjAr[1].SetLineWidth(2)
    tmpObjAr[1].Draw("et same")
    for j in range(2,len(tmpObjAr)):
        makeNiceHistos(tmpObjAr[j],"","Ratio to ttH",False)
        tmpObjAr[j].SetLineWidth(2)
        tmpObjAr[j].Draw("et same")
    canAr[-1].Update()
    #Saving canvas

    canAr[-1].SaveAs("{0}{1}.png".format(histName,saveString))

print("Done.","time:",time.time()-startt)


