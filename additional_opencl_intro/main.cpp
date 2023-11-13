#include <CL/cl.h>
#include <iostream>
#include <vector>

void PrintDeviceInfo(cl_device_id device) {
    cl_int ret;
    char info[1024];
    size_t infoSize;
    cl_ulong ul_info;
    cl_uint ui_info;
    size_t work_sizes[3];

    // Получаем имя устройства
    ret = clGetDeviceInfo(device, CL_DEVICE_NAME, sizeof(info), info, &infoSize);
    if (ret == CL_SUCCESS) {
        std::cout << "Device Name: " << info << std::endl;
    }

    // Получаем версию OpenCL, поддерживаемую устройством
    ret = clGetDeviceInfo(device, CL_DEVICE_VERSION, sizeof(info), info, &infoSize);
    if (ret == CL_SUCCESS) {
        std::cout << "OpenCL Version: " << info << std::endl;
    }

    // Получаем максимальное количество вычислительных юнитов
    ret = clGetDeviceInfo(device, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(ui_info), &ui_info, &infoSize);
    if (ret == CL_SUCCESS) {
        std::cout << "Max Compute Units: " << ui_info << std::endl;
    }

    // Получаем максимальный размер рабочей группы
    ret = clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(size_t), &infoSize, &infoSize);
    if (ret == CL_SUCCESS) {
        std::cout << "Max Work Group Size: " << infoSize << std::endl;
    }

    // Получаем максимальное количество измерений рабочих элементов
    ret = clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof(ui_info), &ui_info, &infoSize);
    if (ret == CL_SUCCESS) {
        std::cout << "Max Work Item Dimensions: " << ui_info << std::endl;
    }

    // Получаем максимальные размеры рабочих элементов
    ret = clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_ITEM_SIZES, sizeof(work_sizes), work_sizes, &infoSize);
    if (ret == CL_SUCCESS) {
        std::cout << "Max Work Item Sizes: " << work_sizes[0] << " " << work_sizes[1] << " " << work_sizes[2] << std::endl;
    }

    // Получаем информацию о поддержке двойной точности
    ret = clGetDeviceInfo(device, CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE, sizeof(ui_info), &ui_info, &infoSize);
    if (ret == CL_SUCCESS) {
        std::cout << "Preferred Vector Width for Double: " << ui_info << std::endl;
    }

    // Получаем информацию о максимальном размере локальной памяти
    ret = clGetDeviceInfo(device, CL_DEVICE_LOCAL_MEM_SIZE, sizeof(ul_info), &ul_info, &infoSize);
    if (ret == CL_SUCCESS) {
        std::cout << "Local Memory Size: " << ul_info << " bytes" << std::endl;
    }

    // Получаем информацию о поддержке компилятора
    ret = clGetDeviceInfo(device, CL_DEVICE_COMPILER_AVAILABLE, sizeof(cl_bool), &ui_info, &infoSize);
    if (ret == CL_SUCCESS) {
        std::cout << "Compiler Available: " << (ui_info ? "Yes" : "No") << std::endl;
    }

    // Получаем информацию о поддержке линкера
    ret = clGetDeviceInfo(device, CL_DEVICE_LINKER_AVAILABLE, sizeof(cl_bool), &ui_info, &infoSize);
    if (ret == CL_SUCCESS) {
        std::cout << "Linker Available: " << (ui_info ? "Yes" : "No") << std::endl;
    }

    // Получаем информацию о поддержке расширений
    ret = clGetDeviceInfo(device, CL_DEVICE_EXTENSIONS, sizeof(info), info, &infoSize);
    if (ret == CL_SUCCESS) {
        std::cout << "Extensions: " << info << std::endl;
    }

    std::cout << std::endl;
}

int main() {
    cl_int ret;
    cl_uint numPlatforms;
    std::vector<cl_platform_id> platformIDs;

    ret = clGetPlatformIDs(0, nullptr, &numPlatforms);
    if (ret != CL_SUCCESS) {
        std::cerr << "Error getting the number of platforms." << std::endl;
        return 1;
    }

    if (numPlatforms == 0) {
        std::cerr << "No OpenCL platforms found." << std::endl;
        return 1;
    }

    platformIDs.resize(numPlatforms);
    ret = clGetPlatformIDs(numPlatforms, platformIDs.data(), nullptr);
    if (ret != CL_SUCCESS) {
        std::cerr << "Error getting platform IDs." << std::endl;
        return 1;
    }

    for (cl_uint i = 0; i < numPlatforms; i++) {
        cl_uint numDevices;
        std::vector<cl_device_id> deviceIDs;

        ret = clGetDeviceIDs(platformIDs[i], CL_DEVICE_TYPE_ALL, 0, nullptr, &numDevices);
        if (ret != CL_SUCCESS) {
            std::cerr << "Error getting the number of devices for platform " << i << std::endl;
            continue;
        }

        if (numDevices == 0) {
            std::cout << "No devices found for platform " << i << std::endl;
            continue;
        }

        deviceIDs.resize(numDevices);
        ret = clGetDeviceIDs(platformIDs[i], CL_DEVICE_TYPE_ALL, numDevices, deviceIDs.data(), nullptr);
        if (ret != CL_SUCCESS) {
                   std::cout << "Devices available on platform " << i << ":" << std::endl;
        }

        for (cl_uint j = 0; j < numDevices; j++) {
            std::cout << "Device " << j + 1 << " on platform " << i << ":" << std::endl;
            PrintDeviceInfo(deviceIDs[j]);
        }
    }

    return 0;
}
