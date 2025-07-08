<?
$database='/usr/local/var/internet.gdb';
$squid_log_file='/usr/local/squid/var/logs/access.log';
$user='INTERNET';
$pass='ipfwlog';
date_default_timezone_set('Europe/Moscow');

$user_ip=$_GET["user_ip"];
$d_mon=$_GET["d_mon"];
$d_year=$_GET["d_year"];

$date = getdate();
if (!strlen($user_ip)) $user_ip=$_SERVER["REMOTE_ADDR"];
if (!strlen($d_mon)) $d_mon=$date["mon"];
if (!strlen($d_year)) $d_year=$date["year"];
?>
