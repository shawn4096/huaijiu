// /u/look/workroom.c include Exp sort and online player
// And write to /log/html/top10.html. Link to /home/httpd/html/top10.html
// And write to /log/html/onlineuser.html. Link to /home/httpd/html/onlineuser.html
// And write to /log/html/party.html. Link to /home/httpd/html/party.html
// And write to /log/html/count24.html. Link to /home/httpd/html/count24.html
// Write By Look@SJ 19990906

#include <ansi.h>
#include <room.h>
#include <mudlib.h>
#include <localtime.h>

inherit ROOM;
int sort_user(object,object);
int sort(object obj1, object obj2);
int filldata(object obj1);
int writefile();
string remove_ansi(string str);

void create()
{
        set("short","��");
        set("long","��");
//        set("objects", ([__DIR__"fuck" : 1]));
        set("valid_startroom", 1);
	set("exits", (["out" : "/d/city/guangchang"]));
	seteuid(getuid());
	remove_call_out("writefile");
	call_out("writefile", 0);
        setup();
}

int clean_up()
{
    return 0;
}

int writefile()
{
        int totalexp = 0, max, i, j = 1, ppl_cnt=0, cnt, count, wcnt = 0, ppls;
        string sn, show="", str="", fname="";
        mixed *ob_list, *ob_list_old, *ltime;
        object *list, *ob, obj1;
//������ǰ��½�˴�������
//show,ppl_cnt,�ֱ���Сʱ������ֹ��ʱ��Сʱ��½���˴�������
//	if (file_size("/log/html/hourcount") > 0)
//	sscanf(read_file("/log/html/hourcount"), "%s %d", show,ppl_cnt);
//	if (ctime(time())[11..12] != show)
//	{
  //      sscanf(read_file("/log/ppls"), "%d", ppls);
//      if (ppl_cnt==0) ppl_cnt = ppls - 100;
//	ob = filter_array(objects(), (: userp :));
//	i = sizeof(ob);
//	write_file("/log/html/hourcount"+ctime(time())[11..12], sprintf("%d %d",ppls - ppl_cnt,i),1);
//	write_file("/log/html/hourcount", sprintf("%s %d",ctime(time())[11..12],ppls),1);
//�ӵ�ǰСʱ+1��ʼ��ʾ������html�ļ�
//	write_file("/log/html/count24.html", "<html>\n<head>\n<META HTTP-EQUIV=\"Pragma\" CONTENT=\"no-cache\">\n<meta http-equiv='Content-Type' content='text/html; charset=gb2312'>\n<title>�齣</title>\n<link rel='stylesheet' href='http://www.mymud.com/my_style.css' type='text/css'>\n</head>\n\n", 1);
//        write_file("/log/html/count24.html", "<center>"CHINESE_MUD_NAME"���24Сʱ��½�˴�ͳ��<HR size=1 width='80%'>\n",0);
//        write_file("/log/html/count24.html", "<table border=0 cellpadding=0 cellspacing=0 height='75%' width='85%'>\n<tr>\n",0);
//	write_file("/log/html/count24.html", "<td width='4%' height='90%' bgcolor=#FFFFFF align=center valign=center>��<br><br><br>��<br><br><font color=RED>��<br>½<br></font><font color=BLUE>��<br>��<br>��</font</td>",0);
//        ltime = localtime(time());
//	cnt = ltime[LT_HOUR];
//	for (i=1;i<25;i++)
//	{
//		sn=((cnt+i)>=24)?((string)(cnt+i-24)):((string)(cnt+i));
//		sn=(((int)sn)<10)?("0"+sn):sn;
//		if (file_size("/log/html/hourcount"+sn) > 0)
//		{
//			sscanf(read_file("/log/html/hourcount"+sn), "%d %d", ppl_cnt,count);
//            ppl_cnt = ppl_cnt / 4;
//			if (ppl_cnt>250) ppl_cnt=250;
//			write_file("/log/html/count24.html", "<td width='4%' height='90%' align=center valign=bottom><img src='image\\red.gif' width='6' height='"+(string)ppl_cnt+"'><img src='image\\blue.gif' width='6' height='"+(string)count+"'></td>\n",0);
//		}
//		else
//		{
//			write_file("/log/html/count24.html", "<td width='4%' height='90%'>��</td>\n",0);
//		}
//	}
//	write_file("/log/html/count24.html", "</tr>\n<tr><td>��</td>",0);
//	for (i=0;i<24;i++)
//	{
//		sn=(string)((cnt+i)>=24?(cnt+i-24):(cnt+i));
//		write_file("/log/html/count24.html", "<td align=center>"+sn+"</td>\n",0);
//	}
//	write_file("/log/html/count24.html", "<tr>\n</table>\n<HR size=1 width='85%'>��ҳ������ÿһСʱˢ��һ�Ρ�"CHINESE_MUD_NAME"���������ܵ�½�˴�("+(string)ppls+")<BR>�����ļ���������˻��壬��Reload���ܿ������µĵ�½������ͳ�����ϡ�<br><a href=http:\\\\www.mymud.com\\index.html>������ҳ</a>&nbsp&nbsp<a href=\"javascript:window.close()\">�رմ���</a></center></body></html>",0);
//        tell_room(this_object(),"��½/��������ͳ����ɡ�\n");
//	}

//���������ļ����ɡ�
        ob_list_old = users();
        ob_list_old = filter_array(ob_list_old, (: filldata :));
        max=sizeof(ob_list_old);
        if (max > 10) max=10;
        ob_list = sort_array(ob_list_old, (: sort :));
	write_file("/log/html/top10.html", "<html>\n<head>\n<META HTTP-EQUIV=\"Pragma\" CONTENT=\"no-cache\">\n<meta http-equiv='Content-Type' content='text/html; charset=gb2312'>\n<title>�齣</title>\n<link rel='stylesheet' href='http://www.mymud.com/my_style.css' type='text/css'>\n</head>\n\n", 1);
        write_file("/log/html/top10.html", "<center><BR><BR>"CHINESE_MUD_NAME"����ʮ�����<BR><HR size=1 width='80%'>\n",0);
        write_file("/log/html/top10.html", "<table border=0 cellpadding=0 cellspacing=5 width='80%'>\n",0);
        write_file("/log/html/top10.html", "<tr align=center><td width='10%' bgcolor='#C0C0C0'>����</td><td width='50%' bgcolor='#C0C0C0'>�ǳ�</td><td width='25%' bgcolor='#C0C0C0'>����</td><td width='15%' bgcolor='#C0C0C0'>����</td></tr>\n",0);
        for (i=0;i<max;i++)
          {
            obj1 = ob_list[i];
            show = obj1->query("name")+"("+capitalize(obj1->query("id"))+")</td><td>";
            write_file("/log/html/top10.html",sprintf("%sNo.%d%s%s%s\n","<tr align=center><td>",i+1,"</td><td>��"+remove_ansi(obj1->query("nickname")?obj1->query("nickname"):"����")+"��</td><td>",show,obj1->query("family/family_name")+"</td></tr>"),0);
          }
        write_file("/log/html/top10.html","</table><HR size=1 width='80%'><BR>��ҳ������ÿ5����ˢ��һ�Ρ�<BR>�����ļ���������˻��壬��Reload���ܿ�������������<br><br><a href=\"javascript:window.close()\">�رմ���</a></center></body></html>",0);
//������Ҽ�����ʵ���ļ�����
	write_file("/log/html/onlineuser.html", "<html>\n<head>\n<META HTTP-EQUIV=\"Pragma\" CONTENT=\"no-cache\">\n<meta http-equiv='Content-Type' content='text/html; charset=gb2312'>\n<title>�齣</title>\n<link rel='stylesheet' href='http://www.mymud.com/my_style.css' type='text/css'>\n</head>\n\n", 1);
        write_file("/log/html/onlineuser.html", "<center><BR>"CHINESE_MUD_NAME"�������<BR><HR size=1 width='80%'>\n",0);
        write_file("/log/html/onlineuser.html", "<table border=0 cellpadding=0 cellspacing=5 width='95%'>\n",0);
        write_file("/log/html/onlineuser.html", "<tr align=center><td width='12%' bgcolor='#C0C0C0'>����</td><td width='88%' colspan=4 bgcolor='#C0C0C0'>��������(ID)</td></tr><tr>\n",0);

	write_file("/log/html/party.html", "<html>\n<head>\n<META HTTP-EQUIV=\"Pragma\" CONTENT=\"no-cache\">\n<meta http-equiv='Content-Type' content='text/html; charset=gb2312'>\n<title>�齣</title>\n<link rel='stylesheet' href='http://www.mymud.com/my_style.css' type='text/css'>\n</head>\n\n", 1);
        write_file("/log/html/party.html", "<center><BR>"CHINESE_MUD_NAME"�����������ʵ��ͼʾ<BR><HR size=1 width='80%'>\n",0);
        write_file("/log/html/party.html", "<table border=0 cellpadding=0 cellspacing=0 width='95%'>\n",0);
        write_file("/log/html/party.html", "<tr align=center><td width='12%' bgcolor='#C0C0C0'>����</td><td width='88%' bgcolor='#C0C0C0'>�ۺ�ʵ��</td></tr>\n",0);

        ob = filter_array(objects(), (: userp :));
        list = sort_array(ob, (: sort_user :));
        ppl_cnt = 0;
        cnt = 0;
        i = sizeof(list);
        count = 0;
        while( i-- ) {
                if( !environment(list[i]) ) continue;
                if (wizardp(list[i]) && list[i]->query("env/invisibility")) continue;
                if (!wiz_level(list[i]) && fname != list[i]->query("family/family_name")) {
                  if (totalexp > 7000000) totalexp = 7000000;
		    if ((fname?totalexp:0) != 0)
		    {
		    	write_file("/log/html/party.html", sprintf("%s%d%s\n","<tr><td align=center>"+fname+"</td><td><hr align=left noshade size='5' color='#FF0000' width='",(totalexp/70000),"%'>"),0);
		    	write_file("/log/html/party.html", sprintf("%s%d%s\n","<hr align=left noshade size='5' color='#0000FF' width='",(totalexp/70000)/j,"%'></td></tr>"),0);
		    }
                    fname = list[i]->query("family/family_name");
		    if (count % 5) str += "</tr>\n<tr>";
		    str += "<td width='12%' align=center bgcolor='#C0C0C0'>"+(fname?fname:"��ͨ����") + "</td>";
                    count = 1;
                    totalexp = 1;
                    j = 0;
                }
                if (!wcnt && wiz_level(list[i])) {
                    if (count % 5) str += "</tr>\n<tr>";
                    str += "<td width='12%' align=center bgcolor='#C0C0C0'>��ʦ</td>";
                    wcnt = 1;
                    count = 1;
                }
                if (!(count % 5)) {
                        count++;
                        str += "<td>��</td>";
                }
                str += sprintf("%s%s%s",
                      "<td width='22%'>"+(interactive(list[i])?(query_idle(list[i]) > 120?"<font color=BLUE>":""):"<font color=RED>"),
                      list[i]->name(1) + "("+capitalize(list[i]->query("id"))+")"+(interactive(list[i])?"":"</font>")+"</td>",
                      (++count % 5) ? "" : "</tr>\n<tr>");
                if (!wiz_level(list[i])){
                	totalexp += (int)list[i]->query("combat_exp");
                	j ++;
                }
                if (interactive(list[i])) ppl_cnt++;
                else cnt++;
        }
        if( count % 5 ) str += "</tr>\n";
   	write_file("/log/html/party.html", sprintf("%s%d%s\n","<tr><td align=center>"+fname+"</td><td><hr align=left noshade size='5' color='#FF0000' width='",(totalexp/70000),"%'>"),0);
   	write_file("/log/html/party.html", sprintf("%s%d%s\n","<hr align=left noshade size='5' color='#0000FF' width='",(totalexp/70000)/j,"%'></td></tr>"),0);
        write_file("/log/html/party.html", "</table><HR size=1 width='95%'><BR><font color=RED>��ɫ</font>��ʾ����EXP�ܺͣ�<font color=BLUE>��ɫ</font>��ʾEXPƽ��ֵ��<BR>��ҳ������ÿ5����ˢ��һ�Ρ�<BR>�����ļ���������˻��壬��Reload���ܿ����������ϡ�<br><br><a href=\"javascript:window.close()\">�رմ���</a></center></body></html>\n",0);
        write_file("/log/html/onlineuser.html", str+"</table>\n",0);
	str = sprintf("�� %d λ��������У�<font color=RED>��ɫ��ʾ����</font>��<font color=BLUE>��ɫ��ʾ����</font>��<BR>\n", ppl_cnt);
        write_file("/log/html/onlineuser.html", str+"\n",0);

        write_file("/log/html/onlineuser.html", "<HR size=1 width='95%'><BR>��ҳ������ÿ5����ˢ��һ�Ρ�<BR>�����ļ���������˻��壬��Reload���ܿ�������������ϡ�<br><br><a href=\"javascript:window.close()\">�رմ���</a></center></body></html>\n",0);
//�ļ����ɽ���
	remove_call_out("writefile");
	call_out("writefile", 300);
        tell_room(this_object(), ctime(time())[11..18]+"\n");
	return 1;
}


