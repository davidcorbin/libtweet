/** \enum OAuthMethod
 * signature method to used for signing the request.
 */
 
#ifndef OAUTH_METHOD
#define OAUTH_METHOD
typedef enum {
    OA_HMAC=0, ///< use HMAC-SHA1 request signing method
    OA_RSA, ///< use RSA signature
    OA_PLAINTEXT ///< use plain text signature (for testing only)
 } OAuthMethod;
#endif


/**
 * calculate OAuth-signature for a given HTTP request URL, parameters and oauth-tokens.
 *
 * if 'postargs' is NULL a "GET" request is signed and the
 * signed URL is returned. Else this fn will modify 'postargs'
 * to point to memory that contains the signed POST-variables
 * and returns the base URL.
 *
 * both, the return value and (if given) 'postargs' need to be freed
 * by the caller.
 *
 * @param url The request URL to be signed. append all GET or POST
 * query-parameters separated by either '?' or '&' to this parameter.
 *
 * @param postargs This parameter points to an area where the return value
 * is stored. If 'postargs' is NULL, no value is stored.
 *
 * @param method specify the signature method to use. It is of type
 * \ref OAuthMethod and most likely \ref OA_HMAC.
 *
 * @param http_method The HTTP request method to use (ie "GET", "PUT",..)
 * If NULL is given as 'http_method' this defaults to "GET" when
 * 'postargs' is also NULL and when postargs is not NULL "POST" is used.
 *
 * @param c_key consumer key
 * @param c_secret consumer secret
 * @param t_key token key
 * @param t_secret token secret
 *
 * @return the signed url or NULL if an error occurred.
 *
 */
char *oauth_sign_url2 (const char *url, char **postargs,
  OAuthMethod method,
  const char *http_method, //< HTTP request method
  const char *c_key, //< consumer key - posted plain text
  const char *c_secret, //< consumer secret - used as 1st part of secret-key
  const char *t_key, //< token key - posted plain text in URL
  const char *t_secret //< token secret - used as 2st part of secret-key
  );



/**
 * splits the given url into a parameter array.
 * (see \ref oauth_serialize_url and \ref oauth_serialize_url_parameters for the reverse)
 * (see \ref oauth_split_post_paramters for a more generic version)
 *
 * @param url the url or query-string to parse; may be NULL
 * @param argv pointer to a (char *) array where the results are stored.
 *  The array is re-allocated to match the number of parameters and each
 *  parameter-string is allocated with strdup. - The memory needs to be freed
 *  by the caller.
 *
 * @return number of parameter(s) in array.
 */
int oauth_split_url_parameters(const char *url, char ***argv);




/**
 * splits the given url into a parameter array.
 * (see \ref oauth_serialize_url and \ref oauth_serialize_url_parameters for the reverse)
 *
 * @param url the url or query-string to parse.
 * @param argv pointer to a (char *) array where the results are stored.
 *  The array is re-allocated to match the number of parameters and each
 *  parameter-string is allocated with strdup. - The memory needs to be freed
 *  by the caller.
 * @param qesc  use query parameter escape (vs post-param-escape) - if set
 *        to 1 all '+' are treated as spaces ' '
 *
 * @return number of parameter(s) in array.
 */
int oauth_split_post_paramters(const char *url, char ***argv, short qesc);



/**
 * same as /ref oauth_sign_url
 * with the url already split into parameter array
 *
 * @param argcp pointer to array length int
 * @param argvp pointer to array values
 * (argv[0]="http://example.org:80/" argv[1]="first=QueryParamater" ..
 *  the array is modified: fi. oauth_ parameters are added)
 *  These arrays can be generated with /ref oauth_split_url_parameters
 *  or /ref oauth_split_post_paramters.
 *
 * @param postargs This parameter points to an area where the return value
 * is stored. If 'postargs' is NULL, no value is stored.
 *
 * @param method specify the signature method to use. It is of type
 * \ref OAuthMethod and most likely \ref OA_HMAC.
 *
 * @param http_method The HTTP request method to use (ie "GET", "PUT",..)
 * If NULL is given as 'http_method' this defaults to "GET" when
 * 'postargs' is also NULL and when postargs is not NULL "POST" is used.
 *
 * @param c_key consumer key
 * @param c_secret consumer secret
 * @param t_key token key
 * @param t_secret token secret
 *
 * @return the signed url or NULL if an error occurred.
 */
