#include <Riostream.h>
#include <TFile.h>
#include "AliRDHFCutsD0toKpi.h"
#include <TClonesArray.h>
#include <TParameter.h>


//Use:
//Set hard coded commentet with //set this!!
// gSystem->SetIncludePath("-I. -I$ROOTSYS/include -I$ALICE_ROOT -I$ALICE_ROOT/include -I$ALICE_ROOT/ITS -I$ALICE_ROOT/TPC -I$ALICE_ROOT/CONTAINERS -I$ALICE_ROOT/STEER -I$ALICE_ROOT/TRD -I$ALICE_ROOT/macros -I$ALICE_ROOT/ANALYSIS -I$ALICE_ROOT/PWG3 -I$ALICE_ROOT/PWG3/vertexingHF -g");
//gSystem->SetIncludePath("-I. -I$ROOTSYS/include -I$ALICE_ROOT -I$ALICE_ROOT/include -I$ALICE_ROOT/ITS -I$ALICE_ROOT/TPC -I$ALICE_ROOT/CONTAINERS -I$ALICE_ROOT/STEER -I$ALICE_ROOT/TRD -I$ALICE_ROOT/macros -I$ALICE_ROOT/ANALYSIS -I$ALICE_PHYSICS/PWGHF -I$ALICE_PHYSICS/PWGHF/vertexingHF -g");

// root[] .L makeInputD0tasks.C++
// root[] makeInputAliAnalysisTaskSED0Mass()
// root[] makeInputAliAnalysisTaskSESignificanceMaximization()
//similar macros for the other D mesons

//Author: Chiara Bianchin, cbianchi@pd.infn.it


//macro to make a .root file which contains an AliRDHFCutsD0toKpi for AliAnalysisTaskSED0Mass task

