// guifei ��������
// created by olives@SJ
/*
     ���������΢����������Ť�����㷴�ߣ������С����ȥ������������ܣ�
�����˳�Ʒ�������������§ס������ͷ�������־�����ס��ذ�ף������׼��
�������ģ�Ц���������ǵ�һ�У����������������������ס�ˡ���

*/
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
#include <combat_msg.h>

int perform(object me, object target)
{
        object weapon;
        string msg;
  
        if(!target) target = offensive_target(me);

        if(!target
        || !target->is_character()
        || !me->is_fighting(target) )
                return notify_fail("������������ֻ����ս��ʱʹ�ã�\n");

        if(me->query("family/master_id")!="hong antong")
                return notify_fail("������������ֻ�а��˽���������ã�\n");

        if(!objectp(weapon=me->query_temp("weapon"))
        || weapon->query("skill_type") != "dagger")
             return notify_fail("������û��ذ�ף����ʹ�á�������������\n");
	
        if((int)(me->query("dex")+me->query_skill("dodge",1)/10) < 30 )
                return notify_fail("����������ʹ�á����������������»��˵��Լ���\n");

        if((int)me->query_skill("tenglong-bifa", 1) < 150 )
                return notify_fail("�������ذ������������������ʹ�á�������������\n");
	if((int)me->query_skill("shenlong-tuifa",1) < 150)
		return notify_fail("��������ȷ���������������ʹ�á�������������\n");
	
        if(me->query_skill_mapped("dagger") != "tenglong-bifa")
                return notify_fail("ֻ��ʹ������ذ��ʱ����ʹ�á�������������\n");

	if(me->query_skill_mapped("leg") != "shenlong-tuifa"
	|| me->query_skill_prepared("leg") != "shenlong-tuifa")
		return notify_fail("������û������׼�����޷�ʹ�á�������������\n");
		
        if( (int)me->query_skill("dulong-dafa", 1) < 150 )
                return notify_fail("��Ķ����󷨹������㣬�����á�������������\n");

        if((int)me->query("jingli", 1) < 800)
                return notify_fail("�����ھ������㣬����ʹ�á�������������\n");

        if((int)me->query("neili", 1) < 1500)
                return notify_fail("�������������㣬����ʹ�á�������������\n");

        if(me->query("gender") == "����" )
                return notify_fail("����Ů����ô��ʹ�á������������أ�\n");

        if( me->query_skill_mapped("force") != "dulong-dafa")
                return notify_fail("��������ʹ�õ��ڹ�ͬ�������໥�ִ�������ʹ�á�������������\n");

        
        msg = HIR"$N��$n��������֮����ƴ��ȫ��ʹ���շ��˲���֮��������������������"NOR;
        msg += MAG"\n$N����΢����������Ť�����㷴�ߣ���$nС����ȥ��\n"NOR;
  	me->receive_damage("neili",500);
  	me->receive_damage("jingli",200);
        message_vision(msg,me,target);
        me->set_temp("sld/pfm/guifei",1);
        weapon->unequip();
        COMBAT_D->do_attack(me,target,0,TYPE_SUPER);
        weapon->wield();
        me->delete_temp("sld/pfm/guifei");
        me->start_busy(2+random(2));
        me->start_perform(2+random(2),"������������");
	return 1;
}

