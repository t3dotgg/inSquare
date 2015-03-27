Pebble.addEventListener("ready",
  function(e) {
    console.log("PebbleKit JS ready!");
  }
);

Pebble.addEventListener("showConfiguration",
  function(e) {
    //Load the settings page from inSquare.theo.website
    Pebble.openURL("http://insquare.theo.website/PebbleSupport/index.html");
  }
);

Pebble.addEventListener("webviewclosed",
  function(e) {
  var configuration = JSON.parse(decodeURIComponent(e.response));
  console.log('Configuration window returned after a long, arduous journey. Data: ', JSON.stringify(configuration["mode"]));

      Pebble.sendAppMessage(
      {"KEY_MODE": configuration.mode},
      function(e) {
        console.log("Sending settings data...");
      },
      function(e) {
        console.log("Settings feedback failed!");
      }
    );
  }
);