int sort(object obj1, object obj2)
{
  int temp1,temp2;
  temp1=obj1->query("combat_exp");
  temp2=obj2->query("combat_exp");
  if (temp1>temp2) return -1;
  else if (temp1<temp2) return 1;
  else return 0;
}

int filldata(object obj1)
{
  if(wiz_level(obj1)) return 0;
  if(!environment(obj1)) return 0;
  else return 1;
}

string remove_ansi(string str)
{
        int i;
        string *color = ({ BLK, RED, GRN, YEL, BLU, MAG, CYN, WHT,
                           HIR, HIG, HIY, HIB, HIM, HIC, HIW,
                           HBRED, HBGRN, HBYEL, HBBLU, HBMAG, HBCYN, HBWHT,
                           BBLK, BRED, BYEL, BBLU, BMAG, BCYN,
                           NOR, BOLD });
        if( !str || !stringp(str) ) return 0;
        i = sizeof(color);
        while( i-- ) {
                str = replace_string(str, color[i], "");
                }
        return str;
}

int sort_user(object ob1, object ob2)
{
        string name1, name2;

        reset_eval_cost();
        if( wiz_level(ob1) != wiz_level(ob2) )
                return wiz_level(ob2)
                        - wiz_level(ob1);
        
        name1 = ob1->query("family/family_name");
        name2 = ob2->query("family/family_name");

        if (intp(name1)) name1 = "";
        if (intp(name2)) name2 = "";
        if (name1 > name2) return -1;
        if (name1 < name2) return 1;

        name1 = ob1->query("id");
        name2 = ob2->query("id");

        if (intp(name1)) name1 = "";
        if (intp(name2)) name2 = "";
        if (name1 > name2) return -1;
        if (name1 < name2) return 1;
//      return 0;
	return (int)ob2->query("combat_exp") - (int)ob1->query("combat_exp");
}
