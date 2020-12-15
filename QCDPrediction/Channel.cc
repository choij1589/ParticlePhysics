#include "Channel.h"

Channel::Channel(const int lhaid) { __calc = new XsecTools(lhaid); }
Channel::~Channel() { delete __calc; }

double Channel::dXsec_dEta_with_pdf(const double &x1, const double &x2, const double &E_cm, const double &eta) {
	double out = 1.;
	double alpha_s = -999.;
	double xf1 = -999.;
	double xf2 = -999.;
	const double dCos_dEta = 4.*Exp(2.*eta) / Power(Exp(2.*eta)+1., 2.);
	const double to_pb = 0.389379 * 10e9;
	const double hat_s = __calc->hatS(x1, x2, E_cm);
	const double hat_t = __calc->hatT(x1, x2, E_cm, eta);
	const double hat_u = __calc->hatU(x1, x2, E_cm, eta);

	if (__channel == "ud_to_ud") {
		const double q2 = -1.*hat_t;
		alpha_s = __calc->alphaS(q2);
		xf1 = __calc->xf(2, x1, q2);
		xf2 = __calc->xf(1, x2, q2);
		out *= 2.*PI*Power(alpha_s, 2);
		out /= (9*hat_s);
		out *= ((Power(hat_s, 2)+Power(hat_u, 2))/Power(hat_t, 2));
	}
	else if (__channel == "uu_to_uu" ) {
		const double q2 = -1.*(hat_t + hat_u) / 2.;
		alpha_s = __calc->alphaS(q2);
		xf1 = __calc->xf(2, x1, q2);
		xf2 = __calc->xf(2, x2, q2);
		out *= 2.*PI*Power(alpha_s, 2);
		out /= (9.*hat_s);
		out *= (((Power(hat_s, 2) + Power(hat_u,2))/Power(hat_t, 2)) + ((Power(hat_s, 2) + Power(hat_t, 2)) / Power(hat_u, 2)) - (2./3.)*(Power(hat_s, 2)/(hat_t*hat_u)));
	}
	else if (__channel == "uubar_to_ddbar") {
		const double q2 = (hat_s - hat_t) / 2.;
		alpha_s = __calc->alphaS(q2);
		xf1 = __calc->xf(2, x1, q2); // u
		xf2 = __calc->xf(-2, x1, q2); // u~
		out *= 2.*PI*Power(alpha_s, 2);
		out /= (9.*hat_s);
		out *= ((Power(hat_t, 2) + Power(hat_u, 2)) / Power(hat_s, 2));
	}
	else if (__channel == "uubar_to_uubar") {
		const double q2 = (hat_s - hat_t) / 2.;
		alpha_s = __calc->alphaS(q2);
		xf1 = __calc->xf(2, x1, q2); // u
		xf2 = __calc->xf(-2, x2, q2); // u~
		out *= 2.*PI*Power(alpha_s, 2);
		out /= (9.*hat_s);
		out *= (((Power(hat_s, 2) + Power(hat_u,2))/Power(hat_t, 2)) + ((Power(hat_t, 2) + Power(hat_u, 2)) / Power(hat_s, 2)) - (2./3.)*(Power(hat_u, 2)/(hat_s*hat_t)));
	}
	else if (__channel == "uubar_to_gg") {
		const double q2 = hat_s;
		alpha_s = __calc->alphaS(q2);
		xf1 = __calc->xf(2, x1, q2); // u
		xf2 = __calc->xf(-2, x2, q2); // u~
		out *= 16.*PI*Power(alpha_s, 2);
		out /= (27.*hat_s);
		out *= ((hat_u / hat_t) + (hat_t / hat_u) - (9./4.)*((Power(hat_t, 2)+Power(hat_u, 2))/Power(hat_s, 2)));
	}
	else if (__channel == "ug_to_ug") {
		const double q2 = -1.*hat_t;
		alpha_s = __calc->alphaS(q2);
		xf1 = __calc->xf(2, x1, q2); // u
        xf2 = __calc->xf(21, x2, q2); // g
		out *= 2.*PI*Power(alpha_s, 2);
		out /= (9.*hat_s);
		out *= (-(hat_u/hat_s)-(hat_s/hat_u)+(9./4.)*((Power(hat_s, 2)+Power(hat_u, 2))/Power(hat_t, 2)));
	}
	else if (__channel == "gg_to_uubar") {
		const double q2 = hat_s;
		alpha_s = __calc->alphaS(q2);
		xf1 = __calc->xf(21, x1, q2);
		xf2 = __calc->xf(21, x2, q2);
		out *= PI*Power(alpha_s, 2);
		out /= (12.*hat_s);
		out *= ((hat_u / hat_t) + (hat_t / hat_u) - (9./4.)*((Power(hat_t, 2)+Power(hat_u, 2))/Power(hat_s, 2)));
	}
	else if (__channel == "gg_to_gg") {
		const double q2 = (hat_s - hat_t - hat_u) / 3.;
		alpha_s = __calc->alphaS(q2);
		xf1 = __calc->xf(21, x1, q2);
		xf2 = __calc->xf(21, x2, q2);
		out *= 9.*PI*Power(alpha_s, 2);
		out /= (4.*hat_s);
		out *= (3.-(hat_t*hat_u/Power(hat_s, 2))-(hat_s*hat_u/Power(hat_t, 2))-(hat_s*hat_t/Power(hat_u, 2)));
		//cout << "q2: " << q2 << endl;
		//cout << "alpha_s: " << alpha_s << endl;
		//cout << "xf1: " << xf1 << endl;
		//cout << "xf2: " << xf2 << endl;
		//cout << "QCD factor: " << 9.*PI*Power(alpha_s, 2) << endl;
		//cout << (4.*hat_s) << endl;
		//cout << (3.-(hat_t*hat_u/Power(hat_s, 2))-(hat_s*hat_u/Power(hat_t, 2))-(hat_s*hat_t/Power(hat_u, 2))) << endl;
		//cout << (hat_t*hat_u)/Power(hat_s, 2) << endl;
		//cout << (hat_s*hat_u)/Power(hat_t, 2) << endl;
		//cout << (hat_s*hat_t)/Power(hat_u, 2) << endl;
	}
	else {
		cerr << "Channel info is not set" << endl;
		exit(EXIT_FAILURE);
	}

	if (alpha_s < 0) {
		cerr << "negative alpha_s: " << alpha_s << endl;
		exit(EXIT_FAILURE);
	}

	out *= dCos_dEta;
	out *= to_pb;
	return out * xf1 * xf2;
}

