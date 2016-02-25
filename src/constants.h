#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace Command {
#if defined(Q_OS_WIN)
static const char *clearCmd = "cls";
#else
static const char *clearCmd = "clear";
#endif
}

#endif // CONSTANTS_H
