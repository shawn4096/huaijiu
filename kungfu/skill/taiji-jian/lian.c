#include <ansi.h>
inherit F_SSERVER;

string perform_name(){ return RED"������"NOR; }

#include "/kungfu/skill/eff_msg.h";

string *name1 = ({ MAG"�ؿڡ�����Ѩ��"HIR, HIG"���ġ���̨Ѩ��"HIR, HIY"�����׵Ѩ��"HIR, HIM"���¡�����Ѩ��"HIR, 
                 HIC"˫�ۡ�����ԨѨ��"HIR, HIB"���¡�ԨҺѨ��"HIR, HIW"�ؿڡ�����Ѩ��"HIR });

int perform(object me, object target)
{
      object wep;
      me = this_player();
      wep = me->query_temp("weapon");
      if( !target ) target = offensive_target(me);
      
      if( !target || !me->is_fighting(target) )
                 return notify_fail("�������־�ֻ����ս���жԶ���ʹ�á�\n");

      if((int)me->query_temp("tjj/chan"))
                 return notify_fail("����������ʹ�á������־���\n");

      if(!living(target))
                 return notify_fail("�������־�ֻ����ս���жԶ���ʹ�á�\n");

      if(!wep || wep->query("skill_type") != "sword" )
                 return notify_fail("�������޽������ʹ�á������־���\n");

      if(me->query_skill_mapped("sword") != "taiji-jian")
                 return notify_fail("����������̫���������޷�ʹ�á������־���\n");

      if(me->query_skill_mapped("parry") != "taiji-jian")
                 return notify_fail("�������̫������Ϊ�мܲ���ʹ�á������־���\n");  

      if( (int)me->query_temp("tjj/lian") )
                 return notify_fail("����������ʹ�á������־���\n");

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

      me->start_perform(7,"�������־�");
      message_vision(CYN"$N΢΢һЦ��ʹ��̫������"+RED+"������"+CYN+"�־����������ӻ�����ת,���ֳֽ��������𣬽��������ǰ����������\n"
                        "��ԣ��籧Բ������"+wep->name()+CYN"δ������Ȼ�������\n"NOR,me,target);
      me->set_temp("tjj/lian",1);
      call_out("perform1", 0, me);
      return 1;
}

int perform1(object me, object target)        
{
      string msg;
      object wep;
      int t_neili,p_neili,i, cost, ap, dp, damage,p;
      wep = me->query_temp("weapon");

      if( !wep 
       || !objectp(wep)
       || wep->query("skill_type") != "sword" ){
           me->delete_temp("tjj/lian");
           return 1;
      }
      if( !target ) target = offensive_target(me);
      if( !target ){ 
          me->delete_temp("tjj/lian");
          return 1;
      }
      if( !present(target->query("id"), environment(me))
       || !me->is_fighting()){
           me->delete_temp("tjj/lian");
           return 1;
      }
      t_neili= target->query("neili");
      p_neili= me->query("neili");
      if ( t_neili > target->query("max_neili")) 
       t_neili = (t_neili-target->query("max_neili")/50);
      if (p_neili > me->query("max_neili"))             
       p_neili=(p_neili-me->query("max_neili")/50);
     
      p = (int)target->query("qi")*100/(int)target->query("max_qi");
      wep = me->query_temp("weapon");
      i = (int)me->query_skill("sword");
      cost = me->query_skill("taiji-jian", 1);
      msg = CYN"$N����"+wep->name()+CYN"������ǰ��������һ���Σ�һ��ɭɭ������ֱ����$n��ͻȻ֮�䣬$N�������֣�����һ������$n��ȥ��\n"NOR;
      ap = me->query("combat_exp")/1000 + p_neili/10 + me->query_con()*10;
      dp = target->query("combat_exp")/1000 + t_neili/10 + target->query_con()*10;
      if (ap < 1) ap = 1;
      if (dp < 1) dp = 1;

      if (random(ap) > dp/2){
           damage =(i + random(i))/2;
           if (damage > 500 ) damage = 500;
           target->receive_damage("qi", damage);
           target->receive_wound("qi", damage/3);
           me->add("neili", cost);
           me->add("jingli", -cost/2);
           msg += HIR"���ֻ����$nһ���Һ���"+wep->name()+HIR"����$n�����ϻ���һ����ɼ��ǵĿ����˿ڣ���Ѫ�������أ���\n"NOR;
           msg += "( $n"+eff_status_msg(p)+" )\n\n";
           if((int)me->query("neili") > 500
            && present(target->query("id"), environment(me)) 
            &&  me->is_fighting(target) 
            &&  living(target)
            &&  living(me)
            &&  me->is_fighting()
            &&  target->is_fighting()
            &&  !target->is_ghost()
            &&  !me->is_ghost()
            &&  me->query_skill_mapped("sword") == "taiji-jian"
            &&  me->query_skill_mapped("parry") == "taiji-jian"
            &&  (string)wep->query("skill_type") == "sword" ){
              me->start_busy(1);
              target->start_busy(1);
              call_out("perform2", 0, me);    
           }
           else{
              me->start_busy(2);
              me->delete_temp("tjj/lian");
           }
      }
      else {         
           me->add("neili", -cost/2);
           me->add("jingli", -cost/10);
           msg += HIY"\n$p���һ�����ã�ȫ������һ�ݣ�˳�����˿�ȥ��\n\n" NOR;
           if( (int)me->query("neili") > 500
            && present(target->query("id"), environment(me)) 
            && me->is_fighting(target) 
            && living(target)
            && living(me)
            && me->is_fighting()
            && target->is_fighting()
            && !target->is_ghost()
            && !me->is_ghost()
            && me->query_skill_mapped("sword") == "taiji-jian"
            && me->query_skill_mapped("parry") == "taiji-jian"
            && (string)wep->query("skill_type") == "sword"){
              me->start_busy(2);
              call_out("perform2", 0, me);    
           }
           else{
              me->start_busy(2+random(2));
              me->delete_temp("tjj/lian");
           }
      }
      message_vision(msg, me, target);
      return 1;
}
              
