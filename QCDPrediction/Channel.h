#ifndef Channel_h__
#define Channel_h__

#include "XsecTools.h"
#include <string>
class Channel {
private:
	XsecTools* __calc = nullptr;
	string __channel;
public:
	Channel(const int lhaid);
	~Channel();
	
	void set_channel(const string &channel) { __channel = channel;}
	// define channel dependent differential cross section
	double dXsec_dEta_with_pdf(const double &x1, const double &x2, const double &E_cm, const double &eta);
	// Monte Carlo integrate to get the total xsection
	void xsec(const double &E_cm, const double &etaCut);
};

#endif
