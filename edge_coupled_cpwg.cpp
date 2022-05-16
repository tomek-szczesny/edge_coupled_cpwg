// Conductor-backed edge coupled coplanar waveguides calculator
// By Tomek Szczęsny, 2022
// Based on:
// Rainee N. Simons "Coplanar waveguide Circuits, Components, and Systems", 2001, Ch. 7.4
// Brian C. Wadell "Transmission Line Design Handbook", 1991, Ch. 4.4.3

#define __STDCPP_WANT_MATH_SPEC_FUNCS__ 1
#include <cmath>
#include <iostream>

// Constants
const double pi = 3.14159265358979323846;
const double eta_0 = 120 * pi;	// Characteristic impedance of free space

// Physical dimensions
double d = 0.15;		// space between strip conductors
double S = 0.28;		// strip conductors' width
double W = 0.15;		// space between strip conductor and ground plane
double t = 0.035;		// copper thickness
double h = 1.593;		// dielectric thickness
#define a (d/2)
#define b (d/2+S)
#define c (d/2+S+W)
#define r (a/b)
#define k1 (b/c)
#define delta (sqrt((1-r*r)/(1-k1*k1*r*r)))

// Electrical parameters
double epsilon_r = 4.5;	// relative permittivity / dielectric constant


inline double K(double arg) {			// Complete elliptic integral of the first kind
	return std::comp_ellint_1(arg);
}

double K_prime(double arg) {			// Complementary modulus of K
	return K(1 - (arg*arg));
}

double Kokp(double arg) {			// K / K'
	return K(arg)/K_prime(arg);
}

#define phi1 (0.5*pow(cosh((pi/(2*h))*c),2))
#define phi2 (pow(sinh((pi/(2*h))*b),2)-phi1+1)
#define phi3 (pow(sinh(pi*d/(4*h)),2)-phi1+1)
#define phi4 (0.5*pow(sinh((pi/(2*h))*c),2))
#define phi5 (pow(sinh((pi/(2*h))*b),2)-phi4)
#define phi6 (pow(sinh(pi*d/(4*h)),2)-phi4)

#define ke (phi1*(-sqrt(phi1*phi1-(phi2*phi2))+sqrt(phi1*phi1-(phi3*phi3)))/(phi3*sqrt(phi1*phi1-(phi2*phi2))+phi2*sqrt(phi1*phi1-(phi3*phi3))))
#define ko (phi4*(-sqrt(phi4*phi4-(phi5*phi5))+sqrt(phi4*phi4-(phi6*phi6)))/(phi6*sqrt(phi4*phi4-(phi5*phi5))+phi5*sqrt(phi4*phi4-(phi6*phi6))))

#define Er_even ((2*epsilon_r*(Kokp(ke))+(Kokp(delta*k1)))/((2*Kokp(ke))+(Kokp(delta*k1))))
#define Er_odd  ((2*epsilon_r*(Kokp(ko))+(Kokp(delta   )))/((2*Kokp(ko))+(Kokp(delta   ))))

#define Zeven (eta_0/(sqrt(Er_even)*(2*(Kokp(ke))+(Kokp(delta*k1)))))
#define Zodd  (eta_0/(sqrt(Er_odd )*(2*(Kokp(ko))+(Kokp(delta   )))))

#define Zdiff (Zodd  * 2)
#define Zcomm (Zeven / 2)
#define Z0    (sqrt(Zeven * Zodd))

int main(int argc, char* argv[])
{

	if (argc != 7) {
		std::cout << "\n"
			  << "Conductor-backed edge coupled coplanar waveguides calculator\n"
			  << "By Tomek Szczęsny, 2022\n"
			  << "\n"
			  << "Based on:\n"
			  << "Rainee N. Simons \"Coplanar waveguide Circuits, Components, and Systems\", 2001, Ch. 7.4\n"
			  << "Brian C. Wadell \"Transmission Line Design Handbook\", 1991, Ch. 4.4.3\n"
			  << "\n"
			  << "Usage:\n"
			  << "edge_coupled_cpwg d S W t h Er\n"
			  << "\n"
			  << "Example:\n"
			  << "edge_coupled_cpwg 0.2 0.41 0.2 0.035 1.593 4.5\n"
			  << "\n"
			  << "                      / /   /            / /   /            / /   /             \n"
			  << "                     / /   /            / /   /            / /   /              \n"
			  << "                    / /   /            / /   /            / /   /               \n"
			  << "                   / /   /            / /   /            / /   /                \n"
			  << "                  / /   /            / /   /            / /   /                 \n"
			  << "-----------------+ /   +------------+ /   +------------+ /   +----------------  \n"
			  << "  Ground Plane   |/    |   Diff -   |/    |   Diff +   |/    | Ground Plane   }t\n"
			  << "-----------------+-----+------------+-----+------------+-----+----------------  \n"
			  << " . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .  ^ \n"
			  << ". . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . | \n"
			  << " . . . . . . . . . . . . . . . . .Dielectric . . . . . . . . . . . . . . . .  |h\n"
			  << ". . . . . . . . . . . . . . . . . . . Er. . . . . . . . . . . . . . . . . . . | \n"
			  << " . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .  | \n"
			  << ". . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . v \n"
			  << "------------------------------------------------------------------------------  \n"
			  << "                           G r o u n d   P l a n e                              \n"
			  << "                                                                                \n"
			  << "                 |     |            |     |            |     |                  \n"
			  << "                 |<--->|<---------->|<--->|<---------->|<--->|                  \n"
			  << "                    W        S         d         S        W                     \n"
			  << "\n"
		;
		exit(0);
	}

	d=atof(argv[1]);
	S=atof(argv[2]);
	W=atof(argv[3]);
	t=atof(argv[4]);
	h=atof(argv[5]);
	epsilon_r=atof(argv[6]);

    std::cout << "Er_even = " << Er_even << '\n'
	      << "Er_odd  = " << Er_odd << '\n'
	      << "Zeven   = " << Zeven << '\n'
	      << "Zodd    = " << Zodd << '\n'
	      << "Z0      = " << Z0 << '\n'
	      << "Zdiff   = " << Zdiff << '\n'
	      << "Zcomm   = " << Zcomm << '\n';
}