void makeInputAliAnalysisTaskSED0Mass(Float_t minc=0., Float_t maxc=20.){

  AliRDHFCutsD0toKpi* RDHFD0toKpi=new AliRDHFCutsD0toKpi();
  RDHFD0toKpi->SetName("D0toKpiCuts");
  RDHFD0toKpi->SetTitle("Cuts for D0 analysis");

  AliESDtrackCuts* esdTrackCuts=new AliESDtrackCuts();
  esdTrackCuts->SetRequireSigmaToVertex(kFALSE);
  //default
  esdTrackCuts->SetRequireTPCRefit(kTRUE);
  esdTrackCuts->SetRequireITSRefit(kTRUE);
  esdTrackCuts->SetEtaRange(-0.8,0.8);
  //esdTrackCuts->SetMinNClustersITS(4); // default is 5
  //esdTrackCuts->SetMinNClustersTPC(90);
  esdTrackCuts->SetClusterRequirementITS(AliESDtrackCuts::kSPD,
					 AliESDtrackCuts::kAny); 
 // default is kBoth, otherwise kAny
  esdTrackCuts->SetMinDCAToVertexXY(0.);
  esdTrackCuts->SetPtRange(0.5,1.e10);
  esdTrackCuts->SetMaxDCAToVertexXY(1.);
  esdTrackCuts->SetMaxDCAToVertexZ(1.);
  //esdTrackCuts->SetMinDCAToVertexXYPtDep("0.005*TMath::Max(0.,(1-TMath::Floor(TMath::Abs(pt)/2.)))");
 
  //esdTrackCuts->SetMinNCrossedRowsTPC(80);
  //esdTrackCuts->SetMinRatioCrossedRowsOverFindableClustersTPC(0.9);
  //esdTrackCuts->SetTPCNclsF(80);

  RDHFD0toKpi->AddTrackCuts(esdTrackCuts);
  //RDHFD0toKpi->SetSelectCandTrackSPDFirst(kTRUE, 5);

  RDHFD0toKpi->SetTriggerClass("");
  RDHFD0toKpi->SetTriggerMask(AliVEvent::kINT7);
  //RDHFD0toKpi->ResetMaskAndEnableSemiCentralTrigger();
  //RDHFD0toKpi->EnableCentralTrigger();
  //RDHFD0toKpi->EnableMBTrigger();
  //RDHFD0toKpi->ResetMaskAndEnableMBTrigger();
  //RDHFD0toKpi->SetTriggerClass("CINT7");
  

  const Int_t nvars=11;

  const Int_t nptbins=19;
  Float_t* ptbins;
  ptbins=new Float_t[nptbins+1];
  ptbins[0]=0.;
  ptbins[1]=1.;
  ptbins[2]=2.;
  ptbins[3]=3.;
  ptbins[4]=4.;
  ptbins[5]=5;
  ptbins[6]=6.;
  ptbins[7]=7.;
  ptbins[8]=8.;
  ptbins[9]=9.;
  ptbins[10]=10.;
  ptbins[11]=12.;
  ptbins[12]=14.;
  ptbins[13]=16.;
  ptbins[14]=18.;
  ptbins[15]=20.;
  ptbins[16]=24.;
  ptbins[17]=36.;
  ptbins[18]=50.;
  ptbins[19]=9999.;

  RDHFD0toKpi->SetPtBins(nptbins+1,ptbins);
  
  //setting my cut values
    //cuts order
    //       printf("    |M-MD0| [GeV]    < %f\n",fD0toKpiCuts[0]);
    //     printf("    dca    [cm]  < %f\n",fD0toKpiCuts[1]);
    //     printf("    cosThetaStar     < %f\n",fD0toKpiCuts[2]);
    //     printf("    pTK     [GeV/c]    > %f\n",fD0toKpiCuts[3]);
    //     printf("    pTpi    [GeV/c]    > %f\n",fD0toKpiCuts[4]);
    //     printf("    |d0K|  [cm]  < %f\n",fD0toKpiCuts[5]);
    //     printf("    |d0pi| [cm]  < %f\n",fD0toKpiCuts[6]);
    //     printf("    d0d0  [cm^2] < %f\n",fD0toKpiCuts[7]);
    //     printf("    cosThetaPoint    > %f\n",fD0toKpiCuts[8]);
    //     printf("    |cosThetaPointXY| < %f\n",fD0toKpiCuts[9]);
    //     printf("    NormDecayLenghtXY    > %f\n",fD0toKpiCuts[10]);

   

	    Float_t cutsMatrixD0toKpiStand[nptbins][nvars] = {
			{ 0.400, 400.*1E-4, 0.8, 0.4, 0.4, 0.1, 0.1, -480.*1E-6, 0.95, 0.996, 8 }, /* 0<pt<1*/
			{ 0.400, 400.*1E-4, 0.8, 0.4, 0.4, 0.1, 0.1, -480.*1E-6, 0.95, 0.996, 8 }, /* 1<pt<2*/
			{ 0.400, 250.*1E-4, 0.8, 0.7, 0.7, 0.1, 0.1, -460.*1E-6, 0.95, 0.998, 7 }, /* 2<pt<3*/
			{ 0.400, 250.*1E-4, 0.8, 0.7, 0.7, 0.1, 0.1, -360.*1E-6, 0.95, 0.998, 6 }, /* 3<pt<4*/
			{ 0.400, 250.*1E-4, 0.8, 0.7, 0.7, 0.1, 0.1, -280.*1E-6, 0.95, 0.998, 6 }, /* 4<pt<5*/
			{ 0.400, 250.*1E-4, 0.8, 0.7, 0.7, 0.1, 0.1, -220.*1E-6, 0.92, 0.998, 6 }, /* 5<pt<6*/
			{ 0.400, 300.*1E-4, 0.8, 0.7, 0.7, 0.1, 0.1, -150.*1E-6, 0.88, 0.998, 6 }, /* 6<pt<7*/
			{ 0.400, 300.*1E-4, 0.8, 0.7, 0.7, 0.1, 0.1, -150.*1E-6, 0.88, 0.998, 6 }, /* 7<pt<8*/
			{ 0.400, 350.*1E-4, 1.0, 0.7, 0.7, 0.1, 0.1, -100.0*1E-6, 0.85, 0.998, 6 }, /* 8<pt<9*/
			{ 0.400, 350.*1E-4, 1.0, 0.7, 0.7, 0.1, 0.1, -100.0*1E-6, 0.85, 0.998, 6 }, /* 9<pt<10*/
			{ 0.400, 350.*1E-4, 1.0, 0.7, 0.7, 0.1, 0.1, -100.0*1E-6, 0.85, 0.998, 6 }, /* 10<pt<12*/
			{ 0.400, 400.*1E-4, 1.0, 0.7, 0.7, 0.1, 0.1, -100.00*1E-6, 0.83, 0.998, 6 }, /* 12<pt<14*/
			{ 0.400, 400.*1E-4, 1.0, 0.7, 0.7, 0.1, 0.1, -100.00*1E-6, 0.83, 0.998, 6 }, /* 14<pt<16*/
			{ 0.400, 400.*1E-4, 1.0, 0.7, 0.7, 0.1, 0.1, -50.00*1E-6, 0.82, 0.998, 6 }, /* 16<pt<18*/
			{ 0.400, 400.*1E-4, 1.0, 0.7, 0.7, 0.1, 0.1, -50.00*1E-6, 0.82, 0.998, 6 }, /* 18<pt<20*/
			{ 0.400, 400.*1E-4, 1.0, 0.7, 0.7, 0.1, 0.1, -50.00*1E-6, 0.82, 0.998, 6 }, /* 20<pt<24*/
			{ 0.400, 400.*1E-4, 1.0, 0.7, 0.7, 0.1, 0.1,  0.00*1E-6, 0.8, 0.995, 5 }, /* 24<pt<36*/
			{ 0.400, 400.*1E-4, 1.0, 0.7, 0.7, 0.1, 0.1,  0.00*1E-6, 0.8, 0.995, 5 }, /* 36<pt<50*/	
			{ 0.400, 400.*1E-4, 1.0, 0.7, 0.7, 0.1, 0.1,  0.00*1E-6, 0.8, 0.995, 5 } /* pt>50*/	
			
		};
		
		
		Float_t cutsMatrixD0toKpiAntonio[nptbins][nvars] = {
			{ 0.400, 400.*1E-4, 0.8, 0.4, 0.4, 0.1, 0.1, -480.*1E-6, 0.85, 0.996, 8 }, /* 0<pt<1*/
			{ 0.400, 400.*1E-4, 0.8, 0.4, 0.4, 0.1, 0.1, -480.*1E-6, 0.85, 0.996, 8 }, /* 1<pt<2*/
			{ 0.400, 250.*1E-4, 0.8, 0.7, 0.7, 0.1, 0.1, -460.*1E-6, 0.95, 0.998, 7 }, /* 2<pt<3*/
			{ 0.400, 250.*1E-4, 0.8, 0.7, 0.7, 0.1, 0.1, -370.*1E-6, 0.95, 0.998, 5 }, /* 3<pt<4*/
			{ 0.400, 250.*1E-4, 0.8, 0.7, 0.7, 0.1, 0.1, -280.*1E-6, 0.95, 0.998, 5 }, /* 4<pt<5*/
			{ 0.400, 250.*1E-4, 0.8, 0.7, 0.7, 0.1, 0.1, -220.*1E-6, 0.92, 0.999, 5 }, /* 5<pt<6*/
			{ 0.400, 300.*1E-4, 0.8, 0.7, 0.7, 0.1, 0.1, -150.*1E-6, 0.88, 0.999, 5 }, /* 6<pt<7*/
			{ 0.400, 300.*1E-4, 0.8, 0.7, 0.7, 0.1, 0.1, -150.*1E-6, 0.88, 0.999, 5 }, /* 7<pt<8*/
			{ 0.400, 350.*1E-4, 1.0, 0.7, 0.7, 0.1, 0.1, -60.0*1E-6, 0.85, 0.999, 5 }, /* 8<pt<9*/
			{ 0.400, 350.*1E-4, 1.0, 0.7, 0.7, 0.1, 0.1, -60.0*1E-6, 0.85, 0.999, 5 }, /* 9<pt<10*/
			{ 0.400, 350.*1E-4, 1.0, 0.7, 0.7, 0.1, 0.1, -60.0*1E-6, 0.85, 0.999, 5 }, /* 10<pt<12*/
			{ 0.400, 400.*1E-4, 1.0, 0.7, 0.7, 0.1, 0.1, -3.00*1E-6, 0.83, 0.999, 8 }, /* 12<pt<14*/
			{ 0.400, 400.*1E-4, 1.0, 0.7, 0.7, 0.1, 0.1, -3.00*1E-6, 0.83, 0.999, 8 }, /* 14<pt<16*/
			{ 0.400, 400.*1E-4, 1.0, 0.7, 0.7, 0.1, 0.1, -3.00*1E-6, 0.82, 0.999, 6 }, /* 16<pt<18*/
			{ 0.400, 400.*1E-4, 1.0, 0.7, 0.7, 0.1, 0.1, -3.00*1E-6, 0.82, 0.999, 6 }, /* 18<pt<20*/
			{ 0.400, 400.*1E-4, 1.0, 0.7, 0.7, 0.1, 0.1, -3.00*1E-6, 0.82, 0.999, 6 }, /* 20<pt<24*/
			{ 0.400, 400.*1E-4, 1.0, 0.7, 0.7, 0.1, 0.1, -3.00*1E-6, 0.82, 0.999, 6 }, /* 24<pt<36*/
			{ 0.400, 400.*1E-4, 1.0, 0.7, 0.7, 0.1, 0.1, -3.00*1E-6, 0.82, 0.999, 6 }, /* 36<pt<50*/	
			{ 0.400, 400.*1E-4, 1.0, 0.7, 0.7, 0.1, 0.1, -3.00*1E-6, 0.82, 0.999, 6 } /* pt>50*/	
			
		};
						    

    Float_t d0MeasMinusExpCut[nptbins]={
			2, /* 0<pt<1*/
			2, /* 1<pt<2*/
			2, /* 2<pt<3*/
			2, /* 3<pt<4*/
			2, /* 4<pt<5*/
			2, /* 5<pt<6*/
			2, /* 6<pt<7*/
			2, /* 7<pt<8*/
			2, /* 8<pt<9*/
			2, /* 9<pt<10*/
			2, /* 10<pt<12*/
			2, /* 12<pt<14*/
			2, /* 14<pt<16*/
			2, /* 16<pt<18*/
			2, /* 18<pt<20*/
			2, /* 20<pt<24*/
			2, /* 24<pt<36*/
			2, /* 36<pt<50*/	
			2 /* pt>50*/	
		};
    

	
	Float_t **cutsMatrixTransposeStand=new Float_t*[nvars];
	for(Int_t iv=0;iv<nvars;iv++)cutsMatrixTransposeStand[iv]=new Float_t[nptbins];
	
	for (Int_t ibin=0;ibin<nptbins;ibin++){
		for (Int_t ivar = 0; ivar<nvars; ivar++){
			cutsMatrixTransposeStand[ivar][ibin]=cutsMatrixD0toKpiStand[ibin][ivar];
		}
	}
	
 
  RDHFD0toKpi->SetCuts(nvars,nptbins,cutsMatrixTransposeStand);
  RDHFD0toKpi->Setd0MeasMinusExpCut(nptbins,d0MeasMinusExpCut);

  Bool_t pidflag=kTRUE;
  RDHFD0toKpi->SetUsePID(pidflag);
  if(pidflag) cout<<"PID is used"<<endl;
  else cout<<"PID is not used"<<endl;

    //pid settings
  AliAODPidHF* pidObj=new AliAODPidHF();
  //pidObj->SetName("pid4D0");
  Int_t mode=1;
  const Int_t nlims=2;
  Double_t plims[nlims]={0.6,0.8}; //TPC limits in momentum [GeV/c]
  Bool_t compat=kTRUE; //effective only for this mode
  Bool_t asym=kTRUE;
  Double_t sigmas[5]={2.,1.,0.,3.,0.}; //to be checked and to be modified with new implementation of setters by Rossella
  pidObj->SetAsym(asym);// if you want to use the asymmetric bands in TPC
  pidObj->SetMatch(mode);
  pidObj->SetPLimit(plims,nlims);
  pidObj->SetSigma(sigmas);
  pidObj->SetCompat(compat);
  pidObj->SetTPC(kTRUE);
  pidObj->SetTOF(kTRUE);

  pidObj->SetPCompatTOF(2.);
  pidObj->SetSigmaForTPCCompat(3.);
  pidObj->SetSigmaForTOFCompat(3.);

  pidObj->SetOldPid(kFALSE);
	
  RDHFD0toKpi->SetLowPt(kFALSE);
  RDHFD0toKpi->SetUseDefaultPID(kFALSE); //to use the AliAODPidHF
	
  //RDHFD0toKpi->SetMaximumPforPID(4.);
  RDHFD0toKpi->SetPidHF(pidObj);
	
  //activate pileup rejection (for pp)
  RDHFD0toKpi->SetOptPileup(AliRDHFCuts::kNoPileupSelection);
		
  RDHFD0toKpi->SetUseSpecialCuts(kFALSE);
  //Do not recalculate the vertex
  RDHFD0toKpi->SetRemoveDaughtersFromPrim(kFALSE); //activate for pp
	
  //RDHFD0toKpi->SetUseAOD049(kTRUE);
  RDHFD0toKpi->SetMaxVtxZ(10.);

  //RDHFD0toKpi->SetRemoveTrackletOutliers(kTRUE);
  RDHFD0toKpi->SetCutOnzVertexSPD(2);

  TString cent="";
  //centrality selection (Pb-Pb)
  
  RDHFD0toKpi->SetMinCentrality(minc);
  RDHFD0toKpi->SetMaxCentrality(maxc);
  cent=Form("%.0f%.0f",minc,maxc);
  RDHFD0toKpi->SetUseCentrality(AliRDHFCuts::kCentV0M); //kCentOff,kCentV0M,kCentTRK,kCentTKL,kCentCL1,kCentInvalid

//  RDHFD0toKpi->SetMaxDifferenceTRKV0Centraltity(5.);

  //temporary
  //RDHFD0toKpi->SetFixRefs();
	
  //RDHFD0toKpi->SetSelectCandTrackSPDFirst(kTRUE, 3.);

  cout<<"This is the odject I'm going to save:"<<endl;
  RDHFD0toKpi->PrintAll();
  TFile* fout=new TFile("D0toKpiCuts_PbPb2015_0_20_Djet_setB.root","recreate");   //set this!!

  fout->cd();
  RDHFD0toKpi->Write();
  fout->Close();

}
 
