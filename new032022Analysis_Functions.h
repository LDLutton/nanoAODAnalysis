#include<TVector2.h>
#include<Math/Vector4D.h>
#include <Math/GenVector/LorentzVector.h>
#include <math.h>
#include<vector>

float ZMass = 91.1876;

//For calculating DeltaR for two particles from their respective etas and phis
float calcDeltaR(float phi1,float eta1,float phi2,float eta2){
    float deta = eta1-eta2;
    float dphi = abs(phi1-phi2);
    if (dphi > M_PI) dphi -= (2*M_PI);
    return sqrt((deta*deta)+(dphi*dphi));
}

//Int_t getInitialMother(TTreeReader *myEventsReader,Int_t genPartInd):
Int_t getInitialMother(TTreeReaderArray<Int_t> &GenPart_genPartIdxMother,TTreeReaderArray<Int_t> &GenPart_pdgId,Int_t genPartInd,bool debug){
    bool momFound = false;
    std::vector<Int_t> motherAr;
    Int_t tmpMomInd = GenPart_genPartIdxMother[genPartInd];
    if (debug) std::cout << "tmpMomInd " << tmpMomInd << "\n";
    while (!momFound){
        motherAr.push_back(GenPart_pdgId[tmpMomInd]);
        tmpMomInd = GenPart_genPartIdxMother[tmpMomInd];
        if (debug) std::cout << "tmpMomInd " << tmpMomInd <<" motherAr " << motherAr.back() << "\n";
        if (tmpMomInd == -1 || tmpMomInd == 0) momFound = true;
    }
    return motherAr.back();
}


void doeCandCut(TTreeReaderArray<Float_t> &Electron_eta,TTreeReaderArray<Float_t> &Electron_mass,TTreeReaderArray<Int_t> &Electron_charge,TTreeReaderArray<Float_t> &Electron_phi,TTreeReaderArray<Float_t> &Electron_pt,UInt_t neLep,std::vector<UInt_t> &elecCandIndAr,std::vector<ROOT::Math::PtEtaPhiMVector> &elecCandVecAr,std::vector<Int_t> &elecCandChargeAr,float ePtCut,float eEtaCut){
    for (UInt_t eItr=0; eItr < neLep; eItr++){
        float tmpPt = Electron_pt[eItr];
        if (tmpPt > ePtCut){
            float tmpEta = Electron_eta[eItr];
            if (abs(tmpEta) < eEtaCut){
                elecCandIndAr.push_back(eItr);
                float tmpPhi = Electron_phi[eItr];
                float tmpMass = Electron_mass[eItr];
                ROOT::Math::PtEtaPhiMVector tmpVec = ROOT::Math::PtEtaPhiMVector(tmpPt, tmpEta, tmpPhi, tmpMass);
                elecCandVecAr.push_back(tmpVec);
                Int_t tmpCharge = Electron_charge[eItr];
                elecCandChargeAr.push_back(tmpCharge);
            }
        }
    }
}

void domCandCut(TTreeReaderArray<Float_t> &Muon_eta,TTreeReaderArray<Float_t> &Muon_mass,TTreeReaderArray<Int_t> &Muon_charge,TTreeReaderArray<Float_t> &Muon_phi,TTreeReaderArray<Float_t> &Muon_pt,UInt_t nmLep,std::vector<UInt_t> muonCandIndAr,std::vector<ROOT::Math::PtEtaPhiMVector> muonCandVecAr,std::vector<Int_t> muonCandChargeAr,float mPtCut,float mEtaCut){
    for (UInt_t mItr=0; mItr < nmLep; mItr++){
        float tmpPt = Muon_pt[mItr];
        if (tmpPt > mPtCut){
            float tmpEta = Muon_eta[mItr];
            if (abs(tmpEta) < mEtaCut){
                muonCandIndAr.push_back(mItr);
                float tmpPhi = Muon_phi[mItr];
                float tmpMass = Muon_mass[mItr];
                ROOT::Math::PtEtaPhiMVector tmpVec = ROOT::Math::PtEtaPhiMVector(tmpPt, tmpEta, tmpPhi, tmpMass);
                muonCandVecAr.push_back(tmpVec);
                Int_t tmpCharge = Muon_charge[mItr];
                muonCandChargeAr.push_back(tmpCharge);
            }
        }
    }
}

void dolCandCut(TTreeReaderArray<Float_t> &Lep_eta,TTreeReaderArray<Float_t> &Lep_mass,TTreeReaderArray<Int_t> &Lep_charge,TTreeReaderArray<Float_t> &Lep_phi,TTreeReaderArray<Float_t> &Lep_pt,UInt_t nlLep,std::vector<UInt_t> &lepCandIndAr,std::vector<ROOT::Math::PtEtaPhiMVector> &lepCandVecAr,std::vector<Int_t> &lepCandChargeAr,float lPtCut,float lEtaCut,bool debug){
    for (UInt_t lItr=0; lItr < nlLep; lItr++){
        float tmpPt = Lep_pt[lItr];
        if (debug) std::cout << "lItr " << lItr << " tmpPt " << tmpPt << "\n";
        if (tmpPt > lPtCut){
            if (debug) std::cout << "passed pt cut\n";
            float tmpEta = Lep_eta[lItr];
            if (debug) std::cout << "tmpEta " <<tmpEta << "\n";
            if (abs(tmpEta) < lEtaCut){
                if (debug) std::cout << "passed eta cut\n";
                lepCandIndAr.push_back(lItr);
                float tmpPhi = Lep_phi[lItr];
                float tmpMass = Lep_mass[lItr];
                ROOT::Math::PtEtaPhiMVector tmpVec = ROOT::Math::PtEtaPhiMVector(tmpPt, tmpEta, tmpPhi, tmpMass);
                lepCandVecAr.push_back(tmpVec);
                Int_t tmpCharge = Lep_charge[lItr];
                lepCandChargeAr.push_back(tmpCharge);
            }
        }
    }
}

