#pragma once


/// <summary>
/// ´ã´ç : JH
/// Template Dynamic Singleton
/// 2022.02.07
/// </summary>
/// <typeparam name="T"></typeparam>

template < typename T >
class TemplateSingleton
{
protected:
    TemplateSingleton()
    {

    }
    virtual ~TemplateSingleton()
    {

    }

public:
    static T* GetInstance()
    {
        if (mpInstance == nullptr)
            mpInstance = new T;

        return mpInstance;
    };

    static void DestroyInstance()
    {
        if (mpInstance)
        {
            delete mpInstance;
            mpInstance = nullptr;
        }
    };

private:
    static T* mpInstance;
};

template <typename T> T* TemplateSingleton<T>::mpInstance = 0;