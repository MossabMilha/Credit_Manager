#include "Check_Email_2FA.h"
#include <stdio.h>
#include <string.h>
#include <curl/curl.h>

// Base64 encoding function for email data
void base64_encode(const char *input, char *output, int length) {
    const char *base64_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    int i, j = 0;
    for (i = 0; i < length; i += 3) {
        output[j++] = base64_table[(input[i] >> 2) & 0x3F];
        output[j++] = base64_table[((input[i] & 0x3) << 4) | ((input[i + 1] & 0xF0) >> 4)];
        if (i + 1 < length) {
            output[j++] = base64_table[((input[i + 1] & 0xF) << 2) | ((input[i + 2] & 0xC0) >> 6)];
            if (i + 2 < length) {
                output[j++] = base64_table[input[i + 2] & 0x3F];
            } else {
                output[j++] = '=';
            }
        } else {
            output[j++] = '=';
            output[j++] = '=';
        }
    }
    output[j] = '\0';
}

// Function to send an email
int send_email(const char *access_token, const char *to_email, const char *subject, const char *message) {
    CURL *curl;
    CURLcode res;

    // Create the raw message to send
    char raw_email[1024];
    snprintf(raw_email, sizeof(raw_email),
             "To: %s\n"
             "Subject: %s\n"
             "\n"
             "%s",
             to_email, subject, message);

    // Encode the message in base64
    char encoded_email[2048];
    base64_encode(raw_email, encoded_email, strlen(raw_email));

    // Prepare the JSON payload with the raw message (no JSON parsing library needed here)
    char payload[4096];
    snprintf(payload, sizeof(payload),
             "{\"raw\":\"%s\"}",
             encoded_email);

    // Initialize CURL
    curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "curl_easy_init() failed\n");
        return 1;
    }

    // Set CURL options
    struct curl_slist *headers = NULL;
    char auth_header[256];
    snprintf(auth_header, sizeof(auth_header), "Authorization: Bearer %s", access_token);

    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, auth_header);

    curl_easy_setopt(curl, CURLOPT_URL, "https://gmail.googleapis.com/gmail/v1/users/me/messages/send");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload);

    // Perform the request
    res = curl_easy_perform(curl);

    // Check for errors
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    } else {
        printf("Email sent successfully!\n");
    }

    // Cleanup
    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);

    return (res == CURLE_OK) ? 0 : 1;
}

void check_With_2FA(const char *email, const int *code) {
    const char *access_token = "ya29.a0AeDClZCZUgVNY7Ks9mpdVHHeBBzskjeyUSNq-kQUj0lQnfXtFdYxCkEZiyloGd7waa2102dkWv6j1Y24IjMXREhs95nFexCDW94z9b2sRJW08qD_R4fPmRyPmUlm2TTfOrhG5fs9DyF1gF1bzq8k-GBq71A0relhx1RX6jiyaCgYKAakSARMSFQHGX2Mik8Jh0UEzlQQFnlMmdwE6kw0175";
    const char *to_email = email;
    const char *subject = "Test Email";
    char message[256];
    snprintf(message, sizeof(message),
             "Dear User,\n"
             "Your verification code is: %d\n"
             "Please note that this code is valid for only 5 minutes. If you did not request this code, please ignore this email.\n"
             "Thank you,\n"
             "Your Credit Manager Team", code);

    send_email(access_token, to_email, subject, message);
}