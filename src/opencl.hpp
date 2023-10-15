#ifndef OPENCL_HPP
#define OPENCL_HPP

#include <OpenCL/opencl.h>
#include <fstream>
#include <iostream>
#include <stdexcept>

class OpenCL
{
  public:
    OpenCL()
        : status{0}, platform_id{0}, device_id{0}, context{0}, command_queue{0}, program{0}, kernel{
                                                                                                 0}
    {
    }
    OpenCL(const char *filename, const char *kernel_name) : OpenCL()
    {
        if ((status = clGetPlatformIDs(1, &platform_id, NULL)) != CL_SUCCESS)
        {
            throw std::runtime_error("No suitable platform found");
        }

        if ((status = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, 1, &device_id, NULL)) !=
            CL_SUCCESS)
        {
            throw std::runtime_error("No GPU found");
        }

        context = clCreateContext(
            NULL, 1, &device_id,
            [](const char *errinfo, const void *private_info, size_t cb, void *user_data)
            { std::cout << errinfo << std::endl; },
            NULL, &status);

        if (status != CL_SUCCESS)
        {
            throw std::runtime_error("Context creation failed");
        }

        command_queue = clCreateCommandQueue(context, device_id, 0, &status);

        if (status != CL_SUCCESS)
        {
            clReleaseContext(context);

            throw std::runtime_error("Command queue creationg failed");
        }

        size_t filesize = 0;
        char *filedata = NULL;

        if (read_file(filename, &filedata, &filesize))
        {
            throw std::runtime_error("Failed to read kernele source file");
        }

        program =
            clCreateProgramWithSource(context, 1, (const char **)&filedata, &filesize, &status);

        free(filedata);

        if (status != CL_SUCCESS)
        {
            clReleaseCommandQueue(command_queue);
            clReleaseContext(context);

            throw std::runtime_error("Program creation failed");
        }

        if ((status = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL)) != CL_SUCCESS)
        {
            clReleaseProgram(program);
            clReleaseCommandQueue(command_queue);
            clReleaseContext(context);

            throw std::runtime_error("Program building faield");
        }

        kernel = clCreateKernel(program, kernel_name, &status);

        if (status != CL_SUCCESS)
        {
            clReleaseProgram(program);
            clReleaseCommandQueue(command_queue);
            clReleaseContext(context);

            throw std::runtime_error("Kernel creation failed");
        }
    }

    OpenCL &operator=(OpenCL &&other)
    {
        if (this == &other)
        {
            return *this;
        }

        this->status = other.status;
        this->platform_id = other.platform_id;
        this->device_id = other.device_id;
        this->context = other.context;
        this->command_queue = other.command_queue;
        this->program = other.program;
        this->kernel = other.kernel;

        other.status = 0;
        other.platform_id = 0;
        other.device_id = 0;
        other.context = 0;
        other.command_queue = 0;
        other.program = 0;
        other.kernel = 0;

        return *this;
    }

    cl_context get_context() { return context; }
    cl_command_queue get_command_queue() { return command_queue; }
    cl_program get_program() { return program; }
    cl_kernel get_kernel() { return kernel; }

    ~OpenCL()
    {
        clReleaseKernel(kernel);
        clReleaseProgram(program);
        clReleaseCommandQueue(command_queue);
        clReleaseContext(context);
    }

  private:
    cl_int status;
    cl_platform_id platform_id;
    cl_device_id device_id;
    cl_context context;
    cl_command_queue command_queue;
    cl_program program;
    cl_kernel kernel;

    std::ifstream::pos_type get_filesize(const char *filename)
    {
        std::ifstream file(filename, std::ifstream::ate | std::ifstream::binary);

        return file.tellg();
    }

    int read_file(const char *filename, char **filedata, size_t *filesize)
    {
        *filesize = get_filesize(filename);

        if ((*filedata = (char *)malloc(sizeof(char) * *filesize)) == NULL)
        {
            return 1;
        }

        std::ifstream file(filename);

        file.read(*filedata, *filesize);

        return 0;
    }
};

