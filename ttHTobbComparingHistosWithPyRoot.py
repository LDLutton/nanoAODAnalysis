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
#Compare to withoutDipole files
#fileWithoutDipole = TFile.Open("histosFromNanoAODWWithoutDipoleRecoil.root")
#Compare to background files
fileOne = TFile.Open("histosFromNanoAODttHBackground.root")
#With Dipole files
fileTwo = TFile.Open("histosFromNanoAODWithDipoleRecoil.root")
listOfKeysOne = fileOne.GetListOfKeys()
listOfKeysTwo = fileTwo.GetListOfKeys()

canAr = []
padAr = []
legAr = []
histAr = []

skipCounter = 0
#for keyWoD,keyWD in zip(listOfKeysOne,listOfKeysTwo):
for i,keyTwo in enumerate(listOfKeysTwo):
    tmpObjTwo = keyTwo.ReadObj()
    histName = tmpObjTwo.GetName()
    if "InitialJet_" in tmpObjTwo.GetName():
      skipCounter += 1
      continue
    tmpObjOne = listOfKeysOne[i-skipCounter].ReadObj()
    histNameOne = tmpObjOne.GetName()
    if histName != histNameOne:
        print("weeooweooo error alert:",histName,histNameOne)
    
    #if "pt" in histName:
    #    makePTHistos(histAr,tmpObjWoD,tmpObjWD)
    canAr.append(TCanvas("{0}Can".format(histName),"{0}Can".format(histName),1920,1440))
    
    setUpLegend(legAr)
    setUpPadsAr(padAr,"{0}Pad".format(histName))
    
    tmpObjOne.SetLineColor(4)
    tmpObjOne.SetLineWidth(3)
    tmpObjTwo.SetLineColor(6)
    tmpObjTwo.SetLineWidth(3)
    canAr[-1].cd()
    padAr[-1][0].Draw()
    padAr[-1][0].cd()
    makeNiceHistos(tmpObjOne,"","Events",True)
    tmpObjOne.SetTitle("{0}".format(histName)+" SM+EFT and ttH background")
    legAr[-1].AddEntry(tmpObjOne,"ttH","l")
    histMax = 0
    
    tmpMaxOne = tmpObjOne.GetMaximum()
    tmpMaxTwo = tmpObjTwo.GetMaximum()
    if tmpMaxTwo < tmpMaxOne:
        histMax = tmpMaxOne
    else:
        histMax = tmpMaxTwo
    tmpObjOne.GetYaxis().SetRangeUser(0,histMax)
    tmpObjOne.Draw("hist")
    
    tmpObjTwo.SetTitle("{0}".format(histName)+" SM+EFT and ttH background")
    legAr[-1].AddEntry(tmpObjTwo,"SM+EFT","l")
    tmpObjTwo.DrawCopy("same hist")
    legAr[-1].Draw()
    """
    if "pt" in histName:
         #padAr[-1][0].SetLogx()
         #tmpObjWoD.GetXaxis().SetLimits(5.0,tmpObjWoD.GetXaxis().GetXmax())
         #tmpObjWD.GetXaxis().SetLimits(5.0,tmpObjWD.GetXaxis().GetXmax())
         #tmpObjWoD.GetXaxis().SetRangeUser(5.0,tmpObjWoD.GetXaxis().GetXmax())
         #tmpObjWD.GetXaxis().SetRangeUser(5.0,tmpObjWD.GetXaxis().GetXmax())
         print(tmpObjWoD,tmpObjWoD.GetXaxis().GetXmax())
         print(tmpObjWD,tmpObjWD.GetXaxis().GetXmax())
         gPad.Modified()
    #    padAr[-1][0].SetLogy()
    #    tmpObjWoD.SetMinimum(0.01)
    #    tmpObjWD.SetMinimum(0.01)
    """
    canAr[-1].cd()
    setUpBottomPadsAr(padAr[-1])
    tmpObjTwo.Sumw2()
    tmpObjTwo.Divide(tmpObjOne)
    makeNiceHistos(tmpObjTwo,"","Ratio to ttH",False)
    tmpRatioMax = tmpObjTwo.GetMaximum()
    if tmpRatioMax > 4:
        tmpObjTwo.GetYaxis().SetRangeUser(0,4)
    tmpObjTwo.SetLineWidth(2)
    tmpObjTwo.Draw("et same")
    """
    if "pt" in histName:
         #tmpObjWoD.GetXaxis().SetRangeUser(5.0,tmpObjWoD.GetXaxis().GetXmax())
         #tmpObjWD.GetXaxis().SetRangeUser(5.0,tmpObjWD.GetXaxis().GetXmax())
         #padAr[-1][1].SetLogx()
         #tmpObjWoD.GetXaxis().SetRangeUser(5.0,tmpObjWoD.GetXaxis().GetXmax())
         #tmpObjWD.GetXaxis().SetRangeUser(5.0,tmpObjWD.GetXaxis().GetXmax())
    """
    canAr[-1].Update()
    #Saving canvas

    canAr[-1].SaveAs("{0}ComparingSMEFTWithTTHtoBB.png".format(histName))


print("Done.","time:",time.time()-startt)


