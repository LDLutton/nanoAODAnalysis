from ROOT import TTree
from array import array

#To enable heavy printing for debug
debug = False
debugChannelSort = False
#To break out of loops after NToEnd events
endAfter = False
NToStart = 0
NToEnd = 2500

#withDipoleRecoil = True

testRun = True
LaraTest = False
MGSM = False
MGEFT = False
ttHToBBBackground = False
ttZJetsBackground = False
DYBackground = False
QCDPT170to300Background = False
QCDPT300to470Background = False
QCDPT470to600Background = False
QCDPT600to800Background = False
QCDPT800to1000Background = False
QCDPT1000to1400Background = False
QCDPT1400to1800Background = False
QCDPT1800to2400Background = False
QCDPT2400to3200Background = False
QCDPT3200toInfBackground = False
QCDSum = False

isBackground = False

#Tree for holding the number of events run over
#and the number of events that passed the cut
evNumTree = TTree('evNumTree','evNumTree')
nEv = array('i',[0])
nEvPass = array('i',[0])
evNumTree.Branch("nEv",nEv,"nEv/I")
evNumTree.Branch("nEvPass",nEvPass,"nEvPass/I")



#creating hJet tree
#"L" is for leaf
#First jets
nJetL = array('i',[0])
jetLeadPtL      = array('f',[0.])
jetTrailingPtL  = array('f',[0.])
jetLeadPhiL     = array('f',[0.])
jetTrailingPhiL = array('f',[0.])
jetPairInvMassL = array('f',[0.])
jetLeadEtaL     = array('f',[0.])
jetTrailingEtaL = array('f',[0.])
#now fat jets
nFatJetL = array('i',[0])

hFatJet_pt_fromPtL = array('f',[0.])
hFatJet_phi_fromPtL = array('f',[0.])
hFatJet_eta_fromPtL = array('f',[0.])
hFatJet_mass_fromPtL = array('f',[0.])
hFatJet_HTag_fromPtL = array('f',[0.])
hFatJet_pt_fromHTagL = array('f',[0.])
hFatJet_phi_fromHTagL = array('f',[0.])
hFatJet_eta_fromHTagL = array('f',[0.])
hFatJet_mass_fromHTagL = array('f',[0.])
hFatJet_HTag_fromHTagL = array('f',[0.])

#now matched fat jets

hFatJet_Matched_pt_fromPtL = array('f',[0.])
hFatJet_Matched_phi_fromPtL = array('f',[0.])
hFatJet_Matched_eta_fromPtL = array('f',[0.])
hFatJet_Matched_mass_fromPtL = array('f',[0.])
hFatJet_Matched_HTag_fromPtL = array('f',[0.])
hFatJet_Matched_pt_fromHTagL = array('f',[0.])
hFatJet_Matched_phi_fromHTagL = array('f',[0.])
hFatJet_Matched_eta_fromHTagL = array('f',[0.])
hFatJet_Matched_mass_fromHTagL = array('f',[0.])
hFatJet_Matched_HTag_fromHTagL = array('f',[0.])
hFatJet_Matched_pt_fromdRL = array('f',[0.])
hFatJet_Matched_phi_fromdRL = array('f',[0.])
hFatJet_Matched_eta_fromdRL = array('f',[0.])
hFatJet_Matched_mass_fromdRL = array('f',[0.])
hFatJet_Matched_HTag_fromdRL = array('f',[0.])

#Now GenPart

nGenPartL = array('i',[0])
hGenPartDR_fromPtL = array('f',[0.])
hGenPartInd_fromPtL = array('f',[0.])
hGenPartpdgId_fromPtL = array('f',[0.])
hGenPartFirstMompdgId_fromPtL = array('i',[0])
hGenPartDR_fromHTagL = array('f',[0.])
hGenPartInd_fromHTagL = array('f',[0.])
hGenPartpdgId_fromHTagL = array('f',[0.])
hGenPartFirstMompdgId_fromHTagL = array('i',[0])

#Now HLT stuff
hbbTagL = array('B',[0])

