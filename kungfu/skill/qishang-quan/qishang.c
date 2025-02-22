#include <ansi.h>

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";
void remove_effect(object target,int damage);
string *songs = ({"五行之气调阴阳","损心伤肺摧肝肠","藏离精失意恍惚","三焦齐逆兮魂魄飞扬"});

int perform(object me, object target)
{
      string msg, song;                                   
      int p ,damage;
      song = songs[random(sizeof(songs))];
   
      if( !target ) target = offensive_target(me);
     
      if( !target
       || !target->is_character()
       || !me->is_fighting(target) || !living(target) )
           return notify_fail("「七伤总诀」只能在战斗中对对手使用。\n");
             
      if( objectp(me->query_temp("weapon")) )
           return notify_fail("你必须空手使用「七伤总诀」！\n");
      
      if( (int)me->query_skill("qishang-quan",1) < 120 )
           return notify_fail("你的七伤拳不够娴熟，不会使用「七伤总诀」！\n");
      
      if(userp(me) && (int)me->query_skill("shenghuo-shengong",1) < 100 )
           return notify_fail("你的圣火神功等级不够，不能使用「七伤总诀」！\n");  
      
      if(!me->query_skill("jiuyang-shengong", 1))
      if(userp(me) && me->query_skill_mapped("force") != "shenghuo-shengong")
           return notify_fail("你没有圣火神功内功，无法使用「七伤总诀」进行攻击。\n"); 
    
      if( (int)me->query_con() < 28 )
           return notify_fail("你的身体不够强壮，不能使用「七伤总诀」！\n");
      
      if( (int)me->query("max_neili") < 1200 )
           return notify_fail("你的内力太弱，不能使用「七伤总诀」！\n");
      
      if( (int)me->query("neili") < 700 )
           return notify_fail("你的内力太少了，无法使用出「七伤总诀」！\n");   

      if( (int)me->query("jingli") < 700 )
           return notify_fail("你的精力太少了，无法使用出「七伤总诀」！\n");     

      if (me->query_skill_prepared("cuff") != "qishang-quan"
       || me->query_skill_mapped("cuff") != "qishang-quan")
           return notify_fail("你现在无法使用「七伤总诀」进行攻击。\n");                                                                                 
      
      if(target->query_temp("qishang"))
           return notify_fail("对方已经身受「七伤总诀」，你不用费劲了！\n");
      
      message_vision(HIR"\n突然$N眼射精光，朗声念出句似歌非歌、似诗非诗的拳诀：“"+song+"”，\n"+
                        "接着走上前去，砰的一拳击向$n！\n"NOR,me, target);

      me->start_perform(6,"「七伤总诀」");

      if (random((int)me->query("combat_exp")) > (int)target->query("combat_exp")/3
       && random((int)me->query_skill("force")) > (int)target->query_skill("force")/3){ 
            target->receive_damage("qi", me->query_skill("force")*2);
            target->receive_wound("qi",me->query_skill("force"));
            me->add("neili", -400);
            me->add("jingli", -50);
            target->start_busy(1);
            if((me->query("neili") + me->query("con")*(20+random(20))) < target->query("neili"))
                 tell_object(me, HIR"你只觉"+target->name()+"体内内力极强，你暗藏在拳内的各种力道根本送不出去！\n"NOR);
            else{
                 damage = target->query_str()/2;
                 damage += target->query_int()/2;
                 damage += target->query_con()/2;
                 damage += target->query_dex()/2;
                 damage /= 4;
                 tell_object(me, HIW"在刚一触到"+target->name()+"的身体时，你便暗暗发力，将隐藏在在拳内的七种力道送了过去！\n"NOR);
                 tell_object(target, HIW"你一晃眼，只见"+me->name()+"的拳已经打在你的身上，跟着几股说不出的暗劲顺势传了过来！\n"NOR);
                 me->start_perform(7,"「七伤总诀」");
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
            msg = damage_msg(me->query_skill("force"), "内伤");
            msg += "( $n"+eff_status_msg(p)+" )\n";                
      } 
      else{
            me->start_busy(3);
            me->add("neili", -(100+random(100))); 
            me->add("jingli", -200);             
            msg = "只见$p轻轻一转身，已经绕到了$P身后。而$N却因劲力打空不受控制，头脑眩晕！\n";
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
      tell_object(target, HIW"终于，体内那几股暗劲在遍布你的全身后开始慢慢散去了。\n"NOR);
}
