// kurong-changong's perform jiuchong
//������ 
// COOL@SJ 19990909
inherit F_SSERVER;

#include <ansi.h>
#include <combat.h>
#include "/kungfu/skill/eff_msg.h";

int perform(object me, object target)
{    
      int i;
      if (me->query_temp("jiuchong_ok")){
         if( !target ) target = offensive_target(me);
         if( !target 
         || !target->is_character()
         || !me->is_fighting(target) || !living(target) )
                return notify_fail("�������졹ֻ����ս����ʹ�á�\n");
      }
      if( objectp( me->query_temp("weapon")) )
                return notify_fail("ֻ�п��ֲ���ʩչ�������졹��\n");
      
      if( (int)me->query_skill("kurong-changong", 1) < 120 )
                return notify_fail("��Ŀ���������Ϊ�������޷�ʹ�á������졹���У�\n");

      if (me->query_skill_mapped("force") != "kurong-changong")
                return notify_fail("�������ڹ����ԣ�\n");

      if (me->query_skill_mapped("parry") != "kurong-changong")
                return notify_fail("������ÿ���������Ϊ�мܣ�����ʹ�á������졹���С�\n");

      if (me->query_skill_prepared("finger") == "yiyang-zhi")
                 return notify_fail("�㲻����ͬʱʹ��һ��ָ�񹦣�\n");

      if( (int)me->query("neili") < 500 )
                return notify_fail("�������̫���ˣ��޷�ʹ�ó��������졹���У�\n");   
    
      if (me->query_skill_prepared("strike") != "kurong-changong" )
                 return notify_fail("�����ʹ�ÿ���������Ϊ����Ʒ�����\n");
                 
      if( (int)me->query("max_neili") < 3000 )
                return notify_fail("���������Ϊ��ô�����ʹ�á������졹���У�\n");   
                                                                                
/*
      if( me->query_temp("pf_ku"))
                return notify_fail("���������á��ݡ��ִ󷨣�\n");

      if( me->query_temp("pf_rong"))
                return notify_fail("���������á��١��ִ󷨣�\n"); 
*/
      
      if (!me->query_temp("jiuchong_ok"))
      if( me->query_temp("pf_jiuchong"))
                return notify_fail("���������á������졹���У�\n"); 
     
      i=(int)((me->query_skill("kurong-changong",1)-40)/20);
      if (i > 9) i = 9;  
      me->start_perform(9,"�������졹");
      if (me->query_temp("jiuchong_ok")){
          me->delete_temp("jiuchong_ok");
          remove_call_out("jiuchong_back");
          call_out("jiuchong_fight", 0, me, target,0);
      }
      else {  
         tell_object(me, BLU"\n������һ������ʼ����������׼������"RED"������"BLU"���У�\n"NOR);                         
         me->start_busy(1);
         me->set_temp("pf_jiuchong",i); 
         call_out("jiuchong_fight",  9, me, target,0);
      }
      return 1;
}

void jiuchong_back(object me)
{       
       if (!me) return;
       tell_object(me, RED"\nʱ��һ����������ȫ��ľ�������������ɢȥ��\n"NOR);    
       me->delete_temp("jiuchong_ok");
       me->delete_temp("pf_jiuchong");
       me->start_perform(4,"�������졹");
}

