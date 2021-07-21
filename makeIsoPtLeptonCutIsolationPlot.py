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


evToDebug = 4042
ptCutToDebug = 2
isoCutToDebug = 2

print("Making Histos/Defining variables.","time:",time.time()-startt)
#Defining Lepton cuts
ZMass = 91.1876

elecCandEtaCut =  2.5          #<
elecCandPTCut = 7              #>
muonCandEtaCut =  2.4          #<
muonCandPTCut = 5              #>

firstZTrailingCut = 10         #>
leptonZ2Cut = 12               #>
#firstZLeadingCut = 20          #>
leptonInvMassCutLow = 60       #>
fourLeptonInvMassCut = 100     #>
leptonInvMassCutTwo = 12       #>
leptonInvMassCutHigh = 120     #<


isoCutAr = [0.25,0.30,0.35,0.40,0.45]
firstZLeadingPtCutAr = [10,15,20,25,30]
#lepCutsAr = [2.5,7,2.4,5,10,12,20,60,100,12,120]
#cutsLowAr  = [3.5,0,3.4,0,0,0,5,30,50,0,150]
#cutsHighAr = [0.5,14,0.4,10,20,24,40,89,200,24,95]

#cutFloorAr = [0.5,0,0.4,0,0,0,5,30,50,0,95]
#cutCeilingAr = [3.5,14,3.4,10,20,24,40,89,200,24,150]
lessThanAr = [True,False,True,False,False,False,False,False,False,False,True]
#splitUpIntoInt = 2
#cutIncrementLowAr = [abs(lepCut-lepCutLow)/splitUpIntoInt for lepCut,lepCutLow in zip(lepCutsAr,cutsLowAr)]
#cutIncrementHighAr = [abs(lepCut-lepCutHigh)/splitUpIntoInt for lepCut,lepCutHigh in zip(lepCutsAr,cutsHighAr)]


