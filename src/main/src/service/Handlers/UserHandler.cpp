#include <services/Handlers/UserHandler.h>
#include <extern/json.h>
#include <services/HTTP/Message/HTTPMessageBuilder.h>
#include <utils/PathUtils.h>

#include <string>

using namespace std;

UserHandler::UserHandler() {
}

HTTPResponse* _response(int code,string conten_type, string body);

HTTPResponse* UserHandler::handle(HTTPRequest* http_request){

	string method = http_request->getMethod();
	string query = http_request->getQuery();
	
	map<string,string> path = PathUtils::routerParser(http_request->getURI(),"/:user_id");

	if (method == "GET"){

		//si pidió un usuario que está en la base de datos
		if (true){

			Json::Value user;
			user["name"] = path["user_id"];
			user["email"] =  path["user_id"] + "@lincedin.com";
			user["profile_picture"] = "https://cysingsoft.files.wordpress.com/2009/01/carlosfontela6.jpg?w=450";

			Json::Value current_job;
			current_job["from"] = "12-12-2012";
			current_job["to"] = "actualidad";
			current_job["company"] = "FIUBA";
			current_job["position"] = "Buscando ser el director del depto de computación.";
			user["current_job"] = current_job;

			Json::Value skills(Json::arrayValue);
			user["skills"] = skills;

			Json::Value skill1;
			skill1["name"] = "Java";
			skill1["category"] = "Lenguaje de programacion";
			skill1["description"] = "OJO, sabe java";

			Json::Value skill2;
			skill2["name"] = "Patterns";
			skill2["category"] = "Software design";
			skill2["description"] = "programacion champagne con patrones que luego nadie puede usar.";

			user["skills"].append(skill1);
			user["skills"].append(skill2);

			Json::Value past_jobs(Json::arrayValue);
			user["past_jobs"] = past_jobs;

			Json::Value job;
			job["from"] = "12-12-2014";
			job["to"] = "10-08-2015";
			job["company"] = "Totos";
			job["position"] = "Gerente comercial.";

			Json::Value job2;
			job2["from"] = "12-12-2015";
			job2["to"] = "10-08-2016";
			job2["company"] = "FIUBA";
			job2["position"] = "Profe.";

			user["past_jobs"].append(job);
			user["past_jobs"].append(job2);

			Json::FastWriter writer;
			writer.omitEndingLineFeed();
			string toReturn = writer.write(user);

			return _response(200,"application/json", toReturn);
		}
		//no hay usuario
		else {
			Json::Value error;
			error["Error"] = "Usuario inexistente";
			Json::FastWriter writer;
			writer.omitEndingLineFeed();
			string toReturn = writer.write(error);

			return _response(400,"application/json", toReturn);
		}

	}

	else {
		return _response(500,"", "BAD REQUEST");
	}
}

HTTPResponse* _response(int code,string conten_type, string body){
	ResponseBuilder* builder = new ResponseBuilder();
	builder = (ResponseBuilder*)builder->appendHeader("Content-type",conten_type);
	builder = (ResponseBuilder*)builder->setBody(body);
	builder = (ResponseBuilder*)builder->setCode(code);
	return builder->build();
}

UserHandler::~UserHandler(){
}
