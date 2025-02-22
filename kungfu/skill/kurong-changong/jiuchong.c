// kurong-changong's perform jiuchong
//九重天 
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
                return notify_fail("「九重天」只能在战斗中使用。\n");
      }
      if( objectp( me->query_temp("weapon")) )
                return notify_fail("只有空手才能施展「九重天」。\n");
      
      if( (int)me->query_skill("kurong-changong", 1) < 120 )
                return notify_fail("你的枯荣禅功修为不够，无法使用「九重天」绝招！\n");

      if (me->query_skill_mapped("force") != "kurong-changong")
                return notify_fail("你现在内功不对！\n");

      if (me->query_skill_mapped("parry") != "kurong-changong")
                return notify_fail("你必须用枯荣禅功作为招架，才能使用「九重天」绝招。\n");

      if (me->query_skill_prepared("finger") == "yiyang-zhi")
                 return notify_fail("你不可以同时使用一阳指神功！\n");

      if( (int)me->query("neili") < 500 )
                return notify_fail("你的内力太少了，无法使用出「九重天」绝招！\n");   
    
      if (me->query_skill_prepared("strike") != "kurong-changong" )
                 return notify_fail("你必须使用枯荣禅功作为你的掌法功夫！\n");
                 
      if( (int)me->query("max_neili") < 3000 )
                return notify_fail("你的内力修为这么差，还想使用「九重天」绝招？\n");   
                                                                                
/*
      if( me->query_temp("pf_ku"))
                return notify_fail("你正在运用「枯」字大法！\n");

      if( me->query_temp("pf_rong"))
                return notify_fail("你正在运用「荣」字大法！\n"); 
*/
      
      if (!me->query_temp("jiuchong_ok"))
      if( me->query_temp("pf_jiuchong"))
                return notify_fail("你正在运用「九重天」绝招！\n"); 
     
      i=(int)((me->query_skill("kurong-changong",1)-40)/20);
      if (i > 9) i = 9;  
      me->start_perform(9,"「九重天」");
      if (me->query_temp("jiuchong_ok")){
          me->delete_temp("jiuchong_ok");
          remove_call_out("jiuchong_back");
          call_out("jiuchong_fight", 0, me, target,0);
      }
      else {  
         tell_object(me, BLU"\n你心念一动，开始悄悄蓄气，准备发出"RED"九重天"BLU"绝招！\n"NOR);                         
         me->start_busy(1);
         me->set_temp("pf_jiuchong",i); 
         call_out("jiuchong_fight",  9, me, target,0);
      }
      return 1;
}

void jiuchong_back(object me)
{       
       if (!me) return;
       tell_object(me, RED"\n时候一到，你凝聚全身的九重天气劲慢慢散去。\n"NOR);    
       me->delete_temp("jiuchong_ok");
       me->delete_temp("pf_jiuchong");
       me->start_perform(4,"「九重天」");
}

int jiuchong_fight(object me, object target, int count)
{
      string msg,dodge_skill,*limbs;
      int damage,p,j;
      int daley_time;
                  
      string *targ=({"左下方","右前方","身体后方","头顶上方","地下","右侧面","左侧面","右下方","右上方","左前方",}); 
      if(!me) return 0;
      daley_time = me->query_skill("force")/10;
      j=(int)((me->query_skill("kurong-changong",1)-40)/20);   

      if (j > 9) j = 9;

      if( !target ) target = offensive_target(me);
     
      if (!me->is_fighting() && !count){
           tell_object(me, WHT"\n你聚气完毕，随时可以发出九重天。\n"NOR);
           me->set_temp("jiuchong_ok",1);
           call_out("jiuchong_back",daley_time , me);
           return 1;
      }    
      if (me->query_skill_mapped("force") != "kurong-changong" ){
           me->delete_temp("pf_jiuchong");
           return notify_fail("你现在内功不对,无法再发绝技！\n");
      }
      if (me->query_skill_mapped("parry") != "kurong-changong"){
           me->delete_temp("pf_jiuchong");
           return notify_fail("你必须用枯荣禅功作为招架，才能使用「九重天」绝招。\n");
      }
      if (me->query_skill_prepared("finger") == "yiyang-zhi"){
           me->delete_temp("pf_jiuchong");
           return notify_fail("你不可以同时使用一阳指神功！\n");
      }
      if((int)me->query("neili") < 500 ){
           me->delete_temp("pf_jiuchong");
           return notify_fail("你的内力太少了，无法使用出「九重天」绝招！\n");   
      }
      if (me->query_skill_prepared("strike") != "kurong-changong"){
           me->delete_temp("pf_jiuchong");
           return notify_fail("你必须使用枯荣禅功作为你的掌法功夫！\n");
      }       
      if ( me->query_temp("pf_ku")){
           me->delete_temp("pf_jiuchong");
           return notify_fail("你正在运用「枯」字大法,无法使出「九重天」绝招！\n");
      }      
      if( me->query_temp("pf_rong")){
           me->delete_temp("pf_jiuchong");
           return notify_fail("你正在运用「荣」字大法,无法使出「九重天」绝招！\n");
      }
      if( !target
       || target->is_ghost() 
       || !living(target)
       || !target->is_character() 
       || !me->is_fighting(target) 
       || environment(target) != environment(me)){
           me->delete_temp("pf_jiuchong");
           tell_object(me, RED"\n你正要施展绝技，却发现对手已经不敢再和你战斗了。\n"NOR);                         
           return 1;
      }               
      if (!count){
           tell_object(me, BLU"\n你力随掌走，悄悄发出"+chinese_number((int)me->query_temp("pf_jiuchong"))+"道掌力，顿时场面气流汹涌澎湃，煞是威猛。\n"NOR);    
           count = 1;  
      }      
      if (!(int)me->query_temp("pf_jiuchong")){
           tell_object(me, RED"\n你长吐一口气，「九重天」绝招施展完毕。\n"NOR);
           me->delete_temp("jiuchong_ok");
           me->start_busy(2);
           me->start_perform(4,"「九重天」");
           return 1;
      }
      damage = me->query_skill("buddhism",1);
      damage += me->query_skill("strike");

      if ((int)me->query_temp("pf_jiuchong") > 0){
        me->add_temp("pf_jiuchong",-1);
        limbs = target->query("limbs");
        message_vision(replace_string(SKILL_D("kurong-changong")->query_action(me, me->query_temp("weapon"))["action"],
                "$l", limbs[random(sizeof(limbs))]) + "\n", me, target);
        tell_object(target, BLU"\n你突然感觉四周不对劲，气流暗涌，一道巨大的掌力紧随着对手的一招从"+targ[random(sizeof(targ))]+"袭来！。\n"NOR);
        tell_object(me, BLU"\n你使出绝顶功夫「九重天」,紧随着袖袍一沉一挥,一道掌劲无声无息,沿对方的"+targ[random(sizeof(targ))]+"袭去！。\n"NOR);
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
             msg = damage_msg(damage, "内伤");
             msg += "( $n"+eff_status_msg(p)+" )\n";
           }
           else{
             if( target->query("neili") > damage)
              target->add("neili",-damage);
             else 
              target->set("neili", 0);
             target->add("jingli",-damage);
             msg = RED"$p面色苍白,身体突然左摇右晃,似乎站在惊涛骇浪中，受到重重掌力围挤，只觉精力恍惚，无力继续支撑住自己！\n"NOR;
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
           me->start_perform(2,"「九重天」");
           call_out("jiuchong_fight", 2, me, target, count);
        }
      }
      return 1;
}
