from ROOT import TFile, TChain, gDirectory, TApplication, TMath, Math, TMinuit, TROOT, TSystem, TTree, TVector2
# You probably also want to import TH1D and TCanvas,
# unless you're not making any histograms.
from ROOT import TH1F, TCanvas, TF1, TGraph, TGraphErrors, TLegend, TLine, TPaveText, TStyle
from ROOT import TH2D, TH2F
from math import sqrt,pi
from fileLists import MGEFTAr
from fileLists import MGSMAr
import time as time

#withDipoleRecoil = True

MGSM = False
MGEFT = True

#For drawing and saving histograms
#Saves a png and, optionally, a pdf version
#Saves histogram to the currently active root file

def DrawPlot(plot,name,saveName):
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

MGEFTCrossSection = 
if MGEFT:
    saveName = "pphzzjjQCD0SMHLOOP0NPE1NPcHWE1QEDE5ResMasAllVer100Ev10179Seed_0p999cHW100GeVIMJetCut"
    for fileName in MGEFTAr:
        fileAr.append("/scratch365/dlutton/NanoAODFiles/"+fileName)
elif MGSM:
    for fileName in MGSMAr:
        fileAr.append("/scratch365/dlutton/NanoAODFiles/"+fileName)
    

print("Making Histos/Defining variables.","time:",time.time()-startt)
h_CaloMET_phi    = TH1F("h_CaloMET_phi","h_CaloMET_phi", 100, -3.5, 3.5)
h_CaloMET_pt     = TH1F("h_CaloMET_pt","h_CaloMET_pt", 20, 0, 200)
h_CaloMET_sumEt  = TH1F("h_CaloMET_sumEt","h_CaloMET_sumEt", 500, 0, 1000)
h_LHEWeight      = TH1F("h_LHEWeight","h_LHEWeight",100,0.25,0.30)

h_Electron_eta   = TH1F("h_Electron_eta","h_Electron_eta", 100, -5.0, 5.0)
h_Electron_hoe   = TH1F("h_Electron_hoe","h_Electron_hoe", 200, 0, 5.0)
h_Electron_mass  = TH1F("h_Electron_mass","h_Electron_mass", 200, 0, 0.15)
h_Electron_phi   = TH1F("h_Electron_phi","h_Electron_phi", 100, -3.5, 3.5)
h_Electron_pt    = TH1F("h_Electron_pt","h_Electron_pt", 20, 0, 200)
h_Electron_r9    = TH1F("h_Electron_r9","h_Electron_r9", 200, 0, 4.0)
h_Electron_sieie = TH1F("h_Electron_sieie","h_Electron_sieie", 200, 0, 0.2)

h_Muon_eta       = TH1F("Muon_eta","Muon_eta", 100, -5.0, 5.0)
h_Muon_mass      = TH1F("h_Muon_mass","h_Muon_mass", 200, 0, 0.15)
h_Muon_phi       = TH1F("h_Muon_phi","h_Muon_phi", 100, -3.5, 3.5)
h_Muon_pt        = TH1F("h_Muon_pt","h_Muon_pt", 20, 0, 200)


