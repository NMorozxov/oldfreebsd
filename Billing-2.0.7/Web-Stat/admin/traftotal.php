<?
require 'config.php';
require 'head.php';

print_base_hdr("Trafic Total");

$q_text="select date_year,date_month,sum(sum_traf) as SUM_TRAF,sum(sum_traf_out) as SUM_TRAF_OUT from traf_view1 group by date_year,date_month";
$dbh = ibase_connect($database,$user,$pass,'WIN1251','100','3');
$sth = ibase_query($dbh, $q_text);
echo "<tr><td align=center><b>Year</b></td><td align=center><b>Month</b></td><td align=center><b>In TRAF</b></td><td align=center><b>Out TRAF</b></td></tr>";
while ($row = ibase_fetch_object($sth)) 
 echo "<tr><td>",$row->DATE_YEAR,"</td><td>",$row->DATE_MONTH,"</td><td align=right>",$row->SUM_TRAF,"</td><td align=right>",$row->SUM_TRAF_OUT,"</td></tr>";
ibase_free_result($sth);
ibase_close($dbh);

echo '</table></center></html>';
?>