void dolZ1Cut(TTreeReaderArray<Float_t> &Lep_pt,std::vector<UInt_t> lepCandIndAr,std::vector<ROOT::Math::PtEtaPhiMVector> lepCandVecAr,std::vector<Int_t> lepCandChargeAr,std::vector<std::array<UInt_t,2>> &lepPassesZ2CutsAr,bool &Z1IsMuon,bool forMuon,float invMassCutLow,float invMassCutHigh,float ptLeadCut,float ptTrailingCut,float &tmpTopZ1LeadPt,float &tmpTopZ1TrailingPt,Int_t &tmpTopLeadItr,Int_t &tmpTopTrailingItr,ROOT::Math::PtEtaPhiMVector &tmpTopLeadVec,ROOT::Math::PtEtaPhiMVector &tmpTopTrailingVec,Int_t &tmpTopLeadCharge,Int_t &tmpTopTrailingCharge,float &difFromZMassOne, bool debug){
    if (debug) std::cout << "in dolZ1Cut fcn\n";
    for (UInt_t lItrOne=0; lItrOne<lepCandIndAr.size()-1; lItrOne++) { //LEP LOOP ONE
        Int_t tmpChargeOne = lepCandChargeAr[lItrOne];
        if (debug) std::cout << "lItrOne " << lItrOne << " lepCandIndAr[lItrOne] " << lepCandIndAr[lItrOne] << " tmpChargeOne " << tmpChargeOne << "\n";
        for (UInt_t lItrTwo=lItrOne+1; lItrTwo<lepCandIndAr.size(); lItrTwo++){ //LEP LOOP TWO
            Int_t tmpChargeTwo = lepCandChargeAr[lItrTwo];
            if (debug) std::cout << "lItrTwo " << lItrTwo << " lepCandIndAr[lItrTwo] " << lepCandIndAr[lItrTwo] << " tmpChargeOne " << tmpChargeTwo << "\n";
            if (tmpChargeOne != tmpChargeTwo){ //CHECK IF OPPOSITE CHARGE
                ROOT::Math::PtEtaPhiMVector tmpZ1VecOne = lepCandVecAr[lItrOne];
                ROOT::Math::PtEtaPhiMVector tmpZ1VecTwo = lepCandVecAr[lItrTwo];
                ROOT::Math::PtEtaPhiMVector tmpZ1Vec =  tmpZ1VecOne+tmpZ1VecTwo;
                float tmpZ1Mass = tmpZ1Vec.M();
                if (debug){
                    std::cout << "not the same charge. yay\n";
                    std::cout << "tmpZ1VecOne " << tmpZ1VecOne << "tmpZ1VecTwo " << tmpZ1VecTwo << "tmpZ1Vec " << tmpZ1Vec << "\n";
                }
                if (tmpZ1Mass > invMassCutLow && tmpZ1Mass < invMassCutHigh){ //CHECK IF INV MASS PASSES CUTS
                    if (debug) std::cout << "Passed inv mass cut\n";
                    float tmpZDif = abs(tmpZ1Mass - ZMass);
                    float tmpPtOne = Lep_pt[lepCandIndAr[lItrOne]];
                    float tmpPtTwo = Lep_pt[lepCandIndAr[lItrTwo]];
                    if (debug) std::cout << "tmpZDif " << tmpZDif << "tmpPtOne " << tmpPtOne << "tmpPtTwo " << tmpPtTwo << "\n";
                    float tmpPtLead;
                    float tmpPtTrailing;
                    UInt_t tmpLeadItr;
                    UInt_t tmpTrailingItr;
                    ROOT::Math::PtEtaPhiMVector tmpLeadVec;
                    ROOT::Math::PtEtaPhiMVector tmpTrailingVec;
                    Int_t tmpLeadCharge;
                    Int_t tmpTrailingCharge;
                    if (tmpPtOne >= tmpPtTwo){ //SORT PTS
                        //lepPassesZ2CutsAr.append([lepCandIndAr[lItrOne],lepCandIndAr[lItrTwo]])
                        tmpPtLead = tmpPtOne;
                        tmpPtTrailing = tmpPtTwo;
                        tmpLeadItr = lItrOne;
                        tmpTrailingItr = lItrTwo;
                        tmpLeadVec = tmpZ1VecOne;
                        tmpTrailingVec = tmpZ1VecTwo;
                        tmpLeadCharge = tmpChargeOne;
                        tmpTrailingCharge = tmpChargeTwo;
                    }
                    else{
                        //lepPassesZ2CutsAr.append([lepCandIndAr[lItrTwo],lepCandIndAr[lItrOne]])
                        tmpPtLead = tmpPtTwo;
                        tmpPtTrailing = tmpPtOne;
                        tmpLeadItr = lItrTwo;
                        tmpTrailingItr = lItrOne;
                        tmpLeadVec = tmpZ1VecTwo;
                        tmpTrailingVec = tmpZ1VecOne;
                        tmpLeadCharge = tmpChargeTwo;
                        tmpTrailingCharge = tmpChargeOne;
                    }


                    if (tmpZDif < difFromZMassOne){ //CHECK IF INV MASS DIF LESS THAN CURRENT SMALLEST DIF
                        if (debug) std::cout << "current smallest zdif yay\n";
                        
                        if (tmpPtLead > ptLeadCut && tmpPtTrailing > ptTrailingCut){ //CHECK IF PASSES PT CUT
                            if (debug) std::cout << "wow it passed the pt cut also yay\n";
                            tmpTopZ1LeadPt = tmpPtLead;
                            tmpTopZ1TrailingPt = tmpPtTrailing;
                            difFromZMassOne = tmpZDif;
                            tmpTopLeadItr = tmpLeadItr;
                            tmpTopTrailingItr = tmpTrailingItr;
                            if (debug) std::cout << "forMuon " << forMuon << " Z1IsMuon " << Z1IsMuon << "\n";
                            if (!forMuon) Z1IsMuon = false;
                            else Z1IsMuon = true;
                            if (debug) std::cout << "forMuon " << forMuon << " Z1IsMuon " << Z1IsMuon << "\n";
                            tmpTopLeadVec = tmpLeadVec;
                            tmpTopTrailingVec = tmpTrailingVec;
                            tmpTopLeadCharge = tmpLeadCharge;
                            tmpTopTrailingCharge = tmpTrailingCharge;
                        }
                    }
                    std::array<UInt_t,2> tmpItrList = {tmpLeadItr,tmpTrailingItr};
                    lepPassesZ2CutsAr.push_back(tmpItrList);
                    
                }
            }
        }
    }
}
                