h_Jet_eta        = TH1F("h_Jet_eta","h_Jet_eta", 100, -5.0, 5.0)
h_Jet_mass       = TH1F("h_Jet_mass","h_Jet_mass", 200, 0, 200)
h_Jet_phi        = TH1F("h_Jet_phi","h_Jet_phi", 100, -3.5, 3.5)
h_Jet_pt         = TH1F("h_Jet_pt","h_Jet_pt", 25, 0, 500)
h_nJet          = TH1F("h_nJet","h_nJet", 19, 0, 19)
h_FatJet_pt         = TH1F("h_FatJet_pt","h_FatJet_pt", 250, 0, 500)
h_nFatJet       = TH1F("h_nFatJet","h_nFatJet", 7, 0, 7)
h_InitialJet_EtaSep     = TH1F("h_InitialJet_EtaSep","h_InitialJet_EtaSep", 100, 0, 10)
h_InitialJet_Eta     = TH1F("h_InitialJet_Eta","h_InitialJet_Eta", 100, -5.0, 5.0)
h_InitialJet_pt    = TH1F("h_InitialJet_pt","h_InitialJet_pt", 25, 0, 500)
h_InitialJetAlt_Eta     = TH1F("h_InitialJetAlt_Eta","h_InitialJetAlt_Eta", 100, -5.0, 5.0)
h_InitialJetAlt_EtaSep     = TH1F("h_InitialJetAlt_EtaSep","h_InitialJetAlt_EtaSep", 100, 0, 10)
h_InitialJetAlt_pt    = TH1F("h_InitialJetAlt_pt","h_InitialJetAlt_pt", 25, 0, 500)
#These for selecting jet pair with inv mass
h_InitialJetAltIM_Eta     = TH1F("h_InitialJetAltIM_Eta","h_InitialJetAltIM_Eta", 100, -5.0, 5.0)
h_InitialJetAltIM_EtaSep     = TH1F("h_InitialJetAltIM_EtaSep","h_InitialJetAltIM_EtaSep", 100, 0, 10)
h_InitialJetAltIM_pt    = TH1F("h_InitialJetAltIM_pt","h_InitialJetAltIM_pt", 25, 0, 500)
#These for selecting jet pair with top jet pt (second jet pt as tiebreaker)
h_InitialJetAltLJ_Eta     = TH1F("h_InitialJetAltLJ_Eta","h_InitialJetAltLJ_Eta", 100, -5.0, 5.0)
h_InitialJetAltLJ_EtaSep     = TH1F("h_InitialJetAltLJ_EtaSep","h_InitialJetAltLJ_EtaSep", 100, 0, 10)
h_InitialJetAltLJ_pt    = TH1F("h_InitialJetAltLJ_pt","h_InitialJetAltLJ_pt", 25, 0, 500)

#Defining jet matching cuts
jetPTCut = 30
jetEtaDifCut = 2.0
jetInvMassCut = 400

#Initializing counter variables
evCount = 0
noMatchCount = 0
noOutCount = 0
ifOneCount = 0
ifTwoCount = 0
ifThreeCount = 0
ifFourCount = 0