int jiuchong_fight(object me, object target, int count)
{
      string msg,dodge_skill,*limbs;
      int damage,p,j;
      int daley_time;
                  
      string *targ=({"���·�","��ǰ��","�����","ͷ���Ϸ�","����","�Ҳ���","�����","���·�","���Ϸ�","��ǰ��",}); 
      if(!me) return 0;
      daley_time = me->query_skill("force")/10;
      j=(int)((me->query_skill("kurong-changong",1)-40)/20);   

      if (j > 9) j = 9;

      if( !target ) target = offensive_target(me);
     
      if (!me->is_fighting() && !count){
           tell_object(me, WHT"\n�������ϣ���ʱ���Է��������졣\n"NOR);
           me->set_temp("jiuchong_ok",1);
           call_out("jiuchong_back",daley_time , me);
           return 1;
      }    
      if (me->query_skill_mapped("force") != "kurong-changong" ){
           me->delete_temp("pf_jiuchong");
           return notify_fail("�������ڹ�����,�޷��ٷ�������\n");
      }
      if (me->query_skill_mapped("parry") != "kurong-changong"){
           me->delete_temp("pf_jiuchong");
           return notify_fail("������ÿ���������Ϊ�мܣ�����ʹ�á������졹���С�\n");
      }
      if (me->query_skill_prepared("finger") == "yiyang-zhi"){
           me->delete_temp("pf_jiuchong");
           return notify_fail("�㲻����ͬʱʹ��һ��ָ�񹦣�\n");
      }
      if((int)me->query("neili") < 500 ){
           me->delete_temp("pf_jiuchong");
           return notify_fail("�������̫���ˣ��޷�ʹ�ó��������졹���У�\n");   
      }
      if (me->query_skill_prepared("strike") != "kurong-changong"){
           me->delete_temp("pf_jiuchong");
           return notify_fail("�����ʹ�ÿ���������Ϊ����Ʒ�����\n");
      }       
      if ( me->query_temp("pf_ku")){
           me->delete_temp("pf_jiuchong");
           return notify_fail("���������á��ݡ��ִ�,�޷�ʹ���������졹���У�\n");
      }      
      if( me->query_temp("pf_rong")){
           me->delete_temp("pf_jiuchong");
           return notify_fail("���������á��١��ִ�,�޷�ʹ���������졹���У�\n");
      }
      if( !target
       || target->is_ghost() 
       || !living(target)
       || !target->is_character() 
       || !me->is_fighting(target) 
       || environment(target) != environment(me)){
           me->delete_temp("pf_jiuchong");
           tell_object(me, RED"\n����Ҫʩչ������ȴ���ֶ����Ѿ������ٺ���ս���ˡ�\n"NOR);                         
           return 1;
      }               
      if (!count){
           tell_object(me, BLU"\n���������ߣ����ķ���"+chinese_number((int)me->query_temp("pf_jiuchong"))+"����������ʱ����������ӿ���ȣ�ɷ�����͡�\n"NOR);    
           count = 1;  
      }      
      if (!(int)me->query_temp("pf_jiuchong")){
           tell_object(me, RED"\n�㳤��һ�������������졹����ʩչ��ϡ�\n"NOR);
           me->delete_temp("jiuchong_ok");
           me->start_busy(2);
           me->start_perform(4,"�������졹");
           return 1;
      }
      damage = me->query_skill("buddhism",1);
      damage += me->query_skill("strike");

      if ((int)me->query_temp("pf_jiuchong") > 0){
        me->add_temp("pf_jiuchong",-1);
        limbs = target->query("limbs");
        message_vision(replace_string(SKILL_D("kurong-changong")->query_action(me, me->query_temp("weapon"))["action"],
                "$l", limbs[random(sizeof(limbs))]) + "\n", me, target);
        tell_object(target, BLU"\n��ͻȻ�о����ܲ��Ծ���������ӿ��һ���޴�����������Ŷ��ֵ�һ�д�"+targ[random(sizeof(targ))]+"Ϯ������\n"NOR);
        tell_object(me, BLU"\n��ʹ���������򡸾����졹,����������һ��һ��,һ���ƾ�������Ϣ,�ضԷ���"+targ[random(sizeof(targ))]+"Ϯȥ����\n"NOR);
        switch(random(3)) {
         case 0:{
             damage += me->query("jiali");
             me->set_temp("jct","jing");
         }
         break;
         case 1:{ 
             damage += damage/2+random(damage)/2;
             me->set_temp("jct","qi");
         }
         break;                        
         case 2:{     
             damage += me->query("jiali")+damage/3;
             me->set_temp("jct","jingli");
         }
         break;         
        } 
        if (random((int)me->query("combat_exp")) > (int)target->query("combat_exp")/(2+random(count))){
           me->start_busy(1);
           if((me->query_temp("jct")=="jing") && (damage > 600)) damage = 600;
           if((me->query_temp("jct")=="jingli")&&(damage > 700)) damage = 700;
           if((me->query_temp("jct")=="qi")&&(damage > 1000)) damage = 1000;
           if(me->query_temp("jct") !="jingli"){
             target->receive_damage((string)me->query_temp("jct"), damage);
             target->receive_wound((string)me->query_temp("jct"), damage/3);
             p = (int)target->query("qi")*100/(int)target->query("max_qi");
             msg = damage_msg(damage, "����");
             msg += "( $n"+eff_status_msg(p)+" )\n";
           }
           else{
             if( target->query("neili") > damage)
              target->add("neili",-damage);
             else 
              target->set("neili", 0);
             target->add("jingli",-damage);
             msg = RED"$p��ɫ�԰�,����ͻȻ��ҡ�һ�,�ƺ�վ�ھ��κ����У��ܵ���������Χ����ֻ��������㱣���������֧��ס�Լ���\n"NOR;
           }
           target->apply_condition("no_perform", 1);
           me->add("neili", - damage/5);
           me->add("jingli", -50);
           me->delete_temp("jct");
           message_vision(msg, me, target);
        } 
        else{       
           me->start_busy(1);
           me->add("neili", -(random(50)+30)); 
           me->add("jingli", -25);
           me->delete_temp("jct");
           dodge_skill = target->query_skill_mapped("dodge");
           if( !dodge_skill ) dodge_skill = "dodge";
           message_vision(SKILL_D(dodge_skill)->query_dodge_msg(target, 1), me, target);         
        }
        if(!living(target)
         || target->is_ghost() 
         || !target
         || !target->is_character() 
         || !me->is_fighting(target) 
         || environment(target)!=environment(me)){            
            me->delete_temp("pf_jiuchong");
            return 1;
        }
        else {
           me->start_perform(2,"�������졹");
           call_out("jiuchong_fight", 2, me, target, count);
        }
      }
      return 1;
}