void fillZ2Ars(std::vector<std::array<UInt_t,2>> &lepPassesZ2CutsFinalAr,std::vector<std::array<ROOT::Math::PtEtaPhiMVector,2>> &lZ2VecPairAr,std::vector<std::array<double,2>> &lZ2PtPairAr,std::vector<std::array<Int_t,2>> &lZ2ChargePairAr,std::vector<std::array<UInt_t,2>> lepPassesZ2CutsAr,std::vector<Int_t> lepCandChargeAr,std::vector<ROOT::Math::PtEtaPhiMVector> lepCandVecAr,bool shouldIgnore,std::array<Int_t,2> indsToIgnore,bool &Z2CandsBool){
    
    if (!shouldIgnore) lepPassesZ2CutsFinalAr = lepPassesZ2CutsAr;
    //std::cout << "lepPassesZ2CutsAr.size() "<< lepPassesZ2CutsAr.size() << "\n";
    for (UInt_t lepPassesZ2CutsInd=0;lepPassesZ2CutsInd<lepPassesZ2CutsAr.size();lepPassesZ2CutsInd++){ //Loop through lep Z2 cand pairs to fill all arrays
        if (shouldIgnore){
            //std::cout << "indsToIgnore[0] " <<indsToIgnore[0] << " indsToIgnore[1] " << indsToIgnore[1] << "\n";
            //std::cout << "lepPassesZ2CutsInd " <<lepPassesZ2CutsInd << "\n";
            //std::cout << "lepPassesZ2CutsAr[lepPassesZ2CutsInd] " <<lepPassesZ2CutsAr[lepPassesZ2CutsInd] << "\n";
            if (!(std::find(std::begin(lepPassesZ2CutsAr[lepPassesZ2CutsInd]), std::end(lepPassesZ2CutsAr[lepPassesZ2CutsInd]), indsToIgnore[0]) != std::end(lepPassesZ2CutsAr[lepPassesZ2CutsInd])) && !(std::find(std::begin(lepPassesZ2CutsAr[lepPassesZ2CutsInd]), std::end(lepPassesZ2CutsAr[lepPassesZ2CutsInd]), indsToIgnore[1]) != std::end(lepPassesZ2CutsAr[lepPassesZ2CutsInd]))){
                lepPassesZ2CutsFinalAr.push_back(lepPassesZ2CutsAr[lepPassesZ2CutsInd]);


                std::array<Int_t,2> tmplZ2ChargePair = {lepCandChargeAr[lepPassesZ2CutsAr[lepPassesZ2CutsInd][0]],lepCandChargeAr[lepPassesZ2CutsAr[lepPassesZ2CutsInd][1]]};
                lZ2ChargePairAr.push_back(tmplZ2ChargePair);
                ROOT::Math::PtEtaPhiMVector tmpVecOne = lepCandVecAr[lepPassesZ2CutsAr[lepPassesZ2CutsInd][0]];
                ROOT::Math::PtEtaPhiMVector tmpVecTwo = lepCandVecAr[lepPassesZ2CutsAr[lepPassesZ2CutsInd][1]];
                std::array<double,2> tmplZ2PtPair = {tmpVecOne.Pt(),tmpVecTwo.Pt()};
                std::array<ROOT::Math::PtEtaPhiMVector,2> tmplZ2VecPair = {tmpVecOne,tmpVecTwo};
                std::array<Int_t,2> tmpZ2ChargePair = {lepCandChargeAr[lepPassesZ2CutsAr[lepPassesZ2CutsInd][0]],lepCandChargeAr[lepPassesZ2CutsAr[lepPassesZ2CutsInd][1]]};
                
                lZ2PtPairAr.push_back(tmplZ2PtPair);
                lZ2VecPairAr.push_back(tmplZ2VecPair);
                Z2CandsBool = true;
            }
        }
        else{
            std::array<Int_t,2> tmplZ2ChargePair = {lepCandChargeAr[lepPassesZ2CutsAr[lepPassesZ2CutsInd][0]],lepCandChargeAr[lepPassesZ2CutsAr[lepPassesZ2CutsInd][1]]};
            lZ2ChargePairAr.push_back(tmplZ2ChargePair);
            ROOT::Math::PtEtaPhiMVector tmpVecOne = lepCandVecAr[lepPassesZ2CutsAr[lepPassesZ2CutsInd][0]];
            ROOT::Math::PtEtaPhiMVector tmpVecTwo = lepCandVecAr[lepPassesZ2CutsAr[lepPassesZ2CutsInd][1]];
            std::array<double,2> tmplZ2PtPair = {tmpVecOne.Pt(),tmpVecTwo.Pt()};
            std::array<ROOT::Math::PtEtaPhiMVector,2> tmplZ2VecPair = {tmpVecOne,tmpVecTwo};
            std::array<Int_t,2> tmpZ2ChargePair = {lepCandChargeAr[lepPassesZ2CutsAr[lepPassesZ2CutsInd][0]],lepCandChargeAr[lepPassesZ2CutsAr[lepPassesZ2CutsInd][1]]};
                
            lZ2PtPairAr.push_back(tmplZ2PtPair);
            lZ2VecPairAr.push_back(tmplZ2VecPair);
            Z2CandsBool = true;

        }
    }
}



