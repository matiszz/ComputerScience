
// *********************************************************************
// Global variables
// *********************************************************************

// Viewer state.
var gamePaused = true;
var gamePreview = false; // If true, render will be called for the next tick even if game is paused, and then will be set to false.
var gameAnim = true;
var gameDirection = 1;
var actRound = 0; // Current round index.


// Data.
var raw_data_str; // String for storing the raw data.
var dataLoaded = false; // Set to true when raw_data_str is ready to be parsed.
var data = { } // Object for storing all the game data.


// Animation.
var speed = 10; // Ticks per second.
var FRAMES_PER_ROUND = 2;
var frames = 0; // Incremented each tick, when it reaches FRAMES_PER_ROUND, actRound is updated (acording to gameDirection).


// Visuals.
var unitSize = 0.6; // 1 = same size as tile.
var unitLineWidth = 2;
var grid_color = "#000000";


var cell_colors = {
  '0': "#FFB8B8",
  '1': "#AAFFAA",
  '2': "#00FFFF",
  '3': "#C0A0FF",
  'X': grid_color,
  '.': "#F0F0F0"
}


var player_colors = {
  0: "#FF0000",
  1: "#008000",
  2: "#0033FF",
  3: "#8000A0"
}


// *********************************************************************
// Utility functions
// *********************************************************************

function getURLParameter (name) {
  // http://stackoverflow.com/questions/1403888/get-url-parameter-with-jquery
  var a = (RegExp(name + '=' + '(.+?)(&|$)').exec(location.search)||[,null])[1]
  if (a != null) return decodeURI(a);
  return null;
}


// Callback has a single parameter with the file contents.
function loadFile (file, callback) {
  var xmlhttp;

  if (file == null || file == "") {
    alert("You must specify a file to load.");
    return;
  }

  if (window.XMLHttpRequest) xmlhttp = new XMLHttpRequest(); // Code for IE7+, Firefox, Chrome, Opera, Safari.
  else xmlhttp = new ActiveXObject("Microsoft.XMLHTTP"); // Code for IE6, IE5.

  // http://www.w3schools.com/ajax/ajax_xmlhttprequest_onreadystatechange.asp
  xmlhttp.onreadystatechange = function() {
    // Note: We cannot check xmlhttp.status != 200 for errors because status is not set when loading local files.
    if (xmlhttp.readyState == 4) callback(xmlhttp.responseText);
  }

  xmlhttp.open("GET", file, false);
  xmlhttp.send();
}


function int (s) {
  return parseInt(s);
}


function double (s) {
  return parseFloat(s);
}


function parse_assert (read_value, expected_value) {
  var correct = (read_value == expected_value);
  if (!correct) alert("Error parsing file, expected token: " + expected_value + ", read token: " + read_value + ".");
  return correct;
}


// *********************************************************************
// Initialization functions
// *********************************************************************

