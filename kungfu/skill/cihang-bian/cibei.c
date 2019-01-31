#include <ansi.h>
#include <combat.h> 

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

int perform(object me, object target)
{
        string msg,dodge_skill;
        int extra,skill,at,df,i,lmt,damage,p;
        object weapon;
        extra = me->query_skill("cihang-bian",1);

        if( !target ) target = offensive_target(me);

        if( !target
         || !target->is_character()
         || !me->is_fighting(target) )
              return notify_fail("���ȱ��־���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( extra < 160)
              return notify_fail("��Ĵ��б޷���Ϊ̫��,������ʹ�á��ȱ��־�����\n");

        skill = me->query_skill("buddhism",1);

        if( skill < 180)
              return notify_fail("��������ķ��ȼ�����������֧�֡��ȱ��־����� \n");

        if( me->query("shen") < 500000)
              return notify_fail("���ȱ��־��������ޱ�����Ϊ��,��ʦ���Ƕ������°�! \n");

        if( me->query("neili") < 1500 )
              return notify_fail("���������Ϊ���������ȱ��־���\n");

        weapon = me->query_temp("weapon");
        
        if( me->query_skill_mapped("whip") != "cihang-bian" && userp(me))
                return notify_fail("�������޷�ʹ�á��ȱ��־�����\n");

        if( me->query_skill_mapped("parry") != "cihang-bian" && userp(me))
                return notify_fail("�������޷�ʹ�á��ȱ��־�����\n");

        if( !weapon
         || weapon->query("skill_type") != "whip")
              return notify_fail("������û�б������ʹ�á��ȱ��־�����\n");

        msg = RED"ֻ��$N����������ȱ�Ϊ�������е�"+ weapon->name()+RED"�·����������㵹����$n��\n"NOR;
        at = me->query("combat_exp",1) * me->query_skill("cihang-bian", 1)/1000;
        df = target->query("combat_exp", 1)* target->query_skill("dodge", 1)/1000;
             lmt = random((me->query_skill("cihang-bian", 1)- 100)/50)+1;
            if( lmt > 3 ) lmt =3;
            me->set_temp("chb",3);
            me->add("neili",200);
            me->add("jingli",-150);
            for(i=1;i <= lmt;i++){
                 extra = me->query_skill("cihang-bian", 1);
                 me->add_temp("apply/attack",extra/5);
                 me->add_temp("apply/whip",extra/5);
                 COMBAT_D->do_attack(me,target, me->query_temp("weapon"), 1);
                 me->add_temp("apply/attack",-extra/5);
                 me->add_temp("apply/whip",-extra/5);
            }
            me->delete_temp("chb");
            me->start_perform(5,"���ȱ��־���");

        if( random(at + df) > df ){
            damage = me->query("shen")/2000;
            if(damage > 1200) damage = 1200;
            msg += CYN"\n$n������$N���ޱ߷𷨴򶯣��͵ĺ��ˣ�����û��һ˿Ѫɫ...\n"NOR;
            target->add("neili",-damage/2);
            target->receive_damage("qi", damage, me);
            target->receive_wound("qi", damage/3, me);
            p = (int)target->query("qi")*100/(int)target->query("max_qi");
            msg += "( $n"+eff_status_msg(p)+" )\n"; 
            message_vision(msg, me, target);
            weapon = me->query_temp("weapon");        
            message_vision(msg,me,target);
            me->add("neili",-(100 + random(me->query_skill("force"))));
            me->add("jingli",-100);
            me->add("shen",-500-random(100));
            me->start_perform(5,"���ȱ��־���");
        }
        else { 
              dodge_skill = target->query_skill_mapped("dodge");
              if( !dodge_skill ) dodge_skill = "dodge";
              msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
              message_vision(msg, me, target);
              if(!target->is_killing(me->query("id"))){
                 target->kill_ob(me);
                 me->kill_ob(target);
              }
              me->add("neili",-100);
              me->add("jingli",-50);
              me->start_busy(random(2));
              me->start_perform(3,"�ȱ��־�");
        }
        return 1;
}
