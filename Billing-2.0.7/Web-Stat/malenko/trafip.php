<?
require 'config.php';
require 'head.php';

$title=sprintf("������ ��� ������� ���������� �� %s/%s",$d_mon,$d_year);
print_base_hdr($title);
//echo '<tr><td><center><b>Date</b></center></td><td align=right><b>',$d_mon,'/',$d_year,'</b></td></tr>';

echo "<tr><td valign=top align=center><b>#</b></td><td valign=top align=center><b>IP-�����<br>����������</b></td><td align=center><b>���<br>����������</b></td><td align=center><b>��������<br>������, ����</b></td><td align=center><b>���������<br>������, ����</b></td></tr>";

$q_text=sprintf("select ip,pcname,sum_traf,sum_traf_out from traf_view1 where sum_traf>0 and date_year=%lu and date_month=%lu order by sum_traf DESC",$d_year,$d_mon);
$dbh = ibase_connect($database,$user,$pass,'WIN1251','100','3');
$sth = ibase_query($dbh, $q_text);
$i=0;
while ($row = ibase_fetch_object($sth)) 
 echo "<tr><td align=right>",++$i,"</td><td align=right>192.168.0. <b>",$row->IP," </b></td><td align=center>",$row->PCNAME,"</td><td align=right>",$row->SUM_TRAF,"</td><td align=right>",$row->SUM_TRAF_OUT,"</td></tr>";
ibase_free_result($sth);
ibase_close($dbh);

echo '</table></center></html>';
?>
