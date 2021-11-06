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



#creating Full Analysis tree
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

#Branches for distinguishing between channels
passedLepL = array('B',[0])
passedSemiLepL = array('B',[0])
passedHadL = array('B',[0])



#Now tree and branches

FATree = TTree('FATree', 'FATree')

#cutTree.Branch("evInd",evInd,"evInd/I")

FATree.Branch("nJetL",nJetL,"nJetL/I")
FATree.Branch("jetLeadPtL",jetLeadPtL,"jetLeadPtL/F")     
FATree.Branch("jetTrailingPtL",jetTrailingPtL,"jetTrailingPtL/F") 
FATree.Branch("jetLeadPhiL",jetLeadPhiL,"jetLeadPhiL/F")    
FATree.Branch("jetTrailingPhiL",jetTrailingPhiL,"jetTrailingPhiL/F")
FATree.Branch("jetPairInvMassL",jetPairInvMassL,"jetPairInvMassL/F")
FATree.Branch("jetLeadEtaL",jetLeadEtaL,"jetLeadEtaL/F")    
FATree.Branch("jetTrailingEtaL",jetTrailingEtaL,"jetTrailingEtaL/F")
#now fat jets
FATree.Branch("nFatJetL",nFatJetL,"nFatJetL/I")

FATree.Branch("hFatJet_pt_fromPtL",hFatJet_pt_fromPtL,"hFatJet_pt_fromPtL/F")
FATree.Branch("hFatJet_phi_fromPtL",hFatJet_phi_fromPtL,"hFatJet_phi_fromPtL/F")
FATree.Branch("hFatJet_eta_fromPtL",hFatJet_eta_fromPtL,"hFatJet_eta_fromPtL/F")
FATree.Branch("hFatJet_mass_fromPtL",hFatJet_mass_fromPtL,"hFatJet_mass_fromPtL/F")
FATree.Branch("hFatJet_HTag_fromPtL",hFatJet_HTag_fromPtL,"hFatJet_HTag_fromPtL/F")
FATree.Branch("hFatJet_pt_fromHTagL",hFatJet_pt_fromHTagL,"hFatJet_pt_fromHTagL/F")
FATree.Branch("hFatJet_phi_fromHTagL",hFatJet_phi_fromHTagL,"hFatJet_phi_fromHTagL/F")
FATree.Branch("hFatJet_eta_fromHTagL",hFatJet_eta_fromHTagL,"hFatJet_eta_fromHTagL/F")
FATree.Branch("hFatJet_mass_fromHTagL",hFatJet_mass_fromHTagL,"hFatJet_mass_fromHTagL/F")
FATree.Branch("hFatJet_HTag_fromHTagL",hFatJet_HTag_fromHTagL,"hFatJet_HTag_fromHTagL/F")

#now genpart
FATree.Branch("nGenPartL",nGenPartL,"nGenPartL/I")
FATree.Branch("hGenPartDR_fromPtL",hGenPartDR_fromPtL,"hGenPartDR_fromPtL/F")
FATree.Branch("hGenPartInd_fromPtL",hGenPartInd_fromPtL,"hGenPartInd_fromPtL/F")
FATree.Branch("hGenPartpdgId_fromPtL",hGenPartpdgId_fromPtL,"hGenPartpdgId_fromPtL/F")
FATree.Branch("hGenPartFirstMompdgId_fromPtL",hGenPartFirstMompdgId_fromPtL,"hGenPartFirstMompdgId_fromPtL/I")
FATree.Branch("hGenPartDR_fromHTagL",hGenPartDR_fromHTagL,"hGenPartDR_fromHTagL/F")
FATree.Branch("hGenPartInd_fromHTagL",hGenPartInd_fromHTagL,"hGenPartInd_fromHTagL/F")
FATree.Branch("hGenPartpdgId_fromHTagL",hGenPartpdgId_fromHTagL,"hGenPartpdgId_fromHTagL/F")
FATree.Branch("hGenPartFirstMompdgId_fromHTagL",hGenPartFirstMompdgId_fromHTagL,"hGenPartFirstMompdgId_fromHTagL/I")

