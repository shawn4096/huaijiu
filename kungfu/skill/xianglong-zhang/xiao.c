// By Snowman@SJ
// modified by snowman 20/06/2000
// modify by looklove 2001.5.22 update help

#include <ansi.h>

inherit F_SSERVER;

void check_fight(object me,object target);
string perform_name(){ return HIY"����Х"NOR; }

int perform(object me, object target)
{
	int skill = me->query_skill("xianglong-zhang",1)/3;

        if(!target ) target = offensive_target(me);

        if(!target || !me->is_fighting(target) )
                return notify_fail("ֻ����ս����ʹ�á�\n");
        if( objectp(me->query_temp("weapon")) )
                return notify_fail("�������ֲ���ʹ�á�����Х����\n");
        if((int)me->query("neili") < me->query_skill("strike")+400 )
                return notify_fail("�������������\n");
        if((int)me->query_temp("xlz/xiao") )
                return notify_fail("���Ѿ���ʼ�˽���Х��\n");
        if((int)me->query_skill("xianglong-zhang", 1) < 100 )
                return notify_fail("��Ľ���ʮ���ƻ�������죬ʹ����������Х������\n");
        if((int)me->query_skill("force") < 200 )
                return notify_fail("����ڹ��ȼ�������ʹ����������Х������\n");
        if(me->query_temp("htqg/powerup"))
                return notify_fail("������ʹ�û���������\n");
        if((int)me->query_str() < 30 )
                return notify_fail("�������������ǿ����ʹ����������Х������\n");
        if( (int)me->query_skill("huntian-qigong", 1) < 100 )
                return notify_fail("��Ļ��������ȼ���������ʹ����������Х��������\n");
        if (me->query_skill_mapped("force") != "huntian-qigong")
                return notify_fail("����ʹ�õ��ڹ����ԡ�\n");
        if (me->query_skill_prepared("strike") != "xianglong-zhang"
         || me->query_skill_mapped("strike") != "xianglong-zhang"
         || me->query_skill_mapped("parry") != "xianglong-zhang")
                return notify_fail("�������޷�ʹ�á�����Х����\n");

        me->add("neili", -(me->query_skill("strike", 1)+200));
        me->add("jingli", -50);
        message_vision(YEL "\n$N�����Х����ʹ����ʮ���ƾ�Ȼ���������������ɵ���ԴԴ������������ɽ�������ѹ��$n��\n\n" NOR, me, target);
        if(me->query("jiali") < 50)
        	me->set("jiali", 50);
        me->set_temp("xlz/xiao", skill);
        me->add_temp("apply/attack", skill);
        me->add_temp("apply/strength", skill/3);
        call_out("check_fight", 1 , me, (skill/3 > 10?skill/3:10));
        if( me->is_fighting() ) me->start_busy(1);
        return 1;
}

void check_fight(object me, int i)
{
        int j;

        if( !me ) return;
        if( !intp(j = me->query_temp("xlz/xiao")) ) return;

        i--;
        if( !me->is_fighting()
        ||  i < 1
        ||  me->query_temp("weapon")
        ||  me->query_temp("secondary_weapon")
        ||  me->query_skill_prepared("strike") != "xianglong-zhang"
        ||  me->query_skill_mapped("force") != "huntian-qigong"
        ||  me->query_skill_mapped("parry") != "xianglong-zhang") {
        	me->add_temp("apply/attack", -j);
        	me->add_temp("apply/strength", -j/3);
        	me->delete_temp("xlz/xiao");
        	me->add("neili", -j );
        	me->start_perform(2, "������Х��");
        	message_vision(YEL "\n$N��Х��ϣ��������������˲��ٵ�����������ʮ���Ƶ�����Ҳ�ָ�Ѱ���ˡ�\n" NOR, me);
        	return;
        }
	me->start_perform(1, "������Х��");
        call_out("check_fight", 1, me, i);
}
int help(object me)
{
	write(HIY"\n�����ơ�����Х����"NOR"\n");
	write(@HELP
	��ʱ���ڿ�������������������ͬʱ���������޴�
	Ҫ��	��ǰ���� �����Ʒ���Ч�ȼ�+400��
		�����Ƶȼ� 100 ���ϣ�
		���������ȼ� 100 ���ϣ�
		���� 30 ���ϣ�
		�����м�Ϊ�����ơ�
HELP
	);
	return 1;
}