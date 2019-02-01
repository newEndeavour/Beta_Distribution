/*
  File:         Beta_Distribution.h
  Version:      0.0.1
  Date:         30-Jan-2019
  Revision:     01-Feb-2019
  Author:       Jerome Drouin (jerome.p.drouin@gmail.com)

  References:
  https://github.com/newEndeavour/Beta_Distribution
  https://en.wikipedia.org/wiki/Beta_Distribution
  A special thank you to:
  http://www.mymathlib.com/functions/probability
  
  Beta_Distribution.h - Library for 'duino

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

  Editions:
  - 0.0.1	: First version

*/


// ensure this library description is only included once
#ifndef Beta_Distribution_h
#define Beta_Distribution_h


#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


//Gamma Constant Parameters
#define CONSTANT_EpsStop 0.0000001
    
//Number Pi
#define CONSTANT_Pi 3.14159265358979


// library interface description
class Beta_Distribution
{
  // user-accessible "public" interface
  public:
  // methods
	Beta_Distribution(double _Alpha, double _Beta);
	
	double 	GetPDF(double x);
	double 	GetCDF(double x);
	double 	GetQuantile(double p);

	double 	GetMean(void);
	double 	GetVariance(void);
	double 	GetStdDeviation(void);
	double 	GetSkewness(void);
	double 	GetKurtosis(void);
	double 	GetEntropy(void);

	double 	GetAlpha(void);
	double 	GetBeta(void);

  // library-accessible "private" interface
  private:
  // variables
	int 	error;

	double	Alpha;			// 
	double	Beta;			// 
	
  // methods
};

#endif
