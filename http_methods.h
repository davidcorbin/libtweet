extern struct Memory {
        char *memory;
        size_t size;
} chunk;

bool peerverify;

struct Memory post(char *url, char *url_enc_args);
struct Memory get(char *url);