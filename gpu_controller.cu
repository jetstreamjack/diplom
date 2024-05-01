#include "gpu_controller.h"

namespace controller {
    __host__ __device__ void GpuController::InvokeClasterFunction(int funcNumber, double* path, double* res)
    {
        // double OF = 0;
        // switch (funcNumber)
        // {
        //     case 1:  OF = this->Klaster1(path); break;
        //     case 2:  OF = Klaster2(path); break;
        //     case 2001:  OF = Klaster2o(path); break;
        //     case 2002:  OF = Klaster2no(path); break;
        //     case 2003:  OF = Klaster2so(path); break;
        //     case 2004:  OF = Klaster2nso(path); break;
        //     case 3:  OF = Klaster3(path); break;
        //     //        case 401:  OF = Bench1(path); break;
        //     //        case 4019:  OF = Bench1m(path); break;
        //     case 404:  OF = Bench4(path); break;
        //     //        case 4049:  OF = Bench4m(path); break;
        //     case 4040:  OF = Bench4x(path); break;
        //     case 4041:  OF = Bench4x1(path); break;
        //     case 4042:  OF = Bench4x2(path); break;
        //     case 40442:  OF = Bench4x3(path); break;
        //     case 40443:  OF = Bench4x4(path); break;
        //     case 4043:  OF = Bench4x22(path); break;
        //     case 4044:  OF = Bench4x222(path); break;
        //     case 4045:  OF = Bench4x2222(path); break;
        //     case 40451:  OF = Bench4xo2222(path); break;
        //     //        case 410:  OF = Bench10(path); break;
        //     //        case 4109:  OF = Bench10(path); break;
        //     case 980:  OF = BenchRozenbrok(path); break;
        //     case 981:  OF = BenchMultiFunction(path); break;
        //     case 982:  OF = BenchBirdFunction(path); break;
        //     case 983:  OF = BenchShevefeliaFunction(path); break;
        //     case 9800:  OF = BenchRozenbrokx10(path); break;
        //     case 9810:  OF = BenchMultiFunctionx10(path); break;
        // }
        
        
    }

    __host__ __device__ void GpuController::Dude(int numFunc, double* path, double* res)
    {
        double OF = 0;
        switch (numFunc)
        {
            case 1:  OF = this->Klaster1(path); break;
            case 2:  OF = Klaster2(path); break;
            case 2001:  OF = Klaster2o(path); break;
            case 2002:  OF = Klaster2no(path); break;
            case 2003:  OF = Klaster2so(path); break;
            case 2004:  OF = Klaster2nso(path); break;
            case 3:  OF = Klaster3(path); break;
            //        case 401:  OF = Bench1(path); break;
            //        case 4019:  OF = Bench1m(path); break;
            case 404:  OF = Bench4(path); break;
            //        case 4049:  OF = Bench4m(path); break;
            case 4040:  OF = Bench4x(path); break;
            case 4041:  OF = Bench4x1(path); break;
            case 4042:  OF = Bench4x2(path); break;
            case 40442:  OF = Bench4x3(path); break;
            case 40443:  OF = Bench4x4(path); break;
            case 4043:  OF = Bench4x22(path); break;
            case 4044:  OF = Bench4x222(path); break;
            case 4045:  OF = Bench4x2222(path); break;
            case 40451:  OF = Bench4xo2222(path); break;
            //        case 410:  OF = Bench10(path); break;
            //        case 4109:  OF = Bench10(path); break;
            case 980:  OF = BenchRozenbrok(path); break;
            case 981:  OF = BenchMultiFunction(path); break;
            case 982:  OF = BenchBirdFunction(path); break;
            case 983:  OF = BenchShevefeliaFunction(path); break;
            case 9800:  OF = BenchRozenbrokx10(path); break;
            case 9810:  OF = BenchMultiFunctionx10(path); break;
        }
        *res = OF;
    }

    __host__ __device__ double GpuController::Klaster1(double* path)
    {
        double OF = 0;
        if (path[0] > 3)
        {
            OF += 10;
        }
        if (path[2] == 0)
        {
            OF *= 5;
        }
        if (path[4] == 0)
        {
            OF += 3;
        }
        return OF;
    }

    __host__ __device__ double GpuController::BenchRozenbrok(double* path)
    {
        double alf = 100;
        double OF = -alf * (path[1] - path[0] * path[0]) * (path[1] - path[0] * path[0]) - (1 - path[0]) * (1 - path[0])+2500;
        return OF;
    }

    __host__ __device__ double GpuController::BenchMultiFunction(double* path)
    {
        double OF = 0;
        //double OF = path[0] * Math.Sin(4 * Math.PI * path[0]) + path[1] * Math.Sin(4 * Math.PI * path[1])+5;
        return OF;
    }

    __host__ __device__ double GpuController::BenchBirdFunction(double* path)
    {
        double OF = 0;
        //double OF = -Math.Sin(path[0]) * Math.Exp((1 - Math.Cos(path[1])) * (1 - Math.Cos(path[1]))) - Math.Cos(path[1]) * Math.Exp((1 - Math.Sin(path[0])) * (1 - Math.Sin(path[0])) - (path[0] - path[1]) * (path[0] - path[1]));
        return OF;
    }

