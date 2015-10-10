// IMPORTANT: choose one
var RL_LIB = "libreadline";  // NOTE: libreadline is GPL
//var RL_LIB = "libedit";

var HISTORY_FILE = require('path').join(process.env.HOME, '.mal-history');

var rlwrap = {}; // namespace for this module in web context

var ffi = require('ffi'),
    fs = require('fs');
