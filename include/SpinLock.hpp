// Copyright (c) 2022 by Sumra

#ifndef _SPIN_LOCK_HPP_
#define _SPIN_LOCK_HPP_

#include <iostream>
#include <mutex>
#include <atomic>
#include <thread>

namespace sumra {

//atomic spinlock with TAS
class SpinLock final {
public:
    using this_type = SpinLock;
    using atomic_type = std::atomic_flag;

public:
    SpinLock() = default;
    ~SpinLock() = default;

    SpinLock(const this_type&) = delete;
    SpinLock& operator=(const this_type&) = delete;
public:
    void lock() noexcept {
        for(;;) {
            //Atomically changes the state of a std::atomic_flag to set (true) 
            //and returns the value it held before.
            if (!m_lock.test_and_set()) {
                return;
            }

            //Provides a hint to the implementation to reschedule the execution of threads
            //allowing other threads to run.
            std::this_thread::yield();
        }
    }

    bool try_lock() noexcept {
        return !m_lock.test_and_set();
    }

    void unlock() noexcept
    {
        m_lock.clear();
    }

private:
    atomic_type m_lock {false};
};

// RAII for lock
// you can change it to a template class
class SpinLockGuard final {
public:
    using this_type = SpinLockGuard;
    using spin_lock_type = SpinLock;
public:
    SpinLockGuard(spin_lock_type& lock) noexcept 
        :m_lock(lock)
    {
        m_lock.lock();
    }

    ~SpinLockGuard() noexcept {
        m_lock.unlock();
    }

public:
    SpinLockGuard(const this_type&) = delete;
    SpinLockGuard& operator=(const this_type&) = delete;

private:
    spin_lock_type& m_lock;
};

}


#endif