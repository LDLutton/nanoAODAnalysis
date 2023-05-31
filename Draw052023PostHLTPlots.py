import datetime
from ROOT import TFile, TChain, gDirectory, TApplication, TMath, Math, TMinuit, TROOT, TSystem, TTree, TVector2, THStack
# You probably also want to import TH1D and TCanvas,
# unless you're not making any histograms.
from ROOT import TH1F, TH1D, TF1, TGraph, TGraphErrors, TLegend, TLine, TPaveText, TStyle,TMultiGraph
from ROOT import TH2D, TH2F,TCanvas,gStyle
from FunctionsFor082022AnalysisPlots import *
from math import sqrt
from array import array


#Copied from Draw082022AnalysisPlots.py


today = datetime.datetime.today()



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

def makeStackedPlotsWithSignal(histCan,histStack,histLeg,histSaveStr,histSum,histTitle,histSignal):
    histStack.SetTitle(histTitle)
    histStack.Draw("hist")
    histStack.GetYaxis().SetTitle("Events")
    histStack.GetYaxis().CenterTitle()
    histStack.GetYaxis().SetTitleSize(0.068)
    histStack.GetYaxis().SetTitleOffset(0.6)
    histSignal.Draw("SAME")
    histLeg.Draw()
    histCan.Draw()
    histCan.cd()
    histCan.Update()
    histCan.Draw()
    histCan.SaveAs("{0}Stack_AllYears_{1}.png".format(histSaveStr,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))
    histCan.cd()
    histCan.SetLogy()
    histCan.cd()
    histCan.Update()
    histCan.Draw()
    histCan.SaveAs("{0}StackLogPlot_AllYears_{1}.png".format(histSaveStr,"{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))









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





def calcAPred(A,B,C,D,AW,BW,CW,DW,AWUC,BWUC,CWUC,DWUC):
    print("A",A,"B",B,"C",C,"D",D)

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





    if B != 0:
        print("A/B",'%.3f' % (A/B))
    if D != 0:
        print("C/D",'%.3f' % (C/D))
        APred = C*B/D
    else:
        APred = 0



    print("APred",'%.3f' % APred)

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

signalOnly = False
backgroundOnly = False
onlyLookingAtBool = False
allIncludingData = False
dataOnly = False
passFailPlotsBool = False

doSplitUpDataMCPlots = False

QCDBool = False


C2V2XS = 0.00106719 #ZZH C2V=2 XS
C2V2WZHXS = 0.00155167 #WZH C2V=2 XS

C2VXSAr = [C2V2XS,C2V2WZHXS]
C2V2TotWeightByYearAr = [99000,98000,98000,99000]
C2V2WZHTotWeightByYearAr = [99999,99993,99995,99993] #change this
C2VTotWeightAr = [C2V2TotWeightByYearAr,C2V2WZHTotWeightByYearAr]


Run2LumiByYearAr = [59830,41480,16810,19520]

toSumHistsSTAr = [13,14,15,25,26]

toSumHistsVVVAr = [37,38,39,51]

toSumHistsVVAr = [17,18,19]

toSumHistsTTbbAr = [20,21,22]
toSumHistsQCDAr = [3,4,5,6,7,8,9,10,11,12]



datasetAr = ["ttHToBB","ttZJets","DY", #2
            "QCDPT170to300","QCDPT300to470","QCDPT470to600","QCDPT600to800","QCDPT800to1000","QCDPT1000to1400", #8
            "QCDPT1400to1800","QCDPT1800to2400","QCDPT2400to3200","QCDPT3200toInf", #12
            "ST_s_Channel","ST_t_ChannelAntiTop","ST_t_ChannelTop", #15
            "TTJets",
            "WW","WZ","ZZ",
            "TTbb_TTTo2L2Nu","TTbb_TTToHadronic","TTbb_TTToSemiLeptonic",
            "ttWJets",
            "DYM10To50",
            "ST_tW_antitop","ST_tW_top", #26
            "EWKWMinus2Jets_WToLNu","EWKWPlus2Jets_WToLNu",
            "EWKWMinus2Jets_WToQQ","EWKWPlus2Jets_WToQQ", #30
            "VHToNonbb",
            "WminusH_HToBB_WToLNu","WminusH_HToBB_WToQQ",
            "WplusH_HToBB_WToLNu","WplusH_HToBB_WToQQ",
            "WJetsToLNu", #36
            "WWW","WWZ","WZZ",
            "ZH_HToBB_ZToBB","ZH_HToBB_ZToLL","ZH_HToBB_ZToNuNu","ZH_HToBB_ZToQQ",
            "ggZH_HToBB_ZToBB","ggZH_HToBB_ZToLL","ggZH_HToBB_ZToNuNu","ggZH_HToBB_ZToQQ",
            "EWKZ2Jets_ZToLL","EWKZ2Jets_ZToNuNu","EWKZ2Jets_ZToQQ", #50
            "ZZZ"]

#datasetYearStrAr = ["","Y17","Y16","Y16APV"]
datasetYearStrAr = ["Y16APV","Y16","Y17",""]

datasetTypeAr = [2,3,4,
                15,16,17,18,19,20,
                21,22,23,24,
                9,10,11,
                5,
                13,14,12,
                8,6,7,
                50,
                51,
                52,53,
                54,56,
                55,57,
                58,
                59,60,
                61,62,
                63,
                64,65,66,
                75,67,76,68,
                77,69,78,70,
                71,72,73,
                74]

crossSectionAr = [0.5071*0.582,0.5407,6424,
103300,6826,552.6,156.6,26.32,7.5,
0.6479,0.08715,0.005242,0.0001349,
3.74,69.09,115.3,
722.8,
75.95,27.59,12.17,
2.9,5.5,4.7,
0.4611,
20490,
32.51,32.45,
32.05,39.13,
19.19,28.71,
2.605,
0.177,0.3675,
0.2832,0.589,
66680.0,
0.2158,0.1707,0.05709,
0.5612,0.07977,0.1573,0.5612,
0.04319,0.006185,0.01222,0.04319,
6.214,10.68,9.778,
0.01476]

totWeightAr = [[2315362.9999999995,2470819.7700000005,3919780.398000001,4843451.890000001],[17127762.0,14329445.0,31791133.0,32793821.0],[1545708040000.0,1220934300000.0,3322971118000.0,3323478039000.0],
[27885000.0,29758000.0,29491000.0,29478000.0],[54028000.0,55264000.0,55358000.0,57868000.0],[50782081.0,52408079.3,50475112.150000006,52448083.800000004],[61904000.0,64584000.0,66419000.0,66914000.0],[35459000.0,37698000.0,36890000.0,36830000.0],[19077000.0,19892000.0,19461000.0,19664000.0],
[11000000.0,10722000.0,10994000.0,10982000.0],[5262000.0,5236000.0,5168000.0,5491000.0],[2999000.0,2848000.0,2997000.0,2931000.0],[1000000.0,996000.0,1000000.0,1000000.0],
[19596255.0,19433136.53,48361399.0,68767088.0],[1983864428.0,1957283170.0,4462869700.0,6114949140.0],[5948133240.0,6703801811.0,13808002655.0,18955976000.0],
[188323895600.0,178352266900.0,497148414000.0,610815599000.0],
[15859132.4,15821146.729999997,15634113.2,15679125.299999999],[7934000.0,7584000.0,7889000.0,7940000.0],[1282000.0,1151000.0,2704470.0,3526000.0],
[6367619.0,7209373.0,15930875.0,21986500.0],[46015100.0,51913700.0,113736153.5,160749330.0],[57255440.0,61707077.0,153797770.0,233964864.0],
[14186419.0,14396001.0,27662128.0,27686858.0],
[1677278070000.0,1664772700000.0,3240932300000.0,3351537100000.0],
[74766330.0,83024122.0,184446275.0,251902108.0],[74624684.0,80821413.6,183284979.29999998,258137399.49999997],
[2248000.0,2202000.0,4077000.0,4479000.0],[2185000.0,2033000.0,3595000.0,4488000.0],
[4999000.0,4998130.0,7874000.0,9655000.0],[4943000.0,4998118.0,7994000.0,9991000.0],
[2561274.6000000006,1917609.33,5066307.699999999,7023767.399999999],
[456329.16,396666.2394000001,838429.8309999999,862915.6845000001],[1794191.0599999998,1836585.5289999996,2924795.0339999995,3676316.52],
[745714.035,630588.626,1379070.2299999997,1377078.4579999996],[2934336.9399999995,2910762.9379999996,4609323.54,5600077.85],
[4989518390000.0,4872963500000.0,4559894064000.0,5018114340000.0],
[1120296.68,897983.3620000002,2127101.264,2135751.129],[866227.1599999999,784714.14,1697048.0349999997,1572221.397],[308416.94,260326.46,565804.579,571468.7320000001],
[1448833.7057000003,1240904.3085000003,2663478.1038999995,2686414.836],[212477.136,176165.53599999993,367961.3039,389609.65400000004],[401141.5949,346164.48300000007,742376.6619999999,361453.3201],[3031836.7879999997,2574971.707000001,5523315.285000001,5611321.760000001],
[104596.24113999997,92902.46724999997,203165.06699999998,200515.39800000004],[14942.124299999996,13538.205100000001,28900.881299999994,30249.127000000008],[31340.952200000007,26758.943700000007,59040.78879999999,59566.16379999999],[116625.05099999998,99347.31699999997,215713.47199999998,212862.332],
[500000.0,453000.0,579000.0,1000000.0],[1450000.0,1500000.0,2976000.0,2969000.0],[4979000.0,4928082.0,8000000.0,9985000.0],
[78317.072,66938.7465,140629.42869999996,146027.43779999999]]



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
datasetYearStrAr = ["Y16APV","Y16","Y17",""]
datasetSignalYearStrAr = ["16APV","16","17",""]

datasetSignalAr = ["C2V2MCZZH","C2V2MCWZH"]



gStyle.SetOptStat(0)

genBackgroundFileString = "/scratch365/dlutton/HLTFilteredFiles/HLTTrimmedFilteredForAnalysis{0}{1}.root"
genSignalFileString = "/scratch365/dlutton/HLTFilteredFiles/HLTTrimmedFilteredForAnalysisSD{0}{1}Reweight_0.root"
fileSignalAr = []
fileBackgroundAr = []
for datasetInd,datasetStr in enumerate(datasetSignalAr):
    fileSignalAr.append([])
    for yearInd,yearStr in enumerate(datasetSignalYearStrAr):
        fileSignalAr[-1].append(genSignalFileString.format(datasetStr,yearStr))

for datasetInd,datasetStr in enumerate(datasetAr):
    fileBackgroundAr.append([])
    for yearInd,yearStr in enumerate(datasetYearStrAr):
        fileBackgroundAr[-1].append(genBackgroundFileString.format(datasetStr,yearStr))


print("Initializing hists")

signalHist = TH1D("signalHist","signalHist", 20,0,2000)

backgroundHistAr = [TH1D("backgroundHist{0}".format(datasetName),"backgroundHist{0}".format(datasetName), 20,0,2000) for datasetName in datasetAr]

########THStacks

backgroundHistStack = THStack("backgroundHistStack","background")

########THSum
backgroundHistSum = TH1D("backgroundHistSum","backgroundHistSum", 20,0,2000)

#ST Sum
backgroundHistSTSum = TH1D("backgroundHistSTSum","backgroundHistSTSum", 20,0,2000)

#VVV Sum
backgroundHistVVVSum = TH1D("backgroundHistVVVSum","backgroundHistVVVSum", 20,0,2000)

#VV Sum
backgroundHistVVSum = TH1D("backgroundHistVVSum","backgroundHistVVSum", 20,0,2000)


#TTbb Sum
backgroundHistTTbbSum = TH1D("backgroundHistTTbbSum","backgroundHistTTbbSum", 20,0,2000)

#QCD Sum
backgroundHistQCDSum = TH1D("backgroundHistQCDSum","backgroundHistQCDSum", 20,0,2000)




###########

skipCtr = 0
cutCtr = 0
evCtr = 0


##################MAIN LOOP##################
for k,fileA in enumerate(fileBackgroundAr):
    for i,fileStr in enumerate(fileA):
        tmpFile = TFile.Open(fileBackgroundAr[k][i])
        tmpTree = tmpFile.FilteredEventsTree
        print("Looping over {0}{1} events".format(datasetAr[k],datasetYearStrAr[i]))
        tmpWeightCoef = crossSectionAr[k]*Run2LumiByYearAr[i]/totWeightAr[k][i]
        #LOOP OVER EVENTS IN FILE k
        for j,ev in enumerate(tmpTree):
            if breakEvEarly and evCtr >= breakEvAt:
                break
            if evCtr % 100000 == 0:
                print("ev:",evCtr)
            tmpEvWeight = tmpWeightCoef*ev.genWeightL
            tmpnFJ = ev.nFatJetL
            for FJInd in range(tmpnFJ):
                tmpFJ_pt = ev.FatJet_ptL[FJInd]
                backgroundHistAr[k].Fill(tmpFJ_pt,tmpEvWeight)
            evCtr += 1
                
    

        

##################MAIN LOOP##################
for k,fileA in enumerate(fileSignalAr):
    for i,fileStr in enumerate(fileA):
        evInFileCtr = 0
        tmpFile = TFile.Open(fileSignalAr[k][i])
        tmpTree = tmpFile.FilteredEventsTree
        print("Looping over {0}{1} events".format(datasetSignalAr[k],datasetSignalYearStrAr[i]))
        tmpWeightCoef = C2VXSAr[k]*Run2LumiByYearAr[i]/C2VTotWeightAr[k][i]
        #LOOP OVER EVENTS IN FILE k
        for j,ev in enumerate(tmpTree):
            if breakEvEarly and evInFileCtr >= breakEvAt:
                break
            if evCtr % 100000 == 0:
                print("ev:",evCtr)
            tmpEvWeight = tmpWeightCoef*ev.genWeightL
            tmpnFJ = ev.nFatJetL
            for FJInd in range(tmpnFJ):
                tmpFJ_pt = ev.FatJet_ptL[FJInd]
                signalHist.Fill(tmpFJ_pt,tmpEvWeight)
            evInFileCtr += 1
            evCtr += 1
                
    

        
    
    
print("evCtr",evCtr,"skipCtr",skipCtr,"cutCtr",cutCtr)

##################END MAIN LOOP##################
print("Finished main loop")

maxVal = 0
minVal = 100000

###################BDT and IM and PN Hists###################

for datasetItr in range(len(datasetAr)):
    tmpMax = backgroundHistAr[datasetItr].GetMaximum()
    if tmpMax > maxVal:
        maxVal = tmpMax
    tmpMin = backgroundHistAr[datasetItr].GetMinimum()
    if tmpMin < minVal:
        minVal = tmpMin

tmpMax = signalHist.GetMaximum()
if tmpMax > maxVal:
    maxVal = tmpMax
tmpMin = signalHist.GetMinimum()
if tmpMin < minVal:
    minVal = tmpMin



print(minVal,maxVal)

if minVal <= 0:
    minVal = 1

print(minVal)

legAr = []
legAr.append(TLegend(.75,.4,.99,.99))
legAr[-1].SetTextSize(0.036)
legAr[-1].SetTextFont(42)

FJCan = TCanvas("FJCan","FJCan",3600,2400)

FJCan.cd()

makeNiceHistos(backgroundHistAr[0],"background Value","",False)
backgroundHistAr[0].SetLineWidth(4)
backgroundHistAr[0].SetLineColorAlpha(colorAr[0],1)

backgroundHistAr[0].GetYaxis().SetRangeUser(minVal-abs(minVal*0.1),maxVal+abs(maxVal*0.1))
backgroundHistAr[0].Draw()

legAr[-1].AddEntry(backgroundHistAr[0],datasetAr[0],"l")

for i,datasetName in enumerate(datasetAr[1:]):
    if backgroundHistAr[i+1].GetMaximum()== 0 and backgroundHistAr[i+1].GetMinimum()== 0:
        continue
    backgroundHistAr[i+1].SetLineWidth(4)
    backgroundHistAr[i+1].SetLineColorAlpha(colorAr[i+1],1.)
    backgroundHistAr[i+1].Draw("SAME")
    legAr[-1].AddEntry(backgroundHistAr[i+1],datasetAr[i+1],"l")

signalHist.SetLineWidth(4)
signalHist.SetLineColorAlpha(2,1.)
signalHist.Draw("SAME")
legAr[-1].AddEntry(signalHist,"C2V","l")

legAr[-1].Draw()
FJCan.Draw()
FJCan.SaveAs("FJPt_PostHLT_AllYears_{0}.png".format("{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))

FJCan.SetLogy()
FJCan.Draw()
FJCan.SaveAs("FJPt_PostHLT_LogPlot_AllYears_{0}.png".format("{0:02}".format(today.month)+"{0:02}".format(today.day)+"{0:04}".format(today.year)))


backgroundLeg = TLegend(.71,.55,.85,.999 )
backgroundLeg.SetTextSize(0.036)
backgroundLeg.SetTextFont(42)

for histItr in range(len(backgroundHistAr)):
    if not backgroundOnly:
        if histItr == 0:
            continue
    if backgroundHistAr[histItr].GetMaximum()== 0 and backgroundHistAr[histItr].GetMinimum()== 0:
        continue
    ######
    backgroundHistSum.Add(backgroundHistAr[histItr])
    backgroundHistAr[histItr].SetFillColorAlpha(colorAr[histItr],1)
    if histItr in toSumHistsSTAr:
        backgroundHistSTSum.Add(backgroundHistAr[histItr])
    elif histItr in toSumHistsVVVAr:
        backgroundHistVVVSum.Add(backgroundHistAr[histItr])
    elif histItr in toSumHistsVVAr:
        backgroundHistVVSum.Add(backgroundHistAr[histItr])
    elif histItr in toSumHistsTTbbAr:
        backgroundHistTTbbSum.Add(backgroundHistAr[histItr])
    elif histItr in toSumHistsQCDAr:
        backgroundHistQCDSum.Add(backgroundHistAr[histItr])
    else:
        backgroundLeg.AddEntry(backgroundHistAr[histItr],datasetAr[histItr],"f")
        backgroundHistStack.Add(backgroundHistAr[histItr])


    
backgroundHistSTSum.SetFillColorAlpha(16,1)
backgroundLeg.AddEntry(backgroundHistSTSum,"ST","f")
backgroundHistStack.Add(backgroundHistSTSum)

backgroundHistVVVSum.SetFillColorAlpha(46,1)
backgroundLeg.AddEntry(backgroundHistVVVSum,"VVV","f")
backgroundHistStack.Add(backgroundHistVVVSum)

backgroundHistVVSum.SetFillColorAlpha(41,1)
backgroundLeg.AddEntry(backgroundHistVVSum,"VV","f")
backgroundHistStack.Add(backgroundHistVVSum)

backgroundHistTTbbSum.SetFillColorAlpha(6,1)
backgroundLeg.AddEntry(backgroundHistTTbbSum,"TTbb","f")
backgroundHistStack.Add(backgroundHistTTbbSum)

backgroundHistQCDSum.SetFillColorAlpha(5,1)
backgroundLeg.AddEntry(backgroundHistQCDSum,"QCD","f")
backgroundHistStack.Add(backgroundHistQCDSum)

backgroundLeg.AddEntry(signalHist,"C2V","l")

FJSecondCan = TCanvas("FJSecondCan","FJSecondCan",3600,2400)
makeStackedPlotsWithSignal(FJSecondCan,backgroundHistStack,backgroundLeg,"AK8JetPt",backgroundHistSum,"AK8 Jet Pt",signalHist)
