#include <iostream>
#include <vector>
#include "LHAPDF/LHAPDF.h"
#include "TFile.h"
#include "TH1D.h"

using namespace LHAPDF;
using namespace std;

int main() {
	PDF* pdf = mkPDF(326300);
	TH1D* h_u = new TH1D("ux", "", 1000, 0., 1.);
	TH1D* h_d = new TH1D("dx", "", 1000, 0., 1.);
	TH1D* h_g = new TH1D("gx", "", 1000, 0., 1.);
	double q2 = 5000.*5000.;

	for (int i = 1; i < 1000; i++) {
		double x = i/1000.;
		h_u->Fill(x, pdf->xfxQ2(2, x, q2));
		h_d->Fill(x, pdf->xfxQ2(1, x, q2));
		h_g->Fill(x, pdf->xfxQ2(21, x, q2));
	}
	TFile* f = new TFile("out.root", "recreate");
	f->cd();
	h_u->Write();
	h_d->Write();
	h_g->Write();
	f->Close();
}
	