print("Going into file loop.","time:",time.time()-startt)
for k,fileName in enumerate(fileAr):
    #Open the file, get the Events tree
    tmpfile = TFile.Open(fileName)
    mytree = tmpfile.Events
    runTree = tmpfile.Runs
    crossSection = runTree[0].genEventSumw
    h_LHEWeight.Fill(crossSection)
    if k % 10 == 0:
        print("Going into event loop for file {0}.".format(k),"time:",time.time()-startt)

    for ev in mytree:
        if evCount % 1000 == 0:
            print("Event: "+str(evCount))
        h_CaloMET_phi.Fill(ev.CaloMET_phi,crossSection)
        h_CaloMET_pt.Fill(ev.CaloMET_pt,crossSection)
        h_CaloMET_sumEt.Fill(ev.CaloMET_sumEt,crossSection)
        h_nJet.Fill(ev.nJet,crossSection)
        h_nFatJet.Fill(ev.nFatJet,crossSection)
        #Initializing temporary, per event, variables for jet matching
        #Gen matching:
        #These for saving the index of the jet pair in jet matching
        jOneInd = -1
        jTwoInd = -1
        #These for saving the two minimum deltaR between jets and the outgoing quarks from gen particles
        deltaRMinOne = 10000
        deltaRMinTwo = 10000

        #Matching with cuts based on max summed PT of the jets:
        #These for saving the maximum PT 
        ptOneInd = -1
        ptTwoInd = -1
        diJetMaxPT = 0


        #Matching with cuts based on max PT of jet in the jet pair, second jet PT as tiebreaker
        LJOneInd = -1
        LJTwoInd = -1
        leadJetMaxPT = 0
        secondJetMaxPT = 0


        #Matching with cuts based on max InvMass of jet pair:
        invMassOneInd = -1
        invMassTwoInd = -1
        diJetMaxInvMass = 0

        

        #For counters to not overcount
        ifOneBool = False
        ifTwoBool = False
        ifThreeBool = False
        ifFourBool = False
        #Electrons loop
        for i in range(ev.nElectron):
            h_Electron_eta.Fill(ev.Electron_eta[i],crossSection)
            h_Electron_hoe.Fill(ev.Electron_hoe[i],crossSection)
            h_Electron_mass.Fill(ev.Electron_mass[i],crossSection)
            h_Electron_phi.Fill(ev.Electron_phi[i],crossSection)
            h_Electron_pt.Fill(ev.Electron_pt[i],crossSection)
            h_Electron_r9.Fill(ev.Electron_r9[i],crossSection)
            h_Electron_sieie.Fill(ev.Electron_sieie[i],crossSection)
        #Muons loop
        for i in range(ev.nMuon):
            h_Muon_eta.Fill(ev.Muon_eta[i],crossSection)
            h_Muon_mass.Fill(ev.Muon_mass[i],crossSection)
            h_Muon_phi.Fill(ev.Muon_phi[i],crossSection)
            h_Muon_pt.Fill(ev.Muon_pt[i],crossSection)
        #Jets loop
        for i in range(ev.nJet):
            #Getting jet PT
            tmpJetPT = ev.Jet_pt[i]
            h_Jet_eta.Fill(ev.Jet_eta[i],crossSection)
            h_Jet_mass.Fill(ev.Jet_mass[i],crossSection)
            h_Jet_phi.Fill(ev.Jet_phi[i],crossSection)
            h_Jet_pt.Fill(tmpJetPT,crossSection)
            #Getting jet DeltaR from first outgoing quark
            tmpDeltaR = calcDeltaR(ev.Jet_phi[i],ev.Jet_eta[i],ev.GenPart_phi[5],ev.GenPart_eta[5])
            #Checking if it's less than the current lowest deltaR
            if tmpDeltaR < deltaRMinOne:
                deltaRMinOne = tmpDeltaR
                jOneInd = i
            #Checking again with the second outgoing quark
            tmpDeltaR = calcDeltaR(ev.Jet_phi[i],ev.Jet_eta[i],ev.GenPart_phi[6],ev.GenPart_eta[6])
            if tmpDeltaR < deltaRMinTwo:
                deltaRMinTwo = tmpDeltaR
                jTwoInd = i
            
            #Starting the matching based on cuts
            #Checking if the jet pt passes the pt cut
            if tmpJetPT > jetPTCut:
                #Counter
                if not ifOneBool:
                    ifOneCount += 1
                    ifOneBool = True
                #Looping through all jets past the current one
                for j in range(i+1,ev.nJet):
                    #Getting PT of the second jet
                    tmpJetPTTwo = ev.Jet_pt[j]
                    #Checking if it passes the pt cut
                    if tmpJetPTTwo > jetPTCut:
                        #Counter
                        if not ifTwoBool:
                            ifTwoCount += 1
                            ifTwoBool = True
                        #Getting the eta dif between the two jets
                        tmpEtaDif = abs(ev.Jet_eta[i]-ev.Jet_eta[j])
                        #Checking if the eta dif passes the eta dif cut
                        if tmpEtaDif > jetEtaDifCut:
                            #Counter
                            if not ifThreeBool:
                                ifThreeCount += 1
                                ifThreeBool = True
                            #Getting four vectors for the two jets, using pt, eta, phi, and mass
                            tmpVecOne = Math.PtEtaPhiMVector(ev.Jet_pt[i], ev.Jet_eta[i], ev.Jet_phi[i], ev.Jet_mass[i])
                            tmpVecTwo = Math.PtEtaPhiMVector(ev.Jet_pt[j], ev.Jet_eta[j], ev.Jet_phi[j], ev.Jet_mass[j])
                            #Adding four vectors together and getting their invariant mass
                            tmpDiJetVec = tmpVecOne+tmpVecTwo
                            tmpInvMass = tmpDiJetVec.M()
                            #Checking if their InvMass passes the InvMass cut
                            if tmpInvMass > jetInvMassCut:
                                #Counter
                                if not ifFourBool:
                                    ifFourCount += 1
                                    ifFourBool = True
                                
                                #Selecting by summed jet pt
                                tmpDiJetPT = tmpJetPT+tmpJetPTTwo
                                if tmpDiJetPT > diJetMaxPT:
                                    diJetMaxPT = tmpDiJetPT
                                    ptOneInd = i
                                    ptTwoInd = j
                                #Selecting by diJet inv mass
                                if tmpInvMass > diJetMaxInvMass:
                                    diJetMaxInvMass = tmpInvMass
                                    invMassOneInd = i
                                    invMassTwoInd = j
                                #Selecting on top jet pt first
                                tmpMaxPtLead = 0
                                tmpMaxPtSecond = 0
                                #Sorting which jet has the larger pt
                                if tmpJetPT > tmpJetPTTwo:
                                    tmpMaxPtLead = tmpJetPT
                                    tmpMaxPtSecond = tmpJetPTTwo
                                else:
                                    tmpMaxPtLead = tmpJetPTTwo
                                    tmpMaxPtSecond = tmpJetPT
                                #Selecting based on that jet's pt
                                if tmpMaxPtLead > leadJetMaxPT:
                                    leadJetMaxPT = tmpMaxPtLead
                                    secondJetMaxPT = tmpMaxPtSecond
                                    LJOneInd = i
                                    LJTwoInd = j
                                #If that jet is already part of the current selected pair,
                                #select based on the respective lower pt jets in the pairs
                                elif tmpMaxPtLead == leadJetMaxPT:
                                    if tmpMaxPtSecond > secondJetMaxPT:
                                        secondJetMaxPT = tmpMaxPtSecond
                                        LJOneInd = i
                                        LJTwoInd = j

        #Filling jet matching with cuts histos:
        #Filling histograms based on summed jet pt
        #Checking that it didn't select the same jet for both parts of the pair                    
        if ptOneInd != ptTwoInd:
            h_InitialJetAlt_Eta.Fill(ev.Jet_eta[ptOneInd],crossSection)
            h_InitialJetAlt_Eta.Fill(ev.Jet_eta[ptTwoInd],crossSection)
            h_InitialJetAlt_EtaSep.Fill(abs(ev.Jet_eta[ptOneInd]-ev.Jet_eta[ptTwoInd],crossSection))
            h_InitialJetAlt_pt.Fill(ev.Jet_pt[ptOneInd],crossSection)
            h_InitialJetAlt_pt.Fill(ev.Jet_pt[ptTwoInd],crossSection)
            #print(evCount,i,deltaRMinOne,deltaRMinTwo,jOneInd,jTwoInd)
        #Filling histograms based on diJet invMass
        #Checking that it didn't select the same jet for both parts of the pair 
        if invMassOneInd != invMassTwoInd:
            h_InitialJetAltIM_Eta.Fill(ev.Jet_eta[invMassOneInd],crossSection)
            h_InitialJetAltIM_Eta.Fill(ev.Jet_eta[invMassTwoInd],crossSection)
            h_InitialJetAltIM_EtaSep.Fill(abs(ev.Jet_eta[invMassOneInd]-ev.Jet_eta[invMassTwoInd],crossSection))
            h_InitialJetAltIM_pt.Fill(ev.Jet_pt[invMassOneInd],crossSection)
            h_InitialJetAltIM_pt.Fill(ev.Jet_pt[invMassTwoInd],crossSection)
            #print(evCount,i,deltaRMinOne,deltaRMinTwo,jOneInd,jTwoInd)
        #Filling histograms based on max jet pt in pair, with secondary jet pt as a tiebreaker
        #Checking that it didn't select the same jet for both parts of the pair 
        if LJOneInd != LJTwoInd:
            h_InitialJetAltLJ_Eta.Fill(ev.Jet_eta[LJOneInd],crossSection)
            h_InitialJetAltLJ_Eta.Fill(ev.Jet_eta[LJTwoInd],crossSection)
            h_InitialJetAltLJ_EtaSep.Fill(abs(ev.Jet_eta[LJOneInd]-ev.Jet_eta[LJTwoInd],crossSection))
            h_InitialJetAltLJ_pt.Fill(ev.Jet_pt[LJOneInd],crossSection)
            h_InitialJetAltLJ_pt.Fill(ev.Jet_pt[LJTwoInd],crossSection)
            #print(evCount,i,deltaRMinOne,deltaRMinTwo,jOneInd,jTwoInd)

        #Filling gen matching histos:
        #Checking that we were actually looking at the outgoing quarks when gen matching
        #Note: should change this to just check at the start and be more flexible with the quark position
        #(i.e. check more than just [5] and [6])
        if abs(ev.GenPart_pdgId[5])>10 or abs(ev.GenPart_pdgId[6])>10:
            #Incrementing counter if not
            noOutCount += 1
        #Checking that the DeltaRs for both jets are small enough
        elif deltaRMinOne > 0.4 or deltaRMinTwo > 0.4:
            #Incrementing counter if not
            noMatchCount +=1
        #Checking that it didn't select the same jet for both parts of the pair 
        elif jOneInd == jTwoInd:
            #If so, then print out what happened (rare)
            print("uhoh",str(jOneInd),str(jTwoInd),evCount,ev.GenPart_pdgId[5],ev.GenPart_pdgId[6],deltaRMinOne,deltaRMinTwo)
        #If it passes all the checks above, fill the gen matching histograms    
        else:
            h_InitialJet_Eta.Fill(ev.Jet_eta[jOneInd],crossSection)
            h_InitialJet_Eta.Fill(ev.Jet_eta[jTwoInd],crossSection)
            h_InitialJet_EtaSep.Fill(abs(ev.Jet_eta[jOneInd]-ev.Jet_eta[jTwoInd],crossSection))
            h_InitialJet_pt.Fill(ev.Jet_pt[jOneInd],crossSection)
            h_InitialJet_pt.Fill(ev.Jet_pt[jTwoInd],crossSection)
        #Increment event count
        evCount += 1

