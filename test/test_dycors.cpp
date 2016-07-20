/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   newsimpletest.cpp
 * Author: davideriksson
 *
 * Created on July 19, 2016, 12:44 PM
 */

#include <sot.h>
#include <armadillo>
#include <stdlib.h>
#include <iostream>

using namespace sot;

void test_dycors() {

    int dim = 10;
    int maxeval = 500;
    
    std::shared_ptr<Problem> data(new Ackley(dim));
    std::shared_ptr<ExpDesign> slhd(new SLHD(2*(dim+1), dim));
    std::shared_ptr<Surrogate> rbf(new CubicRBF(maxeval, dim, data->lbound(), data->rbound()));
    std::shared_ptr<Sampling> dycors(new DYCORS<>(data, rbf, 100*dim, maxeval - slhd->num_points));
    
    Optimizer opt(data, slhd, rbf, dycors, maxeval);
    Result res = opt.run();
    
    // Check that we made enough progress and that we are feasible
    assert(res.fbest <= -20.0);
    assert(arma::all(res.xbest >= data->lbound()));
    assert(arma::all(res.xbest <= data->rbound()));
    std::cout << res.fbest << std::endl;
}

int main(int argc, char** argv) {
    sot::StopWatch watch;
    std::cout << "==== Test Suite for SOT ====" << std::endl;

    std::cout << "Test1:" << std::endl;
    watch.start();
    test_dycors();
    double time = watch.stop();
    std::cout << "Time Elapsed: " << time << " seconds\n";

    return (EXIT_SUCCESS);
}

