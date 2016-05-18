// -*- C++ -*-
//
// Package:    JetProperties
// Class:      JetProperties
// 
/**\class JetProperties JetProperties.cc RA2Classic/JetProperties/src/JetProperties.cc
 * 
 * Description: [one line class summary]
 * 
 * Implementation:
 *     [Notes on implementation]
 */
//
// Original Author:  Arne-Rasmus Draeger,68/111,4719,
//         Created:  Fri Apr 11 16:35:33 CEST 2014
// $Id$
//
//


// system include files
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <map>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/Candidate/interface/Candidate.h"

//enum lists of properties
enum JetPropD { d_jetArea, d_chargedHadronEnergyFraction, d_neutralHadronEnergyFraction, d_chargedEmEnergyFraction, d_neutralEmEnergyFraction,
				d_electronEnergyFraction, d_photonEnergyFraction, d_muonEnergyFraction, d_bDiscriminatorCSV, d_bDiscriminatorMVA,
				d_qgLikelihood, d_qgPtD, d_qgAxis2,
				d_prunedMass, d_bDiscriminatorSubjet1, d_bDiscriminatorSubjet2, d_NsubjettinessTau1, d_NsubjettinessTau2, d_NsubjettinessTau3 }; //AK8 properties
enum JetPropI { i_chargedHadronMultiplicity, i_neutralHadronMultiplicity, i_electronMultiplicity, i_photonMultiplicity,
				i_muonMultiplicity, i_NumBhadrons, i_NumChadrons, i_chargedMultiplicity, i_neutralMultiplicity, i_partonFlavor, i_hadronFlavor, i_qgMult };

// helper class
template <class T>
class NamedPtr {
	public:
		//constructor
		NamedPtr() : name("") {}
		NamedPtr(std::string name_, edm::EDProducer* edprod) : name(name_), ptr(new std::vector<T>()) {
			edprod->produces<std::vector<T>>(name).setBranchAlias(name);
		}
		//destructor
		virtual ~NamedPtr() {}
		//accessors
		void put(edm::Event& iEvent) { iEvent.put(ptr,name); }
		void reset() { ptr.reset(new std::vector<T>()); }
		void push_back(T tmp) { ptr->push_back(tmp); }
		virtual void get_property(const pat::Jet* Jet) { }
	
		//member variables
		std::string name;
		std::auto_ptr< std::vector<T> > ptr;
};

// specialized helper classes
template <JetPropD D>
class NamedPtrD : public NamedPtr<double> {
	public:
		using NamedPtr<double>::NamedPtr;
		virtual void get_property(const pat::Jet* Jet) { }
};

template <JetPropI I>
class NamedPtrI : public NamedPtr<int> {
	public:
		using NamedPtr<int>::NamedPtr;
		virtual void get_property(const pat::Jet* Jet) { }
};

