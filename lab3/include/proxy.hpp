/* Proxy object.
 * @file
 * @date 2018-08-07
 * @author Anonymous
 */

#ifndef __PROXY_HPP__
#define __PROXY_HPP__

#include <mutex>
#include <memory> // Для std::lock_guard

template<class T, class MutexInjection = std::mutex>
class ptr_holder
{
public:
    ptr_holder(T* ptr): ptr_(ptr) {}

    //{ describe proxy object
    class proxy: private std::lock_guard<MutexInjection>
    {
    public:
        // Конструктор прокси:
        // 1. Вызывает конструктор базового класса std::lock_guard, который блокирует мьютекс.
        // 2. Сохраняет указатель для последующего доступа.
        proxy(T* ptr, MutexInjection& m):
            std::lock_guard<MutexInjection>(m),
            ptr_(ptr)
        {}

        // operator-> для прокси-объекта, возвращающий сырой указатель.
        // Это завершает "рекурсивную" цепочку вызовов.
        T* operator->() const
        {
            return ptr_;
        }

    private:
        T* ptr_;
    };

    // operator-> для ptr_holder, возвращающий наш прокси-объект.
    // Вызов этого оператора создает временный прокси-объект, который
    // живет до конца полного выражения (до точки с запятой).
    proxy operator -> () const
    {
        return proxy(ptr_, mutex_);
    }
    //}

private:
    T* ptr_;
    // `mutable` позволяет изменять мьютекс (lock/unlock) даже в константных методах.
    mutable MutexInjection mutex_;
};

#endif // __PROXY_HPP__