doubleElecHLTL = array('B',[0])
doubleMuonHLTL = array('B',[0])
muonEGHLTL = array('B',[0])
elecHLTL = array('B',[0])
muonHLTL = array('B',[0])
hadHLTL = array('B',[0])
isLeptonicL = array('B',[0])
isSemiLeptonicL = array('B',[0])
isHadronicL = array('B',[0])

#Now tree and branches

hJetTree = TTree('hJetTree', 'hJetTree')

#cutTree.Branch("evInd",evInd,"evInd/I")

hJetTree.Branch("nJetL",nJetL,"nJetL/I")
hJetTree.Branch("jetLeadPtL",jetLeadPtL,"jetLeadPtL/F")     
hJetTree.Branch("jetTrailingPtL",jetTrailingPtL,"jetTrailingPtL/F") 
hJetTree.Branch("jetLeadPhiL",jetLeadPhiL,"jetLeadPhiL/F")    
hJetTree.Branch("jetTrailingPhiL",jetTrailingPhiL,"jetTrailingPhiL/F")
hJetTree.Branch("jetPairInvMassL",jetPairInvMassL,"jetPairInvMassL/F")
hJetTree.Branch("jetLeadEtaL",jetLeadEtaL,"jetLeadEtaL/F")    
hJetTree.Branch("jetTrailingEtaL",jetTrailingEtaL,"jetTrailingEtaL/F")
#now fat jets
hJetTree.Branch("nFatJetL",nFatJetL,"nFatJetL/I")

hJetTree.Branch("hFatJet_pt_fromPtL",hFatJet_pt_fromPtL,"hFatJet_pt_fromPtL/F")
hJetTree.Branch("hFatJet_phi_fromPtL",hFatJet_phi_fromPtL,"hFatJet_phi_fromPtL/F")
hJetTree.Branch("hFatJet_eta_fromPtL",hFatJet_eta_fromPtL,"hFatJet_eta_fromPtL/F")
hJetTree.Branch("hFatJet_mass_fromPtL",hFatJet_mass_fromPtL,"hFatJet_mass_fromPtL/F")
hJetTree.Branch("hFatJet_HTag_fromPtL",hFatJet_HTag_fromPtL,"hFatJet_HTag_fromPtL/F")
hJetTree.Branch("hFatJet_pt_fromHTagL",hFatJet_pt_fromHTagL,"hFatJet_pt_fromHTagL/F")
hJetTree.Branch("hFatJet_phi_fromHTagL",hFatJet_phi_fromHTagL,"hFatJet_phi_fromHTagL/F")
hJetTree.Branch("hFatJet_eta_fromHTagL",hFatJet_eta_fromHTagL,"hFatJet_eta_fromHTagL/F")
hJetTree.Branch("hFatJet_mass_fromHTagL",hFatJet_mass_fromHTagL,"hFatJet_mass_fromHTagL/F")
hJetTree.Branch("hFatJet_HTag_fromHTagL",hFatJet_HTag_fromHTagL,"hFatJet_HTag_fromHTagL/F")

#Now matched fat jets


