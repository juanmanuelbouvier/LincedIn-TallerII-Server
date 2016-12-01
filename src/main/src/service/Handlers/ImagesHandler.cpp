#include <services/Handlers/ImagesHandler.h>
#include <model/Image.h>
#include <extern/json.h>
#include <services/HTTP/Message/HTTPMessageBuilder.h>
#include <utils/PathUtils.h>
#include <services/HTTP/HTTPResponseConstants.h>

using namespace std;

HTTPResponse* ImagesHandler::handle(HTTPRequest* http_request) {


	if (PathUtils::matchPathRegexp(http_request->getURI(),"/img/:id") && http_request->isGET()){
		map<string,string> path = PathUtils::routerParser(http_request->getURI(),"/img/:id");
		string id = path["id"];

		if (!Image::exist(id)){
			return ResponseBuilder::createErrorResponse(CODE_NONEXISTEN,"Imagen inexistente");
		}
		string base64 = Image::getBase64(id);
		string dataH = "data:image/jpeg;base64";

		Json::Value body;
		body["info"] = dataH;
		body["name"] = id;
		body["content"] = base64;

		return ResponseBuilder::createJsonResponse(CODE_OK,body);
	}

	return ResponseBuilder::createErrorResponse(CODE_BAD_REQUEST,PHRASE_BAD_REQUEST);
}
