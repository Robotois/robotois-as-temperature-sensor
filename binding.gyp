{
  "targets": [
    {
      "target_name": "TempSensor",
      "sources": [
        "src/lib/wrapper/TempSensor.cpp",
        "src/lib/wrapper/TempWrapper.cpp",
        "src/lib/TemperatureSensor/TemperatureSensor.cpp",
      ],
      "libraries": ["-l bcm2835", "-l rt"]
    }
  ]
}