#Now HLT stuff

FATree.Branch("hbbTagL",hbbTagL,"hbbTagL/O")

FATree.Branch("doubleElecHLTL",doubleElecHLTL,"doubleElecHLTL/O")
FATree.Branch("doubleMuonHLTL",doubleMuonHLTL,"doubleMuonHLTL/O")
FATree.Branch("muonEGHLTL",muonEGHLTL,"muonEGHLTL/O")
FATree.Branch("elecHLTL",elecHLTL,"elecHLTL/O")
FATree.Branch("muonHLTL",muonHLTL,"muonHLTL/O")
FATree.Branch("hadHLTL",hadHLTL,"hadHLTL/O")
FATree.Branch("isLeptonicL",isLeptonicL,"isLeptonicL/O")
FATree.Branch("isSemiLeptonicL",isSemiLeptonicL,"isSemiLeptonicL/O")
FATree.Branch("isHadronicL",isHadronicL,"isHadronicL/O")

#Branches for distinguishing between channels
FATree.Branch("passedLepL",passedLepL,"passedLepL/O")
FATree.Branch("passedSemiLepL",passedSemiLepL,"passedSemiLepL/O")
FATree.Branch("passedHadL",passedHadL,"passedHadL/O")



#Now trees for specific channels

#Leptonic variables
lepZ1LeadPtL      = array('f',[0.])
lepZ1TrailingPtL  = array('f',[0.])
lepZ1LeadPhiL     = array('f',[0.])
lepZ1TrailingPhiL = array('f',[0.])
lepZ1PairInvMassL = array('f',[0.])
lepZ1LeadEtaL     = array('f',[0.])
lepZ1TrailingEtaL = array('f',[0.])
lepZ1IsElectronL   = array('B',[0])
lepZ1IsMuonL       = array('B',[0])
lepZ1LeadIsoL     = array('f',[0.])
lepZ1TrailingIsoL = array('f',[0.])
lepZ1LeadSIPL     = array('f',[0.])
lepZ1TrailingSIPL = array('f',[0.])

lepZ2LeadPtL      = array('f',[0.])
lepZ2TrailingPtL  = array('f',[0.])
lepZ2LeadPhiL     = array('f',[0.])
lepZ2TrailingPhiL = array('f',[0.])
lepZ2PairInvMassL = array('f',[0.])
lepZ2LeadEtaL     = array('f',[0.])
lepZ2TrailingEtaL = array('f',[0.])
lepZ2IsElectronL  = array('B',[0])
lepZ2IsMuonL      = array('B',[0])
lepZ2LeadIsoL     = array('f',[0.])
lepZ2TrailingIsoL = array('f',[0.])
lepZ2LeadSIPL     = array('f',[0.])
lepZ2TrailingSIPL = array('f',[0.])

#Leptonic tree
LepTree = TTree('LepTree', 'LepTree')

