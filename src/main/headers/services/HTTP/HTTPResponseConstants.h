#ifndef SRC_MAIN_HEADERS_SERVICES_HANDLERS_HTTPRESPONSECONSTANTS_H_
#define SRC_MAIN_HEADERS_SERVICES_HANDLERS_HTTPRESPONSECONSTANTS_H_

#include <string>

#define CODE_PERMISSION_DENIED 401
#define PHRASE_PERMISSION_DENIED "PERMISSION DENIED"

#define CODE_OK 200
#define PHRASE_OK "OK"

#define CODE_CREATE 201
#define PHRASE_CREATE "CREATE CORRECT"

#define CODE_UPDATE 200
#define PHRASE_UPDATE "UPDATE CORRECT"

#define CODE_DELETE 204
#define PHRASE_DELETE "DELETE CORRECT"

#define CODE_ACCEPTED 202
#define PHRASE_ACCEPTED "OK"

#define CODE_BREACH_PRECONDITIONS 400
#define PHRASE_BREACH_PRECONDITIONS "BREACH OF PRECONDITIONS"

#define CODE_NONEXISTEN 404
#define PHRASE_NONEXISTEN "BREACH OF PRECONDITIONS"

#define CODE_ALREADY_EXIST 408
#define PHRASE_ALREADY_EXIST "ALREADY EXIST"

#define CODE_BAD_REQUEST 400
#define PHRASE_BAD_REQUEST "BAD REQUEST"

#define CODE_UNEXPECTED_ERROR 500
#define PHRASE_UNEXPECTED_ERROR "UNEXPECTED ERROR"


static string phraseByCode(int code) {
	switch (code) {
		case CODE_PERMISSION_DENIED:
			return PHRASE_PERMISSION_DENIED;

		case CODE_OK:
			return PHRASE_OK;

		case CODE_CREATE:
			return PHRASE_CREATE;

		case CODE_DELETE:
			return PHRASE_DELETE;

		case CODE_ACCEPTED:
			return PHRASE_ACCEPTED;

		case CODE_NONEXISTEN:
			return PHRASE_NONEXISTEN;

		case CODE_ALREADY_EXIST:
			return PHRASE_ALREADY_EXIST;

		case CODE_BAD_REQUEST:
			return PHRASE_BAD_REQUEST;

		case CODE_UNEXPECTED_ERROR:
			return PHRASE_UNEXPECTED_ERROR;

		default:
			return "";
	}
}


static string phraseRFCByCode(int code) {
	switch (code) {
		case 401:
			return "Unauthorized";

		case 200:
			return "OK";

		case 201:
			return "Created";

		case 204:
			return "No Content";

		case 202:
			return "Accepted";

		case 404:
			return "Not Found";

		case 408:
			return "Request Time-out";

		case 400:
			return "Bad Request";

		case 500:
			return "Internal Server Error";

		default:
			return "";
	}
}

#endif /* SRC_MAIN_HEADERS_SERVICES_HANDLERS_HTTPRESPONSECONSTANTS_H_ */
