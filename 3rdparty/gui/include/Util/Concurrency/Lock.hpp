// MIT License
//
// Copyright (c) 2020 Mechatronics and Haptic Interfaces Lab - Rice University
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// Author(s): Evan Pezent (epezent@rice.edu)

#pragma once

#include <Util/NonCopyable.hpp>

namespace util {

//==============================================================================
// CLASS DECLARATIONS
//==============================================================================

/// Represents a lockable object (e.g. Mutex, NamedMutex, etc.)
class Lockable {
public:
    /// Virtual destructor
    virtual ~Lockable() {}

    /// Locks the Lockable
    virtual void lock() = 0;

    /// Unlocks the Lockable
    virtual void unlock() = 0;
};

/// RAII wrapper for automatically locking and unlocking Lockables
class Lock : NonCopyable {
public:
    /// Default contructor. The Lockable is automatically locked.
    Lock(Lockable& lockable);

    /// Destructor. The Lockable is automatically unlocked.
    ~Lock();

private:
    Lockable& lockable_;  ///< the lockable object
};

} // namespace util