LepTree.Branch("lepZ1LeadPtL",lepZ1LeadPtL,"lepZ1LeadPtL/F")     
LepTree.Branch("lepZ1TrailingPtL",lepZ1TrailingPtL,"lepZ1TrailingPtL/F") 
LepTree.Branch("lepZ1LeadPhiL",lepZ1LeadPhiL,"lepZ1LeadPhiL/F")    
LepTree.Branch("lepZ1TrailingPhiL",lepZ1TrailingPhiL,"lepZ1TrailingPhiL/F")
LepTree.Branch("lepZ1PairInvMassL",lepZ1PairInvMassL,"lepZ1PairInvMassL/F")
LepTree.Branch("lepZ1LeadEtaL",lepZ1LeadEtaL,"lepZ1LeadEtaL/F")    
LepTree.Branch("lepZ1TrailingEtaL",lepZ1TrailingEtaL,"lepZ1TrailingEtaL/F")
LepTree.Branch("lepZ1IsElectronL",lepZ1IsElectronL,"lepZ1IsElectronL/O")
LepTree.Branch("lepZ1IsMuonL",lepZ1IsMuonL,"lepZ1IsMuonL/O")
LepTree.Branch("lepZ1LeadIsoL",lepZ1LeadIsoL,"lepZ1LeadIsoL/F")    
LepTree.Branch("lepZ1TrailingIsoL",lepZ1TrailingIsoL,"lepZ1TrailingIsoL/F")
LepTree.Branch("lepZ1LeadSIPL",lepZ1LeadSIPL,"lepZ1LeadSIPL/F")    
LepTree.Branch("lepZ1TrailingSIPL",lepZ1TrailingSIPL,"lepZ1TrailingSIPL/F")

LepTree.Branch("lepZ2LeadPtL",lepZ2LeadPtL,"lepZ2LeadPtL/F")     
LepTree.Branch("lepZ2TrailingPtL",lepZ2TrailingPtL,"lepZ2TrailingPtL/F") 
LepTree.Branch("lepZ2LeadPhiL",lepZ2LeadPhiL,"lepZ2LeadPhiL/F")    
LepTree.Branch("lepZ2TrailingPhiL",lepZ2TrailingPhiL,"lepZ2TrailingPhiL/F")
LepTree.Branch("lepZ2PairInvMassL",lepZ2PairInvMassL,"lepZ2PairInvMassL/F")
LepTree.Branch("lepZ2LeadEtaL",lepZ2LeadEtaL,"lepZ2LeadEtaL/F")    
LepTree.Branch("lepZ2TrailingEtaL",lepZ2TrailingEtaL,"lepZ2TrailingEtaL/F")
LepTree.Branch("lepZ2IsElectronL",lepZ2IsElectronL,"lepZ2IsElectronL/O")
LepTree.Branch("lepZ2IsMuonL",lepZ2IsMuonL,"lepZ2IsMuonL/O")
LepTree.Branch("lepZ2LeadIsoL",lepZ2LeadIsoL,"lepZ2LeadIsoL/F")    
LepTree.Branch("lepZ2TrailingIsoL",lepZ2TrailingIsoL,"lepZ2TrailingIsoL/F")
LepTree.Branch("lepZ2LeadSIPL",lepZ2LeadSIPL,"lepZ2LeadSIPL/F")    
LepTree.Branch("lepZ2TrailingSIPL",lepZ2TrailingSIPL,"lepZ2TrailingSIPL/F")




#SemiLeptonic variables
lepLeadPtL      = array('f',[0.])
lepTrailingPtL  = array('f',[0.])
lepLeadPhiL     = array('f',[0.])
lepTrailingPhiL = array('f',[0.])
lepPairInvMassL = array('f',[0.])
lepLeadEtaL     = array('f',[0.])
lepTrailingEtaL = array('f',[0.])
lepLeadIsoL     = array('f',[0.])
lepTrailingIsoL = array('f',[0.])
lepLeadSIPL     = array('f',[0.])
lepTrailingSIPL = array('f',[0.])
lepIsElectronL  = array('B',[0])
lepIsMuonL      = array('B',[0])


FJPtL      = array('f',[0.])
FJPhiL     = array('f',[0.])
FJMassL    = array('f',[0.])
FJEtaL     = array('f',[0.])

#SemiLeptonic tree
SemiLepTree = TTree('SemiLepTree', 'SemiLepTree')

