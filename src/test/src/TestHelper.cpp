#include <TestHelper.h>
#include <fstream>
#include <string>
#include <iostream>
#include <settings/SettingManager.h>

using namespace std;

bool TestHelper::settinUpTestModel() {
	string json = "{\"db_folder\" : \".temp-test/\" , \"shared_server_url\": \"lincedin.herokuapp.com\"}\n";

	ofstream out(".temp-test/setting-model.json");
	out << json;
	out.close();

	return SettingManager::getInstance()->readFile(".temp-test/setting-model.json");
}

User TestHelper::createBasicUsers(string id){
	Json::Value data;
	data["id"] = id;
	data["first_name"] = id;
	data["last_name"] = "Apellido";
	data["email"] = id + "@lincedin.com";
	data["date_of_birth"] = "1964-04-12 16:22:00";
	data["password"] = "123456";

	User user = User::create(data);

	return user;
}


User TestHelper::createUser(string id) {

	Json::Value data;
	data["id"] = id;
	data["first_name"] = "Facundo";
	data["last_name"] = "Etchanchu";
	data["description"] = "Yo papá, quién si no.";
	data["email"] = "fme@lincedin.com";
	data["date_of_birth"] = "1964-04-12 16:22:00";
	data["password"] = "123456";
	data["education"] = Json::arrayValue;
	data["jobs"] = Json::arrayValue;
	data["skills"] = Json::arrayValue;

	Json::Value ed1;
	ed1["start_date"] = "1981-03-12 16:22:00";
	ed1["end_date"] = "1990-12-12 23:22:00";
	ed1["school_name"] = "FIUBA";
	ed1["degree"] = "Ingeniero en casi todo";
	data["education"].append(ed1);
	Json::Value ed2;
	ed2["start_date"] = "1990-03-12 16:22:00";
	ed2["end_date"] = "1994-12-12 23:22:00";
	ed2["school_name"] = "FIUBA";
	ed2["degree"] = "Ingeniero en lo que faltaba";
	data["education"].append(ed2);

	JobPosition job_p = JobPosition("project manager");

	Json::Value job;
	job["date_since"] = "2012-10-25 16:22:00";
	job["date_to"] = "2016-10-25 16:22:00";
	job["company"] = "FIUBA";
	job["position"] = job_p.asJSON();

	data["jobs"].append(job);

	Skill skill = Skill("Java");
	Skill skill2 = Skill("c");
	data["skills"].append(skill.asJSON());
	data["skills"].append(skill2.asJSON());


	return User::create(data);
}
