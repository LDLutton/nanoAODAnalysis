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
                    std::array<UInt_t,2> tmpItrList = {tmpLeadItr,tmpTrailingItr};
                    lepPassesZ2CutsAr.push_back(tmpItrList);
                    }
                }
            }
        }
    }
}
                

void fillZ2Ars(std::vector<std::array<UInt_t,2>> &lepPassesZ2CutsFinalAr,std::vector<std::array<ROOT::Math::PtEtaPhiMVector,2>> &lZ2VecPairAr,std::vector<std::array<double,2>> &lZ2PtPairAr,std::vector<std::array<Int_t,2>> &lZ2ChargePairAr,std::vector<std::array<UInt_t,2>> lepPassesZ2CutsAr,std::vector<Int_t> lepCandChargeAr,std::vector<ROOT::Math::PtEtaPhiMVector> lepCandVecAr,bool shouldIgnore,std::array<Int_t,2> indsToIgnore,bool &Z2CandsBool){
    
    if (shouldIgnore) lepPassesZ2CutsFinalAr = lepPassesZ2CutsAr;
    for (UInt_t lepPassesZ2CutsInd=0;lepPassesZ2CutsInd<lepPassesZ2CutsAr.size();lepPassesZ2CutsInd++){ //Loop through lep Z2 cand pairs to fill all arrays
        if (shouldIgnore){
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



void dolZ2Cut(ROOT::Math::PtEtaPhiMVector Z1LeadVec,ROOT::Math::PtEtaPhiMVector Z1TrailingVec,ROOT::Math::PtEtaPhiMVector tmpZ1Vec,Int_t Z1LeadCharge,Int_t Z1TrailingCharge,bool Z1IsMuon,std::vector<std::array<ROOT::Math::PtEtaPhiMVector,2>> lZ2VecPairAr,std::vector<std::array<double,2>> lZ2PtPairAr,std::vector<std::array<Int_t,2>> lZ2ChargePairAr,Int_t &tmpZ2Ind,bool &Z2IsMuon,float &tmpTopZ2LeadPt,float &tmpTopZ2TrailingPt,float fourLepInvMassCut,float optLepInvMassCut, bool forElec){
    
    tmpZ1Vec = Z1LeadVec+Z1TrailingVec;
    float tmpZ1M = tmpZ1Vec.M();
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
                        Z2IsMuon = false;
                    }
                    else if (tmpPassCtr == 2){
                        if (tmpLepPairVecTwo.M() > optLepInvMassCut){
                            tmpZ2Ind = Z2Itr;
                            tmpTopZ2LeadPt = tmpZ2LeadPt;
                            tmpTopZ2TrailingPt = lZ2PtPairAr[Z2Itr][1];
                            Z2IsMuon = false;
                        }
                    }
                }
                else{
                    tmpZ2Ind = Z2Itr;
                    tmpTopZ2LeadPt = tmpZ2LeadPt;
                    tmpTopZ2TrailingPt = lZ2PtPairAr[Z2Itr][1];
                    Z2IsMuon = false;
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

