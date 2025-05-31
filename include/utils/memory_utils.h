#ifndef MEMORY_UTILS_H
#define MEMORY_UTILS_H

#include <iostream>
#include <cstdlib>
#include "error_handling.h"

using namespace std;

// ========== Hàm cấp phát bộ nhớ an toàn ==========
template<typename T>
T* safeAllocate(size_t count = 1)
{
    T* ptr = static_cast<T*>(malloc(sizeof(T) * count));
    if (ptr == NULL)
    {
        displayError(ERROR_MEMORY_ALLOCATION, "Không thể cấp phát " + to_string(sizeof(T) * count) + " bytes");
        return NULL;
    }
    return ptr;
}

// ========== Hàm giải phóng bộ nhớ an toàn ==========
template<typename T>
void safeFree(T*& ptr)
{
    if (ptr != NULL)
    {
        free(ptr);
        ptr = NULL;
    }
}

// ========== Hàm cấp phát bộ nhớ với new (C++) ==========
template<typename T>
T* safeNew(size_t count = 1)
{
    try
    {
        if (count == 1)
        {
            return new T;
        }
        else
        {
            return new T[count];
        }
    }
    catch (const bad_alloc& e)
    {
        displayError(ERROR_MEMORY_ALLOCATION, "Không thể cấp phát bộ nhớ: " + string(e.what()));
        return NULL;
    }
}

// ========== Hàm giải phóng bộ nhớ với delete (C++) ==========
template<typename T>
void safeDelete(T*& ptr, bool isArray = false)
{
    if (ptr != NULL)
    {
        if (isArray)
        {
            delete[] ptr;
        }
        else
        {
            delete ptr;
        }
        ptr = NULL;
    }
}

// ========== Hàm kiểm tra và thông báo về trạng thái bộ nhớ ==========
void logMemoryOperation(const string& operation, const string& objectType, bool success)
{
    if (success)
    {
        displayInfo(operation + " " + objectType + " thành công");
    }
    else
    {
        displayError(ERROR_MEMORY_ALLOCATION, operation + " " + objectType + " thất bại");
    }
}

#endif // MEMORY_UTILS_H
