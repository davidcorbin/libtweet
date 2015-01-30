twittercli
==========
As simple as `tweet "#twittercli is awesome!"`

Command line Twitter client built on libcurl


Install
==========
- Create an app and generate consumer/application keys at [apps.twitter.com](apps.twitter.com)
- Install libcurl (if you don't have it already)
- Run `make`
- Run `make install`


Usage
==========
Post Tweet: `tweet "This is my new status"`


Setup
==========
- Generate Twitter API keys
- Run `tweet setconsumerkey <CONSUMER KEY>`
- Run `tweet setconsumersecret <CONSUMER SECRET>`
- Run `tweet setusertoken <USER TOKEN>`
- Run `tweet setusersecret <USER SECRET>`


Future Plans
==========
- libtweet: a Twitter interface for your apps
- tweet daemon: background process for getting mentions/direct messages and alerting you
- Confirming support for more platforms