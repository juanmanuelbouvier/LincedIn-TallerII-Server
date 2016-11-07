#include <model/Skill.h>
#include <list>

namespace std {

Skill::Skill(string name) {
	Json::Value skill = SharedServerAPI::getInstance()->getSkill(name);
	this->name = skill["name"];
	this->category = skill["category"];
	this->description = skill["description"];
}

Skill* Skill::create(Json::Value data){

	Json::FastWriter fastWriter;

	//TODO: Abstraer el response de esta clase. (deberia devolver un booleano o la Skill en JSON que creo)
	//TODO: Estaria bueno que no devuelva un puntero sino el objeto (borrar * en el metodo)

	//	Metodos Utiles de JSON:
	//		asString() convierte los valores "convertibles" (booleanos, string, enteros, flotantes) a string
	//		toStyledString() convierte el Json::Value en un string como si fuera el archivo
	//		isString() Verifica que el sea un string (tambien esta para cualquer tipo)
	HTTPResponse* response = SharedServerAPI::getInstance()->setSkill(
			fastWriter.write(data["name"]),
			fastWriter.write(data["description"]),
			fastWriter.write(data["category"])
			);

	if (response->getCode() == 200){
		return Skill(data["name"]);
	}
	return nullptr;
}

map<string,string> Skill::check( Json::Value data ) {
	map<string,string> errors;
	list<string> dataExpected = {"name","description","category"};
	for (int i = 0; i < dataExpected.size(); i++) {
		string expected = dataExpected[i];
		if ( data[expected] ) {
			if (!data[expected].isString()) {
				errors[expected] = "Invalid value of " + expected;
			}
		} else {
			errors[expected] = expected + " not found in data";
		}
	}
	return errors;
}

string Skill::getName(){
	return name;
}

string Skill::getDescription(){
	return description;
}

string Skill::getCategory(){
	return category;
}

void Skill::setName(string new_name){
	//TODO update in sharedServer
	name = new_name;
}
void Skill::setDescription(string new_description){
	//TODO update in sharedServer
	description = new_description;
}

void Skill::setCategory(string new_category){
	//TODO update in sharedServer
	category = new_category;
}

Skill::~Skill() {

}

} /* namespace std */
