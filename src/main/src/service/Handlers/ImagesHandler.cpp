#include <services/Handlers/ImagesHandler.h>
#include <model/Image.h>
#include <extern/json.h>
#include <services/HTTP/Message/HTTPMessageBuilder.h>
#include <utils/PathUtils.h>
#include <services/HTTP/HTTPResponseConstants.h>

#include <iostream>
#include <services/DB/DBManager.h>

using namespace std;

static const char reverse_table[128] = {
   64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
   64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
   64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 62, 64, 64, 64, 63,
   52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 64, 64, 64, 64, 64, 64,
   64,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
   15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 64, 64, 64, 64, 64,
   64, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
   41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 64, 64, 64, 64, 64
};

string base64_decode(const ::std::string &ascdata) {
   using ::std::string;
   string retval;
   const string::const_iterator last = ascdata.end();
   int bits_collected = 0;
   unsigned int accumulator = 0;

   for (string::const_iterator i = ascdata.begin(); i != last; ++i) {
      const int c = *i;
      if (::std::isspace(c) || c == '=') {
         // Skip whitespace and padding. Be liberal in what you accept.
         continue;
      }
      if ((c > 127) || (c < 0) || (reverse_table[c] > 63)) {
         throw ::std::invalid_argument("This contains characters not legal in a base64 encoded string.");
      }
      accumulator = (accumulator << 6) | reverse_table[c];
      bits_collected += 6;
      if (bits_collected >= 8) {
         bits_collected -= 8;
         retval += (char)((accumulator >> bits_collected) & 0xffu);
      }
   }
   return retval;
}

HTTPResponse* ImagesHandler::handle(HTTPRequest* http_request) {


	if (PathUtils::matchPathRegexp(http_request->getURI(),"/img/:id") && http_request->isGET()){
		map<string,string> path = PathUtils::routerParser(http_request->getURI(),"/img/:id");
		string id = path["id"];
		cout << id << endl;
		if (!Image::exist(id)){
			cout << DBManager::getDB("Image")->getAllKeys().toStyledString() << endl;
			return ResponseBuilder::createErrorResponse(CODE_NONEXISTEN,"Imagen inexistente");
		}
		string base64 = Image::getBase64(id);
		string dataH = "data:image/jpeg;base64,";

		Json::Value body;
		body["info"] = dataH;
		body["name"] = id;
		body["content"] = base64;
		ResponseBuilder::createJsonResponse(200,body);

	}

	return ResponseBuilder::createErrorResponse(CODE_BAD_REQUEST,PHRASE_BAD_REQUEST);
}
