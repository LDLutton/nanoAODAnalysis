from ROOT import TFile, TChain, gDirectory, TApplication, TMath, Math, TMinuit, TROOT, TSystem, TTree, TVector2
# You probably also want to import TH1D and TCanvas,
# unless you're not making any histograms.
from ROOT import TH1F, TCanvas, TF1, TGraph, TGraphErrors, TLegend, TLine, TPaveText, TStyle
from ROOT import TH2D, TH2F
from math import sqrt,pi
from fileLists import MGEFTAr
from fileLists import MGSMAr
from fileLists import ttHToBBBackgroundAr
import time as time

#To enable heavy printing for debug
debug = False

#withDipoleRecoil = True

MGSM = True
MGEFT = False
ttHToBBBackground = False

#For drawing and saving histograms
#Saves a png and, optionally, a pdf version
#Saves histogram to the currently active root file

def DrawPlot(plot,name,saveName,normalizeOrNot):
    if normalizeOrNot and plot.GetEntries() > 0:
        c1 = TCanvas("c1","c1",3600,2400)

        plot.SetFillColorAlpha(30,0.35)

        plot.Draw("hist")
        c1.SaveAs((name+"{0}.png".format(saveName)))
        plot.Write(name)
        plot.Scale(1.0 / plot.Integral())

        plot.Draw("hist")
        c1.SaveAs((name+"{0}Normalized.png".format(saveName)))
        #c1.SaveAs((name+"{0}.pdf".format(saveName)))
        plot.Write(name+"Normalized")
    else:
        print(name,"has no entries. Adding empty histograms")
        c1 = TCanvas()
        plot.Draw("hist")
        plot.Write(name)
        plot.Write(name+"Normalized")




#For calculating DeltaR for two particles from their respective etas and phis
def calcDeltaR(phi1,eta1,phi2,eta2):
    deta = eta1-eta2
    dphi = abs(phi1-phi2)
    if dphi > pi:
        dphi -= (2*pi)
    return sqrt((deta*deta)+(dphi*dphi))


# Open the file. Note that the name of your file outside this class
# will probably NOT be experiment.root.
print("start")
startt = time.time()
#Analyzer will run over all files put into fileAr
fileAr = []

if MGEFT:
    saveName = "pphzzjjQCD0SMHLOOP0NPE1NPcHWE1QEDE5ResMasAllVer100Ev_0p999cHW100GeVIMJetCut"
    h_LHEWeight      = TH1F("h_LHEWeight","h_LHEWeight",100,0.000262,0.000273)

    for fileName in MGEFTAr:
        fileAr.append("/scratch365/dlutton/NanoAODFiles/pphzzjjQCD0SMHLOOP0NPE1NPcHWE1QEDE5ResMasAllVer100Ev_0p999cHW100GeVIMJetCut/"+fileName)
elif MGSM:
    saveName = "pphzzjjQCD0SMHLOOP0QEDE5NPE0ResMasAllVer100Ev_0p999cHW100GeVIMJetCut"
    h_LHEWeight      = TH1F("h_LHEWeight","h_LHEWeight",100,8.0e-05,8.5e-05)
    for fileName in MGSMAr:
        fileAr.append("/scratch365/dlutton/NanoAODFiles/pphzzjjQCD0SMHLOOP0QEDE5NPE0ResMasAllVer100Ev_0p999cHW100GeVIMJetCut/"+fileName)
elif ttHToBBBackground:
    saveName = "ttHToBBBackground"
    h_LHEWeight      = TH1F("h_LHEWeight","h_LHEWeight",100,8.0e-05,8.5e-05) #Non-functional, just to keep the program from crashing
    crossSection = 0.6*0.584
    for fileName in ttHToBBBackgroundAr:
        fileAr.append(fileName)
    
if not ttHToBBBackground:
    crossSectionAvg = 0
    crossSectionCtr = 0

print("Making Histos/Defining variables.","time:",time.time()-startt)
#Defining Lepton cuts
ZMass = 91.1876
"""
elecCandEtaCut =  2.5          <
elecCandPTCut = 7              >
muonCandEtaCut =  2.4          <
muonCandPTCut = 5              >

firstZTrailingCut = 10         >
leptonZ2Cut = 12               >
firstZLeadingCut = 20          >
leptonInvMassCutLow = 60       >
fourLeptonInvMassCut = 100     >
leptonInvMassCutTwo = 12       >
leptonInvMassCutHigh = 120     <
"""


lepCutsAr = [2.5,7,2.4,5,10,12,20,60,100,12,120]
cutsLowAr  = [3.5,0,3.4,0,0,0,5,30,50,0,150]
cutsHighAr = [0.5,14,0.4,10,20,24,40,89,200,24,95]

#cutFloorAr = [0.5,0,0.4,0,0,0,5,30,50,0,95]
#cutCeilingAr = [3.5,14,3.4,10,20,24,40,89,200,24,150]
lessThanAr = [True,False,True,False,False,False,False,False,False,False,True]
splitUpIntoInt = 2
cutIncrementLowAr = [abs(lepCut-lepCutLow)/splitUpIntoInt for lepCut,lepCutLow in zip(lepCutsAr,cutsLowAr)]
cutIncrementHighAr = [abs(lepCut-lepCutHigh)/splitUpIntoInt for lepCut,lepCutHigh in zip(lepCutsAr,cutsHighAr)]


masterCutsLowAr = [[lepCutMid-(cutIncLow*splitUpItr) if not lessThanBool else lepCutMid+(cutIncLow*splitUpItr) for lepCutMid,cutIncLow,lessThanBool in zip(lepCutsAr,cutIncrementLowAr,lessThanAr)] for splitUpItr in range(2,0,-1)]
masterCutsHighAr = [[lepCutMid+(cutIncHigh*splitUpItr) if not lessThanBool else lepCutMid-(cutIncHigh*splitUpItr) for lepCutMid,cutIncHigh,lessThanBool in zip(lepCutsAr,cutIncrementHighAr,lessThanAr)] for splitUpItr in range(1,3)]
masterCutsAr = masterCutsLowAr+[lepCutsAr]+masterCutsHighAr
#counter Ars
masterCutsLen = len(masterCutsAr)
ifEnoughElecCandCount = [0]*masterCutsLen
ifEnoughMuonCandCount = [0]*masterCutsLen
ifZ1ElecPairCandCount = [0]*masterCutsLen
ifZ1MuonPairCandCount = [0]*masterCutsLen
ifZ2ElecPairCandCount = [0]*masterCutsLen
ifZ2MuonPairCandCount = [0]*masterCutsLen
passesIsoCutsCount    = [0]*masterCutsLen
passesSIPCutCount     = [0]*masterCutsLen
allCutPassCount       = [0]*masterCutsLen



#Initializing counter variables
evCount = 0


