void scatter_example_1(){
  TRandom3 * r1 = new TRandom3();
  TCanvas * c1 = new TCanvas();
  c1->SetName("c1");
  TGraph * g1 = new TGraph();
  g1->SetName("g1");
  Int_t i;
  Int_t npoint = 10;
  Double_t x,y;
  // r1->SetSeed(500);
  for(i=0; i<npoint; i++){
    x = 1*(i+1);
    // x = r1->Uniform(0,10);
    y = 2.*x+0.5+(r1->Uniform(-2,2));
    g1->SetPoint(i, x, y);
  }
  // g1->SetLineWidth(1);
  g1->SetMarkerStyle(20);
  g1->SetMarkerSize(0.8);
//  g1->GetXaxis()->SetName("x");
//  g1->GetYaxis()->SetName("y");

//  g1->GetXaxis()->SetTitle("");//SetTitle("x (arb. unit)");
//  g1->GetYaxis()->SetTitle("y (arb. unit)");

  // g1->Fit("pol1");
  g1->Draw();
}


// 0, 2.49897
// 1, 1.15164
// 2, 3.63047
// 3, 8.2888
// 4, 7.42663
// 5, 10.4399
// 6, 14.3299
// 7, 15.4772
// 8, 16.6602
// 9, 19.4598
