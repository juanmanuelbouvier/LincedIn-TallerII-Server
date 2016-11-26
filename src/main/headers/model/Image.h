#ifndef SRC_MAIN_SRC_MODEL_IMAGE_H_
#define SRC_MAIN_SRC_MODEL_IMAGE_H_

#include <services/DB/DBManager.h>
#define BASE_URL "/img/"

using namespace std;

class Image {
private:
	static DB* getDB();
	static string getNextID();
	static bool amountMetadata(string last_id);
public:

	//store image and return the corresponding url
	static string urlByBase64(string base64Image);

	static string getBase64(string id);

	static bool remove(string url);

	static bool exist(string id);
};

#endif /* SRC_MAIN_SRC_MODEL_IMAGE_H_ */