char *oauth_sign_array2 (int *argcp, char***argvp,
  char **postargs,
  OAuthMethod method,
  const char *http_method, //< HTTP request method
  const char *c_key, //< consumer key - posted plain text
  const char *c_secret, //< consumer secret - used as 1st part of secret-key
  const char *t_key, //< token key - posted plain text in URL
  const char *t_secret //< token secret - used as 2st part of secret-key
  );

/**
 * free array args
 *
 * @param argcp pointer to array length int
 * @param argvp pointer to array values to be xfree()d
 */
void oauth_free_array(int *argcp, char ***argvp);



/**
 * the back-end behind by /ref oauth_sign_array2.
 * however it does not serialize the signed URL again.
 * The user needs to call /ref oauth_serialize_url (oA)
 * and /ref oauth_free_array to do so.
 *
 * This allows one to split parts of the URL to be used for
 * OAuth HTTP Authorization header:
 * see http://oauth.net/core/1.0a/#consumer_req_param
 * the oauthtest2 example code does so.
 *
 *
 * @param argcp pointer to array length int
 * @param argvp pointer to array values
 * (argv[0]="http://example.org:80/" argv[1]="first=QueryParamater" ..
 *  the array is modified: fi. oauth_ parameters are added)
 *  These arrays can be generated with /ref oauth_split_url_parameters
 *  or /ref oauth_split_post_paramters.
 *
 * @param postargs This parameter points to an area where the return value
 * is stored. If 'postargs' is NULL, no value is stored.
 *
 * @param method specify the signature method to use. It is of type
 * \ref OAuthMethod and most likely \ref OA_HMAC.
 *
 * @param http_method The HTTP request method to use (ie "GET", "PUT",..)
 * If NULL is given as 'http_method' this defaults to "GET" when
 * 'postargs' is also NULL and when postargs is not NULL "POST" is used.
 *
 * @param c_key consumer key
 * @param c_secret consumer secret
 * @param t_key token key
 * @param t_secret token secret
 *
 * @return void
 *
 */
void oauth_sign_array2_process (int *argcp, char***argvp,
  char **postargs,
  OAuthMethod method,
  const char *http_method, //< HTTP request method
  const char *c_key, //< consumer key - posted plain text
  const char *c_secret, //< consumer secret - used as 1st part of secret-key
  const char *t_key, //< token key - posted plain text in URL
  const char *t_secret //< token secret - used as 2st part of secret-key
  );

/**
 * Escape 'string' according to RFC3986 and
 * http://oauth.net/core/1.0/#encoding_parameters.
 *
 * @param string The data to be encoded
 * @return encoded string otherwise NULL
 * The caller must free the returned string.
 */
char *oauth_url_escape(const char *string);

/**
 * build a url query string from an array.
 *
 * @param argc  the total number of elements in the array
 * @param start element in the array at which to start concatenating.
 * @param argv  parameter-array to concatenate.
 * @return url string needs to be freed by the caller.
 *
 */
char *oauth_serialize_url (int argc, int start, char **argv);

/**
 * encode query parameters from an array.
 *
 * @param argc the total number of elements in the array
 * @param start element in the array at which to start concatenating.
 * @param argv parameter-array to concatenate.
 * @param sep separator for parameters (usually "&")
 * @param mod - bitwise modifiers:
 *   1: skip all values that start with "oauth_"
 *   2: skip all values that don't start with "oauth_"
 *   4: double quotation marks are added around values (use with sep ", " for HTTP Authorization header).
 * @return url string needs to be freed by the caller.
 */
char *oauth_serialize_url_sep (int argc, int start, char **argv, char *sep, int mod);

/**
 * Parse RFC3986 encoded 'string' back to  unescaped version.
 *
 * @param string The data to be unescaped
 * @param olen unless NULL the length of the returned string is stored there.
 * @return decoded string or NULL
 * The caller must free the returned string.
 */
char *oauth_url_unescape(const char *string, size_t *olen);

void oauth_add_protocol(int *argcp, char ***argvp, OAuthMethod method, const char *c_key, const char *t_key);

/**
 * generate a random string between 15 and 32 chars length
 * and return a pointer to it. The value needs to be freed by the
 * caller
 *
 * @return zero terminated random string.
 */
char *oauth_gen_nonce();

