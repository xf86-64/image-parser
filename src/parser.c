#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <net/if.h>

#define ERR(s, err_code){fprintf(stderr, "%s\n", s); exit(err_code); }

static inline void CURLERR(const char* fmt, CURLcode res) {
	char* buf;
	sprintf(buf, fmt, curl_easy_strerror(res));
	ERR(buf, res);
}
static const char* url = NULL;

int main(int argc, char* argv[]) {
  if (argc > 1) 
  	url = argv[1];
  else
  {
  	ERR("please type image url", 1);
  }
  CURL* curl = curl_easy_init(); // init handle 
  CURLcode res;
  
  if(curl) {
	curl_easy_setopt(curl, CURLOPT_URL, url);
	res = curl_easy_perform(curl);

	if (res != CURLE_OK)
		CURLERR("curl_easy_perform() failed: %s\n", res);
	else {
		char* s;
		res = curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &s);
		if((res==CURLE_OK) && s)
			printf("data: %s\n", s);
	}
	curl_easy_cleanup(curl); // free an easy handle
  }
  else 
	ERR("failed to new descriptor(handle)", 1); 
  return 0;
}
