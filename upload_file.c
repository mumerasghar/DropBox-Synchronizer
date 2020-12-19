#include <stdio.h>
#include <curl/curl.h>
#include <sys/stat.h>
#include <fcntl.h>

char access_token[1024] =
    {"Authorization: Bearer cpcxgT1ku8oAAAAAAAAAAV4V3OY-rhhIbF0wF-R6TH0tsWuuDnErOKWBfwzhYvm6"};
char drp_api_arg[1024] =
    {"Dropbox-API-Arg: {\"path\": \"/Homewor.txt\",\"mode\": \"add\",\"autorename\": true,\"mute\": false,\"strict_conflict\": false}"};
char cnt_type[1024] =
    {"Content-Type: application/octet-stream"};

void set_request_props(CURL *curl, char *url, char *req_type, struct curl_slist *list)
{
    curl_easy_setopt(curl, CURLOPT_URL, url);                /* Set Url */
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, req_type); /* Request Type*/
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);        /* Request header*/
}

int upload_file()
{
    FILE *fd;
    CURL *curl;
    CURLcode res;
    struct stat file_info;
    struct curl_slist *list = NULL;
    curl_off_t speed_upload, total_time;

    char url[1024] =
        {"https://content.dropboxapi.com/2/files/upload"};

    fd = fopen("debugit.txt", "rb"); /* open file to upload */
    if (!fd)
        return 1; /*file not found*/

    if (fstat(fileno(fd), &file_info) != 0)
        return 1;

    curl = curl_easy_init();
    if (curl)
    {

        list = curl_slist_append(list, access_token);
        list = curl_slist_append(list, drp_api_arg);
        list = curl_slist_append(list, cnt_type);

        set_request_props(curl, url, "POST", list);

        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
        curl_easy_setopt(curl, CURLOPT_READDATA, fd);
        curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE,
                         (curl_off_t)file_info.st_size);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        curl_easy_cleanup(curl);
        curl_slist_free_all(list);
    }
    fclose(fd);
    return 0;
}

int main(void)
{
    upload_file();
}