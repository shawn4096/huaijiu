// ������ӿ
// By River 
// Modify By River@SJ 2000.2.22
#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;
string *xue_name = ({ 
"�͹�Ѩ","����Ѩ","����Ѩ","��ԪѨ","����Ѩ","�м�Ѩ","�н�Ѩ","��ͻѨ","�ٻ�Ѩ",
"����Ѩ","����Ѩ","���Ѩ","�Ϲ�Ѩ","��ԨѨ","�쾮Ѩ","��ȪѨ","����Ѩ","����Ѩ",
}); 

int perform(object me, object target)
{
        string msg,dodge_skill;
        int i,j,busy,exp,texp,skill,tskill,p;
        object weapon;
        if( me->query("gender") =="����"){
           i = me->query_skill("xuantie-jianfa", 1)/4;
           j = me->query_skill("sword", 1)/4;
        }
        else {
           i = me->query_skill("xuantie-jianfa", 1)/6;
           j = me->query_skill("sword", 1)/6;
        }
        weapon = me->query_temp("weapon");

        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("���������ġ�������ӿ��ֻ����ս���жԶ���ʹ�á�\n");

        if( !weapon || weapon->query("skill_type") != "sword")
                return notify_fail("�����ʹ����������ʹ�á�������ӿ����\n");

        if((int)me->query_skill("xuantie-jianfa", 1) < 130 )
                return notify_fail("�������������������죬ʹ������������ӿ��������\n");

        if((int)me->query_skill("yunu-xinjing", 1) < 130 )
                return notify_fail("�����Ů�ľ��ȼ���������ʹ������������ӿ��������\n");

        if((int)me->query_skill("force") < 180 )
                return notify_fail("����ڹ��ȼ�����������ʹ�á�������ӿ����\n");

        if((int)me->query_str() < 33 )
                return notify_fail("�������������ǿ����ʹ������������ӿ������\n");

        if( target->query_temp("xtjf/haichao"))
                return notify_fail(target->name()+"���Թ˲�Ͼ������Է��ĵؽ�����\n");

        if( me->query_skill_mapped("sword") != "xuantie-jianfa" && userp(me))
                return notify_fail("�������޷�ʹ�á�������ӿ����\n");

        if( me->query_skill_mapped("parry") != "xuantie-jianfa" && userp(me))
                return notify_fail("�������޷�ʹ�á�������ӿ����\n");

        if((int)me->query_temp("xinjing")) 
                return notify_fail("������ʹ�á��ľ����־���\n");

        if((int)me->query("max_neili") < (me->query_skill("force")+j+200) )
                return notify_fail("����������̫����ʹ������������ӿ����\n");      
        if( me->query("env/��������") != "����" ){
         message_vision(HIB"\n$N΢Ц��������е�"+weapon->query("name")+HIB"������죬������ᣬ����Ȼ�����������֮������$nϯ���ȥ��\n"NOR,me,target);
         me->add_temp("apply/sword", i);
         me->add_temp("apply/attack", j);
         me->set_temp("xtjf_pfm", 1);
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
         if (present(target,environment(me)) && me->is_fighting(target))
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
         if (present(target,environment(me)) && me->is_fighting(target)){
          if( random(me->query("combat_exp",1)) > target->query("combat_exp", 1)/3)
            COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
          else
            COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
         }
         me->add_temp("apply/sword", -i);
         me->add_temp("apply/attack", -j);
         if(userp(me))
            me->add("neili", -(me->query_skill("force")));
         else
            me->add("neili", -200);
         me->add("jingli", -150);
         me->delete_temp("xtjf_pfm");
         me->start_perform(5,"��������ӿ��");
        }
        if((int)me->query_skill("xuantie-jianfa", 1) > 150
         &&(int)me->query("neili", 1) > (me->query_skill("force")+j)
         && objectp(target)
         && present(target,environment(me))
         && me->is_fighting(target)
         && me->query("env/��������") !="��ӿ"){
         if( me->query("env/��������") == "����")
          message_vision(HIB"\n$N��"+weapon->query("name")+HIB"Ю���˳�ӿ֮�ƣ������γ�һ����ת�����У���$n���ֹ�ȥ��\n"NOR,me,target);
         else
          message_vision(HIB"\n������$N��"+weapon->query("name")+HIB"Ю���˳�ӿ֮�ƣ������γ�һ����ת�����У���$n���ֹ�ȥ��\n"NOR,me,target);
         if( random(me->query("combat_exp", 1)) > target->query("combat_exp",1) /2
          || me->query("combat_exp", 1) > target->query("combat_exp", 1)*10 
          || !living(target)){
             message_vision(HIR"���$nȫ���������γɵ������������ţ�ֻ�����������ݺ��ξ��ˣ�����ײײ��\n"NOR,me,target);
             skill = me->query_skill("xuantie-jianfa", 1);
             tskill = target->query_skill("dodge", 1);
             exp = me->query("combat_exp", 1);
             texp = target->query("combat_exp", 1);
             busy= 4 + random(skill)/100;
             if( busy > 8) busy= 8;
             if( exp > texp){
              p = texp/100* tskill;
              if( p < 1 ) p = 1;
              busy = busy * exp/100 * skill/p;
             }
              if( busy > 15) busy = 15;
             if( me->query("env/��������") == "����")
               target->start_busy(busy);
             else 
               target->start_busy(2 + random(2));
             target->set_temp("xtjf/haichao", 1);
             me->add("neili", -i*3);
             if (present(target,environment(me)) && me->is_fighting(target))
             COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
             me->start_perform(4, "��������ӿ��");
             call_out("remove_effect", 1, me, target);
         }
         else {
              me->start_busy(random(2));
              me->start_perform(3,"��������ӿ��");
              me->add("neili", -100);
              dodge_skill = target->query_skill_mapped("dodge");
              if( !dodge_skill ) dodge_skill = "dodge";
              msg = SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
              message_vision(msg, me, target);
         }
        }
        return 1;
}

