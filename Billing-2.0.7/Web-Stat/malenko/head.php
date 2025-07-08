<?
function print_base_hdr($title)
 {
 header("Pragma: no-cache"); // HTTP/1.0
 echo '<html><head><meta HTTP-EQUIV="Content-type" CONTENT="text/html; charset=windows-1251"><title>',$title,'</title></head>';
 echo '<style>';
 echo 'body, a, p, td {FONT-FAMILY: Verdana, Arial, sans-serif; FONT-SIZE: 12px}';
 echo 'form {margin:0; padding:0;}';
 echo 'td {background: #DDDDDD;}';
 echo 'a {color: #FF0000;}';
 echo 'h3 {color: #aa5500; font-size: 14px;}';
 echo '</style>';
 echo '<p align="center" style="font-size:10px">Billing System ver 2.0.0 for ipfw firewall (C) Nicol Morozov<br>';
  echo 'Admin Interface</p>';

 echo '<h2 align="center">',$title,'</h2><br><br>';
 echo '<table border="0" cellspacing="2" cellpadding="5" align="center">';
 }
function print_hdr($title,$user_ip,$d_mon,$d_year)
 {
 print_base_hdr($title);
 echo '<tr><td align=center><b>IP-адрес компьютера</b></td><td align=right><b>',$user_ip,'</b></td></tr>';
 echo '<tr><td><center><b>Месяц / год</b></center></td><td align=right><b>',$d_mon,'/',$d_year,'</b></td></tr>';
 }
?>