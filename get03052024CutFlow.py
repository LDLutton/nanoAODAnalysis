import datetime
from ROOT import TFile, TChain, gDirectory, TApplication, TMath, Math, TMinuit, TROOT, TSystem, TTree, TVector2, THStack
# You probably also want to import TH1D and TCanvas,
# unless you're not making any histograms.
from ROOT import TH1F, TH1D, TF1, TGraph, TGraphErrors, TLegend, TLine, TPaveText, TStyle,TMultiGraph
from ROOT import TH2D, TH2F,TCanvas,gStyle
from FunctionsFor082022AnalysisPlots import *
from math import sqrt
from array import array

from scipy import stats
#Copied from Draw082022AnalysisPlots.py


today = datetime.datetime.today()
#cutTypeStrAr = ["Initial Cuts","VBF Jet Invariant Mass Cut","Lepton Invariant Mass and BTag Cuts","All Cuts"]
M_PI = 3.14159265358979323846264338327950288


def poisson_interval(k, alpha=0.05): 
    """
    uses chisquared info to get the poisson interval. Uses scipy.stats 
    (imports in function). 
    """
    
    a = alpha
    low, high = (stats.chi2.ppf(a/2, 2*k) / 2, stats.chi2.ppf(1-a/2, 2*k + 2) / 2)
    if k == 0: 
        low = 0.0
    return low, high

def calcDeltaR( phi1, eta1, phi2, eta2):
    deta = eta1-eta2
    dphi = abs(phi1-phi2)
    if (dphi > M_PI):
        dphi -= (2*M_PI)
    return sqrt((deta*deta)+(dphi*dphi))


def fillKSArs(genListAr,allListAr,genHistAr,datasetNameAr,genCtrAr,allCtrAr):
    for i in range(3):
        print("Getting KS for C and D region after",cutTypeStrAr[i])
        for genListOne,genHistOne,genListTwo,genHistTwo,datasetName,genCtrOne,genCtrTwo in zip(genListAr[(i*3)+1],genHistAr[(i*3)+1],genListAr[(i*3)+2],genHistAr[(i*3)+2],datasetNameAr,genCtrAr[(i*3)+1],genCtrAr[(i*3)+2]):
            if genCtrOne and genCtrTwo:
                tmpNBins = genHistOne.GetNbinsX()
                for binInd in range(tmpNBins):
                    genListOne.append(genHistOne.GetBinContent(binInd))
                    genListTwo.append(genHistTwo.GetBinContent(binInd))
                    #print(i*2,binInd)
                    allListAr[(i*3)+1][binInd] += genListOne[-1]
                    allListAr[(i*3)+2][binInd] += genListTwo[-1]

                print("KS for",datasetName+":")
                tmpKS = stats.ks_2samp(genListOne,genListTwo)
                print(tmpKS,"Events in D Region:",genCtrOne,"Events in C Region:",genCtrTwo)
        print("KS for all combined:")
        tmpKS = stats.ks_2samp(allListAr[(i*3)+1],allListAr[(i*3)+2])
        print(tmpKS,"Events in D Region:",allCtrAr[(i*3)+1],"Events in C Region:",allCtrAr[(i*3)+2])
        print("--------------------------------")
        

def setUpInvHistsForBackground(histAr,cloneHistAr,totSumSetAr,invHistsAr,nameAr,intAr):
    for histInd in range(len(histAr)):
        if histInd == 0 or histInd in totSumSetAr:
            continue
        tmpHistInt = histAr[histInd].Integral()
        intAr.append(tmpHistInt)
        

        if not tmpHistInt:
            continue

        histAr[histInd].Sumw2()

        cloneHistAr.append(histAr[histInd].Clone("{0}Clone".format(nameAr[histInd])))
        invHistsAr.append(histAr[histInd].Clone("{0}Inv".format(nameAr[histInd])))
        #invHistsAr[-1].SetLineColor(1)
        #invHistsAr[-1].SetFillColor(1)
        tmpNBins = histAr[histInd].GetNbinsX()
        tmpBinErrorAr = []
        for binInd in range(tmpNBins):
            tmpBinErrorAr.append(histAr[histInd].GetBinError(binInd))
        for preHistInd in range(histInd):
            if preHistInd == 0 or preHistInd in totSumSetAr:
                continue
            invHistsAr[-1].Add(histAr[preHistInd])
            cloneHistAr[-1].Add(histAr[preHistInd])
        for binInd in range(tmpNBins):
            invHistsAr[-1].SetBinError(binInd,tmpBinErrorAr[binInd])
def setUpInvHistsForSummedBackground(histAr,sumHistAr,cloneHistAr,totSumSetAr,invHistsAr,sumNameAr,intAr):
    for histInd in range(len(sumHistAr)):
        tmpHistInt = sumHistAr[histInd].Integral()
        intAr.append(tmpHistInt)

        if not tmpHistInt:
            continue

        sumHistAr[histInd].Sumw2()

        cloneHistAr.append(sumHistAr[histInd].Clone("{0}Clone".format(sumNameAr[histInd])))
        invHistsAr.append(sumHistAr[histInd].Clone("{0}Inv".format(sumNameAr[histInd])))
        #invHistsAr[-1].SetLineColor(1)
        #invHistsAr[-1].SetFillColor(1)
        tmpNBins = sumHistAr[histInd].GetNbinsX()
        tmpBinErrorAr = []
        for binInd in range(tmpNBins):
            tmpBinErrorAr.append(sumHistAr[histInd].GetBinError(binInd))
        for preHistInd in range(len(histAr)):
            if preHistInd == 0 or preHistInd in totSumSetAr:
                continue
            invHistsAr[-1].Add(histAr[preHistInd])
            cloneHistAr[-1].Add(histAr[preHistInd])
        for preHistInd in range(histInd):
            invHistsAr[-1].Add(sumHistAr[preHistInd])
            cloneHistAr[-1].Add(sumHistAr[preHistInd])
        for binInd in range(tmpNBins):
            invHistsAr[-1].SetBinError(binInd,tmpBinErrorAr[binInd])


def setUpGraphs(gGraph,markerStyle,lineColor,gTitle,xTitle,yTitle,noX=False):
    #gGraph.SetMarkerStyle(markerStyle)
    gGraph.SetTitle(gTitle)
    if noX:
        gGraph.GetXaxis().SetLabelSize(0)
    else:
        gGraph.GetXaxis().SetTitle(xTitle)
        gGraph.GetXaxis().CenterTitle()
        gGraph.GetYaxis().SetTitle(yTitle)
        
        gGraph.GetXaxis().SetLabelFont(42)
        gGraph.GetXaxis().SetLabelSize(0.035)
        gGraph.GetXaxis().SetTitleFont(42)
    gGraph.GetYaxis().SetLabelFont(42)
    gGraph.GetYaxis().SetLabelSize(0.035)
    gGraph.GetYaxis().SetTitleFont(42)
    gGraph.GetYaxis().SetTitleOffset(1.2)
    gGraph.GetXaxis().SetTitleOffset(0.9)
    #gGraph.GetYaxis().CenterTitle()
    #gGraph.SetLineColor(lineColor)


def makeRatioGraph(nameAr,canAr,MGAr,graphAr,graphUCAr,zeroAr,graphsAr,xAr,legAr,addStr,bkgName,padAr,ratioAr,ratioUCAr):
    canAr.append(TCanvas("c1ABCD","c1ABCD",3600,2400))
    setUpPadsAr(padAr,"ABCDPad")
    MGAr.append(TMultiGraph())
    setUpLegend(legAr)
    yellowSkip = 0
    for k,nameA in enumerate(nameAr):
        graphsAr.append(TGraphErrors(len(graphAr[k]),xAr,graphAr[k],zeroAr,graphUCAr[k]))
        setUpGraphs(graphsAr[-1],3,22,"{0}".format(nameA),"BDT Cut Point","",True)
        if k == 4:
            yellowSkip += 1
        #graphsAr[-1].GetHistogram().SetMinimum(0)
        #graphsAr[-1].GetHistogram().SetMaximum(1)
        graphsAr[-1].SetLineColor(k+1+yellowSkip)
        graphsAr[-1].SetMarkerStyle(3)
        MGAr[-1].Add(graphsAr[-1],"lp")
        legAr[-1].AddEntry(graphsAr[-1],nameA,"l")
    #canAr[-1].SetLogy()
    setUpGraphs(MGAr[-1],3,22,"ABCD Results for Different BDT Cuts Using {0}".format(bkgName),"BDT Cut Point","",True)
    #MGAr[-1].GetHistogram().SetMinimum(0)
    #MGAr[-1].GetHistogram().SetMaximum(1)
    MGAr[-1].GetXaxis().SetLimits(0.,1.)
    padAr[0][0].Draw()
    padAr[0][0].cd()
    
    MGAr[-1].Draw("A*")
    legAr[-1].Draw()
    #canAr[-1].BuildLegend()
    canAr[-1].Draw()
    canAr[-1].cd()
    setUpBottomPadsAr(padAr[-1],False)

    graphsAr.append(TGraphErrors(len(ratioAr),xAr,ratioAr,zeroAr,ratioUCAr))

    setUpGraphs(graphsAr[-1],3,22,"","BDT Cut Point","Ratio of Predicted A to A",False)
    graphsAr[-1].GetXaxis().SetLimits(0.,1.)
    graphsAr[-1].Draw("A*")
    canAr[-1].Update()
    canAr[-1].Draw()
    canAr[-1].SaveAs("ABCDResultsByBDTCut_{0}_AllYears_{1}.png".format(addStr,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))

def setUpPadsAltAr(padAr,padName):
  padAr.append([])
  padAr[-1].append(TPad(padName, padName,0.,0.40,1,1))
  padAr[-1].append(TPad(padName+" ratio", padName+" ratio",0.,0.,1,0.457))

