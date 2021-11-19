from ROOT import TLegend, TTree
from array import array




debug = False
#For drawing and saving histograms
#Saves a png and, optionally, a pdf version
#Saves histogram to the currently active root file

testRun = True
MGSM = False
MGEFT = False
LaraTest = False

endAfter = False
NToEnd = 2500
NToStart = 1000
"""
ZOne_ptL = array('f',[0.])
ZTwo_ptL = array('f',[0.])
ZOne_etaL = array('f',[0.])
ZTwo_etaL = array('f',[0.])
H_ptL = array('f',[0.])
H_etaL = array('f',[0.])

JOne_ptL = array('f',[0.])
JTwo_ptL = array('f',[0.])
JOne_etaL = array('f',[0.])
JTwo_etaL = array('f',[0.])

JOne_invmassL = array('f',[0.])
JTwo_invmassL = array('f',[0.])

JPair_invmassL = array('f',[0.])

J_etasepL = array('f',[0.])
"""



ZOne_pt_FromLHEL = array('f',[0.])
ZTwo_pt_FromLHEL = array('f',[0.])
ZOne_eta_FromLHEL = array('f',[0.])
ZTwo_eta_FromLHEL = array('f',[0.])
H_pt_FromLHEL = array('f',[0.])
H_eta_FromLHEL = array('f',[0.])

JOne_pt_FromLHEL = array('f',[0.])
JTwo_pt_FromLHEL = array('f',[0.])
JOne_eta_FromLHEL = array('f',[0.])
JTwo_eta_FromLHEL = array('f',[0.])

JOne_invmass_FromLHEL = array('f',[0.])
JTwo_invmass_FromLHEL = array('f',[0.])

JPair_invmass_FromLHEL = array('f',[0.])

J_etasep_FromLHEL = array('f',[0.])



GenVarsTree = TTree('GenVarsTree', 'GenVarsTree')

#cutTree.Branch("evInd",evInd,"evInd/I")
"""
GenVarsTree.Branch("ZOne_ptL",ZOne_ptL,"ZOne_ptL/F")
GenVarsTree.Branch("ZOne_etaL",ZOne_etaL,"ZOne_etaL/F")     

GenVarsTree.Branch("ZTwo_ptL",ZTwo_ptL,"ZTwo_ptL/F")
GenVarsTree.Branch("ZTwo_etaL",ZTwo_etaL,"ZTwo_etaL/F") 
GenVarsTree.Branch("H_ptL",H_ptL,"H_ptL/F")
GenVarsTree.Branch("H_etaL",H_etaL,"H_etaL/F")    


GenVarsTree.Branch("JOne_ptL",JOne_ptL,"JOne_ptL/F")
GenVarsTree.Branch("JOne_etaL",JOne_etaL,"JOne_etaL/F")     
GenVarsTree.Branch("JTwo_ptL",JTwo_ptL,"JTwo_ptL/F")
GenVarsTree.Branch("JTwo_etaL",JTwo_etaL,"JTwo_etaL/F") 

GenVarsTree.Branch("JOne_invmassL",JOne_invmassL,"JOne_invmassL/F")     
GenVarsTree.Branch("JTwo_invmassL",JTwo_invmassL,"JTwo_invmassL/F") 

GenVarsTree.Branch("JPair_invmassL",JPair_invmassL,"JPair_invmassL/F") 

GenVarsTree.Branch("J_etasepL",J_etasepL,"J_etasepL/F") 
"""

GenVarsTree.Branch("ZOne_pt_FromLHEL",ZOne_pt_FromLHEL,"ZOne_pt_FromLHEL/F")
GenVarsTree.Branch("ZOne_eta_FromLHEL",ZOne_eta_FromLHEL,"ZOne_eta_FromLHEL/F")     
GenVarsTree.Branch("ZTwo_pt_FromLHEL",ZTwo_pt_FromLHEL,"ZTwo_pt_FromLHEL/F")
GenVarsTree.Branch("ZTwo_eta_FromLHEL",ZTwo_eta_FromLHEL,"ZTwo_eta_FromLHEL/F") 
GenVarsTree.Branch("H_pt_FromLHEL",H_pt_FromLHEL,"H_pt_FromLHEL/F")
GenVarsTree.Branch("H_eta_FromLHEL",H_eta_FromLHEL,"H_eta_FromLHEL/F")  

GenVarsTree.Branch("JOne_pt_FromLHEL",JOne_pt_FromLHEL,"JOne_pt_FromLHEL/F")
GenVarsTree.Branch("JOne_eta_FromLHEL",JOne_eta_FromLHEL,"JOne_eta_FromLHEL/F")     
GenVarsTree.Branch("JTwo_pt_FromLHEL",JTwo_pt_FromLHEL,"JTwo_pt_FromLHEL/F")
GenVarsTree.Branch("JTwo_eta_FromLHEL",JTwo_eta_FromLHEL,"JTwo_eta_FromLHEL/F") 

GenVarsTree.Branch("JOne_invmass_FromLHEL",JOne_invmass_FromLHEL,"JOne_invmass_FromLHEL/F")     
GenVarsTree.Branch("JTwo_invmass_FromLHEL",JTwo_invmass_FromLHEL,"JTwo_invmass_FromLHEL/F") 

GenVarsTree.Branch("JPair_invmass_FromLHEL",JPair_invmass_FromLHEL,"JPair_invmass_FromLHEL/F") 

GenVarsTree.Branch("J_etasep_FromLHEL",J_etasep_FromLHEL,"J_etasep_FromLHEL/F") 




nEv = array('i',[0])

evNumTree = TTree('evNumTree','evNumTree')

evNumTree.Branch("nEv",nEv,"nEv/I")
