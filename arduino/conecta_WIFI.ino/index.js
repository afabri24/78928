function getData()
{
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
        if (xhttp.readyState == XMLHttpRequest.DONE) {
           if (xhttp.status == 200) {
           console.log((xhttp.responseText));
           let json = JSON.parse(xhttp.responseText);
              console.log();
           
           let receivedMsg1 = json.temperatura;
           let receivedMsg2 = json.humedad;
           document.getElementById('temp').textContent = receivedMsg1;
           document.getElementById('temp').textContent = receivedMsg2;
           }
           else {
              console.log('error', xhttp);
           }
        }
    };
    xhttp.open("GET", "LED", true);
    xhttp.send();
}