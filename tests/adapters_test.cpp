// This file contains compile time tests.
//
// The functions below are not supposed to be called in runtime.

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

template <typename Natural, typename Adapter>
void test_substitution (Natural n, Adapter a)
{
    n = deal_with_natural<Natural> (n);
    n = deal_with_natural<Natural> (a);
    a = deal_with_natural<Natural> (n);
    a = deal_with_natural<Natural> (a);

    a = deal_with_adapter<Adapter> (a);
    a = deal_with_adapter<Adapter> (n);
    n = deal_with_adapter<Adapter> (a);
    n = deal_with_adapter<Adapter> (n);
}



#ifdef MUNKRES_CPP_ARMADILLO
void test_matrix_armadillo ()
{
    test_substitution (arma::Mat<value_type> (rows, cols)
                    , munkres_cpp::matrix_armadillo<value_type> (rows, cols) );
}
#endif



#ifdef MUNKRES_CPP_BOOST
void test_matrix_boost ()
{
    test_substitution (boost::numeric::ublas::matrix<value_type> (rows, cols)
                     , munkres_cpp::matrix_boost<value_type> (rows, cols) );
}
#endif



#ifdef MUNKRES_CPP_EIGEN3
void test_matrix_eigen ()
{
    test_substitution (Eigen::Matrix<value_type, Eigen::Dynamic, Eigen::Dynamic> (rows, cols)
                     , munkres_cpp::matrix_eigen<value_type> (rows, cols) );
}
#endif



#ifdef MUNKRES_CPP_OPENCV
void test_matrix_opencv ()
{
    test_substitution (cv::Mat_<value_type> (rows, cols)
                     , munkres_cpp::matrix_opencv<value_type> (rows, cols) );
}
#endif



#ifdef MUNKRES_CPP_QT
void test_matrix_qt ()
{
    test_substitution (QGenericMatrix<rows, cols, value_type> ()
                     , munkres_cpp::matrix_qt<value_type, rows, cols> (rows, cols) );
}
#endif
