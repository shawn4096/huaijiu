// chuo.c �򹷰���--���־�
// Creat by Looklove@SJ 2001.4.9
// Modified by Looklove@SJ 2001.5.19

#include <ansi.h>
inherit F_SSERVER;

string perform_name(){ return HBWHT"���־�"NOR; }
int perform(object me, object target)
{
        string msg;
        object tweapon, weapon;
        int mexp, texp, mlvl, tlvl, i, j, b, n;

        if( !target ) target = offensive_target(me);

        if( !target
         || !target->is_character()
         || !me->is_fighting(target) )
                return notify_fail("�����־���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        weapon = me->query_temp("weapon");
        if( !weapon
          || weapon->query("skill_type") != "stick"
          || me->query_skill_mapped("stick") != "dagou-bang" )
               return notify_fail("�������޷�ʹ�á����־�����\n");

        mexp=me->query("combat_exp");
        texp=target->query("combat_exp");

        mlvl=me->query_skill("dagou-bang",1);
        tlvl=target->query_skill("dodge",1);

        i = me->query_int();
        j = target->query_int();
        b = me->query_skill("bangjue",1);

        tweapon = target->query_temp("weapon");

        if(mlvl < 120 )
                return notify_fail("��Ĵ򹷰�����������죬����ʹ�á����־�����\n");

	if( b < 120 )
		return notify_fail("��Ĵ򹷰���������죬�޷�ʹ�������־�����\n");

       	if((int)me->query_skill("huntian-qigong",1) < 120 )
       		return notify_fail("��Ļ��������������㣬�޷�ʹ�������־�����\n");

        if((int)me->query("neili") < 600 )
               return notify_fail("�������������\n");

       	if((int)me->query("max_neili") < 2000)
             return notify_fail("��������Ϊ���ڲ���, �����á����־�����\n");

       	if((int)target->query_condition("no_exert") > 10)
             return notify_fail("�Է��Ѿ�����Ĵ��־����У��󵨽����ɣ�\n");

       	n = b /20 + random(b/50)+mlvl/50+random((i+j)/10);
       	if( mlvl > 350 ) n += (mlvl-350)/10;

	if(wizardp(me)) write(sprintf(HIR"n=%d \n"NOR,n));
	me->start_perform(2, "���־�");

	i = mexp/1000*mlvl*i;
	j = texp/1000*tlvl*j;

	msg = HBWHT"$Nʹ���򹷰������־�����"+weapon->name()+HBWHT"�������ϣ��������ֱ��$n�����к���\n"NOR;

        if( random(i) > j/2 ){
                msg += HBWHT"$n�������˼�����������һ�����ֲ�������"+weapon->name()+HBWHT"�͵Ĵ���ҪѨ��\n"NOR;
                msg += HBCYN"���$n��ʱ��ɫ�԰ף��о�������Ϣ���ң�ͷ�ؽ��ᡣ\n"NOR;
                target->start_busy(1+random(2));
                target->set_temp("dgb/chuo", n);
                target->apply_condition("no_force",n);
        }
        else {
                if (tweapon) msg += HBWHT"$n���һ������æ������"+tweapon->name()+HBWHT"��"+weapon->name()+HBWHT"��һ����\n"NOR;
                else msg += HBWHT "$n���а��в��ã������������������������ܹ���"+weapon->name()+HBWHT"�����ơ�\n" NOR;
		if (random(mexp)>texp/2){
                	msg += WHT "����$N�����ϵ�$n�д�һ�У�����"+weapon->name()+WHT"һת���Ĵ�$n�Ľ��ס�\n" NOR;
                	msg += WHT ""+weapon->name()+WHT"����������$n�Ѿ����޿ɱܣ���ͨһ��Ӧ��������\n" NOR;
                	target->apply_condition("no_exert",n*3/2);
                	target->start_busy(2+random(2));
                }
                me->start_busy(1+random(2));
        }
	message_vision(msg, me, target);
	me->add("neili",-200);
	return 1;
}

int help(object me)
{
	write(HBWHT"\n�򹷰������־�����"NOR"\n");
	write(@HELP
	�򹷰���ʽ�쳣���ɺ�ɨ���򣬴ˡ����־�����������
	���������в��������Ϣ���֮ҪѨ��һ�����У�����ס��
        ��֮��Ϣ��·��һ��ʱ����ʹ������Ϣ���Ҷ��������е�����

	Ҫ��	������� 2000 ���ϣ�
		��ǰ���� 600 ���ϣ�
		�򹷰��ȼ� 120 ���ϣ�
		���������ȼ� 120 ���ϣ�
		�򹷰����ȼ� 120 ���ϣ�
		�����м�Ϊ�򹷰���
HELP
	);
	return 1;
}