# sl2json

Convert Lowrence SL2 files to streaming/newline-delimited JSON (ndjson)

- <http://www.lowrance.com/>
- <https://wiki.openstreetmap.org/wiki/SL2>
- <https://github.com/kmpm/node-sl2format> (very helpful additional field breakdown)
- <https://stackoverflow.com/q/52280751/1457051>
- <https://gitlab.com/hrbrmstr/arabia> (R package)

## Install (macOS homebrew)
```bash
brew install hrbrmstr/tap/sl2json
```

## Build

Just run `make`. There are no external dependencies outside the need for a C++ compiler. Compilation has been tested with both `gcc` and `clang` toolchains.
## Run

    $ ./sl2json some_sl2_file.sl2 > streaming_json_version_of_the_data.json

## Sample record

    {
      "channel": 2,
      "upperLimit": 0,
      "lowerLimit": 13.4,
      "waterDepth": 2.838,
      "keelDepth": 0.328084,
      "speedGps": 0,
      "temperature": 15.6947,
      "longitude": 4433309,
      "latitude": 7003054,
      "speedWater": 0,
      "track": 3.50811,
      "altitude": 333.202,
      "heading": 0,
      "headingValid": false,
      "altitudeValid": false,
      "gpsSpeedValid": false,
      "waterTempValid": false,
      "positionValid": false,
      "waterSpeedValid": false,
      "trackValid": false,
      "timeOffset": 1404539
    }
