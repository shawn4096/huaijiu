// lian.c �������־�

#include <ansi.h>
#include "/kungfu/skill/eff_msg.h";
inherit F_SSERVER;

string *name1 = ({"�ؿڡ�����Ѩ��", "���ġ���̨Ѩ��","�����׵Ѩ��", "���¡�����Ѩ��","˫�ۡ�����ԨѨ��", "���¡�ԨҺѨ��","�ؿڡ�����Ѩ��"});

int perform(object me, object target)
{
      object wep;
      me = this_player();
      wep = me->query_temp("weapon");
      if( !target ) target = offensive_target(me);
      
      if( !target || !me->is_fighting(target) )
                 return notify_fail("�������־�ֻ����ս���жԶ���ʹ�á�\n");
if((int)me->query_temp("tjj/chan"))
return notify_fail(WHT"����������ʹ�á������־���\n"NOR);
      if(!living(target))
                 return notify_fail("�������־�ֻ����ս���жԶ���ʹ�á�\n");
      if(!wep || wep->query("skill_type") != "sword" )
                 return notify_fail("�������޽������ʹ�á������־���\n");
      if(me->query_skill_mapped("sword") != "taiji-jian")
                 return notify_fail("�������޷�ʹ�á������־���\n");
      if(me->query_skill_mapped("parry") != "taiji-jian")
                 return notify_fail("�������޷�ʹ�á������־���\n");  
      if( (int)me->query_temp("tjj/lian") )
return notify_fail(WHT"����������ʹ�á������־���\n"NOR);
      if( (int)me->query_skill("taiji-jian", 1) <120)
                 return notify_fail("���̫��������Ϊ�в�����,�޷�ʹ�á������־���\n");             
      if( (int)me->query_skill("yinyun-ziqi",1) < 120 )
                 return notify_fail("�����������Ϊ��ǳ������ʹ�á������־���\n");
      if( (int)me->query_skill("sword",1) < 120 )
                 return notify_fail("�����������Ϊ�в�����,����ʹ�á������־���\n");  
      if( (int)me->query("max_neili") < 1500 )
                 return notify_fail("���������Ϊ̫��������ʹ�á������־���\n");
      if( (int)me->query("neili") < 800 )
                 return notify_fail("�������̫���ˣ�����ʹ�á������־���\n");  

      message_vision(CYN
"$N΢΢һЦ��ʹ��̫�����С������־����������ӻ�����ת,���ֳֽ��������𣬽��������ǰ������������\n"
"�ԣ��籧Բ������"+wep->name()+"δ������Ȼ�������\n"NOR,me,target);
                me->set_temp("tjj/lian",1);
                call_out("perform1", 0, me);
                return 1;
}

