<?
$database='/usr/local/var/internet.gdb';
$squid_log_file='/usr/local/squid/var/logs/access.log';
$user='INTERNET';
$pass='ipfwlog';
date_default_timezone_set('Europe/Moscow');

$date = getdate();
$user_ip=$_SERVER["REMOTE_ADDR"];
$d_mon=$date["mon"];
$d_year=$date["year"];
?>
