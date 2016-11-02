#include <services/Handlers/UserHandler.h>
#include <extern/json.h>
#include <services/HTTP/Message/HTTPMessageBuilder.h>
#include <utils/PathUtils.h>

#include <string>

using namespace std;

UserHandler::UserHandler() {
}

//private methods
HTTPResponse* _response(int code,string conten_type, string body);
Json::Value _createJob(string from,string to, string company, string position);
Json::Value _createSkill(string name,string category, string description);
Json::Value _createEducation(string start,string end, string school, string degree);
Json::Value _createRecomendation(string recommender, string text);


HTTPResponse* UserHandler::handle(HTTPRequest* http_request){

	string method = http_request->getMethod();
	string query = http_request->getQuery();
	
	map<string,string> path = PathUtils::routerParser(http_request->getURI(),"/user/:user_id");

	if (method == "GET"){

		//si pidió un usuario que está en la base de datos
		if (true){

			Json::Value user;
			user["full_name"] = path["user_id"];
			user["first_name"] = "Carlos";
			user["last_name"] = "Fontela";
			user["email"] =  path["user_id"] + "@lincedin.com";
			user["date_of_birth‎"] = "1964-04-12 16:22:00";
			user["profile_picture"] = "https://cysingsoft.files.wordpress.com/2009/01/carlosfontela6.jpg?w=450";
			user["current_job"] = _createJob("2016-10-25 17:22:00","","FIUBA","Buscando ser el director del depto de computación.");

			user["skills"] = Json::arrayValue;
			user["skills"].append(_createSkill("Java","Lenguaje de programacion", "programacion champagne en java."));
			user["skills"].append(_createSkill("Patterns","Software design","programacion champagne con patrones que luego nadie puede usar."));

			user["past_jobs"] = Json::arrayValue;
			user["past_jobs"].append(_createJob("2010-10-25 16:22:00","2011-10-25 16:22:00","Totos","Gerente comercial"));
			user["past_jobs"].append(_createJob("2012-10-25 16:22:00","2016-10-25 16:22:00","FIUBA","Profesor"));

			user["education"] = Json::arrayValue;
			user["education"].append(_createEducation("1981-03-12 16:22:00","1990-12-12 23:22:00","FIUBA","Ingeniero en casi todo"));

			Json::Value recommendations_received(Json::arrayValue);
			user["recommendations_received"] = Json::arrayValue;
			user["recommendations_received"].append(_createRecomendation("Nico Paez", "Éste es un crack, se auto cita en las diapos."));

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

	} else if (method == "PUT"){

		return _response(500,"", "BAD REQUEST");

	} else if (method == "DELETE"){

		return _response(500,"", "BAD REQUEST");

	} else {
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

Json::Value _createJob(string from,string to, string company, string position){

	Json::Value job;
	job["from"] = from;
	if (to != "") {
		job["to"] = to;
	}
	job["company"] = company;
	job["position"] = position;

	return job;
}

Json::Value _createSkill(string name,string category, string description){

	Json::Value skill;
	skill["name"] = name;
	skill["category"] = category;
	skill["description"] = description;

	return skill;
}

Json::Value _createEducation(string start,string end, string school, string degree){

	Json::Value education;
	education["start_date"] = start;
	if (end != ""){
		education["end_date"] = end;
	}
	education["school_name"] = school;
	education["degree"] = degree;

	return education;
}

Json::Value _createRecomendation(string recommender, string text){

	Json::Value rec;
	rec["recommender"] = recommender; // proximamente un objeto del usuario
	rec["text"] = text;

	return rec;
}

UserHandler::~UserHandler(){
}