int perform2(object me, object target)
{
      string msg, name;
      int i, cost, ap, dp, damage,p,p_neili,t_neili;
      object wep;
      
      if( !target ) target = offensive_target(me);
      wep = me->query_temp("weapon");
      if( !wep
       || !objectp(wep)
       || wep->query("skill_type") != "sword" ){
         me->delete_temp("tjj/lian");
         return 1;
      }
      if( !target
       || !present(target->query("id"), environment(me))
       ||  !me->is_fighting()){
         me->delete_temp("tjj/lian"); 
         return 1;
      }
      t_neili=target->query("neili");
      p_neili=me->query("neili");
      if (t_neili > target->query("max_neili")) 
       t_neili =(t_neili-target->query("max_neili")/50);
      if (p_neili > me->query("max_neili"))             
       p_neili=(p_neili-me->query("max_neili")/50);
      p = (int)target->query("qi")*100/(int)target->query("max_qi");
      wep = me->query_temp("weapon");
      name = name1[random(sizeof(name1))]; 
      i = (int)me->query_skill("sword");
      cost = me->query_skill("taiji-jian", 1);
      ap = me->query("combat_exp")/1000 + p_neili/10 + me->query_dex()*10;
      dp = target->query("combat_exp")/1000 + t_neili/10 + target->query_dex()*10;
      if (ap < 1) ap = 1;
      if (dp < 1) dp = 1;

      msg =CYN"$N���ǽ������֣�����ǰ��������ԲȦ���������໤סȫ�����ް�ֿ�϶���������Ž��������ֽ���ס��\n"
              "����������$n�����ߴ�ҪѨ�����⼱��������������δ���\n"NOR;     

      if (random(ap) > dp/2){         
         damage = i * 3/2 + random(i);
         if ( damage > 600 ) damage = 600;
         target->receive_damage("qi", damage);
         target->receive_wound("qi", damage/4);
         me->add("neili", -cost);
         me->add("jingli", -cost/5);
         if( damage < 500 ){
            msg += HIR"��������͡���һ����"+wep->name()+HIR"����$n"+name+"�̳�һ��Ѫ��ģ����Ѫ������\n"NOR;
            msg += "( $n"+eff_status_msg(p)+" )\n\n";
         }
         else {
            msg +=HIR"���ֻ����$nһ���Һ���"+wep->name()+HIR"����$n��"+name+"�Դ���������Ѫ�������أ���\n"NOR;
            msg += "( $n"+eff_status_msg(p)+" )\n\n";
         }
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
          &&  (string)wep->query("skill_type") == "sword"){
            me->start_busy(1);
            target->start_busy(1);
            call_out("perform3", 0, me);    
         }
         else {
            me->start_busy(2);                           
            me->delete_temp("tjj/lian");
         }
      }
      else{         
         me->add("neili", -cost/2);
         me->add("jingli", -cost/5);
         msg += HIR"\nֻ��$pһ������ԶԶ�����˿�ȥ��\n\n"NOR;
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
          &&  (string)wep->query("skill_type") == "sword" ){
            me->start_busy(1);
            call_out("perform3", 0, me);    
         }
         else {
            me->start_busy(2+random(2));
            me->delete_temp("tjj/lian");
         }
      }                
      message_vision(msg, me, target);
      return 1;
}

