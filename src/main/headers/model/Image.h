#ifndef SRC_MAIN_SRC_MODEL_IMAGE_H_
#define SRC_MAIN_SRC_MODEL_IMAGE_H_

#include <services/DB/DBManager.h>

using namespace std;

class Image {
private:
	static DB* getDB();
	static string getNextID();
	static bool amountMetadata(string last_id);
public:
	static string urlByBase64(string base64Image);
	static bool delet(string url);
};

#endif /* SRC_MAIN_SRC_MODEL_IMAGE_H_ */
