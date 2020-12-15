#ifndef XsecTools_H__
#define XsecTools_H__

#include <iostream>
#include <string>
#include <vector>
#include "LHAPDF/LHAPDF.h"
#include "TMath.h"
#include "TRandom.h"

using namespace LHAPDF;
using namespace std;

// Define constants and inline functions
static const double PI = TMath::Pi();
inline double Exp(double x) { return TMath::Exp(x); }
inline double Power(double x, double k) { return TMath::Power(x, k); }
inline double Sqrt(double x) { return TMath::Sqrt(x); }

class XsecTools {
private:
	int __lhaid;
	PDF* __pdf;
public:
	XsecTools(const int lhaid): __lhaid(lhaid) { __pdf = mkPDF(lhaid); }
	double hatS(const double &x1, const double &x2, const double &E_cm) 
	{
		return x1*x2*Power(E_cm, 2); 
	}
	double hatT(const double &x1, const double &x2, const double &E_cm, const double &eta) 
	{
		double forward_singularity = 1./(Exp(2.*eta) + 1.);
		return -1.* hatS(x1, x2, E_cm) * forward_singularity;
	}
	double hatU(const double &x1, const double &x2, const double &E_cm, const double &eta) 
	{
		double backward_singularity = Exp(2.*eta)/(Exp(2.*eta) + 1.);
		return -1.* hatS(x1, x2, E_cm) * backward_singularity;
	}
	// q2 is process dependent
	double xf(const int pid, const double &x, const double q2) 
	{	return __pdf->xfxQ2(pid, x, q2); }
	double alphaS(const double q2) 
	{ 	return __pdf->alphasQ2(q2);}
};

#endif
