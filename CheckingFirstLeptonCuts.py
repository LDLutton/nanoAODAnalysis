import ROOT as r
#from ROOT import TFile, TChain, gDirectory, TApplication, TMath, Math, TMinuit, TROOT, TSystem, TTree, TVector2
#from ROOT import TH1F, TCanvas, TF1, TGraph, TGraphErrors, TLegend, TLine, TPaveText, TStyle
#from ROOT import TH2D, TH2F
from math import sqrt,pi
from fileLists import MGEFTAr
from fileLists import MGSMAr
from fileLists import ttHToBBBackgroundAr
import time as time

def DrawPlot(plot,name,saveName,normalizeOrNot):
    c1 = TCanvas("c1","c1",3600,2400)

    plot.SetFillColorAlpha(30,0.35)

    plot.Draw("hist")
    c1.SaveAs((name+"{0}.png".format(saveName)))
    plot.Write(name)

MGSM = True
MGEFT = False
ttHToBBBackground = False

fileAr = []

if MGEFT:
    saveName = "pphzzjjQCD0SMHLOOP0NPE1NPcHWE1QEDE5ResMasAllVer100Ev_0p999cHW100GeVIMJetCut"
    for fileName in MGEFTAr:
        fileAr.append("/scratch365/dlutton/NanoAODFiles/pphzzjjQCD0SMHLOOP0NPE1NPcHWE1QEDE5ResMasAllVer100Ev_0p999cHW100GeVIMJetCut/"+fileName)
elif MGSM:
    saveName = "pphzzjjQCD0SMHLOOP0QEDE5NPE0ResMasAllVer100Ev_0p999cHW100GeVIMJetCut"
    for fileName in MGSMAr:
        fileAr.append("/scratch365/dlutton/NanoAODFiles/pphzzjjQCD0SMHLOOP0QEDE5NPE0ResMasAllVer100Ev_0p999cHW100GeVIMJetCut/"+fileName)
elif ttHToBBBackground:
    saveName = "ttHToBBBackground"
    for fileName in ttHToBBBackgroundAr:
        fileAr.append(fileName)

#Gets the number of electrons and muons per event straight from the nanoaod
h_nElectron   = r.TH1F("h_nElectron","h_nElectron", 6, 0, 6)
h_nMuon   = r.TH1F("h_nMuon","h_nMuon", 9, 0, 9)
#tmpfile = r.TFile.Open("unweighted_eventspphzzjjQCD0SMHLOOP0NPE1NPcHWE1QEDE5ResMasAllVer100Ev10080Seed_0p999cHW100GeVIMJetCut_200.root")

