// Create a client instance
client=new Paho.MQTT.Client("ip172-18-0-55-ch0kl5o1k7jg00e5ni5g-1883.direct.labs.play-with-docker.com", 9001, "afabri");
// set callback handlers
client.onConnectionLost=onConnectionLost;
client.onMessageArrived=onMessageArrived;
// connect the client
client.connect({onSuccess:onConnect});
// called when the client connects
function onConnect() {
  // Once a connection has been made, make a subscription and send a message.
  console.log("onConect");
  client.subscribe("World");
    message=new Paho.MQTT.Message("Hello");
  message=destinationName ="World";
  client.send (message);
}
// called when the client loses its connection
function onConnectionLost(responseobject) {
   if (responseObject.errorCode !== 0) {
     console.log("onConnectionLost:"+responseObject.errorMessage);
   }
}
// called when a message arrives
function onMessageArrived(message) {
    console.log("onMessageArrived:"+message.payloadString);
}
