#include <exception/JobException.h>

namespace std {

JobException::JobException(string message) {
	this->message = message;
}

} /* namespace std */
