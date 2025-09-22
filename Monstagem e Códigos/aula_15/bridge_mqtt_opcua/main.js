const mqtt = require("mqtt");
const {
  OPCUAClient,
  AttributeIds,
  DataType,
  StatusCodes,
  Variant
} = require("node-opcua");

const OPCUA_ENDPOINT = "opc.tcp://localhost:4840/UA/device/";
const MQTT_BROKER = "mqtt://localhost:1883";
const MQTT_TOPIC = "/device/sensores/";

async function startBridge() {
  // Conecta ao servidor OPC UA
  const opcuaClient = OPCUAClient.create({ endpointMustExist: false });
  await opcuaClient.connect(OPCUA_ENDPOINT);
  const session = await opcuaClient.createSession();
  console.log("Conectado ao servidor OPC UA!");

  // Função para escrever em um nó OPC UA
  async function writeNode(nodeId, value, dataType) {
    const nodeToWrite = {
      nodeId,
      attributeId: AttributeIds.Value,
      value: { value: new Variant({ dataType, value }) }
    };
    const statusCode = await session.write(nodeToWrite);
    if (statusCode === StatusCodes.Good) {
      console.log(`Valor ${value} escrito em ${nodeId}`);
    } else {
      console.log(`Falha ao escrever em ${nodeId}:`, statusCode.toString());
    }
  }

  // Conecta ao broker MQTT
  const mqttClient = mqtt.connect(MQTT_BROKER);

  mqttClient.on("connect", () => {
    console.log("Conectado ao broker MQTT!");
    mqttClient.subscribe(MQTT_TOPIC, (err) => {
      if (err) {
        console.error("Erro ao se inscrever no tópico:", err);
      } else {
        console.log(`Inscrito no tópico ${MQTT_TOPIC}`);
      }
    });
  });

  mqttClient.on("message", async (topic, message) => {
    try {
      const data = JSON.parse(message.toString());
      if (
        typeof data.ldr === "number" &&
        typeof data.temp === "number" &&
        typeof data.hum === "number"
      ) {
        await writeNode("ns=1;s=LDR", data.ldr, DataType.Int32);
        await writeNode("ns=1;s=TEMP", data.temp, DataType.Float);
        await writeNode("ns=1;s=HUM", data.hum, DataType.Float);
      } else {
        console.log("Mensagem JSON inválida:", data);
      }
    } catch (err) {
      console.error("Erro ao processar mensagem MQTT:", err);
    }
  });

  // Opcional: tratamento de encerramento
  process.on("SIGINT", async () => {
    console.log("Encerrando ponte...");
    await session.close();
    await opcuaClient.disconnect();
    mqttClient.end();
    process.exit(0);
  });
}

startBridge();