function parseData (raw_data_str) {
  if (raw_data_str == "") {
    alert("Could not load game file.");
    return false;
  }

  // Convert text to tokens.
  var st = raw_data_str + "";
  var t = st.replace('\n', ' ').split(/\s+/);
  var p = 0;

  data.secgame = (t[p++] == "SecGame");

  parse_assert(t[p++], "Seed");
  data.seed = int(t[p++]);

  // Game and version.
  if (t[p++] != "Dominator") {
    alert("Are you sure this is a Dominator game file?");
    document.getElementById('file').value = "";
    document.getElementById('inputdiv').style.display = "";
    document.getElementById('loadingdiv').style.display = "none";
    return false;
  }

  data.version = t[p++];
  if (data.version != "4.0") alert("Unsupported game version! Trying to load it anyway.");

  parse_assert(t[p++], "nb_players");
  data.nb_players = int(t[p++]);

  parse_assert(t[p++], "nb_rounds");
  data.nb_rounds = int(t[p++]);

  parse_assert(t[p++], "nb_farmers");
  data.nb_farmers = int(t[p++]);

  parse_assert(t[p++], "nb_knights");
  data.nb_knights = int(t[p++]);

  parse_assert(t[p++], "nb_witches");
  data.nb_witches = int(t[p++]);

  parse_assert(t[p++], "farmers_health");
  data.farmers_health = int(t[p++]);

  parse_assert(t[p++], "knights_health");
  data.knights_health = int(t[p++]);

  parse_assert(t[p++], "farmers_regen");
  data.farmers_regen = int(t[p++]);

  parse_assert(t[p++], "knights_regen");
  data.knights_regen = int(t[p++]);

  parse_assert(t[p++], "damage_min");
  data.damage_min = int(t[p++]);

  parse_assert(t[p++], "damage_max");
  data.damage_max = int(t[p++]);

  parse_assert(t[p++], "rows");
  data.rows = int(t[p++]);

  parse_assert(t[p++], "cols");
  data.cols = int(t[p++]);

  data.nb_units = data.nb_players * (data.nb_knights + data.nb_farmers + data.nb_witches);

  parse_assert(t[p++], "names");
  data.names = new Array();
  for (var i = 0; i < data.nb_players; ++i) data.names[i] = t[p++];

  data.rounds = new Array();
  for (var round = 0; round <= data.nb_rounds; ++round) {
    // Maze.
    data.rounds[round] = new Object();
    data.rounds[round].rows = new Array();
    for (var i = 0; i < data.rows; ++i) data.rounds[round].rows[i] = t[p++];

    parse_assert(t[p++], "round");
    if (int(t[p++]) != round) alert("Wrong round number!");

    // Land.
    parse_assert(t[p++], "land");
    data.rounds[round].land = new Array();
    for (var i = 0; i < data.nb_players; ++i) data.rounds[round].land[i] = int(t[p++]);

    // Total score.
    parse_assert(t[p++], "total_score");
    data.rounds[round].total_score = new Array();
    for (var i = 0; i < data.nb_players; ++i) data.rounds[round].total_score[i] = int(t[p++]);

    // Status.
    parse_assert(t[p++], "status");
    data.rounds[round].cpu = new Array();
    for (var i = 0; i < data.nb_players; ++i) {
      var cpu = int(double(t[p++])*100);
      data.rounds[round].cpu[i] = (cpu == -100) ? "out" : cpu + "%";
    }

    // Units.
    data.rounds[round].units = [ ];
    data.rounds[round].alive_farmers = { 0:0, 1:0, 2:0, 3:0 };
    data.rounds[round].alive_knights = { 0:0, 1:0, 2:0, 3:0 };
    data.rounds[round].alive_witches = { 0:0, 1:0, 2:0, 3:0 };
    for (var i = 0; i < data.nb_units; ++i) {
      var unit = {
        type:   t[p++],
        player: int(t[p++]),
        i:      int(t[p++]),
        j:      int(t[p++]),
        health: int(t[p++]),
        move:   '' // Will be set when reading movements.
      };

      data.rounds[round].units.push(unit);
      if (unit.type == 'k') ++data.rounds[round].alive_knights[unit.player];
      else if (unit.type == 'f') ++data.rounds[round].alive_farmers[unit.player];
      else ++data.rounds[round].alive_witches[unit.player];
    }

    if (round != data.nb_rounds) {
      // Movements.
      parse_assert(t[p++], "movements");
      var code = int(t[p++]);
      while (code != -1) {
        data.rounds[round].units[code].move = t[p++];
        code = int(t[p++]);
      }
    }
  }
  return true;
}


