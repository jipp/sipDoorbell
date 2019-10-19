#ifndef STATUS_CODE_HPP_
#define STATUS_CODE_HPP_

enum class StatusCode
{
    not_defined,
    TRYING = 100,
    RINGING = 180,
    SESSION_PROGRESS = 183,
    OK = 200,
    BAD_REQUEST = 400,
    UNAUTHORIZED = 401,
    NOT_FOUND = 404,
    REQUEST_TIMEOUT = 408,
    LOOP_DETECTED = 482,
    BUSY_HERE = 486,
    REQUEST_TERMINATED = 487,
    INTERNAL_SERVER_ERROR = 500,
    DECLINE = 603
};

#endif