hJetTree.Branch("hFatJet_Matched_pt_fromPtL",hFatJet_Matched_pt_fromPtL,"hFatJet_Matched_pt_fromPtL/F")
hJetTree.Branch("hFatJet_Matched_phi_fromPtL",hFatJet_Matched_phi_fromPtL,"hFatJet_Matched_phi_fromPtL/F")
hJetTree.Branch("hFatJet_Matched_eta_fromPtL",hFatJet_Matched_eta_fromPtL,"hFatJet_Matched_eta_fromPtL/F")
hJetTree.Branch("hFatJet_Matched_mass_fromPtL",hFatJet_Matched_mass_fromPtL,"hFatJet_Matched_mass_fromPtL/F")
hJetTree.Branch("hFatJet_Matched_HTag_fromPtL",hFatJet_Matched_HTag_fromPtL,"hFatJet_Matched_HTag_fromPtL/F")
hJetTree.Branch("hFatJet_Matched_pt_fromHTagL",hFatJet_Matched_pt_fromHTagL,"hFatJet_Matched_pt_fromHTagL/F")
hJetTree.Branch("hFatJet_Matched_phi_fromHTagL",hFatJet_Matched_phi_fromHTagL,"hFatJet_Matched_phi_fromHTagL/F")
hJetTree.Branch("hFatJet_Matched_eta_fromHTagL",hFatJet_Matched_eta_fromHTagL,"hFatJet_Matched_eta_fromHTagL/F")
hJetTree.Branch("hFatJet_Matched_mass_fromHTagL",hFatJet_Matched_mass_fromHTagL,"hFatJet_Matched_mass_fromHTagL/F")
hJetTree.Branch("hFatJet_Matched_HTag_fromHTagL",hFatJet_Matched_HTag_fromHTagL,"hFatJet_Matched_HTag_fromHTagL/F")
hJetTree.Branch("hFatJet_Matched_pt_fromdRL",hFatJet_Matched_pt_fromdRL,"hFatJet_Matched_pt_fromdRL/F")
hJetTree.Branch("hFatJet_Matched_phi_fromdRL",hFatJet_Matched_phi_fromdRL,"hFatJet_Matched_phi_fromdRL/F")
hJetTree.Branch("hFatJet_Matched_eta_fromdRL",hFatJet_Matched_eta_fromdRL,"hFatJet_Matched_eta_fromdRL/F")
hJetTree.Branch("hFatJet_Matched_mass_fromdRL",hFatJet_Matched_mass_fromdRL,"hFatJet_Matched_mass_fromdRL/F")
hJetTree.Branch("hFatJet_Matched_HTag_fromdRL",hFatJet_Matched_HTag_fromdRL,"hFatJet_Matched_HTag_fromdRL/F")

#now genpart
hJetTree.Branch("nGenPartL",nGenPartL,"nGenPartL/I")
hJetTree.Branch("hGenPartDR_fromPtL",hGenPartDR_fromPtL,"hGenPartDR_fromPtL/F")
hJetTree.Branch("hGenPartInd_fromPtL",hGenPartInd_fromPtL,"hGenPartInd_fromPtL/F")
hJetTree.Branch("hGenPartpdgId_fromPtL",hGenPartpdgId_fromPtL,"hGenPartpdgId_fromPtL/F")
hJetTree.Branch("hGenPartFirstMompdgId_fromPtL",hGenPartFirstMompdgId_fromPtL,"hGenPartFirstMompdgId_fromPtL/I")
hJetTree.Branch("hGenPartDR_fromHTagL",hGenPartDR_fromHTagL,"hGenPartDR_fromHTagL/F")
hJetTree.Branch("hGenPartInd_fromHTagL",hGenPartInd_fromHTagL,"hGenPartInd_fromHTagL/F")
hJetTree.Branch("hGenPartpdgId_fromHTagL",hGenPartpdgId_fromHTagL,"hGenPartpdgId_fromHTagL/F")
hJetTree.Branch("hGenPartFirstMompdgId_fromHTagL",hGenPartFirstMompdgId_fromHTagL,"hGenPartFirstMompdgId_fromHTagL/I")

#Now HLT stuff

hJetTree.Branch("hbbTagL",hbbTagL,"hbbTagL/O")

hJetTree.Branch("doubleElecHLTL",doubleElecHLTL,"doubleElecHLTL/O")
hJetTree.Branch("doubleMuonHLTL",doubleMuonHLTL,"doubleMuonHLTL/O")
hJetTree.Branch("muonEGHLTL",muonEGHLTL,"muonEGHLTL/O")
hJetTree.Branch("elecHLTL",elecHLTL,"elecHLTL/O")
hJetTree.Branch("muonHLTL",muonHLTL,"muonHLTL/O")
hJetTree.Branch("hadHLTL",hadHLTL,"hadHLTL/O")
hJetTree.Branch("isLeptonicL",isLeptonicL,"isLeptonicL/O")
hJetTree.Branch("isSemiLeptonicL",isSemiLeptonicL,"isSemiLeptonicL/O")
hJetTree.Branch("isHadronicL",isHadronicL,"isHadronicL/O")

#VBF jet pair selection
#Defining jet matching cuts

jetPTCut = 50
jetEtaDifCut = 2.0
jetInvMassCut = 400

#Defining fat jet matching cuts
fatJetPTCut = 200
hFatJetPTCut = 350
hFatJetDeepTagCut = 0.2
hFatJetdRCut = 0.4