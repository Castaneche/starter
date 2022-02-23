#pragma once

#include <Util/Console.hpp>
#include <Util/Event.hpp>
#include <Util/NonCopyable.hpp>
#include <Util/StlStreams.hpp>
#include <Util/System.hpp>
#include <Util/Types.hpp>

#include <Util/Concurrency/Lock.hpp>
#include <Util/Concurrency/Mutex.hpp>
#include <Util/Concurrency/NamedMutex.hpp>
#include <Util/Concurrency/Spinlock.hpp>

#include <Util/Logging/Csv.hpp>
#include <Util/Logging/Log.hpp>
#include <Util/Logging/File.hpp>

#include <Util/Templates/RingBuffer.hpp>
#include <Util/Templates/Singleton.hpp>

#include <Util/Timing/Clock.hpp>
#include <Util/Timing/Frequency.hpp>
#include <Util/Timing/Time.hpp>
#include <Util/Timing/Timestamp.hpp>

// 3rd party includes
#include <fmt/format.h>
#include <fmt/printf.h>
#include <fmt/color.h>