/**
 * search array for parameter key.
 * @param argv length of array to search
 * @param argc parameter array to search
 * @param key key of parameter to check.
 *
 * @return FALSE (0) if array does not contain a parameter with given key, TRUE (1) otherwise.
 */
int oauth_param_exists(char **argv, int argc, char *key);

/**
 * add query parameter to array
 *
 * @param argcp pointer to array length int
 * @param argvp pointer to array values
 * @param addparam parameter to add (eg. "foo=bar")
 */
void oauth_add_param_to_array(int *argcp, char ***argvp, const char *addparam);

/**
 * returns plaintext signature for the given key.
 *
 * the returned string needs to be freed by the caller
 *
 * @param m message to be signed
 * @param k key used for signing
 * @return signature string
 */
char *oauth_sign_plaintext (const char *m, const char *k);

/**
 * url-escape strings and concatenate with '&' separator.
 * The number of strings to be concatenated must be
 * given as first argument.
 * all arguments thereafter must be of type (char *)
 *
 * @param len the number of arguments to follow this parameter
 *
 * @return pointer to memory holding the concatenated
 * strings - needs to be xfree(d) by the caller. or NULL
 * in case we ran out of memory.
 */
char *oauth_catenc(int len, ...);

/**
 * build a query parameter string from an array.
 *
 * This function is a shortcut for \ref oauth_serialize_url (argc, 1, argv).
 * It strips the leading host/path, which is usually the first
 * element when using oauth_split_url_parameters on an URL.
 *
 * @param argc the total number of elements in the array
 * @param argv parameter-array to concatenate.
 * @return url string needs to be freed by the caller.
 */
char *oauth_serialize_url_parameters (int argc, char **argv);

/**
 * Decode the base64 encoded string 'src' into the memory pointed to by
 * 'dest'.
 *
 * @param dest Pointer to memory for holding the decoded string.
 * Must be large enough to receive the decoded string.
 * @param src A base64 encoded string.
 * @return the length of the decoded string if decode
 * succeeded otherwise 0.
 */
int oauth_decode_base64(unsigned char *dest, const char *src);

/**
 * base64 encode digest, free it and return a URL parameter
 * with the oauth_body_hash. The returned hash needs to be freed by the
 * calling function. The returned string is not yet url-escaped and
 * thus suitable to be passed to \ref oauth_catenc.
 *
 * @param len length of the digest to encode
 * @param digest hash value to encode
 *
 * @return URL oauth_body_hash parameter string
 */
char *oauth_body_hash_encode(size_t len, unsigned char *digest);

/**
 * Base64 encode and return size data in 'src'. The caller must free the
 * returned string.
 *
 * @param size The size of the data in src
 * @param src The data to be base64 encode
 * @return encoded string otherwise NULL
 */
char *oauth_encode_base64(int size, const unsigned char *src);

/**
 * Base64 encode one byte
 */
char oauth_b64_encode(unsigned char u);

/**
 * Decode a single base64 character.
 */
unsigned char oauth_b64_decode(char c);

/**
 * Return TRUE if 'c' is a valid base64 character, otherwise FALSE
 */
int oauth_b64_is_base64(char c);

/**
 * string compare function for oauth parameters.
 *
 * used with qsort. needed to normalize request parameters.
 * see http://oauth.net/core/1.0/#anchor14
 */
int oauth_cmpstringp(const void *p1, const void *p2);

/**
 * same as \ref oauth_sign_hmac_sha1 but allows one
 * to specify length of message and key (in case they contain null chars).
 *
 * @param m message to be signed
 * @param ml length of message
 * @param k key used for signing
 * @param kl length of key
 * @return signature string.
 */
char *oauth_sign_hmac_sha1_raw (const char *m, const size_t ml, const char *k, const size_t kl);


/**
 * returns RSA-SHA1 signature for given data.
 * the returned signature needs to be freed by the caller.
 *
 * @param m message to be signed
 * @param k private-key PKCS and Base64-encoded
 * @return base64 encoded signature string.
 */
char *oauth_sign_rsa_sha1 (const char *m, const char *k);


/**
 * returns base64 encoded HMAC-SHA1 signature for
 * given message and key.
 * both data and key need to be urlencoded.
 *
 * the returned string needs to be freed by the caller
 *
 * @param m message to be signed
 * @param k key used for signing
 * @return signature string.
 */
char *oauth_sign_hmac_sha1 (const char *m, const char *k);