print("Finished file loop.","time:",time.time()-startt)
#Printing out different counters:
#Counters for problems during jet matching:
print("Number of events with no matching jet:",noMatchCount)
print("Number of events with wrong out:",noOutCount)
#Counters for how many events passed each cut:
print("Number of events with one Jet pt > ",jetPTCut,"-",ifOneCount)
print("Number of events with Two Jet pt > ",jetPTCut,"-",ifTwoCount)
print("Number of events with jet pair etaDif >",jetEtaDifCut,"-",ifThreeCount)
print("Number of events with jet pair inv mass >",jetInvMassCut,"-",ifFourCount)

#Setting up outfile for histograms
outFile = TFile("histosFromNanoAOD{0}.root".format(saveName),"recreate")

print("Drawing plots.","time:",time.time()-startt)
#General stuff:
DrawPlot(h_CaloMET_phi, "h_CaloMET_phi",saveName)
DrawPlot(h_CaloMET_pt, "h_CaloMET_pt",saveName)
DrawPlot(h_CaloMET_sumEt, "h_CaloMET_sumEt",saveName)

DrawPlot(h_Electron_eta,"h_Electron_eta",saveName)
DrawPlot(h_Electron_hoe,"h_Electron_hoe",saveName)
DrawPlot(h_Electron_mass,"h_Electron_mass",saveName)
DrawPlot(h_Electron_phi,"h_Electron_phi",saveName)
DrawPlot(h_Electron_pt,"h_Electron_pt",saveName)
DrawPlot(h_Electron_r9,"h_Electron_r9",saveName)
DrawPlot(h_Electron_sieie,"h_Electron_sieie",saveName)