void dolZ2Cut(ROOT::Math::PtEtaPhiMVector Z1LeadVec,ROOT::Math::PtEtaPhiMVector Z1TrailingVec,ROOT::Math::PtEtaPhiMVector tmpZ1Vec,float tmpZ1M,Int_t Z1LeadCharge,Int_t Z1TrailingCharge,bool Z1IsMuon,std::vector<std::array<ROOT::Math::PtEtaPhiMVector,2>> lZ2VecPairAr,std::vector<std::array<double,2>> lZ2PtPairAr,std::vector<std::array<Int_t,2>> lZ2ChargePairAr,Int_t &tmpZ2Ind,bool &Z2IsMuon,float &tmpTopZ2LeadPt,float &tmpTopZ2TrailingPt,float fourLepInvMassCut,float optLepInvMassCut, bool forElec){
    
    //tmpZ1Vec = Z1LeadVec+Z1TrailingVec;
    //float tmpZ1M = tmpZ1Vec.M();
    for (UInt_t Z2Itr=0;Z2Itr<lZ2VecPairAr.size();Z2Itr++){ //LOOP OVER ALL Z2 CANDIDATE PAIRS
        float tmpZ2LeadPt = lZ2PtPairAr[Z2Itr][0];
        if ((tmpZ2LeadPt > tmpTopZ2LeadPt) || (tmpZ2LeadPt == tmpTopZ2LeadPt  && lZ2PtPairAr[Z2Itr][1] > tmpTopZ2TrailingPt)){ //Check if passes lead Z2 pt cut
            ROOT::Math::PtEtaPhiMVector tmpZ4Vec = tmpZ1Vec+lZ2VecPairAr[Z2Itr][0]+lZ2VecPairAr[Z2Itr][1];
            if (tmpZ4Vec.M() > fourLepInvMassCut){ //Check if passes four lepton inv mass cut
                if ((forElec && !Z1IsMuon) || (!forElec && Z1IsMuon)){ //If Z1 is same lep type, then have to perform second 4e cuts
                    ROOT::Math::PtEtaPhiMVector tmpZ2Vec = lZ2VecPairAr[Z2Itr][0] + lZ2VecPairAr[Z2Itr][1];
                    float tmpZ2M = tmpZ2Vec.M();
                    ROOT::Math::PtEtaPhiMVector tmpLepPairVecOne;
                    ROOT::Math::PtEtaPhiMVector tmpLepPairVecTwo;
                    if (Z1LeadCharge != lZ2ChargePairAr[Z2Itr][0]){
                        tmpLepPairVecOne = Z1LeadVec + lZ2VecPairAr[Z2Itr][0];
                        tmpLepPairVecTwo = Z1TrailingVec + lZ2VecPairAr[Z2Itr][1];
                    }
                    else{
                        tmpLepPairVecOne = Z1LeadVec + lZ2VecPairAr[Z2Itr][1];
                        tmpLepPairVecTwo = Z1TrailingVec + lZ2VecPairAr[Z2Itr][0];
                    }

                    UInt_t tmpPassCtr = 0;
                    if (tmpLepPairVecOne.M() > optLepInvMassCut) tmpPassCtr += 1;
                    
                    if (tmpZ1M > optLepInvMassCut) tmpPassCtr += 1;
                    
                    if (tmpZ2M > optLepInvMassCut) tmpPassCtr += 1;
                    
                    if (tmpPassCtr >= 3){
                        tmpZ2Ind = Z2Itr;
                        tmpTopZ2LeadPt = tmpZ2LeadPt;
                        tmpTopZ2TrailingPt = lZ2PtPairAr[Z2Itr][1];
                        Z2IsMuon = !forElec;
                    }
                    else if (tmpPassCtr == 2){
                        if (tmpLepPairVecTwo.M() > optLepInvMassCut){
                            tmpZ2Ind = Z2Itr;
                            tmpTopZ2LeadPt = tmpZ2LeadPt;
                            tmpTopZ2TrailingPt = lZ2PtPairAr[Z2Itr][1];
                            Z2IsMuon = !forElec;
                        }
                    }
                }
                else{
                    tmpZ2Ind = Z2Itr;
                    tmpTopZ2LeadPt = tmpZ2LeadPt;
                    tmpTopZ2TrailingPt = lZ2PtPairAr[Z2Itr][1];
                    Z2IsMuon = !forElec;
                }
            }
        }
    }   
}

bool doISOCut(float Z1LeadIso,float Z1TrailingIso,float Z2LeadIso,float Z2TrailingIso,float lepIsoCut){
    if (Z1LeadIso + Z1TrailingIso >= lepIsoCut) return false;
    else if (Z1LeadIso + Z2LeadIso >= lepIsoCut) return false;
    else if (Z1LeadIso + Z2TrailingIso >= lepIsoCut) return false;
    else if (Z1TrailingIso + Z2LeadIso >= lepIsoCut) return false;
    else if (Z1TrailingIso + Z2TrailingIso >= lepIsoCut) return false;
    else if (Z2LeadIso + Z2TrailingIso >= lepIsoCut) return false;
    else return true;
}

bool doSIPCut(float Z1LeadSIP,float Z1TrailingSIP,float Z2LeadSIP,float Z2TrailingSIP,float SIPCut){
    if (Z1LeadSIP > SIPCut) return false;
    else if (Z1TrailingSIP > SIPCut) return false;
    if (Z2LeadSIP > SIPCut) return false;
    else if (Z2TrailingSIP > SIPCut) return false;
    else return true;
}

bool doSemiLepISOCut(float leadIso,float trailingIso,float lepIsoCut){
    if (leadIso + trailingIso >= lepIsoCut) return false;
    else return true;
}


