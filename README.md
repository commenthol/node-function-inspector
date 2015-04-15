node-function-inspector
=======================

Updated for node 0.12.x.

Inspect your function.

This module is same as UNIVERSAL::which in perl5.

SYNOPSIS
--------

    var http = require('http');
    var inspect = require('function-inspector').inspect;
    console.log(inspect(http.createServer));

