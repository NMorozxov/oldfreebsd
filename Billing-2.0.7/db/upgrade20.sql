SET SQL DIALECT 3;

alter table log add traf_out integer;

drop view traf_view1;
drop view traf_view;
drop view log_view;

CREATE VIEW LOG_VIEW(
    NN,
    IP,
    TRAF,
    MAIL,
    DATE_YEAR,
    DATE_MONTH,
    DATE_DAY,TRAF_OUT)
AS
select nn,ip,traf,mail,extract(year from ins_date),extract(MONTH from ins_date),extract(DAY from ins_date),TRAF_OUT
from log;

CREATE VIEW TRAF_VIEW(
    IP,
    DATE_YEAR,
    DATE_MONTH,
    SUM_TRAF,SUM_TRAF_OUT)
AS
SELECT  IP,DATE_YEAR,DATE_MONTH,sum(traf),sum(traf_out)
FROM log_view
group by IP,DATE_YEAR,DATE_MONTH;

CREATE VIEW TRAF_VIEW1(
    IP,
    DATE_YEAR,
    DATE_MONTH,
    SUM_TRAF,SUM_TRAF_OUT,
    FNAME,
    MNAME,
    LNAME,
    EMAIL,
    PCNAME,
    LIMIT,
    TIME_LIMIT,
    TIME_H_DEL,
    TIME_M_DEL,
    TIME_H_ADD,
    TIME_M_ADD,
    HAVE_MAIL,
    HAVE_ICQ,
    HAVE_INTERNET)
AS
SELECT  TRAF_VIEW.IP,
TRAF_VIEW.DATE_YEAR,
TRAF_VIEW.DATE_MONTH,
TRAF_VIEW.SUM_TRAF,
TRAF_VIEW.SUM_TRAF_OUT,
ip.FNAME,
ip.MNAME,
ip.LNAME,
ip.EMAIL,
ip.PCNAME,
ip.LIMIT,
ip.TIME_LIMIT,
ip.TIME_H_DEL,
ip.TIME_M_DEL,
ip.TIME_H_ADD,
ip.TIME_M_ADD,
ip.HAVE_MAIL,
ip.HAVE_ICQ,
ip.HAVE_INTERNET
FROM TRAF_VIEW left join ip on traf_view.ip=ip.ip;

GRANT SELECT ON TRAF_VIEW1 TO INTERNET;
