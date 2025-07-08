<?
require 'config.php';
require 'head.php';

$total=0;
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
// if ($ip!=$user_ip) continue;
 $workbuf=strtok("/"); //Action
// if ($workbuf=="TCP_DENIED") continue;
 $workbuf=strtok(" "); //Code
 if (strcmp($workbuf,"304") && strcmp($workbuf,"403")) continue;  // Is Cached traffic
 $size=strtok(" "); //Size
 $total+=$size;
 if (!strlen($logar[$ip])) $logar[$ip]=0;
 $logar[$ip]+=$size;
// break;
 }
fclose($log);
arsort($logar);


print_base_hdr("Cached and Denied traffic Report");

//echo '<tr><td align=center><b>IP Address</b></td><td align=right><b>',$user_ip,'</b></td></tr>';
echo '<tr><td><center><b>Date</b></center></td><td align=right><b>',$d_mon,'/',$d_year,'</b></td></tr>';

$av=array_values($logar);
$ak=array_keys($logar);
$i=0;while($av[$i]!="")
 {
 printf("<tr><td><center>%s</center></td><td align=right>%s</td></tr>",$ak[$i],$av[$i]);
 $i++;
 }
printf("<tr><td><center><b>Total</b></center></td><td align=right><b>%s</b></td></tr>",$total); 
echo '</table></center></html>'; 
?>
