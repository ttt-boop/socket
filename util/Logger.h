#pragma once 

#include<string>
#include<fstream>

using namespace std;

namespace cc{
namespace util{

#define log_open(file) \
    Logger::instance()->open(file)

#define log_debug(format, ...) \
    Logger::instance()->log(Logger::DEBUG, __FILE__, __LINE__, format, ##__VA_ARGS__)

#define log_info(format, ...) \
    Logger::instance()->log(Logger::INFO, __FILE__, __LINE__, format, ##__VA_ARGS__)

#define log_error(format, ...) \
    Logger::instance()->log(Logger::ERROR, __FILE__, __LINE__, format, ##__VA_ARGS__)

#define log_warn(format, ...) \
    Logger::instance()->log(Logger::WARN, __FILE__, __LINE__, format, ##__VA_ARGS__)

#define log_fatal(format, ...) \
    Logger::instance()->log(Logger::FATAL, __FILE__, __LINE__, format, ##__VA_ARGS__)


class Logger
{
public:
    enum Level
    {
        DEBUG = 0,
        INFO,
        WARN,
        ERROR,
        FATAL,
        LEVEL_COUNT
    };
    static Logger * instance();
    void open(const string & filename);
    void close();
    void log(Level level, const char * file, int line, const char * fomat, ...);
    void level(Level level){ m_level = level; }
    void max(int bytes) { m_max = bytes; }
private:
    Level m_level;
    string m_filename;
    ofstream m_fout;
    int m_max;
    int m_len;
    static const char * s_level[LEVEL_COUNT];
    static Logger * m_instance;

private:
    Logger();
    ~Logger();
    void rotate();
};

} // namespace util
} // namespace cc

