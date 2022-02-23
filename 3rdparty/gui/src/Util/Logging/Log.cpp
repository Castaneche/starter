#include <Util/Logging/Log.hpp>

namespace util {

#ifdef MAHI_DEFAULT_LOG
    static ColorConsoleWriter<TxtFormatter> default_console_writer(Info);
    Logger<DEFAULT_LOGGER>* DLogger = &init_logger<DEFAULT_LOGGER>(Verbose, ".log", 256000, 10).add_writer(&default_console_writer);
#else
    Logger<DEFAULT_LOGGER>* DLogger = nullptr;
#endif

} // namespace util