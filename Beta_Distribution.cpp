/*
  File:         Beta_Distribution.cpp
  Version:      0.0.2
  Date:         30-Jan-2019
  Revision:     01-Feb-2019
  Author:       Jerome Drouin (jerome.p.drouin@gmail.com)

  Editions:	Please go to Beta_Distribution.h for Edition Notes.

  https://en.wikipedia.org/wiki/Beta_Distribution
  A special thank you to:
  http://www.mymathlib.com/functions/probability

  Beta_Distribution implements the Beta Distribution with shape Alpha and Beta. 

  Copyright (c) 2018-2019 Jerome Drouin  All rights reserved.

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
 
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
 
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/


#include "Arduino.h"
#include "Beta_Distribution.h"
#include <Gamma_Function.h>
#include <Beta_Function.h>


// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances
Beta_Distribution::Beta_Distribution(double _Alpha, double _Beta)
{

	// Object parameter's error handling
	error = 1;

	if (_Alpha<=0)		error = -2;				// Invalid definition domain
	if (_Beta<=0) 		error = -3;				// Invalid definition domain

	//Set initial values	
	Alpha			= _Alpha;		// 
	Beta			= _Beta;		// 

}


// Public Methods //////////////////////////////////////////////////////////////
//Probability Density Function
double Beta_Distribution::GetPDF(double x)
{
	if (error<0)
		return error;

	if (x <= 0.0) 
		return 0.0;

	if (x > 1.0) 
		return 0.0;
   	
	return pow(x,Alpha-1) * pow(1.0-x,Beta-1) / Beta_Function(Alpha,Beta);

}


//Cumulative Distribution Function
double Beta_Distribution::GetCDF(double x)
{
	if (error<0)
		return error;
	
	if (x <= 0.0) 
		return 0.0;

	if (x > 1.0) 
		return 1.0;

	return Beta_Distribution_Func(x,Alpha,Beta);
}

//Mean
double 	Beta_Distribution::GetMean(void)
{
	if (error<0)
		return error;

	return Alpha/(Alpha + Beta);
}


//Variance
double 	Beta_Distribution::GetVariance(void)
{
	if (error<0)
		return error;

	return Alpha*Beta / (pow(Alpha + Beta,2)*(Alpha + Beta + 1.0));

}


//Std Deviation
double 	Beta_Distribution::GetStdDeviation(void)
{
	if (error<0)
		return error;

	return sqrt(Alpha*Beta / (pow(Alpha + Beta,2)*(Alpha + Beta + 1.0)));
}


//Skewness
double 	Beta_Distribution::GetSkewness(void)
{
	if (error<0)
		return error;

	return 2.0 * (Beta - Alpha) * sqrt(Alpha+Beta+1) / (sqrt(Alpha*Beta)*(Alpha + Beta + 2.0));
}


//Kurtosis
double 	Beta_Distribution::GetKurtosis(void)
{
double numer;
double denom;

	if (error<0)
		return error;

	numer = 6 * (pow(Alpha-Beta,2)*(Alpha+Beta+1)-Alpha*Beta*(Alpha+Beta+2));
	denom = Alpha*Beta * (Alpha+Beta+2) * (Alpha+Beta+3);

	return numer / denom;
}


//Entropy
double 	Beta_Distribution::GetEntropy(void)
{
	if (error<0)
		return error;

	return Ln_Beta_Function(Alpha,Beta) 
		- (Alpha-1)*DiGamma_Function(Alpha)
		- (Beta-1)*DiGamma_Function(Beta)
		+ (Alpha+Beta-2)*DiGamma_Function(Alpha+Beta);

}



//Return Quantile z(P) from probability P
double Beta_Distribution::GetQuantile(double p)
{
double Vm;
double Vh = 100;
double Vl = 0;
double Pr;
int i = 0;
double Eps;

	if (p <= 0.0) {
		return Vl;
	} else if (p >= 1.0) {
        	return Vh;
	} else {        
        	do 
		{
          		i++;
          		Vm = (Vh + Vl) / 2;
            
			Pr = GetCDF(Vm);
          		Eps = abs(Pr - p);
			        
          		//New Boundary selection
          		if (Pr > p) {
				Vh = Vm;
          		} else {
				Vl = Vm;
			}
            
        	} 
		while ((Eps > CONSTANT_EpsStop) && (i < 70));
	}
            
        if (i >= 70) {
            return -9999;
        } else {
            return Vm;
    	}

}


double Beta_Distribution::GetAlpha(void)
{
	return Alpha;
}

double Beta_Distribution::GetBeta(void)
{
	return Beta;
}



// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library


// /////////////////////////////////////////////////////////////////////////////