print("Going into file loop.","time:",time.time()-startt)
for k,fileName in enumerate(fileAr):
    #if evCount > 450:
    #    break
    #Open the file, get the Events tree
    tmpfile = TFile.Open(fileName)
    mytree = tmpfile.Events
    #Getting the cross section
    #For background it's precalculated
    if k % 10 == 0:
        print("Going into event loop for file {0}.".format(k),"time:",time.time()-startt)

    #EvLoop
    for ev in mytree:
        for l,cutSet in enumerate(masterCutsAr):
            #if evCount > 450:
            #    break
            if evCount % 1000 == 0:
                print("Event: "+str(evCount))
            #IndicesForLeptonPairs
            lepPairOneLeadInd = -1
            lepPairOneTrailingInd = -1
            #lepPairTwoLeadInd = 0
            #lepPairTwoTrailingInd = 0

            #For counters to not overcount

            ifEnoughElecCandBool = False
            ifEnoughMuonCandBool = False
            ifZ1ElecPairCandBool = False
            ifZ1MuonPairCandBool = False
            ifZ2ElecPairCandBool = False
            ifZ2MuonPairCandBool = False
            passesIsoCutsBool = False
            passesSIPCutBool = False
            allCutPassBool = False

            #Array for the Candidates for the first Z
            ZOneCandAr = []
            #number of electrons and muons and the sum
            tmpnElectron = ev.nElectron
            tmpnMuon = ev.nMuon
            leptonSum = tmpnElectron+tmpnMuon
            #Variables for tracking the lepton energy that is the closest to the Z mass
            difFromZMassOne = 1000
            difFromZMassTwo = 1000
            #Vectors for Leptons
            leadLepPairOneVec = Math.PtEtaPhiMVector(0,0,0,0)
            trailingLepPairOneVec = Math.PtEtaPhiMVector(0,0,0,0)
            #leadLepPairTwoVec = Math.PtEtaPhiMVector(0,0,0,0)
            #trailingLepPairTwoVec = Math.PtEtaPhiMVector(0,0,0,0)
            leadLepPairVec = Math.PtEtaPhiMVector(0,0,0,0)
            trailingLepPairVec = Math.PtEtaPhiMVector(0,0,0,0)
            elecPassesCutsAr = []
            elecPassesZ2CutsAr = []
            leadLepPairCharge = 0
            trailingLepPairCharge = 0
            leadZ2LepPairInd = -1
            leadZ2Pt = 0
            trailingZ2Pt = 0

            #Counting Elec Candidates Loop
            nElecCandidates = 0
            elecVetoAr = []
            #Replacing bools here with a counter
            #elecHasNeg = False
            #elecHasPos = False
            nElecCandidatesNeg = 0
            nElecCandidatesPos = 0
            #Looping over electrons
            if debug:
                print("------------------------------------------------------")
            for i in range(tmpnElectron):
                if debug:
                    print(evCount,"ev.Electron_eta[i]",ev.Electron_eta[i],"ev.Electron_pt[i]",ev.Electron_pt[i],"ev.Electron_charge[i]",ev.Electron_charge[i],"ev.Electron_mass[i]",ev.Electron_mass[i])
                #Checking for electron candidates with the initial eta and pt cuts. Keeping track of whether there is a negative and/or a positive electron present
                if abs(ev.Electron_eta[i]) < cutSet[0] and ev.Electron_pt[i] > cutSet[1]:

                    nElecCandidates += 1
                    if ev.Electron_charge[i] == -1:
                        #elecHasNeg = True
                        nElecCandidatesNeg += 1
                    else:
                        #elecHasPos = True
                        nElecCandidatesPos += 1
                else:
                    #Keeping track of electrons that didn't pass
                    elecVetoAr.append(i)
            nElecCandPairs = 0
            if nElecCandidatesNeg <= nElecCandidatesPos:
                nElecCandPairs = nElecCandidatesNeg
            else:
                nElecCandPairs = nElecCandidatesPos
            if debug:
                print("nElecCandidatesNeg",nElecCandidatesNeg,"nElecCandidatesPos",nElecCandidatesPos,"nElecCandPairs",nElecCandPairs)
            
            #Counting Muon Candidates Loop
            nMuonCandidates = 0
            muonVetoAr = []
            #muonHasNeg = False
            #muonHasPos = False
            nMuonCandidatesNeg = 0
            nMuonCandidatesPos = 0
            #Loop over muons
            for i in range(tmpnMuon):
                if debug:
                    print("ev.Muon_eta[i]",ev.Muon_eta[i],"ev.Muon_pt[i]",ev.Muon_pt[i],"ev.Muon_charge[i]",ev.Muon_charge[i])
                #Checking for muon candidates with the initial eta and pt cuts. Keeping track of whether there is a negative and/or a positive muon present
                if abs(ev.Muon_eta[i]) < cutSet[2] and ev.Muon_pt[i] > cutSet[3]:
                    nMuonCandidates += 1
                    if ev.Muon_charge[i] == -1:
                        #muonHasNeg = True
                        nMuonCandidatesNeg += 1
                    else:
                        #muonHasPos = True
                        nMuonCandidatesPos += 1
                else:
                    #Keeping track of muons that didn't pass
                    muonVetoAr.append(i)
            nMuonCandPairs = 0
            if nMuonCandidatesNeg <= nMuonCandidatesPos:
                nMuonCandPairs = nMuonCandidatesNeg
            else:
                nMuonCandPairs = nMuonCandidatesPos
            if debug:
                print("nMuonCandidatesNeg",nMuonCandidatesNeg,"nMuonCandidatesPos",nMuonCandidatesPos,"nMuonCandPairs",nMuonCandPairs)
            
            enoughElecCands = False
            enoughMuonCands = False
            enoughLepCands = False
            #Checking if there is an electron positron pair
            if nElecCandPairs >= 1:
                enoughElecCands = True
                #Checking if electrons alone satisfy the lep candidates
                #if nElecCandidates >=4 and nElecCandPairs >= 2:
                if nElecCandPairs >= 2:
                    enoughLepCands = True
            if nMuonCandPairs >= 1:
                enoughMuonCands = True
                #Checking if muons alone satisfy the lep candidates
                #if nMuonCandidates >=4 and nMuonCandPairs >= 2:
                if nMuonCandPairs >= 2:
                    enoughLepCands = True
                #Else, checking if the sum of the two is enough and whether or not they both have a pair
                elif not enoughLepCands and enoughElecCands:
                    enoughLepCands = True

            if debug:
                print("enoughElecCands",enoughElecCands,"enoughMuonCands",enoughMuonCands,"enoughLepCands",enoughLepCands)
            #leptonCandSum = nElecCandidates + nMuonCandidates
            #Electrons loop
            if debug:
                print("entering electrons loop")
            for i in range(tmpnElectron):
                if debug:
                    print("Electron",i)
                tmpPtOne = ev.Electron_pt[i]
                tmpEtaOne = ev.Electron_eta[i]
                tmpMassOne = ev.Electron_mass[i]
                tmpPhiOne = ev.Electron_phi[i]
                
                #If enough lepton candidates and enough electron candidates, begin the loop
                #if leptonCandSum >= 4:
                if enoughLepCands and enoughElecCands:
                    if debug:
                        print(i,"enough LepCands and ElecCands")
                    if not ifEnoughElecCandBool:
                        ifEnoughElecCandCount[l] += 1
                        ifEnoughElecCandBool = True
                        
                    if tmpPtOne > cutSet[4]:
                        if debug:
                            print(i,"Electron passed first trailing pt cut",cutSet[4])
                        #Looping over other electrons
                        if debug:
                            print(i,"Loop over remaining electrons")
                        for j in range(i+1,tmpnElectron):
                            if debug:
                                print("Electron",j)
                            #Check that the electrons have the opposite charge
                            tmpElecCharge = ev.Electron_charge[i]
                            tmpElecChargeTwo = ev.Electron_charge[j]
                            if tmpElecCharge == - tmpElecChargeTwo:
                                if debug:
                                    print(i,j,"Electrons have the opposite charge")
                                #Get variables from second electron
                                tmpPtTwo = ev.Electron_pt[j]

                                tmpEtaTwo = ev.Electron_eta[j]
                                tmpMassTwo = ev.Electron_mass[j]
                                if debug:
                                    print(i,j,"ev.Electron_mass",tmpMassOne,tmpMassTwo)
                                
                                tmpPhiTwo = ev.Electron_phi[j]

                                if tmpPtOne > tmpPtTwo:
                                    tmpMaxPtLead = tmpPtOne
                                    tmpMaxPtSecond = tmpPtTwo
                                    tmpLeadInd = i
                                    tmpSecondInd = j
                                    tmpLeadCharge = tmpElecCharge
                                    tmpTrailingCharge = tmpElecChargeTwo
                                else:
                                    tmpMaxPtLead = tmpPtTwo
                                    tmpMaxPtSecond = tmpPtOne
                                    tmpLeadInd = j
                                    tmpSecondInd = i
                                    tmpLeadCharge = tmpElecChargeTwo
                                    tmpTrailingCharge = tmpElecCharge
                                if tmpLeadInd == i:
                                    tmpLeadVec = Math.PtEtaPhiMVector(tmpPtOne, tmpEtaOne, tmpPhiOne, tmpMassOne)
                                    tmpTrailingVec = Math.PtEtaPhiMVector(tmpPtTwo, tmpEtaTwo, tmpPhiTwo, tmpMassTwo)
                                else:
                                    tmpLeadVec = Math.PtEtaPhiMVector(tmpPtTwo, tmpEtaTwo, tmpPhiTwo, tmpMassTwo)
                                    tmpTrailingVec = Math.PtEtaPhiMVector(tmpPtOne, tmpEtaOne, tmpPhiOne, tmpMassOne)
                                
                                tmpDiElectronVec = tmpLeadVec+tmpTrailingVec
                                tmpDiElectronInvMass = tmpDiElectronVec.M()
                                if debug:
                                    print(i,j,"tmpLeadInd",tmpLeadInd,"tmpSecondInd",tmpSecondInd,"tmpMaxPtLead",tmpMaxPtLead,"tmpMaxPtSecond",tmpMaxPtSecond,"tmpLeadCharge",tmpLeadCharge,"tmpTrailingCharge",tmpTrailingCharge)
                                if debug:
                                    print("tmpDiElectronInvMass",tmpDiElectronInvMass)
                                if tmpDiElectronInvMass > cutSet[5]:
                                    if debug:
                                        print(i,j,"Electron pair passed invmass Z2 cut",cutSet[5])
                                    elecPassesZ2CutsAr.append([[tmpLeadInd,tmpSecondInd],[tmpLeadVec,tmpTrailingVec],[tmpLeadCharge,tmpTrailingCharge]])
                                #Check that the pt of the second electron passes the lower pt cut
                                if tmpPtTwo > cutSet[4]:
                                    if debug:
                                        print(i,j,"Second electron pt passed Z1 trailing cut",cutSet[4])
                                    #Sort the electrons into leading and trailing based on pt
                                    #Actually get these earlier
                                    #Check that the lead electron passes the higher pt cut
                                    if tmpMaxPtLead > cutSet[6]:
                                        if debug:
                                            print(i,j,"Electron lead pt passed Z1 lead cut",cutSet[6])
                                        #If so, get variables from the second electron (actually now it works better to get them earlier)
                                        #Also get the vectors and inv mass earlier
                                        
                                        #Check that invmass passes the Cut
                                        if tmpDiElectronInvMass > cutSet[7]:
                                            if debug:
                                                print(i,j,"Electron pair passed Z1 inv mass cut",cutSet[7])
                                            if not ifZ1ElecPairCandBool:
                                                ifZ1ElecPairCandCount[l]+= 1
                                                ifZ1ElecPairCandBool = True
                                            elecPassesCutsAr.append([tmpLeadInd,tmpSecondInd])
                                            #Check if the mass is closer to Z than current candidate
                                            tmpDifFromZMass = abs(tmpDiElectronInvMass-ZMass)
                                            #Switching over variables
                                            if debug:
                                                print(i,j,"tmpDifFromZMass",tmpDifFromZMass)
                                            if tmpDifFromZMass < difFromZMassOne:
                                                if debug:
                                                    print(i,j,"Electron pair has lowest current dif from Zmass. Old ZMassdif:",difFromZMassOne)
                                                #Switching ZMassDif
                                                difFromZMassOne = tmpDifFromZMass
                                                #Switching pair indices
                                                lepPairOneLeadInd = tmpLeadInd
                                                lepPairOneTrailingInd = tmpSecondInd
                                                #Switching 4 vectors
                                                leadLepPairOneVec = tmpLeadVec
                                                trailingLepPairOneVec = tmpTrailingVec
                                                leadLepPairCharge = tmpLeadCharge
                                                trailingLepPairCharge = tmpTrailingCharge
            if debug:
                print("ELECTRON LOOP OVER")
                print("difFromZMassOne",difFromZMassOne,"lepPairOneLeadInd",lepPairOneLeadInd,"lepPairOneTrailingInd",lepPairOneTrailingInd,"leadLepPairCharge",leadLepPairCharge,"trailingLepPairCharge",trailingLepPairCharge)

                            
            muonLeading = False
            muonPassesCutsAr = []
            muonPassesZ2CutsAr = []

            #Muons loop
            if debug:
                print("Entering muons loop")
            for i in range(tmpnMuon):
                if debug:
                    print("Muon",i)
                #No cuts
                tmpPtOne = ev.Muon_pt[i]
                tmpEtaOne = ev.Muon_eta[i]
                tmpMassOne = ev.Muon_mass[i]
                tmpPhiOne = ev.Muon_phi[i]
                
                
                #First Z Cuts
                if enoughLepCands and enoughMuonCands:
                    if debug:
                        print(i,"enough LepCands and MuonCands")
                    if not ifEnoughMuonCandBool:
                        ifEnoughMuonCandCount[l]+= 1
                        ifEnoughMuonCandBool = True
                    if tmpPtOne > cutSet[4]:
                        if debug:
                            print(i,"Muon passed first trailing pt cut", cutSet[4])
                        #Looping over other muons
                        if debug:
                            print(i,"Loop over remaining muons")
                        for j in range(i+1,tmpnMuon):
                            if debug:
                                print("Muon",j)
                            #Check that muons have the opposite charge
                            tmpMuonCharge = ev.Muon_charge[i]
                            tmpMuonChargeTwo = ev.Muon_charge[j]
                            if tmpMuonCharge == - tmpMuonChargeTwo:
                                if debug:
                                    print(i,j,"Muons have the opposite charge")
                                #Get vaariables from second electron
                                tmpPtTwo = ev.Muon_pt[j]
                                tmpEtaTwo = ev.Muon_eta[j]
                                if debug:
                                    print(i,j,"ev.Muon_mass",ev.Muon_mass[i],ev.Muon_mass[j])
                                tmpMassTwo = ev.Muon_mass[j]
                                tmpPhiTwo = ev.Muon_phi[j]

                                if tmpPtOne > tmpPtTwo:
                                    tmpMaxPtLead = tmpPtOne
                                    tmpMaxPtSecond = tmpPtTwo
                                    tmpLeadInd = i
                                    tmpSecondInd = j
                                    tmpLeadCharge = tmpMuonCharge
                                    tmpTrailingCharge = tmpMuonChargeTwo
                                else:
                                    tmpMaxPtLead = tmpPtTwo
                                    tmpMaxPtSecond = tmpPtOne
                                    tmpLeadInd = j
                                    tmpSecondInd = i
                                    tmpLeadCharge = tmpMuonChargeTwo
                                    tmpTrailingCharge = tmpMuonCharge
                                if tmpLeadInd == i:
                                    tmpLeadVec = Math.PtEtaPhiMVector(tmpPtOne, tmpEtaOne, tmpPhiOne, tmpMassOne)
                                    tmpTrailingVec = Math.PtEtaPhiMVector(tmpPtTwo, tmpEtaTwo, tmpPhiTwo, tmpMassTwo)
                                else:
                                    tmpLeadVec = Math.PtEtaPhiMVector(tmpPtTwo, tmpEtaTwo, tmpPhiTwo, tmpMassTwo)
                                    tmpTrailingVec = Math.PtEtaPhiMVector(tmpPtOne, tmpEtaOne, tmpPhiOne, tmpMassOne)
                                tmpDiMuonVec = tmpLeadVec+tmpTrailingVec
                                tmpDiMuonInvMass = tmpDiMuonVec.M()
                                if debug:
                                    print(i,j,"tmpLeadInd",tmpLeadInd,"tmpSecondInd",tmpSecondInd,"tmpMaxPtLead",tmpMaxPtLead,"tmpMaxPtSecond",tmpMaxPtSecond,"tmpLeadCharge",tmpLeadCharge,"tmpTrailingCharge",tmpTrailingCharge)
                                if debug:
                                    print("tmpDiMuonInvMass",tmpDiMuonInvMass)
                                if tmpDiMuonInvMass > cutSet[5]:
                                    if debug:
                                        print(i,j,"Muon pair passed Z2 cut",cutSet[5])
                                    muonPassesZ2CutsAr.append([[tmpLeadInd,tmpSecondInd],[tmpLeadVec,tmpTrailingVec],[tmpLeadCharge,tmpTrailingCharge]])
                                
                                #Check that the pt of the second muon passes the lower pt cut
                                if tmpPtTwo > cutSet[4]:
                                    if debug:
                                        print(i,j,"Muon trailing pt passed Z1 trailing cut",cutSet[4])
                                    #Sort the muons into leading and trailing based on pt
                                    #Check that the lead muon passes the higher pt cut
                                    if tmpMaxPtLead > cutSet[6]:
                                        if debug:
                                            print(i,j,"Muon lead pt passed Z1 lead cut",cutSet[6])
                                        #Check that invmass passes the Cut
                                        if tmpDiMuonInvMass > cutSet[7]:
                                            if debug:
                                                print(i,j,"Muon pair passed Z1 inv mass cut",cutSet[7])
                                            if not ifZ1MuonPairCandBool:
                                                ifZ1MuonPairCandCount[l]+= 1
                                                ifZ1MuonPairCandBool = True
                                            muonPassesCutsAr.append([tmpLeadInd,tmpSecondInd])
                                            #Check if the mass is closer to Z than current candidate
                                            tmpDifFromZMass = abs(tmpDiMuonInvMass-ZMass)
                                            #Switching over variables
                                            if debug:
                                                print(i,j,"tmpDifFromZMass",tmpDifFromZMass)
                                            if tmpDifFromZMass < difFromZMassOne:
                                                if debug:
                                                    print(i,j,"Muon pair has lowest current dif from Zmass. Old ZMassdif:",difFromZMassOne)
                                                muonLeading = True
                                                #Switching ZMassDif
                                                #difFromZMassTwo = difFromZMassOne
                                                difFromZMassOne = tmpDifFromZMass
                                                #Switching pair indices
                                                #lepPairTwoLeadInd = lepPairOneLeadInd
                                                #lepPairTwoTrailingInd = lepPairOneTrailingInd
                                                lepPairOneLeadInd = tmpLeadInd
                                                lepPairOneTrailingInd = tmpSecondInd
                                                #Switching 4 vectors
                                                #leadLepPairTwoVec = leadLepPairOneVec
                                                #trailingLepPairTwoVec = trailingLepPairOneVec
                                                leadLepPairOneVec = tmpLeadVec
                                                trailingLepPairOneVec = tmpTrailingVec
                                                leadLepPairCharge = tmpLeadCharge
                                                trailingLepPairCharge = tmpTrailingCharge

            if debug:
                print("MUON LOOP OVER")
                print("difFromZMassOne",difFromZMassOne,"lepPairOneLeadInd",lepPairOneLeadInd,"lepPairOneTrailingInd",lepPairOneTrailingInd,"leadLepPairCharge",leadLepPairCharge,"trailingLepPairCharge",trailingLepPairCharge,"muonLeading",muonLeading)


            if debug:
                print("Going to find Z2 if Z1 has been found")
            if lepPairOneLeadInd >= 0 and lepPairOneTrailingInd >= 0:
                if debug:
                    print("Z1 was found")
                passesCandCuts = False
                muonZ2Pair = False
                if debug:
                    print("len(muonPassesCutsAr)",len(muonPassesCutsAr),"len(elecPassesCutsAr)",len(elecPassesCutsAr),"len(muonPassesZ2CutsAr)",len(muonPassesZ2CutsAr),"len(elecPassesZ2CutsAr",len(elecPassesZ2CutsAr))
                if len(muonPassesCutsAr) + len(elecPassesCutsAr) > 0 and len(muonPassesZ2CutsAr) + len(elecPassesZ2CutsAr) - 1 > 0: #-1 for the lead Z1 pair
                    if debug:
                        print("Passed check for there being enough candidates for Z2")
                        print("entering loop on Electron Z2 candidates")
                    for i,elecZ2Cand in enumerate(elecPassesZ2CutsAr):
                        if debug:
                            print(i,"elecZ2Cand",elecZ2Cand)
                        if muonLeading or (elecZ2Cand[0][0] != lepPairOneLeadInd and elecZ2Cand[0][0] != lepPairOneTrailingInd and elecZ2Cand[0][1] != lepPairOneLeadInd and elecZ2Cand[0][1] != lepPairOneTrailingInd):
                            if debug:
                                print("Passed the check that we aren't looking at the Z1 pair")
                            fourLepVec = elecZ2Cand[1][0] + elecZ2Cand[1][1] + leadLepPairOneVec + trailingLepPairOneVec
                            fourLepInvMass = fourLepVec.M()
                            if debug:
                                print("fourLepInvMass",fourLepInvMass)
                            if fourLepInvMass > cutSet[8]:
                                if debug:
                                    print("passed four lepton invmass cut",cutSet[8])
                                passesCandCuts = True
                                if not muonLeading:
                                    if debug:
                                        print("not muonLeading. checking 4 e cuts")
                                    passesCandCuts = False
                                    if elecZ2Cand[2][0] != leadLepPairCharge:
                                        if debug:
                                            print("elecZ2Can[2][0] != leadLepPairCharge","elecZ2Can[2][0]",elecZ2Cand[2][0],"leadLepPairCharge",leadLepPairCharge)
                                        tmpCrossCandVec = elecZ2Cand[1][0] + leadLepPairOneVec
                                        if debug:
                                            print("tmpCrossCandVec = elecZ2Cand[1][0] + leadLepPairOneVec",tmpCrossCandVec)
                                            print("tmpCrossCandVec.M()",tmpCrossCandVec.M())
                                        if tmpCrossCandVec.M() > cutSet[9]:
                                            if debug:
                                                print("passed check that the invmass is > cutSet[9]")
                                            passesCandCuts = True
                                        else:
                                            tmpCrossCandVec = elecZ2Cand[1][1] + trailingLepPairOneVec
                                            if debug:
                                                print("Less than cutSet[9] so trying other electron electron combination")
                                                print("tmpCrossCandVec = elecZ2Cand[1][1] + trailingLepPairOneVec",tmpCrossCandVec)
                                                print("tmpCrossCandVec.M()",tmpCrossCandVec.M())
                                            if tmpCrossCandVec.M() > cutSet[9]:
                                                if debug:
                                                    print("passed check that the invmass is > cutSet[9]")
                                                passesCandCuts = True
                                    else:
                                        if debug:
                                            print("elecZ2Can[2][0] == leadLepPairCharge","elecZ2Can[2][0]",elecZ2Cand[2][0],"leadLepPairCharge",leadLepPairCharge)
                                        tmpCrossCandVec = elecZ2Cand[1][1] + leadLepPairOneVec
                                        if debug:
                                            print("tmpCrossCandVec = elecZ2Cand[1][1] + leadLepPairOneVec",tmpCrossCandVec)
                                            print("tmpCrossCandVec.M()",tmpCrossCandVec.M())
                                        if tmpCrossCandVec.M() > cutSet[9]:
                                            if debug:
                                                print("passed check that the invmass is > cutSet[9]")
                                            passesCandCuts = True
                                        else:
                                            tmpCrossCandVec = elecZ2Cand[1][0] + trailingLepPairOneVec
                                            if debug:
                                                print("Less than cutSet[9] so trying other electron electron combination")
                                                print("tmpCrossCandVec = elecZ2Cand[1][0] + trailingLepPairOneVec",tmpCrossCandVec)
                                                print("tmpCrossCandVec.M()",tmpCrossCandVec.M())
                                            if tmpCrossCandVec.M() > cutSet[9]:
                                                if debug:
                                                    print("passed check that the invmass is > cutSet[9]")
                                                passesCandCuts = True
                                if debug:
                                    print("checking if passed potential 4e cut","passesCandCuts",passesCandCuts)
                                if passesCandCuts:
                                    if debug:
                                        print("passed cut. Checking for highest Pt in lead of Z2")
                                    if not ifZ2ElecPairCandBool:
                                        ifZ2ElecPairCandCount[l]+= 1
                                        ifZ2ElecPairCandBool = True
                                    if debug:
                                        print("elecZ2Cand[1][0].Pt()",elecZ2Cand[1][0].Pt())
                                    if elecZ2Cand[1][0].Pt() > leadZ2Pt:
                                        if debug:
                                            print("New highest pt found. Old pt:",leadZ2Pt)
                                        leadZ2Pt = elecZ2Cand[1][0].Pt()
                                        trailingZ2Pt = elecZ2Cand[1][1].Pt()
                                        leadZ2LepPairInd = i
                                    elif elecZ2Cand[1][0].Pt() == leadZ2Pt:
                                        if debug:
                                            print("Highest pt equal. checking trailing Z2 pt")
                                        if elecZ2Cand[1][1].Pt() == trailingZ2Pt:
                                            if debug:
                                                print("New highest trailing pt found. Old pt:",trailingZ2Pt)
                                            trailingZ2Pt = elecZ2Cand[1][1].Pt()
                                            leadZ2LepPairInd = i
                    if debug:

                        print("ELECTRON Z2 LOOP FINISHED")
                        print("leadZ2LepPairInd",leadZ2LepPairInd,"leadZ2Pt",leadZ2Pt,"trailingZ2Pt",trailingZ2Pt)


                                    


                    for i,muonZ2Cand in enumerate(muonPassesZ2CutsAr):
                        if debug:
                            print(i,"muonZ2Cand",muonZ2Cand)
                        if not muonLeading or (muonZ2Cand[0][0] != lepPairOneLeadInd and muonZ2Cand[0][0] != lepPairOneTrailingInd and muonZ2Cand[0][1] != lepPairOneLeadInd and muonZ2Cand[0][1] != lepPairOneTrailingInd): 
                            if debug:
                                print("Passed the check that we aren't looking at the Z1 pair")
                            fourLepVec = muonZ2Cand[1][0] + muonZ2Cand[1][1] + leadLepPairOneVec + trailingLepPairOneVec
                            fourLepInvMass = fourLepVec.M()
                            if debug:
                                print("fourLepInvMass",fourLepInvMass)
                            if fourLepInvMass > cutSet[8]:
                                if debug:
                                    print("passed four lepton invmass cut",cutSet[8])
                                passesCandCuts = True
                                if muonLeading:
                                    if debug:
                                        print("muonLeading. checking 4 e cuts")
                                    passesCandCuts = False
                                    if muonZ2Cand[2][0] != leadLepPairCharge:
                                        if debug:
                                            print("muonZ2Can[2][0] != leadLepPairCharge","muonZ2Can[2][0]",muonZ2Cand[2][0],"leadLepPairCharge",leadLepPairCharge)
                                        tmpCrossCandVec = muonZ2Cand[1][0] + leadLepPairOneVec
                                        if debug:
                                            print("tmpCrossCandVec = muonZ2Cand[1][0] + leadLepPairOneVec",tmpCrossCandVec)
                                            print("tmpCrossCandVec.M()",tmpCrossCandVec.M())
                                        if tmpCrossCandVec.M() > cutSet[9]:
                                            if debug:
                                                print("passed check that the invmass is > cutSet[9]")
                                            passesCandCuts = True
                                        else:
                                            
                                            tmpCrossCandVec = muonZ2Cand[1][1] + trailingLepPairOneVec
                                            if debug:
                                                print("Less than cutSet[9] so trying other muon muon combination")
                                                print("tmpCrossCandVec = muonZ2Cand[1][1] + trailingLepPairOneVec",tmpCrossCandVec)
                                                print("tmpCrossCandVec.M()",tmpCrossCandVec.M())
                                            if tmpCrossCandVec.M() > cutSet[9]:
                                                if debug:
                                                    print("passed check that the invmass is > cutSet[9]")
                                                passesCandCuts = True
                                    else:
                                        if debug:
                                            print("muonZ2Can[2][0] == leadLepPairCharge","muonZ2Can[2][0]",muonZ2Cand[2][0],"leadLepPairCharge",leadLepPairCharge)
                                        tmpCrossCandVec = muonZ2Cand[1][1] + leadLepPairOneVec
                                        if debug:
                                            print("tmpCrossCandVec = muonZ2Cand[1][1] + leadLepPairOneVec",tmpCrossCandVec)
                                            print("tmpCrossCandVec.M()",tmpCrossCandVec.M())
                                        if tmpCrossCandVec.M() > cutSet[9]:
                                            if debug:
                                                print("passed check that the invmass is > cutSet[9]")
                                            passesCandCuts = True
                                            
                                        else:
                                            tmpCrossCandVec = muonZ2Cand[1][0] + trailingLepPairOneVec
                                            if debug:
                                                print("Less than cutSet[9] so trying other muon muon combination")
                                                print("tmpCrossCandVec = muonZ2Cand[1][0] + trailingLepPairOneVec",tmpCrossCandVec)
                                                print("tmpCrossCandVec.M()",tmpCrossCandVec.M())
                                            if tmpCrossCandVec.M() > cutSet[9]:
                                                if debug:
                                                    print("passed check that the invmass is > cutSet[9]")
                                                passesCandCuts = True
                                if passesCandCuts:
                                    if debug:
                                        print("passed cut. Checking for highest Pt in lead of Z2")
                                    if not ifZ2MuonPairCandBool:
                                        ifZ2MuonPairCandCount[l]+= 1
                                        ifZ2MuonPairCandBool = True
                                    if debug:
                                        print("muonZ2Cand[1][0].Pt()",muonZ2Cand[1][0].Pt())
                                    if muonZ2Cand[1][0].Pt() > leadZ2Pt:
                                        if debug:
                                            print("New highest pt found. Old pt:",leadZ2Pt)
                                        muonZ2Pair = True
                                        leadZ2Pt = muonZ2Cand[1][0].Pt()
                                        trailingZ2Pt = muonZ2Cand[1][1].Pt()
                                        leadZ2LepPairInd = i
                                    elif muonZ2Cand[1][0].Pt() == leadZ2Pt:
                                        if debug:
                                            print("Highest pt equal. checking trailing Z2 pt")
                                        if muonZ2Cand[1][1].Pt() == trailingZ2Pt:
                                            if debug:
                                                print("New highest trailing pt found. Old pt:",trailingZ2Pt)
                                            muonZ2Pair = True
                                            trailingZ2Pt = muonZ2Cand[1][1].Pt()
                                            leadZ2LepPairInd = i
                #At this point, if the cuts were passed, should have two pairs of leptons. The first reprsented by
                #lepPairOneLeadInd,lepPairOneTrailingInd variables (also lead/trailingLepPairOneVec and lead/trailingLepPairCharge)
                #which can be used to index ev.Electron/Muon_Branch
                #The second represented by 
                #leadZ2LepPairInd which can be used to index elec/muonPassesZ2CutsAr
                #which contains the indices for accessing the ev.Electron/Muon_branch, the four vector, and the charge)
                #So first check that the cuts were passed:
                if debug:
                    print("MUON Z2 LOOP FINISHED")
                    print("muonZ2Pair",muonZ2Pair,"leadZ2LepPairInd",leadZ2LepPairInd,"leadZ2Pt",leadZ2Pt,"trailingZ2Pt",trailingZ2Pt)
                    print("now checking if the Z2 cuts were passed")
                if leadZ2LepPairInd >= 0:
                    if debug:
                        print("The Z2 cuts were passed")
                    #Now we want to cut based on the relative isolation
                    #For each lepton this is obtained as follows
                    #Sum up the Pt for all the tracks, the energy deposits in the ECAL, and the energy deposits in the HCAL, within a DeltaR < 0.3 cone around the lepton
                    #Add these three sums together and divide by the lepton's Pt
                    #Unfortunately with NanoAOD, you do not have the information to do these sums.
                    #There are branches that have precalculated them, but only for electrons with Pt > 35GeV
                    #The muon branches don't have these, but rather have values based on particle flow
                    #Particularly the Muon_pfRelIso03_all branch
                    #Not sure if it's at all proper to add these together, but will use the electron PF isolation also when Pt < 35GeV
                    passesIsoCuts = True
                    
                    muonOrNotAr = [muonLeading,muonZ2Pair]
                    if debug:
                        print("muonOrNotAr",muonOrNotAr)
                    passesPtCutAr = [True,True,True,True]
                    Z1Z2VecPtAr = []
                    Z1Z2VecPtAr.append(leadLepPairOneVec.Pt())
                    Z1Z2VecPtAr.append(trailingLepPairOneVec.Pt())
                    Z1Z2IndAr = [lepPairOneLeadInd,lepPairOneTrailingInd,leadZ2LepPairInd,leadZ2LepPairInd]
                    #Previously used passesPtCutAr to bypass the cuts if the Pt was less than 35,
                    #but now just using it to switch different types of isolation used in the cuts for electrons
                    for i in range(4):
                        if i < 2: 
                            if muonLeading:
                                continue
                            elif Z1Z2VecPtAr[i] < 35:
                                passesPtCutAr[i] = False
                        elif muonZ2Pair:
                            Z1Z2VecPtAr.append(muonPassesZ2CutsAr[leadZ2LepPairInd][1][i-2].Pt())
                        else:
                            Z1Z2VecPtAr.append(elecPassesZ2CutsAr[leadZ2LepPairInd][1][i-2].Pt())
                            if Z1Z2VecPtAr[i] < 35:
                                passesPtCutAr[i] = False

    

                    if debug:
                        print("Z1Z2VecPtAr",Z1Z2VecPtAr,"Z1Z2IndAr",Z1Z2IndAr,"passesPtCutAr",passesPtCutAr)

                    for i,Z1Z2Ind in enumerate(Z1Z2IndAr):
                        for j in range(i+1,len(Z1Z2IndAr)):
                            Z1Z2IndTwo = Z1Z2IndAr[j]
                            if debug:
                                print(i,j,"muonLeading",muonLeading,"muonZ2Pair",muonZ2Pair,"Z1Z2Ind",Z1Z2Ind,"Z1Z2IndTwo",Z1Z2IndTwo)
                            #Getting indices for accessing the different arrays for Z1
                            tmpIsMuonOne = True
                            if i < 2:
                                tmpIsoOneInd = Z1Z2Ind
                                if not muonLeading:
                                    tmpIsMuonOne = False
                            elif muonZ2Pair:
                                tmpIsoOneInd = muonPassesZ2CutsAr[Z1Z2Ind][0][i-2]
                            else:
                                tmpIsoOneInd = elecPassesZ2CutsAr[Z1Z2Ind][0][i-2]
                                tmpIsMuonOne = False
                            #Getting indices for accessing the different arrays for Z2
                            tmpIsMuonTwo = True
                            if j < 2:
                                tmpIsoTwoInd = Z1Z2IndTwo
                                if not muonLeading:
                                    tmpIsMuonTwo = False
                            elif muonZ2Pair:
                                tmpIsoTwoInd = muonPassesZ2CutsAr[Z1Z2IndTwo][0][j-2]
                            else:
                                tmpIsoTwoInd = elecPassesZ2CutsAr[Z1Z2IndTwo][0][j-2]
                                tmpIsMuonTwo = False
                            if debug:
                                print(i,j,"tmpIsoOneInd",tmpIsoOneInd,"tmpIsoTwoInd",tmpIsoTwoInd)
                            #Getting tmpIsoOne
                            if tmpIsMuonOne:
                                tmpIsoOne = ev.Muon_pfRelIso03_all[tmpIsoOneInd]
                            elif passesPtCutAr[i]:
                                if abs(ev.Electron_eta[tmpIsoOneInd]) < 1.4:
                                    if debug:
                                        print("electron in barrel")
                                    tmpAdd = max(0., ev.Electron_dr03EcalRecHitSumEt[tmpIsoOneInd] - 1.)
                                else:
                                    if debug:
                                        print("electron in endcap")
                                    tmpAdd = ev.Electron_dr03EcalRecHitSumEt[tmpIsoOneInd]
                                tmpIsoOne = ( ev.Electron_dr03TkSumPt[tmpIsoOneInd] + tmpAdd + ev.Electron_dr03HcalDepth1TowerSumEt[tmpIsoOneInd] ) / ev.Electron_pt[tmpIsoOneInd]
                            else:
                                tmpIsoOne = ev.Electron_pfRelIso03_all[tmpIsoOneInd]
                            #Getting tmpIsoTwo
                            if tmpIsMuonTwo:
                                tmpIsoTwo = ev.Muon_pfRelIso03_all[tmpIsoTwoInd]
                            elif passesPtCutAr[i]:
                                if abs(ev.Electron_eta[tmpIsoTwoInd]) < 1.4:
                                    if debug:
                                        print("electron in barrel")
                                    tmpAdd = max(0., ev.Electron_dr03EcalRecHitSumEt[tmpIsoTwoInd] - 1.)
                                else:
                                    if debug:
                                        print("electron in endcap")
                                    tmpAdd = ev.Electron_dr03EcalRecHitSumEt[tmpIsoTwoInd]
                                tmpIsoTwo = ( ev.Electron_dr03TkSumPt[tmpIsoTwoInd] + tmpAdd + ev.Electron_dr03HcalDepth1TowerSumEt[tmpIsoTwoInd] ) / ev.Electron_pt[tmpIsoTwoInd]
                            else:
                                tmpIsoTwo = ev.Electron_pfRelIso03_all[tmpIsoTwoInd]
                            if debug:
                                print(i,j,"tmpIsoOne",tmpIsoOne,"tmpIsoTwo",tmpIsoTwo)
                            if tmpIsoOne + tmpIsoTwo > 0.35:
                                if debug:
                                    print(i,j,"summed isos > 0.35. cuts not passed")
                                passesIsoCuts = False
                            


                            
                                
                    if debug:
                        print("FINISHED WITH ISO CUTS","passesIsoCuts",passesIsoCuts)



                    #Now, assuming all *these* cuts pass, on to cut 6.
                    #Want the SIP of the leptons
                    
                    if passesIsoCuts:
                        if debug:
                            print("passed iso cuts. Starting SIP cuts")
                        if not passesIsoCutsBool:
                            passesIsoCutsCount[l]+= 1
                            passesIsoCutsBool = True

                        passesSIPCut = True
                        if muonLeading:
                            if debug:
                                print("muonLeading",muonLeading)
                            if muonZ2Pair:
                                if debug:
                                    print("muonZ2Pair",muonZ2Pair)
                                    print("ev.Muon_sip3d[lepPairOneLeadInd]",ev.Muon_sip3d[lepPairOneLeadInd],"ev.Muon_sip3d[lepPairOneTrailingInd]",ev.Muon_sip3d[lepPairOneTrailingInd])
                                    print("ev.Muon_sip3d[muonPassesZ2CutsAr[leadZ2LepPairInd][0][0]]",ev.Muon_sip3d[muonPassesZ2CutsAr[leadZ2LepPairInd][0][0]],"ev.Muon_sip3d[muonPassesZ2CutsAr[leadZ2LepPairInd][0][1]]",ev.Muon_sip3d[muonPassesZ2CutsAr[leadZ2LepPairInd][0][1]])
                                if ev.Muon_sip3d[lepPairOneLeadInd] > 4:
                                    passesSIPCut = False
                                elif ev.Muon_sip3d[lepPairOneTrailingInd] > 4:
                                    passesSIPCut = False
                                elif ev.Muon_sip3d[muonPassesZ2CutsAr[leadZ2LepPairInd][0][0]] > 4:
                                    passesSIPCut = False
                                elif ev.Muon_sip3d[muonPassesZ2CutsAr[leadZ2LepPairInd][0][1]] > 4:
                                    passesSIPCut = False
                                if debug:
                                    print("passesSIPCut",passesSIPCut)
                            else:
                                if debug:
                                    print("muonZ2Pair",muonZ2Pair)
                                    print("ev.Muon_sip3d[lepPairOneLeadInd]",ev.Muon_sip3d[lepPairOneLeadInd],"ev.Muon_sip3d[lepPairOneTrailingInd]",ev.Muon_sip3d[lepPairOneTrailingInd])
                                    print("ev.Electron_sip3d[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]]",ev.Electron_sip3d[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]],"ev.Electron_sip3d[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]]",ev.Electron_sip3d[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]])
                                if ev.Muon_sip3d[lepPairOneLeadInd] > 4:
                                    passesSIPCut = False
                                elif ev.Muon_sip3d[lepPairOneTrailingInd] > 4:
                                    passesSIPCut = False
                                elif ev.Electron_sip3d[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]] > 4:
                                    passesSIPCut = False
                                elif ev.Electron_sip3d[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]] > 4:
                                    passesSIPCut = False
                                if debug:
                                    print("passesSIPCut",passesSIPCut)
                        elif muonZ2Pair:
                            if debug:
                                print("muonLeading",muonLeading)
                                print("muonZ2Pair",muonZ2Pair)
                                print("ev.Electron_sip3d[lepPairOneLeadInd]",ev.Electron_sip3d[lepPairOneLeadInd],"ev.Electron_sip3d[lepPairOneTrailingInd]",ev.Electron_sip3d[lepPairOneTrailingInd])
                                print("ev.Muon_sip3d[muonPassesZ2CutsAr[leadZ2LepPairInd][0][0]]",ev.Muon_sip3d[muonPassesZ2CutsAr[leadZ2LepPairInd][0][0]],"ev.Muon_sip3d[muonPassesZ2CutsAr[leadZ2LepPairInd][0][1]]",ev.Muon_sip3d[muonPassesZ2CutsAr[leadZ2LepPairInd][0][1]])
                            #print("lepPairOneLeadInd",lepPairOneLeadInd,"len(ev.Electron_sip3d)",len(ev.Electron_sip3d))
                            #print("len(ev.Electron_pt)",len(ev.Electron_pt))
                            #print("nElecCandidates",nElecCandidates,"nMuonCandidates",nMuonCandidates,"enoughLepCands",enoughLepCands,"enoughElecCands",enoughElecCands,"enoughMuonCands",enoughMuonCands)
                            #print("leadLepPairOneVec",leadLepPairOneVec,"trailingLepPairOneVec",trailingLepPairOneVec)
                            #print("muonLeading",muonLeading,"muonZ2Pair",muonZ2Pair)
                            #print()
                            if ev.Electron_sip3d[lepPairOneLeadInd] > 4:
                                passesSIPCut = False
                            elif ev.Electron_sip3d[lepPairOneTrailingInd] > 4:
                                passesSIPCut = False
                            elif ev.Muon_sip3d[muonPassesZ2CutsAr[leadZ2LepPairInd][0][0]] > 4:
                                passesSIPCut = False
                            elif ev.Muon_sip3d[muonPassesZ2CutsAr[leadZ2LepPairInd][0][1]] > 4:
                                passesSIPCut = False
                            if debug:
                                print("passesSIPCut",passesSIPCut)
                        else:
                            if debug:
                                print("muonLeading",muonLeading)
                                print("muonZ2Pair",muonZ2Pair)
                                print("ev.Electron_sip3d[lepPairOneLeadInd]",ev.Electron_sip3d[lepPairOneLeadInd],"ev.Electron_sip3d[lepPairOneTrailingInd]",ev.Electron_sip3d[lepPairOneTrailingInd])
                                print("ev.Electron_sip3d[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]]",ev.Electron_sip3d[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]],"ev.Electron_sip3d[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]]",ev.Electron_sip3d[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]])
                            if ev.Electron_sip3d[lepPairOneLeadInd] > 4:
                                passesSIPCut = False
                            elif ev.Electron_sip3d[lepPairOneTrailingInd] > 4:
                                passesSIPCut = False
                            elif ev.Electron_sip3d[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]] > 4:
                                passesSIPCut = False
                            elif ev.Electron_sip3d[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]] > 4:
                                passesSIPCut = False
                            if debug:
                                print("passesSIPCut",passesSIPCut)
                        #Now just check that the Z1 and Z2 inv mass falls within the Z low and Z high cuts
                        if passesSIPCut:
                            if debug:
                                print("passed SIP Cut")
                            if not passesSIPCutBool:
                                passesSIPCutCount[l] += 1
                                passesSIPCutBool = True

                            tmpVec = leadLepPairOneVec + trailingLepPairOneVec
                            tmpZ1InvMass = tmpVec.M()
                            if debug:
                                print("tmpVec",tmpVec,"tmpZ1InvMass",tmpZ1InvMass)
                            if tmpZ1InvMass < cutSet[10]:
                                if debug:
                                    print("Passed Z1 invmass cut",cutSet[10])
                                if muonZ2Pair:
                                    if debug:
                                        print("muonZ2Pair",muonZ2Pair)
                                    tmpLeadZ2Vec = muonPassesZ2CutsAr[leadZ2LepPairInd][1][0]
                                    tmpTrailingZ2Vec = muonPassesZ2CutsAr[leadZ2LepPairInd][1][1]
                                    tmpVecTwo = tmpLeadZ2Vec + tmpTrailingZ2Vec
                                    if debug:
                                        print("tmpLeadZ2Vec",tmpLeadZ2Vec,"tmpTrailingZ2Vec",tmpTrailingZ2Vec,"tmpVecTwo",tmpVecTwo)
                                else:
                                    if debug:
                                        print("muonZ2Pair",muonZ2Pair)
                                    tmpLeadZ2Vec = elecPassesZ2CutsAr[leadZ2LepPairInd][1][0]
                                    tmpTrailingZ2Vec = elecPassesZ2CutsAr[leadZ2LepPairInd][1][1]
                                    tmpVecTwo = tmpLeadZ2Vec + tmpTrailingZ2Vec
                                    if debug:
                                        print("tmpLeadZ2Vec",tmpLeadZ2Vec,"tmpTrailingZ2Vec",tmpTrailingZ2Vec,"tmpVecTwo",tmpVecTwo)
                                tmpZ2InvMass = tmpVecTwo.M()
                                if debug:
                                    print("tmpZ2InvMass",tmpZ2InvMass)
                                if tmpZ2InvMass > cutSet[7] and tmpZ2InvMass < cutSet[10]:
                                    if debug:
                                        print("passed Z2 inv mass check",cutSet[7],cutSet[10])
                                        print("all checks passed")
                                    #at this point all lepton cuts have been passed.
                                    if not allCutPassBool:
                                        allCutPassCount[l]+= 1
                                        allCutPassBool = True
                                    
                        

            
        #Increment event count
        evCount += 1

