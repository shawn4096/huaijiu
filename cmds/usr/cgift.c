// $Filename:/cmds/usr/cgift.c$ generated comment change it if the path was changed
// YUJ@SJ 2001-11-02
// Modified by LOOKLOVE@SJ ������ݼ��㣬����Ż���
// 2002/4/29
// ��Ϊ��������޸�����

// Exp�� 100K ���Ͽ����޸����ԡ�
#define MIN_EXP 100000
// ʣ��EXP���ʵ���100%��ȥÿ��۳�����
// ��ǰ�޸�ÿ�����ԣ��۳�exp����Ϊ5%
#define RATE 0.9500

inherit F_CLEAN_UP;
#include <ansi.h>

int help();

static mapping gift_desc = ([
	"str":"����",
	"con":"����",
	"dex":"��",
	"int":"����"
]);

static string *gift = keys(gift_desc);

// ͳһ���� by Lklv
string check(object me)
{
	string msg;

	if ((int)me->query("combat_exp") < MIN_EXP)
		msg = HIY"ϵͳ��ʾ��"NOR"��Ǹ����ľ��鲻�� "+MIN_EXP+" ���޷��޸����ԡ�\n";
	if (me->is_ghost())
		msg = HIY"ϵͳ��ʾ��"NOR"��Ǹ�����״̬���ȶ��������޷��޸����ԡ�\n";
	return msg;
}

// yuj �¹�ʽ������ѭ���㷨��
int check_exp(int exp, int num)
{
        while (num--) exp -= exp / 100;
        return exp;
}

int main(object me, string arg)
{
	string msg, from, to;
	int exp, num, newexp, tmpexp;

	if (!me) return 0;
        if (!me->query_temp("cgift")) return notify_fail("����ʹ�û������쵤����ȡ�����������ԵĻ��ᡣ\n");
	if (!arg) return help();

	if ( stringp(msg = check(me)) )
		return notify_fail(msg);

	exp = me->query("combat_exp");

	if (sscanf(arg, "%d %s to %s", num, from, to) == 3){		
		if (member_array(from, gift) < 0)
			return notify_fail("��Ҫ�۳�ʲô�츳��\n");
		if (member_array(to, gift) < 0)
			return notify_fail("��Ҫ����ʲô�츳��\n");
		if (from == to || num<0 )
			return notify_fail("���һ�£�������󣬿����ۻ���\n");
		if(exp<1000000 && from=="int")
			return notify_fail("��ľ���ֵС��1M�����ܽ����Լ��١�\n");
		if (me->query(from) <= 10)
			return notify_fail("���"+gift_desc[from]+"�����ټ����ˡ�\n");
		if ( ((int)me->query(from) - num) < 10)
			return notify_fail("���"+gift_desc[from]+"����"+num+"�������10�㣬�����޸ġ�\n");
		if (me->query(to) >= 30 )
			return notify_fail("���"+gift_desc[to]+"�Ѿ�����30�㣬�����������ˡ�\n");
		if ( ((int)me->query(to) + num) > 30)
			return notify_fail("���"+gift_desc[to]+"����"+num+"��󽫳���30�㣬�����޸ġ�\n");

		switch (me->query("family/family_name")) {
                        case "�һ���":
				if (from == "int" && ( me->query("int") <= 24 || ((int)me->query("int") - num) <24 ) )
					return notify_fail("�һ�����������Ҫ������ 24��\n");
				break;
			case "������":
				if (from == "int" && ( me->query("int") <= 18 || ((int)me->query("int") - num) <18 ) )
					return notify_fail("�����µ�������Ҫ������ 18��\n");
				break;
			case "������":
				if (from == "str" && ( me->query("str") <= 20 || ((int)me->query("str") - num) <20) )
					return notify_fail("�����µ�������Ҫ������ 20��\n");
				if (from == "con" && ( me->query("con") <= 20 || ((int)me->query("con") - num) <20) )
					return notify_fail("�����µ��Ӹ���Ҫ������ 20��\n");
				break;
		}

		write("��ѡ�� "HIY"Y"NOR"���������ȡ����\n");
		input_to("confirm_passwd", me, from, to, num);
		return 1;
	}

	if (sscanf(arg, "check %d", num) == 1){

		if ( num > 80 )
			return notify_fail("�������ֵ����������������Ժϡ�\n");
		// ����۳�exp
		newexp = check_exp(exp,num);
		tmpexp = exp - newexp;

		msg = HIG"��ʾ�����Ҫ�޸� "+num+" �����ԣ����ԼҪ�۳� "+tmpexp+" ��EXP����ʣ "+newexp+" ��EXP��\n"NOR;

		if ( newexp < 95000 )
			msg += HIR"��Ǹ���޸�"+num+"�����Ժ��齫���� "+MIN_EXP+" ��������һ�����޸ļ������ԡ�\n"NOR;
		if (me->query_skill("jinshe-zhangfa",1) || me->query_skill("jinshe-jianfa",1))
			msg += HIR"ע�⣺����޸ı�������20�����߽����ͽ����Ʒ�����ɾ����\n"NOR;
                
                if (me->query_skill("pixie-jian",1))
			msg += HIR"ע�⣺����޸ı�������28����а��������ɾ����\n"NOR;

		if (me->query("zhou/jieyi"))
			msg += HIR"ע�⣺����޸����Ը���25�����һ���������ȭ����ɾ����\n"NOR;

		if (me->query("dali/meet_dy1") && me->query_skill("lingbo-weibu", 1))
			msg += HIR"ע�⣺����޸����Ե���22���貨΢������ɾ����\n"NOR;

		write(msg);
		return 1;
	}
	return help();
}

