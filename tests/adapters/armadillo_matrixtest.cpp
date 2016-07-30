#include <gtest/gtest.h>
#include "munkres.h"
#include "adapters/armadillo_matrix.h"



class Adapters_armadillo_matrix_Test : public ::testing::Test
{
};



TEST_F (Adapters_armadillo_matrix_Test, solve_armadillo_matrix_Success)
{
    // Arrange.
    static constexpr size_t dimension {3};
    munkres::matrix_armadillo<double> etalon_armadillo_matrix (dimension, dimension);
    //  {-1.0,  0.0, -1.0},
    //  { 0.0, -1.0, -1.0},
    //  {-1.0, -1.0,  0.0}
    etalon_armadillo_matrix (0, 0) = -1.0; etalon_armadillo_matrix (0, 1) =  0.0; etalon_armadillo_matrix (0, 2) = -1.0;
    etalon_armadillo_matrix (1, 0) =  0.0; etalon_armadillo_matrix (1, 1) = -1.0; etalon_armadillo_matrix (1, 2) = -1.0;
    etalon_armadillo_matrix (2, 0) = -1.0; etalon_armadillo_matrix (2, 1) = -1.0; etalon_armadillo_matrix (2, 2) =  0.0;

    munkres::matrix_armadillo<double> test_armadillo_matrix (dimension, dimension);
    //  {1.0,  0.0,  1.0},
    //  {0.0,  1.0,  1.0},
    //  {1.0,  1.0,  0.0}
    test_armadillo_matrix (0, 0) = 1.0; test_armadillo_matrix (0, 1) = 0.0; test_armadillo_matrix (0, 2) = 1.0;
    test_armadillo_matrix (1, 0) = 0.0; test_armadillo_matrix (1, 1) = 1.0; test_armadillo_matrix (1, 2) = 1.0;
    test_armadillo_matrix (2, 0) = 1.0; test_armadillo_matrix (2, 1) = 1.0; test_armadillo_matrix (2, 2) = 0.0;

    // Act.
    Munkres<double> solver;
    solver.solve (test_armadillo_matrix);

    // Assert.
    for (unsigned int row = 0; row < dimension; ++row) {
        for (unsigned int col = 0; col < dimension; ++col) {
            EXPECT_EQ ( etalon_armadillo_matrix (row, col), test_armadillo_matrix (row, col) );
        }
    }
}
