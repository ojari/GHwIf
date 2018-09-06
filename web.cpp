/******************************************************************************
 * Copyright (C) 2018 Jari Ojanen
 ******************************************************************************/
#include "web.h"
#include <iostream>

size_t curl_write(void *buffer, size_t size, size_t nmemb, void *user_data)
{
    std::cout << "CURL: " << (char*)buffer << std::endl;
    
    return size * nmemb;
}

Web::Web()
{
    curl_global_init(CURL_GLOBAL_ALL);

    handle = curl_easy_init();
    
}

Web::~Web()
{
    if (handle != NULL)
	curl_easy_cleanup(handle);
    
    curl_global_cleanup();
}

void Web::read()
{
    if (handle == NULL) {
	std::cout << "CURL not initialized!" << std::endl;
	return;
    }

    CURLcode result;
    
    curl_easy_setopt(handle, CURLOPT_URL, "http://www.iltalehti.fi/index.html");
    curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, 1L);

    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, curl_write);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, NULL);

    result = curl_easy_perform(handle);
    if (result != CURLE_OK) {
	std::cout << "CURL ERROR: " << curl_easy_strerror(result) << std::endl;
    }
}