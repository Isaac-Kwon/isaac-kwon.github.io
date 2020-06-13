class GGraph: public TGraphErrors{
private:
  Float_t xycor(Float_t x);
  Float_t g = 9.80665;
  Float_t hmax = 1.0;
  Float_t hmin = 0.;
  Int_t npoint = 10;
  Float_t stepsize = (hmax-hmin)/npoint;
  Float_t h_offset = 0.;
  Float_t t_offset = 0.;
  TRandom3 * r;
  UInt_t seed;

protected:
public:
  GGraph(const char* name);
  void GenerateGraphIdeal();
  void GenerateGraphOffset(Float_t h_off=0., Float_t t_off=0.);
  void AddNoiseH(Float_t erange, Bool_t overlapped = true, Bool_t initzero = true);
  void AddNoiseT(Float_t erange, Bool_t overlapped = false, Bool_t initzero = true);
  UInt_t GetSeed(){return seed;}
  void SetSeed(UInt_t seed_){r->SetSeed(seed_);}

};

GGraph::GGraph(const char* name): TGraphErrors(){
  SetName(name);
  r = new TRandom3();
  seed = TUUID().GetTime().Get();
  r->SetSeed(seed);
}

Float_t GGraph::xycor(Float_t x){
  return sqrt(2.*(x)/g);
}

void GGraph::GenerateGraphIdeal(){
    Int_t i;
    Float_t tt,ht;
    for(i=0; i<npoint-1; i++){
      ht = stepsize*(i+1);
        tt = xycor(ht);
      // tt = sqrt(2.*(h_real+h0)/g)-t0-(r1->Uniform(-tnoise, tnoise));
      SetPoint(i,tt, ht);
    }
}

void GGraph::GenerateGraphOffset(Float_t h_off, Float_t t_off){
    Int_t i;
    Float_t tt,ht;
    h_offset = h_off;
    t_offset = t_off;
    for(i=0; i<npoint-1; i++){
      ht = stepsize*(i+1);
        tt = xycor(ht+h_off)-t_off;
      // tt = sqrt(2.*(h_real+h0)/g)-t0-(r1->Uniform(-tnoise, tnoise));
      SetPoint(i,tt, ht);
    }
}

void GGraph::AddNoiseH(Float_t erange, Bool_t overlapped, Bool_t initzero){
  Int_t i;
  Double_t t,h; //x:t, y:h
  Double_t realh;
  Double_t noise = 0;//initzero&&overlapped ? 0 : r->Uniform(-erange, erange);
  for(i=initzero&&overlapped?1:0 ; i<GetN(); i++){
    GetPoint(i,t,h);
    noise = overlapped ? noise + (r->Uniform(-erange, erange)) : (r->Uniform(-erange, erange));
    realh = h+noise;
    t = xycor(realh+h_offset)-t_offset;
    SetPoint(i,t,h);
  }
}

void GGraph::AddNoiseT(Float_t erange, Bool_t overlapped, Bool_t initzero){
  Int_t i;
  Double_t t,h; //x:t, y:h
  Double_t noise = 0;//initzero&&overlapped ? 0 : r->Uniform(-erange, erange);
  for(i=initzero&&overlapped?1:0 ; i<GetN(); i++){
    GetPoint(i,t,h);
    noise = overlapped ? noise + (r->Uniform(-erange, erange)) : (r->Uniform(-erange, erange));
    t = t-noise;
    SetPoint(i,t,h);
  }
}

Float_t gravity_simulation_ONE(UInt_t seed = TUUID().GetTime().Get()){
  // TCanvas * c1 = new TCanvas("c1", "c1", 800, 600);

  //Generate IDEAL Case
  GGraph * g = new GGraph("g");
  g->SetSeed(seed);
  g->GenerateGraphOffset(0.,0.);

  //COPY IDEAL CASE
  TGraphErrors * g1 = new TGraphErrors(*g); // without offset
  g1->SetName("g1");
  g1->SetTitle("Ideal Case");
  g1->SetMarkerStyle(20);
  g1->SetMarkerSize(1);
  // g1->Fit("pol2");

  //Add Offset (t0 = 0., x0 = 0.02)
  // g->GenerateGraphOffset(0.,0.02);

  //COPY OFFSET CASE
  // TGraphErrors * g2 = new TGraphErrors(*g); // offset
  // g2->SetName("g2");
  // g2->SetTitle("Offset Case ($$t_0=0.02$$)");
  // g2->SetMarkerStyle(20);
  // g2->SetMarkerSize(1);
  // g2->SetMarkerColor(3);
  // g2->Fit("pol2");

  //Add Height Uncertainty (dH = 0.01:1cm, overlapped noise)
  g->AddNoiseH(0.005, false, true);
  TGraphErrors * g3 = new TGraphErrors(*g); // offset, height noise
  g3->SetName("g3");
  g3->SetTitle("Height Noise");
  g3->SetMarkerStyle(20);
  g3->SetMarkerSize(1);
  g3->SetMarkerColor(7);
  // g3->Fit("pol2");

  g->AddNoiseT(0.0001);
  TGraphErrors * g4 = new TGraphErrors(*g); // offset, height noise
  g4->SetName("g4");
  g4->SetTitle("Height Noise, Time Noise");
  g4->SetMarkerStyle(20);
  g4->SetMarkerSize(1);
  g4->SetMarkerColor(24);
  TFitResultPtr r = g4->Fit("pol2","S");

  cout<<"FITPAR: "<<r->Value(2)<<endl;

  TMultiGraph * mg = new TMultiGraph();
  mg->Add(g);
  mg->Add(g1);
  // mg->Add(g2);
  mg->Add(g3);
  mg->Add(g4);
  mg->Draw("AP");

  mg->GetXaxis()->SetTitle("t (second)");
  mg->GetYaxis()->SetTitle("h (meter)");

  mg->GetXaxis()->SetLimits(0.2, 0.5);
  mg->GetYaxis()->SetRangeUser(0.2, 1.0);
  // c1->BuildLegend();
  // c1->Update();

  return 2*r->Value(2);

}

void gravity_simulation(){
  Int_t i;
  Float_t val;
  TRandom3 * r1 = new TRandom3();
  TH1F * h1 = new TH1F("h1","h1",1000,0,20);
  for(i=0; i<4000; i++){
    h1->Fill(gravity_simulation_ONE(r1->Uniform(0,100000000)));
  }
  h1->Draw();

}