#masterCutsLowAr = [[lepCutMid-(cutIncLow*splitUpItr) if not lessThanBool else lepCutMid+(cutIncLow*splitUpItr) for lepCutMid,cutIncLow,lessThanBool in zip(lepCutsAr,cutIncrementLowAr,lessThanAr)] for splitUpItr in range(2,0,-1)]
#masterCutsHighAr = [[lepCutMid+(cutIncHigh*splitUpItr) if not lessThanBool else lepCutMid-(cutIncHigh*splitUpItr) for lepCutMid,cutIncHigh,lessThanBool in zip(lepCutsAr,cutIncrementHighAr,lessThanAr)] for splitUpItr in range(1,3)]
#masterCutsAr = masterCutsLowAr+[lepCutsAr]+masterCutsHighAr
#counter Ars
#masterCutsLen         = len(masterCutsAr)
ptCutsLen             = len(firstZLeadingPtCutAr)
isoCutsLen            = len(isoCutAr)
ifEnoughElecCandCount = 0
ifEnoughMuonCandCount = 0
ifEnoughLepCandCount  = 0
ifZ1ElecPairCandCount = [0]*ptCutsLen
ifZ1MuonPairCandCount = [0]*ptCutsLen
ifZ1PairCandCount     = [0]*ptCutsLen
ifZ2ElecPairCandCount = [0]*ptCutsLen
ifZ2MuonPairCandCount = [0]*ptCutsLen
ifZ1Z2LepPairCandCount= [0]*ptCutsLen
ifZ1Z2PairAllElecCount= [0]*ptCutsLen
ifZ1Z2PairAllMuonCount= [0]*ptCutsLen
ifZ1ElecZ2MuonCount   = [0]*ptCutsLen
ifZ1MuonZ2ElecCount   = [0]*ptCutsLen
passesIsoCutsCount    = [[0]*ptCutsLen for isoCut in range(isoCutsLen)]
allCutPassCount       = [[0]*ptCutsLen for isoCut in range(isoCutsLen)]



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
        
        if evCount % 1000 == 0:
            print("Event: "+str(evCount))
        #if evCount > 450:
        #    break

        #Uncomment for debug on every event
        #evToDebug = evCount
        
        #IndicesForLeptonPairs
        lepPairOneLeadIndAr     = [-1 for i in range(len(firstZLeadingPtCutAr))]
        lepPairOneTrailingIndAr = [-1 for i in range(len(firstZLeadingPtCutAr))]
        #lepPairTwoLeadInd = 0
        #lepPairTwoTrailingInd = 0

        #For counters to not overcount

        #ifEnoughElecCandBool = False
        #ifEnoughMuonCandBool = False
        ifZ1ElecPairCandBoolAr = [False for i in range(len(firstZLeadingPtCutAr))]
        ifZ1MuonPairCandBoolAr = [False for i in range(len(firstZLeadingPtCutAr))]
        ifZ2ElecPairCandBoolAr = [False for i in range(len(firstZLeadingPtCutAr))]
        ifZ2MuonPairCandBoolAr = [False for i in range(len(firstZLeadingPtCutAr))]

        #Array for the Candidates for the first Z
        #ZOneCandAr   = []
        #number of electrons and muons and the sum
        tmpnElectron = ev.nElectron
        tmpnMuon     = ev.nMuon
        #leptonSum = tmpnElectron+tmpnMuon
        #Variables for tracking the lepton energy that is the closest to the Z mass
        difFromZMassOneAr = [1000 for i in range(len(firstZLeadingPtCutAr))]
        #difFromZMassTwo = 1000
        #Vectors for Leptons
        leadLepPairOneVecAr = [Math.PtEtaPhiMVector(0,0,0,0) for i in range(len(firstZLeadingPtCutAr))]
        trailingLepPairOneVecAr = [Math.PtEtaPhiMVector(0,0,0,0) for i in range(len(firstZLeadingPtCutAr))]
        elecPassesCutsAr   = [[] for i in range(len(firstZLeadingPtCutAr))]
        elecPassesZ2CutsAr = []
        leadLepPairChargeAr = [0 for i in range(len(firstZLeadingPtCutAr))]
        trailingLepPairChargeAr = [0 for i in range(len(firstZLeadingPtCutAr))]
        
        
        
        #Counting Elec Candidates Loop
        nElecCandidates = 0
        #elecVetoAr = []
        #Replacing bools here with a counter
        #elecHasNeg = False
        #elecHasPos = False
        nElecCandidatesNeg = 0
        nElecCandidatesPos = 0
        #Looping over electrons
        if debug and evCount == evToDebug:
            print("------------------------------------------------------")
        for i in range(tmpnElectron):
            if debug and evCount == evToDebug:
                print(evCount,"ev.Electron_eta[i]",ev.Electron_eta[i],"ev.Electron_pt[i]",ev.Electron_pt[i],"ev.Electron_charge[i]",ev.Electron_charge[i],"ev.Electron_mass[i]",ev.Electron_mass[i])
            #Checking for electron candidates with the initial eta and pt cuts. Keeping track of whether there is a negative and/or a positive electron present
            if abs(ev.Electron_eta[i]) < elecCandEtaCut and ev.Electron_pt[i] > elecCandPTCut:

                nElecCandidates += 1
                if ev.Electron_charge[i] == -1:
                    #elecHasNeg = True
                    nElecCandidatesNeg += 1
                else:
                    #elecHasPos = True
                    nElecCandidatesPos += 1
            #else:
            #    #Keeping track of electrons that didn't pass
            #    elecVetoAr.append(i)
        nElecCandPairs = 0
        if nElecCandidatesNeg <= nElecCandidatesPos:
            nElecCandPairs = nElecCandidatesNeg
        else:
            nElecCandPairs = nElecCandidatesPos
        if debug and evCount == evToDebug:
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
            if debug and evCount == evToDebug:
                print("ev.Muon_eta[i]",ev.Muon_eta[i],"ev.Muon_pt[i]",ev.Muon_pt[i],"ev.Muon_charge[i]",ev.Muon_charge[i])
            #Checking for muon candidates with the initial eta and pt cuts. Keeping track of whether there is a negative and/or a positive muon present
            if abs(ev.Muon_eta[i]) < muonCandEtaCut and ev.Muon_pt[i] > muonCandPTCut:
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
        if debug and evCount == evToDebug:
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
        if enoughLepCands:
            ifEnoughLepCandCount += 1
        if enoughElecCands:
            ifEnoughElecCandCount += 1
        if enoughMuonCands:
            ifEnoughMuonCandCount += 1
        if debug and evCount == evToDebug:
            print("enoughElecCands",enoughElecCands,"enoughMuonCands",enoughMuonCands,"enoughLepCands",enoughLepCands)
        #leptonCandSum = nElecCandidates + nMuonCandidates
        #Electrons loop
        if debug and evCount == evToDebug:
            print("entering electrons loop")
        for i in range(tmpnElectron-1):
            if debug and evCount == evToDebug:
                print("Electron",i)
            tmpPtOne = ev.Electron_pt[i]
            tmpEtaOne = ev.Electron_eta[i]
            tmpMassOne = ev.Electron_mass[i]
            tmpPhiOne = ev.Electron_phi[i]
            
            #If enough lepton candidates and enough electron candidates, begin the loop
            #if leptonCandSum >= 4:
            if enoughLepCands and enoughElecCands:
                if debug and evCount == evToDebug:
                    print(i,"enough LepCands and ElecCands")
                #if not ifEnoughElecCandBool:
                #    ifEnoughElecCandCount += 1
                #    ifEnoughElecCandBool = True
                
                
                #if debug and evCount == evToDebug:
                #    print(i,"Electron passed first trailing pt cut",firstZTrailingCut)
                #Looping over other electrons
                if debug and evCount == evToDebug:
                    print(i,"Loop over remaining electrons")
                for j in range(i+1,tmpnElectron):
                    if debug and evCount == evToDebug:
                        print("Electron",j)
                    #Check that the electrons have the opposite charge
                    tmpElecCharge = ev.Electron_charge[i]
                    tmpElecChargeTwo = ev.Electron_charge[j]
                    if tmpElecCharge == - tmpElecChargeTwo:
                        if debug and evCount == evToDebug:
                            print(i,j,"Electrons have the opposite charge")
                        #Get variables from second electron
                        tmpPtTwo = ev.Electron_pt[j]

                        tmpEtaTwo = ev.Electron_eta[j]
                        tmpMassTwo = ev.Electron_mass[j]
                        if debug and evCount == evToDebug:
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
                        if debug and evCount == evToDebug:
                            print(i,j,"tmpLeadInd",tmpLeadInd,"tmpSecondInd",tmpSecondInd,"tmpMaxPtLead",tmpMaxPtLead,"tmpMaxPtSecond",tmpMaxPtSecond,"tmpLeadCharge",tmpLeadCharge,"tmpTrailingCharge",tmpTrailingCharge)
                        if debug and evCount == evToDebug:
                            print("tmpDiElectronInvMass",tmpDiElectronInvMass)
                        #if tmpDiElectronInvMass > leptonZ2Cut:
                        if tmpDiElectronInvMass > leptonInvMassCutLow and tmpDiElectronInvMass < leptonInvMassCutHigh:
                            if debug and evCount == evToDebug:
                                print(i,j,"Electron pair passed invmass Z2 cut",leptonInvMassCutLow,leptonInvMassCutHigh)
                            elecPassesZ2CutsAr.append([[tmpLeadInd,tmpSecondInd],[tmpLeadVec,tmpTrailingVec],[tmpLeadCharge,tmpTrailingCharge]])
                        #Check that the pt of both electrons pass the lower pt cut
                            if tmpPtOne > firstZTrailingCut and tmpPtTwo > firstZTrailingCut:
                                if debug and evCount == evToDebug:
                                    print(i,j,"Both electron pt passed Z1 trailing cut",firstZTrailingCut)
                                #Sort the electrons into leading and trailing based on pt
                                #Actually get these earlier
                                #Check that the lead electron passes the higher pt cut
                                for ptCutItr,firstZLeadingPtCut in enumerate(firstZLeadingPtCutAr):
                                    #uncomment to debug on every pt cut
                                    #ptCutToDebug = ptCutItr
                                    if tmpMaxPtLead > firstZLeadingPtCut:
                                        if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
                                            print(i,j,"Electron lead pt passed Z1 lead cut",firstZLeadingPtCut)
                                        #If so, get variables from the second electron (actually now it works better to get them earlier)
                                        #Also get the vectors and inv mass earlier
                                        if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
                                            print(i,j,"Electron pair passed Z1 inv mass cut",leptonInvMassCutLow,leptonInvMassCutHigh)
                                        if not ifZ1ElecPairCandBoolAr[ptCutItr]:
                                            ifZ1ElecPairCandCount[ptCutItr] += 1
                                            ifZ1ElecPairCandBoolAr[ptCutItr] = True
                                        elecPassesCutsAr[ptCutItr].append([tmpLeadInd,tmpSecondInd])
                                        #Check if the mass is closer to Z than current candidate
                                        tmpDifFromZMass = abs(tmpDiElectronInvMass-ZMass)
                                        #Switching over variables
                                        if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
                                            print(i,j,"tmpDifFromZMass",tmpDifFromZMass)
                                        if tmpDifFromZMass < difFromZMassOneAr[ptCutItr]:
                                            if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
                                                print(i,j,"Electron pair has lowest current dif from Zmass. Old ZMassdif:",difFromZMassOneAr[ptCutItr])
                                            #Switching ZMassDif
                                            difFromZMassOneAr[ptCutItr] = tmpDifFromZMass
                                            #Switching pair indices
                                            lepPairOneLeadIndAr[ptCutItr] = tmpLeadInd
                                            lepPairOneTrailingIndAr[ptCutItr] = tmpSecondInd
                                            #Switching 4 vectors
                                            leadLepPairOneVecAr[ptCutItr] = tmpLeadVec
                                            trailingLepPairOneVecAr[ptCutItr] = tmpTrailingVec
                                            leadLepPairChargeAr[ptCutItr] = tmpLeadCharge
                                            trailingLepPairChargeAr[ptCutItr] = tmpTrailingCharge
        if debug and evCount == evToDebug:
            print("ELECTRON LOOP OVER")
            for ptCutItr,firstZLeadingPtCut in enumerate(firstZLeadingPtCutAr):
                if ptCutItr == ptCutToDebug:
                    print("ptCutItr",ptCutItr,"difFromZMassOneAr[ptCutItr]",difFromZMassOneAr[ptCutItr],"lepPairOneLeadIndAr[ptCutItr]",lepPairOneLeadIndAr[ptCutItr],"lepPairOneTrailingIndAr[ptCutItr]",lepPairOneTrailingIndAr[ptCutItr],"leadLepPairChargeAr[ptCutItr]",leadLepPairChargeAr[ptCutItr],"trailingLepPairChargeAr[ptCutItr]",trailingLepPairChargeAr[ptCutItr])

                    
        muonLeadingAr = [False for i in range(len(firstZLeadingPtCutAr))]
        muonPassesCutsAr = [[] for i in range(len(firstZLeadingPtCutAr))]
        muonPassesZ2CutsAr = []

        #Muons loop
        if debug and evCount == evToDebug:
            print("Entering muons loop")
        for i in range(tmpnMuon-1):
            if debug and evCount == evToDebug:
                print("Muon",i)
            #No cuts
            tmpPtOne = ev.Muon_pt[i]
            tmpEtaOne = ev.Muon_eta[i]
            tmpMassOne = ev.Muon_mass[i]
            tmpPhiOne = ev.Muon_phi[i]
            
            
            #First Z Cuts
            if enoughLepCands and enoughMuonCands:
                if debug and evCount == evToDebug:
                    print(i,"enough LepCands and MuonCands")
                #if not ifEnoughMuonCandBool:
                #    ifEnoughMuonCandCount += 1
                #    ifEnoughMuonCandBool = True
                
                #Looping over other muons
                if debug and evCount == evToDebug:
                    print(i,"Loop over remaining muons")
                for j in range(i+1,tmpnMuon):
                    if debug and evCount == evToDebug:
                        print("Muon",j)
                    #Check that muons have the opposite charge
                    tmpMuonCharge = ev.Muon_charge[i]
                    tmpMuonChargeTwo = ev.Muon_charge[j]
                    if tmpMuonCharge == - tmpMuonChargeTwo:
                        if debug and evCount == evToDebug:
                            print(i,j,"Muons have the opposite charge")
                        #Get vaariables from second electron
                        tmpPtTwo = ev.Muon_pt[j]
                        tmpEtaTwo = ev.Muon_eta[j]
                        if debug and evCount == evToDebug:
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
                        if debug and evCount == evToDebug:
                            print(i,j,"tmpLeadInd",tmpLeadInd,"tmpSecondInd",tmpSecondInd,"tmpMaxPtLead",tmpMaxPtLead,"tmpMaxPtSecond",tmpMaxPtSecond,"tmpLeadCharge",tmpLeadCharge,"tmpTrailingCharge",tmpTrailingCharge)
                        if debug and evCount == evToDebug:
                            print("tmpDiMuonInvMass",tmpDiMuonInvMass)
                        #if tmpDiMuonInvMass > leptonZ2Cut:
                        if tmpDiMuonInvMass > leptonInvMassCutLow and tmpDiMuonInvMass < leptonInvMassCutHigh:
                            if debug and evCount == evToDebug:
                                print(i,j,"Muon pair passed Z2 cut",leptonInvMassCutLow,leptonInvMassCutHigh)
                            muonPassesZ2CutsAr.append([[tmpLeadInd,tmpSecondInd],[tmpLeadVec,tmpTrailingVec],[tmpLeadCharge,tmpTrailingCharge]])
                        
                            #Check that the pt of the muons pass the lower pt cut
                            if tmpPtOne > firstZTrailingCut and tmpPtTwo > firstZTrailingCut:
                                if debug and evCount == evToDebug:
                                    print(i,j,"Both Muon trailing pt passed Z1 trailing cut",firstZTrailingCut)
                                #Sort the muons into leading and trailing based on pt
                                #Check that the lead muon passes the higher pt cut
                                for ptCutItr,firstZLeadingPtCut in enumerate(firstZLeadingPtCutAr):
                                    #uncomment to debug on every pt cut
                                    #ptCutToDebug = ptCutItr
                                    if tmpMaxPtLead > firstZLeadingPtCut:
                                        if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
                                            print(i,j,"Muon lead pt passed Z1 lead cut",firstZLeadingPtCut)
                                        if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
                                            print(i,j,"Muon pair passed Z1 inv mass cut",leptonInvMassCutLow,leptonInvMassCutHigh)
                                        if not ifZ1MuonPairCandBoolAr[ptCutItr]:
                                            ifZ1MuonPairCandCount[ptCutItr] += 1
                                            ifZ1MuonPairCandBoolAr[ptCutItr] = True
                                        muonPassesCutsAr[ptCutItr].append([tmpLeadInd,tmpSecondInd])
                                        #Check if the mass is closer to Z than current candidate
                                        tmpDifFromZMass = abs(tmpDiMuonInvMass-ZMass)
                                        #Switching over variables
                                        if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
                                            print(i,j,"tmpDifFromZMass",tmpDifFromZMass)
                                        if tmpDifFromZMass < difFromZMassOneAr[ptCutItr]:
                                            if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
                                                print(i,j,"Muon pair has lowest current dif from Zmass. Old ZMassdif:",difFromZMassOneAr[ptCutItr])
                                            muonLeadingAr[ptCutItr] = True
                                            #Switching ZMassDif
                                            #difFromZMassTwo = difFromZMassOne
                                            difFromZMassOneAr[ptCutItr] = tmpDifFromZMass
                                            #Switching pair indices
                                            #lepPairTwoLeadInd = lepPairOneLeadInd
                                            #lepPairTwoTrailingInd = lepPairOneTrailingIndAr[ptCutItr]
                                            lepPairOneLeadIndAr[ptCutItr] = tmpLeadInd
                                            lepPairOneTrailingIndAr[ptCutItr] = tmpSecondInd
                                            #Switching 4 vectors
                                            #leadLepPairTwoVec = leadLepPairOneVecAr[ptCutItr]
                                            #trailingLepPairTwoVec = trailingLepPairOneVecAr[ptCutItr]
                                            leadLepPairOneVecAr[ptCutItr] = tmpLeadVec
                                            trailingLepPairOneVecAr[ptCutItr] = tmpTrailingVec
                                            leadLepPairChargeAr[ptCutItr] = tmpLeadCharge
                                            trailingLepPairChargeAr[ptCutItr] = tmpTrailingCharge

        if debug and evCount == evToDebug:
            print("MUON LOOP OVER")
            for ptCutItr,firstZLeadingPtCut in enumerate(firstZLeadingPtCutAr):
                if ptCutItr == ptCutToDebug:
                    print("ptCutItr",ptCutItr,"difFromZMassOneAr[ptCutItr]",difFromZMassOneAr[ptCutItr],"lepPairOneLeadIndAr[ptCutItr]",lepPairOneLeadIndAr[ptCutItr],"lepPairOneTrailingIndAr[ptCutItr]",lepPairOneTrailingIndAr[ptCutItr],"leadLepPairChargeAr[ptCutItr]",leadLepPairChargeAr[ptCutItr],"trailingLepPairChargeAr[ptCutItr]",trailingLepPairChargeAr[ptCutItr],"muonLeadingAr[ptCutItr]",muonLeadingAr[ptCutItr])
            print("Going to find Z2 if Z1 has been found")
        for ptCutItr,firstZLeadingPtCut in enumerate(firstZLeadingPtCutAr):
            #uncomment to debug on every pt cut
            #ptCutToDebug = ptCutItr
            passesIsoCutsBool    = False
            allCutPassBool       = False
            leadZ2LepPairInd = -1
            leadZ2Pt = 0
            trailingZ2Pt = 0
            if lepPairOneLeadIndAr[ptCutItr] >= 0 and lepPairOneTrailingIndAr[ptCutItr] >= 0:
                if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
                    print(ptCutItr,"Z1 was found")
                ifZ1PairCandCount[ptCutItr] += 1
                passesCandCuts = False
                muonZ2Pair = False
                if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
                    print("len(muonPassesCutsAr[ptCutItr])",len(muonPassesCutsAr[ptCutItr]),"len(elecPassesCutsAr[ptCutItr])",len(elecPassesCutsAr[ptCutItr]),"len(muonPassesZ2CutsAr)",len(muonPassesZ2CutsAr),"len(elecPassesZ2CutsAr",len(elecPassesZ2CutsAr))
                if len(muonPassesCutsAr[ptCutItr]) + len(elecPassesCutsAr[ptCutItr]) > 0 and len(muonPassesZ2CutsAr) + len(elecPassesZ2CutsAr) - 1 > 0: #-1 for the lead Z1 pair
                    if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
                        print("Passed check for there being enough candidates for Z2")
                        print("entering loop on Electron Z2 candidates")
                    for i,elecZ2Cand in enumerate(elecPassesZ2CutsAr):
                        if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
                            print(i,"elecZ2Cand",elecZ2Cand)
                        if muonLeadingAr[ptCutItr] or (elecZ2Cand[0][0] != lepPairOneLeadIndAr[ptCutItr] and elecZ2Cand[0][0] != lepPairOneTrailingIndAr[ptCutItr] and elecZ2Cand[0][1] != lepPairOneLeadIndAr[ptCutItr] and elecZ2Cand[0][1] != lepPairOneTrailingIndAr[ptCutItr]):
                            if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
                                print("Passed the check that we aren't looking at the Z1 pair")
                            fourLepVec = elecZ2Cand[1][0] + elecZ2Cand[1][1] + leadLepPairOneVecAr[ptCutItr] + trailingLepPairOneVecAr[ptCutItr]
                            fourLepInvMass = fourLepVec.M()
                            if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
                                print("fourLepInvMass",fourLepInvMass)
                            if fourLepInvMass > fourLeptonInvMassCut:
                                if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
                                    print("passed four lepton invmass cut",fourLeptonInvMassCut)
                                passesCandCuts = True
                                if not muonLeadingAr[ptCutItr]:
                                    if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
                                        print("not muonLeadingAr[ptCutItr]. checking 4 e cuts")
                                    passesCandCuts = False
                                    if elecZ2Cand[2][0] != leadLepPairChargeAr[ptCutItr]:
                                        if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
                                            print("elecZ2Can[2][0] != leadLepPairChargeAr[ptCutItr]","elecZ2Can[2][0]",elecZ2Cand[2][0],"leadLepPairChargeAr[ptCutItr]",leadLepPairChargeAr[ptCutItr])
                                        tmpCrossCandVec = elecZ2Cand[1][0] + leadLepPairOneVecAr[ptCutItr]
                                        if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
                                            print("tmpCrossCandVec = elecZ2Cand[1][0] + leadLepPairOneVecAr[ptCutItr]",tmpCrossCandVec)
                                            print("tmpCrossCandVec.M()",tmpCrossCandVec.M())
                                        if tmpCrossCandVec.M() > leptonInvMassCutTwo:
                                            if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
                                                print("passed check that the invmass is > leptonInvMassCutTwo")
                                            passesCandCuts = True
                                        else:
                                            tmpCrossCandVec = elecZ2Cand[1][1] + trailingLepPairOneVecAr[ptCutItr]
                                            if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
                                                print("Less than leptonInvMassCutTwo so trying other electron electron combination")
                                                print("tmpCrossCandVec = elecZ2Cand[1][1] + trailingLepPairOneVecAr[ptCutItr]",tmpCrossCandVec)
                                                print("tmpCrossCandVec.M()",tmpCrossCandVec.M())
                                            if tmpCrossCandVec.M() > leptonInvMassCutTwo:
                                                if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
                                                        print("passed check that the invmass is > leptonInvMassCutTwo")
                                                passesCandCuts = True
                                    else:
                                        if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
                                            print("elecZ2Can[2][0] == leadLepPairChargeAr[ptCutItr]","elecZ2Can[2][0]",elecZ2Cand[2][0],"leadLepPairChargeAr[ptCutItr]",leadLepPairChargeAr[ptCutItr])
                                        tmpCrossCandVec = elecZ2Cand[1][1] + leadLepPairOneVecAr[ptCutItr]
                                        if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
                                            print("tmpCrossCandVec = elecZ2Cand[1][1] + leadLepPairOneVecAr[ptCutItr]",tmpCrossCandVec)
                                            print("tmpCrossCandVec.M()",tmpCrossCandVec.M())
                                        if tmpCrossCandVec.M() > leptonInvMassCutTwo:
                                            if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
                                                print("passed check that the invmass is > leptonInvMassCutTwo")
                                            passesCandCuts = True
                                        else:
                                            tmpCrossCandVec = elecZ2Cand[1][0] + trailingLepPairOneVecAr[ptCutItr]
                                            if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
                                                print("Less than leptonInvMassCutTwo so trying other electron electron combination")
                                                print("tmpCrossCandVec = elecZ2Cand[1][0] + trailingLepPairOneVecAr[ptCutItr]",tmpCrossCandVec)
                                                print("tmpCrossCandVec.M()",tmpCrossCandVec.M())
                                            if tmpCrossCandVec.M() > leptonInvMassCutTwo:
                                                if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
                                                    print("passed check that the invmass is > leptonInvMassCutTwo")
                                                passesCandCuts = True
                                if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
                                    print("checking if passed potential 4e cut","passesCandCuts",passesCandCuts)
                                if passesCandCuts:
                                    if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
                                        print("passed cut. Checking for highest Pt in lead of Z2")
                                    if not ifZ2ElecPairCandBoolAr[ptCutItr]:
                                        ifZ2ElecPairCandCount[ptCutItr] += 1
                                        ifZ2ElecPairCandBoolAr[ptCutItr] = True
                                    if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
                                        print("elecZ2Cand[1][0].Pt()",elecZ2Cand[1][0].Pt())
                                    if elecZ2Cand[1][0].Pt() > leadZ2Pt:
                                        if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
                                            print("New highest pt found. Old pt:",leadZ2Pt)
                                        leadZ2Pt = elecZ2Cand[1][0].Pt()
                                        trailingZ2Pt = elecZ2Cand[1][1].Pt()
                                        leadZ2LepPairInd = i
                                    elif elecZ2Cand[1][0].Pt() == leadZ2Pt:
                                        if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
                                            print("Highest pt equal. checking trailing Z2 pt")
                                        if elecZ2Cand[1][1].Pt() == trailingZ2Pt:
                                            if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
                                                print("New highest trailing pt found. Old pt:",trailingZ2Pt)
                                            trailingZ2Pt = elecZ2Cand[1][1].Pt()
                                            leadZ2LepPairInd = i
                    if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
                        print("ELECTRON Z2 LOOP FINISHED")
                        print("leadZ2LepPairInd",leadZ2LepPairInd,"leadZ2Pt",leadZ2Pt,"trailingZ2Pt",trailingZ2Pt)


                    for i,muonZ2Cand in enumerate(muonPassesZ2CutsAr):
                        if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
                            print(i,"muonZ2Cand",muonZ2Cand)
                        if not muonLeadingAr[ptCutItr] or (muonZ2Cand[0][0] != lepPairOneLeadIndAr[ptCutItr] and muonZ2Cand[0][0] != lepPairOneTrailingIndAr[ptCutItr] and muonZ2Cand[0][1] != lepPairOneLeadIndAr[ptCutItr] and muonZ2Cand[0][1] != lepPairOneTrailingIndAr[ptCutItr]): 
                            if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
                                print("Passed the check that we aren't looking at the Z1 pair")
                            fourLepVec = muonZ2Cand[1][0] + muonZ2Cand[1][1] + leadLepPairOneVecAr[ptCutItr] + trailingLepPairOneVecAr[ptCutItr]
                            fourLepInvMass = fourLepVec.M()
                            if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
                                print("fourLepInvMass",fourLepInvMass)
                            if fourLepInvMass > fourLeptonInvMassCut:
                                if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
                                    print("passed four lepton invmass cut",fourLeptonInvMassCut)
                                passesCandCuts = True
                                if muonLeadingAr[ptCutItr]:
                                    if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
                                        print("muonLeadingAr[ptCutItr]. checking 4 e cuts")
                                    passesCandCuts = False
                                    if muonZ2Cand[2][0] != leadLepPairChargeAr[ptCutItr]:
                                        if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
                                            print("muonZ2Can[2][0] != leadLepPairChargeAr[ptCutItr]","muonZ2Can[2][0]",muonZ2Cand[2][0],"leadLepPairChargeAr[ptCutItr]",leadLepPairChargeAr[ptCutItr])
                                        tmpCrossCandVec = muonZ2Cand[1][0] + leadLepPairOneVecAr[ptCutItr]
                                        if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
                                            print("tmpCrossCandVec = muonZ2Cand[1][0] + leadLepPairOneVecAr[ptCutItr]",tmpCrossCandVec)
                                            print("tmpCrossCandVec.M()",tmpCrossCandVec.M())
                                        if tmpCrossCandVec.M() > leptonInvMassCutTwo:
                                            if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
                                                print("passed check that the invmass is > leptonInvMassCutTwo")
                                            passesCandCuts = True
                                        else:
                                            
                                            tmpCrossCandVec = muonZ2Cand[1][1] + trailingLepPairOneVecAr[ptCutItr]
                                            if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
                                                print("Less than leptonInvMassCutTwo so trying other muon muon combination")
                                                print("tmpCrossCandVec = muonZ2Cand[1][1] + trailingLepPairOneVecAr[ptCutItr]",tmpCrossCandVec)
                                                print("tmpCrossCandVec.M()",tmpCrossCandVec.M())
                                            if tmpCrossCandVec.M() > leptonInvMassCutTwo:
                                                if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
                                                    print("passed check that the invmass is > leptonInvMassCutTwo")
                                                passesCandCuts = True
                                    else:
                                        if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
                                            print("muonZ2Can[2][0] == leadLepPairChargeAr[ptCutItr]","muonZ2Can[2][0]",muonZ2Cand[2][0],"leadLepPairChargeAr[ptCutItr]",leadLepPairChargeAr[ptCutItr])
                                        tmpCrossCandVec = muonZ2Cand[1][1] + leadLepPairOneVecAr[ptCutItr]
                                        if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
                                            print("tmpCrossCandVec = muonZ2Cand[1][1] + leadLepPairOneVecAr[ptCutItr]",tmpCrossCandVec)
                                            print("tmpCrossCandVec.M()",tmpCrossCandVec.M())
                                        if tmpCrossCandVec.M() > leptonInvMassCutTwo:
                                            if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
                                                print("passed check that the invmass is > leptonInvMassCutTwo")
                                            passesCandCuts = True
                                            
                                        else:
                                            tmpCrossCandVec = muonZ2Cand[1][0] + trailingLepPairOneVecAr[ptCutItr]
                                            if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
                                                print("Less than leptonInvMassCutTwo so trying other muon muon combination")
                                                print("tmpCrossCandVec = muonZ2Cand[1][0] + trailingLepPairOneVecAr[ptCutItr]",tmpCrossCandVec)
                                                print("tmpCrossCandVec.M()",tmpCrossCandVec.M())
                                            if tmpCrossCandVec.M() > leptonInvMassCutTwo:
                                                if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
                                                    print("passed check that the invmass is > leptonInvMassCutTwo")
                                                passesCandCuts = True
                                if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
                                    print("checking if passed potential 4e cut","passesCandCuts",passesCandCuts)
                                if passesCandCuts:
                                    if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
                                        print("passed cut. Checking for highest Pt in lead of Z2")
                                    if not ifZ2MuonPairCandBoolAr[ptCutItr]:
                                        ifZ2MuonPairCandCount[ptCutItr] += 1
                                        ifZ2MuonPairCandBoolAr[ptCutItr] = True
                                    if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
                                        print("muonZ2Cand[1][0].Pt()",muonZ2Cand[1][0].Pt())
                                    if muonZ2Cand[1][0].Pt() > leadZ2Pt:
                                        if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
                                            print("New highest pt found. Old pt:",leadZ2Pt)
                                        muonZ2Pair = True
                                        leadZ2Pt = muonZ2Cand[1][0].Pt()
                                        trailingZ2Pt = muonZ2Cand[1][1].Pt()
                                        leadZ2LepPairInd = i
                                    elif muonZ2Cand[1][0].Pt() == leadZ2Pt:
                                        if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
                                            print("Highest pt equal. checking trailing Z2 pt")
                                        if muonZ2Cand[1][1].Pt() == trailingZ2Pt:
                                            if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
                                                print("New highest trailing pt found. Old pt:",trailingZ2Pt)
                                            muonZ2Pair = True
                                            trailingZ2Pt = muonZ2Cand[1][1].Pt()
                                            leadZ2LepPairInd = i
                #At this point, if the cuts were passed, should have two pairs of leptons. The first reprsented by
                #lepPairOneLeadIndAr[ptCutItr],lepPairOneTrailingIndAr[ptCutItr] variables (also lead/trailingLepPairOneVecAr[ptCutItr] and lead/trailingLepPairChargeAr[ptCutItr])
                #which can be used to index ev.Electron/Muon_Branch
                #The second represented by 
                #leadZ2LepPairInd which can be used to index elec/muonPassesZ2CutsAr
                #which contains the indices for accessing the ev.Electron/Muon_branch, the four vector, and the charge)
                #So first check that the cuts were passed:
                if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
                    print("MUON Z2 LOOP FINISHED")
                    print("muonZ2Pair",muonZ2Pair,"leadZ2LepPairInd",leadZ2LepPairInd,"leadZ2Pt",leadZ2Pt,"trailingZ2Pt",trailingZ2Pt)
                    print("now checking if the Z2 cuts were passed")
                if leadZ2LepPairInd >= 0:
                    ifZ1Z2LepPairCandCount[ptCutItr] += 1
                    if muonZ2Pair:
                        if muonLeadingAr[ptCutItr]:
                            ifZ1Z2PairAllMuonCount[ptCutItr] += 1
                        else:
                            ifZ1ElecZ2MuonCount[ptCutItr] += 1
                    elif muonLeadingAr[ptCutItr]:
                        ifZ1MuonZ2ElecCount[ptCutItr] += 1
                    else:
                        ifZ1Z2PairAllElecCount[ptCutItr] += 1
                    if debug and evCount == evToDebug and ptCutItr == ptCutToDebug:
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
                    for isoItr,isoCut in enumerate(isoCutAr):
                        #uncomment to debug on every iso cut
                        #isoCutToDebug = isoItr
                        passesIsoCuts = True
                        
                        muonOrNotAr = [muonLeadingAr[ptCutItr],muonZ2Pair]
                        if debug and evCount == evToDebug and ptCutItr == ptCutToDebug and isoItr == isoCutToDebug:
                            print("muonOrNotAr",muonOrNotAr)
                        passesPtCutAr = [True,True,True,True]
                        Z1Z2VecPtAr = []
                        Z1Z2VecPtAr.append(leadLepPairOneVecAr[ptCutItr].Pt())
                        Z1Z2VecPtAr.append(trailingLepPairOneVecAr[ptCutItr].Pt())
                        Z1Z2IndAr = [lepPairOneLeadIndAr[ptCutItr],lepPairOneTrailingIndAr[ptCutItr],leadZ2LepPairInd,leadZ2LepPairInd]
                        #Previously used passesPtCutAr to bypass the cuts if the Pt was less than 35,
                        #but now just using it to switch different types of isolation used in the cuts for electrons
                        for i in range(4):
                            if i < 2: 
                                if muonLeadingAr[ptCutItr]:
                                    continue
                                elif Z1Z2VecPtAr[i] < 35:
                                    passesPtCutAr[i] = False
                            elif muonZ2Pair:
                                Z1Z2VecPtAr.append(muonPassesZ2CutsAr[leadZ2LepPairInd][1][i-2].Pt())
                            else:
                                Z1Z2VecPtAr.append(elecPassesZ2CutsAr[leadZ2LepPairInd][1][i-2].Pt())
                                if Z1Z2VecPtAr[i] < 35:
                                    passesPtCutAr[i] = False

            

                        if debug and evCount == evToDebug and ptCutItr == ptCutToDebug and isoItr == isoCutToDebug:
                            print("Z1Z2VecPtAr",Z1Z2VecPtAr,"Z1Z2IndAr",Z1Z2IndAr,"passesPtCutAr",passesPtCutAr)

                        for i,Z1Z2Ind in enumerate(Z1Z2IndAr[:-1):
                            for j in range(i+1,len(Z1Z2IndAr)):
                                Z1Z2IndTwo = Z1Z2IndAr[j]
                                if debug and evCount == evToDebug and ptCutItr == ptCutToDebug and isoItr == isoCutToDebug:
                                    print(i,j,"muonLeadingAr[ptCutItr]",muonLeadingAr[ptCutItr],"muonZ2Pair",muonZ2Pair,"Z1Z2Ind",Z1Z2Ind,"Z1Z2IndTwo",Z1Z2IndTwo)
                                #Getting indices for accessing the different arrays for Z1
                                tmpIsMuonOne = True
                                if i < 2:
                                    tmpIsoOneInd = Z1Z2Ind
                                    if not muonLeadingAr[ptCutItr]:
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
                                    if not muonLeadingAr[ptCutItr]:
                                        tmpIsMuonTwo = False
                                elif muonZ2Pair:
                                    tmpIsoTwoInd = muonPassesZ2CutsAr[Z1Z2IndTwo][0][j-2]
                                else:
                                    tmpIsoTwoInd = elecPassesZ2CutsAr[Z1Z2IndTwo][0][j-2]
                                    tmpIsMuonTwo = False
                                if debug and evCount == evToDebug and ptCutItr == ptCutToDebug and isoItr == isoCutToDebug:
                                    print(i,j,"tmpIsoOneInd",tmpIsoOneInd,"tmpIsoTwoInd",tmpIsoTwoInd)
                                #Getting tmpIsoOne
                                if tmpIsMuonOne:
                                    tmpIsoOne = ev.Muon_pfRelIso03_all[tmpIsoOneInd]
                                elif passesPtCutAr[i]:
                                    if abs(ev.Electron_eta[tmpIsoOneInd]) < 1.4:
                                        if debug and evCount == evToDebug and ptCutItr == ptCutToDebug and isoItr == isoCutToDebug:
                                            print("electron in barrel")
                                        tmpAdd = max(0., ev.Electron_dr03EcalRecHitSumEt[tmpIsoOneInd] - 1.)
                                    else:
                                        if debug and evCount == evToDebug and ptCutItr == ptCutToDebug and isoItr == isoCutToDebug:
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
                                        if debug and evCount == evToDebug and ptCutItr == ptCutToDebug and isoItr == isoCutToDebug:
                                            print("electron in barrel")
                                        tmpAdd = max(0., ev.Electron_dr03EcalRecHitSumEt[tmpIsoTwoInd] - 1.)
                                    else:
                                        if debug and evCount == evToDebug and ptCutItr == ptCutToDebug and isoItr == isoCutToDebug:
                                            print("electron in endcap")
                                        tmpAdd = ev.Electron_dr03EcalRecHitSumEt[tmpIsoTwoInd]
                                    tmpIsoTwo = ( ev.Electron_dr03TkSumPt[tmpIsoTwoInd] + tmpAdd + ev.Electron_dr03HcalDepth1TowerSumEt[tmpIsoTwoInd] ) / ev.Electron_pt[tmpIsoTwoInd]
                                else:
                                    tmpIsoTwo = ev.Electron_pfRelIso03_all[tmpIsoTwoInd]
                                if debug and evCount == evToDebug and ptCutItr == ptCutToDebug and isoItr == isoCutToDebug:
                                    print(i,j,"tmpIsoOne",tmpIsoOne,"tmpIsoTwo",tmpIsoTwo)
                                if tmpIsoOne + tmpIsoTwo > 0.35:
                                    if debug and evCount == evToDebug and ptCutItr == ptCutToDebug and isoItr == isoCutToDebug:
                                        print(i,j,"summed isos > 0.35. cuts not passed")
                                    passesIsoCuts = False
                                


                                
                                    
                        if debug and evCount == evToDebug and ptCutItr == ptCutToDebug and isoItr == isoCutToDebug:
                            print("FINISHED WITH ISO CUTS","passesIsoCuts",passesIsoCuts)



                        #Now, assuming all *these* cuts pass, on to cut 6.
                        #Want the SIP of the leptons
                        
                        if passesIsoCuts:
                            if debug and evCount == evToDebug and ptCutItr == ptCutToDebug and isoItr == isoCutToDebug:
                                print("passed iso cuts. Starting SIP cuts")
                            if not passesIsoCutsBool:
                                passesIsoCutsCount[isoItr][ptCutItr] += 1
                                passesIsoCutsBool = True

                            passesSIPCut = True
                            if muonLeadingAr[ptCutItr]:
                                if debug and evCount == evToDebug and ptCutItr == ptCutToDebug and isoItr == isoCutToDebug:
                                    print("muonLeadingAr[ptCutItr]",muonLeadingAr[ptCutItr])
                                if muonZ2Pair:
                                    if debug and evCount == evToDebug and ptCutItr == ptCutToDebug and isoItr == isoCutToDebug:
                                        print("muonZ2Pair",muonZ2Pair)
                                        print("ev.Muon_sip3d[lepPairOneLeadIndAr[ptCutItr]]",ev.Muon_sip3d[lepPairOneLeadIndAr[ptCutItr]],"ev.Muon_sip3d[lepPairOneTrailingIndAr[ptCutItr]]",ev.Muon_sip3d[lepPairOneTrailingIndAr[ptCutItr]])
                                        print("ev.Muon_sip3d[muonPassesZ2CutsAr[leadZ2LepPairInd][0][0]]",ev.Muon_sip3d[muonPassesZ2CutsAr[leadZ2LepPairInd][0][0]],"ev.Muon_sip3d[muonPassesZ2CutsAr[leadZ2LepPairInd][0][1]]",ev.Muon_sip3d[muonPassesZ2CutsAr[leadZ2LepPairInd][0][1]])
                                    if ev.Muon_sip3d[lepPairOneLeadIndAr[ptCutItr]] > 4:
                                        passesSIPCut = False
                                    elif ev.Muon_sip3d[lepPairOneTrailingIndAr[ptCutItr]] > 4:
                                        passesSIPCut = False
                                    elif ev.Muon_sip3d[muonPassesZ2CutsAr[leadZ2LepPairInd][0][0]] > 4:
                                        passesSIPCut = False
                                    elif ev.Muon_sip3d[muonPassesZ2CutsAr[leadZ2LepPairInd][0][1]] > 4:
                                        passesSIPCut = False
                                    if debug and evCount == evToDebug and ptCutItr == ptCutToDebug and isoItr == isoCutToDebug:
                                        print("passesSIPCut",passesSIPCut)
                                else:
                                    if debug and evCount == evToDebug and ptCutItr == ptCutToDebug and isoItr == isoCutToDebug:
                                        print("muonZ2Pair",muonZ2Pair)
                                        print("ev.Muon_sip3d[lepPairOneLeadIndAr[ptCutItr]]",ev.Muon_sip3d[lepPairOneLeadIndAr[ptCutItr]],"ev.Muon_sip3d[lepPairOneTrailingIndAr[ptCutItr]]",ev.Muon_sip3d[lepPairOneTrailingIndAr[ptCutItr]])
                                        print("ev.Electron_sip3d[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]]",ev.Electron_sip3d[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]],"ev.Electron_sip3d[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]]",ev.Electron_sip3d[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]])
                                    if ev.Muon_sip3d[lepPairOneLeadIndAr[ptCutItr]] > 4:
                                        passesSIPCut = False
                                    elif ev.Muon_sip3d[lepPairOneTrailingIndAr[ptCutItr]] > 4:
                                        passesSIPCut = False
                                    elif ev.Electron_sip3d[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]] > 4:
                                        passesSIPCut = False
                                    elif ev.Electron_sip3d[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]] > 4:
                                        passesSIPCut = False
                                    if debug and evCount == evToDebug and ptCutItr == ptCutToDebug and isoItr == isoCutToDebug:
                                        print("passesSIPCut",passesSIPCut)
                            elif muonZ2Pair:
                                if debug and evCount == evToDebug and ptCutItr == ptCutToDebug and isoItr == isoCutToDebug:
                                    print("muonLeadingAr[ptCutItr]",muonLeadingAr[ptCutItr])
                                    print("muonZ2Pair",muonZ2Pair)
                                    print("ev.Electron_sip3d[lepPairOneLeadIndAr[ptCutItr]]",ev.Electron_sip3d[lepPairOneLeadIndAr[ptCutItr]],"ev.Electron_sip3d[lepPairOneTrailingIndAr[ptCutItr]]",ev.Electron_sip3d[lepPairOneTrailingIndAr[ptCutItr]])
                                    print("ev.Muon_sip3d[muonPassesZ2CutsAr[leadZ2LepPairInd][0][0]]",ev.Muon_sip3d[muonPassesZ2CutsAr[leadZ2LepPairInd][0][0]],"ev.Muon_sip3d[muonPassesZ2CutsAr[leadZ2LepPairInd][0][1]]",ev.Muon_sip3d[muonPassesZ2CutsAr[leadZ2LepPairInd][0][1]])
                                #print("lepPairOneLeadInd",lepPairOneLeadInd,"len(ev.Electron_sip3d)",len(ev.Electron_sip3d))
                                #print("len(ev.Electron_pt)",len(ev.Electron_pt))
                                #print("nElecCandidates",nElecCandidates,"nMuonCandidates",nMuonCandidates,"enoughLepCands",enoughLepCands,"enoughElecCands",enoughElecCands,"enoughMuonCands",enoughMuonCands)
                                #print("leadLepPairOneVecAr[ptCutItr]",leadLepPairOneVecAr[ptCutItr],"trailingLepPairOneVecAr[ptCutItr]",trailingLepPairOneVecAr[ptCutItr])
                                #print("muonLeadingAr[ptCutItr]",muonLeadingAr[ptCutItr],"muonZ2Pair",muonZ2Pair)
                                #print()
                                if ev.Electron_sip3d[lepPairOneLeadIndAr[ptCutItr]] > 4:
                                    passesSIPCut = False
                                elif ev.Electron_sip3d[lepPairOneTrailingIndAr[ptCutItr]] > 4:
                                    passesSIPCut = False
                                elif ev.Muon_sip3d[muonPassesZ2CutsAr[leadZ2LepPairInd][0][0]] > 4:
                                    passesSIPCut = False
                                elif ev.Muon_sip3d[muonPassesZ2CutsAr[leadZ2LepPairInd][0][1]] > 4:
                                    passesSIPCut = False
                                if debug and evCount == evToDebug and ptCutItr == ptCutToDebug and isoItr == isoCutToDebug:
                                    print("passesSIPCut",passesSIPCut)
                            else:
                                if debug and evCount == evToDebug and ptCutItr == ptCutToDebug and isoItr == isoCutToDebug:
                                    print("muonLeadingAr[ptCutItr]",muonLeadingAr[ptCutItr])
                                    print("muonZ2Pair",muonZ2Pair)
                                    print("ev.Electron_sip3d[lepPairOneLeadIndAr[ptCutItr]]",ev.Electron_sip3d[lepPairOneLeadIndAr[ptCutItr]],"ev.Electron_sip3d[lepPairOneTrailingIndAr[ptCutItr]]",ev.Electron_sip3d[lepPairOneTrailingIndAr[ptCutItr]])
                                    print("ev.Electron_sip3d[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]]",ev.Electron_sip3d[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]],"ev.Electron_sip3d[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]]",ev.Electron_sip3d[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]])
                                if ev.Electron_sip3d[lepPairOneLeadIndAr[ptCutItr]] > 4:
                                    passesSIPCut = False
                                elif ev.Electron_sip3d[lepPairOneTrailingIndAr[ptCutItr]] > 4:
                                    passesSIPCut = False
                                elif ev.Electron_sip3d[elecPassesZ2CutsAr[leadZ2LepPairInd][0][0]] > 4:
                                    passesSIPCut = False
                                elif ev.Electron_sip3d[elecPassesZ2CutsAr[leadZ2LepPairInd][0][1]] > 4:
                                    passesSIPCut = False
                                if debug and evCount == evToDebug and ptCutItr == ptCutToDebug and isoItr == isoCutToDebug:
                                    print("passesSIPCut",passesSIPCut)
                            #Now just check that the Z1 and Z2 inv mass falls within the Z low and Z high cuts
                            if passesSIPCut:

                                if debug and evCount == evToDebug and ptCutItr == ptCutToDebug and isoItr == isoCutToDebug:
                                    print("passed SIP Cut, and thus all cuts")
                                
                                if not allCutPassBool:
                                    allCutPassCount[isoItr][ptCutItr] += 1
                                    allCutPassBool = True
                     
        #Increment event count
        evCount += 1

