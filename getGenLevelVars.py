from ROOT import TFile, TChain, gDirectory, TApplication, TMath, Math, TMinuit, TROOT, TSystem, TVector2, TObject
# You probably also want to import TH1D and TCanvas,
# unless you're not making any histograms.
from ROOT import TH1F, TCanvas, TF1, TGraph, TGraphErrors, TLegend, TLine, TPaveText, TStyle
from ROOT import TH2D, TH2F
from math import sqrt,pi
from fileLists import MGEFTAr
from fileLists import MGSMAr
from getGenLevelVars_Functions import *


import time as time






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
    saveName = "EFT"
    
    for fileName in MGEFTAr:
        fileAr.append("/scratch365/dlutton/NanoAODFiles/pphzzjjQCD0SMHLOOP0NPE1NPcHWE1QEDE5/"+fileName)
elif MGSM:
    saveName = "SM"
    
    for fileName in MGSMAr:
        fileAr.append("/scratch365/dlutton/NanoAODFiles/pphzzjjQCD0SMHLOOP0QEDE5NPE0/"+fileName)
elif testRun:
    saveName = "testRun"
    fileAr.append("./unweighted_eventspphzzjjQCD0SMHLOOP0NPE1NPcHWE1QEDE5ResMasAllVer100Ev10080Seed_0p999cHW100GeVIMJetCut_200.root")
elif LaraTest:
    saveName = "LaraTest"
    fileAr.append("/scratch365/dlutton/NanoAODFiles/pp_hwpwmjj_EFT_VBF_chw_09999000_250k.root")
else:
    print("ERROR. NO INPUT DATASET NAME GIVEN")

#Setting up outfile for tree
outFile = TFile("genLevelVarsFrom{0}.root".format(saveName),"recreate")


#Currently doesn't take into account intermediary particles really. should update at some point
#Can look at old AnalyzeNanoAODFilesWithPyRoot.py script to see how I dealt with this previously
def getInitialMother(ev,genPartInd):
    momFound = False
    motherAr = []
    tmpMomInd = ev.GenPart_genPartIdxMother[genPartInd]
    while not momFound:
        motherAr.append(ev.GenPart_pdgId[tmpMomInd])
        tmpMomInd = ev.GenPart_genPartIdxMother[tmpMomInd]
        if tmpMomInd == -1 or tmpMomInd == 0:
            momFound = True
    return motherAr[-1]




