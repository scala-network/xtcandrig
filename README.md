# XTLandRig

XTLandRig is a high performance Stellite (XTL) CPU miner, with official support for Android.

<img src="https://i.imgur.com/MIAgTEd.png" width="619" >

#### Table of contents
* [Features](#features)
* [Download](#download)
* [Usage](#usage)
* [Algorithm variations](#algorithm-variations)
* [Other information](#other-information)
* [Donations](#donations)
* [Release checksums](#release-checksums)
* [Contacts](#contacts)

## Features
* High performance.
* Official Android support.
* Small Android executable, without dependencies.
* Armv7/Armv8 support.
* Support for backup (failover) mining server.
* keepalived support.
* Command line options compatible with cpuminer.
* Smart automatic CPU configuration.
* It's open source software.

## Download
* Binary releases: https://github.com/stellitecoin/xtlandrig/releases
* Git tree: https://github.com/stellitecoin/xtlandrig.git
  * Clone with `git clone https://github.com/stellitecoin/xtlandrig.git`.

### Options
```
  -o, --url=URL            URL of mining server
  -O, --userpass=U:P       username:password pair for mining server
  -u, --user=USERNAME      username for mining server
  -p, --pass=PASSWORD      password for mining server
  -t, --threads=N          number of miner threads
  -v, --av=N               algorithm variation, 0 auto select
  -k, --keepalive          send keepalived for prevent timeout (need pool support)
  -r, --retries=N          number of times to retry before switch to backup server (default: 5)
  -R, --retry-pause=N      time to pause between retries (default: 5)
      --cpu-affinity       set process affinity to CPU core(s), mask 0x3 for cores 0 and 1
      --cpu-priority       set process priority (0 idle, 2 normal to 5 highest)
      --no-huge-pages      disable huge pages support
      --no-color           disable colored output
      --variant            algorithm PoW variant
      --donate-level=N     donate level, default 5% (5 minutes in 100 minutes)
      --user-agent         set custom user-agent string for pool
  -B, --background         run the miner in the background
  -c, --config=FILE        load a JSON-format configuration file
  -l, --log-file=FILE      log all output to a file
  -S, --syslog             use system log for output messages
      --max-cpu-usage=N    maximum CPU usage for automatic threads mode (default 75)
      --safe               safe adjust threads and av settings for current CPU
      --nicehash           enable nicehash/xtlrig-proxy support
      --print-time=N       print hashrate report every N seconds
      --api-port=N         port for the miner API
      --api-access-token=T access token for API
      --api-worker-id=ID   custom worker-id for API
  -h, --help               display this help and exit
  -V, --version            output version information and exit
```

Also you can use configuration via config file, default **config.json**. You can load multiple config files and combine it with command line options.

## Algorithm variations
Since version 0.8.0.
* `--av=1` For CPUs with hardware AES.
* `--av=2` Lower power mode (double hash) of `1`.
* `--av=3` Software AES implementation.
* `--av=4` Lower power mode (double hash) of `3`.


### Maximum performance checklist
* Idle operating system.
* Do not exceed optimal thread count.
* Use modern CPUs with AES-NI instruction set.
* Try setup optimal cpu affinity.
* Enable fast memory (Large/Huge pages).

## Donations
* XTL: `Se3dRf8ZTUXKYivaTFU4KYczPcmMcwPZWEQ5HZmj3RRviFJ3w1mNhtgCWkn6VsnQcMBX1hyCUjZVuSo8X7yJTSYj1joP84WoT`
* BTC: `1P7ujsXeX7GxQwHNnJsRMgAdNkFZmNVqJT`

## Contacts
* support@stellite.cash
* [reddit](https://www.reddit.com/r/stellite)

## Copyrights

Copyright 2016-2018 XMRig                     <https://github.com/xmrig>, <support@xmrig.com>
Copyright 2018 StelliteCoin                     <https://github.com/stellitecoin>, <support@stellite.cash>