// Initializing the game.
function initGame (raw_data) {
  document.getElementById("loadingdiv").style.display = "";

  // TODO: Next two calls could run concurrently.
  if (parseData(raw_data) === false) return;
  preloadImages();

  // Prepare state variables.
  // if (getURLParameter("start") == "yes") gamePaused = false;
  // else gamePaused = true;
  gamePaused = false;

  gamePreview = true;

  // Canvas element.
  canvas = document.getElementById('myCanvas');
  context = canvas.getContext("2d");

  // Prepare the slider.
  $("#slider").slider({
    slide: function(event, ui) {
      var value = $("#slider").slider( "option", "value" );
      actRound = value;
      frames = 0;
      gamePaused = true;
      gamePreview = true;
    }
  });
  $("#slider").width(600);
  $("#slider").slider("option", {min: 0, max: data.nb_rounds});

  // Set the listerners for interaction.
  document.addEventListener('mousewheel', onDocumentMouseWheel, false);
  document.addEventListener('keydown', onDocumentKeyDown, false);
  document.addEventListener('keyup', onDocumentKeyUp, false);

  window.addEventListener('resize', onWindowResize, false);
  onWindowResize();

  document.getElementById("loadingdiv").style.display = "none";
  document.getElementById("gamediv").style.display = "";

  mainloop();
}


function preloadImages () {
  data.img = new Array();

  // Background.
  // data.img.background = new Image();
  // data.img.background.src = "img/tile_floor.png";
}


// *********************************************************************
// Main loop functions
// *********************************************************************

function updateGame () {
  /*
  if (actRound >= 0 && actRound < data.nb_rounds) {
    for (var i = 0; i < data.nb_players; ++i) {
      var f = (frames+i)%4;
      switch (data.rounds[actRound].team[i].pacman.action) {
        case 't': //Top
          data.img.spr_pacman[i] = data.img.spr_pacman_t[i][f];
          break;
        case 'b': //Bottom
          data.img.spr_pacman[i] = data.img.spr_pacman_b[i][f];
          break;
        case 'r': //Right
          data.img.spr_pacman[i] = data.img.spr_pacman_r[i][f];
          break;
        case 'l': //Left
          data.img.spr_pacman[i] = data.img.spr_pacman_l[i][f];
          break;
        default: //None
          data.img.spr_pacman[i] = data.img.spr_pacman_r[i][f];
          break;
      }
    }
  }
  */
  $("#slider").slider("option", "value", actRound);
}


function writeGameState () {
  // Write round.
  $("#round").html("Round: " + actRound);

  // Update scoreboard.
  var scoreboard = "";
  for (var i = 0; i < data.nb_players; ++i) {
    scoreboard += "<span class='score'>"
      + "<div style='display:inline-block; margin-top: 5px; width:20px; height:20px; background-color:" + cell_colors[i] + "'></div>"
      + "<div style='display:inline-block; vertical-align: middle; margin-bottom: 7px; margin-left:8px;'>" + data.names[i] + "</div>"
      + "<br/>"
      + "<div style='margin-left: 10px;'>"
      + "<div style='padding:2px;'>Land: " + data.rounds[actRound].land[i] + "</div>"
      + "<div style='padding:2px;'>Farmers: " + data.rounds[actRound].alive_farmers[i] + "</div>"
      + "<div style='padding:2px;'>Knights: " + data.rounds[actRound].alive_knights[i] + "</div>"
      + (data.secgame ? "<div style='padding:2px;'>CPU: " + data.rounds[actRound].cpu[i] + "</div>" : "")
      + "</div>"
      + "</span><br/><br/>";
  }
  $("#scores").html(scoreboard);

  var order = [0, 1, 2, 3];
  for (var i = 0; i < 3; ++i) {
    for (var j = i + 1; j < 4; ++j) {
      if (data.rounds[actRound].total_score[order[i]] < data.rounds[actRound].total_score[order[j]]) {
        var k = order[i];
        order[i] = order[j];
        order[j] = k;
      }
    }
  }

  var totalboard = "";
  for (var i = 0; i < data.nb_players; ++i) {
    totalboard += "<span class='total'>"
      + "<div style='display:inline-block; margin-top: 5px; width:20px; height:20px; background-color:" + cell_colors[order[i]] + "'></div>"
      + "<div style='display:inline-block; vertical-align: middle; margin-bottom: 7px; margin-left:8px;'>"
      + data.rounds[actRound].total_score[order[i]] + "</div>"
      + "</span><br/><br/>";
  }
  $("#totals").html(totalboard);
}


