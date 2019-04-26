<?php

include_once(dirname(__DIR__).'/libs/admin_modules_itf.php');

$data = @queryShard('egs', 'displayPlayers', 'displayPlayers');

if ($data && isset($data['parsed']) && count($data['parsed']) >= 1) {
	foreach ($data['parsed'] as $cid => $user) {
		$name = explode('(', $user[2]);
		echo '<font color="orange">'.$name[0].'</font><font color="white">('.substr($user[4], 2, strlen($user[4])-4).')</font> ';
	}
} else {
	echo 'No players connected!';
	exit(1);
}
