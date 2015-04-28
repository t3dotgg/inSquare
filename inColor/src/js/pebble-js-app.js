Pebble.addEventListener("ready",
  function(e) {
    console.log("PebbleKit JS ready!");
  }
);

Pebble.addEventListener("showConfiguration",
  function(e) {
    var options = JSON.parse(window.localStorage.getItem('options'));
    console.log('About to make the url!');
    //Load the settings page from inSquare.theo.website
    var url;
    if(options != null && options['KEY_HEX_COLOR'] != null){
      url = 'http://gregorybartell.com/pebble/index.html?' + 'mode=' + encodeURIComponent(options['KEY_MODE']) + '&btv=' + encodeURIComponent(options['KEY_BTV']) + '&hex_color=' + encodeURIComponent(options['KEY_HEX_COLOR']);
    }else{
      url = 'http://gregorybartell.com/pebble/index.html';
    }
    console.log(url);
    Pebble.openURL(url);
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
