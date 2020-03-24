void GenerateGraph(TGraphErrors * g1,
                   Bool_t b_terror = false,
                   Bool_t b_herror = false){
    Int_t i;

    Int_t npoint = 10;
    Float_t hmax = 1.0;
    Float_t hmin = 0.;
    Float_t step = (hmax-hmin)/npoint;

    Float_t g    = 9.80665;

    Float_t t0   = 0.;
    Float_t h0   = 0.01;

    Float_t tnoise = 0.0001;
    Float_t hnoise = 0.01;

    Float_t tt   = 0.;
    Float_t ht   = 0.;
    Float_t h_real   = 0.;

    TRandom3 * r1 = new TRandom3();
    UInt_t seed = TUUID().GetTime().Get();
    r1->SetSeed(seed);

    // cout<<"Seed: "<<seed<<endl;

    for(i=0; i<npoint-1; i++){
      if(b_herror || i==0){
        h_real = h_real + step + r1->Uniform(-hnoise, hnoise);
      }else{
        h_real = h_real + step;
      }
      ht = step*(i+1);

      if(b_terror){
        tt = sqrt(2.*(h_real+h0)/g)-t0-(r1->Uniform(-tnoise, tnoise));
      }else{
        tt = sqrt(2.*(h_real+h0)/g)-t0;
      }
      // tt = sqrt(2.*(h_real+h0)/g)-t0-(r1->Uniform(-tnoise, tnoise));
      g1->SetPoint(i,tt, ht);
    }

    g1->GetXaxis()->SetName("x");
    g1->GetYaxis()->SetName("y");
    g1->GetXaxis()->SetTitle("x (arb. unit)");
    g1->GetYaxis()->SetTitle("y (arb. unit)");
    g1->SetLineWidth(1);
}

void gravity_simulation(){
  TCanvas * c1 = new TCanvas("c1","c1", 600, 400);

  TMultiGraph * mg = new TMultiGraph();

  TGraphErrors * g1 = new TGraphErrors();
  g1->SetName("g1");
  g1->SetTitle("Graph t:h");
  GenerateGraph(g1);
  g1->SetMarkerStyle(4);
  g1->SetMarkerColor(1);
  g1->SetMarkerSize(1);
  g1->Fit("pol2");
  mg->Add(g1);
  // g1->Draw("AP");

  TGraphErrors * g2 = new TGraphErrors();
  g2->SetName("g2");
  g2->SetTitle("Graph t:h, with Time Error 0.0001");
  GenerateGraph(g2, true, false);
  g2->SetMarkerColor(2);
  g2->SetMarkerStyle(33);
  g2->SetMarkerSize(1);
  g2->Fit("pol2");
  mg->Add(g2);
  // g2->Draw("AP");

  TGraphErrors * g3 = new TGraphErrors();
  g3->SetName("g3");
  g3->SetTitle("Graph t:h, with Overlapped Spatial Error");
  GenerateGraph(g3, false, true);
  g3->SetMarkerStyle(4);
  g3->SetMarkerColor(34);
  g3->SetMarkerSize(1);
  g3->Fit("pol2");
  mg->Add(g3);

  TGraphErrors * g4 = new TGraphErrors();
  g4->SetName("g4");
  g4->SetTitle("Graph t:h, with time, spatial error");
  GenerateGraph(g4, true, true);
  g4->SetMarkerColor(6);
  g4->SetMarkerStyle(45);
  g4->SetMarkerSize(1);
  g4->Fit("pol2");
  mg->Add(g4);

  mg->Draw("AP");
  c1->BuildLegend();

}
