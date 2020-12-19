#include <stdio.h>
#include <curl/curl.h>

#define OFFSET_CONSTANT 3688

int main(void)
{
    CURL *curl;
    CURLcode res;
    
    const char *data = "data to send";

    struct curl_slist *list = NULL;
    curl = curl_easy_init();

    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, "https://content.dropboxapi.com/2/files/upload");
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");

        list = curl_slist_append(list, "Authorization: Bearer cpcxgT1ku8oAAAAAAAAAAV4V3OY-rhhIbF0wF-R6TH0tsWuuDnErOKWBfwzhYvm6");
        list = curl_slist_append(list, "Dropbox-API-Arg: {\"path\": \"/Homewor.txt\",\"mode\": \"add\",\"autorename\": true,\"mute\": false,\"strict_conflict\": false}");
        list = curl_slist_append(list, "Content-Type: application/octet-stream");

        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, 12L);

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
        res = curl_easy_perform(curl);

        printf("\n%u", res);
        curl_slist_free_all(list);
        curl_easy_cleanup(curl);
    }
    printf("\n");
}