//define accessors
template<> void NamedPtrD<d_jetArea>::get_property(const pat::Jet* Jet)                     { push_back(Jet->jetArea()); }
template<> void NamedPtrD<d_chargedHadronEnergyFraction>::get_property(const pat::Jet* Jet) { push_back(Jet->chargedHadronEnergyFraction()); }
template<> void NamedPtrD<d_neutralHadronEnergyFraction>::get_property(const pat::Jet* Jet) { push_back(Jet->neutralHadronEnergyFraction()); }
template<> void NamedPtrD<d_chargedEmEnergyFraction>::get_property(const pat::Jet* Jet)     { push_back(Jet->chargedEmEnergyFraction()); }
template<> void NamedPtrD<d_neutralEmEnergyFraction>::get_property(const pat::Jet* Jet)     { push_back(Jet->neutralEmEnergyFraction()); }
template<> void NamedPtrD<d_electronEnergyFraction>::get_property(const pat::Jet* Jet)      { push_back(Jet->electronEnergyFraction()); }
template<> void NamedPtrD<d_photonEnergyFraction>::get_property(const pat::Jet* Jet)        { push_back(Jet->photonEnergyFraction()); }
template<> void NamedPtrD<d_muonEnergyFraction>::get_property(const pat::Jet* Jet)          { push_back(Jet->muonEnergyFraction()); }
//bDiscriminators get special attention
template<> void NamedPtrD<d_qgLikelihood>::get_property(const pat::Jet* Jet)                { push_back(Jet->userFloat("QGTagger:qgLikelihood")); }
template<> void NamedPtrD<d_qgPtD>::get_property(const pat::Jet* Jet)                       { push_back(Jet->userFloat("QGTagger:ptD")); }
template<> void NamedPtrD<d_qgAxis2>::get_property(const pat::Jet* Jet)                     { push_back(Jet->userFloat("QGTagger:axis2")); }
//ak8 jet accessors
template<> void NamedPtrD<d_prunedMass>::get_property(const pat::Jet* Jet)                  { push_back(Jet->userFloat("ak8PFJetsCHSPrunedMass")); }
//bDiscriminatorSubjet1,2 get special attention                                             
template<> void NamedPtrD<d_NsubjettinessTau1>::get_property(const pat::Jet* Jet)           { push_back(Jet->userFloat("NjettinessAK8:tau1")); }
template<> void NamedPtrD<d_NsubjettinessTau2>::get_property(const pat::Jet* Jet)           { push_back(Jet->userFloat("NjettinessAK8:tau2")); }
template<> void NamedPtrD<d_NsubjettinessTau3>::get_property(const pat::Jet* Jet)           { push_back(Jet->userFloat("NjettinessAK8:tau3")); }
template<> void NamedPtrI<i_chargedHadronMultiplicity>::get_property(const pat::Jet* Jet)   { push_back(Jet->chargedHadronMultiplicity()); }
template<> void NamedPtrI<i_neutralHadronMultiplicity>::get_property(const pat::Jet* Jet)   { push_back(Jet->neutralHadronMultiplicity()); }
template<> void NamedPtrI<i_electronMultiplicity>::get_property(const pat::Jet* Jet)        { push_back(Jet->electronMultiplicity()); }
template<> void NamedPtrI<i_photonMultiplicity>::get_property(const pat::Jet* Jet)          { push_back(Jet->photonMultiplicity()); }
template<> void NamedPtrI<i_muonMultiplicity>::get_property(const pat::Jet* Jet)            { push_back(Jet->muonMultiplicity()); }
template<> void NamedPtrI<i_NumBhadrons>::get_property(const pat::Jet* Jet)                 { push_back(Jet->jetFlavourInfo().getbHadrons().size()); }
template<> void NamedPtrI<i_NumChadrons>::get_property(const pat::Jet* Jet)                 { push_back(Jet->jetFlavourInfo().getcHadrons().size()); }
template<> void NamedPtrI<i_chargedMultiplicity>::get_property(const pat::Jet* Jet)         { push_back(Jet->chargedMultiplicity()); }
template<> void NamedPtrI<i_neutralMultiplicity>::get_property(const pat::Jet* Jet)         { push_back(Jet->neutralMultiplicity()); }
template<> void NamedPtrI<i_partonFlavor>::get_property(const pat::Jet* Jet)                { push_back(Jet->partonFlavour()); }
template<> void NamedPtrI<i_hadronFlavor>::get_property(const pat::Jet* Jet)                { push_back(Jet->hadronFlavour()); }
template<> void NamedPtrI<i_qgMult>::get_property(const pat::Jet* Jet)                      { push_back(Jet->userInt("QGTagger:mult")); }

//
// class declaration
//

class JetProperties : public edm::EDProducer {
public:
	explicit JetProperties(const edm::ParameterSet&);
	~JetProperties();
	
	static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
	
private:
	virtual void beginJob() ;
	virtual void produce(edm::Event&, const edm::EventSetup&);
	virtual void endJob() ;
	