SemiLepTree.Branch("lepLeadPtL",lepLeadPtL,"lepLeadPtL/F")     
SemiLepTree.Branch("lepTrailingPtL",lepTrailingPtL,"lepTrailingPtL/F") 
SemiLepTree.Branch("lepLeadPhiL",lepLeadPhiL,"lepLeadPhiL/F")    
SemiLepTree.Branch("lepTrailingPhiL",lepTrailingPhiL,"lepTrailingPhiL/F")
SemiLepTree.Branch("lepPairInvMassL",lepPairInvMassL,"lepPairInvMassL/F")
SemiLepTree.Branch("lepLeadEtaL",lepLeadEtaL,"lepLeadEtaL/F")    
SemiLepTree.Branch("lepTrailingEtaL",lepTrailingEtaL,"lepTrailingEtaL/F")
SemiLepTree.Branch("lepIsElectronL",lepIsElectronL,"lepIsElectronL/O")
SemiLepTree.Branch("lepIsMuonL",lepIsMuonL,"lepIsMuonL/O")
SemiLepTree.Branch("lepLeadIsoL",lepLeadIsoL,"lepLeadIsoL/F")    
SemiLepTree.Branch("lepTrailingIsoL",lepTrailingIsoL,"lepTrailingIsoL/F")
SemiLepTree.Branch("lepLeadSIPL",lepLeadSIPL,"lepLeadSIPL/F")    
SemiLepTree.Branch("lepTrailingSIPL",lepTrailingSIPL,"lepTrailingSIPL/F")
SemiLepTree.Branch("lepZ2IsElectronL",lepZ2IsElectronL,"lepZ2IsElectronL/O")
SemiLepTree.Branch("lepIsMuonL",lepIsMuonL,"lepIsMuonL/O")

SemiLepTree.Branch("FJPtL",FJPtL,"FJPtL/F")
SemiLepTree.Branch("FJPhiL",FJPhiL,"FJPhiL/F")
SemiLepTree.Branch("FJMassL",FJMassL,"FJMassL/F")
SemiLepTree.Branch("FJEtaL",FJEtaL,"FJEtaL/F")


#Hadronic variables
FJLeadPtL      = array('f',[0.])
FJTrailingPtL  = array('f',[0.])
FJLeadPhiL     = array('f',[0.])
FJTrailingPhiL = array('f',[0.])
FJLeadMassL    = array('f',[0.])
FJTrailingMassL = array('f',[0.])
FJPairInvMassL = array('f',[0.])
FJLeadEtaL     = array('f',[0.])
FJTrailingEtaL = array('f',[0.])
FJEtaSepL      = array('f',[0.])

#Hadronic tree
HadTree = TTree('HadTree', 'HadTree')

HadTree.Branch("FJLeadPtL",FJLeadPtL,"FJLeadPtL/F")
HadTree.Branch("FJTrailingPtL",FJTrailingPtL,"FJTrailingPtL/F")
HadTree.Branch("FJLeadPhiL",FJLeadPhiL,"FJLeadPhiL/F")
HadTree.Branch("FJTrailingPhiL",FJTrailingPhiL,"FJTrailingPhiL/F")
HadTree.Branch("FJLeadMassL",FJLeadMassL,"FJLeadMassL/F")
HadTree.Branch("FJTrailingMassL",FJTrailingMassL,"FJTrailingMassL/F")
HadTree.Branch("FJPairInvMassL",FJPairInvMassL,"FJPairInvMassL/F")
HadTree.Branch("FJLeadEtaL",FJLeadEtaL,"FJLeadEtaL/F")    
HadTree.Branch("FJTrailingEtaL",FJTrailingEtaL,"FJTrailingEtaL/F")
HadTree.Branch("FJEtaSepL",FJEtaSepL,"FJEtaSepL/F")



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

#Lepton cuts
ePtCut = 7
eEtaCut = 2.5

mPtCut = 5
mEtaCut = 2.4
invMassCutLow=60
invMassCutHigh=120
ptLeadCut=20
ptTrailingCut=10

fourLepInvMassCut = 100
optLepInvMassCut = 12

lepIsoCut = 0.35

SIPCut = 4