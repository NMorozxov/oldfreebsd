<?
require 'config.php';
require 'head.php';

$log=fopen($squid_log_file,"r");
$total=0;
while (!feof ($log)) 
 {
 $logline=fgets($log/*, 4096*/);
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
 $total+=$size;
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

print_hdr("Squid Log Report",$user_ip,$d_mon,$d_year);
printf("<tr><td><center><b>Total</b></center></td><td align=right><b>%s</b></td></tr>",$total);


$av=array_values($logar);
$ak=array_keys($logar);
$i=0;while($av[$i]!="")
 {
 printf("<tr><td><center>%s</center></td><td align=right>%s</td></tr>",$ak[$i],$av[$i]);
 $i++;
 }
echo '</table></center></html>'; 
?>
