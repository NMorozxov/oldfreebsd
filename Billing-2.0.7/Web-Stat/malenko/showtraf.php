<?
require 'config.php';
require 'head.php';

print_hdr("Трафик за месяц для отдельного компьютера",$user_ip,$d_mon,$d_year);

strtok($user_ip,'.');
strtok('.');
strtok('.');
$tok=strtok('.');

$q_text=sprintf("SELECT * FROM TRAF_VIEW1 WHERE DATE_MONTH=%s AND DATE_YEAR=%s AND IP=%s",$d_mon,$d_year,$tok);

$dbh = ibase_connect($database,$user,$pass,'WIN1251','100','3');
$sth = ibase_query($dbh, $q_text);
while ($row = ibase_fetch_object($sth)) 
 {
// echo "<tr><td><center>Date</center></td><td align=right>",$row->DATE_MONTH,"/",$row->DATE_YEAR,"</td></tr>";
// echo "<tr><td><center>Лимит</center></td><td align=right>",$row->LIMIT,"</td></tr>";
 echo "<tr><td><center>Входящий трафик, байт</center></td><td align=right>",$row->SUM_TRAF,"</td></tr>";
 echo "<tr><td><center>Исходящий трафик, байт</center></td><td align=right>",$row->SUM_TRAF_OUT,"</td></tr>";
// echo "<tr><td><center>Name</center></td><td align=right>",$row->LNAME,"</td></tr>";
 echo "<tr><td><center>Имя компьютера</center></td><td align=right>",$row->PCNAME,"</td></tr>";
// echo "<tr><td><center>E-Mail</center></td><td align=right>",$row->EMAIL,"</td></tr>";
// echo "<tr><td><center>Internet allowed</center></td><td align=right>";
// if ($row->HAVE_INTERNET) echo 'Yes'; else echo 'No';
// echo "</td></tr>";
// echo "<tr><td><center>ICQ allowed</center></td><td align=right>";
// if ($row->HAVE_ICQ) echo 'Yes'; else echo 'No';
// echo "</td></tr>";
// echo "<tr><td><center>Mail allowed</center></td><td align=right>";
// if ($row->HAVE_MAIL) echo 'Yes'; else echo 'No';
// echo "</td></tr>";
 
// echo "<tr><td><center>Time Limit</center></td><td align=right>";
// if ($row->TIME_LIMIT)
//  { echo $row->TIME_H_ADD,':',$row->TIME_M_ADD,' ',$row->TIME_H_DEL,':',$row->TIME_M_DEL,' ';
//  } 
// else echo 'No';
// echo "</td></tr>";
 }
ibase_free_result($sth);
ibase_close($dbh);

echo '</table></center></html>';
?>