void remove_effect(object me, object target)
{
        if( !me) return;
        if( objectp(target) && !me->is_fighting(target)){
          target->delete_temp("xtjf");
          return;
        }
        if( objectp(target)
         && me->is_fighting(target)
         && !target->is_busy()
         && random(2) == 1
         && me->query_temp("weapon")
         && me->query_skill("xuantie-jianfa", 1) > 180
         && me->query("env/��������") != "��ӿ" ){
          target->delete_temp("xtjf");
          call_out("perform2", 1, me, target);
          return;
        }
        call_out("remove_effect", 1 ,me ,target);
}

int perform2(object me,object target)
{
        string msg, dodge_skill,name;
        object weapon = me->query_temp("weapon");        
        int p;
        
        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("���Ѿ����ü���ʹ�á�������ӿ���ˡ�\n");

        if( !weapon || weapon->query("skill_type") != "sword")
                return notify_fail("�����ʹ���������ܼ���ʹ�á�������ӿ����\n");

        if( me->query_skill_mapped("sword") != "xuantie-jianfa" && userp(me))
                return notify_fail("���޷�����ʹ�á�������ӿ����\n");

        if( me->query_skill_mapped("parry") != "xuantie-jianfa" && userp(me))
                return notify_fail("���޷�����ʹ�á�������ӿ����\n");

        if((int)me->query("neili") < 1000)
                return notify_fail("������̫�����޷�����ʹ����������ӿ����\n");

        if((int)me->query("jingli") < 500 )
                return notify_fail("�㾫��̫�����޷�����ʹ����������ӿ����\n");

        if( me->query("gender")=="����" )
         p = me->query_skill("force") / 6;
        else
         p = me->query_skill("force") / 8;

        name = xue_name[random(sizeof(xue_name))];
        msg =HIB"\n$n�ò����׻���������$N����Ʈ����ת�˼�ת���Ʋ�����������һ������$n��"RED+name+HIB"��\n"NOR;
        if( me->query_kar()/2 > random(target->query_kar())){
           msg += CYN"$n�پ���ǰһ���Ի�һʱ���������ϵ�"RED+name+CYN"�ѱ�"+weapon->name()+CYN"���С�\n"NOR;
           message_vision(msg, me, target);
           target->add_temp("apply/attack", -p/2);
           target->add_temp("apply/dodge", -p/2);
           target->add_temp("apply/parry", -p/2);
           target->set_temp("xtjf/haichao", 1);
           if( random(5) == 1){
            target->apply_condition("no_exert", 1+ random(2));
            target->set_temp("xtjf/exert", 1);
            tell_object(me,MAG"����"RED+name+MAG"�����У�"+target->name()+"��ʱ�޷�ʩ���ڹ���\n"NOR);
           }
           else { 
            target->apply_condition("no_perform", 1+random(2));
            target->set_temp("xtjf/perform", 1);
            tell_object(me,YEL"����"RED+name+YEL"�����У�"+target->name()+"��ʱ�޷�ʩ���⹦��\n"NOR);
           }
           me->add("neili", - p * 6);
           me->add("jingli", - p * 2);
           call_out("check_fight", 1, me, target, weapon, p );
        }
        else {
               me->start_busy(random(2));
               me->add("neili", -100);
               dodge_skill = target->query_skill_mapped("dodge");
               if( !dodge_skill ) dodge_skill = "dodge";
               msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
               message_vision(msg, me, target);
        }
        me->start_perform(4,"��������ӿ��");
        return 1;
}

void check_fight(object me,object target,object weapon, int p)
{
        if( !target) return;
        if( ! me 
         || ! me->is_fighting("target")
         || ! me->query_temp("weapon")
         || weapon->query("skill_type") != "sword"
         || ! present(target,environment(me))
         || me->query_skill_mapped("sword") != "xuantie-jianfa"){
            target->add_temp("apply/attack", p/2);
            target->add_temp("apply/dodge", p/2);
            target->add_temp("apply/parry",p/2);
            if( target->query_temp("xtjf/perform"))
            target->clear_condition("no_perform");
            if( target->query_temp("xtjf/exert"))
            target->clear_condition("no_exert");
            target->delete_temp("xtjf");
            message_vision(HIW"\n$N���������˾��������λָ���ԭ�ȵĽýݡ�\n"NOR, target);
            return ;
        }
        else {
           call_out("check_fight", 1, me, target, weapon, p );
           target->add("neili", - random(me->query_skill("sword")));
           if(target->query("neili") < 0 ) target->set("neili", 0);
        }
}
