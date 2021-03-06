import FWCore.ParameterSet.Config as cms

triggerNameList = cms.vstring(
    # handle duplicates
	list(sorted(set([
    'HLT_PFMET90_PFMHT90_IDTight_v',
    'HLT_PFMET100_PFMHT100_IDTight_v',
    'HLT_PFMET110_PFMHT110_IDTight_v',
    'HLT_PFMET120_PFMHT120_IDTight_v',
    'HLT_Ele25_eta2p1_WPTight_Gsf_v ',
    'HLT_Ele27_WPTight_Gsf_v',
    'HLT_Ele27_eta2p1_WPLoose_Gsf_v ',
    'HLT_Ele45_WPLoose_Gsf_v',
    'HLT_Ele105_CaloIdVT_GsfTrkIdT_v',
    'HLT_Ele15_IsoVVVL_PFHT350_PFMET50_v',
    'HLT_Ele15_IsoVVVL_PFHT600_v',
    'HLT_Ele15_IsoVVVL_PFHT350_v',
    'HLT_IsoMu24_v ',
    'HLT_IsoMu22_eta2p1_v',
    'HLT_Mu50_v',
    'HLT_Mu15_IsoVVVL_PFHT350_PFMET50_v',
    'HLT_Mu15_IsoVVVL_PFHT600_v',
    'HLT_Mu15_IsoVVVL_PFHT350_v',
    'HLT_Photon90_CaloIdL_PFHT500_v',
    'HLT_Photon90_CaloIdL_PFHT600_v',
    'HLT_Photon135_PFMET100_v',
    'HLT_Photon165_HE10_v',
    'HLT_Photon175_v',
    'HLT_PFHT300_PFMET100_v',
    'HLT_PFHT300_PFMET110_v',
    'HLT_PFHT800_v',
    'HLT_PFHT900_v',
    'HLT_DoubleMu8_Mass8_PFHT300_v',
    'HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300_v',
    'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v',
    'HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v',
    'HLT_Mu15_IsoVVVL_PFHT400_v',
    'HLT_TkMu50_v',
    'HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v',
    'HLT_Ele15_IsoVVVL_PFHT400_v',
    'HLT_IsoMu22_v',
    'HLT_IsoTkMu22_v',
    'HLT_Mu50_IsoVVVL_PFHT400_v',
    'HLT_Ele50_IsoVVVL_PFHT400_v',
    'HLT_PFMETNoMu90_PFMHTNoMu90_IDTight_v',
    'HLT_PFMETNoMu100_PFMHTNoMu100_IDTight_v',
    'HLT_PFMETNoMu110_PFMHTNoMu110_IDTight_v',
    'HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_v',
    'HLT_PFHT200_v',
    'HLT_PFHT250_v',
    'HLT_PFHT300_v',
    'HLT_PFHT350_v',
    'HLT_PFHT400_v',
    'HLT_PFHT475_v',
    'HLT_PFHT600_v',
    'HLT_PFHT650_v',
    'HLT_IsoMu16_eta2p1_MET30_v',
    'HLT_Mu45_eta2p1_v',
    'HLT_CaloJet500_NoJetID_v',
    'HLT_Ele115_CaloIdVT_GsfTrkIdT_v',
    'HLT_IsoTkMu24_v',
    'HLT_PFHT450_SixJet40_BTagCSV_p056',
    'HLT_PFHT400_SixJet30_DoubleBTagCSV_p056',
    'HLT_AK8DiPFJet250_200_TrimMass30_v',
    'HLT_AK8DiPFJet280_200_TrimMass30_v',
    'HLT_AK8DiPFJet300_200_TrimMass30_v',
    'HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_v',
    'HLT_AK8PFJet360_TrimMass30_v',
    'HLT_AK8PFJet450_v',
    'HLT_DiCentralPFJet55_PFMET110_v',
    'HLT_DiPFJet40_DEta3p5_MJJ600_PFMETNoMu140_v',
    'HLT_PFHT650_WideJetMJJ900DEtaJJ1p5_v',
    ])))
)