int perform3(object me, object target)
{
      string msg;
      int i, cost, ap, dp, damage,p,p_neili,t_neili;
      object wep;
      wep = me->query_temp("weapon");
       
      if(!wep
       || !objectp(wep)
       || wep->query("skill_type") != "sword"){
       	 me->delete_temp("tjj/lian");
       	 return 1;
      }
      if(!target ) target = offensive_target(me);
      if( !target
       || !present(target->query("id"), environment(me))
       ||  !me->is_fighting()){
       	 me->delete_temp("tjj/lian");
       	 return 1;
      }
      t_neili=target->query("neili");
      p_neili=me->query("neili");
      if (t_neili > target->query("max_neili")) 
       t_neili=(t_neili-target->query("max_neili")/50);
      if (p_neili > me->query("max_neili"))             
       p_neili=(p_neili-me->query("max_neili")/50); 
      p = (int)target->query("qi")*100/(int)target->query("max_qi");
      wep = me->query_temp("weapon");
      i = (int)me->query_skill ("sword");
      cost = me->query_skill("taiji-jian", 1);
      ap = me->query("combat_exp")/1000 + p_neili/10 + me->query_str()*10;
      dp = target->query("combat_exp")/1000 + t_neili/10 + target->query_str()*10;

      if (ap < 1) ap = 1;
      if (dp < 1) dp = 1;

      msg = CYN"$N�������õ�"+RED+"��Ȧ"+CYN+"Խ��Խ�࣬������ʱ��ȫ������������"+RED+"��Ȧ"+CYN+"֮�У�"+RED+"��Ȧ"+CYN+"��Ȧһ��δ������һ������������"+wep->name()+CYN"\n"
               "��ʹ�ü��죬ȴ˿����������������֮�����������֮�����Ѵ��ڻ�����\n"
            HIW"$n���ӽ�����������"+RED+"��Ȧ"+HIW+"�����Լ������޿��˱ܣ�ֻ��ð��һ���������ֱ�һ�죬��"+RED+"��Ȧ"+HIW+"�����Ļ���ֱ�롣\n"NOR;
               "����"+wep->name()+HIW"��ʹ�ü��죬ȴ˿����������������֮�����������֮�����Ѵ��ڻ�����\n"
            WHT"$n���ӽ�����������"+RED+"��Ȧ"+WHT+"�����Լ������޿��˱ܣ�ֻ��ð��һ���������ֱ�һ�죬��"+RED+"��Ȧ"+WHT+"�����Ļ���ֱ�롣\n"NOR;

      if ( random(ap) > dp/2 ){
          remove_call_out("check_fight");
          call_out("check_fight", 1, me, target);                                 
          me->start_busy(1);
          target->start_busy(random(2)+1);
          damage = i*3/2 + random(i);
          if( damage > 800 ) damage = 800+(damage-800)/20;
          target->receive_damage("qi", damage);
          target->receive_wound("qi", damage/3);
          me->add("neili", -cost*2);
          me->add("jingli", -cost/3);
          msg += HIR"ֻ�����꿦�꼸�����죬$n���ֱ۱���Ȧ��ôһ�ף���ʱ�ʶϣ����������౻���뽣��Ȧ�С�\n"NOR;
          msg += "( $n"+eff_status_msg(p)+" )\n\n"; 
          me->delete_temp("tjj/lian");
      }
      else{         
          me->start_busy(random(1)+2);
          me->add("neili", -cost);
          me->add("jingli", -cost/5);
          msg += HIR"����һ�����죬$nֻ���ؿھ���һ����Ѫ��ӿ��һֻ�ֱ�ȴ��Ȼ��ã�������Ȧ˲ʱ��ʧ��\n"NOR; 
          me->delete_temp("tjj/lian");
      }
      message_vision(msg, me, target);
      return 1;
} 

int check_fight(object me, object target) 
{
      string msg;
      object wep;
      if( !me) return 1;
      if( !target ) target = offensive_target(me);
      wep = me->query_temp("weapon");
      if(!target 
       || environment(me) != environment(target)
       || !present((string)target->query("id"), environment(me))
       || !me->is_fighting(target)
       || !living(target)
       || !living(me)
       || me->is_ghost()
       || !me->is_fighting()
       || !wep
       || !objectp(wep)
       || me->query_skill_mapped("sword") != "taiji-jian"
       || (string)wep->query("skill_type") != "sword"){
          msg = HIY"\n$N�������־�������ϣ��������֣��ս�������������ȫ�����µĴ�С��Ȧ�漴������Ӱ��\n\n"NOR;
          me->delete_temp("tjj/lian");
      }
      else {
          call_out("check_fight", 1, me, target);
          return 1;
      }
      message_vision(msg, me, target);
      return 1;
}
