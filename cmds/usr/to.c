// to.c

// inherit F_CLEAN_UP;
// Don't want this command be cleaned up while typing long string.

int help(object);

int main(object me, string arg)
{
	if (!arg) return help(me);
	if (!wiz_level(me)) {
		string cmd;

		if (sscanf(arg, "%s ", cmd)!=1) cmd = arg;
		switch(cmd) {
			case "say":
			case "tell":
			case "reply":
			case "describe": break;
			default: return help(me);
		}
	}
	me->edit( (: call_other, this_object(), "do_to" , me, arg :) );
	return 1;
}

void do_to(object me, string arg, string str)
{
	seteuid(getuid());
	str = str[0..<2];
	if (strlen(str) > 800) {tell_object(me, "����̫����\n"); return;}
	if(arg) me->force_me(arg + " " + str);
	else me->force_me(str);
}

int help(object me)
{
write(@HELP
ָ���ʽ : to <ָ��>

����һ������������ϵ�����, <ָ��>ֻ����
say , tell , describe , reply��
���� : 
 to say
 �����뿪�� '.'��ȡ�������� '~q'��ʹ���ڽ��б༭���� '~e'��
 ����������������������������������������������������������
 ������̽��� : ˹ŵ��
 ���������߷��������� : Xiaoyao
 ��������������㲿���� : ���Ź�
 ������ߴ�첿���� : �̱̱�
 .

�����өĻ�ϵĽ������ :

��˵������������̽��� : ˹ŵ��
���������߷��������� : Xiaoyao
��������������㲿���� : ���Ź�
������ߴ�첿���� : �̡̱̱�
HELP
    );
    return 1;
}
