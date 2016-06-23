#include        "stdafx.h"
#include        "random_generator.h"

int main ( int argc, char *argv[] )
{
        cout.setf(ios::fixed);
        base_generator_type base_generator;
        double a = 10;
		int b = 2;
		int max = pow(a,b );
        distribution_type dist(1, max);

        boost::variate_generator<base_generator_type&,distribution_type > uni(base_generator, dist);
        for ( int i=0; i<10; i++ ) {
                //cout << random_number(2) << endl;
                cout << uni() << endl;
        }

        return EXIT_SUCCESS;

}                              
/* ----------  end of function main  ---------- */




