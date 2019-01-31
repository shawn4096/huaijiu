#include <ansi.h>

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";
void remove_effect(object target,int damage);
string *songs = ({"����֮��������","�����˷δݸγ�","���뾫ʧ����","������������Ƿ���"});

int perform(object me, object target)
{
      string msg, song;                                   
      int p ,damage;
      song = songs[random(sizeof(songs))];
   
      if( !target ) target = offensive_target(me);
     
      if( !target
       || !target->is_character()
       || !me->is_fighting(target) || !living(target) )
           return notify_fail("�������ܾ���ֻ����ս���жԶ���ʹ�á�\n");
             
      if( objectp(me->query_temp("weapon")) )
           return notify_fail("��������ʹ�á������ܾ�����\n");
      
      if( (int)me->query_skill("qishang-quan",1) < 120 )
           return notify_fail("�������ȭ������죬����ʹ�á������ܾ�����\n");
      
      if(userp(me) && (int)me->query_skill("shenghuo-shengong",1) < 100 )
           return notify_fail("���ʥ���񹦵ȼ�����������ʹ�á������ܾ�����\n");  
      
      if(!me->query_skill("jiuyang-shengong", 1))
      if(userp(me) && me->query_skill_mapped("force") != "shenghuo-shengong")
           return notify_fail("��û��ʥ�����ڹ����޷�ʹ�á������ܾ������й�����\n"); 
    
      if( (int)me->query_con() < 28 )
           return notify_fail("������岻��ǿ׳������ʹ�á������ܾ�����\n");
      
      if( (int)me->query("max_neili") < 1200 )
           return notify_fail("�������̫��������ʹ�á������ܾ�����\n");
      
      if( (int)me->query("neili") < 700 )
           return notify_fail("�������̫���ˣ��޷�ʹ�ó��������ܾ�����\n");   

      if( (int)me->query("jingli") < 700 )
           return notify_fail("��ľ���̫���ˣ��޷�ʹ�ó��������ܾ�����\n");     

      if (me->query_skill_prepared("cuff") != "qishang-quan"
       || me->query_skill_mapped("cuff") != "qishang-quan")
           return notify_fail("�������޷�ʹ�á������ܾ������й�����\n");                                                                                 
      
      if(target->query_temp("qishang"))
           return notify_fail("�Է��Ѿ����ܡ������ܾ������㲻�÷Ѿ��ˣ�\n");
      
      message_vision(HIR"\nͻȻ$N���侫�⣬����������Ƹ�Ǹ衢��ʫ��ʫ��ȭ������"+song+"����\n"+
                        "��������ǰȥ�����һȭ����$n��\n"NOR,me, target);

      me->start_perform(6,"�������ܾ���");

      if (random((int)me->query("combat_exp")) > (int)target->query("combat_exp")/3
       && random((int)me->query_skill("force")) > (int)target->query_skill("force")/3){ 
            target->receive_damage("qi", me->query_skill("force")*2);
            target->receive_wound("qi",me->query_skill("force"));
            me->add("neili", -400);
            me->add("jingli", -50);
            target->start_busy(1);
            if((me->query("neili") + me->query("con")*(20+random(20))) < target->query("neili"))
                 tell_object(me, HIR"��ֻ��"+target->name()+"����������ǿ���㰵����ȭ�ڵĸ������������Ͳ���ȥ��\n"NOR);
            else{
                 damage = target->query_str()/2;
                 damage += target->query_int()/2;
                 damage += target->query_con()/2;
                 damage += target->query_dex()/2;
                 damage /= 4;
                 tell_object(me, HIW"�ڸ�һ����"+target->name()+"������ʱ����㰵������������������ȭ�ڵ������������˹�ȥ��\n"NOR);
                 tell_object(target, HIW"��һ���ۣ�ֻ��"+me->name()+"��ȭ�Ѿ�����������ϣ����ż���˵�����İ���˳�ƴ��˹�����\n"NOR);
                 me->start_perform(7,"�������ܾ���");
                 target->set_temp("qishang", 1);
                 target->add_temp("apply/strength", -damage);
                 target->add_temp("apply/dexerity", -damage);
                 target->add_temp("apply/intelligence", -damage);
                 target->add_temp("apply/constitution", -damage);
                 target->apply_condition("qishang_poison", 10+ target->query_condition("qishang_poison"));
                 target->apply_condition("no_perform", me->query_skill("force", 1)/8);
                 target->start_call_out( (: call_other, __FILE__, "remove_effect", target ,damage :), me->query_skill("force")/2); 
            }
            p = (int)target->query("qi")*100/(int)target->query("max_qi");
            msg = damage_msg(me->query_skill("force"), "����");
            msg += "( $n"+eff_status_msg(p)+" )\n";                
      } 
      else{
            me->start_busy(3);
            me->add("neili", -(100+random(100))); 
            me->add("jingli", -200);             
            msg = "ֻ��$p����һת���Ѿ��Ƶ���$P��󡣶�$Nȴ������ղ��ܿ��ƣ�ͷ��ѣ�Σ�\n";
      }
      message_vision(msg, me, target);
      return 1;
}

void remove_effect(object target,int damage)
{
      if(!target) return;
      target->add_temp("apply/strength", damage);    
      target->add_temp("apply/dexerity", damage);  
      target->add_temp("apply/intelligence", damage);    
      target->add_temp("apply/constitution", damage);  
      target->clear_condition("no_perform");
      target->delete_temp("qishang");
      tell_object(target, HIW"���ڣ������Ǽ��ɰ����ڱ鲼���ȫ���ʼ����ɢȥ�ˡ�\n"NOR);
}
