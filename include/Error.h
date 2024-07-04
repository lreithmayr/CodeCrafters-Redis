#ifndef REDIS_STARTER_CPP_INCLUDE_ERROR_H_
#define REDIS_STARTER_CPP_INCLUDE_ERROR_H_

#include <exception>

 class UnknownCmdException: public std::exception {
};

#endif //REDIS_STARTER_CPP_INCLUDE_ERROR_H_