void Channel::xsec(const double &E_cm, const double &etaCut) {
	// proceed MC integration
	const unsigned int nEvents = 1000000;
	double sum = 0;
	const double volume = 2.*etaCut*1.*1.;
	double xsecs[nEvents];

	// Do 3D MC integration
	gRandom->SetSeed(time(0));
	for (unsigned int i = 0; i < nEvents; i++) {
		const double x1 = gRandom->Uniform(0., 1.);
		const double x2 = gRandom->Uniform(0., 1.);
		const double eta = gRandom->Uniform(-etaCut, etaCut);
		const double this_xsec = dXsec_dEta_with_pdf(x1, x2, E_cm, eta);
		xsecs[i] = this_xsec;
		sum += this_xsec;

	}
	const double exp = sum / nEvents; // <f>

	// Now estimate the error
	double variance = 0.;
	for (unsigned int i = 0; i < nEvents; i++)
		variance += Power(xsecs[i] - exp, 2);
	variance /= (nEvents-1);
	variance *= Power(volume, 2) / nEvents;

	const double out = exp * volume; // I = V<f>
	const double err = Sqrt(variance);
	cout << "Total xsec for " << __channel << ": " << out << " [pb]" << endl;
	cout << "Total xsec error for " << __channel << ": " << err << " [pb]" << endl;
	cout << "\n";
}		
