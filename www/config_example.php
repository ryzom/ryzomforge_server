<?php

// This file contains all variables needed by other php scripts
$LogRelativePath = include_once(dirname(__FILE__).'/logs');

// ----------------------------------------------------------------------------------------
// Variables for nel database access
// ----------------------------------------------------------------------------------------

// where we can find the mysql database
$DBHost         = 'localhost';
$DBUserName     = 'USER';
$DBPassword     = 'PASSWORD';
$DBName         = 'nel';

$RingDBUserName = 'RING_USER';
$RingDBName = 'ring';
$RingDBPassword = 'RING_PASS';

$AcceptUnknownUser = true;
$AutoCreateRingInfo = true;

