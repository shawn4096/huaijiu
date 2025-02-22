#include <ansi.h>
inherit F_SSERVER;

string perform_name(){ return RED"连环诀"NOR; }

#include "/kungfu/skill/eff_msg.h";

string *name1 = ({ MAG"胸口「膻中穴」"HIR, HIG"背心「灵台穴」"HIR, HIY"项颈「大椎穴」"HIR, HIM"胸下「巨阙穴」"HIR, 
                 HIC"双臂「清冷渊穴」"HIR, HIB"肋下「渊液穴」"HIR, HIW"胸口「玉枕穴」"HIR });

int perform(object me, object target)
{
      object wep;
      me = this_player();
      wep = me->query_temp("weapon");
      if( !target ) target = offensive_target(me);
      
      if( !target || !me->is_fighting(target) )
                 return notify_fail("「连」字诀只能在战斗中对对手使用。\n");

      if((int)me->query_temp("tjj/chan"))
                 return notify_fail("你现在正在使用「缠」字诀。\n");

      if(!living(target))
                 return notify_fail("「连」字诀只能在战斗中对对手使用。\n");

      if(!wep || wep->query("skill_type") != "sword" )
                 return notify_fail("你手中无剑，如何使得「连」字诀？\n");

      if(me->query_skill_mapped("sword") != "taiji-jian")
                 return notify_fail("你所备不是太极剑法，无法使用「连」字诀。\n");

      if(me->query_skill_mapped("parry") != "taiji-jian")
                 return notify_fail("你必须以太极剑法为招架才能使用「连」字诀。\n");  

      if( (int)me->query_temp("tjj/lian") )
                 return notify_fail("你现在正在使用「连」字诀。\n");

      if( (int)me->query_skill("taiji-jian", 1) <120)
                 return notify_fail("你的太极剑法修为尚不纯熟,无法使用「连」字诀！\n");             

      if( (int)me->query_skill("yinyun-ziqi",1) < 120 )
                 return notify_fail("你的氤氲紫气修为尚浅，不能使用「连」字诀！\n");

      if( (int)me->query_skill("sword",1) < 120 )
                 return notify_fail("你基本剑法修为尚不纯熟,不能使用「连」字诀！\n");  

      if( (int)me->query("max_neili") < 1500 )
                 return notify_fail("你的内力修为太弱，不能使用「连」字诀！\n");

      if( (int)me->query("neili") < 800 )
                 return notify_fail("你的真气太少了，不能使用「连」字诀！\n");  

      me->start_perform(7,"「连」字诀");
      message_vision(CYN"$N微微一笑，使出太极剑中"+RED+"「连」"+CYN+"字诀，当下身子缓缓右转,左手持剑向上提起，剑身横于胸前，左右掌心\n"
                        "相对，如抱圆球，手中"+wep->name()+CYN"未出，已然蓄势无穷。\n"NOR,me,target);
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
      msg = CYN"$N左手"+wep->name()+CYN"缓缓向前划出，成一弧形，一股森森寒气，直逼向$n，突然之间，$N剑交右手，寒光一闪，向$n划去。\n"NOR;
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
           msg += HIR"结果只听见$n一声惨嚎，"+wep->name()+HIR"已在$n的身上划出一道深可见骨的可怕伤口，鲜血溅得满地！！\n"NOR;
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
           msg += HIY"\n$p大叫一声不好，全身用力一纵，顺势跳了开去。\n\n" NOR;
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

      msg =CYN"$N又是剑交左手，在身前划了两个圆圈，剑劲连绵护住全身，竟无半分空隙，右手捏着剑诀，左手剑不住的\n"
              "抖动，罩向$n上盘七大要穴，剑尖急颤，看不出攻向何处。\n"NOR;     

      if (random(ap) > dp/2){         
         damage = i * 3/2 + random(i);
         if ( damage > 600 ) damage = 600;
         target->receive_damage("qi", damage);
         target->receive_wound("qi", damage/4);
         me->add("neili", -cost);
         me->add("jingli", -cost/5);
         if( damage < 500 ){
            msg += HIR"结果「噗嗤」地一声，"+wep->name()+HIR"已在$n"+name+"刺出一个血肉模糊的血窟窿！\n"NOR;
            msg += "( $n"+eff_status_msg(p)+" )\n\n";
         }
         else {
            msg +=HIR"结果只听见$n一声惨嚎，"+wep->name()+HIR"已在$n的"+name+"对穿而出，鲜血溅得满地！！\n"NOR;
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
         msg += HIR"\n只见$p一个纵身，远远地跳了开去。\n\n"NOR;
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

      msg = CYN"$N剑上所幻的"+RED+"光圈"+CYN+"越来越多，过不多时，全身已隐在无数"+RED+"光圈"+CYN+"之中，"+RED+"光圈"+CYN+"光圈一个未消，另一个再生，手中"+wep->name()+CYN"\n"
               "虽使得极快，却丝毫听不到金刃劈风之声，足见剑劲之柔韧已达于化境。\n"
            HIW"$n凝视剑光所幻无数"+RED+"光圈"+HIW+"绞向自己，见无可退避，只得冒险一击，当下手臂一伸，向"+RED+"光圈"+HIW+"的中心挥刃直入。\n"NOR;
               "手中"+wep->name()+HIW"虽使得极快，却丝毫听不到金刃劈风之声，足见剑劲之柔韧已达于化境。\n"
            WHT"$n凝视剑光所幻无数"+RED+"光圈"+WHT+"绞向自己，见无可退避，只得冒险一击，当下手臂一伸，向"+RED+"光圈"+WHT+"的中心挥刃直入。\n"NOR;

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
          msg += HIR"只听喀嚓喀嚓几声轻响，$n的手臂被光圈这么一套，登时绞断，整个身体亦被罩入剑光圈中。\n"NOR;
          msg += "( $n"+eff_status_msg(p)+" )\n\n"; 
          me->delete_temp("tjj/lian");
      }
      else{         
          me->start_busy(random(1)+2);
          me->add("neili", -cost);
          me->add("jingli", -cost/5);
          msg += HIR"当的一声大响，$n只感胸口剧烈一震，气血翻涌，一只手臂却仍然完好，无数光圈瞬时消失。\n"NOR; 
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
          msg = HIY"\n$N「连」字诀运行完毕，剑交左手，收剑而立，笼罩在全身上下的大小光圈随即不见踪影。\n\n"NOR;
          me->delete_temp("tjj/lian");
      }
      else {
          call_out("check_fight", 1, me, target);
          return 1;
      }
      message_vision(msg, me, target);
      return 1;
}
