// passwd.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;

	if( me != this_player(1) ) return 0;

	ob = me->query_temp("link_ob");
	if( !ob ) return 0;
	while( ob && ob->is_character() ) ob = ob->query_temp("link_ob");

	write("Ϊ�˰�ȫ���������������ԭ�������룺");
	input_to("get_old_pass", 1, ob);
	return 1;
}

private void get_old_pass(string pass, object ob)
{
	string old_pass;

	old_pass = ob->query("password");
	if( crypt(pass, old_pass)!=old_pass ) {
		write("�������\n");
		return;
	}
	write("�������µ����룺");
	input_to("get_new_pass", 1, ob );
}

private void get_new_pass(string pass, object ob)
{
	int i = strlen(pass), j = 0, k = 0;
	
	write("\n");
	if (pass=="") {
		write("�����޸ģ�����ʹ��ԭ���룡\n");
		return;
	}
	if (i<5) {
		write("����ĳ��ȱ��벻С�������ĸ��\n�������������룺");
		input_to("get_new_pass", 1, ob);
		return;
	}
	if (!LOGIN_D->query("md5") && i>8) {
		write("����ĳ��ȱ��벻���ڰ˸���ĸ��\n�������������룺");
		input_to("get_new_pass", 1, ob);
		return;
	}
        while(i--){
        	if( pass[i]>='0' && pass[i]<='9' ) j++;
        	if( pass[i]>='A' && pass[i]<='Z' ) k++;
	}
	if( j < 1 || k < 1 ) {
		write("�Բ��������������������ֺ�Ӣ�Ĵ�д��ĸ��\n");
		write("�������������룺");
		input_to("get_new_pass", 1, ob);
		return;
	}
	write("��������һ���µ����룺");
	input_to("confirm_new_pass", 1, ob, crypt(pass, "$1$ShuJian"));
}

private void confirm_new_pass(string pass, object ob, string new_pass)
{
	if( crypt(pass, new_pass)!=new_pass ) {
		write("����������������벢����ͬ������ʹ��ԭ�������롣\n");
		return;
	}
	seteuid(getuid());
	if( !ob->set("password", new_pass) ) {
		write("������ʧ�ܡ�����ʹ��ԭ���룡\n");
		return;
	}

	ob->save();
	write("�������ɹ���\n");
	log_file("static/PASSWD", sprintf("%s %s from %s\n", ctime(time()), ob->query("id"), query_ip_number(this_player())));
}

int help(object me)
{
	write(@HELP
ָ���ʽ : passwd

���ָ������޸�����������롣
HELP
);
	return 1;
}
