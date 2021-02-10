
// You have to load the class before ... ;-)
// .L DetectorK.cxx++

//void standardPlots() {

void testDetectorUpCyl(double mass = 0.14, TString outg = "outgr") {


  DetectorK its("ALICE","ITS");

  its.AddLayer((char*)"bpipe",1.6,0.0022); //0.0022);  800->500 \mu
  //its.AddLayer((char*)"bpipe",2.8,0.0015); //0.0022);  800->500 \mu
  its.AddLayer((char*)"vertex",     0,     0); // dummy vertex for matrix calculation
  // new ideal Pixel properties?

  Double_t x0 = 0.0050;
  Double_t x0IB     = 0.0005;
  Double_t x0OB     = 0.0035;
  Double_t resRPhi = 0.0006;    // Resolution in Rphi
  Double_t resZ = 0.0006;       // Resolution in Z
  Double_t eff           = 0.98;
  Double_t xrhoIB = 1.1646e-02; // Surface density for 50 mum thick Si
  Double_t xrhoOB = 1.1646e-01; // Surface density for 500 mum thick Si
  //
  //  /*
  its.AddLayer((char *)"ddd1", 1.8, x0, xrhoIB, resRPhi, resZ, eff);
  its.AddLayer((char *)"foam1", 1.8 + 9.370 * x0, 0.0008); // Foam spacer
  its.AddLayer((char *)"ddd2", 2.4, x0, xrhoIB, resRPhi, resZ, eff);
  its.AddLayer((char *)"foam2", 2.4 + 9.370 * x0, 0.0008); // Foam spacer
  its.AddLayer((char *)"ddd3", 3.0, x0, xrhoIB, resRPhi, resZ, eff);
  its.AddLayer((char *)"foam3", 3.0 + 9.370 * x0, 0.0008); // Foam spacer
  its.AddLayer((char *)"ddd4", 19.4, x0OB, xrhoOB, resRPhi, resZ, eff);
  its.AddLayer((char *)"ddd5", 24.7, x0OB, xrhoOB, resRPhi, resZ, eff);
  its.AddLayer((char *)"ddd6", 35.3, x0OB, xrhoOB, resRPhi, resZ, eff);
  its.AddLayer((char *)"ddd7", 40.5, x0OB, xrhoOB, resRPhi, resZ, eff);

  //  */
  //
  /*
  its.AddLayer((char*)"ddd1",  2.32 ,  x0IB, resRPhiIB, resZIB,eff); 
  its.AddLayer((char*)"ddd2",  3.13 ,  x0IB, resRPhiIB, resZIB,eff); 
  its.AddLayer((char*)"ddd3",  3.91 ,  x0IB, resRPhiIB, resZIB,eff); 
  its.AddLayer((char*)"ddd4",  19.41+5,  x0OB, resRPhiOB, resZOB,eff); 
  its.AddLayer((char*)"ddd5",  24.71+5,  x0OB, resRPhiOB, resZOB,eff); 
  //  its.AddLayer((char*)"ddd4",  5.,  x0OB, resRPhiOB, resZOB,eff); 
  //  its.AddLayer((char*)"ddd5",  32. ,  x0OB, resRPhiOB, resZOB,eff); 
  its.AddLayer((char*)"ddd6",  35.33 ,  x0OB, resRPhiOB, resZOB,eff); 
  its.AddLayer((char*)"ddd7",  40.53 ,  x0OB, resRPhiOB, resZOB,eff); 
  */
  its.SetParticleMass(mass);
  its.SetBField(0.5);
  its.SetAvgRapidity(0.5);
  its.SetAtLeastHits(4);
  its.SetAtLeastCorr(4);
  its.SetAtLeastFake(1);
  //
  its.PrintLayout();
  its.SolveViaBilloir(0);

  TString outITS = "";
  if (!outg.IsNull()) outITS = outg + "_ITS.root";
  its.MakeStandardPlots(0,2,1,outITS.Data());
  //  return;
  its.AddTPC(0.1,0.1);
  //  its.AddTRD(0.02,2.5);
  its.SolveViaBilloir(0);
 
  TString outGlo = "";
  if (!outg.IsNull()) outGlo = outg + "_GLO.root";
  its.MakeStandardPlots(1,1,1,outGlo.Data());
  //  its.PrintLayout(1);
}

void testDetectorCurr(TString outg = "outgr") {
  DetectorK its("ALICE","ITS");
  its.MakeAliceCurrent(0,0);
  its.SetAtLeastCorr(4);
  its.SetAtLeastFake(1);
  its.PrintLayout();
  its.SolveViaBilloir(0);

  
  TString outITS = "";
  if (!outg.IsNull()) outITS = outg + "_ITS.root";
  its.MakeStandardPlots(0,2,1,outITS.Data());
  //  return;
  its.AddTPC(0.1,0.1);
  its.SolveViaBilloir(0);
 
  TString outGlo = "";
  if (!outg.IsNull()) outGlo = outg + "_GLO.root";
  its.MakeStandardPlots(1,1,1,outGlo.Data());
  
}

void particleDependendResolution() { 
// particle dependency on resolution

  // .L Detector.cxx++

  Detector its("ALICE","ITS");

  its.MakeAliceCurrent(); 
  its.PrintLayout();
  its.PlotLayout();

  its.SolveViaBilloir(0);
 
  its.SetRadius("bpipe",2.1);
  its.AddLayer("spd0",2.2,0.001,0.0012,0.0012);

  TCanvas *c1 = new TCanvas("c1","c1");
 
  c1->Divide(2,1);
  c1->cd(1); gPad->SetGridx();   gPad->SetGridy(); 
  gPad->SetLogx(); //gPad->SetLogy();
  c1->cd(2); gPad->SetGridx();   gPad->SetGridy(); 
  gPad->SetLogx(); //gPad->SetLogy();

  
  // compare to telescope equation ?
  //  c1->cd(1); its.GetGraphPointingResolutionTeleEqu(0,1)->Draw("AC");
  //  c1->cd(2); its.GetGraphPointingResolutionTeleEqu(1,1)->Draw("AC");

  its.SetParticleMass(0.140); // pion  
  its.SolveViaBilloir(0,0);
  c1->cd(1); its.GetGraphPointingResolution(0,1)->Draw("AC");
  c1->cd(2); its.GetGraphPointingResolution(1,1)->Draw("AC");
 
  its.SetParticleMass(0.498); // kaon  
  its.SolveViaBilloir(0,0);
  c1->cd(1); its.GetGraphPointingResolution(0,2)->Draw("C");
  c1->cd(2); its.GetGraphPointingResolution(1,2)->Draw("C");

  its.SetParticleMass(0.00051); // electron  
  its.SolveViaBilloir(0,0);
  c1->cd(1); its.GetGraphPointingResolution(0,3)->Draw("C");
  c1->cd(2); its.GetGraphPointingResolution(1,3)->Draw("C");

  its.SetParticleMass(0.938); // proton  
  its.SolveViaBilloir(0,0);
  c1->cd(1); its.GetGraphPointingResolution(0,4)->Draw("C");
  c1->cd(2); its.GetGraphPointingResolution(1,4)->Draw("C");



}

