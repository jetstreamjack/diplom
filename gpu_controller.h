#pragma once

#include <vector>

namespace controller {

class GpuController
{
public:

    /**
     * @brief Invoker Claster function
     * @param funcNumber - number of function
     * @param path - data for function
     * @param res - result of function
     */
    __host__ __device__ void InvokeClasterFunction(int numFunc, double* path, double* res);
private:
    __host__ __device__ double Klaster1(double* path);
    __host__ __device__ double BenchRozenbrok(double* path);
    __host__ __device__ double BenchMultiFunction(double* path);
    __host__ __device__ double BenchBirdFunction(double* path);
    __host__ __device__ double BenchShevefeliaFunction(double* path);
    __host__ __device__ double BenchRozenbrokx10(double* path);
    __host__ __device__ double BenchMultiFunctionx10(double* path);
    __host__ __device__ double Klaster2(double* path);
    __host__ __device__ double Klaster2o(double* path);
    __host__ __device__ double Klaster2no(double* path);
    __host__ __device__ double Klaster2so(double* path);
    __host__ __device__ double Klaster2nso(double* path);
    __host__ __device__ double Klaster3(double* path);
    __host__ __device__ double Bench4(double* path);
    __host__ __device__ double Bench4x(double* path);
    __host__ __device__ double Bench4x1(double* path);
    __host__ __device__ double Bench4x2(double* path);
    __host__ __device__ double Bench4x3(double* path);
    __host__ __device__ double Bench4x4(double* path);
    __host__ __device__ double Bench4x22(double* path);
    __host__ __device__ double Bench4x222(double* path);
    __host__ __device__ double Bench4x2222(double* path);
    __host__ __device__ double Bench4xo2222(double* path);

private:
    double V = 0;
};

} // controller
