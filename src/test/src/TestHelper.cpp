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