def makeStackedPlotsWithDataAndRatio(histCan,histStack,histData,histLeg,histSaveStr,addStr,padAr,histSum,cloneHistAr,histTitle):
    setUpPadsAltAr(padAr,"{0}Pad".format(histSaveStr))
    padAr[-1][0].Draw()
    padAr[-1][0].cd()
    histStack.SetTitle("D Region after Lep Invariant Mass and BTag Cuts")
    
    histStack.Draw("hist")
    histStack.GetYaxis().SetTitle("Events")
    histStack.GetYaxis().CenterTitle()
    histStack.GetYaxis().SetTitleSize(0.068)
    histStack.GetYaxis().SetTitleOffset(0.6)
    histData.Draw("SAME P0 E")
    histData.SetLineColor(1)
    histData.SetMarkerStyle(8)
    histLeg.AddEntry(histData,"Data", "P")
    histLeg.Draw()
    histCan.Draw()
    histCan.cd()
    setUpBottomPadsAr(padAr[-1],False)
    padAr[-1][1].Draw()
    padAr[-1][1].cd()
    cloneHistAr.append(histData.Clone())
    cloneHistAr[-1].SetTitle("")
    
    cloneHistAr[-1].Divide(histSum)
    cloneHistAr[-1].Draw("et")
    cloneHistAr[-1].GetXaxis().SetTitle(histTitle)
    cloneHistAr[-1].GetYaxis().SetTitle("Data/MC")
    cloneHistAr[-1].GetYaxis().CenterTitle()
    cloneHistAr[-1].GetYaxis().SetTitleSize(0.068)
    cloneHistAr[-1].GetXaxis().SetTitleSize(0.068)
    cloneHistAr[-1].GetYaxis().SetTitleOffset(0.6)
    cloneHistAr[-1].GetYaxis().SetRangeUser(0,4)
    cloneHistAr[-1].Draw("et")
    histCan.Update()
    histCan.Draw()
    histCan.SaveAs("{0}{1}StackWithData_AllYears_{2}.png".format(histSaveStr,addStr,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
    
    #histCan.SetLogy()
    histCan.cd()
    padAr[-1][0].SetLogy()
    padAr[-1][0].Draw()
    padAr[-1][0].cd()
    histCan.cd()
    padAr[-1][1].Draw()
    padAr[-1][1].cd()
    histCan.Update()
    histCan.Draw()
    histCan.SaveAs("{0}{1}StackWithDataLogPlot_AllYears_{2}.png".format(histSaveStr,addStr,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))

def makeStackedPlots(histCan,histStack,histLeg,histSaveStr,addStr,histSum,histTitle):
    histStack.SetTitle(histTitle)
    histStack.Draw("hist")
    histStack.GetYaxis().SetTitle("Events")
    histStack.GetYaxis().CenterTitle()
    histStack.GetYaxis().SetTitleSize(0.068)
    histStack.GetYaxis().SetTitleOffset(0.6)
    histLeg.Draw()
    histCan.Draw()
    histCan.cd()
    histCan.Update()
    histCan.Draw()
    histCan.SaveAs("{0}{1}Stack_AllYears_{2}.png".format(histSaveStr,addStr,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
    histCan.cd()
    histCan.SetLogy()
    histCan.cd()
    histCan.Update()
    histCan.Draw()
    histCan.SaveAs("{0}{1}StackLogPlot_AllYears_{2}.png".format(histSaveStr,addStr,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))

def makeStackedPlotsWithSignal(histCan,histStack,histLeg,histSaveStr,addStr,histSum,histTitle,histSignal):
    histStack.SetTitle(histTitle)
    histStack.Draw("hist")
    histStack.GetYaxis().SetTitle("Events")
    histStack.GetYaxis().CenterTitle()
    histStack.GetYaxis().SetTitleSize(0.068)
    histStack.GetYaxis().SetTitleOffset(0.6)
    histSignal.Draw("SAME hist")
    histLeg.Draw()
    histCan.Draw()
    histCan.cd()
    histCan.Update()
    histCan.Draw()
    histCan.SaveAs("{0}{1}Stack_AllYears_{2}.png".format(histSaveStr,addStr,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
    histCan.cd()
    histSignal.SetMinimum(0.1)
    histStack.SetMinimum(0.1)
    histCan.SetLogy()
    
    histCan.cd()
    histSignal.Draw("SAME hist")
    histCan.Update()
    histCan.Draw()
    histCan.SaveAs("{0}{1}StackLogPlot_AllYears_{2}.png".format(histSaveStr,addStr,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))


def makeStackedPlotsWithSignalAndError(histCan,histStack,histLeg,histSaveStr,addStr,histSum,histTitle,histSignal,invHists,XAxisTitle):
    histStack.SetTitle(histTitle)
    histStack.Draw("hist")
    histStack.GetYaxis().SetTitle("Events")
    
    histStack.GetYaxis().CenterTitle()
    histStack.GetYaxis().SetTitleSize(0.068)
    histStack.GetYaxis().SetTitleOffset(0.6)
    histStack.GetXaxis().SetTitle(XAxisTitle)
    histStack.GetXaxis().CenterTitle()
    histStack.GetXaxis().SetTitleSize(0.068)
    histStack.GetXaxis().SetTitleOffset(0.6)
    histSignal.Draw("SAME hist E1")
    histLeg.Draw()
    histCan.Draw()
    histCan.cd()
    histCan.Update()
    histCan.Draw()
    for histItr in range(len(invHists)):
        invHists[histItr].SetStats(0)
        invHists[histItr].Draw("same E1")
    histSignal.Draw("SAME hist E1")
    histCan.SaveAs("{0}{1}Stack_WithError_AllYears_{2}.png".format(histSaveStr,addStr,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
    histCan.cd()
    histSignal.SetMinimum(0.1)
    histStack.SetMinimum(0.1)
    for histItr in range(len(invHists)):
        invHists[histItr].SetMinimum(0.1)
    histCan.SetLogy()
    
    histCan.cd()
    histSignal.Draw("SAME hist E1")
    histCan.Update()
    histCan.Draw()
    histCan.SaveAs("{0}{1}StackLogPlot_WithError_AllYears_{2}.png".format(histSaveStr,addStr,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))


def makeStackedPlotsWithSignalAndErrorAndDataAndRatio(histCan,histStack,histSignal,histData,histLeg,histSaveStr,addStr,padAr,histSum,invHists,cloneHistAr,histTitle,XAxisTitle):
    setUpPadsAltAr(padAr,"{0}Pad".format(histSaveStr))
    padAr[-1][0].Draw()
    padAr[-1][0].cd()
    histStack.SetTitle(histTitle)
    
    histStack.Draw("hist")
    histStack.GetYaxis().SetTitle("Events")
    histStack.GetYaxis().CenterTitle()
    histStack.GetYaxis().SetTitleSize(0.068)
    histStack.GetYaxis().SetTitleOffset(0.6)
    histSignal.Draw("SAME hist E1")
    
    for histItr in range(len(invHists)):
        invHists[histItr].SetStats(0)
        invHists[histItr].Draw("same E1")
    histData.Draw("SAME P0 E")
    histLeg.Draw()
    histCan.Draw()
    histCan.cd()
    histCan.Update()
    histCan.Draw()
    
    histData.SetLineColor(1)
    histData.SetMarkerStyle(8)
    histSignal.Draw("SAME hist E1")
    histData.Draw("SAME P0 E")
    histLeg.AddEntry(histData,"Data [{0:.3f}]".format(histData.Integral()), "p")
    histLeg.Draw()
    histCan.Draw()
    histCan.cd()
    setUpBottomPadsAr(padAr[-1],False)
    padAr[-1][1].Draw()
    padAr[-1][1].cd()
    cloneHistAr.append(histData.Clone())
    cloneHistAr[-1].SetTitle("")
    
    cloneHistAr[-1].Divide(histSum)
    cloneHistAr[-1].Draw("et")
    cloneHistAr[-1].GetXaxis().SetTitle(XAxisTitle)
    cloneHistAr[-1].GetYaxis().SetTitle("Data/MC")
    cloneHistAr[-1].GetYaxis().CenterTitle()
    cloneHistAr[-1].GetYaxis().SetTitleSize(0.068)
    cloneHistAr[-1].GetXaxis().SetTitleSize(0.068)
    cloneHistAr[-1].GetYaxis().SetTitleOffset(0.6)
    tmpMax = cloneHistAr[-1].GetMaximum()
    if tmpMax > 3:
        cloneHistAr[-1].GetYaxis().SetRangeUser(0,4)
    elif tmpMax > 2:
        cloneHistAr[-1].GetYaxis().SetRangeUser(0,3)
    else:
        cloneHistAr[-1].GetYaxis().SetRangeUser(0,2)
    #cloneHistAr[-1].GetYaxis().SetRangeUser(0,4)
    cloneHistAr[-1].Draw("et")
    histCan.Update()
    histCan.Draw()
    histCan.SaveAs("{0}{1}StackWithData_WithError_AllYears_{2}.png".format(histSaveStr,addStr,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
    
    histCan.cd()
    histSignal.SetMinimum(0.1)
    histStack.SetMinimum(0.1)
    histData.SetMinimum(0.1)
    for histItr in range(len(invHists)):
        invHists[histItr].SetMinimum(0.1)
    padAr[-1][0].SetLogy()
    padAr[-1][0].Draw()
    padAr[-1][0].cd()
    histCan.cd()
    padAr[-1][1].Draw()
    padAr[-1][1].cd()
    histCan.Update()
    histCan.Draw()
    histCan.SaveAs("{0}{1}StackWithDataLogPlot_WithError_AllYears_{2}.png".format(histSaveStr,addStr,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))




def makeBasicGraph(nameAr,canAr,MGAr,graphAr,graphUCAr,zeroAr,graphsAr,xAr,legAr,addStr,bkgName):
    canAr.append(TCanvas("c1ABCD","c1ABCD",3600,2400))
    MGAr.append(TMultiGraph())
    setUpLegend(legAr)
    yellowSkip = 0
    for k,nameA in enumerate(nameAr):
        graphsAr.append(TGraphErrors(len(graphAr[k]),xAr,graphAr[k],zeroAr,graphUCAr[k]))
        setUpGraphs(graphsAr[-1],3,22,"{0}".format(nameA),"BDT Cut Point","")
        if k == 4:
            yellowSkip += 1
        #graphsAr[-1].GetHistogram().SetMinimum(0)
        #graphsAr[-1].GetHistogram().SetMaximum(1)
        graphsAr[-1].SetLineColor(k+1+yellowSkip)
        graphsAr[-1].SetMarkerStyle(3)
        MGAr[-1].Add(graphsAr[-1],"lp")
        
    #canAr[-1].SetLogy()
    setUpGraphs(MGAr[-1],3,22,"ABCD Results for Different BDT Cuts Using {0}".format(bkgName),"BDT Cut Point","")
    #MGAr[-1].GetHistogram().SetMinimum(0)
    #MGAr[-1].GetHistogram().SetMaximum(1)
    MGAr[-1].GetXaxis().SetLimits(0.,1.)
    MGAr[-1].Draw("A*")
    #canAr[-1].BuildLegend()
    canAr[-1].Draw()
    canAr[-1].SaveAs("ABCDResultsByBDTCut_{0}_AllYears_{1}.png".format(addStr,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))





def calcAPred(AW,BW,CW,DW,AWUC,BWUC,CWUC,DWUC):

    print("AW",'%.3f' % AW,"BW",'%.3f' % BW,"CW",'%.3f' % CW,"DW",'%.3f' % DW)

    print("AWUC",'%.3f' % AWUC,"BWUC",'%.3f' % BWUC,"CWUC",'%.3f' % CWUC,"DWUC",'%.3f' % DWUC)

    if BW != 0:
        AOverBUC = sqrt(((AWUC/BW)**2)+
                    ((-AW*BWUC/(BW**2))**2))
        print("AW/BW",'%.3f' % (AW/BW),"AOverBUC",'%.3f' % AOverBUC)
    else:
        AOverBUC = 0
        print("BW == 0")

    if DW != 0:
        COverDUC = sqrt(((CWUC/DW)**2)+
                    ((-CW*DWUC/(DW**2))**2))
        print("CW/DW",'%.3f' % (CW/DW),"COverDUC",'%.3f' % COverDUC)
    else:
        COverDUC = 0
        print("DW == 0")


    if DW != 0:
        APredW = CW*BW/DW
        APredUC = sqrt(((CW*BWUC/DW)**2)+
                    ((CWUC*BW/DW)**2)+
                    ((-CW*BW*DWUC/(DW**2))**2))
    else:
        APredW = 0
        APredUC = 0

    print("APredW",'%.3f' % APredW,"APredUC",'%.3f' % APredUC)
    return APredW,APredUC



def calcAPredWithPoisson(AW,BW,CW,DW,AWUCP,BWUCP,CWUCP,DWUCP,AWUCM,BWUCM,CWUCM,DWUCM):

    print("AW",'%.3f' % AW,"BW",'%.3f' % BW,"CW",'%.3f' % CW,"DW",'%.3f' % DW)

    print("AWUCP",'%.3f' % AWUCP,"BWUCP",'%.3f' % BWUCP,"CWUCP",'%.3f' % CWUCP,"DWUCP",'%.3f' % DWUCP,"AWUCM",'%.3f' % AWUCM,"BWUCM",'%.3f' % BWUCM,"CWUCM",'%.3f' % CWUCM,"DWUCM",'%.3f' % DWUCM)

    if BW != 0:
        AOverBUCP = sqrt(((AWUCP/BW)**2)+
                    ((-AW*BWUCP/(BW**2))**2))
        AOverBUCM = sqrt(((AWUCM/BW)**2)+
                    ((-AW*BWUCM/(BW**2))**2))
        print("AW/BW",'%.3f' % (AW/BW),"+",'%.3f' % AOverBUCP,"-",'%.3f' % AOverBUCM)
    else:
        AOverBUCP = 0
        AOverBUCM = 0
        print("BW == 0")

    if DW != 0:
        COverDUCP = sqrt(((CWUCP/DW)**2)+
                    ((-CW*DWUCP/(DW**2))**2))
        COverDUCM = sqrt(((CWUCM/DW)**2)+
                    ((-CW*DWUCM/(DW**2))**2))
        print("CW/DW",'%.3f' % (CW/DW),"+",'%.3f' % COverDUCP,"-",'%.3f' % COverDUCM)
    else:
        COverDUCP = 0
        COverDUCM = 0
        print("DW == 0")


    if DW != 0:
        APredW = CW*BW/DW
        APredUCP = sqrt(((CW*BWUCP/DW)**2)+
                    ((CWUCP*BW/DW)**2)+
                    ((-CW*BW*DWUCP/(DW**2))**2))
        APredUCM = sqrt(((CW*BWUCM/DW)**2)+
                    ((CWUCM*BW/DW)**2)+
                    ((-CW*BW*DWUCM/(DW**2))**2))
    else:
        APredW = 0
        APredUCP = 0
        APredUCM = 0
        

    print("APredW",'%.3f' % APredW,"+",'%.3f' % APredUCP,"-",'%.3f' % APredUCM)
    return APredW,APredUCP,APredUCM


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

allIncludingData = True
dataOnly = False






datasetNameAr = ["C2V","SM","ttHToBB","ttZJets","DY", #4
            "TTJets","TTbb_TTToHadronic","TTbb_TTToSemiLeptonic","TTbb_TTTo2L2Nu","ST_s_Channel","ST_t_ChannelAntiTop","ST_t_ChannelTop", #11
            "ZZ","WW","WZ", #14
            "ttWJets", #15
            "DYM10To50",
            "ST_tW_antitop","ST_tW_top",
            "EWKWMinus2Jets_WToLNu","EWKWMinus2Jets_WToQQ", #20
            "EWKWPlus2Jets_WToLNu","EWKWPlus2Jets_WToQQ",
            "VHToNonbb",
            "WminusH_HToBB_WToLNu","WminusH_HToBB_WToQQ", #25
            "WplusH_HToBB_WToLNu","WplusH_HToBB_WToQQ",
            "WJetsToLNu",
            "WWW","WWZ","WZZ", #31
            "ZH_HToBB_ZToLL","ZH_HToBB_ZToQQ",
            "ggZH_HToBB_ZToLL","ggZH_HToBB_ZToQQ", #35
            "EWKZ2Jets_ZToLL","EWKZ2Jets_ZToNuNu","EWKZ2Jets_ZToQQ",
            "ZZZ", #39
            "ZH_HToBB_ZToBB","ZH_HToBB_ZToNuNu",
            "ggZH_HToBB_ZToBB","ggZH_HToBB_ZToNuNu"
            ] #
onlyLookingAtInd = 3
onlyLookingAtStrAr = ["C2V","SM","TTHTOBB","TTZJETS","DY",
            "TTJETS","TTBB_TOHADRONIC","TTbb_TTToSemiLeptonic","TTBB_TTTO2L2NU","ST_s_Channel","ST_t_ChannelAntiTop","ST_t_ChannelTop",
            "ZZ","WW","WZ"]
onlyLookingAtStr = onlyLookingAtStrAr[onlyLookingAtInd]

numJECVariationsSignal = 11
numJECVariationsData = 26
numJECUpDown = 2
numJERVariationsSignal = 2
numRochVariations = 5


colorAr = [2,0,7,4,8,
               9,0,0,6,0,41,0,
              42,46,49,
              38,
            1,#0,
            11,12,
            1,1,#0,0,
            1,1,#0,0,
            20,
            1,1,#0,0,
            1,1,#0,0,
            1,#0,
            45,44,41,
            25,1,#0,
            27,1,#0,
            28,1,1,#0,0,
            43]

if dataOnly:
    datasetNameAr = ["BTagCSV","BTagMu", #1
    "Charmonium", 
    "DisplacedJet","DoubleEG","DoubleMuon","DoubleMuonLowMass", #6
    "EGamma",
    "FSQJet1","FSQJet2",
    "HTMHT","HeavyFlavor","HighEGJet","HighPtLowerPhotons","HighPtPhoton30AndZ", #14
    "JetHT",
    "LowEGJet",
    "MET","MuOnia","MuonEG", #19
    "SingleElectron","SingleMuon","SinglePhoton", #22
    "Tau"] 
    colorAr = [3,33,
            37,
            30,39,616,800,
            791,
            633,630,
            866,796,595,622,626,
            805,
            398,
            611,608,631,
            900,432,416,
            898]

makeDataCards = False
justSignal = False
if justSignal:
    makeDataCards = False
NoSLHLT = False

useVBFMjjCut = False
VBFMjjCut = 200

doJECRochJER = False

optionsStrAr = ["allIncludingData","dataOnly","makeDataCards","justSignal","NoSLHLT","useVBFMjjCut","doJECRochJER"]
optionsAr = [allIncludingData,dataOnly,makeDataCards,justSignal,NoSLHLT,useVBFMjjCut,doJECRochJER]

#Print the options being used
for optionsInd in range(len(optionsStrAr)):
    print(optionsStrAr[optionsInd],optionsAr[optionsInd])

datasetSaveNameAr = []
fileAr = []
XSAr = []
totalEvents = []
fileAr = []
useLHEAr = []
gStyle.SetOptStat(0)

if justSignal:
    if NoSLHLT:
        dataSetStrAr = ["new032024BDTAnalysisSDC2V2MCReweightTrimmed_NoSLHLT_WithBDT.root"]
    else:
        dataSetStrAr = ["new032024BDTAnalysisSDC2V2MCReweightTrimmed_WithBDT.root"]
else:
    dataSetStrAr = ["new012024BDTAnalysisSDC2V2MCFebUpdateReweightTrimmed_WithBDT.root",#"new012024BDTAnalysisSDC2V2MCReweightTrimmed_WithBDT.root",
                    "new012024BDTAnalysisUniqueData_WithBDT.root"]
    
addStr = ""

for dataSetStr in dataSetStrAr:
    fileAr.append(TFile.Open(dataSetStr))




ABCDBDTCut = 0.9
ABCDEtaCut = 4
ABCDIMCut = 750

JECUncTypeAr = ["FlavorQCD","RelativeBal","HF","BBEC1","EC2","Absolute"]#["RelativeBal","HF","BBEC1","EC2","Absolute"]
JECUncForYearAr = ["Absolute_","HF_","EC2_","RelativeSample_","BBEC1_"]

cutStageStrAr = []
cutTypeStrAr = ["InitialFilter","PostBTag","LIM","ZIM","HIM","ZPN","HPN"]

cutTitleStrAr = ["Initial Filter","B Tag","Lepton Invariant Mass","Z AK8 Jet Invariant Mass","H AK8 Jet Invariant Mass","Z AK8 Jet Particle Net","H AK8 Jet Particle Net"]

C2VStrAr = ["-2.0","-1.75","-1.5","-1.25","-1.0","-0.75","-0.5","-0.25","0.0", #0.0 = 8
         "0.1","0.2","0.3","0.4","0.5","0.6","0.7","0.8","0.9","1.0","1.1", #1.1 = 19
         "1.2","1.3","1.4","1.5","1.6","1.7","1.8","1.9","2.25","2.5", #2.5 = 30
         "2.75","3.0","3.25","3.5","3.75","4.0"]

yearStrAr = ["2018","2017","2016postVFP","2016preVFP"]

ABCDStrAr = ["A","B","C","D"]

datasetC2V2JECYearUncAr = [[[[0 for i in range(numJECUpDown)] for j in range(len(JECUncForYearAr))] for k in range(len(yearStrAr))] for cutTitle in cutTitleStrAr]
datasetC2V2JECYearUncUCAr = [[[[0 for i in range(numJECUpDown)] for j in range(len(JECUncForYearAr))] for k in range(len(yearStrAr))] for cutTitle in cutTitleStrAr]

datasetC2VReweightJECYearUncAr = [[[[[0 for C2VStr in C2VStrAr] for i in range(numJECUpDown)] for j in range(len(JECUncForYearAr))] for k in range(len(yearStrAr))] for cutTitle in cutTitleStrAr]
datasetC2VReweightJECYearUncUCAr = [[[[[0 for C2VStr in C2VStrAr] for i in range(numJECUpDown)] for j in range(len(JECUncForYearAr))] for k in range(len(yearStrAr))] for cutTitle in cutTitleStrAr]

datasetC2V2ABCDJECYearUncAr = [[[[0 for i in range(numJECUpDown)] for j in range(len(JECUncForYearAr))] for k in range(len(yearStrAr))] for ABCD in ABCDStrAr]
datasetC2V2ABCDJECYearUncUCAr = [[[[0 for i in range(numJECUpDown)] for j in range(len(JECUncForYearAr))] for k in range(len(yearStrAr))] for ABCD in ABCDStrAr]


datasetC2VReweightABCDJECYearUncAr = [[[[[0 for C2VStr in C2VStrAr] for i in range(numJECUpDown)] for j in range(len(JECUncForYearAr))] for k in range(len(yearStrAr))] for ABCD in ABCDStrAr]
datasetC2VReweightABCDJECYearUncUCAr = [[[[[0 for C2VStr in C2VStrAr] for i in range(numJECUpDown)] for j in range(len(JECUncForYearAr))] for k in range(len(yearStrAr))] for ABCD in ABCDStrAr]



datasetC2V2Ar = [0  for cutTitle in cutTitleStrAr]
datasetC2V2UCAr = [0  for cutTitle in cutTitleStrAr]
datasetC2V2JECAr = [[[0 for i in range(numJECUpDown)] for j in range(numJECVariationsSignal)] for cutTitle in cutTitleStrAr]
datasetC2V2JECUCAr = [[[0 for i in range(numJECUpDown)] for j in range(numJECVariationsSignal)] for cutTitle in cutTitleStrAr]
datasetC2V2RochAr = [[0 for i in range(numRochVariations)] for cutTitle in cutTitleStrAr]
datasetC2V2RochUCAr = [[0 for i in range(numRochVariations)] for cutTitle in cutTitleStrAr]
datasetC2V2JERAr = [[0 for i in range(numJERVariationsSignal)] for cutTitle in cutTitleStrAr]
datasetC2V2JERUCAr = [[0 for i in range(numJERVariationsSignal)] for cutTitle in cutTitleStrAr]


datasetC2VReweightAr = [[0 for C2VStr in C2VStrAr]  for cutTitle in cutTitleStrAr]
datasetC2VReweightUCAr = [[0 for C2VStr in C2VStrAr]  for cutTitle in cutTitleStrAr]
datasetC2VReweightJECAr = [[[[0 for C2VStr in C2VStrAr] for i in range(numJECUpDown)] for j in range(numJECVariationsSignal)] for cutTitle in cutTitleStrAr]
datasetC2VReweightJECUCAr = [[[[0 for C2VStr in C2VStrAr] for i in range(numJECUpDown)] for j in range(numJECVariationsSignal)] for cutTitle in cutTitleStrAr]
datasetC2VReweightRochAr = [[[0 for C2VStr in C2VStrAr] for i in range(numRochVariations)] for cutTitle in cutTitleStrAr]
datasetC2VReweightRochUCAr = [[[0 for C2VStr in C2VStrAr] for i in range(numRochVariations)] for cutTitle in cutTitleStrAr]
datasetC2VReweightJERAr = [[[0 for C2VStr in C2VStrAr] for i in range(numJERVariationsSignal)] for cutTitle in cutTitleStrAr]
datasetC2VReweightJERUCAr = [[[0 for C2VStr in C2VStrAr] for i in range(numJERVariationsSignal)] for cutTitle in cutTitleStrAr]

datasetDataEvAr = [0 for cutTitle in cutTitleStrAr]
datasetDataEvJECAr = [[[0 for i in range(numJECUpDown)] for j in range(numJECVariationsData)] for cutTitle in cutTitleStrAr]
datasetDataEvRochAr = [[0 for i in range(numRochVariations)] for cutTitle in cutTitleStrAr]
###########



datasetC2V2ABCDAr = [0  for ABCD in ABCDStrAr]
datasetC2V2ABCDUCAr = [0  for ABCD in ABCDStrAr]
datasetC2V2ABCDJECAr = [[[0 for i in range(numJECUpDown)] for j in range(numJECVariationsSignal)] for ABCD in ABCDStrAr]
datasetC2V2ABCDJECUCAr = [[[0 for i in range(numJECUpDown)] for j in range(numJECVariationsSignal)] for ABCD in ABCDStrAr]
datasetC2V2ABCDRochAr = [[0 for i in range(numRochVariations)] for ABCD in ABCDStrAr]
datasetC2V2ABCDRochUCAr = [[0 for i in range(numRochVariations)] for ABCD in ABCDStrAr]
datasetC2V2ABCDJERAr = [[0 for i in range(numJERVariationsSignal)] for ABCD in ABCDStrAr]
datasetC2V2ABCDJERUCAr = [[0 for i in range(numJERVariationsSignal)] for ABCD in ABCDStrAr]
datasetC2V2DRegABCDAr = [0  for ABCD in ABCDStrAr]
datasetC2V2DRegABCDUCAr = [0  for ABCD in ABCDStrAr]
datasetC2V2DRegABCDJECAr = [[[0 for i in range(numJECUpDown)] for j in range(numJECVariationsSignal)] for ABCD in ABCDStrAr]
datasetC2V2DRegABCDJECUCAr = [[[0 for i in range(numJECUpDown)] for j in range(numJECVariationsSignal)] for ABCD in ABCDStrAr]
datasetC2V2DRegABCDRochAr = [[0 for i in range(numRochVariations)] for ABCD in ABCDStrAr]
datasetC2V2DRegABCDRochUCAr = [[0 for i in range(numRochVariations)] for ABCD in ABCDStrAr]
datasetC2V2DRegABCDJERAr = [[0 for i in range(numJERVariationsSignal)] for ABCD in ABCDStrAr]
datasetC2V2DRegABCDJERUCAr = [[0 for i in range(numJERVariationsSignal)] for ABCD in ABCDStrAr]
 




datasetC2VReweightABCDAr = [[0 for C2VStr in C2VStrAr]  for ABCD in ABCDStrAr]
datasetC2VReweightABCDUCAr = [[0 for C2VStr in C2VStrAr]  for ABCD in ABCDStrAr]
datasetC2VReweightABCDJECAr = [[[[0 for C2VStr in C2VStrAr] for i in range(numJECUpDown)] for j in range(numJECVariationsSignal)] for ABCD in ABCDStrAr]
datasetC2VReweightABCDJECUCAr = [[[[0 for C2VStr in C2VStrAr] for i in range(numJECUpDown)] for j in range(numJECVariationsSignal)] for ABCD in ABCDStrAr]
datasetC2VReweightABCDRochAr = [[[0 for C2VStr in C2VStrAr] for i in range(numRochVariations)] for ABCD in ABCDStrAr]
datasetC2VReweightABCDRochUCAr = [[[0 for C2VStr in C2VStrAr] for i in range(numRochVariations)] for ABCD in ABCDStrAr]
datasetC2VReweightABCDJERAr = [[[0 for C2VStr in C2VStrAr] for i in range(numJERVariationsSignal)] for ABCD in ABCDStrAr]
datasetC2VReweightABCDJERUCAr = [[[0 for C2VStr in C2VStrAr] for i in range(numJERVariationsSignal)] for ABCD in ABCDStrAr]
datasetC2VReweightDRegABCDAr = [[0 for C2VStr in C2VStrAr]  for ABCD in ABCDStrAr]
datasetC2VReweightDRegABCDUCAr = [[0 for C2VStr in C2VStrAr]  for ABCD in ABCDStrAr]
datasetC2VReweightDRegABCDJECAr = [[[[0 for C2VStr in C2VStrAr] for i in range(numJECUpDown)] for j in range(numJECVariationsSignal)] for ABCD in ABCDStrAr]
datasetC2VReweightDRegABCDJECUCAr = [[[[0 for C2VStr in C2VStrAr] for i in range(numJECUpDown)] for j in range(numJECVariationsSignal)] for ABCD in ABCDStrAr]
datasetC2VReweightDRegABCDRochAr = [[[0 for C2VStr in C2VStrAr] for i in range(numRochVariations)] for ABCD in ABCDStrAr]
datasetC2VReweightDRegABCDRochUCAr = [[[0 for C2VStr in C2VStrAr] for i in range(numRochVariations)] for ABCD in ABCDStrAr]
datasetC2VReweightDRegABCDJERAr = [[[0 for C2VStr in C2VStrAr] for i in range(numJERVariationsSignal)] for ABCD in ABCDStrAr]
datasetC2VReweightDRegABCDJERUCAr = [[[0 for C2VStr in C2VStrAr] for i in range(numJERVariationsSignal)] for ABCD in ABCDStrAr]


datasetDataEvABCDAr = [0 for ABCD in ABCDStrAr]
datasetDataEvABCDJECAr = [[[0 for i in range(numJECUpDown)] for j in range(numJECVariationsData)] for ABCD in ABCDStrAr]
datasetDataEvABCDRochAr = [[0 for i in range(numRochVariations)] for ABCD in ABCDStrAr]
datasetDataEvDRegABCDAr = [0 for ABCD in ABCDStrAr]
datasetDataEvDRegABCDJECAr = [[[0 for i in range(numJECUpDown)] for j in range(numJECVariationsData)] for ABCD in ABCDStrAr]
datasetDataEvDRegABCDRochAr = [[0 for i in range(numRochVariations)] for ABCD in ABCDStrAr]



V3InvariantMassLowCut = 80
V3InvariantMassHighCut = 100
V1BTagCut = 0.9

V9ParticleNetZCut = 0.6
V9ParticleNetCut = 0.2

V9ZIMSDMassCutLow = 20
V9ZIMSDMassCutHigh = 160

V9HIMSDMassCutLow = 20
V9HIMSDMassCutHigh = 160

V13ZIMSDMassCutLow = 40
V13ZIMSDMassCutHigh = 1000000

V13HIMSDMassCutLow = 40
V13HIMSDMassCutHigh = 1000000

V14ZPNRegressMassCutLow = 40
V14UntreatedMassCutLow = 50
V14HPNRegressMassCutLow = 70
V14HPNRegressMassCutHigh = 160

skipCtr = 0
cutCtr = 0

bTagUL18Cut = 0.7100
bTagUL17Cut = 0.7476
bTagUL16Cut = 0.6377
bTagUL16APVCut = 0.6502

bTagAr = [bTagUL18Cut,bTagUL17Cut,bTagUL16Cut,bTagUL16APVCut]

print(len(datasetDataEvJECAr),len(datasetDataEvJECAr[0]),len(datasetDataEvJECAr[0][0]))

breakEvEarly = False
breakEvAt = 10000
fullEvCtr = 0
##################MAIN LOOP##################
for k,fileA in enumerate(fileAr):
    evCtr = 0

    
    if dataOnly or (allIncludingData and k == 1):
        tmpTree = fileA.passingEvSemiLepUniqueTree
    else:
        tmpTree = fileA.passingEvSemiLepTree
    
    print("Looping over events")
    #LOOP OVER EVENTS IN FILE k
    for j,ev in enumerate(tmpTree):
        if breakEvEarly and evCtr >= breakEvAt:
            break
        if evCtr % 10000 == 0:
            print("ev:",evCtr)
        if dataOnly or (allIncludingData and k == 1):
            tmpDataSetType = ev.datasetType_SLU_L
        else:
            tmpDataSetType = ev.datasetType_SL_L
        
        
        if dataOnly or (allIncludingData and k == 1):
            tmpH_Xbb = ev.selectedHiggsFJ_ParticleNetMD_Xbb_SLU_L
            tmpH_QCD = ev.selectedHiggsFJ_ParticleNetMD_QCD_SLU_L
            

            tmpZ_Xbb = ev.selectedZFJ_ParticleNetMD_Xbb_SLU_L
            tmpZ_Xcc = ev.selectedZFJ_ParticleNetMD_Xcc_SLU_L
            tmpZ_Xqq = ev.selectedZFJ_ParticleNetMD_Xqq_SLU_L
            tmpZ_QCD = ev.selectedZFJ_ParticleNetMD_QCD_SLU_L
            
            
            tmpMaxBTag = ev.selectedVBFJets_MaxBTag_SLU_L
            tmpLIM = ev.selectedLeptons_InvMass_SLU_L
            tmpZIM = ev.selectedZFJ_InvMassSoftDrop_SLU_L
            tmpHIM = ev.selectedHiggsFJ_InvMassSoftDrop_SLU_L
            tmpZPNRIM = ev.selectedZFJ_InvMassPNRegress_SLU_L
            tmpHPNRIM = ev.selectedHiggsFJ_InvMassPNRegress_SLU_L
            tmpZUGIM = ev.selectedZFJ_InvMass_SLU_L
            tmpHUGIM = ev.selectedHiggsFJ_InvMass_SLU_L
            valAr = [ev.bdt,
            ev.selectedVBFJets_EtaSep_SLU_L,
            ev.selectedVBFJets_InvMass_SLU_L]
            tmpWeight = 1
            tmpIsMuon = ev.selectedLeptons_IsMuon_SLU_L
            tmpYear = ev.yearType_SLU_L
            tmpnJet = ev.eventNAK4Jets_SLU_L
            tmpnAK8Jet = ev.eventNAK8Jets_SLU_L
            tmpnElec = ev.eventNElectrons_SLU_L
            tmpnMuon = ev.eventNMuons_SLU_L
            tmpnPassingAK4Jet = ev.eventNAK4JetsPassingCuts_SLU_L
            lepdR = calcDeltaR(ev.selectedLeadLepton_phi_SLU_L, ev.selectedLeadLepton_eta_SLU_L, ev.selectedTrailingLepton_phi_SLU_L, ev.selectedTrailingLepton_eta_SLU_L)
            tmpVBFJetPairInvMass = ev.selectedVBFJets_InvMass_SLU_L
            tmpVBFJetPairEtaSep = ev.selectedVBFJets_EtaSep_SLU_L
            JECCorInd = ev.JECCorInd_SLU_L-1
            JECCorUpOrDown = ev.uncUpDown-1
            RochInd = ev.RochInd_SLU_L-1


        else:
            tmpH_Xbb = ev.selectedHiggsFJ_ParticleNetMD_Xbb_SL_L
            tmpH_QCD = ev.selectedHiggsFJ_ParticleNetMD_QCD_SL_L
            

            tmpZ_Xbb = ev.selectedZFJ_ParticleNetMD_Xbb_SL_L
            tmpZ_Xcc = ev.selectedZFJ_ParticleNetMD_Xcc_SL_L
            tmpZ_Xqq = ev.selectedZFJ_ParticleNetMD_Xqq_SL_L
            tmpZ_QCD = ev.selectedZFJ_ParticleNetMD_QCD_SL_L
            
            
            tmpMaxBTag = ev.selectedVBFJets_MaxBTag_SL_L
            tmpLIM = ev.selectedLeptons_InvMass_SL_L
            tmpZIM = ev.selectedZFJ_InvMassSoftDrop_SL_L
            tmpHIM = ev.selectedHiggsFJ_InvMassSoftDrop_SL_L
            tmpZPNRIM = ev.selectedZFJ_InvMassPNRegress_SL_L
            tmpHPNRIM = ev.selectedHiggsFJ_InvMassPNRegress_SL_L
            tmpZUGIM = ev.selectedZFJ_InvMass_SL_L
            tmpHUGIM = ev.selectedHiggsFJ_InvMass_SL_L

            tmpWeight = ev.fullWeight
            valAr = [ev.bdt,
            ev.selectedVBFJets_EtaSep_SL_L,
            ev.selectedVBFJets_InvMass_SL_L]
            tmpIsMuon = ev.selectedLeptons_IsMuon_SL_L
            tmpYear = ev.yearType_SL_L
            tmpYearForBTag = tmpYear
            tmpnJet = ev.eventNAK4Jets_SL_L
            tmpnAK8Jet = ev.eventNAK8Jets_SL_L
            #if tmpYear == 3: #03242024 Not sure why this was in here in the first place. some place where 2016 and 2016 APV were treated as the same, but for how tmpYear is used this is not what we want
            #    tmpYear = 2
            tmpnElec = ev.eventNElectrons_SL_L
            tmpnMuon = ev.eventNMuons_SL_L

            tmpnPassingAK4Jet = ev.eventNAK4JetsPassingCuts_SL_L
            lepdR = calcDeltaR(ev.selectedLeadLepton_phi_SL_L, ev.selectedLeadLepton_eta_SL_L, ev.selectedTrailingLepton_phi_SL_L, ev.selectedTrailingLepton_eta_SL_L)
            tmpVBFJetPairInvMass = ev.selectedVBFJets_InvMass_SL_L
            tmpVBFJetPairEtaSep = ev.selectedVBFJets_EtaSep_SL_L
            JECCorInd = ev.JECCorInd_SL_L-1
            JECCorUpOrDown = ev.JECCorUpOrDown_SL_L
            JERInd = ev.JERInd_SL_L-1
            RochInd = ev.RochInd_SL_L-1
            if k == 0:
                nLHEReweight  = ev.nLHEReweightingWeight_SL_L
                LHEReweightAr = ev.LHEReweightingWeight_SL_L


        
        

        HPNMD = tmpH_Xbb/(tmpH_Xbb+tmpH_QCD)
        ZPNMD = (tmpZ_Xbb+tmpZ_Xcc+tmpZ_Xqq)/(tmpZ_Xbb+tmpZ_Xcc+tmpZ_Xqq+tmpZ_QCD)
        subInt = 0
        if tmpDataSetType >= 50:
            subInt = 35
            #print(tmpDataSetType)
            #tmpTypeInd = tmpDataSetType -24
        #else if tmpDataSetType >=26:
        #    subInt = 
        elif tmpDataSetType > 25:
            subInt = 26

        elif tmpDataSetType == 25:
            subInt = 25
        
        tmpTypeInd = tmpDataSetType-subInt

        tmpBTag = bTagAr[tmpYearForBTag]

        stopAtInd = 0
        if (tmpMaxBTag<=tmpBTag):
            stopAtInd += 1
            if (tmpLIM >= V3InvariantMassLowCut and tmpLIM <= V3InvariantMassHighCut):
                stopAtInd += 1
                if (tmpZIM >= V13ZIMSDMassCutLow and tmpZIM <= V13ZIMSDMassCutHigh and tmpZPNRIM >= V14ZPNRegressMassCutLow and tmpZUGIM >= V14UntreatedMassCutLow):
                    stopAtInd += 1
                    if (tmpHIM >= V13HIMSDMassCutLow and tmpHIM <= V13HIMSDMassCutHigh  and tmpHPNRIM >= V14HPNRegressMassCutLow and tmpHPNRIM <= V14HPNRegressMassCutHigh and tmpHUGIM >= V14UntreatedMassCutLow):
                        stopAtInd += 1
                        if (ZPNMD >= V9ParticleNetZCut):
                            stopAtInd += 1
                            if (HPNMD >= V9ParticleNetCut):
                                stopAtInd += 1

        if (useVBFMjjCut and tmpVBFJetPairInvMass < VBFMjjCut):
            stopAtInd = 0

        if JECCorInd < 0 and RochInd < 0:
            if dataOnly or (allIncludingData and k == 1):
                for addInd in range(stopAtInd+1):
                    datasetDataEvAr[addInd] += 1
            elif JERInd < 0:
                for addInd in range(stopAtInd+1):
                    datasetC2V2Ar[addInd] += tmpWeight
                    datasetC2V2UCAr[addInd] += tmpWeight**2
                    for C2VInd in range(nLHEReweight):
                        datasetC2VReweightAr[addInd][C2VInd] += tmpWeight*LHEReweightAr[C2VInd]
                        datasetC2VReweightUCAr[addInd][C2VInd] += (tmpWeight*LHEReweightAr[C2VInd])**2
                    #Doing by-year JEC Uncertainty
                    for yearInd in range(len(yearStrAr)):
                        if yearInd != tmpYear:
                            for JECCorTypeInd in range(len(JECUncForYearAr)):
                                for JECCorUpOrDownInd in range(numJECUpDown):
                                    datasetC2V2JECYearUncAr[stopAtInd][yearInd][JECCorTypeInd][JECCorUpOrDownInd] += tmpWeight
                                    datasetC2V2JECYearUncUCAr[stopAtInd][yearInd][JECCorTypeInd][JECCorUpOrDownInd] += tmpWeight**2
                                    for C2VInd in range(nLHEReweight):
                                        datasetC2VReweightJECYearUncAr[stopAtInd][yearInd][JECCorTypeInd][JECCorUpOrDownInd][C2VInd] += tmpWeight*LHEReweightAr[C2VInd]
                                        datasetC2VReweightJECYearUncUCAr[stopAtInd][yearInd][JECCorTypeInd][JECCorUpOrDownInd][C2VInd] += (tmpWeight*LHEReweightAr[C2VInd])**2
            else:
                for addInd in range(stopAtInd+1):
                    datasetC2V2JERAr[addInd][JERInd] += tmpWeight
                    datasetC2V2JERUCAr[addInd][JERInd] += tmpWeight**2
                    for C2VInd in range(nLHEReweight):
                        datasetC2VReweightJERAr[addInd][JERInd][C2VInd] += tmpWeight*LHEReweightAr[C2VInd]
                        datasetC2VReweightJERUCAr[addInd][JERInd][C2VInd] += (tmpWeight*LHEReweightAr[C2VInd])**2
        elif JECCorInd >= 0:
            if dataOnly or (allIncludingData and k == 1):
                for addInd in range(stopAtInd+1):
                    datasetDataEvJECAr[addInd][JECCorInd][JECCorUpOrDown] += 1
            else:
                for addInd in range(stopAtInd+1):
                    datasetC2V2JECAr[addInd][JECCorInd][JECCorUpOrDown] += tmpWeight
                    datasetC2V2JECUCAr[addInd][JECCorInd][JECCorUpOrDown] += tmpWeight**2
                    for C2VInd in range(nLHEReweight):
                        datasetC2VReweightJECAr[addInd][JECCorInd][JECCorUpOrDown][C2VInd] += tmpWeight*LHEReweightAr[C2VInd]
                        datasetC2VReweightJECUCAr[addInd][JECCorInd][JECCorUpOrDown][C2VInd] += (tmpWeight*LHEReweightAr[C2VInd])**2
                    if JECCorInd > 5: #03242024 changing from >4 to >5. I think it being >4 was leftover from when I wasn't using flavorQCD
                        #Doing by-year JEC Uncertainty
                        datasetC2V2JECYearUncAr[stopAtInd][tmpYear][JECCorInd-6][JECCorUpOrDown] += tmpWeight
                        datasetC2V2JECYearUncUCAr[stopAtInd][tmpYear][JECCorInd-6][JECCorUpOrDown] += tmpWeight**2
                        for C2VInd in range(nLHEReweight):
                            datasetC2VReweightJECYearUncAr[stopAtInd][tmpYear][JECCorInd-6][JECCorUpOrDown][C2VInd] += tmpWeight*LHEReweightAr[C2VInd]
                            datasetC2VReweightJECYearUncUCAr[stopAtInd][tmpYear][JECCorInd-6][JECCorUpOrDown][C2VInd] += (tmpWeight*LHEReweightAr[C2VInd])**2
        elif RochInd >= 0:
            if dataOnly or (allIncludingData and k == 1):
                for addInd in range(stopAtInd+1):
                    datasetDataEvRochAr[addInd][RochInd] += 1
            else:
                for addInd in range(stopAtInd+1):
                    datasetC2V2RochAr[addInd][RochInd] += tmpWeight
                    datasetC2V2RochUCAr[addInd][RochInd] += tmpWeight**2
                    for C2VInd in range(nLHEReweight):
                        datasetC2VReweightRochAr[addInd][RochInd][C2VInd] += tmpWeight*LHEReweightAr[C2VInd]
                        datasetC2VReweightRochUCAr[addInd][RochInd][C2VInd] += (tmpWeight*LHEReweightAr[C2VInd])**2

        if stopAtInd == 6:
            ABCDInd = 3
            if ((tmpVBFJetPairEtaSep >= ABCDEtaCut) and (tmpVBFJetPairInvMass >= ABCDIMCut)):
                if (valAr[0] >= ABCDBDTCut):
                    ABCDInd = 0
                else:
                    ABCDInd = 2
            else:
                if (valAr[0] >= ABCDBDTCut):
                    ABCDInd = 1
            
            if JECCorInd < 0 and RochInd < 0:
                if dataOnly or (allIncludingData and k == 1):
                        datasetDataEvABCDAr[ABCDInd] += 1
                elif JERInd < 0:
                    datasetC2V2ABCDAr[ABCDInd] += tmpWeight
                    datasetC2V2ABCDUCAr[ABCDInd] += tmpWeight**2
                    for C2VInd in range(nLHEReweight):
                        datasetC2VReweightABCDAr[ABCDInd][C2VInd] += tmpWeight*LHEReweightAr[C2VInd]
                        datasetC2VReweightABCDUCAr[ABCDInd][C2VInd] += (tmpWeight*LHEReweightAr[C2VInd])**2
                    #Doing by-year JEC Uncertainty
                    for yearInd in range(len(yearStrAr)):
                        if yearInd != tmpYear:
                            for JECCorTypeInd in range(len(JECUncForYearAr)):
                                for JECCorUpOrDownInd in range(numJECUpDown):
                                    datasetC2V2ABCDJECYearUncAr[ABCDInd][yearInd][JECCorTypeInd][JECCorUpOrDownInd] += tmpWeight
                                    datasetC2V2ABCDJECYearUncUCAr[ABCDInd][yearInd][JECCorTypeInd][JECCorUpOrDownInd] += tmpWeight**2
                                    for C2VInd in range(nLHEReweight):
                                        datasetC2VReweightABCDJECYearUncAr[ABCDInd][yearInd][JECCorTypeInd][JECCorUpOrDownInd][C2VInd] += tmpWeight*LHEReweightAr[C2VInd]
                                        datasetC2VReweightABCDJECYearUncUCAr[ABCDInd][yearInd][JECCorTypeInd][JECCorUpOrDownInd][C2VInd] += (tmpWeight*LHEReweightAr[C2VInd])**2
                else:
                    datasetC2V2ABCDJERAr[ABCDInd][JERInd] += tmpWeight
                    datasetC2V2ABCDJERUCAr[ABCDInd][JERInd] += tmpWeight**2
                    for C2VInd in range(nLHEReweight):
                        datasetC2VReweightABCDJERAr[ABCDInd][JERInd][C2VInd] += tmpWeight*LHEReweightAr[C2VInd]
                        datasetC2VReweightABCDJERUCAr[ABCDInd][JERInd][C2VInd] += (tmpWeight*LHEReweightAr[C2VInd])**2
            elif JECCorInd >= 0:
                if dataOnly or (allIncludingData and k == 1):
                    datasetDataEvABCDJECAr[ABCDInd][JECCorInd][JECCorUpOrDown] += 1
                else:
                    datasetC2V2ABCDJECAr[ABCDInd][JECCorInd][JECCorUpOrDown] += tmpWeight
                    datasetC2V2ABCDJECUCAr[ABCDInd][JECCorInd][JECCorUpOrDown] += tmpWeight**2
                    for C2VInd in range(nLHEReweight):
                        datasetC2VReweightABCDJECAr[ABCDInd][JECCorInd][JECCorUpOrDown][C2VInd] += tmpWeight*LHEReweightAr[C2VInd]
                        datasetC2VReweightABCDJECUCAr[ABCDInd][JECCorInd][JECCorUpOrDown][C2VInd] += (tmpWeight*LHEReweightAr[C2VInd])**2
                    if JECCorInd > 5: #03242024 changing from >4 to >5. I think it being >4 was leftover from when I wasn't using flavorQCD
                        #Doing by-year JEC Uncertainty
                        datasetC2V2ABCDJECYearUncAr[ABCDInd][tmpYear][JECCorInd-6][JECCorUpOrDown] += tmpWeight
                        datasetC2V2ABCDJECYearUncUCAr[ABCDInd][tmpYear][JECCorInd-6][JECCorUpOrDown] += tmpWeight**2
                        for C2VInd in range(nLHEReweight):
                            datasetC2VReweightABCDJECYearUncAr[ABCDInd][tmpYear][JECCorInd-6][JECCorUpOrDown][C2VInd] += tmpWeight*LHEReweightAr[C2VInd]
                            datasetC2VReweightABCDJECYearUncUCAr[ABCDInd][tmpYear][JECCorInd-6][JECCorUpOrDown][C2VInd] += (tmpWeight*LHEReweightAr[C2VInd])**2
            elif RochInd >= 0:
                if dataOnly or (allIncludingData and k == 1):
                    datasetDataEvABCDRochAr[ABCDInd][RochInd] += 1
                else:
                    datasetC2V2ABCDRochAr[ABCDInd][RochInd] += tmpWeight
                    datasetC2V2ABCDRochUCAr[ABCDInd][RochInd] += tmpWeight**2
                    for C2VInd in range(nLHEReweight):
                        datasetC2VReweightABCDRochAr[ABCDInd][RochInd][C2VInd] += tmpWeight*LHEReweightAr[C2VInd]
                        datasetC2VReweightABCDRochUCAr[ABCDInd][RochInd][C2VInd] += (tmpWeight*LHEReweightAr[C2VInd])**2

            """
            if ABCDInd == 3:
                if JECCorInd < 0 and RochInd < 0:
                    if dataOnly or (allIncludingData and k == 1):
                        datasetDataEvABCDAr[ABCDInd] += 1
                    elif JERInd < 0:
                        datasetC2V2ABCDAr[ABCDInd] += tmpWeight
                        datasetC2V2ABCDUCAr[ABCDInd] += tmpWeight**2
                        for C2VInd in range(nLHEReweight):
                            datasetC2VReweightABCDAr[ABCDInd][C2VInd] += tmpWeight*LHEReweightAr[C2VInd]
                            datasetC2VReweightABCDUCAr[ABCDInd][C2VInd] += (tmpWeight*LHEReweightAr[C2VInd])**2
                    else:
                        datasetC2V2ABCDJERAr[ABCDInd][JERInd] += tmpWeight
                        datasetC2V2ABCDJERUCAr[ABCDInd][JERInd] += tmpWeight**2
                        for C2VInd in range(nLHEReweight):
                            datasetC2VReweightABCDJERAr[ABCDInd][JERInd][C2VInd] += tmpWeight*LHEReweightAr[C2VInd]
                            datasetC2VReweightABCDJERUCAr[ABCDInd][JERInd][C2VInd] += (tmpWeight*LHEReweightAr[C2VInd])**2
                elif JECCorInd >= 0:
                    if dataOnly or (allIncludingData and k == 1):
                        datasetDataEvABCDJECAr[ABCDInd][JECCorInd][JECCorUpOrDown] += 1
                    else:
                        datasetC2V2ABCDJECAr[ABCDInd][JECCorInd][JECCorUpOrDown] += tmpWeight
                        datasetC2V2ABCDJECUCAr[ABCDInd][JECCorInd][JECCorUpOrDown] += tmpWeight**2
                        for C2VInd in range(nLHEReweight):
                            datasetC2VReweightABCDJECAr[ABCDInd][JECCorInd][JECCorUpOrDown][C2VInd] += tmpWeight*LHEReweightAr[C2VInd]
                            datasetC2VReweightABCDJECUCAr[ABCDInd][JECCorInd][JECCorUpOrDown][C2VInd] += (tmpWeight*LHEReweightAr[C2VInd])**2
                elif RochInd >= 0:
                    if dataOnly or (allIncludingData and k == 1):
                        datasetDataEvABCDRochAr[ABCDInd][RochInd] += 1
                    else:
                        datasetC2V2ABCDRochAr[ABCDInd][RochInd] += tmpWeight
                        datasetC2V2ABCDRochUCAr[ABCDInd][RochInd] += tmpWeight**2
                        for C2VInd in range(nLHEReweight):
                            datasetC2VReweightABCDRochAr[ABCDInd][RochInd][C2VInd] += tmpWeight*LHEReweightAr[C2VInd]
                            datasetC2VReweightABCDRochUCAr[ABCDInd][RochInd][C2VInd] += (tmpWeight*LHEReweightAr[C2VInd])**2
            """


        evCtr += 1
        fullEvCtr += 1
    
print("fullEvCtr",fullEvCtr)


##################END MAIN LOOP##################
print("Finished main loop")

for i,cutTitleStr in enumerate(cutTitleStrAr):
    print(cutTitleStr)
    print("------------------------------")
    #first print out the C2V at 2 values
    print("C2V2",datasetC2V2Ar[i],sqrt(datasetC2V2UCAr[i]))
    if doJECRochJER:
        for JECInd in range(numJECVariationsSignal):
            print("C2V2JEC",JECInd,"Up",datasetC2V2JECAr[i][JECInd][0],sqrt(datasetC2V2JECUCAr[i][JECInd][0]),"Down",datasetC2V2JECAr[i][JECInd][1],sqrt(datasetC2V2JECUCAr[i][JECInd][1]))
        for JERInd in range(numJERVariationsSignal):
            print("C2V2JER",JERInd,datasetC2V2JERAr[i][JERInd],sqrt(datasetC2V2JERUCAr[i][JERInd]))
        for RochInd in range(numRochVariations):
            print("C2V2Roch",RochInd,datasetC2V2RochAr[i][RochInd],sqrt(datasetC2V2RochUCAr[i][RochInd]))
    #now loop over the other C2V Values
    for C2VInd,C2VStr in enumerate(C2VStrAr):
        print("C2V",C2VStr,datasetC2VReweightAr[i][C2VInd],sqrt(datasetC2VReweightUCAr[i][C2VInd]))
        if doJECRochJER:
            for JECInd in range(numJECVariationsSignal):
                print("C2VJEC",C2VStr,JECInd,"Up",datasetC2VReweightJECAr[i][JECInd][0][C2VInd],sqrt(datasetC2VReweightJECUCAr[i][JECInd][0][C2VInd]),"Down",datasetC2VReweightJECAr[i][JECInd][1][C2VInd],sqrt(datasetC2VReweightJECUCAr[i][JECInd][1][C2VInd]))
            for JERInd in range(numJERVariationsSignal):
                print("C2VJER",C2VStr,JERInd,datasetC2VReweightJERAr[i][JERInd][C2VInd],sqrt(datasetC2VReweightJERUCAr[i][JERInd][C2VInd]))
            for RochInd in range(numRochVariations):
                print("C2VRoch",C2VStr,RochInd,datasetC2VReweightRochAr[i][RochInd][C2VInd],sqrt(datasetC2VReweightRochUCAr[i][RochInd][C2VInd]))
    #Now data
    print("Data",datasetDataEvAr[i])
    #for JECInd in range(numJECVariationsData):
    #    print("DataJEC",JECInd,"Up",datasetDataEvJECAr[i][JECInd][0],"Down",datasetDataEvJECAr[i][JECInd][1])
    #for RochInd in range(numRochVariations):
    #    print("DataRoch",RochInd,datasetDataEvRochAr[i][RochInd])

    print("")
    print("+++++++++++++++++++++++++++++++")

DCBAStrAr = ["D","C","B","A"]
#Now print out ABCD results
print("")
print("")
print("ABCD results")
for ABCDInd,ABCDStr in enumerate(DCBAStrAr):
    print("{0} Region".format(ABCDStr))
    #first print out the C2V at 2 values
    print("C2V2",datasetC2V2ABCDAr[3-ABCDInd],sqrt(datasetC2V2ABCDUCAr[3-ABCDInd]))
    if doJECRochJER:
        for JECInd in range(numJECVariationsSignal):
            print("C2V2JEC",JECInd,"Up",datasetC2V2ABCDJECAr[3-ABCDInd][JECInd][0],sqrt(datasetC2V2ABCDJECUCAr[3-ABCDInd][JECInd][0]),"Down",datasetC2V2ABCDJECAr[3-ABCDInd][JECInd][1],sqrt(datasetC2V2ABCDJECUCAr[3-ABCDInd][JECInd][1]))
        for JERInd in range(numJERVariationsSignal):
            print("C2V2JER",JERInd,datasetC2V2ABCDJERAr[3-ABCDInd][JERInd],sqrt(datasetC2V2ABCDJERUCAr[3-ABCDInd][JERInd]))
        for RochInd in range(numRochVariations):
            print("C2V2Roch",RochInd,datasetC2V2ABCDRochAr[3-ABCDInd][RochInd],sqrt(datasetC2V2ABCDRochUCAr[3-ABCDInd][RochInd]))
    #now loop over the other C2V Values
    for C2VInd,C2VStr in enumerate(C2VStrAr):
        print("C2V",C2VStr,datasetC2VReweightABCDAr[3-ABCDInd][C2VInd],sqrt(datasetC2VReweightABCDUCAr[3-ABCDInd][C2VInd]))
        if doJECRochJER:
            for JECInd in range(numJECVariationsSignal):
                print("C2VJEC",C2VStr,JECInd,"Up",datasetC2VReweightABCDJECAr[3-ABCDInd][JECInd][0][C2VInd],sqrt(datasetC2VReweightABCDJECUCAr[3-ABCDInd][JECInd][0][C2VInd]),"Down",datasetC2VReweightABCDJECAr[3-ABCDInd][JECInd][1][C2VInd],sqrt(datasetC2VReweightABCDJECUCAr[3-ABCDInd][JECInd][1][C2VInd]))
            for JERInd in range(numJERVariationsSignal):
                print("C2VJER",C2VStr,JERInd,datasetC2VReweightABCDJERAr[3-ABCDInd][JERInd][C2VInd],sqrt(datasetC2VReweightABCDJERUCAr[3-ABCDInd][JERInd][C2VInd]))
            for RochInd in range(numRochVariations):
                print("C2VRoch",C2VStr,RochInd,datasetC2VReweightABCDRochAr[3-ABCDInd][RochInd][C2VInd],sqrt(datasetC2VReweightABCDRochUCAr[3-ABCDInd][RochInd][C2VInd]))
    #Now data
    if ABCDInd <3:
        print("Data",datasetDataEvABCDAr[3-ABCDInd])
        #for JECInd in range(numJECVariationsData):
        #    print("DataJEC",JECInd,"Up",datasetDataEvABCDJECAr[3-ABCDInd][JECInd][0],"Down",datasetDataEvABCDJECAr[3-ABCDInd][JECInd][1])
        #for RochInd in range(numRochVariations):
        #    print("DataRoch",RochInd,datasetDataEvABCDRochAr[3-ABCDInd][RochInd])

    print("")
    print("")



dataBValFinalPoissonUC = poisson_interval(datasetDataEvABCDAr[1],0.3173)
dataCValFinalPoissonUC = poisson_interval(datasetDataEvABCDAr[2],0.3173)
dataDValFinalPoissonUC = poisson_interval(datasetDataEvABCDAr[3],0.3173)


dataBValFinalPoissonUCP = dataBValFinalPoissonUC[1]-datasetDataEvABCDAr[1]
dataBValFinalPoissonUCM = abs(dataBValFinalPoissonUC[0]-datasetDataEvABCDAr[1])

dataCValFinalPoissonUCP = dataCValFinalPoissonUC[1]-datasetDataEvABCDAr[2]
dataCValFinalPoissonUCM = abs(dataCValFinalPoissonUC[0]-datasetDataEvABCDAr[2])

dataDValFinalPoissonUCP = dataDValFinalPoissonUC[1]-datasetDataEvABCDAr[3]
dataDValFinalPoissonUCM = abs(dataDValFinalPoissonUC[0]-datasetDataEvABCDAr[3])
print("data with poisson uncertainty")
print("B")
print("Data",datasetDataEvABCDAr[1],"+",'%.3f' % (dataBValFinalPoissonUCP),"-",'%.3f' % (dataBValFinalPoissonUCM))

print("C")
print("Data",datasetDataEvABCDAr[2],"+",'%.3f' % (dataCValFinalPoissonUCP),"-",'%.3f' % (dataCValFinalPoissonUCM))

print("D")
print("Data",datasetDataEvABCDAr[3],"+",'%.3f' % (dataDValFinalPoissonUCP),"-",'%.3f' % (dataDValFinalPoissonUCM))

print("Data DA Pred:")
dataAPred,dataAPredPosUnc,dataAPredNegUnc = calcAPredWithPoisson(1,datasetDataEvABCDAr[1],datasetDataEvABCDAr[2],datasetDataEvABCDAr[3],1,dataBValFinalPoissonUCP,dataCValFinalPoissonUCP,dataDValFinalPoissonUCP,1,dataBValFinalPoissonUCM,dataCValFinalPoissonUCM,dataDValFinalPoissonUCM)
print("Data A Pred",dataAPred,"+",dataAPredPosUnc,"-",dataAPredNegUnc)

dataABCD = [dataAPred,datasetDataEvABCDAr[1],datasetDataEvABCDAr[2],datasetDataEvABCDAr[3]]
dataABCDStatUnc = [[dataAPredPosUnc,dataAPredNegUnc],[dataBValFinalPoissonUCP,dataBValFinalPoissonUCM],[dataCValFinalPoissonUCP,dataCValFinalPoissonUCM],[dataDValFinalPoissonUCP,dataDValFinalPoissonUCM]]

if makeDataCards:
    C2VmpStrAr = ["m2p0","m1p75","m1p5","m1p25","m1p0","m0p75","m0p5","m0p25","0p0", #0p0 = 8
            "0p1","0p2","0p3","0p4","0p5","0p6","0p7","0p8","0p9","1p0","1p1", #1p1 = 19
            "1p2","1p3","1p4","1p5","1p6","1p7","1p8","1p9","2p25","2p5", #2p5 = 30
            "2p75","3p0","3p25","3p5","3p75","4p0"]

    RochUnchTypeStrAr = ["RochUnchUp","RochUnchDown"]

    #Making the datacards
    #First make the datacard for C2V2

    outFileDataCard = open("HZZ_C2V_2p0.txt","w")

    outFileDataCard.write("imax    4 number of channels\n")
    outFileDataCard.write("jmax    1 number of backgrounds\n")
    outFileDataCard.write("kmax    * number of nuisance parameters\n")

    outFileDataCard.write("--------------------------------------------------------------------------------------------------------------------------------\n")
    outFileDataCard.write("bin                                                     A           B           C           D           \n")
    outFileDataCard.write("observation                                             {0}           {1}           {2}           {3}           \n".format(dataAPred,datasetDataEvABCDAr[1],datasetDataEvABCDAr[2],datasetDataEvABCDAr[3]))
    outFileDataCard.write("--------------------------------------------------------------------------------------------------------------------------------\n")
    outFileDataCard.write("bin                                                     A           B           C           D           A           B           C           D           \n")
    outFileDataCard.write("process                                                 TotalBkg    TotalBkg    TotalBkg    TotalBkg    TotalSig    TotalSig    TotalSig    TotalSig    \n")
    outFileDataCard.write("process                                                 1           1           1           1           0           0           0           0           \n")
    outFileDataCard.write("rate                                                    1           1           1           1           {0:.5f}     {1:.5f}     {2:.5f}    {3:.5f}    \n".format(datasetC2V2ABCDAr[0],datasetC2V2ABCDAr[1],datasetC2V2ABCDAr[2],datasetC2V2ABCDAr[3]))
    outFileDataCard.write("--------------------------------------------------------------------------------------------------------------------------------\n")
    outFileDataCard.write("CMS_vbsvvhHZZ_abcd_syst                           lnN   2.1           -           -           -           -           -           -           -           \n")
    #outFileDataCard.write("CMS_vbsvvhHZZ_abcd_stat                           lnN   ")
    #for ABCDInd in range(4):
    #        outFileDataCard.write("{0:.5f}/{1:.5f}     ".format((dataABCD[ABCDInd]-dataABCDStatUnc[ABCDInd][1])/dataABCD[ABCDInd],(dataABCD[ABCDInd]+dataABCDStatUnc[ABCDInd][0])/dataABCD[ABCDInd]))
    #outFileDataCard.write("-           -           -           -           ")
    #outFileDataCard.write("\n")
    outFileDataCard.write("CMS_vbsvvhHZZ_abcd_statB                           lnN   {0:.5f}/{1:.5f}           {0:.5f}/{1:.5f}          -           -           -           -           -           -           \n".format((dataABCD[1]-dataABCDStatUnc[1][1])/dataABCD[1],(dataABCD[1]+dataABCDStatUnc[1][0])/dataABCD[1]))
    outFileDataCard.write("CMS_vbsvvhHZZ_abcd_statC                           lnN   {0:.5f}/{1:.5f}           -          {0:.5f}/{1:.5f}           -           -           -           -           -           \n".format((dataABCD[2]-dataABCDStatUnc[2][1])/dataABCD[2],(dataABCD[2]+dataABCDStatUnc[2][0])/dataABCD[2]))
    outFileDataCard.write("CMS_vbsvvhHZZ_abcd_statD                           lnN   {0:.5f}/{1:.5f}           -          -           {0:.5f}/{1:.5f}           -           -           -           -           \n".format((dataABCD[3]-dataABCDStatUnc[3][1])/dataABCD[3],(dataABCD[3]+dataABCDStatUnc[3][0])/dataABCD[3]))
    #outFileDataCard.write("CMS_vbsvvhHZZ_mcstat                           lnN   -           -           -           -           ")
    #for ABCDInd in range(4):
    #        outFileDataCard.write("{0:.5f}/{1:.5f}     ".format((datasetC2V2ABCDAr[ABCDInd]-sqrt(datasetC2V2ABCDUCAr[ABCDInd]))/datasetC2V2ABCDAr[ABCDInd],(datasetC2V2ABCDAr[ABCDInd]+sqrt(datasetC2V2ABCDUCAr[ABCDInd]))/datasetC2V2ABCDAr[ABCDInd]))
    #outFileDataCard.write("\n")
    outFileDataCard.write("CMS_vbsvvhHZZ_mcstatA                           lnN   -           -           -           -           {0:.5f}/{1:.5f}           -          -           -           \n".format((datasetC2V2ABCDAr[0]-datasetC2V2ABCDUCAr[0])/datasetC2V2ABCDAr[0],(datasetC2V2ABCDAr[0]+datasetC2V2ABCDUCAr[0])/datasetC2V2ABCDAr[0]))
    outFileDataCard.write("CMS_vbsvvhHZZ_mcstatB                           lnN   -           -           -           -           -           {0:.5f}/{1:.5f}          -           -           \n".format((datasetC2V2ABCDAr[1]-datasetC2V2ABCDUCAr[1])/datasetC2V2ABCDAr[1],(datasetC2V2ABCDAr[1]+datasetC2V2ABCDUCAr[1])/datasetC2V2ABCDAr[1]))
    outFileDataCard.write("CMS_vbsvvhHZZ_mcstatC                           lnN   -           -           -           -           -           -           {0:.5f}/{1:.5f}           -          \n".format((datasetC2V2ABCDAr[2]-datasetC2V2ABCDUCAr[2])/datasetC2V2ABCDAr[2],(datasetC2V2ABCDAr[2]+datasetC2V2ABCDUCAr[2])/datasetC2V2ABCDAr[2]))
    outFileDataCard.write("CMS_vbsvvhHZZ_mcstatD                           lnN   -           -           -           -           -           -           -           {0:.5f}/{1:.5f}           \n".format((datasetC2V2ABCDAr[3]-datasetC2V2ABCDUCAr[3])/datasetC2V2ABCDAr[3],(datasetC2V2ABCDAr[3]+datasetC2V2ABCDUCAr[3])/datasetC2V2ABCDAr[3]))
    for JECInd,JECUncStr in enumerate(JECUncTypeAr):
        outFileDataCard.write("CMS_Scale_j_{0}_13TeV                           lnN   -           -           -           -           ".format(JECUncStr))
        for ABCDInd in range(4):
            outFileDataCard.write("{0:.5f}/{1:.5f}     ".format((datasetC2V2ABCDJECAr[ABCDInd][JECInd][1]/datasetC2V2ABCDAr[ABCDInd]),(datasetC2V2ABCDJECAr[ABCDInd][JECInd][0]/datasetC2V2ABCDAr[ABCDInd])))
        outFileDataCard.write("\n")
    outFileDataCard.write("CMS_res_j_13TeV                           lnN   -           -           -           -           ")
    for ABCDInd in range(4):
        outFileDataCard.write("{0:.5f}/{1:.5f}     ".format((datasetC2V2ABCDJERAr[ABCDInd][1]/datasetC2V2ABCDAr[ABCDInd]),(datasetC2V2ABCDJERAr[ABCDInd][0]/datasetC2V2ABCDAr[ABCDInd])))
    outFileDataCard.write("\n")
    #forgot to do roch stuff properly. add this later
    #For now move on to the by-year JEC Uncertainties
    for yearInd,yearStr in enumerate(yearStrAr):
        for JECCorInd,JECCorStr in enumerate(JECUncForYearAr):
            outFileDataCard.write("CMS_Scale_j_{0}{1}_13TeV                           lnN   -           -           -           -           ".format(JECCorStr,yearStr))
            for ABCDInd in range(4):
                outFileDataCard.write("{0:.5f}/{1:.5f}     ".format((datasetC2V2ABCDJECYearUncAr[ABCDInd][yearInd][JECCorInd][1]/datasetC2V2ABCDAr[ABCDInd]),(datasetC2V2ABCDJECYearUncAr[ABCDInd][yearInd][JECCorInd][0]/datasetC2V2ABCDAr[ABCDInd])))
            outFileDataCard.write("\n")
    outFileDataCard.write("--------------------------------------------------------------------------------------------------------------------------------\n")
    outFileDataCard.write("HZZ_A rateParam                  A  TotalBkg    (@0*@1/@2) HZZ_B,HZZ_C,HZZ_D    \n")
    outFileDataCard.write("HZZ_B rateParam                  B  TotalBkg    {0} [0,{1}]                 \n".format(datasetDataEvABCDAr[1],dataABCD[1]+(3*dataABCDStatUnc[1][0])))
    outFileDataCard.write("HZZ_C rateParam                  C  TotalBkg    {0} [0,{1}]                 \n".format(datasetDataEvABCDAr[2],dataABCD[2]+(3*dataABCDStatUnc[2][0])))
    outFileDataCard.write("HZZ_D rateParam                  D  TotalBkg    {0} [0,{1}]                 \n".format(datasetDataEvABCDAr[3],dataABCD[3]+(3*dataABCDStatUnc[3][0])))

    outFileDataCard.close()


    for C2VInd,C2VStr in enumerate(C2VmpStrAr):
        outFileDataCard = open("HZZ_C2V_{0}.txt".format(C2VStr),"w")

        outFileDataCard.write("imax    4 number of channels\n")
        outFileDataCard.write("jmax    1 number of backgrounds\n")
        outFileDataCard.write("kmax    * number of nuisance parameters\n")

        outFileDataCard.write("--------------------------------------------------------------------------------------------------------------------------------\n")
        outFileDataCard.write("bin                                                     A           B           C           D           \n")
        outFileDataCard.write("observation                                             {0}           {1}           {2}           {3}           \n".format(dataAPred,datasetDataEvABCDAr[1],datasetDataEvABCDAr[2],datasetDataEvABCDAr[3]))
        outFileDataCard.write("--------------------------------------------------------------------------------------------------------------------------------\n")
        outFileDataCard.write("bin                                                     A           B           C           D           A           B           C           D           \n")
        outFileDataCard.write("process                                                 TotalBkg    TotalBkg    TotalBkg    TotalBkg    TotalSig    TotalSig    TotalSig    TotalSig    \n")
        outFileDataCard.write("process                                                 1           1           1           1           0           0           0           0           \n")
        outFileDataCard.write("rate                                                    1           1           1           1           {0:.5f}     {1:.5f}     {2:.5f}    {3:.5f}    \n".format(datasetC2VReweightABCDAr[0][C2VInd],datasetC2VReweightABCDAr[1][C2VInd],datasetC2VReweightABCDAr[2][C2VInd],datasetC2VReweightABCDAr[3][C2VInd]))
        outFileDataCard.write("--------------------------------------------------------------------------------------------------------------------------------\n")
        outFileDataCard.write("CMS_vbsvvhHZZ_abcd_syst                           lnN   2.1           -           -           -           -           -           -           -           \n")
        #outFileDataCard.write("CMS_vbsvvhHZZ_abcd_stat                           lnN   ")
        #for ABCDInd in range(4):
        #        outFileDataCard.write("{0:.5f}/{1:.5f}     ".format((dataABCD[ABCDInd]-dataABCDStatUnc[ABCDInd][1])/dataABCD[ABCDInd],(dataABCD[ABCDInd]+dataABCDStatUnc[ABCDInd][0])/dataABCD[ABCDInd]))
        #outFileDataCard.write("-           -           -           -           ")
        #outFileDataCard.write("\n")
        outFileDataCard.write("CMS_vbsvvhHZZ_abcd_statB                           lnN   {0:.5f}/{1:.5f}           {0:.5f}/{1:.5f}          -           -           -           -           -           -           \n".format((dataABCD[1]-dataABCDStatUnc[1][1])/dataABCD[1],(dataABCD[1]+dataABCDStatUnc[1][0])/dataABCD[1]))
        outFileDataCard.write("CMS_vbsvvhHZZ_abcd_statC                           lnN   {0:.5f}/{1:.5f}           -          {0:.5f}/{1:.5f}           -           -           -           -           -           \n".format((dataABCD[2]-dataABCDStatUnc[2][1])/dataABCD[2],(dataABCD[2]+dataABCDStatUnc[2][0])/dataABCD[2]))
        outFileDataCard.write("CMS_vbsvvhHZZ_abcd_statD                           lnN   {0:.5f}/{1:.5f}           -          -           {0:.5f}/{1:.5f}           -           -           -           -           \n".format((dataABCD[3]-dataABCDStatUnc[3][1])/dataABCD[3],(dataABCD[3]+dataABCDStatUnc[3][0])/dataABCD[3]))
        #outFileDataCard.write("CMS_vbsvvhHZZ_mcstat                           lnN   -           -           -           -           ")
        #for ABCDInd in range(4):
        #        outFileDataCard.write("{0:.5f}/{1:.5f}     ".format((datasetC2VReweightABCDAr[ABCDInd][C2VInd]-sqrt(datasetC2VReweightABCDUCAr[ABCDInd][C2VInd]))/datasetC2VReweightABCDAr[ABCDInd][C2VInd],(datasetC2VReweightABCDAr[ABCDInd][C2VInd]+sqrt(datasetC2VReweightABCDUCAr[ABCDInd][C2VInd]))/datasetC2VReweightABCDAr[ABCDInd][C2VInd]))
        #outFileDataCard.write("\n")
        outFileDataCard.write("CMS_vbsvvhHZZ_mcstatA                           lnN   -           -           -           -           {0:.5f}/{1:.5f}           -          -           -           \n".format((datasetC2VReweightABCDAr[0][C2VInd]-datasetC2VReweightABCDUCAr[0][C2VInd])/datasetC2VReweightABCDAr[0][C2VInd],(datasetC2VReweightABCDAr[0][C2VInd]+datasetC2VReweightABCDUCAr[0][C2VInd])/datasetC2VReweightABCDAr[0][C2VInd]))
        outFileDataCard.write("CMS_vbsvvhHZZ_mcstatB                           lnN   -           -           -           -           -           {0:.5f}/{1:.5f}          -           -           \n".format((datasetC2VReweightABCDAr[1][C2VInd]-datasetC2VReweightABCDUCAr[1][C2VInd])/datasetC2VReweightABCDAr[1][C2VInd],(datasetC2VReweightABCDAr[1][C2VInd]+datasetC2VReweightABCDUCAr[1][C2VInd])/datasetC2VReweightABCDAr[1][C2VInd]))
        outFileDataCard.write("CMS_vbsvvhHZZ_mcstatC                           lnN   -           -           -           -           -           -           {0:.5f}/{1:.5f}           -          \n".format((datasetC2VReweightABCDAr[2][C2VInd]-datasetC2VReweightABCDUCAr[2][C2VInd])/datasetC2VReweightABCDAr[2][C2VInd],(datasetC2VReweightABCDAr[2][C2VInd]+datasetC2VReweightABCDUCAr[2][C2VInd])/datasetC2VReweightABCDAr[2][C2VInd]))
        outFileDataCard.write("CMS_vbsvvhHZZ_mcstatD                           lnN   -           -           -           -           -           -           -           {0:.5f}/{1:.5f}           \n".format((datasetC2VReweightABCDAr[3][C2VInd]-datasetC2VReweightABCDUCAr[3][C2VInd])/datasetC2VReweightABCDAr[3][C2VInd],(datasetC2VReweightABCDAr[3][C2VInd]+datasetC2VReweightABCDUCAr[3][C2VInd])/datasetC2VReweightABCDAr[3][C2VInd]))
        for JECInd,JECUncStr in enumerate(JECUncTypeAr):
            outFileDataCard.write("CMS_Scale_j_{0}_13TeV                          lnN   -           -           -           -           ".format(JECUncStr))
            for ABCDInd in range(4):
                outFileDataCard.write("{0:.5f}/{1:.5f}     ".format(datasetC2VReweightABCDJECAr[ABCDInd][JECInd][1][C2VInd]/datasetC2VReweightABCDAr[ABCDInd][C2VInd],datasetC2VReweightABCDJECAr[ABCDInd][JECInd][0][C2VInd]/datasetC2VReweightABCDAr[ABCDInd][C2VInd]))
            outFileDataCard.write("\n")
        outFileDataCard.write("CMS_res_j_13TeV                           lnN   -           -           -           -           ")
        for ABCDInd in range(4):
            outFileDataCard.write("{0:.5f}/{1:.5f}     ".format(datasetC2VReweightABCDJERAr[ABCDInd][1][C2VInd]/datasetC2VReweightABCDAr[ABCDInd][C2VInd],datasetC2VReweightABCDJERAr[ABCDInd][0][C2VInd]/datasetC2VReweightABCDAr[ABCDInd][C2VInd]))
        outFileDataCard.write("\n")
        #forgot to do roch stuff properly. add this later
        #For now move on to the by-year JEC Uncertainties
        for yearInd,yearStr in enumerate(yearStrAr):
            for JECCorInd,JECCorStr in enumerate(JECUncForYearAr):
                outFileDataCard.write("CMS_Scale_j_{0}{1}_13TeV                           lnN   -           -           -           -           ".format(JECCorStr,yearStr))
                for ABCDInd in range(4):
                    outFileDataCard.write("{0:.5f}/{1:.5f}     ".format(datasetC2VReweightABCDJECYearUncAr[ABCDInd][yearInd][JECCorInd][1][C2VInd]/datasetC2VReweightABCDAr[ABCDInd][C2VInd],datasetC2VReweightABCDJECYearUncAr[ABCDInd][yearInd][JECCorInd][0][C2VInd]/datasetC2VReweightABCDAr[ABCDInd][C2VInd]))
                outFileDataCard.write("\n")
        outFileDataCard.write("--------------------------------------------------------------------------------------------------------------------------------\n")
        outFileDataCard.write("HZZ_A rateParam                  A  TotalBkg    (@0*@1/@2) HZZ_B,HZZ_C,HZZ_D    \n")
        outFileDataCard.write("HZZ_B rateParam                  B  TotalBkg    {0} [0,{1}]                 \n".format(datasetDataEvABCDAr[1],dataABCD[1]+(3*dataABCDStatUnc[1][0])))
        outFileDataCard.write("HZZ_C rateParam                  C  TotalBkg    {0} [0,{1}]                 \n".format(datasetDataEvABCDAr[2],dataABCD[2]+(3*dataABCDStatUnc[2][0])))
        outFileDataCard.write("HZZ_D rateParam                  D  TotalBkg    {0} [0,{1}]                 \n".format(datasetDataEvABCDAr[3],dataABCD[3]+(3*dataABCDStatUnc[3][0])))

        outFileDataCard.close()







"""
#Now print out ABCD results for D Region
print("")
print("")
print("ABCD results for D Region")
for ABCDInd,ABCDStr in enumerate(DCBAStrAr):
    print("{0} Region".format(ABCDStr))
    #first print out the C2V at 2 values
    print("C2V2",datasetC2V2DRegABCDAr[3-ABCDInd],sqrt(datasetC2V2DRegABCDUCAr[3-ABCDInd]))
    for JECInd in range(numJECVariationsSignal):
        print("C2V2JEC",JECInd,"Up",datasetC2V2DRegABCDJECAr[3-ABCDInd][JECInd][0],sqrt(datasetC2V2DRegABCDJECUCAr[3-ABCDInd][JECInd][0]),"Down",datasetC2V2DRegABCDJECAr[3-ABCDInd][JECInd][1],sqrt(datasetC2V2DRegABCDJECUCAr[3-ABCDInd][JECInd][1]))
    for JERInd in range(numJERVariationsSignal):
        print("C2V2JER",JERInd,datasetC2V2DRegABCDJERAr[3-ABCDInd][JERInd],sqrt(datasetC2V2DRegABCDJERUCAr[3-ABCDInd][JERInd]))
    for RochInd in range(numRochVariations):
        print("C2V2Roch",RochInd,datasetC2V2DRegABCDRochAr[3-ABCDInd][RochInd],sqrt(datasetC2V2DRegABCDRochUCAr[3-ABCDInd][RochInd]))
    #now loop over the other C2V Values
    for C2VInd,C2VStr in enumerate(C2VStrAr):
        print("C2V",C2VStr,datasetC2VReweightDRegABCDAr[3-ABCDInd][C2VInd],sqrt(datasetC2VReweightDRegABCDUCAr[3-ABCDInd][C2VInd]))
        for JECInd in range(numJECVariationsSignal):
            print("C2VJEC",C2VStr,JECInd,"Up",datasetC2VReweightDRegABCDJECAr[3-ABCDInd][JECInd][0][C2VInd],sqrt(datasetC2VReweightDRegABCDJECUCAr[3-ABCDInd][JECInd][0][C2VInd]),"Down",datasetC2VReweightDRegABCDJECAr[3-ABCDInd][JECInd][1][C2VInd],sqrt(datasetC2VReweightDRegABCDJECUCAr[3-ABCDInd][JECInd][1][C2VInd]))
        for JERInd in range(numJERVariationsSignal):
            print("C2VJER",C2VStr,JERInd,datasetC2VReweightDRegABCDJERAr[3-ABCDInd][JERInd][C2VInd],sqrt(datasetC2VReweightDRegABCDJERUCAr[3-ABCDInd][JERInd][C2VInd]))
        for RochInd in range(numRochVariations):
            print("C2VRoch",C2VStr,RochInd,datasetC2VReweightDRegABCDRochAr[3-ABCDInd][RochInd][C2VInd],sqrt(datasetC2VReweightDRegABCDRochUCAr[3-ABCDInd][RochInd][C2VInd]))
    #Now data
    if ABCDInd <3:
        print("Data",datasetDataEvDRegABCDAr[3-ABCDInd])
        #for JECInd in range(numJECVariationsData):
        #    print("DataJEC",JECInd,"Up",datasetDataEvDRegABCDJECAr[3-ABCDInd][JECInd][0],"Down",datasetDataEvDRegABCDJECAr[3-ABCDInd][JECInd][1])
        #for RochInd in range(numRochVariations):
        #    print("DataRoch",RochInd,datasetDataEvDRegABCDRochAr[3-ABCDInd][RochInd])
        
    print("")
    print("")
"""

"""
print("")
print("")
for i,cutTitleStr in enumerate(cutTitleStrAr):
    if i >= 8:
        break
    print(cutTitleStr,datasetDataEvAr[i],sqrt(datasetDataEvAr[i]))

print("")
print("")
print("Reweighted C2V values for final BDT cut:")
for datasetC2VReweightVal,datasetC2VReweightValUC,C2VStr in zip(datasetC2VReweightAr,datasetC2VReweightUCAr,C2VStrAr):
    print(C2VStr,datasetC2VReweightVal,sqrt(datasetC2VReweightValUC))

print("")
print("")
print("ABCD results")

print("A")
print("Signal",'%.3f' % signalAVal,"+/-",'%.3f' % sqrt(signalAValUC),"\t\tN",MCCountAr[0][0][0])
print("Background",'%.3f' % backgroundAVal,"+/-",'%.3f' % sqrt(backgroundAValUC),"\tN",MCCountAr[1][0][0])

print("B")
print("Signal",'%.3f' % signalBVal,"+/-",'%.3f' % sqrt(signalBValUC),"\t\tN",MCCountAr[0][0][1])
print("Background",'%.3f' % backgroundBVal,"+/-",'%.3f' % sqrt(backgroundBValUC),"\tN",MCCountAr[1][0][1])

print("C")
print("Signal",'%.3f' % signalCVal,"+/-",'%.3f' % sqrt(signalCValUC),"\t\tN",MCCountAr[0][0][2])
print("Background",'%.3f' % backgroundCVal,"+/-",'%.3f' % sqrt(backgroundCValUC),"\tN",MCCountAr[1][0][2])

print("D")
print("Signal",'%.3f' % signalDVal,"+/-",'%.3f' % sqrt(signalDValUC),"\t\tN",MCCountAr[0][0][3])
print("Background",'%.3f' % backgroundDVal,"+/-",'%.3f' % sqrt(backgroundDValUC),"\tN",MCCountAr[1][0][3])

calcAPred(backgroundAVal,backgroundBVal,backgroundCVal,backgroundDVal,sqrt(backgroundAValUC),sqrt(backgroundBValUC),sqrt(backgroundCValUC),sqrt(backgroundDValUC))

print("")
print("")
print("ABCD D region validation")

dataDAValFinalUC = sqrt(dataDAVal)
dataDBValFinalUC = sqrt(dataDBVal)
dataDCValFinalUC = sqrt(dataDCVal)
dataDDValFinalUC = sqrt(dataDDVal)

dataDAValFinalPoissonUC = poisson_interval(dataDAVal,0.3173)
dataDBValFinalPoissonUC = poisson_interval(dataDBVal,0.3173)
dataDCValFinalPoissonUC = poisson_interval(dataDCVal,0.3173)
dataDDValFinalPoissonUC = poisson_interval(dataDDVal,0.3173)

dataDAValFinalPoissonUCP = dataDAValFinalPoissonUC[1]-dataDAVal
dataDAValFinalPoissonUCM = abs(dataDAValFinalPoissonUC[0]-dataDAVal)

dataDBValFinalPoissonUCP = dataDBValFinalPoissonUC[1]-dataDBVal
dataDBValFinalPoissonUCM = abs(dataDBValFinalPoissonUC[0]-dataDBVal)

dataDCValFinalPoissonUCP = dataDCValFinalPoissonUC[1]-dataDCVal
dataDCValFinalPoissonUCM = abs(dataDCValFinalPoissonUC[0]-dataDCVal)

dataDDValFinalPoissonUCP = dataDDValFinalPoissonUC[1]-dataDDVal
dataDDValFinalPoissonUCM = abs(dataDDValFinalPoissonUC[0]-dataDDVal)

print("DA")
print("Signal",'%.3f' % signalDAVal,"+/-",'%.3f' % sqrt(signalDAValUC),"\t\tN",MCCountAr[0][1][0])
print("Background",'%.3f' % backgroundDAVal,"+/-",'%.3f' % sqrt(backgroundDAValUC),"\tN",MCCountAr[1][1][0])
print("Data",dataDAVal,"+",'%.3f' % (dataDAValFinalPoissonUCP),"-",'%.3f' % (dataDAValFinalPoissonUCM))

print("DB")
print("Signal",'%.3f' % signalDBVal,"+/-",'%.3f' % sqrt(signalDBValUC),"\t\tN",MCCountAr[0][1][1])
print("Background",'%.3f' % backgroundDBVal,"+/-",'%.3f' % sqrt(backgroundDBValUC),"\tN",MCCountAr[1][1][1])
print("Data",dataDBVal,"+",'%.3f' % (dataDBValFinalPoissonUCP),"-",'%.3f' % (dataDBValFinalPoissonUCM))

print("DC")
print("Signal",'%.3f' % signalDCVal,"+/-",'%.3f' % sqrt(signalDCValUC),"\t\tN",MCCountAr[0][1][2])
print("Background",'%.3f' % backgroundDCVal,"+/-",'%.3f' % sqrt(backgroundDCValUC),"\tN",MCCountAr[1][1][2])
print("Data",dataDCVal,"+",'%.3f' % (dataDCValFinalPoissonUCP),"-",'%.3f' % (dataDCValFinalPoissonUCM))

print("DD")
print("Signal",'%.3f' % signalDDVal,"+/-",'%.3f' % sqrt(signalDDValUC),"\t\tN",MCCountAr[0][1][3])
print("Background",'%.3f' % backgroundDDVal,"+/-",'%.3f' % sqrt(backgroundDDValUC),"\tN",MCCountAr[1][1][3])
print("Data",dataDDVal,"+",'%.3f' % (dataDDValFinalPoissonUCP),"-",'%.3f' % (dataDDValFinalPoissonUCM))

print("MC DA Pred:")
calcAPred(backgroundDAVal,backgroundDBVal,backgroundDCVal,backgroundDDVal,sqrt(backgroundDAValUC),sqrt(backgroundDBValUC),sqrt(backgroundDCValUC),sqrt(backgroundDDValUC))
print("Data DA Pred:")
calcAPredWithPoisson(dataDAVal,dataDBVal,dataDCVal,dataDDVal,dataDAValFinalPoissonUCP,dataDBValFinalPoissonUCP,dataDCValFinalPoissonUCP,dataDDValFinalPoissonUCP,dataDAValFinalPoissonUCM,dataDBValFinalPoissonUCM,dataDCValFinalPoissonUCM,dataDDValFinalPoissonUCM)


DRegionDataEtaCan.cd()
makeNiceHistos(DRegionDataEtaHist,"BDT Value","VBF Jet Eta Separation",False)
DRegionDataEtaHist.SetTitle("Data in D Region, BDT Vs VBF Jet Eta Separation")

DRegionDataEtaHist.GetXaxis().CenterTitle()
DRegionDataEtaHist.Draw("COLZ")
DRegionDataEtaCan.Draw()
bdtCutLine = TLine(ABCDBDTCut/2,ABCDEtaCut/2,ABCDBDTCut/2,ABCDEtaCut)
bdtCutLine.SetLineColor(2)
bdtCutLine.SetLineWidth(4)
bdtCutLine.SetLineStyle(9)
bdtCutLine.Draw()
etaCutLine = TLine(0,3*ABCDEtaCut/4,ABCDBDTCut,3*ABCDEtaCut/4)
etaCutLine.SetLineColor(2)
etaCutLine.SetLineWidth(4)
etaCutLine.SetLineStyle(9)
etaCutLine.Draw()
DRegionDataEtaCan.Update()
DRegionDataEtaCan.SaveAs("dataInDRegion_BDTVsVBFEta_AllYears_{0}_{1}.png".format(addStr,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))


DRegionDataIMCan.cd()
makeNiceHistos(DRegionDataIMHist,"BDT Value","VBF Jet IM",False)
DRegionDataIMHist.SetTitle("Data in D Region, BDT Vs VBF Jet IM")

DRegionDataIMHist.GetXaxis().CenterTitle()
DRegionDataIMHist.Draw("COLZ")
DRegionDataIMCan.Draw()
bdtCutLine = TLine(ABCDBDTCut/2,0,ABCDBDTCut/2,ABCDIMCut)
bdtCutLine.SetLineColor(2)
bdtCutLine.SetLineWidth(4)
bdtCutLine.SetLineStyle(9)
bdtCutLine.Draw()
IMCutLine = TLine(0,ABCDIMCut/2,ABCDBDTCut,ABCDIMCut/2)
IMCutLine.SetLineColor(2)
IMCutLine.SetLineWidth(4)
IMCutLine.SetLineStyle(9)
IMCutLine.Draw()
DRegionDataIMCan.Update()
DRegionDataIMCan.SaveAs("dataInDRegion_BDTVsVBFIM_AllYears_{0}_{1}.png".format(addStr,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))


print("")
print("")
print("No BDT ABCD D region validation")

dataDANoBDTValFinalUC = sqrt(dataDANoBDTVal)
dataDBNoBDTValFinalUC = sqrt(dataDBNoBDTVal)
dataDCNoBDTValFinalUC = sqrt(dataDCNoBDTVal)
dataDDNoBDTValFinalUC = sqrt(dataDDNoBDTVal)

dataDANoBDTValFinalPoissonUC = poisson_interval(dataDANoBDTVal,0.3173)
dataDBNoBDTValFinalPoissonUC = poisson_interval(dataDBNoBDTVal,0.3173)
dataDCNoBDTValFinalPoissonUC = poisson_interval(dataDCNoBDTVal,0.3173)
dataDDNoBDTValFinalPoissonUC = poisson_interval(dataDDNoBDTVal,0.3173)

dataDANoBDTValFinalPoissonUCP = dataDANoBDTValFinalPoissonUC[1]-dataDANoBDTVal
dataDANoBDTValFinalPoissonUCM = abs(dataDANoBDTValFinalPoissonUC[0]-dataDANoBDTVal)

dataDBNoBDTValFinalPoissonUCP = dataDBNoBDTValFinalPoissonUC[1]-dataDBNoBDTVal
dataDBNoBDTValFinalPoissonUCM = abs(dataDBNoBDTValFinalPoissonUC[0]-dataDBNoBDTVal)

dataDCNoBDTValFinalPoissonUCP = dataDCNoBDTValFinalPoissonUC[1]-dataDCNoBDTVal
dataDCNoBDTValFinalPoissonUCM = abs(dataDCNoBDTValFinalPoissonUC[0]-dataDCNoBDTVal)

dataDDNoBDTValFinalPoissonUCP = dataDDNoBDTValFinalPoissonUC[1]-dataDDNoBDTVal
dataDDNoBDTValFinalPoissonUCM = abs(dataDDNoBDTValFinalPoissonUC[0]-dataDDNoBDTVal)

print("DA")
print("Signal",'%.3f' % signalDANoBDTVal,"+/-",'%.3f' % sqrt(signalDANoBDTValUC),"\t\tN",MCCountAr[0][2][0])
print("Background",'%.3f' % backgroundDANoBDTVal,"+/-",'%.3f' % sqrt(backgroundDANoBDTValUC),"\tN",MCCountAr[1][2][0])
print("Data",dataDANoBDTVal,"+",'%.3f' % (dataDANoBDTValFinalPoissonUCP),"-",'%.3f' % (dataDANoBDTValFinalPoissonUCM))

print("DB")
print("Signal",'%.3f' % signalDBNoBDTVal,"+/-",'%.3f' % sqrt(signalDBNoBDTValUC),"\t\tN",MCCountAr[0][2][1])
print("Background",'%.3f' % backgroundDBNoBDTVal,"+/-",'%.3f' % sqrt(backgroundDBNoBDTValUC),"\tN",MCCountAr[1][2][1])
print("Data",dataDBNoBDTVal,"+",'%.3f' % (dataDBNoBDTValFinalPoissonUCP),"-",'%.3f' % (dataDBNoBDTValFinalPoissonUCM))

print("DC")
print("Signal",'%.3f' % signalDCNoBDTVal,"+/-",'%.3f' % sqrt(signalDCNoBDTValUC),"\t\tN",MCCountAr[0][2][2])
print("Background",'%.3f' % backgroundDCNoBDTVal,"+/-",'%.3f' % sqrt(backgroundDCNoBDTValUC),"\tN",MCCountAr[1][2][2])
print("Data",dataDCNoBDTVal,"+",'%.3f' % (dataDCNoBDTValFinalPoissonUCP),"-",'%.3f' % (dataDCNoBDTValFinalPoissonUCM))

print("DD")
print("Signal",'%.3f' % signalDDNoBDTVal,"+/-",'%.3f' % sqrt(signalDDNoBDTValUC),"\t\tN",MCCountAr[0][2][3])
print("Background",'%.3f' % backgroundDDNoBDTVal,"+/-",'%.3f' % sqrt(backgroundDDNoBDTValUC),"\tN",MCCountAr[1][2][3])
print("Data",dataDDNoBDTVal,"+",'%.3f' % (dataDDNoBDTValFinalPoissonUCP),"-",'%.3f' % (dataDDNoBDTValFinalPoissonUCM))

print("MC DA Pred:")
calcAPred(backgroundDANoBDTVal,backgroundDBNoBDTVal,backgroundDCNoBDTVal,backgroundDDNoBDTVal,sqrt(backgroundDANoBDTValUC),sqrt(backgroundDBNoBDTValUC),sqrt(backgroundDCNoBDTValUC),sqrt(backgroundDDNoBDTValUC))
print("Data DA Pred:")
calcAPredWithPoisson(dataDANoBDTVal,dataDBNoBDTVal,dataDCNoBDTVal,dataDDNoBDTVal,dataDANoBDTValFinalPoissonUCP,dataDBNoBDTValFinalPoissonUCP,dataDCNoBDTValFinalPoissonUCP,dataDDNoBDTValFinalPoissonUCP,dataDANoBDTValFinalPoissonUCM,dataDBNoBDTValFinalPoissonUCM,dataDCNoBDTValFinalPoissonUCM,dataDDNoBDTValFinalPoissonUCM)

DRegionDataEtaIMNoBDTCan.cd()
makeNiceHistos(DRegionDataEtaIMNoBDTHist,"VBF Jet Eta Separation","VBF Jet IM",False)
DRegionDataEtaIMNoBDTHist.SetTitle("Data in D Region (No BDT ABCD), VBF Jet Eta Separation Vs VBF Jet IM")

DRegionDataEtaIMNoBDTHist.GetXaxis().CenterTitle()
DRegionDataEtaIMNoBDTHist.Draw("COLZ")
DRegionDataEtaIMNoBDTCan.Draw()
etaCutLine = TLine(3*ABCDEtaCut/4,0,3*ABCDEtaCut/4,ABCDIMCut)
etaCutLine.SetLineColor(2)
etaCutLine.SetLineWidth(4)
etaCutLine.SetLineStyle(9)
etaCutLine.Draw()
IMCutLine = TLine(ABCDEtaCut/2,ABCDIMCut/2,ABCDEtaCut,ABCDIMCut/2)
IMCutLine.SetLineColor(2)
IMCutLine.SetLineWidth(4)
IMCutLine.SetLineStyle(9)
IMCutLine.Draw()

DRegionDataEtaIMNoBDTCan.Update()
DRegionDataEtaIMNoBDTCan.SaveAs("dataInNoBDTDRegion_EtaSepVsIM_AllYears_{0}_{1}.png".format(addStr,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))


print("")
print("")
print("No BDT, BDT Fail full ABCD validation")

dataANoBDTValFinalUC = sqrt(dataANoBDTVal)
dataBNoBDTValFinalUC = sqrt(dataBNoBDTVal)
dataCNoBDTValFinalUC = sqrt(dataCNoBDTVal)
dataDNoBDTValFinalUC = sqrt(dataDNoBDTVal)

dataANoBDTValFinalPoissonUC = poisson_interval(dataANoBDTVal,0.3173)
dataBNoBDTValFinalPoissonUC = poisson_interval(dataBNoBDTVal,0.3173)
dataCNoBDTValFinalPoissonUC = poisson_interval(dataCNoBDTVal,0.3173)
dataDNoBDTValFinalPoissonUC = poisson_interval(dataDNoBDTVal,0.3173)

dataANoBDTValFinalPoissonUCP = dataANoBDTValFinalPoissonUC[1]-dataANoBDTVal
dataANoBDTValFinalPoissonUCM = abs(dataANoBDTValFinalPoissonUC[0]-dataANoBDTVal)

dataBNoBDTValFinalPoissonUCP = dataBNoBDTValFinalPoissonUC[1]-dataBNoBDTVal
dataBNoBDTValFinalPoissonUCM = abs(dataBNoBDTValFinalPoissonUC[0]-dataBNoBDTVal)

dataCNoBDTValFinalPoissonUCP = dataCNoBDTValFinalPoissonUC[1]-dataCNoBDTVal
dataCNoBDTValFinalPoissonUCM = abs(dataCNoBDTValFinalPoissonUC[0]-dataCNoBDTVal)

dataDNoBDTValFinalPoissonUCP = dataDNoBDTValFinalPoissonUC[1]-dataDNoBDTVal
dataDNoBDTValFinalPoissonUCM = abs(dataDNoBDTValFinalPoissonUC[0]-dataDNoBDTVal)

print("A")
print("Signal",'%.3f' % signalANoBDTVal,"+/-",'%.3f' % sqrt(signalANoBDTValUC),"\t\tN",MCCountAr[0][3][0])
print("Background",'%.3f' % backgroundANoBDTVal,"+/-",'%.3f' % sqrt(backgroundANoBDTValUC),"\tN",MCCountAr[1][3][0])
print("Data",dataANoBDTVal,"+",'%.3f' % (dataANoBDTValFinalPoissonUCP),"-",'%.3f' % (dataANoBDTValFinalPoissonUCM))

print("B")
print("Signal",'%.3f' % signalBNoBDTVal,"+/-",'%.3f' % sqrt(signalBNoBDTValUC),"\t\tN",MCCountAr[0][3][1])
print("Background",'%.3f' % backgroundBNoBDTVal,"+/-",'%.3f' % sqrt(backgroundBNoBDTValUC),"\tN",MCCountAr[1][3][1])
print("Data",dataBNoBDTVal,"+",'%.3f' % (dataBNoBDTValFinalPoissonUCP),"-",'%.3f' % (dataBNoBDTValFinalPoissonUCM))

print("C")
print("Signal",'%.3f' % signalCNoBDTVal,"+/-",'%.3f' % sqrt(signalCNoBDTValUC),"\t\tN",MCCountAr[0][3][2])
print("Background",'%.3f' % backgroundCNoBDTVal,"+/-",'%.3f' % sqrt(backgroundCNoBDTValUC),"\tN",MCCountAr[1][3][2])
print("Data",dataCNoBDTVal,"+",'%.3f' % (dataCNoBDTValFinalPoissonUCP),"-",'%.3f' % (dataCNoBDTValFinalPoissonUCM))

print("D")
print("Signal",'%.3f' % signalDNoBDTVal,"+/-",'%.3f' % sqrt(signalDNoBDTValUC),"\t\tN",MCCountAr[0][3][3])
print("Background",'%.3f' % backgroundDNoBDTVal,"+/-",'%.3f' % sqrt(backgroundDNoBDTValUC),"\tN",MCCountAr[1][3][3])
print("Data",dataDNoBDTVal,"+",'%.3f' % (dataDNoBDTValFinalPoissonUCP),"-",'%.3f' % (dataDNoBDTValFinalPoissonUCM))

print("MC A Pred:")
calcAPred(backgroundANoBDTVal,backgroundBNoBDTVal,backgroundCNoBDTVal,backgroundDNoBDTVal,sqrt(backgroundANoBDTValUC),sqrt(backgroundBNoBDTValUC),sqrt(backgroundCNoBDTValUC),sqrt(backgroundDNoBDTValUC))
print("Data A Pred:")
calcAPredWithPoisson(dataANoBDTVal,dataBNoBDTVal,dataCNoBDTVal,dataDNoBDTVal,dataANoBDTValFinalPoissonUCP,dataBNoBDTValFinalPoissonUCP,dataCNoBDTValFinalPoissonUCP,dataDNoBDTValFinalPoissonUCP,dataANoBDTValFinalPoissonUCM,dataBNoBDTValFinalPoissonUCM,dataCNoBDTValFinalPoissonUCM,dataDNoBDTValFinalPoissonUCM)

ABCDDataEtaIMNoBDTCan.cd()
makeNiceHistos(ABCDDataEtaIMNoBDTHist,"VBF Jet Eta Separation","VBF Jet IM",False)
ABCDDataEtaIMNoBDTHist.SetTitle("Data VBF Jet Eta Separation Vs VBF Jet IM for Failing BDT Cut")

ABCDDataEtaIMNoBDTHist.GetXaxis().CenterTitle()
ABCDDataEtaIMNoBDTHist.Draw("COLZ")
ABCDDataEtaIMNoBDTCan.Draw()
etaCutLine = TLine(ABCDEtaCut,0,ABCDEtaCut,2750)
etaCutLine.SetLineColor(2)
etaCutLine.SetLineWidth(4)
etaCutLine.SetLineStyle(9)
etaCutLine.Draw()
IMCutLine = TLine(0,ABCDIMCut,9,ABCDIMCut)
IMCutLine.SetLineColor(2)
IMCutLine.SetLineWidth(4)
IMCutLine.SetLineStyle(9)
IMCutLine.Draw()

ABCDDataEtaIMNoBDTCan.Update()
ABCDDataEtaIMNoBDTCan.SaveAs("dataInBDTFailABCD_EtaSepVsIM_AllYears_{0}_{1}.png".format(addStr,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))



print("")
print("")
print("BDT Pass eta/im ABCD D region validation")

dataDABDTPassValFinalUC = sqrt(dataDABDTPassVal)
dataDBBDTPassValFinalUC = sqrt(dataDBBDTPassVal)
dataDCBDTPassValFinalUC = sqrt(dataDCBDTPassVal)
dataDDBDTPassValFinalUC = sqrt(dataDDBDTPassVal)

dataDABDTPassValFinalPoissonUC = poisson_interval(dataDABDTPassVal,0.3173)
dataDBBDTPassValFinalPoissonUC = poisson_interval(dataDBBDTPassVal,0.3173)
dataDCBDTPassValFinalPoissonUC = poisson_interval(dataDCBDTPassVal,0.3173)
dataDDBDTPassValFinalPoissonUC = poisson_interval(dataDDBDTPassVal,0.3173)


dataDABDTPassValFinalPoissonUCP = dataDABDTPassValFinalPoissonUC[1]-dataDABDTPassVal
dataDABDTPassValFinalPoissonUCM = abs(dataDABDTPassValFinalPoissonUC[0]-dataDABDTPassVal)

dataDBBDTPassValFinalPoissonUCP = dataDBBDTPassValFinalPoissonUC[1]-dataDBBDTPassVal
dataDBBDTPassValFinalPoissonUCM = abs(dataDBBDTPassValFinalPoissonUC[0]-dataDBBDTPassVal)

dataDCBDTPassValFinalPoissonUCP = dataDCBDTPassValFinalPoissonUC[1]-dataDCBDTPassVal
dataDCBDTPassValFinalPoissonUCM = abs(dataDCBDTPassValFinalPoissonUC[0]-dataDCBDTPassVal)

dataDDBDTPassValFinalPoissonUCP = dataDDBDTPassValFinalPoissonUC[1]-dataDDBDTPassVal
dataDDBDTPassValFinalPoissonUCM = abs(dataDDBDTPassValFinalPoissonUC[0]-dataDDBDTPassVal)

print("DA")
print("Signal",'%.3f' % signalDABDTPassVal,"+/-",'%.3f' % sqrt(signalDABDTPassValUC),"\t\tN",MCCountAr[0][4][0])
print("Background",'%.3f' % backgroundDABDTPassVal,"+/-",'%.3f' % sqrt(backgroundDABDTPassValUC),"\tN",MCCountAr[1][4][0])
print("Data",dataDABDTPassVal,"+",'%.3f' % (dataDABDTPassValFinalPoissonUCP),"-",'%.3f' % (dataDABDTPassValFinalPoissonUCM))

print("DB")
print("Signal",'%.3f' % signalDBBDTPassVal,"+/-",'%.3f' % sqrt(signalDBBDTPassValUC),"\t\tN",MCCountAr[0][4][1])
print("Background",'%.3f' % backgroundDBBDTPassVal,"+/-",'%.3f' % sqrt(backgroundDBBDTPassValUC),"\tN",MCCountAr[1][4][1])
print("Data",dataDBBDTPassVal,"+",'%.3f' % (dataDBBDTPassValFinalPoissonUCP),"-",'%.3f' % (dataDBBDTPassValFinalPoissonUCM))

print("DC")
print("Signal",'%.3f' % signalDCBDTPassVal,"+/-",'%.3f' % sqrt(signalDCBDTPassValUC),"\t\tN",MCCountAr[0][4][2])
print("Background",'%.3f' % backgroundDCBDTPassVal,"+/-",'%.3f' % sqrt(backgroundDCBDTPassValUC),"\tN",MCCountAr[1][4][2])
print("Data",dataDCBDTPassVal,"+",'%.3f' % (dataDCBDTPassValFinalPoissonUCP),"-",'%.3f' % (dataDCBDTPassValFinalPoissonUCM))

print("DD")
print("Signal",'%.3f' % signalDDBDTPassVal,"+/-",'%.3f' % sqrt(signalDDBDTPassValUC),"\t\tN",MCCountAr[0][4][3])
print("Background",'%.3f' % backgroundDDBDTPassVal,"+/-",'%.3f' % sqrt(backgroundDDBDTPassValUC),"\tN",MCCountAr[1][4][3])
print("Data",dataDDBDTPassVal,"+",'%.3f' % (dataDDBDTPassValFinalPoissonUCP),"-",'%.3f' % (dataDDBDTPassValFinalPoissonUCM))

print("MC DA Pred:")
calcAPred(backgroundDABDTPassVal,backgroundDBBDTPassVal,backgroundDCBDTPassVal,backgroundDDBDTPassVal,sqrt(backgroundDABDTPassValUC),sqrt(backgroundDBBDTPassValUC),sqrt(backgroundDCBDTPassValUC),sqrt(backgroundDDBDTPassValUC))
print("Data DA Pred:")
calcAPredWithPoisson(dataDABDTPassVal,dataDBBDTPassVal,dataDCBDTPassVal,dataDDBDTPassVal,dataDABDTPassValFinalPoissonUCP,dataDBBDTPassValFinalPoissonUCP,dataDCBDTPassValFinalPoissonUCP,dataDDBDTPassValFinalPoissonUCP,dataDABDTPassValFinalPoissonUCM,dataDBBDTPassValFinalPoissonUCM,dataDCBDTPassValFinalPoissonUCM,dataDDBDTPassValFinalPoissonUCM)

DRegionDataEtaIMBDTPassCan.cd()
makeNiceHistos(DRegionDataEtaIMBDTPassHist,"VBF Jet Eta Separation","VBF Jet IM",False)
DRegionDataEtaIMBDTPassHist.SetTitle("Data in D Region, VBF Jet Eta Separation Vs VBF Jet IM for BDT Pass")

DRegionDataEtaIMBDTPassHist.GetXaxis().CenterTitle()
DRegionDataEtaIMBDTPassHist.Draw("COLZ")
DRegionDataEtaIMBDTPassCan.Draw()
etaCutLine = TLine(3*ABCDEtaCut/4,0,3*ABCDEtaCut/4,ABCDIMCut)
etaCutLine.SetLineColor(2)
etaCutLine.SetLineWidth(4)
etaCutLine.SetLineStyle(9)
etaCutLine.Draw()
IMCutLine = TLine(ABCDEtaCut/2,ABCDIMCut/2,ABCDEtaCut,ABCDIMCut/2)
IMCutLine.SetLineColor(2)
IMCutLine.SetLineWidth(4)
IMCutLine.SetLineStyle(9)
IMCutLine.Draw()

DRegionDataEtaIMBDTPassCan.Update()
DRegionDataEtaIMBDTPassCan.SaveAs("dataInBDTPassDRegion_EtaSepVsIM_AllYears_{0}_{1}.png".format(addStr,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))




print("")
print("")
print("ABCD D region validation, no cuts after selection")

dataDANoCutsValFinalUC = sqrt(dataDANoCutsVal)
dataDBNoCutsValFinalUC = sqrt(dataDBNoCutsVal)
dataDCNoCutsValFinalUC = sqrt(dataDCNoCutsVal)
dataDDNoCutsValFinalUC = sqrt(dataDDNoCutsVal)

dataDANoCutsValFinalPoissonUC = poisson_interval(dataDANoCutsVal,0.3173)
dataDBNoCutsValFinalPoissonUC = poisson_interval(dataDBNoCutsVal,0.3173)
dataDCNoCutsValFinalPoissonUC = poisson_interval(dataDCNoCutsVal,0.3173)
dataDDNoCutsValFinalPoissonUC = poisson_interval(dataDDNoCutsVal,0.3173)

dataDANoCutsValFinalPoissonUCP = dataDANoCutsValFinalPoissonUC[1]-dataDANoCutsVal
dataDANoCutsValFinalPoissonUCM = abs(dataDANoCutsValFinalPoissonUC[0]-dataDANoCutsVal)

dataDBNoCutsValFinalPoissonUCP = dataDBNoCutsValFinalPoissonUC[1]-dataDBNoCutsVal
dataDBNoCutsValFinalPoissonUCM = abs(dataDBNoCutsValFinalPoissonUC[0]-dataDBNoCutsVal)

dataDCNoCutsValFinalPoissonUCP = dataDCNoCutsValFinalPoissonUC[1]-dataDCNoCutsVal
dataDCNoCutsValFinalPoissonUCM = abs(dataDCNoCutsValFinalPoissonUC[0]-dataDCNoCutsVal)

dataDDNoCutsValFinalPoissonUCP = dataDDNoCutsValFinalPoissonUC[1]-dataDDNoCutsVal
dataDDNoCutsValFinalPoissonUCM = abs(dataDDNoCutsValFinalPoissonUC[0]-dataDDNoCutsVal)

print("DA")
print("Signal",'%.3f' % signalDANoCutsVal,"+/-",'%.3f' % sqrt(signalDANoCutsValUC),"\t\tN",MCCountAr[0][5][0])
print("Background",'%.3f' % backgroundDANoCutsVal,"+/-",'%.3f' % sqrt(backgroundDANoCutsValUC),"\tN",MCCountAr[1][5][0])
print("Data",dataDANoCutsVal,"+",'%.3f' % (dataDANoCutsValFinalPoissonUCP),"-",'%.3f' % (dataDANoCutsValFinalPoissonUCM))

print("DB")
print("Signal",'%.3f' % signalDBNoCutsVal,"+/-",'%.3f' % sqrt(signalDBNoCutsValUC),"\t\tN",MCCountAr[0][5][1])
print("Background",'%.3f' % backgroundDBNoCutsVal,"+/-",'%.3f' % sqrt(backgroundDBNoCutsValUC),"\tN",MCCountAr[1][5][1])
print("Data",dataDBNoCutsVal,"+",'%.3f' % (dataDBNoCutsValFinalPoissonUCP),"-",'%.3f' % (dataDBNoCutsValFinalPoissonUCM))

print("DC")
print("Signal",'%.3f' % signalDCNoCutsVal,"+/-",'%.3f' % sqrt(signalDCNoCutsValUC),"\t\tN",MCCountAr[0][5][2])
print("Background",'%.3f' % backgroundDCNoCutsVal,"+/-",'%.3f' % sqrt(backgroundDCNoCutsValUC),"\tN",MCCountAr[1][5][2])
print("Data",dataDCNoCutsVal,"+",'%.3f' % (dataDCNoCutsValFinalPoissonUCP),"-",'%.3f' % (dataDCNoCutsValFinalPoissonUCM))

print("DD")
print("Signal",'%.3f' % signalDDNoCutsVal,"+/-",'%.3f' % sqrt(signalDDNoCutsValUC),"\t\tN",MCCountAr[0][5][3])
print("Background",'%.3f' % backgroundDDNoCutsVal,"+/-",'%.3f' % sqrt(backgroundDDNoCutsValUC),"\tN",MCCountAr[1][5][3])
print("Data",dataDDNoCutsVal,"+",'%.3f' % (dataDDNoCutsValFinalPoissonUCP),"-",'%.3f' % (dataDDNoCutsValFinalPoissonUCM))

print("MC DA Pred:")
calcAPred(backgroundDANoCutsVal,backgroundDBNoCutsVal,backgroundDCNoCutsVal,backgroundDDNoCutsVal,sqrt(backgroundDANoCutsValUC),sqrt(backgroundDBNoCutsValUC),sqrt(backgroundDCNoCutsValUC),sqrt(backgroundDDNoCutsValUC))
print("Data DA Pred:")
calcAPredWithPoisson(dataDANoCutsVal,dataDBNoCutsVal,dataDCNoCutsVal,dataDDNoCutsVal,dataDANoCutsValFinalPoissonUCP,dataDBNoCutsValFinalPoissonUCP,dataDCNoCutsValFinalPoissonUCP,dataDDNoCutsValFinalPoissonUCP,dataDANoCutsValFinalPoissonUCM,dataDBNoCutsValFinalPoissonUCM,dataDCNoCutsValFinalPoissonUCM,dataDDNoCutsValFinalPoissonUCM)


DRegionNoCutsDataEtaCan.cd()
makeNiceHistos(DRegionNoCutsDataEtaHist,"BDT Value","VBF Jet Eta Separation",False)
DRegionNoCutsDataEtaHist.SetTitle("Data in D Region Without Cuts, BDT Vs VBF Jet Eta Separation")

DRegionNoCutsDataEtaHist.GetXaxis().CenterTitle()
DRegionNoCutsDataEtaHist.Draw("COLZ")
DRegionNoCutsDataEtaCan.Draw()
bdtCutLine = TLine(ABCDBDTCut/2,ABCDEtaCut/2,ABCDBDTCut/2,ABCDEtaCut)
bdtCutLine.SetLineColor(2)
bdtCutLine.SetLineWidth(4)
bdtCutLine.SetLineStyle(9)
bdtCutLine.Draw()
etaCutLine = TLine(0,3*ABCDEtaCut/4,ABCDBDTCut,3*ABCDEtaCut/4)
etaCutLine.SetLineColor(2)
etaCutLine.SetLineWidth(4)
etaCutLine.SetLineStyle(9)
etaCutLine.Draw()
DRegionNoCutsDataEtaCan.Update()
DRegionNoCutsDataEtaCan.SaveAs("dataInDRegionNoCuts_BDTVsVBFEta_AllYears_{0}_{1}.png".format(addStr,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))


DRegionNoCutsDataIMCan.cd()
makeNiceHistos(DRegionNoCutsDataIMHist,"BDT Value","VBF Jet IM",False)
DRegionNoCutsDataIMHist.SetTitle("Data in D Region Without Cuts, BDT Vs VBF Jet IM")

DRegionNoCutsDataIMHist.GetXaxis().CenterTitle()
DRegionNoCutsDataIMHist.Draw("COLZ")
DRegionNoCutsDataIMCan.Draw()
bdtCutLine = TLine(ABCDBDTCut/2,0,ABCDBDTCut/2,ABCDIMCut)
bdtCutLine.SetLineColor(2)
bdtCutLine.SetLineWidth(4)
bdtCutLine.SetLineStyle(9)
bdtCutLine.Draw()
IMCutLine = TLine(0,ABCDIMCut/2,ABCDBDTCut,ABCDIMCut/2)
IMCutLine.SetLineColor(2)
IMCutLine.SetLineWidth(4)
IMCutLine.SetLineStyle(9)
IMCutLine.Draw()
DRegionNoCutsDataIMCan.Update()
DRegionNoCutsDataIMCan.SaveAs("dataInDRegionNoCuts_BDTVsVBFIM_AllYears_{0}_{1}.png".format(addStr,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))



print("")
print("")
print("ABCD D region validation, After Btag and Lepton IM Cuts")

dataDAPreFJIMCutsValFinalUC = sqrt(dataDAPreFJIMCutsVal)
dataDBPreFJIMCutsValFinalUC = sqrt(dataDBPreFJIMCutsVal)
dataDCPreFJIMCutsValFinalUC = sqrt(dataDCPreFJIMCutsVal)
dataDDPreFJIMCutsValFinalUC = sqrt(dataDDPreFJIMCutsVal)

dataDAPreFJIMCutsValFinalPoissonUC = poisson_interval(dataDAPreFJIMCutsVal,0.3173)
dataDBPreFJIMCutsValFinalPoissonUC = poisson_interval(dataDBPreFJIMCutsVal,0.3173)
dataDCPreFJIMCutsValFinalPoissonUC = poisson_interval(dataDCPreFJIMCutsVal,0.3173)
dataDDPreFJIMCutsValFinalPoissonUC = poisson_interval(dataDDPreFJIMCutsVal,0.3173)

dataDAPreFJIMCutsValFinalPoissonUCP = dataDAPreFJIMCutsValFinalPoissonUC[1]-dataDAPreFJIMCutsVal
dataDAPreFJIMCutsValFinalPoissonUCM = abs(dataDAPreFJIMCutsValFinalPoissonUC[0]-dataDAPreFJIMCutsVal)

dataDBPreFJIMCutsValFinalPoissonUCP = dataDBPreFJIMCutsValFinalPoissonUC[1]-dataDBPreFJIMCutsVal
dataDBPreFJIMCutsValFinalPoissonUCM = abs(dataDBPreFJIMCutsValFinalPoissonUC[0]-dataDBPreFJIMCutsVal)

dataDCPreFJIMCutsValFinalPoissonUCP = dataDCPreFJIMCutsValFinalPoissonUC[1]-dataDCPreFJIMCutsVal
dataDCPreFJIMCutsValFinalPoissonUCM = abs(dataDCPreFJIMCutsValFinalPoissonUC[0]-dataDCPreFJIMCutsVal)

dataDDPreFJIMCutsValFinalPoissonUCP = dataDDPreFJIMCutsValFinalPoissonUC[1]-dataDDPreFJIMCutsVal
dataDDPreFJIMCutsValFinalPoissonUCM = abs(dataDDPreFJIMCutsValFinalPoissonUC[0]-dataDDPreFJIMCutsVal)

print("DA")
print("Signal",'%.3f' % signalDAPreFJIMCutsVal,"+/-",'%.3f' % sqrt(signalDAPreFJIMCutsValUC),"\t\tN",MCCountAr[0][6][0])
print("Background",'%.3f' % backgroundDAPreFJIMCutsVal,"+/-",'%.3f' % sqrt(backgroundDAPreFJIMCutsValUC),"\tN",MCCountAr[1][6][0])
print("Data",dataDAPreFJIMCutsVal,"+",'%.3f' % (dataDAPreFJIMCutsValFinalPoissonUCP),"-",'%.3f' % (dataDAPreFJIMCutsValFinalPoissonUCM))

print("DB")
print("Signal",'%.3f' % signalDBPreFJIMCutsVal,"+/-",'%.3f' % sqrt(signalDBPreFJIMCutsValUC),"\t\tN",MCCountAr[0][6][1])
print("Background",'%.3f' % backgroundDBPreFJIMCutsVal,"+/-",'%.3f' % sqrt(backgroundDBPreFJIMCutsValUC),"\tN",MCCountAr[1][6][1])
print("Data",dataDBPreFJIMCutsVal,"+",'%.3f' % (dataDBPreFJIMCutsValFinalPoissonUCP),"-",'%.3f' % (dataDBPreFJIMCutsValFinalPoissonUCM))

print("DC")
print("Signal",'%.3f' % signalDCPreFJIMCutsVal,"+/-",'%.3f' % sqrt(signalDCPreFJIMCutsValUC),"\t\tN",MCCountAr[0][6][2])
print("Background",'%.3f' % backgroundDCPreFJIMCutsVal,"+/-",'%.3f' % sqrt(backgroundDCPreFJIMCutsValUC),"\tN",MCCountAr[1][6][2])
print("Data",dataDCPreFJIMCutsVal,"+",'%.3f' % (dataDCPreFJIMCutsValFinalPoissonUCP),"-",'%.3f' % (dataDCPreFJIMCutsValFinalPoissonUCM))

print("DD")
print("Signal",'%.3f' % signalDDPreFJIMCutsVal,"+/-",'%.3f' % sqrt(signalDDPreFJIMCutsValUC),"\t\tN",MCCountAr[0][6][3])
print("Background",'%.3f' % backgroundDDPreFJIMCutsVal,"+/-",'%.3f' % sqrt(backgroundDDPreFJIMCutsValUC),"\tN",MCCountAr[1][6][3])
print("Data",dataDDPreFJIMCutsVal,"+",'%.3f' % (dataDDPreFJIMCutsValFinalPoissonUCP),"-",'%.3f' % (dataDDPreFJIMCutsValFinalPoissonUCM))

print("MC DA Pred:")
calcAPred(backgroundDAPreFJIMCutsVal,backgroundDBPreFJIMCutsVal,backgroundDCPreFJIMCutsVal,backgroundDDPreFJIMCutsVal,sqrt(backgroundDAPreFJIMCutsValUC),sqrt(backgroundDBPreFJIMCutsValUC),sqrt(backgroundDCPreFJIMCutsValUC),sqrt(backgroundDDPreFJIMCutsValUC))
print("Data DA Pred:")
calcAPredWithPoisson(dataDAPreFJIMCutsVal,dataDBPreFJIMCutsVal,dataDCPreFJIMCutsVal,dataDDPreFJIMCutsVal,dataDAPreFJIMCutsValFinalPoissonUCP,dataDBPreFJIMCutsValFinalPoissonUCP,dataDCPreFJIMCutsValFinalPoissonUCP,dataDDPreFJIMCutsValFinalPoissonUCP,dataDAPreFJIMCutsValFinalPoissonUCM,dataDBPreFJIMCutsValFinalPoissonUCM,dataDCPreFJIMCutsValFinalPoissonUCM,dataDDPreFJIMCutsValFinalPoissonUCM)


DRegionPreFJIMCutsDataEtaCan.cd()
makeNiceHistos(DRegionPreFJIMCutsDataEtaHist,"BDT Value","VBF Jet Eta Separation",False)
DRegionPreFJIMCutsDataEtaHist.SetTitle("Data in D Region Before FJ IM Cuts, BDT Vs VBF Jet Eta Separation")

DRegionPreFJIMCutsDataEtaHist.GetXaxis().CenterTitle()
DRegionPreFJIMCutsDataEtaHist.Draw("COLZ")
DRegionPreFJIMCutsDataEtaCan.Draw()
bdtCutLine = TLine(ABCDBDTCut/2,ABCDEtaCut/2,ABCDBDTCut/2,ABCDEtaCut)
bdtCutLine.SetLineColor(2)
bdtCutLine.SetLineWidth(4)
bdtCutLine.SetLineStyle(9)
bdtCutLine.Draw()
etaCutLine = TLine(0,3*ABCDEtaCut/4,ABCDBDTCut,3*ABCDEtaCut/4)
etaCutLine.SetLineColor(2)
etaCutLine.SetLineWidth(4)
etaCutLine.SetLineStyle(9)
etaCutLine.Draw()
DRegionPreFJIMCutsDataEtaCan.Update()
DRegionPreFJIMCutsDataEtaCan.SaveAs("dataInDRegionPreFJIMCuts_BDTVsVBFEta_AllYears_{0}_{1}.png".format(addStr,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))


DRegionPreFJIMCutsDataIMCan.cd()
makeNiceHistos(DRegionPreFJIMCutsDataIMHist,"BDT Value","VBF Jet IM",False)
DRegionPreFJIMCutsDataIMHist.SetTitle("Data in D Region Before FJ IM Cuts, BDT Vs VBF Jet IM")

DRegionPreFJIMCutsDataIMHist.GetXaxis().CenterTitle()
DRegionPreFJIMCutsDataIMHist.Draw("COLZ")
DRegionPreFJIMCutsDataIMCan.Draw()
bdtCutLine = TLine(ABCDBDTCut/2,0,ABCDBDTCut/2,ABCDIMCut)
bdtCutLine.SetLineColor(2)
bdtCutLine.SetLineWidth(4)
bdtCutLine.SetLineStyle(9)
bdtCutLine.Draw()
IMCutLine = TLine(0,ABCDIMCut/2,ABCDBDTCut,ABCDIMCut/2)
IMCutLine.SetLineColor(2)
IMCutLine.SetLineWidth(4)
IMCutLine.SetLineStyle(9)
IMCutLine.Draw()
DRegionPreFJIMCutsDataIMCan.Update()
DRegionPreFJIMCutsDataIMCan.SaveAs("dataInDRegionPreFJIMCuts_BDTVsVBFIM_AllYears_{0}_{1}.png".format(addStr,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))

"""


