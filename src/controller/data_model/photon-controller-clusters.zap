{
  "fileFormat": 2,
  "featureLevel": 107,
  "creator": "zap",
  "keyValuePairs": [
    {
      "key": "commandDiscovery",
      "value": "1"
    },
    {
      "key": "defaultResponsePolicy",
      "value": "always"
    },
    {
      "key": "manufacturerCodes",
      "value": "0x1002"
    }
  ],
  "package": [
    {
      "pathRelativity": "relativeToZap",
      "path": "../../app/zap-templates/zcl/zcl.json",
      "type": "zcl-properties",
      "category": "matter",
      "version": 1,
      "description": "Matter SDK ZCL data"
    },
    {
      "pathRelativity": "relativeToZap",
      "path": "../../app/zap-templates/app-templates.json",
      "type": "gen-templates-json",
      "category": "matter",
      "version": "chip-v1"
    }
  ],
  "endpointTypes": [
    {
      "id": 1,
      "name": "Anonymous Endpoint Type",
      "deviceTypeRef": {
        "code": 22,
        "profileId": 259,
        "label": "MA-rootdevice",
        "name": "MA-rootdevice",
        "deviceTypeOrder": 0
      },
      "deviceTypes": [
        {
          "code": 22,
          "profileId": 259,
          "label": "MA-rootdevice",
          "name": "MA-rootdevice",
          "deviceTypeOrder": 0
        }
      ],
      "deviceVersions": [
        1
      ],
      "deviceIdentifiers": [
        22
      ],
      "deviceTypeName": "MA-rootdevice",
      "deviceTypeCode": 22,
      "deviceTypeProfileId": 259,
      "clusters": [
        {
          "name": "Photon Smart",
          "code": 367524864,
          "mfgCode": null,
          "define": "PHOTON_SMART_CLUSTER",
          "side": "client",
          "enabled": 1
        },
        {
          "name": "Fresh Midea Air Conditioner Alarm",
          "code": 367524865,
          "mfgCode": null,
          "define": "FRESH_MIDEA_AC_ALARM_CLUSTER",
          "side": "client",
          "enabled": 1
        },
        {
          "name": "Fresh Refrigerator Errors Alarm",
          "code": 367524866,
          "mfgCode": null,
          "define": "FRESH_REFRIGERATOR_ERRORS_CLUSTER",
          "side": "client",
          "enabled": 1
        },
        {
          "name": "Fresh Refrigerator Controller",
          "code": 367524867,
          "mfgCode": null,
          "define": "FRESH_REFRIGERATOR_CONTROLLER_CLUSTER",
          "side": "client",
          "enabled": 1
        },
        {
          "name": "Fresh Midea Controller",
          "code": 367524868,
          "mfgCode": null,
          "define": "FRESH_MIDEA_CONTROLLER_CLUSTER",
          "side": "client",
          "enabled": 1
        }
      ]
    }
  ],
  "endpoints": [
    {
      "endpointTypeName": "Anonymous Endpoint Type",
      "endpointTypeIndex": 0,
      "profileId": 259,
      "endpointId": 1,
      "networkId": 0,
      "parentEndpointIdentifier": null
    }
  ]
}