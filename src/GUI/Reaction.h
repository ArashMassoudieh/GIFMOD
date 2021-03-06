#pragma once
#ifdef GIFMOD
#include <vector>
#include "Crxtterm.h"
#include "StringOP.h"

using namespace std;



class CReaction
{
public:
	CReaction(void);
	CReaction(int nterms);
	CReaction(const CReaction &CR);
    CReaction operator=(const CReaction &CR);
	int nproducts;
	int nterms;
	int temp_exponent;
	int RxnID;
	CStringOP rate;
	vector<CStringOP> prodrates;
	vector<int> products;
	vector<int> product_phase;
	vector<int> product_p_type;
	vector<Crxtterm> terms;
    void set_n_terms(int);
    void set_n_prdcts(int);
    void getRxn(FILE *file);
	~CReaction(void);
	string name;
	

};

#endif