    __host__ __device__ double GpuController::BenchShevefeliaFunction(double* path)
    {
        double OF = 0;
        //double OF = -Math.Abs(path[0]) - Math.Abs(path[1]) - Math.Abs(path[0]) * Math.Abs(path[1])+120;
        return OF;
    }

    __host__ __device__ double GpuController::BenchRozenbrokx10(double* path)
    {
        double alf = 100;
        double x1 = path[0] * (path[1] + path[2] + path[3] + path[4] + path[5]);
        double x2 = path[6] * (path[7] + path[8] + path[9] + path[10] + path[11]);
        double OF = -alf * (x2 - x1 * x1) * (x2 - x1 * x1) - (1 - x1) * (1 - x1)+2500;
        return OF;
    }

    __host__ __device__ double GpuController::BenchMultiFunctionx10(double* path)
    {
        double OF = 0;
        double x1 = path[0] * (path[1] + path[2] + path[3] + path[4] + path[5]);
        double x2 = path[6] * (path[7] + path[8] + path[9] + path[10] + path[11]);
        //double OF = x1 * Math.Sin(4 * Math.PI * x1) + x2 * Math.Sin(4 * Math.PI * x2)+5;
        return OF;
    }
    __host__ __device__ double GpuController::Klaster2(double* path)
    {
        double OF = 0;
        OF = OF + (path[0] - path[1] + 2 * path[2] + path[3] + 2 * path[4]);
        OF = OF + 0.5 * path[5] - 0.12 * path[6] - path[7] + 80 * path[8] + 0.00001 * path[9];
        if (path[10] == V)
        {
            OF = OF + 20;
        }
        return OF;
    }

    __host__ __device__ double GpuController::Klaster2o(double* path)
    {
        double OF = 0;
        OF = OF + (path[4] - path[12] + 2 * path[2] + path[3] + 2 * path[5]);
        OF = OF + 0.5 * path[7] - 0.12 * path[10] - path[11] + 80 * path[0] + 0.00001 * path[6];
        if (path[1] == V)
        {
            OF = OF + 20;
        }
        return OF;
    }

    __host__ __device__ double GpuController::Klaster2no(double* path)
    {
        double OF = 0;
        OF = OF + (path[8] - path[0] + 2 * path[10] + path[9] + 2 * path[7]);
        OF = OF + 0.5 * path[5] - 0.12 * path[2] - path[1] + 80 * path[12] + 0.00001 * path[6];
        if (path[11] == V)
        {
            OF = OF + 20;
        }
        return OF;
    }

    __host__ __device__ double GpuController::Klaster2so(double* path)
    {
        double OF = 0;
        OF = OF + (path[5] - path[4] + 2 * path[7] + path[12] + 2 * path[3]);
        OF = OF + 0.5 * path[9] - 0.12 * path[6] - path[8] + 80 * path[10] + 0.00001 * path[11];
        if (path[1] == V)
        {
            OF = OF + 20;
        }
        return OF;
    }

    __host__ __device__ double GpuController::Klaster2nso(double* path)
    {
        double OF = 0;
        OF = OF + (path[12 - 5] - path[12 - 4] + 2 * path[12 - 7] + path[12 - 12] + 2 * path[12 - 3]);
        OF = OF + 0.5 * path[12 - 9] - 0.12 * path[12 - 6] - path[12 - 8] + 80 * path[12 - 10] + 0.00001 * path[12 - 11];
        if (path[12 - 1] == V)
        {
            OF = OF + 20;
        }
        return OF;
    }

    __host__ __device__ double GpuController::Klaster3(double* path)
    {
        double OF = 0;
        // OF = OF + (Math.Pow(path[0] - 4, 2) + Math.Cos(path[1]) + Math.Cos(Math.Exp(path[2])) + Math.Pow(path[3] - 10, 2) + 2 * path[4]);
        // OF = OF + 0.5 * path[5] - 0.12 * path[6] - path[7] + 80 * path[8] + 0.00001 * path[9];
        // OF = OF * 15;
        // if (path[10] == V)
        // {
        //     OF = OF + 20;
        // }
        return OF;
    }

    __host__ __device__ double GpuController::Bench4(double* path)
    {
        double OF = 0;
        // double a1 = Math.Pow(path[0], 2);
        // double a2 = Math.Pow(path[1], 2);
        // double a = 1 - (Math.Sqrt(a1 + a2) / Math.PI);
        // double OF = Math.Pow(Math.Cos(path[0]) * Math.Cos(path[1]) * Math.Exp(Math.Abs(a)), 2);
        return OF;
    }

    __host__ __device__ double GpuController::Bench4x(double* path)
    {
        double OF = 0;
        double p0 = path[0] + path[1];
        double p1 = path[2] + path[3];
        // double a1 = Math.Pow(p0, 2);
        // double a2 = Math.Pow(p1, 2);
        // double a = 1 - (Math.Sqrt(a1 + a2) / Math.PI);
        // double OF = Math.Pow(Math.Cos(p0) * Math.Cos(p1) * Math.Exp(Math.Abs(a)), 2);
        return OF;
    }

