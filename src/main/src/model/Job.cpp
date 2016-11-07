#include <model/Job.h>

using namespace std;

Job::Job(){
	date_since = "",
	date_to,company = "";
	position = new JobPosition("id");

}

Job::~Job() {
	delete position;
}

