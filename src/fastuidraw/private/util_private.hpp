/*!
 * \file util_private.hpp
 * \brief file util_private.hpp
 *
 * Copyright 2016 by Intel.
 *
 * Contact: kevin.rogovin@intel.com
 *
 * This Source Code Form is subject to the
 * terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with
 * this file, You can obtain one at
 * http://mozilla.org/MPL/2.0/.
 *
 * \author Kevin Rogovin <kevin.rogovin@intel.com>
 *
 */


#pragma once

#include <mutex>
#include <vector>
#include <fastuidraw/util/c_array.hpp>

namespace fastuidraw
{
  /*!
    Wrapper over mutex type so that we can replace
    mutex implementation easily.
   */
  class mutex:fastuidraw::noncopyable
  {
  public:
    void
    lock(void)
    {
      m_mutex.lock();
    }

    void
    unlock(void)
    {
      m_mutex.unlock();
    }

    bool
    try_lock(void)
    {
      return m_mutex.try_lock();
    }

  private:
    std::mutex m_mutex;
  };

  class dummy_mutex:fastuidraw::noncopyable
  {
  public:
    void
    lock(void) {}

    void
    unlock(void) {}

    bool
    try_lock(void) { return true; }
  };

  /*!
    Locks mutex on ctor and unlocks un dtor.
   */
  class autolock_mutex:fastuidraw::noncopyable
  {
  public:
    explicit
    autolock_mutex(mutex &m):
      m_mutex(m)
    {
      m_mutex.lock();
    }

    ~autolock_mutex()
    {
      m_mutex.unlock();
    }
  private:
    mutex &m_mutex;
  };

  template<typename T>
  c_array<T>
  make_c_array(std::vector<T> &p)
  {
    if(p.empty())
      {
        return c_array<T>();
      }
    else
      {
        return c_array<T>(&p[0], p.size());
      }
  }

  template<typename T>
  c_array<const T>
  make_c_array(const std::vector<T> &p)
  {
    if(p.empty())
      {
        return c_array<const T>();
      }
    else
      {
        return c_array<const T>(&p[0], p.size());
      }
  }

  template<typename T>
  c_array<T>
  const_cast_c_array(c_array<const T> p)
  {
    T *q;
    q = const_cast<T*>(p.c_ptr());
    return c_array<T>(q, p.size());
  }
}
