#include <OpenCL/opencl.h>
#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>

#include "opencl.hpp"

#define DATA_SIZE 33554432

std::ifstream::pos_type filesize(const char *filename)
{
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);

    return in.tellg();
}

int main()
{
    OpenCL opencl;
    cl_int status;

    try
    {
        opencl = std::move(OpenCL("src/kernels/vectors_addition.cl", "vector_add"));
    }
    catch (std::exception e)
    {
        std::cout << e.what() << std::endl;

        return -1;
    }

    cl_mem a = clCreateBuffer(opencl.get_context(), CL_MEM_READ_ONLY | CL_MEM_HOST_WRITE_ONLY,
                              sizeof(float) * DATA_SIZE, NULL, &status);

    if (status != CL_SUCCESS)
    {
        std::cout << "Buffer creation failed" << std::endl;

        return 0;
    }

    cl_mem b = clCreateBuffer(opencl.get_context(), CL_MEM_READ_ONLY | CL_MEM_HOST_WRITE_ONLY,
                              sizeof(float) * DATA_SIZE, NULL, &status);

    if (status != CL_SUCCESS)
    {
        std::cout << "Buffer creation failed" << std::endl;

        return 0;
    }

    cl_mem c = clCreateBuffer(opencl.get_context(), CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY,
                              sizeof(float) * DATA_SIZE, NULL, &status);

    if (status != CL_SUCCESS)
    {
        std::cout << "Buffer creation failed" << std::endl;

        return 0;
    }

    if ((status = clSetKernelArg(opencl.get_kernel(), 0, sizeof(cl_mem), &a)) != CL_SUCCESS)
    {
        return 0;
    }

    if ((status = clSetKernelArg(opencl.get_kernel(), 1, sizeof(cl_mem), &b)) != CL_SUCCESS)
    {
        return 0;
    }

    if ((status = clSetKernelArg(opencl.get_kernel(), 2, sizeof(cl_mem), &c)) != CL_SUCCESS)
    {
        return 0;
    }

    std::vector<float> A(DATA_SIZE), B(DATA_SIZE), C(DATA_SIZE);

    for (int i = 0; i < DATA_SIZE; ++i)
    {
        A[i] = (float)i;
        B[i] = (float)i;
    }

    if ((status = clEnqueueWriteBuffer(opencl.get_command_queue(), a, CL_TRUE, 0,
                                       sizeof(float) * DATA_SIZE, A.data(), 0, NULL, NULL)) !=
        CL_SUCCESS)
    {
        std::cout << "Buffer writing failed" << std::endl;

        return 0;
    }

    if ((status = clEnqueueWriteBuffer(opencl.get_command_queue(), b, CL_TRUE, 0,
                                       sizeof(float) * DATA_SIZE, B.data(), 0, NULL, NULL)) !=
        CL_SUCCESS)
    {
        std::cout << "Buffer writing failed" << std::endl;

        return 0;
    }

    size_t global_size = DATA_SIZE;
    size_t local_size = 64;

    std::cout << "Calculating the result..." << std::endl;

    std::chrono::high_resolution_clock::time_point start =
        std::chrono::high_resolution_clock::now();

    if ((status = clEnqueueNDRangeKernel(opencl.get_command_queue(), opencl.get_kernel(), 1, NULL,
                                         &global_size, &local_size, 0, NULL, NULL)) != CL_SUCCESS)
    {
        return 0;
    }

    status = clFlush(opencl.get_command_queue());
    status = clFinish(opencl.get_command_queue());

    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

    if ((status = clEnqueueReadBuffer(opencl.get_command_queue(), c, CL_TRUE, 0,
                                      sizeof(float) * DATA_SIZE, C.data(), 0, NULL, NULL)) !=
        CL_SUCCESS)
    {
        return 0;
    }

    for (int i = 0; i < 64; ++i)
    {
        std::cout << C[i] << " ";
    }

    std::cout << std::endl;

    std::cout << "Calculated the result in "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms "
              << std::endl;

    return 0;
}
