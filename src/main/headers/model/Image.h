#ifndef SRC_MAIN_SRC_MODEL_IMAGE_H_
#define SRC_MAIN_SRC_MODEL_IMAGE_H_

#include <services/DB/DBManager.h>
#define BASE_URL "/img/"

using namespace std;

/**
 * Image model object manage all image which were uploaded to the platform
 */
class Image {
private:
	static DB* getDB();
	static string getNextID();
	static bool amountMetadata(string last_id);
public:

	/**
	 * Store an imagen and generate url to get it (clients).
	 * @param A Base 64 image
	 * @return An urr/endpoint to get the image.
	 */
	static string urlByBase64(string base64Image);

	/**
	 * Get an imagen from id
	 * @param imagen id
	 * @return Base 64 image.
	 */
	static string getBase64(string id);

	/**
	 * Remove an image on database.
	 * @param url of the image to be removed
	 * @return True if it could be deleted
	 */
	static bool remove(string url);

	/**
	 * Check ff an image exists
	 * @param id of image
	 * @return True if exist
	 */
	static bool exist(string id);
};

#endif /* SRC_MAIN_SRC_MODEL_IMAGE_H_ */