	virtual void beginRun(edm::Run&, edm::EventSetup const&);
	virtual void endRun(edm::Run&, edm::EventSetup const&);
	virtual void beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);
	virtual void endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);
	edm::InputTag JetTag_;
	edm::EDGetTokenT<edm::View<pat::Jet>> JetTok_;
	std::string   btagnameCSV_, btagnameMVA_;
	std::vector<NamedPtr<int>*> IntPtrs_;
	std::vector<NamedPtr<double>*> DoublePtrs_;
	NamedPtr<double> *DoublePtr_bDiscriminatorCSV_, *DoublePtr_bDiscriminatorMVA_;
	NamedPtr<double> *DoublePtr_bDiscriminatorSubjet1_, *DoublePtr_bDiscriminatorSubjet2_;
};

//
// constructors and destructor
//
JetProperties::JetProperties(const edm::ParameterSet& iConfig)
{
	JetTag_ = iConfig.getParameter<edm::InputTag>("JetTag");
	btagnameCSV_ = iConfig.getParameter<std::string>  ("BTagInputTagCSV");
	btagnameMVA_ = iConfig.getParameter<std::string>  ("BTagInputTagMVA");
	
	JetTok_ = consumes<edm::View<pat::Jet>>(JetTag_);

	//initialize special ones
	DoublePtr_bDiscriminatorSubjet1_ = NULL;
	DoublePtr_bDiscriminatorSubjet2_ = NULL;
	DoublePtr_bDiscriminatorCSV_ = NULL;
	DoublePtr_bDiscriminatorMVA_ = NULL;
	
	//get lists of desired properties
	std::vector<std::string> props = iConfig.getParameter<std::vector<std::string>> ("properties");
	
	//register your products
	for(auto& p : props){
		     if(p=="chargedHadronMultiplicity"  ) IntPtrs_.push_back(new NamedPtrI<i_chargedHadronMultiplicity>     ("chargedHadronMultiplicity",this)  );
		else if(p=="neutralHadronMultiplicity"  ) IntPtrs_.push_back(new NamedPtrI<i_neutralHadronMultiplicity>     ("neutralHadronMultiplicity",this)  );
		else if(p=="electronMultiplicity"       ) IntPtrs_.push_back(new NamedPtrI<i_electronMultiplicity>          ("electronMultiplicity",this)       );
		else if(p=="photonMultiplicity"         ) IntPtrs_.push_back(new NamedPtrI<i_photonMultiplicity>            ("photonMultiplicity",this)         );
		else if(p=="muonMultiplicity"           ) IntPtrs_.push_back(new NamedPtrI<i_muonMultiplicity>              ("muonMultiplicity",this)           );
		else if(p=="NumBhadrons"                ) IntPtrs_.push_back(new NamedPtrI<i_NumBhadrons>                   ("NumBhadrons",this)                );
		else if(p=="NumChadrons"                ) IntPtrs_.push_back(new NamedPtrI<i_NumChadrons>                   ("NumChadrons",this)                );
		else if(p=="chargedMultiplicity"        ) IntPtrs_.push_back(new NamedPtrI<i_chargedMultiplicity>           ("chargedMultiplicity",this)        );
		else if(p=="neutralMultiplicity"        ) IntPtrs_.push_back(new NamedPtrI<i_neutralMultiplicity>           ("neutralMultiplicity",this)        );
		else if(p=="partonFlavor"               ) IntPtrs_.push_back(new NamedPtrI<i_partonFlavor>                  ("partonFlavor",this)               );
		else if(p=="hadronFlavor"               ) IntPtrs_.push_back(new NamedPtrI<i_hadronFlavor>                  ("hadronFlavor",this)               );
		else if(p=="qgMult"                     ) IntPtrs_.push_back(new NamedPtrI<i_qgMult>                        ("qgMult",this)                     );
		else if(p=="jetArea"                    ) DoublePtrs_.push_back(new NamedPtrD<d_jetArea>                    ("jetArea",this)                    );
		else if(p=="chargedHadronEnergyFraction") DoublePtrs_.push_back(new NamedPtrD<d_chargedHadronEnergyFraction>("chargedHadronEnergyFraction",this));
		else if(p=="neutralHadronEnergyFraction") DoublePtrs_.push_back(new NamedPtrD<d_neutralHadronEnergyFraction>("neutralHadronEnergyFraction",this));
		else if(p=="chargedEmEnergyFraction"    ) DoublePtrs_.push_back(new NamedPtrD<d_chargedEmEnergyFraction>    ("chargedEmEnergyFraction",this)    );
		else if(p=="neutralEmEnergyFraction"    ) DoublePtrs_.push_back(new NamedPtrD<d_neutralEmEnergyFraction>    ("neutralEmEnergyFraction",this)    );
		else if(p=="electronEnergyFraction"     ) DoublePtrs_.push_back(new NamedPtrD<d_electronEnergyFraction>     ("electronEnergyFraction",this)     );
		else if(p=="photonEnergyFraction"       ) DoublePtrs_.push_back(new NamedPtrD<d_photonEnergyFraction>       ("photonEnergyFraction",this)       );
		else if(p=="muonEnergyFraction"         ) DoublePtrs_.push_back(new NamedPtrD<d_muonEnergyFraction>         ("muonEnergyFraction",this)         );
		else if(p=="qgLikelihood"               ) DoublePtrs_.push_back(new NamedPtrD<d_qgLikelihood>               ("qgLikelihood",this)               );
		else if(p=="qgPtD"                      ) DoublePtrs_.push_back(new NamedPtrD<d_qgPtD>                      ("qgPtD",this)                      );
		else if(p=="qgAxis2"                    ) DoublePtrs_.push_back(new NamedPtrD<d_qgAxis2>                    ("qgAxis2",this)                    );
		else if(p=="prunedMass"                 ) DoublePtrs_.push_back(new NamedPtrD<d_prunedMass>                 ("prunedMass",this)                 );
		else if(p=="NsubjettinessTau1"          ) DoublePtrs_.push_back(new NamedPtrD<d_NsubjettinessTau1>          ("NsubjettinessTau1",this)          );
		else if(p=="NsubjettinessTau2"          ) DoublePtrs_.push_back(new NamedPtrD<d_NsubjettinessTau2>          ("NsubjettinessTau2",this)          );
		else if(p=="NsubjettinessTau3"          ) DoublePtrs_.push_back(new NamedPtrD<d_NsubjettinessTau3>          ("NsubjettinessTau3",this)          );
		//special ones
		else if(p=="bDiscriminatorCSV"          ) DoublePtr_bDiscriminatorCSV_ = new NamedPtrD<d_bDiscriminatorCSV>("bDiscriminatorCSV",this);
		else if(p=="bDiscriminatorMVA"          ) DoublePtr_bDiscriminatorMVA_ = new NamedPtrD<d_bDiscriminatorMVA>("bDiscriminatorMVA",this);
		else if(p=="bDiscriminatorSubjet1"      ) DoublePtr_bDiscriminatorSubjet1_ = new NamedPtrD<d_bDiscriminatorSubjet1>("bDiscriminatorSubjet1",this);
		else if(p=="bDiscriminatorSubjet2"      ) DoublePtr_bDiscriminatorSubjet2_ = new NamedPtrD<d_bDiscriminatorSubjet2>("bDiscriminatorSubjet2",this);
		else std::cout << "JetsProperties: unknown property " << p << std::endl;
	}	
}


