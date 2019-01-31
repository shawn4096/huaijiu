// time.c
// yuj@sj �������緶Χ��ʱ�䣬������ʱ�䣬������

inherit F_SAVE;

string query_save_file()
{
        return "/log/time";
}

void create() {
        seteuid(getuid());
        restore();
}

string Ctime(int t)
{
	string ts = ctime(t);

	ts = " "+ts[0..2]+ts[19..23]+"-"+ts[4..6]+"-"+ts[8..9]+ts[10..15];
	ts = replace_string(ts, "Sun", "������");
	ts = replace_string(ts, "Mon", "����һ");
	ts = replace_string(ts, "Tue", "���ڶ�");
	ts = replace_string(ts, "Wed", "������");
	ts = replace_string(ts, "Thu", "������");
	ts = replace_string(ts, "Fri", "������");
	ts = replace_string(ts, "Sat", "������");
	ts = replace_string(ts, "Jan", "һ��");
	ts = replace_string(ts, "Feb", "����");
	ts = replace_string(ts, "Mar", "����");
	ts = replace_string(ts, "Apr", "����");
	ts = replace_string(ts, "May", "����");
	ts = replace_string(ts, "Jun", "����");
	ts = replace_string(ts, "Jul", "����");
	ts = replace_string(ts, "Aug", "����");
	ts = replace_string(ts, "Sep", "����");
	ts = replace_string(ts, "Oct", "ʮ��");
	ts = replace_string(ts, "Nov", "ʮһ��");
	ts = replace_string(ts, "Dec", "ʮ����");
	return ts;
}

string SYDtime(int t)
{
	mixed *lt = localtime(t);

	if ( (lt[4] > 9 || lt[4] < 2)
	  || (lt[4] == 9 && lt[3] - 24 > lt[6])	// Last Sunday
	  || (lt[4] == 2 && lt[3] - 25 < lt[6])	// Last Sunday
	) return Ctime(t+3600)+" (����ʱ��)";
	else return Ctime(t);
}

string NZtime(int t)
{
	mixed *lt = localtime(t);

	if ( (lt[4] > 9 || lt[4] < 2)
	  || (lt[4] == 9 && lt[3] > lt[6])	// First Sunday
	  || (lt[4] == 2 && lt[3] - 5 < lt[6])	// First Sunday on or after 5
	) return Ctime(t+3600)+" (����ʱ��)";
	else return Ctime(t);
}

string NAtime(int t)
{
	mixed *lt = localtime(t);

	if ( (lt[4] > 3 && lt[4] < 9)
	  || (lt[4] == 3 && lt[3] > lt[6])	// First Sunday
	  || (lt[4] == 9 && lt[3] - 25 < lt[6])	// Last Sunday
	) return Ctime(t+3600)+" (����ʱ��)";
	else return Ctime(t);
}

string EUtime(int t)
{
	mixed *lt = localtime(t);

	if ( (lt[4] > 2 && lt[4] < 9)
	  || (lt[4] == 2 && lt[3] - 24 > lt[6])	// Last Sunday
	  || (lt[4] == 9 && lt[3] - 25 < lt[6])	// Last Sunday
	) return Ctime(t+3600)+" (����ʱ��)";
	else return Ctime(t);
}

int modify = 0;

int main(object me, string arg)
{
	int t;

	if (!wizardp(me) || !arg) {
		int GMT = time() + localtime(0)[8] + modify;

		write("������" + NATURE_D->game_time() + "��\n");
		write("��������Ϸ����������ʱ����" + Ctime(GMT+28800) + "\n");
		write("                Ϥ��ʱ����" + SYDtime(GMT+36000) + "\n");
		write("      �¿����������ʱ����" + NZtime(GMT+43200) + "\n");
		write("      �¸绪����ɼ�ʱ����" + NAtime(GMT-28800) + "\n");
		write("        ���׶ࡢŦԼʱ����" + NAtime(GMT-18000) + "\n");
		write("    ���֡���������ʱ����" + EUtime(GMT+3600) + "\n");
	} else {
		int i;

		if (sscanf(arg, "%d", i) == 1) {
			modify += i;
			save();
			write(ctime(time() + localtime(0)[8] + 28800 + modify) + "\n");
			return 1;
		}
		me = LOGIN_D->find_body(arg);
		if (!me) return notify_fail("û�������ҡ�\n");
	}
	t = me->query_temp("online_time");
	if (t > 0) write("���Ѿ���������"+CHINESE_D->chinese_time(t)+"��\n");
	t = me->query("online_total");
	if (t > 0) write("���������"+CHINESE_D->chinese_time(t)+"��\n");
	return 1;
}

int help(object me)
{
 	write(@HELP
ָ���ʽ: time

���ָ������(��)֪�����ڵ�ʱ����

HELP
    );
    return 1;
}