function drawGame () {
  // Boundary check.
  if (actRound < 0) actRound = 0;
  if (actRound >= data.nb_rounds) actRound = data.nb_rounds;

  // Outter Rectangle.
  context.fillStyle = grid_color;
  context.fillRect(0, 0, tileSize*data.cols, tileSize*data.rows);

  // Draw maze.
  var rows = data.rounds[actRound].rows;
  for (var i = 0; i < data.rows; ++i) {
    var row = rows[i];
    for (var j = 0; j < data.cols; ++j) {
      var cell = row[j];
      context.fillStyle = cell_colors[cell];
      context.fillRect(j*tileSize, i*tileSize, tileSize - 0.5, tileSize - 0.5); // -1 to show a grid.
    }
  }

  // Draw units.
  context.lineWidth = unitLineWidth;
  var units = data.rounds[actRound].units;
  for (var un in units) {
    var u = units[un];
    context.strokeStyle = player_colors[u.player];
    context.fillStyle = player_colors[u.player];
    var i = u.i;
    var j = u.j;

    if (gameAnim) {
      if (frames >= FRAMES_PER_ROUND/2) {
        if (u.move == 'b') i += 0.5;
        else if (u.move == 'w') { i += 0.5; j += 0.5; }
        else if (u.move == 'r') j += 0.5;
        else if (u.move == 'x') { i -= 0.5; j += 0.5; }
        else if (u.move == 't') i -= 0.5;
        else if (u.move == 'y') { i -= 0.5; j -= 0.5; }
        else if (u.move == 'l') j -= 0.5;
        else if (u.move == 'z') { i += 0.5; j -= 0.5; }
      }
    }

    if (u.type == 'k') drawKnight(i, j);
    else if (u.type == 'f') drawFarmer(i, j);
    else drawWitch(i, j);
  }
}


function drawKnight (i, j) {
  var size = unitSize * tileSize;
  var offset = (tileSize - size) / 2;
  context.fillRect(j*tileSize + offset + 0.1*size, i*tileSize + offset + 0.1*size, 0.8*size, 0.8*size);
}


function drawFarmer (i, j) {
  var size = unitSize * tileSize * 0.4;
  var offset = (tileSize - size) / 2;
  context.beginPath();
  context.arc(j*tileSize + size/2 + offset, i*tileSize + size/2 + offset, size/2, 0, Math.PI*2, false);
  context.fill();
  context.stroke();
}


function drawWitch (i, j) {
  var size = unitSize * tileSize * 0.6;
  var offset = (tileSize - size) / 2;
  context.beginPath();
  context.arc(j*tileSize + size/2 + offset, i*tileSize + size/2 + offset, size/2, 0, Math.PI*2, false);
  context.fill();
  context.stroke();
  context.beginPath();
  context.moveTo(j*tileSize + offset - 0.4*size, i*tileSize + offset - 0.4*size);
  context.lineTo(j*tileSize + offset + 1.4*size, i*tileSize + offset + 1.4*size);
  context.stroke();
  context.beginPath();
  context.moveTo(j*tileSize + offset + 1.4*size, i*tileSize + offset - 0.4*size);
  context.lineTo(j*tileSize + offset - 0.4*size, i*tileSize + offset + 1.4*size);
  context.stroke();
}


// *********************************************************************
// Button events
// *********************************************************************

function playButton () {
  gamePaused = false;
}


function pauseButton () {
  gamePaused = true;
  gamePreview = true; // To call render again.
  frames = 0;
}


function startButton () {
  gamePaused = true;
  gamePreview = true;
  frames = 0;
  actRound = 0;
}


function endButton () {
  gamePreview = true;
  frames = 0;
  actRound = data.nb_rounds;
}


function animButton () {
  gameAnim = !gameAnim;
}


function closeButton () {
  window.close();
}


// *********************************************************************
// Keyboard and Mouse events
// *********************************************************************

function onDocumentMouseWheel (event) {
}


function onDocumentKeyDown (event) {
}