crossSectionAvg = 0
crossSectionCtr = 0
evRunOver = 0
evCount = 0
evPassCount = 0
print("Going into file loop.","time:",time.time()-startt)
for k,fileName in enumerate(fileAr):
    if endAfter and evCount > NToEnd:
        break
    if debug:
        print("File:    ",fileName)
    #Open the file, get the Events tree
    tmpfile = TFile.Open(fileName)
    outFile.cd()
    mytree = tmpfile.Events
    runTree = tmpfile.Runs
    #Getting the cross section
    #For background it's precalculated
    crossSection = 0
    for i,runEv in enumerate(runTree):
        #if i > 0:
        #    print("uhoh it has two",i,k,fileName)
        crossSection +=runEv.genEventSumw / runEv.genEventCount
    crossSection = crossSection / (i+1)
    crossSectionAvg += crossSection
    crossSectionCtr += 1
    if k % 10 == 0:
        print("Going into event loop for file {0}.".format(k),"time:",time.time()-startt)

    #EvLoop
    for ev in mytree:
        if debug:
            print("-------------------------")
            print(evCount+1," starting Z loop")
        if endAfter:
            if evCount < NToStart:
                evCount += 1
                continue
            if evCount > NToEnd:
                break
        if evCount % 1000 == 0:
            print("Event: "+str(evCount))
        #Increment event count
        evRunOver += 1
        evCount += 1
        
        #Gen variables
        ZOne_pt = 0
        ZTwo_pt = 0
        ZOne_eta = 0
        ZTwo_eta = 0
        H_pt = 0
        H_eta = 0

        JOne_pt = 0
        JTwo_pt = 0
        JOne_eta = 0
        JTwo_eta = 0

        JOne_invmass = 0
        JTwo_invmass = 0
        JPair_invmass = 0

        J_etasep = 0

        GenFound = False

        #From LHE variables
        ZOne_pt_FromLHE = 0
        ZTwo_pt_FromLHE = 0
        ZOne_eta_FromLHE = 0
        ZTwo_eta_FromLHE = 0
        H_pt_FromLHE = 0
        H_eta_FromLHE = 0

        JOne_pt_FromLHE = 0
        JTwo_pt_FromLHE = 0
        JOne_eta_FromLHE = 0
        JTwo_eta_FromLHE = 0

        JOne_invmass_FromLHE = 0
        JTwo_invmass_FromLHE = 0
        JPair_invmass_FromLHE = 0

        J_etasep_FromLHE = 0

        LHEFound = False


        #Get channel types
        Z1Ind = -1
        Z2Ind = -1
        foundBothZBool = False
        Z1LepHadNeuOthr = -1
        Z2LepHadNeuOthr = -1
        foundZ1Channel = False
        foundZ2Channel = False
        isLeptonic = False
        isSemiLeptonic = False
        isHadronic = False
        isNeutrinos = False
        isOther = False
        tmpZDecAr = []
        #tmpZ1PDGIdAr = []
        #tmpZ2PDGIdAr = []
        if debug:
            print("EVENT",evCount)
        lenLHEPart = ev.nLHEPart
        if debug:
            print("Starting loop over LHE. lenLHEPart",lenLHEPart)
        

        tmpZCtr = 0
        tmpHCtr = 0
        tmpJCtr = 0
        tmpZAr = []
        tmpHInd = -1
        tmpJAr = []
        for LHEItr in range(lenLHEPart):
            tmpPDGId = ev.LHEPart_pdgId[LHEItr]
            if tmpPDGId == 23:
                tmpZCtr += 1
                
                if tmpZCtr > 2:
                    print("ERROR MORE THAN 2 Zs IN LHE")
                else:
                    tmpZAr.append(LHEItr)
            elif tmpPDGId == 25:
                tmpHCtr += 1
                if tmpHCtr > 1:
                    print("ERROR MORE THAN 1 H IN LHE")
                else:
                    tmpHInd = LHEItr
            elif tmpPDGId >= -8 and tmpPDGId <= 8:
                tmpJCtr += 1
                if tmpJCtr > 4:
                    print("ERROR MORE THAN 4 Qs IN LHE")
                elif tmpJCtr > 2:
                    tmpJAr.append(LHEItr)
            else:
                print("ERROR UNKNOWN PARTICLE {0} IN LHE".format(tmpPDGId))
        if tmpZCtr == 2 and tmpHCtr == 1 and tmpJCtr == 4 and len(tmpJAr) == 2:
            LHEFound = True
            ZOne_pt_FromLHE = ev.LHEPart_pt[tmpZAr[0]]
            ZOne_eta_FromLHE = ev.LHEPart_eta[tmpZAr[0]]

            ZTwo_pt_FromLHE = ev.LHEPart_pt[tmpZAr[1]]
            ZTwo_eta_FromLHE = ev.LHEPart_eta[tmpZAr[1]]

            H_pt_FromLHE = ev.LHEPart_pt[tmpHInd]
            H_eta_FromLHE = ev.LHEPart_eta[tmpHInd]

            JOne_pt_FromLHE = ev.LHEPart_pt[tmpJAr[0]]
            JOne_eta_FromLHE = ev.LHEPart_eta[tmpJAr[0]]

            JTwo_pt_FromLHE = ev.LHEPart_pt[tmpJAr[1]]
            JTwo_eta_FromLHE = ev.LHEPart_eta[tmpJAr[1]]

            JOne_invmass_FromLHE = ev.LHEPart_mass[tmpJAr[0]]
            JTwo_invmass_FromLHE = ev.LHEPart_mass[tmpJAr[1]]

            tmpJOnePhi = ev.LHEPart_phi[tmpJAr[0]]
            tmpJOneVec = Math.PtEtaPhiMVector(JOne_pt_FromLHE, JOne_eta_FromLHE, tmpJOnePhi, JOne_invmass_FromLHE)

            tmpJTwoPhi = ev.LHEPart_phi[tmpJAr[1]]
            tmpJTwoVec = Math.PtEtaPhiMVector(JTwo_pt_FromLHE, JTwo_eta_FromLHE, tmpJTwoPhi, JTwo_invmass_FromLHE)
            tmpJPairVec = tmpJOneVec + tmpJTwoVec
            JPair_invmass_FromLHE = tmpJPairVec.M()

            J_etasep_FromLHE = abs(JOne_eta_FromLHE-JTwo_eta_FromLHE)


            

            
        """


        if debug:
            print("Starting loop over genPart. ev.nGenPart",ev.nGenPart)
        
        outQuarkOne = ev.LHEPart_pdgId[lenLHEPart-1]
        outQuarkTwo = ev.LHEPart_pdgId[lenLHEPart-2]
        if debug:
            print("outQuarkOne",outQuarkOne,"outQuarkTwo",outQuarkTwo)
        tmpZAr = []
        for i in range(ev.nGenPart):
            tmpPDGId = ev.GenPart_pdgId[i]
            tmpMotherID = ev.GenPart_genPartIdxMother[i]
            if debug:
                print("i",i,"ev.GenPart_pdgId[i]",tmpPDGId)
            
            for tmpZItr in range(len(tmpZAr)):
                if debug:
                    print("tmpZItr",tmpZItr,"tmpMotherID",tmpMotherID)
                if tmpMotherID == tmpZAr[tmpZItr][0]:
                    if tmpPDGId == 23:
                        print("ERROR, ERROR, DAUGHTER PARTICLE IS Z")
                    else:
                        tmpZAr[tmpZItr].append(tmpPDGId)
            if ev.GenPart_pdgId[i] == 23:
                    
                tmpStatusBin = bin(ev.GenPart_statusFlags[i])
                if debug:
                    print("len(tmpStatusBin)",len(tmpStatusBin),"tmpStatusBin",tmpStatusBin)
                    
                if len(tmpStatusBin) >= 16:
                    tmpIsEnd = tmpStatusBin[-14]
                    if tmpIsEnd == "1":
                        tmpZAr.append([i])
        if debug:
            print("Finished Z Finding. tmpZAr",tmpZAr)
        tmpZFinalAr = []
        intermediaryZ = -1
        if len(tmpZAr) >= 3:
            for tmpZItr in range(len(tmpZAr)):
                if len(tmpZAr[tmpZItr]) == 3 and outQuarkOne in tmpZAr[tmpZItr][1:] and outQuarkTwo in tmpZAr[tmpZItr][1:]:
                    intermediaryZ = tmpZItr
                    break
        finalZAr = []
        for tmpZItr in range(len(tmpZAr)):
            if not tmpZItr == intermediaryZ:
                finalZAr.append(tmpZAr[tmpZItr][0])
        if not len(finalZAr) == 2:
            print("ERROR ERROR, MORE OR LESS THAN TWO Zs,evCount,tmpZAr,outQuarkOne,outQuarkTwo",evCount,tmpZAr,outQuarkOne,outQuarkTwo)
        else:
            tmpHAr = []
            for i in range(ev.nGenPart):
                tmpPDGId = ev.GenPart_pdgId[i]
                tmpMotherID = ev.GenPart_genPartIdxMother[i]
                if debug:
                    print("i",i,"ev.GenPart_pdgId[i]",tmpPDGId)
                
                for tmpHItr in range(len(tmpHAr)):
                    if debug:
                        print("tmpHItr",tmpHItr,"tmpMotherID",tmpMotherID)
                    if tmpMotherID == tmpHAr[tmpHItr][0]:
                        if tmpPDGId == 25:
                            print("ERROR, ERROR, DAUGHTER PARTICLE IS H")
                        else:
                            tmpHAr[tmpHItr].append(tmpPDGId)
                if ev.GenPart_pdgId[i] == 25:
                    tmpStatusBin = bin(ev.GenPart_statusFlags[i])
                    if debug:
                        print("len(tmpStatusBin)",len(tmpStatusBin),"tmpStatusBin",tmpStatusBin)
                        
                    if len(tmpStatusBin) >= 16:
                        tmpIsEnd = tmpStatusBin[-14]
                        if tmpIsEnd == "1":
                            tmpHAr.append([i])
            if debug:
                print("Finished H Finding. tmpHAr",tmpHAr)
            tmpHFinalAr = []
            intermediaryH = -1
            if len(tmpHAr) >= 2:
                for tmpHItr in range(len(tmpHAr)):
                    if len(tmpHAr[tmpHItr]) == 2 and outQuarkOne in tmpHAr[tmpHItr][1:] or outQuarkTwo in tmpHAr[tmpHItr][1:]:
                        intermediaryH = tmpHItr
                        break
            finalHAr = []
            for tmpHItr in range(len(tmpHAr)):
                if not tmpHItr == intermediaryH:
                    finalHAr.append(tmpHAr[tmpHItr][0])
            if not len(finalHAr) == 1:
                print("ERROR ERROR, MORE OR LESS THAN ONE H,evCount,tmpHAr,outQuarkOne,outQuarkTwo",evCount,tmpHAr,outQuarkOne,outQuarkTwo)
                #########################
                if debug:
                    print("entering loop through finalZAr[0]")
                    debugLoopCtr = 0
                GenFound = True
                
                tmpZOneInd = finalZAr[0]
                tmpZTwoInd = finalZAr[1]

                ZOne_pt = ev.GenPart_pt[tmpZOneInd]
                ZOne_eta = ev.GenPart_eta[tmpZOneInd]

                ZTwo_pt = ev.GenPart_pt[tmpZTwoInd]
                ZTwo_eta = ev.GenPart_eta[tmpZTwoInd]

                tmpZOneInd = finalZAr[0]

                ZOne_pt = ev.GenPart_pt[tmpZOneInd]
                ZOne_eta = ev.GenPart_eta[tmpZOneInd]

                ZTwo_pt = ev.GenPart_pt[tmpZTwoInd]
                ZTwo_eta = ev.GenPart_eta[tmpZTwoInd]
                
        """
            
        ######################
        if LHEFound:# and GenFound:
            ZOne_pt_FromLHEL[0]  = ZOne_pt_FromLHE
            ZTwo_pt_FromLHEL[0]  = ZTwo_pt_FromLHE
            ZOne_eta_FromLHEL[0] = ZOne_eta_FromLHE
            ZTwo_eta_FromLHEL[0] = ZTwo_eta_FromLHE

            H_pt_FromLHEL[0]  = H_pt_FromLHE
            H_eta_FromLHEL[0] = H_eta_FromLHE

            JOne_pt_FromLHEL[0] = JOne_pt_FromLHE
            JTwo_pt_FromLHEL[0] = JTwo_pt_FromLHE
            JOne_eta_FromLHEL[0] = JOne_eta_FromLHE
            JTwo_eta_FromLHEL[0] = JTwo_eta_FromLHE

            JOne_invmass_FromLHEL[0] = JOne_invmass_FromLHE
            JTwo_invmass_FromLHEL[0] = JTwo_invmass_FromLHE

            JPair_invmass_FromLHEL[0] = JPair_invmass_FromLHE

            J_etasep_FromLHEL[0] = J_etasep_FromLHE

            GenVarsTree.Fill()


            evPassCount += 1


outFile.cd()

nEv[0] = evRunOver
evNumTree.Fill()

print("Cross section average before division:",crossSectionAvg)
print("Cross section counter:",crossSectionCtr)
crossSectionAvg = crossSectionAvg / crossSectionCtr
print("Cross section average after division:",crossSectionAvg)
#XS Tree
crossSectionVar = array('f',[0.])
crossSectionTree = TTree('crossSectionTree', 'crossSectionTree')
crossSectionTree.Branch("crossSectionVar",crossSectionVar,"crossSectionVar/F")
crossSectionVar[0] = crossSectionAvg
crossSectionTree.Fill()
crossSectionTree.Write("",TObject.kOverwrite)

GenVarsTree.Write("",TObject.kOverwrite)

outFile.Close()

        
        
                


                