int perform1(object me, object target)        
{
      string msg;
      object wep;
      int i, cost, ap, dp, damage,p;
      me = this_player();
      if( !target ) target = offensive_target(me);
      p = (int)target->query("qi")*100/(int)target->query("max_qi");
      wep = me->query_temp("weapon");
      i = (int)me->query_skill("taiji-jian", 1) +(int)me->query_skill("sword", 1);
      cost = me->query_skill("taiji-jian", 1)/2;
if(!objectp(wep = me->query_temp("weapon")) || wep->query("skill_type") != "sword"){ 
                if(!wep) msg = HIY"$N����������ʧ��Բת��̫����ĻҲ��֮��ɢ��\n"NOR;
else if(!target)
msg = HIY"$N������"+wep->name()+HIY"���һ�ڣ���Բ��һ��������ɢ����̫�����⣮\n"NOR;
else msg = HIY"$N����"+wep->name()+HIY"������̫�����⣬$n����ܲ��Ľ�ĻҲ��֮��ɢ��ѹ����Ȼ���ᣡ\n"NOR;
me->start_busy(1);}
      msg = CYN"$N����"+wep->name()+"������ǰ��������һ���Σ�һ��ɭɭ������ֱ����$n��ͻȻ֮�䣬$N�������֣�����һ������$n��ȥ��\n"NOR;
      ap = me->query("combat_exp")/1000 + me->query("max_neili")/10 + me->query_con()*10;
      dp = target->query("combat_exp")/1000 + target->query("neili")/10 + target->query_con()*10;
      if (ap < 1) ap = 1;
      if (dp < 1) dp = 1;

      if (random(ap)>dp/3)
               {         
                damage = i + random(i)/2;
                target->receive_damage("qi", damage);
                target->receive_wound("qi", damage/3);
                me->add("neili", -cost/2);
                me->add("jingli", -cost/10);
                msg +=HIR"���ֻ����$nһ���Һ���"+wep->name()+"����$n�����ϻ���һ����ɼ��ǵĿ����˿ڣ���Ѫ�������أ���\n"NOR;
                msg += "( $n"+eff_status_msg(p)+" )\n\n";
                if( (int)me->query("neili") > 500
                &&  present(target->query("id"), environment(me)) 
                &&  me->is_fighting(target) 
                &&  living(target)
                &&  living(me)
                &&  me->is_fighting()
                &&  target->is_fighting()
                &&  !target->is_ghost()
                &&  !me->is_ghost()
                &&  me->query_skill_mapped("sword") == "taiji-jian"
                &&  me->query_skill_mapped("parry") == "taiji-jian"
                &&  (string)wep->query("skill_type") == "sword" ) 
                    { me->start_busy(1);
                      target->start_busy(1);
                      call_out("perform2", 0, me);    
                    }
                else                 
                    { me->start_busy(1);
                      target->start_busy(1);                      
                      me->delete_temp("tjj/lian");
                      msg += HIY"$N�������־�������ϣ��������֣��ս�������������ȫ�����µĴ�С��Ȧ�漴������Ӱ��\n"NOR;
                    }
               }
            else
               {         
                me->add("neili", -cost/2);
                me->add("jingli", -cost/10);
                msg += HIY"\n$p���һ�����ã�ȫ������һ�ݣ�˳�����˿�ȥ��\n\n" NOR;
                if( (int)me->query("neili") > 500
                &&  present(target->query("id"), environment(me)) 
                &&  me->is_fighting(target) 
                &&  living(target)
                &&  living(me)
                &&  me->is_fighting()
                &&  target->is_fighting()
                &&  !target->is_ghost()
                &&  !me->is_ghost()
                &&  me->query_skill_mapped("sword") == "taiji-jian"
                &&  me->query_skill_mapped("parry") == "taiji-jian"
                &&  (string)wep->query("skill_type") == "sword" ) 
                    { me->start_busy(1);
                      target->start_busy(1);
                      call_out("perform2", 0, me);    
                    }
                else                 
                    { me->start_busy(1);
                      target->start_busy(1);
                      me->delete_temp("tjj/lian");
                      msg += HIY"$N�������־�������ϣ��������֣��ս�������������ȫ�����µĴ�С��Ȧ�漴������Ӱ��\n"NOR;
                    }
                }
      message_vision(msg, me, target);
      return 1;
}
              
