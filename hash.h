char *oauth_sign_hmac_sha1 (const char *m, const char *k);

char *oauth_sign_rsa_sha1 (const char *m, const char *k);

char *oauth_sign_hmac_sha1_raw (const char *m, const size_t ml, const char *k, const size_t kl);