private void confirm_passwd(string yn, object me, string from, string to, int num)
{
	int exp, newexp, tmpexp;

	if ( yn[0]!='y' && yn[0]!='Y' ) {
		write("��ȡ���˸��޸��������ԵĲ�����\n");
		return;
	}
	// ����۳�exp
	exp = me->query("combat_exp", 1);
	newexp = check_exp(exp,num);
	tmpexp = exp - newexp;

	me->start_busy(1);

	me->add(from, -num);
	me->add(to, num);
	me->add("combat_exp", -tmpexp);

	// �������ƽ����ؼ�
	if ( me->query("str") > 20) {
		me->delete_skill("jinshe-zhangfa");
		me->delete_skill("jinshe-jianfa");
	}
	// �������Ʊ�а����
	if ( me->query("str") > 28) {
		me->delete_skill("pixie-jian");
	}
	// �������ƶ���д��
	if (me->query_skill("literate", 1) > me->query("int") * 10)
		me->set_skill("literate", me->query("int") * 10);

	// ˫�ֻ���Ҫ������ <= 25
	if (me->query("int") > 25){
		me->delete("double_attack");
		me->delete("zhou/jieyi");
		me->delete("zhou/hubo");
                me->delete_skill("kongming-quan");
	}

	// �貨΢��Ҫ������ >= 22
	if ( me->query("int") < 22 ){
		me->delete("dali/meet_dy1");
		me->delete_skill("lingbo-weibu", 1);		
	}

	write("�㽫"+num+"��"+gift_desc[from]+"������"+gift_desc[to]+"�ϣ��㱻�۳��� "+tmpexp+" �㾭�顣\n", me);
        me->delete_temp("cgift");
	me->setup();
	me->save();
	log_file("static/ADJUST",
		me->query("name")+"("+capitalize(geteuid(me))+")"
		+"����"+num+"��"+gift_desc[from]
		+"��"+gift_desc[to]+"�ϣ��۳� "+tmpexp+" �㾭�飬ʣ��"+newexp+"\n",
		me,
		({ me })
	);
	return;
}

int help()
{
	write("��ָ�������޸��������ԡ�\n");
	write("ÿ�������޸Ľ��۳�1% exp��\n");
	write("EXP����"+MIN_EXP+"�����޸����ԡ�\n");
	write("ָ���ʽ��\n");
	write("����۳���ʧ��cgift check <Ҫ�޸ĵĵ���>\n");
	write("�޸����ԣ�cgift <����> <Ҫ�۳����츳> to <Ҫ���ӵ��츳>\n");
	write("���磺��Ҫ��һ�������ӵ������ϣ�������ã�"HIG" cgift 1 str to int "NOR"\n");
	write("�����������Դ�������:����:str,����:con,��:dex,����:int\n");
	write("������ʹ�á�\n");
	write("\n�ر�ע�⣺����ֵС��1M���ܼ������ԡ�\n");
	return 1;
}
