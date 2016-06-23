#include        "stdafx.h"

#include        <boost/random.hpp>
#include        <boost/generator_iterator.hpp>

typedef boost::mt19937 base_generator_type;
typedef boost::lagged_fibonacci19937 fibo_generator_type;
typedef boost::uniform_int<> distribution_type;
typedef boost::variate_generator<fibo_generator_type&,


distribution_type> gen_type;

int random_number ( int bits )
{
        fibo_generator_type fibo_generator;
        int max = pow(static_cast<double>(10), bits);
        distribution_type dist(1, max);

        gen_type uni(fibo_generator, dist);
        return uni();

}               

/* -----  end of function random_number  ----- */


