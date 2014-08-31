char *consumer_key = "PuwsYiFuQyGsEJZ9hHofGQtW3";
char *consumer_secret = "9OqFOSLP6W93jACsChkEfi3PYp4XLlBjI6Ry5COCnyO6DWnGhR";
char *user_token = "620331547-x2XviwVplG1rawauTMgOKq4Mew4MyddEbGDCXnQ2";
char *user_secret = "mNKJFF7wlI2Um1XU5Y5cpS90Iq1uV0x8Zi4HfBbCZskTz";

struct Memory {
	char *memory;
	size_t size;
};

struct Memory chunk;

bool peerverify = true;
bool verbose = false;

char *tweet_url = "https://api.twitter.com/1.1/statuses/update.json";
char *home_feed_url = "https://api.twitter.com/1.1/statuses/home_timeline.json";