#include <OpenCL/opencl.h>
#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>

#define DATA_SIZE 33554432

std::ifstream::pos_type filesize(const char *filename)
{
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);

    return in.tellg();
}

int main()
{
    cl_int status = CL_SUCCESS;
    cl_uint platform_count = 0;
    cl_platform_id *platforms = NULL;

    cl_platform_id platform = 0;

    if ((status = clGetPlatformIDs(0, NULL, &platform_count)) != CL_SUCCESS)
    {
        std::cout << "No platforms available" << std::endl;

        return 0;
    }

    if (!(platforms = (cl_platform_id *)malloc(sizeof(cl_platform_id) * platform_count)))
    {
        std::cout << "Memory allocation error" << std::endl;

        return 0;
    }

    if ((status = clGetPlatformIDs(platform_count, platforms, NULL)) != CL_SUCCESS)
    {
        std::cout << "Can't retreive platorms" << std::endl;

        return 0;
    }

    for (int i = 0; i < platform_count; ++i)
    {
        size_t platform_profile_size = 0;
        char *platform_profile = NULL;

        if ((status = clGetPlatformInfo(0, CL_PLATFORM_PROFILE, 0, NULL, &platform_profile_size)) !=
            CL_SUCCESS)
        {
            std::cout << "Can't retreive platform profile size" << std::endl;

            return 0;
        }

        if (!(platform_profile = (char *)malloc(sizeof(char) * platform_profile_size)))
        {
            std::cout << "Memory allocation error" << std::endl;

            return 0;
        }

        if ((status = clGetPlatformInfo(platforms[i], CL_PLATFORM_PROFILE, platform_profile_size,
                                        platform_profile, NULL)) != CL_SUCCESS)
        {
            std::cout << "Can't retreive platform profile info" << std::endl;

            return 0;
        }

        size_t platform_version_size = 0;
        char *platform_version = NULL;

        if ((status = clGetPlatformInfo(0, CL_PLATFORM_VERSION, 0, NULL, &platform_version_size)) !=
            CL_SUCCESS)
        {
            std::cout << "Can't retreive platform version size" << std::endl;

            return 0;
        }

        if (!(platform_version = (char *)malloc(sizeof(char) * platform_version_size)))
        {
            std::cout << "Memory allocation error" << std::endl;

            return 0;
        }

        if ((status = clGetPlatformInfo(platforms[i], CL_PLATFORM_VERSION, platform_version_size,
                                        platform_version, NULL)) != CL_SUCCESS)
        {
            std::cout << "Can't retreive platform version info" << std::endl;

            return 0;
        }

        size_t platform_name_size = 0;
        char *platform_name = NULL;

        if ((status = clGetPlatformInfo(0, CL_PLATFORM_NAME, 0, NULL, &platform_name_size)) !=
            CL_SUCCESS)
        {
            std::cout << "Can't retreive platform name size" << std::endl;

            return 0;
        }

        if (!(platform_name = (char *)malloc(sizeof(char) * platform_name_size)))
        {
            std::cout << "Memory allocation error" << std::endl;

            return 0;
        }

        if ((status = clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, platform_name_size,
                                        platform_name, NULL)) != CL_SUCCESS)
        {
            std::cout << "Can't retreive platform name info" << std::endl;

            return 0;
        }

        std::cout << "Found available platform: " << std::endl;
        std::cout << "\tName: " << platform_name << std::endl;
        std::cout << "\tVersion: " << platform_version << std::endl;
        std::cout << "\tProfile: " << platform_profile << std::endl;

        platform = platforms[i];
    }

    cl_uint device_count = 0;
    cl_device_id *devices = NULL;
    cl_device_id device;

    if ((status = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 0, NULL, &device_count)) !=
        CL_SUCCESS)
    {
        std::cout << "No devices available" << std::endl;

        return 0;
    }

    if (!(devices = (cl_device_id *)malloc(sizeof(cl_device_id))))
    {
        std::cout << "Memory allocation error" << std::endl;

        return 0;
    }

    if ((status = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, device_count, devices, NULL)) !=
        CL_SUCCESS)
    {
        std::cout << "Can't retreive devices" << std::endl;

        return 0;
    }

    for (int i = 0; i < device_count; ++i)
    {
        cl_uint device_compute_units_available = 0;

        if ((status = clGetDeviceInfo(devices[i], CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(cl_uint),
                                      &device_compute_units_available, NULL)) != CL_SUCCESS)
        {
            std::cout << "Can't retrive device compute units available" << std::endl;

            return 0;
        }

        size_t device_max_work_group_size = 0;

        if ((status = clGetDeviceInfo(devices[i], CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(size_t),
                                      &device_max_work_group_size, NULL)))
        {
            std::cout << "Can't retreive device max work group size" << std::endl;

            return 0;
        }

        size_t device_name_size = 0;
        char *device_name = NULL;

        if ((status = clGetDeviceInfo(devices[i], CL_DEVICE_NAME, 0, NULL, &device_name_size)) !=
            CL_SUCCESS)
        {
            std::cout << "Can't retreive device name size" << std::endl;

            return 0;
        }

        if (!(device_name = (char *)malloc(sizeof(char) * device_name_size)))
        {
            std::cout << "Memory allocation error" << std::endl;

            return 0;
        }

        if ((status = clGetDeviceInfo(devices[i], CL_DEVICE_NAME, device_name_size, device_name,
                                      NULL)) != CL_SUCCESS)
        {
            std::cout << "Can't retreive device name info" << std::endl;

            return 0;
        }

        cl_ulong max_buffer_size = 0;

        if ((status = clGetDeviceInfo(devices[i], CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE,
                                      sizeof(cl_ulong), &max_buffer_size, NULL)) != CL_SUCCESS)
        {
            std::cout << "Can't retreive max buffer size" << std::endl;

            return 0;
        }

        std::cout << "Found available GPU: " << std::endl;
        std::cout << "\tName: " << device_name << std::endl;
        std::cout << "\tMax compute units: " << device_compute_units_available << std::endl;
        std::cout << "\tMax work group size: " << device_max_work_group_size << std::endl;
        std::cout << "\tMax buffer size: " << max_buffer_size << std::endl;

        device = devices[i];
    }

    cl_context context;

    context = clCreateContext(
        NULL, 1, &device,
        [](const char *errinfo, const void *private_info, size_t cb, void *user_data)
        { std::cout << "Error occurred: " << errinfo << std::endl; },
        NULL, &status);

    if (status != CL_SUCCESS)
    {
        return 0;
    }

    cl_command_queue command_queue;

    command_queue = clCreateCommandQueue(context, device, 0, &status);

    if (status != CL_SUCCESS)
    {
        return 0;
    }

    std::cout << "Initializing data..." << std::endl;

    std::chrono::steady_clock::time_point start = std::chrono::high_resolution_clock::now();

    cl_mem a = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_HOST_WRITE_ONLY,
                              sizeof(float) * DATA_SIZE, NULL, &status);

    if (status != CL_SUCCESS)
    {
        std::cout << "1" << std::endl;

        return 0;
    }

    cl_mem b = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_HOST_WRITE_ONLY,
                              sizeof(float) * DATA_SIZE, NULL, &status);

    if (status != CL_SUCCESS)
    {
        std::cout << "2" << std::endl;

        return 0;
    }

    cl_mem c = clCreateBuffer(context, CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY,
                              sizeof(float) * DATA_SIZE, NULL, &status);

    if (status != CL_SUCCESS)
    {
        std::cout << "3" << std::endl;
        return 0;
    }

    std::vector<float> A(DATA_SIZE), B(DATA_SIZE), C(DATA_SIZE);

    for (int i = 0; i < DATA_SIZE; ++i)
    {
        A[i] = (float)i;
        B[i] = (float)i;
    }

    if ((status = clEnqueueWriteBuffer(command_queue, a, CL_TRUE, 0, sizeof(float) * DATA_SIZE,
                                       A.data(), 0, NULL, NULL)) != CL_SUCCESS)
    {
        std::cout << "4" << std::endl;
        return 0;
    }

    if ((status = clEnqueueWriteBuffer(command_queue, b, CL_TRUE, 0, sizeof(float) * DATA_SIZE,
                                       B.data(), 0, NULL, NULL)) != CL_SUCCESS)
    {
        std::cout << "5" << std::endl;
        return 0;
    }

    std::chrono::steady_clock::time_point end = std::chrono::high_resolution_clock::now();

    std::cout << "Initialized data in "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms "
              << std::endl;

    size_t size = filesize("src/kernels/vectors_addition.cl");

    char *data = (char *)malloc(sizeof(char) * size);

    std::ifstream kernel_src;

    kernel_src.open("src/kernels/vectors_addition.cl");

    kernel_src.read(data, size);

    cl_program program =
        clCreateProgramWithSource(context, 1, (const char **)&data, &size, &status);

    if (status != CL_SUCCESS)
    {
        return 0;
    }

    if ((status = clBuildProgram(program, 1, &device, NULL, NULL, NULL)) != CL_SUCCESS)
    {
        std::cout << "Build error" << std::endl;

        return 0;
    }

    cl_kernel kernel = clCreateKernel(program, "vector_add", &status);

    if (status != CL_SUCCESS)
    {
        return 0;
    }

    if ((status = clSetKernelArg(kernel, 0, sizeof(cl_mem), &a)) != CL_SUCCESS)
    {
        return 0;
    }

    if ((status = clSetKernelArg(kernel, 1, sizeof(cl_mem), &b)) != CL_SUCCESS)
    {
        return 0;
    }

    if ((status = clSetKernelArg(kernel, 2, sizeof(cl_mem), &c)) != CL_SUCCESS)
    {
        return 0;
    }

    size_t global_size = DATA_SIZE;
    size_t local_size = 64;

    std::cout << "Calculating the result..." << std::endl;

    start = std::chrono::high_resolution_clock::now();

    if ((status = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_size, &local_size,
                                         0, NULL, NULL)) != CL_SUCCESS)
    {
        return 0;
    }

    status = clFlush(command_queue);
    status = clFinish(command_queue);

    end = std::chrono::high_resolution_clock::now();

    if ((status = clEnqueueReadBuffer(command_queue, c, CL_TRUE, 0, sizeof(float) * DATA_SIZE,
                                      C.data(), 0, NULL, NULL)) != CL_SUCCESS)
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