//macro to make a .root file (for significance maximization) which contains an AliRDHFCutsD0toKpi with loose set of cuts  and TParameter with the tighest value of these cuts

void makeInputAliAnalysisTaskSESignificanceMaximization(){

  AliRDHFCutsD0toKpi* RDHFD0toKpi=new AliRDHFCutsD0toKpi();
  RDHFD0toKpi->SetName("loosercuts");
  RDHFD0toKpi->SetTitle("Cuts for significance maximization");

  AliESDtrackCuts* esdTrackCuts=new AliESDtrackCuts();
  esdTrackCuts->SetRequireSigmaToVertex(kFALSE);
  //default
  esdTrackCuts->SetRequireTPCRefit(kTRUE);
  esdTrackCuts->SetRequireITSRefit(kTRUE);
  //esdTrackCuts->SetMinNClustersITS(4);
  //esdTrackCuts->SetMinNClustersTPC(120);

  esdTrackCuts->SetClusterRequirementITS(AliESDtrackCuts::kSPD,AliESDtrackCuts::kAny);
  esdTrackCuts->SetMinDCAToVertexXY(0.);
  esdTrackCuts->SetEtaRange(-0.8,0.8);
  esdTrackCuts->SetPtRange(0.8,1.e10);
  
  RDHFD0toKpi->AddTrackCuts(esdTrackCuts);

  const Int_t nvars=11;

  const Int_t nptbins=14; //change this when adding pt bins!
  Float_t ptbins[nptbins+1];
  ptbins[0]=0.;
  ptbins[1]=0.5;
  ptbins[2]=1.;
  ptbins[3]=2.;
  ptbins[4]=3.;
  ptbins[5]=4.;
  ptbins[6]=5.;
  ptbins[7]=6.;
  ptbins[8]=8.;
  ptbins[9]=10.;
  ptbins[10]=12.;
  ptbins[11]=16.;
  ptbins[12]=20.;
  ptbins[13]=24.;
  ptbins[14]=9999.;

  RDHFD0toKpi->SetPtBins(nptbins+1,ptbins);

  Float_t** rdcutsvalmine;
  rdcutsvalmine=new Float_t*[nvars];
  for(Int_t iv=0;iv<nvars;iv++){
    rdcutsvalmine[iv]=new Float_t[nptbins];
  }

  //setting my cut values
    //cuts order
    //       printf("    |M-MD0| [GeV]    < %f\n",fD0toKpiCuts[0]);
    //     printf("    dca    [cm]  < %f\n",fD0toKpiCuts[1]);
    //     printf("    cosThetaStar     < %f\n",fD0toKpiCuts[2]);
    //     printf("    pTK     [GeV/c]    > %f\n",fD0toKpiCuts[3]);
    //     printf("    pTpi    [GeV/c]    > %f\n",fD0toKpiCuts[4]);
    //     printf("    |d0K|  [cm]  < %f\n",fD0toKpiCuts[5]);
    //     printf("    |d0pi| [cm]  < %f\n",fD0toKpiCuts[6]);
    //     printf("    d0d0  [cm^2] < %f\n",fD0toKpiCuts[7]);
    //     printf("    cosThetaPoint    > %f\n",fD0toKpiCuts[8]);
    //     printf("    |cosThetaPointXY| < %f\n",fD0toKpiCuts[9]);
    //     printf("    NormDecayLenghtXY    > %f\n",fD0toKpiCuts[10]);


    Float_t cutsMatrixD0toKpiStand[nptbins][nvars]={{0.400,400.*1E-4,0.8,0.3,0.3,1000.*1E-4,1000.*1E-4,-40000.*1E-8,0.75,0.,2.},/* pt<0.5*/
						  {0.400,400.*1E-4,0.8,0.3,0.3,1000.*1E-4,1000.*1E-4,-40000.*1E-8,0.75,0.,2.},/* 0.5<pt<1*/
						  {0.400,400.*1E-4,0.8,0.4,0.4,1000.*1E-4,1000.*1E-4,-33000.*1E-8,0.75,0.,2.},/* 1<pt<2 */
						  {0.400,250.*1E-4,0.8,0.7,0.7,1000.*1E-4,1000.*1E-4,-30000.*1E-8,0.85,0.994,2.},/* 2<pt<3 */
						  {0.400,250.*1E-4,0.8,0.7,0.7,1000.*1E-4,1000.*1E-4,-26000.*1E-8,0.85,0.994,2.},/* 3<pt<4 */
						  {0.400,250.*1E-4,0.8,0.7,0.7,1000.*1E-4,1000.*1E-4,-15000.*1E-8,0.85,0.994,2.},/* 4<pt<5 */
						  {0.400,250.*1E-4,0.8,0.7,0.7,1000.*1E-4,1000.*1E-4,-11000.*1E-8,0.82,0.994,2.},/* 5<pt<6 */
						  {0.400,270.*1E-4,0.8,0.7,0.7,1000.*1E-4,1000.*1E-4,-10000.*1E-8,0.78,0.994,2.},/* 6<pt<8 */
						  {0.400,300.*1E-4,0.8,0.7,0.7,1000.*1E-4,1000.*1E-4,-1000.*1E-8,0.7,0.994,2.},/* 8<pt<10 */
						  {0.400,300.*1E-4,0.8,0.7,0.7,1000.*1E-4,1000.*1E-4,-1000.*1E-8,0.7,0.994,2.},/* 10<pt<12 */
						  {0.400,350.*1E-4,1.0,0.7,0.7,1000.*1E-4,1000.*1E-4,-500.*1E-8,0.7,0.994,2.},/* 12<pt<16 */
						  {0.400,400.*1E-4,1.0,0.7,0.7,1000.*1E-4,1000.*1E-4,-500.*1E-8,0.7,0.994,2.},/* 16<pt<20 */
						  {0.400,400.*1E-4,1.0,0.7,0.7,1000.*1E-4,1000.*1E-4,-500.*1E-8,0.7,0.994,2.},/* 20<pt<24 */
						  {0.400,400.*1E-4,1.0,0.7,0.7,1000.*1E-4,1000.*1E-4,-500.*1E-8,0.7,0.994,2.}};/* pt>24 */

  //CREATE TRANSPOSE MATRIX...REVERSE INDICES as required by AliRDHFCuts
  Float_t **cutsMatrixTransposeStand=new Float_t*[nvars];
  for(Int_t iv=0;iv<nvars;iv++)cutsMatrixTransposeStand[iv]=new Float_t[nptbins];
  for (Int_t ibin=0;ibin<nptbins;ibin++){
    for (Int_t ivar = 0; ivar<nvars; ivar++){
      cutsMatrixTransposeStand[ivar][ibin]=cutsMatrixD0toKpiStand[ibin][ivar];
    }
  }
  RDHFD0toKpi->SetCuts(nvars,nptbins,cutsMatrixTransposeStand);


  Bool_t stdvaropt=kFALSE;
  Int_t dim=4; //set this!!
  Bool_t *boolforopt;
  boolforopt=new Bool_t[nvars];
  if(stdvaropt){
    boolforopt=RDHFD0toKpi->GetVarsForOpt();
  }else{
    TString *names;
    names=new TString[nvars];
    TString answer="";
    Int_t checktrue=0;
    names=RDHFD0toKpi->GetVarNames();
    for(Int_t i=0;i<nvars;i++){
      cout<<names[i]<<" for opt? (y/n)"<<endl;
      cin>>answer;
      if(answer=="y") {
	boolforopt[i]=kTRUE;
	checktrue++;
      }
      else boolforopt[i]=kFALSE;
    }
    if (checktrue!=dim) {
      cout<<"Error! You set "<<checktrue<<" kTRUE instead of "<<dim<<endl;
      return;
    }
    RDHFD0toKpi->SetVarsForOpt(dim,boolforopt);
  }


  Float_t tighterval[dim][nptbins];
  //dca  
  //costhetastar
  //d0d0 <-this 
  //costhetapoint <-this 
  //cosThetaPointXY <-this 
  //NormDecayLength <-this 
  
  //number of steps for each variable is set in the AddTask arguments (default=8)
  //set this!!
  //0-0.5
  tighterval[0][0]=-0.00065;
  tighterval[1][0]=1.;
  tighterval[2][0]=0.4;
  tighterval[3][0]=6.;

  //0.5-1.
  tighterval[0][1]=-0.00065;
  tighterval[1][1]=1.;
  tighterval[2][1]=0.4;
  tighterval[3][1]=6.;

  //1-2
  tighterval[0][2]=-0.00065;
  tighterval[1][2]=1.;
  tighterval[2][2]=0.4;
  tighterval[3][2]=6.;
 
  //2-3
  tighterval[0][3]=-0.0006;
  tighterval[1][3]=1.;
  tighterval[2][3]=1.;
  tighterval[3][3]=6.;

  //3-4
  tighterval[0][4]=-0.00046;
  tighterval[1][4]=1.;
  tighterval[2][4]=1.;
  tighterval[3][4]=6.;
 
  //4-5
  tighterval[0][5]=-0.00045;
  tighterval[1][5]=1.;
  tighterval[2][5]=1.;
  tighterval[3][5]=6.;
 
  //5-6
  tighterval[0][6]=-0.00031;
  tighterval[1][6]=1.;
  tighterval[2][6]=1.;
  tighterval[3][6]=6.;

  //6-8
  tighterval[0][7]=-0.00021;
  tighterval[1][7]=0.98;
  tighterval[2][7]=1.;
  tighterval[3][7]=6.;

  //8-10
  tighterval[0][8]=-0.0001;
  tighterval[1][8]=0.98;
  tighterval[2][8]=1.;
  tighterval[3][8]=6.;

  //10-12
  tighterval[0][9]=-0.0001;
  tighterval[1][9]=0.9;
  tighterval[2][9]=1.;
  tighterval[3][9]=6.;
 
  //12-16
  tighterval[0][10]=-0.00005;
  tighterval[1][10]=0.9;
  tighterval[2][10]=1.;
  tighterval[3][10]=6.;

  //16-20
  tighterval[0][11]=-0.00005;
  tighterval[1][11]=0.9;
  tighterval[2][11]=1.;
  tighterval[3][11]=6.;

  //20-24
  tighterval[0][12]=-0.00005;
  tighterval[1][12]=0.9;
  tighterval[2][12]=1.;
  tighterval[3][12]=6.;

  //>24
  tighterval[0][13]=-0.00005;
  tighterval[1][13]=0.9;
  tighterval[2][13]=1.;
  tighterval[3][13]=6.;


  TString name=""; 
  Int_t arrdim=dim*nptbins;
  cout<<"Will save "<<arrdim<<" TParameter<float>"<<endl;
  TClonesArray max("TParameter<float>",arrdim);
  for(Int_t ival=0;ival<dim;ival++){
    for(Int_t jpt=0;jpt<nptbins;jpt++){
      name=Form("par%dptbin%d",ival,jpt);
      cout<<"Setting "<<name.Data()<<" to "<<tighterval[ival][jpt]<<endl;
      new(max[jpt*dim+ival])TParameter<float>(name.Data(),tighterval[ival][jpt]);
    }
  }

  Bool_t flagPID=kTRUE;
  RDHFD0toKpi->SetUsePID(flagPID);

  RDHFD0toKpi->PrintAll();
  printf("Use PID? %s\n",flagPID ? "yes" : "no");

  //pid settings
  AliAODPidHF* pidObj=new AliAODPidHF();
  //pidObj->SetName("pid4D0");
  Int_t mode=1;
  const Int_t nlims=2;
  Double_t plims[nlims]={0.6,0.8}; //TPC limits in momentum [GeV/c]
  Bool_t compat=kTRUE; //effective only for this mode
  Bool_t asym=kTRUE;
  Double_t sigmas[5]={2.,1.,0.,3.,0.}; //to be checked and to be modified with new implementation of setters by Rossella
  pidObj->SetAsym(asym);// if you want to use the asymmetric bands in TPC
  pidObj->SetMatch(mode);
  pidObj->SetPLimit(plims,nlims);
  pidObj->SetSigma(sigmas);
  pidObj->SetCompat(compat);
  pidObj->SetTPC(kTRUE);
  pidObj->SetTOF(kTRUE);
  RDHFD0toKpi->SetPidHF(pidObj);

  RDHFD0toKpi->SetUseDefaultPID(kFALSE); //to use the AliAODPidHF
  
  //activate pileup rejection (for pp)
  //RDHFD0toKpi->SetOptPileup(AliRDHFCuts::kRejectPileupEvent);

  //Do not recalculate the vertex
  RDHFD0toKpi->SetRemoveDaughtersFromPrim(kFALSE); //activate for pp

  TString cent="";
  //centrality selection (Pb-Pb)
  Float_t minc=20,maxc=80;
  RDHFD0toKpi->SetMinCentrality(minc);
  RDHFD0toKpi->SetMaxCentrality(maxc);
  cent=Form("%.0f%.0f",minc,maxc);
  RDHFD0toKpi->SetUseCentrality(AliRDHFCuts::kCentV0M); //kCentOff,kCentV0M,kCentTRK,kCentTKL,kCentCL1,kCentInvalid

  //temporary
  RDHFD0toKpi->SetFixRefs();

  TFile* fout=new TFile(Form("centralSignifMaxim%s%s%sRecVtx%sPileupRej.root", RDHFD0toKpi->GetUseCentrality()==0 ? "pp" : "PbPb",cent.Data(),RDHFD0toKpi->GetIsPrimaryWithoutDaughters() ? "" : "No",RDHFD0toKpi->GetOptPileUp() ? "" : "No"),"recreate");   //set this!!

  fout->cd();
  RDHFD0toKpi->Write();
  max.Write();
  fout->Close();
 
}

