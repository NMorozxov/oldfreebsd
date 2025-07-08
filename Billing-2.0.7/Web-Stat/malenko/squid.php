<?
require 'config.php';
require 'head.php';

$log=fopen($squid_log_file,"r");
while (!feof ($log)) 
 {
 $logline=fgets($log, 4096);
 $workbuf=strtok($logline,"."); //Time
 $log_date=getdate($workbuf);
 if ($log_date["mon"]!=$d_mon) continue;
 if ($log_date["year"]!=$d_year) continue;
 $workbuf=strtok(" "); //???
 $workbuf=strtok(" "); //Elapsed
 $ip=strtok(" "); //IP
 if ($ip!=$user_ip) continue;
 $workbuf=strtok("/"); //Action
 if ($workbuf=="TCP_DENIED") continue;
 $workbuf=strtok(" "); //Code

if (!strcmp($_GET["count_cache"],"yes") && !strcmp($workbuf,"304")) continue;

 $size=strtok(" "); //Size
 $workbuf=strtok(" "); //Metod
 if ($workbuf=="CONNECT") 
  {
  $site=strtok(" ");
  }
 else
  {
  $site=strtok(":");
  $site=strtok("/");
  } 
 if (!strlen($logar[$site])) $logar[$site]=0;
 $logar[$site]+=$size;
// break;
 }
fclose($log);
arsort($logar);

print_hdr("Подробная статистика для отдельного компьютера с указанием основных серверов с которых скачивалась информация",$user_ip,$d_mon,$d_year);

//echo '<html><head><meta HTTP-EQUIV="Content-type" CONTENT="text/html; charset=windows-1251"><title>Squid Log Report</title></head>';
//echo '<b><center>Billing System ver 1.6.0 for ipfw firewall (C) Nicol Morozov</b><br><br><table border=1><tr><td align=center><b>IP Address</b></td>';
//echo "<td align=right><b>",$user_ip,"</b></td></tr>";
//echo "<tr><td><center><b>Date</b></center></td><td align=right><b>",$d_mon,"/",$d_year,"</b></td></tr>";


$av=array_values($logar);
$ak=array_keys($logar);
$i=0;while($av[$i]!="")
 {
 printf("<tr><td><center>%s</center></td><td align=right>%s</td></tr>",$ak[$i],$av[$i]);
 $i++;
 }
echo '</table></center></html>'; 
?>
