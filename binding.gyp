{
  "targets": [
    {
      "variables": {
        "dht_verbose%": "false"
      },
      "target_name": "dht",
      "sources": [
        "src/dht11.cpp",
        "src/DHTxx.cpp",
      ],
      "include_dirs": [],
      "dependencies": [],
      
      "link_settings": {
        "libraries": [
          "-lwiringPi",
          "-lpthread"
        ]
                  },
      "conditions": [
        ["dht_verbose=='true'", {
          "defines": [ "VERBOSE" ]
        }]
      ]
    }
  ]
  }