// $Filename:/cmds/std/retire.c$ generated comment change it if the path was changed
// retire.c ����ϴ��
// by augx@sj 3/15/2002

#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me)
{
	if (me->query("no_pk") || me->query("no_pk_disable"))
		return notify_fail("�㲻���Ѿ�����ϴ������\n");

	if (me->query("pk_time"))
		return notify_fail("���Ѿ����ڽ���,����ܹ�����ϴ�֣�\n");


	if (me->query("combat_exp") < 3000000) {

		CHANNEL_D->do_channel(me,"chat",HIY"�ҽ�����ʽ����ϴ�֣��Ӵ��˳����������ٹ��ʽ���������"NOR);
		me->set("no_pk",me->query("combat_exp"));
		me->save();
		log_file("PLAYER/RETIRE",
			sprintf("%s ��ʼ����ϴ��",me->detail_name()),
			me,
			0,
			1,
			me->query_hidden()
			);
	}
	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : retire

����ϴ�֣��˳��������Ӵ˲��ٲ��뽭��������

���ֻ����ʵս����С��3Mʱʹ�ø����������������ϴ�֣�
�ڵ�һ�����������󣬽���ʽ�˳�������

ע�⣡������������
һ����Ҿ��鳬��3M���Ѿ�������ɱ��������ҵ���Ϊʱ,���޷�ʹ
�ø�ָ�
������ʽ����ϴ�ֺ��������κ���ʽ��������������������Լ���
�����50%�ľ���ֵ��

HELP);
	return 1;
}
