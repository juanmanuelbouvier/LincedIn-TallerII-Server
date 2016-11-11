#include <exception/SkillException.h>
namespace std {

SkillException::SkillException(string message) {
	this->message = message;
}

} /* namespace std */
