// passwd.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;

	if( me != this_player(1) ) return 0;

	ob = me->query_temp("link_ob");
	if( !ob ) return 0;
	while( ob && ob->is_character() ) ob = ob->query_temp("link_ob");

	write("为了安全起见，请先输入您原来的密码：");
	input_to("get_old_pass", 1, ob);
	return 1;
}

private void get_old_pass(string pass, object ob)
{
	string old_pass;

	old_pass = ob->query("password");
	if( crypt(pass, old_pass)!=old_pass ) {
		write("密码错误！\n");
		return;
	}
	write("请输入新的密码：");
	input_to("get_new_pass", 1, ob );
}

private void get_new_pass(string pass, object ob)
{
	int i = strlen(pass), j = 0, k = 0;
	
	write("\n");
	if (pass=="") {
		write("放弃修改，继续使用原密码！\n");
		return;
	}
	if (i<5) {
		write("密码的长度必须不小于五个字母，\n请重设您的密码：");
		input_to("get_new_pass", 1, ob);
		return;
	}
	if (!LOGIN_D->query("md5") && i>8) {
		write("密码的长度必须不大于八个字母，\n请重设您的密码：");
		input_to("get_new_pass", 1, ob);
		return;
	}
        while(i--){
        	if( pass[i]>='0' && pass[i]<='9' ) j++;
        	if( pass[i]>='A' && pass[i]<='Z' ) k++;
	}
	if( j < 1 || k < 1 ) {
		write("对不起，您的密码必须包含数字和英文大写字母。\n");
		write("请重设您的密码：");
		input_to("get_new_pass", 1, ob);
		return;
	}
	write("请再输入一次新的密码：");
	input_to("confirm_new_pass", 1, ob, crypt(pass, "$1$ShuJian"));
}

private void confirm_new_pass(string pass, object ob, string new_pass)
{
	if( crypt(pass, new_pass)!=new_pass ) {
		write("您两次输入的新密码并不相同，继续使用原来的密码。\n");
		return;
	}
	seteuid(getuid());
	if( !ob->set("password", new_pass) ) {
		write("密码变更失败、继续使用原密码！\n");
		return;
	}

	ob->save();
	write("密码变更成功。\n");
	log_file("static/PASSWD", sprintf("%s %s from %s\n", ctime(time()), ob->query("id"), query_ip_number(this_player())));
}

int help(object me)
{
	write(@HELP
指令格式 : passwd

这个指令可以修改你的人物密码。
HELP
);
	return 1;
}
