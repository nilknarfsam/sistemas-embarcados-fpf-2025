const {
  OPCUAServer,
  Variant,
  DataType,
  StatusCodes
} = require("node-opcua");

const server = new OPCUAServer({
  port: 4840,
  resourcePath: "/UA/device/",
  buildInfo: {
    productName: "DeviceOPCUAServer",
    buildNumber: "1",
    buildDate: new Date()
  },
  allowAnonymous: true
});

let ldrValue = 0;
let tempValue = 0.0;
let humValue = 0.0;

server.initialize(() => {
  console.log("Inicializando endereço de memória OPC UA...");

  const addressSpace = server.engine.addressSpace;
  const namespace = addressSpace.getOwnNamespace();

  const deviceObj = namespace.addObject({
    organizedBy: addressSpace.rootFolder.objects,
    browseName: "Device"
  });

  namespace.addVariable({
    componentOf: deviceObj,
    nodeId: "ns=1;s=LDR",
    browseName: "LDR",
    dataType: "Int32",
    minimumSamplingInterval: 1000,
    value: {
      get: () => new Variant({ dataType: DataType.Int32, value: ldrValue }),
      set: (variant) => {
        ldrValue = variant.value;
        console.log("LDR atualizado:", ldrValue);
        return StatusCodes.Good;
      }
    }
  });

  namespace.addVariable({
    componentOf: deviceObj,
    nodeId: "ns=1;s=TEMP",
    browseName: "TEMP",
    dataType: "Float",
    minimumSamplingInterval: 1000,
    value: {
      get: () => new Variant({ dataType: DataType.Float, value: tempValue }),
      set: (variant) => {
        tempValue = variant.value;
        console.log("TEMP atualizado:", tempValue);
        return StatusCodes.Good;
      }
    }
  });

  namespace.addVariable({
    componentOf: deviceObj,
    nodeId: "ns=1;s=HUM",
    browseName: "HUM",
    dataType: "Float",
    minimumSamplingInterval: 1000,
    value: {
      get: () => new Variant({ dataType: DataType.Float, value: humValue }),
      set: (variant) => {
        humValue = variant.value;
        console.log("HUM atualizado:", humValue);
        return StatusCodes.Good;
      }
    }
  });

  server.start(() => {
    console.log("Servidor OPC UA pronto em opc.tcp://localhost:4840/UA/device/");
  });
});