void doVBFJetCut(UInt_t nJetLen,TTreeReaderArray<Float_t> &Jet_pt,TTreeReaderArray<Int_t> &Jet_jetId,TTreeReaderArray<Float_t> &Jet_eta,TTreeReaderArray<Float_t> &Jet_phi,TTreeReaderArray<Float_t> &Jet_mass,float jetPTCut,float jetEtaDifCut,float jetInvMassCut,float &jetPairInvMass,float &jetLeadPt,float &jetLeadEta,float &jetLeadPhi,float &jetTrailingPt,float &jetTrailingEta,float &jetTrailingPhi,UInt_t &leadJet_1,UInt_t &leadJet_2,vector<float> &selectedFJ_phi,vector<float> &selectedFJ_eta,bool debug){
    //debug = true;
    for (UInt_t jetIndOne=0; jetIndOne<nJetLen-1;jetIndOne++){
        float jetPtOne = Jet_pt[jetIndOne];
        Int_t jetIdOne = Jet_jetId[jetIndOne];
        if (debug) std::cout << "jetIndOne: " << jetIndOne << " Jet_pt[jetIndOne]: " << Jet_pt[jetIndOne] << " Jet_jetId[jetIndOne]: " << Jet_jetId[jetIndOne] << "\n";
        if (jetPtOne < jetPTCut || !(jetIdOne == 6)) continue;
        for (UInt_t jetIndTwo=jetIndOne+1; jetIndTwo<nJetLen; jetIndTwo++){
            float jetPtTwo = Jet_pt[jetIndTwo];
            Int_t jetIdTwo = Jet_jetId[jetIndTwo];
            if (debug) std::cout << "jetIndTwo: " << jetIndTwo << " Jet_pt[jetIndTwo]: " << Jet_pt[jetIndTwo] << " Jet_jetId[jetIndTwo]: " << Jet_jetId[jetIndTwo] << "\n";
            if (jetPtTwo < jetPTCut || !(jetIdTwo == 6)) continue;
            
            float jetEtaOne = Jet_eta[jetIndOne];
            float jetEtaTwo = Jet_eta[jetIndTwo];
            if (debug) std::cout << "jetEtaOne: " << jetEtaOne << " jetEtaTwo: " << jetEtaTwo << " jetEtaDifCut: " << jetEtaDifCut << "\n";
            if (abs(jetEtaOne - jetEtaTwo) < jetEtaDifCut) continue;
            
            float jetPhiOne = Jet_phi[jetIndOne];
            float jetPhiTwo = Jet_phi[jetIndTwo];
            float jetMassOne = Jet_mass[jetIndOne];
            float jetMassTwo = Jet_mass[jetIndTwo];
            ROOT::Math::PtEtaPhiMVector tmpVecOne = ROOT::Math::PtEtaPhiMVector(jetPtOne, jetEtaOne, jetPhiOne, jetMassOne);
            ROOT::Math::PtEtaPhiMVector tmpVecTwo = ROOT::Math::PtEtaPhiMVector(jetPtTwo, jetEtaTwo, jetPhiTwo, jetMassTwo);
            ROOT::Math::PtEtaPhiMVector tmpVecSum = tmpVecOne+tmpVecTwo;
            float tmpJetPairInvMass = tmpVecSum.M();

            if (debug) std::cout << "tmpJetPairInvMass: " << tmpJetPairInvMass << " jetInvMassCut: " << jetInvMassCut << "\n";


            if (tmpJetPairInvMass < jetInvMassCut) continue;
            if (tmpJetPairInvMass > jetPairInvMass){
                //Check dR to Higgs and Z FJs
                bool FJdRPass = true;
                for (UInt_t tmpFJItr=0;tmpFJItr<selectedFJ_phi.size();tmpFJItr++){
  
                    if (calcDeltaR(selectedFJ_phi[tmpFJItr],selectedFJ_eta[tmpFJItr],jetPhiOne,jetEtaOne) <= hFatJetdRCut) {
                        FJdRPass = false;
                        break;
                    }
                    if (calcDeltaR(selectedFJ_phi[tmpFJItr],selectedFJ_eta[tmpFJItr],jetPhiTwo,jetEtaTwo) <= hFatJetdRCut) {
                        FJdRPass = false;
                        break;
                    }
                }
                if (debug) std::cout << "FJdRPass: " << FJdRPass << " FJdRPass: " << FJdRPass << "\n";
                if (FJdRPass){
                    jetPairInvMass = tmpJetPairInvMass;
                    if (jetPtOne >= jetPtTwo) {
                        jetLeadPt = jetPtOne;
                        jetLeadEta = jetEtaOne;
                        jetLeadPhi = jetPhiOne;
                        jetTrailingPt = jetPtTwo;
                        jetTrailingEta = jetEtaTwo;
                        jetTrailingPhi = jetPhiTwo;
                        leadJet_1 = jetIndOne;
                        leadJet_2 = jetIndTwo;
                    }
                    else {
                        jetLeadPt = jetPtTwo;
                        jetLeadEta = jetEtaTwo;
                        jetLeadPhi = jetPhiTwo;
                        jetTrailingPt = jetPtOne;
                        jetTrailingEta = jetEtaOne;
                        jetTrailingPhi = jetPhiOne;
                        leadJet_1 = jetIndTwo;
                        leadJet_2 = jetIndOne;
                    }
                }
            }
        }
    }
    //debug = false;
}

