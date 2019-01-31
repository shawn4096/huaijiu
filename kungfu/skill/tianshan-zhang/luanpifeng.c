#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;

string perform_name(){ return HIC"������"NOR; }

int perform(object me, object target)
{
        object weapon;
        int skill,improve;

        if( !target && me->is_fighting() ) target = offensive_target(me);

        if( !target
         || !target->is_character()
         || !me->is_fighting(target) )
                return notify_fail("�������硹ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon = me->query_temp("weapon"))
         || weapon->query("skill_type") != "staff" )
                return notify_fail("���������ȣ��������á������硹����\n");

        if( me->query_temp("xx_luanpifeng"))
                return notify_fail("���ʹ�꡸�����硹��Ŀǰ��Ѫ��ӿ���޷��ٴ����ã�\n");

        if((int)me->query_skill("tianshan-zhang", 1) < 180
         ||(int)me->query_skill("staff", 1) < 180
         ||(int)me->query_str() <=30 )
                return notify_fail("����Ϊ����������δ�����������硹��\n");

        if( me->query_skill("huagong-dafa", 1) < 180 )
                return notify_fail("����ڹ���Ϊ���δ����ʩչֻ���˼�����\n");

        if( me->query_skill_mapped("force") != "huagong-dafa")
                return notify_fail("�����õ��ڹ��롸�����󷨡��ķ���㣣�\n");

        if (me->query_skill_mapped("staff") != "tianshan-zhang"
         || me->query_skill_mapped("parry") != "tianshan-zhang")
                return notify_fail("�������޷�ʹ�á������硹���й�����\n");

        if( me->query("max_neili") <= 2000 )
                return notify_fail("���������Ϊ���㣬����������ʩչ�������硹��\n");

        if( me->query("neili") <= 600 )
                return notify_fail("�����������������������ʩչ�������硹��\n");

        if( me->query("jingli") <= 200 )
                return notify_fail("��ľ������ޣ�������ʩչ�������硹��\n");

        message_vision(HIB"\n$NͻȻ��"+weapon->name()+HIB"���һ��裬���������ڹ�ע���������������У�һʱ��������!\n" NOR, me);

        if(userp(me)){
           me->add("neili", -300);
           me->add("jingli", -50);
           if(weapon->query("rigidity")<10)
                weapon->add("rigidity", 1);
        }
        skill = me->query_skill("staff");
      	improve = skill/5 + random(skill/5);
      	if ( improve > 100 ) improve = 100 + random(improve-100) / 5;

        me->set_temp("xx_luanpifeng", improve);
        me->add_temp("apply/damage", improve);
        me->add_temp("apply/staff", improve);
        me->add_temp("apply/strength", improve);
        call_out("remove_effect", 1,  me, weapon, skill);
        me->start_perform(5, "�������硹");
        return 1;
}

void remove_effect(object me,object weapon,int count)
{
        int i;
        if(!me) return;
        if(! me->is_fighting()
         || !weapon
         || me->query_skill_mapped("staff") != "tianshan-zhang"
         || me->query_skill_mapped("parry") != "tianshan-zhang"
         || count < 1 ){
          i = me->query_temp("xx_luanpifeng");
          me->add_temp("apply/staff", -i);
          me->add_temp("apply/damage", -i);
          me->add_temp("apply/strength", -i);
          me->delete_temp("xx_luanpifeng");
	if (weapon)
		message_vision(HIB"\n$N������֧������"NOR+weapon->name()+HIB"������������\n"NOR, me);
          return;
        }
        else {
          me->start_perform(1,"�������硹");
          call_out("remove_effect", 1, me, weapon, count -1);
        }
}

int help(object me)
{
        write(
@HELP
������
       �������ɣ�����ɽ�ȷ������⹥������һ�������ڹ�ע���������ø����У�
       ���ƺ��һ��裬��������ҽ�,�޼���Ѱ������������
       ʹ��Ҫ����ɽ�ȷ���������180�ȼ��������ȷ����м�Ϊ��ɽ�ȷ���
HELP
        );
        return 1;
}