// cl_int status = CL_SUCCESS;
//     cl_uint platform_count = 0;
//     cl_platform_id *platforms = NULL;
//
//     cl_platform_id platform = 0;
//
//     if ((status = clGetPlatformIDs(0, NULL, &platform_count)) != CL_SUCCESS)
//     {
//         std::cout << "No platforms available" << std::endl;
//
//         return 0;
//     }
//
//     if (!(platforms = (cl_platform_id *)malloc(sizeof(cl_platform_id) * platform_count)))
//     {
//         std::cout << "Memory allocation error" << std::endl;
//
//         return 0;
//     }
//
//     if ((status = clGetPlatformIDs(platform_count, platforms, NULL)) != CL_SUCCESS)
//     {
//         std::cout << "Can't retreive platorms" << std::endl;
//
//         return 0;
//     }
//
//     for (int i = 0; i < platform_count; ++i)
//     {
//         size_t platform_profile_size = 0;
//         char *platform_profile = NULL;
//
//         if ((status = clGetPlatformInfo(0, CL_PLATFORM_PROFILE, 0, NULL, &platform_profile_size))
//         !=
//             CL_SUCCESS)
//         {
//             std::cout << "Can't retreive platform profile size" << std::endl;
//
//             return 0;
//         }
//
//         if (!(platform_profile = (char *)malloc(sizeof(char) * platform_profile_size)))
//         {
//             std::cout << "Memory allocation error" << std::endl;
//
//             return 0;
//         }
//
//         if ((status = clGetPlatformInfo(platforms[i], CL_PLATFORM_PROFILE, platform_profile_size,
//                                         platform_profile, NULL)) != CL_SUCCESS)
//         {
//             std::cout << "Can't retreive platform profile info" << std::endl;
//
//             return 0;
//         }
//
//         size_t platform_version_size = 0;
//         char *platform_version = NULL;
//
//         if ((status = clGetPlatformInfo(0, CL_PLATFORM_VERSION, 0, NULL, &platform_version_size))
//         !=
//             CL_SUCCESS)
//         {
//             std::cout << "Can't retreive platform version size" << std::endl;
//
//             return 0;
//         }
//
//         if (!(platform_version = (char *)malloc(sizeof(char) * platform_version_size)))
//         {
//             std::cout << "Memory allocation error" << std::endl;
//
//             return 0;
//         }
//
//         if ((status = clGetPlatformInfo(platforms[i], CL_PLATFORM_VERSION, platform_version_size,
//                                         platform_version, NULL)) != CL_SUCCESS)
//         {
//             std::cout << "Can't retreive platform version info" << std::endl;
//
//             return 0;
//         }
//
//         size_t platform_name_size = 0;
//         char *platform_name = NULL;
//
//         if ((status = clGetPlatformInfo(0, CL_PLATFORM_NAME, 0, NULL, &platform_name_size)) !=
//             CL_SUCCESS)
//         {
//             std::cout << "Can't retreive platform name size" << std::endl;
//
//             return 0;
//         }
//
//         if (!(platform_name = (char *)malloc(sizeof(char) * platform_name_size)))
//         {
//             std::cout << "Memory allocation error" << std::endl;
//
//             return 0;
//         }
//
//         if ((status = clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, platform_name_size,
//                                         platform_name, NULL)) != CL_SUCCESS)
//         {
//             std::cout << "Can't retreive platform name info" << std::endl;
//
//             return 0;
//         }
//
//         std::cout << "Found available platform: " << std::endl;
//         std::cout << "\tName: " << platform_name << std::endl;
//         std::cout << "\tVersion: " << platform_version << std::endl;
//         std::cout << "\tProfile: " << platform_profile << std::endl;
//
//         platform = platforms[i];
//     }
//
//     cl_uint device_count = 0;
//     cl_device_id *devices = NULL;
//     cl_device_id device;
//
//     if ((status = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 0, NULL, &device_count)) !=
//         CL_SUCCESS)
//     {
//         std::cout << "No devices available" << std::endl;
//
//         return 0;
//     }
//
//     if (!(devices = (cl_device_id *)malloc(sizeof(cl_device_id))))
//     {
//         std::cout << "Memory allocation error" << std::endl;
//
//         return 0;
//     }
//
//     if ((status = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, device_count, devices, NULL)) !=
//         CL_SUCCESS)
//     {
//         std::cout << "Can't retreive devices" << std::endl;
//
//         return 0;
//     }
//
//     for (int i = 0; i < device_count; ++i)
//     {
//         cl_uint device_compute_units_available = 0;
//
//         if ((status = clGetDeviceInfo(devices[i], CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(cl_uint),
//                                       &device_compute_units_available, NULL)) != CL_SUCCESS)
//         {
//             std::cout << "Can't retrive device compute units available" << std::endl;
//
//             return 0;
//         }
//
//         size_t device_max_work_group_size = 0;
//
//         if ((status = clGetDeviceInfo(devices[i], CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(size_t),
//                                       &device_max_work_group_size, NULL)))
//         {
//             std::cout << "Can't retreive device max work group size" << std::endl;
//
//             return 0;
//         }
//
//         size_t device_name_size = 0;
//         char *device_name = NULL;
//
//         if ((status = clGetDeviceInfo(devices[i], CL_DEVICE_NAME, 0, NULL, &device_name_size)) !=
//             CL_SUCCESS)
//         {
//             std::cout << "Can't retreive device name size" << std::endl;
//
//             return 0;
//         }
//
//         if (!(device_name = (char *)malloc(sizeof(char) * device_name_size)))
//         {
//             std::cout << "Memory allocation error" << std::endl;
//
//             return 0;
//         }
//
//         if ((status = clGetDeviceInfo(devices[i], CL_DEVICE_NAME, device_name_size, device_name,
//                                       NULL)) != CL_SUCCESS)
//         {
//             std::cout << "Can't retreive device name info" << std::endl;
//
//             return 0;
//         }
//
//         cl_ulong max_buffer_size = 0;
//
//         if ((status = clGetDeviceInfo(devices[i], CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE,
//                                       sizeof(cl_ulong), &max_buffer_size, NULL)) != CL_SUCCESS)
//         {
//             std::cout << "Can't retreive max buffer size" << std::endl;
//
//             return 0;
//         }
//
//         std::cout << "Found available GPU: " << std::endl;
//         std::cout << "\tName: " << device_name << std::endl;
//         std::cout << "\tMax compute units: " << device_compute_units_available << std::endl;
//         std::cout << "\tMax work group size: " << device_max_work_group_size << std::endl;
//         std::cout << "\tMax buffer size: " << max_buffer_size << std::endl;
//
//         device = devices[i];
//     }

#endif
