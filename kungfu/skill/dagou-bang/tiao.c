// tiao.c �򹷰���--���־�
// Creat by looklove@SJ 3/17/2001

#include <ansi.h>
inherit F_SSERVER;

string perform_name(){ return HBMAG"���־�"NOR; }
int perform(object me, object target)
{
        string msg;
        object tweapon, weapon;
        int busy, mexp, texp, mlvl, tlvl, i, j, b;

        me->clean_up_enemy();
        target = me->select_opponent();
        
        if( !target ) target = offensive_target(me);

        if( !target
         || !target->is_character()
         || !me->is_fighting(target) )
                return notify_fail("�����־���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        weapon = me->query_temp("weapon");
        tweapon = target->query_temp("weapon");
        
        if( !weapon 
          || weapon->query("skill_type") != "stick"
          || me->query_skill_mapped("stick") != "dagou-bang" ) 
               return notify_fail("�������޷�ʹ�����־���\n");

        if (!tweapon)
                return notify_fail("�Է�û��ʹ���κα��������޷�ʹ�á����־�����\n");

        mexp=me->query("combat_exp");
        texp=target->query("combat_exp");
        if( texp < 100 ) texp = 100;
        
        mlvl=me->query_skill("dagou-bang",1);
        tlvl=target->query_skill("dodge",1);
        
        i = me->query_int();
        j = target->query_int();
        b = me->query_skill("bangjue",1);
        
        if(mlvl < 160 )
                return notify_fail("��Ĵ򹷰�����������죬����ʹ�����־���\n");
	
	if( b < 160 ) 
		return notify_fail("��Ĵ򹷰���������죬�޷�ʹ�����־���\n");
        
       	if((int)me->query_skill("huntian-qigong",1) < 160 )
       		return notify_fail("��Ļ��������������㣬�޷�ʹ�����־���\n");

        if((int) me->query("neili") < 800 )
               return notify_fail("�������������\n");
       	
       	busy = random( b/50 );
       	if ( busy < 0 ) busy = 1 ;
       	if( mlvl > 350 ) busy = busy + (mlvl-350)/5;
	if (busy >4) busy = 4;
        
        if(wizardp(me)) write(sprintf(HIR"busy=%d \n"NOR,busy));
	
        msg = HBMAG"$N���������"+weapon->name()+HBMAG"һת�����һ�����𣡡���ʹ�������־�������ס"+tweapon->name()+HBMAG"����������\n"NOR;
        me->start_perform(2,"���־�");

        mexp = mexp/1000*mlvl*i;
        texp = texp/1000*tlvl*j;
        
        if( random(mexp) > texp/4)
        {
		msg += HBMAG"$nֻ��"+tweapon->name()+HBMAG"�������ַɳ���һ�����ղ�ס�����б����������˳�ȥ��\n"NOR;
		target->start_busy(busy);
		me->add("neili",-300);
			
		if (random(2)!=1){
			msg += HIY"$N��������Ծ�����࣬������е�"+tweapon->name()+HIY"�������С�\n"NOR;
                	tweapon->move(me);
		}
		else {
			msg += HBMAG"$n���������"+tweapon->name()+HBMAG"�������ӣ���$N"+weapon->name()+HBMAG"��һ��������ֻ����"+tweapon->name()+HBMAG"����һ�ߡ�\n"NOR;
                	tweapon->move(environment(me));
		}
        }
        else
        {
                me->add("neili",-300);
                msg += HIG"$n��������б����һ������"+weapon->name()+HIG"���Լ���"+tweapon->name()+HIG"�ϵ��˿�ȥ��\n"NOR;
        }
        message_vision(msg, me, target);
        return 1;
}

int help(object me)
{
	write(HBMAG"\n�򹷰������־�����"NOR"\n");
	write(@HELP
	�򹷰���������������һ���ٵ�֮���ݲ����˵У�����Ա���
	�������ֱֳ�������ʹ�ôˡ����־������ɽ����ֱ�����ɻ�
	�������Լ����С�
	
	Ҫ��	��ǰ���� 800 ���ϣ�
		�򹷰��ȼ� 160 ���ϣ�
		���������ȼ� 160 ���ϣ�
		�򹷰����ȼ� 160 ���ϣ�
		�����м�Ϊ�򹷰���
		���������ޱ���������Ч����
HELP
	);
	return 1;
}