function onDocumentKeyUp (event) {
  // http://www.webonweboff.com/tips/js/event_key_codes.aspx
  switch (event.keyCode) {
    case 36: // Start.
      gamePreview = true;
      actRound = 0;
      frames = 0;
      break;

    case 35: // End.
      gamePreview = true;
      actRound = data.nb_rounds;
      frames = 0;
      break;

    case 33: // PageDown.
      gamePreview = true;
      actRound -= 10;
      frames = 0;
      break;

    case 34: // PageUp.
      gamePreview = true;
      actRound += 10;
      frames = 0;
      break;

    case 38: // ArrowUp.
    case 37: // ArrowLeft.
      gamePaused= true;
      gamePreview = true;
      --actRound;
      frames = 0;
      break;

    case 40: // ArrowDown.
    case 39: // ArrowRight.
      gamePaused = true;
      gamePreview = true;
      ++actRound;
      frames = 0;
      break;

    case 32: // Space.
      if (gamePaused) playButton();
      else pauseButton();
      break;

    case 72: // "h"
      help();
      break;

    default:
      // $("#debug").html(event.keyCode);
      break;
  }
}


function onWindowResize (event) {
  // Constants.
  var header_height = 150;
  var canvas_margin = 20;

  // Set canvas size.
  var size = Math.min(document.body.offsetWidth, document.body.offsetHeight - header_height) - canvas_margin*2;

  canvas.width  = size;
  canvas.height = size;

  var max_dimension = Math.max(data.cols,data.rows);
  tileSize = size / max_dimension;

  drawGame();
}


function help () {
  // Opens a new popup with the help page.
  var win = window.open('help.html', 'name', 'height=400, width=300');
  if (window.focus) win.focus();
  return false;
}


// *********************************************************************
// This function is called periodically.
// *********************************************************************

function mainloop () {
  // Configure buttons.
  if (gamePaused) {
    $("#but_play").show();
    $("#but_pause").hide();
  }
  else {
    $("#but_play").hide();
    $("#but_pause").show();
  }

  if (actRound < 0) actRound = 0;

  if (actRound > data.nb_rounds) {
    actRound = data.nb_rounds;
    gamePaused = true;
    frames = 0;
  }

  if (!gamePaused || gamePreview) {
    updateGame();
    drawGame();
    writeGameState();

    if (gamePreview) {
      frames = 0;
      gamePreview = false;
    }
    else {
      ++frames;
      if (frames == FRAMES_PER_ROUND) {
        frames = 0;
        actRound += gameDirection;
      }
    }
  }

  // Periodically call mainloop.
  var frame_time = 1000/speed;
  setTimeout(mainloop, frame_time);
}


// *********************************************************************
// Main function, it is called when the document is ready.
// *********************************************************************

function init () {
  // Get url parameters.
  var game;
  if (getURLParameter("sub") != null) {
    var domain = window.location.protocol + "//" + window.location.host;
    if (getURLParameter("nbr") != null)
      game = domain + "/?cmd=lliuraments&sub=" + getURLParameter("sub") + "&nbr=" + getURLParameter("nbr") + "&download=partida";
    else
      game = domain + "/?cmd=partida&sub=" + getURLParameter("sub") + "&download=partida";
  }
  else game = getURLParameter("game");

  if (game == null || game == "") {
    // Ask the user for a game input.
    var inputdiv = document.getElementById('inputdiv')
    inputdiv.style.display = "";
    document.getElementById('file').addEventListener('change', function(evt) {
      //http://www.html5rocks.com/en/tutorials/file/dndfiles/
      var file = evt.target.files[0];
      var reader = new FileReader();
      reader.readAsText(file);
      reader.onloadend = function(evt) {
        if (evt.target.readyState != FileReader.DONE) alert("Error accessing file.");
        else { // DONE == 2.
          inputdiv.style.display = "none";
          document.getElementById("loadingdiv").style.display = "";
          initGame(reader.result);
        }
      };
    }, false);
  }
  else {
    document.getElementById("loadingdiv").style.display = "";
    // Load the given game.
    loadFile(game, initGame);
  }
}