void debugOutputForVBFJetCut(UInt_t evCount,UInt_t leadJet_1,UInt_t leadJet_2,TTreeReaderArray<Float_t> &Jet_phi,TTreeReaderArray<Float_t> &Jet_eta,bool debug){
    if (debug){
        std::cout << " found jet pairs\n";
        std::cout << evCount+1 << " selected jet pair\n";
        std::cout << "Lead jet ind    " << leadJet_1 << "\n";
        std::cout << "Trailing jet ind    " << leadJet_2 << "\n";
        std::cout << "Lead jet phi    " << Jet_phi[leadJet_1] << "\n";
        std::cout << "Trailing jet phi    " << Jet_phi[leadJet_2] << "\n";
        std::cout << "Lead jet eta    " << Jet_eta[leadJet_1] << "\n";
        std::cout << "Trailing jet eta    " << Jet_eta[leadJet_2] << "\n";
    }
}
/*
void doHiggsFatJetCut(UInt_t nFatJetLen,float &hFatJet_HTag_fromPt,float &hFatJet_pt_fromPt,float &hFatJet_phi_fromPt,float &hFatJet_eta_fromPt,float &hFatJet_mass_fromPt,float &hFatJet_pt_fromHTag,float &hFatJet_phi_fromHTag,float &hFatJet_eta_fromHTag,float &hFatJet_mass_fromHTag,float &hFatJet_HTag_fromHTag,UInt_t &hFatJet_ind_fromHTag,TTreeReaderArray<Float_t> &FatJet_deepTag_H,float hFatJetDeepTagCut,TTreeReaderArray<Float_t> &FatJet_pt,float hFatJetPTCut,TTreeReaderArray<Int_t> &FatJet_jetId,TTreeReaderArray<Float_t> &FatJet_phi,TTreeReaderArray<Float_t> &FatJet_eta,float jetLeadPhi,float jetLeadEta,float jetTrailingPhi,float jetTrailingEta,float hFatJetdRCut,TTreeReaderArray<Float_t> &FatJet_mass){
    for (UInt_t fatJetInd=0;fatJetInd<nFatJetLen;fatJetInd++){
        float tmpFatJet_deepTag_H = FatJet_deepTag_H[fatJetInd];

        if (debug) {
            std::cout << fatJetInd << " +++++++++++++++\n";
            std::cout << "Fat jet DeepTag_H    " <<  tmpFatJet_deepTag_H << "\n";
        }
        
        if (tmpFatJet_deepTag_H > hFatJetDeepTagCut){
            float tmpFatJet_pt = FatJet_pt[fatJetInd];

            if (debug){
                std::cout << "Fat jet pt    " <<  tmpFatJet_pt << "\n";
            }
            
            if (tmpFatJet_pt > hFatJetPTCut){
                Int_t tmpFatJet_jetId = FatJet_jetId[fatJetInd];

                if (debug){
                    std::cout << "Fat jet jetId    " <<  tmpFatJet_jetId << "\n";
                }

                if (tmpFatJet_jetId == 6){
                    float tmpFatJet_phi = FatJet_phi[fatJetInd];
                    float tmpFatJet_eta = FatJet_eta[fatJetInd];
                    float tmpDROne = calcDeltaR(tmpFatJet_phi,tmpFatJet_eta,jetLeadPhi,jetLeadEta);
                    float tmpDRTwo = calcDeltaR(tmpFatJet_phi,tmpFatJet_eta,jetTrailingPhi,jetTrailingEta);

                    if (debug){
                        std::cout << "Fat jet phi    " <<  tmpFatJet_phi << "\n";
                        std::cout << "Fat jet eta    " <<  tmpFatJet_eta << "\n";
                        std::cout << "Fat jet dROne    " <<  tmpDROne << " \n";
                        std::cout << "Fat jet dRTwo    " <<  tmpDRTwo << " \n";
                    }
                    
                    if (tmpDROne > hFatJetdRCut && tmpDRTwo > hFatJetdRCut){

                        if (debug) std::cout << "Passed fatjet cuts\n";

                        //float tmpFatJet_HTag = FatJet_deepTag_H[fatJetInd];
                        if (tmpFatJet_pt > hFatJet_pt_fromPt){
                            hFatJet_HTag_fromPt = tmpFatJet_deepTag_H;
                            hFatJet_pt_fromPt = tmpFatJet_pt;
                            hFatJet_eta_fromPt = tmpFatJet_eta;
                            hFatJet_phi_fromPt = tmpFatJet_phi;
                            hFatJet_mass_fromPt = FatJet_mass[fatJetInd];
                        }
                        
                        if (tmpFatJet_deepTag_H > hFatJet_HTag_fromHTag){
                            hFatJet_HTag_fromHTag = tmpFatJet_deepTag_H;
                            hFatJet_pt_fromHTag = tmpFatJet_pt;
                            hFatJet_eta_fromHTag = tmpFatJet_eta;
                            hFatJet_phi_fromHTag = tmpFatJet_phi;
                            hFatJet_mass_fromHTag = FatJet_mass[fatJetInd];
                            hFatJet_ind_fromHTag = fatJetInd;
                        }
                    }
                }
            }
        }
    }
}
*/

void doHiggsFatJetCut(UInt_t nFatJetLen,float &hFatJet_pt_fromHTag,float &hFatJet_phi_fromHTag,float &hFatJet_eta_fromHTag,float &hFatJet_mass_fromHTag,float &hFatJet_HTag_fromHTag,UInt_t &hFatJet_ind_fromHTag,TTreeReaderArray<Float_t> &FatJet_deepTag_H,float hFatJetDeepTagCut,TTreeReaderArray<Float_t> &FatJet_pt,float hFatJetPTCut,TTreeReaderArray<Int_t> &FatJet_jetId,TTreeReaderArray<Float_t> &FatJet_phi,TTreeReaderArray<Float_t> &FatJet_eta,TTreeReaderArray<Float_t> &FatJet_mass,vector<float> &selectedFJ_phi,vector<float> &selectedFJ_eta){
    float tmpFJHTagMax = hFatJetDeepTagCut;
    for (UInt_t fatJetInd=0;fatJetInd<nFatJetLen;fatJetInd++){
        float tmpFatJet_deepTag_H = FatJet_deepTag_H[fatJetInd];

        if (debug) {
            std::cout << fatJetInd << " +++++++++++++++\n";
            std::cout << "Fat jet DeepTag_H    " <<  tmpFatJet_deepTag_H << "\n";
        }
        
        if (tmpFatJet_deepTag_H > tmpFJHTagMax){
            float tmpFatJet_pt = FatJet_pt[fatJetInd];

            if (debug){
                std::cout << "Fat jet pt    " <<  tmpFatJet_pt << "\n";
            }
            
            if (tmpFatJet_pt > hFatJetPTCut){
                Int_t tmpFatJet_jetId = FatJet_jetId[fatJetInd];

                if (debug){
                    std::cout << "Fat jet jetId    " <<  tmpFatJet_jetId << "\n";
                }

                if (tmpFatJet_jetId == 6){
                    
                    

                    if (debug) std::cout << "Passed fatjet cuts\n";

                    if (tmpFatJet_deepTag_H > hFatJet_HTag_fromHTag){
                        if (debug) std::cout << "HTag greater than previous FJ HTag\n";
                        float tmpFatJet_phi = FatJet_phi[fatJetInd];
                        float tmpFatJet_eta = FatJet_eta[fatJetInd];
                        if (debug){
                            std::cout << "Fat jet phi    " <<  tmpFatJet_phi << "\n";
                            std::cout << "Fat jet eta    " <<  tmpFatJet_eta << "\n";
                        }
                        hFatJet_HTag_fromHTag = tmpFatJet_deepTag_H;
                        hFatJet_pt_fromHTag = tmpFatJet_pt;
                        hFatJet_eta_fromHTag = tmpFatJet_eta;
                        hFatJet_phi_fromHTag = tmpFatJet_phi;
                        hFatJet_mass_fromHTag = FatJet_mass[fatJetInd];
                        hFatJet_ind_fromHTag = fatJetInd;
                        tmpFJHTagMax = tmpFatJet_deepTag_H;
                    }
                    
                }
            }
        }
    }
    selectedFJ_phi.push_back(hFatJet_phi_fromHTag);
    selectedFJ_eta.push_back(hFatJet_eta_fromHTag);
}