#Counts the number of electron or muon pairs per event
numElecPairsHist = r.TH1I("numElecPairsHist","numElecPairsHist",10,0,10)
numMuonPairsHist = r.TH1I("numMuonPairsHist","numMuonPairsHist",10,0,10)
#plots the number of electron pairs vs the number of muon pairs
numMuonElecPairs2DHist = r.TH2I("numMuonElecPairs2DHist","numMuonElecPairs2DHist",10,0,10,10,0,10)
#Plots the number of electrons and muon candidates per event. the negative range is used for positrons and anti-muons
numElecHist = r.TH1I("numElecHist","numElecHist",20,-10,10)
numMuonHist = r.TH1I("numMuonHist","numMuonHist",20,-10,10)
#Plots the number of electron candidates vs the number of muon candidates. here there is no distinction between particle and anti-particle
numMuonElecHist = r.TH2I("numMuonElecHist","numMuonElecHist",10,0,10,10,0,10)
#Plots the number of pairs, electron or muon, per event. If >= 2, then it passes the first cut
totalPairHist = r.TH1I("totalPairHist","totalPairHist",15,0,15)
#Counters for whether or not electron or muon pairs exist, and then whether or not the event passed the first cut
elecPairExistsCtr = 0
muonPairExistsCtr = 0
passedCutsCtr = 0
for k,fileName in enumerate(fileAr):
    #if evCount > 450:
    #    break
    #Open the file, get the Events tree
    tmpfile = TFile.Open(fileName)
    mytree = tmpfile.Events
    for ev in mytree:
        h_nElectron.Fill(ev.nElectron)
        h_nMuon.Fill(ev.nMuon)
        #print("test0")
        negElecCtr = 0
        posElecCtr = 0
        negMuonCtr = 0
        posMuonCtr = 0
        for elecItr in range(ev.nElectron):
            #print("test01",ev,elecItr)
            if ev.Electron_pt[elecItr] > 7 and ev.Electron_eta[elecItr] < 2.5 and ev.Electron_eta[elecItr] > -2.5:
                if ev.Electron_pdgId[elecItr] < 0:
                    negElecCtr += 1
                else:
                    posElecCtr += 1
        for muonItr in range(ev.nMuon):
            if ev.Muon_pt[muonItr] > 7 and ev.Muon_eta[muonItr] < 2.5 and ev.Muon_eta[muonItr] > -2.5:
                if ev.Muon_pdgId[muonItr] < 0:
                    negMuonCtr += 1
                else:
                    posMuonCtr += 1
        #Fill elec/muon ctr hists
        numElecHist.Fill(-negElecCtr)
        numElecHist.Fill(posElecCtr)
        numMuonHist.Fill(-negMuonCtr)
        numMuonHist.Fill(posMuonCtr)
        numMuonElecHist.Fill(negElecCtr+posElecCtr,negMuonCtr+posMuonCtr)
        #Fill elec/muon pair hists
        #print("test")
        elecPairCtr = min(negElecCtr,posElecCtr)
        muonPairCtr = min(negMuonCtr,posMuonCtr)
        #print("test2")
        numElecPairsHist.Fill(elecPairCtr)
        numMuonPairsHist.Fill(muonPairCtr)
        numMuonElecPairs2DHist.Fill(elecPairCtr,muonPairCtr)
        #print("test3")
        lepCtr = elecPairCtr + muonPairCtr
        totalPairHist.Fill(lepCtr)
        #print("test4")
        if elecPairCtr > 0:
            elecPairExistsCtr += 1
        #print("test5")
        if muonPairCtr > 0:
            muonPairExistsCtr += 1
        #print("test6")
        if lepCtr >= 2:
            passedCutsCtr += 1
        #print("test7")

print("elecPairExistsCtr","muonPairExistsCtr",elecPairExistsCtr,muonPairExistsCtr)
print("passedCutsCtr",passedCutsCtr)

outFile = r.TFile("histosFromNanoAODFirstLeptonCuts{0}.root".format(saveName),"recreate")


#h_nElectron.Draw("hist")
DrawPlot(h_nElectron, "h_nElectron_PreLepCuts_",saveName,True)


#_nMuon.Draw("hist")
DrawPlot(h_nMuon, "h_nMuon_PreLepCuts_",saveName,True)

#numElecPairsHist.Draw("hist")
DrawPlot(numElecPairsHist, "numElecPairsHist_",saveName,True)

#numMuonPairsHist.Draw("hist")
DrawPlot(numMuonPairsHist, "numMuonPairsHist_",saveName,True)

#numMuonElecPairs2DHist.Draw("COLZ")
DrawPlot(numMuonElecPairs2DHist, "numMuonElecPairs2DHist_",saveName,True)

#numElecHist.Draw("hist")
DrawPlot(numElecHist, "numElecHist_",saveName,True)

#numMuonHist.Draw("hist")
DrawPlot(numMuonHist, "numMuonHist_",saveName,True)

#numMuonElecHist.Draw("COLZ")
DrawPlot(numMuonElecHist, "numMuonElecHist_",saveName,True)

#totalPairHist.Draw("hist")
DrawPlot(totalPairHist, "totalPairHist_",saveName,True)
