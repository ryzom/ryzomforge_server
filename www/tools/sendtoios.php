<?php

include_once(dirname(__DIR__).'/libs/admin_modules_itf.php');
include_once(dirname(__DIR__).'/config.php');

$args = array_slice($argv, 1);
queryShard('ios', implode(" ", $args), '', false);