    __host__ __device__ double GpuController::Bench4x1(double* path)
    {
        double OF = 0;
        // double p0 = path[0] * path[1];
        // double p1 = path[2] * path[3];
        // double a1 = Math.Pow(p0, 2);
        // double a2 = Math.Pow(p1, 2);
        // double a = 1 - (Math.Sqrt(a1 + a2) / Math.PI);
        // double OF = Math.Pow(Math.Cos(p0) * Math.Cos(p1) * Math.Exp(Math.Abs(a)), 2);
        return OF;
    }

    __host__ __device__ double GpuController::Bench4x2(double* path)
    {
        double OF = 0;
        // double p0 = path[0] * (path[1] + path[2]);
        // double p1 = path[3] * (path[4] + path[5]);
        // double a1 = Math.Pow(p0, 2);
        // double a2 = Math.Pow(p1, 2);
        // double a = 1 - Math.Sqrt(a1 + a2) / Math.PI;
        // double OF = Math.Pow(Math.Cos(p0) * Math.Cos(p1) * Math.Exp(Math.Abs(a)), 2);
        return OF;
    }

    __host__ __device__ double GpuController::Bench4x3(double* path)
    {
        double OF = 0;
        double p0 = path[0] * (path[1] + path[2] + path[3]);
        double p1 = path[4] * (path[5] + path[6] + path[7]);
        // double a1 = Math.Pow(p0, 2);
        // double a2 = Math.Pow(p1, 2);
        // double a = 1 - Math.Sqrt(a1 + a2) / Math.PI;
        // double OF = Math.Pow(Math.Cos(p0) * Math.Cos(p1) * Math.Exp(Math.Abs(a)), 2);
        return OF;
    }

    __host__ __device__ double GpuController::Bench4x4(double* path)
    {
        double OF = 0;
        double p0 = path[0] * (path[1] + path[2] + path[3] + path[4]);
        double p1 = path[5] * (path[6] + path[7] + path[8] + path[9]);
        // double a1 = Math.Pow(p0, 2);
        // double a2 = Math.Pow(p1, 2);
        // double a = 1 - Math.Sqrt(a1 + a2) / Math.PI;
        // double OF = Math.Pow(Math.Cos(p0) * Math.Cos(p1) * Math.Exp(Math.Abs(a)), 2);
        return OF;
    }

    __host__ __device__ double GpuController::Bench4x22(double* path)
    {
        double OF = 0;
        double p0 = path[0] * (path[1] + path[2] + path[3]);
        double p1 = path[4] * (path[5] + path[6] + path[7]);
        // double a1 = Math.Pow(p0, 2);
        // double a2 = Math.Pow(p1, 2);
        // double a = 1 - Math.Sqrt(a1 + a2) / Math.PI;
        // double OF = Math.Pow(Math.Cos(p0) * Math.Cos(p1) * Math.Exp(Math.Abs(a)), 2);
        return OF;
    }

    __host__ __device__ double GpuController::Bench4x222(double* path)
    {
        double OF = 0;
        double p0 = path[0] * (path[1] + path[2] + path[3] + path[4]);
        double p1 = path[5] * (path[6] + path[7] + path[8] + path[9]);
        // double a1 = Math.Pow(p0, 2);
        // double a2 = Math.Pow(p1, 2);
        // double a = 1 - Math.Sqrt(a1 + a2) / Math.PI;
        // double OF = Math.Pow(Math.Cos(p0) * Math.Cos(p1) * Math.Exp(Math.Abs(a)), 2);
        return OF;
    }

    __host__ __device__ double GpuController::Bench4x2222(double* path)
    {
        double OF = 0;
        double p0 = path[0] * (path[1] + path[2] + path[3] + path[4] + path[5]);
        double p1 = path[6] * (path[7] + path[8] + path[9] + path[10] + path[11]);
        // double a1 = Math.Pow(p0, 2);
        // double a2 = Math.Pow(p1, 2);
        // double a = 1 - Math.Sqrt(a1 + a2) / Math.PI;
        // double OF = Math.Pow(Math.Cos(p0) * Math.Cos(p1) * Math.Exp(Math.Abs(a)), 2);
        return OF;
    }

    __host__ __device__ double GpuController::Bench4xo2222(double* path)
    {
        double OF = 0;
        double p0 = path[10] * (path[8] + path[6] + path[4] + path[2] + path[0]);
        double p1 = path[11] * (path[9] + path[7] + path[5] + path[3] + path[1]);
        // double a1 = Math.Pow(p0, 2);
        // double a2 = Math.Pow(p1, 2);
        // double a = 1 - Math.Sqrt(a1 + a2) / Math.PI;
        // double OF = Math.Pow(Math.Cos(p0) * Math.Cos(p1) * Math.Exp(Math.Abs(a)), 2);
        return OF;
    }
} //controller
