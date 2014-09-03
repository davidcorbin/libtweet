twittercli
==========
As simple as `tweet "#twittercli is awesome!"`

Command line Twitter client built with libcurl, liboauth, and libjson


Install
==========
- Create an app and generate consumer/application keys at apps.twitter.com
- Install libcurl, liboauth, libjson
- Run `make`
- Run `make install`


Usage
==========
Post Tweet: `tweet "This is my new status"`
View Feed: `tweet feed`
View Home Feed (Your tweets/retweets): `tweet feed home`
View Trends: `tweet trend`


Future Plans
==========
- libtweet: a Twitter interface for your apps
- tweet daemon: background process for getting mentions/direct messages and alerting you
- Confirming support for more platforms