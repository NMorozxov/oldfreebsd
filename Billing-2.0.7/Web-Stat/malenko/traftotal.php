<?
require 'config.php';
require 'head.php';

print_base_hdr("Весь трафик офиса (по месецам)");

$q_text="select date_year,date_month,sum(sum_traf) as SUM_TRAF,sum(sum_traf_out) as SUM_TRAF_OUT from traf_view1 group by date_year,date_month";
$dbh = ibase_connect($database,$user,$pass,'WIN1251','100','3');
$sth = ibase_query($dbh, $q_text);
echo "<tr><td valign=top align=center><b>Год</b></td><td valign=top align=center><b>Месяц</b></td><td align=center><b>Входящий трафик,<br>байт </b></td><td align=center><b>Исходящий трафик,<br>байт</b></td></tr>";
while ($row = ibase_fetch_object($sth)) 
 echo "<tr><td align=center>",$row->DATE_YEAR,"</td><td align=center>",$row->DATE_MONTH,"</td><td align=right>",$row->SUM_TRAF,"</td><td align=right>",$row->SUM_TRAF_OUT,"</td></tr>";
ibase_free_result($sth);
ibase_close($dbh);

echo '</table></center></html>';
?>
