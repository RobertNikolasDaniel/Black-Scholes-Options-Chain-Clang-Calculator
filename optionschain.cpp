#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <string>

//Black-Scholes C++ Terminal Calculator
//NO AI USED, Just PowerShell and NotePad
//Credits GitHub RobertNikolasDaniel
//This was build to help concetualize Black Scholes Options Pricing, Each step is broken down to help conceptual mastery

//MAIN

int main() {

        //---WELCOME TEXT---

        std::cout << "\n" << std::endl;
        std::cout << "---Black Scholes Fair Value Options Chain C++ Terminal Calculator---\n" << std::endl;

        //---DEFINE VARIABLES---

        double price, time, sofr, implied, interval, chainsize;

        //---INPUT VARIABLES---

        std::cout << "---INPUTS---\n";

        //Price
        std::cout << "\nUnderlying Price: ";
        std::cin >> price;

        //Time
        std::cout << "\nDays To Expiry: ";
        std::cin >> time;

        //Sofr
        std::cout << "\nOvernight SOFR (Bps): ";
        std::cin >> sofr;
	      sofr = sofr / 10000;

        //Implied Volatility
        std::cout << "\nImplied Volatility (Percentage): ";
        std::cin >> implied;
      	implied = implied / 100;

        //Strike Interval
        std::cout << "\nStrike Interval: ";
        std::cin >> interval;

        //Chain Size
        std::cout << "\nHow Many Options: ";
        std::cin >> chainsize;

        //---FORMAT DATA PROPERLY---
       
        //Make Chainsize an Even Integer
        int chainsizeq = chainsize;
        if ( chainsizeq % 2 == 1 ) {
                chainsizeq++;
                chainsize = chainsizeq;
        } else {
                chainsize = chainsizeq;
        }

        //Create a Price Interget
        int priceq = price;

        //Create a Clean Minimum Strike
        //1 use a temp clean price double
        double priceqq = priceq;
        //2 calculate lowest strike
        double lowest = priceqq - ( ( chainsize / 2 ) * interval );

        //---PRE LOOP OPTIONS MATH---

        //annualize time
        double atime = time / 365;

        //discount factor
        double df = std::exp( -sofr * atime );

        //square time
        double stime = std::sqrt( atime );

        //vol adjust squared time
        double svtime = stime * implied;
               
        //---STRUCTURE VECTOR---

        struct optionschain {
                double strike;
               
                //call structure
                double Cpremium;
                double Cdelta;
                double Cgamma;
                double Ctheta;
                double Cvega;
                double Crho;

                //put structure
                double Ppremium;
                double Pdelta;
                double Pgamma;
                double Ptheta;
                double Pvega;
                double Prho;
        };

        //---CREATE STRUCTURED VECTOR---

        std::vector<optionschain> option;

	//---BUILD OPTIONS CHAIN WITH FOR LOOP---
	
	double q;
	for ( q = 0; q < chainsize; q++ ) {

		//---STORAGE VECTOR---
		optionschain temp;

		//---OPTION STRIKE---
		double strike = lowest + ( q * interval );
		temp.strike = strike;

		//---GAUSSIAN NORMAL PROBABILITY FUNCTIONS---

		//do
		double doo = ( ( std::log( price / strike ) + ( ( sofr + ( ( implied * implied ) / 2 ) ) ) * atime ) ) / svtime;

		//dt
		double dt = doo - svtime;
	
		//Ndo CALL
		double ndoc = 0.5 * std::erfc( -doo / std::sqrt( 2 ) );

		//Ndo PUT
		double ndop = 0.5 * std::erfc( doo / std::sqrt( 2 ) );

		//Ndt CALL
		double ndtc = 0.5 * std::erfc( -dt / std::sqrt( 2 ) );

		//Ndt PUT
		double ndtp = 0.5 * std::erfc ( dt / std::sqrt( 2 ) );

		//---OPTION PREMIUM---

		//Call Premium
		double cp = ( price * ndoc ) - ( strike * df * ndtc );
		temp.Cpremium = cp;

		//Put Premium
		double pp = ( strike * df * ndtp ) - ( price * ndop);
		temp.Ppremium = pp;

		//---GAUSSIAN BELLCURE HEIGHT, powers the greeks---

		double bellh = ( 1.0 / ( std::sqrt( 2 * 3.1415926535 ) ) ) * std::exp( -0.5 * doo * doo );

		//---OPTION GREEKS---

		//---DELTA---

		//Call
		temp.Cdelta = ndoc;

		//Put 
		temp.Pdelta = ndoc - 1.0;

		//---GAMMA---

		//Gamma
		double gamma = bellh / ( price * svtime );
		temp.Cgamma = gamma;
		temp.Pgamma = gamma;

		//---THETA---

		//Theta Base
		double thetabase = -( price * bellh * implied ) / ( 2.0 * stime );

		//Call Theta
		double calltheta = ( thetabase - ( sofr * strike * df * ndtc ) ) / 365;
		temp.Ctheta = calltheta;

		//Put Theta
		double puttheta = ( thetabase - ( sofr * strike * df * ndtp ) ) /365;
		temp.Ptheta = puttheta;

		//---VEGA---
		
		double vega = ( price * bellh * stime ) / 100;
		temp.Cvega = vega;
		temp.Pvega = vega;

		//---RHO---

		//Call Rho
		double callrho = ( strike * atime * df * ndtc ) / 100;
		temp.Crho = callrho;

		//Put Rho
		double putrho = ( -strike * atime * df * ndtp ) / 100;
		temp.Prho = putrho;

		//---PUSH TEMP---
		option.push_back(temp);
	}

	//---OUTPUT TABLE FOR OPTIONS CHAIN---
	std::cout << "\n" << std::endl;
	std::cout << "\n" << std::endl;
	std::cout << "\n---OPTIONS CHAIN---\n" << std::endl;
	std::cout << "\n" << std::endl;

	//formatting
	std::cout << std::fixed << std::setprecision(2);

	
	//title
	std::cout << std::string( 59, '=' ) << " PUTS " << std::string( 18, '=' ) << " CALL " << std::string( 67, '=' ) << "\n" << std::endl;

	//header
	std::cout << std::left
		  << std::setw(12) << "RHO"
		  << std::setw(12) << "VEGA"
		  << std::setw(12) << "THETA"
		  << std::setw(12) << "GAMMA"
		  << std::setw(12) << "DELTA"
		  << std::setw(12) << "PREM"
		  << std::setw(12) << "STRIKE"
		  << std::setw(12) << "PREM"
		  << std::setw(12) << "DELTA"
		  << std::setw(12) << "GAMMA"
		  << std::setw(12) << "THETA"
		  << std::setw(12) << "VEGA"
		  << std::setw(12) << "RHO"
		  << "\n";

	//divider
	std::cout << std::string( 156, '-' ) << "\n";
	std::cout << "\n";

	//for loop to generate body
	int w;
	for ( w = 0; w < option.size(); w++ ) {
		std::cout << std::left
			  << std::setw(12) << option[w].Prho * 100
			  << std::setw(12) << option[w].Pvega * 100
			  << std::setw(12) << option[w].Ptheta * 100
			  << std::setw(12) << option[w].Pgamma * 100
			  << std::setw(12) << option[w].Pdelta * 100
			  << std::setw(12) << option[w].Ppremium * 100
			  << std::setw(12) << option[w].strike
			  << std::setw(12) << option[w].Cpremium * 100
			  << std::setw(12) << option[w].Cdelta * 100
			  << std::setw(12) << option[w].Cgamma * 100
			  << std::setw(12) << option[w].Ctheta * 100
			  << std::setw(12) << option[w].Cvega * 100
			  << std::setw(12) << option[w].Crho * 100
			  << "\n"
			  << std::string( 156, '-' ) << "\n";
	}
		
	//extra space at bottom
	std::cout << "\n" << std::endl;
       
        //RETURN 0
        return 0;
}
