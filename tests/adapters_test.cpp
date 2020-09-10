// This file contains compile time tests.

#include <gtest/gtest.h>
#include "adapters_test.h"



constexpr size_t rows {3};
constexpr size_t cols {3};
using value_type = float;



template <typename Natural>
Natural deal_with_natural (const Natural & in)
{
    const Natural out = in;
    return out;
}

template <typename Adapter>
Adapter deal_with_adapter (const Adapter & in)
{
    const Adapter out = in;
    return out;
}

template <typename Adapter>
bool is_equal (const Adapter & x, const Adapter & y)
{
    return std::distance (x.begin (), x.end () )
        == std::distance (y.begin (), y.end () )
        && std::equal (x.begin (), x.end (), y.begin () );
}

template <typename Natural, typename Adapter>
void test_substitution (Natural n, Adapter a)
{
    Adapter x = a;
    std::fill (a.begin (), a.end (), 1);
    std::fill (x.begin (), x.end (), 2);

    ASSERT_FALSE (is_equal (a, x) );

    n = deal_with_natural<Natural> (n);
    n = deal_with_natural<Natural> (x);
    a = deal_with_natural<Natural> (n);
    a = deal_with_natural<Natural> (a);

    a = deal_with_adapter<Adapter> (a);
    a = deal_with_adapter<Adapter> (n);
    n = deal_with_adapter<Adapter> (a);
    n = deal_with_adapter<Adapter> (n);

    ASSERT_TRUE (is_equal (a, x) );
}



TEST (AdaptersTest, Substitution)
{
    #ifdef MUNKRES_CPP_ARMADILLO
    test_substitution (arma::Mat<value_type> (rows, cols)
                     , munkres_cpp::matrix_armadillo<value_type> (rows, cols) );
    #endif

    #ifdef MUNKRES_CPP_BOOST
    test_substitution (boost::numeric::ublas::matrix<value_type> (rows, cols)
                     , munkres_cpp::matrix_boost<value_type> (rows, cols) );
    #endif

    #ifdef MUNKRES_CPP_EIGEN3
    test_substitution (Eigen::Matrix<value_type, Eigen::Dynamic, Eigen::Dynamic> (rows, cols)
                     , munkres_cpp::matrix_eigen<value_type> (rows, cols) );
    #endif

    #ifdef MUNKRES_CPP_OPENCV
    test_substitution (cv::Mat_<value_type> (rows, cols)
                     , munkres_cpp::matrix_opencv<value_type> (rows, cols) );
    #endif

    #ifdef MUNKRES_CPP_QT
    test_substitution (QGenericMatrix<rows, cols, value_type> ()
                     , munkres_cpp::matrix_qt<value_type, rows, cols> (rows, cols) );
    #endif
}
