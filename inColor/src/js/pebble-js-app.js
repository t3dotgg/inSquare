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

Pebble.addEventListener("webviewclosed", function(e) {
  console.log("configuration closed");
  if (e.response != '') {
    var options = JSON.parse(decodeURIComponent(e.response));
    console.log("storing options: " + JSON.stringify(options));
    window.localStorage.setItem('options', JSON.stringify(options));
    Pebble.sendAppMessage(options,
      function(e) {
          console.log("Sending settings data...");
        },
      function(e) {
          console.log("Settings feedback failed!");
        }
      );
  } else {
    console.log("no options received");
  }
});