void doSemiLepChanFatJetCut(Int_t &FJInd,Int_t numFatJet,UInt_t hFatJet_ind_fromHTag,float fatJetPTCut,float fatJetZTagCut,TTreeReaderArray<Float_t> &FatJet_pt,TTreeReaderArray<Float_t> &FatJet_phi,TTreeReaderArray<Float_t> &FatJet_eta,TTreeReaderArray<Float_t> &FatJet_deepTag_ZvsQCD,vector<float> &selectedFJ_phi,vector<float> &selectedFJ_eta){
    float semiLepFatJetPT = 0;
    float semiLepFatJetTag = 0;
    float semiLepFatJet_phi = 0;
    float semiLepFatJet_eta = 0;
    for (UInt_t i=0; i<numFatJet;i++){

        //Skip selected higgs fatjet
        if (i == hFatJet_ind_fromHTag) continue;

        float tmpFatJetPT = FatJet_pt[i];
        float tmpFatJetTag = FatJet_deepTag_ZvsQCD[i];
        //Trying out tagging instead of pt for choosing final H FJ
        //if (tmpFatJetTag > fatJetZTagCut && tmpFatJetPT > fatJetPTCut && tmpFatJetPT > semiLepFatJetPT){
        if (tmpFatJetTag > fatJetZTagCut && tmpFatJetPT > fatJetPTCut && tmpFatJetTag > semiLepFatJetTag){
            FJInd = i;
            semiLepFatJetPT = tmpFatJetPT;
            semiLepFatJetTag = tmpFatJetTag;
            semiLepFatJet_phi = FatJet_phi[i];
            semiLepFatJet_eta = FatJet_eta[i];
            
        }
    }
    if (FJInd >= 0) {
        selectedFJ_phi.push_back(semiLepFatJet_phi);
        selectedFJ_eta.push_back(semiLepFatJet_eta);
    }
    

}