DrawPlot(h_Muon_eta,"h_Muon_eta",saveName)
DrawPlot(h_Muon_mass,"h_Muon_mass",saveName)
DrawPlot(h_Muon_phi,"h_Muon_phi",saveName)
DrawPlot(h_Muon_pt,"h_Muon_pt",saveName)

#Jets:
DrawPlot(h_Jet_eta,"h_Jet_eta",saveName)
DrawPlot(h_Jet_mass,"h_Jet_mass",saveName)
DrawPlot(h_Jet_phi,"h_Jet_phi",saveName)
DrawPlot(h_Jet_pt,"h_Jet_pt",saveName)
DrawPlot(h_nJet,"h_nJet",saveName)
DrawPlot(h_nFatJet,"h_nFatJet",saveName)

#Gen matched jets:
DrawPlot(h_InitialJet_Eta,"h_InitialJet_Eta",saveName)
DrawPlot(h_InitialJet_EtaSep,"h_InitialJet_EtaSep",saveName)
DrawPlot(h_InitialJet_pt,"h_InitialJet_pt",saveName)

#Jet matching with Cuts:
#summed pt cut
DrawPlot(h_InitialJetAlt_Eta,"h_InitialJetAlt_Eta",saveName)
DrawPlot(h_InitialJetAlt_EtaSep,"h_InitialJetAlt_EtaSep",saveName)
DrawPlot(h_InitialJetAlt_pt,"h_InitialJetAlt_pt",saveName)
#InvMass cut
DrawPlot(h_InitialJetAltIM_Eta,"h_InitialJetAltIM_Eta",saveName)
DrawPlot(h_InitialJetAltIM_EtaSep,"h_InitialJetAltIM_EtaSep",saveName)
DrawPlot(h_InitialJetAltIM_pt,"h_InitialJetAltIM_pt",saveName)
#Max jet pt cut
DrawPlot(h_InitialJetAltLJ_Eta,"h_InitialJetAltLJ_Eta",saveName)
DrawPlot(h_InitialJetAltLJ_EtaSep,"h_InitialJetAltLJ_EtaSep",saveName)
DrawPlot(h_InitialJetAltLJ_pt,"h_InitialJetAltLJ_pt",saveName)


print("Done.","time:",time.time()-startt)


