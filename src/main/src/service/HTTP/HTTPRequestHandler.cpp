#include <services/HTTP/HTTPRequestHandler.h>
#include <services/Handlers/HelloWorldJsonHandler.h>
#include <services/Handlers/DefaultHandler.h>
#include <services/Handlers/SharedServerHandler.h>
#include <services/Handlers/UserHandler.h>
#include <services/Handlers/FriendHandler.h>
#include <services/Handlers/ChatHandler.h>
#include <services/Handlers/LoginHandler.h>
#include <services/Handlers/ImagesHandler.h>
#include <services/Handlers/RecommendationHandler.h>
#include <services/Handlers/GeolocalizationHandler.h>
#include <services/Handlers/SearchHandler.h>
#include <services/Logger/Logger.h>
#include <services/Access/AccessLog.h>
#include <utils/PathUtils.h>
#include <utils/TokenUtils.h>
#include <services/HTTP/HTTPResponseConstants.h>
#include <services/HTTP/Message/HTTPMessageBuilder.h>
#include <exception/AppServerException.h>
#include <exception>

#include <string>
#include <algorithm>

#include <iostream>

using namespace std;

#define NOT_FOUND "HTTPRequestHandler::NOTFOUND"

HTTPRequestHandler::HTTPRequestHandler() {
	// Inicialize all Handlers.
	count = 0;
	//Defaults
	DefaultHandler* defaultHandler = new DefaultHandler();
	addHandler("/"		,defaultHandler);

	//Shared
	SharedServerHandler* sharedHandler = new SharedServerHandler();
	vector<string> sharedGetURLS = sharedHandler->getKnowURLs();
	for ( string& url : sharedGetURLS ) {
		addHandler(url, sharedHandler);
	}

	addHandler("/img/:id", new ImagesHandler() );

	ChatHandler* chatHandler = new ChatHandler();
	addHandler("/chat", chatHandler );
	addHandler("/chat/online", chatHandler );
	addHandler("/chat/:chat_id", chatHandler );


	addHandler("/search", new SearchHandler());

	FriendHandler* friendHandler = new FriendHandler();
	addHandler("/friends",friendHandler);
	addHandler("/friends/:destination_user_id",friendHandler);
	addHandler("/friends/status/:user_id",friendHandler);

	UserHandler* userHandler = new UserHandler();
	addHandler("/user/:user_id", userHandler);
	addHandler("/user", userHandler);

	addHandler("/login", new LoginHandler());

	RecommendationHandler* recommendationHandler= new RecommendationHandler();
	addHandler("/recommendations", recommendationHandler);
	addHandler("/recommendations/:user_id", recommendationHandler);

	GeolocalizationHandler* geolocalizationHandler = new GeolocalizationHandler();
	addHandler("/geolocalization", geolocalizationHandler);
	addHandler("/geolocalization/:user_id", geolocalizationHandler);
}

HTTPResponse* HTTPRequestHandler::handle(HTTPRequest* http_request){
	count ++;
	Log("Request #" + to_string(count) + " " + http_request->getMethod() + " URI-> " + http_request->getURI(),INFO);
	string uri = http_request->getURI();

	if ( !isHandledRequest(http_request) ){
		Log("No Handler for endpoint = `" + uri + "` go to DefaultHandler",INFO);
		return HTTPEndPointsHandlers["/"]->handle(http_request);
	}
	string endpoint = matchPath(uri);
	LOG("Call handler of endpoint: " + endpoint,DEBUG);
	try {
		accessLog(http_request);
		Handler* handler = HTTPEndPointsHandlers[endpoint];
		if (endpoint == NOT_FOUND) {
			throw AppServerException("Can't handler endpoint.");

		}
		return handler->handle(http_request);
	} catch (AppServerException& e) {
		LOG("Unexpected Internal error in (\"" + endpoint + "\" handler) : " + e.what(),WARNING);
		return ResponseBuilder::createErrorResponse(CODE_UNEXPECTED_ERROR,"UNEXPECTED INTERNAL ERROR");
	} catch (exception& e) {
		LOG("Unexpected CPP Exception in (\"" + endpoint + "\" handler) : " + e.what(),WARNING);
		return ResponseBuilder::createErrorResponse(CODE_UNEXPECTED_ERROR,"UNEXPECTED INTERNAL ERROR");
	} catch (...) {
		LOG("Unexpected Error in (\"" + endpoint + "\" handler) :",WARNING);
		return ResponseBuilder::createErrorResponse(CODE_UNEXPECTED_ERROR,"UNEXPECTED INTERNAL ERROR");
	}
}

bool HTTPRequestHandler::isHandledRequest(HTTPRequest* http_request) {
	string uri = http_request->getURI();
	if (uri.empty() || matchPath(uri) != NOT_FOUND ){
		return true;
	}
	return false;
}

#include <iostream>

string HTTPRequestHandler::matchPath( string path ){
	for(string& aPath : workingPaths) {
	    if ( PathUtils::matchPathRegexp(path,aPath) ) {
	    	return aPath;
	    }
	}
	return NOT_FOUND;
}

void HTTPRequestHandler::registerPath( string path ) {
	workingPaths.push_back(path);
	sort(workingPaths.begin(), workingPaths.end());
}

bool HTTPRequestHandler::addHandler(string uri_path, Handler* handler) {
	map<string,string> headers;
	HTTPRequest theRequest("GET",uri_path,"","",headers);
	if (isHandledRequest(&theRequest) || uri_path == NOT_FOUND){
		return false;
	}
	registerPath(uri_path);
	HTTPEndPointsHandlers[uri_path] = handler;
	return true;
}

void HTTPRequestHandler::accessLog(HTTPRequest* http_request){
	Json::Value dataAccessLog;

	string token = http_request->getFromHeader("Authorization");
	if (!token.empty() and TokenUtils::isValidToken(token)){
		dataAccessLog["user_id"] = TokenUtils::userIDByToken(token);
	}

	AccessLog::accessLog(dataAccessLog);
}

HTTPRequestHandler::~HTTPRequestHandler() {
	vector<Handler*> toDelete;
	for(map<string,Handler*>::iterator it = HTTPEndPointsHandlers.begin(); it != HTTPEndPointsHandlers.end(); it++) {
		Handler* handler = it->second;
		if ( find(toDelete.begin(), toDelete.end(), handler) == toDelete.end() ) {
			toDelete.push_back(handler);
		}
	}
	for ( int i = 0; i < toDelete.size(); i++ ) {
		Handler* handler = toDelete[i];
		delete handler;
	}
	HTTPEndPointsHandlers.clear();
}

