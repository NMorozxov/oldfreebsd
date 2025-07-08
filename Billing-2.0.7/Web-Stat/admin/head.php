<?
function print_base_hdr($title)
 {
 header("Pragma: no-cache"); // HTTP/1.0
 echo '<html><head><meta HTTP-EQUIV="Content-type" CONTENT="text/html; charset=windows-1251"><title>',$title,'</title></head>';
 echo '<b><center>Billing System ver 2.0.5 for ipfw firewall (C) Nicol Morozov</b>';
 echo '<b><center>',$title,'</center></b>';
 echo '<br><table border=1>';
 }
function print_hdr($title,$user_ip,$d_mon,$d_year)
 {
 print_base_hdr($title);
 echo '<tr><td align=center><b>IP Address</b></td><td align=right><b>',$user_ip,'</b></td></tr>';
 echo '<tr><td><center><b>Date</b></center></td><td align=right><b>',$d_mon,'/',$d_year,'</b></td></tr>';
 }
?>