print("Finished file loop.","time:",time.time()-startt)
#Writing different counters to output file:
outputFile = open("leptonIsoPtCutOptimizationResults{0}".format(saveName),"w")
if evCount>0:
    outputFile.write("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"+"\n")
    
    elecCandRatio   = (ifEnoughElecCandCount/evCount)*100
    muonCandRatio   = (ifEnoughMuonCandCount/evCount)*100
    lepCandRatio    = (ifEnoughLepCandCount/evCount)*100
    outputFile.write("Number of events with at least one electron candidate pair: "+str(ifEnoughElecCandCount)+" ("+str(elecCandRatio)+")"+"\n")
    outputFile.write("Number of events with at least one muon candidate pair: "+str(ifEnoughMuonCandCount)+" ("+str(muonCandRatio)+")"+"\n")
    outputFile.write("Number of events with enough lepton candidates: "+str(ifEnoughLepCandCount)+" ("+str(lepCandRatio)+")"+"\n")
    for l in range(ptCutsLen):
        outputFile.write("----------------------------- "+"for cut number "+str(l)+" "+str(firstZLeadingPtCutAr[l])+" -----------------------------"+"\n")
        if ifEnoughLepCandCount>0:
            Z1Ratio             = (ifZ1PairCandCount[l]/ifEnoughLepCandCount)*100
            if ifEnoughElecCandCount>0:
                Z1ElecPairRatio = (ifZ1ElecPairCandCount[l]/ifEnoughElecCandCount)*100
            else:
                Z1ElecPairRatio = 0
            if ifEnoughMuonCandCount>0:
                Z1MuonPairRatio = (ifZ1MuonPairCandCount[l]/ifEnoughMuonCandCount)*100
            else:
                Z1MuonPairRatio = 0
            outputFile.write("Number of events with at least one Z1 electron pair: "+str(ifZ1ElecPairCandCount[l])+" ("+str(Z1ElecPairRatio)+")"+"\n")
            outputFile.write("Number of events with at least one Z1 muon pair: "+str(ifZ1MuonPairCandCount[l])+" ("+str(Z1MuonPairRatio)+")"+"\n")
            outputFile.write("Number of events with at least one Z1 pair: "+str(ifZ1PairCandCount[l])+" ("+str(Z1Ratio)+")"+"\n")
            if ifZ1PairCandCount[l]>0:
                Z1Z2PairRatio   = (ifZ1Z2LepPairCandCount[l]/ifZ1PairCandCount[l])*100
                Z2ElecPairRatio = (ifZ2ElecPairCandCount[l]/ifZ1PairCandCount[l])*100
                Z2MuonPairRatio = (ifZ2MuonPairCandCount[l]/ifZ1PairCandCount[l])*100
                outputFile.write("Number of events with a Z1 pair and also at least one Z2 Electron pair: "+str(ifZ2ElecPairCandCount[l])+" ("+str(Z2ElecPairRatio)+")"+"\n")
                outputFile.write("Number of events with a Z1 pair and also at least one Z2 Muon pair: "+str(ifZ2MuonPairCandCount[l])+" ("+str(Z2MuonPairRatio)+")"+"\n")
                outputFile.write("Number of events with a Z1Z2 pair: "+str(ifZ1Z2LepPairCandCount[l])+" ("+str(Z1Z2PairRatio)+")"+"\n")
                
                Z1Z2PairAllElecRatio = (ifZ1Z2PairAllElecCount[l]/ifZ1PairCandCount[l])*100
                Z1Z2PairAllMuonRatio = (ifZ1Z2PairAllMuonCount[l]/ifZ1PairCandCount[l])*100
                Z1ElecZ2MuonRatio    = (ifZ1ElecZ2MuonCount[l]/ifZ1PairCandCount[l])*100
                Z1MuonZ2ElecRatio    = (ifZ1MuonZ2ElecCount[l]/ifZ1PairCandCount[l])*100
                outputFile.write("Number of events with a Z1Z2 pair both elec: "+str(ifZ1Z2PairAllElecCount[l])+" ("+str(Z1Z2PairAllElecRatio)+")"+"\n")
                outputFile.write("Number of events with a Z1Z2 pair both muon: "+str(ifZ1Z2PairAllMuonCount[l])+" ("+str(Z1Z2PairAllMuonRatio)+")"+"\n")
                outputFile.write("Number of events with a Z1 elec Z2 muon pair: "+str(ifZ1ElecZ2MuonCount[l])+" ("+str(Z1ElecZ2MuonRatio)+")"+"\n")
                outputFile.write("Number of events with a Z1 muon Z2 elec pair: "+str(ifZ1MuonZ2ElecCount[l])+" ("+str(Z1MuonZ2ElecRatio)+")"+"\n")
                if ifZ1Z2LepPairCandCount[l]>0:
                    for isoItr in range(isoCutsLen):
                        outputFile.write("............................ " + "for iso cut number " + str(isoItr) + " " + str(isoCutAr[isoItr]) + " .............................."+"\n")
                        passesIsoCutsRatio   = (passesIsoCutsCount[isoItr][l]/ifZ1Z2LepPairCandCount[l])*100
                        outputFile.write("Number of events with at least one Z1Z2 pair passing iso cuts: "+str(passesIsoCutsCount[isoItr][l])+" ("+str(passesIsoCutsRatio)+")"+"\n")
                        if passesIsoCutsCount[isoItr][l]>0:
                            allCutPassRatio   = (allCutPassCount[isoItr][l]/passesIsoCutsCount[isoItr][l])*100
                            outputFile.write("Number of events with at least one Z1Z2 pair passing all cuts: "+str(allCutPassCount[isoItr][l])+" ("+str(allCutPassRatio)+")"+"\n")
        outputFile.write("----------------------------------------------------------"+"\n")
else:
    outputFile.write("There were no events here...")

outputFile.close()

#General stuff:
print("Done.","time:",time.time()-startt)


