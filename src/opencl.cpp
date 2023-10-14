#include <OpenCL/opencl.h>
#include <fstream>
#include <iostream>
#include <stdexcept>

class OpenCL
{
  public:
    OpenCL(const char *filename, const char *kernel_name) : status{0}
    {
        if ((status = clGetPlatformIDs(1, &platform_id, NULL)) != CL_SUCCESS)
        {
            throw std::runtime_error("No suitable platform found");
        }

        if ((status = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, 1, &device_id, NULL)))
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

        size_t filesize = get_filesize(filename);

        char *filedata = (char *)malloc(sizeof(char) * filesize);

        if (filedata == NULL)
        {
            clReleaseCommandQueue(command_queue);
            clReleaseContext(context);

            throw std::runtime_error("Memory allocation for filedata failed");
        }

        std::ifstream file(filename);

        file.read(filedata, filesize);

        program =
            clCreateProgramWithSource(context, 1, (const char **)&filedata, &filesize, &status);

        free(filedata);

        if (status != CL_SUCCESS)
        {
            clReleaseCommandQueue(command_queue);
            clReleaseContext(context);

            throw std::runtime_error("Program creation failed");
        }
    }

    ~OpenCL()
    {
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

    std::ifstream::pos_type get_filesize(const char *filename)
    {
        std::ifstream file(filename, std::ifstream::ate | std::ifstream::binary);

        return file.tellg();
    }
};
