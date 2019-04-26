<?php

include_once(dirname(__DIR__).'/libs/admin_modules_itf.php');

@queryShard('egs', 'broadcast during=30 every=5 @{F00F}The Shard will reboot soon@{FFFF}.\nif you need, please ask @{FB0F}Ulukyn@{FFFF} or @{FB0F}Riasan@{FFFF} to stop it!');