void doHadChanFatJetCut(Int_t &LFJOneInd,Int_t &LFJTwoInd,Int_t numFatJet,UInt_t hFatJet_ind_fromHTag,float fatJetPTCut,float fatJetZPairInvMassCut,TTreeReaderArray<Float_t> &FatJet_pt,TTreeReaderArray<Float_t> &FatJet_phi,TTreeReaderArray<Float_t> &FatJet_eta,TTreeReaderArray<Float_t> &FatJet_mass,TTreeReaderArray<Float_t> &FatJet_deepTag_ZvsQCD,vector<float> &selectedFJ_phi,vector<float> &selectedFJ_eta,float HFJ_pt){

    float leadFatJetMaxTag = 0;
    float secondFatJetMaxTag = 0;
    float leadFatJet_phi = 0;
    float leadFatJet_eta = 0;
    float secondFatJet_phi = 0;
    float secondFatJet_eta = 0;
    for (UInt_t i=0;i<numFatJet-1;i++){
        if (debugHadronic) std::cout << "First FatJet " << i << "\n";

        //Skip selected higgs fatjet
        if (i == hFatJet_ind_fromHTag) continue;

        float tmpFatJet_phi_One = FatJet_phi[i];
        float tmpFatJet_eta_One = FatJet_eta[i];
        float tmpFatJet_Tag_One = FatJet_deepTag_ZvsQCD[i];


        float tmpFatJetPT = FatJet_pt[i];
        if (debugHadronic) std::cout << "tmpFatJetPT " << tmpFatJetPT << "\n";

        if (tmpFatJet_Tag_One > fatJetZTagCut && tmpFatJetPT > fatJetPTCut){
            //Looping through all jets past the current one
            for (UInt_t j=i+1;j<numFatJet;j++){
                if (debugHadronic) std::cout << "Second FatJet " << j << "\n";

                //Skip selected higgs fatjet
                if (j == hFatJet_ind_fromHTag) continue;

                float tmpFatJet_phi_Two = FatJet_phi[j];
                float tmpFatJet_eta_Two = FatJet_eta[j];
                float tmpFatJet_Tag_Two = FatJet_deepTag_ZvsQCD[j];

                //Getting PT of the second jet
                float tmpFatJetPTTwo = FatJet_pt[j];

                if (debugHadronic) std::cout << "tmpFatJetPTTwo " << tmpFatJetPTTwo << "\n";

                //Checking if it passes the pt cut and tag cut
                if (tmpFatJet_Tag_Two > fatJetZTagCut && tmpFatJetPTTwo > fatJetPTCut){
                    float tmpZPairPlusH_pt = HFJ_pt + tmpFatJetPT + tmpFatJetPTTwo;
                    if (tmpZPairPlusH_pt > fatJetZPlusHPTCut){
                        if (debugHadronic) std::cout << "Passed all cuts!!!!!!!!!!!!!!\n";
                        
                        //Selecting on top jet pt first
                        float tmpMaxPtLead = 0;
                        float tmpMaxPtSecond = 0;
                        float tmpMaxTagLead = 0;
                        float tmpMaxTagSecond = 0;
                        UInt_t tmpFJLeadInd=0;
                        UInt_t tmpFJTrailingInd=0;
                        //Sorting which jet has the larger pt
                        if (tmpFatJetPT > tmpFatJetPTTwo){
                            tmpMaxPtLead = tmpFatJetPT;
                            tmpMaxPtSecond = tmpFatJetPTTwo;
                            tmpMaxTagLead = tmpFatJet_Tag_One;
                            tmpMaxTagSecond = tmpFatJet_Tag_Two;
                            tmpFJLeadInd = i;
                            tmpFJTrailingInd = j;

                        }
                        else{
                            tmpMaxPtLead = tmpFatJetPTTwo;
                            tmpMaxPtSecond = tmpFatJetPT;
                            tmpMaxTagLead = tmpFatJet_Tag_Two;
                            tmpMaxTagSecond = tmpFatJet_Tag_One;
                            tmpFJLeadInd = j;
                            tmpFJTrailingInd = i;
                        }

                        //Selecting based on that jet's tag value
                        if (tmpMaxTagLead > leadFatJetMaxTag){
                            leadFatJetMaxTag = tmpMaxTagLead;
                            secondFatJetMaxTag = tmpMaxTagSecond;

                            leadFatJet_phi = FatJet_phi[tmpFJLeadInd];
                            leadFatJet_eta = FatJet_eta[tmpFJLeadInd];
                            secondFatJet_phi = FatJet_phi[tmpFJTrailingInd];
                            secondFatJet_eta = FatJet_eta[tmpFJTrailingInd];

                            LFJOneInd = tmpFJLeadInd;
                            LFJTwoInd = tmpFJTrailingInd;
                        }
                        //If that jet is already part of the current selected pair,
                        //select based on the respective lower pt jets in the pairs
                        else if (tmpMaxTagLead == leadFatJetMaxTag){
                            if (tmpMaxTagSecond > secondFatJetMaxTag){
                                secondFatJetMaxTag = tmpMaxTagSecond;

                                leadFatJet_phi = FatJet_phi[tmpFJLeadInd];
                                leadFatJet_eta = FatJet_eta[tmpFJLeadInd];
                                secondFatJet_phi = FatJet_phi[tmpFJTrailingInd];
                                secondFatJet_eta = FatJet_eta[tmpFJTrailingInd];


                                LFJOneInd = tmpFJLeadInd;
                                LFJTwoInd = tmpFJTrailingInd;
                            }
                        }

                        /*

                        //Selecting based on that jet's pt
                        if (tmpMaxPtLead > leadFatJetMaxPT){
                            leadFatJetMaxPT = tmpMaxPtLead;
                            secondFatJetMaxPT = tmpMaxPtSecond;
                            LFJOneInd = tmpFJLeadInd;
                            LFJTwoInd = tmpFJTrailingInd;
                            FJInvMass = tmpFJInvMass;
                        }
                        //If that jet is already part of the current selected pair,
                        //select based on the respective lower pt jets in the pairs
                        else if (tmpMaxPtLead == leadFatJetMaxPT){
                            if (tmpMaxPtSecond > secondFatJetMaxPT){
                                secondFatJetMaxPT = tmpMaxPtSecond;
                                LFJOneInd = tmpFJLeadInd;
                                LFJTwoInd = tmpFJTrailingInd;
                                FJInvMass = tmpFJInvMass;
                            }
                        }
                        */

                        //Removed inv mass cuts here. Could put them back in but need to see first

                        /*
                        //Getting the eta dif between the two jets
                        tmpEtaDif = abs(FatJet_eta[i]-FatJet_eta[j]);

                        if (debugHadronic) std::cout << "tmpEtaDif " << tmpEtaDif << "\n";

                        //Getting four vectors for the two jets, using pt, eta, phi, and mass
                        ROOT::Math::PtEtaPhiMVector tmpVecOne = ROOT::Math::PtEtaPhiMVector(tmpFatJetPT, tmpFatJet_eta_One, tmpFatJet_phi_One, FatJet_mass[i]);
                        ROOT::Math::PtEtaPhiMVector tmpVecTwo = ROOT::Math::PtEtaPhiMVector(tmpFatJetPTTwo, tmpFatJet_eta_Two, tmpFatJet_phi_Two, FatJet_mass[j]);
                        //Adding four vectors together and getting their invariant mass
                        ROOT::Math::PtEtaPhiMVector tmpDiJetVec = tmpVecOne+tmpVecTwo;
                        float tmpFJInvMass = tmpDiJetVec.M();
                        if (debugHadronic) std::cout << "tmpFJInvMass " << tmpFJInvMass << "\n";

                        //Checking if their InvMass passes the InvMass cut
                        if (tmpFJInvMass > fatJetZPairInvMassCut){
                            if (debugHadronic) std::cout << "Passed all cuts!!!!!!!!!!!!!!\n";
                            
                            //Selecting on top jet pt first
                            float tmpMaxPtLead = 0;
                            float tmpMaxPtSecond = 0;
                            UInt_t tmpFJLeadInd=0;
                            UInt_t tmpFJTrailingInd=0;
                            //Sorting which jet has the larger pt
                            if (tmpFatJetPT > tmpFatJetPTTwo){
                                tmpMaxPtLead = tmpFatJetPT;
                                tmpMaxPtSecond = tmpFatJetPTTwo;
                                tmpFJLeadInd = i;
                                tmpFJTrailingInd = j;
                            }
                            else{
                                tmpMaxPtLead = tmpFatJetPTTwo;
                                tmpMaxPtSecond = tmpFatJetPT;
                                tmpFJLeadInd = j;
                                tmpFJTrailingInd = i;
                            }

                            //Selecting based on that jet's pt
                            if (tmpMaxPtLead > leadFatJetMaxPT){
                                leadFatJetMaxPT = tmpMaxPtLead;
                                secondFatJetMaxPT = tmpMaxPtSecond;
                                LFJOneInd = tmpFJLeadInd;
                                LFJTwoInd = tmpFJTrailingInd;
                                FJInvMass = tmpFJInvMass;
                            }
                            //If that jet is already part of the current selected pair,
                            //select based on the respective lower pt jets in the pairs
                            else if (tmpMaxPtLead == leadFatJetMaxPT){
                                if (tmpMaxPtSecond > secondFatJetMaxPT){
                                    secondFatJetMaxPT = tmpMaxPtSecond;
                                    LFJOneInd = tmpFJLeadInd;
                                    LFJTwoInd = tmpFJTrailingInd;
                                    FJInvMass = tmpFJInvMass;
                                }
                            }
                        }
                        */
                    }
                }
            }
        }
    }
    if (LFJOneInd >= 0 && LFJTwoInd >= 0){
        selectedFJ_phi.push_back(leadFatJet_phi);
        selectedFJ_phi.push_back(secondFatJet_phi);
        selectedFJ_eta.push_back(leadFatJet_eta);
        selectedFJ_eta.push_back(secondFatJet_eta);
    }
}