JetProperties::~JetProperties()
{
	
	// do anything here that needs to be done at desctruction time
	// (e.g. close files, deallocate resources etc.)
	
}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
JetProperties::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
	//reset ptrs
	for(unsigned ip = 0; ip < IntPtrs_.size(); ++ip){
		IntPtrs_[ip]->reset();
	}
	for(unsigned ip = 0; ip < DoublePtrs_.size(); ++ip){
		DoublePtrs_[ip]->reset();
	}
	if(DoublePtr_bDiscriminatorSubjet1_) DoublePtr_bDiscriminatorSubjet1_->reset();
	if(DoublePtr_bDiscriminatorSubjet2_) DoublePtr_bDiscriminatorSubjet2_->reset();
	if(DoublePtr_bDiscriminatorCSV_) DoublePtr_bDiscriminatorCSV_->reset();
	if(DoublePtr_bDiscriminatorMVA_) DoublePtr_bDiscriminatorMVA_->reset();

	edm::Handle< edm::View<pat::Jet> > Jets;
	iEvent.getByToken(JetTok_,Jets);
	if( Jets.isValid() ) {
		for(auto Jet = Jets->begin();  Jet != Jets->end(); ++Jet){
			for(unsigned ip = 0; ip < IntPtrs_.size(); ++ip){
				IntPtrs_[ip]->get_property(&(*Jet));
			}
			for(unsigned ip = 0; ip < DoublePtrs_.size(); ++ip){
				DoublePtrs_[ip]->get_property(&(*Jet));
			}
			//special attention for a few properties
			if(DoublePtr_bDiscriminatorSubjet1_) {
				//for debugging: print out available subjet collections
				//std::vector<std::string> labels = Jet->subjetCollectionNames();
				//std::copy(labels.begin(), labels.end(), std::ostream_iterator<std::string>(std::cout, " "));
				DoublePtr_bDiscriminatorSubjet1_->push_back( Jet->subjets("SoftDrop").size() > 0 ? Jet->subjets("SoftDrop").at(0)->bDiscriminator(btagnameCSV_) : -10. );
			}
			
			if(DoublePtr_bDiscriminatorSubjet2_) DoublePtr_bDiscriminatorSubjet2_->push_back( Jet->subjets("SoftDrop").size() > 1 ? Jet->subjets("SoftDrop").at(1)->bDiscriminator(btagnameCSV_) : -10. );
			
			if(DoublePtr_bDiscriminatorCSV_) DoublePtr_bDiscriminatorCSV_->push_back( Jet->bDiscriminator(btagnameCSV_) );
			
			if(DoublePtr_bDiscriminatorMVA_) DoublePtr_bDiscriminatorMVA_->push_back( Jet->bDiscriminator(btagnameMVA_) );			
		}
	}

	//put products
	for(unsigned ip = 0; ip < IntPtrs_.size(); ++ip){
		IntPtrs_[ip]->put(iEvent);
	}
	for(unsigned ip = 0; ip < DoublePtrs_.size(); ++ip){
		DoublePtrs_[ip]->put(iEvent);
	}
	if(DoublePtr_bDiscriminatorSubjet1_) DoublePtr_bDiscriminatorSubjet1_->put(iEvent);
	if(DoublePtr_bDiscriminatorSubjet2_) DoublePtr_bDiscriminatorSubjet2_->put(iEvent);
	if(DoublePtr_bDiscriminatorCSV_) DoublePtr_bDiscriminatorCSV_->put(iEvent);
	if(DoublePtr_bDiscriminatorMVA_) DoublePtr_bDiscriminatorMVA_->put(iEvent);

}

// ------------ method called once each job just before starting event loop  ------------
void 
JetProperties::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
JetProperties::endJob() {
	//memory management
	for(unsigned ip = 0; ip < IntPtrs_.size(); ++ip){
		delete (IntPtrs_[ip]);
	}
	IntPtrs_.clear();
	for(unsigned ip = 0; ip < DoublePtrs_.size(); ++ip){
		delete (DoublePtrs_[ip]);
	}
	DoublePtrs_.clear();
	delete DoublePtr_bDiscriminatorSubjet1_;
	delete DoublePtr_bDiscriminatorSubjet2_;
	delete DoublePtr_bDiscriminatorCSV_;
	delete DoublePtr_bDiscriminatorMVA_;
}

// ------------ method called when starting to processes a run  ------------
void 
JetProperties::beginRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
JetProperties::endRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
JetProperties::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
JetProperties::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
JetProperties::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
	//The following says we do not know what parameters are allowed so do no validation
	// Please change this to state exactly what you do use, even if it is no parameters
	edm::ParameterSetDescription desc;
	desc.setUnknown();
	descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(JetProperties);