print("Finished file loop.","time:",time.time()-startt)
#Writing different counters to output file:
outputFile = open("leptonCutOptimizationResults{0}".format(saveName),"w")
for l in range(masterCutsLen):
    outputFile.write("~~~~~~~~~~~~~~~~~~ "+"for cut number"+str(i)+" ~~~~~~~~~~~~~~~~~~"+"\n")
    outputFile.write("----------------------------------------------------------"+"\n")
    outputFile.write("Number of events with at least one electron candidate pair:"+str(ifEnoughElecCandCount[l])+"\n")
    outputFile.write("Number of events with at least one muon candidate pair:"+str(ifEnoughMuonCandCount[l])+"\n")
    outputFile.write("Number of events with at least one Z1 electron pair:"+str(ifZ1ElecPairCandCount[l])+"\n")
    outputFile.write("Number of events with at least one Z1 muon pair:"+str(ifZ1MuonPairCandCount[l])+"\n")
    outputFile.write("Number of events with at least one Z2 Electron pair:"+str(ifZ2ElecPairCandCount[l])+"\n")
    outputFile.write("Number of events with at least one Z2 Muon pair:"+str(ifZ2MuonPairCandCount[l])+"\n")
    outputFile.write("Number of events with at least one Z1Z2 pair passing iso cuts:"+str(passesIsoCutsCount[l])+"\n")
    outputFile.write("Number of events with at least one Z1Z2 pair passing SIP cuts:"+str(passesSIPCutCount[l])+"\n")
    outputFile.write("Number of events with at least one Z1Z2 pair passing all cuts:"+str(allCutPassCount[l])+"\n")
    outputFile.write("----------------------------------------------------------"+"\n")

outputFile.close()


#General stuff:
print("Done.","time:",time.time()-startt)


