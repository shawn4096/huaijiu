// chan.c �򹷰���--���־�
// Modify by looklove@SJ 3/16/2001

#include <ansi.h>
inherit F_SSERVER;

string perform_name(){ return HBGRN"���־�"NOR; }
int perform(object me, object target)
{
        string msg;
        object tweapon, weapon;
        int busy, mexp, texp, mlvl, tlvl, x, y, b;

        if( !target ) target = offensive_target(me);

        if( !target
         || !target->is_character()
         || !me->is_fighting(target) )
                return notify_fail("�۲��־���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        weapon = me->query_temp("weapon");
        if( !weapon
          || weapon->query("skill_type") != "stick"
          || me->query_skill_mapped("stick") != "dagou-bang" )
               return notify_fail("�������޷�ʹ�ò��־���\n");

        mexp=me->query("combat_exp");
        texp=target->query("combat_exp");

        mlvl=me->query_skill("dagou-bang",1);
        tlvl=target->query_skill("dodge",1);

        x = me->query_int();
        y = target->query_int();
        b = me->query_skill("bangjue",1);

        tweapon = target->query_temp("weapon");

        if(mlvl < 100 )
                return notify_fail("��Ĵ򹷰�����������죬����ʹ�ò��־���\n");

	if( b < 100 )
		return notify_fail("��Ĵ򹷰���������죬�޷�ʹ�����־���\n");

       	if((int) me->query_skill("huntian-qigong",1) < 100 )
       		return notify_fail("��Ļ��������������㣬�޷�ʹ�����־���\n");

        if((int)me->query("neili") < 500 )
               return notify_fail("������������ˡ�\n");

	if((int)me->query("jingli") < 100 )
		return notify_fail("��ľ�������������ʹ���˾�����\n");

        if((int)me->query("max_neili") < 1000 )
               return notify_fail("�����������֧����ʹ�ô˾�����\n");

        if( target->is_busy()||target->query_temp("dgb/chan"))
               return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");

       	if ( x>y ){
       		busy = 2+(x-y)/2 + random(x-y);
       		busy += random(b/40);
       	}
       	else 	busy = 1+(y-x)/5;
       		busy += random(b/50);

       	if( mexp > texp ) busy += mexp/(texp+1);
       	if( busy > 6) busy = 6;
       	if( mlvl > 350 ) busy += (mlvl-350)/50;

	me->start_perform(3+random(2), "���־�");

        if(wizardp(me)||me->query("id")=="looklove") write(sprintf(HIR"busy=%d\n"NOR,busy));
	x = mexp/1000*mlvl*x;
	y = texp/1000*tlvl*y;

	msg = HBGRN"$N����ʹ�������־���������"+weapon->name()+HBGRN"���һ�Ű�Ӱ��ֱ��$n���˹�ȥ��\n"NOR;
	if( tweapon )
       	msg += HBGRN"ֻ��$n��"+tweapon->name()+HBGRN"�ӵ�����"+weapon->name()+HBGRN"�͸��򶫣�"+tweapon->name()+HBGRN"������"+weapon->name()+HBGRN"�浽����\n"NOR;
       	else
       	msg += HBGRN"ֻ��"+weapon->name()+HBGRN"��Ӱ���Σ����в���$n�����Ѩ�����澫���ޱȡ�\n"NOR;

        if( random(x) > y/3 ){
                msg += HIM "$n���������ʼ���Ӳ�����Ӱ�����������������"+weapon->name()+HIM"��������\n" NOR;
                target->start_busy(busy);
                target->set_temp("dgb/chan", 1);
                call_out("check_fight", 1, me, target, weapon, busy);
        }
        else if( random(x+y) > y ){
                msg += HIM "���$n��ʱ��æ���ң�ʩչ�����������Ҳ�Ѳ���$N�İ�Ӱ��\n" NOR;
                target->start_busy(busy);
                target->set_temp("dgb/chan", 1);
                call_out("check_fight", 1, me, target, weapon, busy);
        }
        else if( random(y) > x/2 ){
                msg += HIW "$n���Ʋ��ã����һ�������Ҵ򣡡�$N�������񼤵�����Ӱ�����ա�\n" NOR;
                me->start_busy(1+random(2));
        }
        else {
                msg += HIW "$n��������Ѱ��������������"+weapon->name()+HIW"��һ�㣬�����Ӱ��ʱ��ʧ�ˡ�\n" NOR;
                me->start_busy(1+random(2));
        }
       	me->add("neili", -200);
        me->add("jingli", -60);
	message_vision(msg, me, target);
	return 1;
}

void check_fight(object me,object target,object weapon,int busy)
{
        int ap, dp, cost;
       
       	cost = me->query_skill("dagou-bang", 1)/2;
       	ap = me->query("combat_exp")/1000 * me->query_skill("dagou-bang",1) * me->query_int();
       	dp = target->query("combat_exp")/1000 * target->query_skill("dodge",1) * target->query_int();
       	if (ap < 1) ap = 1;
       	if (dp < 1) dp = 1;

       	if( !target) return;
       	if( !target->query_temp("dgb/chan")) return;
       	if( ! me
         || ! me->is_fighting(target)
         || weapon != me->query_temp("weapon")
         || me->query_skill_mapped("stick") != "dagou-bang"
         || (int)me->query("neili") < 500 
         || random(ap + dp) < dp
         || busy < 1){
           	target->delete_temp("dgb/chan", 1);
		target->add_busy(1);
           	return;

       }
	me->start_perform(1+random(2), "���־�");
       	me->add("neili", -cost);
       	me->add("jingli", -10);
       call_out("check_fight", 1, me,target,weapon,busy -1);
}

int help(object me)
{
	write(HBGRN"\n�򹷰������־�����"NOR"\n");
	write(@HELP
	������߹��Դ򹷰�֮�������ɣ������������֡�
	��򹷰������־��������Ǻ��߹������ʹ��һ�г���������
	��ʩչ�����������Ҳ�Ѳ��������λð�İ�Ӱ��������ľ�������

	Ҫ��	������� 1000 ���ϣ�
		��ǰ���� 500 ���ϣ�
		�򹷰��ȼ� 100 ���ϣ�
		���������ȼ� 100 ���ϣ�
		�򹷰����ȼ� 100 ���ϣ�
		�����м�Ϊ�򹷰���
HELP
	);
	return 1;
}