int perform2(object me, object target)
{
      string msg, name;
      int i, cost, ap, dp, damage,p;
      object wep;
      me = this_player();
      if( !target ) target = offensive_target(me);
      p = (int)target->query("qi")*100/(int)target->query("max_qi");
      wep = me->query_temp("weapon");
      name = name1[random(sizeof(name1))]; 
      i = (int)me->query_skill("taiji-jian", 1) + (int)me->query_skill ("sword", 1);
      cost = me->query_skill("taiji-jian", 1)/2;
      ap = me->query("combat_exp")/1000 + me->query("max_neili")/10 + me->query_con()*10;
      dp = target->query("combat_exp")/1000 + target->query("neili")/10 + target->query_con()*10;
      if (ap < 1) ap = 1;
      if (dp < 1) dp = 1;
msg =CYN"$N���ǽ������֣�����ǰ��������ԲȦ���������໤סȫ�����ް�ֿ�϶���������Ž��������ֽ���ס�Ķ�\n"
"��������$n�����ߴ�ҪѨ�����⼱��������������δ���\n"NOR;
"����$n�����ߴ�ҪѨ�����⼱��������������δ���\n"NOR;
      
      if (random(ap) > dp/2)
               {         
                damage = i*2 + random(i);
                target->receive_damage("qi", damage);
                target->receive_wound("qi", damage*5/12);
                me->add("neili", -cost);
                me->add("jingli", -cost/5);
                if( damage < 500 ){
                msg += HIR"��������͡���һ����"+wep->name()+"����$n"+name+"�̳�һ��Ѫ��ģ����Ѫ������\n"NOR;
                msg += "( $n"+eff_status_msg(p)+" )\n\n";}

                else {
                msg += HIR"���ֻ����$nһ���Һ���"+wep->name()+"����$n��"+name+"�Դ���������Ѫ�������أ���\n"NOR;
                msg += "( $n"+eff_status_msg(p)+" )\n\n";}

                if( (int)me->query("neili") > 500
                &&  present(target->query("id"), environment(me)) 
                &&  me->is_fighting(target) 
                &&  living(target)
                &&  living(me)
                &&  me->is_fighting()
                &&  target->is_fighting()
                &&  !target->is_ghost()
                &&  !me->is_ghost()
                &&  me->query_skill_mapped("sword") == "taiji-jian"
                &&  me->query_skill_mapped("parry") == "taiji-jian"
                &&  (string)wep->query("skill_type") == "sword" ) 
                    { me->start_busy(1);
                      target->start_busy(1);
                      call_out("perform3", 0, me);    
                    }
                else                 
                    { me->start_busy(1);
                      target->start_busy(1);                      
                      me->delete_temp("tjj/lian");
msg += HIY"\n$N�������־�������ϣ��������֣��ս�������������ȫ�����µĴ�С��Ȧ�漴������Ӱ��\n\n"NOR;
                    }
                }
      else
               {         
                me->add("neili", -cost);
                me->add("jingli", -cost/5);
                msg += HIY"����$pһ�����Ʒ���ԶԶ�Ķ��˿�ȥ��\n\n"NOR;
                if( (int)me->query("neili") > 500
                &&  present(target->query("id"), environment(me)) 
                &&  me->is_fighting(target) 
                &&  living(target)
                &&  living(me)
                &&  me->is_fighting()
                &&  target->is_fighting()
                &&  !target->is_ghost()
                &&  !me->is_ghost()
                &&  me->query_skill_mapped("sword") == "taiji-jian"
                &&  me->query_skill_mapped("parry") == "taiji-jian"
                &&  (string)wep->query("skill_type") == "sword" ) 
                    { me->start_busy(1);
                      target->start_busy(1);
                      call_out("perform3", 0, me);    
                     }
                else                 
                    { me->start_busy(1);
                      target->start_busy(1);
                      me->delete_temp("tjj/lian");
msg += HIY"\n$N�������־�������ϣ��������֣��ս�������������ȫ�����µĴ�С��Ȧ�漴������Ӱ��\n\n"NOR;
                     }
                }                
      message_vision(msg, me, target);
      return 1;
}

