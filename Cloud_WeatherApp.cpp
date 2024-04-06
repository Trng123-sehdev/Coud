#include<iostream>
#include<string>
#include<cpprest/http_client.h>
#include<cpprest/filestream.h>

using namespace std;
using namespace std;
using namespace web;
using namespace web::http;
using namespace web::http::client;

int main() {
	cout << "\n******************************" << endl;
	cout << "\tWeather App"<<endl;
	cout << "\n********************************";
	cout << "\nEnter your city:";
	string city;
	getline(cin, city);
	http_client client(U("https://api.openweathermap.org/data/2.5"));
	uri_builder builder(U("/weather"));
	builder.append_query(U("q"), utility::conversions::to_string_t(city));
	builder.append_query(U("appid"), U("e43ab568174c3b89a67a5b983946e125"));
	http_request request(methods::GET);
	request.set_request_uri(builder.to_string());

	client.request(request).then([](http_response response) {
		return response.extract_json();
		}
	).then([](web::json::value body) {
			cout << "\tTemperature:" << body[U("main")][U("temp")].as_double() << "K" << endl;
			cout << "\tHumidity:" << body[U("main")][U("humidity")].as_double() << "%" << endl;
			cout << "\tWeather:" << utility::conversions::to_utf8string(body[U("weather")][0][U("main")].as_string());
		}
		).wait();

		return 0;

}