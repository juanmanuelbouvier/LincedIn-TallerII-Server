/*
 * DefaultHandler.cpp
 *
 *  Created on: 8 sep. 2016
 *      Author: tomi
 */

#include "DefaultHandler.h"

DefaultHandler::DefaultHandler() {

}

string DefaultHandler::handle(HTTPRequest* http_request){
	string mensaje = "\r\nContent-Type: text/html; charset=utf-8\r\n\r\n<!DOCTYPE html><html><body><h1>Linced In App Server</h1>\n"
						"<h3><b>Metod: </b>" 	+ http_request->getMethod() 	+ "</h3>\n"
						"<h3><b>URI: </b>" 		+ http_request->getURI() 	+ "</h3>\n"
						"<h3><b>QUERY: </b>"	+ http_request->getQuery() 	+ "</h3>\n"
						"<h3><b>BODY: </b>"		+ http_request->getBody() 	+ "</h3>\n"
						"<br/><br/> ========================================================================== <br/>"
						"Change Method of Form:"
						"<select onchange='changeMethod(this.value)'>"
							"<option value=\"GET\">GET</option>"
							"<option value=\"POST\">POST</option>"
							"<option value=\"PUT\">PUT</option>"
							"<option value=\"DELETE\">DELETE</option>"
						"</select>"
						"<br/>"
						"<p>CURRENT METHOD: <a id='current'>GET</a></p>"
						"<form id='myForm' action='/index' method='get'>"
						  "First name:<br>"
						  "<input type=\"text\" name=\"firstname\" value=\"Mickey\">"
						  "<br/>"
						  "Last name:<br>"
						  "<input type=\"text\" name=\"lastname\" value=\"Mouse\">"
						  "<br/><br/>"
						  "<input type=\"submit\" value=\"Submit\">"
						"</form>"
						"<script type='text/javascript'> function changeMethod(value){ document.getElementById('myForm').method = value; document.getElementById('current').innerHTML = value.toUpperCase(); }</script>"
						"</body></html>\n";
	return mensaje;
}

DefaultHandler::~DefaultHandler() {
	// TODO Auto-generated destructor stub
}