int perform3(object me, object target)
{
      string msg;
      int i, cost, ap, dp, damage,p;
      object wep;
      me = this_player();
      if( !target ) target = offensive_target(me);
      p = (int)target->query("qi")*100/(int)target->query("max_qi");
      wep = me->query_temp("weapon");
      i = (int)me->query_skill("taiji-jian", 1) +(int)me->query_skill ("sword", 1);
      cost = me->query_skill("taiji-jian", 1)/2;
      ap = me->query("combat_exp")/1000 + me->query("max_neili")/10 + me->query_con()*10;
      dp = target->query("combat_exp")/1000 + target->query("neili")/10 + target->query_con()*10;
      if (ap < 1) ap = 1;
      if (dp < 1) dp = 1;

msg = CYN"$N�������õĹ�ȦԽ��Խ�࣬������ʱ��ȫ��������������Ȧ֮�У���Ȧһ��δ������һ������������"+wep->name()+"\n"
"��ʹ�ü��죬ȴ˿����������������֮�����������֮�����Ѵ��ڻ�����\n"
HIW"$n���ӽ�������������Ȧ�����Լ������޿��˱ܣ�ֻ��ð��һ���������ֱ�һ�죬���Ȧ�����Ļ���ֱ�롣\n"NOR;
            "����"+wep->name()+"��ʹ�ü��죬ȴ˿����������������֮�����������֮�����Ѵ��ڻ�����\n"
            WHT"$n���ӽ�������������Ȧ�����Լ������޿��˱ܣ�ֻ��ð��һ���������ֱ�һ�죬���Ȧ�����Ļ���ֱ�롣\n"NOR;
      
      if (random(ap+dp) > dp)
              {         
                call_out("check_fight", 1, me, target);                                 
                me->start_busy(1);
                target->start_busy(random(2)+1);
                damage = i*3 + random(i*2);
                target->receive_damage("qi", damage);
                target->receive_wound("qi", damage/2);
                me->add("neili", -cost*2);
                me->add("jingli", -cost/3);
                msg += HIR"ֻ�����꿦�꼸�����죬$n���ֱ۱���Ȧ��ôһ�ף���ʱ�ʶϣ����������౻���뽣��Ȧ�С�\n"NOR;
                msg += "( $n"+eff_status_msg(p)+" )\n\n"; 
             }
      else
               {         
                me->start_busy(random(2)+1);
                target->start_busy(1);
                me->add("neili", -cost);
                me->add("jingli", -cost/5);
                msg += HIR"����һ�����죬$nֻ���ؿھ���һ����Ѫ��ӿ��һֻ�ֱ�ȴ��Ȼ��ã�������Ȧ˲ʱ��ʧ��\n"NOR;
                msg += "( $n"+eff_status_msg(p)+" )\n\n";          
                me->delete_temp("tjj/lian");
                }
      message_vision(msg, me, target);
      return 1;
} 

int check_fight(object me, object target) 
{
      string msg;
      object wep;
      me = this_player();
      if( !target ) target = offensive_target(me);
      wep = me->query_temp("weapon");
      if(!target) 
msg += HIY"\n$N�������־�������ϣ��������֣��ս�������������ȫ�����µĴ�С��Ȧ�漴������Ӱ��\n\n"NOR;
        
      else if(environment(me) != environment(target))
msg += HIY"\n$N�������־�������ϣ��������֣��ս�������������ȫ�����µĴ�С��Ȧ�漴������Ӱ��\n\n"NOR;

      else if ( !target->is_busy()   &&   me->is_fighting(target) )
         {
          me->delete_temp("tjj/lian");
          msg = HIY"$N�������־�������ϣ��������֣��ս�������������ȫ�����µĴ�С��Ȧ�漴������Ӱ��\n"NOR;
         }                                                

      else if ( !present(target->query("id"), environment(me)) 
      &&   me->is_fighting(target) ) 
          { 
           me->delete_temp("tjj/lian");                
msg += HIY"\n$N�������־�������ϣ��������֣��ս�������������ȫ�����µĴ�С��Ȧ�漴������Ӱ��\n\n"NOR;
           }                                                
        
      else if( !living(target) || !present(target->query("id"),environment(me)) ) 
          { 
           me->delete_temp("tjj/lian");                
msg += HIY"\n$N�������־�������ϣ��������֣��ս�������������ȫ�����µĴ�С��Ȧ�漴������Ӱ��\n\n"NOR;
           } 
        
      else if( !me->is_fighting() || !living(me) || me->is_ghost() ) 
          { 
           me->delete_temp("tjj/lian");                
msg += HIY"\n$N�������־�������ϣ��������֣��ս�������������ȫ�����µĴ�С��Ȧ�漴������Ӱ��\n\n"NOR;
          } 
      

      else if( !objectp(wep) || me->query_skill_mapped("sword") != "taiji-jian"
      || (string)wep->query("skill_type") != "sword" ) 
          { 
           me->delete_temp("tjj/lian");
msg += HIY"\n$N�������־�������ϣ��������֣��ս�������������ȫ�����µĴ�С��Ȧ�漴������Ӱ��\n\n"NOR;
          }
      else {call_out("check_fight", 1, me, target);return 1;}
      message_vision(msg, me, target);
      return 1;
}
